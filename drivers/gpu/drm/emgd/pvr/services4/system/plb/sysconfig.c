/* -*- syscommon-c -*-
*-----------------------------------------------------------------------------
* Filename: syscommon.c
* $Revision: 1.2 $
*-----------------------------------------------------------------------------
* INTEL CONFIDENTIAL
* Copyright 2010 Intel Corporation All Rights Reserved.
* The source code contained or described herein and all documents related to
* the source code ("Material") are owned by Intel Corporation or its suppliers
* or licensors. Title to the Material remains with Intel Corporation or its
* suppliers and licensors. The Material contains trade secrets and proprietary
* and confidential information of Intel or its suppliers and licensors. The
* Material is protected by worldwide copyright and trade secret laws and
* treaty provisions. No part of the Material may be used, copied, reproduced,
* modified, published, uploaded, posted, transmitted, distributed, or
* disclosed in any way without Intel's prior express written permission.
*
* No license under any patent, copyright, trade secret or other intellectual
* property right is granted to or conferred upon you by disclosure or
* delivery of the Materials, either expressly, by implication, inducement,
* estoppel or otherwise. Any license under such intellectual property rights
* must be express and approved by Intel in writing.
*
*
*-----------------------------------------------------------------------------
* Description: platform detection, and sharing of correct platform interface.
*
*-----------------------------------------------------------------------------
* Authors:
*  Marcin Tomczyk
*-----------------------------------------------------------------------------
*/

#include "sysconfig.h"
#include "sysplb.h"

/* --------------------------------------------------------------------------*/
/**
* @Synopsis Poulsbo platform interface.
*/
/* --------------------------------------------------------------------------*/
SYS_PLATFORM_INTERFACE gpsSysPlatformInterfacePlb = {
        VS_PRODUCT_NAME_PLB,
        SYS_SGX_DEV_DEVICE_ID_PLB,
	SGX_REGS_OFFSET_PLB,
	MSVDX_REGS_OFFSET_PLB,
	SYS_SGX_CLOCK_SPEED_PLB,
	SYS_SGX_ACTIVE_POWER_LATENCY_MS_PLB
};

