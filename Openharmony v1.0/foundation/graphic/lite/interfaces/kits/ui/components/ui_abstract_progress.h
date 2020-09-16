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
 * @file ui_abstract_progress.h
 *
 * @brief Defines the base class attributes and common functions of a progress bar.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_ABSTRACT_PROGRESS_H
#define GRAPHIC_LITE_UI_ABSTRACT_PROGRESS_H

#include "common/image.h"
#include "components/ui_view.h"

namespace OHOS {
/**
 * @brief Represents the abstract base class which provides functions related to the progress bar.
 *
 * @see UIView
 * @since 1.0
 * @version 1.0
 */
class UIAbstractProgress : public UIView {
public:
    /**
     * @brief A constructor used to create a <b>UIAbstractProgress</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIAbstractProgress();

    /**
     * @brief A destructor used to delete the <b>UIAbstractProgress</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIAbstractProgress();

    /**
     * @brief Obtains the component type.
     *
     * @return Returns the component type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_ABSTRACT_PROGRESS;
    }

    /**
     * @brief Sets whether the background of the progress bar is visible.
     *
     * @param enable Specifies whether the background of the progress bar is visible. <b>true</b> (the default value)
     *               indicates that the background is visible, and <b>false</b> indicates the opposite case.
     * @since 1.0
     * @version 1.0
     */
    void EnableBackground(bool enable)
    {
        enableBackground_ = enable;
    }

    /**
     * @brief Sets the current value for this progress bar.
     *
     * @param value Indicates the current value of this progress bar, within [rangeMin, rangeMax] specified by
     *              {@link SetRange}. If the value is less than <b>rangeMin</b>, <b>rangeMin</b> is used;
     *              if the value is greater than <b>rangeMax</b>, <b>rangeMax</b> is used.
     * @see SetRange | GetValue
     * @since 1.0
     * @version 1.0
     */
    void SetValue(int16_t value);

    /**
     * @brief Obtains the current value of this progress bar.
     *
     * @return Returns the current value of this progress bar.
     * @see SetValue
     * @since 1.0
     * @version 1.0
     */
    int16_t GetValue() const
    {
        return curValue_;
    }

    /**
     * @brief Sets the range for this progress bar.
     *
     * <b>rangeMin</b> and <b>rangeMax</b> can be any value represented by <b>int16_t</b>.
     * <b>rangeMax</b> must be greater than or equal to <b>rangeMin</b>.
     * Otherwise, the setting does not take effect and the original value is used.
     *
     * @param rangeMax Indicates the maximum value of this progress bar. The default value is 100.
     * @param rangeMin Indicates the minimum value of this progress bar. The default value is 0.
     * @see GetRangeMin | GetRangeMax
     * @since 1.0
     * @version 1.0
     */
    void SetRange(int16_t rangeMax, int16_t rangeMin);

    /**
     * @brief Obtains the minimum value of this progress bar.
     *
     * @return Returns the minimum value of this progress bar.
     * @see  SetRange | GetRangeMax
     * @since 1.0
     * @version 1.0
     */
    int16_t GetRangeMin() const
    {
        return rangeMin_;
    }

    /**
     * @brief Obtains the maximum value of this progress bar.
     *
     * @return Returns the maximum value of this progress bar.
     * @see SetRange | GetRangeMin
     * @since 1.0
     * @version 1.0
     */
    int16_t GetRangeMax() const
    {
        return rangeMax_;
    }

    /**
     * @brief Sets the image for this progress bar.
     *
     * The size of the image must be the same as that of the progress bar to ensure a normal display.
     * If the value of any input parameter is <b>nullptr</b>, image filling is canceled.
     * Instead, color filling will be adopted.
     *
     * @param foregroundImage Indicates the foreground image of the progress bar. The default value is <b>nullptr</b>.
     * @param backgroundImage Indicates the background image of the progress bar. The default value is <b>nullptr</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetImage(const char* foregroundImage, const char* backgroundImage = nullptr);

    /**
     * @brief Sets the image as a pixel map for this progress bar.
     *
     * The size of the image must be the same as that of the progress bar to ensure a normal display.
     * If the value of any input parameter is <b>nullptr</b>, image filling is canceled.
     * Instead, color filling will be adopted.
     *
     * @param foregroundImage Indicates the foreground image of the progress bar. The default value is <b>nullptr</b>.
     * @param backgroundImage Indicates the background image of the progress bar. The default value is <b>nullptr</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetImage(const ImageInfo* foregroundImage, const ImageInfo* backgroundImage = nullptr);

    /**
     * @brief Sets the step for this progress bar.
     *
     * The step is used to control the update frequency of the progress bar. When the value change exceeds the step,
     * the progress bar is redrawn. \n
     * For example, when the step is set to 10 and the current progress value is 5, the progress bar will not be
     * redrawn if the progress value becomes 14, but will be redrawn if the progress value becomes 15. \n
     * In addition, when its current value changes to be the maximum or minimum value,
     * the progress bar is redrawn regardless of the step you set. \n
     *
     * @param step Indicates the step to set. The default value is 1.
     * @see GetStep
     * @since 1.0
     * @version 1.0
     */
    void SetStep(uint16_t step)
    {
        step_ = step;
    }

    /**
     * @brief Obtains the current step of this progress bar.
     *
     * @return Returns the current step.
     * @see  SetStep
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetStep() const
    {
        return step_;
    }

    /**
     * @brief Sets the background style for this progress bar.
     *
     * @param style Indicates the background style of the progress bar. For details, see {@link Style}.
     * @see SetForegroundStyle | GetBackgroundStyle
     * @since 1.0
     * @version 1.0
     */
    void SetBackgroundStyle(const Style& style);

    /**
     * @brief Sets a background style for this progress bar.
     *
     * @param key Indicates the key of the style to set.
     * @param value Indicates the value matching the key.
     * @since 1.0
     * @version 1.0
     */
    void SetBackgroundStyle(uint8_t key, int64_t value);

    /**
     * @brief Obtains the background style of this progress bar.
     *
     * @return Returns the background style.
     * @See SetBackgroundStyle
     * @since 1.0
     * @version 1.0
     */
    const Style& GetBackgroundStyle() const;

    /**
     * @brief Obtains the value of a background style of this progress bar.
     *
     * @param key Indicates the key of the style.
     * @return Returns the value of the style.
     * @since 1.0
     * @version 1.0
     */
    int64_t GetBackgroundStyle(uint8_t key) const;

    /**
     * @brief Sets the foreground style for this progress bar.
     *
     * @param style Indicates the foreground style of this progress bar. For details, see {@link Style}.
     * @see SetBackgroundStyle | GetForegroundStyle
     * @since 1.0
     * @version 1.0
     */
    void SetForegroundStyle(const Style& style);

    /**
     * @brief Sets a foreground style for this progress bar.
     *
     * @param key Indicates the key of the style to set.
     * @param value Indicates the value matching the key.
     * @since 1.0
     * @version 1.0
     */
    void SetForegroundStyle(uint8_t key, int64_t value);

    /**
     * @brief Obtains the foreground style of this progress bar.
     *
     * @return Returns the foreground style.
     * @See SetForegroundStyle
     * @since 1.0
     * @version 1.0
     */
    const Style& GetForegroundStyle() const;

    /**
     * @brief Obtains the value of a foreground style of this progress bar.
     *
     * @param key Indicates the key of the style.
     * @return Returns the value of the style.
     * @since 1.0
     * @version 1.0
     */
    int64_t GetForegroundStyle(uint8_t key) const;

    /**
     * @brief Sets the type of caps on the background and foreground of the progress bar.
     *
     * @param cap  Indicates the cap type. For details, see {@link CapType}.
     * @since 1.0
     * @version 1.0
     */
    void SetCapType(CapType cap)
    {
        SetBackgroundStyle(STYLE_LINE_CAP, cap);
        SetForegroundStyle(STYLE_LINE_CAP, cap);
    }

protected:
    static constexpr uint16_t MAX_PERCENT_VALUE = 100;
    static constexpr uint16_t MIN_PERCENT_VALUE = 0;

    uint16_t GetRangeSize() const;
    int16_t GetCurrentPos(int16_t distance) const;
    bool enableBackground_ : 1;
    bool backgroundStyleAllocFlag_ : 1;
    bool foregroundStyleAllocFlag_ : 1;
    Style* backgroundStyle_;
    Style* foregroundStyle_;
    Image* backgroundImage_;
    Image* foregroundImage_;
    int16_t rangeMax_;
    int16_t rangeMin_;
    int16_t curValue_;
    uint16_t step_;
    int16_t lastValue_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_ABSTRACT_PROGRESS_H
