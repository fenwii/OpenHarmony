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
#include "los_task.h"

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
* Solution: Decrease the maximum number of tasks.
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
#define LOS_ERRNO_CPUP_TASK_PTR_NULL         LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x01)

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
* CPU usage error code: The target thread is not created.
*
* Value: 0x02001e04
*
* Solution: Check whether the target thread is created.
*/
#define LOS_ERRNO_CPUP_THREAD_NO_CREATED     LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x04)

/**
* @ingroup los_cpup
* CPU usage error code: The target task ID is invalid.
*
* Value: 0x02001e05
*
* Solution: Check whether the target task ID is applicable for the current operation.
*/
#define LOS_ERRNO_CPUP_TSK_ID_INVALID        LOS_ERRNO_OS_ERROR(LOS_MOD_CPUP, 0x05)

/**
* @ingroup los_cpup
* Sum of cpup with all tasks. It means the value of cpup is a permillage.
*/
#define LOS_CPUP_PRECISION                   1000

/**
* @ingroup los_cpup
* Multiple of current cpup precision change to percent.
*/
#define LOS_CPUP_PRECISION_MULT              (LOS_CPUP_PRECISION / 100)

/**
 * @ingroup los_cpup
 * Count the CPU usage structures of all tasks.
 */
typedef struct tagCpupInfo {
    UINT16 usStatus;            /**< save the cur task status     */
    UINT32 uwUsage;             /**< Usage. The value range is [0,1000].   */
} CPUP_INFO_S;

/**
 * @ingroup los_monitor
 * Type of the CPU usage query.
 */
typedef enum {
    SYS_CPU_USAGE = 0,   /* system cpu occupancy rate */
    TASK_CPU_USAGE,      /* task cpu occupancy rate */
} CPUP_TYPE_E;

/**
 * @ingroup los_monitor
 * Mode of the CPU usage query.
 */
typedef enum {
    CPUP_IN_10S = 0,     /* cpu occupancy rate in 10s */
    CPUP_IN_1S,          /* cpu occupancy rate in 1s */
    CPUP_LESS_THAN_1S,   /* cpu occupancy rate less than 1s, if the input mode is none of them, it will be this. */
} CPUP_MODE_E;

/**
 * @ingroup los_cpup
 * @brief Obtain the current CPU usage.
 *
 * @par Description:
 * This API is used to obtain the current CPU usage.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise, error codes will be returned.</li>
 * <li> The precision of the CPU usage can be adjusted by changing the value of the CPUP_PRECISION macro.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval #OS_ERRNO_CPUP_NO_INIT           0x02001e02: The CPU usage is not initialized.
 * @retval #cpup                            [0,100], current CPU usage, of which the precision is adjustable.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_SysCpuUsage
 */
extern UINT32 LOS_SysCpuUsage(VOID);

/**
 * @ingroup los_cpup
 * @brief Obtain the historical CPU usage.
 *
 * @par Description:
 * This API is used to obtain the historical CPU usage.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise, the CPU usage fails to be obtained.</li>
 * </ul>
 *
 * @param  mode     [IN] UINT16. Task mode. The parameter value 0 indicates that the CPU usage within 10s will be
 * obtained, and the parameter value 1 indicates that the CPU usage in the former 1s will be obtained. Other values
 * indicate that the CPU usage in the period that is less than 1s will be obtained.
 *
 * @retval #OS_ERRNO_CPUP_NO_INIT           0x02001e02: The CPU usage is not initialized.
 * @retval #cpup                            [0,100], historical CPU usage, of which the precision is adjustable.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_HistoryTaskCpuUsage
 */
extern UINT32 LOS_HistorySysCpuUsage(UINT16 mode);

/**
 * @ingroup los_cpup
 * @brief Obtain the CPU usage of a specified task.
 *
 * @par Description:
 * This API is used to obtain the CPU usage of a task specified by a passed-in task ID.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise, the CPU usage fails to be obtained.</li>
 * <li>The passed-in task ID must be valid and the task specified by the task ID must be created. Otherwise,
 * the CPU usage fails to be obtained.</li>
 * </ul>
 *
 * @param taskID   [IN] UINT32. Task ID.
 *
 * @retval #OS_ERRNO_CPUP_NO_INIT             0x02001e02: The CPU usage is not initialized.
 * @retval #OS_ERRNO_CPUP_TSK_ID_INVALID      0x02001e05: The target task ID is invalid.
 * @retval #OS_ERRNO_CPUP_THREAD_NO_CREATED   0x02001e04: The target thread is not created.
 * @retval #cpup                              [0,100], CPU usage of the specified task.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_HistoryTaskCpuUsage
 */
extern UINT32 LOS_TaskCpuUsage(UINT32 taskID);

/**
 * @ingroup los_cpup
 * @brief  Obtain the historical CPU usage of a specified task.
 *
 * @par Description:
 * This API is used to obtain the historical CPU usage of a task specified by a passed-in task ID.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise,
 * the CPU usage fails to be obtained.</li>
 * <li>The passed-in task ID must be valid and the task specified by the task ID must be created. Otherwise,
 * the CPU usage fails to be obtained.</li>
 * </ul>
 *
 * @param taskID   [IN] UINT32. Task ID.
 * @param mode     [IN] UINT16. Task mode. The parameter value 0 indicates that the CPU usage within 10s
 * will be obtained, and the parameter value 1 indicates that the CPU usage in the former 1s will be obtained.
 * Other values indicate that the CPU usage in the period that is less than 1s will be obtained.
 *
 * @retval #OS_ERRNO_CPUP_NO_INIT             0x02001e02: The CPU usage is not initialized.
 * @retval #OS_ERRNO_CPUP_TSK_ID_INVALID      0x02001e05: The target task ID is invalid.
 * @retval #OS_ERRNO_CPUP_THREAD_NO_CREATED   0x02001e04: The target thread is not created.
 * @retval #cpup                              [0,100], CPU usage of the specified task.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_HistorySysCpuUsage
 */
extern UINT32 LOS_HistoryTaskCpuUsage(UINT32 taskID, UINT16 mode);

/**
 * @ingroup los_cpup
 * @brief Obtain the CPU usage of all tasks.
 *
 * @par Description:
 * This API is used to obtain the CPU usage of all tasks according to maximum number of threads.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise, the CPU usage fails to be obtained.</li>
 * <li>The input parameter pointer must not be NULL, Otherwise, the CPU usage fails to be obtained.</li>
 * </ul>
 *
 * @param cpupInfo    [OUT]Type.   CPUP_INFO_S* Pointer to the task CPUP information structure to be obtained.
 * @param mode        [IN] UINT16. Task mode. The parameter value 0 indicates that the CPU usage within 10s
 * will be obtained, and the parameter value 1 indicates that the CPU usage in the former 1s will be obtained.
 * Other values indicate that the CPU usage in the period that is less than 1s will be obtained.
 *
 * @retval #OS_ERRNO_CPUP_NO_INIT           0x02001e02: The CPU usage is not initialized.
 * @retval #OS_ERRNO_CPUP_TASK_PTR_NULL     0x02001e01: The input parameter pointer is NULL.
 * @retval #LOS_OK                          0x00000000: The CPU usage of all tasks is successfully obtained.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_SysCpuUsage
 */
extern UINT32 LOS_AllTaskCpuUsage(CPUP_INFO_S *cpupInfo, UINT16 mode);

/**
 * @ingroup los_monitor
 * @brief Obtain CPU usage history of certain task.
 *
 * @par Description:
 * This API is used to obtain CPU usage history of certain task.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized. Otherwise, -1 will be returned.</li>
 * <li> Only in SYS_CPU_USAGE type, uwTaskID is invalid.</li>
 * </ul>
 *
 * @param type        [IN] cpup type, SYS_CPU_USAGE and TASK_CPU_USAGE
 * @param mode        [IN] mode,CPUP_IN_10S = usage in 10s,CPUP_IN_1S = usage in last 1s,
 * CPUP_LESS_THAN_1S = less than 1s, if the inpuit mode is none of them, it will be as CPUP_LESS_THAN_1S.
 * @param taskID      [IN] task ID, Only in SYS_CPU_USAGE type, taskID is invalid
 *
 * @retval #OS_ERROR           -1:CPU usage info obtain failed.
 * @retval #LOS_OK              0:CPU usage info is successfully obtained.
 * @par Dependency:
 * <ul><li>los_monitor.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_CpupUsageMonitor
 */
extern UINT32 LOS_CpupUsageMonitor(CPUP_TYPE_E type, CPUP_MODE_E mode, UINT32 taskID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_CPUP_H */
