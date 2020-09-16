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

#ifndef _UPG_COMMON_H_
#define _UPG_COMMON_H_

#include <hi_upg_api.h>
#include <hi_upg_file.h>
#include <hi_sal.h>
#include <hi_ft_nv.h>
#include <hi_nvm.h>
#include <hi_nv.h>
#include <hi_partition_table.h>
#include <hi_mem.h>
#include <hi_flash.h>
#include <hi_efuse.h>
#include <hi_sem.h>
#include <hi_stdlib.h>
#include <hi_task.h>

#ifdef UPG_DEBUG
#include <hi_early_debug.h>
#define upg_print(ftm...) \
    do {                  \
        printf(ftm);      \
    } while (0);
#else
#define upg_print(ftm...)
#endif

#define HI_UPG_MODE_NORMAL  0      /* normal mode */
#define HI_UPG_MODE_UPGRADE 1      /* upgrade mode */
#define HI_UPG_MODE_UPGRADE_WAIT 2 /* asynchronous upgrade mode */

#define UPG_FLASH_RETRY_TIMES 3
#define UPG_MAX_BACKUP_CNT    3

#define UPG_FLASH_BLOCK_SIZE 0x1000
#define UPG_NV_KERNEL_OFFSET 0x1000

#define PRODUCT_FLASH_MAX_SIZE 0x200000

#define BIT_U8   8
#define BIT_U16  16
#define MASK_U16 0xFFFF

typedef enum {
    HI_MODE_PKCS_V15 = 0x00,
    HI_MODE_PKCS_PSS = 0x01,
    HI_MODE_ECC = 0x10,
} hi_padding_mode;

typedef struct {
    hi_bool is_init;
    hi_bool is_upg_process;
    hi_bool check_head_flag;
    hi_bool transmit_finish_flag;
    hi_u32 cache_size; /* cached file size */
    hi_u32 file_addr;  /* flash addr of cached file */
    hi_u32 upg_sem;
    hi_u32 rsa_key_addr; /* flash addr of rsa key */
    hi_u32 ecc_key_addr; /* flash addr of ecc key */
    hi_u32 cur_kernel_size; /* current kernel size */
    hi_upg_common_head common_head;
} upg_ctx;

typedef hi_u8 srv_bit; /* value 0 or 1 */
#define SRV_BIT_LOW  0
#define SRV_BIT_HIGH 1

/*
    i must 0~7 b must 0 or 1 x must a character
    high ---------------->  low
    **************************
     7  6  5  4  3  2   1   0
    **************************
 */
#define bit_set(x, i, b) ((x) = (hi_u8)((b) ? ((1 << (i)) | (x)) : ((~(hi_u8)(1 << (i))) & (x))))
#define bit_get(x, i)    (((1 << (i)) & (x)) ? 1 : 0)

#define upg_mem_free(sz)                  \
    do {                                  \
        if ((sz) != HI_NULL) {            \
            hi_free(HI_MOD_ID_UPG, (sz)); \
        }                                 \
        (sz) = HI_NULL;                   \
    } while (0)

#define upg_align_128bit(x) ((((x) + (BIT_U16) - 1) / (BIT_U16)) * (BIT_U16))
#define upg_align_pre(val, a)    ((val) & (~((a) - 1)))
#define upg_align_next(val, a)   ((((val) + ((a) - 1)) & (~((a) - 1))))

hi_u32 upg_get_efuse_code_ver(hi_u8 *ver);
hi_u32 upg_get_efuse_boot_ver(hi_u8 *ver);
hi_u32 upg_get_rsa_key_from_boot(hi_u8 *key, hi_u32 key_len);
hi_u32 upg_get_ecc_key_from_boot(hi_u8 *key, hi_u32 key_len);
hi_u32 upg_get_max_file_len(hi_u8 file_type, hi_u32 *file_len);
hi_bool upg_tool_bit_test(const hi_u8 *data, hi_u16 pos, hi_u16 data_len);
hi_void upg_tool_bit_set(hi_u8 *data, hi_u16 pos, hi_u8 val);
hi_u32 upg_get_start_up_cfg(hi_nv_ftm_startup_cfg *cfg);
hi_void upg_clear_contset(hi_u8 *content, hi_u32 content_len);

#endif /* _UPG_COMMON_H_ */
