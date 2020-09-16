/**
 * @file hi_spi.h
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
 * 描述：SPI SDK APIs. CNcomment:SPI SDK调用接口。CNend
 * @li Supports synchronous serial communication with external devices as the master or slave.
 CNcomment:支持作为Master或Slave与外部设备进行同步串行通信。CNend
 * @li The SPI working reference clock is 160 MHz, the maximum output of Master SPI_CLK is 40 MHz, and the maximum
 *     output of Slave SPI_CLK is 20 MHz. CNcomment:SPI工作参考时钟为160 MHz，
 作为Master SPI_CLK最大输出为40MHz，作为Slave SPI_CLK最大支持20MHz。CNend
 * @li Provides two SPIs. The SPI0 provides one TX/RX FIFO for the 16bit×256, and the SPI1 provides one TX/RX
 *     FIFO for the 16bit×64. CNcomment:提供两路SPI，SPI0提供16bit×256的TX/RX FIFO各一个,
 SPI1提供16bit×64的TX/RX FIFO各一个。CNend
 * @li Only full-duplex communication is supported. When the half-duplex mode is used, the fixed value is sent.
 *     When the half-duplex mode is used, the data in the FIFO is discarded.
 CNcomment:只支持全双工通信，半双工收时发送固定数值，半双工收时丢弃FIFO中的数据。CNend \n
 */

/**
 * @defgroup iot_spi SPI
 * @ingroup drivers
 */

#ifndef __HI_SPI_H__
#define __HI_SPI_H__
#include <hi_types.h>

/**
* @ingroup iot_spi
*
* Channel ID, [0,1]. CNcomment:通道ID：0~1。CNend
*/
typedef enum {
    HI_SPI_ID_0 = 0,
    HI_SPI_ID_1,
} hi_spi_idx;

/**
* @ingroup iot_spi
*
* Communication polarity.CNcomment:通信极性。CNend
*/
typedef enum {
    HI_SPI_CFG_CLOCK_CPOL_0, /**< Polarity 0.CNcomment:极性0 CNend */
    HI_SPI_CFG_CLOCK_CPOL_1, /**< Polarity 1.CNcomment:极性1 CNend */
} hi_spi_cfg_clock_cpol;

/**
* @ingroup iot_spi
*
* Communication phase.CNcomment:通信相位。CNend
*/
typedef enum {
    HI_SPI_CFG_CLOCK_CPHA_0, /**< Phase 0.CNcomment:相位0 CNend */
    HI_SPI_CFG_CLOCK_CPHA_1, /**< Phase 1.CNcomment:相位1 CNend */
} hi_spi_cfg_clock_cpha;

/**
* @ingroup iot_spi
*
* Communication protocol type. CNcomment:通信协议类型。CNend
*/
typedef enum {
    HI_SPI_CFG_FRAM_MODE_MOTOROLA,  /**< Motorola protocol.CNcomment:摩托罗拉协议CNend */
    HI_SPI_CFG_FRAM_MODE_TI,        /**< Texas Instruments protocol.CNcomment:德州仪器协议CNend */
    HI_SPI_CFG_FRAM_MODE_MICROWIRE, /**< Microwire protocol.CNcomment:Microware协议CNend */
} hi_spi_cfg_fram_mode;

/**
* @ingroup iot_spi
*
* Communication bit width, that is, number of valid bits in each frame.CNcomment:通信位宽，
每帧内的有效bit数。CNend
*/
typedef enum {
    HI_SPI_CFG_DATA_WIDTH_E_4BIT = 0x3, /**< The bit width is 4 bits.CNcomment:位宽为4bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_5BIT,       /**< The bit width is 5 bits.CNcomment:位宽为5bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_6BIT,       /**< The bit width is 6 bits.CNcomment:位宽为6bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_7BIT,       /**< The bit width is 7 bits.CNcomment:位宽为7bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_8BIT,       /**< The bit width is 8 bits.CNcomment:位宽为8bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_9BIT,       /**< The bit width is 9 bits.CNcomment:位宽为9bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_10BIT,      /**< The bit width is 10 bits.CNcomment:位宽为10bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_11BIT,      /**< The bit width is 11 bits.CNcomment:位宽为11bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_12BIT,      /**< The bit width is 12 bits.CNcomment:位宽为12bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_13BIT,      /**< The bit width is 13 bits.CNcomment:位宽为13bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_14BIT,      /**< The bit width is 14 bits.CNcomment:位宽为14bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_15BIT,      /**< The bit width is 15 bits.CNcomment:位宽为15bit CNend */
    HI_SPI_CFG_DATA_WIDTH_E_16BIT,      /**< The bit width is 16 bits.CNcomment:位宽为16bit CNend */
} hi_spi_cfg_data_width;

/**
* @ingroup iot_spi
*
* Communication parameter: big-endian and little-endian transmission of each frame.
CNcomment:通信参数：每帧的传输大小端。CNend
*/
typedef enum {
    HI_SPI_CFG_ENDIAN_LITTLE, /**< Little-endian transmission.CNcomment:小端传输CNend */
    HI_SPI_CFG_ENDIAN_BIG,    /**< Big-endian transmission.CNcomment:大端传输CNend */
} hi_spi_cfg_endian;

/**
* @ingroup  iot_spi
* @brief  Type of the SPI callback function.CNcomment:SPI回调函数的类型。CNend
*
* @par 描述:
*           Type of the SPI callback function.CNcomment:SPI回调函数的类型。CNend
*
* @attention None
*
* @param  None
*
* @retval None
*
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see None
*/
typedef hi_void (*hi_spi_usr_func)(hi_void);

/**
 * @ingroup iot_spi
 *
 * Data communication parameter.CNcomment:数据通信参数。CNend
 */
typedef struct {
    hi_u32 cpol : 1;         /**< Communication polarity, type hi_spi_cfg_clock_cpol.CNcomment:通信极性，类型
                                为hi_spi_cfg_clock_cpol。CNend */
    hi_u32 cpha : 1;         /**< Communication phase, type hi_spi_cfg_clock_cpha.CNcomment:通信相位，类型
                                为hi_spi_cfg_clock_cpha。CNend */
    hi_u32 fram_mode : 2;    /**< Communication protocol type, type hi_spi_cfg_fram_mode.CNcomment:通信协议类型，类型
                                为hi_spi_cfg_fram_mode。CNend */
    hi_u32 data_width : 4;   /**< Communication bit width, type hi_spi_cfg_data_width.CNcomment:通信位宽，类型为
                                hi_spi_cfg_data_width。 CNend */
    hi_u32 endian : 1;       /**< Big-endian and little-endian, type hi_spi_cfg_endian.CNcomment:大小端，类型为
                                hi_spi_cfg_endian。CNend */
    hi_u32 pad : 23;         /**< Reserve bits.CNcomment:保留位 CNend */
    hi_u32 freq;           /**< Communication frequency, ranges 2460Hz-40MHz.CNcomment:通信频率，取值范围
                                2460Hz-40MHz。CNend */
} hi_spi_cfg_basic_info;

/**
 * @ingroup iot_spi
 *
 * Data communication parameter.CNcomment:主从设备设置。CNend
 */
typedef struct {
    hi_u32 is_slave : 1;
    hi_u32 pad : 31;
} hi_spi_cfg_init_param;
/**
* @ingroup  iot_spi
* @brief TX interface for the SPI slave mode.CNcomment:SPI从模式发送接口。CNend
*
* @par 描述:
*           TX interface for the SPI slave mode.CNcomment:SPI从模式发送接口。CNend
*
* @attention None
*
* @param  spi_id         [IN]  type #hi_spi_idx，SPI ID。
* @param  write_data     [IN]  type #hi_pvoid，TX data pointer.CNcomment;发送数据指针。CNend
* @param  byte_len       [IN]  type #hi_u32，length of the target data to be sent (unit: byte).
CNcomment:发送数据长度（单位：byte）。CNend
* @param  time_out_ms    [IN]  type #hi_u32，wait timeout period.CNcomment:超时时间。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_slave_write(hi_spi_idx spi_id, hi_pvoid write_data, hi_u32 byte_len, hi_u32 time_out_ms);

/**
* @ingroup  iot_spi
* @brief RX interface for the SPI slave mode.CNcomment:SPI从模式接收接口。CNend
*
* @par 描述:
*           RX interface for the SPI slave mode.CNcomment:SPI从模式接收接口。CNend
*
* @attention None
*
* @param  spi_id          [IN]  type #hi_spi_idx，SPI ID。
* @param  read_data       [OUT] type #hi_pvoid，RX data pointer.CNcomment:接收数据指针。CNend
* @param  byte_len        [IN]  type #hi_u32，length of the target data to be received (unit: byte).
CNcomment:接收数据长度（单位：byte）。CNend
* @param  time_out_ms    [IN]  type #hi_u32，wait timeout period.CNcomment:超时时间。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_slave_read(hi_spi_idx spi_id, hi_pvoid read_data, hi_u32 byte_len, hi_u32 time_out_ms);

/**
* @ingroup  iot_spi
* @brief Half-duplex TX interface for the SPI master mode.CNcomment:SPI主模式半双工发送接口。CNend
*
* @par 描述:
*          Half-duplex TX interface for the SPI master mode.CNcomment: SPI主模式半双工发送接口。CNend
*
* @attention None
*
* @param  spi_id         [IN]  type #hi_spi_idx，SPI ID。
* @param  write_data     [IN]  type #hi_pvoid，TX data pointer.CNcomment;发送数据指针。CNend
* @param  byte_len       [IN]  type #hi_u32，length of the target data to be sent (unit: byte).
CNcomment:发送数据长度（单位：byte）。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_host_write(hi_spi_idx spi_id, hi_pvoid write_data, hi_u32 byte_len);

/**
* @ingroup  iot_spi
* @brief Half-duplex RX interface for the SPI master mode.CNcomment:SPI主模式半双工接收接口。CNend
*
* @par 描述:
*           Half-duplex RX interface for the SPI master mode.CNcomment:SPI主模式半双工接收接口。CNend
*
* @attention None
*
* @param  spi_id          [IN]  type #hi_spi_idx，SPI ID。
* @param  read_data       [OUT] type #hi_pvoid，RX data pointer.CNcomment:接收数据指针。CNend
* @param  byte_len        [IN]  type #hi_u32，length of the target data to be received (unit: byte).
CNcomment:接收数据长度（单位：byte）。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_host_read(hi_spi_idx spi_id, hi_pvoid read_data, hi_u32 byte_len);

/**
* @ingroup  iot_spi
* @brief Full-duplex TX/RX interface for the SPI master mode.CNcomment:SPI主模式全双工收发接口。CNend
*
* @par 描述:
*           Full-duplex TX/RX interface for the SPI master mode.CNcomment:SPI主模式全双工收发接口。CNend
*
* @attention None.
*
* @param  spi_id          [IN]  type #hi_spi_idx，SPI ID。
* @param  write_data     [IN]  type #hi_pvoid，TX data pointer.CNcomment;发送数据指针。CNend
* @param  read_data       [OUT] type #hi_pvoid，RX data pointer.CNcomment:接收数据指针。CNend
* @param  byte_len        [IN]  type #hi_u32，length of the target data to be received (unit: byte).
CNcomment:接收数据长度（单位：byte）。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_host_writeread(hi_spi_idx spi_id, hi_pvoid write_data, hi_pvoid read_data, hi_u32 byte_len);


/**
* @ingroup  iot_spi
* @brief Configures the SPI parameter.CNcomment:配置SPI参数。CNend
*
* @par 描述:
*           Configures the SPI parameter.CNcomment:配置SPI参数。CNend
*
* @attention None
*
* @param  spi_id   [IN]  type #hi_spi_idx，SPI ID。
* @param  param    [IN]  type #hi_spi_cfg_basic_info，SPI parameters.CNcomment:SPI参数。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_set_basic_info(hi_spi_idx spi_id, const hi_spi_cfg_basic_info *param);

/**
* @ingroup  iot_spi
* @brief  Initializes the SPI module.CNcomment:SPI模块初始化。CNend
*
* @par 描述:
*           Initializes the SPI module.CNcomment:SPI模块初始化。CNend
*
* @attention To initialize the SPI module, the user needs to perform the initial configuration on the SPI
*            information as follows:CNcomment:对SPI模块初始化，用户需要对SPI如下信息进行初始配置：CNend
*            @li Clear spi_ctrl to 0.CNcomment:spi_ctrl进行清空为0操作。CNend
*            @li Configure the master/slave mode. CNcomment:配置SPI[id]的主/从模式。CNend
*            @li Configure the transfer parameters.CNcomment:配置SPI[id]的传输参数。CNend
*
* @param  spi_id     [IN] type #hi_spi_idx，SPI ID。
* @param  init_param [IN] type #hi_spi_cfg_init_param，initialize as a slave device.CNcomment:是否做为从设备。CNend
* @param  param      [IN] type #const hi_spi_cfg_basic_info*，configure parameters.CNcomment:初始化SPI设备参数。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_init(hi_spi_idx spi_id, hi_spi_cfg_init_param init_param, const hi_spi_cfg_basic_info *param);

/**
* @ingroup  iot_spi
* @brief  Deinitializes the SPI module.CNcomment:SPI模块去初始化。CNend
*
* @par 描述:
*           Deinitializes the SPI module.CNcomment:SPI模块去初始化。CNend
*
* @attention None
* @param  spi_id  [IN] type #hi_spi_idx，SPI ID。
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
 */
hi_u32 hi_spi_deinit(hi_spi_idx spi_id);

/**
* @ingroup  iot_spi
* @brief  Set a master spi to use irq mode.CNcomment:设置是否使用中断方式传输数据。CNend
*
* @par 描述:
*         Set a master spi to use irq mode.CNcomment:设置是否使用中断方式传输数据。CNend
*
* @attention None
* @param  spi_id        [IN] type #hi_spi_idx，SPI ID。
* @param  irq_en        [IN] type #hi_bool，enable irq. CNcomment:是否使用中断方式。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_set_irq_mode(hi_spi_idx id, hi_bool irq_en);

/**
* @ingroup  iot_spi
* @brief  Set a master spi to use dma mode.CNcomment:设置slave 模式下是否使用DMA方式传输数据。CNend
*
* @par 描述:
*         Set a master spi to use dma mode.CNcomment:设置slave模式下是否使用DMA方式传输数据。CNend
*
* @attention None
* @param  spi_id        [IN] type #hi_spi_idx，SPI ID。
* @param  dma_en        [IN] type #hi_bool，enable dma. CNcomment:是否使用DMA方式。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_set_dma_mode(hi_spi_idx id, hi_bool dma_en);

/**
* @ingroup  iot_spi
* @brief  Register a user to prepare or restore function.CNcomment:注册用户准备/恢复函数。CNend
*
* @par 描述:
*           Register a user to prepare or restore function.CNcomment:注册用户准备/恢复函数。CNend
*
* @attention None
* @param  spi_id    [IN] type #hi_spi_idx，SPI ID。
* @param  prepare_f [IN] type #hi_spi_usr_func，user prepare function.CNcomment:用户准备函数。CNend
* @param  restore_f [IN] type #hi_spi_usr_func，user restore fucntion.CNcomment:用户恢复函数。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_register_usr_func(hi_spi_idx id, hi_spi_usr_func prepare_f, hi_spi_usr_func restore_f);

/**
* @ingroup  iot_spi
* @brief  Set whether to loopback test mode.CNcomment:设置是否为回环测试模式。CNend
*
* @par 描述:
*          Set whether to loopback test mode.CNcomment:设置是否为回环测试模式。CNend
*
* @attention None
* @param  id        [IN] type #hi_spi_idx，SPI ID.CNcomment:ID 号。CNend
* @param  lb_en     [IN] type #hi_bool，loop back enable.CNcomment:使能回环模式。CNend
*
* @retval #0               Success
* @retval #Other           Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_spi.h：Describes the SPI APIs.CNcomment:文件用于描述SPI相关接口。CNend
* @see  None
*/
hi_u32 hi_spi_set_loop_back_mode(hi_spi_idx id, hi_bool lb_en);


#endif
