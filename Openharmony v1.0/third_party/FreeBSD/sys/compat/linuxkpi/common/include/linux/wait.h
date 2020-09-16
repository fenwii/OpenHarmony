/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013, 2014 Mellanox Technologies, Ltd.
 * Copyright (c) 2017 Mark Johnston <markj@FreeBSD.org>
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
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/wait.h 335426 2018-06-20 06:50:11Z hselasky $
 */

#ifndef _LINUX_WAIT_H_
#define	_LINUX_WAIT_H_

#include <linux/spinlock.h>
#include "los_event.h"
#include "los_sys.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * Notice about wait_queue_head_t:
 * 1.The stEvent is used for task-synchronization and has the same function as wait_event_head in Linux.
 *   In LiteOS, when wait_event is called, if the condition is not true, the task will be blocked and
 *   mounted on stEvent.stEventList. In Linux, the blocked task will be mounted on wait_queue_head.task_list.
 * 2.The lock and poll_queue are only used for poll operation: poll_queue is used to link poll_wait_node,
 *   and lock is used to protect this poll_queue.
 */
typedef struct wait_queue_head {
    EVENT_CB_S     stEvent;
    spinlock_t     lock;
    LOS_DL_LIST    poll_queue;
} wait_queue_head_t;

#define osWaitForever     0xFFFFFFFF
#define INVALID_ADDR      0xFFFFFFFF
#define DECLARE_WAIT_QUEUE_HEAD(wq) \
        wait_queue_head_t wq = { { 0, { (struct LOS_DL_LIST *)0xFFFFFFFF, (struct LOS_DL_LIST *)0xFFFFFFFF } },	\
        SPIN_LOCK_INITIALIZER("wait_queue_spinlock"),			\
        { &wq.poll_queue, &wq.poll_queue } }

void __wake_up_interruptible(wait_queue_head_t *wait);
void __init_waitqueue_head(wait_queue_head_t *wait);

/**
 * @ingroup  wait
 * @brief Initialize the waitqueue head.
 *
 * @par Description:
 * This API is used to initialize the waitqueue head.
 *
 * @attention
 * <ul>
 * <li>Please make sure the input parameter wait is valid, otherwise, the system would be crash.</li>
 * </ul>
 *
 * @param  wait [IN]  struct of the process that registered on the wait queue .
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>Wait.h: the header file that contains the API declaration.</li></ul>
 * @see none
 */
#define init_waitqueue_head(wait) __init_waitqueue_head(wait)

/**
 * @ingroup  wait
 * @brief wakeup the process that registered on the wait queue.
 *
 * @par Description:
 * This API is used to wakeup the process that registered on the wait queue.
 *
 * @attention
 * <ul>
 * <li>Please make sure the input parameter wait is valid, otherwise, the system would be crash.</li>
 * </ul>
 *
 * @param  wait [IN]  struct of the process that registered on the wait queue .
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>Wait.h: the header file that contains the API declaration.</li></ul>
 * @see none
 */
#define wake_up_interruptible(wait) __wake_up_interruptible(wait)
#define wake_up_interruptible_poll(wait, key) __wake_up_interruptible_poll(wait, key)

/**
 * @ingroup  wait
 * @brief wakeup the process that registered on the wait queue.
 *
 * @par Description:
 * This API is used to wakeup the process that registered on the wait queue.
 *
 * @attention
 * <ul>
 * <li>Please look up the function __wake_up_interruptible(wait).</li>
 * </ul>
 *
 * @param None.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>Wait.h: the header file that contains the API declaration.</li></ul>
 * @see wake_up_interruptible
 */
#define wake_up        wake_up_interruptible

/**
 * @ingroup wait
 * @brief sleep until a condition gets true.
 *
 * @par Description:
 * This API is used to sleep  a process until the condition evaluates to true.
 * The condition is checked each time when the waitqueue wait is woken up.
 *
 * @attention
 * <ul>
 * <li>none.</li>
 * </ul>
 *
 * @param  wait [IN] the waitqueue to wait on.
 * @param  condition [IN] a condition evaluates to true or false.

 * @retval #0 always return 0

 * @par Dependency:
 * <ul><li>linux\wait.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define wait_event(wait, condition) ({                                                                     \
    INT32 ret = 0;                                                                                         \
                                                                                                           \
    if ((wait).stEvent.stEventList.pstPrev == (struct LOS_DL_LIST *)INVALID_ADDR) {                        \
        (VOID)LOS_EventInit(&(wait).stEvent);                                                              \
    }                                                                                                      \
    while (!(condition)) {                                                                                 \
        (VOID)LOS_EventRead(&(wait).stEvent, 0x1U, LOS_WAITMODE_AND | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER); \
    }                                                                                                      \
    ret;                                                                                                   \
})

#define wait_event_interruptible      wait_event

/**
 * @ingroup wait
 * @brief sleep until a condition gets true or a timeout elapses.
 *
 * @par Description:
 * This API is used to sleep  a process until the condition evaluates to true or a timeout elapses.
 * The condition is checked each time when the waitqueue wait is woken up.
 *
 * @attention
 * <ul>
 * <li>none.</li>
 * </ul>
 *
 * @param  wait [IN] the waitqueue to wait on.
 * @param  condition [IN] a condition evaluates to true or false.
 * @param  timeout [IN] the max sleep time (unit : Tick). it is jiffies in linux.
 *
 * @retval #0 return 0 if the condition evaluated to false after the timeout elapsed
 * @retval #1 return 1 if the condition evaluated to true after the timeout elapsed
 * @retval #2 return 2 if the condition evaluated to true and the timeout is osWaitForever
 *
 * @par Dependency:
 * <ul><li>linux\wait.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define wait_event_interruptible_timeout(wait, condition, timeout)  ({                              \
    INT32 tmpTimeout;                                                                               \
    UINT32 ret = 2;                                                                                 \
    UINT64 ticksnow;                                                                                \
                                                                                                    \
    if ((wait).stEvent.stEventList.pstPrev == (struct LOS_DL_LIST *)INVALID_ADDR) {                 \
        (VOID)LOS_EventInit(&(wait).stEvent);                                                       \
    }                                                                                               \
    while (!(condition)) {                                                                          \
        ticksnow = LOS_TickCountGet();                                                              \
        ret = LOS_EventRead(&(wait).stEvent, 0x1U, LOS_WAITMODE_AND | LOS_WAITMODE_CLR, (timeout)); \
        if ((timeout) == osWaitForever) {                                                           \
            if (condition) {                                                                        \
                ret = 2;                                                                            \
                break;                                                                              \
            } else {                                                                                \
                continue;                                                                           \
            }                                                                                       \
        }                                                                                           \
        tmpTimeout = (INT32)((timeout) - (UINT32)(LOS_TickCountGet() - ticksnow));                  \
        if (tmpTimeout <= 0) {                                                                      \
            ret = (condition) ? 1 : 0;                                                              \
            break;                                                                                  \
        } else {                                                                                    \
            if (ret == LOS_ERRNO_EVENT_READ_TIMEOUT) {                                              \
                if (condition) {                                                                    \
                    ret = 1;                                                                        \
                    break;                                                                          \
                } else {                                                                            \
                    ret = 0;                                                                        \
                    break;                                                                          \
                }                                                                                   \
            } else {                                                                                \
                if (condition) {                                                                    \
                    ret = 2;                                                                        \
                    break;                                                                          \
                }                                                                                   \
            }                                                                                       \
        }                                                                                           \
    }                                                                                               \
    ret;                                                                                            \
})

#define add_wait_queue(wait, newWait) do {} while (0)
#define remove_wait_queue(wait, oldWait) do {} while (0)
#define DECLARE_WAITQUEUE(wait, current) do {} while (0)

static inline int linux_waitqueue_active(wait_queue_head_t *q)
{
    return !LOS_ListEmpty(&(q->stEvent.stEventList));
}

#define	waitqueue_active(wqh)		linux_waitqueue_active(wqh)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LINUX_WAIT_H_ */
