/**
 * @file
 * Base TCP API definitions shared by TCP and ALTCP\n
 * See also @ref tcp_raw
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
#ifndef LWIP_HDR_TCPBASE_H
#define LWIP_HDR_TCPBASE_H

#include "lwip/opt.h"

#if LWIP_TCP /* don't build if not configured for use in lwipopts.h */

#ifdef __cplusplus
extern "C" {
#endif


#if LWIP_WND_SCALE
typedef u32_t tcpwnd_size_t;
#else
typedef u16_t tcpwnd_size_t;
#endif

/** Indicates the TCP state. */
enum tcp_state {
  CLOSED      = 0,  /**< Indicates that there is no connection. */
  /**
   * Indicates that the local end-point waits for a connection
   * request from a remote end-point. That is, a passive open was performed.
   */
  LISTEN      = 1,
  SYN_SENT    = 2, /**< SYN packet is sent. */
  SYN_RCVD    = 3,  /**< SYN packet is received. */
  /**
   * The third step of the three-way connection handshake
   * was performed. The connection is open.
   */
  ESTABLISHED = 4,
  /**
   * The first step of an active close (four-way handshake)
   * was performed. The local end-point has sent a connection termination request to the remote end-point.
   */
  FIN_WAIT_1  = 5,
  /**
   * The remote end-point has sent an acknowledgement for the previouslysent connection termination request.
   * The local end-point waits for an active connection termination request from the remote end-point.
   */
  FIN_WAIT_2  = 6,
  /**
   * The local end-point has received a connection termination request
   * and acknowledged it e.g. a passive close has been performed
   * and the local end-point needs to perform an active close
   * to leave this state.
   */
  CLOSE_WAIT  = 7,
  /**
   * The local end-point is waiting for an acknowledgement for a connection
   * termination request before going to the TIME-WAIT state.
   */
  CLOSING     = 8,
  /**
   * The local end-point has performed a passive close and has
   * initiated an active close by sending a connection termination request to the remote end-point.
   */
  LAST_ACK    = 9,
  /**
   * The local end-point waits for twice the maximum segment lifetime (MSL)
   * to pass before going to CLOSED to be sure that the remote end-point received the acknowledgement.
   */
  TIME_WAIT   = 10
};

/* Flags for "apiflags" parameter in tcp_write */
#define TCP_WRITE_FLAG_COPY 0x01
#define TCP_WRITE_FLAG_MORE 0x02

#define TCP_PRIO_MIN    1
#define TCP_PRIO_NORMAL 64
#define TCP_PRIO_MAX    127

#ifdef __cplusplus
}
#endif

#endif /* LWIP_TCP */

#endif /* LWIP_HDR_TCPBASE_H */
