/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
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
 */

#ifndef _LOS_EXC_H
#define _LOS_EXC_H

#include "los_hwi.h"
#include "los_task_pri.h"
#include "los_queue.h"
#include "los_memcheck.h"
#include "los_sys_pri.h"
#ifdef LOSCFG_LIB_LIBC
#include "string.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define OS_EXC_IN_INIT                      0
#define OS_EXC_IN_TASK                      1
#define OS_EXC_IN_HWI                       2

#define OS_EXC_MAX_BUF_LEN                  25
#define OS_EXC_MAX_NEST_DEPTH               1

#define OS_NVIC_SHCSR                       0xE000ED24
#define OS_NVIC_CCR                         0xE000ED14

#define OS_NVIC_INT_ENABLE_SIZE             0x20
#define OS_NVIC_INT_PRI_SIZE                0xF0
#define OS_NVIC_EXCPRI_SIZE          0xC

#define OS_NVIC_INT_PEND_SIZE               OS_NVIC_INT_ACT_SIZE
#define OS_NVIC_INT_ACT_SIZE                OS_NVIC_INT_ENABLE_SIZE

#define OS_EXC_FLAG_NO_FLOAT                0x10000000
#define OS_EXC_FLAG_FAULTADDR_VALID         0x01
#define OS_EXC_FLAG_IN_HWI                  0x02

#define OS_EXC_IMPRECISE_ACCESS_ADDR        0xABABABAB

/**
 *@ingroup los_exc
 * the struct of register files
 *
 * description: the register files that saved when exception triggered
 *
 * notes:the following register with prefix 'uw'  correspond to the registers in the cpu  data sheet.
 */
typedef struct tagExcContext {
    //handler save
#if ((defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)) && \
     (defined (__FPU_USED   ) && (__FPU_USED    == 1U))     )
    UINT32 S16;
    UINT32 S17;
    UINT32 S18;
    UINT32 S19;
    UINT32 S20;
    UINT32 S21;
    UINT32 S22;
    UINT32 S23;
    UINT32 S24;
    UINT32 S25;
    UINT32 S26;
    UINT32 S27;
    UINT32 S28;
    UINT32 S29;
    UINT32 S30;
    UINT32 S31;
#endif
    UINT32 uwR4;
    UINT32 uwR5;
    UINT32 uwR6;
    UINT32 uwR7;
    UINT32 uwR8;
    UINT32 uwR9;
    UINT32 uwR10;
    UINT32 uwR11;
    UINT32 uwPriMask;
    //auto save
    UINT32 uwSP;
    UINT32 uwR0;
    UINT32 uwR1;
    UINT32 uwR2;
    UINT32 uwR3;
    UINT32 uwR12;
    UINT32 uwLR;
    UINT32 uwPC;
    UINT32 uwxPSR;
#if ((defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)) && \
     (defined (__FPU_USED) && (__FPU_USED== 1U)))
    UINT32 S0;
    UINT32 S1;
    UINT32 S2;
    UINT32 S3;
    UINT32 S4;
    UINT32 S5;
    UINT32 S6;
    UINT32 S7;
    UINT32 S8;
    UINT32 S9;
    UINT32 S10;
    UINT32 S11;
    UINT32 S12;
    UINT32 S13;
    UINT32 S14;
    UINT32 S15;
    UINT32 FPSCR;
    UINT32 NO_NAME;
#endif
}EXC_CONTEXT_S;

typedef UINT32 (*EXC_INFO_SAVE_CALLBACK)(UINT32, VOID*);
typedef VOID (*EXC_PROC_FUNC)(UINT32, EXC_CONTEXT_S *);
VOID OsExcHandleEntry(UINT32 excType, UINT32 faultAddr, UINT32 pid, EXC_CONTEXT_S *excBufAddr);

/**
 * @ingroup  los_hwi
 * @brief: Exception initialization.
 *
 * @par Description:
 * This API is used to configure the exception function vector table.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 *@param uwArraySize [IN] Memory size of exception.
 *
 * @retval: None
 * @par Dependency:
 * <ul><li>los_hwi.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
VOID OsExcInit(UINT32 uwArraySize);

extern VOID OsExcNMI(VOID);
extern VOID OsExcHardFault(VOID);
extern VOID OsExcMemFault(VOID);
extern VOID OsExcBusFault(VOID);
extern VOID OsExcUsageFault(VOID);
extern VOID OsExcSvcCall(VOID);
extern VOID OsBackTrace(VOID);
extern UINT8 g_aucTaskArray[];

/**
 *@ingroup los_exc
 *@brief Kernel panic function.
 *
 *@par Description:
 *Stack function that prints kernel panics.
 *@attention After this function is called and stack information is printed, the system will fail to respond.
 *@attention The input parameter can be NULL.
 *@param fmt [IN] Type #char* : variadic argument.
 *
 *@retval #None.
 *
 *@par Dependency:
 *los_exc.h: the header file that contains the API declaration.
 *@see None.
*/
VOID LOS_Panic(const CHAR *fmt, ...);

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:总线状态寄存器入栈时发生错误
 */
#define OS_EXC_BF_STKERR           1

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:总线状态寄存器出栈时发生错误
 */
#define OS_EXC_BF_UNSTKERR         2

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:总线状态寄存器不精确的数据访问违例
 */
#define OS_EXC_BF_IMPRECISERR      3

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:总线状态寄存器精确的数据访问违例
 */
#define OS_EXC_BF_PRECISERR        4

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:总线状态寄存器取指时的访问违例
 */
#define OS_EXC_BF_IBUSERR          5

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:存储器管理状态寄存器入栈时发生错误
 */
#define OS_EXC_MF_MSTKERR          6

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:存储器管理状态寄存器出栈时发生错误
 */
#define OS_EXC_MF_MUNSTKERR        7

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:存储器管理状态寄存器数据访问违例
 */
#define OS_EXC_MF_DACCVIOL         8

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:存储器管理状态寄存器取指访问违例
 */
#define OS_EXC_MF_IACCVIOL         9


/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:用法错误，表示除法运算时除数为零
 */
#define OS_EXC_UF_DIVBYZERO        10

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:用法错误，未对齐访问导致的错误
 */
#define OS_EXC_UF_UNALIGNED        11

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:用法错误，试图执行协处理器相关指令
 */
#define OS_EXC_UF_NOCP             12

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:用法错误，在异常返回时试图非法地加载EXC_RETURN到PC
 */
#define OS_EXC_UF_INVPC            13

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:用法错误，试图切入ARM状态
 */
#define OS_EXC_UF_INVSTATE         14

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:用法错误，执行的指令其编码是未定义的——解码不能
 */
#define OS_EXC_UF_UNDEFINSTR       15

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:NMI中断
 */

#define OS_EXC_CAUSE_NMI           16

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:硬fault
 */
#define OS_EXC_CAUSE_HARDFAULT     17

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:任务处理函数退出
 */
#define OS_EXC_CAUSE_TASK_EXIT     18

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:致命错误
 */
#define OS_EXC_CAUSE_FATAL_ERR     19

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:调试事件导致的硬fault
 */
#define OS_EXC_CAUSE_DEBUGEVT      20

/**
 *@ingroup los_exc
 *Cortex-M3异常具体类型:取向量时发生的硬fault
 */
#define OS_EXC_CAUSE_VECTBL        21

/**
 *@ingroup los_exc
 * 异常信息结构体
 *
 * 描述:M4平台下的异常触发时保存的异常信息
 *
 */
typedef struct tagExcInfo {
    /**< 异常发生阶段： 0表示异常发生在初始化中，1表示异常发生在任务中，2表示异常发生在中断中 */
    UINT16 phase;
    /**< 异常类型,出异常时对照上面列出的1-19号 */
    UINT16 type;
    /**< 若为精确地址访问错误表示异常发生时的错误访问地址 */
    UINT32 faultAddr;
    /**< 在中断中发生异常，表示中断号。在任务中发生异常，表示任务id，如果发生在初始化中，则为0xffffffff */
    UINT32 thrdPid;
    /**< 异常嵌套个数，目前仅支持第一次进入异常时执行注册的钩子函数 */
    UINT16 nestCnt;
    /**< 保留 */
    UINT16 reserved;
    /**< 自动压栈浮点寄存器的异常发生时刻的硬件上下文 */
    EXC_CONTEXT_S * context;
} ExcInfo;

extern UINT32 g_curNestCount;
extern UINT32 g_vuwIntCount;

static VOID OsExcSave2DDR(VOID);
VOID OsExcInfoDisplay(ExcInfo *exc);


extern TaskSwitchInfo g_taskSwitchInfo;
extern UINT8 g_uwExcTbl[32];

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _LOS_EXC_H */

