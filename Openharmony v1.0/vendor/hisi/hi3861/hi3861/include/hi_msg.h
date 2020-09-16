/**
* @file hi_msg.h
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
* limitations under the License.     \n
*
* Description: message APIs.CNcomment:消息接口。CNend
* @li Wait message: the wait message API cannot be called, to avoid uncontrollable exception scheduling.
CNcomment:等待消息:在中断、关中断、锁任务上下文禁止调用等待消息接口，进而产生不可控的异常调度。CNend
* @li TX message: In the interrupt off context, the message TX API cannot be called, to avoid uncontrollable exception
*     scheduling.CNcomment:发送消息:在关中断上下文禁止调用发送消息接口，进而产生不可控的异常调度。CNend
* @li TX message (the timeout period is not 0): In the interrupt and task locked context, the message TX API cannot be
*     called, to avoid uncontrollable exception scheduling.CNcomment:发送消息(超时时间非0):在中断、锁任务上下文禁止调用
超时时间非0发送消息接口，进而产生不可控的异常调度。CNend  \n
*/

/**
 * @defgroup iot_msgqueue Message Queue
 * @ingroup osa
 */
#ifndef __HI_MSG_H__
#define __HI_MSG_H__
#include <hi_types_base.h>

/**
 * @ingroup iot_msgqueue
 *
 * Failed to read the message queue.CNcomment:读取消息队列出错。CNend
 */
#define HI_MSG_INVALID_MSG_NUM 0xFFFFFFFF
#define HI_SYS_MSG_PARAM_NUM_MAX 4

typedef struct {
    hi_u32 msg_id; /* < Message ID.CNcomment:消息ID CNend */
    uintptr_t param[HI_SYS_MSG_PARAM_NUM_MAX]; /* < Message parameter.CNcomment:消息参数 CNend */
} hi_sys_queue_msg;

/**
* @ingroup  iot_msgqueue
* @brief   Creates a message queue.CNcomment:创建消息队列。CNend
*
* @par 描述:
*           Creates a message queue.CNcomment:创建消息队列。CNend
*
* @attention The number of message queues supported by the system needs to be set during initialization.
CNcomment:系统支持的总消息队列个数，需要在初始化阶段设置。CNend
*
* @param  id           [OUT] type  #hi_u32*，Handle of the created message queue.
CNcomment:所创建的消息队列句柄。CNend
* @param  queue_len    [IN]  type  #hi_u16，Message queue length, that is, the number of messages that can be stored
*                      in the message queue.CNcomment:消息队列长度，即该消息队列支持存储多少条消息。CNend
* @param  msg_size     [IN]  type  #hi_u32，Size of each message in the message queue (unit: byte)
CNcomment:消息队列中一条消息大小（单位：byte）。CNend
*
* @retval #HI_ERR_SUCCESS           Success
* @retval #HI_ERR_MSG_INVALID_PARAM An input argument is incorrect, the handle pointer is null, the name address is
*         null, or the message queue length is 0.CNcomment:入参错误、句柄指针为空、名字地址为空、消息队列长度为0。CNend
* @retval #HI_ERR_MSG_CREATE_Q_FAIL An error occurred when creating the message queue, for example, insufficient
*         memory or insufficient message queue resources.
CNcomment:创建消息队列错误，比如：内存不足、消息队列资源不足。CNend
* @par 依赖:
*            @li hi_msg.h：Describes message queue APIs.CNcomment:文件用于描述消息队列相关接口。CNend
*            @li hi_config.h：Describes the message queue configuration.CNcomment:文件用于消息队列配置。CNend
*            @li hi_errno.h：Describes file configuration error codes.CNcomment:文件配置错误码。CNend
* @see hi_msg_queue_delete。
*/
hi_u32 hi_msg_queue_create(HI_OUT hi_u32 *id, hi_u16 queue_len, hi_u32 msg_size);

/**
* @ingroup  iot_msgqueue
* @brief  Deletes a message queue.CNcomment:删除消息队列。CNend
*
* @par 描述:
*          Deletes a message queue.CNcomment:删除消息队列。CNend
*
* @attention None
* @param  id           [IN] type  #hi_u32，Handle of the created message queue.CNcomment:消息队列句柄。CNend
*
* @retval #HI_ERR_SUCCESS           Success
* @retval #HI_ERR_MSG_Q_DELETE_FAIL An error occurred with the message queue, for example, the ID is out of
*         range, the message queue is not created, or the message queue is in use.CNcomment:删除消息队列错误，
比如：ID越界、消息队列未创建、消息队列正在使用中无法删除等。CNend
* @par 依赖:
*            @li hi_msg.h：Describes message queue APIs.CNcomment:文件用于描述消息队列相关接口。CNend
*            @li hi_config.h：Describes the message queue configuration.CNcomment:文件用于消息队列配置。CNend
*            @li hi_errno.h：Describes file configuration error codes.CNcomment:文件配置错误码。CNend
 @see hi_msg_queue_create。
*/
hi_u32 hi_msg_queue_delete(hi_u32 id);

/**
* @ingroup  iot_msgqueue
* @brief   Sends a message.CNcomment:发送消息。CNend
*
* @par 描述:
*           Sends a message.发送消息。CNend
*
* @attention None
* @param  id           [IN] type #hi_u32，Message queue handle.CNcomment:消息队列句柄。CNend
* @param  msg          [IN] type #hi_pvoid，Message content pointer.CNcomment:消息内容指针。CNend
* @param  timeout_ms   [IN] type #hi_u32，Timeout period for sending a message. The value 0 indicates
*                      that the message is sent immediately.CNcomment:消息发送的最大超时时间(单位：ms)，
立即发送时写0。CNend
* @param  msg_size     [IN] type #hi_u32，Size of the sent message (unit: byte).
CNcomment:发送消息大小（单位：byte）。CNend
*
* @retval #HI_ERR_SUCCESS           Success.
* @retval #HI_ERR_MSG_SEND_FAIL     An error occurs with the message queue, for example, an input argument is
*                                   incorrect, the message queue is not created, the size of the sent data is
*                                   greater than the configured size when the queue is created, or the API is
*                                   used in an interrupt but the timeout period is not 0.
CNcomment:发送消息队列错误，包括：入参错误、消息队列未创建、发送数据大于队列创建时设置大小、
中断中使用但超时时间不为0。CNend
*
* @retval #HI_ERR_MSG_INVALID_PARAM An input argument is incorrect or the message queue pointer is null.
CNcomment:入参错误、消息队列指针为空。CNend
*
* @par 依赖:
*            @li hi_msg.h：Describes message queue APIs.CNcomment:文件用于描述消息队列相关接口。CNend
*            @li hi_config.h：Describes the message queue configuration.CNcomment:文件用于消息队列配置。CNend
*            @li hi_errno.h：Describes file configuration error codes.CNcomment:文件配置错误码。CNend
* @see hi_msg_queue_wait。
*/
hi_u32 hi_msg_queue_send(hi_u32 id, hi_pvoid msg, hi_u32 timeout_ms, hi_u32 msg_size);

/**
* @ingroup  iot_msgqueue
* @brief  Receives a message.CNcomment:接收消息。CNend
*
* @par 描述:
*           Receives a message.CNcomment:接收消息。CNend
*
* @attention None
* @param  id          [IN]   type #hi_u32，Message queue handle.CNcomment:消息队列句柄。CNend
* @param  msg         [OUT]  type #hi_pvoid，Message content pointer.CNcomment:消息内容指针。CNend
* @param  timeout_ms  [IN]   type #hi_u32，Timeout period for receiving a message. The value #HI_SYS_WAIT_FOREVER
*                     indicates permanent wait.CNcomment:消息接收超时时间(单位：ms)，
如果表示永久等待使用#HI_SYS_WAIT_FOREVER。CNend
* @param  msg_size    [IN]   type #hi_u32*，Expected message length (unit: byte),if wait msg success, this val will fill
with actually size of msg.
CNcomment:输入期望的消息长度（单位：byte），如果等待消息成功，该值将被赋值为实际接收到的消息长度。CNend
*
* @retval #HI_ERR_SUCCESS           Success.CNcomment:消息接收成功。CNend
* @retval #HI_ERR_MSG_WAIT_FAIL     An error occurs with the message queue, for example, an input argument is incorrect,
*                                   the message queue is not created, the size of the waiting message is smaller than
*                                   the size set when the queue is created, or the API is used in an interrupt but the
*                                   timeout period is not 0.CNcomment:等待消息队列错误，比如：入参不正确、消息队列未
创建、等待消息大小小于队列创建时设置大小、中断中等待超时非零的消息队列。CNend
* @retval #HI_ERR_MSG_INVALID_PARAM An input argument is incorrect or the message queue pointer is null.
CNcomment:入参错误、消息队列指针为空。CNend
* @retval #HI_ERR_MSG_WAIT_TIME_OUT No message is received when the waiting times out.
CNcomment:等待超时未收到消息。CNend
* @par 依赖:
*            @li hi_msg.h：Describes message queue APIs.CNcomment:文件用于描述消息队列相关接口。CNend
*            @li hi_config.h：Describes the message queue configuration.CNcomment:文件用于消息队列配置。CNend
*            @li hi_errno.h：Describes file configuration error codes.CNcomment:文件配置错误码。CNend
* @see hi_msg_queue_send。
*/
hi_u32 hi_msg_queue_wait(hi_u32 id, HI_OUT hi_pvoid msg, hi_u32 timeout_ms, hi_u32* msg_size);

/**
* @ingroup  iot_msgqueue
* @brief   Checks whether the message queue is full.CNcomment:检查消息队列是否已满。CNend
*
* @par 描述:
*           Checks whether the message queue is full.CNcomment:检查消息队列是否已满。CNend
*
* @attention None
* @param  id        [IN] type #hi_u32，Message queue handle.CNcomment:消息队列句柄。CNend
*
* @retval #HI_TRUE  The message queue is full or the message queue information fails to be obtained.
CNcomment:消息队列已满或获取消息队列信息失败。CNend
* @retval #HI_FALSE The message queue is not full.CNcomment:消息队列未满。CNend
* @par 依赖:
*            @li hi_msg.h：Describes message queue APIs.CNcomment:文件用于描述消息队列相关接口。CNend
* @see None
*/
hi_bool hi_msg_queue_is_full(hi_u32 id);

/**
* @ingroup  iot_msgqueue
* @brief   Obtains the number of used message queues.CNcomment:获取当前已经使用的消息队列个数。CNend
*
* @par 描述:
*           Obtains the number of used message queues.CNcomment:获取当前已经使用的消息队列个数。CNend
*
* @attention None
* @param  id       [IN] #hi_u32，Handle of the created message queue.CNcomment:消息队列句柄。CNend
*
* @retval #HI_ERR_MSG_INVALID_MSG_NUM  Failed to read the message queue.CNcomment:读取消息队列出错。CNend
* @retval value                        Number of used message queues.CNcomment:消息队列使用个数。CNend
* @par 依赖:
*            @li hi_msg.h：Describes message queue APIs.CNcomment:文件用于描述消息队列相关接口。CNend
* @see None
*/
hi_u32 hi_msg_queue_get_msg_num(hi_u32 id);

/**
* @ingroup  iot_msgqueue
* @brief  Obtains the number of message queues.CNcomment:获取消息队列总个数。CNend
*
* @par 描述:
*           Obtains the number of message queues.CNcomment:获取消息队列总个数。CNend
*
* @attention None
* @param  id       [IN] #hi_u32，Handle of the created message queue.CNcomment:消息队列句柄。CNend
*
* @retval #HI_ERR_MSG_INVALID_MSG_NUM  An error occurs with the message queue. For example: An input argument is
*         incorrect, or the message queue is not created.
CNcomment:读取消息队列出错、入参错误、消息队列未创建。CNend
* @retval value                        Number of message queues.CNcomment:消息队列总个数。CNend
* @par 依赖:
*            @li hi_msg.h：Describes message queue APIs.CNcomment:文件用于描述消息队列相关接口。CNend
* @see None
*/
hi_u32 hi_msg_queue_get_msg_total(hi_u32 id);


/**
* @ingroup  iot_msgqueue
* @brief   Send a message to the head of the queue.发送消息到队列头。Nend
*
* @par 描述:
*           Send a message to the head of the queue.发送消息到队列头。CNend
*
* @attention None
* @param  id           [IN] type #hi_u32，Message queue handle.CNcomment:消息队列句柄。CNend
* @param  msg          [IN] type #hi_pvoid，Message content pointer.CNcomment:消息内容指针。CNend
* @param  timeout_ms   [IN] type #hi_u32，Timeout period for sending a message. The value 0 indicates
*                      that the message is sent immediately.CNcomment:消息发送的最大超时时间(单位：ms)，
立即发送时写0。CNend
* @param  msg_size     [IN] type #hi_u32，Size of the sent message (unit: byte).
CNcomment:发送消息大小（单位：byte）。CNend
*
* @retval #HI_ERR_SUCCESS           Success.
* @retval #HI_ERR_MSG_SEND_FAIL     An error occurs with the message queue, for example, an input argument is
*                                   incorrect, the message queue is not created, the size of the sent data is
*                                   greater than the configured size when the queue is created, or the API is
*                                   used in an interrupt but the timeout period is not 0.
CNcomment:发送消息队列错误，包括：入参错误、消息队列未创建、发送数据大于队列创建时设置大小、
中断中使用但超时时间不为0。CNend
*
* @retval #HI_ERR_MSG_INVALID_PARAM An input argument is incorrect or the message queue pointer is null.
CNcomment:入参错误、消息队列指针为空。CNend
*
* @par 依赖:
*            @li hi_msg.h：Describes message queue APIs.CNcomment:文件用于描述消息队列相关接口。CNend
*            @li hi_config.h：Describes the message queue configuration.CNcomment:文件用于消息队列配置。CNend
*            @li hi_errno.h：Describes file configuration error codes.CNcomment:文件配置错误码。CNend
* @see hi_msg_queue_wait。
*/
hi_u32 hi_msg_queue_send_msg_to_front(hi_u32 id,  hi_pvoid msg, hi_u32 msg_size, hi_u32 timeout_ms);


#endif

