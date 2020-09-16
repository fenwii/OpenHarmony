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
#include "components/root_view.h"
#include "components/ui_canvas.h"
#include "components/ui_view_group.h"

using namespace OHOS;
using namespace testing::ext;

class CanvasTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_STYLE_0100
* @tc.name       test canvas style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasStyle, TestSize.Level0) {
    Paint* paint = new Paint();
    Paint::PaintStyle paintStyle = Paint::PaintStyle::FILL_STYLE;
    paint->SetStyle(Paint::PaintStyle::FILL_STYLE);
    EXPECT_EQ(paint->GetStyle(), paintStyle);
    delete(paint);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_STROKEWIDTH_0100
* @tc.name       test canvas stroke width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasStrokeWidth, TestSize.Level0) {
    Paint* paint = new Paint();
    uint16_t width = 10;
    paint->SetStrokeWidth(width);
    EXPECT_EQ(paint->GetStrokeWidth(), width);
    delete(paint);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_OPACITY_0100
* @tc.name       test canvas opacity api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasOpacity, TestSize.Level0) {
    Paint* paint = new Paint();
    uint8_t opacity = OPA_50;
    paint->SetOpacity(OPA_50);
    EXPECT_EQ(paint->GetOpacity(), opacity);
    delete(paint);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_FILLCOLOR_0100
* @tc.name       test canvas fill color api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasFillColor, TestSize.Level0) {
    Paint* paint = new Paint();
    ColorType color = Color::Red();
    paint->SetFillColor(color);
    EXPECT_EQ(paint->GetFillColor().full, color.full);
    delete(paint);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_STROKECOLOR_0100
* @tc.name       test canvas stroke color api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasStrokeColor, TestSize.Level0) {
    Paint* paint = new Paint();
    ColorType color = Color::Red();
    paint->SetStrokeColor(color);
    EXPECT_EQ(paint->GetStrokeColor().full, color.full);
    delete(paint);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_STARTPOSITION_0100
* @tc.name       test canvas start position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasStartPosition, TestSize.Level0) {
    Paint* paint = new Paint();
    UICanvas* canvas = new UICanvas();
    canvas->SetStartPosition({ 50, 100 });
    EXPECT_EQ(canvas->GetStartPosition().x, 50);
    EXPECT_EQ(canvas->GetStartPosition().y, 100);
    delete(paint);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_DRAWLINE_0200
* @tc.name       test canvas draw line position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasDrawLine, TestSize.Level0) {
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    viewGroup->SetPosition(0, 0);
    UICanvas* canvas = new UICanvas();
    Paint paint;
    canvas->DrawLine({ 0, 50 }, { 50, 100 }, paint);
    viewGroup->Add(canvas);
    EXPECT_EQ(canvas->GetStartPosition().x, 50);
    viewGroup->Remove(canvas);
    delete(canvas);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_DRAWCURVE_0200
* @tc.name       test canvas draw curve api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasDrawCurve, TestSize.Level0) {
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    viewGroup->SetPosition(0, 0);
    UICanvas* canvas = new UICanvas();
    Paint paint;
    canvas->DrawCurve({ 100, 100 }, { 150, 100 }, { 150, 100 }, { 150, 200 }, paint);
    viewGroup->Add(canvas);
    EXPECT_EQ(canvas->GetStartPosition().y, 200);
    viewGroup->Remove(canvas);
    delete(canvas);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_DRAWRECT_0200
* @tc.name       test canvas draw rect api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasDrawRect, TestSize.Level0) {
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    viewGroup->SetPosition(0, 0);
    UICanvas* canvas = new UICanvas();
    Paint paint;
    canvas->DrawRect({0, 50}, 50, 50, paint);
    viewGroup->Add(canvas);
    EXPECT_EQ(canvas->GetStartPosition().y, 0);
    viewGroup->Remove(canvas);
    delete(canvas);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_DRAWCIRCLE_0200
* @tc.name       test canvas draw circle api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasDrawCircle, TestSize.Level0) {
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    viewGroup->SetPosition(0, 0);
    UICanvas* canvas = new UICanvas();
    Paint paint;
    canvas->DrawCircle({50, 50}, 25, paint);
    viewGroup->Add(canvas);
    EXPECT_EQ(canvas->GetStartPosition().y, 0);
    viewGroup->Remove(canvas);
    delete(canvas);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CANVAS_CANVAS_DRAWSECTOR_0200
* @tc.name       test canvas draw sector api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CanvasTest, testCanvasDrawSector, TestSize.Level0) {
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    viewGroup->SetPosition(0, 0);
    UICanvas* canvas = new UICanvas();
    Paint paint;
    canvas->DrawSector({50, 0}, 50, 0, 90, paint);
    viewGroup->Add(canvas);
    EXPECT_EQ(canvas->GetStartPosition().y, 0);
    viewGroup->Remove(canvas);
    delete(canvas);
}