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

#ifndef HKS_STORAGE_H
#define HKS_STORAGE_H

#include "hks_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HKS_KEY_INFO_RESERVE_NUMBER 2

#if defined(_HILINK_PRODUCT_)
#define HKS_LOCAL_STORAGE_KEY_MAX_NUM            15
#define HKS_BUF_BYTES                            4096
#else
#define HKS_LOCAL_STORAGE_KEY_MAX_NUM            20
#define HKS_BUF_BYTES                            5120
#endif

struct hks_storage_key_info {
    struct hks_key_param *param;
    struct hks_blob *public_key;
    struct hks_blob *private_key;
    uint32_t reserve[HKS_KEY_INFO_RESERVE_NUMBER];
};

struct hks_storage_buffer {
    uint32_t offset; /* record current buf offset */
    uint8_t *buf;
    uint16_t size;
};

int32_t hks_load_file_to_buffer(const char *file_name,
    int32_t *is_key_info_exist);

int32_t hks_storage_clean_key_info(void);

int32_t hks_storage_write_key_info(const struct hks_blob *key_alias,
    const struct hks_storage_key_info *key_info);

int32_t hks_storage_read_key_info(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info);

int32_t hks_storage_remove_key_info(const struct hks_blob *key_alias);

int32_t hks_storage_get_key_size(const struct hks_blob *key_alias,
    uint32_t *size);

int hks_is_key_can_store(const struct hks_blob *key_alias, uint32_t max_num);

int32_t hks_get_key_alias_list(struct hks_blob *key_alias_list,
    uint32_t *list_count);

int hks_is_key_exist_in_store(const struct hks_blob *key_alias);

int32_t hks_storage_encrypt_key_blob(struct hks_blob *cipher_text,
    uint32_t sealing_alg, const struct hks_blob *key,
    const struct hks_blob *nonce, const struct hks_blob *aad);
int32_t hks_storage_decrypt_key_blob(struct hks_blob *plain_text,
    uint32_t sealing_alg, const struct hks_blob *cipher_text,
    const struct hks_blob *nonce, const struct hks_blob *aad);
int32_t hks_fill_key_info(const struct hks_key_param *param,
    const struct hks_blob *plain_text,
    struct hks_storage_key_info *key_info);

/*
 * get the offset of storage file
 * parameter: none
 * return value:
 *     the offset of storage file
 */
uint32_t hks_get_store_file_offset(void);

/*
 * destroy storage resources
 */
void hks_storage_destroy(void);
#ifdef _SECURE_ENVIREMENT_NMI_
int32_t hks_nmi_write_key_info(const struct hks_blob *key_alias,
    struct hks_encrypt_material *key_material, struct hks_storage_buffer *key_buffer);
int32_t hks_prepare_encrypt_material(const struct hks_blob *key_alias,
    struct hks_encrypt_material *encrypt_material);
int32_t hks_prepare_for_encrypt_key(const struct hks_blob *key_alias,
    struct hks_encrypt_material *key_material, struct hks_storage_buffer *key_buffer);
int32_t hks_storage_read_key_param(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info);
#endif

#ifdef __cplusplus
}
#endif
#endif /* HKS_STORAGE_H */
