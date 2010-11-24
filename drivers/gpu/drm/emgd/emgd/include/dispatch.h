/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: dispatch.h
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
 *  This file contains helper functions for creating a dispatch table
 *  for IGD modules.
 *-----------------------------------------------------------------------------
 */

#ifndef _HAL_DISPATCH_H
#define _HAL_DISPATCH_H

#include <context.h>

typedef struct _dispatch_table {
	unsigned long did;
	void *table;
}dispatch_table_t;

static __inline void *dispatch_acquire(
	igd_context_t *context,
	dispatch_table_t *list)
{
	dispatch_table_t *curr = list;
	unsigned long did = context->device_context.did;

	while(curr->did != 0) {
		if(curr->did == did) {
			return curr->table;
		}
		curr++;
	}
	return curr->table;
}

#endif
