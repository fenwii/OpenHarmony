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

#ifndef __AT_PRINTF_H__
#define __AT_PRINTF_H__

#include <printf.h>
#include "hi_types.h"

hi_void serial_putc_at(hi_char c);

extern uintptr_t g_at_uart_baseaddr;
extern LITE_OS_SEC_TEXT INT32 __dprintf(const CHAR *format, va_list arg_v, OUTPUT_FUNC pFputc, VOID *cookie);

hi_s32 hi_at_printf_crashinfo(const hi_char *fmt, ...);

#endif
