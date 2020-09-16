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

class Geometry2dTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_GEOMETRY2D_INTERSECT_0100
* @tc.name       test geometry2d intersect api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Geometry2dTest, testGeometry2dIntersect, TestSize.Level0) {
    Vector2<int16_t> pt11 = { 0, 200 };
    Vector2<int16_t> pt12 = { 400, 200 };
    Line* line1 = new Line(pt11, pt12);
    Vector2<int16_t> pt21 = { 200, 0 };
    Vector2<int16_t> pt22 = { 200, 400 };
    Line* line2 = new Line(pt21, pt22);
    Vector2<int16_t> pt31 = { 0, 0 };
    Vector2<int16_t> pt32 = { 500, 0 };
    Line* line3 = new Line(pt31, pt32);
    Vector2<int16_t> out;

    EXPECT_EQ(Intersect(*line1, *line2, out), true);
    EXPECT_EQ(out.x_, 200);
    EXPECT_EQ(out.y_, 200);
    EXPECT_EQ(Intersect(*line1, *line3, out), false);
    delete(line1);
    delete(line2);
    delete(line3);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_GEOMETRY2D_ISINTERSECT_0100
* @tc.name       test geometry2d is intersect api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Geometry2dTest, testGeometry2dIsIntersect, TestSize.Level0) {
    Vector2<int16_t> pt11 = { 0, 200 };
    Vector2<int16_t> pt12 = { 400, 200 };
    Line* line1 = new Line(pt11, pt12);
    Vector2<int16_t> pt21 = { 200, 0 };
    Vector2<int16_t> pt22 = { 200, 400 };
    Line* line2 = new Line(pt21, pt22);
    Vector2<int16_t> pt31 = { 0, 0 };
    Vector2<int16_t> pt32 = { 500, 0 };
    Line* line3 = new Line(pt31, pt32);

    EXPECT_EQ(IsIntersect(*line1, *line2), true);
    EXPECT_EQ(IsIntersect(*line1, *line3), false);
    delete(line1);
    delete(line2);
    delete(line3);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_GEOMETRY2D_CLIP_0100
* @tc.name       test geometry2d clip api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(Geometry2dTest, testGeometry2dClip, TestSize.Level0) {
    Vector2<int16_t> vertexes[4] = { {0, 0}, {500, 100}, {300, 500}, {100, 300} };
    Polygon* polygon = new Polygon(vertexes, 4);
    Vector2<int16_t> pt11 = { 100, 300 };
    Vector2<int16_t> pt12 = { 500, 100 };
    Line* line = new Line(pt11, pt12);
    Clip(*polygon, *line);

    EXPECT_EQ(polygon->GetVertexNum(), 3);
    EXPECT_EQ(polygon->operator[](0).x_, 500);
    EXPECT_EQ(polygon->operator[](0).y_, 100);
    EXPECT_EQ(polygon->operator[](1).x_, 100);
    EXPECT_EQ(polygon->operator[](1).y_, 300);
    EXPECT_EQ(polygon->operator[](2).x_, 0);
    EXPECT_EQ(polygon->operator[](2).y_, 0);
    delete(polygon);
    delete(line);
}