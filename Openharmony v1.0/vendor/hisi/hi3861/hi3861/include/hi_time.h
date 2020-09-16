/**
* @file hi_time.h
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
* Description: time APIs.CNcomment:时间接口描述CNend
* @li System time of the hi_get_tick, hi_get_tick64, hi_get_milli_seconds, and hi_get_seconds operations. The system
*     time is calculated starting from kernel startup and cannot be modified through APIs.
CNcomment:hi_get_tick, hi_get_tick64,hi_get_milli_seconds, hi_get_seconds操作的系统时间，
系统时间从kernel启动开始计时，不可以通过接口进行修改。CNend
* @li The hi_get_real_time and hi_set_real_time APIs are about real-time operations. The real time is calculated
*     starting from kernel startup and can be modified by hi_set_real_time.CNcomment:hi_get_real_time，
hi_set_real_time操作的是实时时间，实时时间从kernel启动开始计时，可以通过hi_set_real_time进行修改。CNend   \n
* Author: Hisilicon   \n
* Create: 2019-05-29
*/

/**
 * @defgroup iot_time System Clock
 * @ingroup osa
 */
#ifndef __HI_TIME_H__
#define __HI_TIME_H__
#include <hi_types_base.h>

/**
* @ingroup  iot_time
* @brief  Delay, in microseconds.CNcomment:延时，微秒级。CNend
*
* @par 描述:
*           Delay operation implemented by software based on the system clock, blocking the CPU.
CNcomment:延时操作，阻塞CPU。CNend
*
* @attention This API cannot be used for a long time in an interrupt.CNcomment:不允许中断中使用。CNend
*
* @param  us                [IN] type #hi_u32，delay period (unit: microsecond).
CNcomment:延时时间（单位：μs）。CNend
*
* @retval  None
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
* @see  None
*/
hi_void hi_udelay(hi_u32 us);

/**
* @ingroup  iot_time
* @brief  Obtains the tick value of the system (32-bit).CNcomment:获取系统tick值（32bit）。CNend
*
* @par 描述:
*           Obtains the tick value of the system (32-bit).CNcomment:获取系统tick值（32bit）。CNend
*
* @attention None
* @param None
*
* @retval #hi_u32 Tick value of the system.CNcomment:系统tick值。CNend
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_u32 hi_get_tick(hi_void);

/**
* @ingroup  iot_time
* @brief  Obtains the tick value of the system (64-bit).CNcomment:获取系统tick值（64bit）。CNend
*
* @par 描述:
*           Obtains the tick value of the system (64-bit).CNcomment:获取系统tick值（64bit）。CNend
*
* @attention The hi_mdm_time.h file must be included where the API is called. Otherwise, the API is considered not
*            declared, and the tick value is returned as an int type, resulting in a truncation error.
CNcomment:该接口调用处必须包含头文件hi_time.h，否则按照未声明接口处理，会将tick值当做int类型返回，产生截断错误。CNend
* @param None
*
* @retval  #hi_u64 Tick value of the system.CNcomment:系统tick值。CNend
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_u64 hi_get_tick64(hi_void);

/**
* @ingroup  iot_time
* @brief  Obtains the system time (unit: ms).CNcomment:获取系统时间（单位：ms）。CNend
*
* @par 描述:
*           Obtains the system time (unit: ms).CNcomment:获取系统时间（单位：ms）。CNend
*
* @attention None
* @param None
*
* @retval #hi_u32 System time.CNcomment:系统时间。CNend
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_u32 hi_get_milli_seconds(hi_void);

/**
* @ingroup  iot_time
* @brief  Obtains the system time (unit: s).CNcomment:获取系统时间（单位：s）。CNend
*
* @par 描述:
*           Obtains the system time (unit: s).CNcomment:获取系统时间（单位：s）。CNend
*
* @attention None
* @param None
*
* @retval #hi_u32 System time.CNcomment:系统时间。CNend
* @retval #HI_ERR_FAILURE failed to be obtained. CNcomment:获取时间失败。CNend
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_u32 hi_get_seconds(hi_void);

/**
* @ingroup  iot_time
* @brief  Obtains the system time (unit: us).CNcomment:获取系统时间（单位：us）。CNend
*
* @par 描述:
*           Obtains the system time (unit: us).CNcomment:获取系统时间（单位：us）。CNend
*
* @attention None
* @param None
*
* @retval #hi_u64 System time.CNcomment:系统时间。CNend
* @retval #HI_ERR_FAILURE failed to be obtained. CNcomment:获取时间失败。CNend
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_u64 hi_get_us(hi_void);

/**
* @ingroup  iot_time
* @brief  Obtains the real time of the system (unit: s).CNcomment:获取系统实时时间（单位：s）。CNend
*
* @par 描述:
*           Obtains the real time of the system (unit: s).CNcomment:获取系统实时时间（单位：s）。CNend
*
* @attention None
* @param None
*
* @retval #hi_u32 Real time of the system.CNcomment: 系统实时时间。CNend
* @retval #HI_ERR_FAILURE failed to be obtained. CNcomment:获取时间失败。CNend
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_u32 hi_get_real_time(hi_void);

/**
* @ingroup  iot_time
* @brief  Sets the real time of the system.CNcomment:设置系统实时时间。CNend
*
* @par 描述:
*           Sets the real time of the system.CNcomment:设置系统实时时间。CNend
*
* @attention None
* @param  seconds            [IN] type #hi_u32，set the real time of the system to this value.
CNcomment:将系统实时时间设置为该值。CNend
*
* @retval #HI_ERR_SUCCESS    Success.
* @retval #HI_ERR_FAILURE    Failure.
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_u32 hi_set_real_time(hi_u32 seconds);

extern hi_void_callback g_tick_callback;

/**
* @ingroup  iot_time
* @brief Regiseter system tick callback.CNcomment:注册tick 中断响应回调函数。CNend
*
* @par 描述:
*          Regiseter system tick callback, if callback is NULL, means cancel registration.
CNcomment:注册tick中断回调函数，如果回调函数为空，表示取消注册。CNend
*
* @attention
*           @li cb should not excute in FLASH, must excute in RAM or ROM. u can specify BSP_RAM_TEXT_SECTION before func
to set func excute in RAM.
CNcomment:回调函数不能在FLASH中运行，必须放置在RAM或ROM中，可以通过在
函数名前添加BSP_RAM_TEXT_SECTION 冠头指定函数在RAM中运行。CNend
* @param  cb      [IN] type #hi_void_callback, callback in tick interrupt.CNcomment:tick中断的回调函数。CNend
*
* @retval #None
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_void hi_tick_register_callback(hi_void_callback cb);

/**
* @ingroup  iot_time
* @brief Convert milliseconds to ticks CNcomment:将毫秒转换为ticks。CNend
*
* @par 描述:
*          Convert milliseconds to ticks,ms is greater than 10ms, ticks = ms / 10,
*          otherwise see parameter include0 description.
CNcomment: 将milliseconds换算为ticks,ms大于10ms,ticks=ms/10。CNend
*
* @attention None
* @param  ms            [IN] type #hi_u32, milliseconds.
* @param  include0      [IN] type #hi_bool, ms is 0, if include0 is HI_TRUE, return 0 tick,otherwise return 1 tick.
CNcomment:入参ms为0时，如果include0为HI_TRUE，换算结果为0；否则换算结果为1。CNend
*
* @retval #hi_u32 ticks time.CNcomment:ticks时间数 CNend
* @par 依赖:
*            @li hi_time.h：Describes system time APIs.CNcomment:文件包含系统时间相关接口。CNend
*/
hi_u32 hi_ms2systick (hi_u32 ms, hi_bool include0);

#endif
