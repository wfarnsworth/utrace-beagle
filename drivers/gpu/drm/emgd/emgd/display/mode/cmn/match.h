/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: match.h
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
 *  This file contains the mode matching algorithms
 *-----------------------------------------------------------------------------
 */

#include <mode.h>

int validate_fb(
	pigd_framebuffer_info_t fb_info,
	igd_display_plane_t *plane);

int validate_cursor(
	igd_cursor_info_t *cursor_info,
	igd_display_context_t *display);

int match_mode (
	igd_display_context_t *display,
	igd_timing_info_t *timing_table,
	igd_framebuffer_info_t *fb_info,
	igd_display_info_t *pt_info,
	igd_timing_info_t **timing);


/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: match.h,v 1.3 2010/07/23 16:54:49 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/display/mode/cmn/match.h,v $
 *----------------------------------------------------------------------------
 */
