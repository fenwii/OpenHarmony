/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: los_printf
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
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
 * --------------------------------------------------------------------------- */

/**
 * @defgroup los_printf Printf
 * @ingroup kernel
 */

#ifndef _LOS_PRINTF_H
#define _LOS_PRINTF_H

#include "los_typedef.h"
#include "los_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define LOS_EMG_LEVEL   0

#define LOS_COMMOM_LEVEL   (LOS_EMG_LEVEL + 1)

#define LOS_ERR_LEVEL   (LOS_COMMOM_LEVEL + 1)

#define LOS_WARN_LEVEL  (LOS_ERR_LEVEL + 1)

#define LOS_INFO_LEVEL  (LOS_WARN_LEVEL + 1)

#define LOS_DEBUG_LEVEL (LOS_INFO_LEVEL + 1)

#ifdef GCOVERAGE
#define PRINT_LEVEL 0
#else
#define PRINT_LEVEL LOS_ERR_LEVEL
#endif

extern int printf(const char *fmt, ...);
#define  los_printf (VOID)printf

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
#define diag_printf los_printf

#if PRINT_LEVEL < LOS_DEBUG_LEVEL
#define PRINT_DEBUG(fmt, args...)
#else
#define PRINT_DEBUG(fmt, args...)   do { (los_printf("[DEBUG] "), los_printf(fmt, ##args)); } while (0)
#endif

#if PRINT_LEVEL < LOS_INFO_LEVEL
#define PRINT_INFO(fmt, args...)
#else
#define PRINT_INFO(fmt, args...)    do { (los_printf("[INFO] "), los_printf(fmt, ##args)); } while (0)
#endif

#if PRINT_LEVEL < LOS_WARN_LEVEL
#define PRINT_WARN(fmt, args...)
#else
#define PRINT_WARN(fmt, args...)    do { (los_printf("[WARN] "), los_printf(fmt, ##args)); } while (0)
#endif

#if PRINT_LEVEL < LOS_ERR_LEVEL
#define PRINT_ERR(fmt, args...)
#else
#define PRINT_ERR(fmt, args...)     do { (los_printf("[ERR] "), los_printf(fmt, ##args)); } while (0)
#endif

#if PRINT_LEVEL < LOS_COMMOM_LEVEL
#define PRINTK(fmt, args...)
#else
#define PRINTK(fmt, args...)     los_printf(fmt, ##args)
#endif

#if PRINT_LEVEL < LOS_EMG_LEVEL
#define PRINT_EMG(fmt, args...)
#else
#define PRINT_EMG(fmt, args...)     do { (los_printf("[EMG] "), los_printf(fmt, ##args)); } while (0)
#endif

#define PRINT_RELEASE(fmt, args...)   los_printf(fmt, ##args)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_PRINTF_H */
