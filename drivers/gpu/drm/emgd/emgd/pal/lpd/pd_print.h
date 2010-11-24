/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: pd_print.h
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
 *  Header file to get printing macros for port drivers
 *-----------------------------------------------------------------------------
 */

#ifndef _PD_PRINT_H
#define _PD_PRINT_H

#include <config.h>

extern int pd_print(const char *funcname, const int error,
	const int error_exit, const char *format, ...);
extern void pd_trace_enter(const char *funcname);
extern void pd_trace_exit(const char *funcname);

#ifdef DEBUG_BUILD_TYPE
#define PD_DEBUG(arg...) pd_print(__FUNCTION__, 0, 0, arg)
#define PD_ERROR(arg...) pd_print(__FUNCTION__, 1, 0, arg)
#define PD_TRACE_ENTER   pd_trace_enter(__FUNCTION__)
#define PD_TRACE_EXIT    pd_trace_exit(__FUNCTION__)
#define PD_ERROR_EXIT(arg...) pd_print(__FUNCTION__, 1, 1, arg)
#else
#define PD_DEBUG(arg...)
#define PD_ERROR(arg...)
#define PD_TRACE_ENTER
#define PD_TRACE_EXIT
#define PD_ERROR_EXIT(arg...)
#endif

#define PD_OFFSETOF(t,m) ((unsigned long)&(((t *)0)->m))
#if 0
#define PD_OFFSETOF(t,m) offsetof(t,m)
#endif

#define PD_MODULE_INIT(func, params) func params
#define PD_MODULE_EXIT(func, params) func params

#endif

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: pd_print.h,v 1.5 2010/08/06 17:50:21 rclovrie Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/pal/lpd/pd_print.h,v $
 *----------------------------------------------------------------------------
 */
