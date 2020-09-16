/*
 * Copyright (c) 2001-2004 Leon Woestenberg <leon.woestenberg@gmx.net>
 * Copyright (c) 2001-2004 Axon Digital Design B.V., The Netherlands.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * The Swedish Institute of Computer Science and Adam Dunkels
 * are specifically granted permission to redistribute this
 * source code.
 *
 * Author: Leon Woestenberg <leon.woestenberg@gmx.net>
 *
 */

/**
 * @file
 * Dynamic Host Configuration Protocol Server
 *
 */

#include "dhcps.h"
#include "dhcps_fix.h"

#if (LWIP_DHCP) && (LWIP_DHCPS) /* don't build if not configured for use in lwipopts.h */
#include <string.h>

#include "lwip/stats.h"
#include "lwip/mem.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/def.h"
#include "lwip/prot/dhcp.h"
#include "lwip/dhcp.h"
#include "lwip/sys.h"
#include "netif/etharp.h"

#include "securec.h"

#define DHCPS_ADDRESS_FREE 0x0
#define DHCPS_ADDRESS_OFFERRED 0x1
#define DHCPS_ADDRESS_BOUND 0x2
#define DHCPS_ADDRESS_DECLINED 0x3

u32_t dhcps_rx_options_val[DHCP_OPTION_IDX_MAX];
u8_t  dhcps_rx_options_given[DHCP_OPTION_IDX_MAX];

#define dhcps_option_given(dhcp, idx)          (dhcps_rx_options_given[idx] != 0)
#define dhcps_got_option(dhcp, idx)            (dhcps_rx_options_given[idx] = 1)
#define dhcps_clear_option(dhcp, idx)          (dhcps_rx_options_given[idx] = 0)
#define dhcps_get_option_value(dhcp, idx)      (dhcps_rx_options_val[idx])
#define dhcps_set_option_value(dhcp, idx, val) (dhcps_rx_options_val[idx] = (val))

LWIP_STATIC struct pbuf *dhcps_create_base_msg(struct dhcp_msg *client_msg);
LWIP_STATIC void remove_stale_entries(struct dhcps *dhcps);
LWIP_STATIC void add_client_entry(struct dhcps *dhcps, unsigned int idx, struct dhcp_msg *client_msg);
LWIP_STATIC int find_free_slot(struct dhcps *dhcps);
LWIP_STATIC struct dyn_lease_addr *find_client_lease(struct dhcps *dhcps, struct dhcp_msg *client_msg);
LWIP_STATIC ip4_addr_t validate_discover(struct dhcps *dhcps, struct dhcp_msg *client_msg,
                                         struct dyn_lease_addr **client_lease);
LWIP_STATIC void handle_discover(struct netif *netif, struct dhcps *dhcps, struct dhcp_msg *client_msg,
                                 struct dyn_lease_addr *client_lease);
LWIP_STATIC ip4_addr_t validate_request_message(struct netif *netif, struct dhcp_msg *client_msg,
                                                struct dyn_lease_addr *client_lease, ip4_addr_t serverid);
LWIP_STATIC void handle_request(struct netif *netif, struct dhcps *dhcps, struct dhcp_msg *client_msg,
                                struct dyn_lease_addr *client_lease, ip4_addr_t serverid);
LWIP_STATIC void handle_decline(struct dhcp_msg *client_msg, struct dyn_lease_addr *client_lease);
LWIP_STATIC void handle_inform(struct netif *netif, struct dhcps *dhcps, struct dhcp_msg *client_msg);
LWIP_STATIC void handle_client_messages(struct netif *netif, struct dhcps *dhcps,
                                        struct dhcp_msg *client_msg, ip4_addr_t serverid, u8_t msg_type);
LWIP_STATIC void dhcps_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                            const ip_addr_t *ip_addr, u16_t port);

LWIP_STATIC struct pbuf *dhcps_create_base_msg(struct dhcp_msg *client_msg)
{
  struct pbuf *srvr_msg_pbuf = NULL;
  struct dhcp_msg *srvr_msg = NULL;

  srvr_msg_pbuf = pbuf_alloc(PBUF_TRANSPORT, sizeof(struct dhcp_msg), PBUF_RAM);
  if (srvr_msg_pbuf == NULL) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS,
                ("dhcps_create_base_msg(): could not allocate pbuf\n"));
    return NULL;
  }

  LWIP_ASSERT("dhcps_create_base_msg: check that first pbuf can hold struct dhcp_msg",
              (srvr_msg_pbuf->len >= sizeof(struct dhcp_msg)));
#if DRIVER_STATUS_CHECK
  srvr_msg_pbuf->flags |= PBUF_FLAG_DHCP_BUF;
#endif

  srvr_msg = (struct dhcp_msg *)srvr_msg_pbuf->payload;
  srvr_msg->op = DHCP_BOOTREPLY;
  srvr_msg->htype = client_msg->htype;
  srvr_msg->hlen = client_msg->hlen;
  srvr_msg->hops = 0;
  srvr_msg->xid = client_msg->xid;
  srvr_msg->secs = 0;
  srvr_msg->flags = client_msg->flags;
  ip4_addr_set_zero(&srvr_msg->ciaddr);
  ip4_addr_set_zero(&srvr_msg->yiaddr);
  ip4_addr_set_zero(&srvr_msg->siaddr);
  ip4_addr_copy(srvr_msg->giaddr, client_msg->giaddr);
  if (memcpy_s(srvr_msg->chaddr, sizeof(srvr_msg->chaddr), client_msg->chaddr, DHCP_CHADDR_LEN) != EOK) {
    (void)pbuf_free(srvr_msg_pbuf);
    return NULL;
  }
  (void)memset_s(srvr_msg->sname, sizeof(srvr_msg->sname), 0, DHCP_SNAME_LEN);
  (void)memset_s(srvr_msg->file, sizeof(srvr_msg->file), 0, DHCP_FILE_LEN);
  srvr_msg->cookie = PP_HTONL(DHCP_MAGIC_COOKIE);

  return srvr_msg_pbuf;
}

LWIP_STATIC void remove_stale_entries(struct dhcps *dhcps)
{
  int i = 0;
  u32_t curr_time = sys_now();

  for (i = 0; i < dhcps->lease_num; i++) {
    /* Slot should not be free or have infinite lease time */
    if ((dhcps->leasearr[i].flags != DHCPS_ADDRESS_FREE) && (dhcps->leasearr[i].leasetime != (u32_t)~0)) {
      if (dhcps->leasearr[i].leasetime < curr_time) {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                    ("remove_stale_entries: Removing Client Entry at Index = %"U32_F"\n", i));
        (void)memset_s(&(dhcps->leasearr[i]), sizeof(struct dyn_lease_addr), 0, sizeof(struct dyn_lease_addr));
        dhcps->leasearr[i].flags = DHCPS_ADDRESS_FREE;
      }
    }
  }
}

LWIP_STATIC void add_client_entry(struct dhcps *dhcps, unsigned int idx, struct dhcp_msg *client_msg)
{
  u32_t client_lease_time = (u32_t)(LWIP_DHCPS_LEASE_TIME);

  if ((dhcps_option_given(NULL, DHCP_OPTION_IDX_LEASE_TIME))
#if (LWIP_DHCPS_LEASE_TIME != ~0)
    && (dhcps_get_option_value(NULL, DHCP_OPTION_IDX_LEASE_TIME) < LWIP_DHCPS_LEASE_TIME)
#endif
    ) {
    client_lease_time = (u32_t)dhcps_get_option_value(NULL, DHCP_OPTION_IDX_LEASE_TIME);
  }

  (void)memset_s(&(dhcps->leasearr[idx]), sizeof(struct dyn_lease_addr), 0, sizeof(struct dyn_lease_addr));
  if (memcpy_s(dhcps->leasearr[idx].cli_hwaddr, DHCP_CHADDR_LEN,
               client_msg->chaddr, sizeof(client_msg->chaddr)) != EOK) {
    return;
  }
  /* This is called only during offer message, so adding offer time.
    This is later updated to lease time when request message is handled */
  dhcps->leasearr[idx].leasetime = sys_now() + (LWIP_DHCPS_OFFER_TIME * 1000);
  dhcps->leasearr[idx].cli_addr.addr = dhcps->start_addr.addr + idx;
  dhcps->leasearr[idx].flags = DHCPS_ADDRESS_OFFERRED;
  dhcps->leasearr[idx].proposed_leasetime = client_lease_time;
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("add_client_entry: Adding Client Entry at Index = %"U32_F"\n", idx));
}

LWIP_STATIC int find_free_slot(struct dhcps *dhcps)
{
  int i;
  for (i = 0; i < dhcps->lease_num; i++) {
    if ((dhcps->leasearr[i].flags == DHCPS_ADDRESS_FREE) &&
      (htonl(dhcps->start_addr.addr + (u32_t)i) != ip_2_ip4(&dhcps->netif->ip_addr)->addr)) {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("find_free_slot: Found Free Slot at Index = %"U32_F"\n", i));
      return i;
    }
  }

  return -1;
}

LWIP_STATIC struct dyn_lease_addr *find_client_lease(struct dhcps *dhcps, struct dhcp_msg *client_msg)
{
  int i;
  for (i = 0; i < dhcps->lease_num; i++) {
    if (dhcps->leasearr[i].flags != DHCPS_ADDRESS_FREE) {
      if (memcmp(dhcps->leasearr[i].cli_hwaddr, client_msg->chaddr, client_msg->hlen) == 0) {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("find_client_lease: Found Client Lease at Index = %"U32_F"\n", i));
        return &(dhcps->leasearr[i]);
      }
    }
  }

  return NULL;
}

LWIP_STATIC ip4_addr_t validate_discover(struct dhcps *dhcps, struct dhcp_msg *client_msg,
                                         struct dyn_lease_addr **client_lease)
{
  ip4_addr_t client_ip;
  int idx = -1;

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("validate_discover: Validating Discover Message\n"));

  client_ip.addr = 0;
  if (*client_lease == NULL) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("validate_discover: Existing Client Lease not Found\n"));
    if (dhcps_option_given(dhcps, DHCP_OPTION_IDX_REQUESTED_IP)) {
      client_ip.addr = (u32_t)dhcps_get_option_value(dhcps, DHCP_OPTION_IDX_REQUESTED_IP);
#ifdef  LWIP_DEV_DEBUG
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                  ("validate_discover function: Requested IP from client = %"U32_F"\n", client_ip.addr));
#endif

      if ((client_ip.addr >= dhcps->start_addr.addr) && (client_ip.addr <= dhcps->end_addr.addr)) {
        idx = (int)(client_ip.addr - dhcps->start_addr.addr);
        if ((dhcps->leasearr[idx].flags != DHCPS_ADDRESS_FREE) ||
            (ntohl(client_ip.addr) == ip_2_ip4(&dhcps->netif->ip_addr)->addr)) {
          /* Requested IP is not available */
#ifdef  LWIP_DEV_DEBUG
          LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
            ("validate_discover function: Requested IP from client = %"U32_F" Not available \n", client_ip.addr));
#endif
          idx = -1;
        }
      }
    }

    if (idx == -1) {
      idx = find_free_slot(dhcps);
      if (idx == -1) {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                    ("validate_discover function: No Free Slot available for Storing addresses\n"));
        client_ip.addr = 0;
        return client_ip;
      }
      client_ip.addr =  dhcps->start_addr.addr + (u32_t)idx;
#ifdef  LWIP_DEV_DEBUG
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                  ("validate_discover function: New IP = %"U32_F" is being assigned\n", client_ip.addr));
#endif
    }

    add_client_entry(dhcps, (unsigned int)idx, client_msg);
    (*client_lease) = &(dhcps->leasearr[idx]);
  } else {
    client_ip.addr = (*client_lease)->cli_addr.addr;
#ifdef  LWIP_DEV_DEBUG
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("validate_discover: Existing Client Lease Found. Existing IP =%"U32_F"\n", client_ip.addr));
#endif

    if ((dhcps_option_given(NULL, DHCP_OPTION_IDX_LEASE_TIME))
#if (~0 != LWIP_DHCPS_LEASE_TIME)
      && (dhcps_get_option_value(NULL, DHCP_OPTION_IDX_LEASE_TIME) < LWIP_DHCPS_LEASE_TIME)
#endif
      ) {
      /* Assign the newly requested time or else use the existing lease time as-is */
      (*client_lease)->proposed_leasetime = (u32_t)dhcps_get_option_value(NULL, DHCP_OPTION_IDX_LEASE_TIME);
    }
  }

  return client_ip;
}

void dhcp_common_option(struct dhcp_msg *msg_out, u8_t option_type, u8_t option_len, u16_t *options_out_len)
{
  LWIP_ERROR("dhcps_option: options_out_len + 2 + option_len <= DHCP_OPTIONS_LEN",
             (*options_out_len) + 2U + option_len <= DHCP_OPTIONS_LEN, return);
  msg_out->options[(*options_out_len)++] = option_type;
  msg_out->options[(*options_out_len)++] = option_len;
}
/*
 * Concatenate a single byte to the outgoing DHCP message.
 *
 */
void dhcp_common_option_byte(struct dhcp_msg *msg_out, u8_t value, u16_t *options_out_len)
{
  LWIP_ERROR("dhcps_option_byte: options_out_len < DHCP_OPTIONS_LEN",
             (*options_out_len) < DHCP_OPTIONS_LEN, return);
  msg_out->options[(*options_out_len)++] = value;
}

void dhcp_common_option_short(struct dhcp_msg *msg_out, u16_t value, u16_t *options_out_len)
{
  LWIP_ERROR("dhcps_option_short: options_out_len + 2 <= DHCP_OPTIONS_LEN",
             (*options_out_len) + 2U <= DHCP_OPTIONS_LEN, return);
  msg_out->options[(*options_out_len)++] = (u8_t)((value & 0xff00U) >> 8);
  msg_out->options[(*options_out_len)++] = (u8_t) (value & 0x00ffU);
}

void dhcp_common_option_long(struct dhcp_msg *msg_out, u32_t value, u16_t *options_out_len)
{
  LWIP_ERROR("dhcp_option_long: options_out_len + 4 <= DHCP_OPTIONS_LEN",
             (*options_out_len) + 4U <= DHCP_OPTIONS_LEN, return);
  msg_out->options[(*options_out_len)++] = (u8_t)((value & 0xff000000UL) >> 24);
  msg_out->options[(*options_out_len)++] = (u8_t)((value & 0x00ff0000UL) >> 16);
  msg_out->options[(*options_out_len)++] = (u8_t)((value & 0x0000ff00UL) >> 8);
  msg_out->options[(*options_out_len)++] = (u8_t)((value & 0x000000ffUL));
}

void dhcp_common_option_trailer(struct dhcp_msg *msg_out, u16_t *options_out_len)
{
  LWIP_ERROR("dhcp_common_option_trailer: options_out_len < DHCP_OPTIONS_LEN",
             (*options_out_len) < DHCP_OPTIONS_LEN, return);
  msg_out->options[(*options_out_len)++] = DHCP_OPTION_END;
  /* packet is too small, or not 4 byte aligned? */
  while ((((*options_out_len) < DHCP_MIN_OPTIONS_LEN) || ((*options_out_len) & 3)) &&
         ((*options_out_len) < DHCP_OPTIONS_LEN)) {
    /* add a fill/padding byte */
    msg_out->options[(*options_out_len)++] = 0;
  }
}

LWIP_STATIC void handle_discover(struct netif* netif, struct dhcps *dhcps,
                                 struct dhcp_msg *client_msg, struct dyn_lease_addr *client_lease)
{
#if !LWIP_DHCPS_DISCOVER_BROADCAST
  ip_addr_t client_ipaddr;
#endif

  ip4_addr_t client_ip;
  ip_addr_t dst_addr;
  struct pbuf *out_msg = NULL;
  struct dhcp_msg *srvr_msg = NULL;
  u16_t options_len = 0;
#if !LWIP_DHCPS_DISCOVER_BROADCAST
#if ETHARP_SUPPORT_STATIC_ENTRIES
  struct eth_addr ethaddr;
#endif
#endif
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_discover: Processing Discover Message\n"));

  client_ip = validate_discover(dhcps, client_msg, &client_lease);
  if (client_ip.addr == 0) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_discover: Returning as unable to get a proper address for client\n"));
    return;
  }

  out_msg = dhcps_create_base_msg(client_msg);
  if (out_msg == NULL) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_discover function: Memory allocation for base message failed\n"));
    return;
  }

  srvr_msg = (struct dhcp_msg *)out_msg->payload;
  // no need check msg pointer from payload here
  srvr_msg->yiaddr.addr = htonl(client_ip.addr);

  dhcp_common_option(srvr_msg, DHCP_OPTION_MESSAGE_TYPE, DHCP_OPTION_MESSAGE_TYPE_LEN, &options_len);
  dhcp_common_option_byte(srvr_msg, DHCP_OFFER, &options_len);

  /* hilink need this router option */
  dhcp_common_option(srvr_msg, DHCP_OPTION_ROUTER, DHCP_OPTION_ROUTER_SIZE, &options_len);
  dhcp_common_option_long(srvr_msg, ntohl(ip_2_ip4(&netif->ip_addr)->addr), &options_len);

  /* netif already holds the Server ID in network order. so, no need to convert it again */
  dhcp_common_option(srvr_msg, DHCP_OPTION_SERVER_ID, DHCP_OPTION_SERVER_ID_LEN, &options_len);
  dhcp_common_option_long(srvr_msg, ntohl(ip_2_ip4(&netif->ip_addr)->addr), &options_len);

  dhcp_common_option(srvr_msg, DHCP_OPTION_LEASE_TIME, DHCP_OPTION_LEASE_TIME_SIZE, &options_len);
  dhcp_common_option_long(srvr_msg, client_lease->proposed_leasetime, &options_len);

  dhcp_common_option(srvr_msg, DHCP_OPTION_T1, DHCP_OPTION_T1_LEN, &options_len);
  dhcp_common_option_long(srvr_msg, (client_lease->proposed_leasetime / 2), &options_len);

  dhcp_common_option(srvr_msg, DHCP_OPTION_T2, DHCP_OPTION_T2_LEN, &options_len);
  /* calculate safe periods for lease (proposed_leasetime * 0.875 -> 87.5%) */
  dhcp_common_option_long(srvr_msg, ((client_lease->proposed_leasetime * 7) / 8), &options_len);

  /* No need to convert netmask into network order as it is already stored in network order */
  dhcp_common_option(srvr_msg, DHCP_OPTION_SUBNET_MASK, DHCP_OPTION_SUBNET_MASK_SIZE, &options_len);
  dhcp_common_option_long(srvr_msg, ntohl(ip4_addr_get_u32(ip_2_ip4(&netif->netmask))), &options_len);

  dhcp_common_option_trailer(srvr_msg, &options_len);

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_discover: realloc()ing\n"));
  pbuf_realloc(out_msg, (u16_t)((sizeof(struct dhcp_msg) - DHCP_OPTIONS_LEN) + options_len));

  if (client_msg->ciaddr.addr != 0) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_discover: sendto(OFFER, ciaddr, DHCP_CLIENT_PORT)\n"));
    ip_addr_set_ip4_u32_val(dst_addr, (u32_t)(client_msg->ciaddr.addr));
    (void)udp_sendto_if_src(dhcps->pcb, out_msg, &dst_addr, DHCP_CLIENT_PORT, netif, &(netif->ip_addr));
  }
#if !LWIP_DHCPS_DISCOVER_BROADCAST
  else if (ntohs(client_msg->flags) & DHCP_BROADCAST_FLAG) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_discover: sendto(OFFER, IP_ADDR_BROADCAST, DHCP_CLIENT_PORT)\n"));
    (void)udp_sendto_if_src(dhcps->pcb, out_msg, IP_ADDR_BROADCAST, DHCP_CLIENT_PORT, netif, &(netif->ip_addr));
  } else {
    client_ip.addr = htonl(client_ip.addr);

#if ETHARP_SUPPORT_STATIC_ENTRIES
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_discover: Updating ARP Static Entry for unicast reply\n"));
    if (memcpy_s(ethaddr.addr, ETHARP_HWADDR_LEN, client_msg->chaddr, client_msg->hlen) != EOK) {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("memcpy_s failed\n"));
      (void)pbuf_free(out_msg);
      return;
    }
    if (etharp_add_static_entry(&client_ip, &ethaddr) != ERR_OK) {
      (void)pbuf_free(out_msg);
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_discover: Adding static entry to arp cache failed\n"));
      return;
    }
#endif

    /* Need to check and add an arp entry to make this pass through smoothly */
    ip_addr_copy_from_ip4(client_ipaddr, client_ip);
    (void)udp_sendto_if_src(dhcps->pcb, out_msg, &client_ipaddr, DHCP_CLIENT_PORT, netif, &(netif->ip_addr));
#if ETHARP_SUPPORT_STATIC_ENTRIES
    /* We just added the entry above and checked for it's success too. so, the below function call cannot fail */
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_discover: Removing ARP Static Entry added for unicast reply\n"));
    (void)etharp_remove_static_entry(&client_ip);
#endif
  }
#else
  else {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_discover: sendto(OFFER, IP_ADDR_BROADCAST, DHCP_CLIENT_PORT)\n"));
    (void)udp_sendto_if_src(dhcps->pcb, out_msg, IP_ADDR_BROADCAST, DHCP_CLIENT_PORT, netif, &(netif->ip_addr));
  }
#endif

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_discover: deleting()ing\n"));
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_discover: Sending Reply has been successful\n"));

  (void)pbuf_free(out_msg);
  return;
}

LWIP_STATIC ip4_addr_t validate_request_message(struct netif* netif, struct dhcp_msg *client_msg,
                                                struct dyn_lease_addr *client_lease, ip4_addr_t serverid)
{
  ip4_addr_t requested_ip;
  requested_ip.addr = 0;

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("validate_request_message: Processing Request Message\n"));

  if ((client_lease != NULL) && (client_lease->flags == DHCPS_ADDRESS_OFFERRED)) {
    /* Now, we are in selecting state */
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("validate_request_message: In Selecting State\n"));

    if ((serverid.addr == 0) || (client_msg->ciaddr.addr != 0) ||
        (!dhcps_option_given(dhcps, DHCP_OPTION_IDX_REQUESTED_IP))) {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                  ("Server ID or ciaddr or requested ip option is not present\n"));
      return requested_ip;
    }

    if (serverid.addr != ip_2_ip4(&netif->ip_addr)->addr) {
      /* This message is not meant for us. The client intends to talk to some other server */
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                  ("validate_request_message: Server id doesn't match with ours. Message not for us\n"));
      requested_ip.addr = 1;
      return requested_ip;
    }

    requested_ip.addr = (u32_t)dhcps_get_option_value(dhcps, DHCP_OPTION_IDX_REQUESTED_IP);
  } else {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("validate_request_message: In Init-Reboot, Renew or Rebinding State\n"));

    /* Now, we can be either in Init-reboot state or renew state or rebinding state */
    if (dhcps_option_given(dhcps, DHCP_OPTION_IDX_REQUESTED_IP)) {
      /* Requested IP option is filled in. Indicates we are mostly in Init-Reboot State */
      if (client_lease == NULL) {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                  ("validate_request_message: No Configuration found corresponding to request message\n"));
        requested_ip.addr = 1;
        return requested_ip;
      }

      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                  ("validate_request_message: Requested IP Option is present. So, considering as Init-Reboot State\n"));

      if (client_msg->ciaddr.addr != 0) {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                    ("validate_request_message: Error: ciaddr is filled in the Init-Reboot state. \n"));
        return requested_ip;
      }

      requested_ip.addr = (u32_t)dhcps_get_option_value(dhcps, DHCP_OPTION_IDX_REQUESTED_IP);
    } else {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("validate_request_message: \
                  Requested IP Option is not present. So, considering as Renewing or Rebinding State\n"));

      if (client_msg->ciaddr.addr == 0) {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                    ("validate_request_message: Error: ciaddr is not filled in the Renewing or Rebinding state. \n"));
        return requested_ip;
      }

      requested_ip.addr = ntohl(client_msg->ciaddr.addr);
    }
  }

  /* requested_ip is in host order and DHCP Server IP is in network order,
    so converting the former to network order for check */
  if (htonl(requested_ip.addr) == ip_2_ip4(&netif->ip_addr)->addr) {
    /* This requested_ip is the dhcp server is using, it is invalid */
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("validate_request_message: Requested IP addr is invalid\n"));
    requested_ip.addr = 1;
  }

  return requested_ip;
}

LWIP_STATIC void handle_request(struct netif *netif, struct dhcps *dhcps,  struct dhcp_msg *client_msg,
                                struct dyn_lease_addr *client_lease, ip4_addr_t serverid)
{
  ip4_addr_t requested_ip;
  struct pbuf *out_msg = NULL;
  struct dhcp_msg *srvr_msg = NULL;
  u16_t options_len = 0;
  ip_addr_t dst_addr;
  ip_addr_t ip_send;
#if ETHARP_SUPPORT_STATIC_ENTRIES
  struct eth_addr ethaddr;
#endif

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: Processing Request Message\n"));

  requested_ip = validate_request_message(netif, client_msg, client_lease, serverid);
  if (requested_ip.addr == 1) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_request: Validation of request message failed. Dropping the packet.\n"));
    return;
  }

  out_msg = dhcps_create_base_msg(client_msg);
  if (out_msg == NULL) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: Creating base message failed\n"));
    return;
  }

  srvr_msg = (struct dhcp_msg *)out_msg->payload;
  dhcp_common_option(srvr_msg, DHCP_OPTION_SERVER_ID, DHCP_OPTION_SERVER_ID_LEN, &options_len);
  dhcp_common_option_long(srvr_msg, ntohl(ip_2_ip4(&netif->ip_addr)->addr), &options_len);

  /* hilink need this router option */
  dhcp_common_option(srvr_msg, DHCP_OPTION_ROUTER, DHCP_OPTION_ROUTER_SIZE, &options_len);
  dhcp_common_option_long(srvr_msg, ntohl(ip_2_ip4(&netif->ip_addr)->addr), &options_len);

  if ((client_lease != NULL) && (client_lease->cli_addr.addr == requested_ip.addr)) {
    if (client_lease->proposed_leasetime != (u32_t)(~0)) {
      if (client_lease->flags == DHCPS_ADDRESS_OFFERRED) {
        client_lease->leasetime = sys_now() + (client_lease->proposed_leasetime * 1000);
      } else {
        client_lease->leasetime += (client_lease->proposed_leasetime * 1000);
      }
    } else {
      client_lease->leasetime = client_lease->proposed_leasetime;
    }

    client_lease->flags = DHCPS_ADDRESS_BOUND;
    srvr_msg->yiaddr.addr = htonl(client_lease->cli_addr.addr);

    dhcp_common_option(srvr_msg, DHCP_OPTION_MESSAGE_TYPE, DHCP_OPTION_MESSAGE_TYPE_LEN, &options_len);
    dhcp_common_option_byte(srvr_msg, DHCP_ACK, &options_len);

    dhcp_common_option(srvr_msg, DHCP_OPTION_LEASE_TIME, DHCP_OPTION_LEASE_TIME_SIZE, &options_len);
    dhcp_common_option_long(srvr_msg, client_lease->proposed_leasetime, &options_len);

    dhcp_common_option(srvr_msg, DHCP_OPTION_T1, DHCP_OPTION_T1_LEN, &options_len);
    dhcp_common_option_long(srvr_msg, (client_lease->proposed_leasetime / 2), &options_len);

    dhcp_common_option(srvr_msg, DHCP_OPTION_T2, DHCP_OPTION_T2_LEN, &options_len);
    /* calculate safe periods for lease (proposed_leasetime * 0.875 -> 87.5%) */
    dhcp_common_option_long(srvr_msg, ((client_lease->proposed_leasetime * 7) / 8), &options_len);

    dhcp_common_option(srvr_msg, DHCP_OPTION_SUBNET_MASK, DHCP_OPTION_SUBNET_MASK_SIZE, &options_len);
    dhcp_common_option_long(srvr_msg, ntohl(ip_2_ip4(&netif->netmask)->addr), &options_len);

#ifdef  LWIP_DEV_DEBUG
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_request: Send ACK. to=%"U32_F" lease time=%"U32_F"\n",
                requested_ip.addr, client_lease->proposed_leasetime));
#endif
  } else {
    dhcp_common_option(srvr_msg, DHCP_OPTION_MESSAGE_TYPE, DHCP_OPTION_MESSAGE_TYPE_LEN, &options_len);
    dhcp_common_option_byte(srvr_msg, DHCP_NAK, &options_len);

    /* Just set this here, so that the NAK message is brcasted.
    The correct flags has already been added in the respose message during base message creation */
    client_msg->flags |= htons(DHCP_BROADCAST_FLAG);
    client_msg->ciaddr.addr = 0; /* This is done so that NAK Gets brcasted */
#ifdef  LWIP_DEV_DEBUG
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_request: Send NAK. Requested from=%"U32_F"\n", requested_ip.addr));
#endif
  }

  requested_ip.addr = htonl(requested_ip.addr);
  dhcp_common_option_trailer(srvr_msg, &options_len);

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: realloc()ing\n"));
  pbuf_realloc(out_msg, (u16_t)((sizeof(struct dhcp_msg) - DHCP_OPTIONS_LEN) + options_len));
  if (client_msg->ciaddr.addr != 0) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: sendto(ACK, ciaddr, DHCP_CLIENT_PORT)\n"));
    ip_addr_set_ip4_u32_val(dst_addr, (u32_t)(client_msg->ciaddr.addr));
    (void)udp_sendto_if_src(dhcps->pcb, out_msg, &dst_addr, DHCP_CLIENT_PORT, netif, &(netif->ip_addr));
  } else if (ntohs(client_msg->flags) & DHCP_BROADCAST_FLAG) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: sending reply using brdcast \n"));
    (void)udp_sendto_if_src(dhcps->pcb, out_msg, IP_ADDR_BROADCAST, DHCP_CLIENT_PORT, netif, &(netif->ip_addr));
  } else {
#if ETHARP_SUPPORT_STATIC_ENTRIES
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: Updating ARP Static Entry for unicast reply\n"));
    if (memcpy_s(ethaddr.addr, ETHARP_HWADDR_LEN, client_msg->chaddr, client_msg->hlen) != EOK) {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: Copy chaddr failed\n"));
      (void)pbuf_free(out_msg);
      return;
    }
    if (ERR_OK != etharp_add_static_entry(&requested_ip, &ethaddr)) {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: Adding static entry to arp cache failed\n"));
      (void)pbuf_free(out_msg);
      return;
    }
#endif
    /* Need to check and add an arp entry to make this pass through smoothly */
#ifdef  LWIP_DEV_DEBUG
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_request: sending reply using unicast Client IP =%"U32_F"\n", requested_ip.addr));
#endif
    ip_send.u_addr.ip4.addr = requested_ip.addr;
    ip_send.type = IPADDR_TYPE_V4;
    (void)udp_sendto_if_src(dhcps->pcb, out_msg, &ip_send, DHCP_CLIENT_PORT, netif, &(netif->ip_addr));

#if ETHARP_SUPPORT_STATIC_ENTRIES
    /* We just added the entry above and checked for it's success too. so, the below function call cannot fail */
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("handle_request: Removing ARP Static Entry added for unicast reply\n"));
    (void)etharp_remove_static_entry(&requested_ip);
#endif
  }
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_request: deleting\n"));

  (void)pbuf_free(out_msg);
  return;
}

LWIP_STATIC void handle_decline(struct dhcp_msg *client_msg, struct dyn_lease_addr *client_lease)
{
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_decline: Processing Decline Message\n"));

  if ((client_lease != NULL) && (dhcps_option_given(dhcps, DHCP_OPTION_IDX_REQUESTED_IP)) &&
      (client_msg->ciaddr.addr == 0)) {
    if (client_lease->cli_addr.addr == (u32_t)dhcps_get_option_value(dhcps, DHCP_OPTION_IDX_REQUESTED_IP)) {
#ifdef  LWIP_DEV_DEBUG
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                  ("handle_decline: Marking Client Entry as declined. Client IP =%"U32_F"\n",
                  client_lease->cli_addr.addr));
#endif
      (void)memset_s(client_lease->cli_hwaddr, sizeof(client_lease->cli_hwaddr), 0, DHCP_CHADDR_LEN);
      client_lease->proposed_leasetime = 0;
      client_lease->leasetime = sys_now() + (LWIP_DHCPS_DECLINE_TIME * 1000);
      client_lease->flags = DHCPS_ADDRESS_DECLINED;
    }
  }
}

LWIP_STATIC void handle_inform(struct netif* netif, struct dhcps *dhcps, struct dhcp_msg *client_msg)
{
  struct pbuf *out_msg = NULL;
  struct dhcp_msg *srvr_msg = NULL;
  u16_t options_len = 0;
  ip_addr_t dst_addr;

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_inform: Processing Inform Message\n"));

  if (client_msg->ciaddr.addr == 0) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_inform: ciaddr is empty. Can't send back a response\n"));
    return;
  }

  out_msg = dhcps_create_base_msg(client_msg);
  if (out_msg == NULL) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_inform: Creating base message failed\n"));
    return;
  }

  srvr_msg = (struct dhcp_msg *)out_msg->payload;
  dhcp_common_option(srvr_msg, DHCP_OPTION_MESSAGE_TYPE, DHCP_OPTION_MESSAGE_TYPE_LEN, &options_len);
  dhcp_common_option_byte(srvr_msg, DHCP_ACK, &options_len);

  dhcp_common_option_trailer(srvr_msg, &options_len);

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_inform: realloc()ing\n"));
  pbuf_realloc(out_msg, (u16_t)((sizeof(struct dhcp_msg) - DHCP_OPTIONS_LEN) + options_len));
#ifdef  LWIP_DEV_DEBUG
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
             ("handle_inform: Send ACK to Client. Client is=%"U32_F"\n", client_msg->ciaddr.addr));
#endif
  ip_addr_set_ip4_u32_val(dst_addr, client_msg->ciaddr.addr);
  (void)udp_sendto_if_src(dhcps->pcb, out_msg, &dst_addr, DHCP_CLIENT_PORT, netif, &(netif->ip_addr));

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("handle_inform: deleting pbuf\n"));
  (void)pbuf_free(out_msg);

  return;
}

LWIP_STATIC void handle_client_messages(struct netif *netif, struct dhcps *dhcps,
                                        struct dhcp_msg *client_msg, ip4_addr_t serverid, u8_t msg_type)
{
  struct dyn_lease_addr *client_lease = NULL;

  client_lease = find_client_lease(dhcps, client_msg);
  switch (msg_type) {
    case DHCP_DISCOVER:
      handle_discover(netif, dhcps, client_msg, client_lease);
      break;
    case DHCP_REQUEST:
      handle_request(netif, dhcps, client_msg, client_lease, serverid);
      break;
    case DHCP_DECLINE:
      handle_decline(client_msg, client_lease);
      break;
    case DHCP_RELEASE:
      if ((client_lease != NULL) && (client_lease->cli_addr.addr == ntohl(client_msg->ciaddr.addr))) {
#ifdef  LWIP_DEV_DEBUG
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("DHCP Release: Client IPAdd =%"U32_F"\n", client_msg->ciaddr.addr));
#endif
        (void)memset_s(client_lease, sizeof(struct dyn_lease_addr), 0, sizeof(struct dyn_lease_addr));
        client_lease->flags = DHCPS_ADDRESS_FREE;
      }
      break;
    case DHCP_INFORM:
      handle_inform(netif, dhcps, client_msg);
      break;
    default:
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                  ("DHCP Server. Invalid message type received %d\n", msg_type));
  }
}

#if LWIP_DHCP_BOOTP_FILE
err_t dhcps_parse_options(struct pbuf *p, char *boot_file_name)
#else
err_t dhcps_parse_options(struct pbuf *p)
#endif
{
  u8_t *options = NULL;
  u16_t offset;
  u16_t offset_max;
  u16_t options_idx;
  u16_t options_idx_max;
  struct pbuf *q = NULL;
  int parse_file_as_options = 0;
  int parse_sname_as_options = 0;

  if (p == NULL) {
    return ERR_BUF;
  }
  /* clear received options */
  (void)memset_s(dhcps_rx_options_given, sizeof(dhcps_rx_options_given), 0, sizeof(dhcps_rx_options_given));
  /* check that beginning of dhcp_msg (up to and including chaddr) is in first pbuf */
  if (p->len < DHCP_SNAME_OFS) {
    return ERR_BUF;
  }

  /* parse options */
  /* start with options field */
  options_idx = DHCP_OPTIONS_OFS;
  /* parse options to the end of the received packet */
  options_idx_max = p->tot_len;
again:
  q = p;
  while ((q != NULL) && (options_idx >= q->len)) {
    options_idx = (u16_t)(options_idx - q->len);
    options_idx_max = (u16_t)(options_idx_max - q->len);
    q = q->next;
  }
  if (q == NULL) {
    return ERR_BUF;
  }
  offset = options_idx;
  offset_max = options_idx_max;
  options = (u8_t*)q->payload;
  /* at least 1 byte to read and no end marker, then at least 3 bytes to read? */
  while ((q != NULL) && (offset < offset_max) && (options[offset] != DHCP_OPTION_END)) {
    u8_t op = options[offset];
    u8_t len;
    u8_t decode_len = 0;
    int decode_idx = -1;
    u16_t val_offset = (u16_t)(offset + 2);
    /* len byte might be in the next pbuf */
    if ((offset + 1) < q->len) {
      len = options[offset + 1];
    } else {
      len = (u8_t)(q->next != NULL ? ((u8_t*)q->next->payload)[0] : 0);
    }

    decode_len = len;
    switch (op) {
      /* case(DHCP_OPTION_END): handled above */
      case (DHCP_OPTION_PAD):
        /* special option: no len encoded */
        decode_len = len = 0;
        /* will be increased below */
        offset--;
        break;
      case (DHCP_OPTION_SUBNET_MASK):
        LWIP_ERROR("len == 4", len == 4, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_SUBNET_MASK;
        break;
      case (DHCP_OPTION_ROUTER):
        decode_len = 4; /* only copy the first given router */
        LWIP_ERROR("len >= decode_len", len >= decode_len, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_ROUTER;
        break;
#if LWIP_DHCP_PROVIDE_DNS_SERVERS
      case (DHCP_OPTION_DNS_SERVER):
        /* special case: there might be more than one server */
        LWIP_ERROR("len %% 4 == 0", len % 4 == 0, return ERR_VAL);
        /* limit number of DNS servers */
        decode_len = (u8_t)LWIP_MIN(len, 4 * DNS_MAX_SERVERS);
        LWIP_ERROR("len >= decode_len", len >= decode_len, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_DNS_SERVER;
        break;
#endif /* LWIP_DHCP_PROVIDE_DNS_SERVERS */
      case (DHCP_OPTION_LEASE_TIME):
        LWIP_ERROR("len == 4", len == 4, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_LEASE_TIME;
        break;
      case (DHCP_OPTION_OVERLOAD):
        LWIP_ERROR("len == 1", len == 1, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_OVERLOAD;
        break;
      case (DHCP_OPTION_MESSAGE_TYPE):
        LWIP_ERROR("len == 1", len == 1, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_MSG_TYPE;
        break;
      case (DHCP_OPTION_SERVER_ID):
        LWIP_ERROR("len == 4", len == 4, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_SERVER_ID;
        break;
      case (DHCP_OPTION_T1):
        LWIP_ERROR("len == 4", len == 4, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_T1;
        break;
      case (DHCP_OPTION_T2):
        LWIP_ERROR("len == 4", len == 4, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_T2;
        break;
      case (DHCP_OPTION_REQUESTED_IP):
        LWIP_ERROR("len == 4", len == 4, return ERR_VAL);
        decode_idx = DHCP_OPTION_IDX_REQUESTED_IP;
        break;
      default:
        decode_len = 0;
        LWIP_DEBUGF(DHCP_DEBUG, ("skipping option %"U16_F" in options\n", op));
        break;
    }
    offset = (u16_t)(offset + len + 2);
    if ((decode_len > 0) && (decode_idx >= 0) && (decode_idx < DHCP_OPTION_IDX_MAX)) {
      u32_t value = 0;
      u16_t copy_len;
decode_next:
      /* PC Lint Fix for: Possible negative subscript (-1) in operator '[' */
      /* decode_idx is assigned with non-negative value in switch case, for negative we will not come here,
         So this should be OK. */
      if (!dhcps_option_given(dhcp, decode_idx)) {
        copy_len = (u16_t)LWIP_MIN(decode_len, 4);
        (void)pbuf_copy_partial(q, &value, copy_len, val_offset);
        if (decode_len > 4) {
          /* decode more than one u32_t */
          LWIP_ERROR("decode_len %% 4 == 0", decode_len % 4 == 0, return ERR_VAL);
          dhcps_got_option(NULL, decode_idx);
          dhcps_set_option_value(NULL, decode_idx, htonl(value));
          decode_len = (u8_t)(decode_len - 4);
          val_offset = (u16_t)(val_offset + 4);
          decode_idx++;
          goto decode_next;
        } else if (decode_len == 4) {
          value = ntohl(value);
        } else {
          LWIP_ERROR("invalid decode_len", decode_len == 1, return ERR_VAL);
          value = ((u8_t*)&value)[0];
        }
        dhcps_got_option(NULL, decode_idx);
        dhcps_set_option_value(NULL, decode_idx, value);
      }
    }
    if (offset >= q->len) {
      offset = (u16_t)(offset - q->len);
      offset_max = (u16_t)(offset_max - q->len);
      if ((offset < offset_max) && offset_max) {
        q = q->next;
        if (q == NULL) {
            LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("next pbuf was null"));
            break;
        }
        options = (u8_t*)q->payload;
      } else {
        // We've run out of bytes, probably no end marker. Don't proceed.
        break;
      }
    }
  }
  /* is this an overloaded message? */
  if (dhcps_option_given(NULL, DHCP_OPTION_IDX_OVERLOAD)) {
    u32_t overload = dhcps_get_option_value(NULL, DHCP_OPTION_IDX_OVERLOAD);
    dhcps_clear_option(NULL, DHCP_OPTION_IDX_OVERLOAD);
    if (overload == DHCP_OVERLOAD_FILE) {
      parse_file_as_options = 1;
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("overloaded file field\n"));
    } else if (overload == DHCP_OVERLOAD_SNAME) {
      parse_sname_as_options = 1;
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("overloaded sname field\n"));
    } else if (overload == DHCP_OVERLOAD_SNAME_FILE) {
      parse_sname_as_options = 1;
      parse_file_as_options = 1;
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("overloaded sname and file field\n"));
    } else {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("invalid overload option: %d\n", (int)overload));
    }

#if LWIP_DHCP_BOOTP_FILE
    if ((boot_file_name != NULL) && (parse_file_as_options == 0)) {
      /* only do this for ACK messages */
      if (dhcps_option_given(NULL, DHCP_OPTION_IDX_MSG_TYPE) &&
        (dhcps_get_option_value(NULL, DHCP_OPTION_IDX_MSG_TYPE) == DHCP_ACK)) {
        /* copy bootp file name, don't care for sname (server hostname) */
        (void)pbuf_copy_partial(p, boot_file_name, DHCP_FILE_LEN - 1, DHCP_FILE_OFS);
      }
      /* make sure the string is really NULL-terminated */
      boot_file_name[DHCP_FILE_LEN - 1] = 0;
    }
#endif /* LWIP_DHCP_BOOTP_FILE */
  }
  if (parse_file_as_options == 1) {
    /* if both are overloaded, parse file first and then sname (RFC 2131 ch. 4.1) */
    parse_file_as_options = 0;
    options_idx = DHCP_FILE_OFS;
    options_idx_max = DHCP_FILE_OFS + DHCP_FILE_LEN;
    goto again;
  } else if (parse_sname_as_options == 1) {
    parse_sname_as_options = 0;
    options_idx = DHCP_SNAME_OFS;
    options_idx_max = DHCP_SNAME_OFS + DHCP_SNAME_LEN;
    goto again;
  }
  return ERR_OK;
}

LWIP_STATIC void dhcps_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *ip_addr, u16_t port)
{
  struct netif *netif = (struct netif *)arg;
  struct dhcps *dhcps = netif->dhcps;
  struct dhcp_msg *client_msg = (struct dhcp_msg *)p->payload;
  u8_t msg_type;
  ip4_addr_t serverid;
  ip4_addr_t addr;

  if (client_msg == NULL) {
    return;
  }
  addr.addr = ip_addr->u_addr.ip4.addr;
  serverid.addr = 0;
#ifdef  LWIP_DEV_DEBUG
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
              ("dhcps_recv(pbuf = %p) from DHCP Client %"U16_F".%"U16_F".%"U16_F".%"U16_F" port %"U16_F"\n", (void*)p,
              ip4_addr1_16(&addr), ip4_addr2_16(&addr), ip4_addr3_16(&addr), ip4_addr4_16(&addr), port));
#endif
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("pbuf->len = %"U16_F"\n", p->len));
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("pbuf->tot_len = %"U16_F"\n", p->tot_len));
  /* prevent warnings about unused arguments */
  LWIP_UNUSED_ARG(pcb);
  LWIP_UNUSED_ARG(addr);
  LWIP_UNUSED_ARG(port);

  (void)memset_s(dhcps_rx_options_given, sizeof(dhcps_rx_options_given), 0, sizeof(dhcps_rx_options_given));

  /* Check and remove old entries on each call to dhcp_recv. This way, we don't need to maintain timers */
  remove_stale_entries(dhcps);

  if (p->len < DHCP_OPTIONS_OFS) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                ("DHCP client message or pbuf too short. pbuf len =%"U16_F" DHCP MIN Reply Len = %"U32_F"\n",
                p->len, DHCP_MIN_REPLY_LEN));
    goto free_pbuf_and_return;
  }

  if (client_msg->op != DHCP_BOOTREQUEST) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                ("Not a DHCP reply message, Type %"U16_F"\n", (u16_t)client_msg->op));
    goto free_pbuf_and_return;
  }

  if (client_msg->cookie != PP_HTONL(DHCP_MAGIC_COOKIE)) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                ("DHCP Server. Cookie Value is incorrect. %"U32_F"\n", (u32_t)client_msg->cookie));
    goto free_pbuf_and_return;
  }

  if (client_msg->hlen != ETHARP_HWADDR_LEN) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                ("DHCP Server. Invalid hardware address length %"U16_F"\n", (u16_t)client_msg->hlen));
    goto free_pbuf_and_return;
  }

#if LWIP_DHCP_BOOTP_FILE
  if (dhcps_parse_options(p, NULL) != ERR_OK) {
#else
  if (dhcps_parse_options(p) != ERR_OK) {
#endif
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                ("Parsing of Options failed in DHCP Client Message\n"));
    goto free_pbuf_and_return;
  }

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("Searching DHCP_OPTION_MESSAGE_TYPE\n"));
  /* obtain pointer to DHCP message type */
  if (!dhcps_option_given(dhcps, DHCP_OPTION_IDX_MSG_TYPE)) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                ("DHCP_OPTION_MESSAGE_TYPE option not found\n"));
    goto free_pbuf_and_return;
  }

  /* read DHCP message type */
  msg_type = (u8_t)dhcps_get_option_value(dhcps, DHCP_OPTION_IDX_MSG_TYPE);

  if (dhcps_option_given(dhcps, DHCP_OPTION_IDX_SERVER_ID)) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                ("DHCP_OPTION_SERVER_ID option found\n"));
    /* Parse options would have changed it to host order. But, we have our IP stored in netif in network order */
    serverid.addr = htonl((u32_t)dhcps_get_option_value(dhcps, DHCP_OPTION_IDX_SERVER_ID));
  }

  if ((serverid.addr != 0) && ((msg_type == DHCP_DISCOVER) || (msg_type == DHCP_INFORM))) {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                  ("Serverid present in DHCP_DISCOVER and DHCP_INFORM messages\n"));
    goto free_pbuf_and_return;
  }

  if ((!ip4_addr_cmp(&serverid, ip_2_ip4(&netif->ip_addr))) &&
    ((msg_type == DHCP_DECLINE) || (msg_type == DHCP_RELEASE))) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                ("Serverid not present in DHCP_RELEASE and DHCP_DECLINE messages\n"));
    goto free_pbuf_and_return;
  }

  handle_client_messages(netif, dhcps, client_msg, serverid, msg_type);

  free_pbuf_and_return:
  (void)pbuf_free(p);
}

err_t dhcps_start(struct netif *netif, const char *start_ip, u16_t ip_num)
{
  struct dhcps *dhcps = NULL;
  ip4_addr_t address_in_hton;
  int err;

  LWIP_ERROR("netif != NULL", (netif != NULL), return ERR_ARG);
  dhcps = netif->dhcps;

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
              ("dhcps_start(netif=%p) %s\n", (void*)netif, netif_get_name(netif)));

  if (netif->mtu < DHCP_MAX_MSG_LEN_MIN_REQUIRED) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
                ("MTU =%"U16_F",DHCP Msg Len Required =%"U32_F"\n", netif->mtu, DHCP_MAX_MSG_LEN_MIN_REQUIRED));
    return ERR_MEM;
  }

  if (dhcps != NULL) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcps_start(): DHCP Server is already started\n"));
    return ERR_MEM;
  }

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcps_start(): starting new DHCP Server\n"));
  dhcps = (struct dhcps *)mem_malloc(sizeof(struct dhcps));
  if (dhcps == NULL) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcps_start(): could not allocate dhcp\n"));
    return ERR_MEM;
  }

  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcps_start(): allocated dhcp"));

  (void)memset_s(dhcps, sizeof(struct dhcps), 0, sizeof(struct dhcps));

  dhcps->pcb = udp_new();
  if (dhcps->pcb == NULL) {
    LWIP_DEBUGF(DHCP_DEBUG  | LWIP_DBG_TRACE, ("dhcp_start(): could not allocate pcb\n"));
    mem_free((void *)dhcps);
    return ERR_MEM;
  }

#if LWIP_SO_BINDTODEVICE
  /* bind dhcp udp_pcb to specific netif, this could make dhcp server start on multiple netif */
  dhcps->pcb->ifindex = netif->ifindex;
#endif
  if ((start_ip == NULL) || (ip_num == 0)) {
    /* use default ip lease configuration. */
    dhcps->start_addr.addr = ntohl(ip_2_ip4(&netif->ip_addr)->addr & ip_2_ip4(&netif->netmask)->addr) + 1;
    dhcps->end_addr.addr = ntohl(ip_2_ip4(&netif->ip_addr)->addr | (~ip_2_ip4(&netif->netmask)->addr)) - 1;
    dhcps->lease_num = (u8_t)(dhcps->end_addr.addr - dhcps->start_addr.addr + 1);
    if (dhcps->lease_num > LWIP_DHCPS_MAX_LEASE) {
      dhcps->lease_num = LWIP_DHCPS_MAX_LEASE;
      dhcps->end_addr.addr = dhcps->start_addr.addr + LWIP_DHCPS_MAX_LEASE - 1;
    }
  } else {
    dhcps->start_addr.addr = ntohl(ipaddr_addr(start_ip));
    dhcps->end_addr.addr = (u32_t)(dhcps->start_addr.addr + (u32_t) (LWIP_MIN(ip_num - 1, LWIP_DHCPS_MAX_LEASE - 1)));

    ip4_addr_set_hton(&address_in_hton, &dhcps->start_addr);

    if (!ip4_addr_netcmp((&address_in_hton), ip_2_ip4(&netif->ip_addr), ip_2_ip4(&netif->netmask)) ||
      ip4_addr_isbroadcast((&address_in_hton), netif)) {
      LWIP_DEBUGF(DHCP_DEBUG  | LWIP_DBG_TRACE, ("dhcp_start(): %s in not a valid ip lease\n", start_ip));
      udp_remove(dhcps->pcb);
      mem_free((void *)dhcps);
      return ERR_ARG;
    }

    ip4_addr_set_hton(&address_in_hton, &dhcps->end_addr);

    if (!ip4_addr_netcmp((&address_in_hton), ip_2_ip4(&netif->ip_addr), ip_2_ip4(&netif->netmask)) ||
      ip4_addr_isbroadcast((&address_in_hton), netif)) {
      dhcps->end_addr.addr = ntohl(ip_2_ip4(&netif->ip_addr)->addr | (~ip_2_ip4(&netif->netmask)->addr)) - 1;
    }
    dhcps->lease_num = (u8_t)(dhcps->end_addr.addr - dhcps->start_addr.addr + 1);
  }

  dhcps->netif = netif;
  dhcps->pcb->so_options |= SOF_BROADCAST;
  err = udp_bind(dhcps->pcb, IP_ADDR_ANY, DHCP_SERVER_PORT);
  if (err != ERR_OK) {
    udp_remove(dhcps->pcb);
    mem_free((void *)dhcps);
    return ERR_MEM;
  }

  err = udp_connect(dhcps->pcb, IP_ADDR_ANY, DHCP_CLIENT_PORT);
  if (err != ERR_OK) {
    udp_remove(dhcps->pcb);
    mem_free((void *)dhcps);
    return ERR_MEM;
  }
  udp_recv(dhcps->pcb, dhcps_recv, netif);
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcps_start(): starting DHCPS Successfully\n"));
#ifdef  LWIP_DEV_DEBUG
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
              ("dhcps_start(): DHCPS Conf:: netif addr = %"U32_F" dhcps start addr%"U32_F" dhcp end addr%"U32_F"\n",
              ip_2_ip4(&netif->ip_addr)->addr, dhcps->start_addr.addr, dhcps->end_addr.addr));
#endif
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE,
              ("dhcps_start(): DHCPS Lease Conf:: Lease Time = %"U32_F" Offer Time = %"U32_F"\n",
              LWIP_DHCPS_LEASE_TIME, LWIP_DHCPS_OFFER_TIME));
  netif->dhcps = dhcps;
  return ERR_OK;
}

void dhcps_stop(struct netif *netif)
{
  LWIP_ERROR("dhcps_stop: netif != NULL", (netif != NULL), return);

  if (netif->dhcps != NULL) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcps_stop(): Stopping DHCP Server\n"));
    if (netif->dhcps->pcb != NULL) {
      LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcps_stop(): Removing UDP PCB\n"));
      udp_remove(netif->dhcps->pcb);
      netif->dhcps->pcb = NULL;
    }

    mem_free(netif->dhcps);
    netif->dhcps = NULL;
  }
}

#endif

