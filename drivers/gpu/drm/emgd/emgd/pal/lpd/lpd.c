/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: lpd.c
 * $Revision: 1.7 $
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
 *  Functions necessary to allow debug printing from the port drivers.
 *-----------------------------------------------------------------------------
 */

#define MODULE_NAME hal.dpd

#include <igd_pd.h>
#include <igd_pi.h>
#include "pd_print.h"
#include <memory.h>


/*
 * This file implements the pd debug printing functions using the OAL.
 * In order to keep the OAL debug printing macro definitions in the OAL
 * the DEBUG_BUILD_TYPE option must be set, even in a production build. The
 * port drivers themselves must not call the pd debug printing functions
 * in a release build. This enables the PD SDK to have debug printing from
 * port drivers, even when using a release driver.
 */
#ifndef DEBUG_BUILD_TYPE
#define DEBUG_BUILD_TYPE
#endif
#define MODULE_NAME hal.dpd

#include <io.h>
#include <igd_debug.h>

unsigned long *dropped_debug_messages;

int pd_set_funcname( const char *name )
{
	os_set_funcname(name);
	return 1;
}

int pd_print(const char *funcname, const int error,
	const int error_exit, const char *format, ...)
{
#ifdef DEBUG_BUILD_TYPE
	va_list ap;
	unsigned int *blah;
	char *priority = error ? KERN_ERR : EMGD_DEBUG_MSG_PRIORITY;
	char *fmt = NULL;

	/* Can't directly use the EMGD_DEBUG_S macro (because "format" is a string
	 * variable), so duplicate some of it here:
	 */
	if (!(emgd_debug && emgd_debug-> MODULE_NAME)) {
		return 0;
	}

	va_start(ap, format);
	blah = (unsigned int *)ap;

	if (error_exit) {
		EMGD_DEBUG("EXIT With Error...");
	}

	/* Create a new format string, with all of the correct parts: */
	fmt = OS_ALLOC(strlen(priority) + strlen(funcname) +
		strlen(format) + 2);
	if (fmt == NULL) {
		printk(format, blah[0], blah[1], blah[2], blah[3], blah[4], blah[5],
			blah[6], blah[7], blah[8], blah[9]);
	} else {
		sprintf(fmt, "%s%s %s", priority, funcname, format);
		printk(fmt, blah[0], blah[1], blah[2], blah[3], blah[4], blah[5],
			blah[6], blah[7], blah[8], blah[9]);
		OS_FREE(fmt);
	}
	printk("\n");
	va_end(ap);

	return 0;
#endif
}

void pd_trace_enter(const char *funcname)
{
	EMGD_DEBUG_S("%s ENTER", funcname);
}

void pd_trace_exit(const char *funcname)
{
	EMGD_DEBUG_S("%s EXIT", funcname);
}
