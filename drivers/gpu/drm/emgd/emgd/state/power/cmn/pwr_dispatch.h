/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: pwr_dispatch.h
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
 *  This file contains the protocols for the plaform-specific dispatch
 *  functions that the power module uses.
 *-----------------------------------------------------------------------------
 */

#ifndef _PWR_DISPATCH_H
#define _PWR_DISPATCH_H

#include <context.h>

typedef struct _pwr_dispatch {
	/* Queries support for power_state
	 * ret:  0 if power_state is supported, <0 otherwise
	 */
	int (*pwr_query)(unsigned int power_state);
	/* Dispatch function to set device dependent part of set power */
	int (*pwr_set)(igd_context_t *context, unsigned int power_state);
	/* Dispatch function to set init time device dependent power settings */
	int (*pwr_init)(igd_context_t *context);
} pwr_dispatch_t;

extern pwr_dispatch_t pwr_dispatch_plb;

#endif

/*-----------------------------------------------------------------------------
 * $Id: pwr_dispatch.h,v 1.4 2010/07/23 16:54:50 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/state/power/cmn/pwr_dispatch.h,v $
 *-----------------------------------------------------------------------------
 */
