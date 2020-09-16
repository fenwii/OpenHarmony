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
 * @file ui_label_button.h
 *
 * @brief Declares a label button.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_LABEL_BUTTON_H
#define GRAPHIC_LITE_UI_LABEL_BUTTON_H

#include "common/text.h"
#include "components/ui_button.h"

namespace OHOS {
/**
 * @brief Provides the functions related to a label button.
 *
 * @since 1.0
 * @version 1.0
 */
class UILabelButton : public UIButton {
public:
    /**
      * @brief A constructor used to create a <b>UILabelButton</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UILabelButton();

    /**
     * @brief A destructor used to delete the <b>UILabelButton</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UILabelButton() {}

    /**
     * @brief Draws a label button.
     *
     * @since 1.0
     * @version 1.0
     */
    void OnDraw(const Rect &invalidatedArea) override;

    /**
     * @brief Obtains the view type.
     *
     * @return Returns <b>UI_LABEL_BUTTON</b>, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_LABEL_BUTTON;
    }

    /**
     * @brief Sets the text for this label button.
     *
     * @param text Indicates the pointer to the text.
     * @since 1.0
     * @version 1.0
     */
    void SetText(const char* text)
    {
        labelButtonText_.SetText(text);
    }

    /**
     * @brief Obtains the text of this label button.
     *
     * @return Returns the text.
     * @since 1.0
     * @version 1.0
     */
    const char* GetText() const
    {
        return labelButtonText_.GetText();
    }

    /**
     * @brief Sets the position for this label relative to the button holding it.
     *
     * @param x Indicates the offset distance by which this label is moved on the x-axis.
     * @param y Indicates the offset distance by which this label is moved on the y-axis.
     * @since 1.0
     * @version 1.0
     */
    void SetLablePosition(int16_t x, int16_t y)
    {
        offset_.x = x;
        offset_.y = y;
    }

    /**
     * @brief Obtains the position of this label relative to the button holding it.
     *
     * @return Returns the position of this label.
     * @since 1.0
     * @version 1.0
     */
    Point GetLabelPosition() const
    {
        return offset_;
    }

    /**
     * @brief Sets the alignment mode for this text.
     *
     * @param align Indicates the text alignment mode to set, as defined in {@link UITextLanguageAlignment}.
     * @since 1.0
     * @version 1.0
     */
    void SetAlign(UITextLanguageAlignment align)
    {
        labelButtonText_.SetAlign(align);
    }

    /**
     * @brief Obtains the alignment mode of this text.
     *
     * @return Returns the text alignment mode, as defined in {@link UITextLanguageAlignment}.
     * @since 1.0
     * @version 1.0
     */
    UITextLanguageAlignment GetAlign() const
    {
        return labelButtonText_.GetHorAlign();
    }

    /**
     * @brief Sets the direction for this text.
     *
     * @param direct Indicates the text direction to set, as defined in {@link UITextLanguageDirect}.
     * @since 1.0
     * @version 1.0
     */
    void SetDirect(UITextLanguageDirect direct)
    {
        labelButtonText_.SetDirect(direct);
    }

    /**
     * @brief Obtains the direction of this text.
     *
     * @return Returns the text direction, as defined in {@link UITextLanguageDirect}.
     * @since 1.0
     * @version 1.0
     */
    UITextLanguageDirect GetDirect() const
    {
        return labelButtonText_.GetDirect();
    }

    /**
     * @brief Sets the style for this label.
     *
     * @param labelStyle Indicates the label style to set.
     * @since 1.0
     * @version 1.0
     */
    void SetLabelStyle(Style& labelStyle)
    {
        labelStyle_ = labelStyle;
    }

    /**
     * @brief Sets a style for this label.
     *
     * @param key Indicates the key of the style to set.
     * @param value Indicates the value matching the key.
     * @since 1.0
     * @version 1.0
     */
    void SetLabelStyle(uint8_t key, int64_t value)
    {
        labelStyle_.SetStyle(key, value);
    }

    /**
     * @brief Obtains the style of this label.
     *
     * @return Returns the label style.
     * @since 1.0
     * @version 1.0
     */
    const Style& GetLabelStyle() const
    {
        return labelStyle_;
    }

    /**
     * @brief Obtains the value of a style of this label.
     *
     * @param key Indicates the key of the style.
     * @return Returns the value of the style.
     * @since 1.0
     * @version 1.0
     */
    int64_t GetLabelStyle(uint8_t key) const
    {
        return labelStyle_.GetStyle(key);
    }

    /**
     * @brief Sets the color for this text.
     *
     * @param color Indicates the text color to set.
     * @since 1.0
     * @version 1.0
     */
    void SetTextColor(ColorType color)
    {
        labelStyle_.textColor_ = color;
    }

    /**
     * @brief Sets the font for this text.
     *
     * @param name Indicates the pointer to the font name.
     * @param size Indicates the font size to set.
     * @since 1.0
     * @version 1.0
     */
    void SetFont(const char* name, uint8_t size)
    {
        labelButtonText_.SetFont(name, size);
    }

    /**
     * @brief Sets the font ID.
     *
     * @param fontId Indicates the font ID composed of the font name and size.
     * @since 1.0
     * @version 1.0
     */
    void SetFontId(uint8_t fontId)
    {
        labelButtonText_.SetFontId(fontId);
    }

    /**
     * @brief Obtains the font ID.
     *
     * @return Returns the front ID composed of the font name and size.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetFontId() const
    {
        return labelButtonText_.GetFontId();
    }

protected:
    Text labelButtonText_;

private:
    Style labelStyle_;
    Point offset_; /* Text draw position offset */
};
}  // namespace OHOS
#endif  // GRAPHIC_LITE_UI_LABEL_BUTTON_H
