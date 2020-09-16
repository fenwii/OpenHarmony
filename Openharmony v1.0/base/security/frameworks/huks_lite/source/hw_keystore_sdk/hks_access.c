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

#include "hks_access.h"
#include <stdio.h>
#include <string.h>
#include "securec.h"
#include "hks_errno.h"
#include "soft_service/hks_service.h"
#include "soft_service/hks_rkc.h"
#include "soft_service/hks_storage.h"
#include "common/hks_log_utils.h"
#include "common/hks_mem.h"

#ifdef _SECURE_ENVIREMENT_NMI_
uint32_t *g_sec_mod_ctrl = (uint32_t *)0x00022000;
uint8_t *g_sec_mod_data = (uint8_t *)0x00022004;
#define write_uint32(value, addr)               (*((volatile uint32_t *)(addr)) = (value))
#define NMI_REG_BASE_TRIGGER                    0x40010258
#endif /* _SECURE_ENVIREMENT_NMI_ */

#define SEC_MODE_DATA 0xe3
struct sec_mod_msg g_msg_box;

static void __hks_handle_secure_call(struct sec_mod_msg *msg_box);
void hks_enter_secure_mode(struct sec_mod_msg *msg)
{
    if (msg == NULL)
        return;

#ifdef _SECURE_ENVIREMENT_NMI_
    g_msg_box = *msg;
    log_info("%s: before NMI.\n", __func__);

    write_uint32(0x1, NMI_REG_BASE_TRIGGER); /* LOS_TriggerNMI, write 0x1 to reg 0x40010258 */
    log_info("%s: Entering NMI.\n", __func__);

    *msg = g_msg_box;
    log_info("%s: After NMI.\n", __func__);
#else
    __hks_handle_secure_call(msg);
#endif
}

#ifndef _SUPPORT_HKS_TEE_
int32_t hks_access_init(void)
{
    int32_t status = hks_service_key_info_init();

    hks_if_status_error_return(status);

    return status;
}

void hks_access_destroy(void)
{
    hks_service_destroy();
}

int32_t hks_access_refresh_key_info(void)
{
    int32_t status = hks_service_refresh_key_info();

    hks_if_status_error_return(status);

    return status;
}
#endif

int32_t hks_access_generate_key(const struct hks_blob *key_alias,
    const struct hks_key_param *key_param)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_generate_key_msg *msg = &msg_box.msg_data.generate_key_msg;

    msg_box.cmd_id = HKS_GENERATE_KEY;

#ifdef _SECURE_ENVIREMENT_NMI_
    if (key_param->key_type != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519)
        return HKS_ERROR_INVALID_ARGUMENT;

    struct hks_storage_key_info key_info;
    struct hks_encrypt_material key_material;
    struct hks_storage_buffer key_buffer = { 0, NULL, 0 };

    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));
    (void)memset_s(&key_material, sizeof(key_material), 0, sizeof(key_material));

    msg->key_material = &key_material;
    msg->key_alias = key_alias;
    msg->key_material->key_info = &key_info;
    msg->key_material->key_info->param = (struct hks_key_param *)key_param;

    int32_t status = hks_key_info_init_generate(&key_info);

    hks_if_status_error_goto_error(status, exit);
    status = hks_encrypt_material_init(&key_material);
    hks_if_status_error_goto_error(status, exit);
    status = hks_prepare_for_encrypt_key(key_alias, &key_material, &key_buffer);
    hks_if_status_error_goto_error(status, exit);

    hks_enter_secure_mode(&msg_box);
    status = msg_box.status;
    hks_if_status_error_goto_error(status, exit);
    status = hks_nmi_write_key_info(key_alias, &key_material, &key_buffer);
    hks_if_status_error_goto_error(status, exit);

exit:
    if (key_buffer.buf != NULL)
        (void)memset_s(key_buffer.buf, key_buffer.size, 0, key_buffer.size);
    hks_free_ptr(key_buffer.buf);
    hks_encrypt_material_destroy_free(&key_material);
    hks_blob_destroy(key_info.private_key);
    hks_blob_destroy(key_info.public_key);
    hks_free_ptr(key_info.private_key);
    hks_free_ptr(key_info.public_key);

    return status;
#else
    msg->key_alias = key_alias;
    msg->key_param = key_param;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
#endif
}

int32_t hks_access_generate_key_ex(const struct hks_key_param *key_param, struct hks_blob *priv_key,
    struct hks_blob *pub_key)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_generate_ex_msg *msg = &msg_box.msg_data.generate_ex_msg;

    msg_box.cmd_id = HKS_GENERATE_KEY_EX;
    msg->key_param = key_param;
    msg->priv_key = priv_key;
    msg->pub_key = pub_key;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

int32_t hks_access_sign(const struct hks_blob *key_alias, const struct hks_key_param *key_param,
    const struct hks_blob *hash, struct hks_blob *signature)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_sign_verify_msg *msg = &msg_box.msg_data.sign_verify_msg;

    msg_box.cmd_id = HKS_SIGN;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_storage_key_info key_info;
    struct hks_key_param param;
    struct hks_encrypt_material encrypt_material;

    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));
    (void)memset_s(&param, sizeof(param), 0, sizeof(param));
    (void)memset_s(&encrypt_material, sizeof(encrypt_material), 0, sizeof(encrypt_material));

    key_info.param = &param;
    int32_t res = hks_key_info_init_sign(key_alias, &key_info);

    hks_if_status_error_goto_error(res, exit);
    encrypt_material.key_info = &key_info;
    res = hks_encrypt_material_init(&encrypt_material);
    hks_if_status_error_goto_error(res, exit);
    res = hks_prepare_encrypt_material(key_alias, &encrypt_material);
    hks_if_status_error_goto_error(res, exit);

    msg->key = key_alias;
    msg->key_param = key_param;
    msg->message = hash;
    msg->signature = signature;
    msg->encrypt_material = &encrypt_material;
    hks_enter_secure_mode(&msg_box);
    res = msg_box.status;

exit:
    hks_blob_destroy(key_info.private_key);
    hks_free_ptr(key_info.private_key);
    hks_key_param_destroy(&param);
    hks_encrypt_material_destroy_free(&encrypt_material);

    return res;
#else
    msg->key = key_alias;
    msg->key_param = key_param;
    msg->message = hash;
    msg->signature = signature;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
#endif
}

int32_t hks_access_verify(const struct hks_blob *key_alias, const struct hks_blob *hash,
    const struct hks_blob *signature)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_sign_verify_msg *msg = &msg_box.msg_data.sign_verify_msg;

    msg_box.cmd_id = HKS_VERIFY;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_storage_key_info key_info;
    struct hks_key_param param;
    struct hks_encrypt_material encrypt_material;

    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));
    (void)memset_s(&param, sizeof(param), 0, sizeof(param));
    (void)memset_s(&encrypt_material, sizeof(encrypt_material), 0, sizeof(encrypt_material));

    key_info.param = &param;
    int32_t res = hks_key_info_init_verify(key_alias, &key_info);

    hks_if_status_error_goto_error(res, exit);
    encrypt_material.key_info = &key_info;
    if (key_alias->type == HKS_BLOB_TYPE_ALIAS) {
        res = hks_encrypt_material_init(&encrypt_material);
        hks_if_status_error_goto_error(res, exit);
        res = hks_prepare_encrypt_material(key_alias, &encrypt_material);
        hks_if_status_error_goto_error(res, exit);
    }

    msg->key = key_alias;
    msg->message = hash;
    msg->signature = (struct hks_blob *)signature;
    msg->encrypt_material = &encrypt_material;
    hks_enter_secure_mode(&msg_box);
    res = msg_box.status;

exit:
    if (key_alias->type == HKS_BLOB_TYPE_ALIAS)
        hks_blob_destroy(key_info.public_key);
    hks_free_ptr(key_info.public_key);
    hks_key_param_destroy(&param);
    hks_encrypt_material_destroy_free(&encrypt_material);

    return res;
#else
    msg->key = key_alias;
    msg->message = hash;
    msg->signature = (struct hks_blob *)signature;
    hks_enter_secure_mode(&msg_box);
    return msg_box.status;
#endif
}

int32_t hks_access_aead_encrypt(const struct hks_blob *key, const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *plain_text, struct hks_blob *cipher_text_with_tag)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_encrypt_decrypt_msg *msg = &msg_box.msg_data.encrypt_decrypt_msg;

    msg_box.cmd_id = HKS_ENCRYPT;
    msg->key = key;
    msg->key_param = key_param;
    msg->crypt_param = crypt_param;
    msg->plain_text = (struct hks_blob *)plain_text;
    msg->cipher_text_with_tag = cipher_text_with_tag;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

int32_t hks_access_aead_decrypt(const struct hks_blob *key, const struct hks_key_param *key_param,
    const struct hks_crypt_param *crypt_param, const struct hks_blob *cipher_text_with_tag, struct hks_blob *plain_text)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_encrypt_decrypt_msg *msg = &msg_box.msg_data.encrypt_decrypt_msg;

    msg_box.cmd_id = HKS_DECRYPT;
    msg->key = key;
    msg->key_param = key_param;
    msg->crypt_param = crypt_param;
    msg->plain_text = plain_text;
    msg->cipher_text_with_tag = (struct hks_blob *)cipher_text_with_tag;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

int32_t hks_access_import_key(const struct hks_blob *key_alias, const struct hks_key_param *key_param,
    const struct hks_blob *key)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_import_key_msg *msg = &msg_box.msg_data.import_key_msg;

    msg_box.cmd_id = HKS_IMPORT_KEY;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_storage_key_info key_info;
    struct hks_encrypt_material key_material;
    struct hks_blob public_key = HKS_BLOB_DEFAULT_VALUE;
    struct hks_storage_buffer key_buffer = { 0, NULL, 0 };

    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));
    (void)memset_s(&key_material, sizeof(key_material), 0, sizeof(key_material));

    hks_blob_init(&public_key, sizeof(uint8_t), key->size, key->type);
    if (memcpy_s(public_key.data, public_key.size, key->data, key->size) != EOK)
        goto exit;

    msg->key_material = &key_material;
    msg->key_alias = key_alias;
    msg->key_param = key_param;
    msg->key_data = key;
    msg->key_material->key_info = &key_info;
    msg->key_material->key_info->param = (struct hks_key_param *)key_param;
    msg->key_material->key_info->public_key = &public_key;

    int32_t status = hks_encrypt_material_init(&key_material);

    hks_if_status_error_goto_error(status, exit);
    status = hks_prepare_for_encrypt_key(key_alias, &key_material, &key_buffer);
    hks_if_status_error_goto_error(status, exit);

    hks_enter_secure_mode(&msg_box);
    status = msg_box.status;
    hks_if_status_error_goto_error(status, exit);

    status = hks_nmi_write_key_info(key_alias, &key_material, &key_buffer);

exit:
    if (key_buffer.buf != NULL)
        (void)memset_s(key_buffer.buf, key_buffer.size, 0, key_buffer.size);
    hks_free_ptr(key_buffer.buf);
    hks_blob_destroy(&public_key);
    hks_encrypt_material_destroy_free(&key_material);

    return msg_box.status;
#else
    msg->key_alias = key_alias;
    msg->key_param = key_param;
    msg->key_data = key;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
#endif
}

int32_t hks_access_export_key(const struct hks_blob *key_alias, struct hks_blob *key)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_export_key_msg *msg = &msg_box.msg_data.export_key_msg;

    msg_box.cmd_id = HKS_EXPORT_KEY;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_storage_key_info key_info;
    struct hks_key_param param;
    struct hks_encrypt_material encrypt_material;

    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));
    (void)memset_s(&param, sizeof(param), 0, sizeof(param));
    (void)memset_s(&encrypt_material, sizeof(encrypt_material), 0, sizeof(encrypt_material));

    key_info.param = &param;
    param.key_auth_id.size = HKS_AUTH_ID_MAX_SIZE;
    key_info.private_key = NULL;
    key_info.public_key = key;
    encrypt_material.key_info = &key_info;

    int32_t res = hks_encrypt_material_init(&encrypt_material);

    hks_if_status_error_goto_error(res, exit);
    res = hks_prepare_encrypt_material(key_alias, &encrypt_material);
    hks_if_status_error_goto_error(res, exit);

    msg->key_alias = key_alias;
    msg->key_data = key;
    msg->encrypt_material = &encrypt_material;
    hks_enter_secure_mode(&msg_box);
    res = msg_box.status;

exit:
    hks_key_param_destroy(&param);
    hks_encrypt_material_destroy_free(&encrypt_material);

    return res;
#else
    msg->key_alias = key_alias;
    msg->key_data = key;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
#endif
}

#ifndef _SUPPORT_HKS_TEE_
int32_t hks_access_delete_key(const struct hks_blob *key_alias)
{
    int32_t status = hks_service_delete_key(key_alias);

    hks_if_status_error_return(status);

    return status;
}

int32_t hks_access_is_key_exist(const struct hks_blob *key_alias)
{
    int32_t status = hks_service_is_key_exist(key_alias);

    hks_if_status_error_return(status);

    return status;
}

int32_t hks_access_get_key_param(const struct hks_blob *key_alias,
    struct hks_key_param *key_param)
{
    int32_t status = hks_service_get_key_param(key_alias, key_param);

    hks_if_status_error_return(status);

    return status;
}

int32_t hks_access_get_pub_key_alias_list(struct hks_blob *key_alias_list, uint32_t *list_count)
{
    int32_t status = hks_service_get_pub_key_alias_list(key_alias_list, list_count);

    hks_if_status_error_return(status);

    return status;
}
#endif

int32_t hks_access_get_random(struct hks_blob *random)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_generate_random_msg *msg = &msg_box.msg_data.generate_random_msg;

    msg_box.cmd_id = HKS_GENERATE_RANDOM;
    msg->random = random;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

int32_t hks_access_hmac(const struct hks_blob *key,
    uint32_t alg, const struct hks_blob *src_data, struct hks_blob *output)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_hmac_msg *msg = &msg_box.msg_data.hmac_msg;

    msg_box.cmd_id = HKS_HMAC;
    msg->alg = alg;
    msg->key = key;
    msg->src_data = src_data;
    msg->output = output;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

int32_t hks_access_hash(uint32_t alg, const struct hks_blob *src_data,
    struct hks_blob *hash)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_hash_msg *msg = &msg_box.msg_data.hash_msg;

    msg_box.cmd_id = HKS_HASH;
    msg->alg = alg;
    msg->src_data = src_data;
    msg->hash = hash;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

int32_t hks_access_key_agreement(struct hks_blob *agreed_key, const struct hks_key_param *private_key_param,
    const struct hks_blob *private_key, const struct hks_blob *peer_public_key, const uint32_t agreement_alg)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_key_agreement_msg *msg = &msg_box.msg_data.key_agreement_msg;

    msg_box.cmd_id = HKS_KEY_AGREEMENT;
    msg->agreed_key = agreed_key;
    msg->key_param = private_key_param;
    msg->agreement_alg = agreement_alg;
    msg->priv_key = private_key;
    msg->pub_key = peer_public_key;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

int32_t hks_access_key_derivation(struct hks_blob *derived_key, const struct hks_blob *kdf_key,
    const struct hks_blob *salt, const struct hks_blob *label, const struct hks_key_param *key_params)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_key_derivation_msg *msg = &msg_box.msg_data.key_derivation_msg;

    msg_box.cmd_id = HKS_KEY_DERIVATION;
    msg->derived_key = derived_key;
    msg->key_param = key_params;
    msg->kdf_key = kdf_key;
    msg->salt = salt;
    msg->label = label;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

int32_t hks_access_bn_exp_mod(struct hks_blob *x, const struct hks_blob *a, const struct hks_blob *e,
    const struct hks_blob *n)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_bn_exp_mod_msg *msg = &msg_box.msg_data.bn_exp_mod_msg;

    msg_box.cmd_id = HKS_BN_EXP_MOD;
    msg->x = x;
    msg->a = a;
    msg->e = e;
    msg->n = n;
    hks_enter_secure_mode(&msg_box);

    return msg_box.status;
}

#ifdef _SECURE_ENVIREMENT_NMI_
int32_t hks_access_generate_symmetric_key(struct hks_blob *output_key, const struct hks_key_param *key_param)
{
    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_generate_symmetric_key_msg *msg = &msg_box.msg_data.generate_symmetric_key_msg;
    struct hks_storage_key_info key_info;
    struct hks_encrypt_material key_material;

    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));
    (void)memset_s(&key_material, sizeof(key_material), 0, sizeof(key_material));

    msg_box.cmd_id = HKS_NMI_GENERATE_SYMMETRIC_KEY;
    msg->output_key = output_key;
    msg->key_material = &key_material;
    msg->key_material->key_info = &key_info;
    msg->key_material->key_info->param = (struct hks_key_param *)key_param;

    int32_t status = hks_key_material_init_symmetric(&key_info, &key_material, key_param);

    if (status != HKS_SUCCESS)
        goto exit;

    hks_enter_secure_mode(&msg_box);
    status = msg_box.status;

exit:
    hks_encrypt_material_destroy_free(&key_material);
    hks_blob_destroy(key_info.private_key);
    hks_free_ptr(key_info.private_key);

    return status;
}

int32_t hks_access_symmetric_encrypt_decrypt(const struct hks_blob *key,
    const struct hks_key_param *key_param, const struct hks_crypt_param *crypt_param,
    struct hks_encrypt_decrypt_text *hks_cipher_text, uint32_t operation_mode)
{
    if (hks_cipher_text == NULL)
        return HKS_ERROR_NULL_POINTER;

    struct sec_mod_msg msg_box;

    (void)memset_s(&msg_box, sizeof(msg_box), 0, sizeof(msg_box));

    struct hks_symmetric_encrypt_decrypt_msg *msg = &msg_box.msg_data.symmetric_encrypt_decrypt_msg;
    struct hks_storage_key_info key_info;
    struct hks_encrypt_material key_material;

    (void)memset_s(&key_info, sizeof(key_info), 0, sizeof(key_info));
    (void)memset_s(&key_material, sizeof(key_material), 0, sizeof(key_material));

    msg_box.cmd_id = HKS_SYMMETRIC_ENCRYPT_DECRYPT;
    msg->key_material = &key_material;
    msg->key_material->key_info = &key_info;
    msg->key_material->key_info->param = (struct hks_key_param *)key_param;
    msg->crypt_param = crypt_param;
    msg->input_text = hks_cipher_text->input_text;
    msg->output_text = hks_cipher_text->output_text;
    msg->operation_mode = operation_mode;

    int32_t status = hks_init_get_encrypted_key_info(key, key_param, &key_info, &key_material);

    if (status != HKS_SUCCESS)
        goto exit;

    hks_enter_secure_mode(&msg_box);
    status = msg_box.status;

exit:
    hks_encrypt_material_destroy_free(&key_material);
    hks_blob_destroy(key_info.private_key);
    hks_free_ptr(key_info.private_key);

    return status;
}
#endif

#ifndef _SUPPORT_HKS_TEE_
static void hks_handle_generate_key(struct sec_mod_msg *msg_box)
{
    struct hks_generate_key_msg *msg = &msg_box->msg_data.generate_key_msg;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_blob encrypt_material = HKS_BLOB_DEFAULT_VALUE;

    encrypt_material.type = HKS_BLOB_TYPE_MATERIAL;
    encrypt_material.data = (uint8_t *)msg->key_material;
    msg_box->status = hks_service_generate_key(&encrypt_material, msg->key_material->key_info->param);
#else
    msg_box->status = hks_service_generate_key(msg->key_alias, msg->key_param);
#endif
}

static void hks_handle_sign(struct sec_mod_msg *msg_box)
{
    struct hks_sign_verify_msg *msg = &msg_box->msg_data.sign_verify_msg;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_blob encrypt_material = HKS_BLOB_DEFAULT_VALUE;

    encrypt_material.type = HKS_BLOB_TYPE_MATERIAL;
    encrypt_material.data = (uint8_t *)msg->encrypt_material;
    msg_box->status = hks_service_asymmetric_sign(&encrypt_material, msg->key_param, msg->message, msg->signature);
#else
    msg_box->status = hks_service_asymmetric_sign(msg->key, msg->key_param, msg->message, msg->signature);
#endif
}

static void hks_handle_import(struct sec_mod_msg *msg_box)
{
    struct hks_import_key_msg *msg = &msg_box->msg_data.import_key_msg;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_blob key_alias = HKS_BLOB_DEFAULT_VALUE;

    key_alias.type = HKS_BLOB_TYPE_MATERIAL;
    key_alias.data = (uint8_t *)msg->key_material;
    msg_box->status = hks_service_import_public_key(&key_alias, msg->key_param, msg->key_data);
#else
    msg_box->status = hks_service_import_public_key(msg->key_alias, msg->key_param, msg->key_data);
#endif
}

static void hks_handle_export(struct sec_mod_msg *msg_box)
{
    struct hks_export_key_msg *msg = &msg_box->msg_data.export_key_msg;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_blob encrypt_material = HKS_BLOB_DEFAULT_VALUE;

    encrypt_material.type = HKS_BLOB_TYPE_MATERIAL;
    encrypt_material.data = (uint8_t *)msg->encrypt_material;
    msg_box->status = hks_service_export_public_key(&encrypt_material, msg->key_data);
#else
    msg_box->status = hks_service_export_public_key(msg->key_alias, msg->key_data);
#endif
}
#endif

static void hks_handle_generate_key_ex(struct sec_mod_msg *msg_box)
{
    struct hks_generate_ex_msg *msg = &msg_box->msg_data.generate_ex_msg;

    msg_box->status = hks_service_generate_asymmetric_key(msg->key_param, msg->priv_key, msg->pub_key);
}

static void hks_handle_verify(struct sec_mod_msg *msg_box)
{
    struct hks_sign_verify_msg *msg = &msg_box->msg_data.sign_verify_msg;

#ifdef _SECURE_ENVIREMENT_NMI_
    struct hks_blob encrypt_material = HKS_BLOB_DEFAULT_VALUE;

    encrypt_material.type = HKS_BLOB_TYPE_MATERIAL;
    encrypt_material.data = (uint8_t *)msg->encrypt_material;
    if (msg->key->type == HKS_BLOB_TYPE_ALIAS)
        msg_box->status = hks_service_asymmetric_verify(&encrypt_material, msg->message, msg->signature);
    else
        msg_box->status = hks_service_asymmetric_verify(msg->key, msg->message, msg->signature);
#else
    msg_box->status = hks_service_asymmetric_verify(msg->key, msg->message, msg->signature);
#endif
}

static void hks_handle_encrypt(struct sec_mod_msg *msg_box)
{
    struct hks_encrypt_decrypt_msg *msg = &msg_box->msg_data.encrypt_decrypt_msg;

    msg_box->status = hks_service_aead_encrypt_ex(msg->key, msg->key_param, msg->crypt_param, msg->plain_text,
        msg->cipher_text_with_tag);
}

static void hks_handle_decrypt(struct sec_mod_msg *msg_box)
{
    struct hks_encrypt_decrypt_msg *msg = &msg_box->msg_data.encrypt_decrypt_msg;

    msg_box->status = hks_service_aead_decrypt_ex(msg->key, msg->key_param, msg->crypt_param,
        msg->cipher_text_with_tag, msg->plain_text);
}

static void hks_handle_get_random(struct sec_mod_msg *msg_box)
{
    struct hks_generate_random_msg *msg = &msg_box->msg_data.generate_random_msg;

    msg_box->status = hks_service_get_random(msg->random);
}

static void hks_handle_key_agreement(struct sec_mod_msg *msg_box)
{
    struct hks_key_agreement_msg *msg = &msg_box->msg_data.key_agreement_msg;

    msg_box->status = hks_service_key_agreement(msg->agreed_key, msg->key_param,
        msg->priv_key, msg->pub_key, msg->agreement_alg);
}

static void hks_handle_key_deviration(struct sec_mod_msg *msg_box)
{
    struct hks_key_derivation_msg *msg = &msg_box->msg_data.key_derivation_msg;

    msg_box->status = hks_service_key_derivation(msg->derived_key, msg->kdf_key, msg->salt, msg->label, msg->key_param);
}

static void hks_handle_hmac(struct sec_mod_msg *msg_box)
{
    struct hks_hmac_msg *msg = &msg_box->msg_data.hmac_msg;

    msg_box->status = hks_service_hmac_ex(msg->key, msg->alg, msg->src_data, msg->output);
}

static void hks_handle_hash(struct sec_mod_msg *msg_box)
{
    struct hks_hash_msg *msg = &msg_box->msg_data.hash_msg;

    msg_box->status = hks_service_hash(msg->alg, msg->src_data, msg->hash);
}

static void hks_handle_bn_exp_mod(struct sec_mod_msg *msg_box)
{
    struct hks_bn_exp_mod_msg *msg = &msg_box->msg_data.bn_exp_mod_msg;

    msg_box->status = hks_service_bn_exp_mod(msg->x, msg->a, msg->e, msg->n);
}

#ifdef _SECURE_ENVIREMENT_NMI_
static void hks_handle_generate_symmetric_key(struct sec_mod_msg *msg_box)
{
    struct hks_generate_symmetric_key_msg *msg = &msg_box->msg_data.generate_symmetric_key_msg;

    msg_box->status = hks_service_generate_symmetric_key(msg->output_key, msg->key_material);
}

static void hks_handle_symmetric_encrypt_decrypt(struct sec_mod_msg *msg_box)
{
    struct hks_symmetric_encrypt_decrypt_msg *msg = &msg_box->msg_data.symmetric_encrypt_decrypt_msg;

    msg_box->status = hks_service_symmetric_encrypt_decrypt(msg->key_material, msg->crypt_param, msg->input_text,
        msg->output_text, msg->operation_mode);
}
#endif

#ifndef _SUPPORT_HKS_TEE_
hks_handle_func_p g_hks_handle_func[HKS_CMD_MAX] = {
    hks_handle_generate_key,
    hks_handle_generate_key_ex,
    hks_handle_sign,
    hks_handle_verify,
    hks_handle_encrypt,
    hks_handle_decrypt,
    hks_handle_import,
    hks_handle_export,
    hks_handle_get_random,
    hks_handle_key_agreement,
    hks_handle_key_deviration,
    hks_handle_hmac,
    hks_handle_hash,
    hks_handle_bn_exp_mod,
#ifdef _SECURE_ENVIREMENT_NMI_
    hks_handle_generate_symmetric_key,
    hks_handle_symmetric_encrypt_decrypt,
#else
    NULL,
    NULL,
#endif
};
#else
hks_handle_func_p g_hks_handle_func[HKS_CMD_MAX] = {
    NULL,
    hks_handle_generate_key_ex,
    NULL,
    hks_handle_verify,
    hks_handle_encrypt,
    hks_handle_decrypt,
    NULL,
    NULL,
    hks_handle_get_random,
    hks_handle_key_agreement,
    hks_handle_key_deviration,
    hks_handle_hmac,
    hks_handle_hash,
    hks_handle_bn_exp_mod,
    NULL,
    NULL,
};
#endif

static void __hks_handle_secure_call(struct sec_mod_msg *msg_box)
{
    if (msg_box == NULL)
        return;

#ifdef _SECURE_ENVIREMENT_NMI_
    log_info("Store the temp key to secure memory, cmd id is %u\n", msg_box->cmd_id);
    for (int i = 0; i < HKS_ROOT_KEY_LEN; i++)
        g_sec_mod_data[i] = SEC_MODE_DATA;
    *g_sec_mod_ctrl = 0;
#endif

    if (msg_box->cmd_id < HKS_CMD_MAX) {
        if (g_hks_handle_func[msg_box->cmd_id])
            g_hks_handle_func[msg_box->cmd_id](msg_box);
    } else {
        msg_box->status = HKS_ERROR_NOT_SUPPORTED;
    }
}

void hks_handle_secure_call(void)
{
    log_info("%s: entered!.\n", __func__);

    __hks_handle_secure_call(&g_msg_box);
}
