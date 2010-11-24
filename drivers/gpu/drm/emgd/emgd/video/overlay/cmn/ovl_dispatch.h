/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: ovl_dispatch.h
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
 *  
 *-----------------------------------------------------------------------------
 */

#ifndef _OVERLAY_DISPATCH_H
#define _OVERLAY_DISPATCH_H

typedef struct _ovl_dispatch {
	int (*blend_surf_needed)(igd_display_context_t *display,
		igd_surface_t       *src_surf,
		igd_rect_t          *src_rect,
		igd_rect_t          *dest_rect,
		unsigned int         flags,
		igd_surface_t       *blend_surf,
		igd_rect_t          *blend_rect);
	int (*alter_ovl)(igd_display_context_t *display,
		igd_surface_t       *src_surf,
		igd_rect_t          *src_rect,
		igd_rect_t          *dest_rect,
		igd_ovl_info_t      *ovl_info,
		unsigned int         flags);
	int (*query_ovl)(igd_display_h display_h,
		unsigned int flags);
	int (*query_max_size_ovl)(igd_display_h display_h,
		unsigned long pf,
		unsigned int *max_width,
		unsigned int *max_height);
} ovl_dispatch_t;

#endif
