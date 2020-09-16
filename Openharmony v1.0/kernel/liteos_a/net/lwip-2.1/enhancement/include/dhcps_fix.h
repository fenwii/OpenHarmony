/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LITEOS_A_DHCPS_FIXME_H
#define LITEOS_A_DHCPS_FIXME_H

#include "lwip/opt.h"

#if (LWIP_DHCP) && (LWIP_DHCPS)

#define LWIP_STATIC static


/* Option handling: options are parsed in dhcp_parse_reply
 * and saved in an array where other functions can load them from.
 * This might be moved into the struct dhcp (not necessarily since
 * lwIP is single-threaded and the array is only used while in recv
 * callback). */
enum dhcp_option_idx {
    DHCP_OPTION_IDX_OVERLOAD = 0,
    DHCP_OPTION_IDX_MSG_TYPE,
    DHCP_OPTION_IDX_SERVER_ID,
    DHCP_OPTION_IDX_LEASE_TIME,
    DHCP_OPTION_IDX_T1,
    DHCP_OPTION_IDX_T2,
    DHCP_OPTION_IDX_SUBNET_MASK,
    DHCP_OPTION_IDX_ROUTER,
#if LWIP_DHCP_PROVIDE_DNS_SERVERS
    DHCP_OPTION_IDX_DNS_SERVER,
    DHCP_OPTION_IDX_DNS_SERVER_LAST = DHCP_OPTION_IDX_DNS_SERVER + LWIP_DHCP_PROVIDE_DNS_SERVERS - 1,
#endif /* LWIP_DHCP_PROVIDE_DNS_SERVERS */
#if LWIP_DHCP_GET_NTP_SRV
    DHCP_OPTION_IDX_NTP_SERVER,
    DHCP_OPTION_IDX_NTP_SERVER_LAST = DHCP_OPTION_IDX_NTP_SERVER + LWIP_DHCP_MAX_NTP_SERVERS - 1,
#endif /* LWIP_DHCP_GET_NTP_SRV */
    DHCP_OPTION_IDX_REQUESTED_IP,
    DHCP_OPTION_IDX_MAX
};

#define DHCP_OPTION_ROUTER_SIZE     4
#define DHCP_OPTION_SUBNET_MASK_SIZE 4
#define DHCP_OPTION_LEASE_TIME_SIZE 4
#define DHCP_OPTION_SERVER_ID_LEN   4
#define DHCP_OPTION_T1_LEN          4
#define DHCP_OPTION_T2_LEN          4

#define DHCP_CLIENT_PORT  68
#define DHCP_SERVER_PORT  67

#define DHCP_BROADCAST_FLAG             0x8000
#define DHCP_MAX_MSG_LEN_MIN_REQUIRED   576

struct dyn_lease_addr {
    u8_t cli_hwaddr[DHCP_CHADDR_LEN];
    u32_t flags;
    u32_t leasetime;
    u32_t proposed_leasetime;
    ip4_addr_t cli_addr;
};

struct dhcps {
    struct udp_pcb *pcb;
    struct dyn_lease_addr leasearr[LWIP_DHCPS_MAX_LEASE];
    u8_t pcb_allocated;
    u8_t lease_num;
    struct netif *netif;
    ip4_addr_t start_addr;
    ip4_addr_t end_addr;
};


#endif // (LWIP_DHCP) && (LWIP_DHCPS)

#endif // LITEOS_A_DHCPS_FIXME_H
