/**
 * @file hi_i2s.h
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
 * @defgroup iot_i2s I2S
 * @ingroup drivers
 */
#ifndef __HI_I2S_H__
#define __HI_I2S_H__

/**
* @ingroup iot_i2s
*
* sample rate.
*/
typedef enum {
    HI_I2S_SAMPLE_RATE_8K = 8,
    HI_I2S_SAMPLE_RATE_16K = 16,
    HI_I2S_SAMPLE_RATE_32K = 32,
    HI_I2S_SAMPLE_RATE_48K = 48,
} hi_i2s_sample_rate;

/**
* @ingroup iot_i2s
*
* resolution.
*/
typedef enum {
    HI_I2S_RESOLUTION_16BIT = 16,
    HI_I2S_RESOLUTION_24BIT = 24,
} hi_i2s_resolution;

/**
* @ingroup iot_i2s
*
* I2S attributes.
*/
typedef struct {
    hi_i2s_sample_rate sample_rate;  /**< i2s sample rate, type hi_i2s_sample_rate.CNcomment:采样率，类型为
                                          hi_i2s_sample_rate。CNend */
    hi_i2s_resolution resolution;   /**< i2s resolution, type hi_i2s_resolution.CNcomment:解析度，类型为
                                          hi_i2s_resolution。CNend */
} hi_i2s_attribute;

/**
* @ingroup  iot_i2s
* @brief  I2S initialization. CNcomment:I2S初始化。CNend
*
* @par 描述:
*           Set I2S with configuration. CNcomment:根据参数配置I2S。CNend
*
* @attention Should init DMA driver before using I2S. CNcomment:使用I2S驱动前，需要初始化DMA驱动。CNend
*
* @param  i2s_attribute   [IN] type #hi_i2s_attribute*，I2S configuration parameter. CNcomment:I2S配置参数。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_i2s.h：Describes I2S APIs.CNcomment:I2S相关接口。CNend
* @see  hi_i2s_deinit。
*/
hi_u32 hi_i2s_init(const hi_i2s_attribute *i2s_attribute);

/**
* @ingroup  iot_i2s
* @brief  Deinitializes I2S.CNcomment:去初始化I2S。CNend
*
* @par 描述:
*           Deinitializes I2S.CNcomment:去初始化I2S。CNend
*
* @attention This API is used together with hi_i2s_init.CNcomment:与hi_i2s_init成对使用。CNend
* @param  None
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_i2s.h：Describes I2S APIs.CNcomment:I2S相关接口。CNend
* @see  hi_i2s_deinit。
*/
hi_u32 hi_i2s_deinit(hi_void);

/**
* @ingroup  iot_i2s
* @brief TX interface for the I2S.CNcomment:I2S发送接口。CNend
*
* @par 描述:
*           TX interface for the I2S.CNcomment:I2S发送接口。CNend
*
* @attention None
*
* @param  wr_data         [OUT] type #hi_u8*，TX data pointer.CNcomment:接收数据指针。CNend
* @param  wr_len          [IN]  type #hi_u32，length of the target data to be send (unit: byte).
CNcomment:发送数据长度（单位：byte）。CNend
* @param  time_out_ms     [IN]  type #hi_u32，wait timeout period.CNcomment:超时时间。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_i2s.h：Describes I2S APIs.CNcomment:I2S相关接口。CNend
* @see  hi_i2s_read。
*/
hi_u32 hi_i2s_write(hi_u8 *wr_data, hi_u32 wr_len, hi_u32 time_out_ms);

/**
* @ingroup  iot_i2s
* @brief Read interface for the I2S.CNcomment:I2S接收接口。CNend
*
* @par 描述:
*           Read interface for the I2S.CNcomment:I2S接收接口。CNend
*
* @attention None
*
* @param  rd_data         [OUT] type #hi_u8*，RX data pointer.CNcomment:接收数据指针。CNend
* @param  rd_len          [IN]  type #hi_u32，length of the target data to be received (unit: byte).
CNcomment:接收数据长度（单位：byte）。CNend
* @param  time_out_ms     [IN]  type #hi_u32，wait timeout period.CNcomment:超时时间。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_i2s.h：Describes I2S APIs.CNcomment:I2S相关接口。CNend
* @see  hi_i2s_write。
*/
hi_u32 hi_i2s_read(hi_u8 *rd_data, hi_u32 rd_len, hi_u32 time_out_ms);

#endif
