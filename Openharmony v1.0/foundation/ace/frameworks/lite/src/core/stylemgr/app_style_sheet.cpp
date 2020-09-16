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

#include "stylemgr/app_style_sheet.h"

namespace OHOS {
namespace ACELite {
void AppStyleSheet::Reset()
{
    if (idSelectors_ != nullptr) {
        idSelectors_->Reset();
        delete idSelectors_;
        idSelectors_ = nullptr;
    }

    if (classSelectors_ != nullptr) {
        classSelectors_->Reset();
        delete classSelectors_;
        classSelectors_ = nullptr;
    }

    if (keyFrameSelectors_ != nullptr) {
        keyFrameSelectors_->Reset();
        delete keyFrameSelectors_;
        keyFrameSelectors_ = nullptr;
    }
}

void AppStyleSheet::InitSheet(jerry_value_t styleSheetObj)
{
    if (jerry_value_is_undefined(styleSheetObj)) {
        return;
    }

    Reset();

    // init all id selectors
    const char * const attrIdSelectors = "idSelectors";
    jerry_value_t propName = jerry_create_string(reinterpret_cast<jerry_char_t *>(const_cast<char *>(attrIdSelectors)));
    jerry_value_t propValue = UNDEFINED;
    if (HasOwnProperty(styleSheetObj, propName)) {
        propValue = jerry_get_property(styleSheetObj, propName);
        InitSelectors(&idSelectors_, propValue, false);
        jerry_release_value(propValue);
    }
    jerry_release_value(propName);

    // init all class selectors
    const char * const attrClassSelectors = "classSelectors";
    propName = jerry_create_string(reinterpret_cast<jerry_char_t *>(const_cast<char *>(attrClassSelectors)));
    if (HasOwnProperty(styleSheetObj, propName)) {
        propValue = jerry_get_property(styleSheetObj, propName);
        InitSelectors(&classSelectors_, propValue, false);
        jerry_release_value(propValue);
    }
    jerry_release_value(propName);

    // init styleSheet
    const char * const keyFrames = "@keyframes";
    propName = jerry_create_string(reinterpret_cast<jerry_char_t *>(const_cast<char *>(keyFrames)));
    if (HasOwnProperty(styleSheetObj, propName)) {
        propValue = jerry_get_property(styleSheetObj, propName);
        InitSelectors(&keyFrameSelectors_, propValue, true);
        jerry_release_value(propValue);
    }
    jerry_release_value(propName);
}

void AppStyleSheet::InitSelectors(AppStyleList** selectorsList, jerry_value_t selectorsObj, bool isKeyFrames)
{
    if (jerry_value_is_undefined(selectorsObj)) {
        return;
    }

    if ((*selectorsList) == nullptr) {
        (*selectorsList) = new AppStyleList();
    }

    jerry_value_t styleKeys = jerry_get_object_keys(selectorsObj);
    uint16_t styleKeySize = jerry_get_array_length(styleKeys);
    for (uint16_t index = 0; index < styleKeySize; index++) {
        /* convert style key into char */
        jerry_value_t styleKey = jerry_get_property_by_index(styleKeys, index);
        jerry_value_t styleValue = jerry_get_property(selectorsObj, styleKey);
        AppStyle* newStyle = AppStyle::GenerateFromJS(styleKey, styleValue, isKeyFrames);
        if (newStyle != nullptr) {
            (*selectorsList)->AddStyle(newStyle);
        }
        ReleaseJerryValue(styleKey, styleValue, VA_ARG_END_FLAG);
    }

    jerry_release_value(styleKeys);
}

AppStyle* AppStyleSheet::GetStyleFromIDSelectors(const char * const name) const
{
    return GetStyleFromSelectors(idSelectors_, name);
}

AppStyle* AppStyleSheet::GetStyleFromClassSelectors(const char * const name) const
{
    return GetStyleFromSelectors(classSelectors_, name);
}

AppStyle* AppStyleSheet::GetStyleFromKeyFramesSelectors(const char * const name) const
{
    return GetStyleFromSelectors(keyFrameSelectors_, name);
}

AppStyle* AppStyleSheet::GetStyleFromSelectors(AppStyleList* selectors, const char * const name) const
{
    if ((selectors == nullptr) || (name == nullptr) || strlen(name) == 0) {
        return nullptr;
    }

    AppStyle* first = const_cast<AppStyle *>(selectors->GetFirst());
    while (first != nullptr) {
        const char *styleName = first->GetStyleName();
        if (styleName != nullptr && !strcmp(name, styleName)) {
            return first;
        }
        first = const_cast<AppStyle *>(first->GetNext());
    }

    return first;
}
} // namespace ACELite
} // namespace OHOS
