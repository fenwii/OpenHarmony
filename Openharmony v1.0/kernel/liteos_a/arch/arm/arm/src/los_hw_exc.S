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

    .extern   g_losTask
    .extern   g_intCount
    .extern   g_curNestCount
    .extern   OsExcHandleEntry
    .extern   __svc_stack_top
    .extern   __exc_stack_top
    .extern   __stack_chk_guard
    .extern   OsRandomStackGuard
#ifdef LOSCFG_GDB
    .extern   OsUndefIncExcHandleEntry
#if __LINUX_ARM_ARCH__ >= 7
    .extern   OsPrefetchAbortExcHandleEntry
    .extern   OsDataAbortExcHandleEntry
#endif
#endif
    .extern OsArmSharedPageFault
    .extern OsArmA32SyscallHandle
    .extern LOS_Exit

    .global   _osExceptFiqHdl
    .global   _osExceptAddrAbortHdl
    .global   _osExceptDataAbortHdl
    .global   _osExceptPrefetchAbortHdl
    .global   _osExceptSwiHdl
    .global   _osExceptUndefInstrHdl
    .global   __stack_chk_guard_setup


    .fpu vfpv4

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

#ifdef LOSCFG_GDB
.macro GDB_HANDLE fun
    SUB     SP, SP, #12

    STMFD   SP!, {R0-R12}
    MRS     R1, SPSR
    STMFD   SP!, {R1}  @save spsr

    ADD     R0, SP, #14 * 4
    MOV     R3, LR  @save pc

    MRS     R1, CPSR
    MRS     R2, SPSR
    MOV     R4, SP

    ORR     R2, R2, #(CPSR_INT_DISABLE)
    MSR     CPSR_c, R2

    STR     SP, [R0]  @SP
    STR     LR, [R0, #4]  @LR
    STR     R3, [R0, #8]  @PC

    ORR     R1, R1, #(CPSR_INT_DISABLE)
    BIC     R1, R1, #OS_PSR_THUMB
    MSR     CPSR_c, R1
    MOV     R0, R4

    BL \fun

    ADD     SP, SP, #4
    LDMFD   SP!, {R0-R12}

    MOV     R0, SP
    ADD     SP, SP, #8

    LDR     R1, [R0, #8]  @get pc
    STMFD   SP!, {R1}

    AND     R1, R1, #0x03
    CMP     R1, #0
    BEQ     1f
    LDR     R1, [R0, #-14 * 4]
    ORR     R1, R1, #OS_PSR_THUMB
    B       2f
1:
    LDR     R1, [R0, #-14 * 4]

2:
    MSR     SPSR, R1

    LDR     R1, [R0, #-12 * 4]  @get R1
    STMFD   SP!, {R1}
    LDR     R1, [R0,#-13 * 4]  @get R0
    STMFD   SP!, {R1}

    LDMFD   SP!, {R0-R1, PC}^
.endm
#endif

@ Description: Stack-Protector Init
__stack_chk_guard_setup:
    PUSH    {FP, LR}
    BL      OsRandomStackGuard
    LDR     R1, =__stack_chk_guard
    MOV     R3, R0
    ORR     R2, R3, #0X80000000
    STR     R2, [R1]
    POP     {FP, PC}

@ Description: Undefined instruction exception handler
_osExceptUndefInstrHdl:
#ifdef LOSCFG_GDB
    GDB_HANDLE OsUndefIncExcHandleEntry
#else
                                                              @ LR offset to return from this exception:  0.
    STMFD   SP, {R0-R7}                                       @ Push working registers, but don`t change SP.

    MOV     R0, #OS_EXCEPT_UNDEF_INSTR                        @ Set exception ID to OS_EXCEPT_UNDEF_INSTR.

    B       _osExceptDispatch                                 @ Branch to global exception handler.

#endif

@ Description: Software interrupt exception handler
_osExceptSwiHdl:
    SUB     SP, SP, #(4 * 16)
    STMIA   SP, {R0-R12}
    MRS     R3, SPSR
    MOV     R4, LR

    AND     R1, R3, #CPSR_MASK_MODE                          @ Interrupted mode
    CMP     R1, #CPSR_USER_MODE                              @ User mode
    BNE     OsKernelSVCHandler                               @ Branch if not user mode

    @ we enter from user mode, we need get the values of  USER mode r13(sp) and r14(lr).
    @ stmia with ^ will return the user mode registers (provided that r15 is not in the register list).
    MOV     R0, SP
    STMFD   SP!, {R3}                                        @ Save the CPSR
    ADD     R3, SP, #(4 * 17)                                @ Offset to pc/cpsr storage
    STMFD   R3!, {R4}                                        @ Save the CPSR and r15(pc)
    STMFD   R3, {R13, R14}^                                  @ Save user mode r13(sp) and r14(lr)
    SUB     SP, SP, #4
    PUSH_FPU_REGS R1

    MOV     FP, #0                                           @ Init frame pointer
    CPSIE   I
    BLX     OsArmA32SyscallHandle
    CPSID   I

    POP_FPU_REGS R1
    ADD     SP, SP,#4
    LDMFD   SP!, {R3}                                        @ Fetch the return SPSR
    MSR     SPSR_cxsf, R3                                    @ Set the return mode SPSR

    @ we are leaving to user mode, we need to restore the values of USER mode r13(sp) and r14(lr).
    @ ldmia with ^ will return the user mode registers (provided that r15 is not in the register list)

    LDMFD   SP!, {R0-R12}
    LDMFD   SP, {R13, R14}^                                  @ Restore user mode R13/R14
    ADD     SP, SP, #(2 * 4)
    LDMFD   SP!, {PC}^                                       @ Return to user

OsKernelSVCHandler:
    ADD     R0, SP, #(4 * 16)
    MOV     R5, R0
    STMFD   R0!, {R4}                                        @ Store PC
    STMFD   R0!, {R4}
    STMFD   R0!, {R5}

    STMFD   SP!, {R3}                                        @ Push task`s CPSR (i.e. exception SPSR).
    SUB     SP, SP, #(4 * 2)                                 @ user sp and lr

    MOV     R0, #OS_EXCEPT_SWI                               @ Set exception ID to OS_EXCEPT_SWI.

    B       _osExceptionSwi                                  @ Branch to global exception handler.

@ Description: Prefectch abort exception handler
_osExceptPrefetchAbortHdl:
#ifdef LOSCFG_GDB
#if __LINUX_ARM_ARCH__ >= 7
    GDB_HANDLE OsPrefetchAbortExcHandleEntry
#endif
#else
    SUB     LR, LR, #4                                       @ LR offset to return from this exception: -4.
    STMFD   SP, {R0-R7}                                      @ Push working registers, but don`t change SP.
    MOV     R5, LR
    MRS     R1, SPSR

    MOV     R0, #OS_EXCEPT_PREFETCH_ABORT                    @ Set exception ID to OS_EXCEPT_PREFETCH_ABORT.

    AND     R4, R1, #CPSR_MASK_MODE                          @ Interrupted mode
    CMP     R4, #CPSR_USER_MODE                              @ User mode
    BEQ     _osExcPageFault                                   @ Branch if user mode

_osKernelExceptPrefetchAbortHdl:
    MOV     LR, R5
    B       _osExceptDispatch                                @ Branch to global exception handler.
#endif

@ Description: Data abort exception handler
_osExceptDataAbortHdl:
#ifdef LOSCFG_GDB
#if __LINUX_ARM_ARCH__ >= 7
    GDB_HANDLE OsDataAbortExcHandleEntry
#endif
#else
    SUB     LR, LR, #8                                       @ LR offset to return from this exception: -8.
    STMFD   SP, {R0-R7}                                      @ Push working registers, but don`t change SP.
    MOV     R5, LR
    MRS     R1, SPSR

    MOV     R0, #OS_EXCEPT_DATA_ABORT                        @ Set exception ID to OS_EXCEPT_DATA_ABORT.

    B     _osExcPageFault
#endif

@ Description: Address abort exception handler
_osExceptAddrAbortHdl:
    SUB     LR, LR, #8                                       @ LR offset to return from this exception: -8.
    STMFD   SP, {R0-R7}                                      @ Push working registers, but don`t change SP.

    MOV     R0, #OS_EXCEPT_ADDR_ABORT                        @ Set exception ID to OS_EXCEPT_ADDR_ABORT.

    B       _osExceptDispatch                                @ Branch to global exception handler.

@ Description: Fast interrupt request exception handler
_osExceptFiqHdl:
    SUB     LR, LR, #4                                       @ LR offset to return from this exception: -4.
    STMFD   SP, {R0-R7}                                      @ Push working registers.

    MOV     R0, #OS_EXCEPT_FIQ                               @ Set exception ID to OS_EXCEPT_FIQ.

    B       _osExceptDispatch                                @ Branch to global exception handler.

_osExcPageFault:
    SUB     R3, SP, #(8 * 4)                                 @ Save the start address of working registers.
    MSR     CPSR_c, #(CPSR_INT_DISABLE | CPSR_SVC_MODE)      @ Switch to SVC mode, and disable all interrupts
    MOV     R2, SP
    STMFD   SP!, {R5}                                        @ Push original PC
    STMFD   SP!, {LR}                                        @ Push original svc LR
    STMFD   SP!, {R2}                                        @ Push original svc SP
    STMFD   SP!, {R8-R12}                                    @ Push original R12-R8,
    LDMFD   R3!, {R4-R11}                                    @ Move original R7-R0 from exception stack to original stack.
    STMFD   SP!, {R4-R11}
    STMFD   SP!, {R1}
    SUB     SP, SP, #8
    STMIA   SP, {R13, R14}^                                  @ Save user mode r13(sp) and r14(lr)

    MOV     R4, SP
    BIC     SP, SP, #7
    PUSH_FPU_REGS R1

    CMP     R0, #OS_EXCEPT_DATA_ABORT
    BNE     1f
    MRC     P15, 0, R2, C6, C0, 0
    MRC     P15, 0, R3, C5, C0, 0
    B       2f
1:  MRC     P15, 0, R2, C6, C0, 2
    MRC     P15, 0, R3, C5, C0, 1

2:  MOV     R1, R4
    MOV     R5, R0
    MOV     R8, R2
    MOV     R9, R3
    CPSIE   I
    BLX     OsArmSharedPageFault
    CPSID   I

    POP_FPU_REGS R1
    MOV     SP, R4
    CMP     R0, #0
    BEQ     _OsExcReturn

    MOV     R0, R5                                           @ exc type
    B       _osExceptionSwi

@ Description: Exception handler
@ Parameter  : R0     Exception Type
@ Regs Hold  : R3     Exception`s CPSR
_osExceptDispatch:
    MRS     R2, SPSR                                         @ Save CPSR before exception.
    MOV     R1, LR                                           @ Save PC before exception.
    SUB     R3, SP, #(8 * 4)                                 @ Save the start address of working registers.

    MSR     CPSR_c, #(CPSR_INT_DISABLE | CPSR_SVC_MODE)      @ Switch to SVC mode, and disable all interrupts
    MOV     R5, SP
    EXC_SP_SET __exc_stack_top, OS_EXC_STACK_SIZE, R6, R7

    STMFD   SP!, {R1}                                        @ Push Exception PC
    STMFD   SP!, {LR}                                        @ Push SVC LR
    STMFD   SP!, {R5}                                        @ Push SVC SP
    STMFD   SP!, {R8-R12}                                    @ Push original R12-R8,
    LDMFD   R3!, {R4-R11}                                    @ Move original R7-R0 from exception stack to original stack.
    STMFD   SP!, {R4-R11}
    STMFD   SP!, {R2}                                        @ Push task`s CPSR (i.e. exception SPSR).

    CMP     R0, #OS_EXCEPT_DATA_ABORT
    BNE     1f
    MRC     P15, 0, R8, C6, C0, 0
    MRC     P15, 0, R9, C5, C0, 0
    B       3f
1:  CMP     R0, #OS_EXCEPT_PREFETCH_ABORT
    BNE     2f
    MRC     P15, 0, R8, C6, C0, 2
    MRC     P15, 0, R9, C5, C0, 1
    B       3f
2:  MOV     R8, #0
    MOV     R9, #0

3:  AND     R2, R2, #CPSR_MASK_MODE
    CMP     R2, #CPSR_USER_MODE                              @ User mode
    BNE     4f
    STMFD   SP, {R13, R14}^                                  @ save user mode sp and lr
4:
    SUB     SP, SP, #(4 * 2)

_osExceptionSwi:
    MOV     R1, SP                                            @ The second argument to the exception

    MRC     P15, 0, R4, C0, C0, 5
    AND     R4, R4, #MPIDR_CPUID_MASK                         @ Get Current cpu id
    LSL     R2, R4, #2
    LDR     R3, =g_curNestCount                               @ if(g_curNestCount > 0) dump to _osExceptionGetSP
    ADD     R3, R3, R2
    LDR     R4, [R3]

    CMP     R4, #0
    BNE     _osExceptionGetSP

    LDR     R3, =g_intCount                                   @ Judge the exception is occur in task stack or system stack
    ADD     R3, R3, R2
    LDR     R4, [R3]

    CMP     R4, #0                                            @ if (g_intCount[ArchCurrCpuid()] > 0)
    BNE     _osExceptionGetSP                                 @ can not switch svc stack

    EXC_SP_SET __svc_stack_top, OS_EXC_SVC_STACK_SIZE, R6, R7 @ Switch to unified exception stack.
    ADD     R4, R4, #1
    STR     R4, [R3]

_osExceptionGetSP:
    MOV     R2, R8                                            @ far
    MOV     R3, R9                                            @ fsr
    LDR     R5, =OsExcHandleEntry                             @ OsExcHandleEntry(UINT32 excType, ExcContext * excBufAddr)
    BX      R5

_OsExcReturn:
    LDR     R0, [SP, #(2 * 4)]
    AND     R0, R0,  #CPSR_MASK_MODE
    CMP     R0, #CPSR_USER_MODE                               @ User mode
    BNE     _OsExcReturnToKernel
    LDMFD   SP, {R13, R14}^                                   @ load user mode sp and lr

_OsExcReturnToKernel:
    ADD     SP, SP, #(2 * 4)
    LDMFD   SP!, {R1}
    MSR     SPSR_cxsf, R1                                     @ Set the return mode SPSR
    LDMFD   SP!, {R0-R12}
    ADD     SP, SP, #4
    LDMFD   SP!, {LR, PC}^

    .end
