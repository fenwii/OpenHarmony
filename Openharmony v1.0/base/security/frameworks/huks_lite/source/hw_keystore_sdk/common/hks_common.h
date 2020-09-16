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

#ifndef HKS_COMMON_H
#define HKS_COMMON_H

#include "hks_types.h"

#include <mbedtls/cipher.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <mbedtls/gcm.h>
#include <mbedtls/ccm.h>
#include <mbedtls/md.h>
#include <mbedtls/md2.h>
#include <mbedtls/md4.h>
#include <mbedtls/md5.h>
#include <mbedtls/md_internal.h>
#include <mbedtls/pk.h>
#include <mbedtls/pk_internal.h>
#include <mbedtls/platform_util.h>
#include <mbedtls/ripemd160.h>
#include <mbedtls/sha256.h>
#include <mbedtls/sha512.h>

#include "hks_hardware_api.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define HKS_ALG_MD2                             ((uint32_t)0x01000001)
#define HKS_ALG_MD4                             ((uint32_t)0x01000002)
#define HKS_ALG_MD5                             ((uint32_t)0x01000003)
#define HKS_ALG_RIPEMD160                       ((uint32_t)0x01000004)
#define HKS_ALG_SHA_1                           ((uint32_t)0x01000005)

#define HKS_ALG_AEAD_TAG_LENGTH_MASK            ((uint32_t)0x00003f00)
#define HKS_AEAD_TAG_LENGTH_OFFSET 8

#define HKS_BLOCK_CIPHER_BLOCK_SIZE(type) ((type) == HKS_KEY_TYPE_AES ? 16 : 0)

/*
 * The tag size for an AEAD algorithm, in bytes.
 *
 * \param alg  An AEAD algorithm
 *  (\c HKS_ALG_XXX value such that
 *  #hks_alg_is_aead(\p alg) is true).
 *
 * \return  The tag size for the specified algorithm.
 *  If the AEAD algorithm does not have an identified
 *  tag that can be distinguished from the rest of
 *  the ciphertext, return 0.
 *  If the AEAD algorithm is not recognized, return 0.
 *  An implementation may return either 0 or a
 *  correct size for an AEAD algorithm that it
 *  recognizes, but does not support.
 */
#define hks_aead_tag_length(alg) (hks_alg_is_aead(alg) ? \
    (((alg) & HKS_ALG_AEAD_TAG_LENGTH_MASK) >> HKS_AEAD_TAG_LENGTH_OFFSET) : 0)

#define HKS_ALG_VENDOR_FLAG                 ((uint32_t)0x80000000)
#define HKS_ALG_CATEGORY_MASK               ((uint32_t)0x7f000000)
#define HKS_ALG_CATEGORY_HASH               ((uint32_t)0x01000000)
#define HKS_ALG_CATEGORY_MAC                ((uint32_t)0x02000000)
#define HKS_ALG_CATEGORY_CIPHER             ((uint32_t)0x04000000)
#define HKS_ALG_CATEGORY_AEAD               ((uint32_t)0x06000000)
#define HKS_ALG_CATEGORY_SIGN               ((uint32_t)0x10000000)
#define HKS_ALG_CATEGORY_ASYMMETRIC_ENCRYPTION  ((uint32_t)0x12000000)
#define HKS_ALG_CATEGORY_KEY_AGREEMENT          ((uint32_t)0x22000000)
#define HKS_ALG_CATEGORY_KEY_DERIVATION         ((uint32_t)0x30000000)
#define HKS_ALG_CATEGORY_KEY_SELECTION          ((uint32_t)0x31000000)

/* DSA public key */
#define HKS_KEY_TYPE_DSA_PUBLIC_KEY         ((uint32_t)0x60020000)

/* DSA key pair (private and public key). */
#define HKS_KEY_TYPE_DSA_KEYPAIR            ((uint32_t)0x70020000)

/* Whether a key type is an DSA key (pair or public-only). */
#define hks_key_type_is_dsa(type) \
    (HKS_KEY_TYPE_PUBLIC_KEY_OF_KEYPAIR(type) == \
    HKS_KEY_TYPE_DSA_PUBLIC_KEY)

#define HKS_KEY_USAGE_SIGN             ((uint32_t)0x00000400)

/*
 * Whether the key may be used to verify a message signature.
 *
 * This flag allows the key to be used for a MAC verification operation
 * or for an asymmetric signature verification operation,
 * if otherwise permitted by by the key's type and policy.
 *
 * For a key pair, this concerns the public key.
 */
#define HKS_KEY_USAGE_VERIFY            ((uint32_t)0x00000800)
#define HKS_ALG_ANY_HASH                ((uint32_t)0x010000ff)
#define HKS_ALG_MAC_SUBCATEGORY_MASK    ((uint32_t)0x00c00000)
#define HKS_ALG_HMAC_BASE               ((uint32_t)0x02800000)

/*
 * Macro to build an HMAC algorithm.
 *
 * For example, #hks_alg_hmac(#HKS_ALG_SHA_256) is HMAC-SHA-256.
 *
 * \param hash_algA hash algorithm (\c HKS_ALG_XXX value such that
 * #hks_alg_is_hash(\p hash_alg) is true).
 *
 * \return The corresponding HMAC algorithm.
 * \return Unspecified if \p alg is not a supported
 * hash algorithm.
 */
#define hks_alg_hmac(hash_alg) \
    (HKS_ALG_HMAC_BASE | ((hash_alg) & HKS_ALG_HASH_MASK))

#define hks_alg_hmac_get_hash(hmac_alg) \
    (HKS_ALG_CATEGORY_HASH | ((hmac_alg) & HKS_ALG_HASH_MASK))

/*
 * Whether the specified algorithm is an HMAC algorithm.
 *
 * HMAC is a family of MAC algorithms that are based on a hash function.
 *
 * \param alg An algorithm identifier.
 *
 * \return 1 if \p alg is an HMAC algorithm, 0 otherwise.
 * This macro may return either 0 or 1 if \p alg is not a supported
 * algorithm identifier.
 */
#define hks_alg_is_hmac(alg) \
    (((alg) & (HKS_ALG_CATEGORY_MASK | HKS_ALG_MAC_SUBCATEGORY_MASK)) == \
     HKS_ALG_HMAC_BASE)

/*
 * In the encoding of a MAC algorithm, the bits corresponding to
 * HKS_ALG_MAC_TRUNCATION_MASK encode the length to which the MAC is
 * truncated. As an exception, the value 0 means the untruncated algorithm,
 * whatever its length is. The length is encoded in 6 bits, so it can
 * reach up to 63; the largest MAC is 64 bytes so its trivial truncation
 * to full length is correctly encoded as 0 and any non-trivial truncation
 * is correctly encoded as a value between 1 and 63.
 */
#define HKS_ALG_MAC_TRUNCATION_MASK     ((uint32_t)0x00003f00)
#define HKS_MAC_TRUNCATION_OFFSET 8


/* SHA2-224 */
#define HKS_ALG_SHA_224                 ((uint32_t)0x01000008)

/* SHA2-256 */
#define HKS_ALG_SHA_256                 ((uint32_t)0x01000009)

/* SHA2-384 */
#define HKS_ALG_SHA_384                 ((uint32_t)0x0100000a)

/* SHA2-512 */
#define HKS_ALG_SHA_512                 ((uint32_t)0x0100000b)

/* SHA2-512/224 */
#define HKS_ALG_SHA_512_224             ((uint32_t)0x0100000c)

/* SHA2-512/256 */
#define HKS_ALG_SHA_512_256             ((uint32_t)0x0100000d)

/* SHA3-224 */
#define HKS_ALG_SHA3_224                ((uint32_t)0x01000010)

/* SHA3-256 */
#define HKS_ALG_SHA3_256                ((uint32_t)0x01000011)

/* SHA3-384 */
#define HKS_ALG_SHA3_384                ((uint32_t)0x01000012)

/* SHA3-512 */
#define HKS_ALG_SHA3_512                ((uint32_t)0x01000013)

/* ECDH KEY  AGREEMENT */
#define HKS_ALG_ECDH_RAW                ((uint32_t)0x31000001)

/*
 * Whether the specified algorithm is an authenticated encryption
 * with associated data (AEAD) algorithm.
 *
 * \param alg An algorithm identifier.
 *
 * \return 1 if \p alg is an AEAD algorithm, 0 otherwise.
 * This macro may return either 0 or 1 if \p alg is not a supported
 * algorithm identifier.
 */
#define hks_alg_is_aead(alg) \
    (((alg) & HKS_ALG_CATEGORY_MASK) == HKS_ALG_CATEGORY_AEAD)

#define hks_alg_is_hash(alg) \
    (((alg) & HKS_ALG_CATEGORY_MASK) == HKS_ALG_CATEGORY_HASH)

#ifndef HKS_BLOB_DEFAULT_VALUE
#define HKS_BLOB_DEFAULT_VALUE ((struct hks_blob){ HKS_BLOB_TYPE_RAW, NULL, 0 })
#endif

/* the file name of the key storage */
#define HKS_KEY_STORE_FILE_NAME "hks_keystore"

/* the number of file clear data type */
#define HKS_INIT_DATA_TYPE_NUM    3

/* const define used in Ed25519 algorithm */
#define CRYPTO_SECRET_KEY_BYTES   64
#define CRYPTO_PUBLIC_KEY_BYTES   32
#define CRYPTO_BYTES              64

/* initialize data type - all zero */
enum hks_init_data_type {
    /* all zero */
    HKS_INIT_DATA_TYPE_ALL_ZERO = 0,

    /* all one */
    HKS_INIT_DATA_TYPE_ALL_ONE = 1,

    /* random */
    HKS_INIT_DATA_TYPE_RANDOM = 2,

    HKS_INIT_DATA_TYPE_MAX = HKS_INIT_DATA_TYPE_RANDOM
};

/* the length of hardware UDID */
#define HKS_HARDWARE_UDID_LEN 32

struct hks_aead_operation {
    const mbedtls_cipher_info_t *cipher_info;
    mbedtls_gcm_context gcm;
    mbedtls_ccm_context ccm;
    uint32_t core_alg;
    uint8_t full_tag_length;
    uint8_t tag_length;
};

struct hks_aead_data {
    uint8_t *nonce;
    size_t nonce_length;
    uint8_t *additional_data;
    size_t additional_data_length;
    uint8_t *ciphertext;
    size_t ciphertext_length;
    uint8_t *plaintext;
    size_t plaintext_length;
};

/*
 * malloc and initial memory
 * size: malloc memory length
 * ptr: output malloc pointer
 */
int32_t hks_malloc_init_ptr(uint32_t size, uint8_t **ptr);

/*
 * init hks_blob
 * alloc memory for blob->data , init blob->type and blob->size
 */
int32_t hks_blob_init(struct hks_blob *blob, size_t nmemb, size_t size,
    uint8_t type);

/*
 * destroy hks_blob
 * free the memory which blob->data point to
 */
void hks_blob_destroy(struct hks_blob *blob);

/*
 * is valid auth_id
 * check key_param->key_auth_id is valid
 */
int32_t hks_is_valid_auth_id(const struct hks_key_param *key_param);

/*
 * is valid alias
 * check alias is valid
 */
int32_t hks_is_valid_alias(const struct hks_blob *alias);

/*
 * copy key_param
 * copy from src hks_key_param to dst hks_key_param
 */
int32_t hks_cpy_key_param(struct hks_key_param *dst,
    const struct hks_key_param *src);

/*
 * destroy key_param
 * free the memory which pram->key_auth_id.data point to
 */
void hks_key_param_destroy(struct hks_key_param *pram);

/*
 * check return code
 * converting s into recognizable error number in hks_errno.h
 */
void hks_check_return_code(int32_t s, int32_t *ret);

#ifdef _SUPPORT_HKS_TEE_
int32_t hks_is_valid_data_creator(const struct hks_key_param *key_param);

int32_t hks_is_valid_data_owner(const struct hks_key_param *key_param);

int32_t hks_is_valid_ext_info(const struct hks_key_param *key_param);
#endif

int32_t hks_mbedtls_aead_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, struct hks_aead_data *aead_data,
    size_t *ciphertext_output_length);

int32_t hks_aead_unpadded_locate_tag(size_t tag_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    size_t plaintext_size, const uint8_t **p_tag);

int32_t hks_mbedtls_aead_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    struct hks_aead_data *aead_data, size_t *plaintext_output_length);

int32_t hks_mbedtls_key_derivation(struct hks_blob *derived_key,
    const uint32_t alg, const struct hks_blob *kdf_key,
    const struct hks_blob *salt,
    const struct hks_blob *label);

int32_t hks_endian_swap(uint8_t *p_data, int32_t length);

/*
 * generate random number
 * parameter:
 *     random  - [out]  - the buffer of random number.
 *     len     - [in]   - the length of random number.
 * return value:
 *     success or error code
 */
int32_t hks_gen_random(uint8_t *random, uint32_t len);

/*
 * calculate SHA256
 * parameter:
 *     hash_src      - [in]      - hash source.
 *     hash_src_num  - [in]      - hash source number.
 *     hash_result   - [in,out]  - hash result.
 * return value:
 *     success or error code
 */
int32_t hks_calc_sha256(const struct hks_blob *hash_src, uint32_t hash_src_num,
    struct hks_blob *hash_result);

/*
 * initialize buffer data
 * parameter:
 *     data_type - [in]  - data type
 *     buf       - [out] - buffer
 *     buf_len   - [in]  - the length of buffer
 * return value:
 *     success or error code
 */
int32_t hks_init_buf_data(uint8_t data_type, uint8_t *buf, uint32_t buf_len);

int32_t mbedtls_to_hks_error(int ret);

/*
 * XOR operation
 * parameter:
 *     src1          - [in]  - source data #1.
 *     src2          - [in]  - source data #2.
 *     result        - [out] - result.
 * return value: none
 */
void hks_xor(const struct hks_blob *src1, const struct hks_blob *src2,
    struct hks_blob *result);

/*
 * register callback for get hardware UDID(Unique Device Identifier)
 * parameter:
 *     callback - [in]   - The callback functions for get hardware UDID.
 * return value:
 *     success or error code
 */
int32_t hks_reg_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback);

/*
 * get hardware UDID(Unique Device Identifier)
 * parameter:
 *     udid     - [out]  - UDID.
 *     udid_len - [in]   - the length of UDID.
 * return value:
 *     success or error code
 */
int32_t hks_get_hardware_udid(uint8_t *udid, uint32_t udid_len);

/*
 * calculate cypto hash using mbedtls
 * parameter:
 *     out - [out] - output hash data.
 *     in  - [in]  - input data
 *     len - [in]  - length of input data
 */
void crypto_hash_sha512(unsigned char *out, const unsigned char *in, const int len);

#ifdef _SECURE_ENVIREMENT_NMI_
#define HKS_OPERATION_MODE_ENCRYPT      0
#define HKS_OPERATION_MODE_DECRYPT      1

/* AES encrypt IV minimum size */
#define HKS_GCM_MIN_IV_LENGTH           12
#define HKS_CCM_MIN_IV_LENGTH           7
#define HKS_CCM_MAX_IV_LENGTH           13
#define HKS_CCM_MAX_AAD_LENGTH          0xFF00

#define HKS_AES_IV_LENGTH               16
#define HKS_MBEDTLS_TAG_LENGTH          16
#define HKS_AES_ENCRYPT_BLOCK_SIZE      16

#define HKS_PKI_ALG_ECC                 0
#define HKS_PKI_ALG_RSA                 1

#define MAX_DEVICE_KEY_NUMBER           2
#define KM_DIGEST_SHA256_LEN            32 /* sha256, 256/8 = 32 bytes */
#define MAX_SIGNATURE_LEN               256
#define HKS_PKI_CHALLENGE_LEN           64
#define MAX_FLASH_SIZE                  8192
#define HKS_ROOT_KEY_SALT_LEN           16
#define HKS_PKI_ALG_NAME_LEN            24

#define HKS_EFUSE_LOCK_ROOT_KEY_STATE     0x00000010 /* the 4th bit is set: HI_EFUSE_LOCK_ROOT_KEY_ID */
#define HKS_EFUSE_LOCK_ROOT_SALT_STATE    0x04000000 /* the 26th bit is set: HI_EFUSE_LOCK_TEE_SALT_ID */

enum {
    ASN1_TLV_BUFFER_ONLY_TYPE_LENGTH = 1,
    ASN1_TLV_BUFFER_TYPE_NULL_LENGTH = 2,
    ASN1_TLV_BUFFER_MIN_LENGTH = 3,
    ASN1_TLV_BUFFER_TAG_TYPE_2_MIN_LEN = 4,
};

enum {
    ASN1_TYPE_BOOLEAN = 0x01,
    ASN1_TYPE_INTEGER = 0x02,
    ASN1_TYPE_BIT_STRING = 0x03,
    ASN1_TYPE_OCTET_STRING = 0x04,
    ASN1_TYPE_NULL = 0x05,
    ASN1_TYPE_OBJECT_IDENTIFIER = 0x06,
    ASN1_TYPE_REAL = 0x09,
    ASN1_TYPE_ENUMERATED = 0x0A,
    ASN1_TYPE_RELATIVE_OID = 0x0D,
    ASN1_TYPE_PRINTABLE_STRING = 0x13,
    ASN1_TYPE_SEQ = 0x30,
    ASN1_TYPE_SET = 0x31,
};

enum {
    ASN1_MAX_VAL_NO_EXTRA_LEN_BYTE = 0x7F,
    ASN1_MIN_VAL_1_EXTRA_LEN_BYTE = 0x80,
    ASN1_TAG_TYPE_1_BYTE_LEN = 0x81,
    ASN1_TAG_TYPE_2_BYTE_LEN = 0x82,
};

int32_t hks_aes_cbc_decrypt_data(const struct hks_blob *cipher_text,
    struct hks_blob *plain_text, const struct hks_blob *iv_blob, uint32_t padding_mode);

int32_t hks_aes_cbc_encrypt_data(const struct hks_blob *plain_text,
    struct hks_blob *cipher_text, struct hks_blob *iv_blob, uint32_t padding_mode);

int32_t hks_blob_material_init(struct hks_blob **blob);

int32_t hks_encrypt_material_init(struct hks_encrypt_material *encrypt_material);

void hks_encrypt_material_destroy_free(struct hks_encrypt_material *encrypt_material);

int32_t hks_is_valid_output_key(const struct hks_blob *output_key);

int32_t hks_is_valid_symmetric_key_param(const struct hks_key_param *key_param);

int32_t hks_check_symmetric_data_info(const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *input_text,
    const struct hks_blob *output_text, int32_t operation_mode);

int32_t hks_mbedtls_symmetric_encrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text, struct hks_blob *cipher_text_with_tag);

int32_t hks_mbedtls_symmetric_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    const struct hks_blob *cipher_text_with_tag, struct hks_blob *plain_text);

int32_t hks_efuse_root_salt_read(uint8_t *root_key_salt_data, uint32_t root_key_salt_len);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
