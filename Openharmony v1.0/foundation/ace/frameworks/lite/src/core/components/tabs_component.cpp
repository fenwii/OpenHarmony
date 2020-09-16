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

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_TABS

#include "ace_log.h"
#include "keys.h"
#include "tabs_component.h"
#include "ui_label.h"
#include "ui_view_group.h"

namespace OHOS {
namespace ACELite {
TabsComponent::TabsComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager)
    : Component(options, children, styleManager),
      options_(options),
      children_(children),
      tabBarComponent_(nullptr),
      tabContentComponent_(nullptr),
      tabView_(nullptr),
      changeListener_(nullptr),
      list_(nullptr)
{
    SetComponentName(K_TABS);
}

void TabsComponent::PreRender()
{
    if (!MatchChildren()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Children not matched.");
    }
}

inline UIView *TabsComponent::GetComponentRootView() const
{
    return tabView_;
}

bool TabsComponent::CreateNativeViews()
{
    if (tabBarComponent_ == nullptr || tabContentComponent_ == nullptr) {
        return false;
    }
    tabView_ = new UITabView(GetTabBarLocation());
    if (tabView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Create tabView failed.");
        return false;
    }
    tabView_->SetTitleSize(CalculateBarHeight());
    tabView_->SetTabSize(CalculateBarWidth());
    tabView_->SetAnimatorTime(tabsAnimationTime);
    return true;
}

void TabsComponent::ReleaseNativeViews()
{
    if (tabView_) {
        delete tabView_;
        tabView_ = nullptr;
    }
    if (changeListener_) {
        delete changeListener_;
        changeListener_ = nullptr;
    }
    if (list_) {
        while (list_->Size() > 0) {
            UIViewGroup* viewGroup = list_->Front();
            if (viewGroup) {
                delete viewGroup;
                viewGroup = nullptr;
            }
            list_->PopFront();
        }
        delete list_;
        list_ = nullptr;
    }
}

bool TabsComponent::ProcessChildren()
{
    uint8_t barLength = tabBarComponent_->GetChildrenLength();
    uint8_t contentLength = tabContentComponent_->GetChildrenLength();
    uint8_t length = (barLength > contentLength) ? contentLength : barLength;

    for (uint8_t index = 0; index < length; ++index) {
        Component* component = tabContentComponent_->GetComponentByIndex(index);
        if (component == nullptr) {
            return false;
        }
        UIViewGroup* viewGroup = nullptr;
        if (component->GetComponentName() == K_DIV || component->GetComponentName() == K_STACK) {
            viewGroup = reinterpret_cast<UIViewGroup *>(component->GetComponentRootView());
            if (viewGroup == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "ViewGroup does not existed.");
                return false;
            }
        } else {
            if (list_ == nullptr) {
                list_ = new List<UIViewGroup*>;
                if (list_ == nullptr) {
                    return false;
                }
            }
            viewGroup = new UIViewGroup();
            if (viewGroup == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "Create viewGroup failed.");
                return false;
            }
            viewGroup->SetPosition(0, 0);
            viewGroup->SetHeight(GetVerticalResolution());
            viewGroup->SetWidth(GetHorizontalResolution());
            viewGroup->Add(component->GetComponentRootView());
            list_->PushBack(viewGroup);
        }
        const char* text = tabBarComponent_->GetTextByIndex(index);
        if (text == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "tab-bar's children is error.");
            text = " ";
        }
        tabView_->AddPage(viewGroup, text);
    }
    return true;
}

void TabsComponent::PostRender()
{
    tabView_->SetCurrentPage(GetInitPageIndex());
    tabView_->Layout();
}

bool TabsComponent::RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    if (!KeyParser::IsKeyValid(eventTypeId) || IS_UNDEFINED(funcValue)) {
        return false;
    }
    if (eventTypeId == K_CHANGE) {
        if (tabView_) {
            changeListener_ = new ChangeListener(funcValue);
            if (changeListener_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "Create ChangeListener error.");
                return false;
            }
            tabView_->SetOnSwipeListener(changeListener_);
            return true;
        }
    }
    return false;
}

bool TabsComponent::MatchChildren()
{
    if (jerry_value_is_undefined(children_)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "tabs's children does not exist.");
        return false;
    }
    uint8_t length = jerry_get_array_length(children_);
    if (length != tabsChildrenNum) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Only if one tab-bar and one tab-content.");
        return false;
    }

    for (uint8_t index = 0; index < length; ++index) {
        jerry_value_t child = jerry_get_property_by_index(children_, index);
        Component* component = ComponentUtils::GetComponentFromBindingObject(child);
        if (component == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "tabs' children does not exist.");
            jerry_release_value(child);
            return false;
        }
        if (component->GetComponentName() == K_TAB_BAR) {
            TabBarComponent* tabBarComponent = reinterpret_cast<TabBarComponent *>(component);
            if (tabBarComponent == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "tabs children type is error.");
                jerry_release_value(child);
                return false;
            }
            tabBarComponent_ = tabBarComponent;
        } else if (component->GetComponentName() == K_TAB_CONTENT) {
            TabContentComponent* tabContentComponent = reinterpret_cast<TabContentComponent *>(component);
            if (tabContentComponent == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "tabs children type is error.");
                jerry_release_value(child);
                return false;
            }
            tabContentComponent_ = tabContentComponent;
        } else {
            jerry_release_value(child);
            HILOG_ERROR(HILOG_MODULE_ACE, "tabs children type is error.");
            return false;
        }
        jerry_release_value(child);
    }
    if (tabBarComponent_ == nullptr || tabContentComponent_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Only if one tab-bar and one tab-content.");
        return false;
    }
    return true;
}

UITabView::TitleLocation TabsComponent::GetTabBarLocation()
{
    jerry_value_t firstChildHandler = jerry_get_property_by_index(children_, 0);

    Component* component = ComponentUtils::GetComponentFromBindingObject(firstChildHandler);
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "MatchChildren should not passed.");
        jerry_release_value(firstChildHandler);
        return UITabView::TitleLocation::TOP;
    }
    UITabView::TitleLocation location;
    if (component->GetComponentName() == K_TAB_BAR) {
        location = UITabView::TitleLocation::TOP;
    } else {
        location = UITabView::TitleLocation::BOTTOM;
    }
    jerry_release_value(firstChildHandler);
    return location;
}

int16_t TabsComponent::CalculateBarHeight()
{
    return tabBarComponent_->GetHeight();
}

int16_t TabsComponent::CalculateBarWidth()
{
    int16_t width;
    uint8_t barLength = tabBarComponent_->GetChildrenLength();
    uint8_t contentLength = tabContentComponent_->GetChildrenLength();
    uint8_t length = (barLength > contentLength) ? contentLength : barLength;
    if ((tabBarComponent_->GetMode() != nullptr) && !strcmp(tabBarComponent_->GetMode(), TABS_VAL_SCROLL)) {
        width = tabBarComponent_->GetWidth();
    } else {
        width = GetHorizontalResolution();
    }
    if (length == 0) {
        return 0;
    }
    return width / length;
}

int16_t TabsComponent::GetInitPageIndex()
{
    uint8_t barLength = tabBarComponent_->GetChildrenLength();
    uint8_t contentLength = tabContentComponent_->GetChildrenLength();
    uint8_t length = (barLength > contentLength) ? contentLength : barLength;

    jerry_value_t attrsKeyHandler = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ATTR_ATTRS));
    jerry_value_t attrsValHandler = jerry_get_property(options_, attrsKeyHandler);
    if (jerry_value_is_undefined(attrsValHandler)) {
        jerry_release_value(attrsKeyHandler);
        return 0;
    }

    jerry_value_t indexKeyHandler = jerry_create_string(reinterpret_cast<const jerry_char_t *>(TABS_ATTR_INDEX));
    jerry_value_t indexValHandler = jerry_get_property(attrsValHandler, indexKeyHandler);
    if (jerry_value_is_function(indexValHandler)) {
        jerry_value_t globalObject = jerry_get_global_object();
        jerry_value_t appPropName = jerry_create_string((const jerry_char_t*)ATTR_ROOT);
        jerry_value_t appViewModel = jerry_get_property(globalObject, appPropName);
        jerry_value_t newIndexValHandler = jerry_call_function(indexValHandler, appViewModel, nullptr, 0);
        if (newIndexValHandler != indexValHandler) {
            jerry_release_value(indexValHandler);
            indexValHandler = newIndexValHandler;
        }
        ReleaseJerryValue(appViewModel, appPropName, globalObject, VA_ARG_END_FLAG);
    }
    int16_t currentPage;
    if (!jerry_value_is_undefined(indexValHandler) && !jerry_value_is_error(indexValHandler)
        && (jerry_value_is_number(indexValHandler) || jerry_value_is_string(indexValHandler))) {
        currentPage = IntegerOf(indexValHandler);
        if (currentPage >= length || currentPage < 0) {
            currentPage = 0;
        }
    } else {
        currentPage = 0;
    }

    ReleaseJerryValue(indexValHandler, indexKeyHandler, attrsValHandler, attrsKeyHandler, VA_ARG_END_FLAG);

    return currentPage;
}

void TabsComponent::ChangeListener::OnSwipe(UISwipeView& view)
{
    if (jerry_value_is_undefined(fn_)) {
        return;
    }

    UITabView* tabView = reinterpret_cast<UITabView *>(&view);
    if (tabView == nullptr) {
        return;
    }

    const uint8_t argsNum = 1;
    jerry_value_t args[argsNum];
    args[0] = jerry_create_object();
    jerry_value_t indexKeyHandler = jerry_create_string((const jerry_char_t*)TABS_ATTR_INDEX);
    jerry_value_t indexValHandler = jerry_create_number(tabView->GetCurrentPage());
    jerry_value_t result = jerry_set_property(args[0], indexKeyHandler, indexValHandler);
    ReleaseJerryValue(indexValHandler, indexKeyHandler, VA_ARG_END_FLAG);
    if (jerry_value_is_error(result)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "set index value failed.");
        jerry_release_value(args[0]);
        jerry_release_value(result);
        return;
    }
    jerry_release_value(result);

    jerry_value_t globalObject = jerry_get_global_object();
    jerry_value_t appPropName = jerry_create_string((const jerry_char_t*)ATTR_ROOT);
    jerry_value_t appViewModel = jerry_get_property(globalObject, appPropName);
    if (jerry_value_is_function(fn_)) {
        jerry_value_t retVal = CallJSFunction(fn_, appViewModel, args, argsNum);
        if (jerry_value_is_error(retVal)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "Change event is error.");
        }
        jerry_release_value(retVal);
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "Change event is not a function.");
    }

    ReleaseJerryValue(appViewModel, appPropName, globalObject, args[0], VA_ARG_END_FLAG);
}
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_TABS
