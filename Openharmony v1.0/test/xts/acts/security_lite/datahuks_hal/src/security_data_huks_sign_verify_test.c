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
#include "security_data_huks.h"
#include "hctest.h"
#include "hks_client.h"
#include "hks_types.h"
#include <securec.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is security
 * @param        : module name is securityData
 * @param        : test suit name is SecurityDataHuksSignVerifyTestSuite
 */
LITE_TEST_SUIT(security, securityData, SecurityDataHuksSignVerifyTestSuite);

/* *
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL SecurityDataHuksSignVerifyTestSuiteSetUp(void)
{
    int32_t status;
    status = hks_init();
    if (status != 0) {
        status = hks_refresh_key_info();
    }
    TEST_ASSERT_EQUAL_INT(0, status);
    return TRUE;
}

/* *
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL SecurityDataHuksSignVerifyTestSuiteTearDown(void)
{
    printf("-++++++++++++++++++++++++++++++++++++++++++++-\n");
    return TRUE;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Sign key
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++++++0200-0340

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0200, LEVEL2)
{
    int32_t statusAsymmetricSign;
    int32_t statusAsymmetricVerify;
    unsigned char testFileName[] = "keyalias1";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32];
    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    struct hks_blob src;
    src.data = (uint8_t *)"123456";
    src.size = NUM6;
    int32_t status = hks_hash(alg, &src, &hash);    
    TEST_ASSERT_EQUAL_INT(0, status);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    (void)TestSecShuksGenerateKeyNormal();
    struct hks_blob signature = { 0 };
    HksStBlobInit1(&signature, 1, NUM64, 0);
    statusAsymmetricSign = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(0, statusAsymmetricSign);

    statusAsymmetricVerify = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(0, statusAsymmetricVerify);

    HksBlobDestroyT1(&signature);
    (void)TestSecShuksDeleteKeyNormal();
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0210, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob *keyAlias = NULL; //  = NULL

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);


    status = hks_asymmetric_sign(keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0220, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = NULL; // = NULL
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0230, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = 0; // = 0
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0240, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = NUM65; // > 64
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0250, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = 0; // != HKS_BLOB_TYPE_ALIAS

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0260, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param *keyParam = NULL; // = NULL

    status = hks_asymmetric_sign(&keyAlias, keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0270, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = 0; // = 0
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);


    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0280, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = 0; // != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0290, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t sig[NUM64];

    struct hks_blob *hash = NULL; //  = NULL

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0300, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = NULL; // = NULL
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0310, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = 0; // = 0

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0320, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob *signature = NULL; // = NULL

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);


    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, signature);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0330, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = NULL; // = NULL
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM138, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0900
 * @tc.name      : Asymmetric Sign
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricSign0340, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[] = "test_ed25519_6";
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = NUM63; // < 64

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM138, status);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Sign key
// end+++++++++++++++++++++++++++++++++++++++++++++++++++++++++0200-0340

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Verify key
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++++0350-0510

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0350, LEVEL2)
{
    int32_t statusAsymmetricSign;
    int32_t statusAsymmetricVerify;

    unsigned char testFileName[] = "keyalias1";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32];
    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    struct hks_blob src;
    src.data = (uint8_t *)"123456";
    src.size = NUM6;
    int32_t status = hks_hash(alg, &src, &hash);    
    TEST_ASSERT_EQUAL_INT(0, status);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    struct hks_key_param keyParam2 = { 0 };
    keyParam2.key_type = HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519;
    keyParam2.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam2.key_mode = HKS_ALG_GCM;
    keyParam2.key_len = NUM32;
    keyParam2.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam2.key_auth_id.data = (uint8_t *)testFileName;
    keyParam2.key_auth_id.size = sizeof(testFileName);

    (void)TestSecShuksGenerateKeyNormal();
    struct hks_blob pubKey = { 0 };
    HksStBlobInit1(&pubKey, 1, NUM32, HKS_BLOB_TYPE_KEY);

    (void)TestSecShuksExportPublicNormal(&keyAlias, &pubKey);
    struct hks_blob signature = { 0 };
    HksStBlobInit1(&signature, 1, NUM64, 0);
    statusAsymmetricSign = hks_asymmetric_sign(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(0, statusAsymmetricSign);

    statusAsymmetricVerify = hks_asymmetric_verify(&pubKey, &keyParam2, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(0, statusAsymmetricVerify);

    HksBlobDestroyT1(&signature);
    (void)TestSecShuksDeleteKeyNormal();
    HksBlobDestroyT1(&pubKey);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0360, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob *keyAlias = NULL; // = NULL

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0370, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = NULL; // = NULL
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0380, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = 0; // = 0
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0390, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = NUM65; // > 64
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0400, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = NULL; // = NULL
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_KEY;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1006, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0410, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = NUM25; // != 32
    keyAlias.type = HKS_BLOB_TYPE_KEY;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1006, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0420, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = 0; // = else

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1006, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0430, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param *keyParam = NULL; // = NULL

    status = hks_asymmetric_verify(&keyAlias, keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0440, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = 0; // = 0
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0450, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_KEY;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = 0;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM134, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0460, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t sig[NUM64];

    struct hks_blob *hash = NULL; // = NULL

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0470, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = NULL; // = NULL
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0480, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = 0; // =  0

    struct hks_blob signature;
    signature.data = sig;
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0490, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob *signature = NULL; // = NULL

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, signature);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0500, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = NULL; // = NULL
    signature.size = sizeof(sig);

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1000
 * @tc.name      : Asymmetric Verify
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksSignVerifyTestSuite, securityDataAsymmetricVerify0510, LEVEL2)
{
    int32_t status;
    unsigned char testFileName[NUM32];
    struct hks_blob keyAlias;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    uint8_t hash1[NUM32], sig[NUM64];

    struct hks_blob hash;
    hash.data = (uint8_t *)hash1;
    hash.size = sizeof(hash1);

    struct hks_blob signature;
    signature.data = sig;
    signature.size = NUM63; // < 64

    struct hks_key_param keyParam = { 0 };
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_usage = HKS_KEY_USAGE_SIGN | HKS_KEY_USAGE_VERIFY;
    keyParam.key_mode = HKS_ALG_GCM;
    keyParam.key_len = NUM32;
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_auth_id.data = (uint8_t *)testFileName;
    keyParam.key_auth_id.size = sizeof(testFileName);

    status = hks_asymmetric_verify(&keyAlias, &keyParam, &hash, &signature);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Verify key
// end+++++++++++++++++++++++++++++++++++++++++++++++++++++++0350-0510

RUN_TEST_SUITE(SecurityDataHuksSignVerifyTestSuite);
