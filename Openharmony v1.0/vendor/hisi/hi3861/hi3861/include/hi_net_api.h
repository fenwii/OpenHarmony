/**
 * @file hi_net_api.h
 *
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @defgroup hi_net Lwip API
 */
/**
 * @defgroup hi_net_basic Lwip Basic Interface
 * @ingroup hi_net
 */

#ifndef __HI_NET_API_H__
#define __HI_NET_API_H__

#include <stdint.h>
#include <stddef.h>
#include <errno.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef unsigned char  u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef int err_t;

#ifndef LWIP_TIMEVAL_PRIVATE
#define LWIP_TIMEVAL_PRIVATE 0
#endif

/**
 * @ingroup hi_net_basic
 *
 * max length of INET ADDRESS.CNcomment:INET最大的字符串长度。CNend
 */
#define INET_ADDRSTRLEN 16

/**
 * @ingroup hi_net_basic
 *
 * max num of FD.CNcomment:最大的描述符个数。CNend
 */
#define FD_SETSIZE_MAX 1024

#define  EPERM         1  /* Operation not permitted */
#define  ENOENT        2  /* No such file or directory */
#define  ESRCH         3  /* No such process */
#define  EINTR         4  /* Interrupted system call */
#define  EIO           5  /* I/O error */
#define  ENXIO         6  /* No such device or address */
#define  E2BIG         7  /* Arg list too long */
#define  ENOEXEC       8  /* Exec format error */
#define  EBADF         9  /* Bad file number */
#define  ECHILD       10  /* No child processes */
#define  EAGAIN       11  /* Try again */
#define  ENOMEM       12  /* Out of memory */
#define  EACCES       13  /* Permission denied */
#define  EFAULT       14  /* Bad address */
#define  ENOTBLK      15  /* Block device required */
#define  EBUSY        16  /* Device or resource busy */
#define  EEXIST       17  /* File exists */
#define  EXDEV        18  /* Cross-device link */
#define  ENODEV       19  /* No such device */
#define  ENOTDIR      20  /* Not a directory */
#define  EISDIR       21  /* Is a directory */
#define  ENFILE       23  /* File table overflow */
#define  EMFILE       24  /* Too many open files */
#define  ENOTTY       25  /* Not a typewriter */
#define  ETXTBSY      26  /* Text file busy */
#define  EFBIG        27  /* File too large */
#define  ENOSPC       28  /* No space left on device */
#define  ESPIPE       29  /* Illegal seek */
#define  EROFS        30  /* Read-only file system */
#define  EMLINK       31  /* Too many links */
#define  EPIPE        32  /* Broken pipe */
#define  EDOM         33  /* Math argument out of domain of func */
#define  EDEADLK      35  /* Resource deadlock would occur */
#define  ENAMETOOLONG 36  /* File name too long */
#define  ENOLCK       37  /* No record locks available */
#define  ENOSYS       38  /* Function not implemented */
#define  ENOTEMPTY    39  /* Directory not empty */
#define  ELOOP        40  /* Too many symbolic links encountered */
#define  EWOULDBLOCK  EAGAIN  /* Operation would block */
#define  ENOMSG       42  /* No message of desired type */
#define  EIDRM        43  /* Identifier removed */
#define  ECHRNG       44  /* Channel number out of range */
#define  EL2NSYNC     45  /* Level 2 not synchronized */
#define  EL3HLT       46  /* Level 3 halted */
#define  EL3RST       47  /* Level 3 reset */
#define  ELNRNG       48  /* Link number out of range */
#define  EUNATCH      49  /* Protocol driver not attached */
#define  ENOCSI       50  /* No CSI structure available */
#define  EL2HLT       51  /* Level 2 halted */
#define  EBADE        52  /* Invalid exchange */
#define  EBADR        53  /* Invalid request descriptor */
#define  EXFULL       54  /* Exchange full */
#define  ENOANO       55  /* No anode */
#define  EBADRQC      56  /* Invalid request code */
#define  EBADSLT      57  /* Invalid slot */
#define  EDEADLOCK    EDEADLK
#define  EBFONT       59  /* Bad font file format */
#define  ENOSTR       60  /* Device not a stream */
#define  ENODATA      61  /* No data available */
#define  ETIME        62  /* Timer expired */
#define  ENOSR        63  /* Out of streams resources */
#define  ENONET       64  /* Machine is not on the network */
#define  ENOPKG       65  /* Package not installed */
#define  EREMOTE      66  /* Object is remote */
#define  ENOLINK      67  /* Link has been severed */
#define  EADV         68  /* Advertise error */
#define  ESRMNT       69  /* Srmount error */
#define  ECOMM        70  /* Communication error on send */
#define  EPROTO       71  /* Protocol error */
#define  EMULTIHOP    72  /* Multihop attempted */
#define  EDOTDOT      73  /* RFS specific error */
#define  EBADMSG      74  /* Not a data message */
#define  EOVERFLOW    75  /* Value too large for defined data type */
#define  ENOTUNIQ     76  /* Name not unique on network */
#define  EBADFD       77  /* File descriptor in bad state */
#define  EREMCHG      78  /* Remote address changed */
#define  ELIBACC      79  /* Can not access a needed shared library */
#define  ELIBBAD      80  /* Accessing a corrupted shared library */
#define  ELIBSCN      81  /* .lib section in a.out corrupted */
#define  ELIBMAX      82  /* Attempting to link in too many shared libraries */
#define  ELIBEXEC     83  /* Cannot exec a shared library directly */
#define  EILSEQ       84  /* Illegal byte sequence */
#define  ERESTART     85  /* Interrupted system call should be restarted */
#define  ESTRPIPE     86  /* Streams pipe error */
#define  EUSERS       87  /* Too many users */
#define  ENOTSOCK     88  /* Socket operation on non-socket */
#define  EDESTADDRREQ 89  /* Destination address required */
#define  EMSGSIZE     90  /* Message too long */
#define  EPROTOTYPE   91  /* Protocol wrong type for socket */
#define  ENOPROTOOPT  92  /* Protocol not available */
#define  EPROTONOSUPPORT 93  /* Protocol not supported */
#define  ESOCKTNOSUPPORT 94  /* Socket type not supported */
#define  EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define  EPFNOSUPPORT    96  /* Protocol family not supported */
#define  EAFNOSUPPORT    97  /* Address family not supported by protocol */
#define  EADDRINUSE      98  /* Address already in use */
#define  EADDRNOTAVAIL   99  /* Cannot assign requested address */
#define  ENETDOWN       100  /* Network is down */
#define  ENETUNREACH    101  /* Network is unreachable */
#define  ENETRESET      102  /* Network dropped connection because of reset */
#define  ECONNABORTED   103  /* Software caused connection abort */
#define  ECONNRESET     104  /* Connection reset by peer */
#define  ENOBUFS        105  /* No buffer space available */
#define  EISCONN        106  /* Transport endpoint is already connected */
#define  ENOTCONN       107  /* Transport endpoint is not connected */
#define  ESHUTDOWN      108  /* Cannot send after transport endpoint shutdown */
#define  ETOOMANYREFS   109  /* Too many references: cannot splice */
#define  ETIMEDOUT      110  /* Connection timed out */
#define  ECONNREFUSED   111  /* Connection refused */
#define  EHOSTDOWN      112  /* Host is down */
#define  EHOSTUNREACH   113  /* No route to host */
#define  EALREADY       114  /* Operation already in progress */
#define  EINPROGRESS    115  /* Operation now in progress */
#define  ESTALE         116  /* Stale NFS file handle */
#define  EUCLEAN        117  /* Structure needs cleaning */
#define  ENOTNAM        118  /* Not a XENIX named type file */
#define  ENAVAIL        119  /* No XENIX semaphores available */
#define  EISNAM         120  /* Is a named type file */
#define  EREMOTEIO      121  /* Remote I/O error */
#define  EDQUOT         122  /* Quota exceeded */
#define  ENOMEDIUM      123  /* No medium found */
#define  EMEDIUMTYPE    124  /* Wrong medium type */

#define SOCK_STREAM     1
#define SOCK_DGRAM      2
#define SOCK_RAW        3

#define AF_UNSPEC       0
#define AF_INET         2
#define AF_INET6        AF_UNSPEC
#define PF_INET         AF_INET
#define PF_INET6        AF_INET6
#define PF_UNSPEC       AF_UNSPEC

#define IPPROTO_IP      0
#define IPPROTO_TCP     6
#define IPPROTO_UDP     17
#define IPPROTO_UDPLITE 136

#define MSG_PEEK       0x02
#define MSG_WAITALL    0x100
#define MSG_OOB        0x01
#define MSG_DONTWAIT   0x40
#define MSG_MORE       0x8000

#define SOL_SOCKET   1
#define SO_REUSEADDR 2
#define SO_TYPE      3
#define SO_ERROR     4
#define SO_BROADCAST 6
#define SO_SNDBUF    7
#define SO_RCVBUF    8
#define SO_KEEPALIVE 9
#define SO_NO_CHECK  11
#define SO_SNDLOWAT  19
#define SO_RCVLOWAT  18
#define SO_SNDTIMEO  67
#define SO_RCVTIMEO  66
#define SO_CONTIMEO  0x1009


#ifndef O_NONBLOCK
#define O_NONBLOCK  00004000
#endif

#ifndef O_NDELAY
#define O_NDELAY    O_NONBLOCK
#endif

#ifndef F_GETFL
#define F_GETFL 3
#endif
#ifndef F_SETFL
#define F_SETFL 4
#endif

#define IP_MULTICAST_TTL   5
#define IP_MULTICAST_IF    6
#define IP_MULTICAST_LOOP  7
#define IP_ADD_MEMBERSHIP  35
#define IP_DROP_MEMBERSHIP 36

#define IPADDR_NONE    ((u32_t)0xffffffffUL)
#define IPADDR_ANY     ((u32_t)0x00000000UL)
#define INADDR_ANY     IPADDR_ANY

#define ip4_addr1(ipaddr) (((u8_t*)(ipaddr))[0])
#define ip4_addr2(ipaddr) (((u8_t*)(ipaddr))[1])
#define ip4_addr3(ipaddr) (((u8_t*)(ipaddr))[2])
#define ip4_addr4(ipaddr) (((u8_t*)(ipaddr))[3])

#define ip4_addr1_16(ipaddr) ((u16_t)ip4_addr1(ipaddr))
#define ip4_addr2_16(ipaddr) ((u16_t)ip4_addr2(ipaddr))
#define ip4_addr3_16(ipaddr) ((u16_t)ip4_addr3(ipaddr))
#define ip4_addr4_16(ipaddr) ((u16_t)ip4_addr4(ipaddr))

/**
 * @ingroup hi_net_basic
 *
 * host Host byte order converted to network byte order.CNcomment:主机序转为网络序。CNend
 */
#define LWIP_PLATFORM_HTONS(_n)  ((u16_t)((((_n) & 0xff) << 8) | (((_n) >> 8) & 0xff)))

/**
 * @ingroup hi_net_basic
 *
 * network bytehost order converted to Host byte order.CNcomment:网络序转为主机序。CNend
 */
#define LWIP_PLATFORM_HTONL(_n)  ((u32_t)((((_n) & 0xff) << 24) | (((_n) & 0xff00) << 8) | \
                                  (((_n) >> 8)  & 0xff00) | (((_n) >> 24) & 0xff)))

/**
 * @ingroup hi_net_basic
 *
 * set ip addr for four address.CNcomment:根据ip四段地址设置相应的值。CNend
 */
#define IP4_ADDR(ipaddr, a, b, c, d) \
        (ipaddr)->addr = ((u32_t)((d) & 0xff) << 24) | \
                         ((u32_t)((c) & 0xff) << 16) | \
                         ((u32_t)((b) & 0xff) << 8)  | \
                          (u32_t)((a) & 0xff)

/*****************************************************************************
* 8、LWIP协议栈bsd socket htons/ntohs/ntohl转换
*****************************************************************************/
#define htons(x) lwip_htons(x)
#define ntohs(x) lwip_ntohs(x)
#define htonl(x) lwip_htonl(x)
#define ntohl(x) lwip_ntohl(x)

#define lwip_htons(x) LWIP_PLATFORM_HTONS(x)
#define lwip_ntohs(x) LWIP_PLATFORM_HTONS(x)
#define lwip_htonl(x) LWIP_PLATFORM_HTONL(x)
#define lwip_ntohl(x) LWIP_PLATFORM_HTONL(x)

/**
* @ingroup  hi_net_basic
* @brief  Point to decimal.CNcomment:ip地址点分制转为十进制CNend
*
* @par Description:
*           Point to decimal.CNcomment:ip地址点分制转为十进制CNend
*
* @attention  cp cannot be empty. CNcomment:传入字符串不能为空CNend
* @param  the ip addr in string CNcomment:字符串ip地址CNend
* @retval #IPADDR        Execute successfully.
* @retval #IPADDR_NONE   Execute failed.
* @par NA:
*         NA
* @see  NULL

*/
u32_t ipaddr_addr(const char *cp);
#define inet_addr(cp)  ipaddr_addr(cp)

#if !defined(in_addr_t) && !defined(IN_ADDR_T_DEFINED)
#ifndef _IN_ADDR_T_DECLARED
typedef u32_t in_addr_t;
#define _IN_ADDR_T_DECLARED
#endif
#endif

#if !defined(sa_family_t) && !defined(SA_FAMILY_T_DEFINED)
typedef u16_t sa_family_t;
#endif

#if !defined(in_port_t) && !defined(IN_PORT_T_DEFINED)
typedef u16_t in_port_t;
#endif

#if !defined(socklen_t) && !defined(SOCKLEN_T_DEFINED)
typedef u32_t socklen_t;
#endif

/**
 * @ingroup hi_net_basic
 *
 * ip address in decimal.CNcomment:十进制ip地址CNend
 *
 */
struct ip_addr {
    u32_t addr;
};

/**
 * @ingroup hi_net_basic
 *
 * Package structure ip_addr_t to in_addr.CNcomment:封装结构体in_addr_t到in_addrCNend
 *
 */
struct in_addr {
    in_addr_t s_addr;
};

/**
 * @ingroup hi_net_basic
 *
 * Address form of socket in Internet Environment.CNcomment:internet环境下套接字的地址形式CNend
 *
 */
struct sockaddr_in {
    sa_family_t     sin_family;
    in_port_t       sin_port;
    struct in_addr  sin_addr;
#define SIN_ZERO_LEN 8
    char            sin_zero[SIN_ZERO_LEN];
};

/**
 * @ingroup hi_net_basic
 *
 * General socket address.CNcomment:通用的套接字地址CNend
 *
 */
struct sockaddr {
    sa_family_t sa_family;
#define SA_DATA_LEN 14
    char sa_data[SA_DATA_LEN];
};

/**
 * @ingroup hi_net_basic
 *
 * Multicast address and interface.CNcomment:多播地址和接口CNend
 *
 */
typedef struct ip_mreq {
    struct in_addr imr_multiaddr;
    struct in_addr imr_interface;
} ip_mreq;

/**
 * @ingroup hi_net_basic
 *
 * IPv4 address.CNcomment:ipv4的地址CNend
 *
 */
struct ip4_addr {
    u32_t addr;
};
typedef struct ip4_addr ip4_addr_t;
typedef ip4_addr_t ip_addr_t;

/**
* @ingroup  hi_net_basic
* @brief  Network byte order IP address converted to dotted decimal format.
*         CNcomment:网络字节序的IP地址转化为点分十进制格式CNend
*
* @par Description:
*           Address translation.CNcomment:地址转换CNend
*
* @attention  NULL
* @param  cp    [IN]     Type #ip4_addr_t *, Network byte order IP address.CNcomment:点分十进制格式的IP地址CNend
* @param  addr  [IN]     Type #const char *, length of device name.CNcomment:点分十进制ip地址CNend
*
* @retval #1    Excute successfully
* @retval #0    Excute failure
* @par  NULL
*
* @see  NULL

*/
int ip4addr_aton(const char *cp, ip4_addr_t *addr);
#define inet_aton(cp, addr)  ip4addr_aton(cp, (ip4_addr_t*)addr)

/**
* @ingroup  hi_net_basic
* @brief  Dotted decimal format IP address converted to Network byte order.
*         CNcomment:点分十进制的IP地址转化为网络字节序格式CNend
*
* @par Description:
*           Address translation.CNcomment:地址转换CNend
*
* @attention  NULL
* @param  addr [IN]  Type #ip4_addr_t *, addr ip address in network order to convert.CNcomment:网络字节序ip地址CNend
*
* @retval #Not NULL  Excute successfully
* @retval #NULL      Excute failure
* @par  NULL
*
* @see  NULL

*/
char *ip4addr_ntoa(const ip4_addr_t *addr);
#define inet_ntoa(addr)  ip4addr_ntoa((ip4_addr_t*)&(addr))


typedef void (*dns_found_callback)(const char *name, ip_addr_t *ipaddr, void *callback_arg);
err_t dns_gethostbyname(const char *hostname, ip_addr_t *addr,
                        dns_found_callback found, void *callback_arg);

/**
 * @ingroup hi_net_basic
 *
 * Domain name and network address structure.CNcomment:域名和网络地址结构体CNend
 *
 */
struct hostent {
    char  *h_name;      /**< Indicates the official name of the host. */
    char **h_aliases;   /**< Indicates a pointer to an array of pointers to alternative host names,
                           terminated by a null pointer. */
    int    h_addrtype;  /**< Indicates the address type. */
    int    h_length;    /**< Indicates the length, in bytes, of the address. */
    char **h_addr_list; /**< Indicates a pointer to an array of pointers to network addresses (in
                           network byte order) for the host, terminated by a null pointer. */
#define h_addr h_addr_list[0] /* for backward compatibility */
};

/**
* @ingroup  hi_net_basic
* @brief  Get IP address according to domain name.CNcomment:根据域名获取IP地址CNend
*
* @par Description:
*           The IP address is obtained by using the domain name in string format,
*           and the address information is loaded into the host domain name structure
*           CNcomment:利用字符串格式的域名获得IP地址，并且将地址信息装入hostent域名结构体CNend
*
* @attention  NULL
* @param  name            [IN]    Type #const char * the hostname to resolve.CNcomment:解析的域名CNend
*
* @retval #hostent        Execute successfully.
* @retval #NULL           Execute failed.
* @par Dependency:
*         #NULL
* @see  NULL
*/
struct hostent *gethostbyname(const char *name);

/**
 * @ingroup hi_net_basic
 *
 * Network interface structure.CNcomment:网络接口结构体CNend
 *
 */
struct netif {
#define NETIF_DATA_LEN 8
    unsigned char data[NETIF_DATA_LEN];
};

/**
* @ingroup  hi_net_basic
* @brief  Get the corresponding interface pointer according to the interface name.
*         CNcomment:根据接口名字获取相应接口指针CNend
*
* @par Description:
*         Get the corresponding interface pointer according to the interface name
*         CNcomment:根据接口名字获取相应接口指针CNend
*
* @attention  NULL
* @param  name            [IN]    Type #const char * the interface name to find.CNcomment:要找的接口名字CNend
*
* @retval #struct netif * Execute successfully.
* @retval #NULL           Execute failed.
* @par Dependency:
*         #NULL
* @see  NULL
*/
struct netif *netif_find(const char *name);

/**
* @ingroup  hi_net_basic
* @brief  Start DHCP client according to interface.CNcomment:根据接口启动dhcp客户端CNend
*
* @par Description:
*         Start DHCP client according to interface
*         CNcomment:根据接口启动dhcp客户端CNend
*
* @attention  NULL
* @param  netif      [IN]    Type #struct netif * Interface address.CNcomment:接口地址CNend
*
* @retval #ERR_OK    Execute successfully.
* @retval #OTHERS    Execute failed.
* @par Dependency:
*         #NULL
* @see  NULL
*/
err_t netifapi_dhcp_start(struct netif *netif);

/**
* @ingroup  hi_net_basic
* @brief  Start DHCP server according to interface.CNcomment:根据接口启动dhcp服务端CNend
*
* @par Description:
*         Start DHCP server according to interface
*         CNcomment:根据接口启动dhcp服务端CNend
*
* @attention  NULL
* @param  netif      [IN]    Type #struct netif * Interface address.CNcomment:接口地址CNend
* @param  start_ip   [IN]    Type #char * Assigned client start address.CNcomment:分配的客户端起始地址CNend
* @param  ip_num     [IN]    Type #u16_t  Total number of clients assigned.CNcomment:分配的客户端总数目CNend
* @retval #ERR_OK    Execute successfully.
* @retval #OTHERS    Execute failed.
* @par Dependency:
*         #NULL
* @see  NULL

*/
err_t netifapi_dhcps_start(struct netif *netif, char *start_ip, u16_t ip_num);

/**
* @ingroup  hi_net_basic
* @brief  This API is used to set the the vendor class identifier information
*         of the netif, which is using in DHCP Message.
*         CNcomment:这个API用来设置dhcp的hostname消息CNend
*
* @par Description:
*         The hostname string lenght should be less than NETIF_HOSTNAME_MAX_LEN,
*         otherwise the hostname will truncate to (NETIF_HOSTNAME_MAX_LEN-1).
*         CNcomment:hostname的长度要小于NETIF_HOSTNAME_MAX_LEN,否则会被设置为(NETIF_HOSTNAME_MAX_LEN-1)CNend
*
* @attention  NULL
* @param  netif      [IN]    Type #struct netif * Interface address.CNcomment:接口地址CNend
* @param  hostname   [IN]    Type #char * hostname The new hostname to use.CNcomment:传入使用的名字CNend
* @param  namelen    [IN]    Type #u8_t The hostname string length.CNcomment:名称长度CNend
* @retval #ERR_OK    Execute successfully.
* @retval #ERR_ARG:  On passing invalid arguments.
* @par Dependency:
*       #NULL
* @see  NULL
*/
err_t netifapi_set_hostname(struct netif *netif, char *hostname, u8_t namelen);


/**
* @ingroup  hi_net_basic
* @brief  This API is used to set the vendor class identifier information, which is used in DHCP message.
*         CNcomment:设置dhcp消息的vci信息CNend
*
* @par Description:
*    Length of vendor class identifier information string ,should be not more than DHCP_VCI_MAX_LEN(default 32),
*    otherwise it will return with ERR_ARG. vci_len is the real length of vendor class identifier information string.
*    CNcomment:vci消息长度不超过32个字节,否则会返回ERR_ARG,vci_len是厂商分类信息的真实长度CNend
*
* @attention  NULL
* @param  vci    [IN]    Type #char * The new vendor class identifier information to use.CNcomment:厂商设备信息数据CNend
* @param  vci_len [IN]    Type #u8_t   The length of vendor class identifier information string.CNcomment:上述数据的长度CNend
* @retval #ERR_OK On success
* @retval #ERR_ARG On passing invalid arguments
* @retval #ERR_VAL On failure
* @par Dependency:
*       #NULL
* @see  NULL
*/
err_t netifapi_set_vci(char *vci, u8_t vci_len);

/**
* @ingroup  hi_net_basic
* @brief  allocate a socket.CNcomment:分配套接字CNend
*
* @par Description:
*        It creates an endpoint for communication and returns a file descriptor
*        CNcomment:为通信创建一个端点并返回一个文件描述符CNend
*
* @attention  NULL
* @param  domain     [IN]    Type #int Specifies a protocol family.CNcomment:指定协议族CNend
* @param  type       [IN]    Type #int Specifies the socket type.CNcomment:指定协议类型CNend
* @param  protocol   [IN]    Type #int Specifies the protocol to be used with the socket.
*                            CNcomment:指定要与套接字一起使用的协议CNend
* @retval #>0       Execute successfully.
* @retval #-1       Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int socket(int domain, int type, int protocol);

/**
* @ingroup  hi_net_basic
* @brief  bind a socket.CNcomment:绑定套接字CNend
*
* @par Description:
*        It creates an endpoint for communication and returns a file descriptor
*        CNcomment:为通信创建一个端点并返回一个文件描述符CNend
*
* @attention  NULL
* @param s     [IN]    Type #int Specifies the file descriptor of the socket to be bound.CNcomment:要绑定的描述符CNend
* @param name  [IN]    Type #struct sockaddr *  Points to a sockaddr structure containing the address
*                              to be bound to the socket.    CNcomment:指向包含要绑定到套接字的地址的sockaddr结构CNend
* @param namelen [IN] Type #socklen_t Specifies the length of the sockaddr structure pointed to by the address argument.
*                                     CNcomment:指定address参数指向的sockaddr结构的长度CNend
* @retval #0        Execute successfully.
* @retval #-1       Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int bind(int s, const struct sockaddr *name, socklen_t namelen);

/**
* @ingroup  hi_net_basic
* @brief  Get socket optional fields.CNcomment:获取套接字可选字段CNend
*
* @par Description:
*        Get socket optional fields
*        CNcomment:获取套接字可选字段CNend
*
* @attention  NULL
* @param  socket  [IN]       Type #int Specifies a socket file descriptor.CNcomment:指定的文件描述符CNend
* @param  level   [IN]       Type #int Specifies the protocol level at which the option resides.
*                                      CNcomment:指定选项所在的协议级别CNend
* @param  option_name  [IN]  Type #int Specifies a single option to set.CNcomment:指定选项的名字CNend
* @param  option_value [OUT] Type #void * Indicates the pointer to the option value.CNcomment:指示指向选项值的指针CNend
* @param  option_len   [IN]  Type #socklen_t * Specifies the size of option value.CNcomment:指定选项的值CNend
* @retval #0     Execute successfully.
* @retval #-1    Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen);

/**
* @ingroup  hi_net_basic
* @brief  Set socket optional fields.CNcomment:设置套接字可选字段CNend
*
* @par Description:
*        Set socket optional fields
*        CNcomment:设置套接字可选字段CNend
*
* @attention  NULL
* @param  socket    [IN]     Type #int Specifies a socket file descriptor.CNcomment:指定的文件描述符CNend
* @param  level     [IN]     Type #int Specifies the protocol level at which the option resides.
*                                      CNcomment:指定选项所在的协议级别CNend
* @param  option_name  [IN]  Type #int Specifies a single option to set.CNcomment:指定选项的名字CNend
* @param  option_value [OUT] Type #void * Indicates the pointer to the option value.CNcomment:指示指向选项值的指针CNend
* @param  option_len   [IN]  Type #socklen_t Specifies the size of option value.CNcomment:指定选项的值CNend
* @retval #0     Execute successfully.
* @retval #-1    Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);

/**
* @ingroup  hi_net_basic
* @brief  Accepts a new connection on a socket.CNcomment:套接字上接收一个连接CNend
*
* @par Description:
*        Accepts a new connection on a socket
*        CNcomment:套接字上接收一个连接CNend
*
* @attention  NULL
* @param  socket    [IN]   Type #int Specifies a socket that was created with socket(),has been bound to an address
*                               with bind(),and has issued a successful call to listen().
*                               CNcomment:指定用socket()创建的套接字,该套接字已bind()绑定,并已成功调用listen()CNend
* @param  address   [OUT]  Type #struct sockaddr * Indicates either a null pointer, or a pointer to a sockaddr structure
*                                 where the address of the connecting socket shall be returned.
*                                 CNcomment:指示空指针或指向sockaddr结构的指针,其中应返回连接套接字的地址CNend
* @param  address_len  [IN,OUT]  Type #socklen_t * Indicates either a null pointer,if address is a null pointer,
*                                                  or a pointer to a socklen_t object which on input
*                                 specifies the length of the supplied sockaddr structure,and on output specifies
*                                 the length of the stored address.
*                                 CNcomment:如果地址是空指针,则指示空指针,或者指示指向socklen_t对象的指针,
*                                           该对象在输入时指定提供的sockaddr结构的长度,在输出时指定存储地址的长度.CNend
* @retval #>0     Execute successfully.
* @retval #-1     Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int accept(int s, struct sockaddr *addr, socklen_t *addrlen);

/**
* @ingroup  hi_net_basic
* @brief  Connection to peer IP address.CNcomment:连接对端IP地址CNend
*
* @par Description:
*        attempt to make a connection on a connection-mode socket or to set or
*        reset the peer address of a connectionless-mode socket
*        CNcomment:尝试在连接模式套接字上建立连接,或设置或重置无连接模式套接字的对等地址CNend
*
* @attention  NULL
* @param      s     [IN]  Type #int Specifies a socket file descriptor.CNcomment:指定套接字CNend
* @param      name  [IN]  Type #struct sockaddr * Specifies a pointer to the sockaddr structure
*                            which identifies the connection. CNcomment:指定指向sockaddr结构的指针，该结构标识连接CNend
* @param      namelen [IN] Type # socklen_t Specifies the size of name structure.
*                                 CNcomment:指定名字结构体的长度CNend
* @retval #0     Execute successfully.
* @retval #-1    Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int connect(int s, const struct sockaddr *name, socklen_t namelen);

/**
* @ingroup  hi_net_basic
* @brief  Recieve a message from connected socket.CNcomment:从已经连接的套接字接收消息CNend
*
* @par Description:
*        Recieve a message from connected socket.
*        CNcomment:从已经连接的套接字接收消息CNend
*
* @attention  NULL
* @param      socket  [IN]  Type #int    Specifies the socket file descriptor.CNcomment:指定套接字CNend
* @param      buffer  [OUT] Type #void *  Points to a buffer where the message should be stored.
*                                         CNcomment:接收存储的缓存CNend
* @param      length  [IN]  Type #size_t  Specifies the length in bytes of the buffer pointed to by the buffer argument.
*                                         CNcomment:每次接收的长度CNend
* @param      flags   [IN]  Type #int     Specifies the type of message reception.CNcomment:指定套接字的标志位CNend
* @retval #>0     Execute successfully.
* @retval #-1     Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int recv(int s, void *mem, size_t len, int flags);

/**
* @ingroup  hi_net_basic
* @brief  Recieve a message from connected socket.CNcomment:从已经连接的套接字接收消息CNend
*
* @par Description:
*        Recieve a message from connected socket.
*        CNcomment:从已经连接的套接字接收消息CNend
*
* @attention  NULL
* @param      socket    [IN]    Type #int     Specifies the socket file descriptor.CNcomment:指定套接字CNend
* @param      buffer    [OUT]   Type #void *  Points to a buffer where the message should be stored.
*                                             CNcomment:接收存储的缓存CNend
* @param      length    [IN]    Type #size_t  Specifies the length in bytes of the buffer pointed to
*                                             by the buffer argument.CNcomment:每次接收的长度CNend
* @param      flags     [IN]    Type #int     Specifies the type of message reception.CNcomment:指定套接字的标志位CNend
* @param      flags     [IN]    Type #struct  sockaddr *  A null pointer, or points to a sockaddr structure in which
*                                                        the sending address is to be stored.
*                                                        CNcomment:空指针，或指向要存储发送地址的sockaddr结构CNend
* @param      flags     [IN]    Type #socklen_t *   Either a null pointer, if address is a null pointer, or a pointer
*                        to a socklen_t objectwhich on input specifies the length of the supplied sockaddr structure,
*                        and on output specifies the length of the stored address.
*                        CNcomment:如果地址是空指针，则为空指针，或者指向socklen_t对象的指针,
*                        该对象在输入时指定提供的sockaddr结构的长度，在输出时指定存储地址的长度CNend
* @retval #>0     Execute successfully.
* @retval #-1     Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int recvfrom(int s, void *mem, size_t len, int flags,
             struct sockaddr *from, socklen_t *fromlen);

/**
* @ingroup  hi_net_basic
* @brief Initiates transmission of a message from the specified socket to its peer.CNcomment:传输指定长度消息到对端CNend
*
* @par Description:
*        Initiates transmission of a message from the specified socket to its peer
*        CNcomment:启动从指定套接字到其对等端的消息传输。CNend
*
* @attention  NULL
* @param      socket  [IN]  Type #int     Specifies the socket file descriptor.CNcomment:指定套接字CNend
* @param      buffer  [IN]  Type #void *  Specifies a buffer containing the message to send.
*                                         CNcomment:指定要发送的缓存CNend
* @param      length  [IN]  Type #size_t  Specifies the length of the message to send.CNcomment:指定消息长度CNend
* @param      flags   [IN]  Type #int     Specifies the type of message reception.CNcomment:指定套接字的标志位CNend
* @retval #>0     Execute successfully.
* @retval #-1     Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int send(int s, const void *dataptr, size_t size, int flags);

/**
* @ingroup  hi_net_basic
* @brief  send messages from a connection-oriented and connectionless sockets.
*         CNcomment:从面向连接和无连接的套接字发送消息CNend
*
* @par Description:
*      If the socket is in the connectionless mode, the message is sent to the address specified by the 'to' parameter.
*
*      CNcomment:如果套接字处于无连接模式，则将消息发送到“to”参数指定的地址
*                如果套接字处于连接模式，则忽略“to”参数中的目标地址CNend
* @attention  NULL
* @param      socket    [IN]   Type #int    Specifies the socket file descriptor.CNcomment:指定套接字CNend
* @param      buffer    [IN]   Type #void * Specifies a buffer containing the message to send.
*                                           CNcomment:指定要发送的缓存CNend
* @param      length    [IN]   Type #size_t Specifies the length of the message to send.CNcomment:指定消息长度CNend
* @param      flags     [IN]   Type #int    Specifies the type of message reception.CNcomment:指定套接字的标志位CNend
* @param      flags     [IN]   Type #struct sockaddr *  Specifies a pointer to the sockaddr structure
*                                                       that contains the destination address.
*                                                       CNcomment:指定指向包含目标地址的sockaddr结构的指针CNend
* @param      flags     [IN]   Type #socklen_t *        Specifies the size of the 'to' structure.
*                                                       CNcomment:指定“to”结构的大小CNend
* @retval #>0     Execute successfully.
* @retval #-1     Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int sendto(int s, const void *dataptr, size_t size, int flags,
           const struct sockaddr *to, socklen_t tolen);

/**
* @ingroup  hi_net_basic
* @brief  Allows a program to monitor multiple file descriptors.CNcomment:允许程序监视多个文件描述符CNend
*
* @par Description:
*        select() can monitor only file descriptors numbers that are less than FD_SETSIZE.
*        select() uses a timeout that is a struct timeval (with seconds and microseconds).
*        CNcomment:select()只能监视小于FD_SETSIZE的文件描述符编号.
*                  select()使用的超时值是struct timeval(秒和微秒)CNend
* @attention  NULL
* @param      nfds      [IN]  Type #int Specifies a range of file descriptors.CNcomment:允许程序监视多个文件描述符CNend
* @param      readfds   [IN]  Type #fd_set *  Specifies a pointer to struct fd_set, and specifies the descriptor to
*                                             check for being ready to read.
*                                             CNcomment:指定struct fd_set的指针，并要检查是否准备好读取的描述符CNend
* @param      writefds  [IN]  Type #fd_set *  Specifies a pointer to struct fd_set, and specifies the descriptor
*                                             to check for being ready to write.CNcomment:
*                                             指定指向struct fd_set的指针，并指定要检查是否准备好写入的描述符CNend
* @param     exceptfds  [IN]  Type #fd_set *  Specifies a pointer to struct fd_set, and specifies the descriptor
*                                             to check for pending error conditions.CNcomment:
*                                             指定指向struct fd_set的指针，并指定要检查挂起错误条件的描述符CNend
* @param     timeout    [IN]  Type #struct timeval *  Specifies a pointer to struct timeval, for timeout application.
*                                                      CNcomment:为超时应用程序指定指向struct timeval的指针CNend
* @retval #>0     Execute successfully.
* @retval #-1     Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL

*/
#if LWIP_TIMEVAL_PRIVATE
int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
           struct timeval *timeout);
#endif
/**
* @ingroup  hi_net_basic
* @brief Initiates transmission of a message from the specified socket to its peer.CNcomment:传输指定长度消息到对端CNend
*
* @par Description:
*      Initiates transmission of a message from the specified socket to its peer
*      CNcomment:启动从指定套接字到其对等端的消息传输。CNend
*
* @attention  NULL
* @param      s      [IN]   Type #int  Indicates the socket file descriptor.CNcomment:指定文件描述符CNend
* @param      cmd    [IN]   Type #int  Indicates a command to select an operation[F_GETFL, F_SETFL].
*                                      CNcomment:指示选择操作的命令[F_GETFL, F_SETFL]CNend
* @param      val    [IN]   Type #int  Indicates an additional flag, to set non-blocking.
*                                      CNcomment:指示一个附加标志，以设置非阻塞CNend
* @retval #0               Execute successfully.
* @retval #-1 & Others     Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int fcntl(int s, int cmd, int val);

/**
* @ingroup  hi_net_basic
* @brief  Close the socket.CNcomment:关闭套接字CNend
*
* @par Description:
*      If O_NONBLOCK is not set and if there is data on the module's write queue,
*      close() waits for an unspecified time for any output to drain before dismantling the STREAM.
*      If the O_NONBLOCK flag is set,close() does not wait for output to drain, and dismantles the STREAM immediately.
*      CNcomment:如果未设置O_NONBLOCK，并且模块的写入队列中有数据,close()等待未指定的时间,等待任何输出排出,然后再拆卸流.
*                如果设置了O_NONBLOCK标志,close()不会等待输出耗尽,并立即取消流CNend
*
* @attention  NULL
* @param      s    [IN]     Type #int  Indicates the socket file descriptor.CNcomment:指定文件描述符CNend
* @retval #0               Execute successfully.
* @retval #-1 & Others     Execute failed.
* @par Dependency:
*       #NULL
* @see  NULL
*/
int closesocket(int s);
#define close(s)  closesocket(s)

#ifdef __cplusplus
}
#endif

#endif
