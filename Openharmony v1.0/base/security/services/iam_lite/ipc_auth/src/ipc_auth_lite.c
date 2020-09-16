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

#include "ipc_auth_lite.h"

#include <ohos_init.h>

#include "log.h"

#include "feature.h"
#include "iunknown.h"
#include "samgr_lite.h"
#include "service.h"

#include "ipc_auth.h"

static void Init();
static const char *GetName(Feature *feature);
static void OnInitialize(Feature *feature, Service *parent, Identity identity);
static void OnStop(Feature *feature, Identity identity);
static BOOL OnMessage(Feature *feature, Request *request);

static IpcAuthLite g_authLite = {
    .GetName = GetName,
    .OnInitialize = OnInitialize,
    .OnStop = OnStop,
    .OnMessage = OnMessage,
    DEFAULT_IUNKNOWN_ENTRY_BEGIN,
    .GetCommunicationStrategy = GetCommunicationStrategy,
    .IsCommunicationAllowed = IsCommunicationAllowed,
    DEFAULT_IUNKNOWN_ENTRY_END,
    .identity = {-1, -1, NULL},
};

static void Init()
{
    SAMGR_GetInstance()->RegisterFeature(PERMISSION_SERVICE, (Feature *)&g_authLite);
    SAMGR_GetInstance()->RegisterFeatureApi(PERMISSION_SERVICE, IPCAUTH, GET_IUNKNOWN(g_authLite));
    HILOG_INFO(HILOG_MODULE_APP, "Init ipcAuth feature success");
}
APP_FEATURE_INIT(Init);

static const char *GetName(Feature *feature)
{
    (void)feature;
    return IPCAUTH;
}

static void OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    (void)parent;
    if (feature == NULL) {
        return;
    }
    IpcAuthLite *authLite = (IpcAuthLite *)feature;
    authLite->identity = identity;
    HILOG_INFO(HILOG_MODULE_APP, "OnInitialize ipcAuth feature");
}

static void OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
}

static BOOL OnMessage(Feature *feature, Request *request)
{
    if (feature == NULL || request == NULL) {
        return FALSE;
    }
    // call func
    return TRUE;
}