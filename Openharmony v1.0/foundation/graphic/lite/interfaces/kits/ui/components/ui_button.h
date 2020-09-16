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
 * @file ui_button.h
 *
 * @brief Defines the attributes and common functions of a button.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_BUTTON_H
#define GRAPHIC_LITE_UI_BUTTON_H

#include "common/image.h"
#include "components/ui_view.h"

namespace OHOS {
/**
 * @brief Represents a button.
 *
 * This component responds to the press and release events.
 *
 * @since 1.0
 * @version 1.0
 */
class UIButton : public UIView {
public:
    /**
     * @brief A constructor used to create a <b>UIButton</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIButton();

    /**
     * @brief A constructor used to create a <b>UIButton</b> instance based on the button ID.
     *
     * Buttons sharing the same ID are in the same batch.
     *
     * @param id Indicates the button ID.
     * @since 1.0
     * @version 1.0
     */
    UIButton(const char* id) : UIButton()
    {
        id_ = id;
    }

    /**
     * @brief A destructor used to delete the <b>UIButton</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIButton();

    /**
     * @brief Obtains the component type.
     *
     * @return Returns the component type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_BUTTON;
    }

    /**
     * @fn virtual bool UIButton::OnPreDraw(const Rect& invalidatedArea) override
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
     * @fn  virtual void UIButton::OnDraw(const Rect& invalidatedArea) override;
     *
     * @brief   Executes the draw action
     *
     * @param   [in] invalidatedArea The rectangle to draw, with coordinates relative to this drawable..
     */
    void OnDraw(const Rect& invalidatedArea) override;

    /**
     * @fn  virtual void UIButton::OnPressEvent(const PressEvent& event) override;
     *
     * @brief   Executes the press event action
     *
     * @param   [in] event   The press event, contain press position.
     */
    void OnPressEvent(const PressEvent& event) override;

    /**
     * @fn  virtual void UIButton::OnReleaseEvent(const ReleaseEvent& event) override;
     *
     * @brief   Executes the press release event action
     *
     * @param   [in] event   The press release event.
     */
    void OnReleaseEvent(const ReleaseEvent& event) override;

    /**
     * @fn  virtual void UIButton::OnCancelEvent(const CancelEvent& event) override;
     *
     * @brief   Executes the cancel event action
     *
     * @param   [in] event   The cancel event.
     */
    void OnCancelEvent(const CancelEvent& event) override;

    /**
     * @brief Enumerates the images for different button states.
     *
     * You can define a different image for each button state.
     *
     * @since 1.0
     * @version 1.0
     */
    enum ButtonImageSrc : uint8_t {
        /* An enum constant representing the Button image default option */
        BTN_IMAGE_DEFAULT,
        /* An enum constant representing the Button image triggered option */
        BTN_IMAGE_TRIGGERED,
        /* An enum constant representing the Button Image Number option */
        BTN_IMG_NUM,
    };

    /**
     * @brief Sets the image for this button.
     *
     * @param defaultImgSrc Indicates the default image.
     * @param triggeredImgSrc Indicates the image for a button when it is triggered.
     * @since 1.0
     * @version 1.0
     */
    void SetImageSrc(const char* defaultImgSrc, const char* triggeredImgSrc);

    /**
     * @brief Sets the image for this button.
     *
     * @param defaultImgSrc Indicates the default image.
     * @param triggeredImgSrc Indicates the image for a button when it is triggered.
     * @since 1.0
     * @version 1.0
     */
    void SetImageSrc(const ImageInfo* defaultImgSrc, const ImageInfo* triggeredImgSrc);

    /**
     * @brief Sets the position for this image.
     *
     * @param x Indicates the x-coordinate to set.
     * @param y Indicates the y-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    void SetImagePosition(const int16_t x, const int16_t y)
    {
        imgX_ = x;
        imgY_ = y;
    }

    /**
     * @brief Obtains the x-coordinate of this image.
     *
     * @return Returns the x-coordinate of this image.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetImageX() const
    {
        return imgX_;
    }

    /**
     * @brief Obtains the y-coordinate of this image.
     *
     * @return Returns the y-coordinate of this image.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetImageY() const
    {
        return imgY_;
    }

    /**
     * @brief Obtains the image for the current button state.
     *
     * @return Returns the image for the current button state.
     * @since 1.0
     * @version 1.0
     */
    const Image* GetCurImageSrc() const;

    /**
     * @brief Enumerates the states of this button.
     *
     * The button has three states.
     *
     * @since 1.0
     * @version 1.0
     */
    enum ButtonState : uint8_t {
        /* An enum constant representing the Button state released option */
        RELEASED = 0,
        /* An enum constant representing the Button state pressed option */
        PRESSED,
        /* An enum constant representing the Button state inactive option */
        INACTIVE,
        /* An enum constant representing the Button state Number option */
        BTN_STATE_NUM,
    };

    /**
     * @brief Obtains the width of this image.
     *
     * @return Returns the image width.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetWidth() override
    {
        Style* style = buttonStyles_[state_];
        return GetRelativeRect().GetWidth() - (style->paddingLeft_ + style->paddingRight_) -
            (style->borderWidth_ * 2); /* 2: left and right border */
    }

    /**
     * @brief Obtains the height of this image.
     *
     * @return Returns the image height.
     * @since 1.0
     * @version 1.0
     */
    int16_t GetHeight() override
    {
        Style* style = buttonStyles_[state_];
        return GetRelativeRect().GetHeight() - (style->paddingTop_ + style->paddingBottom_) -
            (style->borderWidth_ * 2); /* 2: top and bottom border */
    }

    /**
     * @brief Sets the width for this image.
     *
     * @param width Indicates the width to set.
     * @since 1.0
     * @version 1.0
     */
    void SetWidth(int16_t width) override
    {
        contentWidth_ = width;
        Style* style = buttonStyles_[state_];
        UIView::SetWidth(width + (style->paddingLeft_ + style->paddingRight_) +
            (style->borderWidth_ * 2)); /* 2: left and right border */
    }

    /**
     * @brief Sets the height for this image.
     *
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    void SetHeight(int16_t height) override
    {
        contentHeight_ = height;
        Style* style = buttonStyles_[state_];
        UIView::SetHeight(height + (style->paddingTop_ + style->paddingBottom_) +
            (style->borderWidth_ * 2)); /* 2: top and bottom border */
    }

    /**
     * @brief Obtains a rectangular area that contains coordinate information.
     *
     * @return Returns the rectangle area.
     * @since 1.0
     * @version 1.0
     */
    virtual Rect GetContentRect() override
    {
        Rect contentRect;
        Style* style = buttonStyles_[state_];
        contentRect.SetX(GetRect().GetX() + style->paddingLeft_ + style->borderWidth_);
        contentRect.SetY(GetRect().GetY() + style->paddingTop_ + style->borderWidth_);
        contentRect.SetWidth(GetWidth());
        contentRect.SetHeight(GetHeight());
        return contentRect;
    }

    /**
     * @brief Obtains the value of a style.
     *
     * @param key Indicates the key of the style.
     * @return Returns the value of the style.
     * @since 1.0
     * @version 1.0
     */
    int64_t GetStyle(uint8_t key) const override;

    /**
     * @brief Sets a style.
     *
     * @param key Indicates the key of the style to set.
     * @param value Indicates the value matching the key.
     * @since 1.0
     * @version 1.0
     */
    void SetStyle(uint8_t key, int64_t value) override;

    /**
     * @brief Obtains the style of a button in a specific state.
     *
     * @param key Indicates the key of the style.
     * @param state Indicates the button state, as enumerated in {@link ButtonState}.
     * @return Returns the style of the button in the specific state.
     * @since 1.0
     * @version 1.0
     */
    int64_t GetStyleForState(uint8_t key, ButtonState state) const;

    /**
     * @brief Sets the style for a button in a specific state.
     *
     * @param key Indicates the key of the style to set.
     * @param value Indicates the value matching the key.
     * @param state Indicates the button state, as enumerated in {@link ButtonState}.
     * @since 1.0
     * @version 1.0
     */
    void SetStyleForState(uint8_t key, int64_t value, ButtonState state);

    /**
     * @brief Disables this button.
     *
     * @since 1.0
     * @version 1.0
     */
    void Disable();

    /**
     * @brief Enables this button.
     *
     * @since 1.0
     * @version 1.0
     */
    void Enable();

    /**
     * @brief Sets the state for a button. After the setting, calling {@link SetStyle}
     *        will change the style of this button, but not its state.
     *
     * @param state Indicates the button state, as enumerated in {@link ButtonState}.
     * @since 1.0
     * @version 1.0
     */
    void SetStateForStyle(ButtonState state)
    {
        styleState_ = state;
    }

protected:
    Image* defaultImgSrc_;
    Image* triggeredImgSrc_;
    ButtonImageSrc currentImgSrc_;
    int16_t imgX_;
    int16_t imgY_;
    int16_t contentWidth_;
    int16_t contentHeight_;
    void SetState(ButtonState state);

    ButtonState state_;
    ButtonState styleState_;
    Style* buttonStyles_[BTN_STATE_NUM];
    bool buttonStyleAllocFlag_;

private:
    /** Sets up the theme styles */
    void SetupThemeStyles();

    void DrawImg(const Rect& invalidatedArea);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_BUTTON_H

