/*
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

#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__
#include<hi_boot_rom.h>
#define hi_io_val_set(cond, id, reg_val) \
        if (cond) \
        { \
            (reg_val) |= (hi_u16)(1 << (id)); \
        } \
        else \
        { \
            (reg_val) &= ~(hi_u16)(1 << (id)); \
        }

#define hi_io_dir_get(cond, id, val_addr) \
        if ((cond) & (hi_u16)(1 << (id))) \
        { \
            *(val_addr) = HI_GPIO_DIR_OUT; \
        } \
        else \
        { \
            *(val_addr) = HI_GPIO_DIR_IN; \
        }

#define hi_io_val_get(cond, id, val_addr) \
        if ((cond) & (hi_u16)(1 << (id))) \
        { \
            *(val_addr) = HI_GPIO_VALUE1; \
        } \
        else \
        { \
            *(val_addr) = HI_GPIO_VALUE0; \
        }

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
hi_u32 hi_gpio_set_output_val(hi_gpio_idx id, hi_gpio_value val);

#endif
