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

#include "ability_mgr_service.h"

#include <pthread.h>

#include "ability_service_interface.h"
#include "adapter.h"
#include "hos_init.h"
#include "samgr_lite.h"
#include "util/abilityms_log.h"

namespace OHOS {
const int STACK_SIZE = 0x800;
const int QUEUE_SIZE = 20;

AbilityMgrService::AbilityMgrService() : Service(), identity_()
{
    this->Service::GetName = AbilityMgrService::GetServiceName;
    this->Service::Initialize = AbilityMgrService::ServiceInitialize;
    this->Service::MessageHandle = AbilityMgrService::ServiceMessageHandle;
    this->Service::GetTaskConfig = AbilityMgrService::GetServiceTaskConfig;
}

static void Init()
{
    SamgrLite *sm = SAMGR_GetInstance();
    CHECK_NULLPTR_RETURN(sm, "AbilityManagerService", "get samgr error");
    BOOL result = sm->RegisterService(AbilityMgrService::GetInstance());
    PRINTI("AbilityManagerService", "ams start result is %{public}s", result ? "successfully" : "failure");
}
SYSEX_SERVICE_INIT(Init);

const char *AbilityMgrService::GetServiceName(Service *service)
{
    (void)service;
    return AMS_SERVICE;
}

BOOL AbilityMgrService::ServiceInitialize(Service *service, Identity identity)
{
    if (service == nullptr) {
        return FALSE;
    }
    AbilityMgrService *abilityManagerService = static_cast<AbilityMgrService *>(service);
    abilityManagerService->identity_ = identity;
    return TRUE;
}

BOOL AbilityMgrService::ServiceMessageHandle(Service *service, Request *request)
{
    if (request == nullptr) {
        return FALSE;
    }

    return TRUE;
}

TaskConfig AbilityMgrService::GetServiceTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, STACK_SIZE, QUEUE_SIZE, SINGLE_TASK};
    return config;
}
} // namespace OHOS
