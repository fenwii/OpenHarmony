/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
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
 *
 * Description: This file provides information for ethtool. reference to linux kernel :include/uapi/linux/ethtool.h
 * Author: none
 * Create: 2013
 */

#ifndef __ETHTOOL_H
#define __ETHTOOL_H

#include "lwip/opt.h"

#if LWIP_NETIF_ETHTOOL /* don't build if not configured for use in lwipopts.h */
#include "lwip/netif.h"
#include "lwip/sockets.h"
#include "arch/cc.h"
#include "netif/ifaddrs.h"
#if LWIP_LITEOS_COMPAT && !LWIP_LINUX_COMPAT
#include <liteos/ethtool.h>
#endif

#if LWIP_LITEOS_COMPAT && LWIP_LINUX_COMPAT
#include <linux/ethtool.h>
#endif

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#if !LWIP_LITEOS_COMPAT
#define ETHTOOL_GSET    0x00000001
#define ETHTOOL_SSET    0x00000002
#define ETHTOOL_GLINK   0x0000000a

/** @brief This struct is to pass data for link control and status */
struct ethtool_cmd {
  u32_t cmd;               /**< Command number = %ETHTOOL_GSET or %ETHTOOL_SSET */
  u32_t supported;         /**< Bitmask of %SUPPORTED_* flags for the link modes, physical connectors and other link
  features for which the interface supports autonegotiation or auto-detection. Read-only. */
  u32_t advertising;       /**< Bitmask of %ADVERTISED_* flags for the link modes, physical connectors and other link
  features that are advertised through autonegotiation or enabled for auto-detection. */
  u16_t speed;             /**< Low bits of the speed, 1Mb units, 0 to INT_MAX or SPEED_UNKNOWN */
  u8_t duplex;             /**< Duplex mode; one of %DUPLEX_* */
  u8_t port;               /**< Physical connector type; one of %PORT_* */
  u8_t phy_address;        /**< MDIO address of PHY (transceiver); 0 or 255 if not applicable. */
  u8_t transceiver;        /**< Historically used to distinguish different possible PHY types, but not in a consistent
  way.  Deprecated. */
  u8_t autoneg;            /**< Enable/disable autonegotiation and auto-detection; either %AUTONEG_DISABLE or
  %AUTONEG_ENABLE */
  u8_t mdio_support;       /**< Bitmask of %ETH_MDIO_SUPPORTS_* flags for the MDIO protocols supported by the interface;
  0 if unknown. Read-only. */
  u32_t maxtxpkt;          /**< Historically used to report TX IRQ coalescing; Read-only; deprecated. */
  u32_t maxrxpkt;          /**< Historically used to report RX IRQ coalescing; Read-only; deprecated. */
  u16_t speed_hi;          /**< High bits of the speed, 1Mb units, 0 to INT_MAX or SPEED_UNKNOWN */
  u8_t eth_tp_mdix;        /**< Ethernet twisted-pair MDI(-X) status; one of %ETH_TP_MDI_*. If the status is unknown or
  not applicable, the value will be %ETH_TP_MDI_INVALID. Read-only. */
  u8_t eth_tp_mdix_ctrl;   /**< Ethernet twisted pair MDI(-X) control; one of %ETH_TP_MDI_*.  If MDI(-X) control is not
  implemented, reads yield %ETH_TP_MDI_INVALID and writes may be ignored or rejected. When written successfully, the
  link should be renegotiated if necessary. */
  u32_t lp_advertising;    /**< Bitmask of %ADVERTISED_* flags for the link modes and other link features that the link
  partner advertised through autonegotiation; 0 if unknown or not applicable. Read-only. */
  u32_t reserved[2];
};

/** @brief This structure is for passing single values. */
struct ethtool_value {
  u32_t cmd; /**< Indicates command. */
  u32_t data; /**< Indicates data. */
};
#endif

/**
 * @brief  Provides optional netdev operations.
 *
 * All operations are optional (that is, the function pointer may be set
 * to %NULL) and callers must take this into account.  Callers must
 * hold the RTNL lock.
 *
 * See the structures used by these operations for further documentation.
 *
 * See &struct net_device and &struct net_device_ops for documentation
 * of the generic netdev features interface.
 */
struct ethtool_ops {
  /**
   * < Reports whether physical link is up. Will only be called if the netdev is up.
   * Should usually be set to ethtool_op_get_link(), which usesnetif_carrier_ok().
   */
  s32_t (*get_link)(struct netif *netif);
  s32_t (*get_settings)(struct netif *netif, struct ethtool_cmd *cmd); /**< Gets the current settings */
  s32_t (*set_settings)(struct netif *netif, struct ethtool_cmd *cmd); /**< Configures settings */
  /**< Function to be called before any other operation.  Returns a  negative error code or zero. */
  int (*begin)(struct netif *netif);
  /**
   * < Function to be called after any other operation except @begin.
   * Will be called even if the other operation failed.
   */
  void (*complete)(struct netif *netif);
};

s32_t dev_ethtool(struct netif *netif, struct ifreq *ifr);
/* [VPPTECH-449] TCP_INFO support */
#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_NETIF_ETHTOOL */

#endif /* __ETHTOOL_H */

