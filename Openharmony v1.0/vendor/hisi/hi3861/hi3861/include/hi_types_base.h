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

#ifndef __HI_TYPES_BASE_H__
#define __HI_TYPES_BASE_H__

#if defined(__CC_ARM)
#define HI_HAVE_CROSS_COMPILER_ARM_ARMCC
#elif defined(__GNUC__)
#define HI_HAVE_CROSS_COMPILER_ARM_GCC
#elif defined(__DCC__)
#define HI_HAVE_CROSS_COMPILER_DIAB
#if defined(__HI_ASM_LANGUAGE__) || defined(_ASMLANGUAGE)
#define HI_HAVE_CROSS_COMPILER_DIAB_AS
#endif
#elif defined(_MSC_VER)
#define HI_HAVE_NOTIVE_COMPILER_VC
#endif

#if !defined(HI_HAVE_CROSS_COMPILER_DIAB_AS)
#if defined(HI_HAVE_CROSS_COMPILER_ARM_GCC) || defined(HI_HAVE_CROSS_COMPILER_ARM_ARMCC) || \
    defined(HI_HAVE_CROSS_COMPILER_DIAB)
#undef HI_HAVE_CROSS_COMPILER
#define HI_HAVE_CROSS_COMPILER
#endif

#ifdef PRODUCT_CFG_PLATFORM_HI3921
#define SAL_HAVE_HI3911_VER
#endif

#ifdef PRODUCT_CFG_OS_WIN
# undef SAL_HAVE_OS_WIN_VER
# undef SAL_HAVE_OS_NU_VER
# undef SAL_HAVE_OS_VX_VER
#define SAL_HAVE_OS_WIN_VER
#endif

#if defined (PRODUCT_CFG_OS_LOS)
# undef SAL_HAVE_OS_VX_VER
# define SAL_HAVE_OS_VX_VER
#else
# if defined (_WIN32) && defined (_MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#  ifndef SAL_HAVE_SIMU_WIN_VER
#   define SAL_HAVE_SIMU_WIN_VER
#   ifdef _USRDLL
#    if !defined(PRODUCT_CFG_MSVC_HIDE_AUTOLINK_OUTPUT_INFO)
#     pragma message("Windows VC Simulator DLL Version ")
#    endif
#   endif
#   ifdef _LIB
#    if !defined(PRODUCT_CFG_MSVC_HIDE_AUTOLINK_OUTPUT_INFO)
#     pragma message("Windows VC Simulator lib Version ")
#    endif
#   endif
#   ifdef _CONSOLE
#    if !defined(PRODUCT_CFG_MSVC_HIDE_AUTOLINK_OUTPUT_INFO)
#     pragma message("Windows VC Simulator console Version ")
#    endif
#   endif
#  else
#   if !defined(PRODUCT_CFG_MSVC_HIDE_AUTOLINK_OUTPUT_INFO)
#    pragma message("Windows Version")
#   endif
#  endif
# endif
#endif

#undef HI_SYS_DEBUG
#if (defined(PRODUCT_CFG_VERSION_DEBUG) || defined(SAL_HAVE_DEBUG_VERSION)) && !defined(SAL_HAVE_RELEASE_VERSION)
# define HI_SYS_DEBUG
#endif

#if defined(PRODUCT_CFG_OS_WIN)
#pragma warning(disable:4200)  /* disable nonstandard extension used : zero-sized array in struct/union. */
#pragma warning(disable:4214)  /* allows bitfield structure members to be of any integral type. */
#pragma warning(disable:4201)
#pragma warning(disable:4514)
#pragma warning(disable:4127)
#endif

/* 基本数据类型定义 */
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
typedef hi_u8                   hi_bool;
typedef void                    hi_void;
typedef void*                   hi_pvoid;
typedef hi_u8                   hi_byte;
typedef hi_byte*                hi_pbyte;

/* for 64bits platform, intptr_t/uintptr_t should be defined as 64bits length. */
typedef int                     intptr_t;
typedef unsigned int            uintptr_t;

#undef ERROR
#define ERROR (-1)

/* defines */
#undef NULL
#ifndef NULL
#define NULL 0
#endif

#define HI_CONST               const
#define HI_REG                 register

#define HI_U32_MAX            0xFFFFFFFF
#define HI_U64_MAX            0xFFFFFFFFFFFFFFFFUL
#define HI_U16_MAX            0xFFFF

typedef hi_pvoid (*hi_pvoid_callback_f)(hi_void);
typedef hi_void  (*hi_void_callback_f)(hi_void);
typedef hi_void  (*hi_void_callback)(hi_void);
typedef hi_bool  (*hi_bool_callback_f)(hi_void);
typedef hi_void  (*hi_void_u32_callback_f)(hi_u32);
typedef hi_u32   (*hi_u32_pvoid_callback_f)(hi_pvoid);
typedef hi_u32   (*hi_u32_void_callback)(hi_void); /* 周边代码待刷新 */
typedef hi_u32   (*hi_u32_u32_pvoid_callback_f)(hi_pvoid, hi_u32);
typedef hi_s32   (*funcptr)(hi_void);     /* ptr to function returning int */
typedef hi_void  (*voidfuncptr)(hi_void); /* ptr to function returning void */

typedef HI_CONST hi_char*  hi_pcstr;

#ifdef PRODUCT_CFG_OS_WIN
typedef unsigned __int64       hi_u64;
typedef __int64 hi_s64;
#elif defined(HI_HAVE_CROSS_COMPILER_ARM_ARMCC)
typedef unsigned __int64       hi_u64;
typedef __int64 hi_s64;
#elif defined(HI_HAVE_CROSS_COMPILER_ARM_GCC) || defined(HAVE_PCLINT_CHECK)
typedef unsigned long long     hi_u64;
typedef long long              hi_s64;
#elif defined(HI_HAVE_CROSS_COMPILER_DIAB)
typedef unsigned long long     hi_u64;
typedef long long              hi_s64;
#elif !defined(PRODUCT_CFG_HSO)
/* #error "unknown compiler" */
typedef unsigned __int64       hi_u64;
typedef __int64 hi_s64;
#endif

#define HI_S32_BITS       32
#define HI_S32_MAX       (~(~0 << (HI_S32_BITS - 1)))

#define HI_PUBLIC    extern
#if !defined(PRODUCT_CFG_FEATURE_UT)
# define HI_PRV   static
#else
# define HI_PRV
#endif

# define STATIC   static

#endif /* HI_HAVE_CROSS_COMPILER_DIAB_AS */

#ifdef PRODUCT_CFG_OS_WIN
# define HI_API   _declspec(dllexport)
# define HI_INLINE  __inline
#elif defined(HI_HAVE_CROSS_COMPILER_ARM_GCC)
#  define HI_INLINE  inline
#  define HI_API
#elif defined(HI_HAVE_CROSS_COMPILER_ARM_ARMCC)
#  define HI_INLINE  inline
#  define HI_API
#elif defined(HI_HAVE_CROSS_COMPILER_DIAB)
#  define HI_INLINE  __inline__
#  define HI_API
# else
#  define HI_INLINE __inline
#  define HI_API
#endif

#define HI_PRVL HI_PRV HI_INLINE

#if defined(__ONEBUILDER__CROSS_COMPILER_PRODUCT_CONFIG__)
#if defined(HI_HAVE_CROSS_COMPILER_ARM_ARMCC) || defined(HI_HAVE_CROSS_COMPILER_ARM_GCC)
# define hi_section(name_string) __attribute__ ((section(name_string)))
# define HI_PACKED               __attribute__((packed))
# define HI_ALIGNED4             __attribute__ ((aligned (4)))
#elif defined(HI_HAVE_CROSS_COMPILER_DIAB)
# define hi_section(name_string) __attribute__ ((section(name_string)))
# define HI_PACKED               __attribute__((packed))
# define HI_ALIGNED4             __attribute__ ((aligned (4)))
#endif
#elif defined(SAL_HAVE_OS_WIN_VER) || defined(PRODUCT_CFG_HSO)
#  define hi_section(name_string)
#  define HI_PACKED
#  define HI_ALIGNED4
#else
#  define hi_section(name_string)
#  define HI_PACKED
#  define HI_ALIGNED4
#endif

#if defined(SAL_HAVE_OS_WIN_VER)
# if defined(_DEBUG) || defined(PRODUCT_CFG_VERSION_DEBUG)
#  define hi_dll_lib_name(x)        x ## "_debug.dll"
# else
#  define hi_dll_lib_name(x)        x ## "_release.dll"
# endif
#else
#if defined(HI_HAVE_CROSS_COMPILER_ARM_GCC)
# define hi_dll_lib_name(x)        x
#else
# define hi_dll_lib_name(x)        x ## ".lib"
#endif
#endif

#if defined(SAL_HAVE_NO_EXTERN_DEFINED)
# define HI_EXTERN
# define HI_EXTERN_C
#else
# if defined(PRODUCT_CFG_OS_WIN)
#  define HI_EXTERN      extern HI_API
#  define HI_EXTERN_C    HI_EXTERN
#  define HI_EAPI        extern HI_API
# else
#    define HI_EXTERN   extern
#    define HI_EAPI
#    define HI_EXTERN_C
# endif
#endif

#ifdef __cplusplus
# define HI_CPP_START    extern "C" {
# define HI_CPP_END      }
#else
# define HI_CPP_START
# define HI_CPP_END
#endif

#if defined(HI_HAVE_CROSS_COMPILER_ARM_ARMCC)
#define HI_NOP             __asm { nop }
#define hi_dbg_break()     __asm { swi 0x14DEAD }
#elif defined(HI_HAVE_CROSS_COMPILER_DIAB)
#define HI_NOP
#define hi_dbg_break()
#else
#define HI_NOP
#ifdef PRODUCT_CFG_OS_WIN
#define hi_dbg_break()     _asm { int 3 }
#else
#define hi_dbg_break()
#endif
#endif

#define HI_START_HEADER    HI_CPP_START
#define HI_END_HEADER      HI_CPP_END

#undef HI_OUT
#undef HI_IN
#undef HI_INOUT
#define HI_OUT
#define HI_IN
#define HI_INOUT

#define HI_FALSE         0
#define HI_TRUE          1
#define HI_SWITCH_OFF    0
#define HI_SWITCH_ON     1

#ifdef __cplusplus
#define HI_NULL       0
#else
#define HI_NULL    ((void *)0)
#endif

#ifndef CACHE_ALIGNED_SIZE
#define CACHE_ALIGNED_SIZE        32
#endif

#define hi_array_count(x)    (sizeof(x) / sizeof((x)[0]))

#if !defined(hi_unref_param) && !defined(HI_HAVE_CROSS_COMPILER_DIAB)
#define hi_unref_param(P)  ((P) = (P))
#else
#define hi_unref_param(P)
#endif

#if defined(PRODUCT_CFG_PLATFORM_HI3921)
#if defined(HI_HAVE_CROSS_COMPILER_ARM_ARMCC)
#define HI_VOLATILE   volatile
#define hi_sys_get_lr()                        __return_address()
#elif defined(HAVE_PCLINT_CHECK)
#define HI_VOLATILE
#define hi_sys_get_lr()                        0
#elif defined(HI_HAVE_CROSS_COMPILER_DIAB)
#define HI_VOLATILE   volatile
#define hi_sys_get_lr()                        0
#else
#define HI_VOLATILE  __volatile__
#define hi_sys_get_lr()                        0
#endif
#else
#define HI_VOLATILE
#define hi_sys_get_lr()                        0
#endif

#define hi_aligin_u32_size(x)  (((x) & (~3)) + 4) /* 构造4个字节对齐 */
#define hi_is_align_u32(x)     (!((x) & 3))       /* 判断是否为4字节对齐 */
#define hi_is_unalign_u32(x)   ((x) & 3)          /* 判断是否为4字节对齐 */
#if defined(HAVE_PCLINT_CHECK)
#define hi_fieldoffset(s, m)    (0)
#else
#define hi_fieldoffset(s, m)    ((hi_u32)&(((s *)0)->m)) /* 结构成员偏移 */
#endif

#define HI_CHAR_CR             '\r' /* 0x0D */
#define HI_CHAR_LF             '\n' /* 0x0A */
#define hi_tolower(x)          ((x) | 0x20)  /* Works only for digits and letters, but small and fast */

#define hi_array_size(_array)  (sizeof(_array) / sizeof((_array)[0]))
#define hi_makeu16(a, b)       ((hi_u16)(((hi_u8)(a))  | ((hi_u16)((hi_u8)(b))) << 8))
#define hi_makeu32(a, b)       ((hi_u32)(((hi_u16)(a)) | ((hi_u32)((hi_u16)(b))) << 16))
#define hi_makeu64(a, b)       ((hi_u64)(((hi_u32)(a)) | ((hi_u64)((hi_u32)(b))) <<32))
#define hi_joinu32(a, b, c, d) ((a) | ((hi_u32)(b) << 8) | ((hi_u32)(c) << 16) | ((hi_u32)(d) << 24))

#define hi_hiu32(l)            ((hi_u32)(((hi_u64)(l) >> 32) & 0xFFFFFFFF))
#define hi_lou32(l)            ((hi_u32)(l))

#define hi_hiu16(l)            ((hi_u16)(((hi_u32)(l) >> 16) & 0xFFFF))
#define hi_lou16(l)            ((hi_u16)(l))
#define hi_hiu8(l)             ((hi_u8)(((hi_u16)(l) >> 8) & 0xFF))
#define hi_lou8(l)             ((hi_u8)(l))

#define hi_max(a, b)            (((a) > (b)) ? (a) : (b))
#define hi_min(a, b)            (((a) < (b)) ? (a) : (b))
#define hi_sub(a, b)            (((a) > (b)) ? ((a) - (b)) : 0)
#define hi_abs_sub(a, b)       (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#define hi_byte_align(value, align)            (((value) + (align) - 1) & (~((align) -1)))
#define hi_is_byte_align(value, align)         (((hi_u32)(value) & ((align) - 1))== 0)
#define hi_inc_wraparound(value, round_size)   ++(value); (value) &= ((round_size) - 1)
#define hi_dec_wraparound(value, round_size)   --(value); (value) &= ((round_size) - 1)

#define hi_swap_byteorder_16(value)            ((((value) & 0xFF) << 8) + (((value) & 0xFF00) >> 8))

#define hi_swap_byteorder_32(value)       \
    ((hi_u32)(((value) & 0x000000FF) << 24) + \
     (hi_u32)(((value) & 0x0000FF00)  << 8) +  \
     (hi_u32)(((value) & 0x00FF0000)  >> 8) +  \
     (hi_u32)(((value) & 0xFF000000)  >> 24))

#define hi_swap_byteorder_64(value)                     \
    ((((value) & 0x00000000000000ffULL) << 56) +    \
     (((value) & 0x000000000000ff00ULL) << 40) +     \
     (((value) & 0x0000000000ff0000ULL) << 24) +     \
     (((value) & 0x00000000ff000000ULL) << 8) +      \
     (((value) & 0x000000ff00000000ULL) >> 8) +      \
     (((value) & 0x0000ff0000000000ULL) >> 24) +     \
     (((value) & 0x00ff000000000000ULL) >> 40) +     \
     (((value) & 0xff00000000000000ULL) >> 56))

#undef MIN_T
#define MIN_T  hi_min

#define hi_make_identifier(a, b, c, d)      hi_makeu32(hi_makeu16(a, b), hi_makeu16(c, d))
#define hi_make_ver16(spc, b)           ((hi_u16)(((hi_u8)((spc)&0x0F))  | ((hi_u16)((hi_u8)(b))) << 12))

#define  hi_set_bit_i(val, n)               ((val) |= (1 << (n)))
#define  hi_clr_bit_i(val, n)               ((val) &= ~(1 << (n)))
#define  hi_is_bit_set_i(val, n)            ((val) & (1 << (n)))
#define  hi_is_bit_clr_i(val, n)            (~((val) & (1 << (n))))
#define  hi_switch_bit_i(val, n)            ((val) ^= (1 << (n)))
#define  hi_get_bit_i(val, n)               (((val) >> (n)) & 1)
#define  hi_reg_clr_bit_i(reg, n)           ((*(volatile unsigned int *)(reg)) &= ~(1 << (n)))

#define  hi_u8_bit_val(b7, b6, b5, b4, b3, b2, b1, b0)                       \
    (((b7) << 7) | ((b6) << 6) | ((b5) << 5) | ((b4) << 4) | ((b3) << 3) | ((b2) << 2) | ((b1) << 1) | ((b0) << 0))
#define  hi_u16_bit_val(b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1, b0)    \
    (hi_u16)(((b12) << 12) | ((b11) << 11) | ((b10) << 10) | ((b9) << 9) | ((b8) << 8) | ((b7) << 7) |   \
    ((b6) << 6) | ((b5) << 5) | ((b4) << 4) | ((b3) << 3) | ((b2) << 2) | ((b1) << 1) | ((b0) << 0))

#if defined(__ONEBUILDER__CROSS_COMPILER_PRODUCT_CONFIG__)
#define HSO_ENUM    HI_ALIGNED4 enum
#define HI_U8A      HI_ALIGNED4 hi_u8
#define HI_U16A     HI_ALIGNED4 hi_u16
#define HI_CHARTA   HI_ALIGNED4 hi_char
#else
#define HSO_ENUM    enum
#define HI_U8A      hi_u8
#define HI_U16A     hi_u16
#define HI_CHARTA   hi_char
#endif

#if defined(PRODUCT_CFG_HSO) && defined(HI_HAVE_NOTIVE_COMPILER_VC)
#define __FUNCTION__   "NA"
#endif

/*****************************************************************************/
#define hi_set_u32_ptr_val(ptr, offset, val)  (*((hi_u32*)(((hi_u8*)(ptr)) + (offset))) = (val))
#define hi_get_u32_ptr_val(ptr, offset)      *((hi_u32*)(((hi_u8*)(ptr)) + (offset)))
/*****************************************************************************/
/*****************************************************************************/
#define HI_SIZE_1K                     1024
#define HI_SIZE_1M                     (1024 * 1024)
/*****************************************************************************/
#ifndef bit
#define bit(x)                         (1UL << (x))
#endif
#define BIT31                          ((hi_u32)(1UL << 31))
#define BIT30                          ((hi_u32)(1 << 30))
#define BIT29                          ((hi_u32)(1 << 29))
#define BIT28                          ((hi_u32)(1 << 28))
#define BIT27                          ((hi_u32)(1 << 27))
#define BIT26                          ((hi_u32)(1 << 26))
#define BIT25                          ((hi_u32)(1 << 25))
#define BIT24                          ((hi_u32)(1 << 24))
#define BIT23                          ((hi_u32)(1 << 23))
#define BIT22                          ((hi_u32)(1 << 22))
#define BIT21                          ((hi_u32)(1 << 21))
#define BIT20                          ((hi_u32)(1 << 20))
#define BIT19                          ((hi_u32)(1 << 19))
#define BIT18                          ((hi_u32)(1 << 18))
#define BIT17                          ((hi_u32)(1 << 17))
#define BIT16                          ((hi_u32)(1 << 16))
#define BIT15                          ((hi_u32)(1 << 15))
#define BIT14                          ((hi_u32)(1 << 14))
#define BIT13                          ((hi_u32)(1 << 13))
#define BIT12                          ((hi_u32)(1 << 12))
#define BIT11                          ((hi_u32)(1 << 11))
#define BIT10                          ((hi_u32)(1 << 10))
#define BIT9                           ((hi_u32)(1 << 9))
#define BIT8                           ((hi_u32)(1 << 8))
#define BIT7                           ((hi_u32)(1 << 7))
#define BIT6                           ((hi_u32)(1 << 6))
#define BIT5                           ((hi_u32)(1 << 5))
#define BIT4                           ((hi_u32)(1 << 4))
#define BIT3                           ((hi_u32)(1 << 3))
#define BIT2                           ((hi_u32)(1 << 2))
#define BIT1                           ((hi_u32)(1 << 1))
#define BIT0                           ((hi_u32)(1 << 0))

#define HALFWORD_BIT_WIDTH              16

/* 寄存器访问接口 */
#define hi_reg_write(addr, val)        (*(volatile unsigned int *)(uintptr_t)(addr) = (val))
#define hi_reg_read(addr, val)         ((val) = *(volatile unsigned int *)(uintptr_t)(addr))
#define hi_reg_write32(addr, val)      (*(volatile unsigned int *)(uintptr_t)(addr) = (val))
#define hi_reg_read32(addr, val)       ((val) = *(volatile unsigned int *)(uintptr_t)(addr))
#define hi_reg_read_val32(addr)        (*(volatile unsigned int*)(uintptr_t)(addr))
#define hi_reg_setbitmsk(addr, msk)    ((hi_reg_read_val32(addr)) |= (msk))
#define hi_reg_clrbitmsk(addr, msk)    ((hi_reg_read_val32(addr)) &= ~(msk))
#define hi_reg_clrbit(addr, pos)       ((hi_reg_read_val32(addr)) &= ~((unsigned int)(1) << (pos)))
#define hi_reg_setbit(addr, pos)       ((hi_reg_read_val32(addr)) |= ((unsigned int)(1) << (pos)))
#define hi_reg_clrbits(addr, pos, bits) (hi_reg_read_val32(addr) &= ~((((unsigned int)1 << (bits)) - 1) << (pos)))
#define hi_reg_setbits(addr, pos, bits, val) (hi_reg_read_val32(addr) =           \
    (hi_reg_read_val32(addr) & (~((((unsigned int)1 << (bits)) - 1) << (pos)))) | \
    ((unsigned int)((val) & (((unsigned int)1 << (bits)) - 1)) << (pos)))
#define hi_reg_getbits(addr, pos, bits) ((hi_reg_read_val32(addr) >> (pos)) & (((unsigned int)1 << (bits)) - 1))

#define hi_reg_write16(addr, val)      (*(volatile unsigned short *)(uintptr_t)(addr) = (val))
#define hi_reg_read16(addr, val)       ((val) = *(volatile unsigned short *)(uintptr_t)(addr))
#define hi_reg_read_val16(addr)        (*(volatile unsigned short*)(uintptr_t)(addr))
#define hi_reg_clrbit16(addr, pos)       ((hi_reg_read_val16(addr)) &= ~((unsigned short)(1) << (pos)))
#define hi_reg_setbit16(addr, pos)       ((hi_reg_read_val16(addr)) |= ((unsigned short)(1) << (pos)))
#define hi_reg_clrbits16(addr, pos, bits) (hi_reg_read_val16(addr) &= ~((((unsigned short)1 << (bits)) - 1) << (pos)))
#define hi_reg_setbits16(addr, pos, bits, val) (hi_reg_read_val16(addr) =           \
    (hi_reg_read_val16(addr) & (~((((unsigned short)1 << (bits)) - 1) << (pos)))) | \
    ((unsigned short)((val) & (((unsigned short)1 << (bits)) - 1)) << (pos)))
#define hi_reg_getbits16(addr, pos, bits) ((hi_reg_read_val16(addr) >> (pos)) & (((unsigned short)1 << (bits)) - 1))

#define reg_write32(addr, val) (*(volatile unsigned int *)(uintptr_t)(addr) = (val))
#define reg_read32(addr, val)  ((val) = *(volatile unsigned int *)(uintptr_t)(addr))
#define reg_read_val(addr)   (*(volatile unsigned *)(uintptr_t)(addr))

#ifndef BSP_RAM_TEXT_SECTION
#define BSP_RAM_TEXT_SECTION       __attribute__ ((section(".bsp.ram.text")))
#endif

#ifndef BSP_ROM_RODATA_SECTION
#define BSP_ROM_RODATA_SECTION      __attribute__ ((section(".bsp.rom.rodata")))
#endif

#ifndef BSP_ROM_DATA0_SECTION
#define BSP_ROM_DATA0_SECTION       __attribute__ ((section(".bsp.rom.data0")))
#endif

#ifndef ROM_TEXT_PATCH_SECTION
#define ROM_TEXT_PATCH_SECTION       __attribute__ ((section(".rom.text.patch")))
#endif

#ifndef LP_RAM_BSS_SECTION
#define LP_RAM_BSS_SECTION           __attribute__ ((section(".lowpower.ram.bss")))
#endif

#ifndef ROM_DATA_PATCH_SECTION
#define ROM_DATA_PATCH_SECTION       __attribute__ ((section(".rom.data.patch")))
#endif

#ifndef EXTERN_ROM_BSS_SECTION
#define EXTERN_ROM_BSS_SECTION       __attribute__ ((section(".extern.rom.bss")))
#endif

#ifndef EXTERN_ROM_DATA1_BSS_SECTION
#define EXTERN_ROM_DATA1_BSS_SECTION       __attribute__ ((section(".extern.rom.data1.bss")))
#endif

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#ifndef CRYPTO_RAM_TEXT_SECTION
#define CRYPTO_RAM_TEXT_SECTION      __attribute__ ((section(".crypto.ram.text")))
#endif
#else
#ifndef CRYPTO_RAM_TEXT_SECTION
#define CRYPTO_RAM_TEXT_SECTION
#endif
#endif

#ifdef HAVE_PCLINT_CHECK
#define hi_likely(x)    (x)
#define hi_unlikely(x)  (x)
#else
#define hi_likely(x) __builtin_expect(!!(x), 1)
#define hi_unlikely(x) __builtin_expect(!!(x), 0)
#endif
#define HI_ALWAYS_STAIC_INLINE __attribute__((always_inline)) static inline

#ifdef HAVE_PCLINT_CHECK
#define hi_offset_of_member(type, member)   0
#else
#define hi_offset_of_member(type, member)   ((hi_u32)(&((type *)0)->member))
#endif
#define BITS_PER_BYTE   8
#define HEXADECIMAL     16
#define DECIMAL         10
#define SZ_1KB 1024
#define SZ_1MB (SZ_1KB * SZ_1KB)
#define SZ_4KB 4096
/*****************************************************************************/
#include <hi_errno.h>

#define HI_SYS_WAIT_FOREVER           0xFFFFFFFF

#endif /* __HI_TYPES__BASE_H__ */
