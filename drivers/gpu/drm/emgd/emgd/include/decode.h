/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: decode.h
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
 *  This is the internal header file for the video decode module.
 *-----------------------------------------------------------------------------
 */


#ifndef _IGD_DECODE_H
#define _IGD_DECODE_H

#include <igd_render.h>  /* For surface definition */

#define IGD_VD_MAX_SURFACES 2048

#define VID_SURFACE(ctx, id) \
	(((ctx->context_info.surfmap == NULL) ? &surface_list[id] : &surface_list[ctx->context_info.surfmap->slist_index[id]]))

typedef struct _igd_vd_surfmap_table {
	int active_entries;
	int total_surfaces;
	int *slist_index;
} igd_vd_surfmap_table_t;

typedef struct _igd_vd_surface_list {
	int allocated;
	igd_surface_t *surface;
	int chroma_offset;
	int stride_mode;
    /* Used to store driver private data, e.g. decoder specific intermediate status data
     * extra_info[0-3]: used for decode
     * extra_info[4]: surface fourcc
     * extra_info[5]: surface skippeded or not for encode
     */
	int extra_info[6];
	igd_region_t buf;
	igd_vd_surfmap_table_t* surfmap;
} igd_vd_surface_list_t;

struct _igd_video_context {
	igd_vp_name_t profile;
	igd_ve_name_t entrypoint;
	igd_vd_surface_list_t *current_render_target;
	igd_vd_surfmap_table_t *surfmap;

	/*
	 * The actual hardware/profile context is much larger. The above
	 * members are device indpendent.
	 */
};

#endif /*_IGD_DECODE_H*/
