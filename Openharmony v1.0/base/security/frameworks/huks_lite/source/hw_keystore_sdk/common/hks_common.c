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

#include "hks_common.h"

#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <mbedtls/hkdf.h>
#include <mbedtls/sha256.h>
#include <mbedtls/sha512.h>

#include "securec.h"
#ifdef _SECURE_ENVIREMENT_NMI_
#include <hi_types_base.h>
#include <hi_cipher.h>
#include <hi_efuse.h>
#include "hks_rkc.h"
#endif

#include "hks_errno.h"
#include "hks_hardware_random.h"
#include "hks_log_utils.h"
#include "hks_mem.h"

#define MAX_GCM_TAG_LENGTH 16
#define MBEDTLS_RET_CODE_BOUNDARY (-0x7f)
#define MBEDTLS_RET_CODE_HIGH_LEVEL_MASK 0x7F80

static int32_t hks_aead_setup(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    struct hks_aead_operation *operation);

/* the custom data of random seed */
const unsigned char g_hks_random_seed_custom[] = {
    /* H     K     S */
    0x48, 0x4B, 0x53
};

static hks_get_hardware_udid_callback g_hks_get_hardware_udid_callback;

/*
 * generate random number
 * parameter:
 *     random  - [out]  - the buffer of random number.
 *     len     - [in]   - the length of random number.
 * return value:
 *     success or error code
 */
#if defined(_HILINK_PRODUCT_)
int32_t hks_gen_random(uint8_t *random, uint32_t len)
{
    if ((len == 0) || (len > HKS_RANDOM_MAX_LEN)) {
        log_error("invalid len=%u", len);
        return HKS_ERROR_INVALID_ARGUMENT;
    }
    if (random == NULL) {
        log_error("invalid random");
        return HKS_ERROR_NULL_POINTER;
    }
    int32_t ret = hilink_hardware_random((unsigned char *)random,
        (unsigned int)len);

    if (ret != HKS_SUCCESS) {
        log_error("hilink_hardware_random return %d", ret);
        return HKS_ERROR_INTERNAL_UNKOWN;
    }
    return ret;
}
#elif defined(_SECURE_ENVIREMENT_NMI_)
int32_t hks_gen_random(uint8_t *random, uint32_t len)
{
    if ((len == 0) || (len > HKS_RANDOM_MAX_LEN)) {
        log_error("invalid len=%u", len);
        return HKS_ERROR_INVALID_ARGUMENT;
    }
    if (random == NULL) {
        log_error("invalid random");
        return HKS_ERROR_NULL_POINTER;
    }
    int32_t ret = (int32_t)hi_cipher_trng_get_random_bytes((hi_u8 *)random, len);
    if (ret != HKS_SUCCESS) {
        log_error("hi_cipher_trng_get_random_bytes return %d", ret);
        return HKS_ERROR_INTERNAL_UNKOWN;
    }
    return ret;
}
#else
int32_t hks_gen_random(uint8_t *random, uint32_t len)
{
    if (random == NULL) {
        log_error("invalid random");
        return HKS_ERROR_NULL_POINTER;
    }

    if ((len == 0) || (len > HKS_RANDOM_MAX_LEN)) {
        log_error("invalid len=%u", len);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;

    (void)memset_s(&ctr_drbg, sizeof(ctr_drbg), 0, sizeof(ctr_drbg));

    mbedtls_entropy_init(&entropy);
    int ret = HKS_SUCCESS;

    /* use the g_hks_random_seed_custom without string terminator */
    int32_t rc = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func,
        &entropy, g_hks_random_seed_custom,
        sizeof(g_hks_random_seed_custom));

    if (rc != HKS_STATUS_OK) {
        log_error("ctr drbg seed fail,rc=%d", rc);
        ret = HKS_ERROR_INTERNAL_UNKOWN;
        goto exit;
    }

    rc = mbedtls_ctr_drbg_random(&ctr_drbg, random, len);
    if (rc != HKS_STATUS_OK) {
        log_error("ctr drbg random fail,rc=%d", rc);
        ret = HKS_ERROR_INTERNAL_UNKOWN;
    }
exit:
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
    return ret;
}
#endif

/*
 * calculate SHA256
 * parameter:
 *     hash_src      - [in]      - hash source.
 *     hash_src_num  - [in]      - hash source number.
 *     hash_result   - [in,out]  - hash result.
 * return value:
 *     success or error code
 */
int32_t hks_calc_sha256(const struct hks_blob *hash_src, uint32_t hash_src_num, struct hks_blob *hash_result)
{
    if (hash_src == NULL) {
        log_error("invalid hash src");
        return HKS_ERROR_NULL_POINTER;
    }
    if (hash_result == NULL) {
        log_error("invalid hash result");
        return HKS_ERROR_NULL_POINTER;
    }

    mbedtls_sha256_context sha256_ctx;

    mbedtls_sha256_init(&sha256_ctx);

    int rc = mbedtls_sha256_starts_ret(&sha256_ctx, HKS_BOOL_FALSE);

    if (rc != HKS_SUCCESS) {
        log_error("sha256 starts fail,rc=%d", rc);
        return HKS_ERROR_INTERNAL_UNKOWN;
    }

    do {
        uint32_t i = 0;

        for (; i < hash_src_num; ++i) {
            rc = mbedtls_sha256_update_ret(&sha256_ctx,
                hash_src[i].data, hash_src[i].size);
            if (rc != HKS_SUCCESS) {
                log_error("sha256 update fail,rc=%d,i=%u", rc, i);
                break;
            }
        }
        if (rc != HKS_STATUS_OK)
            break;

        rc = mbedtls_sha256_finish_ret(&sha256_ctx, hash_result->data);
        if (rc != HKS_SUCCESS) {
            log_error("sha256 finish fail,rc=%d,i=%u", rc, i);
            break;
        }
    } while (0);

    mbedtls_sha256_free(&sha256_ctx);

    if (rc != HKS_STATUS_OK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    return HKS_STATUS_OK;
}

/*
 * check the parameter of buffer data initializtion
 * parameter:
 *     data_type - [in]  - data type
 *     buf       - [in]  - buffer
 *     buf_len   - [in]  - the length of buffer
 * return value:
 *     success or error code
 * note:
 *     This function is only used for the parameter check of hks_init_buf_data()
 */
static int32_t hks_chk_init_buf_data_para(uint8_t data_type, const uint8_t *buf, uint32_t buf_len)
{
    if (buf == NULL) {
        log_error("invalid buf");
        return HKS_ERROR_NULL_POINTER;
    }

    if ((data_type > HKS_INIT_DATA_TYPE_MAX) || (buf_len == 0)) {
        log_error("invalid para,data_type=%u,buf_len=%u", data_type,
            buf_len);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    return HKS_STATUS_OK;
}

/*
 * initialize buffer data
 * parameter:
 *     data_type - [in]  - data type
 *     buf       - [out] - buffer
 *     buf_len   - [in]  - the length of buffer
 * return value:
 *     success or error code
 */
int32_t hks_init_buf_data(uint8_t data_type, uint8_t *buf, uint32_t buf_len)
{
    int32_t rc = hks_chk_init_buf_data_para(data_type, buf, buf_len);

    if (rc != HKS_STATUS_OK)
        return rc;

    if (data_type == HKS_INIT_DATA_TYPE_ALL_ZERO) {
        /* all zero */
        (void)memset_s(buf, buf_len, 0, buf_len);
    } else if (data_type == HKS_INIT_DATA_TYPE_ALL_ONE) {
        /* all one */
        (void)memset_s(buf, buf_len, 0xFF, buf_len);
    } else {
        /* random data */
        rc = hks_gen_random(buf, buf_len);
    }

    return rc;
}

int32_t hks_malloc_init_ptr(uint32_t size, uint8_t **ptr)
{
    if (ptr == NULL)
        return HKS_ERROR_NULL_POINTER;
    if (size == 0)
        return HKS_ERROR_INVALID_ARGUMENT;
    *ptr = (uint8_t *)HKS_MALLOC(size);
    if (*ptr == NULL)
        return HKS_ERROR_INSUFFICIENT_MEMORY;

    if (memset_s(*ptr, size, 0, size) != EOK) {
        hks_free_ptr(*ptr);
        return HKS_ERROR_BAD_STATE;
    }
    return HKS_STATUS_OK;
}

void hks_blob_destroy(struct hks_blob *blob)
{
    if (blob == NULL)
        return;
    if (blob->size == 0)
        return;

    if (blob->data != NULL) {
        (void)memset_s(blob->data, blob->size, 0, blob->size);
        hks_free_ptr(blob->data);
    }

    blob->size = 0;
    blob->type = HKS_BLOB_TYPE_RAW;
}

int32_t hks_blob_init(struct hks_blob *blob, size_t nmemb, size_t size, uint8_t type)
{
    if (blob == NULL)
        return HKS_ERROR_NULL_POINTER;
    if ((nmemb == 0) || (size == 0))
        return HKS_ERROR_INVALID_ARGUMENT;
    blob->data = (uint8_t *)HKS_CALLOC(nmemb, size);
    if (blob->data == NULL)
        return HKS_ERROR_INSUFFICIENT_MEMORY;
    blob->size = (uint32_t)size;
    blob->type = type;
    return HKS_STATUS_OK;
}

#ifdef _SECURE_ENVIREMENT_NMI_
int32_t hks_blob_material_init(struct hks_blob **blob)
{
    hks_if_true_return_error((blob == NULL), HKS_ERROR_NULL_POINTER);

    size_t size = sizeof(**blob);
    *blob = (struct hks_blob *)HKS_CALLOC(sizeof(uint8_t), size);
    if (*blob == NULL)
        return HKS_ERROR_INSUFFICIENT_MEMORY;

    (*blob)->type = HKS_BLOB_TYPE_RAW;
    (*blob)->data = NULL;
    (*blob)->size = 0;

    return HKS_STATUS_OK;
}

int32_t hks_encrypt_material_init(struct hks_encrypt_material *encrypt_material)
{
    hks_if_true_return_error((encrypt_material == NULL), HKS_ERROR_NULL_POINTER);

    int32_t res = hks_blob_material_init(&(encrypt_material->plain_text));

    hks_if_status_error_goto_error(res, exit);
    res = hks_blob_material_init(&(encrypt_material->cipher_text));
    hks_if_status_error_goto_error(res, exit);
    res = hks_blob_material_init(&(encrypt_material->nonce_blob));
    hks_if_status_error_goto_error(res, exit);
    res = hks_blob_material_init(&(encrypt_material->aad_blob));
    hks_if_status_error_goto_error(res, exit);
    return res;

exit:
    hks_free_ptr(encrypt_material->plain_text);
    hks_free_ptr(encrypt_material->cipher_text);
    hks_free_ptr(encrypt_material->nonce_blob);
    hks_free_ptr(encrypt_material->aad_blob);
    return res;
}

void hks_encrypt_material_destroy_free(struct hks_encrypt_material *encrypt_material)
{
    if (encrypt_material == NULL)
        return;

    hks_blob_destroy(encrypt_material->plain_text);
    hks_blob_destroy(encrypt_material->cipher_text);
    hks_blob_destroy(encrypt_material->nonce_blob);
    hks_blob_destroy(encrypt_material->aad_blob);

    hks_free_ptr(encrypt_material->plain_text);
    hks_free_ptr(encrypt_material->cipher_text);
    hks_free_ptr(encrypt_material->nonce_blob);
    hks_free_ptr(encrypt_material->aad_blob);
}

int32_t hks_is_valid_output_key(const struct hks_blob *output_key)
{
    if (output_key == NULL)
        return HKS_ERROR_NULL_POINTER;

    if (output_key->data == NULL)
        return HKS_ERROR_NULL_POINTER;
    if (output_key->size == 0)
        return HKS_ERROR_INVALID_ARGUMENT;
    if (output_key->type != HKS_BLOB_TYPE_BUFFER)
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_STATUS_OK;
}

int32_t hks_is_valid_symmetric_key_param(const struct hks_key_param *key_param)
{
    /* no need check key_param->key_auth_id */
    if (key_param == NULL)
        return HKS_ERROR_NULL_POINTER;

    if (key_param->key_type != HKS_KEY_TYPE_AES)
        return HKS_ERROR_NOT_SUPPORTED;

    if ((key_param->key_mode != HKS_ALG_CCM) &&
        (key_param->key_mode != HKS_ALG_GCM) &&
        (key_param->key_mode != HKS_ALG_CBC))
        return HKS_ERROR_NOT_SUPPORTED;

    if ((key_param->key_len != HKS_MAX_KEY_LEN_128) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_192) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_256))
        return HKS_ERROR_NOT_SUPPORTED;

    /* key_pad checking: CCM/GCM-PKCS7; CBC-PCKS7/NONE */
    if (((key_param->key_mode == HKS_ALG_CCM) || (key_param->key_mode == HKS_ALG_GCM)) &&
        (key_param->key_pad != HKS_PADDING_PKCS7))
        return HKS_ERROR_NOT_SUPPORTED;
    if ((key_param->key_mode == HKS_ALG_CBC) &&
        ((key_param->key_pad != HKS_PADDING_PKCS7) && (key_param->key_pad != HKS_PADDING_NONE)))
        return HKS_ERROR_NOT_SUPPORTED;

    if (((key_param->key_usage & HKS_KEY_USAGE_ENCRYPT) == 0) &&
        ((key_param->key_usage & HKS_KEY_USAGE_DECRYPT) == 0))
        return HKS_ERROR_NOT_SUPPORTED;

    return HKS_STATUS_OK;
}

static int32_t hks_check_symmetric_data_info_aead(const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *input_text,
    const struct hks_blob *output_text, int32_t operation_mode)
{
    hks_if_true_return_error(((crypt_param->aad.data == NULL) || (crypt_param->nonce.data == NULL) ||
        (crypt_param->aad.size == 0)), HKS_ERROR_INVALID_ARGUMENT);

    if (key_param->key_mode == HKS_ALG_GCM) {
        hks_if_true_return_error((crypt_param->nonce.size < HKS_GCM_MIN_IV_LENGTH), HKS_ERROR_INVALID_ARGUMENT);
    } else if (key_param->key_mode == HKS_ALG_CCM) {
        hks_if_true_return_error(((crypt_param->nonce.size < HKS_CCM_MIN_IV_LENGTH) ||
            (crypt_param->nonce.size > HKS_CCM_MAX_IV_LENGTH) || (crypt_param->aad.size > HKS_CCM_MAX_AAD_LENGTH)),
            HKS_ERROR_INVALID_ARGUMENT);
    } else {
        return HKS_ERROR_NOT_SUPPORTED;
    }

    /* operation_mode is only encrypt and decrypt */
    if (operation_mode == HKS_OPERATION_MODE_ENCRYPT) {
        hks_if_true_return_error(((input_text->size > (UINT32_MAX - HKS_SALT_MAX_SIZE)) ||
            (output_text->size < (input_text->size + HKS_SALT_MAX_SIZE))), HKS_ERROR_INVALID_ARGUMENT);
    } else if (operation_mode == HKS_OPERATION_MODE_DECRYPT) {
        hks_if_true_return_error(((input_text->size <= HKS_SALT_MAX_SIZE) ||
            (output_text->size < (input_text->size - HKS_SALT_MAX_SIZE))), HKS_ERROR_INVALID_ARGUMENT);
    } else {
        return HKS_ERROR_NOT_SUPPORTED;
    }

    return HKS_STATUS_OK;
}

static int32_t hks_check_symmetric_data_info_cbc(const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *input_text,
    const struct hks_blob *ouput_text, int32_t operation_mode)
{
    hks_if_true_return_error(((crypt_param->nonce.size != HKS_AES_IV_LENGTH) ||
        (crypt_param->nonce.data == NULL)), HKS_ERROR_INVALID_ARGUMENT);

    /* operation_mode is only encrypt and decrypt */
    if (operation_mode == HKS_OPERATION_MODE_ENCRYPT) {
        if (key_param->key_pad == HKS_PADDING_PKCS7) {
            hks_if_true_return_error(((input_text->size > (UINT32_MAX - HKS_SALT_MAX_SIZE)) ||
                (ouput_text->size < (input_text->size + HKS_SALT_MAX_SIZE))),
                HKS_ERROR_INVALID_ARGUMENT);
        } else if (key_param->key_pad == HKS_PADDING_NONE) {
            hks_if_true_return_error(((ouput_text->size < input_text->size) ||
                ((input_text->size % HKS_AES_ENCRYPT_BLOCK_SIZE) != 0)), HKS_ERROR_INVALID_ARGUMENT);
        } else {
            return HKS_ERROR_INVALID_ARGUMENT;
        }
    } else if (operation_mode == HKS_OPERATION_MODE_DECRYPT) {
        hks_if_true_return_error(((ouput_text->size < input_text->size) ||
            ((input_text->size % HKS_AES_ENCRYPT_BLOCK_SIZE) != 0)), HKS_ERROR_INVALID_ARGUMENT);
    } else {
        return HKS_ERROR_NOT_SUPPORTED;
    }

    return HKS_STATUS_OK;
}

int32_t hks_check_symmetric_data_info(const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *input_text,
    const struct hks_blob *output_text, int32_t operation_mode)
{
    hks_if_true_return_error(((key_param == NULL) || (input_text == NULL) || (output_text == NULL) ||
        (crypt_param == NULL)), HKS_ERROR_NULL_POINTER);

    hks_if_true_return_error(((input_text->size == 0) || (output_text->size == 0) ||
        (input_text->data == NULL) || (output_text->data == NULL)), HKS_ERROR_INVALID_ARGUMENT);

    int32_t status;

    /*
     * AES_GCM and AES_CCM need both iv and aad info, cipher_text need add tag length
     * AES_CBC pkcs7 need iv info, no need aad info; no-padding need 16
     */
    switch (key_param->key_mode) {
    case HKS_ALG_GCM: /* GCM and CCM mode: the same process */
    case HKS_ALG_CCM:
        status = hks_check_symmetric_data_info_aead(key_param, crypt_param, input_text, output_text, operation_mode);
        break;
    case HKS_ALG_CBC:
        status = hks_check_symmetric_data_info_cbc(key_param, crypt_param, input_text, output_text, operation_mode);
        break;
    default:
        return HKS_ERROR_NOT_SUPPORTED;
    }

    return status;
}

static int32_t hks_mbedtls_symmetric_aead_setup(const struct hks_blob *key,
    const struct hks_key_param *key_param, struct hks_aead_operation *operation)
{
    /* the params have been checked by caller function */
    uint32_t key_bits = key_param->key_len;
    const mbedtls_cipher_info_t *cipher_info = NULL;
    int32_t status;

    if (key_param->key_mode == HKS_ALG_GCM) {
        cipher_info = mbedtls_cipher_info_from_values(MBEDTLS_CIPHER_ID_AES, (int)key_bits, MBEDTLS_MODE_GCM);

        if (cipher_info == NULL)
            return HKS_ERROR_NULL_POINTER;

        mbedtls_gcm_init(&operation->gcm);
        status = mbedtls_gcm_setkey(&operation->gcm, MBEDTLS_CIPHER_ID_AES, key->data, (unsigned int)key_bits);

        if (status != HKS_STATUS_OK) {
            mbedtls_gcm_free(&operation->gcm);
            return mbedtls_to_hks_error(status);
        }
    } else if (key_param->key_mode == HKS_ALG_CCM) {
        cipher_info = mbedtls_cipher_info_from_values(MBEDTLS_CIPHER_ID_AES, (int)key_bits, MBEDTLS_MODE_CCM);

        if (cipher_info == NULL)
            return HKS_ERROR_NULL_POINTER;

        mbedtls_ccm_init(&operation->ccm);
        status = mbedtls_ccm_setkey(&operation->ccm, MBEDTLS_CIPHER_ID_AES, key->data, (unsigned int)key_bits);

        if (status != HKS_STATUS_OK) {
            mbedtls_ccm_free(&operation->ccm);
            return mbedtls_to_hks_error(status);
        }
    } else {
        return HKS_ERROR_NOT_SUPPORTED;
    }

    return HKS_STATUS_OK;
}

static int32_t hks_mbedtls_symmetric_aead_encrypt(const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag, struct hks_aead_operation *operation)
{
    /* the params have been checked by caller function */
    int32_t status;
    uint8_t *tag = cipher_text_with_tag->data + plain_text->size;
    size_t tag_len = HKS_MBEDTLS_TAG_LENGTH;

    if (key_param->key_mode == HKS_ALG_GCM)
        status = mbedtls_gcm_crypt_and_tag(&operation->gcm, MBEDTLS_GCM_ENCRYPT, plain_text->size,
            crypt_param->nonce.data, crypt_param->nonce.size, crypt_param->aad.data,
            crypt_param->aad.size, plain_text->data, cipher_text_with_tag->data, tag_len, tag);
    else if (key_param->key_mode == HKS_ALG_CCM)
        status = mbedtls_ccm_encrypt_and_tag(&operation->ccm, plain_text->size, crypt_param->nonce.data,
            crypt_param->nonce.size, crypt_param->aad.data, crypt_param->aad.size, plain_text->data,
            cipher_text_with_tag->data, tag, tag_len);
    else
        return HKS_ERROR_NOT_SUPPORTED;

    if ((status != HKS_SUCCESS) && (cipher_text_with_tag->size != 0))
        (void)memset_s(cipher_text_with_tag->data, cipher_text_with_tag->size, 0, cipher_text_with_tag->size);

    if (status == HKS_SUCCESS)
        cipher_text_with_tag->size = plain_text->size + tag_len; /* plain size is smaller than max_uint32 - 16 */

    return mbedtls_to_hks_error(status);
}

static int32_t hks_mbedtls_symmetric_aead_decrypt(const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *cipher_text_with_tag,
    struct hks_blob *plain_text, struct hks_aead_operation *operation)
{
    /* the params have been checked by caller function */
    const uint8_t *tag = NULL;
    size_t tag_length = HKS_MBEDTLS_TAG_LENGTH;

    int32_t status = hks_aead_unpadded_locate_tag(tag_length, cipher_text_with_tag->data, cipher_text_with_tag->size,
        plain_text->size, &tag);

    if (status != HKS_SUCCESS)
        return status;

    if (key_param->key_mode == HKS_ALG_GCM)
        status = mbedtls_gcm_auth_decrypt(&operation->gcm, cipher_text_with_tag->size - tag_length,
            crypt_param->nonce.data, crypt_param->nonce.size, crypt_param->aad.data, crypt_param->aad.size,
            tag, tag_length, cipher_text_with_tag->data, plain_text->data);
    else if (key_param->key_mode == HKS_ALG_CCM)
        status = mbedtls_ccm_auth_decrypt(&operation->ccm, cipher_text_with_tag->size - tag_length,
            crypt_param->nonce.data, crypt_param->nonce.size, crypt_param->aad.data, crypt_param->aad.size,
            cipher_text_with_tag->data, plain_text->data, tag, tag_length);
    else
        return HKS_ERROR_NOT_SUPPORTED;

    if ((status != HKS_SUCCESS) && (plain_text->size != 0))
        (void)memset_s(plain_text->data, plain_text->size, 0, plain_text->size);

    if (status == HKS_SUCCESS)
        plain_text->size = cipher_text_with_tag->size - tag_length; /* cipher size is bigger than 16 */

    return mbedtls_to_hks_error(status);
}

static int32_t hks_mbedtls_symmetric_aead_reset(const struct hks_key_param *key_param,
    struct hks_aead_operation *operation)
{
    /* the params have been checked by caller function */
    if (key_param->key_mode == HKS_ALG_GCM)
        mbedtls_gcm_free(&operation->gcm);
    else if (key_param->key_mode == HKS_ALG_CCM)
        mbedtls_ccm_free(&operation->ccm);
    else
        return HKS_ERROR_NOT_SUPPORTED;

    return HKS_STATUS_OK;
}

static int32_t hks_mbedtls_symmetric_cipher_setup(const struct hks_blob *key,
    const struct hks_key_param *key_param, mbedtls_cipher_context_t *cipher_ctx, int32_t operation_mode)
{
    /* the params have been checked by caller function */
    uint32_t key_bits = key_param->key_len;
    const mbedtls_cipher_info_t *cipher_info = NULL;

    if (key_param->key_mode == HKS_ALG_CBC)
        cipher_info = mbedtls_cipher_info_from_values(MBEDTLS_CIPHER_ID_AES, (int)key_bits, MBEDTLS_MODE_CBC);
    else
        return HKS_ERROR_NOT_SUPPORTED;

    if (cipher_info == NULL)
        return HKS_ERROR_NULL_POINTER;

    mbedtls_cipher_init(cipher_ctx);

    int32_t status = mbedtls_cipher_setup(cipher_ctx, cipher_info);

    if (status != HKS_SUCCESS) {
        mbedtls_cipher_free(cipher_ctx);
        return mbedtls_to_hks_error(status);
    }

    if (operation_mode == HKS_OPERATION_MODE_ENCRYPT)
        status = mbedtls_cipher_setkey(cipher_ctx, key->data, (int)key_bits, MBEDTLS_ENCRYPT);
    else if (operation_mode == HKS_OPERATION_MODE_DECRYPT)
        status = mbedtls_cipher_setkey(cipher_ctx, key->data, (int)key_bits, MBEDTLS_DECRYPT);

    if (status != HKS_SUCCESS)
        mbedtls_cipher_free(cipher_ctx);

    return mbedtls_to_hks_error(status);
}

static int32_t hks_mbedtls_symmetric_cbc_nopadding_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_blob *iv,
    const struct hks_blob *plain_text, struct hks_blob *cipher_text_with_tag)
{
    /* the params have been checked by caller function */
    if ((plain_text->size % HKS_AES_ENCRYPT_BLOCK_SIZE) != 0)
        return HKS_ERROR_INVALID_ARGUMENT;

    mbedtls_aes_context aes_context;
    mbedtls_aes_init(&aes_context);
    int32_t status = mbedtls_aes_setkey_enc(&aes_context, key->data, key_param->key_len);

    if (status != HKS_SUCCESS)
        goto exit;

    status = mbedtls_aes_crypt_cbc(&aes_context, MBEDTLS_AES_ENCRYPT, plain_text->size, iv->data,
        plain_text->data, cipher_text_with_tag->data);

    if ((status != HKS_SUCCESS) && (cipher_text_with_tag->size != 0))
        (void)memset_s(cipher_text_with_tag->data, cipher_text_with_tag->size, 0, cipher_text_with_tag->size);

    if (status == HKS_SUCCESS)
        cipher_text_with_tag->size = plain_text->size;

exit:
    mbedtls_aes_free(&aes_context);
    return mbedtls_to_hks_error(status);
}

static int32_t hks_mbedtls_symmetric_cbc_nopadding_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_blob *iv,
    const struct hks_blob *cipher_text_with_tag, struct hks_blob *plain_text)
{
    /* the params have been checked by caller function */
    if ((cipher_text_with_tag->size % HKS_AES_ENCRYPT_BLOCK_SIZE) != 0)
        return HKS_ERROR_INVALID_ARGUMENT;

    mbedtls_aes_context aes_context;
    mbedtls_aes_init(&aes_context);
    int32_t status = mbedtls_aes_setkey_dec(&aes_context, key->data, key_param->key_len);

    if (status != HKS_SUCCESS)
        goto exit;

    status = mbedtls_aes_crypt_cbc(&aes_context, MBEDTLS_AES_DECRYPT, cipher_text_with_tag->size, iv->data,
        cipher_text_with_tag->data, plain_text->data);

    if ((status != HKS_SUCCESS) && (plain_text->size != 0))
        (void)memset_s(plain_text->data, plain_text->size, 0, plain_text->size);

    if (status == HKS_SUCCESS)
        plain_text->size = cipher_text_with_tag->size;

exit:
    mbedtls_aes_free(&aes_context);
    return mbedtls_to_hks_error(status);
}

static int32_t hks_mbedtls_symmetric_cipher_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_blob *iv,
    const struct hks_blob *plain_text, struct hks_blob *cipher_text_with_tag)
{
    /* the params have been checked by caller function */
    mbedtls_cipher_context_t cipher_ctx;
    size_t encrypted_len = 0;

    int32_t status = hks_mbedtls_symmetric_cipher_setup(key, key_param, &cipher_ctx, HKS_OPERATION_MODE_ENCRYPT);

    if (status != HKS_STATUS_OK)
        return status;

    status = mbedtls_cipher_crypt(&cipher_ctx, iv->data, iv->size, plain_text->data, plain_text->size,
        cipher_text_with_tag->data, &encrypted_len);

    if ((status != HKS_SUCCESS) && (cipher_text_with_tag->size != 0))
        (void)memset_s(cipher_text_with_tag->data, cipher_text_with_tag->size, 0, cipher_text_with_tag->size);

    if (status == HKS_SUCCESS)
        cipher_text_with_tag->size = encrypted_len;

    mbedtls_cipher_free(&cipher_ctx);
    return mbedtls_to_hks_error(status);
}

static int32_t hks_mbedtls_symmetric_cipher_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_blob *iv,
    const struct hks_blob *cipher_text_with_tag, struct hks_blob *plain_text)
{
    /* the params have been checked by caller function */
    mbedtls_cipher_context_t cipher_ctx;
    size_t decrypted_len = 0;

    int32_t status = hks_mbedtls_symmetric_cipher_setup(key, key_param, &cipher_ctx, HKS_OPERATION_MODE_DECRYPT);

    if (status != HKS_STATUS_OK)
        return status;

    status = mbedtls_cipher_crypt(&cipher_ctx, iv->data, iv->size, cipher_text_with_tag->data,
        cipher_text_with_tag->size, plain_text->data, &decrypted_len);

    if ((status != HKS_SUCCESS) && (plain_text->size != 0))
        (void)memset_s(plain_text->data, plain_text->size, 0, plain_text->size);

    if (status == HKS_SUCCESS)
        plain_text->size = decrypted_len;

    mbedtls_cipher_free(&cipher_ctx);
    return mbedtls_to_hks_error(status);
}

int32_t hks_mbedtls_symmetric_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text, struct hks_blob *cipher_text_with_tag)
{
    if ((key == NULL) || (key->data == NULL) || (key_param == NULL))
        return HKS_ERROR_NULL_POINTER;

    if (key->size != (key_param->key_len / HKS_BITS_PER_BYTES))
        return HKS_ERROR_INVALID_ARGUMENT;

    int32_t status = hks_check_symmetric_data_info(key_param, crypt_param, plain_text,
        cipher_text_with_tag, HKS_OPERATION_MODE_ENCRYPT);

    if (status != HKS_STATUS_OK)
        return status;

    switch (key_param->key_mode) {
    case HKS_ALG_GCM: /* GCM and CCM mode: the same process */
    case HKS_ALG_CCM: {
        struct hks_aead_operation operation;

        (void)memset_s(&operation, sizeof(operation), 0, sizeof(operation));
        status = hks_mbedtls_symmetric_aead_setup(key, key_param, &operation);
        if (status != HKS_STATUS_OK)
            return status;

        status = hks_mbedtls_symmetric_aead_encrypt(key_param, crypt_param, plain_text,
            cipher_text_with_tag, &operation);

        /* no matter encrypt success or fail, reset is needed */
        (void)hks_mbedtls_symmetric_aead_reset(key_param, &operation);
        break;
    }
    case HKS_ALG_CBC: {
        /* cbc will change the input param, need copy nonce.data from crypt_param */
        uint8_t iv_data[HKS_AES_IV_LENGTH];
        struct hks_blob iv = { HKS_BLOB_TYPE_IV, iv_data, sizeof(iv_data) };

        if (memcpy_s(iv.data, iv.size, crypt_param->nonce.data, crypt_param->nonce.size) != EOK)
            return HKS_ERROR_BAD_STATE;

        if (key_param->key_pad == HKS_PADDING_NONE)
            status = hks_mbedtls_symmetric_cbc_nopadding_encrypt(key, key_param, &iv, plain_text,
                cipher_text_with_tag);
        else if (key_param->key_pad == HKS_PADDING_PKCS7)
            status = hks_mbedtls_symmetric_cipher_encrypt(key, key_param, &iv, plain_text, cipher_text_with_tag);
        else
            return HKS_ERROR_NOT_SUPPORTED;
        break;
    }
    default:
        return HKS_ERROR_NOT_SUPPORTED;
    }

    return status;
}

int32_t hks_mbedtls_symmetric_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    const struct hks_blob *cipher_text_with_tag, struct hks_blob *plain_text)
{
    if ((key == NULL) || (key->data == NULL) || (key_param == NULL))
        return HKS_ERROR_NULL_POINTER;

    if (key->size != (key_param->key_len / HKS_BITS_PER_BYTES))
        return HKS_ERROR_INVALID_ARGUMENT;

    int32_t status = hks_check_symmetric_data_info(key_param, crypt_param, cipher_text_with_tag,
        plain_text, HKS_OPERATION_MODE_DECRYPT);

    if (status != HKS_STATUS_OK)
        return status;

    switch (key_param->key_mode) {
    case HKS_ALG_GCM: /* GCM and CCM mode: the same process */
    case HKS_ALG_CCM: {
        struct hks_aead_operation operation;

        (void)memset_s(&operation, sizeof(operation), 0, sizeof(operation));
        status = hks_mbedtls_symmetric_aead_setup(key, key_param, &operation);
        if (status != HKS_STATUS_OK)
            return status;

        status = hks_mbedtls_symmetric_aead_decrypt(key_param, crypt_param, cipher_text_with_tag,
            plain_text, &operation);

        /* no matter decrypt success or fail, reset is needed */
        (void)hks_mbedtls_symmetric_aead_reset(key_param, &operation);
        break;
    }
    case HKS_ALG_CBC: {
        /* cbc will change the input param, need copy nonce.data from crypt_param */
        uint8_t iv_data[HKS_AES_IV_LENGTH];
        struct hks_blob iv = { HKS_BLOB_TYPE_IV, iv_data, sizeof(iv_data) };

        if (memcpy_s(iv.data, iv.size, crypt_param->nonce.data, crypt_param->nonce.size) != EOK)
            return HKS_ERROR_BAD_STATE;

        if (key_param->key_pad == HKS_PADDING_NONE)
            status = hks_mbedtls_symmetric_cbc_nopadding_decrypt(key, key_param, &iv,
                cipher_text_with_tag, plain_text);
        else if (key_param->key_pad == HKS_PADDING_PKCS7)
            status = hks_mbedtls_symmetric_cipher_decrypt(key, key_param, &iv, cipher_text_with_tag, plain_text);
        else
            return HKS_ERROR_NOT_SUPPORTED;
        break;
    }
    default:
        return HKS_ERROR_NOT_SUPPORTED;
    }

    return status;
}

static int32_t check_aes_cbc_encrypt_args(const struct hks_blob *plain_text,
    const struct hks_blob *cipher_text, const struct hks_blob *iv_blob, uint32_t padding_mode)
{
    if ((plain_text == NULL) || (cipher_text == NULL) || (iv_blob == NULL) ||
        (plain_text->data == NULL) || (cipher_text->data == NULL) || (iv_blob->data == NULL))
        return HKS_ERROR_NULL_POINTER;

    if ((plain_text->size == 0) || (iv_blob->size != HKS_AES_IV_LENGTH))
        return HKS_ERROR_INVALID_ARGUMENT;

    if ((padding_mode == HKS_PADDING_PKCS7) && ((plain_text->size > (UINT32_MAX - HKS_SALT_MAX_SIZE)) ||
        (cipher_text->size < (plain_text->size + HKS_SALT_MAX_SIZE))))
        return HKS_ERROR_INVALID_ARGUMENT;

    if ((padding_mode == HKS_PADDING_NONE) && ((cipher_text->size < plain_text->size) ||
        ((plain_text->size % HKS_AES_ENCRYPT_BLOCK_SIZE) != 0)))
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_SUCCESS;
}

int32_t hks_aes_cbc_encrypt_data(const struct hks_blob *plain_text,
    struct hks_blob *cipher_text, struct hks_blob *iv_blob, uint32_t padding_mode)
{
    int32_t status = check_aes_cbc_encrypt_args(plain_text, cipher_text, iv_blob, padding_mode);

    if (status != HKS_SUCCESS)
        return status;

    struct hks_key_param key_param;
    struct hks_crypt_param crypt_param;

    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    (void)memset_s(&crypt_param, sizeof(crypt_param), 0, sizeof(crypt_param));

    struct hks_blob kek = HKS_BLOB_DEFAULT_VALUE;
    struct hks_blob iv = HKS_BLOB_DEFAULT_VALUE;
    status = hks_blob_init(&kek, sizeof(uint8_t), HKS_RKC_KEK_LEN, HKS_BLOB_TYPE_KEY);

    if (status != HKS_SUCCESS)
        goto exit;

    status = hks_blob_init(&iv, sizeof(uint8_t), HKS_AES_IV_LENGTH, HKS_BLOB_TYPE_IV);
    if (status != HKS_SUCCESS)
        goto exit;

    status = hks_gen_random(iv.data, HKS_AES_IV_LENGTH);
    if (status != HKS_SUCCESS)
        goto exit;

    status = hks_rkc_get_kek(&iv, &kek);
    if (status != HKS_SUCCESS)
        goto exit;

    if (memcpy_s(iv_blob->data, iv_blob->size, iv.data, HKS_AES_IV_LENGTH) != EOK) {
        status = HKS_ERROR_BAD_STATE;
        goto exit;
    }

    key_param.key_len = HKS_MAX_KEY_LEN_256;
    key_param.key_type = HKS_KEY_TYPE_AES;
    key_param.key_mode = HKS_ALG_CBC;
    key_param.key_pad = padding_mode;

    status = hks_blob_init(&crypt_param.nonce, sizeof(uint8_t), iv.size, HKS_BLOB_TYPE_IV);
    if (status != HKS_SUCCESS)
        goto exit;

    if (memcpy_s(crypt_param.nonce.data, crypt_param.nonce.size, iv.data, iv.size) != EOK) {
        status = HKS_ERROR_BAD_STATE;
        goto exit;
    }

    status = hks_mbedtls_symmetric_encrypt(&kek, &key_param, &crypt_param, plain_text, cipher_text);

exit:
    hks_blob_destroy(&kek);
    hks_blob_destroy(&iv);
    hks_blob_destroy(&crypt_param.nonce);
    return status;
}

static int32_t check_aes_cbc_decrypt_args(const struct hks_blob *cipher_text,
    const struct hks_blob *plain_text, const struct hks_blob *iv_blob, uint32_t padding_mode)
{
    if ((plain_text == NULL) || (cipher_text == NULL) || (iv_blob == NULL) ||
        (plain_text->data == NULL) || (cipher_text->data == NULL) || (iv_blob->data == NULL))
        return HKS_ERROR_NULL_POINTER;

    if ((iv_blob->size != HKS_AES_IV_LENGTH) || (cipher_text->size == 0) || (plain_text->size < cipher_text->size))
        return HKS_ERROR_INVALID_ARGUMENT;

    if ((padding_mode == HKS_PADDING_NONE) && ((cipher_text->size % HKS_AES_ENCRYPT_BLOCK_SIZE) != 0))
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_SUCCESS;
}

int32_t hks_aes_cbc_decrypt_data(const struct hks_blob *cipher_text,
    struct hks_blob *plain_text, const struct hks_blob *iv_blob, uint32_t padding_mode)
{
    int32_t status = check_aes_cbc_decrypt_args(cipher_text, plain_text, iv_blob, padding_mode);

    if (status != HKS_SUCCESS)
        return status;

    struct hks_blob kek = HKS_BLOB_DEFAULT_VALUE;
    struct hks_key_param key_param;
    struct hks_crypt_param crypt_param;

    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    (void)memset_s(&crypt_param, sizeof(crypt_param), 0, sizeof(crypt_param));

    status = hks_blob_init(&kek, sizeof(uint8_t), HKS_RKC_KEK_LEN, HKS_BLOB_TYPE_KEY);

    if (status != HKS_SUCCESS)
        goto exit;

    status = hks_rkc_get_kek(iv_blob, &kek);
    if (status != HKS_SUCCESS)
        goto exit;

    key_param.key_len = HKS_MAX_KEY_LEN_256;
    key_param.key_type = HKS_KEY_TYPE_AES;
    key_param.key_mode = HKS_ALG_CBC;
    key_param.key_pad = padding_mode;

    status = hks_blob_init(&crypt_param.nonce, sizeof(uint8_t), iv_blob->size, HKS_BLOB_TYPE_IV);
    if (status != HKS_SUCCESS)
        goto exit;

    if (memcpy_s(crypt_param.nonce.data, crypt_param.nonce.size, iv_blob->data, iv_blob->size) != EOK) {
        status = HKS_ERROR_BAD_STATE;
        goto exit;
    }

    status = hks_mbedtls_symmetric_decrypt(&kek, &key_param, &crypt_param, cipher_text, plain_text);

exit:
    hks_blob_destroy(&kek);
    hks_blob_destroy(&crypt_param.nonce);
    return status;
}

int32_t hks_efuse_root_salt_read(uint8_t *root_key_salt_data, uint32_t root_key_salt_len)
{
    if (root_key_salt_data == NULL)
        return HKS_ERROR_NULL_POINTER;

    /* 1. get efuse id size and check wether buffer is enough */
    hi_u32 efuse_size = hi_efuse_get_id_size(HI_EFUSE_TEE_SALT_RW_ID);

    if (efuse_size == HI_ERR_EFUSE_INVALIDATE_ID)
        return HKS_ERROR_EFUSE_READ_FAIL;

    if (root_key_salt_len != (efuse_size / HKS_BITS_PER_BYTES))
        return HKS_ERROR_INVALID_ARGUMENT;

    /* 2. read efuse */
    hi_u32 ret = hi_efuse_read(HI_EFUSE_TEE_SALT_RW_ID, (hi_u8 *)root_key_salt_data, (hi_u8)root_key_salt_len);

    if (ret != HI_ERR_SUCCESS) {
        log_error("failed to read EFUSE! ret is 0x%x\n", ret);
        return HKS_ERROR_EFUSE_READ_FAIL;
    }

    return HKS_STATUS_OK;
}
#endif

int32_t hks_is_valid_alias(const struct hks_blob *alias)
{
    if (alias == NULL)
        return HKS_ERROR_NULL_POINTER;
    if (alias->data == NULL)
        return HKS_ERROR_INVALID_ARGUMENT;
    if ((alias->size > HKS_ALIAS_MAX_SIZE) || (alias->size == 0))
        return HKS_ERROR_INVALID_ARGUMENT;
    if (alias->type != HKS_BLOB_TYPE_ALIAS)
        return HKS_ERROR_INVALID_ARGUMENT;
    return HKS_STATUS_OK;
}

#ifndef _SUPPORT_HKS_TEE_
int32_t hks_is_valid_auth_id(const struct hks_key_param *key_param)
{
    if (key_param == NULL)
        return HKS_ERROR_NULL_POINTER;

    if (key_param->key_auth_id.data == NULL)
        return HKS_ERROR_NULL_POINTER;

    if ((key_param->key_auth_id.size == 0) ||
        (key_param->key_auth_id.size > HKS_AUTH_ID_MAX_SIZE))
        return HKS_ERROR_INVALID_ARGUMENT;

    if (key_param->key_auth_id.type != HKS_BLOB_TYPE_AUTH_ID)
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_STATUS_OK;
}

int32_t hks_cpy_key_param(struct hks_key_param *dst,
    const struct hks_key_param *src)
{
    if (dst == NULL || src == NULL)
        return HKS_ERROR_NULL_POINTER;

    int32_t status = hks_is_valid_auth_id(src);

    if (status != HKS_STATUS_OK)
        return status;

    if ((dst->key_auth_id.data == NULL) ||
        (dst->key_auth_id.size < src->key_auth_id.size))
        return HKS_ERROR_INSUFFICIENT_CAPACITY;

    dst->key_domain = src->key_domain;
    dst->key_len = src->key_len;
    dst->key_mode = src->key_mode;
    dst->key_pad = src->key_pad;
    dst->key_role = src->key_role;
    dst->key_type = src->key_type;
    dst->key_usage = src->key_usage;
    dst->key_auth_id.type = src->key_auth_id.type;
    if (memcpy_s(dst->key_auth_id.data, src->key_auth_id.size,
        src->key_auth_id.data, src->key_auth_id.size) != EOK)
        return HKS_ERROR_BAD_STATE;
    dst->key_auth_id.size = src->key_auth_id.size;
    return HKS_STATUS_OK;
}

void hks_key_param_destroy(struct hks_key_param *pram)
{
    if (pram == NULL)
        return;

    if (pram->key_auth_id.data != NULL)
        hks_free_ptr(pram->key_auth_id.data);

    pram->key_auth_id.data = NULL;
}
#else
int32_t hks_is_valid_auth_id(const struct hks_key_param *key_param)
{
    if (key_param == NULL)
        return HKS_ERROR_NULL_POINTER;

    if (((key_param->key_param_ext.key_auth_id.size > 0) &&
        (key_param->key_param_ext.key_auth_id.data == NULL)) ||
        ((key_param->key_param_ext.key_auth_id.size == 0) &&
        (key_param->key_param_ext.key_auth_id.data != NULL)))
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_STATUS_OK;
}

int32_t hks_cpy_key_param(struct hks_key_param *dst,
    const struct hks_key_param *src)
{
    if (dst == NULL || src == NULL)
        return HKS_ERROR_NULL_POINTER;

    int32_t status = hks_is_valid_auth_id(src);

    if (status != HKS_STATUS_OK)
        return status;

    if ((dst->key_param_ext.key_auth_id.data == NULL) ||
        (dst->key_param_ext.key_auth_id.size < src->key_param_ext.key_auth_id.size))
        return HKS_ERROR_INSUFFICIENT_CAPACITY;

    dst->key_domain = src->key_domain;
    dst->key_len = src->key_len;
    dst->key_mode = src->key_mode;
    dst->key_pad = src->key_pad;
    dst->key_param_ext.key_role = src->key_param_ext.key_role;
    dst->key_type = src->key_type;
    dst->key_usage = src->key_usage;
    dst->key_param_ext.key_auth_id.type =
        src->key_param_ext.key_auth_id.type;
    if (memcpy_s(dst->key_param_ext.key_auth_id.data,
        src->key_param_ext.key_auth_id.size,
        src->key_param_ext.key_auth_id.data,
        src->key_param_ext.key_auth_id.size) != EOK)
        return HKS_ERROR_BAD_STATE;
    dst->key_param_ext.key_auth_id.size =
        src->key_param_ext.key_auth_id.size;
    return HKS_STATUS_OK;
}

void hks_key_param_destroy(struct hks_key_param *pram)
{
    if (pram == NULL)
        return;

    if (pram->key_param_ext.key_auth_id.data != NULL)
        hks_free_ptr(pram->key_param_ext.key_auth_id.data);

    pram->key_param_ext.key_auth_id.data = NULL;
}

int32_t hks_is_valid_data_creator(const struct hks_key_param *key_param)
{
    if (key_param == NULL)
        return HKS_ERROR_NULL_POINTER;

    if (((key_param->key_param_ext.data_creator.size > 0) &&
        (key_param->key_param_ext.data_creator.data == NULL)) ||
        ((key_param->key_param_ext.data_creator.size == 0) &&
        (key_param->key_param_ext.data_creator.data != NULL)))
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_STATUS_OK;
}

int32_t hks_is_valid_data_owner(const struct hks_key_param *key_param)
{
    if (key_param == NULL)
        return HKS_ERROR_NULL_POINTER;
    if (((key_param->key_param_ext.data_owner.size > 0) &&
        (key_param->key_param_ext.data_owner.data == NULL)) ||
        ((key_param->key_param_ext.data_owner.size == 0) &&
        (key_param->key_param_ext.data_owner.data != NULL)))
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_STATUS_OK;
}

int32_t hks_is_valid_ext_info(const struct hks_key_param *key_param)
{
    if (key_param == NULL)
        return HKS_ERROR_NULL_POINTER;
    if (((key_param->key_param_ext.ext_info.size > 0) &&
        (key_param->key_param_ext.ext_info.data == NULL)) ||
        ((key_param->key_param_ext.ext_info.size == 0) &&
        (key_param->key_param_ext.ext_info.data != NULL)))
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_STATUS_OK;
}
#endif

void hks_check_return_code(int32_t s, int32_t *ret)
{
    if (ret == NULL)
        return;
    if (s == HKS_STATUS_OK) {
        *ret = s;
        return;
    }

    log_error("error : %d.\n", s);
    if (((s <= HKS_FAILURE) && (s > HKS_ERROR_MBEDTLS_RANGE_MIN)) ||
        ((s <= HKS_ERROR_NULL_POINTER) && (s > HKS_ERROR_RANGE_MIN)))
        *ret = s;
    else
        *ret = HKS_ERROR_INTERNAL_UNKOWN;
}

static int32_t check_mbedtls_aead_args(const struct hks_blob *key, const struct hks_key_param *key_param,
    const struct hks_aead_data *aead_data, const size_t *output_length)
{
    if ((key == NULL) || (key_param == NULL) || (aead_data == NULL) ||
        (output_length == NULL) || (aead_data->nonce == NULL) ||
        (aead_data->additional_data == NULL) || (aead_data->plaintext == NULL) ||
        (aead_data->ciphertext == NULL))
        return HKS_ERROR_NULL_POINTER;

    if ((aead_data->nonce_length == 0) || (aead_data->additional_data_length == 0) ||
        (aead_data->ciphertext_length <= HKS_SALT_MAX_SIZE) || (aead_data->plaintext_length == 0))
        return HKS_ERROR_INVALID_ARGUMENT;

    if (key_param->key_mode != HKS_ALG_GCM)
        return HKS_ERROR_NOT_SUPPORTED;

    return HKS_SUCCESS;
}

int32_t hks_mbedtls_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    struct hks_aead_data *aead_data, size_t *plaintext_output_length)
{
    int32_t status = check_mbedtls_aead_args(key, key_param, aead_data, plaintext_output_length);

    if (status != HKS_SUCCESS)
        return status;

    struct hks_aead_operation operation;
    const uint8_t *tag = NULL;

    *plaintext_output_length = 0;

    status = hks_aead_setup(key, key_param, &operation);

    if (status != HKS_SUCCESS)
        return status;

    if (operation.core_alg == HKS_ALG_GCM) {
        status = hks_aead_unpadded_locate_tag(operation.tag_length,
            aead_data->ciphertext, aead_data->ciphertext_length, aead_data->plaintext_length, &tag);
        if (status != HKS_SUCCESS)
            goto exit;

        /* length had been checked in hks_aead_unpadded_locate_tag */
        status = mbedtls_gcm_auth_decrypt(&operation.gcm, aead_data->ciphertext_length - operation.tag_length,
            aead_data->nonce, aead_data->nonce_length, aead_data->additional_data,
            aead_data->additional_data_length, tag, operation.tag_length, aead_data->ciphertext,
            aead_data->plaintext);
    } else {
        status = HKS_ERROR_NOT_SUPPORTED;
        goto exit;
    }
    if (status != HKS_SUCCESS && aead_data->plaintext_length != 0)
        (void)memset_s(aead_data->plaintext, aead_data->plaintext_length, 0, aead_data->plaintext_length);
exit:
    mbedtls_gcm_free(&(operation.gcm));
    if (status == HKS_SUCCESS)
        *plaintext_output_length =
        aead_data->ciphertext_length - operation.tag_length;
    return mbedtls_to_hks_error(status);
}

int32_t hks_mbedtls_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, struct hks_aead_data *aead_data,
    size_t *ciphertext_output_length)
{
    int32_t status = check_mbedtls_aead_args(key, key_param, aead_data, ciphertext_output_length);

    if (status != HKS_SUCCESS)
        return status;

    struct hks_aead_operation operation;

    *ciphertext_output_length = 0;
    status = hks_aead_setup(key, key_param, &operation);
    if (status != HKS_SUCCESS)
        return status;

    /* For all supported modes, the tag is at the end of the ciphertext. */
    if (aead_data->ciphertext_length < (aead_data->plaintext_length + operation.tag_length)) {
        status = HKS_ERROR_BUFFER_TOO_SMALL;
        goto exit;
    }

    uint8_t *tag = aead_data->ciphertext + aead_data->plaintext_length;

    if (operation.core_alg == HKS_ALG_GCM)
        status = mbedtls_gcm_crypt_and_tag(&operation.gcm, MBEDTLS_GCM_ENCRYPT,
            aead_data->plaintext_length, aead_data->nonce, aead_data->nonce_length, aead_data->additional_data,
            aead_data->additional_data_length, aead_data->plaintext, aead_data->ciphertext, operation.tag_length, tag);
    else
        status = HKS_ERROR_NOT_SUPPORTED;

    if (status != 0 && aead_data->ciphertext_length != 0)
        (void)memset_s(aead_data->ciphertext, aead_data->ciphertext_length, 0, aead_data->ciphertext_length);
exit:
    mbedtls_gcm_free(&(operation.gcm));
    if (status == HKS_SUCCESS) {
        if (aead_data->plaintext_length > SIZE_MAX - operation.tag_length)
            return HKS_ERROR_BAD_STATE;
        *ciphertext_output_length = aead_data->plaintext_length + operation.tag_length;
    }

    return mbedtls_to_hks_error(status);
}

static int32_t hks_aead_setup(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    struct hks_aead_operation *operation)
{
    int32_t status;
    size_t key_bits = key_param->key_len;
    mbedtls_cipher_id_t cipher_id = MBEDTLS_CIPHER_ID_AES;
    mbedtls_cipher_mode_t mode = MBEDTLS_MODE_GCM;

    operation->cipher_info = mbedtls_cipher_info_from_values(cipher_id,
        (int)key_bits, mode);
    if (operation->cipher_info == NULL)
        return HKS_ERROR_NULL_POINTER;

    switch (key_param->key_mode) {
    case HKS_ALG_GCM:
        operation->core_alg = HKS_ALG_GCM;
        operation->full_tag_length = MAX_GCM_TAG_LENGTH;

        if (HKS_BLOCK_CIPHER_BLOCK_SIZE(key_param->key_type) !=
            MAX_GCM_TAG_LENGTH)
            return HKS_ERROR_INVALID_ARGUMENT;
        mbedtls_gcm_init(&operation->gcm);
        status = mbedtls_gcm_setkey(&operation->gcm, cipher_id,
            key->data, (unsigned int)key_bits);
        break;
    default:
        return HKS_ERROR_NOT_SUPPORTED;
    }

    /*
     * CCM allows the following tag lengths: 4, 6, 8, 10, 12, 14, 16.
     * GCM allows the following tag lengths: 4, 8, 12, 13, 14, 15, 16.
     * In both cases, mbedtls_xxx will validate the tag length below.
     */
    if (hks_aead_tag_length(key_param->key_mode) >
        operation->full_tag_length) {
        status = HKS_ERROR_INVALID_ARGUMENT;
        goto cleanup;
    }
    operation->tag_length = hks_aead_tag_length(key_param->key_mode);
    return HKS_SUCCESS;

cleanup:
    mbedtls_gcm_free(&operation->gcm);
    return mbedtls_to_hks_error(status);
}

int32_t hks_aead_unpadded_locate_tag(size_t tag_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    size_t plaintext_size, const uint8_t **p_tag)
{
    size_t payload_length;

    if (tag_length > ciphertext_length)
        return HKS_ERROR_INVALID_ARGUMENT;

    payload_length = ciphertext_length - tag_length;
    if (payload_length > plaintext_size)
        return HKS_ERROR_BUFFER_TOO_SMALL;

    if (ciphertext_length > SIZE_MAX - payload_length)
        return HKS_ERROR_BAD_STATE;

    *p_tag = ciphertext + payload_length;
    return HKS_SUCCESS;
}

int32_t hks_mbedtls_key_derivation(struct hks_blob *derived_key,
    const uint32_t alg, const struct hks_blob *kdf_key,
    const struct hks_blob *salt, const struct hks_blob *label)
{
    int32_t status = 0;

    switch (alg) {
    case hks_alg_hkdf(HKS_ALG_HASH_SHA_256):
        status = mbedtls_hkdf(
            mbedtls_md_info_from_type(MBEDTLS_MD_SHA256),
            salt->data, salt->size, kdf_key->data, kdf_key->size,
            label->data, label->size, derived_key->data,
            derived_key->size);
        break;
    case hks_alg_hkdf(HKS_ALG_HASH_SHA_512):
        status = mbedtls_hkdf(
            mbedtls_md_info_from_type(MBEDTLS_MD_SHA512),
            salt->data, salt->size, kdf_key->data, kdf_key->size,
            label->data, label->size, derived_key->data,
            derived_key->size);
        break;
    default:
        break;
    }

    hks_check_return_code(mbedtls_to_hks_error(status), &status);
    return status;
}

int32_t hks_endian_swap(uint8_t *p_data, int32_t length)
{
    if (p_data == NULL)
        return HKS_ERROR_NULL_POINTER;

    if (length <= 0)
        return HKS_ERROR_BUF_TOO_SMALL;

    int32_t end = length - 1;
    int32_t start = 0;

    /* count the middle index of array */
    int32_t cnt = length / 2;
    uint8_t tmp;

    for (int32_t i = 0; i < cnt; i++) {
        tmp = p_data[start + i];
        p_data[start + i] = p_data[end - i];
        p_data[end - i] = tmp;
    }
    return HKS_SUCCESS;
}

struct mbedtls_to_hks_err_code {
    int32_t mbedtls_code;
    int32_t hks_code;
};

const struct mbedtls_to_hks_err_code g_code_conv[] = {
    { 0, HKS_SUCCESS },
    /* AES */
    { MBEDTLS_ERR_AES_INVALID_KEY_LENGTH, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_AES_FEATURE_UNAVAILABLE, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_AES_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },

    /* CIPHER */
    { MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_CIPHER_ALLOC_FAILED, HKS_ERROR_INSUFFICIENT_MEMORY },
    { MBEDTLS_ERR_CIPHER_INVALID_PADDING, HKS_ERROR_INVALID_PADDING },
    { MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED, HKS_ERROR_BAD_STATE },
    { MBEDTLS_ERR_CIPHER_AUTH_FAILED, HKS_ERROR_INVALID_SIGNATURE },
    { MBEDTLS_ERR_CIPHER_INVALID_CONTEXT, HKS_ERROR_TAMPERING_DETECTED },
    { MBEDTLS_ERR_CIPHER_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },

    /* CTR_DRBG */
    { MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED, HKS_ERROR_INSUFFICIENT_ENTROPY },
    { MBEDTLS_ERR_CTR_DRBG_REQUEST_TOO_BIG, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_CTR_DRBG_INPUT_TOO_BIG, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_CTR_DRBG_FILE_IO_ERROR, HKS_ERROR_INSUFFICIENT_ENTROPY },

    /* ENTROPY */
    { MBEDTLS_ERR_ENTROPY_NO_SOURCES_DEFINED, HKS_ERROR_INSUFFICIENT_ENTROPY },
    { MBEDTLS_ERR_ENTROPY_NO_STRONG_SOURCE, HKS_ERROR_INSUFFICIENT_ENTROPY },
    { MBEDTLS_ERR_ENTROPY_SOURCE_FAILED, HKS_ERROR_INSUFFICIENT_ENTROPY },

    /* GCM */
    { MBEDTLS_ERR_GCM_AUTH_FAILED, HKS_ERROR_INVALID_SIGNATURE },
    { MBEDTLS_ERR_GCM_BAD_INPUT, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_GCM_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },

    /* MD */
    { MBEDTLS_ERR_MD2_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },
    { MBEDTLS_ERR_MD4_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },
    { MBEDTLS_ERR_MD5_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },
    { MBEDTLS_ERR_MD_FEATURE_UNAVAILABLE, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_MD_BAD_INPUT_DATA, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_MD_ALLOC_FAILED, HKS_ERROR_INSUFFICIENT_MEMORY },
    { MBEDTLS_ERR_MD_FILE_IO_ERROR, HKS_ERROR_STORAGE_FAILURE },
    { MBEDTLS_ERR_MD_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },

    /* MPI */
    { MBEDTLS_ERR_MPI_FILE_IO_ERROR, HKS_ERROR_STORAGE_FAILURE },
    { MBEDTLS_ERR_MPI_BAD_INPUT_DATA, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_MPI_INVALID_CHARACTER, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL, HKS_ERROR_BUFFER_TOO_SMALL },
    { MBEDTLS_ERR_MPI_NEGATIVE_VALUE, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_MPI_DIVISION_BY_ZERO, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_MPI_NOT_ACCEPTABLE, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_MPI_ALLOC_FAILED, HKS_ERROR_INSUFFICIENT_MEMORY },

    /* PK */
    { MBEDTLS_ERR_PK_ALLOC_FAILED, HKS_ERROR_INSUFFICIENT_MEMORY },
    { MBEDTLS_ERR_PK_TYPE_MISMATCH, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_PK_BAD_INPUT_DATA, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_PK_FILE_IO_ERROR, HKS_ERROR_STORAGE_FAILURE },
    { MBEDTLS_ERR_PK_KEY_INVALID_VERSION, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_PK_KEY_INVALID_FORMAT, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_PK_UNKNOWN_PK_ALG, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_PK_PASSWORD_REQUIRED, HKS_ERROR_NOT_PERMITTED },
    { MBEDTLS_ERR_PK_PASSWORD_MISMATCH, HKS_ERROR_NOT_PERMITTED },
    { MBEDTLS_ERR_PK_INVALID_PUBKEY, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_PK_INVALID_ALG, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_PK_UNKNOWN_NAMED_CURVE, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_PK_SIG_LEN_MISMATCH, HKS_ERROR_INVALID_SIGNATURE },
    { MBEDTLS_ERR_PK_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },

    /* RIPEMD160 */
    { MBEDTLS_ERR_RIPEMD160_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },

    /* SHA */
    { MBEDTLS_ERR_SHA256_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE },
    { MBEDTLS_ERR_SHA512_HW_ACCEL_FAILED, HKS_ERROR_INVALID_ARGUMENT },

    /* ECP */
    { MBEDTLS_ERR_ECP_BAD_INPUT_DATA, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_ECP_INVALID_KEY, HKS_ERROR_INVALID_ARGUMENT },
    { MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL, HKS_ERROR_BUFFER_TOO_SMALL },
    { MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE, HKS_ERROR_NOT_SUPPORTED },
    { MBEDTLS_ERR_ECP_SIG_LEN_MISMATCH, HKS_ERROR_INVALID_SIGNATURE },
    { MBEDTLS_ERR_ECP_VERIFY_FAILED, HKS_ERROR_INVALID_SIGNATURE },
    { MBEDTLS_ERR_ECP_ALLOC_FAILED, HKS_ERROR_INSUFFICIENT_MEMORY },
    { MBEDTLS_ERR_ECP_HW_ACCEL_FAILED, HKS_ERROR_HARDWARE_FAILURE }
};

int32_t mbedtls_to_hks_error(int ret)
{
    int rc = ret;

    /*
     * 1. If there's both a high-level code and low-level code, dispatch on
     *    the high-level code.
     * 2. Use bitwise operators only on unsigned operands
     */
    if (rc < MBEDTLS_RET_CODE_BOUNDARY)
        rc = -(int)(((unsigned int)-rc) &
            MBEDTLS_RET_CODE_HIGH_LEVEL_MASK);

    uint32_t code_cov_size = sizeof(g_code_conv) / sizeof(g_code_conv[0]);

    for (uint32_t i = 0; i < code_cov_size; i++) {
        if (rc == g_code_conv[i].mbedtls_code)
            return g_code_conv[i].hks_code;
    }

    return HKS_FAILURE;
}

/*
 * XOR operation
 * parameter:
 *     src1          - [in]  - source data #1.
 *     src2          - [in]  - source data #2.
 *     result        - [out] - result.
 * return value: none
 */
void hks_xor(const struct hks_blob *src1, const struct hks_blob *src2,
    struct hks_blob *result)
{
    if ((src1 == NULL) || (src2 == NULL) || (result == NULL))
        return;

    uint32_t xor_len = (src1->size < src2->size) ? src1->size : src2->size;

    if (xor_len > result->size)
        xor_len = result->size;

    uint32_t i;

    for (i = 0; i < xor_len; ++i)
        result->data[i] = src1->data[i] ^ src2->data[i];
}

/*
 * register callback for get hardware UDID(Unique Device Identifier)
 * parameter:
 *     callback - [in]   - The callback functions for get hardware UDID.
 * return value:
 *     success or error code
 */
int32_t hks_reg_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback)
{
    if (callback == NULL) {
        log_error("invalid callback");
        return HKS_ERROR_NULL_POINTER;
    }

    g_hks_get_hardware_udid_callback = callback;

    return HKS_STATUS_OK;
}

/*
 * get hardware UDID(Unique Device Identifier)
 * parameter:
 *     udid     - [out]  - UDID.
 *     udid_len - [in]   - the length of UDID.
 * return value:
 *     success or error code
 */
int32_t hks_get_hardware_udid(uint8_t *udid, uint32_t udid_len)
{
    if (udid == NULL) {
        log_error("invalid udid");
        return HKS_ERROR_NULL_POINTER;
    }
    if (udid_len != HKS_HARDWARE_UDID_LEN) {
        log_error("invalid udid,len=%u", udid_len);
        return HKS_ERROR_INVALID_ARGUMENT;
    }
    if (g_hks_get_hardware_udid_callback == NULL) {
        log_error("invalid callback");
        return HKS_ERROR_NULL_POINTER;
    }

    int32_t rc = g_hks_get_hardware_udid_callback(udid, udid_len);

    if (rc != HKS_STATUS_OK) {
        log_error("get udid fail,rc=%d", rc);
        return HKS_ERROR_HARDWARE_FAILURE;
    }

    return HKS_STATUS_OK;
}

void crypto_hash_sha512(unsigned char *out, const unsigned char *in, const int len)
{
    if ((out == NULL) || (in == NULL))
        return;
    mbedtls_sha512_context ctx;

    mbedtls_sha512_init(&ctx);
    mbedtls_sha512_starts_ret(&ctx, 0);
    mbedtls_sha512_update(&ctx, in, len);
    mbedtls_sha512_finish(&ctx, out);
}

