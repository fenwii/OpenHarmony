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
 * @file theme.h
 *
 * @brief Declares the base class used to define the functions related to the styles of different components.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_THEME_H
#define GRAPHIC_LITE_THEME_H

#include "components/ui_view.h"
#include "style.h"

namespace OHOS {
/**
 * @brief Stores styles of a button in its different states.
 */
struct ButtonStyle {
    /** Style when released */
    Style released;
    /** Style when pressed */
    Style pressed;
    /** Style when inactive */
    Style inactive;
};

/**
 * @brief Defines the theme class used to define the functions related to the styles of different components.
 *
 * @since 1.0
 * @version 1.0
 */
class Theme : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>Theme</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    Theme();

    /**
     * @brief A destructor used to delete the <b>Theme</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~Theme(){};

    /**
     * @brief Obtains the basic style.
     *
     * @return Returns the basic style.
     * @since 1.0
     * @version 1.0
     */
    Style& GetMainStyle()
    {
        return basicStyle_;
    }

    /**
     * @brief Obtains the style of this button.
     *
     * @return Returns the button style.
     * @since 1.0
     * @version 1.0
     */
    ButtonStyle& GetButtonStyle()
    {
        return buttonStyle_;
    }

    /**
     * @brief Obtains the style of this label.
     *
     * @return Returns the label style.
     * @since 1.0
     * @version 1.0
     */
    Style& GetLabelStyle()
    {
        return labelStyle_;
    }

    /**
     * @brief Obtains the background style of this picker.
     *
     * @return Returns the background style of this picker.
     * @since 1.0
     * @version 1.0
     */
    Style& GetPickerBackgroundStyle()
    {
        return pickerBackgroundStyle_;
    }

    /**
     * @brief Obtains the highlight style of this picker.
     *
     * @return Returns the highlight style of this picker.
     * @since 1.0
     * @version 1.0
     */
    Style& GetPickerHighlightStyle()
    {
        return pickerHighlightStyle_;
    }

    /**
     * @brief Obtains the background style of this progress bar.
     *
     * @return Returns the background style of this progress bar.
     * @since 1.0
     * @version 1.0
     */
    Style& GetProgressBackgroundStyle()
    {
        return progressBackgroundStyle_;
    }

    /**
     * @brief Obtains the foreground style of this progress bar.
     *
     * @return Returns the foreground style of this progress bar.
     * @since 1.0
     * @version 1.0
     */
    Style& GetProgressForegroundStyle()
    {
        return progressForegroundStyle_;
    }

    /**
     * @brief Obtains the style of this slider knob.
     *
     * @return Returns the style of this slider knob.
     * @since 1.0
     * @version 1.0
     */
    Style& GetSliderKnobStyle()
    {
        return sliderKnobStyle_;
    }

protected:
    Style basicStyle_;
    ButtonStyle buttonStyle_;
    Style labelStyle_;
    Style pickerBackgroundStyle_;
    Style pickerHighlightStyle_;
    Style progressBackgroundStyle_;
    Style progressForegroundStyle_;
    Style sliderKnobStyle_;

    virtual void InitBasicStyle();
    virtual void InitButtonStyle();
    virtual void InitLabelStyle();
    virtual void InitPickerStyle();
    virtual void InitProgressStyle();
    virtual void InitSliderStyle();
};
} // namespace OHOS
#endif // GRAPHIC_LITE_THEME_H
