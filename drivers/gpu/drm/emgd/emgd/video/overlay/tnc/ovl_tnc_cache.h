/* -*- pse-c -*-
 *----------------------------------------------------------------------------
 * Filename: ovl_tnc_cache.h
 * $Revision: 1.2 $
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
 *-----------------------------------------------------------------------------
 * Description:
 *  This is the internal header file for overlay caching. It should be not be
 *  by any other module besides the overlay module itself.
 *-----------------------------------------------------------------------------
 */
#ifndef _OVL_TNC_CACHE_H
#define _OVL_TNC_CACHE_H

#include <rb.h>
#include "ovl_regs_tnc.h"
#include "ovl2_regs_tnc.h"

/* Turns the overlay cache on and off. */
#define OVL_TNC_CACHE_QUICK_SWAP


/*
 * In order to cache the overlay registers we need a structure
 * that defines and wraps them.  We already have one for the primary
 * display, called ovl_reg_image_tnc_t.
 * Here we define a structure for the secondary display
 */

typedef struct _ovl2_reg_tnc_cache{
	unsigned long control;
	unsigned long start;
	unsigned long plane_control;
	unsigned long plane_start;
	unsigned long linear_offset;
	unsigned long tiled_offset;

	unsigned long pitch;
	unsigned long dest_rect_x1y1;
	unsigned long dest_rect_w_h;
	unsigned long cont_bright;
	unsigned long satn_hue;
	unsigned long gamma_regs[OVL2_TOTAL_GAMMA_REG];
	unsigned long colorkey_hw;
	unsigned long colorkey_mask;
	unsigned long ckey_high;
	unsigned long ckey_low;
	unsigned long ckey_enable;
} ovl2_reg_tnc_cache_t;

#define MMIO_OFFSET_TNC2_CONTROL        0x72180
#define MMIO_OFFSET_TNC2_LINEAR_OFF     0x72184
#define MMIO_OFFSET_TNC2_PITCH          0x72188
#define MMIO_OFFSET_TNC2_DEST_RECT_X1Y1 0x7218C
#define MMIO_OFFSET_TNC2_DEST_RECT_W_H  0x72190
#define MMIO_OFFSET_TNC2_CKEY_LOW       0x72194
#define MMIO_OFFSET_TNC2_CKEY_ENABLE    0x72198
#define MMIO_OFFSET_TNC2_SURF_ADDR      0x7219C
#define MMIO_OFFSET_TNC2_CKEY_HIGH      0x721A0
#define MMIO_OFFSET_TNC2_DSPC_TILE_OFF  0x721A4
#define MMIO_OFFSET_TNC2_CONT_BRIGHT    0x721D0
#define MMIO_OFFSET_TNC2_SATN_HUE       0x721D4
#define MMIO_OFFSET_TNC2_COLORKEY_HW    0x14
#define MMIO_OFFSET_TNC2_COLORKEY_MASK  0x18

/*
 * This stucture caches the overlay state, so we don't have to
 * re-program everything for every single frame
 */
typedef struct _ovl_tnc_cache {
	igd_surface_t        src_surf;
	igd_rect_t           src_rect;
	igd_rect_t           dest_rect;
	igd_ovl_info_t       ovl_info;
	unsigned long        flags;
	ovl_reg_image_tnc_t  ovl_regs;
	ovl2_reg_tnc_cache_t ovl2_regs;
} ovl_tnc_cache_t, *povl_tnc_cache_t;


/* Flags for things that might have changed in the cache */
#define IGD_OVL_TNC_UPDATE_DEST     (1 << 0)
#define IGD_OVL_TNC_UPDATE_SRC      (1 << 1)
#define IGD_OVL_TNC_UPDATE_SURF     (1 << 2)
#define IGD_OVL_TNC_UPDATE_INFO     (1 << 3)
#define IGD_OVL_TNC_UPDATE_FLAGS    (1 << 4)
#define IGD_OVL_TNC_UPDATE_VQ       (1 << 5)
#define IGD_OVL_TNC_UPDATE_GAMMA    (1 << 6)
#define IGD_OVL_TNC_UPDATE_COLORKEY (1 << 7)


/*
 * Caching helper functions.  Implemented in ovl_tnc.c, but used by
 * the ovl2 and micro_ovl modules as well.
 */

/* Tells if a rectangle has changed */
int is_changed_rect(igd_rect_t *old_rect, igd_rect_t *new_rect);

/* Tells if a surface has changed */
int is_changed_surf(igd_surface_t *old_surf, igd_surface_t *new_surf);

/* Tells if the color key has changed */
int is_changed_color_key(igd_ovl_info_t *old_info, igd_ovl_info_t *new_info);

/* Tells if the video quality has changed */
int is_changed_vq(igd_ovl_info_t *old_info, igd_ovl_info_t *new_info);

/* Tells if the gamma has changed */
int is_changed_gamma(igd_ovl_info_t *old_info, igd_ovl_info_t *new_info);

/* Copies a source rectangle to the cache */
void copy_src_rect_tnc(igd_rect_t *src_rect, povl_tnc_cache_t ovl_cache);

/* Copies a dest rectangle to the cache */
void copy_dest_rect_tnc( igd_rect_t *dest_rect, povl_tnc_cache_t ovl_cache);

/* Copies a surface to the cache */
void copy_surf_tnc(igd_surface_t *src_surf, povl_tnc_cache_t ovl_cache);

/* Copies the color key to the cache */
void copy_color_key_tnc( igd_ovl_info_t *ovl_info, povl_tnc_cache_t ovl_cache);

/* Copies the video quality info to the cache */
void copy_vq_tnc(igd_ovl_info_t *ovl_info, povl_tnc_cache_t ovl_cache);

/* Copies the gamma to the cache */
void copy_gamma_tnc(igd_ovl_info_t *ovl_info, povl_tnc_cache_t ovl_cache);

/* Checks to see what, if anything has changed.
 * Clears bits in the command and config register that are invalid.
 * Returns a set of flags telling what changed */
unsigned int get_cache_changes_tnc(
	igd_surface_t  *src_surf,
	igd_rect_t     *src_rect,
	igd_rect_t     *dest_rect,
	igd_ovl_info_t *ovl_info,
	unsigned int    flags,
	povl_tnc_cache_t ovl_cache);



#endif /* _OVL_TNC_CACHE_H */
