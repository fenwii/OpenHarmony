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

struct DemoApi {
    INHERIT_IUNKNOWN;
    uint32 *(*SAMGR_SendSharedRequestProxy)(const Identity *identity, const Request *request, uint32 *token, 
                                            Handler handler);
    int32 (*SAMGR_SendSharedDirectRequestProxy)(const Identity *id, const Request *req, const Response *resp, 
                                                uint32 **ref, Handler handler);
};

struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
    int featureCalledCount;
    BOOL featureStatus;
    char *latestRequest;
};

struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
};

struct ExampleService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
};

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

    printf("[hcpptest]serviceName %s Initialize \n", service->GetName(service));

    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
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
    .ver = 0x20,
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

    printf("[hcpptest]featureName %s Initialize \n", feature->GetName(feature));
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
    int32 returnCode;
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
                .data = (char*)"Yes, you did!",
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
    int32 returnCode;
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
                .data = (char*)"Yes, you did!",
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
    .ver = 0x20,
    .ref = 1,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .SAMGR_SendSharedRequestProxy = SAMGR_SendSharedRequestProxy,
        .SAMGR_SendSharedDirectRequestProxy = SAMGR_SendSharedDirectRequestProxy,
    },
    .identity = {-1, -1, nullptr},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
    .latestRequest = nullptr,
};
static DemoFeature g_feature02 = {
    .GetName = FEATURE_GetName02,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage02,
    .ver = 0x20,
    .ref = 0,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .SAMGR_SendSharedRequestProxy = SAMGR_SendSharedRequestProxy,
        .SAMGR_SendSharedDirectRequestProxy = SAMGR_SendSharedDirectRequestProxy,
    },
    .identity = {-1, 1, nullptr},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
    .latestRequest = nullptr,
};
static DemoFeature g_feature03 = {
    .GetName = FEATURE_GetName03,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage03,
    .ver = 0x20,
    .ref = 0,
    .iUnknown = {
        DEFAULT_IUNKNOWN_IMPL,
        .SAMGR_SendSharedRequestProxy = SAMGR_SendSharedRequestProxy,
        .SAMGR_SendSharedDirectRequestProxy = SAMGR_SendSharedDirectRequestProxy,
    },
    .identity = {-1, 2, nullptr},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
    .latestRequest = nullptr,
};

static void GServiceInit(void)
{
    printf("[hcpptest]GServiceInit start! \n");
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    if (result == FALSE) {
        printf("[hcpptest]E RegisterService failed! \n");
    }
}
SYSEX_SERVICE_INIT(GServiceInit);

static void GFeatureInit(void)
{
    printf("[hcpptest]GFeatureInit start! \n");

    BOOL result1 = SAMGR_GetInstance()->RegisterDefaultFeatureApi("S_sendShareReq", GET_IUNKNOWN(g_feature));

    BOOL result2 = SAMGR_GetInstance()->RegisterFeature("S_sendShareReq", (Feature *)&g_feature02);
    BOOL result3 = SAMGR_GetInstance()->RegisterFeatureApi("S_sendShareReq", "feature02", 
                                                           GET_IUNKNOWN(g_feature02));

    BOOL result4 = SAMGR_GetInstance()->RegisterFeature("S_sendShareReq", (Feature *)&g_feature03);
    BOOL result5 = SAMGR_GetInstance()->RegisterFeatureApi("S_sendShareReq", "feature03", 
                                                           GET_IUNKNOWN(g_feature03));
    if (result1 == FALSE || result2 == FALSE || result3 == FALSE || result4 == FALSE || result5 == FALSE) {
        printf("[hcpptest]E failed to register feature or api! \n");
    }
}
SYSEX_FEATURE_INIT(GFeatureInit);

static DemoApi *GetIUnknown(const char *serviceName, const char *featureName)
{
    DemoApi *demoApi = nullptr;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(serviceName, featureName);
    if (iUnknown == nullptr) {
        printf("[hcpptest]failed to GetFeatureApi.\n");
        return nullptr;
    }
    int result = iUnknown->QueryInterface(iUnknown, 0x20, (void **)&demoApi);
    if (result == 0 && demoApi != nullptr) {
        return demoApi;
    } else {
        printf("[hcpptest]failed to QueryInterface.\n");
        return nullptr;
    }
}

static void ReleaseIUnknown(DemoApi *demoApi)
{
    demoApi->Release((IUnknown *)demoApi);
}

static void DemoHandler(const Request *request, const Response *response)
{
    (void)request;
    (void)response;
}

static void DemoHandlerAndCheck(const Request *request, const Response *response)
{
    char *requestData = (char*)"I wanna async call good result!";
    ASSERT_EQ(strcmp((char *)request->data, requestData), 0);

    char *responseData = (char*)"Yes, you did!";
    ASSERT_EQ(strcmp((char *)response->data, responseData), 0);
}

class SendShareRequestTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
        printf("[hcpptest]SetUpTestCase! \n");
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
 * @tc.number    : DMSLite_SAMGR_SendSharedRequest_0010
 * @tc.name      : Feature sends a response to a specified feature after processing the original request.
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(SendShareRequestTest, testSendSharedRequest0010, TestSize.Level2) {
    DemoApi *demoApi = GetIUnknown("S_sendShareReq", "feature02");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    Request request = {.msgId = MSG_RT,
                       .len = 0,
                       .data = nullptr,
                       .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        printf("[hcpptest]error failed to strcpy_s \n");
    }

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("S_sendShareReq", "feature03");
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);

    feature->featureCalledCount = 0;
    uint32 *token = NULL;
    token = demoApi->SAMGR_SendSharedRequestProxy(&feature->identity, &request, token, DemoHandlerAndCheck);
    
    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(feature->featureCalledCount, 1);
    
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
HWTEST_F(SendShareRequestTest, testSendSharedDirectRequest0010, TestSize.Level2) {
    DemoApi *demoApi = GetIUnknown("S_sendShareReq", "feature02");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    Request request = {.msgId = MSG_RT,
                       .len = 0,
                       .data = nullptr,
                       .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = (int16)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        printf("[hcpptest]error failed to strcpy_s \n");
    }

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("S_sendShareReq", "feature03");
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);

    feature->featureCalledCount = 0;
    Response response = {
        .data = (char*)"Yes, you did!", 
        .len = 0,
        };
    uint32 *token = NULL;
    int32 result = demoApi->SAMGR_SendSharedDirectRequestProxy(&feature->identity, &request, &response, 
                                                &token, DemoHandlerAndCheck);
    ASSERT_EQ(result, 0);

    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(feature->featureCalledCount, 0);
    
    ReleaseIUnknown(demoApi);
}