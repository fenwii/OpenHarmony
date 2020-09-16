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
 * @file ui_digital_clock.h
 *
 * @brief Declares a digital clock.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_DIGITAL_CLOCK_H
#define GRAPHIC_LITE_UI_DIGITAL_CLOCK_H

#include "components/ui_abstract_clock.h"
#include "components/ui_label.h"
#include "color.h"

namespace OHOS {
/**
 * @brief Displays time digitally.
 *
 * @see UIDigitalClock
 * @since 1.0
 * @version 1.0
 */
class UIDigitalClock : public UIAbstractClock {
public:
    /**
     * @brief A default constructor used to create a <b>UIDigitalClock</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIDigitalClock();

    /**
     * @brief A destructor used to delete the <b>UIDigitalClock</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIDigitalClock() {}

    /**
     * @brief Obtains the view type.
     *
     * @return Returns <b>UI_DIGITAL_CLOCK</b>, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_DIGITAL_CLOCK;
    }

    /**
     * @brief Sets the dynamic font ID for this digital clock.
     *
     * @param fontId Indicates the dynamic font ID to set.
     * @since 1.0
     * @version 1.0
     */
    void SetFontId(uint8_t fontId);

    /**
     * @brief Sets the dynamic font for this digital clock.
     *
     * @param name Indicates the pointer to the font name.
     * @param size Indicates the font size to set.
     * @since 1.0
     * @version 1.0
     */
    void SetFont(const char* name, uint8_t size);

    /**
     * @brief Sets the font color for this digital clock.
     *
     * @param color Indicates the front color to set.
     * @since 1.0
     * @version 1.0
     */
    void SetColor(ColorType color);

    /**
     * @brief Enumerates the display modes of this digital clock.
     */
    enum DisplayMode {
        /** 12-hour format, without seconds */
        DISPLAY_12_HOUR_NO_SECONDS,
        /** 24-hour format, without seconds */
        DISPLAY_24_HOUR_NO_SECONDS,
        /** 12-hour format */
        DISPLAY_12_HOUR,
        /** 24-hour format */
        DISPLAY_24_HOUR
    };

    /**
     * @brief Enumerates the time elements of this digital clock.
     */
    enum TimeElement {
        /** Clock */
        HOUR_ELEMENT,
        /** Minute */
        MINUTE_ELEMENT,
        /** Second */
        SECOND_ELEMENT
    };

    /**
     * @brief Sets the display mode for this digital clock.
     *
     * @param dm Indicates the display mode to set.
     * @since 1.0
     * @version 1.0
     */
    void SetDisplayMode(DisplayMode dm)
    {
        displayMode_ = dm;
        UpdateClock(false);
    }

    /**
     * @brief Obtains the display mode of this digital clock.
     *
     * @return Returns the display mode of this digital clock.
     * @since 1.0
     * @version 1.0
     */
    DisplayMode GetDisplayMode() const
    {
        return displayMode_;
    }

    /**
     * @brief Sets whether to add <b>0</b> before the hour of this digital clock.
     *
     * @param displayLeadingZero Specifies whether to add <b>0</b> before the hour of this digital clock.
     *                           <b>true</b> indicates that <b>0</b> is added, and <b>false</b> indicates
     *                           the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void DisplayLeadingZero(bool displayLeadingZero);

    /**
     * @brief Sets the opacity for this digital clock.
     *
     * @param opacity Indicates the opacity of this digital clock. The value ranges
     *                from <b>0</b> (transparency) to <b>255</b> (opacity).
     * @since 1.0
     * @version 1.0
     */
    void SetOpacity(uint8_t opacity);

    /**
     * @brief Obtains the opacity of this digital clock.
     *
     * @return Returns the opacity of this digital clock, within [0, 255].
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetOpacity() const;

    /**
     * @brief Updates this digital clock.
     *
     * @param clockInit Specifies whether the first initialization. <b>true</b> indicates the first initialization,
     *                  and <b> false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void UpdateClock(bool clockInit) override;

protected:
    static constexpr uint8_t TIME_ELEMENT_COUNT = 3;
    UILabel timeLabels_[TIME_ELEMENT_COUNT];

private:
    static constexpr uint8_t BUFFER_SIZE = 4;
    void SetHorizontal();
    void SetVertical();
    void SetTimeLabels(const char buf[TIME_ELEMENT_COUNT][BUFFER_SIZE]);
    void SetTimeLabelsPosition();
    void TimeElementRefresh();
    void RefreshTime();
    DisplayMode displayMode_;
    bool leadingZero_;
    ColorType color_;
    uint8_t prevHour_;
    uint8_t prevMinute_;
    uint8_t prevSecond_;
    bool verticalShow_;
};
}
#endif // UI_DIGITAL_CLOCK_H
