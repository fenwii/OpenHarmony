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
#include "samgr_lite.h"
#include "broadcast_interface.h"
#include <ohos_init.h>
#include <securec.h>
#include <los_base.h>
#include <cmsis_os.h>

#define TEST_LEN 10
#define WAIT_PUB_PROC 1000
#define BROADCASR_TEST_SERVICE "broadcast test"

static uint32 g_callbackStep = 0;
static void C1Callback(Consumer *consumer, const Topic *topic, const Request *request)
{
    (void)consumer;
    (void)topic;
    printf("[Broadcast Test][TaskID:%p][Step:%d][C1 Callback]c1 is being called data is :%s \n",
           osThreadGetId(), g_callbackStep++, (char *)request->data);
}

static void C2Callback(Consumer *consumer, const Topic *topic, const Request *request)
{
    (void)consumer;
    (void)topic;
    printf("[Broadcast Test][TaskID:%p][Step:%d][C2 Callback]c2 is being called data is :%s \n",
           osThreadGetId(), g_callbackStep++, (char *)request->data);
}

static BOOL Equal(const Consumer *current, const Consumer *other)
{
    return  (current->Notify == other->Notify);
}

static const char *GetName(Service *service)
{
    (void)service;
    return BROADCASR_TEST_SERVICE;
};

static Identity g_identity = { -1, -1, NULL};
static volatile uint32 g_broadcastStep = 0;
static BOOL Initialize(Service *service, Identity identity)
{
    g_identity = identity;
    (void)service;
    printf("[Broadcast Test][TaskID:%p][Step:%d][Reg Finish S:%s]Time: %llu!\n",
           osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE, SAMGR_GetProcessTime());
    return TRUE;
};

static BOOL MessageHandle(Service *service, Request *msg)
{
    printf("[Broadcast Test][TaskID: %p] msgId<%d>: %s \n", osThreadGetId(), msg->msgId, (char *)msg->data);
    (void)service;
    return FALSE;
};

static TaskConfig GetTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_ABOVE_NORMAL, 0x800, 20, SHARED_TASK};
    (void)service;
    return config;
};

static Service g_testService = {GetName, Initialize, MessageHandle, GetTaskConfig};
static void Init(void)
{
    SAMGR_GetInstance()->RegisterService(&g_testService);
    printf("[Broadcast Test][TaskID:%p][Step:%d][Reg S:%s]Time: %llu!\n",
           osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE, SAMGR_GetProcessTime());
}
SYSEX_SERVICE_INIT(Init);

static PubSubInterface *CASE_GetIUnknown(void)
{
    PubSubInterface *fapi = NULL;
    printf("[Broadcast Test][TaskID:%p][Step:%d][GetIUnknown S:%s]: BEGIN\n",
           osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE);
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(BROADCAST_SERVICE, PUB_SUB_FEATURE);
    if (iUnknown == NULL) {
        printf("[Broadcast Test][TaskID:%p][Step:%d][GetDefaultFeatureApi S:%s]Error is NULL!\n",
               osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE);
        goto END;
    }

    int result = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)&fapi);
    if (result != 0 || fapi == NULL) {
        printf("[Broadcast Test][TaskID:%p][Step:%d][QueryInterface S:%s]Error is NULL!\n",
               osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE);
        goto END;
    }
    printf("[Broadcast Test][TaskID:%p][Step:%d][GetIUnknown S:%s]Success\n",
           osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE);
END:
    printf("[Broadcast Test][TaskID:%p][Step:%d][GetIUnknown S:%s]: END\n",
           osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE);
    return fapi;
}

static uint32 g_addTopicStep = 0;
static uint32 g_unsubscribeTopicStep = 0;
static void CASE_AddAndUnsubscribeTopic(PubSubInterface *fapi)
{
    Subscriber *subscriber = &fapi->subscriber;
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};
    // add topic test
    printf("[Topic Test][TaskID:%p][Step:%d][Add Topic]: BEGIN\n", osThreadGetId(), g_addTopicStep++);
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);
    provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "==>111<==", TEST_LEN);
    Topic topic1 = 0x10000;
    subscriber->AddTopic((IUnknown *)fapi, &topic1);
    subscriber->Subscribe((IUnknown *)fapi, &topic1, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic1, &c2);
    provider->Publish((IUnknown *)fapi, &topic1, (uint8_t *) "==>444<==", TEST_LEN);
    printf("[Topic Test][TaskID:%p][Step:%d][Add  Topic]: Success!\n", osThreadGetId(), g_addTopicStep++);
    printf("[Topic Test][TaskID:%p][Step:%d][Add  Topic]: END\n", osThreadGetId(), g_addTopicStep++);
    // unsubscribe topic0 test
    printf("[Topic Test][TaskID:%p][Step:%d][Unsubscribe Topic]: BEGIN\n", osThreadGetId(), g_unsubscribeTopicStep++);
    LOS_Msleep(WAIT_PUB_PROC);
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "@@@222@@@", TEST_LEN);
    LOS_Msleep(WAIT_PUB_PROC);
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c2);
    provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "@@@333@@@", TEST_LEN);
    provider->Publish((IUnknown *)fapi, &topic1, (uint8_t *) "@@@444@@@", TEST_LEN);
    printf("[Topic Test][TaskID:%p][Step:%d][Unsubscribe Topic]: Success!\n",
           osThreadGetId(), g_unsubscribeTopicStep++);
    printf("[Topic Test][TaskID:%p][Step:%d][Unsubscribe Topic]: END\n", osThreadGetId(), g_unsubscribeTopicStep++);
}

static uint32 g_modifyConsumerStep = 0;
static void CASE_ModifyConsumer(PubSubInterface *fapi)
{
    Subscriber *subscriber = &fapi->subscriber;
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};
    // modify consumer test
    printf("[Topic Test][TaskID:%p][Step:%d][Modify Consumer]: BEGIN\n", osThreadGetId(), g_modifyConsumerStep++);
    Topic topic2 = 0x100;
    subscriber->AddTopic((IUnknown *)fapi, &topic2);
    subscriber->Subscribe((IUnknown *)fapi, &topic2, &c1);
    provider->Publish((IUnknown *)fapi, &topic2, (uint8_t *) "==>555<==", TEST_LEN);
    LOS_Msleep(WAIT_PUB_PROC);
    subscriber->ModifyConsumer((IUnknown *)fapi, &topic2, &c1, &c2);
    provider->Publish((IUnknown *)fapi, &topic2, (uint8_t *) "@@@555@@@", TEST_LEN);
    printf("[Topic Test][TaskID:%p][Step:%d][Modify Consumer]: Success!\n", osThreadGetId(), g_modifyConsumerStep++);
    printf("[Topic Test][TaskID:%p][Step:%d][Modify Consumer]: END\n", osThreadGetId(), g_modifyConsumerStep++);
}

static uint32 g_reUnsubscribeTopic = 0;
static void CASE_ReUnsubscribeTopic(PubSubInterface *fapi)
{
    Subscriber *subscriber = &fapi->subscriber;
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    printf("[Topic Test][TaskID:%p][Step:%d][ReUnsubscribe Topic]: BEGIN\n", osThreadGetId(), g_reUnsubscribeTopic++);
    Topic topic3 = 0x1000;
    subscriber->AddTopic((IUnknown *)fapi, &topic3);
    subscriber->Subscribe((IUnknown *)fapi, &topic3, &c1);
    provider->Publish((IUnknown *)fapi, &topic3, (uint8_t *) "==>666<==", TEST_LEN);
    LOS_Msleep(WAIT_PUB_PROC);
    Consumer *retConsumer = subscriber->Unsubscribe((IUnknown *)fapi, &topic3, &c1);
    if (retConsumer == NULL) {
        printf("[Topic Test][TaskID:%p][Step:%d][ReUnsubscribe Topic]: Unsubscribe Topic lead to NULL return value\n",
               osThreadGetId(), g_reUnsubscribeTopic++);
    }
    retConsumer = subscriber->Unsubscribe((IUnknown *)fapi, &topic3, &c1);
    if (retConsumer == NULL) {
        printf("[Topic Test][TaskID:%p][Step:%d][ReUnsubscribe Topic]: ReUnsubscribe Topic lead to NULL return value\n",
               osThreadGetId(), g_reUnsubscribeTopic++);
    }
    provider->Publish((IUnknown *)fapi, &topic3, (uint8_t *) "@@@666@@@", TEST_LEN);
    printf("[Topic Test][TaskID:%p][Step:%d][ReUnsubscribe Topic]: Success!\n",
           osThreadGetId(), g_reUnsubscribeTopic++);
    printf("[Topic Test][TaskID:%p][Step:%d][ReUnsubscribe Topic]: END\n", osThreadGetId(), g_reUnsubscribeTopic++);
}

static void CASE_ReleaseIUnknown(PubSubInterface *fapi)
{
    printf("[Broadcast Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s]: BEGIN\n",
           osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE);
    int32 ref = fapi->Release((IUnknown *)fapi);
    if (ref <= 0) {
        printf("[Broadcast Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s]Error ref is %d!\n",
               osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE, ref);
        goto END;
    }
    printf("[Broadcast Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s]Success\n",
           osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE);
END:
    printf("[Broadcast Test][TaskID:%p][Step:%d][ReleaseIUnknown S:%s]: END\n",
           osThreadGetId(), g_broadcastStep++, BROADCASR_TEST_SERVICE);
}

static void RunTestCase(void)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    CASE_AddAndUnsubscribeTopic(fapi);
    CASE_ModifyConsumer(fapi);
    CASE_ReUnsubscribeTopic(fapi);
    CASE_ReleaseIUnknown(fapi);
}
TEST_INIT(RunTestCase);
