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

#include <securec.h>
#include "commonutil.h"
#include "distribution.h"
#include "log.h"
#include "parsedata.h"
#include "jsonutil.h"
#include "auth_info.h"
#include "add_auth_info.h"
#include "build_object.h"
#include "mem_stat.h"
#include "huks_adapter.h"
#include "sec_clone_server.h"

#define LIST_TRUST_PEER_DEF_COUNT 0

#define FREE_SEND_DATA_FUNC(name) \
    { \
        if (((name)->cipher.val != NULL) && ((name)->cipher.length > 0)) { \
            FREE((name)->cipher.val); \
            (name)->cipher.val = NULL; \
        } \
        break; \
    }

#define FREE_SEC_SEND_DATA_FUNC(name) \
    { \
        if ((name)->val != NULL) { \
            FREE((name)->val); \
            (name)->val = NULL; \
        } \
        break; \
    }

#ifdef DESC
#undef DESC
#endif
#define DESC(...) 1

static void encap_inform_message(int32_t error_code, struct message *send);
static int32_t deserialize_message(const struct uint8_buff *data, struct message *receive);
static int32_t deserialize_message_with_json_object(const void *json_object, struct message *receive);
static int32_t build_send_data_by_struct(const struct message *message, void **send_data, uint32_t *send_data_len);
static void destroy_receive_data_struct(const struct message *message);
static void destroy_send_data(struct message *message);
static void set_result(struct hichain *hichain, uint16_t rcv_msg_code, uint16_t snd_msg_code, int32_t error_code);
static int32_t check_identity(const struct session_identity *identity);
static int32_t check_call_back(const struct hc_call_back *call_back);
static int32_t check_auth_info(const struct hc_user_info *user_info);
static int32_t delete_base_key(struct service_id service_id, struct operation_parameter para);
static int32_t delete_public_key(hc_handle handle, struct service_id service_id, int32_t user_type);
static void build_self_lt_key_pair(const struct hichain *hichain);

#if DESC("api")
DLL_API_PUBLIC hc_handle get_instance(const struct session_identity *identity, enum hc_type type,
    const struct hc_call_back *call_back)
{
    LOGI("Begin get instance");
    if (check_identity(identity) != HC_OK) {
        LOGE("Identity error");
        return NULL;
    }
    if (check_call_back(call_back) != HC_OK) {
        LOGE("Call back error");
        return NULL;
    }

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) || defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
    int32_t ret = key_info_init();
    if (ret != HC_OK) {
        LOGE("Call key info init failed, status=%d", ret);
        return NULL;
    }
#endif

    struct hichain *hichain = (struct hichain *)MALLOC(sizeof(struct hichain));
    if (hichain == NULL) {
        LOGE("Alloc memory failed");
        return NULL;
    }
    (void)memset_s(hichain, sizeof(*hichain), 0, sizeof(*hichain));
    hichain->identity = *identity;
    hichain->type = type;
    hichain->state = INIT_STATE;
    hichain->last_state = INIT_STATE;
    hichain->cb = *call_back;

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) || defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
    build_self_lt_key_pair(hichain);
#endif

    LOGI("Get instance success");
    return hichain;
}

DLL_API_PUBLIC void destroy(hc_handle *handle)
{
    LOGI("Begin destroy");
    check_ptr_return(handle);
    check_ptr_return(*handle);
    struct hichain *hichain = (struct hichain *)*handle;

    if (hichain->pake_server != NULL) {
        destroy_pake_server(hichain->pake_server);
    }
    if (hichain->pake_client != NULL) {
        destroy_pake_client(hichain->pake_client);
    }
    if (hichain->sts_server != NULL) {
        destroy_sts_server(hichain->sts_server);
    }
    if (hichain->sts_client != NULL) {
        destroy_sts_client(hichain->sts_client);
    }
    if (hichain->auth_info != NULL) {
        destroy_auth_client(hichain->auth_info);
    }
    if (hichain->sec_clone_server != NULL) {
        destroy_sec_clone_server(hichain->sec_clone_server);
    }
    FREE(hichain);
    *handle = NULL;
    LOGI("End destroy");
}

DLL_API_PUBLIC void set_context(hc_handle handle, void *context)
{
    LOGI("Begin set context");
    check_ptr_return(handle);
    check_ptr_return(context);
    struct hichain *hichain = (struct hichain *)handle;

    hichain->identity.context = context;
    LOGI("End set context");
}

DLL_API_PUBLIC int32_t receive_data(hc_handle handle, struct uint8_buff *data)
{
    LOGI("Begin receive data");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(data, HC_INPUT_ERROR);
    check_ptr_return_val(data->val, HC_INPUT_ERROR);

    LOGI("Receive data from peer");
    struct hichain *hichain = (struct hichain *)handle;
    struct message receive = { 0, 0, 0 };
    struct message send = { INFORM_MESSAGE, 0, 0 };
    void *send_data = NULL;
    uint32_t send_data_len = 0;
    int32_t ret = deserialize_message(data, &receive);
    if (ret != HC_OK) {
        goto inform;
    }
    struct header_analysis nav = navigate_message(receive.msg_code);
    ret = check_message_support(hichain, &nav, &receive);
    if (ret != HC_OK) {
        goto inform;
    }
    ret = build_object(hichain, nav.modular, !nav.is_request_msg, NULL);
    if (ret != HC_OK) {
        goto inform;
    }
    ret = proc_message(hichain, &nav, &receive, &send);
    if (ret != HC_OK) {
        goto inform;
    }
    ret = connect_message(hichain, &nav, &send);

inform:
    encap_inform_message(ret, &send);

    /* serialization */
    ret = build_send_data_by_struct(&send, &send_data, &send_data_len);
    if (ret == HC_OK) {
        DBG_OUT("Send data to peer");
        hichain->cb.transmit(&hichain->identity, send_data, send_data_len);
        FREE(send_data);
    } else if (ret == HC_NO_MESSAGE_TO_SEND) {
        LOGI("Had no message to send");
        ret = HC_OK;
    } else {
        LOGE("build send data failed, error code is %d", ret);
    }
    set_result(hichain, receive.msg_code, send.msg_code, ret);

    destroy_receive_data_struct(&receive);
    destroy_send_data(&send);
    LOGI("End receive data");
    return ret; /* hc_error */
}

int32_t init_center(const struct hc_package_name *package_name, const struct hc_service_type *service_type,
    const struct hc_auth_id *auth_id, struct hc_key_alias *dek)
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
{
    LOGI("Begin init center");
    check_ptr_return_val(package_name, HC_INPUT_ERROR);
    check_ptr_return_val(service_type, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);
    check_ptr_return_val(dek, HC_INPUT_ERROR);

    struct session_identity identity;
    identity.session_id = 0;
    identity.package_name = *package_name;
    identity.service_type = *service_type;
    struct service_id service_id = generate_service_id(&identity);
    struct hc_auth_id origin_id;
    int32_t ret = hex_string_to_byte((char *)auth_id->auth_id, auth_id->length, origin_id.auth_id);
    if (ret != HC_OK) {
        LOGE("auth_id convert failed");
        return ret;
    }
    origin_id.length = auth_id->length / BYTE_TO_HEX_OPER_LENGTH;

    struct hc_key_alias kek_alias = generate_key_alias(&service_id, &origin_id, KEY_ALIAS_KEK);
    struct hc_key_alias dek_alias = generate_key_alias(&service_id, &origin_id, KEY_ALIAS_DEK);
    struct hc_key_alias base_alias = generate_key_alias(&service_id, &origin_id, KEY_ALIAS_LT_KEY_PAIR);

    ret = gen_derived_key(&base_alias, &kek_alias);
    if (ret != HC_OK) {
        LOGE("Generate derived kek failed");
        return ret;
    }
    ret = gen_derived_key(&base_alias, &dek_alias);
    if (ret != HC_OK) {
        LOGE("Generate derived dek failed");
        return ret;
    }
    if (memcpy_s(dek, sizeof(struct hc_key_alias), &dek_alias, sizeof(struct hc_key_alias)) != HC_OK) {
        return HC_INNER_ERROR;
    }

    LOGI("End init center");
    return HC_OK;
}
#else
{
    LOGE("Secclone has been cut, init center not support");
    (void)package_name;
    (void)service_type;
    (void)auth_id;
    (void)dek;
    return HC_UNSUPPORT;
}
#endif

DLL_API_PUBLIC int32_t receive_data_with_json_object(hc_handle handle, const void *json_object)
{
    LOGI("Begin receive data json object");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(json_object, HC_INPUT_ERROR);

    LOGI("Receive data from peer");
    struct hichain *hichain = (struct hichain *)handle;
    struct message receive = { 0, 0, 0 };
    struct message send = { INFORM_MESSAGE, 0, 0 };
    void *send_data = NULL;
    uint32_t send_data_len = 0;
    int32_t ret = deserialize_message_with_json_object(json_object, &receive);
    if (ret != HC_OK) {
        goto inform;
    }
    struct header_analysis nav = navigate_message(receive.msg_code);
    ret = check_message_support(hichain, &nav, &receive);
    if (ret != HC_OK) {
        goto inform;
    }
    ret = build_object(hichain, nav.modular, !nav.is_request_msg, NULL);
    if (ret != HC_OK) {
        goto inform;
    }
    ret = proc_message(hichain, &nav, &receive, &send);
    if (ret != HC_OK) {
        goto inform;
    }
    ret = connect_message(hichain, &nav, &send);

inform:
    encap_inform_message(ret, &send);

    /* serialization */
    ret = build_send_data_by_struct(&send, &send_data, &send_data_len);
    if (ret == HC_OK) {
        DBG_OUT("Send data to peer");
        hichain->cb.transmit(&hichain->identity, send_data, send_data_len);
        FREE(send_data);
    } else if (ret == HC_NO_MESSAGE_TO_SEND) {
        LOGI("Had no message to send");
        ret = HC_OK;
    } else {
        LOGE("build send data failed, error code is %d", ret);
    }
    set_result(hichain, receive.msg_code, send.msg_code, ret);

    destroy_receive_data_struct(&receive);
    destroy_send_data(&send);
    LOGI("End receive data json object");
    return ret; /* hc_error */
}

static int32_t triggered_sts_client(struct hichain *hichain, int32_t operation_code);
int32_t add_auth_info(hc_handle handle, const struct operation_parameter *params,
    const struct hc_auth_id *auth_id, int32_t user_type)
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
{
    LOGI("Begin add auth info");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(params, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);
    struct hichain *hichain = (struct hichain *)handle;

    int32_t ret = build_object(hichain, STS_MODULAR, true, params);
    if (ret != HC_OK) {
        LOGE("Build sts client sub object failed, error code is %d", ret);
        return ret;
    }

    struct auth_info_cache auth_info = {
        .user_type = user_type,
        .auth_id = *auth_id
    };
    ret = build_object(hichain, ADD_MODULAR, true, &auth_info);
    if (ret != HC_OK) {
        LOGE("Build sts client sub object failed, error code is %d", ret);
        return ret;
    }

    ret = triggered_sts_client(hichain, ADD_AUTHINFO);
    LOGI("Triggered sts client error code is %d", ret);
    LOGI("End add auth info");
    return ret;
}
#else
{
    LOGE("Secclone has been cut, add auth info not support");
    (void)handle;
    (void)params;
    (void)auth_id;
    (void)user_type;
    return HC_UNSUPPORT;
}
#endif

int32_t remove_auth_info(hc_handle handle, const struct operation_parameter *params,
    const struct hc_auth_id *auth_id, int32_t user_type)
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
{
    LOGI("Begin remove auth info");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(params, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);
    struct hichain *hichain = (struct hichain *)handle;

    int32_t ret = build_object(hichain, STS_MODULAR, true, params);
    if (ret != HC_OK) {
        LOGE("Build sts client sub object failed, error code is %d", ret);
        return ret;
    }

    struct auth_info_cache auth_info = {
        .user_type = user_type,
        .auth_id = *auth_id
    };
    ret = build_object(hichain, REMOVE_MODULAR, true, &auth_info);
    if (ret != HC_OK) {
        LOGE("Build remove client sub object failed, error code is %d", ret);
        return ret;
    }

    ret = triggered_sts_client(hichain, REMOVE_AUTHINFO);
    LOGI("Triggered sts client error code is %d", ret);
    LOGI("End remove auth info");
    return ret;
}
#else
{
    LOGE("Secclone has been cut, remove auth info not support");
    (void)handle;
    (void)params;
    (void)auth_id;
    (void)user_type;
    return HC_UNSUPPORT;
}
#endif

DLL_API_PUBLIC void set_self_auth_id(hc_handle handle, struct uint8_buff *data)
{
    LOGI("Begin set self auth id");
    check_ptr_return(handle);
    check_ptr_return(data);
    check_ptr_return(data->val);
    struct hichain *hichain = (struct hichain *)handle;

    if ((hichain->pake_server != NULL) && (hichain->pake_server->self_id.length == 0)) {
        if (data->length <= 0) {
            return;
        }
        uint32_t copy_len = (data->length < HC_AUTH_ID_BUFF_LEN) ? data->length : HC_AUTH_ID_BUFF_LEN;
        if (memcpy_s(hichain->pake_server->self_id.auth_id, HC_AUTH_ID_BUFF_LEN, data->val, copy_len) != EOK) {
            LOGE("memory copy error");
            return;
        }
        hichain->pake_server->self_id.length = copy_len;
    }
    LOGI("End set self auth id");
}

static int32_t triggered_pake_client(struct hichain *hichain, int32_t operation_code);
DLL_API_PUBLIC int32_t start_pake(hc_handle handle, const struct operation_parameter *params)
{
    LOGI("Begin start pake");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(params, HC_INPUT_ERROR);
    struct hichain *hichain = (struct hichain *)handle;

    int32_t ret = build_object(hichain, PAKE_MODULAR, true, params);
    if (ret != HC_OK) {
        LOGE("Build pake client sub object failed, error code is %d", ret);
        return ret;
    }

    ret = triggered_pake_client(hichain, BIND);
    LOGI("Triggered pake client error code is %d", ret);
    LOGI("End start pake");
    return ret;
}

#ifndef _CUT_API_

DLL_API_PUBLIC int32_t authenticate_peer(hc_handle handle, struct operation_parameter *params)
{
    LOGI("Begin authenticate peer");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(params, HC_INPUT_ERROR);
    struct hichain *hichain = (struct hichain *)handle;

    int32_t ret = build_object(hichain, STS_MODULAR, true, params);
    if (ret != HC_OK) {
        LOGE("Build sts client sub object failed, error code is %d", ret);
        return ret;
    }

    ret = triggered_sts_client(hichain, AUTHENTICATE);
    LOGI("Triggered sts client error code is %d", ret);
    LOGI("End authenticate peer");
    return ret;
}

DLL_API_PUBLIC int32_t delete_local_auth_info(hc_handle handle, struct hc_user_info *user_info)
{
    LOGI("Begin delete local auth info");
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    if (check_auth_info(user_info) != HC_OK) {
        LOGE("User info is error");
        return HC_INPUT_ERROR;
    }

    struct hichain *hichain = (struct hichain *)handle;
    struct service_id service_id = generate_service_id(&hichain->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        return HC_GEN_SERVICE_ID_FAILED;
    }

    struct hc_pin pin = { 0, {0} };
    struct operation_parameter para;
    (void)memset_s(&para, sizeof(para), 0, sizeof(para));

    hichain->cb.get_protocol_params(&hichain->identity, REMOVE_ALL_AUTHINFO, &pin, &para);
    if (para.self_auth_id.length > 0) {
        if (memcmp(para.self_auth_id.auth_id, user_info->auth_id.auth_id, para.self_auth_id.length) == 0) {
            int32_t ret_base = delete_base_key(service_id, para);
            int32_t ret_accessor = delete_public_key(handle, service_id, KEY_ALIAS_ACCESSOR_PK);
            int32_t ret_controller = delete_public_key(handle, service_id, KEY_ALIAS_CONTROLLER_PK);
            if ((ret_base != HC_OK) || (ret_accessor != HC_OK) || (ret_controller != HC_OK)) {
                LOGE("delete all key failed");
                return ERROR_CODE_FAILED;
            }
            return HC_OK;
        }
    }

    enum huks_key_alias_type alias_type = (user_info->user_type == HC_USER_TYPE_ACCESSORY ?
                                           KEY_ALIAS_ACCESSOR_PK : KEY_ALIAS_CONTROLLER_PK);
    struct hc_key_alias alias = generate_key_alias(&service_id, &(user_info->auth_id), alias_type);
    if (alias.length == 0) {
        LOGE("Generate key alias failed");
        return HC_GEN_ALIAS_FAILED;
    }
    int32_t ret = check_lt_public_key_exist(&alias);
    if (ret != HC_OK) {
        LOGE("Check lt public key not exist!");
        return HC_OK; /* ipc 65541 time out, temporarily return ok */
    }
    ret = delete_lt_public_key(&alias);
    if (ret != HC_OK) {
        LOGE("delete lt public key is %d", ret);
        return ret;
    }
    LOGI("End delete local auth info");
    return HC_OK;
}

DLL_API_PUBLIC int32_t is_trust_peer(hc_handle handle, struct hc_user_info *user_info)
{
    LOGI("Begin is trust peer");
    check_ptr_return_val(handle, HC_NOT_TRUST_PEER);
    if (check_auth_info(user_info) != HC_OK) {
        LOGE("User info is error");
        return HC_NOT_TRUST_PEER;
    }

    struct hichain *hichain = (struct hichain *)handle;
    struct service_id service_id = generate_service_id(&hichain->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        return HC_GEN_SERVICE_ID_FAILED;
    }
    enum huks_key_alias_type alias_type = (user_info->user_type == HC_USER_TYPE_ACCESSORY ?
                                           KEY_ALIAS_ACCESSOR_PK : KEY_ALIAS_CONTROLLER_PK);
    struct hc_key_alias alias = generate_key_alias(&service_id, &(user_info->auth_id), alias_type);
    if (alias.length == 0) {
        LOGE("Generate key alias failed");
        return HC_GEN_ALIAS_FAILED;
    }
    int32_t ret = check_lt_public_key_exist(&alias);
    if (ret != ERROR_CODE_SUCCESS) {
        LOGE("Check lt public key exist is %d", ret);
        return HC_NOT_TRUST_PEER;
    }
    struct huks_key_type key_type;
    struct hc_auth_id auth_id;

    (void)memset_s(&key_type, sizeof(key_type), 0, sizeof(key_type));
    ret = get_lt_key_info(&alias, &key_type, &auth_id);
    if (ret != ERROR_CODE_SUCCESS) {
        LOGE("Check lt public key exist is %d", ret);
        return HC_NOT_TRUST_PEER;
    }
    LOGI("End is trust peer");
    if (key_type.user_type == (uint8_t)HC_USER_TYPE_ACCESSORY) {
        return HC_ACCESSORY_TRUST_PEER;
    }
    if (key_type.pair_type == (uint8_t)HC_PAIR_TYPE_BIND) {
        return HC_BINDED_TRUST_PEER;
    } else {
        return HC_AUTHED_TRUST_PEER;
    }
}

DLL_API_PUBLIC uint32_t list_trust_peers(hc_handle handle, int32_t trust_user_type,
    struct hc_auth_id *owner_auth_id, struct hc_auth_id **auth_id_list)
{
    LOGI("Begin list trust peers");
    struct hichain *hichain = (struct hichain *)handle;

    check_ptr_return_val(hichain, LIST_TRUST_PEER_DEF_COUNT);
    check_ptr_return_val(auth_id_list, LIST_TRUST_PEER_DEF_COUNT);
    check_ptr_return_val(*auth_id_list, LIST_TRUST_PEER_DEF_COUNT);
    if ((trust_user_type != HC_USER_TYPE_ACCESSORY) && (trust_user_type != HC_USER_TYPE_CONTROLLER)) {
        LOGE("user type is not support");
        return LIST_TRUST_PEER_DEF_COUNT;
    }

    if (owner_auth_id != NULL) {
        struct service_id srv_id = generate_service_id(&hichain->identity);
        if (srv_id.length == 0) {
            LOGE("Generate service id failed");
            return 0;
        }
        enum huks_key_alias_type alias_type = (trust_user_type == HC_USER_TYPE_ACCESSORY ?
                                               KEY_ALIAS_ACCESSOR_PK : KEY_ALIAS_CONTROLLER_PK);
        struct hc_key_alias owner_alias = generate_key_alias(&srv_id, owner_auth_id, alias_type);
        if (owner_alias.length == 0) {
            LOGE("Generate key alias failed");
            return 0;
        }
        if (check_lt_public_key_exist(&owner_alias) != ERROR_CODE_SUCCESS) {
            LOGE("not found this owner");
            return 0;
        }
        if (check_key_alias_is_owner(&owner_alias) != ERROR_CODE_SUCCESS) {
            LOGE("hc_auth_id is not owner");
            return 0;
        }
    }

    uint32_t count = LIST_TRUST_PEER_DEF_COUNT;
    int32_t ret = get_lt_public_key_list(owner_auth_id, trust_user_type, *auth_id_list, &count);
    LOGI("End list trust peers");
    if ((ret != ERROR_CODE_SUCCESS) || (count == LIST_TRUST_PEER_DEF_COUNT)) {
        return LIST_TRUST_PEER_DEF_COUNT;
    }
    return count;
}

DLL_API_PUBLIC int32_t import_auth_info(hc_handle handle, struct hc_user_info *user_info, struct hc_auth_id *auth_id,
    enum hc_export_type auth_info_type, struct uint8_buff *auth_info)
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
{
    LOGI("Begin import auth info");
    (void)user_info;
    struct hichain *hichain = (struct hichain *)handle;

    check_ptr_return_val(hichain, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);
    check_ptr_return_val(auth_info, HC_INPUT_ERROR);
    check_ptr_return_val(auth_info->val, HC_INPUT_ERROR);

    struct hc_auth_id origin_id;
    int32_t ret  = hex_string_to_byte((char *)auth_id->auth_id, auth_id->length, origin_id.auth_id);
    if (ret != HC_OK) {
        LOGE("Auth id convert failed");
        return ret;
    }
    origin_id.length = auth_id->length / BYTE_TO_HEX_OPER_LENGTH;
    origin_id.auth_id[origin_id.length] = '\0';

    if (auth_info_type == EXPORT_DATA_SIGNED_AUTH_INFO) {
        return import_signed_auth_info(hichain, &origin_id, auth_info);
    } else if (auth_info_type == EXPORT_DATA_LITE_AUTH_INFO) {
        return import_lite_auth_info(hichain, &origin_id, auth_info);
    }
    LOGE("Auth info type is not support, type is %u", auth_info_type);
    return HC_UNSUPPORT;
}
#else
{
    LOGI("Begin hilink import auth info");
    (void)user_info;
    struct hichain *hichain = (struct hichain *)handle;

    check_ptr_return_val(hichain, HC_INPUT_ERROR);
    check_ptr_return_val(auth_id, HC_INPUT_ERROR);
    check_ptr_return_val(auth_info, HC_INPUT_ERROR);
    check_ptr_return_val(auth_info->val, HC_INPUT_ERROR);

    if (auth_info_type == EXPORT_DATA_SIGNED_AUTH_INFO) {
        return import_signed_auth_info_hilink(hichain, auth_id, auth_info);
    }

    LOGE("Auth info type is not support, type is %u", auth_info_type);
    return HC_UNSUPPORT;
}
#endif

#endif /* _CUT_XXX_ */
#endif /* DESC */

struct msg_result_map {
    enum message_code msg_code;
    enum hc_result result;
    enum hichain_state state;
};

static void set_result_by_map(struct hichain *hichain, const struct msg_result_map *map)
{
    if (map == NULL) {
        return;
    }
    if (map->state != OPERATION_STATE) {
        goto out;
    }
    if ((hichain->operation_code != AUTHENTICATE) && (hichain->operation_code != AUTH_KEY_AGREEMENT)) {
        goto out;
    }
    if (hichain->state != OVER_STATE) {
        hichain->last_state = hichain->state;
        hichain->state = OVER_STATE;
    }
    hichain->cb.set_service_result(&hichain->identity, END_SUCCESS);
    return;
out:
    if (hichain->state != map->state) {
        hichain->last_state = hichain->state;
        hichain->state = map->state;
    }
    hichain->cb.set_service_result(&hichain->identity, map->result);
}

const struct msg_result_map *select_result_map(uint16_t rcv_msg_code, const struct msg_result_map *map, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        if (rcv_msg_code == map[i].msg_code) {
            return &map[i];
        }
    }
    return NULL;
}

static void set_result(struct hichain *hichain, uint16_t rcv_msg_code, uint16_t snd_msg_code, int32_t error_code)
{
    if (error_code != HC_OK) {
        LOGE("Error code is not ok, and set end failed");
        goto error;
    }
    if (snd_msg_code == INFORM_MESSAGE) {
        LOGE("Send an inform message, and set end failed");
        goto error;
    }
    const struct msg_result_map map[] = { { PAKE_REQUEST, KEY_AGREEMENT_PROCESSING, KEY_AGREEMENT_STATE },
                                          { PAKE_RESPONSE, KEY_AGREEMENT_PROCESSING, KEY_AGREEMENT_STATE },
                                          { PAKE_CLIENT_CONFIRM, KEY_AGREEMENT_END, OPERATION_STATE },
                                          { PAKE_SERVER_CONFIRM_RESPONSE, KEY_AGREEMENT_END, OPERATION_STATE },
                                          { EXCHANGE_REQUEST, END_SUCCESS, OVER_STATE },
                                          { EXCHANGE_RESPONSE, END_SUCCESS, OVER_STATE },
                                          { AUTH_START_REQUEST, KEY_AGREEMENT_PROCESSING, KEY_AGREEMENT_STATE },
                                          { AUTH_START_RESPONSE, KEY_AGREEMENT_PROCESSING, KEY_AGREEMENT_STATE },
                                          { AUTH_ACK_REQUEST, KEY_AGREEMENT_END, OPERATION_STATE },
                                          { AUTH_ACK_RESPONSE, KEY_AGREEMENT_END, OPERATION_STATE },
                                          { ADD_AUTHINFO_REQUEST, END_SUCCESS, OVER_STATE },
                                          { ADD_AUTHINFO_RESPONSE, END_SUCCESS, OVER_STATE },
                                          { REMOVE_AUTHINFO_REQUEST, END_SUCCESS, OVER_STATE },
                                          { REMOVE_AUTHINFO_RESPONSE, END_SUCCESS, OVER_STATE },
                                          { SEC_CLONE_START_REQUEST, OPERATION_PROCESSING, OPERATION_STATE },
                                          { SEC_CLONE_ACK_REQUEST, END_SUCCESS, OVER_STATE },
                                          { INFORM_MESSAGE, END_FAILED, OVER_STATE },
                                          { INVALID_MESSAGE, KEY_AGREEMENT_PROCESSING, KEY_AGREEMENT_STATE } };
    const struct msg_result_map *map_ptr = select_result_map(rcv_msg_code, map,
        sizeof(map) / sizeof(struct msg_result_map));

    set_result_by_map(hichain, map_ptr);
    return;
error:
    hichain->last_state = hichain->state;
    hichain->state = OVER_STATE;
    hichain->cb.set_service_result(&hichain->identity, END_FAILED);
}

static void encap_inform_message(int32_t error_code, struct message *send)
{
    if ((error_code == HC_OK) || (send->msg_code != INFORM_MESSAGE) || (send->payload != NULL)) {
        return;
    }
    int32_t *err = (int32_t *)MALLOC(sizeof(int32_t));
    if (err == NULL) {
        LOGE("Malloc for encape inform message failed");
        return;
    }

    *err = error_code;
    send->payload = err;
}

static int32_t triggered_pake_client(struct hichain *hichain, int32_t operation_code)
#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_CLIENT_))
{
    hichain->operation_code = operation_code;
    hichain->pake_client->operation_code = operation_code;

    struct message send = {
        .msg_code = PAKE_REQUEST,
        .rsv = 0,
        .payload = NULL
    };
    int32_t ret = send_pake_start_request(hichain->pake_client, &send);
    if (ret != HC_OK) {
        LOGE("Object %u build sts start request failed, error code is %d", pake_client_sn(hichain->pake_client), ret);
        return HC_BUILD_SEND_DATA_FAILED;
    }

    void *send_data = NULL;
    uint32_t send_data_len = 0;

    ret = build_send_data_by_struct(&send, &send_data, &send_data_len);
    if (ret != HC_OK) {
        LOGW("build send data failed, error code is %d", ret);
    } else {
        DBG_OUT("send_data:%s", (uint8_t *)send_data);
        hichain->cb.transmit(&hichain->identity, send_data, send_data_len);
        FREE(send_data);
    }

    set_result(hichain, INVALID_MESSAGE, PAKE_REQUEST, ret);
    destroy_send_data(&send);
    return ret;
}
#else
{
    (void)hichain;
    (void)operation_code;
    LOGE("Pake client has been cut, triggered pake client not support");
    return HC_UNSUPPORT;
}
#endif

static int32_t triggered_sts_client(struct hichain *hichain, int32_t operation_code)
#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_))
{
    hichain->operation_code = operation_code;
    hichain->sts_client->operation_code = operation_code;

    struct message send = {
        .msg_code = AUTH_START_REQUEST,
        .rsv = 0,
        .payload = NULL
    };
    int32_t ret = send_sts_start_request(hichain->sts_client, &send);
    if (ret != HC_OK) {
        LOGE("Object %u build sts start request failed, error code is %d", sts_client_sn(hichain->sts_client), ret);
        return HC_BUILD_SEND_DATA_FAILED;
    }

    void *send_data = NULL;
    uint32_t send_data_len = 0;

    ret = build_send_data_by_struct(&send, &send_data, &send_data_len);
    if (ret != HC_OK) {
        LOGW("build send data failed, error code is %d", ret);
    } else {
        DBG_OUT("send_data:%s", (uint8_t *)send_data);
        hichain->cb.transmit(&hichain->identity, send_data, send_data_len);
        FREE(send_data);
    }

    set_result(hichain, INVALID_MESSAGE, AUTH_START_REQUEST, ret);
    destroy_send_data(&send);
    return ret;
}
#else
{
    (void)hichain;
    (void)operation_code;
    LOGE("stsclient has been cut, triggered_sts_client not support");
    return HC_UNSUPPORT;
}
#endif

static int32_t build_struct_by_receive_data(uint32_t msg_code, const char *payload_data,
    enum json_object_data_type type, struct message *message);
static int32_t deserialize_message(const struct uint8_buff *data, struct message *receive)
{
    /* message head deserialization */
    struct pass_through_data *pass_through_data = parse_data((const char *)data->val);
    if (pass_through_data == NULL) {
        LOGE("Parse data failed");
        return HC_BUILD_OBJECT_FAILED;
    }

    /* message payload deserialization */
    int32_t ret = build_struct_by_receive_data(pass_through_data->message_code, pass_through_data->payload_data,
                                               JSON_STRING_DATA, receive);
    if (ret != HC_OK) {
        LOGE("Build struct by receive data failed, error code is %d", ret);
    }
    free_data(pass_through_data);
    pass_through_data = NULL;
    return ret;
}

static int32_t deserialize_message_with_json_object(const void *json_object, struct message *receive)
{
    int32_t message_code = get_json_int((void *)json_object, FIELD_MESSAGE);
    if ((message_code <= 0) || (message_code > (int32_t)INFORM_MESSAGE)) {
        LOGE("Get message code failed, get message code is %d", message_code);
        return HC_BUILD_OBJECT_FAILED;
    }
    json_pobject obj_value = get_json_obj((void *)json_object, FIELD_PAYLOAD);
    if (obj_value == NULL) {
        LOGE("Parse data failed");
        return HC_BUILD_OBJECT_FAILED;
    }

    /* message payload deserialization */
    int32_t ret = build_struct_by_receive_data(message_code, obj_value, JSON_OBJECT_DATA, receive);
    if (ret != HC_OK) {
        LOGE("Build struct by receive data failed, error code is %d", ret);
    }
    return ret;
}

typedef void *(*parse_message_func)(const char *pay_load, enum json_object_data_type type);
struct parse_message_map {
    enum message_code msg_code;
    parse_message_func parse_message;
};

static int32_t build_struct_by_receive_data(uint32_t msg_code, const char *payload_data,
    enum json_object_data_type type, struct message *message)
{
    const struct parse_message_map map[] = { { PAKE_REQUEST, parse_pake_request },
                                             { PAKE_RESPONSE, parse_pake_response },
                                             { PAKE_CLIENT_CONFIRM, parse_pake_client_confirm },
                                             { PAKE_SERVER_CONFIRM_RESPONSE, parse_pake_server_confirm },
                                             { AUTH_START_REQUEST, parse_auth_start_request },
                                             { AUTH_START_RESPONSE, parse_auth_start_response },
                                             { AUTH_ACK_REQUEST, parse_auth_ack_request },
                                             { AUTH_ACK_RESPONSE, parse_auth_ack_response },
                                             { ADD_AUTHINFO_REQUEST, parse_add_auth_info_request },
                                             { REMOVE_AUTHINFO_REQUEST, parse_rmv_auth_info_request },
                                             { ADD_AUTHINFO_RESPONSE, parse_add_auth_info_response },
                                             { REMOVE_AUTHINFO_RESPONSE, parse_rmv_auth_info_response },
                                             { EXCHANGE_REQUEST, parse_exchange_request },
                                             { EXCHANGE_RESPONSE, parse_exchange_response },
                                             { SEC_CLONE_START_REQUEST, sec_clone_parse_client_request },
                                             { SEC_CLONE_ACK_REQUEST, sec_clone_parse_client_ack } };

    for (uint32_t i = 0; i < sizeof(map) / sizeof(struct parse_message_map); i++) {
        if (map[i].msg_code != msg_code) {
            continue;
        }
        void *payload = map[i].parse_message(payload_data, type);

        if (payload == NULL) {
            return HC_BUILD_OBJECT_FAILED;
        }
        message->msg_code = map[i].msg_code;
        message->payload = payload;
        return HC_OK;
    }

    LOGE("Unsupport parse 0x%04x message", message->msg_code);
    return HC_UNKNOW_MESSAGE;
}

typedef void (*free_message_func)(void *obj);
struct free_message_map {
    enum message_code msg_code;
    free_message_func free_message;
};

static void destroy_receive_data_struct(const struct message *message)
{
    const struct free_message_map map[] = { { PAKE_REQUEST, free_pake_request },
                                            { PAKE_RESPONSE, free_pake_response },
                                            { PAKE_CLIENT_CONFIRM, free_pake_client_confirm },
                                            { PAKE_SERVER_CONFIRM_RESPONSE, free_pake_server_confirm },
                                            { AUTH_START_REQUEST, free_auth_start_request },
                                            { AUTH_START_RESPONSE, free_auth_start_response },
                                            { AUTH_ACK_REQUEST, free_auth_ack_request },
                                            { AUTH_ACK_RESPONSE, free_auth_ack_response },
                                            { ADD_AUTHINFO_REQUEST, free_add_auth_info_request },
                                            { REMOVE_AUTHINFO_REQUEST, free_rmv_auth_info_request },
                                            { ADD_AUTHINFO_RESPONSE, free_add_auth_info_response },
                                            { REMOVE_AUTHINFO_RESPONSE, free_rmv_auth_info_response },
                                            { EXCHANGE_REQUEST, free_exchange_request },
                                            { EXCHANGE_RESPONSE, free_exchange_response },
                                            { SEC_CLONE_START_REQUEST, sec_clone_free_client_request },
                                            { SEC_CLONE_ACK_REQUEST, sec_clone_free_client_ack } };

    for (uint32_t i = 0; i < sizeof(map) / sizeof(struct free_message_map); i++) {
        if (map[i].msg_code == message->msg_code) {
            map[i].free_message(message->payload);
        }
    }
}

typedef char *(*make_message_func)(void *data);
struct make_message_map {
    enum message_code msg_code;
    make_message_func make_message;
};

static int32_t build_send_data_by_struct(const struct message *message, void **send_data, uint32_t *send_data_len)
{
    const struct make_message_map map[] = { { PAKE_REQUEST, make_pake_request },
                                            { PAKE_RESPONSE, make_pake_response },
                                            { PAKE_CLIENT_CONFIRM, make_pake_client_confirm },
                                            { PAKE_SERVER_CONFIRM_RESPONSE, make_pake_server_confirm },
                                            { AUTH_START_REQUEST, make_auth_start_request },
                                            { AUTH_START_RESPONSE, make_auth_start_response },
                                            { AUTH_ACK_REQUEST, make_auth_ack_request },
                                            { AUTH_ACK_RESPONSE, make_auth_ack_response },
                                            { ADD_AUTHINFO_REQUEST, make_add_auth_info_request },
                                            { REMOVE_AUTHINFO_REQUEST, make_rmv_auth_info_request },
                                            { ADD_AUTHINFO_RESPONSE, make_add_auth_info_response },
                                            { REMOVE_AUTHINFO_RESPONSE, make_rmv_auth_info_response },
                                            { EXCHANGE_REQUEST, make_exchange_request },
                                            { EXCHANGE_RESPONSE, make_exchange_response },
                                            { SEC_CLONE_START_RESPONSE, sec_clone_make_srv_proof },
                                            { SEC_CLONE_ACK_RESPONSE, sec_clone_make_clone_ret },
                                            { INFORM_MESSAGE, make_inform_message } };

    if (message->msg_code == INVALID_MESSAGE) {
        return HC_NO_MESSAGE_TO_SEND;
    }

    if (message->payload == NULL) {
        LOGE("Message payload is null");
        return HC_BUILD_SEND_DATA_FAILED;
    }

    for (uint32_t i = 0; i < sizeof(map) / sizeof(struct make_message_map); i++) {
        if (map[i].msg_code != message->msg_code) {
            continue;
        }
        *send_data = map[i].make_message(message->payload);
        if (*send_data == NULL) {
            return HC_BUILD_SEND_DATA_FAILED;
        }
        *send_data_len = strlen(*send_data);
        return HC_OK;
    }

    LOGE("Unsupport encape 0x%04x message", message->msg_code);
    return HC_INNER_ERROR;
}

static void destroy_send_data(struct message *message)
{
    if (message->payload == NULL) {
        return;
    }

    switch (message->msg_code) {
        case ADD_AUTHINFO_RESPONSE: {
            add_response_data *add_res_data = message->payload;
            FREE_SEND_DATA_FUNC(add_res_data); /* add_res_data */
        }
        case ADD_AUTHINFO_REQUEST: {
            add_request_data *add_req_data = message->payload;
            FREE_SEND_DATA_FUNC(add_req_data); /* add_req_data */
        }
        case REMOVE_AUTHINFO_RESPONSE: {
            remove_response_data *rmv_auth_info_res_data = message->payload;
            FREE_SEND_DATA_FUNC(rmv_auth_info_res_data); /* rmv_auth_info_res_data */
        }
        case REMOVE_AUTHINFO_REQUEST: {
            remove_request_data *rmv_auth_info_req_data = message->payload;
            FREE_SEND_DATA_FUNC(rmv_auth_info_req_data); /* rmv_auth_info_req_data */
        }
        case EXCHANGE_RESPONSE: {
            exchange_response_data *exchange_response = message->payload;
            FREE_SEND_DATA_FUNC(exchange_response); /* exchange_response */
        }
        case EXCHANGE_REQUEST: {
            exchange_request_data *exchange_requeset = message->payload;
            FREE_SEND_DATA_FUNC(exchange_requeset); /* exchange_requeset */
        }
        case SEC_CLONE_START_RESPONSE: {
            struct uint8_buff *data = message->payload;
            FREE_SEC_SEND_DATA_FUNC(data); /* data */
        }
        case SEC_CLONE_ACK_RESPONSE: {
            struct uint8_buff *data = message->payload;
            FREE_SEC_SEND_DATA_FUNC(data); /* data */
        }
        default:
            break;
    }

    if (message->payload != NULL) {
        FREE(message->payload);
        message->payload = NULL;
    }
}

static int32_t check_identity(const struct session_identity *identity)
{
    check_ptr_return_val(identity, HC_INPUT_ERROR);
    if (identity->package_name.length > HC_PACKAGE_NAME_BUFF_LEN) {
        LOGE("Package name length error, %u > %u", identity->package_name.length, HC_PACKAGE_NAME_BUFF_LEN);
        return HC_INPUT_ERROR;
    }
    if (identity->service_type.length > HC_SERVICE_TYPE_BUFF_LEN) {
        LOGE("Service type length error, %u > %u", identity->service_type.length, HC_SERVICE_TYPE_BUFF_LEN);
        return HC_INPUT_ERROR;
    }
    return HC_OK;
}

static int32_t check_call_back(const struct hc_call_back *call_back)
{
    check_ptr_return_val(call_back, HC_INPUT_ERROR);
    check_ptr_return_val(call_back->transmit, HC_INPUT_ERROR);
    check_ptr_return_val(call_back->get_protocol_params, HC_INPUT_ERROR);
    check_ptr_return_val(call_back->set_session_key, HC_INPUT_ERROR);
    check_ptr_return_val(call_back->set_service_result, HC_INPUT_ERROR);
    check_ptr_return_val(call_back->confirm_receive_request, HC_INPUT_ERROR);
    return HC_OK;
}

static int32_t check_auth_info(const struct hc_user_info *user_info)
{
    check_ptr_return_val(user_info, HC_INPUT_ERROR);
    if (user_info->auth_id.length > HC_AUTH_ID_BUFF_LEN) {
        LOGE("Auth id length is error, %u > %u", user_info->auth_id.length, HC_AUTH_ID_BUFF_LEN);
        return HC_INPUT_ERROR;
    }
    if ((user_info->user_type != HC_USER_TYPE_CONTROLLER) && (user_info->user_type != HC_USER_TYPE_ACCESSORY)) {
        LOGE("User type %d is not controller or accessory", user_info->user_type);
        return HC_INPUT_ERROR;
    }
    return HC_OK;
}

static int32_t delete_base_key(struct service_id service_id, struct operation_parameter para)
{
    LOGI("delete base key");
    struct hc_key_alias alias_list[HC_BASE_KEY_NUM];
    int32_t size = sizeof(struct hc_key_alias);
    int32_t length = HC_BASE_KEY_NUM * size;
    (void)memset_s(alias_list, length, 0, length);

    int32_t pos = 0;
    struct hc_key_alias base_alias = generate_key_alias(&service_id, &(para.peer_auth_id), KEY_ALIAS_KEK);
    (void)memcpy_s(alias_list + pos, length - pos * size, &base_alias, size);
    pos++;
    base_alias = generate_key_alias(&service_id, &(para.peer_auth_id), KEY_ALIAS_DEK);
    (void)memcpy_s(alias_list + pos, length - pos * size, &base_alias, size);
    pos++;
    base_alias = generate_key_alias(&service_id, &(para.peer_auth_id), KEY_ALIAS_LT_KEY_PAIR);
    (void)memcpy_s(alias_list + pos, length - pos * size, &base_alias, size);
    pos++;
    base_alias = generate_key_alias(&service_id, &(para.self_auth_id), KEY_ALIAS_LT_KEY_PAIR);
    (void)memcpy_s(alias_list + pos, length - pos * size, &base_alias, size);
    pos++;
    base_alias = generate_key_alias(&service_id, &(para.self_auth_id), KEY_ALIAS_TMP);
    (void)memcpy_s(alias_list + pos, length - pos * size, &base_alias, size);

    for (uint32_t loop = 0; loop < HC_BASE_KEY_NUM; loop++) {
        if (alias_list[loop].length == 0) {
            LOGE("Generate key alias failed");
            continue;
        }
        int32_t ret = check_lt_public_key_exist(&alias_list[loop]);
        if (ret != HC_OK) {
            LOGE("not found key alias %d", loop);
            continue;
        }
        ret = delete_lt_public_key(&alias_list[loop]);
        if (ret != HC_OK) {
            LOGE("delete auth_alias public key is %d", ret);
            return ret;
        }
    }

    return HC_OK;
}

static int32_t delete_public_key(hc_handle handle, struct service_id service_id, int32_t user_type)
{
    LOGI("delete public key");
    uint32_t length = HC_PUB_KEY_ALIAS_MAX_NUM * sizeof(struct hc_auth_id);
    struct hc_auth_id *auth_id_list = (struct hc_auth_id *)MALLOC(length);
    if (auth_id_list == NULL) {
        LOGE("malloc auth id list failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(auth_id_list, length, 0, length);

    uint32_t peers_num = list_trust_peers(handle, user_type, NULL, &auth_id_list);
    LOGI("peers_num %d", peers_num);
    for (uint32_t loop = 0; loop < peers_num; loop++) {
        struct hc_key_alias key_alias = generate_key_alias(&service_id, &auth_id_list[loop], user_type);
        if (key_alias.length == 0) {
            LOGE("Generate key alias failed");
            continue;
        }
        int32_t ret = check_lt_public_key_exist(&key_alias);
        if (ret != HC_OK) {
            continue;
        }
        ret = delete_lt_public_key(&key_alias);
        if (ret != HC_OK) {
            LOGE("delete key_alias public key is %d", ret);
            if (auth_id_list != NULL) {
                FREE(auth_id_list);
                auth_id_list = NULL;
            }
            return ret;
        }
    }

    if (auth_id_list != NULL) {
        FREE(auth_id_list);
        auth_id_list = NULL;
    }

    return HC_OK;
}

static void build_self_lt_key_pair(const struct hichain *hichain)
{
    struct hc_pin pin = { 0, {0} };
    struct operation_parameter para;

    (void)memset_s(&para, sizeof(para), 0, sizeof(para));
    hichain->cb.get_protocol_params(&hichain->identity, GENERATE_KEY_PAIR, &pin, &para);

    if (para.self_auth_id.length > 0) {
        struct service_id service_id = generate_service_id(&hichain->identity);
        if (service_id.length == 0) {
            LOGE("Generate service id failed");
            return;
        }
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
        struct hc_key_alias alias = generate_key_alias(&service_id, &para.self_auth_id, KEY_ALIAS_LT_KEY_PAIR);
#else
        struct hc_key_alias alias = generate_key_alias(&service_id, &para.self_auth_id, KEY_ALIAS_ACCESSOR_PK);
#endif
        if (alias.length == 0) {
            LOGE("Generate key alias failed");
            return;
        }
        int32_t ret = check_lt_public_key_exist(&alias);
        if (ret != HC_OK) {
            ret = generate_lt_key_pair(&alias, &para.self_auth_id);
            if (ret != HC_OK) {
                LOGE("Generate self ltpk return value is %d", ret);
                return;
            }
            DBG_OUT("Generate self ltpk ok");
        }
    }
}
