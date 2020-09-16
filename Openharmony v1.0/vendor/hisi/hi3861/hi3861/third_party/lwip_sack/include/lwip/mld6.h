/**
 * @file
 *
 * Multicast listener discovery for IPv6. Aims to be compliant with RFC 2710.
 * No support for MLDv2.
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

#ifndef LWIP_HDR_MLD6_H
#define LWIP_HDR_MLD6_H

#include "lwip/opt.h"

#if (LWIP_IPV6 && (LWIP_IPV6_MLD || LWIP_IPV6_MLD_QUERIER))  /* don't build if not configured for use in lwipopts.h */

#include "lwip/pbuf.h"
#include "lwip/netif.h"
#if ((LWIP_RPL || LWIP_RIPPLE) && LWIP_MPL)
#include "mcast6.h"
#endif /* ((LWIP_RPL || LWIP_RIPPLE) && LWIP_MPL) */

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

/** MLD group */
struct mld_group {
  /** next link */
  struct mld_group *next;
  /** multicast address */
  ip6_addr_t         group_address;
  /** signifies we were the last person to report */
  u8_t               last_reporter_flag;
  /** current state of the group */
  u8_t               group_state;
  /** timer for reporting */
  u16_t              timer;
  /** counter of simultaneous uses */
  u8_t               use;
};

#define MLD6_TMR_INTERVAL              100 /* Milliseconds */

err_t  mld6_stop(struct netif *netif);
void   mld6_report_groups(struct netif *netif);
void   mld6_tmr(void);
struct mld_group *mld6_lookfor_group(struct netif *ifp, const ip6_addr_t *addr);
void   mld6_input(struct pbuf *p, struct netif *inp);
err_t  mld6_joingroup(const ip6_addr_t *srcaddr, const ip6_addr_t *groupaddr);
err_t  mld6_joingroup_netif(struct netif *netif, const ip6_addr_t *groupaddr);
err_t  mld6_join_staticgroup_netif(struct netif *netif, const ip6_addr_t *groupaddr);
err_t  mld6_leavegroup(const ip6_addr_t *srcaddr, const ip6_addr_t *groupaddr);
err_t  mld6_leavegroup_netif(struct netif *netif, const ip6_addr_t *groupaddr);

#if LWIP_LOWPOWER
u32_t mld6_tmr_tick(void);
#endif

/** @ingroup mld6
 * Get list head of MLD6 groups for netif.
 * Note: The allnodes group IP is NOT in the list, since it must always
 * be received for correct IPv6 operation.
 * @see @ref netif_set_mld_mac_filter()
 */
#define netif_mld6_data(netif) ((struct mld_group *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_MLD6))

#if ((LWIP_RPL || LWIP_RIPPLE) && LWIP_MPL)
#ifndef LWIP_CONF_MLD6_JOIN_GRP
#define LWIP_CONF_MLD6_JOIN_GRP lwip_mld6_join_group
#endif /* LWIP_CONF_MLD6_JOIN_GRP */
#endif /* (LWIP_RPL || LWIP_RIPPLE) && LWIP_MPL */

#ifndef LWIP_CONF_MLD6_JOIN_GRP
#define LWIP_CONF_MLD6_JOIN_GRP
#endif /* LWIP_CONF_MLD6_JOIN_GRP */

#if LWIP_IPV6_MLD_QUERIER
#ifndef MLD6_MS_PER_SECOND
#define MLD6_MS_PER_SECOND 1000
#endif /* MLD6_MS_PER_SECOND */

#ifndef MLD6_QUERIER_LISTENER_MAX_NUM
#define MLD6_QUERIER_LISTENER_MAX_NUM 4
#endif /* MLD6_QUERIER_LISTENER_MAX_NUM */

enum mld6_listener_state {
  MLD6_LISTENER_STATE_NON,
  MLD6_LISTENER_STATE_PRESENT,
  MLD6_LISTENER_STATE_CHECK
};

struct mld6_listener {
  struct mld6_listener *next;
  ip6_addr_t group_address;
  /* mld6_listener_state */
  u8_t state;
  u8_t query_count;
  u16_t timer;
  /* retransmit timer */
  u16_t rexmt_timer;
};

enum mld6_querier_state {
  MLD6_QUERIER_STATE_STARTUP,
  MLD6_QUERIER_STATE_NON_LISTENER,
  MLD6_QUERIER_STATE_HAVE_LISTENER
};

struct mld6_querier {
  u8_t querier_state;
  u8_t query_count; // when startup, need to send [Startup Query Count] times of General Query
  u16_t timer;
  struct mld6_listener *listeners;
  u8_t listener_num;
};

#define netif_mld6_querier_data(netif) \
  ((struct mld6_querier *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_MLD6_QUERIER))

err_t mld6_querier_start(struct netif *netif);
void mld6_querier_stop(struct netif *netif);
struct mld6_listener *mld6_querier_listener_lookfor(struct netif *netif, const ip6_addr_t *addr);
#endif /* LWIP_IPV6_MLD_QUERIER */

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* (LWIP_IPV6 && (LWIP_IPV6_MLD || LWIP_IPV6_MLD_QUERIER)) */

#endif /* LWIP_HDR_MLD6_H */
