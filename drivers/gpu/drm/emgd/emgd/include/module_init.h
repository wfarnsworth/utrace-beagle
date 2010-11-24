/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: module_init.h
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
 *  This file contains the init/power/shutdown prototypes for all optional
 *  (and possibly other) modules.
 *-----------------------------------------------------------------------------
 */

#ifndef _MODULE_INIT_H
#define _MODULE_INIT_H

#include <config.h>
#include <context.h>

extern int mode_init(igd_context_t *context);
extern int dsp_init(igd_context_t *context);
extern int pi_init(igd_context_t *context);
extern int _init_2d(igd_context_t *context);
extern int _blend_init(igd_context_t *context);
extern int _overlay_init(igd_context_t *context, igd_param_t *params);
extern int _cmd_init(igd_context_t *context);
extern int _pwr_init(igd_context_t *context);
extern int _reset_init(igd_context_t *context);
extern int _reg_init(igd_context_t *context, unsigned long flags);
extern int appcontext_init(igd_context_t *context);
extern int gmm_init(igd_context_t *context, unsigned long scratch_mem,
		unsigned long max_fb_size);
extern void gmm_shutdown(igd_context_t *context);


#ifdef CONFIG_2D
#define INIT_2D(c) _init_2d(c);
#else
#define INIT_2D(c) 0
#endif

#ifdef CONFIG_BLEND
#define BLEND_INIT(c) _blend_init(c);
#else
#define BLEND_INIT(c) 0
#endif

#ifdef CONFIG_OVERLAY
#define OVERLAY_INIT(c, p) _overlay_init(c, p)
#else
#define OVERLAY_INIT(a, p) 0
#endif

#ifdef CONFIG_CMD
#define CMD_INIT(a) _cmd_init(a);
#else
#define CMD_INIT(a) 0
#endif

#ifdef CONFIG_POWER
#define PWR_INIT(a) _pwr_init(a);
#else
#define PWR_INIT(a) 0
#endif

#ifdef CONFIG_REG
#define REG_INIT(a, b) _reg_init(a, b);
#else
#define REG_INIT(a, b) 0
#endif

#ifdef CONFIG_RESET
#define RESET_INIT(a) _reset_init(a);
#else
#define RESET_INIT(a) 0
#endif

#ifdef CONFIG_INTERRUPT
#define INTERRUPT_INIT(did, mmadr) OS_INIT_INTERRUPT(did, mmadr);
#else
#define INTERRUPT_INIT(did, mmadr) 0
#endif

#ifdef CONFIG_APPCONTEXT
#define APPCONTEXT_INIT(a) appcontext_init(a)
#else
#define APPCONTEXT_INIT(a) 0
#endif

#endif
