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

#include "hos_init.h"
#include "samgr_lite.h"
#include "service.h"
#include "common.h"
#include "hiview_def.h"
#include "hiview_config.h"
#include "hiview_log.h"
#include "hiview_service.h"

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static TaskConfig GetTaskConfig(Service *service);
static BOOL MessageHandle(Service *service, Request *request);
static void Output(IUnknown *iUnknown, int16 msgId, uint16 type);

static HiviewService g_hiviewService = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    DEFAULT_IUNKNOWN_ENTRY_BEGIN,
    .Output = Output,
    DEFAULT_IUNKNOWN_ENTRY_END,
};

static HiviewInitFunc g_hiviewInitFuncList[HIVIEW_CMP_TYPE_MAX] = { NULL };
static HiviewMsgHandle g_hiviewMsgHandleList[HIVIEW_MSG_MAX] = { NULL };
static void InitHiviewComponent(void);

static void Init(void)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_hiviewService);
    SAMGR_GetInstance()->RegisterDefaultFeatureApi(HIVIEW_SERVICE, GET_IUNKNOWN(g_hiviewService));
    InitHiviewComponent();
}
SYS_SERVICE_INIT(Init);

static const char *GetName(Service *service)
{
    (void)service;
    return HIVIEW_SERVICE;
}

static BOOL Initialize(Service *service, Identity identity)
{
    HiviewService *hiviewService = NULL;

    if (service == NULL) {
        return FALSE;
    }
    hiviewService = (HiviewService *)service;
    hiviewService->identity = identity;
    /* The communication of task can be use after the service is running. */
    g_hiviewConfig.hiviewInited = TRUE;
    HILOG_DEBUG(HILOG_MODULE_HIVIEW, "hiview init success.");

    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *request)
{
    (void)service;
    if ((request == NULL) || (request->msgId >= HIVIEW_MSG_MAX)) {
        return TRUE;
    }
    if (g_hiviewMsgHandleList[request->msgId] != NULL) {
        (*(g_hiviewMsgHandleList[request->msgId]))(request);
    }

    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = { LEVEL_LOW, PRI_NORMAL, 0x800, 10, SINGLE_TASK };
    return config;
}

static void Output(IUnknown *iUnknown, int16 msgId, uint16 type)
{
    HiviewService *service = GET_OBJECT(iUnknown, HiviewService, iUnknown);
    Request request = {
        .msgId =  msgId,
        .msgValue = type,
        .data = NULL,
        .len = 0
    };
    SAMGR_SendRequest(&(service->identity), &request, NULL);
}

static void InitHiviewComponent(void)
{
    uint8 i;
    for (i = 0; i < HIVIEW_CMP_TYPE_MAX; i++) {
        if (g_hiviewInitFuncList[i] != NULL) {
            (*(g_hiviewInitFuncList[i]))();
        }
    }
}

void HiviewRegisterInitFunc(HiviewComponentType type, HiviewInitFunc func)
{
    g_hiviewInitFuncList[type] = func;
}

void HiviewRegisterMsgHandle(HiviewInnerMessage type, HiviewMsgHandle func)
{
    g_hiviewMsgHandleList[type] = func;
}

void HiviewSendMessage(const char *srvName, int16 msgId, uint16 msgValue)
{
    static HiviewInterface *hiviewInfterface = NULL;

    if (hiviewInfterface == NULL) {
        IUnknown *hiviewDefApi = SAMGR_GetInstance()->GetDefaultFeatureApi(srvName);
        if (hiviewDefApi == NULL) {
            return;
        }
        hiviewDefApi->QueryInterface(hiviewDefApi, 0, (void **)&hiviewInfterface);
    }
    hiviewInfterface->Output((IUnknown *)hiviewInfterface, msgId, msgValue);
}