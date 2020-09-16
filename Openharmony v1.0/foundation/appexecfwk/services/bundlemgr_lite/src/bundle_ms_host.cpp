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

#include "bundle_ms_host.h"

#include <pthread.h>

#include "bundle_inner_interface.h"
#include "bundle_manager_service.h"
#include "hos_init.h"
#include "log.h"
#include "samgr_lite.h"

namespace OHOS {
const int STACK_SIZE = 0x800;
const int QUEUE_SIZE = 20;

BundleMsHost::BundleMsHost() : Service()
{
    this->Service::GetName = BundleMsHost::GetServiceName;
    this->Service::Initialize = BundleMsHost::ServiceInitialize;
    this->Service::MessageHandle = BundleMsHost::ServiceMessageHandle;
    this->Service::GetTaskConfig = BundleMsHost::GetServiceTaskConfig;
}

static void Init()
{
    SamgrLite *sm = SAMGR_GetInstance();
    sm->RegisterService(reinterpret_cast<Service *>(BundleMsHost::GetInstance()));
    HILOG_DEBUG(HILOG_MODULE_APP, "BundleMS start success");
}
APP_SERVICE_INIT(Init);

const char *BundleMsHost::GetServiceName(Service *service)
{
    (void)service;
    return BMS_SERVICE;
}

BOOL BundleMsHost::ServiceInitialize(Service *service, Identity identity)
{
    if (service == nullptr) {
        return FALSE;
    }

    BundleMsHost *bundleMsHost = reinterpret_cast<BundleMsHost *>(service);
    bundleMsHost->identity_ = identity;
    return TRUE;
}

BOOL BundleMsHost::ServiceMessageHandle(Service *service, Request *request)
{
    if (request == nullptr) {
        return FALSE;
    }
    return TRUE;
}

TaskConfig BundleMsHost::GetServiceTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, STACK_SIZE, QUEUE_SIZE, SINGLE_TASK};
    return config;
}
} // namespace OHOS
