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
static const char *BROADCASR_TEST_SERVICE = "S_broadcast2";

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
    TaskConfig config = {LEVEL_HIGH, PRI_NORMAL, 0x800, 20, SHARED_TASK};  // share with broadcast
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

class BroadcastPublishTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
        printf("[hcpptest]SetUpTestCase ! \n");
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
 * @tc.number    : DMSLite_SAMGR_Publish_0010
 * @tc.name      : Provider can publish a broadcast message
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(BroadcastPublishTest, testPublish0010, TestSize.Level1)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "==>111<==", TEST_LEN);
    ASSERT_EQ(result, 1);

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
HWTEST_F(BroadcastPublishTest, testPublish0020, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    Topic noExisttopic = 99;
    BOOL result = provider->Publish((IUnknown *)fapi, &noExisttopic, (uint8_t *) "==>111<==", TEST_LEN);
    ASSERT_EQ(result, 0);

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
HWTEST_F(BroadcastPublishTest, testPublish0030, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "==>111<==", TEST_LEN - 1);
    ASSERT_EQ(result, TRUE);

    result = provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "==>111<==", TEST_LEN + 1);
    ASSERT_EQ(result, TRUE);

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
HWTEST_F(BroadcastPublishTest, testPublish0040, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "", 0);
    ASSERT_EQ(result, 0);

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
HWTEST_F(BroadcastPublishTest, testPublish0050, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Provider *provider = &fapi->provider;

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "==>111<==", TEST_LEN);
    ASSERT_EQ(result, 1);

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
HWTEST_F(BroadcastPublishTest, testPublish0060, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 0;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "==>111<==", TEST_LEN);
    ASSERT_EQ(result, TRUE);

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
HWTEST_F(BroadcastPublishTest, testPublish0070, TestSize.Level2)
{
    PubSubInterface *fapi = CASE_GetIUnknown();
    if (fapi == nullptr) {
        ADD_FAILURE();
    }
    Subscriber *subscriber = &fapi->subscriber;
    if (subscriber == nullptr) {
        ADD_FAILURE();
    }
    
    Provider *provider = &fapi->provider;
    static Consumer c1 = {.identity = &g_identity, .Notify = C1Callback, .Equal = Equal};
    static Consumer c2 = {.identity = &g_identity, .Notify = C2Callback, .Equal = Equal};

    Topic topic0 = 70;
    subscriber->AddTopic((IUnknown *)fapi, &topic0);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c1);
    subscriber->Subscribe((IUnknown *)fapi, &topic0, &c2);

    for (int i = 0; i < PRESSURE_BASE; i++) {
        // after this pressure, some operation will fail.
        provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "==>111<==", TEST_LEN);
    }
    
    usleep(OPER_INTERVAL * MS2US);
    BOOL result = provider->Publish((IUnknown *)fapi, &topic0, (uint8_t *) "==>111<==", TEST_LEN);
    ASSERT_EQ(result, TRUE);

    CASE_ReleaseIUnknown(fapi);
}