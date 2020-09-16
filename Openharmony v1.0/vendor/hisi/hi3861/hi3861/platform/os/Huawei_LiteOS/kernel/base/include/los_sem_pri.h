/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2018. All rights reserved.
 * Description: semaphore
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

#ifndef _LOS_SEM_PRI_H
#define _LOS_SEM_PRI_H

#include "los_sem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

enum LosSemMaxCount {
    OS_SEM_COUNTING_MAX_COUNT = 0xFFFF, /**< Max count of counting semaphores */
    OS_SEM_BINARY_MAX_COUNT = 1         /**< Max count of binary semaphores */
};

/**
 * @ingroup los_sem
 * Semaphore control structure.
 */
typedef struct {
    UINT16 semStat;      /**< Semaphore state */
    UINT16 semCount;     /**< Number of available semaphores */
    UINT16 maxSemCount;  /**< Max number of available semaphores */
    UINT16 semID;        /**< Semaphore control structure ID */
    LOS_DL_LIST semList; /**< Queue of tasks that are waiting on a semaphore */
} LosSemCB;

/**
 * @ingroup los_sem
 * The semaphore is not in use.
 *
 */
#define OS_SEM_UNUSED 0
/**
 * @ingroup los_sem
 * The semaphore is used.
 *
 */
#define OS_SEM_USED   1
/**
 * @ingroup los_sem
 * Obtain the head node in a semaphore doubly linked list.
 *
 */
#define GET_SEM_LIST(ptr) LOS_DL_LIST_ENTRY(ptr, LosSemCB, semList)
extern LosSemCB *g_allSem;
/**
 * @ingroup los_sem
 * Obtain a semaphore ID.
 *
 */
#define GET_SEM(semid) (((LosSemCB *)g_allSem) + (semid))

/**
 * @ingroup los_sem
 * @brief Initialize the  Semaphore doubly linked list.
 *
 * @par Description:
 * This API is used to initialize the  Semaphore doubly linked list.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval UINT32   Initialization result.
 * @par Dependency:
 * <ul><li>los_sem_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsSemInit(VOID *semArray);

/**
 * @ingroup los_sem
 * @brief Create Semaphore.
 *
 * @par Description:
 * This API is used to create Semaphore.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  count      [IN]Type  #UINT16 Semaphore count.
 * @param  maxCount   [IN]Type  #UINT16 Max semaphore count.
 * @param  semHandle  [OUT]Type #UINT32 * Index of semaphore.
 *
 * @retval UINT32   Create result.
 * @par Dependency:
 * <ul><li>los_sem_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
UINT32 OsSemCreate(UINT16 count, UINT16 maxCount, UINT32 *semHandle);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_SEM_PRI_H */
