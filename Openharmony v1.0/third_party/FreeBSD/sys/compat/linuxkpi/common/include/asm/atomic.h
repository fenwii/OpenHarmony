/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2018 Mellanox Technologies, Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.4/sys/compat/linuxkpi/common/include/asm/atomic.h 337898 2018-08-16 08:12:36Z hselasky $
 */

#ifndef _ASM_ATOMIC_H_
#define	_ASM_ATOMIC_H_

#include "los_atomic.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef Atomic atomic_t;
typedef Atomic64 atomic64_t;

#define ATOMIC_INIT(x)                  (x)
#define atomic_read(v)                  LOS_AtomicRead(v)
#define atomic_set(v, i)                LOS_AtomicSet(v, i)
#define atomic_inc(v)                   LOS_AtomicInc(v)
#define atomic_dec(v)                   LOS_AtomicDec(v)
#define atomic_add(i, v)                LOS_AtomicAdd(v, i)
#define atomic_sub(i, v)                LOS_AtomicSub(v, i)

#define atomic_add_return(i, v)         LOS_AtomicAdd(v, i)
#define atomic_inc_return(v)            LOS_AtomicIncRet(v)
#define atomic_dec_return(v)            LOS_AtomicDecRet(v)
#define atomic_dec_and_test(v)          (atomic_dec_return(v) == 0)

#define ATOMIC64_INIT(x)                (x)
#define atomic64_read(v)                LOS_Atomic64Read(v)
#define atomic64_set(v, i)              LOS_Atomic64Set(v, i)
#define atomic64_inc(v)                 LOS_Atomic64Inc(v)
#define atomic64_dec(v)                 LOS_Atomic64Dec(v)
#define atomic64_add(i, v)              LOS_Atomic64Add(v, i)
#define atomic64_sub(i, v)              LOS_Atomic64Sub(v, i)

#define atomic64_add_return(i, v)       LOS_Atomic64Add(v, i)
#define atomic64_inc_return(v)          LOS_Atomic64IncRet(v)
#define atomic64_dec_return(v)          LOS_Atomic64DecRet(v)
#define atomic64_dec_and_test(v)        (atomic64_dec_return(v) == 0)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _ASM_ATOMIC_H_ */
