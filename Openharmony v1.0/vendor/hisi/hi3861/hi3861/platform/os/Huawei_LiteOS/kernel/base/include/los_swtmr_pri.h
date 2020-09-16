/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2018. All rights reserved.
 * Description: Software Timer Manager
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

#ifndef _LOS_SWTMR_PRI_H
#define _LOS_SWTMR_PRI_H

#include "los_swtmr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_swtmr
 * Software timer state
 */
enum SwtmrState {
    OS_SWTMR_STATUS_UNUSED,             /**< The software timer is not used. */
    OS_SWTMR_STATUS_CREATED,            /**< The software timer is created. */
    OS_SWTMR_STATUS_TICKING             /**< The software timer is timing. */
};

/**
 * @ingroup los_swtmr
 * Structure of the callback function that handles software timer timeout
 */
typedef struct {
    SWTMR_PROC_FUNC     handler;        /**< Callback function that handles software timer timeout */
    UINT32              arg;            /**< Parameter passed in when the callback function
                                             that handles software timer timeout is called */
} SwtmrHandlerItem;

extern SWTMR_CTRL_S *g_swtmrCBArray;

#define OS_SWT_FROM_SID(swtmrId)    ((SWTMR_CTRL_S *)g_swtmrCBArray + ((swtmrId) % LOSCFG_BASE_CORE_SWTMR_LIMIT))

/**
 * @ingroup los_swtmr
 * @brief Scan a software timer.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to scan a software timer when a Tick interrupt occurs and determine whether the software timer
   expires.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_swtmr_pri.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_SwtmrStop
 */
extern UINT32 OsSwtmrScan(VOID);

/**
 * @ingroup los_swtmr
 * @brief Initialization software timer.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to initialization software.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_swtmr_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsSwtmrInit(VOID *swtmrArray);

/**
 * @ingroup los_swtmr
 * @brief Initialization software timer save array.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to initialization software timer save array.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval LOS_OK or LOS_ERRNO_SWTMR_NO_MEMORY.
 * @par Dependency:
 * <ul><li>los_swtmr_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsSwtmrSaveInit(VOID);

/**
 * @ingroup los_swtmr
 * @brief Get next timeout.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get next timeout.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_swtmr_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsSwtmrGetNextTimeout(VOID);

/**
 * @ingroup los_swtmr
 * @brief Adjust software timer list.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to adjust software timer list.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  sleepTime    [IN]    UINT32 Sleep time.
 *
 * @retval UINT32    Sleep time.
 * @par Dependency:
 * <ul><li>los_swtmr_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID OsSwtmrAdjust_Patch(UINT32 sleepTime);

/**
 * @ingroup los_swtmr
 * Handle function of software timer task .
 *
 * @par Description:
 * <ul>
 * <li>This API is used to handle the overtime software timer.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_swtmr.inc: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID OsSwtmrTask(VOID);

/**
 * @ingroup los_swtmr
 * Save enable timer id when start sleep.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to save enable timer id when start sleep.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_swtmr.inc: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID OsSwtmrSave(VOID);

extern SWTMR_CTRL_S *g_swtmrSortList;

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_SWTMR_PRI_H */
