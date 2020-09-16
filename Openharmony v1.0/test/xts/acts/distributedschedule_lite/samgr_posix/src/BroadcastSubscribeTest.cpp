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

#include <securec.h>
#include <hos_init.h>
#include "gtest/gtest.h"
#include "broadcast_interface.h"
#include "utils/SamgrTestBase.h"

using namespace testing::ext;

static const int16 TEST_LEN = 10;
static const char *BROADCASR_TEST_SERVICE = "S_broadcast1";

static void C1Callback(Consumer *consumer, const Topic *topic, const Request *request)
{
    (void)consumer;
    (void)topic;
}
static void C2Callback(Consumer *consumer, const Topic *topic, const Request *request)
{
    (void)consumer;
    (void)topic;
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

static Identity g_identity = { -1, -1, nullptr};
static BOOL Initialize(Service *service, Identity identity)
{
    g_identity = identity;
    (void)service;
    return TRUE;
};

static BOOL MessageHandle(Service *service, Request *msg)
{
    (void)service;
    return FALSE;
};

static TaskConfig GetTaskConfig(Service *service)
{
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 0x800, 20, SHARED_TASK}; // share with broadcast
    (void)service;
    return config;
};

static Service g_service = {GetName, Initialize, MessageHandle, GetTaskConfig};
static void GInit(void)
{
    SAMGR_GetInstance()->RegisterService(&g_service);
}
SYSEX_SERVICE_INIT(GInit);

static PubSubInterface *CASE_GetIUnknown(void)
{
    PubSubInterface *fapi = nullptr;
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(BROADCAST_SERVICE, PUB_SUB_FEATURE);
    if (iUnknown == nullptr) {
        printf("[hctest]CASE_GetIUnknown error ");
        return nullptr;
    }

    int result = iUnknown->QueryInterface(iUnknown, 0x20, (void **)&fapi);
    if (result != 0 || fapi == nullptr) {
        printf("[hctest]CASE_GetIUnknown error ");
    }
    return fapi;
}

static void CASE_ReleaseIUnknown(PubSubInterface *fapi)
{
    fapi->Release((IUnknown *)fapi);
}

class BroadcastSubscribeTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
        SystemInitProxy();
    }
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void)
    {
    }
    // Testcase setup
    virtual void SetUp()
    {
    }
    // Testcase teardown
    virtual void TearDown()
    {
    }
};

/**
 * @tc.number    : DMSLite_SAMGR_AddTopic_0010
 * @tc.name      : Valid topic can be added successfully
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testAddTopic0010, TestSize.Level1)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Topic topic0 = 11;
    int result = subscriber->AddTopic((IUnknown *)fapi, &topic0);
    ASSERT_EQ(result == 0, TRUE);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_AddTopic_0020
 * @tc.name      : Topic which is nullptr or already existing can not be added
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testAddTopic0020, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);

    int result = subscriber->AddTopic((IUnknown *)fapi, nullptr);
    ASSERT_EQ(result != 0, TRUE);

    result = subscriber->AddTopic((IUnknown *)fapi, &topic0);
    ASSERT_EQ(result != 0, TRUE);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Subscribe_0010
 * @tc.name      : Consumer can subscribe to a topic
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testSubscribe0010, TestSize.Level1)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 9;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    int result = subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    ASSERT_EQ(result == 0, TRUE);
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Subscribe_0020
 * @tc.name      : Consumer can not subscribe to the topic which is nullptr or does not exist
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testSubscribe0020, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    int result = subscriber->Subscribe((IUnknown *)fapi, nullptr, &c1);
    ASSERT_EQ(result != 0, TRUE);

    Topic noExistTopic = -200;
    result = subscriber->Subscribe((IUnknown *)fapi, &noExistTopic, &c1);
    ASSERT_EQ(result != 0, TRUE);

    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_Subscribe_0030
 * @tc.name      : Consumer which is nullptr can not subscribe to a topic
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testSubscribe0030, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    int result = subscriber->Subscribe((IUnknown *)fapi, &topic0, nullptr);
    ASSERT_EQ(result != 0, TRUE);

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
HWTEST_F(BroadcastSubscribeTest, testSubscribe0040, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    int result = subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    ASSERT_EQ(result != 0, TRUE);
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnSubscribe_0010
 * @tc.name      : Consumer can unsubscribe a topic
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testUnsubscribe0010, TestSize.Level1)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    ASSERT_EQ(result != nullptr, TRUE);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnSubscribe_0020
 * @tc.name      : Consumer can not unsubscribe a topic if the specified topic-comsumer relationship is nullptr 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testUnsubscribe0020, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->Unsubscribe((IUnknown *)fapi, nullptr, &c1);
    ASSERT_EQ(result==NULL, TRUE);  // failed

    result = subscriber->Unsubscribe((IUnknown *)fapi, &topic0, nullptr);
    ASSERT_EQ(result==NULL, TRUE);
    
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
HWTEST_F(BroadcastSubscribeTest, testUnsubscribe0030, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c2);
    ASSERT_EQ(result==NULL, TRUE);  

    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_UnSubscribe_0040
 * @tc.name      : Consumer subscribe and unsubscribe a topic repeatedly, no memory leak.
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testUnsubscribe0040, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);

    for (int i = 0; i < PRESSURE_BASE; i++) {
        int result = subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
        ASSERT_EQ(result == 0, TRUE);

        Consumer *resultConsumer = subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
        ASSERT_EQ(resultConsumer != nullptr, TRUE); 
    }
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
HWTEST_F(BroadcastSubscribeTest, testModifyConsumer0010, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, &topic0, &c1, &c2);
    ASSERT_EQ(result != nullptr, TRUE);  
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}

/**
 * @tc.number    : DMSLite_SAMGR_ModifyConsumer_0020
 * @tc.name      : Consumer can not modify subscription relationship if the input parameter is nullptr
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastSubscribeTest, testModifyConsumer0020, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, nullptr, &c1, &c2);
    ASSERT_EQ(result!=NULL, 0);

    result = subscriber->ModifyConsumer((IUnknown *)fapi, &topic0, nullptr, &c2);
    ASSERT_EQ(result!=NULL, 0);

    result = subscriber->ModifyConsumer((IUnknown *)fapi, &topic0, &c1, nullptr);
    ASSERT_EQ(result!=NULL, 0);
    
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
HWTEST_F(BroadcastSubscribeTest, testModifyConsumer0030, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Topic noExistTopic = 99;
    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, &noExistTopic, &c1, &c2);
    ASSERT_EQ(result==NULL, 1);
    
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
HWTEST_F(BroadcastSubscribeTest, testModifyConsumer0040, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    
    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Topic noExistTopic = 99;
    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, &noExistTopic, &c2, &c2);
    ASSERT_EQ(result==NULL, 1);
    
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
HWTEST_F(BroadcastSubscribeTest, testModifyConsumer0050, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);

    Consumer *result = subscriber->ModifyConsumer((IUnknown *)fapi, &topic0, &c1, &c1);
    ASSERT_EQ(result != nullptr, TRUE);  
    
    subscriber->Unsubscribe((IUnknown *)fapi, &topic0, &c1);
    
    CASE_ReleaseIUnknown(fapi);
}
