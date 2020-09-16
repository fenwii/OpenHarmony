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
#include "utils/graphic_math.h"

using namespace OHOS;
using namespace testing::ext;

class MathTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATH_SIN_0100
* @tc.name       test math sin api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(MathTest, testMathSin, TestSize.Level0) {
    EXPECT_EQ(Sin(0), 0);
    EXPECT_EQ(Sin(90), 32767);
    EXPECT_EQ(Sin(180), 0);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATH_FASTATAN2_0100
* @tc.name       test math fast atan2 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(MathTest, testMathFastAtan2, TestSize.Level0) {
    EXPECT_EQ(FastAtan2(0, 1), 0);
    EXPECT_EQ(FastAtan2(1, 0), 90);
    EXPECT_EQ(FastAtan2(0, -1), 180);
    EXPECT_EQ(FastAtan2(-1, 0), 270);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATH_SQRT_0100
* @tc.name       test math sqrt api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(MathTest, testMathSqrt, TestSize.Level0) {
    EXPECT_EQ(Sqrt(0), 0);
    EXPECT_EQ(Sqrt(4), 2);
    EXPECT_EQ(Sqrt(25), 5);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATH_FLOATTOINT64_0100
* @tc.name       test math float to int 64 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(MathTest, testMathFloatToInt64, TestSize.Level0) {
    EXPECT_EQ(FloatToInt64(1), 256);
}