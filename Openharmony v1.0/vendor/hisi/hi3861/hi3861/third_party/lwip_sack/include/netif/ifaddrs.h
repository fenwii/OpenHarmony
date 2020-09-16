/*
 * Description: declare BSD APIs : getifaddrs freeifaddrs
 */
#if LWIP_IFADDRS
#if LWIP_IPV4 && LWIP_IPV6
#ifndef __LWIP_IFADDRS_H
#define __LWIP_IFADDRS_H

#include "lwip/netif.h"
#include "lwip/sockets.h"
#include "lwip/netif.h"
#include "arch/cc.h"

#if LWIP_LITEOS_COMPAT

#ifndef SIOCETHTOOL
#define SIOCETHTOOL  _IOW('i', 56, struct ifreq)
#endif

#else
#define SIOCADDRT   _IOW('R', 9, struct rtentry)
#define SIOCDELRT   _IOW('R', 10, struct rtentry)

#define SIOCGIFFLAGS  _IOWR('i', 17, struct ifreq)  /* get ifnet flags */
#define SIOCSIFFLAGS   _IOW('i', 16, struct ifreq)  /* set ifnet flags */
#define SIOCGIFADDR _IOWR('i', 33, struct ifreq)  /* get ifnet address */
#define SIOCSIFADDR  _IOW('i', 12, struct ifreq)  /* set ifnet address */

#define SIOCDIFADDR _IOW('i', 25, struct ifreq) /* delete IF addr */

#define SIOCGIFNETMASK  _IOWR('i', 37, struct ifreq)  /* get net addr mask */
#define SIOCSIFNETMASK   _IOW('i', 22, struct ifreq)  /* set net addr mask */
#define SIOCSIFHWADDR  _IOW('i', 140, struct ifreq) /* set IF name */
#define SIOCGIFHWADDR  _IOW('i', 141, struct ifreq) /* set IF name */
#define SIOCGIFNAME  _IOW('i', 142, struct ifreq) /* set IF name */
#define SIOCSIFNAME  _IOW('i', 40, struct ifreq)  /* set IF name */

/** Gets IF mtu */
#define SIOCGIFMTU  _IOWR('i', 51, struct ifreq)
/** Sets IF mtu */
#define SIOCSIFMTU  _IOW('i', 52, struct ifreq)
/** ethtool */
#define SIOCETHTOOL  _IOW('i', 56, struct ifreq)

/* provide PF_PACKET option on SOCK_RAW */
#define  SIOCGIFINDEX  _IOWR('i', 32, struct ifreq) /* get IF index */
#define  SIOCGIFCONF  _IOWR('i', 36, struct ifconf) /* get ifnet list */

/** (n) Indicates that the interface is up */
#define IFF_UP    0x1
/** (i) Indicates that the broadcast address valid */
#define IFF_BROADCAST 0x2
/** (n) Turns on debugging */
#define IFF_DEBUG 0x4
/** (i) A loopback net */
#define IFF_LOOPBACK  0x8
/** (i) Indicates a point-to-point link */
#define IFF_POINTOPOINT 0x10
/*      0x20       was IFF_SMART */
/** (d) Indicates that the resources are allocated */
#define IFF_DRV_RUNNING 0x40
/** (n) No address resolution protocol */
#define IFF_NOARP 0x80
/** (n) Receive all packets */
#define IFF_PROMISC 0x100
/** (n) Receive all multicast packets */
#define IFF_ALLMULTI  0x200
/** (d) Indicates that the tx hardware queue is full */
#define IFF_DRV_OACTIVE 0x400
/** (i) Cannot hear own transmissions */
#define IFF_SIMPLEX 0x800
/** Per link layer defined bit */
#define IFF_LINK0 0x1000
/** Per link layer defined bit */
#define IFF_LINK1 0x2000
/** Per link layer defined bit */
#define IFF_LINK2 0x4000
/** Use alternate physical connection */
#define IFF_ALTPHYS IFF_LINK2
/** Supports multicast */
#define IFF_MULTICAST 0x8000
/** (i) Unconfigurable using ioctl(2) */
#define IFF_CANTCONFIG  0x10000
/** (n) User-requested promisc mode */
#define IFF_PPROMISC  0x20000
/** (n) User-requested IFF_MONITOR mode */
#define IFF_MONITOR 0x40000
/** (n) Static ARP */
#define IFF_STATICARP 0x80000
/** (n) Interface is winding down */
#define IFF_DYING 0x200000
/** (n) Interface is being renamed */
#define IFF_RENAMING  0x400000
/** (n) Dialup device with changing addresses */
#define IFF_DYNAMIC   0x800000
/** (n) Dialup device with changing addresses */
#define IFF_DYNAMIC_S   0x1000000

#define IFF_RUNNING IFF_DRV_RUNNING
struct ifreq {
#define IFHWADDRLEN 6
  union {
    char ifrn_name[IFNAMSIZ];
  } ifr_ifrn;
  union {
    struct sockaddr ifru_addr;
    struct sockaddr ifru_dstaddr;
    struct sockaddr ifru_broadaddr;
    struct sockaddr ifru_netmask;
    struct sockaddr ifru_hwaddr;
    short ifru_flags[2];
    int ifru_ivalue;
    int ifru_mtu;
    char ifru_slave[IFNAMSIZ];
    char ifru_newname[IFNAMSIZ];
    void  *ifru_data;
  } ifr_ifru;
};
#define ifr_name ifr_ifrn.ifrn_name
#define ifr_hwaddr ifr_ifru.ifru_hwaddr
#define ifr_addr ifr_ifru.ifru_addr
#define ifr_dstaddr ifr_ifru.ifru_dstaddr
#define ifr_broadaddr ifr_ifru.ifru_broadaddr
#define ifr_netmask ifr_ifru.ifru_netmask
#define ifr_flags ifr_ifru.ifru_flags[0]  /* flags (low 16 bits) */
#define ifr_flagshigh ifr_ifru.ifru_flags[1]  /* flags (high 16 bits) */
#define ifr_metric ifr_ifru.ifru_ivalue
#define ifr_mtu ifr_ifru.ifru_mtu
#define ifr_slave ifr_ifru.ifru_slave
#define ifr_data ifr_ifru.ifru_data
#define ifr_ifindex ifr_ifru.ifru_ivalue
#define ifr_bandwidth ifr_ifru.ifru_ivalue
#define ifr_qlen ifr_ifru.ifru_ivalue
#define ifr_newname ifr_ifru.ifru_newname
#define ifr_index ifr_ifindex

struct ifconf {
  int ifc_len;
  union {
    char  *ifcu_buf;
    struct ifreq  *ifcu_req;
  } ifc_ifcu;
};

#define ifc_buf ifc_ifcu.ifcu_buf
#define ifc_req ifc_ifcu.ifcu_req

struct ifaddrs {
  struct ifaddrs  *ifa_next; /**< Pointer to the next network interfaces.f */
  char    *ifa_name;         /**< Pointer to the name of the network interfaces  */
  unsigned int   ifa_flags;   /**< Pointer to the status flag.  */
  struct sockaddr *ifa_addr;  /**<  Pointer to the address.  */
  struct sockaddr *ifa_netmask; /**< Pointer to the net masking. */
  struct sockaddr *ifa_dstaddr; /**<  Pointer to the destination address.  */
  void    *ifa_data;            /**< Pointer to the data.   */
};

/*
 * This may have been defined in <net/if.h>.  Note that if <net/if.h> is
 * to be included it must be included before this header file.
 */
#ifndef ifa_broadaddr
/** @brief Indicates a broadcast address interface. */
#define ifa_broadaddr ifa_dstaddr /* brcast address interface */
#endif

struct rtentry {
  struct sockaddr rt_dst;         /**< Indicates the target address.               */
  struct sockaddr rt_gateway;     /**< Indicates the gateway address (RTF_GATEWAY).   */
  struct sockaddr rt_genmask;     /**< Indicates the target network mask (IP).     */
  unsigned int rt_flags;
};
/** Indicates that the route is usable */
#define RTF_UP    0x1
/** Indicates that the destination is a gateway */
#define RTF_GATEWAY 0x2
/** Indicates the host entry (net otherwise) */
#define RTF_HOST  0x4
/** Indicates the host or net is unreachable */
#define RTF_REJECT  0x8
/** Created dynamically (by redirect) */
#define RTF_DYNAMIC 0x10
/**  Modified dynamically (by redirect) */
#define RTF_MODIFIED  0x20
/** Message confirmed. */
#define RTF_DONE  0x40
/*      0x80       unused, was RTF_DELCLONE */
/*      0x100      unused, was RTF_CLONING */
/** Indicates that the external daemon resolves name */
#define RTF_XRESOLVE  0x200
/** DEPRECATED - exists ONLY for backward
             compatibility */
#define RTF_LLINFO  0x400
/** Used by apps to add/del L2 entries */
#define RTF_LLDATA  0x400
/** Manually added */
#define RTF_STATIC  0x800
/** Discard packets */
#define RTF_BLACKHOLE 0x1000
/** Protocol specific routing flag */
#define RTF_PROTO2  0x4000
/** Protocol specific routing flag */
/*      0x10000      unused, was RTF_PRCLONING */
#define RTF_PROTO1  0x8000
/*      0x10000      unused, was RTF_PRCLONING */
/*      0x20000      unused, was RTF_WASCLONED */
/** Protocol specific routing flag */
#define RTF_PROTO3  0x40000
/** MTU was explicitly specified */
#define RTF_FIXEDMTU  0x80000
/** Route is immutable */
#define RTF_PINNED  0x100000
/** Route represents a local address */
#define RTF_LOCAL 0x200000
/** Route represents a broadcast address */
#define RTF_BROADCAST 0x400000
/** Route represents a multicast address */
#define RTF_MULTICAST 0x800000
/* 0x8000000 and up unassigned */
/** Always route dst->src */
#define RTF_STICKY   0x10000000
/** Radix node head is locked */
#define RTF_RNH_LOCKED   0x40000000
/** Indicates the compatibility bit for interacting
             with existing routing apps */
#define RTF_GWFLAG_COMPAT 0x80000000

/* Mask of RTF flags that are allowed to be modified by RTM_CHANGE. */
#define RTF_FMASK \
  (RTF_PROTO1 | RTF_PROTO2 | RTF_PROTO3 | RTF_BLACKHOLE | \
   RTF_REJECT | RTF_STATIC | RTF_STICKY)

/**
 * @defgroup Network_Interfaces_Info  Network Interfaces Info
 * This section contains the interfaces to get information about Network interfaces in lwIP.
 * @ingroup User_interfaces 
 */
/*
 * Func Name:  getifaddrs
 */
/**
 * @ingroup   Network_Interfaces_Info
 * @brief     Creates a linked list of struct ifaddrs, which holds the information
 * about the network interfaces of the local system. The ifa_next field contains a
 * pointer to the next structure on the list, or NULL if this is the last item of the list.
 * The ifa_name points to the null-terminated interface name. The ifa_flags field
 * contains the interface flags. The ifa_addr field points to a structure containing
 * the interface address. The ifa_netmask field points to a structure containing
 * the netmask associated with ifa_addr, if applicable, for the address family.
 * Depending on whether the bit IFF_brcast or IFF_POINTOPOINT is set
 * in ifa_flags (only one can be set at a time), either ifa_broadaddr will contain
 * the broadcast address associated with ifa_addr (if applicable for the address
 * family) or ifa_dstaddr will contain the destination address of the point-to-point
 * interface.
 * For IPv6, stack supports only IFF_UP,IFF_MULTICAST, IFF_DRV_RUNNING, and IFF_LOOPBACK
 * flags.
 * @param[in]    ifap  Indicates a double pointer to the ifaddrs structure.
 * @return
 * On success, getifaddrs() returns zero; on error, -1 is returned, and errno is set appropriately.
 * @par Errors
 *    @li The getifaddrs() function shall fail if:
 *     - <b> [EACCES] </b>: \n Invalid state of system.
 *     - <b> [ENOMEM] </b>: \n In-sufficient memory.
 * @note
 * None
 */
int getifaddrs(struct ifaddrs **ifap);

/*
 * Func Name:  freeifaddrs
 */
/**
 * @ingroup   Network_Interfaces_Info
 * @brief   The function getifaddrs, provides the list of network interfaces in the ifaddrs* structure.
 * The application has to free the memory of the  ifaddrs * structure by using this function.
 * @param[in]    ifa                Indicates a pointer to the  ifaddrs structure.
 * @return
 *  Void
 *  @note
 *  None
 */
void freeifaddrs(struct ifaddrs *ifa);

#endif /* !LWIP_LITEOS_COMPAT */
int get_ipv6_ifaddr(struct netif *netif, struct ifaddrs *ifaddr, int tmp_index);
int get_ipv4_ifaddr(struct netif *netif, struct ifaddrs *ifaddr);
struct ifaddrs_storage *new_ifaddrs_storage(void);
#endif /* __LWIP_IFADDRS_H */
#endif /* LWIP_IPV4 && !LWIP_IPV6 */
#endif /* LWIP_IFADDRS */
