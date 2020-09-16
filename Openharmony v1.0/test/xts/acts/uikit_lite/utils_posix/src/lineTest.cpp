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
#include "utils/geometry2d.h"

using namespace OHOS;
using namespace testing::ext;

class LineTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_LINE_OPERATOR_0100
* @tc.name       test line operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(LineTest, testLineOpeartor, TestSize.Level0) {
    Vector2<int16_t> pt1 = { 100, 200 };
    Vector2<int16_t> pt2 = { 300, 400 };
    Line* line = new Line(pt1, pt2);

    EXPECT_EQ(line->operator[](0).x_, 100);
    EXPECT_EQ(line->operator[](0).y_, 200);
    EXPECT_EQ(line->operator[](1).x_, 300);
    EXPECT_EQ(line->operator[](1).y_, 400);
    delete(line);
}