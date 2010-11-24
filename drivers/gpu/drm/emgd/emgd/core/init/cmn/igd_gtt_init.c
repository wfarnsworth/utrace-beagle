/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_gtt_init.c
 * $Revision: 1.3 $
 *-----------------------------------------------------------------------------
 * Copyright © 2002-2010, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *-----------------------------------------------------------------------------
 * Description:
 *  Initialize the GTT
 *-----------------------------------------------------------------------------
 */
#include <igd_debug.h>
#include <igd_init.h>
#include <drmP.h>
#include <io.h>
#include <memory.h>
#include <context.h>
#include <asm/cacheflush.h>

#define PFX "EMGD: "

#define SCR1	0x71410 /* scratch register set by vbios indicating status*/
#define SCR2	0x71418 /* scratch register set by vbios indicating amount of stolen memory */
#define FW_ID	0xE1DF0000 /* firmware identifier */
#define ST_BIT	0x00000004 /* bit2- stolen memory bit */
#define PSB_GMCH_CTRL       0x52
#define PSB_GMCH_ENABLED    0x04
#define PSB_PGETBL_CTL      0x00002020
#define PSB_PGETBL_ENABLED  0x00000001
#define PSB_GATT_RESOURCE   2
#define PSB_GTT_RESOURCE    3
#define PSB_BSM             0x5c
#define PSB_PTE_VALID       0x0001


/*
 * GTT shutdown.
 *
 * Unmap the GTT mapping that was done during init time.
 */
void igd_gtt_shutdown(igd_context_t *context)
{
	if (context->device_context.virt_gttadr) {
		iounmap(context->device_context.virt_gttadr);

		context->device_context.virt_gttadr = NULL;
	}
}


/*
 * Initialize the GTT.
 *   - Find the size of stolen memory
 *   - Add stolen memory to the GTT
 *   - Map the GTT and video memory
 */

void igd_gtt_init(igd_context_t *context)
{
	struct drm_device *dev;
	unsigned char *mmio = context->device_context.virt_mmadr;
	unsigned long dvmt_mode = 0;
	unsigned long gtt_pages = 0;
	unsigned long stolen_mem_size = 0;
	unsigned long scratch;
	unsigned long base;
	unsigned long pte;
	unsigned short gmch_ctl;
	unsigned long pge_ctl;
	unsigned long gtt_phys_start;
	unsigned long gatt_start;
	unsigned long gatt_pages;
	unsigned long gtt_start;
	unsigned long gtt_order;
	unsigned long stolen_mem_base;
	unsigned long *gtt_table;
	int gtt_enabled = FALSE;
	struct page *gtt_table_page;
	int i;

	dev = (struct drm_device *)context->drm_dev;

	/* Enable the GMCH */
	OS_PCI_READ_CONFIG_16((os_pci_dev_t)dev->pdev, PSB_GMCH_CTRL,
			&gmch_ctl);
	OS_PCI_WRITE_CONFIG_16((os_pci_dev_t)dev->pdev, PSB_GMCH_CTRL,
			(gmch_ctl | PSB_GMCH_ENABLED));
	context->device_context.gmch_ctl = gmch_ctl;

	/* Get the page table control register */
	pge_ctl = readl(mmio + PSB_PGETBL_CTL);
	gtt_phys_start = pge_ctl & PAGE_MASK; 

	gtt_enabled = pge_ctl & PSB_PGETBL_ENABLED;
	
	/* Create a scratch page to initialize empty GTT entries */
	context->device_context.scratch_page = alloc_page(GFP_DMA32 | __GFP_ZERO);

	/*
	* Is pci_resource_start(dev->pdev, PSB_GATT_RESOURCE); the same
	* as pci_read_config_dword(dev->pdev, 0x1C, &value)?
	*
	* PSB_GATT_RESOURCE length is the amount of memory addressable
	* by the GTT table.
	*/
	gatt_start = pci_resource_start(dev->pdev, PSB_GATT_RESOURCE);
	gatt_pages = (pci_resource_len(dev->pdev, PSB_GATT_RESOURCE) >> PAGE_SHIFT);
	context->device_context.gatt_pages = gatt_pages;

	/*
	 * The GTT wasn't set up by the vBios  
	 */
	if (!gtt_enabled) {
		context->device_context.stolen_pages = 0;

		gtt_pages = pci_resource_len(dev->pdev, PSB_GTT_RESOURCE) >> PAGE_SHIFT;
		gtt_order = get_order(gtt_pages << PAGE_SHIFT);
		gtt_table = (unsigned long *)__get_free_pages(GFP_KERNEL, gtt_order);
		/* Make sure allocation was successful */
		if (NULL == gtt_table) {
			EMGD_ERROR("Failed to allocate kernel pages for GTT");
			return;
		}
		context->device_context.virt_gttadr = gtt_table;

		for (i=0; i < (1 << gtt_order); i++) {
			gtt_table_page = virt_to_page(gtt_table + (PAGE_SIZE * i));
			EMGD_DEBUG("Setting reserved bit on %p", gtt_table_page);
			set_bit(PG_reserved, &gtt_table_page->flags);
		}

		gtt_phys_start = virt_to_phys(gtt_table);

		for (i = 0; i < gtt_pages; i++) {
			gtt_table[i] = (unsigned long)context->device_context.scratch_page;
		}

		printk(KERN_INFO "Detected GTT was not enabled by firmware");
		printk(KERN_INFO "GMMADR(region 0) start: 0x%08lx (%ldM).\n",
			gatt_start, (gatt_pages / 256));
		printk(KERN_INFO "GTTADR(region 3) start: 0x%08lx (can map %ldM RAM), and "
			"actual RAM base 0x%08lx.\n",
			(unsigned long)gtt_table, (gtt_pages * 4), gtt_phys_start);

		/* Enable the newly created GTT */
		EMGD_DEBUG("Enabling new GTT");
		writel((gtt_phys_start|PSB_PGETBL_ENABLED), mmio + PSB_PGETBL_CTL);
		pge_ctl = readl(mmio + PSB_PGETBL_CTL);

	} else {

		/*
		 * Get the start address of the GTT page table
		 *
		 * In full_config_vga, this is done differently.  The address is read
		 * from pcidev0's pci config space, at TNC_PCI_GTTADR and the size comes
		 * from TNC_OFFSET_VGA_MSAC. The value read for size is a size id
		 *    1 = 128, 2 = 256, 3 = 512
		 * emgd_gtt->gtt_start = OS_PCI_READ_CONFIG_32(
		 *            context->platform_context->pcidev0, TNC_PCI_GTTADDR)
		 * gtt_pages = OS_PCI_READ_CONFIG_8(context->platform_context->pcidev0,
		 *            TNC_OFFSET_VGA_MSAC) * 1024;
		 *
		 * PSB_GTT_RESOURCE length is the size of the GTT table. Thus,
		 * gtt_pages is the number of pages that make up the table.
		 */
		gtt_start = pci_resource_start(dev->pdev, PSB_GTT_RESOURCE);
		gtt_pages = (pci_resource_len(dev->pdev, PSB_GTT_RESOURCE) >> PAGE_SHIFT);
	
		/* Get stolen memory configuration. */
		pci_read_config_dword(dev->pdev, PSB_BSM, (u32 *)&stolen_mem_base);
		stolen_mem_size = gtt_phys_start - stolen_mem_base - PAGE_SIZE;

		/* Display useful information in the kernel log */
		printk(KERN_INFO "GMMADR(region 0) start: 0x%08lx (%ldM).\n",
				gatt_start, (gatt_pages / 256));
		printk(KERN_INFO "GTTADR(region 3) start: 0x%08lx (can map %ldM RAM), and "
				"actual RAM base 0x%08lx.\n",
				gtt_start, (gtt_pages * 4), gtt_phys_start);
		printk(KERN_INFO "Stolen memory information \n");
		printk(KERN_INFO "       base in RAM: 0x%lx \n", stolen_mem_base);
		printk(KERN_INFO "       size: %luK, calculated by (GTT RAM base) - "
				"(Stolen base)\n", (stolen_mem_size / 1024));
		dvmt_mode = (gmch_ctl >> 4) & 0x7;
		printk(KERN_INFO "       size: %dM (dvmt mode=%ld)\n",
				(dvmt_mode == 1) ? 1 : (2 << (dvmt_mode - 1)), dvmt_mode);

		context->device_context.virt_gttadr =
		ioremap_nocache(gtt_start, gtt_pages << PAGE_SHIFT);

		if (!context->device_context.virt_gttadr) {
			printk(KERN_ERR "Failed to map the GTT.\n");
			/* TODO: Clean up somelthing here */
			return;
		}

		/* Insert stolen memory pages into the beginning of GTT */
		base = stolen_mem_base >> PAGE_SHIFT;
		context->device_context.stolen_pages = stolen_mem_size >> PAGE_SHIFT;

		printk(KERN_INFO "Set up %ld stolen pages starting at 0x%08lx, "
			"GTT offset %dK\n", context->device_context.stolen_pages, base, 0);

		for (i = 0; i < context->device_context.stolen_pages; i++) {
			pte = ((base + i) << PAGE_SHIFT) | PSB_PTE_VALID;
			writel(pte, context->device_context.virt_gttadr + i);
		}

	} 

	/* Update the scratch registers to say we have no stolen memory */
	scratch = readl(mmio + SCR1);
	if ((scratch & FW_ID) == FW_ID) {
		/* if an EMGD vBios modify only the stolen memory bit */
		scratch |= ST_BIT;
		writel(scratch, mmio + SCR1);
	} else {
		/* Not an EMGD vBios so just set the entire register to a known value */
		writel((FW_ID|ST_BIT), mmio + SCR1);
	}

	/*
	 * Report back that there is 0MB of stolen memory regardless of
	 * what was really in there.  Fresh pages will be inserted over
	 * the top of the existing stolen memory.
	 */
	writel(0, mmio + SCR2);

	/*
	 * FIXME: Shouldn't this fill in all the GTT page table entries with
	 * the scratch page?
	 */

	return;
}
