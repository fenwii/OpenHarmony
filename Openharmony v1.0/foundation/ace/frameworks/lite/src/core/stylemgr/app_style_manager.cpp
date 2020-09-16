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

#include "stylemgr/app_style_manager.h"
#include "ace_log.h"
#include "component.h"

namespace OHOS {
namespace ACELite {
const char * const AppStyleManager::ID = "id";
const char * const AppStyleManager::ATTR_STATIC_STYLE = "staticStyle";
const char * const AppStyleManager::ATTR_DYNAMIC_STYLE = "dynamicStyle";
const char * const AppStyleManager::ATTR_STATIC_CLASS = "staticClass";
AppStyleManager::AppStyleManager() : styleSheet_(nullptr), combinedStyle_(nullptr)
{
    // prepare jerry string value in advance to less the overhead
    idStrValue_ = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ID));
    attrsStrValue_ = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ATTR_ATTRS));
    staticStyleStrValue_ = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ATTR_STATIC_STYLE));
    dynamicStyleStrValue_ = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ATTR_DYNAMIC_STYLE));
    staticClassStrValue_ = jerry_create_string(reinterpret_cast<const jerry_char_t *>(ATTR_STATIC_CLASS));
}

AppStyleManager::~AppStyleManager()
{
    if (combinedStyle_ != nullptr) {
        combinedStyle_->Reset();
        delete combinedStyle_;
        combinedStyle_ = nullptr;
    }

    if (styleSheet_ != nullptr) {
        styleSheet_->Reset();
        delete styleSheet_;
        styleSheet_ = nullptr;
    }
    ReleaseJerryValue(idStrValue_, attrsStrValue_, dynamicStyleStrValue_, staticStyleStrValue_, staticClassStrValue_,
                      VA_ARG_END_FLAG);
}

const AppStyle *AppStyleManager::GetCombinedStyle() const
{
    return combinedStyle_;
}

const AppStyleItem *AppStyleManager::GetCombinedStyleItem(const char * const name) const
{
    if (combinedStyle_ != nullptr) {
        return combinedStyle_->GetStyleItemByName(name);
    }
    return nullptr;
}

void AppStyleManager::ResetCombinedStyle()
{
    // do not free the combinedStyle_ object, just reset the content of it,
    // that will slow down the next combining action for next component,
    // it will be freed in ~AppStyleManager after the app exits
    if (combinedStyle_ != nullptr) {
        combinedStyle_->Reset();
    }
}

const AppStyleSheet *AppStyleManager::GetStyleSheet() const
{
    return styleSheet_;
}

void AppStyleManager::InitStyleSheet(jerry_value_t jsStyleSheetObj)
{
    if (jerry_value_is_undefined(jsStyleSheetObj) || jerry_value_is_error(jsStyleSheetObj)) {
        return;
    }

    if (styleSheet_ == nullptr) {
        styleSheet_ = new AppStyleSheet();
    }

    if (styleSheet_ != nullptr) {
        styleSheet_->InitSheet(jsStyleSheetObj);
    }
}

// { attrs: { x: '0', y: '0' }, staticClass: 'divStyle', staticStyle: {display: 'flex', width: 454, height: 454} }
void AppStyleManager::CombineStylesForCurrentTag(const jerry_value_t options, Component &currentComponent)
{
    // reset first
    ResetCombinedStyle();

    if (jerry_value_is_undefined(options)) {
        HILOG_WARN(HILOG_MODULE_ACE, "combine styles for current tag failed");
        return;
    }

    // handle static styles
    HandleInlineStyles(options, currentComponent);

    // handle id selector
    HandleIDSelectors(options);

    // handle class selector
    HandleClassSelectors(options);
}

// return value must be released by caller
jerry_value_t AppStyleManager::GetStyleObjFromOptions(jerry_value_t options, const jerry_value_t name)
{
    jerry_value_t value = UNDEFINED;
    if (jerry_value_is_undefined(options) || jerry_value_is_undefined(name)) {
        return value;
    }

    jerry_value_t valueContainer = options;
    bool containerNeedReleased = false;
    if (name == idStrValue_) {
        // get attrs object from options
        if (!HasOwnProperty(options, attrsStrValue_)) {
            // if no attrs in options, return undefined directly
            return value;
        }
        valueContainer = jerry_get_property(options, attrsStrValue_);
        // mark that the valueContainer need to be released when getting out of scope
        containerNeedReleased = true;
    }

    // check if container object have target property, if not, just return undefined
    if (HasOwnProperty(valueContainer, name)) {
        value = jerry_get_property(valueContainer, name);
    }

    if (containerNeedReleased) {
        jerry_release_value(valueContainer);
    }
    return value;
}

void AppStyleManager::HandleInlineStyles(const jerry_value_t options, Component &currentComponent)
{
    // handle static inline styles
    HandleStaticStyle(options);
    // handle dynamic inline styles
    HandleDynamicStyle(options, currentComponent);
}

void AppStyleManager::HandleStaticStyle(const jerry_value_t options)
{
    jerry_value_t staticStyleValue = GetStyleObjFromOptions(options, staticStyleStrValue_);
    if (jerry_value_is_undefined(staticStyleValue)) {
        return;
    }

    jerry_value_t propKeys = jerry_get_object_keys(staticStyleValue);
    uint32_t propKeySize = jerry_get_array_length(propKeys);
    for (uint32_t index = 0; index < propKeySize; index++) {
        jerry_value_t propKey = jerry_get_property_by_index(propKeys, index);
        jerry_value_t propValue = jerry_get_property(staticStyleValue, propKey);
        CombineStyleItem(propKey, propValue);
        ReleaseJerryValue(propKey, propValue, VA_ARG_END_FLAG);
    }
    ReleaseJerryValue(propKeys, staticStyleValue, VA_ARG_END_FLAG);
}

void AppStyleManager::HandleDynamicStyle(const jerry_value_t options, Component &currentComponent)
{
    jerry_value_t dynamicStyleValue = GetStyleObjFromOptions(options, dynamicStyleStrValue_);
    if (jerry_value_is_undefined(dynamicStyleValue)) {
        return;
    }

    jerry_value_t propKeys = jerry_get_object_keys(dynamicStyleValue);
    uint32_t propKeySize = jerry_get_array_length(propKeys);
    for (uint32_t index = 0; index < propKeySize; index++) {
        jerry_value_t propKey = jerry_get_property_by_index(propKeys, index);
        jerry_value_t propValue = jerry_get_property(dynamicStyleValue, propKey);
        // parse expression and new watcher for it
        if (jerry_value_is_function(propValue)) {
            jerry_value_t expressionValue = currentComponent.ParseExpression(propKey, propValue);
            // the expression's calculating result should be used, not the function value itself
            CombineStyleItem(propKey, expressionValue);
            if (expressionValue != propValue) {
                // generally, ParseExpression() will calculate the expression function's value and return
                // the result back, so it's need to be released
                jerry_release_value(expressionValue);
            }
        }
        ReleaseJerryValue(propKey, propValue, VA_ARG_END_FLAG);
    }
    ReleaseJerryValue(propKeys, dynamicStyleValue, VA_ARG_END_FLAG);
}

void AppStyleManager::HandleSingleSelector(const jerry_value_t prop, const jerry_value_t type)
{
    if (jerry_value_is_undefined(prop) || jerry_value_is_undefined(type)) {
        return;
    }

    uint16_t strLen = 0;
    char *valueBuffer = MallocStringOf(prop, &strLen);
    if (valueBuffer == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "convert id value to char failed, will be dropped");
        return;
    } else {
        if (strLen == 0) {
            ace_free(valueBuffer);
            valueBuffer = nullptr;
            return;
        }
    }

    AppStyle *style = nullptr;
    if (type == idStrValue_ && styleSheet_ != nullptr) {
        style = styleSheet_->GetStyleFromIDSelectors(valueBuffer);
    } else if (type == staticClassStrValue_ && styleSheet_ != nullptr) {
        style = styleSheet_->GetStyleFromClassSelectors(valueBuffer);
    } else {
        HILOG_WARN(HILOG_MODULE_ACE, "not supported yet");
    }
    ace_free(valueBuffer);
    valueBuffer = nullptr;
    CombineStyle(style);
}

void AppStyleManager::HandleSelectors(const jerry_value_t options, const jerry_value_t type)
{
    if (styleSheet_ == nullptr) {
        return;
    }

    jerry_value_t propValue = GetStyleObjFromOptions(options, type);
    if (jerry_value_is_undefined(propValue)) {
        return;
    }

    if (!jerry_value_is_array(propValue)) {
        // if is not array, just handle it
        HandleSingleSelector(propValue, type);
    } else {
        // support array
        uint32_t propCount = jerry_get_array_length(propValue);
        if (propCount > 0 && propCount < UINT8_MAX) {
            // do reverse traversal to ensure style override correctly
            while (propCount > 0) {
                jerry_value_t property = jerry_get_property_by_index(propValue, (propCount - 1));
                HandleSingleSelector(property, type);
                jerry_release_value(property);
                propCount--;
            }
        } else {
            HILOG_ERROR(HILOG_MODULE_ACE, "invalid prop count");
        }
    }
    jerry_release_value(propValue);
}

void AppStyleManager::HandleIDSelectors(const jerry_value_t options)
{
    HandleSelectors(options, idStrValue_);
}

void AppStyleManager::HandleClassSelectors(const jerry_value_t options)
{
    HandleSelectors(options, staticClassStrValue_);
}

void AppStyleManager::CombineStyle(AppStyle *appStyle)
{
    if (appStyle == nullptr) {
        return;
    }

    // go through id style's all items, add it to combinedStyle_ if it's not in it
    const AppStyleItem *styleItem = appStyle->GetFirst();
    while (styleItem != nullptr) {
        if (combinedStyle_) {
            uint16_t styleItemNameId = styleItem->GetPropNameId();
            // if it's already in combined style, skip, as it's lower priority
            const AppStyleItem *exitCombinedStyleItem = combinedStyle_->GetStyleItemByNameId(styleItemNameId);
            if ((exitCombinedStyleItem == nullptr) ||
                (exitCombinedStyleItem->GetPseudoClassType() != styleItem->GetPseudoClassType())) {
                AppStyleItem *newItem = AppStyleItem::CopyFrom(styleItem);
                AppendToCombinedStyle(newItem);
            }
            styleItem = styleItem->GetNext();
        } else {
            /* if combinedStyle_ is null, add all items directly */
            while (styleItem != nullptr) {
                AppStyleItem *newItem = AppStyleItem::CopyFrom(styleItem);
                AppendToCombinedStyle(newItem);
                styleItem = styleItem->GetNext();
            }
        }
    }
}

void AppStyleManager::CombineStyleItem(jerry_value_t stylePropName, jerry_value_t stylePropValue)
{
    AppStyleItem *newStyleItem = AppStyleItem::GenerateFromJSValue(stylePropName, stylePropValue);
    AppendToCombinedStyle(newStyleItem);
}

void AppStyleManager::AppendToCombinedStyle(AppStyleItem *newStyleItem)
{
    if (newStyleItem == nullptr) {
        return;
    }

    if (combinedStyle_ == nullptr) {
        combinedStyle_ = new AppStyle();
    }

    combinedStyle_->AddStyleItem(newStyleItem);
}
} // namespace ACELite
} // namespace OHOS
