/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: ovl_coeff.h
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
 *  This is the internal header file for overlay. It should be not be
 *  by any other module besides the overlay module itself. It contains the
 *  neccessary hardware virtualized structures and functions internal to
 *  overlay
 *-----------------------------------------------------------------------------
 */

#ifndef _OVL_COEFF_H
#define _OVL_COEFF_H

extern void ovl_update_coeff_regs(
	unsigned short wTaps,
	int fpint_cutoff,
	unsigned short bHor,
	unsigned short bY,
	unsigned short * pCoeff);

#endif  /* _OVL_COEFF_H */
