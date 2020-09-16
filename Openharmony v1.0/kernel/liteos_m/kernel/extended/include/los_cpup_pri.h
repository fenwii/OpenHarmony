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

#ifndef _LOS_CPUP_PRI_H
#define _LOS_CPUP_PRI_H

#include "los_cpup.h"
#include "los_tick_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


/**
 * @ingroup los_cpup
 * Number of historical running time records
 */
#define OS_CPUP_HISTORY_RECORD_NUM   10

/**
 * @ingroup los_cpup
 * Count the CPU usage structures of a task.
 */
typedef struct {
    UINT32 cpupID;                                        /**< Task ID */
    UINT16 status;                                        /**< Task status */
    UINT64 allTime;                                       /**< Total running time */
    UINT64 startTime;                                     /**< Time before a task is invoked */
    UINT64 historyTime[OS_CPUP_HISTORY_RECORD_NUM];       /**< Historical running time */
} OsCpupCB;

extern OsCpupCB    *g_cpup;

/**
 * @ingroup los_cpup
 * @brief Initialization cpup.
 *
 * @par Description:
 * This API is used to initialization cpup.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval UINT32   Initialization result.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsCpupInit(VOID);

/**
 * @ingroup los_cpup
 * @brief Start task to get cycles count in current task ending.
 *
 * @par Description:
 * This API is used to start task to get cycles count in current task ending.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID OsTskCycleEndStart(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_CPUP_PRI_H */
