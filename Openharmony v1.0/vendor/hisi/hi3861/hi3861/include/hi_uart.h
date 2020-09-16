/**
 * @file hi_uart.h
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
 * Description: UART Port APIs. \n
 */
/** @defgroup iot_uart UART Port
 *  @ingroup drivers
 */
#ifndef __HI_UART_H__
#define __HI_UART_H__

#include <hi_types.h>
#include "hi_mdm_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup iot_uart
 *
 * UART serial number. CNcomment:UART序号。CNend
 */
typedef enum {
    HI_UART_IDX_0,    /**< Physical port number 0.CNcomment:物理端口号0 CNend */
    HI_UART_IDX_1,    /**< Physical port number 1.CNcomment:物理端口号1 CNend */
    HI_UART_IDX_2,    /**< Physical port number 2.CNcomment:物理端口号2 CNend */
    HI_UART_IDX_MAX   /**< Maximum physical port number, which cannot be used. CNcomment:物理端口号最大值，
                         不可使用CNend */
} hi_uart_idx;

/**
 * @ingroup iot_uart
 *
 * UART data bit. CNcomment:UART数据位。CNend
 */
typedef enum {
    HI_UART_DATA_BIT_5 = 5, /**< Data bit: support option 5bit.CNcomment:数据位：支持配置5bit.CNend */
    HI_UART_DATA_BIT_6,     /**< Data bit: support option 6bit.CNcomment:数据位：支持配置6bit.CNend */
    HI_UART_DATA_BIT_7,     /**< Data bit: support option 7bit.CNcomment:数据位：支持配置7bit.CNend */
    HI_UART_DATA_BIT_8,     /**< Data bit: support option 8bit.CNcomment:数据位：支持配置8bit.CNend */
} hi_uart_data_bit;

/**
 * @ingroup iot_uart
 *
 * UART stop bit. CNcomment:UART停止位。CNend
 */
typedef enum {
    HI_UART_STOP_BIT_1 = 1, /**< Stop bit, 1bit.CNcomment:停止位，1bit停止位.CNend */
    HI_UART_STOP_BIT_2 = 2, /**< Stop bit, 2bit.CNcomment:停止位，2bit停止位.CNend */
} hi_uart_stop_bit;

/**
 * @ingroup iot_uart
 *
 * UART parity bit. CNcomment:UART校验位。CNend
 */
typedef enum {
    HI_UART_PARITY_NONE = 0, /**< Parity bit, None. CNcomment:校验位，无校验CNend */
    HI_UART_PARITY_ODD = 1,  /**< Parity bit, odd. CNcomment:校验位，奇校验CNend */
    HI_UART_PARITY_EVEN = 2, /**< Parity bit, even. CNcomment:校验位，偶校验CNend */
} hi_uart_parity;

/**
 * @ingroup iot_uart
 *
 * UART FIFO interruption limitation. CNcomment:UART FIFO中断门限。CNend
 */
typedef enum {
    HI_FIFO_LINE_ONE_EIGHT = 1,  /**< FIFO interruption limitation, FIFO LINE = 1/8full.
                                    CNcomment:FIFO中断门限，FIFO LINE = 1/8full CNend */
    HI_FIFO_LINE_ONE_QUARTER,    /**< FIFO interruption limitation, FIFO LINE = 1/4full.
                                    CNcomment:FIFO中断门限，FIFO LINE = 1/4full CNend */
    HI_FIFO_LINE_HALF,           /**< FIFO interruption limitation, FIFO LINE = 1/2full.
                                    CNcomment:FIFO中断门限，FIFO LINE = 1/2full CNend */
    HI_FIFO_LINE_THREE_QUARTERS, /**< FIFO interruption limitation, FIFO LINE = 3/4full.
                                    CNcomment:FIFO中断门限，FIFO LINE = 3/4full CNend */
    HI_FIFO_LINE_SEVEN_EIGHTS,   /**< FIFO interruption limitation, FIFO LINE = 7/8full.
                                    CNcomment:FIFO中断门限，FIFO LINE = 7/8full CNend */
} hi_uart_fifo_line;

/**
 * @ingroup iot_uart
 *
 * UART block mode. CNcomment:UART 阻塞模式。CNend
 */
typedef enum {
    HI_UART_BLOCK_STATE_NONE_BLOCK = 1, /**< block mode, none-block. CNcomment:UART阻塞模式，非阻塞传输 CNend */
    HI_UART_BLOCK_STATE_BLOCK,          /**< block mode, block. CNcomment:UART阻塞模式，阻塞传输 CNend */
} hi_uart_block_state;

/**
 * @ingroup iot_uart
 *
 * UART DMA transmation mode. CNcomment:UART DMA传输模式。CNend
 */
typedef enum {
    HI_UART_NONE_DMA = 1, /**< None-DMA mode. CNcomment:DMA传输，不使用DMA CNend */
    HI_UART_USE_DMA,      /**< DMA mode. CNcomment:DMA传输，使用DMA CNend */
} hi_uart_dma_state;

/**
 * @ingroup iot_uart
 *
 * UART hardware flow control mode. CNcomment:UART 硬件流控控制模式。CNend
 */
typedef enum {
    HI_FLOW_CTRL_NONE,     /**< hardware flow ctrl: disable flow ctrl.CNcomment:不使用。CNend */
    HI_FLOW_CTRL_RTS_CTS,  /**< hardware flow ctrl: enable rts and cts.CNcomment:使用RTS和CTS CNend */
    HI_FLOW_CTRL_RTS_ONLY, /**< hardware flow ctrl: enable rts only.CNcomment:只使用RTS CNend */
    HI_FLOW_CTRL_CTS_ONLY, /**< hardware flow ctrl: enable cts only.CNcomment:只使用CTS CNend */
} hi_flow_ctrl;

/**
 * @ingroup iot_uart
 *
 * UART basic settings. CNcomment:UART端口基本配置参数。CNend
 */
typedef struct {
    hi_u32 baud_rate; /**< Baud Rate.CNcomment:波特率。CNend */
    hi_u8 data_bits;  /**< Data bit. CNcomment:数据位。CNend */
    hi_u8 stop_bits;  /**< Stop bit. CNcomment:停止位。CNend */
    hi_u8 parity;     /**< Parity check flag. CNcomment:奇偶校验位。CNend */
    hi_u8 pad;        /**< reserved pad */
} hi_uart_attribute;

/**
 * @ingroup iot_uart
 *
 * UART extra attributes.CNcomment:UART端口额外参数配置。CNend
 */
typedef struct {
    hi_uart_fifo_line tx_fifo_line;
    hi_uart_fifo_line rx_fifo_line;
    hi_uart_fifo_line flow_fifo_line;
    hi_uart_block_state tx_block;
    hi_uart_block_state rx_block;
    hi_u16 tx_buf_size;
    hi_u16 rx_buf_size;
    hi_uart_dma_state tx_use_dma;
    hi_uart_dma_state rx_use_dma;
} hi_uart_extra_attr;

/**
* @ingroup  iot_uart
* @brief  UART initialization. CNcomment:UART初始化。CNend
*
* @par 描述:
*           Set UART with configuration. CNcomment:根据参数配置指定UART。CNend
*
* @attention 1.If extra_attr is set to HI_NULL, all optimization parameters of the notification driver use the default
*            values.CNcomment:extra_attr为HI_NULL表示通知驱动所有优化参数使用默认值；CNend
*            2.If the value of the member parameter in extra_attr is 0, it indicates that the member parameter
*            is notified to the driver. The member parameter uses the default value.
*            CNcomment:extra_attr中成员参数值为0表示通知驱动该成员参数使用默认值；CNend
*            3.After the UART initialization is complete, if you want to change the UART optimization parameter
*            configuration, you need to call hi_uart_deinit to deinitialize the UART before calling hi_uart_init
*            to change the optimization parameter configuration. CNcomment:UART初始化完成后，若要变更UART
优化参数配置，需先调用hi_uart_deinit去初始化UART，再调用hi_uart_init变更优化参数配置。CNend
*
* @param  id            [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  param         [IN] type #const hi_uart_attribute*，UART base settings.CNcomment:UART基本参数。CNend
* @param  extra_attr    [IN] type #const hi_uart_extra_attr*，UART extra settings. CNcomment:UART优化参数。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #HI_ERR_FAILURE  Failure.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_deinit。
*/
hi_u32 hi_uart_init(hi_uart_idx id, const hi_uart_attribute *param, const hi_uart_extra_attr *extra_attr);

/**
* @ingroup  iot_uart
* @brief  Reads data.CNcomment:读数据。CNend
*
* @par 描述:
*           Reads the data received by the UART. CNcomment:将UART接收到的数据读取出来。CNend
*
* @attention This API must be used after the hi_uart_open function is called.
CNcomment:须在调用完hi_uart_init函数之后使用。CNend
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  data      [OUT] type #hi_u8*，Start address of the data to be read.CNcomment:读到数据的首地址。CNend
* @param  data_len  [IN] type #hi_u32，Number of bytes to be read.CNcomment:要读取数据的字节数。CNend
*
* @retval #>=0 Number of bytes that are actually read.CNcomment:实际读到数据的字节数。CNend
* @retval #HI_ERR_FAILURE  Data read error.CNcomment:读数据失败。CNend
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_write。
*/
hi_s32 hi_uart_read(hi_uart_idx id, hi_u8 *data, hi_u32 data_len);

/**
* @ingroup  iot_uart
* @brief  Reads data in specified timeout time.CNomment:在指定超时时间内读取数据。CNend
*
* @par 描述:
*           Reads data in specified timeout time.CNomment:在指定超时时间内读取数据。CNend
*           if Reads all data before timeout, function will return.
CNomment:超时前读取完成所有数据后，函数会立即返回。CNend
*
* @attention This API must be used after the hi_uart_open function is called.
CNcomment:须在调用完hi_uart_init函数之后使用。CNend
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  data      [OUT] type #hi_u8*，Start address of the data to be read.CNcomment:读到数据的首地址。CNend
* @param  data_len  [IN] type #hi_u32，Number of bytes to be read.CNcomment:要读取数据的字节数。CNend
* @param  timeout_ms  [IN] type #hi_u32，timeout.CNcomment:超时时间。CNend
*
* @retval #>=0 Number of bytes that are actually read.CNcomment:实际读到数据的字节数。CNend
* @retval #HI_ERR_FAILURE  Data read error.CNcomment:读数据失败。CNend
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_write。
*/
hi_s32 hi_uart_read_timeout(hi_uart_idx id, hi_u8 *data, hi_u32 len, hi_u32 timeout_ms);

/**
* @ingroup  iot_uart
* @brief  Writes data.CNcomment:写数据。CNend
*
* @par 描述:
*           Writes the data to be sent to the UART. The block mode is used by default.
CNcomment:将待发送的数据写到UART。CNend
*
* @attention This API must be used after the hi_uart_init function is called.
CNcomment:须在调用完hi_uart_init函数之后使用。CNend
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  data   [IN] type #const hi_u8*，Start address of the data to be written.CNcomment:待写数据的首地址。CNend
* @param  data_len   [IN] type #hi_u32，Number of bytes to be written.CNcomment:待写数据的字节数。CNend
*
* @retval #>=0 Number of bytes to be sent.CNcomment:实际发送数据的字节数。CNend
* @retval #HI_ERR_FAILURE  Data send failure. CNcomment:发送数据失败。CNend
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_read。
*/
hi_s32 hi_uart_write(hi_uart_idx id, const hi_u8 *data, hi_u32 data_len);

/**
* @ingroup  iot_uart
* @brief  Deinitializes UART.CNcomment:去初始化UART。CNend
*
* @par 描述:
*           Deinitializes UART.CNcomment:去初始化UART。CNend
*
* @attention This API is used together with hi_uart_init.CNcomment:与hi_uart_init成对使用。CNend
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_init。
*/
hi_u32 hi_uart_deinit(hi_uart_idx id);

/**
* @ingroup  iot_uart
* @brief  Set UART hardware flow control.CNcomment:配置UART硬件流控功能。CNend
*
* @par 描述:
*           Set UART hardware flow control.CNcomment:配置UART硬件流控功能。CNend
*
* @attention This API must be used after the hi_uart_init function is called. UART0 doesn't support flow control.
CNcomment:须在调用完hi_uart_init函数之后使用;UART0不支持流控功能。CNend
*
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  flow_ctrl [IN] type #hi_flow_ctrl，haredware flow control mode.
CNcomment:硬件流控功能控制模式。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  无。
*/
hi_u32 hi_uart_set_flow_ctrl(hi_uart_idx id, hi_flow_ctrl flow_ctrl);

/**
* @ingroup  iot_uart
* @brief  Write data by polling. CNcomment:轮询写数据。CNend
*
* @par 描述:
*           Write data by polling. CNcomment:通过轮询的方式将待发送的数据写到UART。CNend
*
* @attention This API must be used after the hi_uart_init function is called.
CNcomment:须在调用完hi_uart_init函数之后使用。CNend
*
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  data   [IN] type #const hi_u8*，Start address of the data to be written.CNcomment:待写数据的首地址。CNend
* @param  data_len   [IN] type #hi_u32，Number of bytes to be written.CNcomment:待写数据的字节数。CNend
*
* @retval #>=0 Number of bytes to be sent.CNcomment:实际发送数据的字节数。CNend
* @retval #HI_ERR_FAILURE  Data send failure. CNcomment:发送数据失败。CNend
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  None
*/
hi_s32 hi_uart_write_immediately(hi_uart_idx id, const hi_u8 *data, hi_u32 data_len);

/**
* @ingroup  iot_uart
* @brief  Obtains UART settings. CNcomment:获取UART配置参数。CNend
*
* @par 描述:
*           Obtains UART settings. CNcomment:获取指定UART当前配置参数。CNend
*
* @attention If extra_attr is HI_NULL, the current UART optimization parameters are not requested. This parameter
*            must be used after the hi_uart_init function is invoked.CNcomment:extra_attr为HI_NULL表示不请求
当前UART的优化参数;须在调用完hi_uart_init函数之后使用。CNend
*
* @param  id            [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  attr          [OUT] type #hi_uart_attribute*，UART base settings.CNcomment:UART基本参数。CNend
* @param  extra_attr    [OUT] type #hi_uart_extra_attr*，UART extra settings. CNcomment:UART优化参数。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #HI_ERR_FAILURE  Failure.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_init。
*/
hi_u32 hi_uart_get_attribute(hi_uart_idx id, hi_uart_attribute *attr, hi_uart_extra_attr *extra_attr);

/**
* @ingroup  iot_uart
* @brief  Determine FIFO and soft buf is empty. CNcomment:判断FIFO与软件BUF是否为空。CNend
*
* @par 描述:
*           Determine FIFO and soft buf is empty. CNcomment:判断指定UART的FIFO与软件BUF是否为空。CNend
*
* @attention This API must be used after the hi_uart_init function is called.
CNcomment:须在调用完hi_uart_init函数之后使用。CNend
*
* @param  id            [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  empty         [OUT] type #hi_bool*，Store query result, HI_TRUE means empty, HI_FALSE means non-empty.
CNcomment:存储查询结果，如果为HI_TRUE代表FIFO与软件BUF都为空，如果为HI_FALSE表示非空。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #HI_ERR_FAILURE  Failure.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_init。
*/
BSP_RAM_TEXT_SECTION hi_u32 hi_uart_is_buf_empty(hi_uart_idx id, hi_bool *empty);

/**
* @ingroup  iot_uart
* @brief  Determine UART is busy. CNcomment:判断UART是否忙。CNend
*
* @par 描述:
*           Determine UART is busy. CNcomment:判断指定UART是否忙。CNend
*
* @attention This API must be used after the hi_uart_init function is called.
CNcomment:须在调用完hi_uart_init函数之后使用。CNend
*
* @param  id            [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
* @param  busy          [OUT] type #hi_bool*，Store query result, HI_TRUE means busy, HI_FALSE means not busy.
CNcomment:存储查询结果，如果为HI_TRUE代表UART在忙，如果为HI_FALSE表示空闲。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #HI_ERR_FAILURE  Failure.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_init。
*/
BSP_RAM_TEXT_SECTION hi_u32 hi_uart_is_busy(hi_uart_idx id, hi_bool *busy);

/**
* @ingroup  iot_uart
* @brief  Quits Read data.CNcomment:退出阻塞读数据。CNend
*
* @par 描述:
*           Quits Read data. CNcomment:退出阻塞读数据。CNend
*
* @attention Only apply in block read mode.
CNcomment:该接口仅应用在阻塞读数据模式下。CNend
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other  Failure.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_quit_read。
*/
hi_u32 hi_uart_quit_read(hi_uart_idx id);

/**
* @ingroup  iot_uart
* @brief  Save register-related values before going to deep sleep.CNcomment:深睡前保存相关寄存器内容。CNend
*
* @par 描述:
*       Regs-related values are saved before entering deep sleep to facilitate sleep recovery.
CNcomment:深睡前保存相关寄存器内容，以便于睡醒恢复UART。CNend
*
* @attention Called before deep sleep.
CNcomment:在深睡前调用。CNend
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other  Failure.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_lp_save。
*/
hi_u32 hi_uart_lp_save(hi_uart_idx id);

/**
* @ingroup  iot_uart
* @brief  Restore register related values after deep sleep wake up.CNcomment:深睡唤醒后恢复寄存器内容。CNend
*
* @par 描述:
*      Restore register related values after deep sleep wake up.CNcomment:深睡唤醒后恢复寄存器内容。CNend
*
* @attention Called after deep sleep wake up.
CNcomment:深睡唤醒后调用。CNend
* @param  id        [IN] type #hi_uart_idx，UART port id. CNcomment:UART端口号。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other  Failure.
* @par 依赖:
*            @li hi_uart.h：Describes UART APIs.CNcomment:UART相关接口。CNend
* @see  hi_uart_lp_restore。
*/
hi_u32 hi_uart_lp_restore(hi_uart_idx id);

#ifdef __cplusplus
}
#endif

#endif
