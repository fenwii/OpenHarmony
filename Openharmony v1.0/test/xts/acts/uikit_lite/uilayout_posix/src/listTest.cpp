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

#include "gtest/gtest.h"
#include <climits>
#include "utils/list.h"

using namespace OHOS;
using namespace testing::ext;

class ListTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void) {}
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void) {}
    // Testcase setup
    virtual void SetUp() {}
    // Testcase teardown
    virtual void TearDown() {}
};

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_FRONT_0100
* @tc.name       test list front api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListFront, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    EXPECT_EQ(list->Front(), 1);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_BACK_0100
* @tc.name       test list back api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListBack, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    EXPECT_EQ(list->Back(), 2);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_PUSHBACK_0100
* @tc.name       test list push back api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListPushBack, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    EXPECT_EQ(list->Size(), 2);
    EXPECT_EQ(list->Front(), 1);
    EXPECT_EQ(list->Back(), 2);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_PUSHFRONT_0100
* @tc.name       test list push front api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListPushFront, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushFront(1);
    list->PushFront(2);
    EXPECT_EQ(list->Size(), 2);
    EXPECT_EQ(list->Front(), 2);
    EXPECT_EQ(list->Back(), 1);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_POPBACK_0100
* @tc.name       test list pop back api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListPopBack, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    list->PopBack();
    EXPECT_EQ(list->Size(), 1);
    EXPECT_EQ(list->Front(), 1);
    EXPECT_EQ(list->Back(), 1);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_POPFRONT_0100
* @tc.name       test list pop front api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListPopFront, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    list->PopFront();
    EXPECT_EQ(list->Size(), 1);
    EXPECT_EQ(list->Front(), 2);
    EXPECT_EQ(list->Back(), 2);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_INSERT_0100
* @tc.name       test list insert api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListInsert, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    ListNode<uint16_t>* node = list->Tail();
    list->Insert(node, 3);
    EXPECT_EQ(list->Size(), 3);
    EXPECT_EQ(list->Front(), 1);
    EXPECT_EQ(list->Head()->next_->data_, 3);
    EXPECT_EQ(list->Back(), 2);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_REMOVE_0100
* @tc.name       test list remove api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListRemove, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    ListNode<uint16_t>* node = list->Head();
    list->Remove(node);
    EXPECT_EQ(list->Size(), 1);
    EXPECT_EQ(list->Front(), 2);
    EXPECT_EQ(list->Back(), 2);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_CLEAR_0100
* @tc.name       test list clear api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListClear, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    list->Clear();
    EXPECT_EQ(list->Size(), 0);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_HEAD_0100
* @tc.name       test list head api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListHead, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    EXPECT_EQ(list->Head()->data_, 1);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_TAIL_0100
* @tc.name       test list tail api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListTail, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    EXPECT_EQ(list->Tail()->data_, 2);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_BEGIN_0100
* @tc.name       test list begin api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListBegin, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    EXPECT_EQ(list->Begin()->data_, 1);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_NEXT_0100
* @tc.name       test list next api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListNext, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    EXPECT_EQ(list->Next(list->Head())->data_, 2);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_ISEMPTY_0100
* @tc.name       test list is empty api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListIsEmpty, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    EXPECT_EQ(list->IsEmpty(), false);
    list->Clear();
    EXPECT_EQ(list->IsEmpty(), true);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_SIZE_0100
* @tc.name       test list size api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListSize, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    EXPECT_EQ(list->Size(), 1);
    list->Clear();
    EXPECT_EQ(list->Size(), 0);
    delete(list);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LIST_LIST_END_0100
* @tc.name       test list end api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ListTest, testListEnd, TestSize.Level0) {
    List<uint16_t>* list = new List<uint16_t>();
    list->PushBack(1);
    list->PushBack(2);
    EXPECT_EQ(list->End()->next_->data_, 1);
    delete(list);
}