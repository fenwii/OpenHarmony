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

#include <string.h>
#include <los_base.h>
#include "hctest.h"
#include "samgr_lite.h"

#define OPER_INTERVAL 200    // 200 ms
#define PRESSURE_BASE (1024 * 10)

typedef struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
} DefaultFeatureApi;

typedef struct ExampleService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
} ExampleService;

typedef struct DemoApi {
    INHERIT_IUNKNOWN;
} DemoApi;

typedef struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
} DemoFeature;

static const char *GetName(Service *service)
{
    (void)service;
    return "serviceName101";
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
    TaskConfig config = {LEVEL_HIGH, PRI_ABOVE_NORMAL, 0x800, 20, SHARED_TASK};
    return config;
}

static ExampleService g_service = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
    }
};

static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return "featureName101";
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
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
    },
    .identity = {-1, -1, NULL},
};

LITE_TEST_SUIT(test, samgr, ServiceTestSuite);

static BOOL ServiceTestSuiteSetUp(void)
{
    LOS_Msleep(OPER_INTERVAL);
    return TRUE;
}

static BOOL ServiceTestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterService_0010
 * @tc.name      : Valid service can be registered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(ServiceTestSuite, testRegisterService0010, LEVEL1)
{
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    TEST_ASSERT_EQUAL_INT(result, TRUE);  // TRUE: regist success; FALSE: regist fail

    SAMGR_GetInstance()->UnregisterService("serviceName101");
};

/**
 * @tc.number    : DMSLite_SAMGR_RegisterService_0020
 * @tc.name      : Service which is NULL failed to register 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testRegisterService0020, LEVEL2)
{
    BOOL result = SAMGR_GetInstance()->RegisterService(NULL);
    TEST_ASSERT_EQUAL_INT(result, FALSE);
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterService_0030
 * @tc.name      : Service which already exist in samgr failed to register 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testRegisterService0030, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    TEST_ASSERT_EQUAL_INT(result, FALSE);
    SAMGR_GetInstance()->UnregisterService("serviceName101");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterService_0010
 * @tc.name      : Service can be unregistered 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testUnregisterService0010, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    Service *resultService = SAMGR_GetInstance()->UnregisterService("serviceName101");

    // when unregist service samgr will return the target service
    TEST_ASSERT_EQUAL_INT(strcmp(resultService->GetName(resultService), "serviceName101"), 0);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterService_0020
 * @tc.name      : Service which contains NULL failed to unregister
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testUnregisterService0020, LEVEL2)
{
    Service *resultService = SAMGR_GetInstance()->UnregisterService(NULL);
    TEST_ASSERT_EQUAL_INT(resultService == NULL, TRUE);

    resultService = SAMGR_GetInstance()->UnregisterService("");
    TEST_ASSERT_EQUAL_INT(resultService == NULL, TRUE);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterService_0030
 * @tc.name      : Service which does not exist in samgr failed to unregister
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testUnregisterService0030, LEVEL2)
{
    Service *resultService = SAMGR_GetInstance()->UnregisterService("noExistServiceName");
    TEST_ASSERT_EQUAL_INT(resultService == NULL, TRUE);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterService_0040
 * @tc.name      : Service which contains api failed to unregister
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testUnregisterService0040, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName101", GET_IUNKNOWN(g_service));

    Service *resultService = SAMGR_GetInstance()->UnregisterService("serviceName101");
    TEST_ASSERT_EQUAL_INT(resultService == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName101");
    SAMGR_GetInstance()->UnregisterService("serviceName101");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterService_0050
 * @tc.name      : Service which contains feature failed to unregister
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testUnregisterService0050, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName101", (Feature *)&g_feature);

    Service *resultService = SAMGR_GetInstance()->UnregisterService("serviceName101");
    TEST_ASSERT_EQUAL_INT(resultService == NULL, TRUE);
    
    SAMGR_GetInstance()->UnregisterFeature("serviceName101", "featureName101");
    SAMGR_GetInstance()->UnregisterService("serviceName101");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterService_0060
 * @tc.name      : Register and unregister service repeatedly, no memory leak
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testUnregisterService0060, LEVEL2)
{
    // RegisterService and unregister service over and over again, if there is memory leak samgr will crash
    for (int i = 0; i < PRESSURE_BASE; i++) {
        BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
        TEST_ASSERT_EQUAL_INT(result, TRUE);
        
        Service *resultService = SAMGR_GetInstance()->UnregisterService("serviceName101");
        TEST_ASSERT_EQUAL_INT(strcmp(resultService->GetName(resultService), "serviceName101"), 0);
    }
}

/**
 * @tc.number    : DMSLite_SAMGR_Bootstrap_0010
 * @tc.name      : Restart SAMGR service function is normal.
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(ServiceTestSuite, testBootstrap0010, LEVEL2)
{
    SAMGR_Bootstrap();
    LOS_Msleep(OPER_INTERVAL);

    SamgrLite *samgrLite = SAMGR_GetInstance();
    TEST_ASSERT_EQUAL_INT(TRUE, samgrLite != NULL);
};

RUN_TEST_SUITE(ServiceTestSuite);