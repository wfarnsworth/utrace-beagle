/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: intelpci.h
 * $Revision: 1.6 $
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
 *  Contains PCI bus transaction definitions
 *-----------------------------------------------------------------------------
 */

/* PCI */
#define PCI_VENDOR_ID_INTEL             0x8086


/* PLB Family Chips */
#define PCI_DEVICE_ID_BRIDGE_PLB        0x8100
#define PCI_DEVICE_ID_VGA_PLB           0x8108

/* Atom E6xx */
#define PCI_DEVICE_ID_BRIDGE_TNC        0x4114
#define PCI_DEVICE_ID_VGA_TNC           0x4108

/* Atom E6xx ULP */
#define PCI_DEVICE_ID_BRIDGE_TNC_ULP    0x4115

/* Atom E6xx Device 3 */
#define PCI_DEVICE_ID_SDVO_TNC 	        0x8182

/* Atom E6xx Device 31 (LPC) */
#define PCI_DEVICE_ID_LPC_TNC 	        0x8186

/* Support for MSRT and Pre-Release PCI ID for Atom E6xx 
 * Can be removed in future */
#if 0
/* Atom E6xx A0 Stepping */
#define PCI_DEVICE_ID_BRIDGE_TNC_A0     0x4110
#define PCI_DEVICE_ID_VGA_TNC_A0        0x4100

/* Moorestown */
#define PCI_DEVICE_ID_BRIDGE_LNC        0x4110
#define PCI_DEVICE_ID_VGA_LNC           0x4102
#endif

/* Start: Southbridge specific */
#define PCI_DEVICE_ID_LPC_82801AA       0x2410
#define PCI_DEVICE_ID_LPC_82801AB       0x2420
#define PCI_DEVICE_ID_LPC_82801BA       0x2440
#define PCI_DEVICE_ID_LPC_82801BAM      0x244c
#define PCI_DEVICE_ID_LPC_82801E        0x2450
#define PCI_DEVICE_ID_LPC_82801CA       0x2480
#define PCI_DEVICE_ID_LPC_82801DB       0x24c0
#define PCI_DEVICE_ID_LPC_82801DBM      0x24cc
#define PCI_DEVICE_ID_LPC_82801EB       0x24d0
#define PCI_DEVICE_ID_LPC_82801EBM      0x24dc
#define PCI_DEVICE_ID_LPC_80001ESB      0x25a1  /* LPC on HanceRapids ICH */
#define PCI_DEVICE_ID_LPC_82801FB       0x2640  /* ICH6/ICH6R */
#define PCI_DEVICE_ID_LPC_82801FBM      0x2641  /* ICH6M/ICH6MR */
#define PCI_DEVICE_ID_LPC_82801FW       0x2642  /* ICH6W/ICH6WR */
#define PCI_DEVICE_ID_LPC_82801FWM      0x2643  /* ICH6MW/ICH6MWR */
#define PCI_DEVICE_ID_LPC_Q35DES        0x2910  /* ICH9 */
#define PCI_DEVICE_ID_LPC_Q35DHES       0x2912  /* ICH9 */
#define PCI_DEVICE_ID_LPC_Q35DOES       0x2914  /* ICH9 */
#define PCI_DEVICE_ID_LPC_Q35RES        0x2916  /* ICH9 */
#define PCI_DEVICE_ID_LPC_Q35BES        0x2918  /* ICH9 */



#define INTEL_PTE_ALLIGNMENT                0xFFFFF000

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: intelpci.h,v 1.6 2010/09/20 17:26:48 astead Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/include/intelpci.h,v $
 *----------------------------------------------------------------------------
 */
