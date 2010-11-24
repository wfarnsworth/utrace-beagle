/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_rb.h
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
 *  Example Usage:
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_RB_H
#define _IGD_RB_H

#include <igd_mode.h>

/*
 * Flags for igd_sync()
 */
#define IGD_SYNC_BLOCK         0x00000000
#define IGD_SYNC_NONBLOCK      0x00000001
/*
 * No Flush pipe will not issue an MI Flush before the store dword
 * There is no guarentee that the store dword will not complete before
 * an earlier command unless the caller is sure that a store dword alone
 * is sufficient.
 */
#define IGD_SYNC_NOFLUSH_PIPE  0x00000010
/*
 * Do not flush the render cache as part of this flush. Map Cache will
 * be invalidated always.
 */
#define IGD_SYNC_NOFLUSH_CACHE 0x00000020
/* Generate a user Interrupt after the sync completes */
#define IGD_SYNC_INTERRUPT   0x00000040
/*
 * Flush the pipe now but delay the cache flush until the
 * sync is checked.
 */
#define IGD_SYNC_DELAY_FLUSH 0x00000080
/*
 * Synchronize queue with video decode engine.
 */
#define IGD_SYNC_VIDEO       0x00000100


/*!
 * dispatch->get_sync_slot() returns the offset into the status page where
 * the sync values can be found for a particular display handle.
 *
 * This function is to be used by a priviledged IAL only and requires some
 * knowledge of the underlying behavior of the sync. The intention of this
 * function is to allow an IAL that already has device knowledge to
 * check the status of an issued sync call without calling through the HAL.
 * In some cases (such as OGL) the address space seperation would otherwise
 * make sync checking through the HAL a cost prohibitive operation.
 *
 * @param display_handle pointer to an IGD_DISPLAY pointer returned
 *    from a successful call to dispatch->allocate_display().
 *
 * @param priority One of the IGD_PRIORITY_* defines. This must match
 *    the define used when issuing the sync. NORMAL priority is the
 *    only common use case.
 *
 * @return 0: Success.
 * @return -IGD_ERROR_INVAL:  Otherwise
 */
typedef int (*_igd_get_sync_slot_fn_t)(igd_display_h display_handle,
	unsigned int priority,
	unsigned int *offset);

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: igd_rb.h,v 1.3 2010/07/23 16:54:51 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/include/igd_rb.h,v $
 *----------------------------------------------------------------------------
 */

#endif /* _IGD_RB_H */
