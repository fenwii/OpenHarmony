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
#include "acelite_config.h"
#ifdef FEATURE_COMPONENT_VIDEO

#include "panel_view.h"
#include "graphic_config.h"

namespace OHOS {
namespace ACELite {
const char * const PanelView::DEFAULT_PLAY_TIME = "00:00";
const uint16_t PanelView::DEFAULT_VOLUME_VALUE = 50;
const uint16_t PanelView::DEFAULT_PANEL_HEIGHT = 51;
const uint8_t PanelView::SECONDS_PER_MINUTE = 60;
const uint16_t PanelView::MILLIONS_PER_SECOND = 1000;
const uint16_t PanelView::SECONDS_PER_HOUR = 3600;
const uint8_t PanelView::MAX_HOURS = 9;
const int64_t PanelView::MAX_SHOW_TIME = MAX_HOURS * SECONDS_PER_HOUR * MILLIONS_PER_SECOND;
const uint16_t PanelView::UPDATE_CYCLE = 250;
const uint32_t PanelView::UPDATE_CYCLE_MICRO_SECONDS = UPDATE_CYCLE * MILLIONS_PER_SECOND;

PanelView::PanelView()
    : curTimeLabel_(nullptr),
      playImage_(nullptr),
      videoSlider_(nullptr),
      totalTimeLabel_(nullptr),
      mutedImage_(nullptr)
{
}

bool PanelView::InitView()
{
    curTimeLabel_ = new UILabel();
    playImage_ = new UIImageView();
    videoSlider_ = new UISlider();
    totalTimeLabel_ = new UILabel();
    mutedImage_ = new UIImageView();
    if (curTimeLabel_ == nullptr || playImage_ == nullptr || videoSlider_ == nullptr || totalTimeLabel_ == nullptr ||
        mutedImage_ == nullptr) {
        return false;
    }
    /* add to panel & layout */
    Add(playImage_);
    Add(curTimeLabel_);
    Add(videoSlider_);
    Add(totalTimeLabel_);
    Add(mutedImage_);
    LayoutChildren();
    return true;
}


PanelView::~PanelView()
{
    ACE_DELETE(curTimeLabel_);
    ACE_DELETE(playImage_);
    ACE_DELETE(videoSlider_);
    ACE_DELETE(totalTimeLabel_);
    ACE_DELETE(mutedImage_);
}

const UILabel *PanelView::GetCurTimeText() const
{
    return curTimeLabel_;
}

const UIImageView *PanelView::GetVideoPlayImage() const
{
    return playImage_;
}

const UISlider *PanelView::GetVideoSlider() const
{
    return videoSlider_;
}

const UILabel *PanelView::GetVideoTotalTimeText() const
{
    return totalTimeLabel_;
}

const UIImageView *PanelView::GetVideoMutedImage() const
{
    return mutedImage_;
}


void PanelView::SetImageInPanel(
    UIImageView *image,
    int16_t imageWidth,
    int16_t imageHeight,
    const ImageInfo* imageSrc)
{
    if (image == nullptr || imageSrc == nullptr) {
        return;
    }
    image->SetSrc(imageSrc);
    image->SetWidth(imageWidth);
    image->SetHeight(imageHeight);
}

void PanelView::SetTextInPanel(UILabel *label)
{
    if (label == nullptr) {
        return;
    }
    label->SetLineBreakMode(UILabel::LINE_BREAK_ADAPT);
    uint8_t fontSize = 18;
    label->SetFont(DEFAULT_VECTOR_FONT_FILENAME, fontSize);
    label->SetText(DEFAULT_PLAY_TIME);
}

void PanelView::SetVideoSlider()
{
    if (videoSlider_ == nullptr || curTimeLabel_ == nullptr || totalTimeLabel_ == nullptr || playImage_ == nullptr
        || mutedImage_ == nullptr) {
        return;
    }
    const int8_t sliderWidth = 5; // default slider width
    const int8_t knobWidth = 18;  // default knob width
    const int8_t defaultBorderRadius = 0;
    const int8_t knobRadius = 10;
    const int8_t hundred = 100;
    const int8_t margin = 75;
    int16_t visibleHeight = 30;
    const int8_t miniVisibleWidth = 100;
    int16_t visibleWidth = (GetWidth() - (curTimeLabel_->GetWidth()) - (totalTimeLabel_->GetWidth()) -
                            (playImage_->GetWidth()) - (mutedImage_->GetWidth()) - margin);
    if (visibleWidth < miniVisibleWidth) {
        visibleWidth = miniVisibleWidth;
    }
    videoSlider_->SetHeight(visibleHeight);
    videoSlider_->SetWidth(visibleWidth);
    videoSlider_->SetRange(hundred, 0);
    videoSlider_->SetValue(0);
    videoSlider_->SetValidHeight(sliderWidth);
    videoSlider_->SetValidWidth(visibleWidth - knobWidth);
    videoSlider_->SetKnobWidth(knobWidth);
    videoSlider_->SetSliderRadius(defaultBorderRadius, defaultBorderRadius, knobRadius);
    const uint8_t alpha = OPA_OPAQUE;
    /* set videoSlider_ background color */
    videoSlider_->SetBackgroundStyle(STYLE_BACKGROUND_COLOR, Color::White().full);
    videoSlider_->SetBackgroundStyle(STYLE_BACKGROUND_OPA, alpha);
    /* set videoSlider_ selected color */
    videoSlider_->SetForegroundStyle(STYLE_BACKGROUND_COLOR, Color::Green().full);
    videoSlider_->SetForegroundStyle(STYLE_BACKGROUND_OPA, alpha);
}
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_VIDEO