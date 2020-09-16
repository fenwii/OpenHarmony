/*
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
 *
 * Description : common function for samgr api test cases
 * Create      : 2020/07/23
 */

#include "SamgrApiTest.h"
#include "gtest/gtest.h"
#include "log.h"
#include <unistd.h>
#include <cstdio>
#include <csignal>
#include <feature.h>
#include <hos_init.h>
#include <samgr_lite.h>
#include <securec.h>

using namespace std;
using namespace testing::ext;

static int g_initIndex = 0;
static int g_coreInit[API_PRI_MAX] = {0};
static int g_sysRun[API_PRI_MAX] = {0};
static int g_sysServiceInit[API_PRI_MAX] = {0};
static int g_sysFeatureInit[API_PRI_MAX] = {0};
static int g_sysExServiceInit[API_PRI_MAX] = {0};
static int g_sysExFeatureInit[API_PRI_MAX] = {0};
static int g_appServiceInit[API_PRI_MAX] = {0};
static int g_appFeatureInit[API_PRI_MAX] = {0};

static void PrintInitIndex(const int initArr[])
{
    for (int i = 0; i < API_PRI_MAX; i++) {
        if (i == API_PRI_DEFAULT) {
            HILOG_INFO(HILOG_MODULE_HIVIEW, "default: %d", initArr[i]);
            continue;
        }
        HILOG_INFO(HILOG_MODULE_HIVIEW, "%d: %d", i, initArr[i]);
    }
}

static void CoreInitDef(void)
{
    g_coreInit[API_PRI_DEFAULT] = g_initIndex++;
}

static void CoreInit0(void)
{
    g_coreInit[API_PRI0] = g_initIndex++;
}
static void CoreInit1(void)
{
    g_coreInit[API_PRI1] = g_initIndex++;
}
static void CoreInit2(void)
{
    g_coreInit[API_PRI2] = g_initIndex++;
}
static void CoreInit3(void)
{
    g_coreInit[API_PRI3] = g_initIndex++;
}
static void CoreInit4(void)
{
    g_coreInit[API_PRI4] = g_initIndex++;
}

static void SysRunDef(void)
{
    g_sysRun[API_PRI_DEFAULT] = g_initIndex++;
}
static void SysRun0(void)
{
    g_sysRun[API_PRI0] = g_initIndex++;
}
static void SysRun1(void)
{
    g_sysRun[API_PRI1] = g_initIndex++;
}
static void SysRun2(void)
{
    g_sysRun[API_PRI2] = g_initIndex++;
}
static void SysRun3(void)
{
    g_sysRun[API_PRI3] = g_initIndex++;
}
static void SysRun4(void)
{
    g_sysRun[API_PRI4] = g_initIndex++;
}

static void SysServiceInitDef(void)
{
    g_sysServiceInit[API_PRI_DEFAULT] = g_initIndex++;
}
static void SysServiceInit0(void)
{
    g_sysServiceInit[API_PRI0] = g_initIndex++;
}
static void SysServiceInit1(void)
{
    g_sysServiceInit[API_PRI1] = g_initIndex++;
}
static void SysServiceInit2(void)
{
    g_sysServiceInit[API_PRI2] = g_initIndex++;
}
static void SysServiceInit3(void)
{
    g_sysServiceInit[API_PRI3] = g_initIndex++;
}
static void SysServiceInit4(void)
{
    g_sysServiceInit[API_PRI4] = g_initIndex++;
}

static void SysFeatureInitDef(void)
{
    g_sysFeatureInit[API_PRI_DEFAULT] = g_initIndex++;
}
static void SysFeatureInit0(void)
{
    g_sysFeatureInit[API_PRI0] = g_initIndex++;
}
static void SysFeatureInit1(void)
{
    g_sysFeatureInit[API_PRI1] = g_initIndex++;
}
static void SysFeatureInit2(void)
{
    g_sysFeatureInit[API_PRI2] = g_initIndex++;
}
static void SysFeatureInit3(void)
{
    g_sysFeatureInit[API_PRI3] = g_initIndex++;
}
static void SysFeatureInit4(void)
{
    g_sysFeatureInit[API_PRI4] = g_initIndex++;
}

static void SysExSerInitDef(void)
{
    g_sysExServiceInit[API_PRI_DEFAULT] = g_initIndex++;
}
static void SysExSerInit0(void)
{
    g_sysExServiceInit[API_PRI0] = g_initIndex++;
}
static void SysExSerInit1(void)
{
    g_sysExServiceInit[API_PRI1] = g_initIndex++;
}
static void SysExSerInit2(void)
{
    g_sysExServiceInit[API_PRI2] = g_initIndex++;
}
static void SysExSerInit3(void)
{
    g_sysExServiceInit[API_PRI3] = g_initIndex++;
}
static void SysExSerInit4(void)
{
    g_sysExServiceInit[API_PRI4] = g_initIndex++;
}

static void SysExFeaInitDef(void)
{
    g_sysExFeatureInit[API_PRI_DEFAULT] = g_initIndex++;
}
static void SysExFeaInit0(void)
{
    g_sysExFeatureInit[API_PRI0] = g_initIndex++;
}
static void SysExFeaInit1(void)
{
    g_sysExFeatureInit[API_PRI1] = g_initIndex++;
}
static void SysExFeaInit2(void)
{
    g_sysExFeatureInit[API_PRI2] = g_initIndex++;
}
static void SysExFeaInit3(void)
{
    g_sysExFeatureInit[API_PRI3] = g_initIndex++;
}
static void SysExFeaInit4(void)
{
    g_sysExFeatureInit[API_PRI4] = g_initIndex++;
}

static void AppServiceInitDef(void)
{
    g_appServiceInit[API_PRI_DEFAULT] = g_initIndex++;
}
static void AppServiceInit0(void)
{
    g_appServiceInit[API_PRI0] = g_initIndex++;
}
static void AppServiceInit1(void)
{
    g_appServiceInit[API_PRI1] = g_initIndex++;
}
static void AppServiceInit2(void)
{
    g_appServiceInit[API_PRI2] = g_initIndex++;
}
static void AppServiceInit3(void)
{
    g_appServiceInit[API_PRI3] = g_initIndex++;
}
static void AppServiceInit4(void)
{
    g_appServiceInit[API_PRI4] = g_initIndex++;
}

static void AppFeatureInitDef(void)
{
    g_appFeatureInit[API_PRI_DEFAULT] = g_initIndex++;
}
static void AppFeatureInit0(void)
{
    g_appFeatureInit[API_PRI0] = g_initIndex++;
}
static void AppFeatureInit1(void)
{
    g_appFeatureInit[API_PRI1] = g_initIndex++;
}
static void AppFeatureInit2(void)
{
    g_appFeatureInit[API_PRI2] = g_initIndex++;
}
static void AppFeatureInit3(void)
{
    g_appFeatureInit[API_PRI3] = g_initIndex++;
}
static void AppFeatureInit4(void)
{
    g_appFeatureInit[API_PRI4] = g_initIndex++;
}

// 接口注册后的启动顺序依赖hos_init.h中的定义的数字大小

// 第0个执行，内部按照0~4优先级执行，default优先级为2
CORE_INIT(CoreInitDef);
CORE_INIT_PRI(CoreInit0, 0);
CORE_INIT_PRI(CoreInit1, 1);
CORE_INIT_PRI(CoreInit4, 4);
CORE_INIT_PRI(CoreInit2, 2);
CORE_INIT_PRI(CoreInit3, 3);

// 最后一个执行，内部按照0~4优先级执行，default优先级为2
SYS_RUN(SysRunDef);
SYS_RUN_PRI(SysRun0, 0);
SYS_RUN_PRI(SysRun1, 1);
SYS_RUN_PRI(SysRun4, 4);
SYS_RUN_PRI(SysRun2, 2);
SYS_RUN_PRI(SysRun3, 3);

// 第1个执行，内部按照0~4优先级执行，default优先级为2
SYS_SERVICE_INIT(SysServiceInitDef);
SYS_SERVICE_INIT_PRI(SysServiceInit0, 0);
SYS_SERVICE_INIT_PRI(SysServiceInit1, 1);
SYS_SERVICE_INIT_PRI(SysServiceInit4, 4);
SYS_SERVICE_INIT_PRI(SysServiceInit2, 2);
SYS_SERVICE_INIT_PRI(SysServiceInit3, 3);

// 第2个执行，内部按照0~4优先级执行，default优先级为2
SYS_FEATURE_INIT(SysFeatureInitDef);
SYS_FEATURE_INIT_PRI(SysFeatureInit0, 0);
SYS_FEATURE_INIT_PRI(SysFeatureInit2, 2);
SYS_FEATURE_INIT_PRI(SysFeatureInit1, 1);
SYS_FEATURE_INIT_PRI(SysFeatureInit3, 3);
SYS_FEATURE_INIT_PRI(SysFeatureInit4, 4);

// 第3个执行，注意和APP_SERVICE_INIT_XXX并列，谁先注册先执行谁，内部按照0~4优先级执行，default优先级为2
SYSEX_SERVICE_INIT(SysExSerInitDef);
SYSEX_SERVICE_INIT_PRI(SysExSerInit0, 0);
SYSEX_SERVICE_INIT_PRI(SysExSerInit1, 1);
SYSEX_SERVICE_INIT_PRI(SysExSerInit2, 2);
SYSEX_SERVICE_INIT_PRI(SysExSerInit3, 3);
SYSEX_SERVICE_INIT_PRI(SysExSerInit4, 4);

// 第4个执行，注意和APP_FEATURE_INIT_XXX并列，谁先注册先执行谁，内部按照0~4优先级执行，default优先级为2
SYSEX_FEATURE_INIT(SysExFeaInitDef);
SYSEX_FEATURE_INIT_PRI(SysExFeaInit0, 0);
SYSEX_FEATURE_INIT_PRI(SysExFeaInit1, 1);
SYSEX_FEATURE_INIT_PRI(SysExFeaInit2, 2);
SYSEX_FEATURE_INIT_PRI(SysExFeaInit3, 3);
SYSEX_FEATURE_INIT_PRI(SysExFeaInit4, 4);

// 第3个执行，注意和SYSEX_SERVICE_INIT_XXX并列，谁先注册先执行谁，内部按照0~4优先级执行，default优先级为2
APP_SERVICE_INIT(AppServiceInitDef);
APP_SERVICE_INIT_PRI(AppServiceInit0, 0);
APP_SERVICE_INIT_PRI(AppServiceInit4, 4);
APP_SERVICE_INIT_PRI(AppServiceInit3, 3);
APP_SERVICE_INIT_PRI(AppServiceInit2, 2);
APP_SERVICE_INIT_PRI(AppServiceInit1, 1);

// 第4个执行，注意和SYSEX_FEATURE_INIT_XXX并列，谁先注册先执行谁，内部按照0~4优先级执行，default优先级为2
APP_FEATURE_INIT(AppFeatureInitDef);
APP_FEATURE_INIT_PRI(AppFeatureInit0, 0);
APP_FEATURE_INIT_PRI(AppFeatureInit1, 1);
APP_FEATURE_INIT_PRI(AppFeatureInit3, 3);
APP_FEATURE_INIT_PRI(AppFeatureInit4, 4);
APP_FEATURE_INIT_PRI(AppFeatureInit2, 2);

class SamgrApiTest : public testing::Test {
protected:
    static void SetUpTestCase(void) {}
    static void TearDownTestCase(void) {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

/**
 * @tc.number    : SUB_START_Bootstrap_Samgr_0100 
 * @tc.name      : check total init index
 * @tc.desc      : check total init index, return success
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(SamgrApiTest, SUB_START_Bootstrap_Samgr_0100, TestSize.Level0)
{
    HILOG_INFO(HILOG_MODULE_HIVIEW, "[SUB_START_Bootstrap_Samgr_0100:%d]", g_initIndex);
    EXPECT_EQ(g_initIndex, SAMGR_API_GROUP_NUM*SAMGR_API_CALL_NUM);
}

/**
 * @tc.number    : SUB_START_Bootstrap_Samgr_0200 
 * @tc.name      : check core init index
 * @tc.desc      : check core init, return success
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(SamgrApiTest, SUB_START_Bootstrap_Samgr_0200, TestSize.Level0)
{
    HILOG_INFO(HILOG_MODULE_HIVIEW, "g_coreInit");
    PrintInitIndex(g_coreInit);
    EXPECT_EQ(g_coreInit[API_PRI0], GET_INIT_INDEX(CORE_INIT_E, API_PRI0));
    EXPECT_EQ(g_coreInit[API_PRI1], GET_INIT_INDEX(CORE_INIT_E, API_PRI1));
    EXPECT_EQ(g_coreInit[API_PRI_DEFAULT], GET_INIT_INDEX(CORE_INIT_E, API_PRI_DEFAULT));
    EXPECT_EQ(g_coreInit[API_PRI2], GET_INIT_INDEX(CORE_INIT_E, API_PRI2));
    EXPECT_EQ(g_coreInit[API_PRI3], GET_INIT_INDEX(CORE_INIT_E, API_PRI3));
    EXPECT_EQ(g_coreInit[API_PRI4], GET_INIT_INDEX(CORE_INIT_E, API_PRI4));
}

/**
 * @tc.number    : SUB_START_Bootstrap_Samgr_0300 
 * @tc.name      : check system service init index
 * @tc.desc      : check system service init, return success
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(SamgrApiTest, SUB_START_Bootstrap_Samgr_0300, TestSize.Level0)
{
    HILOG_INFO(HILOG_MODULE_HIVIEW, "g_sysServiceInit");
    PrintInitIndex(g_sysServiceInit);
    EXPECT_EQ(g_sysServiceInit[API_PRI0], GET_INIT_INDEX(SYS_SERVICE_INIT_E, API_PRI0));
    EXPECT_EQ(g_sysServiceInit[API_PRI1], GET_INIT_INDEX(SYS_SERVICE_INIT_E, API_PRI1));
    EXPECT_EQ(g_sysServiceInit[API_PRI_DEFAULT], GET_INIT_INDEX(SYS_SERVICE_INIT_E, API_PRI_DEFAULT));
    EXPECT_EQ(g_sysServiceInit[API_PRI2], GET_INIT_INDEX(SYS_SERVICE_INIT_E, API_PRI2));
    EXPECT_EQ(g_sysServiceInit[API_PRI3], GET_INIT_INDEX(SYS_SERVICE_INIT_E, API_PRI3));
    EXPECT_EQ(g_sysServiceInit[API_PRI4], GET_INIT_INDEX(SYS_SERVICE_INIT_E, API_PRI4));
}

/**
 * @tc.number    : SUB_START_Bootstrap_Samgr_0400 
 * @tc.name      : check system feature init index
 * @tc.desc      : check system feature init, return success
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(SamgrApiTest, SUB_START_Bootstrap_Samgr_0400, TestSize.Level0)
{
    HILOG_INFO(HILOG_MODULE_HIVIEW, "g_sysFeatureInit");
    PrintInitIndex(g_sysFeatureInit);
    EXPECT_EQ(g_sysFeatureInit[API_PRI0], GET_INIT_INDEX(SYS_FEATURE_INIT_E, API_PRI0));
    EXPECT_EQ(g_sysFeatureInit[API_PRI1], GET_INIT_INDEX(SYS_FEATURE_INIT_E, API_PRI1));
    EXPECT_EQ(g_sysFeatureInit[API_PRI_DEFAULT], GET_INIT_INDEX(SYS_FEATURE_INIT_E, API_PRI_DEFAULT));
    EXPECT_EQ(g_sysFeatureInit[API_PRI2], GET_INIT_INDEX(SYS_FEATURE_INIT_E, API_PRI2));
    EXPECT_EQ(g_sysFeatureInit[API_PRI3], GET_INIT_INDEX(SYS_FEATURE_INIT_E, API_PRI3));
    EXPECT_EQ(g_sysFeatureInit[API_PRI4], GET_INIT_INDEX(SYS_FEATURE_INIT_E, API_PRI4));
}

/**
 * @tc.number    : SUB_START_Bootstrap_Samgr_0500 
 * @tc.name      : check system extend service and app service init index
 * @tc.desc      : check system extend service and app service init, return success
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(SamgrApiTest, SUB_START_Bootstrap_Samgr_0500, TestSize.Level0)
{
    HILOG_INFO(HILOG_MODULE_HIVIEW, "g_sysExServiceInit");
    PrintInitIndex(g_sysExServiceInit);
    HILOG_INFO(HILOG_MODULE_HIVIEW, "g_appServiceInit");
    PrintInitIndex(g_appServiceInit);
    EXPECT_EQ(g_sysExServiceInit[API_PRI0], GET_INIT_INDEX(APP_SERVICE_INIT_E, 0));
    EXPECT_EQ(g_appServiceInit[API_PRI0], GET_INIT_INDEX(APP_SERVICE_INIT_E, 1));
    EXPECT_EQ(g_sysExServiceInit[API_PRI1], GET_INIT_INDEX(APP_SERVICE_INIT_E, 2));
    EXPECT_EQ(g_appServiceInit[API_PRI1], GET_INIT_INDEX(APP_SERVICE_INIT_E, 3));
    EXPECT_EQ(g_sysExServiceInit[API_PRI_DEFAULT], GET_INIT_INDEX(APP_SERVICE_INIT_E, 4));
    EXPECT_EQ(g_sysExServiceInit[API_PRI2], GET_INIT_INDEX(APP_SERVICE_INIT_E, 5));
    EXPECT_EQ(g_appServiceInit[API_PRI_DEFAULT], GET_INIT_INDEX(APP_SERVICE_INIT_E, 6));
    EXPECT_EQ(g_appServiceInit[API_PRI2], GET_INIT_INDEX(APP_SERVICE_INIT_E, 7));
    EXPECT_EQ(g_sysExServiceInit[API_PRI3], GET_INIT_INDEX(APP_SERVICE_INIT_E, 8));
    EXPECT_EQ(g_appServiceInit[API_PRI3], GET_INIT_INDEX(APP_SERVICE_INIT_E, 9));
    EXPECT_EQ(g_sysExServiceInit[API_PRI4], GET_INIT_INDEX(APP_SERVICE_INIT_E, 10));
    EXPECT_EQ(g_appServiceInit[API_PRI4], GET_INIT_INDEX(APP_SERVICE_INIT_E, 11));
}

/**
 * @tc.number    : SUB_START_Bootstrap_Samgr_0600 
 * @tc.name      : check system extend feature and app feature init index
 * @tc.desc      : check system extend feature and app feature init, return success
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(SamgrApiTest, SUB_START_Bootstrap_Samgr_0600, TestSize.Level0)
{
    HILOG_INFO(HILOG_MODULE_HIVIEW, "g_sysExFeatureInit");
    PrintInitIndex(g_sysExFeatureInit);
    HILOG_INFO(HILOG_MODULE_HIVIEW, "g_appFeatureInit");
    PrintInitIndex(g_appFeatureInit);
    EXPECT_EQ(g_sysExFeatureInit[API_PRI0], GET_INIT_INDEX(APP_FEATURE_INIT_E, 0));
    EXPECT_EQ(g_appFeatureInit[API_PRI0], GET_INIT_INDEX(APP_FEATURE_INIT_E, 1));
    EXPECT_EQ(g_sysExFeatureInit[API_PRI1], GET_INIT_INDEX(APP_FEATURE_INIT_E, 2));
    EXPECT_EQ(g_appFeatureInit[API_PRI1], GET_INIT_INDEX(APP_FEATURE_INIT_E, 3));
    EXPECT_EQ(g_sysExFeatureInit[API_PRI_DEFAULT], GET_INIT_INDEX(APP_FEATURE_INIT_E, 4));
    EXPECT_EQ(g_sysExFeatureInit[API_PRI2], GET_INIT_INDEX(APP_FEATURE_INIT_E, 5));
    EXPECT_EQ(g_appFeatureInit[API_PRI_DEFAULT], GET_INIT_INDEX(APP_FEATURE_INIT_E, 6));
    EXPECT_EQ(g_appFeatureInit[API_PRI2], GET_INIT_INDEX(APP_FEATURE_INIT_E, 7));
    EXPECT_EQ(g_sysExFeatureInit[API_PRI3], GET_INIT_INDEX(APP_FEATURE_INIT_E, 8));
    EXPECT_EQ(g_appFeatureInit[API_PRI3], GET_INIT_INDEX(APP_FEATURE_INIT_E, 9));
    EXPECT_EQ(g_sysExFeatureInit[API_PRI4], GET_INIT_INDEX(APP_FEATURE_INIT_E, 10));
    EXPECT_EQ(g_appFeatureInit[API_PRI4], GET_INIT_INDEX(APP_FEATURE_INIT_E, 11));
}

/**
 * @tc.number    : SUB_START_Bootstrap_Samgr_0700 
 * @tc.name      : check system run index
 * @tc.desc      : check system run, return success
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(SamgrApiTest, SUB_START_Bootstrap_Samgr_0700, TestSize.Level0)
{
    HILOG_INFO(HILOG_MODULE_HIVIEW, "g_sysRun");
    PrintInitIndex(g_sysRun);
    EXPECT_EQ(g_sysRun[API_PRI0], GET_INIT_INDEX(SYS_RUN_E, API_PRI0));
    EXPECT_EQ(g_sysRun[API_PRI1], GET_INIT_INDEX(SYS_RUN_E, API_PRI1));
    EXPECT_EQ(g_sysRun[API_PRI_DEFAULT], GET_INIT_INDEX(SYS_RUN_E, API_PRI_DEFAULT));
    EXPECT_EQ(g_sysRun[API_PRI2], GET_INIT_INDEX(SYS_RUN_E, API_PRI2));
    EXPECT_EQ(g_sysRun[API_PRI3], GET_INIT_INDEX(SYS_RUN_E, API_PRI3));
    EXPECT_EQ(g_sysRun[API_PRI4], GET_INIT_INDEX(SYS_RUN_E, API_PRI4));
}
