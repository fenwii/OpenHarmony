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
 * @file ui_axis.h
 *
 * @brief Defines the attributes and functions of the x- and y-axises. This class is used in {@link UIChart}.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_AXIS_H
#define GRAPHIC_LITE_UI_AXIS_H

#include "components/ui_label.h"
#include "components/ui_view_group.h"

namespace OHOS {
/**
 * @brief Represents the coordinate axis base class, which defines the basic attributes of coordinate axis,
 *        sets whether a coordinate axis is visible, and sets the number of scales on a coordinate axis.
 *        This class is used in {@link UIChart}.
 *
 * @since 1.0
 * @version 1.0
 */
class UIAxis : public UIViewGroup {
public:
    /**
     * @brief A constructor used to create a <b>UIAxis</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIAxis();

    /**
     * @brief A destructor used to delete the <b>UIAxis</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIAxis() {}

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type. For details, see {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_AXIS;
    }

    /**
     * @brief Sets the value range of a coordinate axis.
     *
     * The maximum value must be greater than the minimum value. Otherwise, the setting fails.
     *
     * @param min Indicates the minimum value to set.
     * @param max Indicates the maximum value to set.
     * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    virtual bool SetDataRange(uint16_t min, uint16_t max) = 0;

    /**
     * @brief Sets the number of scales on a coordinate axis.
     *
     * For a bar chart, the number of scales must be the same as that of bars so that each bar
     * can be properly displayed between two scales.
     *
     * @param count Indicates the number of scales to set. The default value is <b>5</b>.
     * @since 1.0
     * @version 1.0
     */
    virtual void SetMarkNum(uint16_t count) = 0;

    void EnableReverse(bool enable)
    {
        enableReverse_ = enable;
    }

    const Point& GetStartPoint() const
    {
        return start_;
    }

    const Point& GetEndPoint() const
    {
        return end_;
    }

    float GetMarkInterval() const
    {
        return markInterval_;
    }

    /**
     * @brief Sets the line color of the coordinate axis.
     *
     * @param color Indicates the line color to set. For details, see {@link ColorType}.
     * @since 1.0
     * @version 1.0
     */
    void SetLineColor(const ColorType& color);

    void OnDraw(const Rect& invalidatedArea) override;

    bool OnPreDraw(const Rect& invalidatedArea) override
    {
        return false;
    }

    virtual bool UpdateAxis() = 0;

    /**
     * @brief Translates data into pixel coordinates.
     *
     * This function calculates the relative position of a pixel in the corresponding {@link UIChart}
     * based on the value of <b>value</b> and the data range of the coordinate axis.
     *
     * @param value Indicates the current value. The coordinate value obtained after translation is
     *              also printed using this parameter.
     * @since 1.0
     * @version 1.0
     */
    virtual void TranslateToPixel(int16_t& value) = 0;

    virtual void UpdateAxisPoints() = 0;

protected:
    float maxRange_;
    float minRange_;
    Point start_;
    Point end_;
    float markInterval_;
    float dataPerMark_;
    float dataInterval_;
    uint16_t markDataCount_;
    bool enableReverse_;

    static constexpr uint8_t AXIS_DEFAULT_MARK_INTERVAL = 5;
    static constexpr uint8_t AXIS_DEFAULT_MARK_LENGTH = 1;

    virtual void DrawAxisMark(const Rect& invalidatedArea) = 0;
};

/**
 * @brief Defines the unique attributes and functions for the x-axis. This class is used in {@link UIChart}.
 *
 * @see UIAxis
 * @since 1.0
 * @version 1.0
 */
class UIXAxis : public UIAxis {
public:
    /**
     * @brief A constructor used to create a <b>UIXAxis</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIXAxis() {}

    /**
     * @brief A destructor used to delete the <b>UIXAxis</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIXAxis() {}

    bool UpdateAxis() override;

    /**
     * @brief Translates data into the x coordinate of a pixel.
     *
     * This function calculates the position of the corresponding pixel (relative position in the chart)
     * based on the value of <b>value</b> and the data range of the x-axis.
     *
     * @param value Indicates the current value. The x coordinate obtained after translation is also
     *              printed using this parameter.
     * @since 1.0
     * @version 1.0
     */
    void TranslateToPixel(int16_t& value) override;

    /**
     * @brief Sets the value range of the X axis.
     *
     * The maximum value must be greater than the minimum value. Otherwise, the setting fails.
     *
     * @param min Indicates the minimum value to set.
     * @param max Indicates the maximum value to set.
     * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool SetDataRange(uint16_t min, uint16_t max) override;

    /**
     * @brief Sets the number of scales on the x-axis.
     *
     * For a bar chart, the number of scales must be the same as that of bars so that each bar can be properly
     * displayed between two scales.
     *
     * @param count Indicates the number of scales to set. The default value is <b>5</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetMarkNum(uint16_t count) override;

    void UpdateAxisPoints() override;

private:
    void DrawAxisMark(const Rect& invalidatedArea) override;
};

/**
 * @brief Defines the unique attributes and functions for the y-axis. This class is used in {@link UIChart}.
 *
 * @see UIAxis
 * @since 1.0
 * @version 1.0
 */
class UIYAxis : public UIAxis {
public:
    /**
     * @brief A constructor used to create a <b>UIYAxis</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIYAxis() {}

    /**
     * @brief A destructor used to delete the <b>UIYAxis</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIYAxis() {}

    bool UpdateAxis() override;

    /**
     * @brief Translates data into the y coordinate of a pixel.
     *
     * Calculates the position of the corresponding pixel (relative position in the chart) based on the value
     * of <b>value</b> and the data range of the Y axis.
     *
     * @param value Indicates the current value. The y coordinate obtained after translation is also printed
     *              using this parameter.
     * @since 1.0
     * @version 1.0
     */
    void TranslateToPixel(int16_t& value) override;

    /**
     * @brief Sets the value range of the y-axis.
     *
     * The maximum value must be greater than the minimum value. Otherwise, the setting fails.
     *
     * @param min Indicates the minimum value to set.
     * @param max Indicates the maximum value to set.
     * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool SetDataRange(uint16_t min, uint16_t max) override;

    /**
     * @brief Sets the number of scales on the Y axis.
     *
     * @param count Indicates the number of scales to set. The default value is <b>5</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetMarkNum(uint16_t count) override;

    void UpdateAxisPoints() override;

private:
    void DrawAxisMark(const Rect& invalidatedArea) override;
};
}
#endif // GRAPHIC_LITE_UI_AXIS_H
