/**
 * @file
 *
 * 6LowPAN output for IPv6. Uses ND tables for link-layer addressing. Fragments packets to 6LowPAN units.
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

#ifndef LWIP_HDR_LOWPAN6_H
#define LWIP_HDR_LOWPAN6_H

#include "netif/lowpan6_opts.h"

#if LWIP_IPV6 && LWIP_6LOWPAN /* don't build if not configured for use in lwipopts.h */

#include "lwip/pbuf.h"
#include "lwip/ip.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

/*
 * 6lowpan context identifier information need to be dessiminated to the nodes
 * in the LLNs using some upper layer protocols. For example The 6LoWPAN Context Option (6CO)
 * suggested in the RFC 6775 (ND Optimization for 6LoWPANs). So the below
 * data structure can be used to store the context information .
 */
struct lowpan6_context_info {
  ip6_addr_t context_prefix;
  /*
   * Its basically the netif that added the lowpan context
   * currently it doesn't have much use . Added for future purpose
   */
  void *iface;
  u8_t context_id;
  u8_t is_used;
};

/** 1 second period */
#define LOWPAN6_TMR_INTERVAL 1000

/* As per RFC 4944 The reassembly timeout MUST be set to a maximum of 60 seconds */
#define LOWPAN6_REASS_TIMEOUT 60

void lowpan6_tmr(void);
#if LWIP_LOWPOWER
u32_t lowpan6_tmr_tick(void);
#endif

err_t lowpan6_set_context(struct netif *hwface, u8_t index, const ip6_addr_t *context);
err_t lowpan6_remove_context(struct netif *hwface, u8_t ctxid);
err_t lowpan6_set_short_addr(u8_t addr_high, u8_t addr_low);

#if LWIP_IPV4
err_t lowpan4_output(struct netif *netif, struct pbuf *q, const ip4_addr_t *ipaddr);
#endif /* LWIP_IPV4 */
err_t lowpan6_output(struct netif *netif, struct pbuf *q, const struct linklayer_addr *dstlinkaddr);

err_t lowpan6_input(struct pbuf *p, struct netif *netif,
                    const struct linklayer_addr *sendermac,
                    const struct linklayer_addr *recvrmac);

err_t lowpan6_if_init(struct netif *netif);

/* pan_id in network byte order. */
err_t lowpan6_set_pan_id(u16_t pan_id);

#if !NO_SYS
err_t tcpip_6lowpan_input(struct pbuf *p, struct netif *inp);
#endif /* !NO_SYS */
void lowpan6_free_reass_context(struct netif *netif);

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_IPV6 && LWIP_6LOWPAN */

#endif /* LWIP_HDR_LOWPAN6_H */
