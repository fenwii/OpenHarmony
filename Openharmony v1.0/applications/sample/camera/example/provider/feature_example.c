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
#include <ohos_init.h>
#include <securec.h>
#include <samgr_maintenance.h>
#include <log.h>
#include <unistd.h>
#include <pthread.h>
#include <ohos_errno.h>
#include "feature.h"
#include "service.h"
#include "samgr_lite.h"

#define WAIT_FEATURE_PROC 1000
enum MessageId {
    MSG_PROC,
    MSG_TIME_PROC,
};
typedef struct DemoFeatureApi {
    INHERIT_SERVER_IPROXY;
    BOOL (*AsyncCall)(IUnknown *iUnknown, const char *buff);
    BOOL (*AsyncTimeCall)(IUnknown *iUnknown);
    BOOL (*SyncCall)(IUnknown *iUnknown, struct Payload *payload);
    BOOL (*AsyncCallBack)(IUnknown *iUnknown, const char *buff, IOwner notify, INotifyFunc handler);
} DemoFeatureApi;

typedef struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoFeatureApi);
    Identity identity;
} DemoFeature;

static BOOL AsyncCall(IUnknown *iUnknown, const char *body);
static BOOL AsyncTimeCall(IUnknown *iUnknown);
static BOOL SyncCall(IUnknown *iUnknown, struct Payload *payload);
static BOOL AsyncCallBack(IUnknown *iUnknown, const char *body, IOwner notify, INotifyFunc handler);
static const char *FEATURE_GetName(Feature *feature);
static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity);
static void FEATURE_OnStop(Feature *feature, Identity identity);
static BOOL FEATURE_OnMessage(Feature *feature, Request *request);
static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);
static DemoFeature g_example = {
    .GetName = FEATURE_GetName,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage,
    SERVER_IPROXY_IMPL_BEGIN,
    .Invoke = Invoke,
    .AsyncCall = AsyncCall,
    .AsyncTimeCall = AsyncTimeCall,
    .SyncCall = SyncCall,
    .AsyncCallBack = AsyncCallBack,
    IPROXY_END,
    .identity = {-1, -1, NULL},
};
static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return EXAMPLE_FEATURE;
}

static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->identity = identity;
}

static void FEATURE_OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
    g_example.identity.queueId = NULL;
    g_example.identity.featureId = -1;
    g_example.identity.serviceId = -1;
}

static BOOL FEATURE_OnMessage(Feature *feature, Request *msg)
{
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]OnMessage(%s)! Request<%d, %d, %p>",
               (unsigned long)pthread_self(), feature->GetName(feature), msg->msgId, msg->msgValue, msg->data);
    if (msg->msgId == MSG_PROC) {
        Response response;
        response.data = "Yes, you did!";
        response.len = 0;
        SAMGR_SendResponse(msg, &response);
        return TRUE;
    }
    if (msg->msgId == MSG_TIME_PROC) {
        if (msg->msgValue) {
            SAMGR_PrintServices();
        } else {
            SAMGR_PrintOperations();
        }
        return TRUE;
    }
    return FALSE;
}

static BOOL SyncCall(IUnknown *iUnknown, struct Payload *payload)
{
    (void)iUnknown;
    if (payload != NULL && payload->name != NULL) {
        HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]SyncCall[%p, %p]! Payload<%s, %d, %d>",
                   (unsigned long)pthread_self(), iUnknown, payload, payload->name, payload->id, payload->value);
        return TRUE;
    }
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]SyncCall[%p, %p]!", (unsigned long)pthread_self(), iUnknown, payload);
    return FALSE;
}

static BOOL AsyncCall(IUnknown *iUnknown, const char *body)
{
    Request request;
    request.msgId = MSG_PROC;
    request.msgValue = 0;
    request.len = (uint32_t)(strlen(body) + 1);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        return FALSE;
    }
    if (strcpy_s(request.data, request.len, body) != EOK) {
        free(request.data);
        return FALSE;
    }
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncCall[%p, %s]!", (unsigned long)pthread_self(), iUnknown, body);
    return SAMGR_SendRequest(&feature->identity, &request, NULL);
}
static BOOL AsyncTimeCall(IUnknown *iUnknown)
{
    static BOOL cnt = FALSE;
    cnt = !cnt;
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncTimeCall[%p] MSG_TIME_PROC count=%d!",
               (unsigned long)pthread_self(), iUnknown, cnt);
    Request request;
    request.msgId = MSG_TIME_PROC;
    request.msgValue = cnt;
    request.len = 0;
    request.data = NULL;
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    return SAMGR_SendRequest(&feature->identity, &request, NULL);
}
typedef struct AsyncBody {
    IOwner owner;
    INotifyFunc handler;
    char body[0];
} AsyncBody;
static void LocalHandler(const Request *request, const Response *response)
{
    AsyncBody *body = (AsyncBody *)request->data;
    body->handler(body->owner, response->data);
}
static BOOL AsyncCallBack(IUnknown *iUnknown, const char *body, IOwner notify, INotifyFunc handler)
{
    int len = strlen(body) + 1;
    Request request;
    request.msgId = MSG_PROC;
    request.msgValue = 0;
    request.len = (uint32_t)(sizeof(struct AsyncBody) + len);
    request.data = malloc(request.len);
    if (request.data == NULL) {
        return FALSE;
    }
    if (strcpy_s(((AsyncBody *)request.data)->body, len, body) != EOK) {
        free(request.data);
        return FALSE;
    }
    ((AsyncBody *)request.data)->owner = notify;
    ((AsyncBody *)request.data)->handler = handler;
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]AsyncCallBack[%p, %s, %p, %p]!",
               (unsigned long)pthread_self(), iUnknown, body, notify, handler);
    return SAMGR_SendRequest(&feature->identity, &request, LocalHandler);
}
enum FUNCID {
    ID_ASYNCALL = 0,
    ID_ASYNTIMECALL,
    ID_SYNCCALL,
    ID_ASYNCCALLBACK
};
static int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    HILOG_INFO(HILOG_MODULE_APP, "[TID:0x%lx]Feature Remote Invoke is called! <%p, %d, %p, %p, %p>",
               (unsigned long)pthread_self(), iProxy, funcId, origin, req, reply);
    DemoFeatureApi *api = (DemoFeatureApi *)iProxy;
    BOOL ret;
    size_t len = 0;
    switch (funcId) {
        case ID_ASYNCALL:
            ret = api->AsyncCall((IUnknown *)iProxy, (char *)IpcIoPopString(req, &len));
            IpcIoPushBool(reply, ret);
            break;
        case ID_ASYNTIMECALL:
            ret = api->AsyncTimeCall((IUnknown *)iProxy);
            IpcIoPushBool(reply, ret);
            break;
        case ID_SYNCCALL: {
            struct Payload payload;
            payload.id = IpcIoPopInt32(req);
            payload.value = IpcIoPopInt32(req);
            payload.name = (char *)IpcIoPopString(req, &len);
            ret = api->SyncCall((IUnknown *)iProxy, &payload);
            IpcIoPushString(reply, ret ? "TRUE" : "FALSE");
        }
            break;
        case ID_ASYNCCALLBACK: { // convert to sync proxy
            IpcIoPushString(reply, "Yes, you did!");
            IpcIoPushBool(reply, TRUE);
        }
            break;
        default:
            IpcIoPushBool(reply, FALSE);
            break;
    }
    return EC_SUCCESS;
}
static void Init(void)
{
    SAMGR_GetInstance()->RegisterFeature(EXAMPLE_SERVICE, (Feature *)&g_example);
    SAMGR_GetInstance()->RegisterFeatureApi(EXAMPLE_SERVICE, EXAMPLE_FEATURE, GET_IUNKNOWN(g_example));
}
SYSEX_FEATURE_INIT(Init);

