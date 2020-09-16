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

#include "components/text_adapter.h"
#include <cstdio>
#include "components/ui_label.h"
#include "securec.h"

namespace OHOS {
bool TextFormatter::Format(int16_t value, char* outText, uint16_t textLen)
{
    if (sprintf_s(outText, textLen, "%d", value) < 0) {
        return false;
    }
    return true;
}

TextAdapter::TextAdapter()
    : fontName_(nullptr),
      fontSize_(0),
      width_(0),
      height_(0),
      direct_(UITextLanguageDirect::TEXT_DIRECT_LTR),
      lineBreakMode_(UILabel::LINE_BREAK_ADAPT),
      dataMode_(DYNAMIC_TEXT_MODE),
      integerTextStart_(0),
      integerTextEnd_(0),
      clickListener_(nullptr),
      formatter_(nullptr)
{
    style_ = StyleDefault::GetBackgroundTransparentStyle();
    fontId_ = style_.font_;
}

TextAdapter::~TextAdapter()
{
    ClearDynamicText();
    if (fontName_ != nullptr) {
        UIFree(fontName_);
        fontName_ = nullptr;
    }
}

void TextAdapter::SetFont(const char* name, uint8_t size)
{
    Text::SetFont(name, size, fontName_, fontSize_);
}

UIView* TextAdapter::GetView(UIView* inView, int16_t index)
{
    UILabel* newView = nullptr;

    switch (dataMode_) {
        case DYNAMIC_TEXT_MODE:
            newView = GetDynamicText(inView, index);
            break;
        case CONTINUOUS_INTEGER_MODE:
            newView = GetIntegerText(inView, index);
            break;
        default:
            break;
    }

    if (newView == nullptr) {
        return nullptr;
    }
    newView->SetLineBreakMode(lineBreakMode_);
    newView->SetAlign(TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_CENTER);
    if (width_) {
        newView->SetWidth(width_);
    }
    if (height_) {
        newView->SetHeight(height_);
    }
    newView->SetViewIndex(index);
    newView->SetStyle(style_);
    newView->GetHeight();
    if (clickListener_) {
        newView->SetOnClickListener(clickListener_);
        newView->SetTouchable(true);
    }
    return newView;
}

UILabel* TextAdapter::GetDynamicText(UIView* inView, int16_t index)
{
    if (dynamicText_.IsEmpty() || index > dynamicText_.Size() - 1 || index < 0) {
        return nullptr;
    }

    ListNode<const char*>* node = dynamicText_.Begin();
    for (uint16_t i = 0; i < index; i++) {
        node = node->next_;
    }
    UILabel* newView = nullptr;
    if (inView == nullptr) {
        newView = new UILabel();
    } else {
        newView = static_cast<UILabel*>(inView);
    }

    if (newView != nullptr) {
        newView->SetText(node->data_);
        if (fontName_ == nullptr) {
            newView->SetFontId(fontId_);
        } else {
            newView->SetFont(fontName_, fontSize_);
        }
        newView->SetDirect(direct_);
    }
    return newView;
}

UILabel* TextAdapter::GetIntegerText(UIView* inView, int16_t index)
{
    if ((index < 0) || ((integerTextEnd_ - integerTextStart_) < index)) {
        return nullptr;
    }
    UILabel* newView = nullptr;
    if (inView == nullptr) {
        newView = new UILabel();
    } else {
        newView = static_cast<UILabel*>(inView);
    }

    if (newView != nullptr) {
        char buf[BUF_LEN] = {0};
        if (formatter_ != nullptr) {
            if (!formatter_->Format(integerTextStart_ + index, buf, BUF_LEN)) {
                if (inView == nullptr) {
                    delete newView;
                    newView = nullptr;
                }
                return nullptr;
            }
        } else {
            if (sprintf_s(buf, sizeof(buf), "%02d", integerTextStart_ + index) < 0) {
                if (inView == nullptr) {
                    delete newView;
                    newView = nullptr;
                }
                return nullptr;
            }
        }

        buf[BUF_LEN - 1] = '\0';
        newView->SetText(buf);
        if (fontName_ == nullptr) {
            newView->SetFontId(fontId_);
        } else {
            newView->SetFont(fontName_, fontSize_);
        }
        newView->SetDirect(direct_);
    }
    return newView;
}

void TextAdapter::ClearDynamicText()
{
    ListNode<const char*>* node = dynamicText_.Begin();
    while (node != dynamicText_.End()) {
        if (node->data_) {
            UIFree(reinterpret_cast<void*>(const_cast<char*>(node->data_)));
            node->data_ = nullptr;
        }
        node = node->next_;
    }
    dynamicText_.Clear();
}

void TextAdapter::SetData(List<const char*>* data)
{
    if (data == nullptr) {
        return;
    }
    if (!dynamicText_.IsEmpty()) {
        ClearDynamicText();
    }
    ListNode<const char*>* node = data->Begin();
    while (node != data->End()) {
        uint32_t len = strlen(node->data_);
        char* stringData = static_cast<char*>(UIMalloc(len + 1));
        if (stringData == nullptr) {
            return;
        }
        if (memcpy_s(stringData, len + 1, node->data_, len) != EOK) {
            UIFree(reinterpret_cast<void*>(stringData));
            stringData = nullptr;
            return;
        }
        stringData[len] = '\0';
        dynamicText_.PushBack(stringData);
        node = node->next_;
    }
    dataMode_ = DYNAMIC_TEXT_MODE;
}

void TextAdapter::SetData(int16_t start, int16_t end)
{
    if (start <= end) {
        integerTextStart_ = start;
        integerTextEnd_ = end;
        dataMode_ = CONTINUOUS_INTEGER_MODE;
    }
}

uint16_t TextAdapter::GetCount()
{
    switch (dataMode_) {
        case DYNAMIC_TEXT_MODE:
            return dynamicText_.Size();
        case CONTINUOUS_INTEGER_MODE:
            if (integerTextStart_ <= integerTextEnd_) {
                return (integerTextEnd_ - integerTextStart_ + 1);
            }
            break;
        default:
            return 0;
    }
    return 0;
}
} // namespace OHOS