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
#include "iunknown.h"
#include "feature.h"
#include "service.h"
#include "samgr_lite.h"

typedef struct DefaultFeatureApi {
    INHERIT_IUNKNOWN;
    void (*SyncCall)(IUnknown *iUnknown);
} DefaultFeatureApi;

typedef struct ExampleService {
    INHERIT_SERVICE;
    INHERIT_IUNKNOWNENTRY(DefaultFeatureApi);
    Identity identity;
} ExampleService;

static const char *GetName(Service *service)
{
    (void)service;
    return EXAMPLE_SERVICE;
}
static int g_regStep = 0;
static BOOL Initialize(Service *service, Identity identity)
{
    ExampleService *example = (ExampleService *)service;
    example->identity = identity;
    printf("[Register Test][TaskID:%p][Step:%d][Reg Finish S:%s]Time: %llu!\n",
           osThreadGetId(), g_regStep++, service->GetName(service), SAMGR_GetProcessTime());
    return TRUE;
}

static BOOL MessageHandle(Service *service, Request *msg)
{
    printf("[LPC Test][TaskID: %p] msgId<%d>: %s \n", osThreadGetId(), msg->msgId, (char *)msg->data);
    (void)service;
    return FALSE;
}

static TaskConfig GetTaskConfig(Service *service)
{
    (void)service;
    TaskConfig config = {LEVEL_HIGH, PRI_BELOW_NORMAL,
                         0x800, 20, SHARED_TASK};
    return config;
}
static volatile uint32 g_asyncStep = 0;
static void SyncCall(IUnknown *iUnknown)
{
    (void)iUnknown;
    printf("[LPC Test][TaskID:%p][Step:%d][SyncCall API] Default Success!\n", osThreadGetId(), g_asyncStep++);
}
static ExampleService g_example = {
    .GetName = GetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    DEFAULT_IUNKNOWN_ENTRY_BEGIN,
    .SyncCall = SyncCall,
    DEFAULT_IUNKNOWN_ENTRY_END,
};

static void Init(void)
{
    SAMGR_GetInstance()->RegisterService((Service *)&g_example);
    SAMGR_GetInstance()->RegisterDefaultFeatureApi(EXAMPLE_SERVICE, GET_IUNKNOWN(g_example));
    printf("[Register Test][TaskID:%p][Step:%d][Reg S:%s]Time: %llu!\n",
           osThreadGetId(), g_regStep++, EXAMPLE_SERVICE, SAMGR_GetProcessTime());
}
SYSEX_SERVICE_INIT(Init);

static int g_discoverStep = 0;
static DefaultFeatureApi *CASE_GetIUnknown(void)
{
    DefaultFeatureApi *demoApi = NULL;
    printf("[Discover Test][TaskID:%p][Step:%d][GetIUnknown S:%s]: BEGIN\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE);
    IUnknown *iUnknown = SAMGR_GetInstance()->GetDefaultFeatureApi(EXAMPLE_SERVICE);
    if (iUnknown == NULL) {
        printf("[Discover Test][TaskID:%p][Step:%d][GetDefaultFeatureApi S:%s]Error is NULL!\n",
               osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE);
        goto END;
    }
    int result = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)&demoApi);
    if (result != 0 || demoApi == NULL) {
        printf("[Discover Test][TaskID:%p][Step:%d][QueryInterface S:%s]Error is NULL!\n",
               osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE);
        goto END;
    }
    printf("[Discover Test][TaskID:%p][Step:%d][GetIUnknown S:%s]Success\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE);
END:
    printf("[Discover Test][TaskID:%p][Step:%d][GetIUnknown S:%s]: END\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE);
    return demoApi;
}


static void CASE_SyncCall(DefaultFeatureApi *defaultApi)
{
    printf("[LPC Test][TaskID:%p][Step:%d][DefaultFeature SyncCall]: BEGIN\n", osThreadGetId(), g_asyncStep++);
    defaultApi->SyncCall((IUnknown *)defaultApi);
    printf("[LPC Test][TaskID:%p][Step:%d][DefaultFeature SyncCall]: END\n", osThreadGetId(), g_asyncStep++);
}

static void CASE_ReleaseIUnknown(DefaultFeatureApi *demoApi)
{
    printf("[Discover Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s]: BEGIN\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE);
    int32 ref = demoApi->Release((IUnknown *)demoApi);
    if (ref <= 0) {
        printf("[Discover Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s]Error ref is %d!\n",
               osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE, ref);
        goto END;
    }
    printf("[Discover Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s]Success\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE);
END:
    printf("[Discover Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s]: END\n",
           osThreadGetId(), g_discoverStep++, EXAMPLE_SERVICE);
}
static void CASE_RegisterInvalidService(void)
{
    Service service = {.GetName = NULL, .GetTaskConfig = NULL, .Initialize = NULL, .MessageHandle = NULL};
    BOOL ret = SAMGR_GetInstance()->RegisterService(&service);
    printf("Register Invalid Service %s\n", ret ? "TRUE" : "FALSE");

    Feature feature = {.GetName = NULL, .OnInitialize = NULL, .OnMessage = NULL, .OnStop = NULL};
    ret = SAMGR_GetInstance()->RegisterFeature(EXAMPLE_SERVICE, &feature);
    printf("Register Invalid Feature %s\n", ret ? "TRUE" : "FALSE");

    IUnknownEntry entry = {
        .ver = DEFAULT_VERSION,
        .ref = 1,
        .iUnknown = {
            .QueryInterface = NULL,
            .Release = NULL,
            .AddRef = NULL
        }
    };
    ret = SAMGR_GetInstance()->RegisterDefaultFeatureApi(EXAMPLE_SERVICE, GET_IUNKNOWN(entry));
    printf("Register Invalid Default Api %s\n", ret ? "TRUE" : "FALSE");

    ret = SAMGR_GetInstance()->RegisterFeatureApi(EXAMPLE_SERVICE, EXAMPLE_FEATURE "2", GET_IUNKNOWN(entry));
    printf("Register Invalid " EXAMPLE_FEATURE "2 Api %s\n", ret ? "TRUE" : "FALSE");
}
static void RunTestCase(void)
{
    DefaultFeatureApi *defaultApi = CASE_GetIUnknown();
    CASE_RegisterInvalidService();
    CASE_SyncCall(defaultApi);
    CASE_ReleaseIUnknown(defaultApi);
}
TEST_INIT(RunTestCase);