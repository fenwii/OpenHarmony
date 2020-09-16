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
 * @file ui_circle_progress.h
 *
 * @brief Defines the attributes and common functions of a circular progress bar.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_CIRCLE_PROGRESS_H
#define GRAPHIC_LITE_UI_CIRCLE_PROGRESS_H

#include "components/ui_abstract_progress.h"

namespace OHOS {
/**
 * @brief Represents a circular progress bar.
 *
 * This class is used to set the start and end angles, range, and current value to display the circular progress bar.
 *
 * @see UIAbstractProgress
 * @since 1.0
 * @version 1.0
 */
class UICircleProgress : public UIAbstractProgress {
public:
    /**
     * @brief A constructor used to create a <b>UICircleProgress</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UICircleProgress();

    /**
     * @brief A destructor used to delete the <b>UICircleProgress</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UICircleProgress() {}

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_CIRCLE_PROGRESS;
    }

    bool OnPreDraw(const Rect& invalidatedArea) override
    {
        return false;
    }

    void OnDraw(const Rect& invalidatedArea) override;

    /**
     * @brief Sets the coordinates of the center point for this circular progress bar.
     *
     * The coordinates of the center point refer to the position relative to the view.
     *
     * @param x Indicates the x-coordinate to set. The default value is 0.
     * @param y Indicates the y-coordinate to set. The default value is 0.
     * @see GetCenterPosition
     * @since 1.0
     * @version 1.0
     */
    void SetCenterPosition(int16_t x, int16_t y);

    /**
     * @brief Obtains the coordinates of the center point for this circular progress bar.
     *
     * The coordinates of the center point refer to the position relative to the view.
     *
     * @return Returns the coordinates of the center point.
     * @see SetCenterPosition
     * @since 1.0
     * @version 1.0
     */
    Point GetCenterPosition() const
    {
        return center_;
    }

    /**
     * @brief Sets the outer radius for this circular progress bar.
     *
     * @param radius Indicates the outer radius to set.
     * @see GetRadius
     * @since 1.0
     * @version 1.0
     */
    void SetRadius(uint16_t radius)
    {
        radius_ = radius;
    }

    /**
     * @brief Obtains the outer radius of this circular progress bar.
     *
     * @return Returns the outer radius.
     * @see SetRadius
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetRadius() const
    {
        return radius_;
    }

    /**
     * @brief Sets the start angle.
     *
     * The 12-clock direction is 0 degrees, and the 3-clock direction is 90 degrees. \n
     * If the start angle is smaller than the end angle, the progress bar is clockwise.
     * Otherwise, the progress bar is anticlockwise. \n
     * The maximum range of a progress bar is a circle. If the difference between the start angle and end angle
     * exceeds 360 degrees, a circular progress bar is created. \n
     *
     * @param startAngle Indicates the start angle to set, which can be any value represented by <b>int16_t</b>.
     *                   The default value is 0.
     * @see GetStartAngle | SetEndAngle
     * @since 1.0
     * @version 1.0
     */
    void SetStartAngle(int16_t startAngle);

    /**
     * @brief Obtains the start angle.
     *
     * @return Returns the start angle.
     * @see SetStartAngle
     * @since 1.0
     * @version 1.0
     */
    int16_t GetStartAngle() const
    {
        return startAngle_;
    }

    /**
     * @brief Sets the end angle.
     *
     * The 12-clock direction is 0 degrees, and the 3-clock direction is 90 degrees. \n
     * If the start angle is smaller than the end angle, the progress bar is clockwise.
     * Otherwise, the progress bar is anticlockwise. \n
     * The maximum range of a progress bar is a circle. If the difference between the start angle and end angle
     * exceeds 360 degrees, a circular progress bar is created. \n
     *
     * @param endAngle Indicates the end angle to set, which can be any value represented by <b>int16_t</b>.
     *                 The default value is 360.
     * @see GetEndAngle | SetStartAngle
     * @since 1.0
     * @version 1.0
     */
    void SetEndAngle(int16_t endAngle);

    /**
     * @brief Obtains the end angle.
     *
     * @return Returns the end angle.
     * @see SetEndAngle
     * @since 1.0
     * @version 1.0
     */
    int16_t GetEndAngle() const
    {
        return endAngle_;
    }

    /**
     * @brief Sets the coordinates of the foreground image for this progress bar relative to the view.
     *
     * @param x Indicates the x-coordinate to set. The default value is 0.
     * @param y Indicates the y-coordinate to set. The default value is 0.
     * @see SetBackgroundImagePosition
     * @since 1.0
     * @version 1.0
     */
    void SetProgressImagePosition(int16_t x, int16_t y)
    {
        progressImagePos_.x = x + style_->paddingLeft_ + style_->borderWidth_;
        progressImagePos_.y = y + style_->paddingTop_ + style_->borderWidth_;
    }

    /**
     * @brief Sets the coordinates of the background image for this progress bar relative to the view.
     *
     * @param x Indicates the x-coordinate to set. The default value is 0.
     * @param y Indicates the y-coordinate to set. The default value is 0.
     * @see SetProgressImagePosition
     * @since 1.0
     * @version 1.0
     */
    void SetBackgroundImagePosition(int16_t x, int16_t y)
    {
        backgroundImagePos_.x = x + style_->paddingLeft_ + style_->borderWidth_;
        backgroundImagePos_.y = y + style_->paddingTop_ + style_->borderWidth_;
    }

    /**
     * @brief Sets the foreground color for this progress bar.
     *
     * @param color Indicates the foreground color to set. For details, see {@link ColorType}.
     * @since 1.0
     * @version 1.0
     */
    void SetLineColor(ColorType color)
    {
        SetForegroundStyle(STYLE_LINE_COLOR, color.full);
    }

private:
    static constexpr uint16_t MAX_ANGLE_VALUE = CIRCLE_IN_DEGREE;
    static constexpr uint16_t MIN_ANGLE_VALUE = 0;

    void GetStartEndAngle(int16_t& start, int16_t& end) const;
    void GetAngleRange(int16_t& start, int16_t& end) const;
    void GetRedrawAngle(int16_t& start, int16_t& end) const;
    void DrawCommonCircle(const Rect& invalidatedArea);

    Point center_;
    Point backgroundImagePos_;
    Point progressImagePos_;
    uint16_t radius_;
    int16_t startAngle_;
    int16_t endAngle_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_CIRCLE_PROGRESS_H
