/*
 * linux/arch/arm/mach-omap2/board-omap3beagle.c
 *
 * Copyright (C) 2008 Texas Instruments
 *
 * Modified from mach-omap2/board-3430sdp.c
 *
 * Initial code: Syed Mohammed Khasim
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/input.h>
#include <linux/gpio_keys.h>
#include <linux/opp.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/nand.h>
#include <linux/mmc/host.h>

#include <linux/regulator/machine.h>
#include <linux/i2c/twl.h>

#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/flash.h>

#include <plat/board.h>
#include <plat/common.h>
#include <plat/display.h>
#include <plat/gpmc.h>
#include <plat/nand.h>
#include <plat/usb.h>
#include <plat/omap_device.h>

#include "mux.h"
#include "hsmmc.h"
#include "timer-gp.h"
#include "pm.h"

#define NAND_BLOCK_SIZE		SZ_128K

/*
 * OMAP3 Beagle revision
 * Run time detection of Beagle revision is done by reading GPIO.
 * GPIO ID -
 *	AXBX	= GPIO173, GPIO172, GPIO171: 1 1 1
 *	C1_3	= GPIO173, GPIO172, GPIO171: 1 1 0
 *	C4	= GPIO173, GPIO172, GPIO171: 1 0 1
 *	XMA	= GPIO173, GPIO172, GPIO171: 0 0 0
 *	XMB	= GPIO173, GPIO172, GPIO171: 0 0 1
 *  XMC = GPIO173, GPIO172, GPIO171: 0 1 0
 */
enum {
	OMAP3BEAGLE_BOARD_UNKN = 0,
	OMAP3BEAGLE_BOARD_AXBX,
	OMAP3BEAGLE_BOARD_C1_3,
	OMAP3BEAGLE_BOARD_C4,
	OMAP3BEAGLE_BOARD_XM,
	OMAP3BEAGLE_BOARD_XMC,
};

static u8 omap3_beagle_version;

static u8 omap3_beagle_get_rev(void)
{
	return omap3_beagle_version;
}

static void __init omap3_beagle_init_rev(void)
{
	int ret;
	u16 beagle_rev = 0;

	omap_mux_init_gpio(171, OMAP_PIN_INPUT_PULLUP);
	omap_mux_init_gpio(172, OMAP_PIN_INPUT_PULLUP);
	omap_mux_init_gpio(173, OMAP_PIN_INPUT_PULLUP);

	ret = gpio_request(171, "rev_id_0");
	if (ret < 0)
		goto fail0;

	ret = gpio_request(172, "rev_id_1");
	if (ret < 0)
		goto fail1;

	ret = gpio_request(173, "rev_id_2");
	if (ret < 0)
		goto fail2;

	gpio_direction_input(171);
	gpio_direction_input(172);
	gpio_direction_input(173);

	beagle_rev = gpio_get_value(171) | (gpio_get_value(172) << 1)
			| (gpio_get_value(173) << 2);

	switch (beagle_rev) {
	case 7:
		printk(KERN_INFO "OMAP3 Beagle Rev: Ax/Bx\n");
		omap3_beagle_version = OMAP3BEAGLE_BOARD_AXBX;
		break;
	case 6:
		printk(KERN_INFO "OMAP3 Beagle Rev: C1/C2/C3\n");
		omap3_beagle_version = OMAP3BEAGLE_BOARD_C1_3;
		break;
	case 5:
		printk(KERN_INFO "OMAP3 Beagle Rev: C4\n");
		omap3_beagle_version = OMAP3BEAGLE_BOARD_C4;
		break;
	case 0:
		printk(KERN_INFO "OMAP3 Beagle Rev: xM A\n");
		omap3_beagle_version = OMAP3BEAGLE_BOARD_XM;
		break;
	case 1:
		printk(KERN_INFO "OMAP3 Beagle Rev: xM B\n");
		omap3_beagle_version = OMAP3BEAGLE_BOARD_XM;
		break;
	case 2:
		printk(KERN_INFO "OMAP3 Beagle Rev: xM C\n");
		omap3_beagle_version = OMAP3BEAGLE_BOARD_XMC;
		break;
	default:
		printk(KERN_INFO "OMAP3 Beagle Rev: unknown %hd, assuming xM C or newer\n", beagle_rev);
		omap3_beagle_version = OMAP3BEAGLE_BOARD_XMC;
	}

	return;

fail2:
	gpio_free(172);
fail1:
	gpio_free(171);
fail0:
	printk(KERN_ERR "Unable to get revision detection GPIO pins\n");
	omap3_beagle_version = OMAP3BEAGLE_BOARD_UNKN;

	return;
}

char expansionboard_name[16];

#if defined(CONFIG_WL1271) || defined(CONFIG_WL1271_MODULE)
#include <linux/regulator/fixed.h>
#include <linux/wl12xx.h>

#define OMAP_BEAGLE_WLAN_EN_GPIO    (139)
#define OMAP_BEAGLE_WLAN_IRQ_GPIO   (137)

struct wl12xx_platform_data omap_beagle_wlan_data __initdata = {
	.irq = OMAP_GPIO_IRQ(OMAP_BEAGLE_WLAN_IRQ_GPIO),
	.board_ref_clock = 2, /* 38.4 MHz */
};

static struct omap2_hsmmc_info mmcbbt[] = {
	{
		.mmc		= 1,
		.caps		= MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA,
		.gpio_wp	= 29,
	},
	{
		.name		= "wl1271",
		.mmc		= 2,
		.caps		= MMC_CAP_4_BIT_DATA | MMC_CAP_POWER_OFF_CARD,
		.gpio_wp	= -EINVAL,
		.gpio_cd	= -EINVAL,
		.nonremovable	= true,
	},
	{}	/* Terminator */
};

static struct regulator_consumer_supply beagle_vmmc2_supply = {
	.supply         = "vmmc",
	.dev_name       = "mmci-omap-hs.1",
};

static struct regulator_init_data beagle_vmmc2 = {
	.constraints = {
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies = 1,
	.consumer_supplies = &beagle_vmmc2_supply,
};

static struct fixed_voltage_config beagle_vwlan = {
	.supply_name = "vwl1271",
	.microvolts = 1800000,  /* 1.8V */
	.gpio = OMAP_BEAGLE_WLAN_EN_GPIO,
	.startup_delay = 70000, /* 70ms */
	.enable_high = 1,
	.enabled_at_boot = 0,
	.init_data = &beagle_vmmc2,
};

static struct platform_device omap_vwlan_device = {
	.name           = "reg-fixed-voltage",
	.id             = 1,
	.dev = {
		.platform_data = &beagle_vwlan,
	},
};
#endif

#if defined(CONFIG_ENC28J60) || defined(CONFIG_ENC28J60_MODULE)

#include <plat/mcspi.h>
#include <linux/spi/spi.h>

#define OMAP3BEAGLE_GPIO_ENC28J60_IRQ 157

static struct omap2_mcspi_device_config enc28j60_spi_chip_info = {
	.turbo_mode	= 0,
	.single_channel	= 1,	/* 0: slave, 1: master */
};

static struct spi_board_info omap3beagle_zippy_spi_board_info[] __initdata = {
	{
		.modalias		= "enc28j60",
		.bus_num		= 4,
		.chip_select		= 0,
		.max_speed_hz		= 20000000,
		.controller_data	= &enc28j60_spi_chip_info,
	},
};

static void __init omap3beagle_enc28j60_init(void)
{
	if ((gpio_request(OMAP3BEAGLE_GPIO_ENC28J60_IRQ, "ENC28J60_IRQ") == 0) &&
	    (gpio_direction_input(OMAP3BEAGLE_GPIO_ENC28J60_IRQ) == 0)) {
		gpio_export(OMAP3BEAGLE_GPIO_ENC28J60_IRQ, 0);
		omap3beagle_zippy_spi_board_info[0].irq	= OMAP_GPIO_IRQ(OMAP3BEAGLE_GPIO_ENC28J60_IRQ);
		set_irq_type(omap3beagle_zippy_spi_board_info[0].irq, IRQ_TYPE_EDGE_FALLING);
	} else {
		printk(KERN_ERR "could not obtain gpio for ENC28J60_IRQ\n");
		return;
	}

	spi_register_board_info(omap3beagle_zippy_spi_board_info,
			ARRAY_SIZE(omap3beagle_zippy_spi_board_info));
}

#else
static inline void __init omap3beagle_enc28j60_init(void) { return; }
#endif

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)

#include <plat/mcspi.h>
#include <linux/spi/spi.h>

#define OMAP3BEAGLE_GPIO_KS8851_IRQ 157

static struct omap2_mcspi_device_config ks8851_spi_chip_info = {
	.turbo_mode	= 0,
	.single_channel	= 1,	/* 0: slave, 1: master */
};

static struct spi_board_info omap3beagle_zippy2_spi_board_info[] __initdata = {
	{
		.modalias		= "ks8851",
		.bus_num		= 4,
		.chip_select		= 0,
		.max_speed_hz		= 36000000,
		.controller_data	= &ks8851_spi_chip_info,
	},
};

static void __init omap3beagle_ks8851_init(void)
{
	if ((gpio_request(OMAP3BEAGLE_GPIO_KS8851_IRQ, "KS8851_IRQ") == 0) &&
	    (gpio_direction_input(OMAP3BEAGLE_GPIO_KS8851_IRQ) == 0)) {
		gpio_export(OMAP3BEAGLE_GPIO_KS8851_IRQ, 0);
		omap3beagle_zippy2_spi_board_info[0].irq	= OMAP_GPIO_IRQ(OMAP3BEAGLE_GPIO_KS8851_IRQ);
		set_irq_type(omap3beagle_zippy2_spi_board_info[0].irq, IRQ_TYPE_EDGE_FALLING);
	} else {
		printk(KERN_ERR "could not obtain gpio for KS8851_IRQ\n");
		return;
	}
	
	spi_register_board_info(omap3beagle_zippy2_spi_board_info,
							ARRAY_SIZE(omap3beagle_zippy2_spi_board_info));
}

#else
static inline void __init omap3beagle_ks8851_init(void) { return; }
#endif

static struct mtd_partition omap3beagle_nand_partitions[] = {
	/* All the partition sizes are listed in terms of NAND block size */
	{
		.name		= "X-Loader",
		.offset		= 0,
		.size		= 4 * NAND_BLOCK_SIZE,
		.mask_flags	= MTD_WRITEABLE,	/* force read-only */
	},
	{
		.name		= "U-Boot",
		.offset		= MTDPART_OFS_APPEND,	/* Offset = 0x80000 */
		.size		= 15 * NAND_BLOCK_SIZE,
		.mask_flags	= MTD_WRITEABLE,	/* force read-only */
	},
	{
		.name		= "U-Boot Env",
		.offset		= MTDPART_OFS_APPEND,	/* Offset = 0x260000 */
		.size		= 1 * NAND_BLOCK_SIZE,
	},
	{
		.name		= "Kernel",
		.offset		= MTDPART_OFS_APPEND,	/* Offset = 0x280000 */
		.size		= 32 * NAND_BLOCK_SIZE,
	},
	{
		.name		= "File System",
		.offset		= MTDPART_OFS_APPEND,	/* Offset = 0x680000 */
		.size		= MTDPART_SIZ_FULL,
	},
};

static struct omap_nand_platform_data omap3beagle_nand_data = {
	.options	= NAND_BUSWIDTH_16,
	.parts		= omap3beagle_nand_partitions,
	.nr_parts	= ARRAY_SIZE(omap3beagle_nand_partitions),
	.dma_channel	= -1,		/* disable DMA in OMAP NAND driver */
	.nand_setup	= NULL,
	.dev_ready	= NULL,
};

/* DSS */

static int beagle_enable_dvi(struct omap_dss_device *dssdev)
{
	if (gpio_is_valid(dssdev->reset_gpio))
		gpio_set_value(dssdev->reset_gpio, 1);

	return 0;
}

static void beagle_disable_dvi(struct omap_dss_device *dssdev)
{
	if (gpio_is_valid(dssdev->reset_gpio))
		gpio_set_value(dssdev->reset_gpio, 0);
}

static struct omap_dss_device beagle_dvi_device = {
	.type = OMAP_DISPLAY_TYPE_DPI,
	.name = "dvi",
	.driver_name = "generic_panel",
	.phy.dpi.data_lines = 24,
	.reset_gpio = -EINVAL,
	.platform_enable = beagle_enable_dvi,
	.platform_disable = beagle_disable_dvi,
};

static struct omap_dss_device beagle_tv_device = {
	.name = "tv",
	.driver_name = "venc",
	.type = OMAP_DISPLAY_TYPE_VENC,
	.phy.venc.type = OMAP_DSS_VENC_TYPE_SVIDEO,
};

static struct omap_dss_device *beagle_dss_devices[] = {
	&beagle_dvi_device,
	&beagle_tv_device,
};

static struct omap_dss_board_info beagle_dss_data = {
	.num_devices = ARRAY_SIZE(beagle_dss_devices),
	.devices = beagle_dss_devices,
	.default_device = &beagle_dvi_device,
};

static struct platform_device beagle_dss_device = {
	.name          = "omapdss",
	.id            = -1,
	.dev            = {
		.platform_data = &beagle_dss_data,
	},
};

static struct regulator_consumer_supply beagle_vdac_supply =
	REGULATOR_SUPPLY("vdda_dac", "omapdss");

static struct regulator_consumer_supply beagle_vdvi_supply =
	REGULATOR_SUPPLY("vdds_dsi", "omapdss");

static void __init beagle_display_init(void)
{
	int r;

	r = gpio_request(beagle_dvi_device.reset_gpio, "DVI reset");
	if (r < 0) {
		printk(KERN_ERR "Unable to get DVI reset GPIO\n");
		return;
	}

	gpio_direction_output(beagle_dvi_device.reset_gpio, 0);
}

#include "sdram-micron-mt46h32m32lf-6.h"

static struct omap2_hsmmc_info mmc[] = {
	{
		.mmc		= 1,
		.caps		= MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA,
		.gpio_wp	= 29,
	},
	{
		.mmc		= 2,
		.caps       = MMC_CAP_4_BIT_DATA,
		.transceiver	= true,
		.ocr_mask	= 0x00100000,	/* 3.3V */
	},
	{}	/* Terminator */
};

static struct regulator_consumer_supply beagle_vmmc1_supply = {
	.supply			= "vmmc",
};

static struct regulator_consumer_supply beagle_vsim_supply = {
	.supply			= "vmmc_aux",
};

static struct gpio_led gpio_leds[];

static int beagle_twl_gpio_setup(struct device *dev,
		unsigned gpio, unsigned ngpio)
{
	int r;

	if (omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XM || omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XMC) {
		mmc[0].gpio_wp = -EINVAL;
	} else if ((omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_C1_3) ||
		(omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_C4)) {
		omap_mux_init_gpio(23, OMAP_PIN_INPUT);
		mmc[0].gpio_wp = 23;
	} else {
		omap_mux_init_gpio(29, OMAP_PIN_INPUT);
	}
	/* gpio + 0 is "mmc0_cd" (input/IRQ) */
	mmc[0].gpio_cd = gpio + 0;
#if defined(CONFIG_WL1271) || defined(CONFIG_WL1271_MODULE)
	if(!strcmp(expansionboard_name, "bbtoys-wifi")) {
		omap2_hsmmc_init(mmcbbt);
		/* link regulators to MMC adapters */
		beagle_vmmc1_supply.dev = mmcbbt[0].dev;
		beagle_vsim_supply.dev = mmcbbt[0].dev;
	} else {
		omap2_hsmmc_init(mmc);
		/* link regulators to MMC adapters */
		beagle_vmmc1_supply.dev = mmc[0].dev;
		beagle_vsim_supply.dev = mmc[0].dev;
	}
#else
	omap2_hsmmc_init(mmc);
	/* link regulators to MMC adapters */
	beagle_vmmc1_supply.dev = mmc[0].dev;
	beagle_vsim_supply.dev = mmc[0].dev;
#endif

	/* REVISIT: need ehci-omap hooks for external VBUS
	 * power switch and overcurrent detect
	 */
	if (omap3_beagle_get_rev() != OMAP3BEAGLE_BOARD_XM && omap3_beagle_get_rev() != OMAP3BEAGLE_BOARD_XMC) {
		r = gpio_request(gpio + 1, "EHCI_nOC");
		if (!r) {
			r = gpio_direction_input(gpio + 1);
			if (r)
				gpio_free(gpio + 1);
		}
		if (r)
			pr_err("%s: unable to configure EHCI_nOC\n", __func__);
	}

	/*
	 * TWL4030_GPIO_MAX + 0 == ledA, EHCI nEN_USB_PWR (out, XM active
	 * high / others active low)
	 */
	gpio_request(gpio + TWL4030_GPIO_MAX, "nEN_USB_PWR");
	if (omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XM)
		gpio_direction_output(gpio + TWL4030_GPIO_MAX, 1);
	else
		gpio_direction_output(gpio + TWL4030_GPIO_MAX, 0);

	/* DVI reset GPIO is different between beagle revisions */
	if (omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XM || omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XMC)
		beagle_dvi_device.reset_gpio = 129;
	else
		beagle_dvi_device.reset_gpio = 170;

	/* TWL4030_GPIO_MAX + 1 == ledB, PMU_STAT (out, active low LED) */
	gpio_leds[2].gpio = gpio + TWL4030_GPIO_MAX + 1;

	/*
	 * gpio + 1 on Xm controls the TFP410's enable line (active low)
	 * gpio + 2 control varies depending on the board rev as follows:
	 * P7/P8 revisions(prototype): Camera EN
	 * A2+ revisions (production): LDO (supplies DVI, serial, led blocks)
	 */
	if (omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XM || omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XMC) {
		r = gpio_request(gpio + 1, "nDVI_PWR_EN");
		if (!r) {
			r = gpio_direction_output(gpio + 1, 0);
			if (r)
				gpio_free(gpio + 1);
		}
		if (r)
			pr_err("%s: unable to configure nDVI_PWR_EN\n",
				__func__);
		r = gpio_request(gpio + 2, "DVI_LDO_EN");
		if (!r) {
			r = gpio_direction_output(gpio + 2, 1);
			if (r)
				gpio_free(gpio + 2);
		}
		if (r)
			pr_err("%s: unable to configure DVI_LDO_EN\n",
				__func__);
	}

	return 0;
}

static struct twl4030_gpio_platform_data beagle_gpio_data = {
	.gpio_base	= OMAP_MAX_GPIO_LINES,
	.irq_base	= TWL4030_GPIO_IRQ_BASE,
	.irq_end	= TWL4030_GPIO_IRQ_END,
	.use_leds	= true,
	.pullups	= BIT(1),
	.pulldowns	= BIT(2) | BIT(6) | BIT(7) | BIT(8) | BIT(13)
				| BIT(15) | BIT(16) | BIT(17),
	.setup		= beagle_twl_gpio_setup,
};

/* VMMC1 for MMC1 pins CMD, CLK, DAT0..DAT3 (20 mA, plus card == max 220 mA) */
static struct regulator_init_data beagle_vmmc1 = {
	.constraints = {
		.min_uV			= 1850000,
		.max_uV			= 3150000,
		.valid_modes_mask	= REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_STANDBY,
		.valid_ops_mask		= REGULATOR_CHANGE_VOLTAGE
					| REGULATOR_CHANGE_MODE
					| REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &beagle_vmmc1_supply,
};

/* VSIM for MMC1 pins DAT4..DAT7 (2 mA, plus card == max 50 mA) */
static struct regulator_init_data beagle_vsim = {
	.constraints = {
		.min_uV			= 1800000,
		.max_uV			= 3000000,
		.valid_modes_mask	= REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_STANDBY,
		.valid_ops_mask		= REGULATOR_CHANGE_VOLTAGE
					| REGULATOR_CHANGE_MODE
					| REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &beagle_vsim_supply,
};

/* VDAC for DSS driving S-Video (8 mA unloaded, max 65 mA) */
static struct regulator_init_data beagle_vdac = {
	.constraints = {
		.min_uV			= 1800000,
		.max_uV			= 1800000,
		.valid_modes_mask	= REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_STANDBY,
		.valid_ops_mask		= REGULATOR_CHANGE_MODE
					| REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &beagle_vdac_supply,
};

/* VPLL2 for digital video outputs */
static struct regulator_init_data beagle_vpll2 = {
	.constraints = {
		.name			= "VDVI",
		.min_uV			= 1800000,
		.max_uV			= 1800000,
		.valid_modes_mask	= REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_STANDBY,
		.valid_ops_mask		= REGULATOR_CHANGE_MODE
					| REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &beagle_vdvi_supply,
};

static struct twl4030_usb_data beagle_usb_data = {
	.usb_mode	= T2_USB_MODE_ULPI,
};

static struct twl4030_codec_audio_data beagle_audio_data = {
	.audio_mclk = 26000000,
};

static struct twl4030_codec_data beagle_codec_data = {
	.audio_mclk = 26000000,
	.audio = &beagle_audio_data,
};

static struct twl4030_madc_platform_data beagle_madc_data = {
	.irq_line	= 1,
};

static struct twl4030_platform_data beagle_twldata = {
	.irq_base	= TWL4030_IRQ_BASE,
	.irq_end	= TWL4030_IRQ_END,

	/* platform_data for children goes here */
	.usb		= &beagle_usb_data,
	.gpio		= &beagle_gpio_data,
	.codec		= &beagle_codec_data,
	.madc		= &beagle_madc_data,
	.vmmc1		= &beagle_vmmc1,
	.vsim		= &beagle_vsim,
	.vdac		= &beagle_vdac,
	.vpll2		= &beagle_vpll2,
};

static struct i2c_board_info __initdata beagle_i2c1_boardinfo[] = {
	{
		I2C_BOARD_INFO("twl4030", 0x48),
		.flags = I2C_CLIENT_WAKE,
		.irq = INT_34XX_SYS_NIRQ,
		.platform_data = &beagle_twldata,
	},
};

static struct i2c_board_info __initdata beagle_i2c_eeprom[] = {
	{
		I2C_BOARD_INFO("eeprom", 0x50),
	},
};

#if defined(CONFIG_RTC_DRV_DS1307) || \
	defined(CONFIG_RTC_DRV_DS1307_MODULE)

static struct i2c_board_info __initdata beagle_i2c2_boardinfo[] = {
	{
		I2C_BOARD_INFO("ds1307", 0x68),
	},
};
#else
static struct i2c_board_info __initdata beagle_i2c2_boardinfo[] = {};
#endif

static int __init omap3_beagle_i2c_init(void)
{
	omap_register_i2c_bus(1, 2600, beagle_i2c1_boardinfo,
			ARRAY_SIZE(beagle_i2c1_boardinfo));
	omap_register_i2c_bus(2, 400,  beagle_i2c2_boardinfo,
			ARRAY_SIZE(beagle_i2c2_boardinfo));
	/* Bus 3 is attached to the DVI port where devices like the pico DLP
	 * projector don't work reliably with 400kHz */
	omap_register_i2c_bus(3, 100, beagle_i2c_eeprom, ARRAY_SIZE(beagle_i2c_eeprom));
	return 0;
}

static struct gpio_led gpio_leds[] = {
	{
		.name			= "beagleboard::usr0",
		.default_trigger	= "heartbeat",
		.gpio			= 150,
	},
	{
		.name			= "beagleboard::usr1",
		.default_trigger	= "mmc0",
		.gpio			= 149,
	},
	{
		.name			= "beagleboard::pmu_stat",
		.gpio			= -EINVAL,	/* gets replaced */
		.active_low		= true,
	},
};

static struct gpio_led_platform_data gpio_led_info = {
	.leds		= gpio_leds,
	.num_leds	= ARRAY_SIZE(gpio_leds),
};

static struct platform_device leds_gpio = {
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= {
		.platform_data	= &gpio_led_info,
	},
};

static struct gpio_keys_button gpio_buttons[] = {
	{
		.code			= BTN_EXTRA,
		.gpio			= 7,
		.desc			= "user",
		.wakeup			= 1,
	},
};

static struct gpio_keys_platform_data gpio_key_info = {
	.buttons	= gpio_buttons,
	.nbuttons	= ARRAY_SIZE(gpio_buttons),
};

static struct platform_device keys_gpio = {
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= {
		.platform_data	= &gpio_key_info,
	},
};

static void __init omap3_beagle_init_irq(void)
{
	omap2_init_common_infrastructure();
	omap2_init_common_devices(mt46h32m32lf6_sdrc_params,
				  mt46h32m32lf6_sdrc_params);
	omap_init_irq();
#ifdef CONFIG_OMAP_32K_TIMER
	omap2_gp_clockevent_set_gptimer(12);
#endif
}

static struct platform_device *omap3_beagle_devices[] __initdata = {
	&leds_gpio,
	&keys_gpio,
	&beagle_dss_device,
};

static void __init omap3beagle_flash_init(void)
{
	u8 cs = 0;
	u8 nandcs = GPMC_CS_NUM + 1;

	/* find out the chip-select on which NAND exists */
	while (cs < GPMC_CS_NUM) {
		u32 ret = 0;
		ret = gpmc_cs_read_reg(cs, GPMC_CS_CONFIG1);

		if ((ret & 0xC00) == 0x800) {
			printk(KERN_INFO "Found NAND on CS%d\n", cs);
			if (nandcs > GPMC_CS_NUM)
				nandcs = cs;
		}
		cs++;
	}

	if (nandcs > GPMC_CS_NUM) {
		printk(KERN_INFO "NAND: Unable to find configuration "
				 "in GPMC\n ");
		return;
	}

	if (nandcs < GPMC_CS_NUM) {
		omap3beagle_nand_data.cs = nandcs;

		printk(KERN_INFO "Registering NAND on CS%d\n", nandcs);
		if (gpmc_nand_init(&omap3beagle_nand_data) < 0)
			printk(KERN_ERR "Unable to register NAND device\n");
	}
}

static const struct ehci_hcd_omap_platform_data ehci_pdata __initconst = {

	.port_mode[0] = EHCI_HCD_OMAP_MODE_PHY,
	.port_mode[1] = EHCI_HCD_OMAP_MODE_PHY,
	.port_mode[2] = EHCI_HCD_OMAP_MODE_UNKNOWN,

	.phy_reset  = true,
	.reset_gpio_port[0]  = -EINVAL,
	.reset_gpio_port[1]  = 147,
	.reset_gpio_port[2]  = -EINVAL
};

#ifdef CONFIG_OMAP_MUX
static struct omap_board_mux board_mux[] __initdata = {
	{ .reg_offset = OMAP_MUX_TERMINATOR },
};
#endif

static struct omap_musb_board_data musb_board_data = {
	.interface_type		= MUSB_INTERFACE_ULPI,
#if defined(CONFIG_USB_MUSB_OTG)
	.mode			= MUSB_OTG,
#elif defined(CONFIG_USB_GADGET_MUSB_HDRC)
	.mode			= MUSB_PERIPHERAL,
#else
	.mode			= MUSB_HOST,
#endif
	.power			= 100,
};

static int __init expansionboard_setup(char *str)
{
	if (!str)
		return -EINVAL;
	strncpy(expansionboard_name, str, 16);
	printk(KERN_INFO "Beagle expansionboard: %s\n", expansionboard_name);
	return 0;
}

static void __init beagle_opp_init(void)
{
	int r = 0;

	/* Initialize the omap3 opp table */
	if (omap3_opp_init()) {
		pr_err("%s: opp default init failed\n", __func__);
		return;
	}

	/* Custom OPP enabled for XM */
	if (omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XM || omap3_beagle_get_rev() == OMAP3BEAGLE_BOARD_XMC) {
		struct omap_hwmod *mh = omap_hwmod_lookup("mpu");
		struct omap_hwmod *dh = omap_hwmod_lookup("iva");
		struct device *dev;

		if (!mh || !dh) {
			pr_err("%s: Aiee.. no mpu/dsp devices? %p %p\n",
				__func__, mh, dh);
			r = -EINVAL;
		} else {
			/* Enable MPU 1GHz and lower opps */
			dev = &mh->od->pdev.dev;
			r = opp_enable(dev, 800000000);
			r |= opp_enable(dev, 1000000000);

			/* Enable IVA 800MHz and lower opps */
			dev = &dh->od->pdev.dev;
			r |= opp_enable(dev, 660000000);
			r |= opp_enable(dev, 800000000);
		}
		if (r) {
			pr_err("%s: failed to enable higher opp %d\n",
				__func__, r);
			/*
			 * Cleanup - disable the higher freqs - we dont care
			 * about the results
			 */
			dev = &mh->od->pdev.dev;
			opp_disable(dev, 800000000);
			opp_disable(dev, 1000000000);
			dev = &dh->od->pdev.dev;
			opp_disable(dev, 660000000);
			opp_disable(dev, 800000000);
		} else {
			pr_err("%s: turbo OPPs enabled!\n", __func__);
		}
	}
}

static void __init omap3_beagle_init(void)
{
	omap3_mux_init(board_mux, OMAP_PACKAGE_CBB);
	omap3_beagle_init_rev();
	omap3_beagle_i2c_init();

	if (cpu_is_omap3630()) {
		gpio_buttons[0].gpio = 4;
	}

	platform_add_devices(omap3_beagle_devices,
			ARRAY_SIZE(omap3_beagle_devices));
	omap_serial_init();

	omap_mux_init_gpio(170, OMAP_PIN_INPUT);
	gpio_request(170, "DVI_nPD");
	/* REVISIT leave DVI powered down until it's needed ... */
	gpio_direction_output(170, true);

	if(!strcmp(expansionboard_name, "zippy"))
	{
		printk(KERN_INFO "Beagle expansionboard: initializing enc28j60\n");
		omap3beagle_enc28j60_init();
		printk(KERN_INFO "Beagle expansionboard: assigning GPIO 141 and 162 to MMC1\n");
		mmc[1].gpio_wp = 141;
		mmc[1].gpio_cd = 162;
	}
	
	if(!strcmp(expansionboard_name, "zippy2"))
	{
		printk(KERN_INFO "Beagle expansionboard: initializing ks_8851\n");
		omap3beagle_ks8851_init();
		printk(KERN_INFO "Beagle expansionboard: assigning GPIO 141 and 162 to MMC1\n");
		mmc[1].gpio_wp = 141;
		mmc[1].gpio_cd = 162;
	}

	if(!strcmp(expansionboard_name, "trainer"))
	{
		printk(KERN_INFO "Beagle expansionboard: exporting GPIOs 130-141,162 to userspace\n");
		gpio_request(130, "sysfs");
		gpio_export(130, 1);
		gpio_request(131, "sysfs");
		gpio_export(131, 1);
		gpio_request(132, "sysfs");
		gpio_export(132, 1);
		gpio_request(133, "sysfs");
		gpio_export(133, 1);
		gpio_request(134, "sysfs");
		gpio_export(134, 1);
		gpio_request(135, "sysfs");
		gpio_export(135, 1);
		gpio_request(136, "sysfs");
		gpio_export(136, 1);
		gpio_request(137, "sysfs");
		gpio_export(137, 1);
		gpio_request(138, "sysfs");
		gpio_export(138, 1);
		gpio_request(139, "sysfs");
		gpio_export(139, 1);
		gpio_request(140, "sysfs");
		gpio_export(140, 1);
		gpio_request(141, "sysfs");
		gpio_export(141, 1);
		gpio_request(162, "sysfs");
		gpio_export(162, 1);
	}

#if defined(CONFIG_WL1271) || defined(CONFIG_WL1271_MODULE)
	if(!strcmp(expansionboard_name, "bbtoys-wifi"))
	{
		if (wl12xx_set_platform_data(&omap_beagle_wlan_data))
			pr_err("error setting wl12xx data\n");
		printk(KERN_INFO "Beagle expansionboard: registering wl12xx platform device\n");
		platform_device_register(&omap_vwlan_device);
	}
#endif

	usb_musb_init(&musb_board_data);
	usb_ehci_init(&ehci_pdata);
	omap3beagle_flash_init();

	/* Ensure msecure is mux'd to be able to set the RTC. */
	omap_mux_init_signal("sys_drm_msecure", OMAP_PIN_OFF_OUTPUT_HIGH);

	/* Ensure SDRC pins are mux'd for self-refresh */
	omap_mux_init_signal("sdrc_cke0", OMAP_PIN_OUTPUT);
	omap_mux_init_signal("sdrc_cke1", OMAP_PIN_OUTPUT);

	beagle_display_init();
	beagle_opp_init();
}

early_param("buddy", expansionboard_setup);

MACHINE_START(OMAP3_BEAGLE, "OMAP3 Beagle Board")
	/* Maintainer: Syed Mohammed Khasim - http://beagleboard.org */
	.boot_params	= 0x80000100,
	.map_io		= omap3_map_io,
	.reserve	= omap_reserve,
	.init_irq	= omap3_beagle_init_irq,
	.init_machine	= omap3_beagle_init,
	.timer		= &omap_timer,
MACHINE_END
