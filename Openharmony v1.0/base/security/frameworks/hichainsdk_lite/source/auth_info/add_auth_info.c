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

#include "add_auth_info.h"
#include <string.h>
#include <securec.h>
#include "log.h"
#include "base.h"
#include "mem_stat.h"
#include "parsedata.h"
#include "commonutil.h"
#include "huks_adapter.h"

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) || defined(_CUT_ADD_) || defined(_CUT_ADD_SERVER_))
#define HC_ADDAUTH_CIPHER_LEN 32
#define HICHAIN_ADD_INFO_RESPONSE "hichain_add_info_response"
#define HICHAIN_ADD_INFO_REQUEST  "hichain_add_info_request"
#define AUTH_INFO_LENGTH 1000

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
static const uint8_t g_import_aad[] = "com.huawei.deviceauth";
#endif
static int32_t parse_add_request_data(const struct hichain *hichain, add_request_data *receive,
    struct auth_info_cache *cache);
static int32_t build_add_response_data(const struct hichain *hichain, add_response_data *send);
int32_t send_add_response(const struct hichain *hichain, struct message *receive, struct message *send)
{
    add_response_data *send_data = malloc_auth_info_msg(HC_ADDAUTH_CIPHER_LEN);
    if (send_data == NULL) {
        LOGE("Malloc struct add_response_data failed");
        send->msg_code = INFORM_MESSAGE;
        return HC_MALLOC_FAILED;
    }
    struct auth_info_cache cache;
    int32_t ret = parse_add_request_data(hichain, (add_request_data *)receive->payload, &cache);
    if (ret != HC_OK) {
        LOGE("Parse add request failed, error code is %d", ret);
        goto error;
    }
    ret = build_add_response_data(hichain, send_data);
    if (ret != HC_OK) {
        LOGE("Build add response failed, error code is %d", ret);
        goto error;
    }
    ret = save_auth_info(hichain, HC_PAIR_TYPE_AUTH, &cache);
    if (ret != HC_OK) {
        LOGE("Save ltpk failed, error code is %d", ret);
        goto error;
    }

    DBG_OUT("Send add response success");
    send->payload = send_data;
    send->msg_code = ADD_AUTHINFO_RESPONSE;
    return HC_OK;

error:
    free_auth_info_msg(send_data);
    send->msg_code = INFORM_MESSAGE;
    return ret;
}

static int32_t get_field_from_request_payload(struct uint8_buff *payload, int32_t *user_type,
    struct hc_auth_id *auth_id, struct ltpk *ltpk);
static int32_t parse_add_request_data(const struct hichain *hichain, add_request_data *receive,
    struct auth_info_cache *cache)
{
    const struct sts_session_key *session_key = get_sts_session_key(hichain);
    if (session_key == NULL) {
        LOGE("Get sts session key failed");
        return HC_STS_OBJECT_ERROR;
    }
    struct uint8_buff plain = { NULL, 0, 0 };
    int32_t ret = decrypt_payload((const struct var_buffer *)session_key, &receive->cipher,
        HICHAIN_ADD_INFO_REQUEST, &plain);
    if (ret != HC_OK) {
        LOGE("Decrypt add request payload failed");
        return ret;
    }
    ret = get_field_from_request_payload(&plain, &cache->user_type, &cache->auth_id, &cache->ltpk);
    FREE(plain.val);
    plain.val = NULL;
    if (ret != HC_OK) {
        LOGE("Get field from add request message failed, error code is %d", ret);
        return ret;
    }
    return HC_OK;
}

static int32_t build_add_response_data(const struct hichain *hichain, add_response_data *send)
{
    uint8_t array[sizeof(int32_t)] = {0};
    struct uint8_buff plain = {
        .val = array,
        .size = sizeof(array),
        .length = sizeof(array)
    };

    const struct sts_session_key *key = get_sts_session_key(hichain);
    int32_t ret = encrypt_payload((const struct var_buffer *)key, &plain, HICHAIN_ADD_INFO_RESPONSE, &send->cipher);
    if (ret != HC_OK) {
        LOGE("Encrypt add response failed, error code is %d", ret);
        return HC_ENCRYPT_FAILED;
    }
    return HC_OK;
}

static int32_t get_field_from_request_payload(struct uint8_buff *payload, int32_t *user_type,
    struct hc_auth_id *auth_id, struct ltpk *ltpk)
{
    struct add_auth_data *add_auth_data = parse_add_auth_info_data((char *)payload->val, JSON_STRING_DATA);
    if (add_auth_data == NULL) {
        LOGE("Parse add auth info data failed");
        return HC_DECRYPT_FAILED;
    }
    *user_type = add_auth_data->user_type;
    *auth_id = add_auth_data->auth_id;
    *ltpk = add_auth_data->ltpk;
    free_add_auth_info_data(add_auth_data);
    return HC_OK;
}

#endif /* _CUT_XXX_ */

static int32_t save_import_auth_info(const struct hichain *hichain, const struct hc_auth_id *auth_id,
    struct import_auth_data *import_data)
{
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    struct auth_info_cache cache = { import_data->user_type, import_data->auth_id, import_data->ltpk };
#else
    struct auth_info_cache cache = { HC_USER_TYPE_CONTROLLER, import_data->auth_id, import_data->ltpk };
#endif

    int32_t pair_type;
    if ((auth_id->length == cache.auth_id.length) &&
        (memcmp(auth_id->auth_id, cache.auth_id.auth_id, auth_id->length) == 0)) {
        pair_type = HC_PAIR_TYPE_BIND;
    } else {
        pair_type = HC_PAIR_TYPE_AUTH;
    }

    int32_t ret = save_auth_info(hichain, pair_type, &cache);
    if (ret != HC_OK) {
        LOGE("Save auth info failed, error code is %d", ret);
        return HC_IMPORT_AUTH_DATA_FAILED;
    }
    return HC_OK;
}

static int32_t verify_import_auth_info(const struct hichain *hichain, struct import_auth_data *import_data,
    struct uint8_buff *message, struct signature *sign_result)
{
    struct service_id service_id = generate_service_id(&hichain->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        return HC_GEN_SERVICE_ID_FAILED;
    }
    struct hc_key_alias key_alias = generate_key_alias(&service_id, &import_data->owner_id, KEY_ALIAS_CONTROLLER_PK);
    int32_t ret = verify(&key_alias, KEY_ALIAS_CONTROLLER_PK, message, sign_result);
    if (ret != HC_OK) {
        LOGE("Verify import add auth data failed, error code is %d", ret);
        return HC_VERIFY_PROOF_FAILED;
    }

    return HC_OK;
}

int32_t import_signed_auth_info_hilink(const struct hichain *hichain, const struct hc_auth_id *auth_id,
    struct uint8_buff *data)
{
    check_ptr_return_val(hichain, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);
    check_ptr_return_val(data, HC_INPUT_ERROR);

    if (data->length <= (HC_SIGNATURE_LEN * BYTE_TO_HEX_OPER_LENGTH)) {
        LOGE("Import public key signature info length is %u", data->length);
        return HC_SIGN_TOO_SHORT;
    }

    uint32_t len = (data->length / BYTE_TO_HEX_OPER_LENGTH) + 1;
    uint8_t *receive_data = (uint8_t *)MALLOC(len);
    if (receive_data == NULL) {
        LOGE("malloc inport signed auth info receive data failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(receive_data, len, 0, len);
    if (hex_string_to_byte((char *)data->val, data->length, receive_data) != HC_OK) {
        FREE(receive_data);
        return HC_INNER_ERROR;
    }

    struct signature sign_result = { 0, {0} };
    if (memcpy_s(sign_result.signature, sizeof(sign_result.signature), receive_data, HC_SIGNATURE_LEN) != EOK) {
        FREE(receive_data);
        return memory_copy_error(__func__, __LINE__);
    }
    sign_result.length = HC_SIGNATURE_LEN;
    struct uint8_buff message = { NULL, 0, 0 };
    message.val = receive_data + HC_SIGNATURE_LEN;
    message.length = (data->length / BYTE_TO_HEX_OPER_LENGTH) - HC_SIGNATURE_LEN;

    struct import_auth_data *import_data = (struct import_auth_data *)parse_import_add_auth_data(
        (char *)message.val, JSON_STRING_DATA);
    if (import_data == NULL) {
        LOGE("Parse import add auth data failed");
        FREE(receive_data);
        return HC_BUILD_OBJECT_FAILED;
    }

    int32_t ret = verify_import_auth_info(hichain, import_data, &message, &sign_result);
    if (ret != HC_OK) {
        FREE(receive_data);
        free_import_add_auth_data(import_data);
        return ret;
    }

    ret = save_import_auth_info(hichain, auth_id, import_data);
    FREE(receive_data);
    free_import_add_auth_data(import_data);
    return ret;
}

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
int32_t import_signed_auth_info(const struct hichain *hichain, const struct hc_auth_id *auth_id,
    struct uint8_buff *data)
{
    check_ptr_return_val(hichain, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);
    check_ptr_return_val(data, HC_INPUT_ERROR);
    if (data->length <= HC_SIGNATURE_LEN) {
        LOGE("Import public key signature info length is %d", data->length);
        return HC_SIGN_TOO_SHORT;
    }

    struct signature sign_result = { 0, {0} };
    if (memcpy_s(sign_result.signature, sizeof(sign_result.signature), data->val, HC_SIGNATURE_LEN) != EOK) {
        return memory_copy_error(__func__, __LINE__);
    }

    sign_result.length = HC_SIGNATURE_LEN;
    struct uint8_buff message = { NULL, 0, 0 };
    message.val = data->val + HC_SIGNATURE_LEN;
    message.length = data->length - HC_SIGNATURE_LEN;
    struct import_auth_data *import_data = (struct import_auth_data *)parse_import_add_auth_data(
        (char *)message.val, JSON_STRING_DATA);
    if (import_data == NULL) {
        LOGE("Parse import add auth data failed");
        return HC_BUILD_OBJECT_FAILED;
    }

    int32_t ret = verify_import_auth_info(hichain, import_data, &message, &sign_result);
    if (ret != HC_OK) {
        LOGE("Verify failed!");
        free_import_add_auth_data(import_data);
        return ret;
    }

    ret = save_import_auth_info(hichain, auth_id, import_data);
    free_import_add_auth_data(import_data);
    LOGI("Import signed auth info success");
    return ret;
}

int32_t import_lite_auth_info(const struct hichain *hichain, const struct hc_auth_id *auth_id,
    struct uint8_buff *data)
{
    check_ptr_return_val(hichain, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);
    check_ptr_return_val(data, HC_INPUT_ERROR);
    if (data->length > AUTH_INFO_LENGTH) {
        LOGE("Import public key info length is %u", data->length);
        return HC_INPUT_ERROR;
    }

    /* KEK decrypt */
    struct service_id service_id = generate_service_id(&hichain->identity);
    struct hc_key_alias kek_alias = generate_key_alias(&service_id, auth_id, KEY_ALIAS_KEK);
    struct uint8_buff out_plain = { NULL, 0, 0 };
    struct aes_aad aes_aad;

    aes_aad.length = strlen((char *)g_import_aad);
    (void)memcpy_s(aes_aad.aad, HC_AES_ADD_LEN, g_import_aad, aes_aad.length);
    aes_aad.aad[aes_aad.length] = '\0';

    out_plain.val = (uint8_t *)MALLOC(data->length);
    if (out_plain.val == NULL) {
        LOGE("Malloc peer_auth_data failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(out_plain.val, data->length, 0, data->length);
    out_plain.size = data->length;

    int32_t ret = aes_ccm_decrypt((struct var_buffer *)&kek_alias, data, &aes_aad, &out_plain);
    if (ret != HC_OK) {
        LOGE("Decrypt failed, error is %d", ret);
        FREE(out_plain.val);
        return HC_DECRYPT_FAILED;
    }

    struct import_auth_data *import_data = (struct import_auth_data *)parse_import_add_auth_data(
        (char *)out_plain.val, JSON_STRING_DATA);
    if (import_data == NULL) {
        LOGE("Parse import lite add auth data failed");
        free_import_add_auth_data(out_plain.val);
        return HC_BUILD_OBJECT_FAILED;
    }

    ret = save_import_auth_info(hichain, auth_id, import_data);
    free_import_add_auth_data(import_data);
    if (ret != HC_OK) {
        LOGE("Import lite auth info failed");
        return ret;
    }
    LOGI("Import lite auth info success");
    return ret;
}
#endif
