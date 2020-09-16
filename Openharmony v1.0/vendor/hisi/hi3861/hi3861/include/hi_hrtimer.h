/**
* @file hi_hrtimer.h
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
* limitations under the License.  \n
*
* Description: 1、In scenarios where the precision is not high, do not use hrtimer. Instead, use a system timer,
*                 because each hrtimer startup, stop, and expiration may increase the error of other high-precision
*                 timers in the queue. CNcomment:在精度要求不高的场景下，尽可能不要使用hrtimer，
*                 应使用系统定时器替代，因为每次hrtimer的启动、停止、到期都可能会增加队列中其它
*                 高精度定时器的误差；CNend
*              2、The callback function of hrtimer is executed in the interrupt context, so you need to comply with
*                 the programming precautions for the interrupt context.CNcomment:hrtimer的回调函数执行在中断上下文，
*                 因此需要遵守中断上下文的编程注意事项。CNend   \n
*/

/**
 * @defgroup hrtimer High Resolution Timer
 * @ingroup drivers
 */
#ifndef __HI_HRTIMER_H__
#define __HI_HRTIMER_H__
#include <hi_types_base.h>

/**
* @ingroup  hrtimer
* @brief  High resolution timer callback function.CNcomment:高精度定时器回调函数。CNend
*
* @par 描述:
*           High resolution timer callback function. When a high resolution timer expires, the high resolution timer
*           module calls this function to notify the user.CNcomment:高精度定时器回调函数，当高精度定时器到期时，
*           高精度定时器模块调用该函数通知使用者。CNend
*
* @attention None
* @param  data [IN] type #hi_u32，Callback function parameter input when the user starts the timer.
CNcomment:用户启动定时器时传入的回调函数参数。CNend
*
* @retval None
* @par 依赖:
*           @li hi_hrtimer.h：Describes timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
* @see  None
*/
typedef hi_void(*hi_hrtimer_callback_f) (hi_u32 data);

/**
* @ingroup  hrtimer
* @brief  Obtains the high resolution timer module handler.CNcomment:获取高精定时器句柄。CNend
*
* @par 描述:
*           Obtains the high resolution timer module handler.CNcomment:获取高精定时器句柄。CNend
*
* @attention None
* @param  timer_handle [OUT] type #hi_u32*，handler obtained. CNcomment:获取到的句柄。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h
*
* @par 依赖:
*           @li hi_hrtimer.h：Describes timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
*
* @see  hi_hrtimer_delete。
*/
hi_u32 hi_hrtimer_create(hi_u32 *timer_handle);

/**
* @ingroup  hrtimer
* @brief  Delete the high resolution timer module handle.CNcomment:删除高精定时器句柄。CNend
*
* @par 描述:
*           Delete the high resolution timer module handle.CNcomment:删除高精定时器句柄。CNend
*
* @attention None
* @param  timer_handle [IN] type #hi_u32，Timer handle, which would be released.
CNcomment:要释放的定时器句柄。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h
*
* @par 依赖:
*           @li hi_hrtimer.h：Describes timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
*
* @see  hi_hrtimer_create。
*/
hi_u32 hi_hrtimer_delete(hi_u32 timer_handle);
/**
* @ingroup  hrtimer
* @brief  Starts a high resolution timer.CNcomment:启动高精度定时器。CNend
*
* @par 描述:
*           Starts the high resolution timer. If the timer has been started, the current timer is stopped and
*           restarted when this API is called.CNcomment:调用该接口启动高精度定时器，如果定时器已经启动，
调用该接口时会停止当前定时器重新启动。CNend
*
* @attention None
* @param  timer_handle [IN] type #hi_u32，Timer handle.CNcomment:定时器句柄。CNend
* @param  expire       [IN] type #hi_u32，Expiration time of the timer (unit: microsecond).When the clock is set to
24M,the maximum of the expiration time is 178s.When the clock is set to 40M,the maximum of the expiration time is 107s.
The expiration time of the timer must be set to a value smaller than the maximum.
CNcomment:定时器超时时间（单位：μs）。24M时钟可设置的最大超时时间为178s，40M时钟可设置的最大超时时间为107s。
          超时时间必须设置为小于最大超时时间的值。CNend
* @param  hrtimer_func [IN] type #hi_hrtimer_callback_f，Callback function when the timer expires.
CNcomment:定时器到期回调函数。CNend
* @param  data         [IN] type #hi_u32，Input parameter of the timer callback function.
CNcomment:定时器回调函数的入参。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h
*
* @par 依赖:
*           @li hi_hrtimer.h：Describes timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
* @see  hi_hrtimer_stop。
*/
hi_u32 hi_hrtimer_start(hi_u32 timer_handle, hi_u32 expire, hi_hrtimer_callback_f hrtimer_func, hi_u32 data);

/**
* @ingroup  hrtimer
* @brief  Stops a high resolution timer.CNcomment:停止高精度定时器。CNend
*
* @par 描述:
*           Stops a high resolution timer. If the timer is stopped when the API is called, no effect is achieved.
CNcomment:调用该接口停止高精度定时器，如果调用该接口时定时器已经停止，不会有任何效果。CNend
*
* @attention None
* @param  timer_handle [IN] type #hi_u32，Timer handle.CNcomment:定时器handle。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h
*
* @par 依赖:
*           @li hi_hrtimer.h：Describes timer APIs.CNcomment:文件用于描述定时器相关接口。CNend
* @see  hi_hrtimer_start。
*/
hi_u32 hi_hrtimer_stop(hi_u32 timer_handle);

#endif
