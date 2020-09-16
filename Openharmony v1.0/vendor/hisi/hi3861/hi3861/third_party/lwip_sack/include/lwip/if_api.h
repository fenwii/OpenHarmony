/*
 * Description: This file contains the implementation for RFC 2553/3493 section Section 4: Interface Identification
 */
/*
 * This file contains the implementation for RFC 2553/3493 section Section 4: Interface Identification
 * The following functions are implemented
 * lwip_if_indextoname
 * lwip_if_nametoindex
 * lwip_if_nameindex
 * lwip_if_freenameindex
 * @note: when passing the ifname pointer to the function lwip_if_indextoname:
 * The ifname argument must point to a buffer of at least IF_NAMESIZE bytes into which the interface
 * name corresponding to the specified
 * index is returned.
 * IF_NAMESIZE is same as IFNAMSIZ and is of 16 bytes including null
 *
 */

#ifndef LWIP_HDR_IF_H
#define LWIP_HDR_IF_H

#include "lwip/opt.h"

#if LWIP_SOCKET /* don't build if not configured for use in lwipopts.h */

#include "lwip/netif.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#if !LWIP_LITEOS_COMPAT

/* Keep the size same as general interface length */
#define IF_NAMESIZE IFNAMSIZ

/**
 * Structure to store the if_index and if_name for each interface.
 */
struct if_nameindex {
  unsigned int if_index; /* 1, 2, ... */
  char *if_name; /* null terminated name: "eth0", ... */
};

#endif /* !LWIP_LITEOS_COMPAT */

#ifdef LWIP_COMPAT_SOCKETS
#if LWIP_COMPAT_SOCKETS != 2
/*
 * Func Name:  lwip_if_indextoname
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * This function maps an interface index into its corresponding name.
 * The ifname argument must point to a buffer of at least IF_NAMESIZE/IFNAMSIZ bytes into which the interface
 * name corresponding to the specified index is returned.
 * (IF_NAMESIZE is also defined in <if.h> and its value includes a terminating null byte at the end of the
 * interface name.) This pointer is also the return value of the function.
 * @param[in]   unsigned int ifindex Specifies an interface index for which the name is to be retrieved.
 * @param[out]  char* ifname Specifies the output interface name which is retrieved based on ifindex
 *
 * @return
 * char *  ifname: On success \n
 *  NULL  : On failure. The errno is set to indicate the error. \n
 * @par Errors
 *   @li The if_indextoname() function fails in the following conditions:
 *     - <b> [ENXIO] </b>: \n The ifindex is more than the max range /There is no name as per the index specified
 *     - <b> [EFAULT] </b>: \n The ifname is a null pointer
 * @par POSIX Conformance:
 * Implementation deviates from RFC 3493, POSIX.1-2001.The following are the exceptions to conformance:
 *  Posix expects errno for scenario If there was a system error (such as running out of memory), if_indextoname
 *  returns   NULL and errno would be set to the proper value (e.g., ENOMEM).
 *  Stack do not allocate memory in this function, so ENOMEM is not returned
 * @note
 * The caller of this function should ensure that the ifname point to a buffer of at least IF_NAMESIZE/IFNAMSIZ bytes.
 * If there is no interface corresponding to the specified index, NULL is returned, and errno is set to ENXIO.
 * Stack only supports ifindex to be max 255 and the index should start from 1 to get a valid name.
 * @par Related Topics
 * if_nametoindex()
 * if_freenameindex()
 * if_nameindex()
 */
char *lwip_if_indextoname(unsigned int ifindex, char *ifname);

/*
 * Func Name:  lwip_if_nametoindex
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * This function maps an interface name into its corresponding index.
 * The ifname argument must point to a buffer of at least IF_NAMESIZE/IFNAMSIZ bytes which will contain the
 * interface name.
 * @param[in]    const char *ifname Specifies the interface name for which corresponding interface
 * index is required.
 * @return
 * unsigned int ifindex: On success.The interface index for the interface name mentioned in ifname \n
 *  0  : On failure. The errno is set to indicate the error. \n
 * @par Errors
 * @li The lwip_if_nametoindex() function fails in the following conditions:
 * - <b> [ENODEV] </b>: \n Could not find the index corresponding to the interface name
 * - <b> [EFAULT] </b>: \n The ifname is a null pointer.
 * @par POSIX Conformance:
 * Implementation deviates from RFC 3493, POSIX.1-2001.The following are the exceptions to conformance:
 * POSIX expects errno for scenario If there was a system error (such as running out of memory),
 * if_nametoindex returns 0 and errno would be set to the proper value (e.g., ENOMEM).
 * Stack does not allocate memory in this function, so ENOMEM is not returned.
 * @note
 * The caller of this function should ensure that the ifname point to a buffer of at least
 * IF_NAMESIZE/IFNAMSIZ bytes. If there is no interface index corresponding to the specified name,
 * 0 is returned, and errno is set to ENODEV.
 * 0 is an invalid index.
 * @par Related Topics
 * if_indextoname()
 * if_freenameindex()
 * if_nameindex()
 */
unsigned int lwip_if_nametoindex(const char *ifname);

/*
 * Func Name:  lwip_if_nameindex
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * This function returns an array of if_nameindex structures, one structure per interface.
 * The if_nameindex structure holds the information about a single interface and is defined as a result of
 * including the <if.h> header.
 * The end of the array of structures is indicated by a structure with an if_index of 0 and an if_name of NULL.
 * The function returns a NULL pointer upon an error, and would set errno to the appropriate value.
 * The memory used for this array of structures along with the interface names pointed to by the if_name members
 * is obtained dynamically.
 * @param[in] void The function does not take any input instead returns all the interfaces in format
 * if_nameindex structures.
 *
 * @return
 * struct if_nameindex * : On success. The function returns an array of if_nameindex structures, one structure
 * per interface. \n
 * NULL  : On failure. The errno is set to indicate the error. \n
 * @par Errors
 * @li The if_nameindex() function fails in the following conditions:
 * - <b> [ENOBUFS] </b>: \n Insufficient resources available. For this, the function returns NULL.
 * @par POSIX Conformance:
 * Implementation conforms to POSIX.1-2001, POSIX.1-2008, RFC 3493.
 * @note
 * The end of the array of structures is indicated by a structure with an if_index of 0 and an if_name of NULL.
 * The function returns a NULL pointer upon an error, and would set errno to the appropriate value.
 * @par Related Topics
 * if_indextoname()
 * if_nametoindex()
 * if_freenameindex()
 */
struct if_nameindex *lwip_if_nameindex(void);

/*
 * Func Name:  lwip_if_freenameindex
 */
/**
 * @ingroup Socket_Interfaces
 * @brief
 * This function frees the dynamic memory that was allocated by  if_nameindex().
 * The argument to this function must be a pointer that was returned by if_nameindex().
 * @param[in] struct if_nameindex *ptr  The argument to this function must be a pointer that was returned by
 * lwip_if_nameindex()
 *
 * @return
 * void  : On success.\n
 * void  : On failure. The errno is not set \n
 * @par POSIX Conformance:
 * Implementation conforms to POSIX.1-2001, POSIX.1-2008, RFC 3493.
 * @par Related Topics
 * if_indextoname()
 * if_nametoindex()
 * if_nameindex()
 */
void lwip_if_freenameindex(struct if_nameindex *ptr);

/* @ingroup socket */
#define if_indextoname(ifindex, ifname)  lwip_if_indextoname(ifindex, ifname)
/* @ingroup socket */
#define if_nametoindex(ifname)          lwip_if_nametoindex(ifname)
#define if_nameindex(void)              lwip_if_nameindex(void)
#define if_freenameindex(ptr)           lwip_if_freenameindex(ptr)
#else
/* @ingroup socket */
#define lwip_if_indextoname(ifindex, ifname)  if_indextoname(ifindex, ifname)
/* @ingroup socket */
#define lwip_if_nametoindex(ifname)          if_nametoindex(ifname)
#define lwip_if_nameindex(void)              if_nameindex(void)
#define lwip_if_freenameindex(ptr)           if_freenameindex(ptr)
#endif /* LWIP_COMPAT_SOCKETS == 2 */
#endif /* LWIP_COMPAT_SOCKETS */

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_SOCKET */

#endif /* !LWIP_HDR_IF_H */

