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
 * Create      : 2020/04/19
 */

#include <los_base.h>
#include "hctest.h"
#include "samgr_lite.h"

#define OPER_INTERVAL 200    // 200 ms

typedef struct DemoApi {
    INHERIT_IUNKNOWN;
    BOOL (*FeatureApi001)(IUnknown *iUnknown, char *para1);
} DemoApi;

typedef struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
} DemoFeature;

typedef struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
    BOOL (*DefaultApi001)(IUnknown *iUnknown, char *para1);
} DefaultFeatureApi;

typedef struct DemoService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
} DemoService;

static BOOL DefaultApi001(IUnknown *iUnknown,  char *para1)
{
    (void)iUnknown;
    (void)para1;
    return TRUE;
}

static BOOL FeatureApi001(IUnknown *iUnknown,  char *para1)
{
    (void)iUnknown;
    (void)para1;
    return TRUE;
}

static const char *GetName(Service *service)
{
    (void)service;
    return "Service_NoTask";
}

static BOOL Initialize(Service *service, Identity identity)
{
    DemoService *service1 = (DemoService *)service;
    service1->identity = identity;
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
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 0x800, 20, NO_TASK};
    return config;
}

static DemoService g_createService = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
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
    Response response = {
        .data = "Yes, you did!", 
        .len = 0
    };
    SAMGR_SendResponse(request, &response);
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
    },
    .identity = {-1, -1, NULL},
};

static void ServiceInit(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_createService);
    if (result == FALSE) {
        printf("[hctest]E RegisterService failed. \n");
    }
}
SYSEX_SERVICE_INIT(ServiceInit);

static void FeatureInit(void)
{
    BOOL result1 = SAMGR_GetInstance()->RegisterDefaultFeatureApi("Service_NoTask", GET_IUNKNOWN(g_createService));
    
    BOOL result2 = SAMGR_GetInstance()->RegisterFeature("Service_NoTask", (Feature *)&g_createFeature);
    BOOL result3 = SAMGR_GetInstance()->RegisterFeatureApi("Service_NoTask", "featureName501", 
                                                           GET_IUNKNOWN(g_createFeature));
    if (result1 == FALSE || result2 == FALSE || result3 == FALSE) {
        printf("[hctest]E failed to register feature or api.\n");
    }
}
SYSEX_FEATURE_INIT(FeatureInit);

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

static void ReleaseIUnknown(DemoApi *demoApi)
{
    demoApi->Release((IUnknown *)demoApi);
}

LITE_TEST_SUIT(distributedschedule, samgr, TaskPoolNoTaskFuncTestSuite);

static BOOL TaskPoolNoTaskFuncTestSuiteSetUp(void)
{
    LOS_Msleep(OPER_INTERVAL);
    return TRUE;
}

static BOOL TaskPoolNoTaskFuncTestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : DMSLite_SAMGR_Taskpool_NoTask_0010
 * @tc.name      : Service without task can handle direct calls
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(TaskPoolNoTaskFuncTestSuite, testNoTask0010, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("Service_NoTask", "featureName501");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    BOOL result = demoApi->FeatureApi001((IUnknown *)demoApi, "xxxx");
    TEST_ASSERT_EQUAL_INT(result, TRUE);
    ReleaseIUnknown(demoApi);

    DefaultFeatureApi *defaultApi = GetDefaultIUnknown("Service_NoTask");
    if (defaultApi == NULL) {
        TEST_FAIL();
    }
    result = defaultApi->DefaultApi001((IUnknown *)defaultApi, "yyyy");
    TEST_ASSERT_EQUAL_INT(result, TRUE);
};

RUN_TEST_SUITE(TaskPoolNoTaskFuncTestSuite);