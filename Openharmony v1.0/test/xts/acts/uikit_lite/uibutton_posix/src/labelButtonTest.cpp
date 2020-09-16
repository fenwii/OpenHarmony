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
#include "components/ui_label_button.h"
#include "font/ui_font.h"
#include "ui_text_language.h"

using namespace OHOS;
using namespace testing::ext;

class LabelButtonTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_LABELBUTTON_BABELBUTTON_SETTEXT_0100
* @tc.name       test label button set text api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(LabelButtonTest, testLabelButtonSetText, TestSize.Level0) {
    const char* text = "abc";
    UILabelButton* labelBtn = new UILabelButton();
    labelBtn->SetText(text);
    EXPECT_EQ(strcmp(labelBtn->GetText(), text), 0);
    delete(labelBtn);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LABELBUTTON_BABELBUTTON_SETLABELPOSITION_0100
* @tc.name       test label button set label position api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(LabelButtonTest, testLabelButtonSetLabelPosition, TestSize.Level0) {
    UILabelButton* labelBtn = new UILabelButton();
    labelBtn->SetLablePosition(10, 20);
    EXPECT_EQ(labelBtn->GetLabelPosition().x, 10);
    EXPECT_EQ(labelBtn->GetLabelPosition().y, 20);
    delete(labelBtn);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LABELBUTTON_BABELBUTTON_SETALIGN_0100
* @tc.name       test label button set align api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(LabelButtonTest, testLabelButtonSetAlign, TestSize.Level0) {
    UILabelButton* labelBtn = new UILabelButton();
    labelBtn->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_RIGHT);
    EXPECT_EQ(labelBtn->GetAlign(), UITextLanguageAlignment::TEXT_ALIGNMENT_RIGHT);
    delete(labelBtn);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LABELBUTTON_BABELBUTTON_SETDIRECT_0100
* @tc.name       test label button set direct api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(LabelButtonTest, testLabelButtonSetDirect, TestSize.Level0) {
    UILabelButton* labelBtn = new UILabelButton();
    labelBtn->SetDirect(UITextLanguageDirect::TEXT_DIRECT_RTL);
    EXPECT_EQ(labelBtn->GetDirect(), UITextLanguageDirect::TEXT_DIRECT_RTL);
    delete(labelBtn);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LABELBUTTON_BABELBUTTON_SETFONT_0100
* @tc.name       test label button set font api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(LabelButtonTest, testLabelButtonSetFont, TestSize.Level0) {
    UILabelButton* labelBtn = new UILabelButton();
    UITextLanguageFontId expectFontId = UITextLanguageFontId::F_HYQIHEI_65S_30_4;
    labelBtn->SetFontId(expectFontId);
    EXPECT_EQ(labelBtn->GetFontId(), expectFontId);
    UITextLanguageFontId expectFontId2 = UITextLanguageFontId::F_HYQIHEI_65S_38_4;
    labelBtn->SetFont("HYQiHei-65S", 38);
    EXPECT_EQ(labelBtn->GetFontId(), expectFontId2);
    delete(labelBtn);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_LABELBUTTON_BABELBUTTON_SETLABELSTYLE_0100
* @tc.name       test label button set label style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(LabelButtonTest, testLabelButtonSetLabelStyle, TestSize.Level0) {
    UILabelButton* labelBtn = new UILabelButton();
    Style &style = labelBtn->GetLabelStyle();
    style.rect.opacity = 0;
    labelBtn->SetLabelStyle(style);
    EXPECT_EQ(labelBtn->GetLabelStyle().rect.opacity, 0);
    delete(labelBtn);
}