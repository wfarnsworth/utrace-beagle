/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: state2d.h
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
 *  This file is the header file for manipulating the 2D State variables.
 *-----------------------------------------------------------------------------
 */

#ifndef _STATE2D_H
#define _STATE2D_H

/* IGD */
#include <igd_render.h>

typedef struct _state2d {
    igd_rect_t dest_rect;
	unsigned int clip_status;
} state2d_t;

#define STATE2D(ac) ((state2d_t *)ac->state2d)

#define STATE2D_SET_CLIP(ac, rect)                            \
if(ac) {                                                      \
    OS_MEMCPY(&((state2d_t *)(ac)->state2d)->dest_rect, rect, \
		sizeof(igd_rect_t));                                  \
}
 /*
  * Checking for the 2D appcontext instead of the appcontext 
  * pointer because the state2d could be null during botched 
  * allocation. 
  */
#define STATE2D_GET_CLIP(ac) \
	(((ac) && ((state2d_t *)(ac)->state2d))? \
	(&((state2d_t *)(ac)->state2d)->dest_rect):NULL)

#define STATE2D_GET_CLIP_STATUS(ac) \
	(((ac) && ((state2d_t *)(ac)->state2d))? \
	(((state2d_t *)(ac)->state2d)->clip_status):0)

#define STATE2D_SET_CLIP_STATUS(ac, s) \
	(((ac) && ((state2d_t *)(ac)->state2d))? \
	(((state2d_t *)(ac)->state2d)->clip_status = s):0)

#endif /*_STATE2D_H */


