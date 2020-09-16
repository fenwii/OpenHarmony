/*
 * Description: declaration of driverif APIs
 */

#ifndef __DRIVERIF_H__
#define __DRIVERIF_H__
/**
 *  @file driverif.h
 */
/**
 * @defgroup System_interfaces System Interfaces
 *  This contains all the system interfaces.
 */
#include "lwip/opt.h"
#include "netif/etharp.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

/** Type of link layer, these macros should be used for link_layer_type of struct netif */
#define LOOPBACK_IF         772
#define LOOPBACK_MTU        ((16 * 1024) + 20 + 20 + 12)
/** Type of link layer, these macros should be used for link_layer_type of struct netif */
#define ETHERNET_DRIVER_IF  1
/** Type of link layer, these macros should be used for link_layer_type of struct netif */
#define WIFI_DRIVER_IF      801
/** Type of link layer, these macros should be used for link_layer_type of struct netif */
#define PLC_DRIVER_IF            10
/** Type of link layer, these macros should be used for link_layer_type of struct netif */
#define IEEE802154_DRIVER_IF     11

/** Short names of link layer */
#define LOOPBACK_IFNAME "lo"
/** Short names of link layer */
#define ETHERNET_IFNAME "eth"
/** Short names of link layer */
#define WIFI_IFNAME "wlan"
#define PLC_IFNAME "plc"
#define RF_IFNAME "ieee802154"

struct linklayer_addr;

/**
 * @defgroup Driver_Interfaces Driver Interfaces
 * This section provides information about the Network driver related interfaces.
 */
/** Function pointer of driver send function */
typedef void (*drv_send_fn)(struct netif *netif, struct pbuf *p);

#if LWIP_IPV6
typedef err_t (*drv_send_lln_fn)(struct netif *netif, struct pbuf *p, struct linklayer_addr *destmac);
#endif

/** Function pointer of driver set hw address function */
/* This callback function should return 0 in case of success */
typedef u8_t (*drv_set_hwaddr_fn)(struct netif *netif, u8_t *addr, u8_t len);

err_t driverif_init(struct netif *netif);

#if LWIP_NETIF_PROMISC
/** Function pointer of driver set/unset promiscuous mode on interface */
typedef void (*drv_config_fn)(struct netif *netif, u32_t config_flags, u8_t setBit);
#endif /* LWIP_NETIF_PROMISC */

/*
 * Func Name:  driverif_input
 */
/**
 * @ingroup   Driver_Interfaces
 * @brief     This API must be called by the network driver to pass the input packet to lwIP.
 * Before calling this API, the driver has to keep the packet in the pbuf structure. The driver must
 * call pbuf_alloc() with the type as PBUF_RAM to create the pbuf structure. The driver
 * has to pass the pbuf structure to this API to add the pbuf into the TCPIP thread.
 * After this packet is processed by TCPIP thread, pbuf will be freed. The driver is not required to
 * free the pbuf.
 * @param[in]    netif                 Indicates the lwIP network interface.
 * @param[in]    p                     Indicates the packet in the pbuf structure.
 * @return None
 * @note
 * None
 */
void  driverif_input(struct netif *netif, struct pbuf *p);

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif

