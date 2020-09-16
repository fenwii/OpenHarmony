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

#include "pake_client.h"
#include "log.h"
#include "mem_stat.h"

#if !(defined(_CUT_PAKE_) || defined(_CUT_PAKE_CLIENT_))

#include <string.h>
#include <securec.h>
#include "huks_adapter.h"
#include "commonutil.h"

static int32_t build_start_request_data(void *handle, void *data);
static int32_t parse_start_response_data(void *handle, void *data);
static int32_t build_end_request_data(void *handle, void *data);
static int32_t parse_end_response_data(void *handle, void *data);

#define HICHAIN_SPEKE_BASE_INFO       "hichain_speke_base_info"
#define HICHAIN_RETURN_KEY            "hichain_return_key"
#define HICHAIN_SPEKE_SESSIONKEY_INFO "hichain_speke_sessionkey_info"

struct pake_client *build_pake_client(const struct session_identity *identity, const struct hc_pin *pin,
    uint32_t key_length, const struct hc_auth_id *client, const struct hc_auth_id *server)
{
    struct pake_client *pake_client = (struct pake_client *)MALLOC(sizeof(struct pake_client));
    if (pake_client == NULL) {
        LOGE("Build pake client object failed");
        return NULL;
    }

    (void)memset_s(pake_client, sizeof(*pake_client), 0, sizeof(*pake_client));
    struct client_virtual_func_group funcs = { build_start_request_data, parse_start_response_data,
                                               build_end_request_data, parse_end_response_data };

    init_client(&pake_client->client_info, &funcs);
    pake_client->pin = *pin;
    pake_client->key_length = key_length;
    pake_client->self_id = *client;
    pake_client->peer_id = *server;
    pake_client->identity = identity;
    pake_client->prime_type = NUM_LEN_384;
    LOGI("Build pake client object %u success", pake_client_sn(pake_client));

    return pake_client;
}

void destroy_pake_client(struct pake_client *pake_client)
{
    if (pake_client == NULL) {
        return;
    }

    LOGI("Destroy pake client object %u success", pake_client_sn(pake_client));
    FREE(pake_client);
}

int32_t send_pake_start_request(struct pake_client *pake_client, struct message *send)
{
    check_ptr_return_val(pake_client, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    struct pake_start_request_data *send_data =
        (struct pake_start_request_data *)MALLOC(sizeof(struct pake_start_request_data));
    if (send_data == NULL) {
        LOGE("Malloc struct PAKE_START_REQUEST_DATA failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(send_data, sizeof(*send_data), 0, sizeof(*send_data));

    int32_t ret = send_start_request(pake_client, send_data);
    if (ret != HC_OK) {
        LOGE("Called send_start_request failed, error code is %d", ret);
        FREE(send_data);
        send->msg_code = INFORM_MESSAGE;
    } else {
        DBG_OUT("Called send_start_request success");
        send->msg_code = PAKE_REQUEST;
        send->payload = send_data;
    }

    return ret;
}

int32_t send_pake_end_request(struct pake_client *pake_client, const struct message *receive, struct message *send)
{
    check_ptr_return_val(pake_client, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    check_ptr_return_val(send, HC_INPUT_ERROR);
    DBG_OUT("Receive pake start response message object %u success", pake_client_sn(pake_client));
    struct pake_start_response_data *receive_data = (struct pake_start_response_data *)receive->payload;

    struct pake_end_request_data *send_data =
        (struct pake_end_request_data *)MALLOC(sizeof(struct pake_end_request_data));
    if (send_data == NULL) {
        LOGE("Malloc struct pake_end_request_data failed");
        return HC_MALLOC_FAILED;
    }
    (void)memset_s(send_data, sizeof(*send_data), 0, sizeof(*send_data));

    int32_t ret = send_end_request(pake_client, receive_data, send_data);
    if (ret != HC_OK) {
        LOGE("Called send_end_request failed, error code is %d", ret);
        FREE(send_data);
        send->msg_code = INFORM_MESSAGE;
    } else {
        DBG_OUT("Called send_end_request success");
        send->msg_code = PAKE_CLIENT_CONFIRM;
        send->payload = send_data;
    }

    return ret;
}

int32_t receive_pake_end_response(struct pake_client *pake_client, struct message *receive)
{
    check_ptr_return_val(pake_client, HC_INPUT_ERROR);
    check_ptr_return_val(receive, HC_INPUT_ERROR);
    DBG_OUT("Receive pake end response message object %u success", pake_client_sn(pake_client));
    struct pake_end_response_data *receive_data = (struct pake_end_response_data *)receive->payload;
    int32_t ret = receive_end_response(pake_client, receive_data);
    if (ret != HC_OK) {
        LOGE("Called receive_end_response failed, error code is %d", ret);
        receive->msg_code = INFORM_MESSAGE;
    } else {
        DBG_OUT("Called receive_end_response success");
        receive->msg_code = PAKE_SERVER_CONFIRM_RESPONSE;
        receive->payload = receive_data;
    }

    return ret;
}

static int32_t build_start_request_data(void *handle, void *data)
{
    struct pake_client *pake_client = (struct pake_client *)handle;
    struct pake_start_request_data *send_data = (struct pake_start_request_data *)data;

    send_data->peer_version.first = 1;
    send_data->peer_version.second = 0;
    send_data->peer_version.third = 0;
    send_data->peer_support_version.first = 1;
    send_data->peer_support_version.second = 0;
    send_data->peer_support_version.third = 0;
    send_data->operation_code = pake_client->operation_code;
    send_data->epk_len = HC_BIG_PRIME_MAX_LEN;

    return HC_OK;
}

static int32_t gen_esk_prime_len(struct pake_client *pake_client, struct pake_start_response_data *receive,
    uint32_t *esk_len, uint32_t *prime_len)
{
    if (receive->epk.length == HC_BIG_PRIME_MAX_LEN_384) {
        pake_client->prime_type = NUM_LEN_384;
    } else if (receive->epk.length == HC_BIG_PRIME_MAX_LEN_256) {
        pake_client->prime_type = NUM_LEN_256;
    } else {
        LOGE("Object %u peer is not support big number len %u", pake_client_sn(pake_client), receive->epk.length);
        return HC_LARGE_PRIME_NUMBER_LEN_UNSUPPORT;
    }
    *esk_len = (pake_client->prime_type == NUM_LEN_384) ? PAKE_ESK_LENGTH : PAKE_ESK_SHORT_LENGTH;
    *prime_len = (pake_client->prime_type == NUM_LEN_384) ?
                         HC_BIG_PRIME_MAX_LEN_384 : HC_BIG_PRIME_MAX_LEN_256;
    return HC_OK;
}

static int32_t parse_start_response_data(void *handle, void *data)
{
    struct pake_client *pake_client = (struct pake_client *)handle;
    struct pake_start_response_data *receive = (struct pake_start_response_data *)data;

    if (!is_peer_support_current_version(&receive->self_version, &receive->self_support_version)) {
        LOGE("Unsupport version received");
        return HC_VERSION_UNSUPPORT;
    }

    pake_client->salt = receive->salt;
    pake_client->peer_epk = receive->epk;
    pake_client->peer_challenge = receive->challenge;

    struct hkdf secret = { 0, {0} };
    int32_t ret = compute_hkdf((struct var_buffer *)&pake_client->pin, &pake_client->salt,
                               HICHAIN_SPEKE_BASE_INFO, HC_HKDF_SECRET_LEN,
                               (struct var_buffer *)&secret);
    if (ret != HC_OK) {
        LOGE("Object %u generate hkdf failed, error code is %d", pake_client_sn(pake_client), ret);
        return ret;
    }

    uint32_t esk_len = 0;
    uint32_t prime_len = 0;
    ret = gen_esk_prime_len(pake_client, receive, &esk_len, &prime_len);
    if (ret != HC_OK) {
        return ret;
    }
    if (pake_client->client_info.protocol_base_info.state == START_REQUEST) {
        struct random_value rand = generate_random(esk_len);
        if (rand.length == 0) {
            LOGE("Generate random value failed");
            return HC_GEN_RANDOM_FAILED;
        }

        pake_client->self_esk = *(struct esk *)&rand;
    }
    struct exponent exp = {.length = 1};

    exp.exp[0] = 2; /* square */
    struct epk base = { 0, {0} };

    ret = cal_bignum_exp((struct var_buffer *)&secret, (struct var_buffer *)&exp,
                         prime_len, (struct big_num *)&base);
    if (ret != HC_OK) {
        return HC_CAL_BIGNUM_EXP_FAILED;
    }
    struct epk self_epk = { 0, {0} };

    ret = cal_bignum_exp((struct var_buffer *)&base, (struct var_buffer *)&pake_client->self_esk,
                         prime_len, (struct big_num *)&self_epk);
    if (ret != HC_OK) {
        return HC_CAL_BIGNUM_EXP_FAILED;
    }
    pake_client->self_epk = self_epk;

    return HC_OK;
}

static int32_t generate_session_key(struct pake_client *pake_client, struct epk *peer_epk);
static struct hmac generate_proof(struct pake_client *pake_client);
static int32_t build_end_request_data(void *handle, void *data)
{
    struct pake_client *pake_client = (struct pake_client *)handle;
    struct pake_end_request_data *send = (struct pake_end_request_data *)data;
    int32_t ret = generate_session_key(pake_client, &pake_client->peer_epk);
    if (ret != HC_OK) {
        LOGE("Object %u generate session key failed", pake_client_sn(pake_client));
        return ret;
    }
    struct challenge challenge = { 0, {0} };
    struct random_value rand = generate_random(CHALLENGE_BUFF_LENGTH);
    if (rand.length == CHALLENGE_BUFF_LENGTH) {
        DBG_OUT("Generate challenge success");
        challenge.length = rand.length;
        if (memcpy_s(challenge.challenge, sizeof(challenge.challenge), rand.random_value,
            CHALLENGE_BUFF_LENGTH) != EOK) {
            return memory_copy_error(__func__, __LINE__);
        }
    } else {
        LOGE("Generate challenge failed.");
    }
    pake_client->self_challenge = challenge;
    pake_client->kcf_data = generate_proof(pake_client);
    send->challenge = challenge;
    send->epk = pake_client->self_epk;
    send->kcf_data = pake_client->kcf_data;

    return HC_OK;
}

static bool verify_proof_is_ok(struct pake_client *pake_client, struct hmac *kcf_data);
static void generate_output_key(struct pake_client *pake_client);
static int32_t parse_end_response_data(void *handle, void *data)
{
    struct pake_client *pake_client = (struct pake_client *)handle;
    struct pake_end_response_data *receive = (struct pake_end_response_data *)data;

    if (verify_proof_is_ok(pake_client, &receive->kcf_data) != true) {
        LOGE("Object %u verify proof failed", pake_client_sn(pake_client));
        return HC_VERIFY_PROOF_FAILED;
    }

    generate_output_key(pake_client);

    return HC_OK;
}

static int32_t generate_session_key(struct pake_client *pake_client, struct epk *peer_epk)
{
    struct pake_shared_secret shared_secret = { 0, {0} };
    uint32_t prime_len = (pake_client->prime_type == NUM_LEN_384) ?
                         HC_BIG_PRIME_MAX_LEN_384 : HC_BIG_PRIME_MAX_LEN_256;
    int32_t ret = cal_bignum_exp((struct var_buffer *)peer_epk, (struct var_buffer *)&pake_client->self_esk,
                                 prime_len, (struct big_num *)&shared_secret);
    pake_client->shared_secret = shared_secret;
    if (ret != HC_OK) {
        LOGE("Object %u generate shared secret failed, error code is %d", pake_client_sn(pake_client), ret);
        goto error;
    }

    struct hkdf hkdf = { 0, {0} };
    ret = compute_hkdf((struct var_buffer *)&shared_secret, &pake_client->salt,
                       HICHAIN_SPEKE_SESSIONKEY_INFO, HC_HKDF_SECRET_LEN, (struct var_buffer *)&hkdf);
    if (ret != HC_OK) {
        LOGE("Object %u generate hkdf failed, error code is %d", pake_client_sn(pake_client), ret);
        goto error;
    }

    (void)memcpy_s(pake_client->session_key.key, sizeof(pake_client->session_key.key),
                   hkdf.hkdf, PAKE_SESSION_KEY_LENGTH);
    (void)memcpy_s(pake_client->hmac_key.key, sizeof(pake_client->hmac_key.key),
                   hkdf.hkdf + PAKE_SESSION_KEY_LENGTH, PAKE_HMAC_KEY_LENGTH);
    pake_client->session_key.length = PAKE_SESSION_KEY_LENGTH;
    pake_client->hmac_key.length = PAKE_HMAC_KEY_LENGTH;
    return HC_OK;

error:
    pake_client->session_key.length = 0;
    pake_client->hmac_key.length = 0;
    return HC_GENERATE_SESSION_KEY_FAILED;
}

static struct hmac generate_proof(struct pake_client *pake_client)
{
    struct hmac proof = { 0, {0} };
    struct uint8_buff challenge = {
        .val = NULL,
        .length = 0,
        .size = CHALLENGE_BUFF_LENGTH + CHALLENGE_BUFF_LENGTH
    };

    challenge.val = (uint8_t *)MALLOC(challenge.size);
    if (challenge.val == NULL) {
        LOGE("Object %u MALLOC generate proof buffer failed.", pake_client_sn(pake_client));
        return proof;
    }
    (void)memset_s(challenge.val, challenge.size, 0, challenge.size);
    (void)memcpy_s(challenge.val, challenge.size, pake_client->self_challenge.challenge, CHALLENGE_BUFF_LENGTH);
    challenge.length = CHALLENGE_BUFF_LENGTH;
    (void)memcpy_s(challenge.val + challenge.length, challenge.size - challenge.length,
                   pake_client->peer_challenge.challenge, CHALLENGE_BUFF_LENGTH);
    challenge.length += CHALLENGE_BUFF_LENGTH;

    int32_t ret = compute_hmac((struct var_buffer *)&pake_client->hmac_key, &challenge, &proof);
    FREE(challenge.val);
    if (ret != HC_OK) {
        LOGE("Object %u generate proof hmac failed, error code is %d.", pake_client_sn(pake_client), ret);
        proof.length = 0;
    }
    DBG_OUT("Object %u generate proof success", pake_client_sn(pake_client));
    return proof;
}

static bool verify_proof_is_ok(struct pake_client *pake_client, struct hmac *kcf_data)
{
    struct uint8_buff challenge = {.size = CHALLENGE_BUFF_LENGTH + CHALLENGE_BUFF_LENGTH};

    challenge.val = (uint8_t *)MALLOC(challenge.size);
    if (challenge.val == NULL) {
        LOGE("Object %u MALLOC verify proof buffer failed", pake_client_sn(pake_client));
        return false;
    }

    (void)memcpy_s(challenge.val, challenge.size, pake_client->peer_challenge.challenge, CHALLENGE_BUFF_LENGTH);
    challenge.length = CHALLENGE_BUFF_LENGTH;
    (void)memcpy_s(challenge.val + challenge.length, challenge.size - challenge.length,
                   pake_client->self_challenge.challenge, CHALLENGE_BUFF_LENGTH);
    challenge.length += CHALLENGE_BUFF_LENGTH;
    struct hmac verify_proof = { 0, {0} };
    int32_t ret = compute_hmac((struct var_buffer *)&pake_client->hmac_key, &challenge, &verify_proof);

    FREE(challenge.val);
    challenge.val = NULL;
    if (ret != HC_OK) {
        LOGE("Object %u verify proof hmac failed, error code is %d", pake_client_sn(pake_client), ret);
        return false;
    }

    ret = memcmp(&verify_proof, kcf_data, sizeof(verify_proof));
    LOGI("Object %u verify proof hmac result is %d", pake_client_sn(pake_client), ret);

    return (ret == 0);
}

static void generate_output_key(struct pake_client *pake_client)
{
    DBG_OUT("pake client generate output key");
    int32_t ret = compute_hkdf((struct var_buffer *)&pake_client->session_key, &pake_client->salt,
                               HICHAIN_RETURN_KEY, pake_client->key_length,
                               (struct var_buffer *)&pake_client->service_key);
    if (ret != HC_OK) {
        LOGE("Object %u generate output key failed, error code is %d", pake_client_sn(pake_client), ret);
        return;
    } else {
        DBG_OUT("Pake client generate output key success");
        return;
    }
}

#else /* _CUT_XXX */

struct pake_client *build_pake_client(const struct session_identity *identity, const struct hc_pin *pin,
    uint32_t key_length, const struct hc_auth_id *client, const struct hc_auth_id *server)
{
    LOGE("Donot support pake protocol");
    (void)identity;
    (void)pin;
    (void)key_length;
    (void)client;
    (void)server;
    return (struct pake_client *)MALLOC(sizeof(struct pake_client));
}

void destroy_pake_client(struct pake_client *pake_client)
{
    LOGE("Donot support pake protocol");
    FREE(pake_client);
}

#endif /* _CUT_XXX */

