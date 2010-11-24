/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: init_dispatch.h
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
 *  
 *-----------------------------------------------------------------------------
 */

#ifndef _INIT_DISPATCH_H
#define _INIT_DISPATCH_H

#include <pci.h>

#include <dispatch.h>

/*
 * Note: Platforms extend this data structure so the pointer can be used
 * as either this DI dispatch or cast to the DD dipatch.
 */
typedef struct _init_dispatch {
	char *name;
	char *chipset;
	char *default_pd_list;
	int (*query)(igd_context_t *context, struct _init_dispatch *dispatch,
		os_pci_dev_t vga_dev, unsigned int *bus, unsigned int *slot,
		unsigned int *func);
	int (*config)(igd_context_t *context, struct _init_dispatch *dispatch);
	int (*set_param)(igd_context_t *context, unsigned long id,
		unsigned long value);
	int (*get_param)(igd_context_t *context, unsigned long id,
		unsigned long *value);
	void (*shutdown)(igd_context_t *context);
} init_dispatch_t;

extern init_dispatch_t init_dispatch_plb;
extern init_dispatch_t init_dispatch_tnc;
extern init_dispatch_t init_dispatch_tnc_a0;
extern init_dispatch_t init_dispatch_lnc;

#endif
