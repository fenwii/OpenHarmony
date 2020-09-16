/*	$NetBSD: memcpy_arm.S,v 1.1 2003/10/14 07:51:45 scw Exp $	*/

/*-
 * Copyright (c) 1997 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Neil A. Carson and Mark Brinicombe
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "asm.h"

// We do not need to check whether the addresses are in the
// kernel or virtual address spaces, since we only access them
// using user privileges.

.syntax unified
.arm

// size_t _arm_user_copy(void *dst, const void *src, size_t len)
FUNCTION(_arm_user_copy)
    /* save leaf functions having to store this away */
    stmdb   sp!, {r0, r1, r2, lr}       /* _arm_user_copy() returns dest addr */

    subs    r2, r2, #4
    blt     .Lmemcpy_l4         /* less than 4 bytes */
    ands    r12, r0, #3
    bne     .Lmemcpy_destul     /* oh unaligned destination addr */
    ands    r12, r1, #3
    bne     .Lmemcpy_srcul      /* oh unaligned source addr */

.Lmemcpy_t8:
    /* We have aligned source and destination */
    subs    r2, r2, #8
    blt     .Lmemcpy_l12        /* less than 12 bytes (4 from above) */
    subs    r2, r2, #0x14
    blt     .Lmemcpy_l32        /* less than 32 bytes (12 from above) */
    stmdb   sp!, {r4}           /* borrow r4 */

    /* blat 32 bytes at a time */
    /* XXX for really big copies perhaps we should use more registers */
.Lmemcpy_loop32:
0:  ldmia   r1!, {r3, r4, r12, lr}
1:  stmia   r0!, {r3, r4, r12, lr}
2:  ldmia   r1!, {r3, r4, r12, lr}
3:  stmia   r0!, {r3, r4, r12, lr}
    subs    r2, r2, #0x20
    bge     .Lmemcpy_loop32

    cmn     r2, #0x10
4:  ldmiage r1!, {r3, r4, r12, lr}  /* blat a remaining 16 bytes */
5:  stmiage r0!, {r3, r4, r12, lr}
    subge   r2, r2, #0x10
    ldmia   sp!, {r4}           /* return r4 */

.Lmemcpy_l32:
    adds    r2, r2, #0x14

    /* blat 12 bytes at a time */
.Lmemcpy_loop12:
6:  ldmiage r1!, {r3, r12, lr}
7:  stmiage r0!, {r3, r12, lr}
    subsge  r2, r2, #0x0c
    bge     .Lmemcpy_loop12

.Lmemcpy_l12:
    adds    r2, r2, #8
    blt     .Lmemcpy_l4

    subs    r2, r2, #4
8:  ldrlt   r3, [r1], #4
9:  strlt   r3, [r0], #4
10: ldmiage r1!, {r3, r12}
11: stmiage r0!, {r3, r12}
    subge   r2, r2, #4

.Lmemcpy_l4:
    /* less than 4 bytes to go */
    adds    r2, r2, #4
    beq     .Lmemcpy_return
    /* copy the crud byte at a time */
    cmp     r2, #2
12: ldrb    r3, [r1], #1
13: strb    r3, [r0], #1
14: ldrbge  r3, [r1], #1
15: strbge  r3, [r0], #1
16: ldrbgt  r3, [r1], #1
17: strbgt  r3, [r0], #1

.Lmemcpy_return:
    ldmia   sp!, {r0, r1, r2, lr}
    mov     r0, 0
    bx      lr

    /* erg - unaligned destination */
.Lmemcpy_destul:
    rsb     r12, r12, #4
    cmp     r12, #2

    /* align destination with byte copies */
18: ldrb    r3, [r1], #1
19: strb    r3, [r0], #1
20: ldrbge  r3, [r1], #1
21: strbge  r3, [r0], #1
22: ldrbgt  r3, [r1], #1
23: strbgt  r3, [r0], #1
    subs    r2, r2, r12
    blt     .Lmemcpy_l4         /* less the 4 bytes */

    ands    r12, r1, #3
    beq     .Lmemcpy_t8         /* we have an aligned source */

    /* erg - unaligned source */
    /* This is where it gets nasty ... */
.Lmemcpy_srcul:
    bic     r1, r1, #3
24: ldr     lr, [r1], #4
    cmp     r12, #2
    bgt     .Lmemcpy_srcul3
    beq     .Lmemcpy_srcul2
    cmp     r2, #0x0c
    blt     .Lmemcpy_srcul1loop4
    sub     r2, r2, #0x0c
    stmdb   sp!, {r4, r5}

.Lmemcpy_srcul1loop16:
    mov     r3, lr, lsr #8
25: ldmia   r1!, {r4, r5, r12, lr}
    orr     r3, r3, r4, lsl #24
    mov     r4, r4, lsr #8
    orr     r4, r4, r5, lsl #24
    mov     r5, r5, lsr #8
    orr     r5, r5, r12, lsl #24
    mov     r12, r12, lsr #8
    orr     r12, r12, lr, lsl #24
26: stmia   r0!, {r3-r5, r12}
    subs    r2, r2, #0x10
    bge     .Lmemcpy_srcul1loop16
    ldmia   sp!, {r4, r5}
    adds    r2, r2, #0x0c
    blt     .Lmemcpy_srcul1l4

.Lmemcpy_srcul1loop4:
    mov     r12, lr, lsr #8
27: ldr     lr, [r1], #4
    orr     r12, r12, lr, lsl #24
28: str     r12, [r0], #4
    subs    r2, r2, #4
    bge     .Lmemcpy_srcul1loop4

.Lmemcpy_srcul1l4:
    sub     r1, r1, #3
    b       .Lmemcpy_l4

.Lmemcpy_srcul2:
    cmp     r2, #0x0c
    blt     .Lmemcpy_srcul2loop4
    sub     r2, r2, #0x0c
    stmdb   sp!, {r4, r5}

.Lmemcpy_srcul2loop16:
    mov     r3, lr, lsr #16
29: ldmia   r1!, {r4, r5, r12, lr}
    orr     r3, r3, r4, lsl #16
    mov     r4, r4, lsr #16
    orr     r4, r4, r5, lsl #16
    mov     r5, r5, lsr #16
    orr     r5, r5, r12, lsl #16
    mov     r12, r12, lsr #16
    orr     r12, r12, lr, lsl #16
30: stmia   r0!, {r3-r5, r12}
    subs    r2, r2, #0x10
    bge     .Lmemcpy_srcul2loop16
    ldmia   sp!, {r4, r5}
    adds    r2, r2, #0x0c
    blt     .Lmemcpy_srcul2l4

.Lmemcpy_srcul2loop4:
    mov     r12, lr, lsr #16
31: ldr     lr, [r1], #4
    orr     r12, r12, lr, lsl #16
32: str     r12, [r0], #4
    subs    r2, r2, #4
    bge     .Lmemcpy_srcul2loop4

.Lmemcpy_srcul2l4:
    sub     r1, r1, #2
    b       .Lmemcpy_l4

.Lmemcpy_srcul3:
    cmp     r2, #0x0c
    blt     .Lmemcpy_srcul3loop4
    sub     r2, r2, #0x0c
    stmdb   sp!, {r4, r5}

.Lmemcpy_srcul3loop16:
    mov     r3, lr, lsr #24
33: ldmia   r1!, {r4, r5, r12, lr}
    orr     r3, r3, r4, lsl #8
    mov     r4, r4, lsr #24
    orr     r4, r4, r5, lsl #8
    mov     r5, r5, lsr #24
    orr     r5, r5, r12, lsl #8
    mov     r12, r12, lsr #24
    orr     r12, r12, lr, lsl #8
34: stmia   r0!, {r3-r5, r12}
    subs    r2, r2, #0x10
    bge     .Lmemcpy_srcul3loop16
    ldmia   sp!, {r4, r5}
    adds    r2, r2, #0x0c
    blt     .Lmemcpy_srcul3l4

.Lmemcpy_srcul3loop4:
    mov     r12, lr, lsr #24
35: ldr     lr, [r1], #4
    orr     r12, r12, lr, lsl #8
36: str     r12, [r0], #4
    subs    r2, r2, #4
    bge     .Lmemcpy_srcul3loop4

.Lmemcpy_srcul3l4:
    sub     r1, r1, #1
    b       .Lmemcpy_l4

.Lfix_return1:
    ldmia   sp!, {r4}
.Lfix_return2:
    ldmia   sp!, {r0, r1}
    cmp     r0, r1
    bhs     .Lfix_return
    sub     r0, r2, r0
    b       .Lfix_return_done
.Lfix_return:
    sub     r0, r2, r1
.Lfix_return_done:
    ldmia   sp!, {r2, lr}
    sub     r0, r2, r0
    bx      lr
.Lfix_return3:
    ldmia   sp!, {r4, r5}
    b       .Lfix_return2

.pushsection __exc_table, "a"
    .long   0b,  .Lfix_return1
    .long   1b,  .Lfix_return1
    .long   2b,  .Lfix_return1
    .long   3b,  .Lfix_return1
    .long   4b,  .Lfix_return1
    .long   5b,  .Lfix_return1
    .long   6b,  .Lfix_return2
    .long   7b,  .Lfix_return2
    .long   8b,  .Lfix_return2
    .long   9b,  .Lfix_return2
    .long   10b, .Lfix_return2
    .long   11b, .Lfix_return2
    .long   12b, .Lfix_return2
    .long   13b, .Lfix_return2
    .long   14b, .Lfix_return2
    .long   15b, .Lfix_return2
    .long   16b, .Lfix_return2
    .long   17b, .Lfix_return2
    .long   18b, .Lfix_return2
    .long   19b, .Lfix_return2
    .long   20b, .Lfix_return2
    .long   21b, .Lfix_return2
    .long   22b, .Lfix_return2
    .long   23b, .Lfix_return2
    .long   24b, .Lfix_return2
    .long   25b, .Lfix_return3
    .long   26b, .Lfix_return3
    .long   27b, .Lfix_return2
    .long   28b, .Lfix_return2
    .long   29b, .Lfix_return3
    .long   30b, .Lfix_return3
    .long   31b, .Lfix_return2
    .long   32b, .Lfix_return2
    .long   33b, .Lfix_return3
    .long   34b, .Lfix_return3
    .long   35b, .Lfix_return2
    .long   36b, .Lfix_return2
.popsection
