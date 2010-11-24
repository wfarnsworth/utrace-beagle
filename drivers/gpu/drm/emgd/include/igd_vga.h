/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_vga.h
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
 *  Header file for common VGA registers and macros.
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_VGA_H
#define _IGD_VGA_H

#ifdef CONFIG_MICRO
#define VB_CODE_SEG __based( __segname("_CODE"))
#else
#define VB_CODE_SEG
#endif

/* The Maximum VGA Mode Number as specified in the IGD Mode Table. */
#define VGA_MODE_NUM_MAX 0x1C

typedef struct vga_mode_data {
	unsigned char  cols;
	unsigned char  rows;                 /* #rows-1 */
	unsigned char  char_height;
	unsigned short video_buff_size;
	unsigned char  sr_regs[4];
	unsigned char  misc_reg;
	unsigned char  crtc_regs[25];
	unsigned char  ar_regs[20];
	unsigned char  gr_regs[9];
} vga_mode_data_t;

/* This contains the VGA Mode Table.  A ptr to this exists in the 
 * Environment. */
extern vga_mode_data_t VB_CODE_SEG vga_mode_data[];

/* This contains a pointer to the VGA Mode_Table.  This is necessary, so
 * vga_mode.c can use this to program the mode, incase the user has
 * changed the Environment Table. */
extern vga_mode_data_t FAR (*vga_mode_data_ptr)[];

#endif
