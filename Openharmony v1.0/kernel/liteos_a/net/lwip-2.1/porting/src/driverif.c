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

#include <lwip/sys.h>
#include <lwip/netif.h>
#include <lwip/snmp.h>
#include <lwip/etharp.h>
#include <lwip/sockets.h>
#include <lwip/snmp.h>
#include <lwip/etharp.h>
#include <lwip/ethip6.h>

#define LWIP_NETIF_HOSTNAME_DEFAULT         "default"
#define LINK_SPEED_OF_YOUR_NETIF_IN_BPS     100000000 // 100Mbps

#define link_rx_drop cachehit
#define link_rx_overrun cachehit

#define NETIF_NAME_LEN 2
#define LWIP_STATIC static

#ifndef LWIP_NETIF_IFINDEX_MAX_EX
#define LWIP_NETIF_IFINDEX_MAX_EX 255
#endif

LWIP_STATIC void
driverif_init_ifname(struct netif *netif)
{
    struct netif *tmpnetif = NULL;
    const char *prefix = (netif->link_layer_type == WIFI_DRIVER_IF) ? "wlan" : "eth";

    for (int i = 0; i < LWIP_NETIF_IFINDEX_MAX_EX; ++i) {
        if (snprintf_s(netif->full_name, sizeof(netif->full_name), sizeof(netif->full_name) - 1,
                       "%s%d", prefix, i) < 0) {
            break;
        }
        NETIF_FOREACH(tmpnetif) {
            if (strcmp(tmpnetif->full_name, netif->full_name) == 0) {
                break;
            }
        }
        if (tmpnetif == NULL) {
            return;
        }
    }
    netif->full_name[0] = '\0';
}

/*
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this driverif
 * @param p the MAC packet to send (e.g. IP packet including MAC_addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

LWIP_STATIC err_t
driverif_output(struct netif *netif, struct pbuf *p)
{
    LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_output : going to send packet pbuf 0x%p of length %"U16_F" through netif 0x%p\n", \
    (void *)p, p->tot_len, (void *)netif));

#if PF_PKT_SUPPORT
    if (all_pkt_raw_pcbs != NULL) {
    p->flags = (u16_t)(p->flags & ~(PBUF_FLAG_LLMCAST | PBUF_FLAG_LLBCAST | PBUF_FLAG_HOST));
    p->flags |= PBUF_FLAG_OUTGOING;
    (void)raw_pkt_input(p, netif, NULL);
  }
#endif

#if ETH_PAD_SIZE
    (void)pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    netif->drv_send(netif, p);

#if ETH_PAD_SIZE
    (void)pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif
    MIB2_STATS_NETIF_ADD(netif, ifoutoctets, p->tot_len);
    LINK_STATS_INC(link.xmit);

    return ERR_OK;
}

/*
 * This function should be called by network driver to pass the input packet to LwIP.
 * Before calling this API, driver has to keep the packet in pbuf structure. Driver has to
 * call pbuf_alloc() with type as PBUF_RAM to create pbuf structure. Then driver
 * has to pass the pbuf structure to this API. This will add the pbuf into the TCPIP thread.
 * Once this packet is processed by TCPIP thread, pbuf will be freed. Driver is not required to
 * free the pbuf.
 *
 * @param netif the lwip network interface structure for this driverif
 * @param p packet in pbuf structure format
 */
void
driverif_input(struct netif *netif, struct pbuf *p)
{
#if PF_PKT_SUPPORT
#if  (DRIVERIF_DEBUG & LWIP_DBG_OFF)
    u16_t ethhdr_type;
    struct eth_hdr* ethhdr = NULL;
#endif
#else
    u16_t ethhdr_type;
    struct eth_hdr* ethhdr = NULL;
#endif
    err_t ret = ERR_VAL;

    LWIP_ERROR("driverif_input : invalid arguments", ((netif != NULL) && (p != NULL)), return);

    LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_input : going to receive input packet. netif 0x%p, pbuf 0x%p, \
                               packet_length %"U16_F"\n", (void *)netif, (void *)p, p->tot_len));

    /* points to packet payload, which starts with an Ethernet header */
    MIB2_STATS_NETIF_ADD(netif, ifinoctets, p->tot_len);
    if (p->len < SIZEOF_ETH_HDR) {
        (void)pbuf_free(p);
        LINK_STATS_INC(link.drop);
        LINK_STATS_INC(link.link_rx_drop);
        return;
    }

#if PF_PKT_SUPPORT
#if  (DRIVERIF_DEBUG & LWIP_DBG_OFF)
    ethhdr = (struct eth_hdr *)p->payload;
    ethhdr_type = ntohs(ethhdr->type);
    LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_input : received packet of type %"U16_F" netif->input=%p\n", ethhdr_type, netif->input));
#endif

    /* full packet send to tcpip_thread to process */
    if (netif->input) {
        ret = netif->input(p, netif);
    }
    if (ret != ERR_OK) {
        LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_input: IP input error\n"));
        (void)pbuf_free(p);
        LINK_STATS_INC(link.drop);
        LINK_STATS_INC(link.link_rx_drop);
        if (ret == ERR_MEM) {
            LINK_STATS_INC(link.link_rx_overrun);
        }
    } else {
        LINK_STATS_INC(link.recv);
    }

#else
    ethhdr = (struct eth_hdr *)p->payload;
    ethhdr_type = ntohs(ethhdr->type);

    switch (ethhdr_type) {
        /* IP or ARP packet? */
        case ETHTYPE_IP:
        case ETHTYPE_IPV6:
        case ETHTYPE_ARP:
#if ETHARP_SUPPORT_VLAN
        case ETHTYPE_VLAN:
#endif /* ETHARP_SUPPORT_VLAN */
            LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_input : received packet of type %"U16_F"\n", ethhdr_type));
            /* full packet send to tcpip_thread to process */
            if (netif->input != NULL) {
                ret = netif->input(p, netif);
            }

            if (ret != ERR_OK) {
                LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_input: IP input error\n"));
                (void)pbuf_free(p);
                LINK_STATS_INC(link.drop);
                LINK_STATS_INC(link.link_rx_drop);
                if (ret == ERR_MEM) {
                    MIB2_STATS_NETIF_INC(netif, ifinoverruns);
                    LINK_STATS_INC(link.link_rx_overrun);
                }
            } else {
                LINK_STATS_INC(link.recv);
            }
            break;

        default:
            LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_input : received packet is of unsupported type %"U16_F"\n", ethhdr_type));
            (void)pbuf_free(p);
            LINK_STATS_INC(link.drop);
            LINK_STATS_INC(link.link_rx_drop);
            break;
    }
#endif

    LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_input : received packet is processed\n"));
}

/*
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this driverif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM on Allocation Failure
 *         any other err_t on error
 */
err_t
driverif_init(struct netif *netif)
{
    u16_t link_layer_type;
    err_t ret;

    if (netif == NULL) {
        return ERR_IF;
    }
    link_layer_type = netif->link_layer_type;
    LWIP_ERROR("driverif_init : invalid link_layer_type in netif", \
    ((link_layer_type == ETHERNET_DRIVER_IF) || (link_layer_type == WIFI_DRIVER_IF)), \
    return ERR_IF);

    LWIP_ERROR("driverif_init : netif hardware length is greater than maximum supported", \
    (netif->hwaddr_len <= NETIF_MAX_HWADDR_LEN), return ERR_IF);

    LWIP_ERROR("driverif_init : drv_send is null", (netif->drv_send != NULL), return ERR_IF);

#if LWIP_NETIF_PROMISC
    LWIP_ERROR("driverif_init : drv_config is null", (netif->drv_config != NULL), return ERR_IF);
#endif

#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
#if LOSCFG_NET_LWIP_SACK_2_0
    if (strncpy_s(netif->hostname, NETIF_HOSTNAME_MAX_LEN,
                  LWIP_NETIF_HOSTNAME_DEFAULT, NETIF_HOSTNAME_MAX_LEN - 1) == EOK) {
        netif->hostname[NETIF_HOSTNAME_MAX_LEN - 1] = '\0';
    } else {
        LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_init: hostname %s in invalid\n", LWIP_NETIF_HOSTNAME_DEFAULT));
        netif->hostname[0] = '\0';
    }
#else
    netif->hostname = LWIP_NETIF_HOSTNAME_DEFAULT;
#endif
#endif /* LWIP_NETIF_HOSTNAME */

    /*
     * Initialize the snmp variables and counters inside the struct netif.
     * The last argument should be replaced with your link speed, in units
     * of bits per second.
     */
    NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

    netif->output = etharp_output;
    netif->linkoutput = driverif_output;

    if (link_layer_type == ETHERNET_DRIVER_IF) {
        ret = memcpy_s(netif->name, sizeof(netif->name), "et", NETIF_NAME_LEN);
    } else {
        ret = memcpy_s(netif->name, sizeof(netif->name), "wl", NETIF_NAME_LEN);
    }
    if (ret != EOK) {
#if LWIP_NETIF_HOSTNAME
#if LOSCFG_NET_LWIP_SACK_2_0
        netif->hostname[0] = '\0';
#else
        netif->hostname = NULL;
#endif
#endif
        return ERR_IF;
    }
    /* init the netif's full name */
    driverif_init_ifname(netif);

    /* maximum transfer unit */
    netif->mtu = IP_FRAG_MAX_MTU;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP |
#if DRIVER_STATUS_CHECK
            NETIF_FLAG_DRIVER_RDY |
#endif
#if LWIP_IGMP
            NETIF_FLAG_IGMP |
#endif

/**
@page RFC-2710 RFC-2710
@par Compliant Sections
Section 5. Node State Transition Diagram
@par Behavior Description
MLD messages are sent for multicast addresses whose scope is 2
(link-local), including Solicited-Node multicast addresses.\n
Behavior:Stack will send MLD6 report /Done to solicited node multicast address
if the LWIP_MLD6_ENABLE_MLD_ON_DAD is enabled. By default, this is disabled.
*/
/* Enable sending MLD report /done for solicited address during neighbour discovery */
#if LWIP_IPV6 && LWIP_IPV6_MLD
#if LWIP_MLD6_ENABLE_MLD_ON_DAD
            NETIF_FLAG_MLD6 |
#endif /* LWIP_MLD6_ENABLE_MLD_ON_DAD */
#endif
            NETIF_FLAG_LINK_UP;

#if DRIVER_STATUS_CHECK
    netif->waketime = -1;
#endif /* DRIVER_STATUS_CHECK */
    LWIP_DEBUGF(DRIVERIF_DEBUG, ("driverif_init : Initialized netif 0x%p\n", (void *)netif));
    return ERR_OK;
}
