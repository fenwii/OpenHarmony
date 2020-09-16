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

#include "hks_service.h"

#include <mbedtls/ctr_drbg.h>
#include <mbedtls/ecdh.h>
#include <mbedtls/entropy.h>
#include <mbedtls/platform.h>
#include <mbedtls/sha1.h>
#ifdef _SECURE_ENVIREMENT_NMI_
#include <openssl/curve25519.h>
#else
#include <ec_local.h>
#endif

#include "securec.h"

#include "common/hks_bn.h"
#include "common/hks_common.h"
#include "common/hks_hardware_random.h"
#include "common/hks_log_utils.h"
#include "common/hks_mem.h"
#include "hks_errno.h"
#include "hks_rkc.h"

#define HKS_BN_MOD_SHIFT_DEC 4 /* bn mod Dec bit shift */
#define HKS_BN_MOD_SHIFT_HEX 16 /* bn mod Hex bit shift */

static int32_t hks_service_generate_x25519_key(struct hks_blob *pri_key,
    struct hks_blob *pub_key);

static int32_t hks_service_hmac(const struct hks_blob *key, uint32_t alg,
    const struct hks_blob *src_data, struct hks_blob *output);

static int32_t hks_service_bn_exp_mod_check(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e, const struct hks_blob *n);

static int32_t hks_service_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag);

static int32_t hks_service_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *cipher_text_with_tag,
    struct hks_blob *plain_text);

static int32_t hks_mbedtls_hash(uint32_t alg, const unsigned char *input,
    size_t ilen, unsigned char *output);

#ifdef _SECURE_ENVIREMENT_NMI_
int32_t hks_key_info_init_sign(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info)
{
    hks_if_true_return_error(((key_alias == NULL) || (key_info == NULL)), HKS_ERROR_NULL_POINTER);

    uint32_t key_size = 0;
    int32_t res = hks_storage_get_key_size(key_alias, &key_size);

    if ((res != HKS_SUCCESS) || (key_size <= 0))
        return HKS_ERROR_INVALID_PRIVATE_KEY;

    res = hks_blob_material_init(&(key_info->private_key));
    hks_if_status_error_return(res);

    key_info->private_key->type = HKS_BLOB_TYPE_KEY;
    key_info->private_key->size = CRYPTO_SECRET_KEY_BYTES;
    res = hks_malloc_init_ptr(CRYPTO_SECRET_KEY_BYTES, &(key_info->private_key->data));
    hks_if_status_error_return(res);
    key_info->public_key = NULL;

    return res;
}

int32_t hks_key_info_init_verify(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info)
{
    hks_if_true_return_error(((key_alias == NULL) || (key_info == NULL)), HKS_ERROR_NULL_POINTER);

    uint32_t key_size = 0;
    int32_t res = hks_storage_get_key_size(key_alias, &key_size);

    if ((res != HKS_SUCCESS) || (key_size <= 0))
        return HKS_ERROR_INVALID_PUBLIC_KEY;

    res = hks_blob_material_init(&(key_info->public_key));
    hks_if_status_error_return(res);

    key_info->public_key->type = HKS_BLOB_TYPE_KEY;
    key_info->public_key->size = CRYPTO_PUBLIC_KEY_BYTES;
    if (key_alias->type == HKS_BLOB_TYPE_ALIAS) {
        res = hks_malloc_init_ptr(CRYPTO_PUBLIC_KEY_BYTES, &(key_info->public_key->data));
        hks_if_status_error_return(res);
    }
    key_info->private_key = NULL;

    return res;
}

int32_t hks_key_info_init_generate(struct hks_storage_key_info *key_info)
{
    hks_if_true_return_error((key_info == NULL), HKS_ERROR_NULL_POINTER);

    size_t private_key_len = CRYPTO_SECRET_KEY_BYTES;
    size_t pub_key_len = CRYPTO_PUBLIC_KEY_BYTES;

    int32_t status = hks_blob_material_init(&(key_info->private_key));

    hks_if_status_error_return(status);
    status = hks_blob_material_init(&(key_info->public_key));
    hks_if_status_error_return(status);

    status = hks_blob_init(key_info->private_key, sizeof(uint8_t), private_key_len, HKS_BLOB_TYPE_KEY);
    hks_if_status_error_return(status);
    status = hks_blob_init(key_info->public_key, sizeof(uint8_t), pub_key_len, HKS_BLOB_TYPE_KEY);
    hks_if_status_error_return(status);

    return status;
}

int32_t hks_key_material_init_symmetric(struct hks_storage_key_info *key_info,
    struct hks_encrypt_material *key_material, const struct hks_key_param *key_param)
{
    hks_if_true_return_error(((key_info == NULL) || (key_material == NULL) || (key_param == NULL)),
        HKS_ERROR_NULL_POINTER);

    size_t private_key_len = key_param->key_len / HKS_BITS_PER_BYTES;

    /* 1.init key_info, only private_key is needed */
    int32_t status = hks_blob_material_init(&(key_info->private_key));

    if (status != HKS_STATUS_OK)
        return status;

    status = hks_blob_init(key_info->private_key, sizeof(uint8_t), private_key_len, HKS_BLOB_TYPE_KEY);
    if (status != HKS_STATUS_OK)
        return status;

    /* 2.init key_material: used to encrypt/decrypt raw_key/encrypted_key */
    status = hks_encrypt_material_init(key_material);
    if (status != HKS_STATUS_OK)
        return status;

    /* init cipher_text_with_tag, nonce_blob and aad blob */
    status = hks_blob_init(key_material->cipher_text, sizeof(uint8_t),
        private_key_len + HKS_ENCRYPTED_KEY_TAG_LEN, HKS_BLOB_TYPE_CIPHER_TEXT);
    if (status != HKS_STATUS_OK)
        return status;

    status = hks_blob_init(key_material->nonce_blob, sizeof(uint8_t),
        HKS_ENCRYPTED_KEY_NONCE_LEN, HKS_BLOB_TYPE_IV);
    if (status != HKS_STATUS_OK)
        return status;

    status = hks_blob_init(key_material->aad_blob, sizeof(uint8_t),
        HKS_ENCRYPTED_KEY_AAD_LEN, HKS_BLOB_TYPE_AAD);

    return status;
}

static int32_t hks_unserialize_encrypted_key(const struct hks_blob *key,
    const struct hks_key_param *key_param, struct hks_encrypt_material *key_material)
{
    uint32_t input_key_size = (key_param->key_len / HKS_BITS_PER_BYTES) + HKS_ENCRYPTED_KEY_TAG_LEN +
        HKS_ENCRYPTED_KEY_NONCE_LEN + HKS_ENCRYPTED_KEY_AAD_LEN;

    if (key->size != input_key_size)
        return HKS_ERROR_INVALID_KEY_INFO;

    size_t cipher_text_len = key_param->key_len / HKS_BITS_PER_BYTES + HKS_ENCRYPTED_KEY_TAG_LEN;

    /* unserialize encrypted key info */
    if (memcpy_s(key_material->cipher_text->data, key_material->cipher_text->size, key->data, cipher_text_len) != EOK)
        return HKS_ERROR_BAD_STATE;

    if (memcpy_s(key_material->nonce_blob->data, key_material->nonce_blob->size,
        key->data + cipher_text_len, HKS_ENCRYPTED_KEY_NONCE_LEN) != EOK)
        return HKS_ERROR_BAD_STATE;

    if (memcpy_s(key_material->aad_blob->data, key_material->aad_blob->size,
        key->data + cipher_text_len + HKS_ENCRYPTED_KEY_NONCE_LEN, HKS_ENCRYPTED_KEY_AAD_LEN) != EOK)
        return HKS_ERROR_BAD_STATE;

    return HKS_STATUS_OK;
}

static int32_t hks_serialize_encrypted_key(struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_encrypt_material *key_material)
{
    uint32_t min_key_size = (key_param->key_len / HKS_BITS_PER_BYTES) + HKS_ENCRYPTED_KEY_TAG_LEN +
        HKS_ENCRYPTED_KEY_NONCE_LEN + HKS_ENCRYPTED_KEY_AAD_LEN;

    if (key->size < min_key_size)
        return HKS_ERROR_BUFFER_TOO_SMALL;

    size_t cipher_text_len = (key_param->key_len / HKS_BITS_PER_BYTES) + HKS_ENCRYPTED_KEY_TAG_LEN;

    /* return err: actual encypted_key_len not equal to the expected len */
    if (key_material->cipher_text->size != cipher_text_len)
        return HKS_ERROR_INVALID_ARGUMENT;

    /* serialize encrypted key info */
    if (memcpy_s(key->data, cipher_text_len, key_material->cipher_text->data, cipher_text_len) != EOK)
        return HKS_ERROR_BAD_STATE;

    if (memcpy_s(key->data + cipher_text_len, HKS_ENCRYPTED_KEY_NONCE_LEN,
        key_material->nonce_blob->data, key_material->nonce_blob->size) != EOK)
        return HKS_ERROR_BAD_STATE;

    if (memcpy_s(key->data + cipher_text_len + HKS_ENCRYPTED_KEY_NONCE_LEN, HKS_ENCRYPTED_KEY_AAD_LEN,
        key_material->aad_blob->data, key_material->aad_blob->size) != EOK)
        return HKS_ERROR_BAD_STATE;

    key->size = min_key_size;

    return HKS_STATUS_OK;
}

int32_t hks_init_get_encrypted_key_info(const struct hks_blob *key,
    const struct hks_key_param *key_param, struct hks_storage_key_info *key_info,
    struct hks_encrypt_material *key_material)
{
    hks_if_true_return_error(((key == NULL) || (key->data == NULL) || (key_info == NULL) || (key_material == NULL) ||
        (key_param == NULL)), HKS_ERROR_NULL_POINTER);

    int32_t status = hks_key_material_init_symmetric(key_info, key_material, key_param);

    if (status != HKS_STATUS_OK)
        return status;

    /* after init, key_material's params are not NULL */
    status = hks_unserialize_encrypted_key(key, key_param, key_material);

    return status;
}

static int32_t hks_generate_ed25519_key(struct hks_storage_key_info *key_info)
{
    hks_if_true_return_error(((key_info->public_key == NULL) || (key_info->private_key == NULL)),
        HKS_ERROR_NULL_POINTER);

    hks_if_true_return_error(((key_info->public_key->size != CRYPTO_PUBLIC_KEY_BYTES) ||
        (key_info->private_key->size != CRYPTO_SECRET_KEY_BYTES)), HKS_ERROR_INVALID_ARGUMENT);

    struct hks_blob *private_key = key_info->private_key;
    struct hks_blob *pub_key = key_info->public_key;

    ED25519_keypair(pub_key->data, private_key->data);

    return HKS_SUCCESS;
}

static int32_t hks_service_generate_key_nmi(const struct hks_blob *generate_key)
{
    struct hks_encrypt_material *key_material = (struct hks_encrypt_material *)generate_key->data;

    if ((key_material == NULL) || (key_material->plain_text == NULL) ||
        (key_material->nonce_blob == NULL) || (key_material->cipher_text == NULL) ||
        (key_material->aad_blob == NULL) || (key_material->key_info == NULL))
        return HKS_ERROR_NULL_POINTER;

    int32_t status = hks_generate_ed25519_key(key_material->key_info);

    if (status != HKS_STATUS_OK)
        return status;
    if ((key_material->plain_text->size != CRYPTO_SECRET_KEY_BYTES) || (key_material->plain_text->data == NULL))
        return HKS_ERROR_INVALID_ARGUMENT;

    if (memcpy_s(key_material->plain_text->data, CRYPTO_SECRET_KEY_BYTES,
        key_material->key_info->private_key->data, CRYPTO_SECRET_KEY_BYTES) != EOK)
        return HKS_ERROR_BAD_STATE;

    status = hks_storage_encrypt_key_blob(key_material->cipher_text, key_material->sealing_alg,
        key_material->plain_text, key_material->nonce_blob, key_material->aad_blob);

    return status;
}

static int32_t hks_service_asymmetric_sign_nmi(const struct hks_blob *key_material,
    const struct hks_blob *hash, struct hks_blob *signature)
{
    struct hks_encrypt_material *encrypt_material = (struct hks_encrypt_material *)key_material->data;

    if ((encrypt_material == NULL) || (encrypt_material->plain_text == NULL) ||
        (encrypt_material->nonce_blob == NULL) || (encrypt_material->cipher_text == NULL) ||
        (encrypt_material->aad_blob == NULL) || (encrypt_material->key_info == NULL))
        return HKS_ERROR_NULL_POINTER;

    int32_t status = hks_storage_decrypt_key_blob(encrypt_material->plain_text,
        encrypt_material->sealing_alg, encrypt_material->cipher_text, encrypt_material->nonce_blob,
        encrypt_material->aad_blob);

    hks_if_status_error_return(status);

    status = hks_fill_key_info(encrypt_material->key_info->param, encrypt_material->plain_text,
        encrypt_material->key_info);
    hks_if_status_error_return(status);

    if ((encrypt_material->key_info->private_key->data == NULL) ||
        (encrypt_material->key_info->private_key->size != CRYPTO_SECRET_KEY_BYTES))
        return HKS_ERROR_INVALID_PRIVATE_KEY;

    if (ED25519_sign(signature->data, hash->data, hash->size,
        encrypt_material->key_info->private_key->data) != HKS_BOOL_TRUE)
        status = HKS_FAILURE;

    return status;
}

static int32_t hks_service_asymmetric_verify_nmi(const struct hks_blob *key_material,
    const struct hks_blob *hash, const struct hks_blob *signature)
{
    struct hks_encrypt_material *encrypt_material = (struct hks_encrypt_material *)key_material->data;

    if ((encrypt_material == NULL) || (encrypt_material->plain_text == NULL) ||
        (encrypt_material->nonce_blob == NULL) || (encrypt_material->cipher_text == NULL) ||
        (encrypt_material->aad_blob == NULL) || (encrypt_material->key_info == NULL))
        return HKS_ERROR_NULL_POINTER;

    int32_t status = hks_storage_decrypt_key_blob(encrypt_material->plain_text,
        encrypt_material->sealing_alg, encrypt_material->cipher_text, encrypt_material->nonce_blob,
        encrypt_material->aad_blob);

    hks_if_status_error_return(status);

    status = hks_fill_key_info(encrypt_material->key_info->param, encrypt_material->plain_text,
        encrypt_material->key_info);
    hks_if_status_error_return(status);

    if ((encrypt_material->key_info->public_key->data == NULL) ||
        (encrypt_material->key_info->public_key->size != CRYPTO_PUBLIC_KEY_BYTES))
        return HKS_ERROR_INVALID_PUBLIC_KEY;

    if (ED25519_verify(hash->data, hash->size, signature->data,
        encrypt_material->key_info->public_key->data) != HKS_BOOL_TRUE)
        status = HKS_FAILURE;

    return status;
}

static int32_t hks_service_import_public_key_nmi(const struct hks_blob *key_alias)
{
    struct hks_encrypt_material *key_material = (struct hks_encrypt_material *)key_alias->data;

    if ((key_material == NULL) || (key_material->plain_text == NULL) ||
        (key_material->nonce_blob == NULL) || (key_material->cipher_text == NULL) ||
        (key_material->aad_blob == NULL))
        return HKS_ERROR_NULL_POINTER;

    return hks_storage_encrypt_key_blob(key_material->cipher_text, key_material->sealing_alg,
        key_material->plain_text, key_material->nonce_blob, key_material->aad_blob);
}

static int32_t hks_service_export_public_key_nmi(const struct hks_blob *key_material)
{
    struct hks_encrypt_material *encrypt_material = (struct hks_encrypt_material *)key_material->data;

    if ((encrypt_material == NULL) || (encrypt_material->plain_text == NULL) ||
        (encrypt_material->nonce_blob == NULL) || (encrypt_material->cipher_text == NULL) ||
        (encrypt_material->aad_blob == NULL) || (encrypt_material->key_info == NULL))
        return HKS_ERROR_NULL_POINTER;

    int32_t status = hks_storage_decrypt_key_blob(encrypt_material->plain_text,
        encrypt_material->sealing_alg, encrypt_material->cipher_text, encrypt_material->nonce_blob,
        encrypt_material->aad_blob);

    hks_if_status_error_return(status);

    status = hks_fill_key_info(encrypt_material->key_info->param, encrypt_material->plain_text,
        encrypt_material->key_info);

    if ((status == HKS_STATUS_OK) && (encrypt_material->key_info->public_key->size != CRYPTO_PUBLIC_KEY_BYTES))
        return HKS_ERROR_INVALID_PUBLIC_KEY;

    return status;
}

static int32_t check_generate_symmetric_key_args(const struct hks_blob *output_key,
    const struct hks_encrypt_material *key_material)
{
    if ((output_key == NULL) || (output_key->data == NULL) || (key_material == NULL) ||
        (key_material->nonce_blob == NULL) || (key_material->cipher_text == NULL) ||
        (key_material->aad_blob == NULL) || (key_material->key_info == NULL) ||
        (key_material->key_info->param == NULL) || (key_material->key_info->private_key == NULL))
        return HKS_ERROR_NULL_POINTER;

    if ((key_material->cipher_text->data == NULL) || (key_material->nonce_blob->data == NULL) ||
        (key_material->aad_blob->data == NULL) || (key_material->key_info->private_key->data == NULL))
        return HKS_ERROR_NULL_POINTER;

    return HKS_SUCCESS;
}

int32_t hks_service_generate_symmetric_key(struct hks_blob *output_key, struct hks_encrypt_material *key_material)
{
    int32_t status = check_generate_symmetric_key_args(output_key, key_material);

    if (status != HKS_SUCCESS)
        return status;

    struct hks_blob *private_key = key_material->key_info->private_key;

    /* 1. generate random as private_key */
    status = hks_gen_random(private_key->data, private_key->size);

    if (status != HKS_SUCCESS)
        return status;

    /* 2. encrypt private_key: using gen_random nonce and aad */
    uint32_t sealing_alg = 0;

    status = hks_gen_random(key_material->nonce_blob->data, key_material->nonce_blob->size);
    if (status != HKS_SUCCESS)
        return status;

    status = hks_gen_random(key_material->aad_blob->data, key_material->aad_blob->size);
    if (status != HKS_SUCCESS)
        return status;

    status = hks_storage_encrypt_key_blob(key_material->cipher_text, sealing_alg, private_key,
        key_material->nonce_blob, key_material->aad_blob);
    if (status != HKS_SUCCESS)
        return status;

    /* 3. serialize encrypted key_info */
    return hks_serialize_encrypted_key(output_key, key_material->key_info->param, key_material);
}

int32_t hks_service_symmetric_encrypt_decrypt(struct hks_encrypt_material *key_material,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *input_text, struct hks_blob *output_text,
    uint32_t operation_mode)
{
    if ((key_material == NULL) || (key_material->nonce_blob == NULL) ||
        (key_material->cipher_text == NULL) || (key_material->aad_blob == NULL) ||
        (key_material->key_info == NULL) || (key_material->key_info->param == NULL) ||
        (key_material->key_info->private_key == NULL))
        return HKS_ERROR_NULL_POINTER;

    /* 1. get raw_key */
    uint32_t sealing_alg = 0;
    struct hks_blob *private_key = key_material->key_info->private_key;
    struct hks_key_param *key_param = key_material->key_info->param;

    if (private_key->data == NULL)
        return HKS_ERROR_NULL_POINTER;
    if (private_key->size != (key_param->key_len / HKS_BITS_PER_BYTES))
        return HKS_ERROR_INVALID_ARGUMENT;

    int32_t status = hks_storage_decrypt_key_blob(private_key, sealing_alg,
        key_material->cipher_text, key_material->nonce_blob, key_material->aad_blob);

    if (status != HKS_SUCCESS)
        return status;

    /* 2. encrypt or decrypt input */
    if (operation_mode == HKS_OPERATION_MODE_ENCRYPT)
        status = hks_mbedtls_symmetric_encrypt(private_key, key_param, crypt_param, input_text, output_text);
    else if (operation_mode == HKS_OPERATION_MODE_DECRYPT)
        status = hks_mbedtls_symmetric_decrypt(private_key, key_param, crypt_param, input_text, output_text);
    else
        return HKS_ERROR_NOT_SUPPORTED;

    return status;
}
#endif

#ifndef _SUPPORT_HKS_TEE_
static int32_t hks_service_asymmetric_verify_init(
    const struct hks_blob *key_alias, struct hks_key_param *param,
    struct hks_blob *public_key, struct hks_storage_key_info *key_info);

static int32_t hks_service_verify_with_alias(const struct hks_blob *key_alias,
    struct hks_blob *public_key,
    struct hks_key_param *param, struct hks_storage_key_info *key_info);

int32_t hks_service_generate_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param)
{
    hks_if_true_return_error(((key_alias == NULL) || (key_param == NULL)), HKS_ERROR_NULL_POINTER);

#ifdef _SECURE_ENVIREMENT_NMI_
    if (key_alias->type == HKS_BLOB_TYPE_MATERIAL)
        return hks_service_generate_key_nmi(key_alias);
    else
        return HKS_ERROR_INVALID_ARGUMENT;
#else
    if (hks_is_key_can_store(key_alias,
        HKS_LOCAL_STORAGE_KEY_MAX_NUM) != HKS_BOOL_TRUE)
        return HKS_ERROR_INSUFFICIENT_STORAGE;
    struct hks_storage_key_info key_info;

    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));

    key_info.param = (struct hks_key_param *)key_param;
    struct hks_blob private_key;
    struct hks_blob pub_key = HKS_BLOB_DEFAULT_VALUE;
    size_t private_key_len = CRYPTO_SECRET_KEY_BYTES;
    size_t pub_key_len = CRYPTO_PUBLIC_KEY_BYTES;

    int32_t status = hks_blob_init(&private_key, sizeof(uint8_t),
        private_key_len, HKS_BLOB_TYPE_KEY);

    hks_if_status_error_return(status);
    status = hks_blob_init(&pub_key, sizeof(uint8_t), pub_key_len, HKS_BLOB_TYPE_KEY);
    hks_if_status_error_goto_error(status, exit);
    if (key_param->key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519) {
        status = HKS_ERROR_INVALID_ARGUMENT;
        goto exit;
    }
    struct hks_blob tmp;

    tmp.data = private_key.data;
    tmp.size = CRYPTO_PUBLIC_KEY_BYTES;
    hks_service_get_random(&tmp);

    ED25519_public_from_private(pub_key.data, private_key.data);
    (void)memcpy_s(private_key.data + CRYPTO_PUBLIC_KEY_BYTES,
        CRYPTO_PUBLIC_KEY_BYTES, pub_key.data, CRYPTO_PUBLIC_KEY_BYTES);

    key_info.private_key = &private_key;
    key_info.public_key = &pub_key;
    if (key_alias->type == HKS_BLOB_TYPE_ALIAS)
        status = hks_storage_write_key_info(key_alias, &key_info);
    else
        status = HKS_STATUS_OK;

exit:
    hks_blob_destroy(&pub_key);
    hks_blob_destroy(&private_key);
    hks_check_return_code(status, &status);
    return status;
#endif
}
#endif

#if defined(_HILINK_PRODUCT_)  /* hilink replace generate random */
static int32_t hks_service_generate_x25519_key(struct hks_blob *pri_key,
    struct hks_blob *pub_key)
{
    mbedtls_ecdh_context *ctx_cli = NULL;
    size_t ctx_cli_size = sizeof(*ctx_cli);

    ctx_cli = (mbedtls_ecdh_context *)HKS_MALLOC(ctx_cli_size);
    hks_if_true_return_error((ctx_cli == NULL), HKS_ERROR_INSUFFICIENT_MEMORY);
    (void)memset_s(ctx_cli, ctx_cli_size, 0, ctx_cli_size);

    mbedtls_ecdh_init(ctx_cli);
    /* Client: inialize context and generate keypair */
    int32_t ret = mbedtls_ecp_group_load(&ctx_cli->grp, MBEDTLS_ECP_DP_CURVE25519);

    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_ecdh_gen_public(&ctx_cli->grp, &ctx_cli->d, &ctx_cli->Q,
        hilink_hardware_poll, NULL);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_mpi_write_binary(&ctx_cli->d, pri_key->data, CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_mpi_write_binary(&ctx_cli->Q.X, pub_key->data, CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    hks_endian_swap(pub_key->data, CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    ret = HKS_SUCCESS;
    pri_key->size = CRYPTO_PUBLIC_KEY_BYTES;
    pub_key->size = CRYPTO_PUBLIC_KEY_BYTES;
exit:
    mbedtls_ecdh_free(ctx_cli);
    hks_free_ptr(ctx_cli);
    int32_t status = (int32_t)ret;

    hks_check_return_code(status, &status);
    return status;
}
#else
static int32_t hks_service_generate_x25519_key(struct hks_blob *pri_key,
    struct hks_blob *pub_key)
{
    const char pers[] = "ecdh";
    mbedtls_ecdh_context ctx_cli;
    mbedtls_ctr_drbg_context ctr_drbg;

    mbedtls_ecdh_init(&ctx_cli);
    mbedtls_ctr_drbg_init(&ctr_drbg);

    /* Initialize random number generation */
    mbedtls_entropy_context entropy;

    mbedtls_entropy_init(&entropy);
    int ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func,
        &entropy, (const unsigned char *)pers, sizeof(pers));
    hks_if_status_error_goto_error(ret, exit);

    /* Client: inialize context and generate keypair */
    ret = mbedtls_ecp_group_load(&ctx_cli.grp, MBEDTLS_ECP_DP_CURVE25519);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_ecdh_gen_public(&ctx_cli.grp, &ctx_cli.d, &ctx_cli.Q,
        mbedtls_ctr_drbg_random, &ctr_drbg);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_mpi_write_binary(&ctx_cli.d, pri_key->data, CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_mpi_write_binary(&ctx_cli.Q.X, pub_key->data, CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    hks_endian_swap(pub_key->data, CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    ret = HKS_SUCCESS;
    pri_key->size = CRYPTO_PUBLIC_KEY_BYTES;
    pub_key->size = CRYPTO_PUBLIC_KEY_BYTES;
exit:
    mbedtls_ecdh_free(&ctx_cli);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
    int32_t status = (int32_t)ret;

    hks_check_return_code(status, &status);
    return status;
}
#endif

int32_t hks_service_generate_asymmetric_key(
    const struct hks_key_param *key_param, struct hks_blob *pri_key,
    struct hks_blob *pub_key)
{
    hks_if_true_return_error((key_param == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((pri_key == NULL) || (pub_key == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((pri_key->data == NULL) || (pub_key->data == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((pri_key->size < CRYPTO_PUBLIC_KEY_BYTES) ||
        (pub_key->size < CRYPTO_PUBLIC_KEY_BYTES), HKS_ERROR_INVALID_ARGUMENT);
    int32_t status;

    if (key_param->key_type == hks_key_type_ecc_key_pair(
        HKS_ECC_CURVE_CURVE25519))
        status = hks_service_generate_x25519_key(pri_key, pub_key);
    else
        status = HKS_ERROR_NOT_SUPPORTED;

    hks_check_return_code(status, &status);
    return status;
}

int32_t hks_service_aead_encrypt_ex(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag)
{
    hks_if_true_return_error(((key == NULL) || (key_param == NULL) || (crypt_param == NULL) ||
        (plain_text == NULL) || (cipher_text_with_tag == NULL)), HKS_ERROR_NULL_POINTER);

    hks_if_true_return_error((key_param->key_mode != HKS_ALG_GCM), HKS_ERROR_NOT_SUPPORTED);
    hks_if_true_return_error((
        (key_param->key_len != HKS_MAX_KEY_LEN_128) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_192) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_256)),
        HKS_ERROR_NOT_SUPPORTED);

    return hks_service_aead_encrypt(key, key_param, crypt_param,
        plain_text, cipher_text_with_tag);
}

int32_t hks_service_aead_decrypt_ex(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *cipher_text_with_tag,
    struct hks_blob *plain_text)
{
    hks_if_true_return_error(((key == NULL) || (key_param == NULL) || (crypt_param == NULL) ||
        (cipher_text_with_tag == NULL) || (plain_text == NULL)), HKS_ERROR_NULL_POINTER);

    hks_if_true_return_error((key_param->key_mode != HKS_ALG_GCM), HKS_ERROR_NOT_SUPPORTED);
    hks_if_true_return_error((
        (key_param->key_len != HKS_MAX_KEY_LEN_128) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_192) &&
        (key_param->key_len != HKS_MAX_KEY_LEN_256)),
        HKS_ERROR_NOT_SUPPORTED);
    hks_if_true_return_error((plain_text == NULL), HKS_ERROR_NULL_POINTER);

    return hks_service_aead_decrypt(key, key_param, crypt_param,
        cipher_text_with_tag, plain_text);
}

static int32_t hks_get_size_from_algrithom(uint32_t alg, uint32_t *output_size)
{
    if (output_size == NULL)
        return HKS_ERROR_NULL_POINTER;

    *output_size = 0;
    if ((alg == hks_alg_hmac(HKS_ALG_HASH_SHA_256)) || (alg == HKS_ALG_HASH_SHA_256))
        *output_size = HKS_HASH256_MIN_OUT_SIZE;

    if ((alg == hks_alg_hmac(HKS_ALG_HASH_SHA_512)) || (alg == HKS_ALG_HASH_SHA_512))
        *output_size = HKS_HASH512_MIN_OUT_SIZE;

    return HKS_STATUS_OK;
}

int32_t hks_service_hmac_ex(const struct hks_blob *key,
    uint32_t alg, const struct hks_blob *src_data, struct hks_blob *output)
{
    hks_if_true_return_error(((key == NULL) || (key->data == NULL) || (key->size <= 0)), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error(((alg != hks_alg_hmac(HKS_ALG_HASH_SHA_256)) &&
        (alg != hks_alg_hmac(HKS_ALG_HASH_SHA_512))), HKS_ERROR_INVALID_ARGUMENT);
    hks_if_true_return_error(((src_data == NULL) || (src_data->data == NULL) || (src_data->size <= 0)),
        HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error(((output == NULL) || (output->data == NULL)), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((((alg == hks_alg_hmac(HKS_ALG_HASH_SHA_256)) &&
        (output->size < HKS_HASH256_MIN_OUT_SIZE)) || ((alg == hks_alg_hmac(HKS_ALG_HASH_SHA_512)) &&
        (output->size < HKS_HASH512_MIN_OUT_SIZE))), HKS_ERROR_BUF_TOO_SMALL);

    /* hmac key len not less than hash output size */
    hks_if_true_return_error((((alg == hks_alg_hmac(HKS_ALG_HASH_SHA_256)) &&
        (key->size < HKS_HASH256_MIN_OUT_SIZE))), HKS_ERROR_INVALID_ARGUMENT);
    hks_if_true_return_error((((alg == hks_alg_hmac(HKS_ALG_HASH_SHA_512)) &&
        (key->size < HKS_HASH512_MIN_OUT_SIZE))), HKS_ERROR_INVALID_ARGUMENT);

    int32_t status = hks_service_hmac(key, alg, src_data, output);

    hks_check_return_code(status, &status);

    status = hks_get_size_from_algrithom(alg, &output->size);
    hks_if_status_error_return(status);

    return status;
}

static int32_t hks_service_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag)
{
    size_t encrypt_length = 0;
    int32_t status = 0;

    struct hks_aead_data aead_data;

    aead_data.nonce = crypt_param->nonce.data;
    aead_data.nonce_length = crypt_param->nonce.size;
    aead_data.additional_data = crypt_param->aad.data;
    aead_data.additional_data_length = crypt_param->aad.size;
    aead_data.ciphertext = cipher_text_with_tag->data;
    aead_data.ciphertext_length = cipher_text_with_tag->size;
    aead_data.plaintext = plain_text->data;
    aead_data.plaintext_length = plain_text->size;

    int32_t encrypt_status = hks_mbedtls_aead_encrypt(key, key_param,
        &aead_data, &encrypt_length);

    hks_check_return_code(encrypt_status, &status);
    if (status != HKS_STATUS_OK)
        return status;

    if (encrypt_length < UINT32_MAX) {
        cipher_text_with_tag->size = (uint32_t)encrypt_length;
        status = HKS_STATUS_OK;
    } else {
        status = HKS_ERROR_DATA_CORRUPT;
    }

    hks_check_return_code(status, &status);
    return status;
}

static int32_t hks_service_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *cipher_text_with_tag,
    struct hks_blob *plain_text)
{
    size_t plain_text_length = 0;
    struct hks_aead_data aead_data;

    aead_data.nonce = crypt_param->nonce.data;
    aead_data.nonce_length = crypt_param->nonce.size;
    aead_data.additional_data = crypt_param->aad.data;
    aead_data.additional_data_length = crypt_param->aad.size;
    aead_data.ciphertext = cipher_text_with_tag->data;
    aead_data.ciphertext_length = cipher_text_with_tag->size;
    aead_data.plaintext = plain_text->data;
    aead_data.plaintext_length = plain_text->size;

    int32_t decrypt_status = hks_mbedtls_aead_decrypt(key, key_param,
        &aead_data, &plain_text_length);
    int32_t status = 0;

    hks_check_return_code(decrypt_status, &status);
    if (status != HKS_STATUS_OK)
        return status;

    if (plain_text_length < UINT32_MAX) {
        plain_text->size = (uint32_t)plain_text_length;
        status = HKS_STATUS_OK;
    } else {
        status = HKS_ERROR_DATA_CORRUPT;
    }
    hks_check_return_code(status, &status);
    return status;
}

int32_t hks_service_key_derivation(struct hks_blob *derived_key,
    const struct hks_blob *kdf_key, const struct hks_blob *salt,
    const struct hks_blob *label, const struct hks_key_param *key_params)
{
    hks_if_true_return_error(((derived_key == NULL) || (kdf_key == NULL) || (salt == NULL) ||
        (label == NULL) || (key_params == NULL)), HKS_ERROR_NULL_POINTER);

    hks_if_true_return_error((derived_key->data == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((derived_key->size < HKS_DERIVED_KEY_MIN_OUT_SIZE), HKS_ERROR_BUFFER_TOO_SMALL);
    hks_if_true_return_error(((kdf_key->data == NULL) || (kdf_key->size <= 0)), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error(((key_params->key_type != HKS_KEY_TYPE_DERIVE) ||
        (key_params->key_usage != HKS_KEY_USAGE_DERIVE)), HKS_ERROR_INVALID_ARGUMENT);
    hks_if_true_return_error(((key_params->key_mode != hks_alg_hkdf(HKS_ALG_HASH_SHA_256)) &&
        (key_params->key_mode != hks_alg_hkdf(HKS_ALG_HASH_SHA_512))), HKS_ERROR_INVALID_ARGUMENT);
    hks_if_true_return_error(((key_params->key_len != HKS_MAX_KEY_LEN_128) &&
        (key_params->key_len != HKS_MAX_KEY_LEN_256)), HKS_ERROR_INVALID_ARGUMENT);
    hks_if_true_return_error(((salt->data == NULL) || (label->data == NULL)), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error(((salt->size < HKS_SALT_MAX_SIZE) || (label->size < HKS_SALT_MAX_SIZE)),
        HKS_ERROR_INVALID_ARGUMENT);

    int32_t status = hks_mbedtls_key_derivation(derived_key, key_params->key_mode, kdf_key, salt, label);
    return status;
}

/*
 * private_key.data is generate by hks ,so must be big endian
 * peer_public_key.data are come from outside, make sure it's little endian
 */
int32_t hks_service_key_agreement(struct hks_blob *agreed_key,
    const struct hks_key_param *private_key_param,
    const struct hks_blob *private_key,
    const struct hks_blob *peer_public_key,
    const uint32_t agreement_alg)
{
    hks_if_true_return_error(((agreed_key == NULL) || (private_key_param == NULL) || (private_key == NULL) ||
        (peer_public_key == NULL)), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((private_key->size != CRYPTO_PUBLIC_KEY_BYTES), HKS_ERROR_INVALID_PRIVATE_KEY);
    hks_if_true_return_error((peer_public_key->size != CRYPTO_PUBLIC_KEY_BYTES), HKS_ERROR_INVALID_PUBLIC_KEY);

    (void)agreement_alg;

    mbedtls_ecdh_context *ctx_cli = NULL;
    size_t ctx_cli_size = sizeof(*ctx_cli);

    ctx_cli = (mbedtls_ecdh_context *)HKS_MALLOC(ctx_cli_size);
    hks_if_true_return_error((ctx_cli == NULL),
        HKS_ERROR_INSUFFICIENT_MEMORY);
    (void)memset_s(ctx_cli, ctx_cli_size, 0, ctx_cli_size);

    mbedtls_ecdh_init(ctx_cli);
    int32_t ret = mbedtls_ecp_group_load(&ctx_cli->grp,
        MBEDTLS_ECP_DP_CURVE25519);

    hks_if_status_error_goto_error(ret, exit);

    /* set the elliptic curve initial coordinates */
    ret = mbedtls_mpi_lset(&ctx_cli->Qp.Z, 1);
    hks_if_status_error_goto_error(ret, exit);

    uint8_t peer_public_key_data[CRYPTO_PUBLIC_KEY_BYTES] = { 0 };

    ret = memcpy_s(peer_public_key_data, CRYPTO_PUBLIC_KEY_BYTES,
        peer_public_key->data, peer_public_key->size);
    hks_if_status_error_goto_error(ret, exit);

    ret = hks_endian_swap(peer_public_key_data, CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_mpi_read_binary(&ctx_cli->Qp.X, peer_public_key_data,
        CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_ecp_check_pubkey(&ctx_cli->grp, &ctx_cli->Qp);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_mpi_read_binary(&ctx_cli->d, private_key->data,
        CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_ecdh_compute_shared(&ctx_cli->grp, &ctx_cli->z,
        &ctx_cli->Qp, &ctx_cli->d, NULL, NULL);
    hks_if_status_error_goto_error(ret, exit);

    ret = mbedtls_mpi_write_binary(&ctx_cli->z, agreed_key->data,
        CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    ret = hks_endian_swap(agreed_key->data, CRYPTO_PUBLIC_KEY_BYTES);
    hks_if_status_error_goto_error(ret, exit);

    agreed_key->size = CRYPTO_PUBLIC_KEY_BYTES;
    ret = HKS_SUCCESS;

exit:
    mbedtls_ecdh_free(ctx_cli);
    hks_free_ptr(ctx_cli);
    int32_t status = mbedtls_to_hks_error(ret);

    hks_check_return_code(status, &status);
    return status;
}

int32_t hks_service_get_random(struct hks_blob *random)
{
    hks_if_true_return_error((random == NULL), HKS_ERROR_NULL_POINTER);
    int32_t status = hks_gen_random(random->data, random->size);

    hks_check_return_code(status, &status);
    return status;
}

static int32_t hks_service_hmac(const struct hks_blob *key, uint32_t alg,
    const struct hks_blob *src_data, struct hks_blob *output)
{
    int32_t status = 0;

    switch (alg) {
#if defined(MBEDTLS_SHA256_C)
    case hks_alg_hmac(HKS_ALG_HASH_SHA_256):
        status = mbedtls_md_hmac(
            mbedtls_md_info_from_type(MBEDTLS_MD_SHA256),
            key->data, key->size, src_data->data, src_data->size,
            output->data);
        break;
#endif
#if defined(MBEDTLS_SHA512_C)
    case hks_alg_hmac(HKS_ALG_HASH_SHA_384):
        status = mbedtls_md_hmac(
            mbedtls_md_info_from_type(MBEDTLS_MD_SHA384),
            key->data, key->size, src_data->data, src_data->size,
            output->data);
        break;
    case hks_alg_hmac(HKS_ALG_HASH_SHA_512):
        status = mbedtls_md_hmac(
            mbedtls_md_info_from_type(MBEDTLS_MD_SHA512),
            key->data, key->size, src_data->data, src_data->size,
            output->data);
        break;
#endif
    default:
        return (hks_alg_is_hash(alg) ? HKS_ERROR_NOT_SUPPORTED :
            HKS_ERROR_INVALID_ARGUMENT);
    }

    return mbedtls_to_hks_error(status);
}

/* an encapsulation function for mbedtls hash processing */
static int32_t hks_mbedtls_hash(uint32_t alg, const unsigned char *input,
    size_t ilen, unsigned char *output)
{
    int32_t ret = 0;

    switch (alg) {
#if defined(MBEDTLS_SHA256_C)
    case HKS_ALG_SHA_224:
        ret = mbedtls_sha256_ret(input, ilen, output, 1);
        break;
    case HKS_ALG_SHA_256:
        ret = mbedtls_sha256_ret(input, ilen, output, 0);
        break;
#endif
#if defined(MBEDTLS_SHA512_C)
    case HKS_ALG_SHA_384:
        ret = mbedtls_sha512_ret(input, ilen, output, 1);
        break;
    case HKS_ALG_SHA_512:
        ret = mbedtls_sha512_ret(input, ilen, output, 0);
        break;
#endif
    default:
        return (hks_alg_is_hash(alg) ? HKS_ERROR_NOT_SUPPORTED :
            HKS_ERROR_INVALID_ARGUMENT);
    }
    return mbedtls_to_hks_error(ret);
}

int32_t hks_service_hash(uint32_t alg, const struct hks_blob *src_data,
    struct hks_blob *hash)
{
    hks_if_true_return_error(((alg != HKS_ALG_HASH_SHA_256) &&
        (alg != HKS_ALG_HASH_SHA_512)), HKS_ERROR_INVALID_ARGUMENT);
    hks_if_true_return_error(((src_data == NULL) || (src_data->data == NULL) ||
        (src_data->size <= 0)), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error(((hash == NULL) || (hash->data == NULL)),
        HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((((alg == HKS_ALG_HASH_SHA_256) &&
        (hash->size < HKS_HASH256_MIN_OUT_SIZE)) ||
        ((alg == HKS_ALG_HASH_SHA_512) &&
        (hash->size < HKS_HASH512_MIN_OUT_SIZE))),
        HKS_ERROR_BUF_TOO_SMALL);

    int32_t status = hks_mbedtls_hash(alg, src_data->data, src_data->size,
        hash->data);

    hks_check_return_code(status, &status);

    status = hks_get_size_from_algrithom(alg, &hash->size);
    hks_if_status_error_return(status);

    return status;
}

#ifndef _SUPPORT_HKS_TEE_
int32_t hks_service_asymmetric_sign(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    struct hks_blob *signature)
{
    hks_if_true_return_error(((key_alias == NULL) || (key_param == NULL) || (hash == NULL) ||
        (signature == NULL)), HKS_ERROR_NULL_POINTER);

#ifdef _SECURE_ENVIREMENT_NMI_
    if (key_alias->type == HKS_BLOB_TYPE_MATERIAL)
        return hks_service_asymmetric_sign_nmi(key_alias, hash, signature);
    else
        return HKS_ERROR_INVALID_ARGUMENT;
#else
    hks_if_true_return_error((signature == NULL), HKS_ERROR_NULL_POINTER);
    if ((key_param->key_usage & HKS_KEY_USAGE_SIGN) == 0)
        return HKS_ERROR_NOT_SUPPORTED;

    if ((signature->data == NULL) || (signature->size < CRYPTO_BYTES))
        return HKS_ERROR_BUFFER_TOO_SMALL;

    uint32_t key_size = 0;
    int32_t res = hks_storage_get_key_size(key_alias, &key_size);

    if ((res != HKS_SUCCESS) || (key_size <= 0))
        return HKS_ERROR_INVALID_PRIVATE_KEY;

    struct hks_key_param param;
    struct hks_blob  private_key;
    struct hks_storage_key_info key_info;

    (void)memset_s(&param, sizeof(param), 0, sizeof(param));
    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));

    private_key.type = HKS_BLOB_TYPE_KEY;
    private_key.size = CRYPTO_SECRET_KEY_BYTES;
    res = hks_malloc_init_ptr(CRYPTO_SECRET_KEY_BYTES,
        &(private_key.data));
    hks_if_status_error_goto_error(res, exit);

    res = hks_malloc_init_ptr(HKS_AUTH_ID_MAX_SIZE,
        &(param.key_auth_id.data));
    hks_if_status_error_goto_error(res, exit);
    param.key_auth_id.size = HKS_AUTH_ID_MAX_SIZE;

    key_info.param = &param;
    key_info.public_key = NULL;
    key_info.private_key = &private_key;

    res = hks_storage_read_key_info(key_alias, &key_info);
    if (res != HKS_SUCCESS)
        goto exit;

    if ((private_key.data == NULL) || (private_key.size != CRYPTO_SECRET_KEY_BYTES)) {
        res = HKS_ERROR_INVALID_PRIVATE_KEY;
        goto exit;
    }
    if (ED25519_sign(signature->data, hash->data, hash->size,
        private_key.data + CRYPTO_PUBLIC_KEY_BYTES, private_key.data) != HKS_BOOL_TRUE)
        res = HKS_FAILURE;

exit:
    hks_blob_destroy(&private_key);
    hks_free_ptr(param.key_auth_id.data);
    hks_check_return_code(res, &res);
    return res;
#endif
}
#endif

static int32_t hks_service_bn_exp_mod_check(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e,
    const struct hks_blob *n)
{
    hks_if_true_return_error((x->data == NULL), HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error(((a->data == NULL) || (a->size <= 0)),
        HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error(((e->data == NULL) || (e->size <= 0)),
        HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error(((n->data == NULL) || (n->size <= 0)),
        HKS_ERROR_NULL_POINTER);
    hks_if_true_return_error((x->size < n->size),
        HKS_ERROR_INVALID_ARGUMENT);
    return HKS_STATUS_OK;
}

int32_t hks_service_bn_exp_mod(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e,
    const struct hks_blob *n)
{
    hks_if_true_return_error(((x == NULL) || (a == NULL) || (e == NULL) || (n == NULL)), HKS_ERROR_NULL_POINTER);

    int32_t status = hks_service_bn_exp_mod_check(x, a, e, n);

    hks_if_status_error_return(status);
    mbedtls_mpi bn_x, bn_a, bn_e, bn_n;

    /* init param & allocate memory */
    hks_bn_init(&bn_x);
    hks_bn_init(&bn_a);
    hks_bn_init(&bn_e);
    hks_bn_init(&bn_n);

    /* import data to mbedtls */
    status = hks_bn_import(&bn_a, a->data, a->size);
    hks_if_status_error_goto_error(status, error);
    status = hks_bn_import(&bn_e, e->data, e->size);
    hks_if_status_error_goto_error(status, error);
    status = hks_bn_import(&bn_n, n->data, n->size);
    hks_if_status_error_goto_error(status, error);

    /* caculate mod */
    status = hks_bn_mpi_exp_mod(&bn_x, &bn_a, &bn_e, &bn_n);
    hks_if_status_error_goto_error(status, error);

    /* export data to blob */
    status = hks_bn_export(&bn_x, x->data, x->size);
error:
    hks_bn_free(&bn_x);
    hks_bn_free(&bn_a);
    hks_bn_free(&bn_e);
    hks_bn_free(&bn_n);
    hks_check_return_code(status, &status);
    return status;
}

#ifndef _SUPPORT_HKS_TEE_
int32_t hks_service_asymmetric_verify(const struct hks_blob *key_alias,
    const struct hks_blob *hash, const struct hks_blob *signature)
{
    hks_if_true_return_error(((key_alias == NULL) || (hash == NULL) || (signature == NULL)), HKS_ERROR_NULL_POINTER);

#ifdef _SECURE_ENVIREMENT_NMI_
    if (key_alias->type == HKS_BLOB_TYPE_MATERIAL)
        return hks_service_asymmetric_verify_nmi(key_alias, hash, signature);
#endif
    struct hks_key_param param;
    struct hks_blob  public_key = HKS_BLOB_DEFAULT_VALUE;
    struct hks_storage_key_info key_info;

    (void)memset_s(&param, sizeof(param), 0, sizeof(param));
    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));

    int32_t ret = hks_service_asymmetric_verify_init(key_alias,
        &param, &public_key, &key_info);

    if (ret != HKS_STATUS_OK)
        goto exit;

    if (ED25519_verify(hash->data, hash->size, signature->data,
        public_key.data) == HKS_BOOL_TRUE)
        ret = HKS_SUCCESS;
    else
        ret = HKS_FAILURE;
exit:
    if (key_alias->type == HKS_BLOB_TYPE_ALIAS) {
        hks_free_ptr(public_key.data);
        hks_free_ptr(param.key_auth_id.data);
    }
    return ret;
}

static int32_t hks_service_verify_with_alias(const struct hks_blob *key_alias,
    struct hks_blob *public_key,
    struct hks_key_param *param, struct hks_storage_key_info *key_info)
{
    uint32_t key_size = 0;
    int32_t res = hks_storage_get_key_size(key_alias, &key_size);

    hks_if_true_return_error(((res != HKS_SUCCESS) || (key_size <= 0)),
        HKS_ERROR_INVALID_PUBLIC_KEY);
    res = hks_malloc_init_ptr(CRYPTO_PUBLIC_KEY_BYTES,
        &(public_key->data));
    hks_if_status_error_goto_error(res, exit);
    res = hks_malloc_init_ptr(HKS_AUTH_ID_MAX_SIZE,
        &(param->key_auth_id.data));
    hks_if_status_error_goto_error(res, exit);
    param->key_auth_id.size = HKS_AUTH_ID_MAX_SIZE;
    res = hks_storage_read_key_info(key_alias, key_info);
    if (res != HKS_SUCCESS)
        goto exit;

    if (key_info->public_key->size != CRYPTO_PUBLIC_KEY_BYTES) {
        res = HKS_ERROR_INVALID_PUBLIC_KEY;
        goto exit;
    }
exit:
    if (res != HKS_STATUS_OK) {
        hks_free_ptr(public_key->data);
        hks_free_ptr(param->key_auth_id.data);
    }
    return res;
}
#else
int32_t hks_service_asymmetric_verify(const struct hks_blob *key_alias,
                                      const struct hks_blob *hash, const struct hks_blob *signature)
{
    if (ED25519_verify(hash->data, hash->size, signature->data, key_alias->data) == HKS_BOOL_TRUE)
        return HKS_SUCCESS;
    else
        return HKS_FAILURE;
}
#endif

#ifndef _SUPPORT_HKS_TEE_
static int32_t hks_service_asymmetric_verify_init(
    const struct hks_blob *key_alias, struct hks_key_param *param,
    struct hks_blob *public_key, struct hks_storage_key_info *key_info)
{
    public_key->type = HKS_BLOB_TYPE_KEY;
    public_key->size = CRYPTO_PUBLIC_KEY_BYTES;
    key_info->param = param;
    key_info->public_key = public_key;
    key_info->private_key = NULL;

    if (key_alias->type == HKS_BLOB_TYPE_ALIAS) {
        int32_t res = hks_service_verify_with_alias(key_alias,
            public_key, param, key_info);

        hks_if_status_error_return(res);
    } else if (key_alias->type == HKS_BLOB_TYPE_KEY) {
        public_key->data = key_alias->data;
        public_key->size = key_alias->size;
    }
    hks_if_true_return_error((public_key->data == NULL),
        HKS_ERROR_INVALID_KEY_INFO);
    hks_if_true_return_error((public_key->size < CRYPTO_PUBLIC_KEY_BYTES),
        HKS_ERROR_BUFFER_TOO_SMALL);
    return HKS_STATUS_OK;
}

int32_t hks_service_import_public_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *key)
{
    hks_if_true_return_error(((key_alias == NULL) || (key_param == NULL) || (key == NULL)), HKS_ERROR_NULL_POINTER);

#ifdef _SECURE_ENVIREMENT_NMI_
    if (key_alias->type == HKS_BLOB_TYPE_MATERIAL)
        return hks_service_import_public_key_nmi(key_alias);
#endif
    if (hks_is_key_can_store(key_alias,
        HKS_LOCAL_STORAGE_KEY_MAX_NUM) != HKS_BOOL_TRUE)
        return HKS_ERROR_INSUFFICIENT_STORAGE;

    struct hks_storage_key_info key_info;

    key_info.param = (struct hks_key_param *)key_param;
    key_info.public_key = (struct hks_blob *)key;
    key_info.private_key = NULL;
    key_info.reserve[0] = 0;
    key_info.reserve[1] = 0;

    return hks_storage_write_key_info(key_alias, &key_info);
}

int32_t hks_service_export_public_key(const struct hks_blob *key_alias,
    struct hks_blob *key)
{
    hks_if_true_return_error(((key_alias == NULL) || (key == NULL)), HKS_ERROR_NULL_POINTER);

#ifdef _SECURE_ENVIREMENT_NMI_
    if (key_alias->type == HKS_BLOB_TYPE_MATERIAL)
        return hks_service_export_public_key_nmi(key_alias);
#endif
    struct hks_storage_key_info key_info;

    key_info.param = NULL;
    key_info.private_key = NULL;
    key_info.public_key = key;
    key_info.reserve[0] = 0;
    key_info.reserve[1] = 0;
    int32_t status = hks_storage_read_key_info(key_alias, &key_info);

    if (status == HKS_STATUS_OK &&
        key_info.public_key->size != CRYPTO_PUBLIC_KEY_BYTES)
        return HKS_ERROR_INVALID_PUBLIC_KEY;
    return status;
}

int32_t hks_service_delete_key(const struct hks_blob *key_alias)
{
    return hks_storage_remove_key_info(key_alias);
}

int32_t hks_service_get_key_param(const struct hks_blob *key_alias,
    struct hks_key_param *key_param)
{
    struct hks_storage_key_info key_info;

    key_info.param = key_param;
    key_info.private_key = NULL;
    key_info.public_key = NULL;
    key_info.reserve[0] = 0;
    key_info.reserve[1] = 0;

#ifdef _SECURE_ENVIREMENT_NMI_
    return hks_storage_read_key_param(key_alias, &key_info);
#else
    return hks_storage_read_key_info(key_alias, &key_info);
#endif
}

int32_t hks_service_is_key_exist(const struct hks_blob *key_alias)
{
    uint32_t size = 0;
    int32_t status = hks_storage_get_key_size(key_alias, &size);

    if (status != HKS_STATUS_OK)
        return status;

    if ((size > 0) && (hks_is_key_exist_in_store(key_alias) ==
        HKS_BOOL_TRUE))
        return HKS_STATUS_OK;
    return HKS_ERROR_KEY_NOT_EXIST;
}

int32_t hks_service_register_file_callbacks(
    struct hks_file_callbacks *callbacks)
{
    if (callbacks == NULL)
        return HKS_ERROR_NULL_POINTER;

    return hks_file_register_callbacks(callbacks);
}

int32_t hks_service_get_pub_key_alias_list(
    struct hks_blob *key_alias_list, uint32_t *list_count)
{
    if ((key_alias_list == NULL) || (list_count == NULL))
        return HKS_ERROR_NULL_POINTER;

    return hks_get_key_alias_list(key_alias_list, list_count);
}

int32_t hks_service_key_info_init(void)
{
    log_info("hks init : begin");
    int32_t is_key_info_exist = HKS_BOOL_FALSE;
    int32_t status;
#ifdef _SECURE_ENVIREMENT_NMI_
    hks_file_liteos_init();
#endif
    status = hks_load_file_to_buffer(HKS_KEY_STORE_FILE_NAME, &is_key_info_exist);
    hks_if_status_error_return(status);

#ifndef _SECURE_ENVIREMENT_NMI_
    status = hks_rkc_init(NULL, is_key_info_exist);
    hks_if_status_error_return(status);
#endif
    log_info("hks init : end");
    return status;
}

void hks_service_destroy(void)
{
    hks_storage_destroy();
#ifndef _SECURE_ENVIREMENT_NMI_
    hks_rkc_destroy();
#endif
}

int32_t hks_service_refresh_key_info(void)
{
    int32_t status = hks_storage_clean_key_info();
    hks_if_status_error_return(status);

#ifndef _SECURE_ENVIREMENT_NMI_
    hks_rkc_destroy();
    status = hks_rkc_init(NULL, HKS_BOOL_FALSE);
#endif
    return status;
}
#endif

int32_t hks_service_register_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback)
{
    return hks_reg_get_hardware_udid_callback(callback);
}
