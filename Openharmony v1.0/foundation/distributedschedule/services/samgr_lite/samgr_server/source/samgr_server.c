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
#include "samgr_server.h"
#include <stdlib.h>
#include <ohos_init.h>
#include <ohos_types.h>
#include <ohos_errno.h>
#include <liteipc_adapter.h>
#include <log.h>
#include "policy_define.h"
#include "samgr_lite.h"
#include "memory_adapter.h"
#include "thread_adapter.h"
#include "default_client.h"

#undef LOG_TAG
#undef LOG_DOMAIN
#define LOG_TAG "Samgr"
#define LOG_DOMAIN 0xD001800

typedef int(*ProcFunc)(SamgrServer *server, int32 option, void *origin, IpcIo *req, IpcIo *reply);
#define MAX_SA_SIZE 0x100
#define RETRY_TIMES 3
#define RETRY_INTERVAL 1

static const char *GetName(Service *service);
static BOOL Initialize(Service *service, Identity identity);
static TaskConfig GetTaskConfig(Service *service);
static BOOL MessageHandle(Service *service, Request *request);
static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);
static int OnEndpointExit(const IpcContext *context, void* ipcMsg, IpcIo* data, void* argv);
static int ProcEndpoint(SamgrServer *server, int32 option, void *origin, IpcIo *req, IpcIo *reply);
static int32 ProcPutFeature(SamgrServer *server, const void *origin, IpcIo *req, IpcIo *reply, SvcIdentity *identity);
static int32 ProcGetFeature(SamgrServer *server, const void *origin, IpcIo *req, IpcIo *reply, SvcIdentity *identity);
static int ProcFeature(SamgrServer *server, int32 option, void *origin, IpcIo *req, IpcIo *reply);
static SvcIdentity QueryLocalIdentity(const char *service, const char *feature);
static int RegisterLocalIdentity(const char *service, const char *feature, SvcIdentity *identity,
                                 PolicyTrans **policy, uint32 *policyNum);
static int RegisterSamgrEndpoint(const IpcContext* context, SvcIdentity* identity);
static void TransmitPolicy(int ret, const SvcIdentity* identity, IpcIo *reply,
                           const PolicyTrans *policy, uint32 policyNum);
static void TransmitFixedPolicy(IpcIo *reply, PolicyTrans policy);
static IpcAuthInterface *GetIpcAuthInterface(void);

static SamgrServer g_server = {
    .GetName = GetName,
    .Initialize = Initialize,
    .GetTaskConfig = GetTaskConfig,
    .MessageHandle = MessageHandle,
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = Invoke,
    IPROXY_END,
};

static ProcFunc g_functions[] = {
    [RES_ENDPOINT] = ProcEndpoint,
    [RES_FEATURE] = ProcFeature,
};

static void InitializeRegistry(void)
{
    HILOG_INFO(HILOG_MODULE_SAMGR, "Initialize Registry!");
    SAMGR_RegisterQueryIdentity(QueryLocalIdentity);
    SAMGR_RegisterRegisterIdentity(RegisterLocalIdentity);
    g_server.mtx = MUTEX_InitValue();
    g_server.clients = VECTOR_Make((VECTOR_Key)SAMGR_GetSAName, (VECTOR_Compare)SAMGR_CompareSAName);
    SASTORA_Init(&g_server.store);
    g_server.samgr = SAMGR_CreateEndpoint("samgr", RegisterSamgrEndpoint);
    g_server.endpoint = SAMGR_CreateEndpoint("ipc receive", NULL);
    SAMGR_GetInstance()->RegisterService((Service *)&g_server);
}
SYS_SERVICE_INIT(InitializeRegistry);

int SAMGR_RegisterServiceApi(const char *service, const char *feature, const Identity *identity, IUnknown *iUnknown)
{
    if (service == NULL) {
        return EC_INVALID;
    }
    MUTEX_Lock(g_server.mtx);
    SaName saName = {service, feature};
    int32 token = SAMGR_AddRouter(g_server.endpoint, &saName, identity, iUnknown);
    MUTEX_Unlock(g_server.mtx);
    if (token < 0 || !g_server.endpoint->running) {
        return token;
    }
    return SAMGR_ProcPolicy(g_server.endpoint, &saName, token);
}

IUnknown *SAMGR_FindServiceApi(const char *service, const char *feature)
{
    SaName key = {service, feature};
    // the proxy already exits.
    int index = VECTOR_FindByKey(&g_server.clients, &key);
    if (index != INVALID_INDEX) {
        return VECTOR_At(&g_server.clients, index);
    }

    SvcIdentity identity = QueryLocalIdentity(service, feature);
    if (identity.handle == INVALID_INDEX) {
        return NULL;
    }
    MUTEX_Lock(g_server.mtx);
    index = VECTOR_FindByKey(&g_server.clients, &key);
    if (index != INVALID_INDEX) {
        MUTEX_Unlock(g_server.mtx);
        return VECTOR_At(&g_server.clients, index);
    }
    IUnknown* client = SAMGR_CreateIProxy(g_server.endpoint->context, service, feature, identity);
    (void)VECTOR_Add(&g_server.clients, client);
    MUTEX_Unlock(g_server.mtx);
    HILOG_INFO(HILOG_MODULE_SAMGR, "Create proxy[%p]<%s, %s, %u, %u>",
               client, service, feature, identity.handle, identity.token);
    return client;
}

static const char *GetName(Service *service)
{
    (void)service;
    return SAMGR_SERVICE;
}

static BOOL Initialize(Service *service, Identity identity)
{
    SamgrServer *server = (SamgrServer *)service;
    server->identity = identity;
    SaName saName = {SAMGR_SERVICE, NULL};
    SAMGR_AddRouter(server->samgr, &saName, &server->identity, GET_IUNKNOWN(*server));
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *request)
{
    SamgrServer *server = (SamgrServer *)service;
    switch (request->msgId) {
        case MSG_CLEAN:
            MUTEX_Lock(server->mtx);
            SASTORA_ClearByPid(&server->store, request->msgValue);
            MUTEX_Unlock(server->mtx);
            break;
        default:
            break;
    }
    return TRUE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 0x400, 20, SINGLE_TASK};
    return config;
}

static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    SamgrServer *server = GET_OBJECT(iProxy, SamgrServer, iUnknown);
    int32 resource = IpcIoPopUint32(req);
    int32 option = IpcIoPopUint32(req);
    if (resource >= RES_BUTT || resource < 0 || g_functions[resource] == NULL) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Invalid Msg<%d, %d, %d>", resource, option, funcId);
        return EC_INVALID;
    }
    return g_functions[resource](server, option, origin, req, reply);
}

static int ProcEndpoint(SamgrServer *server, int32 option, void *origin, IpcIo *req, IpcIo *reply)
{
    if (option != OP_POST) {
        IpcIoPushUint32(reply, (uint32)INVALID_INDEX);
        return EC_FAILURE;
    }

    pid_t pid = GetCallingPid(origin);
    PidHandle handle;
    MUTEX_Lock(server->mtx);
    int index = SASTORA_FindHandleByPid(&g_server.store, pid, &handle);
    if (index == INVALID_INDEX) {
        SvcIdentity identity = {(uint32)INVALID_INDEX, (uint32)INVALID_INDEX, (uint32)INVALID_INDEX};
        identity.handle = IpcIoPopUint32(req);
        if (identity.handle == (uint32)INVALID_INDEX) { // generate handle
            (void)GenServiceHandle(&identity, GetCallingTid(origin));
        }

        handle.pid = pid;
        handle.uid = GetCallingUid(origin);
        handle.handle = identity.handle;
        handle.deadId = INVALID_INDEX;
        (void)SASTORA_SaveHandleByPid(&server->store, handle);
        (void)UnRegisteDeathCallback(identity, handle.deadId);
        (void)RegisteDeathCallback(server->endpoint->context, identity, OnEndpointExit, (void*)((uintptr_t)pid),
                                   &handle.deadId);
    }
    MUTEX_Unlock(server->mtx);
    IpcIoPushUint32(reply, handle.handle);
    HILOG_INFO(HILOG_MODULE_SAMGR, "Register Endpoint<%d, %d, %d>", handle.pid, handle.handle, handle.deadId);
    return EC_SUCCESS;
}

static int32 ProcPutFeature(SamgrServer *server, const void *origin, IpcIo *req, IpcIo *reply, SvcIdentity *identity)
{
    size_t len = 0;
    char *service = (char *)IpcIoPopString(req, &len);
    if (service == NULL || len == 0) {
        IpcIoPushInt32(reply, EC_INVALID);
        return EC_INVALID;
    }
    pid_t pid = GetCallingPid(origin);
    char *feature = IpcIoPopBool(req) ? NULL : (char *)IpcIoPopString(req, &len);
    MUTEX_Lock(server->mtx);
    PidHandle handle;
    int index = SASTORA_FindHandleByPid(&server->store, pid, &handle);
    if (index == INVALID_INDEX) {
        MUTEX_Unlock(server->mtx);
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Endpoint[%d] is not register", pid);
        IpcIoPushInt32(reply, EC_NOSERVICE);
        return EC_NOSERVICE;
    }
    *identity = SASTORA_Find(&server->store, service, feature);
    if (identity->handle != INVALID_INDEX && identity->handle != handle.handle) {
        MUTEX_Unlock(server->mtx);
        IpcIoPushInt32(reply, EC_INVALID);
        return EC_INVALID;
    }
    identity->token = IpcIoPopUint32(req);
    identity->handle = handle.handle;

    PolicyTrans *policy = NULL;
    RegParams regParams = {service, feature, handle.uid, handle.pid};
    uint32 policyNum = 0;
    int ret = g_server.ipcAuth->GetCommunicationStrategy(regParams, &policy, &policyNum);
    if (ret != EC_SUCCESS || policy == NULL) {
        MUTEX_Unlock(g_server.mtx);
        SAMGR_Free(policy);
        HILOG_DEBUG(HILOG_MODULE_SAMGR, "Remote Get Communication Strategy<%s, %s> No Permission<%d>!",
                    service, feature, ret);
        IpcIoPushInt32(reply, EC_PERMISSION);
        return EC_PERMISSION;
    }

    ret = SASTORA_Save(&server->store, service, feature, identity);
    MUTEX_Unlock(server->mtx);
    HILOG_DEBUG(HILOG_MODULE_SAMGR, "Register Feature<%s, %s> pid<%d>, id<%d, %d> ret:%d",
                service, feature, pid, identity->handle, identity->token, ret);
    TransmitPolicy(ret, identity, reply, policy, policyNum);
    SAMGR_Free(policy);
    return ret;
}

static void TransmitPolicy(int ret, const SvcIdentity* identity, IpcIo *reply,
                           const PolicyTrans *policy, uint32 policyNum)
{
    if (identity == NULL || reply == NULL || policy == NULL) {
        IpcIoPushInt32(reply, EC_INVALID);
        return;
    }
    if (ret != EC_SUCCESS) {
        IpcIoPushInt32(reply, ret);
        return;
    }
    IpcIoPushInt32(reply, ret);
    IpcIoPushSvc(reply, identity);
    IpcIoPushUint32(reply, policyNum);
    uint32 i;
    for (i = 0; i < policyNum; i++) {
        IpcIoPushInt32(reply, policy[i].type);
        switch (policy[i].type) {
            case RANGE:
                IpcIoPushInt32(reply, policy[i].uidMin);
                IpcIoPushInt32(reply, policy[i].uidMax);
                break;
            case FIXED:
                TransmitFixedPolicy(reply, policy[i]);
                break;
            case BUNDLENAME:
                IpcIoPushInt32(reply, policy[i].fixedUid[0]);
                break;
            default:
                break;
        }
    }
}

static void TransmitFixedPolicy(IpcIo *reply, PolicyTrans policy)
{
    if (reply == NULL) {
        return;
    }
    uint32 i;
    for (i = 0; i < UID_SIZE; i++) {
        IpcIoPushInt32(reply, policy.fixedUid[i]);
    }
}

static int32 ProcGetFeature(SamgrServer *server, const void *origin, IpcIo *req, IpcIo *reply, SvcIdentity *identity)
{
    size_t len = 0;
    char *service = (char *)IpcIoPopString(req, &len);
    if (service == NULL || len == 0) {
        IpcIoPushInt32(reply, EC_INVALID);
        return EC_INVALID;
    }
    char *feature = IpcIoPopBool(req) ? NULL : (char *)IpcIoPopString(req, &len);
    MUTEX_Lock(server->mtx);
    *identity = SASTORA_Find(&server->store, service, feature);
    if (identity->handle == INVALID_INDEX) {
        MUTEX_Unlock(server->mtx);
        HILOG_DEBUG(HILOG_MODULE_SAMGR, "Cannot Find Feature<%s, %s> id<%d, %d> ret:%d",
                    service, feature, identity->handle, identity->token, EC_NOSERVICE);
        return EC_NOSERVICE;
    }

    PidHandle providerPid = SASTORA_FindPidHandleByIpcHandle(&server->store, identity->handle);
    MUTEX_Unlock(server->mtx);
    if (providerPid.pid == INVALID_INDEX || providerPid.uid == INVALID_INDEX) {
        HILOG_DEBUG(HILOG_MODULE_SAMGR, "Cannot Find PidHandle<%s, %s> id<%d, %d> ret:%d",
                    service, feature, identity->handle, identity->token, EC_FAILURE);
        return EC_FAILURE;
    }
    AuthParams authParams = {
        .providerService = service,
        .providerfeature = feature,
        .consumerPid = GetCallingPid(origin),
        .consumerUid = GetCallingUid(origin),
        .providerPid = providerPid.pid,
        .providerUid = providerPid.uid
    };
    int isAuth = g_server.ipcAuth->IsCommunicationAllowed(authParams);
    HILOG_DEBUG(HILOG_MODULE_SAMGR, "Judge Auth<%s, %s> ret:%d", service, feature, isAuth);

    int32 ret = (isAuth == EC_SUCCESS) ? AddServiceAccess(*identity, GetCallingTid(origin)) : EC_PERMISSION;
    HILOG_DEBUG(HILOG_MODULE_SAMGR, "Find Feature<%s, %s> id<%d, %d> ret:%d",
                service, feature, identity->handle, identity->token, ret);
    return ret;
}

static int ProcFeature(SamgrServer *server, int32 option, void *origin, IpcIo *req, IpcIo *reply)
{
    if (option != OP_PUT && option != OP_GET) {
        IpcIoPushInt32(reply, EC_INVALID);
        return EC_INVALID;
    }

    if (g_server.ipcAuth == NULL) {
        g_server.ipcAuth = GetIpcAuthInterface();
    }
    if (g_server.ipcAuth == NULL) {
        IpcIoPushInt32(reply, EC_NOINIT);
        return EC_NOINIT;
    }

    int ret = EC_SUCCESS;
    SvcIdentity identity = {INVALID_INDEX, INVALID_INDEX, INVALID_INDEX};
    if (option == OP_PUT) {
        ret = ProcPutFeature(server, origin, req, reply, &identity);
    }
    if (ret != EC_SUCCESS) {
        return ret;
    }

    if (option == OP_GET) {
        ret = ProcGetFeature(server, origin, req, reply, &identity);
        IpcIoPushInt32(reply, ret);
        IpcIoPushSvc(reply, &identity);
    }
    return ret;
}

static SvcIdentity QueryLocalIdentity(const char *service, const char *feature)
{
    MUTEX_Lock(g_server.mtx);
    SvcIdentity saInfo = SASTORA_Find(&g_server.store, service, feature);
    MUTEX_Unlock(g_server.mtx);
    return saInfo;
}

static int RegisterLocalIdentity(const char *service, const char *feature, SvcIdentity *identity,
                                 PolicyTrans **policy, uint32 *policyNum)
{
    pid_t selfPid = getpid();
    MUTEX_Lock(g_server.mtx);
    PidHandle pidHandle = {INVALID_INDEX, INVALID_INDEX, INVALID_INDEX, INVALID_INDEX};
    int ret = SASTORA_FindHandleByPid(&g_server.store, selfPid, &pidHandle);
    if (ret != INVALID_INDEX) {
        identity->handle = pidHandle.handle;
        ret = SASTORA_Save(&g_server.store, service, feature, identity);
    } else {
        ret = EC_NODEVICE;
    }
    HILOG_DEBUG(HILOG_MODULE_SAMGR, "RegisterIdentity <%s, %s> pid<%d> <%u, %u> ",
                service, feature, selfPid, identity->handle, identity->token);
    if (ret != EC_SUCCESS) {
        MUTEX_Unlock(g_server.mtx);
        HILOG_DEBUG(HILOG_MODULE_SAMGR, "SaStore Save FAILED(%d), <%s, %s> <%u, %u> ",
                    ret, service, feature, identity->handle, identity->token);
        return ret;
    }
    MUTEX_Unlock(g_server.mtx);

    RegParams regParams = {
        .service = (char *)service,
        .feature = (char *)feature,
        .uid = getuid(),
        .pid = selfPid
    };
    if (g_server.ipcAuth == NULL) {
        g_server.ipcAuth = GetIpcAuthInterface();
    }
    if (g_server.ipcAuth == NULL) {
        HILOG_DEBUG(HILOG_MODULE_SAMGR, "g_server.ipcAuth is NULL");
        return EC_FAILURE;
    }
    ret = g_server.ipcAuth->GetCommunicationStrategy(regParams, policy, policyNum);
    return ret;
}

static int RegisterSamgrEndpoint(const IpcContext* context, SvcIdentity* identity)
{
    int ret = SetSaManager(context, MAX_SA_SIZE);
    if (ret != LITEIPC_OK) {
        HILOG_FATAL(HILOG_MODULE_SAMGR, "Set sa manager<%d> failed!", ret);
        // Set sa manager failed! We need restart to recover
        exit(-ret);
    }
    identity->handle = SAMGR_HANDLE;
    identity->token = SAMGR_TOKEN;
    identity->cookie = SAMGR_COOKIE;
    return EC_SUCCESS;
}

static int OnEndpointExit(const IpcContext *context, void* ipcMsg, IpcIo* data, void* argv)
{
    (void)data;
    if (ipcMsg != NULL) {
        FreeBuffer(g_server.endpoint->context, ipcMsg);
    }
    pid_t pid = (pid_t)((uintptr_t)argv);
    Request request = {0};
    request.msgId = MSG_CLEAN;
    request.msgValue = pid;
    int retry = RETRY_TIMES;
    int ret = EC_INVALID;
    while (retry > 0) {
        ret = SAMGR_SendRequest(&g_server.identity, &request, NULL);
        if (ret == EC_SUCCESS) {
            break;
        }
        sleep(RETRY_INTERVAL);
        --retry;
    }
    HILOG_ERROR(HILOG_MODULE_SAMGR, "IPC pid<%d> exit! send clean request retry(%d), ret(%d)!", pid, retry, ret);
    return EC_SUCCESS;
}

static IpcAuthInterface *GetIpcAuthInterface(void)
{
    IpcAuthInterface *ipcAuth = NULL;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(PERMISSION_SERVICE, IPCAUTH);
    if (iUnknown == NULL) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Get IpcAuthInterface: IUnknown NULL");
        return NULL;
    }
    (void)iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)&ipcAuth);
    return ipcAuth;
}
