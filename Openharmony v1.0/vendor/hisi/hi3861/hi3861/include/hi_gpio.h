/**
 * @file hi_gpio.h
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
* @defgroup iot_gpio GPIO
* @ingroup drivers
*/
#ifndef __HI_GPIO_H__
#define __HI_GPIO_H__


#include <hi_types_base.h>

/**
* @ingroup iot_gpio
*
* GPIO ID.
*/
typedef enum {
    HI_GPIO_IDX_0,     /**< GPIO0*/
    HI_GPIO_IDX_1,     /**< GPIO1*/
    HI_GPIO_IDX_2,     /**< GPIO2*/
    HI_GPIO_IDX_3,     /**< GPIO3*/
    HI_GPIO_IDX_4,     /**< GPIO4*/
    HI_GPIO_IDX_5,     /**< GPIO5*/
    HI_GPIO_IDX_6,     /**< GPIO6*/
    HI_GPIO_IDX_7,     /**< GPIO7*/
    HI_GPIO_IDX_8,     /**< GPIO8*/
    HI_GPIO_IDX_9,     /**< GPIO9*/
    HI_GPIO_IDX_10,    /**< GPIO10*/
    HI_GPIO_IDX_11,    /**< GPIO11*/
    HI_GPIO_IDX_12,    /**< GPIO12*/
    HI_GPIO_IDX_13,    /**< GPIO13*/
    HI_GPIO_IDX_14,    /**< GPIO14*/
    HI_GPIO_IDX_MAX,   /**< Maximum value, which cannot be used.CNcomment:最大值，不可输入使用CNend*/
} hi_gpio_idx;


/**
* @ingroup iot_gpio
*
* I/O level. CNcomment:GPIO电平状态。CNend
*/
typedef enum {
    HI_GPIO_VALUE0 = 0,      /**< Low level.CNcomment:低电平CNend*/
    HI_GPIO_VALUE1           /**< High level.CNcomment:高电平CNend*/
} hi_gpio_value;

/**
* @ingroup iot_gpio
*
* I/O direction. CNcomment:GPIO方向。CNend
*/
typedef enum {
    HI_GPIO_DIR_IN = 0,       /**< Input.CNcomment:输入方向CNend*/
    HI_GPIO_DIR_OUT           /**< Output.CNcomment:输出方向CNend*/
} hi_gpio_dir;

/**
* @ingroup iot_gpio
*
* I/O interrupt trigger mode. This bit is used with HI_GPIO_INT_POLARITY.
CNcomment:GPIO中断触发方式，与hi_gpio_int_polarity配合使用。CNend
*/
typedef enum {
    HI_INT_TYPE_LEVEL = 0, /**< The interrupt is triggered in level-sensitive mode. CNcomment:电平触发中断CNend */
    HI_INT_TYPE_EDGE   /**< Interrupt triggered at the rising edge or falling edge.CNcomment:边沿触发中断CNend */
} hi_gpio_int_type;

/**
* @ingroup iot_gpio
*
* I/O interrupt polarity. This pin is used with HI_GPIO_INT.
CNcomment:IO中断极性，与hi_gpio_int_type配合使用。CNend
*/
typedef enum {
    HI_GPIO_EDGE_FALL_LEVEL_LOW = 0,  /**< Interrupt triggered at low level or falling edge.
                                         CNcomment:低电平或下降沿触发中断CNend */
    HI_GPIO_EDGE_RISE_LEVEL_HIGH      /**< Interrupt triggered at high level or rising edge.
                                         CNcomment:高电平或上升沿触发中断CNend */
} hi_gpio_int_polarity;


/**
* @ingroup  iot_gpio
* @brief  Callback function when GPIO interruption happens.CNcomment:GPIO中断回调函数。CNend
*
* @par 描述:
*           Callback function when GPIO interruption happens.CNcomment:GPIO中断回调函数。CNend
*
* @attention None
*
* @param  arg     [IN] type #hi_void *，arg of interrupt callback function. CNcomment:中断回调函数入参。CNend
*
* @retval None
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  None
*/
typedef hi_void (*gpio_isr_callback) (hi_void *arg);

/**
* @ingroup  iot_gpio
* @brief  Initializes GPIO module.CNcomment:GPIO模块初始化。CNend
*
* @par 描述:
*           Initializes GPIO module.CNcomment:GPIO模块初始化。CNend
*
* @attention
* @li This API needs to be invoked during initialization to enable the GPIO interrupt so that the I/O interrupt
*     can be responded.CNcomment:需要在初始化阶段调用该接口使能GPIO中断，使得IO中断可以得到响应。CNend
* @li This interface cannot be invoked repeatedly. It can be invoked only once in the initialization phase.
CNcomment:该接口不支持重复调用，只能在初始化阶段调用一次。CNend
*
* @param  None
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  None
*/
hi_u32 hi_gpio_init(hi_void);

/**
* @ingroup  iot_gpio
* @brief  Deinitializes GPIO module. CNcomment:GPIO模块去初始化。CNend
*
* @par 描述:
*           Deinitializes GPIO module. CNcomment:GPIO模块去初始化。CNend
*
* @attention
* @li This interface is used to disable the GPIO interrupt. After the GPIO interrupt is called, the GPIO interrupt
*     cannot be responded.CNcomment:该接口功能为去使能GPIO中断，调用后GPIO中断将得不到响应。CNend
*
* @param  None
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  None
*/
hi_u32 hi_gpio_deinit(hi_void);

/**
* @ingroup  iot_gpio
* @brief  Sets the direction of a single I/O pin.CNcomment:设置某个GPIO管脚方向。CNend
*
* @par 描述:
*           Sets the direction of a single I/O pin.CNcomment:设置某个GPIO管脚方向。CNend
*
* @attention None
* @param  id [IN]    type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
* @param  dir   [IN] type #hi_gpio_dir，I/O direction.CNcomment:GPIO方向。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  hi_gpio_get_dir
*/
hi_u32 hi_gpio_set_dir(hi_gpio_idx id, hi_gpio_dir dir);

/**
* @ingroup  iot_gpio
* @brief  Gets the direction of a single I/O pin.CNcomment:获取某个GPIO管脚方向。CNend
*
* @par 描述:
*           Gets the direction of a single I/O pin.CNcomment:获取某个GPIO管脚方向。CNend
*
* @attention None
* @param  id    [IN]  type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
* @param  dir   [OUT] type #hi_gpio_dir*，I/O direction.CNcomment:GPIO方向。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  hi_gpio_set_dir
*/
hi_u32 hi_gpio_get_dir(hi_gpio_idx id, hi_gpio_dir *dir);

/**
* @ingroup  iot_gpio
* @brief  Sets the output level of a single I/O pin.CNcomment:设置单个GPIO管脚输出电平状态。CNend
*
* @par 描述:
*           Sets the output level of a single I/O pin.CNcomment:设置单个GPIO管脚输出电平状态。CNend
*
* @attention None
*
* @param  id [IN]    type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
* @param  val [IN] type #hi_gpio_value，output value. CNcomment:输出值。CNend
*                 @li 0：low level.CNcomment:低电平。CNend
*                 @li 1：high level.CNcomment:高电平。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  hi_gpio_get_input_val。
*/
hi_u32 hi_gpio_set_ouput_val(hi_gpio_idx id, hi_gpio_value val);

/**
* @ingroup  iot_gpio
* @brief  Obtains the input level of a single I/O pin.CNcomment:获取某个IO管脚输出电平状态。CNend
*
* @par 描述:
*           Obtains the input level of a single I/O pin.CNcomment:获取某个IO管脚输出电平状态。CNend
*
* @attention None
* @param  id  [IN]  type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
* @param  val [OUT] type #hi_gpio_value*，Output value.CNcomment:输出值。CNend
*                 @li 0：low level.CNcomment:低电平。CNend
*                 @li 1：high level.CNcomment:高电平。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  hi_gpio_set_ouput_val。
*/
hi_u32 hi_gpio_get_output_val(hi_gpio_idx id, hi_gpio_value* val);

/**
* @ingroup  iot_gpio
* @brief  Obtains the input level of a single I/O pin.CNcomment:获取某个IO管脚输入电平状态。CNend
*
* @par 描述:
*           Obtains the input level of a single I/O pin.CNcomment:获取某个IO管脚输入电平状态。CNend
*
* @attention None
* @param  id  [IN]  type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
* @param  val [OUT] type #hi_gpio_value*，Output value.CNcomment:输出值。CNend
*                 @li 0：low level.CNcomment:低电平。CNend
*                 @li 1：high level.CNcomment:高电平。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  None
*/
hi_u32 hi_gpio_get_input_val(hi_gpio_idx id, hi_gpio_value *val);

/**
* @ingroup  iot_gpio
* @brief  Enable GPIO interruption.CNcomment:使能某个GPIO的中断功能。CNend
*
* @par 描述:
*           Enable GPIO interruption.CNcomment:使能某个GPIO的中断功能。CNend
*
* @attention None
* @param  id            [IN] type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
* @param  int_type      [IN] type #hi_gpio_int_type，Interruption type.CNcomment:中断类型。CNend
* @param  int_polarity  [IN] type #hi_gpio_int_polarity，Interruption polarity.CNcomment:中断极性。CNend
* @param  func          [IN] type #gpio_isr_callback_func，Callback function of interruption.
CNcomment:中断回调函数。CNend
* @param  arg           [IN] type #hi_void *，arg of interrupt callback function. CNcomment:中断回调函数入参。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  hi_gpio_unregister_isr_function。
*/
hi_u32 hi_gpio_register_isr_function(hi_gpio_idx id, hi_gpio_int_type int_type, hi_gpio_int_polarity int_polarity,
                                     gpio_isr_callback func, hi_void *arg);

/**
* @ingroup  iot_gpio
* @brief  Disable GPIO interruption.CNcomment:去使能某个GPIO的中断功能。CNend
*
* @par 描述:
*           Disable GPIO interruption.CNcomment:去使能某个GPIO的中断功能。CNend
*
* @attention None
* @param  id [IN] type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  hi_gpio_register_isr_function。
*/
hi_u32 hi_gpio_unregister_isr_function(hi_gpio_idx id);

/**
* @ingroup  iot_gpio
* @brief  Mask GPIO interruption.CNcomment:屏蔽某个GPIO的中断功能。CNend
*
* @par 描述:
*           Mask GPIO interruption.CNcomment:屏蔽某个GPIO的中断功能。CNend
*
* @attention If this interface is called before hi_gpio_register_isr_function, the hi_gpio_register_isr_function
*            interface will unmask the GPIO interruption.
*            CNcomment:若此接口在hi_gpio_register_isr_function之前调用，hi_gpio_register_isr_function会将配置
*            修改为不屏蔽GPIO中断。CNend
* @param  id            [IN] type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
* @param  is_mask       [IN] type #hi_bool，Interruption type.CNcomment:中断类型。CNend
*                            @li HI_FALSE：Unmask I/O interruption.CNcomment:不屏蔽GPIO中断。CNend
*                            @li HI_TRUE： Mask I/O interruption.CNcomment:屏蔽GPIO中断。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  None
*/
hi_u32 hi_gpio_set_isr_mask(hi_gpio_idx id, hi_bool is_mask);

/**
* @ingroup  iot_gpio
* @brief  Set GPIO interruption type and polarity.CNcomment:设置某个GPIO的中断触发方式。CNend
*
* @par 描述:
*           Set GPIO interruption type and polarity.CNcomment:设置某个GPIO的中断触发方式。CNend
*
* @attention If this interface is called before hi_gpio_register_isr_function, hi_gpio_register_isr_function
*            will overwrite the configurations.
*            CNcomment:若此接口在hi_gpio_register_isr_function之前调用，hi_gpio_register_isr_function会覆盖
*            本接口的配置。CNend
* @param  id            [IN] type #hi_gpio_idx，I/O index.CNcomment:GPIO索引。CNend
* @param  int_type      [IN] type #hi_gpio_int_type，Interruption type.CNcomment:中断类型。CNend
* @param  int_polarity  [IN] type #hi_gpio_int_polarity，Interruption polarity.CNcomment:中断极性。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_gpio.h：Describes GPIO APIs.CNcomment:文件用于描述GPIO相关接口。CNend
* @see  None
*/
hi_u32 hi_gpio_set_isr_mode(hi_gpio_idx id, hi_gpio_int_type int_type, hi_gpio_int_polarity int_polarity);

#endif
