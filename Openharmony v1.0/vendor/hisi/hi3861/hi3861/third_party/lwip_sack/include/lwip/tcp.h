/**
 * @file
 * TCP API (to be used from TCPIP thread)\n
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
#ifndef LWIP_HDR_TCP_H
#define LWIP_HDR_TCP_H

#include "lwip/opt.h"

#if LWIP_TCP /* don't build if not configured for use in lwipopts.h */

#include "lwip/tcpbase.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/ip.h"
#include "lwip/icmp.h"
#include "lwip/err.h"
#include "lwip/ip6.h"
#include "lwip/ip6_addr.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

struct tcp_pcb;
struct tcp_pcb_listen;

/**
 * @brief Function prototype for TCP accept callback functions. Called when a new
 * connection can be accepted on a listening PCB.
 *
 * @param arg Indicates an additional argument to pass to the callback function (Refer to tcp_arg()).
 * @param newpcb Indicates the new connection PCB.
 * @param err Indicates an error code if there has been an error.
 *            This function returns ERR_ABRT if you have called tcp_abort() from within the
 *            callback function.
 */
typedef err_t (*tcp_accept_fn)(void *arg, struct tcp_pcb *newpcb, err_t err);

/** @brief Function prototype for TCP receive callback functions. Called when data has
 * been received.
 *
 * @param arg Indicates an additional argument to pass to the callback function (Refer to tcp_arg()).
 * @param tpcb Indicates the connection PCB which received data.
 * @param p Indicates the received data, or NULL when the connection has been closed.
 * @param err Indicates an error code if there is an error in receiving.
 *            This function returns ERR_ABRT if you have called tcp_abort from within the
 *            callback function.
 */
typedef err_t (*tcp_recv_fn)(void *arg, struct tcp_pcb *tpcb,
                             struct pbuf *p, err_t err);

/** @brief Function prototype for TCP sent callback functions. Called when sent data has
 * been acknowledged by the remote side. Used to free corresponding resources.
 * This also means that the PCB has now space available to send new data.
 *
 * @param arg Indicates an additional argument to pass to the callback function (Refer to tcp_arg()).
 * @param tpcb Indicates the connection PCB for which data has been acknowledged.
 * @param len Indicates the amount of bytes acknowledged.
 * @return ERR_OK: try to send some data by calling tcp_output()
 *            This function returns ERR_ABRT if you have called tcp_abort() from within the
 *            callback function.
 */
typedef err_t (*tcp_sent_fn)(void *arg, struct tcp_pcb *tpcb,
                             u16_t len);

/** @brief Function prototype for TCP poll callback functions. Called periodically as
 * specified by tcp_poll().
 *
 * @param arg Indicates an additional argument to pass to the callback function
 (Refer to tcp_arg()).
 * @param tpcb Indicates the TCP PCB.
 * @return ERR_OK: try to send some data by calling tcp_output()
 *            This function returns ERR_ABRT if you have called tcp_abort() from within the
 *            callback function.
 */
typedef err_t (*tcp_poll_fn)(void *arg, struct tcp_pcb *tpcb);

/** @brief Function prototype for TCP error callback functions. Called when the PCB
 * receives a RST or is unexpectedly closed for any other reason.
 *
 * @note The corresponding PCB is already freed when this callback is called.
 *
 * @param arg Indicates an additional argument to pass to the callback function
 (Refer to tcp_arg()).
 * @param err Provides an error code to indicate why the PCB has been closed. \n
 *            ERR_ABRT: Aborted through tcp_abort or by a TCP timer. \n
 *            ERR_RST: The connection was reset by the remote host.
 */
typedef void  (*tcp_err_fn)(void *arg, err_t err);

/** @brief Function prototype for TCP connected callback functions. Called when a PCB
 * is connected to the remote side after initiating a connection attempt by
 * calling tcp_connect().
 *
 * @param arg Indicates an additional argument to pass to the callback function
 (Refer to tcp_arg()).
 * @param tpcb Indicates the connection PCB which is connected.
 * @param err Indicates an unused error code, always ERR_OK currently.
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function
 *
 * @note When a connection attempt fails, the error callback is currently called.
 */
typedef err_t (*tcp_connected_fn)(void *arg, struct tcp_pcb *tpcb, err_t err);

#if DRIVER_STATUS_CHECK
typedef void (*tcp_event_sndplus_fn)(void *arg, struct tcp_pcb *tpcb);
#endif

#if LWIP_WND_SCALE
/** Recv Window Scaling. Announce Window Size. */
#define RCV_WND_SCALE(pcb, wnd) (((wnd) >> (pcb)->rcv_scale))
/** Send Window Scaling. Sender Window Size */
#define SND_WND_SCALE(pcb, wnd) (((tcpwnd_size_t)(wnd)  << (pcb)->snd_scale))
/** Window Scaling. Actual Window Size. */
#define ACTUAL_WND_SIZE(pcb, wnd) ((tcpwnd_size_t)((wnd) >> (pcb)->rcv_scale) << (pcb)->rcv_scale)
/** TCP Window Size. */
#define TCPWND16(x)             ((u16_t)LWIP_MIN((x), 0xFFFF))
/** TCP maximum window size. */
#define TCP_WND_MAX(pcb)        ((tcpwnd_size_t)(((pcb)->flags & TF_WND_SCALE) ? TCP_WND : TCPWND16(TCP_WND)))
#else /* LWIP_WND_SCALE */
#define RCV_WND_SCALE(pcb, wnd) (wnd)
#define SND_WND_SCALE(pcb, wnd) (wnd)
#define TCPWND16(x)             (x)
#define TCP_WND_MAX(pcb)        TCP_WND
#endif /* LWIP_WND_SCALE */

typedef u32_t tcpflags_t;

#define TCP_ALLFLAGS 0xFFFFFFFFU
#define SNDQUEUE_MAX 0xFFFF
#define SNDQUEUE_MIN 5

/* Increments a tcpwnd_size_t and holds at max value rather than rollover */
#define TCP_WND_INC(wnd, inc) do { \
  if ((tcpwnd_size_t)((wnd) + (inc)) >= (wnd)) { \
    (wnd) = (tcpwnd_size_t)((wnd) + (inc)); \
  } else { \
    (wnd) = (tcpwnd_size_t)-1; \
  } \
} while (0)

#define TCP_WND_DEC(wnd, dec, mss) do { \
  if ((wnd) >= (dec) && (wnd) >= (mss)) { \
    (wnd) = (tcpwnd_size_t)(wnd - (dec)); \
  } else { \
    (wnd) = (mss); \
  } \
} while (0)

#ifndef LWIP_INITIAL_CWND_OVERRIDE
/*
  [RFC 5681] [3.1.  Slow Start and Congestion Avoidance]
  IW, the initial value of cwnd, MUST be set using the following guidelines as an upper bound.
*/
#define LWIP_TCP_CALC_INITIAL_CWND(SMSS, IW) do { \
  if ((SMSS) > 2190) { \
    (IW) = (tcpwnd_size_t)(2 * (SMSS)); \
  } else if (((SMSS) > 1095) && ((SMSS) <= 2190)) { \
    (IW) = (tcpwnd_size_t)(3 * (SMSS)); \
  } else if ((SMSS) <= 1095) { \
    (IW) = (tcpwnd_size_t)(4 * (SMSS)); \
  } \
} while (0)
#else
#define LWIP_TCP_CALC_INITIAL_CWND(SMSS, IW) do { \
  IW = (tcpwnd_size_t)((LWIP_INITIAL_CWND_OVERRIDE) * (SMSS)); \
} while (0)
#endif

/* Increments a wnd * mss and holds at max value rather than rollover */
#define TCP_CALC_SSTHRESH(pcb, ssthresh, wnd, mss) do { \
  if (((u64_t)(wnd) * (mss))  < TCP_WND_MAX(pcb)) { \
    (ssthresh) = (tcpwnd_size_t)((wnd) * (mss)); \
  } else { \
    (ssthresh) = TCP_WND_MAX(pcb); \
  } \
} while (0)

#ifndef LWIP_CONGCNTRL_DUPACK_THRESH
/** Congestion Control duplicate Acknowledgement Threshold */
#define DUPACK_THRESH       3
#else
#define DUPACK_THRESH       LWIP_CONGCNTRL_DUPACK_THRESH
#endif

#ifndef LWIP_CONGCNTRL_INITIAL_SSTHRESH
/** Initial Congestion Control Slow Start Threshold. */
#define INITIAL_SSTHRESH       40
#else
#define INITIAL_SSTHRESH       LWIP_CONGCNTRL_INITIAL_SSTHRESH
#endif

#if DRIVER_STATUS_CHECK
#define DRV_READY         1
#define DRV_NOT_READY     0
#endif

/* Indicates that this pbuf includes a TCP FIN flag and post to mbox is failed */
#define TCP_PBUF_FLAG_TCP_FIN_RECV_SYSPOST_FAIL 0x01U

/* Adding for SACK */
#if LWIP_SACK
struct _sack_seq {
  struct _sack_seq *next;
  u32_t left;
  u32_t right;
  u32_t order;
};
#endif

#if LWIP_SACK_PERF_OPT
struct tcp_sack_fast_rxmited {
  struct tcp_sack_fast_rxmited *next;
  struct tcp_seg *seg;
};
#endif

#if LWIP_SO_SNDBUF
#define LWIP_SO_SNDBUF_DECL  tcpwnd_size_t snd_buf_static;   /* Configured send buffer size */
#else
#define LWIP_SO_SNDBUF_DECL
#endif /* LWIP_SO_SNDBUF */

/** Function prototype for deallocation of arguments. Called *just before* the
 * pcb is freed, so don't expect to be able to do anything with this pcb!
 *
 * @param id ext arg id (allocated via @ref tcp_ext_arg_alloc_id)
 * @param data pointer to the data (set via @ref tcp_ext_arg_set before)
 */
typedef void (*tcp_extarg_callback_pcb_destroyed_fn)(u8_t id, void *data);

/** Function prototype to transition arguments from a listening pcb to an accepted pcb
 *
 * @param id ext arg id (allocated via @ref tcp_ext_arg_alloc_id)
 * @param lpcb the listening pcb accepting a connection
 * @param cpcb the newly allocated connection pcb
 * @return ERR_OK if OK, any error if connection should be dropped
 */
typedef err_t (*tcp_extarg_callback_passive_open_fn)(u8_t id, struct tcp_pcb_listen *lpcb, struct tcp_pcb *cpcb);

/** A table of callback functions that is invoked for ext arguments */
struct tcp_ext_arg_callbacks {
  /** @ref tcp_extarg_callback_pcb_destroyed_fn */
  tcp_extarg_callback_pcb_destroyed_fn destroy;
  /** @ref tcp_extarg_callback_passive_open_fn */
  tcp_extarg_callback_passive_open_fn passive_open;
};

#define LWIP_TCP_PCB_NUM_EXT_ARG_ID_INVALID 0xFF

#if LWIP_TCP_PCB_NUM_EXT_ARGS
/* This is the structure for ext args in tcp pcbs (used as array) */
struct tcp_pcb_ext_args {
  const struct tcp_ext_arg_callbacks *callbacks;
  void *data;
};
/* This is a helper define to prevent zero size arrays if disabled */
#define TCP_PCB_EXTARGS struct tcp_pcb_ext_args ext_args[LWIP_TCP_PCB_NUM_EXT_ARGS];
#else
#define TCP_PCB_EXTARGS
#endif

/**
 * Indicates members common to struct tcp_pcb and struct tcp_listen_pcb.
 */
#define TCP_PCB_COMMON(type) \
  type *next; /* for the linked list */ \
  void *callback_arg; \
  enum tcp_state state; /* TCP state */ \
  u8_t prio; \
  /* ports are in host byte order */ \
  u16_t local_port; \
  /* Configured send buffer size */ \
  LWIP_SO_SNDBUF_DECL

#if LWIP_TCP_TLP_SUPPORT

#define TCP_TLP_MAX_PROBE_CNT 2

#define LWIP_TCP_TLP_CLEAR_VARS(_pcb) do { \
  _pcb->tlp_pto_cnt = 0; \
  _pcb->tlp_rtx_out = 0; \
  _pcb->tlp_high_rxt = 0; \
  _pcb->tlp_time_stamp = 0; \
} while (0)

#define LWIP_TCP_TLP_WCDELACKT 200 /* RECOMMENDED value is 200ms */
#endif /* LWIP_TCP_TLP_SUPPORT */

/** Indicates the TCP protocol control block for listening PCBs. */
struct tcp_pcb_listen {
  /** Common members of all PCB types */
  IP_PCB;
  /** Protocol specific PCB members */
  TCP_PCB_COMMON(struct tcp_pcb_listen)

#if LWIP_CALLBACK_API
  /* Function to call when a listener has been connected. */
  tcp_accept_fn accept;
#endif /* LWIP_CALLBACK_API */

#if LWIP_SO_PRIORITY
  prio_t priority;
#endif /* LWIP_SO_PRIORITY */

#if TCP_LISTEN_BACKLOG
  u8_t backlog;
  u8_t accepts_pending;
#endif /* TCP_LISTEN_BACKLOG */
};

/** Delayed ACK. */
#define TF_ACK_DELAY   0x01U
/** Immediate ACK. */
#define TF_ACK_NOW     0x02U
/** In fast recovery. */
#define TF_INFR        0x04U
/** If this is set, tcp_close failed to enqueue the FIN (retried in tcp_tmr) */
#define TF_CLOSEPEND   0x08U
/** Rx is closed by tcp_shutdown */
#define TF_RXCLOSED    0x10U
/** Connection was closed locally (FIN segment enqueued). */
#define TF_FIN         0x20U
/** Disable Nagle algorithm */
#define TF_NODELAY     0x40U
/** Nagle algorithm is enabled. memerr. Try to output to prevent delayed ACK to happen */
#define TF_NAGLEMEMERR 0x80U
#if LWIP_WND_SCALE
/** Window Scale option enabled */
#define TF_WND_SCALE   0x0100U
#endif
#if TCP_LISTEN_BACKLOG
/** If this is set, a connection PCB has increased the backlog on its listener */
#define TF_BACKLOGPEND 0x0200U
#endif
#if LWIP_TCP_TIMESTAMPS
/** Timestamp option enabled */
#define TF_TIMESTAMP   0x0400U
#endif
/** Tx closed by tcp_shutdown */
#define TF_TXCLOSED    0x0800U

/* TCP flags for New Reno */
#define TF_INFR_PACK  ((tcpflags_t)0x1000U)   /* Partial ACK recved flag */
#define TF_RTO        ((tcpflags_t)0x2000U)   /* RTO timer has fired, in-flight data moved to unsent and being retransmitted */
#define TF_INFR_FPACK        ((tcpflags_t)0x4000U)   /* Flag for wait for first parital ack */

#if LWIP_SACK
/** TCP SACK option enabled. */
#define TF_SACK         ((tcpflags_t)0x10000U)
/** In SACK based Fast retransmit & loss recovery algorithm */
#define TF_IN_SACK_FRLR ((tcpflags_t)0x20000U)
/** From loss recovery, it entered to Retrasnmit timeout state. */
#define TF_IN_SACK_RTO  ((tcpflags_t)0x40000U)
#endif

#if DRIVER_STATUS_CHECK
#define TF_RST_ON_DRV_WAKE  ((tcpflags_t)0x80000U)   /* From loss receovery it entered to Retrasnmit timeout state */
#endif

/** the TCP protocol control block */
struct tcp_pcb {
  /** common PCB members */
  IP_PCB;
  /** protocol specific PCB members */
  TCP_PCB_COMMON(struct tcp_pcb)

  /* ports are in host byte order */
  u16_t remote_port;
  u16_t pad1;

  tcpflags_t flags;

#if DRIVER_STATUS_CHECK
  /* Netif driver status */
  u8_t drv_status; /* 0 - Driver not ready. 1- Driver is ready */
  u8_t pad0;
#endif

  /* the rest of the fields are in host byte order
     as we have to do some math with them */
  /* Timers */
  u8_t polltmr, pollinterval;
  u8_t last_timer;
  u32_t tmr;

  /* receiver variables */
  u32_t rcv_nxt;   /* next seqno expected */
  tcpwnd_size_t rcv_wnd;   /* receiver window available */
  tcpwnd_size_t rcv_ann_wnd; /* receiver window to announce */
  u32_t rcv_ann_right_edge; /* announced right edge of window */

  /* Retransmission timer. */
  s16_t rtime;

  u16_t mss;   /* maximum segment size, the real value used to do segmentation */
  u16_t rcv_mss; /* mss from peer side */

  u16_t pad4;

  /* RTT (round trip time) estimation variables */
  u32_t rttest;   /* The start time of RTT sample in ms, the granularity is system tick */
  u32_t rtseq;    /* sequence number being timed */
  s16_t sa;   /* smoothed round-trip time, 8 times of SRTT in RFC6298 */
  s16_t sv;   /* round-trip time variation, 4 times of RTTVAR in RFC6298 */

  s16_t rto;    /* retransmission time-out (in ticks of TCP_SLOW_INTERVAL) */
  u8_t nrtx;    /* number of retransmissions */

  /* fast retransmit/recovery */
  u8_t dupacks;

  u16_t pad5;

  u32_t lastack; /* Highest acknowledged seqno, also knowns SND.UNA */

  /* congestion avoidance/control variables */
  tcpwnd_size_t iw;
  tcpwnd_size_t cwnd;
  tcpwnd_size_t ssthresh;
  u32_t rto_end;

  /* sender variables */
  u32_t snd_nxt;   /* next new seqno to be sent */
  u32_t snd_sml;   /* The last byte of the most recently transmitted small packet */
  u32_t snd_wl1, snd_wl2; /* Sequence and acknowledgement numbers of last
                             window update. */
  u32_t snd_lbb;       /* Sequence number of next byte to be buffered. */
  tcpwnd_size_t snd_wnd;   /* sender window */
  tcpwnd_size_t snd_wnd_max; /* the maximum sender window announced by the remote host */

  tcpwnd_size_t snd_buf;   /* Available buffer space for sending (in bytes). */

  tcpwnd_size_t bytes_acked;

#if LWIP_WND_SCALE
#define TCP_SNDQUEUELEN_OVERFLOW (0x03ffffffU - 3)
#else /* LWIP_WND_SCALE */
#define TCP_SNDQUEUELEN_OVERFLOW (0xffffU - 3)
#endif /* LWIP_WND_SCALE */
  tcpwnd_size_t snd_queuelen; /* Available buffer space for sending (in tcp_segs). */

  tcpwnd_size_t snd_queuelen_max;
  tcpwnd_size_t snd_queuelen_lowat;
  tcpwnd_size_t snd_buf_lowat;

#if TCP_OVERSIZE
  /* Extra bytes available at the end of the last pbuf in unsent. */
  u16_t unsent_oversize;
  u16_t pad2;
#endif /* TCP_OVERSIZE */

  /* These are ordered by sequence number: */
  struct tcp_seg *unsent;   /* Unsent (queued) segments. */
  struct tcp_seg *unacked;  /* Sent but unacknowledged segments. */
#if TCP_QUEUE_OOSEQ
  struct tcp_seg *ooseq;    /* Received out of sequence segments. */
#endif /* TCP_QUEUE_OOSEQ */

  struct pbuf *refused_data; /* Data previously received but not yet taken by upper layer */

#if LWIP_CALLBACK_API || TCP_LISTEN_BACKLOG
  struct tcp_pcb_listen *listener;
#endif /* LWIP_CALLBACK_API || TCP_LISTEN_BACKLOG */

#if LWIP_CALLBACK_API
  /* Function to be called when more send buffer space is available. */
  tcp_sent_fn sent;
  /* Function to be called when (in-sequence) data has arrived. */
  tcp_recv_fn recv;
  /* Function to be called when a connection has been set up. */
  tcp_connected_fn connected;
  /* Function which is called periodically. */
  tcp_poll_fn poll;
  /* Function to be called whenever a fatal error occurs. */
  tcp_err_fn errf;
#endif /* LWIP_CALLBACK_API */

#if DRIVER_STATUS_CHECK
  tcp_event_sndplus_fn  sndplus;
#endif

#if LWIP_TCP_TIMESTAMPS
  u32_t ts_lastacksent;
  u32_t ts_recent;
#endif /* LWIP_TCP_TIMESTAMPS */

  /* idle time before KEEPALIVE is sent */
  u32_t keep_idle;
#if LWIP_TCP_KEEPALIVE
  u32_t keep_intvl;
  u32_t keep_cnt;
#endif /* LWIP_TCP_KEEPALIVE */

  /* Persist timer counter */
  u8_t persist_cnt;
  /* Persist timer back-off */
  u8_t persist_backoff;
  /* Number of persist probes, used for timeout calculation */
  u8_t persist_probe;
  /* KEEPALIVE counter */
  u8_t keep_cnt_sent;

  u32_t last_payload_len;

  u32_t fast_recovery_point; /* snd_nxt when enter fast recovery */

#if LWIP_SACK
  struct _sack_seq *sack_seq;
  /* SACK based pipe algorthim Changes */
  /* Pipe to hold the number of octets available in network */
  u32_t pipe;
  /* Recovery point for stopping loss recovery phase */
  u32_t recovery_point;
  /* highest octet covered by any received SACK block */
  u32_t high_sacked;

  /* Loss recovery check needs to be started from this seg instead of pcb->unacked */
  /* This excludes the rexmited and sacked seg from pcb->unacked */
  /* That means, next_seg_for_lr points to first unsacked and  not retransmitted seg */
  /* Optimization of SACK based pipe algorthim */
  struct tcp_seg *next_seg_for_lr;

  /* highest data trasnfered so far, equivalent to snd_nxt */
  u32_t high_data;
  /* highest octet retransmitted so far, as part of SACK based loss recovery algorithm */
  u32_t high_rxt;
  /* Rescure rxt as per loss recovery algorithm */
  u32_t rescue_rxt;

  u32_t num_sacks;
  u32_t ooseq_cnt;

#if LWIP_SACK_PERF_OPT
  u32_t pkt_seq_num;  /* packet order on which they are transmitted out of stack */
  u32_t high_sacked_pkt_seq;
  struct tcp_sack_fast_rxmited *fr_segs; /* List of fast retransmitted segments */
  /*
   * The latest fast retransmitted segment. This stores the latest
   * fast retransmitted segment so that when more segments are retransmitted,
   * it can be appended to this segmetn without iterating whole list
   */
  struct tcp_sack_fast_rxmited *last_frseg;
#if LWIP_SACK_CWND_OPT
  tcpwnd_size_t recover_cwnd;
  tcpwnd_size_t recover_ssthresh;
#endif /* LWIP_SACK_CWND_OPT */
#endif /*LWIP_SACK_PERF_OPT*/
  u32_t sacked; /* The total SACKed segments count */

#if LWIP_FACK_THRESHOLD_BASED_FR
  u32_t fack;
#endif /* LWIP_FACK_THRESHOLD_BASED_FR */

#if LWIP_TCP_TLP_SUPPORT
  u8_t tlp_pto_cnt; /* Consecutive PTOs */
  u8_t tlp_rtx_out; /* the number of unacknowledged TLP retransmissions in current TLP episode */
  u32_t tlp_high_rxt; /* SND.NXT at the time it starts doing TLP transmissions during a given TLP episode */
  u32_t tlp_time_stamp; /* PTO trigger time in ms. 0 is one specially value which means PTO is not scheduled */
#endif /* LWIP_TCP_TLP_SUPPORT */
#endif /* LWIP_SACK */

#if LWIP_SO_PRIORITY
  prio_t priority;
#endif /* LWIP_SO_PRIORITY */

#if LWIP_WND_SCALE
  u8_t snd_scale;
  u8_t rcv_scale;
#endif

  u8_t tcp_pcb_flag;
};

#if LWIP_EVENT_API

enum lwip_event {
  LWIP_EVENT_ACCEPT,
  LWIP_EVENT_SENT,
  LWIP_EVENT_RECV,
  LWIP_EVENT_CONNECTED,
  LWIP_EVENT_POLL,
  LWIP_EVENT_ERR
};

err_t lwip_tcp_event(void *arg, struct tcp_pcb *pcb,
                     enum lwip_event,
                     struct pbuf *p,
                     u16_t size,
                     err_t err);

#endif /* LWIP_EVENT_API */

#if LWIP_API_RICH
/* Application program's interface: */
/**
 * @ingroup tcp_raw
 * Creates a new TCP protocol control block but does not place it on
 * any of the TCP PCB lists.
 * The PCB is not put on any list until binding using tcp_bind().
 *
 * @note Maybe there should be a idle TCP PCB list where these
 * PCBs are put on. Port reservation using tcp_bind() is implemented but
 * allocated pcbs that are not bound cannot be killed automatically if wanting
 * to allocate a PCB with higher prio.
 *
 * @return Returns a new tcp_pcb that initially is in state CLOSED.
 */
struct tcp_pcb *tcp_new     (void);
#endif /* LWIP_API_RICH */

/**
 * @ingroup tcp_raw
 * Creates a new TCP protocol control block but doesn't
 * place it on any of the TCP PCB lists.
 * The PCB is not put on any list until binding using tcp_bind().
 *
 * @param type IP address type.
 * If you want to listen to IPv4 and IPv6 (dual-stack) connections,
 * supply @ref IPADDR_TYPE_ANY as argument and bind to @ref IP_ANY_TYPE.
 * @return Returns a new tcp_pcb that initially is in state CLOSED.
 */
struct tcp_pcb *tcp_new_ip_type (u8_t type);
/**
 * @ingroup tcp_raw
 * Used to specify the argument that should be passed callback
 * functions.
 *
 * @param pcb Indicates the tcp_pcb to set the callback argument.
 * @param arg A void pointer argument to pass to callback functions.
 */
void             tcp_arg     (struct tcp_pcb *pcb, void *arg);
#if LWIP_CALLBACK_API
/**
 * @ingroup tcp_raw
 * Used to specify the function that should be called when a TCP
 * connection receives data.
 *
 * @param pcb Indicates the tcp_pcb to set the recv callback
 * @param recv A callback function to call for this PCB when data is received.
 */
void             tcp_recv    (struct tcp_pcb *pcb, tcp_recv_fn recv);
/**
 * @ingroup tcp_raw
 * Used to specify the function that should be called when TCP data
 * has been successfully delivered to the remote host.
 *
 * @param pcb Indicates the tcp_pcb to set the sent callback.
 * @param sent A callback function to call for this pcb when data is successfully sent
 */
void             tcp_sent    (struct tcp_pcb *pcb, tcp_sent_fn sent);
/**
 * @ingroup tcp_raw
 * Used to specify the function that should be called when a fatal error
 * has occurred on the connection.
 *
 * @note The corresponding PCB is already freed when this callback is called!
 *
 * @param pcb Indicates a tcp_pcb to set the err callback.
 * @param err callback function to call for this PCB when a fatal error
 *        has occurred on the connection.
 */
void             tcp_err     (struct tcp_pcb *pcb, tcp_err_fn err);

/**
 * @ingroup tcp_raw
 * Used for specifying the function that should be called when a
 * listening connection has been connected to another host.
 *
 * @param pcb Indicates the tcp_pcb to set the accept callback.
 * @param accept callback function to call for this PCB when listening
 *        connection has been connected to another host.
 */
void             tcp_accept  (struct tcp_pcb *pcb, tcp_accept_fn accept);
#endif /* LWIP_CALLBACK_API */
/**
 * @ingroup tcp_raw
 * Used to specify the function that should be called periodically
 * from TCP. The interval is specified in terms of the TCP coarse
 * timer interval, which is called twice a second.
 *
 */
void             tcp_poll    (struct tcp_pcb *pcb, tcp_poll_fn poll, u8_t interval);

#if LWIP_LOWPOWER
u32_t tcp_fast_tmr_tick(void);
u32_t tcp_slow_tmr_tick(void);
#endif

#if LWIP_TCP_TIMESTAMPS
#define          tcp_mss(pcb)             (((pcb)->flags & TF_TIMESTAMP) ? ((pcb)->mss - 12)  : (pcb)->mss)
#else /* LWIP_TCP_TIMESTAMPS */
#define          tcp_mss(pcb)             ((pcb)->mss)
#endif /* LWIP_TCP_TIMESTAMPS */
#define          tcp_sndbuf(pcb)          ((pcb)->snd_buf)
#define          tcp_sndqueuelen(pcb)     ((pcb)->snd_queuelen)

#if LWIP_SO_SNDBUF
#define          tcp_set_sendbufsize(pcb, size)    ((pcb)->snd_buf_static = (tcpwnd_size_t)(size))
#define          tcp_get_sendbufsize(pcb)    ((pcb)->snd_buf_static)
#endif /* LWIP_SO_SNDBUF */

#if LWIP_SO_PRIORITY
#define      tcp_getpriority(pcb)  ((pcb)->priority)
#endif /* LWIP_SO_PRIORITY */

#define          tcp_set_flags(pcb, set_flags) do { \
  (pcb)->flags = (tcpflags_t)((pcb)->flags | (set_flags)); } while (0)
#define          tcp_clear_flags(pcb, clr_flags) do { \
  (pcb)->flags = (tcpflags_t)((pcb)->flags & (tcpflags_t)(~(clr_flags) & TCP_ALLFLAGS)); } while (0)
#define          tcp_is_flag_set(pcb, flag)        (((pcb)->flags & (flag)) != 0)

/** @ingroup tcp_raw */
#define          tcp_nagle_disable(pcb)   ((pcb)->flags |= TF_NODELAY)
/** @ingroup tcp_raw
* Enables Nagle algorithm. */
#define          tcp_nagle_enable(pcb)    ((pcb)->flags = (tcpflags_t)((pcb)->flags & ~TF_NODELAY))
/** @ingroup tcp_raw
* Disables Nagle algorithm. */
#define          tcp_nagle_disabled(pcb)  (((pcb)->flags & TF_NODELAY) != 0)

#if TCP_LISTEN_BACKLOG
#define          tcp_backlog_set(pcb, new_backlog) do { \
  LWIP_ASSERT("pcb->state == LISTEN (called for wrong pcb?)", (pcb)->state == LISTEN); \
  ((struct tcp_pcb_listen *)(pcb))->backlog = (u8_t)((new_backlog) ? (new_backlog) : 1); } while (0)
void             tcp_backlog_delayed(struct tcp_pcb *pcb);
void             tcp_backlog_accepted(struct tcp_pcb *pcb);
#else /* TCP_LISTEN_BACKLOG */
#define          tcp_backlog_set(pcb, new_backlog)
#define          tcp_backlog_delayed(pcb)
#define          tcp_backlog_accepted(pcb)
#endif /* TCP_LISTEN_BACKLOG */
#define          tcp_accepted(pcb) do { LWIP_UNUSED_ARG(pcb); } while (0) /* compatibility define, no need any more */

void             tcp_recved  (struct tcp_pcb *pcb, u16_t len);
err_t            tcp_bind    (struct tcp_pcb *pcb, const ip_addr_t *ipaddr,
                              u16_t port);
err_t            tcp_connect (struct tcp_pcb *pcb, const ip_addr_t *ipaddr,
                              u16_t port, tcp_connected_fn connected);

struct tcp_pcb *tcp_listen_with_backlog_and_err(struct tcp_pcb *pcb, u8_t backlog, err_t *err);
#if LWIP_API_RICH
struct tcp_pcb *tcp_listen_with_backlog(struct tcp_pcb *pcb, u8_t backlog);
/** @ingroup tcp_raw */
#define          tcp_listen(pcb) tcp_listen_with_backlog(pcb, TCP_DEFAULT_LISTEN_BACKLOG)
#endif /* LWIP_API_RICH */

void             tcp_abort (struct tcp_pcb *pcb);
err_t            tcp_close   (struct tcp_pcb *pcb);
err_t            tcp_shutdown(struct tcp_pcb *pcb, int shut_rx, int shut_tx);

err_t            tcp_write   (struct tcp_pcb *pcb, const void *dataptr, tcpwnd_size_t len,
                              u8_t apiflags);

#if LWIP_API_RICH
void             tcp_setprio (struct tcp_pcb *pcb, u8_t prio);
#endif /* LWIP_API_RICH */

#if LWIP_TCP_TLP_SUPPORT
/*
 * This is the TLP probe timeout function as in draft-dukkipati-tcpm-tcp-loss-probe-01
 *
 * When PTO fires:
 *   (a) If a new previously unsent segment exists:
 *         -> Transmit new segment.
 *         -> FlightSize += SMSS. cwnd remains unchanged.
 *   (b) If no new segment exists:
 *         -> Retransmit the last segment.
 *   (c) Increment statistics counter for loss probes.
 *   (d) If conditions in (2) are satisfied:
 *         -> Reschedule next PTO.
 *       Else:
 *         -> Rearm RTO to fire at epoch 'now+RTO'.
 *
 * @param pcb Protocol control block for the TCP connection to send data
 * @return None
 *
 */
void tcp_pto_fire(struct tcp_pcb *pcb);
#endif

err_t tcp_output  (struct tcp_pcb *pcb);

#if API_MSG_DEBUG || (defined LWIP_DEBUG)
const char *tcp_debug_state_str(enum tcp_state s);
#endif /* API_MSG_DEBUG */

#if DRIVER_STATUS_CHECK
unsigned char tcp_is_netif_addr_check_success(struct tcp_pcb *pcb, struct netif *netif);
void tcp_flush_pcb_on_wake_queue(struct tcp_pcb *pcb, u8_t status);
void tcpip_flush_on_wake_queue(struct netif *netif, u8_t status);
void tcp_ip_flush_pcblist_on_wake_queue(struct netif *netif, struct tcp_pcb *pcb_list, u8_t status);
void tcpip_upd_status_to_tcp_pcbs(struct netif *netif, u8_t status);
void tcp_ip_event_sendplus_on_wake_queue(struct netif *netif);
void tcp_update_drv_status_to_pcbs(struct tcp_pcb *pcb_list, struct netif *netif, u8_t status);
#endif

/* for compatibility with older implementation */
#define tcp_new_ip6() tcp_new_ip_type(IPADDR_TYPE_V6)

void tcp_sndbuf_init(struct tcp_pcb *pcb);

#if LWIP_API_RICH
const char *get_lwip_version(void);
#endif /* LWIP_API_RICH */

void tcp_handle_closepend(void);

#if LWIP_TCP_TLP_SUPPORT
void tcp_tlp_schedule_probe(struct tcp_pcb *pcb, u32_t wnd);
#endif /* LWIP_TCP_TLP_SUPPORT */

#if LWIP_TCP_PCB_NUM_EXT_ARGS
u8_t tcp_ext_arg_alloc_id(void);
void tcp_ext_arg_set_callbacks(struct tcp_pcb *pcb, uint8_t id, const struct tcp_ext_arg_callbacks * const callbacks);
void tcp_ext_arg_set(struct tcp_pcb *pcb, uint8_t id, void *arg);
void *tcp_ext_arg_get(const struct tcp_pcb *pcb, uint8_t id);
#endif

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_TCP */

#endif /* LWIP_HDR_TCP_H */
