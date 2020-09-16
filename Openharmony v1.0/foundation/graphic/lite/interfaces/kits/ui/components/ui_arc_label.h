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
 * @file ui_arc_label.h
 *
 * @brief Defines the attributes of an arc label.
 *
 * The attributes include the center and radius of an arc, angle range, and text orientation.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_ARC_LABEL_H
#define GRAPHIC_LITE_UI_ARC_LABEL_H

#include "common/text.h"
#include "components/ui_view.h"

namespace OHOS {
/**
 * @brief Defines functions related to an arc label.
 *
 * @since 1.0
 * @version 1.0
 */
class UIArcLabel : public UIView {
public:
    /**
     * @brief Enumerates text orientations.
     */
    enum class TextOrientation : uint8_t {
        /** Inside */
        INSIDE,
        /** Outside */
        OUTSIDE,
    };

    /**
     * @brief A default constructor used to create a <b>UIArcLabel</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIArcLabel();

    /**
     * @brief A destructor used to delete the <b>UIArcLabel</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIArcLabel();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns <b>UI_ARC_LABEL</b>, as defined in {link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_ARC_LABEL;
    }

    /**
     * @brief Obtains the width of this arc text.
     *
     * @return Returns the width of this arc text.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetWidth() override
    {
        ReMeasure();
        return UIView::GetWidth();
    }

    /**
     * @brief Obtains the height of this arc text.
     *
     * @return Returns the height of this arc text.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetHeight() override
    {
        ReMeasure();
        return UIView::GetHeight();
    }

    /**
     * @brief Sets the text content for this arc label.
     *
     * @param text Indicates the pointer to the text content.
     * @since 1.0
     * @version 1.0
     */
    void SetText(const char* text);

    /**
     * @brief Obtains the text of this arc label.
     *
     * @return Returns the text.
     * @since 1.0
     * @version 1.0
     */
    const char* GetText() const;

    /**
     * @brief Sets the alignment mode for this text.
     *
     * @param horizontalAlign Indicates the horizontal alignment mode to set,
     *                        which can be {@link TEXT_ALIGNMENT_LEFT},
     *                        {@link TEXT_ALIGNMENT_CENTER}, or {@link TEXT_ALIGNMENT_RIGHT}.
     * @since 1.0
     * @version 1.0
     */
    void SetAlign(UITextLanguageAlignment horizontalAlign);

    /**
     * @brief Obtains the horizontal alignment mode.
     *
     * @return Returns the horizontal alignment mode.
     * @since 1.0
     * @version 1.0
     */
    UITextLanguageAlignment GetHorAlign() const;

    /**
     * @brief Obtains the direction of this text.
     *
     * @return Returns the text direction, as defined in {@link UITextLanguageDirect}.
     * @since 1.0
     * @version 1.0
     */
    UITextLanguageDirect GetDirect();

    /**
     * @brief Sets the font ID for this arc label.
     *
     * @param fontId Indicates the font ID composed of font name and size.
     * @since 1.0
     * @version 1.0
     */
    void SetFontId(uint8_t fontId);

    /**
     * @brief Obtains the font ID composed of font name and size.
     *
     * @return Returns the front ID of this arc label.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetFontId() const;

    /**
     * @brief Sets the font for this arc label.
     *
     * @param name Indicates the pointer to the font name.
     * @param size Indicates the font size to set.
     * @since 1.0
     * @version 1.0
     */
    void SetFont(const char* name, uint8_t size);

    /**
     * @brief Sets the center position for this arc text.
     *
     * @param x Indicates the x-coordinate to set.
     * @param y Indicates the y-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    void SetArcTextCenter(int16_t x, int16_t y)
    {
        if (arcCenter_.x != x || arcCenter_.y != y) {
            arcCenter_.x = x;
            arcCenter_.y = y;
            RefreshArcLabel();
        }
    }

    /**
     * @brief Obtains the center position of this arc text.
     *
     * @return Returns the center position of this arc text.
     * @since 1.0
     * @version 1.0
     */
    Point GetArcTextCenter() const
    {
        return arcCenter_;
    }

    /**
     * @brief Sets the radius for this arc text.
     *
     * @param radius Indicates the radius to set.
     * @since 1.0
     * @version 1.0
     */
    void SetArcTextRadius(uint16_t radius)
    {
        if (radius_ != radius) {
            radius_ = radius;
            RefreshArcLabel();
        }
    }

    /**
     * @brief Obtains the radius of this arc text.
     *
     * @return Returns the radius of this arc text.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetArcTextRadius() const
    {
        return radius_;
    }

    /**
     * @brief Sets the start angle and end angle for this arc text.
     *
     * The angle in 12 o'clock direction is 0 degrees, and the value increases clockwise.
     * The text direction is clockwise when the end angle is greater than the start angle, and the text direction is
     * counterclockwise otherwise.
     *
     * @param startAngle Indicates the start angle to set.
     * @param endAngle Indicates the end angle to set.
     * @since 1.0
     * @version 1.0
     */
    void SetArcTextAngle(int16_t startAngle, int16_t endAngle)
    {
        if (startAngle_ != startAngle || endAngle_ != endAngle) {
            startAngle_ = startAngle;
            endAngle_ = endAngle;
            RefreshArcLabel();
        }
    }

    /**
     * @brief Obtains the start angle of this arc text.
     *
     * @return Returns the start angle of this arc text.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetArcTextStartAngle() const
    {
        return startAngle_;
    }

    /**
     * @brief Obtains the end angle of this arc text.
     *
     * @return Returns the end angle of this arc text.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetArcTextEndAngle() const
    {
        return endAngle_;
    }

    /**
     * @brief Sets the orientation for this arc text.
     *
     * @param orientation Indicates the text orientation to set.
     * @since 1.0
     * @version 1.0
     */
    void SetArcTextOrientation(TextOrientation orientation)
    {
        if (orientation_ != orientation) {
            orientation_ = orientation;
            RefreshArcLabel();
        }
    }

    /**
     * @brief Obtains the orientation of this arc text.
     *
     * @return Returns the orientation of this arc text.
     * @since 1.0
     * @version 1.0
     */
    TextOrientation GetArcTextOrientation() const
    {
        return orientation_;
    }

    /**
     * @brief Draws an arc text.
     *
     * @param invalidatedArea Indicates the area to draw.
     * @since 1.0
     * @version 1.0
     */
    virtual void OnDraw(const Rect& invalidatedArea) override;

    /**
     * @brief Stores the attribute information about this arc text to draw.
     */
    struct ArcTextInfo {
        uint16_t radius;
        int16_t startAngle;
        Point arcCenter;
        uint32_t lineStart;
        uint32_t lineEnd;
        UITextLanguageDirect direct;
    };

protected:
    Text arcLabelText_;
    void RefreshArcLabel();

private:
    virtual void ReMeasure() override;
    void MeasureArcTextInfo();
    void DrawArcText(const Rect& mask);

    bool needRefresh_;
    Point textSize_;
    uint16_t radius_;
    int16_t startAngle_;
    int16_t endAngle_;
    Point arcCenter_;
    TextOrientation orientation_;

    ArcTextInfo arcTextInfo_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_ARC_LABEL_H
