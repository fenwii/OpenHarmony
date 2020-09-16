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
 * Description   : head file for cipher osal lib
 */

#ifndef __CIPHER_OSAL_H__
#define __CIPHER_OSAL_H__

#ifndef HI_MINIBOOT_SUPPORT
#include <common.h>
#else
#include "string.h"
#include "stdio.h"
#endif
#include "common.h"
#include "malloc.h"
#include "hi_types.h"
#include "hi_drv_cipher.h"
#include "drv_cipher_ioctl.h"
#include "hi_mpi_cipher.h"
#define CIPHER_KLAD_SUPPORT
#define HASH_BLOCK_SIZE                     128
#define HASH_RESULT_MAX_LEN                 64
#define HASH_RESULT_MAX_LEN_IN_WORD         16

#define HI_ERR_CIPHER_NOT_INIT              (hi_s32)(0x804D0001)
#define HI_ERR_CIPHER_INVALID_HANDLE        (hi_s32)(0x804D0002)
#define HI_ERR_CIPHER_INVALID_POINT         (hi_s32)(0x804D0003)
#define HI_ERR_CIPHER_INVALID_PARA          (hi_s32)(0x804D0004)
#define HI_ERR_CIPHER_FAILED_INIT           (hi_s32)(0x804D0005)
#define HI_ERR_CIPHER_FAILED_GETHANDLE      (hi_s32)(0x804D0006)
#define HI_ERR_CIPHER_FAILED_RELEASEHANDLE  (hi_s32)(0x804D0007)
#define HI_ERR_CIPHER_FAILED_CONFIGAES      (hi_s32)(0x804D0008)
#define HI_ERR_CIPHER_FAILED_CONFIGDES      (hi_s32)(0x804D0009)
#define HI_ERR_CIPHER_FAILED_ENCRYPT        (hi_s32)(0x804D000A)
#define HI_ERR_CIPHER_FAILED_DECRYPT        (hi_s32)(0x804D000B)
#define HI_ERR_CIPHER_BUSY                  (hi_s32)(0x804D000C)
#define HI_ERR_CIPHER_NO_AVAILABLE_RNG      (hi_s32)(0x804D000D)

#define cipher_cpu_to_be16(v)               (((v) << 8) | ((v) >> 8))

#define cipher_cpu_to_be32(v)                                   \
    ((((hi_u32)(v)) >> 24) | ((((hi_u32)(v)) >> 8) & 0xff00) |  \
     ((((hi_u32)(v)) << 8) & 0xff0000) | (((hi_u32)(v)) << 24))

#define cipher_cpu_to_be64(x)                                           \
    ((((hi_u64)(x) & (hi_u64)0x00000000000000ffULL) << 56) |            \
     (((hi_u64)(x) & (hi_u64)0x000000000000ff00ULL) << 40) |            \
     (((hi_u64)(x) & (hi_u64)0x0000000000ff0000ULL) << 24) |            \
     (((hi_u64)(x) & (hi_u64)0x00000000ff000000ULL) << 8)  |            \
     (((hi_u64)(x) & (hi_u64)0x000000ff00000000ULL) >> 8)  |            \
     (((hi_u64)(x) & (hi_u64)0x0000ff0000000000ULL) >> 24) |            \
     (((hi_u64)(x) & (hi_u64)0x00ff000000000000ULL) >> 40) |            \
     (((hi_u64)(x) & (hi_u64)0xff00000000000000ULL) >> 56))

#define cipher_min(a, b) ((a) < (b) ? (a) : (b))

#define UMAP_DEVNAME_CIPHER "cipher"
#define UMAP_CIPHER_MINOR_BASE              50

#define get_ulong_low(dw) (unsigned int)(dw)
#define get_ulong_high(dw) 0
#define make_ulong(low, high) (low)

#define HI_PRINT printf
#define hi_err_cipher(fmt...)       HI_PRINT(fmt)
#define hi_info_cipher(fmt...)      // HI_PRINT(fmt)

/* ************************* params check api ******************** */
#define inlet_var_over_max_return(val, max)    \
    do {                                       \
        if ((val) > (max)) {                   \
            hi_err_cipher("inlet param %s = 0x%x overflow, must less than %s(0x%x).\n", \
                #val, val, #max, max);         \
            return HI_ERR_CIPHER_INVALID_PARA; \
        }                                      \
    } while (0)

#define inlet_var_is_zero_return(val)                           \
    do {                                                        \
        if ((val) == 0) {                                       \
            hi_err_cipher("inlet param " #val " is zero\n");    \
            return HI_ERR_CIPHER_INVALID_PARA;                  \
        }                                                       \
    } while (0)

#define inlet_var_is_null_return(p)                         \
    do {                                                    \
        if ((p) == HI_NULL) {                               \
            hi_err_cipher("inlet param " #p " is null\n");  \
            return HI_ERR_CIPHER_INVALID_POINT;             \
        }                                                   \
    } while (0)

#define CIPHER_MUTEX hi_void *
#define cipher_mutex_init(x)
#define cipher_mutex_lock(x)
#define cipher_mutex_unlock(x)
#define cipher_mutex_destroy(x)

#define cipher_open(a, b, c)            (cipher_module_init(), 1)
#define cipher_close(x)                 (cipher_module_exit())
#define cipher_ioctl(dev, cmd, argp)    drv_cipher_ioctl(cmd, argp, NULL)

#define cipher_malloc(x) malloc(x)
#define cipher_free(x) free(x)

hi_void *crypto_memset(hi_void *dst, unsigned int dlen, unsigned val, unsigned int len);
int crypto_memcmp(const hi_void *a, const hi_void *b, unsigned len);
hi_void *crypto_memcpy(hi_void *dst, unsigned dstlen, const hi_void *src, unsigned len);

hi_s32 mpi_cipher_get_random_number(hi_u32 *random_number, hi_u32 time_out_us);

extern hi_s32 g_cipher_dev_fd;
extern hi_s32 g_cipher_init_counter;

#define check_cipher_not_open_return()              \
    do {                                            \
        if (g_cipher_init_counter < 0) {            \
            hi_err_cipher("CIPHER is not open.\n"); \
            return HI_ERR_CIPHER_NOT_INIT;          \
        }                                           \
    } while (0)

typedef struct {
    hi_void *start_vir_addr;
    hi_size_t start_phy_addr;
    hi_u32 mmz_size;
} cipher_mmz_buf_t;

#endif
