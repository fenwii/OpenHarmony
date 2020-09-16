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
#include "components/ui_slider.h"
#include "components/ui_view_group.h"

using namespace OHOS;
using namespace testing::ext;

class SliderViewTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_STEP_0100
* @tc.name       test slider step api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderStep, TestSize.Level0) {
    UISlider* slider = new UISlider();
    int16_t step = 10;
    slider->SetStep(step);
    EXPECT_EQ(slider->GetStep(), step);
    delete(slider);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_DIRECTION_0100
* @tc.name       test slider direction api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderDirection, TestSize.Level0) {
    UISlider* slider = new UISlider();
    UISlider::Direction direction = UISlider::Direction::DIR_BOTTOM_TO_TOP;
    slider->SetDirection(direction);

    EXPECT_EQ(slider->GetDirection(), direction);
    delete(slider);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_VALIDWIDTH_0100
* @tc.name       test slider valid width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderValidWidth, TestSize.Level0) {
    UISlider* slider = new UISlider();
    slider->Resize(100, 100);
    int16_t validWidth = 10;
    slider->SetValidWidth(validWidth);
    EXPECT_EQ(slider->GetValidWidth(), validWidth);
    delete(slider);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_VALIDHEIGHT_0100
* @tc.name       test slider valid height api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderValidHeight, TestSize.Level0) {
    UISlider* slider = new UISlider();
    slider->Resize(100, 100);
    int16_t validHeight = 10;
    slider->SetValidHeight(validHeight);
    EXPECT_EQ(slider->GetValidHeight(), validHeight);
    delete(slider);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_VALUE_0100
* @tc.name       test slider value api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderValue, TestSize.Level0) {
    UISlider* slider = new UISlider();
    int16_t value = 10;
    slider->SetValue(value);
    EXPECT_EQ(slider->GetValue(), value);
    delete(slider);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_RANGE_0100
* @tc.name       test slider range api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderRangeTest1, TestSize.Level0) {
    UISlider* slider = new UISlider();
    int16_t rangeMax = 500;
    int16_t rangeMin = 100;
    slider->SetRange(rangeMax, rangeMin);
    EXPECT_EQ(slider->GetRangeMax(), rangeMax);
    EXPECT_EQ(slider->GetRangeMin(), rangeMin);
    delete(slider);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_KNOBWIDTH_0100
* @tc.name       test slider knob width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderRangeTest2, TestSize.Level0) {
    UISlider* slider = new UISlider();
    int16_t knobWidth = 10;
    slider->SetKnobWidth(knobWidth);
    EXPECT_EQ(slider->GetKnobWidth(), knobWidth);
    delete(slider);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_DEFAULTKNOBWIDTH_0100
* @tc.name       test slider default knob width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderDefaultKnobWidthTest1, TestSize.Level0) {
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    viewGroup->SetPosition(0, 0);
    viewGroup->SetWidth(HORIZONTAL_RESOLUTION);
    viewGroup->SetHeight(VERTICAL_RESOLUTION);

    UISlider* slider = new UISlider();
    viewGroup->Add(slider);
    int16_t width = 100;
    int16_t height = 10;
    slider->SetWidth(width);
    slider->SetHeight(height);
    slider->SetDirection(UISlider::Direction::DIR_LEFT_TO_RIGHT);
    viewGroup->Invalidate();
    EXPECT_EQ(slider->GetKnobWidth(), height);

    slider->SetDirection(UISlider::Direction::DIR_RIGHT_TO_LEFT);
    slider->Invalidate();
    EXPECT_EQ(slider->GetKnobWidth(), height);

    viewGroup->Remove(slider);
    delete(slider);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SLIDER_SLIDER_DEFAULTKNOBWIDTH_0200
* @tc.name       test slider default knob width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SliderViewTest, testSliderDefaultKnobWidthTest2, TestSize.Level0) {
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    viewGroup->SetPosition(0, 0);
    viewGroup->SetWidth(HORIZONTAL_RESOLUTION);
    viewGroup->SetHeight(VERTICAL_RESOLUTION);

    UISlider* slider = new UISlider();
    viewGroup->Add(slider);
    int16_t width = 10;
    int16_t height = 100;
    slider->SetWidth(width);
    slider->SetHeight(height);
    slider->SetDirection(UISlider::Direction::DIR_BOTTOM_TO_TOP);
    viewGroup->Invalidate();
    EXPECT_EQ(slider->GetKnobWidth(), width);

    slider->SetDirection(UISlider::Direction::DIR_TOP_TO_BOTTOM);
    slider->Invalidate();
    EXPECT_EQ(slider->GetKnobWidth(), width);

    viewGroup->Remove(slider);
    delete(slider);
}