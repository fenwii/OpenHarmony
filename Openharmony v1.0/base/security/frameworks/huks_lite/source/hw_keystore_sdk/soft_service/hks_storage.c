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

#include "hks_storage.h"

#include <stdlib.h>
#include <string.h>

#include <mbedtls/ctr_drbg.h>
#include <mbedtls/ecdh.h>
#include <mbedtls/entropy.h>
#include <mbedtls/platform.h>

#include "securec.h"

#include "common/hks_common.h"
#include "common/hks_log_utils.h"
#include "common/hks_mem.h"
#include "hks_errno.h"
#include "hks_file.h"
#include "hks_rkc.h"

/* Sealing algorithm defines how key is protected. */
#define HKS_SEALING_NONCE_SIZE          16
#define HKS_SEALING_TAG_SIZE            16
#define HKS_SEALING_ALG_MASK            ((uint32_t)0xffff0000)
#define HKS_SEALING_AES_GCM_128         ((uint32_t)0x01010000)
#define HKS_SEALING_AES_GCM_256         ((uint32_t)0x01020000)

#define HKS_SEALING_HKDF_MASK           ((uint32_t)0x000000ff)
#define HKS_SEALING_HKDF_SHA_256        ((uint32_t)0x00000001)
#define HKS_SEALING_HKDF_SHA_512        ((uint32_t)0x00000002)

#define HKS_SEALING_AES_GCM_128_SHA_256 (HKS_SEALING_AES_GCM_128 | \
    HKS_SEALING_HKDF_SHA_256)
#define HKS_SEALING_AES_GCM_256_SHA_256 (HKS_SEALING_AES_GCM_256 | \
    HKS_SEALING_HKDF_SHA_256)
#define HKS_SEALING_AES_GCM_128_SHA_512 (HKS_SEALING_AES_GCM_128 | \
    HKS_SEALING_HKDF_SHA_512)
#define HKS_SEALING_AES_GCM_256_SHA_512 (HKS_SEALING_AES_GCM_256 | \
    HKS_SEALING_HKDF_SHA_512)

#define HKS_SEALING_DEFAULT             HKS_SEALING_AES_GCM_256_SHA_256

#ifndef hks_bits_to_bytes
#define hks_bits_to_bytes(x) (((x) + 7) / 8)
#endif

#define HKS_HEADER_RESERVE_SIZE  7
#define BUF_SIZE    65536
#define HKS_SLOT_PUBLIC_KEY_IDLE             ((uint8_t)0x00)
#define HKS_SLOT_PUBLIC_KEY_OCCUPY           ((uint8_t)0x01)
#define HKS_SLOT_KEYPAIR_IDLE                ((uint8_t)0x02)
#define HKS_SLOT_KEYPAIR_OCCUPY              ((uint8_t)0x03)

static int32_t hks_write_key_info_check(const struct hks_blob *key_alias,
    const struct hks_storage_key_info *key_info);

static int32_t hks_get_key_info_init(const struct hks_blob *key_alias,
    struct hks_key_param *key_param, uint8_t **key_pos);

static int32_t hks_refresh_header_hash(void);

static int32_t hks_sync_buf_to_file(void);

static int32_t hks_get_key_pos(const struct hks_blob *key_alias, uint8_t **pos);

/*
 * headerlen = version + key_count + slot_count + sealing_alg +
 *    sealing_nonce + hash
 * header = version(2 bytes) | key_count(1 bytes)
 * | slot_count(1 bytes)
 * | sealing_alg(4 bytes) | sealing_nonce(16 bytes) | hash(64 bytes)
 */
static uint16_t hks_get_header_len(void)
{
    uint16_t header_len = (sizeof(uint16_t) + sizeof(uint8_t) +
        sizeof(uint8_t) + sizeof(uint32_t) + HKS_SEALING_NONCE_SIZE +
        HKS_HEADER_HASH_SIZE);
    return header_len;
}

/*
 * slotlen = falgs+ sealing_nonce + alias_size + alias + param + key_size + key
 * keyslot = falgs(1 bytes) | sealing_nonce(16 bytes) | alias_size(1 bytes)
 *       | alias(alias_size bytes) | param | key_size(1 bytes)
 *       | key(key_size bytes)
 * param = key_type(4 bytes) | key_len(2 bytes) | usage(4 bytes) | padding(1 bytes)
 *       | mode(4 bytes) | key_role(4 bytes) | domain(2 bytes)
 *       | auth_id_type(1 bytes) | auth_id_size(1 bytes)
 *       | auth_id_data( auth_id_size bytes)
 *
 * alias : assign  (HKS_ALIAS_MAX_SIZE) bytes
 * auth_id_data : assign  (HKS_AUTH_ID_MAX_SIZE) bytes
 * key: assign  (HKS_KEY_PAIR_CIPHER_ED25519) bytes
 */
static uint16_t hks_get_key_slot_len(void)
{
    uint16_t slot_len = (sizeof(uint8_t) + HKS_SEALING_NONCE_SIZE +
            sizeof(uint8_t) + HKS_ALIAS_MAX_SIZE + (sizeof(uint32_t) +
            sizeof(uint16_t) + sizeof(uint32_t) +
            sizeof(uint8_t) + sizeof(uint32_t) +
            sizeof(uint32_t) + sizeof(uint16_t) +
            sizeof(uint8_t) + sizeof(uint8_t) +
            HKS_AUTH_ID_MAX_SIZE) +
            sizeof(uint8_t) + HKS_KEY_PAIR_CIPHER_ED25519);
    return slot_len;
}

/* Caution: only used in local machine, endian is not considerred */
static inline uint32_t hks_blob_write_uint32(uint8_t *buf, uint32_t value)
{
    *((uint32_t *)buf) = value;
    return sizeof(value);
}

/* Caution: only used in local machine, endian is not considerred */
static inline uint32_t hks_blob_read_uint32(uint32_t *value, const uint8_t *buf)
{
    *value = *((uint32_t *)buf);
    return sizeof(uint32_t);
}

/* Caution: only used in local machine, endian is not considerred */
static inline uint32_t hks_blob_write_uint16(uint8_t *buf, uint16_t value)
{
    *((uint16_t *)buf) = value;
    return sizeof(value);
}

/* Caution: only used in local machine, endian is not considerred */
static inline uint32_t hks_blob_read_uint16(uint16_t *value, const uint8_t *buf)
{
    *value = *((uint16_t *)buf);
    return sizeof(uint16_t);
}

/* Caution: only used in local machine, endian is not considerred */
static inline uint32_t hks_blob_write_uint8(uint8_t *buf, uint8_t value)
{
    *((uint8_t *)buf) = value;
    return sizeof(value);
}

/* Caution: only used in local machine, endian is not considerred */
static inline uint32_t hks_blob_read_uint8(uint8_t *value, const uint8_t *buf)
{
    *value = *((uint8_t *)buf);
    return sizeof(uint8_t);
}

static int32_t hks_blob_write_buf(uint8_t *dest, uint32_t dest_max,
    const uint8_t *src, uint32_t n, uint32_t *ret_offset)
{
    if ((dest == NULL) || (src == NULL) || (ret_offset == NULL))
        return HKS_ERROR_NULL_POINTER;

    if ((n == 0) || (dest_max < n))
        /* in this case, it will return the length of blob, so return 0 */
        return HKS_STATUS_OK;

    if (memcpy_s(dest, dest_max, src, n) != EOK)
        return HKS_ERROR_BAD_STATE;

    *ret_offset += n;
    return HKS_STATUS_OK;
}

/* The buffer is HKS_BUF_BYTES bytes */
static uint8_t *g_storage_image_buffer = NULL;

static int32_t hks_apply_buffer(size_t count, size_t size)
{
    if (g_storage_image_buffer != NULL)
        return HKS_STATUS_OK;
    if ((count == 0) || (count > BUF_SIZE) ||
        (size == 0) || (size > BUF_SIZE))
        return HKS_ERROR_MALLOC_FAIL;

    g_storage_image_buffer = (uint8_t *)HKS_CALLOC(count, size);
    if (g_storage_image_buffer == NULL)
        return HKS_ERROR_MALLOC_FAIL;
    return HKS_STATUS_OK;
}

static int32_t hks_init_buffer(void)
{
    if (g_storage_image_buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    if (memset_s(g_storage_image_buffer, HKS_BUF_BYTES, 0, HKS_BUF_BYTES) != EOK)
        return HKS_ERROR_BAD_STATE;

    /* Generate random nonce for sealing */
    uint8_t nonce[HKS_SEALING_NONCE_SIZE] = {0};
    /* Generate random nonce */
    int32_t ret = hks_gen_random(nonce, HKS_SEALING_NONCE_SIZE);

    if (ret != HKS_STATUS_OK)
        return ret;

    /* encode extra internal info */
    uint32_t n = 0;
    uint16_t version = 0;
    uint8_t key_count = 0;
    uint8_t slot_count = 0;
    uint32_t sealing_alg = HKS_SEALING_DEFAULT;

    n += hks_blob_write_uint16((g_storage_image_buffer + n), version); /* version */
    n += hks_blob_write_uint8((g_storage_image_buffer + n), key_count); /* key_count */
    n += hks_blob_write_uint8((g_storage_image_buffer + n), slot_count); /* slot_count */
    n += hks_blob_write_uint32((g_storage_image_buffer + n), sealing_alg); /* sealing_alg */
    /* sealing_nonce */
    ret = hks_blob_write_buf((g_storage_image_buffer + n), (hks_get_header_len() - n), nonce,
        HKS_SEALING_NONCE_SIZE, &n);
    if (ret != HKS_STATUS_OK)
        return ret;

    return HKS_STATUS_OK;
}

static uint8_t *hks_get_buffer(void)
{
    return g_storage_image_buffer;
}

static void hks_clean_buffer(void)
{
    if (g_storage_image_buffer == NULL) {
        log_info("g_storage_image_buffer is null");
        return;
    }

    (void)memset_s(g_storage_image_buffer, HKS_BUF_BYTES, 0, HKS_BUF_BYTES);
}

static void hks_free_buffer(void)
{
    hks_clean_buffer();
    hks_free_ptr(g_storage_image_buffer);
}

/*
 * calculate hash sha512
 * the length of hash512 must be 64, which should be guaranteed by caller
 */
static int32_t hks_calc_hash_sha512(uint8_t *hash512, uint16_t size)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    if (size == 0)
        return HKS_ERROR_BUFFER_TOO_SMALL;
    uint8_t *buf = (uint8_t *)HKS_CALLOC(sizeof(uint8_t), size);

    if (buf == NULL)
        return HKS_ERROR_MALLOC_FAIL;

    if (memcpy_s(buf, size, buffer, size) != EOK) {
        hks_free_ptr(buf);
        return HKS_ERROR_BAD_STATE;
    }

    crypto_hash_sha512(hash512, buf, size);

    /* clear buffer after use before free. Don't remove! */
    (void)memset_s(buf, size, 0, size);

    hks_free_ptr(buf);
    return HKS_STATUS_OK;
}

static int32_t hks_check_data_valid(const uint8_t *buffer)
{
    uint8_t hash512[HKS_HEADER_HASH_SIZE] = {0};
    uint16_t size = hks_get_header_len() - HKS_HEADER_HASH_SIZE;
    int32_t status = hks_calc_hash_sha512(hash512, size);

    if (status != HKS_STATUS_OK)
        return status;

    if (memcmp(hash512, (buffer + size), HKS_HEADER_HASH_SIZE) != 0)
        return HKS_ERROR_INVALID_KEY_FILE;

    return HKS_STATUS_OK;
}

int32_t hks_load_file_to_buffer(const char *file_name, int32_t *is_key_info_exist)
{
    if ((file_name == NULL) || (is_key_info_exist == NULL))
        return HKS_ERROR_NULL_POINTER;

    if (g_storage_image_buffer != NULL) {
        *is_key_info_exist = HKS_BOOL_TRUE;
        return HKS_STATUS_OK;
    }

    int32_t status = hks_apply_buffer(sizeof(uint8_t), HKS_BUF_BYTES);

    if (status != HKS_STATUS_OK)
        return status;

    hks_clean_buffer();

    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    int32_t len = 0;
    uint32_t offset = hks_get_store_file_offset();

    if (offset >= HKS_BUF_BYTES) {
        hks_free_buffer();
        return HKS_ERROR_INTERNAL_UNKOWN;
    }

    status = hks_file_read(file_name, offset,
        buffer, (HKS_BUF_BYTES - offset), &len);
    if (status != HKS_STATUS_OK) {
        hks_free_buffer();
        return status;
    }
    if (len > 0) {
        status = hks_check_data_valid(buffer);
        if (status != HKS_STATUS_OK) {
            hks_free_buffer();
            return status;
        }
        *is_key_info_exist = HKS_BOOL_TRUE;
    }

    if (len == 0) {
        status = hks_init_buffer();
        if (status != HKS_STATUS_OK) {
            hks_free_buffer();
            return status;
        }
    }
    return status;
}

int32_t hks_storage_clean_key_info(void)
{
    int32_t status = hks_apply_buffer(sizeof(uint8_t), HKS_BUF_BYTES);

    if (status != HKS_STATUS_OK)
        return status;

    hks_clean_buffer();
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    status = hks_init_buffer();
    if (status != HKS_STATUS_OK) {
        hks_free_buffer();
        return status;
    }

    status = hks_refresh_header_hash();
    if (status != HKS_STATUS_OK) {
        hks_free_buffer();
        return status;
    }

    status = hks_sync_buf_to_file();
    if (status != HKS_STATUS_OK) {
        hks_free_buffer();
        return status;
    }
    return status;
}

static int32_t hks_storage_get_key_count(uint32_t *key_num)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint8_t key_count = 0;
    uint32_t key_count_pos = sizeof(uint16_t);

    hks_blob_read_uint8(&key_count, (buffer + key_count_pos));
    *key_num = key_count;
    return HKS_STATUS_OK;
}

static uint8_t hks_get_slot_count_loop(void)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return 0;

    uint32_t slot_count_pos = sizeof(uint16_t) + sizeof(uint8_t);
    uint8_t slot_count = 0;

    hks_blob_read_uint8(&slot_count, (buffer + slot_count_pos));

    uint8_t max_num = HKS_LOCAL_STORAGE_KEY_MAX_NUM;
    uint8_t slot_count_loop = (slot_count <= max_num) ?
        slot_count : max_num;

    return slot_count_loop;
}

int hks_is_key_exist_in_store(const struct hks_blob *key_alias)
{
    int32_t status = hks_is_valid_alias(key_alias);

    if (status != HKS_STATUS_OK)
        return HKS_BOOL_FALSE;

    uint8_t *key_pos = NULL;

    status = hks_get_key_pos(key_alias, &key_pos);
    if (status != HKS_STATUS_OK)
        return HKS_BOOL_FALSE;

    if (key_pos != NULL)
        return HKS_BOOL_TRUE;

    return HKS_BOOL_FALSE;
}

int hks_is_key_can_store(const struct hks_blob *key_alias, uint32_t max_num)
{
    uint32_t key_num = HKS_LOCAL_STORAGE_KEY_MAX_NUM;
    int32_t status = hks_storage_get_key_count(&key_num);

    if (status != HKS_STATUS_OK)
        return HKS_BOOL_FALSE;

    if (key_num < max_num)
        return HKS_BOOL_TRUE;

    if ((key_num == max_num) && (hks_is_key_exist_in_store(key_alias) == HKS_BOOL_TRUE))
        return HKS_BOOL_TRUE;

    return HKS_BOOL_FALSE;
}
/*
 * before call this func make sure that
 * cipher_text.size >= key.size + HKS_SEALING_TAG_SIZE
 */
int32_t hks_storage_encrypt_key_blob(struct hks_blob *cipher_text,
    uint32_t sealing_alg, const struct hks_blob *key,
    const struct hks_blob *nonce, const struct hks_blob *aad)
{
    hks_if_true_return_error(((cipher_text == NULL) || (key == NULL) || (nonce == NULL) || (aad == NULL)),
        HKS_ERROR_NULL_POINTER);

    (void)sealing_alg;

    struct hks_blob kek;
    int32_t status = hks_blob_init(&kek, sizeof(uint8_t),
        HKS_RKC_KEK_LEN, HKS_BLOB_TYPE_KEY);

    hks_if_status_error_goto_error(status, exit);
    status = hks_rkc_get_kek(nonce, &kek);
    hks_if_status_error_goto_error(status, exit);

    size_t cipher_text_length = 0;
    struct hks_key_param key_param;

    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));

    key_param.key_len = HKS_MAX_KEY_LEN_256;
    key_param.key_type = HKS_KEY_TYPE_AES;
    key_param.key_mode = HKS_ALG_GCM;
    struct hks_aead_data aead_data;

    aead_data.nonce = nonce->data;
    aead_data.nonce_length = nonce->size;
    aead_data.additional_data = aad->data;
    aead_data.additional_data_length = aad->size;
    aead_data.ciphertext = cipher_text->data;
    aead_data.ciphertext_length = cipher_text->size;
    aead_data.plaintext = key->data;
    aead_data.plaintext_length = key->size;

    status = hks_mbedtls_aead_encrypt(&kek, &key_param, &aead_data,
        &cipher_text_length);

    if (status != HKS_STATUS_OK) {
        hks_blob_destroy(cipher_text);
        goto exit;
    }

    if (cipher_text_length < UINT32_MAX)
        cipher_text->size = (uint32_t)cipher_text_length;
    else
        status = HKS_ERROR_DATA_CORRUPT;

exit:
    hks_blob_destroy(&kek);
    return status;
}

/*
 * before call this func make sure that cipher_text.size >=
 * HKS_SEALING_TAG_SIZE and
 * plain_text.size >= cipher_text.size - HKS_SEALING_TAG_SIZE
 */
int32_t hks_storage_decrypt_key_blob(struct hks_blob *plain_text,
    uint32_t sealing_alg, const struct hks_blob *cipher_text,
    const struct hks_blob *nonce, const struct hks_blob *aad)
{
    hks_if_true_return_error(((plain_text == NULL) || (cipher_text == NULL) || (nonce == NULL) || (aad == NULL)),
        HKS_ERROR_NULL_POINTER);

    (void)sealing_alg;

    struct hks_blob kek;
    int32_t status = hks_blob_init(&kek, sizeof(uint8_t), HKS_RKC_KEK_LEN, HKS_BLOB_TYPE_KEY);

    hks_if_status_error_goto_error(status, exit);
    status = hks_rkc_get_kek(nonce, &kek);
    hks_if_status_error_goto_error(status, exit);

    size_t plain_text_length = 0;
    struct hks_key_param key_param;

    (void)memset_s(&key_param, sizeof(key_param), 0, sizeof(key_param));

    key_param.key_len = HKS_MAX_KEY_LEN_256;
    key_param.key_type = HKS_KEY_TYPE_AES;
    key_param.key_mode = HKS_ALG_GCM;

    struct hks_aead_data aead_data;

    aead_data.nonce = nonce->data;
    aead_data.nonce_length = nonce->size;
    aead_data.additional_data = aad->data;
    aead_data.additional_data_length = aad->size;
    aead_data.plaintext = plain_text->data;
    aead_data.plaintext_length = plain_text->size;
    aead_data.ciphertext = cipher_text->data;
    aead_data.ciphertext_length = cipher_text->size;

    status = hks_mbedtls_aead_decrypt(&kek, &key_param, &aead_data, &plain_text_length);

    if (status != HKS_STATUS_OK) {
        hks_blob_destroy(plain_text);
        goto exit;
    }

    if (plain_text_length < UINT32_MAX)
        plain_text->size = (uint32_t)plain_text_length;
    else
        status = HKS_ERROR_DATA_CORRUPT;

exit:
    hks_blob_destroy(&kek);
    return status;
}

static int32_t hks_get_sealing_info(uint32_t *sealing_alg)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint32_t seal_alg_shift = sizeof(uint16_t) + sizeof(uint8_t) +
        sizeof(uint8_t);

    seal_alg_shift += hks_blob_read_uint32(sealing_alg,
        (buffer + seal_alg_shift));
    return HKS_STATUS_OK;
}

static int32_t hks_get_key_pos(const struct hks_blob *key_alias, uint8_t **pos)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint8_t slot_count_loop = hks_get_slot_count_loop();
    uint8_t *tmp = buffer + hks_get_header_len();
    uint16_t slot_shift = hks_get_key_slot_len();
    uint8_t flags = 0;
    uint8_t alias_size = 0;

    for (uint8_t i = 0; i < slot_count_loop; i++) {
        hks_blob_read_uint8(&flags, tmp);
        if ((flags == HKS_SLOT_PUBLIC_KEY_IDLE) ||
            (flags == HKS_SLOT_KEYPAIR_IDLE)) {
            tmp += slot_shift;
            continue;
        }
        uint32_t alias_size_shift = sizeof(uint8_t) +
            HKS_SEALING_NONCE_SIZE;

        hks_blob_read_uint8(&alias_size, (tmp + alias_size_shift));
        if (alias_size != key_alias->size) {
            tmp += slot_shift;
            continue;
        }
        uint32_t alias_shift = alias_size_shift + sizeof(uint8_t);

        if (memcmp(key_alias->data, (tmp + alias_shift),
            key_alias->size) == 0) {
            *pos = tmp;
            break;
        }
        tmp += slot_shift;
    }
    return HKS_STATUS_OK;
}

static int32_t hks_add_slot_count(void)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint8_t slot_count = 0;
    uint32_t slot_count_pos = sizeof(uint16_t) + sizeof(uint8_t);

    hks_blob_read_uint8(&slot_count, (buffer + slot_count_pos));
    ++slot_count;
    hks_blob_write_uint8((buffer + slot_count_pos), slot_count);
    return HKS_STATUS_OK;
}

static int32_t hks_add_key_count(void)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint8_t key_count = 0;
    uint32_t key_count_pos = sizeof(uint16_t);

    hks_blob_read_uint8(&key_count, (buffer + key_count_pos));
    ++key_count;
    hks_blob_write_uint8((buffer + key_count_pos), key_count);
    return HKS_STATUS_OK;
}

static int32_t hks_reduce_key_count(void)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint8_t key_count = 0;
    uint32_t key_count_pos = sizeof(uint16_t);

    hks_blob_read_uint8(&key_count, (buffer + key_count_pos));
    if (key_count == 0)
        return HKS_STATUS_OK;
    --key_count;
    hks_blob_write_uint8((buffer + key_count_pos), key_count);
    return HKS_STATUS_OK;
}

static int32_t hks_slot_add_key(const uint8_t *buf, uint32_t len)
{
    uint8_t *image_buffer = hks_get_buffer();

    if (image_buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint8_t slot_count_loop = hks_get_slot_count_loop();
    uint8_t *tmp = image_buffer + hks_get_header_len();
    uint16_t slot_shift = hks_get_key_slot_len();
    uint8_t flags = 0;
    int32_t find_idle = HKS_BOOL_FALSE;

    for (uint8_t i = 0; i < slot_count_loop; i++) {
        hks_blob_read_uint8(&flags, tmp);
        if ((flags == HKS_SLOT_PUBLIC_KEY_IDLE) ||
            (flags == HKS_SLOT_KEYPAIR_IDLE)) {
            find_idle = HKS_BOOL_TRUE;
            break;
        }
        tmp += slot_shift;
    }

    if (memset_s(tmp, slot_shift, 0, slot_shift) != EOK)
        return HKS_ERROR_BAD_STATE;
    if (memcpy_s(tmp, len, buf, slot_shift) != EOK)
        return HKS_ERROR_BAD_STATE;
    int32_t status = hks_add_key_count();

    if (status != HKS_STATUS_OK)
        return status;

    if (find_idle == HKS_BOOL_FALSE) {
        status = hks_add_slot_count();
        if (status != HKS_STATUS_OK)
            return status;
    }
    return HKS_STATUS_OK;
}

static int32_t hks_serialize_fill_buf(uint8_t *buf,
    const struct hks_blob *key_alias, uint32_t key_size,
    const struct hks_storage_key_info *key_info, uint32_t *shift)
{
    uint32_t n = *shift;
    uint8_t alias_size = (uint8_t)(key_alias->size);

    n += hks_blob_write_uint8((buf + n), alias_size); /* alias_size */
    /* alias */
    int32_t status = hks_blob_write_buf((buf + n), (hks_get_key_slot_len() - n), key_alias->data, key_alias->size, &n);

    if (status != HKS_STATUS_OK)
        return status;

    /* encode param */
    n += hks_blob_write_uint32((buf + n), key_info->param->key_type);
    if (key_info->param->key_len > UINT16_MAX)
        return HKS_ERROR_INVALID_ARGUMENT;
    uint16_t key_len = (uint16_t)key_info->param->key_len;

    n += hks_blob_write_uint16((buf + n), key_len);
    n += hks_blob_write_uint32((buf + n), key_info->param->key_usage);
    if (key_info->param->key_pad > UINT8_MAX)
        return HKS_ERROR_INVALID_ARGUMENT;
    uint8_t key_pad = (uint8_t)key_info->param->key_pad;

    n += hks_blob_write_uint8((buf + n), key_pad);
    n += hks_blob_write_uint32((buf + n), key_info->param->key_mode);
    n += hks_blob_write_uint32((buf + n), key_info->param->key_role);
    n += hks_blob_write_uint16((buf + n), key_info->param->key_domain);
    n += hks_blob_write_uint8((buf + n), key_info->param->key_auth_id.type);
    if (key_info->param->key_auth_id.size > HKS_AUTH_ID_MAX_SIZE)
        return HKS_ERROR_INVALID_ARGUMENT;
    uint8_t key_auth_id_size = (uint8_t)key_info->param->key_auth_id.size;

    n += hks_blob_write_uint8((buf + n), key_auth_id_size);
    status = hks_blob_write_buf((buf + n), (hks_get_key_slot_len() - n),
        key_info->param->key_auth_id.data, key_info->param->key_auth_id.size, &n);
    if (status != HKS_STATUS_OK)
        return status;

    /* key_size */
    uint8_t k_size = (uint8_t)(key_size + HKS_SEALING_TAG_SIZE);

    n += hks_blob_write_uint8((buf + n), k_size);
    *shift = n;
    return HKS_STATUS_OK;
}

static int32_t hks_prepare_serialize_key_info(
    const struct hks_storage_key_info *key_info,
    uint32_t *sealing_alg,
    struct hks_blob *nonce,
    struct hks_blob *key)
{
    int32_t status = hks_get_sealing_info(sealing_alg);

    if (status != HKS_STATUS_OK)
        return HKS_ERROR_READ_FILE_FAIL;

    status = hks_gen_random(nonce->data, nonce->size);
    hks_if_status_error_return(status);

    if (key_info->param->key_type == HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519)
        *key = *(key_info->public_key);
    else if (key_info->param->key_type == HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519)
        *key = *(key_info->private_key);
    else
        return HKS_ERROR_INVALID_ARGUMENT;

    return HKS_STATUS_OK;
}

static int32_t hks_serialize_key_info(uint8_t *buf,
    const struct hks_blob *key_alias,
    const struct hks_storage_key_info *key_info)
{
    uint32_t n = 0;
    uint32_t sealing_alg = HKS_SEALING_DEFAULT;
    struct hks_blob key;
    struct hks_blob nonce_blob = HKS_BLOB_DEFAULT_VALUE;
    struct hks_blob cipher_text = HKS_BLOB_DEFAULT_VALUE;

    if (key_info->param == NULL)
        return HKS_ERROR_NULL_POINTER;

    if ((key_info->param->key_type != HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519) &&
        (key_info->param->key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519))
        return HKS_ERROR_INVALID_ARGUMENT;

    /* Prepare */
    int32_t status = hks_blob_init(&nonce_blob, sizeof(uint8_t), HKS_SEALING_NONCE_SIZE, HKS_BLOB_TYPE_RAW);

    hks_if_status_error_return(status);

    status = hks_prepare_serialize_key_info(key_info, &sealing_alg, &nonce_blob, &key);
    hks_if_status_error_goto_error(status, exit);

    /* Write flags */
    if (key_info->param->key_type == HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519)
        n += hks_blob_write_uint8((buf + n), HKS_SLOT_PUBLIC_KEY_OCCUPY);
    else
        n += hks_blob_write_uint8((buf + n), HKS_SLOT_KEYPAIR_OCCUPY);

    /* Write nonce */
    status = hks_blob_write_buf((buf + n), (hks_get_key_slot_len() - n), nonce_blob.data, nonce_blob.size, &n);
    hks_if_status_error_goto_error(status, exit);

    /* Write key info */
    status = hks_serialize_fill_buf(buf, key_alias, key.size, key_info, &n);
    hks_if_status_error_goto_error(status, exit);

    /* Encrypt key, AAD is now the buf itself */
    struct hks_blob buf_blob = { HKS_BLOB_TYPE_RAW, buf, n };

    status = hks_blob_init(&cipher_text, sizeof(uint8_t), (key.size + HKS_SEALING_TAG_SIZE), HKS_BLOB_TYPE_KEY);
    hks_if_status_error_goto_error(status, exit);

    status = hks_storage_encrypt_key_blob(&cipher_text, sealing_alg, &key, &nonce_blob, &buf_blob);
    if (status == HKS_STATUS_OK) {
        status = hks_blob_write_buf((buf + n), (hks_get_key_slot_len() - n), cipher_text.data, cipher_text.size, &n);
        hks_if_status_error_goto_error(status, exit);
    }

exit:
    hks_blob_destroy(&nonce_blob);
    hks_blob_destroy(&cipher_text);

    return status;
}

static int32_t hks_refresh_header_hash(void)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint8_t hash512[HKS_HEADER_HASH_SIZE] = {0};
    uint16_t size = hks_get_header_len() - HKS_HEADER_HASH_SIZE;
    int32_t status = hks_calc_hash_sha512(hash512, size);

    if (status != HKS_STATUS_OK)
        return status;

    uint32_t n = 0;

    status = hks_blob_write_buf((buffer + size), (hks_get_header_len() - size), hash512, HKS_HEADER_HASH_SIZE, &n);
    if (status != HKS_STATUS_OK)
        return status;

    return HKS_STATUS_OK;
}

static int32_t hks_sync_buf_to_file(void)
{
    uint8_t *buffer = hks_get_buffer();

    if (buffer == NULL)
        return HKS_ERROR_NULL_POINTER;

    uint32_t offset = hks_get_store_file_offset();

    if (offset >= HKS_BUF_BYTES)
        return HKS_ERROR_INTERNAL_UNKOWN;

    return hks_file_write(HKS_KEY_STORE_FILE_NAME, offset,
        buffer, HKS_BUF_BYTES - offset);
}

/*
 * Encrypt and seal key
 * Key_info into file according to format:
 *     key_info = header|keyslot1|keyslot2|
 *     header = version(2 bytes) | key_count(1 bytes)
 *             | slot_count(1 bytes)
 *             | sealing_alg(4 bytes) | sealing_nonce(16 bytes) | hash(64 bytes)
 *     keyslot = falgs(1 bytes) | sealing_nonce(16 bytes) | alias_size(1 bytes)
 *               | alias(alias_size bytes) | param | key_size(1 bytes)
 *               | key(key_size bytes)
 *     param = key_type(4 bytes) | key_len(2 bytes) | usage(4 bytes)
 *     | mode(4 bytes)
 *     | padding(1 bytes) | key_role(4 bytes) | domain(2 bytes)
 *     | auth_id_type(1 bytes)
 *     | auth_id_size(1 bytes) | auth_id_data( auth_id_size bytes)
 */
int32_t hks_storage_write_key_info(const struct hks_blob *key_alias,
    const struct hks_storage_key_info *key_info)
{
    if ((key_alias == NULL) || (key_info == NULL))
        return HKS_ERROR_NULL_POINTER;
    int32_t status = hks_write_key_info_check(key_alias, key_info);

    hks_check_return_code(status, &status);
    hks_if_status_error_return(status);
    uint16_t size = hks_get_key_slot_len();
    uint8_t *buf = (uint8_t *)HKS_CALLOC(sizeof(uint8_t), size);

    if (buf == NULL)
        return HKS_ERROR_MALLOC_FAIL;

    if (memset_s(buf, size, 0, size) != EOK) {
        status = HKS_ERROR_BAD_STATE;
        goto exit;
    }
    status = hks_serialize_key_info(buf, key_alias, key_info);
    if (status != HKS_STATUS_OK)
        goto exit;

    uint8_t *key_pos = NULL;

    status = hks_get_key_pos(key_alias, &key_pos);
    if (status != HKS_STATUS_OK)
        goto exit;
    if (key_pos != NULL) {
        uint16_t len = hks_get_key_slot_len();

        if (memset_s(key_pos, len, 0, len) != EOK) {
            status = HKS_ERROR_BAD_STATE;
            goto exit;
        }
        if (memcpy_s(key_pos, len, buf, len) != EOK) {
            status = HKS_ERROR_BAD_STATE;
            goto exit;
        }
    } else {
        status = hks_slot_add_key(buf, hks_get_key_slot_len());
        if (status != HKS_STATUS_OK)
            goto exit;
    }
    status = hks_refresh_header_hash();
    if (status != HKS_STATUS_OK)
        goto exit;
    status = hks_sync_buf_to_file();
exit:
    /* clear buffer after use before free. Don't remove! */
    (void)memset_s(buf, size, 0, size);
    hks_free_ptr(buf);
    return status;
}

static int32_t hks_write_key_info_check(const struct hks_blob *key_alias,
    const struct hks_storage_key_info *key_info)
{
    if (key_alias->data == NULL)
        return HKS_ERROR_NULL_POINTER;

    if ((key_alias->size > HKS_ALIAS_MAX_SIZE) || (key_alias->size <= 0))
        return HKS_ERROR_INVALID_ARGUMENT;

    if (key_info->param->key_type ==
        HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519) {
        if ((key_info->public_key == NULL) ||
            (key_info->public_key->data == NULL) ||
            (key_info->public_key->size != CRYPTO_PUBLIC_KEY_BYTES))
            return HKS_ERROR_INVALID_ARGUMENT;
    } else if (key_info->param->key_type ==
        HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519) {
        if ((key_info->private_key == NULL) ||
            (key_info->private_key->data == NULL) ||
            (key_info->private_key->size != CRYPTO_SECRET_KEY_BYTES))
            return HKS_ERROR_INVALID_ARGUMENT;
    } else {
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    if (key_info->param->key_auth_id.type != HKS_BLOB_TYPE_AUTH_ID)
        return HKS_ERROR_INVALID_ARGUMENT;

    if ((key_info->param->key_auth_id.size <= 0) ||
        (key_info->param->key_auth_id.size > HKS_AUTH_ID_MAX_SIZE))
        return HKS_ERROR_INVALID_ARGUMENT;

    if (key_info->param->key_auth_id.data == NULL)
        return HKS_ERROR_NULL_POINTER;

    return HKS_STATUS_OK;
}

static int32_t hks_unserialize_key_info(uint8_t *key_pos,
    struct hks_key_param *param, uint8_t *key_size,
    uint8_t *nonce, uint32_t *shift)
{
    uint32_t n = 0;
    uint8_t flags = 0;
    uint8_t alias_size = 0;
    uint16_t key_len = 0;
    uint8_t key_pad = 0;
    uint8_t key_auth_id_size = 0;
    uint8_t k_size = 0;

    n += hks_blob_read_uint8(&(flags), (key_pos + n));
    if (hks_blob_write_buf(nonce, HKS_SEALING_NONCE_SIZE, (key_pos + n),
        HKS_SEALING_NONCE_SIZE, &n) != HKS_STATUS_OK)
        return HKS_ERROR_INVALID_KEY_INFO;
    n += hks_blob_read_uint8(&(alias_size), (key_pos + n));
    if (alias_size > HKS_ALIAS_MAX_SIZE)
        return HKS_ERROR_INVALID_KEY_INFO;

    n += alias_size; /* offset + key_alias_size */
    n += hks_blob_read_uint32(&(param->key_type), (key_pos + n));
    n += hks_blob_read_uint16(&key_len, (key_pos + n));
    param->key_len = key_len;

    n += hks_blob_read_uint32(&(param->key_usage), (key_pos + n));
    n += hks_blob_read_uint8(&key_pad, (key_pos + n));
    param->key_pad = key_pad;

    n += hks_blob_read_uint32(&(param->key_mode), (key_pos + n));
    n += hks_blob_read_uint32(&(param->key_role), (key_pos + n));
    n += hks_blob_read_uint16(&(param->key_domain), (key_pos + n));
    n += hks_blob_read_uint8(&(param->key_auth_id.type), (key_pos + n));

    n += hks_blob_read_uint8(&key_auth_id_size, (key_pos + n));
    param->key_auth_id.size = key_auth_id_size;
    if (param->key_auth_id.size > HKS_AUTH_ID_MAX_SIZE)
        return HKS_ERROR_INVALID_KEY_INFO;

    if (hks_blob_write_buf(param->key_auth_id.data, HKS_AUTH_ID_MAX_SIZE, (key_pos + n),
        param->key_auth_id.size, &n) != HKS_STATUS_OK)
        return HKS_ERROR_INVALID_KEY_INFO;
    n += hks_blob_read_uint8(&(k_size), (key_pos + n));

    *key_size = k_size;
    *shift = n;
    return HKS_STATUS_OK;
}

int32_t hks_fill_key_info(const struct hks_key_param *param,
    const struct hks_blob *plain_text,
    struct hks_storage_key_info *key_info)
{
    hks_if_true_return_error(((param == NULL) || (plain_text == NULL) || (key_info == NULL)), HKS_ERROR_NULL_POINTER);

    int32_t status = HKS_STATUS_OK;
    uint32_t n = 0;

    /* 1.fill param */
    if (key_info->param != NULL)
        status = hks_cpy_key_param(key_info->param, param);

    /* 2.fill private key */
    if (key_info->private_key != NULL) {
        if (param->key_type == HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519) {
            status = hks_blob_write_buf(key_info->private_key->data, key_info->private_key->size, plain_text->data,
                CRYPTO_SECRET_KEY_BYTES, &n);
            hks_if_status_error_return(status);

            key_info->private_key->size = CRYPTO_SECRET_KEY_BYTES;
        } else {
            key_info->private_key->size = 0;
        }
    }

    /* 3.fill public key */
    if (key_info->public_key != NULL) {
        if (param->key_type == HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519) {
            status = hks_blob_write_buf(key_info->public_key->data, key_info->public_key->size, plain_text->data,
                CRYPTO_PUBLIC_KEY_BYTES, &n);
            hks_if_status_error_return(status);

            key_info->public_key->size = CRYPTO_PUBLIC_KEY_BYTES;
        } else if (param->key_type == HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519) {
            status = hks_blob_write_buf(key_info->public_key->data, key_info->public_key->size,
                (plain_text->data + CRYPTO_SECRET_KEY_BYTES - CRYPTO_PUBLIC_KEY_BYTES), CRYPTO_PUBLIC_KEY_BYTES, &n);
            hks_if_status_error_return(status);

            key_info->public_key->size = CRYPTO_PUBLIC_KEY_BYTES;
        } else {
            key_info->public_key->size = 0;
        }
    }
    return status;
}

static int32_t hks_get_key_info_init(const struct hks_blob *key_alias,
    struct hks_key_param *key_param, uint8_t **key_pos)
{
    if (memset_s(key_param, sizeof(*key_param), 0, sizeof(*key_param)) != EOK)
        return HKS_ERROR_BAD_STATE;
    key_param->key_auth_id.data = (uint8_t *)HKS_CALLOC(sizeof(uint8_t),
        HKS_AUTH_ID_MAX_SIZE);
    if (key_param->key_auth_id.data == NULL)
        return HKS_ERROR_MALLOC_FAIL;
    int32_t status = hks_get_key_pos(key_alias, key_pos);

    if ((status != HKS_STATUS_OK) || (key_pos == NULL)) {
        hks_key_param_destroy(key_param);
        return HKS_ERROR_KEY_NOT_EXIST;
    }
    if (*key_pos == NULL) {
        hks_key_param_destroy(key_param);
        return HKS_ERROR_KEY_NOT_EXIST;
    }
    return status;
}

static int32_t hks_check_key_info(const struct hks_storage_key_info *key_info)
{
    if ((key_info->public_key == NULL) &&
        (key_info->private_key == NULL) &&
        (key_info->param == NULL))
        return HKS_ERROR_NULL_POINTER;

    if ((key_info->private_key != NULL) &&
        ((key_info->private_key->data == NULL) || (key_info->private_key->size < CRYPTO_SECRET_KEY_BYTES)))
            return HKS_ERROR_BUFFER_TOO_SMALL;

    if ((key_info->public_key != NULL) &&
        ((key_info->public_key->data == NULL) || (key_info->public_key->size < CRYPTO_PUBLIC_KEY_BYTES)))
            return HKS_ERROR_BUFFER_TOO_SMALL;

    return HKS_STATUS_OK;
}

#ifdef _SECURE_ENVIREMENT_NMI_
int32_t hks_prepare_encrypt_material(const struct hks_blob *key_alias,
    struct hks_encrypt_material *encrypt_material)
{
    hks_if_true_return_error(((encrypt_material == NULL) || (key_alias == NULL) ||
        (encrypt_material->key_info == NULL) || (encrypt_material->key_info->param == NULL)), HKS_ERROR_NULL_POINTER);

    uint8_t *key_pos = NULL;
    int32_t status = hks_check_key_info(encrypt_material->key_info);

    hks_if_status_error_return(status);

    encrypt_material->key_info->param->key_auth_id.size = HKS_AUTH_ID_MAX_SIZE;
    status = hks_get_key_info_init(key_alias, encrypt_material->key_info->param, &key_pos);
    hks_if_status_error_return(status);

    encrypt_material->sealing_alg = HKS_SEALING_DEFAULT;
    status = hks_get_sealing_info(&encrypt_material->sealing_alg);
    if (status != HKS_STATUS_OK)
        return HKS_ERROR_READ_FILE_FAIL;

    uint32_t shift = 0;
    uint8_t key_size = 0;
    uint32_t n = 0;
    uint8_t nonce[HKS_SEALING_NONCE_SIZE] = {0};

    status = hks_unserialize_key_info(key_pos, encrypt_material->key_info->param, &key_size, nonce, &shift);
    hks_if_status_error_return(status);
    if (((encrypt_material->key_info->param->key_type != HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519) &&
        (encrypt_material->key_info->param->key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519)) ||
        (key_size > HKS_KEY_PAIR_CIPHER_ED25519) || (key_size < HKS_SEALING_TAG_SIZE)) {
        status = HKS_ERROR_INVALID_KEY_INFO;
        return status;
    }

    /* 1. prepare the cipher_text and plantext */
    status = hks_blob_init(encrypt_material->plain_text, sizeof(uint8_t), CRYPTO_SECRET_KEY_BYTES, HKS_BLOB_TYPE_KEY);
    hks_if_status_error_return(status);
    status = hks_blob_init(encrypt_material->cipher_text, sizeof(uint8_t), key_size, HKS_BLOB_TYPE_KEY);
    hks_if_status_error_return(status);
    status = hks_blob_write_buf(encrypt_material->cipher_text->data, key_size, (key_pos + shift), key_size, &n);
    hks_if_status_error_return(status);

    /* 2. decrypt key. AAD is (buf) */
    status = hks_blob_init(encrypt_material->nonce_blob, sizeof(uint8_t), HKS_SEALING_NONCE_SIZE, HKS_BLOB_TYPE_RAW);
    hks_if_status_error_return(status);
    status = hks_blob_write_buf(encrypt_material->nonce_blob->data, HKS_SEALING_NONCE_SIZE, nonce,
        HKS_SEALING_NONCE_SIZE, &n);
    hks_if_status_error_return(status);

    status = hks_blob_init(encrypt_material->aad_blob, sizeof(uint8_t), shift, HKS_BLOB_TYPE_RAW);
    hks_if_status_error_return(status);
    status = hks_blob_write_buf(encrypt_material->aad_blob->data, shift, key_pos, shift, &n);
    hks_if_status_error_return(status);

    return status;
}

static int32_t hks_prepare_serialize_key_info_nmi(
    const struct hks_storage_key_info *key_info,
    uint32_t *sealing_alg,
    struct hks_blob *nonce,
    struct hks_blob *key)
{
    int32_t status = hks_get_sealing_info(sealing_alg);

    if (status != HKS_STATUS_OK)
        return HKS_ERROR_READ_FILE_FAIL;

    status = hks_gen_random(nonce->data, nonce->size);
    hks_if_status_error_return(status);

    if (key_info->param->key_type == HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519) {
        status = hks_blob_init(key, sizeof(uint8_t), key_info->public_key->size, key_info->public_key->type);
        hks_if_status_error_return(status);

        if (memcpy_s(key->data, key->size, key_info->public_key->data, key_info->public_key->size) != EOK)
            return HKS_ERROR_BAD_STATE;
    } else if (key_info->param->key_type == HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519) {
        status = hks_blob_init(key, sizeof(uint8_t), key_info->private_key->size, key_info->private_key->type);
        hks_if_status_error_return(status);

        if (memcpy_s(key->data, key->size, key_info->private_key->data, key_info->private_key->size) != EOK)
            return HKS_ERROR_BAD_STATE;
    } else {
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    return HKS_STATUS_OK;
}

static int32_t hks_nmi_serialize_key_info(const struct hks_blob *key_alias,
    struct hks_storage_buffer *key_buffer, struct hks_encrypt_material *key_material)
{
    int32_t status;
    struct hks_blob *plain_text = key_material->plain_text;
    struct hks_blob *nonce_blob = key_material->nonce_blob;
    struct hks_blob *aad_blob = key_material->aad_blob;
    struct hks_blob *cipher_text = key_material->cipher_text;
    struct hks_storage_key_info *key_info = key_material->key_info;

    key_buffer->offset = 0;
    key_material->sealing_alg = HKS_SEALING_DEFAULT;

    if (key_info->param == NULL)
        return HKS_ERROR_NULL_POINTER;

    if ((key_info->param->key_type != HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519) &&
        (key_info->param->key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519))
        return HKS_ERROR_INVALID_ARGUMENT;

    /* Prepare */
    status = hks_blob_init(nonce_blob, sizeof(uint8_t), HKS_SEALING_NONCE_SIZE, HKS_BLOB_TYPE_RAW);
    hks_if_status_error_return(status);

    status = hks_prepare_serialize_key_info_nmi(key_info, &key_material->sealing_alg,
        nonce_blob, plain_text);
    hks_if_status_error_return(status);

    /* Write flags */
    if (key_info->param->key_type == HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519)
        key_buffer->offset += hks_blob_write_uint8((key_buffer->buf + key_buffer->offset), HKS_SLOT_PUBLIC_KEY_OCCUPY);
    else
        key_buffer->offset += hks_blob_write_uint8((key_buffer->buf + key_buffer->offset), HKS_SLOT_KEYPAIR_OCCUPY);

    /* Write nonce */
    status = hks_blob_write_buf((key_buffer->buf + key_buffer->offset),
        (hks_get_key_slot_len() - key_buffer->offset), nonce_blob->data, nonce_blob->size, &key_buffer->offset);
    hks_if_status_error_return(status);

    /* Write key info */
    status = hks_serialize_fill_buf(key_buffer->buf, key_alias, plain_text->size, key_info, &key_buffer->offset);
    hks_if_status_error_return(status);

    status = hks_blob_init(cipher_text, sizeof(uint8_t), (plain_text->size + HKS_SEALING_TAG_SIZE), HKS_BLOB_TYPE_KEY);
    hks_if_status_error_return(status);

    status = hks_blob_init(aad_blob, sizeof(uint8_t), key_buffer->offset, HKS_BLOB_TYPE_RAW);
    hks_if_status_error_return(status);

    if (memcpy_s(aad_blob->data, key_buffer->offset, key_buffer->buf, key_buffer->offset) != EOK)
        status = HKS_ERROR_BAD_STATE;

    return status;
}

int32_t hks_prepare_for_encrypt_key(const struct hks_blob *key_alias,
    struct hks_encrypt_material *key_material, struct hks_storage_buffer *key_buffer)
{
    hks_if_true_return_error(((key_alias == NULL) || (key_material == NULL) || (key_buffer == NULL) ||
        (key_material->key_info == NULL)), HKS_ERROR_NULL_POINTER);

    int32_t status = hks_write_key_info_check(key_alias, key_material->key_info);
    hks_if_status_error_return(status);

    uint16_t size = hks_get_key_slot_len();
    uint8_t *buf = (uint8_t *)HKS_CALLOC(sizeof(uint8_t), size);

    if (buf == NULL)
        return HKS_ERROR_MALLOC_FAIL;
    key_buffer->size = size;

    if (memset_s(buf, size, 0, size) != EOK) {
        hks_free_ptr(buf);
        return HKS_ERROR_BAD_STATE;
    }
    key_buffer->buf = buf;
    status = hks_nmi_serialize_key_info(key_alias, key_buffer, key_material);

    return status;
}

int32_t hks_nmi_write_key_info(const struct hks_blob *key_alias,
    struct hks_encrypt_material *key_material, struct hks_storage_buffer *key_buffer)
{
    hks_if_true_return_error(((key_alias == NULL) || (key_material == NULL) || (key_buffer == NULL) ||
        (key_material->key_info == NULL) || (key_buffer->buf == NULL)), HKS_ERROR_NULL_POINTER);

    int32_t status;
    struct hks_storage_key_info *key_info = key_material->key_info;
    uint8_t *buf = key_buffer->buf;

    if (hks_is_key_can_store(key_alias,
        HKS_LOCAL_STORAGE_KEY_MAX_NUM) != HKS_BOOL_TRUE)
        return HKS_ERROR_INSUFFICIENT_STORAGE;

    if (key_alias == NULL)
        return HKS_ERROR_NULL_POINTER;
    if (key_alias->type != HKS_BLOB_TYPE_ALIAS)
        return HKS_STATUS_OK;

    status = hks_write_key_info_check(key_alias, key_info);

    hks_check_return_code(status, &status);
    hks_if_status_error_return(status);

    status = hks_blob_write_buf((buf + key_buffer->offset), (hks_get_key_slot_len() - key_buffer->offset),
        key_material->cipher_text->data, key_material->cipher_text->size, &key_buffer->offset);
    hks_if_status_error_return(status);

    uint8_t *key_pos = NULL;
    status = hks_get_key_pos(key_alias, &key_pos);
    hks_if_status_error_return(status);

    if (key_pos != NULL) {
        uint16_t len = hks_get_key_slot_len();
        if (memcpy_s(key_pos, len, buf, len) != EOK)
            return HKS_ERROR_BAD_STATE;
    } else {
        status = hks_slot_add_key(buf, hks_get_key_slot_len());
        hks_if_status_error_return(status);
    }

    status = hks_refresh_header_hash();
    hks_if_status_error_return(status);
    status = hks_sync_buf_to_file();

    return status;
}

static int32_t hks_stroage_get_key_param(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info)
{
    struct hks_key_param param = {0};
    uint8_t *key_pos = NULL;
    int32_t status = hks_get_key_info_init(key_alias, &param, &key_pos);
    hks_if_status_error_return(status);

    uint32_t shift = 0;
    uint8_t key_size = 0;
    struct hks_blob plain_text  = HKS_BLOB_DEFAULT_VALUE;
    uint8_t nonce[HKS_SEALING_NONCE_SIZE] = {0};

    status = hks_unserialize_key_info(key_pos, &param, &key_size, nonce, &shift);
    hks_if_status_error_goto_error(status, exit);
    if (((param.key_type != HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519) &&
        (param.key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519)) ||
        (key_size > HKS_KEY_PAIR_CIPHER_ED25519) || (key_size < HKS_SEALING_TAG_SIZE)) {
        status = HKS_ERROR_INVALID_KEY_INFO;
        goto exit;
    }
    status = hks_fill_key_info(&param, &plain_text, key_info);

exit:
    hks_key_param_destroy(&param);
    return status;
}

int32_t hks_storage_read_key_param(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info)
{
    if ((key_alias == NULL) || (key_info == NULL))
        return HKS_ERROR_NULL_POINTER;

    int32_t status = hks_check_key_info(key_info);

    if (status != HKS_STATUS_OK)
        return status;

    return hks_stroage_get_key_param(key_alias, key_info);
}
#endif

static int32_t hks_get_plain_text(uint8_t *key_pos, struct hks_blob *plain_text,
    struct hks_key_param *param, uint32_t sealing_alg)
{
    uint32_t shift = 0;
    uint8_t key_size = 0;
    struct hks_blob cipher_text = HKS_BLOB_DEFAULT_VALUE;
    uint8_t nonce[HKS_SEALING_NONCE_SIZE] = {0};

    int32_t status = hks_unserialize_key_info(key_pos, param, &key_size, nonce, &shift);

    hks_if_status_error_return(status);
    if (((param->key_type != HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519) &&
        (param->key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519)) ||
        (key_size > HKS_KEY_PAIR_CIPHER_ED25519) ||
        (key_size < HKS_SEALING_TAG_SIZE))
        return HKS_ERROR_INVALID_KEY_INFO;

    /* 1. prepare the nonce and AAD (aad is buf) */
    struct hks_blob nonce_blob = { HKS_BLOB_TYPE_RAW, nonce, HKS_SEALING_NONCE_SIZE };
    struct hks_blob buf_blob = { HKS_BLOB_TYPE_RAW, key_pos, shift };

    /* 2. prepare the cipher_text */
    status = hks_blob_init(&cipher_text, sizeof(uint8_t), key_size, HKS_BLOB_TYPE_KEY);
    hks_if_status_error_goto_error(status, exit);

    /* use shift as offset value temporarily */
    status = hks_blob_write_buf(cipher_text.data, key_size, (key_pos + shift), key_size, &shift);
    hks_if_status_error_goto_error(status, exit);

    /* 3. decrypt key. */
    status = hks_storage_decrypt_key_blob(plain_text, sealing_alg, &cipher_text, &nonce_blob, &buf_blob);

exit:
    hks_blob_destroy(&cipher_text);
    return status;
}

static int32_t hks_get_key_info(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info)
{
    struct hks_key_param param;

    (void)memset_s(&param, sizeof(param), 0, sizeof(param));

    uint8_t *key_pos = NULL;
    int32_t status = hks_get_key_info_init(key_alias, &param, &key_pos);

    hks_if_status_error_return(status);

    uint32_t sealing_alg = HKS_SEALING_DEFAULT;

    status = hks_get_sealing_info(&sealing_alg);
    if (status != HKS_STATUS_OK) {
        status = HKS_ERROR_READ_FILE_FAIL;
        hks_key_param_destroy(&param);
        return status;
    }

    struct hks_blob plain_text  = HKS_BLOB_DEFAULT_VALUE;

    status = hks_blob_init(&plain_text, sizeof(uint8_t), CRYPTO_SECRET_KEY_BYTES, HKS_BLOB_TYPE_KEY);
    hks_if_status_error_goto_error(status, exit);

    status = hks_get_plain_text(key_pos, &plain_text, &param, sealing_alg);
    if (status == HKS_STATUS_OK)
        status = hks_fill_key_info(&param, &plain_text, key_info);
exit:
    hks_blob_destroy(&plain_text);
    hks_key_param_destroy(&param);
    return status;
}

int32_t hks_storage_read_key_info(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info)
{
    if ((key_alias == NULL) || (key_info == NULL))
        return HKS_ERROR_NULL_POINTER;

    int32_t status = hks_check_key_info(key_info);

    if (status != HKS_STATUS_OK)
        return status;

    return hks_get_key_info(key_alias, key_info);
}

int32_t hks_storage_remove_key_info(const struct hks_blob *key_alias)
{
    if (key_alias == NULL)
        return HKS_ERROR_NULL_POINTER;

    if ((key_alias->size > HKS_ALIAS_MAX_SIZE) || (key_alias->data == NULL))
        return HKS_ERROR_INVALID_ARGUMENT;

    uint8_t *key_pos = NULL;
    int32_t status = hks_get_key_pos(key_alias, &key_pos);

    if (status != HKS_STATUS_OK)
        return status;

    if (key_pos == NULL)
        return HKS_ERROR_KEY_NOT_EXIST;

    if (memset_s(key_pos, hks_get_key_slot_len(), 0,
        hks_get_key_slot_len()) != EOK)
        return HKS_ERROR_BAD_STATE;

    status = hks_reduce_key_count();
    if (status != HKS_STATUS_OK)
        return status;

    status = hks_refresh_header_hash();
    if (status != HKS_STATUS_OK)
        return status;

    status = hks_sync_buf_to_file();

    return status;
}

int32_t hks_storage_get_key_size(const struct hks_blob *key_alias,
    uint32_t *size)
{
    if (key_alias == NULL)
        return HKS_ERROR_NULL_POINTER;

    return hks_file_size(HKS_KEY_STORE_FILE_NAME, size);
}

int32_t hks_get_key_alias_list(struct hks_blob *key_alias_list,
    uint32_t *list_count)
{
    uint8_t *buffer = hks_get_buffer();

    if ((buffer == NULL) || (key_alias_list == NULL) ||
        (list_count == NULL))
        return HKS_ERROR_NULL_POINTER;

    uint8_t slot_count_loop = hks_get_slot_count_loop();
    uint8_t *tmp = buffer + hks_get_header_len();
    uint16_t slot_shift = hks_get_key_slot_len();
    uint8_t flags = 0;
    uint8_t alias_size = 0;
    uint32_t num = 0;

    for (uint8_t j = 0; j < slot_count_loop; j++) {
        hks_blob_read_uint8(&flags, tmp);
        if (flags == HKS_SLOT_PUBLIC_KEY_OCCUPY) {
            uint32_t alias_size_shift = sizeof(uint8_t) + HKS_SEALING_NONCE_SIZE;

            hks_blob_read_uint8(&alias_size, (tmp + alias_size_shift));
            uint32_t alias_shift = alias_size_shift + sizeof(uint8_t);

            if (num >= (*list_count))
                return HKS_ERROR_BUFFER_TOO_SMALL;

            if (key_alias_list[num].size < alias_size)
                return HKS_ERROR_BUFFER_TOO_SMALL;

            if (memcpy_s(key_alias_list[num].data, key_alias_list[num].size,
                tmp + alias_shift, alias_size) != EOK)
                return HKS_ERROR_BAD_STATE;

            key_alias_list[num].size = alias_size;
            ++num;
        }
        tmp += slot_shift;
    }
    *list_count = num;
    return HKS_STATUS_OK;
}

/*
 * get the offset of storage file
 * parameter: none
 * return value:
 *     the offset of storage file
 */
#if defined(_HILINK_PRODUCT_)
uint32_t hks_get_store_file_offset(void)
{
    /* The data of root key should be skipped in hilink product. */
    return HKS_RKC_KSF_BUF_LEN;
}
#else
uint32_t hks_get_store_file_offset(void)
{
    return HKS_FILE_OFFSET_BASE;
}
#endif

/*
 * destroy storage
 * parameter: none
 * return value: none
 */
void hks_storage_destroy(void)
{
    hks_clean_buffer();

    int32_t status = hks_sync_buf_to_file();

    log_info("clean key store, status=%d", status);
    (void)status; /* hilink compile will replace log with {} */
    hks_free_ptr(g_storage_image_buffer);
}
