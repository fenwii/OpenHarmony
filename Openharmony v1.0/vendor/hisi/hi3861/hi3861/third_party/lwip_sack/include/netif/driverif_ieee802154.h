#ifndef __DRIVERIF_IEEE802154__H__
#define __DRIVERIF_IEEE802154__H__
/**
 *  @file driverif_ieee802154.h
 */
#include "lwip/opt.h"
#include "netif/etharp.h"
#include "lwip/netif.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#if !defined NETIF_USE_6BYTE_HWLEN_FOR_IEEE802154 || (NETIF_USE_6BYTE_HWLEN_FOR_IEEE802154 == 0)
#ifndef NETIF_802154_MAX_HWADDR_LEN
#define NETIF_802154_MAX_HWADDR_LEN 8
#endif
#endif

err_t ieee802154driverif_init(struct netif *netif);

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* __DRIVERIF_IEEE802154__H__ */

