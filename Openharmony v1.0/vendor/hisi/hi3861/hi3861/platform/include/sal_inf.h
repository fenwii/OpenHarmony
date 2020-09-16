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

#ifndef __SAL_INF_H__
#define __SAL_INF_H__
#include <hi_types.h>
HI_START_HEADER
#include <hi_sal.h>
#include <hi_task.h>
#include <hi_ft_nv.h>
#include <hi_mdm.h>
#include <hi_config.h>

typedef struct {
    hi_bool enable_save;
    hi_bool delay_over;
    hi_bool has_save;
    hi_u8 rsv;
    hi_u32 rst_times;
    hi_u32 handle;
} sal_rst_times_ctrl;

hi_u32 sal_rst_times_init(hi_void);
sal_rst_times_ctrl *sal_get_rst_times_ctrl(hi_void);
hi_u32 sal_uart_port_allocation(hi_uart_func_idx uart_func_id, hi_u8 *uart_id);
hi_void lp_sleep(hi_void);

HI_END_HEADER
#endif /* __SAL_INF_H__ */

