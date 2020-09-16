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
 * @file ui_analog_clock.h
 *
 * @brief Declares an analog clock.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef UI_ANALOG_CLOCK_H
#define UI_ANALOG_CLOCK_H

#include "components/ui_abstract_clock.h"

namespace OHOS {
class UIImageView;
/**
 * @brief Provides the functions related to an analog clock.
 *
 * @see UIAbstractClock
 * @since 1.0
 * @version 1.0
 */
class UIAnalogClock : public UIAbstractClock {
public:
    /**
     * @brief A default constructor used to create a <b>UIAnalogClock</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIAnalogClock();

    /**
     * @brief A destructor used to delete the <b>UIAnalogClock</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIAnalogClock() {}

    /**
     * @brief Enumerates the clock hand types.
     */
    enum class HandType {
        /** Hour hand */
        HOUR_HAND,
        /** Minute hand */
        MINUTE_HAND,
        /** Second hand */
        SECOND_HAND,
    };

    /**
     * @brief Enumerates the drawing types of a clock hand.
     */
    enum class DrawType {
        /** Using a line to draw a clock hand */
        DRAW_LINE,
        /** Using an image to draw a clock hand */
        DRAW_IMAGE
    };

    /**
     * @brief Defines the basic attributes of the analog clock hands. This is an inner class of <b>UIAbstractClock</b>.
     *
     * @since 1.0
     * @version 1.0
     */
    class Hand : public HeapBase {
    public:
        /**
         * @brief A default constructor used to create a <b>Hand</b> instance.
         *
         * @since 1.0
         * @version 1.0
         */
        Hand()
            : center_ { 0, 0 }, initAngle_(0), preAngle_(0), nextAngle_(0),
              position_ { 0, 0 }, imageInfo_ { { 0, 0, 0 } }, color_ { { 0, 0, 0 } }, width_(0), height_(0),
              opacity_(0), drawtype_(DrawType::DRAW_IMAGE)
        {
        }

        /**
         * @brief A destructor used to delete the <b>Hand</b> instance.
         *
         * @since 1.0
         * @version 1.0
         */
        virtual ~Hand() {}

        /**
         * @brief Represents the rotation center of a clock hand.
         */
        Point center_;

        /**
         * @brief Represents the initial clockwise rotation angle of a clock hand. The default value is <b>0</b>,
         *        indicating that the hand direction is vertically upward.
         */
        uint16_t initAngle_;

        /**
         * @brief Represents the latest rotation angle of this clock hand.
         */
        uint16_t preAngle_;

        /**
         * @brief Represents the next rotation angle of this clock hand.
         */
        uint16_t nextAngle_;

        /**
         * @brief Represents the position of a hand on this analog clock.
         */
        Point position_;

        /**
         * @brief Represents the image information of this clock hand.
         */
        ImageInfo imageInfo_;

        /**
         * @brief Represents the information about the rotation and translation of this clock hand.
         */
        TransformMap trans_;

        /**
         * @brief Represents the new rectangle area after the rotation and translation.
         */
        Rect target_;

        /**
         * @brief Represents the color of this clock hand.
         */
        ColorType color_;

        /**
         * @brief Represents the width of this clock hand.
         */
        uint16_t width_;

        /**
         * @brief Represents the height of this clock hand.
         */
        uint16_t height_;

        /**
         * @brief Represents the opacity of this clock hand.
         */
        OpacityType opacity_;

        /**
         * @brief Represents the drawing type of this clock hand.
         */
        DrawType drawtype_;
    };

    /**
     * @brief Obtains the view type.
     *
     * @return Returns <b>UI_ANALOG_CLOCK</b>, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_ANALOG_CLOCK;
    }

    /**
     * @brief Sets the image used to draw a clock hand.
     *
     * @param type Indicates the clock hand type, as enumerated in {@link HandType}.
     * @param img Indicates the image to set.
     * @param position Indicates the start position of this image.
     * @param center Indicates the rotation center of this clock hand.
     * @since 1.0
     * @version 1.0
     */
    void SetHandImage(HandType type, const UIImageView& img, Point position, Point center);

    /**
     * @brief Sets the line used to draw a clock hand.
     *
     * @param type Indicates the clock hand type, as enumerated in {@link HandType}.
     * @param position Indicates the position of the line endpoint close to the rotation center.
     * @param center Indicates the rotation center of this clock hand.
     * @param color Indicates the color of this line.
     * @param width Indicates the width of this line when it is 12 o'clock.
     * @param height Indicates the height of this line when it is 12 o'clock.
     * @param opacity Indicates the opacity of this line.
     * @since 1.0
     * @version 1.0
     */
    void SetHandLine(HandType type, Point position, Point center, ColorType color,
        uint16_t width, uint16_t height, OpacityType opacity);

    /**
     * @brief Obtains the rotation center of a specified clock hand.
     *
     * @param type Indicates the clock hand type, as enumerated in {@link HandType}.
     * @return Returns the rotation center.
     * @since 1.0
     * @version 1.0
     */
    Point GetHandRotateCenter(HandType type) const;

    /**
     * @brief Obtains the position of a specified clock hand.
     *
     * @param type Indicates the clock hand type, as enumerated in {@link HandType}.
     * @return Returns the position of this specified clock hand.
     * @since 1.0
     * @version 1.0
     */
    Point GetHandPosition(HandType type) const;

    /**
     * @brief Obtains the initial rotation angle of the specified clock hand.
     *
     * @param type Indicates the clock hand type, as enumerated in {@link HandType}.
     * @return Returns the initial rotation angle of this specified clock hand.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetHandInitAngle(HandType type) const;

    /**
     * @brief Obtains the current rotation angle of the specified clock hand.
     *
     * @param type Indicates the clock hand type, as enumerated in {@link HandType}.
     * @return Returns the current rotation angle of this specified clock hand.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetHandCurrentAngle(HandType type) const;

    /**
     * @brief Sets the initial time in the 24-hour format.
     *
     * @param hour Indicates the hour to set.
     * @param minute Indicates the minute to set.
     * @param second Indicates the second to set.
     * @since 1.0
     * @version 1.0
     */
    void SetInitTime24Hour(uint8_t hour, uint8_t minute, uint8_t second);

    /**
     * @brief Sets the initial time in the 12-hour format.
     *
     * @param hour Indicates the hour to set.
     * @param minute Indicates the minute to set.
     * @param second Indicates the second to set.
     * @param am Specifies whether it is in the morning. <b>true</b> indicates that it is in the morning,
     *           and <b> false</b> indicates that it is in the afternoon.
     * @since 1.0
     * @version 1.0
     */
    void SetInitTime12Hour(uint8_t hour, uint8_t minute, uint8_t second, bool am);

    /**
     * @brief Draws an analog clock.
     *
     * @param invalidatedArea Indicates the area to draw.
     * @since 1.0
     * @version 1.0
     */
    void OnDraw(const Rect& invalidatedArea) override;

    /**
     * @brief Performs the operations needed after the drawing.
     *
     * @param invalidatedArea Indicates the area to draw.
     * @since 1.0
     * @version 1.0
     */
    virtual void OnPostDraw(const Rect& invalidatedArea) override;

    /**
     * @brief Sets the position for this analog clock.
     *
     * @param x Indicates the x-coordinate to set.
     * @param y Indicates the y-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    void SetPosition(int16_t x, int16_t y) override;

    /**
     * @brief Sets the position and size for this analog clock.
     *
     * @param x Indicates the x-coordinate to set.
     * @param y Indicates the y-coordinate to set.
     * @param width Indicates the width to set.
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    void SetPosition(int16_t x, int16_t y, int16_t width, int16_t height) override;

    /**
     * @brief Sets the working mode for this analog clock.
     *
     * @param newMode Indicates the working mode to set. For details, see {@link WorkMode}.
     * @since 1.0
     * @version 1.0
     */
    void SetWorkMode(WorkMode newMode) override;

    /**
     * @brief Updates the time of this analog clock.
     *
     * @param clockInit Specifies whether it is the first initialization. <b>true</b> indicates it is the
     *                  first initialization, and <b> false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void UpdateClock(bool clockInit) override;

private:
    Hand hourHand_;
    Hand minuteHand_;
    Hand secondHand_;

    void DrawHand(const Rect& current, const Rect& invalidatedArea, Hand& hand);
    void DrawHandImage(const Rect& current, const Rect& invalidatedArea, Hand& hand);
    void DrawHandLine(const Rect& invalidatedArea, Hand& hand);
    uint16_t ConvertHandValueToAngle(uint8_t handValue, uint8_t range, uint8_t secondHandValue, uint8_t ratio) const;
    uint16_t ConvertHandValueToAngle(uint8_t handValue, uint8_t range) const;
    void CalculateRedrawArea(const Rect& current, Hand& hand, bool clockInit);
};
} // namespace OHOS
#endif // UI_ANALOG_CLOCK_H
