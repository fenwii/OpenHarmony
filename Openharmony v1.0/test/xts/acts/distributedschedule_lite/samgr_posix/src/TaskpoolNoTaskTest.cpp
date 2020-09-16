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

#include <securec.h>
#include <hos_init.h>
#include "gtest/gtest.h"
#include "utils/SamgrTestBase.h"


using namespace testing::ext;

struct DemoApi {
    INHERIT_IUNKNOWN;
    BOOL (*FeatureApi001)(IUnknown *iUnknown, char *para1);
};

struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
};

struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
    BOOL (*DefaultApi001)(IUnknown *iUnknown, char *para1);
};

struct DemoService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
};

static BOOL DefaultApi001(IUnknown *iUnknown,  char *para1)
{
    (void)iUnknown;
    return TRUE;
}

static BOOL FeatureApi001(IUnknown *iUnknown,  char *para1)
{
    (void)iUnknown;
    return TRUE;
}

static const char *GetName(Service *service)
{
    (void)service;
    return "Service_NoTask";
}

static BOOL Initialize(Service *service, Identity identity)
{
    DemoService *demoService = (DemoService *)service;
    demoService->identity = identity;
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    (void)service;
    (void)msg;
    return FALSE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {LEVEL_HIGH, PRI_ABOVE_NORMAL, 0x800, 20, NO_TASK};
    return config;
}

static DemoService g_createService = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    .ver = 0x20,
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .DefaultApi001 = DefaultApi001,
    }
};

static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return "featureName501";
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
    char *dataR = (char*)"Yes, you did!";
    Response response = {
        .data = dataR, 
        .len = 0,
    };
    SAMGR_SendResponse(request, &response);
    return TRUE;
}

static DemoFeature g_createFeature = {
    .GetName = FEATURE_GetName,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage,
    .ver = 0x20,
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .FeatureApi001 = FeatureApi001,
    },
    .identity = {-1, -1, nullptr},
};

static void GServiceInit(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_createService);
    if (result != TRUE) {
        printf("[hcpptest]error RegisterService failed");
    }
}
SYSEX_SERVICE_INIT(GServiceInit);

static void GFeatureInit(void)
{
    BOOL result1 = SAMGR_GetInstance()->RegisterDefaultFeatureApi("Service_NoTask", 
                                                                  GET_IUNKNOWN(g_createService));
    BOOL result2 = SAMGR_GetInstance()->RegisterFeature("Service_NoTask", (Feature *)&g_createFeature);
    BOOL result3 = SAMGR_GetInstance()->RegisterFeatureApi("Service_NoTask", "featureName501", 
                                                           GET_IUNKNOWN(g_createFeature));
    if (result1 != TRUE || result2 != TRUE || result3 != TRUE) {
        printf("[hcpptest]error register feature or api fail <%d, %d, %d> \n", result1, result2, result3);
    }
}
SYSEX_FEATURE_INIT(GFeatureInit);

static DemoApi *GetIUnknown(const char *serviceName, const char *featureName)
{
    DemoApi *demoApi = nullptr;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(serviceName, featureName);
    if (iUnknown == nullptr) {
        return nullptr;
    }
    int result = iUnknown->QueryInterface(iUnknown, 0x20, (void **)&demoApi);
    if (result == 0 && demoApi != nullptr) {
        return demoApi;
    } else {
        return nullptr;
    }
}

static DefaultFeatureApi *GetDefaultIUnknown(const char *serviceName)
{
    DefaultFeatureApi *defaultApi = nullptr;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(serviceName);
    if (iUnknown == nullptr) {
        return nullptr;
    }
    int result = iUnknown->QueryInterface(iUnknown, 0x20, (void **)&defaultApi);
    if (result == 0 && defaultApi != nullptr) {
        return defaultApi;
    } else {
        return nullptr;
    }
}

static void ReleaseIUnknown(DemoApi *demoApi)
{
    demoApi->Release((IUnknown *)demoApi);
}

class TaskpoolNoTaskTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
        printf("[hcpptest]SetUpTestCase ! \n");
        SystemInitProxy();
    }
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void)
    {
    }
    // Testcase setup
    virtual void SetUp()
    {
        usleep(OPER_INTERVAL * MS2US);
    }
    // Testcase teardown
    virtual void TearDown()
    {
    }
};

/**
 * @tc.number    : DMSLite_SAMGR_Taskpool_NoTask_0010
 * @tc.name      : Service without task can handle direct calls
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolNoTaskTest, testNoTask0010, TestSize.Level2)
{
    DemoApi *demoApi = GetIUnknown("Service_NoTask", "featureName501");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }

    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, (char*)"xxxx");
    ASSERT_EQ(result, TRUE);
    ReleaseIUnknown(demoApi);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("Service_NoTask");
    if (defaultApi == nullptr) {
        ADD_FAILURE();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, (char*)"yyyy");
    ASSERT_EQ(result, TRUE);
};