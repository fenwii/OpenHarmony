/**
 * @file hi_cpu.h
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
 * @defgroup iot_cpu CPU
 * @ingroup osa
 */

#ifndef __HI_CPU_H__
#define __HI_CPU_H__
#include <hi_types.h>

#define LOAD_SLEEP_TIME_DEFAULT   30

/**
 * @ingroup iot_cpu
 *
 * CPU usage information structure. CNcomment:cpu使用情况信息结构 CNend
 */
typedef struct {
    hi_u8 b_valid : 1;    /**< Whether the information is valid. HI_TRUE: yes; HI_FALSE: no.
                             CNcomment:表示该条信息是否为有效信息，HI_TRUE:该条信息有效
                             HI_FALSE:该条信息无效 CNend */
    hi_u8 b_task : 1;     /**< Whether the message is a task or an interrupt. HI_TRUE: task; HI_FALSE: interrupt.
                             CNcomment:表示该条信息是任务或中断，HI_TRUE:任务 HI_FALSE:中断 CNend */
    hi_u8 pad0 : 6;       /**< Reserved. CNcomment:保留 CNend */
    hi_u8 id;           /**< Task ID/Interrupt number. CNcomment:当该条信息表示任务时为任务ID,
                           当该条信息为中断信息时表示中断号 CNend */
    hi_u16 pad1;        /**< Reserved. CNcomment:保留 CNend */
    hi_u32 permillage;  /**< CPU usage (per mil). CNcomment:cpu占用率，千分比 CNend */
    hi_u64 cpu_time;    /**< CPU usage time (unit: cputick), where, cputick x 160000000 = 1s.
                           CNcomment:cpu占用时间(单位:cputick),160000000个cputick等于1秒 CNend */
} hi_cpup_item;


typedef enum {
    HI_CPU_CLK_80M,  /**< cpu clock:80M. CNcomment:CPU工作频率:80M CNend */
    HI_CPU_CLK_120M, /**< cpu clock:120M. CNcomment:CPU工作频率:120M CNend */
    HI_CPU_CLK_160M, /**< cpu clock:160M. CNcomment:CPU工作频率:160M CNend */
    HI_CPU_CLK_MAX   /**< Maximum cpu clock, which cannot be used. CNcomment:CPU最大工作频率，
                         不可使用CNend */
} hi_cpu_clk;

/**
* @ingroup  iot_cpu
* @brief  Obtains the CPU usage. CNcomment:获取CPU使用情况。CNend
*
* @par 描述:
*         Obtains the CPU usage between the initialization of the CPU usage module is started or
*         the CPU usage statistics are reset to each task/interrupt.
CNcomment:获取cpu占用率模块初始化开始或cpu占用率统计信息重置开始统计到个各任务(中断)
CPU占用情况。CNend
*
* @attention
* @li A task/interrupt not scheduled after the CPU usage module is initialized or
*     the CPU usage statistics are reset is excluded.
CNcomment:cpu占用率模块初始化或cpu占用率统计信息重置之后没有调度到的任务或中断
不会被统计。CNend
*
* @param array_count [IN] type #hi_u32 Number of CPU usage records that can be stored
*                         in the space corresponding to cpup_items. CNcomment:表示p_cpup_items对应的空间可以
存储多少条cpu使用情况信息。CNend
* @param p_cpup_items [OUT] type #hi_cpup_item* CPU usage information space, applied by the caller.
CNcomment:cpu使用情况信息空间，由调用者申请。CNend
*
* @retval #0   Success.
* @retval #Other    Failure. For details, see hi_errno.h.
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see  None
*/
hi_u32 hi_cpup_get_usage(hi_u32 array_count, hi_cpup_item *p_cpup_items);

/**
* @ingroup  iot_cpu
* @brief  Resets CPU usage statistics. CNcomment:重置cpu使用情况信息。CNend
*
* @param None
*
* @retval #None
* @par 描述:
*         Resets CPU usage statistics. After the reset, the CPU usage statistics of all tasks and interrupts are
*         cleared. CNcomment:重置cpu使用情况信息，重置后所有任务和中断的cpu占用率清0。CNend
*
* @attention None
*
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see None
*/
hi_void hi_cpup_reset_usage(hi_void);

/**
* @ingroup  iot_cpu
* @brief  Set CPU clock. CNcomment:设置CPU的工作频率。CNend
*
* @par 描述:
*         Set CPU clock, such as 80M/120M/160M.
*         CNcomment:设置CPU的工作频率，如80M/120M/160M。CNend
*
* @attention Default CPU clock is 160M, if change CPU clock, Shoud config it
both in System Startup and DeepSleep Wakeup stage.CNcomment:CPU默认工作频率为160M，
如果改变CPU的工作频率，需要在系统启动和深睡唤醒阶段均进行配置。CNend
* @param  clk        [IN] type #hi_cpu_clk，cpu clk. CNcomment:CPU工作频率。CNend
*
* @retval #HI_ERR_SUCCESS  Success.
* @retval #HI_ERR_CPU_CLK_INVALID_PARAM  invalid clk. CNcomment:工作频率无效。CNend
*
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see None
*/
hi_u32 hi_cpu_set_clk(hi_cpu_clk clk);

/**
* @ingroup  iot_cpu
* @brief  Get CPU clock. CNcomment:获取CPU的工作频率。CNend
*
* @par 描述:
*         Get CPU clock, such as 80M/120M/160M.
*         CNcomment:获取CPU的工作频率，如80M/120M/160M。CNend
*
* @attention None
* @param  None
*
* @retval #hi_cpu_clk  cpu clk.
*
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see None
*/
hi_cpu_clk hi_cpu_get_clk(hi_void);

/**
* @ingroup  iot_cpu
* @brief  check cpu load percent and sleep. CNcomment:检查idle任务cpu占有率，
如果小于门限则对当前任务进行睡眠。CNend
*
* @par 描述:
*         check cpu load percent of idle task, if smaller than the threshold
(5%), Then sleep. CNcomment:检查idle任务cpu占有率，如果小于门限(5%)则对当前任务
进行睡眠。CNend
*
* @attention None
*
* @param  task_id  [IN] type #hi_u32，current task ID.
CNcomment:当前固定填写当前任务ID。CNend
* @param  ms       [IN] type #hi_u32，sleep time:当前任务睡眠时间。CNend
*
* @retval None
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see None
*/
hi_void hi_cpup_load_check_proc(hi_u32 task_id, hi_u32 ms);

/**
* @ingroup  iot_cpu
* @brief  Enable Dcache. CNcomment:使能DCache。CNend
*
*
* @par 描述:
*         Enable Dcache，system default Enable Dcache after startup.
CNcomment:使能DCache，系统启动默认使能。CNend
*
* @attention None
*
* @param None
*
* @retval #None
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see None
*/
hi_void hi_cache_enable(hi_void);

/**
* @ingroup  iot_cpu
* @brief  Disable Dcache. CNcomment:禁用DCache。CNend
*
* @par 描述:
*         Disable Dcache. CNcomment:禁用DCache。CNend
*
* @attention:
*         flush cache before disable. CNcomment:禁用Dcache前需要刷Cache。CNend
*
* @param None
*
* @retval #None
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see None
*/
hi_void hi_cache_disable(hi_void);

/**
* @ingroup  iot_cpu
* @brief  Flush Dcache. CNcomment:Flush DCache。CNend
*
* @par 描述:
*         Flush Dcache, synchronize Dcache and memory.
CNcomment:刷新DCache，维持DCache和memory同步。CNend
*
* @attention None
*
* @param None
*
* @retval #None
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see None
*/
hi_void hi_cache_flush(hi_void);

/**
* @ingroup  iot_cpu
* @brief  Flush Icache. CNcomment:Flush ICache。CNend
*
* @par 描述:
*         Flush Icache, synchronize Icache and memory.
CNcomment:刷新ICache，维持ICache和memory同步。CNend
*
* @attention None
*
* @param None
*
* @retval #None
* @par Dependency:
*            @li hi_cpu.h: Describes CPU usage APIs.
CNcomment:文件用于描述cpu相关接口。CNend
* @see None
*/
hi_void hi_icache_flush(hi_void);

#endif
