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

#include <upg_check_boot_bin.h>
#include <upg_check_secure.h>
#include <hi_cipher.h>
#include <upg_common.h>

hi_u32 upg_check_boot_root_pub_key(HI_CONST boot_header *head, HI_CONST hi_u8 *pubk, hi_u32 pubk_len)
{
    hi_u8 hash[SHA_256_LENGTH];
    hi_u8 efuse_hash[SHA_256_LENGTH];

    if ((head == HI_NULL) || (pubk == HI_NULL)) {
        return HI_ERR_UPG_NULL_POINTER;
    }

    if (head->root_pubk_length != pubk_len) {
        return HI_ERR_UPG_BOOT_ROOT_KEY_LEN;
    }

    (hi_void) memset_s(hash, SHA_256_LENGTH, 0, SHA_256_LENGTH);
    hi_u32 ret = hi_cipher_hash_sha256((uintptr_t)pubk, pubk_len, hash, sizeof(hash));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    (hi_void) memset_s(efuse_hash, SHA_256_LENGTH, 0, SHA_256_LENGTH);
    ret = hi_efuse_read(HI_EFUSE_ROOT_PUBKEY_RW_ID, efuse_hash, SHA_256_LENGTH);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (memcmp(hash, efuse_hash, SHA_256_LENGTH) != EOK) {
        ret = HI_ERR_UPG_BOOT_ROOT_KEY;
    }

    return ret;
}

hi_u32 upg_check_die_id(HI_CONST hi_void *sub_key_data)
{
    hi_u8 die_id[DIE_ID_LENGTH] = { 0 };
    hi_u32 ret = HI_ERR_SUCCESS;
    sub_key_common *sub_key = (sub_key_common *)sub_key_data;

    if (sub_key->key_type == MAINTENANCE_KEY_TPYE) {
        ret = hi_efuse_read(HI_EFUSE_DIE_RW_ID, (hi_u8 *)die_id, (hi_u8)sizeof(die_id));
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }

        if (memcmp(sub_key->die_id, die_id, DIE_ID_LENGTH) != EOK) {
            return HI_ERR_UPG_BOOT_DIE_ID;
        }
    }
    return ret;
}

hi_u32 upg_check_boot_subk_attr(HI_CONST hi_void *key, hi_u32 alg)
{
    hi_u32 category = (hi_u32)(-1);
    hi_u32 rsim = (hi_u32)(-1);
    hi_u32 ret = hi_efuse_read(HI_EFUSE_SUBKEY_CAT_RW_ID, (hi_u8 *)(&category), sizeof(hi_u32));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }
    sub_key_common *sub_key_com = (sub_key_common *)key;
    if (sub_key_com->category != category) {
        return HI_ERR_UPG_BOOT_SUB_KEY_CAT;
    }
    ret = hi_efuse_read(HI_EFUSE_SUBKEY_RSIM_RW_ID, (hi_u8 *)&rsim, SUBKEY_RSIM_BYTES);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if ((sub_key_com->key_id > SUBKEY_ID_MAX) || (((rsim >> sub_key_com->key_id) & 1) == 1)) {
        return HI_ERR_UPG_BOOT_SUB_KEY_RSIM;
    }

    if (alg == SIGN_ALG_ECC) {
        sub_ecc_key *sub_key = (sub_ecc_key *)key;
        if ((sub_key->sign_alg.hash_alg != HI_HASH_ALG_SHA256) ||
            (sub_key->sign_alg.sign_alg != SIGN_ALG_ECC) ||
            (sub_key->subkey_length != ECC_64_BYTES)) {
            return HI_ERR_UPG_BOOT_SIGN_ALG;
        }
    } else {
        sub_rsa_key *sub_key = (sub_rsa_key *)key;
        if ((sub_key->sign_alg.hash_alg != HI_HASH_ALG_SHA256) ||
            (sub_key->sign_alg.sign_alg > SIGN_ALG_RSA_PSS) ||
            (sub_key->subkey_length != (RSA_2048_LENGTH + RSA_EXP_E_LENGTH))) {
            return HI_ERR_UPG_BOOT_SIGN_ALG;
        }
    }
    ret = upg_check_die_id(key);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check boot subk attr] die id err:0x%x \r\n", ret);
    }

    return ret;
}

hi_u32 upg_check_boot_sub_key_cpy(const root_rsa_pub_key *root_key, hi_u8 *exp_e)
{
    if (memset_s(exp_e, RSA_4096_LENGTH, 0, RSA_4096_LENGTH) != EOK) {
        return HI_ERR_FAILURE;
    }
    if (memcpy_s((exp_e + RSA_4096_LENGTH - RSA_EXP_E_LENGTH), RSA_EXP_E_LENGTH, root_key->exp_e, RSA_EXP_E_LENGTH)
        != EOK) {
        return HI_ERR_FAILURE;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 upg_check_boot_sub_key(HI_CONST hi_u8 *pubk, HI_CONST hi_u8 *subk, hi_u32 alg)
{
    hi_u8 hash[SHA_256_LENGTH] = { 0 };
    hi_u32 ret = upg_check_boot_subk_attr(subk, alg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check boot sub key]attr err:0x%x \r\n", ret);
        return ret;
    }

    if (alg == SIGN_ALG_ECC) {
        sub_ecc_key *sub_key = (sub_ecc_key *)subk;
        root_ecc_pub_key *root_key = (root_ecc_pub_key *)pubk;
        ret = hi_cipher_hash_sha256((uintptr_t)sub_key, sizeof(sub_ecc_key) - ECC_64_BYTES, hash, sizeof(hash));
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[upg check bootbin]hash ecc key hash err:0x%x \r\n", ret);
            return ret;
        }

        hi_cipher_ecc_verify ecc_verify = {
            .px = root_key->px,
            .py = root_key->py,
            .hash = hash,
            .hash_len = PKE_LEN_32_BYTES,
            .r = sub_key->r,
            .s = sub_key->s,
        };
        ret = hi_cipher_ecc_verify_hash(&g_brain_pool_p256r1_verify, &ecc_verify);
    } else {
        sub_rsa_key *sub_key = (sub_rsa_key *)subk;
        root_rsa_pub_key *root_key = (root_rsa_pub_key *)pubk;
        ret = hi_cipher_hash_sha256((uintptr_t)sub_key, sizeof(sub_rsa_key) - RSA_4096_LENGTH, hash, sizeof(hash));
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        hi_u8 *exp_e = hi_malloc(HI_MOD_ID_UPG, RSA_4096_LENGTH);
        if (exp_e == HI_NULL) {
            return HI_ERR_UPG_MALLOC_FAIL;
        }

        if (upg_check_boot_sub_key_cpy(root_key, exp_e) != HI_ERR_SUCCESS) {
            hi_free(HI_MOD_ID_UPG, exp_e);
            return HI_ERR_FAILURE;
        }

        hi_cipher_rsa_verify rsa_verify;
        rsa_verify.n = root_key->mod_n;
        rsa_verify.e = exp_e;
        rsa_verify.klen = RSA_4096_LENGTH;
        rsa_verify.scheme = (hi_cipher_rsa_sign_scheme)(sub_key->sign_alg.sign_alg);

        ret = hi_cipher_rsa_verify_hash(&rsa_verify, hash, PKE_LEN_32_BYTES, sub_key->sign, RSA_4096_LENGTH);
        hi_free(HI_MOD_ID_UPG, exp_e);
    }
    return ((ret == HI_ERR_FAILURE) ? HI_ERR_UPG_BOOT_SUB_KEY_HASH : ret);
}

/* data: total boot bin. data_len: length of boot bin. */
hi_u32 upg_boot_decrypt(hi_u8 *data, hi_u32 data_len)
{
    hi_u8 rootkey_iv[ROOTKEY_IV_BYTE_LENGTH] = { 0 };
    boot_header *head = (boot_header *)data;
    hi_u32 ret = HI_ERR_FAILURE;

    if ((head == HI_NULL) || (data_len != (head->sign_offset + head->sign_length + sizeof(boot_tail)))) {
        return HI_ERR_UPG_PARAMETER;
    }

    hi_u32 decrypt_addr = (hi_u32)(uintptr_t)data + head->code_section_offset;
    sub_key_common *sub_key_com = (sub_key_common *)(data + head->sub_key_offset);
    hi_cipher_kdf_ctrl *ctrl = hi_malloc(HI_MOD_ID_UPG, sizeof(hi_cipher_kdf_ctrl));
    hi_cipher_aes_ctrl *aes_ctrl = hi_malloc(HI_MOD_ID_UPG, sizeof(hi_cipher_aes_ctrl));
    if ((ctrl == HI_NULL) || (aes_ctrl == HI_NULL)) {
        goto end;
    }

    memset_s(ctrl, sizeof(hi_cipher_kdf_ctrl), 0, sizeof(hi_cipher_kdf_ctrl));
    memset_s(aes_ctrl, sizeof(hi_cipher_aes_ctrl), 0, sizeof(hi_cipher_aes_ctrl));
    if ((memcpy_s(rootkey_iv, sizeof(rootkey_iv), sub_key_com->boot_key, IV_BYTE_LEN) != EOK) ||
        (memcpy_s((rootkey_iv + IV_BYTE_LEN), sizeof(rootkey_iv) - IV_BYTE_LEN, g_magic, IV_BYTE_LEN) != EOK)) {
        goto end;
    }

    ctrl->salt = rootkey_iv;
    ctrl->salt_len = ROOTKEY_IV_BYTE_LENGTH;
    ctrl->kdf_cnt = KDF_ITERATION_CNT;
    ctrl->kdf_mode = HI_CIPHER_SSS_KDF_KEY_STORAGE;
    ret = hi_cipher_kdf_key_derive(ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }
    if (memcpy_s(aes_ctrl->iv, sizeof(aes_ctrl->iv), sub_key_com->aes_iv, IV_BYTE_LEN) != EOK) {
        goto end;
    }
    aes_ctrl->random_en = HI_TRUE;
    aes_ctrl->key_from = HI_CIPHER_AES_KEY_FROM_KDF;
    aes_ctrl->work_mode = HI_CIPHER_AES_WORK_MODE_CBC;
    aes_ctrl->key_len = HI_CIPHER_AES_KEY_LENGTH_256BIT;
    ret = hi_cipher_aes_config(aes_ctrl);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }
    ret = hi_cipher_aes_crypto(decrypt_addr, decrypt_addr, head->code_section_length, HI_FALSE);
    (hi_void) hi_cipher_aes_destroy_config();
end:
    upg_clear_contset((hi_u8 *)ctrl, sizeof(hi_cipher_kdf_ctrl));
    upg_clear_contset((hi_u8 *)aes_ctrl, sizeof(hi_cipher_aes_ctrl));
    upg_mem_free(ctrl);
    upg_mem_free(aes_ctrl);
    return ret;
}

hi_u32 upg_check_boot_from_mem(hi_u8 *data, hi_u32 data_len, hi_u8 *key_part1, hi_u8 *key_part2)
{
    hi_u32 ret;
    hi_u8 hash[SHA_256_LENGTH] = { 0 };
    boot_header *head = HI_NULL;
    hi_u8 *signature = HI_NULL;

    head = (boot_header *)data;
    if (data_len != (head->sign_offset + head->sign_length + sizeof(boot_tail))) {
        return HI_ERR_UPG_BOOT_LEN;
    }
    ret = hi_cipher_hash_sha256((uintptr_t)data, (head->code_section_offset + head->code_section_length),
                                hash, sizeof(hash));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check boot code]sha256 err:0x%x \r\n", ret);
        return ret;
    }

    signature = data + head->sign_offset;
    if (head->sign_alg.sign_alg == SIGN_ALG_ECC) {
        hi_cipher_ecc_verify ecc_verify = {
            .px = key_part1,
            .py = key_part2,
            .hash = hash,
            .hash_len = PKE_LEN_32_BYTES,
            .r = signature,
            .s = signature + ECC_32_BYTES,
        };
        ret = hi_cipher_ecc_verify_hash(&g_brain_pool_p256r1_verify, &ecc_verify);
    } else {
        hi_cipher_rsa_verify rsa_verify = {
            .n = key_part1,
            .e = key_part2,
            .klen = RSA_2048_LENGTH,
            .scheme = (hi_cipher_rsa_sign_scheme)(head->sign_alg.sign_alg),
        };
        ret = hi_cipher_rsa_verify_hash(&rsa_verify, hash, PKE_LEN_32_BYTES, signature, head->sign_length);
    }
    ret = ((ret == HI_ERR_FAILURE) ? HI_ERR_UPG_BOOT_SECTION_HASH : ret);
    upg_print("[upg check boot code]verify ret:0x%x \r\n", ret);
    return ret;
}

/* boot_addr:flashboot bin addr without ota head. boot_len: total len. */
hi_u32 upg_check_encrpt_boot_code(hi_u32 boot_addr, hi_u32 boot_len, hi_u8 *key_part1, hi_u8 *key_part2)
{
    upg_print("[upg check encrpt boot]addr-len:0x%x-0x%x \r\n", boot_addr, boot_len);
    hi_u8 *boot = hi_malloc(HI_MOD_ID_UPG, boot_len);
    if (boot == HI_NULL) {
        upg_print("[upg check encrpt boot]malloc fail,boot_len:0x%x \r\n", boot_len);
        return HI_ERR_UPG_MALLOC_FAIL;
    }

    hi_u32 ret = hi_flash_read(boot_addr, boot_len, boot);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check encrpt boot]flash read err:0x%x \r\n", ret);
        goto end;
    }
    /* decrypt data */
    ret = upg_boot_decrypt(boot, boot_len);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check encrpt boot]decrypt ret:0x%x \r\n", ret);
        goto end;
    }

    ret = upg_check_boot_from_mem(boot, boot_len, key_part1, key_part2);
end:
    upg_mem_free(boot);
    return ret;
}

/* addr:flashboot bin addr without ota head. */
hi_u32 upg_check_unencrpt_boot_code(hi_u32 addr, HI_CONST boot_header *head, hi_u8 *key_part1, hi_u8 *key_part2)
{
    hi_u8 hash[SHA_256_LENGTH] = { 0 };

    if (head->sign_length == 0) {
        return HI_ERR_UPG_PARAMETER;
    }
    hi_u32 ret = upg_hash_one_content(addr, (head->code_section_offset + head->code_section_length),
                                      hash, sizeof(hash));
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    hi_u8 *signature = hi_malloc(HI_MOD_ID_UPG, head->sign_length);
    if (signature == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }

    ret = hi_flash_read(addr + head->sign_offset, head->sign_length, signature);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    if (head->sign_alg.sign_alg == SIGN_ALG_ECC) {
        hi_cipher_ecc_verify ecc_verify = {
            .px = key_part1,
            .py = key_part2,
            .hash = hash,
            .hash_len = PKE_LEN_32_BYTES,
            .r = signature,
            .s = signature + ECC_32_BYTES,
        };
        ret = hi_cipher_ecc_verify_hash(&g_brain_pool_p256r1_verify, &ecc_verify);
    } else {
        hi_cipher_rsa_verify rsa_verify = {
            .n = key_part1,
            .e = key_part2,
            .klen = RSA_2048_LENGTH,
            .scheme = (hi_cipher_rsa_sign_scheme)(head->sign_alg.sign_alg),
        };
        ret = hi_cipher_rsa_verify_hash(&rsa_verify, hash, PKE_LEN_32_BYTES, signature, head->sign_length);
    }
    ret = ((ret == HI_ERR_FAILURE) ? HI_ERR_UPG_BOOT_SECTION_HASH : ret);
    upg_print("[upg check unencrpt boot code]alg-ret:0x%x-0x%x \r\n", head->sign_alg.sign_alg, ret);
end:
    upg_mem_free(signature);
    return ret;
}

/* addr:flashboot bin addr without ota head. */
hi_u32 upg_verify_flashboot(hi_u32 addr, HI_CONST boot_header *head, hi_u8 *key_part1,
                            hi_u8 *key_part2, const sub_key_common *subk_com)
{
    hi_u8 encrypt_flag = 0xFF;
    hi_u32 ret = hi_efuse_read(HI_EFUSE_ENCRYPT_FLAG_RW_ID, (hi_u8 *)(&encrypt_flag), sizeof(hi_u8));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg verify flashboot]efuse read err:0x%x \r\n", ret);
        return ret;
    }

    if ((encrypt_flag == NON_ENCRYPT_FLAG) && (subk_com->encrypt_flag == NON_ENCRYPT_FLAG)) {
        ret = upg_check_unencrpt_boot_code(addr, head, key_part1, key_part2);
    } else {
        ret = upg_check_encrpt_boot_code(addr, (head->sign_offset + head->sign_length + sizeof(boot_tail)),
                                         key_part1, key_part2);
    }
    upg_print("[upg verify flashboot]ret-efuse-fileflag:0x%x-0x%x-0x%x \r\n", ret, encrypt_flag,
              subk_com->encrypt_flag);
    return ret;
}

hi_u32 upg_get_boot_sign_key(HI_CONST boot_header *head, HI_CONST hi_u8 *key, hi_u8 **pubk1,
                             hi_u8 *pubk2, hi_u32 pubk2_len)
{
    if ((head == HI_NULL) || (key == HI_NULL) || (pubk1 == HI_NULL) || (pubk2 == HI_NULL)) {
        return HI_ERR_UPG_NULL_POINTER;
    }

    if (head->root_pubk_alg < SIGN_ALG_ECC) {
        sub_rsa_key *sub_key = (sub_rsa_key *)key;
        if (pubk2_len != RSA_2048_LENGTH) {
            return HI_ERR_UPG_PARAMETER;
        }
        *pubk1 = sub_key->mod_n;
        if (memcpy_s((pubk2 + RSA_2048_LENGTH - RSA_EXP_E_LENGTH), RSA_EXP_E_LENGTH,
            sub_key->exp_e, RSA_EXP_E_LENGTH) != EOK) {
            return HI_ERR_FAILURE;
        }
    } else {
        sub_ecc_key *sub_key = (sub_ecc_key *)key;
        if (pubk2_len != ECC_32_BYTES) {
            return HI_ERR_UPG_PARAMETER;
        }
        *pubk1 = sub_key->px;
        if (memcpy_s(pubk2, ECC_32_BYTES, sub_key->py, ECC_32_BYTES) != EOK) {
            return HI_ERR_FAILURE;
        }
    }

    return HI_ERR_SUCCESS;
}

/* boot_addr:flashboot bin addr without ota head. verify_len: from head to sign(not include). */
hi_u32 upg_check_non_secure_boot_bin(hi_u32 boot_addr, hi_u32 verify_len, hi_u32 sign_addr)
{
    hi_u32 ret;
    hi_u8 *cal_hash = hi_malloc(HI_MOD_ID_UPG, SHA_256_LENGTH);
    hi_u8 *file_hash = hi_malloc(HI_MOD_ID_UPG, SHA_256_LENGTH);
    if ((cal_hash == HI_NULL) || (file_hash == HI_NULL)) {
        ret = HI_ERR_UPG_MALLOC_FAIL;
        goto end;
    }
    memset_s(cal_hash, SHA_256_LENGTH, 0, SHA_256_LENGTH);
    memset_s(file_hash, SHA_256_LENGTH, 0, SHA_256_LENGTH);
    upg_print("[upg_non_secure_boot_bin]addr-verifylen-signaddr:0x%x-0x%x-0x%x \r\n", boot_addr, verify_len,
              sign_addr);
    ret = upg_hash_one_content(boot_addr, verify_len, cal_hash, SHA_256_LENGTH);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }
    ret = hi_flash_read(sign_addr, SHA_256_LENGTH, file_hash);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }
    if (memcmp(cal_hash, file_hash, SHA_256_LENGTH) != EOK) {
        ret = HI_ERR_UPG_BOOT_HASH;
    }
end:
    upg_mem_free(cal_hash);
    upg_mem_free(file_hash);
    return ret;
}

hi_u32 upg_check_boot_bin_key(HI_CONST boot_header *head, HI_CONST hi_u8 *pubk, hi_u32 pubk_len,
                              HI_CONST hi_u8 *subk)
{
    hi_u32 ret = upg_check_boot_root_pub_key(head, pubk, pubk_len);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check boot pub key]fail,ret:0x%x \r\n", ret);
        return ret;
    }

    ret = upg_check_boot_sub_key(pubk, subk, head->root_pubk_alg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check boot sub key]fail,ret:0x%x \r\n", ret)
    }
    return ret;
}

hi_u32 upg_check_boot_get_key_len(HI_CONST boot_header *head, hi_u32 *pubk_len, hi_u32 *subk_len)
{
    if ((head->root_pubk_alg < SIGN_ALG_ECC) && (head->sub_key_length == sizeof(sub_rsa_key))) {
        *pubk_len = sizeof(root_rsa_pub_key);
        *subk_len = sizeof(sub_rsa_key);
        return HI_ERR_SUCCESS;
    }

    if ((head->root_pubk_alg == SIGN_ALG_ECC) && (head->sub_key_length == sizeof(sub_ecc_key))) {
        *pubk_len = sizeof(root_ecc_pub_key);
        *subk_len = sizeof(sub_ecc_key);
        return HI_ERR_SUCCESS;
    }
    return HI_ERR_UPG_BOOT_SUB_KEY_LEN;
}

/* addr:flashboot bin addr without ota head. */
hi_u32 upg_check_secure_boot_bin(hi_u32 addr, HI_CONST boot_header *head)
{
    hi_u8 *pubk1 = HI_NULL;
    hi_u32 pubk_len;
    hi_u32 subk_len;
    hi_u32 puk2_len = RSA_2048_LENGTH;
    hi_u32 ret = upg_check_boot_get_key_len(head, &pubk_len, &subk_len);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (head->root_pubk_alg == SIGN_ALG_ECC) {
        puk2_len = ECC_32_BYTES;
    }
    upg_print("[verify flashboot]pubklen-subklen-puk2len:0x%x-0x%x-0x%x \r\n", pubk_len, subk_len, puk2_len);
    hi_u8 *pubk = hi_malloc(HI_MOD_ID_UPG, pubk_len);
    hi_u8 *subk = hi_malloc(HI_MOD_ID_UPG, subk_len);
    hi_u8 *pubk2 = hi_malloc(HI_MOD_ID_UPG, puk2_len);
    if ((pubk == HI_NULL) || (subk == HI_NULL) || (pubk2 == HI_NULL)) {
        ret = HI_ERR_UPG_MALLOC_FAIL;
        goto end;
    }
    memset_s(pubk2, puk2_len, 0, puk2_len);
    ret = hi_flash_read((addr + head->root_pubk_offset), pubk_len, pubk);
    ret |= hi_flash_read((addr + head->sub_key_offset), subk_len, subk);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    ret = upg_check_boot_bin_key(head, pubk, pubk_len, subk);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    ret = upg_get_boot_sign_key(head, subk, &pubk1, pubk2, puk2_len);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    ret = upg_verify_flashboot(addr, head, pubk1, pubk2, (sub_key_common *)subk);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }
end:
    upg_clear_contset((hi_u8 *)pubk, pubk_len);
    upg_clear_contset((hi_u8 *)subk, subk_len);
    upg_clear_contset((hi_u8 *)pubk2, puk2_len);
    upg_mem_free(pubk);
    upg_mem_free(subk);
    upg_mem_free(pubk2);
    return ret;
}

/* addr:flashboot bin addr(without ota head). len: length of flashboot bin. */
hi_u32 upg_check_boot_file(hi_u32 addr, hi_u32 len)
{
    hi_bool flag;
    hi_unref_param(len);
    hi_u32 ret = upg_is_secure_efuse(&flag);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check boot bin]get secure efuse err:0x%x \r\n", ret);
        return ret;
    }
    upg_print("[upg check boot bin]addr-len:0x%x-0x%x \r\n", addr, len);
    boot_header *head = (boot_header *)hi_malloc(HI_MOD_ID_UPG, sizeof(boot_header));
    if (head == HI_NULL) {
        return HI_ERR_UPG_MALLOC_FAIL;
    }
    ret = hi_flash_read(addr, sizeof(boot_header), (hi_u8 *)head);
    if (ret != HI_ERR_SUCCESS) {
        goto end;
    }

    if ((head->preamble != BOOT_PREAMBLE) || (head->head_magic != BOOT_HEAD_MAGIC)) {
        ret = HI_ERR_UPG_BOOT_HEAD;
        goto end;
    }

    hi_u32 boot_len = head->sign_offset + head->sign_length + sizeof(boot_tail);
    if ((boot_len < BOOT_SECURE_MIN_LEN) || (boot_len > BOOT_MAX_LEN)) {
        ret = HI_ERR_UPG_BOOT_LEN;
        goto end;
    }

    if (flag == HI_TRUE) {
        ret = upg_check_secure_boot_bin(addr, head);
    } else {
        ret = upg_check_non_secure_boot_bin(addr, (head->code_section_offset + head->code_section_length),
                                            addr + head->sign_offset);
    }
end:
    hi_free(HI_MOD_ID_UPG, head);
    return ret;
}
