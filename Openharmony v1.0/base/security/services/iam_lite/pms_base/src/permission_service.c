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

#include "permission_service.h"

#include <ohos_init.h>

#include "log.h"

#include "samgr_lite.h"
#include "service.h"

#define STACK_SIZE 0x800
#define QUEUE_SIZE 20

static void Init();
static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static TaskConfig GetTaskConfig(Service *service);
static BOOL MessageHandle(Service *service, Request *request);

static PermissionService g_permissionService = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    .identity = {-1, -1, NULL}
};

static void Init()
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_permissionService);
    HILOG_INFO(HILOG_MODULE_APP, "Init pms service success");
}
APP_SERVICE_INIT(Init);

static const char *GetName(Service *service)
{
    (void)service;
    return PERMISSION_SERVICE;
}

static BOOL Initialize(Service *service, Identity identity)
{
    PermissionService *pms = (PermissionService *)service;
    pms->identity = identity;
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *request)
{
    (void)service;
    if (request == NULL) {
        return FALSE;
    }
    return FALSE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, STACK_SIZE, QUEUE_SIZE, SINGLE_TASK};
    return config;
}
