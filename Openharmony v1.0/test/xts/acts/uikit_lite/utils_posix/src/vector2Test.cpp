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

class Vector2Test : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_DOT_0100
* @tc.name       test vector2 dot api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Dot, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 4);
    Vector2<uint16_t>* vector2 = new Vector2<uint16_t>(3, 2);

    EXPECT_EQ(vector1->Dot(*vector2), 23);
    delete(vector1);
    delete(vector2);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_CROSS_0100
* @tc.name       test vector2 cross api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Cross, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 4);
    Vector2<uint16_t>* vector2 = new Vector2<uint16_t>(3, 5);

    EXPECT_EQ(vector1->Cross(*vector2), 13);
    delete(vector1);
    delete(vector2);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_OPERATOR_0100
* @tc.name       test vector2 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Operator, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 4);
    Vector2<uint16_t> vector2 = vector1->operator-();

    EXPECT_EQ(vector2.x_, 65531);
    EXPECT_EQ(vector2.y_, 65532);
    delete(vector1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_OPERATOR_0200
* @tc.name       test vector2 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Operator2, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 7);
    Vector2<uint16_t>* vector2 = new Vector2<uint16_t>(3, 5);
    Vector2<uint16_t> vector3 = vector1->operator-(*vector2);

    EXPECT_EQ(vector3.x_, 2);
    EXPECT_EQ(vector3.y_, 2);
    delete(vector1);
    delete(vector2);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_OPERATOR_0300
* @tc.name       test vector2 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Operator3, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 7);
    Vector2<uint16_t>* vector2 = new Vector2<uint16_t>(3, 5);
    Vector2<uint16_t> vector3 = vector1->operator+(*vector2);

    EXPECT_EQ(vector3.x_, 8);
    EXPECT_EQ(vector3.y_, 12);
    delete(vector1);
    delete(vector2);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_OPERATOR_0400
* @tc.name       test vector2 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Operator4, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 7);
    Vector2<uint16_t> vector2 = vector1->operator*(2);

    EXPECT_EQ(vector2.x_, 10);
    EXPECT_EQ(vector2.y_, 14);
    delete(vector1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_OPERATOR_0500
* @tc.name       test vector2 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Operator5, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 7);
    Vector2<uint16_t>* vector2 = new Vector2<uint16_t>(5, 7);
    Vector2<uint16_t>* vector3 = new Vector2<uint16_t>(5, 8);

    EXPECT_EQ(vector1->operator==(*vector2), true);
    EXPECT_EQ(vector1->operator==(*vector3), false);
    delete(vector1);
    delete(vector2);
    delete(vector3);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_OPERATOR_0600
* @tc.name       test vector2 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Operator6, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 7);
    Vector2<uint16_t>* vector2 = new Vector2<uint16_t>(1, 2);
    vector1->operator=(*vector2);
    EXPECT_EQ(vector1->x_, 1);
    EXPECT_EQ(vector1->y_, 2);
    delete(vector1);
    delete(vector2);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_OPERATOR_0700
* @tc.name       test vector2 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Operator7, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 7);
    Vector2<uint16_t>* vector2 = new Vector2<uint16_t>(1, 2);
    vector1->operator+=(*vector2);
    EXPECT_EQ(vector1->x_, 6);
    EXPECT_EQ(vector1->y_, 9);
    delete(vector1);
    delete(vector2);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_VECTOR2_OPERATOR_0800
* @tc.name       test vector2 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Vector2Test, testVector2Operator8, TestSize.Level0) {
    Vector2<uint16_t>* vector1 = new Vector2<uint16_t>(5, 7);
    Vector2<uint16_t>* vector2 = new Vector2<uint16_t>(1, 2);
    vector1->operator-=(*vector2);
    EXPECT_EQ(vector1->x_, 4);
    EXPECT_EQ(vector1->y_, 5);
    delete(vector1);
    delete(vector2);
}