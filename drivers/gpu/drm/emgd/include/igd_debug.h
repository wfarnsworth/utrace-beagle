/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_debug.h
 * $Revision: 1.6 $
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
 *  This file contains data structures and variables needed to control
 *  debugging within the IEGD driver.
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_DEBUG_H
#define _IGD_DEBUG_H

typedef struct _igd_debug {
	struct {
		/* Per-Module Debug Bits */
		short cmd      ;
		short dsp      ;
		short mode     ;
		short init     ;
		short overlay  ;
		short power    ;
		short _2d      ;
		short blend    ;
		short state    ;
		short gmm      ;
		short gart     ;
		short oal      ;
		short intr     ;
		short dpd      ;
		short video    ;
		short pvr3dd   ;
		/* Global Debug Bits */
		short trace    ;
		short instr    ;
		short debug    ;
		/* Verbose debug bits */
		short blend_stats        ;
		short dump_overlay_regs  ;
		short dump_command_queue ;
		short dump_gmm_on_fail   ;
		short dump_shaders       ;
	} hal;
} igd_debug_t;

extern igd_debug_t *emgd_debug;


#endif
