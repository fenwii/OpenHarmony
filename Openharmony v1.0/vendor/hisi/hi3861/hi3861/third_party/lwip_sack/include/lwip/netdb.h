/**
 * @file
 * NETDB API (sockets)
 */

/*
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
 * Author: Simon Goldschmidt
 *
 */

/**
* @defgroup  netdbapi netdb APIs
* @ingroup User_interfaces
* This contains all the netdb user interfaces.
*/
#ifndef LWIP_HDR_NETDB_H
#define LWIP_HDR_NETDB_H

#include "lwip/opt.h"
#if LWIP_LITEOS_COMPAT
#include <netdb.h>
#endif
#if LWIP_DNS && LWIP_SOCKET

#include "lwip/arch.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#if !LWIP_LITEOS_COMPAT
/* some rarely used options */
#ifndef LWIP_DNS_API_DECLARE_H_ERRNO
#define LWIP_DNS_API_DECLARE_H_ERRNO  1
#endif

#ifndef LWIP_DNS_API_DEFINE_ERRORS
#define LWIP_DNS_API_DEFINE_ERRORS    1
#endif

#ifndef LWIP_DNS_API_DEFINE_FLAGS
#define LWIP_DNS_API_DEFINE_FLAGS     1
#endif

#ifndef LWIP_DNS_API_DECLARE_STRUCTS
#define LWIP_DNS_API_DECLARE_STRUCTS  1
#endif

#if LWIP_DNS_API_DEFINE_ERRORS
/** Errors used by the DNS API functions, h_errno can be one of them */
#define EAI_NONAME      200
#define EAI_SERVICE     201
#define EAI_FAIL        202
#define EAI_MEMORY      203
#define EAI_FAMILY      204
#define EAI_BADFLAGS    205
#define EAI_OVERFLOW    206
#define EAI_ADDRFAMILY  207
#define EAI_AGAIN       208

/* h_errno values */
#define HOST_NOT_FOUND  210
#define NO_DATA         211
#define NO_RECOVERY     212
#define TRY_AGAIN       213
#endif /* LWIP_DNS_API_DEFINE_ERRORS */

#if LWIP_DNS_API_DEFINE_FLAGS
/* input flags for struct addrinfo */
#define AI_PASSIVE      0x01
#define AI_CANONNAME    0x02
#define AI_NUMERICHOST  0x04
#define AI_NUMERICSERV  0x08
#define AI_V4MAPPED     0x10
#define AI_ALL          0x20
#define AI_ADDRCONFIG   0x40

/* input flags for getnameinfo api */
#define NI_NUMERICHOST  1
#define NI_NUMERICSERV  2
#define NI_NOFQDN       4
#define NI_NAMEREQD     8
#define NI_DGRAM        16

#endif /* LWIP_DNS_API_DEFINE_FLAGS */

#if LWIP_DNS_API_DECLARE_STRUCTS
/**
@brief This structure provides information about a host.
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
@brief Provides address information that specifies the
       criteria for selecting the socket address structures returned in the
       list pointed to by the res parameter of the lwip_getaddrinfo() function.
*/
struct addrinfo {
  int               ai_flags;      /**< Specifies input flags. */
  int               ai_family;     /**< Specifies the desired address family.
                   Valid values for this field include AF_INET and AF_INET6.   */
  int               ai_socktype;   /**< Specifies the preferred socket type, for example
                   SOCK_STREAM or SOCK_DGRAM.  Specifying 0 in this
                   field indicates that socket addresses of any type can be
                   returned by lwip_getaddrinfo(). */
  int               ai_protocol;   /**< Specifies the protocol for the returned socket
                   addresses.  Specifying 0 in this field indicates that
                   socket addresses with any protocol can be returned by
                   lwip_getaddrinfo(). */
  socklen_t         ai_addrlen;    /**< Specifies the length of socket address. */
  struct sockaddr  *ai_addr;       /**< Specifies the socket address of socket. */
  char             *ai_canonname;  /**< Specifies the canonical name of the service location. */
  struct addrinfo  *ai_next;       /**< Pointer to next in the list. */
};
#endif /* LWIP_DNS_API_DECLARE_STRUCTS */

#if LWIP_DNS_API_DECLARE_H_ERRNO
/* application accessible error code set by the DNS API functions */
extern int h_errno;
#endif /* LWIP_DNS_API_DECLARE_H_ERRNO */

#endif

#define NETDB_ELEM_SIZE           (sizeof(struct addrinfo) + sizeof(struct sockaddr_storage) + DNS_MAX_NAME_LENGTH + 1)
#ifndef NI_MAXHOST
/* Maximum size of a fully-qualified domain name */
#define NI_MAXHOST      1025
#endif
/* Maximum size of a service name */
#define NI_MAXSERV      32

#if LWIP_GETHOSTBYNAME || (defined(LWIP_COMPAT_SOCKETS) && (LWIP_COMPAT_SOCKETS != 2))
/**
 * @ingroup netdbapi
 * @brief This API is used to resolve a hostname (string) into an IP address
         and return a structure of type hostent for the given host name.
 * @param name  Indicates either a hostname that is to be resolved or an IPv4 or IPv6
       address.
 * @return
 * Pointer to the hostent structure containing addresses of address family AF_INET or AF_INET6 for the host with the
 * name 'name' : On success \n
 * Null pointer: On error \n
        h_errno variable holds an error number.  When non-NULL, the return
        value may point at static data, see the notes below.
        The h_errno variable will contain one among the following error codes in case of failure\n
        HOST_NOT_FOUND : Hostname not found in DNS Server.\n
        TRY_AGAIN : Didnt receive information from an authoritative server.\n
        NO_DATA : Hostname is genuine, but there are no A/AAAA records for it in the server.\n
        NO_RECOVERY : Some server failure occured which cant be recovered.\n
        EFAULT : If the parameter "name" is passed as NULL.\n
        EINVAL : Some internal errors.\n

 * @note
 *    - This function is not thread-safe and should not be used in multiple threads.
 *    - If name is an IPv4 or IPv6 address, no lookup is performed and lwip_gethostbyname()
 *      copies the name into the h_name field and its struct in_addr equivalent
 *      into the h_addr_list[0] field of the returned hostent structure.\n
 *    - This API can give more than one resolved IP address.\n
 *    - While parsing the multiple answer recrods in DNS response message, if
 *      it encounters any malformed answer record then it stops parsing and returns
 *      success if it has successfully parsed some record or else it returns failure.\n
 *    - DNS Query for the name, if needed, will be sent out immediately.\n
 *    - If the time gap between the transmission of first DNS Query and the periodic
 *      retransmission of the same query is less than 100ms, then the periodic retransmission
 *      will be postponed by another 1100ms.
 */
struct hostent *lwip_gethostbyname(const char *name);
#endif /* LWIP_GETHOSTBYNAME || (defined(LWIP_COMPAT_SOCKETS) && (LWIP_COMPAT_SOCKETS != 2)) */

#if (defined(LWIP_COMPAT_SOCKETS) && LWIP_COMPAT_SOCKETS != 2) || LWIP_ENABLE_BASIC_SHELL_CMD
/**
 * @ingroup netdbapi
 * @brief This function is the thread-safe variant of the lwip_gethostbyname() function.
 * It is used to resolve a hostname (string) into an IP address and return a structure of type hostent for the given
 * host name. Here name is either a hostname, or an IPv4/IPv6 address in standard dot/colon notation respectively.
 * Instead of using a static buffer, this function takes buf and h_errnop pointers as arguments
 * and uses these for the result.
 * @param name The hostname that is to be resolved.
 * @param ret The pre-allocated structure where the result is stored.
 * @param buf The pre-allocated buffer where additional data is stored.
 * @param buflen The size of the buffer.
 * @param result This is a double pointer to hostent which is set to ret on success
 *               and set to zero on error scenario.
 * @param h_errnop Indicates the pointer to an int where to store errors (instead of modifying
 *                 the global h_errno)
 * @return
 * 0: On success \n
 * -1: On failure.
 *      The h_errnop variable will contain one among the following error codes in case of failure.\n
 *      HOST_NOT_FOUND : Hostname not found in DNS Server.\n
 *      TRY_AGAIN : Didnt receive information from an authoritative server.\n
 *      NO_DATA : Hostname is genuine, but there are no A/AAAA records for it in the server.\n
 *      NO_RECOVERY : Some server failure occured which cant be recovered.\n
 *      EINVAL : Invalid arguments.\n
 *      ERANGE : Result not representable due to storage size limitations.\n
 * @note
 *    - Additional error information is stored in *h_errnop instead of h_errno to be thread-safe.\n
 *    - If name is an IPv4 or IPv6 address, no lookup is performed and lwip_gethostbyname_r()
 *      copies the name into the h_name field and its struct in_addr equivalent
 *      into the h_addr_list[0] field of the returned hostent structure.\n
 *    - This API can give more than one resolved IP address.\n
 *    - While parsing the multiple answer recrods in DNS response message, if
 *      it encounters any malformed answer record then it stops parsing and returns
 *      success if it has successfully parsed some record or else it returns failure.\n
 *    - DNS Query for the name, if needed, will be sent out immediately.\n
 *    - If the time gap between the transmission of first DNS Query and the periodic
 *      retransmission of the same query is less than 100ms, then the periodic retransmission
 *      will be postponed by another 1100ms.
 */
int lwip_gethostbyname_r(const char *name, struct hostent *ret, char *buf,
                         size_t buflen, struct hostent **result, int *h_errnop);
#endif /* (defined(LWIP_COMPAT_SOCKETS) && LWIP_COMPAT_SOCKETS != 2) || LWIP_ENABLE_BASIC_SHELL_CMD */

#if (defined(LWIP_COMPAT_SOCKETS) && LWIP_COMPAT_SOCKETS != 2) || LWIP_ENABLE_LOS_SHELL_CMD
/**
 * @ingroup netdbapi
 * @brief This API is used to free one or more addrinfo
 *      structures returned by the lwip_getaddrinfo() function, along with any additional
 *      storage associated with those structures. If the ai_next field of the
 *      structure ai is not null, the entire list of structures is freed.
 *
 * @param ai  The struct addrinfo to free.
 * @return
 * None
 */
void lwip_freeaddrinfo(struct addrinfo *ai);


/**
 * @ingroup netdbapi
 * @brief  Translates the name of a service location (for example, a host name) and
 * a service name and returns a set of socket addresses and associated
 * information to be used in creating a socket with which to address the
 * specified service.
 * Memory for the result is allocated internally and must be freed by calling
 * lwip_freeaddrinfo(). \n
 *
 * The servname parameter supports only port numbers, and does not support service names.
 * @param nodename  Indicates a descriptive name or address string of the host. NULL denotes a
  local address.
 * @param servname Indicates the port number of the service as string or NULL.
 * @param hints Indicates a structure containing input values that set socktype and protocol.
 * @param res Indicates a pointer to a pointer indicating where to store the result. This is set to NULL on failure.
 * @return
 * 0: On success \n
 * Non-zero error number: On failure\n
 * EAI_FAIL   : If the input parameter res is NULL or the name server returned a permanent failure indication.\n
 * EAI_FAMILY : The requested address family is not supported.\n
 * EAI_NONAME : The node or service is not known; or both node and service are
                NULL; or service was not a numeric port-number string. Currently,
                service supports only AI_NUMERICSERV flag.\n
 * EAI_MEMORY : Out of memory.\n
 * EAI_ADDRFAMILY : The specified network host does not have any network addresses in the requested address family.\n
 * EAI_AGAIN : The name server returned a temporary failure indication. Try again later.

 * @par Note
 * - Either nodename or servname, but not both, may be NULL.
 * - No support for translation of service names.\n
 * - If the specified network host does not have any network addresses in the requested address family,
 *   EAI_FAIL will be returned.
 * - Either nodename or servname, but not both, may be NULL.
 */
int lwip_getaddrinfo(const char *nodename,
                     const char *servname,
                     const struct addrinfo *hints,
                     struct addrinfo **res);
#endif /* (defined(LWIP_COMPAT_SOCKETS) && LWIP_COMPAT_SOCKETS != 2) || LWIP_ENABLE_LOS_SHELL_CMD */

#if LWIP_DNS_REVERSE
/**
 * @ingroup netdbapi
 * @brief   Converts a socket address to a corresponding host and service, in a
 * protocol-independent manner. It is reentrant and allows programs to eliminate
 * IPv4-versus-IPv6 dependencies.
 * Memory for the result is allocated by the caller.
 *
 * @param sa  Indicates a pointer to a generic socket address structure
 *            (of type sockaddr_in or sockaddr_in6) that holds the
 *            input IP address and port number.
 * @param salen Indicates the size of the generic socket address structure "sa".
 * @param host Indicates a pointer to caller-allocated buffer which will holds the null terminated hostname string.
 * @param hostlen Indicates the size of "host" buffer.
 * @param serv Indicates a pointer to caller-allocated buffer which will holds the null terminated service-name string.
 * @param servlen Indicates the size of "serv" buffer.
 * @param flags Used to modify the behaviour of lwip_getnameinfo() and can have the following values:
 * - NI_NAMEREQD : If set, then an error is returned if the hostname cannot be determined.
 * - NI_DGRAM : If set, then the service is datagram (UDP) based rather than stream (TCP) based and causes
 *              getservbyport() to be called with a second  argument of "udp" instead of its default of "tcp".
 *              This is required for the few ports (512-514) that have different services for UDP and TCP.
 * - NI_NOFQDN : If set, return only the hostname part of the fully qualified domain name for local hosts.
 * - NI_NUMERICHOST : If set, then the numeric form of the hostname is returned. (When not set, this will still happen
 *                    in case the node's name cannot be determined.)
 * - NI_NUMERICSERV : If set, then the numeric form of the service address is returned.  (When not set, this will still
 *                    happen in case the service's name cannot be determined.)
 * @return
 * 0: On success \n
 * Non-zero error number: On failure
 * EAI_FAIL   : A nonrecoverable error occurred..
 * EAI_FAMILY : The requested address family is not supported.
 * EAI_NONAME : The name does not resolve for the supplied arguments. NI_NAMEREQD is set and the host's name cannot be
 *              located, or neither hostname nor service name were requested.
 * EAI_OVERFLOW : The buffer pointed to by host or serv was too small.
 * EAI_BADFLAGS : The "flags" argument has an invalid value..

 * @par Note
 * - No support for translation of service names.\n
 * - Since there is no support for Service names, the flags - NI_DGRAM, NI_NUMERICSERV is not supported.
 * - NI_NOFQDN is not currently implemented
 * - Reverse DNS Query for the IP Address, if needed, will be sent out immediately.\n
 * - If the time gap between the transmission of first Reverse DNS Query and the periodic
 *   retransmission of the same query is less than 100ms, then the periodic retransmission
 *   will be postponed by another 1100ms.
 */
int lwip_getnameinfo(const struct sockaddr *sa,
                     socklen_t salen,
                     char *host,
                     size_t hostlen,
                     char *serv,
                     size_t servlen,
                     int flags);
#endif /* LWIP_DNS_REVERSE */

#if defined(LWIP_COMPAT_SOCKETS) && LWIP_COMPAT_SOCKETS != 2
/** @ingroup netdbapi */
#define gethostbyname(name) lwip_gethostbyname(name)
/** @ingroup netdbapi */
#define gethostbyname_r(name, ret, buf, buflen, result, h_errnop) \
       lwip_gethostbyname_r(name, ret, buf, buflen, result, h_errnop)
/** @ingroup netdbapi */
#define freeaddrinfo(addrinfo) lwip_freeaddrinfo(addrinfo)
/** @ingroup netdbapi */
#define getaddrinfo(nodname, servname, hints, res) \
       lwip_getaddrinfo(nodname, servname, hints, res)

/* @ingroup netdbapi */
#define getnameinfo(sock, sock_size, host, host_len, servname, servname_size, flags) \
       lwip_getnameinfo(sock, sock_size, host, host_len, servname, servname_size, flags)
#endif /* defined(LWIP_COMPAT_SOCKETS) && LWIP_COMPAT_SOCKETS != 2 */

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_DNS && LWIP_SOCKET */

#endif /* LWIP_HDR_NETDB_H */
