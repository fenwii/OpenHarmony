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
#include <log.h>
#include <pthread.h>
#include <samgr_lite.h>

static ClientDemo *CASE_GetIUnknown(void)
{
    ClientDemo *demoApi = NULL;
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][GetFeatureApi S:%s F:%s]: BEGIN\n",
               (unsigned long)pthread_self(), EXAMPLE_SERVICE, EXAMPLE_FEATURE);
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(EXAMPLE_SERVICE, EXAMPLE_FEATURE);
    if (iUnknown == NULL) {
        HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][GetFeatureApi S:%s F:%s]: error is NULL\n",
                   (unsigned long)pthread_self(), EXAMPLE_SERVICE, EXAMPLE_FEATURE);
        return NULL;
    }

    (void)iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)&demoApi);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][QueryInterface DEFAULT_VERSION S:%s, F:%s]: is %p\n",
               (unsigned long)pthread_self(), EXAMPLE_SERVICE, EXAMPLE_FEATURE, demoApi);
    return demoApi;
}

static void CASE_SyncCall(ClientDemo *demoApi)
{
    if (demoApi == NULL || demoApi->SyncCall == NULL) {
        return;
    }

    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]SyncCall BEGIN\n", (unsigned long)pthread_self());
    struct Payload payload = {
        .id = 0,
        .name = "I wanna sync call good result!",
        .value = 1
    };
    BOOL ret = demoApi->SyncCall((IUnknown *)demoApi, &payload);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]SyncCall End(%d)\n", (unsigned long)pthread_self(), ret);
}


static void CASE_AsyncCall(ClientDemo *demoApi)
{
    if (demoApi == NULL || demoApi->AsyncCall == NULL) {
        return;
    }
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncCall BEGIN\n", (unsigned long)pthread_self());
    BOOL ret = demoApi->AsyncCall((IUnknown *)demoApi, "I wanna async call good result!");
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncCall End(%d)\n", (unsigned long)pthread_self(), ret);
}

static void CASE_AsyncTimeCall(ClientDemo *demoApi)
{
    if (demoApi == NULL || demoApi->AsyncTimeCall == NULL) {
        return;
    }
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncTimeCall BEGIN\n", (unsigned long)pthread_self());
    BOOL ret = demoApi->AsyncTimeCall((IUnknown *)demoApi);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncTimeCall End(%d)\n", (unsigned long)pthread_self(), ret);
}

void AsyncHandler(IOwner owner, const char *resp)
{
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncCallBack Owner:%p, Response:%s\n",
               (unsigned long)pthread_self(), owner, resp);
}

static void CASE_AsyncCallBack(ClientDemo *demoApi)
{
    if (demoApi == NULL || demoApi->AsyncCallBack == NULL) {
        return;
    }
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncCallBack BEGIN\n", (unsigned long)pthread_self());
    BOOL ret = demoApi->AsyncCallBack((IUnknown *)demoApi,
                                      "I wanna async call callback good result!", NULL, AsyncHandler);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncCallBack End(%d)\n", (unsigned long)pthread_self(), ret);
}

static void CASE_ReleaseIUnknown(ClientDemo *demoApi)
{
    if (demoApi == NULL) {
        return;
    }
    int32 ref = demoApi->Release((IUnknown *)demoApi);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx][Release api S:%s, F:%s]: is %p ref:%d\n",
               (unsigned long)pthread_self(), EXAMPLE_SERVICE, EXAMPLE_FEATURE, demoApi, ref);
}

void RunFeatureTestCase(void)
{
    ClientDemo *demoApi = CASE_GetIUnknown();
    CASE_AsyncCall(demoApi);
    CASE_AsyncTimeCall(demoApi);
    CASE_SyncCall(demoApi);
    CASE_AsyncCallBack(demoApi);
    CASE_ReleaseIUnknown(demoApi);
}
