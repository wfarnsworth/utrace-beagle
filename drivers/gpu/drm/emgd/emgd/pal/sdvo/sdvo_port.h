/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: sdvo_port.h
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
 *  Main include file for SDVO port driver
 *-----------------------------------------------------------------------------
 */

#ifndef _SDVO_PORT_H_
#define _SDVO_PORT_H_

#include <config.h>
#include <igd_pd.h>
#include <pd.h>
#include <pd_print.h>

/* #define DEBUG 0 */

/*  ............................................................................ */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(p) (sizeof(p)/sizeof((p)[0]))
#endif

#include "sdvo_intf.h"
#include "sdvo_attr.h"
#include "sdvo_hdmi.h"

/*  ............................................................................ */
#ifndef CONFIG_MICRO
#define	SDVO_GET_ATTR_NAME(p_attr)	p_attr->name
#else
#define SDVO_GET_ATTR_NAME(p_attr)	""
#endif

/*  ............................................................................ */
unsigned char sdvo_write_i2c_reg(sdvo_device_context_t *p_Ctx, i2c_reg_t offset,
	i2c_reg_t value);
unsigned char sdvo_read_i2c_reg(sdvo_device_context_t *p_Ctx, unsigned char offset,
	i2c_reg_t *p_Value);


int sdvo_is_multi_display_device(sdvo_device_context_t *p_ctx);

#endif  /*  _SDVO_PORT_H_ */
