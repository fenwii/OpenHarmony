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

#include <stdlib.h>
#include <string.h>
#include <los_base.h>
#include "securec.h"
#include "hctest.h"
#include "samgr_lite.h"

#define OPER_INTERVAL 200 // 200 ms
#define SERVICE_NUM 4
#define INDEX0 0
#define INDEX1 1
#define INDEX2 2
#define INDEX3 3

static char *g_serviceNameArray[] = {"SingleTS01", "SingleTS02", "SingleTS03", "SingleTS04"};

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetTaskConfig(Service *service);

static Vector g_nodeVector;
typedef struct Node {
    int id;
    const char *name;
} Node;
static const Node *GetNode(const Node *node)
{
    return node;
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

typedef struct DemoApi {
    INHERIT_IUNKNOWN;
    BOOL (*FeatureApi001)(IUnknown *iUnknown, char *para1);
    int32 (*SendRequestProxyF)(const Identity *identity, const Request *request, Handler handler);
} DemoApi;

typedef struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
    int featureCalledCount;
} DemoFeature;

typedef struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
    BOOL (*DefaultApi001)(IUnknown *iUnknown, char *para1);
    int32 (*SendRequestProxyDF)(const Identity *identity, const Request *request, Handler handler);
} DefaultFeatureApi;

typedef struct DemoService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
    int serviceCalledCount;
} DemoService;

static BOOL DefaultApi001(IUnknown *iUnknown, char *para1)
{
    (void)iUnknown;
    (void)para1;
    return TRUE;
}
static int32 SendRequestProxyDF(const Identity *identity, const Request *request, Handler handler)
{
    return SAMGR_SendRequest(identity, request, handler);
}

static BOOL FeatureApi001(IUnknown *iUnknown, char *para1)
{
    (void)iUnknown;
    (void)para1;
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
        .ref = 1,
        .iUnknown = {
            DEFAULT_IUNKNOWN_IMPL,
            .DefaultApi001 = DefaultApi001,
            .SendRequestProxyDF = SendRequestProxyDF,
        },
        .serviceCalledCount = 0,
    },
    {
        .GetName = GetName,
        .Initialize = Initialize,
        .MessageHandle = MessageHandle,
        .GetTaskConfig = GetTaskConfig,
        .ref = 1,
        .iUnknown = {
            DEFAULT_IUNKNOWN_IMPL,
            .DefaultApi001 = DefaultApi001,
            .SendRequestProxyDF = SendRequestProxyDF,
        },
        .serviceCalledCount = 0,
    },
    {
        .GetName = GetName,
        .Initialize = Initialize,
        .MessageHandle = MessageHandle,
        .GetTaskConfig = GetTaskConfig,
        .ref = 1,
        .iUnknown = {
            DEFAULT_IUNKNOWN_IMPL,
            .DefaultApi001 = DefaultApi001,
            .SendRequestProxyDF = SendRequestProxyDF,
        },
        .serviceCalledCount = 0,
    },
    {
        .GetName = GetName,
        .Initialize = Initialize,
        .MessageHandle = MessageHandle,
        .GetTaskConfig = GetTaskConfig,
        .ref = 1,
        .iUnknown = {
            DEFAULT_IUNKNOWN_IMPL,
            .DefaultApi001 = DefaultApi001,
            .SendRequestProxyDF = SendRequestProxyDF,
        },
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
    if (node == NULL) {
        TEST_FAIL();
    }
    node->id = g_initlizationOrder;
    node->name = service->GetName(service);
    VECTOR_Add(&g_nodeVector, node);
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    (void)msg;
    DemoService *demoService = (DemoService *)service;
    demoService->serviceCalledCount++;
    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    // stackSize: valid stackSize is [1600, 342000), the L0 RAM size is 342000, if stackSize <= 800, system will crash
    // queueSize: [0, system upper limit), 0: will not create taskpool, the max value depends on RAM size
    // priority: PRI_ABOVE_NORMAL PRI_NORMAL PRI_BELOW_NORMAL PRI_LOW

    TaskConfig config = { LEVEL_HIGH, PRI_NORMAL, 1600, 2, SINGLE_TASK };
    if (service == (Service *)&g_service[INDEX0]) {
        config.priority = PRI_LOW;
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
    (void)parent;
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
    (void)request;
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;

    return TRUE;
}

static DemoFeature g_createFeature = {
    .GetName = FEATURE_GetName,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage,
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .FeatureApi001 = FeatureApi001,
        .SendRequestProxyF = SendRequestProxyF,
    },
    .identity = {-1, -1, NULL},
    .featureCalledCount = 0,
};

static void ServiceInit(void)
{
    g_nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    for (int i = 0; i < SERVICE_NUM; i++) {
        BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service[i]);
        if (result == FALSE) {
            printf("[hctest]E RegisterService failed, occurs: %d\n", i);
        }
    }
}
SYS_SERVICE_INIT(ServiceInit);

static void FeatureInit(void)
{
    for (int i = 0; i < SERVICE_NUM; i++) {
        BOOL result1 = SAMGR_GetInstance()->RegisterDefaultFeatureApi(g_service[i].GetName((Service *)&g_service[i]),
            GET_IUNKNOWN(g_service[i]));
        BOOL result2 = SAMGR_GetInstance()->RegisterFeature(g_service[i].GetName((Service *)&g_service[i]), 
                                                            (Feature *)&g_createFeature);
        BOOL result3 = SAMGR_GetInstance()->RegisterFeatureApi(g_service[i].GetName((Service *)&g_service[i]), 
                                                               "featureName501", GET_IUNKNOWN(g_createFeature));
        if (result1 == FALSE || result2 == FALSE || result3 == FALSE) {
            printf("[hctest]E failed to register feature or api.\n");
        }
    }
}
SYS_FEATURE_INIT(FeatureInit);

static DemoApi *GetIUnknown(const char *serviceName, const char *featureName)
{
    DemoApi *demoApi = NULL;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(serviceName, featureName);
    if (iUnknown == NULL) {
        printf("[hctest]failed to GetFeatureApi.\n");
        return NULL;
    }
    int result = iUnknown->QueryInterface(iUnknown, 0, (void **)&demoApi);
    if (result == 0 && demoApi != NULL) {
        return demoApi;
    } else {
        printf("[hctest]failed to QueryInterface.\n");
        return NULL;
    }
}

static DefaultFeatureApi *GetDefaultIUnknown(const char *serviceName)
{
    DefaultFeatureApi *defaultApi = NULL;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(serviceName);
    if (iUnknown == NULL) {
        printf("[hctest]failed to GetFeatureApi.\n");
        return NULL;
    }
    int result = iUnknown->QueryInterface(iUnknown, 0, (void **)&defaultApi);
    if (result == 0 && defaultApi != NULL) {
        return defaultApi;
    } else {
        printf("[hctest]failed to QueryInterface.\n");
        return NULL;
    }
}

LITE_TEST_SUIT(distributedschedule, samgr, SingleTaskFuncTestSuite);

static BOOL SingleTaskFuncTestSuiteSetUp(void)
{
    LOS_Msleep(OPER_INTERVAL);
    return TRUE;
}

static BOOL SingleTaskFuncTestSuiteTearDown(void)
{
    return TRUE;
}

/* *
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0010
 * @tc.name      : Service with PRI_LOW priority function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SingleTaskFuncTestSuite, testSingleTask0010, LEVEL2)
{
    // test featureApi function
    DemoApi *demoApi = GetIUnknown("SingleTS01", "featureName501");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, "xxxx");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    g_createFeature.featureCalledCount = 0;
    Request request = {
        .msgId = 0,
        .msgValue = 0
    };
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);
    int32 result2 = demoApi->SendRequestProxyF(&(g_createFeature.identity), &request, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_createFeature.featureCalledCount == 1, TRUE);

    // test defaultFeatureApi function
    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SingleTS01");
    if (defaultApi == NULL) {
        TEST_FAIL();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, "yyyy");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    Request request2 = {
        .msgId = 0,
        .msgValue = 0
    };
    char *body2 = "I want to call defaultFeature!";
    request2.len = (int16)(strlen(body2) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request2.data, request2.len, body2);
    result2 = defaultApi->SendRequestProxyDF(&(g_service[0].identity), &request2, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_service[0].serviceCalledCount == 1, TRUE);
};

/* *
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0020
 * @tc.name      : Service with PRI_BELOW_NORMAL priority function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SingleTaskFuncTestSuite, testSingleTask0020, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("SingleTS02", "featureName501");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, "xxxx");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    g_createFeature.featureCalledCount = 0;
    Request request = {
        .msgId = 0,
        .msgValue = 0
    };
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);
    int32 result2 = demoApi->SendRequestProxyF(&(g_createFeature.identity), &request, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_createFeature.featureCalledCount == 1, TRUE);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SingleTS02");
    if (defaultApi == NULL) {
        TEST_FAIL();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, "yyyy");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    Request request2 = {
        .msgId = 0,
        .msgValue = 0
    };
    char *body2 = "I want to call defaultFeature!";
    request2.len = (int16)(strlen(body2) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request2.data, request2.len, body2);
    result2 = defaultApi->SendRequestProxyDF(&(g_service[1].identity), &request2, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_service[1].serviceCalledCount == 1, TRUE);
};

/* *
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0030
 * @tc.name      : Service with PRI_NORMAL priority function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SingleTaskFuncTestSuite, testSingleTask0030, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("SingleTS03", "featureName501");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, "xxxx");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    g_createFeature.featureCalledCount = 0;
    Request request = {
        .msgId = 0,
        .msgValue = 0
    };
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);
    int32 result2 = demoApi->SendRequestProxyF(&(g_createFeature.identity), &request, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_createFeature.featureCalledCount == 1, TRUE);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SingleTS03");
    if (defaultApi == NULL) {
        TEST_FAIL();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, "yyyy");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    Request request2 = {
        .msgId = 0,
        .msgValue = 0
    };
    char *body2 = "I want to call defaultFeature!";
    request2.len = (int16)(strlen(body2) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request2.data, request2.len, body2);
    result2 = defaultApi->SendRequestProxyDF(&(g_service[INDEX2].identity), &request2, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_service[INDEX2].serviceCalledCount == 1, TRUE);
};

/* *
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0040
 * @tc.name      : Service with PRI_ABOVE_NORMAL priority function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SingleTaskFuncTestSuite, testSingleTask0040, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("SingleTS04", "featureName501");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, "xxxx");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    g_createFeature.featureCalledCount = 0;
    Request request = {
        .msgId = 0,
        .msgValue = 0
    };
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);
    int32 result2 = demoApi->SendRequestProxyF(&(g_createFeature.identity), &request, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_createFeature.featureCalledCount == 1, TRUE);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SingleTS04");
    if (defaultApi == NULL) {
        TEST_FAIL();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, "yyyy");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    Request request2 = {
        .msgId = 0,
        .msgValue = 0
    };
    char *body2 = "I want to call defaultFeature!";
    request2.len = (int16)(strlen(body2) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request2.data, request2.len, body2);
    result2 = defaultApi->SendRequestProxyDF(&(g_service[INDEX3].identity), &request2, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_service[INDEX3].serviceCalledCount == 1, TRUE);
};

/* *
 * @tc.number    : DMSLite_SAMGR_Taskpool_SingleTask_0050
 * @tc.name      : Service initialization order depends on service priority
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SingleTaskFuncTestSuite, testSingleTask0050, LEVEL2)
{
    for (int i = 0; i < VECTOR_Num(&g_nodeVector); i++) {
        Node *vectorAt = (Node *)VECTOR_At(&g_nodeVector, i);
        if (vectorAt == NULL) {
            continue;
        }
        TEST_ASSERT_EQUAL_INT(vectorAt->id, i + 1);
        TEST_ASSERT_EQUAL_INT(strcmp(vectorAt->name, g_serviceNameArray[SERVICE_NUM - (i + 1)]), 0);
    }
};

RUN_TEST_SUITE(SingleTaskFuncTestSuite);