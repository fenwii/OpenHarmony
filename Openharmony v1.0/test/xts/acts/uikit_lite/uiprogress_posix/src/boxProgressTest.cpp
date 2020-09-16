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
#include "components/ui_box_progress.h"

using namespace OHOS;
using namespace testing::ext;

class BoxProgressTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_STEP_0100
* @tc.name       test box progress step api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressStepTest1, TestSize.Level0) {
    auto boxProgress = new UIBoxProgress();
    uint16_t step = 0;
    int16_t value = 1;
    boxProgress->SetRange(100, 0);
    boxProgress->SetValue(0);
    boxProgress->SetStep(step);
    boxProgress->SetValue(value);
    EXPECT_EQ(boxProgress->GetStep(), step);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_STEP_0200
* @tc.name       test box progress step api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressStepTest2, TestSize.Level0) {
    auto boxProgress = new UIBoxProgress();
    uint16_t step = 10;
    int16_t value = 20;
    boxProgress->SetRange(100, 0);
    boxProgress->SetValue(value);
    boxProgress->SetStep(step);
    boxProgress->SetValue(value + step - 1);
    EXPECT_EQ(boxProgress->GetStep(), step);
    EXPECT_EQ(boxProgress->GetValue(), value + step - 1);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_STEP_0300
* @tc.name       test box progress step api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressStepTest3, TestSize.Level0) {
    auto boxProgress = new UIBoxProgress();
    uint16_t step = 10;
    int16_t value = 20;
    boxProgress->SetRange(100, 0);
    boxProgress->SetValue(value);
    boxProgress->SetStep(step);
    boxProgress->SetValue(value - step + 1);
    EXPECT_EQ(boxProgress->GetStep(), step);
    EXPECT_EQ(boxProgress->GetValue(), value - step + 1);
    delete(boxProgress);
}
/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_DRIECTION_0100
* @tc.name       test box progress direction api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressDirection, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    UIBoxProgress::Direction direction = UIBoxProgress::Direction::DIR_BOTTOM_TO_TOP;
    boxProgress->SetDirection(direction);

    EXPECT_EQ(boxProgress->GetDirection(), direction);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_VALIDWIDTH_0100
* @tc.name       test box progress valid width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressValidWidth, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    boxProgress->Resize(100, 100);
    int16_t validWidth = 10;
    boxProgress->SetValidWidth(validWidth);
    EXPECT_EQ(boxProgress->GetValidWidth(), validWidth);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_VALIDHEIGHT_0100
* @tc.name       test box progress valid height api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressValidHeight, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    boxProgress->Resize(100, 100);
    int16_t validHeight = 10;
    boxProgress->SetValidHeight(validHeight);

    EXPECT_EQ(boxProgress->GetValidHeight(), validHeight);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_VALUE_0100
* @tc.name       test box progress value api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressValueTest1, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    int16_t value = 10;
    boxProgress->SetValue(value);

    EXPECT_EQ(boxProgress->GetValue(), value);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_VALUE_0200
* @tc.name       test box progress value api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressValueTest2, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    int16_t rangeMax = 500;
    int16_t rangeMin = 100;
    boxProgress->SetRange(rangeMax, rangeMin);

    int16_t value = rangeMin - 1;
    boxProgress->SetValue(value);
    EXPECT_EQ(boxProgress->GetValue(), rangeMin);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_VALUE_0300
* @tc.name       test box progress value api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressValueTest3, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    int16_t rangeMax = 500;
    int16_t rangeMin = 100;
    boxProgress->SetRange(rangeMax, rangeMin);

    int16_t value = rangeMax + 1;
    boxProgress->SetValue(value);
    EXPECT_EQ(boxProgress->GetValue(), rangeMax);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_RANGE_0100
* @tc.name       test box progress range api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressRange, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    int16_t rangeMax = 500;
    int16_t rangeMin = 100;
    boxProgress->SetRange(rangeMax, rangeMin);

    EXPECT_EQ(boxProgress->GetRangeMax(), rangeMax);
    EXPECT_EQ(boxProgress->GetRangeMin(), rangeMin);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_WIDTH_0100
* @tc.name       test box progress width api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressWidth, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    int16_t width = 100;
    boxProgress->SetWidth(width);

    EXPECT_EQ(boxProgress->GetWidth(), width);
    EXPECT_EQ(boxProgress->GetValidWidth(), width);
    delete(boxProgress);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BOXPROGRESS_HEIGHT_0100
* @tc.name       test box progress height api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(BoxProgressTest, testBoxProgressHeight, TestSize.Level0) {
    UIBoxProgress *boxProgress = new UIBoxProgress();
    int16_t height = 100;
    boxProgress->SetHeight(height);

    EXPECT_EQ(boxProgress->GetHeight(), height);
    EXPECT_EQ(boxProgress->GetValidHeight(), height);
    delete(boxProgress);
}