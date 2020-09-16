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
 *
 * Description: head file of osal lib define for cipher
 */

#ifndef __DRV_OSAL_LIB_H__
#define __DRV_OSAL_LIB_H__

#define __LITEOS_CRYPTO_SUPPORT__
#ifdef __LITEOS_CRYPTO_SUPPORT__
#include <stdio.h>
#include <stdlib.h>
#include <securec.h>
#include "hi_types.h"
#include <pthread.h>
#include <hi_isr.h>
#include <hi_time.h>
#include <hi_types_base.h>
#include <hi_mux.h>
#include <hi_sem.h>
#include <hi_mem.h>
#include <cipher.h>
#else
#include <hi_types.h>
#include <hi_boot_rom.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif  /* __cplusplus */


/* Turn off the interrupt switch of cipher.
 * #define CRYPTO_OS_INT_SUPPORT
 *
 * Turn off the debug switch of cipher.
 * #define CRYPTO_DEBUG_SUPPORT
 */

#define CRYPTO_QUEUE_HEAD                          hi_u32
#define crypto_queue_init(x)                       hi_sem_create(&(x), 0)
#define crypto_queue_wait_up(x)                    hi_sem_signal(x)
#define crypto_queue_wait_timeout(x, con, time)    hi_sem_wait(x, time)
#define crypto_queue_delete(x)                     hi_sem_delete(x);

#define crypto_irq_enable(irq)                     hi_irq_enable(irq)
#define crypto_irq_disable(irq)                    hi_irq_disable(irq)
#define crypto_request_irq(irq, func, name)        hi_irq_request(irq, HI_IRQ_FLAG_PRI1, (irq_routine)(func), 0);
#define crypto_free_irq(irq, name)                 hi_irq_free(irq)

#define crypto_udelay(us)                          hi_udelay(us)

#define crypto_reg_read(addr)                      (*(volatile hi_u32 *)(uintptr_t)(addr))
#define crypto_reg_write(addr, val)                (*(volatile hi_u32 *)(uintptr_t)(addr) = (val))

/* crypto mutex adapt. */
typedef struct {
    hi_u32 mux_id;
    hi_bool is_liteos;
    hi_u8 resv[3];     /* 3 bytes reserved */
}crypto_mutex_ctx;

#define CRYPTO_MUX_TIME_OUT                        300
hi_u32 crypto_mutex_init(crypto_mutex_ctx *ctx);
hi_u32 crypto_mutex_lock(const crypto_mutex_ctx *ctx);
hi_u32 crypto_mutex_unlock(const crypto_mutex_ctx *ctx);
hi_u32 crypto_mutex_destroy(crypto_mutex_ctx *ctx);

/* clock reg read or write. */
#define REG_CRG_BASE                               0x40c00000
#define clk_read(offset)                           crypto_reg_read(REG_CRG_BASE + (offset))
#define clk_write(offset, val)                     crypto_reg_write(REG_CRG_BASE + (offset), (val))

/* word index number. */
#define WORD_INDEX_0                               0
#define WORD_INDEX_1                               1
#define WORD_INDEX_2                               2
#define WORD_INDEX_3                               3

/* Boundary value 1. */
#define BOUND_VALUE_1                              1

/* multiple value */
#define MULTIPLE_VALUE_1                           1
#define MULTIPLE_VALUE_2                           2

#define SHIFT_4BITS                                4
#define SHIFT_8BITS                                8
#define SHIFT_16BITS                               16
#define SHIFT_24BITS                               24
#define MAX_LOW_2BITS                              3
#define MAX_LOW_3BITS                              7
#define MAX_LOW_4BITS                              0xF
#define MAX_LOW_8BITS                              0xFF
#define WORD_WIDTH                                 4
#define BYTE_BITS                                  8

#define CRYPTO_NUM_1                               1
#define CRYPTO_NUM_2                               2
#define crypto_unused(x)                           ((x) = (x))

#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif

hi_void *crypto_calloc(hi_u32 n, hi_u32 size, hi_bool is_liteos);
hi_u32 crypto_free(hi_void *ptr, hi_bool is_liteos);

#define DCACHE_ENABLE                       1
#define DCACHE_EN_REG                       0x7C1       /* DCACHE enable reg */
#define DCACHE_FLUSH_REG                    0x7C3       /* DCACHE fluch reg */
#define DCACHE_CLEAN_INVALI                 0x000C      /* Bit[2]:invalidation ;Bit[3]:clean */

#define CRYPTO_CACHE_LINE_SIZE              32
#define CRYPTO_DCACHE_BY_ADDR_MAX_SIZE      512         /* 512 bytes. */

hi_u32 crypto_flush_dcache_by_addr(hi_u32 src_addr, hi_u32 size);

/* print for DFX infomation. */
#define HI_PRINT printf
#ifdef HI_LOG_CIPHER_DEBUG_SUPPORT
#define hi_log_debug(fmt...)   \
    do { \
        HI_PRINT("[HI-CIPHER-DEBUG]%s[%d]:", __FUNCTION__, __LINE__); \
        HI_PRINT(fmt); \
    } while (0);
#else
#define hi_log_debug(fmt...)
#endif

#ifdef HI_LOG_CIPHER_INFO_SUPPORT
#define hi_log_info(fmt...)   \
    do { \
        HI_PRINT("[HI-CIPHER-INFO]%s[%d]:", __FUNCTION__, __LINE__); \
        HI_PRINT(fmt); \
    } while (0);
#else
#define hi_log_info(fmt...)
#endif

#ifdef CRYPTO_DEBUG_SUPPORT
#define hi_log_error(fmt...)   \
    do { \
        HI_PRINT("[HI-CIPHER-ERROR]%s[%d]:", __FUNCTION__, __LINE__); \
        HI_PRINT(fmt); \
    } while (0);

#define hi_log_print_func_err(_func, _err_code)  \
    hi_log_error("Call %s return [0x%08x]\n", #_func, (unsigned int)(_err_code));

#define hi_log_print_err_code(_err_code)        \
    hi_log_error("Error code: [0x%08x]\n", (unsigned int)(_err_code));

#define hi_log_check_param(_val)                              \
    do {                                                      \
        if (_val) {                                           \
            hi_log_error("%s\n", #_val);                      \
            hi_log_print_err_code(HI_ERR_CIPHER_INVALID_PARAMETER); \
            return HI_ERR_CIPHER_INVALID_PARAMETER;                \
        }                                                     \
    } while (0)
#else
#define hi_log_error(fmt...)
#define hi_log_print_func_err(_func, _err_code)
#define hi_log_print_err_code(_err_code)

#define hi_log_check_param(_val)                              \
    do {                                                      \
        if (_val) {                                           \
            return HI_ERR_CIPHER_INVALID_PARAMETER;           \
        }                                                     \
    } while (0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __DRV_OSAL_LIB_H__ */
