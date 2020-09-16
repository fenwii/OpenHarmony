/*
 * Description: declaration for TCP SACK APIs
 */

#ifndef __LWIP_TCP_SACK_CA__
#define __LWIP_TCP_SACK_CA__

#include "lwip/tcp.h"
#include "lwip/priv/tcp_priv.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif


#define UNSACKED_AND_LOST_SEG       0x0001U
#define UNSENT_SEG                  0x0002U
#define UNSACKED_SEG                0x0004U
#define RESCUE_RX_SEG               0x0008U
#define SACK_SYNC_PERMITTED_OPTION  0x04020101U
#define SACK_OPTIONS                0x01010500UL
#define MAX_ORDER                   0xFFFFFFFF
#if DRIVER_STATUS_CHECK
#define FAST_RETX_SEG               0x0010U /* First Segment retransmitted as part of Fast retransmit algorithm */
#define SEG_TYPE_NONE               0x0000U
#endif

extern u32_t
tcp_parseopt_sack(u8_t *opts, u16_t c);

extern u32_t
tcp_sack_update(struct tcp_pcb *pcb, u32_t ackno);

extern void
tcp_sack_based_fast_rexmit_alg(struct tcp_pcb *pcb);

extern void
tcp_sack_based_loss_recovery_alg(struct tcp_pcb *pcb);

#if LWIP_SACK_PERF_OPT
extern void
tcp_sack_rexmit_lost_rexmitted(struct tcp_pcb *pcb);
#endif

extern void
tcp_sack_set_pipe(struct tcp_pcb *pcb);

extern int
tcp_sack_is_lost(struct tcp_pcb *pcb, struct tcp_seg *seg);

void tcp_pcb_reset_sack_seq(struct tcp_pcb *pcb);
void tcp_update_sack_for_received_ooseq_segs(struct tcp_pcb *pcb);
void tcp_update_sack_fields_for_new_seg(struct tcp_seg *seg);
void tcp_enqueue_flags_sack(struct tcp_pcb *pcb, u8_t *optflags);
void tcp_build_sack_permitted_option(u32_t *opts);
u8_t tcp_get_sack_block_count_for_send(struct tcp_pcb *pcb, u8_t optlen);
void tcp_build_sack_option(struct tcp_pcb *pcb, u8_t cnt, u32_t *options);
void tcp_parseopt_sack_permitted(struct tcp_pcb *pcb);
void tcp_connect_update_sack(struct tcp_pcb *pcb, u32_t iss);
struct tcp_seg *tcp_sack_get_next_seg(struct tcp_pcb *pcb, u32_t next_seg_type);

#if LWIP_SACK_DATA_SEG_PIGGYBACK
#if LWIP_SACK
u8_t tcp_check_and_alloc_sack_options(struct tcp_seg *seg, struct tcp_pcb *pcb);
#endif
#endif
#if DRIVER_STATUS_CHECK
#if LWIP_SACK
void tcp_search_and_flush_sack_on_wake_queue(struct tcp_pcb *pcb, u32_t sack_type);
#endif
#endif
#if defined (__cplusplus) && __cplusplus
}
#endif

#endif
