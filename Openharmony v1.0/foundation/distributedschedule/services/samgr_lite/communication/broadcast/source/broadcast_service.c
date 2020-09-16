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

#include "broadcast_service.h"
#include "ohos_init.h"
#include "common.h"
#include "samgr_lite.h"
#include "thread_adapter.h"
#include "pub_sub_feature.h"
static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static TaskConfig GetTaskConfig(Service *service);
static BOOL MessageHandle(Service *service, Request *request);
static BroadcastService g_broadcastService = {
    GetName,
    Initialize,
    MessageHandle,
    GetTaskConfig,
};

static void Init(void)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_broadcastService);
}
SYS_SERVICE_INIT(Init);

static const char *GetName(Service *service)
{
    (void)service;
    return BROADCAST_SERVICE;
}

static BOOL Initialize(Service *service, Identity identity)
{
    (void)identity;
    if (service == NULL) {
        return FALSE;
    }
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *request)
{
    (void)service;
    switch (request->msgId) {
        case BROADCAST_MSG:
            break;
        default:
            break;
    }
    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {LEVEL_HIGH, PRI_ABOVE_NORMAL, 0x800, 40, SPECIFIED_TASK};
    return config;
}
