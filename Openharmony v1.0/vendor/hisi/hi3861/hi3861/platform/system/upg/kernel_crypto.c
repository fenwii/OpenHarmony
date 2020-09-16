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

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#include <hi_stdlib.h>
#include <hi_mem.h>
#include <hi_cipher.h>
#include <hi_efuse.h>
#include <hi_flash.h>
#include <hi_nv.h>
#include <hi_upg_file.h>
#include <hi_partition_table.h>
#include "upg_common.h"
#include "kernel_crypto.h"

#define SFC_BUFFER_BASE_ADDRESS             0x400000

static const hi_u8 g_upg_file_magic[IV_BYTE_LENGTH] = {
    0xE4, 0xEE, 0x10, 0x0E, 0x43, 0x4D, 0x94, 0x24,
    0xC7, 0x54, 0x6D, 0xFB, 0x15, 0xA1, 0x46, 0x97
};

encrypt_ctx g_encrypt_param = {0};

encrypt_ctx *encrypt_get_ctx(hi_void)
{
    return &g_encrypt_param;
}

hi_void crypto_clear_content(hi_u8 *content, hi_u32 content_len)
{
    if ((content == HI_NULL) || (content_len == 0)) {
        return;
    }

    (hi_void)memset_s(content, content_len, 0x0, content_len);
}

hi_u32 crypto_content_id(encrypt_ctx *cfg, crypto_workkey_partition *content, crypto_workkey_partition *content_bak)
{
    hi_flash_partition_table *partition = hi_get_partition_table();
    hi_u32 kernel_a = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
    hi_u32 kernel_b = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr;
    if (cfg->kernel_start == kernel_a) {
        *content = CRYPTO_WORKKEY_KERNEL_A;
        *content_bak = CRYPTO_WORKKEY_KERNEL_A_BACKUP;
    } else if (cfg->kernel_start == kernel_b) {
        *content = CRYPTO_WORKKEY_KERNEL_B;
        *content_bak = CRYPTO_WORKKEY_KERNEL_B_BACKUP;
    } else {
        return HI_ERR_FLASH_CRYPTO_KERNEL_ADDR_ERR;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 crypto_load_salt(crypto_workkey_partition part, hi_flash_crypto_content *key_content)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u8 salt_e[ROOT_SALT_LENGTH] = { 0 };

    (hi_void) memset_s(salt_e, sizeof(salt_e), 0x0, ROOT_SALT_LENGTH);
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
        ret = HI_ERR_FLASH_CRYPTO_ROOT_SALT_EMPTY_ERR;
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

    ret = hi_cipher_init();
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = crypto_get_root_salt(save_content);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = memcpy_s(rootkey_iv, sizeof(rootkey_iv), save_content->root_salt, ROOT_SALT_LENGTH);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ctrl.salt = rootkey_iv;
    ctrl.salt_len = sizeof(rootkey_iv);
    ctrl.kdf_cnt = ENCRYPT_KDF_ITERATION_CNT;
    ctrl.kdf_mode = HI_CIPHER_SSS_KDF_KEY_STORAGE;
    return hi_cipher_kdf_key_derive(&ctrl);
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

static hi_u32 crypto_decrypt_hash(hi_flash_crypto_content *key_content)
{
    hi_u32 ret;
    hi_u32 content_size = (hi_u32)sizeof(hi_flash_crypto_content);

    hi_flash_crypto_content *content_tmp = (hi_flash_crypto_content *)hi_malloc(HI_MOD_ID_CRYPTO, content_size);
    if (content_tmp == HI_NULL) {
        return HI_ERR_FLASH_CRYPTO_MALLOC_FAIL;
    }

    ret = (hi_u32)memcpy_s(content_tmp, content_size, key_content, content_size);
    if (ret != EOK) {
        goto fail;
    }

    hi_cipher_aes_ctrl aes_ctrl = {
        .random_en = HI_FALSE,
        .key_from = HI_CIPHER_AES_KEY_FROM_KDF,
        .work_mode = HI_CIPHER_AES_WORK_MODE_CBC,
        .key_len = HI_CIPHER_AES_KEY_LENGTH_256BIT,
    };

    ret = (hi_u32)memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), content_tmp->iv_nv, IV_BYTE_LENGTH);
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

static hi_u32 crypto_encrypt_hash(hi_flash_crypto_content *key_content)
{
    hi_cipher_aes_ctrl aes_ctrl;
    hi_u32 content_size = (hi_u32)sizeof(hi_flash_crypto_content);
    hi_u32 encrypt_size = content_size - ROOT_SALT_LENGTH - IV_BYTE_LENGTH;

    hi_flash_crypto_content *data_tmp = (hi_flash_crypto_content *)hi_malloc(HI_MOD_ID_CRYPTO, content_size);
    if (data_tmp == HI_NULL) {
        return HI_ERR_FLASH_CRYPTO_MALLOC_FAIL;
    }

    hi_u32 ret = (hi_u32)memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), key_content->iv_nv, IV_BYTE_LENGTH);
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

    ret = (hi_u32)memcpy_s(key_content->iv_content, encrypt_size, data_tmp->iv_content, encrypt_size);

crypto_fail:
    (hi_void) hi_cipher_aes_destroy_config();
fail:
    crypto_clear_content((hi_u8 *)data_tmp, content_size);
    crypto_mem_free(data_tmp);
    return ret;
}

static hi_u32 crypto_load_key_content(crypto_workkey_partition part, hi_flash_crypto_content *key_content)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u8 hash[SHA_256_LENGTH];
    hi_u8 key_e[KEY_BYTE_LENGTH] = { 0 };

    (hi_void) memset_s(key_e, sizeof(key_e), 0x0, KEY_BYTE_LENGTH);
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
        ret = HI_ERR_FLASH_CRYPTO_KEY_EMPTY_ERR;
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
        ret = HI_ERR_FLASH_CRYPTO_KEY_INVALID_ERR;
        goto fail;
    }
fail:
    return ret;
}

static hi_u32 crypto_save_work_key(crypto_workkey_partition part, hi_flash_crypto_content *key_content)
{
    hi_u32 ret;
    hi_u32 content_size = (hi_u32)sizeof(hi_flash_crypto_content);
    hi_flash_crypto_content *content_tmp = (hi_flash_crypto_content *)hi_malloc(HI_MOD_ID_CRYPTO, content_size);
    if (content_tmp == HI_NULL) {
        return HI_ERR_FLASH_CRYPTO_MALLOC_FAIL;
    }

    ret = (hi_u32)memcpy_s(content_tmp, content_size, key_content, content_size);
    if (ret != EOK) {
        goto fail;
    }

    /* Encrypt，then save to factory NV. */
    ret = crypto_encrypt_hash(content_tmp);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    if ((hi_u32)part & CRYPTO_WORKKEY_KERNEL_A) {
        ret = hi_factory_nv_write(HI_NV_FTM_KERNELA_WORK_ID, content_tmp, content_size, 0);
        if (ret != HI_ERR_SUCCESS) {
            ret = HI_ERR_FLASH_CRYPTO_KEY_SAVE_ERR;
            goto fail;
        }
    }
    if ((hi_u32)part & CRYPTO_WORKKEY_KERNEL_A_BACKUP) {
        ret = hi_factory_nv_write(HI_NV_FTM_BACKUP_KERNELA_WORK_ID, content_tmp, content_size, 0);
        if (ret != HI_ERR_SUCCESS) {
            ret =  HI_ERR_FLASH_CRYPTO_KEY_SAVE_ERR;
            goto fail;
        }
    }

    if ((hi_u32)part & CRYPTO_WORKKEY_KERNEL_B) {
        ret = hi_factory_nv_write(HI_NV_FTM_KERNELB_WORK_ID, content_tmp, content_size, 0);
        if (ret != HI_ERR_SUCCESS) {
            ret = HI_ERR_FLASH_CRYPTO_KEY_SAVE_ERR;
            goto fail;
        }
    }
    if ((hi_u32)part & CRYPTO_WORKKEY_KERNEL_B_BACKUP) {
        ret = hi_factory_nv_write(HI_NV_FTM_BACKUP_KERNELB_WORK_ID, content_tmp, content_size, 0);
        if (ret != HI_ERR_SUCCESS) {
            ret =  HI_ERR_FLASH_CRYPTO_KEY_SAVE_ERR;
            goto fail;
        }
    }

fail:
    crypto_clear_content((hi_u8 *)content_tmp, content_size);
    crypto_mem_free(content_tmp);
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

    if ((hi_u32)memcpy_s(ctrl.key, sizeof(ctrl.key), kdf_key, sizeof(kdf_key)) != EOK) {
        return HI_ERR_FAILURE;
    }
    ctrl.salt = salt;
    ctrl.salt_len = sizeof(salt);
    ctrl.kdf_cnt = ENCRYPT_KDF_ITERATION_CNT;
    ctrl.kdf_mode = HI_CIPHER_SSS_KDF_KEY_DEVICE; /* In this mode, user should provide root key. */
    if (hi_cipher_kdf_key_derive(&ctrl) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    if (memcpy_s(key_content->work_text, KEY_BYTE_LENGTH, ctrl.result, sizeof(ctrl.result)) != EOK) {
        return HI_ERR_FAILURE;
    }

    if (hi_cipher_hash_sha256((uintptr_t)(key_content->root_salt), sizeof(hi_flash_crypto_content) - SHA_256_LENGTH,
        key_content->content_sh256, SHA_256_LENGTH) != HI_ERR_SUCCESS) {
        return HI_ERR_FAILURE;
    }

    return HI_ERR_SUCCESS;
}

static hi_u32 crypto_decrypt_kernel(hi_flash_crypto_content *content, encrypt_ctx *para)
{
    hi_u32 ret;
    hi_cipher_aes_ctrl aes_ctrl;
    hi_u8 *fw_raw_data = para->raw_buf;

    ret = (hi_u32)memcpy_s(aes_ctrl.key, sizeof(aes_ctrl.key), content->work_text, KEY_BYTE_LENGTH);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = (hi_u32)memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), content->iv_content, IV_BYTE_LENGTH);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    crpto_set_aes_ctrl_default_value(&aes_ctrl);
    ret = hi_cipher_aes_config(&aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = hi_cipher_aes_crypto(para->kernel_start + para->encrypt_offset + SFC_BUFFER_BASE_ADDRESS,
        (uintptr_t)fw_raw_data, para->encrypt_size, HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

crypto_fail:
    (hi_void) hi_cipher_aes_destroy_config();
fail:
    return ret;
}

hi_u32 crypto_decrypt(encrypt_ctx *para)
{
    hi_bool is_backup_content = HI_FALSE;
    crypto_workkey_partition werk_content;
    crypto_workkey_partition werk_content_bak;
    hi_u32 ret = crypto_content_id(para, &werk_content, &werk_content_bak);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    hi_flash_crypto_content *key_content = (hi_flash_crypto_content *)hi_malloc(HI_MOD_ID_CRYPTO,
        sizeof(hi_flash_crypto_content));
    if (key_content == HI_NULL) {
        return HI_ERR_FLASH_CRYPTO_PREPARE_ERR;
    }

    ret = crypto_prepare(key_content);
    if (ret != HI_ERR_SUCCESS) {
        crypto_clear_content((hi_u8 *)key_content, (hi_u32)sizeof(hi_flash_crypto_content));
        crypto_mem_free(key_content);
        return HI_ERR_FLASH_CRYPTO_PREPARE_ERR;
    }

    ret = crypto_load_key_content(werk_content, key_content);
    if (ret != HI_ERR_SUCCESS) {
        ret = crypto_load_key_content(werk_content_bak, key_content);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        } else {
            ret = crypto_save_work_key(werk_content, key_content);
            if (ret != HI_ERR_SUCCESS) {
                goto fail;
            }
            is_backup_content = HI_TRUE;
        }
    }

    ret = crypto_decrypt_kernel(key_content, para);
    if ((ret != HI_ERR_SUCCESS) && (is_backup_content == HI_FALSE)) {
        ret = crypto_load_key_content(werk_content_bak, key_content);
        if (ret != HI_ERR_SUCCESS) {
            goto fail;
        }
        ret = crypto_decrypt_kernel(key_content, para);
        if (ret != HI_ERR_SUCCESS) {
            ret = HI_ERR_FLASH_CRYPTO_DATA_DECRYPT_ERR;
            goto fail;
        }
    }
fail:
    crypto_clear_content((hi_u8 *)key_content, (hi_u32)sizeof(hi_flash_crypto_content));
    crypto_mem_free(key_content);
    return ret;
}

static hi_u32 crypto_encrypt_data(hi_flash_crypto_content *new_content, encrypt_ctx *para)
{
    hi_u32 ret = HI_ERR_FAILURE;
    hi_cipher_aes_ctrl aes_ctrl;

    hi_u8 *fw_cyp_data = hi_malloc(HI_MOD_ID_CRYPTO, para->encrypt_size);
    if (fw_cyp_data == HI_NULL) {
        return HI_ERR_FLASH_CRYPTO_PREPARE_ERR;
    }

    if (memcpy_s(aes_ctrl.key, sizeof(aes_ctrl.key), new_content->work_text, KEY_BYTE_LENGTH) != EOK) {
        goto fail;
    }

    if (memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), new_content->iv_content, IV_BYTE_LENGTH) != EOK) {
        goto fail;
    }

    crpto_set_aes_ctrl_default_value(&aes_ctrl);
    ret = hi_cipher_aes_config(&aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = hi_cipher_aes_crypto((uintptr_t)(para->raw_buf), (uintptr_t)fw_cyp_data, para->encrypt_size, HI_TRUE);
    (hi_void) hi_cipher_aes_destroy_config();
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = hi_flash_write(para->kernel_start + para->encrypt_offset, para->encrypt_size, fw_cyp_data, HI_TRUE);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

fail:
    crypto_mem_free(fw_cyp_data);
    return ret;
}

hi_u32 encrypt_check_start_addr(hi_u32 offset_addr)
{
    hi_flash_partition_table *partition = hi_get_partition_table();
    hi_u32 kernel_a = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
    hi_u32 kernel_b = partition->table[HI_FLASH_PARTITON_KERNEL_B].addr;

    if ((offset_addr != kernel_a) && (offset_addr != kernel_b)) {
        return HI_ERR_FLASH_CRYPTO_INVALID_PARAM;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 encrypt_upg_data(encrypt_ctx *para)
{
    hi_u32 ret;
    crypto_workkey_partition werk_content;
    crypto_workkey_partition werk_content_bak;
    ret = crypto_content_id(para, &werk_content, &werk_content_bak);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    hi_flash_crypto_content *new_content = (hi_flash_crypto_content *)hi_malloc(HI_MOD_ID_CRYPTO,
        sizeof(hi_flash_crypto_content));
    if (new_content == HI_NULL) {
        return HI_ERR_FLASH_CRYPTO_PREPARE_ERR;
    }

    ret = crypto_prepare(new_content);
    if (ret != HI_ERR_SUCCESS) {
        crypto_clear_content((hi_u8 *)new_content, (hi_u32)sizeof(hi_flash_crypto_content));
        crypto_mem_free(new_content);
        return HI_ERR_FLASH_CRYPTO_PREPARE_ERR;
    }

    ret = crypto_gen_key_content(new_content);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = crypto_save_work_key(werk_content, new_content);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = crypto_encrypt_data(new_content, para);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = crypto_save_work_key(werk_content_bak, new_content);
    if (ret != HI_ERR_SUCCESS) {
    }

fail:
    crypto_clear_content((hi_u8 *)new_content, (hi_u32)sizeof(hi_flash_crypto_content));
    crypto_mem_free(new_content);
    return ret;
}

hi_u32 crypto_init_param(encrypt_ctx *para, uintptr_t kernel_start)
{
    hi_u32 ret;

    hi_upg_head *upg_head = (hi_upg_head *)hi_malloc(HI_MOD_ID_CRYPTO, sizeof(hi_upg_head));
    if (upg_head == HI_NULL) {
        return HI_ERR_UPG_CRYPTO_PREPARE_ERR;
    }
    ret = hi_flash_read(kernel_start, sizeof(hi_upg_head), (hi_u8 *)upg_head);
    if (ret != HI_ERR_SUCCESS) {
        crypto_print("[%s]get upg head addr:0x%x ret:0x%x \r\n", __FUNCTION__, kernel_start, ret);
        goto fail;
    }

    para->kernel_start = kernel_start;
    para->encrypt_offset = sizeof(hi_upg_file_head);
    para->encrypt_size = CRYPTO_KERNEL_LENGTH;
    ret = (hi_u32)memcpy_s(para->upg_salt, IV_BYTE_LENGTH, upg_head->common.aes_key, IV_BYTE_LENGTH);
    if (ret != EOK) {
        goto fail;
    }
    ret = (hi_u32)memcpy_s(para->upg_iv, IV_BYTE_LENGTH, upg_head->common.aes_iv, IV_BYTE_LENGTH);
    if (ret != EOK) {
        goto fail;
    }
    para->raw_buf = (hi_u8 *)hi_malloc(0, para->encrypt_size);
    if (para->raw_buf == HI_NULL) {
        ret = HI_ERR_UPG_CRYPTO_PREPARE_ERR;
        goto fail;
    }

fail:
    crypto_mem_free(upg_head);
    return ret;
}

hi_u32 crypto_upg_file_prepare(encrypt_ctx *para)
{
    hi_u32 ret;
    hi_cipher_kdf_ctrl ctrl;
    hi_u8 salt[ROOTKEY_IV_BYTE_LENGTH] = {0};

    ret = (hi_u32)memcpy_s((hi_void *)salt, sizeof(salt), (hi_void *)(para->upg_salt), IV_BYTE_LENGTH);
    if (ret != EOK) {
        return ret;
    }

    ret = (hi_u32)memcpy_s((hi_void *)(salt + IV_BYTE_LENGTH), sizeof(salt) - IV_BYTE_LENGTH,
        (hi_void *)g_upg_file_magic, IV_BYTE_LENGTH);
    if (ret != EOK) {
        return ret;
    }

    ctrl.salt = salt;
    ctrl.salt_len = ROOTKEY_IV_BYTE_LENGTH;
    ctrl.kdf_cnt = ENCRYPT_KDF_ITERATION_CNT;
    ctrl.kdf_mode = HI_CIPHER_SSS_KDF_KEY_STORAGE;

    ret = hi_cipher_kdf_key_derive(&ctrl);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 crypto_upg_file_decrypt(encrypt_ctx *para)
{
    hi_u32 ret;
    hi_cipher_aes_ctrl aes_ctrl;
    hi_u8 *fw_raw_data = para->raw_buf;

    ret = crypto_upg_file_prepare(para);
    if (ret != HI_ERR_SUCCESS) {
        return HI_ERR_UPG_CRYPTO_PREPARE_ERR;
    }

    ret = (hi_u32)memcpy_s(aes_ctrl.iv, sizeof(aes_ctrl.iv), para->upg_iv, IV_BYTE_LENGTH);
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

    ret = hi_cipher_aes_crypto(para->kernel_start + para->encrypt_offset + SFC_BUFFER_BASE_ADDRESS,
        (uintptr_t)fw_raw_data, para->encrypt_size, HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        goto crypto_fail;
    }

crypto_fail:
    (hi_void) hi_cipher_aes_destroy_config();
fail:
    return ret;
}


hi_u32 crypto_encrypt_data_to_flash(uintptr_t kernel_offset)
{
    hi_u32 ret;
    encrypt_ctx *data = encrypt_get_ctx();

    ret = crypto_init_param(data, kernel_offset);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = crypto_upg_file_decrypt(data);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

    ret = encrypt_upg_data(data);
    if (ret != HI_ERR_SUCCESS) {
        goto fail;
    }

fail:
    crypto_mem_free(data->raw_buf);
    return ret;
}

#endif
