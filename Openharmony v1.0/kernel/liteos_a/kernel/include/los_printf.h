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

/**
 * @defgroup los_printf Printf
 * @ingroup kernel
 */

#ifndef _LOS_PRINTF_H
#define _LOS_PRINTF_H

#include "sys_config.h"
#ifdef LOSCFG_LIB_LIBC
#include "stdarg.h"
#endif
#include "los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

extern VOID LOS_LkPrint(INT32 level, const CHAR *func, INT32 line, const CHAR *fmt, ...);

#define LOS_EMG_LEVEL    0

#define LOS_COMMON_LEVEL (LOS_EMG_LEVEL + 1)

#define LOS_ERR_LEVEL    (LOS_COMMON_LEVEL + 1)

#define LOS_WARN_LEVEL   (LOS_ERR_LEVEL + 1)

#define LOS_INFO_LEVEL   (LOS_WARN_LEVEL + 1)

#define LOS_DEBUG_LEVEL  (LOS_INFO_LEVEL + 1)

#define LOS_TRACE_LEVEL  (LOS_DEBUG_LEVEL + 1)

#define PRINT_LEVEL      LOS_ERR_LEVEL

typedef VOID (*pf_OUTPUT)(const CHAR *fmt, ...);

/**
 * @ingroup los_printf
 * @brief Format and print data.
 *
 * @par Description:
 * Print argument(s) according to fmt.
 *
 * @attention
 * <ul>
 * <li>None</li>
 * </ul>
 *
 * @param fmt [IN] Type char* controls the ouput as in C printf.
 *
 * @retval None
 * @par Dependency:
 * <ul><li>los_printf.h: the header file that contains the API declaration.</li></ul>
 * @see printf
 */
extern void dprintf(const char *fmt, ...);

#define diag_printf      dprintf

#define PRINT_DEBUG(fmt, args...)    LOS_LkPrint(LOS_DEBUG_LEVEL, __FUNCTION__, __LINE__, fmt, ##args)
#define PRINT_INFO(fmt, args...)     LOS_LkPrint(LOS_INFO_LEVEL, __FUNCTION__, __LINE__, fmt, ##args)
#define PRINT_WARN(fmt, args...)     LOS_LkPrint(LOS_WARN_LEVEL, __FUNCTION__, __LINE__, fmt, ##args)
#define PRINT_ERR(fmt, args...)      LOS_LkPrint(LOS_ERR_LEVEL, __FUNCTION__, __LINE__, fmt, ##args)
#define PRINTK(fmt, args...)         LOS_LkPrint(LOS_COMMON_LEVEL, __FUNCTION__, __LINE__, fmt, ##args)
#define PRINT_EMG(fmt, args...)      LOS_LkPrint(LOS_EMG_LEVEL, __FUNCTION__, __LINE__, fmt, ##args)
#define PRINT_RELEASE(fmt, args...)  LOS_LkPrint(LOS_COMMON_LEVEL, __FUNCTION__, __LINE__, fmt, ##args)
#define PRINT_TRACE(fmt, args...)    LOS_LkPrint(LOS_TRACE_LEVEL, __FUNCTION__, __LINE__, fmt, ##args)

typedef enum {
    NO_OUTPUT = 0,
    UART_OUTPUT = 1,
    CONSOLE_OUTPUT = 2,
    EXC_OUTPUT = 3
} OutputType;

extern VOID OsVprintf(const CHAR *fmt, va_list ap, OutputType type);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_PRINTF_H */
