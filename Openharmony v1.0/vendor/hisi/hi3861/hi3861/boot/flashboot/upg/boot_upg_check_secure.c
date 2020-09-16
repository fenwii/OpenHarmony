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

#include "boot_upg_check_secure.h"

#include <hi_flashboot.h>
#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#include <crypto.h>
#endif

#include "boot_upg_tool.h"

#ifndef FLASHBOOT_KEY_SECTION
#define FLASHBOOT_KEY_SECTION       __attribute__ ((section(".boot.data.key")))
#endif

#if (defined(CONFIG_TARGET_SIG_RSA_V15) || defined(CONFIG_TARGET_SIG_RSA_PSS))
FLASHBOOT_KEY_SECTION hi_u8 g_boot_rsa_key[RSA_2048_LEN] = {
    0xde, 0x6e, 0x28, 0x74, 0x70, 0xf2, 0xee, 0x57, 0x3a, 0x2b, 0x79, 0xec, 0x3f, 0x12, 0xb0, 0x01,
    0xe9, 0x86, 0xe8, 0xa6, 0x4d, 0xad, 0x57, 0xdb, 0x9f, 0x08, 0x8a, 0x07, 0x14, 0x9d, 0x30, 0x4a,
    0xb7, 0x57, 0xac, 0xb7, 0x11, 0xaf, 0xeb, 0x12, 0x69, 0x72, 0x7e, 0x25, 0xb6, 0xb6, 0x06, 0x69,
    0x35, 0x0a, 0x9a, 0x09, 0x42, 0xc7, 0x44, 0xfb, 0x2a, 0xb5, 0x5f, 0x28, 0x58, 0x81, 0x40, 0x3a,
    0xe2, 0x60, 0x81, 0x35, 0x4a, 0xd2, 0xa6, 0x79, 0x39, 0x14, 0xf8, 0xaa, 0x6e, 0xd9, 0x40, 0x6c,
    0xab, 0x4d, 0x7a, 0x12, 0x9f, 0x7f, 0xfb, 0x48, 0xa5, 0x88, 0x15, 0x45, 0x5b, 0xbc, 0x55, 0xc4,
    0xdb, 0x74, 0x48, 0x8c, 0x88, 0x1f, 0x3d, 0xad, 0xf6, 0x3e, 0x28, 0x41, 0xce, 0xef, 0x70, 0xf3,
    0x60, 0x03, 0x69, 0x10, 0xf8, 0x7f, 0x4d, 0xb9, 0xdb, 0xc7, 0x8c, 0x4d, 0x5d, 0x41, 0xc1, 0x0f,
    0xcc, 0x2a, 0x71, 0x80, 0x16, 0xa3, 0x5c, 0x2c, 0xc6, 0x89, 0xbb, 0xd0, 0xcf, 0x86, 0xc8, 0x19,
    0x3f, 0xdb, 0x47, 0x7d, 0xfd, 0xc7, 0x20, 0xb9, 0x6b, 0xad, 0x5d, 0x09, 0x6d, 0xff, 0xd4, 0x86,
    0xe2, 0x04, 0xaa, 0x1e, 0x15, 0x06, 0x7c, 0x0c, 0x8f, 0x53, 0xb3, 0xa4, 0x46, 0x2f, 0xe4, 0xd5,
    0xb0, 0x5a, 0xff, 0x8f, 0xa2, 0x2b, 0xe4, 0x2c, 0x5f, 0x23, 0xa7, 0x03, 0x06, 0xfe, 0x86, 0x38,
    0xde, 0xb8, 0xd9, 0x26, 0xa5, 0xe7, 0x6d, 0x8d, 0x25, 0xea, 0xca, 0x89, 0xc6, 0xf4, 0xfe, 0xf0,
    0x70, 0x54, 0x64, 0x8a, 0xab, 0x92, 0xcf, 0x8a, 0x87, 0xf5, 0x3d, 0x01, 0x07, 0x1d, 0xf2, 0x15,
    0x53, 0xd8, 0x9a, 0xa9, 0x52, 0xde, 0x59, 0x3d, 0x66, 0x1b, 0x63, 0x46, 0x86, 0x78, 0x05, 0x5e,
    0xa4, 0x4a, 0xf9, 0x2d, 0x50, 0xef, 0xca, 0x28, 0x3d, 0xb9, 0x5b, 0x17, 0xec, 0xd5, 0x8a, 0x99
};
#endif

#if defined(CONFIG_TARGET_SIG_ECC)
FLASHBOOT_KEY_SECTION hi_u8 g_boot_ecc_key[ECC_KEY_LEN] = {
    0x47, 0x9c, 0x30, 0xcb, 0x84, 0xe1, 0x05, 0xd1, 0x82, 0x5e, 0xe0, 0xd6, 0x01, 0xb9, 0x96, 0x82,
    0x8f, 0xcd, 0x6e, 0xf7, 0x70, 0xc7, 0x22, 0x9c, 0xeb, 0xdf, 0x02, 0xdb, 0xfd, 0xe6, 0xa6, 0x0c,
    0x19, 0x23, 0x9c, 0x82, 0x69, 0xc8, 0xe7, 0x58, 0xfe, 0x29, 0x6e, 0xa7, 0xaf, 0x2e, 0x0b, 0x36,
    0xc1, 0xd1, 0x7f, 0xd8, 0x88, 0x82, 0x08, 0x03, 0x4f, 0x2b, 0x77, 0xe0, 0x94, 0x30, 0xbf, 0x1b
};
#endif

#if (defined(CONFIG_TARGET_SIG_RSA_V15) || defined(CONFIG_TARGET_SIG_RSA_PSS))
hi_void boot_upg_save_rsa_key_pos(hi_void)
{
    uintptr_t rsa_key_addr = ((uintptr_t)(&g_boot_rsa_key[0]) - (uintptr_t)(&__data_start)) +
                            ((uintptr_t)(&__data_load) - BOOTLOADER_FLASH_HEAD_ADDR);
    hi_reg_write16(DIAG_CTL_GP_REG0_REG, (rsa_key_addr & MASK_U16));
    hi_reg_write16(DIAG_CTL_GP_REG1_REG, (rsa_key_addr >> BIT_U16));
}
#endif

#if defined(CONFIG_TARGET_SIG_ECC)
hi_void boot_upg_save_ecc_key_pos(hi_void)
{
    uintptr_t ecc_key_addr = ((uintptr_t)(&g_boot_ecc_key[0]) - (uintptr_t)(&__data_start)) +
                            ((uintptr_t)(&__data_load) - BOOTLOADER_FLASH_HEAD_ADDR);
    hi_reg_write16(DIAG_CTL_GP_REG2_REG, (ecc_key_addr & MASK_U16));
    hi_reg_write16(DIAG_CTL_GP_REG3_REG, (ecc_key_addr >> BIT_U16));
}
#endif

hi_void boot_upg_save_key_pos(hi_void)
{
#if (defined(CONFIG_TARGET_SIG_RSA_V15) || defined(CONFIG_TARGET_SIG_RSA_PSS))
    boot_upg_save_rsa_key_pos();
#endif
#if defined(CONFIG_TARGET_SIG_ECC)
    boot_upg_save_ecc_key_pos();
#endif
}

hi_void upg_clear_content(hi_u8 *content, hi_u32 content_len)
{
    if ((content == HI_NULL) || (content_len == 0)) {
        return;
    }

    hi_u32 cs = (uintptr_t)content ^ content_len ^ 0x0 ^ content_len;
    (hi_void)memset_s(content, content_len, 0x0, content_len, cs);
}

hi_bool boot_upg_is_secure_efuse(hi_void)
{
    hi_u8 data = 0;
    hi_u32 ret = hi_efuse_read(HI_EFUSE_SEC_BOOT_RW_ID, &data, sizeof(hi_u8));
    if (ret != HI_ERR_SUCCESS) {
        return HI_TRUE;
    }

    if (data == UPG_SEC_BOOT_FLAG) {
        return HI_FALSE;
    }
    return HI_TRUE;
}

hi_u32 boot_upg_secure_get_key_part1(hi_u32 sign_alg, hi_u8 *key_n, hi_u32 key_len)
{
    hi_u32 ret = HI_ERR_UPG_PARAMETER;
    hi_unref_param(sign_alg);
    hi_unref_param(key_n);
    hi_unref_param(key_len);
#if defined(CONFIG_TARGET_SIG_ECC)
    if (sign_alg == HI_MODE_ECC) {
        hi_u32 cs = (uintptr_t)key_n ^ key_len ^ (uintptr_t)g_boot_ecc_key ^ ECC_256_LEN;
        ret = memcpy_s(key_n, key_len, g_boot_ecc_key, ECC_256_LEN, cs);
    }
#endif
#if (defined(CONFIG_TARGET_SIG_RSA_V15) || defined(CONFIG_TARGET_SIG_RSA_PSS))
    if ((sign_alg == HI_MODE_PKCS_V15) || (sign_alg == HI_MODE_PKCS_PSS)) {
        hi_u32 cs = (uintptr_t)key_n ^ key_len ^ (uintptr_t)g_boot_rsa_key ^ RSA_2048_LEN;
        ret = memcpy_s(key_n, key_len, g_boot_rsa_key, RSA_2048_LEN, cs);
    }
#endif
    return ret;
}

hi_u32 boot_upg_secure_get_key_part2(hi_u32 sign_alg, hi_u8 *key_e, hi_u32 key_len)
{
    hi_u32 ret = HI_ERR_UPG_PARAMETER;
    hi_unref_param(sign_alg);
    hi_unref_param(key_e);
    hi_unref_param(key_len);
#if defined(CONFIG_TARGET_SIG_ECC)
    if (sign_alg == HI_MODE_ECC) {
        hi_u32 cs = (uintptr_t)key_e ^ key_len ^ (uintptr_t)(g_boot_ecc_key + ECC_256_LEN) ^ ECC_256_LEN;
        ret = memcpy_s(key_e, key_len, g_boot_ecc_key + ECC_256_LEN, ECC_256_LEN, cs);
    }
#endif
#if (defined(CONFIG_TARGET_SIG_RSA_V15) || defined(CONFIG_TARGET_SIG_RSA_PSS))
    if ((sign_alg == HI_MODE_PKCS_V15) || (sign_alg == HI_MODE_PKCS_PSS)) {
        (key_e)[key_len - 1] = 0x01; /* 1: first byte. 0x01: part of key_e 0x10001 */
        (key_e)[key_len - 3] = 0x01; /* 3: last byte.  0x01: part of key_e 0x10001 */
        ret = HI_ERR_SUCCESS;
    }
#endif
    return ret;
}

hi_u32 boot_upg_secure_verify(HI_CONST upg_verify_param *param)
{
    hi_u8 hash[SHA_256_LEN] = { 0 };
    hi_u8 out_hash[SHA_256_LEN] = { 0 };
    hi_u32 ret = boot_upg_hash_more_content(param, hash, sizeof(hash));

    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("hash more content, ret:", ret);
        return ret;
    }

    if (boot_upg_is_secure_efuse() != HI_TRUE) {
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
            .out_r = out_hash,
        };
        ret = hi_cipher_ecc_verify_hash(&g_brain_pool_p256r1_verify, &ecc_verify);
    } else {
        hi_cipher_rsa_verify rsa_verify = {
            .n = param->key_n,
            .e = param->key_e,
            .klen = param->key_len,
            .scheme = (hi_cipher_rsa_sign_scheme)(param->pad_mode),
        };
        hi_cipher_rsa_data rsa_data = {
            .hash = hash,
            .out_hash = out_hash,
            .hash_len = PKE_LEN_32_BYTES,
            .sign = param->sign,
            .sign_len = sizeof(upg_rsa_sign),
        };
        ret = hi_cipher_rsa_verify_hash(&rsa_verify, &rsa_data);
    }
    return ret;
}

hi_u32 boot_upg_set_key(HI_CONST hi_upg_head *upg_head, hi_u8 *key2, hi_u32 key_length)
{
    hi_u32 key2_offset = sizeof(hi_upg_common_head) + key_length;
    hi_u32 cs;

    if (upg_head->common.param.sign_alg == HI_MODE_ECC) {
        cs = (uintptr_t)key2 ^ ECC_256_LEN ^ (uintptr_t)((hi_u8 *)upg_head + key2_offset) ^ ECC_256_LEN;
        memcpy_s(key2, key_length, (hi_u8 *)upg_head + key2_offset, ECC_256_LEN, cs);
    } else {
        cs = (uintptr_t)(key2 + key_length - RSA_EXP_E_LEN) ^ RSA_EXP_E_LEN ^
            (uintptr_t)((hi_u8 *)upg_head + key2_offset) ^ RSA_EXP_E_LEN;
        memcpy_s(key2 + key_length - RSA_EXP_E_LEN, RSA_EXP_E_LEN, (hi_u8 *)upg_head + key2_offset, RSA_EXP_E_LEN, cs);
    }
    return HI_ERR_SUCCESS;
}

hi_void boot_upg_set_secure_verify_param(upg_verify_param *param, hi_u32 flash_addr, HI_CONST hi_upg_head *upg_head)
{
    param->flash_addr[0] = (uintptr_t)flash_addr + upg_head->common.section_offset;
    param->total_size[0] = sizeof(hi_upg_section_head);
    param->flash_flag[0] = HI_TRUE;
#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
    param->flash_addr[1] = KERNEL_RAM_ADDR;
    param->total_size[1] = CRYPTO_KERNEL_LENGTH;
    param->flash_flag[1] = HI_FALSE;
    param->flash_addr[2] = flash_addr + upg_head->common.section_offset +
                          sizeof(hi_upg_section_head) + sizeof(hi_upg_sign) + CRYPTO_KERNEL_LENGTH;
    param->total_size[2] = upg_head->common.section_len - sizeof(hi_upg_section_head) - sizeof(hi_upg_sign) -
        CRYPTO_KERNEL_LENGTH;
    param->flash_flag[2] = HI_TRUE;
    param->buffer_count = 3; /* 3 segments */
#else
    param->flash_addr[1] = flash_addr + upg_head->common.section_offset +
                          sizeof(hi_upg_section_head) + sizeof(hi_upg_sign);
    param->total_size[1] = upg_head->common.section_len - sizeof(hi_upg_section_head) - sizeof(hi_upg_sign);
    param->flash_flag[1] = HI_TRUE;
    param->buffer_count = 2; /* 2 segments */
#endif
}

hi_u32 boot_upg_secure_verify_code(hi_u32 flash_addr, HI_CONST hi_upg_head *upg_head)
{
    hi_u32 cs;
    hi_u32 ret = HI_ERR_UPG_MALLOC_FAIL;
    hi_u8 *key2 = HI_NULL;
    hi_u8 *section_sign = boot_malloc(sizeof(hi_upg_sign));
    if (section_sign == HI_NULL) {
        boot_msg0("[upg verify code]malloc fail.");
        goto end;
    }
    ret = hi_flash_read((flash_addr + upg_head->common.section_offset + sizeof(hi_upg_section_head)),
                        sizeof(hi_upg_sign), (hi_u8 *)section_sign);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    hi_u32 key_length = (upg_head->common.param.sign_alg == HI_MODE_ECC)? ECC_256_LEN : RSA_2048_LEN;
    key2 = boot_malloc(key_length);
    if (key2 == HI_NULL) {
        boot_msg0("[upg verify code]malloc fail.");
        goto end;
    }
    cs = (uintptr_t)key2 ^ key_length ^ 0 ^ key_length;
    memset_s(key2, key_length, 0, key_length, cs);
    (hi_void) boot_upg_set_key(upg_head, key2, key_length);

    upg_verify_param param = { 0 };
    boot_upg_set_secure_verify_param(&param, flash_addr, upg_head);
    param.key_n = (hi_u8 *)upg_head + sizeof(hi_upg_common_head);
    param.key_e = key2;
    param.key_len = key_length;
    param.sign = section_sign;
    param.pad_mode = (hi_padding_mode)upg_head->common.param.sign_alg;
    ret = boot_upg_secure_verify(&param);
    upg_clear_content((hi_u8 *)key2, key_length);

end:
    boot_upg_mem_free(section_sign);
    boot_upg_mem_free(key2);
    return ret;
}

hi_u32 boot_upg_unsecure_verify_code(hi_u32 flash_addr, HI_CONST hi_upg_head *upg_head)
{
    hi_u32 ret = HI_ERR_UPG_MALLOC_FAIL;
    hi_u8 *section_sign = boot_malloc(sizeof(hi_upg_sign));
    if (section_sign == HI_NULL) {
        boot_msg0("[upg unsecure verify code]malloc fail.");
        goto end;
    }
    ret = hi_flash_read((flash_addr + upg_head->common.section_offset + sizeof(hi_upg_section_head)),
                        sizeof(hi_upg_sign), (hi_u8 *)section_sign);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    upg_verify_param param = { 0 };
    param.flash_addr[0] = (uintptr_t)flash_addr + upg_head->common.section_offset;
    param.total_size[0] = sizeof(hi_upg_section_head);
    param.flash_flag[0] = HI_TRUE;

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
    param.flash_addr[1] = KERNEL_RAM_ADDR;
    param.total_size[1] = CRYPTO_KERNEL_LENGTH;
    param.flash_flag[1] = HI_FALSE;
    param.flash_addr[2] = flash_addr + upg_head->common.section_offset +
                          sizeof(hi_upg_section_head) + sizeof(hi_upg_sign) + CRYPTO_KERNEL_LENGTH;
    param.total_size[2] = upg_head->common.section_len - sizeof(hi_upg_section_head) - sizeof(hi_upg_sign) -
                          CRYPTO_KERNEL_LENGTH;
    param.flash_flag[2] = HI_TRUE;
    param.buffer_count = 3; /* 3 segments */
#else
    param.flash_addr[1] = flash_addr + upg_head->common.section_offset +
                          sizeof(hi_upg_section_head) + sizeof(hi_upg_sign);
    param.total_size[1] = upg_head->common.section_len - sizeof(hi_upg_section_head) - sizeof(hi_upg_sign);
    param.flash_flag[1] = HI_TRUE;
    param.buffer_count = 2; /* 2 segments */
#endif
    param.key_n = (hi_u8 *)upg_head + sizeof(hi_upg_common_head);
    param.key_e = HI_NULL;
    param.key_len = 0;
    param.sign = section_sign;
    param.pad_mode = (hi_padding_mode)upg_head->common.param.sign_alg;
    ret = boot_upg_secure_verify(&param);
end:
    boot_upg_mem_free(section_sign);

    return ret;
}

hi_u32 boot_upg_secure_verify_head(hi_upg_head *upg_head)
{
    hi_upg_common_head *head = &(upg_head->common);
    hi_u32 ret = HI_ERR_UPG_MALLOC_FAIL;
    hi_u32 cs;
    hi_u32 key_length = (head->param.sign_alg < HI_MODE_ECC) ? RSA_2048_LEN : ECC_256_LEN;
    hi_u8 *key1 = boot_malloc(key_length);
    hi_u8 *key2 = boot_malloc(key_length);
    if ((key1 == HI_NULL) || (key2 == HI_NULL)) {
        boot_msg0("[upg verify head]malloc fail.");
        goto end;
    }
    cs = (uintptr_t)key1 ^ key_length ^ 0 ^ key_length;
    memset_s(key1, key_length, 0, key_length, cs);
    cs = (uintptr_t)key2 ^ key_length ^ 0 ^ key_length;
    memset_s(key2, key_length, 0, key_length, cs);
    ret = boot_upg_secure_get_key_part1(head->param.sign_alg, key1, key_length);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }
    ret = boot_upg_secure_get_key_part2(head->param.sign_alg, key2, key_length);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    upg_verify_param param = { 0 };
    param.flash_addr[0] = (uintptr_t)upg_head;
    param.total_size[0] = sizeof(hi_upg_common_head) + head->key_len;
    param.buffer_count = 1; /* 1 segments */
    param.key_n = key1;
    param.key_e = key2;
    param.key_len = key_length;
    param.sign = (hi_u8 *)upg_head + sizeof(hi_upg_common_head) + head->key_len;
    param.pad_mode = (hi_padding_mode)head->param.sign_alg;
    ret = boot_upg_secure_verify(&param);
end:
    upg_clear_content((hi_u8 *)key1, key_length);
    upg_clear_content((hi_u8 *)key2, key_length);
    boot_upg_mem_free(key1);
    boot_upg_mem_free(key2);
    return ret;
}

hi_u32 boot_upg_unsecure_verify_head(hi_upg_head *upg_head)
{
    hi_upg_common_head *head = &(upg_head->common);
    upg_verify_param param = { 0 };

    param.flash_addr[0] = (uintptr_t)upg_head;
    param.total_size[0] = sizeof(hi_upg_common_head) + head->key_len;
    param.buffer_count = 1; /* 1 segments */
    param.key_n = HI_NULL;
    param.key_e = HI_NULL;
    param.key_len = 0;
    param.sign = (hi_u8 *)upg_head + sizeof(hi_upg_common_head) + head->key_len;
    param.pad_mode = (hi_padding_mode)head->param.sign_alg;
    hi_u32 ret = boot_upg_secure_verify(&param);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[upg unsecure verify head]ret:0x%x", ret);
    }
    return ret;
}

hi_u32 boot_upg_check_secure_info(hi_u32 flash_addr, hi_upg_head *upg_head)
{
    hi_u32 ret = boot_upg_secure_verify_head(upg_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[upg check secure info]head,ret:", ret);
        return ret;
    }
    ret = boot_upg_secure_verify_code(flash_addr, upg_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[upg check secure info]code,ret:", ret);
        return ret;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 boot_upg_check_unsecure_info(hi_u32 flash_addr, hi_upg_head *upg_head)
{
    hi_u32 ret = boot_upg_unsecure_verify_head(upg_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[upg check unsecure info]head,ret:", ret);
        return ret;
    }
    ret = boot_upg_unsecure_verify_code(flash_addr, upg_head);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[upg check unsecure info]code,ret:", ret);
        return ret;
    }

    return HI_ERR_SUCCESS;
}

