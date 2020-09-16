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

#include "upg_check_file.h"
#include "upg_check_secure.h"
#include "upg_check_boot_bin.h"
#include "upg_user_verify.h"

hi_u32 upg_check_image_id(hi_u32 image_id)
{
    if (image_id != PRODUCT_UPG_FILE_IMAGE_ID) {
        upg_print("[upg check image id]fail,image id:0x%x \r\n", image_id);
        return HI_ERR_UPG_IMAGE_ID;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 upg_check_file_type(hi_u8 file_type)
{
    if ((file_type == HI_UPG_FILE_KERNEL) || (file_type == HI_UPG_FILE_BOOT)) {
        return HI_ERR_SUCCESS;
    } else {
        upg_print("[upg check file type]fail,file type:0x%x \r\n", file_type);
        return HI_ERR_UPG_FILE_TYPE;
    }
}

hi_bool upg_check_encrypt_info_is_match(hi_u8 encry_info)
{
#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
    if (encry_info != HI_UPG_FILE_ATTR_ENCRYPT) {
        upg_print("[upg_check_encrypt_info]encrypt 0x%x \r\n", encry_info);
        return HI_FALSE;
    }
#else
    if (encry_info != HI_UPG_FILE_ATTR_UNENCRYPT) {
        upg_print("[upg_check_encrypt_info]unencrypt 0x%x \r\n", encry_info);
        return HI_FALSE;
    }
#endif
    return HI_TRUE;
}

hi_bool upg_check_ota_info_is_match(hi_u8 file_type, hi_u8 ota_info)
{
#if defined(CONFIG_COMPRESSION_OTA_SUPPORT)
    hi_unref_param(file_type);
    if (ota_info != HI_UPG_FILE_ATTR_COMPRESSION) {
        upg_print("[upg_check_ota_info]compression 0x%x \r\n", ota_info);
        return HI_FALSE;
    }
#else
    hi_nv_ftm_startup_cfg cfg = { 0 };
    hi_flash_partition_table *partition = hi_get_partition_table();
    uintptr_t kernel_a_addr = partition->table[HI_FLASH_PARTITON_KERNEL_A].addr;
    hi_u32 ret = upg_get_start_up_cfg(&cfg);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg_check_ota_info]get cfg fail:0x%x \r\n", ret);
        return HI_FALSE;
    }
    /* check flashboot */
    if (file_type == HI_UPG_FILE_BOOT) {
        if (ota_info != (HI_UPG_FILE_ATTR_KERNELA  | HI_UPG_FILE_ATTR_KERNELB)) {
            upg_print("[upg_check_ota_info]dual flashboot 0x%x \r\n", ota_info);
            return HI_FALSE;
        }
        return HI_TRUE;
    }

    if (cfg.addr_start == kernel_a_addr) {
        if ((ota_info != HI_UPG_FILE_ATTR_KERNELB)) {
            upg_print("[upg_check_ota_info]kernela 0x%x \r\n", ota_info);
            return HI_FALSE;
        }
        return HI_TRUE;
    }

    if ((ota_info != HI_UPG_FILE_ATTR_KERNELA)) {
        upg_print("[upg_check_ota_info]kernelb 0x%x \r\n", ota_info);
        return HI_FALSE;
    }
#endif
    return HI_TRUE;
}

hi_u32 upg_check_file_attributes(hi_u8 file_type, hi_u8 file_attr)
{
    hi_u8 file_info = file_attr;
    hi_u8 ota_info = file_info & HI_UPG_OTA_SETTINGS_MASK;
    hi_u8 encry_info = file_info >> 6; /* 6: ota settings bit number */

    upg_print("[upg check attributes]type-attr-encry-ota:0x%x-0x%x-0x%x-0x%x \r\n",
              file_type, file_attr, encry_info, ota_info);
    if (upg_check_encrypt_info_is_match(encry_info) == HI_FALSE) {
        return HI_ERR_UPG_ENCRYPT_NOT_MATCH;
    }

    if (upg_check_ota_info_is_match(file_type, ota_info) == HI_FALSE) {
        return HI_ERR_UPG_OTA_NOT_MATCH;
    }
    upg_print("[upg check attributes]success \r\n");

    return HI_ERR_SUCCESS;
}

hi_u32 upg_check_code_ver(hi_u8 ver)
{
    hi_u8 current_ver;
    hi_u32 ret;

    if (ver > KERELN_VER_MAX) {
        upg_print("[upg check code ver]file ver:%d \r\n", ver);
        return HI_ERR_UPG_KERNEL_VER_OVER;
    }

    ret = upg_get_efuse_code_ver(&current_ver);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check code ver]get ver ret:0x%x \r\n", ret);
        return ret;
    }

    if (ver < current_ver) {
        upg_print("[upg check code ver]current>file:%d-%d \r\n", current_ver, ver);
        return HI_ERR_UPG_LOW_KERNEL_VER;
    }

    if ((current_ver == KERELN_VER_MAX) && (ver > KERELN_VER_MAX)) {
        upg_print("[upg check code ver]current-file:%d-%d \r\n", current_ver, ver);
        return HI_ERR_UPG_FULL_KERNEL_VER;
    }
    return ret;
}

hi_u32 upg_check_boot_ver(hi_u8 ver)
{
    hi_u8 current_ver;
    hi_u32 ret;

    if (ver > BOOT_VER_MAX) {
        upg_print("[upg check boot ver]file ver:%d \r\n", ver);
        return HI_ERR_UPG_BOOT_VER_OVER;
    }

    ret = upg_get_efuse_boot_ver(&current_ver);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check boot ver]get ver ret:0x%x \r\n", ret);
        return ret;
    }

    if (ver < current_ver) {
        upg_print("[upg check boot ver]current>file:%d-%d \r\n", current_ver, ver);
        return HI_ERR_UPG_LOW_BOOT_VER;
    }

    if ((current_ver == BOOT_VER_MAX) && (ver > BOOT_VER_MAX)) {
        upg_print("[upg check boot ver]current-file:%d-%d \r\n", current_ver, ver);
        return HI_ERR_UPG_FULL_BOOT_VER;
    }
    return ret;
}

hi_u32 upg_check_version(hi_u8 file_type, hi_u8 ver)
{
    hi_u32 ret;
    if (file_type == HI_UPG_FILE_KERNEL) {
        ret = upg_check_code_ver(ver);
    } else if (file_type == HI_UPG_FILE_BOOT) {
        ret = upg_check_boot_ver(ver);
    } else {
        return HI_ERR_UPG_FILE_TYPE;
    }
    upg_print("[upg check ver]ret:0x%x \r\n", ret);
    return ret;
}

hi_u32 upg_check_file_len(hi_u8 file_type, hi_u32 file_len)
{
    hi_u32 max_len = 0;
    hi_u32 ret = upg_get_max_file_len(file_type, &max_len);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if (file_len > max_len) {
        upg_print("[upg check file len]fail,filetype-filelen:0x%x-0x%x-0x%x. \r\n", file_type, file_len, max_len);
        return HI_ERR_UPG_FILE_LEN_OVER;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 upg_get_common_head_from_flash(hi_u32 addr, hi_upg_common_head *head)
{
    hi_u32 ret = hi_flash_read(addr, sizeof(hi_upg_common_head), (hi_u8 *)head);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get common head]fail,addr-ret:0x%x-0x%x \r\n", addr, ret);
        return ret;
    }
    return ret;
}

hi_u32 upg_get_section_head_from_flash(hi_u32 addr, hi_upg_section_head *section_head)
{
    hi_upg_common_head head = { 0 };
    hi_u32 ret;

    if (section_head == HI_NULL) {
        upg_print("[upg get section head]is null.\r\n");
        return HI_ERR_UPG_NULL_POINTER;
    }
    ret = hi_flash_read(addr, sizeof(hi_upg_common_head), (hi_u8 *)(&head));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get section head]common head read ret:0x%x \r\n", ret);
        return ret;
    }
    ret = hi_flash_read(addr + head.section_offset, sizeof(hi_upg_section_head), (hi_u8 *)section_head);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg get section head]flash read ret:0x%x \r\n", ret);
        return ret;
    }

    return ret;
}

hi_u32 upg_check_alg_param(HI_CONST hi_upg_common_head *head)
{
    sign_alg_param alg_param = {0};

    if (head == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    if (memcpy_s(&alg_param, sizeof(sign_alg_param), &(head->param), sizeof(sign_alg_param)) != EOK) {
        return HI_ERR_FAILURE;
    }
    if ((alg_param.sign_alg != HI_MODE_PKCS_V15) && (alg_param.sign_alg != HI_MODE_PKCS_PSS) &&
        (alg_param.sign_alg != HI_MODE_ECC)) {
        return HI_ERR_UPG_SIGN_ALG;
    }

    if (alg_param.sign_alg < HI_MODE_ECC) {
        if (head->section_offset != (sizeof(hi_upg_common_head) + sizeof(upg_rsa_key) + sizeof(upg_rsa_sign))) {
            return HI_ERR_UPG_RSA_HEAD_SIGN;
        }
        return HI_ERR_SUCCESS;
    }

    if (head->section_offset != (sizeof(hi_upg_common_head) + sizeof(upg_ecc_key) + sizeof(upg_ecc_sign))) {
        return HI_ERR_UPG_ECC_HEAD_SIGN;
    }
    return HI_ERR_SUCCESS;
}

hi_u32 upg_check_head_common_info(const hi_upg_common_head *head, hi_u32 head_size)
{
    hi_bool flag;

    if (head_size != sizeof(hi_upg_common_head)) {
        return HI_ERR_UPG_HEAD_LEN;
    }

    hi_u32 ret = upg_check_image_id(head->image_id);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = upg_check_file_type(head->file_type);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = upg_check_file_attributes(head->file_type, head->file_attr);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    ret = upg_check_file_len(head->file_type, head->file_len);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    if ((head->file_len != (head->section_offset + head->section_len)) ||
        (head->section_offset != (sizeof(hi_upg_common_head) + sizeof(hi_upg_key) + sizeof(hi_upg_sign))) ||
        (head->section_len < (sizeof(hi_upg_section_head) + sizeof(hi_upg_sign)))) {
        upg_print("[upg check len]fail:0x%x-0x%x-0x%x \r\n", head->file_len, head->section_offset, head->section_len);
        return HI_ERR_UPG_FILE_LEN;
    }

    /* The RSA, ECC, and SHA256 authentication modes have the same key length. */
    if (head->key_len != sizeof(upg_rsa_key)) {
        return HI_ERR_UPG_KEY_LEN;
    }

    ret = upg_is_secure_efuse(&flag);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check head common]get secure efuse,err:0x%x \r\n", ret);
        return ret;
    }

    if (flag == HI_FALSE) {
        upg_print("[upg check head common]not secure boot.\r\n");
        return HI_ERR_SUCCESS;
    }

    ret = upg_check_version(head->file_type, head->file_version);
    if (ret != HI_ERR_SUCCESS) {
        return ret;
    }

    return upg_check_alg_param(head);
}

hi_u32 upg_check_common_head(const hi_upg_common_head *head, hi_u32 head_size)
{
    hi_u32 ret = upg_check_head_common_info(head, head_size);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check common head]ret:0x%x \r\n", ret);
        return ret;
    }
    ret = upg_user_define_verify(&(head->user_info));
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check common head]user verify fail,ret:0x%x\r\n", ret);
    }
    return ret;
}

hi_u32 upg_verify_file(hi_u32 addr)
{
    hi_u32 ret = HI_ERR_UPG_MALLOC_FAIL;
    hi_upg_head *upg_head = (hi_upg_head *)hi_malloc(HI_MOD_ID_UPG, sizeof(hi_upg_head));
    hi_upg_common_head *common_head = HI_NULL;
    hi_upg_section_head *section_head = HI_NULL;

    if (upg_head == HI_NULL) {
        goto end;
    }
    ret = hi_flash_read(addr, sizeof(hi_upg_head), (hi_u8 *)upg_head);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check file]get upg head addr:0x%x ret:0x%x \r\n", addr, ret);
        goto end;
    }
    common_head = &(upg_head->common);
    ret = upg_check_upg_file(addr, upg_head);
    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg check file]secure ret:0x%x \r\n", ret);
        goto end;
    }
    /* Add check boot bin process. */
    if (common_head->file_type == HI_UPG_FILE_BOOT) {
        section_head = (hi_upg_section_head *)hi_malloc(HI_MOD_ID_UPG, sizeof(hi_upg_section_head));
        if (section_head == HI_NULL) {
            ret = HI_ERR_UPG_MALLOC_FAIL;
            goto end;
        }
        memset_s(section_head, sizeof(hi_upg_section_head), 0, sizeof(hi_upg_section_head));
        ret = hi_flash_read(addr + common_head->section_offset, sizeof(hi_upg_section_head), (hi_u8 *)section_head);
        if (ret != HI_ERR_SUCCESS) {
            upg_print("[upg get section head]flash read ret:0x%x \r\n", ret);
            goto end;
        }
        ret = upg_check_boot_file(addr + section_head->section0_offset, section_head->section0_len);
    }
end:
    upg_mem_free(upg_head);
    upg_mem_free(section_head);
    return ret;
}
