/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: memmap.c
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
 *  This file contains the XFree86 implementations of the OAL
 *  memory.h abstractions.
 *-----------------------------------------------------------------------------
 */
#include <io.h>

#ifndef _OAL_LINUX_KERNEL_IO_MEMMAP_H
#define _OAL_LINUX_KERNEL_IO_MEMMAP_H


void * os_map_io_to_mem_nocache(
				unsigned long base_address,
				unsigned long size
				)
{
  return ioremap(base_address, size);
}

void os_unmap_io_from_mem(
			  void * virt_addr,
			  unsigned long size
			  )
{
  iounmap(virt_addr);
}


#endif
