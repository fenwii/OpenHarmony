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

#include "amba_pl011.h"
#include "asm/platform.h"
#include "uart.h"
#include "los_hwi.h"
#include "los_spinlock.h"
#include "los_event.h"
#include "los_task_pri.h"

EVENT_CB_S g_stShellEvent;

CHAR g_inputCmd[CMD_LENGTH];
INT32 g_inputIdx = 0;
__attribute__ ((section(".data"))) UINT32 g_uart_fputc_en = 1;

#define REG32(addr) ((volatile UINT32 *)(UINTPTR)(addr))
#define UARTREG(base, reg)  (*REG32((base) + (reg)))
#define UART_FR_TXFF (0x1U << 5)

STATIC VOID UartPutcReg(UINTPTR base, CHAR c)
{
    /* Spin while fifo is full */
    while (UARTREG(base, UART_FR) & UART_FR_TXFF) {}
    UARTREG(base, UART_DR) = c;
}

STATIC INLINE UINTPTR uart_to_ptr(UINTPTR n)
{
    (VOID)n;
    return UART_REG_BASE;
}

INT32 uart_putc(INT32 port, CHAR c)
{
    UINTPTR base = uart_to_ptr((UINT32)port);
    UartPutcReg(base, c);
    return 1;
}

CHAR uart_fputc(CHAR c, VOID *f)
{
    (VOID)f;
    if (g_uart_fputc_en == 1) {
        if (c == '\n') {
            (VOID)uart_putc(0, '\r');
        }
        return (uart_putc(0, (c)));
    } else {
        return 0;
    }
}

LITE_OS_SEC_BSS STATIC SPIN_LOCK_INIT(g_uartOutputSpin);

STATIC VOID UartPutStr(UINTPTR base, const CHAR *s, UINT32 len)
{
    UINT32 i;

    for (i = 0; i < len; i++) {
        if (*(s + i) == '\n') {
            UartPutcReg(base, '\r');
        }
        UartPutcReg(base, *(s + i));
    }
}

UINT32 UartPutsReg(UINTPTR base, const CHAR *s, UINT32 len, BOOL isLock)
{
    UINT32 intSave;

    if (g_uart_fputc_en == 0) {
        return 0;
    }

    if (isLock) {
        LOS_SpinLockSave(&g_uartOutputSpin, &intSave);
        UartPutStr(base, s, len);
        LOS_SpinUnlockRestore(&g_uartOutputSpin, intSave);
    } else {
        UartPutStr(base, s, len);
    }

    return len;
}

VOID UartPuts(const CHAR *s, UINT32 len, BOOL isLock)
{
    UINTPTR base = uart_to_ptr(0);
    (VOID)UartPutsReg(base, s, len, isLock);
}

INT32 uart_puts(const CHAR *s, UINTPTR len, VOID *state)
{
    (VOID)state;
    UINTPTR i;

    for (i = 0; i < len; i++) {
        if (*(s + i) != '\0') {
            if (*(s + i) == '\n') {
                (VOID)uart_fputc('\r', NULL);
            }

            (VOID)uart_fputc(*(s + i), NULL);
        }
    }

    return (INT32)len;
}

VOID uart_handler(VOID)
{
    CHAR c;
    UINTPTR base = uart_to_ptr(0);

    c = UARTREG(base, UART_DR);

    switch (c) {
        case '\r':
        case '\n':
            if (g_inputIdx < CMD_LENGTH - 1) {
                g_inputCmd[g_inputIdx++] = '\0';
                LOS_EventWrite(&g_stShellEvent, 0x1);
                (VOID)uart_putc(0, '\r');
                (VOID)uart_putc(0, '\n');
            }
            break;
        case 0x8:   /* backspace */
        case 0x7f:  /* delete */
            if (g_inputIdx > 0) {
                g_inputIdx--;
                (VOID)uart_putc(0, '\b');
                (VOID)uart_putc(0, ' ');
                (VOID)uart_putc(0, '\b');
            }
            break;
        default:
            if (g_inputIdx < CMD_LENGTH - 1) {
                (VOID)uart_putc(0, c);
                g_inputCmd[g_inputIdx++] = c;
            }
    }
}

VOID uart_early_init(VOID)
{
    /* enable uart transmit */
    UARTREG(UART_REG_BASE, UART_CR) = (1 << 8) | (1 << 0);
}

VOID uart_init(VOID)
{
    UINT32 ret;

    /* uart interrupt priority should be the highest in interrupt preemption mode */
    ret = LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, (HWI_PROC_FUNC)uart_handler, NULL);
    if (ret != LOS_OK) {
        PRINT_ERR("%s,%d, uart interrupt created error:%x\n", __FUNCTION__, __LINE__, ret);
    } else {
        /* clear all irqs */
        UARTREG(UART_REG_BASE, UART_ICR) = 0x3ff;

        /* set fifo trigger level */
        UARTREG(UART_REG_BASE, UART_IFLS) = 0;

        /* enable rx interrupt */
        UARTREG(UART_REG_BASE, UART_IMSC) = (1 << 4 | 1 << 6);

        /* enable receive */
        UARTREG(UART_REG_BASE, UART_CR) |= (1 << 9);

        HalIrqUnmask(NUM_HAL_INTERRUPT_UART);
    }
}
