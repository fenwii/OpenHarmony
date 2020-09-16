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

#include "at_printf.h"

#include <hi3861_platform_base.h>
#include <serial_dw.h>
#include <stdarg.h>

#include "hi_at.h"

uintptr_t g_at_uart_baseaddr = HI_UART1_REG_BASE;
uintptr_t g_sysinfo_uart_baseaddr = HI_UART0_REG_BASE;

/* send */
hi_void serial_putc_at(hi_char c)
{
    /* Wait until there is space in the FIFO */
    while ((hi_reg_read_val16(g_at_uart_baseaddr + UART_FR) & UARTFR_TXFF_MASK) != 0) {}

    /* Send the character */
    hi_reg_write16(g_at_uart_baseaddr + UART_DR, (hi_uchar)c);
}

hi_s32 uart_puts_at(const hi_char *ptr, hi_u32 len, const hi_void *state)
{
    hi_s32 len_ret = (hi_s32)len;
    hi_at_output_func at_output_func = hi_at_get_register_output_func();

    (hi_void)state;
    while (len-- && (*ptr != 0)) {
        if (*ptr == '\n') {
            if (at_output_func == HI_NULL) {
                serial_putc_at(*ptr++);
            } else {
                at_output_func((const hi_u8*)ptr++, 1);
            }
        } else {
            if (at_output_func == HI_NULL) {
                serial_putc_at(*ptr++);
            } else {
                at_output_func((const hi_u8*)ptr++, 1);
            }
        }
    }
    return len_ret;
}


hi_s32 hi_at_printf(const hi_char *fmt, ...)
{
    va_list ap = 0;
    hi_s32 len;
    va_start(ap, fmt);

#if defined(CONFIG_AT_COMMAND) || defined(CONFIG_FACTORY_TEST_MODE)
    OUTPUT_FUNC fn_put = (OUTPUT_FUNC)uart_puts_at;
    len = __dprintf(fmt, ap, fn_put, (void *)NULL);
#else
    len = 0;
#endif

    va_end(ap);
    return len;
}

/* send */
hi_void serial_putc_crashinfo(hi_char c)
{
#if defined(CONFIG_AT_COMMAND) || defined(CONFIG_FACTORY_TEST_MODE)
    /* Wait until there is space in the FIFO */
    while ((hi_reg_read_val16(g_at_uart_baseaddr + UART_FR) & UARTFR_TXFF_MASK) != 0) {}

    /* Send the character */
    hi_reg_write16(g_at_uart_baseaddr + UART_DR, (hi_uchar)c);
#else
    /* Wait until there is space in the FIFO */
    while ((hi_reg_read_val16(g_sysinfo_uart_baseaddr + UART_FR) & UARTFR_TXFF_MASK) != 0) {}

    /* Send the character */
    hi_reg_write16(g_sysinfo_uart_baseaddr + UART_DR, (hi_uchar)c);
#endif
}

hi_s32 uart_puts_sysinfo(const hi_char *ptr, hi_u32 len, const hi_void *state)
{
    hi_s32 len_ret = (hi_s32)len;
    hi_at_output_func at_output_func = hi_at_get_register_output_func();

    (hi_void)state;
    while (len-- && (*ptr != 0)) {
        if (*ptr == '\n') {
            if (at_output_func == HI_NULL) {
                serial_putc_crashinfo('\r');
                serial_putc_crashinfo(*ptr++);
            } else {
#if defined(CONFIG_AT_COMMAND) || defined(CONFIG_FACTORY_TEST_MODE)
                hi_char tmp_char = '\r';
                at_output_func((const hi_u8*)&tmp_char, 1);
                at_output_func((const hi_u8*)ptr++, 1);
#else
                serial_putc_crashinfo('\r');
                serial_putc_crashinfo(*ptr++);
#endif
            }
        } else {
            if (at_output_func == HI_NULL) {
                serial_putc_crashinfo(*ptr++);
            } else {
#if defined(CONFIG_AT_COMMAND) || defined(CONFIG_FACTORY_TEST_MODE)
                at_output_func((const hi_u8*)ptr++, 1);
#else
                serial_putc_crashinfo(*ptr++);
#endif
            }
        }
    }
    return len_ret;
}

hi_s32 hi_at_printf_crashinfo(const hi_char *fmt, ...)
{
    va_list ap = 0;
    hi_s32 len;
    va_start(ap, fmt);

    OUTPUT_FUNC fn_put = (OUTPUT_FUNC)uart_puts_sysinfo;
    len = __dprintf(fmt, ap, fn_put, (void *)NULL);

    va_end(ap);
    return len;
}

