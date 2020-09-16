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

#ifndef __HISOC_UART_H__
#define __HISOC_UART_H__

#include "asm/platform.h"
#include "los_typedef.h"
#include "los_base.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define CONFIG_UART0_BAUDRATE   115200
#define CONFIG_UART_CLK_INPUT   (24000000) // 24M or 6M

#define UART0                   0
#define UART1                   1
#define UART2                   2
#define UART3                   3

#define UART0_ENABLE  1
#define UART1_ENABLE  1
#define UART2_ENABLE  1
#define UART3_ENABLE  1

#define UART0_DMA_RX_PERI       16
#define UART1_DMA_RX_PERI       18
#define UART2_DMA_RX_PERI       20
#define UART3_DMA_RX_PERI       22

#define uart_pin_mux_cfg(uart_num) ({ \
        if (UART0 == uart_num) {} \
        else if (UART1 == uart_num) { \
        WRITE_UINT16(0x01, IO_MUX_REG_BASE + 0x07C); \
        WRITE_UINT16(0x01, IO_MUX_REG_BASE + 0x084); \
        } \
        else if (UART2 == uart_num) { \
        WRITE_UINT16(0x01, IO_MUX_REG_BASE + 0x088); \
        WRITE_UINT16(0x01, IO_MUX_REG_BASE + 0x08C); \
        } \
        else if (UART3 ==uart_num) { \
        WRITE_UINT16(0x02, IO_MUX_REG_BASE + 0x078); \
        WRITE_UINT16(0x02, IO_MUX_REG_BASE + 0x080); \
        } \
        })
#define  uart_clk_cfg(uart_num, flag)  ({ \
        unsigned int tmp = 0; \
        tmp = GET_UINT32(CRG_REG_BASE + 0x01B8); \
        if (flag) \
            tmp |= (1<<(uart_num)); \
        else \
            tmp &= ~(1<<(uart_num)); \
        WRITE_UINT32(tmp, CRG_REG_BASE + 0x01B8); \
        })
#define  get_uart_dma_peri(uart_num) ({ \
        unsigned int peri_num = -1; \
        if (UART0 == uart_num) \
        peri_num = UART0_DMA_RX_PERI; \
        else if (UART1 == uart_num) \
        peri_num = UART1_DMA_RX_PERI; \
        else if (UART2 == uart_num) \
        peri_num = UART2_DMA_RX_PERI; \
        else if (UART3 == uart_num) \
        peri_num = UART3_DMA_RX_PERI; \
        peri_num; \
        })


#define TTYS0                               "/dev/ttyS0"

#define CONSOLE_UART                        UART0

#define CONSOLE_UART_BAUDRATE               115200
#define UART_NUM    4
#if (CONSOLE_UART == UART0)
#define TTY_DEVICE                "/dev/uartdev-0"
#define UART_REG_BASE             UART0_REG_BASE
#define NUM_HAL_INTERRUPT_UART    NUM_HAL_INTERRUPT_UART0
#elif (CONSOLE_UART == UART1)
#define TTY_DEVICE                "/dev/uartdev-1"
#define UART_REG_BASE             UART1_REG_BASE
#define NUM_HAL_INTERRUPT_UART    NUM_HAL_INTERRUPT_UART1
#elif (CONSOLE_UART == UART2)
#define TTY_DEVICE                "/dev/uartdev-2"
#define UART_REG_BASE             UART2_REG_BASE
#define NUM_HAL_INTERRUPT_UART    NUM_HAL_INTERRUPT_UART2
#elif (CONSOLE_UART == UART3)
#define TTY_DEVICE                "/dev/uartdev-3"
#define UART_REG_BASE             UART3_REG_BASE
#define NUM_HAL_INTERRUPT_UART    NUM_HAL_INTERRUPT_UART3
#endif

#ifdef LOSCFG_PLATFORM_HISI_AMP
#undef TTY_DEVICE
#define TTY_DEVICE                "/dev/virt-tty"
#endif

typedef struct {
    UINT32 base;
    INT32 msec_timeout;
    int isr_vector;
} channel_data_t;

extern void uart_init(void);
extern void uart_interrupt_unmask(void);
extern int uart_hwiCreate(void);
extern UINT8 uart_getc(void);
extern char uart_fputc(char c, void *f);

extern UINT32 UartPutsReg(UINTPTR base, const CHAR *s, UINT32 len, BOOL isLock);
extern VOID UartPuts(const CHAR *s, UINT32 len, BOOL isLock);

#define UART_WITHOUT_LOCK 0
#define UART_WITH_LOCK    1

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
