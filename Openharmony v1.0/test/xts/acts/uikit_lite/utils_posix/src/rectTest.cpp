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

class RectTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_OPERATOR_0100
* @tc.name       test rect operator api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectOpeartor, TestSize.Level0) {
    Rect* rect1 = new Rect();
    rect1->SetRect(100, 200, 300, 400);
    Rect* rect = new Rect();
    rect->operator=(*rect1);

    EXPECT_EQ(rect->GetLeft(), 100);
    EXPECT_EQ(rect->GetTop(), 200);
    EXPECT_EQ(rect->GetRight(), 300);
    EXPECT_EQ(rect->GetBottom(), 400);
    delete(rect1);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETRECT_0100
* @tc.name       test rect set rect api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetRect, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);

    EXPECT_EQ(rect->GetLeft(), 100);
    EXPECT_EQ(rect->GetTop(), 200);
    EXPECT_EQ(rect->GetRight(), 300);
    EXPECT_EQ(rect->GetBottom(), 400);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETWIDTH_0100
* @tc.name       test rect get width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetWidth, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);

    EXPECT_EQ(rect->GetWidth(), 201);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETHEIGHT_0100
* @tc.name       test rect get height api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetHeight, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);

    EXPECT_EQ(rect->GetHeight(), 201);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETX_0100
* @tc.name       test rect get x api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetX, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);

    EXPECT_EQ(rect->GetX(), 100);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETY_0100
* @tc.name       test rect get y api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetY, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);

    EXPECT_EQ(rect->GetY(), 200);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETLEFT_0100
* @tc.name       test rect get left api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetLeft, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);

    EXPECT_EQ(rect->GetLeft(), 100);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETTOP_0100
* @tc.name       test rect get top api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetTop, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);

    EXPECT_EQ(rect->GetTop(), 200);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETRIGHT_0100
* @tc.name       test rect get right api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetRight, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);

    EXPECT_EQ(rect->GetRight(), 300);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETBOTTOM_0100
* @tc.name       test rect get bottom api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetBOTTOM, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);
    EXPECT_EQ(rect->GetBottom(), 400);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETX_0100
* @tc.name       test rect set x api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetX, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);
    rect->SetX(200);
    EXPECT_EQ(rect->GetLeft(), 200);
    EXPECT_EQ(rect->GetRight(), 400);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETY_0100
* @tc.name       test rect set y api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetY, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);
    rect->SetY(300);
    EXPECT_EQ(rect->GetTop(), 300);
    EXPECT_EQ(rect->GetBottom(), 500);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETPOSITION_0100
* @tc.name       test rect set position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetPosition, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);
    rect->SetPosition(200, 300);
    EXPECT_EQ(rect->GetLeft(), 200);
    EXPECT_EQ(rect->GetRight(), 400);
    EXPECT_EQ(rect->GetTop(), 300);
    EXPECT_EQ(rect->GetBottom(), 500);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETWIDTH_0100
* @tc.name       test rect set width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetWidth, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);
    rect->SetWidth(300);
    EXPECT_EQ(rect->GetRight(), 399);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETHIGHT_0100
* @tc.name       test rect set height api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetHeight, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);
    rect->SetHeight(300);
    EXPECT_EQ(rect->GetBottom(), 499);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETLEFT_0100
* @tc.name       test rect set left api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetLeft, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetLeft(200);
    EXPECT_EQ(rect->GetLeft(), 200);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETTOP_0100
* @tc.name       test rect set top api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetTop, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetTop(200);
    EXPECT_EQ(rect->GetTop(), 200);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETRIGHT_0100
* @tc.name       test rect set right api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetRight, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRight(200);
    EXPECT_EQ(rect->GetRight(), 200);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_SETBOTTOM_0100
* @tc.name       test rect set bottom api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectSetBOTTOM, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetBottom(200);
    EXPECT_EQ(rect->GetBottom(), 200);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_RESIZE_0100
* @tc.name       test rect set resize api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectResize, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);
    rect->Resize(300, 300);

    EXPECT_EQ(rect->GetLeft(), 100);
    EXPECT_EQ(rect->GetTop(), 200);
    EXPECT_EQ(rect->GetRight(), 399);
    EXPECT_EQ(rect->GetBottom(), 499);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_GETSIZE_0100
* @tc.name       test rect get size api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectGetSize, TestSize.Level0) {
    Rect* rect = new Rect();
    rect->SetRect(100, 200, 300, 400);
    EXPECT_EQ(rect->GetSize(), 40401);
    delete(rect);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_INTERSECT_0100
* @tc.name       test rect intersect api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectIntersect, TestSize.Level0) {
    Rect* rect1 = new Rect(100, 200, 300, 400);
    Rect* rect2 = new Rect(0, 0, 500, 600);
    Rect* rect3 = new Rect(100, 500, 300, 600);

    EXPECT_EQ(rect1->Intersect(*rect1, *rect2), true);
    EXPECT_EQ(rect1->Intersect(*rect1, *rect3), false);
    delete(rect1);
    delete(rect2);
    delete(rect3);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_ISINTERSECT_0100
* @tc.name       test rect is intersect api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectIsIntersect, TestSize.Level0) {
    Rect* rect1 = new Rect(100, 200, 300, 400);
    Rect* rect2 = new Rect(0, 0, 500, 600);
    Rect* rect3 = new Rect(100, 500, 300, 700);

    EXPECT_EQ(rect1->IsIntersect(*rect2), true);
    EXPECT_EQ(rect1->IsIntersect(*rect3), false);
    delete(rect1);
    delete(rect2);
    delete(rect3);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_JOIN_0100
* @tc.name       test rect join api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectJoin, TestSize.Level0) {
    Rect* rect1 = new Rect(100, 200, 300, 400);
    Rect* rect2 = new Rect(0, 0, 500, 600);
    Rect* rect3 = new Rect(100, 500, 300, 700);

    rect1->Join(*rect1, *rect2);
    EXPECT_EQ(rect1->GetLeft(), 0);
    EXPECT_EQ(rect1->GetTop(), 0);
    EXPECT_EQ(rect1->GetRight(), 500);
    EXPECT_EQ(rect1->GetBottom(), 600);

    rect1->Join(*rect1, *rect3);
    EXPECT_EQ(rect1->GetLeft(), 0);
    EXPECT_EQ(rect1->GetTop(), 0);
    EXPECT_EQ(rect1->GetRight(), 500);
    EXPECT_EQ(rect1->GetBottom(), 700);
    delete(rect1);
    delete(rect2);
    delete(rect3);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_ISCONTAINS_0100
* @tc.name       test rect is contains api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectIsContains, TestSize.Level0) {
    Rect* rect1 = new Rect(100, 200, 300, 400);
    Vector2<int16_t> pt1 = { 200, 300 };
    Vector2<int16_t> pt2 = { 0, 0 };

    EXPECT_EQ(rect1->IsContains(pt1), true);
    EXPECT_EQ(rect1->IsContains(pt2), false);
    delete(rect1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_ISCONTAINS_0200
* @tc.name       test rect is contains api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectIsContains2, TestSize.Level0) {
    Rect* rect1 = new Rect(100, 200, 300, 400);
    Point pt1;
    pt1.x = 200;
    pt1.y = 300;
    Point pt2;
    pt2.x = 0;
    pt2.y = 0;
    EXPECT_EQ(rect1->IsContains(pt1), true);
    EXPECT_EQ(rect1->IsContains(pt2), false);
    delete(rect1);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_GEOMETRY2D_RECT_ISCONTAINS_0300
* @tc.name       test rect is contains api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RectTest, testRectIsContains3, TestSize.Level0) {
    Rect* rect1 = new Rect(100, 200, 300, 400);
    Rect* rect2 = new Rect(0, 0, 500, 600);
    Rect* rect3 = new Rect(100, 500, 300, 700);

    EXPECT_EQ(rect2->IsContains(*rect1), true);
    EXPECT_EQ(rect2->IsContains(*rect3), false);
    delete(rect1);
    delete(rect2);
    delete(rect3);
}
