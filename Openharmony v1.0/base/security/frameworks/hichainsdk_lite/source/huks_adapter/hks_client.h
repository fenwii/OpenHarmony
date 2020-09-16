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

#ifndef HKS_CLIENT_H
#define HKS_CLIENT_H

#include "hks_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * hks_get_sdk_version
 * get sdk version
 * return value: none
 */
HKS_DLL_API_PUBLIC void hks_get_sdk_version(struct hks_blob *sdk_version);

/*
 * hks init
 * load file hks_keystore to buffer
 * parameter: none
 * return value: none
 */
HKS_DLL_API_PUBLIC int32_t hks_init(void);

/*
 * destroy
 * parameter: none
 * return value: none
 */
HKS_DLL_API_PUBLIC void hks_destroy(void);

/*
 * refresh key info and root key info
 * Reproduce the hks_keystore file header and clear the old key
 * Reproduce root key info
 * parameter: none
 * return value: none
 */
HKS_DLL_API_PUBLIC int32_t hks_refresh_key_info(void);

/*
 * generate key
 * Only ED25519 algorithm key pair generation is supported
 * The number of local storage keys (including
 * generated ED25519 public-private key pairs
 * imported ED25519 public keys) is limited to 16
 * key_alias: key alias, constraint condition:
 * key_alias->size must be less than or equal to 64
 * key_param: The parameter of the key which need to generate
 * constraint condition:
 * key_param cannot be NULL
 * key_param->key_type must be HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_generate_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param);

/*
 * generate asymmetric key
 * Only X25519 algorithm key pair generation is supported
 * key_param: The parameter of the key which need to generate
 * constraint condition:
 * key_param.key_type must be
 * HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519
 * key_param.usage must be
 * HKS_ALG_ECDH(HKS_ALG_SELECT_RAW)
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_generate_asymmetric_key(
    const struct hks_key_param *key_param, struct hks_blob *pri_key,
    struct hks_blob *pub_key);

/*
 * import public key
 * Only ED25519 public key import is supported
 * The number of local storage keys (including
 * generated ED25519 public-private key pairs
 * imported ED25519 public keys) is limited to no more than 16
 * key_param: The parameter of the key which need to generate
 * constraint condition:
 * key_param.key_type must be
 * HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_import_public_key(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *key);

/*
 * export public key
 * Only ED25519 public key export is supported
 * key_alias: constraint condition: key_alias->size <= 64
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_export_public_key(
    const struct hks_blob *key_alias, struct hks_blob *key);

/*
 * delete public key
 * Only ED25519 public key delete is supported
 * key_alias: constraint condition: key_alias->size <= 64
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_delete_key(const struct hks_blob *key_alias);

/*
 * get key param
 * key_alias: constraint condition: key_alias->size <= 64
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_get_key_param(const struct hks_blob *key_alias,
    struct hks_key_param *key_param);

/*
 * is key exist
 * key_alias: constraint condition: key_alias->size <= 64
 * return: 0 - exist; other - Non-existent
 */
HKS_DLL_API_PUBLIC int32_t hks_is_key_exist(const struct hks_blob *key_alias);

/*
 * generate random
 * random: random->size must be specified by the caller
 * constraint condition: random->size <= 1024
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_generate_random(struct hks_blob *random);

/*
 * sign
 * Only ED25519 local storage private key signature is supported
 * key_alias: constraint condition: key_alias->size <= 64
 * key_param: constraint condition:
 * key_param.key_type must be
 * HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519
 * signature: constraint condition:
 * signature->size must be greater than or equal to  64
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_asymmetric_sign(
    const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    struct hks_blob *signature);

/*
 * verify
 * Only ED25519 public key verify is supported
 * key: key alias or the key value itself,
 * differentiate by key.type:
 * if it is the key alias, key.type must be HKS_BLOB_TYPE_ALIAS
 * it is the key value itself, key.type must be HKS_BLOB_TYPE_KEY
 * signature: constraint condition:
 * signature->size must be greater than or equal to 64
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_asymmetric_verify(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    const struct hks_blob *signature);

/*
 * encrypt
 * only support AES-128-GCM encrypt
 * key: used to ecrypt plain_text
 * key_param: constraint condition:
 * key_param.key_type is HKS_KEY_TYPE_AES;
 * key_param.key_len is 128 or 192 or 256;
 * key_param.key_usage is HKS_KEY_USAGE_ENCRYPT;
 * key_param.key_mode is HKS_ALG_GCM;
 * key_param.key_pad is HKS_PADDING_NONE;
 * crypt_param:
 * crypt_param.nonce.size suggest to be 16
 * crypt_param.aad.size suggest to be 16
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag);

/*
 * decrypt
 * only support AES-128-GCM decrypt
 * key: used to decrypt cipher_text_with_tag
 * key_param: constraint condition:
 * key_param.key_type is HKS_KEY_TYPE_AES;
 * key_param.key_len is 128 or 192 or 256;
 * key_param.key_usage is HKS_KEY_USAGE_DECRYPT;
 * key_param.key_mode is HKS_ALG_GCM;
 * key_param.key_pad is HKS_PADDING_NONE;
 * crypt_param:
 * crypt_param.nonce.size suggest to be 16
 * crypt_param.aad.size suggest to be 16
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    struct hks_blob *plain_text,
    const struct hks_blob *cipher_text_with_tag);

/*
 * key agreement
 * private_key_param: constraint condition:
 * private_key_param.key_type is HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519
 * private_key_param.key_usage is HKS_KEY_USAGE_DERIVE
 * private_key_param.key_mode is the same as agreement_alg
 * private_key: constraint condition:
 * private_key.size must be 32
 * peer_public_key: constraint condition:
 * peer_public_key.size must be 32
 * agreement_alg: constraint condition:
 * agreement_alg must be
 * HKS_ALG_ECDH(HKS_ALG_SELECT_RAW)
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_key_agreement(struct hks_blob *agreed_key,
    const struct hks_key_param *private_key_param,
    const uint32_t agreement_alg, const struct hks_blob *private_key,
    const struct hks_blob *peer_public_key);

/*
 * key derivation
 * derived_key and data cannot be null, and size >= 16
 * key_param: constraint condition:
 * key_param.key_type is HKS_KEY_TYPE_DERIVE
 * key_param.key_usage is HKS_KEY_USAGE_DERIVE
 * key_param.key_mode is HKS_ALG_HKDF(HKS_ALG_HASH_SHA_256) or
 * HKS_ALG_HKDF(HKS_ALG_HASH_SHA_512)
 * key_param.key_len is 128 or 256
 * salt: constraint condition:
 * salt.size must be greater than or equal to 16
 * label: constraint condition:
 * lable.size must be greater than or equal to 16
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_key_derivation(struct hks_blob *derived_key,
    const struct hks_key_param *key_param, const struct hks_blob *kdf_key,
    const struct hks_blob *salt, const struct hks_blob *label);

/*
 * hks_hmac
 * key: data cannot be null,and size > 0
 * src_data: data cannot be null,and size > 0
 * alg: hks_alg_hmac(HKS_ALG_HASH_SHA_256) or
 * hks_alg_hmac(HKS_ALG_HASH_SHA_512)
 * output: output and output->data cannot be null
 * constraint condition:
 * when alg is hks_alg_hmac(HKS_ALG_HASH_SHA_256), output->size must be
 * greater than or equal to 32
 * when alg is hks_alg_hmac(HKS_ALG_HASH_SHA_512), output->size must be
 * greater than or equal to 64
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_hmac(const struct hks_blob *key,
    const uint32_t alg, const struct hks_blob *src_data,
    struct hks_blob *output);

/*
 * hks_hash
 * alg: Hash algorithm, Only spuuort SHA256/SHA512
 * src_data: data cannot be null, and size > 0
 * hash: hash and hash->data cannot be null
 * constraint condition:
 * when alg is HKS_ALG_HASH_SHA_256, hash->size must be
 * greater than or equal to 32
 * when alg is HKS_ALG_HASH_SHA_512, hash->size must be
 * greater than or equal to 64
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_hash(const uint32_t alg,
    const struct hks_blob *src_data, struct hks_blob *hash);

/*
 * hks_bn_exp_mod
 * x: output, x and x->data cannot be null, x->size >= n.size
 * a, e, n: input, data cannot be null, size > 0
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_bn_exp_mod(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e,
    const struct hks_blob *n);

/*
 * register log Interface
 * log: designated by the caller, invoked by hks
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_register_log_interface(
    const struct hks_log_f_group *log);

/*
 * get public key alias list Interface
 * key_alias_list: struct hks_blob array, alloc and free memory by the caller
 * list_count: public key alias number, alloc and free memory by the caller
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_get_pub_key_alias_list(
    struct hks_blob *key_alias_list, uint32_t *list_count);

#if defined (_SUPPORT_HKS_TEE_)
/*
 * cipher text unwrap Interface
 * key_alias: input key alias
 * target_alias: encrypt key alias
 * key_param: dencrypted export algorithm parameters
 * data: ciphertext data
 * unwrap_result: export result
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_unwrap(const struct hks_blob *key_alias,
    const struct hks_blob *target_alias,
    const struct hks_key_param *key_param,
    const struct hks_blob *data,
    struct hks_blob *unwrap_result);

/*
 * cipher text wrap Interface
 * key_alias: input key alias
 * target_alias: encrypt key alias
 * key_param: encrypted export algorithm parameters
 * data: business data
 * wrap_result: export ciphertext data
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_wrap(const struct hks_blob *key_alias,
    const struct hks_blob *target_alias,
    const struct hks_key_param *key_param,
    const struct hks_blob *data,
    struct hks_blob *wrap_result);

/*
 * key attestation Interface
 * key_alias: input key alias
 * key_param: input key parameters
 * att_spec: sttestation param data
 * cert_chain: output certificate chain data
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_key_attestation(
    const struct hks_blob *key_alias, const struct hks_key_param *key_param,
    const struct hks_attestation_spec *att_spec,
    struct hks_cert_chain *cert_chain);

/*
 * cipher text wrap Interface
 * key_alias: input key alias
 * key_param: input key parameters
 * cert_chain: output certificate chain data
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_get_cert_chain(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param,
    struct hks_cert_chain *cert_chain);

/*
 * generate asymmetric key
 * Only X25519 algorithm key pair generation is supported
 * key_param: The parameter of the key which need to generate
 * constraint condition:
 * key_param.key_type must be
 * HKS_KEY_TYPE_ECC_KEYPAIR_CURVE25519
 * key_param.usage must be
 * HKS_ALG_ECDH(HKS_ALG_SELECT_RAW)
 * return 0 OK, other error
 */
HKS_DLL_API_PUBLIC int32_t hks_generate_symmetric_key(
    const struct hks_blob *key_alias, const struct hks_key_param *key_param,
    const struct hks_derive_param *derive_param);

#endif

#ifdef __cplusplus
}
#endif

#endif /* HKS_CLIENT_H */
