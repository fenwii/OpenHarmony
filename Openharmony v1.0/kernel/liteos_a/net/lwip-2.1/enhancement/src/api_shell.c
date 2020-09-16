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

#include "../core/ipv4/etharp.c"  /* for arp_table */
#define icmp6_hdr netinet_icmp6_hdr
#include <netinet/icmp6.h>
#undef icmp6_hdr
#include "api_shell_fix.h"
#include "lwip/opt.h"

#if LWIP_ENABLE_LOS_SHELL_CMD
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/netif.h"
#include "lwip/netdb.h"
#include "lwip/stats.h"
#include "lwip/err.h"
#include "lwip/inet.h"
#include "netif/etharp.h"
#include "lwip/ip_addr.h"
#include "lwip/ip6_addr.h"
#include "lwip/icmp.h"
#include "lwip/priv/nd6_priv.h"
#include "lwip/sockets.h"
#include "lwip/inet_chksum.h"
#include "lwip/raw.h"
#include "los_config.h"
#include <string.h>
#include "limits.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <poll.h>

#include "api_shell.h"

#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "lwip/udp.h"
#include "lwip/priv/tcp_priv.h"

#include "lwip/dhcp.h"
#include "lwip/netifapi.h"
#include "los_strnlen_user.h"
#include "linux/kernel.h"
#ifdef LOSCFG_SHELL
#include "shcmd.h"
#include "shell.h"
#endif

#define netif_find netifapi_netif_find_by_name

#if LWIP_ARP
extern sys_sem_t ip_conflict_detect;
#endif
extern volatile int tcpip_init_finish;
extern const char *const tcp_state_str[];
extern int get_unused_socket_num(void);

#if LWIP_IPV6
#define LWIP_MAX_PING6_ARG_COUNT              64
#define LWIP_PING6_STANDARD_PKT_SIZE          56
#define LWIP_PING6_STARTING_SEQ_NUM           0x2255
#define LWIP_PING6_OUT_OF_ORDER_MAGNITUDE     1

#define LWIP_PING6_COUNT_ARG           1
#define LWIP_PING6_SOURCE_ADDRESS_ARG  2
#define LWIP_PING6_INTERFACE_ARG       4
#define LWIP_PING6_HOSTNAME_ARG        8
#define LWIP_PING6_DEFAULT_SOCKET      16
#endif

/* Forward Declarations [START] */
#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
int print_netif(struct netif *netif, char *print_buf, unsigned int buf_len);

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
void lwip_ifconfig_show_internal(void *arg);

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
void lwip_ifconfig_internal(void *arg);

void lwip_printsize(size_t size);
LWIP_STATIC void lwip_ifconfig_usage(const char *cmd);

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
void lwip_arp_show_internal(struct netif *netif, char *printf_buf, unsigned int buf_len);

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
void lwip_arp_internal(void *arg);

LWIP_STATIC void lwip_arp_usage(const char *cmd);
void ifup_internal(void *arg);
void ifdown_internal(void *arg);

#if LWIP_DNS
LWIP_STATIC unsigned int get_hostip(const char *hname);

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
struct hostent *gethostnameinfo(const char *host);

#endif /* LWIP_DNS */

#ifdef LWIP_DEBUG_INFO
LWIP_STATIC u32_t netdebug_memp(int argc, const char **argv);
LWIP_STATIC u32_t netdebug_sock(int argc, const char **argv);
u32_t osShellNetDebug(int argc, const char **argv);
u32_t osShellIpDebug(int argc, const char **argv);
#endif /* LWIP_DEBUG_INFO */
#if LWIP_IPV6
/* Holds params for ping6 task */
typedef struct ping6_args {
    u8_t args_found;
    u8_t interface_index;
    u8_t host_index;
    u8_t pad;
    u32_t pingcount;
    ip6_addr_t src_addr;
    ip6_addr_t dst_addr;
} ping6_args_t;

/* Holds stats for ongoing ping6 task */
typedef struct ping6_stats {
    u32_t flag;
    u32_t min_rtt;
    u32_t max_rtt;
    float avg_rtt;
} ping6_stats_t;
LWIP_STATIC void update_ping6_stats(ping6_stats_t *ping6_stats, u32_t rtt, u32_t nrecieved);
LWIP_STATIC int parse_args_ping6(int argc, const char **argv, ping6_args_t *ping6_params);

u32_t osShellPing6(int argc, const char **argv);
LWIP_STATIC int create_ping6_socket(u8_t type, const void *param);
LWIP_STATIC const char *convert_icmpv6_err_to_string(u8_t err_type);
#endif /* LWIP_IPV6 */
u32_t osTcpserver(int argc, const char **argv);
void udpserver(int argc, const char **argv);
void tcp_access(int sockfd);
#if LWIP_IPV6
int netstat_get_udp_sendQLen6(struct udp_pcb *udppcb, struct pbuf *udpbuf);
int netstat_udp_sendq6(struct udp_pcb *upcb);
#endif
#if LWIP_IPV4
int netstat_get_udp_sendQLen(struct udp_pcb *udppcb, struct pbuf *udpbuf);
#endif
int netstat_tcp_sendq(struct tcp_pcb *tpcb);
int netstat_tcp_recvq(struct tcp_pcb *tpcb);
int netstat_netconn_recvq(const struct netconn *conn);

int netstat_udp_sendq(struct udp_pcb *upcb);
int netstat_netconn_sendq(struct netconn *conn);
/* Forward Declarations [END] */

#define IFCONFIG_OPTION_SET_IP          (1)
#define IFCONFIG_OPTION_SET_NETMASK     (1 << 1)
#define IFCONFIG_OPTION_SET_GW          (1 << 2)
#define IFCONFIG_OPTION_SET_HW          (1 << 3)
#define IFCONFIG_OPTION_SET_UP          (1 << 4)
#define IFCONFIG_OPTION_SET_DOWN        (1 << 5)
#define IFCONFIG_OPTION_SET_MTU         (1 << 6)
#define IFCONFIG_OPTION_DEL_IP          (1 << 7)

#define NETSTAT_ENTRY_SIZE 120
#define MAX_NETSTAT_ENTRY (NETSTAT_ENTRY_SIZE * (MEMP_NUM_TCP_PCB + MEMP_NUM_UDP_PCB + MEMP_NUM_TCP_PCB_LISTEN + 1))

#define PRINT_BUF_LEN   1024
#define MAX_MACADDR_STRING_LENGTH    18 /* including NULL */

#define CONVERT_STRING_TO_HEX(_src, _dest)    \
{                                           \
  const char *_srcString = (char *)_src;    \
  _dest = 0;                                  \
  while (*_srcString) {                       \
    _dest = (unsigned char)((_dest << 4) & 0xFF);            \
    if ((*_srcString >= 48) && (*_srcString <= 57))    /* between 0 to 9 */  \
      _dest |= (unsigned char)(*_srcString - 48);                     \
    else if ((*_srcString >= 65 && *_srcString <= 70)) /* between A to F */  \
      _dest |= (unsigned char)((*_srcString - 65) + 10);              \
    else if ((*_srcString >= 97 && *_srcString <= 102)) /* between a to f */  \
      _dest |= (unsigned char)((*_srcString - 97) + 10);              \
    else break;                             \
    ++_srcString;                           \
  }                                         \
}

#define ERR_IFCONFIG_STRING_PUT(ret, str)     do                                             \
{                                                                                            \
  (ret) = snprintf_s(ifconfig_cmd->cb_print_buf + ifconfig_cmd->print_len,                 \
                     PRINT_BUF_LEN - ifconfig_cmd->print_len,                             \
                     ((PRINT_BUF_LEN - ifconfig_cmd->print_len) - 1), (str));             \
  if (((ret) > 0) && ((unsigned int)(ret) < (PRINT_BUF_LEN - ifconfig_cmd->print_len)))   \
    ifconfig_cmd->print_len += (unsigned int)(ret);                                       \
} while(0)

#define LWIP_MSECS_TO_SECS(time_in_msecs) (time_in_msecs / 1000)
struct ifconfig_option {
    char iface[IFNAMSIZ];
    unsigned int option;
    ip_addr_t ip_addr;
    ip_addr_t netmask;
    ip_addr_t gw;
    unsigned char ethaddr[6];
    u16_t mtu;
    /* when using telnet, print to the telnet socket will result in system  */
    /* deadlock. So we cahe the prinf data to a buf, and when the tcpip      */
    /* callback returns, then print the data out to the telnet socket       */
    sys_sem_t cb_completed;
    char cb_print_buf[PRINT_BUF_LEN];
    unsigned int print_len;
};

struct netstat_data {
    s8_t *netstat_out_buf;
    u32_t netstat_out_buf_len;
    u32_t netstat_out_buf_updated_len;
    sys_sem_t cb_completed;
};

struct if_cmd_data {
    char *if_name;
    err_t err;
    sys_sem_t cb_completed;
};

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
int print_netif(struct netif *netif, char *print_buf, unsigned int buf_len)
{
    int i, ret;
    char *tmp = print_buf;
#if LWIP_IPV6
    char *addr = NULL;
#endif

    if (netif->link_layer_type == LOOPBACK_IF) {
        ret = snprintf_s(tmp, buf_len, (buf_len - 1), "%.2s\t", netif->name);
    } else {
        ret = snprintf_s(tmp, buf_len, (buf_len - 1), "%s\t", netif_get_name(netif));
    }
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;
#if LWIP_IPV4
    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "ip:%s ", ipaddr_ntoa(&netif->ip_addr));
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "netmask:%s ", ipaddr_ntoa(&netif->netmask));
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "gateway:%s\n", ipaddr_ntoa(&netif->gw));
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;
#endif

#if LWIP_IPV6
    for (i = 0; i < LWIP_IPV6_NUM_ADDRESSES; i++) {
        /* only PREFERRED addresses are displyaed */
        if (!ip6_addr_isvalid(netif->ip6_addr_state[i])) {
            continue;
        }
        addr = ip6addr_ntoa((const ip6_addr_t *)&netif->ip6_addr[i]);
        ret = snprintf_s(tmp, buf_len, (buf_len - 1), "\tip6: %s/64\n", addr ? addr : "::");
        if ((ret <= 0) || ((unsigned int)ret >= buf_len))
            goto out;
        tmp += ret;
        buf_len -= (unsigned int)ret;
    }
#endif

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "\tHWaddr ");
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    for (i = 0; i < netif->hwaddr_len - 1; i++) {
        ret = snprintf_s(tmp, buf_len, (buf_len - 1), "%02x:", netif->hwaddr[i]);
        if ((ret <= 0) || ((unsigned int)ret >= buf_len))
            goto out;
        tmp += ret;
        buf_len -= (unsigned int)ret;
    }

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "%02x", netif->hwaddr[i]);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), " MTU:%d %s", netif->mtu,
                     netif->flags & NETIF_FLAG_UP ? "Running" : "Stop");
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    if (netif_default == netif && netif_is_up(netif)) {
        ret = snprintf_s(tmp, buf_len, (buf_len - 1), " %s", "Default");
        if ((ret <= 0) || ((unsigned int)ret >= buf_len))
            goto out;
        tmp += ret;
        buf_len -= (unsigned int)ret;
    }

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), " %s\n", netif->flags & NETIF_FLAG_LINK_UP ? "Link UP" : "Link Down");
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        goto out;
    tmp += ret;

#if MIB2_STATS
    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "\tRX packets:%u ",
                     netif->mib2_counters.ifinucastpkts + netif->mib2_counters.ifinnucastpkts);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "errors:%u ", netif->mib2_counters.ifinerrors);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "dropped:%u ", netif->mib2_counters.ifindiscards);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "overruns:%u\n", netif->mib2_counters.ifinoverruns);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "\tTX packets:%u ",
                     netif->mib2_counters.ifoutucastpkts + netif->mib2_counters.ifoutnucastpkts);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "errors:%u ", netif->mib2_counters.ifouterrors);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "dropped:%u\n", netif->mib2_counters.ifoutdiscards);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "\tRX bytes:%u ", netif->mib2_counters.ifinoctets);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "TX bytes:%u\n", netif->mib2_counters.ifoutoctets);
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
      goto out;
    tmp += ret;
    buf_len -= (unsigned int)ret;
#endif

out:
    return (int)(tmp - print_buf);
}

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
void lwip_ifconfig_show_internal(void *arg)
{
    struct netif *netif = NULL;
    struct ifconfig_option *ifconfig_cmd = (struct ifconfig_option *)arg;
    int ret;

    if (netif_list == NULL) {
        ret = snprintf_s(ifconfig_cmd->cb_print_buf, PRINT_BUF_LEN - ifconfig_cmd->print_len,
                         ((PRINT_BUF_LEN - ifconfig_cmd->print_len) - 1), "Device not init\n");
        if ((ret > 0) && ((unsigned int)ret < (PRINT_BUF_LEN - ifconfig_cmd->print_len))) {
            ifconfig_cmd->print_len += (unsigned int)ret;
        }
        sys_sem_signal(&ifconfig_cmd->cb_completed);
        return;
    }

    if (ifconfig_cmd->iface[0] == '\0') {
        /* display all netif */
        for (netif = netif_list; netif != NULL; netif = netif->next) {
            ret = print_netif(netif, ifconfig_cmd->cb_print_buf + ifconfig_cmd->print_len,
                              PRINT_BUF_LEN - ifconfig_cmd->print_len);
            ifconfig_cmd->print_len += (unsigned int)ret;
        }
    } else {
        netif = netif_find(ifconfig_cmd->iface);
        if (netif == NULL) {
            ret = snprintf_s(ifconfig_cmd->cb_print_buf + ifconfig_cmd->print_len,
                             (PRINT_BUF_LEN - ifconfig_cmd->print_len),
                             ((PRINT_BUF_LEN - ifconfig_cmd->print_len) - 1), "Device not found\n");
            if ((ret > 0) && ((unsigned int)ret < (PRINT_BUF_LEN - ifconfig_cmd->print_len))) {
                ifconfig_cmd->print_len += (unsigned int)ret;
            }

            sys_sem_signal(&ifconfig_cmd->cb_completed);
            return;
        }

        ret = print_netif(netif, ifconfig_cmd->cb_print_buf + ifconfig_cmd->print_len,
                          PRINT_BUF_LEN - ifconfig_cmd->print_len);
        ifconfig_cmd->print_len += (unsigned int)ret;
    }
    sys_sem_signal(&ifconfig_cmd->cb_completed);
}

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
void lwip_ifconfig_internal(void *arg)
{
    struct ifconfig_option *ifconfig_cmd = NULL;
    struct netif *netif = NULL;
    ip_addr_t ip_addr;
    ip_addr_t netmask;
    ip_addr_t gw;
    unsigned short mtu;
    struct netif *loc_netif = NULL;
    int ret;
    s8_t idx;
    err_t err;

    ifconfig_cmd = (struct ifconfig_option *)arg;
    netif = netif_find(ifconfig_cmd->iface);
    if (netif == NULL) {
        ERR_IFCONFIG_STRING_PUT(ret, "Device not found\n");
        goto out;
    }

    if (ifconfig_cmd->option & IFCONFIG_OPTION_SET_UP) {
        (void)netif_set_up(netif);
        goto out;
    } else if (ifconfig_cmd->option & IFCONFIG_OPTION_SET_DOWN) {
        (void)netif_set_down(netif);
        goto out;
    }

    if ((ifconfig_cmd->option & IFCONFIG_OPTION_SET_IP) ||
        (ifconfig_cmd->option & IFCONFIG_OPTION_SET_NETMASK) ||
        (ifconfig_cmd->option & IFCONFIG_OPTION_SET_HW)) {
        (void)netif_set_down(netif);
    }

    if (ifconfig_cmd->option & IFCONFIG_OPTION_SET_IP) {
        ip_addr_set_val(&ip_addr, &(ifconfig_cmd->ip_addr));
        if (IP_IS_V4_VAL(ifconfig_cmd->ip_addr)) {
            /* check the address is not multicast/broadcast/0/loopback */
            if (ip_addr_ismulticast_val(&ip_addr) || ip_addr_isbroadcast_val(&ip_addr, netif) ||
                ip_addr_isany(&ip_addr) || ip_addr_isloopback(&ip_addr)) {
                ERR_IFCONFIG_STRING_PUT(ret, "Don't set ip as a multicast/broadcast/0/loopback address!\n");
                goto out;
            }

            /* reset gateway if new and previous ipaddr not in same net */
            if (!ip_addr_netcmp_val(&ip_addr, &netif->ip_addr, ip_2_ip4(&netif->netmask))) {
                ip_addr_set_zero(&netif->gw);
                if (netif == netif_default) {
                    (void)netif_set_default(NULL);
                }
            }

            /* lwip disallow two netif sit in same net at the same time */
            loc_netif = netif_list;
            while (loc_netif != NULL) {
                if (loc_netif == netif) {
                    loc_netif = loc_netif->next;
                    continue;
                }
                if (IP_IS_V4_VAL(ifconfig_cmd->ip_addr) && ip_addr_cmp(&netif->netmask, &loc_netif->netmask) &&
                    ip_addr_netcmp_val(&loc_netif->ip_addr, &ip_addr, ip_2_ip4(&netif->netmask))) {
                    ERR_IFCONFIG_STRING_PUT(ret, "Duplicate network!\n");
                    goto out;
                }
                loc_netif = loc_netif->next;
            }

#if LWIP_DHCP
            if (netif_dhcp_data(netif) && netif_dhcp_data(netif)->state != DHCP_STATE_OFF) {
                (void)netif_dhcp_off(netif);
            }
#endif
            netif_set_ipaddr(netif, ip_2_ip4(&ip_addr));
        } else if (IP_IS_V6_VAL(ifconfig_cmd->ip_addr)) {
            idx = -1;
            err = netif_add_ip6_address(netif, ip_2_ip6(&ip_addr), &idx);
            if (err != ERR_OK || idx == -1) {
                ERR_IFCONFIG_STRING_PUT(ret, "The IPv6 has reached the Global address limit, "
                                             "you should delete one address before add!\n");
                goto out;
            }
        }
    }

    if (ifconfig_cmd->option & IFCONFIG_OPTION_DEL_IP) {
        (void)netif_do_rmv_ipv6_addr(netif, &ifconfig_cmd->ip_addr);
    }

    if (ifconfig_cmd->option & IFCONFIG_OPTION_SET_NETMASK) {
        ip_addr_set_val(&netmask, &(ifconfig_cmd->netmask));
        /* check data valid */
        if (!ip_addr_netmask_valid(ip_2_ip4(&netmask))) {
            ERR_IFCONFIG_STRING_PUT(ret, "ifconfig: netmask is invalid!\n");
            goto out;
        }

#if LWIP_DHCP
        if (netif_dhcp_data(netif) && netif_dhcp_data(netif)->state != DHCP_STATE_OFF) {
            (void)netif_dhcp_off(netif);
        }
#endif
        if (netif_ip4_netmask(netif)->addr != ip_2_ip4(&netmask)->addr) {
            /* lwip disallow two netif sit in same net at the same time */
            loc_netif = netif_list;
            while (loc_netif != NULL) {
                if (loc_netif == netif) {
                    loc_netif = loc_netif->next;
                    continue;
                }
                if (ip_addr_cmp(&loc_netif->netmask, &netmask) &&
                    ip_addr_netcmp(&loc_netif->ip_addr, &netif->ip_addr, ip_2_ip4(&netmask))) {
                    ERR_IFCONFIG_STRING_PUT(ret, "Duplicate network!\n");
                    goto out;
                }
                loc_netif = loc_netif->next;
            }
            netif_set_netmask(netif, ip_2_ip4(&netmask));
            /* check if gateway still reachable */
            if (!ip_addr_netcmp(&netif->gw, &netif->ip_addr, ip_2_ip4(&netmask))) {
                ip_addr_set_zero(&(netif->gw));
                if (netif == netif_default) {
                    (void)netif_set_default(NULL);
                }
            }
        }
    }

    if ((ifconfig_cmd->option & IFCONFIG_OPTION_SET_HW) &&
        netif_set_hwaddr(netif, ifconfig_cmd->ethaddr, NETIF_MAX_HWADDR_LEN) != ERR_OK) {
        ERR_IFCONFIG_STRING_PUT(ret, "Failed to update the hwaddr of the device!\n");
        (void)netif_set_up(netif);
        goto out;
    }

    if ((ifconfig_cmd->option & IFCONFIG_OPTION_SET_IP) ||
        (ifconfig_cmd->option & IFCONFIG_OPTION_SET_NETMASK) ||
        (ifconfig_cmd->option & IFCONFIG_OPTION_SET_HW)) {
        (void)netif_set_up(netif);
    }

    if (ifconfig_cmd->option & IFCONFIG_OPTION_SET_GW) {
        ip_addr_set_val(&gw, &ifconfig_cmd->gw);

        /* check the address multicast/0/loopback */
        if (ip_addr_ismulticast_val(&gw) || ip_addr_isbroadcast_val(&gw, netif) ||
            ip_addr_isany(&gw) || ip_addr_isloopback(&gw)) {
            ERR_IFCONFIG_STRING_PUT(ret, "Don't set gateway as a multicast/broadcast/0/loopback address!\n");
            goto out;
        }

        /* check if reachable */
        if (!ip_addr_netcmp_val(&gw, &netif->ip_addr, ip_2_ip4(&netif->netmask))) {
            ERR_IFCONFIG_STRING_PUT(ret, "The address is unreachable!\n");
            goto out;
        }

        if (netif_default != netif) {
            ip_addr_set_zero(&netif->gw);
            (void)netif_set_default(netif);
        }

#if LWIP_DHCP
        if (netif_dhcp_data(netif) && netif_dhcp_data(netif)->state != DHCP_STATE_OFF) {
            (void)netif_dhcp_off(netif);
        }
#endif
        netif_set_gw(netif, ip_2_ip4(&gw));
    }

    if (ifconfig_cmd->option & IFCONFIG_OPTION_SET_MTU) {
        mtu = ifconfig_cmd->mtu;
        if (netif_set_mtu(netif, mtu) != ERR_OK) {
            ERR_IFCONFIG_STRING_PUT(ret, "Invalid MTU\n");
        }
    }
out:
    sys_sem_signal(&ifconfig_cmd->cb_completed);
}


void lwip_printsize(size_t size)
{
    static const char *SIZES[] = {"B", "KB", "MB", "GB"};
    size_t divis = 0;
    size_t rem = 0;

    while ((size >= 1024) && (divis < ((sizeof(SIZES) / sizeof(char *)) - 1))) {
        rem = (size % 1024);
        divis++;
        size /= 1024;
    }

    PRINTK("(%.1f %s) \r\n", (float)size + (float)rem / 1024.0, SIZES[divis]);
}

LWIP_STATIC void lwip_ifconfig_usage(const char *cmd)
{
    PRINTK("Usage:"\
         "\n%s [-a] "\
         "\n[interface]"\
         "\n[interface ipaddr] <netmask mask> <gateway gw>"\
         "\n[interface inet6 add|del ipaddr]"\
         "\n[interface hw ether MAC]"\
         "\n[interface mtu NN]"\
         "\n[interface up|down]\n",
           cmd);
}

u32_t lwip_ifconfig(int argc, const char **argv)
{
    int i;
    static struct ifconfig_option ifconfig_cmd;
    err_t ret;

#if LWIP_STATS
    u32_t stat_err_cnt;
    u32_t stat_drop_cnt;
    u32_t stat_rx_or_tx_cnt;
    u32_t stat_rx_or_tx_bytes;
#endif

#if LWIP_ARP
    u32_t retval;
    struct netif *netiftmp = NULL;
#if LWIP_ENABLE_IP_CONFLICT_SIGNAL
    u32_t old_ip4addr;
    err_t        err;
    extern sys_sem_t ip_conflict_detect;
    extern u32_t is_ip_conflict_signal;
#endif /* LWIP_ENABLE_IP_CONFLICT_SIGNAL */
#endif /* LWIP_ARP */
#if LWIP_IPV6
    extern sys_sem_t dup_addr_detect;
    extern u32_t is_dup_detect_initialized;
#endif
    if (!tcpip_init_finish) {
        PRINTK("%s: tcpip_init have not been called\n", __FUNCTION__);
        return 2;
    }
    /* To support "ifconfig -a" command
         RX packets:XXXX errors:X dropped:X overruns:X bytes:XXXX (Human readable format)
         TX packets:XXXX errors:X dropped:X overruns:X bytes:XXXX (Human readable format)

         Below is assumed for 'overrun' stat.
         Linux Kernel:
                RX: FIFO overrun
                    Data structure: net_device->stats->rx_fifo_errors
                    Flag which is marked when FIFO overrun: ENRSR_FO

                Function: ei_receive->ENRSR_FO

                TX: A "FIFO underrun" occurred during transmit.
                    Data structure: net_device->stats->tx_fifo_errors
                    Flag which is marked when FIFO underrun: ENTSR_FU

                Function: ei_tx_intr->ENTSR_FU

        LWIP:
            So in our case,
            while receiving a packet RX case, if the buffer is full (trypost - it is sys_mbox_trypost)
            the error will be returned, we can consider that an overflow has happend.
            So this can be RX overrun.

            But while transmitting a packet TX case, underrun cannot happen because it block on the
            message Q if it is full (NOT trypost - it is sys_mbox_post). So TX overrun is always 0.
    */
    if (argc) {
        if (strcmp("-a", argv[0]) == 0) {
#if LWIP_STATS
            stat_rx_or_tx_cnt = lwip_stats.ip.recv;
            stat_err_cnt = (u32_t)(lwip_stats.ip.ip_rx_err +
                                   lwip_stats.ip.lenerr +
                                   lwip_stats.ip.chkerr +
                                   lwip_stats.ip.opterr +
                                   lwip_stats.ip.proterr);
            stat_drop_cnt = (u32_t)(lwip_stats.ip.drop + lwip_stats.link.link_rx_drop);
            stat_rx_or_tx_bytes = lwip_stats.ip.ip_rx_bytes;

            PRINTK("%18s:%u\t errors:%u\t ip dropped:%u\t link dropped:%u\t overrun:%d\t bytes:%u ",
                   "RX packets",
                   stat_rx_or_tx_cnt,
                   stat_err_cnt,
                   stat_drop_cnt,
                   lwip_stats.link.link_rx_drop,
                   lwip_stats.ip.link_rx_overrun,
                   stat_rx_or_tx_bytes);

            /* Print in Human readable format of the incoming bytes */
            lwip_printsize(lwip_stats.ip.ip_rx_bytes);
#if IP6_STATS
            stat_rx_or_tx_cnt = lwip_stats.ip6.recv;
            stat_err_cnt = (u32_t)(lwip_stats.ip6.ip_rx_err +
                                   lwip_stats.ip6.lenerr +
                                   lwip_stats.ip6.chkerr +
                                   lwip_stats.ip6.opterr +
                                   lwip_stats.ip6.proterr);
            stat_drop_cnt = lwip_stats.ip6.drop;
            stat_rx_or_tx_bytes = lwip_stats.ip6.ip_rx_bytes;

            PRINTK("%18s:%u\t errors:%u\t dropped:%u\t overrun:%d\t bytes:%u ",
                   "RX packets(ip6)",
                   stat_rx_or_tx_cnt,
                   stat_err_cnt,
                   stat_drop_cnt,
                   lwip_stats.ip.link_rx_overrun,
                   stat_rx_or_tx_bytes);

            /* Print in Human readable format of the incoming bytes */
            lwip_printsize(lwip_stats.ip6.ip_rx_bytes);
#endif
            stat_rx_or_tx_cnt = (u32_t)(lwip_stats.ip.fw + lwip_stats.ip.xmit);
            stat_err_cnt = (u32_t)(lwip_stats.ip.rterr + lwip_stats.ip.ip_tx_err);
            /* IP layer drop stat param is not maintained, failure at IP is considered in 'errors' stat */
            stat_drop_cnt = lwip_stats.link.link_tx_drop;
            stat_rx_or_tx_bytes = lwip_stats.ip.ip_tx_bytes;

            PRINTK("%18s:%u\t errors:%u\t link dropped:%u\t overrun:0\t bytes:%u",
                   "TX packets",
                   stat_rx_or_tx_cnt,
                   stat_err_cnt,
                   stat_drop_cnt,
                   stat_rx_or_tx_bytes);

            /* Print in Human readable format of the outgoing bytes */
            lwip_printsize(lwip_stats.ip.ip_tx_bytes);

            stat_rx_or_tx_cnt = (u32_t)(lwip_stats.ip6.fw + lwip_stats.ip6.xmit);
            stat_err_cnt = (u32_t)(lwip_stats.ip6.rterr + lwip_stats.ip6.ip_tx_err);
            stat_rx_or_tx_bytes = lwip_stats.ip6.ip_tx_bytes;

            PRINTK("%18s:%u\t errors:%u\t overrun:0\t bytes:%u",
                   "TX packets(ip6)",
                   stat_rx_or_tx_cnt,
                   stat_err_cnt,
                   stat_rx_or_tx_bytes);

            /* Print in Human readable format of the outgoing bytes */
            lwip_printsize(lwip_stats.ip6.ip_tx_bytes);
#endif /* LWIP_STATS */
            return 0;
        }
    }

    (void)memset_s(&ifconfig_cmd, sizeof(ifconfig_cmd), 0, sizeof(ifconfig_cmd));
    if (sys_sem_new(&ifconfig_cmd.cb_completed, 0) != ERR_OK) {
        PRINTK("%s: sys_sem_new fail\n", __FUNCTION__);
        return 1;
    }

    i = 0;
    /* Get the interface */
    if (argc > 0) {
        if (strlen(argv[i]) < IFNAMSIZ) {
            if (strncpy_s(ifconfig_cmd.iface, IFNAMSIZ, argv[i], (strlen(argv[i]))) != EOK) {
                sys_sem_free(&ifconfig_cmd.cb_completed);
                PRINTK("ifconfig : strncpy_s error\n");
                return 1;
            }
            ifconfig_cmd.iface[IFNAMSIZ - 1] = '\0';
        } else {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            PRINTK("ifconfig : interface name is too big\n");
            return 1;
        }
        i++;
        argc--;
        if (argc == 0) {
            /* no more arguments, show the interface state. */
            ret = tcpip_callback(lwip_ifconfig_show_internal, &ifconfig_cmd);
            if (ret != ERR_OK) {
                sys_sem_free(&ifconfig_cmd.cb_completed);
                PRINTK("ifconfig : internal error, l:%d err:%d\n", __LINE__, ret);
                return 1;
            }
            (void)sys_arch_sem_wait(&ifconfig_cmd.cb_completed, 0);
            sys_sem_free(&ifconfig_cmd.cb_completed);
            ifconfig_cmd.cb_print_buf[PRINT_BUF_LEN - 1] = '\0';
            PRINTK("%s", ifconfig_cmd.cb_print_buf);
            return 0;
        }
    } else {
        /* no more arguments, show all the interface state. */
        ret = tcpip_callback(lwip_ifconfig_show_internal, &ifconfig_cmd);
        if (ret != ERR_OK) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            PRINTK("ifconfig : internal error, l:%d err:%d\n", __LINE__, ret);
            return 1;
        }
        (void)sys_arch_sem_wait(&ifconfig_cmd.cb_completed, 0);
        sys_sem_free(&ifconfig_cmd.cb_completed);
        ifconfig_cmd.cb_print_buf[PRINT_BUF_LEN - 1] = '\0';
        PRINTK("%s", ifconfig_cmd.cb_print_buf);

        return 0;
    }

    /* ifup/ifdown */
    if (strcmp("up", argv[i]) == 0) {
        ifconfig_cmd.option |= IFCONFIG_OPTION_SET_UP;
        /* setup the interface, other arguments is ignored. */
        ret = tcpip_callback(lwip_ifconfig_internal, &ifconfig_cmd);
        if (ret != ERR_OK) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            PRINTK("ifconfig : internal error, l:%d err:%d\n", __LINE__, ret);
            return 1;
        }
        (void)sys_arch_sem_wait(&ifconfig_cmd.cb_completed, 0);
        sys_sem_free(&ifconfig_cmd.cb_completed);
        ifconfig_cmd.cb_print_buf[PRINT_BUF_LEN - 1] = '\0';
        PRINTK("%s", ifconfig_cmd.cb_print_buf);
        return 0;
    } else if (strcmp("down", argv[i]) == 0) {
        ifconfig_cmd.option |= IFCONFIG_OPTION_SET_DOWN;
        /* setdown the interface, other arguments is ignored. */
        ret = tcpip_callback(lwip_ifconfig_internal, &ifconfig_cmd);
        if (ret != ERR_OK) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            PRINTK("ifconfig : internal error, l:%d err:%d\n", __LINE__, ret);
            return 1;
        }
        (void)sys_arch_sem_wait(&ifconfig_cmd.cb_completed, 0);
        sys_sem_free(&ifconfig_cmd.cb_completed);
        ifconfig_cmd.cb_print_buf[PRINT_BUF_LEN - 1] = '\0';
        PRINTK("%s", ifconfig_cmd.cb_print_buf);
        return 0;
    }
    /* check if set the ip address. */
#if LWIP_ARP
    netiftmp = netifapi_netif_find_by_name(ifconfig_cmd.iface);
    if (netiftmp == NULL) {
        sys_sem_free(&ifconfig_cmd.cb_completed);
        PRINTK("ifconfig : Interface %s not found\n", ifconfig_cmd.iface);
        return 1;
    }
#if LWIP_ENABLE_IP_CONFLICT_SIGNAL
    old_ip4addr = ipaddr_addr(ipaddr_ntoa(&netiftmp->ip_addr));
#endif /* LWIP_ENABLE_IP_CONFLICT_SIGNAL */
#endif /* LWIP_ARP */
    if (!strcmp(argv[i], "inet") || ip4addr_aton(argv[i], ip_2_ip4(&ifconfig_cmd.ip_addr))) {
        if (!strcmp(argv[i], "inet")) {
            if (argc <= 1) {
                sys_sem_free(&ifconfig_cmd.cb_completed);
                goto ifconfig_error;
            }

            if (!ip4addr_aton(argv[i + 1], ip_2_ip4(&ifconfig_cmd.ip_addr))) {
                sys_sem_free(&ifconfig_cmd.cb_completed);
                PRINTK("ifconfig : Invalid IPv4 Address\n");
                return 1;
            }
            argc--;
            i++;
        }
        IP_SET_TYPE_VAL((ifconfig_cmd.ip_addr), IPADDR_TYPE_V4);
#if LWIP_ARP
        if (!ip_addr_cmp(&ifconfig_cmd.ip_addr, &netiftmp->ip_addr)) {
            ifconfig_cmd.option |= IFCONFIG_OPTION_SET_IP;
        }
#else
        ifconfig_cmd.option |= IFCONFIG_OPTION_SET_IP;
#endif /* LWIP_ARP */
        argc--;
        i++;
    } else if (!strcmp(argv[i], "inet6")) {
        if (argc < 3) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            goto ifconfig_error;
        }
        if (strcmp(argv[i + 1], "add") && strcmp(argv[i + 1], "del")) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            goto ifconfig_error;
        }

        if (!ip6addr_aton(argv[i + 2], ip_2_ip6(&ifconfig_cmd.ip_addr))) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            PRINTK("ifconfig : Invalid IPv6 Address\n");
            return 1;
        }

        IP_SET_TYPE_VAL((ifconfig_cmd.ip_addr), IPADDR_TYPE_V6);
        ifconfig_cmd.option |= (!strcmp(argv[i + 1], "add") ? IFCONFIG_OPTION_SET_IP : IFCONFIG_OPTION_DEL_IP);
        argc -= 3;
        i += 3;
    }

    if (ifconfig_cmd.option & IFCONFIG_OPTION_DEL_IP) {
        if (argc != 0) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            goto ifconfig_error;
        }
    }

    while (argc > 0) {
        if (strcmp("netmask", argv[i]) == 0 && (argc > 1) && (ipaddr_addr(argv[i + 1]) != IPADDR_NONE)) {
            /* if set netmask */
            ip_addr_set_ip4_u32_val((ifconfig_cmd.netmask), ipaddr_addr(argv[i + 1]));
            ifconfig_cmd.option |= IFCONFIG_OPTION_SET_NETMASK;
            i += 2;
            argc -= 2;
        } else if (strcmp("gateway", argv[i]) == 0 && (argc > 1) && (ipaddr_addr(argv[i + 1]) != IPADDR_NONE)) {
            /* if set gateway */
            ip_addr_set_ip4_u32_val((ifconfig_cmd.gw), ipaddr_addr(argv[i + 1]));
            ifconfig_cmd.option |= IFCONFIG_OPTION_SET_GW;
            i += 2;
            argc -= 2;
        } else if (strcmp("hw", argv[i]) == 0 && argc > 2 && strcmp("ether", argv[i + 1]) == 0) {
            /* if set HWaddr */
            char *digit = NULL;
            u32_t macaddrlen = strlen(argv[i + 2]) + 1;
            char tmpStr[MAX_MACADDR_STRING_LENGTH];
            char *tmpStr1 = NULL;
            char *saveptr = NULL;
            int j;

            if (macaddrlen != MAX_MACADDR_STRING_LENGTH) {
                sys_sem_free(&ifconfig_cmd.cb_completed);
                PRINTK("ifconfig : wrong MAC address format\n");
                return 1;
            }

            if (strncpy_s(tmpStr, MAX_MACADDR_STRING_LENGTH, argv[i + 2], macaddrlen - 1) != 0) {
                sys_sem_free(&ifconfig_cmd.cb_completed);
                PRINTK("ifconfig : wrong MAC address\n");
                return 1;
            }
            for (j = 0, tmpStr1 = tmpStr; j < 6; j++, tmpStr1 = NULL) {
                digit = strtok_r(tmpStr1, ":", &saveptr);
                if ((digit == NULL) || (strlen(digit) > 2)) {
                    sys_sem_free(&ifconfig_cmd.cb_completed);
                    PRINTK("ifconfig : wrong MAC address format\n");
                    return 1;
                }
                CONVERT_STRING_TO_HEX(digit, ifconfig_cmd.ethaddr[j]);
            }
            ifconfig_cmd.option |= IFCONFIG_OPTION_SET_HW;
            i += 3;
            argc -= 3;
        } else if (!strcmp("mtu", argv[i]) && (argc > 1)) {
            /* if set mtu */
            if ((atoi(argv[i + 1]) < 0) || (atoi(argv[i + 1]) > 0xFFFF)) {
                sys_sem_free(&ifconfig_cmd.cb_completed);
                PRINTK("\nifconfig: Invalid argument for mtu\n");
                goto ifconfig_error;
            }

            ifconfig_cmd.mtu = (u16_t)(atoi(argv[i + 1]));
            ifconfig_cmd.option |= IFCONFIG_OPTION_SET_MTU;
            i += 2;
            argc -= 2;
        } else {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            goto ifconfig_error;
        }
    }

#if LWIP_ARP && LWIP_ENABLE_IP_CONFLICT_SIGNAL
    if ((ifconfig_cmd.option & IFCONFIG_OPTION_SET_IP) && IP_IS_V4_VAL((ifconfig_cmd.ip_addr))) {
      /* Create the semaphore for ip conflict detection. */
      if (sys_sem_new(&ip_conflict_detect, 0) != ERR_OK) {
        sys_sem_free(&ifconfig_cmd.cb_completed);
        PRINTK("ifconfig: internal error\n");
        return 1;
      }
      is_ip_conflict_signal = 1;
    }
#endif /* LWIP_ARP && LWIP_ENABLE_IP_CONFLICT_SIGNAL */

#if LWIP_IPV6
    if ((ifconfig_cmd.option & IFCONFIG_OPTION_SET_IP) && IP_IS_V6_VAL((ifconfig_cmd.ip_addr))) {
        /* Create the semaphore for duplicate address detection. */
        if (sys_sem_new(&dup_addr_detect, 0) != ERR_OK) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            PRINTK("ifconfig: internal error\n");
            return 1;
        }
        is_dup_detect_initialized = 1;
    }
#endif /* LWIP_IPV6 */

    ret = tcpip_callback(lwip_ifconfig_internal, &ifconfig_cmd);
    if (ret != ERR_OK) {
        sys_sem_free(&ifconfig_cmd.cb_completed);
#if LWIP_ARP && LWIP_ENABLE_IP_CONFLICT_SIGNAL
        if ((ifconfig_cmd.option & IFCONFIG_OPTION_SET_IP) && IP_IS_V4_VAL((ifconfig_cmd.ip_addr))) {
          is_ip_conflict_signal = 0;
          sys_sem_free(&ip_conflict_detect);
        }
#endif /* LWIP_ARP && LWIP_ENABLE_IP_CONFLICT_SIGNAL */

#if LWIP_IPV6
        if ((ifconfig_cmd.option & IFCONFIG_OPTION_SET_IP) && IP_IS_V6_VAL((ifconfig_cmd.ip_addr))) {
            is_dup_detect_initialized = 0;
            sys_sem_free(&dup_addr_detect);
        }
#endif /* LWIP_IPV6 */

        PRINTK("%s : tcpip_callback failed in line %d : errnu %d", __FUNCTION__, __LINE__, ret);
        return 1;
    }
    (void)sys_arch_sem_wait(&ifconfig_cmd.cb_completed, 0);
    ifconfig_cmd.cb_print_buf[PRINT_BUF_LEN - 1] = '\0';
    PRINTK("%s", ifconfig_cmd.cb_print_buf);
#if LWIP_ARP && LWIP_ENABLE_IP_CONFLICT_SIGNAL
    /* Pend 2 seconds for waiting the arp reply if the ip is already in use.*/
    if ((ifconfig_cmd.option & IFCONFIG_OPTION_SET_IP) && IP_IS_V4_VAL((ifconfig_cmd.ip_addr))) {
      err = (err_t)sys_arch_sem_wait(&ip_conflict_detect, DUP_ARP_DETECT_TIME);
      is_ip_conflict_signal = 0;
      sys_sem_free(&ip_conflict_detect);
      if (err < 0) {
        /* The result neither conflict nor timeout. */
        PRINT_ERR("ifconfig: internal error\n");
        sys_sem_free(&ifconfig_cmd.cb_completed);
        return 1;
      } else if (err < DUP_ARP_DETECT_TIME) {
        /* Duplicate use of new ip, restore it to the old one. */
        PRINT_ERR("ifconfig: ip conflict!\n");
        ip_addr_set_ip4_u32_val(ifconfig_cmd.ip_addr, old_ip4addr);
        ret = tcpip_callback(lwip_ifconfig_internal, &ifconfig_cmd);
        if (ret != ERR_OK) {
          sys_sem_free(&ifconfig_cmd.cb_completed);
          PRINTK("%s : tcpip_callback failed in line %d : errnu %d", __FUNCTION__, __LINE__, ret);
          return 1;
        }
        (void)sys_arch_sem_wait(&ifconfig_cmd.cb_completed, 0);
        sys_sem_free(&ifconfig_cmd.cb_completed);
        ifconfig_cmd.cb_print_buf[PRINT_BUF_LEN - 1] = '\0';
        PRINTK("%s", ifconfig_cmd.cb_print_buf);
        return 1;
      }
    }
#endif /* LWIP_ARP && LWIP_ENABLE_IP_CONFLICT_SIGNAL */
#if LWIP_IPV6
    if ((ifconfig_cmd.option & IFCONFIG_OPTION_SET_IP) && IP_IS_V6_VAL(ifconfig_cmd.ip_addr)) {
        /* Pend 2 seconds for waiting the arp reply if the ip is already in use.*/
        retval = sys_arch_sem_wait(&dup_addr_detect, DUP_ARP_DETECT_TIME);
        is_dup_detect_initialized = 0;
        sys_sem_free(&dup_addr_detect);
        if (retval == SYS_ARCH_ERROR) {
            sys_sem_free(&ifconfig_cmd.cb_completed);
            /* The result neither conflict nor timeout. */
            PRINT_ERR("ifconfig: internal error\n");
            return 1;
        } else if (retval < DUP_ARP_DETECT_TIME) {
            /* Duplicate use of new ip, restore it to the old one. */
            struct netif *netif = NULL;
            PRINT_ERR("ifconfig: IP conflict!\n");
            netif = netifapi_netif_find_by_name(ifconfig_cmd.iface);
            i = netif_get_ip6_addr_match(netif, &ifconfig_cmd.ip_addr.u_addr.ip6);
            if (i >= 0) {
                netif->ip6_addr_state[i] = IP6_ADDR_INVALID;
            }

            sys_sem_free(&ifconfig_cmd.cb_completed);
            ifconfig_cmd.cb_print_buf[PRINT_BUF_LEN - 1] = '\0';
            PRINTK("%s", ifconfig_cmd.cb_print_buf);
            return 1;
        }
    }
#endif /* LWIP_IPV6 */
    sys_sem_free(&ifconfig_cmd.cb_completed);
    return 0;
ifconfig_error:
    lwip_ifconfig_usage("ifconfig");
    return 1;
}

#ifdef LOSCFG_SHELL
SHELLCMD_ENTRY(ifconfig_shellcmd, CMD_TYPE_EX, "ifconfig", XARGS, (CmdCallBackFunc)lwip_ifconfig);
#endif /* LOSCFG_SHELL */
/* add arp entry to arp cache */
#define ARP_OPTION_ADD      1
/* delete arp entry to arp cache */
#define ARP_OPTION_DEL      2
/* print all arp entry in arp cache */
#define ARP_OPTION_SHOW     3

struct arp_option {
    /* see the ARP_OPTION_ above */
    int option;
    /* descriptive abbreviation of network interface */
    char iface[IFNAMSIZ];
    /* ip addr */
    unsigned int ipaddr;
    /* hw addr */
    unsigned char ethaddr[6];
    /* when using telnet, printf to the telnet socket will result in system  */
    /* deadlock.so don't do it.cahe the data to prinf to a buf, and when     */
    /* callback returns, then printf the data out to the telnet socket       */
    sys_sem_t cb_completed;
    char cb_print_buf[PRINT_BUF_LEN];
    int print_buf_len;
};

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
void lwip_arp_show_internal(struct netif *netif, char *printf_buf, unsigned int buf_len)
{
    u8_t state, i;
    int ret;
    char *tmp = printf_buf;
    ret = snprintf_s(tmp, buf_len, (buf_len - 1), "%-24s%-24s%-12s%-12s\n", "Address", "HWaddress", "Iface", "Type");
    if ((ret <= 0) || ((unsigned int)ret >= buf_len))
        return;
    tmp += ret;
    buf_len -= (unsigned int)ret;

    if (netif != NULL) {
        for (i = 0; i < ARP_TABLE_SIZE; ++i) {
            state = arp_table[i].state;
            if (((state == ETHARP_STATE_STABLE)
                 #if ETHARP_SUPPORT_STATIC_ENTRIES
                 || (state == ETHARP_STATE_STATIC)
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */
                ) && arp_table[i].netif) {

                if (strcmp(netif_get_name(netif), netif_get_name(arp_table[i].netif)) != 0) {
                    continue;
                }

                ret = snprintf_s(tmp, buf_len, (buf_len - 1), "%-24s%02X:%02X:%02X:%02X:%02X:%02X       %s        %s\n",
                                 ip4addr_ntoa(&arp_table[i].ipaddr),
                                 arp_table[i].ethaddr.addr[0], arp_table[i].ethaddr.addr[1],
                                 arp_table[i].ethaddr.addr[2], arp_table[i].ethaddr.addr[3],
                                 arp_table[i].ethaddr.addr[4], arp_table[i].ethaddr.addr[5],
                                 netif_get_name(netif),
#if ETHARP_SUPPORT_STATIC_ENTRIES
                                 ((state == ETHARP_STATE_STATIC) ? "static" : "dynamic")
#else
                    "dynamic"
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */
                );
                if ((ret <= 0) || ((unsigned int)ret >= buf_len))
                    return;
                tmp += ret;
                buf_len -= (unsigned int)ret;
            }
        }
    } else {
        for (i = 0; i < ARP_TABLE_SIZE; ++i) {
            state = arp_table[i].state;
            if (((state == ETHARP_STATE_STABLE)
                 #if ETHARP_SUPPORT_STATIC_ENTRIES
                 || (state == ETHARP_STATE_STATIC)
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */
                ) && arp_table[i].netif) {
                ret = snprintf_s(tmp, buf_len, (buf_len - 1), "%-24s%02X:%02X:%02X:%02X:%02X:%02X       %s        %s\n",
                                 ip4addr_ntoa(&arp_table[i].ipaddr),
                                 arp_table[i].ethaddr.addr[0], arp_table[i].ethaddr.addr[1],
                                 arp_table[i].ethaddr.addr[2], arp_table[i].ethaddr.addr[3],
                                 arp_table[i].ethaddr.addr[4], arp_table[i].ethaddr.addr[5],
                                 netif_get_name(arp_table[i].netif),
#if ETHARP_SUPPORT_STATIC_ENTRIES
                                 ((state == ETHARP_STATE_STATIC) ? "static" : "dynamic")
#else
                    "dynamic"
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */
                );
                if ((ret <= 0) || ((unsigned int)ret >= buf_len))
                    return;
                tmp += ret;
                buf_len -= (unsigned int)ret;
            }
        }
    }
}

#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
void lwip_arp_internal(void *arg)
{
#if LWIP_IPV4
    struct arp_option *arp_cmd = (struct arp_option *)arg;
    struct netif *netif = NULL;
    struct eth_addr ethaddr;
    ip4_addr_t ipaddr;
    err_t ret = 0;
    int type = 0;

    if (arp_cmd->iface[0] == 'd' && arp_cmd->iface[1] == 'e') {
        netif = NULL;
    } else {
        /* find the specified netif by it's name */
        netif = netif_find(arp_cmd->iface);
        if (netif == NULL) {
            (void)snprintf_s(arp_cmd->cb_print_buf, PRINT_BUF_LEN, (PRINT_BUF_LEN - 1), "No such device\n");
            goto out;
        }
    }

    type = arp_cmd->option;
    switch (type) {
        case ARP_OPTION_SHOW:
            if (netif != NULL) {
                lwip_arp_show_internal(netif, arp_cmd->cb_print_buf, PRINT_BUF_LEN);
            } else {
                lwip_arp_show_internal(NULL, arp_cmd->cb_print_buf, PRINT_BUF_LEN);
            }
            break;

        case ARP_OPTION_ADD:
#if ETHARP_SUPPORT_STATIC_ENTRIES
            ipaddr.addr = arp_cmd->ipaddr;
            (void)memcpy_s(ethaddr.addr, sizeof(ethaddr.addr), arp_cmd->ethaddr, 6);
            if (netif != NULL) {
                if (ip4_addr_netcmp(&ipaddr, ip_2_ip4(&(netif->ip_addr)), ip_2_ip4(&(netif->netmask)))) {
                    ret = etharp_update_arp_entry(netif, &ipaddr, &ethaddr,
                                                  ETHARP_FLAG_TRY_HARD | ETHARP_FLAG_STATIC_ENTRY);
                } else {
                    ret = ERR_RTE;
                }
            } else {
                ret = etharp_add_static_entry(&ipaddr, &ethaddr);
            }
#else
            ret = ERR_ARG;
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */
            break;

        case ARP_OPTION_DEL:
            ipaddr.addr = arp_cmd->ipaddr;
            (void)memcpy_s(ethaddr.addr, sizeof(ethaddr.addr), arp_cmd->ethaddr, 6);
            if (netif != NULL) {
                ret = etharp_delete_arp_entry(netif, &ipaddr);
            } else {
                for (netif = netif_list; netif != NULL; netif = netif->next) {
                    ret = etharp_delete_arp_entry(netif, &ipaddr);
                    if (ret == ERR_OK) {
                        /*only can del success one time*/
                        break;
                    }
                }
            }
            break;

        default:
            (void)snprintf_s(arp_cmd->cb_print_buf, PRINT_BUF_LEN, (PRINT_BUF_LEN - 1), "Error\n");
            goto out;
    }

out:
    if (type == ARP_OPTION_ADD || type == ARP_OPTION_DEL) {
        if (ret == ERR_MEM) {
            (void)snprintf_s(arp_cmd->cb_print_buf, PRINT_BUF_LEN, (PRINT_BUF_LEN - 1), "Out of memory error\n");
        } else if (ret == ERR_ARG) {
            (void)snprintf_s(arp_cmd->cb_print_buf, PRINT_BUF_LEN, (PRINT_BUF_LEN - 1), "Illegal argument\n");
        } else if (ret == ERR_RTE) {
            (void)snprintf_s(arp_cmd->cb_print_buf, PRINT_BUF_LEN, (PRINT_BUF_LEN - 1), "Network is unreachable\n");
        } else {
            (void)snprintf_s(arp_cmd->cb_print_buf, PRINT_BUF_LEN, (PRINT_BUF_LEN - 1), "Successed\n");
        }
    }
#endif

    sys_sem_signal(&arp_cmd->cb_completed);
}


LWIP_STATIC void lwip_arp_usage(const char *cmd)
{
    PRINTK("Usage:"\
         "\n%s"
           "\n%s [-i IF] -s IPADDR HWADDR"\
         "\n%s [-i IF] -d IPADDR\n",
           cmd, cmd, cmd);
}

u32_t lwip_arp(int argc, const char **argv)
{
    int i;
    struct arp_option arp_cmd;
    err_t ret;
    size_t interface_len = 0;

    (void)memset_s(&arp_cmd, sizeof(struct arp_option), 0, sizeof(struct arp_option));
    if (!tcpip_init_finish) {
        PRINTK("%s: tcpip_init have not been called\n", __FUNCTION__);
        return LOS_NOK;
    }

    arp_cmd.iface[0] = 'd';
    arp_cmd.iface[1] = 'e';
    arp_cmd.iface[2] = '0';
    arp_cmd.option = ARP_OPTION_SHOW;
    arp_cmd.print_buf_len = 0;
    if (sys_sem_new(&arp_cmd.cb_completed, 0) != ERR_OK) {
        PRINTK("%s: sys_sem_new fail\n", __FUNCTION__);
        return 1;
    }

    i = 0;
    while (argc > 0) {
        if (strcmp("-i", argv[i]) == 0 && (argc > 1)) {
            /* get the network interface's name */
            interface_len = strlen(argv[i + 1]);
            if (interface_len < IFNAMSIZ) {
                if (strncmp(argv[i + 1], "lo", (sizeof("lo") - 1)) == 0) {
                    PRINTK("Illegal operation\n");
                    goto arp_error;
                }
                if (strncpy_s(arp_cmd.iface, IFNAMSIZ, argv[i + 1], interface_len) != EOK) {
                    PRINTK("strncpy_s error\n");
                    goto arp_error;
                }
                arp_cmd.iface[interface_len] = '\0';
            } else {
                PRINTK("Iface name is big \n");
                goto arp_error;
            }
            i += 2;
            argc -= 2;
        } else if (strcmp("-d", argv[i]) == 0 && (argc > 1)) {
            /* arp delete */
            arp_cmd.option = ARP_OPTION_DEL;
            arp_cmd.ipaddr = inet_addr(argv[i + 1]);

            if (arp_cmd.ipaddr == IPADDR_NONE) {
                PRINTK("IP address is not correct!\n");
                goto arp_error;
            }

            i += 2;
            argc -= 2;
        } else if (strcmp("-s", argv[i]) == 0 && (argc > 2)) {
            /* arp add */
            char *digit = NULL;
            u32_t macaddrlen = strlen(argv[i + 2]) + 1;
            char tmpStr[MAX_MACADDR_STRING_LENGTH];
            char *tmpStr1 = NULL;
            char *saveptr1 = NULL;
            char *temp = NULL;
            int j;

            arp_cmd.option = ARP_OPTION_ADD;
            arp_cmd.ipaddr = inet_addr(argv[i + 1]);

            if (arp_cmd.ipaddr == IPADDR_NONE) {
                PRINTK("IP address is not correct!\n");
                goto arp_error;
            }

            /*cannot add an arp entry of 127.*.*.* */
            if ((arp_cmd.ipaddr & (u32_t)0x0000007fUL) == (u32_t)0x0000007fUL) {
                PRINTK("IP address is not correct!\n");
                goto arp_error;
            }

            if (macaddrlen != MAX_MACADDR_STRING_LENGTH) {
                PRINTK("Wrong MAC address length\n");
                goto arp_error;
            }

            if (strncpy_s(tmpStr, MAX_MACADDR_STRING_LENGTH, argv[i + 2], macaddrlen - 1) != 0) {
                PRINTK("Wrong MAC address\n");
                goto arp_error;
            }

            for (j = 0, tmpStr1 = tmpStr; j < 6; j++, tmpStr1 = NULL) {
                digit = strtok_r(tmpStr1, ":", &saveptr1);
                if ((digit == NULL) || (strlen(digit) > 2)) {
                    PRINTK("MAC address is not correct\n");
                    goto arp_error;
                }

                for (temp = digit; *temp != '\0'; temp++) {
                    if (!isxdigit(*temp)) {
                        PRINTK("MAC address is not correct\n");
                        goto arp_error;
                    }
                }

                CONVERT_STRING_TO_HEX(digit, arp_cmd.ethaddr[j]);
            }

            i += 3;
            argc -= 3;
        } else {
            goto arp_error;
        }
    }

    ret = tcpip_callback(lwip_arp_internal, &arp_cmd);
    if (ret != ERR_OK) {
        PRINTK("%s : tcpip_callback failed in line %d : errnu %d", __FUNCTION__, __LINE__, ret);
        sys_sem_free(&arp_cmd.cb_completed);
        return 1;
    }
    (void)sys_arch_sem_wait(&arp_cmd.cb_completed, 0);
    sys_sem_free(&arp_cmd.cb_completed);
    arp_cmd.cb_print_buf[PRINT_BUF_LEN - 1] = '\0';
    PRINTK("%s", arp_cmd.cb_print_buf);
    return 0;

arp_error:
    lwip_arp_usage("arp");
    sys_sem_free(&arp_cmd.cb_completed);
    return 1;
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(arp_shellcmd, CMD_TYPE_EX, "arp", 1, (CmdCallBackFunc)lwip_arp);
#endif /* LOSCFG_SHELL_CMD_DEBUG */

void ifup_internal(void *arg)
{
    struct netif *netif = NULL;
    struct if_cmd_data *ifcmd_data;

    ifcmd_data = (struct if_cmd_data *)arg;
    if (ifcmd_data == NULL) {
        return;
    }
    netif = netif_find(ifcmd_data->if_name);
    if (netif == NULL) {
        ifcmd_data->err = ERR_VAL;
    } else {
        (void)netif_set_up(netif);
        ifcmd_data->err = ERR_OK;
    }

    sys_sem_signal(&ifcmd_data->cb_completed);
}

void ifdown_internal(void *arg)
{
    struct netif *netif = NULL;
    struct if_cmd_data *ifcmd_data = NULL;

    ifcmd_data = (struct if_cmd_data *)arg;
    if (ifcmd_data == NULL) {
        return;
    }
    netif = netif_find(ifcmd_data->if_name);
    if (netif == NULL) {
        ifcmd_data->err = ERR_VAL;
    } else {
        (void)netif_set_down(netif);
        ifcmd_data->err = ERR_OK;
    }

    sys_sem_signal(&ifcmd_data->cb_completed);
}

#if LWIP_DNS
#ifndef LWIP_TESTBED
LWIP_STATIC
#endif
struct hostent *gethostnameinfo(const char *host)
{
    static struct hostent hostbuf;
    struct hostent *hp = NULL;
    const size_t hstbuflen = 1024;
    char tmphstbuf[1024];
    int res;
    int herr;

    res = lwip_gethostbyname_r(host, &hostbuf, tmphstbuf, hstbuflen, &hp, &herr);
    /*  Check for errors.  */
    if (res || hp == NULL)
        return NULL;
    return hp;
}

LWIP_STATIC unsigned int get_hostip(const char *hname)
{
    unsigned int ip = 0;
    int ret;

    struct hostent *pent = gethostnameinfo(hname);
    if (pent == NULL || pent->h_addr == NULL)
        return 0;
    ret = memcpy_s(&ip, sizeof(ip), pent->h_addr, 4);
    if (ret != 0) {
        return 0;
    }
    return ip;
}
#endif

#if LWIP_EXT_POLL_SUPPORT
static int ping_taskid = -1;
static int ping_kill = 0;
#define PING_ZERO_DATA_LEN 8
static void lwip_ping_usage(void)
{
    PRINTK("Usage:"\
         "\n  ping"
           "\n  ping [-n cnt] [-w interval] [-l data_len] destination"
           "\n  ping [-t] [-w interval] destination"
           "\n  ping -k");
    PRINTK("\n  -t means ping forever, user can use -k to stop the forever ping");
}

LWIP_STATIC int osPingFunc(u32_t destip, u32_t cnt, u32_t interval, u32_t data_len)
{
    int sfd;
    struct sockaddr_in to;
    struct pbuf *pbuf_resp = NULL;
    struct icmp_echo_hdr *iecho = NULL;
    struct icmp_echo_hdr *iecho_resp = NULL;
    struct ip_hdr *iphdr_resp = NULL;
    u32_t iecho_len;
    s16_t ip_hlen;
    u32_t forever;
    u32_t i = 0;
    u32_t succ_cnt = 0;
    u32_t failed_cnt = 0;
    struct timespec start, end;
    long timout_ms = 0;
    struct pollfd pfd;
    long rtt;
    int ret = 0;
    u32_t intrvl = 0;
    char *data_buf = NULL;
    BOOL timeout_flag = false;
    char buf[50];

    iecho_len = sizeof(struct icmp_echo_hdr) + data_len;
    sfd = lwip_socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sfd < 0) {
        perror("Ping socket");
        return -1;
    }
    pbuf_resp = pbuf_alloc(PBUF_RAW, IP_HLEN + sizeof(struct icmp_echo_hdr), PBUF_RAM);
    if (pbuf_resp == NULL) {
        PRINTK("Ping: pbuf_resp malloc failed\n");
        ret = -1;
        goto FAILURE;
    }
    iecho = (struct icmp_echo_hdr *)mem_malloc(iecho_len);
    if (iecho == NULL) {
        PRINTK("Ping: echo request malloc failed\n");
        ret = -1;
        goto FAILURE;
    }

    to.sin_family = AF_INET;
    to.sin_addr.s_addr = destip; /* already in network order */
    to.sin_port = 0;

    if (data_len > PING_ZERO_DATA_LEN) {
        (void)memset_s(iecho, sizeof(struct icmp_echo_hdr) + PING_ZERO_DATA_LEN,
                       0, sizeof(struct icmp_echo_hdr) + PING_ZERO_DATA_LEN);
        data_buf = (char *)iecho + sizeof(struct icmp_echo_hdr) + PING_ZERO_DATA_LEN;
        for (i = 0; i < data_len - PING_ZERO_DATA_LEN; i++) {
            *(data_buf + i) = i + 0x10;
        }
    } else {
        (void)memset_s(iecho, sizeof(struct icmp_echo_hdr) + data_len, 0, sizeof(struct icmp_echo_hdr) + data_len);
    }
    iecho->id = htons((u16_t)LOS_CurTaskIDGet());
    ICMPH_TYPE_SET(iecho, (u8_t)ICMP_ECHO);
    forever = (cnt ? 0 : 1);
    i = 0;
    while (!ping_kill && (forever || (i < cnt))) {
        iecho->seqno = htons((u16_t)i);
        iecho->chksum = 0;
        iecho->chksum = inet_chksum((void *)iecho, iecho_len);

        ret = sendto(sfd, iecho, iecho_len, 0, (struct sockaddr *)&to, (socklen_t)sizeof(to));
        if (ret < 0) {
            perror("Ping: sending ICMP echo request failed\n");
            goto FAILURE;
        }

        /* capture the start time to calculate RTT */
        (void)clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        /* poll for ICMP echo response msg */
        pfd.fd = sfd;

        do {
            pfd.events = POLLIN;
            pfd.revents = 0;
            timeout_flag = false;
            ret = poll(&pfd, 1, LWIP_SHELL_CMD_PING_TIMEOUT);
            if (ret < 0) {
                perror("Ping: poll\n");
                goto FAILURE;
            } else if (ret == 0) {
                /* first type timeout event */
                timeout_flag = true;
                break;
            }

            ret = recv(sfd, pbuf_resp->payload, pbuf_resp->len, MSG_DONTWAIT);
            if (ret < 0) {
                perror("Ping: recv echo reply failed\n");
                goto FAILURE;
            }

            /* Accessing ip header and icmp header */
            iphdr_resp = pbuf_resp->payload;

            ip_hlen = (IPH_HL(iphdr_resp) << 2);
            if (pbuf_header(pbuf_resp, -ip_hlen)) {
                /* this failure will never happen, but failure handle is written just to be in safe side */
                PRINTK("Ping : memory management failure\n");
                goto FAILURE;
            }
            iecho_resp = (struct icmp_echo_hdr *)pbuf_resp->payload;
            /* Reverting back pbuf to its original state */
            if (pbuf_header(pbuf_resp, ip_hlen)) {
                /* this failure will never happen, but failure handle is written just to be in safe side */
                PRINTK("ping : memory management failure\n");
                goto FAILURE;
            }

            if ((iphdr_resp->src.addr != to.sin_addr.s_addr) ||
                ((ICMPH_TYPE(iecho_resp) == ICMP_ECHO) && (iphdr_resp->src.addr == to.sin_addr.s_addr))) {
                /* second type timeout event */
                (void)clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                timout_ms = ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);
                timout_ms = LWIP_SHELL_CMD_PING_TIMEOUT - timout_ms;
            } else {
                timout_ms = 0;
                break;
            }
        } while (timout_ms >= 0);

        /* all timeout events are true timeout */
        if ((timout_ms < 0) || (timeout_flag == true)) {
            failed_cnt++;
            i++;
            PRINTK("\nPing: destination unreachable ...");
            continue;
        }
        /* capture the end time to calculate round trip time */
        (void)clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        rtt = ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);

        if (iphdr_resp->src.addr == to.sin_addr.s_addr) {
            switch (ICMPH_TYPE(iecho_resp)) {
                case ICMP_ER:
                    PRINTK("\n[%u]Reply from %s: ", i, inet_ntop(AF_INET, &to.sin_addr, buf, sizeof(buf)));
                    if (rtt > 0) {
                        PRINTK("time=%ims ", rtt);
                    } else {
                        PRINTK("time<1ms ");
                    }
                    PRINTK("TTL=%u", iphdr_resp->_ttl);

                    /* delay 1s for every successful ping */
                    intrvl = interval;
                    do {
                        if (intrvl < 1000) {
                            sys_msleep(intrvl);
                            break;
                        }
                        intrvl -= 1000;
                        sys_msleep(1000);
                        if (ping_kill == 1)
                            break;
                    } while (intrvl > 0);
                    succ_cnt++;
                    break;
                case ICMP_DUR:
                    PRINTK("\nPing: destination host unreachable ...");
                    break;
                case ICMP_SQ:
                    PRINTK("\nPing: source quench ...");
                    break;
                case ICMP_RD:
                    PRINTK("\nPing: redirect ...");
                    break;
                case ICMP_TE:
                    PRINTK("\nPing: time exceeded ...");
                    break;
                case ICMP_PP:
                    PRINTK("\nPing: parameter problem ...");
                    break;
                default :
                    PRINTK("\nPing: unknow error ...");
                    break;
            }
            i++;
        }
    }

    PRINTK("\n--- %s ping statistics ---\n", inet_ntop(AF_INET, &to.sin_addr, buf, sizeof(buf)));
    PRINTK("%u packets transmitted, %u received, %u loss\n", i, succ_cnt, failed_cnt);

FAILURE:
    ping_kill = 0;
    (void)lwip_close(sfd);
    if (pbuf_resp != NULL) {
        (void)pbuf_free(pbuf_resp);
    }
    if (iecho != NULL) {
        mem_free(iecho);
    }
    return ret;
}

static void ping_cmd(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3)
{
    u32_t destip = p0;
    u32_t count = p1;
    u32_t interval = p2;
    u32_t data_len = p3;
    int ret;

    ret = osPingFunc(destip, count, interval, data_len);
    if (ret < 0) {
        PRINTK("Ping cmd failed due to some errors\n");
    }

    ping_taskid = -1;
}

u32_t osShellPing(int argc, const char **argv)
{
    int ret;
    u32_t i = 0;
    u32_t count = 0;
    int count_set = 0;
    u32_t interval = 1000; /* default ping interval */
    u32_t data_len = 48; /* default data length */
    ip4_addr_t dst_ipaddr;
    TSK_INIT_PARAM_S stPingTask;

    if (!tcpip_init_finish) {
        PRINTK("Ping: tcpip_init have not been called\n");
        return LOS_NOK;
    }

    if ((argc < 1) || (argv == NULL)) {
        PRINTK("Ping: require dest ipaddr at least\n");
        goto ping_error;
    }

    /* could add more param support */
    while (argc > 0) {
        if (strcmp("-n", argv[i]) == 0 && (argc > 1)) {
            ret = atoi(argv[i + 1]);
            if (ret <= 0) {
                PRINTK("Ping count should be greater than 0 \n");
                goto ping_error;
            }
            count = ret;
            count_set = 1;
            i += 2;
            argc -= 2;
        } else if (strcmp("-t", argv[i]) == 0) {
            count = 0; /* ping forerver */
            count_set = 1;
            i++;
            argc--;
        } else if (strcmp("-w", argv[i]) == 0 && (argc > 1)) {
            ret = atoi(argv[i + 1]);
            if (ret <= 0) {
                PRINTK("Ping interval should be greater than 0 \n");
                goto ping_error;
            }

            interval = ret;
            i += 2;
            argc -= 2;
        } else if (strcmp("-l", argv[i]) == 0 && (argc > 1)) {
            ret = atoi(argv[i + 1]);
            if (ret < 0 || ret > (int)(LWIP_MAX_UDP_RAW_SEND_SIZE - sizeof(struct icmp_echo_hdr))) {
                PRINTK("Ping data length error, should be in range of [0, %d] \n",
                       LWIP_MAX_UDP_RAW_SEND_SIZE - sizeof(struct icmp_echo_hdr));
                goto ping_error;
            }
            data_len = ret;
            i += 2;
            argc -= 2;
        } else if (strcmp("-k", argv[i]) == 0) {
            if (ping_taskid > 0) {
                ping_kill = 1; /* stop the current ping task */
                return LOS_OK;
            } else {
                PRINTK("No ping task running...\n");
                return LOS_NOK;
            }
        } else {
            if (argc == 1) {
                break;
            } else {
                PRINTK("Invalid Ping param\n");
                goto ping_error;
            }
        }
    }

    if (!count_set) {
        count = LWIP_SHELL_CMD_PING_RETRY_TIMES;
    }

    /* initialize dst IP address */
    if (argc <= 0) {
        goto ping_error;
    }
#if LWIP_DNS
    dst_ipaddr.addr = get_hostip(argv[i]);
#else /* LWIP_DNS */
    dst_ipaddr.addr = inet_addr(argv[i]);
#endif /* LWIP_DNS */

    if (dst_ipaddr.addr == IPADDR_NONE || dst_ipaddr.addr == IPADDR_ANY) {
        PRINTK("Invalid dest ipaddr: %s\n", argv[i]);
        return LOS_NOK;
    }

    /* start one task if ping forever or ping count greater than 60 */
    if (count == 0 || count > LWIP_SHELL_CMD_PING_RETRY_TIMES) {
        if (ping_taskid > 0) {
            PRINTK("Ping task already running and only support one now\n");
            return LOS_NOK;
        }
        stPingTask.pfnTaskEntry = (TSK_ENTRY_FUNC)ping_cmd;
        stPingTask.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
        stPingTask.pcName = "ping_task";
        stPingTask.usTaskPrio = 8; /* higher than shell */
        stPingTask.uwResved = LOS_TASK_STATUS_DETACHED;
        stPingTask.auwArgs[0] = dst_ipaddr.addr; /* network order */
        stPingTask.auwArgs[1] = count;
        stPingTask.auwArgs[2] = interval;
        stPingTask.auwArgs[3] = data_len;
        ret = LOS_TaskCreate((UINT32 *)(&ping_taskid), &stPingTask);
        if (ret != LOS_OK) {
            PRINTK("ping_task create failed 0x%08x.\n", ret);
            count = LWIP_SHELL_CMD_PING_RETRY_TIMES;
        } else {
            return LOS_OK;
        }
    }

    /* two cases:
     1, ping cout less than LWIP_SHELL_CMD_PING_RETRY_TIMES;
     2, ping task create failed;
    */
    if (osPingFunc(dst_ipaddr.addr, count, interval, data_len) < 0) {
        PRINTK("Ping cmd failed due some errors\n");
    }

    return LOS_OK;
ping_error:
    lwip_ping_usage();
    return LOS_NOK;
}
#ifdef LOSCFG_SHELL
SHELLCMD_ENTRY(ping_shellcmd, CMD_TYPE_EX, "ping", XARGS, (CmdCallBackFunc)osShellPing);
#endif /* LOSCFG_SHELL */

#else /* LWIP_EXT_POLL_SUPPORT*/

u32_t osShellPing(int argc, const char **argv)
{
  int sfd;
  struct sockaddr_in to;
  struct icmp_echo_hdr iecho;
  struct pbuf *pbuf_resp = NULL;
  struct icmp_echo_hdr *iecho_resp = NULL;
  struct ip_hdr *iphdr_resp = NULL;
  s16_t ip_hlen;
  ip_addr_t dst_ipaddr;
  fd_set fdReadSet;
  struct timeval stTimeVal;
  struct timespec start, end;
  int ret;
  s32_t i;
  long rtt;
  s32_t pingcount;
  char buf[50];

  if (!tcpip_init_finish) {
    PRINTK("ping: tcpip_init have not been called\n");
    return LOS_NOK;
  }

  if ((argc < 1) || (argv == NULL)) {
    PRINTK("ping : invalid arguments, ping command receives ip as command line argument \n");
    return LOS_NOK;
  }

  if (argc == 2) {
    pingcount = atoi(argv[1]);
    if (pingcount < 1)
      pingcount = LWIP_SHELL_CMD_PING_RETRY_TIMES;
  } else {
    pingcount = LWIP_SHELL_CMD_PING_RETRY_TIMES;
  }
  PRINTK("ping %u packets start.\n", pingcount);

  /* initialize dst IP address */
#if LWIP_DNS
  ip_2_ip4(&dst_ipaddr)->addr = get_hostip(argv[0]);
#else /* LWIP_DNS */
  ip_2_ip4(&dst_ipaddr)->addr = inet_addr(argv[0]);
#endif /* LWIP_DNS */

  to.sin_family = AF_INET;
  to.sin_addr.s_addr = ip_2_ip4(&dst_ipaddr)->addr;
  to.sin_port = 0;

  if (to.sin_addr.s_addr == IPADDR_NONE || to.sin_addr.s_addr == IPADDR_ANY) {
    PRINTK("ping : invalid ip address : %s\n", argv[0]);
    return LOS_NOK;
  }

  sfd = lwip_socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sfd == -1) {
    PRINTK("ping : failed, socket creation failed\n");
    return LOS_NOK;
  }

  pbuf_resp = pbuf_alloc(PBUF_RAW, IP_HLEN + sizeof(struct icmp_echo_hdr), PBUF_RAM);
  if (pbuf_resp == NULL) {
    PRINTK("ping : memory allocation failed\n");
    goto FAILURE;
  }

  for (i = 0; i < pingcount; i++) {
    (void)memset_s(&iecho, sizeof(iecho), 0, sizeof(iecho));
    ICMPH_TYPE_SET(&iecho, (u8_t)ICMP_ECHO);
    iecho.chksum = inet_chksum(&iecho, sizeof(struct icmp_echo_hdr));

    ret = lwip_sendto(sfd, &iecho, sizeof(struct icmp_echo_hdr), 0, (struct sockaddr *)&to, (socklen_t)sizeof(to));
    if (ret == -1) {
      PRINTK("ping : sending ICMP echo msg failed\n");
      goto FAILURE;
    }

    /* capture the start time to calculate round trip time */
    (void)clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    /* Wait in select for ICMP response msg */
    FD_ZERO(&fdReadSet);
    FD_SET(sfd, &fdReadSet);
    stTimeVal.tv_sec = LWIP_SHELL_CMD_PING_TIMEOUT / 1000;
    stTimeVal.tv_usec = 0;

DO_SELECT:
    ret = select(sfd + 1, &fdReadSet, 0, 0, &stTimeVal);
    if (ret < 0) {
      PRINTK("ping : select failure\n");
      goto FAILURE;
    } else if (ret == 0) {
      PRINTK("Request timed out.\n");
      continue;
    }

    /* capture the end time to calculate round trip time */
    (void)clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    rtt = ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);

    ret = lwip_recv(sfd, pbuf_resp->payload, pbuf_resp->len, 0);
    if (ret == -1) {
      PRINTK("ping : receiving ICMP echo response msg failed\n");
      goto FAILURE;
    }

    /* Accessing ip header and icmp header */
    iphdr_resp = (struct ip_hdr*)(pbuf_resp->payload);
    ip_hlen = (s16_t)(IPH_HL(iphdr_resp) * 4);
    if (pbuf_header(pbuf_resp, (s16_t)(-ip_hlen))) {
      /* this failure will never happen, but failure handle is written just to be in safe side */
      PRINTK("ping : memory management failure\n");
      goto FAILURE;
    }
    iecho_resp = (struct icmp_echo_hdr *)pbuf_resp->payload;

    /* Reverting back pbuf to its original state */
    if (pbuf_header(pbuf_resp, ip_hlen)) {
      /* this failure will never happen, but failure handle is written just to be in safe side */
      PRINTK("ping : memory management failure\n");
      goto FAILURE;
    }

    if (iphdr_resp->src.addr == to.sin_addr.s_addr) {
      if (ICMPH_TYPE(iecho_resp) == ICMP_ER) {
        PRINTK("[%u]Reply from %s: time=%ims TTL=%u\n", i,
               inet_ntoa_r(to.sin_addr.s_addr, buf, sizeof(buf)), rtt, iphdr_resp->_ttl);
      } else if (ICMPH_TYPE(iecho_resp) == ICMP_ECHO) {
        /* If ping self, stack will receive a ICMP_ECHO request message flowing a ICMP_ER reply message,
            and we need reply only, do select again */
        goto DO_SELECT;
      }
    }
  }

  (void)lwip_close(sfd);
  (void)pbuf_free(pbuf_resp);
  return LOS_OK;

FAILURE:
  (void)lwip_close(sfd);
  if (pbuf_resp != NULL) {
    (void)pbuf_free(pbuf_resp);
  }

  return LOS_NOK;
}

#ifdef LOSCFG_SHELL
SHELLCMD_ENTRY(ping_shellcmd, CMD_TYPE_EX, "ping", XARGS, (CmdCallBackFunc)osShellPing);
#endif /* LOSCFG_SHELL */

#endif /* LWIP_EXT_POLL_SUPPORT*/

#if LWIP_IPV6
u32_t osShellPing6(int argc, const char **argv)
{
    u16_t icmpv6_id;
    u16_t icmpv6_seq;
    u32_t nsent;
    u32_t nrecieve;
    u32_t last_recieved;
    struct timespec start, end, start_in_reply;
    struct timespec first, last;
    long rtt;
    int ret;
    fd_set fdReadSet;
    void *param = NULL;
    ping6_args_t ping6_params;
    ping6_stats_t ping6_stats;
    struct sockaddr_in6 to;
    struct icmp6_echo_hdr *iecho_resp = NULL;
    struct icmp6_echo_hdr *iecho = NULL;
    struct timeval stTimeVal;
    struct timeval deltaTimeVal;
    struct pbuf *pbuf_resp = NULL;
    struct pbuf *pbuf_req = NULL;
    int sfd = -1;
    u8_t type;
    u8_t select_on_socket = 0;
    char buf[INET6_ADDRSTRLEN];

    if (!tcpip_init_finish) {
        PRINTK("%s: tcpip_init have not been called\n", __FUNCTION__);
        ret = -1;
        goto exit;
    }

    if ((argc < 1) || (argc > LWIP_MAX_PING6_ARG_COUNT) || (argv == NULL)) {
        goto usage;
    }

    ret = parse_args_ping6(argc, argv, &ping6_params);
    if (ret == -1) {
        goto exit;
    }

    if (ping6_params.args_found & LWIP_PING6_SOURCE_ADDRESS_ARG) {
        type = LWIP_PING6_SOURCE_ADDRESS_ARG;
        param = (void *)(&ping6_params.src_addr);
    } else if (ping6_params.args_found & LWIP_PING6_INTERFACE_ARG) {
        type = LWIP_PING6_INTERFACE_ARG;
        param = (void *)(argv[ping6_params.interface_index]);
    } else {
        type = LWIP_PING6_DEFAULT_SOCKET;
        param = NULL;
    }

    /* Create a socket for sending and receiving pings with appropriate bindings */
    sfd = create_ping6_socket(type, param);
    if (sfd == -1) {
        ret = -1;
        goto exit;
    }

    pbuf_req = pbuf_alloc(PBUF_RAW, LWIP_PING6_STANDARD_PKT_SIZE, PBUF_RAM);
    pbuf_resp = pbuf_alloc(PBUF_RAW, LWIP_PING6_STANDARD_PKT_SIZE, PBUF_RAM);
    if ((pbuf_resp == NULL) || (pbuf_req == NULL)) {
        PRINTK("ping6 : Memory Allocation Failed\n");
        ret = -1;
        goto exit;
    }

    to.sin6_family = AF_INET6;
    inet6_addr_from_ip6addr(&to.sin6_addr, &(ping6_params.dst_addr));
    to.sin6_port = htons(IPPROTO_ICMPV6);

#if LWIP_DNS
    if (lwip_strnicmp(inet_ntop(AF_INET6, &to.sin6_addr, buf, sizeof(buf)), argv[ping6_params.host_index],
                      sizeof(to.sin6_addr))) {
        /* If There Was A DNS Resolution */
        PRINTK("PING %s (%s) with %d bytes of data.\n",
               argv[ping6_params.host_index], buf, LWIP_PING6_STANDARD_PKT_SIZE);
    } else {
        PRINTK("PING %s with %d bytes of data.\n", buf, LWIP_PING6_STANDARD_PKT_SIZE);
    }
#else
    PRINTK("PING %s with %d bytes of data\n", inet_ntop(AF_INET6, &to.sin6_addr, buf, sizeof(buf)), LWIP_PING6_STANDARD_PKT_SIZE);
#endif /* LWIP_DNS */

    nrecieve = 0;
    ping6_stats.flag = 0;
    ping6_stats.avg_rtt = 0;
    ping6_stats.max_rtt = 0;
    ping6_stats.min_rtt = 0;
    last_recieved = LWIP_PING6_STARTING_SEQ_NUM + LWIP_PING6_OUT_OF_ORDER_MAGNITUDE + 1;
    icmpv6_id = (u16_t)LWIP_RAND();
    icmpv6_seq = LWIP_PING6_STARTING_SEQ_NUM;
    /* Setting the start time of the entire ping task for statistics */
    (void)clock_gettime(CLOCK_MONOTONIC_RAW, &first);

    nsent = 0;

    for (nsent = 0; nsent < ping6_params.pingcount; nsent++) {
        /* capture the start tick to calculate rtt */
        (void)clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        /* Initialize Memory To Prevent Unintialized Memory Read Write Issues */
        if (memset_s(pbuf_req->payload, pbuf_req->len, (int)(start.tv_nsec), pbuf_req->len) != 0) {
            goto exit;
        }

        iecho = (struct icmp6_echo_hdr *)pbuf_req->payload;
        iecho->type = ICMP6_TYPE_EREQ;
        iecho->id = icmpv6_id;
        icmpv6_seq++;
        iecho->seqno = icmpv6_seq;
        iecho->code = 0;

        /* Embedding the start_tick as data into the icmp_payload */
        (void)pbuf_header(pbuf_req, (s16_t)(-(s16_t)(sizeof(struct icmp6_echo_hdr))));
        if (memcpy_s(pbuf_req->payload, pbuf_req->len, (void *)&start, sizeof(start)) != 0) {
            goto exit;
        }
        (void)pbuf_header(pbuf_req, (s16_t)((s16_t)(sizeof(struct icmp6_echo_hdr))));

        ret = lwip_sendto(sfd, iecho, pbuf_req->len, 0, (struct sockaddr *)&to, (socklen_t)sizeof(to));
        if (ret == -1) {
            PRINTK("ping6 : Sending ICMP Echo message failed\n");
            goto exit;
        }

        /* Wait in select for ICMP response msg */
        FD_ZERO(&fdReadSet);
        FD_SET(sfd, &fdReadSet);
        stTimeVal.tv_sec = LWIP_MSECS_TO_SECS(LWIP_SHELL_CMD_PING_TIMEOUT);
        stTimeVal.tv_usec = 0;
        select_on_socket = 1;

        while (select_on_socket) {
            select_on_socket = 0;
            ret = select(sfd + 1, &fdReadSet, 0, 0, &stTimeVal);
            if (ret < 0) {
                PRINTK("ping6 : select failure\n");
                goto exit;
            } else if (ret == 0) {
                (void)clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                PRINTK("Request timed out\n");
                continue;
            }

            /* capture the end time to calculate round trip time */
            (void)clock_gettime(CLOCK_MONOTONIC_RAW, &end);

            ret = lwip_recv(sfd, pbuf_resp->payload, pbuf_resp->len, 0);
            if (ret == -1) {
                PRINTK("ping6 : receiving ICMP echo response msg failed\n");
                goto exit;
            }

            if ((u32_t)ret < sizeof(struct icmp6_echo_hdr *)) {
                /* Drop the packet if its too short [Doesnot contain even the header !!] */
                PRINTK("ping6 : received ICMP echo response too short\n");
                goto REDUCE_SELECT_TIME;
            }

            /* Acceping the ICMPv6 payload. */
            /* Here, pbuf_resp->payload wont contain IPv6 Header since its an AF_INET6 RAW Socket */
            iecho_resp = (struct icmp6_echo_hdr *)pbuf_resp->payload;

            if (iecho_resp->id == icmpv6_id) {
                if (iecho_resp->type == ICMP6_TYPE_EREP) {
                    if (ret < LWIP_PING6_STANDARD_PKT_SIZE) {
                        /* Drop the packet if its too short */
                        PRINTK("ping6 : received ICMP echo response too short\n");
                        goto REDUCE_SELECT_TIME;
                    }
                    /* Accept and process only those delayed EREP only if its sequence num is within out-of-order magnitude */
                    if (nsent && iecho_resp->seqno != icmpv6_seq &&
                        (iecho_resp->seqno<(u16_t)(last_recieved - LWIP_PING6_OUT_OF_ORDER_MAGNITUDE) ||
                                           iecho_resp->seqno>(u16_t)(
                            last_recieved + LWIP_PING6_OUT_OF_ORDER_MAGNITUDE))) {
                        /* Otherwise drop it and wait for more packets */
                        goto REDUCE_SELECT_TIME;
                    }
                    ++nrecieve;
                    last_recieved = iecho_resp->seqno;
                    /* Retrieving the start_tick from the packet which was embedded when the request was transmitted */
                    (void)pbuf_header(pbuf_resp, (s16_t)(-(s16_t)(sizeof(struct icmp6_echo_hdr))));
                    if (memcpy_s((void *)&start_in_reply, sizeof(start_in_reply),
                                 pbuf_resp->payload, sizeof(start_in_reply)) != EOK) {
                        goto REDUCE_SELECT_TIME;
                    }
                    (void)pbuf_header(pbuf_resp, (s16_t)((s16_t)(sizeof(struct icmp6_echo_hdr))));

                    rtt = ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);

                    PRINTK("%d bytes from %s : icmp_seq=%d time", ret,
                           inet_ntop(AF_INET6, &to.sin6_addr, buf, sizeof(buf)),
                           ((iecho_resp->seqno) - LWIP_PING6_STARTING_SEQ_NUM));
                    if (rtt < 1) {
                        PRINTK("<1 ms\n");
                    } else {
                        PRINTK("=%i ms\n", rtt);
                    }

                    update_ping6_stats(&ping6_stats, (u32_t)(rtt), nrecieve);

                    /* Checking if its a delayed packet */
                    if ((iecho_resp->seqno != icmpv6_seq) && (nsent < ping6_params.pingcount)) {
                        /* Incase of delayed packet wait on socket for other response before sending a new PING */
                        /* We have to reduce the timeout value now when selecting on socket */
                        goto REDUCE_SELECT_TIME;
                    }
                } else {
                    PRINTK("[%u]ping6 : %s\n", nsent, convert_icmpv6_err_to_string(iecho_resp->type));
                }
            } else {
                /* If incoming packet does not matches with icmp_id, it should be ignored  */
                /* Reduce the timeout for select on socket */
REDUCE_SELECT_TIME:
                deltaTimeVal.tv_sec = (long)(end.tv_sec - start.tv_sec);
                deltaTimeVal.tv_usec = (long)((end.tv_nsec - start.tv_nsec) / 1000);
                /* Subtract deltaTime from stTime and store in stTime */
                /* This will reduce the select time on the socket */
                timersub(&stTimeVal, &deltaTimeVal, &stTimeVal);
                select_on_socket = 1;
            }
        }
    }

    ret = ERR_OK;

    (void)clock_gettime(CLOCK_MONOTONIC_RAW, &last);
    /* Display ping stats */
    PRINTK("--- %s ping statistics ---\n", argv[ping6_params.host_index]);
    PRINTK("%d packets transmitted, %d received, %.2f%% packet loss, time %dms\n",
           nsent, nrecieve, (float)(((float)(nsent - nrecieve)) * ((float)(100)) / ((float)(nsent))),
           ((last.tv_sec - first.tv_sec) * 1000 + (last.tv_nsec - first.tv_nsec) / 1000000));
    if (nrecieve) {
        /* Display rtt stats only if atleast one packet is recieved */
        PRINTK("rtt min/avg/max = %u/%.2f/%u ms\n", ping6_stats.min_rtt, ping6_stats.avg_rtt, ping6_stats.max_rtt);
    }

exit:
    if (sfd != -1) {
        (void)lwip_close(sfd);
    }

    if (pbuf_resp != NULL) {
        (void)pbuf_free(pbuf_resp);
    }

    if (pbuf_req != NULL) {
        (void)pbuf_free(pbuf_req);
    }
    return (u32_t)((ret == (int)ERR_OK) ? LOS_OK : LOS_NOK);

usage:
    PRINTK("Usage:\n");
    PRINTK("\tping6 [-c count] [-I interface/sourceAddress] destination\n");
    return LOS_NOK;
}

LWIP_STATIC int create_ping6_socket(u8_t type, const void *param)
{
    int sfd;
    int ret;
    struct sockaddr_in6 stHostAddr6;
    struct icmp6_filter icmp6_sock_filter;

    sfd = lwip_socket(PF_INET6, SOCK_RAW, IPPROTO_ICMPV6);
    if (sfd == -1) {
        PRINTK("ping6 : Failed, socket creation failed\n");
        return -1;
    }

    if (param != NULL) {
        if (type == LWIP_PING6_SOURCE_ADDRESS_ARG) {
            /* Binding socket to the provided source address */
            (void)memset_s(&stHostAddr6, sizeof(stHostAddr6), 0, sizeof(stHostAddr6));
            stHostAddr6.sin6_family = AF_INET6;
            inet6_addr_from_ip6addr(&stHostAddr6.sin6_addr, (ip6_addr_t *)param);
            stHostAddr6.sin6_port = htons(IPPROTO_ICMPV6);
            stHostAddr6.sin6_scope_id = 0;

            ret = lwip_bind(sfd, (struct sockaddr *)&stHostAddr6, sizeof(stHostAddr6));
            if (ret == -1) {
                (void)lwip_close(sfd);
                PRINTK("ping6 : bind icmp socket: cannot assign requested address\n");
                return ret;
            }
        } else if (type == LWIP_PING6_INTERFACE_ARG) {
            /* Binding socket to the provided netif */
            ret = lwip_setsockopt(sfd, SOL_SOCKET, SO_BINDTODEVICE, (char *)(param), strlen((char *)(param)));
            if (ret == -1) {
                (void)lwip_close(sfd);
                PRINTK("ping6: unknown iface %s\n", (char *)(param));
                return ret;
            }
        }
    }

    /* Setting socket filter since we are interested only in ECHO REPLY and ERROR messages */
    ICMP6_FILTER_SETBLOCKALL (&icmp6_sock_filter);
    ICMP6_FILTER_SETPASS (ICMP6_TYPE_EREP, &icmp6_sock_filter);
    ICMP6_FILTER_SETPASS (ICMP6_TYPE_DUR, &icmp6_sock_filter);
    ICMP6_FILTER_SETPASS (ICMP6_TYPE_PTB, &icmp6_sock_filter);
    ICMP6_FILTER_SETPASS (ICMP6_TYPE_TE, &icmp6_sock_filter);

    ret = lwip_setsockopt(sfd, IPPROTO_ICMPV6, ICMP6_FILTER, &icmp6_sock_filter, sizeof(struct icmp6_filter));
    if (ret == -1) {
        (void)lwip_close(sfd);
        PRINTK("ping6 : setsockopt: Invalid Argument\n");
        return -1;
    }

    return sfd;
}

/*
  Function to parse the command line args for ping6 shell utility
  @return:
    Success: ERR_OK
    Failure: -1
*/
LWIP_STATIC int parse_args_ping6(int argc, const char **argv, ping6_args_t *ping6_params)
{
    int pingcount;
    int ret = -1;
#if LWIP_DNS
    struct addrinfo *res = NULL;
    struct addrinfo hints_structure;
#endif
    u8_t i = 0;

    IP6_ADDR(&(ping6_params->dst_addr), 0, 0, 0, 0);
    IP6_ADDR(&(ping6_params->src_addr), 0, 0, 0, 0);

    ping6_params->pingcount = LWIP_SHELL_CMD_PING_RETRY_TIMES;
    ping6_params->host_index = 0;
    ping6_params->args_found = 0;

    while (i < argc) {
        if (strcmp("-c", argv[i]) == 0) {
            /* Handle number of ICMP packets to transmit :: -c [number_of_packets] */
            if (ping6_params->args_found & LWIP_PING6_COUNT_ARG) {
                PRINTK("ping6: -c option present multiple times \n");
                ret = -1;
                goto exit;
            }

            if (i + 2 > argc) {
                PRINTK("ping6: ping count(-c) should require an argument \n");
                ret = -1;
                goto exit;
            }

            pingcount = atoi(argv[i + 1]);
            if (pingcount <= 0) {
                PRINTK("ping6: bad number of packets to transmit \n");
                ret = -1;
                goto exit;
            }

            ping6_params->args_found |= LWIP_PING6_COUNT_ARG;
            ping6_params->pingcount = (u32_t)pingcount;
            i = (u8_t)(i + 2);
        } else if (strcmp("-I", argv[i]) == 0) {
            /* Handle interface ID / sourceAddress using which the ICMP Packets has to be transmitted :: -I [interface_id/source_address] */

            if ((ping6_params->args_found & LWIP_PING6_SOURCE_ADDRESS_ARG) ||
                (ping6_params->args_found & LWIP_PING6_INTERFACE_ARG)) {
                PRINTK("ping6: -I option present multiple times \n");
                ret = -1;
                goto exit;
            }

            if (i + 2 > argc) {
                PRINTK("ping6: interface/source address(-I) should require an argument \n");
                ret = -1;
                goto exit;
            }

            /* Check whether the given argument to -I is source address */
            if (ip6addr_aton(argv[i + 1], &(ping6_params->src_addr))) {
                ping6_params->args_found |= LWIP_PING6_SOURCE_ADDRESS_ARG;
                i = (u8_t)(i + 2);
                continue;
            }

            /* Storing the index where interface name is found */
            /* If this name is not valid, then it will fail later in setsockopt(BIND_TO_DEVICE) */
            ping6_params->interface_index = (u8_t)(i + 1);
            ping6_params->args_found |= LWIP_PING6_INTERFACE_ARG;

            i = (u8_t)(i + 2);
        } else {
            if (argv[i][0] == '-') {
                /* Check whether its a bad option */
                PRINTK("ping6: bad option %s\n", argv[i]);
                ret = -1;
                goto exit;
            } else if (ping6_params->args_found & LWIP_PING6_HOSTNAME_ARG) {
                /* Check whether hostname is already found and there are extra arguments */
                PRINTK("ping6: bad parameter %s\n", argv[i]);
                ret = -1;
                goto exit;
            }

#if LWIP_DNS
            /* Resolve the given hostname */
            hints_structure.ai_family = AF_INET6;
            hints_structure.ai_flags = 0;
            ret = lwip_getaddrinfo(argv[i], NULL, &hints_structure, &res);
            if (ret != ERR_OK) {
                PRINTK("ping6 : Host : %s can't be resolved to IPv6 address\n", argv[i]);
                ret = -1;
                goto exit;
            }

            inet6_addr_to_ip6addr(&(ping6_params->dst_addr),
                                  &(((const struct sockaddr_in6 *)(res->ai_addr))->sin6_addr));
#else
            /* Convert the string representation to network form */
            if (!ip6addr_aton(argv[i], &(ping6_params->dst_addr))) {
                PRINTK("ping6 : Invalid IPv6 Address : %s\n", argv[i]);
                ret = -1;
                goto exit;
            }
#endif /* LWIP_DNS */
            if (ip6_addr_isany(&(ping6_params->dst_addr)) || ip6_addr_isnone(&(ping6_params->dst_addr))) {
#if LWIP_DNS
                PRINTK("ping6 : IPv6 address of host : %s (%s) is invalid\n", argv[i],
                       ip6addr_ntoa((const ip6_addr_t *)&(ping6_params->dst_addr)));
#else
                PRINTK("ping6 : Invalid IPv6 address : %s\n", argv[i]);
#endif /* LWIP_DNS */
                goto exit;
            }
            /* Setting host_index to the index of argv[] where the host/IP is present */
            ping6_params->args_found |= LWIP_PING6_HOSTNAME_ARG;
            ping6_params->host_index = (u8_t)(i);
            i = (u8_t)(i + 1);
        }
    }

    if (!(ping6_params->args_found & LWIP_PING6_HOSTNAME_ARG)) {
        /* Hostname/IPv6 address not found */
        PRINTK("ping6 : Hostname/IPv6 address to ping is not specified\n");
        ret = -1;
        goto exit;
    }

    if (ip6_addr_islinklocal(&(ping6_params->dst_addr)) &&
        !(ping6_params->args_found & (LWIP_PING6_INTERFACE_ARG | LWIP_PING6_SOURCE_ADDRESS_ARG))) {
        /* For link-local addresses, -I is mandatory */
        PRINTK("ping6 : Interface specification is mandatory for link-local addresses\n");
        ret = -1;
        goto exit;
    }

    ret = ERR_OK;

exit:
#if LWIP_DNS
    lwip_freeaddrinfo(res);
#endif /* LWIP_DNS */

    return ret;
}

/*
 * Function to update ping6_stats
 * stats is maintained in ping6_stats structure
 */
LWIP_STATIC void update_ping6_stats(ping6_stats_t *ping6_stats, u32_t rtt, u32_t nrecieved)
{
    if (rtt > ping6_stats->max_rtt) {
        ping6_stats->max_rtt = rtt;
    }

    if (ping6_stats->flag == 0 || rtt < ping6_stats->min_rtt) {
        ping6_stats->min_rtt = rtt;
        ping6_stats->flag = 1;
    }

    ping6_stats->avg_rtt = (float)(ping6_stats->avg_rtt +
                                   (float)((float)((float)rtt - ping6_stats->avg_rtt) / (float)(nrecieved)));
}

LWIP_STATIC const char *convert_icmpv6_err_to_string(u8_t err_type)
{
    switch (err_type) {
        case ICMP6_TYPE_DUR:
            return "Destination Unreachable";
        case ICMP6_TYPE_PTB:
            return "Packet too big";
        case ICMP6_TYPE_TE:
            return "Time Exceeded";
        case ICMP6_TYPE_PP:
            return "Parameter Problem";
        default:
            break;
    }
    return "Unknown Error";
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(ping6_shellcmd, CMD_TYPE_EX, "ping6", XARGS, (CmdCallBackFunc)osShellPing6);
#endif /* LOSCFG_SHELL_CMD_DEBUG */
#endif /* LWIP_IPV6 */

#if  LWIP_SNTP
u32_t osShellNtpdate(int argc, const char **argv)
{
  int server_num = 0;
  char *ret = NULL;
  struct timeval get_time;
  char buf[50];

  (void)memset_s(&get_time, sizeof(struct timeval), 0, sizeof(struct timeval));

  if (!tcpip_init_finish) {
    PRINTK("%s: tcpip_init have not been called\n", __FUNCTION__);
    return LOS_NOK;
  }

  if (argc < 1 || argv == NULL) {
    goto usage;
  }

  server_num = lwip_sntp_start(argc, (char **)argv, &get_time);
  if (server_num >= 0 && server_num < argc) {
    ret = ctime_r((time_t *)&get_time.tv_sec, buf);
    if (ret != NULL) {
      PRINTK("time server %s: %s\n", argv[server_num], ret);
    } else {
      PRINTK("ctime return null error\n");
    }
  } else {
    PRINTK("no server suitable for synchronization found\n");
  }

  return LOS_OK;

usage:
  PRINTK("\nUsage:\n");
  PRINTK("ntpdate [SERVER_IP1] [SERVER_IP2] ...\n");
  return LOS_NOK;
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(ntpdate_shellcmd, CMD_TYPE_EX, "ntpdate", XARGS, (CmdCallBackFunc)osShellNtpdate);
#endif /* LOSCFG_SHELL_CMD_DEBUG */

#endif /* LWIP_SNTP*/


#ifdef LOSCFG_NET_LWIP_SACK_TFTP
static char *TftpError[] = {
    "TFTP transfer finish\n",
    "Error while creating UDP socket\n",
    "Error while binding to the UDP socket\n",
    "Error returned by select() system call\n",
    "Error while receiving data from the peer\n",
    "Error while sending data to the peer\n",
    "Requested file is not found\n",
    "This is the error sent by the server when hostname cannot be resolved\n",
    "Input paramters passed to TFTP interfaces are invalid\n",
    "Error detected in TFTP packet or the error received from the TFTP server\n",
    "Error during packet synhronization while sending or unexpected packet is received\n",
    "File size limit crossed, Max block can be 0xFFFF, each block containing 512 bytes\n",
    "File name lenght greater than 256\n",
    "Hostname IP is not valid\n",
    "TFTP server returned file access error\n",
    "TFTP server returned error signifying that the DISK is full to write\n",
    "TFTP server returned error signifying that the file exist\n",
    "The source file name do not exisits\n",
    "Memory allocaion failed in TFTP client\n",
    "File open failed\n",
    "File read error\n",
    "File create error\n",
    "File write error\n",
    "Max time expired while waiting for file to be recived\n",
    "Error when the received packet is less than 4bytes(error lenght) or greater than 512bytes\n",
    "Returned by TFTP server for protocol user error\n",
    "The destination file path length greater than 256\n",
    "Returned by TFTP server for undefined transfer ID\n",
    "IOCTL fucntion failed at TFTP client while setting the socket to non-block\n",
};

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif

u32_t osShellTftp(int argc, const char **argv)
{
    u32_t ulRemoteAddr = IPADDR_NONE;
    const u16_t usTftpServPort = 69;
    u8_t ucTftpGet = 0;
    s8_t *szLocalFileName = NULL;
    s8_t *szRemoteFileName = NULL;
    u32_t ret;

    int i = 0;
    if (argc < 1 || argv == NULL) {
        goto usage;
    }

    if (!tcpip_init_finish) {
        PRINTK("%s: tcpip_init have not been called\n", __FUNCTION__);
        return LOS_NOK;
    }

    while (i < argc) {
        if (strcmp(argv[i], "-p") == 0) {
            ucTftpGet = 0;
            i++;
            continue;
        }

        if (strcmp(argv[i], "-g") == 0) {
            ucTftpGet = 1;
            i++;
            continue;
        }

        if (strcmp(argv[i], "-l") == 0 && ((i + 1) < argc)) {
            szLocalFileName = (s8_t *)argv[i + 1];
            i += 2;
            continue;
        }

        if (strcmp(argv[i], "-r") == 0 && ((i + 1) < argc)) {
            szRemoteFileName = (s8_t *)argv[i + 1];
            i += 2;
            continue;
        }

        if ((i + 1) == argc) {
            ulRemoteAddr = inet_addr(argv[i]);
            break;
        }

        goto usage;
    }

    if (ulRemoteAddr == IPADDR_NONE || szLocalFileName == NULL || szRemoteFileName == NULL) {
        goto usage;
    }

    if (ucTftpGet) {
        ret = lwip_tftp_get_file_by_filename(ntohl(ulRemoteAddr), usTftpServPort,
                                             TRANSFER_MODE_BINARY, szRemoteFileName, szLocalFileName);
    } else {
        ret = lwip_tftp_put_file_by_filename(ntohl(ulRemoteAddr), usTftpServPort,
                                             TRANSFER_MODE_BINARY, szLocalFileName, szRemoteFileName);
    }

    LWIP_ASSERT("TFTP UNKNOW ERROR!", ret < ARRAY_SIZE(TftpError));
    PRINTK("%s", TftpError[ret]);
    if (ret) {
        return LOS_NOK;
    } else {
        return LOS_OK;
    }
usage:
    PRINTK("usage:\nTransfer a file from/to tftp server\n");
    PRINTK("tftp <-g/-p> -l FullPathLocalFile -r RemoteFile Host\n");
    return LOS_NOK;
}
#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(tftp_shellcmd, CMD_TYPE_EX, "tftp", XARGS, (CmdCallBackFunc)osShellTftp);
#endif /* LOSCFG_SHELL_CMD_DEBUG */
#endif /* LOSCFG_NET_LWIP_SACK_TFTP */


#if LWIP_DNS
u32_t osShellDns(int argc, const char **argv)
{
    ip_addr_t dns = {0};
    err_t err;
    int i;
    if (argc < 1 || argv == NULL) {
        goto usage;
    }

    if (tcpip_init_finish == 0) {
        PRINTK("%s: tcpip_init have not been called\n", __FUNCTION__);
        return LOS_NOK;
    }

    if (argc == 1 && (strcmp(argv[0], "-a") == 0)) {
        for (i = 0; i < DNS_MAX_SERVERS; i++) {
            err = lwip_dns_getserver((u8_t)i, &dns);
            if (err == ERR_OK) {
                PRINTK("dns %d: %s\n", i + 1, ipaddr_ntoa_unsafe(&dns));
            } else {
                PRINTK("dns: failed\n");
                return LOS_NOK;
            }
        }
        return LOS_OK;
    } else if (argc == 2) {
        i = atoi(argv[0]);
        if ((i <= 0) || (i > DNS_MAX_SERVERS))
            goto usage;
#if LWIP_IPV6
        if (ip6addr_aton(argv[1], ((ip6_addr_t *)&dns))) {
#if LWIP_IPV4 && LWIP_IPV6
            dns.type = IPADDR_TYPE_V6;
#endif
            if (!ip6_addr_isglobal((ip6_addr_t *)&dns)) {
                PRINTK("ip address<%s> is wrong\n", argv[1]);
                return LOS_NOK;
            }
        } else
#endif
        {
#if LWIP_IPV4
            ((ip4_addr_t *)&dns)->addr = ipaddr_addr(argv[1]);
            if (((ip4_addr_t *)&dns)->addr == IPADDR_NONE) {
                PRINTK("ip address<%s> is wrong\n", argv[1]);
                return LOS_NOK;
            }
#if LWIP_IPV4 && LWIP_IPV6
            dns.type = IPADDR_TYPE_V4;
#endif
#endif
        }

        err = lwip_dns_setserver((u8_t)(i - 1), &dns);
        if (err != ERR_OK) {
            PRINTK("dns : failed\n");
            return LOS_NOK;
        }
        return LOS_OK;
    }
usage:
    PRINTK("usage:\n");
    PRINTK("\tdns <1-%d> <IP>\n", DNS_MAX_SERVERS);
    PRINTK("\tdns -a\n");
    return LOS_NOK;
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(dns_shellcmd, CMD_TYPE_EX, "dns", XARGS, (CmdCallBackFunc)osShellDns);
#endif /* LOSCFG_SHELL_CMD_DEBUG */
#endif /* LWIP_DNS */
#if LWIP_IPV6
extern struct nd6_neighbor_cache_entry neighbor_cache[LWIP_ND6_NUM_NEIGHBORS];
#endif
#if LWIP_IPV6
int netstat_get_udp_sendQLen6(struct udp_pcb *udppcb, struct pbuf *udpbuf)
{
    int sendLen = -1;
    u16_t offset = 0, len;
    struct ip6_hdr *iphdr = NULL;
    struct udp_hdr *udphdr = NULL;
    struct ip6_dest_hdr *dest_hdr = NULL;
    struct ip6_frag_hdr *frag_hdr = NULL;
    u8_t nexth;
    u16_t hlen = 0;

    LWIP_ERROR("netstat_get_udp6_sendQLen: NULL pcb received\n", (udppcb != NULL), return -1);
    LWIP_ERROR("netstat_get_udp6_sendQLen: NULL pbuf received\n", (udpbuf != NULL), return -1);

    iphdr = (struct ip6_hdr *)udpbuf->payload;

    if (!(ip6_addr_cmp(&iphdr->dest, ip_2_ip6(&udppcb->remote_ip)) &&
          (ip_addr_isany(&udppcb->local_ip) ||
           ip_get_option(udppcb, SOF_BINDNONUNICAST) ||
           ip6_addr_cmp(&iphdr->src, ip_2_ip6(&udppcb->local_ip))))) {
        goto FUNC_OUT;
    }

    len = IP6_HLEN;
    if (pbuf_header(udpbuf, (s16_t)(-(s16_t)(len)))) {
        goto FUNC_OUT;
    }

    offset = len;

    nexth = IP6H_NEXTH(iphdr);
    while (offset < udpbuf->tot_len) {
        if (nexth == IP6_NEXTH_NONE || nexth == IP6_NEXTH_UDP || nexth == IP6_NEXTH_UDPLITE) {
            break;
        }
        switch (nexth) {
            case IP6_NEXTH_HOPBYHOP:
            case IP6_NEXTH_ROUTING:
                nexth = *((u8_t *)udpbuf->payload);
                hlen = (u16_t)(8 * (1 + *((u8_t *)udpbuf->payload + 1)));
                break;
            case IP6_NEXTH_DESTOPTS:
                nexth = *((u8_t *)udpbuf->payload);
                dest_hdr = (struct ip6_dest_hdr *)udpbuf->payload;
                hlen = (u16_t)(8 * (1 + dest_hdr->_hlen));
                break;
            case IP6_NEXTH_FRAGMENT:
                frag_hdr = (struct ip6_frag_hdr *)udpbuf->payload;
                nexth = frag_hdr->_nexth;
                hlen = IP6_FRAG_HLEN;
                break;
            default:
                /* Unknown next_header */
                goto FUNC_OUT;
        }

        (void)pbuf_header(udpbuf, (s16_t)(-(s16_t)hlen));
        offset = (u16_t)(offset + hlen);
    }

    /* If the while loop test condition failed , then revert the last offset change */
    if (offset >= udpbuf->tot_len) {
        offset = (u16_t)(offset - hlen);
        goto FUNC_OUT;
    }

    LWIP_ERROR("Transport option should be UDP", (nexth == IP6_NEXTH_UDP || nexth == IP6_NEXTH_UDPLITE), goto FUNC_OUT);

    if (offset > iphdr->_plen) {
        goto FUNC_OUT;
    }

    /* check if there is enough space for atleast udp header available */
    if (udpbuf->tot_len < UDP_HLEN) {
        goto FUNC_OUT;
    }

    udphdr = (struct udp_hdr *)udpbuf->payload;
    if ((ntohs(udphdr->dest) == udppcb->remote_port) && (ntohs(udphdr->src) == udppcb->local_port)) {
        if (ntohs(udphdr->len) > UDP_HLEN) {
            sendLen = ntohs(udphdr->len) - UDP_HLEN;
        } else {
            sendLen = udpbuf->tot_len - UDP_HLEN;
        }
    }

FUNC_OUT:
    (void)pbuf_header(udpbuf, (s16_t)offset); // can not cross max limit of s16_t
    return sendLen;
}
#endif

#if LWIP_IPV4
int netstat_get_udp_sendQLen(struct udp_pcb *udppcb, struct pbuf *udpbuf)
{
    int sendLen = -1;
    u16_t offset = 0, len;
    struct ip_hdr *iphdr = NULL;
    struct udp_hdr *udphdr = NULL;

    LWIP_ERROR("netstat_get_udp_sendQLen: NULL pcb received\n", (udppcb != NULL), return -1);
    LWIP_ERROR("netstat_get_udp_sendQLen: NULL pbuf received\n", (udpbuf != NULL), return -1);

    iphdr = (struct ip_hdr *)udpbuf->payload;

    if (!(ip4_addr_cmp(&iphdr->dest, ip_2_ip4(&udppcb->remote_ip)) &&
          (ip_addr_isany(&udppcb->local_ip) ||
           ip_get_option(udppcb, SOF_BINDNONUNICAST) ||
           ip4_addr_cmp(&iphdr->src, ip_2_ip4(&udppcb->local_ip))))) {
        goto FUNC_OUT;
    }
#if LWIP_UDPLITE
    if ((IPH_PROTO(iphdr) != IP_PROTO_UDP) && (IPH_PROTO(iphdr) != IP_PROTO_UDPLITE)) {
#else
    if (IPH_PROTO(iphdr) != IP_PROTO_UDP) {
#endif
        goto FUNC_OUT;
    }

    if ((ntohs(IPH_OFFSET(iphdr)) & IP_OFFMASK) != 0) {
        goto FUNC_OUT;
    }

    len = (u16_t)(IPH_HL(iphdr) * 4);
    if (pbuf_header(udpbuf, (s16_t)(-len))) {
        goto FUNC_OUT;
    }

    offset = (u16_t)(offset + len);

    udphdr = (struct udp_hdr *)udpbuf->payload;
    if ((ntohs(udphdr->dest) == udppcb->remote_port) && (ntohs(udphdr->src) == udppcb->local_port)) {
        sendLen = ntohs(udphdr->len) - UDP_HLEN;
    }

FUNC_OUT:
    (void)pbuf_header(udpbuf, (s16_t)offset);
    return sendLen;
}
#endif

int netstat_tcp_recvq(struct tcp_pcb *tpcb)
{
    unsigned int retVal = 0;
#if LWIP_SO_RCVBUF
    struct netconn *conn = NULL;
#endif

    LWIP_ERROR("netstat_tcp_recvq: Received NULL pcb\n", (tpcb != NULL), return 0);

#if LWIP_SO_RCVBUF
    conn = (struct netconn *)tpcb->callback_arg;
    if (conn != NULL) {
        switch (conn->type) {
            case NETCONN_TCP:
            case NETCONN_RAW:
#if LWIP_IPV6
            case NETCONN_RAW_IPV6:
            case NETCONN_UDP_IPV6:
#endif
            case NETCONN_UDP:
                SYS_ARCH_GET(((unsigned int)conn->recv_avail /*+ conn->lrcv_left*/), retVal);
                break;
            default:
                retVal = 0; /* ur... very ugly, damn DHCP DNS and SNTP */
        }
    }
#endif

    return (int)retVal;
}

int netstat_tcp_sendq(struct tcp_pcb *tpcb)
{
    int retVal = 0;
    struct tcp_seg *useg = NULL;

    LWIP_ERROR("netstat_tcp_sendq: Received NULL pcb\n", (tpcb != NULL), return 0);

    for (useg = tpcb->unacked; useg != NULL; useg = useg->next) {
        retVal = retVal + useg->len;
    }

    return retVal;
}

#if LWIP_IPV6
int netstat_udp_sendq6(struct udp_pcb *upcb)
{
    int retLen = 0;
    int ret;
    int idx = 0;
    int i;
#if LWIP_ND6_QUEUEING
    struct nd6_q_entry *neibq = NULL;
#endif

    LWIP_ERROR("netstat_udp_sendq6: Received NULL pcb\n", (upcb != NULL), return 0);

    for (i = 0; i < LWIP_ND6_NUM_NEIGHBORS; i++) {
        if (neighbor_cache[i].state != ND6_NO_ENTRY) {
            if (ip6_addr_cmp(&upcb->remote_ip.u_addr.ip6, &neighbor_cache[i].next_hop_address)) {
                idx = i;
                break;
            }
        }
    }
#if LWIP_ND6_QUEUEING
    for (neibq = neighbor_cache[idx].q; neibq != NULL; neibq = neibq->next) {
        ret = netstat_get_udp_sendQLen6(upcb, neibq->p);
        if (ret >= 0) {
            retLen += ret;
        }
    }
#else
    ret = netstat_get_udp_sendQLen6(upcb, neighbor_cache[idx].q);
    if (ret >= 0) {
      retLen += ret;
    }
#endif
    return retLen;
}
#endif

#if LWIP_IPV4
int netstat_udp_sendq(struct udp_pcb *upcb)
{
    int retLen = 0;
    int ret;
    int arpidx = -1;
    int i;
#if ARP_QUEUEING
    struct etharp_q_entry *arpq = NULL;
#endif

    LWIP_ERROR("netstat_udp_sendq: Received NULL pcb\n", (upcb != NULL), return 0);

    for (i = 0; i < ARP_TABLE_SIZE; ++i) {
        if (arp_table[i].state != ETHARP_STATE_EMPTY) {
            if (ip4_addr_cmp(ip_2_ip4(&upcb->remote_ip), &arp_table[i].ipaddr)) {
                arpidx = i;
                break;
            }
        }
    }

    if (arpidx >= 0) {
#if ARP_QUEUEING
        for (arpq = arp_table[arpidx].q; arpq != NULL; arpq = arpq->next) {
            ret = netstat_get_udp_sendQLen(upcb, arpq->p);
            if (ret > 0) {
                retLen += ret;
                if (retLen <= 0) { // overflow, set rteLen = -1 to indicate
                    retLen = -1;
                    break;
                }
            }
        }
#else
        ret = netstat_get_udp_sendQLen(upcb, arp_table[arpidx].q);
        if (ret > 0) {
          retLen += ret;
          if (retLen <= 0) { // overflow, set rteLen = -1 to indicate
            retLen = -1;
          }
        }
#endif
    }
    return retLen;
}
#endif
int netstat_netconn_recvq(const struct netconn *conn)
{
    unsigned int retVal = 0;

#if LWIP_SO_RCVBUF
    if (conn == NULL) {
        return 0;
    }

    switch (NETCONNTYPE_GROUP((unsigned int)(conn->type))) {
        case NETCONN_TCP:
        case NETCONN_RAW:
#if PF_PKT_SUPPORT
        case NETCONN_PKT_RAW:
#endif
        case NETCONN_UDP:
            SYS_ARCH_GET(((unsigned int)conn->recv_avail /*+ conn->lrcv_left*/), retVal);
            break;
        default:
            retVal = 0; /* ur... very ugly, damn DHCP DNS and SNTP */
    }
#endif
    return (int)retVal;
}

int netstat_netconn_sendq(struct netconn *conn)
{
    int retVal = 0;

    if (conn == NULL) {
        return 0;
    }

    switch (NETCONNTYPE_GROUP((unsigned int)(conn->type))) {
        case NETCONN_TCP:
            retVal = netstat_tcp_sendq(conn->pcb.tcp);
            break;
        case NETCONN_RAW:
            retVal = 0; /* todo */
            break;
#if PF_PKT_SUPPORT
        case NETCONN_PKT_RAW:
            retVal = 0; /* always be 0 as frame send to driver directly */
#endif
            break;
        case NETCONN_UDP:
            retVal = netstat_udp_sendq(conn->pcb.udp);
            break;
        default:
            retVal = 0; /* ur... very ugly, damn DHCP DNS and SNTP */
    }

    return retVal;
}
void netstat_internal(void *ctx)
{
    s8_t local_ip_port[64] = {0};
    s8_t remote_ip_port[64] = {0};
    struct tcp_pcb *tpcb = NULL;
    struct tcp_pcb_listen *lpcb = NULL;
    struct udp_pcb *upcb = NULL;
    struct raw_pcb *rpcb = NULL;
    s8_t *entry_buf = NULL;
    u32_t entry_buf_len;
    u32_t entry_buf_offset;
    struct netstat_data *ndata = (struct netstat_data *)ctx;
    int iRet;
    int recvQlen = 0;
    int sendQlen = 0;
    u_int proto;
    u8_t netif_name[IFNAMSIZ];
    struct netif *netif = NULL;

    if (ndata == NULL) {
        return;
    }
    entry_buf = ndata->netstat_out_buf;
    entry_buf_len = ndata->netstat_out_buf_len;
    entry_buf_offset = 0;

    if (entry_buf == NULL) {
        goto out;
    }
    iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                      "========== total sockets %d ======  unused sockets %d ==========\n",
                      LWIP_CONFIG_NUM_SOCKETS, get_unused_socket_num());
    if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
        goto out;
    }
    entry_buf_len -= (u32_t)(iRet);
    entry_buf_offset += (u32_t)(iRet);

#if LWIP_TCP
    if (tcp_active_pcbs != NULL || tcp_bound_pcbs != NULL || tcp_tw_pcbs != NULL || tcp_listen_pcbs.pcbs != NULL) {
        iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                          "%-8s%-12s%-12s%-24s%-24s%-16s\n",
                          "Proto", "Recv-Q", "Send-Q", "Local Address", "Foreign Address", "State");
        if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
            goto out;
        }
        entry_buf_len -= (u32_t)(iRet);
        entry_buf_offset += (u32_t)(iRet);

        for (tpcb = tcp_active_pcbs; tpcb != NULL; tpcb = tpcb->next) {
            iRet = snprintf_s((char *)local_ip_port, sizeof(local_ip_port), (sizeof(local_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&tpcb->local_ip), tpcb->local_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(local_ip_port))) {
                goto out;
            }

            iRet = snprintf_s((char *)remote_ip_port, sizeof(remote_ip_port), (sizeof(remote_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(remote_ip_port))) {
                goto out;
            }
            if (tpcb->state == SYN_RCVD) {
                recvQlen = 0;
                sendQlen = 0;
            } else {
                recvQlen = netstat_netconn_recvq(tpcb->callback_arg);
                sendQlen = netstat_netconn_sendq(tpcb->callback_arg);
            }
            iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                              IP_IS_V6(&tpcb->local_ip) ? "%-8s%-12d%-12d%-39s%-39s%-16s\n" :
                              "%-8s%-12d%-12d%-24s%-24s%-16s\n",
                              IP_IS_V6(&tpcb->local_ip) ? "tcp-ip6" : "tcp",
                              recvQlen, sendQlen, local_ip_port, remote_ip_port, tcp_state_str[tpcb->state]);
            if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
                goto out;
            }
            entry_buf_len -= (u32_t)(iRet);
            entry_buf_offset += (u32_t)(iRet);
        }

        /* For bound PCBs */
        sendQlen = 0;
        recvQlen = 0;

        for (tpcb = tcp_bound_pcbs; tpcb != NULL; tpcb = tpcb->next) {
            iRet = snprintf_s((char *)local_ip_port, sizeof(local_ip_port), (sizeof(local_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&tpcb->local_ip), tpcb->local_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(local_ip_port))) {
                goto out;
            }

            iRet = snprintf_s((char *)remote_ip_port, sizeof(remote_ip_port), (sizeof(remote_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(remote_ip_port))) {
                goto out;
            }

            iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                              IP_IS_V6(&tpcb->local_ip) ? "%-8s%-12d%-12d%-39s%-39s%-16s\n" :
                              "%-8s%-12d%-12d%-24s%-24s%-16s\n",
                              IP_IS_V6(&tpcb->local_ip) ? "tcp-ip6" : "tcp",
                              recvQlen, sendQlen, local_ip_port, remote_ip_port, tcp_state_str[tpcb->state]);
            if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
                goto out;
            }
            entry_buf_len -= (u32_t)(iRet);
            entry_buf_offset += (u32_t)(iRet);
        }

        for (tpcb = tcp_tw_pcbs; tpcb != NULL; tpcb = tpcb->next) {
            iRet = snprintf_s((char *)local_ip_port, sizeof(local_ip_port), (sizeof(local_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&tpcb->local_ip), tpcb->local_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(local_ip_port))) {
                goto out;
            }

            iRet = snprintf_s((char *)remote_ip_port, sizeof(remote_ip_port), (sizeof(remote_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&tpcb->remote_ip), tpcb->remote_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(remote_ip_port))) {
                goto out;
            }

            recvQlen = netstat_netconn_recvq(tpcb->callback_arg);
            sendQlen = netstat_netconn_sendq(tpcb->callback_arg);
            iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                              IP_IS_V6(&tpcb->local_ip) ? "%-8s%-12d%-12d%-39s%-39s%-16s\n" :
                              "%-8s%-12d%-12d%-24s%-24s%-16s\n",
                              IP_IS_V6(&tpcb->local_ip) ? "tcp-ip6" : "tcp",
                              recvQlen, sendQlen, local_ip_port, remote_ip_port, tcp_state_str[tpcb->state]);
            if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
                goto out;
            }
            entry_buf_len -= (u32_t)(iRet);
            entry_buf_offset += (u32_t)(iRet);
        }

        /* For listen PCBs */
        recvQlen = 0;
        sendQlen = 0;

        for (lpcb = tcp_listen_pcbs.listen_pcbs; lpcb != NULL; lpcb = lpcb->next) {
            iRet = snprintf_s((char *)local_ip_port, sizeof(local_ip_port), (sizeof(local_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&lpcb->local_ip), lpcb->local_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(local_ip_port))) {
                goto out;
            }

            iRet = snprintf_s((char *)remote_ip_port, sizeof(remote_ip_port), (sizeof(remote_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&lpcb->remote_ip), 0);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(remote_ip_port))) {
                goto out;
            }

            recvQlen = netstat_netconn_recvq(lpcb->callback_arg);

            iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                              IP_IS_V6(&lpcb->local_ip) ? "%-8s%-12d%-12d%-39s%-39s%-16s\n" :
                              "%-8s%-12d%-12d%-24s%-24s%-16s\n",
                              IP_IS_V6(&lpcb->local_ip) ? "tcp-ip6" : "tcp",
                              recvQlen, sendQlen, local_ip_port, remote_ip_port, tcp_state_str[lpcb->state]);
            if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
                goto out;
            }
            entry_buf_len -= (u32_t)(iRet);
            entry_buf_offset += (u32_t)(iRet);
        }
    }
#endif
#if LWIP_UDP
    if (udp_pcbs != NULL) {
        iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                          "\n%-8s%-12s%-12s%-24s%-24s\n",
                          "Proto", "Recv-Q", "Send-Q", "Local Address", "Foreign Address");
        if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
            goto out;
        }
        entry_buf_len -= (u32_t)(iRet);
        entry_buf_offset += (u32_t)(iRet);

        for (upcb = udp_pcbs; upcb != NULL; upcb = upcb->next) {
            iRet = snprintf_s((char *)local_ip_port, sizeof(local_ip_port), (sizeof(local_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&upcb->local_ip), upcb->local_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(local_ip_port))) {
                goto out;
            }

            iRet = snprintf_s((char *)remote_ip_port, sizeof(remote_ip_port), (sizeof(remote_ip_port) - 1),
                              "%s:%d", ipaddr_ntoa(&upcb->remote_ip), upcb->remote_port);
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(remote_ip_port))) {
                goto out;
            }

            recvQlen = netstat_netconn_recvq(upcb->recv_arg);
#if LWIP_IPV6
            sendQlen = IP_IS_V6(&upcb->local_ip) ? netstat_udp_sendq6(upcb) : netstat_netconn_sendq(upcb->recv_arg);
#else
            sendQlen = netstat_netconn_sendq(upcb->recv_arg);
#endif
            iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                              IP_IS_V6(&upcb->local_ip) ? "%-8s%-12d%-12d%-39s%-39s%-16s\n" :
                              "%-8s%-12d%-12d%-24s%-24s%-16s\n",
                              IP_IS_V6(&upcb->local_ip) ? "udp-ip6" : "udp",
                              recvQlen, sendQlen, local_ip_port, remote_ip_port, " ");
            if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
                goto out;
            }
            entry_buf_len -= (u32_t)(iRet);
            entry_buf_offset += (u32_t)(iRet);
        }
    }
#endif

#if LWIP_RAW
    if (raw_pcbs != NULL) {
        iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                          "\n%-8s%-12s%-12s%-20s%-20s%-16s%-16s\n",
                          "Type", "Recv-Q", "Send-Q", "Local Address", "Foreign Address", "Protocol", "HDRINCL");
        if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
            goto out;
        }
        entry_buf_len -= (u32_t)(iRet);
        entry_buf_offset += (u32_t)(iRet);

        for (rpcb = raw_pcbs; rpcb != NULL; rpcb = rpcb->next) {
            iRet = snprintf_s((char *)local_ip_port, sizeof(local_ip_port), (sizeof(local_ip_port) - 1),
                              "%s", ipaddr_ntoa(&rpcb->local_ip));
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(local_ip_port))) {
                goto out;
            }

            iRet = snprintf_s((char *)remote_ip_port, sizeof(remote_ip_port), (sizeof(remote_ip_port) - 1),
                              "%s", ipaddr_ntoa(&rpcb->remote_ip));
            if ((iRet <= 0) || ((u32_t)(iRet) >= sizeof(remote_ip_port))) {
                goto out;
            }

            recvQlen = netstat_netconn_recvq(rpcb->recv_arg);
            sendQlen = netstat_netconn_sendq(rpcb->recv_arg);

            proto = rpcb->protocol;//raw_proto;
            iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                              "%-8s%-12d%-12d%-20s%-20s%-16u%-16d\n",
                              "raw", recvQlen, sendQlen, local_ip_port, remote_ip_port, proto, /*rpcb->hdrincl*/0);
            if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
                goto out;
            }
            entry_buf_len -= (u32_t)(iRet);
            entry_buf_offset += (u32_t)(iRet);
        }
    }
#if PF_PKT_SUPPORT
    if (pkt_raw_pcbs != NULL) {
        iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                          "\n%-12s%-12s%-12s%-16s%-12s\n", "Type", "Recv-Q", "Send-Q", "Protocol", "netif");
        if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
            goto out;
        }
        entry_buf_len -= (u32_t)(iRet);
        entry_buf_offset += (u32_t)(iRet);

        for (rpcb = pkt_raw_pcbs; rpcb != NULL; rpcb = rpcb->next) {
            recvQlen = netstat_netconn_recvq(rpcb->recv_arg);
            sendQlen = netstat_netconn_sendq(rpcb->recv_arg);

            for (netif = netif_list; netif != NULL; netif = netif->next) {
                if (netif_get_index(netif)/*netif->ifindex*/ == rpcb->netif_idx/*index*/) {
                    (void)snprintf_s((char *)netif_name, IFNAMSIZ, IFNAMSIZ - 1, "%s", netif_get_name(netif));
                    break;
                }
            }

            if (netif == NULL) {
                (void)snprintf_s((char *)netif_name, IFNAMSIZ, IFNAMSIZ - 1, "%s", "None");
            }

            proto = rpcb->protocol;//ntohs(rpcb->proto.eth_proto);

            iRet = snprintf_s((char *)(entry_buf + entry_buf_offset), entry_buf_len, entry_buf_len - 1,
                              "%-12s%-12d%-12d%-16x%-12s\n", "pkt-raw", recvQlen, sendQlen, proto, netif_name);
            if ((iRet <= 0) || ((u32_t)(iRet) >= entry_buf_len)) {
                goto out;
            }
            entry_buf_len -= (u32_t)(iRet);
            entry_buf_offset += (u32_t)(iRet);
        }
    }
#endif
#endif

out:
    ndata->netstat_out_buf_updated_len = entry_buf_offset;
    sys_sem_signal(&ndata->cb_completed);
    return;
}

u32_t osShellNetstat(int argc, const char **argv)
{
    struct netstat_data ndata;
    err_t err;

    if (argc > 0) {
        PRINTK("\nUsage: netstat\n");
        return LOS_NOK;
    }

    if (tcpip_init_finish == 0) {
        PRINTK("%s: tcpip_init have not been called\n", __FUNCTION__);
        return LOS_NOK;
    }

    ndata.netstat_out_buf = mem_malloc(MAX_NETSTAT_ENTRY);
    if (ndata.netstat_out_buf == NULL) {
        PRINTK("%s: no free mem\n", __FUNCTION__);
        return LOS_NOK;
    }
    ndata.netstat_out_buf_len = MAX_NETSTAT_ENTRY;
    ndata.netstat_out_buf_updated_len = 0;

    if (sys_sem_new(&ndata.cb_completed, 0) != ERR_OK) {
        goto err_hand;
    }

    err = tcpip_callback(netstat_internal, &ndata);
    if (err != ERR_OK) {
        sys_sem_free(&ndata.cb_completed);
        goto err_hand;
    }

    (void)sys_arch_sem_wait(&ndata.cb_completed, 0);
    sys_sem_free(&ndata.cb_completed);
    if ((ndata.netstat_out_buf_updated_len > 0) && (ndata.netstat_out_buf_updated_len < MAX_NETSTAT_ENTRY)) {
        PRINTK("%s\n", (char *)(ndata.netstat_out_buf));
        mem_free(ndata.netstat_out_buf);
        return LOS_OK;
    }

err_hand:
    mem_free(ndata.netstat_out_buf);
    ndata.netstat_out_buf = NULL;
    (void)(argv);
    return LOS_NOK;
}
#ifdef LOSCFG_SHELL
SHELLCMD_ENTRY(netstat_shellcmd, CMD_TYPE_EX, "netstat", XARGS, (CmdCallBackFunc)osShellNetstat);
#endif /* LOSCFG_SHELL */

#define NETIF_NAME_LEN 10
STATIC VOID OsShellDhclientUsage(VOID)
{
    PRINTK("<netif name>,       start dhcp for netif name\n"
           "-x <netif name>,    stop dhcp for netif name\n"
           "-h | --help,        print dhclient command usage\n");
}

u32_t OsShellDhclient(int argc, const char **argv)
{
    struct netif *netif = NULL;

    if (argc == 0) {
        OsShellDhclientUsage();
    } else if (argc == 1) {
        if (strcmp(argv[0], "-h") == 0 || strcmp(argv[0], "--help") == 0) {
            OsShellDhclientUsage();
        } else {
            netif = netif_find(argv[0]);
            if (netif != NULL) {
                (VOID)netifapi_dhcp_start(netif);
            } else {
                PRINTK("dhclient: invalid option: %s\n", argv[0]);
                OsShellDhclientUsage();
            }
        }
    } else if (argc == 2) {
        if (strcmp(argv[0], "-x") == 0) {
            netif = netif_find(argv[1]);
            if (netif != NULL) {
                (VOID)netifapi_dhcp_stop(netif);
            } else {
                PRINTK("dhclient: invalid option: %s\n", argv[1]);
                OsShellDhclientUsage();
            }
        } else {
            PRINTK("dhclient: invalid option: %s\n", argv[0]);
            OsShellDhclientUsage();
        }
    } else {
        OsShellDhclientUsage();
    }

    return 0;
}

#ifdef LOSCFG_SHELL
SHELLCMD_ENTRY(dhclient_shellcmd, CMD_TYPE_EX, "dhclient", XARGS, (CmdCallBackFunc)OsShellDhclient);
#endif /* LOSCFG_SHELL */

#ifdef LWIP_DEBUG_TCPSERVER

#define MAX_SIZE 1024
void tcp_access(int sockfd)
{
  size_t n, i;
  ssize_t ret;
  char msg[MAX_SIZE] = {0};
  while (1) {
    PRINTK("waiting for recv\n");
    (void)memset_s(msg, MAX_SIZE, 0, MAX_SIZE);
    ret = recv(sockfd, msg, MAX_SIZE - 1, 0);
    if (ret < 0) {
      PRINTK("recv failed, %d.\n", (u32_t)ret);
      (void)closesocket(sockfd);
      return;
    } else if (ret == 0) {
      (void)closesocket(sockfd);
      PRINTK("client disconnect.\n");
      return;
    }

    n = strlen(msg);
    for (i = 0; i < n; ++i) {
      if (msg[i] >= 'a' && msg[i] <= 'z') {
        msg[i] = (char)(msg[i] + ('A' - 'a'));
      } else if (msg[i] >= 'A' && msg[i] <= 'Z') {
        msg[i] = (char)(msg[i] + ('a' - 'A'));
      }
    }

    if (send(sockfd, msg, n, 0) < 0) {
      PRINTK("send failed!\r\n");
      continue;
    }
  }
}

u32_t osTcpserver(int argc, const char **argv)
{
  uint16_t port;
  int sockfd = -1;
  int ret;
  struct sockaddr_in seraddr;
  struct sockaddr_in cliaddr;
  u32_t cliaddr_size = (u32_t)sizeof(cliaddr);
  int    reuse, iPortVal;

  if (tcpip_init_finish == 0) {
    PRINTK("tcpip_init have not been called\n");
    return LOS_NOK;
  }

  if (argc < 1 || argv == NULL) {
    PRINTK("\nUsage: tcpserver <port>\n");
    return LOS_NOK;
  }

  iPortVal = atoi(argv[0]);
  /* Port 0 not supported , negative values not supported , max port limit is 65535 */
  if (iPortVal <= 0 || iPortVal > 65535) {
    PRINTK("\nUsage: Invalid port\n");
    return LOS_NOK;
  }

  port = (uint16_t)iPortVal;

  /* removed the print of argv[1] as its accessing argv[1] without verifying argc and
   * argv[1] not used anywhere else */
  PRINTK("argv[0]:%s, argc:%d\r\n", argv[0], argc);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    PRINTK("\nUsage: create socket fail!\n");
    return LOS_NOK;
  }
  reuse = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof(reuse)) != 0) {
    (void)closesocket(sockfd);
    PRINTK("set SO_REUSEADDR failed\n");
    return LOS_NOK;
  }

  (void)memset_s(&seraddr, sizeof(seraddr), 0, sizeof(seraddr));
  seraddr.sin_family = AF_INET;
  seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  seraddr.sin_port = htons(port);

  ret = bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
  if (ret < 0) {
    PRINTK("bind ip and port failed");
    (void)closesocket(sockfd);
    return LOS_NOK;
  }

  ret = listen(sockfd, 5);
  if (ret < 0) {
    (void)closesocket(sockfd);
    PRINTK("listen failed\n");
    return LOS_NOK;
  }
  while (1) {
    PRINTK("waiting for accept\n");
    (void)memset_s(&cliaddr, sizeof(struct sockaddr_in), 0, sizeof(struct sockaddr_in));
    ret = (int)accept(sockfd, (struct sockaddr*)&cliaddr, &cliaddr_size);
    if (ret < 0) {
      (void)closesocket(sockfd);
      PRINTK("Accept failed, %d\n", ret);
      break ;
    }
    tcp_access(ret);
  }
  return LOS_NOK;            // Hits Only If Accept Fails
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(tcpserver_shellcmd, CMD_TYPE_EX, "tcpserver", XARGS, (CmdCallBackFunc)osTcpserver);
#endif /* LOSCFG_SHELL_CMD_DEBUG */
#endif /* LWIP_DEBUG_TCPSERVER */

#ifdef LWIP_DEBUG_UDPSERVER
void udpserver(int argc, const char **argv)
{
  int sockfd, fromlen;
  int ret, iPortVal;
  struct sockaddr_in seraddr;
  struct sockaddr_in cliaddr;
  size_t n, i;

  char msg[MAX_SIZE] = {0};
  uint16_t port;

  if (argc < 1) {
    PRINTK("\nUsage: udpserver <port>\n");
    return;
  }

  iPortVal = atoi(argv[0]);
  /* Port 0 not supported , negative values not supported , max port limit is 65535 */
  if (iPortVal <= 0 || iPortVal > 65535) {
    PRINTK("\nUsage: Invalid Port\n");
    return ;
  }

  port = (uint16_t)iPortVal;

  PRINTK("port:%d\r\n", port);

  sockfd = lwip_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd == -1) {
    PRINTK("\ncreate socket fail\n");
    return;
  }

  (void)memset_s(&seraddr, sizeof(seraddr), 0, sizeof(seraddr));
  (void)memset_s(&cliaddr, sizeof(cliaddr), 0, sizeof(cliaddr));
  seraddr.sin_family = AF_INET;
  seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  seraddr.sin_port = htons(port);
  ret = lwip_bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
  if (ret < 0) {
    PRINTK("bind ip and port failed:%d\n", errno);
    (void)closesocket(sockfd);
    return;
  }

  while(1) {
    ret = recvfrom(sockfd, msg, MAX_SIZE - 1, 0, (struct sockaddr *)&cliaddr, (socklen_t *)&fromlen);
    if (ret >= 0) {
      n = strlen(msg);
      for (i = 0; i < n; ++i) {
        if (msg[i] >= 'a' && msg[i] <= 'z') {
          msg[i] = (char)(msg[i] + 'A' - 'a');
        } else if (msg[i] >= 'A' && msg[i] <= 'Z') {
          msg[i] = (char)(msg[i] + 'a' - 'A');
        }
      }
      ret = sendto(sockfd, msg, n + 1, 0, (struct sockaddr *)&cliaddr, (socklen_t)fromlen);
      if (ret <= 0 && errno == EPIPE) {
        break;
      }
    } else {
      break;
    }
  }

  (void)closesocket(sockfd);
  return;
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(udpserver_shellcmd, CMD_TYPE_EX, "udpserver", XARGS, (CmdCallBackFunc)udpserver);
#endif /* LOSCFG_SHELL_CMD_DEBUG */
#endif /* LWIP_DEBUG_UDPSERVER */

#ifdef LWIP_DEBUG_INFO
LWIP_STATIC
u32_t netdebug_memp(int argc, const char **argv)
{
  u32_t ret = LOS_OK;
  int type;

  if (argc == 2) {
    if (!strcmp("-i", argv[1])) {
      debug_memp_info();
    } else if (!strcmp("-udp", argv[1])) {
      debug_memp_type_info(MEMP_UDP_PCB);
    } else if (!strcmp("-tcp", argv[1])) {
      debug_memp_type_info(MEMP_TCP_PCB);
    } else if (!strcmp("-raw", argv[1])) {
      debug_memp_type_info(MEMP_RAW_PCB);
    } else if (!strcmp("-conn", argv[1])) {
      debug_memp_type_info(MEMP_NETCONN);
    } else {
      ret = LOS_NOK;
    }
  } else if (argc == 3) {
    if (!strcmp("-d", argv[1])) {
      type = atoi(argv[2]);
      if (type >= 0) {
        debug_memp_detail(type);
      } else {
        PRINTK("Error: type < 0\n");
        ret = LOS_NOK;
      }
    } else {
      ret = LOS_NOK;
    }
  } else {
    ret = LOS_NOK;
  }

  return ret;
}

LWIP_STATIC
u32_t netdebug_sock(int argc, const char **argv)
{
  int idx;
  u32_t ret = LOS_NOK;

  if (argc == 2) {
    if (!strcmp("-i", argv[1])) {
      /* netdebug sock -i */
      for (idx = 0; idx < (int)LWIP_CONFIG_NUM_SOCKETS; idx++) {
        debug_socket_info(idx, 1, 0);
      }
      ret = LOS_OK;
    }
  } else if (argc == 3) {
    if (!strcmp("-d", argv[1])) {
      /* netdebug sock -d <idx> */
      idx = atoi(argv[2]);
      if (idx >= 0) {
        debug_socket_info(idx, 1, 1);
        ret = LOS_OK;
      } else {
        PRINTK("Error: idx < 0\n");
      }
    }
  }

  return ret;
}


u32_t osShellNetDebug(int argc, const char **argv)
{
  u32_t ret = LOS_NOK;

  if (argc < 1 || argv == NULL) {
    goto usage;
  }

  if (!strcmp("memp", argv[0])) {
    ret = netdebug_memp(argc, argv);
    if (ret != LOS_OK) {
      goto usage_memp;
    }
  } else if (!strcmp("sock", argv[0])) {
    /* netdebug sock {-i | -d <idx>} */
    ret = netdebug_sock(argc, argv);
    if (ret != LOS_OK) {
      goto usage_sock;
    }
  } else {
    goto usage;
  }
  return ret;

usage:
  /* Cmd help */
  PRINTK("\nUsage:\n");
  PRINTK("netdebug memp {-i | -d <type> | -udp | -tcp | -raw |-conn}\n");
  PRINTK("netdebug sock {-i | -d <idx>}\n");
  return LOS_NOK;

usage_memp:
  /* netdebug memp help */
  PRINTK("\nUsage:\n");
  PRINTK("netdebug memp {-i | -d <type> | -udp | -tcp | -raw |-conn}\n");
  return LOS_NOK;

usage_sock:
  /* netdebug sock help */
  PRINTK("\nUsage:\n");
  PRINTK("netdebug sock {-i | -d <idx>}\n");
  return LOS_NOK;
}
#endif /* LWIP_DEBUG_INFO */

#if defined(LOSCFG_SHELL_CMD_DEBUG) && defined(LWIP_DEBUG_INFO)
SHELLCMD_ENTRY(netdebug_shellcmd, CMD_TYPE_EX, "netdebug", XARGS, (CmdCallBackFunc)osShellNetDebug);
#endif /* LOSCFG_SHELL_CMD_DEBUG && LWIP_DEBUG_INFO */

u32_t osShellIpDebug(int argc, const char **argv)
{
    u8_t i = 0;
    char acIPv6Addr[IP6ADDR_STRLEN_MAX + 1] = {0};
    char aclladdr[20] = {0};
    const char *acStates[] = {"NO_ENTRY", "INCOMPLETE", "REACHABLE", "STALE", "DELAY", "PROBE"};
    u8_t atleastOneEntry = 0;

    if (!tcpip_init_finish) {
        PRINTK("%s: tcpip_init have not been called\n", __FUNCTION__);
        goto exit;
    }

    /* Display prefix */
    PRINTK("=================\n");
    PRINTK("|| Prefix List ||\n");
    PRINTK("=================\n");
    PRINTK("%-50s %-16s %-20s\n", "Prefix", "netif", "validLifetime");
    PRINTK("---------------------------------------------------------------------------------\n");
    /* Display neighbour Cache Entry */
    for (i = 0; i < LWIP_ND6_NUM_PREFIXES; i++) {
        if (prefix_list[i].netif != NULL && prefix_list[i].invalidation_timer > 0) {
            atleastOneEntry = 1;
            (void)ip6addr_ntoa_r((const ip6_addr_t *)(prefix_list[i].prefix.addr), (acIPv6Addr), INET6_ADDRSTRLEN);
            PRINTK("%-50s ", acIPv6Addr);
            PRINTK("%-16s ", netif_get_name(prefix_list[i].netif));
            PRINTK("%-20u\n", prefix_list[i].invalidation_timer);
        }
    }

    if (!atleastOneEntry) {
        PRINTK("**** NO VALID PREFIXES FOUND CONFIGURED ****\n");
    }
    PRINTK("---------------------------------------------------------------------------------\n");

    atleastOneEntry = 0;

    PRINTK("\n\n");
    PRINTK("============================\n");
    PRINTK("|| Neighbor Cache Entries ||\n");
    PRINTK("============================\n");
    PRINTK("%-50s %-25s %-16s %-15s %-10s\n", "Neighbor", "MAC", "netif", "state", "IsRouter");
    PRINTK("------------------------------------------------------------"
           "----------------------------------------------------------\n");

    /* Display neighbour Cache Entry */
    for (i = 0; i < LWIP_ND6_NUM_NEIGHBORS; i++) {
        if (neighbor_cache[i].state != ND6_NO_ENTRY) {
            atleastOneEntry = 1;
            (void)ip6addr_ntoa_r((const ip6_addr_t *)(neighbor_cache[i].next_hop_address.addr), (acIPv6Addr),
                                 INET6_ADDRSTRLEN);
            PRINTK("%-50s ", acIPv6Addr);

            if (snprintf_s(aclladdr, sizeof(aclladdr), sizeof(aclladdr) - 1, "%02X:%02X:%02X:%02X:%02X:%02X",
                           neighbor_cache[i].lladdr[0], neighbor_cache[i].lladdr[1], neighbor_cache[i].lladdr[2],
                           neighbor_cache[i].lladdr[3], neighbor_cache[i].lladdr[4], neighbor_cache[i].lladdr[5]) < 0) {
                return LOS_NOK;
            }
            PRINTK("%-25s ", aclladdr);
            PRINTK("%-16s ", netif_get_name(neighbor_cache[i].netif));
            PRINTK("%-15s ", acStates[neighbor_cache[i].state]);
            PRINTK("%-10s\n", (neighbor_cache[i].isrouter ? "Yes" : "No"));
        }
    }
    if (!atleastOneEntry) {
        PRINTK("**** NO NEIGHBOURS FOUND ****\n");
    }
    PRINTK("------------------------------------------------------------"
           "----------------------------------------------------------\n");

    atleastOneEntry = 0;

    PRINTK("\n\n");
    PRINTK("===============================\n");
    PRINTK("|| Destination Cache Entries ||\n");
    PRINTK("===============================\n");
    PRINTK("%-50s %-50s %-10s %-10s\n", "Destination", "NextHop", "PMTU", "age");
    PRINTK("------------------------------------------------------------"
           "--------------------------------------------------------\n");
    /* Display destination Cache Entry */
    for (i = 0; i < LWIP_ND6_NUM_DESTINATIONS; i++) {
        if (!ip6_addr_isany(&(destination_cache[i].destination_addr))) {
            atleastOneEntry = 1;
            (void)ip6addr_ntoa_r((const ip6_addr_t *)(destination_cache[i].destination_addr.addr), (acIPv6Addr),
                                 INET6_ADDRSTRLEN);
            PRINTK("%-50s ", acIPv6Addr);
            (void)ip6addr_ntoa_r((const ip6_addr_t *)(destination_cache[i].next_hop_addr.addr), (acIPv6Addr),
                                 INET6_ADDRSTRLEN);
            PRINTK("%-50s ", acIPv6Addr);
            PRINTK("%-10u ", destination_cache[i].pmtu);
            PRINTK("%-10u\n", destination_cache[i].age);
        }
    }
    if (!atleastOneEntry) {
        PRINTK("**** NO DESTINATION CACHE FOUND ****\n");
    }
    PRINTK("------------------------------------------------------------"
           "--------------------------------------------------------\n");

    atleastOneEntry = 0;
    PRINTK("\n\n");
    PRINTK("============================\n");
    PRINTK("|| Default Router Entries ||\n");
    PRINTK("============================\n");
    PRINTK("%-50s %-20s %-10s\n", "Router", "invalidation_timer", "flags");
    PRINTK("-----------------------------------------------------------------------------\n");
    /* Display Default Router Cache Entry */
    for (i = 0; i < LWIP_ND6_NUM_ROUTERS; i++) {
        if (default_router_list[i].neighbor_entry) {
            atleastOneEntry = 1;
            (void)ip6addr_ntoa_r((const ip6_addr_t *)((default_router_list[i].neighbor_entry)->next_hop_address.addr),
                                 (acIPv6Addr), INET6_ADDRSTRLEN);
            PRINTK("%-50s ", acIPv6Addr);
            PRINTK("%-20u ", default_router_list[i].invalidation_timer);
            PRINTK("%-10u\n", default_router_list[i].flags);
        }
    }
    if (!atleastOneEntry) {
        PRINTK("**** NO DEFAULT ROUTERS FOUND ****\n");
    }
    PRINTK("-----------------------------------------------------------------------------\n");

exit:
    return LOS_OK;
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(ipdebug_shellcmd, CMD_TYPE_EX, "ipdebug", XARGS, (CmdCallBackFunc)osShellIpDebug);
#endif
#ifdef LWIP_TESTBED
extern void cmd_reset(void);

void osShellReboot(int argc, const char **argv)
{
  cmd_reset();
}

#ifdef LOSCFG_SHELL_CMD_DEBUG
SHELLCMD_ENTRY(reboot_shellcmd, CMD_TYPE_EX, "reboot", XARGS, (CmdCallBackFunc)osShellReboot);
#endif /* LOSCFG_SHELL_CMD_DEBUG */
#endif

#endif //LWIP_ENABLE_LOS_SHELL_CMD
