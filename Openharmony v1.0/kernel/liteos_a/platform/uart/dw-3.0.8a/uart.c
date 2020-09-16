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
#include "hisoc/uart.h"


EVENT_CB_S g_uartEvent;
#ifdef LOSCFG_PLATFORM_UART_WITHOUT_VFS
#ifdef LOSCFG_SHELL
#define UART_BUF    128
static UINT8 g_uart_buf[UART_BUF];
extern void shellCmdLineParse(CHAR c, pf_OUTPUT pf_put);
#endif
#endif
UINT8 uart_getc(void)
{
    UINT8 ch = 0;

    while (!(GET_UINT32(UART_REG_BASE + UART_USR) & 0x08)) { /*lint !e40*/
        LOS_Msleep(100);
    }
    /* receive one char */
    READ_UINT8(ch, UART_REG_BASE + UART_DR);
    return ch;
}

#if defined(LOSCFG_COREDUMP) || defined(LOSCFG_LLTSER)
UINT8 uart_getc_interrupt(void)
{
    UINT8 ch = 0;

    while (!(GET_UINT32(UART_REG_BASE + UART_USR) & 0x08)) { /*lint !e40*/
    }
    /* receive one char */
    READ_UINT8(ch, UART_REG_BASE + UART_DR);
    return ch;
}
#endif
/* send */
char uart_putc (char c)
{
    /* Wait until THRE is empyt */
    while (!(GET_UINT32(UART_REG_BASE + UART_USR) & 0x02)); /*lint !e40*/
    /* send one char */
    WRITE_UINT8(c, UART_REG_BASE + UART_DR);
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
        case 1: // only one char
            if (ch != 27) {  //   un special
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
                    {
                        uart_notice_adapt();
                        cnt_ii = 0;
                    }
                    break;
                case 51:
                case 49:
                case 52:
                    break;
            }
            break;
        case 4:
            {
                uart_notice_adapt();
                cnt_ii = 0;
            }
            break;
        default:
            {
                uart_notice_adapt();
                cnt_ii = 0;
            }
            break;
    }
}
extern void dprintf(const char *fmt, ...);

static void uart_irqhandle(void)
{
    UINT8 ch;
    shellCmdLineParse(0, dprintf);
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

#endif
#endif
void uart_init()
{
    unsigned int temp;
    unsigned int divider;
    unsigned char dividerH, dividerL;

    /* disable UART1 FIFO */
    WRITE_UINT32(0, UART_REG_BASE + UART_FCR); /*lint !e40*/

    /* reset and enable UART1 FIFO */
    WRITE_UINT32(0x7, UART_REG_BASE + UART_FCR); /*lint !e40*/

    /* disable UART1 interrupt */
    WRITE_UINT32(0, UART_REG_BASE + UART_IER); /*lint !e40*/

    /* enable DLL and DLH */
    WRITE_UINT32(0x80, UART_REG_BASE + UART_LCR); /*lint !e40*/
    /* Caculate devide */
    temp = 16 * CONSOLE_UART_BAUDRATE;
    divider = CONFIG_UART_CLK_INPUT / temp;
    dividerH = ((divider) & 0xff00) >> 8;
    dividerL = ((divider) & 0x00ff);

    /* configure DLL and DLH */
    WRITE_UINT32(dividerL, UART_REG_BASE + UART_DLL); /*lint !e40*/
    WRITE_UINT32(dividerH, UART_REG_BASE + UART_DLH); /*lint !e40*/

    /* disable DLL and DLH */
    WRITE_UINT32(0x0, UART_REG_BASE + UART_LCR); /*lint !e40*/

    /* 8bit data, 1bit stop,even parity */
    WRITE_UINT32(0x1b, UART_REG_BASE + UART_LCR); /*lint !e40*/

    /* enable UART1 */
    WRITE_UINT32(0x1, UART_REG_BASE + UART_IER); /*lint !e40*/

    (VOID)LOS_EventInit(&g_uartEvent);
}

void uart_interrupt_unmask(void)
{
    HalIrqUnmask(NUM_HAL_INTERRUPT_UART);
}
