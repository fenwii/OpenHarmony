/*
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

#ifndef __DFX_SYS_H__
#define __DFX_SYS_H__

#include "hi_types.h"
#include "hi_mdm_types.h"
#include <hi_ft_nv.h>

HI_START_HEADER

typedef struct {
    hi_u16 send_uart_fail_cnt;
    hi_u16 ack_ind_malloc_fail_cnt;
    hi_u16 msg_malloc_fail_cnt;
    hi_u16 msg_send_fail_cnt;
    hi_u16 msg_overbig_cnt;
    hi_u16 ind_send_fail_cnt;
    hi_u16 ind_malloc_fail_cnt;
    hi_u8 diag_queue_used_cnt;
    hi_u8 diag_queue_total_cnt;
    hi_u8 dec_fail_cnt;
    hi_u8 enc_fail_cnt;
    hi_u16 pkt_size_err_cnt;
    hi_u32 local_req_cnt;
    hi_u16 req_cache_overflow_cnt;
    hi_u8 conn_excep_cnt;
    hi_u8 conn_bu_cnt;
    hi_u8 chl_busy_cnt;
    hi_u8 req_overbig1_cnt;
    hi_u8 cmd_list_total_cnt;
    hi_u8 cmd_list_used_cnt;
    hi_u8 stat_list_total_cnt;
    hi_u8 stat_list_used_cnt;
    hi_u8 req_overbig2_cnt;
    hi_u8 invalid_dec_id;
    hi_u8 heart_beat_timeout_cnt;
    hi_u8 rx_start_flag_wrong_cnt;
    hi_u8 rx_cs_wrong_cnt;
    hi_u8 rx_pkt_data_size_wrong_cnt;
    hi_u16 msg_enqueue_fail_cnt;
    hi_u16 pad;
} hi_stat_diag;

HI_END_HEADER
#endif  /* __DFX_SYS_H__ */
