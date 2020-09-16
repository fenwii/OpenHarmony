/*
 * Description: lwIP Options Configuration
 */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef LWIP_LITEOS_COMPAT
#define LWIP_LITEOS_COMPAT  1
#endif

/* Set to 1 if target platform is linux */
#ifndef LWIP_LINUX_COMPAT
#define LWIP_LINUX_COMPAT   0
#endif

#ifndef LWIP_COMPAT_SOCKETS
#define LWIP_COMPAT_SOCKETS 2
#define LWIP_POSIX_SOCKETS_IO_NAMES 0
#endif

#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS 1

#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

#ifndef LWIP_CHKSUM_ALGORITHM
#define LWIP_CHKSUM_ALGORITHM       4
#endif

#ifndef LWIP_PLATFORM_BYTESWAP
#define LWIP_PLATFORM_BYTESWAP 1
#endif

#ifndef LWIP_NETIF_IFINDEX_MAX
#define LWIP_NETIF_IFINDEX_MAX 0xFE
#endif

#ifndef LWIP_PROVIDE_ERRNO
#define LWIP_PROVIDE_ERRNO 1
#endif

/** Define LWIP_COMPAT_MUTEX if the port has no mutexes and binary semaphores
    should be used instead */
#ifndef LWIP_COMPAT_MUTEX
#define LWIP_COMPAT_MUTEX 0
#endif

#ifndef LWIP_COMPAT_MUTEX_ALLOWED
#define LWIP_COMPAT_MUTEX_ALLOWED        0
#endif

/**
 * LWIP_SO_SNDTIMEO==1: Enable send timeout for sockets/netconns and
 * SO_SNDTIMEO processing.
 */
#ifndef LWIP_SO_SNDTIMEO
#define LWIP_SO_SNDTIMEO                1
#endif

/**
 * LWIP_SO_RCVTIMEO==1: Enable receive timeout for sockets/netconns and
 * SO_RCVTIMEO processing.
 */
#ifndef LWIP_SO_RCVTIMEO
#define LWIP_SO_RCVTIMEO                1
#endif

/**
 * LWIP_SO_BINDTODEVICE==1: Enable bind sockets/netconns to specific netif
 */
#ifndef LWIP_SO_BINDTODEVICE
#define LWIP_SO_BINDTODEVICE         1
#endif

/**
 * LWIP_SO_DONTROUTE==1: Enable don't use universal route entry
 */
#ifndef LWIP_SO_DONTROUTE
#define LWIP_SO_DONTROUTE         1
#endif

#ifndef LWIP_SACK
#define LWIP_SACK           1
#endif

#if LWIP_SACK
#ifndef LWIP_SACK_PERF_OPT
#define LWIP_SACK_PERF_OPT 1
#endif
#else
#define LWIP_SACK_PERF_OPT 0
#endif

#ifndef LWIP_SACK_CWND_OPT
#define LWIP_SACK_CWND_OPT  LWIP_SACK_PERF_OPT
#endif

#ifndef LWIP_SACK_DATA_SEG_PIGGYBACK
#define LWIP_SACK_DATA_SEG_PIGGYBACK       (LWIP_SACK & 1)
#endif

/*
 * @page RFC-5827
 * @par  RFC-5827 Appendix A.  Compliance Information
 * @par Compliant Sections
 * <Appendix A. Research Issues in Adjusting the Duplicate ACK Threshold>
 * @par Behavior Description
 * <Behavior:  Reducing the number of duplicate acks for fast retransmit has drawback during minor \n
 * network reordering.\n
 * Our node do not realize the mitigations proposed. So MITIGATION A.1, MITIGATION A.2 and \n
 * MITIGATION A.3 are not implemented.>
 */
#ifndef LWIP_TCP_ER_SUPPORT
#define LWIP_TCP_ER_SUPPORT           1
#endif

#if LWIP_SACK
#ifndef LWIP_TCP_TLP_SUPPORT
#define LWIP_TCP_TLP_SUPPORT 1
#endif
#else
#define LWIP_TCP_TLP_SUPPORT 0
#endif

#if LWIP_SACK
#ifndef LWIP_FACK_THRESHOLD_BASED_FR
#define LWIP_FACK_THRESHOLD_BASED_FR 1
#endif
#else
#define LWIP_FACK_THRESHOLD_BASED_FR 0
#endif

/**
 * NO_SYS==1: Provides very minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                  0

/* ---------- DEBUG options --------- */
#ifndef LWIP_DEV_DEBUG
#define LWIP_DEV_DEBUG
#endif

/* LWIP_DEBUG_INFO is opened by default. */
#ifndef LWIP_DEBUG_INFO
#define LWIP_DEBUG_INFO
#endif
#ifndef LWIP_DBG_TYPES_ON
#define LWIP_DBG_TYPES_ON               LWIP_DBG_ON
#endif
#ifndef IP_DEBUG
#define IP_DEBUG                        LWIP_DBG_OFF
#endif
#ifndef ETHARP_DEBUG
#define ETHARP_DEBUG                   LWIP_DBG_OFF
#endif
#ifndef NETIF_DEBUG
#define NETIF_DEBUG                     LWIP_DBG_OFF
#endif

#if LWIP_LITEOS_COMPAT
/**
 * MEM_LIBC_MALLOC==1: Use malloc/free/realloc provided by your C-library
 * instead of the lwIP internal allocator. Can save code size if you
 * already use it.
 */
#define MEM_LIBC_MALLOC         1
#ifndef MEM_SIZE
#define MEM_SIZE                        (4*1024*1024)
#endif

#ifndef MEM_LIBC_MALLOC_TOTAL_SIZE_LIMIT
#define MEM_LIBC_MALLOC_TOTAL_SIZE_LIMIT 0
#endif

#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS 1
#else
/*
 * MEM_SIZE: the size of the heap memory. If the application will send
 * a lot of data that needs to be copied, this should be set high.
 */
#ifndef MEM_SIZE
#define MEM_SIZE               (512*1024)
#endif

#endif

#if MEM_LIBC_MALLOC
#ifndef MEM_PBUF_RAM_SIZE_LIMIT
#define MEM_PBUF_RAM_SIZE_LIMIT   1
#endif
#endif

#ifndef MAX_NUM_PID
#define MAX_NUM_PID            128
#endif

/**
 * Defines the align size of the DMA memory. If set to 1, then not using DMA.
 */
#ifndef MEM_MALLOC_DMA_ALIGN
#if LWIP_LITEOS_COMPAT
#define MEM_MALLOC_DMA_ALIGN            64
#else
#define MEM_MALLOC_DMA_ALIGN            1
#endif
#endif

/**
 * Attention: Be careful while configure large sockets number, i.e, greater than 128, for that
 * LWIP_NUM_SOCKETS is bind with file system descriptons CONFIG_NFILE_DESCRIPTORS.
 * If socket num is large, file descriptions for file system would be small. See vfs_config.h
 * for detail.
 */
#ifndef LWIP_NUM_SOCKETS_MAX
#define LWIP_NUM_SOCKETS_MAX 128
#endif

/**
 * LWIP_NUM_SOCKETS can be used to override DEFAULT_LWIP_NUM_SOCKETS in lwipopts_*.h
 */
#ifndef LWIP_NUM_SOCKETS

/**
 * DEFAULT_LWIP_NUM_SOCKETS is default number of sockets.
 */
#ifndef DEFAULT_LWIP_NUM_SOCKETS
#define DEFAULT_LWIP_NUM_SOCKETS        128
#endif /* DEFAULT_LWIP_NUM_SOCKETS */

#else /* else LWIP_NUM_SOCKETS */

#ifndef DEFAULT_LWIP_NUM_SOCKETS

#if LWIP_NUM_SOCKETS > 0
#define DEFAULT_LWIP_NUM_SOCKETS        LWIP_NUM_SOCKETS
#else /* else LWIP_NUM_SOCKETS > 0 */
#define DEFAULT_LWIP_NUM_SOCKETS        128
#endif /* LWIP_NUM_SOCKETS */

#endif /* DEFAULT_LWIP_NUM_SOCKETS */
#endif /* LWIP_NUM_SOCKETS */

/*
 * Provides flexibility to use configured values to spread across code
 */
#ifndef LWIP_ALLOW_SOCKET_CONFIG
#define LWIP_ALLOW_SOCKET_CONFIG 1
#endif

#if LWIP_ALLOW_SOCKET_CONFIG == 0
#ifndef LWIP_CONFIG_NUM_SOCKETS
#define LWIP_CONFIG_NUM_SOCKETS         DEFAULT_LWIP_NUM_SOCKETS
#endif

#else /* LWIP_ALLOW_SOCKET_CONFIG */
#ifndef LWIP_CONFIG_NUM_SOCKETS
extern unsigned int g_lwip_num_sockets;
#define LWIP_CONFIG_NUM_SOCKETS         ((int)g_lwip_num_sockets)
#endif
#endif /* LWIP_ALLOW_SOCKET_CONFIG */

/*
 * MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
 * sends a lot of data out of ROM (or other static memory), this
 * should be set high.
 */
#ifndef MEMP_NUM_PBUF
#define MEMP_NUM_PBUF           ((LWIP_CONFIG_NUM_SOCKETS) * 2)
#endif

/*
 * Defines the number of raw connection PCBs
 * (requires the LWIP_RAW option).
 */
#ifndef MEMP_NUM_RAW_PCB
#define MEMP_NUM_RAW_PCB                LWIP_CONFIG_NUM_SOCKETS
#endif

/*
 * Defines the number of struct tcpip_msg, which are used
 * for callback/timeout API communication.
 * (only needed if you use tcpip.c)
 */
#ifndef MEMP_NUM_TCPIP_MSG_API
#define MEMP_NUM_TCPIP_MSG_API          64
#endif

/*
 * Defines the number of struct tcpip_msg, which are used
 * for incoming packets.
 * (only needed if you use tcpip.c)
 */
#ifndef MEMP_NUM_TCPIP_MSG_INPKT
#define MEMP_NUM_TCPIP_MSG_INPKT        512
#endif

#ifndef MEMP_NUM_NETCONN
#define MEMP_NUM_NETCONN        ((LWIP_CONFIG_NUM_SOCKETS) * 4)
#endif

/*
 * Defines the number of struct netbufs.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#ifndef MEMP_NUM_NETBUF
#define MEMP_NUM_NETBUF         (65535 * 3 * (LWIP_CONFIG_NUM_SOCKETS) / ((IP_FRAG_MAX_MTU) - 20 - 8))
#endif

/*
 * Defines the number of simulateously queued outgoing
 * packets (pbufs) that are waiting for an ARP request (to resolve
 * their destination address) to finish.
 * (requires the ARP_QUEUEING option)
 */
#ifndef MEMP_NUM_ARP_QUEUE
#define MEMP_NUM_ARP_QUEUE      (65535 * (LWIP_CONFIG_NUM_SOCKETS) / ((IP_FRAG_MAX_MTU)- 20 - 8))
#endif

/** Indicates the number of UDP protocol control blocks. One per active UDP "connection". */
#ifndef MEMP_NUM_UDP_PCB
#define MEMP_NUM_UDP_PCB        LWIP_CONFIG_NUM_SOCKETS
#endif

/** MEMP_NUM_TCP_PCB: Indicates the number of simultaneously active TCP connections. */
#ifndef MEMP_NUM_TCP_PCB
#define MEMP_NUM_TCP_PCB        LWIP_CONFIG_NUM_SOCKETS
#endif

/** MEMP_NUM_TCP_PCB_LISTEN: Indicates the number of listening TCP connections. */
#ifndef MEMP_NUM_TCP_PCB_LISTEN
#define MEMP_NUM_TCP_PCB_LISTEN LWIP_CONFIG_NUM_SOCKETS
#endif

#ifndef IP_FRAG_MAX_MTU
#define IP_FRAG_MAX_MTU         1500
#endif

/*
 * As per RFC 791, "Every internet module must be able to forward a datagram of 68
 * octets without further fragmentation.  This is because an internet header
 * may be up to 60 octets, and the minimum fragment is 8 octets."
 */
#ifndef IP_FRAG_MIN_MTU
#define IP_FRAG_MIN_MTU            68
#endif

#ifndef IP_REASS_MAX_PBUFS
#define IP_REASS_MAX_PBUFS   ((65535 * 2 * (LWIP_CONFIG_NUM_SOCKETS)) / ((IP_FRAG_MAX_MTU) - 20 - 8))
#endif
/* Max size(65535 + extra buffer(8192) per MAX MTU) */
#ifndef IP_REASS_MAX_PBUFS_PER_PKT
#define IP_REASS_MAX_PBUFS_PER_PKT   ((65535 + 8192) / ((IP_FRAG_MAX_MTU) - 20 - 8))
#endif

/* TCP Maximum segment size. */
#ifdef LWIP_TCP_MSS
#undef TCP_MSS      /* ensure TCP_MSS value is overridden by LWIP_TCP_MSS */
#define TCP_MSS                 LWIP_TCP_MSS
#else /* LWIP_TCP_MSS */
#ifndef TCP_MSS
#define TCP_MSS  ((IP_FRAG_MAX_MTU) - 20 - 20)
#endif /* TCP_MSS */
#endif /* LWIP_TCP_MSS */

/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP segments. */
#ifndef MEMP_NUM_TCP_SEG
#define MEMP_NUM_TCP_SEG        ((((TCP_SND_BUF) * 3 / 2) + (TCP_WND)) * (LWIP_CONFIG_NUM_SOCKETS) / (TCP_MSS))
#endif

/* ---------- Pbuf options ---------- */
/** PBUF_POOL_SIZE: Indicates the number of buffers in the pbuf pool. */
#ifndef PBUF_POOL_SIZE
#define PBUF_POOL_SIZE          64
#endif

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#ifndef PBUF_POOL_BUFSIZE
#define PBUF_POOL_BUFSIZE       1550
#endif

#ifndef PBUF_LINK_CHKSUM_LEN
#define PBUF_LINK_CHKSUM_LEN  0
#endif
/* ---------- ARP options ---------- */
/**
 * ARP_QUEUEING==1: Multiple outgoing packets are queued during hardware address
 * resolution. By default, only the most recent packet is queued per IP_add
 * This is sufficient for most protocols and mainly reduces TCP connection
 * startup time. Set this to 1 if you know that your application sends more than one
 * packet in a row to an IP_add that is not in the ARP cache.
 */
#ifndef ARP_QUEUEING
#define ARP_QUEUEING                    1
#endif

/**
 * ETHARP_TRUST_IP_MAC==1: Incoming IP packets cause the ARP table to be
 * updated with the source MAC and IP address supplied in the packet.
 * You may want to disable this if you do not trust LAN peers to have the
 * correct addresses, or as a limited approach to attempt to handle
 * spoofing. If disabled, lwIP will need to make a new ARP request if
 * the peer is not already in the ARP table, adding a little latency.
 * The peer is in the ARP table if it requested our address before.
 * Also notice that this slows down input processing of every IP packet.
 */
#ifndef ETHARP_TRUST_IP_MAC
#define ETHARP_TRUST_IP_MAC             1
#endif

/** Defines the number of bytes added before the ethernet header to ensure
 * alignment of payload after that header. Since the header is 14 bytes long,
 * without this padding, addresses in the IP header will not be aligned
 * on a 32-bit boundary. So setting this to 2 can speed up 32-bit-platforms.
 */
#ifndef ETH_PAD_SIZE
#define ETH_PAD_SIZE                    2
#endif

/** ETHARP_SUPPORT_STATIC_ENTRIES==1: Enables code to support static ARP table
 * entries (using etharp_add_static_entry/etharp_remove_static_entry).
 */
#ifndef ETHARP_SUPPORT_STATIC_ENTRIES
#define ETHARP_SUPPORT_STATIC_ENTRIES   1
#endif

/* ---------- TCP options ---------- */
#ifndef LWIP_TCP
#define LWIP_TCP                1
#endif
/* @ingroup Config_TCP
* Defines the TCP TTL value.
*/
#ifndef TCP_TTL
#define TCP_TTL                 255
#endif

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ         LWIP_TCP

/**
 * Defines the mailbox size for the tcpip thread messages
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when tcpip_init is called.
 */
#ifndef TCPIP_MBOX_SIZE
#define TCPIP_MBOX_SIZE         512
#endif

/**
 * Defines the mailbox size for the incoming packets on a
 * NETCONN_TCP. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#ifndef DEFAULT_TCP_RECVMBOX_SIZE
#define DEFAULT_TCP_RECVMBOX_SIZE       128
#endif

/**
 * Defines the mailbox size for the incoming connections.
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when the acceptmbox is created.
 */
#ifndef DEFAULT_ACCEPTMBOX_SIZE
#define DEFAULT_ACCEPTMBOX_SIZE         32
#endif

#ifndef MEMP_NUM_REASSDATA
#define MEMP_NUM_REASSDATA  (2 * (LWIP_CONFIG_NUM_SOCKETS))
#endif

#ifdef LWIP_DBG_PREPROCESSOR
#pragma message(VAR_NAME_VALUE(TCP_MSS))
#endif

/* @ingroup Config_TCP
* TCP sender buffer space (bytes). */
#ifndef TCP_SND_BUF
#define TCP_SND_BUF         65535
#endif

/* @ingroup Config_TCP
TCP sender buffer space (pbufs). This must be at least = 2 *
   TCP_SND_BUF/TCP_MSS for things to work. */
#ifndef TCP_SND_QUEUELEN
#define TCP_SND_QUEUELEN        ((8 * (TCP_SND_BUF)) / (TCP_MSS))
#endif
/**
 * Defines the size of a TCP receive window.
 */
#ifndef TCP_WND
#define TCP_WND            32768
#endif

/**
 * Defines the Maximum number of retransmissions of data segments.
 */
#ifndef TCP_MAXRTX
#define TCP_MAXRTX                      15
#endif

/* ---------- IP options ---------- */
/**
 * IP_FRAG_USES_STATIC_BUF==1: Use a static MTU-sized buffer for IP
 * fragmentation. Otherwise pbufs are allocated and reference the original
 * packet data to be fragmented (or with LWIP_NETIF_TX_SINGLE_PBUF==1,
 * new PBUF_RAM pbufs are used for fragments).
 * Note: IP_FRAG_USES_STATIC_BUF==1 may not be used for DMA-enabled MACs.
 */
#ifndef IP_FRAG_USES_STATIC_BUF
#define IP_FRAG_USES_STATIC_BUF         1
#endif

/*
 * Defines the assumed maximum MTU on any interface for IP fragment buffer
 * (requires IP_FRAG_USES_STATIC_BUF==1)
 */
#if IP_FRAG_USES_STATIC_BUF && !defined(IP_FRAG_MAX_MTU)
#define IP_FRAG_MAX_MTU                 1500
#endif

/* As per RFC 791, "Every internet module must be able to forward a datagram of 68
 * octets without further fragmentation.  This is because an internet header
 * may be up to 60 octets, and the minimum fragment is 8 octets." */
#if IP_FRAG_USES_STATIC_BUF && !defined(IP_FRAG_MIN_MTU)
#define IP_FRAG_MIN_MTU            68
#endif

/* ---------- ICMP options ---------- */
/**
 * LWIP_ICMP==1: Enables the ICMP module inside the IP stack.
 */
#ifndef LWIP_ICMP
#define LWIP_ICMP                       1
#endif

/* ---------- IGMP options ---------- */
#ifndef LWIP_IGMP
#define LWIP_IGMP                       1
#endif

/* ---------- DHCP options ---------- */
/**
 * LWIP_DHCP==1: Enables the DHCP module.
 */
#ifndef LWIP_DHCP
#define LWIP_DHCP               1
#endif

/* ---------- DNS options ---------- */
/**
 * LWIP_DNS==1: Turn on DNS module. UDP must be available for DNS
 * transport.
 */
#ifndef LWIP_DNS
#define LWIP_DNS                 1
#endif

/* ---------- UDP options ---------- */
/**
 * LWIP_UDP==1: Turns on UDP.
 */
#ifndef LWIP_UDP
#define LWIP_UDP                1
#endif

#ifndef UDP_TTL
#define UDP_TTL                 255
#endif
/**
 * Defines the mailbox size for the incoming packets on a
 * NETCONN_UDP. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#ifndef DEFAULT_UDP_RECVMBOX_SIZE
#define DEFAULT_UDP_RECVMBOX_SIZE       128
#endif

/* -----------RAW options -----------*/
#ifndef DEFAULT_RAW_RECVMBOX_SIZE

/**
 * LWIP_RAW==1: Enables the application layer to hook into the IP layer itself.
 */
#if !defined LWIP_RAW || defined __DOXYGEN__
#define LWIP_RAW                        1
#endif

/**
 * Enable to support PF_PACKET RAW sockets
*/
#if defined(LWIP_RAW) && LWIP_RAW
#ifndef PF_PKT_SUPPORT
#define PF_PKT_SUPPORT 1
#endif
#endif

/**
 * Defines the mailbox size for the incoming packets on a
 * NETCONN_RAW. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#define DEFAULT_RAW_RECVMBOX_SIZE       128
#endif

#ifndef LWIP_MAX_PF_RAW_SEND_SIZE
#define LWIP_MAX_PF_RAW_SEND_SIZE (0xFFFF - 40) //  - IPv6 header
#endif

/* -----------LOOPIF options -----------*/
#ifndef LWIP_HAVE_LOOPIF
#define LWIP_HAVE_LOOPIF                1
#endif

/* -----------LOOPBACK options -----------*/
#ifndef LWIP_NETIF_LOOPBACK
#define LWIP_NETIF_LOOPBACK             1
#endif

/* ---------- Statistics options ---------- */
/**
 * LWIP_STATS==1: Enables statistics gathering in lwip_stats.
 */
#ifndef LWIP_STATS
#define LWIP_STATS 1
#endif

/* ---------- TFTP options ---------- */
#ifndef LWIP_TFTP
#define LWIP_TFTP               1
#endif

/* ---------- SNTP options ---------- */
#ifndef LWIP_SNTP
#define LWIP_SNTP                      1
#endif

/**
 * SO_REUSE==1: Enable SO_REUSEADDR option.
 */
#ifndef SO_REUSE
#define SO_REUSE                        1
#endif

#define LWIP_ETHERNET               1
#define LWIP_NETCONN                    1
#define LWIP_SOCKET                    1

#ifndef IP_FORWARD
#define IP_FORWARD                      0
#endif

#define LWIP_DHCPS_DISCOVER_BROADCAST   LWIP_LITEOS_COMPAT

#if LWIP_LITEOS_COMPAT
#ifndef TCPIP_THREAD_STACKSIZE
#define TCPIP_THREAD_STACKSIZE          0x6000
#endif
#ifndef TCPIP_THREAD_PRIO
#define TCPIP_THREAD_PRIO               5
#endif

#ifndef LWIP_SOCKET_START_NUM
#define LWIP_SOCKET_START_NUM CONFIG_NFILE_DESCRIPTORS
#endif

#ifndef LWIP_SOCKET_OFFSET
#define LWIP_SOCKET_OFFSET CONFIG_NFILE_DESCRIPTORS
#endif

#ifndef LWIP_ENABLE_LOS_SHELL_CMD
#define LWIP_ENABLE_LOS_SHELL_CMD     1
#endif
#ifndef ERRNO
#define ERRNO
#endif
#ifndef LWIP_PROVIDE_ERRNO
#define LWIP_PROVIDE_ERRNO 0
#endif
/* Currently pthread_cond_timedwait() in liteos doesn't support absolute time */
#ifndef LWIP_USE_POSIX_COND_WAIT_WITH_ABS_TIMEOUT
#define LWIP_USE_POSIX_COND_WAIT_WITH_ABS_TIMEOUT 0
#endif

#ifndef LWIP_INET_ADDR_FUNC
#define LWIP_INET_ADDR_FUNC         1
#endif

#ifndef LWIP_INET_NTOA_FUNC
#define LWIP_INET_NTOA_FUNC         1
#endif

#ifndef LWIP_INET_ATON_FUNC
#define LWIP_INET_ATON_FUNC         1
#endif

#else
#define ERRNO
#define LWIP_PROVIDE_ERRNO 1

#ifndef LWIP_INET_ADDR_FUNC
#define LWIP_INET_ADDR_FUNC         1
#endif

#ifndef LWIP_INET_NTOA_FUNC
#define LWIP_INET_NTOA_FUNC         1
#endif

#ifndef LWIP_INET_ATON_FUNC
#define LWIP_INET_ATON_FUNC         1
#endif

#endif

/* ---------- Socket Filter options ---------- */
/**
  * implement sock filter based on BPF.
  * BPF-extension was not supported.
  * only AF_PACKET RAW socket support socket filter now,
  * we would add supports for other socket type in the feature.
*/
#if defined(LWIP_RAW) && LWIP_RAW
#ifndef LWIP_SOCK_FILTER
#define LWIP_SOCK_FILTER 1
#endif
#else
#define LWIP_SOCK_FILTER 0
#endif

/* Requesting application to configure a cryptographically strong random number generator to LWIP_RAND macro */
#ifndef LWIP_RAND
#define LWIP_RAND g_stlwIPSecSspCallbacks.pfRand
#endif

#ifndef LWIP_STATIC
#define LWIP_STATIC static
#endif

#ifndef LWIP_ALWAYS_SEND_HWTYPE_AS_ETHER_IN_DHCP
#define LWIP_ALWAYS_SEND_HWTYPE_AS_ETHER_IN_DHCP    1
#endif

#ifndef USE_ONLY_PRIMARY_IFACE
#define USE_ONLY_PRIMARY_IFACE 1
#endif

#ifndef DRIVER_STATUS_CHECK
#define DRIVER_STATUS_CHECK    0
#endif

#if DRIVER_STATUS_CHECK
#ifndef DRIVER_WAKEUP_INTERVAL
#define DRIVER_WAKEUP_INTERVAL 120000
#endif
#endif

/* ---------- NETIF options ---------- */
/**
 * LWIP_NETIF_API==1: Supports netif api (in netifapi.c)
 */
#ifndef LWIP_NETIF_API
#define LWIP_NETIF_API                  1
#endif

/*
 * LWIP_NETIF_LINK_CALLBACK==1: Supports a callback function from an interface
 * whenever the link changes. Example: when link goes down.
 */
#ifndef LWIP_NETIF_LINK_CALLBACK
#define LWIP_NETIF_LINK_CALLBACK        1
#endif

/*
 * LWIP_NETIF_NUM_MAX==255: Defines the maximum support number of same type netif.
 */
/*
 * Increase the count of netifs supported by stack.
 * Currently stack restricts the number of netif to 5, but older versions of linux kernel supports
 * upto 255 interfaces . New versions donot have these restrictions but we stick to 255
 */
#ifndef LWIP_NETIF_NUM_MAX
#define LWIP_NETIF_NUM_MAX            255
#endif

/* ---------- SOCKET options ---------- */
/**
 * LWIP_SO_RCVBUF==1: Enables SO_RCVBUF processing.
 */
#ifndef LWIP_SO_RCVBUF
#define LWIP_SO_RCVBUF                  1
#endif

/* ---------- Statistics options ---------- */
/**
 * LWIP_STATS_DISPLAY==1: Compile in the statistics output functions.
 */
#ifndef LWIP_STATS_DISPLAY
#define LWIP_STATS_DISPLAY              1
#endif

/* ---------- Debugging options ---------- */
/**
 * LWIP_DBG_MIN_LEVEL: After masking, the value of the debug is
 * compared against this value. If it is smaller, then debugging
 * messages are written.
 */
#ifndef LWIP_DBG_MIN_LEVEL
#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_OFF
#endif

/**
 * LWIP_DBG_TYPES_ON: A mask that can be used to globally enable/disable
 * debug messages of certain types.
 */
#ifndef LWIP_DBG_TYPES_ON
#define LWIP_DBG_TYPES_ON               LWIP_DBG_OFF
#endif

#ifndef LWIP_SOCKET_POLL
#define LWIP_SOCKET_POLL 1
#endif

/**
 * LWIP_TCP_INFO==1: support get tcp info by getsockopt API
 */
#ifndef LWIP_TCP_INFO
#define LWIP_TCP_INFO 1
#endif

#ifndef LWIP_RPL
#define LWIP_RPL 0
#endif

#ifndef PBUF_API
#define PBUF_API 0
#endif

#if !defined(LWIP_RPL) || (0 == LWIP_RPL)
#ifndef LWIP_RPL_TIMER_COUNT
#define LWIP_RPL_TIMER_COUNT 0
#endif
#else
#ifndef LWIP_RPL_TIMER_COUNT
#define LWIP_RPL_TIMER_COUNT 12
#endif
#endif

#ifndef LWIP_IPV6_MLD
#define LWIP_IPV6_MLD 1
#endif

#ifndef LWIP_MLD6_ENABLE_MLD_ON_DAD
#define LWIP_MLD6_ENABLE_MLD_ON_DAD   LWIP_IPV6 && LWIP_IPV6_MLD
#endif

#ifndef LWIP_MLD6_DONE_ONLYFOR_LAST_REPORTER
#define LWIP_MLD6_DONE_ONLYFOR_LAST_REPORTER   LWIP_IPV6 && LWIP_IPV6_MLD
#endif

#if defined (__cplusplus) && __cplusplus
}
#endif /* __cplusplus */

#endif /* __LWIPOPTS_H__ */

