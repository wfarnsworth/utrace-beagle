/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: ovl2_tnc.h
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
 *  This is the internal header file for napa overlay engine. It should be not be 
 *  by any other module besides the overlay module itself. It contains the
 *  neccessary hardware virtualized structures and functions internal to 
 *  the napa core's overlay engine
 *-----------------------------------------------------------------------------
 */
#ifndef _OVL2_TNC_H
#define _OVL2_TNC_H
extern int blend2_surf_needed_tnc(igd_display_context_t *display,
	igd_surface_t       *src_surf,
	igd_rect_t          *src_rect,
	igd_rect_t          *dest_rect,
	unsigned int         flags,
	igd_surface_t       *blend_surf,
	igd_rect_t          *blend_rect);
extern int alter_ovl2_tnc(igd_display_context_t *display,
	igd_surface_t       *src_surf,
	igd_rect_t          *src_rect,
	igd_rect_t          *dest_rect,
	igd_ovl_info_t      *ovl_info,
	unsigned int         flags);
extern int query_ovl2_tnc(igd_display_h display_h,
	unsigned int flags);
extern int query_max_size_ovl2_tnc(igd_display_h display_h,
	unsigned long pf,
	unsigned int *max_width,
	unsigned int *max_height);
#endif /* _OVL2_NAP_H */
