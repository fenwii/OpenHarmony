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

#ifndef OHOS_ACELITE_IMAGE_ANIMATOR_COMPNENT_H
#define OHOS_ACELITE_IMAGE_ANIMATOR_COMPNENT_H

#include "component.h"
#include "non_copyable.h"
#include "ui_image_animator.h"

namespace OHOS {
namespace ACELite {
class ImageAnimatorStopListener final : public UIImageAnimatorView::AnimatorStopListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ImageAnimatorStopListener);
    explicit ImageAnimatorStopListener(jerry_value_t fn)
    {
        fn_ = jerry_acquire_value(fn);
    }
    ~ImageAnimatorStopListener()
    {
        if (!jerry_value_is_undefined(fn_)) {
            jerry_release_value(fn_);
        }
    }

    void OnAnimatorStop(UIView& view) override
    {
        if (jerry_value_is_undefined(fn_)) {
            return;
        }

        jerry_release_value(CallJSFunction(fn_, UNDEFINED, nullptr, 0));
    }

private:
    jerry_value_t fn_;
};

class ImageAnimatorComponent final : public Component {
public:
    ImageAnimatorComponent() = delete;
    ImageAnimatorComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~ImageAnimatorComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    void PostRender() override;
    void PostUpdate(uint16_t attrKeyId, bool updateResult) override;
    bool RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue) override;

private:
    void ReleaseFrame();
    bool ParseToFixedSize(jerry_value_t value) const;
    bool ParseToFrames(jerry_value_t value);
    bool ParseToIteration(jerry_value_t value) const;
    bool ParseToReverse(jerry_value_t value) const;
    bool ParseToDuration(jerry_value_t value);
    void UpdateAnimator() const;

    UIImageAnimatorView* GetImageAnimator() const
    {
        return imageAnimator_;
    }

    static jerry_value_t StartAnimator(const jerry_value_t func,
                                       const jerry_value_t dom,
                                       const jerry_value_t args[],
                                       const jerry_length_t size);
    static jerry_value_t PauseAnimator(const jerry_value_t func,
                                       const jerry_value_t dom,
                                       const jerry_value_t args[],
                                       const jerry_length_t size);
    static jerry_value_t ResumeAnimator(const jerry_value_t func,
                                        const jerry_value_t dom,
                                        const jerry_value_t args[],
                                        const jerry_length_t size);
    static jerry_value_t StopAnimator(const jerry_value_t func,
                                      const jerry_value_t dom,
                                      const jerry_value_t args[],
                                      const jerry_length_t size);
    static jerry_value_t GetAnimatorState(const jerry_value_t func,
                                          const jerry_value_t dom,
                                          const jerry_value_t args[],
                                          const jerry_length_t size);

    UIViewGroup *viewGroup_;
    UIImageAnimatorView *imageAnimator_;
    ImageAnimatorStopListener* onStopListener_;
    ImageAnimatorInfo *frames_;
    char *duration_;
    uint8_t framesSize_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_IMAGE_ANIMATOR_COMPNENT_H
