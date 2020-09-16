/**
* @file hi_crash.h
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

/** @defgroup iot_crash_info    Crash Log Management
 * @ingroup system
 */

#ifndef __HI_CRASH_H__
#define __HI_CRASH_H__
#include <hi_types.h>
#include <hi_mdm_types.h>
#include <hi_os_stat.h>
#include <hi_mem.h>
#include <hi_isr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @ingroup  iot_crash_info
*
* Version of the crash log module. CNcomment:死机存储模块版本号。CNend
*/
#define HI_SYSERR_VERSION 1

/**
* @ingroup  iot_crash_info
*
* Power down flag. CNcomment:下电标识。CNend
*/
#define HI_SYSERR_POWER_DOWN    0x646F776E /* 下电标志 */

/**
* @ingroup  iot_crash_info
*
* No power down flag. CNcomment:未下电标识。CNend
*/
#define HI_SYSERR_NO_POWER_DOWN 0xFFFFFFFF

/**
* @ingroup  iot_crash_info
*
* Length of the name string of an exception type. CNcomment:异常类型的名字字符串长度限制。CNend
*/
#define HI_SYSERR_EXC_TYPE_NAME_SIZE 8

/**
* @ingroup  iot_crash_info
*
* Length of the task name string of a logged exception.
CNcomment:异常存储的任务名字字符串长度限制。CNend
*/
#define HI_SYSERR_EXC_TASK_NAME_SIZE 8

/**
* @ingroup  iot_crash_info
*
* Depth of the scheduling track before an exception. CNcomment:异常前调度轨迹深度。CNend
*/
#define HI_SYSERR_EXC_TRACE_DEPTH 10

/**
* @ingroup  iot_crash_info
*
* Exception stack information depth (unit: word). CNcomment:异常栈信息深度(word为单位)CNend
*/
#define HI_SYSERR_ESP_DATA_MAX_NUM 36

/**
* @ingroup  iot_crash_info
*
* Extended depth of the exception stack SP to the stack bottom (unit: word).
CNcomment:异常栈sp向栈底扩展深度(word为单位)CNend
*/
#define HI_SYSERR_ESP_PRE_DATA_MAX_NUM 8

/**
* @ingroup  iot_crash_info
*
* Version of the running kernel when the exception occurs. CNcomment:异常时对应的运行版本的版本号CNend
*/
#define HI_SYSERR_EXC_KERNEL_VER_LEN_MAX 60
#if !defined(PRODUCT_CFG_HSO)
#if (HI_SYSERR_EXC_KERNEL_VER_LEN_MAX < HI_BUILD_VER_PRODUCT_LEN_MAX)
#error "HI_SYSERR_EXC_KERNEL_VER_LEN_MAX != HI_BUILD_VER_PRODUCT_LEN_MAX"
#endif
#endif

/**
* @ingroup iot_crash_info
* Crash type eid.CNcomment:死机类型eid.CNend
*/
typedef enum {
    HI_SYSERR_EID_POWER_DOWN,           /**< Power Down or first Power on.CNcomment:下电重启或首次上电.CNend */
    HI_SYSERR_EID_FAULT_IN_TASK,        /**< fault in task.CNcomment:任务中死机.CNend */
    HI_SYSERR_EID_FAULT_IN_ISR,         /**< fault in isr.CNcomment:中断中死机.CNend */
    HI_SYSERR_EID_WATCHDOG_TSK,         /**< watchdog reset(in task).CNcomment:看门狗死机(任务中).CNend */
    HI_SYSERR_EID_WATCHDOG_ISR,         /**< watchdog reset(in isr).CNcomment:看门狗死机(中断中).CNend */
    HI_SYSERR_EID_SYS_SOFT_REBOOT,      /**< system soft reboot.CNcomment:系统软复位.CNend */
    HI_SYSERR_EID_RESERVE,
    HI_SYSERR_EID_MAX = 0xFF,
} hi_syserr_eid;

/* cpu registers */
typedef struct {
    hi_u32 mepc;
    hi_u32 ra;
    hi_u32 sp;
    hi_u32 gp;
    hi_u32 tp;
    hi_u32 t0;
    hi_u32 t1;
    hi_u32 t2;
    hi_u32 s0;
    hi_u32 s1;
    hi_u32 a0;
    hi_u32 a1;
    hi_u32 a2;
    hi_u32 a3;
    hi_u32 a4;
    hi_u32 a5;
    hi_u32 a6;
    hi_u32 a7;
    hi_u32 s2;
    hi_u32 s3;
    hi_u32 s4;
    hi_u32 s5;
    hi_u32 s6;
    hi_u32 s7;
    hi_u32 s8;
    hi_u32 s9;
    hi_u32 s10;
    hi_u32 s11;
    hi_u32 t3;
    hi_u32 t4;
    hi_u32 t5;
    hi_u32 t6;
} syserr_reg_info;

/**
* @ingroup iot_crash_info
* Task information.CNcomment:任务信息.CNend
*/
typedef struct {
    hi_char name[HI_SYSERR_EXC_TASK_NAME_SIZE];
    hi_u32 id;  /**< task id.CNcomment:任务ID.CNend */
    hi_u32 status;  /**< task status.CNcomment:任务运行状态.CNend */
    hi_u8 reserve[3];                       /* reserve's size 3 */
    hi_u8 stack_data_index; /**< extended stack information index from stack bottom.CNcomment:
                                向栈底扩展的栈信息个数.CNend */
    hi_u16 stack_peak;      /**< stack peak.CNcomment:栈使用峰值.CNend */
    hi_u16 stack_size;      /**< stack size.CNcomment:任务栈大小.CNend */
    hi_u32 sp;              /**< stack point.CNcomment:栈指针.CNend */
    hi_u32 stack[2];        /**< stack[2] is stack top and end address.CNcomment:栈顶和栈底地址.CNend */
    hi_u32 real_sp;         /**< real stack point.CNcomment:真实栈指针.CNend */
    hi_u32 stack_pre_data[HI_SYSERR_ESP_PRE_DATA_MAX_NUM]; /**< extended stack information from stack bottom.CNcomment:
                                                               向栈底扩展的栈信息，用于回退栈类错误参考.CNend */
    hi_u32 stack_data[HI_SYSERR_ESP_DATA_MAX_NUM];         /**< stack data.CNcomment:栈数据.CNend */
    hi_u32 overflow_flag;                   /**< stack overflow flag.CNcomment:栈溢出标识.CNend */
} syserr_task_info;

/**
* @ingroup iot_crash_info
* OS information.CNcomment:操作系统信息.CNend
*/
typedef struct {
    hi_os_resource_use_stat usage; /**< os resource used count.CNcomment:系统资源使用个数.CNend */
    syserr_task_info task;         /**< task information.CNcomment:任务信息.CNend */
    hi_mem_pool_crash_info mem;    /**< memory pool information.CNcomment:动态内存池信息.CNend */
} syserr_os_info;

/**
* @ingroup iot_crash_info
* Basic information.CNcomment:基础信息.CNend
*/
typedef struct {
    hi_u16 log_ver;                /**< log version.CNcomment:Log版本号.CNend */
    hi_u16 eid;                    /**< reset reason id.CNcomment:复位类型.CNend */
    hi_u32 rid;                    /**< exception id.CNcomment:异常类型.CNend */
    hi_u32 now_tsec;               /**< current time relative start time.CNcomment:当前运行相对启动时间.CNend */
    hi_u32 crash_tsec;             /**< crash time relative start time.CNcomment:异常时相对当次启动时间.CNend */
    hi_u32 boot_ver;
    hi_char kernel_ver[HI_SYSERR_EXC_KERNEL_VER_LEN_MAX]; /**< kernel version.CNcomment:异常时运行版本的版本号.CNend */
    hi_char type_name[HI_SYSERR_EXC_TYPE_NAME_SIZE];      /**< reset reason name.CNcomment:类型名:与eid对应.CNend */
} syserr_basic_info;

/**
* @ingroup iot_crash_info
* Watchdog information.CNcomment:看门狗信息.CNend
*/
typedef struct {
    hi_u32 wdg_reset_pc;    /**< watchdog reset reserved PC.CNcomment:看门狗复位PC.CNend */
    hi_u32 time_ms : 31;    /**< watchdog timeout.CNcomment:看门狗超时时间.CNend */
    hi_u32 enable : 1;      /**< watchdog enable.CNcomment:看门狗使能状态.CNend */
} syserr_wdg_info;

/**
* @ingroup iot_crash_info
* Flash protect information.CNcomment:Flash保护信息.CNend
*/
typedef struct {
    hi_u32 current_block : 13;  /**< flash protect current block.CNcomment:Flash保护当前block.CNend */
    hi_u32 reserve : 18;
    hi_u32 enable : 1;          /**< flash protect enable.CNcomment:Flash保护使能状态.CNend */
    hi_u32 status_reg;          /**< flash protect status.CNcomment:Flash保护状态寄存器.CNend */
} syserr_fp_info;

/**
* @ingroup iot_crash_info
* Track item information.CNcomment:调度项信息.CNend
*/
typedef struct {
    hi_u16 type;      /**< track type.CNcomment:调度类型.CNend */
    hi_u16 id;        /**< track ID.CNcomment:调度项id.CNend */
    hi_u32 data;      /**< track userdata.CNcomment:调度用户数据.CNend */
    hi_u32 entry;     /**< track Hook function Entry.CNcomment:调度回调勾子函数.CNend */
    hi_u32 timestamp; /**< The low 32 bit of the current time,us.CNcomment:调度时间戳.CNend */
} syserr_track_item;

/**
* @ingroup iot_crash_info
* Track information.CNcomment:调度轨迹信息.CNend
*/
typedef struct {
    hi_u16 current_item;    /**< current track item.CNcomment:当前调度项.CNend */
    hi_u16 item_cnt;        /**< track count of track information.CNcomment:调度项记录个数.CNend */
    syserr_track_item item[HI_SYSERR_EXC_TRACE_DEPTH];  /**< track item data.CNcomment:调度项数据.CNend */
} syserr_track_info;

/**
* @ingroup iot_crash_info
* CPU csr registers information.CNcomment:CPU CSR寄存器信息.CNend
*/
typedef struct {
    hi_u32 mstatus;     /**< CPU mstatus register value.CNcomment:CPU mstatus寄存器值.CNend */
    hi_u32 mtval;       /**< CPU mtval register value.CNcomment:CPU mtval寄存器值.CNend */
    hi_u32 mcause;      /**< CPU mcause register value.CNcomment:CPU mcause寄存器值.CNend */
    hi_u32 ccause;      /**< CPU ccause register value.CNcomment:CPU ccause寄存器值.CNend */
    hi_u16 cur_task_id; /**< current task id.CNcomment:当前任务ID.CNend */
} syserr_core_info;

/**
* @ingroup iot_crash_info
* Saved exception information.CNcomment:异常时对应存储信息。CNend
*/
typedef struct {
    hi_u32 sig_s;       /**< header flag of crash information.CNcomment:异常信息前标识.CNend */
    hi_u32 power_down : 1; /**< power down flag.CNcomment:下电标识.CNend */
    hi_u32 crc_usable : 1; /**< CRC check enable of crash information.CNcomment:死机信息CRC校验使能.CNend */
    hi_u32 info_len : 14;  /**< crash information length.CNcomment:死机信息长度.CNend */
    hi_u32 crc_val : 16;   /**< CRC16 calue of crash information.CNcomment:CRC16校验值.CNend */

    syserr_basic_info basic_info; /**< basic data of crash information.CNcomment:死机基础信息.CNend */
    syserr_os_info os_info;       /**< OS data of crash information.CNcomment:死机OS信息.CNend */
    syserr_reg_info reg_info;     /**< CPU registers of crash information.CNcomment:死机CPU寄存器信息.CNend */
    syserr_wdg_info wdg_info;     /**< watchdog data of crash information.CNcomment:死机看门狗.CNend */
    syserr_fp_info protect_info;  /**< flash protect data of crash information.CNcomment:死机Flash保护信息.CNend */
    syserr_track_info track_info; /**< track data of crash information.CNcomment:死机调度信息.CNend */
    syserr_core_info core_info;   /**< CPU CSR registers of crash information.CNcomment:死机CPU状态寄存器信息.CNend */
    hi_u32 sig_e;                 /**< end flag of crash information.CNcomment:异常信息后标识.CNend */
} hi_syserr_info;

typedef hi_void (*hi_syserr_exc_callback)(hi_void);

/**
* @ingroup  iot_crash_info
* @brief Initializes the exception information module. CNcomment:异常信息模块初始化。CNend
*
* @par 描述:
*           Initializes the exception information module. CNcomment:异常信息模块初始化。CNend
*
* @attention s API can be called only once. Repeated initialization and multi-task calling are not supported.
CNcomment:仅初始化一次，未考虑多次初始化及多任务调用场景。CNend
* @param  None
*
* @retval None
* @par 依赖:
*           @li hi_crash.h：Describes Crash log APIs. CNcomment:文件用于描述死机相关接口。CNend
* @see None
*/
hi_void hi_syserr_init(hi_void);

/**
* @ingroup  iot_crash_info
* @brief Obtains the system exception information pointer (in the memory).
CNcomment:获取系统异常信息指针(内存中)。CNend
*
* @par 描述:
*           Obtains the system exception information pointer (in the memory).
CNcomment:获取系统异常信息指针(内存中)。CNend
*
* @attention None
* @param  None
*
* @retval Pointer to the hi_syserr_info structure. CNcomment:hi_syserr_info结构体指针。CNend
* @par 依赖:
*           @li hi_crash.h：Describes Crash log APIs. CNcomment:文件用于描述死机相关接口。CNend
* @see None
*/
hi_syserr_info *hi_syserr_ptr(hi_void);

/**
* @ingroup  iot_crash_info
* @brief Obtains the system exception information pointer (in the flash).
CNcomment:获取系统异常信息指针(flash中)。CNend
*
* @par 描述:
*           Obtains the system exception information pointer (in the flash).
CNcomment:获取系统异常信息指针(flash中)。CNend
*
* @attention None
* @param  info          [OUT] type #hi_syserr_info* ，Pointer to the hi_syserr_info structure.
CNcomment:异常信息读出后存放地址。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other values    Failure. For details, see hi_errno.h.
* @par 依赖:
*           @li hi_crash.h：Describes Crash log APIs. CNcomment:文件用于描述死机相关接口。CNend
* @see None
*/
hi_u32 hi_syserr_get(hi_syserr_info *info);

/**
* @ingroup  iot_crash_info
* @brief Register exception handling callback. CNcomment:注册异常死机处理回调函数。CNend
*
* @par 描述:
*           Register exception handling callback. CNcomment:注册异常死机处理回调函数。CNend
*
* @attention None
* @param  func          [IN] type #hi_syserr_exc_callback ，Callback function of exception happens
CNcoment:异常回调函数。CNend
*
* @retval None
* @par 依赖:
*           @li hi_crash.h：Describes Crash log APIs. CNcomment:文件用于描述死机相关接口。CNend
* @see None
*/
hi_void hi_syserr_exc_register(hi_syserr_exc_callback func);

/**
* @ingroup  iot_crash_info
* @brief Retains the PC pointer when the watchdog reset in interrupt. CNcomment:中断中看门狗复位时记录PC值。CNend
*
* @par 描述:
*        Retains the PC pointer when the watchdog reset in interrupt.
CNcomment:中断中看门狗复位时记录PC值，打开此功能后看门狗复位有复位不完全的风险，量产版本请务必关闭。CNend
*
* @attention None
* @param  enable          [IN] type #hi_bool ，Enable/Disable retains reset PC pointer function.
CNcoment:打开/关闭记录中断中看门狗复位PC值功能。CNend
*
* @retval None
* @par 依赖:
*           @li hi_crash.h：Describes Crash log APIs. CNcomment:文件用于描述死机相关接口。CNend
* @see None
*/
hi_void hi_syserr_watchdog_debug(hi_bool enable);

/**
* @ingroup  iot_crash_info
* @brief Whether reset after watchdog in task, default yes. CNcomment: 任务中触发看门狗时是否主动复位，默认复位。CNend
*
* @par 描述:
*        Whether reset after wdt in task, default yes.
CNcomment: 任务中触发看门狗时是否主动复位，默认复位。CNend
*
* @attention None
* @param  reset          [IN] type #hi_bool ，Reset/Not reset after watchdog in task.
CNcoment:任务中触发看门狗时是否主动复位。CNend
*
* @retval None
* @par 依赖:
*           @li hi_crash.h：Describes Crash log APIs. CNcomment:文件用于描述死机相关接口。CNend
* @see None
*/
hi_void hi_syserr_reset_after_wdg(hi_bool reset);

/**
* @ingroup  iot_crash_info
* @brief Whether record crash info in flash, default no. CNcomment: 是否记录宕机信息到FLASH，默认不记录。CNend
*
* @par 描述:
*        Whether record crash info in flash, default no.
CNcomment: 是否记录宕机信息到FLASH，默认不记录。CNend
*
* @attention None
* @param  record          [IN] type #hi_bool ，Record/Not record crash info in flash.
CNcoment:宕机时是否记录宕机信息到FLASH。CNend
*
* @retval None
* @par 依赖:
*           @li hi_crash.h：Describes Crash log APIs. CNcomment:文件用于描述死机相关接口。CNend
* @see None
*/
hi_void hi_syserr_record_crash_info(hi_bool record);

/**
* @ingroup  iot_crash_info
* @brief Retains the latest reboot reason. CNcomment:获取最近一次重启原因。CNend
*
* @par 描述:
*        Retains the latest reboot reason.
CNcomment:获取最近一次重启原因。CNend
*
* @attention None
* @param  err_id         [OUT] type #hi_u16 * , error id, see hi_syserr_eid.
power_down or hard rebootwould always be 0.
CNcomment:重启原因ID，取值含义参见hi_syserr_eid，掉电重启和硬复位值均为0。CNend
* @param  reboot_cause   [OUT] type #hi_u32* , when err_id is soft reboot, see hi_sys_reboot_cause;
when err_id is fault in task or isr, reboot_cause would be mcause of cpu regs. Otherwise, reboot_cause would be 0.
CNcomment:当重启原因ID 为软复位时，取值含义见hi_sys_reboot_cause；
当为任务或中断中异常时，取值为cpu mcause寄存器，否则为0。
CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #Other          Failure. See hi_errno.h for details.
* @par 依赖:
*           @li hi_crash.h：Describes Crash log APIs. CNcomment:文件用于描述死机相关接口。CNend
* @see None
*/
hi_u32 hi_syserr_get_reboot_reason(hi_u16 *err_id, hi_u32 *reboot_cause);


#ifdef __cplusplus
}
#endif

#endif /* __HI_CRASH_H__ */
