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

#ifndef OHOS_ACELITE_TABS_COMPONENT_H
#define OHOS_ACELITE_TABS_COMPONENT_H

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_TABS

#include "component.h"
#include "non_copyable.h"
#include "tab_bar_component.h"
#include "tab_content_component.h"
#include "ui_tab_view.h"

namespace OHOS {
namespace ACELite {
constexpr char TABS_ATTR_INDEX[] = "index";
constexpr char TABS_VAL_SCROLL[] = "scrollable";
class TabsComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TabsComponent);
    TabsComponent() = delete;
    TabsComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~TabsComponent() {}

protected:
    void PreRender() override;
    bool CreateNativeViews() override;
    UIView *GetComponentRootView() const override;
    void ReleaseNativeViews() override;
    bool ProcessChildren() override;
    void PostRender() override;
    bool RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue) override;

private:
    bool MatchChildren();
    UITabView::TitleLocation GetTabBarLocation();
    int16_t CalculateBarHeight();
    int16_t CalculateBarWidth();
    int16_t GetInitPageIndex();

    class ChangeListener : public UISwipeView::OnSwipeListener {
    public:
        ACE_DISALLOW_COPY_AND_MOVE(ChangeListener);
        ChangeListener() = delete;
        explicit ChangeListener(jerry_value_t fn) : fn_(jerry_acquire_value(fn)) {};
        ~ChangeListener()
        {
            jerry_release_value(fn_);
        }
        void OnSwipe(UISwipeView& view) override;

    private:
        jerry_value_t fn_ = 0;
    };
    jerry_value_t options_;
    jerry_value_t children_;
    TabBarComponent* tabBarComponent_;
    TabContentComponent* tabContentComponent_;
    UITabView* tabView_;
    const int tabsChildrenNum = 2;
    const int tabsAnimationTime = 0;
    ChangeListener* changeListener_;
    List<UIViewGroup*>* list_;
};
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_TABS

#endif // OHOS_ACELITE_TABS_COMPONENT_H
