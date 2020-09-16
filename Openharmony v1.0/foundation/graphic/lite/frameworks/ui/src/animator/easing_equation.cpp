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

#include "graphic_math.h"
#include "animator/easing_equation.h"

namespace OHOS {
double EasingEquation::overshoot_ = 1.7; // The empirical value commonly used in easing equation

void EasingEquation::SetBackOvershoot(double overshoot)
{
    if (overshoot >= OVERSHOOT_MIN && overshoot <= OVERSHOOT_MAX) {
        overshoot_ = overshoot;
    }
}

int16_t EasingEquation::BackEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        double t = -(static_cast<double>(curTime) / durationTime);
        double x = -t * t * ((overshoot_ + 1) * t + overshoot_);
        pos = static_cast<int16_t>((x * (static_cast<int32_t>(endPos) - startPos)) + startPos);
    }

    return pos;
}

int16_t EasingEquation::BackEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        double t = static_cast<double>(curTime) / durationTime;
        t -= 1.0;
        double x = t * t * ((overshoot_ + 1) * t + overshoot_) + 1;
        pos = static_cast<int16_t>((x * (static_cast<int32_t>(endPos) - startPos)) + startPos);
    }

    return pos;
}

int16_t EasingEquation::BackEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos;
    uint16_t halfTime = durationTime >> 1;
    int16_t halfStep = (endPos >> 1) + (startPos >> 1);
    if (curTime < halfTime) {
        pos = BackEaseIn(startPos, halfStep, curTime, halfTime);
    } else {
        pos = BackEaseOut(halfStep, endPos, curTime - halfTime, halfTime);
    }

    return pos;
}

/* 1 - sqrt(1 - t^2) */
int16_t EasingEquation::CircEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int32_t t = (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;
        uint32_t x = INTERPOLATION_RANGE - Sqrt(INTERPOLATION_RANGE_SQUARE - t * t);
        pos = static_cast<int16_t>(((x * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

/* sqrt(1 - (1 - t)^2) */
int16_t EasingEquation::CircEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int32_t t = INTERPOLATION_RANGE - (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;
        uint32_t x = Sqrt(INTERPOLATION_RANGE_SQUARE - t * t);
        pos = static_cast<int16_t>(((x * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

int16_t EasingEquation::CircEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos;
    uint16_t halfTime = durationTime >> 1;
    int16_t halfStep = (endPos >> 1) + (startPos >> 1);
    if (curTime < halfTime) {
        pos = CircEaseIn(startPos, halfStep, curTime, halfTime);
    } else {
        pos = CircEaseOut(halfStep, endPos, curTime - halfTime, halfTime);
    }

    return pos;
}

/* t^3 */
int16_t EasingEquation::CubicEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int32_t t = (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;
        int16_t x = (t * t * t) >> (INTERPOLATION_RANGE_OFFSET << 1);
        pos = static_cast<int16_t>(((x * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

/* 1 - (1 - t)^3 */
int16_t EasingEquation::CubicEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int32_t t = (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;
        t = INTERPOLATION_RANGE - t;
        int16_t x = INTERPOLATION_RANGE - ((t * t * t) >> (INTERPOLATION_RANGE_OFFSET << 1));
        pos = static_cast<int16_t>(((x * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

int16_t EasingEquation::CubicEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos;
    uint16_t halfTime = durationTime >> 1;
    int16_t halfStep = (endPos >> 1) + (startPos >> 1);
    if (curTime < halfTime) {
        pos = CubicEaseIn(startPos, halfStep, curTime, halfTime);
    } else {
        pos = CubicEaseOut(halfStep, endPos, curTime - halfTime, halfTime);
    }

    return pos;
}

int16_t EasingEquation::LinearEaseNone(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int32_t t = (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;
        pos = static_cast<int16_t>(((t * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

/* t^2 */
int16_t EasingEquation::QuadEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int32_t t = (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;
        int16_t x = (t * t) >> INTERPOLATION_RANGE_OFFSET;
        pos = static_cast<int16_t>(((x * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

/* 1 - (1 - t)^2 */
int16_t EasingEquation::QuadEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int32_t t = INTERPOLATION_RANGE - (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;
        int16_t x = INTERPOLATION_RANGE - ((t * t) >> INTERPOLATION_RANGE_OFFSET);
        pos = static_cast<int16_t>(((x * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

int16_t EasingEquation::QuadEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos;
    uint16_t halfTime = durationTime >> 1;
    int16_t halfStep = (endPos >> 1) + (startPos >> 1);
    if (curTime < halfTime) {
        pos = QuadEaseIn(startPos, halfStep, curTime, halfTime);
    } else {
        pos = QuadEaseOut(halfStep, endPos, curTime - halfTime, halfTime);
    }

    return pos;
}

/* t^5 */
int16_t EasingEquation::QuintEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int64_t t = (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;

        /* 4: the fourth power of t */
        int16_t x = (t * t * t * t * t) >> (INTERPOLATION_RANGE_OFFSET * 4);
        pos = static_cast<int16_t>(((x * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

/* 1 - (1 - t)^5 */
int16_t EasingEquation::QuintEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int64_t t = (curTime << INTERPOLATION_RANGE_OFFSET) / durationTime;
        t = INTERPOLATION_RANGE - t;

        /* 4: the fourth power of t */
        int16_t x = INTERPOLATION_RANGE - ((t * t * t * t * t) >> (INTERPOLATION_RANGE_OFFSET * 4));
        pos = static_cast<int16_t>(((x * (static_cast<int32_t>(endPos) - startPos)) >> INTERPOLATION_RANGE_OFFSET) +
            startPos);
    }

    return pos;
}

int16_t EasingEquation::QuintEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos;
    uint16_t halfTime = durationTime >> 1;
    int16_t halfStep = (endPos >> 1) + (startPos >> 1);
    if (curTime < halfTime) {
        pos = QuintEaseIn(startPos, halfStep, curTime, halfTime);
    } else {
        pos = QuintEaseOut(halfStep, endPos, curTime - halfTime, halfTime);
    }

    return pos;
}

int16_t EasingEquation::SineEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int16_t t = (curTime * QUARTER_IN_DEGREE) / durationTime - QUARTER_IN_DEGREE;
        float x = Sin(t) + 1;
        pos = static_cast<int16_t>(x * (endPos - startPos)) + startPos;
    }

    return pos;
}

int16_t EasingEquation::SineEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos = endPos;
    if (curTime < durationTime) {
        int16_t t = (curTime * QUARTER_IN_DEGREE) / durationTime;
        float x = Sin(t);
        pos = static_cast<int16_t>(x * (endPos - startPos)) + startPos;
    }

    return pos;
}

int16_t EasingEquation::SineEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)
{
    int16_t pos;
    uint16_t halfTime = durationTime >> 1;
    int16_t halfStep = (endPos >> 1) + (startPos >> 1);
    if (curTime < halfTime) {
        pos = SineEaseIn(startPos, halfStep, curTime, halfTime);
    } else {
        pos = SineEaseOut(halfStep, endPos, curTime - halfTime, halfTime);
    }

    return pos;
}
}