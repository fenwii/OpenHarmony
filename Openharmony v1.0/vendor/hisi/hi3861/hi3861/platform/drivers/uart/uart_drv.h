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

#ifndef __UART_DRV_H__
#define __UART_DRV_H__

#include <hi_event.h>
#include <hi_config.h>
#include <hi_mem.h>
#include <hi_mdm.h>
#ifdef __cplusplus
extern "C" {
#endif

#define UART_RD_EVENT        0x1
#define UART_WD_EVENT        0x2
#define UART_RD_QUIT_EVENT   (1 << 2)
#define BUF_CIRCLED          (1 << 0)
#define BUF_OVERFLOWED       (1 << 1)
#define BUF_EMPTIED          (1 << 2)
#define UART_FLG_RD_NONBLOCK 1
#define UART_FLG_RD_BLOCK    2
#define UART_FLG_WD_NONBLOCK 1
#define UART_FLG_WD_BLOCK    2
#define UART_TX_INT_BIT      (1 << 5)
#define UART_RX_INT_ENABLE   0x50

#define GPIO_SEL_UART        0
#define GPIO_SEL_GPIO        1

#define UART_ERR_PARA_INVALID          1
#define UART_ERR_INIT_CIRC_FAILED      2
#define UART_ERR_START_FAILED          3
#define UART_ERR_IOCTL_FAILED          4
#define UART_ERR_PTR_NULL              5
#define UART_ERR_OPEN_AGAIN            6
#define UART_ERR_NOT_OPENED            7
#define UART_ERR_NOT_IDLE              8

/* Read Block: */
#define UART_RD_BLOCK        1
#define UART_RD_NONBLOCK     0

/* Write Block: */
#define UART_WD_BLOCK        1
#define UART_WD_NONBLOCK     0
#define UART_TX_USE_DMA      2
#define UART_RX_USE_DMA      2
#define UART_CFG_SET_ATTR    0x101
#define UART_CFG_RD_BLOCK    0x102
#define UART_CFG_WD_BLOCK    0x103
#define UART_CFG_GET_ATTR    0x104
#define UART_CFG_SET_ACT     0x105
#define UART_CFG_GET_ACT     0x106
#define UART_CFG_GET_BUF_EMPTY    0x107
#define HI_UART_LAST_RECORD_BYTE_COUNT 32
typedef struct {
    hi_u32 baud_rate;
    hi_u8  data_bits;
    hi_u8  stop_bits;
    hi_u8  parity;
    hi_u8  tx_fifo_line;   /**< 0: tx FIFO≤1/8full; 1:tx FIFO≤1/4full; 2:tx FIFO≤1/2full; 3:tx FIFO≤3/4full;
                                4:tx FIFO≤7/8full : default: 2 */
    hi_u8  rx_fifo_line;   /**< 0: rx FIFO≥1/8full; 1:rx FIFO≥1/4full; 2:rx FIFO≥1/2full; 3:rx FIFO≥3/4full;
                                4:rx FIFO≥7/8full : default: 1 */
    hi_u8  flow_fifo_line; /**< 0: rx FIFO≥1/8full; 1:rx FIFO≥1/4full; 2:rx FIFO≥1/2full; 3:rx FIFO≥3/4full;
                                4:rx FIFO≥7/8full : default: 3 */
    hi_u8  flow_ctrl;      /**< 0: disable flow ctrl; 1: enable rts and cts; 2: enable rts only; 3: enable cts only.
                                notice: uart0 not support flow ctrl. */
    hi_u8  pad;            /**< reserved:currently not used. */
} uart_attr_t;

typedef struct {
    hi_u16 tx_buffer_size;
    hi_u16 rx_buffer_size;
    hi_u8 tx_use_dma;
    hi_u8 rx_use_dma;
    hi_u8 tx_block;
    hi_u8 rx_block;
} uart_act_t;

typedef struct uart_circ_buf {
    hi_u32 rp;
    hi_u32 wp;
    hi_u32 flags;
    hi_char *data;
    hi_u32 size;
} uart_circ_buf;

typedef enum uart_status {
    UART_STATE_NOT_OPENED = 0,
    UART_STATE_USEABLE
} uart_status;

typedef enum uart_mode {
    UART_232 = 0
} uart_mode;

typedef struct uart_driver_data uart_driver_data_t;

typedef struct uart_ops {
    hi_u32(*startup) (uart_driver_data_t *udd);
    hi_void(*shutdown) (uart_driver_data_t *udd);
    hi_s32(*start_tx) (uart_driver_data_t *udd, const hi_char *buf, hi_u32 count);
    hi_u32(*ioctl) (uart_driver_data_t *udd);
} uart_ops;

typedef hi_s32(*recv_notify) (uart_circ_buf *transfer, const hi_char *buf, hi_u32 count);
typedef hi_s32(*send_buf) (uart_circ_buf *transfer, hi_char *buf, hi_u32 count);

#ifdef CONFIG_UART_DEBUG_INFO
#define uart_set_errno(err) ((udd->uart_stat_info.uart_errno) = (err))
#else
#define unused_param(p) ((p) = (p))
#define uart_set_errno(err)
#endif

typedef struct {
    hi_char data[HI_UART_LAST_RECORD_BYTE_COUNT];
    hi_u32 num;
} uart_recv_send_last_data;

typedef struct uart_drv_stat_info {
    hi_u32 uart_errno;
    hi_u32 recv_irq_cnt;
    hi_u32 recv_irq_data_cnt;
    hi_u32 read_circ_cnt;
    hi_u32 send_irq_cnt;
    hi_u32 send_irq_data_cnt;
    hi_u32 write_circ_cnt;
    hi_u32 recv_irq_err_overrun;
    hi_u32 recv_irq_err_parity;
    hi_u32 recv_irq_err_frame;
    hi_u32 recv_irq_err_break;
    hi_u32 recv_irq_err_busy;
    hi_u32 recv_irq_err_emptyfifo_cnt;
    hi_u32 send_dma_err_cnt;
    hi_u32 recv_dma_err_cnt;
    uart_recv_send_last_data recv_last_context;
    uart_recv_send_last_data send_last_context;
} uart_drv_stat_info;

struct uart_driver_data {
#ifdef CONFIG_UART_DEBUG_INFO
    uart_drv_stat_info uart_stat_info;
#endif
    hi_char num;
    hi_bool receive_tx_int;
    hi_u16 pad;
    uart_mode type;
    hi_u32 phys_base;
    hi_u32 irq_num;
    uart_circ_buf *rx_transfer;
    uart_circ_buf *tx_transfer;
    hi_u32 event_id;
    hi_u32 count;
    hi_u32 state;
    recv_notify rx_recv;
    send_buf tx_send;
    uart_ops *ops;
    hi_bool tx_use_int;
    uart_attr_t attr;
    uart_act_t act;
};

#ifdef UART_DEBUG_PRINT
#define uart_error(msg...) do { \
        dprintf("\n"); \
        dprintf("<uart,err>:%s,%d: ", __func__, __LINE__); \
        dprintf(msg); \
        dprintf("\n"); \
    }while (0)
#else
#define uart_error(msg...)
#endif

hi_void uart_tx_interrupt_enable(const uart_driver_data_t *udd);
hi_u32 uart_circ_buf_empty(const uart_circ_buf *transfer);
hi_u32 uart_init_circ_buf(uart_driver_data_t *udd, hi_u32 rx_fifo_size, hi_u32 tx_fifo_size);
hi_void uart_deinit_circ_buf(uart_driver_data_t *udd);
hi_s32 uart_read_circ_buf(uart_circ_buf *transfer, hi_char *buf, hi_u32 count);
hi_s32 uart_write_circ_buf(uart_circ_buf *transfer, const hi_char *buf, hi_u32 count);
hi_void uart_set_tx_mode(uart_driver_data_t *udd);
hi_u32 uart_buf_empty(const uart_driver_data_t *udd);
hi_void uart_tx_interrupt_disable(uart_driver_data_t *udd);
hi_void uart_tx_interrupt_clear(const uart_driver_data_t *udd);
hi_void uart_tf_interrupt_disable(uart_driver_data_t *udd);
hi_void uart_rx_interrupt_disable(const uart_driver_data_t *udd);
#ifdef __cplusplus
}
#endif
#endif /* __UART_DRV_H__ */
