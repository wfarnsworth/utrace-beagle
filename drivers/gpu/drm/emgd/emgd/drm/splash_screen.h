/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: splash_screen.h
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
 *
 *-----------------------------------------------------------------------------
 * Description:
 *  This is the Intel Embedded Graphics EFI Driver Splash Screen header file.
 *  This file contains data structures pertinent to showing a splash screen
 *  with a customizable icon.
 *-----------------------------------------------------------------------------
 */

#ifndef _SPLASH_SCREEN_H
#define _SPLASH_SCREEN_H

#include <user_config.h>

#define CONV_16_TO_32_BIT(a) (((a & 0xF800)<<8) | ((a & 0x7E0)<<5) |\
						(a & 0x1F)<<3)

typedef struct _bitmap_header {
	/* What is the widht and height of the bitmap */
	unsigned short width;
	unsigned short height;
	/* If Negative, from bottom right, how much to go left by */
	/* If Positive, from top left, how much to go right by */
	short x_coord;
	/* If Negative, from bottom right, how much to go up by */
	/* If Positive, from top left, how much to go down by */
	short y_coord;
} bitmap_header;

void display_splash_screen(
	igd_framebuffer_info_t *fb_info,
	unsigned char *fb,
	emgd_drm_splash_screen_t *ss_data);

#endif
