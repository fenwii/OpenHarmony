/**
 * @file
 *
 * lwIP Options Configuration
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
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

/**
*   @file opt.h
*   @ingroup lwIP_Compiletime_Configuration
*/
/*
 * NOTE: || defined __DOXYGEN__ is a workaround for doxygen bug -
 * without this, doxygen does not see the actual #define
 */
/** @defgroup  lwIP_Compiletime_Configuration lwIP Compile Time Configuration
*   @ingroup Configuration_Interfaces
*/
/* Below comment section is RFC table for IDG supports, please add only one time for each RFC */

#if !defined LWIP_HDR_OPT_H
#define LWIP_HDR_OPT_H

#ifndef LWIP_IPV6_PREFIX_LEN
#define LWIP_IPV6_PREFIX_LEN 64
#endif

/*
 * Include user defined options first. Anything not defined in these files
 * will be set to standard values. Override anything you don't like!
 */
#ifdef LWIP_CONFIG_FILE
#include LWIP_CONFIG_FILE
#else
#include "lwip/lwipopts.h"
#endif // LWIP_CONFIG_FILE

#include "lwip/debug.h"
#if LWIP_LITEOS_COMPAT
#include "sys/select.h"
#include "sys/socket.h"
#include "sys/ioctl.h"
#include "arch/atomic.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/route.h>
#include <ifaddrs.h>
#include <errno.h>
#include <netinet/tcp.h>

#include <sys/socket.h>
#include <netpacket/packet.h>

#include <netinet/in.h>
#include <netinet/icmp6.h>
/* Added for missing declaration of IN6ADDR_ANY_INIT */
#if !LWIP_LINUX_COMPAT
#else
#include <linux/ipv6.h>
#endif

#endif

#include "securec.h"

/*
 * @defgroup lwip_opts Options (lwipopts.h)
 * @ingroup lwip
 *
 * @defgroup lwip_opts_debug Debugging
 * @ingroup lwip_opts
 *
 * @defgroup lwip_opts_infrastructure Infrastructure
 * @ingroup lwip_opts
 *
 * @defgroup lwip_opts_callback Callback-style APIs
 * @ingroup lwip_opts
 *
 * @defgroup lwip_opts_threadsafe_apis Thread-safe APIs
 * @ingroup lwip_opts
 */

/*
  ------------------------------------
  -------------- NO SYS --------------
  ------------------------------------
*/

/**
 * NO_SYS==1: Use lwIP without OS-awareness (no thread, semaphores, mutexes or
 * mboxes). This means that threaded APIs such as socket APIs or netconn APIs cannot be used.
 *  Only the callback-style raw APIs are
 * available. Ensure that you do not access
 * lwIP functions/structures from more than one context at a time.
 */
#if !defined NO_SYS || defined __DOXYGEN__
#define NO_SYS                          0
#endif
/**
 * @}
 */

/*
 * @defgroup lwip_opts_timers Timers
 * @ingroup lwip_opts_infrastructure
 * @{
 */
/**
 * LWIP_TIMERS==0: Drop support for sys_timeout and lwip-internal cyclic timers
 * (the array of lwip-internal cyclic timers is still provided).
 * Refer to NO_SYS_NO_TIMERS for compatibility to old versions.
 */
#if !defined LWIP_TIMERS || defined __DOXYGEN__
#ifdef NO_SYS_NO_TIMERS
#define LWIP_TIMERS                     (!NO_SYS || (NO_SYS && !NO_SYS_NO_TIMERS))
#else
#define LWIP_TIMERS                     1
#endif
#endif

/**
 * LWIP_TIMERS_CUSTOM==1: Provide your own timer implementation.
 * Function prototypes in timeouts.h and the array of lwip-internal cyclic timers
 * are still included, but the implementation is not included. The following functions
 * are required: sys_timeouts_init(), sys_timeout(), sys_untimeout(),
 *                   sys_timeouts_mbox_fetch()
 */
#if !defined LWIP_TIMERS_CUSTOM || defined __DOXYGEN__
#define LWIP_TIMERS_CUSTOM              0
#endif
#ifndef TCPIP_PRTY_MBOX_SIZE
#define TCPIP_PRTY_MBOX_SIZE 16
#endif

#define lwIP_TRUE 1
#define lwIP_FALSE 0
extern int g_is_lwip_initialized;
/**
 * @}
 */

/*
   ------------------------------------
   ----------- Core locking -----------
   ------------------------------------
*/
/*
 * @defgroup lwip_opts_lock Core locking and MPU
 * @ingroup lwip_opts_infrastructure
 * @{
 */
/**
 * LWIP_MPU_COMPATIBLE: Enables a special memory management mechanism
 * which makes lwip able to work on MPU (Memory Protection Unit) system
 * by not passing stack-pointers to other threads
 * (this decreases performance as memory is allocated from pools instead
 * of keeping it on the stack)
 */
#if !defined LWIP_MPU_COMPATIBLE || defined __DOXYGEN__
#define LWIP_MPU_COMPATIBLE             0
#endif

/**
 * LWIP_TCPIP_CORE_LOCKING
 * Creates a global mutex that is held during TCPIP thread operations.
 * Can be locked by client code to perform lwIP operations without changing
 * into TCPIP thread using callbacks. See LOCK_TCPIP_CORE() and
 * UNLOCK_TCPIP_CORE().
 * Your system should provide mutexes supporting priority inversion to use this.
 */
#if !defined LWIP_TCPIP_CORE_LOCKING || defined __DOXYGEN__
#define LWIP_TCPIP_CORE_LOCKING         1
#endif

/**
 * LWIP_TCPIP_CORE_LOCKING_INPUT: when LWIP_TCPIP_CORE_LOCKING is enabled,
 * this macro lets tcpip_input() grab the mutex for input packets as well,
 * instead of allocating a message and passing it to tcpip_thread.
 *
 * @note This macro does not work when tcpip_input() is called from the
 * interrupt context.
 */
#if !defined LWIP_TCPIP_CORE_LOCKING_INPUT || defined __DOXYGEN__
#define LWIP_TCPIP_CORE_LOCKING_INPUT   0
#endif

/**
 * @ingroup Securelib_Interface
 * SYS_LIGHTWEIGHT_PROT==1:  Enables inter-task protection (and task-vs-interrupt
 * protection) for certain critical regions during buffer allocation and deallocation,
 * and memory allocation and deallocation.
 * @note This macro is required when using lwIP from more than one context. If
 * this macro is disabled, you must be sure what you are doing.
 */
#if !defined SYS_LIGHTWEIGHT_PROT || defined __DOXYGEN__
#define SYS_LIGHTWEIGHT_PROT            1
#endif
/**
 * @}
 */

/**
 * Macro/function to check whether lwIP's threading/locking
 * requirements are satisfied during current function call.
 * This macro usually calls a function that is implemented in the OS-dependent
 * sys layer and performs the following checks:
 * - Not in ISR (this should be checked for NO_SYS==1, too!)
 * - If @ref LWIP_TCPIP_CORE_LOCKING = 1: TCPIP core lock is held
 * - If @ref LWIP_TCPIP_CORE_LOCKING = 0: function is called from TCPIP thread
 * @see @ref multithreading
 */
#if !defined LWIP_ASSERT_CORE_LOCKED || defined __DOXYGEN__
#define LWIP_ASSERT_CORE_LOCKED()
#endif

/**
 * Called as first thing in the lwIP TCPIP thread. Can be used in conjunction
 * with @ref LWIP_ASSERT_CORE_LOCKED to check core locking.
 * @see @ref multithreading
 */
#if !defined LWIP_MARK_TCPIP_THREAD || defined __DOXYGEN__
#define LWIP_MARK_TCPIP_THREAD()
#endif

/*
   ------------------------------------
   ---------- Memory options ----------
   ------------------------------------
*/
/*
 * @defgroup lwip_opts_mem Heap and memory pools
 * @ingroup lwip_opts_infrastructure
 * @{
 */
/**
 * MEM_LIBC_MALLOC==1: Use malloc/free/realloc provided by your C library
 * instead of the lwIP internal allocator. This can save code size if you
 * already use it.
 */
#if !defined MEM_LIBC_MALLOC || defined __DOXYGEN__
#define MEM_LIBC_MALLOC                 0
#endif

#ifndef MEM_LIBC_MALLOC_TOTAL_SIZE_LIMIT
#define MEM_LIBC_MALLOC_TOTAL_SIZE_LIMIT 0
#endif

/**
 * MEMP_MEM_MALLOC==1: Use mem_malloc/mem_free instead of the lwIP pool allocator.
 * Especially useful with MEM_LIBC_MALLOC, but be cautious regarding execution
 * speed (heap alloc can be much slower than pool alloc) and usage from interrupts
 * especially if your netif driver allocates PBUF_POOL pbufs for received frames
 * from interrupt.
 * @note Currently, this macro uses the heap for all pools, including private pools, and
 * not only for internal pools defined in memp_std.h.
 */
#if !defined MEMP_MEM_MALLOC || defined __DOXYGEN__
#define MEMP_MEM_MALLOC                 0
#endif

/**
 * MEMP_MEM_INIT==1: Force use of memset to initialize pool memory.
 * Useful if pool are moved in uninitialized section of memory. This will ensure
 * default values in pcbs struct are well initialized in all conditions.
 */
#if !defined MEMP_MEM_INIT || defined __DOXYGEN__
#define MEMP_MEM_INIT                   0
#endif

#ifndef TCP_PBUF_MALLOC
#define TCP_PBUF_MALLOC                 1
#endif

/**
 * This macro must be set to the alignment of the CPU \n
 *    4 byte alignment -> \#define MEM_ALIGNMENT 4 \n
 *    2 byte alignment -> \#define MEM_ALIGNMENT 2
 */
#ifdef LOSCFG_ARCH_CORTEX_A53_AARCH64
#define MEM_ALIGNMENT           8U // for 64bit support
#else
#define MEM_ALIGNMENT           4U
#endif

/**
* This macro sets the minimum size required for pbuf with type PBUF_RAM
* When setting size using the pbuf_ram_size_set, the input size should be greater than the
* minimum size of PBUF_RAM_SIZE_MIN.
*/
#if !defined PBUF_RAM_SIZE_MIN || defined __DOXYGEN__
#define PBUF_RAM_SIZE_MIN               1024
#endif

#if !defined PBUF_RAM_SIZE_MAX || defined __DOXYGEN__
#define PBUF_RAM_SIZE_MAX               0x7FFFFFFF
#endif

/**
 * This macro sets the maximum length to be passed to pbuf alloc for PBUF_RAM type.
 */
#if !defined MAX_PBUF_RAM_SIZE_TO_ALLOC || defined __DOXYGEN__
#define MAX_PBUF_RAM_SIZE_TO_ALLOC      65535U
#endif

/**
 * This macro sets the align size of the DMA memory. If set to 1, then DMA is not used.
 */
#ifndef MEM_MALLOC_DMA_ALIGN
#define MEM_MALLOC_DMA_ALIGN            64
#endif

/**
 *  MEM_SIZE: This macro defines the size of the heap memory. If the application will send
 *  a lot of data that needs to be copied, this should be set high.
 */
#if !defined MEM_SIZE || defined __DOXYGEN__
#define MEM_SIZE                        1600
#endif

/**
 * This macro reserves a configurable
 * amount of bytes before and after each memp element in every pool and fills
 * it with a prominent default value.
 *    MEMP_OVERFLOW_CHECK == 0 No checking \n
 *    MEMP_OVERFLOW_CHECK == 1 Checks each element when it is freed \n
 *    MEMP_OVERFLOW_CHECK >= 2 Checks each element in every pool every time
 *      memp_malloc() or memp_free() is called. This is useful, but slow.
 */
#if !defined MEMP_OVERFLOW_CHECK || defined __DOXYGEN__
#define MEMP_OVERFLOW_CHECK             0
#endif

/**
 * MEMP_SANITY_CHECK==1: Runs a sanity check after each memp_free() to make
 * sure that there are no cycles in the linked lists.
 */
#if !defined MEMP_SANITY_CHECK || defined __DOXYGEN__
#define MEMP_SANITY_CHECK               0
#endif

/**
 * MEM_OVERFLOW_CHECK: mem overflow protection reserves a configurable
 * amount of bytes before and after each heap allocation chunk and fills
 * it with a prominent default value.
 *    MEM_OVERFLOW_CHECK == 0 no checking
 *    MEM_OVERFLOW_CHECK == 1 checks each element when it is freed
 *    MEM_OVERFLOW_CHECK >= 2 checks all heap elements every time
 *      mem_malloc() or mem_free() is called (useful but slow!)
 */
#if !defined MEM_OVERFLOW_CHECK || defined __DOXYGEN__
#define MEM_OVERFLOW_CHECK              0
#endif

/**
 * MEM_SANITY_CHECK==1: run a sanity check after each mem_free() to make
 * sure that the linked list of heap elements is not corrupted.
 */
#if !defined MEM_SANITY_CHECK || defined __DOXYGEN__
#define MEM_SANITY_CHECK                0
#endif

/**
 * MEM_USE_POOLS==1: Uses an alternative to malloc() by allocating from a set
 * of memory pools of various sizes. When mem_malloc is called, an element of
 * the smallest pool that can provide the length needed is returned.
 * To use this, MEMP_USE_CUSTOM_POOLS also has to be enabled.
 */
#if !defined MEM_USE_POOLS || defined __DOXYGEN__
#define MEM_USE_POOLS                   0
#endif

/**
 * MEM_USE_POOLS_TRY_BIGGER_POOL==1: If one malloc-pool is empty, try the next
 * bigger pool. \n
 * WARNING: This might waste memory, but it can make a system more
 * reliable. */
#if !defined MEM_USE_POOLS_TRY_BIGGER_POOL || defined __DOXYGEN__
#define MEM_USE_POOLS_TRY_BIGGER_POOL   0
#endif

/**
 * MEMP_USE_CUSTOM_POOLS==1: Indicates whether to include a user file lwippools.h
 * that defines additional pools beyond the standard files required
 * by lwIP. If you set this to 1, you must have lwippools.h in your
 * include path.
 */
#if !defined MEMP_USE_CUSTOM_POOLS || defined __DOXYGEN__
#define MEMP_USE_CUSTOM_POOLS           0
#endif

/**
 * Set this macro to 1 to free PBUF_RAM pbufs (or call mem_free()) from
 * interrupt context, or another context that does not allow waiting for a
 * semaphore.
 * If set to 1, mem_malloc will be protected by a semaphore and SYS_ARCH_PROTECT,
 * while mem_free will only use SYS_ARCH_PROTECT. mem_malloc SYS_ARCH_UNPROTECTs
 * with each loop so that mem_free can run.
 *
 * @par Note
 * As mentioned in the description, this leads to disabling or
 * enabling interrupts often, which can reduce the speed. Also, on low memory, mem_malloc
 * can require a longer execution time. \n
 *
 * If you do not want that behavior, at least for NO_SYS=0, you can still use the following
 * functions to enqueue a deallocation call which then runs in the tcpip_thread
 * context:
 * - pbuf_free_callback(p);
 * - mem_free_callback(m);
 */
#if !defined LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT || defined __DOXYGEN__
#define LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT 0
#endif

/**
 * MEM_PBUF_RAM_SIZE_LIMIT : This configuration if enabled, limits the memory size usage by MEM_SIZE
 * value.The configuration can be enabled under MEM_LIBC_MALLOC .
 */
#if MEM_LIBC_MALLOC
#ifndef MEM_PBUF_RAM_SIZE_LIMIT
#define MEM_PBUF_RAM_SIZE_LIMIT   1
#endif
#else
#ifndef MEM_PBUF_RAM_SIZE_LIMIT
#define MEM_PBUF_RAM_SIZE_LIMIT   0
#endif
#endif

#ifndef LWIP_NAT64
#define LWIP_NAT64    0
#endif

/**
 * LWIP_MBR_BROADCAST_SYNC : This configuration if enabled, starts the broadcast sync function in the sdv.
 * the sync function will also use one timer.
 */
#ifndef LWIP_MBR_BROADCAST_SYNC
#define LWIP_MBR_BROADCAST_SYNC    0
#endif

/**
 * @}
 */

/*
   ------------------------------------------------
   ---------- Internal Memory Pool Sizes ----------
   ------------------------------------------------
*/
/*
 * @defgroup lwip_opts_memp Internal memory pools
 * @ingroup lwip_opts_infrastructure
 * @{
 */
/**
 * Indicates the number of memp struct pbufs (used for PBUF_ROM and PBUF_REF).
 * If the application sends a lot of data out of ROM (or other static memory),
 * this macro must be set to a high value.
 */
#if !defined MEMP_NUM_PBUF || defined __DOXYGEN__
#define MEMP_NUM_PBUF                   16
#endif

/**
 * Indicates the number of raw connection PCBs.
 * This macro requires the LWIP_RAW option.
 */
#if !defined MEMP_NUM_RAW_PCB || defined __DOXYGEN__
#define MEMP_NUM_RAW_PCB                4
#endif

/**
 * Indicates the number of UDP protocol control blocks. One
 * per active UDP connection.
 * This macro requires the LWIP_UDP option.
 */
#if !defined MEMP_NUM_UDP_PCB || defined __DOXYGEN__
#define MEMP_NUM_UDP_PCB                4
#endif

/**
 * Defines the number of simultaneously active TCP connections.
 * This macro requires the LWIP_TCP option.
 */
#if !defined MEMP_NUM_TCP_PCB || defined __DOXYGEN__
#define MEMP_NUM_TCP_PCB                5
#endif

/**
 * Defines the number of listening TCP connections.
 * This macro requires the LWIP_TCP option.
 */
#if !defined MEMP_NUM_TCP_PCB_LISTEN || defined __DOXYGEN__
#define MEMP_NUM_TCP_PCB_LISTEN         8
#endif

/**
 * Defines the number of simultaneously queued TCP segments.
 * This macro requires the LWIP_TCP option.
 */
#if !defined MEMP_NUM_TCP_SEG || defined __DOXYGEN__
#define MEMP_NUM_TCP_SEG                16
#endif

/**
 * Defines the number of IP packets simultaneously queued for
 * reassembly.
 */
#if !defined MEMP_NUM_REASSDATA || defined __DOXYGEN__
#define MEMP_NUM_REASSDATA              5
#endif

/**
 * Defines the number of IP fragments simultaneously sent.
 * This is only used with LWIP_NETIF_TX_SINGLE_PBUF==0 and only has to be greater than 1
 * with DMA-enabled MACs where the packet is not yet sent when netif->output
 * returns.
 */
#if !defined MEMP_NUM_FRAG_PBUF || defined __DOXYGEN__
#define MEMP_NUM_FRAG_PBUF              15
#endif

/**
 * Defines the number of simultaneously queued outgoing
 * packets (pbufs) that are waiting for an ARP request (to resolve
 * their destination address) to finish.
 *  This macro requires the ARP_QUEUEING option.
 */
#if !defined MEMP_NUM_ARP_QUEUE || defined __DOXYGEN__
#define MEMP_NUM_ARP_QUEUE              30
#endif

/**
 * Defines the number of multicast groups whose network interfaces
 * can be members at the same time (one per netif - allsystems group -, plus one
 * per netif membership).
 * This macro requires the LWIP_IGMP option.
 */
#if !defined MEMP_NUM_IGMP_GROUP || defined __DOXYGEN__
#define MEMP_NUM_IGMP_GROUP             8
#endif

/**
 * Defines the number of default number of sockets
 */
#ifndef DEFAULT_LWIP_NUM_SOCKETS
#define DEFAULT_LWIP_NUM_SOCKETS        8
#endif

/*
 * Provides flexibility to use configured values to spread across code
 */
/**
* LWIP_ALLOW_SOCKET_CONFIG ==0 allows stack to use default value of the number of sockets.
* That is LWIP_CONFIG_NUM_SOCKETS will be DEFAULT_LWIP_NUM_SOCKETS.
* LWIP_ALLOW_SOCKET_CONFIG ==1 allows application to use the configured value.
* Application can configure the Number of sockets using the API lwip_set_socket_num and retrieve the
* value through API lwip_get_socket_num.
*/
#ifndef LWIP_ALLOW_SOCKET_CONFIG
#define LWIP_ALLOW_SOCKET_CONFIG 0
#endif

#if LWIP_ALLOW_SOCKET_CONFIG == 0
#ifndef LWIP_CONFIG_NUM_SOCKETS
#define LWIP_CONFIG_NUM_SOCKETS         DEFAULT_LWIP_NUM_SOCKETS
#endif

#else /* LWIP_ALLOW_SOCKET_CONFIG */
#ifndef LWIP_CONFIG_NUM_SOCKETS
extern unsigned int g_lwip_num_sockets;
#define LWIP_CONFIG_NUM_SOCKETS         g_lwip_num_sockets
#endif
#endif /* LWIP_ALLOW_SOCKET_CONFIG */

#ifndef CONFIG_NFILE_DESCRIPTORS
#define CONFIG_NFILE_DESCRIPTORS 0
#endif

/**
* Defines the maximum number of sockets supported.
*/
#ifndef LWIP_NUM_SOCKETS_MAX
#define LWIP_NUM_SOCKETS_MAX (FD_SETSIZE - CONFIG_NFILE_DESCRIPTORS)
#endif

/**
 * Defines the number of Maximum number of configurable sockets
 */
#ifndef LWIP_NUM_SOCKETS_MAX
#define LWIP_NUM_SOCKETS_MAX 128
#endif

/**
 * Defines the number of simultaneously active timeouts.
 * The default number of timeouts is calculated in this macro, for all enabled modules.
 * The formula expects settings to be either '0' or '1'.
 */
#if !defined MEMP_NUM_SYS_TIMEOUT || defined __DOXYGEN__
#define MEMP_NUM_SYS_TIMEOUT (LWIP_TCP + IP_REASSEMBLY + LWIP_ARP + (2*LWIP_DHCP) + LWIP_AUTOIP + LWIP_IGMP + LWIP_DNS \
    + LWIP_LIBCOAP + (LWIP_IPV6 ? (1 + LWIP_IPV6_REASS + LWIP_IPV6_MLD + LWIP_IPV6_DHCP6 + LWIP_RPL_TIMER_COUNT \
    + LWIP_RIPPLE_TIMER_COUNT + LWIP_6LOWPAN + LWIP_NAT64 + LWIP_MBR_BROADCAST_SYNC) : 0))
#endif

/**
 * Defines the number of struct netbufs.
 * This macro is only needed if you use  sequential APIs, like api_lib.c.
 */
#if !defined MEMP_NUM_NETBUF || defined __DOXYGEN__
#define MEMP_NUM_NETBUF                 2
#endif

/**
 * Defines the number of struct netconns.
 * This macro is only needed if you use  sequential APIs, like api_lib.c.
 */
#if !defined MEMP_NUM_NETCONN || defined __DOXYGEN__
#define MEMP_NUM_NETCONN                4
#endif

/**
 * Defines the number of struct tcpip_msg, which are used
 * for callback/timeout API communication.
 * This macro is only needed if you use  tcpip.c.
 */
#if !defined MEMP_NUM_TCPIP_MSG_API || defined __DOXYGEN__
#define MEMP_NUM_TCPIP_MSG_API          8
#endif

/**
 * Defines the number of struct tcpip_msg, which are used
 * for incoming packets.
 * This macro is only needed if you use  tcpip.c.
 */
#if !defined MEMP_NUM_TCPIP_MSG_INPKT || defined __DOXYGEN__
#define MEMP_NUM_TCPIP_MSG_INPKT        8
#endif

/**
 * Defines the number of concurrently running lwip_addrinfo() calls,
 * before freeing the corresponding memory using lwip_freeaddrinfo().
 */
#if !defined MEMP_NUM_NETDB || defined __DOXYGEN__
#define MEMP_NUM_NETDB                  8
#endif

/**
 * Defines the number of host entries in the local host list
 * if DNS_LOCAL_HOSTLIST_IS_DYNAMIC==1.
 */
#if !defined MEMP_NUM_LOCALHOSTLIST || defined __DOXYGEN__
#define MEMP_NUM_LOCALHOSTLIST          1
#endif
#ifndef LWIP_DNS_API_DECLARE_H_ERRNO
#define LWIP_DNS_API_DECLARE_H_ERRNO  0
#endif

/**
 * Defines the number of buffers in the pbuf pool.
 */
#if !defined PBUF_POOL_SIZE || defined __DOXYGEN__
#define PBUF_POOL_SIZE                  16
#endif

/** Defines the number of concurrently active calls to various
 * socket, netconn, and tcpip functions.
 */
#if !defined MEMP_NUM_API_MSG || defined __DOXYGEN__
#define MEMP_NUM_API_MSG                MEMP_NUM_TCPIP_MSG_API
#endif

/** Defines the number of concurrently active calls to netconn_gethostbyname.
 */
#if !defined MEMP_NUM_DNS_API_MSG || defined __DOXYGEN__
#define MEMP_NUM_DNS_API_MSG            MEMP_NUM_TCPIP_MSG_API
#endif

/** Defines the number of concurrently active calls
 * to getsockopt/setsockopt.
 */
#if !defined MEMP_NUM_SOCKET_SETGETSOCKOPT_DATA || defined __DOXYGEN__
#define MEMP_NUM_SOCKET_SETGETSOCKOPT_DATA MEMP_NUM_TCPIP_MSG_API
#endif

/** Defines the number of concurrently active calls to the
 * netifapi functions.
 */
#if !defined MEMP_NUM_NETIFAPI_MSG || defined __DOXYGEN__
#define MEMP_NUM_NETIFAPI_MSG           MEMP_NUM_TCPIP_MSG_API
#endif

/**
 * Defines the number of struct rpl_api_msg, which are used
 * for callback/timeout RPL API communication.
 * This macro is only needed if you use  RPL.
 */
#if !defined MEMP_NUM_RPL_API_MSG || defined __DOXYGEN__
#define MEMP_NUM_RPL_API_MSG           4
#endif

/**
 * @}
 */

/*
   ---------------------------------
   ---------- ARP options ----------
   ---------------------------------
*/
/*
 * @defgroup lwip_opts_arp ARP
 * @ingroup lwip_opts_ipv4
 * @{
 */
/**
 * LWIP_ARP==1: Enables ARP functionality.
 */
#if !defined LWIP_ARP || defined __DOXYGEN__
#define LWIP_ARP                        1
#endif

#ifndef LWIP_ARP_GRATUITOUS_REXMIT
#define LWIP_ARP_GRATUITOUS_REXMIT 1
#endif

/**
 * ARP_TABLE_SIZE: Indicates the number of active MAC-IP address pairs cached.
 */
#if !defined ARP_TABLE_SIZE || defined __DOXYGEN__
#define ARP_TABLE_SIZE                  10
#endif

/** Defines the time an ARP entry stays valid after its last update.
 *  For ARP_TMR_INTERVAL = 1000, this is
 *  (60 * 5) seconds = 5 minutes.
 */
#if !defined ARP_MAXAGE || defined __DOXYGEN__
#define ARP_MAXAGE                      300
#endif

/**
 * ARP_QUEUEING==1: Multiple outgoing packets are queued during hardware address
 * resolution. By default, only the most recent packet is queued per IP address.
 * This is sufficient for most protocols and mainly reduces TCP connection
 * startup time. Set this to 1 if you know your application sends more than one
 * packet in a row to an IP address that is not in the ARP cache.
 */
#if !defined ARP_QUEUEING || defined __DOXYGEN__
#define ARP_QUEUEING                    0
#endif

/**
 * ETHARP_TRUST_IP_MAC==1: Incoming IP packets cause the ARP table to be
 * updated with the source MAC and IP_add supplied in the packet.
 * Disable this if you do not trust LAN peers to have the
 * correct addresses, or as a limited approach to attempt to handle
 * spoofing. If disabled, lwIP must make a new ARP request if
 * the peer is not already in the ARP table, adding a little latency.
 * The peer is in the ARP table if it requested our address earlier.
 * Also note that this slows down input processing of every IP packet.
 */
#ifndef ETHARP_TRUST_IP_MAC
#define ETHARP_TRUST_IP_MAC             1
#endif

/** Defines the maximum number of packets which may be queued for each
 *  unresolved address by other network layers. The default is 3. The value 0 means disabled.
 *  Old packets are dropped, and new packets are queued.
 */
#if !defined ARP_QUEUE_LEN || defined __DOXYGEN__
#define ARP_QUEUE_LEN                   3
#endif

/**
 * ETHARP_SUPPORT_VLAN==1: Support receiving and sending ethernet packets with
 * VLAN header. See the description of LWIP_HOOK_VLAN_CHECK and
 * LWIP_HOOK_VLAN_SET hooks to check/set VLAN headers.
 * Additionally, you can define ETHARP_VLAN_CHECK to an u16_t VLAN ID to check.
 * If ETHARP_VLAN_CHECK is defined, only VLAN-traffic for this VLAN is accepted.
 * If ETHARP_VLAN_CHECK is not defined, all traffic is accepted.
 * Alternatively, define a function/define ETHARP_VLAN_CHECK_FN(eth_hdr, vlan)
 * that returns 1 to accept a packet or 0 to drop a packet.
 */
#if !defined ETHARP_SUPPORT_VLAN || defined __DOXYGEN__
#define ETHARP_SUPPORT_VLAN             0
#endif

/** LWIP_ETHERNET==1: Enables ethernet support even though ARP might be disabled.
 */
#if !defined LWIP_ETHERNET || defined __DOXYGEN__
#define LWIP_ETHERNET                   LWIP_ARP
#endif

/** Defines the number of bytes added before the ethernet header to ensure
 * alignment of payload after that header. Since the header is 14 bytes long,
 * without this padding (for example, addresses in the IP header will not be aligned
 * on a 32-bit boundary), so setting this to 2 can speed up 32-bit-platforms.
 */
#if !defined ETH_PAD_SIZE || defined __DOXYGEN__
#define ETH_PAD_SIZE                    0
#endif

/** ETHARP_SUPPORT_STATIC_ENTRIES==1: Enables code to support static ARP table
 * entries (using etharp_add_static_entry/etharp_remove_static_entry).
 */
#if !defined ETHARP_SUPPORT_STATIC_ENTRIES || defined __DOXYGEN__
#define ETHARP_SUPPORT_STATIC_ENTRIES   0
#endif

/** ETHARP_TABLE_MATCH_NETIF==1: Match netif for ARP table entries.
 * If disabled, duplicate IP address on multiple netifs are not supported
 * (but this should only occur for AutoIP).
 */
#if !defined ETHARP_TABLE_MATCH_NETIF || defined __DOXYGEN__
#define ETHARP_TABLE_MATCH_NETIF        !LWIP_SINGLE_NETIF
#endif
/**
 * @}
 */

/** LWIP_PLC==1: Enables PLC support even though ARP might be disabled.
 */
#if !defined LWIP_PLC || defined __DOXYGEN__
#define LWIP_PLC                   0
#endif

/** LWIP_IEEE802154==1: Enables 802.15.4 support.
 */
#if !defined LWIP_IEEE802154 || defined __DOXYGEN__
#define LWIP_IEEE802154                   0
#endif

/*
   --------------------------------
   ---------- IP options ----------
   --------------------------------
*/
/*
 * @defgroup lwip_opts_ipv4 IPv4
 * @ingroup lwip_opts
 * @{
 */
/**
 * LWIP_IPV4==1: Enables IPv4.
 */
#if !defined LWIP_IPV4 || defined __DOXYGEN__
#define LWIP_IPV4                       1
#endif

/**
 * IP_FORWARD==1: Enables the ability to forward IP packets across network
 * interfaces. If you are going to run lwIP on a device with only one network
 * interface, define this to 0.
 */
#if !defined IP_FORWARD || defined __DOXYGEN__
#define IP_FORWARD                      0
#endif

/**
 * IP_REASSEMBLY==1: Reassemble incoming fragmented IP packets. Note that
 * this option does not affect outgoing packet sizes, which can be controlled
 * using IP_FRAG.
 */
#if !defined IP_REASSEMBLY || defined __DOXYGEN__
#define IP_REASSEMBLY                   0
#endif

/**
 * IP_FRAG==1: Fragments outgoing IP packets if their size exceeds MTU. Note
 * that this option does not affect incoming packet sizes, which can be
 * controlled using IP_REASSEMBLY.
 */
#if !defined IP_FRAG || defined __DOXYGEN__
#define IP_FRAG                         1
#endif

#if !LWIP_IPV4
/* disable IPv4 extensions when IPv4 is disabled */
#undef IP_FORWARD
#define IP_FORWARD                      0
#undef IP_REASSEMBLY
#define IP_REASSEMBLY                   0
#undef IP_FRAG
#define IP_FRAG                         0
#endif /* !LWIP_IPV4 */

/**
 * Defines the behavior for IP options. \n
 *      IP_OPTIONS_ALLOWED==0: All packets with IP options are dropped. \n
 *      IP_OPTIONS_ALLOWED==1: IP options are allowed (but not parsed). \n
 */
#if !defined IP_OPTIONS_ALLOWED || defined __DOXYGEN__
#define IP_OPTIONS_ALLOWED              1
#endif

/**
 * Defines the maximum time (in multiples of IP_TMR_INTERVAL - so seconds, normally)
 * a fragmented IP packet waits for all fragments to arrive. If all fragments have not arrived
 * in this time, the whole packet is discarded.
 */
#if !defined IP_REASS_MAXAGE || defined __DOXYGEN__
#define IP_REASS_MAXAGE                 3
#endif

/**
 * Defines the maximum number of pbufs waiting to be reassembled.
 * Since the received pbufs are enqueued, configure
 * PBUF_POOL_SIZE > IP_REASS_MAX_PBUFS so that the stack is still able to receive
 * packets even if the maximum amount of fragments is enqueued for reassembly.
 */
#if !defined IP_REASS_MAX_PBUFS || defined __DOXYGEN__
#define IP_REASS_MAX_PBUFS              10
#endif

/**
 * IP_FRAG_USES_STATIC_BUF==1: Use a static MTU-sized buffer for IP
 * fragmentation. Otherwise, pbufs are allocated and reference the original
 * packet data to be fragmented.
 */
#ifndef IP_FRAG_USES_STATIC_BUF
#define IP_FRAG_USES_STATIC_BUF         0
#endif

/**
 * Defines the assumed maximum MTU on any interface for IP fragment buffer
 * (requires IP_FRAG_USES_STATIC_BUF==1).This is not a configurable value.
 */
#if IP_FRAG_USES_STATIC_BUF && !defined(IP_FRAG_MAX_MTU)
#define IP_FRAG_MAX_MTU                 1500

#endif
/* As per RFC 791, "Every internet module must be able to forward a datagram of 68
 * octets without further fragmentation.  This is because an internet header
 * may be up to 60 octets, and the minimum fragment is 8 octets." */
#if IP_FRAG_USES_STATIC_BUF && !defined(IP_FRAG_MIN_MTU)
#define IP_FRAG_MIN_MTU                  68
#endif

/** IP_DEFAULT_TTL: Defines the default value for Time-To-Live used by transport layers.
 */
#if !defined IP_DEFAULT_TTL || defined __DOXYGEN__
#define IP_DEFAULT_TTL                  255
#endif

/**
 * IP_SOF_BROADCAST=1: Use the SOF_BROADCAST field to enable broadcast
 * filter per pcb on udp and raw send operations. To enable broadcast filter
 * on recv operations, you also have to set IP_SOF_BROADCAST_RECV=1.
 */
#if !defined IP_SOF_BROADCAST || defined __DOXYGEN__
#define IP_SOF_BROADCAST                1
#endif

/**
 * IP_SOF_BROADCAST_RECV (requires IP_SOF_BROADCAST=1) enables the broadcast
 * filter on recv operations.
 * @par Note
 * This macro will affect the way of recving broadcast packets for IPv4 UDP
 * and RAW socket.
 * For IPv4 UDP socket:
 *   - Mode 1: The incoming broadcast packet whose destination IP address fully
 *     match the binding address will be accepted. Socket binding with ANY address
 *     can receive any broadcast packets.
 *   - Mode 2: The incoming broadcast packet whose destination IP address is on
 *     the same subnet of binding address will be accepted. Broadcast packet with
 *     255.255.255.255 as destination will be accepted by all sockets. Socket
 *     bindng with ANY address will receive any broadcast packets.
 * For IPv4 RAW socket:
 *   - Mode 1: The incoming broadcast packet whose destination IP address fully
 *     match the binding address will be accepted. Socket binding with ANY address
 *     can receive any broadcast packets.
 *   - Mode 2: Only socket binding with ANY address can receive broadcast packets.
 * When this macro is disabled, both IPv4 UDP/RAW socket works on mode 2.
 * When this macro is enabled and SO_BROADCAST is not enabled, both works on mode 1.
 * When this macro is enalbed and SO_BROADCAST is enabled, both works on mode 2.
 */
#if !defined IP_SOF_BROADCAST_RECV || defined __DOXYGEN__
#define IP_SOF_BROADCAST_RECV           1
#endif

/**
 * IP_FORWARD_ALLOW_TX_ON_RX_NETIF==1: Allows ip_forward() to send packets back
 * out on the netif where it was received. This should only be used for
 * wireless networks.
 * @par Note
 * When this is 1, ensure that the netif driver correctly marks incoming
 * link-layer-broadcast/multicast packets using the corresponding pbuf flags.
 */
#if !defined IP_FORWARD_ALLOW_TX_ON_RX_NETIF || defined __DOXYGEN__
#define IP_FORWARD_ALLOW_TX_ON_RX_NETIF 0
#endif

/**
 * @}
 */

/*
   ----------------------------------
   ---------- ICMP options ----------
   ----------------------------------
*/
/*
 * @defgroup lwip_opts_icmp ICMP
 * @ingroup lwip_opts_ipv4
 * @{
 */
/**
 * LWIP_ICMP==1: Enables the ICMP module inside the IP stack.
 * Disabling this macro make your product non-compliant to RFC1122.
 */
#if !defined LWIP_ICMP || defined __DOXYGEN__
#define LWIP_ICMP                       1
#endif

/**
 * Defines the default value for Time-To-Live used by ICMP packets.
 */
#if !defined ICMP_TTL || defined __DOXYGEN__
#define ICMP_TTL                       (IP_DEFAULT_TTL)
#endif

/**
 * LWIP_BROADCAST_PING==1: Responds to broadcast pings (default is unicast only).
 */
#if !defined LWIP_BROADCAST_PING || defined __DOXYGEN__
#define LWIP_BROADCAST_PING             0
#endif

/**
 * LWIP_MULTICAST_PING==1: Respond to multicast pings (default allows multicast ping).
 */
#if !defined LWIP_MULTICAST_PING || defined __DOXYGEN__
#define LWIP_MULTICAST_PING             1
#endif
/**
 * @}
 */

/**
 * DRIVER_STATUS_CHECK =0. If enabled can create low performance
 * Usage should be avoided.
 */
#ifndef DRIVER_STATUS_CHECK
#define DRIVER_STATUS_CHECK       0
#endif

/**
 * DRIVER_WAKEUP_INTERVAL = 120000. Not a configurable value.
 */
#if DRIVER_STATUS_CHECK
#ifndef DRIVER_WAKEUP_INTERVAL
#define DRIVER_WAKEUP_INTERVAL 120000
#endif
#endif

/* netif ifindex MUST NOT start from 0 as this value means no netif was bond to sockets */
/**
 * LWIP_NETIF_IFINDEX_START==1: Defines the start index of the interface list.
 * Not a configurable value.
 */
#ifndef LWIP_NETIF_IFINDEX_START
#define LWIP_NETIF_IFINDEX_START        1
#endif /* LWIP_NETIF_IFINDEX_START */

/**
 * LWIP_NETIF_IFINDEX_MAX==10: Defines the start index of the interface list.
 * Not a configurable value.
 */
#ifndef LWIP_NETIF_IFINDEX_MAX
#define LWIP_NETIF_IFINDEX_MAX 0xFE
#endif

/*
   ---------------------------------
   ---------- RAW options ----------
   ---------------------------------
*/
/*
 * @defgroup lwip_opts_raw RAW
 * @ingroup lwip_opts_callback
 * @{
 */
/**
 * LWIP_RAW==1: Enables the application layer to hook into the IP layer itself.
 */
#if !defined LWIP_RAW || defined __DOXYGEN__
#define LWIP_RAW                        1
#endif

/**
 * LWIP_RAW==1: Enables the application layer to hook into the IP layer itself.
 */
#if !defined RAW_TTL || defined __DOXYGEN__
#define RAW_TTL                        (IP_DEFAULT_TTL)
#endif
/**
 * @}
 */

/**
 * If PF_PKT_SUPPORT==1  Enables support for PF packet raw sockets.
 * Requires LWIP_RAW ==1 to be enabled.
 */
#if LWIP_RAW
#ifndef PF_PKT_SUPPORT
#define PF_PKT_SUPPORT  1
#endif
#else
#undef PF_PKT_SUPPORT
#define PF_PKT_SUPPORT 0
#endif

/**
 * If LWIP_NETIF_PROMISC==1 Enables the promiscuous mode of the netif.
 * Requires PF_PKT_SUPPORT ==1 to be enabled.
 */
#if PF_PKT_SUPPORT
#ifndef LWIP_NETIF_PROMISC
#define LWIP_NETIF_PROMISC 1
#endif
#else
#ifndef LWIP_NETIF_PROMISC
#define LWIP_NETIF_PROMISC 0
#endif
#endif

/*
   ----------------------------------
   ---------- DHCP options ----------
   ----------------------------------
*/
/*
 * @defgroup lwip_opts_dhcp DHCP
 * @ingroup lwip_opts_ipv4
 * @{
 */
/**
 * LWIP_DHCP==1: Enables the DHCP module.
 */
#if !defined LWIP_DHCP || defined __DOXYGEN__
#define LWIP_DHCP                       0
#endif
#if !LWIP_IPV4
/* disable DHCP when IPv4 is disabled */
#undef LWIP_DHCP
#define LWIP_DHCP                       0
#endif /* !LWIP_IPV4 */

/**
 * If LWIP_DHCPS==1: Enables the DHCP server handling.
 * Requires LWIP_DHCP ==1 to be enabled.
 */
#if !defined LWIP_DHCPS || defined __DOXYGEN__
#if LWIP_DHCP
#define LWIP_DHCPS                     1
#else
#define LWIP_DHCPS                     0
#endif
#endif

#if (defined LWIP_DHCPS) && (LWIP_DHCPS) && (LWIP_DNS)
#define LWIP_DHCPS_DNS_OPTION                     1
#endif /* LWIP_DHCPS */

/**
 * DHCP_DOES_ARP_CHECK==1: Does an ARP check on the offered address.
 */
#if !defined DHCP_DOES_ARP_CHECK || defined __DOXYGEN__
#define DHCP_DOES_ARP_CHECK             ((LWIP_DHCP) && (LWIP_ARP))
#endif

/**
 * LWIP_DHCP_BOOTP_FILE==1: Stores offered_si_addr and boot_file_name.
 */
#if !defined LWIP_DHCP_BOOTP_FILE || defined __DOXYGEN__
#define LWIP_DHCP_BOOTP_FILE            0
#endif

/**
 * LWIP_DHCP_VENDOR_CLASS_IDENTIFIER==1: use DHCP_OPTION_VCI into DHCP message.
 */
#ifndef LWIP_DHCP_VENDOR_CLASS_IDENTIFIER
#define LWIP_DHCP_VENDOR_CLASS_IDENTIFIER             1
#endif

/**
 * LWIP_DHCP_GETS_NTP==1: Requests NTP servers with discover/select. For each
 * response packet, a callback is called, which has to be provided by the port:
 * void dhcp_set_ntp_servers(u8_t num_ntp_servers, ip_addr_t* ntp_server_addrs);
*/
#if !defined LWIP_DHCP_GET_NTP_SRV || defined __DOXYGEN__
#define LWIP_DHCP_GET_NTP_SRV           0
#endif

/**
 * The maximum of NTP servers requested.
 */
#if !defined LWIP_DHCP_MAX_NTP_SERVERS || defined __DOXYGEN__
#define LWIP_DHCP_MAX_NTP_SERVERS       1
#endif

/**
 * LWIP_DHCP_MAX_DNS_SERVERS > 0: Requests the DNS servers with discover/select.
 * DHCP servers received in the response are passed to DNS via @ref dns_setserver()
 * (up to the maximum limit defined here).
 */
#if !defined LWIP_DHCP_MAX_DNS_SERVERS || defined __DOXYGEN__
#define LWIP_DHCP_MAX_DNS_SERVERS       DNS_MAX_SERVERS
#endif
/**
 * @}
 */

/*
   ------------------------------------
   ---------- AUTOIP options ----------
   ------------------------------------
*/
/*
 * @defgroup lwip_opts_autoip AUTOIP
 * @ingroup lwip_opts_ipv4
 * @{
 */
/**
 * LWIP_AUTOIP==1: Enable AUTOIP module.
 */
#if !defined LWIP_AUTOIP || defined __DOXYGEN__
#define LWIP_AUTOIP                     0
#endif
#if !LWIP_IPV4
/* disable AUTOIP when IPv4 is disabled */
#undef LWIP_AUTOIP
#define LWIP_AUTOIP                     0
#endif /* !LWIP_IPV4 */

/**
 * LWIP_DHCP_AUTOIP_COOP==1: Allow DHCP and AUTOIP to be both enabled on
 * the same interface at the same time.
 */
#if !defined LWIP_DHCP_AUTOIP_COOP || defined __DOXYGEN__
#define LWIP_DHCP_AUTOIP_COOP           0
#endif

/**
 * LWIP_DHCP_AUTOIP_COOP_TRIES: Defines the number of DHCP DISCOVER probes
 * that should be sent before falling back on AUTOIP (the DHCP client keeps
 * running in this case). This can be set as low as 1 to get an AutoIP address
 * very  quickly, but you should be prepared to handle a changing IP address
 * when DHCP overrides AutoIP.
 */
#if !defined LWIP_DHCP_AUTOIP_COOP_TRIES || defined __DOXYGEN__
#define LWIP_DHCP_AUTOIP_COOP_TRIES     64
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ----- SNMP MIB2 support      -----
   ----------------------------------
*/
/*
 * @defgroup lwip_opts_mib2 SNMP MIB2 callbacks
 * @ingroup lwip_opts_infrastructure
 * @{
 */
/**
 * LWIP_MIB2_CALLBACKS==1: Turns on SNMP MIB2 callbacks.
 * Turn this on to get callbacks needed to implement MIB2.
 * Usually MIB2_STATS should also be enabled.
 */
#if !defined LWIP_MIB2_CALLBACKS || defined __DOXYGEN__
#define LWIP_MIB2_CALLBACKS             0
#endif
/**
 * @}
 */

/*
   ----------------------------------
   -------- Multicast options -------
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_multicast Multicast
 * @ingroup lwip_opts_infrastructure
 * @{
 */
/**
 * LWIP_MULTICAST_TX_OPTIONS==1: Enable multicast TX support like the socket options
 * IP_MULTICAST_TTL/IP_MULTICAST_IF/IP_MULTICAST_LOOP, as well as (currently only)
 * core support for the corresponding IPv6 options.
 */
#if !defined LWIP_MULTICAST_TX_OPTIONS || defined __DOXYGEN__
#define LWIP_MULTICAST_TX_OPTIONS       ((LWIP_IGMP || LWIP_IPV6_MLD) && LWIP_UDP)
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ---------- IGMP options ----------
   ----------------------------------
*/
/**
 * @defgroup lwip_opts_igmp IGMP
 * @ingroup lwip_opts_ipv4
 * @{
 */
/**
 * LWIP_IGMP==1: Turns on IGMP module.
 */
#if !defined LWIP_IGMP || defined __DOXYGEN__
#define LWIP_IGMP                       0
#endif
#if !LWIP_IPV4
#undef LWIP_IGMP
#define LWIP_IGMP                       0
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ---------- DNS options -----------
   ----------------------------------
*/
/*
 * @defgroup lwip_opts_dns DNS
 * @ingroup lwip_opts_callback
 * @{
 */
/**
 * LWIP_DNS==1: Turn on DNS module. UDP must be available for DNS
 * transport.
 */
#if !defined LWIP_DNS || defined __DOXYGEN__
#define LWIP_DNS                        0
#endif

/** Defines the maximum number of DNS entries to maintain locally. */
#if !defined DNS_TABLE_SIZE || defined __DOXYGEN__
#define DNS_TABLE_SIZE                  4
#endif

/** Defines the maximum DNS host name length supported in the name table. */
#if !defined DNS_MAX_NAME_LENGTH || defined __DOXYGEN__
#define DNS_MAX_NAME_LENGTH             256
#endif

/** Defines the maximum of DNS servers.
 * The first server can be initialized automatically by defining
 * DNS_SERVER_ADDRESS(ipaddr), where 'ipaddr' is an 'ip_addr_t*'
 */
#if !defined DNS_MAX_SERVERS || defined __DOXYGEN__
#define DNS_MAX_SERVERS                 2
#endif

/** Defines the maximum number of IP addresses supported.**/
#ifndef DNS_MAX_IPADDR
#define DNS_MAX_IPADDR                10
#endif

/** Defines the maximum DNS label length as per RFC. **/
#ifndef DNS_MAX_LABEL_LENGTH
#define DNS_MAX_LABEL_LENGTH          63
#endif

/** Defines whether DNS does a name checking between the query and the response. */
#if !defined DNS_DOES_NAME_CHECK || defined __DOXYGEN__
#define DNS_DOES_NAME_CHECK             1
#endif

/** Controls the security level of the DNS implementation
 * Use all DNS security features by default.
 * This is overridable but should only be needed by very small targets
 * or when using against non-standard DNS servers. */
#if !defined LWIP_DNS_SECURE || defined __DOXYGEN__
#define LWIP_DNS_SECURE (LWIP_DNS_SECURE_RAND_XID | LWIP_DNS_SECURE_NO_MULTIPLE_OUTSTANDING | LWIP_DNS_SECURE_RAND_SRC_PORT)
#endif

/* A list of DNS security features follows */
#define LWIP_DNS_SECURE_RAND_XID                1
#define LWIP_DNS_SECURE_NO_MULTIPLE_OUTSTANDING 2
#define LWIP_DNS_SECURE_RAND_SRC_PORT           4

/** Implements a local host-to-address list. If enabled, you must define an initializer:
 *  \#define DNS_LOCAL_HOSTLIST_INIT {DNS_LOCAL_HOSTLIST_ELEM("host_ip4", IPADDR4_INIT_BYTES(1,2,3,4)), \
 *                                    DNS_LOCAL_HOSTLIST_ELEM("host_ip6", IPADDR6_INIT_HOST(123, 234, 345, 456)}
 *
 *  Instead, you can also use an external function:
 *  \#define DNS_LOOKUP_LOCAL_EXTERN(x)
 * extern err_t my_lookup_function(const char *name, ip_addr_t *addr, u8_t dns_addrtype)
 *  that looks up the IP address and returns ERR_OK if found (LWIP_DNS_ADDRTYPE_xxx is passed in dns_addrtype).
 */
#if !defined DNS_LOCAL_HOSTLIST || defined __DOXYGEN__
#define DNS_LOCAL_HOSTLIST              0
#endif /* DNS_LOCAL_HOSTLIST */

/** If this macro is enabled, the local host-list can be dynamically changed
 *  at runtime. */
#if !defined DNS_LOCAL_HOSTLIST_IS_DYNAMIC || defined __DOXYGEN__
#define DNS_LOCAL_HOSTLIST_IS_DYNAMIC   0
#endif /* DNS_LOCAL_HOSTLIST_IS_DYNAMIC */

/** Set this macro to 1 to enable querying ".local" names via mDNS
 *  using a One-Shot Multicast DNS Query */
#if !defined LWIP_DNS_SUPPORT_MDNS_QUERIES || defined __DOXYGEN__
#define LWIP_DNS_SUPPORT_MDNS_QUERIES  0
#endif
/**
 * @}
 */

/*
   ----------------------------------
   ---------- SNTP options ----------
   ----------------------------------
*/
/**
 * LWIP_SNTP==1: Enables the SNTP module.
 */

#ifndef LWIP_SNTP
#define LWIP_SNTP                      0
#endif

#ifndef LWIP_6LOWPAN
#define LWIP_6LOWPAN  0
#endif

#ifndef ETH_6LOWPAN
#define ETH_6LOWPAN  0
#endif

#ifndef LWIP_ETH_6LOWPAN_ENABLE
#define LWIP_ETH_6LOWPAN_ENABLE  0
#endif

/*
   ---------------------------------
   ---------- UDP options ----------
   ---------------------------------
*/
/*
 * @defgroup lwip_opts_udp UDP
 * @ingroup lwip_opts_callback
 * @{
 */
/**
 * LWIP_UDP==1: Enables UDP.
 */
#if !defined LWIP_UDP || defined __DOXYGEN__
#define LWIP_UDP                        1
#endif

/**
 * LWIP_UDPLITE==1: Enables UDP-Lite. (Requires LWIP_UDP)
 */
#if !defined LWIP_UDPLITE || defined __DOXYGEN__
#define LWIP_UDPLITE                    0
#endif

/**
 * Defines the default Time-To-Live value.
 */
#if !defined UDP_TTL || defined __DOXYGEN__
#define UDP_TTL                         (IP_DEFAULT_TTL)
#endif

/**
 * Appends destination addr and port to every netbuf.
 */
#if !defined LWIP_NETBUF_RECVINFO || defined __DOXYGEN__
#define LWIP_NETBUF_RECVINFO            0
#endif
/**
 * @}
 */

/*
   ---------------------------------
   ---------- TCP options ----------
   ---------------------------------
*/
/*
 * @defgroup lwip_opts_tcp TCP
 * @ingroup lwip_opts_callback
 * @{
 */
/**

 * Defines whether to enable TCP.
 */
#if !defined LWIP_TCP || defined __DOXYGEN__
#define LWIP_TCP                        1
#endif

/**
 * @ingroup Config_TCP
 * Defines the default Time-To-Live value.
 */
#if !defined TCP_TTL || defined __DOXYGEN__
#define TCP_TTL                         (IP_DEFAULT_TTL)
#endif
/**
* @ingroup Config_TCP
 * Defines the TCP Maximum segment size.
 * For the receive side, this MSS is advertised to the remote side
 * when opening a connection. For the transmit size, this MSS sets
 * an upper limit on the MSS advertised by the remote host.
 */
/* TCP Maximum segment size. */
#ifdef LWIP_TCP_MSS
#undef TCP_MSS      /* ensure TCP_MSS value is overridden by LWIP_TCP_MSS */
#define TCP_MSS                 LWIP_TCP_MSS
#else /* LWIP_TCP_MSS */
#ifndef TCP_MSS
#define TCP_MSS  (IP_FRAG_MAX_MTU - 20 - 20)
#endif /* TCP_MSS */
#endif /* LWIP_TCP_MSS */

/**
 * @ingroup Config_TCP
 * Defines the size of a TCP receive window.  This must be at least
 * (2 * TCP_MSS).
 * @par Note
 * When using TCP_RCV_SCALE, TCP_WND is the total size
 * with scaling applied. Maximum window value in the TCP header
 * will be TCP_WND >> TCP_RCV_SCALE.
 */
#if !defined TCP_WND || defined __DOXYGEN__
#define TCP_WND                         (4 * TCP_MSS)
#endif

/**
 * Defines the minimum TTL value.  This value cannot be less than 8.
 */
#ifndef TCP_TTL_MIN_VALUE
#define TCP_TTL_MIN_VALUE 8
#endif

/**
 * Defines the maximum value of the RTO duration. This value must be at least 60 seconds.
 */
#ifndef TCP_MAX_RTO_DURATION
#define TCP_MAX_RTO_DURATION 60000
#endif

/**
 * Defines the maximum number of retransmissions. This value must not be less than 3.
 */
#ifndef TCP_MAXRTX_MIN_VALUE
#define TCP_MAXRTX_MIN_VALUE 3
#endif

/**
 * @ingroup Config_TCP
 * Defines the maximum number of retransmissions of data segments.
 */
#if !defined TCP_MAXRTX || defined __DOXYGEN__
#define TCP_MAXRTX                      15
#endif

/**
 * Defines the maximum number of retransmissions of SYN segments.
 */
#if !defined TCP_SYNMAXRTX || defined __DOXYGEN__
#define TCP_SYNMAXRTX                   6
#endif

/**
 * Defines the Maximum number of retransmissions of data segments in FIN_WAIT_1 or CLOSING.
 */
#ifndef TCP_FW1MAXRTX
#define TCP_FW1MAXRTX                   8
#endif

/**
 * TCP_QUEUE_OOSEQ==1: TCP will queue segments that arrive out of order.
 * Define to 0 if your device is low on memory.
 */
#if !defined TCP_QUEUE_OOSEQ || defined __DOXYGEN__
#define TCP_QUEUE_OOSEQ                 (LWIP_TCP)
#endif

/**
 * TCP_CALCULATE_EFF_SEND_MSS: "The maximum size of a segment that TCP really
 * sends, the 'effective send MSS,' MUST be the smaller of the send MSS (which
 * reflects the available reassembly buffer size at the remote host) and the
 * largest size permitted by the IP layer" (RFC 1122)
 * Setting this to 1 enables code that checks TCP_MSS against the MTU of the
 * netif used for a connection and limits the MSS if it would be too big otherwise.
 */
#if !defined TCP_CALCULATE_EFF_SEND_MSS || defined __DOXYGEN__
#define TCP_CALCULATE_EFF_SEND_MSS      1
#endif

/**
 * @ingroup Config_TCP
 * Defines the TCP sender buffer space in bytes.
 * To achieve good performance, this should be at least 2 * TCP_MSS.
 */
#if !defined TCP_SND_BUF || defined __DOXYGEN__
#define TCP_SND_BUF                     (2 * TCP_MSS)
#endif

/**
 * TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
 * as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work.
 */
#if !defined TCP_SND_QUEUELEN || defined __DOXYGEN__
#define TCP_SND_QUEUELEN                ((4 * (TCP_SND_BUF) + ((TCP_MSS) - 1)) / (TCP_MSS))
#endif

/**
 * TCP_OOSEQ_MAX_BYTES: The default maximum number of bytes queued on ooseq per
 * pcb if TCP_OOSEQ_BYTES_LIMIT is not defined. Default is 0 (no limit).
 * Only valid for TCP_QUEUE_OOSEQ==1.
 */
#if !defined TCP_OOSEQ_MAX_BYTES || defined __DOXYGEN__
#define TCP_OOSEQ_MAX_BYTES             0
#endif

/**
 * TCP_OOSEQ_BYTES_LIMIT(pcb): Return the maximum number of bytes to be queued
 * on ooseq per pcb, given the pcb. Only valid for TCP_QUEUE_OOSEQ==1 &&
 * TCP_OOSEQ_MAX_BYTES==1.
 * Use this to override TCP_OOSEQ_MAX_BYTES to a dynamic value per pcb.
 */
#if !defined TCP_OOSEQ_BYTES_LIMIT
#if TCP_OOSEQ_MAX_BYTES
#define TCP_OOSEQ_BYTES_LIMIT(pcb) TCP_OOSEQ_MAX_BYTES
#elif defined __DOXYGEN__
#define TCP_OOSEQ_BYTES_LIMIT(pcb)
#endif
#endif

/**
 * TCP_OOSEQ_MAX_PBUFS: The default maximum number of pbufs queued on ooseq per
 * pcb if TCP_OOSEQ_BYTES_LIMIT is not defined. Default is 0 (no limit).
 * Only valid for TCP_QUEUE_OOSEQ==1.
 */
#if !defined TCP_OOSEQ_MAX_PBUFS || defined __DOXYGEN__
#define TCP_OOSEQ_MAX_PBUFS             0
#endif

/**
 * TCP_OOSEQ_PBUFS_LIMIT(pcb): Return the maximum number of pbufs to be queued
 * on ooseq per pcb, given the pcb.  Only valid for TCP_QUEUE_OOSEQ==1 &&
 * TCP_OOSEQ_MAX_PBUFS==1.
 * Use this to override TCP_OOSEQ_MAX_PBUFS to a dynamic value per pcb.
 */
#if !defined TCP_OOSEQ_PBUFS_LIMIT
#if TCP_OOSEQ_MAX_PBUFS
#define TCP_OOSEQ_PBUFS_LIMIT(pcb) TCP_OOSEQ_MAX_PBUFS
#elif defined __DOXYGEN__
#define TCP_OOSEQ_PBUFS_LIMIT(pcb)
#endif
#endif

/**
 * Defines whether to enable the backlog option for tcp listen pcb.
 */
#if !defined TCP_LISTEN_BACKLOG || defined __DOXYGEN__
#define TCP_LISTEN_BACKLOG              1
#endif

/**
 * Defines the maximum allowed backlog for TCP listen netconns.
 * This backlog is used unless another is explicitly specified.
 * 0xff is the maximum (u8_t).
 */
#if !defined TCP_DEFAULT_LISTEN_BACKLOG || defined __DOXYGEN__
#define TCP_DEFAULT_LISTEN_BACKLOG      16
#endif

/**
 * TCP_OVERSIZE: The maximum number of bytes that tcp_write may
 * allocate ahead of time in an attempt to create shorter pbuf chains
 * for transmission. The meaningful range is 0 to TCP_MSS. Some
 * suggested values are:
 *
 * 0:         Disable oversized allocation. Each tcp_write() allocates a new
              pbuf (old behaviour).
 * 1:         Allocate size-aligned pbufs with minimal excess. Use this if your
 *            scatter-gather DMA requires aligned fragments.
 * 128:       Limit the pbuf/memory overhead to 20%.
 * TCP_MSS:   Try to create unfragmented TCP packets.
 * TCP_MSS/4: Try to create 4 fragments or less per TCP packet.
 */
#if !defined TCP_OVERSIZE || defined __DOXYGEN__
#define TCP_OVERSIZE                    TCP_MSS
#endif

/**
 * LWIP_TCP_TIMESTAMPS==1: Support the TCP timestamp option.
 * The timestamp option is currently only used to help remote hosts, and it is not
 * really used locally. Therefore, it is only enabled when a TS option is
 * received in the initial SYN packet from a remote host.
 */
#if !defined LWIP_TCP_TIMESTAMPS || defined __DOXYGEN__
#define LWIP_TCP_TIMESTAMPS             0
#endif

/**
 * Defines the difference in window to trigger an
 * explicit window update.
 */
#if !defined TCP_WND_UPDATE_THRESHOLD || defined __DOXYGEN__
#define TCP_WND_UPDATE_THRESHOLD   LWIP_MIN((TCP_WND / 4), (TCP_MSS * 4))
#endif

/**
 * LWIP_EVENT_API and LWIP_CALLBACK_API: Only one of these should be set to 1.
 *     LWIP_EVENT_API==1: The user defines lwip_tcp_event() to receive all
 *         events (accept, sent, etc) that happen in the system.
 *     LWIP_CALLBACK_API==1: The PCB callback function is called directly
 *         for the event. This is the default and is not a configurable value.
 */
#if !defined(LWIP_EVENT_API) && !defined(LWIP_CALLBACK_API) || defined __DOXYGEN__
#define LWIP_EVENT_API                  0
#define LWIP_CALLBACK_API               1
#else
#ifndef LWIP_EVENT_API
#define LWIP_EVENT_API                  0
#endif
#ifndef LWIP_CALLBACK_API
#define LWIP_CALLBACK_API               0
#endif
#endif

/**
 * LWIP_WND_SCALE and TCP_RCV_SCALE:
 * Set LWIP_WND_SCALE to 1 to enable window scaling.
 * Set TCP_RCV_SCALE to the desired scaling factor (shift count in the
 * range of [0..14]).
 * When LWIP_WND_SCALE is enabled but TCP_RCV_SCALE is 0, we can use a large
 * send window while having a small receive window only.
 */
#if !defined LWIP_WND_SCALE || defined __DOXYGEN__
#define LWIP_WND_SCALE                  1
#define TCP_RCV_SCALE                   7
#else
#if !defined TCP_RCV_SCALE || defined __DOXYGEN__
#define TCP_RCV_SCALE                   7
#endif
#endif

/**
 * LWIP_TCP_PCB_NUM_EXT_ARGS:
 * When this is > 0, every tcp pcb (including listen pcb) includes a number of
 * additional argument entries in an array (see tcp_ext_arg_alloc_id)
 */
#if !defined LWIP_TCP_PCB_NUM_EXT_ARGS || defined __DOXYGEN__
#define LWIP_TCP_PCB_NUM_EXT_ARGS       0
#endif

/**
 * @}
 */

/*
   ----------------------------------
   ---------- Pbuf options ----------
   ----------------------------------
*/
/*
 * @defgroup lwip_opts_pbuf PBUF
 * @ingroup lwip_opts
 * @{
 */
/**
 * Defines the number of bytes that should be allocated for a
 * link level header. The default is 14, the standard value for
 * Ethernet.
 */
#if !defined PBUF_LINK_HLEN || defined __DOXYGEN__
#if defined LWIP_HOOK_VLAN_SET && !defined __DOXYGEN__
#define PBUF_LINK_HLEN                  (18 + ETH_PAD_SIZE)
#else /* LWIP_HOOK_VLAN_SET */
#define PBUF_LINK_HLEN                  (14 + ETH_PAD_SIZE)
#endif /* LWIP_HOOK_VLAN_SET */
#endif

/**
 * Defines the number of bytes that should be allocated
 * for an additional encapsulation header before Ethernet headers such as e.g. 802.11.
 */
#if !defined PBUF_LINK_ENCAPSULATION_HLEN || defined __DOXYGEN__
#define PBUF_LINK_ENCAPSULATION_HLEN    0u
#endif

/**
 * Defines the size of each pbuf in the pbuf pool. The default is
 * designed to accommodate single full size TCP frame in one pbuf, including
 * TCP_MSS, IP header, and link header.
 */
#if !defined PBUF_POOL_BUFSIZE || defined __DOXYGEN__
#define PBUF_POOL_BUFSIZE LWIP_MEM_ALIGN_SIZE((TCP_MSS) + 40 + (PBUF_LINK_ENCAPSULATION_HLEN) + (PBUF_LINK_HLEN))
#endif
/**
 * @}
 */

/*
   ------------------------------------------------
   ---------- Network Interfaces options ----------
   ------------------------------------------------
*/
/*
 * @defgroup lwip_opts_netif NETIF
 * @ingroup lwip_opts
 * @{
 */
/**
 * @defgroup lwip_opts_netif NETIF
 * @ingroup lwip_opts
 * @{
 */
/**
 * LWIP_SINGLE_NETIF==1: use a single netif only. This is the common case for
 * small real-life targets. Some code like routing etc. can be left out.
 */
#if !defined LWIP_SINGLE_NETIF || defined __DOXYGEN__
#define LWIP_SINGLE_NETIF               0
#endif

/**
 * LWIP_NETIF_HOSTNAME==1: Use DHCP_OPTION_HOSTNAME with netifs hostname
 * field.
 */
#if !defined LWIP_NETIF_HOSTNAME || defined __DOXYGEN__
#define LWIP_NETIF_HOSTNAME             1
#endif

/**
 * LWIP_NETIF_HOSTNAME_DEFAULT: netif's hostname after init
 * field.This is not a configurable value.
 */
#if !defined LWIP_NETIF_HOSTNAME_DEFAULT || defined __DOXYGEN__
#define LWIP_NETIF_HOSTNAME_DEFAULT     "DEFAULT"
#endif

/**
 * NETIF_HOSTNAME_MAX_LEN: Max length for buffer store the hostname string.
 * The value should be 4 byte aligned and not exceed 256. The minimum value
 * requirement is capable to store string of LWIP_NETIF_HOSTNAME_DEFAULT
 * including tailing zero.This is not a configurable value.
 */
#if !defined NETIF_HOSTNAME_MAX_LEN || defined __DOXYGEN__
#define NETIF_HOSTNAME_MAX_LEN 64U
#endif

/**
 * LWIP_NETIF_API==1: Support netif APIs (in netifapi.c)
 */
#if !defined LWIP_NETIF_API || defined __DOXYGEN__
#define LWIP_NETIF_API                  0
#endif

/**
 * LWIP_NETIF_API==1: Support NBR Cache APIs (in netifapi.c)
 */
#if !defined LWIP_NETIF_NBR_CACHE_API || defined __DOXYGEN__
#define LWIP_NETIF_NBR_CACHE_API                  1
#endif

/**
 * LWIP_NETIF_STATUS_CALLBACK==1: Support a callback function for wifi whenever
 * at commaond ifconfig up/down.
 */
#if !defined LWIP_L2_NETDEV_STATUS_CALLBACK || defined __DOXYGEN__
#define LWIP_L2_NETDEV_STATUS_CALLBACK      0
#endif


/**
 * LWIP_NETIF_STATUS_CALLBACK==1: Support a callback function whenever an interface
 * changes its up/down status (That is, due to DHCP IP acquisition).
 */
#if !defined LWIP_NETIF_STATUS_CALLBACK || defined __DOXYGEN__
#define LWIP_NETIF_STATUS_CALLBACK      0
#endif

/**
 * LWIP_NETIF_EXT_STATUS_CALLBACK==1: Support an extended callback function
 * for several netif related event that supports multiple subscribers.
 * @see netif_ext_status_callback
 */
#ifndef LWIP_NETIF_EXT_STATUS_CALLBACK
#define LWIP_NETIF_EXT_STATUS_CALLBACK  1
#endif

/**
 * LWIP_NETIF_LINK_CALLBACK==1: Supports a callback function from an interface
 * whenever the link changes (That is, link down).
 */
#if !defined LWIP_NETIF_LINK_CALLBACK || defined __DOXYGEN__
#define LWIP_NETIF_LINK_CALLBACK        0
#endif

#ifndef LWIP_NETIF_DEFAULT_LINK_DOWN
#define LWIP_NETIF_DEFAULT_LINK_DOWN 0
#endif

/**
 * LWIP_IP_FILTER==1: Support define a IP(v4) filter rule by user.
 */
#ifndef LWIP_IP_FILTER
#define LWIP_IP_FILTER        1
#endif

/**
 * LWIP_IPV6_FILTER==1: Support define a IPv6 filter rule by user.
 */
#ifndef LWIP_IPV6_FILTER
#define LWIP_IPV6_FILTER        1
#endif

/**
 * LWIP_NETIF_REMOVE_CALLBACK==1: Supports a callback function that is called
 * when a netif has been removed.
 */
#if !defined LWIP_NETIF_REMOVE_CALLBACK || defined __DOXYGEN__
#define LWIP_NETIF_REMOVE_CALLBACK      0
#endif

/**
 * LWIP_NETIF_HWADDRHINT==1: Cache link-layer-address hints, such as table
 * indices, in struct netif. TCP and UDP can make use of this to prevent
 * scanning the ARP table for every sent packet. While this is faster for big
 * ARP tables or many concurrent connections, it might be counter productive
 * if you have a tiny ARP table or if there never are concurrent connections.
 */
#if !defined LWIP_NETIF_HWADDRHINT || defined __DOXYGEN__
#define LWIP_NETIF_HWADDRHINT           0
#endif

#if LWIP_NETIF_HWADDRHINT
#define LWIP_NETIF_USE_HINTS              1
#else /* LWIP_NETIF_HWADDRHINT */
#define LWIP_NETIF_USE_HINTS              0
#endif /* LWIP_NETIF_HWADDRHINT */

/**
 * LWIP_NETIF_TX_SINGLE_PBUF: If this is set to 1, lwIP tries to put all data
 * to be sent into one single pbuf. This is for compatibility with DMA-enabled
 * MACs that do not support scatter-gather.
 * Note: This might involve CPU-memcpy before transmitting that would not
 * be needed without this flag. Use this flag only if required.
 *
 * @note TCP and IP-frag do not work with this.
 */
#if !defined LWIP_NETIF_TX_SINGLE_PBUF || defined __DOXYGEN__
#define LWIP_NETIF_TX_SINGLE_PBUF             1
#endif /* LWIP_NETIF_TX_SINGLE_PBUF */

#if !defined LWIP_CHECK_ADDR_ALIGN || defined __DOXYGEN__
#define LWIP_CHECK_ADDR_ALIGN 0
#endif /* dLWIP_CHECK_ADDR_ALIGN */

/**
 * LWIP_NUM_NETIF_CLIENT_DATA: Defines the number of clients that may store
 * data in client_data member array of struct netif (max. 256).
 */
#if !defined LWIP_NUM_NETIF_CLIENT_DATA || defined __DOXYGEN__
#define LWIP_NUM_NETIF_CLIENT_DATA            0
#endif

/**
 * LWIP_NUM_NETIF_CLIENT_DATA: Defines the number of clients that may store
 * data in client_data member array of struct netif.
 */
#if ! defined NETIF_USE_6BYTE_HWLEN_FOR_IEEE802154 || defined __DOXYGEN__
#if (NETIF_MAX_HWADDR_LEN == 6)
#define NETIF_USE_6BYTE_HWLEN_FOR_IEEE802154 1
#else
#define NETIF_USE_6BYTE_HWLEN_FOR_IEEE802154 0
#endif
#endif

/**
 * @}
 */

/*
   ------------------------------------
   ---------- LOOPIF options ----------
   ------------------------------------
*/
/*
 * @defgroup lwip_opts_loop Loopback interface
 * @ingroup lwip_opts_netif
 * @{
 */
/**
 * LWIP_HAVE_LOOPIF==1: Supports loop interface (127.0.0.1).
 * This is only needed when no real netifs are available. If at least one other
 * netif is available, loopback traffic uses this netif.
 */
#if !defined LWIP_HAVE_LOOPIF || defined __DOXYGEN__
#define LWIP_HAVE_LOOPIF                (LWIP_NETIF_LOOPBACK && !LWIP_SINGLE_NETIF)
#endif

/**
 * LWIP_LOOPIF_MULTICAST==1: Supports multicast/IGMP on loop interface (127.0.0.1).
 */
#if !defined LWIP_LOOPIF_MULTICAST || defined __DOXYGEN__
#define LWIP_LOOPIF_MULTICAST               0
#endif

/**
 * LWIP_NETIF_LOOPBACK==1: Supports sending packets with a destination IP
 * address equal to the netif IP address, looping them back up the stack.
 */
#if !defined LWIP_NETIF_LOOPBACK || defined __DOXYGEN__
#define LWIP_NETIF_LOOPBACK             0
#endif

/**
 * Defines the maximum number of pbufs on queue for loopback
 * sending for each netif. The default value is 0, which denotes disabling this option.
 */
#if !defined LWIP_LOOPBACK_MAX_PBUFS || defined __DOXYGEN__
#define LWIP_LOOPBACK_MAX_PBUFS         0
#endif

/**
 * Indicates whether threading is enabled in
 * the system, as netifs must change how they behave depending on this setting
 * for the LWIP_NETIF_LOOPBACK option to work.
 * Setting this is needed to avoid reentering non-reentrant functions such as
 * tcp_input().
 *    LWIP_NETIF_LOOPBACK_MULTITHREADING==1: Indicates that the user is using a
 *       multithreaded environment such as tcpip.c. In this case, netif->input()
 *       is called directly.
 *    LWIP_NETIF_LOOPBACK_MULTITHREADING==0: Indicates a polling (or NO_SYS) setup.
 *       The packets are put on a list and netif_poll() must be called in
 *       the main application loop.
 */
#if !defined LWIP_NETIF_LOOPBACK_MULTITHREADING || defined __DOXYGEN__
#define LWIP_NETIF_LOOPBACK_MULTITHREADING    (!NO_SYS)
#endif
/**
 * @}
 */

/*
   ------------------------------------
   ---------- Thread options ----------
   ------------------------------------
*/
/*
 * @defgroup lwip_opts_thread Threading
 * @ingroup lwip_opts_infrastructure
 * @{
 */
/**
 * TCPIP_THREAD_NAME: The name assigned to the main tcpip thread.
 */
#if !defined TCPIP_THREAD_NAME || defined __DOXYGEN__
#define TCPIP_THREAD_NAME              "tcpip_thread"
#endif

/**
 * Defines the stack size used by the main tcpip thread.
 * The stack size value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#if !defined TCPIP_THREAD_STACKSIZE || defined __DOXYGEN__
#define TCPIP_THREAD_STACKSIZE          0
#endif

/**
 * Defines the priority assigned to the main tcpip thread.
 * The priority value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#if !defined TCPIP_THREAD_PRIO || defined __DOXYGEN__
#define TCPIP_THREAD_PRIO               1
#endif

#ifndef LWIP_NETIF_ETHTOOL
#define LWIP_NETIF_ETHTOOL          1
#endif
/**
 * TCPIP_MBOX_SIZE: Defines the mailbox size for the tcpip thread messages.
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when tcpip_init is called.
 */
#if !defined TCPIP_MBOX_SIZE || defined __DOXYGEN__
#define TCPIP_MBOX_SIZE                 0
#endif

/**
 * Define this to something that triggers a watchdog. This is called from
 * tcpip_thread after processing a message.
 */
#if !defined LWIP_TCPIP_THREAD_ALIVE || defined __DOXYGEN__
#define LWIP_TCPIP_THREAD_ALIVE()
#endif

/**
 * Defines the name assigned to the slipif_loop thread.
 */
#if !defined SLIPIF_THREAD_NAME || defined __DOXYGEN__
#define SLIPIF_THREAD_NAME             "slipif_loop"
#endif

/**
 * Defines the stack size used by the slipif_loop thread.
 * The stack size value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#if !defined SLIPIF_THREAD_STACKSIZE || defined __DOXYGEN__
#define SLIPIF_THREAD_STACKSIZE         0
#endif

/**
 * Defines the priority assigned to the slipif_loop thread.
 * The priority value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#if !defined SLIPIF_THREAD_PRIO || defined __DOXYGEN__
#define SLIPIF_THREAD_PRIO              1
#endif

/**
 * DEFAULT_THREAD_NAME: The name assigned to any other lwIP thread.
 */
#if !defined DEFAULT_THREAD_NAME || defined __DOXYGEN__
#define DEFAULT_THREAD_NAME            "lwIP"
#endif

/**
 * Defines the stack size used by any other lwIP thread.
 * The stack size value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#if !defined DEFAULT_THREAD_STACKSIZE || defined __DOXYGEN__
#define DEFAULT_THREAD_STACKSIZE        0
#endif

/**
 * Defines the priority assigned to any other lwIP thread.
 * The priority value itself is platform-dependent, but is passed to
 * sys_thread_new() when the thread is created.
 */
#if !defined DEFAULT_THREAD_PRIO || defined __DOXYGEN__
#define DEFAULT_THREAD_PRIO             1
#endif

/**
 * Defines the mailbox size for the incoming packets on a
 * NETCONN_RAW. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#if !defined DEFAULT_RAW_RECVMBOX_SIZE || defined __DOXYGEN__
#define DEFAULT_RAW_RECVMBOX_SIZE       0
#endif

/**
 * Defines the mailbox size for the incoming packets on a
 * NETCONN_UDP. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#if !defined DEFAULT_UDP_RECVMBOX_SIZE || defined __DOXYGEN__
#define DEFAULT_UDP_RECVMBOX_SIZE       0
#endif

/**
 * Maximum size of a UDP RAW packet.
 * Different memory alignment can limit max packet size.
 *  LWIP_MAX_UDP_RAW_SEND_SIZE not a configurable value.
 */
#if (MEM_MALLOC_DMA_ALIGN != 1)
#ifndef LWIP_MAX_UDP_RAW_SEND_SIZE
#define LWIP_MAX_UDP_RAW_SEND_SIZE      65332
#endif /* LWIP_MAX_UDP_RAW_SEND_SIZE */
#else
#ifndef LWIP_MAX_UDP_RAW_SEND_SIZE
#define LWIP_MAX_UDP_RAW_SEND_SIZE      65432
#endif /* LWIP_MAX_UDP_RAW_SEND_SIZE */
#endif /* (MEM_MALLOC_DMA_ALIGN != 1) */

/**
 * Defines the mailbox size for the incoming packets on a
 * NETCONN_TCP. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#if !defined DEFAULT_TCP_RECVMBOX_SIZE || defined __DOXYGEN__
#define DEFAULT_TCP_RECVMBOX_SIZE       0
#endif

/**
 * Defines the mailbox size for the incoming connections.
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when the acceptmbox is created.
 */
#if !defined DEFAULT_ACCEPTMBOX_SIZE || defined __DOXYGEN__
#define DEFAULT_ACCEPTMBOX_SIZE         0
#endif
/**
 * @}
 */
/**
 * Defines the maximum mailbox size for the incoming packets on a
 * NETCONN_*. make it small to save memory.
 */
#ifndef MAX_MBOX_SIZE
#define MAX_MBOX_SIZE                   2048
#endif

/*
   ----------------------------------------------
   ---------- Sequential layer options ----------
   ----------------------------------------------
*/
/*
 * @defgroup lwip_opts_netconn Netconn
 * @ingroup lwip_opts_threadsafe_apis
 * @{
 */
/**
 * LWIP_NETCONN==1: Enables Netconn APIs (required to use api_lib.c)
 */
#if !defined LWIP_NETCONN || defined __DOXYGEN__
#define LWIP_NETCONN                    1
#endif

/** LWIP_TCPIP_TIMEOUT==1: Enables tcpip_timeout/tcpip_untimeout to create
 * timers running in tcpip_thread from another thread.
 */
#if !defined LWIP_TCPIP_TIMEOUT || defined __DOXYGEN__
#define LWIP_TCPIP_TIMEOUT              0
#endif

/** LWIP_NETCONN_SEM_PER_THREAD==1: Use one (thread-local) semaphore per
 * thread calling socket/netconn functions instead of allocating one
 * semaphore per netconn and per select.
 * Note: A thread-local semaphore for API calls is needed in the following cases:
 * - LWIP_NETCONN_THREAD_SEM_GET() returns a sys_sem_t*
 * - LWIP_NETCONN_THREAD_SEM_ALLOC() creates the semaphore
 * - LWIP_NETCONN_THREAD_SEM_FREE() frees the semaphore
 * The latter 2 can be invoked up by calling netconn_thread_init()/netconn_thread_cleanup().
 * Ports may call these for threads created with sys_thread_new().
 */
#if !defined LWIP_NETCONN_SEM_PER_THREAD || defined __DOXYGEN__
#define LWIP_NETCONN_SEM_PER_THREAD     0
#endif

/** LWIP_NETCONN_FULLDUPLEX==1: Enables code that allows reading from one thread,
 * writing from a second thread, and closing from a third thread at the same time.
 */
#if !defined LWIP_NETCONN_FULLDUPLEX || defined __DOXYGEN__
#define LWIP_NETCONN_FULLDUPLEX         1
#endif
/**
 * @}
 */

/*
   ------------------------------------
   ---------- Socket options ----------
   ------------------------------------
*/
/*
 * @defgroup lwip_opts_socket Sockets
 * @ingroup lwip_opts_threadsafe_apis
 * @{
 */
/**
 * LWIP_SOCKET==1: Enables Socket API (require to use sockets.c)
 */
#if !defined LWIP_SOCKET || defined __DOXYGEN__
#define LWIP_SOCKET                     1
#endif

/* LWIP_SOCKET_SET_ERRNO==1: Set errno when socket functions cannot complete
 * successfully, as required by POSIX. Default is POSIX-compliant.Not a configurable value.
 */
#if !defined LWIP_SOCKET_SET_ERRNO || defined __DOXYGEN__
#define LWIP_SOCKET_SET_ERRNO           1
#endif

/**
 * LWIP_COMPAT_SOCKETS==1: Enables BSD-style sockets functions names through defines. \n
 * LWIP_COMPAT_SOCKETS==2: Same as ==1 but correctly named functions are created.
 * While this helps code completion, it might conflict with existing libraries.
 * (only used if you use sockets.c)
 */
#if !defined LWIP_COMPAT_SOCKETS || defined __DOXYGEN__
#define LWIP_COMPAT_SOCKETS             2
#endif

/**
 * LWIP_POSIX_SOCKETS_IO_NAMES==1: Enables POSIX-style sockets functions names.
 * Disable this option if you use a POSIX operating system that uses the same
 * names (read, write & close). This option only used if you use sockets.c.
 */
#if !defined LWIP_POSIX_SOCKETS_IO_NAMES || defined __DOXYGEN__
#define LWIP_POSIX_SOCKETS_IO_NAMES     0
#endif

/**
 * LWIP_SOCKET_OFFSET==n: Increases the file descriptor number created by LwIP with n.
 * This can be useful when there are multiple APIs which create file descriptors.
 * When they all start with a different offset and you won't make them overlap you can
 * reimplement read/write/close/ioctl/fnctl to send the requested action to the right
 * library (sharing select will need more work though).
 */
#if !defined LWIP_SOCKET_OFFSET || defined __DOXYGEN__
#define LWIP_SOCKET_OFFSET              0
#endif

/**
 * LWIP_TCP_KEEPALIVE==1: Enable TCP_KEEPIDLE, TCP_KEEPINTVL, and TCP_KEEPCNT
 * options processing. Note that TCP_KEEPIDLE and TCP_KEEPINTVL have to be set
 * in seconds. (does not require sockets.c, and will affect tcp.c)
 */
#if !defined LWIP_TCP_KEEPALIVE || defined __DOXYGEN__
#define LWIP_TCP_KEEPALIVE              1
#endif

/**
 * LWIP_SO_SNDTIMEO==1: Enables send timeout for sockets/netconns and
 * SO_SNDTIMEO processing.
 */
#if !defined LWIP_SO_SNDTIMEO || defined __DOXYGEN__
#define LWIP_SO_SNDTIMEO                0
#endif

/**
 * LWIP_SO_RCVTIMEO==1: Enables receive timeout for sockets/netconns and
 * SO_RCVTIMEO processing.
 */
#if !defined LWIP_SO_RCVTIMEO || defined __DOXYGEN__
#define LWIP_SO_RCVTIMEO                0
#endif

/**
 * LWIP_SO_SNDRCVTIMEO_NONSTANDARD==1: SO_RCVTIMEO/SO_SNDTIMEO take an int
 * (milliseconds, much like winsock does) instead of a struct timeval (default).
 */
#if !defined LWIP_SO_SNDRCVTIMEO_NONSTANDARD || defined __DOXYGEN__
#define LWIP_SO_SNDRCVTIMEO_NONSTANDARD 0
#endif

/**
 * LWIP_SO_RCVBUF==1: Enables SO_RCVBUF processing.
 */
#if !defined LWIP_SO_RCVBUF || defined __DOXYGEN__
#define LWIP_SO_RCVBUF                  0
#endif

/**
 * Defines the default value for recv_bufsize if LWIP_SO_RCVBUF is used.
 */
#if !defined RECV_BUFSIZE_DEFAULT || defined __DOXYGEN__
#define RECV_BUFSIZE_DEFAULT            65535
#endif

/**
 * RECV_BUFSIZE_MIN =256 Defines the minimum buffer size required for  SO_RCVBUF configuration.
 * Value not configurable.
 */
#ifndef RECV_BUFSIZE_MIN
#define RECV_BUFSIZE_MIN                256
#endif

/**
 * LWIP_SO_SNDBUF==1: Enables SO_SNDBUF processing.
 * Currently, only TCP socket in CLOSED or ESTABLISHED state supports settung sndbuf.
 */
#ifndef LWIP_SO_SNDBUF
#define LWIP_SO_SNDBUF                  1
#endif

/**
 * SEND_BUFSIZE_MIN =TCP_MSS*2 Defines the minimum buffer size required for  SO_SNDBUF configuration.
 * Value not configurable.
 */
#ifndef SEND_BUFSIZE_MIN
#define SEND_BUFSIZE_MIN                (TCP_MSS*2)
#endif

/**
 * SEND_BUFSIZE_MAX  Defines the maximum buffer size allowed for  SO_SNDBUF configuration.
 * Value not configurable.
 */
#if LWIP_WND_SCALE
#ifndef SEND_BUFSIZE_MAX
#define SEND_BUFSIZE_MAX                0x40000
#endif
#else
#ifndef SEND_BUFSIZE_MAX
#define SEND_BUFSIZE_MAX                65535
#endif
#endif /* LWIP_WND_SCALE */

/**
 * LWIP_SO_LINGER==1: Enable SO_LINGER processing.
 */
#if !defined LWIP_SO_LINGER || defined __DOXYGEN__
#define LWIP_SO_LINGER                  0
#endif

/**
 * By default, TCP socket/netconn close waits 20 seconds max to send the FIN
 */
#if !defined LWIP_TCP_CLOSE_TIMEOUT_MS_DEFAULT || defined __DOXYGEN__
#define LWIP_TCP_CLOSE_TIMEOUT_MS_DEFAULT 20000
#endif

/**
 * SO_REUSE==1: Enables the SO_REUSEADDR option.
 */
#if !defined SO_REUSE || defined __DOXYGEN__
#define SO_REUSE                        0
#endif

/**
 * SO_REUSE_RXTOALL==1: Passes a copy of incoming broadcast/multicast packets
 * to all local matches if SO_REUSEADDR is turned on.
 * Warning: This option adds a memcpy for every packet if passing to more than one PCB.
 */
#if !defined SO_REUSE_RXTOALL || defined __DOXYGEN__
#define SO_REUSE_RXTOALL                1
#endif

/**
 * LWIP_FIONREAD_LINUXMODE==0 (default): ioctl/FIONREAD returns the amount of
 * pending data in the network buffer. This is the way Windows does it. It's
 * the default for lwIP since it is smaller.
 * LWIP_FIONREAD_LINUXMODE==1: ioctl/FIONREAD returns the size of the next
 * pending datagram in bytes. This is the way Linux does it. This code is only
 * here for compatibility.
 */
#if !defined LWIP_FIONREAD_LINUXMODE || defined __DOXYGEN__
#define LWIP_FIONREAD_LINUXMODE         0
#endif

/**
 * LWIP_SOCKET_SELECT==1 (default): enable select() for sockets (uses a netconn
 * callback to keep track of events).
 * This saves RAM (counters per socket) and code (netconn event callback), which
 * should improve performance a bit).
 */
#if !defined LWIP_SOCKET_SELECT || defined __DOXYGEN__
#define LWIP_SOCKET_SELECT              1
#endif

/**
 * LWIP_SOCKET_POLL==0 (default): enable poll() for sockets (including
 * struct pollfd, nfds_t, and constants)
 */
#if !defined LWIP_SOCKET_POLL || defined __DOXYGEN__
#define LWIP_SOCKET_POLL                0
#endif

/**
 * This will enable the network stack to use MAC layer security. At the
 transport layer only UDP will be using this mac layer security.
 */
#if !defined LWIP_MAC_SECURITY || defined __DOXYGEN__
#define LWIP_MAC_SECURITY         1
#endif

/**
 * LWIP_SO_PRIORITY==1: Enable SO_PRIORITY processing. We don't support any priority queue at IP
 layer. It just enables the user to inform the priority of application packets
 to the mac layer.
 */
#if !defined LWIP_SO_PRIORITY || defined __DOXYGEN__
#define LWIP_SO_PRIORITY                  1
#endif

#if LWIP_SO_PRIORITY
#if LWIP_PLC
typedef s32_t prio_t;
#ifndef LWIP_PKT_PRIORITY_DEFAULT
#define LWIP_PKT_PRIORITY_DEFAULT 1
#endif
#else
typedef u8_t prio_t;
#ifndef LWIP_PKT_PRIORITY_DEFAULT
#define LWIP_PKT_PRIORITY_DEFAULT LWIP_PKT_PRIORITY_MIN
#endif
#endif

#ifndef LWIP_PKT_PRIORITY_MIN
#define LWIP_PKT_PRIORITY_MIN 0
#endif

#ifndef LWIP_PKT_PRIORITY_MAX
#define LWIP_PKT_PRIORITY_MAX 3
#endif

#ifndef LWIP_PKT_PRIORITY_CTRL
#define LWIP_PKT_PRIORITY_CTRL LWIP_PKT_PRIORITY_MAX
#endif

#ifndef LWIP_PKT_PRIORITY_DHCP
#define LWIP_PKT_PRIORITY_DHCP LWIP_PKT_PRIORITY_MAX
#endif

#ifndef LWIP_PKT_PRIORITY_DHCPS
#define LWIP_PKT_PRIORITY_DHCPS LWIP_PKT_PRIORITY_MAX
#endif

#ifndef LWIP_PKT_PRIORITY_DHCP6
#define LWIP_PKT_PRIORITY_DHCP6 LWIP_PKT_PRIORITY_MAX
#endif

#ifndef LWIP_PKT_PRIORITY_DNS
#define LWIP_PKT_PRIORITY_DNS LWIP_PKT_PRIORITY_MAX
#endif

#ifndef LWIP_PKT_PRIORITY_SNTP
#define LWIP_PKT_PRIORITY_SNTP LWIP_PKT_PRIORITY_MAX
#endif
#endif

/**
 * @}
 */

/*
   ---------------------------------------
   ------------- Utitlity APIs ---------------
   ---------------------------------------
*/

/** LWIP_ENABLE_LOS_SHELL_CMD==1 Enables shell utility functions  */
#if !defined LWIP_ENABLE_LOS_SHELL_CMD || defined __DOXYGEN__
#define LWIP_ENABLE_LOS_SHELL_CMD       1
#endif

/** LWIP_SHELL_CMD_PING_RETRY_TIMES: Configuration value to determine how many times ping command has to send
    echo msg */
#if !defined LWIP_SHELL_CMD_PING_RETRY_TIMES || defined __DOXYGEN__
#define LWIP_SHELL_CMD_PING_RETRY_TIMES     4
#endif

/** LWIP_SHELL_CMD_PING_TIMEOUT =2000 :Ping cmd waiting timeout (in millisec) to receive ping response */
#if !defined LWIP_SHELL_CMD_PING_TIMEOUT || defined __DOXYGEN__
#define LWIP_SHELL_CMD_PING_TIMEOUT     2000
#endif

/** LWIP_SHELL_CMD_PING_TIMEOUT: Ping cmd waiting timeout max(in millisec) to receive ping response */
#if !defined LWIP_SHELL_CMD_PING_TIMEOUT_MAX || defined __DOXYGEN__
#define LWIP_SHELL_CMD_PING_TIMEOUT_MAX 10000
#endif

/** LWIP_SHELL_CMD_PING_TIMEOUT: Ping cmd waiting timeout min(in millisec) to receive ping response */
#if !defined LWIP_SHELL_CMD_PING_TIMEOUT_MIN || defined __DOXYGEN__
#define LWIP_SHELL_CMD_PING_TIMEOUT_MIN 1000
#endif

/*
   ----------------------------------------
   ---------- Statistics options ----------
   ----------------------------------------
*/
/*
 * @defgroup lwip_opts_stats Statistics
 * @ingroup lwip_opts_debug
 * @{
 */
/**
 * LWIP_STATS==1: Enables statistics collection in lwip_stats.
 */
#if !defined LWIP_STATS || defined __DOXYGEN__
#define LWIP_STATS                      1
#endif

#if LWIP_STATS

/**
 * LWIP_STATS_DISPLAY==1: Compiles in the statistics output functions.
 */
#if !defined LWIP_STATS_DISPLAY || defined __DOXYGEN__
#define LWIP_STATS_DISPLAY              0
#endif

/**
 * LWIP_STATS_API==1: Compiles in the statistics API functions.
 */
#if !defined LWIP_STATS_API || defined __DOXYGEN__
#define LWIP_STATS_API              1
#endif

/**
 * LINK_STATS==1: Enables the link stats.
 */
#if !defined LINK_STATS || defined __DOXYGEN__
#define LINK_STATS                      1
#endif

/**
 * ETHARP_STATS==1: Enables etharp stats.
 */
#if !defined ETHARP_STATS || defined __DOXYGEN__
#define ETHARP_STATS                    (LWIP_ARP)
#endif

/**
 * IP_STATS==1: Enables IP stats.
 */
#if !defined IP_STATS || defined __DOXYGEN__
#define IP_STATS                        1
#endif

/**
 * IPFRAG_STATS==1: Enables IP fragmentation stats. Default is
 * on if using either frag or reass.
 */
#if !defined IPFRAG_STATS || defined __DOXYGEN__
#define IPFRAG_STATS                    (IP_REASSEMBLY || IP_FRAG)
#endif

/**
 * ICMP_STATS==1: Enables ICMP stats.
 */
#if !defined ICMP_STATS || defined __DOXYGEN__
#define ICMP_STATS                      1
#endif

/**
 * IGMP_STATS==1: Enable IGMP stats.
 */
#if !defined IGMP_STATS || defined __DOXYGEN__
#define IGMP_STATS                      (LWIP_IGMP)
#endif

/**
 * UDP_STATS==1: Enables UDP stats. Default is on if
 * UDP enabled, otherwise off.
 */
#if !defined UDP_STATS || defined __DOXYGEN__
#define UDP_STATS                       (LWIP_UDP)
#endif

/**
 * TCP_STATS==1: Enables TCP stats. Default is on if TCP
 * enabled, otherwise off.
 */
#if !defined TCP_STATS || defined __DOXYGEN__
#define TCP_STATS                       (LWIP_TCP)
#endif

/**
 * MEM_STATS==1: Enables mem.c stats.
 */
#if !defined MEM_STATS || defined __DOXYGEN__
#define MEM_STATS                       ((MEM_LIBC_MALLOC == 0) && (MEM_USE_POOLS == 0))
#endif

/**
 * MEMP_STATS==1: Enables memp.c pool stats.
 */
#if !defined MEMP_STATS || defined __DOXYGEN__
#define MEMP_STATS                      (MEMP_MEM_MALLOC == 0)
#endif

/**
 * SYS_STATS==1: Enables system stats (sem and mbox counts, etc).
 */
#if !defined SYS_STATS || defined __DOXYGEN__
#define SYS_STATS                       (NO_SYS == 0)
#endif

/**
 * IP6_STATS==1: Enable IPv6 stats.
 */
#if !defined IP6_STATS || defined __DOXYGEN__
#define IP6_STATS                       (LWIP_IPV6)
#endif

/**
 * ICMP6_STATS==1: Enables ICMP for IPv6 stats.
 */
#if !defined ICMP6_STATS || defined __DOXYGEN__
#define ICMP6_STATS                     (LWIP_IPV6 && LWIP_ICMP6)
#endif

/**
 * IP6_FRAG_STATS==1: Enables IPv6 fragmentation stats.
 */
#if !defined IP6_FRAG_STATS || defined __DOXYGEN__
#define IP6_FRAG_STATS                  (LWIP_IPV6 && (LWIP_IPV6_FRAG || LWIP_IPV6_REASS))
#endif

/**
 * MLD6_STATS==1: Enables MLD for IPv6 stats.
 */
#if !defined MLD6_STATS || defined __DOXYGEN__
#define MLD6_STATS                      (LWIP_IPV6 && LWIP_IPV6_MLD)
#endif

/**
 * ND6_STATS==1: Enables neighbor discovery for IPv6 stats.
 */
#if !defined ND6_STATS || defined __DOXYGEN__
#define ND6_STATS                       (LWIP_IPV6)
#endif

/**
 * MIB2_STATS==1: Defines stats for SNMP MIB2.
 */
#if !defined MIB2_STATS || defined __DOXYGEN__
#define MIB2_STATS                      0
#endif

/**
 * DHCP6_STATS==1: Enables stats for DHCPv6.
 */
#if !defined DHCP6_STATS || defined __DOXYGEN__
#define DHCP6_STATS                       (LWIP_IPV6_DHCP6)
#endif

#else

#define LINK_STATS                      0
#define ETHARP_STATS                    0
#define IP_STATS                        0
#define IPFRAG_STATS                    0
#define ICMP_STATS                      0
#define IGMP_STATS                      0
#define UDP_STATS                       0
#define TCP_STATS                       0
#define MEM_STATS                       0
#define MEMP_STATS                      0
#define SYS_STATS                       0
#ifndef LWIP_STATS_DISPLAY
#define LWIP_STATS_DISPLAY              0
#endif
#define IP6_STATS                       0
#define ICMP6_STATS                     0
#define IP6_FRAG_STATS                  0
#define MLD6_STATS                      0
#define ND6_STATS                       0
#define MIB2_STATS                      0
#define DHCP6_STATS                     0

#endif /* LWIP_STATS */
/**
 * @}
 */

/*
   ----------------------------------
   ---------- BIRDGE options -----------
   ----------------------------------
*/
/**
 * BRIDGE_SUPPORT==1: Turns on BRIDGE module.
 */
#ifndef BRIDGE_SUPPORT
#define BRIDGE_SUPPORT                        1
#endif

/*
   --------------------------------------
   ---------- Checksum options ----------
   --------------------------------------
*/
/*
 * @defgroup lwip_opts_checksum Checksum
 * @ingroup lwip_opts_infrastructure
 * @{
 */
/**
 * LWIP_CHECKSUM_CTRL_PER_NETIF==1: Checksum generation/check can be enabled/disabled
 * per netif.
 * Note: If enabled, the CHECKSUM_GEN_* and CHECKSUM_CHECK_* defines must be enabled.
 */
#if !defined LWIP_CHECKSUM_CTRL_PER_NETIF || defined __DOXYGEN__
#define LWIP_CHECKSUM_CTRL_PER_NETIF    0
#endif

/**
 * CHECKSUM_GEN_IP==1: Generates checksums in software for outgoing IP packets.
 */
#if !defined CHECKSUM_GEN_IP || defined __DOXYGEN__
#define CHECKSUM_GEN_IP                 1
#endif

/**
 * CHECKSUM_GEN_UDP==1: Generates checksums in software for outgoing UDP packets.
 */
#if !defined CHECKSUM_GEN_UDP || defined __DOXYGEN__
#define CHECKSUM_GEN_UDP                1
#endif

/**
 * CHECKSUM_GEN_TCP==1: Generates checksums in software for outgoing TCP packets.
 */
#if !defined CHECKSUM_GEN_TCP || defined __DOXYGEN__
#define CHECKSUM_GEN_TCP                1
#endif

/**
 * CHECKSUM_GEN_ICMP==1: Generates checksums in software for outgoing ICMP packets.
 */
#if !defined CHECKSUM_GEN_ICMP || defined __DOXYGEN__
#define CHECKSUM_GEN_ICMP               1
#endif

/**
 * CHECKSUM_GEN_ICMP6==1: Generates checksums in software for outgoing ICMP6 packets.
 */
#if !defined CHECKSUM_GEN_ICMP6 || defined __DOXYGEN__
#define CHECKSUM_GEN_ICMP6              1
#endif

/**
 * CHECKSUM_CHECK_IP==1: Checks checksums in software for incoming IP packets.
 */
#if !defined CHECKSUM_CHECK_IP || defined __DOXYGEN__
#define CHECKSUM_CHECK_IP               1
#endif

/**
 * CHECKSUM_CHECK_UDP==1: Checks checksums in software for incoming UDP packets.
 */
#if !defined CHECKSUM_CHECK_UDP || defined __DOXYGEN__
#define CHECKSUM_CHECK_UDP              1
#endif

/**
 * CHECKSUM_CHECK_TCP==1: Checks checksums in software for incoming TCP packets.
 */
#if !defined CHECKSUM_CHECK_TCP || defined __DOXYGEN__
#define CHECKSUM_CHECK_TCP              1
#endif

/**
 * CHECKSUM_CHECK_ICMP==1: Checks checksums in software for incoming ICMP packets.
 */
#if !defined CHECKSUM_CHECK_ICMP || defined __DOXYGEN__
#define CHECKSUM_CHECK_ICMP             1
#endif

/**
 * CHECKSUM_CHECK_ICMP6==1: Checks checksums in software for incoming ICMPv6 packets
 */
#if !defined CHECKSUM_CHECK_ICMP6 || defined __DOXYGEN__
#define CHECKSUM_CHECK_ICMP6            1
#endif

/**
 * LWIP_CHECKSUM_ON_COPY==1: Calculates the checksum when copying data from
 * application buffers to pbufs.
 */
#if !defined LWIP_CHECKSUM_ON_COPY || defined __DOXYGEN__
#define LWIP_CHECKSUM_ON_COPY           1
#endif

/**
 * LWIP_TX_CSUM_OFFLOAD==1: Allows TX checksum offload
 */
#ifndef LWIP_TX_CSUM_OFFLOAD
#define LWIP_TX_CSUM_OFFLOAD  0
#endif
/**
 * @}
 */

/*
   ---------------------------------------
   ---------- Common options ---------------
   ---------------------------------------
*/
/**
 * LWIP_ENABLE_IP_CONFLICT_SIGNAL==1: Enables IP conflict detection
 */
#ifndef LWIP_ENABLE_IP_CONFLICT_SIGNAL
#define LWIP_ENABLE_IP_CONFLICT_SIGNAL 1
#endif

/*
   ---------------------------------------
   ---------- IPv6 options ---------------
   ---------------------------------------
*/
/*
 * @defgroup lwip_opts_ipv6 IPv6
 * @ingroup lwip_opts
 * @{
 */
#if !defined LWIP_ENABLE_ROUTER || defined __DOXYGEN__
#define LWIP_ENABLE_ROUTER   1
#endif

#if !defined LWIP_LOWER_RSSI_THRESHOLD || defined __DOXYGEN__
#define LWIP_LOWER_RSSI_THRESHOLD   (-90)
#endif

/**
 * LWIP_IPV6==1: Enables IPv6.
 */
#if !defined LWIP_IPV6 || defined __DOXYGEN__
#define LWIP_IPV6                      1
#endif

/**
 * IPV6_REASS_MAXAGE: Maximum time (in multiples of IP6_REASS_TMR_INTERVAL - so seconds, normally)
 * a fragmented IP packet waits for all fragments to arrive. If not all fragments arrived
 * in this time, the whole packet is discarded.
 */
#if !defined IPV6_REASS_MAXAGE || defined __DOXYGEN__
#define IPV6_REASS_MAXAGE               3
#endif

/**
 * LWIP_IPV6_SCOPES==1: Enable support for IPv6 address scopes, ensuring that
 * e.g. link-local addresses are really treated as link-local. Disable this
 * setting only for single-interface configurations.
 */
#if !defined LWIP_IPV6_SCOPES || defined __DOXYGEN__
#define LWIP_IPV6_SCOPES                0
#endif

/**
 * LWIP_IPV6_SCOPES_DEBUG==1: Perform run-time checks to verify that addresses
 * are properly zoned (see ip6_zone.h on what that means) where it matters.
 * Enabling this setting is highly recommended when upgrading from an existing
 * installation that is not yet scope-aware; otherwise it may be too expensive.
 */
#if !defined LWIP_IPV6_SCOPES_DEBUG || defined __DOXYGEN__
#define LWIP_IPV6_SCOPES_DEBUG          0
#endif

/**
 * Defines the number of IPv6 addresses per netif.
 */
#if !defined LWIP_IPV6_NUM_ADDRESSES || defined __DOXYGEN__
#define LWIP_IPV6_NUM_ADDRESSES         5
#endif

/**
 * LWIP_IPV6_FORWARD==1: Forwards IPv6 packets across netifs.
 */
#if !defined LWIP_IPV6_FORWARD || defined __DOXYGEN__
#define LWIP_IPV6_FORWARD               1
#endif

/**
 * LWIP_IPV6_FRAG==1: Fragments outgoing IPv6 packets that are too big.
 */
#if !defined LWIP_IPV6_FRAG || defined __DOXYGEN__
#define LWIP_IPV6_FRAG                  1
#endif

/**
 * LWIP_IPV6_REASS==1: Reassembles incoming IPv6 packets that fragmented.
 */
#if !defined LWIP_IPV6_REASS || defined __DOXYGEN__
#define LWIP_IPV6_REASS                 (LWIP_IPV6)
#endif

/**
 * LWIP_IPV6_SEND_ROUTER_SOLICIT==1: Sends router solicitation messages during
 * network startup.
 */
#if !defined LWIP_IPV6_SEND_ROUTER_SOLICIT || defined __DOXYGEN__
#define LWIP_IPV6_SEND_ROUTER_SOLICIT   1
#endif

/**
 * LWIP_IPV6_AUTOCONFIG==1: Enables stateless address autoconfiguration as per RFC 4862.
 */
#if !defined LWIP_IPV6_AUTOCONFIG || defined __DOXYGEN__
#define LWIP_IPV6_AUTOCONFIG            (LWIP_IPV6)
#endif

#if !defined LWIP_IPV6_AUTOCONFIG_DEFAULT || defined __DOXYGEN__
#define LWIP_IPV6_AUTOCONFIG_DEFAULT          0
#endif

/**
 * LWIP_IPV6_ADDRESS_LIFETIMES==1: Keep valid and preferred lifetimes for each
 * IPv6 address. Required for LWIP_IPV6_AUTOCONFIG. May still be enabled
 * otherwise, in which case the application may assign address lifetimes with
 * the appropriate macros. Addresses with no lifetime are assumed to be static.
 * If this option is disabled, all addresses are assumed to be static.
 */
#if !defined LWIP_IPV6_ADDRESS_LIFETIMES || defined __DOXYGEN__
#define LWIP_IPV6_ADDRESS_LIFETIMES     LWIP_IPV6_AUTOCONFIG
#endif

/**
 * LWIP_IPV6_DUP_DETECT_ATTEMPTS=[0..7]: Defines the number of duplicate address detection attempts.
 */
#if !defined LWIP_IPV6_DUP_DETECT_ATTEMPTS || defined __DOXYGEN__
#define LWIP_IPV6_DUP_DETECT_ATTEMPTS   1
#endif

/**
 * LWIP_ADDR_EXPIRATION_ALLOWED==1: Allwos address expiration in neighbour discovery.
 */
#if !defined  LWIP_ADDR_EXPIRATION_ALLOWED || defined __DOXYGEN__
#define LWIP_ADDR_EXPIRATION_ALLOWED  1
#endif

/**
 * @}
 */

/*
 * @defgroup lwip_opts_icmp6 ICMP6
 * @ingroup lwip_opts_ipv6
 * @{
 */
/**
 * LWIP_ICMP6==1: Enables ICMPv6 (mandatory per RFC)
 */
#if !defined LWIP_ICMP6 || defined __DOXYGEN__
#define LWIP_ICMP6                      (LWIP_IPV6)
#endif

/**
 * Defines the bytes from original packet to send back in
 * ICMPv6 error messages.
 */
#if !defined LWIP_ICMP6_DATASIZE || defined __DOXYGEN__
#define LWIP_ICMP6_DATASIZE             8
#endif

/**
 * Defines the default hop limit for ICMPv6 messages.
 */
#if !defined LWIP_ICMP6_HL || defined __DOXYGEN__
#define LWIP_ICMP6_HL                   255
#endif
/**
 * @}
 */

/*
 * @defgroup lwip_opts_mld6 Multicast listener discovery
 * @ingroup lwip_opts_ipv6
 * @{
 */
/**
 * LWIP_IPV6_MLD==1: Enables multicast listener discovery protocol.
 * If LWIP_IPV6 is enabled, but this setting is disabled, the MAC layer must
 * indiscriminately pass all inbound IPv6 multicast traffic to lwIP.
 */
#if !defined LWIP_IPV6_MLD || defined __DOXYGEN__
#define LWIP_IPV6_MLD                     0
#endif
#if !LWIP_IPV6
#undef LWIP_IPV6_MLD
#define LWIP_IPV6_MLD                     0
#endif

/**
 * LWIP_MLD6_ENABLE_MLD_ON_DAD==1:Enables sending MLD REPORT OR DONE for solicited node
 address when state changes during neighbour discovery.
 */
#if !defined LWIP_MLD6_ENABLE_MLD_ON_DAD || defined __DOXYGEN__
#define LWIP_MLD6_ENABLE_MLD_ON_DAD       0
#endif
#if !LWIP_IPV6_MLD
#undef LWIP_MLD6_ENABLE_MLD_ON_DAD
#define LWIP_MLD6_ENABLE_MLD_ON_DAD       0
#endif

/**
 * LWIP_MLD6_DONE_ONLYFOR_LAST_REPORTER==1:Enables sending MLD DONE only if the group
 is the last listener on the interface for a specific multicast address. If group is not the last reporter
 Done message will not be sent. By disabling the configuration, stack will send Done irrespective of the
 last reporter flag.
RFC 2710 If the node's most   recent Report message was suppressed by hearing another Report
message, it MAY send nothing, as it is highly likely that there is   another listener
for that address still present on the same link.  If   this optimization is implemented
, it MUST be able to be turned off   but SHOULD default to on. */
#if !defined LWIP_MLD6_DONE_ONLYFOR_LAST_REPORTER || defined __DOXYGEN__
#define LWIP_MLD6_DONE_ONLYFOR_LAST_REPORTER    LWIP_IPV6 && LWIP_IPV6_MLD
#endif

/**
 * MEMP_NUM_MLD6_GROUP: Defines the maximum number of IPv6 multicast groups that can be joined.
 * There must be enough groups so that each netif can join the solicited-node
 * multicast group for each of its local addresses, plus one for MDNS if
 * applicable, plus any number of groups to be joined on UDP sockets.
 */
#if !defined MEMP_NUM_MLD6_GROUP || defined __DOXYGEN__
#define MEMP_NUM_MLD6_GROUP         4
#endif

/** LWIP_NETIF_IFINDEX_MAX_EX : The max value allowed for netif interface index:
* Not a configurable value.
*/
/* As the ifindex variable is a uint8 value , restricting the number of index handled in the
interface identification API */
#ifndef LWIP_NETIF_IFINDEX_MAX_EX
#define LWIP_NETIF_IFINDEX_MAX_EX LWIP_NETIF_NUM_MAX
#endif

/** NETIF_NO_INDEX :The interface index 0 is an invalid index . Not a configurable value. */
#ifndef NETIF_NO_INDEX
#define NETIF_NO_INDEX              0
#endif

/* RPL Options */
#if !defined LWIP_RPL || defined __DOXYGEN__
#define LWIP_RPL   0
#endif

/**
 * @}
 */

/*
 * @defgroup lwip_opts_nd6 Neighbor discovery
 * @ingroup lwip_opts_ipv6
 * @{
 */
/**
 * LWIP_ND6_QUEUEING==1: Queues outgoing IPv6 packets while MAC address
 * is being resolved.
 */
#if !defined LWIP_ND6_QUEUEING || defined __DOXYGEN__
#define LWIP_ND6_QUEUEING               (LWIP_IPV6)
#endif

/**
 * Defines the maximum number of IPv6 packets to queue during MAC resolution.
 */
#if !defined MEMP_NUM_ND6_QUEUE || defined __DOXYGEN__
#define MEMP_NUM_ND6_QUEUE              20
#endif

/**
 * Defines the number of entries in IPv6 neighbor cache.
 */
#if !defined LWIP_ND6_NUM_NEIGHBORS || defined __DOXYGEN__
#define LWIP_ND6_NUM_NEIGHBORS          10
#endif

/**
 * Defines the number of entries in IPv6 destination cache.
 */
#if !defined LWIP_ND6_NUM_DESTINATIONS || defined __DOXYGEN__
#define LWIP_ND6_NUM_DESTINATIONS       10
#endif

/**
 * LWIP_ND6_NUM_PREFIXES: number of entries in IPv6 on-link prefixes cache
 */
#if !defined LWIP_ND6_NUM_PREFIXES || defined __DOXYGEN__
#define LWIP_ND6_NUM_PREFIXES           10
#endif

/**
 * Defines the number of entries in IPv6 default router cache.
 */
#if !defined LWIP_ND6_NUM_ROUTERS || defined __DOXYGEN__
#define LWIP_ND6_NUM_ROUTERS            3
#endif

/**
 * Defines the maximum number of multicast solicit messages to send
 * (neighbor solicit and router solicit).
 */
#if !defined LWIP_ND6_MAX_MULTICAST_SOLICIT || defined __DOXYGEN__
#define LWIP_ND6_MAX_MULTICAST_SOLICIT  3
#endif

/**
 * Defines the maximum number of unicast neighbor solicitation messages
 * to send during neighbor reachability detection.
 */
#if !defined LWIP_ND6_MAX_UNICAST_SOLICIT || defined __DOXYGEN__
#define LWIP_ND6_MAX_UNICAST_SOLICIT    3
#endif

/**
 * Unused: See ND RFC (time in milliseconds).
 */
#if !defined LWIP_ND6_MAX_ANYCAST_DELAY_TIME || defined __DOXYGEN__
#define LWIP_ND6_MAX_ANYCAST_DELAY_TIME 1000
#endif

/**
 * Unused: See ND RFC
 */
#if !defined LWIP_ND6_MAX_NEIGHBOR_ADVERTISEMENT || defined __DOXYGEN__
#define LWIP_ND6_MAX_NEIGHBOR_ADVERTISEMENT  3
#endif

/**
 * Defines the default neighbor reachable time in milliseconds.
 * May be updated by router advertisement messages.
 */
#if !defined LWIP_ND6_REACHABLE_TIME || defined __DOXYGEN__
#define LWIP_ND6_REACHABLE_TIME         30000
#endif

/**
 * Defines the default retransmission timer for solicitation messages.
 */
#if !defined LWIP_ND6_RETRANS_TIMER || defined __DOXYGEN__
#define LWIP_ND6_RETRANS_TIMER          1000
#endif

/**
 * Defines the delay before first unicast neighbor solicitation
 * message is sent, during neighbor reachability detection.
 */
#if !defined LWIP_ND6_DELAY_FIRST_PROBE_TIME || defined __DOXYGEN__
#define LWIP_ND6_DELAY_FIRST_PROBE_TIME 5000
#endif

/**
 * LWIP_ND6_ALLOW_RA_UPDATES==1: Allows Router Advertisement messages to update
 * Reachable time and retransmission timers, and netif MTU.
 */
#if !defined LWIP_ND6_ALLOW_RA_UPDATES || defined __DOXYGEN__
#define LWIP_ND6_ALLOW_RA_UPDATES       1
#endif

/**
 * LWIP_ND6_TCP_REACHABILITY_HINTS==1: Allows TCP to provide Neighbor Discovery
 * with reachability hints for connected destinations. This helps avoid sending
 * unicast neighbor solicitation messages.
 */
#if !defined LWIP_ND6_TCP_REACHABILITY_HINTS || defined __DOXYGEN__
#define LWIP_ND6_TCP_REACHABILITY_HINTS 1
#endif

/**
 * LWIP_ND6_RDNSS_MAX_DNS_SERVERS > 0: Uses IPv6 Router Advertisement Recursive
 * DNS Server Option (as per RFC 6106) to copy a defined maximum number of DNS
 * servers to the DNS module.
 */
#if !defined LWIP_ND6_RDNSS_MAX_DNS_SERVERS || defined __DOXYGEN__
#define LWIP_ND6_RDNSS_MAX_DNS_SERVERS  0
#endif

/* Configurations related to neighbor restriction */
#ifndef LWIP_NBRPOLICY_ENABLE_NBR_RESTRICTION
#define LWIP_NBRPOLICY_ENABLE_NBR_RESTRICTION 0
#endif

#if LWIP_NBRPOLICY_ENABLE_NBR_RESTRICTION

#ifndef LWIP_NBRPOLICY_DCHILD_PERCENT
#define LWIP_NBRPOLICY_DCHILD_PERCENT  60
#endif

#ifndef LWIP_NBRPOLICY_PARENT_PERCENT
#define LWIP_NBRPOLICY_PARENT_PERCENT  20
#endif

#ifndef LWIP_NBRPOLICY_DCHILD_MAX_NUM
#define LWIP_NBRPOLICY_DCHILD_MAX_NUM \
  (((LWIP_ND6_NUM_NEIGHBORS) * (LWIP_NBRPOLICY_DCHILD_PERCENT)) / 100)
#endif

#ifndef LWIP_NBRPOLICY_PARENT_MAX_NUM
#define LWIP_NBRPOLICY_PARENT_MAX_NUM \
  (((LWIP_ND6_NUM_NEIGHBORS) * (LWIP_NBRPOLICY_PARENT_PERCENT)) / 100)
#endif

#if (LWIP_NBRPOLICY_PARENT_MAX_NUM == 0) || (LWIP_NBRPOLICY_DCHILD_MAX_NUM == 0)
#error "Neither number of parent nor direct child can be zero"
#endif

#endif

/**
 * @}
 */

/*
 * @defgroup lwip_opts_dhcpv6 DHCPv6
 * @ingroup lwip_opts_ipv6
 * @{
 */
/**
 * LWIP_IPV6_DHCP6==1: enable DHCPv6 stateful/stateless address autoconfiguration.
 *                     LWIP_ND6_RDNSS_MAX_DNS_SERVERS should be 0
 */
#if !defined LWIP_IPV6_DHCP6 || defined __DOXYGEN__
#define LWIP_IPV6_DHCP6                 1
#endif

/**
 * LWIP_IPV6_DHCP6_STATEFUL==1: enable DHCPv6 stateful address autoconfiguration.
 * (not supported, yet!)
 */
#if !defined LWIP_IPV6_DHCP6_STATEFUL || defined __DOXYGEN__
#define LWIP_IPV6_DHCP6_STATEFUL        1
#endif

/**
 * LWIP_IPV6_DHCP6_STATELESS==1: enable DHCPv6 stateless address autoconfiguration.
 */
#if !defined LWIP_IPV6_DHCP6_STATELESS || defined __DOXYGEN__
#define LWIP_IPV6_DHCP6_STATELESS       LWIP_IPV6_DHCP6
#endif

/**
 * LWIP_DHCP6_GETS_NTP==1: Request NTP servers via DHCPv6. For each
 * response packet, a callback is called, which has to be provided by the port:
 * void dhcp6_set_ntp_servers(u8_t num_ntp_servers, ip_addr_t* ntp_server_addrs);
*/
#if !defined LWIP_DHCP6_GET_NTP_SRV || defined __DOXYGEN__
#define LWIP_DHCP6_GET_NTP_SRV          0
#endif

/**
 * The maximum of NTP servers requested
 */
#if !defined LWIP_DHCP6_MAX_NTP_SERVERS || defined __DOXYGEN__
#define LWIP_DHCP6_MAX_NTP_SERVERS      1
#endif

/**
 * LWIP_DHCP6_MAX_DNS_SERVERS > 0: Request DNS servers via DHCPv6.
 * DNS servers received in the response are passed to DNS via @ref dns_setserver()
 * (up to the maximum limit defined here).
 */
#if !defined LWIP_DHCP6_MAX_DNS_SERVERS || defined __DOXYGEN__
#define LWIP_DHCP6_MAX_DNS_SERVERS      DNS_MAX_SERVERS
#endif

/*
 * @defgroup lwip_icmp6_rate_limit
 * @ingroup lwip_icmp6_rate_limit
 * @{
 */
/**
 * LWIP_ICMP6_ERR==1: option to use rate limit feature  or not
 */
#if !defined LWIP_ICMP6_ERR_RT_LMT || defined __DOXYGEN__
#define LWIP_ICMP6_ERR_RT_LMT              1
#endif

/**
 * Defines the maximum number of Icmp6 error buckets to check the average rate.
 * bucket size need to be power of 2. Eg. Correct  values will be 2,4,8,16,32...
 */
#if !defined ICMP6_ERR_BKT_SIZE || defined __DOXYGEN__
#define ICMP6_ERR_BKT_SIZE                2
#endif

/**
 * Defines the max average/threshold rate at which the data can be recieved.
 */
#if !defined ICMP6_ERR_THRESHOLD_LEVEL || defined __DOXYGEN__
#define ICMP6_ERR_THRESHOLD_LEVEL         5
#endif

/**
 * Enables the addition and deletion operation for static perfixes.
 */
#if !defined LWIP_ND6_STATIC_PREFIX || defined __DOXYGEN__
#define LWIP_ND6_STATIC_PREFIX 0
#endif

/**
 * Enables the addition and deletion operation for static default routes.
 */
#if !defined LWIP_ND6_STATIC_DEFAULT_ROUTE || defined __DOXYGEN__
#define LWIP_ND6_STATIC_DEFAULT_ROUTE 0
#endif

/**
 * Enables the static neighbor entry support These entries can't be replaced.
 */
#if !defined LWIP_ND6_STATIC_NBR || defined __DOXYGEN__
#define LWIP_ND6_STATIC_NBR        1
#endif

#if !defined LWIP_USE_LQI_FOR_LINK_METRIC || defined __DOXYGEN__
#define LWIP_USE_LQI_FOR_LINK_METRIC      0
#endif

#if !defined LWIP_USE_RSSI_FOR_LINK_METRIC || defined __DOXYGEN__
#define LWIP_USE_RSSI_FOR_LINK_METRIC     1
#endif

#ifndef LWIP_DHCP_COAP_RELAY
#define LWIP_DHCP_COAP_RELAY    0
#endif

#ifndef LWIP_ND6_ROUTER
#define LWIP_ND6_ROUTER    0
#endif

#ifndef LWIP_ND6_DESTINATIONS_OLDTIME
#define LWIP_ND6_DESTINATIONS_OLDTIME    0
#endif

#ifndef LWIP_RPL_RS_DAO
#define LWIP_RPL_RS_DAO    0
#endif

#ifndef LWIP_NA_PROXY
#define LWIP_NA_PROXY    0
#endif

#ifndef LWIP_NA_PROXY_UNSOLICITED
#define LWIP_NA_PROXY_UNSOLICITED    1
#endif

/**
 * our nat64 module depends on rpl
 */
#if LWIP_RPL == 0 && LWIP_RIPPLE == 0
#if defined(LWIP_NAT64) && (LWIP_NAT64 != 0)
#undef LWIP_NAT64
#define LWIP_NAT64 0
#endif
#endif

#ifndef LWIP_NAT64_MIN_SUBSTITUTE
#define LWIP_NAT64_MIN_SUBSTITUTE 0
#endif

/*
   ---------------------------------------
   ---------- Hook options ---------------
   ---------------------------------------
*/

/*
 * @defgroup lwip_opts_hooks Hooks
 * @ingroup lwip_opts_infrastructure
 * Hooks are undefined by default. Define them to a function if you need them.
 * @{
 */

/**
 * LWIP_HOOK_FILENAME: Custom filename to #include in files that provide hooks.
 * Declare your hook function prototypes in this file. You may also #include all headers
 * providing data types that are need in this file.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_FILENAME "path/to/my/lwip_hooks.h"
#endif

/**
 * LWIP_HOOK_TCP_ISN:
 * Defines the hook for generation of the Initial Sequence Number (ISN) for a new TCP
 * connection. The default lwIP ISN generation algorithm is very basic and may
 * allow for TCP spoofing attacks. This hook provides the means to implement
 * the standardized ISN generation algorithm from RFC 6528 (see contrib/adons/tcp_isn),
 * or any other desired algorithm as a replacement.
 * Called from tcp_connect() and tcp_listen_input() when an ISN is needed for
 * a new TCP connection, if TCP support (@ref LWIP_TCP) is enabled.\n
 * Signature: u32_t my_hook_tcp_isn(const ip_addr_t* local_ip,
 * u16_t local_port, const ip_addr_t* remote_ip, u16_t remote_port); \n
 * It may be necessary to use "struct ip_addr" (ip4_addr, ip6_addr) instead of "ip_addr_t" in function declarations. \n
 * Arguments:
 * - local_ip: Pointer to the local IP address of the connection
 * - local_port: Local port number of the connection (host-byte order)
 * - remote_ip: Pointer to the remote IP address of the connection
 * - remote_port: Remote port number of the connection (host-byte order)\n
 * <b>Return Value</b> \n
 * Returns the 32-bit Initial Sequence Number to use for the new TCP connection.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_TCP_ISN(local_ip, local_port, remote_ip, remote_port)
#endif

/**
 * LWIP_HOOK_TCP_INPACKET_PCB:
 * Hook for intercepting incoming packets before they are passed to a pcb. This
 * allows updating some state or even dropping a packet.
 * Signature:\code{.c}
 * err_t my_hook_tcp_inpkt(struct tcp_pcb *pcb, struct tcp_hdr *hdr, u16_t optlen, u16_t opt1len, u8_t *opt2, struct pbuf *p);
 * \endcode
 * Arguments:
 * - pcb: tcp_pcb selected for input of this packet (ATTENTION: this may be
 *        struct tcp_pcb_listen if pcb->state == LISTEN)
 * - hdr: pointer to tcp header (ATTENTION: tcp options may not be in one piece!)
 * - optlen: tcp option length
 * - opt1len: tcp option length 1st part
 * - opt2: if this is != NULL, tcp options are split among 2 pbufs. In that case,
 *         options start at right after the tcp header ('(u8_t*)(hdr + 1)') for
 *         the first 'opt1len' bytes and the rest starts at 'opt2'. opt2len can
 *         be simply calculated: 'opt2len = optlen - opt1len;'
 * - p: input packet, p->payload points to application data (that's why tcp hdr
 *      and options are passed in seperately)
 * Return value:
 * - ERR_OK: continue input of this packet as normal
 * - != ERR_OK: drop this packet for input (don't continue input processing)
 *
 * ATTENTION: don't call any tcp api functions that might change tcp state (pcb
 * state or any pcb lists) from this callback!
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_TCP_INPACKET_PCB(pcb, hdr, optlen, opt1len, opt2, p)
#endif

/**
 * LWIP_HOOK_TCP_OUT_TCPOPT_LENGTH:
 * Hook for increasing the size of the options allocated with a tcp header.
 * Together with LWIP_HOOK_TCP_OUT_ADD_TCPOPTS, this can be used to add custom
 * options to outgoing tcp segments.
 * Signature:\code{.c}
 * u8_t my_hook_tcp_out_tcpopt_length(const struct tcp_pcb *pcb, u8_t internal_option_length);
 * \endcode
 * Arguments:
 * - pcb: tcp_pcb that transmits (ATTENTION: this may be NULL or
 *        struct tcp_pcb_listen if pcb->state == LISTEN)
 * - internal_option_length: tcp option length used by the stack internally
 * Return value:
 * - a number of bytes to allocate for tcp options (internal_option_length <= ret <= 40)
 *
 * ATTENTION: don't call any tcp api functions that might change tcp state (pcb
 * state or any pcb lists) from this callback!
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_TCP_OUT_TCPOPT_LENGTH(pcb, internal_len)
#endif

/**
 * LWIP_HOOK_TCP_OUT_ADD_TCPOPTS:
 * Hook for adding custom options to outgoing tcp segments.
 * Space for these custom options has to be reserved via LWIP_HOOK_TCP_OUT_TCPOPT_LENGTH.
 * Signature:\code{.c}
 * u32_t *my_hook_tcp_out_add_tcpopts(struct pbuf *p, struct tcp_hdr *hdr, const struct tcp_pcb *pcb, u32_t *opts);
 * \endcode
 * Arguments:
 * - p: output packet, p->payload pointing to tcp header, data follows
 * - hdr: tcp header
 * - pcb: tcp_pcb that transmits (ATTENTION: this may be NULL or
 *        struct tcp_pcb_listen if pcb->state == LISTEN)
 * - opts: pointer where to add the custom options (there may already be options
 *         between the header and these)
 * Return value:
 * - pointer pointing directly after the inserted options
 *
 * ATTENTION: don't call any tcp api functions that might change tcp state (pcb
 * state or any pcb lists) from this callback!
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_TCP_OUT_ADD_TCPOPTS(p, hdr, pcb, opts)
#endif

/**
 * This is called from ip_input() (IPv4) \n
 * Arguments:
 * - pbuf: Received struct pbuf passed to ip_input()
 * - input_netif: struct netif on which the packet has been received.
 * <b>Return Value</b> \n
 * - 0: Hook has not consumed the packet. Packet is processed as normal.
 * - != 0: Hook has consumed the packet.
 * If the hook consumed the packet, the hook must free the 'pbuf'  when it is done.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP4_INPUT(pbuf, input_netif)
#endif

/**
 * This is called from ip_route() (IPv4) \n

 * Returns the destination netif or NULL if no destination netif is found. In
 * that case, ip_route() continues as normal.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP4_ROUTE()
#endif

/**
 * LWIP_HOOK_IP4_ROUTE_SRC(src, dest):
 * Source-based routing for IPv4 - called from ip_route() (IPv4)
 * Signature:
 *   struct netif *my_hook(const ip4_addr_t *src, const ip4_addr_t *dest);
 * Arguments:
 * - dest: destination IPv4 address
 * - src: local/source IPv4 address
 * Returns values:
 * - the destination netif
 * - NULL if no destination netif is found. In that case, ip_route() continues as normal.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP4_ROUTE_SRC(src, dest)
#endif


/**
 * LWIP_HOOK_IP4_CANFORWARD(src, dest):
 * Check if an IPv4 can be forwarded - called from:
 * ip4_input() -> ip4_forward() -> ip4_canforward() (IPv4)
 * - source address is available via ip4_current_src_addr()
 * - calling an output function in this context (e.g. multicast router) is allowed
 * Signature:\code{.c}
 *   int my_hook(struct pbuf *p, u32_t dest_addr_hostorder);
 * \endcode
 * Arguments:
 * - p: packet to forward
 * - dest: destination IPv4 address
 * Returns values:
 * - 1: forward
 * - 0: don't forward
 * - -1: no decision. In that case, ip4_canforward() continues as normal.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP4_CANFORWARD(src, dest)
#endif

/**
 * LWIP_HOOK_ETHARP_GET_GW(netif, dest) is called from etharp_output() (IPv4) \n
 * Arguments:
 * - netif: the netif used for sending
 * - dest: the destination IPv4 address \n
 * Returns the IPv4 address of the gateway to handle the specified destination
 * IPv4 address. If NULL is returned, the netif's default gateway is used.
 * The returned address must be directly reachable on the specified netif.
 * This function is meant to implement advanced IPv4 routing together with
 * LWIP_HOOK_IP4_ROUTE(). The actual routing/gateway table implementation is
 * not part of lwIP but can e.g. be hidden in the netif's state argument.
*/
#ifdef __DOXYGEN__
#define LWIP_HOOK_ETHARP_GET_GW(netif, dest)
#endif

/**
 * LWIP_HOOK_IP6_INPUT(pbuf, input_netif)is  called from ip6_input() (IPv6)
 * Arguments:
 * - pbuf: received struct pbuf passed to ip6_input()
 * - input_netif: struct netif on which the packet has been received \n
 * <b>Return Values</b>
 * - 0: Hook has not consumed the packet, packet is processed as normal
 * - != 0: Hook has consumed the packet. \n
 * If the hook consumed the packet, the hook must free the 'pbuf'  when it is done.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_IP6_INPUT(pbuf, input_netif)
#endif

/**
 * LWIP_HOOK_IP6_ROUTE(src, dest) is called from ip6_route() (IPv6) \n
 * Arguments:
 * - src: sourc IPv6 address
 * - dest: destination IPv6 address \n
 * Returns the destination netif or NULL if no destination netif is found. In
 * that case, ip6_route() continues as normal.
 */
#if LWIP_RPL || LWIP_RIPPLE
#define LWIP_HOOK_IP6_ROUTE(src, dest) lwip_rpl_route_netif_lookup(src, dest)
#else
#define LWIP_HOOK_IP6_ROUTE(src, dest)
#endif

/**
 * LWIP_HOOK_ND6_GET_GW(netif, dest) is called from nd6_get_next_hop_entry() (IPv6)
 * Arguments:
 * - netif: The netif used for sending
 * - dest: The destination IPv6 address
 * Returns the IPv6 address of the next hop to handle the specified destination
 * IPv6 address. If NULL is returned, a NDP-discovered router is used instead.
 * The returned address MUST be directly reachable on the specified netif.
 * This function is meant to implement advanced IPv6 routing together with
 * LWIP_HOOK_IP6_ROUTE(). The actual routing/gateway table implementation is
 * not part of lwIP but can be hidden in the netif's state argument.
*/
#if LWIP_RPL || LWIP_RIPPLE
#define LWIP_HOOK_ND6_GET_GW(netif, dest)  lwip_rpl_route_nexthop_lookup(netif, dest)
#else
#define LWIP_HOOK_ND6_GET_GW(netif, dest)
#endif

/**
 * LWIP_HOOK_VLAN_CHECK(netif, eth_hdr, vlan_hdr) is called from ethernet_input() if VLAN support is enabled
 * Arguments:
 * - netif: struct netif on which the packet has been received
 * - eth_hdr: struct eth_hdr of the packet
 * - vlan_hdr: struct eth_vlan_hdr of the packet
 * <b>Return Values</b> \n
 * - 0: Packet must be dropped.
 * - != 0: Packet must be accepted.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_VLAN_CHECK(netif, eth_hdr, vlan_hdr)
#endif

/**
 * LWIP_HOOK_VLAN_SET:
 * Hook can be used to set prio_vid field of vlan_hdr. If you need to store data
 * on per-netif basis to implement this callback, see @ref netif_cd.
 * Called from ethernet_output() if VLAN support (@ref ETHARP_SUPPORT_VLAN) is enabled.\n
 * Signature: s32_t my_hook_vlan_set(struct netif* netif, struct pbuf* pbuf, const struct eth_addr* src,
 const struct eth_addr* dst, u16_t eth_type);\n
 * Arguments:
 * - netif: struct netif that the packet will be sent through
 * - p: struct pbuf packet to be sent
 * - src: source eth address
 * - dst: destination eth address
 * - eth_type: ethernet type to packet to be sent\n
 *
 *
 * Return values:
 * - &lt;0: Packet shall not contain VLAN header.
 * - 0 &lt;= return value &lt;= 0xFFFF: Packet shall contain VLAN header. Return value is prio_vid in host byte order.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_VLAN_SET(netif, p, src, dst, eth_type)
#endif

/**
 * LWIP_HOOK_MEMP_AVAILABLE(memp_t_type):
 * - called from memp_free() when a memp pool was empty and an item is now available
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_MEMP_AVAILABLE(memp_t_type)
#endif

/**
 * LWIP_HOOK_UNKNOWN_ETH_PROTOCOL(pbuf, netif):
 * Called from ethernet_input() when an unknown eth type is encountered.
 * Returns ERR_OK if packet is accepted, any error code otherwise.
 * The payload points to ethernet header.
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_UNKNOWN_ETH_PROTOCOL(pbuf, netif)
#endif

/**
 * LWIP_HOOK_DHCP6_APPEND_OPTIONS(netif, dhcp6, state, msg, msg_type, options_len_ptr, max_len):
 * Called from various dhcp6 functions when sending a DHCP6 message.
 * This hook is called just before the DHCP6 message is sent, so the
 * options are at the end of a DHCP6 message.
 * Signature:\code{.c}
 *   void my_hook(struct netif *netif, struct dhcp6 *dhcp, u8_t state, struct dhcp6_msg *msg,
 *                u8_t msg_type, u16_t *options_len_ptr);
 * \endcode
 * Arguments:
 * - netif: struct netif that the packet will be sent through
 * - dhcp6: struct dhcp6 on that netif
 * - state: current dhcp6 state (dhcp6_state_enum_t as an u8_t)
 * - msg: struct dhcp6_msg that will be sent
 * - msg_type: dhcp6 message type to be sent (u8_t)
 * - options_len_ptr: pointer to the current length of options in the dhcp6_msg "msg"
 *                    (must be increased when options are added!)
 *
 * Options need to appended like this:
 *   u8_t *options = (u8_t *)(msg + 1);
 *   LWIP_ASSERT("dhcp option overflow", sizeof(struct dhcp6_msg) + *options_len_ptr + newoptlen <= max_len);
 *   options[(*options_len_ptr)++] = &lt;option_data&gt;;
 *   [...]
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_DHCP6_APPEND_OPTIONS(netif, dhcp6, state, msg, msg_type, options_len_ptr, max_len)
#endif

/**
 * LWIP_HOOK_SOCKETS_SETSOCKOPT(s, sock, level, optname, optval, optlen, err)
 * Called from socket API to implement setsockopt() for options not provided by lwIP.
 * Core lock is held when this hook is called.
 * Signature:\code{.c}
 *   int my_hook(int s, struct lwip_sock *sock, int level, int optname, const void *optval, socklen_t optlen, int *err)
 * \endcode
 * Arguments:
 * - s: socket file descriptor
 * - sock: internal socket descriptor (see lwip/priv/sockets_priv.h)
 * - level: protocol level at which the option resides
 * - optname: option to set
 * - optval: value to set
 * - optlen: size of optval
 * - err: output error
 * Return values:
 * - 0: Hook has not consumed the option, code continues as normal (to internal options)
 * - != 0: Hook has consumed the option, 'err' is returned
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_SOCKETS_SETSOCKOPT(s, sock, level, optname, optval, optlen, err)
#endif

/**
 * LWIP_HOOK_SOCKETS_GETSOCKOPT(s, sock, level, optname, optval, optlen, err)
 * Called from socket API to implement getsockopt() for options not provided by lwIP.
 * Core lock is held when this hook is called.
 * Signature:\code{.c}
 *   int my_hook(int s, struct lwip_sock *sock, int level, int optname, void *optval, socklen_t *optlen, int *err)
 * \endcode
 * Arguments:
 * - s: socket file descriptor
 * - sock: internal socket descriptor (see lwip/priv/sockets_priv.h)
 * - level: protocol level at which the option resides
 * - optname: option to get
 * - optval: value to get
 * - optlen: size of optval
 * - err: output error
 * Return values:
 * - 0: Hook has not consumed the option, code continues as normal (to internal options)
 * - != 0: Hook has consumed the option, 'err' is returned
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_SOCKETS_GETSOCKOPT(s, sock, level, optname, optval, optlen, err)
#endif

/**
 * LWIP_HOOK_NETCONN_EXTERNAL_RESOLVE(name, addr, addrtype, err)
 * Called from netconn APIs (not usable with callback apps) allowing an
 * external DNS resolver (which uses sequential API) to handle the query.
 * Signature:\code{.c}
 *   int my_hook(const char *name, ip_addr_t *addr, u8_t addrtype, err_t *err)
 * \endcode
 * Arguments:
 * - name: hostname to resolve
 * - addr: output host address
 * - addrtype: type of address to query
 * - err: output error
 * Return values:
 * - 0: Hook has not consumed hostname query, query continues into DNS module
 * - != 0: Hook has consumed the query
 *
 * err must also be checked to determine if the hook consumed the query, but
 * the query failed
 */
#ifdef __DOXYGEN__
#define LWIP_HOOK_NETCONN_EXTERNAL_RESOLVE(name, addr, addrtype, err)
#endif
/**
 * @}
 */

/*
   ---------------------------------------
   ---------- Debugging options ----------
   ---------------------------------------
*/
/*
 * @defgroup lwip_opts_debugmsg Debug messages
 * @ingroup lwip_opts_debug
 * @{
 */
/**
 * LWIP_DBG_MIN_LEVEL: After masking, the value of the debug is
 * compared against this value. If it is smaller, then debugging
 * messages are written.
 * @see debugging_levels
 */
#if !defined LWIP_DBG_MIN_LEVEL || defined __DOXYGEN__
#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_ALL
#endif

/**
 * Defines a mask that can be used to globally enable/disable
 * debug messages of certain types.
 * @see debugging_levels
 */
#if !defined LWIP_DBG_TYPES_ON || defined __DOXYGEN__
#define LWIP_DBG_TYPES_ON               LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in etharp.c.
 */
#if !defined ETHARP_DEBUG || defined __DOXYGEN__
#define ETHARP_DEBUG                    LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in netif.c.
 */
#if !defined NETIF_DEBUG || defined __DOXYGEN__
#define NETIF_DEBUG                     LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in pbuf.c.
 */
#if !defined PBUF_DEBUG || defined __DOXYGEN__
#define PBUF_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in api_lib.c.
 */
#if !defined API_LIB_DEBUG || defined __DOXYGEN__
#define API_LIB_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in api_msg.c.
 */
#if !defined API_MSG_DEBUG || defined __DOXYGEN__
#define API_MSG_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in sockets.c.
 */
#if !defined SOCKETS_DEBUG || defined __DOXYGEN__
#define SOCKETS_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in icmp.c.
 */
#if !defined ICMP_DEBUG || defined __DOXYGEN__
#define ICMP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in igmp.c.
 */
#if !defined IGMP_DEBUG || defined __DOXYGEN__
#define IGMP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in inet.c.
 */
#if !defined INET_DEBUG || defined __DOXYGEN__
#define INET_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for IP.
 */
#if !defined IP_DEBUG || defined __DOXYGEN__
#define IP_DEBUG                        LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for driver module.
 */
#ifndef DRIVERIF_DEBUG
#define DRIVERIF_DEBUG                  LWIP_DBG_OFF
#endif
/**
 * Defines whether to enable debugging in ip_frag.c for both frag & reass.
 */
#if !defined IP_REASS_DEBUG || defined __DOXYGEN__
#define IP_REASS_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in raw.c.
 */
#if !defined RAW_DEBUG || defined __DOXYGEN__
#define RAW_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in mem.c.
 */
#if !defined MEM_DEBUG || defined __DOXYGEN__
#define MEM_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in memp.c.
 */
#if !defined MEMP_DEBUG || defined __DOXYGEN__
#define MEMP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * SYS_DEBUG: Enable debugging in sys.c.
 */
#if !defined SYS_DEBUG || defined __DOXYGEN__
#define SYS_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in timers.c.
 */
#if !defined TIMERS_DEBUG || defined __DOXYGEN__
#define TIMERS_DEBUG                    LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for TCP.
 */
#if !defined TCP_DEBUG || defined __DOXYGEN__
#define TCP_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * TCP_ERR_DEBUG: Enables debugging for TCP.
 */
#if !defined TCP_ERR_DEBUG || defined __DOXYGEN__
#define TCP_ERR_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * TCP_INPUT_DEBUG: Enables debugging in tcp_in.c for incoming debug.
 */
#if !defined TCP_INPUT_DEBUG || defined __DOXYGEN__
#define TCP_INPUT_DEBUG                 LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in tcp_in.c for fast retransmit.
 */
#if !defined TCP_FR_DEBUG || defined __DOXYGEN__
#define TCP_FR_DEBUG                    LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in TCP for retransmit
 * timeout.
 */
#if !defined TCP_RTO_DEBUG || defined __DOXYGEN__
#define TCP_RTO_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for TCP congestion window.
 */
#if !defined TCP_CWND_DEBUG || defined __DOXYGEN__
#define TCP_CWND_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in tcp_in.c for window updating.
 */
#if !defined TCP_WND_DEBUG || defined __DOXYGEN__
#define TCP_WND_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * TCP_OUTPUT_DEBUG: Enable debugging in tcp_out.c output functions.
 */
#if !defined TCP_OUTPUT_DEBUG || defined __DOXYGEN__
#define TCP_OUTPUT_DEBUG                LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for TCP with the RST message.
 */
#if !defined TCP_RST_DEBUG || defined __DOXYGEN__
#define TCP_RST_DEBUG                   LWIP_DBG_OFF
#endif

/**
* Defines whether to enable debugging for TCP queue lengths.
 */
#if !defined TCP_QLEN_DEBUG || defined __DOXYGEN__
#define TCP_QLEN_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for TCP Selective ACK (SACK)
 */
#if !defined TCP_SACK_DEBUG || defined __DOXYGEN__
#define TCP_SACK_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for TCP Tail Loss Probe(TLP)
 */
#if !defined TCP_TLP_DEBUG || defined __DOXYGEN__
#define TCP_TLP_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in UDP.
 */
#if !defined UDP_DEBUG || defined __DOXYGEN__
#define UDP_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in tcpip.c.
 */
#if !defined TCPIP_DEBUG || defined __DOXYGEN__
#define TCPIP_DEBUG                     LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in tcpip.c.
 */
#if !defined L3_EVENT_MSG_DEBUG || defined __DOXYGEN__
#define L3_EVENT_MSG_DEBUG                     LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in slipif.c.
 */
#if !defined SLIP_DEBUG || defined __DOXYGEN__
#define SLIP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in dhcp.c.
 */
#if !defined DHCP_DEBUG || defined __DOXYGEN__
#define DHCP_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging in autoip.c.
 */
#if !defined AUTOIP_DEBUG || defined __DOXYGEN__
#define AUTOIP_DEBUG                    LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for DNS.
 */
#if !defined DNS_DEBUG || defined __DOXYGEN__
#define DNS_DEBUG                       LWIP_DBG_OFF
#endif

/**
* Defines whether to enable debugging for DNS.
 */
#ifndef TFTP_DEBUG
#define TFTP_DEBUG                       LWIP_DBG_OFF
#endif

/** * Defines whether to enable debugging for DNS. */
#ifndef SYS_ARCH_DEBUG
#define SYS_ARCH_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for SNTP.
 */
#ifndef SNTP_DEBUG
#define SNTP_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * Defines whether to enabledebugging for IPv6.
 */
#if !defined IP6_DEBUG || defined __DOXYGEN__
#define IP6_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * DHCP6_DEBUG: Enable debugging in dhcp6.c.
 */
#if !defined DHCP6_DEBUG || defined __DOXYGEN__
#define DHCP6_DEBUG                     LWIP_DBG_OFF
#endif

/**
 * Defines whether to enabledebugging for IPv6.
 */
#if !defined RPL_DEBUG || defined __DOXYGEN__
#define RPL_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * Defines whether to enabledebugging for RPL Adaptor module.
 */
#if !defined RPLADPT_DEBUG || defined __DOXYGEN__
#define RPLADPT_DEBUG               LWIP_DBG_OFF
#endif

/**
 * Defines whether to enabledebugging for MLD6 module.
 */
#if !defined MLD6_DEBUG || defined __DOXYGEN__
#define MLD6_DEBUG               LWIP_DBG_OFF
#endif

/**
 * @}
 */

/**
 * LWIP_TESTMODE: Changes to make unit test possible
 */
#if !defined LWIP_TESTMODE
#define LWIP_TESTMODE                   0
#endif

/**
 * Defines whether to enable debugging for  Driver Status
 */
#ifndef DRV_STS_DEBUG
#define DRV_STS_DEBUG           LWIP_DBG_OFF
#endif

/**
 * Defines whether to enable debugging for NAT64.
 */
#if !defined NAT64_DEBUG || defined __DOXYGEN__
#define NAT64_DEBUG                       LWIP_DBG_OFF
#endif

/*
   --------------------------------------------------
   ---------- Performance tracking options ----------
   --------------------------------------------------
*/
/*
 * @defgroup lwip_opts_perf Performance
 * @ingroup lwip_opts_debug
 * @{
 */
/**
 * Defines whether to enable performance testing for lwIP.
 * If enabled, arch/perf.h is included.
 */
#if !defined LWIP_PERF || defined __DOXYGEN__
#define LWIP_PERF                       0
#endif
#include "arch/perf.h"
/**
 * @}
 */

/**
 * Defines the mailbox size for the tcpip thread messages
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when tcpip_init is called.
 */
#ifndef TCPIP_MBOX_SIZE
#if LWIP_NETIF_PROMISC
#define TCPIP_MBOX_SIZE                 512
#else
#define TCPIP_MBOX_SIZE                 320
#endif
#endif

#ifndef TCPIP_PRTY_MBOX_SIZE
#define TCPIP_PRTY_MBOX_SIZE 16
#endif

#ifndef PBUF_LINK_CHKSUM_LEN
#define PBUF_LINK_CHKSUM_LEN  0
#endif

#ifndef LWIP_SACK_PERF_OPT
#if LWIP_SACK
#define LWIP_SACK_PERF_OPT 0
#else
#define LWIP_SACK_PERF_OPT 0
#endif
#endif /* LWIP_SACK_PERF_OPT */

#ifndef LWIP_SACK_CWND_OPT
#define LWIP_SACK_CWND_OPT LWIP_SACK_PERF_OPT
#endif

/**
 * PBUF_API  macro must be enabled by the application in case the pbuf APIs are directly used by
 * the application code. This macro enables NULL validations and can have a performance impact.
 */
#ifndef PBUF_API
#define PBUF_API 0 // add in opt.h
#endif

/**
 * enable LWIP_LOWPOWER macro to use lowpower function
 */
#undef LWIP_LOWPOWER
#if LWIP_TIMERS && !LWIP_TIMERS_CUSTOM
#if defined (CONFIG_LWIP_LOWPOWER)
#define LWIP_LOWPOWER 1
#else
#define LWIP_LOWPOWER 0
#endif
#else
#define LWIP_LOWPOWER 0
#endif

#if LWIP_LOWPOWER

#ifndef LOWPOWER_DBG
#define LOWPOWER_DBG     0
#endif

#if LOWPOWER_DBG
#define LOWPOWER_DEBUG(msg) printf msg
#else
#define LOWPOWER_DEBUG(msg)
#endif

#ifndef MEMP_NUM_TCPIP_MSG_LOWPOWER
#define MEMP_NUM_TCPIP_MSG_LOWPOWER 10
#endif

#if LWIP_SNTP
#define LWIP_NSTP_TIMER    2
#else
#define LWIP_NSTP_TIMER    0
#endif

#define LOWPOWER_TCP_TIMER 1

#define MEMP_NUM_SYS_TIMEOUT_LOW (MEMP_NUM_SYS_TIMEOUT + LWIP_NSTP_TIMER + LOWPOWER_TCP_TIMER)
#endif /* LWIP_LOWPOWER */

#ifndef LWIP_L3_EVENT_MSG
#define LWIP_L3_EVENT_MSG 0
#endif

#endif /* LWIP_HDR_OPT_H */

