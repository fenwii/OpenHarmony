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

#ifdef __KERNEL__

#include <linux/types.h>
#else

#include <stdint.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef NULL
    #define NULL                0L
#endif

#define HI_NULL                 0L
#define HI_SUCCESS              0
#define HI_FAILURE              (-1)

typedef unsigned char           hi_uchar;
typedef unsigned char           hi_u8;
typedef unsigned short          hi_u16;
typedef unsigned int            hi_u32;
typedef unsigned long           hi_ulong;

typedef char                    hi_char;
typedef signed char             hi_s8;
typedef short                   hi_s16;
typedef int                     hi_s32;
typedef long                    hi_slong;

typedef float                   hi_float;
typedef double                  hi_double;

typedef void                    hi_void;

#ifndef _M_IX86
    typedef unsigned long long  hi_u64;
    typedef long long           hi_s64;
#else
    typedef unsigned __int64    hi_u64;
    typedef __int64             hi_s64;
#endif
typedef unsigned long int       uintptr_t;

typedef unsigned long           hi_size_t;
typedef unsigned long           hi_length_t;
typedef unsigned long int       hi_phys_addr_t;
typedef hi_u32                  hi_handle;
typedef uintptr_t               hi_uintptr_t;
typedef unsigned int            hi_fr32;

typedef enum {
    HI_FALSE = 0,
    HI_TRUE  = 1,
} hi_bool;

#define EOK 0


/** @} */  /** <!-- ==== Structure Definition end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */

