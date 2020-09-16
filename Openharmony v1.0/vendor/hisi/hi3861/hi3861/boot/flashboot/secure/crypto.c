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

/*
 * CONFIG_FLASH_ENCRYPT_SUPPORT:
 * --Determine that the flash crypto function is supported;
 *   This configuration can be modified in menuconfig.
 */
#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#include <hi_cipher.h>
#include "crypto.h"
#include <boot_upg_check.h>
#include <boot_upg_start_up.h>

boot_crypto_ctx g_boot_crypto_param = {0};
boot_crypto_ctx g_boot_decrypt_param = {0};
boot_crypto_ctx *boot_crypto_get_ctx(hi_void)
{
    return &g_boot_crypto_param;
}

boot_crypto_ctx *boot_decrypt_get_ctx(hi_void)
{
    return &g_boot_decrypt_param;
}

hi_u32 crypto_check_image_id(hi_u32 image_id)
{
    if (image_id != PRODUCT_UPG_FILE_IMAGE_ID) {
        boot_msg1("[crypto check image id]fail, id:", image_id);
        return HI_PRINT_ERRNO_CRYPTO_CHECK_KERNEL_ERR;
    }
    return HI_ERR_SUCCESS;
}

hi_bool crypto_check_kernel_file(hi_u32 addr_start)
{
    hi_u32 ret;
    hi_upg_head upg_head;
    ret = hi_flash_read(addr_start, sizeof(hi_upg_head), (hi_u8 *)&upg_head);
    if (ret != HI_ERR_SUCCESS) {
        return HI_FALSE;
    }
    hi_upg_common_head *common_head = &(upg_head.common);

    ret = crypto_check_image_id(common_head->image_id);
    if (ret != HI_ERR_SUCCESS) {
        return HI_FALSE;
    }

    return HI_TRUE;
}

hi_void change_kernel(hi_void)
{
    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    hi_flash_partition_table *partition = hi_get_partition_table();
    uintptr_t kernel_a_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
    uintptr_t kernel_b_addr = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr;

    if (cfg->addr_start == kernel_a_addr) {
        cfg->addr_start = kernel_b_addr;
    } else {
        cfg->addr_start = kernel_a_addr;
    }
}

hi_u32 boot_get_crypto_kernel_start(hi_u32 *flash_offset)
{
    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    if (!crypto_check_kernel_file(cfg->addr_start)) {
        return HI_PRINT_ERRNO_CRYPTO_CHECK_KERNEL_ERR;
    }

    boot_get_start_addr_offset(cfg->addr_start, flash_offset);

    return HI_ERR_SUCCESS;
}

hi_void crypto_clear_content(hi_u8 *content, hi_u32 content_len)
{
    if ((content == HI_NULL) || (content_len == 0)) {
        return;
    }

    hi_u32 cs = (uintptr_t)content ^ content_len ^ 0x0 ^ content_len;
    (hi_void)memset_s(content, content_len, 0x0, content_len, cs);
}

static hi_u32 crypto_load_salt(crypto_workkey_partition part, hi_flash_crypto_content *key_content)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u8 salt_e[ROOT_SALT_LENGTH] = { 0 };

    hi_u32 cs = (uintptr_t)salt_e ^ (hi_u32)sizeof(salt_e) ^ 0x0 ^ ROOT_SALT_LENGTH;
    (hi_void) memset_s(salt_e, sizeof(salt_e), 0x0, ROOT_SALT_LENGTH, cs);
    if (part == CRYPTO_WORKKEY_KERNEL_A) {
        ret = hi_factory_nv_read(HI_NV_FTM_KERNELA_WORK_ID, key_content, sizeof(hi_flash_crypto_content), 0);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        }
    } else if (part == CRYPTO_WORKKEY_KERNEL_A_BACKUP) {
        ret = hi_factory_nv_read(HI_NV_FTM_BACKUP_KERNELA_WORK_ID, key_content, sizeof(hi_flash_crypto_content), 0);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        }
    }

    if (memcmp(key_content->root_salt, salt_e, ROOT_SALT_LENGTH) == HI_ERR_SUCCESS) {
        ret = HI_PRINT_ERRNO_CRYPTO_SALT_EMPTY_ERR;
        goto fail;
    }
fail:
    return ret;
}

static hi_u32 crypto_get_root_salt(hi_flash_crypto_content *key_content)
{
    hi_u32 ret = crypto_load_salt(CRYPTO_WORKKEY_KERNEL_A, key_content);
    if (ret != HI_ERR_SUCCESS) {
        ret = crypto_load_salt(CRYPTO_WORKKEY_KERNEL_A_BACKUP, key_content);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 crypto_prepare(hi_flash_crypto_content *save_content)
{
    hi_u32 ret;
    hi_u8 rootkey_iv[ROOTKEY_IV_BYTE_LENGTH];
    hi_cipher_kdf_ctrl ctrl;
    hi_u32 cs;

    ret = hi_cipher_init();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = crypto_get_root_salt(save_content);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    cs = (uintptr_t)rootkey_iv ^ sizeof(rootkey_iv) ^ ((uintptr_t)save_content->root_salt) ^ ROOT_SALT_LENGTH;
    ret = memcpy_s(rootkey_iv, sizeof(rootkey_iv), save_content->root_salt, ROOT_SALT_LENGTH, cs);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ctrl.salt = rootkey_iv;
    ctrl.salt_len = sizeof(rootkey_iv);
    ctrl.kdf_cnt = KDF_ITERATION_CNT;
    /* The HUK value is automatically generated. The hardware directly obtains the HUK
       from the eFUSE and generates a fixed root key. */
    /* 自动生成HUK值的方式，硬件直接从EFUSE中获取HUK，生成根密钥固定 */
    ctrl.kdf_mode = HI_CIPHER_SSS_KDF_KEY_STORAGE;
    return hi_cipher_kdf_key_derive(&ctrl);
}

static hi_u32 crypto_destory(hi_void)
{
    return hi_cipher_deinit();
}

hi_bool is_upg_need_crypto(hi_void)
{
    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    if ((cfg->mode == HI_UPG_MODE_UPGRADE) &&
        ((cfg->reset_cnt >= 1) && (cfg->reset_cnt < cfg->cnt_max))) {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static hi_void crpto_set_aes_ctrl_default_value(hi_cipher_aes_ctrl *aes_ctrl)
{
    if (aes_ctrl == HI_NULL) {
        return;
    }
    aes_ctrl->random_en = HI_FALSE;
    aes_ctrl->key_from = HI_CIPHER_AES_KEY_FROM_CPU;
    aes_ctrl->work_mode = HI_CIPHER_AES_WORK_MODE_CBC;
    aes_ctrl->key_len = HI_CIPHER_AES_KEY_LENGTH_256BIT;
}

static hi_u32 crypto_encrypt_hash(hi_flash_crypto_content *key_content)
{
    hi_cipher_aes_ctrl aes_ctrl;
    hi_u32 ret;
    hi_u32 content_size = (hi_u32)sizeof(hi_flash_crypto_content);
    hi_u32 encrypt_size = content_size - ROOT_SALT_LENGTH - IV_BYTE_LENGTH;

    hi_flash_crypto_content *data_tmp = (hi_flash_crypto_content *)boot_malloc(content_size);
    if (data_tmp == HI_NULL) {
        return HI_PRINT_ERRNO_MALLOC_EXAUST_ERR;
    }

    hi_u32 cs = (uintptr_t)(aes_ctrl.iv) ^ (hi_u32)sizeof(aes_ctrl.iv) ^ (uintptr_t)(key_content->iv_nv) ^
        IV_BYTE_LENGTH;
    ret = (hi_u32)memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), key_content->iv_nv, IV_BYTE_LENGTH, cs);
    if (ret != EOK) {
        goto fail;
    }

    aes_ctrl.random_en = HI_FALSE;
    aes_ctrl.key_from = HI_CIPHER_AES_KEY_FROM_KDF;
    aes_ctrl.work_mode = HI_CIPHER_AES_WORK_MODE_CBC;
    aes_ctrl.key_len = HI_CIPHER_AES_KEY_LENGTH_256BIT;
    ret = hi_cipher_aes_config(&aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }
    ret = hi_cipher_aes_crypto((hi_u32)(uintptr_t)key_content->iv_content, (hi_u32)(uintptr_t)(data_tmp->iv_content),
        encrypt_size, HI_TRUE);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

    hi_u8* key_content_ptr = key_content->iv_content;
    hi_u8* data_tmp_ptr = data_tmp->iv_content;
    cs = (uintptr_t)key_content_ptr ^ encrypt_size ^ (uintptr_t)data_tmp_ptr ^ encrypt_size;
    ret = memcpy_s(key_content_ptr, encrypt_size, data_tmp_ptr, encrypt_size, cs);

crypto_fail:
    (hi_void) hi_cipher_aes_destroy_config();
fail:
    crypto_clear_content((hi_u8 *)data_tmp, content_size);
    crypto_mem_free(data_tmp);
    return ret;
}

static hi_u32 crypto_decrypt_hash(hi_flash_crypto_content *key_content)
{
    hi_u32 ret;
    hi_u32 cs;
    hi_u32 content_size = (hi_u32)sizeof(hi_flash_crypto_content);

    hi_flash_crypto_content *content_tmp = (hi_flash_crypto_content *)boot_malloc(content_size);
    if (content_tmp == HI_NULL) {
        return HI_PRINT_ERRNO_MALLOC_EXAUST_ERR;
    }

    cs = (uintptr_t)(content_tmp) ^ content_size ^ (uintptr_t)(key_content) ^ content_size;
    ret = (hi_u32)memcpy_s(content_tmp, content_size, key_content, content_size, cs);
    if (ret != EOK) {
        goto fail;
    }

    hi_cipher_aes_ctrl aes_ctrl = {
        .random_en = HI_FALSE,
        .key_from = HI_CIPHER_AES_KEY_FROM_KDF,
        .work_mode = HI_CIPHER_AES_WORK_MODE_CBC,
        .key_len = HI_CIPHER_AES_KEY_LENGTH_256BIT,
    };
    cs = (uintptr_t)(aes_ctrl.iv) ^ (hi_u32)sizeof(aes_ctrl.iv) ^ (uintptr_t)(content_tmp->iv_nv) ^ IV_BYTE_LENGTH;
    ret = (hi_u32)memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), content_tmp->iv_nv, IV_BYTE_LENGTH, cs);
    if (ret != EOK) {
        goto fail;
    }
    ret = hi_cipher_aes_config(&aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }
    ret = hi_cipher_aes_crypto((uintptr_t)content_tmp->iv_content, (uintptr_t)key_content->iv_content,
        content_size - ROOT_SALT_LENGTH - IV_BYTE_LENGTH, HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

crypto_fail:
    (hi_void) hi_cipher_aes_destroy_config();
fail:
    crypto_clear_content((hi_u8 *)content_tmp, content_size);
    crypto_mem_free(content_tmp);
    return ret;
}

static hi_u32 crypto_save_work_key(crypto_workkey_partition part, hi_flash_crypto_content *key_content)
{
    hi_u32 ret;
    hi_u32 cs;
    hi_u32 content_size = (hi_u32)sizeof(hi_flash_crypto_content);
    hi_flash_crypto_content *content_tmp = (hi_flash_crypto_content *)boot_malloc(content_size);
    if (content_tmp == HI_NULL) {
        return HI_PRINT_ERRNO_MALLOC_EXAUST_ERR;
    }

    cs = (uintptr_t)(content_tmp) ^ content_size ^ (uintptr_t)(key_content) ^ content_size;
    ret = (hi_u32)memcpy_s(content_tmp, content_size, key_content, content_size, cs);
    if (ret != EOK) {
        goto fail;
    }

    /* 先加密，再存到工厂区NV中 */
    ret = crypto_encrypt_hash(content_tmp);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    if ((hi_u32)part & CRYPTO_WORKKEY_KERNEL_A) {
        ret = hi_factory_nv_write(HI_NV_FTM_KERNELA_WORK_ID, content_tmp, content_size, 0);
        if (ret != HI_ERR_SUCCESS) {
            ret = HI_PRINT_ERRNO_CRYPTO_KEY_SAVE_ERR;
            goto fail;
        }
    }
    if ((hi_u32)part & CRYPTO_WORKKEY_KERNEL_A_BACKUP) {
        ret = hi_factory_nv_write(HI_NV_FTM_BACKUP_KERNELA_WORK_ID, content_tmp, content_size, 0);
        if (ret != HI_ERR_SUCCESS) {
            ret =  HI_PRINT_ERRNO_CRYPTO_KEY_SAVE_ERR;
            goto fail;
        }
    }

fail:
    crypto_clear_content((hi_u8 *)content_tmp, content_size);
    crypto_mem_free(content_tmp);
    return ret;
}

static hi_u32 crypto_load_key_content(crypto_workkey_partition part, hi_flash_crypto_content *key_content)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u8 hash[SHA_256_LENGTH];
    hi_u8 key_e[KEY_BYTE_LENGTH] = { 0 };

    hi_u32 cs = (uintptr_t)key_e ^ (hi_u32)sizeof(key_e) ^ 0x0 ^ KEY_BYTE_LENGTH;
    (hi_void) memset_s(key_e, sizeof(key_e), 0x0, KEY_BYTE_LENGTH, cs);
    if (part == CRYPTO_WORKKEY_KERNEL_A) {
        ret = hi_factory_nv_read(HI_NV_FTM_KERNELA_WORK_ID, key_content, sizeof(hi_flash_crypto_content), 0);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        }
    } else if (part == CRYPTO_WORKKEY_KERNEL_A_BACKUP) {
        ret = hi_factory_nv_read(HI_NV_FTM_BACKUP_KERNELA_WORK_ID, key_content, sizeof(hi_flash_crypto_content), 0);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        }
    } else if (part == CRYPTO_WORKKEY_KERNEL_B) {
        ret = hi_factory_nv_read(HI_NV_FTM_KERNELB_WORK_ID, key_content, sizeof(hi_flash_crypto_content), 0);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        }
    } else if (part == CRYPTO_WORKKEY_KERNEL_B_BACKUP) {
        ret = hi_factory_nv_read(HI_NV_FTM_BACKUP_KERNELB_WORK_ID, key_content, sizeof(hi_flash_crypto_content), 0);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        }
    }

    if (memcmp(key_content->work_text, key_e, KEY_BYTE_LENGTH) == HI_ERR_SUCCESS) {
        ret = HI_PRINT_ERRNO_CRYPTO_KEY_EMPTY_ERR;
        goto fail;
    }

    ret = crypto_decrypt_hash(key_content);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = hi_cipher_hash_sha256((uintptr_t)(key_content->root_salt), sizeof(hi_flash_crypto_content) - SHA_256_LENGTH,
                                hash, SHA_256_LENGTH);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }
    if (memcmp(key_content->content_sh256, hash, SHA_256_LENGTH) != HI_ERR_SUCCESS) {
        ret = HI_PRINT_ERRNO_CRYPTO_KEY_INVALID_ERR;
        goto fail;
    }
fail:
    return ret;
}

static hi_u32 crypto_gen_key_content(hi_flash_crypto_content *key_content)
{
    hi_u8 salt[IV_BYTE_LENGTH];
    hi_u8 kdf_key[KEY_BYTE_LENGTH];
    hi_cipher_kdf_ctrl ctrl;

    (hi_void)hi_cipher_trng_get_random_bytes(salt, IV_BYTE_LENGTH);
    (hi_void)hi_cipher_trng_get_random_bytes(kdf_key, KEY_BYTE_LENGTH);
    (hi_void)hi_cipher_trng_get_random_bytes(key_content->iv_nv, IV_BYTE_LENGTH);
    (hi_void)hi_cipher_trng_get_random_bytes(key_content->iv_content, IV_BYTE_LENGTH);

    hi_u32 cs = (uintptr_t)(ctrl.key) ^ (hi_u32)sizeof(ctrl.key) ^ (uintptr_t)kdf_key ^ (hi_u32)sizeof(kdf_key);
    if ((hi_u32)memcpy_s(ctrl.key, sizeof(ctrl.key), kdf_key, sizeof(kdf_key), cs) != EOK) {
        return HI_ERR_FAILURE;
    }
    ctrl.salt = salt;
    ctrl.salt_len = sizeof(salt);
    ctrl.kdf_cnt = KDF_ITERATION_CNT;
    ctrl.kdf_mode = HI_CIPHER_SSS_KDF_KEY_DEVICE; /* 用户提供HUK值的方式 */
    if (hi_cipher_kdf_key_derive(&ctrl) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    cs = (uintptr_t)(key_content->work_text) ^ KEY_BYTE_LENGTH ^ (uintptr_t)(ctrl.result) ^ (hi_u32)sizeof(ctrl.result);
    if (memcpy_s(key_content->work_text, KEY_BYTE_LENGTH, ctrl.result, sizeof(ctrl.result), cs) != EOK) {
        return HI_ERR_FAILURE;
    }

    if (hi_cipher_hash_sha256((uintptr_t)(key_content->root_salt), sizeof(hi_flash_crypto_content) - SHA_256_LENGTH,
        key_content->content_sh256, SHA_256_LENGTH) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 crypto_encrypt_data(hi_flash_crypto_content *content, boot_crypto_ctx *para)
{
    hi_u32 ret = HI_ERR_FAILURE;
    hi_cipher_aes_ctrl aes_ctrl;

    hi_u8 *fw_cyp_data = boot_malloc(para->crypto_total_size);
    if (fw_cyp_data == HI_NULL) {
        return HI_PRINT_ERRNO_CRYPTO_PREPARE_ERR;
    }

    hi_u32 cs = (uintptr_t)(aes_ctrl.key) ^ (hi_u32)sizeof(aes_ctrl.key) ^
        (uintptr_t)(content->work_text) ^ KEY_BYTE_LENGTH;
    if (memcpy_s(aes_ctrl.key, sizeof(aes_ctrl.key), content->work_text, KEY_BYTE_LENGTH, cs) != EOK) {
        goto fail;
    }

    cs = (uintptr_t)(aes_ctrl.iv) ^ (hi_u32)sizeof(aes_ctrl.iv) ^ (uintptr_t)(content->iv_content) ^ IV_BYTE_LENGTH;
    if (memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), content->iv_content, IV_BYTE_LENGTH, cs) != EOK) {
        goto fail;
    }

    crpto_set_aes_ctrl_default_value(&aes_ctrl);
    ret = hi_cipher_aes_config(&aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = hi_cipher_aes_crypto((uintptr_t)(para->buf), (uintptr_t)fw_cyp_data, para->crypto_total_size, HI_TRUE);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

    ret = g_flash_cmd_funcs.write(para->kernel_addr + para->crypto_start_addr, para->crypto_total_size,
                                  (hi_u8 *)fw_cyp_data, HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

crypto_fail:
    (hi_void) hi_cipher_aes_destroy_config();
fail:
    crypto_mem_free(fw_cyp_data);
    return ret;
}

static hi_u32 crypto_decrypt_kernel(hi_flash_crypto_content *content, hi_u32 ram_addr, hi_u32 ram_size)
{
    hi_u32 ret;
    hi_cipher_aes_ctrl aes_ctrl;
    hi_u8 *fw_raw_data = (hi_u8 *)(uintptr_t)ram_addr;
    hi_u32 cs;
    hi_u32 kernel_offset;
    hi_unref_param(ram_size);
    ret = boot_get_crypto_kernel_start(&kernel_offset);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    cs = (uintptr_t)(aes_ctrl.key) ^ (hi_u32)sizeof(aes_ctrl.key) ^ (uintptr_t)(content->work_text) ^ KEY_BYTE_LENGTH;
    ret = (hi_u32)memcpy_s(aes_ctrl.key, sizeof(aes_ctrl.key), content->work_text, KEY_BYTE_LENGTH, cs);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }
    cs = (uintptr_t)(aes_ctrl.iv) ^ (hi_u32)sizeof(aes_ctrl.iv) ^ (uintptr_t)(content->iv_content) ^ IV_BYTE_LENGTH;
    ret = (hi_u32)memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), content->iv_content, IV_BYTE_LENGTH, cs);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    crpto_set_aes_ctrl_default_value(&aes_ctrl);
    ret = hi_cipher_aes_config(&aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = hi_cipher_aes_crypto(kernel_offset + SFC_BUFFER_BASE_ADDRESS, (hi_u32)(uintptr_t)fw_raw_data,
        CRYPTO_KERNEL_LENGTH, HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

crypto_fail:
    (hi_void) hi_cipher_aes_destroy_config();
fail:
    return ret;
}


hi_u32 crypto_load_flash_raw(uintptr_t ram_addr, hi_u32 ram_size)
{
    hi_u32 ret;
    hi_u32 flash_offset = 0;
    uintptr_t addr_start;
    if (ram_addr == 0 || ram_size == 0) {
        return HI_PRINT_ERRNO_CRYPTO_PREPARE_ERR;
    }

    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    addr_start = cfg->addr_start;
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
    addr_start = cfg->addr_write;
#endif
    boot_get_start_addr_offset(addr_start, &flash_offset);

    ret = g_flash_cmd_funcs.read(flash_offset, ram_size, (hi_u8 *)ram_addr);

    return ret;
}

hi_u32 crypto_content_id(crypto_workkey_partition *content, crypto_workkey_partition *content_bak)
{
    hi_flash_partition_table *partition = hi_get_partition_table();
    hi_u32 kernel_a = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
    hi_u32 kernel_b = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr;

    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    if (cfg->addr_start == kernel_a) {
        *content = CRYPTO_WORKKEY_KERNEL_A;
        *content_bak = CRYPTO_WORKKEY_KERNEL_A_BACKUP;
    } else if (cfg->addr_start == kernel_b) {
        *content = CRYPTO_WORKKEY_KERNEL_B;
        *content_bak = CRYPTO_WORKKEY_KERNEL_B_BACKUP;
    } else {
#ifdef CONFIG_FACTORY_TEST_SUPPORT
        hi_u32 kernel_factory = 0;
        hi_nv_ftm_factory_mode factory_mode_cfg = {0};
        hi_u32 ret = hi_factory_nv_read(HI_NV_FTM_FACTORY_MODE, &factory_mode_cfg, sizeof(hi_nv_ftm_factory_mode), 0);
        if (ret != HI_ERR_SUCCESS) {
        } else {
            if (factory_mode_cfg.factory_mode == 0x1) {
                boot_msg0("get ftm addr");
                kernel_factory = factory_mode_cfg.factory_addr_start; /* 0x0: factory mode, start addr:0x14D000. */
            }
        }

        if (cfg->addr_start == kernel_factory) {
            *content = CRYPTO_WORKKEY_KERNEL_A;
            *content_bak = CRYPTO_WORKKEY_KERNEL_A_BACKUP;
        } else {
            return HI_PRINT_ERRNO_CRYPTO_KERNEL_ADDR_ERR;
        }
#else
        return HI_PRINT_ERRNO_CRYPTO_KERNEL_ADDR_ERR;
#endif
    }

    return HI_ERR_SUCCESS;
}

hi_u32 crypto_decrypt(hi_u32 ram_addr, hi_u32 ram_size)
{
    hi_bool is_backup_content = HI_FALSE;
    crypto_workkey_partition work_content;
    crypto_workkey_partition work_content_bak;
    hi_u32 ret = crypto_content_id(&work_content, &work_content_bak);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    hi_flash_crypto_content *key_content = (hi_flash_crypto_content *)boot_malloc(sizeof(hi_flash_crypto_content));
    if (key_content == HI_NULL) {
        return HI_PRINT_ERRNO_CRYPTO_PREPARE_ERR;
    }

    ret = crypto_prepare(key_content);
    if (ret != HI_ERR_SUCCESS) {
        crypto_clear_content((hi_u8 *)key_content, (hi_u32)sizeof(hi_flash_crypto_content));
        crypto_mem_free(key_content);
        return HI_PRINT_ERRNO_CRYPTO_PREPARE_ERR;
    }

    ret = crypto_load_key_content(work_content, key_content);
    if (ret != HI_ERR_SUCCESS) {
        ret = crypto_load_key_content(work_content_bak, key_content);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        } else {
            ret = crypto_save_work_key(work_content, key_content);
            if (ret != HI_ERR_SUCCESS) {
                goto fail;
            }
            is_backup_content = HI_TRUE;
        }
    }

    ret = crypto_decrypt_kernel(key_content, ram_addr, ram_size);
    if ((ret != HI_ERR_SUCCESS) && (is_backup_content == HI_FALSE)) {
        ret = crypto_load_key_content(work_content_bak, key_content);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        }
        ret = crypto_decrypt_kernel(key_content, ram_addr, ram_size);
        if (ret != HI_ERR_SUCCESS) {
            ret = HI_PRINT_ERRNO_CRYPTO_FW_DECRYPT_ERR;
            goto fail;
        }
    }
fail:
    crypto_clear_content((hi_u8 *)key_content, (hi_u32)sizeof(hi_flash_crypto_content));
    crypto_mem_free(key_content);
    crypto_destory();
    return ret;
}

hi_void crypto_check_decrypt(hi_void)
{
    hi_u32 ret;
    hi_nv_ftm_startup_cfg *cfg = boot_upg_get_cfg();
    hi_bool upg_encrypt_flag = is_upg_need_crypto();
    if ((upg_encrypt_flag == HI_TRUE) && (cfg->file_type == HI_UPG_FILE_KERNEL)) {
#if !defined(CONFIG_COMPRESSION_OTA_SUPPORT)
        /* 双分区升级模式，将升级文件加密数据解密到ram中 */
        ret = crypto_decrypt(KERNEL_RAM_ADDR, CRYPTO_KERNEL_LENGTH);
        if (ret != HI_ERR_SUCCESS) {
            boot_put_errno(ret);
        }
#else
        /* 压缩升级模式，将升级加密压缩包原始数据拷贝到ram中 */
        ret = crypto_load_flash_raw(KERNEL_RAM_ADDR, CRYPTO_KERNEL_LENGTH);
        if (ret != HI_ERR_SUCCESS) {
            boot_put_errno(ret);
        }
#endif
    } else {
        /* 普通模式，将运行区加密数据解密到ram中 */
        ret = crypto_decrypt(KERNEL_RAM_ADDR, CRYPTO_KERNEL_LENGTH);
        if (ret != HI_ERR_SUCCESS) {
            boot_put_errno(ret);
        }
    }
}

hi_u32 encrypt_upg_data(boot_crypto_ctx *para)
{
    hi_u32 ret;

    hi_flash_crypto_content *new_content = (hi_flash_crypto_content *)boot_malloc(sizeof(hi_flash_crypto_content));
    if (new_content == HI_NULL) {
        return HI_PRINT_ERRNO_CRYPTO_PREPARE_ERR;
    }

    ret = crypto_prepare(new_content);
    if (ret != HI_ERR_SUCCESS) {
        crypto_clear_content((hi_u8 *)new_content, (hi_u32)sizeof(hi_flash_crypto_content));
        crypto_mem_free(new_content);
        return HI_PRINT_ERRNO_CRYPTO_PREPARE_ERR;
    }

    hi_u32 cs = KERNEL_RAM_ADDR ^ CRYPTO_KERNEL_LENGTH ^ (uintptr_t)(para->buf) ^ CRYPTO_KERNEL_LENGTH;
    ret = memcpy_s((hi_u8 *)KERNEL_RAM_ADDR, CRYPTO_KERNEL_LENGTH, para->buf, CRYPTO_KERNEL_LENGTH, cs);
    if (ret != EOK) {
        goto fail;
    }

    /* 生成新密钥存放到密钥分区 */
    ret = crypto_gen_key_content(new_content);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    /* 更新密钥流程中，密钥备份区暂不更新，待旧kernel解密成功后再更新密钥备份区 */
    ret = crypto_save_work_key(CRYPTO_WORKKEY_KERNEL_A, new_content);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = crypto_encrypt_data(new_content, para);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    /* 新密钥加密数据完毕，更新密钥备份区 */
    ret = crypto_save_work_key(CRYPTO_WORKKEY_KERNEL_A_BACKUP, new_content);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

fail:
    crypto_clear_content((hi_u8 *)new_content, (hi_u32)sizeof(hi_flash_crypto_content));
    crypto_mem_free(new_content);
    crypto_destory();
    return ret;
}

hi_u32 encrypt_para_init(boot_crypto_ctx *encrypt_para, hi_u32 start)
{
    encrypt_para->para_is_init = HI_TRUE;
    encrypt_para->is_crypto_section = HI_TRUE;
    encrypt_para->kernel_addr = start;
    encrypt_para->crypto_start_addr = sizeof(hi_upg_file_head);
    encrypt_para->crypto_total_size = CRYPTO_KERNEL_LENGTH;
    encrypt_para->crypto_end_addr = encrypt_para->crypto_start_addr + encrypt_para->crypto_total_size;
    encrypt_para->cryptoed_size = 0;
    encrypt_para->buf = (hi_u8 *)boot_malloc(CRYPTO_KERNEL_LENGTH);
    if (encrypt_para->buf == HI_NULL) {
        return HI_PRINT_ERRNO_MALLOC_EXAUST_ERR;
    }

    hi_u32 cs = (uintptr_t)(encrypt_para->buf) ^ CRYPTO_KERNEL_LENGTH ^ 0 ^ CRYPTO_KERNEL_LENGTH;
    hi_u32 ret = memset_s(encrypt_para->buf, CRYPTO_KERNEL_LENGTH, 0, CRYPTO_KERNEL_LENGTH, cs);
    if (ret != HI_ERR_SUCCESS) {
        return HI_PRINT_ERRNO_MALLOC_EXAUST_ERR;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 upg_check_encrypt(boot_crypto_ctx *para, hi_u8 *buf, hi_u32 buf_len)
{
    hi_u32 ret;
    hi_u32 cs;

    hi_u32 size = para->cryptoed_size + buf_len;
    if (size > para->crypto_total_size) {
        cs = (uintptr_t)(para->buf + para->cryptoed_size) ^ (para->crypto_total_size - para->cryptoed_size) ^
            (uintptr_t)buf ^ (para->crypto_total_size - para->cryptoed_size);
        if (memcpy_s(para->buf + para->cryptoed_size, para->crypto_total_size - para->cryptoed_size, buf,
            para->crypto_total_size - para->cryptoed_size, cs) != EOK) {
            return HI_PRINT_ERRNO_CRYPTO_KEY_EMPTY_ERR;
        }

        ret = encrypt_upg_data(para);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        ret = hi_flash_write(para->kernel_addr + para->crypto_end_addr, size - para->crypto_total_size,
            buf + (para->crypto_total_size - para->cryptoed_size), HI_FALSE);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        para->is_crypto_section = HI_FALSE;
    } else if (size == para->crypto_total_size) {
        cs = (uintptr_t)(para->buf + para->cryptoed_size) ^ buf_len ^ (uintptr_t)buf ^ buf_len;
        if (memcpy_s(para->buf + para->cryptoed_size, buf_len, buf, buf_len, cs) != EOK) {
            return HI_PRINT_ERRNO_CRYPTO_KEY_EMPTY_ERR;
        }

        ret = encrypt_upg_data(para);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        para->is_crypto_section = HI_FALSE;
    } else {
        cs = (uintptr_t)(para->buf + para->cryptoed_size) ^ (para->crypto_total_size - para->cryptoed_size) ^
            (uintptr_t)buf ^ buf_len;
        if (memcpy_s(para->buf + para->cryptoed_size, para->crypto_total_size - para->cryptoed_size,
            buf, buf_len, cs) != EOK) {
            return HI_PRINT_ERRNO_CRYPTO_KEY_EMPTY_ERR;
        }

        para->cryptoed_size += buf_len;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 upg_encrypt_part_write(hi_u32 start, hi_u32 offset, hi_u8 *buf, hi_u32 buf_len)
{
    hi_u32 ret;
    boot_crypto_ctx *encrypt_para = boot_crypto_get_ctx();
    if (encrypt_para->para_is_init == HI_FALSE) {
        ret =  encrypt_para_init(encrypt_para, start);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }

    if (encrypt_para->crypto_start_addr == offset) {
        ret = upg_check_encrypt(encrypt_para, buf, buf_len);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    } else if ((encrypt_para->crypto_start_addr > offset) &&
               (encrypt_para->crypto_start_addr < (offset + buf_len))) {
        ret = hi_flash_write(start + offset, (encrypt_para->crypto_start_addr - offset), buf, HI_FALSE);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        ret = upg_check_encrypt(encrypt_para, buf + encrypt_para->crypto_start_addr - offset,
            buf_len - (encrypt_para->crypto_start_addr - offset));
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    } else {
        ret = upg_check_encrypt(encrypt_para, buf, buf_len);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }

    if ((encrypt_para->is_crypto_section == HI_FALSE) && (encrypt_para->buf != HI_NULL)) {
        crypto_mem_free(encrypt_para->buf);
    }

    return HI_ERR_SUCCESS;
}

static const hi_u8 g_upg_file_magic[IV_BYTE_LENGTH] = {
    0xE4, 0xEE, 0x10, 0x0E, 0x43, 0x4D, 0x94, 0x24,
    0xC7, 0x54, 0x6D, 0xFB, 0x15, 0xA1, 0x46, 0x97
};

hi_u32 boot_crypto_upg_file_prepare(boot_crypto_ctx *para)
{
    hi_u32 ret;
    hi_cipher_kdf_ctrl ctrl;
    hi_u8 salt[ROOTKEY_IV_BYTE_LENGTH] = {0};

    hi_u32 cs = (uintptr_t)salt ^ sizeof(salt) ^ (uintptr_t)(para->upg_salt) ^ IV_BYTE_LENGTH;
    ret = memcpy_s((hi_void *)salt, sizeof(salt), (hi_void *)(para->upg_salt), IV_BYTE_LENGTH, cs);
    if (ret != EOK) {
        return ret;
    }

    cs = (uintptr_t)(salt + IV_BYTE_LENGTH) ^ (sizeof(salt) - IV_BYTE_LENGTH) ^
        (uintptr_t)g_upg_file_magic ^ IV_BYTE_LENGTH;
    ret = memcpy_s((hi_void *)(salt + IV_BYTE_LENGTH), sizeof(salt) - IV_BYTE_LENGTH,
        (hi_void *)g_upg_file_magic, IV_BYTE_LENGTH, cs);
    if (ret != EOK) {
        return ret;
    }

    ctrl.salt = salt;
    ctrl.salt_len = ROOTKEY_IV_BYTE_LENGTH;
    ctrl.kdf_cnt = KDF_ITERATION_CNT;
    ctrl.kdf_mode = HI_CIPHER_SSS_KDF_KEY_STORAGE;
    ret = hi_cipher_kdf_key_derive(&ctrl);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 boot_crypto_upg_file_decrypt(boot_crypto_ctx *para)
{
    hi_u32 ret;
    hi_cipher_aes_ctrl aes_ctrl;

    ret = hi_cipher_init();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    hi_upg_head *fw_raw_data = (hi_upg_head *)boot_malloc(para->crypto_total_size);
    if (fw_raw_data == HI_NULL) {
        crypto_destory();
        return HI_PRINT_ERRNO_MALLOC_EXAUST_ERR;
    }

    ret = boot_crypto_upg_file_prepare(para);
    if (ret != HI_ERR_SUCCESS) {
        ret = HI_PRINT_ERRNO_UPG_CRYPTO_PREPARE_ERR;
        goto fail;
    }

    hi_u32 cs = (uintptr_t)(aes_ctrl.iv) ^ sizeof(aes_ctrl.iv) ^ (uintptr_t)(para->upg_iv) ^ IV_BYTE_LENGTH;
    ret = memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), para->upg_iv, IV_BYTE_LENGTH, cs);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    aes_ctrl.random_en = HI_FALSE;
    aes_ctrl.key_from = HI_CIPHER_AES_KEY_FROM_KDF;
    aes_ctrl.work_mode = HI_CIPHER_AES_WORK_MODE_CBC;
    aes_ctrl.key_len = HI_CIPHER_AES_KEY_LENGTH_256BIT;
    ret = hi_cipher_aes_config(&aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = hi_cipher_aes_crypto((uintptr_t)(para->buf), (uintptr_t)fw_raw_data, para->crypto_total_size, HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

    cs = (uintptr_t)(para->buf) ^ para->crypto_total_size ^ (uintptr_t)(fw_raw_data) ^ para->crypto_total_size;
    ret = memcpy_s(para->buf, para->crypto_total_size, fw_raw_data, para->crypto_total_size, cs);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

crypto_fail:
    (hi_void) hi_cipher_aes_destroy_config();
fail:
    crypto_mem_free(fw_raw_data);
    crypto_destory();
    return ret;
}

hi_u32 decrypt_para_init(boot_crypto_ctx *para, hi_u32 start)
{
    hi_u32 ret;
    uintptr_t addr_write = start - sizeof (hi_upg_file_head);
    hi_upg_common_head *upg_head = (hi_upg_common_head *)boot_malloc(sizeof(hi_upg_common_head));
    if (upg_head == HI_NULL) {
        return HI_PRINT_ERRNO_MALLOC_EXAUST_ERR;
    }

    ret = hi_flash_read(addr_write, sizeof(hi_upg_common_head), (hi_u8 *)upg_head);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    para->kernel_addr = start;
    para->crypto_start_addr = LZMA_HEAD_SIZE;
    para->crypto_total_size = CRYPTO_KERNEL_LENGTH + sizeof(hi_upg_file_head);
    para->crypto_end_addr = para->crypto_start_addr + para->crypto_total_size;

    hi_u32 cs = (uintptr_t)(para->upg_salt) ^ IV_BYTE_LENGTH ^ (uintptr_t)(upg_head->aes_key) ^
        sizeof(upg_head->aes_key);
    ret = memcpy_s((hi_void *)(para->upg_salt), IV_BYTE_LENGTH, (hi_void *)(upg_head->aes_key),
        sizeof(upg_head->aes_key), cs);
    if (ret != EOK) {
        goto fail;
    }

    cs = (uintptr_t)(para->upg_iv) ^ IV_BYTE_LENGTH ^ (uintptr_t)(upg_head->aes_iv) ^
        sizeof(upg_head->aes_iv);
    ret = memcpy_s((hi_void *)(para->upg_iv), IV_BYTE_LENGTH, (hi_void *)(upg_head->aes_iv),
        sizeof(upg_head->aes_iv), cs);
    if (ret != EOK) {
        goto fail;
    }

    para->buf = (hi_u8 *)boot_malloc(para->crypto_total_size);
    if (para->buf == HI_NULL) {
        ret = HI_PRINT_ERRNO_MALLOC_EXAUST_ERR;
        goto fail;
    }

    ret = hi_flash_read(para->kernel_addr + para->crypto_start_addr, para->crypto_total_size, para->buf);
    if (ret != HI_ERR_SUCCESS) {
        crypto_mem_free(para->buf);
        goto fail;
    }

fail:
    /* clear salt and iv. */
    crypto_clear_content(upg_head->aes_key, (hi_u32)sizeof(upg_head->aes_key));
    crypto_clear_content(upg_head->aes_iv, (hi_u32)sizeof(upg_head->aes_iv));
    crypto_mem_free(upg_head);
    return ret;
}

hi_void set_upg_decrypt_flag(boot_crypto_ctx *para)
{
    para->para_is_init = HI_TRUE;
    para->is_crypto_section = HI_TRUE;
    para->is_verify_byte = HI_FALSE;
    para->data_medium = DATA_MEDIUM_NOT_INIT;
    para->ram_offset = 0;
    para->cryptoed_size = 0;
}

hi_u32 upg_check_decrypt(boot_crypto_ctx *para, hi_u8 *buf, hi_u32 buf_len)
{
    hi_u32 ret;
    hi_u32 cs;

    hi_u32 size = para->cryptoed_size + buf_len;
    if (size > para->crypto_total_size) {
        cs = (uintptr_t)buf ^ (para->crypto_total_size - para->cryptoed_size) ^
            (uintptr_t)(para->buf + para->cryptoed_size) ^ (para->crypto_total_size - para->cryptoed_size);
        ret = memcpy_s(buf, para->crypto_total_size - para->cryptoed_size, para->buf + para->cryptoed_size,
            para->crypto_total_size - para->cryptoed_size, cs);
        if (ret != EOK) {
            return ret;
        }

        ret = hi_flash_read(para->kernel_addr + para->crypto_end_addr, size - para->crypto_total_size,
            buf + (para->crypto_total_size - para->cryptoed_size));
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        para->ram_offset = para->cryptoed_size;
        para->cryptoed_size = para->crypto_total_size;
    } else if (size == para->crypto_total_size) {
        cs = (uintptr_t)buf ^ buf_len ^ (uintptr_t)(para->buf + para->cryptoed_size) ^ buf_len;
        ret = memcpy_s(buf, buf_len, para->buf + para->cryptoed_size, buf_len, cs);
        if (ret != EOK) {
            return ret;
        }

        para->ram_offset = para->cryptoed_size;
        para->cryptoed_size = para->crypto_total_size;
    } else {
        cs = (uintptr_t)buf ^ buf_len ^ (uintptr_t)(para->buf + para->cryptoed_size) ^ buf_len;
        ret = memcpy_s(buf, buf_len, para->buf + para->cryptoed_size, buf_len, cs);
        if (ret != EOK) {
            return ret;
        }

        para->ram_offset = para->cryptoed_size;
        para->cryptoed_size += buf_len;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 upg_decrypt_part_read(hi_u32 start, hi_u32 offset, hi_u8 *buf, hi_u32 buf_len)
{
    hi_u32 ret;
    boot_crypto_ctx *decrypt_para = boot_decrypt_get_ctx();
    if (decrypt_para->para_is_init == HI_FALSE) {
        set_upg_decrypt_flag(decrypt_para);
    }

    if ((decrypt_para->is_verify_byte == HI_TRUE) && (buf_len == 1)) {
        decrypt_para->is_verify_byte = HI_FALSE;
        if (decrypt_para->cryptoed_size == decrypt_para->crypto_total_size) {
            decrypt_para->is_crypto_section = HI_FALSE;
            decrypt_para->para_is_init = HI_FALSE;
        }

        if (decrypt_para->data_medium == DATA_MEDIUM_RAM) {
            buf[0] = decrypt_para->buf[decrypt_para->ram_offset];
        } else if (decrypt_para->data_medium == DATA_MEDIUM_FLASH) {
            ret = hi_flash_read(start + offset, buf_len, buf);
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            }
        }

        return HI_ERR_SUCCESS;
    }

    if (decrypt_para->crypto_start_addr == offset) {
        ret = upg_check_decrypt(decrypt_para, buf, buf_len);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        decrypt_para->data_medium = DATA_MEDIUM_RAM;
    } else if ((decrypt_para->crypto_start_addr > offset) && (decrypt_para->crypto_start_addr < (offset + buf_len))) {
        ret = hi_flash_read(start + offset, (decrypt_para->crypto_start_addr - offset), buf);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        ret = upg_check_decrypt(decrypt_para, buf + decrypt_para->crypto_start_addr - offset,
            buf_len - (decrypt_para->crypto_start_addr - offset));
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        decrypt_para->data_medium = DATA_MEDIUM_FLASH;
    } else {
        ret = upg_check_decrypt(decrypt_para, buf, buf_len);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        decrypt_para->data_medium = DATA_MEDIUM_RAM;
    }
    decrypt_para->is_verify_byte = HI_TRUE;

    return HI_ERR_SUCCESS;
}

hi_u32 crypto_kernel_write(hi_u32 start, hi_u32 offset, hi_u8 *buf, hi_u32 buf_len)
{
    hi_u32 ret;
    boot_crypto_ctx *para = boot_crypto_get_ctx();
    hi_u32 code_offset = (hi_u32)sizeof(hi_upg_file_head);

    if (((code_offset >= offset) && (code_offset < (offset + buf_len))) || (para->is_crypto_section == HI_TRUE)) {
        ret = upg_encrypt_part_write(start, offset, buf, buf_len);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg1("encrypt flash fail! Err: ", ret);
            return ret;
        }
    } else {
        ret = hi_flash_write(start + offset, buf_len, buf, HI_FALSE);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }

    return HI_ERR_SUCCESS;
}

hi_u32 crypto_kernel_read(hi_u32 start, hi_u32 offset, hi_u8 *buf, hi_u32 buf_len)
{
    hi_u32 ret;
    boot_crypto_ctx *para = boot_decrypt_get_ctx();
    hi_u32 code_offset = LZMA_HEAD_SIZE;

    if (((code_offset >= offset) && (code_offset < (offset + buf_len))) || (para->is_crypto_section == HI_TRUE)) {
        ret = upg_decrypt_part_read(start, offset, buf, buf_len);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg1("decrypt flash fail! Err: ", ret);
            return ret;
        }
    } else {
        ret = hi_flash_read(start + offset, buf_len, buf);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
    }

    return HI_ERR_SUCCESS;
}

hi_u32 boot_decrypt_upg_file(hi_u32 addr_write, const hi_upg_section_head *section_head)
{
    hi_u32 ret;
    hi_u32 start_offset = addr_write + section_head->section0_offset;
    boot_crypto_ctx *decrypt_para = boot_decrypt_get_ctx();

    ret =  decrypt_para_init(decrypt_para, start_offset);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("init decrypt para, err: ", ret);
        crypto_mem_free(decrypt_para->buf);
        return ret;
    }

    ret = boot_crypto_upg_file_decrypt(decrypt_para);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("decrypt upg file, err: ", ret);
        crypto_mem_free(decrypt_para->buf);
        return HI_PRINT_ERRNO_UPG_CRYPTO_DECRYPT_ERR;
    }

    return ret;
}

hi_void boot_decrypt_free_memory(hi_void)
{
    boot_crypto_ctx *decrypt_para = boot_decrypt_get_ctx();
    crypto_mem_free(decrypt_para->buf);
}

#endif
