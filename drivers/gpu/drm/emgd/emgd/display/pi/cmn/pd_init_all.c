/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: pd_init_all.c
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
 *  This file controls the port drivers that are initialized as part of
 *  the HAL init. These must be statically linked with the HAL.
 *  NOTE: This file is visible to customers. It is used in source form as
 *  part of the vBIOS build procedure.
 *-----------------------------------------------------------------------------
 */

#include "config.h"

/*!
 * @addtogroup display_group
 * @{
 */

/* Enable Analog (CRT) port driver */
#ifdef CONFIG_LINK_PD_ANALOG
extern int analog_init(void *handle);
#define ANALOG_INIT(handle)  analog_init(handle)
#else
#define ANALOG_INIT(handle)  0
#endif

/* Enable Silicon Image 154/164 FP port driver */
#ifdef CONFIG_LINK_PD_SII164
extern int sii164_init(void *handle);
#define SII164_INIT(handle)  sii164_init(handle)
#else
#define SII164_INIT(handle)  0
#endif

/* Enable Texas Instruments 410 FP port driver */
#ifdef CONFIG_LINK_PD_TI410
extern int ti410_init(void *handle);
#define TI410_INIT(handle)  ti410_init(handle)
#else
#define TI410_INIT(handle)  0
#endif

/* Enable Chrontel 7009 TMDS & TVOut port driver */
#ifdef CONFIG_LINK_PD_CH7009
extern int ch7009_init(void *handle);
#define CH7009_INIT(handle)  ch7009_init(handle)
#else
#define CH7009_INIT(handle)  0
#endif

/* Enable National Semiconductor 2501 LVDS port driver */
#ifdef CONFIG_LINK_PD_NS2501
extern int ns2501_init(void *handle);
#define NS2501_INIT(handle)  ns2501_init(handle)
#else
#define NS2501_INIT(handle)  0
#endif

/* Enable TL955 port driver */
#ifdef CONFIG_LINK_PD_TL955
extern int tl955_init(void *handle);
#define TL955_INIT(handle)  tl955_init(handle)
#else
#define TL955_INIT(handle)  0
#endif

/* Enable Th164 port driver */
#ifdef CONFIG_LINK_PD_TH164
extern int th164_init(void *handle);
#define TH164_INIT(handle)  th164_init(handle)
#else
#define TH164_INIT(handle)  0
#endif

/* Enable FS454 port driver */
#ifdef CONFIG_LINK_PD_FS454
extern int fs454_init(void *handle);
#define FS454_INIT(handle)  fs454_init(handle)
#else
#define FS454_INIT(handle)  0
#endif

/* Enable NS387/389 port driver */
#ifdef CONFIG_LINK_PD_NS387
extern int ns387_init(void *handle);
#define NS387_INIT(handle)  ns387_init(handle)
#else
#define NS387_INIT(handle)  0
#endif

/* Enable connexant port driver */
#ifdef CONFIG_LINK_PD_CX873
extern int cx873_init(void *handle);
#define CX873_INIT(handle)  cx873_init(handle)
#else
#define CX873_INIT(handle)  0
#endif

/* Enable Internal LVDS port driver */
#ifdef CONFIG_LINK_PD_LVDS
extern int lvds_init(void *handle);
#define LVDS_INIT(handle)  lvds_init(handle)
#else
#define LVDS_INIT(handle)  0
#endif

/* Enable SDVO port driver */
#ifdef CONFIG_LINK_PD_SDVO
extern int sdvo_init(void *handle);
#define SDVO_INIT(handle)  sdvo_init(handle)
#else
#define SDVO_INIT(handle)  0
#endif

/* Enable Integrated TV port driver for NAPA */
#ifdef CONFIG_LINK_PD_TV
extern int tv_init(void *handle);
#define TV_INIT(handle)  tv_init(handle)
#else
#define TV_INIT(handle)  0
#endif

/* Enable FS460 port driver */
#ifdef CONFIG_LINK_PD_FS460
extern int fs460_init(void *handle);
#define FS460_INIT(handle)  fs460_init(handle)
#else
#define FS460_INIT(handle)  0
#endif

/* Enable FS450 port driver */
#ifdef CONFIG_LINK_PD_FS450
extern int fs450_init(void *handle);
#define FS450_INIT(handle)  fs450_init(handle)
#else
#define FS450_INIT(handle)  0
#endif

/* Enable Chrontel 7017 LVDS & TVOut port driver */
#ifdef CONFIG_LINK_PD_CH7017
extern int ch7017_init(void *handle);
#define CH7017_INIT(handle)  ch7017_init(handle)
#else
#define CH7017_INIT(handle)  0
#endif

/* Enable internal HDMI port driver */
#ifdef CONFIG_LINK_PD_HDMI
extern int hdmi_init(void *handle);
#define HDMI_INIT(handle)  hdmi_init(handle)
#else
#define HDMI_INIT(handle)  0
#endif

/*!
 * 
 * @param handle
 *
 * @return 0
 */
int pi_init_all(void *handle)
{
	int ret;

	ret = ANALOG_INIT(handle);
	ret = CH7009_INIT(handle);
	ret = SII164_INIT(handle);
	ret = NS2501_INIT(handle);
	ret = TH164_INIT(handle);
	ret = NS387_INIT(handle);
	ret = FS454_INIT(handle);
	ret = CH7017_INIT(handle);
	ret = LVDS_INIT(handle);
	ret = SDVO_INIT(handle);
	ret = TI410_INIT(handle);
	ret = TV_INIT(handle);
	ret = HDMI_INIT(handle);
	/* ret = PD000_INIT(handle); */

	return 0;
}

