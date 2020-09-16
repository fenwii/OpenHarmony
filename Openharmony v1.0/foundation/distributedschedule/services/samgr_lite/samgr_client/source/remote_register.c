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
#include "remote_register.h"
#include <ohos_errno.h>
#include <ohos_init.h>
#include <liteipc_adapter.h>
#include <log.h>
#include "policy_define.h"
#include "samgr_lite.h"
#include "memory_adapter.h"
#include "thread_adapter.h"
#include "iproxy_client.h"
#include "default_client.h"

#undef LOG_TAG
#undef LOG_DOMAIN
#define LOG_TAG "Samgr"
#define LOG_DOMAIN 0xD001800

#define RETRY_INTERVAL 2
#define MAX_RETRY_TIMES 10
#define MAX_POLICY_NUM 8
static void InitializeRegistry(void);
static SvcIdentity QueryRemoteIdentity(const char *service, const char *feature);
static int RegisterRemoteIdentity(const char *service, const char *feature, SvcIdentity *saInfo,
                                  PolicyTrans **policy, uint32 *policyNum);
static void GetRemotePolicy(IpcIo *reply, PolicyTrans **policy, uint32 *policyNum);
static RemoteRegister g_remoteRegister;

int __attribute__((weak)) SAMGR_RegisterServiceApi(const char *service, const char *feature,
                                                   const Identity *identity, IUnknown *iUnknown)
{
    if (service == NULL) {
        return EC_INVALID;
    }
    InitializeRegistry();
    MUTEX_Lock(g_remoteRegister.mtx);
    SaName saName = {service, feature};
    int32 token = SAMGR_AddRouter(g_remoteRegister.endpoint, &saName, identity, iUnknown);
    MUTEX_Unlock(g_remoteRegister.mtx);
    if (token < 0 || !g_remoteRegister.endpoint->running) {
        return token;
    }
    return SAMGR_ProcPolicy(g_remoteRegister.endpoint, &saName, token);
}

IUnknown *__attribute__((weak)) SAMGR_FindServiceApi(const char *service, const char *feature)
{
    InitializeRegistry();
    SaName key = {service, feature};
    // the proxy already exits.
    int index = VECTOR_FindByKey(&g_remoteRegister.clients, &key);
    if (index != INVALID_INDEX) {
        return VECTOR_At(&g_remoteRegister.clients, index);
    }

    SvcIdentity identity = QueryRemoteIdentity(service, feature);
    if (identity.handle == INVALID_INDEX) {
        return NULL;
    }
    MUTEX_Lock(g_remoteRegister.mtx);
    index = VECTOR_FindByKey(&g_remoteRegister.clients, &key);
    if (index != INVALID_INDEX) {
        MUTEX_Unlock(g_remoteRegister.mtx);
        return VECTOR_At(&g_remoteRegister.clients, index);
    }
    IUnknown *proxy = SAMGR_CreateIProxy(g_remoteRegister.endpoint->context, service, feature, identity);
    VECTOR_Add(&g_remoteRegister.clients, proxy);
    MUTEX_Unlock(g_remoteRegister.mtx);
    HILOG_INFO(HILOG_MODULE_SAMGR, "Create remote sa proxy[%p]<%s, %s> id<%u,%u>!",
               proxy, service, feature, identity.handle, identity.token);
    return proxy;
}

static SvcIdentity QueryRemoteIdentity(const char *service, const char *feature)
{
    IpcIo req;
    uint8 data[MIN_DATA_LEN];
    IpcIoInit(&req, data, MIN_DATA_LEN, 0);
    IpcIoPushUint32(&req, RES_FEATURE);
    IpcIoPushUint32(&req, OP_GET);
    IpcIoPushString(&req, service);
    IpcIoPushBool(&req, feature == NULL);
    if (feature != NULL) {
        IpcIoPushString(&req, feature);
    }
    IpcIo reply;
    void *replyBuf = NULL;
    SvcIdentity samgr = {SAMGR_HANDLE, SAMGR_TOKEN, SAMGR_COOKIE};
    int ret = Transact(g_remoteRegister.endpoint->context, samgr, INVALID_INDEX, &req, &reply,
                       LITEIPC_FLAG_DEFAULT, (uintptr_t *)&replyBuf);
    ret = (ret != LITEIPC_OK) ? EC_FAILURE : IpcIoPopInt32(&reply);
    SvcIdentity target = {INVALID_INDEX, INVALID_INDEX, INVALID_INDEX};
    if (ret == EC_SUCCESS) {
        SvcIdentity *svc = IpcIoPopSvc(&reply);
        if (svc != NULL) {
            target = *svc;
        }
    }
    if (ret == EC_PERMISSION) {
        HILOG_INFO(HILOG_MODULE_SAMGR, "Cannot Access<%s, %s> No Permission!", service, feature);
    }
    if (replyBuf != NULL) {
        FreeBuffer(g_remoteRegister.endpoint->context, replyBuf);
    }
    return target;
}

static int RegisterRemoteIdentity(const char *service, const char *feature, SvcIdentity *saInfo,
                                  PolicyTrans **policy, uint32 *policyNum)
{
    IpcIo req;
    uint8 data[MIN_DATA_LEN];
    IpcIoInit(&req, data, MIN_DATA_LEN, 0);
    IpcIoPushUint32(&req, RES_FEATURE);
    IpcIoPushUint32(&req, OP_PUT);
    IpcIoPushString(&req, service);
    IpcIoPushBool(&req, feature == NULL);
    if (feature != NULL) {
        IpcIoPushString(&req, feature);
    }
    IpcIoPushUint32(&req, saInfo->token);
    IpcIo reply;
    void *replyBuf = NULL;
    SvcIdentity samgr = {SAMGR_HANDLE, SAMGR_TOKEN, SAMGR_COOKIE};
    int ret = Transact(g_remoteRegister.endpoint->context, samgr, INVALID_INDEX, &req, &reply,
                       LITEIPC_FLAG_DEFAULT, (uintptr_t *)&replyBuf);
    ret = -ret;
    if (ret == LITEIPC_OK) {
        ret = IpcIoPopInt32(&reply);
    }
    if (ret == EC_SUCCESS) {
        saInfo = IpcIoPopSvc(&reply);
        GetRemotePolicy(&reply, policy, policyNum);
    }
    if (replyBuf != NULL) {
        FreeBuffer(g_remoteRegister.endpoint->context, replyBuf);
    }
    return ret;
}

static void GetRemotePolicy(IpcIo *reply, PolicyTrans **policy, uint32 *policyNum)
{
    if (reply == NULL) {
        return;
    }
    uint32 i;
    uint32 j;
    *policyNum = IpcIoPopUint32(reply);
    if (*policyNum > MAX_POLICY_NUM) {
        *policyNum = MAX_POLICY_NUM;
    }
    SAMGR_Free(*policy);
    if (*policyNum == 0) {
        *policy = NULL;
        return;
    }
    *policy = (PolicyTrans *)SAMGR_Malloc(sizeof(PolicyTrans) * (*policyNum));
    if (*policy == NULL) {
        return;
    }
    for (i = 0; i < *policyNum; i++) {
        (*policy)[i].type = IpcIoPopInt32(reply);
        switch ((*policy)[i].type) {
            case RANGE:
                (*policy)[i].uidMin = IpcIoPopInt32(reply);
                (*policy)[i].uidMax = IpcIoPopInt32(reply);
                break;
            case FIXED:
                for (j = 0; j < UID_SIZE; j++) {
                    (*policy)[i].fixedUid[j] = IpcIoPopInt32(reply);
                }
                break;
            case BUNDLENAME:
                (*policy)[i].fixedUid[0] = IpcIoPopInt32(reply);
                break;
            default:
                break;
        }
    }
}

static void InitializeRegistry(void)
{
    if (g_remoteRegister.endpoint != NULL) {
        return;
    }
    HILOG_INFO(HILOG_MODULE_SAMGR, "Initialize Registry!");
    SAMGR_RegisterQueryIdentity(QueryRemoteIdentity);
    SAMGR_RegisterRegisterIdentity(RegisterRemoteIdentity);
    g_remoteRegister.mtx = MUTEX_InitValue();
    g_remoteRegister.clients = VECTOR_Make((VECTOR_Key)SAMGR_GetSAName, (VECTOR_Compare)SAMGR_CompareSAName);
    g_remoteRegister.endpoint = SAMGR_CreateEndpoint("ipc client", NULL);
}
