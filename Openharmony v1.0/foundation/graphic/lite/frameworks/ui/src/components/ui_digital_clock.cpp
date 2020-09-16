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

#include "components/ui_digital_clock.h"
#include <cstdio>
#include "components/ui_view_group.h"
#include "font/ui_font.h"
#include "graphic_log.h"
#include "securec.h"

namespace OHOS {
UIDigitalClock::UIDigitalClock()
    : displayMode_(DISPLAY_24_HOUR), leadingZero_(true), color_(Color::White()),
      prevHour_(0), prevMinute_(0), prevSecond_(0), verticalShow_(false)
{
    for (uint8_t i = 0; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].SetAlign(TEXT_ALIGNMENT_LEFT);
        timeLabels_[i].SetFontId(style_->font_);
        timeLabels_[i].SetStyle(STYLE_TEXT_COLOR, color_.full);
        timeLabels_[i].SetLineBreakMode(UILabel::LINE_BREAK_ADAPT);
        timeLabels_[i].SetStyle(STYLE_BACKGROUND_OPA, OPA_TRANSPARENT);
        Add(&timeLabels_[i]);
    }
    style_ = &(StyleDefault::GetBackgroundTransparentStyle());
}

void UIDigitalClock::DisplayLeadingZero(bool displayLeadingZero)
{
    leadingZero_ = displayLeadingZero;
    UpdateClock(false);
}

void UIDigitalClock::SetOpacity(uint8_t opacity)
{
    opaScale_ = opacity;
    for (uint8_t i = 0; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].SetStyle(STYLE_TEXT_OPA, opacity);
    }
    RefreshTime();
}

uint8_t UIDigitalClock::GetOpacity() const
{
    return opaScale_;
}

void UIDigitalClock::SetFontId(uint8_t fontId)
{
    SetStyle(STYLE_TEXT_FONT, fontId);
    for (uint8_t i = 0; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].SetFontId(fontId);
    }
    UpdateClock(false);
}

void UIDigitalClock::SetFont(const char* name, uint8_t size)
{
    for (uint8_t i = 0; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].SetFont(name, size);
    }
    UpdateClock(false);
}

void UIDigitalClock::SetColor(ColorType color)
{
    color_ = color;
    for (uint8_t i = 0; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].SetStyle(STYLE_TEXT_COLOR, color.full);
    }
    RefreshTime();
}

void UIDigitalClock::TimeElementRefresh()
{
    if (currentHour_ != prevHour_) {
        prevHour_ = currentHour_;
        timeLabels_[HOUR_ELEMENT].Invalidate();
    }

    if (currentMinute_ != prevMinute_) {
        prevMinute_ = currentMinute_;
        timeLabels_[MINUTE_ELEMENT].Invalidate();
    }

    if (currentSecond_ != prevSecond_) {
        prevSecond_ = currentSecond_;
        timeLabels_[SECOND_ELEMENT].Invalidate();
    }
}

void UIDigitalClock::RefreshTime()
{
    for (uint8_t i = 0; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].Invalidate();
    }
}

void UIDigitalClock::UpdateClock(bool clockInit)
{
    char buf[TIME_ELEMENT_COUNT][BUFFER_SIZE] = {{ 0 }};
    const char* formatWithColon = leadingZero_ ? "%02d:" : "%d:";
    const char* formatWithoutColon = leadingZero_ ? "%02d" : "%d";
    const char* format = verticalShow_ ? formatWithoutColon : formatWithColon;
    const char* formatForMinute = verticalShow_ ? "%02d" : "%02d:";
    switch (displayMode_) {
        case DISPLAY_24_HOUR_NO_SECONDS: {
            if (sprintf_s(buf[HOUR_ELEMENT], BUFFER_SIZE, format, currentHour_) < 0) {
                return;
            }
            if (sprintf_s(buf[MINUTE_ELEMENT], BUFFER_SIZE, "%02d", currentMinute_) < 0) {
                return;
            }
            break;
        }
        case DISPLAY_12_HOUR_NO_SECONDS: {
            if (sprintf_s(buf[HOUR_ELEMENT], BUFFER_SIZE, format, currentHour_ % HALF_DAY_IN_HOUR) < 0) {
                return;
            }
            if (sprintf_s(buf[MINUTE_ELEMENT], BUFFER_SIZE, "%02d", currentMinute_) < 0) {
                return;
            }
            break;
        }
        case DISPLAY_12_HOUR: {
            if (sprintf_s(buf[HOUR_ELEMENT], BUFFER_SIZE, format, currentHour_ % HALF_DAY_IN_HOUR) < 0) {
                return;
            }
            if (sprintf_s(buf[MINUTE_ELEMENT], BUFFER_SIZE, formatForMinute, currentMinute_) < 0) {
                return;
            }
            if (sprintf_s(buf[SECOND_ELEMENT], BUFFER_SIZE, "%02d", currentSecond_) < 0) {
                return;
            }
            break;
        }
        case DISPLAY_24_HOUR: {
            if (sprintf_s(buf[HOUR_ELEMENT], BUFFER_SIZE, format, currentHour_) < 0) {
                return;
            }
            if (sprintf_s(buf[MINUTE_ELEMENT], BUFFER_SIZE, formatForMinute, currentMinute_) < 0) {
                return;
            }
            if (sprintf_s(buf[SECOND_ELEMENT], BUFFER_SIZE, "%02d", currentSecond_) < 0) {
                return;
            }
            break;
        }
        default: {
            break;
        }
    }
    SetTimeLabels(buf);
}

void UIDigitalClock::SetTimeLabels(const char buf[TIME_ELEMENT_COUNT][BUFFER_SIZE])
{
    for (uint8_t i = 0; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].SetText(buf[i]);
    }

    SetTimeLabelsPosition();
    TimeElementRefresh();
}

void UIDigitalClock::SetHorizontal()
{
    uint16_t totalWidth = timeLabels_[HOUR_ELEMENT].GetWidth() +
                         timeLabels_[MINUTE_ELEMENT].GetWidth() + timeLabels_[SECOND_ELEMENT].GetWidth();
    UITextLanguageAlignment align = timeLabels_[HOUR_ELEMENT].GetHorAlign();
    int16_t x = 0;
    Rect rect = GetContentRect();
    if (align == TEXT_ALIGNMENT_CENTER) {
        x = (rect.GetWidth() >> 1) - (totalWidth >> 1);
    } else if (align == TEXT_ALIGNMENT_RIGHT) {
        x = rect.GetRight() - totalWidth;
    }
    timeLabels_[HOUR_ELEMENT].SetPosition(x, 0);
    int16_t width = timeLabels_[HOUR_ELEMENT].GetWidth();
    for (uint8_t i = 1; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].SetPosition(x + width, 0);
        width += timeLabels_[i].GetWidth();
    }
}

void UIDigitalClock::SetTimeLabelsPosition()
{
    if (verticalShow_) {
        SetVertical();
    } else {
        SetHorizontal();
    }
}

void UIDigitalClock::SetVertical()
{
    uint16_t fontHeight = timeLabels_[HOUR_ELEMENT].GetHeight();
    timeLabels_[HOUR_ELEMENT].SetPosition(0, 0);
    uint16_t y = fontHeight;
    for (uint8_t i = 1; i < TIME_ELEMENT_COUNT; i++) {
        timeLabels_[i].SetPosition(0, y);
        y += fontHeight;
    }
}
}
