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

#include "components/ui_label_button.h"
#include "common/typed_text.h"
#include "draw/draw_label.h"
#include "font/ui_font.h"

namespace OHOS {
UILabelButton::UILabelButton() : offset_({ 0, 0 })
{
    labelStyle_ = StyleDefault::GetDefaultStyle();
    if (UIFont::GetInstance()->IsVectorFont()) {
        labelButtonText_.SetFont(DEFAULT_VECTOR_FONT_FILENAME, 18); // 18: means font size
    } else {
        labelButtonText_.SetFontId(style_->font_);
    }
    labelButtonText_.SetAlign(TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_CENTER);
}

void UILabelButton::OnDraw(const Rect& invalidatedArea)
{
    UIButton::OnDraw(invalidatedArea);

    Rect textRect = GetContentRect();
    textRect.SetLeft(textRect.GetLeft() + offset_.x);
    textRect.SetTop(textRect.GetTop() + offset_.y);
    labelButtonText_.ReMeasureTextSize(textRect, labelStyle_);
    labelButtonText_.OnDraw(invalidatedArea, GetOrigRect(), textRect, 0, labelStyle_, Text::TEXT_ELLIPSIS_END_INV);
}
}  // namespace OHOS
