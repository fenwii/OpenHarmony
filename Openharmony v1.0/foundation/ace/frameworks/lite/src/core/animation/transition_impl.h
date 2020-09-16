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

#ifndef OHOS_ACELITE_TRANSITION_IMPL_H
#define OHOS_ACELITE_TRANSITION_IMPL_H
#include <ctime>

#include "animator.h"
#include "js_fwk_common.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
enum EasingType { LINEAR, EASE_IN, EASE_OUT, EASE_IN_OUT, EEND };

enum OptionsFill { FNONE, FORWARDS };

struct TransitionParams {
    /* animation execution time (ms), default is 0, means no animation effect. */
    int32_t during;
    /* the time interval (ms) between requesting an animation operation and executing it. */
    int32_t delay;
    /* animation execution times, default is 1. */
    int8_t iterations;
    /* specify whether to return to the initial state after the animation finishes,
    default is 'none', means to return to the initial state; 'forwards' means not return to. */
    OptionsFill fill;
    /* specify the speed curve of the animation */
    EasingType easing;

    /* transformType include "translateX/translateY", you can only specify one of these once a time. */
    char* transformType;
    /* transform from source (px) to target (px) */
    int16_t transform_from;
    int16_t transform_to;

    int16_t height_from;
    int16_t height_to;
    int16_t width_from;
    int16_t width_to;
    int16_t opacity_from;
    int16_t opacity_to;
    uint32_t background_color_from;
    uint32_t background_color_to;

    TransitionParams()
        : during(0),
          delay(0),
          iterations(1),
          fill(OptionsFill::FNONE),
          easing(EasingType::LINEAR),
          transformType(nullptr),
          transform_from(0),
          transform_to(0),
          height_from(-1),
          height_to(-1),
          width_from(-1),
          width_to(-1),
          opacity_from(-1),
          opacity_to(-1),
          background_color_from(RGB_COLOR_VALUE_MAX),
          background_color_to(RGB_COLOR_VALUE_MAX){};
};

struct ViewStatus {
    int16_t x;
    int16_t y;
    int16_t height;
    int16_t width;
    int16_t rectOpacity;
    int16_t imageOpacity;
    int16_t lineOpacity;
    int16_t textOpacity;
    Rect oriRect;
    ColorType background_color;

    ACE_DISALLOW_COPY_AND_MOVE(ViewStatus);
    ViewStatus() : x(0), y(0), height(0), width(0), rectOpacity(0), imageOpacity(0), lineOpacity(0), textOpacity(0),
                   oriRect(), background_color() {};
};

enum TransformType { TRANSLATE_X, TRANSLATE_Y, ROTATE, NONE }; // rotate only support image

enum GeneralType {
    IS_HEIGHT_TRANSITION_SET,
    IS_WIDTH_TRANSITION_SET,
    IS_BACKGROUND_COLOR_TRANSITION_SET,
    IS_OPCITY_TRANSITION_SET,
    END
};

enum TransitionType {
    TTRANSLATE_X,
    TTRANSLATE_Y,
    TROTATE,
    HEIGHT,
    WIDTH,
    BACKGROUND_COLOR,
    OPACITY
};

/**
 * @brief: animation callback implement.
 *         supported parameters can refer to struct TransitionParams
 */
class TransitionImpl final : public AnimatorCallback {
public:
    /**
     * @brief: Construct function
     *
     * @param: params animation transition effect
     * @param: view target view which run the animation
     */
    ACE_DISALLOW_COPY_AND_MOVE(TransitionImpl);
    TransitionImpl(TransitionParams& params, UIView* view)
        : view_(view),
          params_(params),
          oriIteration_(1),
          animator_(nullptr),
          xSrc_(0), ySrc_(0), rotateSrc_(0), widthSrc_(0), heightSrc_(0), opacitySrc_(0), bgcolorTimeSrc_(0)
    {
    }
    TransitionImpl() = delete;
    ~TransitionImpl()
    {
        if (animator_ != nullptr) {
            AnimatorManager *am = AnimatorManager::GetInstance();
            if (am != nullptr) {
                AnimatorManager::GetInstance()->Remove(animator_);
            }
            delete (animator_);
            animator_ = nullptr;
        }
    }

    /**
     * @brief: must call this to do initialization after create TransitionImpl instance
     */
    void Init();
    /**
     * brief: start the animation
     */
    void Start();
    static int8_t GetNumIterations(const char* iterations);
    static bool IsEndWith(const char* src, const char *end);
    void Stop() const;

private:
    void Callback(UIView* view) override;
    bool RepeatAnimator();
    void ResetRepeatParam();
    void RecordViewStatus();
    void RecoveryViewStatus(Rect invalidatedAreaBefore) const;
    void InitTransitionParams();
    void InitTransitionParamsStyle();
    void InitTransitionParamsTransform();
    void InitTransitionParamsEasing();
    void GetRGB(const uint32_t color, uint8_t& r, uint8_t& g, uint8_t& b) const;
    int16_t GetNextFrameValue(int16_t from, int16_t to, int32_t elapsedTime) const;
    void SetTransformSrcPosition();
    void RotateAroundCenterPoint(int16_t angle);
    void Perform(int32_t elapsedTime);
    void PerformTransitionBgColorLinear(int32_t elapsedTime);
    void PerformTransition(int16_t from,
                           int16_t to,
                           TransitionType transitionType,
                           int16_t& updateAttrValue,
                           int32_t elapsedTime);

    UIView* view_;
    TransitionParams& params_;
    int8_t oriIteration_;
    Animator* animator_;
    Vector2<int16_t> pivot_;
    int16_t xSrc_;
    int16_t ySrc_;
    int16_t rotateSrc_;
    int16_t widthSrc_;
    int16_t heightSrc_;
    int16_t opacitySrc_;
    ViewStatus viewStatus_;
    bool isTransformSrcSet_ = false;
    bool timeArrivaled_ = false;
    bool easingType_[EasingType::EEND] = {0};
    bool isTransitionSet_[GeneralType::END] = {0};
    OptionsFill fill_ = OptionsFill::FNONE;
    TransformType transformType_ = TransformType::NONE;

    /* used for background-color */
    uint8_t rSrc_ = 0; // used to record the last time red value
    uint8_t gSrc_ = 0;
    uint8_t bSrc_ = 0;
    uint8_t rTo_ = 0;
    uint8_t gTo_ = 0;
    uint8_t bTo_ = 0;
    int8_t count_ = 1;             // used to record the current number of times of updating the bg-color
    int8_t steps_ = 1;             // total target number of times of updating the bg-color (during_/INTERVAL)
    int32_t bgcolorTimeSrc_ = 0;       // used to record the last time bg-color
    const static int8_t ITERATIONS_INFINITY = -1;
    const static int16_t INTERVAL = 150; // update the bg-color every INTERVAL (ms)
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_TRANSITION_IMPL_H
