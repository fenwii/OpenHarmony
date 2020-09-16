/**
 * @file
 * DNS API
 */

/**
 * lwip DNS resolver header file.

 * Author: Jim Pettinato
 *   April 2007

 * ported from uIP resolv.c Copyright (c) 2002-2003, Adam Dunkels.
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
 */

#ifndef LWIP_HDR_DNS_H
#define LWIP_HDR_DNS_H

#include "lwip/opt.h"

#if LWIP_DNS

#include "lwip/ip_addr.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

/** DNS timer period */
#define DNS_TMR_INTERVAL          1000

/** @cond liteos */
/** DNS resolve types: */
/** LWIP_DNS_ADDRTYPE_DEFAULT can be set to
    any one of the following values which describes the default DNS Resolution behaviour */
/** Try to resolve hostname to an IPv4 address only */
#define LWIP_DNS_ADDRTYPE_IPV4      0
/** Try to resolve hostname to an IPv6 address only */
#define LWIP_DNS_ADDRTYPE_IPV6      1
/** Try to resolve hostname to an IPv4 address, if some failure happends or no A records recieved,
   then try to resolve the hostname to an IPv6 address */
/** If LWIP_DNS_ADDRTYPE_DEFAULT  is not defined, then LWIP_DNS_ADDRTYPE_IPV4_IPV6 will be taken as default */
#define LWIP_DNS_ADDRTYPE_IPV4_IPV6 2
/** Try to resolve hostname to an IPv6 address, if some failure happends or no AAAA records recieved,
   then try to resolve the hostname to an IPv4 address */
#define LWIP_DNS_ADDRTYPE_IPV6_IPV4 3
/** @endcond */
#if LWIP_IPV4 && LWIP_IPV6
#ifndef LWIP_DNS_ADDRTYPE_DEFAULT
#define LWIP_DNS_ADDRTYPE_DEFAULT   LWIP_DNS_ADDRTYPE_IPV4_IPV6
#endif
#elif LWIP_IPV4
#define LWIP_DNS_ADDRTYPE_DEFAULT   LWIP_DNS_ADDRTYPE_IPV4
#else
#define LWIP_DNS_ADDRTYPE_DEFAULT   LWIP_DNS_ADDRTYPE_IPV6
#endif /*LWIP_IPV4 && LWIP_IPV6 */

#define REVERSE_PTR_TOP_DOMAIN "arpa"
#if LWIP_IPV4
#define REVERSE_PTR_V4_DOMAIN "in-addr"
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
#define REVERSE_PTR_V6_DOMAIN "ip6"
#endif /* LWIP_IPV6 */

#if DNS_LOCAL_HOSTLIST
/** struct used for local host-list */
struct local_hostlist_entry {
  /** static hostname */
  const char *name;
  /** static host address in network byteorder */
  ip_addr_t addr;
  struct local_hostlist_entry *next;
};
#define DNS_LOCAL_HOSTLIST_ELEM(name, addr_init) {name, addr_init, NULL}
#if DNS_LOCAL_HOSTLIST_IS_DYNAMIC
#ifndef DNS_LOCAL_HOSTLIST_MAX_NAMELEN
#define DNS_LOCAL_HOSTLIST_MAX_NAMELEN  DNS_MAX_NAME_LENGTH
#endif
#define LOCALHOSTLIST_ELEM_SIZE ((sizeof(struct local_hostlist_entry) + DNS_LOCAL_HOSTLIST_MAX_NAMELEN + 1))
#endif /* DNS_LOCAL_HOSTLIST_IS_DYNAMIC */
#endif /* DNS_LOCAL_HOSTLIST */

#if LWIP_IPV4
extern const ip_addr_t dns_mquery_v4group;
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
extern const ip_addr_t dns_mquery_v6group;
#endif /* LWIP_IPV6 */

/** Callback which is invoked when a hostname is found.
 * A function of this type must be implemented by the application using the DNS resolver.
 * @param name pointer to the name that was looked up.
 * @param ipaddr pointer to an ip_addr_t containing the IP address of the hostname,
 *        or NULL if the name could not be found (or on any other error).
 * @param count
 *        If the addr is not NULL, then count is the count number of resolved IP address for hostname.
 *        If the addr is NULL, then count is the error code (because h_errno is not implemented yet).
 * @param callback_arg a user-specified callback argument passed to dns_gethostbyname.
 */
typedef void (*dns_found_callback)(const char *name, const ip_addr_t *ipaddr, u32_t count, void *callback_arg);


/*
 * Callback which is invoked when a PTR record for the IP-Address is found.
 * A function of this type must be implemented by the application using the DNS resolver.
 * @param ipaddr pointer to ip_addr_t containing the IP address whose PTR record was looked up.
 * @param name pointer to the name that points to ipaddr.
 *        or NULL if the name could not be found (or on any other error).
 * @param count
 *        If the name is not NULL, then count is the count number of resolved domain name for IP address.
 *        If the name is NULL, then count is the error code (because h_errno is not implemented yet).
 * @param callback_arg a user-specified callback argument passed to reverse_dns_getnamebyhost
 */
typedef void (*reverse_dns_found_callback)(const char *name, u32_t count, void *callback_arg);

void dns_init(void);
void dns_tmr(void);
void dns_setserver(u8_t numdns, const ip_addr_t *dnsserver);
const ip_addr_t *dns_getserver(u8_t numdns);
#if LWIP_SNTP || (defined LWIP_TESTBED)
err_t dns_gethostbyname(const char *hostname, ip_addr_t *addr, u32_t *count,
                        dns_found_callback found, void *callback_arg);
#endif /* LWIP_SNTP || (defined LWIP_TESTBED) */
err_t dns_gethostbyname_addrtype(const char *hostname, ip_addr_t *addr, u32_t *count,
                                 dns_found_callback found, void *callback_arg,
                                 u8_t dns_addrtype);

err_t reverse_dns_getnamebyhost(ip_addr_t *ipaddr, char *hostname, reverse_dns_found_callback found,
                                void *callback_arg);
#if DNS_LOCAL_HOSTLIST
size_t dns_local_iterate(dns_found_callback iterator_fn, void *iterator_arg);
err_t dns_local_lookup(const char *hostname, ip_addr_t *addr, u8_t dns_addrtype);
#if DNS_LOCAL_HOSTLIST_IS_DYNAMIC
int dns_local_removehost(const char *hostname, const ip_addr_t *addr);
err_t dns_local_addhost(const char *hostname, const ip_addr_t *addr);
#endif /* DNS_LOCAL_HOSTLIST_IS_DYNAMIC */
#endif /* DNS_LOCAL_HOSTLIST */

#if LWIP_LOWPOWER
u32_t dns_tmr_tick(void);
#endif

#if LWIP_ENABLE_BASIC_SHELL_CMD || LWIP_API_RICH
/** @defgroup DNS_Interfaces
* @ingroup User_interfaces
* This section contains the DNS Interfaces.
*/
/*
Func Name:  lwip_dns_setserver
*/
/**
* @ingroup DNS_Interfaces
* @brief This API is used to set the DNS server IP.
*
* @param[in]    numdns      Index of the DNS server to set [NA]
* @param[in]    dnsserver   IP_add of the DNS server to set [NA]
*
* @return
*  - ERR_OK: On success
*  - ERR_MEM: On failure due to memory
*  - ERR_VAL: On failure due to Illegal value
*
*
* @note
* 1. Index of the dns server array should be passed as numdns, it should
* be in the range from 0 to (DNS_MAX_SERVERS-1). If it's not in the range
* then this API fails with return value ERR_VAL.\n
* 2. If NULL is passed to dnsserver, then IPADDR_ANY is updated.\n
* 3. This is a Thread safe API, this needs to be used in application instead
* of dns_setserver.\n
*
* @par Related Topics
* lwip_dns_getserver()
*/
err_t lwip_dns_setserver(u8_t numdns, ip_addr_t *dnsserver);
/*
Func Name:  lwip_dns_getserver
*/
/**
* @ingroup DNS_Interfaces
* @brief  This API is used to obtain  the configured DNS server. This API
*  Gets the DNS server address on the index numdns and updates dnsserver.
*  Application should pass valid pointer of type ip_addr_t as dnsserver.
*
* @param[in]    numdns   index of the DNS server to set.
* @param[out]   dnsserver pointer to IP_add variable.
*
* @par Return values
*  - ERR_OK: On success
*  - ERR_MEM: On failure due to memory
*  - ERR_VAL: On failure due to Illegal value
*
* @note
* 1. Index of the dns server array should be passed as numdns, it should
* be in the range from 0 to (DNS_MAX_SERVERS-1). If it's not in the range
* then it updates dnsserver to be IPADDR_ANY.\n
* 2. If NULL is passed to dnsserver, then this API fails with return value
* ERR_VAL.\n
* 3. This is a Thread safe API, this needs to be used in application instead
* of dns_getserver.\n
*
* @par Related Topics
* lwip_dns_setserver()
*/
err_t lwip_dns_getserver(u8_t numdns, ip_addr_t *dnsserver);
#endif /* LWIP_ENABLE_BASIC_SHELL_CMD || LWIP_API_RICH */

u16_t dns_skip_name(const struct pbuf *p, u16_t query_idx);
u8_t lwip_dns_get_server_cnt(u8_t *ip4cnt, u8_t *ip6cnt);
err_t lwip_dns_copy_ip6server_addr(const struct netif *nif, ip6_addr_t *ipaddr, u8_t num);

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_DNS */

#endif /* LWIP_HDR_DNS_H */
