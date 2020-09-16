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

#include "gtest/gtest.h"
#include "log.h"
#include "utils.h"

using namespace testing::ext;

class ActsUtilMathApiTest : public testing::Test {
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
* @tc.number     SUB_KERNEL_UTIL_MATH_DRAND48_0100
* @tc.name       test drand48 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilMathApiTest, testDrand480100, TestSize.Level1) {
    double returnVal;
    long seedVal;

    seedVal = 12345;
    srand48(seedVal);
    returnVal = drand48();
    LOGD("    drand48 returnVal:='%f'\n", returnVal);
    ASSERT_TRUE(returnVal >= 0.0 && returnVal < 1.0) << "ErrInfo: drand48 returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_MATH_ERAND48_0200
* @tc.name       test erand48 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilMathApiTest, testErand480200, TestSize.Level1) {
    double returnVal;
    unsigned short xsubi[3] = {0, 1, 2};

    returnVal = erand48(xsubi);
    LOGD("    erand48 returnVal:='%f'\n", returnVal);
    ASSERT_TRUE(returnVal >= 0.0 && returnVal < 1.0) << "ErrInfo: erand48 returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_MATH_JRAND48_0300
* @tc.name       test jrand48 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilMathApiTest, testJrand480300, TestSize.Level1) {
    long returnVal;
    unsigned short xsubi[3] = {0, 1, 2};

    returnVal = jrand48(xsubi);
    LOGD("    jrand48 returnVal:='%ld'\n", returnVal);
    ASSERT_TRUE(returnVal >= -2147483648)
        << "ErrInfo: jrand48 returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_MATH_MAND48_0400
* @tc.name       test mrand48 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilMathApiTest, testMrand480400, TestSize.Level1) {
    long returnVal;
    unsigned short paraVal[7] = {0, 1, 2, 3, 4, 5, 6};

    lcong48(paraVal);
    returnVal = mrand48();
    LOGD("    mrand48 returnVal:='%ld'\n", returnVal);
    ASSERT_TRUE(returnVal >= -2147483648)
        << "ErrInfo: mrand48 returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_MATH_LAND48_0500
* @tc.name       test lrand48 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilMathApiTest, testLrand480500, TestSize.Level1) {
    long returnVal;
    unsigned short paraVal[3] = {0, 1, 2};

    seed48(paraVal);
    returnVal = lrand48();
    LOGD("    lrand48 returnVal:='%ld'\n", returnVal);
    ASSERT_TRUE(returnVal >= 0) << "ErrInfo: lrand48 returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_MATH_NRAND48_0700
* @tc.name       test nrand48 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilMathApiTest, testNrand480700, TestSize.Level1) {
    long returnVal;
    unsigned short paraVal[3] = {0, 1, 2};

    returnVal = nrand48(paraVal);
    LOGD("    nrand48 returnVal:='%ld'\n", returnVal);
    ASSERT_TRUE(returnVal >= 0) << "ErrInfo: nrand48 returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_MATH_RAND_R_0800
* @tc.name       test rand_r api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilMathApiTest, testNrand480800, TestSize.Level1) {
    int returnVal;
    unsigned int paraVal;

    returnVal = rand_r(&paraVal);
    LOGD("    rand_r returnVal:='%ld'\n", returnVal);
    ASSERT_TRUE(returnVal >= 0 && returnVal <= RAND_MAX) << "ErrInfo: rand_r returnVal:='" << returnVal << "'";
}