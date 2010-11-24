/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: rb.h
 * $Revision: 1.7 $
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
 *  This header file describes the inter-module interface for using the
 *  ring buffer. This is a legacy interface that is not strictly
 *  device-independent. It is kept here because many legacy chipsets use
 *  this interface.
 *-----------------------------------------------------------------------------
 */

#ifndef _RB_H
#define _RB_H

#include <igd_rb.h>
#include <igd_errno.h>

#include <context.h>
#include <module_init.h>
#include <mode.h>

#include <io.h>
#include <memory.h>
#include <sched.h>


/*
 * The rb_buffer contents should be treated as opaque but are defined
 * here for the use in the inline functions below.
 */
typedef struct _rb_buffer {
	unsigned int id;       /* ring index */
	unsigned long size;    /* size of rb in bytes */
	unsigned long tail_off;
	unsigned long dead_off;
	unsigned long avail;
	unsigned long addr;    /* starting address of rb */
	unsigned char *virt;    /* virt starting address of rb */
	unsigned char *start;   /* ring buffer start register offset */
	unsigned char *head;    /* ring buffer head register offset */
	unsigned char *tail;    /* ring buffer tail register offset */
	unsigned char *ctrl;    /* ring buffer ctrl register offset */
	unsigned char *sync;    /* used to synchronize s/w interface
								   * code via rb_sync() */
	unsigned long next_sync;
	int state;             /* on or off state */
	unsigned long last_head_value; /* used for checking ring buf lockup,
									* keeps last head value*/
	os_alarm_t last_head_time; /* used for checking ring buf lockup,
								* keeps last head time*/
	unsigned long reservation; /* increments upon each rb_reserver(),
								* reset to zero upon rb_update() */
	unsigned long sync_wrap;   /* Sync number to wrap at */
	igd_context_t * context_ptr; /*back pointer to the main driver context */
	igd_appcontext_h appcontext; /* Appcontext that is current on the ring */
        unsigned int skip_timeout;  /* skip the timeout check */
	unsigned int force_reset_rb;  /* force a rb reset */
} rb_buffer_t;


#define MODE_GET_RING(d, p) \
	((rb_buffer_t *)((igd_display_pipe_t *)((igd_display_context_t *)d)->pipe)->queue[p])

/*
 * Flags used exclusively by rb_reserve()
 */
#define RB_RESERVE_BLOCK     0x00000000
#define RB_RESERVE_NONBLOCK  0x00000001


/*
 * Determine how much space is available in the ring buffer.
 */
unsigned long rb_avail(rb_buffer_t *buffer);


#define MODE_PIPE_ALLOCED(d) \
	((igd_display_pipe_t *)((igd_display_context_t *)d)->pipe)

extern igd_command_t *rb_slow_reserve(rb_buffer_t *buffer,
	unsigned long size,
	unsigned long flags);
/*
 * For Debug do not use the inline ring functions. It makes it hard
 * to add breakpoints.
 */
#ifdef DEBUG_BUILD_TYPE 
extern igd_command_t *rb_reserve(rb_buffer_t *buffer,
	unsigned long size,
	unsigned long flags);

extern int rb_update(rb_buffer_t *buffer,
	igd_command_t *addr);

#else
#ifdef CONFIG_CMD
static __inline igd_command_t *rb_reserve(rb_buffer_t *buffer,
	unsigned long size,
	unsigned long flags)
{
	if (buffer->state == CMD_CONTROL_OFF) {
		/* ring buffer is turned off, so don't allow a rb_reserve() */
		buffer->context_ptr->igd_device_error_no = -IGD_ERROR_PWRDOWN;
		return(NULL);
	}

	/*
	 * Change size to bytes for efficiency.
	 */
	size = ((size<<2) + 7) & ~7;

	if(buffer->reservation) {
		buffer->avail += buffer->reservation;
	}
	buffer->reservation = size;

	if(buffer->avail > size) {
		buffer->avail -= size;
		return (igd_command_t *)(buffer->virt + buffer->tail_off);
	}

	return rb_slow_reserve(buffer, size, flags);
}


static __inline int rb_update(rb_buffer_t *buffer,
	igd_command_t *addr)
{
	unsigned long tail_off;
/*	tail_off = (addr - buffer->virt); */
   	tail_off = (unsigned long)((unsigned char *)(addr) - buffer->virt);

	buffer->reservation = 0;
	buffer->tail_off = tail_off;

	if(buffer->tail_off & 0x7) {
		EMGD_WRITE32(0, buffer->virt + buffer->tail_off);
		buffer->tail_off += 4;
		buffer->avail -= 4;
	}

	EMGD_WRITE32(buffer->tail_off, buffer->tail);

	return 0;
}
#else
static __inline igd_command_t *rb_reserve(rb_buffer_t *buffer,
	unsigned long size,
	unsigned long flags)
{
	return NULL;
}

static __inline int rb_update(rb_buffer_t *buffer,
	igd_command_t *addr)
{
	return 0;
}
#endif /* CONFIG_CMD */
#endif

#endif /* _RB_H */

/*----------------------------------------------------------------------------
 * File Revision History
 * $Id: rb.h,v 1.7 2010/08/06 17:50:21 rclovrie Exp $
 * $Source: /nfs/fm/proj/eia/cvsroot/koheo/linux/egd_drm/emgd/include/rb.h,v $
 *----------------------------------------------------------------------------
 */
