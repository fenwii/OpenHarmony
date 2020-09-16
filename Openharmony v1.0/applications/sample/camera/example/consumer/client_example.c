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
#include <pthread.h>
#include <securec.h>
#include <ohos_errno.h>
#include <log.h>
#include <iproxy_client.h>

#define MAX_DATA_LEN 0x100
enum FUNCID {
    ID_ASYNCALL = 0,
    ID_ASYNTIMECALL,
    ID_SYNCCALL,
    ID_ASYNCCALLBACK
};
typedef struct DemoClientProxy {
    INHERIT_CLIENT_IPROXY;
    BOOL (*AsyncCall)(IUnknown *iUnknown, const char *buff);
    BOOL (*AsyncTimeCall)(IUnknown *iUnknown);
    BOOL (*SyncCall)(IUnknown *iUnknown, struct Payload *payload);
    BOOL (*AsyncCallBack)(IUnknown *iUnknown, const char *buff, IOwner notify, INotifyFunc handler);
} DemoClientProxy;

typedef struct DemoClientEntry {
    INHERIT_IUNKNOWNENTRY(DemoClientProxy);
} DemoClientEntry;
static BOOL AsyncCall(IUnknown *iUnknown, const char *buff);
static BOOL AsyncTimeCall(IUnknown *iUnknown);
static BOOL SyncCall(IUnknown *iUnknown, struct Payload *payload);
static BOOL AsyncCallBack(IUnknown *iUnknown, const char *buff, IOwner notify, INotifyFunc handler);
void *DEMO_CreatClient(const char *service, const char *feature, uint32 size)
{
    (void)service;
    (void)feature;
    uint32 len = size + sizeof(DemoClientEntry);
    uint8 *client = malloc(len);
    if (client == NULL) {
        return NULL;
    }
    (void)memset_s(client, len, 0, len);
    DemoClientEntry *entry = (DemoClientEntry *)&client[size];
    entry->ver = ((uint16)CLIENT_PROXY_VER | (uint16)DEFAULT_VERSION);
    entry->ref = 1;
    entry->iUnknown.QueryInterface = IUNKNOWN_QueryInterface;
    entry->iUnknown.AddRef = IUNKNOWN_AddRef;
    entry->iUnknown.Release = IUNKNOWN_Release;
    entry->iUnknown.Invoke = NULL;
    entry->iUnknown.AsyncCall = AsyncCall;
    entry->iUnknown.AsyncTimeCall = AsyncTimeCall;
    entry->iUnknown.SyncCall = SyncCall;
    entry->iUnknown.AsyncCallBack = AsyncCallBack;
    return client;
}
void DEMO_DestroyClient(const char *service, const char *feature, void *iproxy)
{
    free(iproxy);
}

static BOOL AsyncCall(IUnknown *iUnknown, const char *buff)
{
    DemoClientProxy *proxy = (DemoClientProxy *)iUnknown;
    IpcIo request;
    char data[MAX_DATA_LEN];
    IpcIoInit(&request, data, MAX_DATA_LEN, 0);
    IpcIoPushString(&request, buff);
    int ret = proxy->Invoke((IClientProxy *)proxy, ID_ASYNCALL, &request, NULL, NULL);
    return ret == EC_SUCCESS;
}
static BOOL AsyncTimeCall(IUnknown *iUnknown)
{
    DemoClientProxy *proxy = (DemoClientProxy *)iUnknown;
    IpcIo request;
    char data[MAX_DATA_LEN];
    IpcIoInit(&request, data, MAX_DATA_LEN, 0);
    int ret = proxy->Invoke((IClientProxy *)proxy, ID_ASYNTIMECALL, &request, NULL, NULL);
    return ret == EC_SUCCESS;
}

static int Callback(IOwner owner, int code, IpcIo *reply)
{
    size_t len = 0;
    char *src = (char *)IpcIoPopString(reply, &len);
    if (src == NULL) {
        return EC_BADPTR;
    }
    return strcpy_s(owner, MAX_DATA_LEN, src);
}
static BOOL SyncCall(IUnknown *iUnknown, struct Payload *payload)
{
    DemoClientProxy *proxy = (DemoClientProxy *)iUnknown;
    IpcIo request;
    char data[MAX_DATA_LEN];
    IpcIoInit(&request, data, MAX_DATA_LEN, 0);
    IpcIoPushInt32(&request, payload->id);
    IpcIoPushInt32(&request, payload->value);
    IpcIoPushString(&request, payload->name);
    int ret = proxy->Invoke((IClientProxy *)proxy, ID_SYNCCALL, &request, data, Callback);
    data[MAX_DATA_LEN - 1] = 0;
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]Remote response is %s!", (unsigned long)pthread_self(), data);
    return ret == EC_SUCCESS;
}
struct CurrentNotify {
    IOwner notify;
    INotifyFunc handler;
};
static int CurrentCallback(IOwner owner, int code, IpcIo *reply)
{
    struct CurrentNotify *notify = (struct CurrentNotify *)owner;
    size_t len = 0;
    char *response = (char *)IpcIoPopString(reply, &len);
    if (response == NULL) {
        return EC_BADPTR;
    }
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]Notify Remote response is %s!", (unsigned long)pthread_self(), response);
    notify->handler(notify->notify, response);
    return EC_SUCCESS;
}

static BOOL AsyncCallBack(IUnknown *iUnknown, const char *buff, IOwner notify, INotifyFunc handler)
{
    struct CurrentNotify owner = {notify, handler};
    DemoClientProxy *proxy = (DemoClientProxy *)iUnknown;
    IpcIo request;
    char data[MAX_DATA_LEN];
    IpcIoInit(&request, data, MAX_DATA_LEN, 0);
    IpcIoPushString(&request, buff);
    int ret = proxy->Invoke((IClientProxy *)proxy, ID_ASYNCCALLBACK, &request, &owner, CurrentCallback);
    return ret == EC_SUCCESS;
}
