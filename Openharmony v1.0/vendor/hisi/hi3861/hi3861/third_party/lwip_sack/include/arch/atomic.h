/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2016. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: define atomic type and function
 * Author: none
 * Create: 2013
 */

#ifndef __ASM_ATOMIC_H__
#define __ASM_ATOMIC_H__

#include "los_atomic.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#ifdef __LP64__
#define atomic_t long
#else
#define atomic_t int
#endif

#define atomic_inc(atom)     LOS_AtomicInc(atom)
#define atomic_dec(atom)    LOS_AtomicDec(atom)
#define atomic_sub(n, v)      LOS_AtomicSub(v, n)
#define atomic_add(n, v)     LOS_AtomicAdd(v, n)
#define atomic_read(atom)    (*((volatile typeof(atom))(atom)))
#ifdef __LP64__
#define atomic_set(p, v)      LOS_AtomicXchg64bits(p, v)
#else
#define atomic_set(p, v)      LOS_AtomicXchg32bits(p, v)
#endif
#define ATOMIC_INIT(x)     (x)

#define atomic_add_return(i, v)    LOS_AtomicAdd(v, i)
#define atomic_inc_return(v)        LOS_AtomicIncRet(v)
#define atomic_dec_return(v)       LOS_AtomicDecRet(v)
#define atomic_dec_and_test(v)    (atomic_dec_return(v) == 0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __ASM_ATOMIC_H__ */
