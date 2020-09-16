/**
 * @file
 * lwIP Error codes
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
#ifndef LWIP_HDR_ERR_H
#define LWIP_HDR_ERR_H

#include "lwip/opt.h"
#include "lwip/arch.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

/**
 * @defgroup infrastructure_errors Error codes
 * @ingroup infrastructure
 * @{
 */

/** Define LWIP_ERR_T in cc.h if you want to use
 *  a different type for your platform (must be signed). */
#ifdef LWIP_ERR_T
typedef LWIP_ERR_T err_t;
#else /* LWIP_ERR_T */
typedef s32_t err_t;
#endif /* LWIP_ERR_T*/

/** @cond liteosdebug
* Definitions for error constants. */
typedef enum {
  /** No error, everything OK. */
  ERR_OK         = 0,
  /** Out of memory error.     */
  ERR_MEM        = -1,
  /** Buffer error.            */
  ERR_BUF        = -2,
  /** Timeout.                 */
  ERR_TIMEOUT    = -3,
  /** Routing problem.         */
  ERR_RTE        = -4,
  /** Operation in progress    */
  ERR_INPROGRESS = -5,
  /** Illegal value.           */
  ERR_VAL        = -6,
  /** Operation would block.   */
  ERR_WOULDBLOCK = -7,
  /** Address in use.          */
  ERR_USE        = -8,
  /** Already connecting.      */
  ERR_ALREADY    = -9,
  /** Conn already established. */
  ERR_ISCONN     = -10,
  /** Not connected.           */
  ERR_CONN       = -11,
  /** Low-level netif error    */
  ERR_IF         = -12,
  /** Message too long.        */
  ERR_MSGSIZE    = -13,
  /** No such device.          */
  ERR_NODEV      = -14,
  /** No such device or address. */
  ERR_NODEVADDR  = -15,
  /** socket is not connection-mode & no peer address is set */
  ERR_NODEST     = -16,
  /** Network is down           */
  ERR_NETDOWN    = -17,
  /** Address family not supported by protocol */
  ERR_AFNOSUPP   = -18,
  /** No such address */
  ERR_NOADDR = -19,
  /** Operation not supported on transport endpoint */
  ERR_OPNOTSUPP = -20,

  ERR_NETUNREACH = -21,

  /** connection request timedout */
  ERR_CONNECTIMEOUT = -22,
  /** Error pipe */
  ERR_PIPE       = -23,
  /** AF not supported */
  ERR_AFNOSUPPORT = -24,
  /** Protocol not available */
  ERR_NOPROTOOPT = -25,

  ERR_ACCESS   = -26,
  ERR_NFILE   = -27,
  ERR_RESERVE3   = -28,
  ERR_RESERVE4   = -29,
  ERR_RESERVE5   = -30,
  ERR_RESERVE6   = -31,
  ERR_FATAL_START = -32,

  /** Connection aborted.      */
  ERR_ABRT       = -33,
  /** Connection reset.        */
  ERR_RST        = -34,
  /** Connection closed.       */
  ERR_CLSD       = -35,
  /** Illegal argument.       @endcond */
  ERR_ARG        = -36,

  ERR_CONNREFUSED = -37,

  /** User can't overwrite the existing neighbor entry */
  ERR_NBR_OVERWRITEFORBIDDEN = -38,

  /** Neighbor information not found */
  ERR_NBR_NOTFOUND = -39,

  /** Default router information not found */
  ERR_DEFAULT_ROUTER_NOTFOUND = -40,

  /** IPv6 Prefix information not found */
  ERR_PREFIX_NOT_FOUND = -41,

  /** No free memory available */
  ERR_NO_FREE_ENTRY = -42,

  /** Default route entry already exists */
  ERR_DEFAULT_ROUTE_EXISTS = -43,

  /** Prefix entry already exists */
  ERR_PREFIX_EXISTS = -44,

  /** 6lowpan context infomation not found */
  ERR_LOWPAN_CTX_NOTFOUND = -45,

  /** Neighbor restriction related error code */
  ERR_NBR_NOMORE_DCHILD = -46,

  ERR_DROP_NEW_NBR = -47,

  ERR_MAX_VAL = -48
} err_enum_t;


#define ERR_IS_FATAL(e) ((e) < ERR_FATAL_START)
#ifdef LWIP_DEBUG
extern const char *lwip_strerr(err_t err);
#else
#define lwip_strerr(x) ""
#endif /* LWIP_DEBUG */


#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_HDR_ERR_H */
