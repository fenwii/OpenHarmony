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

#include "text_component.h"
#include <stdlib.h>
#include <string.h>
#include "ace_log.h"
#include "font/ui_font_header.h"
#include "key_parser.h"
#include "keys.h"

using namespace OHOS;

namespace OHOS {
namespace ACELite {
TextComponent::TextComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager),
      uiLabel_(nullptr),
      fontSize_(DEFAULT_FONT_SIZE),
      fontFamily_(nullptr),
      textValue_(nullptr),
      overflowMode_(UILabel::LINE_BREAK_CLIP)
{
    SetComponentName(K_TEXT);
}

bool TextComponent::CreateNativeViews()
{
    uiLabel_ = new UILabel();
    if (uiLabel_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create native label failed");
        return false;
    }
    /* set default text OverFlow clip */
    uiLabel_->SetLineBreakMode(overflowMode_);
    return CopyFontFamily(fontFamily_, DEFAULT_FONT_FAMILY);
}

void TextComponent::ReleaseNativeViews()
{
    if (uiLabel_) {
        delete uiLabel_;
        uiLabel_ = nullptr;
    }
    ACE_FREE(textValue_);
    ACE_FREE(fontFamily_);
}

inline UIView *TextComponent::GetComponentRootView() const
{
    return uiLabel_;
}

UILabel *TextComponent::GetUILabelView() const
{
    return uiLabel_;
}

bool TextComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    switch (attrKeyId) {
        case K_VALUE: {
            ACE_FREE(textValue_);
            textValue_ = MallocStringOf(attrValue);
            break;
        }
        case K_SCROLLAMOUNT: {
            int16_t speed = IntegerOf(attrValue);
            uiLabel_->SetRollSpeed(speed);
            break;
        }
        default: {
            return false;
        }
    }

    return true;
}

bool TextComponent::ApplyPrivateStyle(const AppStyleItem *styleItem)
{
    switch (GetStylePropNameId(styleItem)) {
        case K_COLOR:
            SetTextColor(*uiLabel_, styleItem);
            break;
        case K_LETTER_SPACING:
            SetTextLetterSpace(*uiLabel_, styleItem);
            break;
        case K_TEXT_ALIGN:
            SetTextAlign(*uiLabel_, styleItem);
            break;
        case K_FONT_SIZE:
            SetTextSize(styleItem);
            break;
        case K_FONT_FAMILY:
            if (!IsStyleValueTypeString(styleItem)) {
                HILOG_ERROR(HILOG_MODULE_ACE, "text Family style value type is invalid!");
                return false;
            }
            CopyFontFamily(fontFamily_, GetStyleStrValue(styleItem));
            break;
        case K_TEXT_OVERFLOW:
            SetTextOverflow(*uiLabel_, styleItem);
            break;
        case K_LINE_HEIGHT:
            SetTextLineHeight(*uiLabel_, styleItem);
            break;
        default:
            return false;
    }

    return true;
}

void TextComponent::SetTextLetterSpace(UILabel &label, const AppStyleItem *styleItem) const
{
    label.SetStyle(STYLE_LETTER_SPACE, (int16_t)GetStylePixelValue(styleItem));
}

void TextComponent::SetTextLineHeight(UILabel &label, const AppStyleItem *styleItem) const
{
    label.SetStyle(STYLE_LINE_SPACE, (int16_t)GetStylePixelValue(styleItem));
}

void TextComponent::SetTextOverflow(UILabel &label, const AppStyleItem *styleItem)
{
    if (!IsStyleValueTypeString(styleItem)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "text overflow style value is invalid!");
        return;
    }
    // set ui label text OverFlow, LINE_BREAK_CLIP, TEXT_OVERFLOW_ELLIPSIS and TEXT_OVERFLOW_EXPAND are support
    uint16_t propNameId = KeyParser::ParseKeyId(GetStyleStrValue(styleItem), GetStyleStrValueLen(styleItem));

    switch (propNameId) {
        case K_CLIP:
            overflowMode_ = UILabel::LINE_BREAK_CLIP;
            break;
        case K_ELLIPSIS:
            overflowMode_ = UILabel::LINE_BREAK_ELLIPSIS;
            break;
        case K_EXPAND:
            overflowMode_ = UILabel::LINE_BREAK_ADAPT;
            break;
        case K_BREAK:
            overflowMode_ = UILabel::LINE_BREAK_WRAP;
            break;
        default:
            HILOG_WARN(HILOG_MODULE_ACE, "TextOverFlow id=%d is invalid, using default instead", propNameId);
            break;
    }
    label.SetLineBreakMode(overflowMode_);
}

void TextComponent::SetTextColor(UILabel &label, const AppStyleItem *styleItem) const
{
    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    if (GetStyleColorValue(styleItem, color, alpha)) {
        label.SetStyle(STYLE_TEXT_COLOR, GetRGBColor(color).full);
        label.SetStyle(STYLE_TEXT_OPA, alpha);
    }
}

void TextComponent::SetTextSize(const AppStyleItem *styleItem)
{
    fontSize_ = GetStylePixelValue(styleItem);
}

void TextComponent::PostRender()
{
    if (GetHeight() < 0 && GetWidth() < 0) {
        /* component height & width adjust text context when not set text height & text width */
        uiLabel_->SetLineBreakMode(UILabel::LINE_BREAK_ADAPT);
    } else if (GetHeight() < 0 && GetWidth() >= 0) {
        /* component height adjust text context when set width not set text height */
        uiLabel_->SetLineBreakMode(UILabel::LINE_BREAK_WRAP);
    } else if (GetHeight() >= 0 && GetWidth() < 0) {
        /* component width adjust text context when not set text width */
        uiLabel_->SetLineBreakMode(UILabel::LINE_BREAK_STRETCH);
    }
    if (textValue_ != nullptr && fontFamily_ != nullptr) {
        uiLabel_->SetFont(fontFamily_, fontSize_);
        uiLabel_->SetText(textValue_);
    }
}

/* watchcallback update text context*/
void TextComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    if ((uiLabel_ == nullptr) || !updateResult || !KeyParser::IsKeyValid(attrKeyId)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "text component post update check args failed");
        return;
    }
    switch (attrKeyId) {
        case K_VALUE:
            if (textValue_ != nullptr) {
                uiLabel_->SetText(textValue_);
            }
            break;
        case K_FONT_SIZE:
        case K_FONT_FAMILY:
            if (fontFamily_ != nullptr) {
                uiLabel_->SetFont(fontFamily_, fontSize_);
            }
            break;
        default:
            break;
    }
}

void TextComponent::SetTextAlign(UILabel &label, const AppStyleItem *styleItem) const
{
    if (!IsStyleValueTypeString(styleItem)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "text text align style value is invalid!");
        return;
    }
    // set ui label text align, ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER are support.
    const char * const stylePropValue = GetStyleStrValue(styleItem);
    uint16_t alignId = KeyParser::ParseKeyId(stylePropValue, GetStyleStrValueLen(styleItem));
    UITextLanguageAlignment align = UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT;
    switch (alignId) {
        case K_LEFT:
            align = UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT;
            break;
        case K_RIGHT:
            align = UITextLanguageAlignment::TEXT_ALIGNMENT_RIGHT;
            break;
        case K_CENTER:
            align = UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER;
            break;
        default:
            HILOG_WARN(HILOG_MODULE_ACE, "text textAlign style value =%s is invalid, using default instead",
                       stylePropValue);
            break;
    }
    label.SetAlign(align);
}
} // namespace ACELite
} // namespace OHOS
