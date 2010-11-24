/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: memmap.h
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
 *  This file contains OS abstractions for memory mapping of bus addresses.
 *-----------------------------------------------------------------------------
 */

#ifndef _OAL_IO_MEMMAP_H
#define _OAL_IO_MEMMAP_H

void * os_map_io_to_mem_cache(
        unsigned long base_address,
        unsigned long size);
void * os_map_io_to_mem_nocache(
        unsigned long base_address,
        unsigned long size);
void os_unmap_io_from_mem(
        void * virt_addr,
        unsigned long size);


/*****************************************************************************
 * Function: os_map_io_to_mem_cache
 *
 * Description:
 *  This function will reserve a range of virtual memory space of "size" and 
 *  map the that virtual address to the hardware "base_address" provided. This 
 *  function call will enable caching of read write transactions to the region.
 * Parameters:
 *              IN: base_address -> the base bus/hardware address that will be
 *                                  used as the target of the memory mapping.
 *              IN: size-> the size of the virtual memory range requested to
 *                         be mapped
 * Return Value:
 *              NULL for failure OR
 *              valid virtual address casted as a void *
 *
 ****************************************************************************/
#define OS_MAP_IO_TO_MEM_CACHE(a, b)	os_map_io_to_mem_cache(a, b)

/*****************************************************************************
 * Function: os_map_io_to_mem_cache
 *
 * Description:
 *  This function will reserve a range of virtual memory space of "size" and 
 *  map the that virtual address to the hardware "base_address" provided. This 
 *  function call will NOT cache any read/write transactions to the region and 
 *  apply the access directly to the hardware bus address that is mapped.
 * Parameters:
 *              IN: base_address -> the base bus/hardware address that will be
 *                                  used as the target of the memory mapping.
 *              IN: size-> the size of the virtual memory range requested to
 *                         be mapped
 * Return Value:
 *              NULL for failure OR
 *              valid virtual address casted as a void *
 *
 ****************************************************************************/
#define OS_MAP_IO_TO_MEM_NOCACHE(a, b)	os_map_io_to_mem_nocache(a, b)
#define OS_MAP_IO_TO_LARGE_MEM_NOCACHE(a, b) os_map_io_to_mem_nocache(a, b)

/*****************************************************************************
 * Function: os_map_io_to_mem_cache
 *
 * Description:
 *  This function will unmap the range of virtual memory space of "size" that 
 *  was previously mapped with any of the above functions.
 * Parameters:
 *              IN: virt_address -> the base bus or hardware address that will
 *                                  be used as the target of the memory
 *                                  mapping.
 *              IN: size-> the size of the virtual memory range as requested in
 *                         os_map_io*
 * Return Value:
 *              none (N/A)
 *
 ****************************************************************************/
#define OS_UNMAP_IO_FROM_MEM(a, b)	os_unmap_io_from_mem(a, b)

#endif
