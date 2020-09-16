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

typedef struct BootTestExample {
    Service service;
    Feature feature;
} BootTestExample;
static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetTaskConfig(Service *service);
static const char *FEATURE_GetName(Feature *feature);
static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity);
static void FEATURE_OnStop(Feature *feature, Identity identity);
static BOOL FEATURE_OnMessage(Feature *feature, Request *request);
static BootTestExample g_example[] = {
    {
        .service = {GetName, Initialize, MessageHandle, GetTaskConfig},
        .feature = {FEATURE_GetName, FEATURE_OnInitialize, FEATURE_OnStop, FEATURE_OnMessage}
    }, {
        .service = {GetName, Initialize, MessageHandle, GetTaskConfig},
        .feature = {FEATURE_GetName, FEATURE_OnInitialize, FEATURE_OnStop, FEATURE_OnMessage}
    }, {
        .service = {GetName, Initialize, MessageHandle, GetTaskConfig},
        .feature = {FEATURE_GetName, FEATURE_OnInitialize, FEATURE_OnStop, FEATURE_OnMessage}
    }, {
        .service = {GetName, Initialize, MessageHandle, GetTaskConfig},
        .feature = {FEATURE_GetName, FEATURE_OnInitialize, FEATURE_OnStop, FEATURE_OnMessage}
    }
};
static int g_initIndex = 0;
static const char *FEATURE_GetName(Feature *feature)
{
    // test cases service 0
    if (feature == &g_example[0].feature) {
        return BOOT_SYS_FEATURE1;
    }
    // test cases service 1
    if (feature == &g_example[1].feature) {
        return BOOT_SYS_FEATURE2;
    }
    // test cases service 2
    if (feature == &g_example[2].feature) {
        return BOOT_SYSEX_FEATURE1;
    }
    // test cases service 3
    if (feature == &g_example[3].feature) {
        return BOOT_SYSEX_FEATURE2;
    }
    return NULL;
}

static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    (void)identity;
    printf("[Boot Test][TaskID:%p][Step:%d][Reg Finish S:%s, F:%s]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, parent->GetName(parent), feature->GetName(feature), SAMGR_GetProcessTime());
}

static void FEATURE_OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
}

static BOOL FEATURE_OnMessage(Feature *feature, Request *request)
{
    printf("[Boot Test][TaskID:%p][Step:%d][F:%s] msgId<%d> \n",
           osThreadGetId(), g_initIndex++, feature->GetName(feature), request->msgId);
    return FALSE;
}

static const char *GetName(Service *service)
{
    // test cases service 0
    if (service == &g_example[0].service) {
        return BOOT_SYS_SERVICE1;
    }
    // test cases service 1
    if (service == &g_example[1].service) {
        return BOOT_SYS_SERVICE2;
    }
    // test cases service 2
    if (service == &g_example[2].service) {
        return BOOT_SYSEX_SERVICE1;
    }
    // test cases service 3
    if (service == &g_example[3].service) {
        return BOOT_SYSEX_SERVICE2;
    }
    return NULL;
}

static BOOL Initialize(Service *service, Identity identity)
{
    (void)identity;
    printf("[Boot Test][TaskID:%p][Step:%d][Reg Finish S:%s]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, service->GetName(service), SAMGR_GetProcessTime());
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    printf("[Boot Test][TaskID:%p][Step:%d][S:%s] msgId<%d> \n",
           osThreadGetId(), g_initIndex++, service->GetName(service), msg->msgId);
    return FALSE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {LEVEL_HIGH, PRI_ABOVE_NORMAL,
                         0x400, 2, SHARED_TASK};
    return config;
}
static void MInit(void)
{
    printf("[Boot Test][TaskID:%p][Step:%d][CORE INIT]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, SAMGR_GetProcessTime());
}
static void MRun(void)
{
    printf("[Boot Test][TaskID:%p][Step:%d][SYS RUN]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, SAMGR_GetProcessTime());
}
static void SInit(BootTestExample *demo)
{
    SAMGR_GetInstance()->RegisterService(&demo->service);

    // test cases service 2
    printf((demo < &g_example[2]) ?
           "[Boot Test][TaskID:%p][Step:%d][SYS Reg S:%s]Time: %llu!\n" :
           "[Boot Test][TaskID:%p][Step:%d][SYSEX Reg S:%s]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, demo->service.GetName(&demo->service), SAMGR_GetProcessTime());
}
static void FInit(BootTestExample *demo)
{
    SAMGR_GetInstance()->RegisterFeature(demo->service.GetName(&demo->service), &demo->feature);

    // test cases service 2
    printf((demo < &g_example[2]) ?
           "[Boot Test][TaskID:%p][Step:%d][SYS Reg S:%s, F:%s]Time: %llu!\n" :
           "[Boot Test][TaskID:%p][Step:%d][SYSEX Reg S:%s, F:%s]Time: %llu!\n",
           osThreadGetId(), g_initIndex++, demo->service.GetName(&demo->service), demo->feature.GetName(&demo->feature),
           SAMGR_GetProcessTime());
}
static void S1Init(void)
{
    // test cases service 0
    SInit(&g_example[0]);
}
static void S2Init(void)
{
    // test cases service 1
    SInit(&g_example[1]);
}
static void F1Init(void)
{
    // test cases feature 0
    FInit(&g_example[0]);
}
static void F2Init(void)
{
    // test cases feature 1
    FInit(&g_example[1]);
}
static void S3Init(void)
{
    // test cases service 2
    SInit(&g_example[2]);
}
static void S4Init(void)
{
    // test cases service 3
    SInit(&g_example[3]);
}
static void F3Init(void)
{
    // test cases feature 2
    FInit(&g_example[2]);
}
static void F4Init(void)
{
    // test cases feature 3
    FInit(&g_example[3]);
}
CORE_INIT(MInit);
SYS_RUN(MRun);
// init pri first
SYS_SERVICE_INIT_PRI(S1Init, 0);
// init pri second
SYS_SERVICE_INIT_PRI(S2Init, 1);
// init pri first
SYS_FEATURE_INIT_PRI(F1Init, 0);
// init pri second
SYS_FEATURE_INIT_PRI(F2Init, 1);
// init pri first
SYSEX_SERVICE_INIT_PRI(S3Init, 0);
// init pri second
SYSEX_SERVICE_INIT_PRI(S4Init, 1);
// init pri first
SYSEX_FEATURE_INIT_PRI(F3Init, 0);
// init pri second
SYSEX_FEATURE_INIT_PRI(F4Init, 1);
