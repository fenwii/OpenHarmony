/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013, 2014 Mellanox Technologies, Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/completion.h 334767 2018-06-07 07:47:32Z hselasky $
 */
#ifndef	_LINUX_COMPLETION_H_
#define	_LINUX_COMPLETION_H_

#include "los_sys.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

enum CompletionState {
    COMPLETION_ONE,
    COMPLETION_ALL
};

#define COMPLETION_EVT 0x1

typedef struct completion {
    LOS_DL_LIST comList;
    UINT32 comCount;
    enum CompletionState state;
} completion_t;

#define init_completion(x) \
    linux_init_completion(x)

/* This inline function should be used to reinitialize a completion structure so it can
 * be reused. This is especially important after complete_all() is used.
 */
#define reinit_completion(x) \
        do { (x)->comCount = 0; } while (0)

#define complete(x) \
    linux_complete(x)

#define wait_for_completion(x) \
    linux_wait_for_completion(x)

#define wait_for_completion_timeout(x, timeout) \
    linux_wait_for_completion_timeout(x, timeout)

#define complete_all(x) \
    linux_complete_all(x)

#define completion_done(x) \
    linux_completion_done(x)

/**
 * @ingroup completion
 * @brief Initialize a completion.
 *
 * @par Description:
 * This API is used to initialize a specified completion.
 * @attention
 * <ul>
 * <li>The input parameter x must point to valid memory, otherwise, initilize a completion would failed.</li>
 * </ul>
 *
 * @param x   [IN] Pointer to the completion to be initialized,which must point to valid memory.
 *
 * @retval None.
 * @par Dependency: none
 * <ul><li>completion.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern void linux_init_completion(struct completion *x);

/**
 * @ingroup completion
 * @brief Wake up a task that is waiting on this completion.
 *
 * @par Description:
 * This API is used to wake up a task that is waiting on the completion.
 * @attention
 * <ul>
 * <li>The input parameter x must point to valid memory, otherwise, the system would be abnormal.</li>
 * <li>It suggested that calling complete() after wait_for_completion() or wait_for_completion_timeout(),
 * otherwise, wait_for_completion() or wait_for_completion_timeout() would not block
 * because there is already a completion completed.</li>
 * </ul>
 *
 * @param x [IN] Pointer to the completion on which the task to be woken up is waiting,
 * which must point to valid memory.
 *
 * @retval None.
 * @par Dependency:
 * <ul>
 * <li>this function should be used after init_completion() be called.</li>
 * <li>completion.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see
 */
extern void linux_complete(struct completion *x);

/**
 * @ingroup completion
 * @brief Wait on a completion forever.
 *
 * @par Description:
 * This API is used to wait on a completion forever.
 * @attention
 * <ul>
 * <li>The input parameter x must point to valid memory, otherwise, the system would be abnormal.</li>
 * <li>Can not be used in interrupt.</li>
 * <li>DO NOT call this API in system tasks. </li>
 * </ul>
 *
 * @param x [IN] Pointer to the completion to be waited on, which must point to valid memory.
 *
 * @retval None.
 * @par Dependency:
 * <ul>
 * <li>this function should be used after init_completion() be called.</li>
 * <li>completion.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see
 */
extern void linux_wait_for_completion(struct completion *x);

/**
 * @ingroup completion
 * @brief Wait on a completion within a certain time period.
 *
 * @par Description:
 * This API is used to wait on a completion within a certain time period (timeout).
 * @attention
 * <ul>
 * <li>The input parameter x must point to valid memory, otherwise, the system would be abnormal.</li>
 * <li>Timeout interval timeout should be in [1 , 0xFFFFFFFF], otherwise,
 *  it would return OS_WAIT_COMPLETION_ERROR but not wait for completion.</li>
 * <li>Can not be used in interrupt.</li>
 * <li>DO NOT call this API in software timer callback. </li>
 * </ul>
 *
 * @param x       [IN] Pointer to the  completion to be waited on, which must point to valid memory.
 * @param timeout [IN] Timeout interval for waiting on the completion (unit: Tick).
 *
 * @retval 0 The timeout period expires before the task is blocked or scheduled, or that timeout period is 0.
 * @retval [1,0xFFFFFFFF] Remaining waiting time.
 * @par Dependency:
 * <ul>
 * <li>this function should be used after init_completion() be called.</li>
 * <li>completion.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see
 */
extern unsigned long linux_wait_for_completion_timeout(struct completion *x, unsigned long timeout);

/**
 * @ingroup completion
 * @brief Wake up all tasks that are waiting on this completion.
 *
 * @par Description:
 * This API is used to wake up all tasks that are waiting on the completion.
 * @attention
 * <ul>
 * <li>The input parameter x must point to valid memory, otherwise, the system would be abnormal.</li>
 * <li>It suggested that calling complete_all() after wait_for_completion() or wait_for_completion_timeout(),
 * otherwise, wait_for_completion() or wait_for_completion_timeout() would not block
 * because there is already a completion completed.</li>
 * </ul>
 *
 * @param x [IN] Pointer to the completion on which the task to be woken up is waiting,
 * which must point to valid memory.
 *
 * @retval None.
 * @par Dependency:
 * <ul>
 * <li>this function should be used after init_completion() be called.</li>
 * <li>completion.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see
 */
extern void linux_complete_all(struct completion *x);
extern int linux_completion_done(struct completion *x);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LINUX_COMPLETION_H_ */
