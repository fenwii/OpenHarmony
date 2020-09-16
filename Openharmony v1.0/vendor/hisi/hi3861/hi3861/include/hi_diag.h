/**
* @file hi_diag.h
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

/** @defgroup iot_diag Diagnostic
 *  @ingroup dfx
 */

#ifndef __HI_DIAG_H__
#define __HI_DIAG_H__

#include <hi_types.h>
#include <hi_uart.h>

/**
* @ingroup  iot_diag
* @brief Registers the callback function for DIAG channel status changes.
CNcomment:注册DIAG通道状态变更回调函数。CNend
*
* @par 描述:
*           Registers the callback function for DIAG channel status changes. That is, when the DIAG channel is
*           connected or disconnected, the function registered by this API is called back.
CNcomment:注册DIAG通道变更回调函数（即：当DIAG通道连接或断开时，会回调本接口注册的函数）。CNend
*
* @attention None
* @param  connect_notify_func [IN] type #hi_diag_connect_f，User function. CNcomment:用户函数。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_u32 hi_diag_register_connect_notify(hi_diag_connect_f connect_notify_func);

/**
* @ingroup  iot_diag
* @brief Checks the connection status of the DIAG channel. CNcomment:检测DIAG通道连接状态的函数。CNend
*
* @par 描述:
*           Checks the connection status of the DIAG channel. CNcomment:检测DIAG通道是否处于连接状态的函数 。CNend
*
* @attention None
* @param None
*
* @retval HI_FALSE disconnected. CNcomment:处于非连接状态。CNend
* @retval HI_TRUE  connected. CNcomment:处于连接状态。CNend
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_bool hi_diag_is_connect(hi_void);

/**
* @ingroup  iot_diag
* @brief  Registers the command handling function. CNcomment:注册命令处理函数。CNend
*
* @par 描述:
*           @li Called at initialize stage, does NOT support multiable task calls.
CNcomment:在初始化阶段调用, 不支持多任务调用。CNend
*           @li The DIAG subsystem supports a maximum of 10 different command tables.
CNcomment:最多能注册10个不同的命令表。CNend
*
* @attention None
* @param  p_cmd_tbl  [IN] type #const hi_diag_cmd_reg_obj*，Command table, which must be declared as a constant array
*                              and transmitted to this parameter.
CNcomment:命令表，必须申明为常量数组传给该参数。CNend
* @param  cmd_num    [IN] type #hi_u16，Number of commands. The value cannot be 0. CNcomment:命令个数，
如果usCmdNum为0而pstCmdTbl不为0，则取消注册。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_u32 hi_diag_register_cmd(const hi_diag_cmd_reg_obj* cmd_tbl, hi_u16 cmd_num);

/**
* @ingroup  iot_diag
* @brief  Reports DIAG packets. CNcomment:DIAG包上报。CNend
*
* @par 描述:
*           Reports DIAG channel packets to the DIAG client.
CNcomment:该函数用于将DIAG通道报文上报给DIAG客户端。CNend
*
* @attention
*         This API can not be used in interrupt when report data synchronously.
CNcomment:当同步上报数据时，该接口不支持在中断中调用。CNend
* @param  cmd_id       [IN] type #hi_u16，DIAG data packet ID. CNcomment:DIAG应答包ID。CNend
* @param  instance_id  [IN] type #hi_u8，Command type.This parameter is used to obtain the command type in the
*                           option parameter of the command callback function hi_diag_cmd_f.currently only support
*                           HI_DIAG_CMD_INSTANCE_LOCAL.
CNcomment:命令类型。在命令回调函数hi_diag_cmd_f的option参数中获取命令类型，在函数中使用
此接口回复报文时，通过本参数传递。当前仅支持HI_DIAG_CMD_INSTANCE_LOCAL。CNend
* @param  buffer       [IN] type #hi_pbyte，Buffer address of the data packet. This function does not release the
*                      pointer. CNcomment:数据包的buffer地址，该函数不会释放该指针。CNend
* @param  buffer_size  [IN] type #hi_u16，Data packet size (unit: byte), range[0, 65507]
CNcomment:数据包大小（单位：byte），取值范围[0, 65507]。CNend
* @param  sync         [IN] type #hi_bool，Synchronous or asynchronous DIAG packet pushing. TRUE indicates that the
*                           packets are pushed synchronously and the operation is blocked. FALSE indicates the packets
*                           are pushed asynchronously (with the memory allocated, the packet is cashed by the OS queue
*                           before being pushed), and the operation is not blocked.
CNcomment:DIAG包同步/异步上报设置。TRUE表示同步上报, 阻塞操作; FALSE表示异步
（通过分配内存后, 由OS队列缓存再上报), 非阻塞操作。CNend
*
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_u32 hi_diag_report_packet(hi_u16 cmd_id, hi_u8 instance_id, hi_pbyte buffer,
                                       hi_u16 buffer_size, hi_bool sync);

/**
* @ingroup  iot_diag
* @brief  Sends ACK packets to the DIAG client. CNcomment:应答回复。CNend
*
* @par 描述:
*           Sends ACK packets to the DIAG client. CNcomment:该函数用于回复报文或ACK给DIAG客户端。CNend
*
* @attention
*         This API can not be used in interrupt.CNcomment:该接口不支持在中断中调用。CNend
* @param  cmd_id       [IN] type #hi_u16，DIAG ACK packet ID. CNcomment:DIAG包ID。CNend
* @param  instance_id  [IN] type #hi_u8，Command type.This parameter is used to obtain the command type in the
*                           option parameter of the command callback function hi_diag_cmd_f.currently only support
*                           HI_DIAG_CMD_INSTANCE_LOCAL.
CNcoment:在命令回调函数HI_DIAG_CMD_F的option参数中获取命令类型，在函数中使用此接口回复
报文时，通过本参数传递。当前仅支持HI_DIAG_CMD_INSTANCE_LOCAL。CNend
* @param  buffer       [IN] type #hi_pbyte，Buffer address of the data packet. This function does not release the
*                      pointer. CNcomment:数据包的buffer地址，该函数不会释放该指针。CNend
* @param  buffer_size  [IN] type #hi_u16，Data packet size(unit: byte), range[0, 1024]
CNcomment:数据包大小（单位：byte），取值范围[0, 1024]。CNend
*
* @retval #HI_ERR_CONSUMED   Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_u32 hi_diag_send_ack_packet(hi_u16 cmd_id, hi_u8 instance_id, hi_pvoid buffer, hi_u16 buffer_size);

/**
* @ingroup  iot_diag
* @brief  Registers the callback function for notifying DIAG operations.
CNcomment:注册DIAG操作通知回调函数。CNend
*
* @par 描述:
*           Carbon copies data to the app layer by using a callback function in the case of data interaction between
*           the host and the board.CNcommand:该函数用于当上位机与单板有数据交互发生时，
将数据通过回调函数抄送给应用层。CNend
*
* @attention None
* @param  cmd_notify_func  [IN] type #hi_diag_cmd_notify_f*，When data interaction occurs between the HSO and the board,
*                                    this API is used to notify the app layer.
CNcomment:当HSO与单板有数据交互发生时，通过该接口通知应用层。CNend
*
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_u32 hi_diag_register_cmd_notify(hi_diag_cmd_notify_f cmd_notify_func);

/**
* @ingroup  iot_diag
* @brief  Sets the UART parameters of the DIAG channel. CNcomment:设置诊断通道UART参数。CNend
*
* @par 描述:
*           Sets the UART parameters of the used by the DIAG subsystem before the DIAG subsystem is initialized.
CNcomment:该函数用于在诊断子系统初始化之前，设置诊断子系统使用的UART的相关参数。CNend
*
* @attention The parameters must be set before the initialization of the DIAG subsystem.
CNcomment:必须在诊断子系统初始化之前设置才可生效。CNend
* @param  uart_port [IN] type #hi_uart_idx，UART port number used by the DIAG subsystem.
CNcomment:诊断子系统使用的UART端口号。CNend
* @param  uart_cfg  [IN] type #hi_uart_attribute，UART configuration used by the DIAG subsystem.
CNcomment:诊断子系统使用的UART配置。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_u32 hi_diag_set_uart_param(hi_uart_idx uart_port, hi_uart_attribute uart_cfg);

/**
* @ingroup  iot_diag
* @brief  Initializes the DIAG subsystem. CNcomment:诊断子系统初始化。CNend
*
* @par 描述:
*           Initializes the DIAG subsystem. CNcomment:该函数用于初始化诊断子系统。CNend
*
* @attention The initialization of the DIAG subsystem needs to be performed only once. Repeated initialization is
*            invalid. CNcomment:诊断子系统初始化只需执行一次，多次初始化无效。CNend
* @param None
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_u32 hi_diag_init(hi_void);

/**
* @ingroup  iot_diag
*
* Structure for querying the number of command tables and statistic object tables.
CNcomment:命令注册列表和统计量对象注册列表个数查询结构体。CNend
*/
typedef struct {
    hi_u8 cmd_list_total_cnt;    /**< Number of command registration tables can be registered.
                                    CNcomment:总共支持注册的命令列表个数 CNend */
    hi_u8 cmd_list_used_cnt;     /**< Number of registered command tables.
                                    CNcomment:已经注册的命令列表个数 CNend */
    hi_u8 stat_list_total_cnt;   /**< Number of statistic object tables can be registered. Currently not support.
                                    CNcomment:总共支持注册的统计量对象列表个数。当前暂不支持。 CNend */
    hi_u8 stat_list_used_cnt;    /**< Number of registered statistic object tables. Currently not support.
                                    CNcomment:已经注册的统计量对象列表个数。当前暂不支持。 CNend */
} hi_diag_cmd_stat_reg_info;

/**
* @ingroup  iot_diag
* @brief  Queries the registration status of the command tables and statistic tables of the DIAG subsystem.
CNcomment:查询诊断子系统命令列表和统计量列表注册情况。CNend
*
* @par 描述:
*      Queries the registration status of the command tables and statistic tables of the DIAG subsystem.
*      Number of registered command tables and number of command tables can be registered/ Number of registered
*      statistic object tables
CNcomment:查询总共支持注册/已经注册的命令列表个数、总共支持注册/已经注册的统计量对象列表个数。CNend
*
* @attention None
* @param     None
*
* @retval #hi_diag_cmd_stat_reg_info Structure of the number of registered command tables and statistic tables.
CNcomment:命令列表和统计量列表注册个数信息结构体。CNend
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
HI_EXTERN hi_diag_cmd_stat_reg_info hi_diag_get_cmd_stat_reg_info(hi_void);

typedef struct {
    hi_u32 data0;
    hi_u32 data1;
    hi_u32 data2;
    hi_u32 data3;
}diag_log_msg;

/**
* @ingroup  iot_diag
* @brief  Reports usr packets. CNcomment:上报用户日志。CNend
*
* @par 描述:
*      Reports usr packets. CNcomment:上报用户日志消息。CNend
*
* @attention None
* @param  diag_usr_msg   [IN] type #hi_diag_layer_msg，log message. CNcomment:日志消息。CNend
* @param  msg_level      [IN] type #hi_u16，level of log message, [HI_MSG_USR_L0, HI_MSG_USR_L4].
CNcomment:日志消息级别，取值从:HI_MSG_USR_L0- HI_MSG_USR_L4。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_report_usr_msg(const hi_diag_layer_msg* diag_usr_msg, hi_u16 msg_level);

/**
* @ingroup  iot_diag
* @brief  Reports simple packet that without data. CNcomment:上报简单日志，不携带数据内容。CNend
*
* @par 描述:
*      Reports simple packets, fixed module ID. CNcomment:上报简单日志消息，固定模块ID。
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  msg_level      [IN] type #hi_u16，log message level, [HI_MSG_SYS_L0, HI_MSG_SYS_L2]
CNcomment:日志消息级别，取值从:HI_MSG_SYS_L0- HI_MSG_SYS_L2。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_log_msg0(hi_u32 msg_id, hi_u16 msg_level);

/**
* @ingroup  iot_diag
* @brief  Reports simple packet that with one word data. CNcomment:上报简单日志，携带1个数据。CNend
*
* @par 描述:
*      Reports simple packets, fixed module ID. CNcomment:上报简单日志消息，固定模块ID。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  d0             [IN] type #hi_u32，first data. CNcomment:携带的第1个数据。Cnend
* @param  msg_level      [IN] type #hi_u16，log message level, [HI_MSG_SYS_L0, HI_MSG_SYS_L2]
CNcomment:日志消息级别，取值从:HI_MSG_SYS_L0- HI_MSG_SYS_L2。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_log_msg1(hi_u32 msg_id, hi_u32 d0, hi_u16 msg_level);

/**
* @ingroup  iot_diag
* @brief  Reports simple packet that with 2 words data. CNcomment:上报简单日志，携带2个数据。CNend
*
* @par 描述:
*      Reports simple packets, fixed module ID. CNcomment:上报简单日志消息，固定模块ID。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  d0             [IN] type #hi_u32，first data. CNcomment:携带的第1个数据。CNend
* @param  d1             [IN] type #hi_u32，second data. CNcomment:携带的第2个数据。CNend
* @param  msg_level      [IN] type #hi_u16，log message level, [HI_MSG_SYS_L0, HI_MSG_SYS_L2]
CNcomment:日志消息级别，取值从:HI_MSG_SYS_L0- HI_MSG_SYS_L2。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_log_msg2(hi_u32 msg_id, hi_u32 d0, hi_u32 d1, hi_u16 msg_level);

/**
* @ingroup  iot_diag
* @brief  Reports simple packet that with three words data. CNcomment:上报简单日志，携带3个数据。CNend
*
* @par 描述:
*      Reports simple packets, fixed module ID. CNcomment:上报简单日志消息，固定模块ID。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  d0             [IN] type #hi_u32，first data. CNcomment:携带的第1个数据。Cnend
* @param  d1             [IN] type #hi_u32，second data. CNcomment:携带的第2个数据。CNend
* @param  d2             [IN] type #hi_u32，third data. CNcomment:携带的第3个数据。CNend
* @param  msg_level      [IN] type #hi_u16，log message level, [HI_MSG_SYS_L0, HI_MSG_SYS_L2]
CNcomment:日志消息级别，取值从:HI_MSG_SYS_L0- HI_MSG_SYS_L2。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_log_msg3(hi_u32 msg_id, hi_u32 d0, hi_u32 d1, hi_u32 d2, hi_u16 msg_level);

/**
* @ingroup  iot_diag
* @brief  Reports simple packet that with four words data. CNcomment:上报简单日志，携带4个数据。CNend
*
* @par 描述:
*      Reports simple packets, fixed module ID. CNcomment:上报简单日志消息，固定模块ID。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  log_msg        [IN] type #diag_log_msg，four words. CNcomment:携带4个数据。CNend
* @param  msg_level      [IN] type #hi_u16，log message level, [HI_MSG_SYS_L0, HI_MSG_SYS_L2]
CNcomment:日志消息级别，取值从:HI_MSG_SYS_L0- HI_MSG_SYS_L2。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_log_msg4(hi_u32 msg_id, diag_log_msg log_msg, hi_u16 msg_level);

/**
* @ingroup  iot_diag
* @brief  Reports simple packet that with one buffer data. CNcomment:上报简单日志，携带数据buffer。CNend
*
* @par 描述:
*      Reports simple packets, fixed module ID. CNcomment:上报简单日志消息，固定模块ID。CNend
*
* @attention A maximum of 99 bytes can be send in one diag packet, so param size cannot be greater than 99.
CNcomment:diag单包最多能发99字节数据，参数size不能大于99。CNend
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  buffer         [IN] type #hi_pvoid，address of the data. CNcomment:携带的数据buffer首地址。CNend
* @param  size           [IN] type #hi_16，buffer size (unit byte).
CNcomment:携带的数据buffer长度(单位byte)。CNend
* @param  msg_level      [IN] type #hi_u16，log message level, [HI_MSG_SYS_L0, HI_MSG_SYS_L2]
CNcomment:日志消息级别，取值从:HI_MSG_SYS_L0- HI_MSG_SYS_L2。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_log_msg_buffer(hi_u32 msg_id, hi_pvoid buffer, hi_u16 size, hi_u16 msg_level);

/**
* @ingroup  iot_diag
* @brief  Reports layer log that without data. CNcomment:上报层间简单日志，不携带数据内容。CNend
*
* @par 描述:
*      Reports layer log that without data. CNcomment:上报层间简单日志，不携带数据内容。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  module_id      [IN] type #hi_u16，message module ID，describe which module the log belongs to.
CNcomment:消息模块ID，描述日志属于哪个模块。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_layer_msg0(hi_u32 msg_id, hi_u16 module_id);

/**
* @ingroup  iot_diag
* @brief  Reports layer log that with one word data. CNcoment:上报层间简单日志，携带1个数据。CNend
*
* @par 描述:
*      Reports layer log that with one word data. CNcoment:上报层间简单日志，携带1个数据。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  module_id      [IN] type #hi_u16，message module ID，describe which module the log belongs to.
CNcomment:消息模块ID，描述日志属于哪个模块。CNend
* @param  d0             [IN] type #hi_u32，first data. CNcomment:携带的第1个数据。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_layer_msg1(hi_u32 msg_id, hi_u16 module_id, hi_u32 d0);

/**
* @ingroup  iot_diag
* @brief  Reports layer log that with two words data. CNcoment:上报层间简单日志，携带2个数据。CNend
*
* @par 描述:
*      Reports layer log that with two words data. CNcoment:上报层间简单日志，携带2个数据。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  module_id      [IN] type #hi_u16，message module ID，describe which module the log belongs to.
CNcomment:消息模块ID，描述日志属于哪个模块。CNend
* @param  d0             [IN] type #hi_u32，first data. CNcomment:携带的第1个数据。CNend
* @param  d1             [IN] type #hi_u32，second data. CNcomment:携带的第2个数据。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_layer_msg2(hi_u32 msg_id, hi_u16 module_id, hi_u32 d0, hi_u32 d1);

/**
* @ingroup  iot_diag
* @brief  Reports layer log that with 3 words data. CNcoment:上报层间简单日志，携带3个数据。CNend
*
* @par 描述:
*      Reports layer log that with 3 words data. CNcoment:上报层间简单日志，携带3个数据。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  module_id      [IN] type #hi_u16，message module ID，describe which module the log belongs to.
CNcomment:消息模块ID，描述日志属于哪个模块。CNend
* @param  d0             [IN] type #hi_u32，first data. CNcomment:携带的第1个数据。CNend
* @param  d1             [IN] type #hi_u32，second data. CNcomment:携带的第2个数据。CNend
* @param  d2             [IN] type #hi_u32，third data. CNcomment:携带的第3个数据。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_layer_msg3(hi_u32 msg_id, hi_u16 module_id, hi_u32 d0, hi_u32 d1, hi_u32 d2);

/**
* @ingroup  iot_diag
* @brief  Reports layer log that with 4 words data. CNcoment:上报层间简单日志，携带4个数据。CNend
*
* @par 描述:
*      Reports layer log that with 4 words data. CNcoment:上报层间简单日志，携带4个数据。CNend
*
* @attention None
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  module_id      [IN] type #hi_u16，message module ID，describe which module the log belongs to.
CNcomment:消息模块ID，描述日志属于哪个模块。CNend
* @param  log_msg        [IN] type #diag_log_msg，four data to report. CNcomment:携带4个数据。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
*/
hi_u32 hi_diag_layer_msg4(hi_u32 msg_id, hi_u16 module_id, diag_log_msg log_msg);

/**
* @ingroup  iot_diag
* @brief  Reports layer log that with one buffer data. CNcomment:上报层间简单日志，携带数据buffer。CNend
*
* @par 描述:
*      Reports layer log that with one buffer data. CNcomment:上报层间简单日志，携带数据buffer。CNend
*
* @attention A maximum of 99 bytes can be send in one diag packet, so param size cannot be greater than 99.
CNcomment:diag单包最多能发99字节数据，参数size不能大于99。CNend
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  module_id      [IN] type #hi_u16，message module ID，describe which module the log belongs to.
CNcomment:消息模块ID，描述日志属于哪个模块。CNend
* @param  buffer         [IN] type #const hi_pvoid，address of the data. CNcomment:携带的数据buffer首地址。CNend
* @param  size           [IN] type #hi_16，buffer size (unit byte).
CNcomment:携带的数据buffer长度(单位byte)。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
*/
hi_u32 hi_diag_layer_msg_buffer(hi_u32 msg_id, hi_u16 module_id, const hi_void *buffer, hi_u16 size);

typedef struct {
    hi_u16 size1;
    hi_u16 size2;
} diag_buffer_size;

/**
* @ingroup  iot_diag
* @brief  Reports layer log that with two buffer data. CNcomment:上报层间简单日志，支持携带两个数据buffer。CNend
*
* @par 描述:
*      Reports layer log that with two buffer data. CNcomment:上报层间简单日志，支持携带两个数据buffer。CNend
*
* @attention A maximum of 99 bytes can be send in one diag packet.A space is reserved between two buffers.
             Therefore, the sum of buffer_size.size1 and buffer_size.size2 cannot be greater than 98.
CNcomment:diag单包最多能发99字节数据，两个buffer之间会预留一个空格，所以参数buffer_size.size1与buffer_size.size2的和不能大于98。CNend
* @param  msg_id         [IN] type #hi_u32，log message ID. CNcomment:日志消息ID。CNend
* @param  module_id      [IN] type #hi_u16，message module ID，describe which module the log belongs to.
CNcomment:消息模块ID，描述日志属于哪个模块。CNend
* @param  buf1           [IN] type #const hi_void *，address of the first buffer.
CNcomment:携带的数据buffer1首地址。CNend
* @param  buf1           [IN] type #const hi_void *，address of the second buffer.
CNcomment:携带的数据buffer2首地址。CNend
* @param  buffer_size    [IN] type #diag_buffer_size，two buffer size (unit byte).
CNcomment:携带的数据buffer长度(单位byte)。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
*/
hi_u32 hi_diag_layer_two_buffer(hi_u32 msg_id, hi_u16 module_id, const hi_void *buf1,
                                const hi_void *buf2, diag_buffer_size buffer_size);

/**
* @ingroup  iot_diag
* @brief  Set whether to check the UART busy status when low power vote.
CNcomment:设置低功耗投票时是否检查UART busy状态。CNend
*
* @par 描述:
*      Set whether to check the UART busy status when low power vote.
CNcomment:设置低功耗投票时是否检查UART busy状态。CNend
*
* @attention UART busy status is not checked by default.
CNcomment:默认低功耗睡眠投票时不检查UART busy状态。CNend
* @param  enable         [IN] type #hi_bool，enable status. CNcomment:设置是否检查UART busy状态。CNend
*
* @retval None
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
*/
hi_void hi_diag_set_check_uart_busy(hi_bool enable);

typedef  hi_s32 (*hi_diag_input_func)(hi_u8 *data, hi_u32 data_len);
typedef  hi_s32 (*hi_diag_output_func)(const hi_u8 *data, hi_u32 data_len);

/**
* @ingroup  iot_diag
* @brief  Register diag input function to replace uart input.
CNcomment:注册DIAG输入函数，代替默认从UART读取DIAG输入数据。CNend
*
* @par 描述:
*      Register diag input function to replace uart input.
CNcomment:注册DIAG输入函数，代替默认从UART读取DIAG输入数据。CNend
*
* @attention Should set suitable task size; input func should not continuous read data without break. otherwise,
a watchdog may happen.not support register HI_NULL when diag channel is already uart.
CNcomment:根据输入函数实现，设置合适的栈大小；输入函数不能持续
返回有效数据避免触发看门狗。当DIAG 通道已经是UART时，不支持注
册DIAG 输入函数为HI_NULL。CNend
* @param  diag_input_func      [IN] type #hi_diag_input_func，diag input function.
CNcomment:DIAG输入函数。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
*/
hi_u32 hi_diag_register_input_func(hi_diag_input_func diag_input_func);

/**
* @ingroup  iot_diag
* @brief  Register diag output function to replace uart output.
CNcomment:注册DIAG输出函数，代替默认从UART输出DIAG相关数据。CNend
*
* @par 描述:
*      Register diag output function to replace uart output.
CNcomment:注册DIAG输出函数，代替默认从UART输出DIAG相关数据。CNend
*
* @attention Should set suitable task size according to implementation of output func.
CNcomment:根据输出函数实现，设置合适的栈大小。CNend
* @param  diag_output_func      [IN] type #hi_diag_output_func，diag output function.
CNcomment:DIAG输出函数。CNend
*
* @retval None
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
*/
hi_void hi_diag_register_output_func(hi_diag_output_func diag_output_func);

/**
* @ingroup  iot_diag
* @brief  Set taks size of DIAG. CNcomment:设置DIAG相关任务栈大小。CNend
*
* @par 描述:
*         Set taks size of DIAG. CNcomment:设置DIAG相关任务栈大小。CNend
*
* @attention diag task stack size needs to be set before diag initialization.
CNcomment:diag任务栈大小需要在diag初始化之前设置。CNend
* @param  channel_task_size      [IN] type #hi_u16 channel task size,task size should not smaller than 0x600.
CNcomment:通道任务栈大小,任务栈大小不低于0x600。CNend
* @param  process_task_size      [IN] type #hi_u16 process task size,task size should not smaller than 0x800.
CNcomment:处理任务栈大小,任务栈大小不低于0x800。CNend
*
* @retval None
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
*/
hi_void hi_diag_set_task_size(hi_u16 channel_task_size, hi_u16 process_task_size);


typedef hi_u32 (*hi_diag_sys_msg_forward_func)(const hi_diag_layer_msg *diag_sys_msg, hi_u16 msg_level);
typedef hi_u32 (*hi_diag_layer_msg_forward_func)(hi_u32 msg_id, hi_u16 src_module_id, hi_u16 dst_module_id,
    const hi_void *packet, hi_u16 packet_size);
typedef hi_u32 (*hi_diag_usr_msg_forward_func)(const hi_diag_layer_msg* diag_usr_msg, hi_u16 msg_level);

/**
* @ingroup  iot_diag
* @brief  Register msg forward func. CNcomment:设置消息转发函数，替代默认从HSO输出。CNend
*
* @par 描述:
*        Register msg forward func. CNcomment:设置消息转发函数，替代默认从HSO输出。CNend
*
* @attention None.
* @param  diag_sys_msg_func      [IN] type #hi_diag_sys_msg_forward_func forward function of sys_msg.
CNcomment:sys_msg的转发函数。CNend
* @param  diag_layer_msg_func      [IN] type #hi_diag_layer_msg_forward_func forward function of layer_msg.
CNcomment:layder_msg的转发函数。CNend
* @param  diag_usr_msg_func      [IN] type #hi_diag_usr_msg_forward_func forward function of usr_msg.
CNcomment:usr_msg的转发函数。CNend
*
* @retval None
* @par 依赖:
*           @li hi_diag.h：Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
*/
hi_void hi_diag_register_msg_forward_func(hi_diag_sys_msg_forward_func diag_sys_msg_func,
    hi_diag_layer_msg_forward_func diag_layer_msg_func, hi_diag_usr_msg_forward_func diag_usr_msg_func);


#endif
