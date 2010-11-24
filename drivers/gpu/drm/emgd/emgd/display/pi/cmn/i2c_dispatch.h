/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: i2c_dispatch.h
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
 *  
 *-----------------------------------------------------------------------------
 */

#ifndef _I2C_DISPATCH_H
#define _I2C_DISPATCH_H

/*
 * IO.h is needed to resolve the FAR define
 * context.h is needed for the igd_display_context_t
 */

#include <io.h>
#include <context.h>
#include <mode.h>

#include <pd.h>

#define I2C_DEFAULT_SPEED 100  /* Default I2C bus speed in KHz */
#define DDC_DEFAULT_SPEED  10  /* Default DDC bus speed in KHz */

/*
 * Flags for Write Reg List
 *
 * Serial Write: Write a Reg Value, Data Value repeatedly within one
 *  write cycle.
 */
#define IGD_I2C_SERIAL_WRITE 0x1

typedef struct _i2c_dispatch {
	int (*i2c_read_regs)(
		igd_context_t *context,
		unsigned long i2c_bus,
		unsigned long i2c_speed,
		unsigned long dab,
		unsigned char reg,
		unsigned char FAR *buffer,
		unsigned long num_bytes);
	int (*i2c_write_reg_list)(
		igd_context_t *context,
		unsigned long i2c_bus,
		unsigned long i2c_speed,
		unsigned long dab,
		pd_reg_t *reg_list,
		unsigned long flags);
} i2c_dispatch_t;

#endif

