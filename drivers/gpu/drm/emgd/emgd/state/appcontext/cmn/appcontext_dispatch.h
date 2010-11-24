/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: appcontext_dispatch.h
 * $Revision: 1.4 $
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


#ifndef _APPCONTEXT_DISPATCH_H
#define _APPCONTEXT_DISPATCH_H

typedef struct _appcontext_table_t {
	unsigned long appcontext_id;
	unsigned long logical_context_offset;
} appcontext_table_t;

typedef struct _appcontext_dispatch_t {
	int (*appcontext_init)(igd_context_t *context);
	void (*appcontext_shutdown)(igd_context_t *context);
	igd_appcontext_h (*appcontext_alloc)(igd_display_h display_handle,
		int priority, unsigned int flags);
	void (*appcontext_free)(igd_display_h display_handle,
		int priority, igd_appcontext_h context_handle);
	appcontext_table_t *table;
} appcontext_dispatch_t;


extern appcontext_dispatch_t appcontext_dispatch_plb;

extern appcontext_dispatch_t *appcontext_dispatch;

#endif
