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

#include "huks_adapter.h"
#include <securec.h>
#include <stdio.h>
#include "log.h"
#include "mem_stat.h"
#include "commonutil.h"
#include "hks_file_api.h"
#include "hks_client.h"

#define HC_HKDF_KEY_LEN    128
#define HC_AES_GCM_KEY_LEN 128
#define HC_PARAM_CHAIN_LEN 255
#define HC_PARAM_KEY_LEN   256

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
static const uint8_t g_factor[] = "hichain_key_enc_key";
static const int32_t g_cert_chain_cnt = 4;

void build_keyparam_ext(struct hks_key_param *param)
{
    param->key_param_ext.wrap_flag = 1; /* 1: use tee interface */
    param->key_param_ext.storage_flag = 1; /* reserve */

    param->key_param_ext.data_creator.type = HKS_BLOB_TYPE_RAW;
    param->key_param_ext.data_creator.size = 0;
    param->key_param_ext.data_creator.data = NULL;

    param->key_param_ext.data_owner.type = HKS_BLOB_TYPE_RAW;
    param->key_param_ext.data_owner.size = 0;
    param->key_param_ext.data_owner.data = NULL;

    param->key_param_ext.ext_info.type = HKS_BLOB_TYPE_RAW;
    param->key_param_ext.ext_info.size = 0;
    param->key_param_ext.ext_info.data = NULL;
}

#endif

union huks_key_type_union {
    struct huks_key_type type_struct;
    uint32_t key_type;
};

#define CREATE_STRUCT(T) \
    struct T *create_struct_##T(void) \
    { \
        struct T *val = (struct T *)MALLOC(sizeof(struct T)); \
        if (val == NULL) { \
            return NULL; \
        } \
        (void)memset_s(val, sizeof(*val), 0, sizeof(*val)); \
        return val; \
    }

#define CONVERT_TO_BLOB(T, field_name) \
    struct hks_blob convert_to_blob_from_##T(struct T *val) \
    { \
        struct hks_blob hks_blob_val; \
        (void)memset_s(&hks_blob_val, sizeof(hks_blob_val), 0, sizeof(hks_blob_val)); \
        check_ptr_return_val(val->field_name, hks_blob_val); \
        check_num_return_val(val->length, hks_blob_val); \
        hks_blob_val.data = val->field_name; \
        hks_blob_val.size = val->length; \
        return hks_blob_val; \
    }

CREATE_STRUCT(hc_key_alias)
CREATE_STRUCT(sha256_value)
CREATE_STRUCT(uint8_buff)

CONVERT_TO_BLOB(hc_key_alias, key_alias)
CONVERT_TO_BLOB(ltpk, ltpk)
CONVERT_TO_BLOB(sha256_value, sha256_value)
CONVERT_TO_BLOB(sha512_value, sha512_value)
CONVERT_TO_BLOB(signature, signature)
CONVERT_TO_BLOB(stpk, stpk)
CONVERT_TO_BLOB(stsk, stsk)
CONVERT_TO_BLOB(hc_auth_id, auth_id)

static const uint8_t G_KEY_TYPE_PAIRS[HC_MAX_KEY_TYPE_NUM][HC_KEY_TYPE_PAIR_LEN] = {
    { 0x00, 0x00 }, /* ACCESSOR_PK */
    { 0x00, 0x01 }, /* CONTROLLER_PK */
    { 0x00, 0x02 }, /* ed25519 KEYPAIR */
    { 0x00, 0x03 }, /* KEK ,key encryption key, used only by DeviceAuthService */
    { 0x00, 0x04 }, /* DEK,data encryption key, used only by upper apps */
    { 0x00, 0x05 }  /* key tmp */
};

static const char *g_large_prime_number_hex_348 =
     "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74"\
    "020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F1437"\
    "4FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"\
    "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF05"\
    "98DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB"\
    "9ED529077096966D670C354E4ABC9804F1746C08CA18217C32905E462E36CE3B"\
    "E39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9DE2BCBF695581718"\
    "3995497CEA956AE515D2261898FA051015728E5A8AAAC42DAD33170D04507A33"\
    "A85521ABDF1CBA64ECFB850458DBEF0A8AEA71575D060C7DB3970F85A6E1E4C7"\
    "ABF5AE8CDB0933D71E8C94E04A25619DCEE3D2261AD2EE6BF12FFA06D98A0864"\
    "D87602733EC86A64521F2B18177B200CBBE117577A615D6C770988C0BAD946E2"\
    "08E24FA074E5AB3143DB5BFCE0FD108E4B82D120A93AD2CAFFFFFFFFFFFFFFFF";

static const char *g_large_prime_number_hex_256 =
    "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74"\
    "020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F1437"\
    "4FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"\
    "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF05"\
    "98DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB"\
    "9ED529077096966D670C354E4ABC9804F1746C08CA18217C32905E462E36CE3B"\
    "E39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9DE2BCBF695581718"\
    "3995497CEA956AE515D2261898FA051015728E5A8AACAA68FFFFFFFFFFFFFFFF";

static int32_t hks_hex_string_to_byte(const char *src, uint8_t *dst, uint32_t dst_size)
{
    size_t length = strlen(src);
    if (length % 2 != 0) { /* odd number or not */
        LOGE("Invalid hex_string length: %zu, even num is expected", length);
        return ERROR_CODE_FAILED;
    }

    uint32_t hex_length = length / BYTE_TO_HEX_OPER_LENGTH; /* Calculate hexadecimal length */
    if (dst_size < hex_length) {
        LOGE("Invalid dst_size: %u is smaller than hex_length: %u", dst_size, hex_length);
        return ERROR_CODE_FAILED;
    }

    uint8_t nibble[2]; /* create an array of two elements */
    for (uint32_t i = 0; i < hex_length; i++) {
        nibble[0] = src[i * BYTE_TO_HEX_OPER_LENGTH];
        nibble[1] = src[i * BYTE_TO_HEX_OPER_LENGTH + 1];
        for (uint32_t j = 0; j < BYTE_TO_HEX_OPER_LENGTH; j++) { /* iterate through array */
            if ((nibble[j] <= 'F') && (nibble[j] >= 'A')) {
                nibble[j] = nibble[j] - 'A' + 10; /* hex conversion */
            } else if ((nibble[j] <= 'f') && (nibble[j] >= 'a')) {
                nibble[j] = nibble[j] - 'a' + 10; /* hex conversion */
            } else if ((nibble[j] >= '0') && (nibble[j] <= '9')) {
                nibble[j] = nibble[j] - '0';
            } else {
                LOGE("Invalid char: [%c] in hex string, [0-9]|[A-F]|[a-f] expected", (char)nibble[j]);
                return ERROR_CODE_FAILED;
            }
        }
        dst[i] = nibble[0] << 4; /* shift left for filling */
        dst[i] |= nibble[1];
    }
    return ERROR_CODE_SUCCESS;
}

static struct sha256_value sha256(const struct uint8_buff *message)
{
    struct sha256_value sha256_value;
    (void)memset_s(&sha256_value, sizeof(sha256_value), 0, sizeof(sha256_value));

    struct hks_blob src_data = {
        .data = message->val,
        .size = message->length,
        .type = HKS_BLOB_TYPE_RAW
    };
    struct hks_blob hash;
    (void)memset_s(&hash, sizeof(hash), 0, sizeof(hash));
    hash.data = (uint8_t *)MALLOC(HC_SHA256_LEN * sizeof(uint8_t));
    if (hash.data == NULL) {
        LOGE("SHA256 malloc failed");
        return sha256_value;
    }
    hash.size = HC_SHA256_LEN;
    int32_t hks_status = hks_hash(HKS_ALG_HASH_SHA_256, &src_data, &hash);
    if ((hks_status == 0) && (hash.size == HC_SHA256_LEN)) {
        (void)memcpy_s(sha256_value.sha256_value, sizeof(sha256_value.sha256_value), hash.data, HC_SHA256_LEN);
        sha256_value.length = HC_SHA256_LEN;
    } else {
        LOGE("SHA256 failed, status=%d", hks_status);
        sha256_value.length = 0;
    }
    safe_free(hash.data);
    return sha256_value;
}

int32_t cal_bignum_exp(struct var_buffer *base, struct var_buffer *exp,
    const uint32_t big_num_len, struct big_num *out_result)
{
    check_ptr_return_val(base, HC_INPUT_ERROR);
    check_ptr_return_val(exp, HC_INPUT_ERROR);
    check_ptr_return_val(out_result, HC_INPUT_ERROR);

    if ((big_num_len != HC_BIG_PRIME_MAX_LEN_384) && (big_num_len != HC_BIG_PRIME_MAX_LEN_256)) {
        LOGE("Not support big number len %d", big_num_len);
        return HC_LARGE_PRIME_NUMBER_LEN_UNSUPPORT;
    }

    struct hks_blob a;
    a.type = HKS_BLOB_TYPE_RAW;
    a.data = base->data;
    a.size = base->length;

    struct hks_blob e;
    e.type = HKS_BLOB_TYPE_RAW;
    e.data = exp->data;
    e.size = exp->length;

    struct hks_blob n;
    n.type = HKS_BLOB_TYPE_RAW;
    uint8_t *large_num = (uint8_t *)MALLOC(big_num_len);
    if (large_num == NULL) {
        LOGE("Malloc big num buff fail");
        return ERROR_CODE_FAILED;
    }

    (void)memset_s(large_num, big_num_len, 0, big_num_len);
    int32_t status;

    if (big_num_len == HC_BIG_PRIME_MAX_LEN_384) {
        status = hks_hex_string_to_byte(g_large_prime_number_hex_348, large_num, big_num_len);
    } else {
        status = hks_hex_string_to_byte(g_large_prime_number_hex_256, large_num, big_num_len);
    }

    if (status != ERROR_CODE_SUCCESS) {
        FREE(large_num);
        return ERROR_CODE_FAILED;
    }
    n.data = large_num;
    n.size = big_num_len;

    struct hks_blob x;
    x.type = 0;
    x.data = out_result->big_num;
    x.size = big_num_len;
    status = hks_bn_exp_mod(&x, &a, &e, &n);
    FREE(large_num);
    if (status != ERROR_CODE_SUCCESS) {
        LOGE("Huks bn exp mod error, status=%d", status);
        return ERROR_CODE_FAILED;
    }
    out_result->length = x.size;

    return ERROR_CODE_SUCCESS;
}

struct random_value generate_random(uint32_t length)
{
    struct random_value rand;
    (void)memset_s(&rand, sizeof(rand), 0, sizeof(rand));
    if ((length == 0) || (length > HC_RAMDOM_MAX_LEN)) {
        LOGE("Generate random failed, invalid param length: %d", length);
        return rand;
    }

    struct hks_blob hks_rand;
    hks_rand.type = HKS_BLOB_TYPE_RAW;
    hks_rand.data = rand.random_value;
    hks_rand.size = length;
    int32_t status = hks_generate_random(&hks_rand);
    if (status == 0) {
        rand.length = hks_rand.size;
    } else {
        LOGE("Huks generate random failed, status: %d", status);
    }

    return rand;
}

int32_t compute_hmac(struct var_buffer *key, const struct uint8_buff *message, struct hmac *out_hmac)
{
    check_ptr_return_val(key, HC_INPUT_ERROR);
    check_ptr_return_val(message, HC_INPUT_ERROR);
    check_ptr_return_val(out_hmac, HC_INPUT_ERROR);

    struct hks_blob hks_key;
    hks_key.size = key->length;
    hks_key.data = key->data;
    hks_key.type = HKS_KEY_USAGE_EXPORT;
    uint32_t alg = HKS_ALG_HMAC(HKS_ALG_HASH_SHA_256);

    struct hks_blob src_data;
    src_data.type = HKS_BLOB_TYPE_RAW;
    src_data.size = message->length;
    src_data.data = message->val;

    struct hks_blob output;
    output.type = HKS_BLOB_TYPE_RAW;
    output.data = out_hmac->hmac;
    output.size = HC_HMAC_LEN;

    /* make hmac */
    int32_t status = hks_hmac(&hks_key, alg, &src_data, &output);
    if (status != 0) {
        LOGE("Huks hmac failed, status: %d", status);
        return ERROR_CODE_FAILED;
    }
    out_hmac->length = output.size;

    return ERROR_CODE_SUCCESS;
}

int32_t compute_hkdf(struct var_buffer *shared_secret, struct hc_salt *salt,
    char *key_info, uint32_t hkdf_len, struct var_buffer *out_hkdf)
{
    check_ptr_return_val(shared_secret, HC_INPUT_ERROR);
    check_ptr_return_val(salt, HC_INPUT_ERROR);
    check_ptr_return_val(out_hkdf, HC_INPUT_ERROR);
    check_ptr_return_val(key_info, HC_INPUT_ERROR);

    struct hks_blob derived_key;
    derived_key.type = HKS_BLOB_TYPE_RAW;
    derived_key.data = out_hkdf->data;
    derived_key.size = hkdf_len;
    /* derived key param */
    struct hks_key_param key_param;

    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    key_param.key_len = HC_HKDF_KEY_LEN;
    key_param.key_type = HKS_KEY_TYPE_DERIVE;
    key_param.key_usage = HKS_KEY_USAGE_DERIVE;
    key_param.key_mode = HKS_ALG_HKDF(HKS_ALG_HASH_SHA_256);
    key_param.key_pad = HKS_PADDING_NONE;
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    build_keyparam_ext(&key_param);
#endif

    /* original key */
    struct hks_blob kdf_key;
    kdf_key.size = shared_secret->length;
    kdf_key.data = shared_secret->data;
    kdf_key.type = (uint8_t)HKS_KEY_TYPE_AES;

    struct hks_blob hks_salt;
    hks_salt.type = HKS_BLOB_TYPE_RAW;
    hks_salt.data = salt->salt;
    hks_salt.size = salt->length;

    struct hks_blob label;
    label.type = HKS_BLOB_TYPE_RAW;
    label.data = (uint8_t *)key_info;
    label.size = (uint32_t)strlen(key_info);
    /* make hkdf */
    int32_t status = hks_key_derivation(&derived_key, &key_param, &kdf_key, &hks_salt, &label);
    if (status != 0) {
        LOGE("Huks key derivation failed, status: %d", status);
        return ERROR_CODE_FAILED;
    }
    out_hkdf->length = derived_key.size;

    return ERROR_CODE_SUCCESS;
}

static void init_aes_gcm_encrypt_key_params(struct hks_key_param *key_params)
{
    (void)memset_s(key_params, sizeof(*key_params), 0, sizeof(*key_params));
    key_params->key_type = HKS_KEY_TYPE_AES;
    key_params->key_len = HC_AES_GCM_KEY_LEN;
    key_params->key_usage = HKS_KEY_USAGE_ENCRYPT;
    key_params->key_mode = HKS_ALG_GCM;
    key_params->key_pad = HKS_PADDING_NONE;
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    build_keyparam_ext(key_params);
#endif
}

static void crypt_param_fill(struct random_value *iv, struct aes_aad *aad, struct hks_crypt_param *param)
{
    (void)memset_s(param, sizeof(*param), 0, sizeof(*param));
    param->nonce.data = iv->random_value;
    param->nonce.size = iv->length;
    param->nonce.type = HKS_BLOB_TYPE_IV;
    param->aad.data = aad->aad;
    param->aad.size = aad->length;
    param->aad.type = HKS_BLOB_TYPE_AAD;
}

int32_t aes_gcm_encrypt(struct var_buffer *key, const struct uint8_buff *plain,
    struct aes_aad *aad, struct uint8_buff *out_cipher)
{
    check_ptr_return_val(key, HC_INPUT_ERROR);
    check_ptr_return_val(plain, HC_INPUT_ERROR);
    check_ptr_return_val(aad, HC_INPUT_ERROR);
    check_ptr_return_val(out_cipher, HC_INPUT_ERROR);

    struct random_value iv = generate_random(HC_IV_MAX_LEN);
    if (iv.length == 0) {
        LOGE("Generate random to make iv failed");
        return HC_GEN_RANDOM_FAILED;
    }
    struct hks_blob hks_key = {
        .type = HKS_BLOB_TYPE_KEY,
        .data = key->data,
        .size = key->length
    };
    struct hks_key_param key_params;

    init_aes_gcm_encrypt_key_params(&key_params);
    struct hks_crypt_param crypt_param;

    crypt_param_fill(&iv, aad, &crypt_param);
    struct hks_blob hks_plain_text;
    hks_plain_text.type = HKS_BLOB_TYPE_PLAIN_TEXT;
    hks_plain_text.data = plain->val;
    hks_plain_text.size = plain->length;

    struct hks_blob tag_cipher;
    tag_cipher.type = HKS_BLOB_TYPE_CIPHER_TEXT;
    tag_cipher.size = hks_plain_text.size + HKS_ENCRYPT_MAX_TAG_SIZE + HC_IV_MAX_LEN;
    tag_cipher.data = (uint8_t *)MALLOC(tag_cipher.size);
    check_ptr_return_val(tag_cipher.data, ERROR_CODE_FAILED);
    int32_t status = hks_aead_encrypt(&hks_key, &key_params, &crypt_param, &hks_plain_text, &tag_cipher);
    if (status != 0) {
        LOGE("Huks aead encrypt error, status: %d", status);
        safe_free(tag_cipher.data);
        return ERROR_CODE_FAILED;
    }
    if (memcpy_s(out_cipher->val, out_cipher->size, iv.random_value, iv.length) != EOK) {
        safe_free(tag_cipher.data);
        return memory_copy_error(__func__, __LINE__);
    }
    if (memcpy_s(out_cipher->val + iv.length, out_cipher->size - iv.length, tag_cipher.data, tag_cipher.size) != EOK) {
        safe_free(tag_cipher.data);
        return memory_copy_error(__func__, __LINE__);
    }
    out_cipher->length = tag_cipher.size + iv.length;
    safe_free(tag_cipher.data);
    return ERROR_CODE_SUCCESS;
}

static void init_aes_gcm_decrypt_key_params(struct hks_key_param *key_params)
{
    (void)memset_s(key_params, sizeof(*key_params), 0, sizeof(*key_params));
    key_params->key_type = HKS_KEY_TYPE_AES;
    key_params->key_usage = HKS_KEY_USAGE_DECRYPT;
    key_params->key_mode = HKS_ALG_GCM;
    key_params->key_pad = HKS_PADDING_NONE;
    key_params->key_len = HC_AES_GCM_KEY_LEN;
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    build_keyparam_ext(key_params);
#endif
}

int32_t aes_gcm_decrypt(struct var_buffer *key, const struct uint8_buff *cipher,
    struct aes_aad *aad, struct uint8_buff *out_plain)
{
    check_ptr_return_val(key, HC_INPUT_ERROR);
    check_ptr_return_val(cipher, HC_INPUT_ERROR);
    check_ptr_return_val(aad, HC_INPUT_ERROR);
    check_ptr_return_val(out_plain, HC_INPUT_ERROR);

    struct hks_blob hks_key = {
        .type = HKS_BLOB_TYPE_KEY,
        .data = key->data,
        .size = key->length
    };
    struct hks_key_param key_params;
    init_aes_gcm_decrypt_key_params(&key_params);
    struct hks_crypt_param crypt_param; /* param filling */
    uint8_t iv[HC_IV_MAX_LEN];

    (void)memset_s(iv, sizeof(iv), 0, sizeof(iv));
    if (cipher->length < sizeof(iv)) {
        LOGE("Cipher length is short than iv max length");
        return ERROR_CODE_FAILED;
    }
    (void)memcpy_s(iv, HC_IV_MAX_LEN, cipher->val, sizeof(iv));
    crypt_param.nonce.data = iv;
    crypt_param.nonce.size = sizeof(iv);
    crypt_param.aad.data = aad->aad;
    crypt_param.aad.size = aad->length;

    struct hks_blob cipher_text_with_tag;
    (void)memset_s(&cipher_text_with_tag, sizeof(cipher_text_with_tag), 0, sizeof(cipher_text_with_tag));
    cipher_text_with_tag.data = cipher->val + sizeof(iv);
    cipher_text_with_tag.size = cipher->length - sizeof(iv);

    struct hks_blob plain_text;
    (void)memset_s(&plain_text, sizeof(plain_text), 0, sizeof(plain_text));
    plain_text.data = (uint8_t *)MALLOC(cipher_text_with_tag.size - HKS_SALT_MAX_SIZE);
    check_ptr_return_val(plain_text.data, ERROR_CODE_FAILED);
    plain_text.size = cipher_text_with_tag.size - HKS_SALT_MAX_SIZE;
    int32_t status = hks_aead_decrypt(&hks_key, &key_params, &crypt_param, &plain_text, &cipher_text_with_tag);
    if (status != 0) {
        LOGE("Huks aead decrypt failed, status: %d", status);
        safe_free(plain_text.data);
        return ERROR_CODE_FAILED;
    }

    if (memcpy_s(out_plain->val, out_plain->size, plain_text.data, plain_text.size) != EOK) {
        safe_free(plain_text.data);
        return memory_copy_error(__func__, __LINE__);
    }
    out_plain->length = plain_text.size;
    safe_free(plain_text.data);

    return status;
}

struct service_id generate_service_id(const struct session_identity *identity)
{
    struct service_id service_id;
    (void)memset_s(&service_id, sizeof(service_id), 0, sizeof(service_id));
    if (identity == NULL) {
        LOGE("Input is null");
        return service_id;
    }

    uint32_t pack_name_len = identity->package_name.length;
    if ((pack_name_len == 0) || (pack_name_len > HC_PACKAGE_NAME_BUFF_LEN)) {
        LOGE("Pack name length is: %u", pack_name_len);
        return service_id;
    }
    uint32_t type_len = identity->service_type.length;
    if ((type_len == 0) || (type_len > HC_SERVICE_TYPE_BUFF_LEN)) {
        LOGE("Service type length is: %u", type_len);
        return service_id;
    }
    uint32_t srv_len = type_len + pack_name_len;
    struct uint8_buff id_buff = {
        .length = srv_len,
        .size = srv_len
    };

    id_buff.val = (uint8_t *)MALLOC(srv_len);
    if (id_buff.val == NULL) {
        LOGE("Malloc mem failed");
        return service_id;
    }

    if (memcpy_s(id_buff.val, srv_len, identity->package_name.name, pack_name_len) != EOK) {
        LOGE("Copy service id buff failed");
        safe_free(id_buff.val);
        return service_id;
    }
    if (memcpy_s(id_buff.val + pack_name_len, srv_len - pack_name_len, identity->service_type.type, type_len) != EOK) {
        LOGE("Copy service id buff failed");
        safe_free(id_buff.val);
        return service_id;
    }

    struct sha256_value srv_sha256 = sha256(&id_buff);
    safe_free(id_buff.val);
    id_buff.val = NULL;

    if (srv_sha256.length > 0) {
        if (memcpy_s(service_id.service_id, HC_SERVICE_ID_BUFF_LEN, srv_sha256.sha256_value, HC_SHA256_LEN) == EOK) {
            service_id.length = srv_sha256.length;
        } else {
            LOGE("Copy hash value failed");
        }
    }

    return service_id;
}

static int32_t convert_byte_to_hex_string(const uint8_t *byte_array, uint32_t byte_array_size,
    uint8_t *hex_string, uint32_t out_size)
{
    int32_t length = 0;

    check_num_return_val(byte_array_size, length);
    if (out_size < (byte_array_size * BYTE_TO_HEX_OPER_LENGTH)) { /* doubleword, length*2 */
        return length;
    }
    uint32_t hex_str_arr_len = (uint32_t)(out_size + 1);
    char *hex_str_arr = (char *)MALLOC(hex_str_arr_len);
    if (hex_str_arr == NULL) {
        LOGE("Copy hex arr to string failed");
        return 0;
    }
    (void)memset_s(hex_str_arr, hex_str_arr_len, 0, hex_str_arr_len);
    for (uint32_t i = 0; i < byte_array_size; i++) {
        if (sprintf_s((char *)(hex_str_arr + length), hex_str_arr_len - length, "%02x", byte_array[i]) < 0) {
            LOGE("What happened was that the probability was zero"); /* caller perceives memery error, no return */
        }
        length += BYTE_TO_HEX_OPER_LENGTH; /* doubleword, length increases 2 each time */
    }
    if (memcpy_s(hex_string, out_size, hex_str_arr, length) != EOK) {
        LOGE("Copy hex arr to string failed");
        length = 0;
    }

    safe_free(hex_str_arr);
    hex_str_arr = NULL;
    return length;
}

struct hc_key_alias generate_key_alias(const struct service_id *service_id,
    const struct hc_auth_id *auth_id, enum huks_key_alias_type key_type)
{
    struct hc_key_alias temp_alias;
    (void)memset_s(&temp_alias, sizeof(temp_alias), 0, sizeof(temp_alias));
    check_ptr_return_val(service_id, temp_alias);
    check_ptr_return_val(auth_id, temp_alias);
    if (key_type >= HC_MAX_KEY_TYPE_NUM) {
        LOGE("Invalid user type");
        return temp_alias;
    }
    if (service_id->length > HC_SERVICE_ID_BUFF_LEN) {
        LOGE("service_id length is error");
        return temp_alias;
    }
    if (auth_id->length > HC_AUTH_ID_BUFF_LEN) {
        LOGE("auth_id length is error");
        return temp_alias;
    }

    uint32_t key_type_pair_size = HC_KEY_TYPE_PAIR_LEN;
    const uint8_t *key_type_pair = G_KEY_TYPE_PAIRS[key_type];
    uint32_t total_len = service_id->length + auth_id->length + key_type_pair_size;
    struct uint8_buff key_alias_buff;

    (void)memset_s(&key_alias_buff, sizeof(key_alias_buff), 0, sizeof(key_alias_buff));
    key_alias_buff.val = (uint8_t *)MALLOC(total_len + 1);
    if (key_alias_buff.val == NULL) {
        LOGE("Malloc key alias buff failed");
        return temp_alias;
    }

    key_alias_buff.size = total_len + 1; /* one character longer for terminator */
    key_alias_buff.length = total_len;
    (void)memset_s(key_alias_buff.val, key_alias_buff.size, 0, key_alias_buff.size);
    (void)memcpy_s(key_alias_buff.val, key_alias_buff.size, service_id->service_id, service_id->length);
    (void)memcpy_s(key_alias_buff.val + service_id->length, key_alias_buff.size - service_id->length,
                   key_type_pair, key_type_pair_size);
    (void)memcpy_s(key_alias_buff.val + service_id->length + key_type_pair_size,
                   key_alias_buff.size - service_id->length - key_type_pair_size,
                   auth_id->auth_id, auth_id->length);

    struct hc_key_alias key_alias;
    (void)memset_s(&key_alias, sizeof(key_alias), 0, sizeof(key_alias));
    struct sha256_value alias_sha256 = sha256(&key_alias_buff);

    safe_free(key_alias_buff.val);
    key_alias_buff.val = NULL;
    if (alias_sha256.length > 0) {
        int32_t length = convert_byte_to_hex_string(alias_sha256.sha256_value, alias_sha256.length,
                                                    key_alias.key_alias, HC_KEY_ALIAS_MAX_LEN);
        key_alias.length = length;
    }
    return key_alias;
}

int32_t generate_st_key_pair(struct st_key_pair *out_key_pair)
{
    check_ptr_return_val(out_key_pair, HC_INPUT_ERROR);
    int32_t error_code = ERROR_CODE_FAILED;
    (void)memset_s(out_key_pair, sizeof(*out_key_pair), 0, sizeof(*out_key_pair));

    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    key_param.key_type = HKS_KEY_TYPE_ECC_KEYPAIR(HKS_ECC_CURVE_CURVE25519);
    key_param.key_usage = HKS_KEY_USAGE_DERIVE;
    key_param.key_mode = HKS_ALG_ECDH(HKS_ALG_SELECT_RAW);

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    build_keyparam_ext(&key_param);
#endif

    struct hks_blob public_key;
    (void)memset_s(&public_key, sizeof(public_key), 0, sizeof(public_key));
    public_key.data = out_key_pair->st_public_key.stpk;
    public_key.size = HC_ST_PUBLIC_KEY_LEN;

    struct hks_blob private_key;
    (void)memset_s(&private_key, sizeof(private_key), 0, sizeof(private_key));
    private_key.data = out_key_pair->st_private_key.stsk;
    private_key.size = HC_ST_PRIVATE_KEY_LEN;
    int32_t hks_status = hks_generate_asymmetric_key(&key_param, &private_key, &public_key);
    if (hks_status == 0) {
        out_key_pair->st_public_key.length = public_key.size;
        out_key_pair->st_private_key.length = private_key.size;
        error_code = ERROR_CODE_SUCCESS;
    }
    return error_code;
}

int32_t generate_lt_key_pair(struct hc_key_alias *key_alias, const struct hc_auth_id *auth_id)
{
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_FAILED;
    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);

    check_num_return_val(hks_key_alias.size, error_code);
    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS;

    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    key_param.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    key_param.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    key_param.key_mode = HKS_ALG_GCM;

    struct hc_auth_id tmp_id = *auth_id;

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    key_param.key_len = HC_PARAM_KEY_LEN; /* interface regulations */
    key_param.key_domain = HKS_ECC_CURVE_ED25519;
    key_param.key_pad = HKS_PADDING_NONE;
    key_param.key_digest = HKS_ALG_HASH_SHA_256;
    key_param.key_param_ext.key_auth_id = convert_to_blob_from_hc_auth_id(&tmp_id);
    key_param.key_param_ext.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    build_keyparam_ext(&key_param);
#else
    key_param.key_len = HC_LT_PUBLIC_KEY_LEN;
    key_param.key_auth_id = convert_to_blob_from_hc_auth_id(&tmp_id);
    key_param.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
#endif

    int32_t hks_status = hks_generate_key(&hks_key_alias, &key_param);
    if (hks_status == 0) {
        error_code = ERROR_CODE_SUCCESS;
    } else {
        LOGE("Hks generate failed, status=%d", hks_status);
    }
    return error_code;
}

int32_t export_lt_public_key(struct hc_key_alias *key_alias, struct ltpk *out_public_key)
{
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    check_ptr_return_val(out_public_key, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_FAILED;
    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);

    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS;
    check_num_return_val(hks_key_alias.size, error_code);

    struct hks_blob key;
    (void)memset_s(&key, sizeof(key), 0, sizeof(key));
    key.data = out_public_key->ltpk;
    key.size = HC_LT_PUBLIC_KEY_LEN;
    int32_t hks_status = hks_export_public_key(&hks_key_alias, &key);
    if (hks_status == 0) {
        out_public_key->length = key.size;
        error_code = ERROR_CODE_SUCCESS;
    } else {
        LOGE("Export public key failed, status=%d", hks_status);
    }
    return error_code;
}

int32_t delete_lt_public_key(struct hc_key_alias *key_alias)
{
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    int32_t error_code = ERROR_CODE_FAILED;
    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);

    check_num_return_val(hks_key_alias.size, error_code);
    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS;
    int32_t hks_status = hks_delete_key(&hks_key_alias);
    if (hks_status == 0) {
        error_code = ERROR_CODE_SUCCESS;
    } else {
        LOGE("Delete lt public key failed, status=%d", hks_status);
    }
    return error_code;
}

int32_t import_lt_public_key(struct hc_key_alias *key_alias, struct ltpk *peer_public_key,
    const int32_t user_type, const int32_t pair_type, struct hc_auth_id *auth_id)
{
    if ((pair_type < 0) || (pair_type >= HC_MAX_PAIR_TYPE_NUM)) {
        return HC_INPUT_ERROR;
    }
    if ((user_type < 0) || (user_type >= HC_MAX_KEY_TYPE_NUM)) {
        return HC_INPUT_ERROR;
    }
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    check_ptr_return_val(peer_public_key, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_FAILED;
    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);
    if (hks_key_alias.size == 0) {
        LOGE("Convert key alias to blob failed");
        return error_code;
    }
    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS;

    struct hks_blob ltpk_key = convert_to_blob_from_ltpk(peer_public_key);
    if (ltpk_key.size == 0) {
        LOGE("Convert ltpk key to blob failed");
        return error_code;
    }
    ltpk_key.type = HKS_BLOB_TYPE_KEY;
    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    key_param.key_type = HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519;
    key_param.key_len = ltpk_key.size;
    key_param.key_mode = HKS_ALG_GCM;
    key_param.key_pad = HKS_PADDING_NONE;
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    key_param.key_usage = HKS_KEY_USAGE_VERIFY;
    key_param.key_param_ext.key_role = user_type;
    key_param.key_param_ext.key_auth_id = convert_to_blob_from_hc_auth_id(auth_id);
    key_param.key_param_ext.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    build_keyparam_ext(&key_param);
#else
    union huks_key_type_union huks_key_type;
    huks_key_type.type_struct.user_type = (uint8_t)user_type;
    huks_key_type.type_struct.pair_type = (uint8_t)pair_type;
    huks_key_type.type_struct.reserved1 = (uint8_t)0;
    huks_key_type.type_struct.reserved2 = (uint8_t)0;
    key_param.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    key_param.key_role = (uint32_t)huks_key_type.key_type;
    key_param.key_auth_id = convert_to_blob_from_hc_auth_id(auth_id);
    key_param.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
#endif

    int32_t hks_status = hks_import_public_key(&hks_key_alias, &key_param, &ltpk_key);

    return hks_status;
}

int32_t check_lt_public_key_exist(struct hc_key_alias *key_alias)
{
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    check_num_return_val(key_alias->length, HC_INPUT_ERROR);

    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);
    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS;
    int32_t hks_status = hks_is_key_exist(&hks_key_alias);
    if (hks_status == 0) {
        return ERROR_CODE_SUCCESS;
    } else {
        LOGI("Check lt public key exist failed, status = %d", hks_status);
        return ERROR_CODE_FAILED;
    }
}

static int32_t init_key_alias_list(struct hks_blob *key_alias_list, int32_t len)
{
    (void)memset_s(key_alias_list, sizeof(struct hks_blob) * len, 0, sizeof(struct hks_blob) * len);
    for (int32_t i = 0; i < len; ++i) {
        struct hks_blob key_alias_tmp;
        key_alias_tmp.data = (uint8_t *)MALLOC(HC_KEY_ALIAS_MAX_LEN);
        if (key_alias_tmp.data == NULL) {
            return -1;
        }
        (void)memset_s(key_alias_tmp.data, HC_KEY_ALIAS_MAX_LEN, 0, HC_KEY_ALIAS_MAX_LEN);
        key_alias_tmp.size = HC_KEY_ALIAS_MAX_LEN;
        key_alias_tmp.type = HKS_BLOB_TYPE_ALIAS;
        key_alias_list[i] = key_alias_tmp;
    }
    return 0;
}

static int32_t gen_key_param(struct hks_key_param *key_param)
{
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    key_param->key_param_ext.key_auth_id.data = (uint8_t *)MALLOC(HC_AUTH_ID_BUFF_LEN);
    if (key_param->key_param_ext.key_auth_id.data == NULL) {
#else
    key_param->key_auth_id.data = (uint8_t *)MALLOC(HC_AUTH_ID_BUFF_LEN);
    if (key_param->key_auth_id.data == NULL) {
#endif
        LOGE("Malloc key auth data failed");
        return ERROR_CODE_FAILED;
    }
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    (void)memset_s(key_param->key_param_ext.key_auth_id.data, HC_AUTH_ID_BUFF_LEN, 0, HC_AUTH_ID_BUFF_LEN);
    key_param->key_param_ext.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    key_param->key_param_ext.key_auth_id.size = HC_AUTH_ID_BUFF_LEN;
    build_keyparam_ext(key_param);
#else
    (void)memset_s(key_param->key_auth_id.data, HC_AUTH_ID_BUFF_LEN, 0, HC_AUTH_ID_BUFF_LEN);
    key_param->key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    key_param->key_auth_id.size = HC_AUTH_ID_BUFF_LEN;
#endif

    return EOK;
}

static int32_t inner_get_lt_info(struct hks_blob key_alias, struct huks_key_type *out_key_type,
    struct hc_auth_id *out_auth_id)
{
    int32_t error_code;
    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));

    error_code = gen_key_param(&key_param);
    if (error_code != EOK) {
        goto get_key_info_free;
    }
    int32_t status = hks_get_key_param(&key_alias, &key_param);
    if (status != 0) {
        LOGE("Get huks key param failed");
        goto get_key_info_free;
    }

    union huks_key_type_union key_type_union;

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    key_type_union.key_type = key_param.key_param_ext.key_role;
    *out_key_type = key_type_union.type_struct;
    out_auth_id->length = key_param.key_param_ext.key_auth_id.size;
    error_code = memcpy_s(out_auth_id->auth_id, HC_AUTH_ID_BUFF_LEN,
                          key_param.key_param_ext.key_auth_id.data, key_param.key_param_ext.key_auth_id.size);
#else
    key_type_union.key_type = key_param.key_role;
    *out_key_type = key_type_union.type_struct;
    out_auth_id->length = key_param.key_auth_id.size;
    error_code = memcpy_s(out_auth_id->auth_id, HC_AUTH_ID_BUFF_LEN,
                          key_param.key_auth_id.data, key_param.key_auth_id.size);
#endif
    if (error_code != EOK) {
        LOGE("Copy key param failed");
        goto get_key_info_free;
    }

get_key_info_free:
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    if (key_param.key_param_ext.key_auth_id.data != NULL) {
        safe_free(key_param.key_param_ext.key_auth_id.data);
        key_param.key_param_ext.key_auth_id.data = NULL;
    }
#else
    if (key_param.key_auth_id.data != NULL) {
        safe_free(key_param.key_auth_id.data);
        key_param.key_auth_id.data = NULL;
    }
#endif
    return error_code;
}

int32_t get_lt_key_info(struct hc_key_alias *alias, struct huks_key_type *out_key_type, struct hc_auth_id *out_auth_id)
{
    check_ptr_return_val(alias, HC_INPUT_ERROR);
    check_ptr_return_val(out_key_type, HC_INPUT_ERROR);
    check_ptr_return_val(out_auth_id, HC_INPUT_ERROR);

    struct hks_blob huks_alias = convert_to_blob_from_hc_key_alias(alias);
    huks_alias.type = HKS_BLOB_TYPE_ALIAS;
    return inner_get_lt_info(huks_alias, out_key_type, out_auth_id);
}

int32_t check_key_alias_is_owner(struct hc_key_alias *key_alias)
{
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    check_num_return_val(key_alias->length, HC_INPUT_ERROR);

    int32_t error_code = check_lt_public_key_exist(key_alias);
    if (error_code != ERROR_CODE_SUCCESS) {
        LOGE("Key is not exist");
        return error_code;
    }
    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);
    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS;
    struct huks_key_type key_type;
    struct hc_auth_id auth_id;

    error_code = inner_get_lt_info(hks_key_alias, &key_type, &auth_id);
    if (error_code != ERROR_CODE_SUCCESS) {
        LOGE("Get key info failed");
        return error_code;
    }

    if (key_type.user_type != (uint8_t)HC_USER_TYPE_CONTROLLER) {
        return ERROR_CODE_FAILED;
    }
    if (key_type.pair_type == (uint8_t)HC_PAIR_TYPE_BIND) {
        return ERROR_CODE_SUCCESS;
    } else {
        return ERROR_CODE_FAILED;
    }
}

static uint32_t load_lt_public_key_list(const struct hc_auth_id *owner_id, int32_t trust_user_type,
    struct hks_blob *key_alias_list, uint32_t list_count, struct hc_auth_id *out_auth_list)
{
    uint8_t pair_type = owner_id == NULL ? (uint8_t)HC_PAIR_TYPE_BIND : (uint8_t)HC_PAIR_TYPE_AUTH;
    uint8_t user_type = (uint8_t)trust_user_type;
    int32_t err_code;
    struct huks_key_type key_type;
    struct hc_auth_id auth_id;
    uint32_t effect_count = 0;

    if ((trust_user_type < 0) || (trust_user_type >= HC_MAX_KEY_TYPE_NUM)) {
        return effect_count;
    }
    for (uint32_t i = 0; i < list_count; i++) {
        err_code = inner_get_lt_info(key_alias_list[i], &key_type, &auth_id);
        if (err_code != ERROR_CODE_SUCCESS) {
            continue;
        }
        if (key_type.user_type != user_type) {
            continue;
        }
        if (user_type == (uint8_t)HC_USER_TYPE_CONTROLLER) {
            if (key_type.pair_type != pair_type) {
                continue;
            }
        }
        if (memcpy_s(out_auth_list[effect_count].auth_id, HC_AUTH_ID_BUFF_LEN,
                     auth_id.auth_id, auth_id.length) != EOK) {
            LOGE("Copy from temp hc_auth_id to out_auth_list failed");
            continue;
        }
        out_auth_list[effect_count].length = auth_id.length;
        effect_count++;
    }
    return effect_count;
}

int32_t get_lt_public_key_list(const struct hc_auth_id *owner_auth_id, int32_t trust_user_type,
    struct hc_auth_id *out_auth_list, uint32_t *out_count)
{
    check_ptr_return_val(out_auth_list, HC_INPUT_ERROR);
    check_ptr_return_val(out_count, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_SUCCESS;
    struct hks_blob key_alias_list[HC_PUB_KEY_ALIAS_MAX_NUM];
    int32_t status = init_key_alias_list(key_alias_list, HC_PUB_KEY_ALIAS_MAX_NUM);
    if (status != 0) {
        LOGE("Init key alias list failed, status=%d", status);
        error_code = ERROR_CODE_FAILED;
        goto exit;
    }
    uint32_t list_count = HC_PUB_KEY_ALIAS_MAX_NUM;
    status = hks_get_pub_key_alias_list(key_alias_list, &list_count);
    if (status != 0) {
        LOGE("Huks get pub key alias list failed, status=%d", status);
        error_code = ERROR_CODE_FAILED;
        goto exit;
    }
    /* filter with trust_user_type */
    uint32_t effect_count = load_lt_public_key_list(owner_auth_id, trust_user_type, key_alias_list,
                                                    list_count, out_auth_list);
    /* output param */
    *out_count = effect_count;

exit:
    for (int32_t i = 0; i < HC_PUB_KEY_ALIAS_MAX_NUM; ++i) {
        safe_free(key_alias_list[i].data);
    }
    return error_code;
}

void gen_sign_key_param(struct hks_key_param *key_param)
{
    key_param->key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    key_param->key_usage = HKS_KEY_USAGE_SIGN; /* huks have cheaked this param */
    key_param->key_mode = HKS_ALG_GCM;

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    key_param->key_pad = HKS_PADDING_NONE;
    key_param->key_domain = HKS_ECC_CURVE_ED25519;
    key_param->key_len = HC_PARAM_KEY_LEN; /* interface regulations */
    key_param->key_digest = HKS_ALG_HASH_SHA_256;

    build_keyparam_ext(key_param);
#endif
}

int32_t sign(struct hc_key_alias *key_alias, const struct uint8_buff *message, struct signature *out_signature)
{
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    check_ptr_return_val(message, HC_INPUT_ERROR);
    check_ptr_return_val(out_signature, HC_INPUT_ERROR);
    check_num_return_val(key_alias->length, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_FAILED;
    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);
    if (hks_key_alias.size == 0) {
        LOGE("Convert hks key alias to blob failed");
        return error_code;
    }
    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS;

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    struct hks_blob hash;
    hash.data = message->val;
    hash.size = message->length;
    if (hash.size == 0) {
        LOGE("Message to blob failed");
        return error_code;
    }
#else
    struct sha256_value sha256_value = sha256(message);
    if (sha256_value.length == 0) {
        LOGE("Get sha256 hash failed");
        return error_code;
    }
    struct hks_blob hash = convert_to_blob_from_sha256_value(&sha256_value);
    if (hash.size == 0) {
        LOGE("Convert sha256 hash to blob failed");
        return error_code;
    }
#endif

    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    gen_sign_key_param(&key_param);

    struct hks_blob signature;
    (void)memset_s(&signature, sizeof(signature), 0, sizeof(signature));
    signature.data = out_signature->signature;
    signature.size = HC_SIGNATURE_LEN;
    int32_t hks_status = hks_asymmetric_sign(&hks_key_alias, &key_param, &hash, &signature);
    if ((hks_status == 0) && (signature.size == HC_SIGNATURE_LEN)) {
        out_signature->length = HC_SIGNATURE_LEN;
        error_code = ERROR_CODE_SUCCESS;
    } else {
        LOGE("Sign failed, status=%d", hks_status);
        error_code = ERROR_CODE_FAILED;
    }
    return error_code;
}

void gen_verify_key_param(const int32_t user_type, struct hks_key_param *key_param)
{
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    key_param->key_pad = HKS_PADDING_NONE;
    key_param->key_domain = HKS_ECC_CURVE_ED25519;
    key_param->key_len = HC_PARAM_KEY_LEN; /* interface regulations */
    key_param->key_digest = HKS_ALG_HASH_SHA_256;
    key_param->key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    key_param->key_param_ext.key_role = (uint32_t)user_type;
    build_keyparam_ext(key_param);
#else
    key_param->key_role = (uint32_t)user_type;
    key_param->key_type = HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519; /* HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519 */
#endif
    key_param->key_usage = HKS_KEY_USAGE_VERIFY;
    key_param->key_mode = HKS_ALG_GCM;
}

int32_t verify(struct hc_key_alias *key_alias, const int32_t user_type,
    const struct uint8_buff *message, struct signature *signature)
{
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    check_ptr_return_val(message, HC_INPUT_ERROR);
    check_ptr_return_val(signature, HC_INPUT_ERROR);
    check_num_return_val(key_alias->length, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_FAILED;
    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);
    if (hks_key_alias.size == 0) {
        LOGE("Convert hks key alias to blob failed");
        return error_code;
    }
    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS; /* alias pattern */

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    struct hks_blob hash;
    hash.data = message->val;
    hash.size = message->length;
    if (hash.size == 0) {
        LOGE("Message to blob failed");
        return error_code;
    }
#else
    struct sha256_value sha256_value = sha256(message);
    if (sha256_value.length == 0) {
        LOGE("Get sha256 hash failed. message val:%s, message length: %d", message->val, message->length);
        return error_code;
    }

    struct hks_blob hash = convert_to_blob_from_sha256_value(&sha256_value);
    if (hash.size == 0) {
        LOGE("Convert sha256 hash to blob failed");
        return error_code;
    }
#endif

    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    gen_verify_key_param(user_type, &key_param);

    struct hks_blob hks_signature = convert_to_blob_from_signature(signature);
    if (hks_signature.size == 0) {
        LOGE("Convert hks signature to blob failed");
        return error_code;
    }

    int32_t hks_status = hks_asymmetric_verify(&hks_key_alias, &key_param, &hash, &hks_signature);
    if (hks_status == 0) {
        error_code = ERROR_CODE_SUCCESS;
    } else {
        LOGE("Verify failed. status=%d", hks_status);
    }
    return error_code;
}

static void gen_verify_with_public_key_param(struct hks_key_param *key_param, const int32_t user_type)
{
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    key_param->key_pad = HKS_PADDING_NONE;
    key_param->key_domain = HKS_ECC_CURVE_ED25519;
    key_param->key_len = HC_PARAM_KEY_LEN; /* interface regulations */
    key_param->key_digest = HKS_ALG_HASH_SHA_256;
    key_param->key_param_ext.key_role = (uint32_t)user_type;
    build_keyparam_ext(key_param);
#else
    key_param->key_role = (uint32_t)user_type;
    key_param->key_len = HC_ST_PUBLIC_KEY_LEN;
#endif
    key_param->key_type = HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519;
    key_param->key_usage = HKS_KEY_USAGE_VERIFY;
    key_param->key_mode = HKS_ALG_GCM;
}

int32_t verify_with_public_key(const int32_t user_type, const struct uint8_buff *message,
    struct var_buffer *public_key, struct signature *signature)
{
    check_ptr_return_val(message, HC_INPUT_ERROR);
    check_ptr_return_val(public_key, HC_INPUT_ERROR);
    check_ptr_return_val(signature, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_FAILED;
    struct sha256_value sha256_value = sha256(message);
    if (sha256_value.length == 0) {
        LOGE("Get sha256 hash failed");
        return error_code;
    }

    struct hks_blob hash = convert_to_blob_from_sha256_value(&sha256_value);
    if (hash.size == 0) {
        LOGE("Convert sha256 hash to blob failed");
        return error_code;
    }

    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    gen_verify_with_public_key_param(&key_param, user_type);
    struct hks_blob hks_signature = convert_to_blob_from_signature(signature);
    if (hks_signature.size == 0) {
        LOGE("Convert hks signature to blob failed");
        return error_code;
    }

    struct hks_blob hks_public_key;
    (void)memset_s(&hks_public_key, sizeof(hks_public_key), 0, sizeof(hks_public_key));
    hks_public_key.data = public_key->data;
    hks_public_key.size = public_key->length;
    hks_public_key.type = HKS_BLOB_TYPE_KEY; /* public key pattern */
    int32_t hks_status = hks_asymmetric_verify(&hks_public_key, &key_param, &hash, &hks_signature);
    if (hks_status == 0) {
        error_code = ERROR_CODE_SUCCESS;
    } else {
        LOGE("Verify failed, status=%d", hks_status);
        error_code = ERROR_CODE_FAILED;
    }
    return error_code;
}

int32_t compute_sts_shared_secret(struct stsk *self_private_key, struct stpk *peer_public_key,
    struct sts_shared_secret *out_shared_key)
{
    check_ptr_return_val(self_private_key, HC_INPUT_ERROR);
    check_num_return_val(self_private_key->length, HC_INPUT_ERROR);
    check_ptr_return_val(peer_public_key, HC_INPUT_ERROR);
    check_num_return_val(peer_public_key->length, HC_INPUT_ERROR);
    check_ptr_return_val(out_shared_key, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_FAILED;
    (void)memset_s(out_shared_key, sizeof(*out_shared_key), 0, sizeof(*out_shared_key));
    struct hks_blob key_alias_for_private_key = convert_to_blob_from_stsk(self_private_key);
    if (key_alias_for_private_key.size == 0) {
        LOGE("Convert key alias for private key to blob failed");
        return error_code;
    }

    struct hks_blob key_alias_for_peer_public_key = convert_to_blob_from_stpk(peer_public_key);
    if (key_alias_for_peer_public_key.size == 0) {
        LOGE("Convert key alias for peer public key to blob failed");
        return error_code;
    }

    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    key_param.key_type = HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519;
    key_param.key_usage = HKS_KEY_USAGE_DERIVE;
    key_param.key_len = HC_ST_PUBLIC_KEY_LEN;
    key_param.key_mode = HKS_ALG_ECDH(HKS_ALG_SELECT_RAW);

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    build_keyparam_ext(&key_param);
#endif

    struct hks_blob key_alias_for_agreed_key = {
        .data = out_shared_key->sts_shared_secret,
        .size = HC_STS_SHARED_SECRET_LENGTH,
        .type = 0
    };
    uint32_t agreement_alg = HKS_ALG_ECDH(HKS_ALG_SELECT_RAW);
    int32_t hks_status = hks_key_agreement(&key_alias_for_agreed_key, &key_param, agreement_alg,
        &key_alias_for_private_key, &key_alias_for_peer_public_key);
    if ((hks_status == 0) && (key_alias_for_agreed_key.size == HC_STS_SHARED_SECRET_LENGTH)) {
        out_shared_key->length = key_alias_for_agreed_key.size;
        error_code = ERROR_CODE_SUCCESS;
    } else {
        LOGE("Key agreement by alias failed");
    }
    return error_code;
}

int32_t key_info_init(void)
{
    int32_t hks_status = hks_init();
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    return hks_status;
#else
    if (hks_status == 0) {
        return ERROR_CODE_SUCCESS;
    } else if ((hks_status == HKS_ERROR_INVALID_KEY_FILE) || (hks_status == HKS_ERROR_READ_FILE_FAIL)) {
        LOGE("Key info init failed, status=%d", hks_status);
        hks_status = hks_refresh_key_info();
        if (hks_status == 0) {
            return ERROR_CODE_SUCCESS;
        }
        LOGE("Key info refresh failed, status=%u", hks_status);
        return ERROR_CODE_FAILED;
    }

    return ERROR_CODE_FAILED;
#endif
}

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
static void init_aes_ccm_decrypt_key_params(struct hks_key_param *key_params)
{
    (void)memset_s(key_params, sizeof(*key_params), 0, sizeof(*key_params));
    key_params->key_type = HKS_KEY_TYPE_AES;
    key_params->key_usage = HKS_KEY_USAGE_DECRYPT;
    key_params->key_mode = HKS_ALG_CCM;
    key_params->key_pad = HKS_PADDING_PKCS7;
    key_params->key_len = HKS_MAX_KEY_LEN_256;
    key_params->key_digest = HKS_ALG_HASH_SHA_256;

    build_keyparam_ext(key_params);
}

static int32_t gen_crypt_param(const struct uint8_buff *cipher, struct hks_crypt_param *crypt_param,
    struct aes_aad *aad)
{
    uint8_t iv[HC_IV_MAX_LEN];
    (void)memset_s(iv, sizeof(iv), 0, sizeof(iv));
    if (cipher->length < sizeof(iv)) {
        LOGE("Cipher length is short than iv max length");
        return ERROR_CODE_FAILED;
    }
    (void)memcpy_s(iv, HC_IV_MAX_LEN, cipher->val, sizeof(iv));
    crypt_param->nonce.data = iv;
    crypt_param->nonce.size = sizeof(iv);
    crypt_param->nonce.type = HKS_BLOB_TYPE_IV;
    crypt_param->aad.data = aad->aad;
    crypt_param->aad.size = aad->length;
    crypt_param->aad.type = HKS_BLOB_TYPE_AAD;
    crypt_param->tag.data = NULL;
    crypt_param->tag.size = 0;
    crypt_param->tag.type = HKS_BLOB_TYPE_AAD;

    return EOK;
}

int32_t aes_ccm_decrypt(struct var_buffer *key, const struct uint8_buff *cipher,
    struct aes_aad *aad, struct uint8_buff *out_plain)
{
    check_ptr_return_val(key, HC_INPUT_ERROR);
    check_ptr_return_val(cipher, HC_INPUT_ERROR);
    check_ptr_return_val(aad, HC_INPUT_ERROR);
    check_ptr_return_val(out_plain, HC_INPUT_ERROR);

    struct hks_blob hks_key = {
        .type = HKS_BLOB_TYPE_ALIAS,
        .data = key->data,
        .size = key->length
    };
    struct hks_key_param key_params;
    init_aes_ccm_decrypt_key_params(&key_params);

    struct hks_crypt_param crypt_param;
    if (gen_crypt_param(cipher, &crypt_param, aad) != EOK) {
        return ERROR_CODE_FAILED;
    }

    struct hks_blob cipher_text_with_tag;
    (void)memset_s(&cipher_text_with_tag, sizeof(cipher_text_with_tag), 0, sizeof(cipher_text_with_tag));
    cipher_text_with_tag.data = cipher->val;
    cipher_text_with_tag.size = cipher->length;

    struct hks_blob plain_text;
    (void)memset_s(&plain_text, sizeof(plain_text), 0, sizeof(plain_text));
    plain_text.data = (uint8_t *)MALLOC(cipher_text_with_tag.size - HKS_SALT_MAX_SIZE);
    check_ptr_return_val(plain_text.data, ERROR_CODE_FAILED);
    plain_text.size = cipher_text_with_tag.size - HKS_SALT_MAX_SIZE;
    int32_t status = hks_aead_decrypt(&hks_key, &key_params, &crypt_param, &plain_text, &cipher_text_with_tag);
    if (status != 0) {
        LOGE("Huks aead decrypt failed, status: %d", status);
        safe_free(plain_text.data);
        return ERROR_CODE_FAILED;
    }

    if (memcpy_s(out_plain->val, out_plain->size, plain_text.data, plain_text.size) != EOK) {
        safe_free(plain_text.data);
        return memory_copy_error(__func__, __LINE__);
    }
    out_plain->length = plain_text.size;
    safe_free(plain_text.data);

    return status;
}

int32_t generate_lt_X25519_key_pair(struct hc_key_alias *key_alias, const struct hc_auth_id *auth_id)
{
    check_ptr_return_val(key_alias, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);

    int32_t error_code = ERROR_CODE_FAILED;
    struct hks_blob hks_key_alias = convert_to_blob_from_hc_key_alias(key_alias);

    check_num_return_val(hks_key_alias.size, error_code);
    hks_key_alias.type = HKS_BLOB_TYPE_ALIAS;

    struct hks_key_param key_param;
    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));
    key_param.key_type = HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519;
    key_param.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    key_param.key_len = HC_PARAM_KEY_LEN; /* interface regulations */
    key_param.key_domain = HKS_ECC_CURVE_CURVE25519;
    key_param.key_pad = HKS_PADDING_NONE;
    key_param.key_digest = HKS_ALG_HASH_SHA_256;

    struct hc_auth_id tmp_id = *auth_id;
    key_param.key_param_ext.key_auth_id = convert_to_blob_from_hc_auth_id(&tmp_id);
    key_param.key_param_ext.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    build_keyparam_ext(&key_param);

    int32_t hks_status = hks_generate_key(&hks_key_alias, &key_param);
    if (hks_status == 0) {
        error_code = ERROR_CODE_SUCCESS;
    } else {
        LOGE("Hks generate failed, status=%d", hks_status);
    }
    if (hks_is_key_exist(&hks_key_alias) == 0) {
        LOGI("Generate key success, key exist");
    }

    return error_code;
}

int32_t get_key_attestation(const struct uint8_buff *challenge, struct hc_key_alias *sk_alias,
    struct uint8_buff *out_cert_chain)
{
    int32_t error_code = HC_INPUT_ERROR;

    check_ptr_return_val(challenge, error_code);
    check_ptr_return_val(sk_alias, error_code);
    check_ptr_return_val(out_cert_chain, error_code);

    struct hks_blob hks_key_alias = {
        .data = sk_alias->key_alias,
        .size = sk_alias->length,
        .type = HKS_BLOB_TYPE_ALIAS
    };

    struct hks_attestation_spec hks_attestation;
    hks_attestation.challenge.data = challenge->val,
    hks_attestation.challenge.size = challenge->length,
    hks_attestation.challenge.type = HKS_BLOB_TYPE_RAW,
    hks_attestation.temporary = 0; /* 0: save attestation result, 1: temporary attestation */

    struct hks_blob cert[g_cert_chain_cnt];
    for (int32_t i = 0; i < g_cert_chain_cnt; ++i) {
        struct hks_blob certBlob;
        certBlob.data = out_cert_chain[i].val;
        certBlob.size = out_cert_chain[i].length;
        certBlob.type = HKS_BLOB_TYPE_RAW;
        cert[i] = certBlob;
    }

    struct hks_cert_chain hks_cert_chains = {
        .count = g_cert_chain_cnt,
        .cert = cert
    };

    struct hks_key_param key_param = {0};
    key_param.key_type = HKS_KEY_TYPE_ECC_KEYPAIR(HKS_ECC_CURVE_CURVE25519);
    key_param.key_len = HC_PARAM_CHAIN_LEN; /* interface regulations */
    key_param.key_domain = HKS_ECC_CURVE_CURVE25519;
    key_param.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    key_param.key_pad = HKS_PADDING_NONE;
    build_keyparam_ext(&key_param);

    int32_t ret = hks_key_attestation(&hks_key_alias, &key_param, &hks_attestation, &hks_cert_chains);
    if (ret != ERROR_CODE_SUCCESS) {
        LOGE("Key attestaion failed, errCode is %d", ret);
    }
    LOGI("hks_key_attestation finish");
    for (int32_t i = 0; i < g_cert_chain_cnt; ++i) {
        out_cert_chain[i].length = hks_cert_chains.cert[i].size;
    }

    return ret;
}

static void gen_key_alias_and_param(struct hks_blob *hks_key_alias, struct hks_key_param *key_param,
    struct hc_key_alias *sk_alias)
{
    hks_key_alias->data = sk_alias->key_alias,
    hks_key_alias->size = sk_alias->length,
    hks_key_alias->type = HKS_BLOB_TYPE_ALIAS;
    key_param->key_type = HKS_KEY_TYPE_ECC_KEYPAIR(HKS_ECC_CURVE_CURVE25519);
    key_param->key_len = HC_PARAM_CHAIN_LEN; /* interface regulations */
    key_param->key_domain = HKS_ECC_CURVE_CURVE25519;
    key_param->key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    key_param->key_pad = HKS_PADDING_NONE;
    build_keyparam_ext(key_param);
}

int32_t get_cert_chain(const struct uint8_buff *challenge,
    struct hc_key_alias *sk_alias, struct uint8_buff *out_cert_chain)
{
    int32_t error_code = HC_INPUT_ERROR;

    check_ptr_return_val(challenge, error_code);
    check_ptr_return_val(sk_alias, error_code);
    check_ptr_return_val(out_cert_chain, error_code);

    struct hks_blob hks_key_alias = {0};
    struct hks_key_param key_param = {0};
    gen_key_alias_and_param(&hks_key_alias, &key_param, sk_alias);

    int8_t malloc_flag = 1; /* malloc ok */
    struct hks_blob cert[g_cert_chain_cnt];
    (void)memset_s(cert, sizeof(cert), 0, sizeof(cert));
    const uint32_t cert_buff_size = 8192; /* each certificate buff max size */
    for (int32_t i = 0; i < g_cert_chain_cnt; ++i) {
        struct hks_blob certBlob;
        certBlob.data = (uint8_t *)MALLOC(cert_buff_size);
        if (certBlob.data == NULL) {
            malloc_flag = 0;
            break;
        }
        (void)memset_s(certBlob.data, cert_buff_size, 0, cert_buff_size);
        certBlob.size = cert_buff_size;
        certBlob.type = HKS_BLOB_TYPE_RAW;
        cert[i] = certBlob;
    }

    if (malloc_flag == 0) {
        for (int32_t i = 0; i < g_cert_chain_cnt; ++i) {
            if (cert[i].size != 0) {
                FREE(cert[i].data);
            }
        }
        return HC_MALLOC_FAILED;
    }

    struct hks_cert_chain hks_cert_chains = {
        .count = g_cert_chain_cnt,
        .cert = cert
    };

    int32_t ret = hks_get_cert_chain(&hks_key_alias, &key_param, &hks_cert_chains);
    if (ret != ERROR_CODE_SUCCESS) {
        LOGE("Get cert chain failed, errCode is %d", ret);
    }

    out_cert_chain->length = hks_cert_chains.cert[0].size;
    (void)memset_s(out_cert_chain->val, out_cert_chain->length, 0, out_cert_chain->length);
    if (memcpy_s(out_cert_chain->val, out_cert_chain->length, hks_cert_chains.cert[0].data,
        hks_cert_chains.cert[0].size) != EOK) {
        LOGE("Copy cert chain failed!");
    }

    for (int32_t i = 0; i < g_cert_chain_cnt; ++i) {
        FREE(hks_cert_chains.cert[i].data);
    }

    return ret;
}

int32_t asset_unwrap(struct uint8_buff *sec_data, struct hc_key_alias *dec_alias,
    struct hc_key_alias *target_alias)
{
    int32_t error_code = HC_INPUT_ERROR;

    check_ptr_return_val(sec_data, error_code);
    check_ptr_return_val(dec_alias, error_code);
    check_ptr_return_val(target_alias, error_code);

    struct hks_blob hks_dec_alias = {
        .data = dec_alias->key_alias,
        .size = dec_alias->length,
        .type = HKS_BLOB_TYPE_ALIAS
    };

    struct hks_blob hks_target_alias = {
        .data = target_alias->key_alias,
        .size = target_alias->length,
        .type = HKS_BLOB_TYPE_ALIAS
    };

    struct hks_key_param hks_param = {0};

    hks_param.key_type = HKS_KEY_TYPE_AES;
    hks_param.key_len = HC_PARAM_KEY_LEN; /* interface regulations */
    hks_param.key_usage = HKS_KEY_USAGE_UNWRAP;
    hks_param.key_mode = HKS_ALG_CCM;
    hks_param.key_pad = HKS_PADDING_PKCS7;
    build_keyparam_ext(&hks_param);

    struct hks_blob hks_sec_data = {
        .data = sec_data->val,
        .size = sec_data->size,
        .type = HKS_BLOB_TYPE_RAW
    };

    uint8_t result_buff[64] = {0}; /* interface regulations */
    struct hks_blob hks_result = {
        .data = result_buff,
        .size = 64, /* interface regulations */
        .type = HKS_BLOB_TYPE_WRAP_ECDH_ENC_DATA
    };

    int32_t ret = hks_unwrap(&hks_dec_alias, &hks_target_alias, &hks_param, &hks_sec_data, &hks_result);
    if (ret != ERROR_CODE_SUCCESS) {
        LOGE("Hks unwrap failed, errCode is %d", ret);
    }

    return ret;
}

static void gen_hks_param(struct hks_key_param *hks_param, struct hc_auth_id *temp_auth_id)
{
    hks_param->key_param_ext.key_auth_id = convert_to_blob_from_hc_auth_id(temp_auth_id);
    hks_param->key_param_ext.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    hks_param->key_type = HKS_KEY_TYPE_AES;
    hks_param->key_len = HKS_MAX_KEY_LEN_256;
    hks_param->key_mode = HKS_ALG_CCM;
    hks_param->key_pad = HKS_PADDING_PKCS7;
    hks_param->key_digest = HKS_ALG_HASH_SHA_256;
    hks_param->key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT | HKS_KEY_USAGE_WRAP | HKS_KEY_USAGE_UNWRAP;
    build_keyparam_ext(hks_param);
}

int32_t gen_derived_key(struct hc_key_alias *base_alias, struct hc_key_alias *to_save_alias)
{
    check_ptr_return_val(base_alias, HC_INPUT_ERROR);
    check_num_return_val(to_save_alias, HC_INPUT_ERROR);
    if (check_lt_public_key_exist(base_alias) != HC_OK) {
        LOGE("Base key is not exist");
        return HC_INPUT_ERROR;
    }

    if (check_lt_public_key_exist(to_save_alias) == HC_OK) {
        LOGW("Derive key exists, will be genetate again");
    }

    struct hks_blob hks_base_alias = {
        .data = base_alias->key_alias,
        .size = base_alias->length,
        .type = HKS_BLOB_TYPE_ALIAS
    };

    struct hks_blob hks_target_alias = {
        .data = to_save_alias->key_alias,
        .size = to_save_alias->length,
        .type = HKS_BLOB_TYPE_ALIAS
    };

    struct hc_auth_id temp_auth_id = {
        .length = HC_AUTH_ID_BUFF_LEN,
        .auth_id = {0}
    };

    struct hks_key_param hks_param = {0};
    gen_hks_param(&hks_param, &temp_auth_id);
    struct hks_derive_param hks_derive_param = {0};
    int32_t factor_size = strlen((char *)g_factor);

    hks_derive_param.derive_factor.size = factor_size;
    hks_derive_param.derive_factor.data = (uint8_t *)MALLOC(factor_size + 1);
    if (hks_derive_param.derive_factor.data == NULL) {
        return HC_MALLOC_FAILED;
    }

    (void)memcpy_s(hks_derive_param.derive_factor.data, factor_size, g_factor, factor_size);
    hks_derive_param.derive_factor.data[factor_size] = '\0';
    hks_derive_param.derive_factor.type = 0;
    hks_derive_param.master_key = hks_base_alias;
    hks_derive_param.key_gen_type = HKS_KEY_GEN_TYPE_DERIVE;
    int32_t ret = hks_generate_symmetric_key(&hks_target_alias, &hks_param, &hks_derive_param);
    if (ret != ERROR_CODE_SUCCESS) {
        LOGE("Derive key failed, errCode is %d", ret);
    }
    safe_free(hks_derive_param.derive_factor.data);
    return ret;
}

#endif
