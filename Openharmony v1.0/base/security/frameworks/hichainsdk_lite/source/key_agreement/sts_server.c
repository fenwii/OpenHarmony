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

#include "sts_server.h"
#include "log.h"

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_))

#include <securec.h>
#include "commonutil.h"
#include "distribution.h"
#include "mem_stat.h"
#include "huks_adapter.h"

#ifdef DESC
#undef DESC
#endif
#define DESC(...) 1

#define HC_STS_REQUEST_LEN  256
#define HC_STS_RESPONSE_LEN 256

static int32_t parse_start_request_data(void *handle, void *receive_data);
static int32_t build_start_response_data(void *handle, void *send_data);
static int32_t parse_end_request_data(void *handle, void *receive_data);
static int32_t build_end_response_data(void *handle, void *send_data);

struct sts_server *build_sts_server(const hc_handle hichain_handle, uint32_t key_length,
    const struct hc_auth_id *client, const struct hc_auth_id *server)
{
    struct sts_server *sts_server = (struct sts_server *)MALLOC(sizeof(struct sts_server));
    if (sts_server == NULL) {
        LOGE("Build sts server object failed");
        return NULL;
    }
    (void)memset_s(sts_server, sizeof(*sts_server), 0, sizeof(*sts_server));
    const struct server_virtual_func_group funcs = { parse_start_request_data, build_start_response_data,
                                                     parse_end_request_data, build_end_response_data };

    init_server(&sts_server->server_info, &funcs);
    LOGI("Build sts server object %u success", sts_server_sn(sts_server));
    sts_server->self_id = *server;
    sts_server->peer_id = *client;
    sts_server->identity = &((struct hichain *)hichain_handle)->identity;
    sts_server->key_length = key_length;
    sts_server->hichain_handle = hichain_handle;
    sts_server->start_request = 0;
    sts_server->ack_request = 0;
    return sts_server;
}

void destroy_sts_server(struct sts_server *handle)
{
    if (handle == NULL) {
        DBG_OUT("Destroy sts server object failed");
        return;
    }

    FREE(handle);
    LOGI("FREE sts server object success");
}

int32_t send_sts_start_response(struct sts_server *handle, struct message *receive, struct message *send)
{
    DBG_OUT("Called send sts start response");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    int32_t ret = HC_OK;
    struct sts_start_response_data *send_data =
        (struct sts_start_response_data *)MALLOC(sizeof(struct sts_start_response_data));

    if (send_data == NULL) {
        LOGE("Malloc struct sts_start_request_data failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(send_data, sizeof(*send_data), 0, sizeof(*send_data));

    if (handle->start_request == 0) {
        struct sts_start_request_data *receive_data = receive->payload;
        ret = send_start_response(handle, receive_data, send_data);
        if (ret != HC_OK) {
            LOGE("Called send_start_response failed, error code is %d", ret);
            FREE(send_data);
            send_data = NULL;
            send->msg_code = INFORM_MESSAGE;
        } else {
            DBG_OUT("Called send_start_response success");
            send->msg_code = AUTH_START_RESPONSE;
            send->payload = send_data;
            handle->start_request = 1;
            (void)memcpy_s(&handle->start_response_data, sizeof(struct sts_start_response_data),
                           send_data, sizeof(struct sts_start_response_data));
        }
    } else {
        DBG_OUT("Called send_start_response again");
        send->msg_code = AUTH_START_RESPONSE;
        (void)memcpy_s(send_data, sizeof(struct sts_start_response_data),
                       &handle->start_response_data, sizeof(struct sts_start_response_data));
        send->payload = send_data;
    }

    return ret;
}

int32_t send_sts_end_response(struct sts_server *handle, struct message *receive, struct message *send)
{
    DBG_OUT("Called send sts end response");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    int32_t ret = HC_OK;
    struct sts_end_response_data *send_data =
        (struct sts_end_response_data *)MALLOC(sizeof(struct sts_end_response_data));

    if (send_data == NULL) {
        LOGE("Malloc struct sts_end_response_data failed");
        send->msg_code = INFORM_MESSAGE;
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(send_data, sizeof(*send_data), 0, sizeof(*send_data));

    if (handle->ack_request == 0) {
        struct sts_end_request_data *receive_data = receive->payload;
        ret = send_end_response(handle, receive_data, send_data);
        if (ret != HC_OK) {
            LOGE("Called send_end_response failed, error code is %d", ret);
            FREE(send_data);
            send_data = NULL;
            send->msg_code = INFORM_MESSAGE;
        } else {
            DBG_OUT("Called send_end_response success");
            send->msg_code = AUTH_ACK_RESPONSE;
            send->payload = send_data;
            handle->ack_request = 1;
            (void)memcpy_s(&handle->end_response_data, sizeof(struct sts_end_response_data),
                           send_data, sizeof(struct sts_end_response_data));
        }
    } else {
        DBG_OUT("Called send sts end response again");
        send->msg_code = AUTH_ACK_RESPONSE;
        (void)memcpy_s(send_data, sizeof(struct sts_end_response_data),
                       &handle->end_response_data, sizeof(struct sts_end_response_data));
        send->payload = send_data;
    }
    return ret;
}

static int32_t parse_start_request_data(void *handle, void *receive_data)
{
    DBG_OUT("Called parse start request data");
    struct sts_server *sts_server = handle;
    struct sts_start_request_data *auth_start_req = receive_data;

    DBG_OUT("Object %u begin parse PAKE start request data", sts_server_sn(sts_server));
    if (!is_peer_support_current_version(&auth_start_req->peer_version, &auth_start_req->peer_support_version)) {
        LOGE("Object %u peer is not support current version", sts_server_sn(sts_server));
        return HC_VERSION_UNSUPPORT;
    }

    sts_server->peer_challenge = auth_start_req->challenge;
    sts_server->peer_public_key = auth_start_req->epk;
    sts_server->peer_user_type = auth_start_req->peer_user_type;

    if (sts_server->server_info.protocol_base_info.state == PROTOCOL_INIT) {
        struct st_key_pair key_pair;
        int32_t ret = generate_st_key_pair(&key_pair);
        if (ret != HC_OK) {
            LOGE("Object %u generate_st_key_pair failed, error code is %d", sts_server_sn(sts_server), ret);
            return HC_ST_KEY_PAIR_FAILED;
        }
        sts_server->self_public_key = key_pair.st_public_key;
        sts_server->self_private_key = key_pair.st_private_key;

        struct random_value salt = generate_random(CHALLENGE_BUFF_LENGTH);
        if (salt.length == 0) {
            LOGE("Generate random value failed");
            return HC_GEN_RANDOM_FAILED;
        }
        if (memcpy_s(sts_server->salt.salt, sizeof(sts_server->salt.salt), salt.random_value, salt.length) != EOK) {
            return memory_copy_error(__func__, __LINE__);
        }
        sts_server->salt.length = salt.length;
    }

    struct sts_shared_secret shared_secret;

    int32_t ret = compute_sts_shared_secret(&sts_server->self_private_key, &sts_server->peer_public_key,
                                            &shared_secret);
    if (ret != HC_OK) {
        LOGE("Object %u compute_shared_secret failed, error code is %d", sts_server_sn(sts_server), ret);
        return HC_COMPUTE_STS_SHARED_SECRET_FAILED;
    }

    ret = compute_hkdf((struct var_buffer *)&shared_secret, &sts_server->salt, HICHAIN_AUTH_INFO,
        STS_SESSION_KEY_LENGTH, (struct var_buffer *)&sts_server->session_key);
    if (ret != HC_OK) {
        LOGE("Object %u compute_hkdf failed, error code is %d", sts_server_sn(sts_server), ret);
        return HC_COMPUTE_HKDF_FAILED;
    }
    LOGI("Called parse start request data success!");
    return HC_OK;
}

static int32_t generate_sts_response_sign(void *handle, struct signature *signature)
{
    struct sts_server *sts_server = handle;
    int32_t len = sts_server->self_public_key.length + sts_server->self_id.length +
                  sts_server->peer_public_key.length + sts_server->peer_id.length;
    uint8_t *info2 = (uint8_t *)MALLOC(len);
    if (info2 == NULL) {
        LOGE("Malloc failed");
        return HC_MALLOC_FAILED;
    }
    int32_t pos = 0;

    (void)memcpy_s(info2 + pos, len - pos, sts_server->self_public_key.stpk, sts_server->self_public_key.length);
    pos += sts_server->self_public_key.length;
    (void)memcpy_s(info2 + pos, len - pos, sts_server->self_id.auth_id, sts_server->self_id.length);
    pos += sts_server->self_id.length;
    (void)memcpy_s(info2 + pos, len - pos, sts_server->peer_public_key.stpk, sts_server->peer_public_key.length);
    pos += sts_server->peer_public_key.length;
    (void)memcpy_s(info2 + pos, len - pos, sts_server->peer_id.auth_id, sts_server->peer_id.length);

    struct service_id service_id = generate_service_id(sts_server->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        FREE(info2);
        return HC_GEN_SERVICE_ID_FAILED;
    }
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
    struct hc_key_alias key_alias = generate_key_alias(&service_id, &sts_server->self_id, KEY_ALIAS_LT_KEY_PAIR);
#else
    struct hc_key_alias key_alias = generate_key_alias(&service_id, &sts_server->self_id, KEY_ALIAS_ACCESSOR_PK);
#endif
    if (key_alias.length == 0) {
        LOGE("Generate key alias failed");
        FREE(info2);
        return HC_GEN_ALIAS_FAILED;
    }
    struct uint8_buff sign_message = { info2, len, len };
    int32_t ret = sign(&key_alias, &sign_message, signature);

    FREE(info2);
    return ret;
}

static void auth_start_response_fill(const struct sts_server *srv, struct sts_start_response_data *auth_start_res)
{
    auth_start_res->challenge = srv->my_challenge;
    auth_start_res->salt = srv->salt;
    auth_start_res->epk = srv->self_public_key;
    auth_start_res->self_version = get_current_version();
    auth_start_res->self_support_version = get_current_version();
    auth_start_res->self_auth_id = srv->self_id;
    auth_start_res->peer_user_type = ((struct hichain *)srv->hichain_handle)->type == HC_CENTRE ?
        HC_USER_TYPE_CONTROLLER : HC_USER_TYPE_ACCESSORY;
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

static int32_t build_start_response_data(void *handle, void *send_data)
{
    struct sts_start_response_data *auth_start_res = send_data;
    struct signature signature;
    int32_t ret = generate_sts_response_sign(handle, &signature);
    struct sts_server *srv = handle;
    if (ret != HC_OK) {
        LOGE("Object %u sign failed, error code is %d", sts_server_sn(srv), ret);
        return HC_SIGN_EXCHANGE_FAILED;
    }

    struct uint8_buff auth_data;
    ret = init_auth_data(&auth_data);
    if (ret != HC_OK) {
        return ret;
    }
    struct aes_aad aes_aad;

    if (memcpy_s(aes_aad.aad, sizeof(aes_aad.aad), srv->peer_challenge.challenge, srv->peer_challenge.length) != EOK) {
        FREE(auth_data.val);
        return memory_copy_error(__func__, __LINE__);
    }
    aes_aad.length = srv->peer_challenge.length;
    struct uint8_buff plain = { signature.signature, signature.length, signature.length };

    ret = aes_gcm_encrypt((struct var_buffer *)&srv->session_key, &plain, &aes_aad, &auth_data);
    if (ret != HC_OK) {
        FREE(auth_data.val);
        LOGE("Object %u aes_gcm_encrypt failed, error code is %d", sts_server_sn(srv), ret);
        return HC_ENCRYPT_FAILED;
    }

    if (memcpy_s(auth_start_res->auth_data.auth_data, HC_AUTH_DATA_BUFF_LEN, auth_data.val, auth_data.length) != EOK) {
        FREE(auth_data.val);
        return memory_copy_error(__func__, __LINE__);
    }
    auth_start_res->auth_data.length = auth_data.length;
    if (srv->server_info.protocol_base_info.state == PROTOCOL_INIT) {
        struct random_value random_value = generate_random(CHALLENGE_BUFF_LENGTH);
        if (random_value.length == 0) {
            FREE(auth_data.val);
            return HC_GEN_RANDOM_FAILED;
        }
        if (memcpy_s(srv->my_challenge.challenge, sizeof(srv->my_challenge.challenge),
            random_value.random_value, random_value.length) != EOK) {
            FREE(auth_data.val);
            return memory_copy_error(__func__, __LINE__);
        }
        srv->my_challenge.length = random_value.length;
    }
    auth_start_response_fill(srv, auth_start_res);

    FREE(auth_data.val);
    return HC_OK;
}

static int32_t generate_sign_message(void *handle, struct uint8_buff *message)
{
    DBG_OUT("Called generate sign message");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(message, HC_INPUT_ERROR);
    struct sts_server *sts_server = handle;
    int32_t len = sts_server->peer_public_key.length + sts_server->peer_id.length +
                  sts_server->self_public_key.length + sts_server->self_id.length;
    uint8_t *info1 = (uint8_t *)MALLOC(len);
    if (info1 == NULL) {
        LOGE("Malloc failed");
        return HC_MALLOC_FAILED;
    }
    int32_t pos = 0;

    (void)memcpy_s(info1 + pos, len - pos, sts_server->peer_public_key.stpk, sts_server->peer_public_key.length);
    pos += sts_server->peer_public_key.length;
    (void)memcpy_s(info1 + pos, len - pos, sts_server->peer_id.auth_id, sts_server->peer_id.length);
    pos += sts_server->peer_id.length;
    (void)memcpy_s(info1 + pos, len - pos, sts_server->self_public_key.stpk, sts_server->self_public_key.length);
    pos += sts_server->self_public_key.length;
    (void)memcpy_s(info1 + pos, len - pos, sts_server->self_id.auth_id, sts_server->self_id.length);

    message->val = info1;
    message->length = len;
    message->size = len;
    return HC_OK;
}

static int32_t verify_request_data(void *handle, const struct uint8_buff *message, struct signature *signature)
{
    DBG_OUT("Called verify request data");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(message, HC_INPUT_ERROR);
    check_ptr_return_val(signature, HC_INPUT_ERROR);
    struct sts_server *sts_server = handle;
    struct service_id service_id = generate_service_id(sts_server->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        return HC_GEN_SERVICE_ID_FAILED;
    }

    struct hichain *hichain_handle = sts_server->hichain_handle;
    enum huks_key_alias_type alias_type;

    if (hichain_handle->type == HC_CENTRE) {
        struct hc_pin pin = { 0, {0} };
        struct operation_parameter para;
        (void)memset_s(&para, sizeof(para), 0, sizeof(para));
        hichain_handle->cb.get_protocol_params(&hichain_handle->identity, GET_PEER_USER_TYPE, &pin, &para);
        int32_t flag = sts_server->peer_user_type;
        if (flag == PEER_USER_TYPE_EMPTY) {
            sts_server->peer_user_type = para.key_length;
        }
        if (para.key_length == PEER_USER_TYPE_ACCESSORY) {
            sts_server->peer_user_type = HC_USER_TYPE_ACCESSORY;
        }

        if (sts_server->peer_user_type == HC_USER_TYPE_CONTROLLER) {
            if (memcmp(sts_server->peer_id.auth_id, sts_server->self_id.auth_id, sts_server->peer_id.length) == 0) {
                alias_type = KEY_ALIAS_LT_KEY_PAIR; /* center(as phone identity) -> phone */
            } else {
                alias_type = KEY_ALIAS_CONTROLLER_PK; /* center -> phone (other identity) */
            }
        } else {
            alias_type = KEY_ALIAS_ACCESSOR_PK; /* center -> accessory */
        }
    } else {
        alias_type = KEY_ALIAS_CONTROLLER_PK; /* accessory -> center/phone */
    }
    struct hc_key_alias key_alias = generate_key_alias(&service_id, &sts_server->peer_id, alias_type);
    if (key_alias.length == 0) {
        LOGE("Generate key alias failed");
        return HC_GEN_ALIAS_FAILED;
    }
    int32_t ret = verify(&key_alias, sts_server->peer_user_type, message, signature);
    if (ret != HC_OK) {
        LOGE("Object %u verify failed, error code is %d", sts_server_sn(sts_server), ret);
        return HC_VERIFY_PROOF_FAILED;
    }
    return HC_OK;
}

static int32_t decrypt_request_message(void *handle, struct sts_end_request_data *request_data,
    struct uint8_buff *out_plain)
{
    DBG_OUT("Called decrypt request message");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(request_data, HC_INPUT_ERROR);

    struct sts_server *sts_server = handle;
    struct aes_aad aes_aad;

    if (memcpy_s(aes_aad.aad, sizeof(aes_aad.aad), sts_server->my_challenge.challenge,
        sts_server->my_challenge.length) != EOK) {
        return memory_copy_error(__func__, __LINE__);
    }
    aes_aad.length = sts_server->my_challenge.length;
    struct uint8_buff auth_data = {
        .val = request_data->auth_data.auth_data,
        .length = request_data->auth_data.length,
        .size = request_data->auth_data.length
    };
    int32_t ret = aes_gcm_decrypt((struct var_buffer *)&sts_server->session_key, &auth_data, &aes_aad, out_plain);

    return ret;
}

static int32_t parse_end_request_data(void *handle, void *receive_data)
{
    DBG_OUT("Called parse end request data");
    struct sts_server *sts_server = handle;
    struct sts_end_request_data *auth_ack_request = receive_data;
    struct uint8_buff out_plain;

    out_plain.val = (uint8_t *)MALLOC(HC_STS_REQUEST_LEN);
    if (out_plain.val == NULL) {
        LOGE("Malloc failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(out_plain.val, HC_STS_REQUEST_LEN, 0, HC_STS_REQUEST_LEN);
    out_plain.size = HC_STS_REQUEST_LEN;
    out_plain.length = 0;

    int32_t ret = decrypt_request_message(handle, auth_ack_request, &out_plain);
    if (ret != HC_OK) {
        FREE(out_plain.val);
        LOGE("Object %u aes_gcm_decrypt failed, error code is %d", sts_server_sn(sts_server), ret);
        return HC_DECRYPT_FAILED;
    }

    struct signature signature;

    if (memcpy_s(signature.signature, sizeof(signature.signature), out_plain.val, out_plain.length) != EOK) {
        FREE(out_plain.val);
        return memory_copy_error(__func__, __LINE__);
    }
    signature.length = out_plain.length;
    FREE(out_plain.val);
    struct uint8_buff message;

    (void)memset_s(&message, sizeof(message), 0, sizeof(message));
    ret = generate_sign_message(handle, &message);
    if (ret != HC_OK) {
        return HC_MALLOC_FAILED;
    }
    ret = verify_request_data(handle, &message, &signature);
    FREE(message.val);
    message.val = NULL;
    if (ret != HC_OK) {
        LOGE("Object %u verify failed, error code is %d", sts_server_sn(sts_server), ret);
        return HC_VERIFY_PROOF_FAILED;
    }
    LOGI("Called parse end request data success!");
    (void)sts_server;
    return HC_OK;
}

static void generate_output_key(struct sts_server *sts_server);
static int32_t build_end_response_data(void *handle, void *send_data)
{
    DBG_OUT("Called build end response_data");
    struct sts_server *sts_server = handle;
    struct sts_end_response_data *auth_start_response = send_data;
    struct uint8_buff auth_ret;

    auth_ret.size = HC_STS_RESPONSE_LEN;
    auth_ret.val = (uint8_t *)MALLOC(auth_ret.size);
    if (auth_ret.val == NULL) {
        LOGE("Malloc failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(auth_ret.val, auth_ret.size, 0, auth_ret.size);
    auth_ret.length = 0;

    struct aes_aad aes_aad;
    if (memcpy_s(aes_aad.aad, sizeof(aes_aad.aad), sts_server->peer_challenge.challenge,
        sts_server->peer_challenge.length) != EOK) {
        FREE(auth_ret.val);
        return memory_copy_error(__func__, __LINE__);
    }
    aes_aad.length = sts_server->peer_challenge.length;
    struct uint8_buff ret_code;
    ret_code.val = (uint8_t *)MALLOC(sizeof(uint8_t));
    if (ret_code.val == NULL) {
        FREE(auth_ret.val);
        LOGE("Malloc failed");
        return HC_MALLOC_FAILED;
    }
    ret_code.length = 1;
    ret_code.size = 1;
    ret_code.val[0] = 0;

    int32_t ret = aes_gcm_encrypt((struct var_buffer *)&sts_server->session_key, &ret_code, &aes_aad, &auth_ret);
    FREE(ret_code.val);
    if (ret != HC_OK) {
        FREE(auth_ret.val);
        LOGE("Object %u aes_gcm_encrypt failed, err code is %d", sts_server_sn(sts_server), ret);
        return HC_ENCRYPT_FAILED;
    }
    generate_output_key(sts_server);
    if (memcpy_s(auth_start_response->auth_return.auth_return, sizeof(auth_start_response->auth_return.auth_return),
        auth_ret.val, auth_ret.length) != EOK) {
        FREE(auth_ret.val);
        return memory_copy_error(__func__, __LINE__);
    }
    auth_start_response->auth_return.length = auth_ret.length;
    FREE(auth_ret.val);

    LOGI("Called build end response data success!");
    return HC_OK;
}

static void generate_output_key(struct sts_server *sts_server)
{
    DBG_OUT("sts_server generate output key");
    int32_t ret = compute_hkdf((struct var_buffer *)&sts_server->session_key, &sts_server->salt, HICHAIN_RETURN_KEY,
                               sts_server->key_length, (struct var_buffer *)&sts_server->service_key);
    if (ret != HC_OK) {
        LOGE("Object %u generate output key failed, error code is %d", sts_server_sn(sts_server), ret);
    }
}

#else /* _CUT_XXX_ */

#include "mem_stat.h"

struct sts_server *build_sts_server(const hc_handle hichain_handle, uint32_t key_length,
    const struct hc_auth_id *client, const struct hc_auth_id *server)
{
    LOGE("Donot support sts protocol");
    (void)hichain_handle;
    (void)key_length;
    (void)client;
    (void)server;
    return (struct sts_server *)MALLOC(sizeof(struct sts_server));
}

void destroy_sts_server(struct sts_server *handle)
{
    LOGE("Donot support sts protocol");
    FREE(handle);
}

#endif /* _CUT_XXX_ */
