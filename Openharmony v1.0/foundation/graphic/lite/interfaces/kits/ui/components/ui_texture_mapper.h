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
 * @file ui_texture_mapper.h
 *
 * @brief Defines the attributes and functions of a texture mapper.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_TEXTURE_MAPPER_H
#define GRAPHIC_LITE_UI_TEXTURE_MAPPER_H

#include "components/ui_image_view.h"
#include "animator/animator.h"
#include "animator/easing_equation.h"

namespace OHOS {
/**
 * @brief Rotates and scales images.
 *
 * @see UIImageView
 * @since 1.0
 * @version 1.0
 */
class UITextureMapper : public UIImageView {
public:
    /**
     * @brief A constructor used to create a <b>UITextureMapper</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UITextureMapper();

    /**
     * @brief A destructor used to delete the <b>UITextureMapper</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UITextureMapper();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_TEXTURE_MAPPER;
    }

    /**
     * @brief Starts this animator.
     *
     * @since 1.0
     * @version 1.0
     */
    void Start();

    /**
     * @brief Sets the start angle of rotation for this image.
     *
     * By default, the image starts to rotate from the current angle of this stopped animator.
     *
     * @param start Indicates the start angle to set. The default value is <b>0</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetRotateStart(int16_t start)
    {
        rotateCur_ = start;
    }

    /**
     * @brief Sets the end angle of rotation for this image.
     *
     * @param end Indicates the end angle of rotation to set. The default value is <b>0</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetRotateEnd(int16_t end)
    {
        rotateEnd_ = end;
    }

    /**
     * @brief Sets the start ratio for scaling this image.
     *
     * By default, the image starts to scale from the current ratio of this stopped animator. \n
     * The X and Y directions are scaled at the same ratio. Single-direction scaling is not supported. \n
     *
     * @param start Indicates the start ratio to set. The default value is <b>1</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetScaleStart(float start)
    {
        scaleCur_ = static_cast<int16_t>(FloatToInt64(start));
    }

    /**
     * @brief Sets the end ratio for scaling this image.
     *
     * @param end Indicates the end ratio to set. The default value is <b>1</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetScaleEnd(float end)
    {
        scaleEnd_ = static_cast<int16_t>(FloatToInt64(end));
    }

    /**
     * @brief Sets the duration for this animator, in milliseconds.
     *
     * The durations of image scaling and rotation are the same and cannot be set separately.
     *
     * @param durationTime Indicates the duration to set.
     * @since 1.0
     * @version 1.0
     */
    void SetDurationTime(uint16_t durationTime)
    {
        animator_.SetTime(durationTime);
    }

    /**
     * @brief Sets the delay time for this animator, in milliseconds.
     *
     * The delays of image scaling and rotation are the same and cannot be set separately.
     *
     * @param delayTime Indicates the delay time to set.
     * @since 1.0
     * @version 1.0
     */
    void SetDelayTime(uint16_t delayTime)
    {
        delayTime_ = delayTime;
    }

    /**
     * @brief Sets the easing function for this animator.
     *
     * The easing functions for image scaling and rotation are the same and cannot be set separately.
     *
     * @param easingFunc Indicates the easing function to set. The animation moves at a constant velocity by default.
     *                   For details, see {@link EasingEquation}.
     * @since 1.0
     * @version 1.0
     */
    void SetEasingFunc(EasingFunc easingFunc)
    {
        easingFunc_ = easingFunc;
    }

    /**
     * @brief Cancels this animator.
     *
     * After being cancelled, the animator will stop in the current playback state.
     *
     * @since 1.0
     * @version 1.0
     */
    void Cancel();

    /**
     * @brief Displays the original image.
     *
     * The configured parameters are reserved and will not be reset.
     *
     * @since 1.0
     * @version 1.0
     */
    void Reset();

    /**
     * @brief Sets the coordinates of the rotation and scaling pivots for this image.
     *
     * The coordinates represent the position relative to this image. For example, setting the x-coordinate and
     * y-coordinate of the rotation or scaling center to the half of the image width and height respectively
     * means the rotation or scaling is going to be performed around the center of this image.
     *
     * @param x Indicates the x-coordinate to set.
     * @param y Indicates the y-coordinate to set.
     * @since 1.0
     * @version 1.0
     */
    void SetPivot(int16_t x, int16_t y)
    {
        pivot_.x_ = x;
        pivot_.y_ = y;
    }

    /**
     * @brief Represents a listener that contains a callback to be invoked when this animator stops.
     *
     * @since 1.0
     * @version 1.0
     */
    class AnimatorStopListener : public HeapBase {
    public:
        /**
         * @brief A destructor used to delete an <b>AnimatorStopListener</b> instance.
         *
         * @since 1.0
         * @version 1.0
         */
        virtual ~AnimatorStopListener() {}

        /**
         * @brief Called when this animator stops. This is a pure virtual function, which needs
         *        your inheritance and implementation.
         *
         * @param view Indicates the instance of this view.
         * @since 1.0
         * @version 1.0
         */
        virtual void OnAnimatorStop(UIView& view) = 0;
    };

    /**
     * @brief Sets the listener for the stop of this animator.
     *
     * @param listener Indicates the listener to set. For details, see {@link AnimatorStopListener}.
     * @since 1.0
     * @version 1.0
     */
    void SetAnimatorStopListener(AnimatorStopListener* listener)
    {
        listener_ = listener;
    }

private:
    class TextureMapperAnimatorCallback : public AnimatorCallback {
    public:
        virtual ~TextureMapperAnimatorCallback() {}

        void Callback(UIView* view) override;

        void OnStop(UIView& view) override;
    };

    static constexpr int16_t SCALE_CONVERTION = 256;

    void Callback();

    TextureMapperAnimatorCallback animatorCallback_;
    Animator animator_;
    AnimatorStopListener* listener_;

    Vector2<int16_t> pivot_;
    int16_t rotateCur_;
    int16_t rotateStart_;
    int16_t rotateEnd_;
    int16_t scaleCur_;
    int16_t scaleStart_;
    int16_t scaleEnd_;
    uint16_t delayTime_;
    EasingFunc easingFunc_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_UI_TEXTURE_MAPPER_H
