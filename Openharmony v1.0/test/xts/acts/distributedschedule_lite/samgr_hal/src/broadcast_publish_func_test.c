/**
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Description : testcases for distributedschedule_lite subsystem
 * Create      : 2020/04/19
 */

#include <los_base.h>
#include "hctest.h"
#include "samgr_lite.h"
#include "broadcast_interface.h"

#define PRESSURE_BASE (1024 * 10)
#define TEST_LEN 10
#define OPER_INTERVAL 200
#define BROADCASR_TEST_SERVICE "S_broadcast2"

static void C1Callback(Consumer *consumer, const Topic *topic, const Request *request)
{
    (void)consumer;
    (void)topic;
    (void)request;
}
static void C2Callback(Consumer *consumer, const Topic *topic, const Request *request)
{
    (void)consumer;
    (void)topic;
    (void)request;
}

static BOOL Equal(const Consumer *current, const Consumer *other)
{
    if (current->Notify == other->Notify) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static const char *GetName(Service *service)
{
    (void)service;
    return BROADCASR_TEST_SERVICE;
};

static Identity g_identity = { -1, -1, NULL};

static BOOL Initialize(Service *service, Identity identity)
{
    g_identity = identity;
    (void)service;
    return TRUE;
};

static BOOL MessageHandle(Service *service, Request *msg)
{
    (void)service;
    (void)msg;
    return FALSE;
};

static TaskConfig GetTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 0x800, 20, SHARED_TASK};  // share with broadcast
    (void)service;
    return config;
};

static Service g_service = {GetName, Initialize, MessageHandle, GetTaskConfig};
static void Init(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterService(&g_service);
    if (result == FALSE) {
        printf("[hctest]E RegisterService failed.\n");
    }
}
SYSEX_SERVICE_INIT(Init);

static PubSubInterface *CASE_GetIUnknown(void)
{
    PubSubInterface *fapi = NULL;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(BROADCAST_SERVICE, PUB_SUB_FEATURE);
    if (iUnknown == NULL) {
        printf("[hctest]CASE_GetIUnknown error ");
        return NULL;
    }

    int result = iUnknown->QueryInterface(iUnknown, 0, (void **)&fapi);
    if (result != 0 || fapi == NULL) {
        printf("[hctest]CASE_GetIUnknown error ");
    }
    return fapi;
}

static void CASE_ReleaseIUnknown(PubSubInterface *fapi)
{
    fapi->Release((IUnknown *)fapi);
}

LITE_TEST_SUIT(test, broadcast, Broadcast02TestSuite);

static BOOL Broadcast02TestSuiteSetUp(void)
{   
    LOS_Msleep(OPER_INTERVAL);
    return TRUE;
}

static BOOL Broadcast02TestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : DMSLite_SAMGR_Publish_0010
 * @tc.name      : Provider can publish a broadcast message
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(Broadcast02TestSuite, testPublish0010, LEVEL1)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }

    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8 *) "==>111<==", TEST_LEN);
    TEST_ASSERT_EQUAL_INT(1, result);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Publish_0020
 * @tc.name      : Provider failed to publish broadcast for the specified topic not exist  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast02TestSuite, testPublish0020, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    Topic noExisttopic = 99;
    BOOL result = provider->Publish((IUnknown *)fapi, &noExisttopic, (uint8 *) "==>111<==", TEST_LEN);
    TEST_ASSERT_EQUAL_INT(result, 0);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Publish_0030
 * @tc.name      : Provider failed to publish broadcast for len and data not match  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast02TestSuite, testPublish0030, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8 *) "==>111<==", TEST_LEN - 1);
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    result = provider->Publish((IUnknown *)fapi, &topic0, (uint8 *) "==>111<==", TEST_LEN + 1);
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Publish_0040
 * @tc.name      : Provider publish broadcast successfully for 0 and max lenth message  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast02TestSuite, testPublish0040, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8 *) "", 0);
    TEST_ASSERT_EQUAL_INT(result, 0);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Publish_0050
 * @tc.name      : Provider publish broadcast successfully for no consumer  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast02TestSuite, testPublish0050, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    
    Provider *provider = &fapi->provider;
    if (provider == NULL) {
        printf("[hctest]E provider is NULL. \n");
    }

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8 *) "==>111<==", TEST_LEN);
    TEST_ASSERT_EQUAL_INT(result, 1);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Publish_0060
 * @tc.name      : Provider publish broadcast successfully for multi consumers  
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast02TestSuite, testPublish0060, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8 *) "==>111<==", TEST_LEN);
    TEST_ASSERT_EQUAL_INT(result, TRUE);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Publish_0070
 * @tc.name      : Provider send broadcast repeatedly, no memory leak
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast02TestSuite, testPublish0070, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    for (int i = 0; i < PRESSURE_BASE; i++) {
        BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8 *) "==>111<==", TEST_LEN);
        TEST_ASSERT_EQUAL_INT(result, TRUE);
    }

    CASE_ReleaseIUnknown(fapi);
}

RUN_TEST_SUITE(Broadcast02TestSuite);