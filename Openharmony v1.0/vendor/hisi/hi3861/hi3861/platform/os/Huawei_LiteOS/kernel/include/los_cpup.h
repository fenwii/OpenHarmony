/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 * Description : LiteOS Cpu Usage Calculation Module Headfile For User
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
 * @defgroup los_cpup CPU usage
 * @ingroup kernel
 */

#ifndef _LOS_CPUP_H
#define _LOS_CPUP_H

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
    UINT64 ullAllTime;          /**< Time before a task is invoked */
} CPUP_INFO_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_CPUP_H */
