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

#ifndef OHOS_ACELITE_SWIPER_COMPONENT_H
#define OHOS_ACELITE_SWIPER_COMPONENT_H

#include "component.h"
#include "non_copyable.h"
#include "ui_swipe_view.h"

namespace OHOS {
namespace ACELite {
constexpr char SWIPER_ATTR_INDEX[] = "index";
class SwiperComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(SwiperComponent);
    SwiperComponent() = delete;
    SwiperComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager);
    ~SwiperComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    void PostUpdate(uint16_t attrKeyId, bool updateResult) override;
    void PostRender() override;
    bool ProcessChildren() override;
    bool RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue) override;

private:
    class ChangeListener : public UISwipeView::OnSwipeListener {
    public:
        ACE_DISALLOW_COPY_AND_MOVE(ChangeListener);
        explicit ChangeListener(jerry_value_t fn) : fn_(jerry_acquire_value(fn)) {}
        ChangeListener() = delete;
        ~ChangeListener()
        {
            jerry_release_value(fn_);
        }
        void OnSwipe(UISwipeView &view) override;

    private:
        jerry_value_t fn_;
    };
    void SetPageIndex() const;
    UISwipeView *swiperView_;
    bool hasChildren_;
    int16_t index_;
    ChangeListener *changeListener_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_SWIPER_COMPONENT_H
