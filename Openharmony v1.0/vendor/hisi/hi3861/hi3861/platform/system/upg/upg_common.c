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

#include <upg_common.h>
#include <upg_check_file.h>
#include <upg_check_secure.h>
#include <upg_start_up.h>
#include <upg_check_boot_bin.h>
#include <upg_ver_update.h>
#include <flash_prv.h>

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
#include "kernel_crypto.h"
#endif

upg_ctx g_upg_ctx = { 0 };
volatile hi_u8 g_upg_updating_ver = UPG_UPDATE_VER_NONE; /* 非升级中;升级BOOT；升级kernel */
volatile hi_bool g_upg_update_ver_success = HI_FALSE;
hi_u8 g_upg_efuse_data_boot_ver[BOOT_VER_LEN] = {0};
hi_u8 g_upg_efuse_data_kernel_ver[KERNEL_VER_LEN] = {0};

/************************the following functions are inner functions************************************/
upg_ctx *upg_get_ctx(hi_void)
{
    return &g_upg_ctx;
}

hi_bool upg_is_init(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    return ctx->is_init;
}

hi_bool upg_is_transmit_finish(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    return ctx->transmit_finish_flag;
}

hi_u32 upg_lock(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    return hi_sem_wait(ctx->upg_sem, HI_SYS_WAIT_FOREVER);
}

hi_u32 upg_unlock(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    return hi_sem_signal(ctx->upg_sem);
}

hi_bool upg_is_upg_process(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_bool flag;
    hi_u32 ret = HI_ERR_FAILURE;
    if (upg_is_init()) {
        ret = upg_lock();
    }
    flag = ctx->is_upg_process;
    if (ret == HI_ERR_SUCCESS) {
        upg_unlock();
    }

    return flag;
}

hi_void upg_set_upg_process(hi_bool is_upg_process)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 ret = HI_ERR_FAILURE;
    if (upg_is_init()) {
        ret = upg_lock();
    }
    ctx->is_upg_process = is_upg_process;
    if (ret == HI_ERR_SUCCESS) {
        upg_unlock();
    }
}

hi_void upg_get_boot_key_addr(hi_void)
{
    hi_u32 val;
    hi_u32 rsa_key_addr = { 0 };
    hi_u32 ecc_key_addr = { 0 };
    upg_ctx *ctx = upg_get_ctx();

    hi_reg_read16(DIAG_CTL_GP_REG0_REG, val);
    rsa_key_addr = rsa_key_addr | val;
    hi_reg_read16(DIAG_CTL_GP_REG1_REG, val);
    rsa_key_addr = rsa_key_addr | (val << BIT_U16);
    ctx->rsa_key_addr = rsa_key_addr;

    hi_reg_read16(DIAG_CTL_GP_REG2_REG, val);
    ecc_key_addr = ecc_key_addr | val;
    hi_reg_read16(DIAG_CTL_GP_REG3_REG, val);
    ecc_key_addr = ecc_key_addr | (val << BIT_U16);
    ctx->ecc_key_addr = ecc_key_addr;
}

hi_bool upg_tool_bit_test(const hi_u8 *data, hi_u16 pos, hi_u16 data_len)
{
    hi_u16 base = pos / BIT_U8;
    hi_u16 i = pos % BIT_U8;
    if (pos > (data_len * BIT_U8)) {
        return HI_FALSE;
    }
    return (hi_bool)bit_get(data[base], i);
}

hi_void upg_tool_bit_set(hi_u8 *data, hi_u16 pos, hi_u8 val)
{
    hi_u16 base = pos / BIT_U8;
    hi_u16 i = pos % BIT_U8;
    bit_set(data[base], i, val);
}

hi_void upg_clear_contset(hi_u8 *content, hi_u32 content_len)
{
    if ((content == HI_NULL) || (content_len == 0)) {
        return;
    }

    (hi_void)memset_s(content, content_len, 0x0, content_len);
}

/*
    Decompress NV conditions:
     1. The decompressed NV flag exists;
     2. nv file header error (no NV file backup area for wifi);
     3. Upgrade and non-boot upgrade.
 */
hi_bool upg_is_refresh_nv(const hi_nv_ftm_startup_cfg *cfg)
{
    if (cfg->refresh_nv == ENV_REFRESH_NV) {
        upg_print("[upg refresh nv]flag is true \r\n");
        return HI_TRUE;
    }

    if ((cfg->mode == HI_UPG_MODE_UPGRADE) && (cfg->file_type != HI_UPG_FILE_BOOT)) {
        upg_print("[upg refresh nv]mode-filetype:0x%x-0x%x \r\n", cfg->mode, cfg->file_type);
        return HI_TRUE;
    }
    return HI_FALSE;
}

hi_u32 upg_refresh_nv(hi_void)
{
    hi_nv_ftm_startup_cfg cfg;
    hi_upg_section_head section_head = { 0 };
    hi_u32 ret = upg_get_start_up_nv(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    /* Not need to decompress NV during normal startup, which is a normal branch and returns successfully. */
    if (upg_is_refresh_nv(&cfg) == HI_FALSE) {
        return HI_ERR_SUCCESS;
    }

    /* Replace nv first and then initialize NV. */
    ret = upg_get_section_head_from_flash(cfg.addr_start, &section_head);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_UPG_GET_SECTION_HEAD;
    }

    hi_u32 nv_addr = cfg.addr_start + section_head.section1_offset;
    hi_u32 nv_size = section_head.section1_len;
    if (nv_size != HI_NV_DEFAULT_BLOCK_SIZE) {
        return HI_ERR_UPG_NV_SIZE;
    }
    hi_pvoid buf = hi_malloc(HI_MOD_ID_UPG, section_head.section1_len);
    if (buf == HI_NULL) {
        return HI_ERR_MALLOC_FAILUE;
    }
    ret = hi_flash_read(nv_addr, nv_size, buf);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg refresh nv]flash read fail:nvfrom-nvsize-ret:0x%x-0x%x-0x%x \r\n", nv_addr, nv_size, ret);
        goto fail;
    }
    ret = hi_nv_flush_keep_ids(buf, nv_size);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }
    ret = hi_nv_block_write(buf, nv_size, 0);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    hi_u32 normal_nv_addr = 0;
    hi_u32 normal_nv_size = 0;
    ret = hi_get_normal_nv_partition_table(&normal_nv_addr, &normal_nv_size);
    if (ret == HI_ERR_SUCCESS) {
        ret = hi_nv_init(normal_nv_addr, normal_nv_size, nv_size);
    }

fail:
    hi_free(HI_MOD_ID_UPG, (hi_pvoid)buf);
    upg_print("[upg]refresh nv ret 0x%x \r\n", ret);
    return ret;
}

hi_u32 upg_get_start_up_cfg(hi_nv_ftm_startup_cfg *cfg)
{
    hi_nv_ftm_startup_cfg tmp_data = { 0 };
    hi_u32 ret = upg_get_start_up_nv(&tmp_data);
    if (ret == HI_ERR_SUCCESS) {
        if (memcpy_s(cfg, sizeof(hi_nv_ftm_startup_cfg), &tmp_data, sizeof(hi_nv_ftm_startup_cfg)) != EOK) {
            return HI_ERR_FAILURE;
        }
    }
    return ret;
}

hi_u32 upg_set_start_up_cfg(hi_nv_ftm_startup_cfg *cfg)
{
    hi_nv_ftm_startup_cfg current_data = { 0 };
    hi_u32 ret = upg_get_start_up_nv(&current_data);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    if (memcmp(cfg, &current_data, sizeof(hi_nv_ftm_startup_cfg))) {
        ret = upg_save_start_up_nv(cfg);
        upg_print("[upg set env]ret:0x%x \r\n", ret);
    }
    return ret;
}

hi_u32 upg_get_code_file_ver(hi_u8 *ver)
{
    hi_upg_common_head *head = HI_NULL;
    hi_nv_ftm_startup_cfg cfg;
    hi_u32 ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get file ver]get env ret:0x%x \r\n", ret);
        return ret;
    }

    head = hi_malloc(HI_MOD_ID_UPG, sizeof(hi_upg_common_head));
    if (head == HI_NULL) {
        upg_print("[upg get file ver]malloc fail \r\n");
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    memset_s(head, sizeof(hi_upg_common_head), 0, sizeof(hi_upg_common_head));
    ret = upg_get_common_head_from_flash(cfg.addr_start, head);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get file ver]get head ret:0x%x \r\n", ret);
        hi_free(HI_MOD_ID_UPG, head);
        return ret;
    }
    *ver = head->file_version;
    hi_free(HI_MOD_ID_UPG, head);
    upg_print("[upg get file ver]ver:%d \r\n", *ver);
    return ret;
}

hi_u32 upg_set_efuse_code_ver(hi_void)
{
    hi_u8 pos;
    hi_u32 ret;
    hi_u8 upg_ver;
    hi_u8 current_ver;
    hi_bool flag;

    ret = upg_is_secure_efuse(&flag);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg set kernel ver]get secure efuse,err:0x%x \r\n", ret);
        return ret;
    }

    if (flag == HI_FALSE) {
        upg_print("[upg set kernel ver]not secure boot.\r\n");
        return HI_ERR_SUCCESS;
    }

    ret = upg_get_efuse_code_ver(&current_ver);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg set kernel ver]get ver ret:0x%x\r\n", ret);
        return ret;
    }

    ret = upg_get_code_file_ver(&upg_ver);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg set kernel ver]get head ret:0x%x \r\n", ret);
        return ret;
    }

    if (upg_ver < current_ver) {
        upg_print("[upg set kernel ver]current>file:0%d-%d \r\n", current_ver, upg_ver);
        return HI_ERR_UPG_LOW_KERNEL_VER;
    }

    if ((current_ver == KERELN_VER_MAX) && (upg_ver > KERELN_VER_MAX)) {
        upg_print("[upg set kernel ver]current ver:%d \r\n", upg_ver);
        return HI_ERR_UPG_FULL_KERNEL_VER;
    }

    if (upg_ver == current_ver) {
        upg_print("[upg set kernel ver]same ver:%d \r\n", upg_ver);
        return HI_ERR_SUCCESS;
    }

    (hi_void) memset_s(g_upg_efuse_data_kernel_ver, KERNEL_VER_LEN, 0, KERNEL_VER_LEN);
    for (pos = current_ver; ((pos < upg_ver) && (pos < KERELN_VER_MAX)); pos++) {
        upg_tool_bit_set(g_upg_efuse_data_kernel_ver, pos, SRV_BIT_HIGH);
    }
    ret = upg_start_and_wait_update_ver(UPG_UPDATE_VER_FIRMARE);

    upg_print("[upg set kernel ver]ret:0x%x \r\n", ret);
    return ret;
}

hi_u32 upg_get_kernel_size(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    return ctx->cur_kernel_size;
}

hi_u32 upg_set_kernel_size(hi_u32 addr_start)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 kernel_size = 0;
    hi_u32 ret = hi_flash_read(addr_start + hi_fieldoffset(hi_upg_common_head, file_len), sizeof(hi_u32),
                               (hi_u8 *)(&kernel_size));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg set kernel size]ret:0x%x \r\n", ret);
        return ret;
    }
    ctx->cur_kernel_size = upg_align_next(kernel_size, UPG_FLASH_BLOCK_SIZE);
    return HI_ERR_SUCCESS;
}

hi_u32 upg_mode_init(hi_void)
{
    hi_nv_ftm_startup_cfg cfg = { 0 };
    hi_u32 ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg mode init]get env fail:0x%x \r\n", ret);
        return ret;
    }

    if (cfg.mode != HI_UPG_MODE_UPGRADE) {
        if (cfg.refresh_nv == ENV_REFRESH_NV) {
            cfg.refresh_nv = 0;
            (hi_void) upg_set_start_up_cfg(&cfg);
        }
    }

    if (cfg.reset_cnt > 0) {
        upg_print("[upg mode init]resetcnt:0x%x \r\n", cfg.reset_cnt);
        cfg.reset_cnt = 0;
        cfg.mode = HI_UPG_MODE_NORMAL;
        cfg.refresh_nv = 0;
        ret = upg_set_start_up_cfg(&cfg);
        if (cfg.file_type == HI_UPG_FILE_KERNEL) {
            ret |= upg_set_efuse_code_ver();
            upg_print("[upg mode init]upg set code version ret:0x%x \r\n", ret);
        }
    }
    ret |= upg_set_kernel_size(cfg.addr_start);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg mode init]fail:0x%x \r\n", ret);
    }
    return ret;
}

hi_u32 upg_cache_ctrl(hi_u32 offset, hi_u8 *buf, hi_u32 buf_len, hi_bool is_write)
{
    hi_u32 ret;
    hi_u32 cache_addr;
    upg_ctx *ctx = upg_get_ctx();

    if (buf == HI_NULL) {
        return HI_ERR_UPG_NULL_POINTER;
    }

    if (((offset + buf_len) > (ctx->common_head.file_len)) ||
        ((offset + buf_len) < buf_len)) {
        upg_print("[upg cache ctrl]error param:0x%x-0x%x-0x%x \r\n", offset, buf_len, ctx->common_head.file_len);
        return HI_ERR_UPG_PARAMETER;
    }

    cache_addr = ctx->file_addr;
    if (is_write == HI_FALSE) {
        ret = hi_flash_read(offset + cache_addr, buf_len, (hi_u8 *)buf);
    } else {
        ret = hi_flash_write(offset + cache_addr, buf_len, (hi_u8 *)buf, HI_FALSE);
    }
    return ret;
}

hi_void upg_clear_ctx(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 ret = HI_ERR_FAILURE;
    if (upg_is_init()) {
        ret = upg_lock();
    }
    ctx->is_upg_process = HI_FALSE;
    ctx->check_head_flag = HI_FALSE;
    ctx->transmit_finish_flag = HI_FALSE;
    ctx->cache_size = 0;
    ctx->file_addr = 0;
    memset_s(&ctx->common_head, sizeof(hi_upg_common_head), 0, sizeof(hi_upg_common_head));
    if (ret == HI_ERR_SUCCESS) {
        upg_unlock();
    }
}

hi_u32 upg_clear_wait_mode(hi_nv_ftm_upg_wait_mode *mode)
{
    hi_u32 ret = memset_s(mode, sizeof(hi_nv_ftm_upg_wait_mode), 0, sizeof(hi_nv_ftm_upg_wait_mode));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = upg_save_wait_mode_nv(mode);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_void upg_check_clear_wait_mode(hi_void)
{
    hi_nv_ftm_upg_wait_mode mode_cfg = {0};
    hi_u32 ret = upg_get_wait_mode_nv(&mode_cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[check wait mode]ret=0x%x\r\n", ret);
    }

    if ((mode_cfg.trans_finish_flag == HI_TRUE) || (mode_cfg.is_upg_process == HI_TRUE)) {
        ret = upg_clear_wait_mode(&mode_cfg);
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[clear wait mode]ret=0x%x\r\n", ret);
        }
    }
}

hi_void upg_check_clear_upg_mode(hi_void)
{
    hi_nv_ftm_startup_cfg cfg = { 0 };
    hi_u32 ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[clear upg mode]get env fail,ret:0x%x.\r\n", ret);
    }

    if (cfg.mode == HI_UPG_MODE_UPGRADE_WAIT) {
        cfg.mode = HI_UPG_MODE_NORMAL;
        ret = upg_set_start_up_cfg(&cfg);
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[clear upg mode]set env fail,ret=0x%x\r\n", ret);
        }
    }
}

/*
    1. Modify to the correct boot mode and boot area;
    2. nv file recovery;
    3. Local global variable recovery.

 */
hi_u32 upg_stop(hi_u32 error_no)
{
    hi_nv_ftm_startup_cfg cfg = { 0 };
    hi_u32 ret;

    hi_unref_param(error_no);
    upg_check_clear_wait_mode();
    upg_print("[upg stop]reason:0x%x.\r\n", error_no);
    if (upg_is_upg_process() == HI_FALSE) {
        upg_print("[upg stop]is not upg process.\r\n");
        return HI_ERR_UPG_NOT_START;
    }

    ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg stop]get env fail,ret:0x%x.\r\n", ret);
        return ret;
    }
    if ((cfg.mode == HI_UPG_MODE_UPGRADE) && (cfg.file_type == HI_UPG_FILE_KERNEL)) {
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
        ret = hi_flash_erase(cfg.addr_write, UPG_FLASH_BLOCK_SIZE);
        upg_print("[upg stop]erase ret-addr:0x%x-0x%x.\r\n", ret, cfg.addr_write);
#else
        hi_flash_partition_table *partition = hi_get_partition_table();
        uintptr_t kernel_a_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
        uintptr_t kernel_b_addr = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr;

        ret = hi_flash_erase(cfg.addr_start, UPG_FLASH_BLOCK_SIZE);
        upg_print("[upg stop]dual erase ret-addr:0x%x-0x%x.\r\n", ret, cfg.addr_start);
        if (cfg.addr_start == kernel_a_addr) {
            cfg.addr_start = kernel_b_addr;
        } else {
            cfg.addr_start = kernel_a_addr;
        }
#endif
    }
    if (cfg.file_type == HI_UPG_FILE_KERNEL) {
        cfg.addr_write = 0;
    }

    cfg.mode = HI_UPG_MODE_NORMAL;
    cfg.file_type = 0;
    cfg.refresh_nv = 0;
    ret = upg_set_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    upg_clear_ctx();
    upg_print("[upg stop]ret:0x%x \r\n", ret);
    return ret;
}

hi_u32 upg_check_head(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 addr = ctx->file_addr;
    hi_u32 ret;
    hi_upg_head *upg_head = hi_malloc(HI_MOD_ID_UPG, sizeof(hi_upg_head));
    if (upg_head == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    ret = hi_flash_read(addr, sizeof(hi_upg_head), (hi_u8 *)upg_head);
    if (ret != HI_ERR_SUCCESS) {
        upg_mem_free(upg_head);
        return ret;
    }

    ret = upg_check_upg_file_head(upg_head);
    upg_print("[upg check head]verify head,ret:0x%x. \r\n", ret);
    upg_mem_free(upg_head);
    return ret;
}

hi_u32 upg_get_cache_clear_info(hi_u8 file_type, hi_u32 file_len, hi_u32 *addr, hi_u32 *size)
{
    hi_flash_partition_table *partition = hi_get_partition_table();

    if (file_type == HI_UPG_FILE_BOOT) {
        *addr = partition->table[HI_FLASH_PARTITON_BOOT_BACK].addr;
        *size = partition->table[HI_FLASH_PARTITON_BOOT_BACK].size;
    } else {
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
        hi_u32 erase_start_addr = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr +
                               partition->table[HI_FLASH_PARTITON_KERNEL_B].size - file_len;
        hi_u32 erase_end_addr = erase_start_addr + file_len;
        erase_start_addr = upg_align_pre(erase_start_addr, UPG_FLASH_BLOCK_SIZE);
        erase_end_addr = upg_align_next(erase_end_addr, UPG_FLASH_BLOCK_SIZE);
        *addr = erase_start_addr;
        *size = erase_end_addr - erase_start_addr;
#else
        uintptr_t kernel_a_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
        uintptr_t kernel_b_addr = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr;
        hi_nv_ftm_startup_cfg cfg;
        hi_u32 ret = upg_get_start_up_cfg(&cfg);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        /* Change area, read NV to get the current startup address and change to another area. */
        if (cfg.addr_start == kernel_a_addr) {
            *addr = kernel_b_addr;
            *size = partition->table[HI_FLASH_PARTITON_KERNEL_B].size;
        } else if (cfg.addr_start == kernel_b_addr) {
            *addr = kernel_a_addr;
            *size = partition->table[HI_FLASH_PARTITON_KERNEL_A].size;
        } else {
            return HI_ERR_UPG_START_ADDR;
        }
#endif
    }
    upg_print("[upg clear info]filetype-filelen-addr-size:0x%x-0x%x-0x%x-0x%x\r\n", file_type, file_len, *addr, *size);
    return HI_ERR_SUCCESS;
}

hi_u32 upg_get_backup_write_addr(hi_u8 file_type, hi_u32 file_len, hi_u32 *addr)
{
    hi_flash_partition_table *partition = hi_get_partition_table();

    if (file_type == HI_UPG_FILE_BOOT) {
        uintptr_t boot_bak_addr = partition->table[HI_FLASH_PARTITON_BOOT_BACK].addr +
                                  partition->table[HI_FLASH_PARTITON_BOOT_BACK].size;
        *addr = boot_bak_addr - file_len;
    } else {
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
        hi_u32 erase_st_addr = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr +
                               partition->table[HI_FLASH_PARTITON_KERNEL_B].size - file_len;
        erase_st_addr = upg_align_pre(erase_st_addr, UPG_FLASH_BLOCK_SIZE);
        *addr = erase_st_addr;
#else
        uintptr_t kernel_a_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
        uintptr_t kernel_b_addr = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr;
        hi_nv_ftm_startup_cfg cfg;
        hi_u32 ret = upg_get_start_up_cfg(&cfg);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        /* Change area, read NV to get the current startup address and change to another area. */
        if (cfg.addr_start == kernel_a_addr) {
            *addr = kernel_b_addr;
        } else if (cfg.addr_start == kernel_b_addr) {
            *addr = kernel_a_addr;
        } else {
            return HI_ERR_UPG_START_ADDR;
        }
#endif
    }
    return HI_ERR_SUCCESS;
}

hi_u32 upg_get_max_file_len(hi_u8 file_type, hi_u32 *file_len)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_flash_partition_table *partition = hi_get_partition_table();
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
    if (file_type == HI_UPG_FILE_BOOT) {
        *file_len = partition->table[HI_FLASH_PARTITON_BOOT_BACK].size;
    } else {
        hi_u32 end_addr = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr +
                          partition->table[HI_FLASH_PARTITON_KERNEL_B].size;
        hi_u32 start_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
        hi_u32 current_kernel_size = upg_get_kernel_size();
        if (current_kernel_size == 0) {
            ret = HI_ERR_UPG_KERNEL_LEN;
        } else {
            *file_len = end_addr - start_addr - current_kernel_size;
        }
    }
#else
    hi_nv_ftm_startup_cfg cfg = { 0 };
    ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get max len]error:0x%x \r\n", ret);
        return ret;
    }
    if (file_type == HI_UPG_FILE_BOOT) {
        *file_len = partition->table[HI_FLASH_PARTITON_BOOT_BACK].size;
    } else if (cfg.addr_start == partition->table[HI_FLASH_PARTITON_KERNEL_A].addr) {
        *file_len = partition->table[HI_FLASH_PARTITON_KERNEL_B].size;
    } else if (cfg.addr_start == partition->table[HI_FLASH_PARTITON_KERNEL_B].addr) {
        *file_len = partition->table[HI_FLASH_PARTITON_KERNEL_A].size;
    } else {
        ret = HI_ERR_UPG_PARAMETER;
    }
#endif
    return ret;
}

hi_u32 upg_cache_clear(hi_u8 file_type, hi_u32 file_len)
{
    hi_u32 backup_addr = 0;
    hi_u8 i;
    hi_u32 backup_size = 0;
    hi_u32 ret = upg_get_cache_clear_info(file_type, file_len, &backup_addr, &backup_size);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg clear]get info:0x%x\r\n", ret);
        return ret;
    }
    upg_print("[upg clear]start :%d \r\n", hi_get_milli_seconds());

    for (i = 0; i < UPG_FLASH_RETRY_TIMES; i++) {
        ret = hi_flash_erase(backup_addr, backup_size);
        if (ret == HI_ERR_SUCCESS) {
            break;
        }
    }
    upg_print("[upg clear]end :%d \r\n", hi_get_milli_seconds());
    return ret;
}

hi_u32 upg_set_flash_write_addr(hi_void)
{
    hi_u32 write_addr;
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 ret = upg_get_backup_write_addr(ctx->common_head.file_type, ctx->common_head.file_len, &write_addr);
    if (ret == HI_ERR_SUCCESS) {
        ctx->file_addr = write_addr;
    }
    upg_print("[upg write addr]ret-addr-size:0x%x-0x%x-0x%x\r\n", ret, ctx->file_addr, ctx->common_head.file_len);
    return ret;
}

hi_u32 upg_start(hi_u8 *buf, hi_u32 buf_len)
{
    hi_nv_ftm_startup_cfg cfg = { 0 };
    hi_upg_common_head *head = HI_NULL;
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 ret;

    if (buf == HI_NULL) {
        return HI_ERR_UPG_PARAMETER;
    }

    /* The first packet cannot be less than 96 bytes. */
    if (buf_len < sizeof(hi_upg_common_head)) {
        return HI_ERR_UPG_BUF_LEN;
    }
    head = (hi_upg_common_head *)buf;
    ret = upg_check_common_head(head, sizeof(hi_upg_common_head));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    cfg.file_type = 0;
    cfg.reset_cnt = 0;

    /* Record file header information. */
    if (memcpy_s(&(ctx->common_head), sizeof(hi_upg_common_head), head, sizeof(hi_upg_common_head)) != EOK) {
        return HI_ERR_FAILURE;
    }
    ctx->cache_size = 0;

    /* Erase FLASH. */
    ret = upg_cache_clear(head->file_type, head->file_len);
    if (ret == HI_ERR_SUCCESS) {
        ret = upg_set_flash_write_addr();
        ctx->transmit_finish_flag = HI_FALSE;
        upg_set_upg_process(HI_TRUE);
    }

    if (head->file_type == HI_UPG_FILE_KERNEL) {
        cfg.addr_write = ctx->file_addr;
    }

    if (ret == HI_ERR_SUCCESS) {
        ret = upg_set_start_up_cfg(&cfg);
    }
    return ret;
}

hi_u32 upg_cache_write(hi_u32 offset, hi_u8 *buf, hi_u32 buf_len)
{
    return upg_cache_ctrl(offset, buf, buf_len, HI_TRUE);
}

hi_u32 upg_start_and_wait_update_ver(hi_u8 update_ver_type)
{
    if (update_ver_type != UPG_UPDATE_VER_FIRMARE
        && update_ver_type != UPG_UPDATE_VER_BOOT) {
        return HI_ERR_UPG_UPDATE_VER_INVALID_PARAM;
    }

    /* init upg flag */
    g_upg_updating_ver = update_ver_type;
    g_upg_update_ver_success = HI_FALSE;

    /* trigger upg nmi */
    hi_reg_setbit(UPG_NMI_BASE_ADDRESS + UPG_NMI_CTRL, UPG_NMI_INT_MOD_DONE_EN_POS);

    /* wait nmi handle finish */
    hi_u32 wait_cnt = 1000; /* wait 10s */
    hi_u32 try_cnt = 0;
    /* 小型化和场景考虑，此处实现不采用事件通知 */
    for (try_cnt = 0; try_cnt < wait_cnt; try_cnt++) {
        if (g_upg_updating_ver == UPG_UPDATE_VER_NONE) {
            break;
        }
        hi_sleep(10);   /* sleep 10ms */
    }

    if (g_upg_update_ver_success == HI_TRUE) {
        return HI_ERR_SUCCESS;
    } else if (try_cnt == wait_cnt) {
        return HI_ERR_UPG_UPDATE_VER_TIMEOUT;
    } else {
        return HI_ERR_UPG_UPDATE_VER_FAIL;
    }
}

hi_u32 upg_get_efuse_code_ver(hi_u8 *ver)
{
    hi_u8 pos;
    hi_u8 efuse_data[KERNEL_VER_LEN];
    hi_u32 ret;

    (hi_void) memset_s(efuse_data, KERNEL_VER_LEN, 0, KERNEL_VER_LEN);
    ret = hi_efuse_read(HI_EFUSE_TEE_KERNEL_VER_RW_ID, efuse_data, sizeof(efuse_data));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    for (pos = 0; pos < KERELN_VER_MAX; pos++) {
        if (upg_tool_bit_test(efuse_data, pos, KERNEL_VER_LEN) == HI_FALSE) {
            break;
        }
    }
    if (pos >= KERELN_VER_MAX) {
        *ver = KERELN_VER_MAX;
    } else {
        *ver = pos;
    }
    return ret;
}

hi_u32 upg_get_efuse_boot_ver(hi_u8 *ver)
{
    hi_u8 pos;
    hi_u8 efuse_data[BOOT_VER_LEN] = { 0 };
    hi_u32 ret = hi_efuse_read(HI_EFUSE_TEE_BOOT_VER_RW_ID, efuse_data, sizeof(efuse_data));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    for (pos = 0; pos < BOOT_VER_MAX; pos++) {
        if (upg_tool_bit_test(efuse_data, pos, BOOT_VER_LEN) == HI_FALSE) {
            break;
        }
    }
    if (pos >= BOOT_VER_MAX) {
        *ver = BOOT_VER_MAX;
    } else {
        *ver = pos;
    }
    return ret;
}

hi_void upg_get_boot_file_ver(hi_u8 *ver)
{
    upg_ctx *ctx = upg_get_ctx();
    *ver = ctx->common_head.file_version;
}

hi_u32 upg_set_efuse_boot_ver(hi_void)
{
    hi_u8 pos;
    hi_u32 ret;
    hi_u8 upg_ver;
    hi_u8 current_ver;
    hi_bool flag;

    ret = upg_is_secure_efuse(&flag);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg set boot ver]get secure efuse,err:0x%x \r\n", ret);
        return ret;
    }

    if (flag == HI_FALSE) {
        upg_print("[upg set boot ver]not secure boot.\r\n");
        return HI_ERR_SUCCESS;
    }

    ret = upg_get_efuse_boot_ver(&current_ver);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg set boot ver]get ver ret:0x%x \r\n", ret);
        return ret;
    }
    upg_get_boot_file_ver(&upg_ver);

    if (upg_ver < current_ver) {
        upg_print("[upg set boot ver]current>file:%d-%d \r\n", current_ver, upg_ver);
        return HI_ERR_UPG_LOW_BOOT_VER;
    }

    if ((current_ver == BOOT_VER_MAX) && (upg_ver > BOOT_VER_MAX)) {
        upg_print("[upg set boot ver]current ver:%d \r\n", upg_ver);
        return HI_ERR_UPG_FULL_BOOT_VER;
    }

    if (upg_ver == current_ver) {
        upg_print("[upg set boot ver]same ver:%d \r\n", upg_ver);
        return HI_ERR_SUCCESS;
    }
    (hi_void) memset_s(g_upg_efuse_data_boot_ver, BOOT_VER_LEN, 0, BOOT_VER_LEN);
    for (pos = current_ver; ((pos < upg_ver) && (pos < BOOT_VER_MAX)); pos++) {
        upg_tool_bit_set(g_upg_efuse_data_boot_ver, pos, SRV_BIT_HIGH);
    }
    ret = upg_start_and_wait_update_ver(UPG_UPDATE_VER_BOOT);
    upg_print("[upg set boot ver]ret:0x%x \r\n", ret);
    return ret;
}

hi_u32 upg_refresh_boot(hi_u32 addr)
{
    hi_u32 offset;
    hi_u32 total_size;
    hi_u32 this_size;
    hi_upg_section_head section_head = { 0 };

    hi_flash_partition_table *partiton = hi_get_partition_table();
    hi_u32 boot_addr = partiton->table[HI_FLASH_PARTITON_BOOT].addr;
    hi_u32 boot_size = partiton->table[HI_FLASH_PARTITON_BOOT].size;
    hi_u32 ret = upg_get_section_head_from_flash(addr, &section_head);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg refresh boot]get section head ret:0x%x \r\n", ret);
        return ret;
    }
    total_size = section_head.section0_len;
    if ((total_size == 0) || (total_size > boot_size)) {
        upg_print("[upg refresh boot]total size:0x%x \r\n", total_size);
        return HI_ERR_UPG_FILE_LEN;
    }

    hi_u8 *buf = hi_malloc(HI_MOD_ID_UPG, UPG_FLASH_BLOCK_SIZE);
    if (buf == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    upg_print("[upg eraseboot]starttime:%d \r\n", hi_get_milli_seconds());
    ret = hi_flash_erase(boot_addr, boot_size);
    upg_print("[upg erase]ret-addr-size-end:0x%x-0x%x-0x%x-%d\r\n", ret, boot_addr, boot_size, hi_get_milli_seconds());
    if (ret != HI_ERR_SUCCESS) {
        hi_free(HI_MOD_ID_UPG, buf);
        return ret;
    }

    for (offset = 0; offset < total_size;) {
        this_size = (total_size - offset > UPG_FLASH_BLOCK_SIZE) ? UPG_FLASH_BLOCK_SIZE : (total_size - offset);
        ret = hi_flash_read(addr + section_head.section0_offset + offset, this_size, buf);
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[upg refresh boot]flash read ret:0x%x \r\n", ret);
            break;
        }
        ret = hi_flash_write(boot_addr + offset, this_size, buf, HI_FALSE);
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[upg refresh boot]flash write ret:0x%x \r\n", ret);
            break;
        }
        offset += this_size;
    }
    hi_free(HI_MOD_ID_UPG, buf);
    return ret;
}

hi_u32 upg_get_boot_encrypt_flag(HI_CONST boot_header *head, hi_u8 *flag)
{
    hi_flash_partition_table *partiton = hi_get_partition_table();
    hi_u32 boot_addr = partiton->table[HI_FLASH_PARTITON_BOOT].addr;
    sub_key_common *comk = HI_NULL;
    hi_u32 ret = HI_ERR_SUCCESS;

    if ((head == HI_NULL) || (flag == HI_NULL)) {
        return HI_ERR_UPG_NULL_POINTER;
    }

    comk = hi_malloc(HI_MOD_ID_UPG, sizeof(sub_key_common));
    if (comk == HI_NULL) {
        ret = HI_ERR_UPG_MALLOC_FAIL;
        goto end;
    }

    ret = hi_flash_read((boot_addr + head->sub_key_offset), sizeof(sub_key_common), (hi_u8 *)comk);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    *flag = comk->encrypt_flag;
end:
    upg_clear_contset((hi_u8 *)comk, sizeof(sub_key_common));
    upg_mem_free(comk);
    return ret;
}

hi_u32 upg_get_aes_info(HI_CONST boot_header *head, hi_u8 *key, hi_u32 key_len, hi_u8 *iv, hi_u32 iv_len)
{
    hi_flash_partition_table *partiton = hi_get_partition_table();
    hi_u32 boot_addr = partiton->table[HI_FLASH_PARTITON_BOOT].addr;
    sub_key_common *comk = HI_NULL;
    hi_u32 ret = HI_ERR_SUCCESS;

    if ((head == HI_NULL) || (key_len != IV_BYTE_LEN) || (iv_len != IV_BYTE_LEN)) {
        return HI_ERR_UPG_PARAMETER;
    }

    comk = hi_malloc(HI_MOD_ID_UPG, sizeof(sub_key_common));
    if (comk == HI_NULL) {
        ret = HI_ERR_UPG_MALLOC_FAIL;
        goto end;
    }
    ret = hi_flash_read((boot_addr + head->sub_key_offset), sizeof(sub_key_common), (hi_u8 *)comk);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    if ((memcpy_s(key, key_len, comk->boot_key, key_len) != EOK) ||
        (memcpy_s(iv, iv_len, comk->aes_iv, iv_len) != EOK)) {
        ret = HI_ERR_FAILURE;
        goto end;
    }
end:
    upg_clear_contset((hi_u8 *)comk, sizeof(sub_key_common));
    upg_mem_free(comk);
    return ret;
}

hi_u32 upg_set_kdf_key(const hi_u8 *boo_key, hi_u32 key_len)
{
    hi_cipher_kdf_ctrl *ctrl = HI_NULL;
    hi_u8 rootkey_iv[ROOTKEY_IV_BYTE_LENGTH] = { 0 };
    hi_u32 ret;

    if (key_len != IV_BYTE_LEN) {
        return HI_ERR_UPG_PARAMETER;
    }
    ctrl = hi_malloc(HI_MOD_ID_UPG, sizeof(hi_cipher_kdf_ctrl));
    if (ctrl == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }

    if ((memcpy_s(rootkey_iv, IV_BYTE_LEN, boo_key, IV_BYTE_LEN) != EOK) ||
        (memcpy_s((rootkey_iv + IV_BYTE_LEN), sizeof(rootkey_iv) - IV_BYTE_LEN, g_magic, IV_BYTE_LEN) != EOK)) {
        hi_free(HI_MOD_ID_UPG, ctrl);
        return HI_ERR_FAILURE;
    }

    ctrl->salt = rootkey_iv;
    ctrl->salt_len = ROOTKEY_IV_BYTE_LENGTH;
    ctrl->kdf_cnt = KDF_ITERATION_CNT;
    ctrl->kdf_mode = HI_CIPHER_SSS_KDF_KEY_STORAGE;

    ret = hi_cipher_kdf_key_derive(ctrl);
    hi_free(HI_MOD_ID_UPG, ctrl);
    return ret;
}

hi_u32 upg_boot_key_decrypt(hi_u8 *key, hi_u32 key_len, const hi_u8 *iv, hi_u32 iv_len)
{
    hi_cipher_aes_ctrl *aes_ctrl = HI_NULL;
    hi_u32 ret;

    if (iv_len != IV_BYTE_LEN) {
        return HI_ERR_UPG_PARAMETER;
    }
    aes_ctrl = hi_malloc(HI_MOD_ID_UPG, sizeof(hi_cipher_aes_ctrl));
    if (aes_ctrl == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }

    if (memcpy_s(aes_ctrl->iv, sizeof(aes_ctrl->iv), iv, IV_BYTE_LEN) != EOK) {
        hi_free(HI_MOD_ID_UPG, aes_ctrl);
        return HI_ERR_FAILURE;
    }
    aes_ctrl->random_en = HI_TRUE;
    aes_ctrl->key_from = HI_CIPHER_AES_KEY_FROM_KDF;
    aes_ctrl->work_mode = HI_CIPHER_AES_WORK_MODE_CBC;
    aes_ctrl->key_len = HI_CIPHER_AES_KEY_LENGTH_256BIT;
    ret = hi_cipher_aes_config(aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        hi_free(HI_MOD_ID_UPG, aes_ctrl);
        return ret;
    }
    ret = hi_cipher_aes_crypto((uintptr_t)key, (uintptr_t)key, key_len, HI_FALSE);
    hi_cipher_aes_destroy_config();
    hi_free(HI_MOD_ID_UPG, aes_ctrl);
    return ret;
}

/* key_n:from flash; key_e: use default value 0x10001. */
hi_u32 upg_get_unencrpt_rsa_key(hi_u8 *key, hi_u32 key_len)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 ret;

    if (ctx->rsa_key_addr == 0) {
        return HI_ERR_UPG_RSA_KEY_ADDR;
    }

    ret = hi_flash_read(ctx->rsa_key_addr, RSA_2048_LEN, key);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get unencrpt rsa key]flash read fail:0x%x. \r\n", ret);
        return ret;
    }
    key[key_len - 1] = 0x01; /* 1: first byte. 0x01: part of key_e 0x10001 */
    key[key_len - 3] = 0x01; /* 3: last byte.  0x01: part of key_e 0x10001 */
    upg_print("[upg get unencrpt rsa key]success. \r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 upg_get_unencrpt_ecc_key(hi_u8 *key, hi_u32 key_len)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 ret;

    if (ctx->ecc_key_addr == 0) {
        return HI_ERR_UPG_ECC_KEY_ADDR;
    }

    ret = hi_flash_read(ctx->ecc_key_addr, key_len, key);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get unencrpt ecc key]flash read fail:0x%x. \r\n", ret);
        return ret;
    }
    upg_print("[upg get unencrpt ecc key]success. \r\n");
    return HI_ERR_SUCCESS;
}

hi_u32 upg_get_decrpt_rsa_key(HI_CONST boot_header *head, hi_u8 *key, hi_u32 key_len)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    upg_ctx *ctx = upg_get_ctx();
    hi_flash_partition_table *partiton = hi_get_partition_table();
    hi_u32 boot_addr = partiton->table[HI_FLASH_PARTITON_BOOT].addr;
    hi_u8 *raw_data = HI_NULL;
    hi_u8 boot_key[IV_BYTE_LEN] = { 0 };
    hi_u8 aes_iv[IV_BYTE_LEN] = { 0 };

    ret = upg_get_aes_info(head, boot_key, IV_BYTE_LEN, aes_iv, IV_BYTE_LEN);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if ((ctx->rsa_key_addr == 0) || (ctx->rsa_key_addr < head->code_section_offset)) {
        return HI_ERR_UPG_RSA_KEY_ADDR;
    }
    hi_u32 data_len = upg_align_128bit(ctx->rsa_key_addr - head->code_section_offset + RSA_2048_LEN);
    upg_print("[upg get decrpt rsa key]offset-addr-len:0x%x-0x%x-0x%x \r\n", head->code_section_offset,
              ctx->rsa_key_addr, data_len);
    raw_data = hi_malloc(HI_MOD_ID_UPG, data_len);
    if (raw_data == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    ret = hi_flash_read(boot_addr + head->code_section_offset, data_len, raw_data);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    ret = upg_set_kdf_key(boot_key, IV_BYTE_LEN);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get decrpt rsa key]kdf ret:0x%x \r\n", ret);
        goto end;
    }

    ret = upg_boot_key_decrypt(raw_data, data_len, aes_iv, IV_BYTE_LEN);
    if (memcpy_s(key, RSA_2048_LEN, raw_data + (ctx->rsa_key_addr - head->code_section_offset), RSA_2048_LEN) != EOK) {
        ret = HI_ERR_FAILURE;
        goto end;
    }
    key[key_len - 1] = 0x01; /* 1: first byte. 0x01: part of key_e 0x10001 */
    key[key_len - 3] = 0x01; /* 3: last byte.  0x01: part of key_e 0x10001 */
end:
    upg_clear_contset(raw_data, data_len);
    upg_mem_free(raw_data);
    return ret;
}

/* px+py:from flash. */
hi_u32 upg_get_decrpt_ecc_key(HI_CONST boot_header *head, hi_u8 *key, hi_u32 key_len)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    upg_ctx *ctx = upg_get_ctx();
    hi_flash_partition_table *partiton = hi_get_partition_table();
    hi_u32 boot_addr = partiton->table[HI_FLASH_PARTITON_BOOT].addr;
    hi_u8 *raw_data = HI_NULL;
    hi_u8 boot_key[IV_BYTE_LEN] = { 0 };
    hi_u8 aes_iv[IV_BYTE_LEN] = { 0 };

    ret = upg_get_aes_info(head, boot_key, IV_BYTE_LEN, aes_iv, IV_BYTE_LEN);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if ((ctx->ecc_key_addr == 0) || (ctx->ecc_key_addr < head->code_section_offset)) {
        return HI_ERR_UPG_ECC_KEY_ADDR;
    }
    hi_u32 data_len = upg_align_128bit(ctx->ecc_key_addr - head->code_section_offset + key_len);
    upg_print("[upg get decrpt ecc key]offset-addr-len:0x%x-0x%x-0x%x \r\n", head->code_section_offset,
              ctx->ecc_key_addr, data_len);
    raw_data = hi_malloc(HI_MOD_ID_UPG, data_len);
    if (raw_data == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    ret = hi_flash_read(boot_addr + head->code_section_offset, data_len, raw_data);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    ret = upg_set_kdf_key(boot_key, IV_BYTE_LEN);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get decrpt ecc key]set kdf ret:0x%x \r\n", ret);
        goto end;
    }

    ret = upg_boot_key_decrypt(raw_data, data_len, aes_iv, IV_BYTE_LEN);
    if (memcpy_s(key, key_len, raw_data + (ctx->ecc_key_addr - head->code_section_offset), key_len) != EOK) {
        ret = HI_ERR_FAILURE;
    }
end:
    upg_clear_contset(raw_data, data_len);
    upg_mem_free(raw_data);
    return ret;
}

/* key_n:from flash; key_e: use default value 0x10001. */
hi_u32 upg_get_rsa_key_from_boot(hi_u8 *key, hi_u32 key_len)
{
    hi_u32 ret;
    hi_u8 flag;
    hi_u8 efuse_flag = 0xFF;
    boot_header *head = HI_NULL;
    hi_flash_partition_table *partiton = hi_get_partition_table();
    hi_u32 boot_addr = partiton->table[HI_FLASH_PARTITON_BOOT].addr;

    if ((key == HI_NULL) || (key_len != RSA_KEY_LEN)) {
        upg_print("[upg get rsa key]param err:len:0x%x \r\n", key_len);
        return HI_ERR_UPG_PARAMETER;
    }
    head = hi_malloc(HI_MOD_ID_UPG, sizeof(boot_header));
    if (head == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    ret = hi_flash_read(boot_addr, sizeof(boot_header), (hi_u8 *)head);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    ret = upg_get_boot_encrypt_flag(head, &flag);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get rsa key]get encrypt flag fail:0x%x \r\n", ret);
        goto end;
    }

    ret = hi_efuse_read(HI_EFUSE_ENCRYPT_FLAG_RW_ID, (hi_u8 *)(&efuse_flag), sizeof(hi_u8));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get rsa key]efuse read err:0x%x \r\n", ret);
        goto end;
    }

    if ((efuse_flag == NON_ENCRYPT_FLAG) && (flag == NON_ENCRYPT_FLAG)) {
        ret = upg_get_unencrpt_rsa_key(key, key_len);
    } else {
        ret = upg_get_decrpt_rsa_key(head, key, key_len);
    }

end:
    upg_mem_free(head);
    return ret;
}

/* px+py:from flash. */
hi_u32 upg_get_ecc_key_from_boot(hi_u8 *key, hi_u32 key_len)
{
    hi_u32 ret;
    hi_u8 flag;
    hi_u8 efuse_flag = 0xFF;
    boot_header *head = HI_NULL;
    hi_flash_partition_table *partiton = hi_get_partition_table();
    hi_u32 boot_addr = partiton->table[HI_FLASH_PARTITON_BOOT].addr;

    if ((key == HI_NULL) || (key_len != ECC_KEY_LEN)) {
        upg_print("[upg get ecc key]param err:len:0x%x \r\n", key_len);
        return HI_ERR_UPG_PARAMETER;
    }
    head = hi_malloc(HI_MOD_ID_UPG, sizeof(boot_header));
    if (head == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    ret = hi_flash_read(boot_addr, sizeof(boot_header), (hi_u8 *)head);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }
    ret = upg_get_boot_encrypt_flag(head, &flag);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get ecc key]get encrypt flag fail:0x%x \r\n", ret);
        goto end;
    }

    ret = hi_efuse_read(HI_EFUSE_ENCRYPT_FLAG_RW_ID, (hi_u8 *)(&efuse_flag), sizeof(hi_u8));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get ecc key]efuse read err:0x%x \r\n", ret);
        goto end;
    }

    if ((efuse_flag == NON_ENCRYPT_FLAG) && (flag == NON_ENCRYPT_FLAG)) {
        ret = upg_get_unencrpt_ecc_key(key, key_len);
    } else {
        ret = upg_get_decrpt_ecc_key(head, key, key_len);
    }

end:
    upg_mem_free(head);
    return ret;
}

hi_u32 upg_boot_process(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 ret = hi_flash_protect_enable(HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }
    ret = upg_refresh_boot(ctx->file_addr);
    upg_print("[upg transmit finish]refresh boot:0x%x\r\n", ret);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }
    ret = hi_flash_protect_enable(HI_TRUE);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg transmit finish]refresh boot:0x%x\r\n", ret);
    }
    ret = upg_set_efuse_boot_ver();
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }
    return ret;
}
/************************the following functions are external interface************************************/
hi_u32 hi_upg_init(hi_void)
{
    hi_u32 ret;
    upg_ctx *ctx = upg_get_ctx();

    if (ctx->is_init == HI_TRUE) {
        return HI_ERR_UPG_INITILIZATION_ALREADY;
    }

    ret = hi_sem_bcreate(&ctx->upg_sem, HI_SEM_ONE);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg init]sem create fail: 0x%x\r\n", ret);
        return ret;
    }
    ctx->is_init = HI_TRUE;
    upg_get_boot_key_addr();
    ret = upg_refresh_nv();
    ret |= upg_mode_init();
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg init]fail:0x%x \r\n", ret);
    }
    return ret;
}

hi_u32 hi_upg_get_max_file_len(hi_u8 file_type, hi_u32 *file_len)
{
    if (file_len == HI_NULL) {
        return HI_ERR_UPG_NULL_POINTER;
    }
    return upg_get_max_file_len(file_type, file_len);
}

hi_u32 hi_upg_get_content(hi_u32 offset, hi_u8 *buf, hi_u32 buf_len)
{
    hi_nv_ftm_startup_cfg cfg;
    hi_nv_ftm_upg_wait_mode mode;
    hi_u32 ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (cfg.mode != HI_UPG_MODE_UPGRADE_WAIT) {
        if (upg_is_upg_process() == HI_FALSE) {
            return HI_ERR_UPG_NOT_START;
        }

        if (upg_is_transmit_finish() == HI_TRUE) {
            return HI_ERR_UPG_ALREADY_FINISH;
        }
    } else {
        ret = upg_get_wait_mode_nv(&mode);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        if (mode.is_upg_process == HI_FALSE) {
            return HI_ERR_UPG_NOT_START;
        }

        upg_ctx *ctx = upg_get_ctx();
        ctx->file_addr = mode.file_addr;
        hi_upg_common_head head = {0};
        ret = hi_flash_read(ctx->file_addr, sizeof(hi_upg_common_head), (hi_u8 *)(&head));
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[upg get content]Failed to read flash,ret=%X\r\n", ret);
            return ret;
        }
        ctx->common_head.file_len = head.file_len;
    }

    return upg_cache_ctrl(offset, buf, buf_len, HI_FALSE);
}

hi_u32 hi_upg_transmit(hi_u32 offset, hi_u8 *buf, hi_u32 buf_len)
{
    hi_u32 ret;
    upg_ctx *ctx = upg_get_ctx();

    if (buf == HI_NULL) {
        return HI_ERR_UPG_NULL_POINTER;
    }
    upg_check_clear_wait_mode();
    upg_check_clear_upg_mode();
    upg_print("[upg transmit]offset-buflen-cachesize:0x%x-0x%x-0x%x\r\n", offset, buf_len, ctx->cache_size);

    if (offset != ctx->cache_size) {
        upg_print("[upg transmit]offset-cachesize:0x%x-0x%x\r\n", offset, ctx->cache_size);
        upg_stop(HI_ERR_UPG_PARAMETER);
    }

    /* The first packet. */
    if (upg_is_upg_process() == HI_FALSE) {
        if (offset != 0) {
            return HI_ERR_UPG_FIRST_PACKET_OFFSET;
        }
        ret = upg_start(buf, buf_len);
        upg_print("[upg transmit]upg start ret:0x%x\r\n", ret);
        if (ret != HI_ERR_SUCCESS) {
            upg_stop(ret);
            return ret;
        }
    }

    ret = upg_cache_write(offset, buf, buf_len);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg transmit]cache write err: 0x%x\r\n", ret);
        upg_stop(ret);
        return ret;
    }
    ctx->cache_size += buf_len;
    if ((ctx->check_head_flag == HI_FALSE) && (ctx->cache_size >= sizeof(hi_upg_head))) {
        ret = upg_check_head();
        ctx->check_head_flag = HI_TRUE;
    }

    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg transmit]check head fail:0x%x\r\n", ret);
        upg_stop(ret);
    }
    return ret;
}

hi_u32 upg_file_decrypt(upg_ctx *ctx)
{
    hi_u32 ret = HI_ERR_SUCCESS;
#if (defined(CONFIG_FLASH_ENCRYPT_SUPPORT)) && (!defined(CONFIG_COMPRESSION_OTA_SUPPORT))
    if (ctx->common_head.file_type == HI_UPG_FILE_KERNEL) {
        ret = crypto_encrypt_data_to_flash(ctx->file_addr);
        if (ret != HI_ERR_SUCCESS) {
            upg_stop(ret);
            return ret;
        }
    }
#else
    hi_unref_param(ctx);
#endif

    return ret;
}

hi_u32 hi_upg_transmit_finish(hi_void)
{
    hi_nv_ftm_startup_cfg cfg;
    upg_ctx *ctx = upg_get_ctx();
    if (ctx->transmit_finish_flag == HI_TRUE) {
        return HI_ERR_UPG_ALREADY_FINISH;
    }

    if (upg_is_upg_process() == HI_FALSE) {
        return HI_ERR_UPG_NOT_START;
    }
    hi_u32 ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    if (upg_file_decrypt(ctx) != HI_ERR_SUCCESS) {
        return HI_ERR_UPG_FILE_DECRYPT_ERR;
    }

    ret = upg_verify_file(ctx->file_addr);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    if (ctx->common_head.file_type == HI_UPG_FILE_BOOT) {
        ret = upg_boot_process();
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    } else {
        /* Change kernel start address. */
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
        cfg.addr_write = ctx->file_addr;
#else
        cfg.addr_start = ctx->file_addr;
        cfg.addr_write = ctx->file_addr;
#endif
        cfg.refresh_nv = ENV_REFRESH_NV;
        cfg.reset_cnt = 0;
    }
    cfg.mode = HI_UPG_MODE_UPGRADE;
    cfg.file_type = ctx->common_head.file_type;
    ret = upg_set_start_up_cfg(&cfg);
    if (ret == HI_ERR_SUCCESS) {
        ctx->transmit_finish_flag = HI_TRUE;
    } else {
        upg_stop(ret);
    }
    upg_print("[upg transmit finish]start-type-write-ret:0x%x-0x%x-0x%x-0x%x\r\n",
              cfg.addr_start, cfg.file_type, cfg.addr_write, ret);
    return ret;
}

hi_void hi_upg_finish(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();

    upg_print("[upg finish]finish flag:0x%x \r\n", ctx->transmit_finish_flag);
    if (ctx->transmit_finish_flag == HI_FALSE) {
        hi_soft_reboot(HI_SYS_REBOOT_CAUSE_UPG_B);
    } else {
        hi_soft_reboot(HI_SYS_REBOOT_CAUSE_UPG);
    }
}

hi_u32 upg_check_transmit_finish_flag(hi_void)
{
    hi_u32 ret;
    hi_nv_ftm_upg_wait_mode mode_cfg = {0};

    ret = upg_get_wait_mode_nv(&mode_cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    if (mode_cfg.trans_finish_flag == HI_TRUE) {
        return HI_ERR_UPG_ALREADY_FINISH;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 upg_check_download_finish(hi_void)
{
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 addr = ctx->file_addr;
    hi_u32 ret;
    hi_upg_common_head *comm_head = hi_malloc(HI_MOD_ID_UPG, sizeof(hi_upg_common_head));
    if (comm_head == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    ret = hi_flash_read(addr, sizeof(hi_upg_common_head), (hi_u8 *)comm_head);
    if (ret != HI_ERR_SUCCESS) {
        upg_mem_free(comm_head);
        return ret;
    }

    if (ctx->cache_size < comm_head->file_len) {
        upg_mem_free(comm_head);
        return HI_ERR_UPG_NOT_DOWNLOAD_FINISH;
    }

    upg_mem_free(comm_head);
    return HI_ERR_SUCCESS;
}

hi_u32 hi_upg_transmit_finish_save_cache(hi_void)
{
    hi_nv_ftm_startup_cfg cfg;
    hi_nv_ftm_upg_wait_mode mode_cfg = {0};
    upg_ctx *ctx = upg_get_ctx();
    if (upg_check_transmit_finish_flag() != HI_ERR_SUCCESS) {
        return HI_ERR_UPG_ALREADY_FINISH;
    }

    if (upg_is_upg_process() == HI_FALSE) {
        return HI_ERR_UPG_NOT_START;
    }

    if (upg_check_download_finish() != HI_ERR_SUCCESS) {
        return HI_ERR_UPG_NOT_DOWNLOAD_FINISH;
    }

    hi_u32 ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    if (ctx->common_head.file_type == HI_UPG_FILE_BOOT) {
        ret = upg_verify_file(ctx->file_addr);
        if (ret != HI_ERR_SUCCESS) {
            upg_stop(ret);
            return ret;
        }
        mode_cfg.boot_version = ctx->common_head.file_version;
    } else {
        cfg.refresh_nv = ENV_REFRESH_NV_WAIT;
        cfg.reset_cnt = 0;
    }

    cfg.mode = HI_UPG_MODE_UPGRADE_WAIT;
    cfg.file_type = ctx->common_head.file_type;
    ret = upg_set_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    mode_cfg.file_addr = ctx->file_addr;
    mode_cfg.file_type = ctx->common_head.file_type;
    mode_cfg.is_upg_process = ctx->is_upg_process;
    mode_cfg.trans_finish_flag = HI_TRUE;
    ret = upg_save_wait_mode_nv(&mode_cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    upg_print("[upg transmit finish with cache]start-type-write-ret:0x%x-0x%x-0x%x-0x%x\r\n",
              cfg.addr_start, cfg.file_type, cfg.addr_write, ret);
    return ret;
}

hi_u32 upg_kernel_decrypt_and_verify(upg_ctx *ctx)
{
    hi_u32 ret;
    if (upg_file_decrypt(ctx) != HI_ERR_SUCCESS) {
        upg_stop(HI_ERR_UPG_FILE_DECRYPT_ERR);
        return HI_ERR_UPG_FILE_DECRYPT_ERR;
    }

    ret = upg_verify_file(ctx->file_addr);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 hi_upg_finish_with_cache(hi_void)
{
    hi_nv_ftm_startup_cfg cfg = {0};
    hi_nv_ftm_upg_wait_mode mode_cfg = {0};
    upg_ctx *ctx = upg_get_ctx();
    hi_u32 ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    ret = upg_get_wait_mode_nv(&mode_cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    if ((cfg.mode != HI_UPG_MODE_UPGRADE_WAIT) || (mode_cfg.is_upg_process != HI_TRUE) ||
        (mode_cfg.trans_finish_flag != HI_TRUE)) {
        return HI_ERR_UPG_NOT_WITH_CACHE_MODE_ERR;
    }

    upg_print("[upg finish with cache]file_addr-file_type: 0x%x-0x%x\r\n", mode_cfg.file_addr, mode_cfg.file_type);
    ctx->file_addr = mode_cfg.file_addr;
    ctx->common_head.file_type = mode_cfg.file_type;

    ret = upg_kernel_decrypt_and_verify(ctx);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (ctx->common_head.file_type == HI_UPG_FILE_BOOT) {
        ctx->common_head.file_version = mode_cfg.boot_version;
        ret = upg_boot_process();
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    } else {
        /* Change kernel start address. */
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
        cfg.addr_write = ctx->file_addr;
#else
        cfg.addr_start = ctx->file_addr;
        cfg.addr_write = ctx->file_addr;
#endif
        cfg.refresh_nv = ENV_REFRESH_NV;
    }
    cfg.mode = HI_UPG_MODE_UPGRADE;

    ret = upg_set_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    ret = upg_clear_wait_mode(&mode_cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_stop(ret);
        return ret;
    }

    hi_soft_reboot(HI_SYS_REBOOT_CAUSE_UPG);
    return HI_ERR_SUCCESS;
}

hi_u32 hi_upg_get_file_index(hi_u8 *index)
{
    hi_nv_ftm_startup_cfg cfg = { 0 };
    hi_flash_partition_table *partition = hi_get_partition_table();
    uintptr_t kernel_a_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
    hi_u32 ret = upg_get_start_up_cfg(&cfg);

    if (index == HI_NULL) {
        return HI_ERR_UPG_PARAMETER;
    }

    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    if (cfg.addr_start == kernel_a_addr) {
        *index = HI_UPG_FILE_FOR_AREA_B;
    } else {
        *index = HI_UPG_FILE_FOR_AREA_A;
    }
    upg_print("[upg get file index]index:%d \r\n", *index);
    return ret;
}

hi_u32 hi_upg_stop(hi_void)
{
    return upg_stop(HI_ERR_UPG_STOP);
}

hi_bool upg_update_ver(hi_void)
{
    if (g_upg_updating_ver == UPG_UPDATE_VER_NONE) {
        return HI_FALSE;
    }

    hi_u32 ret = HI_ERR_FAILURE;

    if (g_upg_updating_ver == UPG_UPDATE_VER_FIRMARE) {
        ret = hi_efuse_write(HI_EFUSE_TEE_KERNEL_VER_RW_ID, g_upg_efuse_data_kernel_ver);
    } else if (g_upg_updating_ver == UPG_UPDATE_VER_BOOT) {
        ret = hi_efuse_write(HI_EFUSE_TEE_BOOT_VER_RW_ID, g_upg_efuse_data_boot_ver);
    }

    if (ret == HI_ERR_SUCCESS) {
        g_upg_update_ver_success = HI_TRUE;
    }
    g_upg_updating_ver = UPG_UPDATE_VER_NONE;

    return HI_TRUE;
}
