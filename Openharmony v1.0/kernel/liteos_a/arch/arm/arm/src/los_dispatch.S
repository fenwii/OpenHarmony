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

#include "asm.h"
#include "arch_config.h"

#ifdef LOSCFG_KERNEL_SMP_LOCKDEP
    .extern   OsLockDepCheckOut
#endif
    .extern   g_taskSpin
    .extern   g_percpu
    .global   OsStartToRun
    .global   OsTaskSchedule
    .global   OsIrqHandler
    .global   ArchSpinUnlock
    .global   OsSchedToUserSpinUnlock

    .equ OS_TASK_STATUS_RUNNING,       0x0010U
    .equ OS_PERCPU_STRUCT_SIZE,        0x28U
    .equ OS_PERCPU_TASK_LOCK_OFFSET,   0x14U
    .fpu vfpv4

/* macros to align and unalign the stack on 8 byte boundary for ABI compliance */
.macro STACK_ALIGN, reg
    MOV     \reg, sp
    TST     SP, #4
    SUBEQ   SP, #4
    PUSH    { \reg }
.endm

.macro STACK_RESTORE, reg
    POP     { \reg }
    MOV     sp, \reg
.endm

/* macros to save and restore fpu regs */
.macro PUSH_FPU_REGS reg1
#if !defined(LOSCFG_ARCH_FPU_DISABLE)
    VMRS    \reg1, FPEXC
    PUSH    {\reg1}
    VMRS    \reg1, FPSCR
    PUSH    {\reg1}
#if defined(LOSCFG_ARCH_FPU_VFP_D32)
    VPUSH   {D16-D31}
#endif
    VPUSH   {D0-D15}
#endif
.endm

.macro POP_FPU_REGS reg1
#if !defined(LOSCFG_ARCH_FPU_DISABLE)
    VPOP    {D0-D15}
#if defined(LOSCFG_ARCH_FPU_VFP_D32)
    VPOP    {D16-D31}
#endif
    POP     {\reg1}
    VMSR    FPSCR, \reg1
    POP     {\reg1}
    VMSR    FPEXC, \reg1
#endif
.endm

/* R0: new task */
OsStartToRun:

    MSR     CPSR_c, #(CPSR_INT_DISABLE | CPSR_SVC_MODE)

    LDRH    R1, [R0, #4]
    ORR     R1, #OS_TASK_STATUS_RUNNING
    STRH    R1, [R0, #4]

    /* R0 is new task, save it on tpidrprw */
    MCR     p15, 0, R0, c13, c0, 4
    ISB

    VPUSH   {S0}                                     /* fpu */
    VPOP    {S0}
    VPUSH   {D0}
    VPOP    {D0}

    B       OsTaskContextLoad

/*
 * R0: new task
 * R1: run task
 */
OsTaskSchedule:
    MRS      R2, CPSR
    STMFD    SP!, {LR}
    STMFD    SP!, {LR}
    /* jump sp */
    SUB      SP, SP, #4

    /* push r0-r12*/
    STMFD    SP!, {R0-R12}
    STMFD    SP!, {R2}

    /* 8 bytes stack align */
    SUB      SP, SP, #4

    /* save fpu registers */
    PUSH_FPU_REGS   R2

    /* store sp on running task */
    STR     SP, [R1]

OsTaskContextLoad:
    /* clear the flag of ldrex */
    CLREX

    /* switch to new task's sp */
    LDR     SP, [R0]

    /* restore fpu registers */
    POP_FPU_REGS    R2

    /* 8 bytes stack align */
    ADD     SP, SP, #4

    LDMFD   SP!, {R0}
    MOV     R4, R0
    AND     R0, R0, #CPSR_MASK_MODE
    CMP     R0, #CPSR_USER_MODE
    BNE     OsKernelTaskLoad

#ifdef LOSCFG_KERNEL_SMP
#ifdef LOSCFG_KERNEL_SMP_LOCKDEP
    /* 8 bytes stack align */
    SUB     SP, SP, #4
    LDR     R0, =g_taskSpin
    BL      OsLockDepCheckOut
    ADD     SP, SP, #4
#endif
    /* R0 = &g_taskSpin.rawLock */
    LDR     R0, =g_taskSpin
    BL      ArchSpinUnlock
    LDR     R2, =g_percpu
    MRC     P15, 0, R3, C0, C0, 5
    UXTB    R3, R3
    MOV     R1, #OS_PERCPU_STRUCT_SIZE
    MLA     R3, R1, R3, R2
    MOV     R2, #0
    STR     R2, [R3, #OS_PERCPU_TASK_LOCK_OFFSET]
#endif

    MVN     R3, #CPSR_INT_DISABLE
    AND     R4, R4, R3
    MSR     SPSR_cxsf, R4

    /* restore r0-r12, lr */
    LDMFD   SP!, {R0-R12}
    LDMFD   SP, {R13, R14}^
    ADD     SP, SP, #(2 * 4)
    LDMFD   SP!, {PC}^

OsKernelTaskLoad:
    MSR     SPSR_cxsf, R4
    /* restore r0-r12, lr */
    LDMFD   SP!, {R0-R12}
    ADD     SP, SP, #4
    LDMFD   SP!, {LR, PC}^

OsIrqHandler:
    SUB     LR, LR, #4

    /* push r0-r3 to irq stack */
    STMFD   SP, {R0-R3}
    SUB     R0, SP, #(4 * 4)
    MRS     R1, SPSR
    MOV     R2, LR

    /* disable irq, switch to svc mode */
    CPSID   i, #0x13

    /* push spsr and pc in svc stack */
    STMFD   SP!, {R1, R2}
    STMFD   SP, {LR}

    AND     R3, R1, #CPSR_MASK_MODE
    CMP     R3, #CPSR_USER_MODE
    BNE     OsIrqFromKernel

    /* push user sp, lr in svc stack */
    STMFD   SP, {R13, R14}^

OsIrqFromKernel:
    /* from svc not need save sp and lr */
    SUB     SP, SP, #(2 * 4)

    /* pop r0-r3 form irq stack*/
    LDMFD   R0, {R0-R3}

    /* push caller saved regs as trashed regs in svc stack */
    STMFD   SP!, {R0-R3, R12}

    /* 8 bytes stack align */
    SUB     SP, SP, #4

    /*
     * save fpu regs in case in case those been
     * altered in interrupt handlers.
     */
    PUSH_FPU_REGS   R0
#ifdef LOSCFG_IRQ_USE_STANDALONE_STACK
    PUSH    {R4}
    MOV     R4, SP
    EXC_SP_SET __svc_stack_top, OS_EXC_SVC_STACK_SIZE, R1, R2
#endif

    BLX     HalIrqHandler

#ifdef LOSCFG_IRQ_USE_STANDALONE_STACK
    MOV     SP, R4
    POP     {R4}
#endif

    /* process pending signals */
    BL      OsTaskProcSignal

    /* check if needs to schedule */
    CMP     R0, #0
    BLNE    OsSchedPreempt

    MOV     R0,SP
    MOV     R1,R7
    BL      OsSaveSignalContextIrq

    /* restore fpu regs */
    POP_FPU_REGS    R0

    ADD     SP, SP, #4

OsIrqContextRestore:
    LDR     R0, [SP, #(4 * 7)]
    MSR     SPSR_cxsf, R0
    AND     R0, R0, #CPSR_MASK_MODE
    CMP     R0, #CPSR_USER_MODE

    LDMFD   SP!, {R0-R3, R12}

    BNE     OsIrqContextRestoreToKernel

    /* load user sp and lr, and jump cpsr */
    LDMFD   SP, {R13, R14}^
    ADD     SP, SP, #(3 * 4)

    /* return to user mode */
    LDMFD   SP!, {PC}^

OsIrqContextRestoreToKernel:
    /* svc mode not load sp */
    ADD     SP, SP, #4
    LDMFD   SP!, {LR}
    /* jump cpsr and return to svc mode */
    ADD     SP, SP, #4
    LDMFD   SP!, {PC}^

FUNCTION(ArchSpinLock)
    mov     r1, #1
1:
    ldrex   r2, [r0]
    cmp     r2, #0
    wfene
    strexeq r2, r1, [r0]
    cmpeq   r2, #0
    bne     1b
    dmb
    bx      lr

FUNCTION(ArchSpinTrylock)
    mov     r1, #1
    mov     r2, r0
    ldrex   r0, [r2]
    cmp     r0, #0
    strexeq r0, r1, [r2]
    dmb
    bx      lr

FUNCTION(ArchSpinUnlock)
    mov     r1, #0
    dmb
    str     r1, [r0]
    dsb
    sev
    bx      lr
