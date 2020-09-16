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
#ifndef OHOS_ACELITE_TEXT_COMPONENT_H
#define OHOS_ACELITE_TEXT_COMPONENT_H

#include "component.h"

#include "js_app_context.h"
#include "js_fwk_common.h"
#include "non_copyable.h"
#include "ui_label.h"

namespace OHOS {
namespace ACELite {
class TextComponent : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TextComponent);
    TextComponent() = delete;
    TextComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~TextComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    bool ApplyPrivateStyle(const AppStyleItem* styleItem) override;
    UILabel* GetUILabelView() const;
    void PostRender() override;
    void PostUpdate(uint16_t attrKeyId, bool updateResult) override;

private:
    // parse js text align style to ui_label
    void SetTextAlign(UILabel& label, const AppStyleItem* styleItem) const;
    // parse js text size style to fontSize_
    void SetTextSize(const AppStyleItem* styleItem);
    // parse js text color style to ui_label
    void SetTextColor(UILabel& label, const AppStyleItem* styleItem) const;
    // parse js text overflow style to ui_label
    void SetTextOverflow(UILabel& label, const AppStyleItem* styleItem);
    // parse js text letter space style to ui_label
    void SetTextLetterSpace(UILabel& label, const AppStyleItem* styleItem) const;
    // parse js text line height style to ui_label
    void SetTextLineHeight(UILabel& label, const AppStyleItem* styleItem) const;
    UILabel* uiLabel_;
    uint8_t fontSize_;
    char* fontFamily_;
    char* textValue_;
    uint8_t overflowMode_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_TEXT_COMPONENT_H
