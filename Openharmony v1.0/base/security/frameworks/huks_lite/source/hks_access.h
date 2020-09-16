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

#ifndef HKS_ACCESS_H
#define HKS_ACCESS_H

#include "hks_types.h"

enum hks_cmd_type {
    HKS_GENERATE_KEY = 0,
    HKS_GENERATE_KEY_EX,
    HKS_SIGN,
    HKS_VERIFY,
    HKS_ENCRYPT,
    HKS_DECRYPT,
    HKS_IMPORT_KEY,
    HKS_EXPORT_KEY,
    HKS_GENERATE_RANDOM,
    HKS_KEY_AGREEMENT,
    HKS_KEY_DERIVATION,
    HKS_HMAC,
    HKS_HASH,
    HKS_BN_EXP_MOD,
    HKS_NMI_GENERATE_SYMMETRIC_KEY,
    HKS_SYMMETRIC_ENCRYPT_DECRYPT,

    HKS_CMD_MAX, /* new cmd type must be added before HKS_CMD_MAX */
};

struct hks_generate_key_msg {
    const struct hks_blob *key_alias;
    const struct hks_key_param *key_param;
    struct hks_encrypt_material *key_material;
};

struct hks_generate_ex_msg {
    const struct hks_key_param *key_param;
    struct hks_blob *priv_key;
    struct hks_blob *pub_key;
};

struct hks_sign_verify_msg {
    const struct hks_blob *key;
    const struct hks_key_param *key_param;
    const struct hks_blob *message;
    struct hks_blob *signature;
    struct hks_encrypt_material *encrypt_material;
};

struct hks_encrypt_decrypt_msg {
    const struct hks_blob *key;
    const struct hks_key_param *key_param;
    const struct hks_crypt_param *crypt_param;
    struct hks_blob *plain_text;
    struct hks_blob *cipher_text_with_tag;
};

struct hks_import_key_msg {
    const struct hks_blob *key_alias;
    const struct hks_key_param *key_param;
    const struct hks_blob *key_data;
    struct hks_encrypt_material *key_material;
};

struct hks_export_key_msg {
    const struct hks_blob *key_alias;
    struct hks_blob *key_data;
    struct hks_encrypt_material *encrypt_material;
};

struct hks_delete_key_msg {
    const struct hks_blob *key_alias;
};

struct hks_get_key_param_msg {
    const struct hks_blob *key_alias;
    struct hks_key_param *key_param;
};

struct hks_key_exist_msg {
    const struct hks_blob *key_alias;
};

struct hks_generate_random_msg {
    struct hks_blob *random;
};

struct hks_key_agreement_msg {
    struct hks_blob *agreed_key;
    const struct hks_key_param *key_param;
    uint32_t agreement_alg;
    const struct hks_blob *priv_key;
    const struct hks_blob *pub_key;
};

struct hks_key_derivation_msg {
    struct hks_blob *derived_key;
    const struct hks_key_param *key_param;
    const struct hks_blob *kdf_key;
    const struct hks_blob *salt;
    const struct hks_blob *label;
};

struct hks_hmac_msg {
    const struct hks_blob *key;
    uint32_t alg;
    const struct hks_blob *src_data;
    struct hks_blob *output;
};

struct hks_hash_msg {
    uint32_t alg;
    const struct hks_blob *src_data;
    struct hks_blob *hash;
};

struct hks_bn_exp_mod_msg {
    struct hks_blob *x;
    const struct hks_blob *a;
    const struct hks_blob *e;
    const struct hks_blob *n;
};

struct hks_get_pub_key_list_msg {
    uint32_t *list_count;
    struct hks_blob *key_alias_list;
};

struct hks_generate_symmetric_key_msg {
    struct hks_blob *output_key;
    struct hks_encrypt_material *key_material;
};

struct hks_encrypt_decrypt_text {
    const struct hks_blob *input_text;
    struct hks_blob *output_text;
};

struct hks_symmetric_encrypt_decrypt_msg {
    const struct hks_crypt_param *crypt_param;
    const struct hks_blob *input_text;
    struct hks_blob *output_text;
    struct hks_encrypt_material *key_material;
    uint32_t operation_mode;
};

struct sec_mod_msg {
    enum hks_cmd_type cmd_id;
    int32_t status;
    union {
        struct hks_generate_key_msg generate_key_msg;
        struct hks_generate_ex_msg generate_ex_msg;
        struct hks_encrypt_decrypt_msg encrypt_decrypt_msg;
        struct hks_sign_verify_msg sign_verify_msg;
        struct hks_import_key_msg import_key_msg;
        struct hks_export_key_msg export_key_msg;
        struct hks_delete_key_msg delete_key_msg;
        struct hks_get_key_param_msg get_key_param_msg;
        struct hks_key_exist_msg key_exist_msg;
        struct hks_generate_random_msg generate_random_msg;
        struct hks_key_agreement_msg key_agreement_msg;
        struct hks_key_derivation_msg key_derivation_msg;
        struct hks_hmac_msg hmac_msg;
        struct hks_hash_msg hash_msg;
        struct hks_bn_exp_mod_msg bn_exp_mod_msg;
        struct hks_get_pub_key_list_msg get_pub_key_list_msg;
        struct hks_generate_symmetric_key_msg generate_symmetric_key_msg;
        struct hks_symmetric_encrypt_decrypt_msg symmetric_encrypt_decrypt_msg;
    } msg_data;
};

typedef void (*hks_handle_func_p)(struct sec_mod_msg *msg_box);
void hks_enter_secure_mode(struct sec_mod_msg *msg);
void hks_handle_secure_call(void);

int32_t hks_access_init(void);
void hks_access_destroy(void);
int32_t hks_access_refresh_key_info(void);
int32_t hks_access_generate_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param);
int32_t hks_access_generate_key_ex(
    const struct hks_key_param *key_param, struct hks_blob *priv_key, struct hks_blob *pub_key);
int32_t hks_access_sign(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *hash, struct hks_blob *signature);
int32_t hks_access_verify(const struct hks_blob *key_alias,
    const struct hks_blob *hash, const struct hks_blob *signature);
int32_t hks_access_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text, struct hks_blob *cipher_text_with_tag);
int32_t hks_access_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    const struct hks_blob *cipher_text_with_tag, struct hks_blob *plain_text);
int32_t hks_access_import_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *key);
int32_t hks_access_export_key(const struct hks_blob *key_alias, struct hks_blob *key);
int32_t hks_access_delete_key(const struct hks_blob *key_alias);
int32_t hks_access_is_key_exist(const struct hks_blob *key_alias);
int32_t hks_access_get_key_param(const struct hks_blob *key_alias,
    struct hks_key_param *key_param);
int32_t hks_access_get_random(struct hks_blob *random);
int32_t hks_access_hmac(const struct hks_blob *key,
    uint32_t alg, const struct hks_blob *src_data, struct hks_blob *output);
int32_t hks_access_hash(uint32_t alg, const struct hks_blob *src_data, struct hks_blob *hash);
int32_t hks_access_key_agreement(struct hks_blob *agreed_key,
    const struct hks_key_param *private_key_param, const struct hks_blob *private_key,
    const struct hks_blob *peer_public_key, const uint32_t agreement_alg);
int32_t hks_access_key_derivation(struct hks_blob *derived_key,
    const struct hks_blob *kdf_key, const struct hks_blob *salt,
    const struct hks_blob *label, const struct hks_key_param *key_params);
int32_t hks_access_bn_exp_mod(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e, const struct hks_blob *n);
int32_t hks_access_get_pub_key_alias_list(
    struct hks_blob *key_alias_list, uint32_t *list_count);

#ifdef _SECURE_ENVIREMENT_NMI_
int32_t hks_access_generate_symmetric_key(struct hks_blob *output_key,
    const struct hks_key_param *key_param);

int32_t hks_access_symmetric_encrypt_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    struct hks_encrypt_decrypt_text *hks_cipher_text, uint32_t operation_mode);
#endif

#endif /* HKS_ACCESS_H */
