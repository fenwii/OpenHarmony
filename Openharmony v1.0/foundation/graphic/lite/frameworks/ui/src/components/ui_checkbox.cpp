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

#include "common/image.h"
#include "components/ui_checkbox.h"
#include "default_resource/check_box_res.h"
#include "draw/draw_image.h"
#include "draw/draw_rect.h"
#include "imgdecode/cache_manager.h"

namespace OHOS {
UICheckBox::UICheckBox()
    : state_(UNSELECTED), onStateChangeListener_(nullptr)
{
    touchable_ = true;
    style_ = &(StyleDefault::GetBackgroundTransparentStyle());
    image_[UNSELECTED].SetSrc(GetCheckBoxOffInfo());
    image_[SELECTED].SetSrc(GetCheckBoxOnInfo());
    ImageHeader header = { 0 };
    image_[UNSELECTED].GetHeader(header);
    Resize(header.width, header.height);
}

UICheckBox::~UICheckBox()
{
}

void UICheckBox::SetState(UICheckBoxState state)
{
    if (state != state_) {
        state_ = state;
        if (onStateChangeListener_ != nullptr) {
            onStateChangeListener_->OnChange(state);
        }
        Invalidate();
    }
}

void UICheckBox::ReverseState()
{
    state_ = (state_ == SELECTED) ? UNSELECTED : SELECTED;
}

void UICheckBox::OnClickEvent(const ClickEvent& event)
{
    ReverseState();
    Invalidate();
    UIView::OnClickEvent(event);
}

void UICheckBox::SetImages(const char* selectedImageSrc, const char* unselectedImageSrc)
{
    image_[SELECTED].SetSrc(selectedImageSrc);
    image_[UNSELECTED].SetSrc(unselectedImageSrc);
}

void UICheckBox::SetImages(const ImageInfo* selectedImageSrc, const ImageInfo* unselectedImageSrc)
{
    image_[SELECTED].SetSrc(selectedImageSrc);
    image_[UNSELECTED].SetSrc(unselectedImageSrc);
}

void UICheckBox::OnDraw(const Rect& invalidatedArea)
{
    ImageHeader header = {0};
    image_[state_].GetHeader(header);
    int16_t imgWidth = header.width;
    int16_t imgHeight = header.height;

    Rect coords = GetContentRect();
    coords.SetWidth(imgWidth);
    coords.SetHeight(imgHeight);

    DrawRect::Draw(GetRect(), invalidatedArea, *style_);

    Rect trunc = invalidatedArea;
    Rect contentRect = GetContentRect();
    if (trunc.Intersect(trunc, contentRect)) {
        image_[state_].DrawImage(coords, trunc, *style_, opaScale_);
    }
}
} // namespace OHOS
