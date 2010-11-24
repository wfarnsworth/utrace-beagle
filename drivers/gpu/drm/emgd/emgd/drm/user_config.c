/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: user_config.c
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
 *  A file that contains the initial display configuration information of the
 *  EMGD kernel module.  A user can edit this file in order to affect the way
 *  that the kernel initially configures the displays.  This file is compiled
 *  into the EMGD kernel module.
 *-----------------------------------------------------------------------------
 */
#include "user_config.h"

/*
 * One array of igd_display_info_t structures should exist for each port that
 * needs to provide a DTD list.  Each igd_display_info_t contains the DTD
 * information for a given resolution/refresh-rate.  This is especially needed
 * for analog/VGA ports.
 */

static emgd_drm_splash_screen_t splash_screen_data = {
	0,			/* bg_color */
	0,			/* x */
	0,			/* y */
	0,			/* width */
	0,			/* height */
};

static emgd_drm_splash_video_t splash_video_data = {
	0,			/* offset */
	0,			/* pixel_format */
	0,			/* src_width */
	0,			/* src_height */
	0,			/* src_pitch */
	0,			/* dst_x */
	0,			/* dst_y */
	0,			/* dst_width */
	0,			/* dst_height */
};

static igd_param_t config_params_config1 = {
		1*256*1024,		/* Page request */
		0,		/* Max frame buffer size */
		1,		/* Preserve registers */
		0x6, 		/* Display flags */
		{ 4, 0, 0, 0, 0 },		/* Display port order */
		{		/* Display Params */
		{		/* Port */
			4,		/* Display port number */
			0x0,		/* Parameters present */
			0x1,		/* EDID flag */
			0x3,		/* Flags when EDID is available */
			0x1,		/* Flags when EDID is not available */
			0,		/* DDC GPIO pins */
			0,		/* DDC speed */
			0,		/* DDC DAB */
			0,		/* I2C GPIO pins */
			0,		/* I2C speed */
			0,		/* I2C DAB */
			{		/* Flat Panel Info */
				0,		/* Flat Panel width */
				0,		/* Flat Panel height */
				0,		/* Flat Panel power method */
				0,		/* VDD active & DVO clock/data active */
				0,		/* DVO clock/data active & backlight enable */
				0,		/* backlight disable & DVO clock/data inactive */
				0,		/* DVO clock/data inactive & VDD inactive */
				0			/* VDD inactive & VDD active */
			},
			{		/* DTD Info */
			0, NULL
			},
			{		/* Attribute Info */
			0, NULL
			}
		},
	},
	0,			/* 24-bit RGB color that framebuffer is cleared to */
	0,			/* Quickboot (1 = enabled) */
	0,			/* Quickboot seamless (1 = enabled) */
	0,			/* Quickboot video input (1 = enabled) */
	0			/* Polling (1 = override interrupt support and use polling) */
};

igd_param_t *config_params = {&config_params_config1};

/*
 * The emgd_drm_config_t structure is the main configuration structure
 * for the EMGD kernel module.
 */
emgd_drm_config_t config_drm = {
	0,	/* Whether to initialize the display at EMGD module startup time
		 * (corresponds to the "init" module parameter)
		 */
	1,	/* The display configuration to use if initializing the display
		 * (corresponds to the "init" module parameter), where:
		 * - 1 = Single port/display
		 * - 2 = Cloned port/display (e.g. LVDS + CRT with different timings)
		 * - 4 = Twin ports/displays (e.g. LVDS + CRT with same timings)
		 *       Note: Twin is NOT CURRENTLY SUPPORTED
		 * - 8 = Extended displays (e.g. LVDS + CRT displaying different images)
		 */
	1024,/* Display width to use if initializing the display
		 * (corresponds to the "width" module parameter)
		 */
	768,/* Display height to use if initializing the display
		 * (corresponds to the "height" module parameter)
		 */
	60,	/* Display refresh rate to use if initializing the display
		 * (corresponds to the "refresh" module parameter)
		 */
	0,	/* ovl_brightness */
	0,	/* ovl_contrast */
	0,	/* ovl_saturation */
	0,	/* ovl_gamma_red */
	0,	/* ovl_gamma_green */
	0,	/* ovl_gamma_blue */
	&splash_screen_data,
	&splash_video_data,
	&config_params	/* driver parameters from above */
};
 
