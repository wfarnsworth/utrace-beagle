/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_interrupt.h
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
 *  The is the IGD exported interrupt access functions. It should be included
 *  by client drivers making use of interrupt functionality of IGD.
 *  This file Should NOT be included by any IGD modules because in some
 *  IGD environments the interrupt module will not be available.
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_INTERRUPT_H
#define _IGD_INTERRUPT_H

#include <igd_mode.h>

typedef struct _oal_callbacks {

	void (*spin_lock_irqsave)(void *lock);
	void (*spin_unlock_irqrestore)(void *lock);
	void (*spin_lock_isr)(void *lock);
	void (*spin_unlock_isr)(void *lock);
	void (*spin_lock)(void *lock);
	void (*spin_unlock)(void *lock);
} oal_callbacks_t;

#define CB_FUNC(a, b, c) if(a && a->b) { a->b(c); }

/* Responses returned to the client from drm */
#define INT_INVALID  -1
#define INT_NOOP      0
#define INT_CLEARED   1
#define INT_HANDLED   2
#define INT_READ      3
#define INT_STORED    4
#define INT_TIMEOUT   5

/* Response from the ISR helper to the ISR routine */
#define ISR_NEED_DPC  0
#define ISR_HANDLED   1
#define ISR_NOT_OURS  2

typedef struct _interrupt_data {

	void *irqmask_lock;

	unsigned char *msvdx_reg;
	unsigned long sgx_irq_mask;
	unsigned long sgx_irq_mask2;
	unsigned long vdc_irq_mask;
	unsigned long msvdx_irq_mask;
	int irq_enabled;

	/* condition to wake up on */
	unsigned int event_present;

	/* interrupts that have already occured */
	unsigned int out_vdc;

	unsigned int out_sgx;
	unsigned int out_sgx2;

	unsigned int out_mtx;
} interrupt_data_t;


/*----------------------------------------------------------------------
 * Typedef: igd_interrupt_handler_t
 *
 * Description:
 *  This function type is used for OS independent interrupt handlers
 *  that will be called by the hal to handle a requested interrupt.
 *
 * Members:
 *
 *----------------------------------------------------------------------
 */
typedef void (igd_interrupt_handler_t)(unsigned long type,
	void *call_data,
	void *user_data);


/*----------------------------------------------------------------------
 * Typedef: igd_interrupt_t
 *
 * Description:
 *  An opaque handle to identify an interrupt to be handled
 *
 * Members:
 *
 *----------------------------------------------------------------------
 */
typedef void * igd_interrupt_t;

#define IGD_INTERRUPT_VBLANK 0x1
#define IGD_INTERRUPT_SYNC   0x2

/*----------------------------------------------------------------------
 * Function:
 *  isr_helper
 *
 * Description:
 *  This function helps the OAL/DRM module in doing all chipset specific
 *  functionality like register sets when an ISR is fired
 * Parameters:
 *	void
 * Returns:
 *  int - 0 on the interrupt was handled and we need to queue a DPC for it
 *      - 1 on the interrupt was handled but wasn't one to do further
 *          processing on
 *      - 2 on failure
 *----------------------------------------------------------------------
 */
int isr_helper(void);

/*----------------------------------------------------------------------
 * Function:
 *  unmask_int_helper
 *
 * Description:
 *  This function helps the OAL/DRM module in unmasking the Interrupt
 *  registers for a particular chipset so that the Interrupts can start
 *  firing
 * Parameters:
 *	void
 * Returns:
 *  int - 0 on SUCCESS
 *      - 1 on FAILURE
 *----------------------------------------------------------------------
 */
int unmask_int_helper(void);

/*----------------------------------------------------------------------
 * Function:
 *  mask_int_helper
 *
 * Description:
 *  This function helps the OAL/DRM module in masking the Interrupt
 *  registers for a particular chipset so that the Interrupts can stop
 *  firing
 * Parameters:
 *	void
 * Returns:
 *  int - 0 on SUCCESS
 *      - 1 on FAILURE
 *----------------------------------------------------------------------
 */
int mask_int_helper(void);

/*----------------------------------------------------------------------
 * Function:
 *  request_int_info_helper
 *
 * Description:
 *  This function helps the OAL module to request interrupt information 
 *  and status
 * Parameters:
 *	void *int_info_data 
 * Returns:
 *  int -  1 on Interrupt events supported and previous events occured
 *      -  0 on Interrupt events supported but no previous events occured
 *      - -1 on FAILURE or Interrupt events type not supported
 *----------------------------------------------------------------------
 */
int request_int_info_helper(void *int_info_data);

/*----------------------------------------------------------------------
 * Function:
 *  clear_occured_int_helper
 *
 * Description:
 *  This function helps the OAL module to request interrupt information 
 *  and status
 * Parameters:
 *	void *int_info_data 
 * Returns:
 *  void
 *----------------------------------------------------------------------
 */
void clear_occured_int_helper(void *int_info_data);

/*----------------------------------------------------------------------
 * Function:
 *  mask_int_helper
 *
 * Description:
 *  This function helps the OAL/DRM module in clearing the cached copy
 *  of Interrupt data
 * Parameters:
 *	void
 * Returns:
 *	void
 *----------------------------------------------------------------------
 */
void clear_interrupt_cache(void);

/*----------------------------------------------------------------------
 * Function:
 *  dpc_helper
 *
 * Description:
 *  This function helps the OAL/DRM module in doing all chipset specific
 *  functionality like register sets when an DPC is fired
 * Parameters:
 *  interrupt_data_t **int_data
 * Returns:
 *  int - 0 on SUCCESS
 *      - 1 on FAILURE
 *----------------------------------------------------------------------
 */
int dpc_helper(interrupt_data_t **int_data);


/*----------------------------------------------------------------------
 * Function:
 *  interrupt_init
 *
 * Description:
 *  This function initializees the interrupt helper module
 * Parameters:
 *  unsigned short did - Device ID for main video device
 *  oal_callbacks_t *oal_callbacks_table - Callback for
 *              spin lock related functions
 * Returns:
 *  int - 0 on SUCCESS
 *      - 1 on FAILURE
 *----------------------------------------------------------------------
 */
int interrupt_init(unsigned short did,
	oal_callbacks_t *oal_callbacks_table);

/*----------------------------------------------------------------------
 * Function:
 *  pre_init_interrupt
 *
 * Description:
 *  This function helps the OAL/DRM module in doing all chipset specific
 *  functionality like register sets before an ISR is initialized
 * Parameters:
 *  unsigned char *virt_mmadr - The MMIO base address
 * Returns:
 *  void
 *----------------------------------------------------------------------
 */
void pre_init_interrupt(unsigned char *virt_mmadr);

/*----------------------------------------------------------------------
 * Function:
 *  post_init_interrupt
 *
 * Description:
 *  This function helps the OAL/DRM module in doing all chipset specific
 *  functionality like register sets after an ISR is initialized
 * Parameters:
 *  unsigned char *virt_mmadr - The MMIO base address
 * Returns:
 *  void
 *----------------------------------------------------------------------
 */
void post_init_interrupt(unsigned char *virt_mmadr);

/*----------------------------------------------------------------------
 * Function:
 *  uninstall_interrupt
 *
 * Description:
 *  This function helps the OAL/DRM module in doing all chipset specific
 *  functionality like register sets for removing Interrupt support
 * Parameters:
 *  unsigned char *virt_mmadr - The MMIO base address
 * Returns:
 *  void
 *----------------------------------------------------------------------
 */
void uninstall_interrupt(void);

#endif
