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

#ifndef _LOS_SYS_PRI_H
#define _LOS_SYS_PRI_H

#include "los_base_pri.h"
#include "los_tick_pri.h"
#include "los_sys.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_sys
 * Number of operable bits of a 32-bit operand
 */
#define OS_SYS_MV_32_BIT       32

/**
 * @ingroup los_sys
 * Number of milliseconds in one second.
 */
#define OS_SYS_MS_PER_SECOND   1000

/**
 * @ingroup los_sys
 * Number of microseconds in one second.
 */
#define OS_SYS_US_PER_SECOND   1000000

/**
 * @ingroup los_sys
 * The maximum length of name.
 */
#define OS_SYS_APPVER_NAME_MAX 64

/**
 * @ingroup los_sys
 * The magic word.
 */
#define OS_SYS_MAGIC_WORD      0xAAAAAAAA

/**
 * @ingroup los_sys
 * The initialization value of stack space.
 */
#define OS_SYS_EMPTY_STACK     0xCACACACA

/**
 * @ingroup los_sys
 * @brief Convert cycles to milliseconds.
 *
 * @par Description:
 * This API is used to convert cycles to milliseconds.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  cpuTick  [IN]  Number of CPU cycles.
 * @param  msHi     [OUT] Upper 32 bits of the number of milliseconds.
 * @param  msLo     [OUT] Lower 32 bits of the number of milliseconds.
 *
 * @retval #LOS_ERRNO_SYS_PTR_NULL    0x02000011: Invalid parameter.
 * @retval #LOS_OK                   0:  Cycles are successfully converted to microseconds.
 * @par Dependency:
 * <ul><li>los_sys_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsCpuTick2MS(CpuTick *cpuTick, UINT32 *msHi, UINT32 *msLo);

/**
 * @ingroup los_sys
 * @brief Convert cycles to microseconds.
 *
 * @par Description:
 * This API is used to convert cycles to microseconds.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  cpuTick  [IN]  Number of CPU cycles.
 * @param  usHi     [OUT] Upper 32 bits of the number of microseconds.
 * @param  usLo     [OUT] Lower 32 bits of the number of microseconds.
 *
 * @retval #LOS_ERRNO_SYS_PTR_NULL    0x02000011: Invalid parameter.
 * @retval #LOS_OK                   0: Cycles are successfully converted to microseconds.
 * @par Dependency:
 * <ul><li>los_sys_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsCpuTick2US(CpuTick *cpuTick, UINT32 *usHi, UINT32 *usLo);

/**
 * @ingroup los_sys
 * @brief Convert cycles to milliseconds.
 *
 * @par Description:
 * This API is used to convert cycles to milliseconds.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  cycle     [IN] Number of cycles.
 *
 * @retval Number of milliseconds obtained through the conversion.    Cycles are successfully converted to milliseconds.
 * @par Dependency:
 * <ul><li>los_sys_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
STATIC_INLINE UINT64 OsCycle2MS(UINT64 cycle)
{
    return (UINT64)((cycle / (g_sysClock / OS_SYS_MS_PER_SECOND)));
}

/**
 * @ingroup los_sys
 * @brief Convert cycles to microseconds.
 *
 * @par Description:
 * This API is used to convert cycles to microseconds.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  cycle     [IN] Number of cycles.
 *
 * @retval Number of microseconds obtained through the conversion. Cycles are successfully converted to microseconds.
 * @par Dependency:
 * <ul><li>los_sys_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
STATIC_INLINE UINT64 OsCycle2US(UINT64 cycle)
{
    UINT64 tmp = g_sysClock / OS_SYS_US_PER_SECOND;
    if (tmp == 0) {
        return 0;
    }
    return (UINT64)(cycle / tmp);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_SYS_PRI_H */
