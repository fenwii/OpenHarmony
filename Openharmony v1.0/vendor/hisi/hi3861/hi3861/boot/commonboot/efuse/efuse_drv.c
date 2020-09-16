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

#include "efuse_drv.h"
#define THREE_BITS_OFFSET 3

hi_efuse_stru g_efuse_cfg[HI_EFUSE_IDX_MAX] = {
    { 0,    8,   EFUSE_IDX_RW },
    { 8,    192, EFUSE_IDX_RW },
    { 200,  10,  EFUSE_IDX_RW },
    { 210,  10,  EFUSE_IDX_RW },
    { 220,  2,   EFUSE_IDX_RW },
    { 222,  2,   EFUSE_IDX_RW },
    { 224,  2,   EFUSE_IDX_RW },
    { 234,  1,   EFUSE_IDX_RW },
    { 240,  256, EFUSE_IDX_RW },
    { 496,  256, EFUSE_IDX_WO },
    { 752,  256, EFUSE_IDX_RW },
    { 1008, 32,  EFUSE_IDX_RW },
    { 1040, 8,   EFUSE_IDX_RW },
    { 1048, 24,  EFUSE_IDX_RW },
    { 1072, 1,   EFUSE_IDX_RW },
    { 1073, 1,   EFUSE_IDX_RW },
    { 1074, 1,   EFUSE_IDX_RW },
    { 1075, 1,   EFUSE_IDX_RW },
    { 1076, 1,   EFUSE_IDX_RW },
    { 1077, 1,   EFUSE_IDX_RW },
    { 1078, 1,   EFUSE_IDX_RW },
    { 1079, 1,   EFUSE_IDX_RW },
    { 1080, 2,   EFUSE_IDX_RW },
    { 1082, 2,   EFUSE_IDX_RW },
    { 1084, 4,   EFUSE_IDX_RW },
    { 1088, 8,   EFUSE_IDX_RW },
    { 1096, 48,  EFUSE_IDX_RW },
    { 1144, 128, EFUSE_IDX_RW },
    { 1272, 32,  EFUSE_IDX_RW },
    { 1304, 32,  EFUSE_IDX_RW },
    { 1336, 32,  EFUSE_IDX_RW },
    { 1368, 32,  EFUSE_IDX_RW },
    { 1400, 32,  EFUSE_IDX_RW },
    { 1432, 32,  EFUSE_IDX_RW },
    { 1464, 32,  EFUSE_IDX_RW },
    { 1496, 32,  EFUSE_IDX_RW },
    { 1528, 32,  EFUSE_IDX_RW },
    { 1560, 32,  EFUSE_IDX_RW },
    { 1592, 32,  EFUSE_IDX_RW },
    { 1624, 32,  EFUSE_IDX_RW },
    { 1656, 16,  EFUSE_IDX_RW },
    { 1672, 48,  EFUSE_IDX_RW },
    { 1720, 128, EFUSE_IDX_RW },
    { 1848, 2,   EFUSE_IDX_RW },
    { 1850, 2,   EFUSE_IDX_RW },
    { 1852, 2,   EFUSE_IDX_RW },
    { 1854, 1,   EFUSE_IDX_RW },
    { 1855, 1,   EFUSE_IDX_RW },
    { 1856, 10,  EFUSE_IDX_RW },
    { 1866, 18,  EFUSE_IDX_RW },
    { 1884, 64,  EFUSE_IDX_RW },
    { 1948, 64,  EFUSE_IDX_RW },
    { 226,  8,   EFUSE_IDX_RW },
};


hi_efuse_stru *get_efuse_cfg(hi_void)
{
    return &g_efuse_cfg[0];
}

hi_void get_efuse_cfg_by_id(hi_efuse_idx idx, hi_u16 *start_bit, hi_u16 *size, hi_u8 *attr)
{
    hi_efuse_stru *efuse_cfg = get_efuse_cfg();

    /* Internal interface, which does not check input parameters. */
    if (start_bit != HI_NULL) {
        *start_bit = efuse_cfg[idx].id_start_bit;
    }

    if (size != HI_NULL) {
        *size = efuse_cfg[idx].id_size;
    }

    if (attr != HI_NULL) {
        *attr = efuse_cfg[idx].attr;
    }
}

hi_bool check_efuse_isbusy(hi_void)
{
    hi_u32 val = 0;
    hi_u32 cnt = 0;

    while (cnt < EFUSE_TIMEOUT_DEFAULT) {
        hi_reg_read(EFUSE_STATUS, val);
        if ((!(val & EFUSE_STATUS_READY)) && (val & EFUSE_PO_STATUS_READY)) {
            return HI_FALSE;
        }
        udelay(EFUSE_TIMECNT_TICK);
        cnt += EFUSE_TIMECNT_TICK;
    }
    return HI_TRUE;
}

hi_u32 efuse_write_bit(hi_u16 addr)
{
    hi_u32 val;
    hi_u32 cnt = 0;

    if (addr >= EFUSE_PGM_ADDR_SIZE) {
        return HI_ERR_EFUSE_INVALIDATE_PARA;
    }

    if (check_efuse_isbusy() == HI_TRUE) {
        boot_msg0("efuse is busy !");
        return HI_ERR_EFUSE_BUSY;
    }

    hi_reg_write(EFUSE_PGM_ADDR, addr);
    hi_reg_write(EFUSE_PGM_EN, HI_TRUE);

    /* Query the current status. */
    while (cnt < EFUSE_TIMEOUT_DEFAULT) {
        hi_reg_read(EFUSE_PGM_EN, val);
        if ((val & EFUSE_EN_SWITCH) == EFUSE_EN_OK) {
            break;
        }

        udelay(EFUSE_TIMECNT_TICK);
        cnt += EFUSE_TIMECNT_TICK;
    }

    if (cnt >= EFUSE_TIMEOUT_DEFAULT) {
        boot_msg0("timeout");
        return HI_ERR_EFUSE_TIMEOUT;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 efuse_read_bits(hi_u16 start_bit, hi_u16 size, hi_u8 *key_data)
{
    hi_u32 i;
    hi_u32 val;
    hi_u16 free_area_addr_start = start_bit;
    hi_u32 free_area_addr_end = start_bit + size;
    hi_u32 cnt;

    /* The start position and length must be 8-pixel aligned. */
    if (((start_bit & 0x7) != 0x0) || ((size & 0x7) != 0x0)) {
        boot_msg0("start_bits and lenth should be ALIGN_8!");
        return HI_ERR_EFUSE_INVALIDATE_PARA;
    }

    if (check_efuse_isbusy() == HI_TRUE) {
        boot_msg0("EFUSE is busy!");
        return HI_ERR_EFUSE_BUSY;
    }

    free_area_addr_start = free_area_addr_start >> 3; /* right shift 3bit */
    free_area_addr_end = free_area_addr_end >> 3;     /* right shift 3bit */

    for (i = free_area_addr_start; i < free_area_addr_end; i++) {
        hi_reg_write(EFUSE_RD_ADDR, i);
        hi_reg_write(EFUSE_RD_EN, HI_TRUE);
        /* Query the current status. */
        cnt = 0;
        while (cnt < EFUSE_TIMEOUT_DEFAULT) {
            hi_reg_read(EFUSE_RD_EN, val);
            if (((val & EFUSE_EN_SWITCH) == EFUSE_EN_OK) &&
                ((hi_reg_read_val32(EFUSE_STATUS) & EFUSE_READ_READY_STATUS) != EFUSE_EN_OK)) {
                cnt = 0;
                break;
            }
            udelay(1);
            cnt++;
        }

        if (cnt >= (EFUSE_TIMEOUT_DEFAULT)) {
            boot_msg0("timeout\r\n");
            return HI_ERR_EFUSE_TIMEOUT;
        }

        hi_reg_read(EFUSE_RDATA, val);
        key_data[i - free_area_addr_start] = (hi_u8)val;
    }

    return HI_ERR_SUCCESS;
}

hi_void efuse_get_errstate(hi_u16 byte_id, hi_u16 bit_id, hi_u8 *err_state)
{
    hi_u32 val = 0;

    hi_reg_read(EFUSE_STATUS, val);

    if (val & EFUSE_CTRL_ST) {
        err_state[byte_id] |= (hi_u8)(1 << bit_id);
    } else {
        err_state[byte_id] &= (~(hi_u8)(1 << bit_id));
    }
}

hi_u32 efuse_write_bits(hi_u16 start_bit, hi_u16 size, const hi_u8 *key_data, hi_u8 *err_state)
{
    hi_u16 i;
    hi_u16 j;
    hi_u16 a;
    hi_u16 b;
    hi_u32 ret;
    hi_u16 zero_count = 0;

    /* j: the current bit offset of key_data. */
    for (i = start_bit, j = 0; i < (start_bit + size); i++, j++) {
        a = j >> THREE_BITS_OFFSET; /* subscript of receive array. */
        b = j & 0x7;                /* bit offset in one byte. */

        if (key_data[a] & (hi_u8)(1 << b)) {
            ret = efuse_write_bit(i);
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            } else if (err_state != HI_NULL) {
                efuse_get_errstate(a, b, err_state);
            }
        } else {
            zero_count++;
        }
    }

    if (zero_count == size) {
        return HI_ERR_FAILURE;
    }
    return HI_ERR_SUCCESS;
}

