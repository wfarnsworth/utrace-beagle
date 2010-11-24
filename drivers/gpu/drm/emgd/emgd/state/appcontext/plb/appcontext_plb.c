/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: appcontext_plb.c
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

#include <io.h>

#include <igd_appcontext.h>
#include <igd_gmm.h>
#include <igd_mode.h>
#include <igd_render.h>
#include <igd_errno.h>

#include <intelpci.h>
#include <memory.h>
#include <mode_access.h>
#include <context.h>
#include <state2d.h>
#include <mode.h>
#include <dispatch.h>
#include <utils.h>

#include <plb/appcontext.h>
#include <plb/instr.h>
#include <plb/state3d_plb.h>

#include "../cmn/appcontext_dispatch.h"

/*!
 * @addtogroup state_group
 * @{
 */

/*
 * Prototype these here because they are only needed by appcontext.c
 * and putting them in state2d.h would cause a circular dependency.
 */

static igd_appcontext_h igd_appcontext_alloc_plb(
	igd_display_h display_handle,
	int priority,
	unsigned int flags);
static void igd_appcontext_free_plb(
	igd_display_h display_h,
	int priority,
	igd_appcontext_h appcontext_handle);
static int appcontext_init_plb(igd_context_t *context);
static void appcontext_shutdown_plb(igd_context_t *context);

static appcontext_table_t appcontext_table_plb[] = {
	{0, 0}
};

appcontext_dispatch_t appcontext_dispatch_plb = {
	appcontext_init_plb,
	appcontext_shutdown_plb,
	igd_appcontext_alloc_plb,
	igd_appcontext_free_plb,
	appcontext_table_plb
};

/*!
 * 
 * @param appcontext
 *
 * @return 0 on success
 * @return -IGD_ERROR_NOMEM on failure
 */
static int state2d_init_plb(appcontext_t *appcontext)
{

	appcontext->state2d = OS_ALLOC(sizeof(state2d_t));
	if(!appcontext->state2d) {
		return -IGD_ERROR_NOMEM;
	}

	STATE2D(appcontext)->clip_status = IGD_CLIP_DISABLED;
	STATE2D(appcontext)->dest_rect.x1 = 0;
	STATE2D(appcontext)->dest_rect.y1 = 0;
	STATE2D(appcontext)->dest_rect.x2 = 0;
	STATE2D(appcontext)->dest_rect.y2 = 0;

	return 0;
}

/*!
 * 
 * @param appcontext
 *
 * @return void
 */
static int state2d_shutdown_plb(appcontext_t *appcontext)
{
	if(appcontext->state2d) {
		OS_FREE(appcontext->state2d);
	}

	appcontext->state2d = NULL;

	return 0;
}

/*!
 * 
 * @param display_handle
 * @param priority
 * @param flags
 *
 * @return appcontext_h on success
 * @return NULL on failure
 */
static igd_appcontext_h igd_appcontext_alloc_plb(
	igd_display_h display_handle,
	int priority,
	unsigned int flags)
{
	appcontext_t *appcontext;

	/* A proper appcontext is not required for Poulsbo
	 * as a result, we'll allocate it and have it set to NULL
	 */
	appcontext = OS_ALLOC(sizeof(appcontext_t));
	if (!appcontext) {
		EMGD_ERROR ("OS_ALLOC appcontext failed\n");
		return NULL;
	}

	OS_MEMSET(appcontext, 0, sizeof(appcontext_t));
	appcontext->state2d = NULL;

	if (flags & IGD_CONTEXT_STATE_2D) {
		if (state2d_init_plb(appcontext)) {
			igd_appcontext_free_plb(display_handle, priority, appcontext);
			return NULL;
		}
	}

	return appcontext;

}

static void igd_appcontext_free_plb(
	igd_display_h display_h,
	int priority,
	igd_appcontext_h appcontext_handle)
{

	appcontext_t *appcontext = (appcontext_t *)appcontext_handle;

	/* Free the appcontext struct */
	if (appcontext) {
		state2d_shutdown_plb(appcontext);

		OS_FREE(appcontext_handle);
	}
}

/*!
 * 
 * @param context
 *
 * @return 0
 */
static int appcontext_init_plb(igd_context_t *context)
{
	return 0;
}

/*!
 * 
 * @param context
 *
 * @return void
 */
static void appcontext_shutdown_plb(igd_context_t *context)
{
	return;
}

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: appcontext_plb.c,v 1.6 2010/07/23 16:54:50 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/state/appcontext/plb/appcontext_plb.c,v $
 *----------------------------------------------------------------------------
 */

