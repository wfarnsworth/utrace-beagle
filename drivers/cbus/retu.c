/**
 * drivers/cbus/retu.c
 *
 * Support functions for Retu ASIC
 *
 * Copyright (C) 2004, 2005 Nokia Corporation
 *
 * Written by Juha Yrj�l� <juha.yrjola@nokia.com>,
 *	      David Weinehall <david.weinehall@nokia.com>, and
 *	      Mikko Ylinen <mikko.k.ylinen@nokia.com>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/poll.h>
#include <linux/fs.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>

#include <asm/uaccess.h>
#include <asm/mach-types.h>

#include <plat/mux.h>
#include <plat/board.h>

#include "cbus.h"
#include "retu.h"

#define RETU_ID			0x01
#define PFX			"retu: "

static int retu_initialized;
static int retu_is_vilma;

static struct tasklet_struct retu_tasklet;
spinlock_t retu_lock = SPIN_LOCK_UNLOCKED;

struct retu_irq_handler_desc {
	int (*func)(unsigned long);
	unsigned long arg;
	char name[8];
};

static struct retu_irq_handler_desc retu_irq_handlers[MAX_RETU_IRQ_HANDLERS];

int retu_get_status(void)
{
	return retu_initialized;
}
EXPORT_SYMBOL(retu_get_status);

/**
 * retu_read_reg - Read a value from a register in Retu
 * @reg: the register to read from
 *
 * This function returns the contents of the specified register
 */
int retu_read_reg(unsigned reg)
{
	BUG_ON(!retu_initialized);
	return cbus_read_reg(RETU_ID, reg);
}
EXPORT_SYMBOL(retu_read_reg);

/**
 * retu_write_reg - Write a value to a register in Retu
 * @reg: the register to write to
 * @reg: the value to write to the register
 *
 * This function writes a value to the specified register
 */
void retu_write_reg(unsigned reg, u16 val)
{
	BUG_ON(!retu_initialized);
	cbus_write_reg(RETU_ID, reg, val);
}
EXPORT_SYMBOL(retu_write_reg);

void retu_set_clear_reg_bits(unsigned reg, u16 set, u16 clear)
{
	unsigned long flags;
	u16 w;

	spin_lock_irqsave(&retu_lock, flags);
	w = retu_read_reg(reg);
	w &= ~clear;
	w |= set;
	retu_write_reg(reg, w);
	spin_unlock_irqrestore(&retu_lock, flags);
}
EXPORT_SYMBOL_GPL(retu_set_clear_reg_bits);

#define ADC_MAX_CHAN_NUMBER	13

int retu_read_adc(int channel)
{
	unsigned long flags;
	int res;

	if (channel < 0 || channel > ADC_MAX_CHAN_NUMBER)
		return -EINVAL;

	spin_lock_irqsave(&retu_lock, flags);

	if ((channel == 8) && retu_is_vilma) {
		int scr = retu_read_reg(RETU_REG_ADCSCR);
		int ch = (retu_read_reg(RETU_REG_ADCR) >> 10) & 0xf;
		if (((scr & 0xff) != 0) && (ch != 8))
			retu_write_reg (RETU_REG_ADCSCR, (scr & ~0xff));
	}

	/* Select the channel and read result */
	retu_write_reg(RETU_REG_ADCR, channel << 10);
	res = retu_read_reg(RETU_REG_ADCR) & 0x3ff;

	if (retu_is_vilma)
		retu_write_reg(RETU_REG_ADCR, (1 << 13));

	/* Unlock retu */
	spin_unlock_irqrestore(&retu_lock, flags);

	return res;
}
EXPORT_SYMBOL(retu_read_adc);

static u16 retu_disable_bogus_irqs(u16 mask)
{
       int i;

       for (i = 0; i < MAX_RETU_IRQ_HANDLERS; i++) {
               if (mask & (1 << i))
                       continue;
               if (retu_irq_handlers[i].func != NULL)
                       continue;
               /* an IRQ was enabled but we don't have a handler for it */
               printk(KERN_INFO PFX "disabling bogus IRQ %d\n", i);
               mask |= (1 << i);
       }
       return mask;
}

/*
 * Disable given RETU interrupt
 */
void retu_disable_irq(int id)
{
	unsigned long flags;
	u16 mask;

	spin_lock_irqsave(&retu_lock, flags);
	mask = retu_read_reg(RETU_REG_IMR);
	mask |= 1 << id;
	mask = retu_disable_bogus_irqs(mask);
	retu_write_reg(RETU_REG_IMR, mask);
	spin_unlock_irqrestore(&retu_lock, flags);
}
EXPORT_SYMBOL(retu_disable_irq);

/*
 * Enable given RETU interrupt
 */
void retu_enable_irq(int id)
{
	unsigned long flags;
	u16 mask;

	if (id == 3) {
		printk("Enabling Retu IRQ %d\n", id);
		dump_stack();
	}
	spin_lock_irqsave(&retu_lock, flags);
	mask = retu_read_reg(RETU_REG_IMR);
	mask &= ~(1 << id);
	mask = retu_disable_bogus_irqs(mask);
	retu_write_reg(RETU_REG_IMR, mask);
	spin_unlock_irqrestore(&retu_lock, flags);
}
EXPORT_SYMBOL(retu_enable_irq);

/*
 * Acknowledge given RETU interrupt
 */
void retu_ack_irq(int id)
{
	retu_write_reg(RETU_REG_IDR, 1 << id);
}
EXPORT_SYMBOL(retu_ack_irq);

/*
 * RETU interrupt handler. Only schedules the tasklet.
 */
static irqreturn_t retu_irq_handler(int irq, void *dev_id)
{
	tasklet_schedule(&retu_tasklet);
	return IRQ_HANDLED;
}

/*
 * Tasklet handler
 */
static void retu_tasklet_handler(unsigned long data)
{
	struct retu_irq_handler_desc *hnd;
	u16 id;
	u16 im;
	int i;

	for (;;) {
		id = retu_read_reg(RETU_REG_IDR);
		im = ~retu_read_reg(RETU_REG_IMR);
		id &= im;

		if (!id)
			break;

		for (i = 0; id != 0; i++, id >>= 1) {
			if (!(id & 1))
				continue;
			hnd = &retu_irq_handlers[i];
			if (hnd->func == NULL) {
                               /* Spurious retu interrupt - disable and ack it */
				printk(KERN_INFO "Spurious Retu interrupt "
						 "(id %d)\n", i);
				retu_disable_irq(i);
				retu_ack_irq(i);
				continue;
			}
			hnd->func(hnd->arg);
			/*
			 * Don't acknowledge the interrupt here
			 * It must be done explicitly
			 */
		}
	}
}

/*
 * Register the handler for a given RETU interrupt source.
 */
int retu_request_irq(int id, void *irq_handler, unsigned long arg, char *name)
{
	struct retu_irq_handler_desc *hnd;

	if (!retu_initialized)
		return -ENODEV;

	if (irq_handler == NULL || id >= MAX_RETU_IRQ_HANDLERS ||
	    name == NULL) {
		printk(KERN_ERR PFX "Invalid arguments to %s\n",
		       __FUNCTION__);
		return -EINVAL;
	}
	hnd = &retu_irq_handlers[id];
	if (hnd->func != NULL) {
		printk(KERN_ERR PFX "IRQ %d already reserved\n", id);
		return -EBUSY;
	}
	printk(KERN_INFO PFX "Registering interrupt %d for device %s\n",
	       id, name);
	hnd->func = irq_handler;
	hnd->arg = arg;
	strlcpy(hnd->name, name, sizeof(hnd->name));

	retu_ack_irq(id);
	retu_enable_irq(id);

	return 0;
}
EXPORT_SYMBOL(retu_request_irq);

/*
 * Unregister the handler for a given RETU interrupt source.
 */
void retu_free_irq(int id)
{
	struct retu_irq_handler_desc *hnd;

	if (id >= MAX_RETU_IRQ_HANDLERS) {
		printk(KERN_ERR PFX "Invalid argument to %s\n",
		       __FUNCTION__);
		return;
	}
	hnd = &retu_irq_handlers[id];
	if (hnd->func == NULL) {
		printk(KERN_ERR PFX "IRQ %d already freed\n", id);
		return;
	}

	retu_disable_irq(id);
	hnd->func = NULL;
}
EXPORT_SYMBOL(retu_free_irq);

/**
 * retu_power_off - Shut down power to system
 *
 * This function puts the system in power off state
 */
static void retu_power_off(void)
{
	/* Ignore power button state */
	retu_write_reg(RETU_REG_CC1, retu_read_reg(RETU_REG_CC1) | 2);
	/* Expire watchdog immediately */
	retu_write_reg(RETU_REG_WATCHDOG, 0);
	/* Wait for poweroff*/
	for (;;);
}

/**
 * retu_allocate_child - Allocates one Retu child
 * @name: name of new child
 * @parent: parent device for this child
 */
static struct device *retu_allocate_child(char *name, struct device *parent)
{
	struct platform_device		*pdev;
	int				status;

	pdev = platform_device_alloc(name, -1);
	if (!pdev) {
		dev_dbg(parent, "can't allocate %s\n", name);
		goto err;
	}

	pdev->dev.parent = parent;

	status = platform_device_add(pdev);
	if (status < 0) {
		dev_dbg(parent, "can't add %s\n", name);
		goto err;
	}

	return &pdev->dev;

err:
	platform_device_put(pdev);
	return NULL;
}

/**
 * retu_allocate_children - Allocates Retu's children
 */
static int retu_allocate_children(struct device *parent)
{
	struct device	*child;

	child = retu_allocate_child("retu-pwrbutton", parent);
	if (!child)
		return -ENOMEM;

	child = retu_allocate_child("retu-headset", parent);
	if (!child)
		return -ENOMEM;

	child = retu_allocate_child("retu-rtc", parent);
	if (!child)
		return -ENOMEM;

	child = retu_allocate_child("retu-user", parent);
	if (!child)
		return -ENOMEM;

	child = retu_allocate_child("retu-wdt", parent);
	if (!child)
		return -ENOMEM;

	return 0;
}

/**
 * retu_probe - Probe for Retu ASIC
 * @dev: the Retu device
 *
 * Probe for the Retu ASIC and allocate memory
 * for its device-struct if found
 */
static int __init retu_probe(struct platform_device *pdev)
{
	int rev, ret;
	int irq;

	/* Prepare tasklet */
	tasklet_init(&retu_tasklet, retu_tasklet_handler, 0);

	irq = platform_get_irq(pdev, 0);

	retu_initialized = 1;

	rev = retu_read_reg(RETU_REG_ASICR) & 0xff;
	if (rev & (1 << 7))
		retu_is_vilma = 1;

	dev_info(&pdev->dev, "%s v%d.%d found\n", retu_is_vilma ? "Vilma" : "Retu",
	       (rev >> 4) & 0x07, rev & 0x0f);

	/* Mask all RETU interrupts */
	retu_write_reg(RETU_REG_IMR, 0xffff);

	ret = request_irq(irq, retu_irq_handler, 0,
			  "retu", 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "Unable to register IRQ handler\n");
		return ret;
	}

	set_irq_wake(irq, 1);

	/* Register power off function */
	pm_power_off = retu_power_off;

#ifdef CONFIG_CBUS_RETU_USER
	/* Initialize user-space interface */
	if (retu_user_init() < 0) {
		dev_err(&pdev->dev, "Unable to initialize driver\n");
		free_irq(irq, 0);
		return ret;
	}
#endif

	ret = retu_allocate_children(&pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Unable to allocate Retu children\n");
#ifdef CONFIG_CBUS_RETU_USER
		retu_user_cleanup();
#endif
		retu_write_reg(RETU_REG_IMR, 0xffff);
		free_irq(irq, 0);
		tasklet_kill(&retu_tasklet);
		return ret;
	}

	return 0;
}

static int __exit retu_remove(struct platform_device *pdev)
{
	int irq;

	irq = platform_get_irq(pdev, 0);

#ifdef CONFIG_CBUS_RETU_USER
	retu_user_cleanup();
#endif
	/* Mask all RETU interrupts */
	retu_write_reg(RETU_REG_IMR, 0xffff);
	free_irq(irq, 0);
	tasklet_kill(&retu_tasklet);

	return 0;
}

static struct platform_driver retu_driver = {
	.remove		= __exit_p(retu_remove),
	.driver		= {
		.name	= "retu",
	},
};

/**
 * retu_init - initialise Retu driver
 *
 * Initialise the Retu driver and return 0 if everything worked ok
 */
static int __init retu_init(void)
{
	return platform_driver_probe(&retu_driver, retu_probe);
}

/*
 * Cleanup
 */
static void __exit retu_exit(void)
{
	platform_driver_unregister(&retu_driver);
}

subsys_initcall(retu_init);
module_exit(retu_exit);

MODULE_DESCRIPTION("Retu ASIC control");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Juha Yrj�l�");
MODULE_AUTHOR("David Weinehall");
MODULE_AUTHOR("Mikko Ylinen");
