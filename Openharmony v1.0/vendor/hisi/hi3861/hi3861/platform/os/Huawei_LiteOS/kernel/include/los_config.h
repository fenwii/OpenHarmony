/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 * Description: los_config system configuration items
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
 * @defgroup los_config System configuration items
 * @ingroup kernel
 */

#ifndef _LOS_CONFIG_H
#define _LOS_CONFIG_H

#include "target_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* =============================================================================
                                        System clock module configuration
============================================================================= */
/**
 * @ingroup los_config
 * System clock (unit: HZ)
 */
#ifndef OS_SYS_CLOCK
#define OS_SYS_CLOCK                                        100000000UL
#endif

/**
 * @ingroup los_config
 * timer1 clock (unit: HZ)
 */
#ifndef OS_TIME_TIMER_CLOCK
#define OS_TIME_TIMER_CLOCK                                 OS_SYS_CLOCK
#endif

/**
 * @ingroup los_config
 * Number of Ticks in one second
 */
#ifndef LOSCFG_BASE_CORE_TICK_PER_SECOND
#define LOSCFG_BASE_CORE_TICK_PER_SECOND                    1000UL
#endif

/**
 * @ingroup los_config
 * External configuration item for timer tailoring
 */
#ifndef LOSCFG_BASE_CORE_TICK_HW_TIME1
#define LOSCFG_BASE_CORE_TICK_HW_TIME1                      YES
#endif

#ifndef LOSCFG_BASE_CORE_TICK_HW_TIME
#define LOSCFG_BASE_CORE_TICK_HW_TIME                       NO
#endif

/* =============================================================================
                                        Hardware interrupt module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for hardware interrupt tailoring
 */
#ifndef LOSCFG_PLATFORM_HWI
#define LOSCFG_PLATFORM_HWI                                 YES
#endif

/**
 * @ingroup los_config
 * Maximum number of used hardware interrupts, including Tick timer interrupts.
 */
#ifndef LOSCFG_PLATFORM_HWI_LIMIT
#define LOSCFG_PLATFORM_HWI_LIMIT                           32
#endif


/* =============================================================================
                                       Task module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Minimum stack size.
 *
 * 0x80 bytes, aligned on a boundary of 8.
 */
#ifndef LOSCFG_BASE_CORE_TSK_MIN_STACK_SIZE
#define LOSCFG_BASE_CORE_TSK_MIN_STACK_SIZE                 (ALIGN(0x80, 4))
#endif

/**
 * @ingroup los_config
 * Default task priority
 */
#ifndef LOSCFG_BASE_CORE_TSK_DEFAULT_PRIO
#define LOSCFG_BASE_CORE_TSK_DEFAULT_PRIO                   10
#endif

/**
 * @ingroup los_config
 * Maximum supported number of tasks except the idle task rather than the number of usable tasks
 */
#ifndef LOSCFG_BASE_CORE_TSK_LIMIT
#define LOSCFG_BASE_CORE_TSK_LIMIT                          5
#endif

/**
 * @ingroup los_config
 * Size of the idle task stack
 */
#ifndef LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE
#define LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE                0x180UL
#endif

/**
 * @ingroup los_config
 * Default task stack size
 */
#ifndef LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE
#define LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE             0x400UL
#endif

/**
 * @ingroup los_config
 * Configuration item for task Robin tailoring
 */
#ifndef LOSCFG_BASE_CORE_TIMESLICE
#define LOSCFG_BASE_CORE_TIMESLICE                          YES
#endif

/**
 * @ingroup los_config
 * Longest execution time of tasks with the same priorities
 */
#ifndef LOSCFG_BASE_CORE_TIMESLICE_TIMEOUT
#define LOSCFG_BASE_CORE_TIMESLICE_TIMEOUT                  10
#endif

/**
 * @ingroup los_config
 * Configuration item for task (stack) monitoring module tailoring
 */
#ifndef LOSCFG_BASE_CORE_TSK_MONITOR
#define LOSCFG_BASE_CORE_TSK_MONITOR                        NO
#endif

/**
 * @ingroup los_config
 * Configuration item for task perf task filter hook
 */
#ifndef LOSCFG_BASE_CORE_EXC_TSK_SWITCH
#define LOSCFG_BASE_CORE_EXC_TSK_SWITCH                     NO
#endif

/**
 * @ingroup los_config
 * Define a usable task priority.Highest task priority.
 */
#ifndef LOS_TASK_PRIORITY_HIGHEST
#define LOS_TASK_PRIORITY_HIGHEST                           0
#endif

/**
 * @ingroup los_config
 * Define a usable task priority.Lowest task priority.
 */
#ifndef LOS_TASK_PRIORITY_LOWEST
#define LOS_TASK_PRIORITY_LOWEST                            31
#endif

/**
 * @ingroup los_config
 * SP align size
 */
#ifndef LOSCFG_STACK_POINT_ALIGN_SIZE
#define LOSCFG_STACK_POINT_ALIGN_SIZE                       8
#endif

/* =============================================================================
                                       Semaphore module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for semaphore module tailoring
 */
#ifndef LOSCFG_BASE_IPC_SEM
#define LOSCFG_BASE_IPC_SEM                                 YES
#endif

/**
 * @ingroup los_config
 * Maximum supported number of semaphores
 */
#ifndef LOSCFG_BASE_IPC_SEM_LIMIT
#define LOSCFG_BASE_IPC_SEM_LIMIT                           6
#endif

/* =============================================================================
                                       Mutex module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for mutex module tailoring
 */
#ifndef LOSCFG_BASE_IPC_MUX
#define LOSCFG_BASE_IPC_MUX                                YES
#endif

/**
 * @ingroup los_config
 * Maximum supported number of mutexes
 */
#ifndef LOSCFG_BASE_IPC_MUX_LIMIT
#define LOSCFG_BASE_IPC_MUX_LIMIT                           6
#endif

/* =============================================================================
                                       Queue module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for queue module tailoring
 */
#ifndef LOSCFG_BASE_IPC_QUEUE
#define LOSCFG_BASE_IPC_QUEUE                               YES
#endif

/**
 * @ingroup los_config
 * Maximum supported number of queues rather than the number of usable queues
 */
#ifndef LOSCFG_BASE_IPC_QUEUE_LIMIT
#define LOSCFG_BASE_IPC_QUEUE_LIMIT                         6
#endif


/* =============================================================================
                                       Software timer module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for software timer module tailoring
 */
#ifndef LOSCFG_BASE_CORE_SWTMR
#define LOSCFG_BASE_CORE_SWTMR                              YES
#endif

/**
 * @ingroup los_config
 * Maximum supported number of software timers rather than the number of usable software timers
 */
#ifndef LOSCFG_BASE_CORE_SWTMR_LIMIT
#define LOSCFG_BASE_CORE_SWTMR_LIMIT                        5
#endif

/**
 * @ingroup los_config
 * Software timer task stack size
 */
#ifndef LOSCFG_BASE_CORE_TSK_SWTMR_STACK_SIZE
#define LOSCFG_BASE_CORE_TSK_SWTMR_STACK_SIZE               LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE
#endif

/**
 * @ingroup los_config
 * Configurate item for handling software timer interrupt in task tailoring
 */
#ifndef LOSCFG_BASE_CORE_SWTMR_TASK
#define LOSCFG_BASE_CORE_SWTMR_TASK                         YES
#endif

/**
 * @ingroup los_config
 * Configurate item for software timer align tailoring
 */
#ifndef LOSCFG_BASE_CORE_SWTMR_ALIGN
#define LOSCFG_BASE_CORE_SWTMR_ALIGN                        NO
#endif

#if((LOSCFG_BASE_CORE_SWTMR == NO) && (LOSCFG_BASE_CORE_SWTMR_ALIGN == YES))
    #error "swtmr align first need support swmtr, should make LOSCFG_BASE_CORE_SWTMR = YES"
#endif

/**
 * @ingroup los_config
 * Max number of software timers ID
 */
#ifndef OS_SWTMR_MAX_TIMERID
#define OS_SWTMR_MAX_TIMERID              ((65535 / LOSCFG_BASE_CORE_SWTMR_LIMIT) * LOSCFG_BASE_CORE_SWTMR_LIMIT)
#endif

/**
 * @ingroup los_config
 * Maximum size of a software timer queue
 */
#ifndef OS_SWTMR_HANDLE_QUEUE_SIZE
#define OS_SWTMR_HANDLE_QUEUE_SIZE                          (LOSCFG_BASE_CORE_SWTMR_LIMIT)
#endif

/**
 * @ingroup los_config
 * Minimum divisor of software timer multiple alignment
 */
#ifndef LOS_COMMON_DIVISOR
#define LOS_COMMON_DIVISOR                                 10
#endif

/* =============================================================================
                                       Memory module configuration
============================================================================= */
extern UINT8 *m_aucSysMem0;

/**
 * @ingroup los_config
 * Starting address of the memory
 */
#ifndef OS_SYS_MEM_ADDR
#define OS_SYS_MEM_ADDR                                     (&m_aucSysMem0[0])
#endif

/**
 * @ingroup los_config
 * Ending address of the memory
 */
extern UINT32 g_sysMemAddrEnd;

/**
 * @ingroup los_config
 * Memory size
 */
#ifndef OS_SYS_MEM_SIZE
#define OS_SYS_MEM_SIZE                                     0x10000UL
#endif

#ifndef LOSCFG_MEMORY_BESTFIT
#define LOSCFG_MEMORY_BESTFIT                               YES
#endif

/**
 * @ingroup los_config
 * Configuration module tailoring of more mempry pool checking
 */
#ifndef LOSCFG_MEM_MUL_POOL
#define LOSCFG_MEM_MUL_POOL                                 NO
#endif

/**
 * @ingroup los_config
 * Configuration module tailoring of slab memory
 */
#ifndef LOSCFG_KERNEL_MEM_SLAB
#define LOSCFG_KERNEL_MEM_SLAB                              YES
#endif

/**
 * @ingroup los_config
 * Configuration module tailoring of mem node integrity checking
 */
#ifndef LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK
#define LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK                NO
#endif

/**
 * @ingroup los_config
 * Configuration module tailoring of mem node size checking
 */
#ifndef LOSCFG_BASE_MEM_NODE_SIZE_CHECK
#define LOSCFG_BASE_MEM_NODE_SIZE_CHECK                     YES
#endif

/**
 * @ingroup los_config
 * Configuration module momery alloc and free check
 */
#ifndef LOSCFG_MEM_ENABLE_ALLOC_CHECK
#define LOSCFG_MEM_ENABLE_ALLOC_CHECK                       YES
#endif

/**
 * @ingroup los_config
 * Number of memory checking blocks
 */
#ifndef OS_SYS_MEM_NUM
#define OS_SYS_MEM_NUM                                      20
#endif

/**
 * @ingroup los_config
 * Configuration heap memory peak statistics
 */
#ifndef LOSCFG_HEAP_MEMORY_PEAK_STATISTICS
#define LOSCFG_HEAP_MEMORY_PEAK_STATISTICS                  YES
#endif

/**
 * @ingroup los_config
 * Size of unaligned memory
 */
#ifndef OS_SYS_NOCACHEMEM_SIZE
#define OS_SYS_NOCACHEMEM_SIZE                              0x0UL
#endif

/**
 * @ingroup los_config
 * Starting address of the unaligned memory
 */
#if (OS_SYS_NOCACHEMEM_SIZE > 0)
extern UINT8 *g_sysNoCacheMem0;
#define OS_SYS_NOCACHEMEM_ADDR                              (&g_sysNoCacheMem0[0])
#endif


/* =============================================================================
                                        Exception module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for exception tailoring
 */
#ifndef LOSCFG_PLATFORM_EXC
#define LOSCFG_PLATFORM_EXC                                 NO
#endif

/**
 * @ingroup los_config
 * Configuration item for saveing exception info tailoring
 */
#ifndef LOSCFG_SAVE_EXC_INFO
#define LOSCFG_SAVE_EXC_INFO                                NO
#endif

#if(LOSCFG_PLATFORM_EXC == NO && LOSCFG_SAVE_EXC_INFO == YES)
    #error "save exception info need support platform exception, should make LOSCFG_PLATFORM_EXC = YES"
#endif

/* =============================================================================
                                       MPU module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for MPU
 */
#ifndef LOSCFG_BASE_CORE_MPU
#define LOSCFG_BASE_CORE_MPU                                NO
#endif

/**
 * @ingroup los_config
   * MPU support number : MPU maximum number of region support(According to the cotex-m4 authority Guide)
 */
#ifndef LOSCFG_MPU_MAX_SUPPORT
#define LOSCFG_MPU_MAX_SUPPORT                              8
#endif

/**
 * @ingroup los_config
   * MPU support address range : from LOSCFG_MPU_MIN_ADDRESS to LOSCFG_MPU_MAX_ADDRESS
 */
#ifndef LOSCFG_MPU_MIN_ADDRESS
#define LOSCFG_MPU_MIN_ADDRESS                              0x0UL           // Minimum protected address
#endif

#ifndef LOSCFG_MPU_MAX_ADDRESS
#define LOSCFG_MPU_MAX_ADDRESS                              0xFFFFFFFFUL    // Maximum protected address
#endif

/* =============================================================================
                                       Runstop module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for runstop module tailoring
 */
#ifndef LOSCFG_KERNEL_RUNSTOP
#define LOSCFG_KERNEL_RUNSTOP                               YES
#endif

#ifndef LOSCFG_RUNSTOP_THRESHOLD
#define LOSCFG_RUNSTOP_THRESHOLD                            2
#endif

/* =============================================================================
                                            Perf module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for performance moniter unit
 */
#ifndef OS_INCLUDE_PERF
#define OS_INCLUDE_PERF                                     NO
#endif


/* =============================================================================
                                        CPUP configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for CPU usage tailoring
 */
#ifndef LOSCFG_BASE_CORE_CPUP
#define LOSCFG_BASE_CORE_CPUP                               NO
#endif

#ifndef LOSCFG_BASE_CORE_CPUP_HWI
#define LOSCFG_BASE_CORE_CPUP_HWI                           NO
#endif

#if(LOSCFG_BASE_CORE_TSK_MONITOR == NO && LOSCFG_BASE_CORE_CPUP == YES)
    #error "cpup need support task monitor, should make LOSCFG_BASE_CORE_TSK_MONITOR = YES"
#endif

/*=============================================================================
                                        FPB configuration
=============================================================================*/
#ifndef LOSCFG_BASE_CORE_FPB
#define LOSCFG_BASE_CORE_FPB                                NO
#endif


#ifndef LOSCFG_FPB_CONFIG_PCO
#define LOSCFG_FPB_CONFIG_PCO                               1
#endif

#if (LOSCFG_FPB_CONFIG_PCO > 1)
    #error "LOSCFG_FPB_CONFIG_PCO can only set 0 or 1!"
#endif


/* =============================================================================
                                       fw Interface configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for the monitoring of task communication
 */
#ifndef LOSCFG_COMPAT_CMSIS_FW
#define LOSCFG_COMPAT_CMSIS_FW                              NO
#endif


/* =============================================================================
                                       Shell module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration item for shell module tailoring
 */
#ifndef OS_INCLUDE_SHELL
#define OS_INCLUDE_SHELL                                    NO
#endif

/* =============================================================================
                                       Lib configurable feature configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration lib configurable feature to open
 */
#ifndef LOSCFG_LIB_CONFIGURABLE
#define LOSCFG_LIB_CONFIGURABLE                             NO
#endif

/* =============================================================================
                                       Test module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration test case to open
 */
#ifndef LOSCFG_TEST
#define LOSCFG_TEST                                         NO
#endif

/* =============================================================================
                                       LIBC module configuration
============================================================================= */
/**
 * @ingroup los_config
 * Configuration to support libc
 */
#ifndef LOSCFG_LIB_LIBC
#define LOSCFG_LIB_LIBC                                     NO
#endif

/* =============================================================================
                                       LiteOS kernel version configuration
============================================================================= */
/**
 * @ingroup los_config
 * Version number
 */
#ifndef LITEOS_VER
#endif

/**
 * @ingroup los_config
 * Configuration CMSIS_OS_VER
 */
#ifndef CMSIS_OS_VER
#define CMSIS_OS_VER                                        0
#endif

/**
 * @ingroup  los_config
 * @brief: Task start running function.
 *
 * @par Description:
 * This API is used to start a task.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param: None.
 *
 * @retval None.
 *
 * @par Dependency:
 * <ul><li>los_config.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID LOS_StartToRun(VOID);

/**
 * @ingroup  los_config
 * @brief: Test Task init function.
 *
 * @par Description:
 * This API is used to initialize Test Task.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param: None.
 *
 * @retval #LOS_OK                                  0:App_Task initialization success.
 *
 * @par Dependency:
 * <ul><li>los_config.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 LOS_TestInit(VOID);
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_CONFIG_H */
