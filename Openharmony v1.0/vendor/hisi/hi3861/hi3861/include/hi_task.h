/**
 * @file hi_task.h
 *
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @defgroup iot_task Task
 * @ingroup osa
 */
#ifndef __HI_TASK_H__
#define __HI_TASK_H__

#include <hi_types_base.h>

#define HI_INVALID_TASK_ID   0xFFFFFFFF
#define HI_TASK_NAME_LEN     32
#define HI_DEFAULT_TSKNAME   "default"  /**< hi_task_attr default value. CNcomment:hi_task_attr的默认值CNend */
#define HI_DEFAULT_TSKPRIO   20         /**< hi_task_attr default value. CNcomment:hi_task_attr的默认值CNend */
#define HI_DEFAULT_STACKSIZE (4 * 1024) /**< hi_task_attr default value. CNcomment:hi_task_attr的默认值CNend */
#define NOT_BIND_CPU         (-1)

typedef struct {
    hi_char name[HI_TASK_NAME_LEN]; /**< Task entrance function.CNcomment:入口函数CNend */
    hi_u32 id;                      /**< Task ID.CNcomment:任务ID CNend */
    hi_u16 status;                  /**< Task status.CNcomment:任务状态 CNend */
    hi_u16 priority;                /**< Task priority.CNcomment:任务优先级 CNend */
    hi_pvoid task_sem;              /**< Semaphore pointer.CNcomment:信号量指针CNend */
    hi_pvoid task_mutex;            /**< Mutex pointer.CNcomment:互斥锁指针CNend */
    hi_u32 event_stru[3];           /**< Event: 3 nums.CNcomment:3个事件CNend */
    hi_u32 event_mask;              /**< Event mask.CNcomment:事件掩码CNend */
    hi_u32 stack_size;              /**< Task stack size.CNcomment:栈大小CNend */
    hi_u32 top_of_stack;            /**< Task stack top.CNcomment:栈顶CNend */
    hi_u32 bottom_of_stack;         /**< Task stack bottom.CNcomment:栈底CNend */
    hi_u32 mstatus;                 /**< Task current mstatus.CNcomment:当前mstatusCNend */
    hi_u32 mepc;                    /**< Task current mepc.CNcomment:当前mepc.CNend */
    hi_u32 tp;                      /**< Task current tp.CNcomment:当前tp.CNend */
    hi_u32 ra;                      /**< Task current ra.CNcomment:当前ra.CNend */
    hi_u32 sp;                      /**< Task SP pointer.CNcomment:当前SP.CNend */
    hi_u32 curr_used;               /**< Current task stack usage.CNcomment:当前任务栈使用率CNend */
    hi_u32 peak_used;               /**< Task stack usage peak.CNcomment:栈使用峰值CNend */
    hi_u32 overflow_flag;           /**< Flag that indicates whether a task stack overflow occurs.
                                       CNcomment:栈溢出标记位CNend */
} hi_task_info;

typedef struct {
    hi_u16 task_prio;
    hi_u32 stack_size;
    hi_u32 task_policy;
    hi_u32 task_nice;
    hi_u32 task_cpuid;
    hi_char *task_name;
    hi_void *resved;
} hi_task_attr;

/**
* @ingroup  iot_task
* @brief  Creates a task.CNcomment:创建任务。CNend
*
* @par 描述:
*           Creates a task.CNcomment:创建任务。CNend
*
* @attention
*           @li The space occupied by a task name string must be applied for by the caller and saved statically.
*               The task name is not stored internally in the API.CNcomment:任务名字符串占用空间需要调用者
                申请并静态保存，接口内部不对任务名进行存储。CNend
*           @li If the size of the specified task stack is 0, use the default size specified by
*               #OS_TSK_DEFAULT_STACK_SIZE. CNcomment:若指定的任务栈大小为0，则使用配置项
                HI_DEFAULT_STACKSIZE指定默认的任务栈大小。CNend
*           @li The size of the task stack should be 8-byte aligned. The principle for determining the task stack
*               size is as follows: Do not use a too large or too small task stack size (to avoid waste or
*               overflow).CNcomment:任务栈的大小按8byte大小对齐。确定任务栈大小的原则：够用即可（多则浪费，
                少则任务栈溢出）。CNend
*           @li The recommended user priority should be within the range of [10, 30]. Do not use the priorities of
*               [0, 5] and [31].CNcomment:用户优先级配置建议使用[10,30]，切记不可使用[0,5]和[31]号的优先级。CNend
*
* @param  taskid         [OUT] type #hi_u32*，task ID.CNcomment:任务ID号。CNend
* @param  attr           [IN]  type #const task_attr_t*，task attributes,when NULL was set here,the properties
                               are configured as follows: task_name:"default" task_prio:20  stack_size:(4*1024)
                               CNcomment:任务属性,当该值为空时配置如下:任务名:"default"
                               任务优先级:20 任务栈大小:(4*1024),CNend
* @param  task_route     [IN]  type #task_route task entry function.CNcomment:任务入口函数。CNend
* @param  arg            [IN]  type #hi_void*，parameter that needs to be input to the task entry when a task is
*                              created. If this parameter does not need to be input, set this parameter to 0.
                               CNcomment:创建任务时需要传给任务入口的参数。如果不需要传递，参数直接填0。CNend
*
* @retval #0         Success
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  hi_task_delete。
*/
hi_u32 hi_task_create(hi_u32 *taskid, const hi_task_attr *attr,
                      hi_void* (*task_route)(hi_void *), hi_void *arg);

/**
* @ingroup  iot_task
* @brief  Deletes a task.CNcomment:删除任务。CNend
*
* @par 描述:
*          Deletes a task.CNcomment:删除任务。CNend
*
* @attention
*           @li Use this API with caution. A task can be deleted only after the confirmation of the user. The idle task
*           and Swt_Task cannot be deleted.idle.CNcomment:任务及Swt_Task任务不能被删除。CNend
*           @li When deleting a task, ensure that the resources (such as mutex and semaphore) applied by the task have
*           been released.在删除任务时要保证任务申请的资源（如互斥锁、信号量等）已被释放。CNend
*
* @param  taskid      [IN] type #hi_u32，task ID. CNcomment:任务ID号。CNend
*
* @retval #0         Success
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  hi_task_create。
*/
hi_u32 hi_task_delete(hi_u32 taskid);

/**
* @ingroup  iot_task
* @brief  Suspends a task.CNcomment:挂起任务。CNend
*
* @par 描述:
*           Suspends a task.CNcomment:挂起指定任务。CNend
*
* @attention
*          @li A task cannot be suspended if it is the current task and is locked.
CNcomment:挂起任务的时候若为当前任务且已锁任务，则不能被挂起。CNend
*          @li The idle task and Swt_Task cannot be suspended.
CNcomment:idle任务及Swt_Task任务不能被挂起。CNend
*          @li The task cannot be blocked or suspended in the lock task status.
CNcomment:在锁任务调度状态下，禁止任务阻塞。CNend
*
* @param  taskid      [IN] type #hi_u32，task ID. CNcomment:任务ID号。CNend
*
* @retval #0         Success
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  hi_task_resume。
*/
hi_u32 hi_task_suspend(hi_u32 taskid);

/**
* @ingroup  iot_task
* @brief  Resumes a task.CNcomment:恢复挂起任务。CNend
*
* @par 描述:
*           Resumes a task.CNcomment:恢复挂起指定任务。CNend
*
* @attention None
* @param  taskid      [IN] type #hi_u32，task ID. CNcomment:任务ID号。CNend
*
* @retval #0         Success
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  hi_task_suspend。
*/
hi_u32 hi_task_resume(hi_u32 taskid);

/**
* @ingroup  iot_task
* @brief  Obtains the task priority.CNcomment:获取任务优先级。CNend
*
* @par 描述:
*           Obtains the task priority.CNcomment:获取任务优先级。CNend
*
* @attention None
*
* @param  taskid      [IN] type #hi_u32，task ID. CNcomment:任务ID号。CNend
* @param  priority   [OUT] type #hi_u32*，task priority.CNcomment:任务优先级。CNend
*
* @retval #0         Success
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  hi_task_set_priority。
*/
hi_u32 hi_task_get_priority(hi_u32 taskid, hi_u32 *priority);

/**
* @ingroup  iot_task
* @brief  Sets the task priority.CNcomment:设置任务优先级。CNend
*
* @par 描述:
            Sets the task priority.CNcomment:设置任务优先级。CNend
*
* @attention
*           @li Only the ID of the task created by the user can be configured.
CNcomment:仅可配置用户自己创建的任务ID。CNend
*           @li The recommended user priority should be within the range of [10, 30]. Do not use the priorities of
*            [0, 5] and [31].CNcomment:用户优先级配置建议使用[10,30]，切记不可使用[0,5]和[31]号的优先级。CNend
*           @li Setting user priorities may affect task scheduling. The user needs to plan tasks in the SDK.
CNcomment:设置用户优先级有可能影响任务调度，用户需要SDK中对各任务统一规划。CNend
*
* @param  taskid      [IN] type #hi_u32，task ID. CNcomment:任务ID号。CNend
* @param  priority    [IN] type #hi_u32，task priority.CNcomment:任务优先级。CNend
*
* @retval #0         Success
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  hi_task_get_priority。
*/
hi_u32 hi_task_set_priority(hi_u32 taskid, hi_u32 priority);

/**
* @ingroup  iot_task
* @brief  Obtains the task information.CNcomment:获取任务信息。CNend
*
* @par 描述:
*           Obtains the task information.CNcomment:获取任务信息。CNend
*
* @attention None
* @param  taskid      [IN] type #hi_u32，task ID. CNcomment:任务ID号。CNend
* @param  inf        [OUT] type #hi_task_info* ，task information.CNcomment:任务信息。CNend
*
* @retval #0         Success
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  None
*/
hi_u32 hi_task_get_info(hi_u32 taskid, hi_task_info *inf);

/**
* @ingroup  iot_task
* @brief  Obtains the current task ID.CNcomment:获取当前任务ID。CNend
*
* @par 描述:
*         Obtains the current task ID.CNcomment:获取当前任务ID。CNend
*
* @attention None
* @param  None
*
* @retval #hi_u32  Task ID. If the task fails, #HI_INVALID_TASK_ID is returned.
CNcomment:任务ID，失败返回#HI_INVALID_TASK_ID。CNend
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  None
*/
hi_u32 hi_task_get_current_id(hi_void);

/**
* @ingroup  iot_task
* @brief  Lock task switch.CNcomment:禁止系统任务调度。CNend
*
* @par 描述:
*         Lock task switch.CNcomment:禁止系统任务调度。CNend
*
* @attention  Work pair with hi_task_unlock.CNcomment:与hi_task_unlock配对使用。CNend
* @param  None
*
* @retval None
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see None
*/
hi_void hi_task_lock(hi_void);

/**
* @ingroup  iot_task
* @brief  Unlock task switch. CNcomment:允许系统任务调度。CNend
*
* @par 描述:
*         Unlock task switch. CNcomment:允许系统任务调度。CNend
*
* @attention  Work pair with hi_task_lock; Call hi_task_lock to disable task switch, then call hi_task_unlock
*             reenable it.
CNcomment:与hi_task_lock配对使用；先调用hi_task_lock禁止任务调度，然后调用hi_task_unlock打开任务调度。CNend
* @param  None
*
* @retval  None
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  None
*/
hi_void hi_task_unlock(hi_void);

/**
* @ingroup  iot_task
* @brief Task sleep.CNcomment:任务睡眠。CNend
*
* @par 描述:
*          Task sleep.CNcomment:任务睡眠。CNend
*
* @attention
*           @li In the interrupt processing function or in the case of a lock task, the hi_sleep operation fails.
CNcomment:在中断处理函数中或者在锁任务的情况下，执行hi_sleep操作会失败。CNend
*           @li When less than 10 ms, the input parameter value should be replaced by 10 ms. When greater than 10 ms,
*            the input parameter value should be exactly divided and then rounded-down to the nearest integer.
CNcomment:入参小于10ms时，当做10ms处理，Tick=1；大于10ms时，整除向下对齐，Tick = ms/10。CNend
*           @li This function cannot be used for precise timing and will be woken up after Tick system scheduling.
*            The actual sleep time is related to the time consumed by the Tick when the function is called.
CNcomment:本函数不能用于精确计时，将在Tick个系统调度后唤醒，实际睡眠时间与函数被调用时该Tick已消耗的时间相关。CNend
* @param  ms      [IN] type #hi_u32，sleep time (unit: ms). The precision is 10 ms.
CNcomment:睡眠时间（单位：ms），精度为10ms。CNend
*
* @retval #0         Success
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  None
*/
hi_u32 hi_sleep(hi_u32 ms);

/**
* @ingroup  iot_task
* @brief Regiseter idle task callback.CNcomment:注册idle任务回调函数。CNend
*
* @par 描述:
*          Regiseter idle task callback, if callback is NULL, means cancel registration.
CNcomment:注册idle任务回调函数，如果回调函数为空，表示取消注册。CNend
*
* @attention
*           @li lowper sleep process handle after callback, callback should not contain complicated
operations that affect lowpower process .
CNcomment:低功耗睡眠处理在idle回调执行之后，回调函数避免处理复杂操作影响低功耗流程。CNend
*           @li When less than 10 ms, the input parameter value should be replaced by 10 ms. When greater than 10 ms,
* @param  cb      [IN] type #hi_void_callback, callback in idle task.CNcomment:idle任务中的回调函数。CNend
*
* @retval #None
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  None
*/
hi_void hi_task_register_idle_callback(hi_void_callback cb);

/**
* @ingroup  iot_task
* @brief Wait task excute finish.CNcomment:等待任务执行结束。CNend
*
* @par 描述:
*          Wait task excute finish.CNcomment:等待任务执行结束。CNend
*
* @attention None
* @param  taskid            [IN] type #hi_u32, task id of the task to be waited finish.
CNcomment:被等待结束的任务ID。CNend
* @param  wait_interval  [IN] type #hi_u32, interval time of query task status when waiting. at least one tick.
CNcomment:等待时查询任务状态的间隔时间，至少间隔1个Tick。CNend
*
* @retval #None
* @par 依赖:
*           @li hi_task.h：Describes the task APIs.CNcomment:文件用于描述任务相关接口。CNend
* @see  None
*/
hi_void hi_task_join(hi_u32 taskid, hi_u32 wait_interval);

#endif
