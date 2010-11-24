/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: sdvo_hdmi.h
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
 *  Main include file for SDVO port driver HDMI interface function
 *-----------------------------------------------------------------------------
 */

#ifndef _SDVO_PORT_HDMI_H_
#define _SDVO_PORT_HDMI_H_

#include <config.h>
#include <igd_pd.h>
#include <pd.h>
#include <pd_print.h>
#include "sdvo_port.h"
#include "sdvo_intf.h"

/* VBios abstraction macro */
#if !defined(CONFIG_MICRO)
#define SDVO_HDMI
#endif


#if defined(SDVO_HDMI)

#define SDVO_HDMI_ELD_BUFFER_SIZE			256
#define SDVO_HDMI_AVI_BUFFER_SIZE			17
#define SDVO_HDMI_SPD_BUFFER_SIZE			29
#define	SDVO_HDMI_ELD_BUFFER				0			/* ELD buffer index */
#define SDVO_HDMI_AVI_BUFFER				1			/* AVI buffer index */
#define SDVO_HDMI_SPD_BUFFER				2			/* SPD buffer index */
#define SDVO_HDMI_ELD_INFO_TYPE				0x00		/* ELD buffer type */
#define SDVO_HDMI_AVI_INFO_TYPE				0x82		/* AVI buffer type */
#define SDVO_HDMI_SPD_INFO_TYPE				0x83		/* SPD buffer type */
#define SDVO_HDMI_AVI_BUFFER_SIZE			17
#define SDVO_HDMI_TRANSMIT_DISABLE			0x00
#define SDVO_HDMI_TRANSMIT_ONCE				0x80
#define SDVO_HDMI_TRANSMIT_EVERY			0xC0

#define SDVO_HDMI_VENDOR_NAME				"Intel"
#define SDVO_HDMI_VENDOR_DESCRIPTION		"IEGD Driver"
#define SDVO_HDMI_INTEL_VENDOR_NAME_SIZE		6
#define SDVO_HDMI_IEGD_VENDOR_DESCRIPTION_SIZE	12

#define SDVO_HDMI_VENDOR_NAME_SIZE			8
#define SDVO_HDMI_VENDOR_DESCRIPTION_SIZE	16
#define SDVO_HDMI_SPD_SOURCE_PC				0x09

#define DVI_MODE	0
#define HDMI_MODE	1
sdvo_status_t sdvo_hdmi_transmitter(sdvo_device_context_t *p_context);
sdvo_status_t sdvo_hdmi_support(void *p_context);
sdvo_status_t sdvo_hdmi_audio_characteristic(sdvo_device_context_t *p_context);
sdvo_status_t sdvo_hdmi_configure(sdvo_device_context_t *p_ctx);
sdvo_status_t sdvo_hdmi_pr_and_color(sdvo_device_context_t *p_context);
sdvo_status_t sdvo_hdmi_send_eld(sdvo_device_context_t *p_ctx);
sdvo_status_t sdvo_hdmi_avi_info_frame(sdvo_device_context_t *p_context);
sdvo_status_t sdvo_hdmi_spd_info_frame(sdvo_device_context_t *p_context);
sdvo_status_t sdvo_hdmi_write_buffer
	(sdvo_device_context_t *p_ctx,unsigned char index, 
	unsigned char offset, unsigned char *input, int len);

typedef union
{
	unsigned char value;
	struct {
		unsigned char eld_valid: 1;
		unsigned char presense_detect: 1;
		unsigned char cp_ready: 1;
		unsigned char reserved: 5;
	};
} sdvo_audio_state_t;
/* AVI Info Frames version 2 */
typedef struct
{
	unsigned char type;
	unsigned char version;
	unsigned char length;
	unsigned char chksum;
} sdvo_info_header_t;

typedef union
{
	unsigned char data[SDVO_HDMI_AVI_BUFFER_SIZE];
	struct {
		sdvo_info_header_t	header;
		union {
			unsigned char data1;
			struct {
				unsigned char scan_info: 2;
				unsigned char bar_info: 2;
				unsigned char active_format: 1;
				unsigned char color_space: 2;
				unsigned char reserved1: 1;
			};
		};
		union {
			unsigned char data2;
			struct {
				unsigned char format_aspect_ratio: 4;
				unsigned char pic_aspect_ratio: 2;
				unsigned char colorimetry: 2;
			};
		};
		union {
			unsigned char data3;
			struct {
				unsigned char pic_scaling: 2;
				unsigned char reserved2: 6;
			};
		};
		union {
			unsigned char data4;
			struct {
				unsigned char video_id_code: 7;
				unsigned char reserved3: 1;
			};
		};
		union {
			unsigned char data5;
			struct {
				unsigned char pixel_rep: 4;
				unsigned char reserved4: 4;
			};
		};
		unsigned char bar1;
		unsigned char bar2;
		unsigned char bar3;
		unsigned char bar4;
		unsigned char bar5;
		unsigned char bar6;
		unsigned char bar7;
		unsigned char bar8;
	};
} sdvo_avi_info_t;

typedef union
{
	unsigned char data[SDVO_HDMI_SPD_BUFFER_SIZE];
	struct {
		sdvo_info_header_t	header;
		unsigned char vendor_name[SDVO_HDMI_VENDOR_NAME_SIZE];
		unsigned char product_desc[SDVO_HDMI_VENDOR_DESCRIPTION_SIZE];
		unsigned char source_device;
	};
} sdvo_spd_info_t;


#define SDVO_INIT_HDMI(a)			sdvo_hdmi_audio_characteristic(a)
#define SDVO_IS_HDMI_SUPPORTED(a)	sdvo_hdmi_support(a)
#define SDVO_CONFIGURE_HDMI(a)		sdvo_hdmi_configure(a)
#else
#define SDVO_INIT_HDMI(a)			
#define SDVO_IS_HDMI_SUPPORTED(a)		SS_NOT_SUPPORTED
#define SDVO_CONFIGURE_HDMI(a)		
#endif  /* SDVO_HDMI */

#endif  /*  _SDVO_PORT_HDMI_H_ */
