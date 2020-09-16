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

#ifndef __SERIAL_DW_H__
#define __SERIAL_DW_H__

#include <hi3861_platform.h>

/**
 * @ingroup hct_io
 */
typedef enum {
    UART_0 = 0, /**< uart0 */
    UART_1 = 1, /**< uart1 */
    UART_2 = 2, /**< uart2 */
} hi_uart;

/**
 * @ingroup hct_io
 * 串口参数结构体
 */
typedef struct {
    hi_u32 baudrate;           /* ex:115200 */
    hi_u8  databit;            /* 5; 6; 7; 8 */
    hi_u8  stopbit;            /* 1:stop_bit 1;  2: stop_bit 2. */
    hi_u8  parity;             /* 0: None; 1:Odd; 2:Even */
    hi_u8  flow_ctrl;          /* 0: None; 1:rts&&cts. 2:only rts; 3:only cts */
    hi_u8  fifoline_tx_int;    /* 0: tx FIFO≤1/8full; 1:tx FIFO≤1/4full; 2:tx FIFO≤1/2full;
                                  3:tx FIFO≤3/4full; 4:tx FIFO≤7/8full */
    hi_u8  fifoline_rx_int;    /* 0: rx FIFO≥1/8full; 1:rx FIFO≥1/4full; 2:rx FIFO≥1/2full;
                                  3:rx FIFO≥3/4full; 4:rx FIFO≥7/8full */
    hi_u8  fifoline_rts;       /* 0:rx FIFO≥1/8full; 1:rx FIFO≥1/4full; 2:rx FIFO≥1/2full;
                                  3:rx FIFO≥3/4full; 4:rx FIFO≥7/8full */
    hi_u8 pad;
} uart_param_stru;

typedef struct {
    hi_u32 baudrate;
    hi_u16 ibrd;
    hi_u16 fbrd;
} hi_uart_brd;

hi_u32 serial_init(hi_uart uart_num, uart_param_stru default_uart_param);
hi_u32 change_uart(hi_uart uart_num);
hi_void serial_putc(const hi_char c);
hi_void serial_puts(const hi_char *s);
hi_void serial_put_buf(const hi_char *buffer, hi_s32 length);
hi_void serial_puthex(hi_u32 h, hi_u8 print_all);
hi_void serial_put_msg0(const hi_char *s);
hi_void serial_put_msg1(const hi_char *s, hi_u32 h);
hi_void serial_put_msg2(const hi_char *s, hi_u32 h1, hi_u32 h2);
hi_void serial_put_msg4(const hi_char *s, hi_u32 h1, hi_u32 h2, hi_u32 h3, hi_u32 h4);
hi_void dw_putc(hi_char c);
hi_s32 serial_getc(hi_void);
hi_s32 serial_tstc(hi_void);
hi_u8 dw_getc(hi_void);
hi_s32 dw_tstc(hi_void);
hi_u32 set_uart_param(hi_u32 base_addr, uart_param_stru uart_param);

/* UART register OFFSET */
#define UART_DR                     0x0
#define UART_RSR_ECR                0x04
#define UART_FR                     0x18
#define UART_ILPR                   0x20
#define UART_IBRD                   0x24
#define UART_FBRD                   0x28
#define UART_LCR_H                  0x2C
#define UART_CR                     0x30
#define UART_IFLS                   0x34
#define UART_IMSC                   0x38
#define UART_RIS                    0x3C
#define UART_MIS                    0x40
#define UART_ICR                    0x44
#define UART_DMACR                  0x48

#define UARTFR_TXFE_MASK            0x80
#define UARTFR_RXFF_MASK            0x40
#define UARTFR_TXFF_MASK            0x20
#define UARTFR_RXFE_MASK            0x10
#define UARTFR_BUSY_MASK            0x04
#define UARTDR_DATA_MASK            0xFF

#define UARTIFS_CFG                 0x10A     /* FIFO water mark:Rx 16 Tx 32 RTS 56 */
#define UART_DMA_ENABLE             0X03
#define UART_DMA_DISABLE            0X04
#define UARTICR_CFG                 0x7FF     /* Clear up all uart interrupt */

#define UARTIMSC_CFG                0x0       /* Disable all uart interrupt */
#define UARTIMSC_CFG_INT            0x50      /* enable rx time out interrupt */

/* UART register OFFSET */
#define UART_LCH_H                  0x2C

#define UART_INTMASK_OVERRUN        (1 << 10)
#define UART_INTMASK_BREAKERR       (1 << 9)
#define UART_INTMASK_PARERR         (1 << 8)
#define UART_INTMASK_FRAMINGERR     (1 << 7)
#define UART_INTMASK_RECTIMEOUT     (1 << 6)
#define UART_INTMASK_TX             (1 << 5)
#define UART_INTMASK_RX             (1 << 4)

#define UARTLCR_H_CFG               0x60      /* 8bit, no parity, FIFO disable */
#define UARTLCR_H_CFG_ODD           0x72      /* 8bit, odd parity,FIFO enable */
#define UARTLCR_H_CFG_FIFO          0x70      /* 8bit, no parity, FIFO enable */
#define UARTCR_CFG                  0x301     /* UART tx enable, rx enable, uart enable */
#define UARTCR_CFG_FLOWENABLE       0xC301    /* UART tx enable, rx enable, uart enable, flow control enable */

#define UART_FIFO_TX_SIZE           64

typedef enum {
    HI_UART_BRD_IDX_1200    = 0,
    HI_UART_BRD_IDX_2400    = 1,
    HI_UART_BRD_IDX_9600    = 2,
    HI_UART_BRD_IDX_19200   = 3,
    HI_UART_BRD_IDX_115200  = 4,
    HI_UART_BRD_IDX_230400  = 5,
    HI_UART_BRD_IDX_460800  = 6,
    HI_UART_BRD_IDX_921600  = 7,
    HI_UART_BRD_IDX_1000000 = 8,
    HI_UART_BRD_IDX_1024000 = 9,
    HI_UART_BRD_IDX_1500000 = 10,
    HI_UART_BRD_IDX_1536000 = 11,
    HI_UART_BRD_IDX_2000000 = 12,
    HI_UART_BRD_IDX_2048000 = 13,
    HI_UART_BRD_IDX_2252800 = 14,
    HI_UART_BRD_IDX_2304000 = 15,
    HI_UART_BRD_IDX_2500000 = 16,
    HI_UART_BRD_IDX_2560000 = 17,
    HI_UART_BRD_IDX_3000000 = 18,
    HI_UART_BRD_IDX_3072000 = 19,
    HI_UART_BRD_IDX_3500000 = 20,
    HI_UART_BRD_IDX_3584000 = 21,
    HI_UART_BRD_IDX_3840000 = 22,
    HI_UART_BRD_IDX_4000000 = 23,
    HI_UART_BRD_IDX_4096000 = 24,
    HI_UART_BRD_IDX_4500000 = 25,
    HI_UART_BRD_IDX_4608000 = 26,
    HI_UART_BRD_IDX_5000000 = 27,
    HI_UART_BRD_IDX_6000000 = 28,
    HI_UART_BRD_IDX_MAX,
} hi_uart_brd_idx_e;

typedef enum {
    HI_UART_BRD_1200    = 1200,
    HI_UART_BRD_2400    = 2400,
    HI_UART_BRD_9600    = 9600,
    HI_UART_BRD_19200   = 19200,
    HI_UART_BRD_115200  = 115200,
    HI_UART_BRD_230400  = 230400,
    HI_UART_BRD_460800  = 460800,
    HI_UART_BRD_921600  = 921600,
    HI_UART_BRD_1000000 = 1000000,
    HI_UART_BRD_1024000 = 1024000,
    HI_UART_BRD_1500000 = 1500000,
    HI_UART_BRD_1536000 = 1536000,
    HI_UART_BRD_2000000 = 2000000,
    HI_UART_BRD_2048000 = 2048000,
    HI_UART_BRD_2252800 = 2252800,
    HI_UART_BRD_2304000 = 2304000,
    HI_UART_BRD_2500000 = 2500000,
    HI_UART_BRD_2560000 = 2560000,
    HI_UART_BRD_3000000 = 3000000,
    HI_UART_BRD_3072000 = 3072000,
    HI_UART_BRD_3500000 = 3500000,
    HI_UART_BRD_3584000 = 3584000,
    HI_UART_BRD_3840000 = 3840000,
    HI_UART_BRD_4000000 = 4000000,
    HI_UART_BRD_4096000 = 4096000,
    HI_UART_BRD_4500000 = 4500000,
    HI_UART_BRD_4608000 = 4608000,
    HI_UART_BRD_5000000 = 5000000,
    HI_UART_BRD_6000000 = 6000000,
} hi_uart_baudrate_e;

#endif
