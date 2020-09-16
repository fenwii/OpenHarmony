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
#include "components/ui_circle_progress.h"

using namespace OHOS;
using namespace testing::ext;

class CircleProgressTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_STEP_0100
* @tc.name       test circle progress step api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressStep, TestSize.Level0) {
    UICircleProgress* circleProgress = new UICircleProgress();
    uint16_t step = 10;
    circleProgress->SetStep(step);
    EXPECT_EQ(circleProgress->GetStep(), step);
    delete(circleProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_RADIUS_0100
* @tc.name       test circle progress radius api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressRadius, TestSize.Level0) {
    UICircleProgress *circleProgress = new UICircleProgress();
    uint16_t radius = 10;
    circleProgress->SetRadius(radius);

    EXPECT_EQ(circleProgress->GetRadius(), radius);
    delete(circleProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_CENTERPOSITION_0100
* @tc.name       test circle progress center position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressCenterPosition, TestSize.Level0) {
    UICircleProgress *circleProgress = new UICircleProgress();
    circleProgress->Resize(100, 100);
    int16_t centerX = 50;
    int16_t centerY = 50;
    circleProgress->SetCenterPosition(centerX, centerY);

    int16_t left = circleProgress->GetStyle(STYLE_PADDING_LEFT);
    int16_t top = circleProgress->GetStyle(STYLE_PADDING_TOP);
    int16_t borderWidth = circleProgress->GetStyle(STYLE_BORDER_WIDTH);

    EXPECT_EQ(circleProgress->GetCenterPosition().x, centerX + left + borderWidth);
    EXPECT_EQ(circleProgress->GetCenterPosition().y, centerY + top + borderWidth);
    delete(circleProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_CENTERPOSITION_0200
* @tc.name       test circle progress center position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressCenterPosition2, TestSize.Level0) {
    UICircleProgress *circleProgress = new UICircleProgress();
    circleProgress->SetStyle(STYLE_PADDING_LEFT, 10);
    circleProgress->SetStyle(STYLE_PADDING_TOP, 20);
    circleProgress->SetStyle(STYLE_BORDER_WIDTH, 30);
    circleProgress->Resize(100, 100);
    int16_t centerX = 50;
    int16_t centerY = 50;
    circleProgress->SetCenterPosition(centerX, centerY);

    int16_t left = circleProgress->GetStyle(STYLE_PADDING_LEFT);
    int16_t top = circleProgress->GetStyle(STYLE_PADDING_TOP);
    int16_t borderWidth = circleProgress->GetStyle(STYLE_BORDER_WIDTH);

    EXPECT_EQ(circleProgress->GetCenterPosition().x, centerX);
    EXPECT_EQ(circleProgress->GetCenterPosition().y, centerY);
    delete(circleProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_VALUE_0100
* @tc.name       test circle progress value api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressValue, TestSize.Level0) {
    UICircleProgress *circleProgress = new UICircleProgress();
    int16_t value = 10;
    circleProgress->SetValue(value);

    EXPECT_EQ(circleProgress->GetValue(), value);
    delete(circleProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_RANGE_0100
* @tc.name       test circle progress range api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressRange, TestSize.Level0) {
    UICircleProgress *circleProgress = new UICircleProgress();
    int16_t rangeMax = 500;
    int16_t rangeMin = 100;
    circleProgress->SetRange(rangeMax, rangeMin);
    EXPECT_EQ(circleProgress->GetRangeMax(), rangeMax);
    EXPECT_EQ(circleProgress->GetRangeMin(), rangeMin);
    delete(circleProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_STARTANGLE_0100
* @tc.name       test circle progress start angle api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressStartAngle, TestSize.Level0) {
    UICircleProgress *circleProgress = new UICircleProgress();
    int16_t startAngle = 50;
    circleProgress->SetStartAngle(startAngle);

    EXPECT_EQ(circleProgress->GetStartAngle(), startAngle);
    delete(circleProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_ENDANGLE_0100
* @tc.name       test circle progress end angle api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressEndAngle, TestSize.Level0) {
    UICircleProgress *circleProgress = new UICircleProgress();
    int16_t endAngle = 50;
    circleProgress->SetEndAngle(endAngle);

    EXPECT_EQ(circleProgress->GetEndAngle(), endAngle);
    delete(circleProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_CIRCLEPROGRESS_CIRCLEPROGRESS_LINECOLOR_0100
* @tc.name       test circle progress line color api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CircleProgressTest, testCircleProgressLineColor, TestSize.Level0) {
    UICircleProgress *circleProgress = new UICircleProgress();
    circleProgress->GetBackgroundStyle().line.color = Color::Yellow();
    ColorType color = Color::Red();
    circleProgress->SetLineColor(color);

    EXPECT_EQ(circleProgress->GetForegroundStyle().line.color.full, color.full);
    EXPECT_NE(circleProgress->GetBackgroundStyle().line.color.full, color.full);

    delete(circleProgress);
}