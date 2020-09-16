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

 .syntax unified
 .arch armv7e-m
 .thumb
 .fpu vfpv4
//;.arch_extension sec



.equ    OS_NVIC_INT_CTRL,            0xE000ED04
.equ    OS_NVIC_SYSPRI2,             0xE000ED20
.equ    OS_NVIC_PENDSV_PRI,          0xF0F00000
.equ    OS_NVIC_PENDSVSET,           0x10000000
.equ    OS_TASK_STATUS_RUNNING,      0x0010

    .section .text
    .thumb

    .type LOS_StartToRun, %function
    .global LOS_StartToRun

LOS_StartToRun:
    .fnstart
    .cantunwind

    ldr     r4, =OS_NVIC_SYSPRI2
    ldr     r5, =OS_NVIC_PENDSV_PRI
    str     r5, [r4]

    ldr     r0, =g_taskScheduled
    mov     r1, #1
    str     r1, [r0]

    mov     r0, #2
    msr     CONTROL, r0


    ldr     r0, =g_losTask
    ldr     r2, [r0, #4]
    ldr     r0, =g_losTask
    str     r2, [r0]

    ldr     r3, =g_losTask
    ldr     r0, [r3]
    ldrh    r7, [r0 , #4]
    mov     r8,  #OS_TASK_STATUS_RUNNING
    orr     r7,  r7,  r8
    strh    r7,  [r0 , #4]

    ldr     r12, [r0]
    add     r12, r12, #100

    ldmfd   r12!, {r0-r7}
    add     r12, r12, #72
    msr     psp, r12
    vpush    {S0}
    vpop     {S0}
    mov     lr, r5
    //MSR     xPSR, R7

    cpsie   I
    bx      r6

    .fnend


    .type LOS_IntLock, %function
    .global LOS_IntLock
LOS_IntLock:
    .fnstart
    .cantunwind

    MRS R0, PRIMASK
    CPSID I
    BX LR
    .fnend

    .type LOS_IntUnLock, %function
    .global LOS_IntUnLock
LOS_IntUnLock:
    .fnstart
    .cantunwind

    MRS R0, PRIMASK
    CPSIE I
    BX LR
    .fnend

    .type LOS_IntRestore, %function
    .global LOS_IntRestore
LOS_IntRestore:
    .fnstart
    .cantunwind

    MSR PRIMASK, R0
    BX LR
    .fnend

    .type osTaskSchedule, %function
    .global osTaskSchedule
osTaskSchedule:
    .fnstart
    .cantunwind

    ldr     r0, =OS_NVIC_INT_CTRL
    ldr     r1, =OS_NVIC_PENDSVSET
    str     r1, [r0]
    bx      lr
   .fnend




    .type osPendSV, %function
    .global osPendSV
osPendSV:
    .fnstart
    .cantunwind

    mrs     r12, PRIMASK
    cpsid   I

    ldr     r2, =g_taskSwitchHook
    ldr     r2, [r2]
    cbz     r2, TaskSwitch
    push    {r12, lr}
    blx     r2
    pop     {r12, lr}

TaskSwitch:

    mrs     r0, psp

    stmfd   r0!, {r4-r12}

    vstmdb   r0!, {d8-d15}
    ldr     r5, =g_losTask
    ldr     r6, [r5]
    str     r0, [r6]


    ldrh    r7, [r6 , #4]
    mov     r8,#OS_TASK_STATUS_RUNNING
    bic     r7, r7, r8
    strh    r7, [r6 , #4]


    ldr     r0, =g_losTask
    ldr     r0, [r0, #4]
    str     r0, [r5]


    ldrh    r7, [r0 , #4]
    mov     r8,  #OS_TASK_STATUS_RUNNING
    orr     r7, r7, r8
    strh    r7,  [r0 , #4]

    ldr     r1,   [r0]

    vldmia   r1!, {d8-d15}
    ldmfd   r1!, {r4-r12}
    msr     psp,  r1

    msr     PRIMASK, r12


    bx      lr
    .fnend

