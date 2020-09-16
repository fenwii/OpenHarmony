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

#include "pake_server.h"
#include "log.h"

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_SERVER_))

#include <securec.h>
#include "huks_adapter.h"
#include "mem_stat.h"

#ifdef DESC
#undef DESC
#endif
#define DESC(...) 1

static int32_t parse_start_request_data(void *handle, void *receive_data);
static int32_t build_start_response_data(void *handle, void *send_data);
static int32_t parse_end_request_data(void *handle, void *receive_data);
static int32_t build_end_response_data(void *handle, void *send_data);

#define HICHAIN_SPEKE_BASE_INFO       "hichain_speke_base_info"
#define HICHAIN_RETURN_KEY            "hichain_return_key"
#define HICHAIN_SPEKE_SESSIONKEY_INFO "hichain_speke_sessionkey_info"

#if DESC("interface")
struct pake_server *build_pake_server(const struct hc_pin *pin, uint32_t key_length, const struct hc_auth_id *client,
    const struct hc_auth_id *server)
{
    struct pake_server *pake_server = (struct pake_server *)MALLOC(sizeof(struct pake_server));
    if (pake_server == NULL) {
        LOGE("Build pake server object failed");
        return NULL;
    }

    (void)memset_s(pake_server, sizeof(*pake_server), 0, sizeof(*pake_server));
    const struct server_virtual_func_group funcs = { parse_start_request_data, build_start_response_data,
                                                     parse_end_request_data, build_end_response_data };
    init_server(&pake_server->server_info, &funcs);
    pake_server->pin = *pin;
    pake_server->key_length = key_length;
    pake_server->self_id = *server;
    pake_server->peer_id = *client;
    pake_server->prime_type = NUM_LEN_384;

    LOGI("Build pake server object %u success", pake_server_sn(pake_server));

    return pake_server;
}

void destroy_pake_server(struct pake_server *pake_server)
{
    if (pake_server == NULL) {
        return;
    }

    LOGI("Destroy pake server object %u success", pake_server_sn(pake_server));
    FREE(pake_server);
}

int32_t send_pake_start_response(struct pake_server *pake_server, struct message *receive, struct message *send)
{
    check_ptr_return_val(pake_server, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    DBG_OUT("Receive pake start request message object %u success", pake_server_sn(pake_server));
    struct pake_start_request_data *receive_data = receive->payload;
    struct pake_start_response_data *send_data =
        (struct pake_start_response_data *)MALLOC(sizeof(struct pake_start_response_data));

    if (send_data == NULL) {
        LOGE("Malloc struct pake_start_response_data failed");
        send->msg_code = INFORM_MESSAGE;
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(send_data, sizeof(*send_data), 0, sizeof(*send_data));
    int32_t ret = send_start_response(pake_server, receive_data, send_data);
    if (ret != HC_OK) {
        LOGE("Object %u called send_start_response failed, error code is %d", pake_server_sn(pake_server), ret);
        FREE(send_data);
        send_data = NULL;
        send->msg_code = INFORM_MESSAGE;
    } else {
        LOGI("Object %u called send_start_response success", pake_server_sn(pake_server));
        send->msg_code = PAKE_RESPONSE;
        send->payload = send_data;
    }
    return ret;
}

int32_t send_pake_end_response(struct pake_server *pake_server, struct message *receive, struct message *send)
{
    check_ptr_return_val(pake_server, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    DBG_OUT("Receive pake end request message object %u success", pake_server_sn(pake_server));
    struct pake_end_request_data *receive_data = receive->payload;
    struct pake_end_response_data *send_data =
        (struct pake_end_response_data *)MALLOC(sizeof(struct pake_end_response_data));

    if (send_data == NULL) {
        LOGE("Malloc struct pake_end_response_data failed");
        send->msg_code = INFORM_MESSAGE;
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(send_data, sizeof(*send_data), 0, sizeof(*send_data));
    int32_t ret = send_end_response(pake_server, receive_data, send_data);
    if (ret != HC_OK) {
        LOGE("Object %u called send_end_response failed, error code is %d", pake_server_sn(pake_server), ret);
        FREE(send_data);
        send_data = NULL;
        send->msg_code = INFORM_MESSAGE;
    } else {
        LOGI("Object %u called send_end_response success", pake_server_sn(pake_server));
        send->msg_code = PAKE_SERVER_CONFIRM_RESPONSE;
        send->payload = send_data;
    }
    return ret;
}
#endif /* DESC */

#if DESC("virtual") /* called by base class */
static int32_t parse_start_request_data(void *handle, void *receive_data)
{
    struct pake_server *pake_server = handle;
    struct pake_start_request_data *data = receive_data;

    DBG_OUT("Object %u begin parse PAKE start request data", pake_server_sn(pake_server));
    if (!is_peer_support_current_version(&data->peer_version, &data->peer_support_version)) {
        LOGE("Object %u peer is not support current version", pake_server_sn(pake_server));
        return HC_VERSION_UNSUPPORT;
    }
    if (data->epk_len == HC_BIG_PRIME_MAX_LEN_384) {
        pake_server->prime_type = NUM_LEN_384;
    } else if (data->epk_len == HC_BIG_PRIME_MAX_LEN_256) {
        pake_server->prime_type = NUM_LEN_256;
    } else {
        LOGE("Object %u peer is not support big number len %d", pake_server_sn(pake_server), data->epk_len);
        return HC_LARGE_PRIME_NUMBER_LEN_UNSUPPORT;
    }
    return HC_OK;
}

static int32_t generate_pake_params(struct pake_server *pake_server, struct epk *self_epk);
static int32_t build_start_response_data(void *handle, void *send_data)
{
    struct pake_server *pake_server = handle;
    struct pake_start_response_data *data = send_data;

    DBG_OUT("Object %u begin build PAKE start response data", pake_server_sn(pake_server));
    struct epk self_epk = { 0, {0} };

    if (generate_pake_params(pake_server, &self_epk) != HC_OK) {
        LOGE("Object %u internal calculation error", pake_server_sn(pake_server));
        return HC_INTERNAL_ERROR;
    }
    data->salt = pake_server->salt;
    data->challenge = pake_server->self_challenge;
    data->epk = self_epk;
    data->self_version = get_current_version();
    data->self_support_version = get_current_version();
    return HC_OK;
}

static void generate_output_key(struct pake_server *pake_server);
static int32_t generate_session_key(struct pake_server *pake_server, struct epk *peer_epk);
static bool verify_proof_is_ok(struct pake_server *pake_server, struct hmac *kcf_data);
static int32_t parse_end_request_data(void *handle, void *receive_data)
{
    struct pake_server *pake_server = handle;
    struct pake_end_request_data *data = receive_data;

    DBG_OUT("Object %u begin parse PAKE end request data", pake_server_sn(pake_server));
    pake_server->peer_challenge = data->challenge;
    int32_t ret = generate_session_key(pake_server, &data->epk);
    if (ret != HC_OK) {
        LOGE("Object %u generate session key failed", pake_server_sn(pake_server));
        return ret;
    }

    if (verify_proof_is_ok(pake_server, &data->kcf_data) != true) {
        LOGE("Object %u verify proof failed", pake_server_sn(pake_server));
        return HC_VERIFY_PROOF_FAILED;
    }

    generate_output_key(pake_server);
    return HC_OK;
}

static struct hmac generate_proof(struct pake_server *pake_server);
static int32_t build_end_response_data(void *handle, void *send_data)
{
    struct pake_server *pake_server = handle;
    struct pake_end_response_data *data = send_data;

    DBG_OUT("Object %u begin build PAKE end response data", pake_server_sn(pake_server));
    data->kcf_data = generate_proof(pake_server);
    if (data->kcf_data.length == 0) {
        LOGE("Object %u generate proof failed", pake_server_sn(pake_server));
        return HC_GENERATE_PROOF_FAILED;
    }
    return HC_OK;
}
#endif /* DESC */

static struct challenge get_challenge(void);
static struct hc_salt get_salt(void);
static int32_t generate_pake_params(struct pake_server *pake_server, struct epk *self_epk)
{
    if (pake_server->server_info.protocol_base_info.state == PROTOCOL_INIT) {
        pake_server->salt = get_salt();
        pake_server->self_challenge = get_challenge();
    }
    uint32_t esk_len = (pake_server->prime_type == NUM_LEN_384) ? PAKE_ESK_LENGTH : PAKE_ESK_SHORT_LENGTH;
    uint32_t prime_len = (pake_server->prime_type == NUM_LEN_384) ?
        HC_BIG_PRIME_MAX_LEN_384 : HC_BIG_PRIME_MAX_LEN_256;
    if (pake_server->server_info.protocol_base_info.state == PROTOCOL_INIT) {
        struct random_value rand = generate_random(esk_len);
        if (rand.length == 0) {
            LOGE("Generate random value failed");
            return HC_GEN_RANDOM_FAILED;
        }
        pake_server->self_esk = *(struct esk *)&rand;
    }

    struct hkdf secret = { 0, {0} };
    int32_t ret = compute_hkdf((struct var_buffer *)&pake_server->pin, &pake_server->salt, HICHAIN_SPEKE_BASE_INFO,
                               HC_HKDF_SECRET_LEN, (struct var_buffer *)&secret);
    if (ret != HC_OK) {
        LOGE("Object %u generate hkdf failed, error code is %d", pake_server_sn(pake_server), ret);
        return ret;
    }
    struct exponent exp = {.length = 1};

    exp.exp[0] = 2; /* square */
    struct epk base = { 0, {0} };

    ret = cal_bignum_exp((struct var_buffer *)&secret, (struct var_buffer *)&exp,
        prime_len, (struct big_num *)&base);
    if (ret != HC_OK) {
        return HC_CAL_BIGNUM_EXP_FAILED;
    }
    ret = cal_bignum_exp((struct var_buffer *)&base, (struct var_buffer *)&pake_server->self_esk,
        prime_len, (struct big_num *)self_epk);
    if (ret != HC_OK) {
        return HC_CAL_BIGNUM_EXP_FAILED;
    }
    return HC_OK;
}

static struct challenge get_challenge(void)
{
    struct challenge challenge = { 0, {0} };
    struct random_value rand = generate_random(CHALLENGE_BUFF_LENGTH);
    if (rand.length == CHALLENGE_BUFF_LENGTH) {
        DBG_OUT("Generate challenge success");
        challenge.length = rand.length;
        (void)memcpy_s(challenge.challenge, sizeof(challenge.challenge), rand.random_value, CHALLENGE_BUFF_LENGTH);
    } else {
        LOGE("Generate challenge failed");
    }
    return challenge;
}

static struct hc_salt get_salt(void)
{
    struct hc_salt salt = { 0, {0} };
    struct random_value rand = generate_random(HC_SALT_BUFF_LEN);
    if (rand.length == HC_SALT_BUFF_LEN) {
        DBG_OUT("Generate salt success");
        salt.length = rand.length;
        (void)memcpy_s(salt.salt, sizeof(salt.salt), rand.random_value, HC_SALT_BUFF_LEN);
    } else {
        LOGE("Generate salt failed");
    }
    return salt;
}

static bool verify_proof_is_ok(struct pake_server *pake_server, struct hmac *kcf_data)
{
    struct uint8_buff challenge = {.size = CHALLENGE_BUFF_LENGTH + CHALLENGE_BUFF_LENGTH};
    challenge.val = (uint8_t *)MALLOC(challenge.size);
    if (challenge.val == NULL) {
        LOGE("Object %u MALLOC verify proof buffer failed", pake_server_sn(pake_server));
        return false;
    }

    (void)memcpy_s(challenge.val, challenge.size, pake_server->peer_challenge.challenge, CHALLENGE_BUFF_LENGTH);
    challenge.length = CHALLENGE_BUFF_LENGTH;
    (void)memcpy_s(challenge.val + challenge.length, challenge.size - challenge.length,
                   pake_server->self_challenge.challenge, CHALLENGE_BUFF_LENGTH);
    challenge.length += CHALLENGE_BUFF_LENGTH;
    struct hmac verify_proof = { 0, {0} };
    int32_t ret = compute_hmac((struct var_buffer *)&pake_server->hmac_key, &challenge, &verify_proof);
    FREE(challenge.val);
    challenge.val = NULL;
    if (ret != HC_OK) {
        LOGE("Object %u verify proof hmac failed, error code is %d", pake_server_sn(pake_server), ret);
        return false;
    }

    ret = memcmp(&verify_proof, kcf_data, sizeof(verify_proof));
    LOGI("Object %u verify proof hmac result is %d", pake_server_sn(pake_server), ret);

    return (ret == 0);
}

static struct hmac generate_proof(struct pake_server *pake_server)
{
    struct hmac proof = { 0, {0} };
    struct uint8_buff challenge = {
        .val = NULL,
        .length = 0,
        .size = CHALLENGE_BUFF_LENGTH + CHALLENGE_BUFF_LENGTH
    };

    challenge.val = (uint8_t *)MALLOC(challenge.size);
    if (challenge.val == NULL) {
        LOGE("Object %u MALLOC generate proof buffer failed", pake_server_sn(pake_server));
        return proof;
    }

    (void)memcpy_s(challenge.val, challenge.size, pake_server->self_challenge.challenge, CHALLENGE_BUFF_LENGTH);
    challenge.length = CHALLENGE_BUFF_LENGTH;
    (void)memcpy_s(challenge.val + challenge.length, challenge.size - challenge.length,
                   pake_server->peer_challenge.challenge, CHALLENGE_BUFF_LENGTH);
    challenge.length += CHALLENGE_BUFF_LENGTH;

    int32_t ret = compute_hmac((struct var_buffer *)&pake_server->hmac_key, &challenge, &proof);
    FREE(challenge.val);
    challenge.val = NULL;
    if (ret != HC_OK) {
        LOGE("Object %u generate proof hmac failed, error code is %d", pake_server_sn(pake_server), ret);
        proof.length = 0;
    }
    DBG_OUT("Object %u generate proof success", pake_server_sn(pake_server));
    return proof;
}

static int32_t generate_session_key(struct pake_server *pake_server, struct epk *peer_epk)
{
    struct pake_shared_secret shared_secret = { 0, {0} };
    uint32_t prime_len = (pake_server->prime_type == NUM_LEN_384) ?
        HC_BIG_PRIME_MAX_LEN_384 : HC_BIG_PRIME_MAX_LEN_256;
    int32_t ret = cal_bignum_exp((struct var_buffer *)peer_epk, (struct var_buffer *)&pake_server->self_esk,
        prime_len, (struct big_num *)&shared_secret);
    if (ret != HC_OK) {
        LOGE("Object %u generate shared secret failed, error code is %d", pake_server_sn(pake_server), ret);
        goto error;
    }

    struct hkdf hkdf = { 0, {0} };
    ret = compute_hkdf((struct var_buffer *)&shared_secret, &pake_server->salt,
        HICHAIN_SPEKE_SESSIONKEY_INFO, HC_HKDF_SECRET_LEN, (struct var_buffer *)&hkdf);
    if (ret != HC_OK) {
        LOGE("Object %u generate hkdf failed, error code is %d", pake_server_sn(pake_server), ret);
        goto error;
    }

    (void)memcpy_s(pake_server->session_key.key, sizeof(pake_server->session_key.key),
                   hkdf.hkdf, PAKE_SESSION_KEY_LENGTH);
    (void)memcpy_s(pake_server->hmac_key.key, sizeof(pake_server->hmac_key.key),
                   hkdf.hkdf + PAKE_SESSION_KEY_LENGTH, PAKE_HMAC_KEY_LENGTH);
    pake_server->session_key.length = PAKE_SESSION_KEY_LENGTH;
    pake_server->hmac_key.length = PAKE_HMAC_KEY_LENGTH;
    return HC_OK;

error:
    pake_server->session_key.length = 0;
    pake_server->hmac_key.length = 0;
    return HC_GENERATE_SESSION_KEY_FAILED;
}

static void generate_output_key(struct pake_server *pake_server)
{
    DBG_OUT("pake server generate output key");
    int32_t ret = compute_hkdf((struct var_buffer *)&pake_server->session_key, &pake_server->salt,
                               HICHAIN_RETURN_KEY, pake_server->key_length,
                               (struct var_buffer *)&pake_server->service_key);
    if (ret != HC_OK) {
        LOGE("Object %u generate output key failed, error code is %d", pake_server_sn(pake_server), ret);
    }
}

#else /* _CUT_XXX_ */

#include "stdlib_south.h"

struct pake_server *build_pake_server(const struct hc_pin *pin, uint32_t key_length, const struct hc_auth_id *client,
    const struct hc_auth_id *server)
{
    LOGE("Donot support pake protocol");
    (void)pin;
    (void)key_length;
    (void)client;
    (void)server;
    return (struct pake_server *)MALLOC(sizeof(struct pake_server));
}

void destroy_pake_server(struct pake_server *pake_server)
{
    LOGE("Donot support pake protocol");
    FREE(pake_server);
}

#endif /* _CUT_XXX_ */
