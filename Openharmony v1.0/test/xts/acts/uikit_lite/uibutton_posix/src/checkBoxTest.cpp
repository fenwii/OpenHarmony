
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
#include "components/ui_checkbox.h"
#include "components/ui_view_group.h"
#include "core/system_booter.h"

using namespace OHOS;
using namespace testing::ext;

class CheckBoxTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_CHECKBOX_POSITION_0100
* @tc.name       test checkbox position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CheckBoxTest, testCheckBoxPosition, TestSize.Level0){
    UICheckBox* checkbox = new UICheckBox();
    EXPECT_EQ(checkbox->GetX(), 0);
    EXPECT_EQ(checkbox->GetY(), 0);

    checkbox->SetPosition(30, 200);
    EXPECT_EQ(checkbox->GetX(), 30);
    EXPECT_EQ(checkbox->GetY(), 200);

    checkbox->SetX(60);
    checkbox->SetY(160);
    EXPECT_EQ(checkbox->GetX(), 60);
    EXPECT_EQ(checkbox->GetY(), 160);

    checkbox->SetPosition(100, 200, 300, 400);
    EXPECT_EQ(checkbox->GetX(), 100);
    EXPECT_EQ(checkbox->GetY(), 200);
    delete(checkbox);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_CHECKBOX_SIZE_0100
* @tc.name       test checkbox size api by normal value
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CheckBoxTest, testCheckBoxSizeNormal, TestSize.Level0){
    UICheckBox* checkbox = new UICheckBox();
    EXPECT_EQ(checkbox->GetWidth(), 56);
    EXPECT_EQ(checkbox->GetHeight(), 56);

    checkbox->SetWidth(90);
    checkbox->SetHeight(60);
    EXPECT_EQ(checkbox->GetWidth(), 90);
    EXPECT_EQ(checkbox->GetHeight(), 60);

    checkbox->SetPosition(100, 200, 300, 400);
    EXPECT_EQ(checkbox->GetWidth(), 300);
    EXPECT_EQ(checkbox->GetHeight(), 400);
    delete(checkbox);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_CHECKBOX_SIZE_0100
* @tc.name       test checkbox size api by abnormal value
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CheckBoxTest, testCheckBoxSizeAbnormal, TestSize.Level0){
    UICheckBox* checkbox = new UICheckBox();
    checkbox->SetWidth(-90);
    checkbox->SetHeight(-60);
    EXPECT_EQ(checkbox->GetWidth(), -90);
    EXPECT_EQ(checkbox->GetHeight(), -60);
    delete(checkbox);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_CHECKBOX_STATE_0100
* @tc.name       test checkbox set state api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CheckBoxTest, testCheckBoxSetState, TestSize.Level0){
    UICheckBox* checkbox = new UICheckBox();
    EXPECT_EQ(checkbox->GetState(), UICheckBox::UNSELECTED);

    checkbox->SetState(UICheckBox::SELECTED);
    EXPECT_EQ(checkbox->GetState(), UICheckBox::SELECTED);

    checkbox->SetState(UICheckBox::UNSELECTED);
    EXPECT_EQ(checkbox->GetState(), UICheckBox::UNSELECTED);
    delete(checkbox);
}


/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_CHECKBOX_STYLE_0100
* @tc.name       test checkbox style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CheckBoxTest, testCheckBoxStyle, TestSize.Level0){
    UICheckBox* checkbox = new UICheckBox();
    checkbox->SetStyle(STYLE_BACKGROUND_OPA, 0);
    checkbox->SetStyle(STYLE_BACKGROUND_COLOR, 200);
    checkbox->SetStyle(STYLE_BORDER_RADIUS, 100);
    checkbox->SetStyle(STYLE_IMAGE_OPA, 190);

    EXPECT_EQ(checkbox->GetStyle(STYLE_BACKGROUND_OPA), 0);
    EXPECT_EQ(checkbox->GetStyle(STYLE_BACKGROUND_COLOR), 200);
    EXPECT_EQ(checkbox->GetStyle(STYLE_BORDER_RADIUS), 100);
    EXPECT_EQ(checkbox->GetStyle(STYLE_IMAGE_OPA), 190);
    delete(checkbox);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_BUTTON_CHECKBOX_EVENT_0100
* @tc.name       test checkbox event api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(CheckBoxTest, testCheckBoxEvent, TestSize.Level0){
    RootView* rootView = RootView::GetInstance();
    UIViewGroup* viewGroup = static_cast<UIViewGroup*>(rootView);
    UICheckBox* checkbox1 = new UICheckBox();
    UICheckBox* checkbox2 = new UICheckBox();
    UICheckBox* checkbox3 = new UICheckBox();
    viewGroup->Add(checkbox1);
    viewGroup->Add(checkbox2);
    viewGroup->Add(checkbox3);
    ClickEvent event({ 345, 430 });
    checkbox1->OnClickEvent(event);
    checkbox2->OnClickEvent(event);
    EXPECT_EQ(checkbox1->GetState(), UICheckBox::SELECTED);
    EXPECT_EQ(checkbox2->GetState(), UICheckBox::SELECTED);
    EXPECT_EQ(checkbox3->GetState(), UICheckBox::UNSELECTED);
    delete(checkbox1);
    delete(checkbox2);
    delete(checkbox3);
}