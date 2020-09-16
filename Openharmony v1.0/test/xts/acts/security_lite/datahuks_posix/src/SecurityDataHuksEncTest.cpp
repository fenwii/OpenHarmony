/* Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include "SecurityDataHuks.h"
#include "hks_client.h"
#include "hks_types.h"
#include <securec.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtest/gtest.h"
using namespace std;
using namespace testing::ext;

class SecurityDataHuksEncTestSuite : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void) {}
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void) {}
    // Testcase setup
    virtual void SetUp()
    {
        int32_t status;
        struct hks_file_callbacks fileCallbacks;

        fileCallbacks.read = FileRead;
        fileCallbacks.write = FileWrite;
        fileCallbacks.file_size = FileSize;

        status = hks_register_file_callbacks(&fileCallbacks);
        EXPECT_EQ(0, status);

        struct hks_log_f_group logFunc;
        logFunc.log_info = Logi;
        logFunc.log_warn = Logw;
        logFunc.log_error = Loge;
        logFunc.log_debug = Logd;

        status = hks_register_log_interface(&logFunc);
        EXPECT_EQ(0, status);

        status = hks_register_get_hardware_udid_callback(HksTestGetHardwareUdid);

        EXPECT_EQ(0, status);

        status = hks_init();
        if (status != 0) {
            status = hks_refresh_key_info();
        }
        EXPECT_EQ(0, status);
    }
    // Testcase teardown
    virtual void TearDown() {}
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Encrypt key
// begin++++++++++++++++++++++++++++++++++++++++++++++++++++2100-4400

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2100, TestSize.Level1)
{
    char alias[] = "test_hks_aead_encrypt";
    int32_t s;
    int32_t statusEncrypt;
    int32_t statusDecrypt;

    struct hks_blob key;
    HksStBlobInit1(&key, 1, NUM16, HKS_BLOB_TYPE_KEY);
    s = hks_generate_random(&key);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;
    struct hks_blob nonce;
    HksStBlobInit1(&nonce, 1, NUM16, HKS_BLOB_TYPE_IV);
    s = hks_generate_random(&nonce);

    struct hks_blob aad;
    HksStBlobInit1(&aad, 1, NUM16, HKS_BLOB_TYPE_AAD);
    s = hks_generate_random(&aad);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    HksStBlobInit1(&plaintext, 1, NUM64, HKS_BLOB_TYPE_PLAIN_TEXT);
    s = hks_generate_random(&plaintext);

    struct hks_blob ciphertext;
    HksStBlobInit1(&ciphertext, 1, NUM64 + HKS_SALT_MAX_SIZE, HKS_BLOB_TYPE_CIPHER_TEXT);
    statusEncrypt = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(0, statusEncrypt);

    struct hks_blob decrypted;
    HksStBlobInit1(&decrypted, 1, NUM64, HKS_BLOB_TYPE_PLAIN_TEXT);
    statusDecrypt = hks_aead_decrypt(&key, &keyParam, &cryptParam, &decrypted, &ciphertext);
    EXPECT_EQ(0, statusDecrypt);

    size_t k;
    for (k = 0; k < decrypted.size; k++) {
        EXPECT_EQ(plaintext.data[k], decrypted.data[k]);
    }
    HksBlobDestroyT1(&key);
    HksBlobDestroyT1(&nonce);
    HksBlobDestroyT1(&aad);
    HksBlobDestroyT1(&plaintext);
    HksBlobDestroyT1(&ciphertext);
    HksBlobDestroyT1(&decrypted);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2200, TestSize.Level1)
{
    char alias[] = "test_hks_aead_encrypt";
    int32_t s;
    int32_t statusEncrypt;
    int32_t statusDecrypt;

    struct hks_blob key;
    HksStBlobInit1(&key, 1, NUM24, HKS_BLOB_TYPE_KEY);
    s = hks_generate_random(&key);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM192;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;
    struct hks_blob nonce;
    HksStBlobInit1(&nonce, 1, NUM16, HKS_BLOB_TYPE_IV);
    s = hks_generate_random(&nonce);

    struct hks_blob aad;
    HksStBlobInit1(&aad, 1, NUM16, HKS_BLOB_TYPE_AAD);
    s = hks_generate_random(&aad);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    HksStBlobInit1(&plaintext, 1, NUM64, HKS_BLOB_TYPE_PLAIN_TEXT);
    s = hks_generate_random(&plaintext);

    struct hks_blob ciphertext;
    HksStBlobInit1(&ciphertext, 1, NUM64 + HKS_SALT_MAX_SIZE, HKS_BLOB_TYPE_CIPHER_TEXT);
    statusEncrypt = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(0, statusEncrypt);

    struct hks_blob decrypted;
    HksStBlobInit1(&decrypted, 1, NUM64, HKS_BLOB_TYPE_PLAIN_TEXT);
    statusDecrypt = hks_aead_decrypt(&key, &keyParam, &cryptParam, &decrypted, &ciphertext);
    EXPECT_EQ(0, statusDecrypt);

    size_t k;
    for (k = 0; k < decrypted.size; k++) {
        EXPECT_EQ(plaintext.data[k], decrypted.data[k]);
    }
    HksBlobDestroyT1(&key);
    HksBlobDestroyT1(&nonce);
    HksBlobDestroyT1(&aad);
    HksBlobDestroyT1(&plaintext);
    HksBlobDestroyT1(&ciphertext);
    HksBlobDestroyT1(&decrypted);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2300, TestSize.Level1)
{
    char alias[] = "test_hks_aead_encrypt";
    int32_t s;
    int32_t statusEncrypt;
    int32_t statusDecrypt;

    struct hks_blob key;
    HksStBlobInit1(&key, 1, NUM32, HKS_BLOB_TYPE_KEY);
    s = hks_generate_random(&key);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM256;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;
    struct hks_blob nonce;
    HksStBlobInit1(&nonce, 1, NUM16, HKS_BLOB_TYPE_IV);
    s = hks_generate_random(&nonce);

    struct hks_blob aad;
    HksStBlobInit1(&aad, 1, NUM16, HKS_BLOB_TYPE_AAD);
    s = hks_generate_random(&aad);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    HksStBlobInit1(&plaintext, 1, NUM64, HKS_BLOB_TYPE_PLAIN_TEXT);
    s = hks_generate_random(&plaintext);

    struct hks_blob ciphertext;
    HksStBlobInit1(&ciphertext, 1, NUM64 + HKS_SALT_MAX_SIZE, HKS_BLOB_TYPE_CIPHER_TEXT);
    statusEncrypt = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(0, statusEncrypt);

    struct hks_blob decrypted;
    HksStBlobInit1(&decrypted, 1, NUM64, HKS_BLOB_TYPE_PLAIN_TEXT);
    statusDecrypt = hks_aead_decrypt(&key, &keyParam, &cryptParam, &decrypted, &ciphertext);
    EXPECT_EQ(0, statusDecrypt);

    size_t k;
    for (k = 0; k < decrypted.size; k++) {
        EXPECT_EQ(plaintext.data[k], decrypted.data[k]);
    }
    HksBlobDestroyT1(&key);
    HksBlobDestroyT1(&nonce);
    HksBlobDestroyT1(&aad);
    HksBlobDestroyT1(&plaintext);
    HksBlobDestroyT1(&ciphertext);
    HksBlobDestroyT1(&decrypted);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2400, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob *key = nullptr; // = NULL

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2500, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = NUM32; // != key_param.key_len / 8

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM1006, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2600, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = NULL; // = NULL
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM1006, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2700, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = 0; // != HKS_BLOB_TYPE_KEY
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM1006, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2800, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param *keyParam = nullptr; // = NULL

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt2900, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = 0; // != HKS_ALG_GCM
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3000, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM11; // != 128 192 256
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3100, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = 0; // != HKS_KEY_TYPE_AES
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3200, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;
    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = NUM88; // != HKS_PADDING_NONE
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3300, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = 0; // = 0
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3400, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param *cryptParam = nullptr; // = NULL


    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3500, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = NUM10; // < 12

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3600, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = NULL; // = NULL
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3700, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = 0; // = 0

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3800, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = NULL; // = NULL
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt3900, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob *plaintext = nullptr; // = NULL

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, plaintext, &ciphertext);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt4000, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = NULL; // = NULL
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt4100, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = 0; // = 0

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt4200, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob *ciphertext = nullptr; // = NULL
    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, ciphertext);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt4300, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;

    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = NULL; // = NULL
    ciphertext.size = sizeof(ciphertext1);

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1000
 * @tc.name      : Aead Encrypt
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksEncTestSuite, securityDataAeadEncrypt4400, TestSize.Level2)
{
    char alias[] = "test_hks_aead_encrypt";

    uint8_t key1[NUM16], nonce1[NUM16], aad1[NUM16], plaintext1[NUM64], ciphertext1[NUM100];

    int32_t status;
    struct hks_blob key;
    key.type = HKS_BLOB_TYPE_KEY;
    key.data = (uint8_t *)key1;
    key.size = sizeof(key1);

    struct hks_key_param keyParam;
    keyParam.key_type = HKS_KEY_TYPE_AES;
    keyParam.key_len = NUM128;
    keyParam.key_usage = HKS_KEY_USAGE_ENCRYPT | HKS_KEY_USAGE_DECRYPT;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_pad = HKS_PADDING_NONE;
    keyParam.key_auth_id.data = (uint8_t *)alias;
    keyParam.key_auth_id.size = sizeof(alias);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;

    struct hks_crypt_param cryptParam;

    struct hks_blob nonce;
    nonce.data = (uint8_t *)nonce1;
    nonce.size = sizeof(nonce1);

    struct hks_blob aad;
    aad.data = (uint8_t *)aad1;
    aad.size = sizeof(aad1);

    cryptParam.nonce = nonce;
    cryptParam.aad = aad;

    struct hks_blob plaintext;
    plaintext.data = (uint8_t *)plaintext1;
    plaintext.size = sizeof(plaintext1);

    struct hks_blob ciphertext;
    ciphertext.data = (uint8_t *)ciphertext1;
    ciphertext.size = NUM10; // < +16

    status = hks_aead_encrypt(&key, &keyParam, &cryptParam, &plaintext, &ciphertext);
    EXPECT_EQ(NUM135, status);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Encrypt key
// end==++++++++++++++++++++++++++++++++++++++++++++++++++++2100-4400

