/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: dispatch_utils.h
 * $Revision: 1.4 $
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
 *  This file implements common macros that are used throughout the HAL
 *  for Device Dependent dispatching. This file is used in both the HAL and
 *  HAL helper libraries, as such it cannot include any HAL data structures
 *  that are not available to the helper libraries.
 *-----------------------------------------------------------------------------
 */

#ifndef _DISPATCH_UTILS_H_
#define _DISPATCH_UTILS_H_

#include <config.h>
#include <intelpci.h>

typedef struct _dispatch_table {
	unsigned long did;
	void *table;
}dispatch_table_t;

static __inline void *dispatch_acquire(
	unsigned long did,
	dispatch_table_t *list)
{
	dispatch_table_t *curr = list;

	while(curr->did != 0) {
		if(curr->did == did) {
			return curr->table;
		}
		curr++;
	}
	return curr->table;
}


#ifdef CONFIG_PLB
#define DISPATCH_PLB(p) {PCI_DEVICE_ID_VGA_PLB, p},
#else
#define DISPATCH_PLB(p)
#endif
#ifdef CONFIG_TNC
#define DISPATCH_TNC(p) {PCI_DEVICE_ID_VGA_TNC, p},
#define DISPATCH_TNC_A0(p) {PCI_DEVICE_ID_VGA_TNC_A0, p},
#define DISPATCH_LNC(p) {PCI_DEVICE_ID_VGA_LNC, p},
#else
#define DISPATCH_TNC(p)
#define DISPATCH_TNC_A0(p)
#define DISPATCH_LNC(p)
#endif
#define DISPATCH_END {0, NULL}

#endif
