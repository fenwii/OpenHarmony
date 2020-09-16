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

#define TEST_LEN 10
#define OPER_INTERVAL 200
#define BROADCASR_TEST_SERVICE "S_broadcast1"

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
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 0x800, 20, SHARED_TASK}; // share with broadcast
    (void)service;
    return config;
};

static Service g_service = {GetName, Initialize, MessageHandle, GetTaskConfig};
static void Init(void)
{
    BOOL result = SAMGR_GetInstance()->RegisterService(&g_service);
    if (result == FALSE) {
        printf("[hctest]E RegisterService failed. \n");
    }
}
SYSEX_SERVICE_INIT(Init);

static PubSubInterface *CASE_GetIUnknown(void)
{
    PubSubInterface *fapi = NULL;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(BROADCAST_SERVICE, PUB_SUB_FEATURE);
    if (iUnknown == NULL) {
        printf("[hctest]failed to GetIUnknown ");
        return NULL;
    }

    int result = iUnknown->QueryInterface(iUnknown, 0, (void **)&fapi);
    if (result != 0 || fapi == NULL) {
        printf("[hctest]failed to QueryInterface ");
    }
    return fapi;
}

static void CASE_ReleaseIUnknown(PubSubInterface *fapi)
{
    fapi->Release((IUnknown *)fapi);
}

LITE_TEST_SUIT(test, broadcast, Broadcast01TestSuite);

static BOOL Broadcast01TestSuiteSetUp(void)
{   
    LOS_Msleep(OPER_INTERVAL);

    return TRUE;
}

static BOOL Broadcast01TestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : DMSLite_SAMGR_AddTopic_0010
 * @tc.name      : Valid topic can be added successfully
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(Broadcast01TestSuite, testAddTopic0010, LEVEL1)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }

    Topic topic0 = 11;
    int result = subscriber->AddTopic((IUnknown *)fapi, &topic0);
    TEST_ASSERT_EQUAL_INT(result == 0, TRUE);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_AddTopic_0020
 * @tc.name      : Topic which is NULL or already existing can not be added
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testAddTopic0020, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);

    int result = subscriber->AddTopic((IUnknown *)fapi, NULL);
    TEST_ASSERT_EQUAL_INT(result != 0, TRUE);

    result = subscriber->AddTopic((IUnknown *)fapi, &topic0);
    TEST_ASSERT_EQUAL_INT(result != 0, TRUE);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Subscribe_0010
 * @tc.name      : Consumer can subscribe to a topic
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(Broadcast01TestSuite, testSubscribe0010, LEVEL1)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 9;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    int result = subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    TEST_ASSERT_EQUAL_INT(result == 0, TRUE);
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Subscribe_0020
 * @tc.name      : Consumer can not subscribe to the topic which is NULL or does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testSubscribe0020, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    int result = subscriber->Subscribe((IUnknown *)fapi, NULL, &c1);
    TEST_ASSERT_EQUAL_INT(result != 0, TRUE);

    Topic noExistTopic = -200;
    result = subscriber->Subscribe((IUnknown *)fapi, &noExistTopic, &c1);
    TEST_ASSERT_EQUAL_INT(result != 0, TRUE);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Subscribe_0030
 * @tc.name      : Consumer which is NULL can not subscribe to a topic
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testSubscribe0030, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    int result = subscriber->Subscribe((IUnknown *)fapi, &topic0, NULL);
    TEST_ASSERT_EQUAL_INT(result != 0, TRUE);

    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Subscribe_0040
 * @tc.name      : Consumer can not subscribe to the same topic twice
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testSubscribe0040, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    int result = subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    TEST_ASSERT_EQUAL_INT(result != 0, TRUE);
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnSubscribe_0010
 * @tc.name      : Consumer can unsubscribe a topic
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(Broadcast01TestSuite, testUnsubscribe0010, LEVEL1)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }

    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    TEST_ASSERT_EQUAL_INT(result != NULL, TRUE);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnSubscribe_0020
 * @tc.name      : Consumer can not unsubscribe a topic if the specified topic-comsumer relationship is NULL 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testUnsubscribe0020, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->Unsubscribe((IUnknown *)fapi, NULL, &c1);
    TEST_ASSERT_EQUAL_INT(result==NULL, TRUE);  // failed

    result = subscriber->Unsubscribe((IUnknown *)fapi, &topic0, NULL);
    TEST_ASSERT_EQUAL_INT(result==NULL, TRUE);
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnSubscribe_0030
 * @tc.name      : Consumer can not unsubscribe a topic if the specified topic-comsumer relationship not exist 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testUnsubscribe0030, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c2);
    TEST_ASSERT_EQUAL_INT(result==NULL, TRUE);  

    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_ModifyConsumer_0010
 * @tc.name      : Consumer can modify subscription relationship
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testModifyConsumer0010, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, &topic0, &c1, &c2);
    TEST_ASSERT_EQUAL_INT(result != NULL, TRUE);  
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_ModifyConsumer_0020
 * @tc.name      : Consumer can not modify subscription relationship if the input parameter is NULL
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testModifyConsumer0020, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, NULL, &c1, &c2);
    TEST_ASSERT_EQUAL_INT(result!=NULL, 0);

    result = subscriber->ModifyConsumer((IUnknown *)fapi, &topic0, NULL, &c2);
    TEST_ASSERT_EQUAL_INT(result!=NULL, 0);

    result = subscriber->ModifyConsumer((IUnknown *)fapi, &topic0, &c1, NULL);
    TEST_ASSERT_EQUAL_INT(result!=NULL, 0);
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_ModifyConsumer_0030
 * @tc.name      : Consumer can not modify subscription relationship if the specified topic not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testModifyConsumer0030, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Topic noExistTopic = 99;
    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, &noExistTopic, &c1, &c2);
    TEST_ASSERT_EQUAL_INT(result==NULL, 1);
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_ModifyConsumer_0040
 * @tc.name      : Consumer can not modify subscription relationship if the specified old consumer not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testModifyConsumer0040, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Topic noExistTopic = 99;
    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, &noExistTopic, &c2, &c2);
    TEST_ASSERT_EQUAL_INT(result==NULL, 1);
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_ModifyConsumer_0050
 * @tc.name      : Consumer can modify subscription relationship if the new consumer is the same as old consumer 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(Broadcast01TestSuite, testModifyConsumer0050, LEVEL2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == NULL) {
        TEST_FAIL();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == NULL) {
        TEST_FAIL();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, &topic0, &c1, &c1);
    TEST_ASSERT_EQUAL_INT(result != NULL, TRUE);  
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

RUN_TEST_SUITE(Broadcast01TestSuite);