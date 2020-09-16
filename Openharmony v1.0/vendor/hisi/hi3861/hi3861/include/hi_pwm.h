/**
 * @file hi_pwm.h
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
 * Description: PWM driver interfaces.
 */

/** @defgroup iot_pwm PWM
 *  @ingroup drivers
 */
#ifndef __HI_PWM_H__
#define __HI_PWM_H__

#include <hi_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup iot_pwm
 *
 * Enumerates the PWM clock sources.CNcomment:PWM时钟源枚举。CNend
 */
typedef enum {
    PWM_CLK_160M, /**< 160M APB clock.CNcomment:160M 工作时钟 CNend */
    PWM_CLK_XTAL, /**< 24M/40M crystal clock.CNcomment:24M或40M 晶体时钟 CNend */
    PWM_CLK_MAX   /**< Maximum value, which cannot be used.CNcomment:最大值，不可使用CNend */
} hi_pwm_clk_source;

/**
 * @ingroup iot_pwm
 *
 * Enumerates the PWM ports.CNcomment:PWM端口枚举。CNend
 */
typedef enum {
    HI_PWM_PORT_PWM0 = 0, /**< PWM port0. Register base address: 0x40040000, multiplexed with GPIOX.
                             CNcomment:PWM0端口。寄存器基址:0x40040000，复用GPIOX。CNend */
    HI_PWM_PORT_PWM1 = 1, /**< PWM port1. Register base address: 0x40040100, multiplexed with GPIOX.
                             CNcomment:PWM1端口。寄存器基址:0x40040100，复用GPIOX。CNend */
    HI_PWM_PORT_PWM2 = 2, /**< PWM port2. Register base address: 0x40040200, multiplexed with GPIOX.
                             CNcomment:PWM2端口。寄存器基址:0x40040200，复用GPIOX。CNend */
    HI_PWM_PORT_PWM3 = 3, /**< PWM port3. Register base address: 0x40040300, multiplexed with GPIOX.
                             CNcomment:PWM3端口。寄存器基址:0x40040300，复用GPIOX。CNend */
    HI_PWM_PORT_PWM4 = 4, /**< PWM port4. Register base address: 0x40040400, multiplexed with GPIOX.
                             CNcomment:PWM4端口。寄存器基址:0x40040400，复用GPIOX。CNend */
    HI_PWM_PORT_PWM5 = 5, /**< PWM port5. Register base address: 0x40040500, multiplexed with GPIOX.
                             CNcomment:PWM5端口。寄存器基址:0x40040500，复用GPIOX。CNend */
    HI_PWM_PORT_MAX   /**< Maximum value, which cannot be used.CNcomment:最大值，不可使用CNend */
} hi_pwm_port;

/**
* @ingroup iot_pwm
* @brief  Initializes the PWM module.CNcomment:PWM初始化。CNend
*
* @par   描述:
*            Initializes the PWM module.CNcomment:PWM初始化。CNend
* @attention
*        @li Before using the PWM function, ensure that the GPIO multiplexing relationship has been configured.
CNcomment:使用PWM功能前需要确认已配置GPIO复用关系。CNend
*        @li For details, see Hi3861 V100 API Development Guide.
CNcomment:具体配置方法请参见<Hi3861V100 API开发指南>Demo介绍小节相关说明。CNend
*        @li For details about the multiplexed GPIO, see the Hi3861 V100 Data Sheet.
CNcomment:具体复用的GPIO请参见<Hi3861 芯片 硬件用户指南>。CNend
*        @li Before using the PWM function, initialize the PWM.CNcomment:使用PWM功能前需要先初始化。CNend
*
* @param  port [IN]  type #hi_pwm_port PWM port number.CNcomment:PWM端口号。CNend
*
* @retval #HI_ERR_SUCCESS Success.
* @retval #Other          Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_pwm.h: Describes the APIs of the PWM module.CNcomment:文件用于描述PWM对外接口。CNend
* @see hi_pwm_deinit | hi_pwm_start | hi_pwm_stop。
*/
hi_u32 hi_pwm_init(hi_pwm_port port);

/**
* @ingroup iot_pwm
* @brief  Deinitializes the PWM module.CNcomment:PWM去初始化。CNend
*
* @par   描述:
*            Deinitializes the PWM module.CNcomment:PWM去初始化。CNend
*
* @attention Deinitialize the PWM module when the function iss not used.
CNcomment:不使用PWM功能时去初始化。CNend
*
* @param  port [IN]  type #hi_pwm_port PWM port number.CNcomment:PWM端口号。CNend
*
* @retval #HI_ERR_SUCCESS Success.
* @retval #Other          Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_pwm.h: Describes the APIs of the PWM module.CNcomment:文件用于描述PWM对外接口。CNend
* @see hi_pwm_init。
*/
hi_u32 hi_pwm_deinit(hi_pwm_port port);

/**
* @ingroup iot_pwm
* @brief  Sets the clock type of the PWM module.CNcomment:设置PWM模块时钟类型。CNend
*
* @par   描述:
*            This function is used to set the clock type of the PWM module.
CNcomment:该函数用于设置PWM模块时钟类型。CNend
*
* @attention This setting takes effect for all PWM modules. The 160 MHz clock is used by default.
CNcomment:该设置对所有PWM模块均生效。默认为160M时钟。CNend
*
* @param  clk_type [IN] type #hi_pwm_clk_source Clock type. CNcomment:时钟类型。CNend
*
* @retval #HI_ERR_SUCCESS Success.
* @retval #Other          Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_pwm.h: Describes the APIs of the PWM module.CNcomment:文件用于描述PWM对外接口。CNend
* @see None
*/
hi_u32 hi_pwm_set_clock(hi_pwm_clk_source clk_type);

/**
* @ingroup iot_pwm
* @brief  Outputs the PWM signal according to the configured parameter.
*         PWM signal duty cycle = duty/freq Frequency = Clock source frequency/freq.
CNcomment:按配置的参数输出PWM信号。PWM信号占空比=duty/freq。频率=时钟源频率/freq。CNend
*
* @par   描述:
*            Starts the PWM signal output.CNcomment:启动PWM信号输出。CNend
*
* @attention This API cannot be called in an interrupt.CNcomment:不支持在中断中调用。CNend
*
* @param  port [IN] type #hi_pwm_port PWM port number.CNcomment:PWM端口号。CNend
* @param  duty [IN] type #hi_u16 PWM duty cycle count. Value range: [1, 65535]. The default value is 750.
CNcomment:PWM占空比计数值。取值范围为:[1, 65535]。默认值为750。CNend
* @param  freq [IN] type #hi_u16 Frequency division multiple. Value range: [1, 65535]. The default value is 1500.
CNcomment:分频倍数。取值范围为:[1, 65535]。默认值为1500。CNend
*
* @retval #HI_ERR_SUCCESS Success.
* @retval #Other          Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_pwm.h: Describes the APIs of the PWM module.CNcomment:文件用于描述PWM对外接口。CNend
* @see  hi_pwm_init | hi_pwm_stop。
*/
hi_u32 hi_pwm_start(hi_pwm_port port, hi_u16 duty, hi_u16 freq);

/**
* @ingroup iot_pwm
* @brief  Stops the PWM signal output.CNcomment:停止PWM信号输出。CNend
*
* @par   描述:
*          Stops the PWM signal output.CNcomment: 停止PWM信号输出。CNend
*
* @attention This API cannot be called in an interrupt.CNcomment:不支持在中断中调用。CNend
*
* @param  port [IN] type #hi_pwm_port PWM port number.CNcomment:PWM端口号。CNend
*
* @retval #HI_ERR_SUCCESS Success.
* @retval #Other          Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_pwm.h: Describes the APIs of the PWM module.CNcomment:文件用于描述PWM对外接口。CNend
* @see  hi_pwm_init | hi_pwm_start。
*/
hi_u32 hi_pwm_stop(hi_pwm_port port);

#ifdef __cplusplus
}
#endif
#endif
