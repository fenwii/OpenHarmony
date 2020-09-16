/**
 * @file hi_systick.h
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
 * @defgroup systick System Tick Status
 * @ingroup drivers
 */
#ifndef __HI_SYSTICK_H__
#define __HI_SYSTICK_H__
#include <hi_types_base.h>

/**
* @ingroup  systick
* @brief  Obtains systick currect value. CNcomment:获取systick当前计数值。CNend
*
* @par 描述:
* @li   Obtains the current count value of systick. The time of each value is determined by the systick clock source.
*       The systick clock is 32Khz, and the tick value is 1/32000 seconds.CNcomment:获取systick当前计数值。
每个值的时间由systick时钟源决定。systick时钟为32Khz，一个tick值为1/32000秒。CNend
* $li   After the system is powered on, systick immediately adds a count from 0.CNcomment:系统上电运行后，
systick立刻从0开始递增加一计数。CNend
*
* @attention The delay interface is invoked in the interface. Therefore, it is prohibited to invoke this interface in
*            the interrupt context.CNcomment:接口内调用了延时接口，所以禁止在中断上下文中调用该接口。CNend
* @param  None
*
* @retval #hi_u64 Indicates the obtained current count value.CNcomment:获取到的当前计数值。CNend
*
* @par 依赖:
*           @li hi_systick.h：Describes systick APIs.CNcomment:文件用于描述SYSTICK相关接口。CNend
* @see  hi_systick_clear。
*/
hi_u64 hi_systick_get_cur_tick(hi_void);

/**
* @ingroup  systick
* @brief  The value of systick is cleared.CNcomment:将systick计数值清零。CNend
*
* @par 描述:
*         The value of systick is cleared.CNcomment:将systick计数值清零。CNend
*
* @attention After the interface is returned, the clock cycles of three systick clocks need to be cleared.
CNcomment:接口返回后需要等三个systick的时钟周期才会完成清零。CNend
* @param  None
*
* @retval None
* @par 依赖:
*           @li hi_systick.h：Describes systick APIs.CNcomment:文件用于描述SYSTICK相关接口。CNend
* @see  hi_systick_get_cur_tick。
*/
hi_void hi_systick_clear(hi_void);

/**
* @ingroup  systick
* @brief Get the millisecond value counted by systick. CNcomment:获取以systick计数的毫秒值。CNend
*
* @par 描述:
* @li   Calculate the current millisecond value according to the current value of systick and the actual frequency of
32K.CNcomment:根据systick的当前值与32K实际的频率计算当前的毫秒值。CNend
*
* @attention The delay interface is invoked in the interface. Therefore, it is prohibited to invoke this interface in
*            the interrupt context.CNcomment:接口内调用了延时接口，所以禁止在中断上下文中调用该接口。CNend
* @param  None
*
* @retval #hi_u64 Indicates the obtained current millisecond.CNcomment:获取到的当前毫秒计数值。CNend
*
* @par 依赖:
*           @li hi_systick.h：Describes systick APIs.CNcomment:文件用于描述SYSTICK相关接口。CNend
* @see  hi_systick_get_cur_ms。
*/
hi_u64 hi_systick_get_cur_ms(hi_void);

/**
* @ingroup  systick
* @brief  Sets the real time of the system, base on systick, not effect by deep sleep.
CNcomment:设置系统实时时间，基于systick，不受深睡影响。CNend
*
* @par 描述:
*           Sets the real time of the system.CNcomment:设置系统实时时间。CNend
*
* @attention None
* @param  seconds            [IN] type #hi_u32，set the real time of the system to this value.
CNcomment:将系统实时时间设置为该值。CNend
*
* @retval None.
* @par 依赖:
*           @li hi_systick.h：Describes systick APIs.CNcomment:文件用于描述SYSTICK相关接口。CNend
*/
hi_void hi_systick_set_real_time(hi_u32 sec);

/**
* @ingroup  systick
* @brief  Obtains the real time of the system, base on systick, not effect by deep sleep
CNcomment:获取系统实时时间（单位：s），基于systick，不受深睡影响。CNend
*
* @par 描述:
*           Obtains the real time of the system (unit: s).CNcomment:获取系统实时时间（单位：s）。CNend
*
* @attention None
* @param None
*
* @retval #hi_u32 Real time of the system.CNcomment: 系统实时时间。CNend
* @par 依赖:
*           @li hi_systick.h：Describes systick APIs.CNcomment:文件用于描述SYSTICK相关接口。CNend
*/
hi_u32 hi_systick_get_real_time(hi_void);

#endif
