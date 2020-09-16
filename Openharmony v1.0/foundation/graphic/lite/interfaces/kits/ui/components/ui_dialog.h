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
 * @file ui_dialog.h
 *
 * @brief Declares the UIDialog class that defines the dialog box component.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_DIALOG_H
#define GRAPHIC_LITE_UI_DIALOG_H

#include "components/root_view.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"

namespace OHOS {
/**
 * @brief Represents a dialog box.
 *
 * A dialog box displays information for user input.
 * After a button is clicked in the dialog box, the corresponding callback event is triggered.
 *
 * @since 1.0
 * @version 1.0
 */
class UIDialog : public UIViewGroup {
public:
    /**
     * @brief A constructor used to create a <b>UIDialog</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIDialog();

    /**
     * @brief A destructor used to delete the <b>UIDialog</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIDialog();

    /**
     * @brief Enumerates buttons in a dialog box.
     *
     * @since 1.0
     * @version 1.0
     */
    enum class DialogButtonType {
        /** First button */
        BUTTON1,
        /** Second button */
        BUTTON2,
        /** Third button */
        BUTTON3,
    };

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_DIALOG;
    }

    /**
     * @brief Sets the title for this dialog box.
     *
     * @param title Indicates the pointer to the title.
     * @since 1.0
     * @version 1.0
     */
    void SetTitle(const char* title);

    /**
     * @brief Sets the text for this dialog box.
     *
     * @param text Indicates the pointer to the text.
     * @since 1.0
     * @version 1.0
     */
    void SetText(const char* text);

    /**
     * @brief Checks whether this label needs to be covered before drawing it.
     *
     * @param invalidatedArea Indicates the area to draw.
     * @return Returns <b>true</b> if this label needs to be covered; returns <b> false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool OnPreDraw(const Rect& invalidatedArea) override
    {
        return false;
    }

    /**
     * @brief Sets a button for this dialog box.
     *
     * @param buttonType Indicates the button position.
     * @param text Indicates the pointer to the button text.
     * @param listener Indicates the pointer to the listener registered for the button.
     * @since 1.0
     * @version 1.0
     */
    void SetButton(DialogButtonType buttonType, const char* text, OnClickListener* listener);

    /**
     * @brief Sets whether a dialog box is visible.
     *
     * @param visible Specifies whether a dialog box is visible. The value <b>true</b> means visible,
     *                and <b>false</b> means invisible.
     * @since 1.0
     * @version 1.0
     */
    void SetVisible (bool visible) override;

private:
    const static uint16_t BUTTON_MIN_WIDTH = 100;
    const static uint16_t BUTTON_HEIGHT = 36;
    const static uint16_t PADDING = 24;
    const static uint8_t TITLE_SMALL_FONT_SIZE = 18;
    const static uint8_t TITLE_LARGE_FONT_SIZE = 20;
    const static uint8_t TEXT_FONT_SIZE = 18;
    const static uint8_t BUTTON_FONT_SIZE = 14;
    const static uint8_t MAX_WIDTH_PERCENT = 80;
    const static uint8_t MAX_HEIGHT_PERCENT = 80;
    const static uint8_t DIALOG_RADIUS = 18;
    constexpr static const char* DEFAULT_FONT = "HYQiHei-65S";

    void AddButton(DialogButtonType buttonType, UILabelButton* button, const char* text, OnClickListener* listener);
    void MeasureTitle();
    void MeasureText();
    void MeasureButton();
    void ReMeasureSize();
    void ReMoveButton();
    void ReLayout();

    uint8_t buttonNum_;
    UILabel* title_;
    UILabel* text_;
    UIView maskLayer_;
    UIViewGroup dialogLayer_;
    UILabelButton* button1_;
    UILabelButton* button2_;
    UILabelButton* button3_;
    uint16_t widthMax_;
    uint16_t heightMax_;
    uint16_t buttonWidth_;
};
}
#endif // GRAPHIC_LITE_UI_DIALOG_H