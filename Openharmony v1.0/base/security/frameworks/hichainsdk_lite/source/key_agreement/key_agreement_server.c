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

#include "key_agreement_server.h"
#include "base.h"
#include "hichain.h"
#include "log.h"

#ifdef DESC
#undef DESC
#endif
#define DESC(...) 1

static bool is_state_error(struct key_agreement_server *handle, enum protocol_action action);

#if DESC("interface")
void init_server(struct key_agreement_server *handle, const struct server_virtual_func_group *funcs)
{
    check_ptr_return(handle);
    check_ptr_return(funcs);
    init_protocol(&handle->protocol_base_info);
    handle->package_funcs = *funcs;
}

int32_t send_start_response(void *handle, void *receive_data, void *send_data)
{
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(receive_data, HC_INPUT_ERROR);
    check_ptr_return_val(send_data, HC_INPUT_ERROR);
    struct key_agreement_server *server = handle;
    struct key_agreement_protocol *base = &server->protocol_base_info;

    DBG_OUT("Object %u begin receive start request data and send start response data", base->sn);
    if (is_state_error(server, SEND_START_RESPONSE)) {
        LOGE("Object %u state error", base->sn);
        return PROTOCOL_STATE_ERROR;
    }
    const struct server_virtual_func_group *funcs = &server->package_funcs;
    int32_t ret = funcs->parse_start_request_data(handle, receive_data);
    if (ret != HC_OK) {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u parse start request data failed, error code is %d", base->sn, ret);
        return ret;
    }
    ret = funcs->build_start_response_data(handle, send_data);
    if (ret != HC_OK) {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u build start response data failed, error code is %d", base->sn, ret);
        return ret;
    }
    set_state(base, START_RESPONSE);
    set_last_time_sec(base);
    DBG_OUT("Object %u receive start request data send start response data succcess", base->sn);
    return HC_OK;
}

int32_t send_end_response(void *handle, void *receive_data, void *send_data)
{
    check_ptr_return_val(handle, HC_INPUT_ERROR);
    check_ptr_return_val(receive_data, HC_INPUT_ERROR);
    check_ptr_return_val(send_data, HC_INPUT_ERROR);
    struct key_agreement_server *server = handle;
    struct key_agreement_protocol *base = &server->protocol_base_info;

    DBG_OUT("Object %u begin receive end request data and send end response data", base->sn);
    if (is_state_error(server, SEND_END_RESPONSE)) {
        LOGE("Object %u state error", base->sn);
        return PROTOCOL_STATE_ERROR;
    }
    const struct server_virtual_func_group *funcs = &server->package_funcs;
    int32_t ret = funcs->parse_end_request_data(handle, receive_data);
    if (ret != HC_OK) {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u parse end request data failed, error code is %d", base->sn, ret);
        return ret;
    }
    ret = funcs->build_end_response_data(handle, send_data);
    if (ret != HC_OK) {
        set_state(base, PROTOCOL_ERROR);
        LOGE("Object %u build end response data failed, error code is %d", base->sn, ret);
        return ret;
    }
    set_state(base, PROTOCOL_FINISH);
    set_last_time_sec(base);
    DBG_OUT("Object %u receive end request data send end response data succcess", base->sn);
    return HC_OK;
}
#endif /* DESC */

static bool is_state_error(struct key_agreement_server *handle, enum protocol_action action)
{
    struct key_agreement_protocol *base = &handle->protocol_base_info;
    enum protocol_state state = base->state;
    enum protocol_state last_state = base->last_state;

    DBG_OUT("Object %u state is %d, action is %d", base->sn, state, action);
    if (action == SEND_START_RESPONSE) {
        return ((state == PROTOCOL_INIT) || (last_state == PROTOCOL_INIT)) ? false : true;
    } else if (action == SEND_END_RESPONSE) {
        return ((state == START_RESPONSE) || (last_state == START_RESPONSE)) ? false : true;
    }
    set_state(base, PROTOCOL_ERROR);
    LOGE("Object %u state is error", base->sn);
    return true;
}
