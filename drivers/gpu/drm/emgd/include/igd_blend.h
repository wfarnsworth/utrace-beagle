/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_blend.h
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
 *  This is a header file for the Intel GFX commands.
 *  This includes commands specific to Intel hardware and structures specific
 *  to Intel hardware.  All other commands and structures are available
 *  through GFX.
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_BLEND_H
#define _IGD_BLEND_H

#include <igd_render.h>

/* These flags must not conflict with the IGD_RENDER flags in igd_render.h */
#define IGD_FILTER_MASK             0x00000300
#define IGD_FILTER_NEAREST          0x00000000
#define IGD_FILTER_BILINEAR         0x00000100
#define IGD_FILTER_ANISOTROPIC      0x00000200
#define IGD_FILTER_4X4              0x00000300
/* Indicates multiple blends will be sent in a row and this is not the
 * last blend. */
#define IGD_BLEND_NO_FLUSH          0x00000800

/*----------------------------------------------------------------------
 * Function:
 *  int dispatch->blend(igd_display_h display_handle,
 *    int priority,
 *    igd_appcontext_h appcontext,
 *    unsigned int num_src,
 *    igd_surface_t **src_surface_list,
 *    igd_rect_t **src_rect_list,
 *    igd_rect_t **dest_rect_list,
 *    igd_surface_t *dest_surface,
 *    igd_rect_t *clip_rect,
 *    unsigned long flags);
 *
 * Description:
 *
 * Parameters:
 *
 *  flags: Flags are defined in igd_render.h
 *
 * Returns:
 *----------------------------------------------------------------------
 */

#endif /* _IGD_BLEND_H */

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: igd_blend.h,v 1.3 2010/07/23 16:54:51 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/include/igd_blend.h,v $
 *----------------------------------------------------------------------------
 */
