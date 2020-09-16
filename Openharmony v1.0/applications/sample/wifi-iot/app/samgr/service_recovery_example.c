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
#include <los_base.h>
#include <securec.h>
#include <ohos_init.h>
#include <cmsis_os.h>
#include "service.h"
#include "samgr_lite.h"

#define TIME_UNLIMITED_CASE 0
#define WAIT_BOOT_PROC ((1000) * (11))
#define TEST_SYS_SERVICE1 "tst_sys1"
#define TEST_SYS_SERVICE2 "tst_sys2"
#define TEST_APP_SERVICE1 "tst_app1"
#define TEST_APP_SERVICE2 "tst_app2"
static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *msg);
static TaskConfig GetTaskConfig(Service *service);
static Service g_testSys1 = {GetName, Initialize, MessageHandle, GetTaskConfig};
static Service g_testSys2 = {GetName, Initialize, MessageHandle, GetTaskConfig};
static Service g_testApp1 = {GetName, Initialize, MessageHandle, GetTaskConfig};
static Service g_testApp2 = {GetName, Initialize, MessageHandle, GetTaskConfig};

static const char *GetName(Service *service)
{
    if (service == &g_testSys1) {
        return TEST_SYS_SERVICE1;
    }
    if (service == &g_testSys2) {
        return TEST_SYS_SERVICE2;
    }
    if (service == &g_testApp1) {
        return TEST_APP_SERVICE1;
    }
    if (service == &g_testApp2) {
        return TEST_APP_SERVICE2;
    }
    return NULL;
}

static BOOL Initialize(Service *service, Identity identity)
{
    (void)identity;
    if (service == &g_testSys1 || service == &g_testApp1) {
        printf("[Recovery Test][Initialize]Time Out Case Running\n");
        LOS_Msleep(WAIT_BOOT_PROC);
        return TRUE;
    }
#if TIME_UNLIMITED_CASE
    if (service == &g_testSys2 || service == &g_testApp2) {
        printf("[Recovery Test][Initialize]Time Unlimited Case Running\n\n");
        while (1) {
            (void)identity;
        }
        return TRUE;
    }
#endif
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
                         0x400, 16, SHARED_TASK};
    return config;
}

static void SInit(Service *demo)
{
    SAMGR_GetInstance()->RegisterService(demo);
}

static void SS1Init(void)
{
    SInit(&g_testSys1);
}
static void SS2Init(void)
{
    SInit(&g_testSys2);
}
static void AS1Init(void)
{
    SInit(&g_testApp1);
}
static void AS2Init(void)
{
    SInit(&g_testApp2);
}
SYS_SERVICE_INIT(SS1Init);
SYS_SERVICE_INIT(SS2Init);
SYSEX_SERVICE_INIT(AS1Init);
SYSEX_SERVICE_INIT(AS2Init);