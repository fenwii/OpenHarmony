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

#ifndef _LOS_PRIQUEUE_PRI_H
#define _LOS_PRIQUEUE_PRI_H

#include "los_list.h"
#include "los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define OS_PRIORITY_QUEUE_PRIORITYNUM 32

/**
 * @ingroup los_priqueue
 * @brief Initialize the priority queue.
 *
 * @par Description:
 * This API is used to initialize the priority queue.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param none.
 *
 * @retval LOS_OK on success .
 * @retval LOS_NOK on failure.
 * @par Dependency:
 * <ul><li>los_priqueue_pri.h: the header file that contains the API declaration.</li></ul>
 * @see none.
 */
extern UINT32 OsPriqueueInit(VOID);

/**
 * @ingroup los_priqueue
 * @brief Insert a item to the priority queue.
 *
 * @par Description:
 * This API is used to insert a item to the priority queue according to the priority of this item.
 * @attention
 * <ul>
 * <li>Param priqueueItem must point to valid memory.</li>
 * <li>Param priority rang is [0, OS_PRIORITY_QUEUE_PRIORITYNUM),included 0 and not included
   LOS_PRIORITY_QUEUE_PRIORITYNUM.</li>
 * </ul>
 * @param priqueueItem   [IN] The node of item to be inserted.
 * @param priority       [IN] Priority of the item be inserted.
 *
 * @retval none.
 * @par Dependency:
 * <ul><li>los_priqueue_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsPriqueueDequeue.
 */
extern VOID OsPriqueueEnqueue(LOS_DL_LIST *priqueueItem, UINT32 priority);

/**
 * @ingroup los_priqueue
 * @brief Delete a item from the priority queue.
 *
 * @par Description:
 * This API is used to delete a item from the priority queue.
 * @attention
 * <ul>
 * <li>Param priqueueItem must point to valid memory.</li>
 * </ul>
 * @param priqueueItem   [IN] The node of item to be deleted.
 *
 * @retval none.
 * @par Dependency:
 * <ul><li>los_priqueue_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsPriqueueEnqueue.
 */
extern VOID OsPriqueueDequeue(LOS_DL_LIST *priqueueItem);

/**
 * @ingroup los_priqueue
 * @brief Obtain the item with highest priority.
 *
 * @par Description:
 * This API is used to obtain the item with highest priority in the priority queue.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param none.
 *
 * @retval NULL    : The priority queue is empty.
 * @retval item node : The node of the item with highest priority.
 * @par Dependency:
 * <ul><li>los_priqueue_pri.h: the header file that contains the API declaration.</li></ul>
 * @see none.
 */
extern LOS_DL_LIST *OsPriqueueTop(VOID);

/**
 * @ingroup los_priqueue
 * @brief Obtain the number of items with the specified priority.
 *
 * @par Description:
 * This API is used to obtain the number of items with the specified priority.
 * @attention
 * <ul>
 * <li>Param priority rang is [0, OS_PRIORITY_QUEUE_PRIORITYNUM),included 0 and not included
   LOS_PRIORITY_QUEUE_PRIORITYNUM.</li>
 * </ul>
 * @param priority    [IN] Obtain the number of items with the specified priority of priority.
 *
 * @retval The number of items :The number of items with the specified priority.
 * @par Dependency:
 * <ul><li>los_priqueue_pri.h: the header file that contains the API declaration.</li></ul>
 * @see none.
 */
extern UINT32 OsPriqueueSize(UINT32 priority);

/**
 * @ingroup los_priqueue
 * @brief Obtain the total number of items in the priority queue.
 *
 * @par Description:
 * This API is used to obtain the number of items in the priority queue.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval The number of items: The total number of items in the priority queue.
 * @par Dependency:
 * <ul><li>los_priqueue_pri.h: the header file that contains the API declaration.</li></ul>
 * @see none.
 */
extern UINT32 OsPriqueueTotalSize(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_PRIQUEUE_PRI_H */
