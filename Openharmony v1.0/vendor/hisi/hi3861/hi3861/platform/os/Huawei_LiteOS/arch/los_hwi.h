/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description : LiteOS interrupt module implemention.
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
 * ---------------------------------------------------------------------------- */

/**
 * @defgroup los_hwi Hardware interrupt
 * @ingroup kernel
 */

#ifndef _LOS_HWI_H
#define _LOS_HWI_H

#include "los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */
/**
 * @ingroup los_config
 * Configuration item for interrupt with argument
 */
#ifndef OS_HWI_WITH_ARG
#define OS_HWI_WITH_ARG             YES
#endif
/**
 * @ingroup los_hwi
 * Define the type of a hardware interrupt number.
 */
typedef UINT32                                              HWI_HANDLE_T;

/**
 * @ingroup los_hwi
 * Define the type of a hardware interrupt priority.
 */
typedef UINT16                                              HWI_PRIOR_T;

/**
 * @ingroup los_hwi
 * Define the type of hardware interrupt mode configurations.
 */
typedef UINT16                                              HWI_MODE_T;

/**
 * @ingroup los_hwi
 * Define the type of the parameter used for the hardware interrupt creation function.
 * The function of this parameter varies among platforms.
 */
typedef UINT32                                              HWI_ARG_T;

/**
 * @ingroup  los_hwi
 * Define the type of a hardware interrupt handling function.
 */
#if (OS_HWI_WITH_ARG == YES)

typedef VOID (* HWI_PROC_FUNC)(VOID *arg);
typedef struct {
    HWI_PROC_FUNC pfnHandler;
    VOID*         pParm;
} HWI_SLAVE_FUNC;

#else

typedef VOID (* HWI_PROC_FUNC)(VOID);

#endif

/**
 * @ingroup  los_hwi
 * Define the type of a hardware interrupt hook function.
 */
typedef VOID (*HWI_HOOK_FUNC)(UINT32 hwiNum);

/**
 * @ingroup  los_hwi
 * Define the type of a hardware interrupt vector table function.
 */
typedef VOID (**HWI_VECTOR_FUNC)(VOID);

/**
 * @ingroup los_hwi
 * Count of interrupts.
 */
extern UINT32  g_vuwIntCount;

/**
 * @ingroup los_hwi
 * An interrupt is active.
 */
#define OS_INT_ACTIVE               (g_vuwIntCount > 0)

/**
 * @ingroup los_hwi
 * An interrupt is inactive.
 */
#define OS_INT_INACTIVE             (!(OS_INT_ACTIVE))

/**
 * @ingroup los_hwi
 * Count of HimiDeer system interrupt vector.
 */
#define OS_HIMIDEER_SYS_VECTOR_CNT               26

/**
 * @ingroup los_hwi
 * Count of HimiDeer local interrupt vector 0 - 5, enabled by CSR mie 26 -31 bit.
 */
#define OS_HIMIDEER_MIE_IRQ_VECTOR_CNT            6

/**
 * @ingroup los_hwi
 * Count of HimiDeer IRQ controlled by CSR mie
 */
#define OS_HIMIDEER_MIE_TOTAL_CNT        (OS_HIMIDEER_SYS_VECTOR_CNT + OS_HIMIDEER_MIE_IRQ_VECTOR_CNT)

/**
 * @ingroup los_hwi
 * Count of HimiDeer local interrupt vector 6 - 34, enabled by custom CSR locie0 0 - 22 bit.
 */
#ifndef LOSCFG_RAM_MONITOR
#define OS_HIMIDEER_CUSTOM_IRQ_VECTOR_CNT        29
#else
#define OS_HIMIDEER_CUSTOM_IRQ_VECTOR_CNT        (29 + 1)  // add ram monitor interrupt
#endif
/**
 * @ingroup los_hwi
 * Count of HimiDeer local IRQ interrupt vector.
 */
#define OS_HIMIDEER_LOCAL_IRQ_VECTOR_CNT        (OS_HIMIDEER_MIE_IRQ_VECTOR_CNT + OS_HIMIDEER_CUSTOM_IRQ_VECTOR_CNT)

/**
 * @ingroup los_hwi
 * Count of himideer interrupt vector.
 */
#define OS_HIMIDEER_VECTOR_CNT      (OS_HIMIDEER_SYS_VECTOR_CNT + OS_HIMIDEER_LOCAL_IRQ_VECTOR_CNT)

#define OS_VECTOR_CNT               OS_HIMIDEER_VECTOR_CNT

#define OS_HWI_MAX_NUM              OS_HIMIDEER_VECTOR_CNT

/**
 * @ingroup los_hwi
 * Minimum interrupt number.
 */
#define OS_HWI_MIN                  0

/**
 * @ingroup los_hwi
 * Maximum interrupt number.
 */
#define OS_HWI_MAX                  ((OS_HWI_MAX_NUM) - 1)

/**
 * @ingroup los_hwi
 * Highest priority of a hardware interrupt.
 */
#ifndef OS_HWI_PRIO_HIGHEST
#define OS_HWI_PRIO_HIGHEST        7
#endif
/**
 * @ingroup los_hwi
 * Lowest priority of a hardware interrupt.
 */
#ifndef OS_HWI_PRIO_LOWEST
#define OS_HWI_PRIO_LOWEST         1
#endif

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: Invalid interrupt number.
 *
 * Value: 0x02000900
 *
 * Solution: Ensure that the interrupt number is valid. The value range of the interrupt number applicable
 * for a Cortex-M4 platform is [0,240].
 */
#define OS_ERRNO_HWI_NUM_INVALID                 LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x00)

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: Null hardware interrupt handling function.
 *
 * Value: 0x02000901
 *
 * Solution: Pass in a valid non-null hardware interrupt handling function.
 */
#define OS_ERRNO_HWI_PROC_FUNC_NULL              LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x01)

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: Insufficient interrupt resources for hardware interrupt creation.
 *
 * Value: 0x02000902
 *
 * Solution: Increase the configured maximum number of supported hardware interrupts.
 */
#define OS_ERRNO_HWI_CB_UNAVAILABLE              LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x02)

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: Insufficient memory for hardware interrupt initialization.
 *
 * Value: 0x02000903
 *
 * Solution: Expand the configured memory.
 */
#define OS_ERRNO_HWI_NO_MEMORY                   LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x03)

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: The interrupt has already been created.
 *
 * Value: 0x02000904
 *
 * Solution: Check whether the interrupt specified by the passed-in interrupt number has already been created.
 */
#define OS_ERRNO_HWI_ALREADY_CREATED             LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x04)

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: Invalid interrupt priority.
 *
 * Value: 0x02000905
 *
 * Solution: Ensure that the interrupt priority is valid. The value range of the interrupt priority applicable
 * for a Cortex-M4 platform is [OS_HWI_PRIO_HIGHEST,OS_HWI_PRIO_LOWEST].
 */
#define OS_ERRNO_HWI_PRIO_INVALID                LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x05)

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: Incorrect interrupt creation mode.
 *
 * Value: 0x02000906
 *
 * Solution: The interrupt creation mode can be only set to OS_HWI_MODE_COMM or OS_HWI_MODE_FAST of which the
 * value can be 0 or 1.
 */
#define OS_ERRNO_HWI_MODE_INVALID                LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x06)

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: The interrupt has already been created as a fast interrupt.
 *
 * Value: 0x02000907
 *
 * Solution: Check whether the interrupt specified by the passed-in interrupt number has already been created.
 */
#define OS_ERRNO_HWI_FASTMODE_ALREADY_CREATED    LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x07)

/**
 * @ingroup los_hwi
 * Hardware interrupt error code: The interrupt is not created when enable this interrupt.
 *
 * Value: 0x02000908
 *
 * Solution: Check whether the interrupt is already been created before enable.
 */
#define OS_ERRNO_HWI_NOT_CREATED    LOS_ERRNO_OS_ERROR(LOS_MOD_HWI, 0x08)

#if (OS_HWI_WITH_ARG == YES)
/**
 * @ingroup los_hwi
 * hardware interrupt Slave form mapping handling function array.
 */
extern HWI_SLAVE_FUNC g_hwiSlaveForm[OS_HIMIDEER_VECTOR_CNT];

/**
 * @ingroup los_hwi
 * Set interrupt vector table.
 */
extern HWI_PROC_FUNC g_intEntry;
#define OS_SET_VECTOR(num, vector, arg) do {    \
    g_hwiSlaveForm[num].pfnHandler = (vector);   \
    g_hwiSlaveForm[num].pParm = (VOID*)(UINTPTR)(arg);   \
} while (0)
#else
/**
 * @ingroup los_hwi
 * hardware interrupt Slave form mapping handling function array.
 */
extern HWI_PROC_FUNC g_hwiSlaveForm[OS_HIMIDEER_VECTOR_CNT];

/**
 * @ingroup los_hwi
 * Set interrupt vector table.
 */
#define OS_SET_VECTOR(num, vector) do { \
    g_hwiSlaveForm[num] = (vector);     \
} while (0)
#endif

/**
 * @ingroup  los_hwi
 * @brief Create a hardware interrupt.
 *
 * @par Description:
 * This API is used to configure a hardware interrupt and register a hardware interrupt handling function.
 *
 * @attention
 * <ul>
 * <li>The hardware interrupt module is usable only when the configuration item for hardware interrupt tailoring
 * is enabled.</li>
 * <li>Hardware interrupt number value range: [OS_HWI_MIN,OS_HWI_MAX]. The value range applicable for a Cortex-M4
 * platform is [0,240].</li>
 * <li>OS_HWI_MAX_NUM specifies the maximum number of interrupts that can be created.</li>
 * <li>Before executing an interrupt on a platform, refer to the chip manual of the platform.</li>
 * </ul>
 *
 * @param  hwiNum     [IN] Type#HWI_HANDLE_T: hardware interrupt number. The value range applicable for a Cortex-M4
 * platform is [0,240].
 * @param  hwiPrio    [IN] Type#HWI_PRIOR_T: hardware interrupt priority. Ignore this parameter temporarily.
 * @param  mode       [IN] Type#HWI_MODE_T: hardware interrupt mode. Ignore this parameter temporarily.
 * @param  funHandler [IN] Type#HWI_PROC_FUNC: interrupt handler used when a hardware interrupt is triggered.
 * @param  arg        [IN] Type#HWI_ARG_T: input parameter of the interrupt handler used when a hardware interrupt
 *                         is triggered.
 *
 * @retval #OS_ERRNO_HWI_PROC_FUNC_NULL     0x02000901: Null hardware interrupt handling function.
 * @retval #OS_ERRNO_HWI_NUM_INVALID        0x02000900: Invalid interrupt number.
 * @retval #OS_ERRNO_HWI_NO_MEMORY          0x02000903: Insufficient memory for hardware interrupt creation.
 * @retval #OS_ERRNO_HWI_ALREADY_CREATED    0x02000904: The interrupt handler being created has already been created.
 * @retval #LOS_OK                          0,               : The interrupt is successfully created.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_HwiCreate(HWI_HANDLE_T  hwiNum,
                            HWI_PRIOR_T   hwiPrio,
                            HWI_MODE_T    mode,
                            HWI_PROC_FUNC funHandler,
                            HWI_ARG_T     arg);

/**
 * @ingroup  los_hwi
 * @brief: Hardware interrupt entry function.
 *
 * @par Description:
 * This API is used as all hardware interrupt handling function entry.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param: None.
 *
 * @retval:None.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID  OsInterrupt(VOID);

/**
 * @ingroup  los_hwi
 * @brief: Get a interrupt number.
 *
 * @par Description:
 * This API is used to get the current interrupt number.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param: None.
 *
 * @retval: Interrupt Indexes number.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsIntNumGet(VOID);

/**
 * @ingroup  los_hwi
 * @brief: Default vector handling function.
 *
 * @par Description:
 * This API is used to configure interrupt for null function.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param: None.
 *
 * @retval:None.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID  OsHwiDefaultHandler(VOID);

/**
 * @ingroup  los_config
 * @brief: hardware interrupt init function.
 *
 * @par Description:
 * This API is used to initialize hardware interrupt module.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param: None.
 *
 * @retval #LOS_OK                      0:Hardware interrupt initialization success.
 *
 * @par Dependency:
 * <ul><li>los_config.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID OsHwiInit(VOID);

 /**
 * @ingroup los_hwi
 * @brief Enable all interrupts.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to enable all IRQ and FIQ interrupts in the CPSR.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval CPSR value obtained after all interrupts are enabled.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_IntRestore
 */
extern UINTPTR LOS_IntUnLock(VOID);

 /**
 * @ingroup los_hwi
 * @brief Disable all interrupts.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to disable all IRQ and FIQ interrupts in the CPSR.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval CPSR value obtained before all interrupts are disabled.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_IntRestore
 */
extern UINTPTR LOS_IntLock(VOID);

 /**
 * @ingroup los_hwi
 * @brief Restore interrupts.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to restore the CPSR value obtained before all interrupts are disabled.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>This API can be called only after all interrupts are disabled, and the input parameter value
 * should be the value returned by calling the all interrupt disabling API.</li>
 * </ul>
 *
 * @param intSave [IN] CPSR value obtained before all interrupts are disabled.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_IntLock
 */
extern VOID LOS_IntRestore(UINTPTR intSave);

/**
 * @ingroup  los_hwi
 * @brief Delete hardware interrupt.
 *
 * @par Description:
 * This API is used to delete hardware interrupt.
 *
 * @attention
 * <ul>
 * <li>The hardware interrupt module is usable only when the configuration item for hardware interrupt
 * tailoring is enabled.</li>
 * <li>Hardware interrupt number value range: [OS_HWI_MIN,OS_HWI_MAX]. The value range applicable for
 * a Cortex-M4 platform is [0,240].</li>
 * <li>OS_HWI_MAX_NUM specifies the maximum number of interrupts that can be created.</li>
 * <li>Before executing an interrupt on a platform, refer to the chip manual of the platform.</li>
 * </ul>
 *
 * @param  hwiNum [IN] Type#HWI_HANDLE_T: hardware interrupt number. The value range applicable for
 * a Cortex-M4 platform is [0,240].
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID              0x02000900: Invalid interrupt number.
 * @retval #LOS_OK                                0: The interrupt is successfully delete.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_HwiDelete(HWI_HANDLE_T hwiNum);

/**
 * @ingroup los_hwi
 * @brief Rigister interrupt hook functions.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to register functions which is reserved in rom code .</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None .</li>
 * </ul>
 *
 * @param  prepareFunc [IN] Type#HWI_HOOK_FUNC: function that called before irq.
 * @param  resumeFunc [IN] Type#HWI_HOOK_FUNC: function that called after irq.
 *
 * @retval VOID.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None
 */
extern VOID LOS_HwiRigister(HWI_HOOK_FUNC prepareFunc, HWI_HOOK_FUNC resumeFunc);

/**
 * @ingroup los_hwi
 * @brief Get interrupt number.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to get irq number .</li>
 * </ul>
 * @attention
 * <ul>
 * <li>This API can be called only when an irq come up .</li>
 * </ul>
 *
 * @param None.
 *
 * @retval UINT32 irq number.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None
 */
extern UINT32 LOS_IntNumGet(VOID);

/**
 * @ingroup los_hwi
 * @brief Enable interrupt and set the priority.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to set irq priority and enable it.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>This API can be called only when an irq is created by LOS_HwiCreate .</li>
 * </ul>
 *
 * @param irqnum [IN] The Irq num,it should in [OS_HIMIDEER_SYS_VECTOR_CNT,
 * OS_HIMIDEER_LOCAL_IRQ_VECTOR_CNT]
 * @param prior  [IN] The Irq priority, it should in [OS_HWI_PRIO_LOWEST, OS_HWI_PRIO_HIGHEST].
 * @retval OS_ERRNO_HWI_NUM_INVALID: the input irqnum is incorrect
 * @retval OS_ERRNO_HWI_NOT_CREATED: the irq is not created by LOS_HwiCreate
 * @retval OS_ERRNO_HWI_PRIO_INVALID: the input the input irqnum is incorrect is incorrect
 * @retval LOS_OK: success
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None
 */
extern UINT32 LOS_AdapIrqEnable(UINT32 irqNum, UINT16 prior);

/**
 * @ingroup los_hwi
 * @brief Disable the interrupt.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to disable irq.</li>
 * </ul>
 * @attention
 * <ul>
 * <li>None .</li>
 * </ul>
 *
 * @param irqnum [IN] The Irq num,it should in [OS_HIMIDEER_SYS_VECTOR_CNT,
 * OS_HIMIDEER_LOCAL_IRQ_VECTOR_CNT]
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None
 */
extern VOID LOS_AdapIrqDisable(UINT32 irqNum);

/**
 * @ingroup los_hwi
 * @brief diable interrupts.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to disable interrupts .</li>
 * </ul>
 * @attention
 * <ul>
 * <li>This API can be called only in OsTaskExit() .</li>
 * </ul>
 *
 * @param None.
 *
 * @retval None.
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None
 */
extern VOID OsDisableIRQ(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* _LOS_HWI_H */
