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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>

#include "gtest/gtest.h"
#include "XtsActsUtil.h"
#include "XtsActsMathApiExpect.h"

using namespace testing::ext;

class ActsMathApiTest : public testing::Test {
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
* @tc.number     SUB_KERNEL_NDKAPI_MATH_ABS_0100
* @tc.name       test abs api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsMathApiTest, testAbs, TestSize.Level1) {
    int returnVal, paraVal;

    paraVal = 3;
    returnVal = abs(paraVal);
	LogPrint("    abs i:='%d',   --> returnVal:='%d'\n", paraVal, returnVal);
    EXPECT_EQ(3, returnVal) << "ErrInfo: abs i:='" << paraVal << "',   --> returnVal:='" << returnVal << "'";
	
    paraVal = -3;
    returnVal = abs(paraVal);
	LogPrint("    abs i:='%d',   --> returnVal:='%d'\n", paraVal, returnVal);
    EXPECT_EQ(3, returnVal) << "ErrInfo: abs i:='" << paraVal << "',   --> returnVal:='" << returnVal << "'";

    paraVal = 0;
    returnVal = abs(paraVal);
	LogPrint("    abs i:='%d',   --> returnVal:='%d'\n", paraVal, returnVal);
    EXPECT_EQ(0, returnVal) << "ErrInfo: abs i:='" << paraVal << "',   --> returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MATH_DOUBLE_CEIL_0100
* @tc.name       test double ceil api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsMathApiTest, testCeil01, TestSize.Level1) {
    double returnVal, paraVal;

    paraVal = 123.45;
    returnVal = ceil(paraVal);
    EXPECT_EQ(124, returnVal) << "ErrInfo: ceil i:='" << paraVal << "',   returnVal:='" << returnVal << "'";

    paraVal = -5.9;
    returnVal = ceil(paraVal);
    EXPECT_EQ(-5, returnVal) << "ErrInfo: ceil i:='" << paraVal << "',   returnVal:='" << returnVal << "'";

    paraVal = 0;
    returnVal = ceil(paraVal);
    EXPECT_EQ(0, returnVal) << "ErrInfo: ceil i:='" << paraVal << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MATH_FLOAT_CEIL_0100
* @tc.name       test double ceil api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsMathApiTest, testCeil02, TestSize.Level1) {
    float returnVal, paraVal;

    paraVal = 123.45;
    returnVal = ceilf(paraVal);
    EXPECT_EQ(124, returnVal) << "ErrInfo: ceilf paraVal:='" << paraVal << "',   returnVal:='" << returnVal << "'";

    paraVal = -5.9;
    returnVal = ceilf(paraVal);
    EXPECT_EQ(-5, returnVal) << "ErrInfo: ceilf paraVal:='" << paraVal << "',   returnVal:='" << returnVal << "'";

    paraVal = 0;
    returnVal = ceilf(paraVal);
    EXPECT_EQ(0, returnVal) << "ErrInfo: ceilf paraVal:='" << paraVal << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MATH_DOUBLE_CBRT_0100
* @tc.name       test double ceil api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsMathApiTest, testCbrt01, TestSize.Level1) {
    double returnVal, paraVal;

    paraVal = 64;
    returnVal = cbrt(paraVal);
    EXPECT_EQ(4, returnVal) << "ErrInfo: cbrt paraVal:='" << paraVal << "',   returnVal:='" << returnVal << "'";

    paraVal = -125;
    returnVal = cbrt(paraVal);
    EXPECT_EQ(-5, returnVal) << "ErrInfo: cbrt paraVal:='" << paraVal << "',   returnVal:='" << returnVal << "'";

    paraVal = 0;
    returnVal = cbrt(paraVal);
    EXPECT_EQ(0, returnVal) << "ErrInfo: cbrt paraVal:='" << paraVal << "',   returnVal:='" << returnVal << "'";

    paraVal = 91.125;
    returnVal = cbrt(paraVal);
    EXPECT_EQ(4.5, returnVal) << "ErrInfo: cbrt paraVal:='" << paraVal << "',   returnVal:='" << returnVal << "'";
}
