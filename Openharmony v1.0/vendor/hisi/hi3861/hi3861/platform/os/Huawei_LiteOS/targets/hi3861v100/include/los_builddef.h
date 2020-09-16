/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: los_builddef
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

/**
 * @defgroup los_builddef
 * @ingroup kernel
 */

#ifndef _LOS_BUILDEF_H
#define _LOS_BUILDEF_H
#include "los_compiler.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup los_builddef
 * Little endian
 */
#define OS_LITTLE_ENDIAN                                    0x1234

/**
 * @ingroup los_builddef
 * Big endian
 */
#define OS_BIG_ENDIAN                                       0x4321

/**
 * @ingroup los_builddef
 * Byte order
 */
#ifndef OS_BYTE_ORDER
#define OS_BYTE_ORDER                                       OS_LITTLE_ENDIAN
#endif

/* Define OS code data sections */
/* The indicator function is inline */
/**
 * @ingroup los_builddef
 * Allow inline sections
 */
#ifndef LITE_OS_SEC_ALW_INLINE
#define LITE_OS_SEC_ALW_INLINE      __attribute__((always_inline))
#endif

/**
 * @ingroup los_builddef
 * Vector table section
 */
#ifndef LITE_OS_SEC_VEC
#define LITE_OS_SEC_VEC          __attribute__ ((section(".data.vector")))
#endif

/**
 * @ingroup los_builddef
 * .Text section (Code section)
 */
#ifndef LITE_OS_SEC_TEXT
#define LITE_OS_SEC_TEXT
#endif

/**
 * @ingroup los_builddef
 * .Text.ddr section
 */
#ifndef LITE_OS_SEC_TEXT_MINOR
#define LITE_OS_SEC_TEXT_MINOR
#endif

/**
 * @ingroup los_builddef
 * .Text.init section
 */
#ifndef LITE_OS_SEC_TEXT_INIT
#define LITE_OS_SEC_TEXT_INIT
#endif

/**
 * @ingroup los_builddef
 * Redirect .Text  section (Code section)
 */
#ifndef LITE_OS_SEC_TEXT_REDIRECT
#define LITE_OS_SEC_TEXT_REDIRECT                   LITE_OS_SEC_TEXT
#endif

/**
 * @ingroup los_builddef
 * Redirect .Text.ddr section
 */
#ifndef LITE_OS_SEC_TEXT_MINOR_REDIRECT
#define LITE_OS_SEC_TEXT_MINOR_REDIRECT                   LITE_OS_SEC_TEXT_MINOR
#endif

/**
 * @ingroup los_builddef
 * Redirect .Text.init section
 */
#ifndef LITE_OS_SEC_TEXT_INIT_REDIRECT
#define LITE_OS_SEC_TEXT_INIT_REDIRECT                   LITE_OS_SEC_TEXT_INIT
#endif


#ifndef LITE_OS_RAM_SECTION
#define LITE_OS_RAM_SECTION                   __attribute__ ((section(".ram.kernel")))
#endif

/**
 * @ingroup los_builddef
 * .rodata section
 */
#ifndef LITE_OS_SEC_RODATA
#define LITE_OS_SEC_RODATA
#endif

/**
 * @ingroup los_builddef
 * .Data section
 */
#ifndef LITE_OS_SEC_DATA
#define LITE_OS_SEC_DATA                      __attribute__ ((section(".data")))
#endif

/**
 * @ingroup los_builddef
 * .remap section
 */
#ifndef LITE_OS_SEC_REMAP
#define LITE_OS_SEC_REMAP                      __attribute__ ((section(".fpb.remap")))
#endif


/**
 * @ingroup los_builddef
 * .Data.init section
 */
#ifndef LITE_OS_SEC_DATA_INIT
#define LITE_OS_SEC_DATA_INIT
#endif

/**
 * @ingroup los_builddef
 * Not initialized variable section
 */
#ifndef LITE_OS_SEC_BSS
#define LITE_OS_SEC_BSS
#endif

/**
 * @ingroup los_builddef
 * .bss.ddr section
 */
#ifndef LITE_OS_SEC_BSS_MINOR
#define LITE_OS_SEC_BSS_MINOR
#endif

/**
 * @ingroup los_builddef
 * .bss.init sections
 */
#ifndef LITE_OS_SEC_BSS_INIT
#define LITE_OS_SEC_BSS_INIT
#endif

/**
 * @ingroup los_builddef
 * .text.rom.libsec section
 */
#ifndef LIB_SECURE_SEC_TEXT
#define LIB_SECURE_SEC_TEXT
#endif

/**
 * @ingroup los_builddef
 * .text.rom.libc section
 */
#ifndef LIBC_SEC_TEXT
#define LIBC_SEC_TEXT
#endif

/**
 * @ingroup los_builddef
 * Define extern
 */
#define EXTERN_FAR             extern

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _LOS_BUILDEF_H */
