/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "los_event.h"
#include "los_task.h"
#include "hisoc/uart.h"
#include "los_printf.h"
EVENT_CB_S g_uartEvent;

#ifdef LOSCFG_PLATFORM_UART_WITHOUT_VFS
#ifdef LOSCFG_SHELL
#define UART_BUF    128
static UINT8    g_uart_buf[UART_BUF];
extern void shellCmdLineParse(CHAR c, pf_OUTPUT pf_put);
static channel_data_t smdk_ser_channels[2] = {
    {(UINT32)UART0_REG_BASE, 1000, NUM_HAL_INTERRUPT_UART0},
    {(UINT32)UART1_REG_BASE, 1000, NUM_HAL_INTERRUPT_UART1}
};
#endif
#endif
#ifdef LOSCFG_GDB
extern int gdb_is_enter(void);
#endif

UINT8 uart_getc(void)
{
    UINT8 ch = 0;
    UINT32 base = UART_REG_BASE;
#ifdef LOSCFG_GDB
    if (gdb_is_enter()) {
        // nothing to do when using gdb, you can't read from serial.
    } else {
#endif
        UINT32 status;
        READ_UINT32(status, base + UART_FR);
        /* Wait until there is data in the FIFO */
        while (status & 0x10) {
            READ_UINT32(status, base + UART_FR);
            (VOID)LOS_TaskDelay(1);
        }

        READ_UINT8(ch, UART_REG_BASE + UART_DR);
#ifdef LOSCFG_GDB
    }
#endif

    return ch;  /*lint !e438*/
}   /*lint !e550*/

#if defined(LOSCFG_COREDUMP) || defined(LOSCFG_LLTSER)
UINT8 uart_getc_interrupt(void)
{
    UINT8 ch = 0;
    UINT32 status;
    UINT32 base = UART_REG_BASE;
    READ_UINT32(status, base + UART_FR);

    while (status & 0x10) { /*lint !e40*/
        READ_UINT32(status, base + UART_FR);
    }
    /* receive one char */
    READ_UINT8(ch, UART_REG_BASE + UART_DR);
    return ch;
}
#endif

#ifdef LOSCFG_GDB
static char gdb_log_buf[1024 * 8];
static int gdb_log_buf_write_pos = 0;
static int gdb_log_buf_read_pos = 0;
const static int gdb_log_buf_size = sizeof(gdb_log_buf);

#endif

char uart_putc(char c)
{
#ifdef LOSCFG_GDB
    if (gdb_is_enter()) {
        // if buf full
        if (((gdb_log_buf_write_pos + 1) % gdb_log_buf_size) == gdb_log_buf_read_pos) {
            // buffer is full, u can do others
        } else {
            // when using gdb, we should save log data temporarily.
            gdb_log_buf[gdb_log_buf_write_pos] = c;
            gdb_log_buf_write_pos = (gdb_log_buf_write_pos + 1) % gdb_log_buf_size;
        }
    } else {
#endif
        UINT32 status = 0;

        /* Wait for Tx FIFO not full */
        do {
            READ_UINT32(status, UART_REG_BASE + UART_FR);
        } while (status & 0x20);

        WRITE_UINT8(c, UART_REG_BASE + UART_DR);
#ifdef LOSCFG_GDB
    }
#endif

    return c;
}

unsigned int g_uart_fputc_en __attribute__ ((section(".data"))) = 1;
char uart_fputc(char c, void *f)
{
    if (g_uart_fputc_en == 1) {
        if (c == '\n') {
            uart_putc('\r'); /*lint !e534*/
        }
        return (uart_putc(c));
    } else {
        return 0;
    }
}

#ifdef LOSCFG_PLATFORM_UART_WITHOUT_VFS
#ifdef LOSCFG_SHELL
static void uart_notice_adapt(void)
{
    LOS_EventWrite(&g_uartEvent, 0x112);
}
void uart_get_raw(void)
{
    UINT8 ch;
    static int cnt_ii = 0;
    if (cnt_ii == 0) {
        (VOID)memset_s(g_uart_buf, UART_BUF, 0, UART_BUF);
    }
    ch = uart_getc();
    g_uart_buf[cnt_ii] = ch;
    cnt_ii++;
    switch (cnt_ii) {
        case 1:  // only one char
            if (ch != 27) { // un special
                uart_notice_adapt();
                cnt_ii = 0;
            }
            break;
        case 2:
            if (ch != 91) {
                uart_notice_adapt();
                cnt_ii = 0;
            }
            break;
        case 3:
            switch (ch) {
                default:
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                        uart_notice_adapt();
                        cnt_ii = 0;
                    break;
                case 51:
                case 49:
                case 52:
                    break;
            }
            break;
        case 4:
                uart_notice_adapt();
                cnt_ii = 0;
            break;

        default:
                uart_notice_adapt();
                cnt_ii = 0;
            break;
    }
}
extern void dprintf(const char *fmt, ...);

static void uart_irqhandle(void)
{
    shellCmdLineParse(0, dprintf);
    WRITE_UINT32((1 << 4) | (1 << 6), UART_REG_BASE + UART_CLR);
}

int uart_hwiCreate(void)
{
    UINT32 uwRet = 0;
    if (uwRet != LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0xa0, 0, uart_irqhandle, 0)) {
        return uwRet;
    }
    uart_interrupt_unmask();
    return 0;
}
#endif /* LOSCFG_SHELL */
#endif /* LOSCFG_PLATFORM_UART_WITHOUT_VFS */

void uart_init(void)
{
    UINT32 uwBaudRate;
    UINT32 divider;
    UINT32 remainder;
    UINT32 fraction;

#if defined LOSCFG_PLATFORM_HI3519 || defined LOSCFG_PLATFORM_HI3519V101 || defined LOSCFG_PLATFORM_HI3559
        uart_pin_mux_cfg(CONSOLE_UART);  /*lint !e506*/
        uart_clk_cfg(CONSOLE_UART, true);  /*lint !e506*/
#endif

    /* First, disable everything */
    WRITE_UINT32(0x0, UART_REG_BASE + UART_CR);

    /* set baud rate */
    uwBaudRate = 16 * CONSOLE_UART_BAUDRATE;
    divider = CONFIG_UART_CLK_INPUT / uwBaudRate;
    remainder = CONFIG_UART_CLK_INPUT % uwBaudRate;
    uwBaudRate = (8 * remainder) / CONSOLE_UART_BAUDRATE;
    fraction = (uwBaudRate >> 1) + (uwBaudRate & 1);

    WRITE_UINT32(divider, UART_REG_BASE + UART_IBRD);
    WRITE_UINT32(fraction, UART_REG_BASE + UART_FBRD);

    /* Set the UART to be 8 bits, 1 stop bit, no parity, fifo enabled. */
    WRITE_UINT32((3 << 5) | (1 << 4), UART_REG_BASE + UART_LCR_H);

    /* set the fifo threshold of recv interrupt >= 1/8 full */
    WRITE_UINT32((2 << 3) | (4 << 0), UART_REG_BASE + UART_IFLS);

    /* set nonblock of recv interrupt and recv timeout interrupt */
    WRITE_UINT32((1 << 4) | (1 << 6), UART_REG_BASE + UART_IMSC);
    /* enable the UART */
    WRITE_UINT32((1 << 0) | (1 << 8) | (1 << 9), UART_REG_BASE + UART_CR);

    (VOID)LOS_EventInit(&g_uartEvent);
}

#ifdef LOSCFG_GDB
UINT8 gdb_uart_getc(void)
{
    UINT8 ch = 0;
    UINT32 status;

    UINT32 base = UART_REG_BASE;
    READ_UINT32(status, base + UART_FR);

    /* Wait until there is data in the FIFO */
    while (status & 0x10) { /*lint !e40*/
        READ_UINT32(status, base + UART_FR);
    }

    READ_UINT8(ch, UART_REG_BASE + UART_DR);
    return ch;  /*lint !e438*/
}

char gdb_uart_putc(char c)
{
    UINT32 status = 0;

    /* Wait for Tx FIFO not full */
    do {
        READ_UINT32(status, UART_REG_BASE + UART_FR);
    } while (status & 0x20);

    WRITE_UINT8(c, UART_REG_BASE + UART_DR);
    return c;
}

void gdb_log_flush(void)
{
    while (gdb_log_buf_read_pos != gdb_log_buf_write_pos) {
        gdb_uart_putc(gdb_log_buf[gdb_log_buf_read_pos]);
        gdb_log_buf_read_pos = (gdb_log_buf_read_pos + 1) % gdb_log_buf_size;
    }
}

#endif

void uart_interrupt_unmask(void)
{
    HalIrqUnmask(NUM_HAL_INTERRUPT_UART);
}
