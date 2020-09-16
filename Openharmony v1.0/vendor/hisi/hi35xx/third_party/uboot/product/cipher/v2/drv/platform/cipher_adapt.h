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
 * Description   : head file for cipher drv adapt.

 */

#ifndef __CIPHER_ADAPT_H_
#define __CIPHER_ADAPT_H_

#ifndef HI_MINIBOOT_SUPPORT
#include <common.h>
#else
#include "delay.h"
#include "malloc.h"
#include "string.h"
#include "stdio.h"
#endif
#include "malloc.h"

#include "hi_types.h"
#include "drv_cipher_ioctl.h"
#include "hi_drv_cipher.h"
#include "cipher_config.h"
#include "spacc_intf.h"
#include "drv_rng.h"
#include "drv_rsa.h"
#include "drv_klad.h"
#include "hal_otp.h"
#include "hi_drv_compat.h"

/**************************** M A C R O ****************************/
#define HI_ERR_CIPHER_NOT_INIT                     (hi_s32)(0x804D0001)
#define HI_ERR_CIPHER_INVALID_HANDLE               (hi_s32)(0x804D0002)
#define HI_ERR_CIPHER_INVALID_POINT                (hi_s32)(0x804D0003)
#define HI_ERR_CIPHER_INVALID_PARA                 (hi_s32)(0x804D0004)
#define HI_ERR_CIPHER_FAILED_INIT                  (hi_s32)(0x804D0005)
#define HI_ERR_CIPHER_FAILED_GETHANDLE             (hi_s32)(0x804D0006)
#define HI_ERR_CIPHER_FAILED_RELEASEHANDLE         (hi_s32)(0x804D0007)
#define HI_ERR_CIPHER_FAILED_CONFIGAES             (hi_s32)(0x804D0008)
#define HI_ERR_CIPHER_FAILED_CONFIGDES             (hi_s32)(0x804D0009)
#define HI_ERR_CIPHER_FAILED_ENCRYPT               (hi_s32)(0x804D000A)
#define HI_ERR_CIPHER_FAILED_DECRYPT               (hi_s32)(0x804D000B)
#define HI_ERR_CIPHER_BUSY                         (hi_s32)(0x804D000C)
#define HI_ERR_CIPHER_NO_AVAILABLE_RNG             (hi_s32)(0x804D000D)

#define HI_ID_CIPHER                        100

#define CIPHER_IOR                          _IOWR
#define CIPHER_IOW                          _IOW
#define CIPHER_IOWR                         _IOWR

#define CIPHER_IOC_DIR                      _IOC_DIR
#define CIPHER_IOC_TYPE                     _IOC_TYPE
#define CIPHER_IOC_NR                       _IOC_NR
#define CIPHER_IOC_SIZE                     _IOC_SIZE
#define u32_to_point(addr)                  ((hi_void*)((hi_size_t)(addr)))
#define point_to_u32(addr)                  ((hi_u32)((hi_size_t)(addr)))

#define hal_cipher_read_reg(addr, result)   (*(result) = *(volatile unsigned int *)(addr))
#define hal_cipher_write_reg(addr, result)  (*(volatile unsigned int *)(addr) = (result))

#define hal_set_bit(src, bit)               ((src) |= (1 << (bit)))
#define hal_clear_bit(src, bit)             ((src) &= ~(1 << (bit)))

#define cipher_cpu_to_be16(v) (((v) << 8) | ((v) >> 8))
#define cipher_cpu_to_be32(v) (((v) >> 24) | (((v) >> 8) & 0xff00) | (((v) << 8) & 0xff0000) | ((v) << 24))
#define cipher_cpu_to_be64(x) ((hi_u64)(                         \
    (((x) & 0x00000000000000ffULL) << 56) | (((x) & 0x000000000000ff00ULL) << 40) |   \
    (((x) & 0x0000000000ff0000ULL) << 24) | (((x) & 0x00000000ff000000ULL) <<  8) |   \
    (((x) & 0x000000ff00000000ULL) >>  8) | (((x) & 0x0000ff0000000000ULL) >> 24) |   \
    (((x) & 0x00ff000000000000ULL) >> 40) | (((x) & 0xff00000000000000ULL) >> 56)))

/**************************** S T D L I B ****************************/
#define cipher_ioremap_nocache(addr, size)  (hi_void*)(addr)
#define cipher_iounmap(x)

void *crypto_memset(hi_void *dst, unsigned int dlen, unsigned val, unsigned int len);
int  crypto_memcmp(const hi_void *a, const hi_void *b, unsigned len);
void *crypto_memcpy(hi_void *dst, unsigned dstlen, const hi_void *src, unsigned len);
hi_s32 cipher_waitdone_callback(hi_void *param);

#define CIPHER_MUTEX                        hi_void *
#define cipher_mutex_init(x)
#define cipher_mutex_lock(x)                0
#define cipher_mutex_unlock(x)

#define CIPHER_QUEUE_HEAD                   hi_void *
#define cipher_queue_init(x)
#define cipher_queue_wait_up(x)
#define cipher_queue_wait_timeout(head, con, time)

#define cipher_request_irq(irq, func, name)
#define cipher_free_irq(irq, name)
#define CIPHER_IRQRETURN_T                  hi_s32
#define CIPHER_IRQ_HANDLED                  1

#define cipher_copy_from_user(s, d, l)      (memcpy(s, d, l), 0)
#define cipher_copy_to_user(s, d, l)        (memcpy(s, d, l), 0)

#define cipher_malloc(x)                    malloc(x)
#define cipher_free(x)                      free(x)

#define cipher_msleep(msec)                 udelay(1000)
#define HI_PRINT                            printf
#define hi_err_cipher(fmt...)               HI_PRINT(fmt)
#define hi_info_cipher(fmt...)              // HI_PRINT(fmt)
#define CIPHER_PROC_PRINTF                  // osal_seq_printf

#define cipher_min(a, b) ((a) < (b) ? (a) : (b))

void hex2str(char buf[2], hi_u8 val); /* 2 buf size */

/**************************** P R I V A T E ****************************/
typedef struct {
    hi_void *start_vir_addr;
    hi_size_t start_phy_addr;
    hi_u32 mmz_addr;
    hi_u32 mmz_size;
} cipher_mmz_buf_t;

hi_s32  cipher_mmz_alloc_remap(hi_char *name, cipher_mmz_buf_t *cipher_mmz);
hi_void cipher_mmz_release_unmap(cipher_mmz_buf_t *cipher_mmz);
hi_s32  cipher_mmz_map(cipher_mmz_buf_t *cipher_mmz);
hi_void cipher_mmz_unmap(cipher_mmz_buf_t *cipher_mmz);

#endif

