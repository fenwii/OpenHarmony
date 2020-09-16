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

#ifndef __EFUSE_DRV_H__
#define __EFUSE_DRV_H__
#include <hi_flashboot.h>

typedef struct {
    hi_u16 id_start_bit;    /* Start bit */
    hi_u16 id_size;         /* Unit: bit */
    hi_u8 attr;             /* 0x0:None,0x1:RO,0x2:WO,0x3:R/W */
} hi_efuse_stru;

#define EFUSE_PGM_EN   (HI_EFUSE_REG_BASE + 0x0)
#define EFUSE_PGM_ADDR (HI_EFUSE_REG_BASE + 0x4)
#define EFUSE_RD_EN    (HI_EFUSE_REG_BASE + 0x8)
#define EFUSE_RD_ADDR  (HI_EFUSE_REG_BASE + 0xc)
#define EFUSE_STATUS   (HI_EFUSE_REG_BASE + 0x10)
#define EFUSE_RDATA    (HI_EFUSE_REG_BASE + 0x14)

#define EFUSE_WRITE_READY_STATUS (1 << 0) /* Write completion status.
                                             The value 1 indicates that the write is complete. */
#define EFUSE_READ_READY_STATUS  (1 << 1) /* Read completion status.
                                             The value 1 indicates that the read is complete. */
#define EFUSE_STATUS_MASK        (0x7 << 2)
#define EFUSE_PO_STATUS_READY    (0x1 << 2) /* Whether the read operation is complete after power-on.
                                               The value 1 indicates that the read operation is complete. */
#define EFUSE_STATUS_READY       (0x1 << 4) /* Busy/idle status. The value 0 indicates idle. */

#define EFUSE_CTRL_ST   (0x1 << 5)
#define EFUSE_EN_SWITCH (1 << 0)
#define EFUSE_EN_OK     0

#define EFUSE_STATUS_RD    (1 << 1)
#define EFUSE_8_BIT        8
#define EFUSE_KEY_LOCK_BIT 2

#define EFUSE_TIMEOUT_DEFAULT 1000000 /* 1000000us */
#define EFUSE_TIMECNT_TICK    10

#define EFUSE_PGM_ADDR_SIZE          2048
#define EFUSE_USER_RESEVED_START_BIT 1884
#define EFUSE_USER_RESEVED_END_BIT   2011
#define EFUSE_LOCK_START_BITS        2012
#define EFUSE_LOCK_FIELD2_START_BITS 235
#define EFUSE_LOCK_SIZE              36
#define EFUSE_LOCK_FIELD2_SIZE       5
#define EFUSE_MAX_INDEX_SIZE         32

#define EFUSE_IDX_NRW 0x0
#define EFUSE_IDX_RO  0x1
#define EFUSE_IDX_WO  0x2
#define EFUSE_IDX_RW  0x3

hi_efuse_stru *get_efuse_cfg(hi_void);
hi_void get_efuse_cfg_by_id(hi_efuse_idx idx, hi_u16 *start_bit, hi_u16 *size, hi_u8 *attr);
hi_u32 efuse_read_bits(hi_u16 start_bit, hi_u16 size, hi_u8 *key_data);
hi_u32 efuse_write_bits(hi_u16 start_bit, hi_u16 size, const hi_u8 *key_data, hi_u8 *err_state);

#endif /* __EFUSE_H__ */

