/**
 * @file
 *
 * IPv6 version of ICMP, as per RFC 4443.
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

 * compliance:
 * rfc:2292
 * Section: 3.1 Checksum
 * Section: 3.2 ICMPv6 Type Filtering
 * Each ICMPv6 raw socket has an associated filter whose datatype is
 * defined as
 * struct icmp6_filter;
 * This structure, along with the macros and constants defined later in
 * this section, are defined as a result of including the
 * <netinet/icmp6.h> header.
 *
 * The current filter is fetched and stored using getsockopt() and
 * setsockopt() with a level of IPPROTO_ICMPV6 and an option name of
 * ICMP6_FILTER.
 * Six macros operate on an icmp6_filter structure:
 * void ICMP6_FILTER_SETPASSALL(struct icmp6_filter *);
 * void ICMP6_FILTER_SETBLOCKALL(struct icmp6_filter *);
 *
 * void ICMP6_FILTER_SETPASS( int, struct icmp6_filter *);
 * void ICMP6_FILTER_SETBLOCK( int, struct icmp6_filter *);
 *
 * int  ICMP6_FILTER_WILLPASS(int, const struct icmp6_filter *);
 * int  ICMP6_FILTER_WILLBLOCK(int, const struct icmp6_filter *);
 *
 * The first argument to the last four macros (an integer) is an ICMPv6
 * message type, between 0 and 255.  The pointer argument to all six
 * macros is a pointer to a filter that is modified by the first four
 * macros examined by the last two macros.
 *
 * The first two macros, SETPASSALL and SETBLOCKALL, let us specify that
 * all ICMPv6 messages are passed to the application or that all ICMPv6
 * messages are blocked from being passed to the application.
 *
 * The next two macros, SETPASS and SETBLOCK, let us specify that
 * messages of a given ICMPv6 type should be passed to the application
 * or not passed to the application (blocked).
 *
 * The final two macros, WILLPASS and WILLBLOCK, return true or false
 * depending whether the specified message type is passed to the
 * application or blocked from being passed to the application by the
 * filter pointed to by the second argument.
 *
 * Limitation: IPV6_CHECKSUM Offset need to be set by application based on the
 * socket and messages they are passing.
 * Checksum option need to be used for the messages of type UDP, TCP and ICMP.
 */


#ifndef LWIP_HDR_ICMP6_H
#define LWIP_HDR_ICMP6_H

#include "lwip/opt.h"
#include "lwip/pbuf.h"
#include "lwip/ip6_addr.h"
#include "lwip/netif.h"
#include "lwip/prot/icmp6.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif


#if LWIP_ICMP6 && LWIP_IPV6 /* don't build if not configured for use in lwipopts.h */


#if LWIP_ICMP6_ERR_RT_LMT

/* struct for queueing icmp6 error packet */
struct icmp6_err_bkt {
  u32_t icmp_bkt[ICMP6_ERR_BKT_SIZE];
  u32_t avg;
  u16_t bkt_index;
  u16_t spare;
};

extern struct icmp6_err_bkt icmp6_err_bkt;

u8_t icmp6_err_update_rate_lmt(void);
void icmp6_err_rate_calc(void);

#endif

void icmp6_input(struct pbuf *p, struct netif *inp);
void icmp6_dest_unreach(struct pbuf *p, enum icmp6_dur_code c);
void icmp6_packet_too_big(struct pbuf *p, u32_t mtu);
void icmp6_time_exceeded(struct pbuf *p, enum icmp6_te_code c);
void icmp6_time_exceeded_with_addrs(struct pbuf *p, enum icmp6_te_code c,
    const ip6_addr_t *src_addr, const ip6_addr_t *dest_addr);
void icmp6_param_problem(struct pbuf *p, enum icmp6_pp_code c, u32_t pointer);

#endif /* LWIP_ICMP6 && LWIP_IPV6 */

#if LWIP_IPV6 && LWIP_RAW

/* raw socket checksum offset for ICMPV6 */
#define IPV6_ICMP_CHKSUM_OFFSET 2

/* raw socket checksum offset for UDP */
#define IPV6_UDP_CHKSUM_OFFSET 6

/* raw socket checksum offset for TCP */
#define IPV6_TCP_CHKSUM_OFFSET 16

/* checksum length */
#define LWIP_IPV6_CHKSUM_LEN 2

/*
 * ICMP6 structure filter length
 */
#define ICMP_FILTER_LENGTH 8  /* ICMP6 structure filter length */

/* icmp6 const filter value */
#define ICMP6_FILTER_VAL 5

/* icmp6 const filter integer bits  */
#define ICMP6_FILTER_INTVAL 31

/* icmp6 max value filter value */
#define ICMP6_FILTER_MAXVAL 0xFF


#if !LWIP_LITEOS_COMPAT
/*
 * socket option for ICMP6 filering support
 */
#define ICMP6_FILTER       1 /* ICMP filter support */


/*
 * stucture to hold the sockets filter state to allow packets to application or not.
 * Max size of structure is 256 bits.
 */
struct icmp6_filter {
  u32_t icmp6_filt[ICMP_FILTER_LENGTH];  /* 8*32 = 256 bits */
};

/*
 * filter macro to check if the raw socket is blocked or not.
 */
#define ICMP6_FILTER_WILLPASS(type, filterp) \
  ((((filterp)->icmp6_filt[(type) >> ICMP6_FILTER_VAL]) & (1U << ((type) & ICMP6_FILTER_INTVAL))) == 0)


/*
 * filter macro to check if the raw socket to blocked
 */
#define ICMP6_FILTER_WILLBLOCK(type, filterp) \
  ((((filterp)->icmp6_filt[(type) >> ICMP6_FILTER_VAL]) & (1U << ((type) & ICMP6_FILTER_INTVAL))) != 0)

/*
 * filter macro to allow raw socket for giving the data to application
 */
#define ICMP6_FILTER_SETPASS(type, filterp) \
  (((filterp)->icmp6_filt[(type) >> (ICMP6_FILTER_VAL)]) &= (~(u32_t)(1U << ((type) & ICMP6_FILTER_INTVAL))))


/*
 * filter macro to block raw socket from giving the data to application
 */
#define ICMP6_FILTER_SETBLOCK(type, filterp) \
  (((filterp)->icmp6_filt[(type) >> ICMP6_FILTER_VAL]) |= (1U << ((type) & ICMP6_FILTER_INTVAL)))

/*
 * filter macro to allow all raw socket to give the data to application
 */
#define ICMP6_FILTER_SETPASSALL(filterp) \
    (void)memset((filterp), 0x00, sizeof(struct icmp6_filter))

/*
 * filter macro to block all raw socket from giving the data to application
 */
#define ICMP6_FILTER_SETBLOCKALL(filterp) \
    (void)memset((filterp), ICMP6_FILTER_MAXVAL, sizeof(struct icmp6_filter))

#endif

#endif

#if LWIP_IPV6 && (LWIP_RPL || LWIP_RIPPLE)
void lwip_handle_rpl_ctrl_msg
(
  const struct icmpv6_hdr *icmp_hdr,
  struct pbuf *buf,
  const ip6_addr_t *srcip,
  const ip6_addr_t *dstip,
  struct netif *intf
);
#endif

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_HDR_ICMP6_H */
