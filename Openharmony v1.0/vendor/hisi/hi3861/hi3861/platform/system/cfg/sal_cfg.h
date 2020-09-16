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

#ifndef __SAL_CFG_H__
#define __SAL_CFG_H__
#include <hi_types.h>
#include <hi_diag.h>

/* defined in tee_hks lib. */
extern hi_void hks_handle_secure_call(void);
extern hi_void hks_handle_secure_pki_provision(void);

#define INIT_CONFIG_XTAL_COMPESATION 1

typedef struct {
    hi_s32 init_cfg_rf_high_temp_threshold;
    hi_s32 init_cfg_rf_low_temp_threshold;
    hi_s32 init_cfg_rf_ppm_compesation;
} rf_cfg_xtal_compesation;

/* read rf xtal compesation from Factory NV */
hi_u32 hi_get_rf_xtal_compesation_param(rf_cfg_xtal_compesation *rf_cfg_xtal_compesatioan);

typedef hi_u32 (*oam_log_msg0_func)(hi_u32 msg_id, hi_u16 msg_level);
typedef hi_u32 (*oam_log_msg1_func)(hi_u32 msg_id, hi_u32 d0, hi_u16 msg_level);
typedef hi_u32 (*oam_log_msg2_func)(hi_u32 msg_id, hi_u32 d0, hi_u32 d1, hi_u16 msg_level);
typedef hi_u32 (*oam_log_msg3_func)(hi_u32 msg_id, hi_u32 d0, hi_u32 d1, hi_u32 d2, hi_u16 msg_level);
typedef hi_u32 (*oam_log_msg4_func)(hi_u32 msg_id, diag_log_msg log_msg, hi_u16 msg_level);
typedef hi_u32 (*oam_log_msg_buffer_func)(hi_u32 msg_id, hi_pvoid buffer, hi_u16 size, hi_u16 msg_level);

typedef struct oam_log_hook_func_ {
    oam_log_msg0_func oam_log_msg0;
    oam_log_msg1_func oam_log_msg1;
    oam_log_msg2_func oam_log_msg2;
    oam_log_msg3_func oam_log_msg3;
    oam_log_msg4_func oam_log_msg4;
    oam_log_msg_buffer_func oam_log_msg_buffer;
}oam_log_hook_func;

hi_void oam_log_register_hook_func(const oam_log_hook_func *hook_func);

hi_void hi_diag_register_wifi_log();

#endif

