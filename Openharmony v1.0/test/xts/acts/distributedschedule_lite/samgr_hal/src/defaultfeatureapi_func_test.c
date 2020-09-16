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

#define PRESSURE_BASE (1024 * 10)

typedef struct DemoApi {
    INHERIT_IUNKNOWN;
} DemoApi;

typedef struct ExampleService {
    INHERIT_SERVICE;
    Identity identity;
} ExampleService;

static DemoApi g_api = {
    DEFAULT_IUNKNOWN_IMPL,
};

static const char *GetName(Service *service)
{
    (void)service;
    return "serviceName301";
}

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
    TaskConfig config = {LEVEL_HIGH, PRI_ABOVE_NORMAL, 0x800, 20, SHARED_TASK};
    return config;
}

static ExampleService g_service = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    .identity = {-1, -1, NULL},
};

LITE_TEST_SUIT(test, samgr, DefaultFeatureApiTestSuite);

static BOOL DefaultFeatureApiTestSuiteSetUp(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    return result;
}

static BOOL DefaultFeatureApiTestSuiteTearDown(void)
{
    Service *resultService = SAMGR_GetInstance()->UnregisterService("serviceName301");
    if (strcmp(resultService->GetName(resultService), "serviceName301") == 0) {
        return TRUE;
    } else {
        printf("[hctest]failed to unregister service.\n");
        return FALSE;
    }
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterDefaultFeatureApi_0010
 * @tc.name      : Valid API can be registered under default feature
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testRegisterDefaultFeatureApi0010, LEVEL1)
{
    BOOL result = SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);
    TEST_ASSERT_EQUAL_INT(result, TRUE);    // TRUE: success; FALSE: fail

    SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterDefaultFeatureApi_0020
 * @tc.name      : API failed to register if the specified service is null
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testRegisterDefaultFeatureApi0020, LEVEL2)
{
    BOOL result = SAMGR_GetInstance()->RegisterDefaultFeatureApi(NULL, (IUnknown *)&g_api);
    TEST_ASSERT_EQUAL_INT(result, FALSE);
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterDefaultFeatureApi_0030
 * @tc.name      : API failed to register if the specified service does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testRegisterDefaultFeatureApi0030, LEVEL2)
{
    BOOL result = SAMGR_GetInstance()->RegisterDefaultFeatureApi("noExistService", (IUnknown *)&g_api);
    TEST_ASSERT_EQUAL_INT(result, FALSE);
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterDefaultFeatureApi_0040
 * @tc.name      : API failed to register if the target API is NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testRegisterDefaultFeatureApi0040, LEVEL2) 
{
    BOOL result = SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", NULL);
    TEST_ASSERT_EQUAL_INT(result, FALSE);
}

/**
 * @tc.number    : DMSLite_SAMGR_RegisterDefaultFeatureApi_0050
 * @tc.name      : API failed to register for the target API already exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testRegisterDefaultFeatureApi0050, LEVEL2)
{
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);
    BOOL result = SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);
    TEST_ASSERT_EQUAL_INT(result, FALSE);

    SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetDefaultFeatureApi_0010
 * @tc.name      : API can be queried out from service
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testGetDefaultFeatureApi0010, LEVEL1)
{
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);

    IUnknown *resultIUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi("serviceName301");
    TEST_ASSERT_EQUAL_INT(resultIUnknown != NULL, TRUE);

    SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetDefaultFeatureApi_0020
 * @tc.name      : It's NULL result if the specified service name is NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testGetDefaultFeatureApi0020, LEVEL2)
{
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);

    IUnknown *resultIUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(NULL);
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetDefaultFeatureApi_0030
 * @tc.name      : The query result is NULL for the specified service does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testGetDefaultFeatureApi0030, LEVEL2)
{
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);

    IUnknown *resultIUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi("noExistService");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);
    
    SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
}

/**
 * @tc.number    : DMSLite_SAMGR_GetDefaultFeatureApi_0040
 * @tc.name      : The query result is the same for multi query operations
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testGetDefaultFeatureApi0040, LEVEL2)
{
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);

    IUnknown *resultIUnknown1 = SAMGR_GetInstance()->GetDefaultFeatureApi("serviceName301");
    IUnknown *resultIUnknown2 = SAMGR_GetInstance()->GetDefaultFeatureApi("serviceName301");
    TEST_ASSERT_EQUAL_INT(resultIUnknown1 == resultIUnknown2, TRUE);
    
    SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterDefaultFeatureApi_0010
 * @tc.name      : Default feature API can be unregistered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testUnregisterDefaultFeatureApi0010, LEVEL1)
{
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);

    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
    TEST_ASSERT_EQUAL_INT(resultIUnknown != NULL, TRUE);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterDefaultFeatureApi_0020
 * @tc.name      : The unregister operation failed if serviceName is NULL or space
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testUnregisterDefaultFeatureApi0020, LEVEL2)
{
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);

    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterDefaultFeatureApi(NULL);
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    resultIUnknown = SAMGR_GetInstance()->UnregisterDefaultFeatureApi("");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);

    SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterDefaultFeatureApi_0030
 * @tc.name      : The unregister operation failed if the specified service does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testUnregisterDefaultFeatureApi0030, LEVEL2)
{
    IUnknown *resultIUnknown = SAMGR_GetInstance()->UnregisterDefaultFeatureApi("noExistService");
    TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnregisterDefaultFeatureApi_0040
 * @tc.name      : Register and unregister default api repeatedly, no memory leak
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(DefaultFeatureApiTestSuite, testUnregisterDefaultFeatureApi0040, LEVEL2)
{
    // RegisterService and unregister default api over and over again, if there is memory leak samgr will crash
    for (int i = 0; i < PRESSURE_BASE; i++) {
        BOOL result = SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName301", (IUnknown *)&g_api);
        TEST_ASSERT_EQUAL_INT(result, TRUE);

        IUnknown *resultIUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi("serviceName301");
        TEST_ASSERT_EQUAL_INT(resultIUnknown != NULL, TRUE);

        resultIUnknown = SAMGR_GetInstance()->UnregisterDefaultFeatureApi("serviceName301");
        TEST_ASSERT_EQUAL_INT(resultIUnknown != NULL, TRUE);

        resultIUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi("serviceName301");
        TEST_ASSERT_EQUAL_INT(resultIUnknown == NULL, TRUE);
    }
}

RUN_TEST_SUITE(DefaultFeatureApiTestSuite);