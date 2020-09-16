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

#ifndef __BASE_H__
#define __BASE_H__

#define _HC_DEBUF_ 1

#include <stdint.h>

#ifdef _HC_DEBUG_
#include <assert.h>

/* for memory leak check, only used for input params checking */
#define check_ptr_return_val(d_ptr, d_val) \
    do { \
        assert((d_ptr) != NULL); \
        (void)(d_val); \
    } while (0)

#define check_ptr_return(d_ptr)  assert((d_ptr) != NULL)

#define check_num_return_val(d_num, d_val) \
    do { \
        assert((d_num) != 0); \
        (void)(d_val); \
    } while (0)

#else /* _HC_DEBUG_ */
/* only used for input params checking */
#define check_ptr_return_val(d_ptr, d_val) \
    do { \
        if ((d_ptr) == NULL) { \
            return (d_val); \
        } \
    } while (0)

#define check_ptr_return(d_ptr) \
    do { \
        if ((d_ptr) == NULL) { \
            return; \
        } \
    } while (0)

#define check_num_return_val(d_num, d_val) \
    do { \
        if ((d_num) == 0) { \
            return (d_val); \
        } \
    } while (0)

#endif /* _HC_DEBUG_ */

#define HC_RAMDOM_MAX_LEN           32
#define HC_BASE_LEN                 32
#define HC_EXPONENT_LEN             32
#define HC_RAMDOM_VALUE_MAX_LEN     1024
#define HC_HMAC_LEN                 32
#define HC_HKDF_LEN                 512
#define HC_HKDF_SECRET_LEN          32

#define HC_STS_SHARED_SECRET_LENGTH 32
#define HC_SERVICE_ID_BUFF_LEN      64

#if !defined(_SCANTY_MEMORY_)
#define HC_BIG_PRIME_MAX_LEN        384
#else /* _SCANTY_MEMORY_ */
#define HC_BIG_PRIME_MAX_LEN        256
#endif /* _SCANTY_MEMORY_ */

#define HC_BIG_PRIME_MAX_LEN_384    384
#define HC_BIG_PRIME_MAX_LEN_256    256

/* SHA256 */
#define HC_SHA256_LEN               32
#define HC_SHA512_LEN               64

/* KEY */
#define HC_LT_PUBLIC_KEY_LEN        32
#define HC_LT_PRIVATE_KEY_LEN       64
#define HC_ST_PUBLIC_KEY_LEN        32
#define HC_ST_PRIVATE_KEY_LEN       32

#define HC_SIGNATURE_LEN            64
#define HC_KEY_ALIAS_MAX_LEN        64

/* AES */
#define HC_AES_ADD_LEN              64

/* IV */
#define HC_IV_MAX_LEN               12

#define BYTE_TO_HEX_OPER_LENGTH     2
#define VERSION_LENGTH              30

#define HC_MAX_KEY_TYPE_NUM         6
#define HC_MAX_PAIR_TYPE_NUM        2
#define HC_KEY_TYPE_PAIR_LEN        2

#define AUTH_FORM                   0

struct var_buffer {
    uint32_t length;
    uint8_t data[0];
};

struct big_num {
    uint32_t length;
    uint8_t big_num[HC_BIG_PRIME_MAX_LEN];
};

struct ltsk {
    uint32_t length;
    uint8_t ltsk[HC_LT_PRIVATE_KEY_LEN];
};

struct ltpk {
    uint32_t length;
    uint8_t ltpk[HC_LT_PUBLIC_KEY_LEN];
};

/* temp public key */
struct stpk {
    uint32_t length;
    uint8_t stpk[HC_ST_PUBLIC_KEY_LEN];
};

/* temp private key */
struct stsk {
    uint32_t length;
    uint8_t stsk[HC_ST_PRIVATE_KEY_LEN];
};

/* long store key pair */
struct lt_key_pair {
    struct ltpk lt_public_key;
    struct ltsk lt_private_key;
};

/* temp key pair */
struct st_key_pair {
    struct stpk st_public_key;
    struct stsk st_private_key;
};

struct signature {
    uint32_t length;
    uint8_t signature[HC_SIGNATURE_LEN];
};

struct sts_shared_secret {
    uint32_t length;
    uint8_t sts_shared_secret[HC_STS_SHARED_SECRET_LENGTH];
};

struct service_id {
    uint32_t length;
    uint8_t service_id[HC_SERVICE_ID_BUFF_LEN];
};

struct sha256_value {
    uint32_t length;
    uint8_t sha256_value[HC_SHA256_LEN];
};

struct sha512_value {
    uint32_t length;
    uint8_t sha512_value[HC_SHA512_LEN];
};

struct aes_aad {
    uint32_t length;
    uint8_t aad[HC_AES_ADD_LEN];
};

struct random_value {
    uint32_t length;
    uint8_t random_value[HC_RAMDOM_MAX_LEN];
};

struct base {
    uint32_t length;
    uint8_t base[HC_BASE_LEN];
};

struct exponent {
    uint32_t length;
    uint8_t exp[HC_EXPONENT_LEN];
};

struct rand_value {
    uint32_t length;
    uint8_t ramdom_value[HC_RAMDOM_VALUE_MAX_LEN];
};

struct hmac {
    uint32_t length;
    uint8_t hmac[HC_HMAC_LEN];
};

struct hkdf {
    uint32_t length;
    uint8_t hkdf[HC_HKDF_LEN];
};

struct message {
    uint16_t msg_code;
    uint16_t rsv;
    void *payload;
};

struct inform_message_data {
    uint16_t error_code;
};

enum message_code {
    INVALID_MESSAGE = 0,

    PAKE_REQUEST = 0x0001,
    PAKE_CLIENT_CONFIRM = 0x0002,
    EXCHANGE_REQUEST = 0x0003,
    AUTH_START_REQUEST = 0x0011,
    AUTH_ACK_REQUEST = 0x0012,
    ADD_AUTHINFO_REQUEST = 0x0023,
    REMOVE_AUTHINFO_REQUEST = 0x0033,
    SEC_CLONE_START_REQUEST = 0x0041,
    SEC_CLONE_ACK_REQUEST = 0x0042,

    PAKE_RESPONSE = 0x8001,
    PAKE_SERVER_CONFIRM_RESPONSE = 0x8002,
    EXCHANGE_RESPONSE = 0x8003,
    AUTH_START_RESPONSE = 0x8011,
    AUTH_ACK_RESPONSE = 0x8012,
    ADD_AUTHINFO_RESPONSE = 0x8023,
    REMOVE_AUTHINFO_RESPONSE = 0x8033,
    SEC_CLONE_START_RESPONSE = 0x8041,
    SEC_CLONE_ACK_RESPONSE = 0x8042,

    INFORM_MESSAGE = 0x8080,
};

enum json_object_data_type {
    JSON_STRING_DATA = 0,
    JSON_OBJECT_DATA = 1
};

enum large_prime_number_type {
    NUM_LEN_384 = 0, /* big prime number type is 384 length */
    NUM_LEN_256 /* big prime number type is 256 length */
};

#endif /* __BASE_H__ */
