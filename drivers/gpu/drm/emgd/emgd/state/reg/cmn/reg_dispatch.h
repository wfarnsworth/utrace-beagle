/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: reg_dispatch.h
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
 *  This is the implementation file for the register module's main API's called
 *  by external devices.
 *-----------------------------------------------------------------------------
 */

#ifndef _REG_DISPATCH_H
#define _REG_DISPATCH_H

#include <context.h>

typedef struct _reg_buffer {
	unsigned long flags;
	module_state_h mode_buffer;
	void *platform_buffer;
}reg_buffer_t;

/*
 * This needs to be available for inter-module use so that the
 * mode module can save state during it's init which happens after
 * the reg module init.
 */
typedef struct _reg_dispatch {
	reg_buffer_t *(*reg_alloc)(igd_context_t *context, unsigned long flags,
		void *_platform_context);
	void (*reg_free)(igd_context_t *context, reg_buffer_t *reg_set,
		void *_platform_context);
	int (*reg_save)(igd_context_t *context, reg_buffer_t *reg_set,
		void *_platform_context);
	int (*reg_restore)(igd_context_t *context, reg_buffer_t *reg_set,
		void *_platform_context);
	void *platform_context;
} reg_dispatch_t;

/*
 * Reg dispatch data structure is in reg.h because it and the reg context
 * needs to be available for initial reg save during mode module init.
 */


extern reg_dispatch_t reg_dispatch_plb;
extern reg_dispatch_t reg_dispatch_tnc;

#endif
