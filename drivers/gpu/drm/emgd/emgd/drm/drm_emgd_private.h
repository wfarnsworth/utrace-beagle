/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: drm_emgd_private.h
 * $Revision: 1.15 $
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
 *  This file contains the EMGD-specific drm_device.dev_private structure,
 *  which is used to share data with the EMGD-specific, IMG 3rd-Party Display
 *  Driver (3DD, implimented in the
 *  "egd_drm/pvr/services4/3rdparty/emgd_displayclass" directory).
 *-----------------------------------------------------------------------------
 */
#ifndef _DRM_EMGD_PRIVATE_H_
#define _DRM_EMGD_PRIVATE_H_

#include <drm/drmP.h>
#include <drm/drm.h>
#include "context.h"



/**
 * This enum is used to record the currently-saved register state (e.g. for VT
 * switching)--either the Linux console's state is saved (i.e. the X server is
 * active), or the X server's state is saved (i.e. the Linux console is
 * active).
 */
typedef enum _drm_emgd_saved_state {
	CONSOLE_STATE_SAVED = 0,
	X_SERVER_STATE_SAVED = 1,
} drm_emgd_saved_state;


/**
 * This structure allows the EMGD-proper code to communicate information and
 * function pointers to the IMG 3rd-Party Display Driver (mrstlfb).
 */
typedef struct _drm_emgd_private {
	/** Non-zero if the HAL is running */
	int hal_running;

	/**
	 * Which register state is currently saved for VT switches (X or the
	 * console; note: the opposite is what's actively installed in the
	 * hardware)
	 */
	drm_emgd_saved_state saved_registers;

	/**
	 * Saved state of the console, when suspending (or hibernating) the system.
	 * emgd_driver_suspend() allocates this, and emgd_driver_resume() frees
	 * this.
	 */
	void *suspended_state;

	/**
	 * A flag which emgd_driver_pre_init() sets and emgd_alter_displays()
	 * clears.  If set (i.e. to 1), this indicates that emgd_alter_displays()
	 * must power on the port drivers' hardware.
	 */
	int must_power_on_ports;

	/** Non-zero if the X server is running (i.e. PVR can't do mode changes) */
	int xserver_running;

	/** Non-zero if emgd_start_pvrsrv() started the PVR services, else zero. */
	int pvrsrv_started;

	/**
	 * Function to re-initialize the 3DD's data structures, after calls to
	 * alter_displays()
	 */
	int (*reinit_3dd)(struct drm_device *dev);


	/** The context is set during the DRM module load function. */
	igd_context_t *context;

	/* The selected DC is copied to here each time alter_displays() is called
	 * via an ioctl.
	 */
	unsigned long dc;

	/**
	 * The port number of the primary display handle is copied to here each
	 * time alter_displays() is called via an ioctl.
	 */
	unsigned short primary_port_number;

	/**
	 * The primary display handle is copied to here each time alter_displays()
	 * is called via an ioctl.
	 */
	igd_display_h primary;

	/**
	 * The port number of the secondary display handle is copied to here each
	 * time alter_displays() is called via an ioctl.
	 */
	unsigned short secondary_port_number;

	/**
	 * The secondary display handle is copied to here each time alter_displays()
	 * is called via an ioctl.
	 */
	igd_display_h secondary;

	/**
	 * Store the device information so it can be passed back to userspace
	 * callers via an ioctl.
	 */
	igd_init_info_t *init_info;

    
    /** TODO:  May use this in future.
     * MSVDX
     */   
    void *msvdx_private;


} drm_emgd_private;

#endif
