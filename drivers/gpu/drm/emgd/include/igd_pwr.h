/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_pwr.h
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
 *  
 *-----------------------------------------------------------------------------
 */



#ifndef _IGD_PWR_H
#define _IGD_PWR_H

/*
 * Device power state defines
 */

#define IGD_POWERSTATE_D0			0x0
#define IGD_POWERSTATE_D1			0x1
#define IGD_POWERSTATE_D2			0x2
#define IGD_POWERSTATE_D3			0x3
#define IGD_POWERSTATE_UNDEFINED    0xFFFFFFFF

/*
 * Graphics Adaptor Power State Defines
 */
#define IGD_ADAPTERPOWERSTATE_ON        0x10
#define IGD_ADAPTERPOWERSTATE_STANDBY   0x11
#define IGD_ADAPTERPOWERSTATE_SUSPEND   0x12
#define IGD_ADAPTERPOWERSTATE_OFF       0x13
#define IGD_ADAPTERPOWERSTATE_HIBERNATE 0x14


/*----------------------------------------------------------------------
 * Function:
 *  int dispatch->pwr_alter(igd_driver_h driver_handle,
 *    unsigned int power_state);
 *
 * *----------------------------------------------------------------------
 */

#endif /*_IGD_PWR_H*/
