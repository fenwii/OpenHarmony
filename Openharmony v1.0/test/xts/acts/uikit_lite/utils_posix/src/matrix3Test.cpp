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

class Matrix3Test : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_GETDATA_0100
* @tc.name       test matrix3 get data api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3GetData, TestSize.Level0) {
    Matrix3<uint16_t>* matrix = new Matrix3<uint16_t>(1, 1, 1, 1, 1, 1, 1, 1, 1);
    EXPECT_EQ(matrix->GetData()[0], 1);
    EXPECT_EQ(matrix->GetData()[5], 1);
    delete(matrix);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_OPERATOR_0100
* @tc.name       test matrix3 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Operator, TestSize.Level0) {
    Matrix3<uint16_t>* matrix1 = new Matrix3<uint16_t>(1, 1, 1, 1, 1, 1, 1, 1, 1);
    Matrix3<uint16_t>* matrix2 = new Matrix3<uint16_t>(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3<uint16_t>* matrix3 = &matrix1->operator*(*matrix2);

    EXPECT_EQ(matrix3->GetData()[0], 6);
    EXPECT_EQ(matrix3->GetData()[1], 6);
    EXPECT_EQ(matrix3->GetData()[2], 6);
    EXPECT_EQ(matrix3->GetData()[3], 15);
    EXPECT_EQ(matrix3->GetData()[4], 15);
    EXPECT_EQ(matrix3->GetData()[5], 15);
    EXPECT_EQ(matrix3->GetData()[6], 24);
    EXPECT_EQ(matrix3->GetData()[7], 24);
    EXPECT_EQ(matrix3->GetData()[8], 24);
    delete(matrix1);
    delete(matrix2);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_OPERATOR_0200
* @tc.name       test matrix3 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Operator2, TestSize.Level0) {
    Matrix3<uint16_t>* matrix1 = new Matrix3<uint16_t>(1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vector3<uint16_t>* vector1 = new Vector3<uint16_t>(1, 2, 3);
    Vector3<uint16_t>* vector2 = &matrix1->operator*(*vector1);

    EXPECT_EQ(vector2->x_, 6);
    EXPECT_EQ(vector2->y_, 6);
    EXPECT_EQ(vector2->z_, 6);
    delete(matrix1);
    delete(vector1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_OPERATOR_0300
* @tc.name       test matrix3 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Operator3, TestSize.Level0) {
    Matrix3<uint16_t>* matrix = new Matrix3<uint16_t>(1, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_EQ(*matrix->operator[](0), 1);
    EXPECT_EQ(*matrix->operator[](1), 4);
    EXPECT_EQ(*matrix->operator[](2), 7);
    delete(matrix);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_OPERATOR_0400
* @tc.name       test matrix3 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Operator4, TestSize.Level0) {
    Matrix3<uint16_t>* matrix1 = new Matrix3<uint16_t>(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3<uint16_t>* matrix2 = new Matrix3<uint16_t>(1, 1, 1, 1, 1, 1, 1, 1, 1);
    matrix1->operator=(*matrix2);
    EXPECT_EQ(matrix1->GetData()[0], 1);
    EXPECT_EQ(matrix1->GetData()[1], 1);
    EXPECT_EQ(matrix1->GetData()[2], 1);
    EXPECT_EQ(matrix1->GetData()[3], 1);
    EXPECT_EQ(matrix1->GetData()[4], 1);
    EXPECT_EQ(matrix1->GetData()[5], 1);
    EXPECT_EQ(matrix1->GetData()[6], 1);
    EXPECT_EQ(matrix1->GetData()[7], 1);
    EXPECT_EQ(matrix1->GetData()[8], 1);
    delete(matrix1);
    delete(matrix2);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_OPERATOR_0500
* @tc.name       test matrix3 operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Operator5, TestSize.Level0) {
    Matrix3<uint16_t>* matrix1 = new Matrix3<uint16_t>(1, 1, 1, 1, 1, 1, 1, 1, 1);
    Matrix3<uint16_t>* matrix2 = new Matrix3<uint16_t>(1, 1, 1, 1, 1, 1, 1, 1, 1);
    Matrix3<uint16_t>* matrix3 = new Matrix3<uint16_t>(1, 1, 1, 1, 1, 1, 8, 1, 1);
    EXPECT_EQ(matrix1->operator==(*matrix2), true);
    EXPECT_EQ(matrix1->operator==(*matrix3), false);
    delete(matrix1);
    delete(matrix2);
    delete(matrix3);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_DETERMINANT_0100
* @tc.name       test matrix3 determinant api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Determinant, TestSize.Level0) {
    Matrix3<uint16_t>* matrix1 = new Matrix3<uint16_t>(1, 2, 2, 2, 1, 2, 2, 2, 1);
    EXPECT_EQ(matrix1->Determinant(), 5);
    delete(matrix1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_Inverse_0100
* @tc.name       test matrix3 inverse api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Inverse, TestSize.Level0) {
    Matrix3<uint16_t>* matrix1 = new Matrix3<uint16_t>(1, 1, 1, 1, 1, 1, 1, 1, 1);
    Matrix3<uint16_t>* matrix2 = &matrix1->Inverse();
    EXPECT_EQ(matrix2->GetData()[0], 1);
    EXPECT_EQ(matrix2->GetData()[1], 1);
    EXPECT_EQ(matrix2->GetData()[2], 1);
    EXPECT_EQ(matrix2->GetData()[3], 1);
    EXPECT_EQ(matrix2->GetData()[4], 1);
    EXPECT_EQ(matrix2->GetData()[5], 1);
    EXPECT_EQ(matrix2->GetData()[6], 1);
    EXPECT_EQ(matrix2->GetData()[7], 1);
    EXPECT_EQ(matrix2->GetData()[8], 1);
    delete(matrix1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_ROTATE_0100
* @tc.name       test matrix3 rotate api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Rotate, TestSize.Level0) {
    Matrix3<uint64_t> rotate = Matrix3<uint64_t>::Rotate(0, Vector2<uint64_t>(0, 0));
    EXPECT_EQ(rotate.GetData()[0], 32767);
    EXPECT_EQ(rotate.GetData()[1], 0);
    EXPECT_EQ(rotate.GetData()[2], 0);
    EXPECT_EQ(rotate.GetData()[3], 0);
    EXPECT_EQ(rotate.GetData()[4], 32767);
    EXPECT_EQ(rotate.GetData()[5], 0);
    EXPECT_EQ(rotate.GetData()[6], 0);
    EXPECT_EQ(rotate.GetData()[7], 0);
    EXPECT_EQ(rotate.GetData()[8], 32768);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_SCALE_0100
* @tc.name       test matrix3 scale api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Scale, TestSize.Level0) {
    Matrix3<int64_t> scale = Matrix3<int64_t>::Scale(Vector2<int64_t>(256, 256), Vector2<int64_t>(0, 0));
    EXPECT_EQ(scale.GetData()[0], 256);
    EXPECT_EQ(scale.GetData()[1], 0);
    EXPECT_EQ(scale.GetData()[2], 0);
    EXPECT_EQ(scale.GetData()[3], 0);
    EXPECT_EQ(scale.GetData()[4], 256);
    EXPECT_EQ(scale.GetData()[5], 0);
    EXPECT_EQ(scale.GetData()[6], 0);
    EXPECT_EQ(scale.GetData()[7], 0);
    EXPECT_EQ(scale.GetData()[8], 256);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_TRANSLATE_0100
* @tc.name       test matrix3 translate api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3Translate, TestSize.Level0) {
    Matrix3<int64_t> translate = Matrix3<int64_t>::Translate(Vector2<int64_t>(0, 0));
    EXPECT_EQ(translate.GetData()[0], 1);
    EXPECT_EQ(translate.GetData()[1], 0);
    EXPECT_EQ(translate.GetData()[2], 0);
    EXPECT_EQ(translate.GetData()[3], 0);
    EXPECT_EQ(translate.GetData()[4], 1);
    EXPECT_EQ(translate.GetData()[5], 0);
    EXPECT_EQ(translate.GetData()[6], 0);
    EXPECT_EQ(translate.GetData()[7], 0);
    EXPECT_EQ(translate.GetData()[8], 1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_MATH_MATRIX3_FLOATTOINT64_0100
* @tc.name       test matrix3 float to int 64 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Matrix3Test, testMatrix3FloatToInt64, TestSize.Level0) {
    EXPECT_EQ(FloatToInt64(1), 256);
}