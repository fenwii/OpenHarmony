/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: implementation for IPv4 DHCP server
 * Author: none
 * Create: 2013
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
#define LWIP_DHCPS_LEASE_TIME  7200
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
#if LWIP_NETIFAPI_DHCPS_IP
err_t dhcps_find_client_lease(struct netif *netif, u8_t *mac, u8_t maclen, ip_addr_t *ip);
#endif
void dhcps_client_disconnect(struct netif *netif, const u8_t *mac, u8_t maclen);

#if defined (__cplusplus) && __cplusplus
}
#endif
#endif /* LWIP_DHCPS */
#endif /* LWIP_HDR_DHCPS_H */
