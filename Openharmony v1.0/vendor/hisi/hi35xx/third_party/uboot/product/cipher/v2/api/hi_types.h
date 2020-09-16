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
 * Description   : head file for type
 */

#ifndef __HI_TYPE_H__
#define __HI_TYPE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*--------------------------------------------------------------------------------------------------------------*
 * Defintion of basic data types. The data types are applicable to both the application layer and kernel codes. *                                             *
 *--------------------------------------------------------------------------------------------------------------*/
/*************************** Structure Definition ****************************/
/** \addtogroup      Common_TYPE */
/** @{ */  /** <!-- [Common_TYPE] */

typedef unsigned char           hi_u8;
typedef unsigned char           hi_uchar;
typedef unsigned short          hi_u16;
typedef unsigned int            hi_u32;
typedef unsigned long           hi_ulong;

typedef signed char             hi_s8;
typedef short                   hi_s16;
typedef int                     hi_s32;
typedef long                    hi_slong;

#ifndef _M_IX86
typedef unsigned long long      hi_u64;
typedef long long               hi_s64;
#else
typedef __int64                 hi_u64;
typedef __int64                 hi_s64;
#endif

typedef char                    hi_char;
typedef char*                   hi_pchar;

typedef unsigned long           hi_ul;
typedef signed long             hi_sl;

typedef float                   hi_float;
typedef double                  hi_double;
#define hi_void                 void

typedef unsigned long           hi_size_t;
typedef unsigned long           hi_length_t;

typedef hi_u32                  hi_handle;

typedef unsigned int            hi_phys_addr_t;

#ifdef CONFIG_ARCH_LP64_MODE
typedef unsigned long long      hi_virt_addr_t;
#else
typedef unsigned int            hi_virt_addr_t;
#endif

/** Constant Definition */
typedef enum {
    HI_FALSE    = 0,
    HI_TRUE     = 1,
} hi_bool;

#ifndef NULL
#define NULL                0L
#endif

#define HI_NULL             0L
#define HI_NULL_PTR         0L

#define HI_SUCCESS          0
#define HI_FAILURE          (-1)

#define HI_INVALID_HANDLE   0xffffffff
#define HI_INVALID_PTS      0xffffffff
#define HI_INVALID_TIME     0xffffffff

#define HI_OS_LINUX         0xabcd
#define HI_OS_WIN32         0xcdef

#ifdef _WIN32
#define HI_OS_TYPE          HI_OS_WIN32
#else
#define __OS_LINUX__
#define HI_OS_TYPE          HI_OS_LINUX
#endif

#ifdef HI_ADVCA_SUPPORT
#define __INIT__
#define __EXIT__
#else
#define __INIT__  __init
#define __EXIT__  __exit
#endif

/**

define of hi_handle :
bit31                                                           bit0
  |<----   16bit --------->|<---   8bit    --->|<---  8bit   --->|
  |--------------------------------------------------------------|
  |      HI_MOD_ID_E       |  mod defined data |     chnID       |
  |--------------------------------------------------------------|

mod defined data: private data define by each module(for example: sub-mod id), usually, set to 0.
*/

#define hi_handle_make_handle(mod, privatedata, chnid) \
    (hi_handle)((((mod) & 0xffff) << 16) | ((((privatedata) & 0xff) << 8)) | (((chnid) & 0xff)))

#define hi_handle_get_mod_id(handle)     (((handle) >> 16) & 0xffff)
#define hi_handle_get_pri_data(handle)   (((handle) >> 8) & 0xff)
#define hi_handle_get_chn_id(handle)     (((handle)) & 0xff)

/** @} */  /** <!-- ==== Structure Definition end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */

