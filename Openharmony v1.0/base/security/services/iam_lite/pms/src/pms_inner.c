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

#include "pms_inner.h"

#include <ohos_init.h>

#include "feature.h"
#include "log.h"
#include "samgr_lite.h"
#include "service.h"

#include "pms.h"
#include "pms_common.h"

static void Init();
static const char *GetName(Feature *feature);
static void OnInitialize(Feature *feature, Service *parent, Identity identity);
static void OnStop(Feature *feature, Identity identity);
static BOOL OnMessage(Feature *feature, Request *request);

static PmsInner g_permlite = {
    .GetName = GetName,
    .OnInitialize = OnInitialize,
    .OnStop = OnStop,
    .OnMessage = OnMessage,
    DEFAULT_IUNKNOWN_ENTRY_BEGIN,
    .CheckPermission = CheckPermissionStat,
    .QueryPermission = QueryPermission,
    .GrantPermission = GrantPermission,
    .RevokePermission = RevokePermission,
    .GrantRuntimePermission = GrantRuntimePermission,
    .RequestPermission = RequestPermission,
    DEFAULT_IUNKNOWN_ENTRY_END,
    .identity = {-1, -1, NULL},
};

static void Init()
{
    SAMGR_GetInstance()->RegisterFeature(PERMISSION_SERVICE, (Feature *)&g_permlite);
    SAMGR_GetInstance()->RegisterFeatureApi(PERMISSION_SERVICE, PERM_INNER, GET_IUNKNOWN(g_permlite));
    HILOG_INFO(HILOG_MODULE_APP, "Init pms inner feature success");
}
APP_FEATURE_INIT(Init);

static const char *GetName(Feature *feature)
{
    (void)feature;
    return PERM_INNER;
}

static void OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    (void)parent;
    if (feature == NULL) {
        return;
    }
    PmsInner *permlite = (PmsInner *)feature;
    permlite->identity = identity;
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