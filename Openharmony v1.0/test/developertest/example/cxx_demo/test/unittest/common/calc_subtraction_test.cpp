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

#include <climits>
#include <gtest/gtest.h>

using namespace std;
using namespace testing::ext;

class CalcSubtractionTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};

void CalcSubtractionTest::SetUpTestCase(void)
{
    // step 2: input testsuit setup step
}

void CalcSubtractionTest::TearDownTestCase(void)
{
    // step 2: input testsuit teardown step
}

void CalcSubtractionTest::SetUp(void)
{
    // step 3: input testcase setup step
}

void CalcSubtractionTest::TearDown(void)
{
    // step 3: input testcase teardown step
}

static int Subtraction(int a, int b)
{
    return a - b;
}

/*
 * Feature: Calculator
 * Function: Subtraction
 * SubFunction: NA
 * FunctionPoints: Integer Subtraction
 * EnvConditions: NA
 * CaseDescription: Verify the Subtraction function.
 */
HWTEST_F(CalcSubtractionTest, integer_sub_001, TestSize.Level1)
{
    EXPECT_EQ(0, Subtraction(1, 0));
}

/*
 * Feature: Calculator
 * Function: Subtraction
 * SubFunction: NA
 * FunctionPoints: Integer Subtraction
 * EnvConditions: NA
 * CaseDescription: Verify the Subtraction function.
 */
HWTEST_F(CalcSubtractionTest, integer_sub_002, TestSize.Level1)
{
    EXPECT_EQ(1, Subtraction(2, 1));
}