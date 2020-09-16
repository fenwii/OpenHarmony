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

#include <stdlib.h>
#include <search.h>

#include "gtest/gtest.h"
#include "log.h"
#include "utils.h"
#include "XtsActsUtil.h"

using namespace testing::ext;

class ActsUtilDataStructApiTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
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
* @tc.number     SUB_KERNEL_UTIL_DATASTRUCT_BSEARCH_0100
* @tc.name       test bsearch api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilDataStructApiTest, testBsearch0100, TestSize.Level1) {
    int numArray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *itemPtr = nullptr;
    int keyVal;

    keyVal = 5;
    itemPtr = (int *)bsearch(&keyVal, numArray, sizeof(numArray) / sizeof(numArray[0]),
        sizeof(int), (int (*)(const void *, const void *))NumCompare);
    ASSERT_TRUE(&numArray[5] == itemPtr) << "ErrInfo: bsearch  returnVal:='" << *itemPtr << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_DATASTRUCT_BSEARCH_0200
* @tc.name       test bsearch api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilDataStructApiTest, testBsearch0200, TestSize.Level1) {
    int numArray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *itemPtr = nullptr;
    int keyVal;

    keyVal = 10;
    itemPtr = (int *)bsearch(&keyVal, numArray, sizeof(numArray) / sizeof(numArray[0]),
        sizeof(int), (int (*)(const void *, const void *))NumCompare);
    ASSERT_TRUE(nullptr == itemPtr) << "ErrInfo: bsearch  returnVal:='" << *itemPtr << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_DATASTRUCT_HCREATE_0300
* @tc.name       test hcreate api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilDataStructApiTest, testHcreate0300, TestSize.Level1) {
    int createResult;
    size_t netVal = 10;
    ENTRY item;
    ENTRY *searchResult = nullptr;
    char hashKey[10] = "key1";
    char hashValue[10] = "value1";

    createResult = hcreate(netVal);
    LOGD("    hcreate createResult:='%d'\n", createResult);
    ASSERT_TRUE(createResult != 0) << "ErrInfo: hcreate returnVal:='" << createResult << "'";

    item.key = hashKey;
    item.data = hashValue;

    searchResult = hsearch(item, ENTER);
    ASSERT_TRUE(searchResult != nullptr) << "ErrInfo: hsearch searchResult:='" << searchResult << "'";

    item.key = hashKey;
    searchResult = hsearch(item, FIND);
    LOGD("    hsearch searchResult->data:='%s'\n", searchResult->data);
    ASSERT_TRUE(searchResult != nullptr && strcmp((const char *)searchResult->data, "value1") == 0)
         << "ErrInfo: hsearch searchResult->data:='" << searchResult->data << "'";

    hdestroy();
}

/**
* @tc.number     SUB_KERNEL_UTIL_DATASTRUCT_HCREATE_0400
* @tc.name       test hcreate api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilDataStructApiTest, testHcreate0400, TestSize.Level1) {
    int createResult;
    size_t netVal = 10;
    ENTRY item;
    ENTRY *searchResult = nullptr;
    char hashKey[10] = "key1";

    createResult = hcreate(netVal);
    LOGD("    hcreate createResult:='%d'\n", createResult);
    ASSERT_TRUE(createResult != 0) << "ErrInfo: hcreate returnVal:='" << createResult << "'";

    item.key = hashKey;
    searchResult = hsearch(item, FIND);
    ASSERT_TRUE(searchResult == nullptr)
         << "ErrInfo: hsearch searchResult:='" << searchResult << "'";

    hdestroy();
}

/**
* @tc.number     SUB_KERNEL_UTIL_DATASTRUCT_HCREATE_R_0500
* @tc.name       test hcreate_r api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilDataStructApiTest, testHcreateR0500, TestSize.Level1) {
    int createResult;
    int returnVal = 0;
    size_t netVal = 10;
    ENTRY item;
    ENTRY *searchResult = nullptr;
    char hashKey[10] = "key1";
    char hashValue[10] = "value1";
    struct hsearch_data hTab;

    createResult = hcreate_r(netVal, &hTab);
    LOGD("    hcreate_r createResult:='%d'\n", createResult);
    ASSERT_TRUE(createResult != 0) << "ErrInfo: hcreate_r returnVal:='" << createResult << "'";

    item.key = hashKey;
    item.data = hashValue;

    returnVal = hsearch_r(item, ENTER, &searchResult, &hTab);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: hsearch_r searchResult:='" << searchResult << "'";

    item.key = hashKey;
    returnVal = hsearch_r(item, FIND, &searchResult, &hTab);
    LOGD("    hsearch_r searchResult->data:='%s'\n", searchResult->data);
    ASSERT_TRUE(returnVal != 0 && strcmp((const char *)searchResult->data, "value1") == 0)
         << "ErrInfo: hsearch_r searchResult->data:='" << searchResult->data << "'";

    hdestroy_r(&hTab);
}

/**
* @tc.number     SUB_KERNEL_UTIL_DATASTRUCT_HCREATE_R_0600
* @tc.name       test hcreate_r api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilDataStructApiTest, testHcreateR0600, TestSize.Level1) {
    int createResult;
    int returnVal = 0;
    size_t netVal = 10;
    ENTRY item;
    ENTRY *searchResult = nullptr;
    char hashKey[10] = "key1";
    struct hsearch_data hTab;

    createResult = hcreate_r(netVal, &hTab);
    LOGD("    hcreate_r createResult:='%d'\n", createResult);
    ASSERT_TRUE(createResult != 0) << "ErrInfo: hcreate_r returnVal:='" << createResult << "'";

    item.key = hashKey;
    returnVal = hsearch_r(item, FIND, &searchResult, &hTab);
    LOGD("    hsearch_r searchResult='%s'\n", searchResult);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: hsearch_r searchResult:='" << searchResult << "'";

    hdestroy_r(&hTab);
}

/**
* @tc.number     SUB_KERNEL_UTIL_DATASTRUCT_INITSTATE_0700
* @tc.name       test initstate api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilDataStructApiTest, testInitstate0700, TestSize.Level1) {
    int seed = 8;
    char *returnVal = nullptr;
    char state[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    size_t num = 8;

    returnVal = initstate(seed, state, num);
    LOGD("    initstate returnVal:='%x'\n", returnVal);
    ASSERT_TRUE(returnVal != nullptr) << "ErrInfo: initstate returnVal:='" << returnVal << "'";
}