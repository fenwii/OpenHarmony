/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 * Description: LiteOS Task Module Implementation
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

#ifndef _LOS_TASK_PRI_H
#define _LOS_TASK_PRI_H

#include "los_task.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_task
 * Null task ID
 *
 */
#define OS_TASK_ERRORID                             0xFFFFFFFF

/**
 * @ingroup los_task
 * Define a usable task priority.
 *
 * Highest task priority.
 */
#define OS_TASK_PRIORITY_HIGHEST                    0

/**
 * @ingroup los_task
 * Define a usable task priority.
 *
 * Lowest task priority.
 */
#define OS_TASK_PRIORITY_LOWEST                     31

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task control block is unused.
 */
#define OS_TASK_STATUS_UNUSED                       0x0001

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is suspended.
 */
#define OS_TASK_STATUS_SUSPEND                      0x0002

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is ready.
 */
#define OS_TASK_STATUS_READY                        0x0004

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is blocked.
 */
#define OS_TASK_STATUS_PEND                         0x0008

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is running.
 */
#define OS_TASK_STATUS_RUNNING                      0x0010

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is delayed.
 */
#define OS_TASK_STATUS_DELAY                        0x0020

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The time for waiting for an event to occur expires.
 */
#define OS_TASK_STATUS_TIMEOUT                      0x0040

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is waiting for an event to occur.
 */
#define OS_TASK_STATUS_EVENT                        0x0400

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is reading an event.
 */
#define OS_TASK_STATUS_EVENT_READ                   0x0800

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * A software timer is waiting for an event to occur.
 */
#define OS_TASK_STATUS_SWTMR_WAIT                   0x1000

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is blocked on a queue.
 */
#define OS_TASK_STATUS_PEND_QUEUE                   0x2000

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is blocked on a mutex.
 */
#define OS_TASK_STATUS_PEND_MUT                     0x4000

/**
 * @ingroup los_task
 * Flag that indicates the task or task control block status.
 *
 * The task is blocked on a semaphore.
 */
#define OS_TASK_STATUS_PEND_SEM                     0x8000

/**
 * @ingroup los_task
 * Boundary on which the stack size is aligned.
 *
 */
#define OS_TASK_STACK_SIZE_ALIGN                    16

/**
 * @ingroup los_task
 * Boundary on which the stack address is aligned.
 *
 */
#define OS_TASK_STACK_ADDR_ALIGN                    8

/**
 * @ingroup los_task
 * Task stack top magic number.
 *
 */
#define OS_TASK_MAGIC_WORD                          0xCCCCCCCC

/**
 * @ingroup los_task
 * Initial task stack value.
 *
 */
#define OS_TASK_STACK_INIT                          0xCACACACA

/**
 * @ingroup los_task
 * Number of usable task priorities.
 */
#define OS_TSK_PRINUM                               ((OS_TASK_PRIORITY_LOWEST - OS_TASK_PRIORITY_HIGHEST) + 1)

/**
 * @ingroup los_task
 * @brief the num of delayed tasks bucket
 */
#define OS_TSK_SORTLINK_LEN                         32

/**
 * @ingroup los_task
 * @brief the bit width occupied by the delayed ticks of task
 */
#define OS_TSK_SORTLINK_LOGLEN                      5

/**
 * @ingroup los_task
 * @brief the mask of delayed tasks bucket id.
 */
#define OS_TSK_SORTLINK_MASK                        (OS_TSK_SORTLINK_LEN - 1)

/**
 * @ingroup los_task
 * @brief the max task count for switch.
 */
#define OS_TASK_SWITCH_INFO_COUNT                   0xA

/**
 * @ingroup  los_task
 * @brief Check whether a task ID is valid.
 *
 * @par Description:
 * This API is used to check whether a task ID, excluding the idle task ID, is valid.
 * @attention None.
 *
 * @param  taskID [IN] Task ID.
 *
 * @retval 0 or 1. One indicates that the task ID is invalid, whereas zero indicates that the task ID is valid.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define OS_TSK_GET_INDEX(taskID)                      (taskID)

/**
 * @ingroup  los_task
 * @brief Obtain the pointer to a task control block.
 *
 * @par Description:
 * This API is used to obtain the pointer to a task control block using a corresponding parameter.
 * @attention None.
 *
 * @param  ptr [IN] Parameter used for obtaining the task control block.
 *
 * @retval Pointer to the task control block.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define OS_TCB_FROM_PENDLIST(ptr)                       LOS_DL_LIST_ENTRY(ptr, LosTaskCB, pendList)

/**
 * @ingroup  los_task
 * @brief Obtain the pointer to a task control block.
 *
 * @par Description:
 * This API is used to obtain the pointer to a task control block that has a specified task ID.
 * @attention None.
 *
 * @param  taskID [IN] task ID.
 *
 * @retval Pointer to the task control block.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
#define OS_TCB_FROM_TID(taskID)                       (((LosTaskCB *)g_taskCBArray) + (taskID))
#define OS_IDLE_TASK_ENTRY                            ((TSK_ENTRY_FUNC)OsIdleTask)

/**
 * @ingroup los_task
 * Define the task control block structure.
 */
typedef struct {
    VOID                        *stackPointer;            /**< Task stack pointer */
    UINT16                      taskStatus;
    UINT16                      priority;
    UINT32                      stackSize;                /**< Task stack size */
    UINT32                      topOfStack;               /**< Task stack top */
    UINT32                      taskID;                   /**< Task ID */
    TSK_ENTRY_FUNC              taskEntry;                /**< Task entrance function */
    VOID                        *taskSem;                 /**< Task-held semaphore */
    VOID                        *taskMux;                 /**< Task-held mutex */
    UINT32                      args[LOS_TASK_ARG_NUM];   /**< Parameter */
    CHAR                        *taskName;                /**< Task name */
    LOS_DL_LIST                 pendList;
    LOS_DL_LIST                 timerList;
    UINT32                      idxRollNum;
    EVENT_CB_S                  event;
    UINT32                      eventMask;                /**< Event mask */
    UINT32                      eventMode;                /**< Event mode */
    VOID                        *msg;                     /**< Memory allocated to queues */
    UINT32                      priBitMap;                /**< BitMap for recording the change of task priority, */
	                                                      /**< the priority can not be greater than 31 */
} LosTaskCB;

typedef struct {
    LosTaskCB   *runTask;
    LosTaskCB   *newTask;
} LosTask;

typedef struct {
    LOS_DL_LIST     *sortLink;
    UINT16          cursor;
    UINT16          unused;
} TaskSortLinkAttr;

/**
 * @ingroup los_task
 * Time slice structure.
 */
typedef struct TaskTimeSlice {
    LosTaskCB               *task;                        /**< Current running task */
    UINT16                  time;                         /**< Expiration time point */
    UINT16                  tout;                         /**< Expiration duration */
} OsTaskRobin;

typedef struct {
    UINT8 maxCnt : 7;   // bits [6:0] store count of task switch info
    UINT8 isFull : 1;   // bit [7] store isfull status
} TaskCountInfo;

/**
 * @ingroup los_task
 * Task switch information structure.
 *
 */
typedef struct {
    UINT8 idx;
    TaskCountInfo cntInfo;
    UINT16 pid[OS_TASK_SWITCH_INFO_COUNT];
    CHAR   name[OS_TASK_SWITCH_INFO_COUNT][LOS_TASK_NAMELEN];
} TaskSwitchInfo;

extern LosTask              g_losTask;

/**
 * @ingroup los_task
 * Task lock flag.
 *
 */
extern UINT16               g_losTaskLock;

/**
 * @ingroup los_task
 * Maximum number of tasks.
 *
 */
extern UINT32               g_taskMaxNum;

/**
 * @ingroup los_task
 * Idle task ID.
 *
 */
extern UINT32               g_idleTaskID;

/**
 * @ingroup los_task
 * Software timer task ID.
 *
 */
extern UINT32               g_swtmrTaskID;

/**
 * @ingroup los_task
 * Starting address of a task.
 *
 */
extern LosTaskCB            *g_taskCBArray;

/**
 * @ingroup los_task
 * Delayed task linked list.
 *
 */
extern LOS_DL_LIST          g_taskTimerList;

/**
 * @ingroup los_task
 * Free task linked list.
 *
 */
extern LOS_DL_LIST          g_losFreeTask;

/**
 * @ingroup los_task
 * Circular linked list that stores tasks that are deleted automatically.
 *
 */
extern LOS_DL_LIST          g_taskRecyleList;

/**
 * @ingroup los_task
 * task Sort linked list.
 *
 */
extern TaskSortLinkAttr            g_taskSortLink;

extern  BOOL                        g_taskScheduled;

extern  UINT32                      g_taskUsedCount;

/**
 * @ingroup los_task
 * @brief the block status of task
 */
extern VOID OsTaskSchedule(VOID);

/**
 * @ingroup  los_task
 * @brief Modify the priority of task.
 *
 * @par Description:
 * This API is used to modify the priority of task.
 *
 * @attention
 * <ul>
 * <li>The taskCB should be a correct pointer to task control block structure.</li>
 * <li>the priority should be in [0, OS_TASK_PRIORITY_LOWEST].</li>
 * </ul>
 *
 * @param  taskCB    [IN] Type #LosTaskCB * pointer to task control block structure.
 * @param  priority  [IN] Type #UINT16 the priority of task.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern VOID OsTaskPriModify(LosTaskCB *taskCB, UINT16 priority);

/**
 * @ingroup  los_task
 * @brief Scan a task.
 *
 * @par Description:
 * This API is used to scan a task.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern VOID OsTaskScan(VOID);

/**
 * @ingroup  los_task
 * @brief Initialization a task.
 *
 * @par Description:
 * This API is used to initialization a task.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval  UINT32    Initialization result.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 OsTaskInit(VOID *taskArray);

/**
 * @ingroup  los_task
 * @brief Create idle task.
 *
 * @par Description:
 * This API is used to create idle task.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval  UINT32   Create result.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 OsIdleTaskCreate(VOID);

/**
 * @ingroup  los_task
 * @brief Check task switch.
 *
 * @par Description:
 * This API is used to check task switch.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern VOID OsTaskSwitchCheck(VOID);

/**
 * @ingroup  los_task
 * @brief TaskMonInit.
 *
 * @par Description:
 * This API is used to taskMonInit.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  None.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern VOID OsTaskMonInit(VOID);

/**
 * @ingroup  los_task
 * @brief Task entry.
 *
 * @par Description:
 * This API is used to task entry.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  taskID  [IN] Type #UINT32   task id.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern VOID OsTaskEntry(UINT32 taskID);

/**
 * @ingroup  los_task
 * @brief pend running task to pendlist
 *
 * @par Description:
 * This API is used to pend task to  pendlist and add to sorted delay list.
 *
 * @attention
 * <ul>
 * <li>The pstList should be a vaild pointer to pendlist.</li>
 * </ul>
 *
 * @param  list       [IN] Type #LOS_DL_LIST * pointer to list which running task will be pended.
 * @param  taskStatus [IN] Type #UINT32  Task Status.
 * @param  timeOut    [IN] Type #UINT32  Expiry time. The value range is [0,LOS_WAIT_FOREVER].
 *
 * @retval  LOS_OK       wait success
 * @retval  LOS_NOK      pend out
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsTaskWake
 */
extern VOID OsTaskWait(LOS_DL_LIST *list, UINT32 taskStatus, UINT32 timeOut);

/**
 * @ingroup  los_task
 * @brief delete task from pendlist.
 *
 * @par Description:
 * This API is used to delete task from pendlist and also add to the priqueue.
 *
 * @attention
 * <ul>
 * <li>The pstList should be a vaild pointer to pend list.</li>
 * </ul>
 *
 * @param  resumedTask [IN] Type #LosTaskCB * pointer to the task which will be add to priqueue.
 * @param  taskStatus  [IN] Type #UINT32  Task Status.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsTaskWait
 */
extern VOID OsTaskWake(LosTaskCB *resumedTask, UINT32 taskStatus);

/**
 * @ingroup  los_task
 * @brief Get the task water line.
 *
 * @par Description:
 * This API is used to get the task water line.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  taskID [IN] Type #UINT32 task id.
 *
 * @retval  UINT32  Task water line.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsGetTaskWaterLine(UINT32 taskID);

/**
 * @ingroup  los_task
 * @brief Convert task status to string.
 *
 * @par Description:
 * This API is used to convert task status to string.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param  taskStatus [IN] Type #UINT16 task status.
 *
 * @retval  UINT8 *  String.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT8 *OsConvertTskStatus(UINT16 taskStatus);

/**
 * @ingroup  los_task
 * @brief Add task to sorted delay list.
 *
 * @par Description:
 * This API is used to add task to sorted delay list.
 *
 * @attention
 * <ul>
 * <li>The taskCB should be a correct pointer to task control block structure.</li>
 * </ul>
 *
 * @param  taskCB     [IN] Type #LosTaskCB * pointer to task control block structure.
 * @param  timeout    [IN] Type #UINT32 wait time, ticks.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsTimerListDelete
 */
extern VOID OsTaskAdd2TimerList(LosTaskCB *taskCB, UINT32 timeout);

/**
 * @ingroup  los_task
 * @brief delete task from sorted delay list.
 *
 * @par Description:
 * This API is used to delete task from sorted delay list.
 *
 * @attention
 * <ul>
 * <li>The taskCB should be a correct pointer to task control block structure.</li>
 * </ul>
 *
 * @param  taskCB [IN] Type #LosTaskCB * pointer to task control block structure.
 *
 * @retval  None.
 * @par Dependency:
 * <ul><li>los_task_pri.h: the header file that contains the API declaration.</li></ul>
 * @see OsTaskAdd2TimerList
 */
extern VOID OsTimerListDelete(LosTaskCB *taskCB);

extern BOOL OsRunningTaskIsSwtmr(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_TASK_PRI_H */
