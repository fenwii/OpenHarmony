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

class SecurityDataHuksHashRandomHmacTestSuite : public testing::Test {
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

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Hash
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++6900-7800

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash6900, TestSize.Level1)
{
    struct hks_blob src, dst;
    src.data = (uint8_t *)"123456";
    src.size = NUM6;
    dst.data = (uint8_t *)malloc(NUM65);
    if (dst.data == NULL) {
        EXPECT_EQ(0, 1);
    }
    dst.size = NUM65;

    int32_t res = hks_hash(HKS_ALG_HASH_SHA_256, &src, &dst);
    EXPECT_EQ(0, res);
    free(dst.data);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7000, TestSize.Level1)
{
    struct hks_blob src, dst;
    src.data = (uint8_t *)"123456";
    src.size = NUM6;
    dst.data = (uint8_t *)malloc(NUM65);
    if (dst.data == NULL) {
        EXPECT_EQ(0, 1);
    }
    dst.size = NUM65;

    int32_t res = hks_hash(HKS_ALG_HASH_SHA_512, &src, &dst);
    EXPECT_EQ(0, res);
    free(dst.data);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7100, TestSize.Level2)
{
    struct hks_blob srcData = { 0 };
    char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob hash = { 0 };
    char tmpData7[] = "3031323334353637383961626364656630313233343536373839616263646566";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = HKS_ALG_HASH_SHA_1; // != HKS_ALG_HASH_SHA_256 HKS_ALG_HASH_SHA_512
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&hash);
    EXPECT_EQ(NUM135, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7200, TestSize.Level2)
{
    struct hks_blob *srcData = nullptr; // = NULL

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "3031323334353637383961626364656630313233343536373839616263646566";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, srcData, &hash);
    HksBlobDestroyT1(&hash);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7300, TestSize.Level2)
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
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7400, TestSize.Level2)
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
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7500, TestSize.Level2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob *hash = nullptr; //  = NULL

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, &srcData, hash);
    HksBlobDestroyT1(&srcData);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7600, TestSize.Level2)
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
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7700, TestSize.Level2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "303132333435363738396162636465663031323334353637383961611266";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM30, 0); // hash.size < 32

    uint32_t alg = HKS_ALG_HASH_SHA_256;
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&hash);
    EXPECT_EQ(NUM1007, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1500
 * @tc.name      : Hash
 * @tc.desc      : [C- SECURITY -1600]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHash7800, TestSize.Level2)
{
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "30313233343536373839616263646566";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM16, 0);

    struct hks_blob hash = { 0 };
    const char tmpData7[] = "303132333435363738396162636465663031323334353637383961626364656630313233343536373839616263646566303132333435363738396162";
    BuildBlobData(&hash, tmpData7, HKS_BLOB_TYPE_RAW, NUM60, 0); // hash.size < 64

    uint32_t alg = HKS_ALG_HASH_SHA_512;
    int32_t status = hks_hash(alg, &srcData, &hash);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&hash);
    EXPECT_EQ(NUM1007, status);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Hash
// end+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++6900-7800


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Generate random
// beign++++++++++++++++++++++++++++++++++++++++++++++++7900-8200

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0700
 * @tc.name      : Generate Random
 * @tc.desc      : [C- SECURITY -1700]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataGenerateRandom7900, TestSize.Level1)
{
    int32_t status;
    struct hks_blob random = { 0 };

    random.data = (uint8_t *)calloc(1, NUM64);
    if (random.data == NULL) {
        EXPECT_EQ(0, 1);
        return;
    }
    if (memset_s(random.data, NUM64, 0, NUM64) != EOK) {
        EXPECT_EQ(0, 1);
    }
    random.size = NUM64;
    random.type = 0;
    status = hks_generate_random(&random);
    EXPECT_EQ(0, status);

    HksBlobDestroyT1(&random);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0700
 * @tc.name      : Generate Random
 * @tc.desc      : [C- SECURITY -1700]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataGenerateRandom8000, TestSize.Level2)
{
    int32_t status;
    struct hks_blob *random = nullptr; // = NULL

    status = hks_generate_random(random);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0700
 * @tc.name      : Generate Random
 * @tc.desc      : [C- SECURITY -1700]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataGenerateRandom8100, TestSize.Level2)
{
    int32_t status;
    struct hks_blob random = { 0 };

    random.data = NULL; // = NULL
    random.size = NUM32;
    random.type = HKS_BLOB_TYPE_KEY;

    status = hks_generate_random(&random);
    EXPECT_EQ(NUM1000, status);
    HksBlobDestroyT1(&random);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0700
 * @tc.name      : Generate Random
 * @tc.desc      : [C- SECURITY -1700]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataGenerateRandom8200, TestSize.Level2)
{
    int32_t status;
    struct hks_blob random = { 0 };

    random.data = (uint8_t *)malloc(NUM1025);
    if (random.data == NULL) {
        EXPECT_EQ(0, 1);
    }
    random.size = NUM1025; // > 1024
    random.type = HKS_BLOB_TYPE_KEY;

    status = hks_generate_random(&random);
    EXPECT_EQ(NUM135, status);
    HksBlobDestroyT1(&random);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Generate random
// end++++++++++++++++++++++++++++++++++++++++++++++++++7900-8200

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Hmac
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++8300-9700

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1400
 * @tc.name      : Hmac
 * @tc.desc      : [C- SECURITY -2000]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHmac8300, TestSize.Level1)
{
    struct hks_blob keyAlias;
    uint32_t alg = hks_alg_hmac(HKS_ALG_HASH_SHA_256);
    struct hks_blob srcData;
    srcData.data = (uint8_t *)"123456789";
    srcData.size = NUM9;

    struct hks_blob output;
    output.data = (uint8_t *)malloc(NUM65);
    output.size = NUM65;
    keyAlias.data = (uint8_t *)"1234567890abcdefghigkl0123456789";
    keyAlias.size = NUM32;
    keyAlias.type = HKS_KEY_USAGE_EXPORT;

    int32_t status = hks_hmac(&keyAlias, alg, &srcData, &output);
    EXPECT_EQ(0, status);

    HKS_FREE_PTR1(output.data);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1400
 * @tc.name      : Hmac
 * @tc.desc      : [C- SECURITY -2000]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHmac8400, TestSize.Level1)
{
    struct hks_blob keyAlias;
    uint32_t alg = hks_alg_hmac(HKS_ALG_HASH_SHA_512);
    struct hks_blob srcData;
    srcData.data = (uint8_t *)"123456789";
    srcData.size = NUM9;

    struct hks_blob output;
    output.data = (uint8_t *)malloc(NUM65);
    output.size = NUM65;
    keyAlias.data = (uint8_t *)"1234567890abcdefghigkl0123456789";
    keyAlias.size = NUM65;
    keyAlias.type = HKS_KEY_USAGE_EXPORT;

    int32_t status = hks_hmac(&keyAlias, alg, &srcData, &output);
    EXPECT_EQ(0, status);

    HKS_FREE_PTR1(output.data);
};

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1400
 * @tc.name      : Hmac
 * @tc.desc      : [C- SECURITY -2000]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHmac8500, TestSize.Level2)
{
    struct hks_blob *key = nullptr; // key = NULL
    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "3031323334353637";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM8, 0);

    struct hks_blob output = { 0 };
    const char tmpData7[] = "3031323334353637303132333435363730313233343536373031323334353637";
    BuildBlobData(&output, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = hks_alg_hmac(HKS_ALG_HASH_SHA_256);
    int32_t status = hks_hmac(key, alg, &srcData, &output);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&output);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1400
 * @tc.name      : Hmac
 * @tc.desc      : [C- SECURITY -2000]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHmac8600, TestSize.Level2)
{
    struct hks_blob key = { 0 };
    const char tmpData5[] = "3031323334353637303132333435363730313233343536373031323334353637";
    BuildBlobData(&key, tmpData5, HKS_BLOB_TYPE_RAW, NUM32, NUM1); // key.data = NULL

    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "3031323334353637";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM8, 0);

    struct hks_blob output = { 0 };
    const char tmpData7[] = "3031323334353637303132333435363730313233343536373031323334353637";
    BuildBlobData(&output, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = hks_alg_hmac(HKS_ALG_HASH_SHA_256);
    int32_t status = hks_hmac(&key, alg, &srcData, &output);
    HksBlobDestroyT1(&key);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&output);
    EXPECT_EQ(NUM1000, status);
}

/*
 * @tc.number    : SUB_SEC_DataPro_HuksL1_1400
 * @tc.name      : Hmac
 * @tc.desc      : [C- SECURITY -2000]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksHashRandomHmacTestSuite, securityDataHmac8700, TestSize.Level2)
{
    struct hks_blob key = { 0 };
    key.data = (uint8_t *)"1234567890abcdefghigkl0123456789";
    key.size = 0; // key.size <= 0
    key.type = HKS_BLOB_TYPE_RAW;

    struct hks_blob srcData = { 0 };
    const char tmpData6[] = "3031323334353637";
    BuildBlobData(&srcData, tmpData6, HKS_BLOB_TYPE_RAW, NUM8, 0);

    struct hks_blob output = { 0 };
    const char tmpData7[] = "3031323334353637303132333435363730313233343536373031323334353637";
    BuildBlobData(&output, tmpData7, HKS_BLOB_TYPE_RAW, NUM32, 0);

    uint32_t alg = hks_alg_hmac(HKS_ALG_HASH_SHA_256);
    int32_t status = hks_hmac(&key, alg, &srcData, &output);
    HksBlobDestroyT1(&srcData);
    HksBlobDestroyT1(&output);
    EXPECT_EQ(NUM1000, status);
}
