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

#include <los_base.h>
#include "hctest.h"
#include "samgr_lite.h"

#define PRESSURE_BASE (1024 * 10)

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
    return "serviceName401";
}

typedef struct ExampleService {
    INHERIT_SERVICE;
    Identity identity;
} ExampleService;

static BOOL Initialize(Service *service, Identity identity)
{
    ExampleService *example = (ExampleService *)service;
    example->identity = identity;
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
    .identity = {-1, -1, NULL},
};

static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return "featureName401";
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

LITE_TEST_SUIT(test, samgr, FeatureApiTestSuite);

static BOOL FeatureApiTestSuiteSetUp(void)
{
    return TRUE;
}

static BOOL FeatureApiTestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeatureApi_0010
 * @tc.name      : Api can be registered under a feature
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testRegisterFeatureApi0010, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);

    BOOL result = SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401",
                                                          GET_IUNKNOWN(g_feature));
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeatureApi_0020
 * @tc.name      : API failed to register if the specified service name is null or space
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testRegisterFeatureApi0020, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);

    BOOL result = SAMGR_GetInstance()->RegisterFeatureApi(NULL, "featureName401", GET_IUNKNOWN(g_feature));
    TEST_ASSERT_EQUAL_INT(result, FALSE);

    result = SAMGR_GetInstance()->RegisterFeatureApi("", "featureName401", GET_IUNKNOWN(g_feature));
    TEST_ASSERT_EQUAL_INT(result, FALSE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeatureApi_0030
 * @tc.name      : API failed to register if the specified feature is space
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testRegisterFeatureApi0030, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);

    BOOL result = SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "", GET_IUNKNOWN(g_feature));
    TEST_ASSERT_EQUAL_INT(result, FALSE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeatureApi_0040
 * @tc.name      : API failed to register if the api is null
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testRegisterFeatureApi0040, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);

    BOOL result = SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", NULL);
    TEST_ASSERT_EQUAL_INT(result, FALSE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeatureApi_0050
 * @tc.name      : If the specified feature is null api will be registered as default feature api
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testRegisterFeatureApi0050, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);

    // feature is null, handle as default feature api
    BOOL result = SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", NULL, GET_IUNKNOWN(g_feature));
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", NULL);
    TEST_ASSERT_EQUAL_INT(resultIUnknown != NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeatureApi_0060
 * @tc.name      : API failed to register if the specified service name does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testRegisterFeatureApi0060, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);

    BOOL result = SAMGR_GetInstance()->RegisterFeatureApi("noExistService", "featureName401", GET_IUNKNOWN(g_feature));
    TEST_ASSERT_EQUAL_INT(result, FALSE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeatureApi_0070
 * @tc.name      : API failed to register if the specified feature name does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testRegisterFeatureApi0070, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);

    BOOL result = SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "noExistFeature", GET_IUNKNOWN(g_feature));
    TEST_ASSERT_EQUAL_INT(result, FALSE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterFeatureApi_0080
 * @tc.name      : feature api can not be registered twice
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testRegisterFeatureApi0080, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    BOOL result = SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401",
                                                          GET_IUNKNOWN(g_feature));
    TEST_ASSERT_EQUAL_INT(FALSE, result);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetFeatureApi_0010
 * @tc.name      : Service can query API by serverName-featureName
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testGetFeatureApi0010, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    IUnknown *resultIUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName401", "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown != NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetFeatureApi_0020
 * @tc.name      : If the specified serviceName is NULL or space GetFeatureApi return NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testGetFeatureApi0020, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    IUnknown *resultIUnknown = SAMGR_GetInstance()->GetFeatureApi(NULL, "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);
    resultIUnknown = SAMGR_GetInstance()->GetFeatureApi("", "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetFeatureApi_0030
 * @tc.name      : If the specified featureName is NULL or space GetFeatureApi return NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testGetFeatureApi0030, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    IUnknown *resultIUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName401", NULL);
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);
    resultIUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName401", "");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetFeatureApi_0040
 * @tc.name      : If the specified featureName does not exist GetFeatureApi return NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testGetFeatureApi0040, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    
    IUnknown *resultIUnknown = SAMGR_GetInstance()->GetFeatureApi("noExistService", "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);
    resultIUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName401", "noExistFeature");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);
    
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetFeatureApi_0050
 * @tc.name      : If no API under the specified feature GetFeatureApi return NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testGetFeatureApi0050, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    
    IUnknown *resultIUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName401", "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetFeatureApi_0060
 * @tc.name      : The results of multiple queries are the same for GetFeatureApi 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testGetFeatureApi0060, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    IUnknown *resultIUnknown1 = SAMGR_GetInstance()->GetFeatureApi("serviceName401", "featureName401");
    IUnknown *resultIUnknown2 = SAMGR_GetInstance()->GetFeatureApi("serviceName401", "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown1 == resultIUnknown2, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeatureApi_0010
 * @tc.name      : FeatureApi can be unregistered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testUnregisterFeatureApi0010, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown != NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeatureApi_0020
 * @tc.name      : FeatureApi failed to unregister if the specified serviceName is NULL or space
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testUnregisterFeatureApi0020, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterFeatureApi(NULL, "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);
    resultIUnknown = SAMGR_GetInstance()->UnregisterFeatureApi("", "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeatureApi_0030
 * @tc.name      : FeatureApi failed to unregister if the specified featureName is space
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testUnregisterFeatureApi0030, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeatureApi_0040
 * @tc.name      : FeatureApi failed to unregister if the specified serviceName does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testUnregisterFeatureApi0040, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));

    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterFeatureApi("noExistService", "featureName401");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeatureApi_0050
 * @tc.name      : FeatureApi failed to unregister if the specified featureName does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testUnregisterFeatureApi0050, LEVEL2)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));
    
    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "noExistFeature");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
    SAMGR_GetInstance()->UnregisterService("serviceName401");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterFeatureApi_0060
 * @tc.name      : Register and unregister feature api repeatedly, no memory leak
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(FeatureApiTestSuite, testUnregisterFeatureApi0060, LEVEL2)
{
    // RegisterService and unregister feature api over and over again, if there is memory leak samgr will crash
    for (int i = 0; i < PRESSURE_BASE; i++) {
        BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
        TEST_ASSERT_EQUAL_INT(result, TRUE);
        result = SAMGR_GetInstance()->RegisterFeature("serviceName401", (Feature *)&g_feature);
        TEST_ASSERT_EQUAL_INT(result, TRUE);
        result = SAMGR_GetInstance()->RegisterFeatureApi("serviceName401", "featureName401", GET_IUNKNOWN(g_feature));
        TEST_ASSERT_EQUAL_INT(result, TRUE);

        IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterFeatureApi("serviceName401", "featureName401");
        TEST_ASSERT_EQUAL_INT(resultIUnknown != NULL, TRUE);
        Feature *resultFeature = SAMGR_GetInstance()->UnregisterFeature("serviceName401", "featureName401");
        TEST_ASSERT_EQUAL_INT(resultFeature != NULL, TRUE);
        Service *resultService = SAMGR_GetInstance()->UnregisterService("serviceName401");
        TEST_ASSERT_EQUAL_INT(resultService != NULL, TRUE);
    }
}

RUN_TEST_SUITE(FeatureApiTestSuite);