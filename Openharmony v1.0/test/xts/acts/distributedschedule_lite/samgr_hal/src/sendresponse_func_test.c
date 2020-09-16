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
    MSG_NO = 1, // receiver does not send response
    MSG_RT = 2, // receiver send response
    MSG_FW = 3, // receiver forward message 
    MSG_RT_MULTI = 4, // receiver send response
};

struct Payload {
    int id;
    const char *name;
    int value;
};

typedef struct DemoApi {
    INHERIT_IUNKNOWN;
    int32 (*SAMGR_SendRequestProxy)(const Identity *identity, const Request *request, Handler handler);
} DemoApi;

typedef struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
    int featureCalledCount;
    BOOL featureStatus;
} DemoFeature;

typedef struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
} DefaultFeatureApi;

typedef struct ExampleService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
} ExampleService;

static int32 SAMGR_SendRequestProxy(const Identity *identity, const Request *request, Handler handler)
{
    return SAMGR_SendRequest(identity, request, handler);
}

static const char *GetName(Service *service)
{
    (void)service;
    return "serviceName601";
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
    TaskConfig config = {LEVEL_HIGH, PRI_ABOVE_NORMAL, 0x800, 20, SHARED_TASK};  // share with broadcast
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
    return "featureName601";
}

static const char *FEATURE_GetName02(Feature *feature)
{
    (void)feature;
    return "featureName602";
}

static const char *FEATURE_GetName03(Feature *feature)
{
    (void)feature;
    return "featureName603";
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
    (void)request;
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;
    demoFeature->featureStatus = TRUE;

    return TRUE;
}

static BOOL FEATURE_OnMessage02(Feature *feature, Request *request)
{
    int32 returnCode = 0;
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;

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
            Response response = {
                .data = "Yes, you did!",
                .len = 0,
                };
            request->msgId = MSG_NO;
            IUnknown *iUnknownX = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName602");
            DemoFeature *featureX = GET_OBJECT(iUnknownX, DemoFeature, iUnknown);
            returnCode = SAMGR_SendResponseByIdentity(&featureX->identity, request, &response);
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
            Response response = {
                .data = "Yes, you did!",
                .len = 0,
                };
            request->msgId = MSG_NO;
            IUnknown *iUnknownX = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName602");
            DemoFeature *featureX = GET_OBJECT(iUnknownX, DemoFeature, iUnknown);
            returnCode = SAMGR_SendResponseByIdentity(&featureX->identity, request, &response);
        };
        break;
        case MSG_RT_MULTI:
        {
            Response response = {
                .data = "Yes, you did!",
                .len = 0,
                };
            for (int i = 0; i < PRESSURE_BASE; i++) {
                int tempCode = SAMGR_SendResponse(request, &response);
                if (tempCode != 0) {
                    printf("[hctest]E failed to SendResponse occurs: %d rt: %d \n", i, tempCode);
                    returnCode++;
                }
            }
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
        .SAMGR_SendRequestProxy = SAMGR_SendRequestProxy,
    },
    .identity = {-1, -1, NULL},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
};
static DemoFeature g_feature02 = {
    .GetName = FEATURE_GetName02,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage02,
    .ref = 0,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .SAMGR_SendRequestProxy = SAMGR_SendRequestProxy,
    },
    .identity = {-1, 1, NULL},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
};
static DemoFeature g_feature03 = {
    .GetName = FEATURE_GetName03,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage03,
    .ref = 0,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .SAMGR_SendRequestProxy = SAMGR_SendRequestProxy,
    },
    .identity = {-1, 2, NULL},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
};

static void ServiceInit(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    if (result == FALSE) {
        printf("[hctest]E RegisterService failed \n");
    }
}
SYSEX_SERVICE_INIT(ServiceInit);

static void FeatureInit(void)
{
    BOOL result1 = SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName601", GET_IUNKNOWN(g_feature));

    BOOL result2 = SAMGR_GetInstance()->RegisterFeature("serviceName601", (Feature *)&g_feature02);
    BOOL result3 = SAMGR_GetInstance()->RegisterFeatureApi("serviceName601", "featureName602", 
                                                           GET_IUNKNOWN(g_feature02));

    BOOL result4 = SAMGR_GetInstance()->RegisterFeature("serviceName601", (Feature *)&g_feature03);
    BOOL result5 = SAMGR_GetInstance()->RegisterFeatureApi("serviceName601", "featureName603", 
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

static void DemoHandler(const Request *request, const Response *response)
{
    (void)request;
    (void)response;
}

LITE_TEST_SUIT(test, samgr, SendResponseTestSuite);

static BOOL SendResponseTestSuiteSetUp(void)
{
    LOS_Msleep(OPER_INTERVAL);
    return TRUE;
}

static BOOL SendResponseTestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : DMSLite_SAMGR_SendResponse_0010
 * @tc.name      : Receiver send response successfully
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SendResponseTestSuite, testSendResponse0010, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
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

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    if (iUnknown == NULL) {
        TEST_FAIL();
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, DemoHandlerAndCheck);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(feature->featureStatus == TRUE, TRUE);
    ReleaseIUnknown(demoApi);
}

/**
 * @tc.number    : DMSLite_SAMGR_SendResponse_0020
 * @tc.name      : Receiver can not send response if sender has not register callback
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SendResponseTestSuite, testSendResponse0020, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
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

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    if (iUnknown == NULL) {
        TEST_FAIL();
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, NULL);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(feature->featureStatus == FALSE, TRUE);
    ReleaseIUnknown(demoApi);
}

/**
 * @tc.number    : DMSLite_SAMGR_SendResponse_0030
 * @tc.name      : Receiver send response to itself successfully
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SendResponseTestSuite, testSendResponse0030, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName603");
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

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    if (iUnknown == NULL) {
        TEST_FAIL();
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, DemoHandler);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(feature->featureStatus == TRUE, TRUE);
    ReleaseIUnknown(demoApi);
}

/**
 * @tc.number    : DMSLite_SAMGR_SendResponse_0040
 * @tc.name      : Receiver send response to the origin feature repeatedly
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SendResponseTestSuite, testSendResponse0040, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    Request request = {.msgId = MSG_RT_MULTI, .msgValue = 0};    // MSG_RT_MULTI: multi response
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    if (iUnknown == NULL) {
        TEST_FAIL();
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, DemoHandlerAndCheck);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(feature->featureStatus, TRUE);
    ReleaseIUnknown(demoApi);
}

/**
 * @tc.number    : DMSLite_SAMGR_SendResponseByIdentity_0010
 * @tc.name      : Receiver forward message successfully
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SendResponseTestSuite, testSendResponseByIdentity0010, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    Request request = {.msgId = MSG_FW, .msgValue = 0};
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    if (iUnknown == NULL) {
        TEST_FAIL();
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    feature->featureStatus = FALSE;
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, DemoHandlerAndCheck);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(feature->featureStatus == TRUE, TRUE);  

    ReleaseIUnknown(demoApi);
}

/**
 * @tc.number    : DMSLite_SAMGR_SendResponseByIdentity_0020
 * @tc.name      : Receiver can not forward message if the sender has not registered handler
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(SendResponseTestSuite, testSendResponseByIdentity0020, LEVEL2)
{
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
    if (demoApi == NULL) {
        TEST_FAIL();
    }
    Request request = {.msgId = MSG_FW, .msgValue = 0};
    char *body = "I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        TEST_FAIL();
    }
    strcpy_s(request.data, request.len, body);

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    if (iUnknown == NULL) {
        TEST_FAIL();
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, NULL);

    LOS_Msleep(OPER_INTERVAL);
    TEST_ASSERT_EQUAL_INT(feature->featureStatus == FALSE, TRUE);

    ReleaseIUnknown(demoApi);
}

RUN_TEST_SUITE(SendResponseTestSuite);