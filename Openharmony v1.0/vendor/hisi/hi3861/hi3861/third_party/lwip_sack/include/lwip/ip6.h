/**
 * @file
 *
 * IPv6 layer.
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
#ifndef LWIP_HDR_IP6_H
#define LWIP_HDR_IP6_H

#include "lwip/opt.h"

#if LWIP_IPV6  /* don't build if not configured for use in lwipopts.h */

#include "lwip/ip6_addr.h"
#include "lwip/prot/ip6.h"
#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/netif.h"

#include "lwip/err.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

/* \brief  Destination and Hop By Hop extension headers option types */
#define LWIP_EXT_HDR_OPT_PAD1  0
#define LWIP_EXT_HDR_OPT_PADN  1

#define LWIP_RPL_RPI_TYPE_NEW   0x23
#define LWIP_RPL_RPI_TYPE_OLD   0x63

#define LWIP_IPH_LEN 40

#define IP_PROTO_VERSION_6 6

/*
 * brief is address a multicast address, see RFC 3513
 * a is of type uip_ipaddr_t*
 */
#define lwip_rpl_is_addr_mcast(a) ((a)->addr[0] == 0xFF000000)

void ip6_process_destination_header_extension_options(struct pbuf *p, struct ip6_dest_hdr *opt_hdr,
                                                      u16_t hlen, u8_t *need_ip6_input_cleanup);

struct netif *ip6_route(const ip6_addr_t *src, const ip6_addr_t *dest
#if LWIP_SO_DONTROUTE
                        , rt_scope_t scope
#endif
                       );


/*
 * @ingroup ip6
 * Select the best IPv6 source address for a given destination IPv6 address.
 *
 * This implementation follows RFC 6724 Sec. 5 to the following extent:
 * - Rules 1, 2, 3: fully implemented
 * - Rules 4, 5, 5.5: not applicable
 * - Rule 6: not implemented
 * - Rule 7: not applicable
 * - Rule 8: limited to addresses with /64 addresses
 *
 * For Rule 2, we deliberately deviate from RFC 6724 Sec. 3.1 by considering
 * ULAs to be of smaller scope than global addresses, to avoid that a preferred
 * ULA is picked over a deprecated global address when given a global address
 * as destination, as that would likely result in broken two-way communication.
 *
 * As long as temporary addresses are not supported (as used in Rule 7), a
 * proper implementation of Rule 8 would obviate the need to implement Rule 6.
 *
 * @param netif the netif on which to send a packet
 * @param dest the destination we are trying to reach (possibly not properly
 *             zoned)
 * @return the most suitable source address to use, or NULL if no suitable
 *         source address is found
 */
const ip_addr_t *ip6_select_source_address(struct netif *netif, const ip6_addr_t *dest);

const ip6_addr_t *ip6_select_first_valid_address(struct netif *netif);

/*
 * @ingroup ip6
 * Compute the number of common network prefix bits between two IPv6 addresses
 *
 * @param addr1 IPv6 Address 1
 * @param addr2 IPv6 Address 2
 * @param prefix_length Length of network prefix(in bits)
 * @return
 * Number of common prefix bits in addr1 & addr2 : On success
 * -1 : Invalid parameters
 */
int ip6_common_prefix_length(const ip6_addr_t *addr1, const ip6_addr_t *addr2, u8_t prefix_length);


err_t         ip6_input(struct pbuf *p, struct netif *inp);
#if LWIP_API_RICH
err_t         ip6_output(struct pbuf *p, const ip6_addr_t *src, const ip6_addr_t *dest,
                         u8_t hl, u8_t tc, u8_t nexth, struct ip_pcb *pcb);
#endif /* LWIP_API_RICH */
err_t         ip6_output_if(struct pbuf *p, const ip6_addr_t *src, const ip6_addr_t *dest,
                            u8_t hl, u8_t tc, u8_t nexth, struct netif *netif);
err_t         ip6_output_if_src(struct pbuf *p, const ip6_addr_t *src, const ip6_addr_t *dest,
                                u8_t hl, u8_t tc, u8_t nexth, struct netif *netif);
#if LWIP_NETIF_USE_HINTS
err_t         ip6_output_hinted(struct pbuf *p, const ip6_addr_t *src, const ip6_addr_t *dest,
                                u8_t hl, u8_t tc, u8_t nexth, struct netif_hint *netif_hint);
#endif /* LWIP_NETIF_USE_HINTS */
#if LWIP_IPV6_MLD
err_t         ip6_options_add_hbh_ra(struct pbuf *p, u8_t nexth, u8_t value);
#endif /* LWIP_IPV6_MLD */

#define ip6_netif_get_local_ip(netif, dest) (((netif) != NULL) ? \
  ip6_select_source_address(netif, dest) : NULL)

#if IP6_DEBUG
void ip6_debug_print(struct pbuf *p);
#else
#define ip6_debug_print(p)  (void)0
#endif /* IP6_DEBUG */

#if LWIP_RPL || LWIP_RIPPLE
int lwip_get_pkt_route_status(void);

void lwip_set_pkt_route_status(int up);

int lwip_get_rte_nexthop_nonmesh(void);

void lwip_set_rte_nexthop_nonmesh(int stat);

/* For accessing hardcoded hbh_len. */
u16_t lwip_hbh_len(struct pbuf *p);
#endif /* LWIP_RPL || LWIP_RIPPLE */

#if LWIP_RPL
struct pbuf *lwip_add_rpi_hdr(struct pbuf *p, u8_t nexth, u16_t hbh_len, u8_t flags);
#endif

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_IPV6 */

#endif /* LWIP_HDR_IP6_H */
