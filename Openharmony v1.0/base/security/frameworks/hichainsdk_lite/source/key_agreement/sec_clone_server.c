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

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))

#include "sec_clone_server.h"
#include <stdlib.h>
#include <string.h>
#include <securec.h>
#include "hks_client.h"
#include "huks_adapter.h"
#include "log.h"
#include "commonutil.h"
#include "distribution.h"
#include "hichain.h"

#define MAX_ITER_COUNT 10

const char *SEC_CLONE_SRV_PROOF_STR = "hichain_sec_clone_server_proof";
const char *SEC_CLONE_CHALLENGE_STR = "hichain_sec_clone_challenge";
const char *SEC_CLONE_CLONE_STR = "hichain_sec_clone_clone_data";
const char *SEC_CLONE_SEC_RESULT_STR = "hichain_sec_clone_result";

const int32_t SEC_CLONE_START_RESP_DATA_SIZE = 9216;
const int32_t SEC_CLONE_CERT_CHAIN_SIZE = 9216;

const char *CERT_NUM = "certs";
const char *CERT_LEVEL_1 = "cert1";
const char *CERT_LEVEL_2 = "cert2";
const char *CERT_LEVEL_3 = "cert3";
const char *CERT_LEVEL_4 = "cert4";

const int32_t CERT_CHAIN_NUM = 4;

static int32_t parse_start_request_data(void *handle, void *data);
static int32_t build_start_response_data(void *handle, void *data);
static int32_t parse_end_request_data(void *handle, void *data);
static int32_t build_end_response_data(void *handle, void *data);

struct sec_clone_server *build_sec_clone_server(hc_handle hichain)
{
    struct hichain *hichain_ins = (struct hichain *)hichain;
    if (hichain_ins->sts_server == NULL) {
        LOGE("Sts server is null");
        return NULL;
    }

    struct sec_clone_server *server = (struct sec_clone_server *)MALLOC(sizeof(struct sec_clone_server));
    if (server == NULL) {
        LOGE("Build sec clone server object failed");
        return NULL;
    }

    (void)memset_s(server, sizeof(*server), 0, sizeof(*server));
    struct server_virtual_func_group funcs = { parse_start_request_data,
                                               build_start_response_data,
                                               parse_end_request_data,
                                               build_end_response_data };

    init_server(&server->server_info, &funcs);
    server->hichain_handle = hichain;
    server->need_clean_temp_key = false;

    return server;
}

static void clear_temp_key(struct hc_key_alias *temp_key_alias)
{
    int32_t ret = check_lt_public_key_exist(temp_key_alias);
    if (ret != HC_OK) {
        LOGE("temp key is not exist");
        return;
    }

    ret = delete_lt_public_key(temp_key_alias);
    if (ret != HC_OK) {
        LOGE("delete temp key failed");
    }
}

void destroy_sec_clone_server(struct sec_clone_server *handle)
{
    if (handle == NULL) {
        return;
    }

    if (handle->start_request_data.val != NULL) {
        FREE(handle->start_request_data.val);
        handle->start_request_data.val = NULL;
    }

    if (handle->client_sec_data.val != NULL) {
        FREE(handle->client_sec_data.val);
        handle->client_sec_data.val = NULL;
    }

    if (handle->need_clean_temp_key) {
        struct hc_key_alias *temp_key_alias = &(handle->cert_key_alias);
        clear_temp_key(temp_key_alias);
        handle->need_clean_temp_key = false;
    }

    FREE(handle);
}

int32_t send_sec_clone_start_response(struct sec_clone_server *sec_clone_server,
    const struct message *receive, struct message *send)
{
    check_ptr_return_val(sec_clone_server, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    struct uint8_buff *receive_data = (struct uint8_buff *)receive->payload;
    struct uint8_buff *send_data = (struct uint8_buff *)MALLOC(sizeof(struct uint8_buff));
    if (send_data == NULL) {
        LOGE("Malloc struct send_data failed");
        return HC_MALLOC_FAILED;
    }

    int32_t send_data_size = SEC_CLONE_START_RESP_DATA_SIZE;

    send_data->val = (uint8_t *)MALLOC(send_data_size);
    if (send_data->val == NULL) {
        LOGE("Malloc send data failed");
        FREE(send_data);
        return HC_MALLOC_FAILED;
    }
    send_data->size = send_data_size;
    send_data->length = send_data_size;
    int32_t ret = send_start_response(sec_clone_server, receive_data, send_data);
    if (ret != HC_OK) {
        LOGE("Called send_start_response failed, error code is %d", ret);
        FREE(send_data->val);
        send_data->val = NULL;
        FREE(send_data);
        send->msg_code = INFORM_MESSAGE;
    } else {
        LOGI("Called send_start_response success");
        send->msg_code = SEC_CLONE_START_RESPONSE;
        send->payload = send_data;
    }

    return ret;
}

int32_t send_sec_clone_end_response(struct sec_clone_server *sec_clone_server,
    const struct message *receive, struct message *send)
{
    LOGI("Called send_sec_clone_end_response start");
    check_ptr_return_val(sec_clone_server, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    struct uint8_buff *receive_data = (struct uint8_buff *)receive->payload;
    struct uint8_buff *send_data = (struct uint8_buff *)MALLOC(sizeof(struct uint8_buff));
    if (send_data == NULL) {
        LOGE("Malloc struct UINT8_BUFF failed");
        send->msg_code = INFORM_MESSAGE;
        return HC_MALLOC_FAILED;
    }

    int32_t send_data_size = sizeof(int32_t) + HKS_ENCRYPT_MAX_TAG_SIZE;

    send_data->val = (uint8_t *)MALLOC(send_data_size);
    if (send_data->val == NULL) {
        send->msg_code = INFORM_MESSAGE;
        FREE(send_data);
        return HC_MALLOC_FAILED;
    }
    send_data->size = send_data_size;
    send_data->length = send_data_size;

    int32_t ret = send_end_response(sec_clone_server, receive_data, send_data);
    if (ret != HC_OK) {
        LOGE("Called send_end_response failed, error code is %d", ret);
        if (send_data->val != NULL) {
            FREE(send_data->val);
            send_data->val = NULL;
        }
        FREE(send_data);
        send->msg_code = INFORM_MESSAGE;
    } else {
        LOGI("Called send_end_response success");
        send->msg_code = SEC_CLONE_ACK_RESPONSE;
        send->payload = send_data;
    }

    return ret;
}

static int32_t sec_clone_combine_challenge(struct sec_clone_server *sec_clone_server,
    struct uint8_buff *challenge_out)
{
    struct uint8_buff *recv_challenge = &sec_clone_server->start_request_data;
    struct hichain *hichain = (struct hichain *)sec_clone_server->hichain_handle;
    struct sts_server *sts_server = hichain->sts_server;
    struct challenge *challenge_c = &sts_server->peer_challenge;
    struct challenge *challenge_s = &sts_server->my_challenge;

    challenge_out->size = CHALLENGE_BUFF_LENGTH * BYTE_TO_HEX_OPER_LENGTH + recv_challenge->length;
    challenge_out->val = (uint8_t *)MALLOC(challenge_out->size);
    if (challenge_out->val == NULL) {
        LOGE("Object MALLOC generate buffer failed");
        return HC_BUILD_OBJECT_FAILED;
    }

    if (memcpy_s(challenge_out->val, challenge_out->size, recv_challenge->val, recv_challenge->length) != EOK) {
        FREE(challenge_out->val);
        challenge_out->val = NULL;
        return memory_copy_error(__func__, __LINE__);
    }
    challenge_out->length = recv_challenge->length;

    if (memcpy_s(challenge_out->val + challenge_out->length, challenge_out->size - challenge_out->length,
        challenge_c->challenge, challenge_c->length) != EOK) {
        FREE(challenge_out->val);
        challenge_out->val = NULL;
        return memory_copy_error(__func__, __LINE__);
    }
    challenge_out->length += CHALLENGE_BUFF_LENGTH;

    if (memcpy_s(challenge_out->val + challenge_out->length, challenge_out->size - challenge_out->length,
        challenge_s->challenge, challenge_s->length) != EOK) {
        FREE(challenge_out->val);
        challenge_out->val = NULL;
        return memory_copy_error(__func__, __LINE__);
    }
    challenge_out->length += CHALLENGE_BUFF_LENGTH;

    return HC_OK;
}

static int32_t sec_clone_gen_srv_proof(struct uint8_buff *certificate_chain,
    struct uint8_buff *out_srv_proof)
{
    struct uint8_buff cert_str;
    cert_str.val = (uint8_t *)MALLOC(SEC_CLONE_CERT_CHAIN_SIZE);
    if (cert_str.val == NULL)
        return HC_MALLOC_FAILED;

    (void)memset_s(cert_str.val, SEC_CLONE_CERT_CHAIN_SIZE, 0, SEC_CLONE_CERT_CHAIN_SIZE);
    if (snprintf_s((char *)cert_str.val, SEC_CLONE_CERT_CHAIN_SIZE, SEC_CLONE_CERT_CHAIN_SIZE - 1,
        "{\"%s\":%d,\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}", CERT_NUM, CERT_CHAIN_NUM,
        CERT_LEVEL_1, certificate_chain[0].val, CERT_LEVEL_2, certificate_chain[1].val,
        CERT_LEVEL_3, certificate_chain[2].val, CERT_LEVEL_4, certificate_chain[3].val) < 0) {
        LOGE("String generate failed");
        FREE(cert_str.val);
        cert_str.val = NULL;
        return HC_BUILD_SEND_DATA_FAILED;
    }
    cert_str.length = strlen((char *)cert_str.val);
    LOGI("%d, cert_str.length: %d", __LINE__, cert_str.length);
    LOGI("%d, strlen(cert_str.val): %d", __LINE__, strlen((const char *)cert_str.val));

    out_srv_proof->val = cert_str.val;
    out_srv_proof->length = strlen((const char *)cert_str.val);
    out_srv_proof->size = strlen((const char *)cert_str.val);

    return HC_OK;
}

static int32_t parse_start_request_data(void *handle, void *data)
{
    struct sec_clone_server *sec_clone_server = (struct sec_clone_server *)handle;
    struct uint8_buff *src_data = (struct uint8_buff *)data;
    struct hichain *hichain = (struct hichain *)sec_clone_server->hichain_handle;
    struct aes_aad aes_aad;

    if (memcpy_s(aes_aad.aad, sizeof(aes_aad.aad), SEC_CLONE_CHALLENGE_STR, strlen(SEC_CLONE_CHALLENGE_STR)) != EOK) {
        return memory_copy_error(__func__, __LINE__);
    }

    aes_aad.length = strlen(SEC_CLONE_CHALLENGE_STR);
    /* out data len is less than src data len, so src data len is enough for out data */
    int32_t out_data_len = src_data->length;
    struct uint8_buff *out_data = &sec_clone_server->start_request_data;
    out_data->val = (uint8_t *)MALLOC(out_data_len);
    if (out_data->val == NULL) {
        LOGE("MALLOC failed");
        return HC_MALLOC_FAILED;
    }
    out_data->length = out_data_len;
    out_data->size = out_data_len;

    int32_t ret = aes_gcm_decrypt((struct var_buffer *)&hichain->sts_server->session_key,
                                  src_data, &aes_aad, out_data);
    if (ret != HC_OK) {
        LOGE("Called parse sec_clone request data failed, errCode:%d", ret);
        FREE(out_data->val);
        out_data->val = NULL;
        return ret;
    }

    return HC_OK;
}

static int32_t gen_temp_cert_key(struct sts_server *sts_server, struct hc_key_alias *cert_key_alias)
{
    int32_t ret;

    struct service_id service_id = generate_service_id(sts_server->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        return HC_GEN_SERVICE_ID_FAILED;
    }
    *cert_key_alias = generate_key_alias(&service_id, &sts_server->self_id, KEY_ALIAS_TMP);
    if (cert_key_alias->length == 0) {
        LOGE("Generate key alias failed");
        return HC_GEN_ALIAS_FAILED;
    }

    ret = check_lt_public_key_exist(cert_key_alias);
    if (ret == HC_OK) {
        LOGE("key is exist");
        return HC_OK;
    }

    struct hc_auth_id temp_auth_id = {
        .auth_id = {0},
        .length = HC_AUTH_ID_BUFF_LEN
    };
    ret = generate_lt_X25519_key_pair(cert_key_alias, &temp_auth_id);
    if (ret != HC_OK) {
        LOGE("gen temp key failed");
    }
    return ret;
}

static int32_t gen_cert_chain_buff(struct uint8_buff *cert_chain, int32_t len)
{
    if (len > CERT_CHAIN_NUM) {
        return HC_INPUT_ERROR;
    }
    for (int32_t i = 0; i < CERT_CHAIN_NUM; ++i) {
        cert_chain[i].size = SEC_CLONE_CERT_CHAIN_SIZE;
        cert_chain[i].length = SEC_CLONE_CERT_CHAIN_SIZE;
        cert_chain[i].val = (uint8_t *)MALLOC(SEC_CLONE_CERT_CHAIN_SIZE);
        if (cert_chain[i].val == NULL) {
            LOGE("MALLOC cert_chain failed");
            return HC_MALLOC_FAILED;
        }
        (void)memset_s(cert_chain[i].val, SEC_CLONE_CERT_CHAIN_SIZE, 0, SEC_CLONE_CERT_CHAIN_SIZE);
    }
    return HC_OK;
}

static int32_t build_start_response_data(void *handle, void *data)
{
    struct sec_clone_server *sec_clone_server = (struct sec_clone_server *)handle;
    struct hichain *hichain = (struct hichain *)sec_clone_server->hichain_handle;
    struct sts_server *sts_server = (struct sts_server *)hichain->sts_server;
    struct uint8_buff *resp_data = (struct uint8_buff *)data;
    int32_t ret;

    if (sts_server == NULL) {
        LOGE("Sts server is null");
        return HC_STS_OBJECT_ERROR;
    }

    struct uint8_buff combined_challenge;

    ret = sec_clone_combine_challenge(sec_clone_server, &combined_challenge);
    if (ret != HC_OK) {
        LOGE("Combine challenge failed");
        return ret;
    }

    struct uint8_buff cert_chain[CERT_CHAIN_NUM];
    ret = gen_cert_chain_buff(cert_chain, CERT_CHAIN_NUM);
    if (ret != HC_OK) {
        goto FREE_BUFF;
    }
    ret = gen_temp_cert_key(sts_server, &sec_clone_server->cert_key_alias);
    if (ret != HC_OK) {
        LOGE("Get temp cert key failed");
        goto FREE_BUFF;
    }
    sec_clone_server->need_clean_temp_key = true;

    ret = get_key_attestation(&combined_challenge, &sec_clone_server->cert_key_alias, cert_chain);
    if (ret != HC_OK) {
        LOGE("Get key attestation failed");
        goto FREE_BUFF;
    }

    ret = sec_clone_gen_srv_proof(cert_chain, resp_data);
    if (ret != HC_OK) {
        LOGE("Called sec_clone_gen_srv_proof failed");
    }

FREE_BUFF:

    if (combined_challenge.val != NULL) {
        FREE(combined_challenge.val);
        combined_challenge.val = NULL;
    }

    for (int32_t i = 0; i < CERT_CHAIN_NUM; ++i) {
        if (cert_chain[i].val != NULL) {
            FREE(cert_chain[i].val);
            cert_chain[i].val = NULL;
        }
    }

    return ret;
}

static struct hc_key_alias gen_peer_key_alias(struct sec_clone_server *sec_clone_server)
{
    struct hichain *hichain = (struct hichain *)sec_clone_server->hichain_handle;
    struct service_id srv_id = generate_service_id(&hichain->identity);

    return generate_key_alias(&srv_id, &hichain->sts_server->peer_id, KEY_ALIAS_LT_KEY_PAIR);
}

static int32_t save_sec_data(struct sec_clone_server *sec_clone_server, struct uint8_buff *sec_data)
{
    uint32_t key_len = HC_ST_PUBLIC_KEY_LEN;
    if (sec_data->length <= key_len) {
        LOGE("The sec_data len is lesser than key len");
        return HC_INPUT_ERROR;
    }

    struct hc_key_alias target_alias = gen_peer_key_alias(sec_clone_server);

    int32_t ret = asset_unwrap(sec_data, &sec_clone_server->cert_key_alias, &target_alias);
    if (ret != HC_OK) {
        LOGE("Called asset_unwrap failed, errCode:%d", ret);
    }
    return ret;
}

static int32_t parse_end_request_data(void *handle, void *data)
{
    LOGI("Called parse_end_request_data start");
    struct sec_clone_server *sec_clone_server = (struct sec_clone_server *)handle;
    struct uint8_buff *src_data = (struct uint8_buff *)data;
    struct hichain *hichain = (struct hichain *)sec_clone_server->hichain_handle;
    struct aes_aad aes_aad;

    if (memcpy_s(aes_aad.aad, sizeof(aes_aad.aad), SEC_CLONE_CLONE_STR, strlen(SEC_CLONE_CLONE_STR)) != EOK) {
        return memory_copy_error(__func__, __LINE__);
    }

    aes_aad.length = strlen(SEC_CLONE_CLONE_STR);

    struct uint8_buff *out_data = &sec_clone_server->client_sec_data;
    out_data->val = (uint8_t *)MALLOC(src_data->length);
    if (out_data->val == NULL) {
        LOGE("MALLOC out_data val failed");
        return HC_MALLOC_FAILED;
    }
    out_data->size = src_data->length;
    out_data->length = src_data->length;

    int32_t ret = aes_gcm_decrypt((struct var_buffer *)&hichain->sts_server->session_key, src_data, &aes_aad, out_data);
    if (ret != HC_OK) {
        LOGE("Called parse sec_clone request data failed, errCode:%d", ret);
        FREE(out_data->val);
        out_data->val = NULL;
        return ret;
    }

    return HC_OK;
}

static int32_t sec_clone_gen_end_resp(struct var_buffer *session_key, int32_t ret_code, struct uint8_buff *out_data)
{
    LOGI("Called sec_clone_gen_end_resp start");
    int32_t ret;
    struct aes_aad aes_add;

    if (memcpy_s(aes_add.aad, sizeof(aes_add.aad), SEC_CLONE_SEC_RESULT_STR, strlen(SEC_CLONE_SEC_RESULT_STR)) != EOK) {
        return memory_copy_error(__func__, __LINE__);
    }

    aes_add.length = strlen(SEC_CLONE_SEC_RESULT_STR);
    struct uint8_buff ret_code_buff;
    (void)memset_s(&ret_code_buff, sizeof(ret_code_buff), 0, sizeof(ret_code_buff));

    ret_code_buff.val = (uint8_t *)MALLOC(sizeof(int32_t));
    if (ret_code_buff.val == NULL) {
        LOGE("MALLOC ret_code_buff failed");
        return HC_MALLOC_FAILED;
    }

    ret_code_buff.size = sizeof(int32_t);
    ret_code_buff.length = ret_code_buff.size;

    (void)memcpy_s(ret_code_buff.val, sizeof(int32_t), &ret_code, sizeof(int32_t));

    out_data->size = ret_code_buff.length * BYTE_TO_HEX_OPER_LENGTH + HKS_ENCRYPT_MAX_TAG_SIZE;
    ret = aes_gcm_encrypt(session_key, &ret_code_buff, &aes_add, out_data);
    if (ret != ERROR_CODE_SUCCESS) {
        LOGE("Encrypt retCode failed, errCode:%d", ret);
    }
    if (ret_code_buff.val != NULL) {
        FREE(ret_code_buff.val);
        ret_code_buff.val = NULL;
    }

    return ret;
}

static int32_t build_end_response_data(void *handle, void *data)
{
    LOGI("Called build_end_response_data start");
    struct sec_clone_server *sec_clone_server = (struct sec_clone_server *)handle;
    struct hichain *hichain = (struct hichain *)sec_clone_server->hichain_handle;
    struct sts_server *sts_server = hichain->sts_server;
    struct uint8_buff *out_data = (struct uint8_buff *)data;

    int32_t unwrap_ret = save_sec_data(sec_clone_server, &sec_clone_server->client_sec_data);
    if (unwrap_ret != HC_OK) {
        LOGE("Called save_sec_data failed, errCode:%d", unwrap_ret);
        return unwrap_ret;
    }

    int32_t ret = sec_clone_gen_end_resp((struct var_buffer *)&sts_server->session_key, unwrap_ret, out_data);
    if (ret != HC_OK) {
        LOGE("Called sec_clone_gen_end_resp failed, errCode:%d", ret);
    }
    return ret;
}

#else

#include "sec_clone_server.h"
#include "log.h"
#include "mem_stat.h"

struct sec_clone_server *build_sec_clone_server(hc_handle hichain)
{
    LOGE("Donot support sec clone protocol");
    (void)hichain;
    return (struct sec_clone_server *)MALLOC(sizeof(struct sec_clone_server));
}

void destroy_sec_clone_server(struct sec_clone_server *handle)
{
    LOGE("Donot support sec clone protocol");
    FREE(handle);
}

#endif
