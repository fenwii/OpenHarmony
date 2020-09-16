/**
 * @file
 *
 * Neighbor discovery and stateless address autoconfiguration for IPv6.
 * Aims to be compliant with RFC 4861 (Neighbor discovery) and RFC 4862
 * (Address autoconfiguration).
 */

/*
 * Copyright (c) 2010 Inico Technologies Ltd.
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

#ifndef LWIP_HDR_ND6_H
#define LWIP_HDR_ND6_H

#include "lwip/opt.h"

#if LWIP_IPV6  /* don't build if not configured for use in lwipopts.h */

#include "lwip/ip6_addr.h"
#include "lwip/err.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif


/** @cond liteos
 * 1 second period */
#define ND6_TMR_INTERVAL 1000

/** Router solicitations are sent in 4 second intervals (see RFC 4861, ch. 6.3.7)
 * @endcond */
#ifndef ND6_RTR_SOLICITATION_INTERVAL
#define ND6_RTR_SOLICITATION_INTERVAL  4000
#endif

/* [rfc4861][section 10] */
#ifndef ND6_MAX_NEIGHBOR_ADVERTISEMENT
#define ND6_MAX_NEIGHBOR_ADVERTISEMENT 3
#endif

#ifndef ND6_RETRANS_TIMER
#define ND6_RETRANS_TIMER 1000 /* milliseconds */
#endif

#define ND6_SEND_FLAG_MULTICAST_DEST 0x01
#define ND6_SEND_FLAG_ALLNODES_DEST 0x02
#define ND6_SEND_FLAG_UNSECURE 0x04

#define ND6_SEND_FLAG_UNSPEC_SRC 0x10
#define SIZEOF_RDNSS_OPTION_BASE 8

/* Hop limit value */
#define ND6_HOPLIM 255
#if LWIP_RPL_RS_DAO
#define ND6_RS_FLAG_DAO  (1)
#endif
#define ND6_RS_FLAG_RA   (0)
#define RS_LLADDR_OPTION_HEADER_LEN 2

struct pbuf;
struct netif;
#ifdef LWIP_TESTBED
void nd6_remove_netif_neighbor_cache_entries(struct netif *netif);
#endif

#if LWIP_IPV6 && LWIP_NETIF_NBR_CACHE_API
struct nd6_neighbor_info {
  struct ip6_addr nbripaddr;
  u32_t reachabletime;
  u8_t hwaddr[NETIF_MAX_HWADDR_LEN];
  u8_t hwlen;
  u8_t curstate;
};
#endif
void nd6_tmr(void);
void nd6_input(struct pbuf *p, struct netif *inp);
void nd6_rs_input(struct pbuf *p, struct netif *inp, u8_t flags);
err_t nd6_send_ra(struct netif *netif, const ip6_addr_t *target_addr, u8_t flags);
void nd6_clear_destination_cache(void);
struct netif *nd6_find_route(const ip6_addr_t *ip6addr);
err_t nd6_get_next_hop_addr_or_queue(struct netif *netif, struct pbuf *q, const ip6_addr_t *ip6addr,
                                     const u8_t **hwaddrp);
u16_t nd6_get_destination_mtu(const ip6_addr_t *ip6addr, struct netif *netif);
#if LWIP_ND6_TCP_REACHABILITY_HINTS
void nd6_reachability_hint(const ip6_addr_t *ip6addr);
#endif /* LWIP_ND6_TCP_REACHABILITY_HINTS */
void nd6_cleanup_netif(struct netif *netif);
#if LWIP_IPV6_MLD
void nd6_adjust_mld_membership(struct netif *netif, s8_t addr_idx, u8_t new_state);
#endif /* LWIP_IPV6_MLD */
void nd6_send_na(struct netif *netif, const ip6_addr_t *target_addr, u8_t flags);

#if LWIP_IPV6_SEND_ROUTER_SOLICIT
err_t nd6_send_rs(struct netif *netif);
#endif /* LWIP_IPV6_SEND_ROUTER_SOLICIT */

#if LWIP_RPL || LWIP_RIPPLE || (defined LWIP_TESTBED)
err_t nd6_add_neighbor_cache_entry(struct netif *netif, const ip6_addr_t *nbr_addr, const  u8_t *addr,
                                   const u8_t addrlen, u8_t uc_reason2_add, void *pv_data);
#endif /* LWIP_RPL || LWIP_RIPPLE || (defined LWIP_TESTBED) */

#ifdef LWIP_TESTBED
const ip6_addr_t *nd6_get_prefix_addr(const ip6_addr_t *ip6addr, struct netif *netif);
#endif /* LWIP_TESTBED */

#if LWIP_IPV6 && LWIP_NETIF_NBR_CACHE_API
err_t nd6_add_neighbor_cache_entry_manually(struct netif *netif, struct nd6_neighbor_info *nbrinfo);
err_t nd6_del_neighbor_cache_entry_manually(struct netif *netif, struct ip6_addr *nbrip);
err_t nd6_get_neighbor_cache_info(struct netif *netif, struct ip6_addr *nbrip, struct nd6_neighbor_info *nbrinfo);
#endif

#if LWIP_RPL || LWIP_RIPPLE

void *nd6_add_default_router(const ip6_addr_t *router_addr, u32_t lifetime, struct netif *netif);

err_t nd6_get_default_router_ip(ip6_addr_t *router_addr, void *default_route);

void nd6_remove_default_router(void *default_route);

void nd6_refresh_destination_cache(const ip6_addr_t *nexthop_addr);
void nd6_refresh_destination_cache_by_dest(const ip6_addr_t *dest);
#endif

#if LWIP_IPV6_AUTOCONFIG
void nd6_clear_netif_autoconf_address(struct netif *netif);
#endif

int nd6_validate_options(u8_t *opt, int opt_len);
void nd6_restart_netif(struct netif *netif);
void nd6_report_groups(struct netif *netif, s8_t addr_idx);

#if LWIP_ND6_STATIC_DEFAULT_ROUTE
err_t lwip_nd6_add_static_default_route_manually(struct netif *netif, struct ip6_addr *router_addr);
err_t lwip_nd6_del_static_default_route(struct netif *netif, const ip6_addr_t *router_addr);
#endif /* LWIP_ND6_STATIC_DEFAULT_ROUTE */
#if LWIP_ND6_STATIC_PREFIX
s8_t nd6_add_static_prefix(struct netif *netif, ip6_addr_t *prefix, u8_t flags);
s8_t nd6_del_static_prefix(struct netif *netif, ip6_addr_t *prefix);
#endif /* LWIP_ND6_STATIC_PREFIX */

#if LWIP_RIPPLE
struct nd6_neighbor_cache_entry *nd6_get_neighbor_byindex(s8_t nbrindex);
struct nd6_neighbor_cache_entry *nd6_neighbor_cache_lookup(const ip6_addr_t *ip6addr, struct netif *iface);
void beacon_priority_update(u8_t is_clear);
#endif /* LWIP_RIPPLE */

s8_t nd6_find_neighbor_cache_entry(const ip6_addr_t *ip6addr, struct netif *netif);

#if LWIP_ENABLE_ROUTER
void *nd6_get_neighbor_linkquality_from_lladdr(struct netif *linkiface, const u8_t *sendermac, u8_t hwaddrlen);
u8_t *nd6_get_neighbor_lladdr(struct netif *linkiface, const ip6_addr_t *ip6addr, u8_t *lladdrlen);
void *nd6_get_neighbor_cache_entry_from_lladdr(struct netif *linkiface,  u8_t *sendermac, u8_t hwaddrlen);
void nd6_remove_neighbor_cache_entry(struct netif *netif, const ip6_addr_t *nbr_addr);
void nd6_remove_neighbor_by_mac(struct netif *netif, const u8_t *mac, u8_t maclen);
#endif

#if LWIP_NBRPOLICY_ENABLE_NBR_RESTRICTION
s8_t lwip_nbrpolicy_find_reusable_entry(u8_t uc_reason2_add, void *pv_data, s8_t *index2use);
#endif /* LWIP_NBRPOLICY_ENABLE_NBR_RESTRICTION */

u16_t lwip_nbr_cache_free_count(void);

#ifdef LWIP_LOWPOWER
u32_t nd6_tmr_tick(void);
#endif

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_IPV6 */

#endif /* LWIP_HDR_ND6_H */
