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
 * @file ui_slider.h
 *
 * @brief Defines the attributes and common functions of a slider.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_SLIDER_H
#define GRAPHIC_LITE_UI_SLIDER_H

#include "common/image.h"
#include "components/ui_box_progress.h"

namespace OHOS {
/**
 * @brief Represents a slider.
 *
 * Users can drag or click the knob to adjust the progress of an event.
 *
 * @see UIBoxProgress
 * @since 1.0
 * @version 1.0
 */
class UISlider : public UIBoxProgress {
public:
    /**
     * @brief A constructor used to create a <b>UISlider</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UISlider();

    /**
     * @brief A destructor used to delete the <b>UISlider</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UISlider();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_SLIDER;
    }

    /**
     * @brief Sets the width for this knob.
     *
     * The width of this knob is the same as its height. \n
     * By default, the width of this knob is the same as the height of the horizontal slider
     * or the width of the vertical slider. \n
     *
     * @param width Indicates the knob width to set.
     * @see GetKnobWidth
     * @since 1.0
     * @version 1.0
     */
    void SetKnobWidth(int16_t width)
    {
        knobWidth_ = width;
        knobWidthSetFlag_ = true;
    }

    /**
     * @brief Obtains the knob width.
     *
     * @return Returns the knob width.
     * @see SetKnobWidth
     * @since 1.0
     * @version 1.0
     */
    int16_t GetKnobWidth();

    /**
     * @brief Sets the images as pixel maps for this slider, including the background, foreground, and knob images.
     *
     * @param backgroundImage Indicates the background image to set.
     * @param foregroundImage Indicates the foreground image to set.
     * @param knobImage Indicates the knob image to set.
     * @since 1.0
     * @version 1.0
     */
    void SetImage(const ImageInfo* backgroundImage, const ImageInfo* foregroundImage, const ImageInfo* knobImage);

    /**
     * @brief Sets the images for this slider, including the background, foreground, and knob images.
     *
     * @param backgroundImage Indicates the background image to set.
     * @param foregroundImage Indicates the foreground image to set.
     * @param knobImage Indicates the knob image to set.
     * @since 1.0
     * @version 1.0
     */
    void SetImage(const char* backgroundImage, const char* foregroundImage, const char* knobImage);

    /**
     * @brief Sets the colors for this slider, including the background, foreground, and knob colors.
     *
     * @param backgroundColor Indicates the background color to set.
     * @param foregroundColor Indicates the foreground color to set.
     * @param knobColor Indicates the knob color to set.
     * @since 1.0
     * @version 1.0
     */
    void SetSliderColor(const ColorType backgroundColor, const ColorType foregroundColor, const ColorType knobColor)
    {
        SetBackgroundStyle(STYLE_BACKGROUND_COLOR, backgroundColor.full);
        SetForegroundStyle(STYLE_BACKGROUND_COLOR, foregroundColor.full);
        SetKnobStyle(STYLE_BACKGROUND_COLOR, knobColor.full);
    }

    /**
     * @brief Sets the corner radiuses for this slider, including the background, foreground, and knob corner radiuses.
     *
     * @param backgroundRadius Indicates the background corner radius to set.
     * @param foregroundRadius Indicates the foreground corner radius to set.
     * @param knobRadius Indicates the knob corner radius to set.
     * @since 1.0
     * @version 1.0
     */
    void SetSliderRadius(int16_t backgroundRadius, int16_t foregroundRadius, int16_t knobRadius)
    {
        SetBackgroundStyle(STYLE_BORDER_RADIUS, backgroundRadius);
        SetForegroundStyle(STYLE_BORDER_RADIUS, foregroundRadius);
        SetKnobStyle(STYLE_BORDER_RADIUS, knobRadius);
    }

    /**
     * @brief Sets the knob style.
     *
     * @param style Indicates the knob style to set. For details, see {@link Style}.
     * @see GetKnobStyle
     * @since 1.0
     * @version 1.0
     */
    void SetKnobStyle(const Style& style);

    /**
     * @brief Sets a knob style.
     *
     * @param key Indicates the key of the style to set.
     * @param value Indicates the value matching the key.
     * @since 1.0
     * @version 1.0
     */
    void SetKnobStyle(uint8_t key, int64_t value);

    /**
     * @brief Obtains the knob style.
     *
     * @return Returns the knob style.
     * @since 1.0
     * @version 1.0
     */
    const Style& GetKnobStyle() const;

    /**
     * @brief Obtains the value of a knob style.
     *
     * @param key Indicates the key of the style.
     * @return Returns the value of the style.
     * @since 1.0
     * @version 1.0
     */
    int64_t GetKnobStyle(uint8_t key) const;

    void OnClickEvent(const ClickEvent& event) override;

    bool OnDragEvent(const DragEvent& event) override;

    bool OnDragEndEvent(const DragEvent& event) override;

    bool OnPreDraw(const Rect& invalidatedArea) override
    {
        return false;
    }

    void OnDraw(const Rect& invalidatedArea) override;

    /**
     * @brief Represents the listener for a slider change.
     *
     * This is an inner class of <b>UISlider</b> used to listen for slider events and invoke the callback function.
     *
     * @see UISlider
     * @since 1.0
     * @version 1.0
     */
    class UISliderEventListener : public HeapBase {
    public:
        /**
         * @brief A destructor used to delete the <b> UISliderEventListener </b> instance.
         *
         * @since 1.0
         * @version 1.0
         */
        virtual ~UISliderEventListener() {}
        /**
         * @brief Called when the slider is dragged or clicked. This is a virtual function, which needs your
         *        implementation.
         *
         * @param value Indicates the current value of the slider.
         * @since 1.0
         * @version 1.0
         */
        virtual void OnChange(int16_t value) {}
        /**
         * @brief Called when the slider is released. This is a virtual function, which needs your implementation.
         *
         * @param value Indicates the current value of the slider.
         * @since 1.0
         * @version 1.0
         */
        virtual void OnRelease(int16_t value) {}
    };

    /**
     * @brief Sets the listener for a slider change.
     *
     * When a user drags or clicks the slider, listening is triggered and the <b>OnChange</b> callback is invoked.
     * When a user releases the slider, the <b>OnRelease</b> callback is invoked.
     *
     * @param listener Indicates the listener to set. For details, see {@link UISliderEventListener}.
     * @since 1.0
     * @version 1.0
     */
    void SetSliderEventListener(UISliderEventListener* listener)
    {
        listener_ = listener;
    }

private:
    void DrawKnob(const Rect& invalidatedArea, const Rect& foregroundRect);
    int16_t CalculateCurrentValue(int16_t length, int16_t totalLength);
    int16_t UpdateCurrentValue(const Point& knobPosition);

    int16_t knobWidth_;
    bool knobWidthSetFlag_;
    bool knobStyleAllocFlag_;
    Style* knobStyle_;
    Image* knobImage_;
    UISliderEventListener* listener_;
}; // class UISlider
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_SLIDER_H
