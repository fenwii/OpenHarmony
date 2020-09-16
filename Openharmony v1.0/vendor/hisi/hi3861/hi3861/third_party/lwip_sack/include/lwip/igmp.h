/**
 * @file
 * IGMP API
 */

/*
 * Copyright (c) 2002 CITEL Technologies Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of CITEL Technologies Ltd nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY CITEL TECHNOLOGIES AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL CITEL TECHNOLOGIES OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is a contribution to the lwIP TCP/IP stack.
 * The Swedish Institute of Computer Science and Adam Dunkels
 * are specifically granted permission to redistribute this
 * source code.
*/

#ifndef LWIP_HDR_IGMP_H
#define LWIP_HDR_IGMP_H

#include "lwip/opt.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"

#if LWIP_IPV4 && LWIP_IGMP /* don't build if not configured for use in lwipopts.h */

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

/* IGMP timer */
#define IGMP_TMR_INTERVAL              100 /* Milliseconds */
#define IGMP_V1_DELAYING_MEMBER_TMR   (1000 / (IGMP_TMR_INTERVAL))
#define IGMP_JOIN_DELAYING_MEMBER_TMR (500 / (IGMP_TMR_INTERVAL))

/* Compatibility defines (don't use for new code) */
#define IGMP_DEL_MAC_FILTER            NETIF_DEL_MAC_FILTER
#define IGMP_ADD_MAC_FILTER            NETIF_ADD_MAC_FILTER

/*
 * igmp group structure - there is
 * a list of groups for each interface
 * these should really be linked from the interface, but
 * if we keep them separate we will not affect the lwip original code
 * too much
 *
 * There will be a group for the all systems group address but this
 * will not run the state machine as it is used to kick off reports
 * from all the other groups
 */
struct igmp_group {
  /* next link */
  struct igmp_group *next;
  /* multicast address */
  ip4_addr_t         group_address;
  /* signifies we were the last person to report */
  u8_t               last_reporter_flag;
  /* current state of the group */
  u8_t               group_state;
  /* timer for reporting, negative is OFF */
  u16_t              timer;
  /* counter of simultaneous uses */
  u8_t               use;
};

/*  Prototypes */
/*
 * @ingroup igmp
 * Initialize the IGMP module
 */
void igmp_init(void);

/*
 * @ingroup igmp
 * Start IGMP processing on interface
 *
 * @param netif network interface on which start IGMP processing
 * @return ERR_OK if IGMP was started on the netif(s), an err_t otherwise
 *
 * Note: This is an internal function.
 */
err_t igmp_start(struct netif *netif);

/*
 * @ingroup igmp
 * Stop IGMP processing on interface
 *
 * @param netif network interface on which stop IGMP processing
 * @return ERR_OK if IGMP was stopped on the netif(s), an err_t otherwise
 *
 * Note: This is an internal function.
 */
err_t igmp_stop(struct netif *netif);

/*
 * @ingroup igmp
 * Report IGMP memberships for this interface
 *
 * @param netif network interface on which report IGMP memberships
 *
 * Note: This is an internal function.
 */
void igmp_report_groups(struct netif *netif);

/*
 * @ingroup igmp
 * Search for a group in the global igmp_group_list
 *
 * @param ifp the network interface for which to look
 * @param addr the group ip address to search for
 * @return a struct igmp_group* if the group has been found,
 *         NULL if the group wasn't found.
 *
 * Note: This is an internal function.
 */
struct igmp_group *igmp_lookfor_group(struct netif *ifp, const ip4_addr_t *addr);

/*
 * @ingroup igmp
 * Called from ip_input() if a new IGMP packet is received.
 *
 * @param p received igmp packet, p->payload pointing to the igmp header
 * @param inp network interface on which the packet was received
 * @param dest destination ip address of the igmp packet
 */
void igmp_input(struct pbuf *p, struct netif *inp, const ip4_addr_t *dest);

/*
 * @ingroup igmp
 * Join a group on one network interface.
 *
 * @param ifaddr ip address of the network interface which should join a new group
 * @param groupaddr the ip address of the group which to join
 * @return ERR_OK if group was joined on the netif(s), an err_t otherwise
 *
 * Note: This is an internal function.
 */
err_t igmp_joingroup(const ip4_addr_t *ifaddr, const ip4_addr_t *groupaddr);

/*
 * @ingroup igmp
 * Join a group on one network interface.
 *
 * @param netif the network interface which should join a new group
 * @param groupaddr the ip address of the group which to join
 * @return ERR_OK if group was joined on the netif, an err_t otherwise
 *
 * Note: This is an internal function.
 */
err_t igmp_joingroup_netif(struct netif *netif, const ip4_addr_t *groupaddr);

/*
 * @ingroup igmp
 * Leave a group on one network interface.
 *
 * @param ifaddr ip address of the network interface which should leave a group
 * @param groupaddr the ip address of the group which to leave
 * @return ERR_OK if group was left on the netif(s), an err_t otherwise
 *
 * Note: This is an internal function.
 */
err_t igmp_leavegroup(const ip4_addr_t *ifaddr, const ip4_addr_t *groupaddr);

/*
 * @ingroup igmp
 * Leave a group on one network interface.
 *
 * @param netif the network interface which should leave a group
 * @param groupaddr the ip address of the group which to leave
 * @return ERR_OK if group was left on the netif, an err_t otherwise
 *
 * Note: This is an internal function.
 */
err_t igmp_leavegroup_netif(struct netif *netif, const ip4_addr_t *groupaddr);

/*
 * @ingroup igmp
 *
 * The igmp timer function
 * Should be called every IGMP_TMR_INTERVAL milliseconds (100 ms is default).
 */
void igmp_tmr(void);

#if LWIP_LOWPOWER
u32_t igmp_tmr_tick(void);
#endif

/* @ingroup igmp
 * Get list head of IGMP groups for netif.
 * Note: The allsystems group IP is contained in the list as first entry.
 * @see @ref netif_set_igmp_mac_filter()
 */
#define netif_igmp_data(netif) ((struct igmp_group *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_IGMP))

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_IPV4 && LWIP_IGMP */

#endif /* LWIP_HDR_IGMP_H */
