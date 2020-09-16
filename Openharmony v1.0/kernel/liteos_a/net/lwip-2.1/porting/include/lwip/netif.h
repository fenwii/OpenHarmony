/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LWIP_PORTING_NETIF_H_
#define _LWIP_PORTING_NETIF_H_

#include <net/if.h> // For IFNAMSIZ/IF_NAMESIZE and `struct ifreq', by `lwip/netif.h' and `api/sockets.c'
#include <netinet/ip.h> // For IP_OFFMASK, by `core/ipv4/ip4_frag.c'

struct dhcps;
#define linkoutput      linkoutput; \
                        void (*drv_send)(struct netif *netif, struct pbuf *p); \
                        u8_t (*drv_set_hwaddr)(struct netif *netif, u8_t *addr, u8_t len); \
                        void (*drv_config)(struct netif *netif, u32_t config_flags, u8_t setBit); \
                        struct dhcps *dhcps; \
                        char full_name[IFNAMSIZ]; \
                        u16_t link_layer_type
#include_next <lwip/netif.h>
#undef linkoutput

#include <lwip/etharp.h> // For ETHARP_HWADDR_LEN, by `hieth-sf src/interface.c' and `wal/wal_net.c'

#ifdef __cplusplus
extern "C" {
#endif

// redefine NETIF_NAMESIZE which was defined in netif.h
#undef NETIF_NAMESIZE
#define NETIF_NAMESIZE IFNAMSIZ

#define LOOPBACK_IF         0 // 772
#define ETHERNET_DRIVER_IF  1
#define WIFI_DRIVER_IF      801

err_t driverif_init(struct netif *netif);
void driverif_input(struct netif *netif, struct pbuf *p);

#ifndef __LWIP__
struct netif *netifapi_netif_find_by_name(const char *name);
#define PF_PKT_SUPPORT              1 // For netif->drv_config
#define netif_find(name)            netifapi_netif_find_by_name(name)
#define netif_add(a, b, c, d)       netif_add(a, b, c, d, (a)->state, driverif_init, tcpip_input)
#else /* __LWIP__ */
#define netif_get_name(netif)       ((netif)->full_name)
#endif /* __LWIP__ */

#ifdef __cplusplus
}
#endif

#endif /* _LWIP_PORTING_NETIF_H_ */
