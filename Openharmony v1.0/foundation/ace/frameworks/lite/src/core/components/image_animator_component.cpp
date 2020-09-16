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
#include "image_animator_component.h"
#include "ace_log.h"
#include "handler.h"
#include "key_parser.h"
#include "keys.h"
#include "time_util.h"

namespace OHOS {
namespace ACELite {
constexpr char ITR_INFINITE[] = "infinite";
constexpr char FUNC_START[] = "start";
constexpr char FUNC_PAUSE[] = "pause";
constexpr char FUNC_RESUME[] = "resume";
constexpr char FUNC_STOP[] = "stop";
constexpr char FUNC_GET_STATE[] = "getState";
constexpr char STATUS_PLAYING[] = "playing";
constexpr char STATUS_PAUSED[] = "paused";
constexpr char STATUS_STOPED[] = "stopped";

ImageAnimatorComponent::ImageAnimatorComponent(jerry_value_t options,
                                               jerry_value_t children,
                                               AppStyleManager *styleManager)
    : Component(options, children, styleManager),
      viewGroup_(nullptr),
      imageAnimator_(nullptr),
      onStopListener_(nullptr),
      frames_(nullptr),
      duration_(nullptr),
      framesSize_(0)
{
    SetComponentName(K_IMAGE_ANIMATOR);
    RegisterNamedFunction(FUNC_START, StartAnimator);
    RegisterNamedFunction(FUNC_PAUSE, PauseAnimator);
    RegisterNamedFunction(FUNC_RESUME, ResumeAnimator);
    RegisterNamedFunction(FUNC_STOP, StopAnimator);
    RegisterNamedFunction(FUNC_GET_STATE, GetAnimatorState);
}

bool ImageAnimatorComponent::CreateNativeViews()
{
    viewGroup_ = new UIViewGroup();

    if (viewGroup_ == nullptr) {
        return false;
    }
    viewGroup_->SetStyle(STYLE_BACKGROUND_OPA, OPA_TRANSPARENT);
    imageAnimator_ = new UIImageAnimatorView();

    if (imageAnimator_ == nullptr) {
        delete (viewGroup_);
        viewGroup_ = nullptr;
        return false;
    }

    viewGroup_->Add(imageAnimator_);
    imageAnimator_->SetRepeat(true);
    imageAnimator_->SetReverse(false);
    imageAnimator_->SetSizeFixed(true);
    return true;
}

void ImageAnimatorComponent::ReleaseNativeViews()
{
    ReleaseFrame();
    ACE_FREE(duration_);
    ACE_DELETE(viewGroup_);
    ACE_DELETE(imageAnimator_);
    ACE_DELETE(onStopListener_);
}

inline UIView *ImageAnimatorComponent::GetComponentRootView() const
{
    return viewGroup_;
}

bool ImageAnimatorComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    switch (attrKeyId) {
        case K_FIXED_SIZE:
            return ParseToFixedSize(attrValue);
        case K_IMAGES:
            return ParseToFrames(attrValue);
        case K_ITERATION:
            return ParseToIteration(attrValue);
        case K_REVERSE:
            return ParseToReverse(attrValue);
        case K_DURATION:
            return ParseToDuration(attrValue);
        default:
            return false;
    }
}

void ImageAnimatorComponent::PostRender()
{
    UpdateAnimator();
}

void ImageAnimatorComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    if ((K_IMAGES == attrKeyId) || (K_DURATION == attrKeyId)) {
        UpdateAnimator();
    }
}

bool ImageAnimatorComponent::RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    if (eventTypeId == K_STOP) {
        onStopListener_ = new ImageAnimatorStopListener(funcValue);
        if (onStopListener_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "Failed to register stop event listener.");
            return false;
        }
        imageAnimator_->SetAnimatorStopListener(onStopListener_);
        return true;
    }

    return false;
}

bool ImageAnimatorComponent::ParseToFixedSize(jerry_value_t value) const
{
    if (!jerry_value_is_boolean(value)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "fixedsize is not a boolean value.");
        return false;
    }
    imageAnimator_->SetSizeFixed(jerry_get_boolean_value(value));
    return true;
}

void ImageAnimatorComponent::ReleaseFrame()
{
    if (frames_ == nullptr) {
        return;
    }

    for (uint8_t idx = 0; idx < framesSize_; ++idx) {
        ImageAnimatorInfo frame = frames_[idx];
        if (frame.imageInfo != nullptr) {
            ace_free(const_cast<char *>(frame.imageInfo));
            frame.imageInfo = nullptr;
        }
    }
    ACE_FREE(frames_);
}

bool ImageAnimatorComponent::ParseToFrames(jerry_value_t value)
{
    ReleaseFrame();
    if (!jerry_value_is_array(value)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "images is not a array value.");
        return false;
    }
    framesSize_ = jerry_get_array_length(value);
    if (framesSize_ == 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "images is empty.");
        return false;
    }
    if (framesSize_ > UINT8_MAX) {
        framesSize_ = UINT8_MAX;
    }

    frames_ = static_cast<ImageAnimatorInfo *>(ace_malloc(sizeof(ImageAnimatorInfo) * framesSize_));
    if (frames_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "fail to set images cause by out of memory.");
        return false;
    }
    for (uint16_t idx = 0; idx < framesSize_; ++idx) {
        jerry_value_t image = jerry_get_property_by_index(value, idx);
        if (jerry_value_is_undefined(image) || !jerry_value_is_object(image)) {
            HILOG_WARN(HILOG_MODULE_ACE, "the %d frame is null or not a object.", idx);
            continue;
        }

        jerry_value_t src = jerryx_get_property_str(image, ATTR_SRC);
        if (jerry_value_is_undefined(src)) {
            jerry_release_value(image);
            HILOG_WARN(HILOG_MODULE_ACE, "the src of %d frame is null.", src);
            continue;
        }

        ImageAnimatorInfo frame = {0};
        frame.imageInfo = ParseImageSrc(src);
        jerry_release_value(src);
        frame.width = JerryGetIntegerProperty(image, ATTR_WIDTH);
        frame.height = JerryGetIntegerProperty(image, ATTR_HEIGHT);
        Point point = {0};
        point.x = JerryGetIntegerProperty(image, ATTR_LEFT);
        point.y = JerryGetIntegerProperty(image, ATTR_TOP);
        frame.pos = point;
        jerry_release_value(image);
        frames_[idx] = frame;
    }
    return true;
}

bool ImageAnimatorComponent::ParseToIteration(jerry_value_t value) const
{
    uint16_t length = 0;
    char *iteration = MallocStringOf(value, &length);
    if (iteration == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "fail to set iteration cause by out of memory.");
        return false;
    }

    if (length == 0 || !strcmp(iteration, ITR_INFINITE)) {
        imageAnimator_->SetRepeat(true);
    } else {
        imageAnimator_->SetRepeat(false);
        imageAnimator_->SetRepeatTimes(strtol(iteration, nullptr, DEC));
    }

    ace_free(iteration);
    iteration = nullptr;
    return true;
}

bool ImageAnimatorComponent::ParseToReverse(jerry_value_t value) const
{
    if (!jerry_value_is_boolean(value)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "reverse is not a boolean value.");
        return false;
    }
    imageAnimator_->SetReverse(jerry_get_boolean_value(value));
    return true;
}

bool ImageAnimatorComponent::ParseToDuration(jerry_value_t value)
{
    ACE_FREE(duration_);
    uint16_t length = 0;
    duration_ = MallocStringOf(value, &length);
    if (length == 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "fail to set duration cause by out of memory");
        ACE_FREE(duration_);
        return false;
    }
    return true;
}

void ImageAnimatorComponent::UpdateAnimator() const
{
    if (frames_ != nullptr && framesSize_ != 0 && duration_ != nullptr) {
        imageAnimator_->SetImageAnimatorSrc(reinterpret_cast<const char *>(frames_), framesSize_);

        int32_t millions = ParseToMilliseconds(duration_);
        uint16_t timeOfUpdate = 0;
        if (millions > 0) {
            timeOfUpdate = static_cast<uint16_t>(millions / framesSize_);
            if (timeOfUpdate == 0) {
                timeOfUpdate = DEFAULT_TASK_PERIOD;
            }
        }
        imageAnimator_->SetTimeOfUpdate(timeOfUpdate);
        imageAnimator_->Start();
    }
}

jerry_value_t ImageAnimatorComponent::StartAnimator(const jerry_value_t func,
                                                    const jerry_value_t dom,
                                                    const jerry_value_t args[],
                                                    const jerry_length_t size)
{
    ImageAnimatorComponent *component =
        static_cast<ImageAnimatorComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to get DOM.");
        return UNDEFINED;
    }
    UIImageAnimatorView *animator = component->GetImageAnimator();

    if (animator != nullptr) {
        animator->Start();
    }

    return UNDEFINED;
}
jerry_value_t ImageAnimatorComponent::PauseAnimator(const jerry_value_t func,
                                                    const jerry_value_t dom,
                                                    const jerry_value_t args[],
                                                    const jerry_length_t size)
{
    ImageAnimatorComponent *component =
        static_cast<ImageAnimatorComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to get DOM.");
        return UNDEFINED;
    }
    UIImageAnimatorView *animator = component->GetImageAnimator();

    if (animator != nullptr) {
        animator->Pause();
    }

    return UNDEFINED;
}
jerry_value_t ImageAnimatorComponent::ResumeAnimator(const jerry_value_t func,
                                                     const jerry_value_t dom,
                                                     const jerry_value_t args[],
                                                     const jerry_length_t size)
{
    ImageAnimatorComponent *component =
        static_cast<ImageAnimatorComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to get DOM.");
        return UNDEFINED;
    }
    UIImageAnimatorView *animator = component->GetImageAnimator();

    if (animator != nullptr) {
        animator->Resume();
    }

    return UNDEFINED;
}
jerry_value_t ImageAnimatorComponent::StopAnimator(const jerry_value_t func,
                                                   const jerry_value_t dom,
                                                   const jerry_value_t args[],
                                                   const jerry_length_t size)
{
    ImageAnimatorComponent *component =
        static_cast<ImageAnimatorComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to get DOM.");
        return UNDEFINED;
    }
    UIImageAnimatorView *animator = component->GetImageAnimator();

    if (animator != nullptr) {
        animator->Stop();
    }

    return UNDEFINED;
}

jerry_value_t ImageAnimatorComponent::GetAnimatorState(const jerry_value_t func,
                                                       const jerry_value_t dom,
                                                       const jerry_value_t args[],
                                                       const jerry_length_t size)
{
    ImageAnimatorComponent *component =
        static_cast<ImageAnimatorComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to get DOM.");
        return UNDEFINED;
    }
    UIImageAnimatorView *animator = component->GetImageAnimator();

    if (animator != nullptr) {
        uint8_t state = animator->GetState();

        switch (state) {
            case Animator::START:
                return jerry_create_string(reinterpret_cast<const jerry_char_t *>(STATUS_PLAYING));
            case Animator::PAUSE:
                return jerry_create_string(reinterpret_cast<const jerry_char_t *>(STATUS_PAUSED));
            case Animator::STOP:
                return jerry_create_string(reinterpret_cast<const jerry_char_t *>(STATUS_STOPED));
            default:
                break;
        }
    }
    return UNDEFINED;
}
} // namespace ACELite
} // namespace OHOS
