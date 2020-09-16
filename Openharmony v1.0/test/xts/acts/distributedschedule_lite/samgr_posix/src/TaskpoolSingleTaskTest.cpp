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

const int SERVICE_NUM = 4;

const int INDEX0 = 0;
const int INDEX1 = 1;
const int INDEX2 = 2;
const int INDEX3 = 3;

static char *g_serviceNameArray[] = {
    (char*)"SingleTS01",
    (char*)"SingleTS02",
    (char*)"SingleTS03",
    (char*)"SingleTS04"
};

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetTaskConfig(Service *service);

static Vector g_nodeVector;
struct Node {
    int id;
    char *name;
};
static Node *GetNode(const Node *node)
{
    return const_cast<Node*>(node);
}
static int CompareNode(const Node *node1, const Node *node2)
{
    if (node1->id < node2->id) {
        return -1;
    } else if (node1->id == node2->id) {
        return 0;
    } else {
        return 1;
    }
}

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

static DemoService g_service[] = {
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
    if (service == (Service *)&g_service[INDEX0]) {
        return g_serviceNameArray[INDEX0];
    } else if (service == (Service *)&g_service[INDEX1]) {
        return g_serviceNameArray[INDEX1];
    } else if (service == (Service *)&g_service[INDEX2]) {
        return g_serviceNameArray[INDEX2];
    } else {
        return g_serviceNameArray[INDEX3];
    }
}

static int g_initlizationOrder = 0;
static BOOL Initialize(Service *service, Identity identity)
{
    DemoService *demoService = (DemoService *)service;
    demoService->identity = identity;

    g_initlizationOrder++;
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == nullptr) {
        ADD_FAILURE();
    }
    node->id = g_initlizationOrder;
    node->name = (char *)service->GetName(service);
    VECTOR_Add(&g_nodeVector, node);
    
    printf("[hcpptest]serviceName %s priority %d Initialize \n", service->GetName(service), 
           service->GetTaskConfig(service).priority);

    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    DemoService *demoService = (DemoService *)service;
    demoService->serviceCalledCount++;
    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    // stackSize: valid stackSize is [1600, 342000), the L0 RAM size is 342000, if stackSize = 800, system will crash
    // queueSize: [0, system upper limit), 0: will not create taskpool, the max value depends on RAM size
    // priority: PRI_ABOVE_NORMAL PRI_NORMAL PRI_BELOW_NORMAL PRI_LOW

    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 1600, 2, SINGLE_TASK};
    if (service == (Service *)&g_service[INDEX0]) {
        config.priority = PRI_LOW + 1;
    } else if (service == (Service *)&g_service[INDEX1]) {
        config.priority = PRI_BELOW_NORMAL;
    } else if (service == (Service *)&g_service[INDEX2]) {
        config.priority = PRI_NORMAL;
    } else {
        config.priority = PRI_ABOVE_NORMAL;
    }
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

static DemoFeature g_feature = {
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
    for (int i = 0; i < SERVICE_NUM; i++) {
        BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service[i]);
        if (result == FALSE) {
            printf("[hcpptest]E RegisterService failed, occurs: %d\n", i);
        }
    }
}
SYS_SERVICE_INIT(GServiceInit);

static void GFeatureInit(void)
{
    for (int i = 0; i < SERVICE_NUM; i++) {
        BOOL result1 = SAMGR_GetInstance()->RegisterDefaultFeatureApi(g_service[i].GetName((Service *)&g_service[i]),
                                                                      GET_IUNKNOWN(g_service[i]));
        BOOL result2 = SAMGR_GetInstance()->RegisterFeature(g_service[i].GetName((Service *)&g_service[i]),
                                                            (Feature *)&g_feature);
        BOOL result3 = SAMGR_GetInstance()->RegisterFeatureApi(g_service[i].GetName((Service *)&g_service[i]),
                                                               "featureName501", GET_IUNKNOWN(g_feature));
        if (result1 == FALSE || result2 == FALSE || result3 == FALSE) {
            printf("[hcpptest]E failed to register feature or api.\n");
        }
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

class TaskpoolSingleTaskTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
        printf("[hcpptest]SetUpTestCase ! \n");
        SystemInitProxy();
        usleep(OPER_INTERVAL * MS2US);
    }
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void)
    {
    }
    // Testcase setup
    virtual void SetUp()
    {
    }
    // Testcase teardown
    virtual void TearDown()
    {
    }
};

/**
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0010
 * @tc.name      : Service with PRI_LOW priority function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolSingleTaskTest, testSingleTask0010, TestSize.Level2)
{
    // test featureApi function
    DemoApi *demoApi = GetIUnknown("SingleTS01", "featureName501");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    char *para = (char*)"xxxx";
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, para);
    ASSERT_EQ(result, TRUE);

    g_feature.featureCalledCount = 0;
    Request request = {.msgId = 0, 
                        .len = 0,
                       .data = nullptr,
                       .msgValue = 0};
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
    int32 result2 = demoApi->SendRequestProxyF(&(g_feature.identity), &request, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_feature.featureCalledCount == 1, TRUE);

    // test defaultFeatureApi function
    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SingleTS01");
    if (defaultApi == nullptr) {
        ADD_FAILURE();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, (char*)"yyyy");
    ASSERT_EQ(result, TRUE);

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
    result2 = defaultApi->SendRequestProxyDF(&(g_service[0].identity), &request2, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_service[0].serviceCalledCount == 1, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0020
 * @tc.name      : Service with PRI_BELOW_NORMAL priority function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolSingleTaskTest, testSingleTask0020, TestSize.Level2)
{
    DemoApi *demoApi = GetIUnknown("SingleTS02", "featureName501");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, (char*)"xxxx");
    ASSERT_EQ(result, TRUE);

    g_feature.featureCalledCount = 0;
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
    int32 result2 = demoApi->SendRequestProxyF(&(g_feature.identity), &request, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_feature.featureCalledCount == 1, TRUE);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SingleTS02");
    if (defaultApi == nullptr) {
        ADD_FAILURE();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, (char*)"yyyy");
    ASSERT_EQ(result, TRUE);

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
    result2 = defaultApi->SendRequestProxyDF(&(g_service[1].identity), &request2, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_service[1].serviceCalledCount == 1, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0030
 * @tc.name      : Service with PRI_NORMAL priority function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolSingleTaskTest, testSingleTask0030, TestSize.Level2)
{
    DemoApi *demoApi = GetIUnknown("SingleTS03", "featureName501");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, (char*)"xxxx");
    ASSERT_EQ(result, TRUE);

    g_feature.featureCalledCount = 0;
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
    int32 result2 = demoApi->SendRequestProxyF(&(g_feature.identity), &request, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_feature.featureCalledCount == 1, TRUE);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SingleTS03");
    if (defaultApi == nullptr) {
        ADD_FAILURE();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, (char*)"yyyy");
    ASSERT_EQ(result, TRUE);

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
    result2 = defaultApi->SendRequestProxyDF(&(g_service[INDEX2].identity), &request2, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_service[INDEX2].serviceCalledCount == 1, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0040
 * @tc.name      : Service with PRI_ABOVE_NORMAL priority function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolSingleTaskTest, testSingleTask0040, TestSize.Level2)
{
    DemoApi *demoApi = GetIUnknown("SingleTS04", "featureName501");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, (char*)"xxxx");
    ASSERT_EQ(result, TRUE);

    g_feature.featureCalledCount = 0;
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
    int32 result2 = demoApi->SendRequestProxyF(&(g_feature.identity), &request, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_feature.featureCalledCount == 1, TRUE);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SingleTS04");
    if (defaultApi == nullptr) {
        ADD_FAILURE();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, (char*)"yyyy");
    ASSERT_EQ(result, TRUE);

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
    result2 = defaultApi->SendRequestProxyDF(&(g_service[INDEX3].identity), &request2, nullptr);
    ASSERT_EQ(result2 == 0, TRUE);
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(g_service[INDEX3].serviceCalledCount == 1, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0050
 * @tc.name      : Service initialization order depends on service priority
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(TaskpoolSingleTaskTest, testSingleTask0050, TestSize.Level2)
{
    for (int i = 0; i < VECTOR_Num(&g_nodeVector); i++) {
        Node *node = (Node *)VECTOR_At(&g_nodeVector, i);
        if (node == NULL) {
            continue;
        }
        printf("[hcpptest]vector: service %s, serviceArray: %s \n", node->name,
                g_serviceNameArray[SERVICE_NUM - (i + 1)]);
        ASSERT_EQ(node->id, i + 1);
        ASSERT_EQ(strcmp(node->name, g_serviceNameArray[SERVICE_NUM - (i + 1)]), 0);
    }
};