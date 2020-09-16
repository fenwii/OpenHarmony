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

#include "js_fwk_common.h"
#include "key_parser.h"
#include "keys.h"
#include "tab_bar_component.h"
#include "ui_label.h"
#include "ace_log.h"
#include "ace_mem_base.h"

namespace OHOS {
namespace ACELite {
TabBarComponent::TabBarComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager)
    : Component(options, children, styleManager),
      options_(options),
      children_(children),
      width_(0),
      height_(0),
      mode_(nullptr)
{
    SetComponentName(K_TAB_BAR);
    combinedStyle_ = GetStyleManager()->GetCombinedStyle();
}

uint8_t TabBarComponent::GetChildrenLength()
{
    return jerry_get_array_length(children_);
}

void TabBarComponent::ReleaseNativeViews()
{
    if (mode_) {
        ace_free(mode_);
        mode_ = nullptr;
    }
}

const char* TabBarComponent::GetTextByIndex(uint8_t index)
{
    jerry_value_t childHandler = jerry_get_property_by_index(children_, index);
    Component* textComponent = ComponentUtils::GetComponentFromBindingObject(childHandler);
    if (textComponent == nullptr) {
        jerry_release_value(childHandler);
        return nullptr;
    }
    if (textComponent->GetComponentName() == K_TEXT) {
        UIView* view = textComponent->GetComponentRootView();
        UILabel* label = reinterpret_cast<UILabel *>(view);
        if (label == nullptr) {
            jerry_release_value(childHandler);
            return nullptr;
        }
        jerry_release_value(childHandler);
        return label->GetText();
    }

    jerry_release_value(childHandler);
    return nullptr;
}

void TabBarComponent::PreRender()
{
    SetWidth();
    SetHeight();
    SetMode();
}

void TabBarComponent::SetWidth()
{
    jerry_value_t widthKeyHandler = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ATTR_WIDTH));
    jerry_value_t widthValHandler = GetAttrValHandler(widthKeyHandler);
    int32_t defaultWidth = GetHorizontalResolution();
    width_ = defaultWidth;
    if (jerry_value_is_undefined(widthValHandler)) {
        if (combinedStyle_) {
            const AppStyleItem* item = combinedStyle_->GetStyleItemByNameId(K_WIDTH);
            defaultWidth = (item == nullptr) ? defaultWidth : item->GetNumValue();
        }
    }
    if (defaultWidth >= 0 && defaultWidth <= INT16_MAX) {
        width_ = defaultWidth;
    } else {
        HILOG_DEBUG(HILOG_MODULE_ACE, "set width of tab-bar fail.");
    }
    jerry_release_value(widthValHandler);
    jerry_release_value(widthKeyHandler);
}

void TabBarComponent::SetHeight()
{
    jerry_value_t heightKeyHandler = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ATTR_HEIGHT));
    jerry_value_t heightValHandler = GetAttrValHandler(heightKeyHandler);
    int32_t defaultHeight = 50;
    height_ = defaultHeight;
    if (jerry_value_is_undefined(heightValHandler)) {
        if (combinedStyle_) {
            const AppStyleItem* item = combinedStyle_->GetStyleItemByNameId(K_HEIGHT);
            defaultHeight = (item == nullptr) ? defaultHeight : item->GetNumValue();
        }
    }
    if (defaultHeight >= 0 && defaultHeight <= VERTICAL_RESOLUTION) {
        height_ = defaultHeight;
    } else {
        HILOG_DEBUG(HILOG_MODULE_ACE, "set height of tab-bar fail.");
    }
    jerry_release_value(heightValHandler);
    jerry_release_value(heightKeyHandler);
}

void TabBarComponent::SetMode()
{
    const char * const attrMode = "mode";
    jerry_value_t modeKeyHandler = jerry_create_string(reinterpret_cast<const jerry_char_t *>(attrMode));
    jerry_value_t modeValHandler = GetAttrValHandler(modeKeyHandler);
    char defaultMode[] = "fixed";
    mode_ = static_cast<char *>(ace_malloc(sizeof(defaultMode)));
    if (mode_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc mode_ failed.");
    } else {
        if (memcpy_s(mode_, sizeof(defaultMode), defaultMode, sizeof(defaultMode)) != 0) {
            HILOG_ERROR(HILOG_MODULE_ACE, "memcpy mode_ failed.");
            ace_free(mode_);
            mode_ = nullptr;
            jerry_release_value(modeValHandler);
            jerry_release_value(modeKeyHandler);
            return;
        }
        if (!jerry_value_is_undefined(modeValHandler) && jerry_value_is_string(modeValHandler)) {
            char* newMode_ = MallocStringOf(modeValHandler);
            if (newMode_ != nullptr) {
                ace_free(mode_);
                mode_ = newMode_;
            }
        } else {
            HILOG_DEBUG(HILOG_MODULE_ACE, "tab-bar mode value is not define or error.");
        }
    }
    jerry_release_value(modeValHandler);
    jerry_release_value(modeKeyHandler);
}

jerry_value_t TabBarComponent::GetAttrValHandler(jerry_value_t attrKeyHandler)
{
    jerry_value_t attrsKeyHandler = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ATTR_ATTRS));
    jerry_value_t attrsValHandler = jerry_get_property(options_, attrsKeyHandler);
    if (jerry_value_is_undefined(attrsValHandler)) {
        jerry_release_value(attrsKeyHandler);
        return UNDEFINED;
    }

    jerry_value_t attrValHandler = jerry_get_property(attrsValHandler, attrKeyHandler);
    if (jerry_value_is_function(attrValHandler)) {
        jerry_value_t globalObject = jerry_get_global_object();
        jerry_value_t appPropName = jerry_create_string((const jerry_char_t*)ATTR_ROOT);
        jerry_value_t appViewModel = jerry_get_property(globalObject, appPropName);
        jerry_value_t newAttrValHandler = jerry_call_function(attrValHandler, appViewModel, nullptr, 0);
        if (newAttrValHandler != attrValHandler) {
            jerry_release_value(attrValHandler);
            attrValHandler = newAttrValHandler;
        }
        ReleaseJerryValue(appViewModel, appPropName, globalObject, VA_ARG_END_FLAG);
    }
    if (jerry_value_is_undefined(attrValHandler) || jerry_value_is_error(attrValHandler)) {
        jerry_release_value(attrValHandler);
        attrValHandler = UNDEFINED;
    }
    jerry_release_value(attrsValHandler);
    jerry_release_value(attrsKeyHandler);
    return attrValHandler;
}
} // namespace ACELite
} // namespace OHOS

#endif // FEATURE_COMPONENT_TABS
