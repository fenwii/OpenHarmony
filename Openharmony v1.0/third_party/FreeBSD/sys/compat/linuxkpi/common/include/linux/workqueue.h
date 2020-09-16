/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2017 Mellanox Technologies, Ltd.
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
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/linux/workqueue.h 337897 2018-08-16 08:11:17Z hselasky $
 */
#ifndef	_LINUX_WORKQUEUE_H_
#define	_LINUX_WORKQUEUE_H_

#include "pthread.h"
#include "los_task.h"
#include "semaphore.h"
#include "los_memory.h"
#include "los_event.h"
#include "linux/list.h"
#include "linux/timer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


struct lock_class_key {
};

#ifdef WORKQUEUE_SUPPORT_PRIORITY
/**
 * @ingroup los_task
 * Define a usable work priority.
 *
 * Highest task priority.
 */
#define OS_WORK_PRIORITY_HIGHEST                    0

/**
 * @ingroup los_task
 * Define a usable work priority.
 *
 * Lowest task priority.
 */
#define OS_WORK_PRIORITY_LOWEST                     31


/**
 * @ingroup los_task
 * Define a usable work priority.
 *
 * Default task priority.
 */
#define OS_WORK_PRIORITY_DEFAULT                     OS_WORK_PRIORITY_LOWEST
#endif

/**
 * @ingroup workqueue
 * System default workqueue.
 */
extern struct workqueue_struct *g_pstSystemWq;

/**
 * @ingroup workqueue
 * Workqueue task control block structure.
 */
typedef struct LosTaskCB task_struct;

/**
 * @ingroup workqueue
 * Define atomic_long_t as a signed integer.
 *
 */
typedef long atomic_long_t;

struct work_struct;

/**
 * @ingroup workqueue
 * Workqueue handling function.
 */
typedef void (*work_func_t)(struct work_struct *);

/**
 * @ingroup workqueue
 * Work structure.
 * A work is a node in a workqueue.
 */
struct work_struct {
    atomic_long_t data;        /**< Input parameter of the work handling function. */
    struct list_head entry;    /**< Pointer to a doubly linked list of a work. */
    work_func_t func;          /**< Work handling function. */
    unsigned int work_status;  /**< Work status. */
#ifdef WORKQUEUE_SUPPORT_PRIORITY
    unsigned int work_pri;
#endif
};

/**
 * @ingroup workqueue
 * delayed_work structure.
 * A delayed_work is a work that is delayed to be mounted to a workqueue.
 */
struct delayed_work {
    struct work_struct work;        /**< Work structure. */
    struct timer_list timer;        /**< Delay control block parameter structure. */
    struct workqueue_struct *wq;    /**< Workqueue that contains the delayed_work structure. */
    int cpu;                        /**< Number of CPUs. Not in use temporarily. */
};

/**
 * @ingroup workqueue
 * Workqueue control structure.
 * It awakes a workqueue or makes a workqueue sleep.
 */
typedef struct tag_cpu_workqueue_struct {
    struct list_head worklist;         /**< Pointer to a work doubly linked list. */
    struct work_struct *current_work;  /**< Work that is being executed. */
    struct workqueue_struct *wq;       /**< Workqueue that contains the workqueue control structure. */
    task_struct *thread;               /**< Workqueue handling thread. */
} cpu_workqueue_struct;

/**
 * @ingroup workqueue
 * Definition of a workqueue structure.
 */
struct workqueue_struct {
    cpu_workqueue_struct *cpu_wq;   /**< Workqueue control structure. */
    struct list_head list;          /**< Pointer to a workqueue doubly linked list. */
    EVENT_CB_S wq_event;            /**< Event of a workqueue. */
    unsigned int wq_id;             /**< Workqueue ID. */
    int delayed_work_count;         /**< Number of delayed works in a workqueue. */
    char *name;                     /**< Workqueue name. */
    int singlethread;               /**< Whether to create a new working task. 0 indicates that
                                         the default working task will be used. */
    int wq_status;                  /**< Workqueue status. */
    int freezeable;                 /**< Not in use temporarily. */
    int rt;                         /**< Not in use temporarily. */
};

/**
 * @ingroup workqueue
 * Work status enumeration.
 */
enum work_status {
    WORK_BUSY_PENDING   = 1U << 0,    /**< The status of work item is pending execution. */
    WORK_BUSY_RUNNING   = 1U << 1,    /**< The status of work item is running. */
    WORK_STRUCT_PENDING = 1U << 0,    /**< Work item is pending execution. */
    WORK_STRUCT_RUNNING = 1U << 1,    /**< Work item is running. */
};

/**
 * @ingroup workqueue
 * Initialize a work.
 */
#ifdef WORKQUEUE_SUPPORT_PRIORITY
#define INIT_WORK(work, callbackFunc)  do {      \
    INIT_LIST_HEAD(&((work)->entry));            \
    (work)->func = (callbackFunc);               \
    (work)->data = (atomic_long_t)(0);           \
    (work)->work_status = 0;                     \
    (work)->work_pri = OS_WORK_PRIORITY_DEFAULT; \
} while (0)
#else
#define INIT_WORK(work, callbackFunc)  do { \
    INIT_LIST_HEAD(&((work)->entry));       \
    (work)->func = (callbackFunc);          \
    (work)->data = (atomic_long_t)(0);      \
    (work)->work_status = 0;                \
} while (0)
#endif

/**
 * @ingroup workqueue
 * Initialize a delayed work.
 */
#define INIT_DELAYED_WORK(work, func) \
    linux_init_delayed_work(work, func)

#define create_singlethread_workqueue(name) \
    linux_create_singlethread_workqueue(name)

#define create_workqueue(name) \
    linux_create_singlethread_workqueue(name)

#define destroy_workqueue(wq) \
    linux_destroy_workqueue(wq)

#define queue_work(wq, work) \
    linux_queue_work(wq, work)

#define queue_delayed_work(wq, dwork, delayTime) \
    linux_queue_delayed_work(wq, dwork, delayTime)

#define schedule_work(work) \
    linux_schedule_work(work)

#define schedule_delayed_work(dwork, delayTime) \
    linux_schedule_delayed_work(dwork, delayTime)

#define work_busy(work) \
    linux_work_busy(work)

#define flush_delayed_work(dwork) \
    linux_flush_delayed_work(dwork)

#define cancel_delayed_work(dwork) \
    linux_cancel_delayed_work(dwork)

#define cancel_delayed_work_sync(dwork) \
    linux_cancel_delayed_work_sync(dwork)

#define flush_work(work) \
    linux_flush_work(work)

#define cancel_work_sync(work) \
    linux_cancel_work_sync(work)

/* prototypes */

/**
 * @ingroup  workqueue
 * @brief Initialize a delayed work.
 *
 * @par Description:
 * This API is used to initialize a delayed work.
 *
 * @attention
 * <ul>
 * <li>The parameter dwork and func shoud be valid memory, otherwise, the system may be abnormal. </li>
 * </ul>
 *
 * @param  dwork   [IN] Work handle.
 * @param  func    [IN] Executive function.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>workqueue.h: the header file that contains the API declaration.</li></ul>
 * @see none.
 */
extern void linux_init_delayed_work(struct delayed_work *dwork, work_func_t func);

/**
 * @ingroup  workqueue
 * @brief Create a workqueue.
 *
 * @par Description:
 * This API is used to create a workqueue that has a specified name.
 *
 * @attention
 * <ul>
 * <li> The passed-in workqueue name is a character string that cannot be null
 * and is the only identifier of the workqueue, make sure it is unique. </li>
 * </ul>
 *
 * @param  name  [IN] Workqueue name.
 *
 * @retval  NULL                   The workqueue fails to be created.
 * @retval  workqueue_struct*      The workqueue is successfully created.
 * @par Dependency:
 * <ul><li>workqueue.h: the header file that contains the API declaration.</li></ul>
 * @see destroy_workqueue
 */
extern struct workqueue_struct *linux_create_singlethread_workqueue(char *name);

/**
 * @ingroup  workqueue
 * @brief Delete a workqueue.
 *
 * @par Description:
 * This API is used to delete a workqueue that has a specified handle.
 *
 * @attention
 * <ul>
 * <li>The name of the workqueue will be null and the workqueue cannot be used again
 * after the workqueue is deleted. </li>
 * </ul>
 *
 * @param  wq  [IN] Workqueue handle.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>workqueue.h: the header file that contains the API declaration.</li></ul>
 * @see create_workqueue
 */
extern void linux_destroy_workqueue(struct workqueue_struct *wq);

/**
 * @ingroup  workqueue
 * @brief Queue a work on a workqueue.
 *
 * @par Description:
 * This API is used to queue a work on a specified workqueue.
 *
 * @attention
 * <ul>
 * <li>The parameter wq and work shoud be valid memory, otherwise, the system may be abnormal. </li>
 * <li>The work will be immediately queued on the workqueue. </li>
 * </ul>
 *
 * @param  wq     [IN] Workqueue handle.
 * @param  work  [IN] Work handle.
 *
 * @retval #TRUE      The work is successfully queued on the workqueue.
 * @retval #FALSE     The work fails to be queued on the workqueue.
 * @par Dependency:
 * <ul>
 * <li>This function should be used after create_singlethread_workqueue() or create_workqueue() has been called</li>
 * <li>workqueue.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see cancel_work_sync
 */
extern bool linux_queue_work(struct workqueue_struct *wq, struct work_struct *work);

/**
 * @ingroup  workqueue
 * @brief Queue a work on a workqueue after delay.
 *
 * @par Description:
 * This API is used to queue a work on a specified workqueue after delay.
 *
 * @attention
 * <ul>
 * <li>The parameter wq and dwork shoud be valid memory, otherwise, the system may be abnormal. </li>
 * <li>The work will be queued on the workqueue in a delayed period of time. </li>
 * <li>The work will be queued on the workqueue immediately if delayTime is 0, it as same as queue_work(). </li>
 * </ul>
 *
 * @param  wq         [IN] Workqueue handle.
 * @param  dwork      [IN] Delayed work handle.
 * @param  delayTime  [IN] Delayed time, number of ticks to wait or 0 for immediate execution.
 *
 * @retval #TRUE      The work is successfully queued on the workqueue.
 * @retval #FALSE     The work fails to be queued on the workqueue.
 * @par Dependency:
 * <ul>
 * <li>This function should be used after create_singlethread_workqueue() or create_workqueue() has been called</li>
 * <li>workqueue.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see cancel_delayed_work
 */
extern bool linux_queue_delayed_work(struct workqueue_struct *wq, struct delayed_work *dwork, unsigned int delayTime);

/**
 * @ingroup  workqueue
 * @brief Put a work in a default workqueue.
 *
 * @par Description:
 * This API is used to put a work in the default workqueue that is created when Huawei LiteOS is initialized.
 *
 * @attention
 * <ul>
 * <li>The parameter work shoud be valid memory, otherwise, the system may be abnormal. </li>
 * <li>The default workqueue is g_pstSystemWq. </li>
 * </ul>
 *
 * @param  work        [IN] Work handle.
 *
 * @retval #TRUE      The work is successfully put in the workqueue.
 * @retval #FALSE     The work fails to be put in the workqueue.
 * @par Dependency:
 * <ul>
 * <li>This function should be used after create_singlethread_workqueue() or create_workqueue() has been called</li>
 * <li>workqueue.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see cancel_work_sync
 */
extern bool linux_schedule_work(struct work_struct *work);

/**
 * @ingroup  workqueue
 * @brief Put a work in a default workqueue after delay.
 *
 * @par Description:
 * This API is used to put a work in the default workqueue that is created
 * when Huawei LiteOS is initialized in a delayed period of time.
 *
 * @attention
 * <ul>
 * <li>The parameter dwork shoud be valid memory, otherwise, the system may be abnormal. </li>
 * <li>The default workqueue is g_pstSystemWq. </li>
 * <li>The dwork will be queued on the workqueue immediately if delayTime is 0. </li>
 * </ul>
 *
 * @param  dwork         [IN] Delayed work handle.
 * @param  delayTime     [IN] Delayed time, number of ticks to wait or 0 for immediate execution.
 *
 * @retval #TRUE      The work is successfully put in the workqueue.
 * @retval #FALSE     The work fails to be put in the workqueue.
 * @par Dependency:
 * <ul>
 * <li>This function should be used after create_singlethread_workqueue() or create_workqueue() has been called</li>
 * <li>workqueue.h: the header file that contains the API declaration.</li>
 * </ul>
 * @see cancel_delayed_work
 */
extern bool linux_schedule_delayed_work(struct delayed_work *dwork, unsigned int delayTime);

/**
 * @ingroup  workqueue
 * @brief Query the work status.
 *
 * @par Description:
 * This API is used to query the status of a work and a delayed work.
 *
 * @attention
 * <ul>
 * <li>The parameter work shoud be valid memory, otherwise, the system may be abnormal.</li>
 * </ul>
 *
 * @param  work          [IN] Work handle.
 *
 * @retval #WORK_BUSY_PENDING      The work is pending.
 * @retval #WORK_BUSY_RUNNING      The work is running.
 * @retval #FALSE                  The value of the parameter work is NULL.
 * @par Dependency:
 * <ul><li>workqueue.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern unsigned int linux_work_busy(struct work_struct *work);

/**
 * @ingroup  workqueue
 * @brief Immediately execute a delayed work.
 *
 * @par Description:
 * This API is used to immediately put a delayed work in a workqueue
 * and wait for the execution of the delayed work to end.
 *
 * @attention
 * <ul>
 * <li>flush_delayed_work() should be used after queue_delayed_work() has been called.</li>
 * <li>The parameter dwork shoud be valid memory, otherwise, the system may be abnormal.</li>
 * </ul>
 *
 * @param  dwork          [IN] Delayed work handle.
 *
 * @retval #TRUE      The operation succeeds.
 * @retval #FALSE     The operation fails.
 * @par Dependency
 * <ul><li>workqueue.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern bool linux_flush_delayed_work(struct delayed_work *dwork);

/**
 * @ingroup  workqueue
 * @brief Cancel a delayed work.
 *
 * @par Description:
 * This API is used to cancel a delayed work, which means that the work will not be executed regardless of
 * whether the delayed time has expired.
 *
 * @attention
 * <ul>
 * <li>cancel_delayed_work() should be used after queue_delayed_work() has been called.</li>
 * <li>The parameter dwork shoud be valid memory, otherwise, the system may be abnormal.</li>
 * </ul>
 *
 * @param  dwork          [IN] Delayed work handle.
 *
 * @retval #TRUE      The delayed work is successfully canceled.
 * @retval #FALSE     The delayed work fails to be canceled.
 * @par Dependency:
 * <ul><li>workqueue.h: the header file that contains the API declaration.</li></ul>
 * @see queue_delayed_work
 */
extern bool linux_cancel_delayed_work(struct delayed_work *dwork);
/**
 * @ingroup  workqueue
 * @brief Cancel a delayed work and wait for it to finish.
 *
 * @par Description:
 * This API is used to cancel a delayed work, which means that the work will not be executed regardless of
 * whether the delayed time has expired.
 *
 * @attention
 * <ul>
 * <li>cancel_delayed_work_sync() should be used after queue_delayed_work() has been called.</li>
 * <li>The parameter dwork shoud be valid memory, otherwise, the system may be abnormal.</li>
 * </ul>
 *
 * @param  dwork          [IN] Delayed work handle.
 *
 * @retval #TRUE      The delayed work is successfully canceled.
 * @retval #FALSE     The delayed work fails to be canceled.
 * @par Dependency:
 * <ul><li>workqueue.h: the header file that contains the API declaration.</li></ul>
 * @see queue_delayed_work
 */
extern bool linux_cancel_delayed_work_sync(struct delayed_work *dwork);

/**
 * @ingroup  workqueue
 * @brief Immediately execute a work.
 *
 * @par Description:
 * This API is used to immediately execute a specified work and wait for the execution to end.
 *
 * @attention
 * <ul>
 * <li>flush_work() should be used after queue_work() has been called.</li>
 * <li>The parameter work shoud be valid memory, otherwise, the system may be abnormal.</li>
 * </ul>
 *
 * @param  work          [IN] Work handle.
 *
 * @retval #TRUE      The operation succeeds.
 * @retval #FALSE     The operation fails.
 * @par Dependency:
 * <ul><li>workqueue.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern bool linux_flush_work(struct work_struct *work);

/**
 * @ingroup  workqueue
 * @brief Cancel a work.
 *
 * @par Description:
 * This API is used to cancel a work that is pending or running.
 *
 * @attention
 * <ul>
 * <li>cancel_work_sync() should be used after queue_work() has been called.</li>
 * <li>The parameter work shoud be valid memory, otherwise, the system may be abnormal.</li>
 * </ul>
 *
 * @param  work          [IN] Work handle.
 *
 * @retval #TRUE      The work is successfully canceled.
 * @retval #FALSE     The work fails to be canceled.
 * @par Dependency:
 * <ul><li>workqueue.h: the header file that contain the API declaration.</li></ul>
 * @see queue_work
 */
extern bool linux_cancel_work_sync(struct work_struct *work);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LINUX_WORKQUEUE_H_ */
