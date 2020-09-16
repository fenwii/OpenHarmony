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

#include "auth_info.h"
#include <securec.h>
#include "log.h"
#include "mem_stat.h"
#include "huks_adapter.h"

#define HC_AUTH_DECRYPT_LEN 300

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))
const struct pake_session_key *get_pake_session_key(const struct hichain *hichain)
{
    if (hichain->pake_server == NULL) {
        LOGE("Pake server object is NULL");
        return NULL;
    }
    return &hichain->pake_server->session_key;
}

const struct challenge *get_pake_self_challenge(const struct hichain *hichain)
{
    if (hichain->pake_server == NULL) {
        LOGE("Pake server object is NULL");
        return NULL;
    }
    return &hichain->pake_server->self_challenge;
}

const struct challenge *get_pake_peer_challenge(const struct hichain *hichain)
{
    if (hichain->pake_server == NULL) {
        LOGE("Pake server object is NULL");
        return NULL;
    }
    return &hichain->pake_server->peer_challenge;
}

const struct hc_auth_id *get_pake_self_auth_id(const struct hichain *hichain)
{
    if (hichain->pake_server == NULL) {
        LOGE("Pake server object is NULL");
        return NULL;
    }
    return &hichain->pake_server->self_id;
}

#endif /* _CUT_XXX_ */

#if !(defined(_CUT_STS_) || defined(_CUT_STS_SERVER_))
const struct sts_session_key *get_sts_session_key(const struct hichain *hichain)
{
    if (hichain->sts_server == NULL) {
        LOGE("Sts server object is NULL");
        return NULL;
    }
    return &hichain->sts_server->session_key;
}

#endif /* _CUT_XXX_ */

int32_t encrypt_payload(const struct var_buffer *key, const struct uint8_buff *plain,
    const char *aad, struct uint8_buff *payload)
{
    struct aes_aad aes_aad;
    (void)memset_s(&aes_aad, sizeof(aes_aad), 0, sizeof(aes_aad));
    if (strcpy_s((char *)aes_aad.aad, sizeof(aes_aad.aad), aad) != EOK) {
        LOGE("What happened was that the probability was zero"); /* caller perceives memery error, no return */
    }
    aes_aad.length = strlen(aad);
    int32_t ret = aes_gcm_encrypt((struct var_buffer *)key, plain, &aes_aad, payload);
    if (ret != HC_OK) {
        LOGE("Encrypt payload failed, error code is %d", ret);
        return HC_ENCRYPT_FAILED;
    }
    DBG_OUT("Encrypt payload success");
    return HC_OK;
}

int32_t decrypt_payload(const struct var_buffer *key, const struct uint8_buff *payload,
    const char *aad, struct uint8_buff *plain)
{
    plain->val = (uint8_t *)MALLOC(HC_AUTH_DECRYPT_LEN);
    if (plain->val == NULL) {
        LOGE("Malloc failed");
        return HC_MALLOC_FAILED;
    }
    plain->size = HC_AUTH_DECRYPT_LEN;
    plain->length = 0;
    (void)memset_s(plain->val, plain->size, 0, plain->size);
    struct aes_aad aes_aad;
    (void)memset_s(&aes_aad, sizeof(aes_aad), 0, sizeof(aes_aad));
    if (strcpy_s((char *)aes_aad.aad, sizeof(aes_aad.aad), aad) != EOK) {
        LOGE("What happened was that the probability was zero"); /* caller perceives memery error, no return */
    }
    aes_aad.length = strlen(aad);
    int32_t ret = aes_gcm_decrypt((struct var_buffer *)key, payload, &aes_aad, plain);
    if (ret != HC_OK) {
        LOGE("Decrypt payload failed");
        FREE(plain->val);
        plain->val = NULL;
        plain->size = 0;
        return HC_DECRYPT_FAILED;
    }
    DBG_OUT("Decrypt payload success");
    return HC_OK;
}

struct auth_info_message *malloc_auth_info_msg(uint32_t size)
{
    struct auth_info_message *data = (struct auth_info_message *)MALLOC(sizeof(struct auth_info_message));
    if (data == NULL) {
        LOGE("Malloc struct remove_response_data failed");
        return NULL;
    }
    (void)memset_s(data, sizeof(*data), 0, sizeof(*data));
    data->cipher.val = (uint8_t *)MALLOC(size);
    if (data->cipher.val == NULL) {
        LOGE("Malloc remove response val failed");
        FREE(data);
        return NULL;
    }
    (void)memset_s(data->cipher.val, size, 0, size);
    data->cipher.size = size;
    data->cipher.length = 0;
    return data;
}

void free_auth_info_msg(struct auth_info_message *data)
{
    FREE(data->cipher.val);
    data->cipher.val = NULL;
    FREE(data);
}

int32_t save_auth_info(const struct hichain *hichain, int32_t pair_type, struct auth_info_cache *cache)
{
    struct service_id service_id = generate_service_id(&hichain->identity);
    if (service_id.length == 0) {
        LOGE("Generate service id failed");
        return HC_GEN_SERVICE_ID_FAILED;
    }
    enum huks_key_alias_type alias_type = (cache->user_type == HC_USER_TYPE_ACCESSORY) ?
                                           KEY_ALIAS_ACCESSOR_PK : KEY_ALIAS_CONTROLLER_PK;
    struct hc_key_alias alias = generate_key_alias(&service_id, &cache->auth_id, alias_type);
    if (alias.length == 0) {
        LOGE("Generate key alias failed");
        return HC_GEN_ALIAS_FAILED;
    }
    int32_t ret = import_lt_public_key(&alias, &cache->ltpk, cache->user_type, pair_type, &cache->auth_id);
    if (ret != HC_OK) {
        LOGE("Import ltpk failed, error code is %d", ret);
        return HC_SAVE_LTPK_FAILED;
    }
    ret = check_lt_public_key_exist(&alias);
    if (ret != HC_OK) {
        LOGE("Check ltpk failed, error code is %d", ret);
        return HC_SAVE_LTPK_FAILED;
    }
    DBG_OUT("Save ltpk success");
    return HC_OK;
}

struct auth_info_cache *build_auth_client_info(struct hc_auth_id auth_id, int32_t user_type)
{
    struct auth_info_cache *auth_info = MALLOC(sizeof(struct auth_info_cache));
    if (auth_info == NULL) {
        LOGE("Malloc failed");
        return NULL;
    }
    (void)memset_s(auth_info, sizeof(*auth_info), 0, sizeof(*auth_info));
    auth_info->user_type = user_type;
    auth_info->auth_id = auth_id;

    return auth_info;
}

void destroy_auth_client(struct auth_info_cache *auth_info)
{
    if (auth_info == NULL) {
        LOGE("Destroy auth info client object failed");
        return;
    }
    FREE(auth_info);
}
