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

#include <upg_check_secure.h>
#include <brain_pool_p256r1.h>
#include <hi_efuse.h>
#include <upg_common.h>

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
#include "kernel_crypto.h"
#endif

hi_u8 g_upg_tool_block[HI_BLOCK_SIZE];

hi_u32 upg_is_secure_efuse(hi_bool *secure_flag)
{
    hi_u8 data = 0;
    hi_u32 ret = hi_efuse_read(HI_EFUSE_SEC_BOOT_RW_ID, (hi_u8 *)(&data), (hi_u8)(sizeof(hi_u8)));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg]secure efuse read err:0x%x \r\n", ret);
        return ret;
    }

    if (data == UPG_SEC_BOOT_FLAG) {
        *secure_flag = HI_FALSE;
    } else {
        *secure_flag = HI_TRUE;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 upg_hash_one_content(hi_u32 flash_addr, hi_u32 total_size, hi_u8 *hash, hi_u32 hash_size)
{
    hi_u8 *block = g_upg_tool_block;
    uintptr_t offset;
    uintptr_t this_size;
    hi_cipher_hash_atts hash_atts;

    (hi_void) memset_s(&hash_atts, sizeof(hash_atts), 0, sizeof(hash_atts));
    hash_atts.sha_type = HI_CIPHER_HASH_TYPE_SHA256;
    hi_u32 ret = hi_cipher_hash_start((hi_cipher_hash_atts *)(&hash_atts));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg hash one content]cipher start ret:0x%x \r\n", ret);
        return ret;
    }

    for (offset = 0; offset < total_size;) {
        this_size = ((total_size - offset) > HI_BLOCK_SIZE) ? HI_BLOCK_SIZE : (total_size - offset);

        ret = (hi_u32)memcpy_s(block, this_size, (hi_u8 *)(HI_FLASH_BASE + flash_addr + offset), this_size);
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[upg hash one content]flash read ret:0x%x \r\n", ret);
            (hi_void) hi_cipher_hash_final(hash, hash_size);
            return ret;
        }

        ret = hi_cipher_hash_update((uintptr_t)block, this_size);
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[upg hash one content]hash update ret:0x%x \r\n", ret);
            return ret;
        }
        offset += this_size;
    }
    return hi_cipher_hash_final(hash, hash_size);
}

hi_u32 upg_hash_more_content(HI_CONST upg_verify_param *param, hi_u8 *hash, hi_u32 hash_size)
{
    hi_u8 *block = g_upg_tool_block;
    uintptr_t offset;
    uintptr_t this_size;
    hi_cipher_hash_atts hash_atts;

    (hi_void) memset_s(&hash_atts, sizeof(hash_atts), 0, sizeof(hash_atts));
    hash_atts.sha_type = HI_CIPHER_HASH_TYPE_SHA256;
    hi_u32 ret = hi_cipher_hash_start((hi_cipher_hash_atts *)(&hash_atts));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg hash more content]cipher start ret:0x%x \r\n", ret);
        return ret;
    }

    for (hi_u32 i = 0; i < param->buffer_count; i++) {
        uintptr_t size = param->total_size[i];
        for (offset = 0; offset < size;) {
            this_size = ((size - offset) > HI_BLOCK_SIZE) ? HI_BLOCK_SIZE : (size - offset);
            if (param->flash_flag[i]) {
                ret = (hi_u32)memcpy_s(block, this_size, (hi_u8 *)(HI_FLASH_BASE + param->flash_addr[i] + offset),
                    this_size);
            } else {
                ret = (hi_u32)memcpy_s(block, HI_BLOCK_SIZE, (hi_u8 *)(param->flash_addr[i] + offset), this_size);
            }
            if (ret != HI_ERR_SUCCESS) {
                upg_print("[upg hash more content]get content ret:0x%x \r\n", ret);
                (hi_void) hi_cipher_hash_final(hash, hash_size);
                return ret;
            }

            ret = hi_cipher_hash_update((uintptr_t)block, this_size);
            if (ret != HI_ERR_SUCCESS) {
                upg_print("[upg hash more content]hash update ret:0x%x \r\n", ret);
                return ret;
            }
            offset += this_size;
        }
    }
    return hi_cipher_hash_final(hash, hash_size);
}

hi_u32 upg_convert_cipher_err(hi_u32 buffer_cnt, hi_u32 cipher_err)
{
    hi_u32 ret = cipher_err;

    if (cipher_err != HI_ERR_FAILURE) {
        return ret;
    }
    if (buffer_cnt < 2) { /* 2: code section buf cnt */
        ret = HI_ERR_UPG_COMMON_HASH;
    } else {
        ret = HI_ERR_UPG_SECTION_HASH;
    }
    return ret;
}

hi_u32 upg_secure_verify(HI_CONST upg_verify_param *param)
{
    hi_bool flag;
    hi_u8 hash[SHA_256_LEN] = { 0 };
    hi_u32 ret = upg_hash_more_content(param, hash, sizeof(hash));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg secure verify]hash more content ret:0x%x \r\n", ret);
        return ret;
    }
    ret = upg_is_secure_efuse(&flag);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (flag != HI_TRUE) {
        if (memcmp(param->sign, hash, SHA_256_LEN) != EOK) {
            ret = HI_ERR_UPG_SECTION_SHA256;
        }
        /* Common head only check one content. */
        if ((ret != HI_ERR_SUCCESS) && (param->buffer_count < 2)) { /* 2: code section buf cnt */
            ret = HI_ERR_UPG_COMMON_SHA256;
        }
        return ret;
    }
    if (param->pad_mode == HI_MODE_ECC) {
        hi_cipher_ecc_verify ecc_verify = {
            .px = param->key_n,
            .py = param->key_e,
            .hash = hash,
            .hash_len = PKE_LEN_32_BYTES,
            .r = (hi_u8 *)param->sign,
            .s = (hi_u8 *)param->sign + ECC_32_BYTES,
        };
        ret = hi_cipher_ecc_verify_hash(&g_brain_pool_p256r1_verify, &ecc_verify);
    } else {
        hi_cipher_rsa_verify rsa_verify = {
            .n = param->key_n,
            .e = param->key_e,
            .klen = RSA_2048_LEN,
            .scheme = (hi_cipher_rsa_sign_scheme)(param->pad_mode),
        };
        ret = hi_cipher_rsa_verify_hash(&rsa_verify, hash, PKE_LEN_32_BYTES, param->sign, sizeof(upg_rsa_sign));
    }
    ret = upg_convert_cipher_err(param->buffer_count, ret);
    upg_print("[upg secure verify]sign ret-mode:0x%x-0x%x \r\n", ret, param->pad_mode);
    return ret;
}

hi_void upg_get_subkey(hi_u8 *key, hi_u32 key_length, HI_CONST hi_upg_head *upg_head)
{
    hi_u32 key2_offset = sizeof(hi_upg_common_head) + key_length;
    memset_s(key, key_length, 0, key_length);
    if (upg_head->common.param.sign_alg == HI_MODE_ECC) {
        if (memcpy_s(key, key_length, (hi_u8 *)upg_head + key2_offset, ECC_256_LEN) != EOK) {
            return;
        }
    } else {
        if (memcpy_s(key + key_length - RSA_EXP_E_LEN, RSA_EXP_E_LEN, (hi_u8 *)upg_head + key2_offset, RSA_EXP_E_LEN)
            != EOK) {
            return;
        }
    }
}

hi_void upg_crypto_set_secure_verify_param(upg_verify_param *param, hi_u32 flash_addr,
    const hi_upg_common_head *head)
{
    param->flash_addr[0] = (uintptr_t)flash_addr + head->section_offset;
    param->total_size[0] = sizeof(hi_upg_section_head);
    param->flash_flag[0] = HI_TRUE;
#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT) && (!defined(CONFIG_COMPRESSION_OTA_SUPPORT))
    encrypt_ctx *para = encrypt_get_ctx();
    para->raw_buf = (hi_u8 *)hi_malloc(0, CRYPTO_KERNEL_LENGTH);
    if (para->raw_buf == HI_NULL) {
        return;
    }

    hi_u32 ret = crypto_decrypt(para);
    if (ret != HI_ERR_SUCCESS) {
        param->buffer_count = 0;
        return;
    }

    param->flash_addr[1] = (uintptr_t)(para->raw_buf);
    param->total_size[1] = para->encrypt_size;
    param->flash_flag[1] = HI_FALSE;
    param->flash_addr[FLASH_ADDR_NUM - 1] = flash_addr + head->section_offset + sizeof(hi_upg_section_head) +
                                            sizeof(hi_upg_sign) + para->encrypt_size;
    param->total_size[TOTAL_SIZE_NUM - 1] = head->section_len - sizeof(hi_upg_section_head) - sizeof(hi_upg_sign) -
                                            para->encrypt_size;
    param->flash_flag[FLASH_FLAG_NUM - 1] = HI_TRUE;
    param->buffer_count = 3; /* 3 segments */
#else
    param->flash_addr[1] = flash_addr + head->section_offset + sizeof(hi_upg_section_head) + sizeof(hi_upg_sign);
    param->total_size[1] = head->section_len - sizeof(hi_upg_section_head) - sizeof(hi_upg_sign);
    param->flash_flag[1] = HI_TRUE;
    param->buffer_count = 2; /* 2 segments */
#endif
}

hi_void upg_set_secure_verify_param(upg_verify_param *param, hi_u32 flash_addr, const hi_upg_common_head *head)
{
    if (head->file_type == HI_UPG_FILE_KERNEL) {
        upg_crypto_set_secure_verify_param(param, flash_addr, head);
    } else if (head->file_type == HI_UPG_FILE_BOOT) {
        param->flash_addr[0] = (uintptr_t)flash_addr + head->section_offset;
        param->total_size[0] = sizeof(hi_upg_section_head);
        param->flash_flag[0] = HI_TRUE;
        param->flash_addr[1] = flash_addr + head->section_offset + sizeof(hi_upg_section_head) + sizeof(hi_upg_sign);
        param->total_size[1] = head->section_len - sizeof(hi_upg_section_head) - sizeof(hi_upg_sign);
        param->flash_flag[1] = HI_TRUE;
        param->buffer_count = 2; /* 2 segments */
    }
}

hi_u32 upg_check_upg_file_code(hi_u32 flash_addr, hi_upg_head *upg_head)
{
    hi_upg_common_head *head = &(upg_head->common);
    hi_u32 key_length = 0;
    hi_u8 *key2 = HI_NULL;
    hi_bool flag;
    hi_u32 ret = upg_is_secure_efuse(&flag);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    hi_u8 *code_sign = hi_malloc(HI_MOD_ID_UPG, sizeof(hi_upg_sign));
    if (code_sign == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    ret = hi_flash_read(flash_addr + head->section_offset + sizeof(hi_upg_section_head),
                        sizeof(hi_upg_sign), (hi_u8 *)code_sign);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg verify code]flash read ret:0x%x \r\n", ret);
        goto end;
    }
    if (flag == HI_TRUE) {
        key_length = (head->param.sign_alg == HI_MODE_ECC) ? ECC_256_LEN : RSA_2048_LEN;
        key2 = hi_malloc(HI_MOD_ID_UPG, key_length);
        if (key2 == HI_NULL) {
            ret = HI_ERR_UPG_MALLOC_FAIL;
            upg_print("[upg verify code] malloc fail. \r\n");
            goto end;
        }
        upg_get_subkey(key2, key_length, upg_head);
    }
    upg_verify_param param = { 0 };
    upg_set_secure_verify_param(&param, flash_addr, head);
    param.key_n = (hi_u8 *)upg_head + sizeof(hi_upg_common_head);
    param.key_e = key2;
    param.key_len = key_length;
    param.sign = code_sign;
    param.pad_mode = (hi_padding_mode)head->param.sign_alg;
    ret = upg_secure_verify(&param);

#if (defined(CONFIG_FLASH_ENCRYPT_SUPPORT)) && (!defined(CONFIG_COMPRESSION_OTA_SUPPORT))
    encrypt_ctx *para = encrypt_get_ctx();
    crypto_mem_free(para->raw_buf);
#endif
end:
    upg_mem_free(code_sign);
    upg_clear_contset((hi_u8 *)key2, key_length);
    upg_mem_free(key2);
    return ret;
}

hi_u32 upg_check_upg_file_head(hi_upg_head *upg_head)
{
    hi_upg_common_head *head = &(upg_head->common);
    hi_u8 *key = HI_NULL;
    hi_u32 key_length = 0; /* 2 key length: (px+py) or (key_n+key_e) */
    hi_bool flag;
    hi_u32 ret = upg_is_secure_efuse(&flag);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (flag == HI_TRUE) {
        key_length = (head->param.sign_alg < HI_MODE_ECC) ? RSA_KEY_LEN : ECC_KEY_LEN;
        key = hi_malloc(HI_MOD_ID_UPG, key_length);
        if (key == HI_NULL) {
            ret = HI_ERR_UPG_MALLOC_FAIL;
            upg_print("[upg verify code] malloc fail. \r\n");
            goto end;
        }
        memset_s(key, key_length, 0, key_length);

        /* Get key from flash */
        if (head->param.sign_alg == HI_MODE_ECC) {
            ret = upg_get_ecc_key_from_boot(key, key_length);
        } else {
            ret = upg_get_rsa_key_from_boot(key, key_length);
        }
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[upg verify head]fail ret:0x%x.\r\n", ret);
            goto end;
        }
    }
    upg_verify_param param = { 0 };
    param.flash_addr[0] = (uintptr_t)upg_head;
    param.total_size[0] = sizeof(hi_upg_common_head) + head->key_len;
    param.buffer_count = 1; /* 1 segments */
    param.key_n = key;
    param.key_len = (key_length / 2); /* 2: ken len include (px+py) or (key_n+key_e) */
    param.key_e = key + param.key_len;
    param.sign = (hi_u8 *)upg_head + sizeof(hi_upg_common_head) + head->key_len;
    param.pad_mode = (hi_padding_mode)head->param.sign_alg;
    ret = upg_secure_verify(&param);
end:
    upg_clear_contset((hi_u8 *)key, key_length);
    upg_mem_free(key);
    return ret;
}

hi_u32 upg_check_upg_file(hi_u32 flash_addr, hi_upg_head *upg_head)
{
    hi_u32 ret = upg_check_upg_file_head(upg_head);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check secure info]verify head,ret:0x%x \r\n", ret);
        return ret;
    }

    ret = upg_check_upg_file_code(flash_addr, upg_head);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check secure info]verify code,ret:0x%x \r\n", ret);
        return ret;
    }
    return HI_ERR_SUCCESS;
}

