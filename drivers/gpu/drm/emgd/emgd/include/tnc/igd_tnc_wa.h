/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: igd_tnc_wa.h
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
 *  This header file contains the Device Dependent information used with
 *  the IEGD HAL for the Atom E6xx family of supported chips.
 *  Note: This file should be included into a C file as <tnc/igd_tnc_wa.h> and
 *  not <igd_tnc_wa.h> this will insure that multiple device dependent
 *  igd_cmd.h files can be included into a single C source.
 *-----------------------------------------------------------------------------
 */

#ifndef _IGD_TNC_WA_H
#define _IGD_TNC_WA_H

#define LNC_CLOCK 200000
#define LIMIT_TOTAL_CHECK_DISPLAY 10
#define T0 0
#define T1 1
#define WA_TUNE \
	((tnc_wa_timing_t *)&tune)
/* Graphic core Revision ID for Atom E6xx stepping */
#define TNC_A0_RID			0x2
#define TNC_B0_RID			0x3
#define SDVO_CRC_CTRL_REG	0x61050
#define SDVO_BUFF_CTRL_REG	0x61170
#define TNC_HTOTAL_TUNED	0x8000

typedef struct _tnc_wa_timing_t{
	short htotal;
	short delta;
	short flag;
	short counter;
	unsigned int crc_red;
	unsigned int crc_green;
	unsigned int crc_blue;
}tnc_wa_timing_t;

static tnc_wa_timing_t tune = {0, 0, 0, 0, 0, 0, 0,};

typedef union
{
       unsigned int pixel;
       struct
	   {
			   unsigned int bit0             :1;  
               unsigned int bit1             :1;  
               unsigned int bit2             :1;  
               unsigned int bit3             :1;  
               unsigned int bit4             :1;  
               unsigned int bit5             :1;  
               unsigned int bit6             :1;  
               unsigned int bit7             :1;  
               unsigned int bit8             :1;  
               unsigned int bit9             :1;  
               unsigned int bit10             :1;  
               unsigned int bit11             :1;  
               unsigned int bit12             :1;  
               unsigned int bit13             :1;  
               unsigned int bit14             :1;  
               unsigned int bit15             :1;  
               unsigned int bit16             :1;  
               unsigned int bit17             :1;  
               unsigned int bit18             :1;  
               unsigned int bit19             :1;  
               unsigned int bit20             :1;  
               unsigned int bit21             :1;  
               unsigned int bit22             :1;  
               unsigned int bitExtra          :1;  
               unsigned int bitRest           :8;  
       } bit;
} pixel_crc_t;


#endif