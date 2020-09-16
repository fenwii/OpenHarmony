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
#ifndef OHOS_ACELITE_INPUT_COMPONENT_H
#define OHOS_ACELITE_INPUT_COMPONENT_H
#include "component.h"
#include "key_parser.h"
#include "non_copyable.h"
#include "ui_checkbox.h"
#include "ui_label_button.h"
#include "ui_radiobutton.h"

namespace OHOS {
namespace ACELite {
class InputComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(InputComponent);
    InputComponent() = delete;
    InputComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *manager)
        : Component(options, children, manager),
          options_(options),
          checkbox_(nullptr),
          button_(nullptr),
          radioButton_(nullptr),
          changeListener_(nullptr),
          clickListener_(nullptr),
          pressedBackGroundColorValue_(-1),
          normalBackGroundImg_(nullptr),
          pressedBackGroundImg_(nullptr),
          textValue_(nullptr),
          fontFamily_(nullptr),
          fontSize_(DEFAULT_FONT_SIZE)
    {
        uint8_t pressedOpacityValue = 255;
        pressedOpacityValue_ = pressedOpacityValue;
        SetComponentName(K_INPUT);
    }
    ~InputComponent() override {}
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    bool RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue) override;
    bool ApplyPrivateStyle(const AppStyleItem *style) override;
    void PostRender() override;
    void PostUpdate(uint16_t attrKeyId, bool updateResult) override;

protected:
    UIView *GetComponentRootView() const override
    {
        if (checkbox_ != nullptr) {
            return checkbox_;
        } else if (radioButton_ != nullptr) {
            return radioButton_;
        } else {
            return button_;
        }
    }

private:
    bool SetTextAlign(const AppStyleItem *style) const;
    bool SetFontSize(const AppStyleItem *style);
    bool HandleButtonBackGroundImg(const AppStyleItem &styleItem);
    void DealEvent();
    void CreateCheckboxOrRadio();
    bool SetBackgroundColor(const AppStyleItem &style);
    bool SetColor(const AppStyleItem &style) const;
    bool HandleImage(const AppStyleItem &style);
    jerry_value_t options_;
    UICheckBox *checkbox_;
    UILabelButton *button_;
    UIRadioButton *radioButton_;
    StateChangeListener *changeListener_;
    ViewOnClickListener *clickListener_;
    int32_t pressedBackGroundColorValue_;
    uint8_t pressedOpacityValue_;
    char *normalBackGroundImg_;
    char *pressedBackGroundImg_;
    char *textValue_;
    char *fontFamily_;
    uint8_t fontSize_;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_INPUT_COMPONENT_H