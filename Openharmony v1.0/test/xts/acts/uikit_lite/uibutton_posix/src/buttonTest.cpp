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
#include "components/ui_button.h"
#include "core/system_booter.h"

using namespace OHOS;
using namespace testing::ext;

class ButtonTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
        SystemBooter::Init();
    }
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void) {}
    // Testcase setup
    virtual void SetUp() {}
    // Testcase teardown
    virtual void TearDown() {}
};

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_POSITION_0100
* @tc.name       test button position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonPosition, TestSize.Level0){
    UIButton* button = new UIButton();
    EXPECT_EQ(button->GetX(), 0);
    EXPECT_EQ(button->GetY(), 0);

    button->SetPosition(30, 200);
    EXPECT_EQ(button->GetX(), 30);
    EXPECT_EQ(button->GetY(), 200);

    button->SetX(60);
    button->SetY(160);
    EXPECT_EQ(button->GetX(), 60);
    EXPECT_EQ(button->GetY(), 160);

    button->SetPosition(100, 200, 300, 400);
    EXPECT_EQ(button->GetX(), 100);
    EXPECT_EQ(button->GetY(), 200);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_SIZE_0100
* @tc.name       test button size api by normal value
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonSizeNormal, TestSize.Level0){
    UIButton* button = new UIButton();
    EXPECT_EQ(button->GetWidth(), -1);
    EXPECT_EQ(button->GetHeight(), -1);

    button->SetWidth(90);
    button->SetHeight(60);
    EXPECT_EQ(button->GetWidth(), 90);
    EXPECT_EQ(button->GetHeight(), 60);

    button->SetPosition(100, 200, 300, 400);
    EXPECT_EQ(button->GetWidth(), 300);
    EXPECT_EQ(button->GetHeight(), 400);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_SIZE_0200
* @tc.name       test button size api by abnormal value
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonSizeAbnormal, TestSize.Level0){
    UIButton* button = new UIButton();
    button->SetWidth(-90);
    button->SetHeight(-60);
    EXPECT_EQ(button->GetWidth(), -90);
    EXPECT_EQ(button->GetHeight(), -60);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_STYLE_0100
* @tc.name       test button style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonStyle, TestSize.Level0){
    UIButton* button = new UIButton();
    button->SetStyle(STYLE_BACKGROUND_OPA, 0);
    button->SetStyle(STYLE_BACKGROUND_COLOR, 800);
    button->SetStyle(STYLE_BORDER_RADIUS, 100);
    button->SetStyle(STYLE_IMAGE_OPA, 190);

    EXPECT_EQ(button->GetStyle(STYLE_BACKGROUND_OPA), 0);
    EXPECT_EQ(button->GetStyle(STYLE_BACKGROUND_COLOR), 800);
    EXPECT_EQ(button->GetStyle(STYLE_BORDER_RADIUS), 100);
    EXPECT_EQ(button->GetStyle(STYLE_IMAGE_OPA), 190);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_STYLE_0200
* @tc.name       test button style for release api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonStyleStateReleased, TestSize.Level0){
    UIButton* button = new UIButton();
    button->SetStyleForState(STYLE_BACKGROUND_OPA, 100, UIButton::RELEASED);
    button->SetStyleForState(STYLE_BORDER_RADIUS, 200, UIButton::RELEASED);
    button->SetStyleForState(STYLE_BACKGROUND_COLOR, 300, UIButton::RELEASED);

    EXPECT_EQ(button->GetStyleForState(STYLE_BACKGROUND_OPA, UIButton::RELEASED), 100);
    EXPECT_EQ(button->GetStyleForState(STYLE_BORDER_RADIUS, UIButton::RELEASED), 200);
    EXPECT_EQ(button->GetStyleForState(STYLE_BACKGROUND_COLOR, UIButton::RELEASED), 300);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_STYLE_0300
* @tc.name       test button style for pressed api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonStyleStatePressed, TestSize.Level0){
    UIButton* button = new UIButton();
    button->SetStyleForState(STYLE_BACKGROUND_OPA, 50, UIButton::PRESSED);
    button->SetStyleForState(STYLE_BORDER_RADIUS, 100, UIButton::PRESSED);
    button->SetStyleForState(STYLE_BACKGROUND_COLOR, 900, UIButton::PRESSED);

    EXPECT_EQ(button->GetStyleForState(STYLE_BACKGROUND_OPA, UIButton::PRESSED), 50);
    EXPECT_EQ(button->GetStyleForState(STYLE_BORDER_RADIUS, UIButton::PRESSED), 100);
    EXPECT_EQ(button->GetStyleForState(STYLE_BACKGROUND_COLOR, UIButton::PRESSED), 900);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_STYLE_0400
* @tc.name       test button style for inactivate api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonStyleStateInactive, TestSize.Level0){
    UIButton* button = new UIButton();
    button->SetStyleForState(STYLE_BACKGROUND_OPA, 150, UIButton::INACTIVE);
    button->SetStyleForState(STYLE_BORDER_RADIUS, 800, UIButton::INACTIVE);
    button->SetStyleForState(STYLE_BACKGROUND_COLOR, 1900, UIButton::INACTIVE);

    EXPECT_EQ(button->GetStyleForState(STYLE_BACKGROUND_OPA, UIButton::INACTIVE), 150);
    EXPECT_EQ(button->GetStyleForState(STYLE_BORDER_RADIUS, UIButton::INACTIVE), 800);
    EXPECT_EQ(button->GetStyleForState(STYLE_BACKGROUND_COLOR, UIButton::INACTIVE), 1900);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_IMAGE_POSITION_0100
* @tc.name       test button set image position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonSetImagePosition, TestSize.Level0){
    UIButton* button = new UIButton();
    button->SetImagePosition(170, 190);
    EXPECT_EQ(button->GetImageX(), 170);
    EXPECT_EQ(button->GetImageY(), 190);

    button->SetImagePosition(-170, -190);
    EXPECT_EQ(button->GetImageX(), -170);
    EXPECT_EQ(button->GetImageY(), -190);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_IMAGE_SRC_0100
* @tc.name       test button set image src api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonSetImageSrc, TestSize.Level0){
    UIButton* button = new UIButton();
    char* path = nullptr;
    button->SetImageSrc(path, path);
    EXPECT_EQ(button->GetCurImageSrc()->GetPath(), nullptr);
    button->SetImageSrc("/user/data/A021_028.bin", "/user/data/A021_029.bin");
    EXPECT_NE(button->GetCurImageSrc()->GetPath(), nullptr);
    delete(button);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_BUTTON_TOUCHABLE_0100
* @tc.name       test button touchable api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ButtonTest, testButtonTouchable, TestSize.Level0){
    UIButton* button = new UIButton();
    EXPECT_EQ(button->IsTouchable(), true);

    button->Disable();
    EXPECT_EQ(button->IsTouchable(), false);

    button->Enable();
    EXPECT_EQ(button->IsTouchable(), true);
    delete(button);
}