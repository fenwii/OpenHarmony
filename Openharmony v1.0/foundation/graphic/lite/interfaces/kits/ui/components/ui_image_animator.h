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
 * @file ui_image_animator.h
 *
 * @brief Defines the attributes and functions of an image animator.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_IMAGE_ANIMATOR_H
#define GRAPHIC_LITE_UI_IMAGE_ANIMATOR_H

#include "animator/animator.h"
#include "components/ui_image_view.h"

namespace OHOS {
/**
 * @brief Provides information about the images.
 */
struct ImageAnimatorInfo {
    /** Image path or pointer to the {@link ImageInfo} structure */
    const char* imageInfo;
    /** Image start position, relative to this view */
    Point pos;
    /** Image width */
    int16_t width;
    /** Image height */
    int16_t height;
};

/**
 * @brief Represents an image animator.
 *
 * Images are switched at a specified interval to form an animator.
 *
 * @see UIImageView
 * @since 1.0
 * @version 1.0
 */
class UIImageAnimatorView : public UIImageView {
public:
    /**
     * @brief A constructor used to create a <b>UIImageAnimatorView</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIImageAnimatorView();

    /**
     * @brief A destructor used to delete the <b>UIImageAnimatorView</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIImageAnimatorView();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type, as defined in {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_IMAGE_ANIMATOR_VIEW;
    }

    /**
     * @brief Sets the images and speed for this animator.
     *
     * @param imageSrc Indicates the pointer to the {@link ImageAnimatorInfo} array for storing the configured
     *                 image information. The memory cannot be released before this animator stops.
     * @param imageNum Indicates the number of images.
     * @param timeOfUpdate Indicates the interval for updating images, in milliseconds. The default value is <b>1</b>.
     * @see GetTimeOfUpdate | GetImageAnimatorSrc | GetImageAnimatorImageNum
     * @since 1.0
     * @version 1.0
     */
    void SetImageAnimatorSrc(const char* imageSrc, uint8_t imageNum, uint16_t timeOfUpdate);

    /**
     * @brief Sets the images for this animator.
     *
     * @param imageSrc Indicates the pointer to the {@link ImageAnimatorInfo} array for storing the configured
     *                 image information. The memory cannot be released before this animator stops.
     * @param imageNum Indicates the number of images.
     * @see GetImageAnimatorSrc | GetImageAnimatorImageNum
     * @since 1.0
     * @version 1.0
     */
    void SetImageAnimatorSrc(const char* imageSrc, uint8_t imageNum);

    /**
     * @brief Sets the speed for this animator.
     *
     * @param timeOfUpdate Indicates the interval for updating images, in milliseconds. The default value is <b>1</b>.
     * @see GetTimeOfUpdate
     * @since 1.0
     * @version 1.0
     */
    void SetTimeOfUpdate(uint16_t timeOfUpdate);

    /**
     * @brief Obtains the speed of this animator.
     *
     * @return Returns the interval for updating images, in milliseconds.
     * @see SetTimeOfUpdate
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetTimeOfUpdate() const;

    /**
     * @brief Sets the interval between two playbacks of an infinitely repeated animator.
     *
     * @param timeOfPause Indicates the interval between two playbacks of an infinitely repeated animator, in
     *                    milliseconds. The default value is <b>0</b>, indicating that there is no interval.
     * @see GetTimeOfPause
     * @since 1.0
     * @version 1.0
     */
    void SetTimeOfPause(uint16_t timeOfPause);

    /**
     * @brief Obtains the interval between two playbacks of an infinitely repeated animator.
     *
     * @return Returns the interval between two playbacks, in milliseconds.
     * @see SetTimeOfPause
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetTimeOfPause() const;

    /**
     * @brief Obtains the image array of this frame animator.
     *
     * @return Returns a pointer to the {@link ImageAnimatorInfo} array if the operation is successful;
     *         returns <b>nullptr</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    const ImageAnimatorInfo* GetImageAnimatorSrc() const;

    /**
     * @brief Obtains the number of images.
     *
     * @return Returns the number of images.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetImageAnimatorImageNum() const;

    /**
     * @brief Sets whether the image size is fixed to the view size.
     *
     * @param fixed Specifies whether the image size is fixed to the view size. The value <b>true</b> indicates
     *              the size of the image is the same as that of the view, and <b>false</b> indicates the
     *              position and size of this image need to be set in the {@link ImageAnimatorInfo} structure.
     * @see IsSizeFixed
     * @since 1.0
     * @version 1.0
     */
    void SetSizeFixed(bool fixed)
    {
        sizeFixed_ = fixed;
    }

    /**
     * @brief Checks whether the image size is fixed to the view size.
     *
     * @return Returns <b>true</b> if the image size is fixed to the view size;
     *         returns <b>false</b> if the image size is set independently.
     * @see SetSizeFixed
     * @since 1.0
     * @version 1.0
     */
    bool IsSizeFixed() const
    {
        return sizeFixed_;
    }

    /**
     * @brief Sets whether to play this animator for infinite times.
     *
     * @param repeat Specifies whether the animator is played for infinite times. <b>true</b> (default value)
     *               indicates the animator is played for infinite times, and <b>false</b> indicates the animator
     *               is played a specified number of times.
     * @see IsRepeat
     * @since 1.0
     * @version 1.0
     */
    void SetRepeat(bool repeat)
    {
        repeat_ = repeat;
    }

    /**
     * @brief Checks whether this animator is played for infinite times.
     *
     * @return Returns <b>true</b> if this animator is played for infinite times, returns <b>false</b> if the
     *         animator is played a specified number of times.
     * @see SetRepeat
     * @since 1.0
     * @version 1.0
     */
    bool IsRepeat() const
    {
        return repeat_;
    }

    /**
     * @brief Sets the playback times for this animator.
     *
     * This function takes effect only when <b>repeat</b> is set to <b>false</b> in {@link SetRepeat}.
     *
     * @param times Indicates the playback times to set. The default value is <b>1</b>.
     * @see GetRepeatTimes
     * @since 1.0
     * @version 1.0
     */
    void SetRepeatTimes(uint32_t times)
    {
        repeatTimes_ = times;
    }

    /**
     * @brief Obtains the playback times.
     *
     * @return Returns the playback times.
     * @see SetRepeatTimes
     * @since 1.0
     * @version 1.0
     */
    uint32_t GetRepeatTimes() const
    {
        return repeatTimes_;
    }

    /**
     * @brief Obtains the current state of this animator.
     *
     * @return Returns the current state, which can be {@link START}, {@link STOP}, or {@link PAUSE}.
     *         For details, see {@link Animator}.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetState() const
    {
        return imageAnimator_.GetState();
    }

    /**
     * @brief Sets the playback sequence for this animator.
     *
     * @param reverse Indicates the playback sequence to set. <b>true</b> indicates a reverse playback
     *                and <b>false</b> (default value) indicates a forward playback.
     * @see IsReverse
     * @since 1.0
     * @version 1.0
     */
    void SetReverse(bool reverse)
    {
        reverse_ = reverse;
    }

    /**
     * @brief Obtains the playback sequence of this animator.
     *
     * @return Returns <b>true</b> if a reverse playback is performed;
     *         returns <b>false</b> if a forward playback is performed.
     * @see SetReverse
     * @since 1.0
     * @version 1.0
     */
    bool IsReverse() const
    {
        return reverse_;
    }

    /**
     * @brief Starts this animator.
     *
     * The forward playback starts from the first image and the reverse playback starts from the last image.
     *
     * @see Stop
     * @since 1.0
     * @version 1.0
     */
    void Start();

    /**
     * @brief Stops this animator.
     *
     * @param needReset Specifies whether the animator needs to be reset to the original one.
     *                  <b>true</b> (default value) indicates the original image is displayed,
     *                  and <b>false</b> indicates the current image is displayed.
     * @see Start
     * @since 1.0
     * @version 1.0
     */
    void Stop(bool needReset = true);

    /**
     * @brief Pauses this animator at the current image.
     *
     * @see Resume
     * @since 1.0
     * @version 1.0
     */
    void Pause()
    {
        imageAnimator_.SetState(Animator::PAUSE);
    }

    /**
     * @brief Resumes this animator from the current image.
     *
     * @see Pause
     * @since 1.0
     * @version 1.0
     */
    void Resume()
    {
        imageAnimator_.SetState(Animator::START);
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
         * @brief Called when this animator stops.
         *
         * You need to inherit from the <b> AnimatorStopListener</b> class and implement this function.
         *
         * @param view Indicates the instance of this view.
         * @since 1.0
         * @version 1.0
         */
        virtual void OnAnimatorStop(UIView& view) {}
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

protected:
    class ImageAnimatorCallback : public AnimatorCallback {
    public:
        ImageAnimatorCallback()
            : tickNum_(0), loop_(1), drawingImage_(0), repeat_(0),
            imageSrc_(nullptr), imageNum_(0)
        {
        };

        virtual ~ImageAnimatorCallback() {}

        virtual void Callback(UIView* view) override;

        void Reset()
        {
            tickNum_ = 0;
            loop_ = 1;
            repeat_ = 0;
        }

    protected:
        uint16_t tickNum_;
        uint8_t loop_;
        uint8_t drawingImage_;
        uint32_t repeat_;
        const ImageAnimatorInfo* imageSrc_;
        uint8_t imageNum_;
    };

    void Reset();
    void UpdateImage(uint8_t& drawingImage, uint8_t& loop);
    uint8_t GetTickByTime(uint16_t time) const;
    ImageAnimatorInfo* imageSrc_;
    uint8_t imageNum_;
    uint8_t tickOfUpdate_;
    uint16_t timeOfUpdate_;
    uint16_t timeOfPause_;
    uint8_t tickOfPause_;
    uint32_t repeatTimes_;
    Animator imageAnimator_;
    ImageAnimatorCallback imageAnimatorCallback_;
    AnimatorStopListener* listener_;
    bool reverse_;
    bool repeat_;
    bool sizeFixed_;
};
}
#endif // GRAPHIC_LITE_UI_IMAGE_ANIMATOR_H
