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
#include "securec.h"
#include <securec.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void HksStBlobInit1(struct hks_blob *blob, size_t nmemb, size_t size, uint8_t type)
{
    if (blob == NULL || nmemb == 0 || size == 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        return;
    }
    blob->data = (uint8_t *)calloc(nmemb, size);
    if (blob->data == NULL) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        return;
    }
    if (memset_s(blob->data, size, 0, size) != EOK) {
        TEST_ASSERT_EQUAL_INT(0, 1);
    }
    blob->size = size;
    blob->type = type;
}
void HksBlobDestroyT1(struct hks_blob *blob)
{
    if (blob == NULL) {
        return;
    }
    if (blob && blob->data) {
        memset_s(blob->data, blob->size, 0, blob->size);
        HKS_FREE_PTR1(blob->data);
    }
    blob->data = NULL;
    blob->size = 0;
    blob->type = HKS_BLOB_TYPE_RAW;
}
int TestSecShuksGenerateKeyNormal(void)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
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
    int32_t status = hks_generate_key(&keyAlias, &keyParam);    
    TEST_ASSERT_EQUAL_INT(0, status);
    return 0;
}
int TestSecShuksDeleteKeyNormal(void)
{
    char testFileName[] = "keyalias1";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    int32_t status = hks_delete_key(&keyAlias);
    TEST_ASSERT_EQUAL_INT(0, status);
    return 0;
}
int TestSecShuksExportPublicNormal(struct hks_blob *keyAlias, struct hks_blob *publicKey1)
{
    int32_t status = hks_export_public_key(keyAlias, publicKey1);
    TEST_ASSERT_EQUAL_INT(0, status);
    return 0;
}
void BuildBlobData(struct hks_blob *param, const char *str, uint8_t type, uint32_t size, uint8_t isDataNull)
{
    if (param == NULL) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        return;
    }
    param->type = type;
    param->size = size;
    if (isDataNull == NUM1) {
        param->data = NULL;
    } else {
        if (size == 0) {
            return;
        }
        unsigned char *buff = (unsigned char *)malloc(size + NUM2);
        if (buff == NULL) {
            return;
        }
        memset_s(buff, size + NUM2, 0, size + NUM2);
        HexStringToByte(str, size * NUM2, buff);
        param->data = (uint8_t *)buff;
    }
}
void HexStringToByte(const char *str, int nLen, unsigned char *pHex)
{
    unsigned int number = 4;
    if (pHex == NULL) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        return;
    }
    if (nLen % NUM2) {
        TEST_ASSERT_EQUAL_INT(0, 1);
    }
    int nHexLen = nLen / NUM2;
    unsigned char nibble[2];
    if (nHexLen >= MAX_INT) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        return;
    }
    for (int i = 0; i < nHexLen; i++) {
        nibble[0] = str[i * NUM2];
        nibble[1] = str[i * NUM2 + NUM1];
        for (int j = 0; j < NUM2; j++) {
            if (nibble[j] <= 'F' && nibble[j] >= 'A') {
                nibble[j] = nibble[j] - 'A' + NUM10;
            } else if (nibble[j] <= 'f' && nibble[j] >= 'a') {
                nibble[j] = nibble[j] - 'a' + NUM10;
            } else if (nibble[j] >= '0' && nibble[j] <= '9') {
                nibble[j] = nibble[j] - '0';
            } else {
                TEST_ASSERT_EQUAL_INT(0, 1);
            }
        }
        pHex[i] = nibble[0] << number;
        pHex[i] |= nibble[1];
    }
}

void TestInitKeyParam1(struct hks_key_param *keyParam, uint32_t keyType, uint32_t keyLen, uint32_t keyMode,
    uint32_t keyUsage)
{
    if (keyParam == NULL) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        return;
    }
    keyParam->key_type = keyType;
    keyParam->key_len = keyLen;
    keyParam->key_pad = HKS_PADDING_NONE;
    keyParam->key_mode = keyMode;
    keyParam->key_domain = HKS_ECC_CURVE_ED25519;
    keyParam->key_usage = keyUsage;

    const char tmpData1[] = "111111";
    BuildBlobData(&keyParam->key_auth_id, tmpData1, HKS_BLOB_TYPE_AUTH_ID, NUM3, 0);
}
    
int TestSecShuksImportPublicNormal(void)
{
    char testFileName[] = "keyalias1";
    struct hks_key_param keyParam1 = { 0 };

    keyParam1.key_type = HKS_KEY_TYPE_EDDSA_PUBLIC_KEY_ED25519;
    keyParam1.key_len = NUM256;
    keyParam1.key_usage = NUM3;
    keyParam1.key_pad = NUM4;
    keyParam1.key_mode = NUM5;
    keyParam1.key_role = NUM6;
    keyParam1.key_auth_id.type = HKS_BLOB_TYPE_AUTH_ID;
    keyParam1.key_auth_id.data = (uint8_t *)testFileName;
    keyParam1.key_auth_id.size = sizeof(testFileName);

    struct hks_blob publicKey1 = { 0 };
    HksStBlobInit1(&publicKey1, NUM1, NUM32, HKS_BLOB_TYPE_KEY);

    struct hks_blob keyAlias;
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    int32_t status = hks_import_public_key(&keyAlias, &keyParam1, &publicKey1);
    TEST_ASSERT_EQUAL_INT(0, status);

    HksBlobDestroyT1(&publicKey1);
    return 0;
}

/* *
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is security
 * @param        : module name is securityData
 * @param        : test suit name is SecurityDataHuksGenDelTestSuite
 */
LITE_TEST_SUIT(security, securityData, SecurityDataHuksGenDelTestSuite);

/* *
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL SecurityDataHuksGenDelTestSuiteSetUp(void)
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
static BOOL SecurityDataHuksGenDelTestSuiteTearDown(void)
{
    printf("-++++++++++++++++++++++++++++++++++++++++++++-\n");
    return TRUE;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++generate key
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++0000-0120

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0000, LEVEL1)
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
        TEST_FAIL();
        return;
    }
    char tmpGenerate[3] = { 0 };
    if (strcat_s((char *)keyAliasGenerate.data, strlen((char *)keyAliasGenerate.data) + strlen(tmpGenerate) + 1, tmpGenerate) != EOK) {
        HksBlobDestroyT1(&keyAliasGenerate);
        TEST_FAIL();
        return;
    }
    keyAliasGenerate.size = strlen((char *)keyAliasGenerate.data);
    statusGenerate = hks_generate_key(&keyAliasGenerate, &keyParam);
    TEST_ASSERT_EQUAL_INT(0, statusGenerate);
    HksBlobDestroyT1(&keyAliasGenerate);
    struct hks_blob keyAliasDelete;
    HksStBlobInit1(&keyAliasDelete, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
    if (memcpy_s(keyAliasDelete.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
        HksBlobDestroyT1(&keyAliasDelete);
        TEST_FAIL();
        return;
    }
    char tmpDelete[3] = { 0 };
    if (strcat_s((char *)keyAliasDelete.data, strlen((char *)keyAliasDelete.data) + strlen(tmpDelete) + 1, tmpDelete) != EOK) {
        HksBlobDestroyT1(&keyAliasDelete);
        TEST_FAIL();
        return;
    }
    keyAliasDelete.size = strlen((char *)keyAliasDelete.data);
    statusDelete = hks_delete_key(&keyAliasDelete);
    TEST_ASSERT_EQUAL_INT(0, statusDelete);
    HksBlobDestroyT1(&keyAliasDelete);
};

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0010, LEVEL2)
{
    char testFileName1[] = "key_auth_id1";
    struct hks_blob *keyAlias = NULL; // = NULL
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
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0020, LEVEL2)
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
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0030, LEVEL2)
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
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0040, LEVEL2)
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
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0050, LEVEL2)
{
    char testFileName[] = "keyalias1";
    char testFileName1[] = "key_auth_id1";
    struct hks_blob keyAlias;
    int32_t status;

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

    status = hks_generate_key(&keyAlias, &keyParam);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0060, LEVEL2)
{
    char testFileName[] = "keyalias1";
    struct hks_blob keyAlias;
    int32_t status;

    keyAlias.type = HKS_BLOB_TYPE_ALIAS;
    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);

    struct hks_key_param *keyParam = NULL; // = NULL

    status = hks_generate_key(&keyAlias, keyParam);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0070, LEVEL2)
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
    keyParam.key_type = NUM1; // != HKS_KEY_TYPE_EDDSA_KEYPAIR_ED25519
    keyParam.key_len = 0;
    keyParam.key_usage = 0;
    keyParam.key_pad = 0;

    status = hks_generate_key(&keyAlias, &keyParam);
    TEST_ASSERT_EQUAL_INT(NUM134, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0080, LEVEL2)
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
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0090, LEVEL2)
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
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0100, LEVEL2)
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
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0110, LEVEL2)
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
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0100
 * @tc.name      : Generate key
 * @tc.desc      : [C- SECURITY -1400]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataGenerateKey0120, LEVEL2)
{
    int status;
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
            TEST_FAIL();
            return;
        }
        char tmp[3] = { 0 };
        sprintf_s(tmp, sizeof(tmp), "%d", j);
        if (strcat_s((char*)keyAlias.data, strlen((char*)keyAlias.data) + strlen(tmp) + 1, tmp) != EOK) {   
            HksBlobDestroyT1(&keyAlias);
            TEST_FAIL();
            return;
        }
        keyAlias.size = strlen((char*)keyAlias.data);
        status = hks_generate_key(&keyAlias, &keyParam);
        if (j < NUM20){
            TEST_ASSERT_EQUAL_INT(0, status);
            }
        else {
            TEST_ASSERT_EQUAL_INT(NUM142, status);
            }
        HksBlobDestroyT1(&keyAlias);
    }
    for (int j = 0; j < NUM20; j++) {
        struct hks_blob keyAlias;
        HksStBlobInit1(&keyAlias, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
        if (memcpy_s(keyAlias.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
            HksBlobDestroyT1(&keyAlias);
            TEST_FAIL();
            return;
        }
        char tmp[3] = { 0 };
        sprintf_s(tmp, sizeof(tmp), "%d", j);
        if (strcat_s((char*)keyAlias.data, strlen((char*)keyAlias.data) + strlen(tmp) + 1, tmp) != EOK) {
            HksBlobDestroyT1(&keyAlias);
            TEST_FAIL();
            return;
        }
        keyAlias.size = strlen((char*)keyAlias.data);
        status = hks_delete_key(&keyAlias);
        TEST_ASSERT_EQUAL_INT(0, status);
        HksBlobDestroyT1(&keyAlias);
    }
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++generate key
// end+++++++++++++++++++++++++++++++++++++++++++++++++++++0000-0120

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Delete key
// begin+++++++++++++++++++++++++++++++++++++++++++++++++++++0130-0190
/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey0130, LEVEL1)
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
        TEST_FAIL();
        return;
    }
    char tmpGenerate[3] = { 0 };
    if (strcat_s((char *)keyAliasGenerate.data, strlen((char *)keyAliasGenerate.data) + strlen(tmpGenerate) + 1, tmpGenerate) != EOK) {
        HksBlobDestroyT1(&keyAliasGenerate);
        TEST_FAIL();
        return;
    }
    keyAliasGenerate.size = strlen((char *)keyAliasGenerate.data);
    statusGenerate = hks_generate_key(&keyAliasGenerate, &keyParam);
    TEST_ASSERT_EQUAL_INT(0, statusGenerate);
    HksBlobDestroyT1(&keyAliasGenerate);
    struct hks_blob keyAliasDelete;
    HksStBlobInit1(&keyAliasDelete, sizeof(uint8_t), sizeof(testFileName) + NUM3, HKS_BLOB_TYPE_ALIAS);
    if (memcpy_s(keyAliasDelete.data, sizeof(testFileName), testFileName, sizeof(testFileName)) != EOK) {
        HksBlobDestroyT1(&keyAliasDelete);
        TEST_FAIL();
        return;
    }
    char tmpDelete[3] = { 0 };
    if (strcat_s((char *)keyAliasDelete.data, strlen((char *)keyAliasDelete.data) + strlen(tmpDelete) + 1, tmpDelete) != EOK) {
        HksBlobDestroyT1(&keyAliasDelete);
        TEST_FAIL();
        return;
    }
    keyAliasDelete.size = strlen((char *)keyAliasDelete.data);
    statusDelete = hks_delete_key(&keyAliasDelete);
    TEST_ASSERT_EQUAL_INT(0, statusDelete);
    HksBlobDestroyT1(&keyAliasDelete);
};

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey0140, LEVEL2)
{
    int32_t status;
    struct hks_blob *keyAlias = NULL; // = NULL

    status = hks_delete_key(keyAlias);
    TEST_ASSERT_EQUAL_INT(NUM1000, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey0150, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = NULL; // = NULL
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_delete_key(&keyAlias);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey0160, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = 0; // != HKS_BLOB_TYPE_ALIAS

    status = hks_delete_key(&keyAlias);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}
/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey0170, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = 0;
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_delete_key(&keyAlias);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}
/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey0180, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = NUM65;
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_delete_key(&keyAlias);
    TEST_ASSERT_EQUAL_INT(NUM135, status);
}

/* *
 * @tc.number    : SUB_SEC_DataPro_HuksL0_0400
 * @tc.name      : Delete key
 * @tc.desc      : [C- SECURITY -1900]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 */
LITE_TEST_CASE(SecurityDataHuksGenDelTestSuite, securityDataDeleteKey0190, LEVEL2)
{
    int32_t status;
    char testFileName[] = "Test_file_north_interfaces";
    struct hks_blob keyAlias = { 0 };

    keyAlias.data = (uint8_t *)testFileName;
    keyAlias.size = sizeof(testFileName);
    keyAlias.type = HKS_BLOB_TYPE_ALIAS;

    status = hks_delete_key(&keyAlias);
    TEST_ASSERT_EQUAL_INT(NUM1010, status);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Delete key
// end+++++++++++++++++++++++++++++++++++++++++++++++++++++++0130-0190

RUN_TEST_SUITE(SecurityDataHuksGenDelTestSuite);
