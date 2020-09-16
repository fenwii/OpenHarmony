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
 * @defgroup los_cpup CPU usage
 * @ingroup kernel
 */

#ifndef _LOS_CPUP_H
#define _LOS_CPUP_H

#include "los_hwi.h"
#include "los_base.h"
#include "los_sys.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_cpup
 * CPU usage error code: The request for memory fails.
 *
 * Value: 0x02001e00
 *
 * Solution: Decrease the maximum number of processes.
 */
#define LOS_ERRNO_CPUP_NO_MEMORY             LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x00)

/**
 * @ingroup los_cpup
 * CPU usage error code: The pointer to an input parameter is NULL.
 *
 * Value: 0x02001e01
 *
 * Solution: Check whether the pointer to the input parameter is usable.
 */
#define LOS_ERRNO_CPUP_PROCESS_PTR_NULL         LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x01)

/**
 * @ingroup los_cpup
 * CPU usage error code: The CPU usage is not initialized.
 *
 * Value: 0x02001e02
 *
 * Solution: Check whether the CPU usage is initialized.
 */
#define LOS_ERRNO_CPUP_NO_INIT               LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x02)

/**
 * @ingroup los_cpup
 * CPU usage error code: The number of threads is invalid.
 *
 * Value: 0x02001e03
 *
 * Solution: Check whether the number of threads is applicable for the current operation.
 */
#define LOS_ERRNO_CPUP_MAXNUM_INVALID        LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x03)

/**
 * @ingroup los_cpup
 * CPU usage error code: The target process is not created.
 *
 * Value: 0x02001e04
 *
 * Solution: Check whether the target process is created.
 */
#define LOS_ERRNO_CPUP_PROCESS_NO_CREATED     LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x04)

/**
 * @ingroup los_cpup
 * CPU usage error code: The target process ID is invalid.
 *
 * Value: 0x02001e05
 *
 * Solution: Check whether the target process ID is applicable for the current operation.
 */
#define LOS_ERRNO_CPUP_PID_INVALID        LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x05)

/**
 * @ingroup los_cpup
 * Sum of single core cpup with all processes. It means the value of cpup is a permillage.
 */
#define LOS_CPUP_SINGLE_CORE_PRECISION       1000

/**
 * @ingroup los_cpup
 * Multiple of current cpup precision change to percent.
 */
#define LOS_CPUP_PRECISION_MULT              (LOS_CPUP_SINGLE_CORE_PRECISION / 100)

/**
 * @ingroup los_cpup
 * Sum of all core cpup with all processes. It means the value of cpup is a permillage.
 */
#define LOS_CPUP_PRECISION                   (LOS_CPUP_SINGLE_CORE_PRECISION * LOSCFG_KERNEL_CORE_NUM)

/**
 * @ingroup los_cpup
 * Count the CPU usage structures of all processs.
 */
typedef struct tagCpupInfo {
    UINT16 usStatus; /**< Save the cur process status     */
    UINT32 uwUsage;  /**< Usage. The value range is [0,1000].   */
} CPUP_INFO_S;

/**
 * @ingroup los_cpup
 * Query the CPU usage of the system.
 */
enum {
    CPUP_LAST_TEN_SECONDS = 0, /**< Display CPU usage in the last ten seconds. */
    CPUP_LAST_ONE_SECONDS = 1, /**< Display CPU usage in the last one seconds. */
    CPUP_ALL_TIME = 0xffff     /**< Display CPU usage from system startup to now. */
};


/**
 * @ingroup los_cpup
 * @brief Obtain the historical CPU usage.
 *
 * @par Description:
 * This API is used to obtain the historical CPU usage.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise, the CPU usage fails to be
 * obtained.</li>
 * </ul>
 *
 * @param  mode     [IN] UINT16. process mode. The parameter value 0 indicates that the CPU usage within 10s will be
 *                               obtained, and the parameter value 1 indicates that the CPU usage in the former 1s will
 *                               be obtained. Other values indicate that the CPU usage in all time will be obtained.
 *
 * @retval #LOS_ERRNO_CPUP_NO_INIT           The CPU usage is not initialized.
 * @retval #UINT32                           [0,100], historical CPU usage, of which the precision is adjustable.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 LOS_HistorySysCpuUsage(UINT16 mode);

/**
 * @ingroup los_cpup
 * @brief  Obtain the historical CPU usage of a specified process.
 *
 * @par Description:
 * This API is used to obtain the historical CPU usage of a process specified by a passed-in process ID.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise,
 * the CPU usage fails to be obtained.</li>
 * <li>The passed-in process ID must be valid and the process specified by the process ID must be created. Otherwise,
 * the CPU usage fails to be obtained.</li>
 * </ul>
 *
 * @param pid      [IN] UINT32. process ID.
 * @param mode     [IN] UINT16. process mode. The parameter value 0 indicates that the CPU usage within 10s will be
 *                              obtained, and the parameter value 1 indicates that the CPU usage in the former 1s will
 *                              be obtained. Other values indicate that the CPU usage in the period that is less than
 *                              1s will be obtained.
 *
 * @retval #LOS_ERRNO_CPUP_NO_INIT                  The CPU usage is not initialized.
 * @retval #LOS_ERRNO_CPUP_PID_INVALID              The target process ID is invalid.
 * @retval #LOS_ERRNO_CPUP_PROCESS_NO_CREATED       The target process is not created.
 * @retval #UINT32                                  [0,100], CPU usage of the specified process.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 LOS_HistoryProcessCpuUsage(UINT32 pid, UINT16 mode);

/**
 * @ingroup los_cpup
 * @brief Obtain the CPU usage of processes and hwi.
 *
 * @par Description:
 * This API is used to obtain the CPU usage of processes and hwi according to the passed-in maximum number and usFlag
 * which indicate obtain the cpup usage of process or hwi.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise, the CPU usage fails to be
 * obtained.</li>
 * <li>The input parameter pointer must not be NULL, and the maximum number must be usable. Otherwise, the CPU usage
 * fails to be obtained.</li>
 * <li>The input parameter pointer should point to the structure array whose size be greater than
 * (maxNum * sizeof (CPUP_INFO_S)).</li>
 * </ul>
 *
 * @param maxNum     [IN] UINT16. The Maximum number of threads or hwis.
 * @param cpupInfo   [OUT]Type.   CPUP_INFO_S* Pointer to the CPUP information structure to be obtained.
 * @param mode       [IN] UINT16. Time mode. The parameter value 0 indicates that the CPU usage within 10s will be
 *                                obtained, and the parameter value 1 indicates that the CPU usage in the former 1s
 *                                will be obtained.Other values indicate that the CPU usage in all time will be
 *                                obtained.
 * @param flag       [IN] UINT16. The parameter value 0 indicates that the CPU usage of hwi. Other values indicate that
 *                                the CPU usage of process.
 *
 * @retval #LOS_ERRNO_CPUP_NO_INIT                  The CPU usage is not initialized.
 * @retval #LOS_ERRNO_CPUP_PROCESS_PTR_NULL         The input parameter pointer is NULL.
 * @retval #LOS_ERRNO_CPUP_MAXNUM_INVALID           The maximum number of threads or hwi is invalid.
 * @retval #LOS_OK                                  The CPU usage of all processes or hwi is successfully obtained.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 LOS_AllCpuUsage(UINT16 maxNum, CPUP_INFO_S *cpupInfo, UINT16 mode, UINT16 flag);

/**
 * @ingroup los_cpup
 * @brief Reset the data of CPU usage.
 *
 * @par Description:
 * This API is used to reset the data of CPU usage.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval #None.
 *
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern VOID LOS_CpupReset(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif
