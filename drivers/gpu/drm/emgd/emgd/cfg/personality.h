/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: personality.h
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
 *  This file is used in conjunction with the default_config.h to
 *  gererate a full set of build defines.
 *-----------------------------------------------------------------------------
 */

#ifndef _PERSONALITY_H
#define _PERSONALITY_H
/*
TODO: After the 9.1.1 branch, re-enable this code and delete igd_version.h
#define IGD_MAJOR_NUM  9
#define IGD_MINOR_NUM  1
#define IGD_BUILD_NUM  1258

#define IGD_PCF_VERSION   0x00000400
*/

/* Enable COPP */
#define CONFIG_COPP

#include <igd_version.h>

#endif
