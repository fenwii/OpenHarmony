/**
 * @file
 * 6LowPAN options list
 */

/*
 * Copyright (c) 2015 Inico Technologies Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Ivan Delamer <delamer@inicotech.com>
 *
 *
 * Please coordinate changes and requests with Ivan Delamer
 * <delamer@inicotech.com>
 */

#ifndef LWIP_HDR_LOWPAN6_OPTS_H
#define LWIP_HDR_LOWPAN6_OPTS_H

#include "lwip/opt.h"

#define LOWPAN_LINK_LAYER_TYPE_RF 1
#define LOWPAN_LINK_LAYER_TYPE_PLC 2

/*
 * This configuration will enable the 6lowpan layer processing for the IPv6
 * traffic. 6lopwan enables the IPv6 packets to sned over the link whose MTU is
 * less than the default IPv6 MTU.
 */
#ifndef LWIP_6LOWPAN
#define LWIP_6LOWPAN                     1
#endif

/*
 * This configuration will enable the 6lowpan layer statistics.
 */
#if !defined LOWPAN6_STATS || defined __DOXYGEN__
#define LOWPAN6_STATS        (LWIP_STATS && LWIP_IPV6 && LWIP_6LOWPAN)
#endif

#define LWIP_6LOWPAN_MAX_CTXID 15

/*
 * Defines the number of 6lowpan contexts that can be added to the 6lowpan layer.
 */
#ifndef LWIP_6LOWPAN_NUM_CONTEXTS
#define LWIP_6LOWPAN_NUM_CONTEXTS        10
#endif

#ifndef LWIP_6LOWPAN_INFER_SHORT_ADDRESS
#define LWIP_6LOWPAN_INFER_SHORT_ADDRESS 1
#endif

#ifndef LWIP_6LOWPAN_IPHC
#define LWIP_6LOWPAN_IPHC                1
#endif

#ifndef LWIP_6LOWPAN_HW_CRC
#define LWIP_6LOWPAN_HW_CRC              1
#endif
/*
 * Enables debug log for 6lowpan module.
 */
#ifndef LOWPAN6_DEBUG
#define LOWPAN6_DEBUG                    LWIP_DBG_OFF
#endif

/*
 * Defines the MTU of PLC link.
 */
#ifndef LOWPAN6_PLC_MAX_LINK_MTU
#define LOWPAN6_PLC_MAX_LINK_MTU 512
#endif

/*
 * Defines the MTU of RF link.
 */
#ifndef LOWPAN6_RF_MAX_LINK_MTU
#define LOWPAN6_RF_MAX_LINK_MTU 128
#endif

/*
 * Defines the MAC layer overhead for PLC link.
 */
#ifndef LOWPAN6_PLC_MAC_FIXED_OVERHEAD
#define LOWPAN6_PLC_MAC_FIXED_OVERHEAD 16
#endif

/*
 * Defines the MAC layer overhead for PLC link.
 */
#ifndef LOWPAN6_RF_MAC_FIXED_OVERHEAD
#define LOWPAN6_RF_MAC_FIXED_OVERHEAD 23
#endif

/*
 * Defines the maximum IPv6 MTU over PLC link.
 */
#ifndef LOWPAN6_IPV6_MAX_MTU_OVER_IEE802154
#define LOWPAN6_IPV6_MAX_MTU_OVER_IEE802154 1280
#endif

/*
 * Defines the maximum IPv6 MTU over RF link.
 */
#ifndef LOWPAN6_IPV6_MAX_MTU_OVER_PLC
#define LOWPAN6_IPV6_MAX_MTU_OVER_PLC 1280
#endif

#endif /* LWIP_HDR_LOWPAN6_OPTS_H */
