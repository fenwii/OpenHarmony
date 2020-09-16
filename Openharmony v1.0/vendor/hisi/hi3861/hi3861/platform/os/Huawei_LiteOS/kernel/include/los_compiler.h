/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2018. All rights reserved.
 * Description: compiler related definitions
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
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
 * --------------------------------------------------------------------------- */

#ifndef _LOS_COMPILER_H
#define _LOS_COMPILER_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* for IAR Compiler */
#ifdef __ICCARM__

#ifndef ASM
#define ASM           __asm
#endif

#ifndef asm
#define asm           __asm
#endif

#ifndef INLINE
#define INLINE        inline
#endif

#ifndef STATIC_INLINE
#define STATIC_INLINE static inline
#endif

#ifndef USED
#define USED          __root
#endif

#ifndef WEAK
#define WEAK          __weak
#endif

/* for ARM Compiler */
#elif defined(__CC_ARM)

#ifndef ASM
#define ASM           __asm
#endif

#ifndef asm
#define asm           __asm
#endif

#ifndef INLINE
#define INLINE        __inline
#endif

#ifndef STATIC_INLINE
#define STATIC_INLINE static __inline
#endif

#ifndef USED
#define USED          __attribute__((used))
#endif

#ifndef WEAK
#define WEAK          __attribute__((weak))
#endif

#ifndef CLZ
#define CLZ           __clz
#endif

#pragma anon_unions

/* for GNU Compiler */
#elif defined(__GNUC__)

#ifndef ASM
#define ASM           __asm
#endif

#ifndef asm
#define asm           __asm
#endif

#ifndef INLINE
#define INLINE        inline
#endif

#ifndef STATIC_INLINE
#define STATIC_INLINE static inline
#endif

#ifndef USED
#define USED          __attribute__((used))
#endif

#ifndef WEAK
#define WEAK          __attribute__((__weak__))
#endif

#ifndef CLZ
#define CLZ           __builtin_clz
#endif

#ifdef typeof
#undef typeof
#endif
#define typeof                  __typeof__
#else
#error Unknown compiler.
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_COMPILER_H */
