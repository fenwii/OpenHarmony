/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _HI_BOOT_TYPES_H_
#define _HI_BOOT_TYPES_H_

/* Basic data type definition */
typedef unsigned char           hi_uchar;
typedef unsigned char           hi_u8;
typedef unsigned short          hi_u16;
typedef unsigned int            hi_u32;
typedef unsigned long long      hi_u64;
typedef unsigned long           hi_ulong;
typedef char                    hi_char;
typedef signed char             hi_s8;
typedef short                   hi_s16;
typedef int                     hi_s32;
typedef long long               hi_s64;
typedef long                    hi_slong;
typedef float                   hi_float;
typedef double                  hi_double;
typedef unsigned long           hi_size_t;
typedef unsigned long           hi_length_t;
typedef hi_u32                  hi_handle;
typedef hi_u8                   hi_bool;
typedef unsigned int            uintptr_t;
typedef void                    hi_void;
typedef void*                   hi_pvoid;

typedef hi_u8                   hi_byte;
typedef hi_byte*                hi_pbyte;
typedef hi_u32                  size_t;
typedef unsigned long long      uint64_t;

typedef hi_void  (*hi_void_callback_f)(hi_void);

#define HI_PRV    static
#define HI_PRVL   static inline
#define HI_INLINE inline
#define HI_EXTERN extern
#define HI_CONST  const
#define HI_ALWAYS_INLINE __attribute__((always_inline)) inline

#define HI_OUT
#define HI_IN
#define HI_INOUT

#define HI_FALSE 0
#define HI_TRUE  1


#ifdef __cplusplus
#define HI_NULL 0
#else
#define HI_NULL ((void*)0)
#endif

#ifndef NULL
#define NULL (void*)0
#endif

#define SZ_1KB 1024
#define SZ_1MB (SZ_1KB * SZ_1KB)
#define SZ_4KB 4096

#define hi_array_count(x) (sizeof(x) / sizeof((x)[0]))

#define hi_align_4(x)        ((unsigned int)((x) + 0x3) & (~0x3))
#define hi_is_align_u32(x)   (!((x) & 3))
#define hi_is_unalign_u32(x) ((x) & 3)
#if defined(HAVE_PCLINT_CHECK)
#define hi_fieldoffset(s, m) (0)
#else
#define hi_fieldoffset(s, m) ((hi_u32) & (((s*)0)->m))
#endif
#define HI_CHAR_CR '\r' /* 0x0D */
#define HI_CHAR_LF '\n' /* 0x0A */

#define hi_makeu16(a, b) ((hi_u16)(((hi_u8)(a)) | ((hi_u16)((hi_u8)(b))) << 8))
#define hi_makeu32(a, b) ((hi_u32)(((hi_u16)(a)) | ((hi_u32)((hi_u16)(b))) << 16))
#define hi_hiu16(l)      ((hi_u16)(((hi_u32)(l) >> 16) & 0xFFFF))
#define hi_lou16(l)      ((hi_u16)(l))
#define hi_hiu8(l)       ((hi_u8)(((hi_u16)(l) >> 8) & 0xFF))
#define hi_lou8(l)       ((hi_u8)(l))

#define hi_max(a, b) (((a) > (b)) ? (a) : (b))
#define hi_min(a, b) (((a) < (b)) ? (a) : (b))

#define hi_set_bit_i(val, n)                          ((val) |= (1 << (n)))
#define hi_clr_bit_i(val, n)                          ((val) &= ~(1 << (n)))
#define hi_is_bit_set_i(val, n)                       ((val) & (1 << (n)))
#define hi_is_bit_clr_i(val, n)                       (~((val) & (1 << (n))))
#define hi_switch_bit_i(val, n)                       ((val) ^= (1 << (n)))
#define hi_get_bit_i(val, n)                          (((val) >> (n)) & 1)
#define hi_u8_bit_val(b7, b6, b5, b4, b3, b2, b1, b0) \
    (((b7) << 7) | ((b6) << 6) | ((b5) << 5) | ((b4) << 4) | ((b3) << 3) | ((b2) << 2) | ((b1) << 1) | ((b0) << 0))

#define hi_u16_bit_val(b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1, b0) \
    (hi_u16)(((b12) << 12) | ((b11) << 11) | ((b10) << 10) | ((b9) << 9) | ((b8) << 8) | ((b7) << 7) | \
    ((b6) << 6) | ((b5) << 5) | ((b4) << 4) | ((b3) << 3) | ((b2) << 2) | ((b1) << 1) | ((b0) << 0))

#define ALIGNTYPE_1BYTE             1
#define ALIGNTYPE_2BYTE             2
#define ALIGNTYPE_4BYTE             4
#define ALIGNTYPE_8BYTE             8
#define ALIGNTYPE_64BYTE            64
#define ALIGNTYPE_32BYTE            32
#define ALIGNTYPE_4K                4096
#define align_next(val, a)          ((((val) + ((a)-1)) & (~((a)-1))))
#define align_length(val, a)        align_next(val, a)
#define HI_ALL_F_32                 0xFFFFFFFF
#define HI_ALL_F_16                 0xFFFF

#define BYTE_WIDTH                  1
#define HALF_WIDTH                  2
#define WORD_WIDTH                  4

#define BITS_PER_BYTE               8
#define HEXADECIMAL                 16
#define DECIMAL                     10

#define HALFWORD_BIT_WIDTH          16

#if !defined(hi_unref_param) && !defined(HI_HAVE_CROSS_COMPILER_DIAB)
#define hi_unref_param(P)  P = P
#else
#define hi_unref_param(P)
#endif

#ifndef __ROM_ADDITION
#define __ROM_ADDITION __attribute__((section(".rom_addition.text")))
#endif

#endif
