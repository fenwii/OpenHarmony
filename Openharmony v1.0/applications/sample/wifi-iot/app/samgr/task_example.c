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
#include <feature.h>
#include <securec.h>
#include <ohos_init.h>
#include <samgr_lite.h>
#include <cmsis_os.h>

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetTaskConfig(Service *service);
static Service g_example[] = {
    {GetName, Initialize, MessageHandle, GetTaskConfig},
    {GetName, Initialize, MessageHandle, GetTaskConfig},
    {GetName, Initialize, MessageHandle, GetTaskConfig},
    {GetName, Initialize, MessageHandle, GetTaskConfig}
};
static int g_initIndex = 0;
static const char *GetName(Service *service)
{
    // test cases demo 0
    if (service == &g_example[0]) {
        return TASK_SERVICE1;
    }
    // test cases demo 1
    if (service == &g_example[1]) {
        return TASK_SERVICE2;
    }
    // test cases demo 2
    if (service == &g_example[2]) {
        return TASK_SERVICE3;
    }
    // test cases demo 3
    if (service == &g_example[3]) {
        return TASK_SERVICE4;
    }
    return NULL;
}

static BOOL Initialize(Service *service, Identity identity)
{
    (void)identity;
    printf("[Task Test][TaskID:%p][Step:%d][Reg Finish S:%s]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, service->GetName(service), SAMGR_GetProcessTime());
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    printf("[Task Test][TaskID:%p][Step:%d][S:%s] msgId<%d> \n",
           osThreadGetId(), g_initIndex++, service->GetName(service), msg->msgId);
    return FALSE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL,
                         0x800, 5, SHARED_TASK};
    // test cases demo 0
    if (service == &g_example[0]) {
        config.taskFlags = SINGLE_TASK;
    }
    // test cases demo 3
    if (service == &g_example[3]) {
        config.priority = PRI_ABOVE_NORMAL;
    }
    return config;
}

static void SInit(Service *demo)
{
    SAMGR_GetInstance()->RegisterService(demo);

    printf("[Task Test][TaskID:%p][Step:%d][SYSEX Reg S:%s]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, demo->GetName(demo), SAMGR_GetProcessTime());
}
static void S1Init(void)
{
    // test cases demo 0
    SInit(&g_example[0]);
}
static void S2Init(void)
{
    // test cases demo 1
    SInit(&g_example[1]);
}
static void S3Init(void)
{
    // test cases demo 2
    SInit(&g_example[2]);
}
static void S4Init(void)
{
    // test cases demo 3
    SInit(&g_example[3]);
}
SYSEX_SERVICE_INIT(S1Init);
SYSEX_SERVICE_INIT(S2Init);
SYSEX_SERVICE_INIT(S3Init);
SYSEX_SERVICE_INIT(S4Init);
