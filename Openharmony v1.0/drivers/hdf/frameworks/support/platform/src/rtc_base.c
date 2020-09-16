/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "hdf_log.h"
#include "rtc_base.h"

#define HDF_LOG_TAG rtc_base

uint8_t RtcGetMonthDays(const uint8_t isLeapYear, const uint8_t month)
{
    uint8_t days;
    uint8_t oddMonth;

    if (IS_INVALID_MONTH(month) || (isLeapYear > RTC_TRUE)) {
        return 0;
    }

    if (RTC_FEBRUARY == month) {
        days = RTC_TWO_MONTH_DAY + isLeapYear;
    } else {
        oddMonth = (month > RTC_AUGUST) ? (month - RTC_UNIT_DIFF) : month;
        days = (oddMonth & RTC_ODD_MONTH_MASK) ? RTC_GREAT_MONTH_DAY : RTC_SMALL_MONTH_DAY;
    }
    return days;
}

uint8_t RtcIsInvalidDay(const uint8_t day, const uint8_t month, const uint16_t year)
{
    uint8_t MaxDay;
    MaxDay = RtcGetMonthDays(IS_LEAP_YEAR(year), month);

    return ((day == 0) || (day > MaxDay)) ? RTC_TRUE : RTC_FALSE;
}

uint8_t RtcIsInvalid(const struct RtcTime *time)
{
    if (time == NULL) {
        HDF_LOGE("RtcIsInvalid: time null");
        return RTC_FALSE;
    }

    return (IS_INVALID_YEAR(time->year) || IS_INVALID_MONTH(time->month) ||
        (RtcIsInvalidDay(time->day, time->month, time->year) == RTC_TRUE) ||
        IS_INVALID_HOUR(time->hour) || IS_INVALID_MIN(time->minute) ||
        IS_INVALID_SECOND(time->second) || IS_INVALID_MS(time->millisecond));
}

uint8_t RtcGetWeekDay(const struct RtcTime *time)
{
    uint32_t days;
    int8_t month;
    uint16_t year;

    if ((time == NULL) || IS_INVALID_MONTH(time->month) || IS_INVALID_YEAR(time->year) ||
        (RtcIsInvalidDay(time->day, time->month, time->year) == RTC_TRUE)) {
        HDF_LOGE("RtcGetWeekDay: time invalid");
        return RTC_FALSE;
    }

    days = time->day - RTC_UNIT_DIFF;
    month = time->month;
    while (--month >= RTC_JANUARY) {
        days += RtcGetMonthDays(IS_LEAP_YEAR(time->year), month);
    }

    year = time->year;
    while (--year >= RTC_BEGIN_YEAR) {
        days += RTC_YEAR_DAYS(year);
    }

    return ((RTC_BEGIN_WEEKDAY + days - RTC_UNIT_DIFF) % RTC_MAX_WEEKDAY + RTC_UNIT_DIFF);
}

uint64_t RtcTimeToTimestamp(const struct RtcTime *time)
{
    uint64_t seconds;
    uint32_t days;
    uint16_t year;
    int8_t month;

    if (time == NULL) {
        HDF_LOGE("RtcTimeToTimestamp: time null");
        return RTC_FALSE;
    }
    HDF_LOGD("RtcToTimestamp:year-month-day hour:min:second ms %04u-%02u-%02u %02u:%02u:%02u .%03u",
        time->year, time->month, time->day, time->hour, time->minute, time->second, time->millisecond);
    if (RtcIsInvalid(time) == RTC_TRUE) {
        HDF_LOGE("RtcTimeToTimestamp: time invalid");
        return 0;
    }

    seconds = ((uint64_t)time->hour * RTC_MAX_MINUTE + time->minute) * RTC_MAX_SECOND + time->second;
    days = time->day - RTC_UNIT_DIFF;
    month = time->month - RTC_UNIT_DIFF;
    year = time->year;

    while (--month >= 0) {
        days += RtcGetMonthDays(IS_LEAP_YEAR(time->year), month);
    }

    while (--year >= RTC_BEGIN_YEAR) {
        days += RTC_YEAR_DAYS(year);
    }

    seconds += days * RTC_DAY_SECONDS;
    return seconds;
}

void TimestampToRtcTime(struct RtcTime *time, const uint64_t seconds)
{
    uint32_t daySeconds = (uint32_t)(seconds % RTC_DAY_SECONDS);
    uint32_t days = (uint32_t)(seconds / RTC_DAY_SECONDS);

    if (time == NULL) {
        HDF_LOGE("TimestampToRtcTime: rtc null!");
        return;
    }

    time->year = RTC_BEGIN_YEAR;
    while (days >= RTC_YEAR_DAYS(time->year)) {
        days -= RTC_YEAR_DAYS(time->year);
        time->year++;
    }

    time->month = 0;
    while (days >= RtcGetMonthDays(IS_LEAP_YEAR(time->year), time->month)) {
        days -= RtcGetMonthDays(IS_LEAP_YEAR(time->year), time->month);
        time->month++;
    }

    time->day = days;
    time->second = daySeconds % RTC_MAX_SECOND;
    time->minute = (daySeconds % RTC_HOUR_SECONDS) / RTC_MAX_MINUTE;
    time->hour = daySeconds / RTC_HOUR_SECONDS;

    time->month += RTC_UNIT_DIFF;
    time->day += RTC_UNIT_DIFF;
    time->weekday = RtcGetWeekDay(time);
    HDF_LOGD("TimestampToRtc:year-month-day weekday hour:min:second ms %04u-%02u-%02u %u %02u:%02u:%02u .%03u",
        time->year, time->month, time->day, time->weekday, time->hour, time->minute, time->second, time->millisecond);
}
