/**
 * @file hi_i2c.h
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

/** @defgroup iot_i2c  I2C
 *  @ingroup drivers
 */
#ifndef __HI_I2C_H__
#define __HI_I2C_H__

#include <hi_types_base.h>

/*
 * I2C Interface
 */
#define I2C_RATE_DEFAULT  100000

typedef hi_void (*i2c_reset_func)(hi_void);
typedef hi_void (*i2c_prepare_func)(hi_void);
typedef hi_void (*i2c_restore_func)(hi_void);

/**
 * @ingroup iot_i2c
 *
 * I2C callback function. CNcomment:I2C回调函数。CNend
 */
typedef struct {
    i2c_reset_func   reset_func;    /**< This function is called back when the communication with the slave device
                                         is abnormal.CNcomment:I2C从异常处理函数CNend */
    i2c_prepare_func prepare_func;  /**< This function is called back before the I2C read/write operation to implement
                                         the preparations before the I2C operation.
                                         CNcomment:I2C操作前准备函数CNend */
    i2c_restore_func restore_func;  /**< After the I2C read/write operation is performed, this function is
                                         called back to implement the recovery after the I2C operation.
                                         CNcomment:I2C操作后恢复函数CNend */
} hi_i2c_func;

/**
 * @ingroup iot_i2c
 *
 * I2C TX/RX data descriptor. CNcomment:I2C发送/接收数据描述符。CNend
 */
typedef struct {
    hi_u8*  send_buf;        /**< Data TX pointer. The user needs to ensure that no null pointer is transferred.
                                CNcomment:数据发送指针CNend */
    hi_u32  send_len;        /**< Length of sent data (unit: byte).
                                CNcomment:发送数据长度（单位：byte）CNend */
    hi_u8*  receive_buf;     /**< Data RX pointer. CNcomment:数据接收指针CNend */
    hi_u32  receive_len;     /**< Length of received data (unit: byte).
                                CNcomment:接收数据长度（单位：byte）CNend */
} hi_i2c_data;

/**
 * @ingroup iot_i2c
 *
 * I2C hardware index. CNComment:I2C硬件设备枚举。CNend
 */
typedef enum {
    HI_I2C_IDX_0,
    HI_I2C_IDX_1,
} hi_i2c_idx;

/**
* @ingroup  iot_i2c
* @brief  Set I2C baudrate. CNcomment:I2C设置波特率。CNend
*
* @par 描述:
*           Set I2C baudrate. CNcomment:I2C设置波特率。CNend
*
* @attention Multiple tasks are not protected (multiple tasks are not supported). CNcomment:未作
多任务保护（不支持多任务）。CNend
* @param  id       [IN] type #hi_i2c_idx，I2C hardware selection. CNcomment:I2C硬件设备选择。CNend
* @param  baudrate [IN] type #hi_u32，I2C baudrate. CNcomment:I2C波特率。CNend
*
* @retval #0          Success.
* @retval #Other      Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_i2c.h：Declares the API.CNcomment:该接口声明所在的头文件。CNend
* @see  hi_i2c_write|hi_i2c_receive。
*/
hi_u32 hi_i2c_set_baudrate(hi_i2c_idx id, hi_u32 baudrate);

/**
* @ingroup  iot_i2c
* @brief  I2C data TX and RX.CNcomment:I2C发送与接收数据。CNend
*
* @par 描述:
*           The I2C sends data to the slave device and then receives data from the slave device.
CNcomment:I2C向从机发送数据，然后接收从机数据。CNend
*
* @attention Multi-tasking is not supported. CNcomment:未作多任务保护（不支持多任务）。CNend
* @param  id       [IN] type #hi_i2c_idx，I2C hardware selection. CNcomment:I2C硬件设备选择。CNend
* @param  device_addr [IN] type #hi_u16，The device ID. High three bits of offset address of the I2C device on chipset.
CNcomment:设备号及设备片内偏移地址高3位（从设备哪个地方开始读）。CNend
* @param  i2c_data  [IN/OUT] type #const hi_i2c_data*，The data descriptor to be received.
*                             The structure member data sending pointer and data receiving pointer cannot be null.
CNcomment:待接收数据描述符，结构体成员数据发送指针和数据接收指针都不为空。CNend
*
* @retval #0          Success.
* @retval #Other      Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_i2c.h：Declares the API.CNcomment:该接口声明所在的头文件。CNend
* @see  hi_i2c_write|hi_i2c_receive。
*/
hi_u32 hi_i2c_writeread(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data);

/**
* @ingroup  iot_i2c
* @brief  I2C data TX. CNcomment:I2C发送数据。CNend
*
* @par 描述:
*           I2C data TX. CNcomment:I2C发送数据。CNend
*
* @attention Multiple tasks are not protected (multiple tasks are not supported). CNcomment:未作
多任务保护（不支持多任务）。CNend
* @param  id       [IN] type #hi_i2c_idx，I2C hardware selection. CNcomment:I2C硬件设备选择。CNend
* @param  device_addr [IN] type #hi_u16，The device ID. High three bits of offset address of the I2C device on chipset.
CNcomment:设备号及设备片内偏移地址高3位（从设备哪个地方开始读）。CNend
* @param  i2c_data  [IN] type #const hi_i2c_data*，The data descriptor to be received. The structure member data sending
*                             pointer and data receiving pointer cannot be null.
CNcomment:待接收数据描述符，结构体成员数据发送指针和数据接收指针都不为空。CNend
*
* @retval #0          Success.
* @retval #Other      Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_i2c.h：Declares the API.CNcomment:该接口声明所在的头文件。CNend
* @see  hi_i2c_writeread|hi_i2c_receive。
*/
hi_u32 hi_i2c_write(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data);

/**
* @ingroup  iot_i2c
* @brief  I2C data RX. CNcomment:I2C接收数据。CNend
*
* @par 描述:
*            I2C data RX. CNcomment:I2C接收数据。CNend
*
* @attention Multi-tasking is not supported. CNcomment:未作多任务保护（不支持多任务）。CNend
* @param  id       [IN] type #hi_i2c_idx，I2C hardware selection. CNcomment:I2C硬件设备选择。CNend
* @param  device_addr [IN] type #hi_u16，The device ID. High three bits of offset address of the I2C device on chipset.
CNcomment:设备号及设备片内偏移地址高3位（从设备哪个地方开始读）。CNend
* @param  i2c_data  [OUT] type #const hi_i2c_data*，The data descriptor to be received. The structure member data sending
*                             pointer and data receiving pointer cannot be null.
CNcomment:待接收数据描述符，结构体成员数据发送指针和数据接收指针都不为空。CNend
*
* @retval #0          Success.
* @retval #Other      Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_i2c.h：Declares the API.CNcomment:该接口声明所在的头文件。CNend
* @see  hi_i2c_write|hi_i2c_sendreceive。
*/
hi_u32 hi_i2c_read(hi_i2c_idx id, hi_u16 device_addr, const hi_i2c_data *i2c_data);

/**
* @ingroup  iot_i2c
* @brief  Initializes the I2C controller. CNcomment:I2C初始化。CNend
*
* @par 描述:
*           Initializes the I2C controller. CNcomment:I2C初始化。CNend
*
* @attention None
* @param  id       [IN] type #hi_i2c_idx，I2C hardware selection. CNcomment:I2C硬件设备选择。CNend
* @param  baudrate [IN] type #hi_u32，I2C baudrate. CNcomment:I2C波特率。CNend
*
* @retval #0          Success.
* @retval #Other      Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_i2c.h：Declares the API.CNcomment:该接口声明所在的头文件。CNend
* @see  hi_i2c_deinit。
*/
hi_u32 hi_i2c_init(hi_i2c_idx id, hi_u32 baudrate);

/**
* @ingroup  iot_i2c
* @brief  Exits the I2C module.CNcomment:退出I2C模块。CNend
*
* @par 描述:
*          Exits the I2C module. CNcomment:退出I2C模块。CNend
*
* @attention This API is called after hi_i2c_init is called. CNcomment:hi_i2c_init调用后再使用。CNend
* @param  id       [IN] type #hi_i2c_idx，I2C hardware selection. CNcomment:I2C硬件设备选择。CNend
*
* @retval #0          Success.
* @retval #Other      Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_i2c.h：Declares the API.CNcomment:该接口声明所在的头文件。CNend
* @see  hi_i2c_init。
*/
hi_u32 hi_i2c_deinit(hi_i2c_idx id);

/**
* @ingroup  iot_i2c
* @brief  Registers the I2C callback function.CNcomment:注册I2C回调函数。CNend
*
* @par 描述:
*           Registers the I2C callback function, for extension.CNcomment:注册I2C回调函数，用于扩展。CNend
*
* @attention None
* @param  id      [IN] type #hi_i2c_idx，I2C hardware selection. CNcomment:I2C硬件设备选择。CNend
* @param  pfn     [IN] type #hi_i2c_func，Callback function. CNcomment:回调函数。CNend
*
* @retval #0          Success.
* @retval #Other      Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_i2c.h：Declares the API.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_void hi_i2c_register_reset_bus_func(hi_i2c_idx id, hi_i2c_func pfn);

#endif
