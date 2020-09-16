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
#include <iproxy_client.h>
#include <samgr_lite.h>
#include <log.h>
#include <pthread.h>

#define MAX_DATA_LEN 250
static IClientProxy *CASE_GetRemoteIUnknown(void)
{
    IClientProxy *demoApi = NULL;
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][GetDefaultFeatureApi S:%s]: BEGIN",
               (unsigned long)pthread_self(), EXAMPLE_SERVICE);
    IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(EXAMPLE_SERVICE);
    if (iUnknown == NULL) {
        HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][GetDefaultFeatureApi S:%s]: error is NULL",
                   (unsigned long)pthread_self(), EXAMPLE_SERVICE);
        return NULL;
    }
    (void)iUnknown->QueryInterface(iUnknown, CLIENT_PROXY_VER, (void **)&demoApi);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][QueryInterface CLIENT_PROXY_VER S:%s]: is %p",
               (unsigned long)pthread_self(), EXAMPLE_SERVICE, demoApi);
    return demoApi;
}

static void CASE_SyncCall(IClientProxy *defaultApi)
{
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][CASE_SyncCall api S:%s]: is %p",
               (unsigned long)pthread_self(), EXAMPLE_SERVICE, defaultApi);
    if (defaultApi == NULL) {
        return;
    }
    IpcIo request;
    char data[MAX_DATA_LEN];
    IpcIoInit(&request, data, sizeof(data), 0);
    defaultApi->Invoke(defaultApi, 0, &request, NULL, NULL);
}

static void CASE_ReleaseIUnknown(IUnknown *demoApi)
{
    if (demoApi == NULL) {
        return;
    }
    int32 ref = demoApi->Release((IUnknown *)demoApi);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][Release api S:%s]: is %p ref:%d",
               (unsigned long)pthread_self(), EXAMPLE_SERVICE, demoApi, ref);
}

void RunServiceTestCase(void)
{
    IClientProxy *remoteApi = CASE_GetRemoteIUnknown();
    CASE_SyncCall(remoteApi);
    CASE_ReleaseIUnknown((IUnknown *)remoteApi);
}
