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
#include "components/ui_toggle_button.h"
#include "core/system_booter.h"
using namespace OHOS;
using namespace testing::ext;

class ToggleButtonTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_TOGGLEBUTTON_POSITION_0100
* @tc.name       test toggle button position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ToggleButtonTest, testToggleButtonPosition, TestSize.Level0){
    UIToggleButton* togglebutton = new UIToggleButton();
    EXPECT_EQ(togglebutton->GetX(), 0);
    EXPECT_EQ(togglebutton->GetY(), 0);

    togglebutton->SetPosition(30, 200);
    EXPECT_EQ(togglebutton->GetX(), 30);
    EXPECT_EQ(togglebutton->GetY(), 200);

    togglebutton->SetX(60);
    togglebutton->SetY(160);
    EXPECT_EQ(togglebutton->GetX(), 60);
    EXPECT_EQ(togglebutton->GetY(), 160);

    togglebutton->SetPosition(100, 200, 300, 400);
    EXPECT_EQ(togglebutton->GetX(), 100);
    EXPECT_EQ(togglebutton->GetY(), 200);
    delete(togglebutton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_TOGGLEBUTTON_SIZE_0100
* @tc.name       test toggle button size api by normal value
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ToggleButtonTest, testToggleButtonSizeNormal, TestSize.Level0){
    UIToggleButton* togglebutton = new UIToggleButton();
    EXPECT_EQ(togglebutton->GetWidth(), 64);
    EXPECT_EQ(togglebutton->GetHeight(), 64);

    togglebutton->SetWidth(90);
    togglebutton->SetHeight(60);
    EXPECT_EQ(togglebutton->GetWidth(), 90);
    EXPECT_EQ(togglebutton->GetHeight(), 60);

    togglebutton->SetPosition(100, 200, 300, 400);
    EXPECT_EQ(togglebutton->GetWidth(), 300);
    EXPECT_EQ(togglebutton->GetHeight(), 400);
    delete(togglebutton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_TOGGLEBUTTON_SIZE_0200
* @tc.name       test toggle button size api by abnormal value
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ToggleButtonTest, testToggleButtonOSizeAbnormal, TestSize.Level0){
    UIToggleButton* togglebutton = new UIToggleButton();
    togglebutton->SetWidth(-90);
    togglebutton->SetHeight(-60);
    EXPECT_EQ(togglebutton->GetWidth(), -90);
    EXPECT_EQ(togglebutton->GetHeight(), -60);
    delete(togglebutton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_TOGGLEBUTTON_STATE_0100
* @tc.name       test toggle button set state api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ToggleButtonTest, testToggleButtonSetState, TestSize.Level0){
    UIToggleButton* togglebutton = new UIToggleButton();
    EXPECT_EQ(togglebutton->GetState(), false);

    togglebutton->SetState(true);
    EXPECT_EQ(togglebutton->GetState(), true);

    togglebutton->SetState(false);
    EXPECT_EQ(togglebutton->GetState(), false);
    delete(togglebutton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_TOGGLEBUTTON_STYLE_0100
* @tc.name       test toggle button style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ToggleButtonTest, testToggleButtonStyle, TestSize.Level0){
    UIToggleButton* togglebutton = new UIToggleButton();
    togglebutton->SetStyle(STYLE_BACKGROUND_OPA, 100);
    togglebutton->SetStyle(STYLE_BACKGROUND_COLOR, 300);
    togglebutton->SetStyle(STYLE_BORDER_RADIUS, 200);

    EXPECT_EQ(togglebutton->GetStyle(STYLE_BACKGROUND_OPA), 100);
    EXPECT_EQ(togglebutton->GetStyle(STYLE_BACKGROUND_COLOR), 300);
    EXPECT_EQ(togglebutton->GetStyle(STYLE_BORDER_RADIUS), 200);

    togglebutton->SetStyle(STYLE_BACKGROUND_OPA, 50);
    togglebutton->SetStyle(STYLE_BACKGROUND_COLOR, 900);
    togglebutton->SetStyle(STYLE_BORDER_RADIUS, 100);

    EXPECT_EQ(togglebutton->GetStyle(STYLE_BACKGROUND_OPA), 50);
    EXPECT_EQ(togglebutton->GetStyle(STYLE_BACKGROUND_COLOR), 900);
    EXPECT_EQ(togglebutton->GetStyle(STYLE_BORDER_RADIUS), 100);

    togglebutton->SetStyle(STYLE_BACKGROUND_OPA, 150);
    togglebutton->SetStyle(STYLE_BACKGROUND_COLOR, 1900);
    togglebutton->SetStyle(STYLE_BORDER_RADIUS, 800);

    EXPECT_EQ(togglebutton->GetStyle(STYLE_BACKGROUND_OPA), 150);
    EXPECT_EQ(togglebutton->GetStyle(STYLE_BACKGROUND_COLOR), 1900);
    EXPECT_EQ(togglebutton->GetStyle(STYLE_BORDER_RADIUS), 800);

    delete(togglebutton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_TOGGLEBUTTON_EVENT_0100
* @tc.name       test toggle button event api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ToggleButtonTest, testToggleButtonEvent, TestSize.Level0){
    UIToggleButton* togglebutton = new UIToggleButton();
    togglebutton->SetPosition(300, 400);
    togglebutton->SetWidth(90);
    togglebutton->SetHeight(60);
    togglebutton->SetState(true);
    ClickEvent event({310, 410});
    togglebutton->OnClickEvent(event);
    EXPECT_EQ(togglebutton->GetState(), false);
    delete(togglebutton);
}