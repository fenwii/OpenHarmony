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

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ui_abstract_clock.h
 *
 * @brief Declares the <b>UIAbstractClock</b> class that provides the functions related to clocks.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef UI_ABSTRACT_CLOCK_H
#define UI_ABSTRACT_CLOCK_H

#include "components/ui_view_group.h"

namespace OHOS {
/**
 * @brief An abstract class that contains functions for converting units of time (hour, minute, and second),
 *        setting and obtaining the time.
 *
 * @since 1.0
 * @version 1.0
 */
class UIAbstractClock : public UIViewGroup {
public:
    /**
     * @brief Represents 60 seconds per minute.
     */
    static constexpr uint8_t ONE_MINUTE_IN_SECOND = 60;

    /**
     * @brief Represents 60 minutes per hour.
     */
    static constexpr uint8_t ONE_HOUR_IN_MINUTE = 60;

    /**
     * @brief Represents 24 hours per day.
     */
    static constexpr uint8_t ONE_DAY_IN_HOUR = 24;

    /**
     * @brief Represents 12 hours every half day.
     */
    static constexpr uint8_t HALF_DAY_IN_HOUR = 12;

    /**
     * @brief A default constructor used to create a <b>UIAbstractClock</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIAbstractClock() : currentHour_(0), currentMinute_(0), currentSecond_(0), mode_(WorkMode::NORMAL) {}

    /**
     * @brief A constructor used to create a <b>UIAbstractClock</b> instance with
     *        time elements (hour, minute and second).
     *
     * @param hour Indicates the hour.
     * @param minute Indicates the minute.
     * @param second Indicates the second.
     * @since 1.0
     * @version 1.0
     */
    UIAbstractClock(uint8_t hour, uint8_t minute, uint8_t second)
        : currentHour_(hour), currentMinute_(minute), currentSecond_(second) {}

    /**
     * @brief A destructor used to delete the <b>UIAbstractClock</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIAbstractClock() {}

    /**
     * @brief Obtains the view type.
     *
     * @return Returns <b>UI_ABSTRACT_CLOCK</b>, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_ABSTRACT_CLOCK;
    }

    /**
     * @brief Sets the time in 24-hour format.
     *
     * @param hour Indicates the hour to set, within [0, 23] after the modulo operation.
     * @param minute Indicates the minute to set, within [0, 59] after the modulo operation.
     * @param second Indicates the second to set, within [0, 59] after the modulo operation.
     * @since 1.0
     * @version 1.0
     */
    void SetTime24Hour(uint8_t hour, uint8_t minute, uint8_t second);

    /**
     * @brief Sets the time in 12-hour format.
     *
     * @param hour Indicates the hour to set, within [0, 11] after the modulo operation.
     * @param minute Indicates the minute to set, within [0, 59] after the modulo operation.
     * @param second Indicates the second to set, within [0, 59] after the modulo operation.
     * @param am Specifies whether it is in the morning. <b>true</b> indicates that it is in the morning,
     *           and <b> false</b> indicates that it is in the afternoon.
     * @since 1.0
     * @version 1.0
     */
    void SetTime12Hour(uint8_t hour, uint8_t minute, uint8_t second, bool am);

    /**
     * @brief Obtains the current number of hours.
     *
     * @return Returns the current number of hours.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetCurrentHour() const
    {
        return currentHour_;
    }

    /**
     * @brief Obtains the current number of minutes.
     *
     * @return Returns the current number of minutes.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetCurrentMinute() const
    {
        return currentMinute_;
    }

    /**
     * @brief Obtains the current number of seconds.
     *
     * @return Returns the current number of seconds.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetCurrentSecond() const
    {
        return currentSecond_;
    }

    /**
     * @brief Increases the time by one second.
     *
     * @since 1.0
     * @version 1.0
     */
    void IncOneSecond();

    /**
     * @brief Updates this clock.
     *
     * @param clockInit Specifies whether it is the first initialization. <b>true</b> indicates it is the first
     *                  initialization, and <b> false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    virtual void UpdateClock(bool clockInit);

    /**
     * @brief Enumerates the working modes of this clock.
     */
    enum WorkMode {
        /** Always on (drawing not updated) */
        ALWAYS_ON,
        /** Normal (drawing updated with the time change) */
        NORMAL,
    };

    /**
     * @brief Sets the working mode for this clock.
     *
     * @param newMode Indicates the working mode to set. For details, see {@link WorkMode}.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetWorkMode(WorkMode newMode);

    /**
     * @brief Obtains the working mode of this clock.
     *
     * @return Returns the working mode, as defined in {@link WorkMode}.
     * @since 1.0
     * @version 1.0
     */
    virtual WorkMode GetWorkMode() const
    {
        return mode_;
    }

protected:
    /**
     * @brief Represents the current number of hours.
     */
    uint8_t currentHour_;

    /**
     * @brief Represents the current number of minutes.
     */
    uint8_t currentMinute_;

    /**
     * @brief Represents the current number of seconds.
     */
    uint8_t currentSecond_;

    /**
     * @brief Represents the current working mode of this clock.
     */
    WorkMode mode_;
};
} // namespace OHOS
#endif // UI_ABSTRACT_CLOCK_H
