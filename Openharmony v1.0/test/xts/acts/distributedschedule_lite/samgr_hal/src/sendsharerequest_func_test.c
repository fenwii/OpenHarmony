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

#define OPER_INTERVAL 200    // 200 ms
#define PRESSURE_BASE (1024 * 10)

enum MessageId {
    MSG_NO, // receiver does not send response
    MSG_RT, // receiver send response
    MSG_FW, // receiver forward message 
};

struct Payload {
    int id;
    const char *name;
    int value;
};

typedef struct DemoApi {
    INHERIT_IUNKNOWN;
    uint32 *(*SAMGR_SendSharedRequestProxy)(const Identity *identity, const Request *request, uint32 *token, 
                                            Handler handler);
    int32 (*SAMGR_SendSharedDirectRequestProxy)(const Identity *id, const Request *req, const Response *resp, 
                                                uint32 **ref, Handler handler);
} DemoApi;

typedef struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
    int featureCalledCount;
    BOOL featureStatus;
    char *latestRequest;
} DemoFeature;

typedef struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
} DefaultFeatureApi;

typedef struct ExampleService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
} ExampleService;

static uint32 *SAMGR_SendSharedRequestProxy(const Identity *identity, const Request *request, uint32 *token, 
                                            Handler handler)
{
    return SAMGR_SendSharedRequest(identity, request, token, handler);
}

static int32 SAMGR_SendSharedDirectRequestProxy(const Identity *id, const Request *req, const Response *resp, 
                                                uint32 **ref, Handler handler)
{
    return SAMGR_SendSharedDirectRequest(id, req, resp, ref, handler);
}

static const char *GetName(Service *service)
{
    (void)service;
    return "S_sendShareReq";
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
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
    }
};

static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return "feature01";
}

static const char *FEATURE_GetName02(Feature *feature)
{
    (void)feature;
    return "feature02";
}

static const char *FEATURE_GetName03(Feature *feature)
{
    (void)feature;
    return "feature03";
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
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;
    demoFeature->latestRequest = (char *)request->data;

    demoFeature->featureStatus = TRUE;
    return TRUE;
}

static BOOL FEATURE_OnMessage02(Feature *feature, Request *request)
{
    int32 returnCode = 0;
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;
    demoFeature->latestRequest = (char *)request->data;

    switch (request->msgId) {
        case MSG_NO:
            returnCode = 0;
            break;
        case MSG_RT:
        {
            Response response = {
                .data = "Yes, you did!",
                .len = 0,
                };
            returnCode = SAMGR_SendResponse(request, &response);
        };
        break;
        case MSG_FW:
        {
            returnCode = 0;
        };
        break;
    }
    demoFeature->featureStatus = ((returnCode == 0) ? TRUE : FALSE);
    return demoFeature->featureStatus;
}

static BOOL FEATURE_OnMessage03(Feature *feature, Request *request)
{
    int32 returnCode = 0;
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;
    demoFeature->latestRequest = (char *)request->data;

    switch (request->msgId) {
        case MSG_NO:
            returnCode = 0;
            break;
        case MSG_RT:
        {
            Response response = {
                .data = "Yes, you did!",
                .len = 0,
                };
            returnCode = SAMGR_SendResponse(request, &response);
        };
        break;
        case MSG_FW:
        {
            returnCode = 0;
        };
        break;
    }
    demoFeature->featureStatus = ((returnCode == 0) ? TRUE : FALSE);
    return demoFeature->featureStatus;
}

static DemoFeature g_feature = {
    .GetName = FEATURE_GetName,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage,
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .SAMGR_SendSharedRequestProxy = SAMGR_SendSharedRequestProxy,
        .SAMGR_SendSharedDirectRequestProxy = SAMGR_SendSharedDirectRequestProxy,
    },
    .identity = {-1, -1, NULL},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
    .latestRequest = NULL,
};
static DemoFeature g_feature02 = {
    .GetName = FEATURE_GetName02,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage02,
    .ref = 0,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .SAMGR_SendSharedRequestProxy = SAMGR_SendSharedRequestProxy,
        .SAMGR_SendSharedDirectRequestProxy = SAMGR_SendSharedDirectRequestProxy,
    },
    .identity = {-1, 1, NULL},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
    .latestRequest = NULL,
};
static DemoFeature g_feature03 = {
    .GetName = FEATURE_GetName03,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage03,
    .ref = 0,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .SAMGR_SendSharedRequestProxy = SAMGR_SendSharedRequestProxy,
        .SAMGR_SendSharedDirectRequestProxy = SAMGR_SendSharedDirectRequestProxy,
    },
    .identity = {-1, 2, NULL},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
    .latestRequest = NULL,
};

static void ServiceInit(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    if (result == FALSE) {
        printf("[hctest]E RegisterService failed.\n");
    }
}
SYSEX_SERVICE_INIT(ServiceInit);

static void FeatureInit(void)
{
    BOOL result1 = SAMGR_GetInstance()->RegisterDefaultFeatureApi("S_sendShareReq", GET_IUNKNOWN(g_feature));

    BOOL result2 = SAMGR_GetInstance()->RegisterFeature("S_sendShareReq", (Feature *)&g_feature02);
    BOOL result3 = SAMGR_GetInstance()->RegisterFeatureApi("S_sendShareReq", "feature02", 
                                                           GET_IUNKNOWN(g_feature02));

    BOOL result4 = SAMGR_GetInstance()->RegisterFeature("S_sendShareReq", (Feature *)&g_feature03);
    BOOL result5 = SAMGR_GetInstance()->RegisterFeatureApi("S_sendShareReq", "feature03", 
                                                           GET_IUNKNOWN(g_feature03));
    if (result1 == FALSE || result2 == FALSE || result3 == FALSE || result4 == FALSE || result5 == FALSE) {
        printf("[hctest]E failed to register feature or api.\n");
    }
}
SYSEX_FEATURE_INIT(FeatureInit);

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

static void ReleaseIUnknown(DemoApi *demoApi)
{
    demoApi->Release((IUnknown *)demoApi);
}

static void DemoHandlerAndCheck(const Request *request, const Response *response)
{
    char *requestData = "I wanna async call good result!";
    TEST_ASSERT_EQUAL_INT(strcmp((char *)request->data, requestData), 0);

    char *responseData = "Yes, you did!";
    TEST_ASSERT_EQUAL_INT(strcmp((char *)response->data, responseData), 0);
}

LITE_TEST_SUIT(test, samgr, SendSharedRequestTestSuite);

static BOOL SendSharedRequestTestSuiteSetUp(void)
{
    LOS_Msleep(OPER_INTERVAL);
    return TRUE;
}

static BOOL SendSharedRequestTestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : DMSLite_SAMGR_SendSharedRequest_0010
 * @tc.name      : Feature sends a response to a specified feature after processing the original request.
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SendSharedRequestTestSuite, testSendSharedRequest0010, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("S_sendShareReq", "feature02");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    Request request = {.msgId = MSG_RT, .msgValue = 0};
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("S_sendShareReq", "feature03");
    if (iUnknown == NULL) {
        TEST_FAIL();
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);

    feature->featureCalledCount = 0;
    uint32 *token = NULL;
    token = demoApi->SAMGR_SendSharedRequestProxy(&feature->identity, &request, token, DemoHandlerAndCheck);
    
    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(feature->featureCalledCount, 1);
    TEST_ASSERT_EQUAL_INT(strcmp(feature->latestRequest, body), 0);

    ReleaseIUnknown(demoApi);
}

/**
 * @tc.number    : DMSLite_SAMGR_SendSharedDirectRequest_0010
 * @tc.name      : Sends a request and response of a caller to the feature thread
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SendSharedRequestTestSuite, testSendSharedDirectRequest0010, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("S_sendShareReq", "feature02");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    Request request = {.msgId = MSG_RT, .msgValue = 0};
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("S_sendShareReq", "feature03");
    if (iUnknown == NULL) {
        TEST_FAIL();
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);

    feature->featureCalledCount = 0;
    Response response = {
        .data = "Yes, you did!", 
        .len = 0,
        };
    uint32 *token = NULL;
    int32 result = demoApi->SAMGR_SendSharedDirectRequestProxy(&feature->identity, &request, &response, 
                                                &token, DemoHandlerAndCheck);
    TEST_ASSERT_EQUAL_INT(result, 0);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(feature->featureCalledCount, 0);
    
    ReleaseIUnknown(demoApi);
}

RUN_TEST_SUITE(SendSharedRequestTestSuite);