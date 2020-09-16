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
#include "bootstrap_service.h"
#include <ohos_init.h>
#include "samgr_lite.h"

#define LOAD_FLAG 0x01
typedef struct Bootstrap {
    INHERIT_SERVICE;
    Identity identity;
    uint8 flag;
} Bootstrap;
static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static TaskConfig GetTaskConfig(Service *service);
static BOOL MessageHandle(Service *service, Request *request);

static void Init(void)
{
    static Bootstrap bootstrap;
    bootstrap.GetName = GetName;
    bootstrap.Initialize = Initialize;
    bootstrap.MessageHandle = MessageHandle;
    bootstrap.GetTaskConfig = GetTaskConfig;
    bootstrap.flag = FALSE;
    SAMGR_GetInstance()->RegisterService((Service *)&bootstrap);
}
SYS_SERVICE_INIT(Init);

static const char *GetName(Service *service)
{
    (void)service;
    return BOOTSTRAP_SERVICE;
}

static BOOL Initialize(Service *service, Identity identity)
{
    Bootstrap *bootstrap = (Bootstrap *)service;
    bootstrap->identity = identity;
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *request)
{
    Bootstrap *bootstrap = (Bootstrap *)service;
    switch (request->msgId) {
        case BOOT_SYS_COMPLETED:
            if ((bootstrap->flag & LOAD_FLAG) != LOAD_FLAG) {
                INIT_APP_CALL(service);
                INIT_APP_CALL(feature);
                bootstrap->flag |= LOAD_FLAG;
            }
            (void)SAMGR_SendResponseByIdentity(&bootstrap->identity, request, NULL);
            break;

        case BOOT_APP_COMPLETED:
            (void)SAMGR_SendResponseByIdentity(&bootstrap->identity, request, NULL);
            break;

        case BOOT_REG_SERVICE:
            (void)SAMGR_SendResponseByIdentity(&bootstrap->identity, request, NULL);
            break;

        default:
            break;
    }
    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    // The bootstrap service uses a stack of 2 KB (0x800) in size and a queue of 20 elements.
    // You can adjust it according to the actual situation.
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 0x800, 20, SHARED_TASK};
    return config;
}
