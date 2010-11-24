/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: math_fix.h
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
 *  This file contains OS abstracted interfaces to fixed point math functions
 *-----------------------------------------------------------------------------
 */

#ifndef _OAL_MATH_FIX_H
#define _OAL_MATH_FIX_H


#define OS_POW_FIX(b, p)         os_pow_fix(b, p)


#define OS_MAX(a,b)              (((a) > (b)) ? (a) : (b))
#define OS_MIN(a,b)              (((a) < (b)) ? (a) : (b))

/*****************************************************************************
 * Function: os_pow_fix
 *
 * Parameters:
 *    [IN] base:  the base, should be between 0 and 255.
 *    [IN] power:  this must be in 24i.8f format.
 *
 * Description:
 *    This function uses the Taylor Series to approximate the power function
 *    using fixed-point math.
 *
 ****************************************************************************/

unsigned int os_pow_fix( const int base, const int power );



#endif
