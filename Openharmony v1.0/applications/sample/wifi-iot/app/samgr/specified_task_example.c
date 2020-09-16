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

#include <securec.h>
#include <ohos_init.h>
#include <cmsis_os.h>
#include "service.h"
#include "samgr_lite.h"

#define TOTAL_SPEC_TASK_NUM 19
static const char *g_specTaskService[] = {
    "ltsk_s1", "ltsk_s2", "ltsk_s3",
    "otsk_s1", "otsk_s2", "otsk_s3", "otsk_s4",
    "otsk_s5", "otsk_s6", "otsk_s7", "otsk_s8",
    "otsk_s9", "otsk_s10", "otsk_s11", "otsk_s12",
    "otsk_s13", "otsk_s14", "otsk_s15", "otsk_s16",
};
static const char *g_specServiceName1[] = {
    "l6tsk_s1", "l6tsk_s2"
};
static const char *g_specServiceName2[] = {
    "l7tsk_s1", "l7tsk_s2", "l7tsk_s3"
};
static const char *g_specServiceName3[] = {
    "l8tsk_s1", "l8tsk_s2", "l8tsk_s3", "l8tsk_s4"
};
static const char *GetName(Service *service);
static const char *GetSpec1Name(Service *service);
static const char *GetSpec2Name(Service *service);
static const char *GetSpec3Name(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetLowTagTaskConfig(Service *service);
static TaskConfig GetHighTagTaskConfig(Service *service);
static TaskConfig GetSpec1TagTaskConfig(Service *service);
static TaskConfig GetSpec2TagTaskConfig(Service *service);
static TaskConfig GetSpec3TagTaskConfig(Service *service);
static Service g_example[] = {
    {GetName, Initialize, MessageHandle, GetLowTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetLowTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetLowTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig},
    {GetName, Initialize, MessageHandle, GetHighTagTaskConfig}
};
static Service g_exampleSpec1[] = {
    {GetSpec1Name, Initialize, MessageHandle, GetSpec1TagTaskConfig},
    {GetSpec1Name, Initialize, MessageHandle, GetSpec1TagTaskConfig}
};
static Service g_exampleSpec2[] = {
    {GetSpec2Name, Initialize, MessageHandle, GetSpec2TagTaskConfig},
    {GetSpec2Name, Initialize, MessageHandle, GetSpec2TagTaskConfig},
    {GetSpec2Name, Initialize, MessageHandle, GetSpec2TagTaskConfig}
};
static Service g_exampleSpec3[] = {
    {GetSpec3Name, Initialize, MessageHandle, GetSpec3TagTaskConfig},
    {GetSpec3Name, Initialize, MessageHandle, GetSpec3TagTaskConfig},
    {GetSpec3Name, Initialize, MessageHandle, GetSpec3TagTaskConfig},
    {GetSpec3Name, Initialize, MessageHandle, GetSpec3TagTaskConfig}
};
static int g_initIndex = 0;

static const char *GetName(Service *service)
{
    int i;
    for (i = 0; i < TOTAL_SPEC_TASK_NUM; ++i) {
        if (service == &g_example[i]) {
            return g_specTaskService[i];
        }
    }
    return NULL;
}

static const char *GetSpec1Name(Service *service)
{
    int i;
    // g_exampleSpec1 has 2 services
    for (i = 0; i < 2; ++i) {
        if (service == &g_exampleSpec1[i]) {
            return g_specServiceName1[i];
        }
    }
    return NULL;
}

static const char *GetSpec2Name(Service *service)
{
    int i;
    // g_exampleSpec2 has 3 services
    for (i = 0; i < 3; ++i) {
        if (service == &g_exampleSpec2[i]) {
            return g_specServiceName2[i];
        }
    }
    return NULL;
}

static const char *GetSpec3Name(Service *service)
{
    int i;
    // g_exampleSpec3 has 4 services
    for (i = 0; i < 4; ++i) {
        if (service == &g_exampleSpec3[i]) {
            return g_specServiceName3[i];
        }
    }
    return NULL;
}

static BOOL Initialize(Service *service, Identity identity)
{
    (void)identity;
    printf("[Specified Task Test][TaskID:%p][Step:%d][Reg Finish S:%s]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, service->GetName(service), SAMGR_GetProcessTime());
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    printf("[Specified Task Test][TaskID:%p][Step:%d][S:%s] msgId<%d> \n",
           osThreadGetId(), g_initIndex++, service->GetName(service), msg->msgId);
    return FALSE;
}

static TaskConfig GetLowTagTaskConfig(Service *service)
{
    (void)service;
    int16 customLevelLow = LEVEL_CUSTOM_BEGIN + 1;
    TaskConfig config = {customLevelLow, PRI_NORMAL,
                         0x400, 16, SPECIFIED_TASK};
    return config;
}

static TaskConfig GetHighTagTaskConfig(Service *service)
{
    (void)service;
    int16 customLevelHigh = LEVEL_CUSTOM_BEGIN + 2; // Custom level 2
    TaskConfig config = {customLevelHigh, PRI_NORMAL,
                         0x400, 16, SPECIFIED_TASK};
    return config;
}

static TaskConfig GetSpec1TagTaskConfig(Service *service)
{
    (void)service;
    int16 customLevelSpec1 = LEVEL_CUSTOM_BEGIN + 3; // Custom level 3
    TaskConfig config = {customLevelSpec1, PRI_NORMAL,
                         0x400, 16, SPECIFIED_TASK};
    return config;
}

static TaskConfig GetSpec2TagTaskConfig(Service *service)
{
    (void)service;
    int16 customLevelSpec2 = LEVEL_CUSTOM_BEGIN + 4; // Custom level 4
    TaskConfig config = {customLevelSpec2, PRI_NORMAL,
                         0x400, 16, SPECIFIED_TASK};
    return config;
}

static TaskConfig GetSpec3TagTaskConfig(Service *service)
{
    (void)service;
    int16 customLevelSpec3 = LEVEL_CUSTOM_BEGIN + 5; // Custom level 5
    TaskConfig config = {customLevelSpec3, PRI_NORMAL,
                         0x400, 16, SPECIFIED_TASK};
    return config;
}

static void SInit(Service *demo)
{
    SAMGR_GetInstance()->RegisterService(demo);

    printf("[Specified Task Test][TaskID:%p][Step:%d][SYSEX Reg S:%s]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, demo->GetName(demo), SAMGR_GetProcessTime());
}
static void SSInit(void)
{
    int i;
    for (i = 0; i < TOTAL_SPEC_TASK_NUM; ++i) {
        SInit(&g_example[i]);
    }

    // g_exampleSpec1 has 2 services
    for (i = 0; i < 2; ++i) {
        SInit(&g_exampleSpec1[i]);
    }
    // g_exampleSpec2 has 3 services
    for (i = 0; i < 3; ++i) {
        SInit(&g_exampleSpec2[i]);
    }
    // g_exampleSpec3 has 4 services
    for (i = 0; i < 4; ++i) {
        SInit(&g_exampleSpec3[i]);
    }
}
SYSEX_SERVICE_INIT(SSInit);