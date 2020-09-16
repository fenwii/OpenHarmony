/**
 * @file hi_tsensor.h
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
 * @defgroup iot_tsensor Tsensor
 * @ingroup drivers
 */

#ifndef __HI_TSENSOR_H__
#define __HI_TSENSOR_H__
#include <hi_types_base.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @ingroup  iot_tsensor
* @brief Callback function of Tsensor interruption. CNcomment:Tsensor中断回调函数。CNend
*
* @par 描述:
*           Callback function of Tsensor interruption. CNcomment:Tsensor回调函数。CNend
*
* @attention None
* @param  data [IN] type #hi_s16，Parameter transfer of the callback function, indicating the temperature when the
*              interrupt is reported.CNcomment:回调函数参数传递，表示中断上报时的温度值。CNend
*
* @retval None
* @par 依赖:
*            @li hi_tsensor.h：Tsensor APIs.CNcomment:文件用于描述获取tsensor相关接口。CNend
* @see None
*/
typedef hi_void (*hi_tsensor_callback_func)(hi_s16);

/**
 * @ingroup iot_tsensor
 *
 * Tsensor report mode.CNcomment:Tsensor上报模式。CNend
 */
typedef enum {
    HI_TSENSOR_MODE_16_POINTS_SINGLE = 0, /**< Mode: 16 points single.CNcomment:模式：16点平均单次上报 CNend */
    HI_TSENSOR_MODE_16_POINTS_LOOP = 1,   /**< Mode: 16 points loop.CNcomment:模式：16点平均循环上报 CNend */
    HI_TSENSOR_MODE_1_POINT_LOOP = 2,     /**< Mode: 1 point loop.CNcomment:模式：单点循环上报 CNend */
    HI_TSENSOR_MODE_MAX,                  /**< Invalid input parameter, which cannot be used.
                                             CNcomment:错误入参，不可使用 CNend */
}hi_tsensor_mode;

#define HI_TSENSOR_INVALID_CODE 0xFFFF    /* Tsensor 无效温度码，有效温度码为(0-255) */
#define HI_TSENSOR_INVALID_TEMP (-1000)   /* Tsensor 无效温度, 有效温度码为(-40-140) */

/**
* @ingroup  iot_tsensor
* @brief tsensor module start.CNcomment:tsensor模块启动。CNend
*
* @par 描述:
*           tsensor module start.CNcomment:tsensor启动温度采集。CNend
*
* @attention Period is valid when mode = #HI_TSENSOR_MODE_16_POINTS_LOOP or HI_TSENSOR_MODE_1_POINT_LOOP.
*            By default, the tsensor HI_TSENSOR_MODE_16_POINTS_SINGLE temperature collection mode is enabled for the
*            Wi-Fi module. If this function is repeatedly called, the default mode used by the Wi-Fi module will be
*            overwritten. If you want to use the tsensor module for other services, you can register the
*            corresponding interrupt callback function in the service.
CNcomment:period仅当mode为HI_TSENSOR_MODE_16_POINTS_SINGLE有效, period范围: period * 31.25us > 16 * 192us;
WiFi模块默认启用tsensor HI_TSENSOR_MODE_16_POINTS_SINGLE温度采集模式，重复调用此函数会覆盖WiFi模块使
用的默认模式， 如要将tsensor模块用于其他业务，可直接在该业务内注册对应的中断回调函数。CNend
*
* @param  mode             [IN] type #hi_tsensor_mode，Mode of Tsensor temperature acquisition.
CNcomment:Tsensor温度采集模式。CNend
* @param  period           [IN] type #hi_u16，Acquisition period, it is the multiple of 2 ms.
CNcomment:温度自动检测周期，为32K时钟数。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_u32 hi_tsensor_start(hi_tsensor_mode mode, hi_u16 period);

/**
* @ingroup  iot_tsensor
* @brief Read temperature data.CNcomment:读取温度值。CNend
*
* @par 描述:
*          Read temperature data.CNcomment:在启动tsensor温度采集后，读取温度值。CNend
*
* @attention None
* @param  temperature      [IN] type #hi_s16*，address wait to be writed the temperature value.
CNcomment:待写入温度值的地址。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_u32 hi_tsensor_read_temperature(hi_s16* temperature);

/**
* @ingroup  iot_tsensor
* @brief Tsensor module stop.CNcomment:停止tsensor温度采集。CNend
*
* @par 描述:
*          Tsensor module stop.CNcomment:停止tsensor温度采集。CNend
*
* @attention By default, the tsensor function is enabled for the Wi-Fi module. If this function is invoked, the
*            temperature threshold protection function of the Wi-Fi module registration will be affected.
CNcomment:WiFi模块默认启用tsensor，调用此函数将会影响WiFi本身注册的温度阈值保护等功能。CNend
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_void hi_tsensor_stop(hi_void);

/**
* @ingroup  iot_tsensor
* @brief Destroy Tsensor module.CNcomment:销毁tsensor模块。CNend
*
* @par 描述:
*          On the basis of hi_tsensor_stop, this interface disables the reporting of tsensor interrupts and clears
*          the callback functions registered by users.CNcomment:在hi_tsensor_stop的基础上，此接口同时禁用了
tsensor的中断上报，并清空用户注册的回调函数。CNend
*
* @attention After this API is called, if the interrupt callback function is used, you need to invoke the corresponding
*            interface to set the interrupt function before starting the interrupt, and enable the interrupt reporting
*            function.By default, the tsensor function is enabled for the Wi-Fi module. If this function is invoked,
*            the temperature threshold protection function of the Wi-Fi module registration will be affected.
CNcomment:调用此接口后，对于使用中断回调的场景，在start之前，需再次调用相应接口设置中断函数，开启中断上报；
WiFi模块默认启用tsensor，调用此函数将会影响WiFi本身注册的温度阈值保护等功能。CNend
*
* @param None
*
* @retval None
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_void hi_tsensor_destroy(hi_void);

/**
* @ingroup  iot_tsensor
* @brief Sets the temperature calibration.CNcomment:温度校准设置。CNend
*
* @par 描述:
*          Sets the temperature calibration.CNcomment:温度校准设置。CNend
*
* @attention None
* @param  trim_code          [IN] type #hi_u8，Low 4bit valid. The corresponding temperature calibration values are
*                            as follows:CNcomment:低4bit有效，对应的温度校准值如下所示:CNend
*                            0000 ――  0.000 ℃
*                            0001 ――  1.410 ℃
*                            0010 ――  2.820 ℃
*                            0011 ――  4.230 ℃
*                            0100 ――  5.640 ℃
*                            0101 ――  7.050 ℃
*                            0110 ――  8.460 ℃
*                            0111 ――  9.870 ℃
*                            1000 ――  0.000℃
*                            1001 ―― -1.410 ℃
*                            1010 ―― -2.820 ℃
*                            1011 ―― -4.230 ℃
*                            1100 ―― -5.640 ℃
*                            1101 ―― -7.050 ℃
*                            1110 ―― -8.460 ℃
*                            1111 ―― -9.870 ℃
* @param  trim_sel           [IN] type #hi_bool，0：The temp_trim of the Tsensor IP is directly loaded by the efuse.
CNcomment:选择Tsensor IP的temp_trim由efuse直接加载，CNend
*                                                1：The temp_trim of the Tsensor IP is configured by the register.
CNcomment:选择Tsensor IP的temp_trim由寄存器配置。CNend
*
* @retval None
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_void hi_tsensor_set_temp_trim(hi_u8 trim_code, hi_bool trim_sel);

/**
* @ingroup  iot_tsensor
* @brief Converts the temperature code into a temperature value.CNcomment:温度码转换成温度值。CNend
*
* @par 描述:
*          Converts the temperature code into a temperature value.CNcomment:将温度码转换成温度值。CNend
*
* @attention None
* @param  code        [IN] type #hi_u8，temperature value.CNcomment:温度码。CNend
*
* @retval #hi_s16 Valid temperature value or invalid data (HI_TSENSOR_INVALID_TEMP).
CNcomment:有效的温度值或无效数据(HI_TSENSOR_INVALID_TEMP)。CNend
*
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_s16 hi_tsensor_code_to_temperature(hi_u8 code);

/**
* @ingroup  iot_tsensor
* @brief Converts the temperature into a temperature code.CNcomment:温度值转换成温度码。CNend
*
* @par 描述:
*          Converts the temperature into a temperature code.CNcomment:将温度值转换成温度码。CNend
*
* @attention None
* @param  temp       [IN] type #hi_float，temperature code.CNcomment:温度值。CNend
*
* @retval #hi_u16 Valid temperature value or invalid data (HI_TSENSOR_INVALID_TEMP).
CNcomment:有效的温度值或无效数据(HI_TSENSOR_INVALID_TEMP)。CNend
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_u16 hi_tsensor_temperature_to_code(hi_s16 temp);

/**
* @ingroup  iot_tsensor
* @brief Sets the temperature threshold.CNcomment:设置温度阈值门限。CNend
*
* @par 描述:
*          Sets the temperature threshold.CNcomment:设置温度阈值门限。CNend
*
* @attention This function is invoked before tsensor temperature collection is started. This function is invoked to
*            enable the function of reporting the temperature threshold interrupt. A maximum of three temperature
*            threshold interrupt callback functions can be registered at the same time. When the Wi-Fi service is
*            started, this interface is invoked to set the default high and low temperature thresholds. Before other
*            services use this interface, check whether the default high and low temperature thresholds need to be
*            changed. CNcomment:在启动tsensor温度采集之前调用，调用此函数将使能温度阈值门限中断上报, 最多可同时注册
3个温度阈值门限中断回调函数;WiFi业务启动时会调用此接口设置默认的高低温门限，此后其他业务使用此接口前，
请确认是否要修改默认的高低温门限值。CNend
*
* @param  low_temp            [IN] type #hi_s16，Low Temperature Threshold.CNcomment:低温门限。CNend
* @param  high_temp           [IN] type #hi_s16，High Temperature Threshold.CNcomment:高温门限。CNend
* @param  callback_func       [IN] type #hi_tsensor_callback_func，Indicates the callback function when the temperature
*                             exceeds the threshold.CNcomment:温度超阈值中断回调函数。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_u32 hi_tsensor_set_outtemp_threshold(hi_s16 low_temp, hi_s16 high_temp,
                                        hi_tsensor_callback_func callback_func);

/**
* @ingroup  iot_tsensor
* @brief To set the threshold for the over-high temperature threshold.CNcomment:设置超高温阈值门限。CNend
*
* @par 描述:
*          To set the threshold for the over-high temperature threshold.CNcomment:设置超高温阈值门限。CNend
*
* @attention This function is invoked before tsensor temperature collection is started. This function is invoked to
*            enable the function of reporting the temperature threshold interrupt. A maximum of three temperature
*            threshold interrupt callback functions can be registered at the same time. When the Wi-Fi service is
*            started, this interface is invoked to set the default high and low temperature thresholds. Before other
*            services use this interface, check whether the default high and low temperature thresholds need to be
*            changed. CNcomment:在启动tsensor温度采集之前调用，调用此函数将使能温度阈值门限中断上报, 最多可同时注册
3个温度阈值门限中断回调函数;WiFi业务启动时会调用此接口设置默认的高低温门限，此后其他业务使用此接口前，
请确认是否要修改默认的高低温门限值。CNend
*
* @param  over_temp           [IN] type #hi_s16，Ultra-high temperature threshold.CNcomment:超高温门限。CNend
* @param  callback_func       [IN] type #hi_tsensor_callback_func，Interrupt callback function when the temperature
*                             exceeds the upper temperature threshold. CNcomment:温度超过超高温门限中断回调函数。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_u32 hi_tsensor_set_overtemp_threshold(hi_s16 over_temp, hi_tsensor_callback_func callback_func);

/**
* @ingroup  iot_tsensor
* @brief Sets the overtemperature power-off threshold.CNcomment:设置过温掉电阈值门限。CNend
*
* @par 描述:
*          Sets the overtemperature power-off threshold.CNcomment:设置过温掉电阈值门限。CNend
*
* @attention This function is invoked before tsensor temperature collection is started. This function is invoked to
*            enable the function of reporting the temperature threshold interrupt. A maximum of three temperature
*            threshold interrupt callback functions can be registered at the same time. When the Wi-Fi service is
*            started, this interface is invoked to set the default high and low temperature thresholds. Before other
*            services use this interface, check whether the default high and low temperature thresholds need to be
*            changed. CNcomment:在启动tsensor温度采集之前调用，调用此函数将使能温度阈值门限中断上报, 最多可同时注册
3个温度阈值门限中断回调函数;WiFi业务启动时会调用此接口设置默认的高低温门限，此后其他业务使用此接口前，
请确认是否要修改默认的高低温门限值。CNend
*
* @param  pd_temp            [IN] type #hi_s16，Indicates the threshold of the overtemperature power-off threshold.
CNcomment:过温掉电阈值门限。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_u32 hi_tsensor_set_pdtemp_threshold(hi_s16 pd_temp);

/**
* @ingroup  iot_tsensor
* @brief Registers the callback function for the temperature collection completion interrupt.
CNcomment:注册温度采集完成中断回调函数。CNend
*
* @par 描述:
*          Registers the callback function for the temperature collection completion interrupt.
CNcomment:注册温度采集完成中断回调函数。CNend
*
* @attention This function is invoked before tsensor temperature collection is started. This function is invoked to
*            enable the function of reporting the temperature threshold interrupt. A maximum of three temperature
*            threshold interrupt callback functions can be registered at the same time. The tsensor temperature
*            collection period is short. In HI_TSENSOR_MODE_16_POINTS_LOOP and HI_TSENSOR_MODE_1_POINT_LOOP modes,
*            the collection completion interrupt is frequently triggered, occupying a large number of CPU resources.
*            As a result, other services may fail to be scheduled. In HI_TSENSOR_MODE_16_POINTS_SINGLE mode, a large
*            period can be set to avoid this problem, however, if the value of period is too large, the temperature
*            monitoring density decreases. Therefore, it is recommended that you do not read the temperature by
*            collecting data. CNcomment:在启动tsensor温度采集之前调用，调用此函数将使能温度采集完成中断上报,
最多可同时注册3个温度采集完成中断回调函数;tsensor温度采集周期很短，HI_TSENSOR_MODE_16_POINTS_LOOP和
HI_TSENSOR_MODE_1_POINT_LOOP模式下采集完成中断会频繁触发，占用大量cpu资源，可能会导致其他业务得不到调度，
HI_TSENSOR_MODE_16_POINTS_SINGLE模式虽然可以通过设置较大的period来避免这个问题，但过大的period值将会导致温度监控密度
的下降，因此建议尽量不要通过采集完成中断的方式读取温度。CNend
*
* @param  callback_func       [IN] type #hi_tsensor_callback_func，Temperature collection completion interrupt callback
*                             function.CNcomment:温度采集完成中断回调函数。CNend
*
* @retval #0           Success.
* @retval #Other       Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see None
*/
hi_u32 hi_tsensor_register_temp_collect_finish_int_callback(hi_tsensor_callback_func callback_func);

/**
* @ingroup  iot_tsensor
* @brief  Save register-related values before going to deep sleep.CNcomment:深睡前保存相关寄存器内容。CNend
*
* @par 描述:
*       Regs-related values are saved before entering deep sleep to facilitate sleep recovery.
CNcomment:深睡前保存相关寄存器内容，以便于睡醒恢复Tsensor。CNend
*
* @attention Called before deep sleep. It must be used in pairs with hi_tsensor_lp_restore.
CNcomment:在深睡前调用，必须与hi_tsensor_lp_restore接口成对使用。CNend
* @param None
*
* @retval None
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see  hi_tsensor_lp_restore。
*/
hi_void  hi_tsensor_lp_save(hi_void);

/**
* @ingroup  iot_tsensor
* @brief  Restore register related values after deep sleep wake up.CNcomment:深睡唤醒后恢复寄存器内容。CNend
*
* @par 描述:
*      Restore register related values after deep sleep wake up.CNcomment:深睡唤醒后恢复寄存器内容。CNend
*
* @attention Called after deep sleep wake up. It must be used in pairs with hi_tsensor_lp_save.
CNcomment:深睡唤醒后调用，必须与hi_tsensor_lp_save接口成对使用。CNend
* @param None
*
* @retval None
* @par 依赖:
*            @li hi_tsensor.h：for Tsensor APIs.CNcomment:文件用于描述tsensor相关接口。CNend
* @see  hi_tsensor_lp_save。
*/
hi_void hi_tsensor_lp_restore(hi_void);

#ifdef __cplusplus
}
#endif

#endif
