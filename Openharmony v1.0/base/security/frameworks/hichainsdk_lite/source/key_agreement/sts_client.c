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

#include "sts_client.h"

#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_))
#include <string.h>
#include <securec.h>
#include "huks_adapter.h"
#include "log.h"
#include "commonutil.h"
#include "distribution.h"

static int32_t build_start_request_data(void *handle, void *data);
static int32_t parse_start_response_data(void *handle, void *data);
static int32_t build_end_request_data(void *handle, void *data);
static int32_t parse_end_response_data(void *handle, void *data);

static void generate_output_key(struct sts_client *sts_client);

struct sts_client *build_sts_client(const hc_handle hichain_handle, uint32_t key_length,
    const struct hc_auth_id *client, const struct hc_auth_id *server)
{
    struct sts_client *sts_client = (struct sts_client *)MALLOC(sizeof(struct sts_client));
    if (sts_client == NULL) {
        LOGE("Build sts client object failed");
        return NULL;
    }
    (void)memset_s(sts_client, sizeof(*sts_client), 0, sizeof(*sts_client));

    struct client_virtual_func_group funcs = { build_start_request_data, parse_start_response_data,
                                               build_end_request_data, parse_end_response_data };

    init_client(&sts_client->client_info, &funcs);
    DBG_OUT("Build sts client object %u success", sts_client_sn(sts_client));

    sts_client->self_id = *client;
    sts_client->peer_id = *server;
    sts_client->identity = &((struct hichain *)hichain_handle)->identity;
    sts_client->key_length = key_length;
    sts_client->hichain_handle = hichain_handle;

    return sts_client;
}

void destroy_sts_client(struct sts_client *handle)
{
    if (handle == NULL) {
        DBG_OUT("Destroy sts client object failed");
        return;
    }

    FREE(handle);
    DBG_OUT("FREE sts client object success");
}

static int32_t build_start_request_data(void *handle, void *data)
{
    struct sts_client *sts_client = (struct sts_client *)handle;
    struct sts_start_request_data *send_data = (struct sts_start_request_data *)data;
    struct st_key_pair key_pair;
    int32_t ret = generate_st_key_pair(&key_pair);
    if (ret != HC_OK) {
        LOGE("Object %u generate_st_key_pair failed, error code is %d", sts_client_sn(sts_client), ret);
        return HC_INPUT_ERROR;
    }

    sts_client->self_private_key = key_pair.st_private_key;
    sts_client->self_public_key = key_pair.st_public_key;

    struct random_value random_value = generate_random(CHALLENGE_BUFF_LENGTH);
    if (memcpy_s(sts_client->my_challenge.challenge, sizeof(sts_client->my_challenge.challenge),
        random_value.random_value, random_value.length) != EOK) {
        return memory_copy_error(__func__, __LINE__);
    }
    sts_client->my_challenge.length = random_value.length;

    send_data->peer_version.first = 1;
    send_data->peer_version.second = 0;
    send_data->peer_version.third = 0;
    send_data->peer_support_version.first = 1;
    send_data->peer_support_version.second = 0;
    send_data->peer_support_version.third = 0;
    send_data->operation_code = sts_client->operation_code;
    send_data->epk = sts_client->self_public_key;
    send_data->challenge = sts_client->my_challenge;
    send_data->package_name = sts_client->identity->package_name;
    send_data->service_type = sts_client->identity->service_type;
    send_data->self_auth_id = sts_client->self_id;
    send_data->peer_user_type = ((struct hichain *)sts_client->hichain_handle)->type == HC_CENTRE ?
        HC_USER_TYPE_CONTROLLER : HC_USER_TYPE_ACCESSORY;
    send_data->key_length = sts_client->key_length;

    return HC_OK;
}

static int32_t parse_start_response_data(void *handle, void *data)
{
    struct sts_client *sts_client = (struct sts_client *)handle;
    struct sts_start_response_data *receive = (struct sts_start_response_data *)data;

    sts_client->salt = receive->salt;
    sts_client->peer_public_key = receive->epk;
    sts_client->peer_challenge = receive->challenge;
    sts_client->peer_auth_data = receive->auth_data;
    sts_client->peer_user_type = receive->peer_user_type;

    struct sts_shared_secret shared_secret;

    int32_t ret = compute_sts_shared_secret(&sts_client->self_private_key,
                                            &sts_client->peer_public_key, &shared_secret);
    if (ret != HC_OK) {
        LOGE("Object %u compute_shared_secret failed, error code is %d", sts_client_sn(sts_client), ret);
        return ret;
    }

    ret = compute_hkdf((struct var_buffer *)&shared_secret, &sts_client->salt, HICHAIN_AUTH_INFO,
                       STS_SESSION_KEY_LENGTH, (struct var_buffer *)&sts_client->session_key);
    if (ret != HC_OK) {
        LOGE("Object %u compute_hkdf failed, error code is %d", sts_client_sn(sts_client), ret);
        return HC_STS_OBJECT_ERROR;
    }

    return HC_OK;
}

static int32_t generate_sign_message(void *handle, struct uint8_buff *message)
{
    DBG_OUT("Called generate sign message");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(message, HC_INPUT_ERROR);
    struct sts_client *sts_client = (struct sts_client *)handle;

    int len = sts_client->peer_public_key.length + sts_client->peer_id.length +
              sts_client->self_public_key.length + sts_client->self_id.length;
    uint8_t *info = (uint8_t *)MALLOC(len);
    if (info == NULL) {
        LOGE("Malloc info failed");
        return HC_MALLOC_FAILED;
    }

    int32_t pos = 0;
    (void)memcpy_s(info + pos, len - pos, sts_client->peer_public_key.stpk, sts_client->peer_public_key.length);
    pos += sts_client->peer_public_key.length;
    (void)memcpy_s(info + pos, len - pos, sts_client->peer_id.auth_id, sts_client->peer_id.length);
    pos += sts_client->peer_id.length;
    (void)memcpy_s(info + pos, len - pos, sts_client->self_public_key.stpk, sts_client->self_public_key.length);
    pos += sts_client->self_public_key.length;
    (void)memcpy_s(info + pos, len - pos, sts_client->self_id.auth_id, sts_client->self_id.length);

    message->val = info;
    message->length = len;
    message->size = len;
    return HC_OK;
}

static int32_t verify_response_data(void *handle, const struct uint8_buff *message, struct signature *signature)
{
    DBG_OUT("Called verify request data");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(message, HC_INPUT_ERROR);
    check_ptr_return_val(signature, HC_INPUT_ERROR);
    struct sts_client *sts_client = (struct sts_client *)handle;

    struct hichain *hichain_handle = sts_client->hichain_handle;
    enum huks_key_alias_type alias_type;

    if (hichain_handle->type == HC_CENTRE) {
        if (sts_client->peer_user_type == HC_USER_TYPE_CONTROLLER) { /* center(as phone identity) -> phone */
            alias_type = KEY_ALIAS_LT_KEY_PAIR;
        } else { /* center -> accessory */
            alias_type = KEY_ALIAS_ACCESSOR_PK;
        }
    } else { /* accessory -> center/phone */
        alias_type = KEY_ALIAS_CONTROLLER_PK;
    }

    struct service_id service_id = generate_service_id(sts_client->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        return HC_GEN_SERVICE_ID_FAILED;
    }
    struct hc_key_alias key_alias = generate_key_alias(&service_id, &sts_client->peer_id, alias_type);
    if (key_alias.length == 0) {
        LOGE("Generate key alias failed");
        return HC_GEN_ALIAS_FAILED;
    }

    int32_t ret = verify(&key_alias, sts_client->peer_user_type, message, signature);
    if (ret != HC_OK) {
        LOGE("Object %u verify failed, error code is %d", sts_client_sn(sts_client), ret);
        return HC_VERIFY_PROOF_FAILED;
    }
    return HC_OK;
}

static int32_t generate_sts_request_sign(void *handle, struct signature *signature)
{
    struct sts_client *sts_client = (struct sts_client *)handle;

    int32_t len = sts_client->self_public_key.length + sts_client->self_id.length +
                  sts_client->peer_public_key.length + sts_client->peer_id.length;
    uint8_t *info = (uint8_t *)MALLOC(len);
    if (info == NULL) {
        LOGE("Malloc info failed");
        return HC_MALLOC_FAILED;
    }

    int32_t pos = 0;
    (void)memcpy_s(info + pos, len - pos, sts_client->self_public_key.stpk, sts_client->self_public_key.length);
    pos += sts_client->self_public_key.length;
    (void)memcpy_s(info + pos, len - pos, sts_client->self_id.auth_id, sts_client->self_id.length);
    pos += sts_client->self_id.length;
    (void)memcpy_s(info + pos, len - pos, sts_client->peer_public_key.stpk, sts_client->peer_public_key.length);
    pos += sts_client->peer_public_key.length;
    (void)memcpy_s(info + pos, len - pos, sts_client->peer_id.auth_id, sts_client->peer_id.length);

    struct service_id service_id = generate_service_id(sts_client->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        FREE(info);
        return HC_GEN_SERVICE_ID_FAILED;
    }
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    struct hc_key_alias key_alias = generate_key_alias(&service_id, &sts_client->self_id, KEY_ALIAS_LT_KEY_PAIR);
#else
    struct hc_key_alias key_alias = generate_key_alias(&service_id, &sts_client->self_id, KEY_ALIAS_ACCESSOR_PK);
#endif
    if (key_alias.length == 0) {
        LOGE("Generate key alias failed");
        FREE(info);
        return HC_GEN_ALIAS_FAILED;
    }
    struct uint8_buff sign_message = { info, len, len };
    int32_t ret = sign(&key_alias, &sign_message, signature);
    if (ret != HC_OK) {
        LOGE("Object %u sign failed, error code is %d", sts_client_sn(sts_client), ret);
        FREE(info);
        return HC_SIGN_EXCHANGE_FAILED;
    }

    FREE(info);
    return ret;
}

static int32_t init_auth_data(struct uint8_buff *auth_data)
{
    auth_data->size = HC_AUTH_DATA_BUFF_LEN;
    auth_data->val = (uint8_t *)MALLOC(auth_data->size);
    if (auth_data->val == NULL) {
        LOGE("Malloc failed");
        return HC_MALLOC_FAILED;
    }
    auth_data->length = 0;
    (void)memset_s(auth_data->val, auth_data->size, 0, auth_data->size);
    return HC_OK;
}

static int32_t init_signature(void *handle, struct signature *signature)
{
    struct sts_client *sts_client = (struct sts_client *)handle;
    struct aes_aad aes_aad;

    if (memcpy_s(aes_aad.aad, sizeof(aes_aad.aad), sts_client->my_challenge.challenge,
                 sts_client->my_challenge.length) != EOK) {
        return memory_copy_error(__func__, __LINE__);
    }

    aes_aad.length = sts_client->my_challenge.length;

    struct uint8_buff out_plain = { 0, 0, 0 };

    out_plain.val = (uint8_t *)MALLOC(sts_client->peer_auth_data.length);
    if (out_plain.val == NULL) {
        LOGE("Malloc peer_auth_data failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(out_plain.val, sts_client->peer_auth_data.length, 0, sts_client->peer_auth_data.length);
    out_plain.size = sts_client->peer_auth_data.length;

    struct uint8_buff auth_data = {sts_client->peer_auth_data.auth_data, sts_client->peer_auth_data.length,
                                   sts_client->peer_auth_data.length};

    int32_t ret = aes_gcm_decrypt((struct var_buffer *)&sts_client->session_key, &auth_data, &aes_aad, &out_plain);
    if (ret != HC_OK) {
        FREE(out_plain.val);
        LOGE("Object %u aes_gcm_decrypt failed, error code is %d", sts_client_sn(sts_client), ret);
        return HC_DECRYPT_FAILED;
    }

    if (memcpy_s(signature->signature, sizeof(signature->signature), out_plain.val, out_plain.length) != EOK) {
        FREE(out_plain.val);
        return memory_copy_error(__func__, __LINE__);
    }
    signature->length = out_plain.length;
    FREE(out_plain.val);
    return HC_OK;
}

static int32_t verify_data(void *handle)
{
    struct signature signature = { 0, {0} };
    int32_t ret = init_signature(handle, &signature);
    if (ret != HC_OK) {
        return ret;
    }

    struct uint8_buff message;
    (void)memset_s(&message, sizeof(message), 0, sizeof(message));
    ret = generate_sign_message(handle, &message);
    if (ret != HC_OK) {
        return ret;
    }

    ret = verify_response_data(handle, &message, &signature);
    FREE(message.val);
    message.val = NULL;
    if (ret != HC_OK) {
        return ret;
    }
    return HC_OK;
}

static int32_t build_end_request_data(void *handle, void *data)
{
    struct sts_client *sts_client = (struct sts_client *)handle;
    struct sts_end_request_data *send = (struct sts_end_request_data *)data;

    int32_t ret = verify_data(handle);
    if (ret != HC_OK) {
        return ret;
    }

    struct signature request_sign = { 0, {0} };
    ret = generate_sts_request_sign(handle, &request_sign);
    if (ret != HC_OK) {
        return ret;
    }

    struct uint8_buff out_auth_data;
    ret = init_auth_data(&out_auth_data);
    if (ret != HC_OK) {
        return ret;
    }

    struct aes_aad aes_aad;
    if (memcpy_s(aes_aad.aad, sizeof(aes_aad.aad), sts_client->peer_challenge.challenge,
        sts_client->peer_challenge.length) != EOK) {
        FREE(out_auth_data.val);
        return memory_copy_error(__func__, __LINE__);
    }
    aes_aad.length = sts_client->peer_challenge.length;

    struct uint8_buff plain = {request_sign.signature, request_sign.length, request_sign.length};
    ret = aes_gcm_encrypt((struct var_buffer *)&sts_client->session_key, &plain, &aes_aad, &out_auth_data);
    if (ret != HC_OK) {
        FREE(out_auth_data.val);
        LOGE("Object %u aes_gcm_encrypt failed, error code is %d", sts_client_sn(sts_client), ret);
        return HC_ENCRYPT_FAILED;
    }

    if (memcpy_s(send->auth_data.auth_data, sizeof(send->auth_data.auth_data),
        out_auth_data.val, out_auth_data.length) != EOK) {
        FREE(out_auth_data.val);
        return memory_copy_error(__func__, __LINE__);
    }
    send->auth_data.length = out_auth_data.length;
    FREE(out_auth_data.val);

    return HC_OK;
}

static int32_t parse_end_response_data(void *handle, void *data)
{
    struct sts_client *sts_client = (struct sts_client *)handle;
    struct sts_end_response_data *receive = (struct sts_end_response_data *)data;

    struct uint8_buff auth_ret;
    (void)memset_s(&auth_ret, sizeof(auth_ret), 0, sizeof(auth_ret));
    auth_ret.val = (uint8_t *)MALLOC(receive->auth_return.length);
    if (auth_ret.val == NULL) {
        LOGE("Malloc auth_ret.val failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(auth_ret.val, receive->auth_return.length, 0, receive->auth_return.length);
    auth_ret.size = receive->auth_return.length;

    struct aes_aad aes_aad;
    if (memcpy_s(aes_aad.aad, sizeof(aes_aad.aad), sts_client->my_challenge.challenge,
        sts_client->my_challenge.length) != EOK) {
        FREE(auth_ret.val);
        return memory_copy_error(__func__, __LINE__);
    }
    aes_aad.length = sts_client->peer_challenge.length;
    struct uint8_buff cipher = { receive->auth_return.auth_return,
                                 receive->auth_return.length, receive->auth_return.length };

    int32_t ret = aes_gcm_decrypt((struct var_buffer *)&sts_client->session_key, &cipher, &aes_aad, &auth_ret);
    if (ret != HC_OK) {
        FREE(auth_ret.val);
        LOGE("Object %u aes_gcm_encrypt failed, error code is %d", sts_client_sn(sts_client), ret);
        return false;
    }
    FREE(auth_ret.val);
    generate_output_key(sts_client);

    return ret;
}

int32_t send_sts_start_request(struct sts_client *sts_client, struct message *send)
{
    check_ptr_return_val(sts_client, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    struct sts_start_request_data *send_data =
        (struct sts_start_request_data *)MALLOC(sizeof(struct sts_start_request_data));
    if (send_data == NULL) {
        LOGE("Malloc struct STS_START_REQUEST_DATA failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(send_data, sizeof(*send_data), 0, sizeof(*send_data));

    int32_t ret = send_start_request(sts_client, send_data);
    if (ret != HC_OK) {
        LOGE("Called send_start_request failed, error code is %d", ret);
        FREE(send_data);
        send->msg_code = INFORM_MESSAGE;
    } else {
        DBG_OUT("Called send_start_request success");
        send->msg_code = AUTH_START_REQUEST;
        send->payload = send_data;
    }

    return ret;
}

int32_t send_sts_end_request(struct sts_client *sts_client, const struct message *receive, struct message *send)
{
    DBG_OUT("Receive data send_sts_start_response");
    check_ptr_return_val(sts_client, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    struct sts_start_response_data *receive_data = (struct sts_start_response_data *)receive->payload;

    struct sts_end_request_data *send_data =
        (struct sts_end_request_data *)MALLOC(sizeof(struct sts_end_request_data));
    if (send_data == NULL) {
        LOGE("Malloc struct STS_END_REQUEST_DATA failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(send_data, sizeof(*send_data), 0, sizeof(*send_data));

    int32_t ret = send_end_request(sts_client, receive_data, send_data);
    if (ret != HC_OK) {
        LOGE("Called send_end_request failed, error code is %d", ret);
        FREE(send_data);
        send->msg_code = INFORM_MESSAGE;
    } else {
        DBG_OUT("Called send_end_request success");
        send->msg_code = AUTH_ACK_REQUEST;
        send->payload = send_data;
    }

    return ret;
}

int32_t receive_sts_end_response(struct sts_client *sts_client, struct message *receive)
{
    DBG_OUT("Receive sts end response data");
    check_ptr_return_val(sts_client, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    struct sts_end_response_data *receive_data = (struct sts_end_response_data *)receive->payload;
    int32_t ret = receive_end_response(sts_client, receive_data);
    if (ret != HC_OK) {
        LOGE("Called receive_end_response failed, error code is %d", ret);
        receive->msg_code = INFORM_MESSAGE;
    } else {
        DBG_OUT("Called receive_end_response success");
        receive->msg_code = AUTH_ACK_RESPONSE;
        receive->payload = receive_data;
    }

    return ret;
}

static void generate_output_key(struct sts_client *sts_client)
{
    DBG_OUT("Start sts_client generate output key");
    int32_t ret = compute_hkdf((struct var_buffer *)&sts_client->session_key,
                               &sts_client->salt,
                               HICHAIN_RETURN_KEY,
                               sts_client->key_length,
                               (struct var_buffer *)&sts_client->service_key);
    if (ret != HC_OK) {
        LOGE("Object %u generate output key failed, error code is %d", sts_client_sn(sts_client), ret);
        return;
    } else {
        DBG_OUT("Sts client generate output key success");
        return;
    }
}

#else /* _CUT_XXX_ */
struct sts_client *build_sts_client(const hc_handle hichain_handle, uint32_t key_length,
    const struct hc_auth_id *client, const struct hc_auth_id *server)
{
    (void)hichain_handle;
    (void)key_length;
    (void)client;
    (void)server;
    return NULL;
}

void destroy_sts_client(struct sts_client *handle)
{
    (void)handle;
    return;
}

#endif /* _CUT_XXX_ */

