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

#include <strings.h>
#include <wctype.h>
#include <wchar.h>

#include "gtest/gtest.h"
#include "log.h"
#include "utils.h"

using namespace testing::ext;

class ActsUtilStringOperApiTest : public testing::Test {
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
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_FFS_0100
* @tc.name       test fss api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFss0100, TestSize.Level1) {
    int paraValue;
    int returnVal;

    paraValue = 1;
    returnVal = ffs(paraValue);
    LOGD("    ffs returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(1 == returnVal) << "ErrInfo: ffs returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_FFS_0200
* @tc.name       test fss api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFss0200, TestSize.Level1) {
    int paraValue;
    int returnVal;

    paraValue = 0;
    returnVal = ffs(paraValue);
    LOGD("    ffs returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: ffs returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_FFS_0300
* @tc.name       test fss api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFss0300, TestSize.Level1) {
    int paraValue;
    int returnVal;

    paraValue = 0x8000;
    returnVal = ffs(paraValue);
    LOGD("    ffs returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(16 == returnVal) << "ErrInfo: ffs returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_FFSL_0400
* @tc.name       test fssl api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFssl0400, TestSize.Level1) {
    long int paraValue;
    int returnVal;

    paraValue = 1;
    returnVal = ffsl(paraValue);
    LOGD("    ffsl returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(1 == returnVal) << "ErrInfo: ffsl returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UUTIL_STRINGOPER_FFSL_0500
* @tc.name       test fssl api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFssl0500, TestSize.Level1) {
    long int paraValue;
    int returnVal;

    paraValue = 0;
    returnVal = ffsl(paraValue);
    LOGD("    ffsl returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: ffsl returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_FFSL_0600
* @tc.name       test fssl api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFssl0600, TestSize.Level1) {
    long int paraValue;
    int returnVal;

    paraValue = 0x8000;
    returnVal = ffsl(paraValue);
    LOGD("    ffsl returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(16 == returnVal) << "ErrInfo: ffsl returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_FFSLL_0700
* @tc.name       test fssll api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFssll0700, TestSize.Level1) {
    long long int paraValue;
    int returnVal;

    paraValue = 1;
    returnVal = ffsll(paraValue);
    LOGD("    ffsll returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(1 == returnVal) << "ErrInfo: ffsll returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_FFSLL_0800
* @tc.name       test fssll api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFssll0800, TestSize.Level1) {
    long long int paraValue;
    int returnVal;

    paraValue = 0;
    returnVal = ffsll(paraValue);
    LOGD("    ffsll returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: ffsll returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_FFSLL_0900
* @tc.name       test fssll api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testFssll0900, TestSize.Level1) {
    long long int paraValue;
    int returnVal;

    paraValue = 0x800000000000;
    returnVal = ffsll(paraValue);
    LOGD("    ffsll returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(48 == returnVal) << "ErrInfo: ffsll returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_WCWIDTH_1100
* @tc.name       test wcwidth api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testWcwidth1100, TestSize.Level1) {
    wchar_t wideChar;
    int returnVal;

    wideChar = 'A';
    returnVal = wcwidth(wideChar);
    LOGD("    wcwidth returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(1 == returnVal) << "ErrInfo: wcwidth returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_STRINGOPER_WCTYPE_1200
* @tc.name       test wctype api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilStringOperApiTest, testWctype1200, TestSize.Level1) {
    const char *paraVal = "alnum";
    wctype_t returnVal;

    returnVal = wctype(paraVal);
    LOGD("    wcwidth returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: wcwidth returnVal:='" << returnVal << "'";
}