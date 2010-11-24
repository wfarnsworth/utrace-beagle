/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: emgd_shared.h
 * $Revision: 1.11 $
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
 *  This include file contains information that is shared between the various
 *  EMGD driver components.
 *-----------------------------------------------------------------------------
 */

#ifndef _EMGD_SHARED_H
#define _EMGD_SHARED_H

/*
 * Module name is the name of the drm kernel module. This is used by
 * user space components to open a connection to the module. A typical
 * call would look like  -- drmOpen(EMGD_MODULE_NAME, NULL);
 */
#define EMGD_MODULE_NAME "emgd"

#define EMGD_DRIVER_NAME "emgd"

/*
 * EMGD-specific numbering of the PVR DRM ioctls.  The EMGD DRM module is in
 * charge, and includes the PVR DRM code.  As such, the PVR ioctls are included
 * in with the EMGD ioctls ("emgd_drm.h"), and must be kept in sync.  Both sets
 * of these ioctls are mapped to the device specific range between 0x40 and
 * 0x79.
 *
 * Client driver must use these values!
 */
#define DRM_PVR_RESERVED1	0x12
#define DRM_PVR_RESERVED2	0x13
#define DRM_PVR_RESERVED3	0x14
#define DRM_PVR_RESERVED4	0x15
#define DRM_PVR_RESERVED5	0x16
#define DRM_PVR_RESERVED6	0x1E


/*
 * The following typedefs support the ability of non-HAL software to have a
 * function called when a VBlank interrupt occurs.
 */

/**
 * A pointer to a non-HAL-provided function that processes a VBlank interrupt.
 */
typedef int (*emgd_process_vblank_interrupt_t)(void *priv);

/**
 * This structure allows the HAL to track a non-HAL callback (and its
 *  parameter) to call when a VBlank interrupt occurs for a given port.  An
 *  opaque pointer to this structure serves as a unique identifier for the
 *  callback/port combination.
 */
typedef struct _emgd_vblank_callback {
	/** Non-HAL callback function to process a VBlank interrupt. */
	emgd_process_vblank_interrupt_t callback;
	/** An opaque pointer to a non-HAL data structure (passed to callback). */
	void *priv;
	/** Which HAL port number is associated with this interrupt callback. */
	unsigned long port_number;
} emgd_vblank_callback_t;

/**
 * An opaque pointer to a emgd_vblank_callback_t.  This pointer serves as a
 * unique identifier for the callback/port combination.
 */
typedef void *emgd_vblank_callback_h;

/**
 * A special value of a emgd_vblank_callback_h, meaning ALL devices/displays.
 */
#define ALL_PORT_CALLBACKS	((void *) 1001)

#endif
