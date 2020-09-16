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

#ifndef _ARCH_CONFIG_H
#define _ARCH_CONFIG_H

#include "menuconfig.h"

#define CPSR_INT_DISABLE         0xC0 /* Disable both FIQ and IRQ */
#define CPSR_IRQ_DISABLE         0x80 /* IRQ disabled when =1 */
#define CPSR_FIQ_DISABLE         0x40 /* FIQ disabled when =1 */
#define CPSR_THUMB_ENABLE        0x20 /* Thumb mode when   =1 */
#define CPSR_USER_MODE           0x10
#define CPSR_FIQ_MODE            0x11
#define CPSR_IRQ_MODE            0x12
#define CPSR_SVC_MODE            0x13
#define CPSR_ABT_MODE            0x17
#define CPSR_UNDEF_MODE          0x1B
#define CPSR_MASK_MODE           0x1F

/* Define exception type ID */
#define OS_EXCEPT_RESET          0x00
#define OS_EXCEPT_UNDEF_INSTR    0x01
#define OS_EXCEPT_SWI            0x02
#define OS_EXCEPT_PREFETCH_ABORT 0x03
#define OS_EXCEPT_DATA_ABORT     0x04
#define OS_EXCEPT_FIQ            0x05
#define OS_EXCEPT_ADDR_ABORT     0x06
#define OS_EXCEPT_IRQ            0x07

/* Define core num */
#ifdef LOSCFG_KERNEL_SMP
#define CORE_NUM                 LOSCFG_KERNEL_SMP_CORE_NUM
#else
#define CORE_NUM                 1
#endif

/* Initial bit32 stack value. */
#define OS_STACK_INIT            0xCACACACA
/* Bit32 stack top magic number. */
#define OS_STACK_MAGIC_WORD      0xCCCCCCCC

#ifdef LOSCFG_GDB
#define OS_EXC_UNDEF_STACK_SIZE  512
#define OS_EXC_ABT_STACK_SIZE    512
#else
#define OS_EXC_UNDEF_STACK_SIZE  40
#define OS_EXC_ABT_STACK_SIZE    40
#endif
#define OS_EXC_FIQ_STACK_SIZE    64
#define OS_EXC_IRQ_STACK_SIZE    64
#define OS_EXC_SVC_STACK_SIZE    0x2000
#define OS_EXC_STACK_SIZE        0x1000

#define REG_R0   0
#define REG_R1   1
#define REG_R2   2
#define REG_R3   3
#define REG_R4   4
#define REG_R5   5
#define REG_R6   6
#define REG_R7   7
#define REG_R8   8
#define REG_R9   9
#define REG_R10  10
#define REG_R11  11
#define REG_R12  12
#define REG_R13  13
#define REG_R14  14
#define REG_R15  15
#define REG_CPSR 16
#define REG_SP   REG_R13
#define REG_LR   REG_R14
#define REG_PC   REG_R15
#endif