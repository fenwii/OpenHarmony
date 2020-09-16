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
#include <hks_file_api.h>
#include "gtest/gtest.h"
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>
#include "hks_errno.h"
#include <sys/time.h>
#include <hks_hardware_api.h>
using namespace std;
using namespace testing::ext;

class SecurityDataHuksGenDelTestSuite : public testing::Test {
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

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++generate key
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++0100-1300

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0100, TestSize.Level1)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    int32_t statusGenerate;
    int32_t statusDelete;
    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;
    struct hks_blob keyAliasGenerate;
    HksStBlobInit1(&keyAliasGenerate, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
    if (memcpy_s(keyAliasGenerate.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
        HksBlobDestroyT1(&keyAliasGenerate);
        EXPECT_EQ(0, 1);
        return;
    }
    char tmpGenerate[NUM3] = { 0 };
    if (strcat_s((char *)keyAliasGenerate.data, strlen((char *)keyAliasGenerate.data) + strlen(tmpGenerate) + 1, tmpGenerate) != EOK) {
        HksBlobDestroyT1(&keyAliasGenerate);
        EXPECT_EQ(0, 1);
        return;
    }
    keyAliasGenerate.size = strlen((char *)keyAliasGenerate.data);
    statusGenerate = hks_generate_key(&keyAliasGenerate, &keyParam);
    EXPECT_EQ(0, statusGenerate);
    HksBlobDestroyT1(&keyAliasGenerate);
    struct hks_blob keyAliasDelete;
    HksStBlobInit1(&keyAliasDelete, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
    if (memcpy_s(keyAliasDelete.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
        HksBlobDestroyT1(&keyAliasDelete);
        EXPECT_EQ(0, 1);
        return;
    }
    char tmpDelete[NUM3] = { 0 };
    if (strcat_s((char *)keyAliasDelete.data, strlen((char *)keyAliasDelete.data) + strlen(tmpDelete) + 1, tmpDelete) != EOK) {
        HksBlobDestroyT1(&keyAliasDelete);
        EXPECT_EQ(0, 1);
        return;
    }
    keyAliasDelete.size = strlen((char *)keyAliasDelete.data);
    statusDelete = hks_delete_key(&keyAliasDelete);
    EXPECT_EQ(0, statusDelete);
    HksBlobDestroyT1(&keyAliasDelete);
};

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0200, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob *keyAlias = nullptr; // = NULL
    int32_t status;

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(keyAlias, &keyParam);
    EXPECT_EQ(NUM1000, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0300, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = 0; // = 0

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0400, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = NUM65; // > 64

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0500, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = 0; // != HKS_BLOB_TYPE_ALIAS
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0600, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = NULL; // = NULL
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    int32_t status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0700, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param *keyParam = nullptr; // = NULL

    status = hks_generate_key(&keyAlias, keyParam);
    EXPECT_EQ(NUM1000, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0800, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = 1; // != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM134, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0900, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = 0; // = 0
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey1000, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = NUM65; // > 64
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey1100, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = 0; // != HKS_BLOB_TYPE_AUTHID
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey1200, TestSize.Level2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = NULL; // = NULL
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    EXPECT_EQ(NUM1000, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0000
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey1300, TestSize.Level2)
{
    char testFileName[] = "keyalias1", testFileName1[] = "key_auth_id1";
    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t*)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;
    for (int j = 0; j < NUM21; j++) {
        struct hks_blob keyAlias;
        HksStBlobInit1(&keyAlias, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
        if (memcpy_s(keyAlias.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
            HksBlobDestroyT1(&keyAlias);
            EXPECT_EQ(0, 1);
            return;
        }
        char tmp[NUM3] = { 0 };
        sprintf_s(tmp, sizeof(tmp), "%d", j);
        if (strcat_s((char*)keyAlias.data, strlen((char*)keyAlias.data) + strlen(tmp) + 1, tmp) != EOK) {
            HksBlobDestroyT1(&keyAlias);
            EXPECT_EQ(0, 1);
            return;
        }
        keyAlias.size = strlen((char*)keyAlias.data);
        int status = hks_generate_key(&keyAlias, &keyParam);
        if (j < NUM20){
            EXPECT_EQ(0, status);
            }
        else {
            EXPECT_EQ(NUM142, status);
            }
        HksBlobDestroyT1(&keyAlias);
    }
    for (int j = 0; j < NUM20; j++) {
        struct hks_blob keyAlias;
        HksStBlobInit1(&keyAlias, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
        if (memcpy_s(keyAlias.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
            HksBlobDestroyT1(&keyAlias);
            EXPECT_EQ(0, 1);
            return;
        }
        char tmp[NUM3] = { 0 };
        sprintf_s(tmp, sizeof(tmp), "%d", j);
        if (strcat_s((char*)keyAlias.data, strlen((char*)keyAlias.data) + strlen(tmp) + 1, tmp) != EOK) {
            HksBlobDestroyT1(&keyAlias);
            EXPECT_EQ(0, 1);
            return;
        }
        keyAlias.size = strlen((char*)keyAlias.data);
        int status = hks_delete_key(&keyAlias);
        EXPECT_EQ(0, status);
        HksBlobDestroyT1(&keyAlias);
    }
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++generate key
// end+++++++++++++++++++++++++++++++++++++++++++++++++++++0100-1300

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Delete key
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++++1400-2000

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey1400, TestSize.Level1)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    int32_t statusGenerate;
    int32_t statusDelete;
    struct hks_key_param keyParam;
    keyParam.key_auth_id.data = (uint8_t *)testFileName1;
    keyParam.key_auth_id.size = sizeof(testFileName1);
    keyParam.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam.key_type = HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519;
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;
    struct hks_blob keyAliasGenerate;
    HksStBlobInit1(&keyAliasGenerate, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
    if (memcpy_s(keyAliasGenerate.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
        HksBlobDestroyT1(&keyAliasGenerate);
        EXPECT_EQ(0, 1);
        return;
    }
    char tmpGenerate[NUM3] = { 0 };
    if (strcat_s((char *)keyAliasGenerate.data, strlen((char *)keyAliasGenerate.data) + strlen(tmpGenerate) + 1, tmpGenerate) != EOK) {
        HksBlobDestroyT1(&keyAliasGenerate);
        EXPECT_EQ(0, 1);
        return;
    }
    keyAliasGenerate.size = strlen((char *)keyAliasGenerate.data);
    statusGenerate = hks_generate_key(&keyAliasGenerate, &keyParam);
    EXPECT_EQ(0, statusGenerate);
    HksBlobDestroyT1(&keyAliasGenerate);
    struct hks_blob keyAliasDelete;
    HksStBlobInit1(&keyAliasDelete, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
    if (memcpy_s(keyAliasDelete.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
        HksBlobDestroyT1(&keyAliasDelete);
        EXPECT_EQ(0, 1);
        return;
    }
    char tmpDelete[NUM3] = { 0 };
    if (strcat_s((char *)keyAliasDelete.data, strlen((char *)keyAliasDelete.data) + strlen(tmpDelete) + 1, tmpDelete) != EOK) {
        HksBlobDestroyT1(&keyAliasDelete);
        EXPECT_EQ(0, 1);
        return;
    }
    keyAliasDelete.size = strlen((char *)keyAliasDelete.data);
    statusDelete = hks_delete_key(&keyAliasDelete);
    EXPECT_EQ(0, statusDelete);
    HksBlobDestroyT1(&keyAliasDelete);
};

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey1500, TestSize.Level2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob *keyAlias = nullptr; // = NULL

    status = hks_delete_key(keyAlias);
    EXPECT_EQ(NUM1000, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey1600, TestSize.Level2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = NULL; // = NULL
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_delete_key(&keyAlias);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey1700, TestSize.Level2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = 0; // != HKS_BLOB_TYPE_ALIAS

    status = hks_delete_key(&keyAlias);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey1800, TestSize.Level2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = 0;
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_delete_key(&keyAlias);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey1900, TestSize.Level2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = NUM65;
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_delete_key(&keyAlias);
    EXPECT_EQ(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL1_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1500]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
HWTEST_F(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey2000, TestSize.Level2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_delete_key(&keyAlias);
    EXPECT_EQ(NUM1010, status);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Delete key
// end+++++++++++++++++++++++++++++++++++++++++++++++++++++++1400-2000

