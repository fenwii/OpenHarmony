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
 * @file style.h
 *
 * @brief Defines the attributes and common functions of style.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_STYLE_H
#define GRAPHIC_LITE_STYLE_H

#include "color.h"

namespace OHOS {
/**
 * @brief Enumerates keys of styles.
 *
 * @since 1.0
 * @version 1.0
 */
enum : uint8_t {
    /** Background color */
    STYLE_BACKGROUND_COLOR,
    /** Background opacity */
    STYLE_BACKGROUND_OPA,
    /** Border radius */
    STYLE_BORDER_RADIUS,
    /** Border color */
    STYLE_BORDER_COLOR,
    /** Border opacity */
    STYLE_BORDER_OPA,
    /** Border width */
    STYLE_BORDER_WIDTH,
    /** Left padding */
    STYLE_PADDING_LEFT,
    /** Right padding */
    STYLE_PADDING_RIGHT,
    /** Top padding */
    STYLE_PADDING_TOP,
    /** Bottom padding */
    STYLE_PADDING_BOTTOM,
    /** Left margin */
    STYLE_MARGIN_LEFT,
    /** Right margin */
    STYLE_MARGIN_RIGHT,
    /** Top margin */
    STYLE_MARGIN_TOP,
    /** Bottom margin */
    STYLE_MARGIN_BOTTOM,
    /** Image opacity */
    STYLE_IMAGE_OPA,
    /** Text color */
    STYLE_TEXT_COLOR,
    /** Text font */
    STYLE_TEXT_FONT,
    /** Letter spacing */
    STYLE_LETTER_SPACE,
    /** Line spacing */
    STYLE_LINE_SPACE,
    /** Text opacity */
    STYLE_TEXT_OPA,
    /** Line color */
    STYLE_LINE_COLOR,
    /** Line width */
    STYLE_LINE_WIDTH,
    /** Line opacity */
    STYLE_LINE_OPA,
    /** Line cap style */
    STYLE_LINE_CAP
};

/**
 * @brief Enumerates cap styles.
 *
 * @since 1.0
 * @version 1.0
 */
enum CapType : uint8_t {
    /** No cap style */
    CAP_NONE,
    /** Round cap style */
    CAP_ROUND,
};

/**
 * @brief Defines the basic attributes and functions of a style. You can use this class to set different styles.
 *
 * @since 1.0
 * @version 1.0
 */
class Style : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>Style</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    Style();

    /**
     * @brief A destructor used to delete the <b>Style</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~Style() {}

    /**
     * @brief Sets a style.
     *
     * @param key Indicates the key of the style to set.
     * @param value Indicates the value matching the key.
     * @since 1.0
     * @version 1.0
     */
    void SetStyle(uint8_t key, int64_t value);

    /**
     * @brief Obtains the value of a style.
     *
     * @param key Indicates the key of the style.
     * @return Returns the value of the style.
     * @since 1.0
     * @version 1.0
     */
    int64_t GetStyle(uint8_t key) const;

    /* background style */
    ColorType bgColor_;
    uint8_t bgOpa_;
    /* border style */
    uint8_t borderOpa_;
    int16_t borderWidth_;
    int16_t borderRadius_;
    ColorType borderColor_;
    /* padding style */
    uint16_t paddingLeft_;
    uint16_t paddingRight_;
    uint16_t paddingTop_;
    uint16_t paddingBottom_;
    /* margin style */
    int16_t marginLeft_;
    int16_t marginRight_;
    int16_t marginTop_;
    int16_t marginBottom_;
    /* image style */
    uint8_t imageOpa_;
    /* text style */
    uint8_t textOpa_;
    uint8_t font_;
    int16_t letterSpace_;
    int16_t lineSpace_;
    ColorType textColor_;
    /* line style */
    ColorType lineColor_;
    uint8_t lineOpa_;
    uint8_t lineCap_;
    int16_t lineWidth_;
};

/**
 * @brief Define some default style for {@link UIView}.
 *
 * @since 1.0
 * @version 1.0
 */
class StyleDefault : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>StyleDefault</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    StyleDefault() {};

    /**
     * @brief A destructor used to delete the <b>StyleDefault</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    ~StyleDefault() {};

    static void Init();

    /**
     * @brief Obtains the default style.
     *
     * @return Returns the default style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetDefaultStyle()
    {
        return defaultStyle_;
    }

    /**
     * @brief Obtains the bright style.
     *
     * @return Returns the bright style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetBrightStyle()
    {
        return brightStyle_;
    }

    /**
     * @brief Obtains the bright color style.
     *
     * @return Returns the bright color style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetBrightColorStyle()
    {
        return brightColorStyle_;
    }

    /**
     * @brief Obtains the button pressed style.
     *
     * @return Returns the button pressed style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetButtonPressedStyle()
    {
        return buttonPressedStyle_;
    }

    /**
     * @brief Obtains the button released style.
     *
     * @return Returns the button released style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetButtonReleasedStyle()
    {
        return buttonReleasedStyle_;
    }

    /**
     * @brief Obtains the button inactived style.
     *
     * @return Returns the button inactived style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetButtonInactivedStyle()
    {
        return buttonInactiveStyle_;
    }

    /**
     * @brief Obtains the label style.
     *
     * @return Returns the label style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetLabelStyle()
    {
        return labelStyle_;
    }

    /**
     * @brief Obtains the background transparent style.
     *
     * @return Returns the background transparent style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetBackgroundTransparentStyle()
    {
        return backgroundTransparentStyle_;
    }

    /**
     * @brief Obtains the progress background style.
     *
     * @return Returns the progress background style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetProgressBackgroundStyle()
    {
        return progressBackgroundStyle_;
    }

    /**
     * @brief Obtains the progress foreground style.
     *
     * @return Returns the progress foreground style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetProgressForegroundStyle()
    {
        return progressForegroundStyle_;
    }

    /**
     * @brief Obtains the slider knob style.
     *
     * @return Returns the slider knob style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetSliderKnobStyle()
    {
        return sliderKnobStyle_;
    }

    /**
     * @brief Obtains the picker background style.
     *
     * @return Returns the picker background style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetPickerBackgroundStyle()
    {
        return pickerBackgroundStyle_;
    }

    /**
     * @brief Obtains the picker highlight style.
     *
     * @return Returns the picker highlight style.
     * @since 1.0
     * @version 1.0
     */
    static Style& GetPickerHighlightStyle()
    {
        return pickerHighlightStyle_;
    }

private:
    static Style defaultStyle_;
    static Style brightStyle_;
    static Style brightColorStyle_;

    static Style buttonPressedStyle_;
    static Style buttonReleasedStyle_;
    static Style buttonInactiveStyle_;
    static Style labelStyle_;
    static Style backgroundTransparentStyle_;
    static Style progressBackgroundStyle_;
    static Style progressForegroundStyle_;
    static Style sliderKnobStyle_;

    static Style pickerBackgroundStyle_;
    static Style pickerHighlightStyle_;

    static void InitStyle();
    static void InitButtonStyle();
    static void InitLabelStyle();
    static void InitBackgroundTransparentStyle();
    static void InitProgressStyle();
    static void InitPickerStyle();
};
} // namespace OHOS
#endif // GRAPHIC_LITE_STYLE_H