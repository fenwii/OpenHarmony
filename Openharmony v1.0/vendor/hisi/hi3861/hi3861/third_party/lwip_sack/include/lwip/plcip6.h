/*
 * Description: declaration of PLC IPv6 APIs
 */

#ifndef LWIP_HDR_PLCIP6_H
#define LWIP_HDR_PLCIP6_H

#include "lwip/opt.h"

#if LWIP_IPV6 && LWIP_PLC /* don't build if not configured for use in
lwipopts.h */

#include "lwip/pbuf.h"
#include "lwip/ip6.h"
#include "lwip/ip6_addr.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

err_t output_ip6_onplc(struct netif *netif, struct pbuf *p,
                       const ip6_addr_t *ip6addr);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6 && LWIP_ETHERNET */

#endif /* LWIP_HDR_PLCIP6_H */

