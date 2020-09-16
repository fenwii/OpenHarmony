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
 * Description: shell cmds APIs declaration
 * Author: none
 * Create: 2013
 */

#ifndef LWIP_API_SHELL_H
#define LWIP_API_SHELL_H

#include "lwip/opt.h"
#include "lwip/netif.h"
#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

extern int tcpip_init_finish;
#ifndef PRINT_USE_CRLF
#define PRINT_USE_CRLF 1
#endif

#if PRINT_USE_CRLF
#define CRLF "\r\n"
#else
#define CRLF "\n"
#endif

/* help convert ptr to u32 array(if 64bit platfrom) */
union los_ptr_args {
  void *ptr;
  u32_t args[2];
};

typedef void (*icmp_code_hander)(u8_t code, void *arg);

#ifdef CUSTOM_AT_COMMAND
typedef enum netstat_trans_type {
  TCP_IP6,
  TCP,
  UDP_IP6,
  UDP,
  RAW,
  PKT_RAW,
} netstat_trans_type;
#endif

u32_t lwip_ifconfig(int argc, const char **argv);
u32_t lwip_get_ipv4(char *localIp, unsigned char ipLen, unsigned char *ifname);
u32_t lwip_get_mac_addr(unsigned char *macAddr, unsigned int len, unsigned char *ifname);

u32_t lwip_ifstats(int argc, char **argv);
u32_t lwip_arp(int argc, char **argv);
u32_t at_lwip_arp(int argc, char **argv);
u32_t os_shell_netif_up(int argc, char **argv);
u32_t os_shell_netif_down(int argc, char **argv);
u32_t os_shell_ping(int argc, const char **argv);
#if LWIP_IPV6
u32_t os_shell_ping6(int argc, const char **argv);
u32_t os_shell_ipdebug(int argc, char **argv);
#endif

#if LWIP_RPL || LWIP_RIPPLE
u32_t os_shell_rpl(int argc, char **argv);
u32_t os_rte_debug(int argc, char **argv);
#endif

u32_t os_shell_tftp(int argc, char **argv);
#if LWIP_SNTP
u32_t os_shell_ntpdate(int argc, char **argv);
#endif
#if LWIP_DNS
#ifdef CUSTOM_AT_COMMAND
u32_t os_shell_show_dns(void);
#endif
u32_t os_shell_dns(int argc, const char **argv);
#endif /* LWIP_DNS */
#if LWIP_IPV4 && LWIP_IGMP
u32_t os_shell_igmp(int argc, char **argv);
u32_t at_os_shell_igmp(int argc, char **argv);
#endif /* LWIP_IPV4 && LWIP_IGMP */
#if (LWIP_IPV6 && (LWIP_IPV6_MLD || LWIP_IPV6_MLD_QUERIER))
u32_t os_shell_mld6(int argc, char **argv);
#endif /* (LWIP_IPV6 && (LWIP_IPV6_MLD || LWIP_IPV6_MLD_QUERIER)) */
#if LWIP_DHCP
u32_t os_shell_dhcp(int argc, const char **argv);
void dhcp_clients_info_show(struct netif *netif_p);
#if LWIP_DHCPS
u32_t os_shell_dhcps(int argc, const char **argv);
void dhcps_info_show(struct netif *netif);
#endif /* LWIP_DHCPS */
#endif /* LWIP_DHCP */
u32_t os_shell_netstat(int argc, char **argv);

void netstat_internal(void *ctx);

u32_t os_shell_mcast6(int argc, char **argv);
#if LWIP_RIPPLE
u32_t os_shell_l2test(int argc, char **argv);
#endif /* LWIP_RIPPLE */

u32_t os_shell_netif(int argc, char **argv);

u32_t os_shell_display_version(int argc, char **argv);

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif

