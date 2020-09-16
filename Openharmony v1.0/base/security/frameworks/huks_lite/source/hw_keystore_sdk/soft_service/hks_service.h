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

#ifndef HKS_SERVICE_H
#define HKS_SERVICE_H

#include <stdint.h>
#include <stdlib.h>

#include "common/hks_common.h"
#include "hks_file.h"
#include "hks_storage.h"
#include "hks_types.h"

int32_t hks_service_generate_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param);

int32_t hks_service_generate_asymmetric_key(
    const struct hks_key_param *key_param, struct hks_blob *pri_key,
    struct hks_blob *pub_key);

int32_t hks_service_aead_encrypt_ex(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *plain_text,
    struct hks_blob *cipher_text_with_tag);

int32_t hks_service_aead_decrypt_ex(const struct hks_blob *key,
    const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param,
    const struct hks_blob *cipher_text_with_tag,
    struct hks_blob *plain_text);

int32_t hks_service_key_derivation(struct hks_blob *derived_key,
    const struct hks_blob *kdf_key, const struct hks_blob *salt,
    const struct hks_blob *label, const struct hks_key_param *key_params);

int32_t hks_service_key_agreement(struct hks_blob *agreed_key,
    const struct hks_key_param *private_key_param,
    const struct hks_blob *private_key,
    const struct hks_blob *peer_public_key,
    const uint32_t agreement_alg);

int32_t hks_service_get_random(struct hks_blob *random);

int32_t hks_service_hmac_ex(const struct hks_blob *key,
    uint32_t alg, const struct hks_blob *src_data,
    struct hks_blob *output);

int32_t hks_service_hash(uint32_t alg, const struct hks_blob *src_data,
    struct hks_blob *hash);

#ifdef _SECURE_ENVIREMENT_NMI_
int32_t hks_key_info_init_sign(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info);

int32_t hks_key_info_init_verify(const struct hks_blob *key_alias,
    struct hks_storage_key_info *key_info);

int32_t hks_key_info_init_generate(struct hks_storage_key_info *key_info);

int32_t hks_key_material_init_symmetric(struct hks_storage_key_info *key_info,
    struct hks_encrypt_material *key_material, const struct hks_key_param *key_param);

int32_t hks_init_get_encrypted_key_info(const struct hks_blob *key,
    const struct hks_key_param *key_param, struct hks_storage_key_info *key_info,
    struct hks_encrypt_material *key_material);

int32_t hks_service_generate_symmetric_key(struct hks_blob *output_key, struct hks_encrypt_material *key_material);

int32_t hks_service_symmetric_encrypt_decrypt(struct hks_encrypt_material *key_material,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *input_text, struct hks_blob *output_text,
    uint32_t operation_mode);

#endif

int32_t hks_service_asymmetric_sign(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *hash,
    struct hks_blob *signature);

int32_t hks_service_bn_exp_mod(struct hks_blob *x,
    const struct hks_blob *a, const struct hks_blob *e,
    const struct hks_blob *n);

int32_t hks_service_asymmetric_verify(const struct hks_blob *key_alias,
    const struct hks_blob *hash, const struct hks_blob *signature);

int32_t hks_service_import_public_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param, const struct hks_blob *key);

int32_t hks_service_export_public_key(const struct hks_blob *key_alias,
    struct hks_blob *key);

int32_t hks_service_delete_key(const struct hks_blob *key_alias);

int32_t hks_service_get_key_param(const struct hks_blob *key_alias,
    struct hks_key_param *key_param);

int32_t hks_service_is_key_exist(const struct hks_blob *key_alias);

int32_t hks_service_register_file_callbacks(
    struct hks_file_callbacks *callbacks);

int32_t hks_service_get_pub_key_alias_list(
    struct hks_blob *key_alias_list, uint32_t *list_count);

int32_t hks_service_key_info_init(void);

void hks_service_destroy(void);

int32_t hks_service_refresh_key_info(void);

int32_t hks_service_register_get_hardware_udid_callback(
    hks_get_hardware_udid_callback callback);

#endif /* HKS_SERVICE_H */

