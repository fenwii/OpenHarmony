/**
 * @file hi_clock.h
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
 * @defgroup iot_clock Crystal Clock
 * @ingroup drivers
 */

#ifndef __HI_CLOCK_H__
#define __HI_CLOCK_H__
#include <hi_types_base.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HI_XTAL_24MHZ_VAL   24000000
#define HI_XTAL_40MHZ_VAL   40000000

/**
 * @ingroup iot_clock Xtal Clock Configuration
 *
 * Crystal clock frequency.CNcomment:晶体时钟频率。CNend
 */
typedef enum {
    HI_XTAL_CLOCK_24M,   /**< 24M crystal clock frequency.CNcomment:24M晶体时钟CNend */
    HI_XTAL_CLOCK_40M,   /**< 40M crystal clock frequency.CNcomment:40M晶体时钟CNend */
    HI_XTAL_CLOCK_MAX    /**< MAX value, invalid.CNcomment:最大值，不可使用CNend */
}hi_xtal_clock;

/**
* @ingroup  iot_clock
* @brief Obtains the crystal clock frequency.CNcomment:获取晶体时钟频率。CNend
*
* @par 描述:
*           Obtains the crystal clock frequency.CNcomment:获取晶体时钟频率。CNend
*
* @attention None
* @param     None
*
* @retval #HI_XTAL_CLOCK_24M  24M crystal clock frequency.CNcomment:24M晶体时钟。CNend
* @retval #HI_XTAL_CLOCK_40M  40M crystal clock frequency.CNcomment:40M晶体时钟。CNend
* @retval #HI_XTAL_CLOCK_MAX  MAX value, invalid.CNcomment:最大值，不可使用。CNend
* @par 依赖:
*            @li hi_clock.h：Describes hardware clock APIS.
CNcomment:文件用于描述硬件时钟相关接口。CNend
* @see None
*/
HI_EXTERN hi_xtal_clock hi_get_xtal_clock(hi_void);

/**
* @ingroup  iot_clock
* @brief Configure the frequency divider of the 24M/40M crystal oscillator to generate the 32K clock.
CNcomment:配置24M/40M晶体分频值，产生32K时钟。CNend
*
* @par 描述:
*        Configure the frequency divider of the 24M/40M crystal oscillator to generate the 32K clock.
CNcomment:配置24M/40M晶体分频值，产生32K时钟。CNend
*
* @attention Impact Scope:systick、rtc.CNcomment:影响范围:systick、rtc。CNend
* @param     None
*
* @retval None
* @par 依赖:
*            @li hi_clock.h：Describes hardware clock APIS.
CNcomment:文件用于描述硬件时钟相关接口。CNend
* @see None
*/
HI_EXTERN hi_void hi_cfg_xtal_clk_div(hi_void);

#ifdef __cplusplus
}
#endif

#endif
