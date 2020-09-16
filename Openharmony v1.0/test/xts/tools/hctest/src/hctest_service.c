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
#include "samgr_lite.h"
#include <hos_init.h>
#include <securec.h>
#include <los_base.h>
#include "service.h"
#include "common.h"
#include "hctest_internal.h"

typedef struct TestService {
    INHERIT_SERVICE;
    Identity identity;
    uint8 flag;
} TestService;

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static BOOL MessageHandle(Service *service, Request *request);
static TaskConfig GetTaskConfig(Service *service);
static void Init(void)
{
    static TestService testService;
    testService.GetName = GetName;
    testService.Initialize = Initialize;
    testService.MessageHandle = MessageHandle;
    testService.GetTaskConfig = GetTaskConfig;
    testService.flag = FALSE;
    SAMGR_GetInstance()->RegisterService((Service *)&testService);
}
SYS_SERVICE_INIT(Init);
static const char *GetName(Service *service)
{
    (void)service;
    return HCTEST_SERVICE;
};

static BOOL Initialize(Service *service, Identity identity)
{
    TestService *testService = (TestService *)service;
    testService->identity = identity;
    Request request = {.msgId = MSG_START_TEST};
    int times = 0;
    while (times < MAXIMUM_TRY_TIMES) {
        int ret = SAMGR_SendRequest(&testService->identity, &request, (Handler)MessageHandle);
        if (ret != 0) {
            times++;
            ret = SAMGR_SendRequest(&testService->identity, &request, (Handler)MessageHandle);
        } else {
            return TRUE;
        }
    }
    return FALSE;
};

static BOOL MessageHandle(Service *service, Request *request)
{
    TestService *testService = (TestService *)service;
    switch (request->msgId) {
        case MSG_START_TEST:
            if ((testService->flag & TEST_FLAG) != TEST_FLAG) {
                INIT_TEST_CALL();
                testService->flag |= TEST_FLAG;
            }
            (void)SAMGR_SendResponseByIdentity(&testService->identity, request, NULL);
            break;
        default:
            break;
    }
    return TRUE;
};

static TaskConfig GetTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_MIDDLE, PRI_NORMAL, 0x1000, 20, SINGLE_TASK};
    (void)service;
    return config;
};
