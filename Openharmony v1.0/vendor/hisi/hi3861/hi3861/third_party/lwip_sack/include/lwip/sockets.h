/**
 * @file
 * Socket API (to be used from non-TCPIP threads)
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 * Copyright (c) <2013-2016>, <Huawei Technologies Co., Ltd>
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
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
/** @mainpage RFC Compliance
 *  The following pages provide information about RFC Compliance.
 *  - Click the RFC number for more information about limitations or RFC implementation.
 *  - @subpage RFC-2292
 *  - @subpage RFC-2460
 *  - @subpage RFC-2553
 *  - @subpage RFC-2553_RFC-3493
 *  - @subpage RFC-2710
 *  - @subpage RFC-3493
 *  - @subpage RFC-4213
 *  - @subpage RFC-4291
 *  - @subpage RFC-4443
 *  - @subpage RFC-4861
 *  - @subpage RFC-4862
 *  - @subpage RFC-5827
 *  - @subpage RFC-6052
 *  - @subpage RFC-6724
 *  - @subpage RFC-8028
 */
#ifndef LWIP_HDR_SOCKETS_H
#define LWIP_HDR_SOCKETS_H

#include "lwip/opt.h"

#if LWIP_SOCKET /* don't build if not configured for use in lwipopts.h */

#include "lwip/ip_addr.h"
#include "lwip/err.h"
#include "lwip/inet.h"
#include "lwip/errno.h"

#if LWIP_LITEOS_COMPAT
#include <poll.h>
#include <netinet/tcp.h>
#endif
#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#if !LWIP_LITEOS_COMPAT
/**
 * @defgroup  User_interfaces User Interfaces
 * This contains all the user interfaces.
 */
/**
 *  @defgroup  Socket_Interfaces  Socket Interfaces
 *  @ingroup User_interfaces
 *   This file contains socket interfaces.
 */
/* If your port already typedef's sa_family_t, define SA_FAMILY_T_DEFINED
   to prevent this code from redefining it. */
#if !defined(sa_family_t) && !defined(SA_FAMILY_T_DEFINED)
typedef u16_t sa_family_t;
#endif
/* If your port already typedef's in_port_t, define IN_PORT_T_DEFINED
   to prevent this code from redefining it. */
#if !defined(in_port_t) && !defined(IN_PORT_T_DEFINED)
typedef u16_t in_port_t;
#endif

#if LWIP_IPV4
#ifndef SIN_ZERO_LEN
#define SIN_ZERO_LEN 8
#endif

/** @brief Defines the socket address. */
struct sockaddr_in {
  u8_t            sin_len; /**<   Specifies the socket length. */
  sa_family_t     sin_family; /**<   Specifies the socket family. */
  in_port_t       sin_port; /**<   Specifies the port. */
  struct in_addr  sin_addr; /**< Specifies the address. */
  char            sin_zero[SIN_ZERO_LEN]; /**<  Indicates an 6-bit padding. */
};
#endif /* LWIP_IPV4 */

#if LWIP_IPV6
/* @brief Defines the socket address. */
/**
 *  @page RFC-2553_RFC-3493 RFC-2553/3493
 *  @par Compliant Sections
 *  Section 3.4 Socket Address Structure for 4.4 BSD-Based Systems
 *  @par Behavior Description
 *  Systems that provide this version of the sockaddr_in6 data structure must also declare SIN6_LEN
 *  as a result of including the <netinet/in.h> header.  This macro allows applications to determine
 *  whether they are being built on a system that supports the 4.3BSD or 4.4BSD variants of the data structure. \n
 *  Behavior: Macro SIN6_LEN for applications to determine which version of sockaddr_in6 stack supports.\n
 *  If SIN6_LEN is defined the version of sockaddr_in6 is 4.4 BSD compliant.
 */
/*
 * RFC 2553/3493
 * Systems that provide this version of the sockaddr_in6(4.4 BSD) data structure   must also
 * declare SIN6_LEN .  This macro allows applications to determine   whether they are being built
 * on a system that supports the 4.3BSD or   4.4BSD variants of the data structure.
 */
#define SIN6_LEN

struct sockaddr_in6 {
  u8_t            sin6_len;      /*< Specifies the length of the structure. */
  sa_family_t     sin6_family;   /*< Specifies the socket family. */
  in_port_t       sin6_port;     /*< Specifies the transport layer port number. */
  u32_t           sin6_flowinfo; /*< Specifies the IPv6 flow information. */
  struct in6_addr sin6_addr;     /*< Specifies the IPv6 address. */
  u32_t           sin6_scope_id; /*< Specifies the set of interfaces for scope */
};

#define IN6_IS_ADDR_MULTICAST(a) (((__const u8_t *) (a))[0] == 0xff)

#endif /* LWIP_IPV6 */
/**
 *  @brief Indicates socket address.
 */
struct sockaddr {
  u8_t        sa_len;  /**<   Specifies the length of the structure. */
  sa_family_t sa_family;  /**< Specifies the socket family. */
  char        sa_data[14];  /**< Specifies the address. */
};

#if PF_PKT_SUPPORT

/**
 * @note
 * You must enable PF_PKT_SUPPORT to use the sockaddr_ll data structure. \n
 */
struct sockaddr_ll {
  u16_t sll_family;   /**< Specifies the socket family. Always AF_PACKET */
  u16_t sll_protocol; /**< Specifies the Ethernet protocol. Physical layer protocol. */
  int sll_ifindex;  /**< Specifies the network interface index. Starts from 1. */
  u16_t sll_hatype;   /**<  Specifies the hat type. */
  u8_t  sll_pkttype; /**< Specifies the packet type.*/
  u8_t  sll_halen;    /**< Specifies the physical layer address length. */
  u8_t  sll_addr[8];  /**< Specifies the physical layer address. */
};
#endif /* PF_PKT_SUPPORT*/

struct sockaddr_storage {
  u8_t        s2_len;
  sa_family_t ss_family;
  char        s2_data1[2];
  u32_t       s2_data2[3];
#if LWIP_IPV6
  u32_t       s2_data3[3];
#endif /* LWIP_IPV6 */
};

/* If your port already typedef's socklen_t, define SOCKLEN_T_DEFINED
   to prevent this code from redefining it. */
#if !defined(socklen_t) && !defined(SOCKLEN_T_DEFINED)
typedef u32_t socklen_t;
#endif

struct lwip_sock;

#if !defined(iovec)
struct iovec {
  void  *iov_base;
  size_t iov_len;
};
#endif

struct msghdr {
  void         *msg_name;
  socklen_t     msg_namelen;
  struct iovec *msg_iov;
  size_t           msg_iovlen;
  void         *msg_control;
  socklen_t     msg_controllen;
  int           msg_flags;
};

/** Socket protocol types (TCP/UDP/RAW) */
#define SOCK_STREAM     1
#define SOCK_DGRAM      2
#define SOCK_RAW        3
#define SOCK_MAX (SOCK_RAW + 1)

#define SOCK_TYPE_MASK 0xf

/*
 * Option flags per-socket. These must match the SOF_ flags in ip.h (checked in init.c)
 */
#define SO_REUSEADDR   0x0004 /* Allow local address reuse */
#define SO_KEEPALIVE   0x0008 /* keep connections alive */
#define SO_BROADCAST   0x0020 /* permit to send and to receive broadcast messages (see IP_SOF_BROADCAST option) */

/*
 * Additional options, not kept in so_options.
 */
#define SO_DEBUG       0x0001 /* Unimplemented: turn on debugging info recording */
/** Socket has had listen() */
#define SO_ACCEPTCONN  0x0002

#define SO_DONTROUTE   0x0010

#ifndef SO_BINDTODEVICE
#define SO_BINDTODEVICE 25
#endif

#ifndef SO_ATTACH_FILTER
#define SO_ATTACH_FILTER 26
#endif

#ifndef SO_DETACH_FILTER
#define SO_DETACH_FILTER 27
#endif

#define SO_USELOOPBACK 0x0040 /* Unimplemented: bypass hardware when possible */
/** Linger on close, if data is present. */
#define SO_LINGER      0x0080 /* linger on close if data present */
#define SO_DONTLINGER  ((int)(~SO_LINGER))

#define SO_OOBINLINE   0x0100 /* Unimplemented: Leave received OOB data in line */

#define SO_REUSEPORT   0x0200 /* Unimplemented: allow local address & port reuse */
#define SO_SNDBUF      0x1001 /* Unimplemented: send buffer size */
#define SO_RCVBUF      0x1002 /* receive buffer size */
#define SO_SNDLOWAT    0x1003 /* Unimplemented: send low-water mark */
#define SO_RCVLOWAT    0x1004 /* Unimplemented: receive low-water mark */
/** Indicates the Send timeout. */
#define SO_SNDTIMEO  0x1005
/** Indicates the receive timeout. */
#define SO_RCVTIMEO  0x1006
/** Gets the error status and clear. */
#define SO_ERROR     0x1007
/** Get the socket type */
#define SO_TYPE      0x1008

#define SO_CONTIMEO  0x1009
/** Do not create UDP checksum. */
#define SO_NO_CHECK  0x100a

#define SO_PRIORITY    0x100b

/**
 * Structure used for manipulating linger option.
 */
struct linger {
  int l_onoff;                /**< Indicates whether the linger option is on/off. */
  int l_linger;               /**< Indicates the linger time in seconds. */
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define  SOL_SOCKET  1    /* options for socket level */

#define AF_UNSPEC       0
#define AF_INET         2
#if LWIP_IPV6
#define AF_INET6        10
#else /* LWIP_IPV6 */
#define AF_INET6        AF_UNSPEC
#endif /* LWIP_IPV6 */
#define PF_INET         AF_INET
#define PF_INET6        AF_INET6
#define PF_UNSPEC       AF_UNSPEC

#if PF_PKT_SUPPORT
/** Packet family.  */
#define PF_PACKET 17
/** Pakcet family socket level */
#define SOL_PACKET   263
#endif

#define IPPROTO_IP      0
#define IPPROTO_ICMP    1
#define IPPROTO_TCP     6
#define IPPROTO_UDP     17
#if LWIP_IPV6
#define IPPROTO_IPV6    41
#define IPPROTO_ICMPV6  58
#endif /* LWIP_IPV6 */
#define IPPROTO_UDPLITE 136
#define IPPROTO_RAW     255

/* Flags we can use with send and recv. */
/** Peeks at an incoming message */
#define MSG_PEEK       0x01
/* Unimplemented: Requests that the function block until the full amount of data requested can be returned */
#define MSG_WAITALL    0x02
/* Unimplemented: Requests out-of-band data. The significance and semantics of out-of-band data are protocol-specific */
#define MSG_OOB        0x04
/** Nonblocking I/O for this operation only */
#define MSG_DONTWAIT   0x08
/** Sender will send more messages. */
#define MSG_MORE       0x10

/* Do not generate SIGPIPE */
#define MSG_NOSIGNAL    0x4000

/*
 * Options for level IPPROTO_IP
 */
#define IP_TOS             1
#define IP_TTL              2
#define IP_PKTINFO       8

#if LWIP_TCP
/*
 * Options for level IPPROTO_TCP
 */
#define TCP_NODELAY    0x01   /* don't delay send to coalesce packets */
/** Send KEEPALIVE Signals when idle for pcb->keep_idle milliseconds */
#define TCP_KEEPALIVE  0x02
/** Set pcb->keep_idle  - Same as TCP_KEEPALIVE, but use seconds for get/setsockopt */
#define TCP_KEEPIDLE   0x03
/** Set pcb->keep_intvl - Use seconds for get/setsockopt */
#define TCP_KEEPINTVL  0x04
/** Set pcb->keep_cnt   - Use number of Signals sent for get/setsockopt */
#define TCP_KEEPCNT    0x05
/** Set sequence number of repaired queue. */
#define TCP_QUEUE_SEQ     0x15
/* [VPPTECH-449] TCP_INFO support */
/*
 * User-gettable options (used with getsockopt).
 */
#ifndef TCP_INFO
/** Information about this connection. */
#define TCP_INFO 11
#endif
/* [VPPTECH-449] TCP_INFO support */
#endif /* LWIP_TCP */

#if LWIP_IPV6
/*
 * Options for level IPPROTO_IPV6
 */
#define IPV6_CHECKSUM       7  /* RFC3542: calculate and insert the ICMPv6 checksum for raw sockets. */
#define IPV6_V6ONLY          27 /* RFC3493: boolean control to restrict AF_INET6 sockets to IPv6 communications only. */

/*
 * RFC 2553/3493 : To set/get the unicast hop limit for outgoing unicast packets
 * As of now stack support only get options
 */
#define IPV6_UNICAST_HOPS   16

#if LWIP_MULTICAST_TX_OPTIONS
/*
 * RFC 2553/3493 : To Set/get the hop limit to use for outgoing multicast packets
 * As of now stack support only get options, also not supported for RAW as of now
 */
#define IPV6_MULTICAST_HOPS 18

#endif /* LWIP_MULTICAST_TX_OPTIONS */
#define IPV6_RECVPKTINFO    49
#define IPV6_PKTINFO         50
#endif /* LWIP_IPV6 */

#if LWIP_TCP
#define TCP_KEEPALIVE  0x02    /* send KEEPALIVE probes when idle for pcb->keep_idle milliseconds */

/** @brief Indicates socket repair options.  */
enum {
  TCP_NO_QUEUE,   /**<  Indicates no queue. */
  TCP_RECV_QUEUE, /**< Indicates the receive queue.  */
  TCP_SEND_QUEUE, /**< Indicates the send  queue.  */
  TCP_QUEUES_NR, /**<  Indicates Queue NR.  */
};
#endif /* LWIP_TCP */

#if LWIP_UDP && LWIP_UDPLITE
/*
 * Options for level IPPROTO_UDPLITE
 */
/** Indicates sender checksum coverage. */
#define UDPLITE_SEND_CSCOV 0x01
/** Indicates minimal receiver checksum coverage. */
#define UDPLITE_RECV_CSCOV 0x02
#endif /* LWIP_UDP && LWIP_UDPLITE */

#if LWIP_MULTICAST_TX_OPTIONS
/**
 * Options and types for UDP multicast traffic handling
 */
#define IP_MULTICAST_TTL   5
#define IP_MULTICAST_IF    6
#define IP_MULTICAST_LOOP  7
#endif /* LWIP_MULTICAST_TX_OPTIONS */

#if !LWIP_LITEOS_COMPAT
#if LWIP_IGMP
/*
 * Options and types related to multicast membership
 */
#ifndef IP_ADD_MEMBERSHIP
#define IP_ADD_MEMBERSHIP  35
#endif /* IP_ADD_MEMBERSHIP */

#ifndef IP_DROP_MEMBERSHIP
#define IP_DROP_MEMBERSHIP 36
#endif /* IP_DROP_MEMBERSHIP */
typedef struct ip_mreq {
  struct in_addr imr_multiaddr; /**< Indicates the IP multicast address of the group. */
  struct in_addr imr_interface; /**<    Indicates the local IP address of the interface. */
} ip_mreq;
#endif /* LWIP_IGMP */
#if LWIP_IPV6 && LWIP_IPV6_MLD
/*
 * Options and types related to IPv6 multicast membership
 */
#define IPV6_JOIN_GROUP      20
#define IPV6_ADD_MEMBERSHIP  IPV6_JOIN_GROUP
#define IPV6_LEAVE_GROUP     21
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP

typedef struct ipv6_mreq {
  struct in6_addr ipv6mr_multiaddr; /*  IPv6 multicast addr */
  unsigned int    ipv6mr_interface; /*  interface index, or 0 */
} ipv6_mreq;
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */
#if !LWIP_LITEOS_COMPAT
#if LWIP_IPV6
struct in6_ifreq {
  struct in6_addr ifr6_addr;
  u32_t ifr6_prefixlen;
  s32_t ifr6_ifindex;
};
#endif /* LWIP_IPV6 */
#endif /* !LWIP_LITEOS_COMPAT */
#if LWIP_RAW
#ifndef IP_HDRINCL
#define IP_HDRINCL        0x3     /* int; Header is included with data.  */
#endif /* IP_HDRINCL */
#endif /* LWIP_RAW */
#endif /* !LWIP_LITEOS_COMPAT */

#if LWIP_IPV4
struct in_pktinfo {
  unsigned int   ipi_ifindex;  /* Interface index */
  struct in_addr ipi_addr;     /* Destination (from header) address */
};
#endif /* LWIP_IPV4 */

/**
 * The Type of Service provides an indication of the abstract
 * parameters of the quality of service desired.  These parameters are
 * to be used to guide the selection of the actual service parameters
 * when transmitting a datagram through a particular network.  Several
 * networks offer service precedence, which somehow treats high
 * precedence traffic as more important than other traffic (generally
 * by accepting only traffic above a certain precedence at time of high
 * load).  The major choice is a three way tradeoff between low-delay,
 * high-reliability, and high-throughput.
 * The use of the Delay, Throughput, and Reliability indications may
 * increase the cost (in some sense) of the service.  In many networks
 * better performance for one of these parameters is coupled with worse
 * performance on another.  Except for very unusual cases at most two
 * of these three indications should be set.
 */
#define IPTOS_TOS_MASK          0x1E
/**  Refer to IPTOS_TOS_MASK description. */
#define IPTOS_TOS(tos)          ((tos) & IPTOS_TOS_MASK)
/**  Refer to IPTOS_TOS_MASK description. */
#define IPTOS_LOWDELAY          0x10
/**  Refer to IPTOS_TOS_MASK description. */
#define IPTOS_THROUGHPUT        0x08
/**  Refer to IPTOS_TOS_MASK description. */
#define IPTOS_RELIABILITY       0x04
/**  Refer to IPTOS_TOS_MASK description. */
#define IPTOS_LOWCOST           0x02
/**  Refer to IPTOS_TOS_MASK description. */
#define IPTOS_MINCOST           IPTOS_LOWCOST

/**
 * The Network Control precedence designation is intended to be used
 * within a network only.  The actual use and control of that
 * designation is up to each network. The Internetwork Control
 * designation is intended for use by gateway control originators only.
 * If the actual use of these precedence designations is of concern to
 * a particular network, it is the responsibility of that network to
 * control the access to, and use of, those precedence designations.
 */
#define IPTOS_PREC_MASK                 0xe0
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC(tos)                ((tos) & IPTOS_PREC_MASK)
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC_NETCONTROL           0xe0
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC_INTERNETCONTROL      0xc0
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC_CRITIC_ECP           0xa0
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC_FLASHOVERRIDE        0x80
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC_FLASH                0x60
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC_IMMEDIATE            0x40
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC_PRIORITY             0x20
/**  Refer to IPTOS_PREC_MASK description. */
#define IPTOS_PREC_ROUTINE              0x00

/*
 * Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
 * lwip_ioctl only supports FIONREAD and FIONBIO, for now
 *
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 */
#if !defined(FIONREAD) || !defined(FIONBIO)
#ifndef IOCPARM_MASK
#define IOCPARM_MASK    0x7fU           /* parameters must be < 128 bytes */
#endif
#ifndef IOC_VOID
#define IOC_VOID        0x20000000UL    /* no parameters */
#endif
#ifndef IOC_OUT
#define IOC_OUT         0x40000000UL    /* copy out parameters */
#endif
#ifndef IOC_IN
#define IOC_IN          0x80000000UL    /* copy in parameters */
#endif
#ifndef IOC_INOUT
#define IOC_INOUT       (IOC_IN | IOC_OUT)
#endif
/* 0x20000000 distinguishes new &
   old ioctl's */
#ifndef _IO
#define _IO(x, y)        (IOC_VOID | ((x) << 8) | (y))
#endif
#ifndef _IOR
#define _IOR(x, y, t)     (IOC_OUT | ((sizeof(t) & IOCPARM_MASK) << 16) | ((x) << 8) | (y))
#endif
#ifndef _IOW
#define _IOW(x, y, t)     (IOC_IN | ((sizeof(t) & IOCPARM_MASK) << 16) | ((x) << 8) | (y))
#endif
#ifndef _IOWR
#define _IOWR(x, y, t)     (IOC_INOUT | ((sizeof(t) & IOCPARM_MASK) << 16) | ((x) << 8) | (y))
#endif
#endif /* !defined(FIONREAD) || !defined(FIONBIO) */

#ifndef FIONREAD
#define FIONREAD    _IOR('f', 127, unsigned long) /* get # bytes to read */
#endif
#ifndef FIONBIO
#define FIONBIO     _IOW('f', 126, unsigned long) /* set/clear non-blocking i/o */
#endif

/* Socket I/O Controls: unimplemented */
#ifndef SIOCSHIWAT
#define SIOCSHIWAT  _IOW('s',  0, unsigned long)  /* set high watermark */
#define SIOCGHIWAT  _IOR('s',  1, unsigned long)  /* get high watermark */
#define SIOCSLOWAT  _IOW('s',  2, unsigned long)  /* set low watermark */
#define SIOCGLOWAT  _IOR('s',  3, unsigned long)  /* get low watermark */
#define SIOCATMARK  _IOR('s',  7, unsigned long)  /* at oob mark? */
#endif
/**
 *   @page RFC-4862 RFC-4862
 *   @par  RFC-4862 Compliance Information
 *   @par Compliant Sections
 *   Section 5.5.4.  Address Lifetime Expiry
 *   @par Behavior Description
 *   Test: System management MUST have the ability to disable preferred_lifetime facility,
 *   and the facility MUST be disabled by default.
 */
/* commands for fnctl */
#ifndef F_GETFL
#define F_GETFL 3
#endif
#ifndef F_SETFL
#define F_SETFL 4
#endif

/* File status flags and file access modes for fnctl,
   these are bits in an int. */
#ifndef O_NONBLOCK
#define O_NONBLOCK  4U /* nonblocking I/O */
#endif
#ifndef O_NDELAY
#define O_NDELAY    O_NONBLOCK /* same as O_NONBLOCK, for compatibility */
#endif

#ifndef SHUT_RD
#define SHUT_RD   0
#define SHUT_WR   1
#define SHUT_RDWR 2
#endif

/* FD_SET used for lwip_select */
#ifndef FD_SET
#undef FD_SETSIZE
/* Make FD_SETSIZE match NUM_SOCKETS in socket.c */
#define FD_SETSIZE    MEMP_NUM_NETCONN
#define FDSETSAFESET(n, code) do { \
  if (((n) - LWIP_SOCKET_OFFSET < MEMP_NUM_NETCONN) && (((int)(n) - LWIP_SOCKET_OFFSET) >= 0)) { \
  code; } } while (0)
#define FDSETSAFEGET(n, code) (((n) - LWIP_SOCKET_OFFSET < MEMP_NUM_NETCONN) && (((int)(n) - LWIP_SOCKET_OFFSET) >= 0) ?\
  (code) : 0)
#define FD_SET(n, p) \
  FDSETSAFESET(n, (p)->fd_bits[((u32_t)((n) - LWIP_SOCKET_OFFSET)) / 8] |=  (1 << (((n)-LWIP_SOCKET_OFFSET) & 7)))
#define FD_CLR(n, p) \
  FDSETSAFESET(n, (p)->fd_bits[((u32_t)((n) - LWIP_SOCKET_OFFSET)) / 8] &= ~(1 << (((n)-LWIP_SOCKET_OFFSET) & 7)))
#define FD_ISSET(n, p) \
  FDSETSAFEGET(n, (p)->fd_bits[((u32_t)((n) - LWIP_SOCKET_OFFSET)) / 8] &   (1 << (((n)-LWIP_SOCKET_OFFSET) & 7)))
#define FD_ZERO(p) memset((void*)(p), 0, sizeof(*(p)))

typedef struct fd_set {
  unsigned char fd_bits [(FD_SETSIZE + 7) / 8];
} fd_set;

#elif LWIP_SOCKET_OFFSET
#error LWIP_SOCKET_OFFSET does not work with external FD_SET!
#elif FD_SETSIZE < MEMP_NUM_NETCONN
#error "external FD_SETSIZE too small for number of sockets"
#endif /* FD_SET */

/** LWIP_TIMEVAL_PRIVATE: If you want to use the struct timeval provided
 * by your system, set this to 0 and include <sys/time.h> in cc.h */
#ifndef LWIP_TIMEVAL_PRIVATE
#define LWIP_TIMEVAL_PRIVATE 1
#endif

#if LWIP_TIMEVAL_PRIVATE
struct timeval {
  long    tv_sec;         /* seconds */
  long    tv_usec;        /* and microseconds */
};
#endif /* LWIP_TIMEVAL_PRIVATE */

#define lwip_socket_init() /* Compatibility define, no init needed. */
#endif
#if LWIP_NETCONN_SEM_PER_THREAD
void lwip_socket_thread_init(void); /* LWIP_NETCONN_SEM_PER_THREAD==1: initialize thread-local semaphore */
void lwip_socket_thread_cleanup(void); /* LWIP_NETCONN_SEM_PER_THREAD==1: destroy thread-local semaphore */
#endif

#if LWIP_IPV6
/**
 * @ingroup Duplicate_Address_Detection_IOCTL
 * @brief
 *   This is a IOCTL to turn on/off Duplicate Address Detection at run time.
 *   IOCTL cmd: SIOCSIPV6DAD.
 *
 * @param[in] s        Indicates socket index, but not used.
 * @param[in] cmd      Indicates IOCTL unique command.
 * @param[in] argp     Indicates void pointer to struct ifreq.
 *                               Valid struct ifreq must have valid ifrn_name
 *                               (interface name.) and ifru_ivalue 0 or 1,\n
 *                               0 indicates turnoff.\n
 *                               1 indicates turnon.
 *
 * @returns
 *   0 : On success. \n
 *   Negative Value : On failure.
 */
#ifndef SIOCSIPV6DAD
#define SIOCSIPV6DAD _IOW('z', 0, unsigned long) /* set DAD enable/disable on netif */
#endif

/**
 * @ingroup Duplicate_Address_Detection_IOCTL
 * @brief
 *   This is a IOCTL to get status of Duplicate Address Detection.
 *   IOCTL cmd: SIOCGIPV6DAD.
 *
 *
 * @param[in] s          Indicates socket index, but not used.
 * @param[in] cmd     Indicates IOCTL unique command.
 * @param[out] argp     Indicates void pointer to struct ifreq.
 *                               Valid struct ifreq must have valid ifrn_name
 *                               (interface name.). \n
 *                               User can read value of ifru_ivalue in struct
 *                               ifreq.
 *                               0 indicates turnoff.\n
 *                               1 indicates turnon.
 *
 * @returns
 *   0 : On sucess. \n
 *   Negative Value : On failure.
 */
#ifndef SIOCGIPV6DAD
#define SIOCGIPV6DAD _IOR('z', 1, unsigned long) /* get DAD status on netif */
#endif

/* set DEPRECATION enable/disable on netif */
/**

 * @brief
 *
 *   This is a IOCTL to turn on/off Preferred and Deprecation state facility for
 *   address at run time.
 *   IOCTL cmd: SIOCSIPV6DPCTD.
 *
 * @param[in] s          Indicates socket index, but not used.
 * @param[in] cmd     Indicates IOCTL unique command.
 * @param[in] argp     Indicates void pointer to struct ifreq.
 *                               Valid struct ifreq must have valid ifrn_name
 *                               (interface name.) and ifru_ivalue 0 or 1,\n
 *                               0 indicates turnoff.\n
 *                               1 indicates turnon.
 *
 * @returns
 *   0 : On sucess. \n
 *   Negative Value : On failure.
 */
#ifndef SIOCSIPV6DPCTD
#define SIOCSIPV6DPCTD _IOW('z', 2, unsigned long)
#endif

/* get DEPRECATION status on netif */
/**

 * @brief
 *   This is a IOCTL to get status of Duplicate Address Detection.
 *   IOCTL cmd: SIOCGIPV6DPCTD.
 *
 *
 * @param[in] s          Indicates socket index, but not used.
 * @param[in] cmd     Indicates IOCTL unique command.
 * @param[out] argp     Indicates void pointer to struct ifreq.
 *                               Valid struct ifreq must have valid ifrn_name
 *                               (interface name.). \n
 *                               User can read value of ifru_ivalue in struct
 *                               ifreq.
 *                               0 indicates turnoff.\n
 *                               1 indicates turnon.
 *
 * @returns
 *   0 : On sucess. \n
 *   Negative Value : On failure.
 */
#ifndef SIOCGIPV6DPCTD
#define SIOCGIPV6DPCTD _IOR('z', 3, unsigned long)
#endif

#endif

#if LWIP_MAC_SECURITY
#define  IP_MACSEC   128
#endif

#if LWIP_LITEOS_COMPAT

#ifndef TCP_KEEPALIVE
#define TCP_KEEPALIVE  0x02    /* send KEEPALIVE probes when idle for pcb->keep_idle milliseconds */
#endif
#ifndef SIN_ZERO_LEN
#define SIN_ZERO_LEN 8
#endif

#ifndef SOCK_MAX
#define SOCK_MAX (SOCK_RAW + 1)
#endif

#ifndef SOCK_TYPE_MASK
#define SOCK_TYPE_MASK 0xf
#endif
#endif

#if LWIP_IPV6
#define LWIP_IS_IPPROTOCOL(protocol)   ((protocol) == IPPROTO_IP || (protocol) == IPPROTO_IPV6 || (protocol) == 0)
#if PF_PACKET
#define LWIP_IS_VALID_DOMAIN(domain) (((domain) == AF_INET) || ((domain) == AF_INET6) || ((domain) == PF_PACKET))
#else
#define LWIP_IS_VALID_DOMAIN(domain) ((domain) == AF_INET) || ((domain) == AF_INET6)
#endif
#else
#define LWIP_IS_IPPROTOCOL(protocol)   ((protocol) == IPPROTO_IP || (protocol) == 0)
#if PF_PACKET
#define LWIP_IS_VALID_DOMAIN(domain) (((domain) == AF_INET) || ((domain) == PF_PACKET))
#else
#define LWIP_IS_VALID_DOMAIN(domain) ((domain) == AF_INET)
#endif
#endif

#if LWIP_COMPAT_SOCKETS == 2
/* This helps code parsers/code completion by not having the COMPAT functions as defines */
#define lwip_accept       accept
#define lwip_bind         bind
#define lwip_shutdown     shutdown
#define lwip_close        closesocket
#define lwip_connect      connect
#define lwip_getsockname  getsockname
#define lwip_getpeername  getpeername
#define lwip_setsockopt   setsockopt
#define lwip_getsockopt   getsockopt

#define lwip_listen       listen
#define lwip_recv         recv
#define lwip_recvfrom     recvfrom
#define lwip_send         send
#define lwip_sendmsg      sendmsg
#define lwip_sendto       sendto
#define lwip_socket       socket
#if LWIP_SOCKET_SELECT
#define lwip_select       select
#endif
#define lwip_ioctlsocket  ioctl
#define lwip_inet_ntop    inet_ntop
#define lwip_inet_pton    inet_pton
#ifdef LWIP_FCNTL
#define lwip_fcntl        fcntl
#endif

#if LWIP_GETHOSTBYNAME
#define lwip_gethostbyname(name) gethostbyname(name)
#endif

#if !LWIP_LITEOS_COMPAT
#define lwip_if_indextoname if_indextoname
#define lwip_if_nametoindex if_nametoindex
#define lwip_if_freenameindex if_freenameindex
#define lwip_if_nameindex if_nameindex
#endif

#if LWIP_DNS

#define lwip_gethostbyname(name)   gethostbyname(name)
#define lwip_gethostbyname_r       gethostbyname_r
#define lwip_freeaddrinfo          freeaddrinfo
#define lwip_getaddrinfo           getaddrinfo
#define lwip_getnameinfo           getnameinfo
#endif

#if LWIP_POSIX_SOCKETS_IO_NAMES
#define lwip_read         read
#define lwip_write        write
#define lwip_writev       writev
#undef lwip_close
#define lwip_close        close
#define closesocket(s)    close(s)
#define lwip_fcntl        fcntl
#define lwip_ioctl        ioctl
#endif /* LWIP_POSIX_SOCKETS_IO_NAMES */
#endif /* LWIP_COMPAT_SOCKETS == 2 */

/*
 *  Func Name:  lwip_accept
 */
/**
 * @ingroup Socket_Interfaces
 * @brief This API accepts a new connection on a socket.
 *  The accept() function extracts the first connection on the queue of pending connections,
 *  creates a new socket with the same socket type protocol and address family as the specified socket,
 *  and allocates a new file descriptor for that socket.
 *  If the address is not a null pointer, the address of the peer for the accepted connection shall be
 *  stored in the sockaddr structure pointed to by address,
 *  and the length of this address shall be stored in the object pointed to by address_len.
 *  If the actual length of the address is greater than the length of the supplied sockaddr structure,
 *  the stored address shall be truncated.
 *  If the listen queue is empty of connection requests and O_NONBLOCK is not set on the file descriptor
 *  for the socket, accept() shall block until a connection is present.*
 *  If the listen() queue is empty of connection requests and O_NONBLOCK is set on the file descriptor for the socket,
 *  accept() shall fail and set errno to  [EWOULDBLOCK].
 * @param[in]     socket         Specifies a socket that was created with socket(), has been bound to an address with
 *                                 bind(), and has issued a successful call to listen().
 * @param[out]    address        Indicates either a null pointer, or a pointer to a sockaddr structure
 *                                 where the address of the connecting socket shall be returned.
 * @param[in,out] address_len    Indicates either a null pointer, if address is a null pointer,
 *                                 or a pointer to a socklen_t object which on input
 *                               specifies the length of the supplied sockaddr structure,
 *                                 and on output specifies the length of the stored address.
 *
 * @return
 *  The non-negative file descriptor of the accepted socket: On success \n
 *  -1: On failure. The errno shall be set to indicate the error,
 *                  and any object pointed to by address_len shall remain unchanged. \n
 *
 * @par Errors
 *  \li The accept() function fails if:
 *     - <b> [EBADF] </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [ECONNABORTED] </b>: \n A connection has been aborted.
 *     - <b> [ECONNABORTED] </b>: \n IP address of stack has changed or removed while accept() was waiting.
 *     - <b> [EFAULT] </b>: \n A valid address length provide with address pointing to invalid memory.
 *     - <b> [EINVAL] </b>: \n The socket is not listening for connections.
 *     - <b> [EINVAL] </b>: \n The address length is invalid (For example, address_len is negative).
 *     - <b> [ENFILE] </b>: \n The maximum number of sockets in the system are already open.
 *     - <b> [ENOBUFS] </b>: \n No buffer space is available.
 *     - <b> [ENOMEM] </b>: \n There was insufficient memory available to complete the operation.
 *     - <b> [EOPNOTSUPP] </b>: \n The referenced socket is not of type SOCK_STREAM.
 *     - <b> [EWOULDBLOCK]</b> : \n O_NONBLOCK is set for the socket file descriptor
 *                                  and no connections are present to be accepted.
 *     - <b> [EWOULDBLOCK]</b> : \n O_NONBLOCK is not set but SO_RCVTIMEO is set,
 *                                  and no connections are present within accept timeout.

 *  \li The accept() function may fail if:
 *      - <b> [EIO] </b>: \n Internal errors
 * @par POSIX Conformance:
 *  @li Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *    - The following are the exceptions to conformance:
 *    - The new socket return by accept() inherit socket options such as SOF_REUSEADDR,SOF_KEEPALIVE.
 *    - This behaviour may differ from other implementations.
 *    - Portable programs should not rely on inheritance or non inheritance of file status flags or socket options,
 *    - and always explicitly set all required flags or options on the socket returned from the accept() API.
 *    - EIO is an lwIP specific errno, not defined by POSIX.
 *    - Portable programs must not use these options in applications.
 * @cond liteos
 *         - If IP address of stack changes or removed due to netif_remove,
 *         - while accept() is waiting,then stack might return ECONNABORTED.
 *         - If accept() called after IP address bind to socket has been removed,
 *         - then accept() might block indefinitely.
 * @endcond
 *
 * @note
 *  - This API does not support the PF_PACKET option.
 * @par Related Topics
 * connect()
 */
int lwip_accept(int socket, struct sockaddr *address, socklen_t *address_len);

/*
 *  Func Name:  lwip_bind
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * The bind() function assigns a local socket address address to a socket identified by descriptor socket
 * that has no local socket address assigned. Sockets created with the socket() function are initially unnamed;
 * they are identified only by their address family. This API assigns the address specified by name to the socket
 * by the file descriptor s. namelen specifies the size, in bytes, of the address
 * referred to structure pointed to by name.
 *
 * @param[in]    s              Specifies the file descriptor of the socket to be bound.
 * @param[in]    name        Points to a sockaddr structure containing the address to be bound to the socket
 * The length and format of the address depend on the address family of the socket.
 * @param[in]    namelen  Specifies the length of the sockaddr structure pointed to by the address argument
 *
 * @return
 *  0: On success \n
 *  -1: On failure. The errno is set to indicate the error. \n
 *
 * @par Errors
 *    @li The bind() function shall fail if:
 *     - <b> [EADDRINUSE] </b>: \n The specified address is already in use.
 *     - <b> [EADDRINUSE] </b>: \n For AF_INET/AF_INET6 socket, the port number was specified
 *     - <b> as zero in the socket address structure, but, upon attempting to bind to an ephemeral port,
 *     - <b>.it was determined that all port numbers in the ephemeral port range are currently in use.
 *     - <b> [EADDRNOTAVAIL] </b>: \n The specified address is not available from the local machine.
 *     - <b> [EAFNOSUPPORT] </b>: \n The specified address is not a valid address
 *     - <b> for the address family of the specified socket.
 *     - <b> [EBADF] </b> : \n The socket argument is not a valid file descriptor.
 *     - <b> [EINVAL] </b> : \n The socket is already bound to an address,
 *     - <b> and the protocol does not support binding to a new address.
 *     - <b> [EINVAL] </b> : \n The namelen argument is not a valid length for the address family.
 *     - <b> [EINVAL] </b> : \n For PF_PACKET socket, the ifindex is out of system netif index range.
 *     - <b> [EISCONN] </b>: \n The specified socket is already connected.
 *     - <b> [ENOBUFS] </b>: \n Insufficient resources were available to complete the call.
 *     - <b> [ENODEV] </b>: \n For PF_PACKET socket, the netif can not be determined by the ifindex.
 *     - <b> [ENETDOWN] </b>: \n For PF_PACKET socket, the netif determined by the ifindex was down.
 *     - <b> [EOPNOTSUPP] </b>: \n The socket type of the specified socket does not support binding to an address.

 *  @par POSIX Conformance:
 *     Confirming to POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition)
 * @note
 * - Multiple bind call behavior:  bind() call will change port binding of UDP socket.
 *    - On UDP socket will change local binding port.
 *    - On TCP socket it is not allowed, will return failure with errno EINVAL.
 *    - On AF_INET/AF_INET6 SOCK_RAW socket, it will update local IP address.
 *    - ON PF_PAKCET socket, it will change binding to new interface index. \n
 * - AF_INET/AF_INET6 SOCK_RAW bind does not check if socket address is available or not.
 */
int lwip_bind(int s, const struct sockaddr *name, socklen_t namelen);

/*
 *  Func Name:  lwip_shutdown
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API  is used to shut down socket send and receive operations.\n
 *  The shutdown() function shall cause all or part of a full-duplex connection on the socket associated
 *  with the file descriptor socket to be shut down.
 *
 * @param[in]    socket       Specifies a file descriptor referring to the socket.
 * @param[in]    how     Specifies the type of shut-down. The values are as follows: \n
 *                       SHUT_RD Disables further receive operations. \n SHUT_WR: Disables further send operations. \n
 *                       SHUT_RDWR: Disables further send and receive operations. \n

 * The shutdown() function disables subsequent send and/or receive operations on a socket,
 * depending on the value of the how argument.
 * @return
 *  0:  On success \n
 *  -1: On failure. The errno is set to indicate the error. \n
 *
 * @par Errors
 *    @li The shutdown() function shall fail if:
 *     - <b> [EBADF] </b> : \n The socket argument is not a valid file descriptor.
 *     - <b> [EINPROGRESS] </b>: \n If WRITE/CONNECTING/CLOSE is in progress, lwIP may fail.
 *     - <b> [EINVAL] </b>: \n The 'how' argument is invalid.
 *     - <b> [ENOMEM] </b>: \n There was insufficient memory available to complete the operation.
 *     - <b> [ENOTCONN] </b>: \n If socket is not connected, or already shutdown. lwIP shall fail with ENOTCONN.
 *     - <b> [ENOTCONN] </b>: \n lwIP does not support half close, ENOTCONN is returned.
 *     - <b> [ENOTCONN] </b>: \n Socket is not TCP, lwIP shall fail.

 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *  The following are the exceptions to conformance:
 *  - lwIP does not support half shutdown. That is, if you try to shutdown with either SHUT_RD or SHUT_WR alone,
 *   this API returns error ENOTCONN.
 * @note
 * - This API does not support the PF_PACKET option.
 * - The listen socket does not support half shutdown.
 * @par Limitations
 * - If shutdown is called with SHUT_RDWR or SHUT_RD flag, any pending data to be received shall be cleared by lwIP,
 * - and RST is sent to peer, application must read all data before calling SHUT_RDWR or SHUT_RD.
 * - This behavior is a limitation of lwIP. \n
 * - When send is blocked, and shutdown(SHUT_RDWR) is called, the shutdown will return EINPROGRESS (115).
 */
int lwip_shutdown(int socket, int how);

#if LWIP_GETPEERNAME || (LWIP_COMPAT_SOCKETS != 2)
/*
 *  Func Name:  lwip_getpeername
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  The getpeername() API returns the address of the peer connected to the socket 's', in the buffer pointed to by name.
 *  Initialize the namelen argument to indicate the amount of space pointed to by the name parameter.
 *  On return it contains the actual size, in bytes, of the name returned.
 *  The name is truncated if the buffer provided is too small.
 *
 * @param[in]     s          Specifies the file descriptor referring to the connected socket.
 * @param[out]    name       Indicates the pointer to the sockaddr structure of remote peer.
 * @param[in,out] namelen    Specifies the size of name structure.
 *
 * @return
 *  0: On success \n
 *  -1: On failure. The errno is set to indicate the error. \n
 * @par Errors
 *    @li The getpeername() function fails if:
 *     - <b> [EBADF] </b>: The socket argument is not a valid file descriptor.
 *     - <b> [EINVAL] </b>: The name or namelen are NULL, then EINVAL is returned.
 *     - <b> [ENOTCONN] </b>: The socket is not connected or otherwise has not had the peer pre-specified.
 *     - <b> [EOPNOTSUPP] </b>: The operation is not supported for the socket protocol.

 * @par POSIX Conformance:
 * Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 * The following are the exceptions to conformance:
 * - lwIP does not check if connection-mode socket have been shutdown, and does not return failure with  errno [EINVAL]
 *
 * @note
 * - For PF_PACKET socket type, name should be pointing to sockaddr_ll type or memory of size struct sockaddr_ll
 *
 * @par Related Topics
 * getsockname()
 */
int lwip_getpeername(int s, struct sockaddr *name, socklen_t *namelen);
#endif /* LWIP_GETPEERNAME || (LWIP_COMPAT_SOCKETS != 2) */

#if LWIP_GETSOCKNAME || (LWIP_COMPAT_SOCKETS != 2)
/*
 *  Func Name:  lwip_getsockname
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API returns the current address to which the socket 's'  is bound,
 *  in the buffer pointed to by the name parameter.
 *  Initialize the namelen argument to indicate the amount of space (in bytes) pointed to by the name parameter.
 *  The returned address is truncated if the buffer provided is too small.
 *
 * @param[in]     s        Specifies the file descriptor referring to connected socket.
 * @param[out]    name      Indicates a pointer to sockaddr structure of local peer.
 * @param[in,out] namelen  Specifies the size of name structure.
 *
 * @return
 *  0: On success \n
 *  -1: On failure. The errno is set to indicate the error. \n
 * @par Errors
 *  @li The getsockname() function shall fail if:
 *     - <b> [EBADF] </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [EINVAL] </b>: \n If name or namelen are NULL, then this errno will be set.
 *     - <b> [EOPNOTSUPP] </b>: \n   The operation is not supported for this socket's protocol.
 *     - <b>.For PF_PACKET/SOCK_RAW sockets, this error is returned.

 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition)
 *  The following are the exceptions to conformance:
 *  - lwIP does not check if connection-mode socket have been shutdown,
 *  - and does not return failure with  errno [EINVAL].
 * @note
 * \n
 * - For PF_PACKET socket type, name should be pointing to sockaddr_ll type or memory of size struct sockaddr_ll
 *
 * @par Related Topics
 * getpeername()
 */
int lwip_getsockname(int s, struct sockaddr *name, socklen_t *namelen);
#endif /* LWIP_GETSOCKNAME || (LWIP_COMPAT_SOCKETS != 2) */

/*
 *  Func Name:  lwip_getsockopt
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API is used to get options set on a socket.
 *  This API retrieves the value for the option specified by the optname argument for the socket
 *  specified by sockfd. If the size of the optval is greater than optlen, the value stored in the object
 *  pointed to by the optval argument is silently truncated.

 *
 * @param[in]        sockfd      Specifies a socket file descriptor.
 * @param[in]        level        Specifies the protocol level at which the option resides.
 * @param[in]        optname     Specifies a single option to be retrieved.
 * @param[out]       optval      Indicates an address to store option value.
 * @param[in,out]    optlen      Specifies the size of the option value.
 *
 * @return
 *  0: On success \n
 *  -1: On failure. The errno is set to indicate the error. \n

 *
 * @par Errors
 *    @li The getsockopt() function fails in the following conditions:
 *     - <b> [EBADF]   </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [EFAULT] </b>: \n If opt or optlen are NULL,option or option length is incorrect.
 *     - <b> [EINVAL] </b>: \n If option length is incorrect for specified opt.
 *     - <b> [EINVAL] </b>: \n The specified option is invalid at the specified socket level.
 *     - <b> [EINVAL] </b>: \n The specified optval is invalid for specified opt.
 *     - <b> [EINVAL] </b>: \n The specified socket is already closed or has been disconnected.
 *     - <b> [ENOMEM] </b>: \n There was insufficient memory available to complete the operation.
 *     - <b> [ENOPROTOOPT] </b>: \n The option is not supported by the protocol.
 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *  The following are the exceptions to conformance:
 *  - lwIP does not check if connection-mode socket have been shutdown, and does not return failure with errno [EINVAL]
 * @note
 * - The following protocol levels are supported:
 * - SOL_SOCKET
 *   - IPPROTO_IP
 *   - IPPROTO_TCP
 *   - IPPROTO_RAW
 *   - IPPROTO_IPV6
 *   - IPPROTO_UDPLITE
 * - The following options are supported under SOL_SOCKET:\n
 *   - SO_ACCEPTCONN
 *   - SO_BROADCAST
 *   - SO_ERROR
 *   - SO_KEEPALIVE
 *   - SO_SNDTIMEO
 *   - SO_RCVTIMEO
 *   - SO_RCVBUF
 *   - SO_SNDBUF
 *   - SO_REUSEADDR
 *   - SO_TYPE
 *   - SO_NO_CHECK
 *   - SO_BINDTODEVICE
 *   - SO_DONTROUTE
 *   - SO_LINGER
 * @cond liteos For SO_SNDTIMEO, SO_RCVTIMEO, SO_RCVBUF, the macros LWIP_SO_SNDTIMEO,
 *                  LWIP_SO_RCVTIMEO, and LWIP_SO_RCVBUF must be defined at compile time.\n
 * For SO_REUSEADDR, the macro SO_REUSE must be defined at compile time.\n
 *   For SO_BINDTODEVICE, the macro
 * LWIP_SO_BINDTODEVCE should have been defined at compile time. For SO_DONTROUTE,
 * the macro LWIP_SO_DONTROUTE should have been defined at compile time.
 * For SO_SNDBUF, the macro LWIP_SO_SNDBUF must be defined at compile time.\n @endcond
 * - The following options are supported under IPPROTO_IP:
 *   - IP_MULTICAST_TTL
 *   - IP_MULTICAST_LOOP
 *   - IP_MULTICAST_IF
 *   - IP_HDRINCL
 *   - IP_TTL
 *   - IP_TOS
 * If IP_HDRINCL is set , other options like IP_TTL and IP_TOS will be still able to set but will be effective only
 *   when IP_HDRINCL is unset.\n
 * - The following options are supported under IPPROTO_TCP:
 *   - TCP_NODELAY
 *   - TCP_KEEPIDLE
 *   - TCP_KEEPINTVL
 *   - TCP_KEEPCNT
 *   - TCP_INFO
 *   - TCP_QUEUE_SEQ
 * @cond liteos - For TCP_KEEPIDLE, TCP_KEEPINTVL, TCP_KEEPCNT, the macro LWIP_TCP_KEEPALIVE
 *                 should have been defined at compile time. @endcond
 * - SO_ERROR is not supported when socket is SOCK_RAW type.
 * @cond For TCP_INFO, the macro LWIP_TCP_INFO should have been defined at compile time.\n  @endcond
 * - For TCP_INFO, Only tcpi_state, tcpi_retransmits, tcpi_probes, tcpi_backoff, tcpi_options,
 * -.              tcpi_rto, tcpi_snd_mss, tcpi_rcv_mss, tcpi_unacked,
 * tcpi_rtt, tcpi_rttvar, tcpi_snd_ssthresh, tcpi_snd_cwnd, tcpi_reordering in
 * struct tcp_info are supported. Other fields are not supported and may contain undefined values. \n
 * - The following options are supported under IPPROTO_RAW:
 *   - IPV6_CHECKSUM: Checksum option to the offset for raw socket for updating the checksum. \n
 * - The following options are supported under IPPROTO_IPV6:
 *   - IPV6_V6ONLY: Sets the ipv6 option.
 *   - IPV6_CHECKSUM: Checksum option to the offset for raw socket for updating the checksum.
 *   - IPV6_UNICAST_HOPS:To get the hop limit value used in outgoing   unicast IPv6 packets
 *   -                   Only supported in get implementation.
 *   - IPV6_MULTICAST_HOPS: To get the hop limit value used for outgoing multicast packets,
 *   -                      only for UDP. Only supported in get implementation.
 * - The following options are supported under IPPROTO_UDPLITE:\n
 * - UDPLITE_SEND_CSCOV \n
 * - UDPLITE_RECV_CSCOV\n
 *
 *
 * @par Related Topics \n
 * setsockopt()
 */
int lwip_getsockopt(int sockfd, int level, int optname,
                    void *optval, socklen_t *optlen);

/*
 *  Func Name:  lwip_setsockopt
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * The setsockopt() function sets the option specified by the option_name argument,
 * at the protocol level specified by the level argument,to the value pointed to by the option_value argument
 * for the socket associated with the file descriptor specified by the socket argument

 * The level argument specifies the protocol level at which the option resides. To set options at the socket level,
 * specify the level argument as SOL_SOCKET. To set options at other levels,
 * supply the appropriate level identifier for the protocol controlling the option.
 * For example, to indicate that an option is interpreted by the TCP (Transport Control Protocol),
 * set level to IPPROTO_TCP.

 * The option_name argument specifies a single option to set.
 * If option_name is equal to SO_RCVTIMEO or SO_SNDTIMEO and the implementation supports setting the option,
 * the struct timeval pointed to by option_value is rounded up to align with the resolution of the clock being used.
 * If setsockopt() is called with option_name equal to SO_ACCEPTCONN, SO_ERROR, or SO_TYPE, the setsockopt fails.
 *
 * @param[in]    socket         Specifies a socket file descriptor.
 * @param[in]    level           Specifies the protocol level at which the option resides.
 * @param[in]    option_name    Specifies a single option to set.
 * @param[out]   option_value   Indicates the pointer to the option value.
 * @param[in]    option_len     Specifies the size of option value.
 *
 * @return
 *  0: On success \n
 *  -1: On failure. The errno is set to indicate the error. \n

 * @par Errors
 *   @li The setsockopt() function fails in the following conditions:
 *     - <b> [EBADF] </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [EDOM] </b>: \n The send and receive timeout values are too big to
 *     - <b> [EDOM] </b>: \n fit into the timeout fields in the socket structure.
 *     - <b> [EFAULT]  </b>: \n If optval is NULL pointer, lwIP fails.
 *     - <b> [EINVAL] </b>: \n If for PF_PACKET socket type, level is neither SOL_PACKET nor SOL_SOCKET, lwIP fails.
 *     - <b> [EINVAL] </b>: If for PF_PACKET socket type, level is neither SOL_PACKET nor SOL_SOCKET, lwIP shall fail.
 *     - <b> [EINVAL] </b>: \n If option_len does not match optval for corresponding option_name, lwIP fails.
 *     - <b> [EINVAL] </b>: \n If the send and receive timeout values are smaller than 10000 microseconds, lwIP fails.
 *     - <b> [ENOENT] </b>: \n The option is SO_DETACH_FILTER while no previous socket filter was attached.
 *     - <b> [ENOMEM] </b>: \n There was insufficient memory available for the operation to complete.
 *     - <b> [ENOPROTOOPT] </b>: \n The option is not supported by the protocol.
 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *  The following are the exceptions to conformance:
 * - If connection oriented socket is shutdown, setsockopt does not check for this and does not return failure
 * - with errno EINVAL as expected by POSIX.
 * - If socket option is INVALID at specified socket level, setsockopt returns failure with errno set to ENOPROTOOPT,
 * - which is not in conformance to POSIX.
 * - setsockopt does not check if connection is already connected for the specified options
 * - if can not be set while socket is connected.
 * @note
 * - The following protocol levels are supported:
 *   - SOL_SOCKET
 *   - IPPROTO_IP
 *   - IPPROTO_IPV6
 *   - IPPROTO_TCP
 *   - IPPROTO_RAW
 *   - IPPROTO_UDPLITE
 * - The following options are supported under SOL_SOCKET:
 *   - SO_BROADCAST
 *   - SO_KEEPALIVE
 *   - SO_LINGER
 *   - SO_SNDTIMEO
 *   - SO_RCVTIMEO
 *   - SO_RCVBUF
 *   - SO_SNDBUF
 *   - SO_ATTACH_FILTER
 *   - SO_DETACH_FILTER
 *   - SO_BINDTODEVICE
 *   - SO_DONTROUTE
 *   - SO_REUSEADDR
 *   - SO_NO_CHECK
 * @cond liteos
 * For SO_ATTACH_FILTER, SO_DETACH_FILTER,
 * the macro LWIP_SOCKET_FILTER should have been defined at compile time.
 * @endcond
 * SO_ATTACH_FILTER: \n
 * - LSF_MSH are not supported, due to which LSF_LDX hack for loading IP header length wont be supported. Hence, \n
 *   Following mode of filter is not supported: \n
 *   LSF_LDX+LSF_B+LSF_MSH  X    <- 4*(P[k:1]&0xf)\n
 * Only PF_PACKET RAW socket supports SO_ATTACH_FILTER and SO_DETACH_FILTER now.\n
 * @cond liteos
 * For SO_SNDTIMEO, SO_RCVTIMEO, SO_RCVBUF, the macros LWIP_SO_SNDTIMEO, LWIP_SO_RCVTIMEO
 * and LWIP_SO_RCVBUF must be defined at compile time. \n
 * For SO_DONTROUTE, the macro LWIP_SO_DONTROUTE should have been defined at compile time,
 * and RT_SCOPE_HOST is not supported. \n
 * For SO_SNDBUF, the macro LWIP_SO_SNDBUF must be defined at compile time.\n
 * For SO_REUSEADDR, the macro SO_REUSE must be defined at compile time.\n
 * @endcond
 * SO_REUSEADDR: \n
 * - SO_REUSEADDR does not distribute datagrams evenly across the receiving threads.\n
 * Only TCP socket in listen or closed states supports SO_SNDBUF.\n
 * - The following options are supported under IPPROTO_IP:
 *   - IP_ADD_MEMBERSHIP
 *   - IP_DROP_MEMBERSHIP
 *   - IP_MULTICAST_TTL
 *   - IP_MULTICAST_LOOP
 *   - IP_MULTICAST_IF
 *   - IP_HDRINCL
 *   - IP_TTL
 *   - IP_TOS
 * - The following options are supported under IPPROTO_IPV6:
 *   - IPV6_V6ONLY
 *   - IPV6_CHECKSUM
 *   -IPV6_JOIN_GROUP(IPV6_ADD_MEMBERSHIP)
 *    If the interface index is specified as 0, stack will not handle further, application has to give the valid index.
 *   -IPV6_LEAVE_GROUP(IPV6_DROP_MEMBERSHIP)
 * - The following options are supported under IPPROTO_RAW:
 *     - IPV6_CHECKSUM
 * - The following options are supported under IPPROTO_TCP:
 *   - TCP_NODELAY
 *   - TCP_KEEPIDLE
 *   - TCP_KEEPINTVL
 *   - TCP_KEEPCNT
 * @cond liteos For TCP_KEEPIDLE, TCP_KEEPINTVL and TCP_KEEPCNT,
 * -            the macro LWIP_TCP_KEEPALIVE must be defined at compile time.\n @endcond
 * - The following options are supported under IPPROTO_UDPLITE the options supported are:
 *   - UDPLITE_SEND_CSCOV
 *   - UDPLITE_RECV_CSCOV\n
 * @cond liteos For IPPROTO_UDPLITE, the macro LWIP_UDPLITE must be defined at compile time.\n @endcond

 * @par Related Topics
 * getsockopt()
 */
int lwip_setsockopt(int socket, int level, int option_name,
                    const void *option_value, socklen_t option_len);

/*
 *  Func Name:  lwip_close
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API is used to close the socket.
 *  If O_NONBLOCK is not set and if there is data on the module's write queue, close()
 *     waits for an unspecified time for any output to drain before dismantling the STREAM
 *  If the O_NONBLOCK flag is set, close() does not wait for output to drain, and dismantles the STREAM immediately
 *
 * @param[in]    s      Specifies a socket file descriptor.
 *
 * @return
 *  0: On success \n
 *  -1: On failure. The errno is set to indicate the error. \n
 * @par Errors
 *   @li The close() function shall fail if:
 *     - <b> [EBADF] </b>: \n The files argument is not a open file descriptor. Invalid file descriptor.
 *
 * @par Note
 * The API must not be called concurrently with other BSD API on the same socket,
 * because this scenario maybe causes other BSD API to return with unexpected behavior.
 *
 * @par POSIX Conformance:
 * Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition)
 * The following are the exceptions to conformance:
 * - Does not support SO_LINGER socket option.
 *
 *
 */
int lwip_close(int s);

/*
 *  Func Name:  lwip_connect
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * The connect() function shall attempt to make a connection on a connection-mode socket
 * or to set or reset the peer address of a connectionless-mode socket.\n
 * Specifies the length of the sockaddr structure pointed to by the address argument.     \n
 * If the socket has not already been bound to a local address,
 * connect() shall bind it to an address which is an unused local address.
 * If the initiating socket is not connection-mode, then connect() shall set the socket's peer address,
 * and no connection is made. For SOCK_DGRAM sockets,
 * the peer address identifies where all datagrams are sent on subsequent send() functions,
 * and limits the remote sender for subsequent recv() functions.
 *
 * If the initiating socket is connection-mode, then connect() shall attempt to establish a connection
 * to the address specified by the address argument. If the connection cannot be established immediately
 * and O_NONBLOCK is not set for the file descriptor for the socket, connect() shall block for up to
 * an unspecified timeout interval until the connection is established. If the timeout interval expires before
 * the connection is established, connect() shall fail and the connection attempt shall be aborted.
 *
 * If the connection cannot be established immediately and O_NONBLOCK is set for the file descriptor for the socket,
 * connect() shall fail and set errno to [EINPROGRESS], but the connection request shall not be aborted,
 * and the connection shall be established asynchronously.
 *
 *
 * @param[in]    s          Specifies a socket file descriptor.
 * @param[in]    name       Specifies a pointer to the sockaddr structure which identifies the connection.
 * @param[in]    namelen    Specifies the size of name structure.
 *
 *
 * @return
 *  0: On success \n
 *  -1: On failure \n
 * @par Errors
 *    @li The connect() function shall fail if:
 *     - <b> [EACCES] </b>: \n The user tried to connect to a broadcast address without having the socket broadcast flag
 *                             enabled.
 *     - <b> [EADDRNOTAVAIL] </b>: \n For AF_INET/AF_INET6 socket, the socket had not previously been bound to
 *                                    an address and, upon attempting to bind it to an ephemeral port,
 *                                    it was determined that all port numbers in the ephemeral port
 *                                    range are currently in use.
 *     - <b> [EAFNOSUPPORT] </b>: \n The passed address did not have the correct address family in its sa_family field.
 *     - <b> [EALREADY] </b>: \n The socket is nonblocking and a previous connection attempt has not yet been completed.
 *     - <b> [EBADF] </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [ECONNREFUSED] </b>: \n The target address was not listening
 *                                   for connections or refused the connection request.
 *     - <b> [ECONNRESET] </b>: \n Remote host reset the connection request.
 *     - <b> [EINPROGRESS] </b>: \n O_NONBLOCK is set for the file descriptor for the socket
 *                                  and the connection cannot be immediately established;
 *                                  the connection shall be established asynchronously.
 *     - <b> [EINVAL] </b>: \n The address_len argument is not a valid length for the address family.
 *     - <b> [EAFNOSUPPORT] </b>: \n The specified address is not a valid address for the address family
 *                                   of the specified socket.
 *     - <b> [EISCONN] </b>: \n The specified socket is connection-mode and is already connected.
 *     - <b> [ENETUNREACH] </b>: \n No route to the network is present.
 *     - <b> [ENOBUFS] </b>: \n No buffer space is available.
 *     - <b> [EOPNOTSUPP] </b>: \n The referenced socket is not of domain AF_INET.
 *     - <b> [EOPNOTSUPP] </b>: \n The socket is listening and cannot be connected.
 *     - <b> [ETIMEDOUT] </b>: \n The attempt to connect timed out before a connection was made.
 *
 * @par POSIX Conformance:
 * Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 * The following are the exceptions to conformance:
 * - lwIP does not check if specified address has a different type
 * than the socket bound to the specified peer address. Behavior is unspecified.
 */
int lwip_connect(int s, const struct sockaddr *name, socklen_t namelen);

/*
 *  Func Name:  lwip_listen
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API is used to set a socket into listen mode.
 *  This API marks the socket referred to by sockfd as a passive socket.
 *  That is, as a socket that will be used
 *  to accept incoming connection requests using accept().
 *
 * @param[in]    sockfd      Specifies a file descriptor that refers to a socket of type SOCK_STREAM.
 * @param[in]    backlog     Defines the maximum length to which the queue of pending connections for sockfd may grow
 *                           If a connection request arrives
 *                           when the queue is full, the client may receive an error with an indication of ECONNREFUSED
 *                           or, if the underlying protocol
 *                           supports retransmission, the request may be ignored
 *                           so that a later reattempt at connection succeeds.
 *
 * @par Errors
 *   @li The listen() function shall fail if:
 *     - <b> [EBADF] </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [EDESTADDRREQ] </b>: \n The socket is not bound to a local address,
 *                                   and the protocol does not support listening on an unbound socket.
 *     - <b> [EINVAL] </b>: \n The socket is in state which is not acceptable for listen.
 *     - <b> [ENOBUFS] </b>: \n Insufficient resources are available in the system to complete the call.
 *     - <b> [EOPNOTSUPP] </b>: \n The socket protocol does not support listen().
 *
 * @return
 *  0: On success \n
 *  -1: On failure. The errno is set to indicate the error. \n
 * @par POSIX Conformance:
 *      POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition)
 * @note
 * - Maximum value of backlog is 16, and minimum value of backlog is 0.
 * - If backlog value is 0 or less than zero, backlog value of 1 is used.
 * - This API does not support the PF_PACKET socket.
 * - lwIP does not support auto binding in listen operation, so bind() must be called before listen().
 * - The listen() API supports multiple calls. If socket is already listening, it will update listen backlog.
 * -              New backlog value shall be applicable only for new incoming connection requests.
 */
int lwip_listen(int sockfd, int backlog);

/*
 *  Func Name:  lwip_recv
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API is used to recieve a message from connected socket. The recv() function shall receive a message
 *  from a connection-mode or connectionless-mode socket. It is normally used with connected sockets
 *  because it does not permit the application to retrieve the source address of received data.
 * If no messages are available at the socket and O_NONBLOCK is not set on the socket's file descriptor,
 * recv() shall block until a message arrives. If no messages are available at the socket and O_NONBLOCK
 * is set on the socket's file descriptor, recv() shall fail and set errno to [EWOULDBLOCK].
 *
 * @param[in]    socket    Specifies the socket file descriptor.
 * @param[in]    buffer    Points to a buffer where the message should be stored.
 * @param[in]    length    Specifies the length in bytes of the buffer pointed to by the buffer argument.
 * @param[in]    flags     Specifies the type of message reception.
 *                         Values of this argument are formed by logically OR'ing zero or more of the
 *                         following values:\n
 *                         MSG_PEEK : Peeks at an incoming message. The data is treated as unread and the next recv()
 *                                     or similar function shall still return this data. \n
 *                         MSG_DONTWAIT : Enables nonblocking operation;if the operation would block,
 *                                        or similar function shall still EWOULDBLOCK.\n
 *                         MSG_NOSIGNAL : Disables raising of SIGPIPE
 *                                        on stream sockets when the other end disappears.\n
 *
 * @return
 *  The length of the message in bytes. : On success. If no messages are available to be received
 *  and the peer has performed an orderly shutdown, recv() returns 0. \n
 *  -1: On failure. The errno is set to indicate the error.
 *
 * @par Errors
 *    @li The recv() function fails if:
 *     - <b> [EBADF] </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [ECONNRESET] </b>: \n A connection was forcibly closed by a peer.
 *     - <b> [EINVAL]</b>: \n Invalid input parameters. If mem, len is null or flags is less than zero,
 *                            lwIP returns failure.
 *     - <b> [ENOBUFS] </b>: \n Insufficient resources were available in the system to perform the operation.
 *     - <b> [ENOMEM] </b>: \n Insufficient memory was available to fulfil the request.
 *     - <b> [ENOTCONN] </b>: \n A receive is attempted on a connection-mode socket that is not connected.
 *     - <b> [EOPNOTSUPP] </b>: \n Some bit in the flags argument is unsupported for the socket type.
 *     - <b> [EWOULDBLOCK] </b>: \n The socket's file descriptor is marked O_NONBLOCK or MSG_DONTWAIT flag
 *                                  is set and no data is waiting to be received.
 *     - <b> [EWOULDBLOCK] </b>: \n The socket was not marked with O_NONBLOCK,
 *                                  but set with option SO_RCVTIMEO, and elapsed time is more than timeout value.
 *
 *    @li The recv() function may fail if:
 *     - <b> [EIO]</b>: \n Internal errors.
 *
 * @par POSIX Conformance:
 * Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 * The following are the exceptions to conformance:
 *  For UDP MSG_PEEK is not suported and data is discarded even if it is set.
 *  MSG_OOB, MSG_WAITALL flags are not supported.
 *
 * @note
 * - TCP receive buffer is a list, which holds the segement received from peer.
 * If application is calling recv to get the data, then it just tries to get the
 * first entry from the list and gives back to application. This doesn't get recursively
 * from list to fill the complete user buffer. \n
 * - lwIP updates this receive buffer list when it gets the next expected segment.
 * If there is any out of order segment which is next to the received segment,
 * lwIP merges the segments and puts that as one segment on to the receive buffer list.
 * - If the apps don't read the packet form the socket and the recv buffered
 * packets up to MAX_MBOX_SIZE, the incoming packet may be discard by lwIP and cause
 * retransmission for tcp connection.\n
 * - MSG_PEEK is not  supported for UDP or RAW sockets.
 * - UDP or RAW does not report memory allocation failure if memory allocation failed for received packet.
 * - Instead of MSG_WAITALL, MSG_DONTWAIT is supported.
 * - SO_RECVTIMEO socket option is set, and socket is not marked as O_NONBLOCK, (nonblocking),
 * -              and non data is received for timeout duration on socket, error is returned with ETIMEDOUT set.
 * - For TCP connection, when RST is received after FIN, this API will return 0 to indicate FIN,
 * -   then return -1 and set errno to ECONNRESET for RST.
 * - For TCP connection, when data is received and RST is recevied together (push, ack, rst) flag is set
 * -   then the data will be lost and RST will be processed.
 * This API is not thread-safe.
 * @par Related Topics
 * read()
 * recvfrom()
 */
ssize_t lwip_recv(int socket, void *buffer, size_t length, int flags);

/*
 *  Func Name:  lwip_read
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  The read() function shall attempt to read nbyte bytes from the file associated with the open file descriptor,
 *  fildes, into the buffer pointed to by buf. The behavior of multiple concurrent reads on the same device/socket is
 *  unspecified.
 *  Before any action described below is taken, and if nbyte is zero, the read() function may detect
 *  and return errors as described below. In the absence of errors, or if error detection is not performed,
 *  the read() function shall return zero and have no other results.
 *    If no messages are available at the socket and O_NONBLOCK is not set on the socket's file descriptor,
 *  recv() shall block until a message arrives.
 *  If no messages are available at the socket and O_NONBLOCK is set on the socket's file descriptor,
 *  recv() shall fail and set errno to [EWOULDBLOCK].
 *  For message-based sockets, such as SOCK_DGRAM and SOCK_SEQPACKET,
 *  the entire message shall be read in a single operation.
 *  If a message is too long to fit in the supplied buffer, the excess bytes shall be discarded.
 *
 *
 * @param[in]    fildes          Specifies a socket file descriptor.
 * @param[out]   buf                Specifies the buffer to store the received data.
 * @param[in]    nbyte              Specifies the number of bytes of data to receive.
 *
 * @return
 *  Number of bytes received: On success. \n
 *  -1: On failure. \n
 *
 * @par Errors
 *    @li The read() function fails if:
 *     - <b> [EBADF] </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [ECONNRESET] </b>: \n A connection was forcibly closed by a peer.
 *     - <b> [EINVAL]</b>: \n Invalid input parameters. If mem, len is null or flags is less than zero,
 *                            lwIP returns failure.
 *     - <b> [ENOBUFS] </b>: \n Insufficient resources were available in the system to perform the operation.
 *     - <b> [ENOMEM] </b>: \n Insufficient memory was available to fulfil the request.
 *     - <b> [ENOTCONN] </b>: \n A receive is attempted on a connection-mode socket that is not connected.
 *     - <b> [EWOULDBLOCK] </b>: \n The socket's file descriptor is marked O_NONBLOCK
 *                                  or MSG_DONTWAIT flag is set and no data is waiting to be received.
 *     - <b> [EWOULDBLOCK] </b>: \n The socket was not marked with O_NONBLOCK, but set with option SO_RCVTIMEO,
 *                                  and elapsed time is more than timeout value.
 *    @li The read() function may fail if:
 *     - <b> [EIO]</b>: \n Internal errors.
 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *  The following are the exceptions to conformance:
 * @par Related Topics
 * recv() \n
 * recvfrom()
 *
 *
 */
ssize_t lwip_read(int fildes, void *buf, size_t nbyte);

/*
 *  Func Name:  lwip_recvfrom
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * The recvfrom() function shall receive a message from a connection-mode or connectionless-mode socket.
 * It is normally used with connectionless-mode sockets
 * because it permits the application to retrieve the source address of received data.
 * The function shall return the length of the message written to the buffer pointed to by the buffer argument.
 * For message-based sockets, such as [RS] [Option Start]  SOCK_RAW, [Option End] SOCK_DGRAM, and SOCK_SEQPACKET,
 * the entire message shall be read in a single operation. If a message is too long to fit in the supplied buffer,
 * the excess bytes shall be discarded.
 *
 * For stream-based sockets, such as SOCK_STREAM, message boundaries shall be ignored. In this case,
 * data shall be returned to the user as soon as it becomes available, and no data shall be discarded.
 *
 * Not all protocols provide the source address for messages. If the address argument is not a null pointer
 * and the protocol provides the source address of messages, the source address of the received message shall be stored
 * in the sockaddr structure pointed to by the address argument,
 * and the length of this address shall be stored in the object pointed to by the address_len argument.
 *
 * If the actual length of the address is greater than the length of the supplied sockaddr structure,
 * the stored address shall be truncated.
 *
 * If no messages are available at the socket and O_NONBLOCK is not set on the socket's file descriptor,
 * recvfrom() shall block until a message arrives.
 * If no messages are available at the socket and O_NONBLOCK is set on the socket's file descriptor,
 * recvfrom() shall fail and set errno to [EWOULDBLOCK].
 *
 * @param[in]    socket    Specifies the socket file descriptor.
 * @param[out]    buffer   Points to the buffer where the message should be stored.
 * @param[in]    length            Specifies the length in bytes of the buffer pointed to by the buffer argument.
 * @param[in]    flags     Specifies the type of message reception.
 *                         Values of this argument are formed by logically OR'ing zero
 *                           or more of the following values: \n
 *                         MSG_PEEK : Peeks at an incoming message. The data is treated as unread and the next recv()
 *                                     or similar function shall still
 *                                     return this data. \n
 *                         MSG_DONTWAIT : Enables nonblocking operation; if the operation would block,
 *                                        the call fails with the error EAGAIN or
 *                                        EWOULDBLOCK. \n
 *                        MSG_NOSIGNAL : Disables raising of SIGPIPE on stream sockets when the other end disappears.\n
 * @param[out]  address  A null pointer, or points to a sockaddr structure in which the sending address is to be stored.
 *                         The length and format of the address depend on the address family of the socket.
 * @param[out]  address_len    Either a null pointer, if address is a null pointer, or a pointer to a socklen_t object
 *                             which on input specifies the length of the supplied sockaddr structure,
 *                             and on output specifies the length of the stored address.
 *
 * @return
 *  Number of bytes received: Indicates a successful execution. \n
 *  -1: Indicates a failure.
 *
 * @par Required Header File
 * sockets.h
 *  @par Errors
 *    @li The recvfrom() function fails if:
 *     - <b> [EBADF] </b>: \n The socket argument is not a valid file descriptor.
 *     - <b> [ECONNRESET] </b>: \n A connection was forcibly closed by a peer.
 *     - <b> [EINVAL]</b>: \n Invalid input parameters. If mem, len is null or flags is less than zero
 *                            lwIP returns failure.
 *     - <b> [ENOBUFS] </b>: \n Insufficient resources were available in the system to perform the operation.
 *     - <b> [ENOMEM] </b>: \n Insufficient memory was available to fulfil the request.
 *     - <b> [ENOTCONN] </b>: \n A receive is attempted on a connection-mode socket that is not connected.
 *     - <b> [EOPNOTSUPP] </b>: \n Some bit in the flags argument is unsupported for the socket type.
 *     - <b> [EWOULDBLOCK] </b>: \n The socket's file descriptor is marked O_NONBLOCK or MSG_DONTWAIT
 *                                  flag is set and no data is waiting to be received.
 *     - <b> [EWOULDBLOCK] </b>: \n The socket was not marked with O_NONBLOCK,
 *                                  but set with option SO_RCVTIMEO, and elapsed time is more than timeout value.
 *
 *   @li The recvfrom() function may fail if:
 *     - <b> [EIO]</b>: \n Internal errors.
 *  @par Return value
 *   Upon successful completion, recvfrom() shall return the length of the message in bytes.
 *   If no messages are available to be received and the peer has performed an orderly shutdown,
 *   recvfrom() shall return 0. Otherwise, the function shall return -1 and set errno to indicate the error.
 *
 *    @par POSIX Conformance:
 *   Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *   The following are the exceptions to conformance:
 * -  For UDP MSG_PEEK is not suported and data is discarded even if it is set.
 * -  MSG_OOB, MSG_WAITALL flags are not supported.
 *
 * @note
 * The behaviour of multiple concurrent reads on the same socket, is unspecified.
 * - MSG_PEEK is not  supported for UDP or RAW sockets.
 * -UDP or RAW does not report memory allocation failure if memory allocation failed for received packet.
 * - Instead of MSG_WAITALL, MSG_DONTWAIT is supported.
 * - On TCP sockets, recvfrom() attempts to receive all the data from receive buffer if available.
 * -TCP receive buffer is a list which holds the segment received from the peer.
 * -If the application calls the recv function to get the data, the function gets the first entry from the list
 * -and gives it back to application. This function does not recursively get entries
 * -from the list to fill the complete user buffer.
 * -lwIP updates this receive buffer list when it gets the next expected segment.
 * -If there is any out of order segment which is next to the received segment,
 * -lwIP merges the segments and puts that as one segment on to the receive buffer list.
 * - If the apps don't read the packet form the socket and the recv buffered packets up to MAX_MBOX_SIZE,
 * - the incoming packet may be discard by lwIP.
 * - If the 'length' parameter is passed as zero, the stack will return -1 and errno will be set to EINVAL.
 * - This behaviour is unspecified in POSIX specification, and a deviation from the LINUX implementation of recvfrom(),
 * - where it returns 0 when the buffer size is passed as zero.
 * - MSG_TRUNC flag is not supported.
 * - For TCP connection, when RST is received after FIN, this API will return 0 to indicate FIN, then return -1
 * - and set errno to ECONNRESET for RST.
 * - For TCP connection, when data is received and RST is recevied together (push, ack, rst) flag is set
 * - then the data will be lost and RST will be processed.
 * - This API is not thread-safe.
 * @par Related Topics
 * read() \n
 * recv()
 */
ssize_t lwip_recvfrom(int socket, void *buffer, size_t length,
                      int flags, struct sockaddr *address,
                      socklen_t *address_len);

/*
 * Func Name:  lwip_send
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API initiates transmission of a message from the specified socket to its peer.
 *  It sends a message only when the socket is connected.
 *
 * @param[in]    s          Specifies the socket file descriptor.
 * @param[in]    dataptr    Specifies a buffer containing message to send.
 * @param[in]    size       Specifies the length of the message to send.
 * @param[in]    flags      Indicates the flags of message transmission.
 *
 * @return
 *  Number of bytes sent: Indicates a successful execution.\n
 *  -1: Indicates failure.
 *
 * @par Errors
 *   @li The send() function fails if:
 *     - <b> [EADDINUSE] </b>: For PF_INET/SOCK_DGRAM socket without local port bond, \
 *                             when attempting to bind to an ephemeral port,
 *                             it was determined that all port numbers in the ephemeral port range are currently in use.
 *     - <b> [EBADF] </b>: The socket argument is not a valid file descriptor.
 *     - <b> [ECONNRESET] </b>: A connection was forcibly closed by a peer.
 *     - <b> [EDESTADDRREQ] </b>: The socket is not connection-mode and does not have its peer address set.
 *     - <b> [EINPROGRESS] </b>: For PF_INET/SOCK_STREAM, there was one send operation in progress,
 *                               and concurrent sending was not supported.
 *     - <b> [EINVAL] </b>: Invalid argument passed, e.g. dataptr is NULL, size is zero.
 *     - <b> [EMSGSIZE] </b>: The socket type requires that message be sent atomically,\
 *                            and the size of the message to be sent made this impossible.
 *                            For PF_PACKET/SOCK_RAW socket, it means the packet is larger than
 *                            the MTU of out network interface. For PF_INET/(SOCK_RAW,SOCK_DGRAM) socket,
 *                            it means the packet is larger than 65000 bytes.
 *     - <b> [ENETDOWN] </b>: For PF_PACKET/SOCK_RAW socket, the binding network interface was down.
 *     - <b> [ENOBUFS] </b>: Insufficient resources were available in the system to perform the operation.
 *     - <b> [ENODEVADDR] </b>: For PF_PACKET/SOCK_RAW socket, the binding network interface does not exist.
 *     - <b> [ENOMEM] </b>: Insufficient memory was available to fulfill the request.
 *     - <b> [ENOTCONN] </b>: The socket is not connected.
 *     - <b> [EOPNOTSUPP] </b>: Some bit in the flags argument is unsupported for the socket type.
 *     - <b> [EPIPE] </b>: The socket is shut down for writing, or the socket is connection-mode
 *                         and is no longer connected.In the latter case, and if the socket is of type SOCK_STREAM.
 *     - <b> [EWOULDBLOCK] </b>: The socket's file descriptor is marked O_NONBLOCK or MSG_DONWAIT flag is set
 *                               and the requested operation would block.
 *     - <b> [EWOULDBLOCK] </b>: The socket was not marked with O_NONBLOCK, but set with option SO_SNDTIMEO,
 *                               and elapsed time is more than timeout value.

 *   @li The send() function may fail if:
 *     - <b> [EIO] </b>: Internal errors.
 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *  The following are the exceptions to conformance:
 *   - lwIP do not support half-close, if sending data on the socket that was shut down for writing,
 *     it would failed and errno set to ENOTCONN, while it is EPIPE in POSIX.
 *   - Return type is int instead of ssize_t
 *   - If the socket is in connecting LwIP would return EINPROGRESS, which is ENOTCONN in POSIX.
 *
 * @note
 * - UDP and RAW connection can send only data of maximum length 65332. Sending more than data
 * will return -1 and errno set to EMSGSIZE.
 * - Only flag MSG_MORE and MSG_DONTWAIT is supported.
 * - Other flags, such as MSG_OOB/MSG_NOSIGNAL/MSG_EOR are not supported.\n
 *
 *
 * @par Related Topics
 * write()
 * sendto()
 */
ssize_t lwip_send(int s, const void *dataptr, size_t size, int flags);
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API initiates transmission of a message from the specified socket to its peer.
 *  It sends a message only when the socket is connected.  The sendmsg() call also allows
 * sending ancillary data (also known as control information).
 *
 * @param[in]    s          Specifies the socket file descriptor.
 * @param[in]    message       Specifies a buffer containing message to send.
 * @param[in]    flags       Indicates the types of message transmission.
 *
 * @return
 *  Number of bytes sent: Indicates a successful execution.\n
 *  -1: Indicates failure.
 *
 * @par Errors
 *   @li The sendmsg() function fails if:
 *     - <b> [EADDINUSE] </b>: For PF_INET/SOCK_DGRAM socket without local port bond, when attempting to
 * bind to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use.
 *     - <b> [EBADF] </b>: The socket argument is not a valid file descriptor.
 *     - <b> [ECONNRESET] </b>: A connection was forcibly closed by a peer.
 *     - <b> [EDESTADDRREQ] </b>: The socket is not connection-mode and does not have its peer address set.
 *     - <b> [EINPROGRESS] </b>: For PF_INET/SOCK_STREAM, there was one send operation in progress,
 * and concurrent sending was not supported.
 *     - <b> [EINVAL] </b>: Invalid argument passed, e.g. dataptr is NULL, size is zero.
 *     - <b> [EMSGSIZE] </b>: The socket type requires that message be sent atomically, and the size of the message
 * to be sent made this impossible. For PF_PACKET/SOCK_RAW socket,
 * it means the packet is larger than the MTU of out network interface. For PF_INET/(SOCK_RAW,SOCK_DGRAM) socket,
 * it means the packet is larger than 65000 bytes.
 *     - <b> [ENETDOWN] </b>: For PF_PACKET/SOCK_RAW socket, the binding network interface was down.
 *     - <b> [ENOBUFS] </b>: Insufficient resources were available in the system to perform the operation.
 *     - <b> [ENODEVADDR] </b>: For PF_PACKET/SOCK_RAW socket, the binding network interface does not exist.
 *     - <b> [ENOMEM] </b>: Insufficient memory was available to fulfill the request.
 *     - <b> [ENOTCONN] </b>: The socket is not connected.
 *     - <b> [EOPNOTSUPP] </b>: Some bit in the flags argument is unsupported for the socket type.
 *     - <b> [EPIPE] </b>: The socket is shut down for writing, or the socket is connection-mode
 * and is no longer connected. In the latter case, and if the socket is of type SOCK_STREAM.
 *     - <b> [EWOULDBLOCK] </b>: The socket's file descriptor is marked O_NONBLOCK
 * or MSG_DONWAIT flag is set and the requested operation would block.
 *     - <b> [EWOULDBLOCK] </b>: The socket was not marked with O_NONBLOCK,
 * but set with option SO_SNDTIMEO, and elapsed time is more than timeout value.
 *
 *   @li The sendmsg() function may fail if:
 *     - <b> [EIO] </b>: Internal errors.
 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 * The following are the exceptions to conformance:
 *   - lwIP do not support half-close, if sending data on the socket that was shut down
 * for writing, it would failed and errno set to ENOTCONN, while it is EPIPE in POSIX.
 *   - Return type is int instead of ssize_t
 *   - If the socket is in connecting LwIP would return EINPROGRESS, which is ENOTCONN in POSIX.
 *
 * @note
 * - UDP and RAW connection can send only data of maximum length 65332. Sending more than data
 * will return -1 and errno set to EMSGSIZE.
 * - Only flag MSG_MORE and MSG_DONTWAIT is supported. Other flags, such as
 *  MSG_OOB/MSG_NOSIGNAL/MSG_EOR are not supported.\n
 *
 *
 * @par Related Topics
 * write()
 * sendto()
 */
ssize_t lwip_sendmsg(int s, const struct msghdr *message, int flags);

/*
 *  Func Name:  lwip_sendto
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API is used to send messages from a connection-oriented and connectionless sockets.
 *  If the socket is in the connectionless mode, the message is sent to the address specified by the 'to' parameter.
 *  If the socket is in the connection mode, the destination address in the 'to' parameter is ignored.
 *
 * @param[in]    s          Specifies a socket file descriptor.
 * @param[in]    dataptr       Specifies a buffer containing the message to send.
 * @param[in]    size       Specifies the length of the message to send.
 * @param[in]    flags       Indicates the flags of message transmission.
 * @param[in]    to         Specifies a pointer to the sockaddr structure that contains the destination address.
 * @param[in]    tolen      Specifies the size of the 'to' structure.
 *
 * @return
 *  Number of bytes sent: Indicates a successful execution. \n
 *  -1: Indicates a failure.
 * @par Errors
 *    @li The sendto() function fails if:
 *     - <b> [EACCES] </b>: For PF_INET/(SOCK_RAW,SOCK_DGRAM) socket,
 *                          the destination address is broadcast but SO_BROADCAST option was not enabled.
 *     - <b> [EADDINUSE] </b>: For PF_INET/SOCK_DGRAM socket without local port bond,
 *                             when attempting to bind to an ephemeral port, it was determined that all port
 *                             numbers in the ephemeral port range are currently in use.
 *     - <b> [EAFNOSUPPORT] </b>: Addresses in the specified address family cannot be used with this socket.
 *     - <b> [EBADF] </b>: The socket argument is not a valid file descriptor.
 *     - <b> [ECONNRESET] </b>: A connection was forcibly closed by a peer.
 *     - <b> [EDESTADDRREQ] </b>: The socket is not connection-mode and does not have its peer address set,
 *                                and no destination address was specified.
 *     - <b> [EINPROGRESS] </b>: For PF_INET/SOCK_STREAM, there was one send operation in progress,
 *                               and concurrent sending was not supported.
 *     - <b> [EINVAL] </b>: Invalid argument passed. For example, dataptr is NULL, size is zero.
 *     - <b> [EMSGSIZE] </b>: The socket type requires that message be sent atomically,
 *                            and the size of the message to be sent made this impossible.
 *                            For PF_PACKET/SOCK_RAW socket,
 *                            it means the packet is larger than the MTU of out network interface.
 *                            For PF_INET/(SOCK_RAW,SOCK_DGRAM) socket, it means the packet is larger than 65000 bytes.
 *     - <b> [ENETDOWN] </b>: For PF_PACKET/SOCK_RAW socket, the out network interface was down.
 *     - <b> [ENETUNREACH] </b>: No route to the destination is present.
 *     - <b> [ENOBUFS] </b>: Insufficient resources were available in the system to perform the operation.
 *     - <b> [ENOMEM] </b>: Insufficient memory was available to fulfill the request.
 *     - <b> [ENOTCONN] </b>: The socket is not connected.
 *     - <b> [ENXIO] </b>: For PF_PACKET/SOCK_RAW socket, the given network interface does not exist.
 *     - <b> [EOPNOTSUPP] </b>: Some bit in the flags argument is unsupported for the socket type.
 *     - <b> [EPIPE] </b>: The socket is shut down for writing,
 *                         or the socket is connection-mode and is no longer connected.
 *                         In the latter case, and if the socket is of type SOCK_STREAM .
 *     - <b> [EWOULDBLOCK] </b>: The socket's file descriptor is marked O_NONBLOCK
 *                               or MSG_DONTWAIT flag is set and the requested operation would block.
 *     - <b> [EWOULDBLOCK] </b>: The socket was not marked with O_NONBLOCK, but set with option SO_SNDTIMEO,
 *                               and elapsed time is more than timeout value.

 *   @li The sendto() function may fail if:
 *     - <b> [EIO] </b>: Internal error.
 * @par POSIX Conformance:
 * Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 * *The following are the exceptions to conformance:
 * - For UDP/RAW socket, sendto() override peer address set in connect by address provided in sendto,
 * - and does not return failure with EISCONN.
 * - TCP ignore destination address provided in sendto(), and use connection set up by connect()
 * - MSG_EOR, MSG_OOB, MSG_NOSIGNAL,  are not suported, lwip fails with errnor set to EOPNOTSUPP.
 * - LwIP does not support half-close, if sending data on the socket that was shut down for writing,
 * - it would failed and errno set to ENOTCONN, while it is EPIPE in POSIX.
 * - For PF_PACKET SOCK_RAW socket, if given network interface index does not exist,
 * - lwIP return failure with errno ENXIO.
 * - If the socket is in connecting LwIP would return EINPROGRESS, which is ENOTCONN in POSIX.
 * @note
 * - AF_INET/AF_INET6 UDP and RAW connection can send only data of maximum length 65332. Sending more than data
 * will return failure with return value -1 and errno set to EMSGSIZE.
 * - Only flag MSG_MORE and MSG_DONTWAIT is supported, other flags,
 * - such as MSG_OOB/MSG_NOSIGNAL/MSG_EOR is not supported
 *
 * @par Related Topics
 * write() \n
 * send()
 */
ssize_t lwip_sendto(int s, const void *dataptr, size_t size, int flags,
                    const struct sockaddr *to, socklen_t tolen);

/*
 *  Func Name:  lwip_socket
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API is used to allocate a socket.
 *  It creates an endpoint for communication and returns a file descriptor.
 *
 * @param[in]    domain    Specifies a protocol family.
 * @param[in]    type       Specifies the socket type.  [SOCK_RAW|SOCK_DGRAM,SOCK_STREAM]
 * @param[in]    protocol   Specifies the protocol to be used with the socket.
 *
 * @return
 * Valid socket file descriptor: On success. \n
 *  -1: On failure.
 * @par Errors
 *    @li The socket() function fails if:
 *     - <b>[EAFNOSUPPORT] </b>: \n The implementation does not support the specified address family.
 *     - <b>[EINVAL] </b>:  \n Invalid type or invalid flags in type.
 *     - <b>[ENFILE] </b>: \n The maximum number of sockets in the system are already open.
 *     - <b>[ENOBUFS] </b>: \n Insufficient resources were available in the system to perform the operation.
 *     - <b>[EPROTONOSUPPORT] </b>: \n The specified protocol is not supported within this domain & type.
 *     - <b>[ESOCKTNOSUPPORT] </b>: \n The socket type is not supported within this domain.
 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *  The following are the exceptions to conformance:
 *  - socket() does not validate domain. It assumes it to be AF_INET(PF_INET) if not PF_PACKET.
 *  As per POSIX it should return failure with errno [EAFNOSUPPORT], but it does not return that error.
 *  - For socket type not recognised by socket it returns failure with errno ESOCKTNOSUPPORT instead of EPROTOTYPE.
 * @note
 * - PF_PACKET is supported only for SOCK_RAW.
 *   - For AF_INET socket SOCK_RAW | SOCK_DGRAM | SOCK_STREAM types are supported.
 *   - For AF_PACKET, only the SOCK_RAW type is supported.
 *   - For AF_INET6 socket SOCK_RAW | SOCK_DGRAM | SOCK_STREAM types are supported.
 */
int lwip_socket(int domain, int type, int protocol);

/*
 * Func Name:  lwip_write
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  This API is used to send data on connection-oriented sockets.
 *
 * @param[in]    s           Specifies a socket file descriptor.
 * @param[in]    dataptr       Specifies a buffer containing the message to send.
 * @param[in]    size       Specifies the length of the message to send.
 *
 * @return
 *  Number of bytes sent: Indicates success. \n
 *  -1: Indicates failure.
 *
 * @par Errors
 *    @li The write() function shall fail if:
 *     - <b> [EWOULDBLOCK] </b>: The socket's file descriptor is marked O_NONBLOCK or MSG_DONWAIT flag is set
 *                               and the requested operation would block.
 *     - <b> [EWOULDBLOCK] </b>: The socket was not marked with O_NONBLOCK, but set with option SO_SNDTIMEO,
 *                               and elapsed time is more than timeout value.
 *     - <b> [EADDINUSE] </b>: For PF_INET/SOCK_DGRAM socket without local port bond,
 *                               when attempting to bind to an ephemeral port,*
 *                               it was determined that all port numbers in the ephemeral port
 *                               range are currently in use.
 *     - <b> [EBADF] </b>: The socket argument is not a valid file descriptor.
 *     - <b> [ECONNRESET] </b>: A connection was forcibly closed by a peer.
 *     - <b> [EDESTADDRREQ] </b>: The socket is not connection-mode and does not have its peer address set.
 *     - <b> [EINPROGRESS] </b>: For PF_INET/SOCK_STREAM, there was one send operation in progress,
 *                               and concurrent sending was not supported.
 *     - <b> [EINVAL] </b>: Invalid argument passed. For example, dataptr is NULL or size is zero.
 *     - <b> [EMSGSIZE] </b>: The socket type requires that message be sent atomically, and the size of the message
 *                            to be sent made this impossible. For PF_PACKET/SOCK_RAW socket,
 *                            it means the packet is larger than the MTU of out network interface.
 *                            For PF_INET/(SOCK_RAW,SOCK_DGRAM) socket, it means the packet is larger than 65000 bytes.
 *     - <b> [ENETDOWN] </b>: For PF_PACKET/SOCK_RAW socket, the binding network interface was down.
 *     - <b> [ENOBUFS] </b>: Insufficient resources were available in the system to perform the operation.
 *     - <b> [ENOMEM] </b>: Insufficient memory was available to fulfill the request.
 *     - <b> [ENODEVADDR] </b>: For PF_PACKET/SOCK_RAW socket, the binding network interface does not exist.
 *     - <b> [ENOTCONN] </b>: The socket is not connected.
 *
 *   @li The write() function may fail if:
 *     - <b> [EIO] </b>: Internal errors.
 *
 * @par POSIX Conformance:
 * Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 * The following are the exceptions to conformance:
 * - Return type is int instead of ssize_t
 * - lwIP sets EWOULDBLOCK instead of EAGAIN, wherever EAGAIN is set to errno.
 * @note
 * - For sockets not marked with O_NONBLOCK, and socket set with option SP_SENDTIMEO,
  and elapsed time is more than timeout value, lwIP shall fail with errno EAGAIN.
 * @par Related Topics
 * send() \n
 * sendto()
 */
int lwip_write(int s, const void *dataptr, size_t size);
/**
 * @ingroup Socket_Interfaces
 * @brief
 *  The writev() function writes iovcnt buffers of data described
 *    by iov to the file associated with the file descriptor s.
 *
 * @param[in]    s           Specifies a file descriptor.
 * @param[in]    iov       Indicates buffers of data.
 * @param[in]    iovcnt       Indicates the number of buffers.
 *
 * @return
 *  Number of bytes sent: Indicates success. \n
 *  -1: Indicates failure.
 *
 * @par Errors
 *    @li The writev() function shall fail if:
 *     - <b> [EWOULDBLOCK] </b>: The socket's file descriptor is marked O_NONBLOCK
 * or MSG_DONWAIT flag is set and the requested operation would block.
 *     - <b> [EWOULDBLOCK] </b>: The socket was not marked with O_NONBLOCK,
 * but set with option SO_SNDTIMEO, and elapsed time is more than timeout value.
 *     - <b> [EADDINUSE] </b>: For PF_INET/SOCK_DGRAM socket without local port bond,
 *                             when attempting to bind to an ephemeral port, it was determined
 *                             that all port numbers in the ephemeral port range are currently in use.
 *     - <b> [EBADF] </b>: The socket argument is not a valid file descriptor.
 *     - <b> [ECONNRESET] </b>: A connection was forcibly closed by a peer.
 *     - <b> [EDESTADDRREQ] </b>: The socket is not connection-mode and does not have its peer address set.
 *     - <b> [EINPROGRESS] </b>: For PF_INET/SOCK_STREAM, there was one send operation
 * in progress, and concurrent sending was not supported.
 *     - <b> [EINVAL] </b>: Invalid argument passed. For example, dataptr is NULL or size is zero.
 *     - <b> [EMSGSIZE] </b>: The socket type requires that message be sent atomically,
 * and the size of the message to be sent made this impossible. For PF_PACKET/SOCK_RAW socket,
 *  it means the packet is larger than the MTU of out network interface.
 *   For PF_INET/(SOCK_RAW,SOCK_DGRAM) socket, it means the packet is larger than 65000 bytes.
 *     - <b> [ENETDOWN] </b>: For PF_PACKET/SOCK_RAW socket, the binding network interface was down.
 *     - <b> [ENOBUFS] </b>: Insufficient resources were available in the system to perform the operation.
 *     - <b> [ENOMEM] </b>: Insufficient memory was available to fulfil the request.
 *     - <b> [ENODEVADDR] </b>: For PF_PACKET/SOCK_RAW socket, the binding network interface does not exist.
 *     - <b> [ENOTCONN] </b>: The socket is not connected.
 *
 *   @li The writev() function may fail if:
 *     - <b> [EIO] </b>: Internal errors.
 *
 * @par POSIX Conformance:
 * Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 * The following are the exceptions to conformance:
 * - Return type is int instead of ssize_t
 * - lwIP sets EWOULDBLOCK instead of EAGAIN, wherever EAGAIN is set to errno.
 * @note
 * - For sockets not marked with O_NONBLOCK,
 *   and socket set with option SP_SENDTIMEO, and elapsed time is more than timeout value,
 *   lwIP shall fail with errno EAGAIN.
 * @par Related Topics
 * send() \n
 * sendto()
 */
int lwip_writev(int s, const struct iovec *iov, int iovcnt);

#if LWIP_SOCKET_POLL
/*
 * Func Name:  lwip_poll
 * */
/**
  * @ingroup Socket_Interfaces
  * @brief
  * This API is used to poll on multiple file descriptors, waiting until one or more of the file descriptors
  * become "ready" for some of I/O operations.
  * @param[in]    sockfd    socket file descriptor
  * @param[in]    wait   Indicates poll  table struct include events provided by the user.
  * @return
  * Socket file descriptor: On success \n
  * -1: On failure \n
  */
int lwip_poll(int sockfd, poll_table *wait);
#endif /* LWIP_SOCKET_POLL*/

#if LWIP_SOCKET_SELECT
/*
 *  Func Name:  lwip_select
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 *
 * select() allows a program to monitor multiple file
 *       descriptors, waiting until one or more of the file descriptors become
 *       "ready" for some class of I/O operation (input possible).  A
 *       file descriptor is considered ready if it is possible to perform a
 *       corresponding I/O operation (read() without blocking, or a
 *       sufficiently small write()).
 *
 *        select() can monitor only file descriptors numbers that are less than
 *       FD_SETSIZE.
 *
 * select() uses a timeout that is a struct timeval (with seconds
 *              and microseconds).
 * Three independent sets of file descriptors are watched.  The file
 *       descriptors listed in readfds will be watched to see if characters
 *       become available for reading (more precisely, to see if a read will
 *       not block; in particular, a file descriptor is also ready on end-of-
 *       file).  The file descriptors in writefds will be watched to see if
 *       space is available for write (though a large write may still block).
 *       The file descriptors in exceptfds will be watched for exceptional
 *       conditions.
 * On exit, each of the file descriptor sets is modified in place to
 *       indicate which file descriptors actually changed status.  (Thus, if
 *       using select() within a loop, the sets must be reinitialized before
 *       each call.)
 *
 *       Each of the three file descriptor sets may be specified as NULL if no
 *       file descriptors are to be watched for the corresponding class of
 *       events.
 *
 *       Four macros are provided to manipulate the sets.  FD_ZERO() clears a
 *       set.  FD_SET() and FD_CLR() respectively add and remove a given file
 *       descriptor from a set.  FD_ISSET() tests to see if a file descriptor
 *       is part of the set; this is useful after select() returns.
 *
 *       nfds should be set to the highest-numbered file descriptor in any of
 *       the three sets, plus 1.  The indicated file descriptors in each set
 *       are checked, up to this limit
 *
 * The timeout argument specifies the interval that select() should
 *       block waiting for a file descriptor to become ready.  The call will
 *       block until either:
 *       -  a file descriptor becomes ready;
 *       -  the timeout expires.
 *
 * Note that the timeout interval will be rounded up to the system clock
 *       granularity, and kernel scheduling delays mean that the blocking
 *       interval may overrun by a small amount.  If both fields of the
 *       timeval structure are zero, then select() returns immediately.  (This
 *       is useful for polling.)  If timeout is NULL (no timeout), select()
 *       can block indefinitely.
 *
 * @param[in]    nfds    Specifies a range of file descriptors.
 * @param[in]    readfds   Specifies a pointer to struct fd_set,
 *                         and specifies the descriptor to check for being ready to read.
 * @param[in]    writefds  Specifies a pointer to struct fd_set,
 *                         and specifies the descriptor to check for being ready to write.
 * @param[in]    exceptfds   Specifies a pointer to struct fd_set,
 *                           and specifies the descriptor to check for pending error conditions.
 * @param[in]    timeout      Specifies a pointer to struct timeval, for timeout application.
 *
 * @return
 *  Socket file descriptor: On success \n
 *  -1: On failure \n
 * @par POSIX Conformance:
 *  Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
 *  The following are the exceptions to conformance:
 * - select() does not validate if nfds argument,
 * - does not check if argument is less than zero or greater than FD_SETSIZE
 * - As per POSIX, implementations may place limitations on the maximum timeout interval supported.
 * All implementations shall support a maximum timeout interval of at least 31 days,
 * but  lwIP limits value until any overflow happens,
 * timer with very high value might result in unspecified behavior.

 * @par Errors
 * The select() function shall fail if:
 *     - <b>[EBADF] </b>: \n One or more of the file descriptor sets specified a file descriptor
 *                           that is not a valid open file descriptor.
 *     - <b>[EINVAL] </b>: \n An invalid timeout interval was specified. \n
 *     - <b>[ENOMEM] </b>: \n Insufficient resources or memory, memory allocation failed.

 * @note
 * - The select() API does not update the timeout argument to indicate how much time was left.
 * - FD_SETSIZE is compile time configurable in lwIP, and application must ensure it does not violate this boundary,
 * - lwIP does not validate this at runtime.
 *
 * @par Multithreaded Application
 *      If a file descriptor being monitored by select() is closed in another
 *      thread, the result is unspecified. lwIP may return without setting any fdset.
 *      On some UNIX systems, select()  unblocks and returns, with an indication that the file descriptor is
 *      ready (a subsequent I/O operation will likely fail with an error,
 *      unless another the file descriptor reopened between the time select()
 *      returned and the I/O operations was performed).  On Linux (and some
 *       other systems), closing the file descriptor in another thread has no
 *      effect on select().  In summary, any application that relies on a
 *      particular behaviour in this scenario must be considered buggy.
 */
int lwip_select(int nfds, fd_set *readfds,
                fd_set *writefds, fd_set *exceptfds,
                struct timeval *timeout);
#endif /* LWIP_SOCKET_SELECT */

 /*
 Func Name:  lwip_ioctl
 */
 /**
 * @ingroup Socket_Interfaces
 * @brief
  This function manipulates the underlying device parameters of
        special files.  In particular, many operating characteristics of
        character special files (for example, terminals) may be controlled with
        ioctl() requests.  The argument fd must be an open file descriptor.

        The second argument is a device-dependent request code.

        An ioctl() request has encoded in it whether the argument is an input
        parameter or output parameter, and the size of the argument argp in
        bytes.

 * @param[in]    s         Specifies an open socket file descriptor.
 * @param[in]    request   Specifies a device-dependent request code.
 * @param[in]    argp      Specifies additional information, if required.
 *
 *
 * @return
 *      Usually, on success zero is returned.  A few ioctl() requests use the
 *       return value as an output parameter and return a nonnegative value on
 *        success.  On error, -1 is returned, and errno is set appropriately.
 *
 * @par Errors
 *    @li The ioctl() function shall fail if:
 *     - <b> [EBADF] </b> : The fd argument is not a valid open file descriptor.
 *     - <b> [EINVAL] </b> : The request or arg argument is not valid for this device.
 *     - <b> [ENOMEM] </b> : If any resource allocation fails, ENOMEM is set as errno.
 *     - <b> [ENODEV] </b> : If no device found, ENODEV is set as errno.
 *     - <b> [EPERM] </b> : If specified device is loopback i.e. "lo", EPERM is set as errno.
 *    @li The ioctl() function may fail if:
 *     - <b> [EAFNOSUPPORT] </b>: If socket created with PF_PACKET, SOCK_RAW is called with SIOCADDRT.
 *     - <b> [EIO] </b>: If socket failed to set/get ethtool settings, called with SIOCETHTOOL.
 *     - <b> [ENOSYS] </b>: If specified option is not supported/unimplemented, then errno is set as ENOSYS.
 * @note
 * - Linux API supports variable argument support. The lwIP API supports only one void * as the
 * third argument. \n
 * - This API supports the following options: \n
 * - SIOCADDRT: Set IF gateway, soft-route is not support by lwIP yet. \n
 * - SIOCGIFADDR: Get ifnet address.\n
 * - SIOCGIFFLAGS: Get ifnet flags.\n
 * - SIOCSIFFLAGS: Set ifnet flags.\n
 * - IFF_UP: Interface is up.\n
 * - IFF_BROADCAST: Broadcast address valid.\n
 * - IFF_LOOPBACK: Is a loopback net.\n
 * - IFF_POINTOPOINT: Is a point-to-point link.\n
 * - IFF_DRV_RUNNING: Resources allocated.\n
 * - IFF_NOARP: No address resolution protocol.\n
 * - IFF_MULTICAST: Supports multicast.\n
 * - IFF_DYNAMIC: Dialup device with changing addresses.\n
 * - IFF_DYNAMIC_S: Dialup device with changing addresses.\n
 *
 * - This API also supports the following options: \n
 *   - SIOCGIFADDR: Get ifnet address.\n
 *   - SIOCSIFADDR: Set ifnet address.\n
 *   - SIOCGIFNETMASK: Get net addr mask.\n
 *   - SIOCSIFNETMASK : Set net addr mask.\n
 *   - SIOCSIFHWADDR: Set IF mac_address.\n
 *   - SIOCGIFHWADDR: Get IF mac_address\n
 *   - SIOCGIFNAME: Get IF name.\n
 *   - SIOCSIFNAME: Set IF name.\n
 *   - SIOCGIFMTU: Get IF mtu size.\n
 *   - SIOCSIFMTU: Set IF mtu size.\n
 *   - SIOCGIFINDEX: Get IF index.\n
 *   - SIOCGIFCONF: Get ifnet config. \n
 *   - SIOCETHTOOL: Detect eth link status. \n
 *   - FIONBIO: Set/clear non-blocking i/o.\n
 *   - FIONREAD:get the size of buffer.\n
 * - For SIOCSIFNAME, the new name must be consisted by letters and numbers,
 * - and the letters must be in front of numbers.
 * The number range is from 0 to 255.\n @cond liteos
 * - For FIONREAD option, argp should point to an application variable of type signed int.
 * - FIONREAD is supported if LWIP_SO_RCVBUF is enabled.  \n @endcond
 * - For PF_PACKET sockets SIOCADDRT option is not supported. The options supported are:
 *   - FIONBIO
 *   - SIOCGIFADDR
 *   - SIOCSIFADDR
 *   - SIOCGIFNETMASK
 *   - SIOCSIFNETMASK
 *   - SIOCSIFHWADDR
 *   - SIOCGIFHWADDR
 *   - SIOCGIFFLAGS
 * - SIOCSIFFLAGS
 * - SIOCGIFNAME
 * - SIOCSIFNAME
 * - SIOCGIFINDEX
 * - SIOCGIFCONF
 * - For SIOCSIFADDR/SIOSIFNETMASK option, the gateway address is reset if the changed\n
 * netif was the default netif and the gateway was unreachable after changing.\n
 * Also duplicate network is forbidden.\n
 * - For SIOCADDRT, only gateway setting is supported(flags in "struct rtentry" must be RTF_GATEWAY).\n
 *
 */
 int lwip_ioctl(int s, long request, void *argp);

 /*
 Func Name:  lwip_fcntl
 */
 /**
 * @ingroup Socket_Interfaces
 * @brief
 *  The fcntl() function performs the operations described below on open files. The fd argument is a file descriptor.
 *  @li The available values for cmd are as follows:
 *   - F_GETFL: Get the file status flags and file access mode for the file description associated
 *   - with file descriptor. The flags returned may include non-standard file status flags
 *   - which the application did not set, provided that these additional flags
 *   - do not alter the behavior of a conforming application.
 *   - F_SETFL: val the file status flags for the file description associated with fildes
 *   - from thecorresponding bits in the third argument, val, taken as type int. Bits corresponding
 *   - to the file access mode and the file creation flags, that are set in arg shall be ignored.
 *   - If any bits in val other than those mentioned here are changed by the application, the result is unspecified.
 *   - If fildes does not support non-blocking operations.
 *   - it is unspecified whether the O_NONBLOCK flag will be ignored.
 *

 * @param[in]    s        Indicates the socket file descriptor.
 * @param[in]    cmd      Indicates a command to select an operation [F_GETFL, F_SETFL].
 * @param[in]    val      Indicates an additional flag, to set non-blocking.
 *
 * @return
 * Upon successful completion, the value returned depends on cmd as follows:
 * @li F_GETFL: Value of file status flags and access modes. The return value is not negative.
 * @li F_SETFL: Value other than -1.
 *
 * @par Errors
 *    @li The fcntl() function shall fail if:
 *     - <b> [EBADF] </b> : \n The field argument is not a valid opened file descriptor.
 *     - <b> [EINVAL] </b> : \n The cmd argument is invalid, or cmd not supported by implementation,
 *                              or if val is set to any other value other than O_NONBLOCK.
 *                              Only F_GETFL and F_SETFL are supported by lwIP.
 * @par POSIX Conformance:
   Implementation deviates from POSIX.1-2008 (IEEE Std 1003.1-2008, 2016 Edition).
   The following are the exceptions to conformance:
 - Function prototype does not support variable arguments like POSIX or Linux fcntl API.
 - The arg values to F_GETFL, and F_SETFL all represent flag values to allow for future growth.
 - Applications using these functions should do a read-modify-write operation on them,
 - rather than assuming that only the values defined by POSIX.1-2008 are valid.\
 - It is a common error to forget this, particularly in the case of F_SETFD.
 - Some implementations set additional file status flags to advise the application of default behavior,
 - even though the application did not request these flags.
 * @note

 * -  Only F_GETFL & F_SETFL commands are supported. For F_SETFL, only O_NONBLOCK is supported for val.
 * -  PF_PACKET sockets supports the F_SETFL and F_GETFL option.
 */
int lwip_fcntl(int s, int cmd, int val);

/*
 *  internal function.
 *  Call this function to intialise global socket resources
 */
int sock_init(void);

/**
 * @ingroup Socket_Interfaces
 * @brief
 *   This API is used to get TCP or UDP connection information.

 * @param[in]    s        Indicates a socket file descriptor.
 * @param[out]  conninfo  Connection information  details of given socket.
 *
 *
 * @return
 *    0: On success \n
 *    Negative value: On failure

 * @par Errors
 *  \li The lwip_get_conn_info() function fails if:
 *     - <b> [ERR_CLSD] </b>: The Connections are not valid TCP or UDP connections.
 *     - <b> [EIO] </b>: Internal Error , validation issue.
 *     - <b> [EOPNOTSUPP] </b>: Not a UDP/TCP connection or TCP connection in listen state.
 *     - <b> [ERR_CONN] </b>: For unconnected TCP connections.
 *
 * @note
 * - This function called to get TCP or UDP connection information.
 * - The void pointer is of type tcpip_conn.
 * - This API does not support getting connection information of the TCP socket in LISTEN state.\n
 */
int lwip_get_conn_info (int s, void *conninfo);

#if LWIP_API_RICH
struct lwip_sock *get_socket(int s);
#endif /* LWIP_API_RICH */
struct lwip_sock *get_socket_ext(int s);

#if LWIP_COMPAT_SOCKETS
#if LWIP_COMPAT_SOCKETS != 2
/** @ingroup socket */
#define accept(s, addr, addrlen)                     lwip_accept(s, addr, addrlen)
/** @ingroup socket */
#define bind(s, name, namelen)                       lwip_bind(s, name, namelen)
/** @ingroup socket */
#define shutdown(s, how)                             lwip_shutdown(s, how)
/** @ingroup socket */
#define getpeername(s, name, namelen)                lwip_getpeername(s, name, namelen)
/** @ingroup socket */
#define getsockname(s, name, namelen)                lwip_getsockname(s, name, namelen)
/** @ingroup socket */
#define setsockopt(s, level, optname, opval, optlen) lwip_setsockopt(s, level, optname, opval, optlen)
/** @ingroup socket */
#define getsockopt(s, level, optname, opval, optlen) lwip_getsockopt(s, level, optname, opval, optlen)
/** @ingroup socket */
#define closesocket(s)                               lwip_close(s)
/** @ingroup socket */
#define connect(s, name, namelen)                    lwip_connect(s, name, namelen)
/** @ingroup socket */
#define listen(s, backlog)                           lwip_listen(s, backlog)
/** @ingroup socket */
#define recv(s, mem, len, flags)                     lwip_recv(s, mem, len, flags)
/** @ingroup socket */
#define recvfrom(s, mem, len, flags, from, fromlen)  lwip_recvfrom(s, mem, len, flags, from, fromlen)
/** @ingroup socket */
#define send(s, dataptr, size, flags)                lwip_send(s, dataptr, size, flags)
/** @ingroup socket */
#define sendmsg(s, message, flags)                   lwip_sendmsg(s, message, flags)
/** @ingroup socket */
#define sendto(s, dataptr, size, flags, to, tolen)   lwip_sendto(s, dataptr, size, flags, to, tolen)
/** @ingroup socket */
#define socket(domain, type, protocol)               lwip_socket(domain, type, protocol)
#if LWIP_SOCKET_SELECT
/** @ingroup socket */
#define select(maxfdp1, readset, writeset, exceptset, timeout) \
                                                     lwip_select(maxfdp1, readset, writeset, exceptset, timeout)
#endif
/** @ingroup socket */
#define ioctlsocket(s, cmd, argp)                    lwip_ioctl(s, cmd, argp)
/** @ingroup socket */
#define inet_ntop(af, src, dst, size)                lwip_inet_ntop(af, src, dst, size)
/** @ingroup socket */
#define inet_pton(af, src, dst)                      lwip_inet_pton(af, src, dst)

#if LWIP_POSIX_SOCKETS_IO_NAMES
/** @ingroup socket */
#define read(s, mem, len)                            lwip_read(s, mem, len)
/** @ingroup socket */
#define write(s, dataptr, len)                       lwip_write(s, dataptr, len)
/** @ingroup socket */
#define writev(s, iov, iovcnt)                       lwip_writev(s, iov, iovcnt)
/** @ingroup socket */
#define close(s)                                     lwip_close(s)
/** @ingroup socket */
#define fcntl(s, cmd, val)                           lwip_fcntl(s, cmd, val)
/** @ingroup socket */
#define ioctl(s, cmd, argp)                          lwip_ioctl(s, cmd, argp)
#endif /* LWIP_POSIX_SOCKETS_IO_NAMES */
#endif /* LWIP_COMPAT_SOCKETS != 2 */

/*
 *  Func Name:  lwip_inet_ntop
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * This function converts the network address structure src in the af address family into a
 * character string.  The resulting string is copied to the buffer pointed to by dst, which
 * must be a non-null pointer. The following address families are currently supported:
 * AF_INET
 * src points to a struct in_addr (in network byte order) which is converted to an IPv4 network address
 *          in the dotted-decimal format, "ddd.ddd.ddd.ddd".The buffer dst must be at least INET_ADDRSTRLEN bytes long.
 *
 * AF_INET6
 * src points to a struct in6_addr (in network byte order) which is converted to a representation of this
 *          address in the most appropriate  IPv6  network  address format for this address.
 *          The buffer dst must be at least INET6_ADDRSTRLEN bytes long.
 *
 * @param[in]    af            Specifies the Address family.
 * @param[in]    src           Indicates Network Address structure.
 * @param[in]    dst           Indicates the buffer to store the result string.
 * @param[in]    size          Indicates the number of bytes available in the dst string.
 *
 * @return
 *  non NULL pointer to dst: On success \n
 *  NULL: Error case,with errno set to indicate the error \n
 *
 * @par Errors
 *    @li The inet_ntop() function shall fail if:
 *     - <b> [EAFNOSUPPORT] </b> : af was not a valid address family.
 *     - <b> [ENOSPC] </b> : The converted address string would exceed the size given by size.
 */
const char *lwip_inet_ntop(int af, const void *src, char *dst, socklen_t size);

/*
 *  Func Name:  lwip_inet_pton
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * This function converts the character string src into a network address structure in the
 * af address family, then copies the network address structure to dst.The following address
 * families are currently supported:
 * AF_INET
 *          src points to a character string containing an IPv4 network address in dotted-decimal format,
 *           "ddd.ddd.ddd.ddd", where ddd is a decimal number of up to  three digits in the range 0 to 255.
 *           The address is converted to a struct in_addr and copied to dst,
 *           which must be sizeof(struct in_addr) (4) bytes (32 bits) long.
 *
 * AF_INET6
 *          src  points  to  a  character  string  containing  an  IPv6  network  address.  The address is converted
 *          to a struct in6_addr and copied to dst, which must be sizeof(struct in6_addr) (16) bytes (128 bits) long.
 *
 * @param[in]    af            Specifies the Address family.
 * @param[in]    src           Indicates a character string with IPv4 or IPv6 address.
 * @param[in]    dst           Indicates Network address structure.
 *
 * @return
 *  1: On success (network address was successfully converted) \n
 *  0: if src doesnot contain character string representing a valid network address in the specified address family\n
 *  -1: invalid address family and errno is set\n
 *
 * @par Errors
 *    @li The inet_pton() function shall fail if:
 *     - <b> [EAFNOSUPPORT] </b> : af was not a valid address family.
 */
int lwip_inet_pton(int af, const char *src, void *dst);

#endif /* LWIP_COMPAT_SOCKETS */

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_SOCKET */

#endif /* LWIP_HDR_SOCKETS_H */
