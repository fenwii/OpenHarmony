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

#ifndef __HUKS_ADAPTER_H__
#define __HUKS_ADAPTER_H__

#include "base.h"
#include "hichain.h"

#define safe_free(T) \
    do { \
        if ((T) != NULL) { \
            FREE(T); \
        } \
    } while (0)

enum huks_adapter_error_code {
    ERROR_CODE_FAILED = -1,
    ERROR_CODE_SUCCESS
};

enum huks_key_alias_type {
    KEY_ALIAS_ACCESSOR_PK = HC_USER_TYPE_ACCESSORY,
    KEY_ALIAS_CONTROLLER_PK = HC_USER_TYPE_CONTROLLER,
    KEY_ALIAS_LT_KEY_PAIR,
    KEY_ALIAS_KEK,
    KEY_ALIAS_DEK,
    KEY_ALIAS_TMP,
};

enum hc_pair_type {
    HC_PAIR_TYPE_BIND,
    HC_PAIR_TYPE_AUTH,
};

struct huks_key_type {
    uint8_t user_type;
    uint8_t pair_type;
    uint8_t reserved1;
    uint8_t reserved2;
};

#define HKS_ERROR_INVALID_KEY_FILE ((int32_t)-1015)
#define HKS_ERROR_READ_FILE_FAIL ((int32_t)-1003)

enum huks_derived_type {
    HUKS_DERIVED_TYPE_KEK = KEY_ALIAS_KEK,
    HUKS_DERIVED_TYPE_DEK = KEY_ALIAS_DEK,
};

struct service_id generate_service_id(const struct session_identity *identity);

/*
 * generate key alias by service id and auth id
 *
 * @param service_id: service id
 * @param hc_auth_id: auth id
 * @param key_type: ACCESSOR_PK:0 CONTROLLER_PK:1 LT_KEY_PAIR:2 KEK:3 DEK:4
 * @return key alias
 */
struct hc_key_alias generate_key_alias(const struct service_id *service_id,
    const struct hc_auth_id *auth_id, enum huks_key_alias_type key_type);

/*
 * Generate temporary key pair X25519
 *
 * @param keyPair: the public&private key struct
 * @param keyPairType: the key pair type, support X25519 and ED25519
 * @return 0 -- success, others -- failed
 */
int32_t generate_st_key_pair(struct st_key_pair *out_key_pair);

/*
 * Generate a long-lived key pair ED25519.
 *
 * @param key_alias: key alias
 * @return 0 -- success, others -- failed
 */
int32_t generate_lt_key_pair(struct hc_key_alias *key_alias, const struct hc_auth_id *auth_id);

/*
 * Export long-acting public key
 *
 * @param key_alias: the public key alias
 * @return 0 -- success, others -- failed
 */
int32_t export_lt_public_key(struct hc_key_alias *key_alias, struct ltpk *out_public_key);

/*
 * Delete stored public key
 *
 * @param key_alias: the public key alias
 * @return 0 -- success, others -- failed
 */
int32_t delete_lt_public_key(struct hc_key_alias *key_alias);

/*
 * Import public key
 *
 * @param key_alias: the public key alias
 * @param peer_public_key: the peer public key to be store
 * @return 0 -- success, others -- failed
 */
int32_t import_lt_public_key(struct hc_key_alias *key_alias, struct ltpk *peer_public_key,
    const int32_t user_type, const int32_t pair_type, struct hc_auth_id *auth_id);

/*
 * Check if the public key exists according to alias
 *
 * @param key_alias: the public key alias
 * @return 0 -- exist, others -- not exist
 */
int32_t check_lt_public_key_exist(struct hc_key_alias *key_alias);

/*
 * Check if the public key exists according to alias
 *
 * @param key_alias: the public key alias
 * @return 0 -- is owner, others -- not
 */
int32_t check_key_alias_is_owner(struct hc_key_alias *key_alias);

/*
 * Check if the public key exists according to alias
 *
 * @param key_alias: key alias
 * @param out_key_type: output param, with key type info
 * @param out_auth_id: output param, with auth id
 * @return 0 -- work, others -- failed
 */
int32_t get_lt_key_info(struct hc_key_alias *alias, struct huks_key_type *out_key_type, struct hc_auth_id *out_auth_id);

/*
 * Query the list of imported and stored ed25519 public keys
 *
 * @param owner_auth_id: input null, output binding list;input owner, output auth list;other ,output null
 * @param trust_user_type: the public key alias
 * @return 0 -- exist, others -- not exist
 */
int32_t get_lt_public_key_list(const struct hc_auth_id *owner_auth_id, int32_t trust_user_type,
    struct hc_auth_id *out_auth_list, uint32_t *out_count);

/*
 * compute shared secret by X25519.
 *
 * @param self_private_key: the private key
 * @param peer_public_key: the peer public key
 * @param out_shared_key: out shared key
 * @return 0 -- success, others -- failed
 */
int32_t compute_sts_shared_secret(struct stsk *self_private_key,
    struct stpk *peer_public_key, struct sts_shared_secret *out_shared_key);

/*
 * sign by ED25519.
 *
 * @param key_alias: the key alias
 * @param message: the message to sign
 * @param out_sig: sign result
 * @return 0 -- success, others -- failed
 */
int32_t sign(struct hc_key_alias *key_alias, const struct uint8_buff *message, struct signature *out_signature);

/*
 * verify by ED25519.
 *
 * @param service_id: the service ID
 * @param hc_auth_id: the auth ID
 * @param user_type:
 * @param message: the message to verify
 * @param signature: signature to compare
 * @return 0 -- success, others -- failed
 */
int32_t verify(struct hc_key_alias *key_alias, const int32_t user_type, const struct uint8_buff *message,
    struct signature *signature);

/*
 * verify by ED25519, pass public_key.
 *
 * @param service_id: the service ID
 * @param hc_auth_id: the auth ID
 * @param user_type:
 * @param message: the message to verify
 * @param public_key: the public key
 * @param signature: signature to compare
 * @return 0 -- success, others -- failed
 */
int32_t verify_with_public_key(const int32_t user_type, const struct uint8_buff *message,
    struct var_buffer *public_key, struct signature *signature);

/*
 * Calculate BigNum Exponent
 * @param base 32 byte
 * @param exp 32 byte
 * @param big_num_len: big num len 384 or 256
 * @param out_result
 * @return others -- failed, 0 -- success
 */
int32_t cal_bignum_exp(struct var_buffer *base, struct var_buffer *exp,
    const uint32_t big_num_len, struct big_num *out_result);

/*
 * generate random string
 *
 * @param length : length of required random byte array
 * @return generated random uint8_t array
 */
struct random_value generate_random(uint32_t length);

/*
 * HMAC method
 *
 * @param key HMAC key
 * @param message message to be digested
 * @return others -- failed, 0 -- success
 */
int32_t compute_hmac(struct var_buffer *key, const struct uint8_buff *message, struct hmac *out_hmac);

/*
 * key derivation of HKDF, salt and info are offered
 *
 * @param sharedSecret the seed of the key derivation
 * @param salt salt used in HKDF
 * @param [out] out_hkadf,the derived key, out_hkadf.length must be specified
 * @return 0 = success, -1 = failed
 */
int32_t compute_hkdf(struct var_buffer *shared_secret, struct hc_salt *salt, char *key_info,
    uint32_t hkdf_len, struct var_buffer *out_hkdf);

/*
 * aes gcm encrypt.
 *
 * @param key: encrypt key
 * @param plain: data to be encrypted
 * @param aad:
 * @param out_cipher: encrypted data
 * @return 0 -- success, others -- failed
 */
int32_t aes_gcm_encrypt(struct var_buffer *key, const struct uint8_buff *plain,
    struct aes_aad *aad, struct uint8_buff *out_cipher);

/*
 * aes gcm decrypt.
 *
 * @param key: encrypt key
 * @param cipher: data to be decrypted
 * @param aad:
 * @param out_plain: edecrypted data
 * @return 0 -- success, others -- failed
 */
int32_t aes_gcm_decrypt(struct var_buffer *key, const struct uint8_buff *cipher,
    struct aes_aad *aad, struct uint8_buff *out_plain);

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
int32_t generate_lt_X25519_key_pair(struct hc_key_alias *key_alias, const struct hc_auth_id *auth_id);

int32_t aes_ccm_decrypt(struct var_buffer *key, const struct uint8_buff *cipher,
    struct aes_aad *aad, struct uint8_buff *out_plain);

int32_t get_cert_chain(const struct uint8_buff *challenge, struct hc_key_alias *sk_alias,
    struct uint8_buff *out_cert_chain);

int32_t asset_unwrap(struct uint8_buff *sec_data, struct hc_key_alias *dec_alias,
    struct hc_key_alias *target_alias);

int32_t get_key_attestation(const struct uint8_buff *challenge, struct hc_key_alias *sk_alias,
    struct uint8_buff *out_cert_chain);

int32_t gen_derived_key(struct hc_key_alias *base_alias, struct hc_key_alias *to_save_alias);

#endif

/*
 * load file hks keystore to buffer
 *
 * @return 0 -- success, others -- failed
 */
int32_t key_info_init(void);

#endif
