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

static const char *SERVICE_NAME = {"ipcService01"};

static int calledCount = 0;
struct DefaultFeatureApi {
    INHERIT_SERVER_IPROXY;
    void (*SyncCall)(IUnknown *iUnknown);
};

struct DemoService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
    BOOL serviceStatus;
};

static const char *GetName(Service *service)
{
    (void)service;
    return SERVICE_NAME;
}
static const char *GetName2(Service *service)
{
    (void)service;
    return "samgr";
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
    printf("[hcpptest][TID:0x%lx]MessageHandle(%s)! Request<%d, %d, %p>",
           pthread_self(), service->GetName(service), msg->msgId, msg->msgValue, msg->data);
    return FALSE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {LEVEL_HIGH, PRI_BELOW_NORMAL, 0x800, 20, SHARED_TASK};
    return config;
}
static void SyncCall(IUnknown *iUnknown)
{
    calledCount++;
}
static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    printf("[hcpptest][TID:0x%lx]Service Remote Invoke is called! <%p, %d, %p, %p, %p>",
           pthread_self(), iProxy, funcId, origin, req, reply);

    size_t len = 0;
    char *requestStr = (char *)IpcIoPopString(req, &len);
    if (requestStr != nullptr) {
        printf("[hcpptest]requestStr is %s", requestStr);
    } else {
        printf("[hcpptest]requestStr is NULL");
    }
    
    DefaultFeatureApi *defaultApi = (DefaultFeatureApi *)iProxy;
    if (funcId == 0) {
        defaultApi->SyncCall((IUnknown *)iProxy);
    }

    IpcIoPushString(reply, "Yes, you did!");
    return EC_SUCCESS;
}
static DemoService g_service = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = Invoke,
    .SyncCall = SyncCall,
    IPROXY_END,
    .identity = {-1, -1, nullptr},
    .serviceStatus = FALSE,
};

static DemoService g_service2 = {
    .GetName = GetName2,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = Invoke,
    .SyncCall = SyncCall,
    IPROXY_END,
    .identity = {-1, -1, nullptr},
    .serviceStatus = FALSE,
};

static void ServiceInit(void)
{
    BOOL result1 = SAMGR_GetInstance()->RegisterService((Service *)&g_service);
    BOOL result2 = SAMGR_GetInstance()->RegisterDefaultFeatureApi(SERVICE_NAME, GET_IUNKNOWN(g_service));
    if (result1 == FALSE || result2 == FALSE) {
        printf("[hcpptest][error]RegisterService or register api fail \n");
        (&g_service)->serviceStatus = FALSE;
    }
}
SYSEX_SERVICE_INIT(ServiceInit);

static IClientProxy *getRemoteIUnknown(const char *serviceName, const char *featureName)
{
    IClientProxy *demoApi = nullptr;
    IUnknown *iUnknown = nullptr;
    if (featureName == nullptr) {
        iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(serviceName);
    } else {
        iUnknown = SAMGR_GetInstance()->GetFeatureApi(serviceName, featureName);
    }

    if (iUnknown == nullptr) {
        printf("[hcpptest]failed to get api\n");
    }
    int resultCode = iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, (void **)&demoApi);
    if (resultCode != EC_SUCCESS) {
        printf("[hcpptest][error]fail to QueryInterface and returnCode: %d\n", resultCode);
    }
    return demoApi;
}

static void ReleaseIUnknown(IUnknown *demoApi)
{
    if (demoApi != NULL) {
        demoApi->Release((IUnknown *)demoApi);
    }
}

class LiteIPCServiceTest : public testing::Test {
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
 * @tc.number    : DMSLite_SAMGR_IPCService_0010
 * @tc.name      : Service which cross processes is registered ok
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
*/
HWTEST_F(LiteIPCServiceTest, testIPCService0010, TestSize.Level1)
{
    ASSERT_EQ((&g_service)->serviceStatus, TRUE);
    ASSERT_EQ((&g_service)->identity.serviceId != -1, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_IPCService_0020
 * @tc.name      : Service which cross process also can be accessed as LPC
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(LiteIPCServiceTest, testIPCService0020, TestSize.Level2)
{
    DefaultFeatureApi *demoApi = nullptr;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(SERVICE_NAME);
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
 * @tc.number    : DMSLite_SAMGR_IPCService_0030
 * @tc.name      : For inside caller, Service which cross process can not be accessed as IPC
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(LiteIPCServiceTest, testIPCService0030, TestSize.Level2)
{
    IClientProxy *demoApi = nullptr;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(SERVICE_NAME);
    ASSERT_EQ(iUnknown != nullptr, TRUE);

    // CLIENT_PROXY_VER: means access other process
    int resultCode = iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, (void **)&demoApi);
    ASSERT_EQ(resultCode != EC_SUCCESS, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_IPCService_0040
 * @tc.name      : Service which cross process can be unregistered
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(LiteIPCServiceTest, testIPCService0040, TestSize.Level2)
{
    IUnknown *iUnknown = SAMGR_GetInstance()->UnregisterDefaultFeatureApi(SERVICE_NAME);
    ASSERT_EQ(iUnknown != nullptr, TRUE);

    Service *service = SAMGR_GetInstance()->UnregisterService(SERVICE_NAME);
    ASSERT_EQ(service != nullptr, TRUE);
};

/**
 * @tc.number    : DMSLite_SAMGR_IPCService_0050
 * @tc.name      : User can not unregister service belong to other process
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(LiteIPCServiceTest, testIPCService0050, TestSize.Level2)
{
    // samgr belong foundation process
    IUnknown *iUnknown = SAMGR_GetInstance()->UnregisterDefaultFeatureApi("samgr");
    ASSERT_EQ(iUnknown == nullptr, TRUE);
};