/*-
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
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/hrtimer.h 335411 2018-06-20 06:35:37Z hselasky $
 */

#ifndef _LINUX_HRTIMER_H_
#define	_LINUX_HRTIMER_H_

#include "sys/types.h"
#include "los_base.h"
#include "los_task.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


/**
 * @ingroup hr_swtmr
 * Define the number of timer cycles in 1us.
 */
#define HRTIMER_PERUS  (OS_SYS_CLOCK / 1000000.0)

/**
 * @ingroup hr_swtmr
 * Define s64 as a signed long integer.
 */
typedef signed long long s64;

/**
 * @ingroup hr_swtmr
 * Define s32 as a signed long integer.
 */
typedef signed int s32;

/**
 * @ingroup hr_swtmr
 * Define u64 as an unsigned long integer.
 */
typedef unsigned long long u64;

/**
 * @ingroup hr_swtmr
 * Structure of the scheduled time.
 */
union ktime {
    s64 tv64;            /**< Scheduled time for 64-bit CPU systems. */
    struct {
        s32 sec, usec;   /**< Scheduled time for 32-bit CPU systems. */
    } tv;
};

/**
 * @ingroup hr_swtmr
 * Structure of a node in a high-resolution timer queue.
 */
struct timerqueue_node {
    unsigned int node;   /**< Not in use temporarily. */
};

/**
 * @ingroup hr_swtmr
 * Enumerative structure of the high-resolution timer mode arguments.
 */
enum hrtimer_mode {
    HRTIMER_MODE_ABS = 0x0,     /**< Time value is absolute. */
    HRTIMER_MODE_REL = 0x1,     /**< Time value is relative to now. */
    HRTIMER_MODE_PINNED = 0x2,  /**< Timer is bound to CPU. */
};

/**
 * @ingroup hr_swtmr
 * Enumerative structure of the return type of a high-resolution timer timeout callback function.
 */
enum hrtimer_restart {
    HRTIMER_NORESTART,   /**< The timer will not be restarted.*/
    HRTIMER_RESTART      /**< The timer must be restarted.*/
};
struct hrtimer;

/**
 * @ingroup hr_swtmr
 * Define the function handler type of a high-resolution timer timeout callback function.
 */
typedef enum hrtimer_restart (*Handler)(struct hrtimer *);

/**
 * @ingroup hr_swtmr
 * Structure of parameters of a high-resolution timer API.
 */
struct hrtimer {
    union ktime _softexpires;             /**< Structure of the scheduled time. */
    Handler function;                     /**< Timeout callback function. */
    unsigned long state;                  /**< Timer working state. Not in use temporarily. */
#ifdef CONFIG_TIMER_STATS
    int start_pid;                        /**< ID of the task that invokes a high-resolution timer.
                                               Not in use temporarily. */
    void *start_site;                     /**< Function that invokes a high-resolution timer. Not in use temporarily. */
#define START_TASK_NAME_LEN  16
    char start_comm[START_TASK_NAME_LEN]; /**< Name of the task that invokes a high-resolution timer.
                                               Not in use temporarily. */
#endif
};

/**
 * @ingroup hr_swtmr
 * Parameter structure of the nodes of a high-resolution timer timeout callback function.
 */
struct handler_list_node {
    struct handler_list_node *pstNext;  /**< Pointer to the next node. */
    Handler pfnHandler;                 /**< Timeout callback function. */
    union ktime _softexpires;           /**< Structure of the scheduled time. */
};

/**
 * @ingroup hr_swtmr
 * Parameter structure of a high-resolution timer node.
 */
struct hrtimer_list_node {
    struct hrtimer_list_node *pstNext;     /**< Pointer to the next node. */
    struct handler_list_node *HandlerHead; /**< Pointer to the node queue of a timeout callback function. */
    unsigned int set_time_reload;          /**< Count of timers. */
    union ktime _softexpires;              /**< Structure of the scheduled time. */
};

#define hrtimer_init(timer, clockID, mode) \
    linux_hrtimer_init(timer, clockID, mode)

#define hrtimer_create(timer, time, handler) \
    linux_hrtimer_create(timer, time, handler)

#define hrtimer_start(timer, time, mode) \
    linux_hrtimer_start(timer, time, mode)

#define hrtimer_cancel(timer) \
    linux_hrtimer_cancel(timer)

#define hrtimer_forward(timer, interval) \
    linux_hrtimer_forward(timer, interval)

#define hrtimer_is_queued(timer) \
    linux_hrtimer_is_queued(timer)

/**
 * @ingroup hr_swtmr
 * @brief Initialize a high-resolution timer.
 *
 * @par Description:
 * This API is used to initialize a high-resolution timer to the given clock.
 * @attention
 * <ul>
 * <li>The pointer to the high-resolution timer structure to be initialized must not be null.</li>
 * </ul>
 *
 * @param timer      [IN] Pointer to the high-resolution timer structure.
 * @param clockID    [IN] This parameter is not supported, so users can pass in any integer.
 * @param mode       [IN] Mode setting is currently not supported by Huawei LiteOS.
 *
 * @retval   None.
 * @par Dependency:
 * <ul>
 * <li>hrtimer.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
void linux_hrtimer_init(struct hrtimer *timer, clockid_t clockID, enum hrtimer_mode mode);

/**
 * @ingroup hr_swtmr
 * @brief Create a high-resolution timer.
 *
 * @par Description:
 * This API is used to create a high-resolution timer node and initialize timer parameters.
 * @attention
 * <ul>
 * <li>The passed-in pointer to the high-resolution timer structure must not be null.</li>
 * <li>The value of the scheduled time cannot be zero.</li>
 * </ul>
 *
 * @param timer      [IN] Pointer to the high-resolution timer structure.
 * @param time       [IN] Structure of the scheduled time.
 * @param handler    [IN] Pointer to the timeout callback function.
 *
 * @retval  -1        The high-resolution timer fails to be created because the pointer to
 * the high-resolution timer structure is null.
 * @retval    0         The high-resolution timer is successfully created.
 * @par Dependency:
 * <ul>
 * <li>hrtimer.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
int linux_hrtimer_create(struct hrtimer *timer, union ktime time, Handler handler);

/**
 * @ingroup hr_swtmr
 * @brief Start a high-resolution timer.
 *
 * @par Description:
 * This API is used to add a high-resolution timer node to the global linked list and start timing.
 * @attention
 * <ul>
 * <li>The passed-in pointer to the high-resolution timer structure must not be null.</li>
 * <li>The value of the scheduled time cannot be zero.</li>
 * </ul>
 *
 * @param timer        [IN] Pointer to the high-resolution timer structure.
 * @param time         [IN] Structure of the scheduled time.
 * @param mode         [IN] Mode setting is currently not supported by Huawei LiteOS.
 *
 * @retval    -1       The high-resolution timer fails to be started.
 * @retval    0        The high-resolution timer is successfully started.
 * @retval    1        The high-resolution timer node is already in the linked list.
                       Only the scheduled time will be updated and a new timer node will not be created.
 * @par Dependency:
 * <ul>
 * <li>hrtimer.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see hrtimer_cancel
 */
int linux_hrtimer_start(struct hrtimer *timer, union ktime time, const enum hrtimer_mode mode);

/**
 * @ingroup hr_swtmr
 * @brief Delete an existing high-resolution timer.
 *
 * @par Description:
 * This API is used to delete an existing high-resolution timer. The timeout callback function applied in
 * an existing high-resolution timer is deleted first. If the timeout callback function linked list is not null
 * after the function is deleted, the timer will not be deleted. If the timeout callback function linked list is null
 * after the function is deleted, the timer will be deleted.
 * @attention
 * <ul>
 * <li>If the pointer to the high-resolution timer is null or the timer node does not exist,
 * the high-resolution timer fails to be deleted.</li>
 * </ul>
 *
 * @param timer        [IN] Pointer to the high-resolution timer structure to be deleted.
 *
 * @retval    -1       The high-resolution timer fails to be deleted.
 * @retval    0        The timer to be deleted does not exist.
 * @retval    1        The timer is in scheduled state.
 * @par Dependency:
 * <ul>
 * <li>hrtimer.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see hrtimer_start
 */
int linux_hrtimer_cancel(struct hrtimer *timer);

/**
 * @ingroup hr_swtmr
 * @brief Forward the expiry of an existing high-resolution timer.
 *
 * @par Description:
 * This API is used to change the scheduled time of an existing high-resolution timer to
 * the time specified by the passed-in parameter.
 * @attention
 * <ul>
 * <li>If the timer does not exist, create a timer.</li>
 * <li>The value of the scheduled time cannot be zero.</li>
 * </ul>
 *
 * @param timer        [IN] Pointer to the high-resolution timer structure.
 * @param interval     [IN] Structure of the interval to forward.
 *
 * @retval    0       The timer expiry fails to be forwarded.
 * @retval    Timer value    The timer expiry is successfully forwarded.
 * @par Dependency:
 * <ul>
 * <li>hitimer.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
u64 linux_hrtimer_forward(struct hrtimer *timer, union ktime interval);

/**
 * @ingroup hr_swtmr
 * @brief Check whether a specified high-resolution timer exists.
 *
 * @par Description:
 * This API is used to determine whether a specified high-resolution timer exists by
 * querying the global linked list of timer nodes.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param timer        [IN] Pointer to the high-resolution timer structure to be checked.
 *
 * @retval    #LOS_NOK   1: The queried timer does not exist.
 * @retval    #LOS_OK    0: The queried timer exists.
 * @retval    #-1           The value of the parameter timer is NULL.
 * @par Dependency
 * <ul>
 * <li>hrtimer.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see None.
 */
int linux_hrtimer_is_queued(struct hrtimer *timer);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _HRTIMER_H */
