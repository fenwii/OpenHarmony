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
#include "default_client.h"
#include <ohos_errno.h>
#include <string.h>
#include <log.h>
#include "client_factory.h"
#include "iproxy_client.h"
#include "memory_adapter.h"
#include "thread_adapter.h"

#undef LOG_TAG
#undef LOG_DOMAIN
#define LOG_TAG "Samgr"
#define LOG_DOMAIN 0xD001800

typedef struct IClientHeader IClientHeader;
typedef struct IDefaultClient IDefaultClient;
typedef struct IClientEntry IClientEntry;
struct IClientHeader {
    SaName key;
    SvcIdentity target;
    uint32 deadId;
    const IpcContext *context;
};

struct IClientEntry {
    INHERIT_IUNKNOWNENTRY(IClientProxy);
};

#pragma pack(1)
struct IDefaultClient {
    IClientHeader header;
    IClientEntry entry;
};
#pragma pack()

static int AddRef(IUnknown *iUnknown);
static int Release(IUnknown *proxy);
static int ProxyInvoke(IClientProxy *proxy, int funcId, IpcIo *request, IOwner owner, INotify notify);
static int OnServiceExit(const IpcContext *context, void *ipcMsg, IpcIo *data, void *argv);
static const IClientEntry DEFAULT_ENTRY = {CLIENT_IPROXY_BEGIN, .Invoke = ProxyInvoke, IPROXY_END};
static MutexId g_mutex = NULL;
static QueryIdentity g_queryID = NULL;

IUnknown *SAMGR_CreateIProxy(const IpcContext *context, const char *service, const char *feature, SvcIdentity identity)
{
    if (g_queryID == NULL) {
        return NULL;
    }

    IDefaultClient *client = SAMGR_CreateIClient(service, feature, sizeof(IClientHeader));
    if (client == NULL) {
        client = SAMGR_Malloc(sizeof(IDefaultClient));
        if (client == NULL) {
            return NULL;
        }
        client->entry = DEFAULT_ENTRY;
    }

    IClientHeader *header = &client->header;
    header->target = identity;
    header->key.service = service;
    header->key.feature = feature;
    header->context = context;
    (void)RegisteDeathCallback(context, identity, OnServiceExit, client, &header->deadId);

    IClientEntry *entry = &client->entry;
    entry->iUnknown.Invoke = ProxyInvoke;
    entry->iUnknown.AddRef = AddRef;
    entry->iUnknown.Release = Release;
    return GET_IUNKNOWN(*entry);
}

int SAMGR_RegisterQueryIdentity(QueryIdentity query)
{
    if (g_mutex == NULL) {
        g_mutex = MUTEX_InitValue();
    }

    if (query == NULL || g_queryID != NULL) {
        return EC_INVALID;
    }

    g_queryID = query;
    return EC_SUCCESS;
}

SvcIdentity SAMGR_GetRemoteIdentity(const char *service, const char *feature)
{
    if (g_queryID != NULL) {
        return g_queryID(service, feature);
    }
    SvcIdentity identity = {INVALID_INDEX, INVALID_INDEX, INVALID_INDEX};
    return identity;
}

SaName *SAMGR_GetSAName(const IUnknown *proxy)
{
    IDefaultClient *client = GET_OBJECT(proxy, IDefaultClient, entry.iUnknown);
    return &(client->header.key);
}

int SAMGR_CompareSAName(const SaName *key1, const SaName *key2)
{
    if (key1 == key2) {
        return 0;
    }

    if (key1->service != key2->service) {
        int ret = strcmp(key1->service, key2->service);
        if (ret != 0) {
            return ret;
        }
    }

    if (key1->feature == key2->feature) {
        return 0;
    }

    if (key1->feature == NULL) {
        return -1;
    }

    if (key2->feature == NULL) {
        return 1;
    }

    return strcmp(key1->feature, key2->feature);
}

static int AddRef(IUnknown *iUnknown)
{
    MUTEX_Lock(g_mutex);
    int ref = IUNKNOWN_AddRef(iUnknown);
    MUTEX_Unlock(g_mutex);
    return ref;
}

static int Release(IUnknown *proxy)
{
    MUTEX_Lock(g_mutex);
    int ref = IUNKNOWN_Release(proxy);
    MUTEX_Unlock(g_mutex);
    if (ref != 0) {
        return ref;
    }
    IDefaultClient *client = GET_OBJECT(proxy, IDefaultClient, entry.iUnknown);
    int ret = SAMGR_ReleaseIClient(client->header.key.service, client->header.key.feature, client);
    if (ret == EC_NOHANDLER) {
        SAMGR_Free(client);
        return EC_SUCCESS;
    }
    return ret;
}

static int ProxyInvoke(IClientProxy *proxy, int funcId, IpcIo *request, IOwner owner, INotify notify)
{
    if (proxy == NULL) {
        return EC_INVALID;
    }

    IDefaultClient *client = GET_OBJECT(proxy, IDefaultClient, entry.iUnknown);
    IClientHeader *header = &client->header;
    if (header->target.handle == INVALID_INDEX) {
        header->target = g_queryID(header->key.service, header->key.feature);
        if (header->target.handle == INVALID_INDEX) {
            return EC_INVALID;
        }
        (void)RegisteDeathCallback(header->context, header->target, OnServiceExit, header, &header->deadId);
    }

    IpcIo reply;
    void *replyBuf = NULL;
    IpcFlag flag = (notify == NULL) ? LITEIPC_FLAG_ONEWAY : LITEIPC_FLAG_DEFAULT;
    int ret = Transact(header->context, header->target, funcId, request, &reply, flag, (uintptr_t *)&replyBuf);
    if (ret != LITEIPC_OK) {
        (void)UnRegisteDeathCallback(header->target, header->deadId);
        header->deadId = INVALID_INDEX;
        header->target.handle = INVALID_INDEX;
        header->target.token = INVALID_INDEX;
        header->target.cookie = INVALID_INDEX;
        return EC_FAILURE;
    }

    if (notify != NULL) {
        notify(owner, ret, &reply);
    }

    if (replyBuf != NULL) {
        FreeBuffer(header->context, replyBuf);
    }
    return ret;
}

static int OnServiceExit(const IpcContext *context, void *ipcMsg, IpcIo *data, void *argv)
{
    (void)data;
    IClientHeader *header = (IClientHeader *)argv;
    (void)UnRegisteDeathCallback(header->target, header->deadId);
    header->deadId = INVALID_INDEX;
    header->target.handle = INVALID_INDEX;
    header->target.token = INVALID_INDEX;
    header->target.cookie = INVALID_INDEX;
    if (ipcMsg != NULL) {
        FreeBuffer(header->context, ipcMsg);
    }
    HILOG_ERROR(HILOG_MODULE_SAMGR, "Miss the remote service<%u, %u>!", header->target.handle, header->target.token);
    return EC_SUCCESS;
}
