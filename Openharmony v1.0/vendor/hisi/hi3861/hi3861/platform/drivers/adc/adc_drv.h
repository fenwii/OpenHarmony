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
 *
 * Description: ADC driver header file.
 */

#ifndef __ADC_DRV_H__
#define __ADC_DRV_H__

#include <hi_adc.h>
#include <hi_mdm_types.h>
#include <hi3861_platform_base.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif  /* __cplusplus */

#ifdef ADC_DEBUG
#define adc_print(fmt...)       \
    do {                        \
        printf(fmt);            \
        printf("\n"); \
    } while (0)
#else
#define adc_print(fmt...)
#endif

#define LS_ADC_CLK_DIV1_REG     CLDO_CTL_CLK_DIV1_REG
#define LS_ADC_CLK_DIV1_OFFSET  9

#define HI_LS_ADC_REG_BASE      0x40070000 /* LD ADC base address */
#define REG_ADC_CFG      (HI_LS_ADC_REG_BASE + 0x00)
#define REG_ADC_FIFO_CFG (HI_LS_ADC_REG_BASE + 0x04)
#define REG_ADC_IMSC     (HI_LS_ADC_REG_BASE + 0x08)
#define REG_ADC_CR       (HI_LS_ADC_REG_BASE + 0x0C)
#define REG_ADC_SR       (HI_LS_ADC_REG_BASE + 0x10)
#define REG_ADC_RIS      (HI_LS_ADC_REG_BASE + 0x14)
#define REG_ADC_MIS      (HI_LS_ADC_REG_BASE + 0x18)
#define REG_ADC_START    (HI_LS_ADC_REG_BASE + 0x1C)
#define REG_ADC_STOP     (HI_LS_ADC_REG_BASE + 0x20)
#define REG_ADC_DR       (HI_LS_ADC_REG_BASE + 0x24)
#define REG_ADC_CTRL     (HI_LS_ADC_REG_BASE + 0x28)
#define REG_ADC_EN       (HI_LS_ADC_REG_BASE + 0x2C)

#define ADC_INT_FIFO_WATER_LINE (1 << 1)
#define ADC_INT_FIFO_OVER_FLOW  (1 << 0)

#define ADC_SR_RNE (1 << 0) /* FIFO not empty flag: 0:empty 1:not empty */
#define ADC_SR_RFF (1 << 1) /* FIFO full flag 0:not full 1:full */
#define ADC_SR_BSY (1 << 2) /* ADC busy flag 0:idle 1:busy */

#define ADC_SCAN_START  1
#define ADC_SCAN_STOP   1
#define ADC_POWER_ON    0
#define ADC_POWER_OFF   1
#define ADC_ISR_DISABLE 0
#define ADC_DATA_BIT_WIDTH 12

/*
 * The longest time to get 1 data is ((0xfff+(18*8)+3)*334)ns
 * The unit of this cnt is about 5us
 */
#define ADC_PER_DATA_TIMEOUT_CNT 500
#define ADC_LOOP_DELAY_US        5

typedef void (*adc_clken_callback)(hi_void);

/**
* @ingroup  iot_ls_adc
* @brief  Callback function of ADC read data done.
CNcomment:ADC读数完成后回调函数的类型。CNend
*
* @par 描述:
*           Callback function of ADC read data done.
CNcomment:ADC读数完成后回调函数的类型。CNend
*
* @attention Can NOT be called in the interruption.
CNcomment:在其它中断响应中无法被调用。CNend
* @param  data_buf [IN] type #hi_u16 *，received data.
CNcomment:回调入参,读到的数据。CNend
* @param  length   [IN] type #hi_u32，length of the received data.
CNcomment:读取数据的长度。CNend
*
* @retval None
* @par 依赖:
*            @li hi_adc.h：Describes ADC APIs.
CNcomment:文件用于描述ADC相关接口。CNend
* @see None
*/
typedef hi_void(*adc_read_cb) (const hi_u16 *data_buf, hi_u32 length);

typedef struct {
    hi_u32 ch_vld : 8;
    hi_u32 equ_model : 2;
    hi_u32 reserved0 : 2;
    hi_u32 delay_cnt : 12;
    hi_u32 cur_bais : 2;
    hi_u32 reserved1 : 6;
} adc_cfg_reg_s;

typedef struct {
    volatile hi_u32 buf_pos; /* offset of data buffer */
    hi_u32 is_init;          /* init flag */
    hi_u32 buf_length;       /* length of data buffer length */
    hi_u16 *data_buf;        /* point of data buffer */
    adc_read_cb adc_cb;      /* callback function after read data finish */
} adc_data;


/**
 * @ingroup iot_ls_adc
 *
 * Settings: ADC RX threshold. CNcomment:设置参数：ADC接收水线。CNend
 */
typedef enum {
    HI_ADC_FIFO_WATER_LINE_127,
    HI_ADC_FIFO_WATER_LINE_124,
    HI_ADC_FIFO_WATER_LINE_64,
    HI_ADC_FIFO_WATER_LINE_32,
    HI_ADC_FIFO_WATER_LINE_16,
    HI_ADC_FIFO_WATER_LINE_8,
    HI_ADC_FIFO_WATER_LINE_4,
    HI_ADC_FIFO_WATER_LINE_1,
} hi_adc_fifo_water_line;

/**
 * @ingroup iot_ls_adc
 *
 * ADC settings. CNcomment:ADC设置参数。CNend
 */
typedef struct {
    hi_u16 delay_cnt;                     /**< Countings from config to start collect, [0xF, 0xFF].
                                           CNcomment:从配置采样到启动采样的延时时间计数，其值需在
                                           0xF~0xFFF之间 CNend */
    hi_adc_equ_model_sel equ_model_sel; /**< Average algorithm mode.
                                           CNcomment:平均算法模式 CNend */
    hi_adc_cur_bais cur_bais;           /**< ADC Analog power control.
                                           CNcomment:模拟电源控制 CNend */
    hi_adc_fifo_water_line fifo_water_line;  /**< FIFO threshold interruption settings. Not use in sync rx mode.
                                                CNcomment:FIFO水线中断设置，同步读取时无需设置 CNend */
} hi_adc_cfg;

/**
 * @ingroup iot_ls_adc
 *
 * Data format in 16bit, [0:11] are data bits, [0:2] are decimal fractions, [12:24] are channel number, [15] reserved.
 CNcomment:读取到的ADC数据格式，[0:11]是数据位，其中[0:1]是小数位。[12:14]是通道编号，
 [15]保留。CNend
 */
typedef struct {
    hi_u16 val : 12;          /**< Data bit, [0:1] are decimal fractions.
                               CNcomment:数据位，其中[0:1]是小数位 CNend */
    hi_u16 ch_id : 3;         /**< Channel number. CNcomment:通道编号 CNend */
    hi_u16 reserved : 1;
} hi_adc_data_format;

/**
* @ingroup  iot_ls_adc
* @brief  Initializes the data acquisition control module.
CNcomment:ADC模块初始化。CNend
*
* @par 描述:
*           Initializes the data acquisition control module, apply for interrupt, enable the module.
CNcomment:ADC模块初始化，对ADC模块初始化，申请中断，使能ADC模块。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other          Failure. See hi_errno.h for details.
* @see  hi_adc_shutdown。
*/
hi_u32 hi_adc_init(hi_void);

/**
* @ingroup  iot_ls_adc
* @brief   ADC settings. CNcomment:设置ADC参数。CNend
*
* @par 描述:
*          Set ADC parameters. CNcomment:设置ADC参数。CNend
*
* @attention None
* @param adc_cfg           [IN] type #hi_adc_cfg，ADC settings. CNcomment:ADC模块相关参数。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other          Failure. See hi_errno.h for details.
* @par 依赖:
*            @li hi_adc.h：Describes ADC APIs.
CNcomment:文件用于描述ADC相关接口。CNend
* @see  hi_adc_set_basic_info。
*/
hi_u32 hi_adc_set_basic_info(const hi_adc_cfg *adc_cfg);

/**
* @ingroup  iot_ls_adc
* @brief   Read ADC received data synchronously. CNcomment:同步读取ADC数据。CNend
*
* @par 描述:
*          Read ADC received data synchronously. CNcomment:同步读取ADC数据。CNend
*
* @attention None
* @param  channel          [IN] type #hi_u8 ，channel to be read. CNcomment:要使能的channel。CNend
* @param  data_buf         [IN] type #hi_u16 * ，data buffer to store the data.
CNcomment:读取的ADC数据保存buf地址。CNend
* @param  get_len          [IN] type #hi_u32 ，length to read, do NOT longer than the buffer size.
CNcomment:要读的数据长度，数据存入data_buf，不能大于data_buf长度。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other          Failure. See hi_errno.h for details.
* @par 依赖:
*            @li hi_adc.h：Describes ADC APIs.
CNcomment:文件用于描述ADC相关接口。CNend
* @see  hi_adc_get_data。
*/
hi_u32 hi_adc_read_sync(hi_u8 channel, hi_u16 *data_buf, hi_u32 get_len);

/**
* @ingroup  iot_ls_adc
* @brief   Asynchronously reading ADC data. CNcomment:异步读取ADC数据。CNend
*
* @par 描述:
*          Asynchronously reading ADC data. CNcomment:异步读取ADC数据。CNend
*
* @attention None
* @param  channel          [IN] type #hi_u8 ，channel to be read. CNcomment:要使能的channel。CNend
* @param  data_buf         [IN] type #hi_u16 * ，data buffer to store the data.
CNcomment:读取的ADC数据保存buf地址。CNend
* @param  get_len          [IN] type #hi_u32 ，length to read, do NOT longer than the buffer size.
CNcomment:要读的数据长度，数据存入data_buf，不能大于data_buf长度。CNend
* @param  cb               [IN] type #adc_read_cb ，Callback function when read done.
CNcomment:ADC读数完成后回调函数。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other          Failure. See hi_errno.h for details.
* @par 依赖:
*            @li hi_adc.h：Describes ADC APIs.
CNcomment:文件用于描述ADC相关接口。CNend
* @see  hi_adc_scan_stop。
*/
hi_u32 hi_adc_read_async(hi_u8 channel, hi_u16 *data_buf, hi_u32 get_len, adc_read_cb cb);

/**
* @ingroup  iot_ls_adc
* @brief  Deinitialize ADC module. CNcomment:关闭ADC模块。CNend
*
* @par 描述:
*           Deinitialize ADC module, clear up FIFO, disable interruption, shutdown power.
CNcomment:关闭ADC模块，清空FIFO，关闭中断，关闭电源。CNend
*
* @attention None
* @param None
* @retval None
* @par 依赖:
*            @li hi_adc.h：Describes ADC APIs.
CNcomment:文件用于描述ADC相关接口。CNend
* @see  hi_adc_init。
*/
hi_void hi_adc_deinit(hi_void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */

#endif
