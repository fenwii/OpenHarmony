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

#include "components/ui_abstract_clock.h"

namespace OHOS {
void UIAbstractClock::SetTime24Hour(uint8_t hour, uint8_t minute, uint8_t second)
{
    currentHour_ = hour % ONE_DAY_IN_HOUR;
    currentMinute_ = minute % ONE_HOUR_IN_MINUTE;
    currentSecond_ = second % ONE_MINUTE_IN_SECOND;
    UpdateClock(false);
}

void UIAbstractClock::SetTime12Hour(uint8_t hour, uint8_t minute, uint8_t second, bool am)
{
    SetTime24Hour((hour % HALF_DAY_IN_HOUR) + (am ? 0 : HALF_DAY_IN_HOUR), minute, second);
}

void UIAbstractClock::IncOneSecond()
{
    currentSecond_++;
    currentMinute_ += currentSecond_ / ONE_MINUTE_IN_SECOND;
    currentSecond_ = currentSecond_ % ONE_MINUTE_IN_SECOND;

    currentHour_ += currentMinute_ / ONE_HOUR_IN_MINUTE;
    currentMinute_ = currentMinute_ % ONE_HOUR_IN_MINUTE;
    currentHour_ = currentHour_ % ONE_DAY_IN_HOUR;

    UpdateClock(false);
}

void UIAbstractClock::SetWorkMode(WorkMode newMode)
{
    if (mode_ != newMode) {
        mode_ = newMode;
        Invalidate();
    }
}

void UIAbstractClock::UpdateClock(bool clockInit)
{
    Invalidate();
}
} // namespace OHOS