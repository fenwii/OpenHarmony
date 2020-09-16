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
#include <samgr_maintenance.h>
#include "service.h"
#include "feature.h"
#include "samgr_lite.h"

#define MAINTEN_SERVICE1 "mntn_s1"
#define MAINTEN_SERVICE2 "mntn_s2"
#define MAINTEN_SERVICE3 "mntn_s3"
#define MAINTEN_SERVICE4 "mntn_s4"
#define MAINTEN_FEATURE1 "mntn_f1"
#define MAINTEN_FEATURE2 "mntn_f2"
static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetTaskConfig(Service *service);
static const char *FEATURE_GetName(Feature *feature);
static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity);
static void FEATURE_OnStop(Feature *feature, Identity identity);
static BOOL FEATURE_OnMessage(Feature *feature, Request *request);
Service g_maintenExample1 = {GetName, Initialize, MessageHandle, GetTaskConfig};
Service g_maintenExample2 = {GetName, Initialize, MessageHandle, GetTaskConfig};
Service g_maintenExample3 = {GetName, Initialize, MessageHandle, GetTaskConfig};
Service g_maintenExample4 = {GetName, Initialize, MessageHandle, GetTaskConfig};
Feature g_maintenFeature1 = {FEATURE_GetName, FEATURE_OnInitialize, FEATURE_OnStop, FEATURE_OnMessage};
Feature g_maintenFeature2 = {FEATURE_GetName, FEATURE_OnInitialize, FEATURE_OnStop, FEATURE_OnMessage};
IUnknownEntry g_demoApi = {DEFAULT_IUNKNOWN_ENTRY_BEGIN, DEFAULT_IUNKNOWN_ENTRY_END};

static const char *FEATURE_GetName(Feature *feature)
{
    if (feature == &g_maintenFeature1) {
        return MAINTEN_FEATURE1;
    }
    if (feature == &g_maintenFeature2) {
        return MAINTEN_FEATURE2;
    }
    return NULL;
}

static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    (void)feature;
    (void)parent;
    (void)identity;
}

static void FEATURE_OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
}

static BOOL FEATURE_OnMessage(Feature *feature, Request *request)
{
    (void)feature;
    (void)request;
    return FALSE;
}

static const char *GetName(Service *service)
{
    if (service == &g_maintenExample1) {
        return MAINTEN_SERVICE1;
    }
    if (service == &g_maintenExample2) {
        return MAINTEN_SERVICE2;
    }
    if (service == &g_maintenExample3) {
        return MAINTEN_SERVICE3;
    }
    if (service == &g_maintenExample4) {
        return MAINTEN_SERVICE4;
    }
    return NULL;
}

static BOOL Initialize(Service *service, Identity identity)
{
    (void)identity;
    (void)service;
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    (void)service;
    (void)msg;
    return FALSE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL,
                         0x800, 16, SHARED_TASK};
    if (service == &g_maintenExample4) {
        config.priority = PRI_HIGH;
        config.stackSize = 0x400;
    }
    return config;
}

static void SInit(Service *service)
{
    if (service == &g_maintenExample4) {
        printf("[Maintenance Test][Before App Service Init]Print Uninitialized App Service\n");
        SAMGR_PrintServices();
    }
    SAMGR_GetInstance()->RegisterService(service);
}

static void FInit(Feature *feature)
{
    if (feature == &g_maintenFeature1) {
        SAMGR_GetInstance()->RegisterFeature(MAINTEN_SERVICE1, feature);
        SAMGR_GetInstance()->RegisterFeatureApi(MAINTEN_SERVICE1, MAINTEN_FEATURE1, GET_IUNKNOWN(g_demoApi));
    }
    if (feature == &g_maintenFeature2) {
        SAMGR_GetInstance()->RegisterFeature(MAINTEN_SERVICE2, feature);
        SAMGR_GetInstance()->RegisterDefaultFeatureApi(MAINTEN_SERVICE2, GET_IUNKNOWN(g_demoApi));
    }
}

static void S1Init(void)
{
    SInit(&g_maintenExample1);
}
static void S2Init(void)
{
    SInit(&g_maintenExample2);
}
static void S3Init(void)
{
    SInit(&g_maintenExample3);
}
static void S4Init(void)
{
    SInit(&g_maintenExample4);
}
static void F1Init(void)
{
    FInit(&g_maintenFeature1);
}
static void F2Init(void)
{
    FInit(&g_maintenFeature2);
}

SYSEX_SERVICE_INIT(S1Init);
SYSEX_SERVICE_INIT(S2Init);
SYSEX_SERVICE_INIT(S3Init);
SYSEX_SERVICE_INIT(S4Init);
SYSEX_FEATURE_INIT(F1Init);
SYSEX_FEATURE_INIT(F2Init);
