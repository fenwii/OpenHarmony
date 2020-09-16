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
#include "components/ui_radiobutton.h"
#include "components/ui_view_group.h"
#include "core/system_booter.h"

using namespace OHOS;
using namespace testing::ext;

class RadioButtonTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_RADIOBUTTON_POSITION_0100
* @tc.name       test radio button position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RadioButtonTest, testRadioButtonPosition, TestSize.Level0){
    UIRadioButton* radioButton = new UIRadioButton("aasd");
    EXPECT_EQ(radioButton->GetX(), 0);
    EXPECT_EQ(radioButton->GetY(), 0);

    radioButton->SetPosition(30, 200);
    EXPECT_EQ(radioButton->GetX(), 30);
    EXPECT_EQ(radioButton->GetY(), 200);

    radioButton->SetX(60);
    radioButton->SetY(160);
    EXPECT_EQ(radioButton->GetX(), 60);
    EXPECT_EQ(radioButton->GetY(), 160);

    radioButton->SetPosition(100, 200, 300, 400);
    EXPECT_EQ(radioButton->GetX(), 100);
    EXPECT_EQ(radioButton->GetY(), 200);
    delete(radioButton);
}


/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_RADIOBUTTON_SIZE_0100
* @tc.name       test radio button size api by normal value
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RadioButtonTest, testRadioButtonSizeNormal, TestSize.Level0){
    UIRadioButton* radioButton = new UIRadioButton("aasd");
    EXPECT_EQ(radioButton->GetWidth(), 56);
    EXPECT_EQ(radioButton->GetHeight(), 56);

    radioButton->SetWidth(90);
    radioButton->SetHeight(60);
    EXPECT_EQ(radioButton->GetWidth(), 90);
    EXPECT_EQ(radioButton->GetHeight(), 60);

    radioButton->SetPosition(100, 200, 300, 400);
    EXPECT_EQ(radioButton->GetWidth(), 300);
    EXPECT_EQ(radioButton->GetHeight(), 400);
    delete(radioButton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_RADIOBUTTON_SIZE_0200
* @tc.name       test radio button size api by abnormal value
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RadioButtonTest, testRadioButtonSizeAbnormal, TestSize.Level0){
    UIRadioButton* radioButton = new UIRadioButton("aasd");
    radioButton->SetWidth(-90);
    radioButton->SetHeight(-60);
    EXPECT_EQ(radioButton->GetWidth(), -90);
    EXPECT_EQ(radioButton->GetHeight(), -60);
    delete(radioButton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_RADIOBUTTON_STATE_0100
* @tc.name       test radio button set state api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RadioButtonTest, testRadioButtonSetState, TestSize.Level0){
    UIRadioButton* radioButton = new UIRadioButton("aasd");
    EXPECT_EQ(radioButton->GetState(), UIRadioButton::UNSELECTED);

    radioButton->SetState(UIRadioButton::SELECTED);
    EXPECT_EQ(radioButton->GetState(), UIRadioButton::SELECTED);

    radioButton->SetState(UIRadioButton::UNSELECTED);
    EXPECT_EQ(radioButton->GetState(), UIRadioButton::UNSELECTED);
    delete(radioButton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_RADIOBUTTON_STYLE_0100
* @tc.name       test radio button style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RadioButtonTest, testRadioButtonStyle, TestSize.Level0){
    UIRadioButton* radioButton = new UIRadioButton("aasd");
    radioButton->SetStyle(STYLE_BACKGROUND_OPA, 0);
    radioButton->SetStyle(STYLE_BACKGROUND_COLOR, 200);
    radioButton->SetStyle(STYLE_BORDER_RADIUS, 100);
    radioButton->SetStyle(STYLE_IMAGE_OPA, 190);

    EXPECT_EQ(radioButton->GetStyle(STYLE_BACKGROUND_OPA), 0);
    EXPECT_EQ(radioButton->GetStyle(STYLE_BACKGROUND_COLOR), 200);
    EXPECT_EQ(radioButton->GetStyle(STYLE_BORDER_RADIUS), 100);
    EXPECT_EQ(radioButton->GetStyle(STYLE_IMAGE_OPA), 190);
    delete(radioButton);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_RADIOBUTTON_EVENT_0100
* @tc.name       test radio button event api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(RadioButtonTest, testRadioButtonEvent, TestSize.Level0){
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    UIRadioButton* radioButton1 = new UIRadioButton("aasd");
    UIRadioButton* radioButton2 = new UIRadioButton("aasd");
    UIRadioButton* radioButton3 = new UIRadioButton("aasd");
    viewGroup->Add(radioButton1);
    viewGroup->Add(radioButton2);
    viewGroup->Add(radioButton3);
    ClickEvent event({ 345, 430 });
    radioButton1->OnClickEvent(event);
    EXPECT_EQ(radioButton1->GetState(), UICheckBox::SELECTED);
    radioButton2->OnClickEvent(event);
    EXPECT_EQ(radioButton1->GetState(), UICheckBox::UNSELECTED);
    EXPECT_EQ(radioButton2->GetState(), UICheckBox::SELECTED);
    EXPECT_EQ(radioButton3->GetState(), UICheckBox::UNSELECTED);
    delete(radioButton1);
    delete(radioButton2);
    delete(radioButton3);
}