/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: mode_access.h
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
 *  Contains functional support to set video mode
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_MODEACCESS_H
#define _IGD_MODEACCESS_H

#include <mode.h>
#include <context.h>

extern int mode_getresolution(igd_display_h display_h,
	unsigned long *width,
	unsigned long *height);

/*
 * The power state for the display is the lower(power) of the display
 * state and the device state. A larger power_state number means a
 * lower power state.
 */
#define GET_DISPLAY_POWER_STATE(d_h, pn) \
(GET_DEVICE_POWER_STATE(d_h) > ((PORT(d_h, pn))->power_state) ? \
GET_DEVICE_POWER_STATE(d_h) : ((PORT(d_h, pn))->power_state))

#endif /* _IGD_MODEACCESS_H */

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: mode_access.h,v 1.3 2010/07/23 16:54:50 bpaauwe Exp $
 *
 *----------------------------------------------------------------------------
 */
