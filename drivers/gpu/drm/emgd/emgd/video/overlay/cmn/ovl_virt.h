/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: ovl_virt.h
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
 *  This is the internal header file for overlay. It should be not be
 *  by any other module besides the overlay module itself. It contains the
 *  neccessary hardware virtualized structures and functions internal to
 *  overlay
 *-----------------------------------------------------------------------------
 */

#ifndef _OVL_VIRT_H
#define _OVL_VIRT_H

/* None of the IALs use the OVL_SUPPORT_*.  Exclude it for now. */
/* None of the IALs use the OVL_RULE_MUST_*.  Exclude it for now. */

/* Overlay HW range of values for color control and gamma correction*/
#define OVL_HW_DEF_BRIGHT      750L
#define OVL_HW_MIN_BRIGHT      0L
#define OVL_HW_MAX_BRIGHT      10000L

#define OVL_HW_DEF_CONT	    10000L
#define OVL_HW_MIN_CONT	    0L
#define OVL_HW_MAX_CONT	    20000L

#define OVL_HW_DEF_SAT	        10000L
#define OVL_HW_MIN_SAT		    0L
#define OVL_HW_MAX_SAT	        20000L

#define OVL_HW_DEF_HUE			0L
#define OVL_HW_MIN_HUE			-180L
#define OVL_MHW_AX_HUE			180L

#define OVL_HW_DEF_GAMMA       1L
#define OVL_HW_MAX_GAMMA       500L
#define OVL_HW_MIN_GAMMA       1L

enum {
	OVL_STATE_OFF = 0,
	OVL_STATE_ON,
};

#define OVL_PRIMARY   0
#define OVL_SECONDARY 1
#define OVL_MAX_HW    2  /* Maximum number of overlays */

/* Define the maximum number of blend surfaces which can be used */
#define MAX_BLEND_SURF 2

typedef struct _ovl_context{
	ovl_dispatch_t (*dispatch)[];  /* Pointer to an array */
	unsigned int  state;
	unsigned long reg_update_offset;
	unsigned long reg_update_phys;
	unsigned long sync;
	unsigned long sync2;
	unsigned int blend_surf_num[OVL_MAX_HW];
	igd_surface_t blend_surf[OVL_MAX_HW][MAX_BLEND_SURF];
	unsigned int ovl_buff;
	unsigned int fb_blend_ovl;
	unsigned short reg_allocated;
} ovl_context_t;

extern ovl_context_t ovl_context[];

#endif /*_OVL_VIRT_H*/
