/**
 * @file
 * Ethernet output function - handles OUTGOING ethernet level traffic, implements
 * ARP resolving.
 * To be used in most low-level netif implementations
 */

/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * Copyright (c) 2003-2004 Leon Woestenberg <leon.woestenberg@axon.tv>
 * Copyright (c) 2003-2004 Axon Digital Design B.V., The Netherlands.
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
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#ifndef LWIP_HDR_NETIF_ETHARP_H
#define LWIP_HDR_NETIF_ETHARP_H

#include "lwip/opt.h"

#if LWIP_ARP || LWIP_ETHERNET /* don't build if not configured for use in lwipopts.h */

#include "lwip/pbuf.h"
#include "lwip/ip4_addr.h"
#include "lwip/netif.h"
#include "lwip/ip4.h"
#include "lwip/prot/ethernet.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif


#if LWIP_IPV4 && LWIP_ARP /* don't build if not configured for use in lwipopts.h */

#include "lwip/prot/etharp.h"

/** 1 seconds period */
#define ARP_TMR_INTERVAL 1000

/* 2 seconds period */
#define DUP_ARP_DETECT_TIME 2000

/* ARP message types (opcodes) */
#define ARP_REQUEST 1
#define ARP_REPLY   2

/*
 * Try hard to create a new entry - we want the IP_add to appear in
 * the cache (even if this means removing an active entry or so).
 */
#define ETHARP_FLAG_TRY_HARD     1
#define ETHARP_FLAG_FIND_ONLY    2
#if ETHARP_SUPPORT_STATIC_ENTRIES
#define ETHARP_FLAG_STATIC_ENTRY 4
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */

#define ETHTYPE_ARP       0x0806U
#define ETHTYPE_IP        0x0800U
#define ETHTYPE_VLAN      0x8100U
#define ETHTYPE_ALL       0x0003U  /* All packets */

#if ARP_QUEUEING
/** struct for queueing outgoing packets for unknown address
  * defined here to be accessed by memp.h
  */
struct etharp_q_entry {
  struct etharp_q_entry *next;
  struct pbuf *p;
};
#endif /* ARP_QUEUEING */

enum etharp_state {
  ETHARP_STATE_EMPTY = 0,
  ETHARP_STATE_PENDING,
  ETHARP_STATE_STABLE,
  ETHARP_STATE_STABLE_REREQUESTING_1,
  ETHARP_STATE_STABLE_REREQUESTING_2
#if ETHARP_SUPPORT_STATIC_ENTRIES
  , ETHARP_STATE_STATIC
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */
};

struct etharp_entry {
#if ARP_QUEUEING
  /* Pointer to queue of pending outgoing packets on this ARP entry. */
  struct etharp_q_entry *q;
#else /* ARP_QUEUEING */
  /* Pointer to a single pending outgoing packet on this ARP entry. */
  struct pbuf *q;
#endif /* ARP_QUEUEING */
  ip4_addr_t ipaddr;
  struct netif *netif;
  struct eth_addr ethaddr;
  u16_t ctime;
  u8_t state;
};

#define etharp_init() /* Compatibility define, no init needed. */
void etharp_tmr(void);
s8_t etharp_find_addr(struct netif *netif, const ip4_addr_t *ipaddr,
                      struct eth_addr **eth_ret, const ip4_addr_t **ip_ret);
err_t etharp_ip_to_mac(const ip4_addr_t *ipaddr, u8_t *mac, u8_t *maclen);
#if LWIP_API_RICH
u8_t etharp_get_entry(u8_t i, ip4_addr_t **ipaddr, struct netif **netif, struct eth_addr **eth_ret);
#endif /* LWIP_API_RICH */
err_t etharp_output(struct netif *netif, struct pbuf *q, const ip4_addr_t *ipaddr);
err_t etharp_query(struct netif *netif, const ip4_addr_t *ipaddr, struct pbuf *q);
err_t etharp_request(struct netif *netif, const ip4_addr_t *ipaddr);
err_t etharp_announce(struct netif *netif, const ip4_addr_t *ipaddr);
/** For Ethernet network interfaces, we might want to send "gratuitous ARP";
 *  this is an ARP packet sent by a node in order to spontaneously cause other
 *  nodes to update an entry in their ARP cache.
 *  From RFC 3220 "IP Mobility Support for IPv4" section 4.6. */
#if LWIP_ARP_GRATUITOUS_REXMIT
err_t etharp_gratuitous_start(struct netif *netif);
#define etharp_gratuitous(netif) etharp_gratuitous_start(netif)
#define ETHARP_GRATUITOUS_NUM 2
#else
#define etharp_gratuitous(netif) etharp_request((netif), netif_ip4_addr(netif))
#endif
void etharp_cleanup_netif(struct netif *netif);

#if ETHARP_SUPPORT_STATIC_ENTRIES
err_t etharp_add_static_entry(const ip4_addr_t *ipaddr, struct eth_addr *ethaddr);
err_t etharp_remove_static_entry(const ip4_addr_t *ipaddr);
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */

#if ETHARP_TRUST_IP_MAC
void etharp_ip_input(struct netif *netif, struct pbuf *p);
#endif /* ETHARP_TRUST_IP_MAC */

#if LWIP_LOWPOWER
u32_t etharp_tmr_tick(void);
#endif /* LWIP_LOWPOWER */

err_t etharp_update_arp_entry(struct netif *netif, const ip4_addr_t *ipaddr, struct eth_addr *ethaddr, u8_t flags);
#if LWIP_ENABLE_LOS_SHELL_CMD || (defined LWIP_TESTBED)
err_t etharp_delete_arp_entry(struct netif *netif, ip4_addr_t *ipaddr);
#endif /* LWIP_ENABLE_LOS_SHELL_CMD */
#endif /* LWIP_IPV4 && LWIP_ARP */

void etharp_input(struct pbuf *p, struct netif *netif);

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_ARP || LWIP_ETHERNET */

#endif /* LWIP_HDR_NETIF_ETHARP_H */
