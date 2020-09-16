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

const int TARGET_NUM = 2;

using namespace testing::ext;

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetTaskConfig(Service *service);

static pthread_t g_servicePoint1;
static pthread_t g_servicePoint2;

struct DemoApi {
    INHERIT_IUNKNOWN;
    BOOL(*FeatureApi001)
    (IUnknown *iUnknown, char *para1);
    int32 (*SendRequestProxyF)(const Identity *identity, const Request *request, Handler handler);
};

struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
    int featureCalledCount;
};

struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
    BOOL(*DefaultApi001)
    (IUnknown *iUnknown, char *para1);
    int32 (*SendRequestProxyDF)(const Identity *identity, const Request *request, Handler handler);
};

struct DemoService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
    int serviceCalledCount;
};

static BOOL DefaultApi001(IUnknown *iUnknown, char *para1)
{
    (void)iUnknown;
    return TRUE;
}
static int32 SendRequestProxyDF(const Identity *identity, const Request *request, Handler handler)
{
    return SAMGR_SendRequest(identity, request, handler);
}

static BOOL FeatureApi001(IUnknown *iUnknown, char *para1)
{
    (void)iUnknown;
    return TRUE;
}
static int32 SendRequestProxyF(const Identity *identity, const Request *request, Handler handler)
{
    return SAMGR_SendRequest(identity, request, handler);
}

static DemoService g_createService[] = {
    {
        .GetName = GetName,
        .Initialize = Initialize,
        .MessageHandle = MessageHandle,
        .GetTaskConfig = GetTaskConfig,
        .ver = 0x20,
        .ref = 1,
        .iUnknown = {
            DEFAULT_IUNKNOWN_IMPL,
            .DefaultApi001 = DefaultApi001,
            .SendRequestProxyDF = SendRequestProxyDF,
        },
        .identity = {-1, -1, nullptr},
        .serviceCalledCount = 0,
    },
    {
        .GetName = GetName,
        .Initialize = Initialize,
        .MessageHandle = MessageHandle,
        .GetTaskConfig = GetTaskConfig,
        .ver = 0x20,
        .ref = 1,
        .iUnknown = {
            DEFAULT_IUNKNOWN_IMPL,
            .DefaultApi001 = DefaultApi001,
            .SendRequestProxyDF = SendRequestProxyDF,
        },
        .identity = {-1, -1, nullptr},
        .serviceCalledCount = 0,
    }
};

static const char *GetName(Service *service)
{
    if (service == (Service *)&g_createService[0]) {
        return "SpecifiedT01";
    } else {
        return "SpecifiedT02";
    }
}

static BOOL Initialize(Service *service, Identity identity)
{
    DemoService *demoService = (DemoService *)service;
    demoService->identity = identity;
    
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    DemoService *demoService = (DemoService *)service;
    demoService->serviceCalledCount++;

    if (service == (Service *)&g_createService[0]) {
        g_servicePoint1 = pthread_self();
    } else {
        g_servicePoint2 = pthread_self();
    }
    
    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 1600, 20, SPECIFIED_TASK};
    return config;
}

static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return "featureName501";
}

static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->identity = identity;
}

static void FEATURE_OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
}

static BOOL FEATURE_OnMessage(Feature *feature, Request *request)
{
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;

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
        .SendRequestProxyF = SendRequestProxyF,
    },
    .identity = {-1, -1, nullptr},
    .featureCalledCount = 0,
};

static void GServiceInit(void)
{
    for (int i = 0; i < TARGET_NUM; i++) {
        SAMGR_GetInstance()->RegisterService((Service *)&g_createService[i]);
    }
}
SYS_SERVICE_INIT(GServiceInit);

static void GFeatureInit(void)
{
    for (int i = 0; i < TARGET_NUM; i++) {
        SAMGR_GetInstance()->RegisterDefaultFeatureApi(g_createService[i].GetName((Service *)&g_createService[i]),
                                                       GET_IUNKNOWN(g_createService[i]));

        SAMGR_GetInstance()->RegisterFeature(g_createService[i].GetName((Service *)&g_createService[i]),
                                             (Feature *)&g_createFeature);
        SAMGR_GetInstance()->RegisterFeatureApi(g_createService[i].GetName((Service *)&g_createService[i]),
                                                "featureName501", GET_IUNKNOWN(g_createFeature));
    }
}
SYS_FEATURE_INIT(GFeatureInit);

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

class TaskpoolSpecifiedTaskTest : public testing::Test {
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
 * @tc.number    : SUB_DSS_samgrLite_taskpool_0010
 * @tc.name      : the first task function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolSpecifiedTaskTest, testTaskPool0010, TestSize.Level2)
{
    DemoApi *demoApi = GetIUnknown("SpecifiedT01", "featureName501");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, (char*)"xxxx");
    ASSERT_EQ(result, TRUE);

    g_createFeature.featureCalledCount = 0;
    Request request = {.msgId = 0, .len = 0, .data = nullptr, .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = (uint32_t)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        ADD_FAILURE();
    }
    int32 result2 = demoApi->SendRequestProxyF(&(g_createFeature.identity), &request, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_createFeature.featureCalledCount == 1, TRUE);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SpecifiedT01");
    if (defaultApi == nullptr) {
        ADD_FAILURE();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, (char*)"yyyy");
    ASSERT_EQ(result, TRUE);

    g_createService[0].serviceCalledCount = 0;
    Request request2 = {.msgId = 0, .len = 0, .data = nullptr, .msgValue = 0};
    char *body2 = (char*)"I want to call defaultFeature!";
    request2.len = (uint32_t)(strlen(body2) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == nullptr) {
        ADD_FAILURE();
    }
    error = strcpy_s((char *)request2.data, request2.len, body2);
    if (error != EOK) {
        ADD_FAILURE();
    }
    result2 = defaultApi->SendRequestProxyDF(&(g_createService[0].identity), &request2, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_createService[0].serviceCalledCount == 1, TRUE);
};

/**
 * @tc.number    : SUB_DSS_samgrLite_taskpool_0020
 * @tc.name      : PRI_LOW function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolSpecifiedTaskTest, testTaskPool0020, TestSize.Level2)
{
    DemoApi *demoApi = GetIUnknown("SpecifiedT02", "featureName501");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, (char*)"xxxx");
    ASSERT_EQ(result, TRUE);

    g_createFeature.featureCalledCount = 0;
    Request request = {.msgId = 0, .len = 0, .data = nullptr, .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = (uint32_t)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        ADD_FAILURE();
    }
    int32 result2 = demoApi->SendRequestProxyF(&(g_createFeature.identity), &request, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_createFeature.featureCalledCount == 1, TRUE);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SpecifiedT02");
    if (defaultApi == nullptr) {
        ADD_FAILURE();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, (char*)"yyyy");
    ASSERT_EQ(result, TRUE);

    g_createService[0].serviceCalledCount = 0;
    Request request2 = {.msgId = 0, .len = 0, .data = nullptr, .msgValue = 0};
    char *body2 = (char*)"I want to call defaultFeature!";
    request2.len = (uint32_t)(strlen(body2) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == nullptr) {
        ADD_FAILURE();
    }
    error = strcpy_s((char *)request2.data, request2.len, body2);
    if (error != EOK) {
        ADD_FAILURE();
    }
    result2 = defaultApi->SendRequestProxyDF(&(g_createService[0].identity), &request2, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_createService[0].serviceCalledCount == 1, TRUE);
};

/**
 * @tc.number    : SUB_DSS_samgrLite_taskpool_0030
 * @tc.name      : PRI_LOW function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolSpecifiedTaskTest, testTaskPool0030, TestSize.Level2)
{
    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SpecifiedT01");
    if (defaultApi == nullptr) {
        ADD_FAILURE();
    }
    Request request = {.msgId = 0, .len = 0, .data = nullptr, .msgValue = 0};
    char *body = (char*)"I want to call defaultFeature!";
    request.len = (uint32_t)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        ADD_FAILURE();
    }
    defaultApi->SendRequestProxyDF(&(g_createService[0].identity), &request, nullptr);

    DefaultFeatureApi *defaultApi2 = GetDefaultIUnknown("SpecifiedT01");
    if (defaultApi2 == nullptr) {
        ADD_FAILURE();
    }
    Request request2 = {.msgId = 0, .len = 0, .data = nullptr, .msgValue = 0};
    char *body2 = (char*)"I want to call defaultFeature!";
    request2.len = (uint32_t)(strlen(body2) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == nullptr) {
        ADD_FAILURE();
    }
    error = strcpy_s((char *)request2.data, request2.len, body2);
    if (error != EOK) {
        ADD_FAILURE();
    }
    defaultApi2->SendRequestProxyDF(&(g_createService[1].identity), &request2, nullptr);

    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_servicePoint1 == g_servicePoint2, TRUE);
};