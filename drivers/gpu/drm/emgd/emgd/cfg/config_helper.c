/* -*- pse-c -*-
 *-----------------------------------------------------------------------------
 * Filename: config_helper.c
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
 *  
 *-----------------------------------------------------------------------------
 */

#include <stdio.h>

#include <config.h>

int main(int argc, char **argv)
{
	char configs[] = ""
#ifdef CONFIG_MICRO
		"MICRO "
#else
		"FULL "
#endif
#ifdef CONFIG_WHT
		"WHT "
#endif
#ifdef CONFIG_ALM
		"ALM "
#endif
#ifdef CONFIG_NAP
		"NAP "
#endif
#ifdef CONFIG_GN4
		"GN4 "
#endif
#ifdef CONFIG_PLB
		"PLB "
#endif
#ifdef CONFIG_TNC
		"TNC "
#endif
#ifdef CONFIG_MODE
		"MODE "
#endif
#ifdef CONFIG_DSP
		"DSP "
#endif
#ifdef CONFIG_PI
		"PI "
#endif
#ifdef CONFIG_PD
		"PD "
#endif
#ifdef CONFIG_INIT
		"INIT "
#endif
#ifdef CONFIG_INTERRUPT
		"INTERRUPT "
#endif
#ifdef CONFIG_GART
		"GART "
#endif
#ifdef CONFIG_REG
		"REG "
#endif
#ifdef CONFIG_RESET
		"RESET "
#endif
#ifdef CONFIG_POWER
		"POWER "
#endif
#ifdef CONFIG_GMM
		"GMM "
#endif
#ifdef CONFIG_MICRO_GMM
		"MICRO_GMM "
#endif
#ifdef CONFIG_APPCONTEXT
		"APPCONTEXT "
#endif
#ifdef CONFIG_CMD
		"CMD "
#endif
#ifdef CONFIG_2D
		"2D "
#endif
#ifdef CONFIG_BLEND
		"BLEND "
#endif
#ifdef CONFIG_OVERLAY
		"OVERLAY "
#endif
#ifdef CONFIG_DECODE
		"DECODE "
#endif
		/*
		 * Port Driver Compile Options
		 */
#ifdef CONFIG_PD_ANALOG
		"PD_ANALOG "
#endif
#ifdef CONFIG_PD_SII164
		"PD_SII164 "
#endif
#ifdef CONFIG_PD_CH7009
		"PD_CH7009 "
#endif
#ifdef CONFIG_PD_TL955
		"PD_TL955 "
#endif
#ifdef CONFIG_PD_RGBA
		"PD_RGBA "
#endif
#ifdef CONFIG_PD_NS2501
		"PD_NS2501 "
#endif
#ifdef CONFIG_PD_TH164
		"PD_TH164 "
#endif
#ifdef CONFIG_PD_FS454
		"PD_FS454 "
#endif
#ifdef CONFIG_PD_NS387
		"PD_NS387 "
#endif
#ifdef CONFIG_PD_CX873
		"PD_CX873 "
#endif
#ifdef CONFIG_PD_LVDS
		"PD_LVDS "
#endif
#ifdef CONFIG_PD_FS460
		"PD_FS460 "
#endif
#ifdef CONFIG_PD_CH7017
		"PD_CH7017 "
#endif
#ifdef CONFIG_PD_TI410
		"PD_TI410 "
#endif
#ifdef CONFIG_PD_TV
		"PD_TV "
#endif
#ifdef CONFIG_PD_HDMI
		"PD_HDMI "
#endif
#ifdef CONFIG_PD_SDVO
		"PD_SDVO "
#endif
#ifdef CONFIG_PD_SOFTPD
		"PD_SOFTPD "
#endif
		/*
		 * Port Driver Link Options
		 */
#ifdef CONFIG_LINK_PD_ANALOG
		"LINK_PD_ANALOG "
#endif
#ifdef CONFIG_LINK_PD_SII164
		"LINK_PD_SII164 "
#endif
#ifdef CONFIG_LINK_PD_CH7009
		"LINK_PD_CH7009 "
#endif
#ifdef CONFIG_LINK_PD_TL955
		"LINK_PD_TL955 "
#endif
#ifdef CONFIG_LINK_PD_RGBA
		"LINK_PD_RGBA "
#endif
#ifdef CONFIG_LINK_PD_NS2501
		"LINK_PD_NS2501 "
#endif
#ifdef CONFIG_LINK_PD_TH164
		"LINK_PD_TH164 "
#endif
#ifdef CONFIG_LINK_PD_FS454
		"LINK_PD_FS454 "
#endif
#ifdef CONFIG_LINK_PD_NS387
		"LINK_PD_NS387 "
#endif
#ifdef CONFIG_LINK_PD_CX873
		"LINK_PD_CX873 "
#endif
#ifdef CONFIG_LINK_PD_LVDS
		"LINK_PD_LVDS "
#endif
#ifdef CONFIG_LINK_PD_FS460
		"LINK_PD_FS460 "
#endif
#ifdef CONFIG_LINK_PD_CH7017
		"LINK_PD_CH7017 "
#endif
#ifdef CONFIG_LINK_PD_TI410
		"LINK_PD_TI410 "
#endif
#ifdef CONFIG_LINK_PD_TV
		"LINK_PD_TV "
#endif
#ifdef CONFIG_LINK_PD_HDMI
		"LINK_PD_HDMI "
#endif
#ifdef CONFIG_LINK_PD_SDVO
		"LINK_PD_SDVO "
#endif
#ifdef CONFIG_LINK_PD_SOFTPD
		"LINK_PD_SOFTPD "
#endif


#ifdef CONFIG_COPP
		"COPP "
#endif
		;
	printf("%s\n", configs);
	return 0;
}

