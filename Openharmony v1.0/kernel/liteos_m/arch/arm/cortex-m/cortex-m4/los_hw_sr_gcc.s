;
; Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
; Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
;
; Redistribution and use in source and binary forms, with or without modification,
; are permitted provided that the following conditions are met:
;
; 1. Redistributions of source code must retain the above copyright notice, this list of
;    conditions and the following disclaimer.
;
; 2. Redistributions in binary form must reproduce the above copyright notice, this list
;    of conditions and the following disclaimer in the documentation and/or other materials
;    provided with the distribution.
;
; 3. Neither the name of the copyright holder nor the names of its contributors may be used
;    to endorse or promote products derived from this software without specific prior written
;    permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
; "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
; THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
; PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
; CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
; EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
; WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
; OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
; ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;

 .syntax unified
 .arch armv7e-m
 .thumb
 .fpu vfpv4


    .extern g_saveSRContext
    .extern g_saveAR
    .extern g_losTask

    .global OsSRSaveRegister
    .global OsSRRestoreRegister

    .section .text
    .thumb

        .type OsSRSaveRegister, %function
        .global OsSRSaveRegister
OsSRSaveRegister:
        .fnstart
        .cantunwind
        PUSH    {R2}
        LDR     R2, =g_saveAR
        STR     R0, [R2]
        STR     R1, [R2, #4]
        POP     {R2}

        MRS     R0, PSP

        VSTMDB  R0!, {D0-D7}
        VMRS    R1, FPSCR
        STMFD   R0!, {R1}       //FPSCR
        STMFD   R0!, {R1}       //NO_NAME

        MRS     R1,  PSR
        ORR     R1, R1, #0x01000000
        STMFD   R0!, {R1}

        MOV     R1,  LR
        STMFD   R0!, {R1}    // ;PC
        STMFD   R0!, {R1}    // ;LR

        STMFD   R0!, {R12}

        MOV      R12,  R0

        LDR     R0, =g_saveAR
        LDR     R0, [R0]
        LDR     R1, =g_saveAR
        LDR     R1, [R1, #4]

        STMFD   R12!, {R0-R3}
        STMFD   R12!, {R4-R11}
        VSTMDB  R12!, {D8-D15}

        MRS     R0,  CONTROL
        STMFD   R12!,  {R0}

        MRS     R0,  MSP
        STMFD   R12!,  {R0}

        LDR     R1, =g_losTask
        LDR     R1, [R1]
        STR     R12, [R1]

        MSR     PSP, R12
        BX      LR
        .fnend

        .type OsSRSaveRegister, %function
        .global OsSRSaveRegister
OsSRRestoreRegister:
        .fnstart
        .cantunwind
        MRS     R0, MSP
        ADD     R0, R0, #8
        MSR     MSP, R0

        LDR     R0, =g_losTask
        LDR     R0,  [R0]
        LDR     R12, [R0]

        LDR     R0, =g_saveSRContext
        ADD     R0, R0, #120
        MSR     PSP, R0

        LDMFD   R12!,{R0}
        MSR     MSP, R0

        LDMFD   R12!,{R0}
        MSR     CONTROL, R0

        VLDMIA  R12!,{D8-D15}
        LDMFD   R12!,{R4-R11}

        MSR     PSP, R12
        MOV     LR, #0xFFFFFFED
        BX      LR

        .fnend
