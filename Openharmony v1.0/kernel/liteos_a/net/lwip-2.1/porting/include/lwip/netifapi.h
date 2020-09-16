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

#ifndef _LWIP_PORTING_NETIFAPI_H_
#define _LWIP_PORTING_NETIFAPI_H_

#include_next <lwip/netifapi.h>

#ifdef __cplusplus
extern "C" {
#endif

err_t netifapi_dhcps_start(struct netif *netif, char *start_ip, u16_t ip_num);
err_t netifapi_dhcps_stop(struct netif *netif);

#define netifapi_dhcp_cleanup(n)          netifapi_netif_common(n, dhcp_cleanup, NULL)
#define netifapi_dhcp_is_bound(n)         netifapi_netif_common(n, NULL, dhcp_is_bound)

void netifapi_netif_rmv_ip6_address(struct netif *netif, ip_addr_t *ipaddr);

#ifndef __LWIP__
#define netifapi_netif_add(a, b, c, d)       netifapi_netif_add(a, b, c, d, (a)->state, driverif_init, tcpip_input)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LWIP_PORTING_NETIFAPI_H_ */
