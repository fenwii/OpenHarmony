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
#include "transition_impl.h"

#include <stdlib.h>
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#endif // ENABLED(SECURE_C_FUNCTION)
#include "ace_log.h"
#include "ace_mem_base.h"
#include "easing_equation.h"
#include "root_view.h"

namespace OHOS {
namespace ACELite {
void TransitionImpl::Init()
{
    if (animator_ != nullptr) {
        return;
    }
    animator_ = new Animator(this, view_, 0, true);
    if (animator_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "animator create failed");
        return;
    }
    AnimatorManager::GetInstance()->Add(animator_);
}

void TransitionImpl::Callback(UIView* view)
{
    if (animator_ == nullptr) {
        return;
    }
    int32_t elapsedTime = animator_->GetRunTime() - params_.delay; // animation execution time
    if (elapsedTime <= 0) {
        return;
    }
    if (elapsedTime >= params_.during) {
        timeArrivaled_ = true;
    }

    Perform(elapsedTime);
}

void TransitionImpl::Start()
{
    if (animator_) {
        uint8_t state = animator_->GetState();
        if (((state == Animator::STOP) || (state == Animator::PAUSE)) && (params_.during > 0)) {
            RecordViewStatus();
            InitTransitionParams();
            animator_->Start();
        }
    } else {
        HILOG_INFO(HILOG_MODULE_ACE, "animator not initial or has been started");
    }
}

void TransitionImpl::Stop() const
{
    if (animator_) {
        uint8_t state = animator_->GetState();
        if (state == Animator::START || state == Animator::RUNNING) {
            animator_->Stop();
        }
    } else {
        HILOG_INFO(HILOG_MODULE_ACE, "animator not initial or is not running");
    }
}

void TransitionImpl::InitTransitionParams()
{
    InitTransitionParamsStyle();
    InitTransitionParamsTransform();
    InitTransitionParamsEasing();
}

void TransitionImpl::InitTransitionParamsStyle()
{
    params_.delay = (params_.delay <= 0) ? 0 : params_.delay;
    params_.during = (params_.during <= 0) ? 0 : params_.during;
    oriIteration_ = params_.iterations;

    if (params_.fill == OptionsFill::FORWARDS) {
        fill_ = OptionsFill::FORWARDS;
    }

    if (params_.height_from >= 0 && params_.height_to >= 0) {
        isTransitionSet_[GeneralType::IS_HEIGHT_TRANSITION_SET] = true;
        heightSrc_ = params_.height_from;
    }
    if (params_.width_from >= 0 && params_.width_to >= 0) {
        isTransitionSet_[GeneralType::IS_WIDTH_TRANSITION_SET] = true;
        widthSrc_ = params_.width_from;
    }
    if (params_.opacity_from >= 0 && params_.opacity_to >= 0) {
        isTransitionSet_[GeneralType::IS_OPCITY_TRANSITION_SET] = true;
        opacitySrc_ = (params_.opacity_from <= OPA_OPAQUE) ? params_.opacity_from : OPA_OPAQUE;
        params_.opacity_to = (params_.opacity_to <= OPA_OPAQUE) ? params_.opacity_to : OPA_OPAQUE;
    }

    const uint32_t rgbValueMin = 0x000000;
    const uint32_t rgbValueMax = 0xFFFFFF;
    if ((params_.background_color_from >= rgbValueMin) && (params_.background_color_from <= rgbValueMax) &&
        (params_.background_color_to >= rgbValueMin) && (params_.background_color_to <= rgbValueMax)) {
        isTransitionSet_[GeneralType::IS_BACKGROUND_COLOR_TRANSITION_SET] = true;
        GetRGB(params_.background_color_from, rSrc_, gSrc_, bSrc_);
        GetRGB(params_.background_color_to, rTo_, gTo_, bTo_);
        steps_ = params_.during / INTERVAL;
    }
}

void TransitionImpl::InitTransitionParamsTransform()
{
    if (params_.transformType == nullptr) {
        return;
    }
    if (!strcmp(params_.transformType, TRANSITION_TRANSFORM_X)) {
        transformType_ = TransformType::TRANSLATE_X;
        xSrc_ = viewStatus_.x + params_.transform_from;
    } else if (!strcmp(params_.transformType, TRANSITION_TRANSFORM_Y)) {
        transformType_ = TransformType::TRANSLATE_Y;
        ySrc_ = viewStatus_.y + params_.transform_from;
    } else if (!strcmp(params_.transformType, TRANSITION_ROTATE)) {
        transformType_ = TransformType::ROTATE;
        rotateSrc_ = params_.transform_from;
    }
}

void TransitionImpl::InitTransitionParamsEasing()
{
    switch (params_.easing) {
        case EasingType::EASE_IN:
            easingType_[EasingType::EASE_IN] = true;
            break;
        case EasingType::EASE_OUT:
            easingType_[EasingType::EASE_OUT] = true;
            break;
        case EasingType::EASE_IN_OUT:
            easingType_[EasingType::EASE_IN_OUT] = true;
            break;
        default:
            easingType_[EasingType::LINEAR] = true;
            break;
    }
}

void TransitionImpl::GetRGB(const uint32_t color, uint8_t& r, uint8_t& g, uint8_t& b) const
{
    r = uint8_t((color & TEXT_RED_COLOR_MASK) >> RED_COLOR_START_BIT);
    g = uint8_t((color & TEXT_GREEN_COLOR_MASK) >> GREEN_COLOR_START_BIT);
    b = uint8_t((color & TEXT_BLUE_COLOR_MASK));
}

int16_t TransitionImpl::GetNextFrameValue(int16_t from, int16_t to, int32_t elapsedTime) const
{
    int16_t nextPoint;
    if (easingType_[EasingType::EASE_IN]) {
        nextPoint = EasingEquation::CubicEaseIn(from, to, elapsedTime, params_.during);
    } else if (easingType_[EasingType::EASE_OUT]) {
        nextPoint = EasingEquation::CubicEaseOut(from, to, elapsedTime, params_.during);
    } else if (easingType_[EasingType::EASE_IN_OUT]) {
        nextPoint = EasingEquation::CubicEaseInOut(from, to, elapsedTime, params_.during);
    } else {
        nextPoint = EasingEquation::LinearEaseNone(from, to, elapsedTime, params_.during);
    }

    return nextPoint;
}

void TransitionImpl::SetTransformSrcPosition()
{
    if (params_.transformType == nullptr) {
        return;
    }
    if (!strcmp(params_.transformType, TRANSITION_TRANSFORM_X)) {
        view_->SetPosition(xSrc_, viewStatus_.y);
        view_->GetParent()->Invalidate();
    } else if (!strcmp(params_.transformType, TRANSITION_TRANSFORM_Y)) {
        view_->SetPosition(viewStatus_.x, ySrc_);
        view_->GetParent()->Invalidate();
    } else if (!strcmp(params_.transformType, TRANSITION_ROTATE)) {
        RotateAroundCenterPoint(rotateSrc_);
    } else {
        // do nothing
    }
}

void TransitionImpl::RotateAroundCenterPoint(int16_t angle)
{
    TransformMap transMap(view_->GetOrigRect());
    const int circleRate = 360;
    angle = angle % circleRate;
    uint8_t halfVal = 2;
    pivot_.x_ = view_->GetWidth() / halfVal;
    pivot_.y_ = view_->GetHeight() / halfVal;
    transMap.Rotate((angle), pivot_);
    view_->SetTransformMap(transMap);
}

void TransitionImpl::Perform(int32_t elapsedTime)
{
    if (timeArrivaled_) {
        if (!RepeatAnimator()) {
            this->Stop();
        }
    }

    if (!isTransformSrcSet_) {
        SetTransformSrcPosition();
        isTransformSrcSet_ = true;
    }

    if (transformType_ == TransformType::TRANSLATE_X) {
        PerformTransition(params_.transform_from, params_.transform_to, TransitionType::TTRANSLATE_X, xSrc_,
                          elapsedTime);
    } else if (transformType_ == TransformType::TRANSLATE_Y) {
        PerformTransition(params_.transform_from, params_.transform_to, TransitionType::TTRANSLATE_Y, ySrc_,
                          elapsedTime);
    } else if (transformType_ == TransformType::ROTATE) {
        PerformTransition(params_.transform_from, params_.transform_to, TransitionType::TROTATE, rotateSrc_,
                          elapsedTime);
    }

    if (isTransitionSet_[GeneralType::IS_HEIGHT_TRANSITION_SET]) {
        PerformTransition(params_.height_from, params_.height_to, TransitionType::HEIGHT, heightSrc_, elapsedTime);
    }
    if (isTransitionSet_[GeneralType::IS_WIDTH_TRANSITION_SET]) {
        PerformTransition(params_.width_from, params_.width_to, TransitionType::WIDTH, widthSrc_, elapsedTime);
    }

    if (isTransitionSet_[GeneralType::IS_OPCITY_TRANSITION_SET]) {
        PerformTransition(params_.opacity_from, params_.opacity_to, TransitionType::OPACITY, opacitySrc_, elapsedTime);
    }

    if (isTransitionSet_[GeneralType::IS_BACKGROUND_COLOR_TRANSITION_SET]) {
        PerformTransitionBgColorLinear(elapsedTime);
    }

    if (fill_ == OptionsFill::FNONE && timeArrivaled_) {
        RecoveryViewStatus(view_->GetRect());
    }

    if (timeArrivaled_) {
        ResetRepeatParam();
    }
}

void TransitionImpl::PerformTransitionBgColorLinear(int32_t elapsedTime)
{
    if (timeArrivaled_) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "time arrived");
        view_->SetStyle(STYLE_BACKGROUND_COLOR, Color::GetColorFromRGB(rTo_, gTo_, bTo_).full);
        return;
    }
    if ((steps_ != 0) && (count_ <= steps_) && (elapsedTime <= params_.during)) {
        if ((elapsedTime - bgcolorTimeSrc_) > INTERVAL) {
            ColorType color = Color::GetColorFromRGB(rSrc_ + (rTo_ - rSrc_) * count_ / steps_,
                                                     gSrc_ + (gTo_ - gSrc_) * count_ / steps_,
                                                     bSrc_ + (bTo_ - bSrc_) * count_ / steps_);
            view_->SetStyle(STYLE_BACKGROUND_COLOR, color.full);
            view_->Invalidate();
            bgcolorTimeSrc_ = elapsedTime;
            count_++;
        }
    }
}

void TransitionImpl::PerformTransition(int16_t from,
                                       int16_t to,
                                       TransitionType transitionType,
                                       int16_t& updateAttrValue,
                                       int32_t elapsedTime)
{
    bool needUpdate = true;

    if (timeArrivaled_) {
        updateAttrValue = to;
    } else {
        int16_t prefectchedValue = 0;
        prefectchedValue = GetNextFrameValue(from, to, elapsedTime);
        int16_t diffDistance = prefectchedValue - updateAttrValue;
        if (((diffDistance < 1) && (diffDistance > -1)) || (elapsedTime > params_.during)) {
            needUpdate = false;
        } else {
            updateAttrValue = static_cast<int16_t>(prefectchedValue);
        }
    }

    if (needUpdate) {
        Rect invalidatedArea = view_->GetRect();

        switch (transitionType) {
            case TransitionType::TTRANSLATE_X:
                view_->SetPosition((updateAttrValue + viewStatus_.x), viewStatus_.y);
                break;
            case TransitionType::TTRANSLATE_Y:
                view_->SetPosition(viewStatus_.x, (updateAttrValue + viewStatus_.y));
                break;
            case TransitionType::TROTATE: {
                RotateAroundCenterPoint(updateAttrValue);
                break;
            }
            case TransitionType::HEIGHT:
                view_->SetHeight(updateAttrValue);
                break;
            case TransitionType::WIDTH:
                view_->SetWidth(updateAttrValue);
                break;
            case TransitionType::OPACITY: {
                double rate = (double)updateAttrValue / ALPHA_MAX;
                view_->SetStyle(STYLE_BACKGROUND_OPA, viewStatus_.rectOpacity * rate);
                view_->SetStyle(STYLE_IMAGE_OPA, viewStatus_.imageOpacity * rate);
                view_->SetStyle(STYLE_LINE_OPA, viewStatus_.lineOpacity * rate);
                view_->SetStyle(STYLE_TEXT_OPA, viewStatus_.textOpacity * rate);
                break;
            }
            default:
                HILOG_INFO(HILOG_MODULE_ACE, "animation nothing to do.");
                break;
        }

        invalidatedArea.Join(invalidatedArea, view_->GetRect());
        view_->InvalidateRect(invalidatedArea);
    }
}
int8_t TransitionImpl::GetNumIterations(const char* iterations)
{
    if (!strcmp(iterations, "infinite")) {
        return TransitionImpl::ITERATIONS_INFINITY;
    }

    int8_t min = 1;
    int8_t max = 127;
    long value = strtol(iterations, nullptr, DEC);
    if ((value < min) || (value > max)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "animation iterations should set between 1 and 127");
        return min;
    } else {
        return (int8_t)value;
    }
}

bool TransitionImpl::IsEndWith(const char* src, const char* end)
{
    if (src == nullptr || end == nullptr) {
        return false;
    }

    size_t strLen = strlen(src);
    size_t endLen = strlen(end);
    if (strLen < endLen || strLen == 0 || endLen == 0) {
        return false;
    }

    while ((endLen > 0) && (strLen > 0)) {
        if (src[strLen - 1] != end[endLen - 1]) {
            return false;
        }
        endLen--;
        strLen--;
    }
    return true;
}

bool TransitionImpl::RepeatAnimator()
{
    if (oriIteration_ != TransitionImpl::ITERATIONS_INFINITY) {
        oriIteration_--;
        if (oriIteration_ == 0) {
            oriIteration_ = params_.iterations;
            return false;
        }
    }
    HILOG_DEBUG(HILOG_MODULE_ACE, "repeat");
    return true;
}

void TransitionImpl::ResetRepeatParam()
{
    if (animator_ != nullptr) {
        animator_->SetRunTime(0); // reset animation executing time
    }
    timeArrivaled_ = false;   // reset timeArrivaled flag
    bgcolorTimeSrc_ = 0;      // reset bg-color last update time
    count_ = 1;               // reset bg-color update number of times
}

void TransitionImpl::RecordViewStatus()
{
    viewStatus_.x = view_->GetX();
    viewStatus_.y = view_->GetY();
    viewStatus_.oriRect = view_->GetOrigRect();
    viewStatus_.height = view_->GetHeight();
    viewStatus_.width = view_->GetWidth();
    viewStatus_.background_color.full = view_->GetStyle(STYLE_BACKGROUND_COLOR);
    viewStatus_.rectOpacity = view_->GetStyle(STYLE_BACKGROUND_OPA);
    viewStatus_.imageOpacity = view_->GetStyle(STYLE_IMAGE_OPA);
    viewStatus_.lineOpacity = view_->GetStyle(STYLE_LINE_OPA);
    viewStatus_.textOpacity = view_->GetStyle(STYLE_TEXT_OPA);
}

void TransitionImpl::RecoveryViewStatus(Rect invalidatedAreaBefore) const
{
    view_->SetX(viewStatus_.x);
    view_->SetY(viewStatus_.y);
    view_->SetHeight(viewStatus_.height);
    view_->SetWidth(viewStatus_.width);
    TransformMap& transMap = view_->GetTransformMap();
    Polygon polygon(Rect(0, 0, 0, 0));
    transMap.SetPolygon(polygon);
    view_->SetStyle(STYLE_BACKGROUND_COLOR, viewStatus_.background_color.full);
    view_->SetStyle(STYLE_BACKGROUND_OPA, viewStatus_.rectOpacity);
    view_->SetStyle(STYLE_IMAGE_OPA, viewStatus_.imageOpacity);
    view_->SetStyle(STYLE_LINE_OPA, viewStatus_.lineOpacity);
    view_->SetStyle(STYLE_TEXT_OPA, viewStatus_.textOpacity);
    invalidatedAreaBefore.Join(invalidatedAreaBefore, view_->GetRect());
    view_->InvalidateRect(invalidatedAreaBefore);
}
} // namespace ACELite
} // namespace OHOS
