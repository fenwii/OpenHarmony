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

#include <lwip/sockets.h>
#include <lwip/priv/tcpip_priv.h>
#include <api_shell_fix.h>

#if LWIP_ENABLE_NET_CAPABILITY
#include "capability_type.h"
#include "capability_api.h"
#define BIND_SERVICE_CAP_MIN_PORT 1024
#endif

#define netif_find netifapi_netif_find_by_name

#define IOCTL_CMD_CASE_HANDLER() \
    {                                                          \
        err_t  err;                                            \
        struct lwip_ioctl_apimsg msg;                          \
        msg.sock = sock;                                       \
        msg.cmd = cmd;                                         \
        msg.argp = argp;                                       \
                                                               \
        err = tcpip_api_call(lwip_do_ioctl_impl, &msg.call);   \
        if (err != ENOSYS) {                                   \
            sock_set_errno(sock, err);                         \
            done_socket(sock);                                 \
            return -(err != ERR_OK);                           \
        }                                                      \
    }

struct lwip_ioctl_apimsg {
    struct tcpip_api_call_data call;
    struct lwip_sock *sock;
    long cmd;
    void *argp;
};

static err_t lwip_do_ioctl_impl(struct tcpip_api_call_data *call);

static void poll_check_waiters(int s, int check_waiters);

static int lwip_socket_wrap(int domain, int type, int protocol);
int lwip_socket(int domain, int type, int protocol)
{
    return lwip_socket_wrap(domain, type, protocol);
}

static int lwip_setsockopt_wrap(int s, int level, int optname, const void *optval, socklen_t optlen);
int lwip_setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen)
{
    return lwip_setsockopt_wrap(s, level, optname, optval, optlen);
}

static int lwip_bind_wrap(int s, const struct sockaddr *name, socklen_t namelen);
int lwip_bind(int s, const struct sockaddr *name, socklen_t namelen)
{
    return lwip_bind_wrap(s, name, namelen);
}

static ssize_t lwip_sendto_wrap(int s, const void *dataptr, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);
ssize_t lwip_sendto(int s, const void *dataptr, size_t size, int flags, const struct sockaddr *to, socklen_t tolen)
{
    return lwip_sendto_wrap(s, dataptr, size, flags, to, tolen);
}

#ifdef lwip_socket
#undef lwip_socket
#endif
#define lwip_socket static lwip_socket2
static int lwip_socket2(int domain, int type, int protocol);

#ifdef lwip_setsockopt
#undef lwip_setsockopt
#endif
#define lwip_setsockopt static lwip_setsockopt2
static int lwip_setsockopt2(int s, int level, int optname, const void *optval, socklen_t optlen);

#ifdef lwip_bind
#undef lwip_bind
#endif
#define lwip_bind static lwip_bind2
static int lwip_bind2(int s, const struct sockaddr *name, socklen_t namelen);

#ifdef lwip_sendto
#undef lwip_sendto
#endif
#define lwip_sendto lwip_sendto2
ssize_t lwip_sendto2(int s, const void *dataptr, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);

#include "../api/sockets.c"

#undef lwip_socket
#undef lwip_setsockopt
#undef lwip_bind
#undef lwip_sendto

static int lwip_socket_wrap(int domain, int type, int protocol)
{
    if (domain != AF_INET && domain != AF_INET6) {
        set_errno(EAFNOSUPPORT);
        return -1;
    }
#if LWIP_ENABLE_NET_CAPABILITY
    if (type == SOCK_RAW && !IsCapPermit(CAP_NET_RAW)) {
        set_errno(EPERM);
        return -1;
    }
#endif
    return lwip_socket2(domain, type, protocol);
}

static int lwip_setsockopt_wrap(int s, int level, int optname, const void *optval, socklen_t optlen)
{
#if LWIP_ENABLE_NET_CAPABILITY
    if (level == SOL_SOCKET) {
        switch (optname) {
            case SO_BROADCAST:
                if (!IsCapPermit(CAP_NET_BROADCAST)) {
                    set_errno(EPERM);
                    return -1;
                }
                break;
            case SO_DEBUG:
            case SO_MARK:
            case SO_PRIORITY:
            case SO_RCVBUFFORCE:
            case SO_SNDBUFFORCE:
                if (!IsCapPermit(CAP_NET_ADMIN)) {
                    set_errno(EPERM);
                    return -1;
                }
                break;
            default:
                break;
        }
    }
#endif
    return lwip_setsockopt2(s, level, optname, optval, optlen);
}

#if LWIP_ENABLE_NET_CAPABILITY
static int ip_addr_isbroadcast_bysock(const ip_addr_t *ipaddr, int s)
{
    struct sockaddr sa;
    socklen_t salen = sizeof(sa);

    if (ipaddr == NULL) {
        return 0;
    }

    if (lwip_getsockname(s, &sa, &salen) == -1) {
        return 0;
    }

    ip_addr_t addr;
    u16_t port;

    SOCKADDR_TO_IPADDR_PORT(&sa, &addr, port);

    struct netif *netif = NULL;
    NETIF_FOREACH(netif) {
        if (ip_addr_cmp(&netif->ip_addr, &addr)) {
            return ip_addr_isbroadcast(ipaddr, netif);
        }
        for (int i = 0; i < LWIP_IPV6_NUM_ADDRESSES; i++) {
            if (ip_addr_cmp(&netif->ip6_addr[i], &addr)) {
                return ip_addr_isbroadcast(ipaddr, netif);
            }
        }
    }

    return 0;
}
#endif

static int lwip_bind_wrap(int s, const struct sockaddr *name, socklen_t namelen)
{
#if LWIP_ENABLE_NET_CAPABILITY
    if ((name->sa_family == AF_INET && namelen >= sizeof(struct sockaddr_in)) ||
        (name->sa_family == AF_INET6 && namelen >= sizeof(struct sockaddr_in6))) {
        ip_addr_t ipaddr;
        u16_t port;

        SOCKADDR_TO_IPADDR_PORT(name, &ipaddr, port);

        if (port != 0 && port < BIND_SERVICE_CAP_MIN_PORT) {
            LWIP_ERROR("permission deny: NET_BIND_SERVICE\n", IsCapPermit(CAP_NET_BIND_SERVICE),
                       set_errno(EPERM); return -1);
        }
        if (ip_addr_isany(&ipaddr)) {
            LWIP_ERROR("permission deny: NET_RAW\n", IsCapPermit(CAP_NET_RAW),
                       set_errno(EPERM); return -1);
            LWIP_ERROR("permission deny: NET_ADMIN\n", IsCapPermit(CAP_NET_ADMIN),
                       set_errno(EPERM); return -1);
        }
        if (ip_addr_ismulticast(&ipaddr) || ip_addr_isbroadcast_bysock(&ipaddr, s)) {
            LWIP_ERROR("permission deny: NET_BROADCAST\n", IsCapPermit(CAP_NET_BROADCAST),
                       set_errno(EPERM); return -1);
        }
    }
#endif

    return lwip_bind2(s, name, namelen);
}

static ssize_t lwip_sendto_wrap(int s, const void *dataptr, size_t size, int flags,
               const struct sockaddr *to, socklen_t tolen)
{
#if LWIP_ENABLE_NET_CAPABILITY
    if (to &&
        ((to->sa_family == AF_INET && tolen >= sizeof(struct sockaddr_in)) ||
        (to->sa_family == AF_INET6 && tolen >= sizeof(struct sockaddr_in6)))) {
        ip_addr_t ipaddr;
        u16_t port;

        SOCKADDR_TO_IPADDR_PORT(to, &ipaddr, port);

        if (ip_addr_ismulticast(&ipaddr) || ip_addr_isbroadcast_bysock(&ipaddr, s)) {
            LWIP_ERROR("permission deny: NET_BROADCAST\n", IsCapPermit(CAP_NET_BROADCAST),
                       set_errno(EPERM); return -1);
        }
    }
#endif

    return lwip_sendto2(s, dataptr, size, flags, to, tolen);
}

#if LWIP_SOCKET_SELECT || LWIP_SOCKET_POLL

struct file;
extern void poll_wait(struct file *filp, wait_queue_head_t *wait_address, poll_table *p);
extern void __wake_up_interruptible_poll(wait_queue_head_t *wait, pollevent_t key);

static void poll_check_waiters(int s, int check_waiters)
{
    unsigned long int_save, wq_empty;
    pollevent_t mask = 0;
    struct lwip_sock *sock;
    SYS_ARCH_DECL_PROTECT(lev);

    if (!check_waiters) {
        return;
    }

    sock = get_socket(s);
    if (!sock) {
        return;
    }

    SYS_ARCH_PROTECT(lev);

    mask |= (sock->rcvevent > 0) ? (POLLIN | POLLPRI | POLLRDNORM | POLLRDBAND) : 0;
    mask |= (sock->sendevent != 0) ? (POLLOUT | POLLWRNORM | POLLWRBAND) : 0;
    mask |= (sock->errevent != 0) ? (POLLERR) : 0;

    SYS_ARCH_UNPROTECT(lev);

    spin_lock_irqsave(&sock->wq.lock, int_save);
    wq_empty = LOS_ListEmpty(&(sock->wq.poll_queue));
    spin_unlock_irqrestore(&sock->wq.lock, int_save);

    if (mask && !wq_empty) {
        __wake_up_interruptible_poll(&sock->wq, mask);
    }

    done_socket(sock);
}

int socks_poll(int s, poll_table *wait)
{
    int ret;
    pollevent_t mask = 0;
    struct lwip_sock *sock;
    SYS_ARCH_DECL_PROTECT(lev);

    LWIP_ERROR("sock_poll: invalid poll_table", (wait != NULL), return -EINVAL;);

    sock = get_socket(s);
    if (!sock) {
        LWIP_DEBUGF(SOCKETS_DEBUG, ("sock_poll: Invalid socket"));
        set_errno(EBADF);
        return -EBADF; /* compatible with file poll */
    }

    SYS_ARCH_PROTECT(lev);

    mask |= (sock->rcvevent > 0 || sock->lastdata.pbuf) ? (POLLIN | POLLPRI | POLLRDNORM | POLLRDBAND) : 0;
    mask |= (sock->sendevent != 0) ? (POLLOUT | POLLWRNORM | POLLWRBAND) : 0;
    mask |= (sock->errevent != 0) ? (POLLERR) : 0;

    SYS_ARCH_UNPROTECT(lev);

    ret = wait->key & mask;
    if (!ret) {
        poll_wait(NULL, &sock->wq, wait);
    }

    done_socket(sock);
    return ret;
}

#endif /* LWIP_SOCKET_SELECT || LWIP_SOCKET_POLL */

#if !LWIP_COMPAT_SOCKETS

#define API_ALIAS(old, new) \
    extern __typeof(old) new __attribute__((__weak__, __alias__(#old)))

API_ALIAS(lwip_ioctl, ioctlsocket);

#endif /* !LWIP_COMPAT_SOCKETS */

#if LWIP_ENABLE_LOS_SHELL_CMD
/* get numbers of unused sockets */
int get_unused_socket_num(void)
{
    int unused = 0;
    SYS_ARCH_DECL_PROTECT(lev);

    SYS_ARCH_PROTECT(lev);

    for (int i = 0; i < NUM_SOCKETS; i++) {
        if (sockets[i].conn == NULL) {
#if LWIP_NETCONN_FULLDUPLEX
            if (sockets[i].fd_used) {
                continue;
            }
#endif
            unused++;
        }
    }

    SYS_ARCH_UNPROTECT(lev);

    return unused;
}
#endif

/**
 * socket ioctl
 */

// Options for lwip ioctl
#define LWIP_IOCTL_ROUTE                1
#define LWIP_IOCTL_IF                   1
#define LWIP_NETIF_PROMISC              1
#define LWIP_NETIF_ETHTOOL              0
#define LWIP_IOCTL_IPV6DPCTD            0
#undef LWIP_IPV6_DUP_DETECT_ATTEMPTS
#define LWIP_IPV6_DUP_DETECT_ATTEMPTS   0

#ifndef SIOCSIPV6DAD
#define SIOCSIPV6DAD _IOW('z', 0, unsigned long) /* set DAD enable/disable on netif */
#endif

#ifndef SIOCGIPV6DAD
#define SIOCGIPV6DAD _IOR('z', 1, unsigned long) /* get DAD status on netif */
#endif

#ifndef SIOCSIPV6DPCTD
#define SIOCSIPV6DPCTD _IOW('z', 2, unsigned long)
#endif

#ifndef SIOCGIPV6DPCTD
#define SIOCGIPV6DPCTD _IOR('z', 3, unsigned long)
#endif

#ifndef SIOCETHTOOL
#define SIOCETHTOOL 0x8946
#endif

#if LWIP_NETIF_PROMISC
#define NETIF_FLAG_PROMISC 0x80U
#endif /* LWIP_NETIF_PROMISC */


#if LWIP_IOCTL_ROUTE

#include <net/route.h>

static u8_t lwip_ioctl_internal_SIOCADDRT(struct rtentry *rmten)
{
    struct netif *netif = NULL;
    ip_addr_t rtgw_addr;
    u16_t rtgw_port;

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    SOCKADDR_TO_IPADDR_PORT(&rmten->rt_gateway, &rtgw_addr, rtgw_port);

    if (!IP_IS_V4_VAL(rtgw_addr)) {
        return EINVAL;
    }

    /* check if multicast/0/loopback */
    if (ip_addr_ismulticast(&rtgw_addr) || ip_addr_isany(&rtgw_addr) ||
        ip_addr_isloopback(&rtgw_addr)) {
        return EINVAL;
    }

    /* check if reachable */
    for (netif = netif_list; netif != NULL; netif = netif->next) {
        if (ip_addr_netcmp(&rtgw_addr, &netif->ip_addr, ip_2_ip4(&netif->netmask))) {
            break;
        }
    }

    if (netif == NULL) {
        return EHOSTUNREACH;
    }

    /* check if broadcast */
    if (ip_addr_isbroadcast(&rtgw_addr, netif) != 0) {
        return EINVAL;
    }

    /* Check flags */
    if ((rmten->rt_flags & RTF_GATEWAY) == 0) {
        return EINVAL;
    }

    /* Add validation */
    if ((netif_default != NULL) && (netif_default != netif)) {
        ip_addr_set_zero(&netif_default->gw);
        (void)netif_set_default(netif);
    }
    netif_set_gw(netif, ip_2_ip4(&rtgw_addr));

    return 0;
}

#endif

#if LWIP_IOCTL_IF

static u8_t lwip_ioctl_internal_SIOCGIFCONF(struct ifreq *ifr)
{
    struct ifconf *ifc = NULL;
    struct netif *netif = NULL;
    struct ifreq ifreq;
    struct sockaddr_in *sock_in = NULL;
    int pos;
    int len;
    int ret;

    /* Format the caller's buffer. */
    ifc = (struct ifconf *)ifr;
    len = ifc->ifc_len;

    /* Loop over the interfaces, and write an info block for each. */
    pos = 0;
    for (netif = netif_list; netif != NULL; netif = netif->next) {
        if (ifc->ifc_buf == NULL) {
            pos = (pos + (int)sizeof(struct ifreq));
            continue;
        }

        if (len < (int)sizeof(ifreq)) {
            break;
        }
        (void)memset_s(&ifreq, sizeof(struct ifreq), 0, sizeof(struct ifreq));
        if (netif->link_layer_type == LOOPBACK_IF) {
            ret = snprintf_s(ifreq.ifr_name, IFNAMSIZ, (IFNAMSIZ - 1), "%.2s", netif->name);
            if ((ret <= 0) || (ret >= IFNAMSIZ)) {
                LWIP_DEBUGF(NETIF_DEBUG, ("lwip_ioctl: snprintf_s ifr_name failed."));
                return ENOBUFS;
            }
        } else {
            ret = snprintf_s(ifreq.ifr_name, IFNAMSIZ, (IFNAMSIZ - 1), "%s", netif_get_name(netif));
            if ((ret <= 0) || (ret >= IFNAMSIZ)) {
                LWIP_DEBUGF(NETIF_DEBUG, ("lwip_ioctl: snprintf_s ifr_name failed."));
                return ENOBUFS;
            }
        }

        sock_in = (struct sockaddr_in *)&ifreq.ifr_addr;
        sock_in->sin_family = AF_INET;
        sock_in->sin_addr.s_addr = ip_2_ip4(&netif->ip_addr)->addr;
        if (memcpy_s(ifc->ifc_buf + pos, sizeof(struct ifreq), &ifreq, sizeof(struct ifreq)) != EOK) {
            return ENOBUFS;
        }
        pos = pos + (int)sizeof(struct ifreq);
        len = len - (int)sizeof(struct ifreq);
    }

    ifc->ifc_len = pos;

    return 0;
}

static u8_t lwip_ioctl_internal_SIOCGIFADDR(struct ifreq *ifr)
{
    struct netif *netif = NULL;
    struct sockaddr_in *sock_in = NULL;

    /* get netif ipaddr */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    } else {
        sock_in = (struct sockaddr_in *)&ifr->ifr_addr;
        sock_in->sin_family = AF_INET;
        sock_in->sin_addr.s_addr = ip_2_ip4(&netif->ip_addr)->addr;
        return 0;
    }
}

#ifndef LWIP_IPV6_PREFIX_LEN
#define LWIP_IPV6_PREFIX_LEN 64
#endif

#ifndef LWIP_NETIF_IFINDEX_MAX_EX
#define LWIP_NETIF_IFINDEX_MAX_EX 255
#endif

#include "lwip/dhcp.h"
#include "lwip/dhcp6.h"
#include "lwip/prot/dhcp.h"
#include "lwip/prot/dhcp6.h"

static u8_t lwip_ioctl_internal_SIOCSIFADDR_6(struct ifreq *ifr)
{
    (void)ifr;
    return ENOSYS;
}

static u8_t lwip_ioctl_internal_SIOCSIFADDR(struct ifreq *ifr)
{
    struct netif *netif = NULL;

    struct netif *loc_netif = NULL;
    ip_addr_t taget_addr;
    u16_t taget_port;
    SOCKADDR_TO_IPADDR_PORT(&ifr->ifr_addr, &taget_addr, taget_port);

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    /* set netif ipaddr */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    }
#if LWIP_HAVE_LOOPIF
    else if (netif->link_layer_type == LOOPBACK_IF) {
        return EPERM;
    }
#endif
    else {
        /* check the address is not multicast/broadcast/0/loopback */
        if (!IP_IS_V4(&taget_addr) || ip_addr_ismulticast(&taget_addr) ||
            ip_addr_isbroadcast(&taget_addr, netif) ||
            ip_addr_isany(&taget_addr) ||
            ip_addr_isloopback(&taget_addr)) {
            return EINVAL;
        }

        /* reset gateway if new and previous ipaddr not in same net */
        if (ip_addr_netcmp(&taget_addr, &netif->ip_addr, ip_2_ip4(&netif->netmask)) == 0) {
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
            if (ip_addr_cmp(&netif->netmask, &loc_netif->netmask) &&
                ip_addr_netcmp(&loc_netif->ip_addr, &taget_addr,
                               ip_2_ip4(&netif->netmask))) {
                return EINVAL;
            }
            loc_netif = loc_netif->next;
        }

#if LWIP_DHCP
        if ((netif_dhcp_data(netif) != NULL) &&
            (netif_dhcp_data(netif)->state != DHCP_STATE_OFF)) {
            (void)netif_dhcp_off(netif);
        }
#endif

#if LWIP_ARP
        /* clear ARP cache when IP address changed */
        if ((netif->flags & NETIF_FLAG_ETHARP) != 0) {
            etharp_cleanup_netif(netif);
        }
#endif /* LWIP_ARP */

        netif_set_ipaddr(netif, ip_2_ip4(&taget_addr));

        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCDIFADDR_6(struct ifreq *ifr)
{
    (void)ifr;
    return ENOSYS;
}

static u8_t lwip_ioctl_internal_SIOCDIFADDR(struct ifreq *ifr)
{
    struct netif *netif = NULL;

    ip_addr_t target_addr;
    u16_t target_port;

    SOCKADDR_TO_IPADDR_PORT(&ifr->ifr_addr, &target_addr, target_port);

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    /* set netif ipaddr */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    }
#if LWIP_HAVE_LOOPIF
    else if (netif->link_layer_type == LOOPBACK_IF) {
        return EPERM;
    }
#endif

    /* check the address is not loopback */
    if (!IP_IS_V4(&target_addr) || ip_addr_isloopback(&target_addr)) {
        return EINVAL;
    }

#if LWIP_DHCP
    if ((netif_dhcp_data(netif) != NULL) &&
        (netif_dhcp_data(netif)->state != DHCP_STATE_OFF)) {
        (void)netif_dhcp_off(netif);
    }
#endif

    ip_addr_set_zero(&netif->gw);
    ip_addr_set_zero(&netif->ip_addr);
    ip_addr_set_zero(&netif->netmask);
    if (netif == netif_default) {
        (void)netif_set_default(NULL);
    }

#if LWIP_IPV4 && LWIP_ARP
    if ((netif->flags & NETIF_FLAG_ETHARP) != 0) {
        etharp_cleanup_netif(netif);
    }
#endif /* LWIP_IPV4 && LWIP_ARP */

    return ERR_OK;
}

static u8_t lwip_ioctl_internal_SIOCGIFNETMASK(struct ifreq *ifr)
{
    struct netif *netif = NULL;
    struct sockaddr_in *sock_in = NULL;

    /* get netif netmask */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    } else {
        sock_in = (struct sockaddr_in *)&ifr->ifr_netmask;
        sock_in->sin_family = AF_INET;
        sock_in->sin_addr.s_addr = ip_2_ip4(&netif->netmask)->addr;
        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCSIFNETMASK(struct ifreq *ifr)
{
    struct netif *netif = NULL;

    struct netif *loc_netif = NULL;
    ip_addr_t taget_addr;
    u16_t taget_port;
    SOCKADDR_TO_IPADDR_PORT(&ifr->ifr_addr, &taget_addr, taget_port);

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    if (!IP_IS_V4(&taget_addr)) {
        return EINVAL;
    }

    /* set netif netmask */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    }
#if LWIP_HAVE_LOOPIF
    else if (netif->link_layer_type == LOOPBACK_IF) {
        return EPERM;
    }
#endif
    else {
        if (ip_addr_cmp(&netif->netmask, &taget_addr)) {
            return 0;
        }
        /* check data valid */
        if (ip_addr_netmask_valid(ip_2_ip4(&taget_addr)) != 0) {
            return EINVAL;
        }

        /* lwip disallow two netif sit in same net at the same time */
        loc_netif = netif_list;
        while (loc_netif != NULL) {
            if (loc_netif == netif) {
                loc_netif = loc_netif->next;
                continue;
            }
            if (ip_addr_cmp(&loc_netif->netmask, &taget_addr) &&
                ip_addr_netcmp(&loc_netif->ip_addr,
                               &netif->ip_addr, ip_2_ip4(&loc_netif->netmask))) {
                return EINVAL;
            }
            loc_netif = loc_netif->next;
        }

#if LWIP_DHCP // LWIP_DHCP
        if ((netif_dhcp_data(netif) != NULL) &&
            (netif_dhcp_data(netif)->state != DHCP_STATE_OFF)) {
            (void)netif_dhcp_off(netif);
        }
#endif

        netif_set_netmask(netif, ip_2_ip4(&taget_addr));

        /* check if gateway still reachable */
        if (!ip_addr_netcmp(&netif->gw, &netif->ip_addr, ip_2_ip4(&taget_addr))) {
            ip_addr_set_zero(&(netif->gw));
            if (netif == netif_default) {
                (void)netif_set_default(NULL);
            }
        }
        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCSIFHWADDR(struct ifreq *ifr)
{
    struct netif *netif = NULL;
    err_t ret;

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    /* set netif hw addr */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    }
#if LWIP_HAVE_LOOPIF
    else if (netif->link_layer_type == LOOPBACK_IF) {
        return EPERM;
    }
#endif
    else {

        /* bring netif down to clear all Neighbor Cache Entry */
        (void)netif_set_down(netif);

        ret = netif_set_hwaddr(netif, (const unsigned char *)ifr->ifr_hwaddr.sa_data, netif->hwaddr_len);

        if (ret != ERR_OK) {
            (void)netif_set_up(netif);
            return err_to_errno(ret);
        }

        /*
         * bring netif up to try to send GARP/IGMP/NA/MLD/RS. GARP and NA would
         * make the neighboring nodes update their Neighbor Cache immediately.
         */
        (void)netif_set_up(netif);
        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCGIFHWADDR(struct ifreq *ifr)
{
    struct netif *netif = NULL;

    /* get netif hw addr */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    }
#if LWIP_HAVE_LOOPIF
    else if (netif->link_layer_type == LOOPBACK_IF) {
        return EPERM;
    }
#endif /* LWIP_HAVE_LOOPIF */
    else {
        if (memcpy_s((void *)ifr->ifr_hwaddr.sa_data, sizeof(ifr->ifr_hwaddr.sa_data),
                     (void *)netif->hwaddr, netif->hwaddr_len) != EOK) {
            return EINVAL;
        }
        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCSIFFLAGS(struct ifreq *ifr)
{
    struct netif *netif = NULL;

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    /* set netif hw addr */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    }
#if LWIP_HAVE_LOOPIF
    else if (netif->link_layer_type == LOOPBACK_IF) {
        return EPERM;
    }
#endif /* LWIP_HAVE_LOOPIF */
    else {
        if (((unsigned short)ifr->ifr_flags & IFF_UP) && !(netif->flags & NETIF_FLAG_UP)) {
            (void)netif_set_up(netif);
        } else if (!((unsigned short)ifr->ifr_flags & IFF_UP) && (netif->flags & NETIF_FLAG_UP)) {
            (void)netif_set_down(netif);
        }
        if (((unsigned short)ifr->ifr_flags & IFF_RUNNING) && !(netif->flags & NETIF_FLAG_LINK_UP)) {
            (void)netif_set_link_up(netif);
        } else if (!((unsigned short)ifr->ifr_flags & IFF_RUNNING) && (netif->flags & NETIF_FLAG_LINK_UP)) {
            (void)netif_set_link_down(netif);
        }

        if ((unsigned short)ifr->ifr_flags & IFF_BROADCAST) {
            netif->flags |= NETIF_FLAG_BROADCAST;
        } else {
            netif->flags = netif->flags & (~NETIF_FLAG_BROADCAST);
        }
        if ((unsigned short)ifr->ifr_flags & IFF_NOARP) {
            netif->flags = (netif->flags & (~NETIF_FLAG_ETHARP));
        } else {
            netif->flags |= NETIF_FLAG_ETHARP;
        }

        if ((unsigned short)ifr->ifr_flags & IFF_MULTICAST) {
#if LWIP_IGMP
            netif->flags |= NETIF_FLAG_IGMP;
#endif /* LWIP_IGMP */
#if LWIP_IPV6 && LWIP_IPV6_MLD
            netif->flags |= NETIF_FLAG_MLD6;
#endif /* LWIP_IPV6_MLD */
        } else {
#if LWIP_IGMP
            netif->flags = (netif->flags & ~NETIF_FLAG_IGMP);
#endif /* LWIP_IGMP */
#if LWIP_IPV6 && LWIP_IPV6_MLD
            netif->flags = (netif->flags & ~NETIF_FLAG_MLD6);
#endif /* LWIP_IPV6_MLD */
        }

#if LWIP_DHCP
        if ((unsigned short)ifr->ifr_flags & IFF_DYNAMIC) {
            (void)dhcp_start(netif);
        } else {
            dhcp_stop(netif);
#if !LWIP_DHCP_SUBSTITUTE
            dhcp_cleanup(netif);
#endif
        }
#endif

#if LWIP_NETIF_PROMISC
        if (((unsigned short)ifr->ifr_flags & IFF_PROMISC)) {
            netif->flags |= NETIF_FLAG_PROMISC;
        } else {
            netif->flags &= ~NETIF_FLAG_PROMISC;
        }
        if (netif->drv_config) {
            netif->drv_config(netif, IFF_PROMISC, !!((unsigned short)ifr->ifr_flags & IFF_PROMISC));
        }
#endif /* LWIP_NETIF_PROMISC */
        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCGIFFLAGS(struct ifreq *ifr)
{
    struct netif *netif = NULL;

    /* set netif hw addr */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    } else {
        if (netif->flags & NETIF_FLAG_UP) {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) | IFF_UP;
        } else {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) & ~IFF_UP;
        }
        if (netif->flags & NETIF_FLAG_LINK_UP) {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) | IFF_RUNNING;
        } else {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) & ~IFF_RUNNING;
        }
        if (netif->flags & NETIF_FLAG_BROADCAST) {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) | IFF_BROADCAST;
        } else {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) & ~IFF_BROADCAST;
        }
        if (netif->flags & NETIF_FLAG_ETHARP) {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) & ~IFF_NOARP;
        } else {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) | IFF_NOARP;
        }

#if LWIP_IGMP || LWIP_IPV6_MLD
        if (
#if LWIP_IGMP
            (netif->flags & NETIF_FLAG_IGMP)
#endif /* LWIP_IGMP */
#if LWIP_IGMP && LWIP_IPV6_MLD
            ||
#endif /* LWIP_IGMP && LWIP_IPV6_MLD */
#if LWIP_IPV6_MLD
            (netif->flags & NETIF_FLAG_MLD6)
#endif /* LWIP_IPV6_MLD */
                ) {
            ifr->ifr_flags = (short)((unsigned short)ifr->ifr_flags | IFF_MULTICAST);
        } else {
            ifr->ifr_flags = (short)((unsigned short)ifr->ifr_flags & (~IFF_MULTICAST));
        }
#endif /* LWIP_IGMP || LWIP_IPV6_MLD */

#if LWIP_DHCP
        //if ((netif->flags & NETIF_FLAG_DHCP) != 0) {
        if (dhcp_supplied_address(netif)) {
            ifr->ifr_flags = (short)((unsigned short)ifr->ifr_flags | IFF_DYNAMIC);
        } else {
            ifr->ifr_flags = (short)((unsigned short)ifr->ifr_flags & (~IFF_DYNAMIC));
        }
#endif

#if LWIP_HAVE_LOOPIF
        if (netif->link_layer_type == LOOPBACK_IF) {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) | IFF_LOOPBACK;
        }
#endif

#if LWIP_NETIF_PROMISC
        if (netif->flags & NETIF_FLAG_PROMISC) {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) | IFF_PROMISC;
        } else {
            ifr->ifr_flags = ((unsigned short)(ifr->ifr_flags)) & ~IFF_PROMISC;
        }
#endif /* LWIP_NETIF_PROMISC */

        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCGIFNAME(struct ifreq *ifr)
{
    struct netif *netif = NULL;
    int ret;

    for (netif = netif_list; netif != NULL; netif = netif->next) {
        if (ifr->ifr_ifindex == netif_get_index(netif)) {
            break;
        }
    }

    if (netif == NULL) {
        return ENODEV;
    } else {
        if (netif->link_layer_type == LOOPBACK_IF) {
            ret = snprintf_s(ifr->ifr_name, IFNAMSIZ, (IFNAMSIZ - 1), "%.2s", netif->name);
            if ((ret <= 0) || (ret >= IFNAMSIZ)) {
                return ENOBUFS;
            }
        } else {
            ret = snprintf_s(ifr->ifr_name, IFNAMSIZ, (IFNAMSIZ - 1), "%s", netif_get_name(netif));
            if ((ret <= 0) || (ret >= IFNAMSIZ)) {
                return ENOBUFS;
            }
        }
        return 0;
    }
}

static bool lwip_validate_ifname(const char *name, u8_t *let_pos)
{
    unsigned short num_pos = 0;
    unsigned short letter_pos = 0;
    unsigned short pos = 0;
    bool have_num = 0;

    /* if the first position of variable name is not letter, such as '6eth2' */
    if (((*name >= 'a') && (*name <= 'z')) || ((*name >= 'A') && (*name <= 'Z'))) {
        return 0;
    }

    /* check if the position of letter is bigger than the the position of digital */
    while (*name != '\0') {
        if ((*name >= '0') && (*name <= '9')) {
            num_pos = pos;
            have_num = 1;
        } else if (((*name >= 'a') && (*name <= 'z')) || ((*name >= 'A') && (*name <= 'Z'))) {
            letter_pos = pos;
            if (have_num != 0) {
                return 0;
            }
        } else {
            return 0;
        }
        pos++;
        name++;
    }

    /* for the speacil case as all position of variable name is letter, such as 'ethabc' */
    if (num_pos == 0) {
        return 0;
    }

    /* cheak if the digital in the variable name is bigger than 255, such as 'eth266' */
    if (atoi(name - (pos - letter_pos - 1)) > 255) {
        return 0;
    }

    *let_pos = (u8_t)letter_pos;

    return 1;
}

static u8_t lwip_ioctl_internal_SIOCSIFNAME(struct ifreq *ifr)
{
    struct netif *netif = NULL;
    u8_t letter_pos = 0;

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    netif = netif_find(ifr->ifr_name);

    if (netif == NULL) {
        return ENODEV;
    } else if (netif->link_layer_type == LOOPBACK_IF) {
        return EPERM;
    } else if ((netif->flags & IFF_UP) != 0) {
        return EBUSY;
    } else {
        if (strncmp(ifr->ifr_name, ifr->ifr_newname, IFNAMSIZ) == 0) {
            /* not change */
            return 0;
        }

        ifr->ifr_newname[IFNAMSIZ - 1] = '\0';
        if ((lwip_validate_ifname(ifr->ifr_newname, &letter_pos) == 0) || (strlen(ifr->ifr_newname) > (IFNAMSIZ - 1))) {
            return EINVAL;
        }

        if (strncpy_s(netif->full_name, sizeof(netif->full_name), ifr->ifr_newname, strlen(ifr->ifr_newname)) != EOK) {
            return EINVAL;
        }
    }

    return 0;
}

static u8_t lwip_ioctl_internal_SIOCGIFINDEX(struct ifreq *ifr)
{
    struct netif *netif = NULL;

    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    } else {
        ifr->ifr_ifindex = netif_get_index(netif);
        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCSIFMTU(struct ifreq *ifr)
{
    struct netif *netif = NULL;

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    /* set netif hw addr */
    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    }
#if LWIP_HAVE_LOOPIF
        /* the mtu of loopif is not used. */
    else if (netif->link_layer_type == LOOPBACK_IF) {
        return EPERM;
    }
#endif
    else {
        if (ERR_OK != netif_set_mtu(netif, (u16_t)ifr->ifr_mtu)) {
            return EINVAL;
        }

        return 0;
    }
}

static u8_t lwip_ioctl_internal_SIOCGIFMTU(struct ifreq *ifr)
{
    struct netif *netif = NULL;

    /* get netif hw addr */
    netif = netif_find(ifr->ifr_name);

    if (netif == NULL) {
        return ENODEV;
    } else {
        ifr->ifr_mtu = netif->mtu;
        return 0;
    }
}

#endif /* LWIP_IOCTL_IF */

#if LWIP_NETIF_ETHTOOL

static s32_t lwip_ioctl_internal_SIOCETHTOOL(struct ifreq *ifr)
{
    struct netif *netif;

#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    netif = netif_find(ifr->ifr_name);
    if (netif == NULL) {
        return ENODEV;
    } else {
        return dev_ethtool(netif, ifr);
    }
}

#endif

#if LWIP_IPV6
#if LWIP_IPV6_DUP_DETECT_ATTEMPTS

static u8_t lwip_ioctl_internal_SIOCSIPV6DAD(struct ifreq *ifr)
{
#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    struct netif *tmpnetif = netif_find(ifr->ifr_name);
    if (tmpnetif == NULL) {
        LWIP_DEBUGF(SOCKETS_DEBUG, ("Interface not found.\n"));
        return ENODEV;
    }

    if ((ifr->ifr_ifru.ifru_ivalue != 0) && (ifr->ifr_ifru.ifru_ivalue != 1)) {
        LWIP_DEBUGF(SOCKETS_DEBUG, ("Invalid ioctl argument(ifru_ivalue 0/1).\n"));
        return EBADRQC;
    }

    if (ifr->ifr_ifru.ifru_ivalue == 1) {
        tmpnetif->ipv6_flags = (tmpnetif->ipv6_flags | LWIP_IPV6_ND6_FLAG_DAD);

        LWIP_DEBUGF(SOCKETS_DEBUG, ("DAD turned on through ioctl for  %s iface index %u \n",
                tmpnetif->name, tmpnetif->num));
    } else {
        tmpnetif->ipv6_flags = (tmpnetif->ipv6_flags & ((~LWIP_IPV6_ND6_FLAG_DAD) & 0xffU));

        LWIP_DEBUGF(SOCKETS_DEBUG, ("DAD turned off through ioctl for  %s iface index %u \n",
                tmpnetif->name, tmpnetif->num));
    }
    return 0;
}

static u8_t lwip_ioctl_internal_SIOCGIPV6DAD(struct ifreq *ifr)
{
    struct netif *tmpnetif = netif_find(ifr->ifr_name);
    if (tmpnetif == NULL) {
        LWIP_DEBUGF(SOCKETS_DEBUG, ("Interface not found.\n"));
        return ENODEV;
    }
    ifr->ifr_ifru.ifru_ivalue = (tmpnetif->ipv6_flags & LWIP_IPV6_ND6_FLAG_DAD) ? 1 : 0;
    return 0;
}

#endif

#if LWIP_IOCTL_IPV6DPCTD

static u8_t lwip_ioctl_internal_SIOCSIPV6DPCTD(struct ifreq *ifr)
{
#if LWIP_ENABLE_NET_CAPABILITY
    if (!IsCapPermit(CAP_NET_ADMIN)) {
        return EPERM;
    }
#endif

    struct netif *tmpnetif = netif_find(ifr->ifr_name);
    if (tmpnetif == NULL) {
        LWIP_DEBUGF(SOCKETS_DEBUG, ("Interface not found.\n"));
        return ENODEV;
    }
    if ((ifr->ifr_ifru.ifru_ivalue != 0) && (ifr->ifr_ifru.ifru_ivalue != 1)) {
        LWIP_DEBUGF(SOCKETS_DEBUG, ("Invalid ioctl argument(ifru_ivalue 0/1).\n"));
        return EBADRQC;
    }
    if (ifr->ifr_ifru.ifru_ivalue == 1) {
        tmpnetif->ipv6_flags = (tmpnetif->ipv6_flags | LWIP_IPV6_ND6_FLAG_DEPRECATED);
        LWIP_DEBUGF(SOCKETS_DEBUG, ("Deprecation turned on through ioctl for  %s iface index %u \n",
                tmpnetif->name, tmpnetif->num));
    } else {
        tmpnetif->ipv6_flags = (tmpnetif->ipv6_flags & ((~LWIP_IPV6_ND6_FLAG_DEPRECATED) & 0xffU));
        LWIP_DEBUGF(SOCKETS_DEBUG, ("Deprecation turned off through ioctl for  %s iface index %u \n",
                tmpnetif->name, tmpnetif->num));
    }
    return 0;
}

static u8_t lwip_ioctl_internal_SIOCGIPV6DPCTD(struct ifreq *ifr)
{
    struct netif *tmpnetif = netif_find(ifr->ifr_name);
    if (tmpnetif == NULL) {
        LWIP_DEBUGF(SOCKETS_DEBUG, ("Interface not found.\n"));
        return ENODEV;
    }

    ifr->ifr_ifru.ifru_ivalue = (tmpnetif->ipv6_flags & LWIP_IPV6_ND6_FLAG_DEPRECATED) ? 1 : 0;
    return 0;
}

#endif /* LWIP_IOCTL_IPV6DPCTD */
#endif

static u8_t lwip_ioctl_impl(const struct lwip_sock *sock, long cmd, void *argp)
{
    u8_t err = 0;
#if LWIP_NETIF_ETHTOOL
    s32_t ret;
#endif
#if LWIP_IPV6_DUP_DETECT_ATTEMPTS || LWIP_IOCTL_IPV6DPCTD || LWIP_IOCTL_IF || LWIP_NETIF_ETHTOOL
    struct ifreq *ifr = (struct ifreq *)argp;
#endif
#if LWIP_IOCTL_ROUTE
    struct rtentry *rmten = (struct rtentry *)argp;
#endif
#if LWIP_IPV6_DUP_DETECT_ATTEMPTS || LWIP_IOCTL_IPV6DPCTD || LWIP_IOCTL_ROUTE || LWIP_IOCTL_IF
    bool is_ipv6 = 0;

    /* allow it only on IPv6 sockets... */
    is_ipv6 = NETCONNTYPE_ISIPV6((unsigned int)(sock->conn->type));
#endif

    switch ((u32_t)cmd) {
#if LWIP_IPV6
#if LWIP_IPV6_DUP_DETECT_ATTEMPTS
        case SIOCSIPV6DAD:
            /* allow it only on IPv6 sockets... */
            if (is_ipv6 == 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCSIPV6DAD(ifr);
            }
            break;
        case SIOCGIPV6DAD:
            /* allow it only on IPv6 sockets... */
            if (is_ipv6 == 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCGIPV6DAD(ifr);
            }
            break;
#endif /* LWIP_IPV6_DUP_DETECT_ATTEMPTS */
#if LWIP_IOCTL_IPV6DPCTD
        case SIOCSIPV6DPCTD:
            /* allow it only on IPv6 sockets... */
            if (is_ipv6 == 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCSIPV6DPCTD(ifr);
            }
            break;
        case SIOCGIPV6DPCTD:
            /* allow it only on IPv6 sockets... */
            if (is_ipv6 == 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCGIPV6DPCTD(ifr);
            }
            break;
#endif
#endif /* LWIP_IPV6 */
#if LWIP_IOCTL_ROUTE
        case SIOCADDRT:
            /* Do not allow if socket is AF_INET6 */
            if (is_ipv6 != 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCADDRT(rmten);
            }
            break;
#endif
#if LWIP_IOCTL_IF
        case SIOCGIFCONF:
            /* Do not allow if socket is AF_INET6 */
            if (is_ipv6 != 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCGIFCONF(ifr);
            }
            break;
        case SIOCGIFADDR:
            if (is_ipv6 != 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCGIFADDR(ifr);
            }
            break;
        case SIOCSIFADDR:
            if (is_ipv6 != 0) {
                err = lwip_ioctl_internal_SIOCSIFADDR_6(ifr);
            } else {
                err = lwip_ioctl_internal_SIOCSIFADDR(ifr);
            }
            break;
        case SIOCDIFADDR:
            /* Delete interface address */
            if (is_ipv6 != 0) {
                err = lwip_ioctl_internal_SIOCDIFADDR_6(ifr);
            } else {
                err = lwip_ioctl_internal_SIOCDIFADDR(ifr);
            }
            break;
        case SIOCGIFNETMASK:
            if (is_ipv6 != 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCGIFNETMASK(ifr);
            }
            break;
        case SIOCSIFNETMASK:
            if (is_ipv6 != 0) {
                err = EINVAL;
            } else {
                err = lwip_ioctl_internal_SIOCSIFNETMASK(ifr);
            }
            break;
        case SIOCSIFHWADDR:
            err = lwip_ioctl_internal_SIOCSIFHWADDR(ifr);
            break;
        case SIOCGIFHWADDR:
            err = lwip_ioctl_internal_SIOCGIFHWADDR(ifr);
            break;
        case SIOCSIFFLAGS:
            err = lwip_ioctl_internal_SIOCSIFFLAGS(ifr);
            break;
        case SIOCGIFFLAGS:
            err = lwip_ioctl_internal_SIOCGIFFLAGS(ifr);
            break;
        case SIOCGIFNAME:
            err = lwip_ioctl_internal_SIOCGIFNAME(ifr);
            break;
        case SIOCSIFNAME:
            err = lwip_ioctl_internal_SIOCSIFNAME(ifr);
            break;
            /* Need to support the get index through ioctl
             * As of now the options is restricted to PF_PACKET scenario , so removed the compiler flag Begin
             */
        case SIOCGIFINDEX:
            err = lwip_ioctl_internal_SIOCGIFINDEX(ifr);
            break;
        case SIOCGIFMTU:
            err = lwip_ioctl_internal_SIOCGIFMTU(ifr);
            break;
        case SIOCSIFMTU:
            err = lwip_ioctl_internal_SIOCSIFMTU(ifr);
            break;
#endif /* LWIP_IOCTL_IF */
#if LWIP_NETIF_ETHTOOL
        case SIOCETHTOOL:
            ret = lwip_ioctl_internal_SIOCETHTOOL(ifr);
            if (ret != 0) {
                /* an IO error happened */
                err = EIO;
            }
            break;
#endif
            /* START For cmd = -1 stack has to treat it as Invalid Input and return EINVAL */
        case 0xFFFFFFFF:
            err = EINVAL;
            LWIP_DEBUGF(SOCKETS_DEBUG, ("lwip_ioctl_impl(INVALID: 0x%lx)\n", cmd));
            break;
        default:
            err = ENOSYS;
            LWIP_DEBUGF(SOCKETS_DEBUG, ("lwip_ioctl(UNIMPL: 0x%lx)\n", cmd));
            break;
    }

    return err;
}

static err_t lwip_do_ioctl_impl(struct tcpip_api_call_data *call)
{
    struct lwip_ioctl_apimsg *msg = (struct lwip_ioctl_apimsg *)(void *)call;
    return lwip_ioctl_impl(msg->sock, msg->cmd, msg->argp);
}

#include "los_vm_map.h"
#include "user_copy.h"
int socks_ioctl(int sockfd, long cmd, void *argp)
{
    void *argpbak = argp;
    int ret;
    size_t nbytes = 0;

    if (LOS_IsUserAddress((VADDR_T)(uintptr_t)argp)) {
        switch (cmd) {
            case FIONREAD:
            case FIONBIO:
                nbytes = sizeof(int);
                break;
            case SIOCADDRT:
                nbytes = sizeof(struct rtentry);
                break;
            case SIOCSIPV6DAD:
            case SIOCGIPV6DAD:
            case SIOCSIPV6DPCTD:
            case SIOCGIPV6DPCTD:
            case SIOCGIFCONF:
            case SIOCGIFADDR:
            case SIOCSIFADDR:
            case SIOCDIFADDR:
            case SIOCGIFNETMASK:
            case SIOCSIFNETMASK:
            case SIOCSIFHWADDR:
            case SIOCGIFHWADDR:
            case SIOCSIFFLAGS:
            case SIOCGIFFLAGS:
            case SIOCGIFNAME:
            case SIOCSIFNAME:
            case SIOCGIFINDEX:
            case SIOCGIFMTU:
            case SIOCSIFMTU:
            case SIOCETHTOOL:
                nbytes = sizeof(struct ifreq);
                break;
            default:
                nbytes = 0;
        }
        if (argp != NULL && nbytes > 0) {
            argp = malloc(nbytes);
            if (argp == NULL) {
                set_errno(ENOMEM);
                return -1;
            }
            if (LOS_ArchCopyFromUser(argp, argpbak, nbytes) != 0) {
                free(argp);
                set_errno(EFAULT);
                return -1;
            }
        }
    }
    ret = lwip_ioctl(sockfd, cmd, argp);
    if (ret == 0 && argp != argpbak) {
        if (LOS_ArchCopyToUser(argpbak, argp, nbytes) != 0) {
            /* how to rollback ioctl ? */
            set_errno(EFAULT);
            ret = -1;
        }
    }
    if (argp != argpbak) {
        free(argp);
    }
    return ret;
}

void socks_refer(int sockfd)
{
    struct lwip_sock *sock = NULL;
    SYS_ARCH_DECL_PROTECT(lev);

    sock = get_socket(sockfd);
    if (!sock) {
        return;
    }

    SYS_ARCH_PROTECT(lev);

    sock->s_refcount++;

    SYS_ARCH_UNPROTECT(lev);

    done_socket(sock);
}

int socks_close(int sockfd)
{
    struct lwip_sock *sock = NULL;
    SYS_ARCH_DECL_PROTECT(lev);

    sock = get_socket(sockfd);
    if (!sock) {
        return -1;
    }

    SYS_ARCH_PROTECT(lev);

    if (sock->s_refcount == 0) {
        SYS_ARCH_UNPROTECT(lev);
        done_socket(sock);
        return lwip_close(sockfd);
    }

    sock->s_refcount--;

    SYS_ARCH_UNPROTECT(lev);
    done_socket(sock);
    return 0;
}
