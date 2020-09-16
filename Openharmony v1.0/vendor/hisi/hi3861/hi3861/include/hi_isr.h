/**
 * @file hi_isr.h
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
 * @defgroup iot_isr Interruption
 * @ingroup osa
 */

#ifndef __HI_ISR_H__
#define __HI_ISR_H__
#include "hi_types.h"

#define HI_EXC_FLAG_NO_FLOAT                0x10000000
#define HI_EXC_FLAG_FAULTADDR_VALID         0x01
#define HI_EXC_FLAG_IN_HWI                  0x02

typedef struct {
    /* handler save */
    hi_u32 r4;
    hi_u32 r5;
    hi_u32 r6;
    hi_u32 r7;
    hi_u32 r8;
    hi_u32 r9;
    hi_u32 r10;
    hi_u32 r11;
    hi_u32 pri_mask;
    /* auto save */
    hi_u32 sp;
    hi_u32 r0;
    hi_u32 r1;
    hi_u32 r2;
    hi_u32 r3;
    hi_u32 r12;
    hi_u32 lr;
    hi_u32 pc;
    hi_u32 xpsr;
} hi_exc_context;

/**
* @ingroup  iot_isr
* @brief  HISR callback function type.CNcomment:HISR中断回调函数的类型。CNend
*
* @par 描述：
*           HISR callback function type.CNcomment:HISR中断回调函数的类型。CNend
*
* @attention None
* @param  param [IN] type #hi_u32，Callback input parameter.CNcomment:回调入参。CNend
*
* @retval None
* @par 依赖:
*            @li hi_isr.h：Describes ISR APIs.CNcomment:文件用于描述ISR相关接口。CNend
* @see None
*/
typedef hi_void (*irq_routine)(hi_u32 param);

/**
* @ingroup  iot_isr
* @brief  Interrupt off.CNcomment:关中断。CNend
*
* @par 描述:
*           Interrupt off.CNcomment:关中断。CNend
*
* @attention
*           @li A function that causes scheduling cannot be executed in an interrupt off context, for example,
*               hi_sleep and other blocked APIs.
*               CNcomment:关中断后不能执行引起调度的函数，如hi_sleep或其他阻塞接口。CNend
*           @li Interrupt off only protects short-time operations that can be expected. Otherwise, the interrupt
*               response and the performance may be affected.
*               CNcomment:关中断仅保护可预期的短时间的操作，否则影响中断响应，可能引起性能问题。CNend
*
* @param  None
*
* @retval #hi_u32 Interruption status value  Interrupt status before interrupt off.
CNcomment:中断状态值  关中断前的中断状态。CNend
*
* @par 依赖:
*            @li hi_isr.h：Describes ISR APIs.CNcomment:文件用于描述ISR相关接口。CNend
* @see  hi_int_restore。
*/
hi_u32 hi_int_lock(hi_void);

/**
* @ingroup  iot_isr
* @brief  Restores the status before interrupt off.CNcomment:恢复关中断前的状态。CNend
*
* @par 描述:
*           Restores the status before interrupt off.CNcomment:恢复关中断前的状态。CNend
*
* @attention The input argument must be the value of CPSR that is saved before interrupt off.
CNcomment:入参必须是与之对应的关中断时保存的关中断之前的CPSR的值。CNend
*
* @param  int_value [IN] type #hi_u32，Interrupt status.CNcomment:中断状态。CNend
*
* @retval None
* @par 依赖:
*            @li hi_isr.h：Describes ISR APIs.CNcomment:文件用于描述ISR相关接口。CNend
* @see  hi_int_lock。
*/
hi_void hi_int_restore(hi_u32 int_value);

/**
* @ingroup  iot_isr
* @brief  Enables a specified interrupt.CNcomment:使能指定中断。CNend
*
* @par 描述:
*           Enables a specified interrupt.CNcomment:使能指定中断。CNend
*
* @attention None
*
* @param  vector [IN] type #hi_u32，Interrupt ID.CNcomment:中断号。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h
* @par 依赖:
*            @li hi_isr.h：Describes ISR APIs.CNcomment:文件用于描述ISR相关接口。CNend
* @see  hi_irq_disable。
*/
hi_u32 hi_irq_enable(hi_u32 vector);

/**
* @ingroup  iot_isr
* @brief  Disables a specified interrupt.CNcomment:去使能指定中断。CNend
*
* @par 描述:
*           Disables a specified interrupt.CNcomment:去使能指定中断。CNend
*
* @attention None
* @param  vector [IN] type #hi_u32，Interrupt ID.CNcomment:中断号。CNend
*
* @retval None
* @par 依赖:
*            @li hi_isr.h：Describes ISR APIs.CNcomment:文件用于描述ISR相关接口。CNend
* @see  hi_irq_enable。
*/
hi_void hi_irq_disable(hi_u32 vector);

/* 由于不支持中断嵌套，仅当中断同时触发的场景下有效。 */
#define HI_IRQ_FLAG_PRI1    1
#define HI_IRQ_FLAG_PRI2    2
#define HI_IRQ_FLAG_PRI3    3
#define HI_IRQ_FLAG_PRI4    4
#define HI_IRQ_FLAG_PRI5    5
#define HI_IRQ_FLAG_PRI6    6
#define HI_IRQ_FLAG_PRI7    7
#define HI_IRQ_FLAG_PRI_MASK  0x7
#define HI_IRQ_FLAG_NOT_IN_FLASH 0x10

#define HI_IRQ_FLAG_DEFAULT    HI_IRQ_FLAG_NOT_IN_FLASH

/**
* @ingroup  iot_isr
* @brief  Registers an interrupt.CNcomment:注册中断。CNend
*
* @par 描述:
*           Registers an interrupt.CNcomment:注册中断。CNend
*
* @attention The interruption handling program cannot take too long a time, which affects the timely response of the
*            CPU to the interrupt.CNcomment:中断处理程序耗时不能过长，影响CPU对中断的及时响应。CNend
*
* @param  vector [IN] type #hi_u32，Interrupt ID.CNcomment:中断号。CNend
* @param  flag [IN]   type #hi_u32, attributes like priority,etc.CNcomment:中断优先级等属性。CNend
* @param  routine  [IN] type #irq_routine，Interrupt callback function.CNcomment:中断回调函数。CNend
* @param  param    [IN] type #hi_u32，Parameter transferred to the callback function.
CNcomment:中断回调函数的入参。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h
* @par 依赖:
*            @li hi_isr.h：Describes ISR APIs.CNcomment:文件用于描述ISR相关接口。CNend
* @see  hi_irq_free。
*/
hi_u32 hi_irq_request(hi_u32 vector, hi_u32 flags, irq_routine routine, hi_u32 param);

/**
* @ingroup  iot_isr
* @brief  Clears a registered interrupt.CNcomment:清除注册中断。CNend
*
* @par 描述:
*           Clears a registered interrupt.CNcomment:清除注册中断。CNend
*
* @attention None
* @param  vector [IN] type #hi_u32，Interrupt ID.CNcomment:中断号。CNend
*
* @retval #0       Success.
* @retval #Other   Failure. For details, see hi_errno.h
* @par 依赖:
*            @li hi_isr.h：Describes ISR APIs.CNcomment:文件用于描述ISR相关接口。CNend
* @see  hi_irq_request。
*/
hi_u32 hi_irq_free(hi_u32 vector);

/**
* @ingroup  iot_isr
* @brief  Checks whether it is in the interrupt context.CNcomment:检查是否在中断上下文中。CNend
*
* @par 描述:
*           Checks whether it is in the interrupt context.CNcomment:检查是否在中断上下文中。CNend
*
* @attention None
* @param  None
*
* @retval #HI_FALSE     Not in the interrupt context.CNcomment:不在中断上下文中。CNend
* @retval #HI_TRUE     In the interrupt context.CNcomment:在中断上下文中。CNend
* @par 依赖:
*            @li hi_isr.h：Describes ISR APIs.CNcomment:文件用于描述ISR相关接口。CNend
* @see  无。
*/
hi_bool hi_is_int_context(hi_void);

#endif

