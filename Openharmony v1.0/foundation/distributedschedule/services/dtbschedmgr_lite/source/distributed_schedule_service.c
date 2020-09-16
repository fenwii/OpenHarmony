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

#include "distributed_schedule_service.h"

#include <pthread.h>

#include "distributed_service_interface.h"
#include "dmslite_log.h"

#include "ohos_init.h"
#include "samgr_lite.h"

#define STACK_SIZE 0x800
#define QUEUE_SIZE 20
#define EMPTY_SERVICE_NAME ""

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *request);
static TaskConfig GetTaskConfig(Service *service);

static DistributedService g_distributedService = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig
};

static const char *GetName(Service *service)
{
    if (service == NULL) {
        return EMPTY_SERVICE_NAME;
    }
    return DISTRIBUTED_SCHEDULE_SERVICE;
}

static BOOL Initialize(Service *service, Identity identity)
{
    if (service == NULL) {
        return FALSE;
    }

    ((DistributedService*) service)->identity = identity;
    (void) pthread_setname_np(pthread_self(), DISTRIBUTED_SCHEDULE_SERVICE);
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *request)
{
    if (request == NULL || service == NULL) {
        return FALSE;
    }

    /* process for a specific service-level msgId can be added below */
    switch (request->msgId) {
        default: {
            HILOGW("[Unkonwn msgId = %d]", request->msgId);
            break;
        }
    }
    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, STACK_SIZE, QUEUE_SIZE, SINGLE_TASK};
    return config;
}

static void Init()
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_distributedService);
    HILOGD("[dms service start success]");
}
SYS_SERVICE_INIT(Init);
