/**
* @file hi_adc.h
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
* 描述：Analog-to-digital conversion (ADC) module interface.
* @li Provides 8 ADC channels.
CNcomment:提供8个ADC通道，通道7为参考电压，不能adc转换。CNend
* @li LSADC reading rate is slow, please avoid used in interruption.
CNcomment: LSADC读数速率较慢，请避免在中断使用。CNend
* Author: Hisilicon \n
* Create: 2019-4-3
*/

/**
* @defgroup iot_ls_adc ADC
* @ingroup drivers
*/

#ifndef __HI_ADC_H__
#define __HI_ADC_H__

#include <hi_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup iot_ls_adc
 *
 * channel ID。CNcomment:通道编号.CNend
 */
typedef enum {
    HI_ADC_CHANNEL_0,
    HI_ADC_CHANNEL_1,
    HI_ADC_CHANNEL_2,
    HI_ADC_CHANNEL_3,
    HI_ADC_CHANNEL_4,
    HI_ADC_CHANNEL_5,
    HI_ADC_CHANNEL_6,
    HI_ADC_CHANNEL_7,
    HI_ADC_CHANNEL_BUTT,
} hi_adc_channel_index;

/**
 * @ingroup iot_ls_adc
 *
 * Analog power control. CNcomment:模拟电源控制。CNend
 */
typedef enum {
    HI_ADC_CUR_BAIS_DEFAULT,       /**< 0：Auto control.
                                      CNcomment:自动识别模式 */
    HI_ADC_CUR_BAIS_AUTO,          /**< 1：Auto control.
                                      CNcomment:自动识别模式 */
    HI_ADC_CUR_BAIS_1P8V,          /**< 2：Manual control, AVDD=1.8V.
                                      CNcomment:手动控制，AVDD=1.8V */
    HI_ADC_CUR_BAIS_3P3V,          /**< 3：Manual control, AVDD=3.3V.
                                      CNcomment:手动控制，AVDD=3.3V */
    HI_ADC_CUR_BAIS_BUTT,
} hi_adc_cur_bais;

/**
 * @ingroup iot_ls_adc
 *
 * Average algorithm mode CNcoment:平均算法模式。CNend
 */
typedef enum {
    HI_ADC_EQU_MODEL_1,            /**< 0：The average value is not used.
                                      CNcomment:1次平均，即不进行
                                      平均 CNend */
    HI_ADC_EQU_MODEL_2,            /**< 1：2-time average algorithm mode.
                                      CNcomment:2次平均算法模式 CNend */
    HI_ADC_EQU_MODEL_4,            /**< 2：4-time average algorithm mode.
                                      CNcomment:4次平均算法模式 CNend */
    HI_ADC_EQU_MODEL_8,            /**< 3：8-time average algorithm mode.
                                      CNcomment:8次平均算法模式 CNend */
    HI_ADC_EQU_MODEL_BUTT,
} hi_adc_equ_model_sel;

/**
* @ingroup  iot_ls_adc
* @brief  Read one data in single ADC channel. CNcomment:从一个ADC通道读一个数据。CNend
*
* @par 描述:
*           Read one data in single ADC channel.
CNcomment:从一个ADC通道读一个数据。CNend
*
* @attention None
* @param  channel      [IN] type #hi_adc_channel_index，channel to be read. CNcomment:要读的channel。CNend
* @param  data         [OUT] type #hi_u16 * ，data point to store the data.
CNcomment:读取的ADC数据保存地址。CNend
* @param  equ_model    [IN] type #hi_adc_equ_model_sel ，Average algorithm mode.
CNcomment:平均算法模式。CNend
* @param  cur_bais     [IN] type #hi_adc_cur_bais ，Analog power control.
CNcomment:模拟电源控制。CNend
* @param  delay_cnt      [IN] type #hi_u16 ，Countings from config to start collect，One count is 334ns，[0, 0xFF0].
CNcomment:从配置采样到启动采样的延时时间计数，一次计数是334ns，其值需在0~0xFF0之间。CNend
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other          Failure. See hi_errno.h for details.
* @par 依赖:
*            @li hi_adc.h：Describes ADC APIs.
CNcomment:文件用于描述ADC相关接口。CNend
* @see  hi_adc_read。
*/
hi_u32 hi_adc_read(hi_adc_channel_index channel, hi_u16 *data, hi_adc_equ_model_sel equ_model,
    hi_adc_cur_bais cur_bais, hi_u16 delay_cnt);


/**
* @ingroup  iot_ls_adc
* @brief  Convert adc read data to voltage. CNcomment:将ADC读取到的码字转换为电压。CNend
*
* @par 描述:
*           Convert adc read data to voltage.
CNcomment:将ADC读取到的码字转换为电压。CNend
*
* @attention None
* @param  data      [IN] type #hi_u16，data read by adc. CNcomment:ADC读取到的码字。CNend
* @retval votalge converted by data. CNcomment: 码字转换得到的电压。CNend
* @par 依赖:
*            @li hi_adc.h：Describes ADC APIs.
CNcomment:文件用于描述ADC相关接口。CNend
* @see  hi_adc_read。
*/
hi_float hi_adc_convert_to_voltage(hi_u16 data);


#ifdef __cplusplus
}
#endif
#endif
