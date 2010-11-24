/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: pwr_plb.c
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

/* copied from napa */

#include <io.h>
#include "igd_pwr.h"
#include "../cmn/pwr_dispatch.h"
#include <plb/regs.h>

/*!
 * @addtogroup state_group
 * @{
 */

static int pwr_query_full_plb(unsigned int power_state);
static int pwr_set_plb(igd_context_t *context, unsigned int power_state);
static int pwr_init_plb(igd_context_t *context);

pwr_dispatch_t pwr_dispatch_plb = {
	pwr_query_full_plb,
	pwr_set_plb,
	pwr_init_plb,
};

/*!
 * This function returns "0" for all ACPI system states.
 * 
 * @param power_state the requested power state
 *
 * @return 0
 */
static int pwr_query_full_plb(unsigned int power_state)
{                                                          /* pwr_query_full */
	switch( power_state ) {

	case IGD_ADAPTERPOWERSTATE_ON:
	case IGD_ADAPTERPOWERSTATE_STANDBY:
	case IGD_ADAPTERPOWERSTATE_OFF:
	case IGD_ADAPTERPOWERSTATE_SUSPEND:
	case IGD_ADAPTERPOWERSTATE_HIBERNATE:
	default:
		return 0;
		break;
	}
}                                                          /* pwr_query_full */

/*!
 * 
 * @patam context
 * @param power_state the requested power state
 *
 * @return 0
 */
static int pwr_set_plb(igd_context_t *context, unsigned int power_state)
{
	unsigned char *mmio;

	mmio = context->device_context.virt_mmadr;

	switch (power_state) {
	case IGD_POWERSTATE_D0:
		break;
	case IGD_POWERSTATE_D1:
		break;
	case IGD_POWERSTATE_D2:
		break;
	case IGD_POWERSTATE_D3:
		break;

	default:
		break;
	}
	return 0;
}

/*!
 * 
 * @param context
 *
 * @return 0
 */
static int pwr_init_plb(igd_context_t *context)
{
	unsigned char *mmio;

	mmio = context->device_context.virt_mmadr;

	/* Reset CLKGATECTL and CLKGATECTLOVR */
	EMGD_WRITE32(0x1111111, mmio + PSB_CR_CLKGATECTL);
	EMGD_WRITE32(0, mmio + PSB_CR_CLKGATECTL + 8);

	return 0;
}


/*-----------------------------------------------------------------------------
 * $Id: pwr_plb.c,v 1.4 2010/07/23 16:54:50 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/state/power/plb/pwr_plb.c,v $
 *-----------------------------------------------------------------------------
 */
