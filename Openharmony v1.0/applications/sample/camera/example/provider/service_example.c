/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "example.h"
#include <ohos_init.h>
#include <pthread.h>
#include <log.h>
#include <ohos_errno.h>
#include "iproxy_server.h"
#include "feature.h"
#include "service.h"
#include "samgr_lite.h"

typedef struct ExampleService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
} ExampleService;

static const char *GetName(Service *service)
{
    (void)service;
    return EXAMPLE_SERVICE;
}
static BOOL Initialize(Service *service, Identity identity)
{
    ExampleService *example = (ExampleService *)service;
    example->identity = identity;
    HILOG_DEBUG(HILOG_MODULE_APP, "[TID:0x%lx]Initialize(%s)! Identity<%d, %d, %p>", (unsigned long)pthread_self(),
                EXAMPLE_SERVICE, identity.serviceId, identity.featureId, identity.queueId);
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]MessageHandle(%s)! Request<%d, %d, %p>",
               (unsigned long)pthread_self(), service->GetName(service), msg->msgId, msg->msgValue, msg->data);
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
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]SyncCall is called! iUnknown[%p]",
               (unsigned long)pthread_self(), iUnknown);
}
static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]Service Remote Invoke is called! <%p, %d, %p, %p, %p>",
               (unsigned long)pthread_self(), iProxy, funcId, origin, req, reply);
    DefaultFeatureApi *defaultApi = (DefaultFeatureApi *)iProxy;
    if (funcId == 0) {
        defaultApi->SyncCall((IUnknown *)iProxy);
    }
    return EC_SUCCESS;
}
static ExampleService g_example = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = Invoke,
    .SyncCall = SyncCall,
    IPROXY_END,
};

static void Init(void)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_example);
    SAMGR_GetInstance()->RegisterDefaultFeatureApi(EXAMPLE_SERVICE, GET_IUNKNOWN(g_example));
}
SYSEX_SERVICE_INIT(Init);
