/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_appcontext.h
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
 *  This is an IGD exported header file for the client context Module.
 *  This module includes tools for maintaining device state including
 *  hardware context allocation.
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_APPCONTEXT_H
#define _IGD_APPCONTEXT_H

typedef void *igd_appcontext_h;

#define IGD_CONTEXT_STATE_2D     0x00000001
#define IGD_CONTEXT_STATE_3D     0x00000002
#define IGD_CONTEXT_STATE_VD     0x00000004

/*----------------------------------------------------------------------
 * Function:
 *  igd_appcontext_h dispatch->appcontext_alloc(igd_display_h display_handle,
 *    int priority,
 *    unsigned int flags);
 *
 * Description:
 *
 * Parameters:
 *
 * Returns:
 *----------------------------------------------------------------------
 */

/*----------------------------------------------------------------------
 * Function:
 *  void dispatch->appcontext_free(igd_display_h display_handle,
 *    int priority,
 *    igd_appcontext_h context_handle);
 *
 * Description:
 *
 * Parameters:
 *
 * Returns:
 *----------------------------------------------------------------------
 */


#endif

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: igd_appcontext.h,v 1.3 2010/07/23 16:54:51 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/include/igd_appcontext.h,v $
 *----------------------------------------------------------------------------
 */
