/**
 * @file
 * This file (together with sockets.h) aims to provide structs and functions from
 * - arpa/inet.h
 * - netinet/in.h
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
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
#ifndef LWIP_HDR_INET_H
#define LWIP_HDR_INET_H

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/ip_addr.h"
#include "lwip/ip6_addr.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif


#if !LWIP_LITEOS_COMPAT
/* If your port already typedef's in_addr_t, define IN_ADDR_T_DEFINED
   to prevent this code from redefining it. */
#if !defined(in_addr_t) && !defined(IN_ADDR_T_DEFINED)
typedef u32_t in_addr_t;
#endif
/**
*
* @brief Provides a binary notation of the IPv4 address.
*/
struct in_addr {
  in_addr_t s_addr; /** <  Specifies the s_addr. */
};


/** 255.255.255.255 */
#define INADDR_NONE         IPADDR_NONE
/** 127.0.0.1 */
#define INADDR_LOOPBACK     IPADDR_LOOPBACK
/** 0.0.0.0 */
#define INADDR_ANY          IPADDR_ANY
/** 255.255.255.255 */
#define INADDR_BROADCAST    IPADDR_BROADCAST


/* Definitions of the bits in an (IPv4) Internet address integer.

   On subnets, host and network parts are found according to
   the subnet mask, not these masks.  */
#define IN_CLASSA(a)        IP_CLASSA(a)
#define IN_CLASSA_NET       IP_CLASSA_NET
#define IN_CLASSA_NSHIFT    IP_CLASSA_NSHIFT
#define IN_CLASSA_HOST      IP_CLASSA_HOST
#define IN_CLASSA_MAX       IP_CLASSA_MAX

#define IN_CLASSB(b)        IP_CLASSB(b)
#define IN_CLASSB_NET       IP_CLASSB_NET
#define IN_CLASSB_NSHIFT    IP_CLASSB_NSHIFT
#define IN_CLASSB_HOST      IP_CLASSB_HOST
#define IN_CLASSB_MAX       IP_CLASSB_MAX

#define IN_CLASSC(c)        IP_CLASSC(c)
#define IN_CLASSC_NET       IP_CLASSC_NET
#define IN_CLASSC_NSHIFT    IP_CLASSC_NSHIFT
#define IN_CLASSC_HOST      IP_CLASSC_HOST
#define IN_CLASSC_MAX       IP_CLASSC_MAX

#define IN_CLASSD(d)        IP_CLASSD(d)
#define IN_CLASSD_NET       IP_CLASSD_NET     /* These ones aren't really */
#define IN_CLASSD_NSHIFT    IP_CLASSD_NSHIFT  /*   net and host fields, but */
#define IN_CLASSD_HOST      IP_CLASSD_HOST    /*   routing needn't know. */
#define IN_CLASSD_MAX       IP_CLASSD_MAX

#define IN_MULTICAST(a)     IP_MULTICAST(a)

#define IN_EXPERIMENTAL(a)  IP_EXPERIMENTAL(a)
#define IN_BADCLASS(a)      IP_BADCLASS(a)

#define IN_LOOPBACKNET      IP_LOOPBACKNET

struct in6_addr {
  union {
    u32_t u32_addr[4];
    u8_t  u8_addr[16];
  } un;
#define s6_addr  un.u8_addr
};

/**
 * This macro is used to initialize a variable of type struct in6_addr
 * to the IPv6 wildcard address.
 */
#ifndef IN6ADDR_ANY_INIT
#define IN6ADDR_ANY_INIT {{{0, 0, 0, 0}}}
#endif
/**
 * This macro is used to initialize a variable of type struct in6_addr
 * to the IPv6 loopback address.
 */
#ifndef IN6ADDR_LOOPBACK_INIT
#define IN6ADDR_LOOPBACK_INIT {{{0, 0, 0, PP_HTONL(1)}}}
#endif

#endif /* !LWIP_LITEOS_COMPAT */


/** This variable is initialized by the system to contain the wildcard IPv6 address. */
extern const struct in6_addr in6addr_any;
/* [Added new structure for ipv6 loopback as per section 3.9 of rfc 2553/3493] */
extern const struct in6_addr in6addr_loopback;

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN     IP4ADDR_STRLEN_MAX
#endif
#if LWIP_IPV6
#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN    IP6ADDR_STRLEN_MAX
#endif
#endif

#if LWIP_IPV4

#define inet_addr_from_ip4addr(target_inaddr, source_ipaddr) ((target_inaddr)->s_addr = ip4_addr_get_u32(source_ipaddr))
#define inet_addr_to_ip4addr(target_ipaddr, source_inaddr)   (ip4_addr_set_u32(target_ipaddr, (source_inaddr)->s_addr))

/* directly map this to the lwip internal functions */
/**
* @defgroup INET_Interfaces  INET Interfaces
* This section contains information about INET interfaces.
* @ingroup User_interfaces
*/
/**
* @ingroup INET_Interfaces
* @brief
* This function is used to convert the IPv4 address from string notation (number and dot format)
* to binary notation of network byte order.
*
* @param[in]    cp  Indicates a pointer to the IPv4 address string.
*
* @returns
*  Valid IP address: On success, in unsigned int (32-bit) format. \n
*  IPADDR_NONE: On failure \n

* @note
* This interface will be available as function if LWIP_INET_ADDR_FUNC is enabled,
* otherwise it will be available as macro.
*/
#if LWIP_INET_ADDR_FUNC
unsigned int inet_addr(const char *cp);
#else
#define inet_addr(cp)         ipaddr_addr(cp)
#endif

/*
Func Name:  inet_aton
*/
/**
* @ingroup INET_Interfaces
* @brief
* This function is used to convert an IPv4 address from string notation (number and dot format)
* to binary notation of network byte order and store it in the structure that the addr parameter points to.
*
* @param[in]    cp     Indicates a pointer to an IPv4 address string.
* @param[out]  addr  Indicates a the generated binary notation of the IPv4 address.
* @returns
*  1 : On success\n
*  0 : On failure \n
* @note
* - This interface is similar to inet_addr(). The only difference is that the generated binary notation
* of IPv4 address is updated in the addr parameter, instead of returning it.
* - This interface is available as a function if LWIP_INET_ATON_FUNC is enabled,
* otherwise it will be available as macro.
*/
#if LWIP_INET_ATON_FUNC
int inet_aton(const char *cp, struct in_addr *addr);
#else
#define inet_aton(cp, addr)             ip4addr_aton(cp, (ip4_addr_t*)addr)
#endif


/*
Func Name:  inet_ntoa
*/
/**
* @ingroup INET_Interfaces
* @brief
* This function is used to convert an IPv4 address from binary notation (network byte order)
* to string notation (number and dot format).
*
* @param[in]    in     Indicates a pointer to the binary notation of an IPv4 address.
*
* @returns
*  Valid pointer: On success, returns a pointer to the string notation of the IPv4 address. \n
*  NULL: On failure \n
*
* @par Note
* This interface is available as a function if LWIP_INET_NTOA_FUNC is enabled,
* otherwise it will be available as macro.
*
*/
#if LWIP_INET_NTOA_FUNC
char *inet_ntoa (struct in_addr in);
#else
#define inet_ntoa(addr)                 ip4addr_ntoa((const ip4_addr_t*)&(addr))
#endif
/**
* @ingroup INET_Interfaces


* @brief
* This function is used to convert an IPv4 address from binary notation (network byte order)
* to string notation (number and dot format). This is the reentrant API of inet_ntoa. The
* generated string notation IPv4 address is updated in the buffer passed by the user.
*
* @param[in]   addr     Indicates the binary notation of an IPv4 address.
* @param[out]  buf   Indicates a pointer to a user buffer, in which the output string format
 of the IPv4 address is updated.
* @param[in]    buflen  Indicates the length of the user buffer.
*
* @returns
*  Valid pointer : On success, returns a pointer to the buffer passed by the user in buf. \n
*  NULL : On failure \n
*

* @note
* This interface is available as only macro.
*
*/
#define inet_ntoa_r(addr, buf, buflen)  ip4addr_ntoa_r((const ip4_addr_t*)&(addr), buf, buflen)

#endif /* LWIP_IPV4 */

#if LWIP_IPV6

#if LWIP_LITEOS_COMPAT
#define inet6_addr_from_ip6addr(target_in6addr, source_ip6addr) { \
  (void)memcpy((target_in6addr)->s6_addr, (source_ip6addr)->addr, sizeof(struct ip6_addr)); }
#define inet6_addr_to_ip6addr(target_ip6addr, source_in6addr)   { \
  (void)memcpy((target_ip6addr)->addr, (source_in6addr)->s6_addr, sizeof(struct ip6_addr)); }
#else
#define inet6_addr_from_ip6addr(target_in6addr, source_ip6addr) do { \
  (target_in6addr)->un.u32_addr[0] = (source_ip6addr)->addr[0];   \
  (target_in6addr)->un.u32_addr[1] = (source_ip6addr)->addr[1];   \
  (target_in6addr)->un.u32_addr[2] = (source_ip6addr)->addr[2];   \
  (target_in6addr)->un.u32_addr[3] = (source_ip6addr)->addr[3]; } while (0)

#define inet6_addr_to_ip6addr(target_ip6addr, source_in6addr) do {   \
  (target_ip6addr)->addr[0] = (source_in6addr)->un.u32_addr[0];   \
  (target_ip6addr)->addr[1] = (source_in6addr)->un.u32_addr[1];   \
  (target_ip6addr)->addr[2] = (source_in6addr)->un.u32_addr[2];   \
  (target_ip6addr)->addr[3] = (source_in6addr)->un.u32_addr[3]; } while (0)
#endif

/* directly map this to the lwip internal functions */
#define inet6_aton(cp, addr)            ip6addr_aton(cp, (ip6_addr_t*)addr)
#define inet6_ntoa(addr)                ip6addr_ntoa((const ip6_addr_t*)&(addr))
/**
* @ingroup INET_Interfaces
* @brief
* This interface is used to convert an IPv6 address from binary notation (network byte order)
* to string notation (colon format). This is the reentrant API of inet6_ntoa. The
* generated string notation IPv6 address is updated in the buffer passed by the user.
*
* @param[in]   addr     Indicates the binary notation of an IPv6 address.
* @param[out]  buf   Indicates a pointer to a user buffer, in which the output string
 format of the IPv6 address is updated.
* @param[in]    buflen  Indicates the length of the user buffer.
*
* @returns
*  Valid pointer: On success, returns a pointer to the buffer passed by the user in buf. \n
*  NULL: On failure \n

*
* @par Note
* This interface is available as only macro.

*
*/
#define inet6_ntoa_r(addr, buf, buflen) ip6addr_ntoa_r((const ip6_addr_t*)&(addr), buf, buflen)

#endif /* LWIP_IPV6 */


#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_HDR_INET_H */
