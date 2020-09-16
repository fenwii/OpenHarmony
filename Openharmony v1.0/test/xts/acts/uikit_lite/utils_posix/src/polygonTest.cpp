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

class PolygonTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_POLYGON_MAKEAABB_0100
* @tc.name       test polygon makeAABB api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(PolygonTest, testPolygonMakeAABB, TestSize.Level0) {
    Vector2<int16_t> vertexes[4] = { {0, 0}, {500, 100}, {300, 500}, {100, 300} };
    Polygon* polygon = new Polygon(vertexes, 4);
    Rect rect = polygon->MakeAABB();
    EXPECT_EQ(rect.GetLeft(), 0);
    EXPECT_EQ(rect.GetTop(), 0);
    EXPECT_EQ(rect.GetRight(), 500);
    EXPECT_EQ(rect.GetBottom(), 500);
    delete(polygon);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_POLYGON_GETVERTEXNUM_0100
* @tc.name       test polygon get vertex num api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(PolygonTest, testPolygonGetVertexNum, TestSize.Level0) {
    Vector2<int16_t> vertexes[4] = { {0, 0}, {500, 100}, {300, 500}, {100, 300} };
    Polygon* polygon = new Polygon(vertexes, 4);
    EXPECT_EQ(polygon->GetVertexNum(), 4);
    delete(polygon);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_POLYGON_SETVERTEXNUM_0100
* @tc.name       test polygon set vertex num api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(PolygonTest, testPolygonSetVertexNum, TestSize.Level0) {
    Polygon* polygon = new Polygon();
    polygon->SetVertexNum(8);
    EXPECT_EQ(polygon->GetVertexNum(), 8);
    delete(polygon);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_POLYGON_OPERATOR_0100
* @tc.name       test polygon operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(PolygonTest, testPolygonOperator, TestSize.Level0) {
    Vector2<int16_t> vertexes[4] = { {0, 0}, {500, 100}, {300, 500}, {100, 300} };
    Polygon* polygon = new Polygon(vertexes, 4);
    EXPECT_EQ(polygon->operator[](1).x_, 500);
    EXPECT_EQ(polygon->operator[](2).y_, 500);
    delete(polygon);
}