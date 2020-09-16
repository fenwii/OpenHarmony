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
#include "endpoint.h"
#include <stdlib.h>
#include <securec.h>
#include <ohos_errno.h>
#include <service.h>
#include <log.h>
#include "iproxy_server.h"
#include "memory_adapter.h"
#include "thread_adapter.h"
#include "default_client.h"

#undef LOG_TAG
#undef LOG_DOMAIN
#define LOG_TAG "Samgr"
#define LOG_DOMAIN 0xD001800

#define MAX_STACK_SIZE 0x1000
#define MAX_OBJECT_NUM 5
#define MAX_RETRY_TIMES 3
#define RETRY_INTERVAL 5
#define MAX_REGISTER_RETRY_TIMES 10
#define REGISTER_RETRY_INTERVAL 2

#ifndef MAX_BUCKET_RATE
#define MAX_BUCKET_RATE 1000
#endif

#ifndef MAX_BURST_RATE
#define MAX_BURST_RATE (MAX_BUCKET_RATE + (MAX_BUCKET_RATE >> 1))
#endif

#define SAMGR_SERVICE "samgr"

typedef struct Router {
    SaName saName;
    Identity identity;
    IServerProxy *proxy;
    PolicyTrans *policy;
    uint32 policyNum;
} Router;

static int CompareIServerProxy(const IServerProxy *proxy1, const IServerProxy *proxy2);
static IServerProxy *GetIServerProxy(const Router *router);
static void *Receive(void *argv);
static int Dispatch(const IpcContext *context, void *ipcMsg, IpcIo *data, void *argv);
static void HandleIpc(const Request *request, const Response *response);
static int OnSamgrServerExit(const IpcContext *context, void *ipcMsg, IpcIo *data, void *argv);
static int RegisterRemoteFeatures(Endpoint *endpoint);
static void Listen(Endpoint *endpoint);
static boolean JudgePolicy(uid_t callingUid, const PolicyTrans *policy, uint32 policyNum);
static boolean SearchFixedPolicy(uid_t callingUid, PolicyTrans policy);
static int AddPolicyToRouter(const Endpoint *endpoint, const SvcIdentity *saInfo,
                             const PolicyTrans *policy, uint32 policyNum);
static int RegisterRemoteEndpoint(const IpcContext *context, SvcIdentity *identity);
static RegisterIdentity g_registerID = NULL;
int SAMGR_RegisterRegisterIdentity(RegisterIdentity action)
{
    if (action == NULL || g_registerID != NULL) {
        return EC_INVALID;
    }

    g_registerID = action;
    return EC_SUCCESS;
}

Endpoint *SAMGR_CreateEndpoint(const char *name, RegisterEndpoint registry)
{
    Endpoint *endpoint = SAMGR_Malloc(sizeof(Endpoint));
    if (endpoint == NULL) {
        return NULL;
    }
    endpoint->deadId = INVALID_INDEX;
    endpoint->context = OpenLiteIpc(LITEIPC_DEFAULT_MAP_SIZE);
    endpoint->boss = NULL;
    endpoint->routers = VECTOR_Make((VECTOR_Key)GetIServerProxy, (VECTOR_Compare)CompareIServerProxy);
    endpoint->name = name;
    endpoint->running = FALSE;
    endpoint->identity.handle = (uint32_t)INVALID_INDEX;
    endpoint->identity.token = (uint32_t)INVALID_INDEX;
    endpoint->identity.cookie = (uint32_t)INVALID_INDEX;
    endpoint->registerEP = (registry == NULL) ? RegisterRemoteEndpoint : registry;
    TB_InitBucket(&endpoint->bucket, MAX_BUCKET_RATE, MAX_BURST_RATE);
    return endpoint;
}

int SAMGR_AddRouter(Endpoint *endpoint, const SaName *saName, const Identity *id, IUnknown *proxy)
{
    if (endpoint == NULL || id == NULL || proxy == NULL || saName == NULL) {
        return EC_INVALID;
    }

    IServerProxy *serverProxy = NULL;
    proxy->QueryInterface(proxy, SERVER_PROXY_VER, (void *)&serverProxy);
    if (serverProxy == NULL) {
        return EC_INVALID;
    }
    // Lock the multi-write
    int index = VECTOR_FindByKey(&endpoint->routers, proxy);
    if (index != INVALID_INDEX) {
        serverProxy->Release((IUnknown *)serverProxy);
        return index;
    }

    Router *router = SAMGR_Malloc(sizeof(Router));
    if (router == NULL) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Memory is not enough! Identity<%d, %d, %p>",
                    id->serviceId, id->featureId, id->queueId);
        return EC_NOMEMORY;
    }
    router->saName = *saName;
    router->identity = *id;
    router->proxy = serverProxy;
    router->policy = NULL;
    router->policyNum = 0;
    index = VECTOR_Add(&endpoint->routers, router);
    if (index == INVALID_INDEX) {
        SAMGR_Free(router);
        return EC_FAILURE;
    }
    Listen(endpoint);
    return index;
}

int SAMGR_ProcPolicy(const Endpoint *endpoint, const SaName *saName, int token)
{
    if (endpoint == NULL || saName == NULL || token == INVALID_INDEX) {
        return EC_INVALID;
    }
    // retry until success or 20 seconds.
    int ret = EC_INVALID;
    uint8 retry = 0;
    SvcIdentity saInfo = {INVALID_INDEX, token, INVALID_INDEX};
    while (retry < MAX_REGISTER_RETRY_TIMES) {
        ++retry;
        PolicyTrans *policy = NULL;
        uint32 policyNum = 0;
        ret = g_registerID(saName->service, saName->feature, &saInfo, &policy, &policyNum);
        if (ret != EC_SUCCESS || policy == NULL) {
            SAMGR_Free(policy);
            continue;
        }
        HILOG_INFO(HILOG_MODULE_SAMGR, "Register server sa<%s, %s> id<%u, %u> retry:%d ret:%d!",
                   saName->service, saName->feature, saInfo.handle, saInfo.token, retry, ret);
        ret = AddPolicyToRouter(endpoint, &saInfo, policy, policyNum);
        if (ret == EC_SUCCESS) {
            SAMGR_Free(policy);
            break;
        }
        SAMGR_Free(policy);
        sleep(REGISTER_RETRY_INTERVAL);
    }
    return ret;
}

static void Listen(Endpoint *endpoint)
{
    if (endpoint->boss != NULL) {
        return;
    }
    ThreadAttr attr = {endpoint->name, MAX_STACK_SIZE, PRI_ABOVE_NORMAL, 0, 0};
    endpoint->boss = (ThreadId)THREAD_Create(Receive, endpoint, &attr);
}

static int AddPolicyToRouter(const Endpoint *endpoint, const SvcIdentity *saInfo,
                             const PolicyTrans *policy, uint32 policyNum)
{
    if (endpoint == NULL || saInfo == NULL || policy == NULL) {
        return EC_INVALID;
    }

    Router *router = VECTOR_At((Vector *)&endpoint->routers, saInfo->token);
    if (router == NULL) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Router <%s, %u> is NULL", endpoint->name, saInfo->token);
        return EC_INVALID;
    }

    if (router->policy != NULL) {
        return EC_SUCCESS;
    }
    router->policyNum = policyNum;
    if (policyNum == 0) {
        return EC_INVALID;
    }
    router->policy = (PolicyTrans *)SAMGR_Malloc(sizeof(PolicyTrans) * policyNum);
    if (router->policy == NULL) {
        return EC_NOMEMORY;
    }
    if (memcpy_s(router->policy, sizeof(PolicyTrans) * policyNum, policy, sizeof(PolicyTrans) * policyNum) != EOK) {
        SAMGR_Free(router->policy);
        router->policy = NULL;
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Add Policy <%s, %s, %s> Failed!",
                    endpoint->name, router->saName.service, router->saName.feature);
        return EC_FAILURE;
    }
    HILOG_DEBUG(HILOG_MODULE_SAMGR, "Add Policy <%s, %s, %s> Success",
                endpoint->name, router->saName.service, router->saName.feature);
    return EC_SUCCESS;
}

static void *Receive(void *argv)
{
    Endpoint *endpoint = (Endpoint *)argv;
    if (endpoint == NULL || endpoint->registerEP == NULL) {
        return NULL;
    }

    int ret = EC_INVALID;
    uint8 retry = 0;
    while (retry < MAX_RETRY_TIMES) {
        ret = endpoint->registerEP(endpoint->context, &endpoint->identity);
        if (ret == EC_SUCCESS) {
            SvcIdentity samgr = {SAMGR_HANDLE, SAMGR_TOKEN, SAMGR_COOKIE};
            (void)UnRegisteDeathCallback(samgr, endpoint->deadId);
            (void)RegisteDeathCallback(endpoint->context, samgr, OnSamgrServerExit, endpoint, &endpoint->deadId);
            break;
        }
        ++retry;
        sleep(RETRY_INTERVAL);
    }

    if (ret != EC_SUCCESS) {
        HILOG_FATAL(HILOG_MODULE_SAMGR, "Register endpoint<%s>, handle<%u> failed! will exit to recover!",
                    endpoint->name, endpoint->identity.handle);
        exit(-ret);
    }

    endpoint->running = TRUE;
    if (endpoint->identity.handle != SAMGR_HANDLE) {
        int remain = RegisterRemoteFeatures(endpoint);
        HILOG_INFO(HILOG_MODULE_SAMGR, "Register endpoint<%s> and iunknown finished! remain<%d> iunknown!",
                   endpoint->name, remain);
    }
    StartLoop(endpoint->context, Dispatch, endpoint);
    return NULL;
}

static int Dispatch(const IpcContext *context, void *ipcMsg, IpcIo *data, void *argv)
{
    if (argv == NULL || ipcMsg == NULL) {
        return EC_INVALID;
    }

    Endpoint *endpoint = (Endpoint *)argv;
    uint32_t token = (uint32_t)INVALID_INDEX;
    GetToken(ipcMsg, &token);
    if (TB_CheckMessage(&endpoint->bucket) == BUCKET_BUSY) {
        HILOG_WARN(HILOG_MODULE_SAMGR, "Flow Control <%u> is NULL", token);
        goto ERROR;
    }

    Router *router = VECTOR_At(&endpoint->routers, token);
    if (router == NULL) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Router <%s, %u> is NULL", endpoint->name, token);
        goto ERROR;
    }
    Response resp = {0};
    resp.data = endpoint;
    Request request = {0};
    request.msgId = token;
    request.data = ipcMsg;
    request.msgValue = INVALID_INDEX;
    GetCode(ipcMsg, &request.msgValue);
#ifdef LITE_LINUX_BINDER_IPC
    HandleIpc(&request, &resp);
#else
    uint32 *ref = NULL;
    int ret = SAMGR_SendSharedDirectRequest(&router->identity, &request, &resp, &ref, HandleIpc);
    if (ret != EC_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Router[%u] Service<%d, %d, %p> is busy",
                    token, router->identity.serviceId, router->identity.featureId, router->identity.queueId);
        goto ERROR;
    }
#endif
    return EC_SUCCESS;
ERROR:
    if (ipcMsg != NULL) {
        FreeBuffer(endpoint->context, ipcMsg);
    }
    return EC_INVALID;
}

static void HandleIpc(const Request *request, const Response *response)
{
    void *ipcMsg = (void *)request->data;
    Endpoint *endpoint = (Endpoint *)response->data;
    Router *router = VECTOR_At(&endpoint->routers, request->msgId);
    if (ipcMsg == NULL) {
        return;
    }

    if (router == NULL || router->proxy == NULL || router->proxy->Invoke == NULL) {
        FreeBuffer(endpoint->context, ipcMsg);
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Invalid IPC router<%p>!", router);
        return;
    }

    uid_t uid = GetCallingUid(ipcMsg);
    if ((strcmp(router->saName.service, SAMGR_SERVICE) != 0) &&
        !JudgePolicy(uid, (const PolicyTrans *)(router->policy), router->policyNum)) {
        FreeBuffer(endpoint->context, ipcMsg);
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Consumer uid<%d> has no permission to access<%s, %d, %d>!",
                    uid, router->saName.service, router->identity.serviceId, router->identity.featureId);
        return;
    }

    IpcIo req;
    IpcIoInitFromMsg(&req, ipcMsg);
    IpcIo reply;
    uint8 data[MAX_DATA_LEN];
    IpcIoInit(&reply, data, MAX_DATA_LEN, MAX_OBJECT_NUM);
    router->proxy->Invoke(router->proxy, request->msgValue, ipcMsg, &req, &reply);
    uint32_t flag = 0;
    GetFlag(ipcMsg, &flag);
    if (flag == LITEIPC_FLAG_DEFAULT) {
        SendReply(endpoint->context, ipcMsg, &reply);
    } else {
        FreeBuffer(endpoint->context, ipcMsg);
    }
}
static int CompareIServerProxy(const IServerProxy *proxy1, const IServerProxy *proxy2)
{
    if (proxy1 == proxy2) {
        return 0;
    }
    return (proxy1 > proxy2) ? 1 : -1;
}

static IServerProxy *GetIServerProxy(const Router *router)
{
    if (router == NULL) {
        return NULL;
    }
    return router->proxy;
}

static int RegisterRemoteFeatures(Endpoint *endpoint)
{
    int nums = 0;
    if (g_registerID == NULL) {
        return nums;
    }
    int size = VECTOR_Size(&endpoint->routers);
    int i;
    SvcIdentity identity;
    for (i = 0; i < size; ++i) {
        Router *router = VECTOR_At(&endpoint->routers, i);
        if (router == NULL) {
            continue;
        }

        identity.handle = endpoint->identity.handle;
        identity.token = i;
        int ret = g_registerID(router->saName.service, router->saName.feature, &identity,
                               &(router->policy), &(router->policyNum));
        if (ret == EC_SUCCESS) {
            ++nums;
        }
        HILOG_DEBUG(HILOG_MODULE_SAMGR, "RegisterRemoteFeatures<%s, %s> ret:%d",
                    router->saName.service, router->saName.feature,  ret);
    }
    return VECTOR_Num(&endpoint->routers) - nums;
}

static int RegisterRemoteEndpoint(const IpcContext *context, SvcIdentity *identity)
{
    IpcIo req;
    uint8 data[MAX_DATA_LEN];
    IpcIoInit(&req, data, MAX_DATA_LEN, 0);
    IpcIoPushUint32(&req, RES_ENDPOINT);
    IpcIoPushUint32(&req, OP_POST);
    IpcIoPushUint32(&req, identity->handle);
    uint8 retry = 0;
    while (retry < MAX_RETRY_TIMES) {
        ++retry;
        IpcIo reply;
        void *replyBuf = NULL;
        SvcIdentity samgr = {SAMGR_HANDLE, SAMGR_TOKEN, SAMGR_COOKIE};
        int err = Transact(context, samgr, INVALID_INDEX, &req, &reply, LITEIPC_FLAG_DEFAULT, (uintptr_t *)&replyBuf);
        if (err == LITEIPC_OK) {
            identity->handle = IpcIoPopUint32(&reply);
            if (replyBuf != NULL) {
                FreeBuffer(context, replyBuf);
            }
            if (identity->handle == (uint32)INVALID_INDEX) {
                continue;
            }
            return EC_SUCCESS;
        }
        sleep(RETRY_INTERVAL);
    }
    return EC_FAILURE;
}

static int OnSamgrServerExit(const IpcContext *context, void *ipcMsg, IpcIo *data, void *argv)
{
    (void)data;
    HILOG_ERROR(HILOG_MODULE_SAMGR, "Disconnect to samgr server!");
    Endpoint *endpoint = (Endpoint *)argv;
    if (endpoint == NULL || endpoint->registerEP == NULL) {
        return EC_FAILURE;
    }
    if (ipcMsg != NULL) {
        FreeBuffer(endpoint->context, ipcMsg);
    }
    int size = VECTOR_Size(&endpoint->routers);
    int i;
    for (i = 0; i < size; i++) {
        Router *router = VECTOR_At(&endpoint->routers, i);
        if (router == NULL) {
            continue;
        }
        SAMGR_Free(router->policy);
        router->policy = NULL;
        router->policyNum = 0;
    }

    while (endpoint->registerEP(endpoint->context, &endpoint->identity) != EC_SUCCESS) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Reconnect to samgr server failed!");
        sleep(RETRY_INTERVAL);
    }

    SvcIdentity identity;
    identity.handle = SAMGR_HANDLE;
    identity.token = SAMGR_TOKEN;
    identity.cookie = SAMGR_COOKIE;
    (void)UnRegisteDeathCallback(identity, endpoint->deadId);
    (void)RegisteDeathCallback(endpoint->context, identity, OnSamgrServerExit, endpoint, &endpoint->deadId);
    int remain = RegisterRemoteFeatures(endpoint);
    HILOG_INFO(HILOG_MODULE_SAMGR, "Reconnect and register finished! remain<%d> iunknown!", remain);
    return EC_SUCCESS;
}

static boolean JudgePolicy(uid_t callingUid, const PolicyTrans *policy, uint32 policyNum)
{
    if (policy == NULL) {
        HILOG_ERROR(HILOG_MODULE_SAMGR, "Policy is NULL! Num is %u", policyNum);
        return FALSE;
    }

    uint32 i;
    for (i = 0; i < policyNum; i++) {
        if (policy[i].type == RANGE && callingUid >= policy[i].uidMin && callingUid <= policy[i].uidMax) {
            return TRUE;
        }
        if (policy[i].type == FIXED && SearchFixedPolicy(callingUid, policy[i])) {
            return TRUE;
        }
    }
    return FALSE;
}

static boolean SearchFixedPolicy(uid_t callingUid, PolicyTrans policy)
{
    int i;
    for (i = 0; i < UID_SIZE; i++) {
        if (callingUid == policy.fixedUid[i]) {
            return TRUE;
        }
    }
    return FALSE;
}