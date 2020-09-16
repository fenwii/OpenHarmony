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

#ifndef __HICHAIN_H__
#define __HICHAIN_H__

#include <stdint.h>

#if defined(_WINDOWS)
#ifdef DLL_EXPORT
#define DLL_API_PUBLIC __declspec(dllexport)
#else
#define DLL_API_PUBLIC __declspec(dllimport)
#endif
#else
#define DLL_API_PUBLIC __attribute__ ((visibility("default")))
#endif

#ifdef HILINK_E2E_SECURITY_CONFIG
#define _SCANTY_MEMORY_
#endif

enum hc_error {
    HC_OK = 0,
    HC_INPUT_ERROR,
    HC_INNER_ERROR,
    HC_STATE_ERROR,
    HC_SERVICE_CONFIRM_ERROR,
    HC_UNKNOW_MESSAGE,
    HC_NO_MESSAGE_TO_SEND,
    HC_REPEATED_REFERENCE,
    HC_NEED_DEPEND,
    HC_BUILD_OBJECT_FAILED,
    HC_BUILD_SEND_DATA_FAILED,
    HC_MALLOC_FAILED,
    HC_VERSION_UNSUPPORT,
    HC_LARGE_PRIME_NUMBER_LEN_UNSUPPORT,
    HC_CAL_BIGNUM_EXP_FAILED,
    HC_INTERNAL_ERROR,
    HC_IMPORT_AUTH_DATA_FAILED,
    HC_VERIFY_PROOF_FAILED,
    HC_GENERATE_PROOF_FAILED,
    HC_GENERATE_SESSION_KEY_FAILED,
    HC_ST_KEY_PAIR_FAILED,
    HC_COMPUTE_STS_SHARED_SECRET_FAILED,
    HC_COMPUTE_HKDF_FAILED,
    HC_PAKE_SESSION_KEY_ERROR,
    HC_PAKE_OBJECT_ERROR,
    HC_STS_OBJECT_ERROR,
    HC_DECRYPT_FAILED,
    HC_ENCRYPT_FAILED,
    HC_SIGN_TOO_SHORT,
    HC_VERIFY_EXCHANGE_FAILED,
    HC_SIGN_EXCHANGE_FAILED,
    HC_SAVE_LTPK_FAILED,
    HC_DELETE_LTPK_FAILED,
    HC_GET_LTPK_FAILED,
    HC_GEN_ALIAS_FAILED,
    HC_GEN_SERVICE_ID_FAILED,
    HC_GEN_RANDOM_FAILED,
    HC_UNSUPPORT,
    HC_MESSAGE_INCONSISTENCY,
    HC_OPERATION_CODE_ERROR,
    HC_MEMCPY_ERROR,
    PROTOCOL_STATE_ERROR,
    PROTOCOL_SET_STATE_ERROR,
    PROTOCOL_TIMEOUT_ERROR,
    PROTOCOL_SAHRED_SECRET_FAIL,
    PROTOCOL_HKDF_FAIL,
    PROTOCOL_SHA_FAIL,
    PROTOCOL_RAND_FAIL,
    PROTOCOL_ENCRYPT_FAIL,
    PROTOCOL_DECRYPT_FAIL,
    PROTOCOL_VERIFY_DATA_FAIL,
    PROTOCOL_KEY_ALG_FAIL,
    PROTOCOL_RESULT_ERROR,
    KEK_NOT_EXIST,
    DEK_NOT_EXIST,
    TEMP_KEY_GEN_FAILED,
};

enum hc_type {
    HC_CENTRE = 1,
    HC_ACCESSORY,
};

enum hc_user_type {
    HC_USER_TYPE_ACCESSORY = 0,
    HC_USER_TYPE_CONTROLLER = 1
};

enum hc_operation {
    INVALID_OPERATION_CODE = -1,
    NO_OPERATION_CODE = 0,
    BIND = 1,
    AUTHENTICATE,
    ADD_AUTHINFO,
    REMOVE_AUTHINFO,
    UNBIND,
    AUTH_KEY_AGREEMENT,
    REGISTER,
    SEC_CLONE_OP,
    REMOVE_ALL_AUTHINFO,
    GET_PEER_USER_TYPE,
    GENERATE_KEY_PAIR = 99
};

enum hc_result {
    END_SUCCESS = 0,
    END_FAILED,
    KEY_AGREEMENT_PROCESSING,
    KEY_AGREEMENT_END,
    OPERATION_PROCESSING,
    OPERATION_END,
};

enum hc_export_type {
    EXPORT_DATA_FULL_AUTH_INFO   = 0,
    EXPORT_DATA_LITE_AUTH_INFO   = 1,
    EXPORT_DATA_SIGNED_AUTH_INFO = 2
};

#define HC_AUTH_ID_BUFF_LEN 64
#define HC_SALT_BUFF_LEN    16
#define HC_PIN_BUFF_LEN     16
#define HC_SESSION_KEY_LEN  128
#define HC_KEY_TYPE_LEN     2
#define HC_BASE_KEY_NUM     5

#if !defined(_SCANTY_MEMORY_)
#define HC_PACKAGE_NAME_BUFF_LEN    256
#define HC_SERVICE_TYPE_BUFF_LEN    256
#else /* _SCANTY_MEMORY_ */
#define HC_PACKAGE_NAME_BUFF_LEN    16
#define HC_SERVICE_TYPE_BUFF_LEN    16
#endif /* _SCANTY_MEMORY_ */
#define HC_KEY_ALIAS_MAX_LEN        64

/* alia list max size */
#if defined(_SCANTY_MEMORY_)
#define HC_PUB_KEY_ALIAS_MAX_NUM    15
#elif defined(_SUPPORT_SEC_CLONE_SERVER_)
#define HC_PUB_KEY_ALIAS_MAX_NUM    120
#else
#define HC_PUB_KEY_ALIAS_MAX_NUM    20
#endif

enum hc_trust_peer_result {
    HC_NOT_TRUST_PEER = 0,
    HC_BINDED_TRUST_PEER,
    HC_AUTHED_TRUST_PEER,
    HC_ACCESSORY_TRUST_PEER
};

typedef void *hc_handle;

struct uint8_buff {
    uint8_t *val;
    uint32_t size;
    uint32_t length;
};

struct hc_pin {
    uint32_t length;
    uint8_t pin[HC_PIN_BUFF_LEN];
};

struct hc_salt {
    uint32_t length;
    uint8_t salt[HC_SALT_BUFF_LEN];
};

struct hc_auth_id {
    uint32_t length;
    uint8_t auth_id[HC_AUTH_ID_BUFF_LEN];
};

struct hc_session_key {
    uint32_t length;
    uint8_t session_key[HC_SESSION_KEY_LEN];
};

struct hc_package_name {
    uint32_t length;
    uint8_t name[HC_PACKAGE_NAME_BUFF_LEN];
};

struct hc_service_type {
    uint32_t length;
    uint8_t type[HC_SERVICE_TYPE_BUFF_LEN];
};

struct hc_user_info {
    struct hc_auth_id auth_id;
    int32_t user_type;
};

struct operation_parameter {
    struct hc_auth_id self_auth_id;
    struct hc_auth_id peer_auth_id;
    uint32_t key_length;
};

struct hc_key_alias {
    uint32_t length;
    uint8_t key_alias[HC_KEY_ALIAS_MAX_LEN];
};

struct session_identity {
    uint32_t session_id;
    struct hc_package_name package_name;
    struct hc_service_type service_type;
    void *context;
};

typedef void (*transmit_cb)(const struct session_identity *identity, const void *data, uint32_t length);
typedef void (*get_protocol_params_cb)(const struct session_identity *identity, int32_t operation_code,
                                       struct hc_pin *pin, struct operation_parameter *para);
typedef void (*set_session_key_func)(const struct session_identity *identity,
                                     const struct hc_session_key *session_key);
typedef void (*set_service_result_func)(const struct session_identity *identity, int32_t result);
typedef int32_t (*confirm_receive_request_func)(const struct session_identity *identity, int32_t operation_code);

struct hc_call_back {
    transmit_cb transmit;
    get_protocol_params_cb get_protocol_params;
    set_session_key_func set_session_key;
    set_service_result_func set_service_result;
    confirm_receive_request_func confirm_receive_request;
};

typedef void (*log_func)(const char *tag, const char *func_name, const char *format, ...);

struct log_func_group {
    log_func log_d;
    log_func log_i;
    log_func log_w;
    log_func log_e;
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Register log operation callback
 *
 * para log:  The log callback functions group
 * return  void
 */
DLL_API_PUBLIC void registe_log(struct log_func_group *log);

/*
 * Get hichain instance
 *
 * para identity:  basic information of session
 * pare type:  hichain device type
 * hc_call_back:  hichain callback functions
 * return  hichain instance
 */
DLL_API_PUBLIC hc_handle get_instance(const struct session_identity *identity, enum hc_type type,
    const struct hc_call_back *call_back);

/*
 * Destroy hichain instance
 *
 * para handle:  hichain instance
 * return  void
 */
DLL_API_PUBLIC void destroy(hc_handle *handle);

/*
 * set context in handle
 *
 * para handle:  hichain instance
 * para context: put in an object in instance
 * return  void
 */
DLL_API_PUBLIC void set_context(hc_handle handle, void *context);

/*
 * Hichain receives message data
 *
 * para handle:  hichain instance
 * para data:  message data
 * return  0 ok, others error
 */
DLL_API_PUBLIC int32_t receive_data(hc_handle handle, struct uint8_buff *data);

/*
 * Hichain receives message data , data is json object
 *
 * para handle:  hichain instance
 * para json_object:  message data
 * return  0 ok, others error
 */
DLL_API_PUBLIC int32_t receive_data_with_json_object(hc_handle handle, const void *json_object);

#ifndef _CUT_API_

/*
 * Initialize the center device
 *
 * para hc_package_name:  the package name of the product
 * para hc_service_type:  the type of the product
 * para hc_auth_id:  the auth id of controller
 * para dek:  the alias of secret key used for encryption and decryption of data
 * return  0 ok, others error
 */
DLL_API_PUBLIC int32_t init_center(const struct hc_package_name *package_name,
    const struct hc_service_type *service_type, const struct hc_auth_id *auth_id, struct hc_key_alias *dek);

/*
 * Start pake module
 *
 * para handle:  hichain instance
 * para params:  operating parameter
 * return  0 ok, others error
 */
DLL_API_PUBLIC int32_t start_pake(hc_handle handle, const struct operation_parameter *params);

/*
 * Authenticate peer identity and build session key
 *
 * para handle:  hichain instance
 * para params:  operating parameter
 * return  0 ok, others error
 */
DLL_API_PUBLIC int32_t authenticate_peer(hc_handle handle, struct operation_parameter *params);

/*
 * Delete local saved authentication
 *
 * para handle:  hichain instance
 * para hc_user_info:  user to be deleted
 * return  0 ok, others error
 */
DLL_API_PUBLIC int32_t delete_local_auth_info(hc_handle handle, struct hc_user_info *user_info);

/*
 * Import auth info of bounded trust accessory
 *
 * para handle:  hichain instance
 * para hc_user_info:  the information of Authorized user
 * para hc_auth_id:  the auth id of device
 * para auth_info_type:  the export auth info type: 0: full authentication data
 *                                                  1: lite authentication data
 *                                                  2: signed authentication data
 * para auth_info:  auth info of accessory
 * return  0 ok, others error
 */
DLL_API_PUBLIC int32_t import_auth_info(hc_handle handle, struct hc_user_info *user_info, struct hc_auth_id *auth_id,
    enum hc_export_type auth_info_type, struct uint8_buff *auth_info);

/*
 * Share the bound device to other users
 *
 * para handle:  hichain instance
 * para params:  operating parameter, self_auth_id: controller auth id, peer_auth_id: peer auth id
 * para auth_id:  authorized auth id
 * para user_type:  authorized user type. 0 : ACCESSORY ; 1 : CONTROLLER
 * return  0 ok, others error
 */
int32_t add_auth_info(hc_handle handle, const struct operation_parameter *params,
    const struct hc_auth_id *auth_id, int32_t user_type);

/*
 * Remove user authorization of an accessory
 *
 * para handle:  hichain instance
 * para params:  operating parameter, self_auth_id: controller auth id, peer_auth_id: peer auth id
 * para auth_id:  unauthorized auth id
 * para user_type:  unauthorized user type. 0 : ACCESSORY ; 1 : CONTROLLER
 * return  0 ok, others error
 */
int32_t remove_auth_info(hc_handle handle, const struct operation_parameter *params,
    const struct hc_auth_id *auth_id, int32_t user_type);

/*
 * Delete local saved authentication
 *
 * para handle:  hichain instance
 * para user_info:  user to be deleted
 * return  0 ok, others error
 */
int32_t delete_local_auth_info(hc_handle handle, struct hc_user_info *user_info);

/*
 * Judge trusted peer
 *
 * para handle:  hichain instance
 * para hc_user_info:  user to be judged
 * return 0 untrusted, 1 trusted(bind), 2 trusted(auth)
 */
DLL_API_PUBLIC int32_t is_trust_peer(hc_handle handle, struct hc_user_info *user_info);

/*
 * List trusted peers
 *
 * para handle:  hichain instance
 * para trust_user_type:  the type of peer. 0 : ACCESSORY ; 1 : CONTROLLER
 * para owner_auth_id:  input null, output binding list; input owner, output auth list;others, output null
 * para auth_id_list:  list to receive auth id
 * return  number of trusted peers
 */
DLL_API_PUBLIC uint32_t list_trust_peers(hc_handle handle, int32_t trust_user_type,
    struct hc_auth_id *owner_auth_id, struct hc_auth_id **auth_id_list);
#endif /* _CUT_XXX_ */

/*
 * Set self authId
 *
 * para handle:  hichain instance
 * para data:  the data of auth id
 * return  void
 */
DLL_API_PUBLIC void set_self_auth_id(hc_handle handle, struct uint8_buff *data);

#ifdef __cplusplus
}
#endif

#endif /* __HICHAIN_H__ */
