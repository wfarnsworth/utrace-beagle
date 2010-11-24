/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: config.h
 * $Revision: 1.9 $
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
 *  This file contains the compile options for the IGD compile. It is included
 *  by all IGD OAL and RAL modules. Do not remove valid options from this
 *  file, simply comment them out.
 *  Eventually a config tool will auto generate this file based on selected
 *  options.
 *-----------------------------------------------------------------------------
 */

#ifndef _HAL_CONFIG_H
#define _HAL_CONFIG_H

/*
 *  * Select ONE of these to be defined. It controls which OAL port
 *   * is used during the build and where the output goes.
 *    */
/* #define CONFIG_OAL linux */
#define CONFIG_OAL linux-user
/* #define CONFIG_OAL xfree86 */
/* #define CONFIG_OAL windows */
/* #define CONFIG_OAL null */

/* #define CONFIG_OAL_WINDOWS_MINIPORT */


//#define CONFIG_NEW_MATCH 1

/*
 * Which Cores are supported
 *
 * Use Defaults
 */

/*
 * This macro configures the DRM/kernel's EMGD_DEBUG() and EMGD_DEBUG_S() macros to
 * use the KERN_INFO message priority, instead of the normal KERN_DEBUG message
 * priority.  This is useful for bugs (e.g. crashes) where dmesg can't be used
 * to obtain debug messages.
 */
/* #define CONFIG_USE_INFO_PRIORITY */


/*
 * Which of the optional modules are included in the build
 * for the most part this is for modules that need an init
 * or power entry point.
 *
 * Use Defaults.
 */

/*
 * Default FB/Display Resolution
 */
#define CONFIG_DEFAULT_WIDTH  640
#define CONFIG_DEFAULT_HEIGHT 480
#define CONFIG_DEFAULT_PF     IGD_PF_ARGB32


/*
  power modes supported
  0 -don't support
  1 - support

  Use Defaults.
*/

/*
 * Turn off fences for performance analysis. 3d makes use of "Use Fences"
 * So this will make fences regions become linear but everything should
 * still work.
 *
 * #define CONFIG_NOFENCES
 */

/* Don't enable Dynamic port driver loading for simple driver. For simple, 
 * one can limit the port drivers by enabling CONFIG_LIMIT_PDS to 
 * required port drivers *
 * 
 * Enable Dynamic port driver loading
 *
 * #define IGD_DPD_ENABLED 1 */

/* Enable required port drivers. */
#define CONFIG_LIMIT_PDS 1
#define CONFIG_PD_ANALOG 0
#define CONFIG_PD_LVDS   1
#define CONFIG_PD_SDVO   1
#define CONFIG_PD_TV     0 /* Integrated TV for NAPA */

#define CONFIG_LINK_PD_LVDS
#define CONFIG_LINK_PD_SDVO

#define CONFIG_DECODE

#include <config_default.h>

#endif

