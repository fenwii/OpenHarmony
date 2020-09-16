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
#include <string>

#include "gtest/gtest.h"
#include "securec.h"
#include "bundle_info.h"
#include "bundle_manager.h"
#include "want.h"

using namespace std;
using namespace testing::ext;
using namespace OHOS;
static bool g_installState = false;
static int g_errorCode = -1;
static sem_t g_sem;
static const int32_t WAIT_TIMEOUT = 60;

extern "C" {
void __attribute__((weak)) HOS_SystemInit(void){};
}

/* callback */
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

class BundleMgrTest : public testing::Test {
protected:
    static void SetUpTestCase(void)
    {
        printf("----------test case with BundleMgrTest start-------------\n");
        HOS_SystemInit();
        sem_init(&g_sem, 0, 0);
        bool installResult = Install("/test_root/appexecfwk/testjsdemo.hap", nullptr, TestBundleStateCallback);
        sem_wait(&g_sem);
        EXPECT_TRUE(installResult);
    }
    static void TearDownTestCase(void)
    {
        sem_init(&g_sem, 0, 0);
        bool uninstallState = Uninstall("com.huawei.testjsdemo", nullptr, TestBundleStateCallback);
        sem_wait(&g_sem);
        EXPECT_TRUE(uninstallState);
        printf("----------test case with BundleMgrTest end-------------\n");
    }
};


/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_044
 * @tc.name      : ClearAbilityInfo parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testClearAbilityInfoIllegal, TestSize.Level2)
{
    printf("------start testClearAbilityInfoIllegal------\n");
    // abilityInfo is nullptr
    AbilityInfo abilityInfo;
    memset_s(&abilityInfo, sizeof(abilityInfo), 0, sizeof(abilityInfo));
    abilityInfo.bundleName = (char*)"com.huawei.testjsdemo";
    printf("abilityInfo.bundleName is %s \n", abilityInfo.bundleName);
    ClearAbilityInfo(nullptr);
    EXPECT_STREQ(abilityInfo.bundleName, "com.huawei.testjsdemo");
    printf("------end testClearAbilityInfoIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_045
 * @tc.name      : ClearAbilityInfo parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testClearBundleInfoIllegal, TestSize.Level2)
{
    printf("------start testClearBundleInfoIllegal------\n");
    BundleInfo bundleInfo;
    memset_s(&bundleInfo, sizeof(bundleInfo), 0, sizeof(bundleInfo));
    bundleInfo.bundleName = (char*)"com.huawei.testjsdemo";
    printf("abilityInfo.bundleName is %s \n", bundleInfo.bundleName);
    ClearBundleInfo(nullptr);
    printf("abilityInfo.bundleName afterclear is %s \n", bundleInfo.bundleName);
    EXPECT_STREQ(bundleInfo.bundleName, "com.huawei.testjsdemo");
    printf("------end testClearBundleInfoIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_046
 * @tc.name      : ClearAbilityInfo parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(BundleMgrTest, testClearModuleInfoIllegal, TestSize.Level1)
{
    printf("------start testClearModuleInfoIllegal------\n");
    ModuleInfo moduleInfo;
    memset_s(&moduleInfo, sizeof(moduleInfo), 0, sizeof(moduleInfo));
    moduleInfo.description = (char*)"test app";
    moduleInfo.moduleType = (char*)"entry";
    printf("mouduleInfo.description  is %s \n", moduleInfo.description);
    printf("mouduleInfo.moduleType  is %s \n", moduleInfo.moduleType);
    ClearModuleInfo(nullptr);
    EXPECT_STREQ(moduleInfo.description, "test app");
    EXPECT_STREQ(moduleInfo.moduleType, "entry");
    printf("------end testClearModuleInfoIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_009
 * @tc.name      : testAbilityMgrSetWantElement parameter legal test
 * @tc.desc      : [C- SOFTWARE -0100]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(BundleMgrTest, testSetElementAbilityName, TestSize.Level0)
{
    printf("------start testSetElementAbilityName------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementAbilityName(&element, "SecondAbility");
    SetWantElement(&want, element);
    printf("element is %s \n", want.element->abilityName);
    char aName[] = "SecondAbility";
    printf("aName is %s \n", aName);
    EXPECT_STREQ(want.element->abilityName, aName);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testSetElementAbilityName------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_010
 * @tc.name      : testSetElementAbilityName parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0100]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 3
 */
HWTEST_F(BundleMgrTest, testSetElementAbilityNameIllegal, TestSize.Level2)
{
    printf("------start testSetElementAbilityNameIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementAbilityName(&element, nullptr);
    SetWantElement(&want, element);
    printf("AbilityName1 is %s \n", want.element->abilityName);
    EXPECT_STREQ(want.element->abilityName, nullptr);
    char aName[] = "";
    SetElementAbilityName(&element, aName);
    SetWantElement(&want, element);
    printf("AbilityName2 is %s \n", want.element->abilityName);
    EXPECT_STREQ(want.element->abilityName, "");
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testSetElementAbilityNameIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_007
 * @tc.name      : testSetElementBundleName parameter legal test
 * @tc.desc      : [C- SOFTWARE -0100]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(BundleMgrTest, testSetElementBundleName, TestSize.Level0)
{
    printf("------start testSetElementBundleName------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "com.huawei.testjsdemo");
    SetWantElement(&want, element);
    printf("element is %s \n", want.element->bundleName);
    char bName[] = "com.huawei.testjsdemo";
    EXPECT_STREQ(want.element->bundleName, bName);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testSetElementBundleName------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_008
 * @tc.name      : testAbilityMgrSetWantElement parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0100]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testSetElementBundleNameIllegal, TestSize.Level2)
{
    printf("------start testSetElementBundleNameIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementBundleName(&element, "");
    SetWantElement(&want, element);
    printf("BundleName1 is %s \n", want.element->bundleName);
    char bName[] = "";
    EXPECT_STREQ(want.element->bundleName, bName);
    SetElementBundleName(&element, nullptr);
    SetWantElement(&want, element);
    printf("BundleName2 is %s \n", want.element->bundleName);
    EXPECT_STREQ(want.element->bundleName, nullptr);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testSetElementBundleNameIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_005
 * @tc.name      : testSetElementDeviceID parameter legal test
 * @tc.desc      : [C- SOFTWARE -0100]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(BundleMgrTest, testSetElementDeviceID, TestSize.Level0)
{
    printf("------start testSetElementDeviceID------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementDeviceID(&element, "0001000");
    SetWantElement(&want, element);
    printf("element is %s \n", want.element->deviceId);
    char dID[] = "0001000";
    EXPECT_STREQ(want.element->deviceId, dID);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testSetElementDeviceID------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_AMS_API_006
 * @tc.name      : testSetElementDeviceID parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0100]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(BundleMgrTest, testSetElementDeviceIDIllegal, TestSize.Level2)
{
    printf("------start testSetElementDeviceIDIllegal------\n");
    Want want = { nullptr };
    ElementName element = { nullptr };
    SetElementDeviceID(&element, "");
    SetWantElement(&want, element);
    printf("element is %s \n", want.element->deviceId);
    char dID[] = "";
    EXPECT_STREQ(want.element->deviceId, dID);
    SetElementDeviceID(&element, nullptr);
    SetWantElement(&want, element);
    printf("element is %s \n", want.element->deviceId);
    EXPECT_STREQ(want.element->deviceId, nullptr);
    ClearElement(&element);
    ClearWant(&want);
    printf("------end testSetElementDeviceIDIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_007
 * @tc.name      : Install parameter illegal test that callback is null
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testInstallWithNullptr, TestSize.Level2)
{
    printf("------start testInstallWithNullptr------\n");
    string hapPath = "/test_root/appexecfwk/testnative.hap";
    bool isInstallSuccess = Install(hapPath.c_str(), nullptr, nullptr);
    EXPECT_FALSE(isInstallSuccess);
    printf("install result is %d \n", isInstallSuccess);
    printf("------end testInstallWithNullptr------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_004
 * @tc.name      : Install parameter illegal test that path is null
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testInstallWithNullPath, TestSize.Level2)
{
    printf("------start testInstallWithNullPath------\n");
    bool isInstallSuccess = Install(nullptr, nullptr, TestBundleStateCallback);
    EXPECT_FALSE(isInstallSuccess);
    printf("install result is %d \n", isInstallSuccess);
    printf("------end testInstallWithNullPath------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_002
 * @tc.name      : Install parameter illegal test that ErrorPath is wrong
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testInstallWithErrorPath, TestSize.Level2)
{
    printf("------start testBundleMgrInstallWithErrorPath------\n");
    string hapPath = "/test_root/appexecfwk/nothishap.hap";
    bool isInstallSuccess = false;
    sem_init(&g_sem, 0, 0);
    bool installResult = Install(hapPath.c_str(), nullptr, TestBundleStateCallback);
    sem_wait(&g_sem);
    if (g_errorCode == 0) {
        isInstallSuccess = true;
    }else if (g_errorCode > 0) {
        isInstallSuccess = false;
        HILOG_DEBUG(HILOG_MODULE_APP, "TestBundleMgrInstall failed,g_errorCode is: %d", g_errorCode);
    }
    EXPECT_FALSE(isInstallSuccess);
    printf("install result is %d", installResult);
    printf("------end testBundleMgrInstallWithErrorPath------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_003
 * @tc.name      : Install parameter illegal test that Path is empty
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testBundleMgrInstallEmpty, TestSize.Level2)
{
    printf("------start testBundleMgrInstallEmpty------\n");
    string hapPath = "";
    bool isInstallSuccess = false;
    sem_init(&g_sem, 0, 0);
    bool installResult = Install(hapPath.c_str(), nullptr, TestBundleStateCallback);
    sem_wait(&g_sem);
    if (g_errorCode == 0) {
        isInstallSuccess = true;
    }else if (g_errorCode > 0) {
        isInstallSuccess = false;
        HILOG_DEBUG(HILOG_MODULE_APP, "TestBundleMgrInstall failed,g_errorCode is: %d", g_errorCode);
    }
    EXPECT_FALSE(isInstallSuccess);
    printf("install result is %d", installResult);
    printf("------end testBundleMgrInstallEmpty------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_009
 * @tc.name      : Install parameter illegal test that file is *.bin
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
HWTEST_F(BundleMgrTest, testBundleMgrInstallBin, TestSize.Level1)
{
    printf("------start testBundleMgrInstallBin------\n");
    string hapPath = "/test_root/appexecfwk/testdemo.bin";
    bool isInstallSuccess = false;
    sem_init(&g_sem, 0, 0);
    bool installResult = Install(hapPath.c_str(), nullptr, TestBundleStateCallback);
    sem_wait(&g_sem);
    if (g_errorCode == 0) {
        isInstallSuccess = true;
    }else if (g_errorCode > 0) {
        isInstallSuccess = false;
        HILOG_DEBUG(HILOG_MODULE_APP, "TestBundleMgrInstall failed,g_errorCode is: %d", g_errorCode);
    }
    EXPECT_FALSE(isInstallSuccess);
    printf("install result is %d", installResult);
    printf("------end testBundleMgrInstallBin------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_014
 * @tc.name      : Uninstall parameter illegal test that callback is null
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testUninstallNullCallback, TestSize.Level2)
{
    printf("------start testUninstallNullCallback------\n");
    const char *bundleName = (char*)"com.huawei.testdemo";
    bool isUninstallSuccess = Uninstall(bundleName, nullptr, nullptr);
    EXPECT_FALSE(isUninstallSuccess);
    printf("uninstall result is %d", isUninstallSuccess);
    printf("------end testUninstallNullCallback------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_013
 * @tc.name      : Uninstall parameter illegal test that bundleName is null
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testUninstallnullBundleName, TestSize.Level2)
{
    printf("------start testUninstallnullBundleName------\n");
    const char *bundleName = (char*)"com.huawei.testnative";
    bool isUninstallSuccess = Uninstall(nullptr, nullptr, TestBundleStateCallback);
    EXPECT_FALSE(isUninstallSuccess);
    printf("uninstall result is %d", isUninstallSuccess);
    printf("------end testUninstallnullBundleName------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_010
 * @tc.name      : Uninstall parameter legal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(BundleMgrTest, testUninstallright, TestSize.Level0)
{
    printf("------start testUninstallright------\n");
    string hapPath = "/test_root/appexecfwk/testnative.hap";
    sem_init(&g_sem, 0, 0);
    bool installResult = Install(hapPath.c_str(), nullptr, TestBundleStateCallback);
    sem_wait(&g_sem);
    EXPECT_TRUE(installResult);
    sleep(1);
    const char *bundleName = (char*)"com.huawei.testnative";
    bool isUninstallSuccess = false;
    sem_init(&g_sem, 0, 0);
    bool uninstallState = Uninstall(bundleName, nullptr, TestBundleStateCallback);
    sem_wait(&g_sem);
    printf("uninstall result is %d", uninstallState);
    if (g_installState) {
        isUninstallSuccess = true;
    }else if (g_errorCode > 0) {
        isUninstallSuccess = false;
        HILOG_DEBUG(HILOG_MODULE_APP, "TestBundleMgrUninstall failed,g_errorCode is: %d", g_errorCode);
    }
    EXPECT_TRUE(uninstallState);
    printf("uninstall result is %d", isUninstallSuccess);
    printf("------end testUninstallright------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_011
 * @tc.name      : Uninstall parameter illegal test that bundleName is wrong
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testUninstallErrorName, TestSize.Level2)
{
    printf("------start testUninstallErrorName------\n");
    const char *bundleName = (char*)"com.huawei.nothisBundleName";
    bool isUninstallSuccess = false;
    sem_init(&g_sem, 0, 0);
    bool uninstallState = Uninstall(bundleName, nullptr, TestBundleStateCallback);
    sem_wait(&g_sem);
    printf("uninstall resute is %d", uninstallState);
    if (g_installState) {
        isUninstallSuccess = true;
    }else if (g_errorCode > 0) {
        isUninstallSuccess = false;
        HILOG_DEBUG(HILOG_MODULE_APP, "TestBundleMgrUninstall failed,g_errorCode is: %d", g_errorCode);
    }
    EXPECT_FALSE(isUninstallSuccess);
    printf("uninstall result is %d", isUninstallSuccess);
    printf("------end testUninstallErrorName------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_012
 * @tc.name      : Uninstall parameter illegal test that bundleName is empty
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testUninstallEmptyName, TestSize.Level2)
{
    printf("------start testUninstallEmptyName------\n");
    const char *bundleName = (char*)"";
    bool isUninstallSuccess = false;
    sem_init(&g_sem, 0, 0);
    bool uninstallState = Uninstall(bundleName, nullptr, TestBundleStateCallback);
    sem_wait(&g_sem);
    printf("uninstall resute is %d", uninstallState);
    if (g_installState) {
        isUninstallSuccess = true;
    }else if (g_errorCode > 0) {
        isUninstallSuccess = false;
        HILOG_DEBUG(HILOG_MODULE_APP, "TestBundleMgrUninstall failed,g_errorCode is: %d", g_errorCode);
    }
    EXPECT_FALSE(isUninstallSuccess);
    printf("uninstall result is %d", isUninstallSuccess);
    printf("------end testUninstallEmptyName------\n");
}


/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_041
 * @tc.name      : QueryAbilityInfo parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testQueryAbilityInfoIllegal, TestSize.Level2)
{
    printf("------start testQueryAbilityInfoIllegal------\n");
    AbilityInfo abilityInfo;
    memset_s(&abilityInfo, sizeof(AbilityInfo), 0, sizeof(AbilityInfo));
    // want is nullptr
    g_errorCode = QueryAbilityInfo(nullptr, &abilityInfo);
    printf("ret is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode == 4);
    // abilityInfo is nullptr
    Want want;
    memset_s(&want, sizeof(Want), 0, sizeof(Want));
    ElementName element;
    memset_s(&element, sizeof(ElementName), 0, sizeof(ElementName));
    SetElementAbilityName(&element, "MainAbility");
    SetElementBundleName(&element, "com.huawei.testjsdemo");
    SetWantElement(&want, element);
    SetWantData(&want, "test", 4);
    g_errorCode = QueryAbilityInfo(&want, nullptr);
    printf("ret is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode == 4);
    // content of want is ""
    Want want1 = { nullptr };
    ElementName element1 = { nullptr };
    SetElementBundleName(&element1, "");
    SetElementAbilityName(&element1, "");
    SetWantElement(&want1, element1);
    AbilityInfo abilityInfo1;
    g_errorCode = QueryAbilityInfo(&want1, &abilityInfo1);
    printf("abilityInfo is null \n");
    printf("ret is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode == 2);
    printf("------end testQueryAbilityInfoIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_030
 * @tc.name      : GetBundleInfo parameter illegal test.
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testGetBundleInfoIllegal, TestSize.Level2)
{
    printf("------start testGetBundleInfoIllegal------\n");
    BundleInfo bundleInfo;
    memset_s(&bundleInfo, sizeof(bundleInfo), 0, sizeof(bundleInfo));
    const char *bundleName = (char*)"com.huawei.nothishap";
    int32_t flags = 0;
    // error bundleName
    g_errorCode = GetBundleInfo(bundleName, flags, &bundleInfo);
    printf("bundleInfo1.bundleName is %s \n", bundleInfo.bundleName);
    printf("bundleInfo1.versionCode is %d \n", bundleInfo.versionCode);
    printf("bundleInfo1.codePath is %s \n", bundleInfo.codePath);
    EXPECT_EQ(g_errorCode, 2);
    // bundleName = nullptr
    g_errorCode = GetBundleInfo(nullptr, flags, &bundleInfo);
    printf("abilityInfo2 is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode == 4);
    printf("bundleInfo2.bundleName is %s \n", bundleInfo.bundleName);
    printf("bundleInfo2.versionCode is %d \n", bundleInfo.versionCode);
    printf("bundleInfo2.codePath is %s \n", bundleInfo.codePath);
    // bunldeName = ""
    g_errorCode = GetBundleInfo("", flags, &bundleInfo);
    printf("bundleInfo3.bundleName is %s \n", bundleInfo.bundleName);
    printf("bundleInfo3.versionCode is %d \n", bundleInfo.versionCode);
    printf("bundleInfo3.codePath is %s \n", bundleInfo.codePath);
    EXPECT_TRUE(g_errorCode == 2);
    // flags not exit
    g_errorCode = GetBundleInfo("com.huawei.testjsdemo", 2, &bundleInfo);
    sleep(2);
    printf("bundleInfo3.bundleName is %s \n", bundleInfo.bundleName);
    printf("bundleInfo3.versionCode is %d \n", bundleInfo.versionCode);
    printf("bundleInfo3.codePath is %s \n", bundleInfo.codePath);
    EXPECT_EQ(g_errorCode, 1);
    printf("------end testGetBundleInfoIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_043
 * @tc.name      : GetBundleInfos parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testGetBundleInfosIllegal, TestSize.Level2)
{
    printf("------start testGetBundleInfosIllegal------\n");
    BundleInfo *bundleInfos = {nullptr};
    int32_t *length = nullptr;
    const char *bundleName = (char*)"com.huawei.nothishap";
    int32_t flags = 0;
    g_errorCode = GetBundleInfos(flags, nullptr, length);
    printf("bundleInfos1 is %x \n", bundleInfos);
    EXPECT_EQ(g_errorCode, 4);
    g_errorCode = GetBundleInfos(flags, &bundleInfos, nullptr);
    printf("g_errorCode is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode == 4);
    printf("bundleInfos2 is %x \n", bundleInfos);
    g_errorCode = GetBundleInfos(2, &bundleInfos, length);
    printf("g_errorCode is %d \n", g_errorCode);
    EXPECT_EQ(g_errorCode, 4);
    printf("------end testGetBundleInfosIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_039
 * @tc.name      : GetBundleInfosByMetaData parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testGetBundleInfosByMetaDataIllegal, TestSize.Level2)
{
    printf("------start testGetBundleInfosByMetaDataIllegal------\n");
    BundleInfo *bundleInfos = {nullptr};
    int32_t length = 0;
    const char *metaDataKey = "appId";
    g_errorCode = GetBundleInfosByMetaData(nullptr, &bundleInfos, &length);
    printf("bundleInfos1 is %x \n", bundleInfos);
    EXPECT_EQ(g_errorCode, 4);
    g_errorCode = GetBundleInfosByMetaData(metaDataKey, &bundleInfos, nullptr);
    printf("g_errorCode is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode == 4);
    printf("bundleInfos2 is %x \n", bundleInfos);
    g_errorCode = GetBundleInfosByMetaData(metaDataKey, nullptr, &length);
    printf("g_errorCode is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode == 4);
    const char *metaDataKey1 = "noThisKey";
    printf("metaDataKey is %s \n", metaDataKey1);
    g_errorCode = GetBundleInfosByMetaData(metaDataKey1, &bundleInfos, &length);
    printf("GetBundleInfosByMetaData result is %d \n", g_errorCode);
    EXPECT_EQ(g_errorCode, 2);
    const char *metaDataKey2 = "";
    g_errorCode = GetBundleInfosByMetaData(metaDataKey2, &bundleInfos, &length);
    printf("GetBundleInfosByMetaData result is %d \n", g_errorCode);
    EXPECT_EQ(g_errorCode, 2);
    printf("------end testGetBundleInfosByMetaDataIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_037
 * @tc.name      : QueryKeepAliveBundleInfos parameter illegal test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testQueryKeepAliveBundleInfosIllegal, TestSize.Level2)
{
    printf("------start testQueryKeepAliveBundleInfosIllegal------\n");
    BundleInfo *bundleInfos = {nullptr};
    int32_t length = 0;
    const char *metaDataKey = "appId";
    g_errorCode = QueryKeepAliveBundleInfos(nullptr, &length);
    printf("g_errorCode1 is %d \n", g_errorCode);
    EXPECT_EQ(g_errorCode, 4);
    g_errorCode = QueryKeepAliveBundleInfos(&bundleInfos, nullptr);
    printf("g_errorCode2 is %d \n", g_errorCode);
    EXPECT_TRUE(g_errorCode == 4);
    printf("------end testQueryKeepAliveBundleInfosIllegal------\n");
}

/**
 * @tc.number    : SUB_APPEXECFWK_BMS_API_034
 * @tc.name      : GetBundleNameForUid parameter nullptr test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
HWTEST_F(BundleMgrTest, testGetBundleNameForUidWithNullptr, TestSize.Level2)
{
    printf("------start testGetBundleNameForUidWithNullptr------\n");
    int32_t resultCode = GetBundleNameForUid(0, nullptr);
    EXPECT_EQ(resultCode, 4);
    printf("GetBundleNameForUid result is %d \n", resultCode);
    printf("------end testGetBundleNameForUidWithNullptr------\n");
}
