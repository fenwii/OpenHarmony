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

#include <lwip/err.h>
#include <lwip/pbuf.h>
#include <lwip/dhcp.h>
#include <lwip/netifapi.h>

#include "usb_eth_drv.h"
#include "securec.h"
#include "los_printf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

static void eth_drv_send(struct netif *usb_netif, struct pbuf *p);

#if PF_PKT_SUPPORT
static void
eth_drv_config(struct netif *ni, u32_t cflags, u8_t setBit)
{
	LWIP_UNUSED_ARG(ni);
	LWIP_UNUSED_ARG(cflags);
	LWIP_UNUSED_ARG(setBit);
	/* Nothing to be done for now */
}
#endif

/*
 * This function is called during system initialization to register a
 * network interface with the system.
 */

static void
eth_drv_init(struct los_eth_driver *sc, unsigned char *enaddr)
{
	struct netif *usb_netif = &sc->ac_if;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc*)sc->driver_context;
	ip4_addr_t ipaddr, netmask, gw;
	err_t ret;

	IP4_ADDR(&gw, 192, 168, 0, 1);
	IP4_ADDR(&ipaddr, 192, 168, 0, 100);
	IP4_ADDR(&netmask, 255, 255, 255, 0);

	usb_netif->state = sc;
	usb_netif->drv_send = eth_drv_send;
	usb_netif->drv_set_hwaddr = NULL;
	usb_netif->link_layer_type = ETHERNET_DRIVER_IF;
	usb_netif->hwaddr_len = NETIF_MAX_HWADDR_LEN;
#if PF_PKT_SUPPORT
	usb_netif->drv_config = eth_drv_config;
#endif
#if LWIP_NETIF_ETHTOOL
	usb_netif->ethtool_ops = NULL;
#endif
	if (enaddr != 0) {
		(void)memcpy_s(usb_netif->hwaddr, NETIF_MAX_HWADDR_LEN, enaddr, NETIF_MAX_HWADDR_LEN);
		(drv_sc->funs->start)(sc, NULL, 0);
	}
	ret = netifapi_netif_add(usb_netif, &ipaddr, &netmask, &gw);
	if (ret) {
		PRINT_ERR("Fatal Error, unable to add USB network interface! ret:%d\n", ret);
		return;
	}

	ret = netifapi_netif_set_default(usb_netif);
	if (ret) {
		PRINT_ERR("%s, %d, netif set default failed, ret:%d\n", __FUNCTION__, __LINE__, ret);
		return;
	}

	ret = netifapi_netif_set_up(usb_netif);
	if (ret) {
		PRINT_ERR("%s, %d, netif set up failed, ret:%d\n", __FUNCTION__, __LINE__, ret);
		return;
	}

	ret = netifapi_dhcp_start(usb_netif);
	if (ret) {
		PRINT_ERR("%s, %d, dhcp start failed, ret:%d\n", __FUNCTION__, __LINE__, ret);
		return;
	}
}

/*
 * This function is called from the hardware driver when an output operation
 * has completed - i.e. the packet has been sent.
 */
static void
eth_drv_tx_done(struct eth_drv_sc *sc, unsigned int key, int status)
{

}

/*
 * This function is called from a hardware driver to indicate that an input
 * packet has arrived.  The routine will set up appropriate network resources
 * to hold the data and call back into the driver to retrieve the data.
 */
static void
eth_drv_recv(struct los_eth_driver *sc, int total_len)
{
	struct eth_drv_sg sg_list[MAX_ETH_DRV_SG];
	struct netif *usb_netif = &sc->ac_if;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc*)sc->driver_context;
	struct pbuf *p, *q;
	int sg_len = 0;

	if ((total_len > MAX_ETH_MSG) || (total_len < 0)) {
		total_len = MAX_ETH_MSG;
	}

	p = pbuf_alloc(PBUF_RAW, (total_len + ETH_PAD_SIZE), PBUF_RAM);
	if (p == NULL) {
		PRINTK("eth_drv_recv : pbuf_alloc failed\n");
		return;
	}

#if ETH_PAD_SIZE
	(void)pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

	for (q = p; q != NULL; q = q->next) {
		sg_list[sg_len].buf = (UINTPTR)q->payload;
		sg_list[sg_len++].len = q->len;
	}

	(drv_sc->funs->recv)(sc, sg_list, sg_len);

#if ETH_PAD_SIZE
	(void)pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

	driverif_input(usb_netif,p);
}
static void
eth_drv_send(struct netif *usb_netif, struct pbuf *p)
{
	struct eth_drv_sg sg_list[MAX_ETH_DRV_SG];
	struct los_eth_driver *sc = (struct los_eth_driver *)usb_netif->state;
	struct eth_drv_sc *drv_sc = (struct eth_drv_sc*)sc->driver_context;
	int sg_len = 0;
	struct pbuf *q;

	while (!(drv_sc->funs->can_send)(sc));

	for (q = p; q != NULL; q = q->next) {
		sg_list[sg_len].buf = (UINTPTR)q->payload;
		sg_list[sg_len++].len = q->len;
	}

	(drv_sc->funs->send) (sc, sg_list, sg_len, p->tot_len, (UINTPTR)p);
}

const struct los_eth_funs eth_drv_funs_usb = {
	(void (*)(struct los_eth_driver *, unsigned char *))eth_drv_init,
	(void (*)(struct los_eth_driver *, int))eth_drv_recv,
	(void (*)(struct los_eth_driver *, unsigned int, int))eth_drv_tx_done
};

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
