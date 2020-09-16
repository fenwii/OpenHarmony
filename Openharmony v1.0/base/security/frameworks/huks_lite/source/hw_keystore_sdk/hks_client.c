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

#include "hks_client.h"

#include <mbedtls/config.h>
#include <mbedtls/platform.h>

#include "securec.h"

#include "common/hks_common.h"
#include "common/hks_log_utils.h"
#include "common/hks_mem.h"
#include "hks_errno.h"
#include "hks_file_api.h"
#include "hks_hardware_api.h"
#include "hks_types.h"
#include "soft_service/hks_service.h"

#include "hks_access.h"

/* AES-GCM encrypt IV minimum size,96bit=12bytes */
#define HKS_AES_GCM_MIN_IV_LENGTH 12

#define hks_not_support_interface \
do { \
    log_error("interface %s not support.\n", __func__); \
    return HKS_ERROR_INTERNAL_UNKOWN; \
} while (0)

void hks_get_sdk_version(struct hks_blob *sdk_version)
{
    if (sdk_version == NULL)
        return;

    const size_t version_len = strlen(HKS_SDK_VERSION);
    if ((sdk_version->data != NULL) && (sdk_version->size > version_len)) {
        if (memcpy_s(sdk_version->data, sdk_version->size, HKS_SDK_VERSION, version_len) != EOK) {
            log_error("memcpy_s fail");
            return;
        }
        sdk_version->data[version_len] = '\0';
        sdk_version->size = (uint32_t)version_len + 1;
    }
}

#if (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)) && \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_generate_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_generate_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param)
{
    HKS_TRACE_IN;
    hks_if_status_error_return(hks_is_valid_auth_id(key_param));
    hks_if_status_error_return(hks_is_valid_alias(key_alias));

#ifdef _SUPPORT_HKS_TEE_
    if (key_param->key_type == HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519) {
        if ((key_param->key_domain != HKS_ECC_CURVE_ED25519) ||
            (key_param->key_pad != HKS_PADDING_NONE))
            return HKS_ERROR_INVALID_ARGUMENT;
    } else if (key_param->key_type == HKS_KEY_TYPE_RSA_KEYPAIR) {
        if ((key_param->key_len != HKS_KEY_LEN_RSA_KEYPAIR) ||
            (key_param->key_pad != HKS_PADDING_PSS))
            return HKS_ERROR_INVALID_ARGUMENT;
    } else if (key_param->key_type == HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519) {
        if ((key_param->key_len != HKS_MAX_KEY_LEN_256) ||
            (key_param->key_pad != HKS_PADDING_NONE))
            return HKS_ERROR_INVALID_ARGUMENT;
    } else {
        return HKS_ERROR_NOT_SUPPORTED;
    }
    if (key_param->key_usage != (HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY))
        return HKS_ERROR_INVALID_ARGUMENT;

    if (key_param->key_param_ext.storage_flag != HKS_STORAGE_TEE)
        return HKS_ERROR_NOT_SUPPORTED;

    hks_if_status_error_return(hks_is_valid_data_creator(key_param));
    hks_if_status_error_return(hks_is_valid_data_owner(key_param));
    hks_if_status_error_return(hks_is_valid_ext_info(key_param));
    return hks_tee_generate_key(key_alias, key_param);
#else
    if (key_param->key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519)
        return HKS_ERROR_NOT_SUPPORTED;
    return hks_access_generate_key(key_alias, key_param);
#endif
}
#endif

#ifdef _SUPPORT_HKS_TEE_
HKS_DLL_API_PUBLIC int32_t hks_generate_symmetric_key(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param,
    const struct hks_derive_param *derive_param)
{
    hks_if_status_error_return(hks_is_valid_auth_id(key_param));
    hks_if_status_error_return(hks_is_valid_alias(key_alias));
    hks_if_true_return_error((derive_param == NULL),
        HKS_ERROR_NULL_POINTER);

    if ((key_param->key_type != HKS_KEY_TYPE_AES) ||
        (key_param->key_len != HKS_MAX_KEY_LEN_256))
        return HKS_ERROR_NOT_SUPPORTED;

    if ((derive_param->key_gen_type != HKS_KEY_GEN_TYPE_DERIVE) &&
        (derive_param->key_gen_type != HKS_KEY_GEN_TYPE_DEFAULT))
        return HKS_ERROR_NOT_SUPPORTED;

    if (derive_param->key_gen_type == HKS_KEY_GEN_TYPE_DERIVE) {
        if (derive_param->master_key.type != HKS_BLOB_TYPE_ALIAS)
            return HKS_ERROR_INVALID_ARGUMENT;
        int32_t status = hks_is_valid_alias(&(derive_param->master_key));
        hks_if_status_error_return(status);
        if ((derive_param->derive_factor.data == NULL) ||
            (derive_param->derive_factor.size == 0))
            return HKS_ERROR_INVALID_ARGUMENT;
    } else if (derive_param->key_gen_type == HKS_KEY_GEN_TYPE_DEFAULT) {
        if ((derive_param->derive_factor.data != NULL) ||
            (derive_param->derive_factor.size != 0))
            return HKS_ERROR_INVALID_ARGUMENT;
    }

    if (key_param->key_param_ext.storage_flag != HKS_STORAGE_TEE)
        return HKS_ERROR_NOT_SUPPORTED;

    return hks_tee_generate_symmetric_key(key_alias, key_param,
        derive_param);
}
#endif

#if defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)
HKS_DLL_API_PUBLIC int32_t hks_generate_asymmetric_key(
    const struct hks_key_param *key_param, struct hks_blob *pri_key,
    struct hks_blob *pub_key)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_generate_asymmetric_key(
    const struct hks_key_param *key_param, struct hks_blob *pri_key,
    struct hks_blob *pub_key)
{
    HKS_TRACE_IN;
    hks_if_true_return_error((key_param == NULL), HKS_ERROR_NULL_POINTER);
    if (key_param->key_type != HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519)
        return HKS_ERROR_NOT_SUPPORTED;
    if (key_param->key_mode != hks_alg_ecdh(HKS_ALG_SELECT_RAW))
        return HKS_ERROR_NOT_SUPPORTED;
    if ((pri_key == NULL) || (pri_key->data == NULL) || (pub_key == NULL) ||
        (pub_key->data == NULL))
        return HKS_ERROR_NULL_POINTER;
#ifdef _SUPPORT_HKS_TEE_
    hks_if_status_error_return(hks_is_valid_data_creator(key_param));
    hks_if_status_error_return(hks_is_valid_data_owner(key_param));
    hks_if_status_error_return(hks_is_valid_ext_info(key_param));
    return hks_service_generate_asymmetric_key(key_param, pri_key, pub_key);
#else
    return hks_access_generate_key_ex(key_param, pri_key, pub_key);
#endif
}
#endif

#if (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) ||  \
    defined(_CUT_ADD_) || defined(_CUT_ADD_SERVER_)) &&  \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_import_public_key(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *key)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_import_public_key(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *key)
{
    HKS_TRACE_IN;
    hks_if_status_error_return(hks_is_valid_auth_id(key_param));
    int32_t status = hks_is_valid_alias(key_alias);

    if (status != HKS_STATUS_OK)
        return status;
    if (key_param->key_type != HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519)
        return HKS_ERROR_NOT_SUPPORTED;
    hks_if_true_return_error((key == NULL), HKS_ERROR_NULL_POINTER);
    if ((key->data == NULL) || (key->size != CRYPTO_PUBLIC_KEY_BYTES))
        return HKS_ERROR_INVALID_PUBLIC_KEY;

#ifdef _SUPPORT_HKS_TEE_
    if (key_param->key_usage != HKS_KEY_USAGE_VERIFY)
        return HKS_ERROR_INVALID_ARGUMENT;
    if (key_param->key_param_ext.storage_flag != HKS_STORAGE_TEE)
        return HKS_ERROR_NOT_SUPPORTED;
    status = hks_tee_import_public_key(key_alias, key_param, key);
#else
    status = hks_access_import_key(key_alias, key_param, key);
#endif
    return status;
}
#endif

#if defined(_CUT_EXCHANGE_SERVER_) || defined(_CUT_PAKE_) || \
    defined(_CUT_PAKE_SERVER_) || defined(_CUT_EXCHANGE_)
HKS_DLL_API_PUBLIC int32_t hks_export_public_key(
    const struct hks_blob *key_alias, struct hks_blob *key)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_export_public_key(
    const struct hks_blob *key_alias, struct hks_blob *key)
{
    int32_t status = hks_is_valid_alias(key_alias);

    if (status != HKS_STATUS_OK)
        return status;
    if (key == NULL)
        return HKS_ERROR_NULL_POINTER;
    if ((key->data == NULL) || (key->size < CRYPTO_PUBLIC_KEY_BYTES))
        return HKS_ERROR_BUF_TOO_SMALL;

#ifdef _SUPPORT_HKS_TEE_
    status = hks_tee_export_public_key(key_alias, key);
#else
    status = hks_access_export_key(key_alias, key);
#endif
    return status;
}
#endif

#if defined(_CUT_API_) && (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) || \
    defined(_CUT_REMOVE_) || defined(_CUT_REMOVE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_delete_key(const struct hks_blob *key_alias)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_delete_key(const struct hks_blob *key_alias)
{
    /* to add log here track return value */
    int32_t status = hks_is_valid_alias(key_alias);

    if (status != HKS_STATUS_OK)
        return status;
#ifdef _SUPPORT_HKS_TEE_
    return hks_tee_delete_key(key_alias);
#else
    return hks_access_delete_key(key_alias);
#endif
}
#endif

#if defined(_CUT_API_)
HKS_DLL_API_PUBLIC int32_t hks_get_key_param(const struct hks_blob *key_alias,
    struct hks_key_param *key_param)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_get_key_param(const struct hks_blob *key_alias,
    struct hks_key_param *key_param)
{
    int32_t status = hks_is_valid_alias(key_alias);

    if (status != HKS_STATUS_OK)
        return status;
    if (key_param == NULL)
        return HKS_ERROR_NULL_POINTER;
#ifdef _SUPPORT_HKS_TEE_
    status = hks_tee_get_key_param(key_alias, key_param);
#else
    status = hks_access_get_key_param(key_alias, key_param);
#endif
    return status;
}
#endif

/*
 * For current interface, if status is HKS_STATUS_OK
 * means key exist, others means key does not exist or error occurs
 */
#if defined(_CUT_API_) && (defined(_CUT_STS_) || \
    defined(_CUT_STS_SERVER_)) &&  (defined(_CUT_PAKE_) || \
    defined(_CUT_PAKE_SERVER_) || defined(_CUT_EXCHANGE_) || \
    defined(_CUT_EXCHANGE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_is_key_exist(const struct hks_blob *key_alias)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_is_key_exist(const struct hks_blob *key_alias)
{
    int32_t status = hks_is_valid_alias(key_alias);

    if (status != HKS_STATUS_OK)
        return status;
#ifdef _SUPPORT_HKS_TEE_
    status = hks_tee_is_key_exist(key_alias);
#else
    status = hks_access_is_key_exist(key_alias);
#endif
    return status;
}
#endif

#if (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)) && \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_asymmetric_sign(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    struct hks_blob *signature)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_asymmetric_sign(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    struct hks_blob *signature)
{
    int32_t status = hks_is_valid_alias(key_alias);

    hks_if_status_error_return(status);
    hks_if_true_return_error(((key_param == NULL) || (hash == NULL) ||
        (signature == NULL)), HKS_ERROR_NULL_POINTER);
#ifdef _SUPPORT_HKS_TEE_
    status = hks_tee_asymmetric_sign(key_alias, key_param,
        hash, signature);
#else
    if ((key_param->key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519) ||
        ((key_param->key_usage & HKS_KEY_USAGE_SIGN) == 0))
        return HKS_ERROR_NOT_SUPPORTED;
    if ((hash->data == NULL) || (hash->size <= 0))
        return HKS_ERROR_INVALID_ARGUMENT;
    if ((signature->data == NULL) ||
        (signature->size < HKS_SIGNATURE_MIN_SIZE))
        return HKS_ERROR_BUFFER_TOO_SMALL;

    status = hks_access_sign(key_alias, key_param,
        hash, signature);
#endif
    return status;
}
#endif

#if (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)) && \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_asymmetric_verify(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    const struct hks_blob *signature)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_asymmetric_verify(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    const struct hks_blob *signature)
{
    hks_if_true_return_error(((key == NULL) || (key_param == NULL) ||
        (hash == NULL) || (signature == NULL)), HKS_ERROR_NULL_POINTER);

    int32_t status;

    if (key->type == HKS_BLOB_TYPE_ALIAS) {
        status = hks_is_valid_alias(key);
        hks_if_status_error_return(status);
    } else if (key->type == HKS_BLOB_TYPE_KEY) {
        if (key_param->key_type != HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519)
            return HKS_ERROR_NOT_SUPPORTED;
        if ((key->data == NULL) || (key->size != HKS_PUBLIC_BYTES_ED25519))
            return HKS_ERROR_INVALID_KEY_INFO;
    } else {
        return HKS_ERROR_INVALID_KEY_INFO;
    }

    if ((key_param->key_usage & HKS_KEY_USAGE_VERIFY) == 0)
        return HKS_ERROR_NOT_SUPPORTED;

    if ((hash->data == NULL) || (hash->size <= 0))
        return HKS_ERROR_INVALID_ARGUMENT;

    if ((signature->data == NULL) || (signature->size < HKS_SIGNATURE_MIN_SIZE))
        return HKS_ERROR_INVALID_ARGUMENT;
#ifdef _SUPPORT_HKS_TEE_
    if (key_param->key_param_ext.storage_flag != HKS_STORAGE_TEE)
        return HKS_ERROR_NOT_SUPPORTED;

    if (key->type == HKS_BLOB_TYPE_KEY)
        status = hks_service_asymmetric_verify(key, hash, signature);
    else
        status = hks_tee_asymmetric_verify(key, key_param, hash, signature);
#else
    status = hks_access_verify(key, hash, signature);
#endif
    return status;
}
#endif

#ifdef _SUPPORT_HKS_TEE_
static int32_t hks_aead_encrypt_tee(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag)
{
    if (key_param->key_mode == HKS_ALG_GCM) {
        hks_if_true_return_error(((key_param->key_type != HKS_KEY_TYPE_AES) ||
            (key_param->key_pad != HKS_PADDING_NONE) ||
            ((key_param->key_usage & HKS_KEY_USAGE_ENCRYPT) == 0)), HKS_ERROR_NOT_SUPPORTED);

        hks_if_true_return_error(((key_param->key_len != HKS_MAX_KEY_LEN_128) &&
            (key_param->key_len != HKS_MAX_KEY_LEN_192) &&
            (key_param->key_len != HKS_MAX_KEY_LEN_256)), HKS_ERROR_NOT_SUPPORTED);

        hks_if_true_return_error(((key->type != HKS_BLOB_TYPE_KEY) || (key->data == NULL) ||
            (key->size != (key_param->key_len / HKS_BITS_PER_BYTES))), HKS_ERROR_INVALID_KEY_INFO);

        hks_if_true_return_error(((crypt_param->nonce.data == NULL) ||
            (crypt_param->nonce.size < HKS_AES_GCM_MIN_IV_LENGTH) ||
            (crypt_param->aad.data == NULL) ||
            (crypt_param->aad.size == 0) ||
            (plain_text->data == NULL) || (plain_text->size == 0)), HKS_ERROR_INVALID_ARGUMENT);

        hks_if_true_return_error(((cipher_text_with_tag == NULL) ||
            (cipher_text_with_tag->data == NULL) ||
            (cipher_text_with_tag->size <
             (plain_text->size + HKS_SALT_MAX_SIZE))), HKS_ERROR_INVALID_ARGUMENT);

        return hks_service_aead_encrypt_ex(key, key_param, crypt_param, plain_text, cipher_text_with_tag);
    } else if (key_param->key_mode == HKS_ALG_CCM) {
        return hks_tee_aead_encrypt(key, key_param, crypt_param, plain_text, cipher_text_with_tag);
    }

    return HKS_ERROR_INVALID_ARGUMENT;
}
#else
static int32_t hks_aead_encrypt_ree(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag)
{
    hks_if_true_return_error(((key_param->key_type != HKS_KEY_TYPE_AES) ||
        (key_param->key_mode != HKS_ALG_GCM) ||
        (key_param->key_pad != HKS_PADDING_NONE) ||
        ((key_param->key_usage & HKS_KEY_USAGE_ENCRYPT) == 0)), HKS_ERROR_NOT_SUPPORTED);

    hks_if_true_return_error(((key_param->key_len != HKS_MAX_KEY_LEN_128) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_192) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_256)), HKS_ERROR_NOT_SUPPORTED);

    hks_if_true_return_error(((key->type != HKS_BLOB_TYPE_KEY) || (key->data == NULL) ||
        (key->size != (key_param->key_len / HKS_BITS_PER_BYTES))), HKS_ERROR_INVALID_KEY_INFO);

    hks_if_true_return_error(((crypt_param->nonce.data == NULL) ||
        (crypt_param->nonce.size < HKS_AES_GCM_MIN_IV_LENGTH) ||
        (crypt_param->aad.data == NULL) ||
        (crypt_param->aad.size == 0) ||
        (plain_text->data == NULL) || (plain_text->size == 0)), HKS_ERROR_INVALID_ARGUMENT);

    hks_if_true_return_error(((cipher_text_with_tag == NULL) ||
        (cipher_text_with_tag->data == NULL) ||
        (cipher_text_with_tag->size < (plain_text->size + HKS_SALT_MAX_SIZE))),
        HKS_ERROR_INVALID_ARGUMENT);

    return hks_access_aead_encrypt(key, key_param, crypt_param, plain_text, cipher_text_with_tag);
}
#endif

#if defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_)
HKS_DLL_API_PUBLIC int32_t hks_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag)
{
    hks_if_true_return_error(((key == NULL) || (key_param == NULL) ||
        (crypt_param == NULL || (plain_text == NULL) ||
        (cipher_text_with_tag == NULL))), HKS_ERROR_NULL_POINTER);
#ifdef _SUPPORT_HKS_TEE_
    return hks_aead_encrypt_tee(key, key_param, crypt_param, plain_text, cipher_text_with_tag);
#else
    return hks_aead_encrypt_ree(key, key_param, crypt_param, plain_text, cipher_text_with_tag);
#endif
}
#endif

#ifdef _SUPPORT_HKS_TEE_
static int32_t hks_aead_decrypt_tee(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    struct hks_blob *plain_text,
    const struct hks_blob *cipher_text_with_tag)
{
    if (key_param->key_mode == HKS_ALG_GCM) {
        hks_if_true_return_error(((key_param->key_type != HKS_KEY_TYPE_AES) ||
            (key_param->key_pad != HKS_PADDING_NONE) ||
            ((key_param->key_usage & HKS_KEY_USAGE_DECRYPT) == 0)), HKS_ERROR_NOT_SUPPORTED);

        hks_if_true_return_error(((key_param->key_len != HKS_MAX_KEY_LEN_128) &&
            (key_param->key_len != HKS_MAX_KEY_LEN_192) &&
            (key_param->key_len != HKS_MAX_KEY_LEN_256)), HKS_ERROR_NOT_SUPPORTED);

        hks_if_true_return_error(((key->type != HKS_BLOB_TYPE_KEY) || (key->data == NULL) ||
            (key->size != (key_param->key_len / HKS_BITS_PER_BYTES))), HKS_ERROR_INVALID_KEY_INFO);

        hks_if_true_return_error(((crypt_param->nonce.data == NULL) ||
            (crypt_param->nonce.size == 0) ||
            (crypt_param->aad.data == NULL) ||
            (crypt_param->aad.size == 0) ||
            (plain_text == NULL) || (plain_text->data == NULL)), HKS_ERROR_INVALID_ARGUMENT);

        hks_if_true_return_error(((cipher_text_with_tag->data == NULL) ||
            (cipher_text_with_tag->size <= HKS_SALT_MAX_SIZE) ||
            (plain_text->size < (cipher_text_with_tag->size - HKS_SALT_MAX_SIZE))),
            HKS_ERROR_INVALID_ARGUMENT);

        return hks_service_aead_decrypt_ex(key, key_param, crypt_param,
                                           cipher_text_with_tag, plain_text);
    } else if (key_param->key_mode == HKS_ALG_CCM) {
        return hks_tee_aead_decrypt(key, key_param, crypt_param, plain_text, cipher_text_with_tag);
    }

    return HKS_ERROR_INVALID_ARGUMENT;
}
#else
static int32_t hks_aead_decrypt_ree(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    struct hks_blob *plain_text,
    const struct hks_blob *cipher_text_with_tag)
{
    hks_if_true_return_error(((key_param->key_type != HKS_KEY_TYPE_AES) ||
        (key_param->key_mode != HKS_ALG_GCM) ||
        (key_param->key_pad != HKS_PADDING_NONE) ||
        ((key_param->key_usage & HKS_KEY_USAGE_DECRYPT) == 0)), HKS_ERROR_NOT_SUPPORTED);

    hks_if_true_return_error(((key_param->key_len != HKS_MAX_KEY_LEN_128) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_192) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_256)), HKS_ERROR_NOT_SUPPORTED);

    hks_if_true_return_error(((key->type != HKS_BLOB_TYPE_KEY) || (key->data == NULL) ||
        (key->size != (key_param->key_len / HKS_BITS_PER_BYTES))), HKS_ERROR_INVALID_KEY_INFO);

    hks_if_true_return_error(((crypt_param->nonce.data == NULL) ||
        (crypt_param->nonce.size == 0) ||
        (crypt_param->aad.data == NULL) ||
        (crypt_param->aad.size == 0) ||
        (plain_text == NULL) || (plain_text->data == NULL)), HKS_ERROR_INVALID_ARGUMENT);

    hks_if_true_return_error(((cipher_text_with_tag->data == NULL) ||
        (cipher_text_with_tag->size <= HKS_SALT_MAX_SIZE) ||
        (plain_text->size < (cipher_text_with_tag->size - HKS_SALT_MAX_SIZE))),
        HKS_ERROR_INVALID_ARGUMENT);

    return hks_access_aead_decrypt(key, key_param, crypt_param, cipher_text_with_tag, plain_text);
}
#endif

#if defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_)
HKS_DLL_API_PUBLIC int32_t hks_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    struct hks_blob *plain_text,
    const struct hks_blob *cipher_text_with_tag)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    struct hks_blob *plain_text,
    const struct hks_blob *cipher_text_with_tag)
{
    hks_if_true_return_error(((key == NULL) || (key_param == NULL) ||
        (crypt_param == NULL || (plain_text == NULL) ||
        (cipher_text_with_tag == NULL))), HKS_ERROR_NULL_POINTER);
#ifdef _SUPPORT_HKS_TEE_
    return hks_aead_decrypt_tee(key, key_param, crypt_param, plain_text, cipher_text_with_tag);
#else
    return hks_aead_decrypt_ree(key, key_param, crypt_param, plain_text, cipher_text_with_tag);
#endif
}
#endif

#if (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)) && \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_key_derivation(struct hks_blob *derived_key,
    const struct hks_key_param *key_param, const struct hks_blob *kdf_key,
    const struct hks_blob *salt, const struct hks_blob *label)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_key_derivation(struct hks_blob *derived_key,
    const struct hks_key_param *key_param, const struct hks_blob *kdf_key,
    const struct hks_blob *salt, const struct hks_blob *label)
{
    hks_if_true_return_error(((derived_key == NULL) ||
        (key_param == NULL) || (kdf_key == NULL) ||
        (salt == NULL) || (label == NULL)),
        HKS_ERROR_NULL_POINTER);
#ifdef _SUPPORT_HKS_TEE_
    hks_if_status_error_return(hks_is_valid_data_creator(key_param));
    hks_if_status_error_return(hks_is_valid_data_owner(key_param));
    hks_if_status_error_return(hks_is_valid_ext_info(key_param));
    return hks_service_key_derivation(derived_key, kdf_key, salt, label,
        key_param);
#else
    return hks_access_key_derivation(derived_key, kdf_key, salt, label,
        key_param);
#endif
}
#endif

#if defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)
HKS_DLL_API_PUBLIC int32_t hks_key_agreement(struct hks_blob *agreed_key,
    const struct hks_key_param *private_key_param,
    const uint32_t agreement_alg, const struct hks_blob *private_key,
    const struct hks_blob *peer_public_key)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_key_agreement(struct hks_blob *agreed_key,
    const struct hks_key_param *private_key_param,
    const uint32_t agreement_alg, const struct hks_blob *private_key,
    const struct hks_blob *peer_public_key)
{
    hks_if_true_return_error(((agreed_key == NULL) ||
        (private_key_param == NULL) || (private_key == NULL) ||
        (peer_public_key == NULL)), HKS_ERROR_NULL_POINTER);

    if ((agreed_key == NULL) || (agreed_key->data == NULL))
        return HKS_ERROR_NULL_POINTER;

    if (agreed_key->size < HKS_KEY_BYTES_CURVE25519)
        return HKS_ERROR_INVALID_KEY_INFO;

    if ((private_key_param->key_type !=
        HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519) ||
        (private_key_param->key_usage != HKS_KEY_USAGE_DERIVE) ||
        (private_key_param->key_mode != hks_alg_ecdh(HKS_ALG_ECDH_RAW)) ||
        (agreement_alg != hks_alg_ecdh(HKS_ALG_ECDH_RAW)))
        return HKS_ERROR_NOT_SUPPORTED;

    if ((private_key->data == NULL) ||
        (private_key->size != HKS_KEY_BYTES_CURVE25519))
        return HKS_ERROR_INVALID_PRIVATE_KEY;

    if ((peer_public_key->data == NULL) ||
        (peer_public_key->size != HKS_KEY_BYTES_CURVE25519))
        return HKS_ERROR_INVALID_PUBLIC_KEY;
#ifdef _SUPPORT_HKS_TEE_
    hks_if_status_error_return(hks_is_valid_data_creator(private_key_param));
    hks_if_status_error_return(hks_is_valid_data_owner(private_key_param));
    hks_if_status_error_return(hks_is_valid_ext_info(private_key_param));
    return hks_service_key_agreement(agreed_key,
        private_key_param, private_key, peer_public_key, agreement_alg);
#else
    return hks_access_key_agreement(agreed_key,
        private_key_param, private_key, peer_public_key, agreement_alg);
#endif
}
#endif

#if (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)) && \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_generate_random(struct hks_blob *random)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_generate_random(struct hks_blob *random)
{
    hks_if_true_return_error(((random == NULL) || (random->data == NULL)),
        HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((random->size > HKS_RANDOM_MAX_LEN),
        HKS_ERROR_INVALID_ARGUMENT);
#ifdef _SUPPORT_HKS_TEE_
    return hks_service_get_random(random);
#else
    return hks_access_get_random(random);
#endif
}
#endif

#if defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_)
HKS_DLL_API_PUBLIC int32_t hks_hmac(const struct hks_blob *key,
    const uint32_t alg, const struct hks_blob *src_data,
    struct hks_blob *output)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_hmac(const struct hks_blob *key,
    const uint32_t alg, const struct hks_blob *src_data,
    struct hks_blob *output)
{
    hks_if_true_return_error(((key == NULL) || (src_data == NULL) ||
        (output == NULL)), HKS_ERROR_NULL_POINTER);
#ifdef _SUPPORT_HKS_TEE_
    return hks_service_hmac_ex(key, alg, src_data, output);
#else
    return hks_access_hmac(key, alg, src_data, output);
#endif
}
#endif

#if defined(_CUT_API_) &&  \
    (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)) && \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) ||  \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_hash(const uint32_t alg,
    const struct hks_blob *src_data, struct hks_blob *hash)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_hash(const uint32_t alg,
    const struct hks_blob *src_data, struct hks_blob *hash)
{
    hks_if_true_return_error(((src_data == NULL) || (hash == NULL)),
        HKS_ERROR_NULL_POINTER);
#ifdef _SUPPORT_HKS_TEE_
    return hks_service_hash(alg, src_data, hash);
#else
    return hks_access_hash(alg, src_data, hash);
#endif
}
#endif

#if defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_)
HKS_DLL_API_PUBLIC int32_t hks_bn_exp_mod(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e,
    const struct hks_blob *n)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_bn_exp_mod(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e,
    const struct hks_blob *n)
{
    hks_if_true_return_error(((x == NULL) || (a == NULL) || (e == NULL) ||
        (n == NULL)), HKS_ERROR_NULL_POINTER);
#ifdef _SUPPORT_HKS_TEE_
    return hks_service_bn_exp_mod(x, a, e, n);
#else
    return hks_access_bn_exp_mod(x, a, e, n);
#endif
}
#endif

#ifndef _SUPPORT_HKS_TEE_
HKS_DLL_API_PUBLIC int32_t hks_register_file_callbacks(
    struct hks_file_callbacks *callbacks)
{
    if (callbacks == NULL)
        return HKS_ERROR_NULL_POINTER;

    return hks_service_register_file_callbacks(callbacks);
}

HKS_DLL_API_PUBLIC int32_t hks_register_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback)
{
    return hks_service_register_get_hardware_udid_callback(callback);
}
#endif

HKS_DLL_API_PUBLIC int32_t hks_register_log_interface(
    const struct hks_log_f_group *log)
{
    if (log == NULL)
        return HKS_ERROR_NULL_POINTER;

    hks_register_log(log);
    return HKS_STATUS_OK;
}

#if defined(_CUT_API_)
HKS_DLL_API_PUBLIC int32_t hks_get_pub_key_alias_list(
    struct hks_blob *key_alias_list, uint32_t *list_count)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_get_pub_key_alias_list(
    struct hks_blob *key_alias_list, uint32_t *list_count)
{
    if ((key_alias_list == NULL) || (list_count == NULL))
        return HKS_ERROR_NULL_POINTER;

#ifdef _SUPPORT_HKS_TEE_
    return hks_tee_get_pub_key_alias_list(key_alias_list, list_count);
#else
    return hks_access_get_pub_key_alias_list(key_alias_list, list_count);
#endif
}
#endif

#if (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)) &&  \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_init(void)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_init(void)
{
#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C) && defined(_STD_LIB_SOUTH_)
    mbedtls_platform_set_calloc_free(HKS_CALLOC, HKS_FREE);
#endif

#ifdef _SUPPORT_HKS_TEE_
    return hks_tee_init();
#else
    return hks_access_init();
#endif
}
#endif

#ifndef _SUPPORT_HKS_TEE_
HKS_DLL_API_PUBLIC void hks_destroy(void)
{
    hks_access_destroy();
}
#endif

#if defined(_SUPPORT_HKS_TEE_) || \
    (defined(_CUT_STS_) || defined(_CUT_STS_SERVER_)) &&  \
    (defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || \
    defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
HKS_DLL_API_PUBLIC int32_t hks_refresh_key_info(void)
{
    hks_not_support_interface;
}
#else
HKS_DLL_API_PUBLIC int32_t hks_refresh_key_info(void)
{
    return hks_access_refresh_key_info();
}
#endif

#if defined (_SUPPORT_HKS_TEE_)
HKS_DLL_API_PUBLIC int32_t hks_unwrap(const struct hks_blob *key_alias,
    const struct hks_blob *target_alias,
    const struct hks_key_param *key_param,
    const struct hks_blob *data,
    struct hks_blob *unwrap_result)
{
    int32_t status = hks_is_valid_alias(key_alias);

    hks_if_status_error_return(status);
    status = hks_is_valid_alias(target_alias);
    hks_if_status_error_return(status);
    hks_if_true_return_error((key_param == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((data == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((unwrap_result == NULL),
        HKS_ERROR_NULL_POINTER);
    if (unwrap_result->type != HKS_BLOB_TYPE_WRAP_ASSET_DATA &&
        unwrap_result->type != HKS_BLOB_TYPE_WRAP_ECDH_ENC_DATA)
        return HKS_ERROR_INVALID_ARGUMENT;
    if (key_param->key_type != HKS_KEY_TYPE_AES ||
        key_param->key_len != HKS_MAX_KEY_LEN_256 ||
        key_param->key_usage != HKS_KEY_USAGE_UNWRAP ||
        key_param->key_mode != HKS_ALG_CCM ||
        key_param->key_pad != HKS_PADDING_PKCS7)
        return HKS_ERROR_INVALID_ARGUMENT;
    if (key_param->key_param_ext.storage_flag != HKS_STORAGE_TEE)
        return HKS_ERROR_NOT_SUPPORTED;
    hks_if_status_error_return(hks_is_valid_data_creator(key_param));
    hks_if_status_error_return(hks_is_valid_data_owner(key_param));
    hks_if_status_error_return(hks_is_valid_ext_info(key_param));
    return hks_tee_unwrap(key_alias, target_alias, key_param, data,
        unwrap_result);
}

HKS_DLL_API_PUBLIC int32_t hks_wrap(const struct hks_blob *key_alias,
    const struct hks_blob *target_alias,
    const struct hks_key_param *key_param,
    const struct hks_blob *data,
    struct hks_blob *wrap_result)
{
    int32_t status = hks_is_valid_alias(key_alias);

    hks_if_status_error_return(status);
    status = hks_is_valid_alias(target_alias);
    hks_if_status_error_return(status);
    hks_if_true_return_error((key_param == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((wrap_result == NULL), HKS_ERROR_NULL_POINTER);

    if (wrap_result->type != HKS_BLOB_TYPE_WRAP_ASSET_DATA)
        return HKS_ERROR_INVALID_ARGUMENT;
    if (key_param->key_type != HKS_KEY_TYPE_AES ||
        key_param->key_len != HKS_MAX_KEY_LEN_256 ||
        key_param->key_usage != HKS_KEY_USAGE_WRAP ||
        key_param->key_mode != HKS_ALG_CCM ||
        key_param->key_pad != HKS_PADDING_PKCS7)
        return HKS_ERROR_INVALID_ARGUMENT;
    if (key_param->key_param_ext.storage_flag != HKS_STORAGE_TEE)
        return HKS_ERROR_NOT_SUPPORTED;
    hks_if_status_error_return(hks_is_valid_data_creator(key_param));
    hks_if_status_error_return(hks_is_valid_data_owner(key_param));
    hks_if_status_error_return(hks_is_valid_ext_info(key_param));
    return hks_tee_wrap(key_alias, target_alias, key_param, data,
        wrap_result);
}

HKS_DLL_API_PUBLIC int32_t hks_key_attestation(
    const struct hks_blob *key_alias, const struct hks_key_param *key_param,
    const struct hks_attestation_spec *att_spec,
    struct hks_cert_chain *cert_chain)
{
    int32_t status = hks_is_valid_alias(key_alias);

    hks_if_status_error_return(status);
    hks_if_true_return_error((key_param == NULL), HKS_ERROR_NULL_POINTER);
    if (key_param->key_type == hks_key_type_ecc_key_pair(HKS_ECC_CURVE_CURVE25519)) {
        if (key_param->key_domain != HKS_ECC_CURVE_CURVE25519)
            return HKS_ERROR_INVALID_ARGUMENT;
    } else if (key_param->key_type == HKS_KEY_TYPE_RSA_KEYPAIR) {
        if (key_param->key_len != HKS_KEY_LEN_RSA_KEYPAIR)
            return HKS_ERROR_INVALID_ARGUMENT;
    } else {
        return HKS_ERROR_NOT_SUPPORTED;
    }
    if (key_param->key_usage != (HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY))
        return HKS_ERROR_INVALID_ARGUMENT;
    hks_if_status_error_return(hks_is_valid_data_creator(key_param));
    hks_if_status_error_return(hks_is_valid_data_owner(key_param));
    hks_if_status_error_return(hks_is_valid_ext_info(key_param));
    hks_if_true_return_error((att_spec == NULL), HKS_ERROR_NULL_POINTER);
    if ((att_spec->challenge.size < HKS_CHALLENGE_MIN_LEN) ||
        (att_spec->challenge.size > HKS_CHALLENGE_MAX_LEN) ||
        (att_spec->challenge.data == NULL))
        return HKS_ERROR_INVALID_ARGUMENT;

    hks_if_true_return_error((cert_chain == NULL), HKS_ERROR_NULL_POINTER);
    if ((cert_chain->count == 0) || (cert_chain->cert == NULL))
        return HKS_ERROR_INVALID_ARGUMENT;
    return hks_tee_key_attestation(key_alias, key_param, att_spec,
        cert_chain);
}

HKS_DLL_API_PUBLIC int32_t hks_get_cert_chain(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param,
    struct hks_cert_chain *cert_chain)
{
    int32_t status = hks_is_valid_alias(key_alias);

    hks_if_status_error_return(status);
    hks_if_true_return_error((key_param == NULL), HKS_ERROR_NULL_POINTER);
    if (key_param->key_type == hks_key_type_ecc_key_pair(HKS_ECC_CURVE_CURVE25519)) {
        if (key_param->key_domain != HKS_ECC_CURVE_CURVE25519)
            return HKS_ERROR_INVALID_ARGUMENT;
    } else if (key_param->key_type == HKS_KEY_TYPE_RSA_KEYPAIR) {
        if (key_param->key_len != HKS_KEY_LEN_RSA_KEYPAIR)
            return HKS_ERROR_INVALID_ARGUMENT;
    } else {
        return HKS_ERROR_NOT_SUPPORTED;
    }
    if (key_param->key_usage != (HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY))
        hks_if_status_error_return(hks_is_valid_data_creator(key_param));
    hks_if_status_error_return(hks_is_valid_data_owner(key_param));
    hks_if_status_error_return(hks_is_valid_ext_info(key_param));

    hks_if_true_return_error((cert_chain == NULL), HKS_ERROR_NULL_POINTER);
    if ((cert_chain->count == 0) || (cert_chain->cert == NULL))
        return HKS_ERROR_INVALID_ARGUMENT;

    return hks_tee_get_cert_chain(key_alias, key_param, cert_chain);
}
#endif

#ifdef _SECURE_ENVIREMENT_NMI_
HKS_DLL_API_PUBLIC int32_t hks_generate_symmetric_key(struct hks_blob *output_key,
    const struct hks_key_param *key_param)
{
    hks_if_status_error_return(hks_is_valid_output_key(output_key));
    hks_if_status_error_return(hks_is_valid_symmetric_key_param(key_param));

    /* key_len is 128/192/256 */
    uint32_t min_output_key_len = (key_param->key_len / HKS_BITS_PER_BYTES) + HKS_ENCRYPTED_KEY_TAG_LEN +
        HKS_ENCRYPTED_KEY_NONCE_LEN + HKS_ENCRYPTED_KEY_AAD_LEN;

    if (output_key->size < min_output_key_len)
        return HKS_ERROR_BUFFER_TOO_SMALL;

    return hks_access_generate_symmetric_key(output_key, key_param);
}

HKS_DLL_API_PUBLIC int32_t hks_symmetric_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text, struct hks_blob *cipher_text_with_tag)
{
    hks_if_status_error_return(hks_is_valid_symmetric_key_param(key_param));
    hks_if_true_return_error(((key == NULL) || (crypt_param == NULL) || (plain_text == NULL) ||
        (cipher_text_with_tag == NULL)), HKS_ERROR_NULL_POINTER);

    if ((key_param->key_usage & HKS_KEY_USAGE_ENCRYPT) == 0)
        return HKS_ERROR_INVALID_ARGUMENT;

    /* key_len is 128/192/256 */
    uint32_t input_key_len = (key_param->key_len / HKS_BITS_PER_BYTES) + HKS_ENCRYPTED_KEY_TAG_LEN +
        HKS_ENCRYPTED_KEY_NONCE_LEN + HKS_ENCRYPTED_KEY_AAD_LEN;

    hks_if_true_return_error(((key->type != HKS_BLOB_TYPE_ENCRYPTED_KEY) || (key->data == NULL) ||
        (key->size != input_key_len)), HKS_ERROR_INVALID_KEY_INFO);

    hks_if_status_error_return(hks_check_symmetric_data_info(key_param, crypt_param, plain_text,
        cipher_text_with_tag, HKS_OPERATION_MODE_ENCRYPT));

    struct hks_encrypt_decrypt_text hks_cipher_text;
    hks_cipher_text.input_text = plain_text;
    hks_cipher_text.output_text = cipher_text_with_tag;

    return hks_access_symmetric_encrypt_decrypt(key, key_param, crypt_param, &hks_cipher_text,
        HKS_OPERATION_MODE_ENCRYPT);
}

HKS_DLL_API_PUBLIC int32_t hks_symmetric_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    struct hks_blob *plain_text, const struct hks_blob *cipher_text_with_tag)
{
    hks_if_status_error_return(hks_is_valid_symmetric_key_param(key_param));
    hks_if_true_return_error(((key == NULL) || (crypt_param == NULL) || (plain_text == NULL) ||
        (cipher_text_with_tag == NULL)), HKS_ERROR_NULL_POINTER);

    if ((key_param->key_usage & HKS_KEY_USAGE_DECRYPT) == 0)
        return HKS_ERROR_INVALID_ARGUMENT;

    /* key_len is 128/192/256 */
    uint32_t input_key_len = (key_param->key_len / HKS_BITS_PER_BYTES) + HKS_ENCRYPTED_KEY_TAG_LEN +
        HKS_ENCRYPTED_KEY_NONCE_LEN + HKS_ENCRYPTED_KEY_AAD_LEN;

    hks_if_true_return_error(((key->type != HKS_BLOB_TYPE_ENCRYPTED_KEY) || (key->data == NULL) ||
        (key->size != input_key_len)), HKS_ERROR_INVALID_KEY_INFO);

    hks_if_status_error_return(hks_check_symmetric_data_info(key_param, crypt_param, cipher_text_with_tag,
        plain_text, HKS_OPERATION_MODE_DECRYPT));

    struct hks_encrypt_decrypt_text hks_cipher_text;
    hks_cipher_text.input_text = cipher_text_with_tag;
    hks_cipher_text.output_text = plain_text;

    return hks_access_symmetric_encrypt_decrypt(key, key_param, crypt_param, &hks_cipher_text,
        HKS_OPERATION_MODE_DECRYPT);
}

#endif
