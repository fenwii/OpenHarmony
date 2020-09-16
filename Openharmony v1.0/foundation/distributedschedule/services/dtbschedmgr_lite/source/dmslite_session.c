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

#include "dmslite_session.h"

#include <unistd.h>

#include "distributed_service_interface.h"
#include "dmslite_inner_common.h"
#include "dmslite_log.h"
#include "dmslite_msg_parser.h"

#include "ohos_errno.h"
#include "session.h"

#define DMS_SESSION_NAME "dms"
#define DMS_MODULE_NAME "dms"
#define ACCEPT_SESSION_OPEN 0

static void OnBytesReceived(int32_t sessionId, const void *data, uint32_t dataLen);
static void OnSessionClosed(int32_t sessionId);
static int32_t OnSessionOpened(int32_t sessionId);

static void OnStartAbilityDone(int8_t errCode);

static struct ISessionListener g_sessionCallback = {
    .onBytesReceived = OnBytesReceived,
    .onSessionOpened = OnSessionOpened,
    .onSessionClosed = OnSessionClosed
};

static IDmsFeatureCallback g_dmsFeatureCallback = {
    /* in non-test mode, there is no need set a TlvParseCallback */
    .onTlvParseDone = NULL,
    .onStartAbilityDone = OnStartAbilityDone,
};

void OnStartAbilityDone(int8_t errCode)
{
    HILOGD("[onStartAbilityDone errCode = %d]", errCode);
}

void OnBytesReceived(int32_t sessionId, const void *data, uint32_t dataLen)
{
    CommuInterInfo interInfo;
    interInfo.payloadLength = dataLen;
    interInfo.payload = data;

    int8_t errCode = DmsLiteProcessCommuMsg(&interInfo, &g_dmsFeatureCallback);
    HILOGI("[DmsLiteProcessCommuMsg errCode = %d]", errCode);
}

void OnSessionClosed(int32_t sessionId)
{
    HILOGD("[function called]");
}

int32_t OnSessionOpened(int32_t sessionId)
{
    HILOGD("[function called]");
    /* only when we explicitly accept can the incoming session open successfully */
    return ACCEPT_SESSION_OPEN;
}

void RegisterTcpCallback()
{
    if (getuid() != FOUNDATION_UID) {
        HILOGE("[Only dtbschedsrv can register dms bus]");
        return;
    }

    int32_t errCode = CreateSessionServer(DMS_MODULE_NAME, DMS_SESSION_NAME, &g_sessionCallback);
    HILOGD("[Register %s, errCode = %d]", (errCode == EC_SUCCESS) ? "success" : "failed", errCode);
}
