/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __HI_TYPE_H__
#define __HI_TYPE_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef unsigned char HI_U8;
typedef unsigned short HI_U16;
typedef unsigned int HI_U32;

typedef signed char HI_S8;
typedef short HI_S16;
typedef int HI_S32;

typedef unsigned long HI_UL;
typedef signed long HI_SL;

typedef float HI_FLOAT;
typedef double HI_DOUBLE;

#ifndef _M_IX86
typedef unsigned long long HI_U64;
typedef long long HI_S64;
#else
typedef unsigned __int64 HI_U64;
typedef __int64 HI_S64;
#endif

typedef char HI_CHAR;
#define HI_VOID void

typedef HI_U32 HI_HANDLE;

typedef enum {
    HI_FALSE = 0,
    HI_TRUE = 1,
} HI_BOOL;

#ifndef NULL
#define NULL 0L
#endif

#define HI_NULL    0L
#define HI_SUCCESS 0
#define HI_FAILURE (-1)

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

typedef void                    hi_void;

typedef unsigned long           hi_size_t;
typedef unsigned long           hi_length_t;
typedef unsigned long int       hi_phys_addr_t;

typedef hi_u32                  hi_handle;

typedef HI_BOOL                 hi_bool;
typedef uintptr_t               hi_uintptr_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */
