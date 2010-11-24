/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_errno.h
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
 *  This file contains igd error definitions.
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_ERRNO_H
#define _IGD_ERRNO_H

/* Error values, must be <64kb for vBIOS */
#define IGD_ERROR_NOMEM      0x0001
#define IGD_ERROR_INVAL      0x0002
#define IGD_ERROR_BUSY       0x0003
#define IGD_ERROR_PWRDOWN    0x0004
#define IGD_ERROR_NODEV      0x0005
#define IGD_ERROR_HWERROR    0x0006
#define IGD_ERROR_EDID       0x0007

#define IGD_NO_MEM           IGD_ERROR_NOMEM
#define IGD_INVAL            IGD_ERROR_INVAL

/* Success value */
#define IGD_SUCCESS               0
#define IGD_SUCCESS_DO_QRY_SETMODE    0x1001

#define IGD_DO_QRY_SETMODE        IGD_SUCCESS_DO_QRY_SETMODE

#endif
