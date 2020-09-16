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
#include <los_base.h>
#include <cmsis_os.h>
#include <samgr_maintenance.h>
#include "iunknown.h"
#include "feature.h"
#include "service.h"
#include "samgr_lite.h"

#define WAIT_FEATURE_PROC 1000
enum MessageId {
    MSG_PROC,
    MSG_TIME_PROC,
};

struct Payload {
    int id;
    const char *name;
    int value;
};

typedef struct DemoApi {
    INHERIT_IUNKNOWN;
    BOOL (*AsyncCall)(IUnknown *iUnknown, const char *buff);
    BOOL (*AsyncTimeCall)(IUnknown *iUnknown);
    BOOL (*SyncCall)(IUnknown *iUnknown, struct Payload *payload);
    BOOL (*AsyncCallBack)(IUnknown *iUnknown, const char *buff, Handler handler);
} DemoApi;

typedef struct DemoFeature {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(DemoApi);
    Identity identity;
} DemoFeature;

static BOOL AsyncCall(IUnknown *iUnknown, const char *body);
static BOOL AsyncTimeCall(IUnknown *iUnknown);
static BOOL SyncCall(IUnknown *iUnknown, struct Payload *payload);
static BOOL AsyncCallBack(IUnknown *iUnknown, const char *body, Handler handler);
static const char *FEATURE_GetName(Feature *feature);
static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity);
static void FEATURE_OnStop(Feature *feature, Identity identity);
static BOOL FEATURE_OnMessage(Feature *feature, Request *request);
static DemoFeature g_example = {
    .GetName = FEATURE_GetName,
    .OnInitialize = FEATURE_OnInitialize,
    .OnStop = FEATURE_OnStop,
    .OnMessage = FEATURE_OnMessage,
    DEFAULT_IUNKNOWN_ENTRY_BEGIN,
    .AsyncCall = AsyncCall,
    .AsyncTimeCall = AsyncTimeCall,
    .SyncCall = SyncCall,
    .AsyncCallBack = AsyncCallBack,
    DEFAULT_IUNKNOWN_ENTRY_END,
    .identity = {-1, -1, NULL},
};
static int g_regStep = 0;
static const char *FEATURE_GetName(Feature *feature)
{
    (void)feature;
    return EXAMPLE_FEATURE;
}

static void FEATURE_OnInitialize(Feature *feature, Service *parent, Identity identity)
{
    DemoFeature *demoFeature = (DemoFeature *)feature;
    demoFeature->identity = identity;
    printf("[Register Test][TaskID:%p][Step:%d][Reg Finish S:%s, F:%s]Time: %llu!\n",
           osThreadGetId(), g_regStep++, parent->GetName(parent), feature->GetName(feature), SAMGR_GetProcessTime());
}

static void FEATURE_OnStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
    g_example.identity.queueId = NULL;
    g_example.identity.featureId = -1;
    g_example.identity.serviceId = -1;
}

static volatile uint32 g_asyncStep = 0;
static BOOL FEATURE_OnMessage(Feature *feature, Request *request)
{
    (void)feature;
    if (request->msgId == MSG_PROC) {
        printf("[LPC Test][TaskID:%p][Step:%d][OnMessage: S:%s, F:%s] msgId<MSG_PROC> %s \n",
               osThreadGetId(), g_asyncStep++, EXAMPLE_SERVICE, feature->GetName(feature), (char *)request->data);
        Response response = {.data = "Yes, you did!", .len = 0};
        SAMGR_SendResponse(request, &response);
        return TRUE;
    } else {
        if (request->msgId == MSG_TIME_PROC) {
            LOS_Msleep(WAIT_FEATURE_PROC * 11); // sleep 11 seconds
            if (request->msgValue) {
                SAMGR_PrintServices();
            } else {
                SAMGR_PrintOperations();
            }
            AsyncTimeCall(GET_IUNKNOWN(g_example));
            return FALSE;
        }
    }
    printf("[LPC Test][TaskID:%p][Step:%d][OnMessage S:%s, F:%s] Inner Error! \n",
           osThreadGetId(), g_asyncStep++, EXAMPLE_SERVICE, feature->GetName(feature));
    return FALSE;
}

static BOOL SyncCall(IUnknown *iUnknown, struct Payload *payload)
{
    (void)iUnknown;
    if (payload != NULL && payload->id >= 0 && payload->name != NULL) {
        printf("[LPC Test][TaskID:%p][Step:%d][SyncCall API] Id:%d, name:%s, value:%d \n",
               osThreadGetId(), g_asyncStep++, payload->id, payload->name, payload->value);
        return TRUE;
    }
    printf("[LPC Test][TaskID:%p][Step:%d][SyncCall API] Input Error! \n", osThreadGetId(), g_asyncStep++);
    return FALSE;
}

static BOOL AsyncCall(IUnknown *iUnknown, const char *body)
{
    Request request = {.msgId = MSG_PROC, .msgValue = 0};
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
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCall API] Send request! \n", osThreadGetId(), g_asyncStep++);
    return SAMGR_SendRequest(&feature->identity, &request, NULL);
}
static BOOL AsyncTimeCall(IUnknown *iUnknown)
{
    static int8 cnt = 0;
    cnt = (cnt + 1) % 2; // mod 2 to get async status
    Request request = {.msgId = MSG_TIME_PROC, .msgValue = cnt};
    DemoFeature *feature = GET_OBJECT(iUnknown, DemoFeature, iUnknown);
    return SAMGR_SendRequest(&feature->identity, &request, NULL);
}
static BOOL AsyncCallBack(IUnknown *iUnknown, const char *body, Handler handler)
{
    Request request = {.msgId = MSG_PROC, .msgValue = 0};
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
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCallBack API] Send request! \n",
           osThreadGetId(), g_asyncStep++);
    return SAMGR_SendRequest(&feature->identity, &request, handler);
}

static void Init(void)
{
    SAMGR_GetInstance()->RegisterFeature(EXAMPLE_SERVICE, (Feature *)&g_example);
    SAMGR_GetInstance()->RegisterFeatureApi(EXAMPLE_SERVICE, EXAMPLE_FEATURE, GET_IUNKNOWN(g_example));
    printf("[Register Test][TaskID:%p][Step:%d][Reg S:%s, F:%s]Time: %llu!\n",
           osThreadGetId(), g_regStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE, SAMGR_GetProcessTime());
}
SYSEX_FEATURE_INIT(Init);
static int g_discoverStep = 0;
static DemoApi *CASE_GetIUnknown(void)
{
    DemoApi *demoApi = NULL;
    printf("[Discover Test][TaskID:%p][Step:%d][GetIUnknown S:%s, F:%s]: BEGIN\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE);
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(EXAMPLE_SERVICE, EXAMPLE_FEATURE);
    if (iUnknown == NULL) {
        printf("[Discover Test][TaskID:%p][Step:%d][GetFeatureApi S:%s, F:%s]Error is NULL!\n",
               osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE);
        goto END;
    }
    int result = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)&demoApi);
    if (result != 0 || demoApi == NULL) {
        printf("[Discover Test][TaskID:%p][Step:%d][QueryInterface S:%s, F:%s]Error is NULL!\n",
               osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE);
        goto END;
    }
    printf("[Discover Test][TaskID:%p][Step:%d][GetIUnknown S:%s, F:%s]Success\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE);
END:
    printf("[Discover Test][TaskID:%p][Step:%d][GetIUnknown S:%s, F:%s]: END\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE);
    return demoApi;
}

static void CASE_SyncCall(DemoApi *demoApi)
{
    if (demoApi->SyncCall == NULL) {
        return;
    }
    printf("[LPC Test][TaskID:%p][Step:%d][SyncCall]: BEGIN! \n", osThreadGetId(), g_asyncStep++);
    struct Payload payload = {
        .id = 0,
        .name = "I wanna sync call good result!",
        .value = 1
    };
    if (!demoApi->SyncCall((IUnknown *)demoApi, &payload)) {
        printf("[LPC Test][TaskID:%p][Step:%d][SyncCall]Error return false! \n",
               osThreadGetId(), g_asyncStep++);
        goto END;
    }
    printf("[LPC Test][TaskID:%p][Step:%d][SyncCall]Success!\n",
           osThreadGetId(), g_asyncStep++);
END:
    printf("[LPC Test][TaskID:%p][Step:%d][SyncCall]: END\n",
           osThreadGetId(), g_asyncStep++);
}


static void CASE_AsyncCall(DemoApi *demoApi)
{
    if (demoApi->AsyncCall == NULL) {
        return;
    }
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCall]: BEGIN! \n", osThreadGetId(), g_asyncStep++);
    uint32 count = g_asyncStep;
    demoApi->AsyncCall((IUnknown *)demoApi, "I wanna async call good result!");
    LOS_Msleep(WAIT_FEATURE_PROC);
    if (count == g_asyncStep) {
        printf("[LPC Test][TaskID:%p][Step:%d][AsyncCall] result is faild! \n", osThreadGetId(), g_asyncStep++);
        goto END;
    }
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCall]Success! \n", osThreadGetId(), g_asyncStep++);
END:
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCall]: END! \n", osThreadGetId(), g_asyncStep++);
}

static void CASE_AsyncTimeCall(DemoApi *demoApi)
{
    if (demoApi->AsyncCall == NULL) {
        return;
    }
    demoApi->AsyncTimeCall((IUnknown *)demoApi);
}

void AsyncHandler(const Request *request, const Response *response)
{
    (void)request;
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCallBack]Success! Response:%s \n",
           osThreadGetId(), g_asyncStep++, (char *)response->data);
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCallBack]: END! \n", osThreadGetId(), g_asyncStep++);
}

static void CASE_AsyncCallBack(DemoApi *demoApi)
{
    if (demoApi->AsyncCallBack == NULL) {
        return;
    }
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCallBack]: BEGIN! \n", osThreadGetId(), g_asyncStep++);
    demoApi->AsyncCallBack((IUnknown *)demoApi, "I wanna async call callback good result!", AsyncHandler);
    printf("[LPC Test][TaskID:%p][Step:%d][AsyncCallBack]Wait for response! \n",
           osThreadGetId(), g_asyncStep++);
}

static void CASE_ReleaseIUnknown(DemoApi *demoApi)
{
    printf("[Discover Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s, F:%s]: BEGIN\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE);
    int32 ref = demoApi->Release((IUnknown *)demoApi);
    if (ref <= 0) {
        printf("[Discover Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s, F:%s]Error ref is %d!\n",
               osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE, ref);
        goto END;
    }
    printf("[Discover Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s, F:%s]Success\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE);
END:
    printf("[Discover Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s, F:%s]: END\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, EXAMPLE_FEATURE);
}

static void RunTestCase(void)
{
    DemoApi *demoApi = CASE_GetIUnknown();
    CASE_SyncCall(demoApi);
    CASE_AsyncCall(demoApi);
    CASE_AsyncCallBack(demoApi);
    CASE_AsyncTimeCall(demoApi);
    CASE_ReleaseIUnknown(demoApi);
}
TEST_INIT(RunTestCase);
