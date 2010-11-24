/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_reset.h
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
 *  This is the external header file for the reset module. It should be included 
 *  by above IAL for reset functionality on the ssigd HAL layers.
 *-----------------------------------------------------------------------------
 */


#ifndef _IGD_RESET_H
#define _IGD_RESET_H


/*----------------------------------------------------------------------------
 * Function:
 *   int dispatch->reset_alter(igd_driver_h driver_handle);
 *
 * Description:
 *		.
 * Parameters:
 *		driver_handle - pointer to main driver context structure.
 *
 * Return:
 *  !0: Pointer to a ring buffer structure upon successful allocation
 *  0: A ring buffer of specified type can not be allocated, or an
 *    error occurred during memory allocation for the buffer.
 *----------------------------------------------------------------------------
 */


#endif /*_IGD_RESET_H*/
