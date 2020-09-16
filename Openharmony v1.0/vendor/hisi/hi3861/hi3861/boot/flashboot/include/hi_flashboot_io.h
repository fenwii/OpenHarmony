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

#ifndef __FLASHBOOT_IO_H__
#define __FLASHBOOT_IO_H__
#include<hi_boot_rom.h>

/**
* @ingroup iot_io
*
* I/O drive capability.CNcomment:IO驱动能力。CNend
* Note: The HI_IO_NAME_GPIO_0~HI_IO_NAME_GPIO_11 and HI_IO_NAME_GPIO_13~HI_IO_NAME_GPIO_14 driver capabilities are
*       optional.The value range is HI_IO_DRIVER_STRENGTH_0~HI_IO_DRIVER_STRENGTH_3, and the other I/O ranges are
*       HI_IO_DRIVER_STRENGTH_0~HI_IO_DRIVER_STRENGTH_7.CNcomment:注意:HI_IO_NAME_GPIO_0~HI_IO_NAME_GPIO_11、
*       HI_IO_NAME_GPIO_13~HI_IO_NAME_GPIO_14驱动能力可选范围是HI_IO_DRIVER_STRENGTH_0~HI_IO_DRIVER_STRENGTH_3，
*       其余IO范围是HI_IO_DRIVER_STRENGTH_0~HI_IO_DRIVER_STRENGTH_7。CNend
*/
typedef enum {
    HI_IO_DRIVER_STRENGTH_0 = 0,      /**< Drive strength level 0 (highest).
                                         CNcomment:驱动能力0级，驱动能力最高CNend */
    HI_IO_DRIVER_STRENGTH_1,          /**< Drive strength level 1.CNcomment:驱动能力1级CNend */
    HI_IO_DRIVER_STRENGTH_2,          /**< Drive strength level 2.CNcomment:驱动能力2级CNend */
    HI_IO_DRIVER_STRENGTH_3,          /**< Drive strength level 3.CNcomment:驱动能力3级CNend */
    HI_IO_DRIVER_STRENGTH_4,          /**< Drive strength level 4.CNcomment:驱动能力4级CNend */
    HI_IO_DRIVER_STRENGTH_5,          /**< Drive strength level 5.CNcomment:驱动能力5级CNend */
    HI_IO_DRIVER_STRENGTH_6,          /**< Drive strength level 6.CNcomment:驱动能力6级CNend */
    HI_IO_DRIVER_STRENGTH_7,          /**< Drive strength level 7 (lowest).
                                         CNcomment:驱动能力7级，驱动能力最低CNend */
    HI_IO_DRIVER_STRENGTH_MAX,
} hi_io_driver_strength;

/**
* @ingroup  iot_io
* @brief Obtains the GPIO pull-up status.CNcomment:获取某个GPIO上下拉状态。CNend
*
* @par 描述:
*           Obtains the GPIO pull-up status.CNcomment:获取某个GPIO上下拉状态。CNend
*
* @attention None
* @param  id    [IN]  type #hi_io_name，I/O index.CNcomment:硬件管脚。CNend
* @param  val   [OUT] type #hi_io_pull*，pull-up status.CNcomment:获取到的上下拉状态。CNend.
*
* @retval 0       Success
* @retval #HI_ERR_GPIO_INVALID_PARAMETER     Failure. Input invalid.
* @par 依赖:
*           @li hi_io.h：Describes I/O APIs.CNcomment:文件用于描述IO相关接口。CNend
* @see  hi_io_set_pull。
*/
hi_u32 hi_io_get_pull(hi_io_name id, hi_io_pull *val);

/**
* @ingroup  iot_io
* @brief Obtains the I/O multiplexing.CNcomment:获取某个IO复用功能。CNend
*
* @par 描述:
*           Obtains the I/O multiplexing.CNcomment:获取某个IO复用功能。CNend
*
* @attention None
* @param  id    [IN]  type #hi_io_name，I/O index.CNcomment:硬件管脚。CNend
* @param  val   [OUT] type #hi_u8*，I/O multiplexing.CNcomment:IO复用功能。CNend
*
* @retval 0       Success
* @retval #HI_ERR_GPIO_INVALID_PARAMETER     Failure. Input invalid.
* @par 依赖:
*           @li hi_io.h：Describes I/O APIs.CNcomment:文件用于描述IO相关接口。CNend
* @see  hi_io_set_func。
*/
hi_u32 hi_io_get_func(hi_io_name id, hi_u8 *val);

/**
* @ingroup  iot_io
* @brief Sets the I/O drive strength.CNcomment:设置某个IO驱动能力。CNend
*
* @par 描述:
*          The I/O drive strength is closely related to hardware design. For details, see SoC data sheet.
CNcomment:设置某个IO驱动能力，与硬件设计强相关，详细配置参考芯片手册。CNend
*
* @attention None
* @param  id    [IN] type #hi_io_name，I/O index.CNcomment:硬件管脚。CNend
* @param  level [IN] type #hi_io_driver_strength，I/O drive strength level.CNcomment:IO驱动能力级别。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_io.h：Describes I/O APIs.CNcomment:文件用于描述IO相关接口。CNend
* @see  None
*/
hi_u32 hi_io_set_driver_strength(hi_io_name id, hi_io_driver_strength val);

/**
* @ingroup  iot_io
* @brief Obtains the I/O drive strength.CNcomment:获取某个IO驱动能力。CNend
*
* @par 描述:
*          Obtains the I/O drive strength.CNcomment:获取某个IO驱动能力。CNend
*
* @attention None
* @param  id    [IN]  type #hi_io_name，I/O index.CNcomment:硬件管脚。CNend
* @param  val   [OUT] type #hi_io_driver_strength*，I/O drive strength level.CNcomment:IO驱动能力级别。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_io.h：Describes I/O APIs.CNcomment:文件用于描述IO相关接口。CNend
* @see  None
*/
hi_u32 hi_io_get_driver_strength(hi_io_name id, hi_io_driver_strength *val);

/**
* @ingroup  iot_io
* @brief Set the I/O input enable status.CNcomment:设置某个IO输入使能的状态。CNend
*
* @par 描述:
*          Set the I/O input enable status.CNcomment:设置某个IO输入使能的状态。CNend
*
* @attention If the input enable status of an IO is set to FALSE in the input state, the CPU can't read the IO changes.
CNcomment:如果某个IO的输入使能设置为FALSE，CPU将读取不到该IO的变化。CNend
* @param  id      [IN] type #hi_io_name，I/O index.CNcomment:硬件管脚。CNend
* @param  state   [IN] type #hi_bool，IO input enable state.CNcomment:要设置的输入使能状态。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_io.h：Describes I/O APIs.CNcomment:文件用于描述IO相关接口。CNend
* @see  None
*/
hi_u32 hi_io_set_input_enable(hi_io_name id, hi_bool state);

/**
* @ingroup  iot_io
* @brief Get the I/O input enable status.CNcomment:获取某个IO输入使能的状态。CNend
*
* @par 描述:
*          Get the I/O input enable status.CNcomment:获取某个IO输入使能的状态。CNend
*
* @attention None
* @param  id      [IN]  type #hi_io_name，I/O index.CNcomment:硬件管脚。CNend
* @param  state   [OUT] type #hi_bool *，IO input enable state.CNcomment:IO的输入使能状态。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_io.h：Describes I/O APIs.CNcomment:文件用于描述IO相关接口。CNend
* @see  None
*/
hi_u32 hi_io_get_input_enable(hi_io_name id, hi_bool *state);

#endif
