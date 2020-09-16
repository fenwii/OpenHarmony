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

#include "gtest/gtest.h"
#include "utils/SamgrTestBase.h"

using namespace testing::ext;

struct DemoApi {
    INHERIT_IUNKNOWN;
};

struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
};

struct ExampleService {
    INHERIT_SERVICE;
    Identity identity;
};

static const char *GetName(Service *service)
{
    (void)service;
    return "serviceName201";
}

static BOOL Initialize(Service *service, Identity identity)
{
    ExampleService *example = (ExampleService *)service;
    example->identity = identity;
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    (void)msg;
    (void)service;
    return FALSE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {
        LEVEL_HIGH, 
        PRI_ABOVE_NORMAL,
        0x800, 
        20, 
        SHARED_TASK
        };
    return config;
}

static ExampleService g_service = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    .identity = {-1, -1, nullptr},
};

static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return "featureName201";
}
static const char *FEATURE_GetName2(Feature *feature)
{
    (void)feature;
    return "featureName202";
}
static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->identity = identity;
    (void)parent;
}
static void FEATURE_OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
}

static BOOL FEATURE_OnMessage(Feature *feature, Request *request)
{
    (void)feature;
    (void)request;
    return TRUE;
}

static DemoFeature g_feature = {
    .GetName = FEATURE_GetName,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage,
    .ver = 0,
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
    },
    .identity = {-1, -1, nullptr},
};

static DemoFeature g_feature2 = {
    .GetName = FEATURE_GetName2,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage,
    .ver = 0,
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
    },
    .identity = {-1, -1, nullptr},
};

class FeatureTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
        SystemInitProxy();
    }
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void)
    {
    }
    // Testcase setup
    virtual void SetUp()
    {
        BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
        if (result != TRUE) {
            printf("[hcpptest]E failed to register service. \n");
        }
    }
    // Testcase teardown
    virtual void TearDown()
    {
        SAMGR_GetInstance()->UnregisterService("serviceName201");
    }
};

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeature_0010
 * @tc.name      : Valid feature can be registered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testRegisterFeature0010, TestSize.Level1) {
    BOOL result = SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);
    ASSERT_EQ(result, TRUE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeature_0020
 * @tc.name      : If the specified service is null feature can not be registered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testRegisterFeature0020, TestSize.Level2) {
    BOOL result = SAMGR_GetInstance()->RegisterFeature(NULL, (Feature *)&g_feature);
    ASSERT_EQ(result, FALSE);
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeature_0030
 * @tc.name      : If the specified feature is null feature can not be registered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testRegisterFeature0030, TestSize.Level2) {
    BOOL result = SAMGR_GetInstance()->RegisterFeature("serviceName201", nullptr);
    ASSERT_EQ(result, FALSE);
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeature_0040
 * @tc.name      : Feature can not be registered if the specified service does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testRegisterFeature0040, TestSize.Level2) {
    BOOL result = SAMGR_GetInstance()->RegisterFeature("noExistServiceName", (Feature *)&g_feature);
    ASSERT_EQ(result, FALSE);
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeature_0050
 * @tc.name      : Feature failed to register if the same feature name already exist in samgr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testRegisterFeature0050, TestSize.Level2) {
    SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);

    BOOL result = SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);
    ASSERT_EQ(result, FALSE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeature_0060
 * @tc.name      : Multi features can be registered under one service
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testRegisterFeature0060, TestSize.Level2) {
    BOOL result1 = SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);
    ASSERT_EQ(result1, TRUE);
    BOOL result2 = SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature2);
    ASSERT_EQ(result2, TRUE);
    
    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName202");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeature_0010
 * @tc.name      : Feature can be unregistered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testUnregisterFeature0010, TestSize.Level2) {
    SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);

    Feature *resultFeature = SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
    ASSERT_EQ(strcmp(resultFeature->GetName(resultFeature), "featureName201"), 0);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeature_0020
 * @tc.name      : Feature can not be unregistered if the specified service is null or space
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testUnregisterFeature0020, TestSize.Level2) {
    SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);

    Feature *resultFeature = SAMGR_GetInstance()->UnregisterFeature(NULL, "featureName201");
    ASSERT_EQ(resultFeature == nullptr, TRUE);

    resultFeature = SAMGR_GetInstance()->UnregisterFeature("", "featureName201");
    ASSERT_EQ(resultFeature == nullptr, TRUE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeature_0030
 * @tc.name      : Feature can not be unregistered if the specified feature is null or space
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testUnregisterFeature0030, TestSize.Level2) {
    SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);

    Feature *resultFeature = SAMGR_GetInstance()->UnregisterFeature("serviceName201", nullptr);
    ASSERT_EQ(resultFeature == nullptr, TRUE);

    resultFeature = SAMGR_GetInstance()->UnregisterFeature("serviceName201", "");
    ASSERT_EQ(resultFeature == nullptr, TRUE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeature_0040
 * @tc.name      : Feature failed to unregister if the specified service not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testUnregisterFeature0040, TestSize.Level2) {
    SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);

    Feature *resultFeature = SAMGR_GetInstance()->UnregisterFeature("noExistService", "featureName201");
    ASSERT_EQ(resultFeature == nullptr, TRUE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeature_0050
 * @tc.name      : Feature failed to unregister if the specified feature not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testUnregisterFeature0050, TestSize.Level2) {
    SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);

    Feature *resultFeature = SAMGR_GetInstance()->UnregisterFeature("serviceName201", "noExistFeature");
    ASSERT_EQ(resultFeature == nullptr, TRUE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeature_0060
 * @tc.name      : Feature failed to unregister if there is api under the feature
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testUnregisterFeature0060, TestSize.Level2) {
    SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName201", "featureName201", GET_IUNKNOWN(g_feature));

    Feature *result = SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
    ASSERT_EQ(result == nullptr, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName201", "featureName201");
    SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeature_0070
 * @tc.name      : Register and unregister feature repeatedly, no memory leak
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(FeatureTest, testUnregisterFeature0070, TestSize.Level2) {
    // RegisterService and unregister feature over and over again, if there is memory leak samgr will crash
    for (int i = 0; i < PRESSURE_BASE; i++) {
        BOOL result = SAMGR_GetInstance()->RegisterFeature("serviceName201", (Feature *)&g_feature);
        ASSERT_EQ(result, TRUE);

        Feature *resultFeature = SAMGR_GetInstance()->UnregisterFeature("serviceName201", "featureName201");
        ASSERT_EQ(resultFeature != nullptr, TRUE);
    }
}