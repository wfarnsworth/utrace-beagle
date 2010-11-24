/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: user_config.h
 * $Revision: 1.5 $
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
 *  Data structure containing the initial display configuration information of
 *  the EMGD kernel module.
 *-----------------------------------------------------------------------------
 */
#ifndef _USER_CONFIG_H_
#define _USER_CONFIG_H_

#include "igd_init.h"
#include "igd_mode.h"

/*
 * Splash Screen data provided by the user.
 */
typedef struct _emgd_drm_splash_screen {
	unsigned long bg_color;
	unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height;
} emgd_drm_splash_screen_t;

/*
 * Splash Video data provided by the user.
 */
typedef struct _emgd_drm_splash_video {
	unsigned long offset;
	unsigned long pixel_format;
	unsigned long src_width;
	unsigned long src_height;
	unsigned long src_pitch;
	unsigned long dst_x;
	unsigned long dst_y;
	unsigned long dst_width;
	unsigned long dst_height;
} emgd_drm_splash_video_t;

/**
 * User-configurable parameters.  This structure is the basis for the
 * user_config.c" file, which allows compile-time customization of the EMGD DRM
 * module.
 *
 * Besides the igd_param_t values, the other options in this structure
 * correspond to EMGD module parameters of the same name.  Most are only
 * applicable if the init option is non-zero.  There is one additional module
 * parameter ("portorder") that corresponds to the port_order member of the
 * igd_param_t structure.
 */
typedef struct _emgd_drm_config {
	/**
	 * Whether the EMGD kernel/DRM module should initialize the display at
	 * startup time (1=yes, 0=no).
	 */
	int init;
	/** The display configuration to use if initializing the display. */
	int dc;
	/** The width to use if initializing the display. */
	int width;
	/** The height to use if initializing the display. */
	int height;
	/** The refresh rate to use if initializing the display. */
	int refresh;
	/** Overlay Brightness */
	unsigned long ovl_brightness;
	/** Overlay Contrast */
	unsigned long ovl_contrast;
	/** Overlay Saturation */
	unsigned long ovl_saturation;
	/** Overlay Gamma Correction - Red */
	unsigned long ovl_gamma_red;
	/** Overlay Gamma Correction - Green */
	unsigned long ovl_gamma_green;
	/** Overlay Gamma Correction - Blue */
	unsigned long ovl_gamma_blue;
	/** The splash screen data if specified by the user. */
	emgd_drm_splash_screen_t *ss_data;
	/** The splash video data if specified by the user. */
	emgd_drm_splash_video_t *sv_data;
	/** Array of other parameters (one per configid), used by the hardware
	 * abstraction layer code.
	 */
	igd_param_t **hal_params;
} emgd_drm_config_t;

#endif
