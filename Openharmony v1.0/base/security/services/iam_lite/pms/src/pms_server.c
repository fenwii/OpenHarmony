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

#include <ohos_init.h>
#include <ohos_errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

#include "feature.h"
#include "iproxy_client.h"
#include "iproxy_server.h"
#include "iunknown.h"
#include "liteipc_adapter.h"
#include "samgr_lite.h"
#include "service.h"

#include "pms.h"
#include "pms_common.h"
#include "pms_types.h"

#define SYS_APP_UID_MIN 100
#define SYS_APP_UID_MAX 999

typedef struct PermLiteApi {
    INHERIT_SERVER_IPROXY;
    int (*CheckPermission)(int taskID, const char *permissionName);
    int (*QueryPermission)(const char *identifier, PermissionSaved **permissions, int *permNum);
    int (*GrantPermission)(const char *identifier, const char *permName);
    int (*RevokePermission)(const char *identifier, const char *permName);
    int (*GrantRuntimePermission)(int taskID, const char *permissionName);
    int (*RequestPermission)(int taskID, const char *permissionName);
} PermLiteApi;

typedef struct PermLite {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(PermLiteApi);
    Identity identity;
} PermLite;

enum FUNCID {
    ID_CHECK = 0,
    ID_QUERY,
    ID_GRANT,
    ID_REVOKE,
    ID_GRANT_RUNTIME,
    ID_REQUEST
};

static void Init();
static const char *GetName(Feature *feature);
static void OnInitialize(Feature *feature, Service *parent, Identity identity);
static void OnStop(Feature *feature, Identity identity);
static BOOL OnMessage(Feature *feature, Request *request);
static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);

static PermLite g_permlite = {
    .GetName = GetName,
    .OnInitialize = OnInitialize,
    .OnStop = OnStop,
    .OnMessage = OnMessage,
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = Invoke,
    .CheckPermission = CheckPermissionStat,
    .QueryPermission = QueryPermission,
    .GrantPermission = GrantPermission,
    .RevokePermission = RevokePermission,
    .GrantRuntimePermission = GrantRuntimePermission,
    .RequestPermission = RequestPermission,
    IPROXY_END,
    .identity = {-1, -1, NULL},
};

static void Init()
{
    SAMGR_GetInstance()->RegisterFeature(PERMISSION_SERVICE, (Feature *)&g_permlite);
    SAMGR_GetInstance()->RegisterFeatureApi(PERMISSION_SERVICE, PERM_FEATURE, GET_IUNKNOWN(g_permlite));
    HILOG_INFO(HILOG_MODULE_APP, "Init pms lite feature success");
}
APP_FEATURE_INIT(Init);

static const char *GetName(Feature *feature)
{
    (void)feature;
    return PERM_FEATURE;
}

static void OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    (void)parent;
    if (feature == NULL) {
        return;
    }
    PermLite *permlite = (PermLite *)feature;
    permlite->identity = identity;
    HILOG_INFO(HILOG_MODULE_APP, "onInitialize pms lite feature");
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

void static InnerFreeDataBuff(void *ptr)
{
    if (ptr != NULL) {
        free(ptr);
    }
}

static void ReplyCheckPermission(const void *origin, IpcIo *req, IpcIo *reply, PermLiteApi* api)
{
    pid_t callingPid = GetCallingPid(origin);
    pid_t callingUid = GetCallingUid(origin);
    HILOG_INFO(HILOG_MODULE_APP, "Enter ID_CHECK, [callerPid: %d][callerUid: %d]", callingPid, callingUid);
    if (callingUid <= SYS_APP_UID_MAX) {
        IpcIoPushInt32(reply, GRANTED);
        return;
    }
    size_t permLen = 0;
    int taskId = IpcIoPopInt64(req);
    char *permName = (char *)IpcIoPopString(req, &permLen);
    int32_t ret = api->CheckPermission(callingPid, permName);
    HILOG_INFO(HILOG_MODULE_APP, "check permission, [taskId: %d][perm: %s][ret: %d]", taskId, permName, ret);
    IpcIoPushInt32(reply, ret);
}

static void ReplyQueryPermission(const void *origin, IpcIo *req, IpcIo *reply)
{
    pid_t callingPid = GetCallingPid(origin);
    pid_t callingUid = GetCallingUid(origin);
    HILOG_INFO(HILOG_MODULE_APP, "Enter ID_Query, [callerPid: %d][callerUid: %d]", callingPid, callingUid);
    size_t idLen = 0;
    int ret = 0;
    char *identifier = (char *)IpcIoPopString(req, &idLen);
    char *jsonStr = QueryPermissionString(identifier, &ret);

    IpcIoPushInt32(reply, ret);
    if (ret != PERM_ERRORCODE_SUCCESS) {
        return;
    }

    BuffPtr dataBuff = {
        .buffSz = strlen(jsonStr) + 1,
        .buff = (char *)jsonStr,
    };
    IpcIoPushDataBuffWithFree(reply, &dataBuff, InnerFreeDataBuff);
}

static void ReplyGrantPermission(const void *origin, IpcIo *req, IpcIo *reply, PermLiteApi* api)
{
    pid_t callingPid = GetCallingPid(origin);
    pid_t callingUid = GetCallingUid(origin);
    HILOG_INFO(HILOG_MODULE_APP, "Enter ID_GRANT, [callerPid: %d][callerUid: %d]", callingPid, callingUid);
    size_t permLen = 0;
    size_t idLen = 0;
    char *identifier = (char *)IpcIoPopString(req, &idLen);
    char *permName = (char *)IpcIoPopString(req, &permLen);
    int32_t ret = api->GrantPermission(identifier, permName);
    HILOG_INFO(HILOG_MODULE_APP, "grant permission, [id: %s][perm: %s][ret: %d]", identifier, permName, ret);
    IpcIoPushInt32(reply, ret);
}

static void ReplyRevokePermission(const void *origin, IpcIo *req, IpcIo *reply, PermLiteApi* api)
{
    pid_t callingPid = GetCallingPid(origin);
    pid_t callingUid = GetCallingUid(origin);
    HILOG_INFO(HILOG_MODULE_APP, "Enter ID_REVOKE, [callerPid: %d][callerUid: %d]", callingPid, callingUid);
    size_t permLen = 0;
    size_t idLen = 0;
    char *identifier = (char *)IpcIoPopString(req, &idLen);
    char *permName = (char *)IpcIoPopString(req, &permLen);
    int32_t ret = api->RevokePermission(identifier, permName);
    HILOG_INFO(HILOG_MODULE_APP, "revoke permission, [id: %s][perm: %s][ret: %d]", identifier, permName, ret);
    IpcIoPushInt32(reply, ret);
}

static void ReplyGrantRuntimePermission(const void *origin, IpcIo *req, IpcIo *reply, PermLiteApi* api)
{
    pid_t callingPid = GetCallingPid(origin);
    pid_t callingUid = GetCallingUid(origin);
    HILOG_INFO(HILOG_MODULE_APP, "Enter ID_GRANTRUNTIME, [callerPid: %d][callerUid: %d]", callingPid, callingUid);
    size_t permLen = 0;
    int taskId = IpcIoPopInt64(req);
    char *permName = (char *)IpcIoPopString(req, &permLen);
    int32_t ret = api->GrantRuntimePermission(callingPid, permName);
    HILOG_INFO(HILOG_MODULE_APP, "check permission, [taskId: %d][perm: %s][ret: %d]", taskId, permName, ret);
    IpcIoPushInt32(reply, ret);
}

static void ReplyRequestPermission(const void *origin, IpcIo *req, IpcIo *reply, PermLiteApi* api)
{
    pid_t callingPid = GetCallingPid(origin);
    pid_t callingUid = GetCallingUid(origin);
    HILOG_INFO(HILOG_MODULE_APP, "Enter ID_REQUEST, [callerPid: %d][callerUid: %d]", callingPid, callingUid);
    size_t permLen = 0;
    int taskId = IpcIoPopInt64(req);
    char *permName = (char *)IpcIoPopString(req, &permLen);
    int32_t ret = api->RequestPermission(callingPid, permName);
    HILOG_INFO(HILOG_MODULE_APP, "check permission, [taskId: %d][perm: %s][ret: %d]", taskId, permName, ret);
    IpcIoPushInt32(reply, ret);
}

static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    PermLiteApi *api = (PermLiteApi *)iProxy;
    switch (funcId) {
        case ID_CHECK:
            ReplyCheckPermission(origin, req, reply, api);
            break;
        case ID_QUERY:
            ReplyQueryPermission(origin, req, reply);
            break;
        case ID_GRANT:
            ReplyGrantPermission(origin, req, reply, api);
            break;
        case ID_REVOKE:
            ReplyRevokePermission(origin, req, reply, api);
            break;
        case ID_GRANT_RUNTIME:
            ReplyGrantRuntimePermission(origin, req, reply, api);
            break;
        case ID_REQUEST:
            ReplyRequestPermission(origin, req, reply, api);
            break;
        default:
            break;
    }
    return EC_SUCCESS;
}
