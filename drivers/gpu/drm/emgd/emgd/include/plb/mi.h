/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: mi.h
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
 *  This is a header file for the Intel GFX commands.
 *  This includes commands specific to Intel hardware and structures specific
 *  to Intel hardware.  All other commands and structures are available
 *  through GFX.
 *-----------------------------------------------------------------------------
 */

#ifndef _MI_H
#define _MI_H

#include <igd_mode.h>
#include <igd_render.h>

/* FIXME: This file has not been checked for PLB. */

#define MI_FLUSH_OPTIONS_MASK 0x0000000f
#define MI_FLUSH_MAP          0x00000001
#define MI_FLUSH_RENDER       0x00000004
/* #define MI_FLUSH_END_SCENE    0x00000008  Not available on PLB? */
/* #define MI_FLUSH_WRITE_DIRTY  0x00000010  Not available on PLB? */

extern int mi_display_buffer_info_plb(igd_display_h display_h,
	int priority,
	unsigned long flags);
				   
extern int mi_wait_scan_priority_arb_on_off_plb(igd_command_t *addr,
	int priority, int enable);
				   
extern int mi_wait_scan_lines_excl_plb(igd_display_h display_h,
	int priority,
	unsigned long start,
	unsigned long end);

extern int mi_wait_scan_lines_incl_plb(igd_display_h display_h,
	int priority,
	unsigned long start,
	unsigned long end);

extern int mi_wait_vblank_plb(igd_display_h display_h,
	int priority);

extern int mi_flush_plb(igd_display_h display_h, int priority,
	unsigned int flush_options, unsigned int flags);

extern int mi_wait_for_scan_plb(igd_display_h display_h, int priority,
	igd_rect_t *dest_rect);

extern int mi_user_interrupt_plb(igd_display_h display_h, int priority);

#endif /* _MI_H */
