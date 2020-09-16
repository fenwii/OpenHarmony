/**
* @file hi_sdio_device.h
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
* Description: sdio slave mode APIs.   \n
* Create: 2019-01-17
*/

/**
 * @defgroup iot_sdio SDIO Slave
 * @ingroup drivers
 */

#ifndef __HI_SDIO_DEVICE_H__
#define __HI_SDIO_DEVICE_H__

#include <hi_types_base.h>

/**
 * @ingroup iot_sdio
 *
 * SDIO definition.CNcomment:SDIO定义CNend
 */
#define CHAN_TX_BUSY                            1
#define CHAN_TX_IDLE                            0
#define CHAN_RX_BUSY                            1
#define CHAN_RX_IDLE                            0

#define HISDIO_EXTENDREG_COUNT                  64
#define HISDIO_BLOCK_SIZE                       512

/**
 * @ingroup iot_sdio
 *
 * Device to Host sdio message type, The name can be modified according to product.
CNcomment:设备到主机的SDIO消息类型，类型名称可以根据产品实际应用场景更改。CNend
 */
typedef enum {
    D2H_MSG_WLAN_READY     = 0,
    D2H_MSG_WOW_COMPLETE   = 1,  /**< wow complete. */
    D2H_MSG_FLOWCTRL_OFF   = 2,  /**< can't send data */
    D2H_MSG_FLOWCTRL_ON    = 3,  /**< can send data */
    D2H_MSG_WAKEUP_SUCC    = 4,  /**< wakeup done */
    D2H_MSG_ALLOW_SLEEP    = 5,  /**< allow sleep */
    D2H_MSG_DISALLOW_SLEEP = 6,  /**< disalow sleep */
    D2H_MSG_DEVICE_PANIC   = 7,  /**< device panic */
    D2H_MSG_POWEROFF_ACK   = 8,  /**< poweroff cmd ack */
    D2H_MSG_CREDIT_UPDATE  = 11, /**< update high priority buffer credit value */
    D2H_MSG_HIGH_PKT_LOSS  = 12, /**< high pri pkts loss count */
    D2H_MSG_HEARTBEAT      = 14, /**< send heartbeat */
    D2H_MSG_WOW_WIFI_REDAY = 15, /**< device ready for host sleep */
    D2H_MSG_COUNT          = 32, /**< max support msg count */
} hi_sdio_d2h_msg_type_e;

/**
 * @ingroup iot_sdio
 *
 * Host to Device sdio message type, The name can be modified according to product.
CNcomment:主机到设备的SDIO消息类型，类型名称可以根据产品实际应用场景更改。CNend
 */
typedef enum {
    H2D_MSG_FLOWCTRL_ON         = 0,
    H2D_MSG_DEVICE_INFO_DUMP    = 1,
    H2D_MSG_DEVICE_MEM_DUMP     = 2,
    H2D_MSG_TEST                = 3,
    H2D_MSG_PM_WLAN_OFF         = 4,
    H2D_MSG_SLEEP_REQ           = 5,
    H2D_MSG_PM_DEBUG            = 6,
    H2D_MSG_QUERY_RF_TEMP       = 8,
    H2D_MSG_HCC_SLAVE_THRUPUT_BYPASS = 9,
    H2D_MSG_DEVICE_MEM_INFO     = 10,
    H2D_MSG_STOP_SDIO_TEST      = 11,
    H2D_MSG_FORCESLP_REQ        = 13,
    H2D_MSG_WOW_WIFI_SUSPEND    = 14,
    H2D_MSG_WOW_WIFI_RESUME     = 15,
    H2D_MSG_COUNT               = 32, /**< max support msg value count */
} hi_sdio_h2d_msg_type_e;

/**
 * @ingroup iot_sdio
 *
 * max message value between Host and Device.
 */
typedef enum {
    SDIO_DEVICE_MSG_WLAN_READY = 0,
    SDIO_DEVICE_MSG_COUNT = 32, /**< max support msg count */
    SDIO_DEVICE_MSG_BUTT
} hi_sdio_msg_e;

/**
 * @ingroup iot_sdio
 *
 * SDIO ADMA table.
 */
typedef struct {
    hi_u16                      param;
    hi_u16                      len;
    uintptr_t                   address;
} hi_sdio_admatable;

/**
 * @ingroup iot_sdio
 *
 * SDIO extend function structure.
 */
typedef struct {
    hi_u32                   int_stat;
    hi_u32                   msg_stat;
    hi_u32                   xfer_count;
    hi_u32                   credit_info;
    hi_s8                    credit_isvalid;
    hi_u8                    comm_reg[HISDIO_EXTENDREG_COUNT];
    hi_s8                    commreg_isvalid;
    hi_s32                   valid_commreg_cnt;
} hi_sdio_extendfunc;

/**
 * @ingroup iot_sdio
 *
 * use this callback to notify host msg event occurs.
 */
typedef hi_void (*notify_host_message_event)(hi_void);

/**
 * @ingroup iot_sdio
 *
 * SDIO interrupt callback structure.
 */
typedef struct {
    hi_s32 (*rdstart_callback)(hi_u32 len, hi_u8 *admatable); /**< Callback function for HOST reading.
                                                                 CNcomment:DEV感知到HOST发起了读操作 CNend */
    hi_s32 (*rdover_callback)(hi_void);                       /**< Callback function for HOST reading over.
                                                                 CNcomment:DEV感知到HOST读操作结束 CNend */
    hi_void (*rderr_callback)(hi_void);                       /**< Callback function for HOST read error.
                                                                 CNcomment:DEV感知到HOST读数据错误 CNend */
    hi_s32 (*wrstart_callback)(hi_u32 len, hi_u8 *admatable); /**< Callback function for HOST writting.
                                                                 CNcomment:DEV感知到HOST发起了写操作 CNend */
    hi_s32 (*wrover_callback)(hi_void);                       /**< Callback function for HOST write over.
                                                                 CNcomment:DEV感知到HOST写操作结束 CNend */
    hi_void (*processmsg_callback)(hi_u32 msg);               /**< Callback function for HOST getting message.
                                                                 CNcomment:DEV接收到HOST发来的消息 CNend */
    hi_void (*soft_rst_callback)(hi_void);                    /**< Callback function for HOST getting reset
                                                                 interruption.CNcomment:DEV接收到HOST发来的
                                                                 软复位中断 CNend */
} hi_sdio_intcallback;

/**
* @ingroup  iot_sdio
* @brief  sdio init function
*
* @par 描述:
*         sdio initialization function.CNcomment:sdio 初始化函数。CNend
*
* @attention None
* @param  None
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.

* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_init(hi_void);

/**
* @ingroup  iot_sdio
* @brief  sdio reinit function
*
* @par 描述:
*         sdio Reinitialize the function.CNcomment:sdio 重新初始化函数。CNend
*
* @attention None
* @param  None
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.

* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_reinit(hi_void);

/**
* @ingroup  iot_sdio
* @brief  sdio soft reset function
*
* @par 描述:
*         sdio software reset function.CNcomment:sdio 软件复位函数。CNend
*
* @attention None
* @param  None
*
* @retval None
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None
*/
hi_void hi_sdio_soft_reset(hi_void);

/**
* @ingroup  iot_sdio
* @brief  sdio register interrupt callback function
*
* @par 描述:
*         sdio register interrupt callback function.CNcomment:sdio 注册中断回调 函数。CNend
*
* @attention。
* @param  callback_func [IN] type #const hi_sdio_intcallback，sdio callback function.
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.

* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_register_callback(const hi_sdio_intcallback *callback_func);

/**
* @ingroup  iot_sdio
* @brief  sdio complete send function
*
* @par 描述:
*         sdio complete send function.CNcomment:sdio 结束发送接口函数。CNend
*
* @attention。
* @param  admatable [IN] type #hi_u8 *, adma table first address. One channel occupies eight bytes. Ensure that the
*          buffer space is sufficient to prevent memory overwriting. CNcomment:adma table首地址，一个通道占用8字节，使
*          用时请确保足够
的缓存空间，防止内存越界访问。CNend
* @param  adma_index [IN] type hi_u32, adma_index  adma Transmission channel number, range: [0-130].CNcomment:adma
*          传输通道号,范围[0-130]。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.

* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_complete_send(hi_u8 *admatable, hi_u32 adma_index);

/**
* @ingroup  iot_sdio
* @brief  set sdio pad adma table function
*
* @par 描述:
*         set sdio pad adma table function.CNcomment:sdio 配置数据对齐后的ADMA表CNend
*
* @attention。
* @param  padlen [IN] type #hi_u32, Length of data to be sent after data alignment.
CNcomment:数据对齐后要发送的数据长度。CNend
* @param  admatable [IN] type #hi_u8 *, adma table first address. One channel occupies eight bytes. Ensure that the
*         buffer space is sufficient to prevent memory overwriting.
CNcomment:adma table首地址，一个通道占用8字节，使用时请确保足够的缓存空间，防止内存越界访问。CNend
* @param  adma_index [IN] type #hi_u32, adma Transmission channel number, range: [0-130].
CNcomment:adma传输通道号,范围[0-130]。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.

* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_set_pad_admatab(hi_u32 padlen, hi_u8 *admatable, hi_u32 adma_index);

/**
* @ingroup  iot_sdio
* @brief  write extend information function
*
* @par 描述:
*         write extend information function.CNcomment:写扩展信息接口CNend
*
* @attention。
* @param  extfunc [IN] type #hi_sdio_extendfunc, Extended information pointer.CNcomment:扩展信息指针.CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.

* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_write_extendinfo(hi_sdio_extendfunc *extfunc);

/**
* @ingroup  iot_sdio
* @brief  start to send data
*
* @par 描述:
*         start to send data.CNcomment:启动数据发送接口CNend
*
* @attention。
* @param  xfer_bytes [IN] type #hi_u32, Length of sent data.CNcomment:发送数据长度.CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.

* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_void hi_sdio_send_data(hi_u32 xfer_bytes);

/**
* @ingroup  iot_sdio
* @brief  set adma table
*
* @par 描述:
*         set adma table.CNcomment:设置adma传输通道CNend
*
* @attention。
* @param  admatable [IN] type #hi_u8*, adma table first address. One channel occupies eight bytes. Ensure that the
*         buffer space is sufficient to prevent memory overwriting. CNcomment:adma table首地址，一个通道占用8字节，使
用时请确保足够的缓存空间，防止内存越界访问。CNend
* @param  adma_index [IN] type #hi_u32, adma Transmission channel number, range: [0-130].CNcomment:adma传输通道号,
范围[0-130]。CNend
* @param  data_addr [IN] type #const hi_u32 *, dama transmission destination address.CNcomment:dama 传输目的地址CNend
* @param  data_len [IN] type #hi_u32, adma Transmission data length.CNcomment:adma 传输数据长度CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h.

* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_set_admatable(hi_u8 *admatable, hi_u32 adma_index, const hi_u32 *data_addr, hi_u32 data_len);

/**
* @ingroup  iot_sdio
* @brief  schedule sdio pending message.
*
* @par 描述:
*         schedule sdio message.CNcomment:将挂起的sdio消息发送出去CNend
*
* @attention。
* @param    None
*
* @retval    #true  if there is no pending msg or send pending msg success, retun true.
CNcomment:如果没有挂起的消息，或者将挂起的消息发送成功，返回true.CNend
* @retval    #false if sdio not in work status or there is msg sending, return false.
CNcomment:如果sdio不在工作状态，或者sdio正在发送消息，返回false.CNend
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_bool hi_sdio_sched_msg(hi_void);

/**
* @ingroup  iot_sdio
* @brief  sync send message.
*
* @par 描述:
*         put msg in pending msg and send.CNcomment:将消息加入消息队列并发送CNend
*
* @attention。
* @param  msg [IN] type #hi_u32, The message, range [0-31].CNcomment:给定消息，范围[0-31].CNend
*
* @retval    #true    Success.
* @retval    #false   Failure.
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_bool hi_sdio_send_sync_msg(hi_u32 msg);

/**
* @ingroup  iot_sdio
* @brief  send given message ack
*
* @par 描述:
*         Sending a Specified Signal Message.CNcomment:发送指定消息CNend
*
* @attention:
          the current sending msg will be overwrite by this msg.
          CNcomment: 当前正在发送的消息将该消息覆盖?CNend
* @param   msg [IN] type #hi_u32, The message, range [0-31].CNcomment:给定消息，范围[0-31].CNend
*
* @retval    #true    Success.
* @retval    #false   Failure.
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_bool hi_sdio_send_msg_ack(hi_u32 msg);

/**
* @ingroup  iot_sdio
* @brief  Clear given msg and add new msg to pending msg and send.
*
* @par 描述:
*         Clear given msg and add new msg in pending msg and send.
CNcomment:清除消息队列中挂起的指定消息，将新消息加入消息队列并发送CNend
* @attention。
* @param   send_msg [IN] type #hi_u32, Message in range [0~31] which will be sent.
CNcomment:指定发送的消息号，范围[0-31]CNend
* @param   clear_msg [IN] type #hi_u32, Message in range [0~31] which will be cleard.
CNcomment:指定清除的消息号，范围[0-31]CNend
*
* @retval    #true    Success.
* @retval    #false   Failure.
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_bool hi_sdio_process_message(hi_u32 send_msg, hi_u32 clear_msg);

/**
* @ingroup  iot_sdio
* @brief  sdio is pending given message
*
* @par 描述:
*         sdio is pending given message.CNcomment:判断sdio是否挂起指定的消息CNend
*
* @attention。
* @param   msg [IN] type #hi_u32, The message, range [0-31].CNcomment:给定消息，范围[0-31].CNend
*
* @retval    #true    message at pending status.CNcomment:指定消息处于挂起状态CNend
* @retval    #false   message at other status. CNcomment:指定消息不处于挂起状态CNend
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_is_pending_message(hi_u32 msg);

/**
* @ingroup  iot_sdio
* @brief  Check whether the sdio is sending a specified message.
*
* @par 描述:
*         Check whether the sdio is sending a specified message.CNcomment:判断sdio是否正在发送指定的消息CNend
*
* @attention。
* @param   msg [IN] type #hi_u32, The message, range [0-31].CNcomment:给定消息，范围[0-31].CNend
*
* @retval    #true    The message at sending status.CNcomment:指定消息处于发送状态CNend
* @retval    #false   The message at other status.CNcomment:指定消息不处于发送状态CNend
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_u32 hi_sdio_is_sending_message(hi_u32 msg);

/**
* @ingroup  iot_sdio
* @brief  get sdio extend configuration.
*
* @par 描述:
*         get sdio extend configuration.CNcomment:获取扩展区配置信息CNend
*
* @attention None
* @param     None
*
* @retval    hi_sdio_extendfunc*  pointer to extend info buffer.
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_sdio_extendfunc *hi_sdio_get_extend_info(hi_void);

/**
* @ingroup  iot_sdio
* @brief  register callback to notify host msg or data event occurs.
*
* @par 描述:
*         register callback to notify host msg or data event occurs.
CNcomment:注册通知Host发送了消息或数据的回调函数。CNend
*
* @attention None
* @param  msg_event_callback [IN] type #notify_host_message_event, notify_host_message_event callback function when
*         sending msg or data.
CNcomment:消息或数据发送时调用的回调函数CNend
*
* @retval    None
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_void hi_sdio_register_notify_message_callback(notify_host_message_event msg_event_callback);

/**
* @ingroup  iot_sdio
* @brief  set sdio powerdown or not when system enter deep_sleep.
*
* @par 描述:
*         set sdio powerdown or not when system enter deep_sleep.
CNcomment:设置系统深睡模式下，SDIO模块是否掉电。CNend
*
* @attention default powerdown.CNcomment:默认掉电.CNend
* @param   power_down [IN] type #hi_bool, powerdown or not.CNcomment:是否掉电.CNend
*
* @retval    None
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_void hi_sdio_set_powerdown_when_deep_sleep(hi_bool power_down);

/**
* @ingroup  iot_sdio
* @brief Init sdio but not wait host clock ready and not wait func1 enable interrupt.
*
* @par 描述:
*         Init sdio but not wait host clock ready and not wait func1 enable interrupt.
CNcomment:初始化SDIO，初始化过程中不判断host时钟是否就绪，
不判断是否接收到了使能function1的中断。CNend
*
* @attention None
* @param   None
*
* @retval    None
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_void hi_sdio_init_no_wait(hi_void);

/**
* @ingroup  iot_sdio
* @brief Get whether host clock ready.
*
* @par 描述:
*         Get whether host clock ready.
CNcomment:判断HOST时钟是否就绪。CNend
*
* @attention None
* @param   None
*
* @retval    None
*
* @par 依赖:
*           @li hi_sdio_device.h：Describe sdio slave APIs.CNcomment:该接口声明所在的头文件。CNend
* @see  None。
*/
hi_bool hi_sdio_host_clk_ready(hi_void);

#endif /* end of hi_sdio_device.h */
