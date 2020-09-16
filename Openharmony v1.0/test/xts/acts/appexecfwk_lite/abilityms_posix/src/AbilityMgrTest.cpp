/**
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <log.h>
#include <semaphore.h>

#include "gtest/gtest.h"
#include "securec.h"

#include "ability.h"
#include "ability_connection.h"
#include "ability_env.h"
#include "ability_event_handler.h"
#include "ability_manager.h"
#include "ability_slice.h"
#include "abilityms_client.h"
#include "bundle_manager.h"
#include "want.h"

using namespace std;
using namespace testing::ext;
using namespace OHOS;
static int32_t g_errorCode = -1;
static sem_t g_sem;
static const int32_t WAIT_TIMEOUT = 30;
static bool g_installState = false;

extern "C" {
void __attribute__((weak)) HOS_SystemInit(void){};
}

/* install callback */
static void TestBundleStateCallback(const uint8_t resultCode, const void *resultMessage)
{
    HILOG_DEBUG(HILOG_MODULE_APP, "TestBundleStateCallback resultCode: %d", resultCode);
    HILOG_DEBUG(HILOG_MODULE_APP, "TestBundleStateCallback resultMessage: %s", (char *) resultMessage);
    if (resultCode == 0) {
        g_installState = true;
        g_errorCode = resultCode;
    } else {
        g_installState = false;
        g_errorCode = resultCode;
    }
    sem_post(&g_sem);
}

/* connectAbiltiy callback */
static void OnAbilityConnectDone(ElementName *elementName, SvcIdentity *serviceSid, int resultCode, void *storeData)
{
    printf("OnAbilityConnectDone, serviceSid is %p \n", serviceSid);
    printf("elementName is %s, %s \n", elementName->bundleName, elementName->abilityName);
    ClearElement(elementName);
    if (serviceSid == nullptr) {
        return;
    }
    printf("ipc callback success \n");
    // push data
    IpcIo request;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&request, data, IPC_IO_DATA_MAX, 0);
    int32_t data1 = 10;
    int32_t data2 = 6;
    IpcIoPushInt32(&request, data1);
    IpcIoPushInt32(&request, data2);
    // send and getReply
    IpcIo reply = {nullptr};
    uintptr_t ptr = 0;
    Transact(NULL, *serviceSid, 0, &request, &reply, LITEIPC_FLAG_DEFAULT, &ptr);
    int result = 0;
    result = IpcIoPopInt32(&reply);
    if (result != 0) {
        printf("execute add method, result is %d\n", result);
    }
    if (ptr != 0) {
        FreeBuffer(nullptr, reinterpret_cast<void *>(ptr));
    }
    sem_post(&g_sem);
}

static void OnAbilityDisconnectDone(ElementName *elementName, int resultCode, void *storeData)
{
    printf("OnAbilityDisconnectDone\n");
    sem_post(&g_sem);
}


static IAbilityConnection g_conn = {
    .OnAbilityConnectDone = OnAbilityConnectDone,
    .OnAbilityDisconnectDone = OnAbilityDisconnectDone
};

class AbilityMgrTest: public testing :: Test {
protected:
    static void SetUpTestCase(void)
    {
        printf("----------test case with AbilityMgrTest start-------------\n");
        HOS_SystemInit();
        AbilityMsClient::GetInstance().Initialize();
        sem_init(&g_sem, 0, 0);
        bool installResult = false;
        installResult = Install("/test_root/appexecfwk/testnative.hap", nullptr, TestBundleStateCallback);
        struct timespec ts = {};
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += WAIT_TIMEOUT;
        sem_timedwait(&g_sem, &ts);
        if (installResult) {
            printf("sem exit \n");
        }
    }
    static void TearDownTestCase(void)
    {
        bool uninstallResult = false;
        sem_init(&g_sem, 0, 0);
        uninstallResult = Uninstall("com.huawei.testnative", nullptr, TestBundleStateCallback);
        sem_wait(&g_sem);
        if (uninstallResult) {
            printf("sem exit \n");
        }
        printf("----------test case with AbilityMgrTest end-------------\n");
    }
};

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_013
 * @tc.name      : testClearElement parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(AbilityMgrTest, testClearElement, TestSize.Level0)
{
    printf("------start testClearElement------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementAbilityName(&element, "SecondAbility");
    if (element.abilityName != nullptr) {
        printf("abilityName is %s \n", element.abilityName);
        char aName[] = "SecondAbility";
        EXPECT_STREQ(element.abilityName, aName);
        ClearElement(&element);
        printf("AbilityName afterclear is %s \n", element.abilityName);
        EXPECT_STREQ(element.abilityName, nullptr);
    }
    printf("------end testClearElement------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_014
 * @tc.name      : testClearElement parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testClearElementIllegal, TestSize.Level2)
{
    printf("------start testClearElementIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementAbilityName(&element, "SecondAbility");
    if (element.abilityName != nullptr) {
        printf("abilityName is %s \n", element.abilityName);
        char aName[] = "SecondAbility";
        EXPECT_STREQ(element.abilityName, aName);
        ClearElement(nullptr);
        printf("AbilityName of element is %s \n", element.abilityName);
        EXPECT_STREQ(element.abilityName, aName);
    }
    printf("------end testClearElementIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_015
 * @tc.name      : testSetWantElement parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(AbilityMgrTest, testSetWantElement, TestSize.Level0)
{
    printf("------start testSetWantElement------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementDeviceID(&element, "0001000");
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "SecondAbility");
    if (element.abilityName !=nullptr) {
        SetWantElement(&want, element);
        if (want.element->abilityName != nullptr) {
            printf("deviceid is %s \n", want.element->deviceId);
            printf("abilityName is %s \n", want.element->abilityName);
            printf("bundleName is %s \n", want.element->bundleName);
            EXPECT_STREQ(want.element->deviceId, "0001000");
            EXPECT_STREQ(want.element->abilityName, "SecondAbility");
            EXPECT_STREQ(want.element->bundleName, "com.huawei.testnative");
        }
    }
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testSetWantElement------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_016
 * @tc.name      : testSetWantElement parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testSetWantElementIllegal, TestSize.Level2)
{
    printf("------start testSetWantElementIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetWantElement(&want, element);
    if (want.element->abilityName == nullptr) {
        printf("deviceid is %s \n", want.element->deviceId);
        printf("abilityName is %s \n", want.element->abilityName);
        printf("bundleName is %s \n", want.element->bundleName);
        EXPECT_STREQ(want.element->deviceId, nullptr);
        EXPECT_STREQ(want.element->abilityName, nullptr);
        EXPECT_STREQ(want.element->bundleName, nullptr);
    }
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testSetWantElementIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_022
 * @tc.name      : testClearWant parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testClearWantIllegal, TestSize.Level2)
{
    printf("------start testClearWantIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementAbilityName(&element, "SecondAbility");
    if (element.abilityName != nullptr) {
        SetWantElement(&want, element);
        if (want.element->abilityName != nullptr) {
            printf("abilityName is %s \n", want.element->abilityName);
            char aName[] = "SecondAbility";
            EXPECT_STREQ(want.element->abilityName, aName);
            ClearWant(nullptr);
            printf("AbilityName afterclear is %s \n", want.element->abilityName);
            EXPECT_STREQ(want.element->abilityName, aName);
        }
    }
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testClearWantIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_025
 * @tc.name      : testWantToUri parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(AbilityMgrTest, testWantToUri, TestSize.Level0)
{
    printf("------start testWantToUri------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementDeviceID(&element, "0001000");
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "SecondAbility");
    if (element.abilityName !=nullptr) {
        SetWantElement(&want, element);
        if (want.element->abilityName !=nullptr) {
            printf("deviceid is %s \n", want.element->deviceId);
            printf("abilityName is %s \n", want.element->abilityName);
            printf("bundleName is %s \n", want.element->bundleName);
            const char *uri = WantToUri(want);
            printf("uri is %s \n", uri);
            const char *expectResult = "#Want;device=0001000;bundle=com.huawei.testnative;ability=SecondAbility;end";
            EXPECT_STREQ(uri, expectResult);
            free((void*)uri);
        }
    }
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testWantToUri------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_026
 * @tc.name      : testWantToUri parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testWantToUriIllegal, TestSize.Level2)
{
    printf("------start testWantToUriIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    const char *uri = WantToUri(want);
    printf("uri is %s \n", uri);
    const char *expectResult = "#Want;device=;bundle=;ability=;end";
    EXPECT_STREQ(uri, expectResult);
    if (uri != nullptr) {
        free((void*)uri);
    }
    printf("------end testWantToUriIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_017
 * @tc.name      : testSetWantDate parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(AbilityMgrTest, testSetWantDate, TestSize.Level0)
{
    printf("------start testSetWantDate------\n");
    Want want = { nullptr };
    SetWantData(&want, "test", 5);
    if (want.data != nullptr) {
        printf("data is %s \n", (char*)(want.data));
        printf("dataLength is %d \n", want.dataLength);
        EXPECT_STREQ((char*)(want.data), "test");
        EXPECT_TRUE(want.dataLength == 5);
    }
    ClearWant(&want);
    printf("------end testSetWantDate------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_018
 * @tc.name      : testSetWantDate parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testSetWantDateIllegal, TestSize.Level2)
{
    printf("------start testSetWantDateIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetWantData(&want, "test", -1);
    printf("dataLength is %d \n", want.dataLength);
    EXPECT_STREQ((char*)(want.data), nullptr);
    EXPECT_TRUE(want.dataLength == 0);
    SetWantData(&want, nullptr, 0);
    printf("dataLength is %d \n", want.dataLength);
    EXPECT_STREQ((char*)(want.data), nullptr);
    EXPECT_TRUE(want.dataLength == 0);
    printf("------end testSetWantDateIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_023
 * @tc.name      : testWantParseUri parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(AbilityMgrTest, testWantParseUri, TestSize.Level0)
{
    printf("------start testWantParseUri------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementDeviceID(&element, "0001000");
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "SecondAbility");
    if (element.abilityName != nullptr) {
        SetWantElement(&want, element);
        if (want.element->abilityName != nullptr) {
            printf("deviceid is %s \n", want.element->deviceId);
            printf("abilityName is %s \n", want.element->abilityName);
            printf("bundleName is %s \n", want.element->bundleName);
            const char *uri = WantToUri(want);
            Want *want2 = WantParseUri(uri);
            printf("uri is %s \n", uri);
            if (uri != nullptr) {
                free((void*)uri);
            }
            printf("want is %s \n", want2->element->deviceId);
            EXPECT_STREQ(want2->element->deviceId, want.element->deviceId);
            EXPECT_STREQ(want2->element->abilityName, want.element->abilityName);
            EXPECT_STREQ(want2->element->bundleName, want.element->bundleName);
            free(want2);
        }
    }
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testWantParseUri------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_024
 * @tc.name      : testWantParseUri parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testWantParseUriIllegal, TestSize.Level2)
{
    printf("------start testWantParseUriIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, nullptr);
    SetWantElement(&want, element);
    const char *uri = WantToUri(want);
    // empty
    printf("uri is %s \n", uri);
    Want *want2 = WantParseUri(uri);
    if (uri != nullptr) {
        free((void*)uri);
    }
    if (want2 != nullptr) {
        printf("want is %s \n", want2->element->bundleName);
        EXPECT_STREQ(want2->element->deviceId, "");
        EXPECT_STREQ(want2->element->abilityName, "");
        EXPECT_STREQ(want2->element->bundleName, "");
        free(want2);
    } 
    // nullptr
    Want *want4 = WantParseUri(nullptr);
    printf("want4 is %p \n", want4);
    EXPECT_TRUE(want4 == nullptr);
    const char *str = "test";
    // error format
    Want *want1 = WantParseUri(str);
    printf("want is %p \n", want1);
    EXPECT_TRUE(want1 == nullptr);
    Want *want3 = WantParseUri("");
    printf("want is %p \n", want3);
    EXPECT_TRUE(want3 == nullptr);
    free(want1);
    free(want3);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testWantParseUriIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_030
 * @tc.name      : testGetBundleNameIllegal parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testGetBundleNameIllegal, TestSize.Level1)
{
    printf("------start testGetBundleNameIllegal------\n");
    Want want;
    memset_s(&want, sizeof(Want), 0, sizeof(Want));
    ElementName element;
    memset_s(&element, sizeof(ElementName), 0, sizeof(ElementName));
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    int result = StartAbility(&want);
    sleep(2);
    printf("ret is %d \n", result);
    const char * bundleName1 = GetBundleName();
    printf("result of startAbility is %s \n", bundleName1);
    EXPECT_STREQ(bundleName1, "");
    printf("------end testGetBundleNameIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_031
 * @tc.name      : testGetSrcPathIllegal parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testGetSrcPathIllegal, TestSize.Level1)
{
    printf("------start testGetSrcPathIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    int result = StartAbility(&want);
    sleep(2);
    printf("ret is %d \n", result);
    const char * srcPath = GetSrcPath();
    printf("result of startAbility is %s \n", srcPath);
    EXPECT_STREQ(srcPath, "");
    printf("------end testGetSrcPathIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_032
 * @tc.name      : testGetDataPath parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testGetDataPathIllegal, TestSize.Level1)
{
    printf("------start testGetDataPathIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    int result = StartAbility(&want);
    sleep(2);
    printf("ret is %d \n", result);
    const char * dataPath = GetDataPath();
    printf("result of startAbility is %s \n", dataPath);
    EXPECT_STREQ(dataPath, "");
    printf("------end testGetDataPathIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_019
 * @tc.name      : testDump parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testDumpIllegal, TestSize.Level1)
{
    printf("------start testDump------\n");
    Want want;
    memset_s(&want, sizeof(Want), 0, sizeof(Want));
    ElementName element;
    memset_s(&element, sizeof(ElementName), 0, sizeof(ElementName));
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    Ability *ability = new Ability();
    int result = ability->StartAbility(want);
    sleep(3);
    printf("ret is %d \n", result);
    EXPECT_EQ(result, 0);
    char *extra = (char*)"test";
    ability->Dump(extra);
    printf("------end testDump------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_005
 * @tc.name      : testStartAbilityIllegal parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testStartAbilityIllegal, TestSize.Level2)
{
    printf("------start testStartAbilityIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    int result = StartAbility(nullptr);
    printf("ret is %d \n", result);
    int expect = -1;
    EXPECT_EQ(result, expect);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testStartAbilityIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_007
 * @tc.name      : testStopAbilityIllegal parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testStopAbilityIllegal, TestSize.Level2)
{
    printf("------start testStopAbilityIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    g_errorCode = StartAbility(&want);
    printf("ret is %d \n", g_errorCode);
    EXPECT_EQ(g_errorCode, 0);
    g_errorCode = StopAbility(nullptr);
    printf("ret of stop is %d \n", g_errorCode);
    EXPECT_EQ(g_errorCode, -1);
    printf("------end testStopAbilityIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_008
 * @tc.name      : testConnectAbiltiy parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testConnectAbiltiy, TestSize.Level1)
{
    printf("------start testConnectAbiltiy------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    sem_init(&g_sem, 0, 0);
    g_errorCode = ConnectAbility(&want, &g_conn, this);
    struct timespec ts = {};
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += WAIT_TIMEOUT;
    sem_timedwait(&g_sem, &ts);
    printf("sem exit \n");
    printf("ret is %d \n ", g_errorCode);
    EXPECT_EQ(g_errorCode, 0);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testConnectAbiltiy------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_009
 * @tc.name      : testConnectAbiltiyIllegal parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testConnectAbiltiyIllegal, TestSize.Level1)
{
    printf("------start testConnectAbiltiyIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    g_errorCode = ConnectAbility(nullptr, &g_conn, this);
    printf("ret1 is %d \n ", g_errorCode);
    EXPECT_EQ(g_errorCode, -1);
    g_errorCode = ConnectAbility(&want, nullptr, this);
    printf("ret2 is %d \n ", g_errorCode);
    EXPECT_EQ(g_errorCode, -1);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testConnectAbiltiyIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_011
 * @tc.name      : testDisConnectAbiltiyIllegal parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testDisConnectAbiltiyIllegal, TestSize.Level1)
{
    printf("------start testDisConnectAbiltiyIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "ServiceAbility");
    SetWantElement(&want, element);
    sem_init(&g_sem, 0, 0);
    g_errorCode = ConnectAbility(&want, &g_conn, this);
    struct timespec ts = {};
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += WAIT_TIMEOUT;
    sem_timedwait(&g_sem, &ts);
    printf("sem exit \n");
    printf("ret is of connect is %d \n ", g_errorCode);
    EXPECT_EQ(g_errorCode, 0);
    g_errorCode = DisconnectAbility(nullptr);
    int expect = -10;
    EXPECT_EQ(g_errorCode, expect);
    printf("ret of disconnect is %d \n ", g_errorCode);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testDisConnectAbiltiyIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_012
 * @tc.name      : testTerminateAbility parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testTerminateAbility, TestSize.Level1)
{
    printf("------start testTerminateAbility------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testnative");
    SetElementAbilityName(&element, "SecondAbility");
    SetWantElement(&want, element);
    int result1 = StartAbility(&want);
    sleep(5);
    printf("result1 of startAbility is %d \n", result1);
    EXPECT_EQ(result1, 0);
    Ability *ability = new Ability();
    int result2 = ability->TerminateAbility();
    sleep(5);
    printf("result2 of TerminateAbility is %d \n", result2);
    EXPECT_EQ(result2, 0);
    ClearElement(&element);
    ClearWant(&want);
    delete ability;
    printf("------end testTerminateAbility------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_WANT_004
 * @tc.name      : test Want Not Match BundleInfo
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testWantNotMathBundle, TestSize.Level2)
{
    printf("------start testWantNotMathBundle------\n");
    Want want;
    memset_s(&want, sizeof(Want), 0, sizeof(Want));
    ElementName element;
    char aName[] = "NoThisAbility";
    memset_s(&element, sizeof(ElementName), 0, sizeof(ElementName));
    SetElementAbilityName(&element, aName);
    SetElementBundleName(&element, "com.huawei.nothishap");
    SetWantElement(&want, element);
    AbilityInfo abilityInfo;
    memset_s(&abilityInfo, sizeof(AbilityInfo), 0, sizeof(AbilityInfo));
    g_errorCode = QueryAbilityInfo(&want, &abilityInfo);
    printf("ret is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode != 0);
    int result = StartAbility(&want);
    sleep(2);
    printf("result of startAbility is %d \n", result);
    EXPECT_TRUE(result == 0);
    printf("element is %s \n", want.element->bundleName);
    printf("------end testWantNotMathBundle------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_WANT_002
 * @tc.name      : testWantOnlyMathBundle
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testWantOnlyMathBundleName, TestSize.Level1)
{
    printf("------start testWantOnlyMathBundleName------\n");
    Want want;
    memset_s(&want, sizeof(Want), 0, sizeof(Want));
    ElementName element;
    char aName[] = "Ability";
    memset_s(&element, sizeof(ElementName), 0, sizeof(ElementName));
    SetElementAbilityName(&element, aName);
    SetElementBundleName(&element, "com.huawei.testnative");
    SetWantElement(&want, element);
    AbilityInfo abilityInfo;
    memset_s(&abilityInfo, sizeof(AbilityInfo), 0, sizeof(AbilityInfo));
    g_errorCode = QueryAbilityInfo(&want, &abilityInfo);
    printf("ret is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode != 0);
    int result = StartAbility(&want);
    sleep(2);
    printf("result of startAbility is %d \n", result);
    EXPECT_TRUE(result == 0);
    printf("element is %s \n", want.element->bundleName);
    printf("------end testWantOnlyMathBundleName------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_WANT_003
 * @tc.name      : testWantOnlyMathAbility
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(AbilityMgrTest, testWantOnlyMathAbility, TestSize.Level1)
{
    printf("------start testWantOnlyMathAbility------\n");
    Want want;
    memset_s(&want, sizeof(Want), 0, sizeof(Want));
    ElementName element;
    char aName[] = "MainAbility";
    memset_s(&element, sizeof(ElementName), 0, sizeof(ElementName));
    SetElementAbilityName(&element, aName);
    SetElementBundleName(&element, "com.huawei.test");
    SetWantElement(&want, element);
    AbilityInfo abilityInfo;
    memset_s(&abilityInfo, sizeof(AbilityInfo), 0, sizeof(AbilityInfo));
    g_errorCode = QueryAbilityInfo(&want, &abilityInfo);
    printf("ret is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode != 0);
    int result = StartAbility(&want);
    sleep(2);
    printf("result of startAbility is %d \n", result);
    EXPECT_TRUE(result == 0);
    printf("element is %s \n", want.element->abilityName);
    printf("------end testWantOnlyMathAbility------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_WANT_006
 * @tc.name      : test WantData Not Match DataLength
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testWantDataNotMatchLength, TestSize.Level2)
{
    printf("------start testWantDataNotMatchLength------\n");
    Want want;
    memset_s(&want, sizeof(Want), 0, sizeof(Want));
    ElementName element;
    memset_s(&element, sizeof(ElementName), 0, sizeof(ElementName));
    SetElementAbilityName(&element, "SecondAbility");
    SetElementBundleName(&element, "com.huawei.testnative");
    SetWantElement(&want, element);
    SetWantData(&want, "test", 3);
    int result = StartAbility(&want);
    sleep(2);
    printf("result of startAbility is %d \n", result);
    EXPECT_TRUE(result == 0);
    EXPECT_EQ(want.dataLength, 3);
    printf("------end testWantDataNotMatchLength------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_40
 * @tc.name      : PostTask parameter illegal test that callback is null
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(AbilityMgrTest, testPostTask, TestSize.Level1)
{
    printf("------start testPostTask------\n");
    const char *hapPath = (char*)"testnative.hap";
    AbilityEventHandler eventHandler1;
    auto task = [this, hapPath]{
        sem_init(&g_sem, 0, 0);
        bool installResult = Install(hapPath, nullptr, TestBundleStateCallback);
        sem_wait(&g_sem);
        printf("installResult is %d \n", installResult);
        EXPECT_TRUE(installResult);

        AbilityEventHandler *eventHandler2 = AbilityEventHandler::GetCurrentHandler();
        eventHandler2->PostQuit();
    };
    eventHandler1.PostTask(task);
    eventHandler1.Run();
    printf("------end testPostTask------\n");
}
