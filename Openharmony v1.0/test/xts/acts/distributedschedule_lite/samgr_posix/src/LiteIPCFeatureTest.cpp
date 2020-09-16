/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 */

#include <securec.h>
#include <hos_init.h>
#include <hos_errno.h>
#include "gtest/gtest.h"
#include "utils/SamgrTestBase.h"
#include "iproxy_client.h"
#include "iproxy_server.h"

using namespace testing::ext;

static const char *SERVICE_NAME = {"ipcService02"};
static const char *FEATURE_NAME = {"ipcFeature"};

struct DemoService {
    INHERIT_SERVICE;
    Identity identity;
    BOOL serviceStatus;
};

static const char *GetName(Service *service)
{
    (void)service;
    return SERVICE_NAME;
}

static BOOL Initialize(Service *service, Identity identity)
{
    DemoService *demoService = (DemoService *)service;
    demoService->identity = identity;
    demoService->serviceStatus = TRUE;
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
    TaskConfig config = {LEVEL_HIGH, PRI_BELOW_NORMAL, 0x800, 20, SHARED_TASK};
    return config;
}

static DemoService g_service = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    .identity = {-1, -1, nullptr},
    .serviceStatus = FALSE,
};

static int calledCount = 0;
struct DemoFeatureApi {
    INHERIT_SERVER_IPROXY;
    void (*SyncCall)(IUnknown *iUnknown);
};

struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoFeatureApi);
    Identity identity;
    BOOL featureStatus;
};

static const char *FEATURE_GetName(Feature *feature);
static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity);
static void FEATURE_OnStop(Feature *feature, Identity identity);
static BOOL FEATURE_OnMessage(Feature *feature, Request *request);
static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);
static void SyncCall(IUnknown *iUnknown);

static DemoFeature g_feature = {
    .GetName = FEATURE_GetName,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage,
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = Invoke,
    .SyncCall = SyncCall,
    IPROXY_END,
    .identity = {-1, -1, NULL},
    .featureStatus = FALSE,
};
static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return FEATURE_NAME;
}

static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->identity = identity;
    demoFeature->featureStatus = TRUE;
}

static void FEATURE_OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
}

static BOOL FEATURE_OnMessage(Feature *feature, Request *msg)
{
    printf("[hcpptest][TID:0x%lx]OnMessage(%s)! Request<%d, %d, %p>",
           pthread_self(), feature->GetName(feature), msg->msgId, msg->msgValue, msg->data);
    return TRUE;
}

static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    printf("[hcpptest][TID:0x%lx]Feature Remote Invoke is called! <%p, %d, %p, %p, %p>",
           pthread_self(), iProxy, funcId, origin, req, reply);
    IpcIoPushBool(reply, TRUE);
    return EC_SUCCESS;
}

static void SyncCall(IUnknown *iUnknown)
{
    calledCount++;
}

static void ServiceInit(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    if (result == FALSE) {
        printf("[hcpptest][error]RegisterService fail \n");
        (&g_service)->serviceStatus = FALSE;
    }
}
SYSEX_SERVICE_INIT(ServiceInit);

static void FeatureInit(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterFeature(SERVICE_NAME, (Feature *)&g_feature);
    if (result == FALSE) {
        printf("[hcpptest][error]RegisterFeature fail \n");
        (&g_feature)->featureStatus = FALSE;
    }
    result = SAMGR_GetInstance()->RegisterFeatureApi(SERVICE_NAME, FEATURE_NAME, GET_IUNKNOWN(g_feature));
    if (result == FALSE) {
        printf("[hcpptest][error]RegisterFeatureApi fail \n");
        (&g_feature)->featureStatus = FALSE;
    }
}
SYSEX_FEATURE_INIT(FeatureInit);

class LiteIPCFeatureTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
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
 * @tc.number    : DMSLite_SAMGR_IPCFeature_0010
 * @tc.name      : Feature which cross process should be inited ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(LiteIPCFeatureTest, testIPCFeature0010, TestSize.Level2)
{
    ASSERT_EQ((&g_service)->serviceStatus, TRUE);
    ASSERT_EQ((&g_feature)->featureStatus, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_IPCFeature_0020
 * @tc.name      : Feature which cross process also can be accessed as LPC
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(LiteIPCFeatureTest, testIPCFeature0020, TestSize.Level2)
{
    DemoFeatureApi *demoApi = nullptr;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(SERVICE_NAME, FEATURE_NAME);
    ASSERT_EQ(iUnknown != nullptr, TRUE);

    // DEFAULT_VERSION: means access inside service
    int resultCode = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)&demoApi);
    ASSERT_EQ(resultCode == EC_SUCCESS, TRUE);

    int countBefore = calledCount;
    demoApi->SyncCall((IUnknown *)demoApi);
    int countAfter = calledCount;

    ASSERT_EQ(countAfter - countBefore, 1);
};

/**
 * @tc.number    : DMSLite_SAMGR_IPCFeature_0030
 * @tc.name      : For inside caller, Feature which cross process can not be accessed as IPC
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(LiteIPCFeatureTest, testIPCFeature0030, TestSize.Level2)
{
    IClientProxy *demoApi = nullptr;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(SERVICE_NAME, FEATURE_NAME);
    ASSERT_EQ(iUnknown != nullptr, TRUE);

    // CLIENT_PROXY_VER: means access cross process
    int resultCode = iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, (void **)&demoApi);
    ASSERT_EQ(resultCode != EC_SUCCESS, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_IPCFeature_0040
 * @tc.name      : Feature which cross process can be unregistered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(LiteIPCFeatureTest, testIPCFeature0040, TestSize.Level2)
{
    IUnknown *iUnknown = SAMGR_GetInstance()->UnregisterFeatureApi(SERVICE_NAME, FEATURE_NAME);
    ASSERT_EQ(iUnknown != nullptr, TRUE);

    Feature *feature = SAMGR_GetInstance()->UnregisterFeature(SERVICE_NAME, FEATURE_NAME);
    ASSERT_EQ(feature != nullptr, TRUE);

    Service *service = SAMGR_GetInstance()->UnregisterService(SERVICE_NAME);
    ASSERT_EQ(service != nullptr, TRUE);
};