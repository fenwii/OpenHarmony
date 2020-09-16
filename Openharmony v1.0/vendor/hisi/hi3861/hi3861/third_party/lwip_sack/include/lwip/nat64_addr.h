/*
 * Description: NAT64 address header
 */
#ifndef LWIP_HDR_NAT64_ADDR_H
#define LWIP_HDR_NAT64_ADDR_H

#include "lwip/lwip_rpl.h"
#include "lwip/nat64.h"
#if LWIP_NAT64
int nat64_stateless_addr_4to6(const ip4_addr_t *ip4addr, ip6_addr_t *ip6addr);
int nat64_addr_mac_to6(const linklayer_addr_t *mac, ip6_addr_t *ip6addr);
int nat64_stateless_addr_6to4(const ip6_addr_t *ip6addr, ip4_addr_t *ip4addr);
int nat64_addr_6to4(const ip6_addr_t *ip6addr, ip4_addr_t *ip4addr);
int nat64_addr_is_ip4(const ip6_addr_t *ip6addr);
int nat64_entry_to6(const nat64_entry_t *entry, ip6_addr_t *ip6addr);
#endif
#endif
