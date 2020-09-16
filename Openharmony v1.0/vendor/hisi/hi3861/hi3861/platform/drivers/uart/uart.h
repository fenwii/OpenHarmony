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

#ifndef __UART_H__
#define __UART_H__

#include <hi3861_platform.h>

#include "uart_drv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART_NUM         3
#define UART0            0
#define UART1            1
#define UART2            2

#define UART0_BASE      (HI_UART0_REG_BASE)
#define UART1_BASE      (HI_UART1_REG_BASE)
#define UART2_BASE      (HI_UART2_REG_BASE)

#define UART_CIRC_BUF_ENABLE
#define UART_DEFAULT_TX_FIFO_LINE    2 /* tx FIFO<=1/2full */
#define UART_DEFAULT_RX_FIFO_LINE    1 /* rx FIFO>=1/4full */
#define UART_DEFAULT_FLOW_FIFO_LINE  3 /* rx FIFO>=3/4full */
#define UART_DEFAULT_TX_BUFFER_SIZE  0x0200
#define UART_DEFAULT_RX_BUFFER_SIZE  0x0200
#define UART_DEFAULT_TX_USE_DMA      1 /* not use dma */
#define UART_DEFAULT_RX_USE_DMA      1 /* not use dma */
#define UART_DEFAULT_TX_BLOCK        2 /* block */
#define UART_DEFAULT_RX_BLOCK        2 /* block */

#define UART_DEFAULT_FLOW_CONTROL   0 /* 0: disable flow ctrl; 1: enable rts and cts; 2: enable rts only;
                                         3: enable cts only. notice: uart0 not support flow ctrl. */

#define UART_ATTR_DEFAULT    {115200, 8, 1, 0, UART_DEFAULT_TX_FIFO_LINE, UART_DEFAULT_RX_FIFO_LINE,             \
                              UART_DEFAULT_FLOW_FIFO_LINE, UART_DEFAULT_FLOW_CONTROL, HI_FALSE}
#define UART_ACT_DEFAULT     {UART_DEFAULT_TX_BUFFER_SIZE, UART_DEFAULT_RX_BUFFER_SIZE, UART_DEFAULT_TX_USE_DMA, \
                              UART_DEFAULT_RX_USE_DMA, UART_DEFAULT_TX_BLOCK, UART_DEFAULT_RX_BLOCK}


uart_driver_data_t *uart_open(hi_u32 uart_index, uart_mode uart_mode);
hi_s32 uart_read(uart_driver_data_t *udd, hi_char *buf, hi_u32 count);
hi_s32 uart_write(uart_driver_data_t *udd, const hi_char *buf, hi_u32 count);
hi_s32 uart_write_immediately(uart_driver_data_t *udd, const hi_char *buf, hi_u32 count);
hi_u32 uart_ioctl(uart_driver_data_t *udd, hi_u32 cmd, uintptr_t arg);
hi_u32 uart_close(uart_driver_data_t *udd);

extern uart_driver_data_t *g_udd_g[UART_NUM];
extern uart_ops g_uart_driver_uops;

#ifdef __cplusplus
}
#endif
#endif

