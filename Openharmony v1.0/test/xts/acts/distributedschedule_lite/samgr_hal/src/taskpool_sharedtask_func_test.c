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
 *
 * Description : testcases for distributedschedule_lite subsystem
 * Create      : 2020/05/16
 */

#include <stdlib.h>
#include <los_base.h>
#include "securec.h"
#include "cmsis_os2.h"
#include "hctest.h"
#include "samgr_lite.h"

#define OPER_INTERVAL 200  // 200ms
#define TARGET_NUM 2

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetTaskConfig(Service *service);

static const char *FEATURE_GetName(Feature *feature);
static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity);
static void FEATURE_OnStop(Feature *feature, Identity identity);
static BOOL FEATURE_OnMessage(Feature *feature, Request *request);

static void *g_threadID11;  // for the first service threadID
static void *g_threadID12;  // for the first feature threadID
static void *g_threadID21;  // for the second service threadID
static void *g_threadID22;  // for the second feature threadID

typedef struct DemoApi {
    INHERIT_IUNKNOWN;
    BOOL(*FeatureApi001)
    (IUnknown *iUnknown, char *para1);
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
    BOOL(*DefaultApi001)
    (IUnknown *iUnknown, char *para1);
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
    }
};

static const char *GetName(Service *service)
{
    if (service == (Service *)&g_service[0]) {
        return "SharedTask01";
    } else {
        return "SharedTask02";
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
    (void)msg;
    DemoService *demoService = (DemoService *)service;
    demoService->serviceCalledCount++;
    if (service == (Service *)&g_service[0]) {
        g_threadID11 =  osThreadGetId();
    } else {
        g_threadID21 =  osThreadGetId();
    }
    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 1600, 20, SHARED_TASK};
    if (service == (Service *)&g_service[0]) {
        config.priority = PRI_NORMAL;
    } else {
        config.priority = PRI_NORMAL + 1;
    }
    return config;
}

static DemoFeature g_createFeature[] = {
    {
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
    },
    {
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
    },
};

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
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;

    printf("[hctest]FEATURE_OnMessage request msgId is %d \n", request->msgId);
    if (feature == (Feature *)&g_createFeature[0]) {
        g_threadID12 =  osThreadGetId();
    } else {
        g_threadID22 =  osThreadGetId();
    }
    return TRUE;
}

static void ServiceInit(void)
{
    for (int i = 0; i < TARGET_NUM; i++) {
        SAMGR_GetInstance()->RegisterService((Service *)&g_service[i]);
    }
}
SYS_SERVICE_INIT(ServiceInit);

static void FeatureInit(void)
{
    for (int i = 0; i < TARGET_NUM; i++) {
        SAMGR_GetInstance()->RegisterDefaultFeatureApi(g_service[i].GetName((Service *)&g_service[i]),
                                                       GET_IUNKNOWN(g_service[i]));

        SAMGR_GetInstance()->RegisterFeature(g_service[i].GetName((Service *)&g_service[i]),
                                             (Feature *)&g_createFeature[i]);
        SAMGR_GetInstance()->RegisterFeatureApi(g_service[i].GetName((Service *)&g_service[i]), "featureName501",
                                                GET_IUNKNOWN(g_createFeature[i]));
    }
}
SYS_FEATURE_INIT(FeatureInit);

static DemoApi *GetIUnknown(const char *serviceName, const char *featureName)
{
    DemoApi *demoApi = NULL;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(serviceName, featureName);
    if (iUnknown == NULL) {
        return NULL;
    }
    int result = iUnknown->QueryInterface(iUnknown, 0, (void **)&demoApi);
    if (result == 0 && demoApi != NULL) {
        return demoApi;
    } else {
        return NULL;
    }
}

static DefaultFeatureApi *GetDefaultIUnknown(const char *serviceName)
{
    DefaultFeatureApi *defaultApi = NULL;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(serviceName);
    if (iUnknown == NULL) {
        return NULL;
    }
    int result = iUnknown->QueryInterface(iUnknown, 0, (void **)&defaultApi);
    if (result == 0 && defaultApi != NULL) {
        return defaultApi;
    } else {
        return NULL;
    }
}

LITE_TEST_SUIT(distributedschedule, taskpool, ShareTaskFuncTestSuite);

static BOOL ShareTaskFuncTestSuiteSetUp(void)
{
    LOS_Msleep(OPER_INTERVAL);
    return TRUE;
}

static BOOL ShareTaskFuncTestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : SUB_DSS_samgrLite_sharedtask_0010
 * @tc.name      : the first task function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ShareTaskFuncTestSuite, testSharedTask0010, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("SharedTask01", "featureName501");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, "xxxx");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    g_createFeature[0].featureCalledCount = 0;
    Request request = {.msgId = 0, .msgValue = 0};
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);
    int32 result2 = demoApi->SendRequestProxyF(&(g_createFeature[0].identity), &request, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_createFeature[0].featureCalledCount == 1, TRUE);

    // *************************** //
    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SharedTask01");
    if (defaultApi == NULL) {
        TEST_FAIL();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, "yyyy");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    g_service[0].serviceCalledCount = 0;
    Request request2 = {.msgId = 0, .msgValue = 0};
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

/**
 * @tc.number    : SUB_DSS_samgrLite_sharedtask_0020
 * @tc.name      : the second task function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ShareTaskFuncTestSuite, testSharedTask0020, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("SharedTask02", "featureName501");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, "xxxx");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    g_createFeature[1].featureCalledCount = 0;
    Request request = {.msgId = 0, .msgValue = 0};
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);
    int32 result2 = demoApi->SendRequestProxyF(&(g_createFeature[1].identity), &request, NULL);
    TEST_ASSERT_EQUAL_INT(result2 == 0, TRUE);
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_createFeature[1].featureCalledCount == 1, TRUE);

    // *************************** //
    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SharedTask02");
    if (defaultApi == NULL) {
        TEST_FAIL();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, "yyyy");
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    g_service[1].serviceCalledCount = 0;
    Request request2 = {.msgId = 0, .msgValue = 0};
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

/**
 * @tc.number    : SUB_DSS_samgrLite_sharedtask_0030
 * @tc.name      : PRI_LOW function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ShareTaskFuncTestSuite, testSharedTask0030, LEVEL2)
{
    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("SharedTask01");
    if (defaultApi == NULL) {
        TEST_FAIL();
    }
    Request request = {.msgId = 0, .msgValue = 0};
    char *body = "I want to call defaultFeature!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);
    defaultApi->SendRequestProxyDF(&(g_service[0].identity), &request, NULL);

    DefaultFeatureApi *defaultApi2 = GetDefaultIUnknown("SharedTask01");
    if (defaultApi2 == NULL) {
        TEST_FAIL();
    }
    Request request2 = {.msgId = 0, .msgValue = 0};
    request2.len = (int16)(strlen(body) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request2.data, request2.len, body);
    defaultApi2->SendRequestProxyDF(&(g_service[1].identity), &request2, NULL);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_threadID11 == g_threadID21, TRUE);
};

/**
 * @tc.number    : SUB_DSS_samgrLite_sharedtask_0040
 * @tc.name      : PRI_LOW function is ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ShareTaskFuncTestSuite, testSharedTask0040, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("SharedTask01", "featureName501");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    Request request1 = {.msgId = 1, .msgValue = 0};
    char *body = "I wanna async call good result!";
    request1.len = (int16)(strlen(body) + 1);
    request1.data = malloc(request1.len);
    if (request1.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request1.data, request1.len, body);
    demoApi->SendRequestProxyF(&(g_createFeature[0].identity), &request1, NULL);

    DemoApi *demoApi2 = GetIUnknown("SharedTask02", "featureName501");
    if (demoApi2 == NULL) {
        TEST_FAIL();
    }
    Request request2 = {.msgId = 1 + 1, .msgValue = 0};
    request2.len = (int16)(strlen(body) + 1);
    request2.data = malloc(request2.len);
    if (request2.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request2.data, request2.len, body);
    demoApi2->SendRequestProxyF(&(g_createFeature[1].identity), &request2, NULL);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(g_threadID12 == g_threadID22, TRUE);
};
RUN_TEST_SUITE(ShareTaskFuncTestSuite);