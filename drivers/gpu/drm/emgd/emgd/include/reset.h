/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: reset.h
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
 *  This is the internal header file for the reset module. It should be included 
 *  by ssigd HAL modules that need to access the reset module for initialization
 *  and shutdown
 *-----------------------------------------------------------------------------
 */


#ifndef _IGD_RESET_INIT_H
#define _IGD_RESET_INIT_H

#define RESET_FLAG_CAPTURE_SNAPSHOT         0x00000001
#define RESET_FLAG_EXECUTE_SOFT_RESET       0x00000002
#define RESET_FLAG_EXECUTE_HARD_RESET       0x00000003


#endif /*_IGD_RESET_H*/
