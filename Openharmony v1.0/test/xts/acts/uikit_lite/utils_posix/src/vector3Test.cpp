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

class Vector3Test : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR3_OPERATOR_0100
* @tc.name       test vector3 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector3Test, testVector3Operator, TestSize.Level0) {
    Vector3<uint16_t>* vector1 = new Vector3<uint16_t>(3, 5, 7);
    EXPECT_EQ(vector1->operator[](0), 3);
    EXPECT_EQ(vector1->operator[](1), 5);
    EXPECT_EQ(vector1->operator[](2), 7);
    delete(vector1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR3_OPERATOR_0200
* @tc.name       test vector3 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector3Test, testVector3Operator2, TestSize.Level0) {
    Vector3<uint16_t>* vector1 = new Vector3<uint16_t>(3, 5, 7);
    Vector3<uint16_t>* vector2 = new Vector3<uint16_t>(3, 5, 7);
    Vector3<uint16_t>* vector3 = new Vector3<uint16_t>(3, 5, 9);

    EXPECT_EQ(vector1->operator==(*vector2), true);
    EXPECT_EQ(vector1->operator==(*vector3), false);
    delete(vector1);
    delete(vector2);
    delete(vector3);
}