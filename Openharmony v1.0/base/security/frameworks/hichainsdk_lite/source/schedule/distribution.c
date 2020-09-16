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

#include "distribution.h"
#include <securec.h>
#include "log.h"
#include "pake_client.h"
#include "pake_server.h"
#include "sts_server.h"
#include "exchange_auth_info.h"
#include "exchange_auth_info_client.h"
#include "add_auth_info.h"
#include "remove_auth_info.h"
#include "add_auth_info_client.h"
#include "remove_auth_info_client.h"

#ifdef DESC
#undef DESC
#endif
#define DESC(...) 1

static int32_t proc_pake_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_pake_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_sts_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_exchange_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_exchange_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_add_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_remove_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_add_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_remove_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_sec_clone_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static int32_t proc_inform_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);
static bool check_hichain_state_is_success(struct hichain *hichain, const struct header_analysis *nav);
static int32_t get_operation_code(const struct header_analysis *nav, const struct message *receive);
static bool is_message_illegal(int32_t operation_code, int32_t modular);
static int32_t proc_sts_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);

typedef int32_t (*proc_message_func)(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send);

struct message_code_map {
    uint32_t code;
    int32_t modular;
    bool is_request_msg;
};

struct distribution_message {
    int32_t modular;
    bool is_request_msg;
    proc_message_func func;
};

struct check_message_powered {
    int32_t operation_code;
    int32_t modular;
};

static const struct message_code_map G_MESSAGE_CODE_MAP[] = {
    { PAKE_REQUEST, PAKE_MODULAR, true },
    { PAKE_CLIENT_CONFIRM, PAKE_MODULAR, true },
    { EXCHANGE_REQUEST, EXCHANGE_MODULAR, true },
    { AUTH_START_REQUEST, STS_MODULAR, true },
    { AUTH_ACK_REQUEST, STS_MODULAR, true },
    { ADD_AUTHINFO_REQUEST, ADD_MODULAR, true },
    { REMOVE_AUTHINFO_REQUEST, REMOVE_MODULAR, true },
    { SEC_CLONE_START_REQUEST, SEC_CLONE_MODULAR, true },
    { SEC_CLONE_ACK_REQUEST, SEC_CLONE_MODULAR, true },
    { PAKE_RESPONSE, PAKE_MODULAR, false },
    { PAKE_SERVER_CONFIRM_RESPONSE, PAKE_MODULAR, false },
    { EXCHANGE_RESPONSE, EXCHANGE_MODULAR, false },
    { AUTH_START_RESPONSE, STS_MODULAR, false },
    { AUTH_ACK_RESPONSE, STS_MODULAR, false },
    { ADD_AUTHINFO_RESPONSE, ADD_MODULAR, false },
    { REMOVE_AUTHINFO_RESPONSE, REMOVE_MODULAR, false },
    { SEC_CLONE_START_RESPONSE, SEC_CLONE_MODULAR, false },
    { SEC_CLONE_ACK_RESPONSE, SEC_CLONE_MODULAR, false },
    { INFORM_MESSAGE, INFORM_MODULAR, true }
};

static const struct distribution_message G_DISTRIBUTION_MESSAGE[] = {
    { PAKE_MODULAR, true, proc_pake_request_message },
    { PAKE_MODULAR, false, proc_pake_response_message },
    { STS_MODULAR, true, proc_sts_request_message },
    { EXCHANGE_MODULAR, true, proc_exchange_request_message },
    { EXCHANGE_MODULAR, false, proc_exchange_response_message },
    { ADD_MODULAR, true, proc_add_request_message },
    { REMOVE_MODULAR, true, proc_remove_request_message },
    { SEC_CLONE_MODULAR, true, proc_sec_clone_request_message },
    { INFORM_MODULAR, false, proc_inform_message },
    { STS_MODULAR, false, proc_sts_response_message },
    { ADD_MODULAR, false, proc_add_response_message },
    { REMOVE_MODULAR, false, proc_remove_response_message },
};

#if DESC("interface")
struct header_analysis navigate_message(uint32_t message_code)
{
    struct header_analysis nav = { INVALID_MODULAR, 0, 0 };

    for (uint32_t i = 0; i < sizeof(G_MESSAGE_CODE_MAP) / sizeof(G_MESSAGE_CODE_MAP[0]); i++) {
        if (G_MESSAGE_CODE_MAP[i].code == message_code) {
            nav.modular = G_MESSAGE_CODE_MAP[i].modular;
            nav.msg_type = message_code & 0xf; /* message_code & 0xf get low four bits of message code */
            nav.is_request_msg = G_MESSAGE_CODE_MAP[i].is_request_msg;
            break;
        }
    }
    LOGI("Message code %u, nav is %d, %d, %d", message_code, nav.modular, nav.msg_type, nav.is_request_msg);
    return nav;
}

int32_t check_message_support(struct hichain *hichain, const struct header_analysis *nav,
    const struct message *receive)
{
    if (nav->modular == 0) {
        LOGE("Receive unknow message, message code is 0x%04x", receive->msg_code);
        return HC_UNKNOW_MESSAGE;
    }

    if (!check_hichain_state_is_success(hichain, nav)) {
        return HC_STATE_ERROR;
    }

    int32_t operation_code = get_operation_code(nav, receive);
    if (operation_code == INVALID_OPERATION_CODE) {
        return HC_OPERATION_CODE_ERROR;
    } else if (operation_code == NO_OPERATION_CODE) {
        /* compare with recorded operation code and verify */
        if (is_message_illegal(hichain->operation_code, nav->modular)) {
            LOGE("Operation code is %d, message code is %u, it is inconsistency",
                hichain->operation_code, receive->msg_code);
            return HC_MESSAGE_INCONSISTENCY;
        }
    } else {
        int32_t ret = hichain->cb.confirm_receive_request(&hichain->identity, operation_code);
        if (ret != 0) {
            LOGE("Service does not allow response %d", operation_code);
            return HC_SERVICE_CONFIRM_ERROR;
        }
        hichain->operation_code = operation_code;
    }

    return HC_OK;
}

int32_t proc_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
{
    for (uint32_t i = 0; i < sizeof(G_DISTRIBUTION_MESSAGE) / sizeof(G_DISTRIBUTION_MESSAGE[0]); i++) {
        if ((nav->modular == G_DISTRIBUTION_MESSAGE[i].modular) &&
            (nav->is_request_msg == G_DISTRIBUTION_MESSAGE[i].is_request_msg)) {
            int32_t ret = G_DISTRIBUTION_MESSAGE[i].func(handle, nav, receive, send);
            LOGI("Proc_message return code is %d", ret);
            return ret;
        }
    }
    return HC_UNKNOW_MESSAGE;
}

int32_t connect_message(struct hichain *handle, struct header_analysis *nav, struct message *send)
{
    if (nav->modular != STS_MODULAR && nav->modular != PAKE_MODULAR) {
        return HC_OK;
    }
    if (nav->msg_type != STS_END_MSG) {
        return HC_OK;
    }
    if (nav->is_request_msg) { /* server does not need message connection */
        return HC_OK;
    }

    int32_t ret;

    switch (handle->operation_code) {
        case BIND:
            ret = send_exchange_request(handle, send);
            LOGI("Client build exchange request message return value is %d", ret);
            return ret;
        case AUTHENTICATE:
            send->msg_code = INVALID_MESSAGE;
            return HC_OK;
        case ADD_AUTHINFO:
            ret = send_add_request(handle, send);
            LOGI("Client build add auth info request message return value is %d", ret);
            return ret;
        case REMOVE_AUTHINFO:
            ret = send_remove_request(handle, send);
            LOGI("Client build remove auth info request message return value is %d", ret);
            return ret;
        default:
            return HC_INNER_ERROR;
    }

    return HC_OK;
}
#endif /* DESC */

static bool check_hichain_state_is_success(struct hichain *hichain, const struct header_analysis *nav)
{
    if ((nav->modular == PAKE_MODULAR) || (nav->modular == STS_MODULAR)) {
        if ((hichain->state != INIT_STATE) && (hichain->state != KEY_AGREEMENT_STATE) &&
            (hichain->last_state != INIT_STATE) && (hichain->last_state != KEY_AGREEMENT_STATE)) {
            goto error;
        }
    } else {
        if ((hichain->state != KEY_AGREEMENT_STATE) && (hichain->state != OPERATION_STATE) &&
            (hichain->last_state != KEY_AGREEMENT_STATE) && (hichain->last_state != OPERATION_STATE)) {
            goto error;
        }
    }
    return true;

error:
    LOGE("Check hichain state failed, state is %d, message nav is %d-%d-%d", hichain->state, nav->modular,
        nav->msg_type, nav->is_request_msg);
    return false;
}

static int32_t get_operation_from_pake(void *payload);
static int32_t get_operation_from_sts(void *payload);
static int32_t get_operation_code(const struct header_analysis *nav, const struct message *receive)
{
    int32_t operation_code = NO_OPERATION_CODE;

    if ((nav->modular == PAKE_MODULAR) && (nav->msg_type == PAKE_START_MSG) && nav->is_request_msg) {
        operation_code = get_operation_from_pake(receive->payload);
    } else if ((nav->modular == STS_MODULAR) && (nav->msg_type == STS_START_MSG) && nav->is_request_msg) {
        operation_code = get_operation_from_sts(receive->payload);
    }
    LOGI("Receive message had operation code is %d", operation_code);
    return operation_code;
}

static bool is_message_illegal(int32_t operation_code, int32_t modular)
{
    struct check_message_powered table[] = { { BIND, PAKE_MODULAR },
                                             { BIND, EXCHANGE_MODULAR },
                                             { AUTH_KEY_AGREEMENT, PAKE_MODULAR },
                                             { UNBIND, STS_MODULAR },
                                             { UNBIND, REMOVE_MODULAR },
                                             { AUTHENTICATE, STS_MODULAR },
                                             { ADD_AUTHINFO, STS_MODULAR },
                                             { ADD_AUTHINFO, ADD_MODULAR },
                                             { REMOVE_AUTHINFO, STS_MODULAR },
                                             { REMOVE_AUTHINFO, REMOVE_MODULAR },
                                             { SEC_CLONE_OP, STS_MODULAR },
                                             { SEC_CLONE_OP, SEC_CLONE_MODULAR } };

    for (uint32_t i = 0; i < sizeof(table) / sizeof(table[0]); i++) {
        if ((modular == table[i].modular) && (operation_code == table[i].operation_code)) {
            return false;
        }
    }
    return true;
}

static int32_t get_operation_from_pake(void *payload)
#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))
{
    int32_t permissible_code[] = { BIND, AUTH_KEY_AGREEMENT };
    struct pake_start_request_data *data = payload;

    for (uint32_t i = 0; i < sizeof(permissible_code) / sizeof(int32_t); i++) {
        if (permissible_code[i] == data->operation_code) {
            return data->operation_code;
        }
    }
    LOGE("Receive operation code %d is error", data->operation_code);
    return INVALID_OPERATION_CODE;
}
#else /* _CUT_XXX_ */
{
    (void)payload;
    return HC_UNSUPPORT;
}
#endif /* _CUT_XXX_ */

static int32_t get_operation_from_sts(void *payload)
#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_))
{
    int32_t permissible_code[] = { AUTHENTICATE, ADD_AUTHINFO, REMOVE_AUTHINFO, UNBIND, SEC_CLONE_OP };
    struct sts_start_request_data *data = payload;

    for (uint32_t i = 0; i < sizeof(permissible_code) / sizeof(int32_t); i++) {
        if (permissible_code[i] == data->operation_code) {
            return data->operation_code;
        }
    }
    LOGE("Receive operation code %d is error", data->operation_code);
    return INVALID_OPERATION_CODE;
}
#else /* _CUT_XXX_ */
{
    (void)payload;
    return HC_UNSUPPORT;
}
#endif /* _CUT_XXX_ */

/* function macro which is not called in functions */
#define CUT_EMPTY_FUNC(d_name) \
    { \
        LOGE("Receive %s message, but do not support %s", d_name, d_name); \
        (void)handle; \
        (void)nav; \
        (void)receive; \
        send->msg_code = INVALID_MESSAGE; \
        return HC_UNSUPPORT; \
    }

static int32_t proc_pake_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))
{
    DBG_OUT("Object %u proc pake %d request message", pake_server_sn(handle->pake_server), nav->msg_type);
    int32_t ret;

    if (nav->msg_type == PAKE_START_MSG) {
        ret = send_pake_start_response(handle->pake_server, receive, send);
    } else if (nav->msg_type == PAKE_END_MSG) {
        ret = send_pake_end_response(handle->pake_server, receive, send);
        if (ret == HC_OK) {
            handle->cb.set_session_key(&handle->identity, &handle->pake_server->service_key);
            (void)memset_s(handle->pake_server->service_key.session_key, HC_SESSION_KEY_LEN, 0, HC_SESSION_KEY_LEN);
        }
    } else {
        return HC_UNKNOW_MESSAGE;
    }
    return ret;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("pake request");
#endif /* _CUT_XXX_ */

static int32_t proc_pake_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_CLIENT_))
{
    DBG_OUT("Object %u proc pake %d response message", pake_client_sn(handle->pake_client), nav->msg_type);
    int32_t ret;

    if (nav->msg_type == PAKE_START_MSG) {
        ret = send_pake_end_request(handle->pake_client, receive, send);
    } else if (nav->msg_type == PAKE_END_MSG) {
        ret = receive_pake_end_response(handle->pake_client, receive);
        if (ret == HC_OK) {
            handle->cb.set_session_key(&handle->identity, &handle->pake_client->service_key);
            (void)memset_s(handle->pake_client->service_key.session_key, HC_SESSION_KEY_LEN, 0, HC_SESSION_KEY_LEN);
        }
    } else {
        return HC_UNKNOW_MESSAGE;
    }
    return ret;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("pake response");
#endif /* _CUT_XXX_ */

static int32_t proc_exchange_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_) || defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_SERVER_))
{
    DBG_OUT("Object %u proc exchange auth info request message", pake_server_sn(handle->pake_server));
    (void)nav;
    int32_t ret = send_exchange_response(handle, receive, send);

    DBG_OUT("Object %u proc exchange message, error code is %d", pake_server_sn(handle->pake_server), ret);
    return ret;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("exchange request");
#endif /* _CUT_XXX_ */

static int32_t proc_exchange_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_CLIENT_) || defined(_CUT_EXCHANGE_) || defined(_CUT_EXCHANGE_CLIENT_))
{
    DBG_OUT("Object %u proc exchange auth info response message", pake_client_sn(handle->pake_client));
    (void)nav;
    (void)send;
    int32_t ret = receive_exchange_response(handle, receive);

    send->msg_code = INVALID_MESSAGE;
    DBG_OUT("Object %u proc exchange message, error code is %d", pake_client_sn(handle->pake_client), ret);
    return ret;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("exchange response");
#endif /* _CUT_XXX_ */

static int32_t proc_sts_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_))
{
    DBG_OUT("Object %u proc sts %d request message", sts_server_sn(handle->sts_server), nav->msg_type);
    int32_t ret;

    if (nav->msg_type == STS_START_MSG) {
        ret = send_sts_start_response(handle->sts_server, receive, send);
    } else if (nav->msg_type == STS_END_MSG) {
        ret = send_sts_end_response(handle->sts_server, receive, send);
        if (ret == HC_OK) {
            handle->cb.set_session_key(&handle->identity, &handle->sts_server->service_key);
            (void)memset_s(handle->sts_server->service_key.session_key, HC_SESSION_KEY_LEN, 0, HC_SESSION_KEY_LEN);
        }
    } else {
        return HC_UNKNOW_MESSAGE;
    }
    return ret;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("sts request");
#endif /* _CUT_XXX_ */

static int32_t proc_sts_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_))
{
    DBG_OUT("Object %u proc sts %d response message.", sts_client_sn(handle->sts_client), nav->msg_type);
    int32_t ret;

    if (nav->msg_type == STS_START_MSG) {
        ret = send_sts_end_request(handle->sts_client, receive, send);
    } else if (nav->msg_type == STS_END_MSG) {
        ret = receive_sts_end_response(handle->sts_client, receive);
        if (ret == HC_OK) {
            handle->cb.set_session_key(&handle->identity, &handle->sts_client->service_key);
        }
    } else {
        return HC_UNKNOW_MESSAGE;
    }
    return ret;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("sts request");
#endif /* _CUT_XXX_ */

static int32_t proc_add_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) || defined(_CUT_ADD_) || defined(_CUT_ADD_SERVER_))
{
    DBG_OUT("Object %u proc add auth info request message", sts_server_sn(handle->sts_server));
    (void)nav;
    int32_t ret = send_add_response(handle, receive, send);

    DBG_OUT("Object %u proc add auth info request message, error code is %d",
        sts_server_sn(handle->sts_server), ret);
    return ret;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("add auth info request");
#endif /* _CUT_XXX_ */

static int32_t proc_remove_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_) || defined(_CUT_REMOVE_) || defined(_CUT_REMOVE_SERVER_))
{
    DBG_OUT("Object %u proc remove auth info request message", sts_server_sn(handle->sts_server));
    (void)nav;
    int32_t ret = send_remove_response(handle, receive, send);

    DBG_OUT("Object %u proc remove auth info message, error code is %d", sts_server_sn(handle->sts_server), ret);
    return ret;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("remove auth info request");
#endif /* _CUT_XXX_ */

static int32_t proc_add_response_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_) || defined(_CUT_ADD_) || defined(_CUT_ADD_CLIENT_))
{
    (void)nav;
    int32_t ret = receive_add_response(handle, receive);
    if (ret != HC_OK) {
        LOGE("Object %u proc add auth info request message, error code is %d",
             sts_client_sn(handle->sts_client), ret);
        return ret;
    }
    send->msg_code = INVALID_MESSAGE; /* add_auth_info receives data and process ends, does not need to send */

    return HC_OK;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("add auth info response");
#endif /* _CUT_XXX_ */

static int32_t proc_remove_response_message(struct hichain *handle, struct header_analysis *nav,
                                            struct message *receive, struct message *send)
#if !(defined(_CUT_STS_) || defined(_CUT_STS_CLIENT_) || defined(_CUT_REMOVE_) || defined(_CUT_REMOVE_CLIENT_))
{
    (void)nav;
    int32_t ret = receive_remove_response(handle, receive);
    if (ret != HC_OK) {
        LOGE("Object %u proc add auth info request message, error code is %d",
             sts_client_sn(handle->sts_client), ret);
        return ret;
    }
    send->msg_code = INVALID_MESSAGE; /* remove_auth_info receives data and process ends, does not need to send */

    return HC_OK;
}
#else /* _CUT_XXX_ */
CUT_EMPTY_FUNC("remove auth info response");
#endif /* _CUT_XXX_ */

static int32_t proc_sec_clone_request_message(struct hichain *handle, struct header_analysis *nav,
    struct message *receive, struct message *send)
#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
{
    int32_t ret;

    if (nav->msg_type == SEC_CLONE_START_MSG) {
        ret = send_sec_clone_start_response(handle->sec_clone_server, receive, send);
    } else if (nav->msg_type == SEC_CLONE_END_MSG) {
        ret = send_sec_clone_end_response(handle->sec_clone_server, receive, send);
    } else {
        return HC_UNKNOW_MESSAGE;
    }

    return ret;
}
#else /* _SUPPORT_SEC_ */
CUT_EMPTY_FUNC("sec clone request");
#endif /* _SUPPORT_SEC_ */

static int32_t proc_inform_message(struct hichain *handle, struct header_analysis *nav, struct message *receive,
    struct message *send)
{
    (void)handle;
    (void)nav;
    (void)receive;
    send->msg_code = INVALID_MESSAGE;
    LOGE("Receive inform message");
    return HC_OK;
}
