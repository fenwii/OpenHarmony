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

#ifndef __PARSEDATA_H__
#define __PARSEDATA_H__

#include <stdint.h>
#include "base.h"
#include "mem_stat.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFINE_EMPTY_STRUCT_FUNC(d_name) \
    void *parse_##d_name(const char *payload, enum json_object_data_type data_type) \
    { \
        (void)payload; \
        (void)data_type; \
        return NULL; \
    } \
    void free_##d_name(void *obj) \
    { \
        (void)obj; \
    } \
    char *make_##d_name(void *data) \
    { \
        (void)data; \
        return "Current devices do not support this feature."; \
    }


struct pass_through_data {
    uint32_t message_code;
    void *payload_data;
};

uint32_t parse_header(const char *data);

struct pass_through_data *parse_data(const char *data);
void free_data(struct pass_through_data *data);

void *parse_payload(const char *payload, enum json_object_data_type data_type);
void free_payload(char *data, enum json_object_data_type data_type);

/* pake request */
void *parse_pake_request(const char *payload, enum json_object_data_type data_type);
void free_pake_request(void *obj);
char *make_pake_request(void *data);

/* pake response */
void *parse_pake_response(const char *payload, enum json_object_data_type data_type);
void free_pake_response(void *obj);
char *make_pake_response(void *data);

/* pake client confirm */
void *parse_pake_client_confirm(const char *payload, enum json_object_data_type data_type);
void free_pake_client_confirm(void *obj);
char *make_pake_client_confirm(void *data);

/* pake server confirm */
void *parse_pake_server_confirm(const char *payload, enum json_object_data_type data_type);
void free_pake_server_confirm(void *obj);
char *make_pake_server_confirm(void *data);

/* sts auth start request */
void *parse_auth_start_request(const char *payload, enum json_object_data_type data_type);
void free_auth_start_request(void *obj);
char *make_auth_start_request(void *data);

/* sts auth start response */
void *parse_auth_start_response(const char *payload, enum json_object_data_type data_type);
void free_auth_start_response(void *obj);
char *make_auth_start_response(void *data);

/* sts auth ack request */
void *parse_auth_ack_request(const char *payload, enum json_object_data_type data_type);
void free_auth_ack_request(void *obj);
char *make_auth_ack_request(void *data);

/* sts auth ack response */
void *parse_auth_ack_response(const char *payload, enum json_object_data_type data_type);
void free_auth_ack_response(void *obj);
char *make_auth_ack_response(void *data);

/* add auth request */
void *parse_add_auth_info_request(const char *payload, enum json_object_data_type data_type);
void free_add_auth_info_request(void *obj);
char *make_add_auth_info_request(void *data);

/* add auth response */
void *parse_add_auth_info_response(const char *payload, enum json_object_data_type data_type);
void free_add_auth_info_response(void *obj);
char *make_add_auth_info_response(void *data);

/* add auth data */
void *parse_add_auth_info_data(const char *payload, enum json_object_data_type data_type);
void free_add_auth_info_data(void *obj);
char *make_add_auth_info_data(void *data);

/* rmv auth request */
void *parse_rmv_auth_info_request(const char *payload, enum json_object_data_type data_type);
void free_rmv_auth_info_request(void *obj);
char *make_rmv_auth_info_request(void *data);

/* rmv auth response */
void *parse_rmv_auth_info_response(const char *payload, enum json_object_data_type type);
void free_rmv_auth_info_response(void *obj);
char *make_rmv_auth_info_response(void *data);

/* rmv auth data */
void *parse_rmv_auth_info_data(const char *payload, enum json_object_data_type data_type);
void free_rmv_auth_info_data(void *obj);
char *make_rmv_auth_info_data(void *data);

/* exchange request */
void *parse_exchange_request(const char *payload, enum json_object_data_type data_type);
void free_exchange_request(void *obj);
char *make_exchange_request(void *data);

/* exchange response */
void *parse_exchange_response(const char *payload, enum json_object_data_type data_type);
void free_exchange_response(void *obj);
char *make_exchange_response(void *data);

/* exchange authdata */
void *parse_exchange_data(const char *payload, enum json_object_data_type data_type);
void free_exchange_data(void *obj);
char *make_exchange_data(void *data);

/* sec_clone data */
void *sec_clone_parse_client_request(const char *payload, enum json_object_data_type data_type);
void sec_clone_free_client_request(void *obj);
char *sec_clone_make_srv_proof(void *data);
void *sec_clone_parse_client_ack(const char *payload, enum json_object_data_type data_type);
void sec_clone_free_client_ack(void *obj);
char *sec_clone_make_clone_ret(void *data);
void *sec_clone_parse_start_resp(const char *payload, enum json_object_data_type data_type);
void *sec_clone_parse_ack_resp(const char *payload, enum json_object_data_type data_type);

/* inform message */
void *parse_inform_message(const char *payload, enum json_object_data_type data_type);
void free_inform_message(void *obj);
char *make_inform_message(void *data);

/* improt data message */
void *parse_import_add_auth_data(const char *payload, enum json_object_data_type data_type);
void free_import_add_auth_data(void *obj);

#define FIELD_ADD_TYPE        "addType"
#define FIELD_ADD_ID          "addId"
#define FIELD_ADD_KEY         "addKey"
#define FIELD_AUTH_DATA       "authData"
#define FIELD_AUTH_RETURN     "authReturn"
#define FIELD_AUTH_ID         "authId"
#define FIELD_AUTH_PK         "authPk"
#define FIELD_AUTH_FORM       "authForm"
#define FIELD_ADD_AUTH_INFO   "addAuthInfo"
#define FIELD_ADD_RETURN      "addReturn"
#define FIELD_CHALLENGE       "challenge"
#define FIELD_CURRENT_VERSION "currentVersion"
#define FIELD_EPK             "epk"
#define FIELD_EPK_LEN         "epkLen"
#define FIELD_EX_AUTH_INFO    "exAuthInfo"
#define FIELD_ERROR_CODE      "errorCode"
#define FIELD_KCF_DATA        "kcfData"
#define FIELD_KEY_LENGTH      "keyLength"
#define FIELD_KEY_TYPE        "keyType"
#define FIELD_MESSAGE         "message"
#define FIELD_MIN_VERSION     "minVersion"
#define FIELD_OPERATION_CODE  "operationCode"
#define FIELD_OWNER_ID        "ownerId"
#define FIELD_PERMISSION      "Permission"
#define FIELD_PAYLOAD         "payload"
#define FIELD_PUBLIC_KEY      "publicKey"
#define FIELD_PKG_NAME        "pkgName"
#define FIELD_PEER_AUTH_ID    "peerAuthId"
#define FIELD_PEER_USER_TYPE  "peerUserType"
#define FIELD_RMV_TYPE        "rmvType"
#define FIELD_RMV_ID          "rmvId"
#define FIELD_RMV_AUTH_INFO   "rmvAuthInfo"
#define FIELD_RMV_RETURN      "rmvReturn"
#define FIELD_SALT            "salt"
#define FIELD_SUPPORT_256_MOD "support256mod"
#define FIELD_SERVICE_TYPE    "serviceType"
#define FIELD_VERSION         "version"

#ifdef __cplusplus
}
#endif
#endif /* __PARSEDATA_H__ */
