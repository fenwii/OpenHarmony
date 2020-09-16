/**
 * @file
 * Functions to sync with TCPIP thread
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
#ifndef LWIP_HDR_TCPIP_H
#define LWIP_HDR_TCPIP_H

#include "lwip/opt.h"

#if !NO_SYS /* don't build if not configured for use in lwipopts.h */

#include "lwip/err.h"
#include "lwip/timeouts.h"
#include "lwip/netif.h"

#if LWIP_L3_EVENT_MSG
#include "lwip/l3event.h"
#endif

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#if LWIP_TCPIP_CORE_LOCKING
/** The global semaphore to lock the stack. */
extern sys_mutex_t lock_tcpip_core;
/** Lock lwIP core mutex (needs @ref LWIP_TCPIP_CORE_LOCKING 1) */
#define LOCK_TCPIP_CORE()     (void)sys_mutex_lock(&lock_tcpip_core)
/** Unlock lwIP core mutex (needs @ref LWIP_TCPIP_CORE_LOCKING 1) */
#define UNLOCK_TCPIP_CORE()   sys_mutex_unlock(&lock_tcpip_core)
#else /* LWIP_TCPIP_CORE_LOCKING */
#define LOCK_TCPIP_CORE()
#define UNLOCK_TCPIP_CORE()
#endif /* LWIP_TCPIP_CORE_LOCKING */

extern int tcpip_init_finish;

struct pbuf;
struct netif;

/**
 * @ingroup Tcip_interface
 * @brief
 *  This callback checks whether initialization is done.
 *
 * @param[in]    arg  Specifies the argument to pass to tcpip_init_done.
 *
 *
 * @par Return values
 *  None
 */
typedef void (*tcpip_init_done_fn)(void *arg);
/** Function prototype for functions passed to tcpip_callback() */
typedef void (*tcpip_callback_fn)(void *ctx);

/* Forward declarations */
struct tcpip_callback_msg;

/*
 * Func Name:  tcpip_init
 */
/**
 * @ingroup Tcip_interface
 * @brief
 *  This API initializes all sub modules and starts the tcpip_thread.
 *
 * @param[in]    tcpip_init_done   Specifies the function to call when the
 * tcpip_thread is running and finished initializing.
 * @param[in]    arg               Specifies the argument to pass to tcpip_init_done.
 * @par Return values
 *  None
 */
void tcpip_init(tcpip_init_done_fn tcpip_init_done, void *arg);
#if LWIP_ALLOW_SOCKET_CONFIG

/*
 * Func Name:  lwip_set_socket_num
 */
/**
 * @ingroup TCPIP_Interfaces
 *
 *
 * @brief
 *    This API is used to configure maximum number of allowed sockets in the lwIP stack.
 *
 *
 *
 * @param[in]   socketnum    Indicates the maximum number of sockets.
 *
 * @return
 *  0: On Success\n
 *  Non Zero value: On Failure
 *
 *
 * @Note
 * \n
 * Call this API before tcpip_init, or it will be failed.
 * If this API is not invoked, maximum socket number is set to DEFAULT_LWIP_NUM_SOCKETS, which is defined in
 * opt.h/lwipopts.h.
 * @par Related Topics
 * \n
 * None
 */
int lwip_set_socket_num(unsigned int socketnum);

/*
 * Func Name:  lwip_get_socket_num
 */
/**
 * @ingroup TCPIP_Interfaces
 *
 *
 * @brief
 *    This API is used to get the maximum socket num setting in lwIP.
 *
 *
 * @param[in]   void
 *
 * @return
 *  current max socket number
 *
 * @par Required Header File
 * tcpip.h
 *
 * @par Note
 * None
 */
unsigned int lwip_get_socket_num(void);
#endif /* LWIP_ALLOW_SOCKET_CONFIG */

err_t  tcpip_inpkt(struct pbuf *p, struct netif *inp, netif_input_fn input_fn);
err_t  tcpip_input(struct pbuf *p, struct netif *inp);

#if LWIP_PLC || LWIP_IEEE802154
err_t tcpip_lln_inpkt(struct netif *iface, struct pbuf *p,
                      struct  linklayer_addr *sender_mac, struct  linklayer_addr *recver_mac,
                      netif_lln_input_fn input_lln_fn);

err_t tcpip_lln_input(struct netif *iface, struct pbuf *p,
                      struct linklayer_addr *sendermac, struct linklayer_addr *recvermac);
#endif
err_t  tcpip_callback_with_block(tcpip_callback_fn function, void *ctx, u8_t block);
/**
 * @ingroup lwip_os
 * @see tcpip_callback_with_block
 */
#define tcpip_callback(f, ctx)  tcpip_callback_with_block(f, ctx, 1)

#if LWIP_API_RICH
struct tcpip_callback_msg *tcpip_callbackmsg_new(tcpip_callback_fn function, void *ctx);
void   tcpip_callbackmsg_delete(struct tcpip_callback_msg *msg);
err_t  tcpip_trycallback(struct tcpip_callback_msg *msg);

/* free pbufs or heap memory from another context without blocking */
err_t  pbuf_free_callback(struct pbuf *p);
err_t  mem_free_callback(void *m);
#endif /* LWIP_API_RICH */

#if LWIP_TCPIP_TIMEOUT && LWIP_TIMERS
err_t  tcpip_timeout(u32_t msecs, sys_timeout_handler h, void *arg);
err_t  tcpip_untimeout(sys_timeout_handler h, void *arg);
#endif /* LWIP_TCPIP_TIMEOUT && LWIP_TIMERS */

/** This structure defines TCP IP connections. */
struct tcpip_conn {
  struct eth_addr dst_mac; /**< Specifies the destination MAC. */
  ip_addr_t src_ip; /**< Specifies the source IP address. */
  ip_addr_t dst_ip; /**< Specifies the destination IP address of a TCP/UDP connection.
  If lwip_connect is not called for a UDP connection, then this field will be set to 0 for that UDP connection. */
  u16_t ipid;    /**<  Retains the same value as identification field in the IP header. */
  u16_t srcport; /**< Specifies the source port address. */
  u16_t dstport; /**< Specifies the destination port address. If connect is not called for a
  UDP connection, then this field will be set to 0 for that UDP connection. */
  u32_t tcpwin;  /**< Specifies the TCP window of the last sent TCP packet. For a UDP connection,
  this field is set to 0. */
  u32_t seqnum; /**< Specifies the TCP sequence number of the last ACKED byte of a TCP connection.
  For a UDP connection, this field is set to 0. */
  u32_t acknum;  /**< Specifies the TCP Ack number of the last sent packet in the TCP connection.
  For a UDP connection, this field is set to 0. */
  u32_t last_payload_len;    /**< Specifies the UDP/TCP payload length of the last packet sent in
  the UDP/TCP connection.  */
  u32_t tsval;   /**<  Indicates the timestamp value. This field is 0 for both TCP and UDP connections. */
  u32_t tsecr;  /**< Indicates the timestamp echo reply. This field is 0 for both TCP and UDP connections. */
};

#if LWIP_LOWPOWER
void tcpip_send_msg_na(enum lowpower_msg_type type);
#endif

#if LWIP_L3_EVENT_MSG
void tcpip_send_msg_l3_event(enum l3_event_msg_type type, void *rinfo);
#endif

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* !NO_SYS */

#endif /* LWIP_HDR_TCPIP_H */
