/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: dsp_dispatch.h
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

#ifndef _DSP_DISPATCH_H
#define _DSP_DISPATCH_H

#include <igd.h>
#include <igd_init.h>
#include <igd_mode.h>

#include <mode.h>

/*
 * FIXME: This belong to PI, remove the defaults and let PI set
 * them as it does for i2c.
 */
#define DDC_DEFAULT_SPEED  10  /* Default DDC bus speed in KHz */

typedef struct _dsp_dispatch {
	igd_plane_t **planes;
	igd_display_pipe_t **pipes;
	igd_display_port_t **ports;
	igd_fb_caps_t *caps;
	unsigned long *overlay_pfs;
	unsigned long *render_pfs;
	unsigned long *texture_pfs;
	int (*dsp_init)(igd_context_t *context);
} dsp_dispatch_t;

extern dsp_dispatch_t dsp_dispatch_plb;
extern dsp_dispatch_t dsp_dispatch_tnc;

#endif
