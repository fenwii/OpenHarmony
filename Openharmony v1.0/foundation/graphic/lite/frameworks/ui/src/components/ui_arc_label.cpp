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

#include "components/ui_arc_label.h"
#include "common/typed_text.h"
#include "draw/draw_label.h"
#include "draw/draw_rect.h"
#include "font/ui_font.h"
#include "themes/theme_manager.h"

namespace OHOS {
UIArcLabel::UIArcLabel()
    : needRefresh_(false), textSize_ { 0, 0 }, radius_(0), startAngle_(0), endAngle_(0), arcCenter_({ 0, 0 }),
      orientation_(TextOrientation::INSIDE), arcTextInfo_ { 0 }
{
    Theme* theme = ThemeManager::GetInstance().GetCurrent();
    style_ = (theme != nullptr) ? &(theme->GetLabelStyle()) : &(StyleDefault::GetLabelStyle());

    if (UIFont::GetInstance()->IsVectorFont()) {
        arcLabelText_.SetFont(DEFAULT_VECTOR_FONT_FILENAME, 18); // 18: means font size
    } else {
        arcLabelText_.SetFontId(style_->font_);
    }
}

UIArcLabel::~UIArcLabel()
{
}

void UIArcLabel::SetText(const char* text)
{
    if (text == nullptr) {
        return;
    }
    arcLabelText_.SetText(text);
    if (arcLabelText_.IsNeedRefresh()) {
        RefreshArcLabel();
    }
}

const char* UIArcLabel::GetText() const
{
    return arcLabelText_.GetText();
}

void UIArcLabel::SetAlign(UITextLanguageAlignment horizontalAlign)
{
    arcLabelText_.SetAlign(horizontalAlign, TEXT_ALIGNMENT_TOP);
    if (arcLabelText_.IsNeedRefresh()) {
        RefreshArcLabel();
    }
}

UITextLanguageAlignment UIArcLabel::GetHorAlign() const
{
    return arcLabelText_.GetHorAlign();
}

UITextLanguageDirect UIArcLabel::GetDirect()
{
    return arcLabelText_.GetDirect();
}

void UIArcLabel::SetFontId(uint8_t fontId)
{
    arcLabelText_.SetFontId(fontId);
    if (arcLabelText_.IsNeedRefresh()) {
        RefreshArcLabel();
    }
}

uint8_t UIArcLabel::GetFontId() const
{
    return arcLabelText_.GetFontId();
}

void UIArcLabel::SetFont(const char* name, uint8_t size)
{
    if (name == nullptr) {
        return;
    }
    arcLabelText_.SetFont(name, size);
    if (arcLabelText_.IsNeedRefresh()) {
        RefreshArcLabel();
    }
}

void UIArcLabel::OnDraw(const Rect& invalidatedArea)
{
    const char* text = arcLabelText_.GetText();
    if (text == nullptr || radius_ == 0) {
        return;
    }
    UIFont::GetInstance()->SetCurrentFontId(arcLabelText_.GetFontId());
    Rect trunc = invalidatedArea;
    DrawRect::Draw(GetRect(), trunc, *style_);

    Rect coords = GetContentRect();
    if (trunc.Intersect(trunc, coords)) {
        DrawArcText(trunc);
    }
}

void UIArcLabel::DrawArcText(const Rect& mask)
{
    OpacityType opa;
    if (opaScale_ == OPA_OPAQUE) {
        opa = style_->textOpa_;
    } else {
        opa = (static_cast<uint16_t>(style_->textOpa_) * opaScale_) >> 8;  // 8: opacity scale
    }
    Point center;
    center.x = arcTextInfo_.arcCenter.x + GetRect().GetX();
    center.y = arcTextInfo_.arcCenter.y + GetRect().GetY();
    DrawLabel::DrawArcText(mask, arcLabelText_.GetText(), center, arcLabelText_.GetFontId(),
        arcTextInfo_, orientation_, *style_, opa);
}

void UIArcLabel::RefreshArcLabel()
{
    Invalidate();
    if (!needRefresh_) {
        needRefresh_ = true;
        AddMeasureView();
    }
}

void UIArcLabel::ReMeasure()
{
    if (!needRefresh_) {
        return;
    }
    needRefresh_ = false;
    UIFont::GetInstance()->SetCurrentFontId(arcLabelText_.GetFontId());

    MeasureArcTextInfo();
    Rect textRect;
    TypedText::GetArcTextRect(textRect, arcLabelText_.GetText(), arcCenter_, style_->letterSpace_,
        orientation_, arcTextInfo_);
    int16_t arcTextWidth = textRect.GetWidth();
    int16_t arcTextHeight = textRect.GetHeight();

    SetPosition(textRect.GetX(), textRect.GetY());
    Resize(arcTextWidth, arcTextHeight);
    arcTextInfo_.arcCenter.x = arcCenter_.x - GetX();
    arcTextInfo_.arcCenter.y = arcCenter_.y - GetY();
    textSize_.x = arcTextWidth;
    textSize_.y = arcTextHeight;
    Invalidate();
}

void UIArcLabel::MeasureArcTextInfo()
{
    const char* text = arcLabelText_.GetText();
    if (text == nullptr) {
        return;
    }
    uint16_t letterHeight = UIFont::GetInstance()->GetHeight();
    arcTextInfo_.radius = ((orientation_ == TextOrientation::INSIDE) ? radius_ : (radius_ - letterHeight));
    if (arcTextInfo_.radius == 0) {
        return;
    }

    uint16_t arcAngle;
    if (startAngle_ < endAngle_) {
        arcAngle = endAngle_ - startAngle_;
        arcTextInfo_.direct = TEXT_DIRECT_LTR;  // Clockwise
        arcLabelText_.SetDirect(TEXT_DIRECT_LTR);
    } else {
        arcAngle = startAngle_ - endAngle_;
        arcTextInfo_.direct = TEXT_DIRECT_RTL;  // Counterclockwise
        arcLabelText_.SetDirect(TEXT_DIRECT_RTL);
    }
    uint16_t maxLength = static_cast<uint16_t>((UI_PI * radius_ * arcAngle) / SEMICIRCLE_IN_DEGREE);
    arcTextInfo_.lineStart = 0;
    arcTextInfo_.lineEnd = TypedText::GetNextLine(&text[arcTextInfo_.lineStart], style_->letterSpace_, maxLength);
    arcTextInfo_.startAngle = startAngle_;
    uint16_t actLength = TypedText::GetTextWidth(&text[arcTextInfo_.lineStart],
        arcTextInfo_.lineEnd - arcTextInfo_.lineStart, style_->letterSpace_);
    if (arcLabelText_.GetHorAlign() != TEXT_ALIGNMENT_LEFT && actLength < maxLength) {
        uint16_t gapLength = maxLength - actLength;
        if (arcLabelText_.GetHorAlign() == TEXT_ALIGNMENT_CENTER) {
            gapLength = gapLength >> 1;
        }
        if (arcTextInfo_.direct == TEXT_DIRECT_LTR) {
            arcTextInfo_.startAngle += (SEMICIRCLE_IN_DEGREE * gapLength) / (UI_PI * arcTextInfo_.radius);
        } else {
            arcTextInfo_.startAngle += CIRCLE_IN_DEGREE -
                (SEMICIRCLE_IN_DEGREE * gapLength) / (UI_PI * arcTextInfo_.radius);
        }
    }
    arcTextInfo_.startAngle %= CIRCLE_IN_DEGREE;
}
} // namespace OHOS