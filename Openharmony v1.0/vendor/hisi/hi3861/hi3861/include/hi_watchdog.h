/**
 * @file hi_watchdog.h
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
 * @defgroup iot_watchdog Watchdog
 * @ingroup drivers
 */
#ifndef __HI_WATCHDOG_H__
#define __HI_WATCHDOG_H__

#include <hi_types_base.h>

#define HI_WDG_MIN_TIMEOUT 6500

/**
* @ingroup  iot_watchdog
* @brief Enables the watchdog.CNcomment:使能看门狗。CNend
*
* @par 描述:
*          Enables the watchdog.CNcomment:使能看门狗。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_watchdog.h：describes the watchdog APIs.CNcomment:文件用于描述看门狗相关接口。CNend
* @see None
*/
hi_void hi_watchdog_enable(hi_void);

/**
* @ingroup  iot_watchdog
* @brief Feeds the watchdog.CNcomment:喂狗。CNend
*
* @par 描述: Feeds the watchdog.CNcomment:喂狗。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_watchdog.h：describes the watchdog APIs.CNcomment:文件用于描述看门狗相关接口。CNend
* @see None
*/
hi_void hi_watchdog_feed(hi_void);

/**
* @ingroup  iot_watchdog
* @brief Disables the watchdog.CNcomment:关闭看门狗。CNend
*
* @par 描述:
*           @li Disable the clock enable control of the watchdog.CNcomment:禁止WatchDog时钟使能控制位。CNend
*           @li Mask the watchdog reset function.CNcomment:屏蔽WatchDog复位功能。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_watchdog.h：describes the watchdog APIs.CNcomment:文件用于描述看门狗相关接口。CNend
* @see None
*/
hi_void hi_watchdog_disable(hi_void);

/**
* @ingroup  iot_watchdog
* @brief Set watchod timeout(ms).CNcomment:设置看门狗超时时间，单位ms。CNend
*
* @par 描述:
*           @li Set watchod timeout(ms).CNcomment:设置看门狗超时时间，单位ms。CNend
*
* @attention
* timeout should not smaller than 6500ms.CNcomment:看门狗超时时间不得小于6500ms。
* system will restart count after set timeout.CNcomment:设置超时时间后，系统会重新开始计数。
* @param  timeout_ms    [IN] type #hi_u32，timeout(ms). CNcomment:超时时间(单位:ms)。CNend
*
* @retval #HI_ERR_SUCCESS   Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_watchdog.h：describes the watchdog APIs.CNcomment:文件用于描述看门狗相关接口。CNend
* @see None
*/
hi_u32 hi_watchdog_set_timeout(hi_u32 timeout_ms);

#endif
