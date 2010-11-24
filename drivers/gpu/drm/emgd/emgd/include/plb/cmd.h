/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: cmd.h
 * $Revision: 1.9 $
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
 *  Device dependent header file for the command interface for poulsbo
 *  devices.
 *-----------------------------------------------------------------------------
 */

#ifndef _PLB_CMD_H
#define _PLB_CMD_H

#include <io.h>
#include <sched.h>

#include <instr_common.h>
#include <utils.h>

//#define TMP_PLB_SERIALIZE_2D
//#define TMP_PLB_SERIALIZE_RASTER
//#define TMP_PLB_SERIALIZE_BINNER
#define CONFIG_ENABLE_SYNC_SLEEP 0
#define CONFIG_ENABLE_CPU_SYNC 0
#define CONFIG_ENABLE_DIRECT_2D 1
#define CONFIG_ENABLE_DIRECT_BIN 1
#define CONFIG_ENABLE_DIRECT_VIDEO 1


#define CMD_QUEUE_SIZE_PLB (1024*128)
#define MAX_2D_COMMAND_PLB 0x60

/* Wait at most 2 second for a 2D, 3D, or Video operation to complete */
#define CMD_TIMEOUT_PLB 2000

/*
 * Bitfield to track which engines are possibly busy and in need
 * of sync.
 */
#define CMD_ENGINE_2D_PLB     0x01
#define CMD_ENGINE_BINNER_PLB 0x02
#define CMD_ENGINE_RASTER_PLB 0x04
#define CMD_ENGINE_VIDEO_PLB  0x08
#define CMD_ENGINE_CPU_PLB    0x10
#define CMD_ENGINE_WAIT_PLB   0x20
#define CMD_ENGINE_DPM_PLB    0x40
#define CMD_ENGINE_ALL_PLB    0x7f

typedef unsigned long cmd_engine_plb_t;

/*
 * Virtual Commands for the PLB Virtual Engine.
 * Note: They are numbered such that they are unlikely to happen in
 * a command stream and should then be easily spotted during debug.
 *
 * There is a special relationship between the 3D and RASTER numbers.
 * The command packet for these two is the same and the command is either
 * a binner + raster (3D) or just a raster alone (RASTER).
 * Sometimes the binner is processed out of order and the command ID is
 * converted from 3D to raster by or'ing in the extra bit.
 */
#define VCOMMAND_2D_PLB          0x12300000
#define VCOMMAND_3D_PLB          0x12310000
#define VCOMMAND_RASTER_PLB      0x12330000
#define VCOMMAND_VIDEO_PLB       0x12340000
#define VCOMMAND_REG_PLB         0x12350000
#define VCOMMAND_WAIT_PLB        0x12360000
#define VCOMMAND_SYNC_PLB        0x12370000
#define VCOMMAND_SW2D_PLB        0x12380000
#define VCOMMAND_EXIT_PLB        0x123e0000
#define VCOMMAND_WRAP_PLB        0x123f0000
#define VCOMMAND_ID_MASK_PLB     0xffff0000
#define VCOMMAND_SIZE_MASK_PLB   0x0000ffff

#define CMD_SYNC_NEED_IDLE_PLB (CMD_ENGINE_RASTER_PLB | CMD_ENGINE_DPM_PLB | \
		CMD_ENGINE_VIDEO_PLB | CMD_ENGINE_WAIT_PLB | CMD_ENGINE_2D_PLB)

#define CMD_2D_NEED_IDLE_PLB (CMD_ENGINE_RASTER_PLB | \
		CMD_ENGINE_VIDEO_PLB | CMD_ENGINE_WAIT_PLB)

#define CMD_BINNER_NEED_IDLE_PLB (CMD_ENGINE_BINNER_PLB | CMD_ENGINE_2D_PLB)

#define CMD_RASTER_NEED_IDLE_PLB (CMD_ENGINE_2D_PLB | CMD_ENGINE_VIDEO_PLB | \
		CMD_ENGINE_BINNER_PLB | CMD_ENGINE_RASTER_PLB | CMD_ENGINE_DPM_PLB | \
		CMD_ENGINE_WAIT_PLB)

#define CMD_VIDEO_NEED_IDLE_PLB (CMD_ENGINE_WAIT_PLB)

#define CMD_REG_NEED_IDLE_PLB (CMD_ENGINE_RASTER_PLB | CMD_ENGINE_DPM_PLB | \
		CMD_ENGINE_2D_PLB | CMD_ENGINE_VIDEO_PLB | CMD_ENGINE_WAIT_PLB)

#define CMD_CPU_NEED_IDLE_PLB (CMD_ENGINE_RASTER_PLB | CMD_ENGINE_DPM_PLB | \
		CMD_ENGINE_2D_PLB | CMD_ENGINE_VIDEO_PLB | CMD_ENGINE_WAIT_PLB)

#define CMD_WAIT_NEED_IDLE_PLB (CMD_ENGINE_WAIT_PLB)

/*
 * wait_flags
 * Flags to pass with the VCOMMAND_WAIT_PLB commands
 */
/*#define CMD_WAIT_VBLANK_PLB   1*/
/*#define CMD_WAIT_SCANLINE_PLB 2*/
#define CMD_WAIT_FLIP_A_PLB   4
#define CMD_WAIT_FLIP_B_PLB   8
#define CMD_WAIT_OVL_PLB      0x10
#define CMD_WAIT_OVL2_PLB     0x20
#define CMD_WAIT_VIDEO_SYNC_PLB 0x40

#define CMD_SW2D_SRC_COPY_BLT   1

typedef struct _cmd_queue_plb {
	/* 2D HW access */
	struct {
		unsigned char *avail_reg;
		unsigned char *status_reg;
		igd_command_t *base;
		igd_command_t *end;
		volatile unsigned int avail;
	} blt;

	/* Registers - Set at init*/
	unsigned char *event_status_reg;
	unsigned char *event_enable_reg;
	unsigned char *event_clear_reg;
	unsigned char *event_status2_reg;
	unsigned char *event_enable2_reg;
	unsigned char *event_clear2_reg;
	unsigned char *mtx_status_reg;
	unsigned long msvdx_fence;
	unsigned long msvdx_last_fence;
	/* HW status page virtual addr */
	volatile unsigned char *sync;

	/* Virtual command queue - accessed by both threads */
	volatile igd_command_t vqueue[CMD_QUEUE_SIZE_PLB];
	volatile igd_command_t * volatile head;
	volatile igd_command_t * volatile tail;
  	volatile igd_command_t * current_node;
	volatile igd_command_t * reservation;

	/* Only for main thread */
	unsigned long last_sync;

	/* Check lock */
	volatile igd_command_t * volatile last_head_value;
	volatile os_alarm_t last_head_time;

	/* Process thread */

	/* Accessed by both main thread and process thread */
	unsigned long wait_flags;
	volatile cmd_engine_plb_t busy_engines;

	igd_appcontext_h appcontext;
	struct _igd_context *context;

	/* Flag used by the main thread in cmd_reserve when
	 * a 2d instruction is being written directly into
	 * the hardware.
	 * Can only be set if is_thread_waiting = 1.
	 * Purpose is for update to know this is a 2d instr
	 * directly to the HW.
	 */
	int direct_access_2d;

	/* Mutex/Conditions */
	/* The process thread will set this to 1 when it is
	 * sleeping and the main thread will set to 0 when awake
	 */
	volatile int is_thread_waiting;
	os_pthread_mutex_t thread_mutex;
	os_pthread_cond_t  thread_waiting;

	/*
	 * The main thread will sleep on the sync_waiting condition variable
	 * when waiting for a sync tom complete. The sync_waiting_id will
	 * identify the sync number that the main thread is waiting for.
	 */
	volatile unsigned long sync_waiting_id;
	volatile int sync_thread_waiting;
	os_pthread_cond_t sync_waiting_cond;

	/* This protects main thread and process thread when calling
	 * check_lock_plb.
	 */
	os_pthread_mutex_t check_lock_mutex;
} cmd_queue_plb_t;

#if 0  /* Removing all the command vqueue stuff */
extern os_pthread_t *cmd_vqueue_thread_plb;
extern void *process_vqueue_plb(void *data);

#define CMD_GET_QUEUE_PLB(d, p) \
	((cmd_queue_plb_t *)((igd_display_pipe_t *)			\
		((igd_display_context_t *)d)->pipe)->queue[p])

/*
 * This is a clever trick so that we get inlined functions for normal
 * builds and a single instance of this function for debug builds.
 */
#if !defined(DEBUG_BUILD_TYPE) || defined(IS_CMD_PLB_C)
OPT_DEBUG_INLINE int cmd_reserve_plb(cmd_queue_plb_t *queue,
	unsigned long size,
	igd_command_t type)
{
	volatile igd_command_t *needed_start;
	volatile igd_command_t *needed_end;
	int first = 1;
	int expired = 0;
//	int wrap = 0;
	os_alarm_t timeout = (os_alarm_t)0;

	EMGD_TRACE_ENTER;

	/* Since this is not a 2d instruction, ensure update knows this */
	queue->direct_access_2d = 0;

	/*
	 * Always leave space for 1 extra command so that we can put
	 * the wrap command in without waiting on the head. Also remember
	 * to leave space at the end of the queue.
	 */
	needed_start = queue->tail;
	needed_end = queue->tail + size + 2;
	if(needed_end >= &queue->vqueue[CMD_QUEUE_SIZE_PLB]) {
		/* Doesn't fit so wrap to beginning */
		needed_start = queue->vqueue;
		needed_end = queue->vqueue + size + 2;
		*queue->tail = VCOMMAND_WRAP_PLB;
		//wrap = 0;
	}

	while(1) {
		if((queue->head <= needed_start) ||
			(queue->head >= needed_end)) {
			//if(wrap) {
			//	queue->tail = queue->vqueue;
			//}
			*needed_start++ = type | size;
			queue->current_node = needed_start;
			queue->reservation = needed_start + size;
			EMGD_TRACE_EXIT;
			return 0;
		}
		if(first) {
			timeout = OS_SET_ALARM(CMD_TIMEOUT_PLB);
			first = 0;
		}
		if(expired) {
			break;
		}
		OS_SCHEDULE();
		expired = OS_TEST_ALARM(timeout);
	}

	EMGD_ERROR_EXIT("Timeout waiting for Virtual Queue Space");
	return -IGD_ERROR_BUSY;
}
#else
extern int cmd_reserve_plb(cmd_queue_plb_t *queue,
	unsigned long size, igd_command_t type);
#endif

extern int cmd_ready_plb(cmd_queue_plb_t *queue, cmd_engine_plb_t need_idle);

#if !defined(DEBUG_BUILD_TYPE) || defined(IS_CMD_PLB_C)
OPT_DEBUG_INLINE int cmd_update_plb(cmd_queue_plb_t *queue)
{
	int ret;

	EMGD_ASSERT(queue, "Null Queue", -IGD_ERROR_INVAL);
	EMGD_ASSERT(queue->current_node <= queue->reservation,
		"Queue use exceeds reservation", -IGD_ERROR_INVAL);

	/*
	 * If the queue is set up for direct access then fire off the
	 * blit engine and return.
	 */
	if(queue->direct_access_2d) {
		unsigned int tmp;
		/*
		 * Need to read the last dword back to trigger the blit engine.
		 */
		tmp = EMGD_READ32(queue->blt.end - 1);
		queue->current_node = NULL;
		queue->reservation = NULL;

#ifdef TMP_PLB_SERIALIZE_2D
		cmd_ready_plb(queue, CMD_CPU_NEED_IDLE_PLB);
#endif

		EMGD_TRACE_EXIT;
		return 0;
	}


	/*
	 * Commands were placed in the ring so move the tail. Then if we
	 * have threads signal the ring thread to go. If we don't have
	 * threads we will just process the commands that were placed in the
	 * ring.
	 */
	ret = OS_PTHREAD_MUTEX_LOCK(&queue->thread_mutex);
	queue->tail = queue->current_node;

	/*
	 * Null these out so that any invalid uses will get caught
	 */
	queue->current_node = NULL;
	queue->reservation = NULL;

	if(cmd_vqueue_thread_plb) {
			queue->is_thread_waiting = 0;
		ret = OS_PTHREAD_COND_SIGNAL(&queue->thread_waiting);
		OS_PTHREAD_MUTEX_UNLOCK(&queue->thread_mutex);
	} else {
		OS_PTHREAD_MUTEX_UNLOCK(&queue->thread_mutex);
		/* For syncronous use */
		process_vqueue_plb(queue);
	}

	return 0;
}
#else
extern int cmd_update_plb(cmd_queue_plb_t *queue);
#endif

/*
 * 2D Engine has a on-chip queue. As long as there is space
 * in the queue the 2d commands can be written starting at the
 * base register.
 *
 * 2D Engine runs asynchronously with other engines so for IEGD
 * we ensure that other engines are idle when inserting 2d commands.
 */
static __inline int cmd_2d_direct_reserve_plb(cmd_queue_plb_t *queue,
	unsigned int size)
{
	int ret;
	os_alarm_t timeout = (os_alarm_t)0;
	int expired = 0;
	int first = 1;

	EMGD_TRACE_ENTER;
	EMGD_ASSERT(queue, "Null Queue", -IGD_ERROR_INVAL);
	EMGD_ASSERT( size < MAX_2D_COMMAND_PLB, "2D Command too large",
		-IGD_ERROR_INVAL);

	queue->direct_access_2d = 1;

	if(queue->busy_engines & CMD_2D_NEED_IDLE_PLB) {
		ret = cmd_ready_plb(queue, CMD_2D_NEED_IDLE_PLB);
		/* Do not return if cmd_ready_plb returns an error.
		 * this may be a sync and not putting it in the command queue
		 * will cause problems.  Since the failure was on a previous
		 * command, this should be ok.
		if(ret) {
			return ret;
		}*/
	}

	queue->busy_engines |= CMD_ENGINE_2D_PLB;

	queue->current_node = queue->blt.base;
	queue->blt.end = queue->blt.base + size;
	queue->reservation = queue->blt.end;
	if (size <= queue->blt.avail) {
		queue->blt.avail -= size;
		EMGD_TRACE_EXIT;
		return 0;
	}
	while(1) {
		queue->blt.avail = EMGD_READ32(queue->blt.avail_reg);
		if(size <= queue->blt.avail) {
			break;
		}
		if(first) {
			timeout = OS_SET_ALARM(CMD_TIMEOUT_PLB);
			first = 0;
		}
		if(expired) {
			EMGD_ERROR_EXIT("Timeout waiting for 2D Hardware");
			return -IGD_ERROR_HWERROR;
		}
		expired = OS_TEST_ALARM(timeout);
	}
	queue->blt.avail -= size;

	EMGD_TRACE_EXIT;
	return 0;
}

/*
 * Reserve Space for a 2D command. This function will set up the
 * queue to directly send the 2d command to the hardware when there
 * are no engines to wait for and will instead set up the queue to
 * put the 2d command in the virtual ring buffer when we would
 * have to wait.
 * In this manner we get the benefit of direct command placement
 * with 0 latency when we can use it and non-blocking behavior
 * always.
 */
#if !defined(DEBUG_BUILD_TYPE) || defined(IS_CMD_PLB_C)
OPT_DEBUG_INLINE int cmd_2d_reserve_plb(cmd_queue_plb_t *queue,
	unsigned int size)
{
	int ret;

	EMGD_TRACE_ENTER;
	EMGD_ASSERT(queue, "Null Queue", -IGD_ERROR_INVAL);
	EMGD_ASSERT( size < MAX_2D_COMMAND_PLB, "2D Command too large",
		-IGD_ERROR_INVAL);

	/*
	 * Only do a direct reserve of the 2D command if the virtual queue
	 * is empty AND this won't have to wait for another engine
	 * to complete.  Otherwise this stalls waiting on that engine.
	 */
	if(CONFIG_ENABLE_DIRECT_2D && (queue->is_thread_waiting == 1) &&
			!(queue->busy_engines & CMD_2D_NEED_IDLE_PLB)) {
		ret = cmd_2d_direct_reserve_plb(queue, size);
		EMGD_TRACE_EXIT;
		return ret;
	}

	ret = cmd_reserve_plb(queue, size, VCOMMAND_2D_PLB);
	EMGD_TRACE_EXIT;
	return ret;
}
#else
extern int cmd_2d_reserve_plb(cmd_queue_plb_t *queue,
	unsigned int size);
#endif

#define CMD_2D_RESERVE_PLB(q, s) cmd_2d_reserve_plb(q, s)
#define CMD_2D_WRITE_PLB(q, dw) INSTR_WRITE(dw, q->current_node)
#define CMD_2D_UPDATE_PLB(q) cmd_update_plb(q)


/*
 * The sync command uses the 2D engine directly when there are no
 * dependent engines running. Otherwise it puts a sync command in the
 * vqueue which is processed using the CPU in the cmd thread.
 */
#if !defined(DEBUG_BUILD_TYPE) || defined(IS_CMD_PLB_C)
OPT_DEBUG_INLINE int cmd_sync_reserve_plb(cmd_queue_plb_t *queue,
	unsigned int size)
{
	int ret;

	EMGD_TRACE_ENTER;
	EMGD_ASSERT(queue, "Null Queue", -IGD_ERROR_INVAL);
	EMGD_ASSERT( size < MAX_2D_COMMAND_PLB, "2D Command too large",
		-IGD_ERROR_INVAL);

	/*
	 * Only do a direct reserve of the sync if the virtual queue
	 * is empty AND this won't have to wait for another engine
	 * to complete.  Otherwise this stalls waiting on that engine.
	 */
	if((queue->is_thread_waiting == 1) &&
			!(queue->busy_engines & CMD_2D_NEED_IDLE_PLB)) {
		ret = cmd_2d_direct_reserve_plb(queue, size);
		EMGD_TRACE_EXIT;
		return ret;
	}

	ret = cmd_reserve_plb(queue, size, VCOMMAND_SYNC_PLB);
	EMGD_TRACE_EXIT;
	return ret;
}
#else
extern int cmd_sync_reserve_plb(cmd_queue_plb_t *queue);
#endif

#define CMD_SYNC_RESERVE_PLB(q, s) cmd_sync_reserve_plb(q, s)
#define CMD_SYNC_WRITE_PLB(q, dw) INSTR_WRITE(dw, q->current_node)
#define CMD_SYNC_UPDATE_PLB(q) cmd_update_plb(q)
#endif


#endif
