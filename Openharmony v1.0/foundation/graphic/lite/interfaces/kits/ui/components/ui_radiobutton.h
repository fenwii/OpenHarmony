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
 * @file ui_radiobutton.h
 *
 * @brief Defines the attributes and common functions of a radio button.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_RADIO_BUTTON_H
#define GRAPHIC_LITE_UI_RADIO_BUTTON_H

#include "components/ui_checkbox.h"

namespace OHOS {
/**
 * @brief Represents a radio button.
 *
 * Only one option can be selected with the radio button.
 *
 * @see UICheckBox
 * @since 1.0
 * @version 1.0
 */
class UIRadioButton : public UICheckBox {
public:
    /**
     * @brief A constructor used to create a <b>UIRadioButton</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIRadioButton();

    /**
     * @fn  UIRadioButton::UIRadioButton(const char* name);
     *
     * @brief   Default constructor
     */
    UIRadioButton(const char* name);

    /**
     * @brief A destructor used to delete the <b>UIRadioButton</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIRadioButton()
    {
        if (name_ != nullptr) {
            UIFree(name_);
            name_ = nullptr;
        }
    }

    /**
     * @brief Obtains the component type.
     *
     * @return Returns the component type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_RADIO_BUTTON;
    }

    /**
     * @fn virtual bool UIRadioButton::OnPreDraw(const Rect& invalidatedArea) override
     *
     * @brief Do something before draw, this function will be invoked mainly to check if this view need
     *        to cover invalidate area so render manager can decide which layer to draw firstly.
     * @param [in] invalidate area.
     * @returns True if need cover.
     */
    bool OnPreDraw(const Rect& invalidatedArea) override
    {
        return false;
    }

    /**
     * @fn  virtual void UIRadioButton::OnClickEvent(const ClickEvent& event) override;
     *
     * @brief   Executes the click event action
     *          OnClickEvent will reverse the selected state of checkbox.
     *          Example: If the check box is selected, the checkbox status is changed to
     *          Unselected after the click action is taken.
     *
     * @param [in] event   The event that passed when OnClickEvent is invoked.
     */
    void OnClickEvent(const ClickEvent& event) override;

    /**
     * @brief Sets the name for this radio button.
     *
     * @param name Indicates the name to set, which is a character string.
     * @since 1.0
     * @version 1.0
     */
    void SetName(const char* name);

    /**
     * @brief Obtains the name of this radio button.
     *
     * @return Returns the name of this radio button, which is a defined character string. Radio buttons sharing the
     * same name are in the same batch from which only one can be selected.
     * @since 1.0
     * @version 1.0
     */
    const char* GetName() const
    {
        return name_;
    }

private:
    char* name_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_RADIO_BUTTON_H

