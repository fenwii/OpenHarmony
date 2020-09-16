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

#include "components/ui_button.h"
#include "common/image.h"
#include "draw/draw_image.h"
#include "draw/draw_rect.h"
#include "imgdecode/cache_manager.h"
#include "style.h"
#include "themes/theme_manager.h"

namespace OHOS {
UIButton::UIButton()
    : defaultImgSrc_(nullptr),
      triggeredImgSrc_(nullptr),
      currentImgSrc_(ButtonImageSrc::BTN_IMAGE_DEFAULT),
      imgX_(0),
      imgY_(0),
      contentWidth_(0),
      contentHeight_(0),
      state_(RELEASED),
      styleState_(RELEASED),
      buttonStyleAllocFlag_(false)
{
    touchable_ = true;
    SetupThemeStyles();
}

UIButton::~UIButton()
{
    if (defaultImgSrc_ != nullptr) {
        delete defaultImgSrc_;
        defaultImgSrc_ = nullptr;
    }

    if (triggeredImgSrc_ != nullptr) {
        delete triggeredImgSrc_;
        triggeredImgSrc_ = nullptr;
    }

    if (buttonStyleAllocFlag_) {
        for (uint8_t i = 0; i < BTN_STATE_NUM; i++) {
            delete buttonStyles_[i];
            buttonStyles_[i] = nullptr;
        }
        buttonStyleAllocFlag_ = false;
    }
}

void UIButton::DrawImg(const Rect& invalidatedArea)
{
    const Image* image = GetCurImageSrc();
    if (image == nullptr) {
        return;
    }

    ImageHeader header = {0};
    image->GetHeader(header);
    Rect coords;
    Rect viewRect = GetContentRect();
    coords.SetLeft(viewRect.GetLeft() + GetImageX());
    coords.SetTop(viewRect.GetTop() + GetImageY());
    coords.SetWidth(header.width);
    coords.SetHeight(header.height);

    Rect trunc(invalidatedArea);
    if (trunc.Intersect(trunc, viewRect)) {
        image->DrawImage(coords, trunc, *buttonStyles_[state_], opaScale_);
    }
}

void UIButton::OnDraw(const Rect& invalidatedArea)
{
    DrawRect::Draw(GetRect(), invalidatedArea, *buttonStyles_[state_]);
    DrawImg(invalidatedArea);
}

void UIButton::SetupThemeStyles()
{
    Theme* theme = ThemeManager::GetInstance().GetCurrent();

    if (theme == nullptr) {
        buttonStyles_[RELEASED] = &(StyleDefault::GetButtonReleasedStyle());
        buttonStyles_[PRESSED] = &(StyleDefault::GetButtonPressedStyle());
        buttonStyles_[INACTIVE] = &(StyleDefault::GetButtonInactivedStyle());
    } else {
        buttonStyles_[RELEASED] = &(theme->GetButtonStyle().released);
        buttonStyles_[PRESSED] = &(theme->GetButtonStyle().pressed);
        buttonStyles_[INACTIVE] = &(theme->GetButtonStyle().inactive);
    }
}

int64_t UIButton::GetStyle(uint8_t key) const
{
    return GetStyleForState(key, styleState_);
}

void UIButton::SetStyle(uint8_t key, int64_t value)
{
    SetStyleForState(key, value, styleState_);
}

int64_t UIButton::GetStyleForState(uint8_t key, ButtonState state) const
{
    if (state < BTN_STATE_NUM) {
        return (buttonStyles_[state])->GetStyle(key);
    }
    return 0;
}

void UIButton::SetStyleForState(uint8_t key, int64_t value, ButtonState state)
{
    if (state < BTN_STATE_NUM) {
        if (!buttonStyleAllocFlag_) {
            for (uint8_t i = 0; i < BTN_STATE_NUM; i++) {
                Style styleSaved = *buttonStyles_[i];
                buttonStyles_[i] = new Style;
                *(buttonStyles_[i]) = styleSaved;
            }
            buttonStyleAllocFlag_ = true;
        }
        buttonStyles_[state]->SetStyle(key, value);
    }
}

void UIButton::OnPressEvent(const PressEvent& event)
{
    currentImgSrc_ = ButtonImageSrc::BTN_IMAGE_TRIGGERED;
    SetState(PRESSED);
    Resize(contentWidth_, contentHeight_);
    Invalidate();
    UIView::OnPressEvent(event);
}

void UIButton::OnReleaseEvent(const ReleaseEvent& event)
{
    currentImgSrc_ = ButtonImageSrc::BTN_IMAGE_DEFAULT;
    SetState(RELEASED);
    Resize(contentWidth_, contentHeight_);
    Invalidate();
    UIView::OnReleaseEvent(event);
}

void UIButton::OnCancelEvent(const CancelEvent& event)
{
    currentImgSrc_ = ButtonImageSrc::BTN_IMAGE_DEFAULT;
    SetState(RELEASED);
    Resize(contentWidth_, contentHeight_);
    Invalidate();
    UIView::OnCancelEvent(event);
}

const Image* UIButton::GetCurImageSrc() const
{
    if (currentImgSrc_ == ButtonImageSrc::BTN_IMAGE_DEFAULT) {
        return defaultImgSrc_;
    } else if (currentImgSrc_ == ButtonImageSrc::BTN_IMAGE_TRIGGERED) {
        return triggeredImgSrc_;
    } else {
        return nullptr;
    }
}

void UIButton::SetImageSrc(const char* defaultImgSrc, const char* triggeredImgSrc)
{
    if (defaultImgSrc_ == nullptr) {
        defaultImgSrc_ = new Image();
    }
    defaultImgSrc_->SetSrc(defaultImgSrc);

    if (triggeredImgSrc_ == nullptr) {
        triggeredImgSrc_ = new Image();
    }
    triggeredImgSrc_->SetSrc(triggeredImgSrc);
}

void UIButton::SetImageSrc(const ImageInfo* defaultImgSrc, const ImageInfo* triggeredImgSrc)
{
    if (defaultImgSrc_ == nullptr) {
        defaultImgSrc_ = new Image();
    }
    defaultImgSrc_->SetSrc(defaultImgSrc);

    if (triggeredImgSrc_ == nullptr) {
        triggeredImgSrc_ = new Image();
    }
    triggeredImgSrc_->SetSrc(triggeredImgSrc);
}

void UIButton::Disable()
{
    SetState(INACTIVE);
    touchable_ = false;
}

void UIButton::Enable()
{
    SetState(RELEASED);
    touchable_ = true;
}

void UIButton::SetState(ButtonState state)
{
    state_ = state;
    Invalidate();
}
} // namespace OHOS