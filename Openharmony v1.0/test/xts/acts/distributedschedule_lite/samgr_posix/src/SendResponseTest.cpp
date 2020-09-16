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

struct DemoApi {
    INHERIT_IUNKNOWN;
    int32 (*SAMGR_SendRequestProxy)(const Identity *identity, const Request *request, Handler handler);
};

struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
    int featureCalledCount;
    BOOL featureStatus;
};

struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
};

struct ExampleService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
};

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

    printf("[hcpptest]serviceName %s Initialize \n", service->GetName(service));
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
    .ver = 0x20,
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
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;
    demoFeature->featureStatus = TRUE;

    return TRUE;
}

static BOOL FEATURE_OnMessage02(Feature *feature, Request *request)
{
    int32 returnCode;
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->featureCalledCount++;

    switch (request->msgId) {
        case MSG_NO:
            returnCode = 0;
            break;
        case MSG_RT:
        {
            char *dataR = (char*)"Yes, you did!";
            Response response = {
                .data = dataR,
                .len = 0,
                };
            returnCode = SAMGR_SendResponse(request, &response);
        };
        break;
        case MSG_FW:
        {
            char *dataR = (char*)"Yes, you did!";
            Response response = {
                .data = dataR,
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
            char *dataR = (char*)"Yes, you did!";
            Response response = {
                .data = dataR,
                .len = 0,
                };
            returnCode = SAMGR_SendResponse(request, &response);
        };
        break;
        case MSG_FW:
        {
            char *dataR = (char*)"Yes, you did!";
            Response response = {
                .data = dataR,
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
                .data = (char*)"Yes, you did!",
                .len = 0,
                };
            for (int i = 0; i < PRESSURE_L0; i++) {
                int tempCode = SAMGR_SendResponse(request, &response);
                if (tempCode != 0) {
                    printf("[hctest]E failed to SendResponse occurs: %d rt: %d \n", i, tempCode);
                    returnCode++;
                }
            }
        }
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
        .SAMGR_SendRequestProxy = SAMGR_SendRequestProxy,
    },
    .identity = {-1, -1, nullptr},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
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
        .SAMGR_SendRequestProxy = SAMGR_SendRequestProxy,
    },
    .identity = {-1, 1, nullptr},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
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
        .SAMGR_SendRequestProxy = SAMGR_SendRequestProxy,
    },
    .identity = {-1, 2, nullptr},
    .featureCalledCount = 0,
    .featureStatus = TRUE,
};

static void GServiceInit(void)
{
    printf("[hcpptest]ServiceInit! \n");
    SAMGR_GetInstance()->RegisterService((Service *)&g_service);
}
SYSEX_SERVICE_INIT(GServiceInit);

static void GFeatureInit(void)
{
    printf("[hcpptest]FeatureInit! \n");
    SAMGR_GetInstance()->RegisterDefaultFeatureApi("serviceName601", GET_IUNKNOWN(g_feature));

    SAMGR_GetInstance()->RegisterFeature("serviceName601", (Feature *)&g_feature02);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName601", "featureName602", GET_IUNKNOWN(g_feature02));

    SAMGR_GetInstance()->RegisterFeature("serviceName601", (Feature *)&g_feature03);
    SAMGR_GetInstance()->RegisterFeatureApi("serviceName601", "featureName603", GET_IUNKNOWN(g_feature03));
}
SYSEX_FEATURE_INIT(GFeatureInit);

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

static void DemoHandlerAndCheck2(const Request *request, const Response *response)
{
    ASSERT_EQ(request->data != nullptr, TRUE);
    ASSERT_EQ(response->data != nullptr, TRUE);
}

class SendResponseTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
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
 * @tc.number    : DMSLite_SAMGR_SendResponse_0010
 * @tc.name      : Receiver send response successfully
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(SendResponseTest, testSendResponse0010, TestSize.Level2) {
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    Request request = {.msgId = MSG_RT,
                       .len = 0,
                       .data = nullptr,
                       .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = strlen(body) + 1;
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        ADD_FAILURE();
    }

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, DemoHandlerAndCheck);

    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(feature->featureStatus, TRUE);
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
HWTEST_F(SendResponseTest, testSendResponse0020, TestSize.Level2) {
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    Request request = {.msgId = MSG_RT,
                       .len = 0,
                       .data = nullptr,
                       .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = strlen(body) + 1;
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        ADD_FAILURE();
    }

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, nullptr);

    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(feature->featureStatus == FALSE, TRUE);
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
HWTEST_F(SendResponseTest, testSendResponse0030, TestSize.Level2) {
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName603");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    Request request = {.msgId = MSG_RT, 
                       .len = 0,
                       .data = nullptr,
                       .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = strlen(body) + 1;
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        ADD_FAILURE();
    }

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, DemoHandler);

    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(feature->featureStatus == TRUE, TRUE);
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
HWTEST_F(SendResponseTest, testSendResponse0040, TestSize.Level2) {
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    Request request = {.msgId = MSG_RT_MULTI, 
                       .len = 0,
                       .data = nullptr,
                       .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = strlen(body) + 1;
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        ADD_FAILURE();
    }

    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, DemoHandler);

    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(feature->featureStatus == TRUE, TRUE);
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
HWTEST_F(SendResponseTest, testSendResponseByIdentity0020, TestSize.Level2) {
    DemoApi *demoApi = GetIUnknown("serviceName601", "featureName602");
    if (demoApi == nullptr) {
        ADD_FAILURE();
    }
    Request request = {.msgId = MSG_FW, 
                       .len = 0,
                       .data = nullptr,
                       .msgValue = 0};
    char *body = (char*)"I wanna async call good result!";
    request.len = strlen(body) + 1;
    request.data = malloc(request.len);
    if (request.data == nullptr) {
        ADD_FAILURE();
    }
    errno_t error = strcpy_s((char *)request.data, request.len, body);
    if (error != EOK) {
        ADD_FAILURE();
    }
    
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi("serviceName601", "featureName603");
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);

    demoApi->SAMGR_SendRequestProxy(&feature->identity, &request, nullptr);

    usleep(OPER_INTERVAL * MS2US);
    ASSERT_EQ(feature->featureStatus == FALSE, TRUE);

    ReleaseIUnknown(demoApi);
}