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
#include "demo.h"
using namespace std;
using namespace testing::ext;

class Demo: public testing::Test {
protected:
    // SetUpTestCase：测试套预置动作，在第一个TestCase之前执行
    static void SetUpTestCase(void) {}
    // TearDownTestCase：测试套清理动作，在最后一个TestCase之后执行
    static void TearDownTestCase(void) {}
    // 用例的预置动作
    virtual void SetUp() {}
    // 用例的清理动作
    virtual void TearDown() {}
};


// Return the sum of n.  If n is negative, return 0.
static int Sum(int n)
{
    if (n <= 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

/**
 * @tc.number    : TEST_CASE_100 
 * @tc.name      : Demo test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(Demo, Negative, TestSize.Level0) {
    EXPECT_EQ(NUM0, Sum(NG_NUM5));
    EXPECT_EQ(NUM0, Sum(NG_NUM1));
}

/**
 * @tc.number    : TEST_CASE_200
 * @tc.name      : Demo test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(Demo, Zero, TestSize.Level0) {
    EXPECT_EQ(NUM0, Sum(NUM0));
}

/**
 * @tc.number    : TEST_CASE_300
 * @tc.name      : Demo test
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 0
 */
HWTEST_F(Demo, Positive, TestSize.Level0) {
    EXPECT_EQ(NUM1, Sum(NUM1));
    EXPECT_EQ(NUM45, Sum(NUM10));
    EXPECT_EQ(NUM4950, Sum(NUM100));
}
