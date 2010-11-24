/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_appcontext.c
 * $Revision: 1.6 $
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
 *  This file inplements the IGD interface for the context module. This
 *  includes functions that handle hardware context swapping and state
 *  variable management.
 *-----------------------------------------------------------------------------
 */

#define MODULE_NAME hal.state

#include <config.h>

#include <igd_appcontext.h>
#include <igd_gmm.h>
#include <igd_mode.h>
#include <igd_errno.h>

#include <intelpci.h>
#include <context.h>
#include <mode.h>
#include <dispatch.h>

#include <io.h>

#include "appcontext_dispatch.h"

/*!
 * @addtogroup state_group
 * @{
 */

static dispatch_table_t appcontext_dispatch_list[] = {
#ifdef CONFIG_PLB
	{PCI_DEVICE_ID_VGA_PLB, &appcontext_dispatch_plb},
#endif
#ifdef CONFIG_TNC
	{PCI_DEVICE_ID_VGA_TNC, &appcontext_dispatch_plb},
#endif
	{0, NULL}
};

/* Not static: cores may need it */
appcontext_dispatch_t *appcontext_dispatch = NULL;

/*!
 *
 * @param display_handle
 * @param priority
 * @param flags
 *
 * @return appcontext_h
 */
igd_appcontext_h igd_appcontext_alloc(
	igd_display_h display_handle,
	int priority,
	unsigned int flags)
{

	return appcontext_dispatch->appcontext_alloc(
		display_handle, priority, flags);
}

/*!
 *
 * @param display_handle
 * @param priority
 * @param appcontext_handle
 *
 * @return void
 */
void igd_appcontext_free(
	igd_display_h display_handle,
	int priority,
	igd_appcontext_h appcontext_handle)
{
	appcontext_dispatch->appcontext_free(
		display_handle, priority, appcontext_handle);
}

/*!
 *
 * @param context
 *
 * @return void
 */
void appcontext_shutdown(igd_context_t *context)
{

	EMGD_DEBUG("appcontext_shutdown Entry");

	if (appcontext_dispatch != NULL)
	{
		appcontext_dispatch->appcontext_shutdown(context);
	}
}

/*!
 *
 * @param context
 *
 * @return void
 */
int appcontext_init(igd_context_t *context)
{

	EMGD_DEBUG("appcontext_init Entry");

	appcontext_dispatch = (appcontext_dispatch_t *)dispatch_acquire(context,
		appcontext_dispatch_list);
	if(!appcontext_dispatch) {
		return -IGD_ERROR_NODEV;
	}

	/* Hook up top level dispatch table */
	context->dispatch.appcontext_alloc = appcontext_dispatch->appcontext_alloc;
	context->dispatch.appcontext_free = appcontext_dispatch->appcontext_free;

	/* Hook up optional inter-module functions */
	context->mod_dispatch.appcontext_shutdown = appcontext_shutdown;

	return 0;
}

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: igd_appcontext.c,v 1.6 2010/07/23 16:54:50 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/state/appcontext/cmn/igd_appcontext.c,v $
 *----------------------------------------------------------------------------
 */
