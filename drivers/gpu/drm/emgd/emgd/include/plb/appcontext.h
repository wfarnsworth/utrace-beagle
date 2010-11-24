/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: appcontext.h
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
 *  This is the inter-module header file for the client context module.
 *  It contains data structures needed for modules to use and manipulate 
 *  the device state including hardware context switching.
 *-----------------------------------------------------------------------------
 */

#ifndef _APPCONTEXT_PLB_H
#define _APPCONTEXT_PLB_H

#include <context.h>
#include <igd_mode.h>

/*
 * This data structure contains a copy of all needed state variables and
 * the logical context used by hardware for context switching. An IGD
 * client driver can allocate a client context for each client or allocate
 * just one to be shared by all clients.
 */
/*
 * TODO:
 * Add or modify the struct and other definitions for Poulsbo
 */
typedef struct _appcontext {
	void *state3d;
	void *state2d;
	unsigned char *hw_context_virt;
	unsigned long hw_context_phys;
	unsigned long hw_context_offset;
}appcontext_t, appcontext_plb_t;

int appcontext_set_plb(igd_display_h display,
	int priority,
	appcontext_t *context,
	int extstate_save_enable,
	int extstate_restore_enable,
	int force_restore,
	int restore_inhibit);


#endif
