/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: instr_common.h
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
 *  Common tools for hardware that uses instruction engines.
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_INSTR_COMMON_H
#define _IGD_INSTR_COMMON_H

/* Write instructions macro. */
#ifdef DEBUG_BUILD_TYPE
#define INSTR_WRITE(data, addr)											\
    if(igd_debug->hal.instr) {											\
		EMGD_DEBUG_S("    addr:%p   data:0x%8.8x", ((void *)(addr)),	\
			(unsigned int)(data));										\
    }																	\
	EMGD_WRITE32 (data, (addr));											\
	addr++;

#define IGD_PRINT_INSTR(name)                                    \
    if(igd_debug->hal.instr) {									 \
		EMGD_DEBUG_S("GMCH Instruction: %s", name);				 \
    }
#else
#define INSTR_WRITE(data, addr) EMGD_WRITE32(data, (addr)++);
#define IGD_PRINT_INSTR(name)
#endif

#endif
