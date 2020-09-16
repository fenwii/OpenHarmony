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

.syntax unified
.arm

// errno_t _arm_put_user(void *dst, const void *src, size_t dstTypeLen, size_t srcTypeLen)
FUNCTION(_arm_put_user)
    stmdb   sp!, {r0, r1, r2, r3, lr}
    cmp     r2, #0
    beq     .Lget_user_return
    cmp     r2, r3
    bne     .Lget_user_err
    cmp     r2, #1
    bhi     .Lget_user_half
.Lget_user_byte:
0:  ldrb    r3, [r1], #0
1:  strbt   r3, [r0], #0
    b       .Lget_user_return
.Lget_user_half:
    cmp     r2, #2
    bhi     .Lget_user_word
2:  ldrh    r3, [r1], #0
3:  strht   r3, [r0], #0
    b       .Lget_user_return
.Lget_user_word:
    cmp     r2, #4
    bhi     .Lget_user_err
4:  ldr    r3, [r1], #0
5:  strt   r3, [r0], #0
.Lget_user_return:
    ldmia   sp!, {r0, r1, r2, r3, lr}
    mov     r0, 0
    bx      lr
.Lget_user_err:
    ldmia   sp!, {r0, r1, r2, r3, lr}
    mov     r0, #-14
    bx      lr

.pushsection __exc_table, "a"
    .long   0b,  .Lget_user_err
    .long   1b,  .Lget_user_err
    .long   2b,  .Lget_user_err
    .long   3b,  .Lget_user_err
    .long   4b,  .Lget_user_err
    .long   5b,  .Lget_user_err
.popsection
