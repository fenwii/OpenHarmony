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

#include "hi_nvm.h"
#include <hi_boot_err.h>
#include <hi_flashboot.h>

typedef hi_u32(*hi_nvm_changed_notify_f) (hi_u8 id);

typedef struct {
    hi_u8 min_id;
    hi_u8 max_id;
    hi_u16 count;
} nvm_changed_proc_stru;
typedef struct {
    hi_u32 base_addr;
    hi_u32 total_size;
    hi_u32 block_size;
} nvm_basic_info;


HI_CONST hi_u32 g_ver_magic = 0x12345678;

static hi_nv_ctrl g_s_nv_ctrl[HI_TYPE_NV_MAX];
hi_u16 g_s_nv_change_notify_list_cnt = 0;

hi_u32 hi_crc32_nv(hi_u32 crc_start, HI_CONST hi_u8* buf, hi_u32 len, hi_u32 *crc_result)
{
    if (!buf || !len || !crc_result) {
        return HI_ERR_CRC_INVALID_PARAMETER;
    }
    *crc_result =  hi_crc32(crc_start, buf, len);
    return HI_ERR_SUCCESS;
}

hi_u32 nv_read_flash(hi_u32 addr, hi_u32 size, hi_u8* data)
{
    hi_u32 ret;

    for (hi_u32 i = 0; i < HNV_FAULT_TOLERANT_TIMES; i++) {
        ret = hi_flash_read(addr, size, data);
        if (ret == HI_ERR_SUCCESS) {
            return HI_ERR_SUCCESS;
        }
    }

    return HI_ERR_NV_FAIL_N_TIMES;
}

hi_u32 nv_write_flash(hi_u32 addr, hi_u32 size, const hi_u8* data)
{
    hi_u32 ret;

    for (hi_u32 i = 0; i < HNV_FAULT_TOLERANT_TIMES; i++) {
        ret = hi_flash_write(addr, size, data, HI_TRUE);
        if (ret == HI_ERR_SUCCESS) {
            return HI_ERR_SUCCESS;
        }
    }

    return HI_ERR_NV_FAIL_N_TIMES;
}

/* Check the validity of the NV file. */
hi_u32 nv_check_file(hi_u8* pdata, hi_u32 len, hi_nv_type nv_type)
{
    hi_nv_manage* nv_head;
    hi_u32 magic = HNV_FILE_SIGNATURE;
    hi_u32 crc_val = 0;

    nv_head = (hi_nv_manage*)pdata;
    if (nv_type == HI_TYPE_FACTORY_NV) {
        magic = FNV_FILE_SIGNATURE;
    }
    if (magic != nv_head->magic) {
        return HI_ERR_NV_INVALID_TYPE;
    }
    if (nv_head->total_num >= NV_TOTAL_MAX_NUM) {
        return HI_ERR_NV_FULL;
    }
    hi_crc32_nv(0, pdata + HNV_NCRC_SIZE, len - HNV_NCRC_SIZE, &crc_val);

    if (nv_head->crc != crc_val) {
        return HI_ERR_NV_BAD_DATA;
    }
    return HI_ERR_SUCCESS;
}

/* Returns the corresponding NV index. */
hi_nv_item_index* nv_find_item(hi_u8* data, hi_u8 id, hi_nv_type nv_type)
{
    hi_nv_item_index* index = HI_NULL;
    hi_u16 total_num;

    if (data == HI_NULL) {
        total_num = g_s_nv_ctrl[nv_type].total_num;
        index = g_s_nv_ctrl[nv_type].index;
    } else {
        hi_nv_manage* nv_head = (hi_nv_manage*)data;
        total_num = nv_head->total_num;
        index = (hi_nv_item_index*)&nv_head->nv_item_data[0];
    }

    for (hi_u32 i = 0; i < total_num; i++) {
        if (id == index[i].nv_id) {
            return &index[i];
        }
    }
    return (hi_nv_item_index*)HI_NULL;
}

hi_u32 nv_init_start(hi_u32 block_size, hi_u8** data, hi_u8** back, hi_nv_ctrl** nv_ctrl, hi_nv_type nv_type)
{
    if (nv_type >= HI_TYPE_NV_MAX) {
        return HI_ERR_NV_INVALID_PARAMETER;
    }
    *nv_ctrl = &g_s_nv_ctrl[nv_type];
    *data = (hi_u8 *)rom_boot_malloc(block_size);
    if (*data == HI_NULL) {
        return HI_ERR_MALLOC_FAILUE;
    }
    *back = (hi_u8 *)rom_boot_malloc(block_size);
    if (*back == HI_NULL) {
        rom_boot_free(*data);
        return HI_ERR_MALLOC_FAILUE;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 nv_init_index(hi_nv_ctrl* nv_ctrl, const nvm_basic_info* nv_info, hi_u8* p_index, const hi_u8** data,
    const hi_u8** back)
{
    hi_u32 ret, cs;
    hi_u32 index_size = sizeof(hi_nv_item_index) * nv_ctrl->total_num;
    hi_u16 block_count = (hi_u16)nv_info->total_size / (hi_u16)nv_info->block_size;
    nv_ctrl->index = (hi_nv_item_index*)rom_boot_malloc(index_size);
    if (nv_ctrl->index == HI_NULL) {
        ret = HI_ERR_MALLOC_FAILUE;
        rom_boot_free((hi_void *)*back);
        rom_boot_free((hi_void *)*data);
        return ret;
    }
    cs = (uintptr_t)(nv_ctrl->index) ^ index_size ^ (uintptr_t)p_index ^ index_size;
    ret = (hi_u32)memcpy_s(nv_ctrl->index, index_size, p_index, index_size, cs);
    if (ret != HI_ERR_SUCCESS) {
        ret = HI_ERR_NV_FILE_ERR;
        rom_boot_free(p_index);
        rom_boot_free((hi_void *)*back);
        rom_boot_free((hi_void *)*data);
        return ret;
    }
    nv_ctrl->base_addr = nv_info->base_addr;
    nv_ctrl->block_size = nv_info->block_size;
    nv_ctrl->total_block_size = nv_info->block_size * block_count;
    nv_ctrl->init_flag = HI_TRUE;

    rom_boot_free((hi_void *)*back);
    rom_boot_free((hi_void *)*data);
    return HI_ERR_SUCCESS;
}

hi_u32 nv_init_common(hi_u32 base_addr, hi_u32 total_size, hi_u32 block_size, hi_nv_type nv_type)
{
    hi_nv_ctrl* nv_ctrl = HI_NULL;
    nvm_basic_info nv_info;
    hi_u8* data = HI_NULL;
    hi_u8* back = HI_NULL;
    hi_u32 seq_max = 0;
    hi_u8* p_index = HI_NULL;
    if (block_size == (hi_u32)0) {
        return HI_ERR_FAILURE;
    }
    hi_bool flag_read_success = HI_FALSE;

    hi_u32 ret = nv_init_start(block_size, &data, &back, &nv_ctrl, nv_type);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    for (hi_u16 i = 0; i < (hi_u16)total_size / (hi_u16)block_size; i++) {
        hi_u32 flash_addr = base_addr + i * block_size;
        if (nv_read_flash(flash_addr, block_size, data) != HI_ERR_SUCCESS) { /* 读取 hi_nv_manage nv_head */
            /* If the read value is incorrect, continue the processing. */
            continue;
        }
        if (nv_check_file(data, block_size, nv_type) != HI_ERR_SUCCESS) { /* 检查nv文件合法性 */
            continue;
        }
        hi_nv_manage* nv_head = (hi_nv_manage*)data;
        if (nv_head->seq >= seq_max) {
            seq_max = nv_head->seq;
            nv_ctrl->seq = nv_head->seq;
            nv_ctrl->current_addr = flash_addr;
            nv_ctrl->total_num = nv_head->total_num;
            nv_ctrl->ver_magic = nv_head->ver_magic;
            hi_u32 cs = (uintptr_t)back ^ block_size ^ (uintptr_t)data ^ block_size;
            if (memcpy_s(back, block_size, data, block_size, cs) != EOK) {
                continue;
            }
            p_index = &(((hi_nv_manage*)back)->nv_item_data[0]);
            flag_read_success = HI_TRUE;
        }
    }
    if (flag_read_success != HI_TRUE) {
        rom_boot_free(data);
        rom_boot_free(back);
        return HI_ERR_NV_INITILIZATION;
    }
    nv_info.base_addr = base_addr;
    nv_info.block_size = block_size;
    nv_info.total_size = total_size;
    /* Index space application */
    ret = nv_init_index(nv_ctrl, (const nvm_basic_info*)&nv_info, p_index, (const hi_u8**)&data, (const hi_u8**)&back);
    return ret;
}

hi_u8 nv_get_item_len(hi_u32 id, hi_nv_type nv_type)
{
    hi_nv_item_index* nv_index;

    nv_index = nv_find_item(HI_NULL, (hi_u8)id, nv_type);
    if (nv_index == HI_NULL) {
        return 0;
    }
    return nv_index->nv_len;
}

hi_u32 nv_read_common(hi_u8 id, hi_pvoid pdata, hi_u8 len, hi_nv_type nv_type)
{
    hi_u32 ret;
    hi_nv_ctrl* nv_ctrl = HI_NULL;
    hi_nv_item_index* nv_index = HI_NULL;
    hi_u32 crc = 0;
    hi_u32 flash_addr;
    hi_u8 item_len;
    hi_bool to_check_crc;
    hi_u32 crc_val = 0;

    if (nv_type >= HI_TYPE_NV_MAX) {
        return HI_ERR_NV_INVALID_PARAMETER;
    }
    nv_ctrl = &g_s_nv_ctrl[nv_type];
    nv_index = nv_find_item(HI_NULL, id, nv_type);
    if (nv_index == HI_NULL) {
        return HI_ERR_NV_ERROR_READ;
    }
    if (nv_index->nv_len == len) {
        item_len = len;
        to_check_crc = HI_TRUE;
    } else {
        item_len = hi_min(nv_index->nv_len, len);
        to_check_crc = HI_FALSE;
    }

    flash_addr = nv_ctrl->current_addr + nv_index->nv_offset;
    ret = nv_read_flash(flash_addr, item_len, pdata);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    /* CRC is verified only when the lengths are the same. */
    if (to_check_crc == HI_TRUE) {
        ret = nv_read_flash(flash_addr + item_len, sizeof(crc), (hi_u8*)&crc);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        hi_crc32_nv(0, pdata, item_len, &crc_val);
        if (crc != crc_val) {
            return HI_ERR_NV_BAD_DATA;
        }
    } else {
        ret = HI_ERR_NV_LEN_ERR;
    }

    return ret;
}


hi_u32 nv_next_addr(HI_CONST hi_nv_ctrl *nv_ctrl)
{
    hi_u32 new_addr = ((nv_ctrl->current_addr + nv_ctrl->block_size) < (nv_ctrl->base_addr + nv_ctrl->total_block_size))
        ? (nv_ctrl->current_addr + nv_ctrl->block_size) : (nv_ctrl->base_addr);

    return new_addr;
}

hi_u32 nv_block_write(hi_u8* p_nv_file, hi_nv_type nv_type)
{
    hi_u32 ret;
    hi_nv_ctrl* nv_ctrl = &g_s_nv_ctrl[nv_type];
    hi_nv_manage* nv_head = (hi_nv_manage*)p_nv_file;
    hi_u32 flash_addr = nv_next_addr((HI_CONST hi_nv_ctrl *)nv_ctrl);

    nv_head->ver_magic = g_ver_magic;
    nv_head->seq = nv_ctrl->seq + 1;

    hi_crc32_nv(0, p_nv_file + 8, nv_ctrl->block_size - 8, &(nv_head->crc));    // 8
    ret = nv_write_flash(flash_addr, nv_ctrl->block_size, p_nv_file);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    nv_ctrl->seq = nv_head->seq;
    nv_ctrl->current_addr = flash_addr;

    return ret;
}

hi_u32 nv_common_write(hi_u8 id, hi_nv_type nv_type, hi_u8 len, const hi_pvoid data)
{
    hi_u8 backup_num = 1;
    hi_u8 item_len = len;
    hi_u32 ret, crc, cs;
    hi_nv_ctrl* nv_ctrl = &g_s_nv_ctrl[nv_type];

    /* Normal write process */
    hi_nv_item_index* nv_index = nv_find_item(HI_NULL, id, nv_type);
    if (nv_index == HI_NULL) {
        return HI_ERR_NV_ERROR_READ;
    }

    if (nv_index->nv_len != len) {
        item_len = hi_min(nv_index->nv_len, len);
    }

    hi_u8* nv_file = (hi_u8 *)rom_boot_malloc(nv_ctrl->block_size);
    if (nv_file == HI_NULL) {
        return HI_ERR_MALLOC_FAILUE;
    }
    if (nv_type == HI_TYPE_FACTORY_NV) {
        backup_num = 2; /* The operations in the factory area are mutually backed up. 2 copies are written. */
    }
    for (; backup_num > 0; backup_num--) {
        ret = nv_read_flash(nv_ctrl->current_addr, nv_ctrl->block_size, nv_file);
        if (ret != HI_ERR_SUCCESS) {
            continue;
        }

        hi_crc32_nv(0, data, item_len, &crc);
        cs = (uintptr_t)(nv_file + nv_index->nv_offset) ^ item_len ^ (uintptr_t)data ^ item_len;
        if (memcpy_s(nv_file + nv_index->nv_offset, item_len, data, item_len, cs) != EOK) {
            continue;
        }
        cs = (uintptr_t)(nv_file + nv_index->nv_offset + item_len) ^ sizeof(crc) ^ ((uintptr_t)&crc) ^ sizeof(crc);
        if (memcpy_s(nv_file + nv_index->nv_offset + item_len, sizeof(crc), &crc, sizeof(crc), cs) != EOK) {
            continue;
        }
        ret = nv_block_write(nv_file, nv_type);
        if (ret != HI_ERR_SUCCESS) {
            continue;
        }
    }
    rom_boot_free(nv_file);
    return ret;
}

hi_u32 nv_write_common(hi_u8 id, const hi_pvoid data, hi_u8 len, hi_nv_type nv_type)
{
    if (nv_type >= HI_TYPE_NV_MAX) {
        return HI_ERR_NV_INVALID_PARAMETER;
    }
    /* If the readback is equal, no write operation is performed. */
    hi_u8* item_readback = (hi_u8 *)rom_boot_malloc(HNV_ITEM_MAXLEN);
    if (item_readback == HI_NULL) {
        return HI_ERR_MALLOC_FAILUE;
    }

    hi_u32 ret = nv_read_common(id, item_readback, len, nv_type);
    if (ret != HI_ERR_SUCCESS) {
        rom_boot_free(item_readback);
        return ret;
    }
    if (memcmp(data, item_readback, len) == HI_ERR_SUCCESS) {
        rom_boot_free(item_readback);
        return HI_ERR_SUCCESS;
    }
    rom_boot_free(item_readback);

    /* Normal write process */
    ret = nv_common_write(id, nv_type, len, data);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 hi_factory_nv_init(hi_u32 addr, hi_u32 total_size, hi_u32 block_size)
{
    return nv_init_common(addr, total_size, block_size, HI_TYPE_FACTORY_NV);
}

hi_u32 hi_factory_nv_write(hi_u8 id, hi_pvoid pdata, hi_u8 len, hi_u32 flag)
{
    hi_unref_param(flag);
    hi_u32 ret;
    hi_nv_ctrl* nv_ctrl = HI_NULL;

    if (id >= HI_NV_FACTORY_USR_ID_END) {
        return HI_ERR_NV_NOT_SUPPORT;
    }
    if ((pdata == HI_NULL) || (len == 0) || (len > HNV_ITEM_MAXLEN)) {
        return HI_ERR_NV_INVALID_PARAMETER;
    }
    nv_ctrl = &g_s_nv_ctrl[HI_TYPE_FACTORY_NV];
    if (nv_ctrl->init_flag != HI_TRUE) {
        return HI_ERR_NV_INITILIZATION;
    }
    ret = nv_write_common(id, (HI_CONST hi_pvoid)pdata, len, HI_TYPE_FACTORY_NV);

    return ret;
}

hi_u32 hi_factory_nv_read(hi_u8 id, hi_pvoid data, hi_u8 len, hi_u32 flag)
{
    hi_unref_param(flag);
    hi_u32 ret;
    hi_nv_ctrl* nv_ctrl = HI_NULL;

    if (id >= HI_NV_FACTORY_USR_ID_END) {
        return HI_ERR_NV_NOT_SUPPORT;
    }
    if ((data == HI_NULL) || (len == 0) || (len > HNV_ITEM_MAXLEN)) {
        return HI_ERR_NV_INVALID_PARAMETER;
    }
    nv_ctrl = &g_s_nv_ctrl[HI_TYPE_FACTORY_NV];
    if (nv_ctrl->init_flag != HI_TRUE) {
        return HI_ERR_NV_INITILIZATION;
    }
    ret = nv_read_common(id, data, len, HI_TYPE_FACTORY_NV);

    return ret;
}

