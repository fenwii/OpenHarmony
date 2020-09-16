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

#include "components/ui_analog_clock.h"
#include "components/ui_image_view.h"
#include "draw/draw_image.h"
#include "draw/draw_line.h"
#include "draw/draw_rect.h"
#include "graphic_log.h"
#include "imgdecode/cache_manager.h"
#include "style.h"
#include "themes/theme.h"

namespace OHOS {
UIAnalogClock::UIAnalogClock()
{
    touchable_ = true;
}

void UIAnalogClock::SetHandImage(HandType type, const UIImageView& img, Point position, Point center)
{
    Hand *hand = nullptr;
    if (type == HandType::HOUR_HAND) {
        hand = &hourHand_;
    } else if (type == HandType::MINUTE_HAND) {
        hand = &minuteHand_;
    } else {
        hand = &secondHand_;
    }

    hand->center_ = center;
    hand->position_ = position;
    hand->initAngle_ = 0;
    hand->preAngle_ = 0;
    hand->nextAngle_ = 0;
    hand->drawtype_ = DrawType::DRAW_IMAGE;

    if (img.GetSrcType() == IMG_SRC_FILE) {
        CacheEntry entry;
        RetCode ret = CacheManager::GetInstance().Open(img.GetPath(), *style_, entry);
        if (ret != RetCode::OK) {
            return;
        }
        hand->imageInfo_ = entry.GetImageInfo();
    } else {
        hand->imageInfo_ = *(img.GetImageInfo());
    }
}

void UIAnalogClock::SetHandLine(HandType type, Point position, Point center, ColorType color,
    uint16_t width, uint16_t height, OpacityType opacity)
{
    Hand* hand = nullptr;
    if (type == HandType::HOUR_HAND) {
        hand = &hourHand_;
    } else if (type == HandType::MINUTE_HAND) {
        hand = &minuteHand_;
    } else {
        hand = &secondHand_;
    }

    hand->color_ = color;
    hand->height_ = height;
    hand->width_ = width;
    hand->position_ = position;
    hand->center_ = center;
    hand->opacity_ = opacity;
    hand->initAngle_ = 0;
    hand->preAngle_ = 0;
    hand->nextAngle_ = 0;
    hand->drawtype_ = DrawType::DRAW_LINE;
}

Point UIAnalogClock::GetHandRotateCenter(HandType type) const
{
    if (type == HandType::HOUR_HAND) {
        return hourHand_.center_;
    } else if (type == HandType::MINUTE_HAND) {
        return minuteHand_.center_;
    } else {
        return secondHand_.center_;
    }
}

Point UIAnalogClock::GetHandPosition(HandType type) const
{
    if (type == HandType::HOUR_HAND) {
        return hourHand_.position_;
    } else if (type == HandType::MINUTE_HAND) {
        return minuteHand_.position_;
    } else {
        return secondHand_.position_;
    }
}

uint16_t UIAnalogClock::GetHandInitAngle(HandType type) const
{
    if (type == HandType::HOUR_HAND) {
        return hourHand_.initAngle_;
    } else if (type == HandType::MINUTE_HAND) {
        return minuteHand_.initAngle_;
    } else {
        return secondHand_.initAngle_;
    }
}

uint16_t UIAnalogClock::GetHandCurrentAngle(HandType type) const
{
    if (type == HandType::HOUR_HAND) {
        return hourHand_.nextAngle_;
    } else if (type == HandType::MINUTE_HAND) {
        return minuteHand_.nextAngle_;
    } else {
        return secondHand_.nextAngle_;
    }
}

void UIAnalogClock::SetInitTime24Hour(uint8_t hour, uint8_t minute, uint8_t second)
{
    currentHour_ = hour % ONE_DAY_IN_HOUR;
    currentMinute_ = minute % ONE_HOUR_IN_MINUTE;
    currentSecond_ = second % ONE_MINUTE_IN_SECOND;

    hourHand_.initAngle_ = ConvertHandValueToAngle(currentHour_,
        HALF_DAY_IN_HOUR, currentMinute_, ONE_HOUR_IN_MINUTE);
    hourHand_.preAngle_ = hourHand_.initAngle_;
    hourHand_.nextAngle_ = hourHand_.initAngle_;

    minuteHand_.initAngle_ = ConvertHandValueToAngle(currentMinute_,
        ONE_HOUR_IN_MINUTE, currentSecond_, ONE_MINUTE_IN_SECOND);
    minuteHand_.preAngle_ = minuteHand_.initAngle_;
    minuteHand_.nextAngle_ = minuteHand_.initAngle_;

    secondHand_.initAngle_ = ConvertHandValueToAngle(currentSecond_, ONE_MINUTE_IN_SECOND);
    secondHand_.preAngle_ = secondHand_.initAngle_;
    secondHand_.nextAngle_ = secondHand_.initAngle_;

    UpdateClock(true);
}

void UIAnalogClock::SetInitTime12Hour(uint8_t hour, uint8_t minute, uint8_t second, bool am)
{
    SetInitTime24Hour((hour % HALF_DAY_IN_HOUR) + (am ? 0 : HALF_DAY_IN_HOUR), minute, second);
}

uint16_t UIAnalogClock::ConvertHandValueToAngle(uint8_t handValue, uint8_t range,
    uint8_t secondHandValue, uint8_t ratio) const
{
    if (range == 0 || ratio == 0) {
        GRAPHIC_LOGW("UIAnalogClock::ConvertHandValueToAngle Invalid range or ratio\n");
        return 0;
    }
    /*
     * Example: calculate the angle of hour hand
     * Assume that the time is 5: 30, then range is 12, radio is 60
     * angle is [(5 * 60  + 30) / (12 * 60)] * 360
     */
    uint32_t degree = (static_cast<uint16_t>(handValue) * ratio + secondHandValue);
    degree = static_cast<uint32_t>(CIRCLE_IN_DEGREE * degree / (static_cast<uint16_t>(range) * ratio));

    return static_cast<uint16_t>(degree % CIRCLE_IN_DEGREE);
}

uint16_t UIAnalogClock::ConvertHandValueToAngle(uint8_t handValue, uint8_t range) const
{
    if (range == 0) {
        GRAPHIC_LOGW("UIAnalogClock::ConvertHandValueToAngle Invalid range or ratio\n");
        return 0;
    }
    /*
     * Example: calculate the angle of second hand without millisecond handle
     * Assume that the time is 5:30:30, then range is 60
     * angle is (30 / 60) * 360
     */
    return (static_cast<uint16_t>(handValue) * CIRCLE_IN_DEGREE / range);
}

void UIAnalogClock::UpdateClock(bool clockInit)
{
    Invalidate();
    hourHand_.nextAngle_ = ConvertHandValueToAngle(currentHour_,
        HALF_DAY_IN_HOUR, currentMinute_, ONE_HOUR_IN_MINUTE);

    minuteHand_.nextAngle_ = ConvertHandValueToAngle(currentMinute_,
        ONE_HOUR_IN_MINUTE, currentSecond_, ONE_MINUTE_IN_SECOND);

    secondHand_.nextAngle_ = ConvertHandValueToAngle(currentSecond_, ONE_MINUTE_IN_SECOND);

    Rect rect = GetRect();
    CalculateRedrawArea(rect, hourHand_, clockInit);
    CalculateRedrawArea(rect, minuteHand_, clockInit);
    if (GetWorkMode() == WorkMode::NORMAL) {
        CalculateRedrawArea(rect, secondHand_, clockInit);
    }
}

void UIAnalogClock::OnDraw(const Rect& invalidatedArea)
{
    DrawRect::Draw(GetRect(), invalidatedArea, *style_);
}

void UIAnalogClock::OnPostDraw(const Rect& invalidatedArea)
{
    Rect current = GetOrigRect();
    DrawHand(current, invalidatedArea, hourHand_);
    DrawHand(current, invalidatedArea, minuteHand_);
    if (GetWorkMode() == WorkMode::NORMAL) {
        DrawHand(current, invalidatedArea, secondHand_);
    }
}

void UIAnalogClock::SetPosition(int16_t x, int16_t y)
{
    UIViewGroup::SetPosition(x, y);
    UpdateClock(true);
}

void UIAnalogClock::SetPosition(int16_t x, int16_t y, int16_t width, int16_t height)
{
    UIViewGroup::SetPosition(x, y, width, height);
    UpdateClock(true);
}

void UIAnalogClock::CalculateRedrawArea(const Rect& current, Hand& hand, bool clockInit)
{
    /*
     * Use the current image as an independent rectangular area
     * to calculate the coordinate conversion coefficient.
     */
    int16_t imgWidth = hand.imageInfo_.header.width;
    int16_t imgHeight = hand.imageInfo_.header.height;

    int16_t left = hand.position_.x + current.GetLeft();
    int16_t right = left + imgWidth;
    int16_t top = hand.position_.y + current.GetTop();
    int16_t bottom = top + imgHeight;
    Rect imgRect(left, top, right, bottom);
    TransformMap backwardMap(imgRect);
    Vector2<int16_t> pivot;
    pivot.x_ = hand.center_.x;
    pivot.y_ = hand.center_.y;

    /* Rotate the specified angle,  */
    backwardMap.Rotate(hand.nextAngle_ - hand.initAngle_, pivot);
    Rect redraw = hand.target_;
    hand.target_ = backwardMap.GetBoxRect();
    hand.trans_ = backwardMap;
    hand.preAngle_ = hand.nextAngle_;
    if (clockInit == false) {
        /* Prevent old images from being residued */
        redraw.Join(redraw, hand.target_);
        InvalidateRect(redraw);
    }
}

void UIAnalogClock::DrawHand(const Rect& current, const Rect& invalidatedArea, Hand& hand)
{
    if (hand.drawtype_ == DrawType::DRAW_IMAGE) {
        DrawHandImage(current, invalidatedArea, hand);
    } else {
        DrawHandLine(invalidatedArea, hand);
    }
}

void UIAnalogClock::DrawHandImage(const Rect& current, const Rect& invalidatedArea, Hand& hand)
{
    uint8_t pxSize = DrawUtils::GetPxSizeByColorMode(hand.imageInfo_.header.colorMode);
    TransformDataInfo imageTranDataInfo = {
        hand.imageInfo_.header, hand.imageInfo_.data, pxSize,
        BlurLevel::LEVEL0, TransformAlgorithm::BILINEAR
    };
    DrawUtils::GetInstance()->DrawTransform(invalidatedArea, { 0, 0 },
        Color::Black(), hand.trans_, imageTranDataInfo);
}

void UIAnalogClock::DrawHandLine(const Rect& invalidatedArea, Hand& hand)
{
    float sinma = Sin(hand.nextAngle_);
    float cosma = Sin(hand.nextAngle_ + THREE_QUARTER_IN_DEGREE);
    int32_t handLength = hand.height_;
    Rect rect = GetRect();
    Point start;
    Point end;
    Point curCenter;
    curCenter.x = hand.position_.x + hand.center_.x + rect.GetLeft();
    curCenter.y = hand.position_.y + hand.center_.y + rect.GetTop();

    int32_t startToCenterLength = hand.center_.y;

    int32_t xPointLength = static_cast<int32_t>(startToCenterLength * sinma);
    int32_t yPointLength = static_cast<int32_t>(startToCenterLength * cosma);

    start.x = xPointLength + curCenter.x;
    start.y = yPointLength + curCenter.y;

    /*
     * @ startToCenterLength: means the length between StartPoint and CenterPoint.
     * @ handlength: means the hand height.
     * @ xlength: means X-axis length relative to the center point
     * @ ylength: means Y-axis length relative to the center point
     */
    int32_t xlength = static_cast<int32_t>((startToCenterLength - handLength) * sinma);
    int32_t ylength = static_cast<int32_t>((startToCenterLength - handLength) * cosma);
    end.x = xlength + curCenter.x;
    end.y = ylength + curCenter.y;

    DrawLine::Draw(start, end, invalidatedArea, hand.width_, hand.color_, hand.opacity_);
}

void UIAnalogClock::SetWorkMode(WorkMode newMode)
{
    WorkMode oldMode = mode_;

    if (oldMode != newMode) {
        /*
         * After entering the alwayson mode, all child controls are no longer drawn,
         * making the simplest analog clock.
         */
        isViewGroup_ = (newMode == ALWAYS_ON) ? false : true;
        mode_ = newMode;
        Invalidate();
    }
}
} // namespace OHOS
