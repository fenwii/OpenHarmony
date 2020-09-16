/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hctest.h"
#include "discovery_service.h"
#include "session.h"
#include "securec.h"
#include <unistd.h>
#include <stdlib.h>

#define PUB_SUCCESS 1
#define PUB_FAIL (-1)
#define TESTCASE_COUNT 23
#define ERROR_SESSION_ID (-1)
#define SESSION_NAME_LEN 64
#define SOFTBUS_TEST_SUCCESS 0
#define SOFTBUS_TEST_FAIL (-1)
#define ONE_SECOND 1
#define DEF_TIMEOUT 6
#define DEF_DEVTYPE "L0"
#define DEF_DEVID "sb_test_default_devid"
#define DEF_PUB_ID 33113322
#define DEF_PUB_MODULE_NAME "sb_pub_module_name"
#define DEF_PUB_CAPABILITY "ddmpCapability"
#define DEF_PUB_CAPABILITYDATA_LEN 2
#define DEVID_MAX_LEN 96

static int g_pubFlag = 0;
static int g_setUpFlag = 0;
static int g_caseExeCount = 0;
static unsigned char* g_pubCapabilityData = (unsigned char*)"Hi";
static IPublishCallback g_pubCallback = {0};
static struct ISessionListener *g_sessionListenerCallback = NULL;

static void ResetPubFlag(void)
{
    g_pubFlag = 0;
}

static void WaitPublishResult(void)
{
    int timeout = DEF_TIMEOUT;
    while (timeout > 0) {
        sleep(ONE_SECOND);
        timeout--;
        if (g_pubFlag == PUB_SUCCESS || g_pubFlag == PUB_FAIL) {
            printf("checkPublish:wait[%d].\n", DEF_TIMEOUT - timeout);
            break;
        }
    }
    if (timeout <= 0) {
        printf("checkPublish:timeout!\n");
    }
}

/**
 * callback of publish success
 */
static void SbPublishSuccess(int pubId)
{
    printf("[PubSuccess]publish success id[%d].\n", pubId);
    g_pubFlag = PUB_SUCCESS;
}

/**
 * callback of publish fail
 */
static void SbPublishFail(int pubId, PublishFailReason reason)
{
    printf("[PubFail]publish fail id[%d],reason[%d].\n", pubId, reason);
    g_pubFlag = PUB_FAIL;
}

/**
 * callback of session opened
 */
static int SbSessionOpened(int sessionId)
{
    if (sessionId < 0) {
        printf("[Session opened]sessionId is invalid.\n");
    }
    return SOFTBUS_TEST_SUCCESS;
}

/**
 * callback of session closed
 */
static void SbSessionClosed(int sessionId)
{
    if (sessionId < 0) {
        printf("[Session closed]sessionId is invalid.\n");
    }
    printf("[Session closed]session closed.\n");
}

/**
 * callback of received data
 */
static void SbOnBytesReceived(int sessionId, const void *data, unsigned int len)
{
    if (sessionId < 0 || data == NULL) {
        printf("[Session recevie]id or data invalid, .\n");
    }
    printf("[Session recevie]receive data, length[%d].\n", len);
}

/**
 * init service during first publish
 */
static void DefaultPublishToInitService(void)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    if (pubInfo == NULL) {
        printf("[DefaultPublishToInitService]malloc fail!\n");
        return;
    }
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    if (ret != SOFTBUS_TEST_SUCCESS) {
        printf("[DefaultPublishToInitService]call PublishService fail!\n");
    } else {
        WaitPublishResult();
        if (g_pubFlag != PUB_SUCCESS) {
            printf("[DefaultPublishToInitService]call PublishService fail!\n");
            ret  = SOFTBUS_TEST_FAIL;
        }
    }
    free(pubInfo);
}

/**
 * undo the first publish
 */
static void UnDefaultPublish(void)
{
    int ret;
    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    if (ret != SOFTBUS_TEST_SUCCESS) {
        printf("[UnDefaultPublish]unpublish fail!\n");
    }
}

/**
 * @tc.desc      : register a test suite, this suite is used to test function
 * @param        : subsystem name is communication
 * @param        : module name is softbus
 * @param        : test suit name is SoftBusFuncTestSuite
 */
LITE_TEST_SUIT(communication, softbus, SoftBusFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL SoftBusFuncTestSuiteSetUp(void)
{
    if (g_setUpFlag == 0) {
        g_pubCallback.onPublishSuccess = SbPublishSuccess;
        g_pubCallback.onPublishFail = SbPublishFail;
        g_sessionListenerCallback = (struct ISessionListener*)malloc(sizeof(struct ISessionListener));
        if (g_sessionListenerCallback == NULL) {
            printf("SetUp:malloc(g_sessionListenerCallback) fail!\n");
            return FALSE;
        }
        g_sessionListenerCallback->onSessionOpened = SbSessionOpened;
        g_sessionListenerCallback->onSessionClosed = SbSessionClosed;
        g_sessionListenerCallback->onBytesReceived = SbOnBytesReceived;
        g_setUpFlag = 1;

        DefaultPublishToInitService();
        UnDefaultPublish();
    }
    g_caseExeCount++;
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL SoftBusFuncTestSuiteTearDown(void)
{
    if (g_caseExeCount == TESTCASE_COUNT) {
        if (g_sessionListenerCallback != NULL) {
            free(g_sessionListenerCallback);
            g_sessionListenerCallback = NULL;
        }
    }
    printf("+----------------------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0100
 * @tc.name      : abnormal parameter test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetNumGreaterThanMax, LEVEL3)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVID;
    devInfo->value = DEF_DEVID;
    
    int ret = SetCommonDeviceInfo(devInfo, COMM_DEVICE_KEY_MAX + 1);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    int num = 0;
    ret  = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    num = 1;
    ret  = SetCommonDeviceInfo(NULL, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0200
 * @tc.name      : set ID value less than maximum value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevIdLessThanMax, LEVEL2)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVID;
    devInfo->value = 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890abcde";
    int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0300
 * @tc.name      : set ID value equal and greater maximum value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevIdEqualMax, LEVEL3)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVID;
    devInfo->value = 
        "abcdef123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    devInfo->value = 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890abcdefg";
    ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0400
 * @tc.name      : set ID value with special characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevIdSpecialChars, LEVEL2)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVID;
    devInfo->value = "!@#$%^&*()_+:><?\n\0\r/.,[123]";
    int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0500
 * @tc.name      : set name value less than maximum value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevNameLessThanMax, LEVEL2)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVNAME;
    devInfo->value = "123456789012345678901234567890123456789012345678901234567890abc";
    int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0600
 * @tc.name      : set name value equal and greater maximum value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevNameEqualMax, LEVEL3)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVNAME;
    devInfo->value = "abcd123456789012345678901234567890123456789012345678901234567890";
    int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);

    devInfo->value = "123456789012345678901234567890123456789012345678901234567890abcde";
    ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0700
 * @tc.name      : set name value with special characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevNameSpecialChars, LEVEL2)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVNAME;
    devInfo->value = "!@#$%^&*()_+:><?\n\0\r/.,[123]";
    int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0800
 * @tc.name      : set type value not in enum
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevTypeError, LEVEL3)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVTYPE;
    devInfo->value = "error";
    int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_0900
 * @tc.name      : set type value not match actual
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevTypeNotMacthActual, LEVEL2)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    devInfo->key = COMM_DEVICE_KEY_DEVTYPE;
    devInfo->value = "PAD";
    unsigned int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1000
 * @tc.name      : set key is error
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetDevKeyIsError, LEVEL2)
{
    CommonDeviceInfo *devInfo = NULL;
    devInfo = (CommonDeviceInfo *)malloc(sizeof(CommonDeviceInfo));
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, sizeof(CommonDeviceInfo), 0, sizeof(CommonDeviceInfo));
    int errorKey = 10;
    devInfo->key = errorKey;
    devInfo->value = DEF_DEVID;
    unsigned int num = 1;
    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1100
 * @tc.name      : set all three
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetAllDevInfo, LEVEL2)
{
    int num = 3;
    CommonDeviceInfo *devInfo = NULL;
    int size = sizeof(CommonDeviceInfo)*num;
    devInfo = (CommonDeviceInfo *)malloc(size);
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, size, 0, size);
    devInfo[2].key = COMM_DEVICE_KEY_DEVID;
    devInfo[2].value = DEF_DEVID;
    devInfo[0].key = COMM_DEVICE_KEY_DEVTYPE;
    devInfo[0].value = DEF_DEVTYPE;
    devInfo[1].key = COMM_DEVICE_KEY_DEVNAME;
    devInfo[1].value = "sb_test_default_devname";

    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1200
 * @tc.name      : first set id and type ,but type is error, will set fail, then set name, will success
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSetTwoInfoOneIsError, LEVEL2)
{
    int num = 2;
    CommonDeviceInfo *devInfo = NULL;
    int size = sizeof(CommonDeviceInfo)*num;
    devInfo = (CommonDeviceInfo *)malloc(size);
    TEST_ASSERT_NOT_NULL(devInfo);
    (void)memset_s(devInfo, size, 0, size);
    devInfo[0].key = COMM_DEVICE_KEY_DEVID;
    devInfo[0].value = DEF_DEVTYPE;
    devInfo[1].key = COMM_DEVICE_KEY_DEVTYPE;
    devInfo[1].value = "error";

    int ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    num = 1;
    devInfo[0].key = COMM_DEVICE_KEY_DEVNAME;
    devInfo[0].value = "testSetTwoOneIsError";
    ret = SetCommonDeviceInfo(devInfo, num);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(devInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1300
 * @tc.name      : Test publish with invalid parameter
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPublishParameterIsNull, LEVEL2)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(NULL, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);
    ret = PublishService(DEF_PUB_MODULE_NAME, NULL, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, NULL);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    ret = PublishService(NULL, NULL, NULL);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1400
 * @tc.name      : set name value empty and less than maximum value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPubPkgNameNormal, LEVEL2)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    char *pkgNameEmpty = "";
    int ret = PublishService(pkgNameEmpty, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    ResetPubFlag();
    char *pkgNameLessMax = "123456789012345678901234567890123456789012345678901234567890abc";
    ret = PublishService(pkgNameLessMax, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    ret = UnPublishService(pkgNameEmpty, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(pkgNameLessMax, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1500
 * @tc.name      : set package name value equal and greater than maximum value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPublishPkgNameAbnormal, LEVEL2)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(NULL, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ResetPubFlag();
    char *pkgNameMax = "123456789012345678901234567890123456789012345678901234567890abcd";
    ret = PublishService(pkgNameMax, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ResetPubFlag();
    char *pkgNameMoreMax = "abcde123456789012345678901234567890123456789012345678901234567890";
    ret = PublishService(pkgNameMoreMax, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ret = UnPublishService(pkgNameMax, DEF_PUB_ID);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(pkgNameMoreMax, DEF_PUB_ID);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1600
 * @tc.name      : test publish limit
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPublishCountLimit, LEVEL2)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    char *pkgNameOne = "one";
    int ret = PublishService(pkgNameOne, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    ResetPubFlag();
    char *pkgNameTwo = "two";
    ret = PublishService(pkgNameTwo, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    ResetPubFlag();
    char *pkgNameThree = "three";
    ret = PublishService(pkgNameThree, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    ResetPubFlag();
    char *pkgNameFour = "four";
    ret = PublishService(pkgNameFour, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);
    ResetPubFlag();
    pubInfo->publishId = DEF_PUB_ID + 1;
    ret = PublishService(pkgNameOne, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);
    ResetPubFlag();
    ret = PublishService(pkgNameFour, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);
    pubInfo->publishId = DEF_PUB_ID;

    ResetPubFlag();
    ret = PublishService(pkgNameTwo, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ret = UnPublishService(pkgNameOne, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ResetPubFlag();
    ret = PublishService(pkgNameOne, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    ResetPubFlag();
    ret = PublishService(pkgNameOne, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ret = UnPublishService(pkgNameThree, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ResetPubFlag();
    ret = PublishService(pkgNameFour, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    ret = UnPublishService(pkgNameTwo, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(pkgNameOne, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(pkgNameThree, DEF_PUB_ID);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(pkgNameFour, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);

    char *pkgNameComm = "common";
    int pubIdOne = 110;
    pubInfo->publishId = pubIdOne;
    ResetPubFlag();
    ret = PublishService(pkgNameComm, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    int pubIdTwo = 220;
    pubInfo->publishId = pubIdTwo;
    ResetPubFlag();
    ret = PublishService(pkgNameComm, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    int pubIdThree = 330;
    pubInfo->publishId = pubIdThree;
    ResetPubFlag();
    ret = PublishService(pkgNameComm, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    int pubIdFour = 440;
    pubInfo->publishId = pubIdFour;
    ResetPubFlag();
    ret = PublishService(pkgNameComm, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);
    pubInfo->publishId = pubIdThree;
    ResetPubFlag();
    ret = PublishService(pkgNameOne, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);
    pubInfo->publishId = pubIdFour;
    ResetPubFlag();
    ret = PublishService(pkgNameOne, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ResetPubFlag();
    pubInfo->publishId = pubIdOne;
    ret = PublishService(pkgNameComm, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ret = UnPublishService(pkgNameComm, pubIdOne);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    pubInfo->publishId = pubIdOne;
    ResetPubFlag();
    ret = PublishService(pkgNameComm, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    ResetPubFlag();
    ret = PublishService(pkgNameComm, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ret = UnPublishService(pkgNameComm, pubIdOne);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    int pubIdFive = 555;
    pubInfo->publishId = pubIdFive;
    ResetPubFlag();
    ret = PublishService(pkgNameComm, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    ret = UnPublishService(pkgNameComm, pubIdFive);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(pkgNameComm, pubIdThree);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(pkgNameComm, pubIdTwo);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(pkgNameComm, pubIdOne);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);

    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1700
 * @tc.name      : set capability value not in list
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPublishCapabilityError, LEVEL3)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = "error capability";
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);
    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1800
 * @tc.name      : this case used to cover interface only
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testSessionSample, LEVEL3)
{
    int randomId = 5;
    char *moduleName = "default_test_module_name";
    int ret = CreateSessionServer(moduleName, "ohos", g_sessionListenerCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);

    char mySessionName[SESSION_NAME_LEN] = {0};
    ret = GetMySessionName(randomId, (char *)mySessionName, SESSION_NAME_LEN);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);

    char peerSeesionName[SESSION_NAME_LEN] = {0};
    ret = GetPeerSessionName(randomId, (char *)peerSeesionName, SESSION_NAME_LEN);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);

    char peerDeviceId[DEVID_MAX_LEN] = {0};
    ret = GetPeerDeviceId(randomId, (char *)peerDeviceId, DEVID_MAX_LEN);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);

    int size = 10;
    char *sampleCharData = "L0->phone";
    ret = SendBytes(randomId, sampleCharData, size);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);

    CloseSession(randomId);

    ret = RemoveSessionServer(moduleName, (char *)mySessionName);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_1900
 * @tc.name      : test pubInfo-publishId mode medium invalid value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPublishInfoInvalidValue, LEVEL3)
{
    int pubId = -1;
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = pubId;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_ACTIVE;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);

    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = BLE;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    pubInfo->medium = AUTO;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    pubInfo->medium = 10;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_2000
 * @tc.name      : test pubInfo-freq value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPublishInfoFreq, LEVEL3)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = LOW;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);

    pubInfo->freq = HIGH;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);

    pubInfo->freq = SUPER_HIGH;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);

    pubInfo->freq = -1;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);
    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);

    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_2100
 * @tc.name      : test pubInfo-capability invalid value
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPublishInfoCapability, LEVEL3)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = "hicall";
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    pubInfo->capability = "error capability";
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    pubInfo->capability = NULL;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_2200
 * @tc.name      : set capabilitydata value invalid
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testPublishCapabilityDataError, LEVEL3)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = NULL;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    pubInfo->capabilityData = (unsigned char *)"1";
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN - 1;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    pubInfo->capabilityData = (unsigned char *)"123";
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN + 1;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN - 1;
    ResetPubFlag();
    ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_FAIL);

    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    free(pubInfo);
}

/**
 * @tc.number    : SUB_COMMUNICATION_SOFTBUS_SDK_2300
 * @tc.name      : test unpublish invalid parameters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SoftBusFuncTestSuite, testUnPublishInvalidParam, LEVEL2)
{
    PublishInfo *pubInfo = NULL;
    pubInfo = (PublishInfo *)malloc(sizeof(PublishInfo));
    TEST_ASSERT_NOT_NULL(pubInfo);
    (void)memset_s(pubInfo, sizeof(PublishInfo), 0, sizeof(PublishInfo));
    pubInfo->publishId = DEF_PUB_ID;
    pubInfo->mode = DISCOVER_MODE_PASSIVE;
    pubInfo->medium = COAP;
    pubInfo->freq = MID;
    pubInfo->capability = DEF_PUB_CAPABILITY;
    pubInfo->capabilityData = g_pubCapabilityData;
    pubInfo->dataLen = DEF_PUB_CAPABILITYDATA_LEN;

    ResetPubFlag();
    int ret = PublishService(DEF_PUB_MODULE_NAME, pubInfo, &g_pubCallback);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    WaitPublishResult();
    TEST_ASSERT_EQUAL_INT(g_pubFlag, PUB_SUCCESS);

    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_EQUAL_INT(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(DEF_PUB_MODULE_NAME, DEF_PUB_ID);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);

    ret = UnPublishService(NULL, DEF_PUB_ID);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    ret = UnPublishService(DEF_PUB_MODULE_NAME, -1);
    TEST_ASSERT_NOT_EQUAL(ret, SOFTBUS_TEST_SUCCESS);
    free(pubInfo);
}

RUN_TEST_SUITE(SoftBusFuncTestSuite);
