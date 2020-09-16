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

#include "dmslite.h"

#include <pthread.h>

#include "dmslite_log.h"
#include "dmslite_msg_parser.h"
#include "dmslite_session.h"

#include "discovery_service.h"
#include "iunknown.h"
#include "ohos_errno.h"
#include "ohos_init.h"
#include "samgr_lite.h"

#define DMS_PUBLISHID 1
#define CAPABILITY "ddmpCapability"
#define CAPABILITY_DATA ""
#define CAPABILITY_DATA_LENGTH 0
#define BUNDLE_NAME "dms"
#define EMPTY_FEATURE_NAME ""

static const char *GetName(Feature *feature);
static void OnInitialize(Feature *feature, Service *parent, Identity identity);
static void OnStop(Feature *feature, Identity identity);
static BOOL OnMessage(Feature *feature, Request *request);

static void OnPublishSuccess(int32_t publishId);
static void OnPublishFail(int32_t publishId, PublishFailReason reason);

static DmsLite g_dmslite = {
    /* feature functions */
    .GetName = GetName,
    .OnInitialize = OnInitialize,
    .OnStop = OnStop,
    .OnMessage = OnMessage,
    .identity = {-1, -1, NULL},
};

static PublishInfo g_publishInfo = {
    .publishId = DMS_PUBLISHID,
    .mode = DISCOVER_MODE_ACTIVE,
    .medium = COAP,
    .freq = MID,
    .capability = CAPABILITY,
    .capabilityData = (unsigned char *)CAPABILITY_DATA,
    .dataLen = CAPABILITY_DATA_LENGTH,
};

static IPublishCallback g_publishCallback = {
    .onPublishSuccess = OnPublishSuccess,
    .onPublishFail = OnPublishFail,
};

static const char *GetName(Feature *feature)
{
    if (feature == NULL) {
        return EMPTY_FEATURE_NAME;
    }
    return DMSLITE_FEATURE;
}

static void OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    if (feature == NULL || parent == NULL) {
        return;
    }

    ((DmsLite*) feature)->identity = identity;

    int32_t ret = PublishService(BUNDLE_NAME, &g_publishInfo, &g_publishCallback);
    if (ret != EC_SUCCESS) {
        HILOGW("[PublishService failed]");
    }
}

static void OnStop(Feature *feature, Identity identity)
{
    HILOGD("[Feature stop]");
}

static BOOL OnMessage(Feature *feature, Request *request)
{
    if (feature == NULL || request == NULL) {
        return FALSE;
    }

    /* process for a specific feature-level msgId can be added below */
    switch (request->msgId) {
        default: {
            HILOGW("[Unkonwn msgId = %d]", request->msgId);
            break;
        }
    }
    return TRUE;
}

static void OnPublishSuccess(int32_t publishId)
{
    RegisterTcpCallback();
    HILOGI("[dms service publish success]");
}

static void OnPublishFail(int32_t publishId, PublishFailReason reason)
{
    HILOGW("[dms service publish failed reason = %d]", (int32_t) reason);
}

static void Init()
{
    SAMGR_GetInstance()->RegisterFeature(DISTRIBUTED_SCHEDULE_SERVICE, (Feature*) &g_dmslite);
    SAMGR_GetInstance()->RegisterFeatureApi(DISTRIBUTED_SCHEDULE_SERVICE, DMSLITE_FEATURE, GET_IUNKNOWN(g_dmslite));
}
SYS_FEATURE_INIT(Init);
