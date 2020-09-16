/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2018. All rights reserved.
 * Description: Basic definitions
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */

/**
 * @defgroup kernel Kernel
 * @defgroup los_base Basic definitions
 * @ingroup kernel
 */

#ifndef _LOS_BASE_H
#define _LOS_BASE_H

#include "los_printf.h"
#include "los_list.h"
#include "los_errno.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define SIZE(a) (a)

#define LOS_ASSERT_COND(expression)

/**
 * @ingroup los_base
 * Define the timeout interval as LOS_NO_WAIT.
 */
#define LOS_NO_WAIT                      0

/**
 * @ingroup los_base
 * Define the timeout interval as LOS_WAIT_FOREVER.
 */
#define LOS_WAIT_FOREVER                 0xFFFFFFFF

/**
 * @ingroup los_base
 * Align the beginning of the object with the base address addr,
 * with boundary bytes being the smallest unit of alignment.
 */
#ifndef ALIGN
#define ALIGN(addr, boundary)        LOS_Align(addr, boundary)
#endif
/**
 * @ingroup los_base
 * Align the tail of the object with the base address addr, with size bytes being the smallest unit of alignment.
 */
#define TRUNCATE(addr, size)         ((addr) & ~((size)-1))

/**
 * @ingroup los_base
 * Read a UINT8 value from addr and stroed in value.
 */
#define READ_UINT8(value, addr)      ((value) = *((volatile UINT8 *)(addr)))
/**
 * @ingroup los_base
 * Read a UINT16 value from addr and stroed in addr.
 */
#define READ_UINT16(value, addr)     ((value) = *((volatile UINT16 *)(addr)))
/**
 * @ingroup los_base
 * Read a UINT32 value from addr and stroed in value.
 */
#define READ_UINT32(value, addr)     ((value) = *((volatile UINT32 *)(addr)))
/**
 * @ingroup los_base
 * Read a UINT64 value from addr and stroed in value.
 */
#define READ_UINT64(value, addr)     ((value) = *((volatile UINT64 *)(addr)))

/**
 * @ingroup los_base
 * Get a UINT8 value from addr.
 */
#define GET_UINT8(addr)                (*((volatile UINT8 *)(addr)))
/**
 * @ingroup los_base
 * Get a UINT16 value from addr.
 */
#define GET_UINT16(addr)               (*((volatile UINT16 *)(addr)))
/**
 * @ingroup los_base
 * Get a UINT32 value from addr.
 */
#define GET_UINT32(addr)               (*((volatile UINT32 *)(addr)))
/**
 * @ingroup los_base
 * Get a UINT64 value from addr.
 */
#define GET_UINT64(addr)               (*((volatile UINT64 *)(addr)))

/**
 * @ingroup los_base
 * Write a UINT8 value to addr.
 */
#define WRITE_UINT8(value, addr)     (*((volatile UINT8 *)(addr)) = (value))
/**
 * @ingroup los_base
 * Write a UINT16 value to addr.
 */
#define WRITE_UINT16(value, addr)    (*((volatile UINT16 *)(addr)) = (value))
/**
 * @ingroup los_base
 * Write a UINT32 value to addr.
 */
#define WRITE_UINT32(value, addr)    (*((volatile UINT32 *)(addr)) = (value))
/**
 * @ingroup los_base
 * Write a UINT64 addr to addr.
 */
#define WRITE_UINT64(value, addr) (*((volatile UINT64 *)(addr)) = (value))

#if PRINT_LEVEL < LOS_ERR_LEVEL
#define LOS_ASSERT(judge)
#else
#define LOS_ASSERT(judge)                                                          \
    do {                                                                           \
        if ((judge) == 0) {                                                        \
            (VOID)LOS_IntLock();                                                   \
            PRINT_ERR("ASSERT ERROR! %s, %d\n", __FUNCTION__, __LINE__);           \
            while (1) { }                                                          \
        }                                                                          \
    } while (0)
#endif

/**
 * @ingroup los_base
 * @brief Align the value (addr) by some bytes (boundary) you specify.
 *
 * @par Description:
 * This API is used to align the value (addr) by some bytes (boundary) you specify.
 *
 * @attention
 * <ul>
 * <li>the value of boundary usually is 4,8,16,32.</li>
 * </ul>
 *
 * @param addr     [IN]  The variable what you want to align.
 * @param boundary [IN]  The align size what you want to align.
 *
 * @retval #UINT32 The variable what have been aligned.
 * @par Dependency:
 * <ul><li>los_base.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 LOS_Align(UINT32 addr, UINT32 boundary);

/**
 * @ingroup los_base
 * @brief Sleep the current task.
 *
 * @par Description:
 * This API is used to delay the execution of the current task. The task is able to be scheduled
 * after it is delayed for a specified number of Ticks.
 *
 * @attention
 * <ul>
 * <li>The task fails to be delayed if it is being delayed during interrupt processing or it is locked.</li>
 * <li>If 0 is passed in and the task scheduling is not locked,
 * execute the next task in the queue of tasks with the priority of the current task.
 * If no ready task with the priority of the current task is available,
 * the task scheduling will not occur, and the current task continues to be executed.</li>
 * <li>The parameter passed in can not be equal to LOS_WAIT_FOREVER(0xFFFFFFFF).
 * If that happens, the task will not sleep 0xFFFFFFFF milliseconds or sleep forever but sleep 0xFFFFFFFF Ticks.</li>
 * </ul>
 *
 * @param mSecs [IN] Type #UINT32 Number of MS for which the task is delayed.
 *
 * @retval None
 * @par Dependency:
 * <ul><li>los_base.h: the header file that contains the API declaration.</li></ul>
 * @see None
 */
extern VOID LOS_Msleep(UINT32 mSecs);

/**
 * @ingroup los_base
 * @brief System kernel initialization function.
 *
 * @par Description:
 * This API is used to start liteOS .
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param: None.
 *
 * @retval #LOS_OK                                  0:LiteOS start success.
 *
 * @par Dependency:
 * <ul><li>los_config.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 LOS_Start(VOID);

/**
 * @ingroup los_base
 * @brief System kernel initialization function.
 *
 * @par Description:
 * This API is used to Initialize kernel ,configure all system modules.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param: None.
 *
 * @retval #LOS_OK                                  0:System kernel initialization success.
 *
 * @par Dependency:
 * <ul><li>los_config.h: the header file that contains the API declaration.</li></ul>
 * @see
 */
extern UINT32 LOS_KernelInit(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_BASE_H */
