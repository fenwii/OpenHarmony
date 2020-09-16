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

#include "key_agreement_client.h"
#include "base.h"
#include "hichain.h"
#include "log.h"

#ifdef DESC
#undef DESC
#endif
#define DESC(...) 1

static bool is_state_error(struct key_agreement_client *handle, enum protocol_action action);

void init_client(struct key_agreement_client *handle, struct client_virtual_func_group *funcs)
{
    check_ptr_return(handle);
    check_ptr_return(funcs);
    init_protocol(&handle->protocol_base_info);
    handle->package_funcs = *funcs;
}

int32_t send_start_request(void *handle, void *send_data)
{
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(send_data, HC_INPUT_ERROR);
    struct key_agreement_client *client = (struct key_agreement_client *)handle;
    struct key_agreement_protocol *base = &client->protocol_base_info;

    DBG_OUT("Object %u begin send start request data", base->sn);
    if (is_state_error(client, SEND_START_REQUEST)) {
        LOGE("Object %u state error", base->sn);
        return PROTOCOL_STATE_ERROR;
    }
    struct client_virtual_func_group *funcs = &client->package_funcs;
    int32_t ret = funcs->build_start_request_data(handle, send_data);
    if (ret != HC_OK) {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u build start request data failed, error code is %d", base->sn, ret);
        return ret;
    }
    set_state(base, START_REQUEST);
    set_last_time_sec(base);
    DBG_OUT("Object %u send start request data success", base->sn);
    return HC_OK;
}

int32_t send_end_request(void *handle, void *receive_data, void *send_data)
{
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(receive_data, HC_INPUT_ERROR);
    check_ptr_return_val(send_data, HC_INPUT_ERROR);
    struct key_agreement_client *client = (struct key_agreement_client *)handle;
    struct key_agreement_protocol *base = &client->protocol_base_info;

    DBG_OUT("Object %u begin receive start response data and send end request data", base->sn);
    if (is_state_error(client, SEND_END_REQUEST)) {
        LOGE("Object %u state error", base->sn);
        return PROTOCOL_STATE_ERROR;
    }
    struct client_virtual_func_group *funcs = &client->package_funcs;
    int32_t ret = funcs->parse_start_response_data(handle, receive_data);
    if (ret != HC_OK) {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u parse start response data failed, error code is %d", base->sn, ret);
        return ret;
    }
    ret = funcs->build_end_request_data(handle, send_data);
    if (ret != HC_OK) {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u build end request data failed, error code is %d", base->sn, ret);
        return ret;
    }

    set_state(base, END_REQUEST);
    set_last_time_sec(base);
    DBG_OUT("Object %u receive start response data and send end request data success", base->sn);
    return HC_OK;
}

int32_t receive_end_response(void *handle, void *receive_data)
{
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(receive_data, HC_INPUT_ERROR);
    struct key_agreement_client *client = (struct key_agreement_client *)handle;
    struct key_agreement_protocol *base = &client->protocol_base_info;

    DBG_OUT("Object %u begin receive end response data", base->sn);
    if (is_state_error(client, RECEIVE_END_RESPONSE)) {
        LOGE("Object %u state error", base->sn);
        return PROTOCOL_STATE_ERROR;
    }
    struct client_virtual_func_group *funcs = &client->package_funcs;
    int32_t ret = funcs->parse_end_response_data(handle, receive_data);
    if (ret != HC_OK) {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u parse end response data failed, error code is %d", base->sn, ret);
        return ret;
    }

    set_state(base, PROTOCOL_FINISH);
    set_last_time_sec(base);
    DBG_OUT("Object %u receive end response data success", base->sn);
    return HC_OK;
}

static bool is_state_error(struct key_agreement_client *handle, enum protocol_action action)
{
    struct key_agreement_protocol *base = &handle->protocol_base_info;
    enum protocol_state state = base->state;
    DBG_OUT("Object %u state is %d, action is %d", base->sn, state, action);

    if (action == SEND_START_REQUEST) {
        return (state == PROTOCOL_INIT) ? false : true;
    } else if (action == SEND_END_REQUEST) {
        return (state == START_REQUEST) ? false : true;
    } else if (action == RECEIVE_END_RESPONSE) {
        return (state == END_REQUEST) ? false : true;
    } else {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u state is error", base->sn);
        return true;
    }
}
