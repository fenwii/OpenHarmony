/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2018. All rights reserved.
 * Description: mutex
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

#ifndef _LOS_MUX_PRI_H
#define _LOS_MUX_PRI_H

#include "los_task_pri.h"
#include "los_mux.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_mux
 * Mutex object.
 */
typedef struct {
    UINT8 muxStat;       /**< State OS_MUX_UNUSED,OS_MUX_USED  */
    UINT16 muxCount;     /**< Times of locking a mutex */
    UINT32 muxID;        /**< Handle ID */
    LOS_DL_LIST muxList; /**< Mutex linked list */
    LosTaskCB *owner;    /**< The current thread that is locking a mutex */
    UINT16 priority;     /**< Priority of the thread that is locking a mutex */
} LosMuxCB;

/**
 * @ingroup los_mux
 * Mutex state: not in use.
 */
#define OS_MUX_UNUSED 0

/**
 * @ingroup los_mux
 * Mutex state: in use.
 */
#define OS_MUX_USED   1

extern LosMuxCB *g_allMux;

/**
 * @ingroup los_mux
 * Obtain the pointer to a mutex object of the mutex that has a specified handle.
 */
#define GET_MUX(muxid) (((LosMuxCB *)g_allMux) + (muxid))

/**
 * @ingroup los_mux
 * @brief Initializes the mutex.
 *
 * @par Description:
 * This API is used to initializes the mutex.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval UINT32     Initialization result.
 * @par Dependency:
 * <ul><li>los_mux_pri.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_MuxDelete
 */
extern UINT32 OsMuxInit(VOID *muxArray);

/**
 * @ingroup los_mux
 * Obtain the pointer to the linked list in the mutex pointed to by a specified pointer.
 */
#define GET_MUX_LIST(ptr) LOS_DL_LIST_ENTRY(ptr, LosMuxCB, muxList)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_MUX_PRI_H */
