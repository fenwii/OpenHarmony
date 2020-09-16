/**
 * @file hi_timer.h
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
 * @defgroup iot_systimer System Timer
 * @ingroup osa
 */
#ifndef __INTERFACE_ROM_HI_TIMER_H__
#define __INTERFACE_ROM_HI_TIMER_H__
#include <hi_types_base.h>


/**
 * @ingroup iot_systimer
 *
 * Specifies the type of the timer to be created.CNcomment:用于设置所创建的定时器类型。CNend
 */
typedef enum {
    HI_TIMER_TYPE_ONCE,     /**< Single-period timer.CNcomment:表示单次定时器 CNend */
    HI_TIMER_TYPE_PERIOD,   /**< Periodic timer.CNcomment:表示周期定时器 CNend */
    HI_TIMER_TYPE_MAX       /**< Maximum value, which cannot be used.CNcomment:最大值，不可使用 CNend */
} hi_timer_type;

/**
* @ingroup  iot_systimer
* @brief  Defines the type of the timer callback function.CNcomment:定义定时器回调函数的类型。CNend
*
* @par 描述：
*           Defines the type of the timer callback function.CNcomment:定义定时器回调函数的类型。CNend
*
* @attention None
* @param  data [IN] type #hi_u32，callback input parameter.CNcomment:回调入参。CNend
*
* @retval None
* @par 依赖:
*            @li hi_timer.h：Describes the timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
* @see hi_timer_start | hi_timer_stop
*/
typedef hi_void (*hi_timer_callback_f)(hi_u32 data);

/**
* @ingroup  iot_systimer
* @brief  Creates the system timer.CNcomment:获取定时器句柄。CNend
*
* @par 描述:
*           Creates the system timer.CNcomment:获取高精定时器句柄。CNend
*
* @attention None
* @param  timer_handle [OUT] type #hi_u32*，handle.CNcomment:获取到的句柄。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
*
* @par 依赖:
*          @li hi_timer.h：Describes the timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
* @see  hi_timer_delete。
*/
hi_u32 hi_timer_create(hi_u32 *timer_handle);

/**
* @ingroup  iot_systimer
* @brief  Starts the system timer.CNcomment:启动系统定时器。CNend
*
* @par 描述:
*            This API is used in the following scenarios:CNcomment:本API接口使用分为以下几个场景：CNend
*            @li If no timer is created, create and start a timer.
CNcomment:如果未启动定时器，则直接启动。CNend
*            @li If the timer expires and is called again, start the timer directly.
CNcomment:如果该定时器到期后调用，则直接启动定时器。CNend
*            @li If the timer does not expire, stop and restart the timer.
CNcomment:如果定时器没有到期，则停止该定时器，重新启动定时器。CNend
*
* @attention This timer callback function is executed in the interrupt context. Therefore, the callback function should
*            be as simple as possible and the functions such as sleep and wait semaphores that trigger scheduling
*            cannot be used.CNcomment:本定时器回调函数执行于中断上下文，回调函数尽量简单，不能使用睡眠、
等待信号量等引起调度的函数。CNend
*
* @param  timer_handle  [IN]  type #hi_u32，handle.CNcomment:句柄。CNend
* @param  type          [IN]   type #hi_timer_type，timer type.CNcomment:定时器类型。CNend
* @param  expire        [IN]   type #hi_u32，timeout period of the timer (unit: ms). If this parameter is set to 0,
*                       the default value is 10 ms.CNcomment:定时器超时时间（单位：ms）。配置为0时，默认为10ms。CNend
* @param  timer_func    [IN]   type #timer_proc_func，timer callback function.CNcomment:定时器回调函数。CNend
* @param  data          [IN]   type #hi_u32，callback input parameter.CNcomment:回调函数传参。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
*
* @par 依赖:
*          @li hi_timer.h：Describes the timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
* @see hi_timer_stop
*/
hi_u32 hi_timer_start(hi_u32 timer_handle, hi_timer_type type, hi_u32 expire,
                      hi_timer_callback_f timer_func, hi_u32 data);

/**
* @ingroup  iot_systimer
* @brief  Stops the system timer.CNcomment:停止系统定时器。CNend
*
* @par 描述:
*          Stops the system timer.CNcomment:停止系统定时器。CNend
*
* @attention This API only stops the timer and does not delete the timer.CNcomment:本接口仅停止定时器，
并不删除该定时器。CNend
* @param  timer_handle [IN] type #hi_u32，handle.CNcomment:句柄。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
*
* @par 依赖:
*          @li hi_timer.h：Describes the timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
* @see hi_timer_start | hi_timer_delete
*/
hi_u32 hi_timer_stop(hi_u32 timer_handle);

/**
* @ingroup  iot_systimer
* @brief  Deletes the timer.CNcomment:删除定时器。CNend
*
* @par 描述:
*           Deletes the timer.CNcomment:删除定时器。CNend
*
* @attention
*            @li If the timer does not expire, stop the timer before deleting it.
CNcomment:如果定时器未到期，则先停止该定时器再删除。CNend
*
* @param  timer_handle [IN] type #hi_u32，handle.CNcomment:句柄。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
*
* @par 依赖:
*          @li hi_timer.h：Describes the timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
* @see hi_timer_start | hi_timer_stop
*/
hi_u32 hi_timer_delete(hi_u32 timer_handle);

#endif
