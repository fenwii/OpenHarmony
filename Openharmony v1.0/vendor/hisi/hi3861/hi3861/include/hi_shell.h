/**
 * @file hi_shell.h
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

/** @defgroup iot_shell Shell
 *  @ingroup dfx
 */

#ifndef __HI_SHELL_H__
#define __HI_SHELL_H__

#include <hi_types.h>
#include <hi_uart.h>

typedef  hi_s32 (*hi_shell_input_func)(hi_u8 *data, hi_u32 data_len);
typedef  hi_s32 (*hi_shell_output_func)(const hi_u8 *data, hi_u32 data_len);
typedef hi_u32 (*hi_shell_cmd_callback_func)(hi_u32 argc, hi_char **argv);
/**
* @ingroup  iot_shell
* @brief  Shell initialization function.
CNcomment:SHELL初始化函数。CNend
*
* @par 描述:
*      Shell initialization function.
CNcomment:SHELL初始化函数。CNend
*
* @attention None.
* @param None.
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_shell.h：Describes SHELL APIs.
CNcomment:文件用于描述SHELL相关接口。CNend
*/
hi_u32 hi_shell_init(hi_void);

/**
* @ingroup  iot_shell
* @brief  Set taks size of SHELL. CNcomment:设置SHELL相关任务栈大小。CNend
*
* @par 描述:
*         Set taks size of SHELL. CNcomment:设置SHELL相关任务栈大小。CNend
*
* @attention shell task stack size needs to be set before shell initialization.
CNcomment:shell任务栈大小需要在shell初始化之前设置。CNend
* @param  channel_task_size      [IN] type #hi_u16 channel task size,task size should not smaller than 0x600.
CNcomment:通道任务栈大小,任务栈大小不低于0x600。CNend
* @param  process_task_size      [IN] type #hi_u16 process task size,task size should not smaller than 0xc00.
CNcomment:处理任务栈大小,任务栈大小不低于0xc00。CNend
*
* @retval None
* @par 依赖:
*           @li hi_shell.h：Describes SHELL APIs.
CNcomment:文件用于描述SHELL相关接口。CNend
*/
hi_void hi_shell_set_task_size(hi_u16 channel_task_size, hi_u16 process_task_size);

/**
* @ingroup  iot_shell
* @brief  Get shell registered output function.
CNcomment:获取SHELL注册的输出函数。CNend
*
* @par 描述:
*      Get shell registered output function.
CNcomment:获取SHELL注册的输出函数。CNend
*
* @attention None.
* @param  None.
*
* @retval #g_shell_output_func   Shell output function.
* @par 依赖:
*           @li hi_shell.h：Describes SHELL APIs.
CNcomment:文件用于描述SHELL相关接口。CNend
*/
hi_shell_output_func hi_shell_get_register_output_func(hi_void);

/**
* @ingroup  iot_shell
* @brief  Register shell input function to replace uart input.
CNcomment:注册SHELL输入函数，代替默认从UART读取SHELL输入数据。CNend
*
* @par 描述:
*      Register shell input function to replace uart input.
CNcomment:注册SHELL输入函数，代替默认从UART读取SHELL输入数据。CNend
*
* @attention Should set suitable task size; input func should not continuous read data without break. otherwise,
a watchdog may happen.not support register HI_NULL when shell channel is already uart.
CNcomment:根据输入函数实现，设置合适的栈大小；输入函数不能持续
返回有效数据避免触发看门狗。当SHELL 通道已经是UART时，不支持注
册SHELL 输入函数为HI_NULL。CNend
* @param  shell_input_func      [IN] type #hi_shell_input_func，shell input function.
CNcomment:SHELL输入函数。CNend
*
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_shell.h：Describes SHELL APIs.
CNcomment:文件用于描述SHELL相关接口。CNend
*/
hi_u32 hi_shell_register_input_func(hi_shell_input_func shell_input_func);

/**
* @ingroup  iot_shell
* @brief  Register shell output function to replace uart output.
CNcomment:注册SHELL输出函数，代替默认从UART输出SHELL相关数据。CNend
*
* @par 描述:
*      Register shell output function to replace uart output.
CNcomment:注册SHELL输出函数，代替默认从UART输出SHELL相关数据。CNend
*
* @attention Should set suitable task size according to implementation of output func.
CNcomment:根据输出函数实现，设置合适的栈大小。CNend
* @param  shell_output_func      [IN] type #hi_shell_output_func，shell output function.
CNcomment:SHELL输出函数。CNend
*
* @retval None
* @par 依赖:
*           @li hi_shell.h：Describes SHELL APIs.
CNcomment:文件用于描述SHELL相关接口。CNend
*/
hi_void hi_shell_register_output_func(hi_shell_output_func shell_output_func);

/**
* @ingroup  iot_shell
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
*           @li hi_diag.h：Describes SHELL APIs.
CNcomment:文件用于描述SHELL相关接口。CNend
*/
hi_void hi_shell_set_check_uart_busy(hi_bool enable);

/**
* @ingroup  iot_shell
* @brief  Registration shell command processing function.CNcomment:注册shell命令处理函数。CNend
*
* @par 描述:Registration shell command processing function.CNcomment:注册shell命令处理函数。CNend
*
* @attention：Only the first 32 command line arguments are recognized, and the remaining parts are not recognized.
CNcomment:仅识别前32个shell命令行参数，32个之后的命令行参数将不被识别。CNend
* @param  cmd_key       [IN] type #hi_char*，Register command name, the length must be less than 16 bytes.
CNcomment:shell命令名称，命令长度不能大于16字节。CNend
* @param  cmd_callback  [IN] type #hi_shell_cmd_callback_func，Shell command processing function.
CNcomment:shell命令处理函数。CNend
*
* @retval #HI_ERR_SUCCESS         Success.
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_shell.h：Describes SHELL APIs. CNcomment:文件用于描述SHELL相关接口。CNend
* @see  None
*/
hi_u32 hi_shell_cmd_register(hi_char *cmd_key, hi_shell_cmd_callback_func cmd_callback);

#endif
