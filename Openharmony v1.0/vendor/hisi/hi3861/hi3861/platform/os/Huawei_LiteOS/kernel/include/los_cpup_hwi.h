/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 * Description : LiteOS Cpu Usage Hwi Headfile For User
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
 * @defgroup los_cpup CPU usage hwi
 * @ingroup kernel
 */

#ifndef _LOS_CPUP_HWI_H
#define _LOS_CPUP_HWI_H

#include "los_cpup.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_cpup
 * @brief Obtain the CPU usage of all tasks.
 *
 * @par Description:
 * This API is used to obtain the CPU usage of all tasks according to the passed-in maximum number of threads.
 * @attention
 * <ul>
 * <li>This API can be called only after the CPU usage is initialized.
 * Otherwise, the CPU usage fails to be obtained.</li>
 * <li>The input parameter pointer must not be NULL, and the maximum number of threads must be usable.
 * Otherwise, the CPU usage fails to be obtained.</li>
 * <li>The input parameter pointer should point to the structure array who's size be greater than
 * (maxNum * sizeof (CPUP_INFO_S)).</li>
 * </ul>
 *
 * @param maxNum      [IN] UINT16. The Maximum number of threads.
 * @param cpupInfo    [OUT]Type.   CPUP_INFO_S* Pointer to the task CPUP information structure to be obtained.
 *
 * @retval #LOS_ERRNO_CPUP_NO_INIT                  The CPU usage is not initialized.
 * @retval #LOS_ERRNO_CPUP_TASK_PTR_NULL            The input parameter pointer is NULL.
 * @retval #LOS_ERRNO_CPUP_MAXNUM_INVALID           The maximum number of threads is invalid.
 * @retval #LOS_OK                                  The CPU usage of all tasks is successfully obtained.
 * @par Dependency:
 * <ul><li>los_cpup.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 LOS_AllTaskCpuUsage(UINT16 maxNum, CPUP_INFO_S *cpupInfo);

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

#endif /* _LOS_CPUP_HWI_H */

