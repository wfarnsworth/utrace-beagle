/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: dsp.h
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

#ifndef _DSP_H_
#define _DSP_H_

#include <mode.h>

/* FIXME: Illegal exports */
void dsp_dc_init(igd_context_t *context);
int dsp_alloc(igd_context_t *context, unsigned long dc, unsigned long flags);
int dsp_wait_rb(igd_context_t *context);
unsigned long dsp_valid_dc(unsigned long dc, unsigned long flags);
int dsp_display_connected(igd_context_t *context, igd_display_port_t *port);


#endif /* _DSP_H_ */

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: dsp.h,v 1.3 2010/07/23 16:54:50 bpaauwe Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/include/dsp.h,v $
 *----------------------------------------------------------------------------
 */
