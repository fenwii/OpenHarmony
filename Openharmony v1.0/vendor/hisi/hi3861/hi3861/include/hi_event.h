/**
 * @file hi_event.h
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
 *
 * Description: system event API.CNcomment:系统事件接口。CNend
 * @li Before sending, waiting, or clearing an event, the event must be created to obtain the event ID.
CNcomment:在发送、等待、清空事件之前首先需要创建事件，获取事件使用ID。CNend
 * @li Wait event: The wait event API cannot be called in the interrupt, interrupt off,
 * and lock task contexts to avoid uncontrollable exceptional scheduling.CNcomment:等待事件:在中断、
关中断、锁任务上下文禁止调用等待事件接口，进而产生不可控的异常调度。CNend
 * @li TX event: The TX event API cannot be called in the interrupt off context to avoid uncontrollable
exceptional scheduling.CNcomment:发送事件:在关中断上下文禁止调用发送事件接口，
进而产生不可控的异常调度。CNend
 * @li Each bit of bit[0:23] of an event can represent an event type. The meaning of each bit is allocated by the user.
CNcomment:一个事件的[0:23]bit的每一bit可以表示一种事件，每一位的意义由用户自定义分配。CNend
 * @li Bit[24:31] of an event are reserved and cannot be used by the user.
CNcomment:一个事件的[24:31]bit系统保留，用户不得使用。CNend   \n
 */

/**
 * @defgroup iot_event Event
 * @ingroup osa
 */
#ifndef __HI_EVENT_H__
#define __HI_EVENT_H__
#include <hi_types_base.h>

#define HI_INVALID_EVENT_ID           0xffffffff   /**< Failed to obtain the event ID.CNcoment:获取事件ID失败CNend  */
#define HI_EVENT_WAITMODE_AND         4            /**< If all expected events occur, the wait is successful.
                                                        It cannot be used with HI_EVENT_WAITMODE_OR at the same time.
                                                        CNcomment:所有预期等待的事件均发生时，才认定等待成功，
                                                        不允许与HI_EVENT_WAITMODE_OR同时使用 CNend */
#define HI_EVENT_WAITMODE_OR          2            /**< If any of the expected events occurs, the wait is successful.
                                                        It cannot be used with HI_EVENT_WAITMODE_AND at the same time.
                                                        CNcomment:所有预期等待的事件发生任意一种，认定等待成功，
                                                        不允许与HI_EVENT_WAITMODE_AND同时使用 CNend */
#define HI_EVENT_WAITMODE_CLR         1            /**< The waited event is cleared when the wait event is successful.
                                                        CNcomment:等待事件成功时，清除等待到的事件CNend  */

/**
* @ingroup  iot_event
* @brief  Creates an event.CNcomment:创建事件。CNend
*
* @par 描述:
*           Creates an event to obtain the event ID.CNcomment:创建事件，获取事件使用ID。CNend
*
* @attention
*           @li The read/write event interface cannot be invoked before system initialization.
CNcomment:在系统初始化之前不能调用读写事件接口。CNend
*           @li In the interrupt, the event object can be written, but cannot be read.
CNcomment:在中断中，可以对事件对象进行写操作，但不能读操作。CNend
*           @li In the lock task scheduling state, a write operation can be performed on an event object, but the
*               read operation cannot be performed.CNcomment:在锁任务调度状态下，可以对事件对象进行写操作，
但不能读操作。CNend
*
* @param  id       [OUT] type #hi_u32*，Event ID.
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
*
* @par 依赖:
*           @li hi_event.h：Describes event APIs.CNcomment:文件用于描述事件相关接口。CNend
* @see  hi_event_delete。
*/
hi_u32 hi_event_create(HI_OUT hi_u32 *id);

/**
* @ingroup  iot_event
* @brief  Defines the TX event. CNcomment:发送事件。CNend
*
* @par 描述:
*           Defines the TX event.CNcomment:发送事件。CNend
*
* @attention
*           @li The read/write event interface cannot be invoked before system initialization.
CNcomment:在系统初始化之前不能调用读写事件接口。CNend
*           @li In the interrupt, the event object can be written, but cannot be read.
CNcomment:在中断中，可以对事件对象进行写操作，但不能读操作。CNend
*           @li In the lock task scheduling state, a write operation can be performed on an event object, but the
*               read operation cannot be performed.CNcomment:在锁任务调度状态下，可以对事件对象进行写操作，
但不能读操作。CNend
*
* @param  id         [IN]  type #hi_u32，Event ID.
* @param  event_bits [IN] type #hi_u32，Set of events to be sent.CNcomment:事件bit位。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
*
* @par 依赖:
*           @li hi_event.h：Describes event APIs.CNcomment:文件用于描述事件相关接口。CNend
* @see  hi_event_wait。
*/
hi_u32 hi_event_send(hi_u32 id, hi_u32 event_bits);

/**
* @ingroup  iot_event
* @brief  Defines the wait event.CNcomment:等待事件。CNend
*
* @par 描述:
*          Defines the wait event.CNcomment:等待事件。CNend
*
* @attention
*           @li The read/write event interface cannot be invoked before system initialization.
CNcomment:在系统初始化之前不能调用读写事件接口。CNend
*           @li In the interrupt, the event object can be written, but cannot be read.
CNcomment:在中断中，可以对事件对象进行写操作，但不能读操作。CNend
*           @li In the lock task scheduling state, a write operation can be performed on an event object, but the
*               read operation cannot be performed.CNcomment:在锁任务调度状态下，可以对事件对象进行写操作，
但不能读操作。CNend
*
* @param  id         [IN] type #hi_u32，Event ID.
* @param  mask       [IN] type #hi_u32，Set of events to be waited for, which may be one bit or multiple bits in
*                    bits 0-23.CNcomment:预等待的事件集合，可以为0~23bit中的1bit或多bit。CNend
* @param  event_bits [OUT] type #hi_u32*，Set of events to be sent.CNcomment:事件bit位。CNend
* @param  timeout    [IN] type #hi_u32，Waiting timeout period (unit: ms).
CNcomment:等待超时时间（单位：ms）。CNend
* @param  flag       [IN] type #hi_u32，Waiting option. For details, see #HI_EVENT_WAITMODE_AND,
*                    #HI_EVENT_WAITMODE_OR, and #HI_EVENT_WAITMODE_CLR.
CNcomment:等待选项,取值见#HI_EVENT_WAITMODE_AND、#HI_EVENT_WAITMODE_OR、#HI_EVENT_WAITMODE_CLR。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
*
* @par 依赖:
*           @li hi_event.h：Describes event APIs.CNcomment:文件用于描述事件相关接口。CNend
* @see  hi_event_send。
*/
hi_u32 hi_event_wait(hi_u32 id, hi_u32 mask, HI_OUT hi_u32 *event_bits, hi_u32 timeout, hi_u32 flag);

/**
* @ingroup  iot_event
* @brief  Defines the clearing event.CNcomment:清除事件。CNend
*
* @par 描述:
*           Defines the clearing event.CNcomment:清除事件。CNend
*
* @attention
*           @li The read/write event interface cannot be invoked before system initialization.
CNcomment:在系统初始化之前不能调用读写事件接口。CNend
*           @li In the interrupt, the event object can be written, but cannot be read.
CNcomment:在中断中，可以对事件对象进行写操作，但不能读操作。CNend
*           @li In the lock task scheduling state, a write operation can be performed on an event object, but the
*               read operation cannot be performed.CNcomment:在锁任务调度状态下，可以对事件对象进行写操作，
但不能读操作。CNend
*
* @param  id         [IN] type #hi_u32，Event ID.
* @param  event_bits [IN] type #hi_u32，Set of events to be cleared, which may be one bit or multiple bits in
*                    bits 0-23.CNcomment:清除的事件集合，可以为0~23bit中的1bit或多bit。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
*
* @par 依赖:
*           @li hi_event.h：Describes event APIs.CNcomment:文件用于描述事件相关接口。CNend
* @see  hi_event_wait。
*/
hi_u32 hi_event_clear(hi_u32 id, hi_u32 event_bits);

/**
* @ingroup  iot_event
* @brief  Deletion event.CNcomment:删除事件。CNend
*
* @par 描述:
*           Defines the deletion event, releasing an event ID.CNcomment:删除事件，释放事件使用id。CNend
*
* @attention
*           @li The read/write event interface cannot be invoked before system initialization.
CNcomment:在系统初始化之前不能调用读写事件接口。CNend
*           @li In the interrupt, the event object can be written, but cannot be read.
CNcomment:在中断中，可以对事件对象进行写操作，但不能读操作。CNend
*           @li In the lock task scheduling state, a write operation can be performed on an event object, but the
*               read operation cannot be performed.CNcomment:在锁任务调度状态下，可以对事件对象进行写操作，
但不能读操作。CNend
*
* @param  id       [IN]  type #hi_u32，Event ID.
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
*
* @par 依赖:
*           @li hi_event.h：Describes event APIs.CNcomment:文件用于描述事件相关接口。CNend
* @see  hi_event_create。
*/
hi_u32 hi_event_delete(hi_u32 id);

/**
* @ingroup  iot_event
* @brief  Initializes event resources.CNcomment:初始化事件资源。CNend
*
* @par 描述:
*           Initializes event resources. This API is called during system initialization only once.
CNcomment:初始化event资源，初始化阶段调用。CNend
*
* @attention Change the number of event resources based on the site requirements.
CNcomment:用户需根据实际使用情况修改event资源个数CNend
*
* @param  max_event_cnt   [IN] type #hi_u8，Number of event resources.CNcomment:event资源个数。CNend
* @param  event_space   [IN]   type #hi_pvoid，Event resource space. If the value is null,
* it indicates that the space is applied internally. If this parameter is not null,
* external space is used to create event resources. Currently, set this parameter to HI_NULL.
CNcomment:event资源空间。传空表示空间由内部申请；非空表示使用外部空间用于创建event资源。
当前请传HI_NULL。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
*
* @par 依赖:
*           @li hi_event.h：Describes event APIs.CNcomment:文件用于描述事件相关接口。CNend
* @see  None
*/
hi_u32 hi_event_init(hi_u8 max_event_cnt, hi_pvoid event_space);

#endif

