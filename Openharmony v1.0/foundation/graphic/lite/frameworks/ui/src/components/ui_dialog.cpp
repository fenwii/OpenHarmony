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

#include "components/ui_dialog.h"
#include "common/screen.h"
#include "common/ui_text_language.h"
#include "graphic_log.h"

namespace OHOS {
class UIDialogLabelButton : public UILabelButton {
public:
    virtual void OnClickEvent(const ClickEvent& event)
    {
        if (onClickListener_ != nullptr) {
            onClickListener_->OnClick(*this, event);
        }
        if (parent_ != nullptr) {
            UIDialog* dialog = static_cast<UIDialog*>(parent_->GetParent());
            if (dialog != nullptr) {
                dialog->SetVisible(false);
            }
        }
    }
};

UIDialog::UIDialog()
    : buttonNum_(0),
      title_(nullptr),
      text_(nullptr),
      button1_(nullptr),
      button2_(nullptr),
      button3_(nullptr),
      buttonWidth_(0)
{
    UIViewGroup::SetVisible(false);
    SetStyle(STYLE_BACKGROUND_OPA, OPA_TRANSPARENT);
    uint16_t screenWidth = Screen::GetInstance().GetWidth();
    uint16_t screenHeight = Screen::GetInstance().GetHeight();
    UIViewGroup::SetPosition(0, 0, screenWidth, screenHeight);

    widthMax_ = screenWidth * MAX_WIDTH_PERCENT / 100 - 2 * PADDING;    // there are 2 paddings horizontally
    heightMax_ = screenHeight * MAX_HEIGHT_PERCENT / 100 - 2 * PADDING; // there are 2 paddings horizontally

    Add(&maskLayer_);
    maskLayer_.SetTouchable(true);
    maskLayer_.SetDraggable(true);
    maskLayer_.SetPosition(0, 0, GetWidth(), GetHeight());
    maskLayer_.SetStyle(STYLE_BACKGROUND_COLOR, Color::Black().full);
    maskLayer_.SetStyle(STYLE_BACKGROUND_OPA, 153); // 153 default opa

    Add(&dialogLayer_);
    dialogLayer_.SetStyle(STYLE_BORDER_RADIUS, DIALOG_RADIUS);
    dialogLayer_.SetStyle(STYLE_BACKGROUND_COLOR, Color::Gray().full);
    dialogLayer_.SetStyle(STYLE_BACKGROUND_OPA, 230); // 230 default opa
}

UIDialog::~UIDialog()
{
    if (title_ != nullptr) {
        dialogLayer_.Remove(title_);
        delete title_;
        title_ = nullptr;
    }
    if (text_ != nullptr) {
        dialogLayer_.Remove(text_);
        delete text_;
        text_ = nullptr;
    }
    if (button1_ != nullptr) {
        dialogLayer_.Remove(button1_);
        delete button1_;
        button1_ = nullptr;
    }
    if (button2_ != nullptr) {
        dialogLayer_.Remove(button2_);
        delete button2_;
        button2_ = nullptr;
    }
    if (button3_ != nullptr) {
        dialogLayer_.Remove(button3_);
        delete button3_;
        button3_ = nullptr;
    }
    Remove(&maskLayer_);
    Remove(&dialogLayer_);
}

void UIDialog::SetTitle(const char* title)
{
    if (title == nullptr) {
        return;
    }
    if (title_ == nullptr) {
        title_ = new UILabel();
        title_->SetViewId("dialogTitle");
        dialogLayer_.Add(title_);
    }
    title_->SetText(title);
    title_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    dialogLayer_.Add(title_);

    ReMeasureSize();
    ReLayout();
}

void UIDialog::MeasureTitle()
{
    if (title_ == nullptr) {
        return;
    }
    title_->SetLineBreakMode(UILabel::LINE_BREAK_ADAPT);
    title_->SetFont(DEFAULT_FONT, TITLE_LARGE_FONT_SIZE);
    if (title_->GetTextWidth() > widthMax_) {
        title_->SetFont(DEFAULT_FONT, TITLE_SMALL_FONT_SIZE);
    }
    title_->SetWidth(title_->GetTextWidth());
    title_->SetHeight(title_->GetTextHeight());
    if (title_->GetTextWidth() > widthMax_) {
        title_->SetLineBreakMode(UILabel::LINE_BREAK_ELLIPSIS);
        title_->SetWidth(widthMax_);
    }
}

void UIDialog::SetText(const char* text)
{
    if (text == nullptr) {
        return;
    }
    if (text_ == nullptr) {
        text_ = new UILabel();
        text_->SetViewId("dialogText");
        dialogLayer_.Add(text_);
    }
    text_->SetText(text);

    ReMeasureSize();
    ReLayout();
}

void UIDialog::MeasureText()
{
    if (text_ == nullptr) {
        return;
    }
    text_->SetFont(DEFAULT_FONT, TEXT_FONT_SIZE);
    text_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    dialogLayer_.Add(text_);

    text_->SetLineBreakMode(UILabel::LINE_BREAK_ADAPT);
    uint16_t textWidth = text_->GetTextWidth();
    uint16_t textHeight = text_->GetTextHeight();
    if (textWidth <= widthMax_) {
        text_->SetWidth(textWidth);
        text_->SetHeight(textHeight);
    } else {
        text_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT);
        text_->SetWidth(widthMax_);
        text_->SetLineBreakMode(UILabel::LINE_BREAK_WRAP);
        textHeight = text_->GetTextHeight();
        // If there is no title, there are 3 paddings vertically
        // If there is a title, there are 4 paddings vertically
        uint16_t textHightMax = (title_ == nullptr) ? (heightMax_ - 3 * PADDING - BUTTON_HEIGHT)
                                                    : (heightMax_ - 4 * PADDING - title_->GetHeight() - BUTTON_HEIGHT);
        if (textHeight <= textHightMax) {
            text_->SetHeight(textHeight);
        } else {
            text_->SetHeight(textHightMax);
            text_->SetLineBreakMode(UILabel::LINE_BREAK_ELLIPSIS);
        }
    }
}

void UIDialog::SetButton(DialogButtonType buttonType, const char* text, OnClickListener* listener)
{
    switch (buttonType) {
        case DialogButtonType::BUTTON1:
            if (button1_ == nullptr) {
                button1_ = new UIDialogLabelButton();
                button1_->SetViewId("dialogButton1");
                AddButton(buttonType, button1_, text, listener);
            } else {
                button1_->SetText(text);
                button1_->SetOnClickListener(listener);
            }
            break;
        case DialogButtonType::BUTTON2:
            if (button2_ == nullptr) {
                button2_ = new UIDialogLabelButton();
                button2_->SetViewId("dialogButton2");
                AddButton(buttonType, button2_, text, listener);
            } else {
                button2_->SetText(text);
                button2_->SetOnClickListener(listener);
            }
            break;
        case DialogButtonType::BUTTON3:
            if (button3_ == nullptr) {
                button3_ = new UIDialogLabelButton();
                button3_->SetViewId("dialogButton3");
                AddButton(buttonType, button3_, text, listener);
            } else {
                button3_->SetText(text);
                button3_->SetOnClickListener(listener);
            }
            break;
        default:
            break;
    }
}

void UIDialog::AddButton(DialogButtonType buttonType,
                         UILabelButton* button,
                         const char* text,
                         OnClickListener* listener)
{
    buttonNum_++;

    dialogLayer_.Add(button);
    button->SetDraggable(true);
    button->SetText(text);
    button->SetOnClickListener(listener);
    button->SetFont(DEFAULT_FONT, BUTTON_FONT_SIZE);

    button->SetTextColor(Color::White());
    button->SetStyle(STYLE_BACKGROUND_COLOR, Color::Gray().full);
    button->SetHeight(BUTTON_HEIGHT);

    ReMeasureSize();
    ReLayout();
}

void UIDialog::MeasureButton()
{
    if (buttonNum_ == 0) {
        return;
    }
    uint16_t buttonWidthMin = BUTTON_MIN_WIDTH;
    uint16_t buttonTotalWidthMin = buttonWidthMin * buttonNum_ + (buttonNum_ - 1) * PADDING;
    if (buttonTotalWidthMin >= widthMax_) {
        buttonWidth_ = (widthMax_ - (buttonNum_ - 1) * PADDING) / buttonNum_;
    } else {
        buttonWidth_ = buttonWidthMin;
    }
    if (button1_ != nullptr) {
        button1_->SetWidth(buttonWidth_);
    }
    if (button2_ != nullptr) {
        button2_->SetWidth(buttonWidth_);
    }
    if (button3_ != nullptr) {
        button3_->SetWidth(buttonWidth_);
    }
}

void UIDialog::ReMoveButton()
{
    if (button1_ != nullptr) {
        button1_->LayoutLeftOfParent(PADDING);
        button1_->LayoutBottomOfParent(PADDING);
        if (button2_ != nullptr) {
            button2_->LayoutRightToSibling("dialogButton1", PADDING - 1);
            button2_->LayoutBottomOfParent(PADDING);
        }
    } else {
        if (button2_ != nullptr) {
            button2_->LayoutLeftOfParent(PADDING);
            button2_->LayoutBottomOfParent(PADDING);
        }
    }
    if (button3_ != nullptr) {
        button3_->LayoutRightOfParent(PADDING);
        button3_->LayoutBottomOfParent(PADDING);
    }
}

void UIDialog::ReMeasureSize()
{
    MeasureText();
    MeasureTitle();
    MeasureButton();

    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t num = 0;

    if (title_ != nullptr) {
        uint16_t titleWidth = title_->GetWidth();
        width = MATH_MAX(width, titleWidth);
        height += title_->GetHeight();
        num++;
    }
    if (text_ != nullptr) {
        uint16_t textWidth = text_->GetWidth();
        width = MATH_MAX(width, textWidth);
        height += text_->GetHeight();
        num++;
    }
    if (buttonNum_ != 0) {
        uint16_t buttonTotalWidth = buttonWidth_ * buttonNum_ + (buttonNum_ - 1) * PADDING;
        width = MATH_MAX(width, buttonTotalWidth);
        height += BUTTON_HEIGHT;
        num++;
    }

    if (title_ != nullptr && (title_->GetWidth() != width)) {
        title_->SetWidth(width);
    }
    if (text_ != nullptr && (text_->GetWidth() != width)) {
        text_->SetWidth(width);
    }
    if (buttonNum_ != 0) {
        uint16_t buttonTotalWidth = buttonWidth_ * buttonNum_ + (buttonNum_ - 1) * PADDING;
        if (buttonTotalWidth != width) {
            buttonWidth_ = (width - (buttonNum_ - 1) * PADDING) / buttonNum_;
            if (button1_ != nullptr) {
                button1_->SetWidth(buttonWidth_);
            }
            if (button2_ != nullptr) {
                button2_->SetWidth(buttonWidth_);
            }
            if (button3_ != nullptr) {
                button3_->SetWidth(buttonWidth_);
            }
        }
    }
    uint16_t dialogHeight = height + (num + 1) * PADDING;
    dialogLayer_.SetHeight(dialogHeight);
    dialogLayer_.SetWidth(width + 2 * PADDING); // 2: there are 2 paddings horizontally
}

void UIDialog::ReLayout()
{
    if (title_ != nullptr) {
        title_->LayoutLeftOfParent(PADDING);
        title_->LayoutTopOfParent(PADDING);
        if (text_ != nullptr) {
            text_->LayoutLeftOfParent(PADDING);
            text_->LayoutBottomToSibling("dialogTitle", PADDING);
        }
    } else {
        if (text_ != nullptr) {
            text_->LayoutLeftOfParent(PADDING);
            text_->LayoutTopOfParent(PADDING);
        }
    }
    ReMoveButton();
    dialogLayer_.LayoutCenterOfParent();
}

void UIDialog::SetVisible(bool visible)
{
    UIViewGroup::SetVisible(visible);
    Invalidate();
}
} // namespace OHOS