/**
 * @file hi_os_stat.h
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
 * @defgroup os_stat OS Status
 * @ingroup osa
 */

#ifndef __HI_OS_STAT_H__
#define __HI_OS_STAT_H__

#include <hi_types_base.h>

#define HI_OS_STAT_MSG_WAIT_FAIL     0x1   /**< Used in the interrupt context.CNcomment:中断上下文使用CNend */
#define HI_OS_STAT_MSG_SEND_FAIL     0x2   /**< The timeout period of the interrupt context configuration is not 0,
                                              and the queue is full.CNcomment:中断上下文配置超时时间不为0，
                                              队列满 CNend */
#define HI_OS_STAT_SEM_WAIT_FAIL     0x4   /**< Used in the interrupt context.CNcomment:中断上下文使用CNend */
#define HI_OS_STAT_SEM_SIGNAL_FAIL   0x8   /**< Repeated release.CNcomment:重复释放CNend */
#define HI_OS_STAT_MUX_PEND_FAIL     0x10  /**< Used in the interrupt context.CNcomment:中断上下文使用CNend  */
#define HI_OS_STAT_MUX_POST_FAIL     0x20  /**< Cross-task use, not created.CNcomment:跨任务使用，未创建CNend  */
#define HI_OS_STAT_EVENT_WAIT_FAIL   0x40  /**< Used in the interrupt context.CNcomment:中断上下文使用 CNend */
#define HI_OS_STAT_EVENT_SEND_FAIL   0x80  /**< Initialized EVT resources used up.
                                              CNcomment:初始化EVT资源已经用完 CNend */
#define HI_OS_STAT_EVENT_CLR_FAIL    0x100 /**< Invalid input argument.CNcomment:入参错误 CNend */
#define HI_OS_STAT_SLEEP_FAIL        0x200 /**< Used in the interrupt context.CNcomment:中断上下文使用CNend  */
#define HI_OS_STAT_START_TIMER_FAIL  0x400 /**< Invalid input argument.CNcomment:入参错误 CNend */
#define HI_OS_STAT_CREATE_TIMER_FAIL 0x800 /**< WorkQueue used up.CNcomment:创建定时器句柄失败 CNend */

/**
 * @ingroup os_stat
 * System resource usage statistic.CNcomment:系统资源使用统计量。CNend
 */
typedef struct {
    hi_u8 timer_usage;  /**< Number of used system timers.CNcomment:当前使用系统定时器个数 CNend */
    hi_u8 task_usage;   /**< Number of used tasks.CNcomment:当前使用任务个数 CNend */
    hi_u8 sem_usage;    /**< Number of used semaphores.CNcomment:当前使用信号量个数 CNend */
    hi_u8 queue_usage;  /**< Number of used message queues.CNcomment:当前使用消息队列个数 CNend */
    hi_u8 mux_usage;    /**< Number of used mutexes.CNcomment:当前使用互斥锁个数 CNend */
    hi_u8 event_usage;  /**< Number of used events.CNcomment:当前使用事件个数 CNend */
    hi_u16 err_info;    /**< Error statistic HI_OS_STAT_XXX, used to log occurred errors.
                           CNcomment:错误统计量HI_OS_STAT_XXX，用于记录曾经出现过的错误 CNend */
}hi_os_resource_use_stat;

/**
* @ingroup  os_stat
* @brief  Obtains the system resource usage.CNcomment:获取当前系统资源使用情况。CNend
*
* @par 描述:
*           Obtains the system resource usage.CNcomment:获取当前系统资源使用情况。CNend
*
* @attention None
* @param  os_resource_stat [OUT] type #hi_os_resource_use_stat*，System resource usage statistic.
CNcomment:系统资源使用统计量。CNend
*
* @retval #0               Success.
* @retval #Other           Failure. For details, see hi_errno.h
* @par 依赖:
*            @li hi_os_stat.h：Describes system resource usage APIs.
CNcomment:文件用于描述定时器相关接口。CNend
* @see  None
*/
hi_u32 hi_os_get_resource_status(hi_os_resource_use_stat *os_resource_stat);

#endif

