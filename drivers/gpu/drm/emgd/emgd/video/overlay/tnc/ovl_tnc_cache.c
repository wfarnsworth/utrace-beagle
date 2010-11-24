/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: ovl_tnc_cache.c
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
 *  Support functions for overlay caching.
 *-----------------------------------------------------------------------------
 */
#define MODULE_NAME hal.overlay

#include "ovl_tnc_cache.h"


/* Copies a source rectangle to the cache */
void copy_src_rect_tnc(igd_rect_t *src_rect, povl_tnc_cache_t ovl_cache)
{
	if (src_rect) {
		OS_MEMCPY(&ovl_cache->src_rect,
			  src_rect,
			  sizeof(igd_rect_t));
	} else {
		OS_MEMSET(&ovl_cache->src_rect,
			  0,
			  sizeof(igd_rect_t));
	}
}


/* Copies a dest rectangle to the cache */
void copy_dest_rect_tnc( igd_rect_t *dest_rect, povl_tnc_cache_t ovl_cache)
{
	if (dest_rect) {
		OS_MEMCPY(&ovl_cache->dest_rect,
			  dest_rect,
			  sizeof(igd_rect_t));
	} else {
		OS_MEMSET(&ovl_cache->dest_rect,
			  0,
			  sizeof(igd_rect_t));
	}
}


/* Copies a surface to the cache */
void copy_surf_tnc(igd_surface_t *src_surf, povl_tnc_cache_t ovl_cache)
{
	if (src_surf) {
		OS_MEMCPY(&ovl_cache->src_surf,
			  src_surf,
			  sizeof(igd_surface_t));
	} else {
		OS_MEMSET(&ovl_cache->src_surf,
			  0,
			  sizeof(igd_surface_t));
	}
}


/* Copies the color key to the cache */
void copy_color_key_tnc( igd_ovl_info_t *ovl_info, povl_tnc_cache_t ovl_cache)
{
	if (ovl_info) {
		OS_MEMCPY(&ovl_cache->ovl_info.color_key,
			  &(ovl_info->color_key),
			  sizeof(igd_ovl_color_key_info_t));
	} else {
		OS_MEMSET(&ovl_cache->ovl_info.color_key,
			  0,
			  sizeof(igd_ovl_color_key_info_t));
	}
}


/* Copies the video quality info to the cache */
void copy_vq_tnc(igd_ovl_info_t *ovl_info, povl_tnc_cache_t ovl_cache)
{
	if (ovl_info) {
		OS_MEMCPY(&ovl_cache->ovl_info.video_quality,
			  &(ovl_info->video_quality),
			  sizeof(igd_ovl_video_quality_info_t));
	} else {
		OS_MEMSET(&ovl_cache->ovl_info.video_quality,
			  0,
			  sizeof(igd_ovl_video_quality_info_t));
	}
}


/* Copies the gamma to the cache */
void copy_gamma_tnc(igd_ovl_info_t *ovl_info, povl_tnc_cache_t ovl_cache)
{
	if (ovl_info) {
		OS_MEMCPY(&ovl_cache->ovl_info.gamma,
			  &(ovl_info->gamma),
			  sizeof(igd_ovl_gamma_info_t));
	} else {
		OS_MEMSET(&ovl_cache->ovl_info.gamma,
			  0,
			  sizeof(igd_ovl_gamma_info_t));
	}
}



/* Checks to see what, if anything has changed.
 * Clears bits in the command and config register that are invalid.
 * Returns a set of flags telling what changed */
unsigned int get_cache_changes_tnc(
	igd_surface_t  *src_surf,
	igd_rect_t     *src_rect,
	igd_rect_t     *dest_rect,
	igd_ovl_info_t *ovl_info,
	unsigned int    flags,
	povl_tnc_cache_t ovl_cache)
{
	unsigned int cache_changed = 0;

	ovl_cache->ovl2_regs.control = 0;

	/* Have the flags changed? */
	if (ovl_cache->flags != flags) {

		/* NOTE that we did not check which flags changed.
		   Currently if any flag changes, we invalidate all
		   the flags. We could further optimize caching if
		   we tested for individual flag changes, but I don't
		   think it will really help much.  Once a movie starts
		   playing, it pretty much uses the same flags
		   for its entire duration, unless the user is mucking
		   about with it as it plays, in which case it's going
		   to be slow anyway. */


		ovl_cache->flags = flags;
		cache_changed |= IGD_OVL_TNC_UPDATE_FLAGS;

		/* Invalidating the flags cache will cause the following
		 * bits to be re-calculated.  Clear them in preparation for
		 * re-calculation. */
		ovl_cache->ovl_regs.command &= ~ (OVL_CMD_FRAME_MODE      |
						 OVL_CMD_FIELD_MODE      |
						 OVL_CMD_FIELD_SYNC_FLIP |
						 OVL_CMD_ACT_FLD1        |
						 OVL_CMD_ACT_FLD0        );
	}

	/* Do a comparison to source surface */
	if (is_changed_surf(&ovl_cache->src_surf, src_surf)) {
		cache_changed |= IGD_OVL_TNC_UPDATE_SURF;
		copy_surf_tnc(src_surf, ovl_cache);

		/* invalidating the source surface will cause the driver
		 * to recalculate the following bits in command */
		ovl_cache->ovl_regs.command &= ~( OVL_CMD_YUV_422  |
						 OVL_CMD_YUV_420P |
						 OVL_CMD_YUV_410P |
						 OVL_CMD_YUV_NV12 |
						 OVL_CMD_Y_SWAP   |
						 OVL_CMD_UV_SWAP  |
						 OVL_CMD_RGB_8888 |
						 OVL_CMD_RGB_565  |
						 OVL_CMD_RGB_555  );

		/* Invalidating the source surface will cause the driver
		 * to recalculate the following bits in config */
		ovl_cache->ovl_regs.config &= ~ ( (1<<4)                    |
					    OVL_CONFIG_LINE_BUFF_MASK );

	}

	/* Do a comparison to source rectangle */
	if (is_changed_rect(&ovl_cache->src_rect, src_rect)) {
		cache_changed |= IGD_OVL_TNC_UPDATE_SRC;
		copy_src_rect_tnc(src_rect, ovl_cache);

		/* invalidating the source rectangle will cause the driver
		 * to recalculate the following bits in command */
		ovl_cache->ovl_regs.command &= ~( OVL_CMD_YUV_422  |
						 OVL_CMD_YUV_420P |
						 OVL_CMD_YUV_410P |
						 OVL_CMD_YUV_NV12 |
						 OVL_CMD_Y_SWAP   |
						 OVL_CMD_UV_SWAP  |
						 OVL_CMD_RGB_8888 |
						 OVL_CMD_RGB_565  |
						 OVL_CMD_RGB_555  );

		/* Invalidating the source rectangle will cause the driver
		 * to recalculate the following bits in config */
		ovl_cache->ovl_regs.config &= ~ ( (1<<4)                    |
					    OVL_CONFIG_LINE_BUFF_MASK );


	}

	/* Has our destination rectangle changed? */
	if (is_changed_rect(&ovl_cache->dest_rect, dest_rect)) {
		cache_changed |= IGD_OVL_TNC_UPDATE_DEST;
		copy_dest_rect_tnc(dest_rect, ovl_cache);
	}

	/* Do a comparison to overlay info color key */
	if (is_changed_color_key(&ovl_cache->ovl_info, ovl_info)) {
		cache_changed |= (IGD_OVL_TNC_UPDATE_INFO |
				  IGD_OVL_TNC_UPDATE_COLORKEY);
		copy_color_key_tnc(ovl_info, ovl_cache);
	}

	/* Do a comparison to overlay info video quality */
	if (is_changed_vq(&ovl_cache->ovl_info, ovl_info)) {
		cache_changed |= ( IGD_OVL_TNC_UPDATE_INFO |
				   IGD_OVL_TNC_UPDATE_VQ);
		copy_vq_tnc(ovl_info, ovl_cache);
	}

	/* Do a comparison to overlay info gamma */
	if (is_changed_gamma(&ovl_cache->ovl_info, ovl_info)) {
		cache_changed |= ( IGD_OVL_TNC_UPDATE_INFO |
				   IGD_OVL_TNC_UPDATE_GAMMA);
		copy_gamma_tnc(ovl_info, ovl_cache);
	}

	return cache_changed;
}

