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

#ifndef __HI_SAL_NV_H__
#define __HI_SAL_NV_H__

#define  HI_NV_SYS_RST_TIMES        0x40
#define  HI_NV_SYS_RST_CFG_ID       0x41
#define  HI_NV_SYS_UART_PORT_ID     0x42

typedef struct {
    hi_u32 rst_times;
    hi_u32 enable_save;
} hi_sys_reset_times;

typedef struct {
    hi_u8 enable_rst;
    hi_u8 rsv[3];  /* 3 bytes reserved */
    hi_u32 secure_begin_time;
    hi_u32 secure_end_time;
    hi_u32 max_time_usr0;
    hi_u32 max_time_usr1;
} hi_nv_reset_cfg_id;

typedef enum {
    UART_FUNC_AT,
    UART_FUNC_SHELL,
    UART_FUNC_DIAG,
    UART_FUNC_SIGMA,
    UART_FUNC_MAX,
} hi_uart_func_idx;

/* uart port allocation */
typedef struct {
    hi_u8 uart_port_at;
    hi_u8 uart_port_debug;
    hi_u8 uart_port_sigma;
    hi_u8 uart_port_reserved;
} hi_nv_uart_port_alloc;

#endif /* __HI_SAL_NV_H__ */

