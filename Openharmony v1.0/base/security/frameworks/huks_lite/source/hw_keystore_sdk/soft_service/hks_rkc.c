/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hks_rkc.h"

#include <mbedtls/pkcs5.h>

#include "securec.h"

#include "common/hks_common.h"
#include "common/hks_log_utils.h"
#include "common/hks_mem.h"
#include "hks_errno.h"
#include "hks_file.h"

#ifdef _SECURE_ENVIREMENT_NMI_
#include <hi_cipher.h>
#include <hi_efuse.h>
#include "hks_service.h"
#endif

/* the configuration of root key component */
struct hks_rkc_cfg g_hks_rkc_cfg = {
    HKS_RKC_STATE_INIT, HKS_RKC_VER, HKS_RKC_STORAGE_FILE_SYS, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 },
    { 0, { NULL, NULL } }, HKS_RKC_RMK_ITER, HKS_RKC_RMK_HMAC_SHA256,
    NULL, 0, {0}, HKS_RKC_MK_CRYPT_ALG_AES256_GCM, HKS_RKC_RMK_HMAC_SHA256,
    HKS_RKC_KEK_ITER, {0}
};

/* the default initialized parameter of root key component */
#if defined(_HILINK_PRODUCT_)
const struct hks_rkc_init_para g_hks_rkc_def_init_para = {
    HKS_RKC_VER, HKS_RKC_STORAGE_FILE_SYS,
    { HKS_RKC_KSF_NUM_HILINK, { HKS_KEY_STORE_FILE_NAME, NULL } },
    HKS_RKC_RMK_ITER, HKS_RKC_RMK_HMAC_SHA256, NULL, 0,
    HKS_RKC_MK_CRYPT_ALG_AES256_GCM, HKS_RKC_RMK_HMAC_SHA256,
    HKS_RKC_KEK_ITER
};
#else
const struct hks_rkc_init_para g_hks_rkc_def_init_para = {
    HKS_RKC_VER, HKS_RKC_STORAGE_FILE_SYS,
    { HKS_RKC_KSF_NUM, { "info1.data", "info2.data" } },
    HKS_RKC_RMK_ITER, HKS_RKC_RMK_HMAC_SHA256, NULL, 0,
    HKS_RKC_MK_CRYPT_ALG_AES256_GCM, HKS_RKC_RMK_HMAC_SHA256,
    HKS_RKC_KEK_ITER
};
#endif

/* the flag of keystore file */
const uint8_t g_hks_rkc_ksf_flag[HKS_RKC_KSF_FLAG_LEN] = {
    0x5F, 0x64, 0x97, 0x8D, 0x19, 0x4F, 0x89, 0xCF
};

/* the additional data of master key */
uint8_t g_hks_rkc_mk_add_data[HKS_RKC_MK_ADD_DATA_LEN] = {
    /* H     K     S     R     K     C     M     K */
    0x48, 0x4B, 0x53, 0x52, 0x4B, 0x43, 0x4D, 0x4B
};

/* the data of master key */
struct hks_rkc_mk g_hks_rkc_mk = {
    HKS_BOOL_FALSE, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, {0}
};

#define IV_SHA256_RESULT_LEN 32
#define KDF_ITERATION_TIMES 1000 /* the lowest iteration times, cannot change smaller */

/*
 * root key component - initialize the attribute of keystore file
 * parameter:
 *     ksf_attr      - [in] - the attribute of keystore file.
 * return value:
 *     success or error code
 * note:
 *     If initialization failed in this function,
 *     the dynamic memory will be freed by hks_rkc_destroy().
 */
static int32_t hks_rkc_init_ksf_attr(const struct hks_rkc_ksf_attr *ksf_attr)
{
    g_hks_rkc_cfg.ksf_attr.num = ksf_attr->num;

    uint32_t i = 0;
    int32_t rc = HKS_STATUS_OK;

    /* clone keystore filename from parameter. */
    for (; i < ksf_attr->num; ++i) {
        char *filename = hks_clone_str(ksf_attr->name[i],
            HKS_RKC_KSF_NAME_LEN_MAX);

        if (filename == NULL) {
            /* the memory will be freed by hks_rkc_destroy() */
            rc = HKS_ERROR_MALLOC_FAIL;
            break;
        }
        g_hks_rkc_cfg.ksf_attr.name[i] = filename;
    }

    return rc;
}

/*
 * root key component - initialize entropy
 * parameter:
 *     entropy      - [in] - entropy.
 *     entropy_len  - [in] - the length of entropy.
 * return value:
 *     success or error code
 * note:
 *     If initialization failed in this function,
 *     the dynamic memory will be freed by hks_rkc_destroy().
 */
static int32_t hks_rkc_init_entropy(const uint8_t *entropy,
    const uint32_t entropy_len)
{
    /* the entropy is optional. */
    if (entropy == NULL) {
        /* the entropy is empty, skip it. */
        log_info("the entropy is empty");
        return HKS_STATUS_OK;
    }

    /* if entropy is not empty, the length should be checked. */
    if ((entropy_len == 0) ||
        (entropy_len > HKS_RKC_ENTROPY_LEN_MAX)) {
        log_error("invalid para,entropy_len=%u", entropy_len);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    g_hks_rkc_cfg.entropy = (uint8_t *)HKS_MALLOC(entropy_len);
    if (g_hks_rkc_cfg.entropy == NULL) {
        log_error("malloc entropy buffer fail,len=%u", entropy_len);
        return HKS_ERROR_MALLOC_FAIL;
    }

    g_hks_rkc_cfg.entropy_len = entropy_len;

    int32_t rc = memcpy_s(g_hks_rkc_cfg.entropy, entropy_len, entropy,
        entropy_len);
    /* if copy fail, the memory will be freed by hks_rkc_destroy() */
    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    return HKS_STATUS_OK;
}

/*
 * root key component - fill hash field of keystore file buffer
 * parameter:
 *     ksf_buf        - [in]     - the buffer of keystore file.
 *     ksf_buf_len    - [out]    - the length of keystore file buffer.
 *     ksf_buf_offset - [in,out] - the offset of keystore file buffer.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_fill_ksf_hash(uint8_t *ksf_buf, uint32_t ksf_buf_len,
    uint32_t *ksf_buf_offset)
{
    struct hks_blob hash_src = { 0, NULL, 0 };
    struct hks_blob hash = { 0, NULL, 0 };

    if ((ksf_buf_len < HKS_RKC_KSF_FLAG_LEN) || (*ksf_buf_offset <= HKS_RKC_KSF_FLAG_LEN) ||
        (ksf_buf_len < *ksf_buf_offset))
        return HKS_ERROR_INSUFFICIENT_CAPACITY;

    /*
     * calculate SHA256
     * skip file flag, begin with version, end with reserve field.
     */
    hash_src.data = ksf_buf + HKS_RKC_KSF_FLAG_LEN;
    hash_src.size = *ksf_buf_offset - HKS_RKC_KSF_FLAG_LEN;
    hash.data = ksf_buf + *ksf_buf_offset;
    hash.size = HKS_RKC_HASH_LEN;
    int32_t rc = hks_calc_sha256(&hash_src,
        HKS_RKC_KSF_HASH_SRC_NUM, &hash);

    if (rc != HKS_STATUS_OK)
        return rc;

    *ksf_buf_offset += HKS_RKC_HASH_LEN;

    return HKS_STATUS_OK;
}

/*
 * root key component - fill root key data into keystore file buffer
 * parameter:
 *     ksf_data       - [in]     - the data of keystore file.
 *     ksf_buf        - [out]    - the buffer of keystore file.
 *     ksf_buf_len    - [in]     - the buffer length of keystore file.
 *     ksf_buf_offset - [in,out] - the buffer offset of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_fill_ksf_rk(const struct hks_rkc_ksf_data *ksf_data,
    uint8_t *ksf_buf, uint32_t ksf_buf_len, uint32_t *ksf_buf_offset)
{
    /* Fill version */
    int32_t rc = hks_u16_2_u8_buf(ksf_data->version, ksf_buf, ksf_buf_len,
        ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill rk_creat_time */
    rc = hks_time_2_u8_buf(&(ksf_data->rk_created_time), ksf_buf,
        ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill rk_expired_time */
    rc = hks_time_2_u8_buf(&(ksf_data->rk_expired_time), ksf_buf,
        ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill the first material */
    rc = hks_u8_array_2_u8_buf(ksf_data->rk_material1,
        HKS_RKC_MATERIAL_LEN,
        ksf_buf, ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill the second material */
    rc = hks_u8_array_2_u8_buf(ksf_data->rk_material2,
        HKS_RKC_MATERIAL_LEN,
        ksf_buf, ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill iterator number */
    rc = hks_u32_2_u8_buf(ksf_data->rmk_iter, ksf_buf, ksf_buf_len,
        ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill salt */
    rc = hks_u8_array_2_u8_buf(ksf_data->rmk_salt, HKS_RKC_SALT_LEN,
        ksf_buf, ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill hash algorithm */
    rc = hks_u32_2_u8_buf(ksf_data->rmk_hash_alg, ksf_buf, ksf_buf_len,
        ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill reserve field */
    rc = hks_u8_array_2_u8_buf(ksf_data->rk_rsv, sizeof(ksf_data->rk_rsv),
        ksf_buf, ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    return HKS_STATUS_OK;
}


/*
 * root key component - fill masetr key data into keystore file buffer
 * parameter:
 *     ksf_data       - [in]     - the data of keystore file.
 *     ksf_buf        - [out]    - the buffer of keystore file.
 *     ksf_buf_len    - [in]     - the buffer length of keystore file.
 *     ksf_buf_offset - [in,out] - the buffer offset of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_fill_ksf_mk(const struct hks_rkc_ksf_data *ksf_data,
    uint8_t *ksf_buf, uint32_t ksf_buf_len, uint32_t *ksf_buf_offset)
{
    /* Fill mk_created_time */
    int32_t rc = hks_time_2_u8_buf(&(ksf_data->mk_created_time), ksf_buf,
        ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill mk_expired_time */
    rc = hks_time_2_u8_buf(&(ksf_data->mk_expired_time), ksf_buf,
        ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill encrption algorithm */
    rc = hks_u32_2_u8_buf(ksf_data->mk_encrypt_alg, ksf_buf, ksf_buf_len,
        ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill IV */
    rc = hks_u8_array_2_u8_buf(ksf_data->mk_iv, HKS_RKC_MK_IV_LEN,
        ksf_buf, ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill ciphertext */
    rc = hks_u8_array_2_u8_buf(ksf_data->mk_ciphertext,
        HKS_RKC_MK_CIPHERTEXT_LEN, ksf_buf, ksf_buf_len,
        ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill reserve field */
    rc = hks_u8_array_2_u8_buf(ksf_data->mk_rsv, sizeof(ksf_data->mk_rsv),
        ksf_buf, ksf_buf_len, ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    return rc;
}

/*
 * root key component - fill keystore file buffer
 * parameter:
 *     ksf_data      - [in]  - the data of keystore file.
 *     ksf_buf       - [out] - the buffer of keystore file.
 *     ksf_buf_len   - [in]  - the buffer length of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_fill_ksf_buf(const struct hks_rkc_ksf_data *ksf_data,
    uint8_t *ksf_buf, uint32_t ksf_buf_len)
{
    uint32_t ksf_buf_offset = 0;

    /* Fill file flag */
    int32_t rc = hks_u8_array_2_u8_buf(g_hks_rkc_ksf_flag,
        HKS_RKC_KSF_FLAG_LEN,
        ksf_buf, ksf_buf_len, &ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill root key */
    rc = hks_rkc_fill_ksf_rk(ksf_data, ksf_buf, ksf_buf_len,
        &ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill master key */
    rc = hks_rkc_fill_ksf_mk(ksf_data, ksf_buf, ksf_buf_len,
        &ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /*
     * calculate and fill SHA256 result
     * skip file flag, begin with version, end with reserve field.
     */
    rc = hks_rkc_fill_ksf_hash(ksf_buf, ksf_buf_len, &ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    return HKS_STATUS_OK;
}

/*
 * root key component - write keystore file
 * parameter:
 *     ksf_name      - [in]  - keystore filename.
 *     ksf_data      - [in]  - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_write_ksf(const char *ksf_name, const struct hks_rkc_ksf_data *ksf_data)
{
    uint8_t *ksf_buf = (uint8_t *)HKS_MALLOC(HKS_RKC_KSF_BUF_LEN);

    if (ksf_buf == NULL) {
        log_error("malloc ksf buffer fail");
        return HKS_ERROR_MALLOC_FAIL;
    }

    /* Clear buffer data before using it. */
    (void)memset_s(ksf_buf, HKS_RKC_KSF_BUF_LEN, 0, HKS_RKC_KSF_BUF_LEN);

    int32_t rc;

    do {
        /* Fill data into buffer. */
        rc = hks_rkc_fill_ksf_buf(ksf_data, ksf_buf, HKS_RKC_KSF_BUF_LEN);
        if (rc != HKS_STATUS_OK)
            break;

        /* write buffer data into keystore file */
        rc = hks_file_write(ksf_name, HKS_FILE_OFFSET_BASE, ksf_buf,
            HKS_RKC_KSF_BUF_LEN);
        if (rc != HKS_STATUS_OK) {
            log_error("write ksf fail,name=%s,rc=%d", ksf_name, rc);
            break;
        }

        log_info("write ksf success");
    } while (0);

    /* clear buffer after use. */
    (void)memset_s(ksf_buf, HKS_RKC_KSF_BUF_LEN, 0, HKS_RKC_KSF_BUF_LEN);

    /* The buffer must be freed no matter success or fail. */
    hks_free_ptr(ksf_buf);

    return rc;
}

/*
 * root key component - extract ksf file flag from keystore file buffer
 * parameter:
 *     ksf_buf        - [in]     - the buffer of keystore file.
 *     ksf_buf_len    - [out]    - the length of keystore file buffer.
 *     ksf_buf_offset - [in,out] - the offset of keystore file buffer.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_extract_ksf_file_flag(const uint8_t *ksf_buf,
    uint32_t ksf_buf_len, uint32_t *ksf_buf_offset)
{
    uint8_t file_flag[HKS_RKC_KSF_FLAG_LEN] = {0};

    /* Extract file flag. */
    int32_t rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len,
        ksf_buf_offset,
        file_flag, HKS_RKC_KSF_FLAG_LEN);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Check file flag. */
    if (memcmp(file_flag, g_hks_rkc_ksf_flag, HKS_RKC_KSF_FLAG_LEN)) {
        log_error("ksf file flag is invalid");
        return HKS_ERROR_READ_FILE_FAIL;
    }

    return HKS_STATUS_OK;
}

/*
 * root key component - extract hash field from keystore file buffer
 * parameter:
 *     ksf_buf        - [in]     - the buffer of keystore file.
 *     ksf_buf_len    - [out]    - the length of keystore file buffer.
 *     ksf_buf_offset - [in,out] - the offset of keystore file buffer.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_extract_ksf_hash(uint8_t *ksf_buf, uint32_t ksf_buf_len,
    uint32_t *ksf_buf_offset)
{
    uint8_t ksf_hash[HKS_RKC_HASH_LEN] = {0};
    uint8_t hash_result[HKS_RKC_HASH_LEN] = {0};
    struct hks_blob hash_src = { 0, NULL, 0 };
    struct hks_blob hash = { 0, NULL, 0 };

    /*
     * calculate SHA256
     * skip file flag, begin with version, end with reserve field.
     */
    hash_src.data = ksf_buf + HKS_RKC_KSF_FLAG_LEN;
    hash_src.size = *ksf_buf_offset - HKS_RKC_KSF_FLAG_LEN;
    hash.data = hash_result;
    hash.size = HKS_RKC_HASH_LEN;
    int32_t rc = hks_calc_sha256(&hash_src, HKS_RKC_KSF_HASH_SRC_NUM,
        &hash);

    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract hash from ksf buffer */
    rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len, ksf_buf_offset,
        ksf_hash, HKS_RKC_HASH_LEN);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Check hash result. */
    if (memcmp(hash_result, ksf_hash, HKS_RKC_HASH_LEN)) {
        log_error("ksf hash result is invalid");
        return HKS_ERROR_INVALID_KEY_FILE;
    }

    return HKS_STATUS_OK;
}

/*
 * root key component - extract root key data from keystore file buffer
 * parameter:
 *     ksf_buf        - [in]     - the buffer of keystore file.
 *     ksf_buf_len    - [in]     - the buffer length of keystore file.
 *     ksf_buf_offset - [in,out] - the buffer offset of keystore file.
 *     ksf_data       - [out]    - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_extract_ksf_rk(const uint8_t *ksf_buf,
    uint32_t ksf_buf_len, uint32_t *ksf_buf_offset,
    struct hks_rkc_ksf_data *ksf_data)
{
    /* Extract version. */
    int32_t rc = hks_u8_buf_2_u16(ksf_buf, ksf_buf_len, ksf_buf_offset,
        &(ksf_data->version));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract rk_creat_time */
    rc = hks_u8_buf_2_time(ksf_buf, ksf_buf_len, ksf_buf_offset,
        &(ksf_data->rk_created_time));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract rk_expired_time */
    rc = hks_u8_buf_2_time(ksf_buf, ksf_buf_len, ksf_buf_offset,
        &(ksf_data->rk_expired_time));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract the first material */
    rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len, ksf_buf_offset,
        ksf_data->rk_material1, HKS_RKC_MATERIAL_LEN);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract the second material */
    rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len, ksf_buf_offset,
        ksf_data->rk_material2, HKS_RKC_MATERIAL_LEN);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract iterator number */
    rc = hks_u8_buf_2_u32(ksf_buf, ksf_buf_len, ksf_buf_offset,
        &(ksf_data->rmk_iter));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract salt */
    rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len, ksf_buf_offset,
        ksf_data->rmk_salt, HKS_RKC_SALT_LEN);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract hash algorithm */
    rc = hks_u8_buf_2_u32(ksf_buf, ksf_buf_len, ksf_buf_offset,
        &(ksf_data->rmk_hash_alg));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract reserve field */
    rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len, ksf_buf_offset,
        ksf_data->rk_rsv, sizeof(ksf_data->rk_rsv));
    if (rc != HKS_STATUS_OK)
        return rc;

    return rc;
}

/*
 * root key component - extract master key data from keystore file buffer
 * parameter:
 *     ksf_buf        - [in]     - the buffer of keystore file.
 *     ksf_buf_len    - [in]     - the buffer length of keystore file.
 *     ksf_buf_offset - [in,out] - the buffer offset of keystore file.
 *     ksf_data       - [out]    - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_extract_ksf_mk(const uint8_t *ksf_buf,
    uint32_t ksf_buf_len, uint32_t *ksf_buf_offset,
    struct hks_rkc_ksf_data *ksf_data)
{
    /* Extract mk_created_time */
    int32_t rc = hks_u8_buf_2_time(ksf_buf, ksf_buf_len, ksf_buf_offset,
        &(ksf_data->mk_created_time));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill mk_expired_time */
    rc = hks_u8_buf_2_time(ksf_buf, ksf_buf_len, ksf_buf_offset,
        &(ksf_data->mk_expired_time));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill encrption algorithm */
    rc = hks_u8_buf_2_u32(ksf_buf, ksf_buf_len, ksf_buf_offset,
        &(ksf_data->mk_encrypt_alg));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill IV */
    rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len, ksf_buf_offset,
        ksf_data->mk_iv, HKS_RKC_MK_IV_LEN);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill ciphertext */
    rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len, ksf_buf_offset,
        ksf_data->mk_ciphertext, HKS_RKC_MK_CIPHERTEXT_LEN);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill reserve field */
    rc = hks_u8_buf_2_u8_array(ksf_buf, ksf_buf_len, ksf_buf_offset,
        ksf_data->mk_rsv, sizeof(ksf_data->mk_rsv));
    if (rc != HKS_STATUS_OK)
        return rc;

    return rc;
}

/*
 * root key component - extract data from keystore file buffer
 * parameter:
 *     ksf_buf       - [in]  - the buffer of keystore file.
 *     ksf_buf_len   - [in]  - the buffer length of keystore file.
 *     ksf_data      - [out] - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_extract_ksf_buf(uint8_t *ksf_buf, uint32_t ksf_buf_len,
    struct hks_rkc_ksf_data *ksf_data)
{
    uint32_t ksf_buf_offset = 0;

    /* Extract file flag. */
    int32_t rc = hks_rkc_extract_ksf_file_flag(ksf_buf, ksf_buf_len,
        &ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract root key data */
    rc = hks_rkc_extract_ksf_rk(ksf_buf, ksf_buf_len, &ksf_buf_offset,
        ksf_data);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract master key data */
    rc = hks_rkc_extract_ksf_mk(ksf_buf, ksf_buf_len, &ksf_buf_offset,
        ksf_data);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract hash */
    rc = hks_rkc_extract_ksf_hash(ksf_buf, ksf_buf_len, &ksf_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    return HKS_STATUS_OK;
}

/*
 * root key component - read keystore file
 * parameter:
 *     ksf_name      - [in]  - keystore filename.
 *     ksf_data      - [out] - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_read_ksf(const char *ksf_name,
    struct hks_rkc_ksf_data *ksf_data)
{
    uint32_t file_size = 0;

    int32_t rc = hks_file_size(ksf_name, &file_size);

    if (rc != HKS_STATUS_OK) {
        log_error("get ksf file size fail,name=%s,rc=%d", ksf_name, rc);
        return HKS_ERROR_INVALID_KEY_FILE;
    }

    /* check the file size. */
    if (file_size < HKS_RKC_KSF_BUF_LEN) {
        log_error("file size is invalid,name=%s,size=%u",
            ksf_name, file_size);
        return HKS_ERROR_INVALID_KEY_FILE;
    }

    uint8_t *ksf_buf = (uint8_t *)HKS_MALLOC(HKS_RKC_KSF_BUF_LEN);

    if (ksf_buf == NULL) {
        log_error("malloc ksf buffer fail");
        return HKS_ERROR_MALLOC_FAIL;
    }

    /* Clear buffer data before using it. */
    (void)memset_s(ksf_buf, HKS_RKC_KSF_BUF_LEN, 0, HKS_RKC_KSF_BUF_LEN);

    do {
        int32_t ksf_real_len = 0;

        rc = hks_file_read(ksf_name, HKS_FILE_OFFSET_BASE, ksf_buf,
            HKS_RKC_KSF_BUF_LEN, &ksf_real_len);
        if (rc != HKS_STATUS_OK) {
            log_error("read ksf file fail,name=%s,rc=%d",
                ksf_name, rc);
            break;
        }

        if (ksf_real_len != HKS_RKC_KSF_BUF_LEN) {
            log_error("real length is invalid,name=%s,real_len=%d",
                      ksf_name, ksf_real_len);
            rc = HKS_ERROR_INVALID_KEY_FILE;
            break;
        }

        rc = hks_rkc_extract_ksf_buf(ksf_buf, ksf_real_len, ksf_data);
        if (rc != HKS_STATUS_OK) {
            log_error("extract ksf file fail,name=%s,rc=%d",
                ksf_name, rc);
            break;
        }
    } while (0);

    /* the data of root key should be cleared after use */
    (void)memset_s(ksf_buf, HKS_RKC_KSF_BUF_LEN, 0, HKS_RKC_KSF_BUF_LEN);
    hks_free_ptr(ksf_buf);

    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INVALID_KEY_FILE;

    return HKS_STATUS_OK;
}

/*
 * root key component - read all keystore files.
 * parameter:
 *     all_ksf_rc      - [out] - all reture code.
 *     all_ksf_data    - [out] - all data.
 *     valid_ksf_data  - [out] - the first valid data.
 *     valid_ksf_index - [out] - the index of first valid data.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_read_all_ksf(int32_t *all_ksf_rc,
    struct hks_rkc_ksf_data *all_ksf_data,
    struct hks_rkc_ksf_data **valid_ksf_data, uint32_t *valid_ksf_index)
{
    if (g_hks_rkc_cfg.ksf_attr.num > HKS_RKC_KSF_NUM) {
        log_error("invalid ksf num=%u", g_hks_rkc_cfg.ksf_attr.num);
        return HKS_ERROR_INTERNAL_UNKOWN;
    }

    uint32_t i = 0;

    /* Read all ksf */
    for (; i < g_hks_rkc_cfg.ksf_attr.num; ++i) {
        if (g_hks_rkc_cfg.ksf_attr.name[i] == NULL)
            continue;

        all_ksf_rc[i] = hks_rkc_read_ksf(g_hks_rkc_cfg.ksf_attr.name[i],
            &(all_ksf_data[i]));
        if (all_ksf_rc[i] != HKS_STATUS_OK)
            continue;

        if (*valid_ksf_data == NULL) {
            /* the first valid ksf is found, save flag and index. */
            *valid_ksf_data  = &(all_ksf_data[i]);
            *valid_ksf_index = i;
        }
    }

    return HKS_STATUS_OK;
}

/*
 * root key component - check keystore file.
 * parameter:
 *     ksf_name        - [in] - ksf name.
 *     rc              - [in] - return code.
 *     ksf_data        - [in] - ksf data.
 *     valid_ksf_data  - [in] - valid ksf data.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_chk_ksf(const char *ksf_name, int32_t rc,
    const struct hks_rkc_ksf_data *ksf_data,
    const struct hks_rkc_ksf_data *valid_ksf_data)
{
    if ((rc != HKS_STATUS_OK) ||
        memcmp(valid_ksf_data, ksf_data, HKS_RKC_KSF_DATA_SIZE)) {
        /*
         * If this ksf is different from the first valid ksf,
         * try to overwrite it by the first valid ksf.
         */
        log_error("repair ksf[%s]", ksf_name);
        return hks_rkc_write_ksf(ksf_name, valid_ksf_data);
    }

    return HKS_STATUS_OK;
}

/*
 * root key component - check all keystore files.
 * parameter:
 *     all_ksf_rc      - [in] - all reture code.
 *     all_ksf_data    - [in] - all data.
 *     valid_ksf_data  - [in] - the first valid data.
 *     valid_ksf_index - [in] - the index of first valid data.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_chk_all_ksf(const int32_t *all_ksf_rc,
    const struct hks_rkc_ksf_data *all_ksf_data,
    const struct hks_rkc_ksf_data *valid_ksf_data, uint32_t valid_ksf_index)
{
    if (g_hks_rkc_cfg.ksf_attr.num > HKS_RKC_KSF_NUM) {
        log_error("invalid ksf num=%u", g_hks_rkc_cfg.ksf_attr.num);
        return HKS_ERROR_INTERNAL_UNKOWN;
    }

    uint32_t i = 0;

    for (; i < g_hks_rkc_cfg.ksf_attr.num; ++i) {
        if (i == valid_ksf_index)
            continue;

        if (g_hks_rkc_cfg.ksf_attr.name[i] == NULL)
            continue;

        int32_t rc = hks_rkc_chk_ksf(g_hks_rkc_cfg.ksf_attr.name[i],
            all_ksf_rc[i], all_ksf_data + i, valid_ksf_data);

        if (rc != HKS_STATUS_OK) {
            log_error("check ksf fail,i=%u,rc=%d", i, rc);
            continue;
        }
    }

    return HKS_STATUS_OK;
}

/*
 * root key component - get fixed material
 * parameter:
 *     material      - [out]    - fixed material.
 *     len           - [in]     - the length of material, it should be 32 bytes.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_get_fixed_material(uint8_t *material, uint32_t len)
{
    const uint8_t fixed_material[HKS_RKC_MATERIAL_LEN] = {
        0xB2, 0xA1, 0x0C, 0x73, 0x52, 0x73, 0x76, 0xA1,
        0x60, 0x62, 0x2E, 0x08, 0x52, 0x08, 0x2E, 0xA9,
        0x60, 0xBC, 0x2E, 0x73, 0x52, 0x0B, 0x0C, 0xBC,
        0xEE, 0x0A, 0x2E, 0x08, 0x52, 0x9C, 0x76, 0xA9
    };

    int32_t rc = memcpy_s(material, len, fixed_material,
        HKS_RKC_MATERIAL_LEN);

    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    return rc;
}

/*
 * root key component - make random material
 * parameter:
 *     random1       - [in]      - the first random number.
 *     random1_len   - [in]      - the length of first random number.
 *     random2       - [in]      - the second random number.
 *     random2_len   - [in]      - the length of second random number.
 *     ksf_data      - [in,out]  - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_calc_material(uint8_t *random1, uint32_t random1_len,
    uint8_t *random2, uint32_t random2_len,
    struct hks_rkc_ksf_data *ksf_data)
{
    /* two material sequence number */
    uint8_t material_sn[HKS_RKC_MATERIAL_NUM] = {
        HKS_RKC_MATERIAL1_SN, HKS_RKC_MATERIAL2_SN
    };

    /* hash source number */
    uint32_t hash_src_num = HKS_RKC_MATERIAL_HASH_SRC_NUM_NO_E;
    /* hash source */
    struct hks_blob hash_src[HKS_RKC_MATERIAL_HASH_SRC_NUM] = {
        { 0, NULL, 0 }, { 0, NULL, 0 }, { 0, NULL, 0 }, { 0, NULL, 0 }
    };
    /* hash result */
    struct hks_blob hash_result[HKS_RKC_MATERIAL_NUM] = {
        { 0, NULL, 0 }, { 0, NULL, 0 }
    };

    /*
     *  calculate material
     *  material1: SHA256(0x1 + R1 + R2 + E)
     *  material2: SHA256(0x2 + R1 + R2 + E)
     */
    hash_src[HKS_RKC_MATERIAL_HASH_SRC_R1].data = random1;
    hash_src[HKS_RKC_MATERIAL_HASH_SRC_R1].size = random1_len;
    hash_src[HKS_RKC_MATERIAL_HASH_SRC_R2].data = random2;
    hash_src[HKS_RKC_MATERIAL_HASH_SRC_R2].size = random2_len;

    /* the entropy is optional. */
    if (g_hks_rkc_cfg.entropy != NULL) {
        hash_src_num = HKS_RKC_MATERIAL_HASH_SRC_NUM;
        hash_src[HKS_RKC_MATERIAL_HASH_SRC_E].data =
            g_hks_rkc_cfg.entropy;
        hash_src[HKS_RKC_MATERIAL_HASH_SRC_E].size =
            g_hks_rkc_cfg.entropy_len;
    }

    /* Two material would be ouput as hash result. */
    hash_result[HKS_RKC_HASH_RESULT_MATERIAL1].data =
        ksf_data->rk_material1;
    hash_result[HKS_RKC_HASH_RESULT_MATERIAL1].size =
        HKS_RKC_MATERIAL_LEN;
    hash_result[HKS_RKC_HASH_RESULT_MATERIAL2].data =
        ksf_data->rk_material2;
    hash_result[HKS_RKC_HASH_RESULT_MATERIAL2].size =
        HKS_RKC_MATERIAL_LEN;

    /* generate two material by SHA256 */
    int32_t rc;
    uint32_t i = 0;

    for (; i < HKS_RKC_MATERIAL_NUM; ++i) {
        hash_src[HKS_RKC_MATERIAL_HASH_SRC_SN].data = &(material_sn[i]);
        hash_src[HKS_RKC_MATERIAL_HASH_SRC_SN].size = sizeof(uint8_t);
        rc = hks_calc_sha256(hash_src, hash_src_num, &(hash_result[i]));
        if (rc != HKS_STATUS_OK) {
            log_error("calc hash fail,rc=%d,i=%u", rc, i);
            return rc;
        }
    }

    return rc;
}

/*
 * root key component - make random material
 * parameter:
 *     ksf_data      - [in,out]  - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_make_random_material(struct hks_rkc_ksf_data *ksf_data)
{
    /* two random number */
    uint8_t random1[HKS_RKC_MATERIAL_LEN] = {0};
    uint8_t random2[HKS_RKC_MATERIAL_LEN] = {0};

    int32_t rc;

    do {
        /* Generate 32*2 random number: R1 + R2 */
        rc = hks_gen_random(random1, HKS_RKC_MATERIAL_LEN);
        if (rc != HKS_STATUS_OK) {
            log_error("generate random1 fail,rc=%d", rc);
            break;
        }

        rc = hks_gen_random(random2, HKS_RKC_MATERIAL_LEN);
        if (rc != HKS_STATUS_OK) {
            log_error("generate random2 fail,rc=%d", rc);
            break;
        }

        /* calculate material */
        rc = hks_rkc_calc_material(random1, HKS_RKC_MATERIAL_LEN,
            random2,
            HKS_RKC_MATERIAL_LEN, ksf_data);
        if (rc != HKS_STATUS_OK)
            break;
    } while (0);

    /* the random number should be cleared after use */
    (void)memset_s(random1, sizeof(random1), 0, sizeof(random1));
    (void)memset_s(random2, sizeof(random2), 0, sizeof(random2));

    return rc;
}

/*
 * root key component - calculate pbkdf2 hmac
 * parameter:
 *     hash_alg      - [in]      - hash algorithm.
 *     raw_key       - [in]      - raw key.
 *     salt          - [in]      - salt.
 *     iter_num      - [in]      - the number of iterater.
 *     dk            - [in,out]  - derived key.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_pbkdf2_hmac(uint32_t hash_alg,
    const struct hks_blob *raw_key, const struct hks_blob *salt,
    uint32_t iter_num, struct hks_blob *dk)
{
    mbedtls_md_type_t md_type;

    if (hash_alg == HKS_RKC_RMK_HMAC_SHA256) {
        md_type = MBEDTLS_MD_SHA256;
    } else {
        log_error("the hash algorithm(%u) is unsupported", hash_alg);
        return HKS_ERROR_NOT_SUPPORTED;
    }

    /* Initialize the generic message-digest context. */
    mbedtls_md_context_t sha_ctx;

    mbedtls_md_init(&sha_ctx);

    /* Get the generic message-digest context by hash algorithm. */
    const mbedtls_md_info_t *info_sha = mbedtls_md_info_from_type(md_type);

    if (info_sha == NULL) {
        log_error("info sha is invalid");
        return HKS_ERROR_INTERNAL_UNKOWN;
    }

    int32_t rc;

    do {
        /* Setup the generic message-digest context. */
        rc = mbedtls_md_setup(&sha_ctx, info_sha,
            HKS_RKC_RMK_HMAC_FLAG);
        if (rc != HKS_SUCCESS) {
            log_error("setup mbedtls md fail,rc=%d", rc);
            break;
        }

        /* PBKDF2-HMAC */
        rc = mbedtls_pkcs5_pbkdf2_hmac(&sha_ctx, raw_key->data,
            raw_key->size,
            salt->data, salt->size, iter_num, dk->size, dk->data);
        if (rc != HKS_SUCCESS) {
            log_error("mbedtls pbkdf2 hmac fail,rc=%d", rc);
            break;
        }
    } while (0);

    /* Free the generic message-digest context. */
    mbedtls_md_free(&sha_ctx);
    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    return HKS_STATUS_OK;
}

/*
 * root key component - write all keystore file
 * parameter:
 *     ksf_data      - [in] - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_write_all_ksf(const struct hks_rkc_ksf_data *ksf_data)
{
    if (g_hks_rkc_cfg.ksf_attr.num > HKS_RKC_KSF_NUM) {
        log_error("invalid ksf num=%u", g_hks_rkc_cfg.ksf_attr.num);
        return HKS_ERROR_INTERNAL_UNKOWN;
    }

    uint32_t i = 0;
    int32_t rc;
    uint32_t success_num = 0;

    for (; i < g_hks_rkc_cfg.ksf_attr.num; ++i) {
        if (g_hks_rkc_cfg.ksf_attr.name[i] == NULL)
            continue;

        rc = hks_rkc_write_ksf(g_hks_rkc_cfg.ksf_attr.name[i],
            ksf_data);
        if (rc != HKS_STATUS_OK)
            continue;
        ++success_num;
    }

    /*
     * If all keystore file were wrotten fail, return error code,
     * otherwise, return success code.
     */
    if (success_num == 0)
        rc = HKS_ERROR_WRITE_FILE_FAIL;
    else
        rc = HKS_STATUS_OK;

    return rc;
}

/*
 * root key component - get the raw key for derive root master key
 * parameter:
 *     ksf_data      - [in]  - the data which loaded from keystore file.
 *     raw_key       - [out] - raw key
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_get_rmk_raw_key(const struct hks_rkc_ksf_data *ksf_data,
    struct hks_blob *raw_key)
{
    uint8_t material3[HKS_RKC_MATERIAL_LEN] = {0};

    /* Get the fixed material */
    int32_t rc = hks_rkc_get_fixed_material(material3, HKS_RKC_MATERIAL_LEN);

    if (rc != HKS_STATUS_OK)
        return rc;

    /* materials xor */
    uint32_t i = 0;

    for (; i < HKS_RKC_MATERIAL_LEN; i++)
        raw_key->data[i] = (uint8_t)(ksf_data->rk_material1[i] ^
            ksf_data->rk_material2[i] ^ material3[i]);

    /* append hardware UDID */
    rc = hks_get_hardware_udid(raw_key->data + HKS_RKC_MATERIAL_LEN,
        HKS_HARDWARE_UDID_LEN);
    if (rc != HKS_STATUS_OK)
        return rc;

    return HKS_STATUS_OK;
}

/*
 * root key component - derive root master key
 * parameter:
 *     ksf_data      - [in]  - the data which loaded from keystore file.
 *     rmk           - [out] - root master key,
 *                             it must be clear by caller after use.
 *     rmk_len       - [in]  - the length of root master key,
 *                             it should be 64 bytes.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_derive_rmk(const struct hks_rkc_ksf_data *ksf_data,
    uint8_t *rmk, uint32_t rmk_len)
{
    uint8_t salt_data[HKS_RKC_SALT_LEN] = {0};
    int32_t rc = memcpy_s(salt_data, HKS_RKC_SALT_LEN, ksf_data->rmk_salt,
        HKS_RKC_SALT_LEN);

    if (rc != HKS_STATUS_OK) {
        log_error("generate material fail,rc=%d", rc);
        return HKS_ERROR_INTERNAL_UNKOWN;
    }

    struct hks_blob dk = { 0, rmk, rmk_len };
    struct hks_blob salt = { 0, salt_data, HKS_RKC_SALT_LEN };
    struct hks_blob raw_key;

    rc = hks_blob_init(&raw_key, sizeof(uint8_t), HKS_RKC_RAW_KEY_LEN,
        HKS_BLOB_TYPE_RAW);
    if (rc != HKS_STATUS_OK) {
        log_error("init raw key fail,rc=%d", rc);
        return rc;
    }

    do {
        /* get the raw key */
        rc = hks_rkc_get_rmk_raw_key(ksf_data, &raw_key);
        if (rc != HKS_STATUS_OK)
            break;

        /* PBKDF2-HMAC */
        rc = hks_rkc_pbkdf2_hmac(ksf_data->rmk_hash_alg, &raw_key, &salt,
            ksf_data->rmk_iter, &dk);
        if (rc != HKS_STATUS_OK)
            break;
    } while (0);

    hks_blob_destroy(&raw_key);

    return rc;
}

/*
 * root key component - do crypt operation for master key
 * parameter:
 *     ksf_data   - [in]     - the data which loaded from keystore file.
 *     plaintext  - [in,out] - the plaintext of master key
 *     ciphertext - [in,out] - the ciphertext of master key
 *     operation  - [in]     - operation, HKS_RKC_ENCRYPT or HKS_RKC_DECRYPT.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_mk_crypt(struct hks_rkc_ksf_data *ksf_data,
    struct hks_blob *plaintext, struct hks_blob *ciphertext,
    uint8_t operation)
{
    uint8_t *rmk = (uint8_t *)HKS_MALLOC(HKS_RKC_RMK_LEN);

    if (rmk == NULL) {
        log_error("malloc rmk fail");
        return HKS_ERROR_MALLOC_FAIL;
    }

    int32_t rc;

    do {
        rc = hks_rkc_derive_rmk(ksf_data, rmk, HKS_RKC_RMK_LEN);
        if (rc != HKS_STATUS_OK)
            break;

        struct hks_blob key = { HKS_BLOB_TYPE_KEY, rmk, HKS_RKC_RMK_EK_LEN };

        size_t output_len = 0;
        struct hks_key_param key_param;
        struct hks_aead_data aead_data;

        (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
        (void)memset_s(&aead_data, sizeof(aead_data), 0, sizeof(aead_data));
        key_param.key_len = HKS_MAX_KEY_LEN_256;
        key_param.key_type = HKS_KEY_TYPE_AES;
        key_param.key_mode = HKS_ALG_GCM;
        aead_data.nonce = ksf_data->mk_iv;
        aead_data.nonce_length = HKS_RKC_MK_IV_LEN;
        aead_data.additional_data = g_hks_rkc_mk_add_data;
        aead_data.additional_data_length = HKS_RKC_MK_ADD_DATA_LEN;
        aead_data.ciphertext = ciphertext->data;
        aead_data.ciphertext_length = ciphertext->size;
        aead_data.plaintext = plaintext->data;
        aead_data.plaintext_length = plaintext->size;
        if (operation == HKS_RKC_ENCRYPT) {
            rc = hks_mbedtls_aead_encrypt(&key, &key_param,
                &aead_data, &output_len);
        } else if (operation == HKS_RKC_DECRYPT) {
            rc = hks_mbedtls_aead_decrypt(&key, &key_param,
                &aead_data, &output_len);
        } else {
            log_error("invalid operation=%u", operation);
            rc = HKS_ERROR_INVALID_ARGUMENT;
            break;
        }
        if (rc != HKS_STATUS_OK) {
            log_error("mbedtls aead encrypt fail, rc=%d", rc);
            break;
        }
    } while (0);

    /* the data of root key should be cleared after use */
    (void)memset_s(rmk, HKS_RKC_RMK_LEN, 0, HKS_RKC_RMK_LEN);
    hks_free_ptr(rmk);

    return rc;
}

/*
 * root key component - mask master key
 * parameter:
 *     mk   - [in]     - mask.
 * return value: none
 */
static void hks_rkc_mask_mk(const struct hks_blob *mk)
{
    struct hks_blob mk_mask = { HKS_BLOB_TYPE_KEY, g_hks_rkc_cfg.mk_mask, HKS_RKC_MK_LEN };
    struct hks_blob mk_with_mask = { HKS_BLOB_TYPE_KEY, g_hks_rkc_mk.mk_with_mask, HKS_RKC_MK_LEN };

    hks_xor(mk, &mk_mask, &mk_with_mask);

    g_hks_rkc_mk.is_valid = HKS_BOOL_TRUE;
}

/*
 * root key component - make master key
 * parameter:
 *     ksf_data      - [in,out]  - the data which loaded from keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_make_mk(struct hks_rkc_ksf_data *ksf_data)
{
    struct hks_blob mk;
    int32_t rc = hks_blob_init(&mk, sizeof(uint8_t), HKS_RKC_MK_LEN,
        HKS_BLOB_TYPE_KEY);

    if (rc != HKS_STATUS_OK) {
        log_error("init mk fail");
        return HKS_ERROR_MALLOC_FAIL;
    }

    do {
        ksf_data->mk_encrypt_alg = g_hks_rkc_cfg.mk_encrypt_alg;

        /* generate the mask of master key */
        rc = hks_gen_random(g_hks_rkc_cfg.mk_mask, HKS_RKC_MK_LEN);
        if (rc != HKS_STATUS_OK)
            break;

        /* generate master key */
        rc = hks_gen_random(mk.data, mk.size);
        if (rc != HKS_STATUS_OK)
            break;

        /* generate the IV of master key */
        rc = hks_gen_random(ksf_data->mk_iv, HKS_RKC_MK_IV_LEN);
        if (rc != HKS_STATUS_OK)
            break;

        struct hks_blob ciphertext = { HKS_BLOB_TYPE_KEY, ksf_data->mk_ciphertext, HKS_RKC_MK_CIPHERTEXT_LEN };

        rc = hks_rkc_mk_crypt(ksf_data, &mk, &ciphertext,
            HKS_RKC_ENCRYPT);
        if (rc != HKS_STATUS_OK)
            break;

        /* the master key in memory should be masked */
        hks_rkc_mask_mk(&mk);
    } while (0);

    hks_blob_destroy(&mk);

    return rc;
}

/*
 * root key component - creat keystore file
 * parameter: none
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_create_ksf(void)
{
    struct hks_rkc_ksf_data *new_ksf_data =
        (struct hks_rkc_ksf_data *)HKS_MALLOC(HKS_RKC_KSF_DATA_SIZE);

    if (new_ksf_data == NULL) {
        log_error("malloc ksf data fail");
        return HKS_ERROR_MALLOC_FAIL;
    }

    /* The root key component data must be clear firstly. */
    (void)memset_s(new_ksf_data, HKS_RKC_KSF_DATA_SIZE, 0,
        HKS_RKC_KSF_DATA_SIZE);

    int32_t rc;

    do {
        /* Fill some fixed field. */
        new_ksf_data->version = g_hks_rkc_cfg.version;
        new_ksf_data->rmk_iter = g_hks_rkc_cfg.rmk_iter;
        new_ksf_data->rmk_hash_alg = g_hks_rkc_cfg.rmk_hash_alg;

        /* Two material are generated by random number. */
        rc = hks_rkc_make_random_material(new_ksf_data);
        if (rc != HKS_STATUS_OK) {
            log_error("generate material fail,rc=%d", rc);
            break;
        }

        /* The salt value is generated by random number. */
        rc = hks_gen_random(new_ksf_data->rmk_salt, HKS_RKC_SALT_LEN);
        if (rc != HKS_STATUS_OK) {
            log_error("generate rmk_salt fail,rc=%d", rc);
            break;
        }

        /* make master key. */
        rc = hks_rkc_make_mk(new_ksf_data);
        if (rc != HKS_STATUS_OK) {
            log_error("make mk fail,rc=%d", rc);
            break;
        }

        /* Write the root key component data into all keystore files */
        rc = hks_rkc_write_all_ksf(new_ksf_data);
        if (rc != HKS_STATUS_OK)
            break;

        log_info("create root key component success");
    } while (0);

    /* the data of root key should be cleared after use */
    (void)memset_s(new_ksf_data, HKS_RKC_KSF_DATA_SIZE, 0,
        HKS_RKC_KSF_DATA_SIZE);
    hks_free_ptr(new_ksf_data);

    return rc;
}

/*
 * root key component - recover master key memory
 * parameter:
 *     ksf_data      - [in]  - the data which loaded from keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_recover_mk_mem(struct hks_rkc_ksf_data *ksf_data)
{
    int32_t rc = memcpy_s(&(g_hks_rkc_mk.mk_created_time),
        sizeof(g_hks_rkc_mk.mk_created_time),
        &(ksf_data->mk_created_time),
        sizeof(ksf_data->mk_created_time));

    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    rc = memcpy_s(&(g_hks_rkc_mk.mk_expired_time),
        sizeof(g_hks_rkc_mk.mk_expired_time),
        &(ksf_data->mk_expired_time),
        sizeof(ksf_data->mk_expired_time));
    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    struct hks_blob mk;

    rc = hks_blob_init(&mk, sizeof(uint8_t), HKS_RKC_MK_LEN,
        HKS_BLOB_TYPE_KEY);
    if (rc != HKS_STATUS_OK) {
        log_error("init mk fail");
        return HKS_ERROR_MALLOC_FAIL;
    }

    do {
        /* generate the mask of master key */
        rc = hks_gen_random(g_hks_rkc_cfg.mk_mask, HKS_RKC_MK_LEN);
        if (rc != HKS_STATUS_OK)
            break;

        struct hks_blob ciphertext = { HKS_BLOB_TYPE_KEY, ksf_data->mk_ciphertext, HKS_RKC_MK_CIPHERTEXT_LEN };

        rc = hks_rkc_mk_crypt(ksf_data, &mk, &ciphertext,
            HKS_RKC_DECRYPT);
        if (rc != HKS_STATUS_OK) {
            rc = HKS_ERROR_INVALID_KEY_FILE;
            break;
        }

        /* the master key in memory should be masked */
        hks_rkc_mask_mk(&mk);
    } while (0);

    hks_blob_destroy(&mk);

    return rc;
}

/*
 * root key component - recover root key memory
 * parameter:
 *     ksf_data      - [in]  - the data which loaded from keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_recover_rk_mem(const struct hks_rkc_ksf_data *ksf_data)
{
    int32_t rc = memcpy_s(&(g_hks_rkc_cfg.rk_created_time),
        sizeof(g_hks_rkc_cfg.rk_created_time),
        &(ksf_data->rk_created_time),
        sizeof(ksf_data->rk_created_time));

    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    rc = memcpy_s(&(g_hks_rkc_cfg.rk_expired_time),
        sizeof(g_hks_rkc_cfg.rk_expired_time),
        &(ksf_data->rk_expired_time),
        sizeof(ksf_data->rk_expired_time));
    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    return HKS_STATUS_OK;
}

/*
 * root key component - load keystore file
 * parameter:
 *     ksf_data      - [out] - the data of keystore file.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_load_ksf(struct hks_rkc_ksf_data *ksf_data)
{
    int32_t all_ksf_rc[HKS_RKC_KSF_NUM] = {0};
    uint32_t data_size = HKS_RKC_KSF_DATA_SIZE * HKS_RKC_KSF_NUM;

    struct hks_rkc_ksf_data *all_ksf_data =
        (struct hks_rkc_ksf_data *)HKS_MALLOC(data_size);

    if (all_ksf_data == NULL) {
        log_error("malloc all ksf data fail");
        return HKS_ERROR_MALLOC_FAIL;
    }

    (void)memset_s(all_ksf_data, data_size, 0, data_size);

    int32_t rc;

    do {
        uint32_t valid_ksf_index = 0;
        struct hks_rkc_ksf_data *valid_ksf_data = NULL;

        rc = hks_rkc_read_all_ksf(all_ksf_rc, all_ksf_data,
            &valid_ksf_data,
            &valid_ksf_index);
        if (rc != HKS_STATUS_OK)
            break;

        if (valid_ksf_data == NULL) {
            log_error("all ksf file are invalid");
            rc = HKS_ERROR_INVALID_KEY_FILE;
            break;
        }

        rc = hks_rkc_recover_rk_mem(valid_ksf_data);
        if (rc != HKS_STATUS_OK)
            break;

        rc = hks_rkc_recover_mk_mem(valid_ksf_data);
        if (rc != HKS_STATUS_OK)
            break;

        rc = hks_rkc_chk_all_ksf(all_ksf_rc, all_ksf_data,
            valid_ksf_data,
            valid_ksf_index);
        if (rc != HKS_STATUS_OK)
            break;

        if (ksf_data != NULL) {
            rc = memcpy_s(ksf_data, HKS_RKC_KSF_DATA_SIZE,
                valid_ksf_data,
                HKS_RKC_KSF_DATA_SIZE);
            if (rc != HKS_STATUS_OK)
                break;
        }

        log_info("load ksf success");
    } while (0);

    (void)memset_s(all_ksf_data, data_size, 0, data_size);
    hks_free_ptr(all_ksf_data);

    return rc;
}

/*
 * root key component - check initialization parameter
 * parameter:
 *     init_para      - [in] - initialization parameter.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_chk_init_para(const struct hks_rkc_init_para *init_para)
{
    /* This function is only used for the parameter check of hks_rkc_init() */
    if ((init_para->storage_type != HKS_RKC_STORAGE_FILE_SYS) &&
        (init_para->storage_type != HKS_RKC_STORAGE_FLASH)) {
        log_error("invalid para,storage_type=%u", init_para->storage_type);
        return HKS_ERROR_INVALID_ARGUMENT;
    }
    if ((init_para->rmk_iter == 0) ||
        (init_para->rmk_iter > HKS_RKC_RMK_ITER_MAX)) {
        log_error("invalid para,rmk_iter=%u", init_para->rmk_iter);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    if (init_para->rmk_hash_alg != HKS_RKC_RMK_HMAC_SHA256) {
        log_error("invalid para,rmk_hash_alg=%u",
            init_para->rmk_hash_alg);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    if ((init_para->ksf_attr.num == 0) ||
        (init_para->ksf_attr.num > HKS_RKC_KSF_NUM)) {
        log_error("invalid para,num=%u", init_para->ksf_attr.num);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    return HKS_STATUS_OK;
}

/*
 * root key component - initialize
 * parameter:
 *     is_key_info_exist  - [in] - is key info exist.
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_init_ksf(int32_t is_key_info_exist)
{
#ifdef _SECURE_ENVIREMENT_NMI_
    return HKS_STATUS_OK;
#endif
    /* load the root key component data from keystore file. */
    int32_t rc = hks_rkc_load_ksf(NULL);

    /*
     * if the keystore file is failed to load and no key is exist,
     * try to recreate it.
     */
    if ((rc != HKS_STATUS_OK) && (is_key_info_exist == HKS_BOOL_FALSE))
        rc = hks_rkc_create_ksf();

    return rc;
}

/*
 * root key component - initialize
 * parameter:
 *     init_para          - [in] - initialization parameter.
 *     is_key_info_exist  - [in] - is key info exist.
 * return value:
 *     success or error code
 */
int32_t hks_rkc_init(const struct hks_rkc_init_para *init_para,
    int32_t is_key_info_exist)
{
    const struct hks_rkc_init_para *init_para_inner = init_para;

    if (init_para_inner == NULL)
        init_para_inner = &g_hks_rkc_def_init_para;

    int32_t rc = hks_rkc_chk_init_para(init_para_inner);

    if (rc != HKS_STATUS_OK)
        return rc;

    if (g_hks_rkc_cfg.state != HKS_RKC_STATE_INIT)
        return HKS_STATUS_OK;

    log_info("RKC init:begin, is_key_info_exist=%d", is_key_info_exist);
    do {
        g_hks_rkc_cfg.state = HKS_RKC_STATE_ON_INIT;
        g_hks_rkc_cfg.version = init_para_inner->version;
        g_hks_rkc_cfg.storage_type = init_para_inner->storage_type;
        g_hks_rkc_cfg.rmk_iter = init_para_inner->rmk_iter;
        g_hks_rkc_cfg.rmk_hash_alg = init_para_inner->rmk_hash_alg;
        g_hks_rkc_cfg.mk_encrypt_alg = init_para_inner->mk_encrypt_alg;
        g_hks_rkc_cfg.kek_hash_alg = init_para_inner->kek_hash_alg;
        g_hks_rkc_cfg.kek_iter = init_para_inner->kek_iter;

        /* Initialize the attribute of keystore file */
        rc = hks_rkc_init_ksf_attr(&(init_para_inner->ksf_attr));
        if (rc != HKS_STATUS_OK)
            break;

        /* Initialize entropy */
        rc = hks_rkc_init_entropy(init_para_inner->entropy,
            init_para_inner->entropy_len);
        if (rc != HKS_STATUS_OK)
            break;

        /* Initialize the keystore file of root key component. */
        rc = hks_rkc_init_ksf(is_key_info_exist);
        if (rc != HKS_STATUS_OK)
            break;

        g_hks_rkc_cfg.state = HKS_RKC_STATE_RUNNING;
        log_info("root key component init success");
    } while (0);

    if (rc != HKS_STATUS_OK) {
        g_hks_rkc_cfg.state = HKS_RKC_STATE_FAIL;
        hks_rkc_destroy();
    }
    log_info("RKC init:end,rc=%d", rc);

    return rc;
}

/*
 * root key component - destory
 * parameter: none
 * return value: none
 */
void hks_rkc_destroy(void)
{
    g_hks_rkc_cfg.state = HKS_RKC_STATE_ON_DEL;

    uint32_t i = 0;

    for (; i < HKS_RKC_KSF_NUM; ++i)
        hks_file_del_s(g_hks_rkc_cfg.ksf_attr.name[i]);

    hks_rkc_clear_mem();
}

/*
 * root key component - clear memory
 * parameter: none
 * return value: none
 */
void hks_rkc_clear_mem(void)
{
    uint32_t i = 0;

    for (; i < HKS_RKC_KSF_NUM; ++i)
        hks_free_ptr(g_hks_rkc_cfg.ksf_attr.name[i]);

    hks_free_ptr(g_hks_rkc_cfg.entropy);

    (void)memset_s(&g_hks_rkc_cfg, sizeof(g_hks_rkc_cfg), 0,
        sizeof(g_hks_rkc_cfg));

    (void)memset_s(&g_hks_rkc_mk, sizeof(g_hks_rkc_mk), 0,
        sizeof(g_hks_rkc_mk));
}

/*
 * root key component - check the parameter of key-encrypting key
 * parameter:
 *     salt      - [in]  - salt,
 *     kek       - [in]  - key-encrypting key,
 * return value:
 *     success or error code
 */
static int32_t hks_rkc_chk_kek_para(const struct hks_blob *salt,
    const struct hks_blob *kek)
{
    if (salt == NULL) {
        log_error("invalid salt");
        return HKS_ERROR_NULL_POINTER;
    }
    if (salt->data == NULL) {
        log_error("invalid salt data");
        return HKS_ERROR_NULL_POINTER;
    }
    if ((salt->size > HKS_RKC_KEK_SALT_LEN_MAX) ||
        (salt->size < HKS_RKC_KEK_SALT_LEN_MIN)) {
        log_error("invalid salt size=%u", salt->size);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    if (kek == NULL) {
        log_error("invalid kek");
        return HKS_ERROR_NULL_POINTER;
    }
    if (kek->data == NULL) {
        log_error("invalid kek data");
        return HKS_ERROR_NULL_POINTER;
    }
    if (kek->size != HKS_RKC_KEK_LEN) {
        log_error("invalid kek size=%u", kek->size);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    return HKS_STATUS_OK;
}

#ifdef _SECURE_ENVIREMENT_NMI_
static int32_t hks_load_root_key(struct hks_blob *key)
{
    hi_cipher_kdf_ctrl ctrl;
    uint8_t salt_sha256_result[IV_SHA256_RESULT_LEN] = {0};
    uint8_t salt_for_mk[HKS_ROOT_KEY_SALT_LEN] = {0}; /* material for derive root key */

    (void)memset_s(&ctrl, sizeof(ctrl), 0, sizeof(ctrl));

    struct hks_blob final_salt = { HKS_BLOB_TYPE_HASH, salt_sha256_result, sizeof(salt_sha256_result) };
    struct hks_blob message = { HKS_BLOB_TYPE_MESSAGE, salt_for_mk, sizeof(salt_for_mk) };

    int32_t ret = hks_efuse_root_salt_read(message.data, message.size);

    if (ret != HKS_SUCCESS) {
        log_error("read efuse root salt failed, return %d", ret);
        return ret;
    }

    ret = hks_service_hash(HKS_ALG_HASH_SHA_256, &message, &final_salt);
    if (ret != HKS_SUCCESS) {
        log_error("sha256 iv failed, return %d", ret);
        return ret;
    }

    ctrl.salt = final_salt.data;
    ctrl.salt_len = final_salt.size;
    ctrl.kdf_cnt = KDF_ITERATION_TIMES;
    ctrl.kdf_mode = HI_CIPHER_SSS_KDF_KEY_STORAGE;

    /* hi_cipher has been initialized in Hi1131SDK, no need init here */
    ret = (hi_s32)hi_cipher_kdf_key_derive(&ctrl);
    if (ret != HKS_SUCCESS) {
        log_error("key derive failed, return %d", ret);
        return ret;
    }

    for (int i = 0; i < HKS_ROOT_KEY_LEN; i++)
        key->data[i] = ctrl.result[i];

    return ret;
}
#endif

/*
 * root key component - get the key-encrypting key
 * parameter:
 *     salt      - [in]  - salt,
 *     kek       - [out] - key-encrypting key,
 *                        it must be cleared by caller after use.
 * return value:
 *     success or error code
 */
int32_t hks_rkc_get_kek(const struct hks_blob *salt, struct hks_blob *kek)
{
#ifndef _SECURE_ENVIREMENT_NMI_
    if (g_hks_rkc_mk.is_valid == HKS_BOOL_FALSE) {
        log_error("mk is valid");
        return HKS_ERROR_INVALID_KEY_FILE;
    }
#endif

    int32_t rc = hks_rkc_chk_kek_para(salt, kek);

    if (rc != HKS_STATUS_OK)
        return rc;

    struct hks_blob mk;

    rc = hks_blob_init(&mk, sizeof(uint8_t), HKS_RKC_MK_LEN,
        HKS_BLOB_TYPE_KEY);
    if (rc != HKS_STATUS_OK)
        return rc;

#ifdef _SECURE_ENVIREMENT_NMI_
    rc = hks_load_root_key(&mk);
    if (rc != HKS_STATUS_OK) {
        hks_blob_destroy(&mk);
        return rc;
    }
#else
    struct hks_blob mk_mask = { HKS_BLOB_TYPE_KEY, g_hks_rkc_cfg.mk_mask, HKS_RKC_MK_LEN };
    struct hks_blob mk_with_mask = { HKS_BLOB_TYPE_KEY, g_hks_rkc_mk.mk_with_mask, HKS_RKC_MK_LEN };

    /* remove mask */
    hks_xor(&mk_with_mask, &mk_mask, &mk);
#endif

    /* derive kek with PBKDF2-HMAC */
    rc = hks_rkc_pbkdf2_hmac(g_hks_rkc_cfg.kek_hash_alg, &mk, salt,
        g_hks_rkc_cfg.kek_iter, kek);

    hks_blob_destroy(&mk);

    return rc;
}
