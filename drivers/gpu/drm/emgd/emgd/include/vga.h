/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: vga.h
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
 *  Header file for common VGA registers and macros.
 *-----------------------------------------------------------------------------
 */

#ifndef _HAL_VGA_H
#define _HAL_VGA_H

#include <igd_vga.h>
#include <io.h>

extern void program_pipe_vga(
	igd_display_context_t *display,
	igd_timing_info_t *timings);

extern void program_plane_vga(
	igd_display_context_t *display,
	igd_timing_info_t *timings);

extern unsigned long get_vga_color(int i);

extern void set_256_palette(unsigned char *mmio);

extern unsigned char vga_port_offset;

#define READ_VGA(mmio, port, index, data) \
  EMGD_WRITE8((unsigned char)index, EMGD_MMIO(mmio) + port); \
  data = EMGD_READ8(EMGD_MMIO(mmio) + port + 1);

#define WRITE_VGA(mmio, port, index, data) \
  EMGD_WRITE8(index, EMGD_MMIO(mmio) + port); \
  EMGD_WRITE8(data, EMGD_MMIO(mmio) + port + 1); \
  EMGD_DEBUG("0x%lx (0x%lx): 0x%lx", (unsigned long) port, \
		  (unsigned long) index, (unsigned long) data);

#define READ_AR(mmio, index, data) \
 { \
	 unsigned char tmp; \
	 tmp = EMGD_READ8(EMGD_MMIO(mmio) + ST01); \
     EMGD_WRITE8(index, EMGD_MMIO(mmio) + AR_PORT); \
     data = EMGD_READ8(EMGD_MMIO(mmio) + ARX_DATA_R); \
	 tmp = EMGD_READ8(EMGD_MMIO(mmio) + ST01); \
 }

#define WRITE_AR(mmio, index, data) \
 { \
    unsigned char tmp; \
	tmp = EMGD_READ8(EMGD_MMIO(mmio) + ST01); \
	EMGD_WRITE8(index, EMGD_MMIO(mmio) + AR_PORT); \
    EMGD_WRITE8(data, EMGD_MMIO(mmio) + AR_PORT); \
	EMGD_WRITE8(0x20, EMGD_MMIO(mmio) + AR_PORT); \
	tmp = EMGD_READ8(EMGD_MMIO(mmio) + ST01); \
}

/* Status registers */
#define ST00 0x3C2
#define ST01 (0x3BA + vga_port_offset)

/* Sequencer Registers */
#define SR_PORT   0x3c4
#define SRX_INDEX 0x3C4   /* Index port */
#define SRX_DATA  0x3C5   /* Data port */

/* Graphics Registers */
#define GR_PORT   0x3ce
#define GRX_INDEX 0x3CE   /* Index port */
#define GRX_DATA  0x3CF   /* Data port */

/* Attribute Controlller Registers */
#define AR_PORT    0x3c0
#define ARX_INDEX  0x3C0   /* Index port */
#define ARX_DATA_R 0x3C1   /* Data port read */
#define ARX_DATA_W 0x3C0   /* Data port write */

/* CRTC Registers */
#define CR_PORT   (0x3b4 + vga_port_offset)
#define CRX_INDEX (0x3b4 + vga_port_offset)  /* Index port */
#define CRX_DATA (0x3b5 + vga_port_offset)  /* Data port */


#endif
