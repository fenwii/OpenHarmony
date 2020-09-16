/**
 * @file
 * DHCP client API
 */

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
 *
 * Author: Leon Woestenberg <leon.woestenberg@gmx.net>
 *
 */
#ifndef LWIP_HDR_DHCP_H
#define LWIP_HDR_DHCP_H

#include "lwip/opt.h"

#if LWIP_DHCP /* don't build if not configured for use in lwipopts.h */

#include "lwip/netif.h"
#include "lwip/udp.h"
#include "lwip/dhcps.h"
#include "lwip/prot/dhcp.h"
#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#ifndef LWIP_DHCP_NATIVE_IDX
#define LWIP_DHCP_NATIVE_IDX 0
#endif

#ifndef LWIP_DHCP_ANNOUNCE_NUM
#define LWIP_DHCP_ANNOUNCE_NUM 2
#endif

#ifndef LWIP_DHCP_ANNOUNCE_INTERVAL
#define LWIP_DHCP_ANNOUNCE_INTERVAL 2 /* seconds */
#endif

#if LWIP_DHCP_SUBSTITUTE
struct dhcp_clients_info;
#ifndef DHCP_CLIENT_NUM
#define DHCP_CLIENT_NUM 256
#endif
typedef u16_t dhcp_num_t;
#define DHCP_NUM_F "hu"
#else
#ifndef DHCP_CLIENT_NUM
#define DHCP_CLIENT_NUM 1
#endif
typedef u32_t dhcp_num_t;
#define DHCP_NUM_F "u"
#endif /* LWIP_DHCP_SUBSTITUTE */

#define IPV4_ADDRESS_PREFIX_CLASS_A 127
#define IPV4_ADDRESS_PREFIX_CLASS_C 192

#define DHCP_XID(_xid, _mac, _mac_len, _dhcp_xid) do { \
  u8_t *_p = (u8_t *)(&(_xid)); \
  _p[0] = (_mac)[(_mac_len) - 3]; \
  _p[1] = (_mac)[(_mac_len) - 2]; \
  _p[2] = (_mac)[(_mac_len) - 1]; \
  _p[3] = _dhcp_xid; \
} while (0)

#define DHCP_HOST_TO_IP(_ip, _serv_ip, _mask, _host) do { \
  u32_t _ipaddr = (u32_t)(_host); \
  (_ip) = (((_serv_ip) & (_mask)) | lwip_htonl(_ipaddr)); \
} while (0)

#define DHCP_IP_TO_HOST(_host, _ip, _mask) do { \
  (_host) = (dhcp_num_t)(lwip_ntohl(_ip) & (~lwip_ntohl(_mask))); \
} while (0)

/* more related events should be defined here */
#define DHCP_EVENT_HW 0x01

/* period (in seconds) of the application calling dhcp_coarse_tmr() */
#define DHCP_COARSE_TIMER_SECS  10
/* period (in milliseconds) of the application calling dhcp_coarse_tmr() */
#define DHCP_COARSE_TIMER_MSECS (DHCP_COARSE_TIMER_SECS * 1000UL)
/* period (in milliseconds) of the application calling dhcp_fine_tmr() */
#define DHCP_FINE_TIMER_MSECS   500

#ifndef DHCP_DISCOVER_RETRANSMIT_INTERVAL
#define DHCP_DISCOVER_RETRANSMIT_INTERVAL 250
#endif

#define DHCP_BOOT_FILE_LEN      128U
#define DHCP_BROADCAST_FLAG 0x8000
/* AutoIP cooperation flags (struct dhcp.autoip_coop_state) */
typedef enum {
  DHCP_AUTOIP_COOP_STATE_OFF  = 0,
  DHCP_AUTOIP_COOP_STATE_ON   = 1
} dhcp_autoip_coop_state_enum_t;

/*
 * DHCP_OPTION_MAX_MSG_SIZE is set to the MTU
 * MTU is checked to be big enough in dhcp_start
 */
#define DHCP_MAX_MSG_LEN(netif)        (netif->mtu)
#define DHCP_MAX_MSG_LEN_MIN_REQUIRED  576

#if LWIP_DHCP_VENDOR_CLASS_IDENTIFIER
struct vci_info {
  /* buffer for vendor class identifier information */
  char vci[DHCP_VCI_MAX_LEN];
  /* real length of vci */
  u8_t vci_len;
  /* pad for performance optimization */
  char pad[24];
};

err_t dhcp_set_vci(char *vci, u8_t vci_len);
#if LWIP_DHCP_GET_VENDOR_CLASS_IDENTIFIER
err_t dhcp_get_vci(char *vci, u8_t *vci_len);
#endif /* LWIP_DHCP_GET_VENDOR_CLASS_IDENTIFIER */
#endif /* LWIP_DHCP_VENDOR_CLASS_IDENTIFIER */

/** Minimum length for reply before packet is parsed */
#define DHCP_MIN_REPLY_LEN             44

#define REBOOT_TRIES                2

#if LWIP_DNS && LWIP_DHCP_MAX_DNS_SERVERS
#if DNS_MAX_SERVERS > LWIP_DHCP_MAX_DNS_SERVERS
#define LWIP_DHCP_PROVIDE_DNS_SERVERS LWIP_DHCP_MAX_DNS_SERVERS
#else
#define LWIP_DHCP_PROVIDE_DNS_SERVERS DNS_MAX_SERVERS
#endif
#else
#define LWIP_DHCP_PROVIDE_DNS_SERVERS 0
#endif

/*
 * Option handling: options are parsed in dhcp_parse_reply
 * and saved in an array where other functions can load them from.
 * This might be moved into the struct dhcp (not necessarily since
 * lwIP is single-threaded and the array is only used while in recv
 * callback).
 */
enum dhcp_option_idx {
  DHCP_OPTION_IDX_OVERLOAD = 0,
  DHCP_OPTION_IDX_MSG_TYPE,
  DHCP_OPTION_IDX_SERVER_ID,
  DHCP_OPTION_IDX_LEASE_TIME,
  DHCP_OPTION_IDX_T1,
  DHCP_OPTION_IDX_T2,
  DHCP_OPTION_IDX_SUBNET_MASK,
  DHCP_OPTION_IDX_ROUTER,
#if LWIP_DHCP_PROVIDE_DNS_SERVERS
  DHCP_OPTION_IDX_DNS_SERVER,
  DHCP_OPTION_IDX_DNS_SERVER_LAST = DHCP_OPTION_IDX_DNS_SERVER + LWIP_DHCP_PROVIDE_DNS_SERVERS - 1,
#endif /* LWIP_DHCP_PROVIDE_DNS_SERVERS */
#if LWIP_DHCP_GET_NTP_SRV
  DHCP_OPTION_IDX_NTP_SERVER,
  DHCP_OPTION_IDX_NTP_SERVER_LAST = DHCP_OPTION_IDX_NTP_SERVER + LWIP_DHCP_MAX_NTP_SERVERS - 1,
#endif /* LWIP_DHCP_GET_NTP_SRV */
  DHCP_OPTION_IDX_REQUESTED_IP,
#if LWIP_DHCPS_AGENT_INFO
  DHCP_OPTION_IDX_AGENT_INFO,
#endif
  DHCP_OPTION_IDX_MAX
};

struct dhcp_state {
  /* transaction identifier of last sent request */
  u8_t xid;
  /* retries of current request <= 255 */
  u8_t tries;
  u16_t lease_used; /* #ticks with period DHCP_COARSE_TIMER_SECS since last received DHCP ack */
  u16_t request_timeout; /* #ticks with period DHCP_FINE_TIMER_SECS for request timeout */
  u16_t re_time;  /* #ticks with period DHCP_COARSE_TIMER_SECS until next renew/rebind try */
  /* current DHCP state machine state */
  u8_t state: 4;
  u8_t hwaddr_len: 4;
  /* idx in NAT64 table */
  dhcp_num_t idx;
  /* host part of IP */
  dhcp_num_t offered_ip_addr;
};

struct dhcp_client {
  u16_t t0_timeout; /* #ticks with period DHCP_COARSE_TIMER_SECS for lease time */
  u16_t t1_timeout;  /* #ticks with period DHCP_COARSE_TIMER_SECS for renewal time */
  u16_t t2_timeout;  /* #ticks with period DHCP_COARSE_TIMER_SECS for rebind time */
  ip_addr_t server_ip_addr; /* dhcp server address that offered this lease (ip_addr_t because passed to UDP) */
  u8_t subnet_mask_given;
  ip4_addr_t offered_sn_mask;
  ip4_addr_t offered_gw_addr;
  ip4_addr_t relay_ip;
  u32_t offered_t0_lease; /* lease period (in seconds) */
  u32_t offered_t1_renew; /* recommended renew time (usually 50% of lease period) */
  u32_t offered_t2_rebind; /* recommended rebind time (usually 87.5 of lease period)  */

  /* incoming msg */
  struct dhcp_msg *msg_in;
  struct pbuf *p_out; /* pbuf of outcoming msg */
  struct dhcp_msg *msg_out; /* outgoing msg */
  u16_t options_out_len; /* outgoing msg options length */

  u8_t hwaddr[NETIF_MAX_HWADDR_LEN];
  dhcp_num_t cli_cnt;
  /* cli_idx = LWIP_DHCP_NATIVE_IDX always means the client for the netif */
  dhcp_num_t cli_idx;
  struct dhcp_state states[DHCP_CLIENT_NUM];
};

struct dhcp {
  /* track PCB allocation state */
  u8_t pcb_allocated;
#if LWIP_DHCP_AUTOIP_COOP
  u8_t autoip_coop_state;
#endif

#if LWIP_DHCP_BOOTP_FILE
  ip4_addr_t offered_si_addr;
  char boot_file_name[DHCP_BOOT_FILE_LEN];
#endif /* LWIP_DHCP_BOOTPFILE */
#if LWIP_DHCP_SUBSTITUTE
  u8_t flags;
  struct dhcp_clients_info *clis_info;
#endif
  struct dhcp_client client;
};

#ifdef LWIP_DHCPS
struct dyn_lease_addr {
  u8_t cli_hwaddr[DHCP_CHADDR_LEN];
  u32_t flags;
  u32_t leasetime;
  u32_t proposed_leasetime;
  ip4_addr_t cli_addr;
};

struct dhcps {
  struct udp_pcb *pcb;
  struct dyn_lease_addr leasearr[LWIP_DHCPS_MAX_LEASE];
  u8_t pcb_allocated;
  u8_t lease_num;
  struct netif *netif;
  ip4_addr_t start_addr;
  ip4_addr_t end_addr;
#if LWIP_DHCPS_AGENT_INFO
  struct pbuf *p_in; /* pbuf of incoming msg */
#endif
};
#endif

#if LWIP_API_RICH
void dhcp_set_struct(struct netif *netif, struct dhcp *dhcp);
/* Remove a struct dhcp previously set to the netif using dhcp_set_struct() */
void dhcp_remove_struct(struct netif *netif);
#endif /* LWIP_API_RICH */

void dhcp_cleanup(struct netif *netif);
err_t dhcp_is_bound(struct netif *netif);
err_t dhcp_start(struct netif *netif);
err_t dhcp_renew(struct netif *netif);
err_t dhcp_release(struct netif *netif);
void dhcp_stop(struct netif *netif);
void dhcp_inform(struct netif *netif);
void dhcp_network_changed(struct netif *netif);
#if DHCP_DOES_ARP_CHECK
void dhcp_arp_reply(struct netif *netif, const ip4_addr_t *addr);
#endif
#if LWIP_API_RICH
u8_t dhcp_supplied_address(const struct netif *netif);
#endif /* LWIP_API_RICH */
/* to be called every minute */
void dhcp_coarse_tmr(void);
/* to be called every half second */
void dhcp_fine_tmr(void);

#if LWIP_LOWPOWER
u32_t dhcp_coarse_tmr_tick(void);
u32_t dhcp_fine_tmr_tick(void);
#endif

#if LWIP_DHCP_GET_NTP_SRV
/* This function must exist, in other to add offered NTP servers to
 * the NTP (or SNTP) engine.
 * See LWIP_DHCP_MAX_NTP_SERVERS */
extern void dhcp_set_ntp_servers(u8_t num_ntp_servers, const ip4_addr_t *ntp_server_addrs);
#endif /* LWIP_DHCP_GET_NTP_SRV */

#define netif_dhcp_data(netif) ((struct dhcp*)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP))

#if LWIP_DHCP_SUBSTITUTE

struct dhcp_client_info {
  ip4_addr_t ipaddr;
  u8_t mac[NETIF_MAX_HWADDR_LEN];
#if NETIF_MAX_HWADDR_LEN != 6
  u8_t mac_len;
#endif
};

struct dhcp_clients_info {
  dhcp_num_t num;
  struct dhcp_client_info clis[0];
};

#if LWIP_ARP
void dhcp_events_record(struct netif *netif, u8_t flags);
void dhcp_events_trigger(struct netif *netif);
#endif /* LWIP_ARP */
err_t dhcp_substitute_start(struct netif *netif, dhcp_num_t mac_idx);
void dhcp_substitute_stop(struct netif *netif, dhcp_num_t mac_idx);
err_t dhcp_substitute_idx_to_ip(struct netif *netif, dhcp_num_t idx, ip4_addr_t *ip);
err_t dhcp_clients_info_get(struct netif *netif, void *arg);
err_t dhcp_clients_info_free(struct netif *netif, void *arg);
#if LWIP_ENABLE_BASIC_SHELL_CMD
s32_t dhcp_netif_addr_clients_check(const struct netif *netif, const ip4_addr_t *ipaddr);
#endif /* LWIP_ENABLE_BASIC_SHELL_CMD */
#endif /* LWIP_DHCP_SUBSTITUTE */

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_DHCP */

#endif /* LWIP_HDR_DHCP_H */
