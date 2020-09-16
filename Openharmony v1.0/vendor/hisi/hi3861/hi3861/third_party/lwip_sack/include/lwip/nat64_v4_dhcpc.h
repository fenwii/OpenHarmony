/*
 * Description: NAT64 dhcp proxy header
 */
#ifndef LWIP_HDR_NAT64_V4_DHCPC_H
#define LWIP_HDR_NAT64_V4_DHCPC_H
#include "lwip/opt.h"

#if LWIP_NAT64
#include "lwip/lwip_rpl.h"
#include "lwip/netif.h"

#define NAT64_DHCP_EVENT_RELEASE 0
#define NAT64_DHCP_EVENT_OFFER 1
#define NAT64_DHCP_EVENT_RENEW 2

err_t nat64_dhcp_request_ip(struct netif *ntf, const linklayer_addr_t *lladdr);
err_t nat64_dhcp_stop(struct netif *ntf, const linklayer_addr_t *lladdr);
void nat64_dhcp_ip4_event(const u8_t *mac, u8_t maclen, const ip4_addr_t *ipaddr, int event);

#endif
#endif
