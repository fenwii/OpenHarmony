/**
* @file hi_at.h
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

/** @defgroup iot_at  AT Command
 *  @ingroup dfx
 */
#ifndef __HI_AT_H__
#define __HI_AT_H__
#include <hi_types.h>

typedef hi_u32 (*at_call_back_func)(hi_s32 argc, const hi_char **argv);

typedef struct {
    hi_char *at_cmd_name;
    hi_s8   at_cmd_len;
    at_call_back_func at_test_cmd;
    at_call_back_func at_query_cmd;
    at_call_back_func at_setup_cmd;
    at_call_back_func at_exe_cmd;
} at_cmd_func;

typedef enum {
    AT_IDLE,
    AT_CMD_PROCESS,
    AT_DATA_RECVING,
    AT_DATA_SENDING,
    AT_TRANSPARENT,
} at_state_machine;

typedef struct {
    at_state_machine at_state;
    hi_u16 send_len;
    hi_u16 trans_len;
    hi_bool is_first_recv_data;
    hi_bool is_first_over_data;
    hi_u16 is_recv_end_char_flag;
} at_cmd_ctrl;

typedef  hi_s32 (*hi_at_input_func)(hi_u8 *data, hi_u32 data_len);
typedef  hi_s32 (*hi_at_output_func)(const hi_u8 *data, hi_u32 data_len);

/**
* @ingroup  iot_at
* @brief  Get at registered output function.
CNcomment:获取AT注册的输出函数。CNend
*
* @par 描述:
*      Get at registered output function.
CNcomment:获取AT注册的输出函数。CNend
*
* @attention None.
* @param  None.
*
* @retval #g_at_output_func   At output function.
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see  None
*/
hi_at_output_func hi_at_get_register_output_func(hi_void);

/**
* @ingroup  iot_at
* @brief  Registration command processing function.CNcomment:注册命令处理函数。CNend
*
* @par 描述:
*           @li This command is invoked during initialization and cannot be invoked by multiple tasks.
CNcomment:在初始化阶段调用, 不支持多任务调用。CNend
*           @li A maximum of 20 different command tables can be registered.
CNcomment:最多能注册20个不同的命令表。CNend
*
* @attention None
* @param  cmd_tbl    [IN] type #at_cmd_func*，Command table, which must be declared as a constant array and
*                    transferred to this parameter.CNcomment:命令表，
必须申明为常量数组传给该参数。CNend
* @param  cmd_num    [IN] type #hi_u16，The number of commands. The value must be equal to the actual number of
*                    commands in the command table. If it is less than the actual command number, only the number of
*                    commands equal to this value is registered. If it is greater than the actual command number,
*                    the command table will be accessed out of bounds.
CNcomment:命令表中命令的个数，该值必须等于命令表中实际的命令个数，如果小于实际命令数，则只注册等于该值的命令个数，
          大于实际命令个数将会导致越界访问命令表。CNend
*
* @retval #HI_ERR_SUCCESS         Success.
* @retval #Other     Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see  None
*/
hi_u32 hi_at_register_cmd(HI_CONST at_cmd_func *cmd_tbl, hi_u16 cmd_num);

/**
* @ingroup  iot_at
* @brief  Register system AT command. CNcomment:注册系统AT命令。CNend
*
* @par 描述:
*           Register system AT command. CNcomment:该函数用于注册系统AT命令。CNend
* @param None
* @retval None
*
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see  None
*/
hi_void hi_at_sys_cmd_register(hi_void);

/**
* @ingroup  iot_at
* @brief  Formats the data and outputs it to AT command terminal.
CNcomment:将数据格式化输出到AT命令终端。CNend
*
* @par 描述: Formats the data and outputs it to AT command terminal.
CNcomment:将数据格式化输出到AT命令终端。CNend
* @attention None
*
* @param fmt      [IN]  type #const hi_char *。 Formatting control string.CNcomment:格式化控制字符串。CNend
* @param ...      [IN]  Optional parameter CNcomment:可选参数。CNend
*
* @retval #>=0 Return the number of bytes stored in terminal, not counting the terminating null character.
CNcomment:返回输出到终端的字节数，不包括结束符CNend
* @retval #-1 Failure
*
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see None
*/
hi_s32 hi_at_printf(const hi_char *fmt, ...);

/**
* @ingroup  iot_at
* @brief  Initializes the AT task. CNcomment:AT命令任务初始化。CNend
*
* @par 描述:
*           Initializes the AT task. CNcomment:该函数用于初始化AT命令任务。CNend
* @param None
* @retval #HI_ERR_SUCCESS         Success.
* @retval #Other     Failure. For details, see hi_errno.h.
*
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see  None
*/
hi_u32 hi_at_init(hi_void);

/**
* @ingroup  iot_at
* @brief  Set taks size of AT. CNcomment:设置AT相关任务栈大小。CNend
*
* @par 描述:
*         Set taks size of AT. CNcomment:设置AT相关任务栈大小。CNend
*
* @attention AT task stack size needs to be set before AT initialization.
CNcomment:AT任务栈大小需要在AT初始化之前设置。CNend
* @param  channel_task_size      [IN] type #hi_u16 channel task size, task size should not smaller than 0x600.
CNcomment:通道任务栈大小, 任务栈大小不低于0x600。Nend
* @param  process_task_size      [IN] type #hi_u16 process task size, task size should not smaller than 0xc00.
CNcomment:处理任务栈大小, 任务栈大小不低于0xc00。CNend
*
* @retval None
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see  None
*/
hi_void hi_at_set_task_size(hi_u16 channel_task_size, hi_u16 process_task_size);

/**
* @ingroup  iot_at
* @brief  Set whether to check the UART busy status when low power vote.
CNcomment:设置低功耗投票时是否检查UART busy状态。CNend
*
* @par 描述:
*      Set whether to check the UART busy status when low power vote.
CNcomment:设置低功耗投票时是否检查UART busy状态。CNend
*
* @attention UART busy status is checked by default.
CNcomment:默认低功耗睡眠投票时检查UART busy状态。CNend
* @param  enable         [IN] type #hi_bool，enable status. CNcomment:设置是否检查UART busy状态。CNend
*
* @retval None
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see  None
*/
hi_void hi_at_set_check_uart_busy(hi_bool enable);

/**
* @ingroup  iot_at
* @brief  Register at input function to replace uart input.
CNcomment:注册AT输入函数，代替默认从UART读取AT输入数据。CNend
*
* @par 描述:
*      Register at input function to replace uart input.
CNcomment:注册AT输入函数，代替默认从UART读取AT输入数据。CNend
*
* @attention Should set suitable task size; input func should not continuous read data without break. otherwise,
a watchdog may happen.not support register HI_NULL when at channel is already uart.
CNcomment:根据输入函数实现，设置合适的栈大小；输入函数不能持续
返回有效数据避免触发看门狗。当AT通道已经是UART时，不支持注
册AT 输入函数为HI_NULL。CNend
* @param  at_input_func      [IN] type #hi_at_input_func，at input funciton.
CNcomment:AT输入函数。CNend
* @retval #0                 Success.
* @retval #Other             Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see  None
*/
hi_u32 hi_at_register_input_func(hi_at_input_func at_input_func);

/**
* @ingroup  iot_at
* @brief  Register at output function to replace uart output.
CNcomment:注册AT命令输出函数，代替默认从UART输出AT相关数据。CNend
*
* @par 描述:
*      Register at output function to replace uart output.
CNcomment:注册AT命令输出函数，代替默认从UART输出AT相关数据。CNend
*
* @attention Should set suitable task size according to implementation of output func.
CNcomment:根据输出函数实现，设置合适的栈大小。CNend
* @param  at_output_func      [IN] type #hi_at_output_func，at output function.
CNcomment:AT输出函数。CNend
* @retval None
* @par 依赖:
*           @li hi_at.h：Describes at command APIs. CNcomment:文件用于描述at指令相关接口。CNend
* @see  None
*/
hi_void hi_at_register_output_func(hi_at_output_func at_output_func);

#endif
