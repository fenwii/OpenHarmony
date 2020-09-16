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
 * @param        : test suit name is SecurityDataHuksExportHashRandomHmacTestSuite
 */
LITE_TEST_SUIT(security, securityData, SecurityDataHuksExportHashRandomHmacTestSuite);

/* *
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL SecurityDataHuksExportHashRandomHmacTestSuiteSetUp(void)
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
static BOOL SecurityDataHuksExportHashRandomHmacTestSuiteTearDown(void)
{
    printf("-++++++++++++++++++++++++++++++++++++++++++++-\n");
    return TRUE;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Export Public key
// begin++++++++++++++++++++++++++++++++++++++++++++++1000-1090

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1000, LEVEL1)
{
    int32_t status;
    char testFileName[] = "keyalias1";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    (void)TestSecShuksGenerateKeyNormal();

    struct hks_blob publicKey1 = { 0 };
    HksStBlobInit1(&publicKey1, 1, NUM32, HKS_BLOB_TYPE_KEY);
    status = hks_export_public_key(&keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(0, status);
    HksBlobDestroyT1(&publicKey1);
    (void)TestSecShuksDeleteKeyNormal();
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1010, LEVEL2)
{
    int32_t status;
    struct hks_blob *keyAlias = NULL; // = NULL
    struct hks_blob publicKey1 = { 0 };

    publicKey1.data = (uint8_t *)malloc(NUM32);
    if (publicKey1.data == NULL) {
        return;
    }
    publicKey1.size = NUM32;
    publicKey1.type = HKS_BLOB_TYPE_KEY;

    status = hks_export_public_key(keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
    HksBlobDestroyT1(&publicKey1);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1020, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };
    struct hks_blob publicKey1 = { 0 };
    keyAlias.data = NULL; // = NULL
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    publicKey1.data = (uint8_t *)malloc(NUM32);
    if (publicKey1.data == NULL) {
        return;
    }
    publicKey1.size = NUM32;
    publicKey1.type = HKS_BLOB_TYPE_KEY;

    status = hks_export_public_key(&keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
    HksBlobDestroyT1(&publicKey1);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1030, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };
    struct hks_blob publicKey1 = { 0 };
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = 0; // != HKS_BLOB_TYPE_ALIAS

    publicKey1.data = (uint8_t *)malloc(NUM32);
    if (publicKey1.data == NULL) {
        return;
    }
    publicKey1.size = NUM32;
    publicKey1.type = HKS_BLOB_TYPE_KEY;

    status = hks_export_public_key(&keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
    HksBlobDestroyT1(&publicKey1);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1040, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };
    struct hks_blob publicKey1 = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = 0; // = 0
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    publicKey1.data = (uint8_t *)malloc(NUM32);
    if (publicKey1.data == NULL) {
        return;
    }
    publicKey1.size = NUM32;
    publicKey1.type = HKS_BLOB_TYPE_KEY;

    status = hks_export_public_key(&keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
    HksBlobDestroyT1(&publicKey1);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1050, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };
    struct hks_blob publicKey1 = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = NUM65; // > 64
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    publicKey1.data = (uint8_t *)malloc(NUM32);
    if (publicKey1.data == NULL) {
        return;
    }
    publicKey1.size = NUM32;
    publicKey1.type = HKS_BLOB_TYPE_KEY;

    status = hks_export_public_key(&keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
    HksBlobDestroyT1(&publicKey1);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1060, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };
    struct hks_blob *publicKey1 = NULL; // = NULL

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_export_public_key(&keyAlias, publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
    HksBlobDestroyT1(&keyAlias);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1070, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };
    struct hks_blob publicKey1 = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    publicKey1.data = (uint8_t *)malloc(NUM31);
    if (publicKey1.data == NULL) {
        return;
    }
    publicKey1.size = NUM31; // < 32
    publicKey1.type = HKS_BLOB_TYPE_KEY;

    status = hks_export_public_key(&keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM1007, status);
    HksBlobDestroyT1(&publicKey1);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1080, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };
    struct hks_blob publicKey1 = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    publicKey1.data = NULL; // = NULL
    publicKey1.size = NUM32;
    publicKey1.type = HKS_BLOB_TYPE_KEY;

    status = hks_export_public_key(&keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM1007, status);
    HksBlobDestroyT1(&publicKey1);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0700
 * @tc.name      : Export Public Key
 * @tc.desc      : [C- SECURITY -1800]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataExportPublicKey1090, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };
    struct hks_blob publicKey1 = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    publicKey1.data = (uint8_t *)malloc(NUM32);
    if (publicKey1.data == NULL) {
        return;
    }
    publicKey1.size = NUM32;
    publicKey1.type = HKS_BLOB_TYPE_KEY;

    status = hks_export_public_key(&keyAlias, &publicKey1);
    TEST_ASSERT_EQUAL_INT(NUM1010, status);
    HksBlobDestroyT1(&publicKey1);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Export Public key
// end++++++++++++++++++++++++++++++++++++++++++++++++1000-1090

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Hash
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++1100-1190

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1100, LEVEL1)
{
    struct hks_blob src, dst;
    src.data = (uint8_t *)"123456";
    src.size = NUM6;
    dst.data = (uint8_t *)malloc(NUM65);
    if (dst.data == NULL) {
        return;
    }
    dst.size = NUM65;

    int32_t res = hks_hash(HKS_ALG_HASH_SHA_256, &src, &dst);
    TEST_ASSERT_EQUAL_INT(0, res);
    free(dst.data);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1110, LEVEL1)
{
    struct hks_blob src, dst;
    src.data = (uint8_t *)"123456";
    src.size = NUM6;
    dst.data = (uint8_t *)malloc(NUM65);
    if (dst.data == NULL) {
        return;
    }
    dst.size = NUM65;

    int32_t res = hks_hash(HKS_ALG_HASH_SHA_512, &src, &dst);
    TEST_ASSERT_EQUAL_INT(0, res);
    free(dst.data);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1120, LEVEL2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "3031323334353637383961626364656630313233343536373839616263646566";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = HKS_ALG_HASH_SHA_1; // != HKS_ALG_HASH_SHA_256 HKS_ALG_HASH_SHA_512
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&hash);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1130, LEVEL2)
{
    struct hks_blob *srcData = NULL; // = NULL

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "3031323334353637383961626364656630313233343536373839616263646566";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, srcData, &hash);
    HksBlobDestroyT1(&hash);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1140, LEVEL2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 1); // srcData.data = NULL

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "3031323334353637383961626364656630313233343536373839616263646566";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&hash);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1150, LEVEL2)
{
    struct hks_blob srcData = { 0 };
    srcData.data = (uint8_t *)"1234567890abcdefghigkl0123456789";
    srcData.size = 0; // = 0
    srcData.type = HKS_BLOB_TYPE_RAW;

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "3031323334353637383961626364656630313233343536373839616263646566";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&hash);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1160, LEVEL2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob *hash = NULL; //  = NULL

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, &srcData, hash);
    HksBlobDestroyT1(&srcData);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1170, LEVEL2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "3031323334353637383961626364656630313233343536373839616263646566";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 1); // hash.data = NULL

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&hash);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1180, LEVEL2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "303132333435363738396162636465663031323334353637383961626361";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM30, 0); // hash.size < 32

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&hash);
    TEST_ASSERT_EQUAL_INT(NUM1007, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_1600
 * @tc.name      : Hash
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataHash1190, LEVEL2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "303132333435363738396162636465663031323334353637383961626361303132333435363738396162636465663031323334353637383961626361";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM60, 0); // hash.size < 64

    uint32_t alg = HKS_ALG_HASH_SHA_512;
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&hash);
    TEST_ASSERT_EQUAL_INT(NUM1007, status);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Hash
// end+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++1100-1190


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Generate random
// beign++++++++++++++++++++++++++++++++++++++++++++++++1200-1230

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0800
 * @tc.name      : Generate Random
 * @tc.desc      : [C- SECURITY -1700]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataGenerateRandom1200, LEVEL1)
{
    int32_t statusFirst;
    int32_t statusSecond;
    struct hks_blob randomFirst = { 0 };
    struct hks_blob randomSecond = { 0 };

    HksStBlobInit1(&randomFirst, 1, NUM64, 0);
    HksStBlobInit1(&randomSecond, 1, NUM64, 0);
    statusFirst = hks_generate_random(&randomFirst);
    statusSecond = hks_generate_random(&randomSecond);
    TEST_ASSERT_EQUAL_INT(0, statusFirst);
    TEST_ASSERT_EQUAL_INT(0, statusSecond);
    TEST_ASSERT_NOT_EQUAL(randomFirst.data, randomSecond.data);

    HksBlobDestroyT1(&randomFirst);
    HksBlobDestroyT1(&randomSecond);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0800
 * @tc.name      : Generate Random
 * @tc.desc      : [C- SECURITY -1700]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataGenerateRandom1210, LEVEL2)
{
    int32_t status;
    struct hks_blob *random = NULL; // = NULL

    status = hks_generate_random(random);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0800
 * @tc.name      : Generate Random
 * @tc.desc      : [C- SECURITY -1700]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataGenerateRandom1220, LEVEL2)
{
    int32_t status;
    struct hks_blob random = { 0 };

    random.data = NULL; // = NULL
    random.size = NUM32;
    random.type = HKS_BLOB_TYPE_KEY;

    status = hks_generate_random(&random);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
    HksBlobDestroyT1(&random);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0800
 * @tc.name      : Generate Random
 * @tc.desc      : [C- SECURITY -1700]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksExportHashRandomHmacTestSuite, securityDataGenerateRandom1230, LEVEL2)
{
    int32_t status;
    struct hks_blob random = { 0 };

    random.data = (uint8_t *)malloc(NUM1025);
    if (random.data == NULL) {
        return;
    }
    random.size = NUM1025; // > 1024
    random.type = HKS_BLOB_TYPE_KEY;

    status = hks_generate_random(&random);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
    HksBlobDestroyT1(&random);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Generate random
// end++++++++++++++++++++++++++++++++++++++++++++++++++1200-1230

RUN_TEST_SUITE(SecurityDataHuksExportHashRandomHmacTestSuite);
