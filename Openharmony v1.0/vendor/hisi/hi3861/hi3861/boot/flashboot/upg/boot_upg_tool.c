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

#include "boot_upg_tool.h"

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
#include <crypto.h>
#endif

hi_u8 g_upg_tool_block[HI_BLOCK_SIZE];
static hi_u32 g_compress_src_addr = 0;
static hi_u32 g_compress_dst_addr = 0;

hi_u32 kernel_comprss_flash_read(hi_u32 offset, hi_u8 *buffer, hi_u32 size)
{
    hi_u32 ret;
#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
    ret = crypto_kernel_read(g_compress_src_addr, offset, buffer, size);
    if (ret == HI_ERR_SUCCESS) {
        ret = 0;
    }
#else
    ret = hi_flash_read(g_compress_src_addr + offset, size, buffer);
    if (ret == HI_ERR_SUCCESS) {
        ret = 0;
    }
#endif

    return ret;
}

hi_u32 kernel_comprss_flash_write(hi_u32 offset, hi_u8 *buffer, hi_u32 size)
{
    hi_u32 ret;
    hi_u32 tmp_size = size + 1;

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
    ret = crypto_kernel_write(g_compress_dst_addr, offset, buffer, size);
    if (ret != HI_ERR_SUCCESS) {
        return tmp_size;
    }
#else
    ret = hi_flash_write(g_compress_dst_addr + offset, size, buffer, HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        return tmp_size;
    }
#endif
    return size;
}

hi_u32 kernel_comprss_flash_hash(hi_u32 offset, hi_u8 *buffer, hi_u32 size)
{
    hi_u32 cs;
    hi_u32 ret = HI_ERR_SUCCESS;
    hi_u32 hash_size = size + 1;

    if (offset >= sizeof(hi_upg_file_head)) {
        ret = hi_cipher_hash_update((uintptr_t)buffer, size);
        if (ret == HI_ERR_SUCCESS) {
            hash_size = size;
        } else {
            boot_msg4("code hash ret-size-offset-headsize", ret, size, offset, hash_size);
        }
        return hash_size;
    }

    /* offset less than sizeof(hi_upg_file_head) */
    if ((offset + size) > sizeof(hi_upg_file_head)) {
        hi_u32 cy_size = sizeof(hi_upg_file_head) - offset;
        cs = (uintptr_t)(g_compress_dst_addr + offset) ^ cy_size ^ (uintptr_t)buffer ^ cy_size;
        (hi_void) memcpy_s((hi_void *)(uintptr_t)(g_compress_dst_addr + offset), cy_size, buffer, cy_size, cs);

        /* Cal hash of common section head */
        ret = hi_cipher_hash_update((uintptr_t)(g_compress_dst_addr + sizeof(hi_upg_head)),
                                    sizeof(hi_upg_section_head));
        if (ret != HI_ERR_SUCCESS) {
            boot_msg4("head hash updata ret-size-offset-hashsize", ret, size, offset, hash_size);
            return hash_size;
        }
        /* Cal hash of common section */
        ret = hi_cipher_hash_update((uintptr_t)(buffer + cy_size), (size - cy_size));
    } else {
        cs = (uintptr_t)(g_compress_dst_addr + offset) ^ size ^ (uintptr_t)buffer ^ size;
        (hi_void) memcpy_s((hi_void *)(uintptr_t)(g_compress_dst_addr + offset), size, buffer, size, cs);
    }
    if (ret == HI_ERR_SUCCESS) {
        hash_size = size;
    } else {
        boot_msg4("code head hash ret-size-offset-hashsize", ret, size, offset, hash_size);
    }
    return hash_size;
}

hi_u32 boot_upg_copy_flash_2_flash(hi_u32 src_addr, hi_u32 src_size, hi_u32 dst_addr, hi_u32 dst_size, hi_bool comprss)
{
    hi_u8 lzma_head[13] = { 0 }; /* head 13B */
    hi_u32 ret = HI_ERR_UPG_PARAMETER;

    if (!comprss) {
        boot_msg0("Not support uncompressed file.");
        return ret;
    } else {
        boot_msg4("src-size-dst-size", src_addr, src_size, dst_addr, dst_size);
        hi_flash_read(src_addr, 13, lzma_head); /* read 13B */
        g_compress_src_addr = src_addr;
        g_compress_dst_addr = dst_addr;
        ret = hi_lzma_decompress(lzma_head, sizeof(lzma_head), src_size, kernel_comprss_flash_read,
                                 kernel_comprss_flash_write);
    }
    return ret;
}

hi_u32 boot_upg_hash_one_content(hi_u32 flash_addr, hi_u32 total_size, hi_u8 *hash, hi_u32 hash_size)
{
    hi_u32 ret;
    hi_u8 *block = g_upg_tool_block;

    ret = hi_cipher_hash_start();
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[bootupg hash one content]start ret:", ret);
        return ret;
    }

    for (uintptr_t offset = 0; offset < total_size;) {
        uintptr_t this_size = (total_size - offset > HI_BLOCK_SIZE) ? HI_BLOCK_SIZE : (total_size - offset);
        ret = hi_flash_read(flash_addr + offset, this_size, block);
        if (ret != HI_ERR_SUCCESS) {
            (hi_void) hi_cipher_hash_final(hash, hash_size);
            return ret;
        }

        ret = hi_cipher_hash_update((uintptr_t)block, this_size);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg1("[bootupg hash one content]update ret:", ret);
            return ret;
        }
        offset += this_size;
    }
    return hi_cipher_hash_final(hash, hash_size);
}

hi_u32 boot_upg_hash_more_content(HI_CONST upg_verify_param *param, hi_u8 *hash, hi_u32 hash_size)
{
    hi_u32 cs;
    hi_u8 *block = g_upg_tool_block;

    hi_u32 ret = hi_cipher_hash_start();
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[bootupg hash more content]cipher start ret:", ret);
        return ret;
    }

    for (hi_u8 i = 0; i < param->buffer_count; i++) {
        uintptr_t size = param->total_size[i];
        for (uintptr_t offset = 0; offset < size;) {
            uintptr_t this_size = ((size - offset) > HI_BLOCK_SIZE) ? HI_BLOCK_SIZE : (size - offset);
            if (param->flash_flag[i]) {
                ret = hi_flash_read(param->flash_addr[i] + offset, this_size, block);
            } else {
                cs = (uintptr_t)block ^ HI_BLOCK_SIZE ^ (uintptr_t)(param->flash_addr[i] + offset) ^ this_size;
                ret = (hi_u32)memcpy_s(block, HI_BLOCK_SIZE, (hi_u8 *)(param->flash_addr[i] + offset), this_size, cs);
            }
            if (ret != HI_ERR_SUCCESS) {
                (hi_void) hi_cipher_hash_final(hash, hash_size);
                return ret;
            }

            ret = hi_cipher_hash_update((uintptr_t)block, this_size);
            if (ret != HI_ERR_SUCCESS) {
                boot_msg1("[bootupg hash more content]hash update ret: ", ret);
                return ret;
            }
            offset += this_size;
        }
    }
    return hi_cipher_hash_final(hash, hash_size);
}

hi_u32 boot_upg_lzma_secure_verify(const upg_verify_param *param, hi_u8 *hash, hi_u32 hash_size)
{
    hi_u8 out_hash[SHA_256_LEN] = { 0 };
    hi_u32 ret;

    if (hash_size != SHA_256_LEN) {
        return HI_ERR_UPG_PARAMETER;
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

hi_u32 boot_upg_lzma_secure_verify_code(const hi_upg_file_head *upg_head, hi_u8 *hash, hi_u32 hash_size)
{
    hi_u32 cs;
    hi_u32 ret;
    hi_u32 key_length = (upg_head->common.param.sign_alg == HI_MODE_ECC) ? ECC_256_LEN : RSA_2048_LEN;
    hi_u32 key2_offset = sizeof(hi_upg_common_head) + key_length;
    hi_u8 *key_e = g_upg_tool_block;

    if (key_length > HI_BLOCK_SIZE) {
        boot_msg1("[bootupg lzma verify code]key size", key_length);
        return HI_ERR_UPG_PARAMETER;
    }
    cs = (uintptr_t)key_e ^ HI_BLOCK_SIZE ^ 0 ^ HI_BLOCK_SIZE;
    memset_s(key_e, HI_BLOCK_SIZE, 0, HI_BLOCK_SIZE, cs);

    if (upg_head->common.param.sign_alg == HI_MODE_ECC) {
        cs = (uintptr_t)key_e ^ ECC_256_LEN ^ (uintptr_t)((hi_u8 *)upg_head + key2_offset) ^ ECC_256_LEN;
        (hi_void) memcpy_s(key_e, key_length, (hi_u8 *)upg_head + key2_offset, ECC_256_LEN, cs);
    } else {
        cs = (uintptr_t)(key_e + key_length - RSA_EXP_E_LEN) ^ RSA_EXP_E_LEN ^
            (uintptr_t)((hi_u8 *)upg_head + key2_offset) ^ RSA_EXP_E_LEN;
        (hi_void)memcpy_s(key_e + key_length - RSA_EXP_E_LEN, RSA_EXP_E_LEN,
                          (hi_u8 *)upg_head + key2_offset, RSA_EXP_E_LEN, cs);
    }

    upg_verify_param param = { 0 };
    param.key_n = (hi_u8 *)upg_head + sizeof(hi_upg_common_head);
    param.key_e = key_e;
    param.key_len = key_length;
    param.sign = (hi_u8 *)upg_head + sizeof(hi_upg_head) + sizeof(hi_upg_section_head);
    param.pad_mode = (hi_padding_mode)upg_head->common.param.sign_alg;
    ret = boot_upg_lzma_secure_verify(&param, hash, hash_size);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[bootupg lzma verify code]ret", ret);
    }
    return ret;
}

hi_u32 boot_upg_lzma_unsecure_verify_code(const hi_upg_file_head *upg_head, hi_u8 *hash, hi_u32 hash_size)
{
    if (hash_size != SHA_256_LEN) {
        return HI_ERR_UPG_PARAMETER;
    }

    if (memcmp((hi_u8 *)upg_head + sizeof(hi_upg_head) + sizeof(hi_upg_section_head), hash, hash_size) != EOK) {
        return HI_ERR_UPG_SECTION_SHA256;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 boot_upg_check_before_decompress(hi_u32 addr_write, const hi_upg_section_head *section_head,
                                        const hi_upg_file_head *file_head)
{
    hi_u8 lzma_head[13] = { 0 }; /* head 13B */
    hi_u32 ret;
    hi_u8 hash[SHA_256_LEN] = { 0 };

    hi_flash_read(addr_write + section_head->section0_offset, 13, lzma_head); /* read 13B */
    g_compress_src_addr = addr_write + section_head->section0_offset;
    g_compress_dst_addr = (hi_u32)(uintptr_t)file_head;

    ret = hi_cipher_hash_start();
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[bootupg before decompress]hash start fail", ret);
        return ret;
    }
    ret = hi_lzma_decompress(lzma_head, sizeof(lzma_head), section_head->section0_len, kernel_comprss_flash_read,
                             kernel_comprss_flash_hash);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[bootupg before decompress]decompress fail", ret);
        return ret;
    }
    (hi_void)hi_cipher_hash_final(hash, SHA_256_LEN);

    /* verify common & code section */
    hi_upg_head *common_section = (hi_upg_head *)(uintptr_t)g_compress_dst_addr;
    if (boot_upg_is_secure_efuse() == HI_TRUE) {
        ret = boot_upg_secure_verify_head(common_section);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg1("[bootupg before decompress]verify head hash ret", ret);
            return ret;
        }
        ret = boot_upg_lzma_secure_verify_code(file_head, hash, SHA_256_LEN);
    } else {
        ret = boot_upg_unsecure_verify_head(common_section);
        if (ret != HI_ERR_SUCCESS) {
            boot_msg1("[bootupg before decompress]verify head sha256 ret", ret);
            return ret;
        }
        ret = boot_upg_lzma_unsecure_verify_code(file_head, hash, SHA_256_LEN);
    }

    if (ret != HI_ERR_SUCCESS) {
        boot_msg1("[bootupg before decompress]verfiy code fail", ret);
    }
    return ret;
}

