/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_gart.h
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

#ifndef _IGD_GART_H_
#define _IGD_GATR_H_

typedef struct _gtt_info {
	void* virt_mmadr;
	void* virt_gttadr;
	void* virt_gttadr_upper;

	unsigned long new_gtt;
	unsigned long gtt_phyadr;
	unsigned long is_virt_aperture;
	unsigned long reset_gtt_entries;
	unsigned long fb_phys_addr;
	unsigned long scratch_phys;
	
	unsigned long num_gtt_entries;
	unsigned long gtt_entry_start;
	unsigned long gtt_entry_end;
	unsigned long num_contig_allocs;
	unsigned char **cont_pages_virts;
	/* FIXME!!! - this cant handle 64-bit Architecture*/
	unsigned long *cont_pages_phys;
	unsigned long *cont_pages_sizes;
#ifdef D3D_DPM_ALLOC
   void* virt_gttadr_dpm;
#endif
}gtt_info_t;

/*
 * Note: Platforms extend this data structure so the pointer can be used
 * as either this DI dispatch or cast to the DD dipatch.
 */
typedef struct _init_gart_dispatch {
	int (*get_gtt_ctl)(void* gtt_info);
	int (*init_gtt_table)(void* gtt_info);
	int (*flush_gtt_tlb)(void* gtt_info);
	int (*shutdown_gtt)(void* gtt_info);
} init_gart_dispatch_t;

void* igd_get_gtt_dispatch(unsigned long dev_id);
int igd_get_gtt_ctl(void* gtt_info, unsigned long dev_id);
int igd_init_gtt(void* gtt_info, unsigned long dev_id);
int igd_flush_gtt(void* gtt_info, unsigned long dev_id);
int igd_shutdown_gtt(void* gtt_info, unsigned long dev_id);

#endif
