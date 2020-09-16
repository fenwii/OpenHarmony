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

#ifndef OHOS_ACELITE_APP_STYLE_MANAGER_H
#define OHOS_ACELITE_APP_STYLE_MANAGER_H

#include "non_copyable.h"
#include "stylemgr/app_style.h"
#include "stylemgr/app_style_sheet.h"

namespace OHOS {
namespace ACELite {
class Component;
class AppStyleManager final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(AppStyleManager);
    AppStyleManager();
    ~AppStyleManager();

    void InitStyleSheet(jerry_value_t jsStyleSheetObj);
    // combine id/static class/static styles for current tag from arguments of createElement function
    void CombineStylesForCurrentTag(const jerry_value_t options, Component& currentComponent);
    const AppStyle* GetCombinedStyle() const;
    const AppStyleItem* GetCombinedStyleItem(const char * const name) const;
    void ResetCombinedStyle();
    const AppStyleSheet* GetStyleSheet() const;

private:
    void HandleInlineStyles(const jerry_value_t options, Component& currentComponent);
    void HandleStaticStyle(const jerry_value_t options);
    void HandleDynamicStyle(const jerry_value_t options, Component& currentComponent);
    void HandleIDSelectors(const jerry_value_t options);
    void HandleClassSelectors(const jerry_value_t options);
    void HandleSelectors(const jerry_value_t options, const jerry_value_t type);
    void HandleSingleSelector(const jerry_value_t selectorValue, const jerry_value_t type);
    void CombineStyleItem(jerry_value_t stylePropName, jerry_value_t stylePropValue);
    void AppendToCombinedStyle(AppStyleItem* newStyle);
    void CombineStyle(AppStyle* appStyle);
    jerry_value_t GetStyleObjFromOptions(jerry_value_t options, const jerry_value_t name);
    AppStyleSheet* styleSheet_;
    AppStyle* combinedStyle_; // record the combined styles for current tag
    // prepare jerry string value in advance to speed up
    jerry_value_t idStrValue_;
    jerry_value_t attrsStrValue_;
    jerry_value_t dynamicStyleStrValue_;
    jerry_value_t staticStyleStrValue_;
    jerry_value_t staticClassStrValue_;
    static const char * const ID;
    static const char * const ATTR_STATIC_STYLE;
    static const char * const ATTR_DYNAMIC_STYLE;
    static const char * const ATTR_STATIC_CLASS;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_APP_STYLE_MANAGER_H
