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

#ifndef LWIP_HDR_DHCPS_H
#define LWIP_HDR_DHCPS_H

#include "lwip/opt.h"
#include "lwip/prot/dhcp.h"
#if LWIP_DHCPS /* don't build if not configured for use in lwipopts.h */

#include "lwip/netif.h"
#include "lwip/udp.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif


#ifndef LWIP_DHCPS_MAX_LEASE
#define LWIP_DHCPS_MAX_LEASE 30
#endif

#ifndef LWIP_DHCPS_LEASE_TIME
#define LWIP_DHCPS_LEASE_TIME  ~0
#endif

/* Offer time in seconds */
#ifndef LWIP_DHCPS_OFFER_TIME
#define LWIP_DHCPS_OFFER_TIME 300
#endif

#ifndef LWIP_DHCPS_DECLINE_TIME
#define LWIP_DHCPS_DECLINE_TIME 500
#endif

err_t dhcps_start(struct netif *netif, const char *start_ip, u16_t ip_num);
void dhcps_stop(struct netif *netif);
void dhcp_common_option(struct dhcp_msg *msg_out, u8_t option_type, u8_t option_len, u16_t *options_out_len);
void dhcp_common_option_byte(struct dhcp_msg *msg_out, u8_t value, u16_t *options_out_len);
void dhcp_common_option_short(struct dhcp_msg *msg_out, u16_t value, u16_t *options_out_len);
void dhcp_common_option_long(struct dhcp_msg *msg_out, u32_t value, u16_t *options_out_len);
void dhcp_common_option_trailer(struct dhcp_msg *msg_out, u16_t *options_out_len);
#if LWIP_DHCP_BOOTP_FILE
err_t dhcps_parse_options(struct pbuf *p, char *boot_file_name);
#else
err_t dhcps_parse_options(struct pbuf *p);
#endif

#if defined (__cplusplus) && __cplusplus
}
#endif
#endif /* LWIP_DHCPS */
#endif /* LWIP_HDR_DHCPS_H */
