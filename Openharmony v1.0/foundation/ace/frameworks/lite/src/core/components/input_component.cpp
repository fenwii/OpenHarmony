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

#include "input_component.h"
#include "ace_log.h"
#include "ace_mem_base.h"
#include "js_app_context.h"
#include "js_fwk_common.h"
#include "key_parser.h"
#include "keys.h"
#include "ui_button.h"
#include "font/ui_font_header.h"

namespace OHOS {
namespace ACELite {
bool InputComponent::CreateNativeViews()
{
    CreateCheckboxOrRadio();
    if ((checkbox_ == nullptr) && (radioButton_ == nullptr)) {
        button_ = new UILabelButton();
        if (button_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "create button failed");
            return false;
        }
        // set font family
        if (!CopyFontFamily(fontFamily_, DEFAULT_FONT_FAMILY)) {
            return false;
        }
        const uint8_t defaultWidth = 100;
        const uint8_t defaultHeight = 50;
        button_->SetWidth(defaultWidth);
        button_->SetHeight(defaultHeight);
        button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
        button_->SetStyle(STYLE_BACKGROUND_OPA, OPA_OPAQUE);
        button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
        button_->SetStyle(STYLE_BACKGROUND_OPA, OPA_OPAQUE);
    }
    return (checkbox_ != nullptr) || (button_ != nullptr) || (radioButton_ != nullptr);
}

void InputComponent::CreateCheckboxOrRadio()
{
    jerry_value_t attrsPropValue = jerryx_get_property_str(options_, ATTR_ATTRS);
    // create component according to attribute type
    const char * const attrType = "type";
    jerry_value_t typeValHandler = jerryx_get_property_str(attrsPropValue, attrType);
    if (!jerry_value_is_undefined(typeValHandler)) {
        uint16_t len = 0;
        char *type = MallocStringOf(typeValHandler, &len);
        uint16_t typeId = KeyParser::ParseKeyId(type, len);
        if (typeId == K_CHECKBOX) {
            checkbox_ = new UICheckBox();
            if (checkbox_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "create checkbox failed.");
            }
        } else if (typeId == K_RADIO) {
            // get the property name
            const char * const nameAttr = "name";
            char *name = nullptr;
            jerry_value_t nameAttrVal = jerryx_get_property_str(attrsPropValue, nameAttr);
            if (!jerry_value_is_undefined(nameAttrVal)) {
                name = MallocStringOf(nameAttrVal);
            }
            jerry_release_value(nameAttrVal);
            if (name == nullptr) {
                const char * const tmpNameVal = "";
                radioButton_ = new UIRadioButton(tmpNameVal);
            } else {
                radioButton_ = new UIRadioButton(name);
            }
            ACE_FREE(name);
            if (radioButton_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "create radioButton failed");
            }
        }
        ACE_FREE(type);
    }
    ReleaseJerryValue(typeValHandler, attrsPropValue, VA_ARG_END_FLAG);
}

void InputComponent::ReleaseNativeViews()
{
    if (checkbox_ != nullptr) {
        delete checkbox_;
        checkbox_ = nullptr;
    }
    if (button_ != nullptr) {
        delete button_;
        button_ = nullptr;
    }
    if (radioButton_ != nullptr) {
        delete radioButton_;
        radioButton_ = nullptr;
    }
    if (changeListener_ != nullptr) {
        delete changeListener_;
        changeListener_ = nullptr;
    }
    if (clickListener_ != nullptr) {
        delete clickListener_;
        clickListener_ = nullptr;
    }
    ACE_FREE(textValue_);
    ACE_FREE(fontFamily_);
    ACE_FREE(normalBackGroundImg_);
    ACE_FREE(pressedBackGroundImg_);
}
bool InputComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    switch (attrKeyId) {
        case K_CHECKED:
            // set the state of checkbox and radioButton
            if ((checkbox_ != nullptr) || (radioButton_ != nullptr)) {
                if (jerry_value_is_boolean(attrValue)) {
                    bool checked = jerry_get_boolean_value(attrValue);
                    UICheckBox::UICheckBoxState state =
                        checked ? UICheckBox::UICheckBoxState::SELECTED : UICheckBox::UICheckBoxState::UNSELECTED;
                    if (checkbox_ != nullptr) {
                        checkbox_->SetState(state);
                    } else {
                        radioButton_->SetState(state);
                    }
                    return true;
                } else {
                    HILOG_ERROR(HILOG_MODULE_ACE, "the checkbox checked is error value");
                    return false;
                }
            }
            break;
        case K_VALUE:
            if (button_ != nullptr) {
                ACE_FREE(textValue_);
                textValue_ = MallocStringOf(attrValue);
                return true;
            }
            break;
        case K_NAME:
            if (radioButton_ != nullptr) {
                char *name = MallocStringOf(attrValue);
                UIRadioButton *radio = static_cast<UIRadioButton *>(radioButton_);
                if (name == nullptr) {
                    const char * const tmpName = "";
                    radio->SetName(tmpName);
                } else {
                    radio->SetName(name);
                    ACE_FREE(name);
                }
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

bool InputComponent::RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    if (eventTypeId == K_CHANGE) {
        if ((checkbox_ != nullptr) || (radioButton_ != nullptr)) {
            if (checkbox_ != nullptr) {
                changeListener_ = new StateChangeListener(funcValue, K_CHECKBOX);
            } else {
                changeListener_ = new StateChangeListener(funcValue, K_RADIO);
            }
            if (changeListener_ == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "create change listener failed");
                return false;
            }
            return true;
        }
    } else if (eventTypeId == K_CLICK) {
        clickListener_ = new ViewOnClickListener(funcValue, eventTypeId);
        if (clickListener_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "create click listener failed");
            return false;
        }
        return true;
    }
    return false;
}

bool InputComponent::ApplyPrivateStyle(const AppStyleItem *style)
{
    if (button_ == nullptr) {
        return HandleImage(*style);
    }
    bool result = true;
    uint16_t styleKey = GetStylePropNameId(style);
    switch (styleKey) {
        case K_FONT_SIZE:
            result = SetFontSize(style);
            break;
        case K_FONT_FAMILY:
            if (IsStyleValueTypeString(style)) {
                // the style would be freed after this method
                result = CopyFontFamily(fontFamily_, GetStyleStrValue(style));
            } else {
                result = false;
            }
            break;
        case K_TEXT_ALIGN:
            result = SetTextAlign(style);
            break;
        case K_COLOR:
            result = SetColor(*style);
            break;
        case K_BACKGROUND_COLOR:
            result = SetBackgroundColor(*style);
            break;
        case K_BACKGROUND_IMAGE:
            result = HandleButtonBackGroundImg(*style);
            break;
        case K_MARGIN: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetMargin(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetMargin(*button_, *style);
            break;
        }
        case K_MARGIN_BOTTOM: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetBottomMargin(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetBottomMargin(*button_, *style);
            break;
        }
        case K_MARGIN_LEFT: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetLeftMargin(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetLeftMargin(*button_, *style);
            break;
        }
        case K_MARGIN_RIGHT: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetRightMargin(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetRightMargin(*button_, *style);
            break;
        }
        case K_MARGIN_TOP: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetTopMargin(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetTopMargin(*button_, *style);
            break;
        }
        case K_PADDING:
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetPadding(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetPadding(*button_, *style);
            break;
        case K_PADDING_BOTTOM:
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetBottomPadding(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetBottomPadding(*button_, *style);
            break;
        case K_PADDING_LEFT:
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetLeftPadding(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetLeftPadding(*button_, *style);
            break;
        case K_PADDING_RIGHT:
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetRightPadding(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetRightPadding(*button_, *style);
            break;
        case K_PADDING_TOP: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetTopPadding(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetTopPadding(*button_, *style);
            break;
        }
        case K_BORDER_BOTTOM_WIDTH:
        case K_BORDER_LEFT_WIDTH:
        case K_BORDER_RIGHT_WIDTH:
        case K_BORDER_TOP_WIDTH:
        case K_BORDER_WIDTH: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetBorderWidth(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetBorderWidth(*button_, *style);
            break;
        }
        case K_BORDER_BOTTOM_COLOR:
        case K_BORDER_LEFT_COLOR:
        case K_BORDER_RIGHT_COLOR:
        case K_BORDER_TOP_COLOR:
        case K_BORDER_COLOR: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetBorderColor(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetBorderColor(*button_, *style);
            break;
        }
        case K_BORDER_RADIUS: {
            button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
            SetBorderRadius(*button_, *style);
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            SetBorderRadius(*button_, *style);
            break;
        }
        default:
            result = false;
            break;
    }
    return result;
}

bool InputComponent::HandleImage(const AppStyleItem &style)
{
    if ((checkbox_ != nullptr) || (radioButton_ != nullptr)) {
        uint16_t styleKey = GetStylePropNameId(&style);
        if (styleKey == K_BACKGROUND_IMAGE) {
            return HandleButtonBackGroundImg(style);
        }
    }
    return false;
}

bool InputComponent::SetBackgroundColor(const AppStyleItem &style)
{
    if (style.GetPseudoClassType() != PSEUDO_CLASS_ACTIVE) {
        // let parent handle the normal state background color style,
        // will be set for released state style of ui button
        button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
        Component::SetBackgroundColor(*button_, style);
        button_->SetStateForStyle(UIButton::ButtonState::RELEASED);
        Component::SetBackgroundColor(*button_, style);
        return true;
    }
    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    if (!GetStyleColorValue(&style, color, alpha)) {
        return false;
    }
    pressedBackGroundColorValue_ = color;
    pressedOpacityValue_ = alpha;
    return true;
}

bool InputComponent::SetColor(const AppStyleItem &style) const
{
    bool result = true;
    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    if (GetStyleColorValue(&style, color, alpha)) {
        button_->SetLabelStyle(STYLE_TEXT_COLOR, GetRGBColor(color).full);
        button_->SetLabelStyle(STYLE_TEXT_OPA, alpha);
    } else {
        result = false;
    }
    return result;
}

bool InputComponent::SetTextAlign(const AppStyleItem *style) const
{
    bool result = true;
    if (IsStyleValueTypeString(style) && GetStyleStrValue(style)) {
        uint16_t valueId = KeyParser::ParseKeyId(GetStyleStrValue(style), GetStyleStrValueLen(style));
        switch (valueId) {
            case K_LEFT:
                button_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT);
                break;
            case K_CENTER:
                button_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
                break;
            case K_RIGHT:
                button_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_RIGHT);
                break;
            default:
                HILOG_ERROR(HILOG_MODULE_ACE, "the value of text-align in input component is error");
                result = false;
                break;
        }
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "the type of style align is error");
        result = false;
    }
    return result;
}

bool InputComponent::SetFontSize(const AppStyleItem *style)
{
    bool result = true;
    fontSize_ = GetStylePixelValue(style);
    return result;
}

bool InputComponent::HandleButtonBackGroundImg(const AppStyleItem &styleItem)
{
    bool result = false;
    if (styleItem.GetValueType() == STYLE_PROP_VALUE_TYPE_STRING) {
        const char * const url = styleItem.GetStrValue();
        char *filePath = CreatePathStrFromUrl(url);
        if (filePath != nullptr) {
            const char * const rootPath = JsAppContext::GetInstance()->GetCurrentAbilityPath();
            char *imagePath = RelocateResourceFilePath(rootPath, filePath);
            if (imagePath == nullptr) {
                ace_free(filePath);
                filePath = nullptr;
                return result;
            }
#ifdef OHOS_ACELITE_PRODUCT_WATCH
            // convert .png/jpeg/bmp to .bin subfix
            CureImagePath(imagePath);
#endif // OHOS_ACELITE_PRODUCT_WATCH
            if ((styleItem.GetPseudoClassType() == PSEUDO_CLASS_ACTIVE)
                || (styleItem.GetPseudoClassType() == PSEUDO_CLASS_CHECKED)) {
                // in case we don't free the buffer after using
                ACE_FREE(pressedBackGroundImg_);
                pressedBackGroundImg_ = imagePath;
            } else {
                // in case we don't free the buffer after using
                ACE_FREE(normalBackGroundImg_);
                normalBackGroundImg_ = imagePath;
            }
            ace_free(filePath);
            filePath = nullptr;
            result = true;
        }
    }
    return result;
}

void InputComponent::PostRender()
{
    if (button_ != nullptr) {
        if (textValue_ != nullptr && fontFamily_ != nullptr) {
            button_->SetFont(fontFamily_, fontSize_);
            button_->SetText(textValue_);
        }
        if (clickListener_ != nullptr) {
            button_->SetOnClickListener(clickListener_);
        }
        if (pressedBackGroundColorValue_ >= 0) {
            button_->SetStateForStyle(UIButton::ButtonState::PRESSED);
            button_->SetStyle(STYLE_BACKGROUND_COLOR, GetRGBColor(pressedBackGroundColorValue_).full);
            button_->SetStyle(STYLE_BACKGROUND_OPA, pressedOpacityValue_);
        }
        if (normalBackGroundImg_ != nullptr || pressedBackGroundImg_ != nullptr) {
            // make sure the normal and pressed image same in case user only set one of them
            char *normalImg = (normalBackGroundImg_ == nullptr) ? pressedBackGroundImg_ : normalBackGroundImg_;
            char *pressedImg = (pressedBackGroundImg_ == nullptr) ? normalBackGroundImg_ : pressedBackGroundImg_;
            button_->SetImageSrc(normalImg, pressedImg);
        }
    }
    DealEvent();
    ACE_FREE(normalBackGroundImg_);
    ACE_FREE(pressedBackGroundImg_);
}

void InputComponent::DealEvent()
{
    if ((checkbox_ == nullptr) && (radioButton_ == nullptr)) {
        return;
    }
    if (changeListener_ != nullptr) {
            if (checkbox_ != nullptr) {
                checkbox_->SetOnChangeListener(changeListener_);
            } else {
                changeListener_->SetView(radioButton_);
                radioButton_->SetOnChangeListener(changeListener_);
            }
            if (clickListener_ == nullptr) {
                // trigger changeEvent
                clickListener_ = new ViewOnClickListener(UNDEFINED, K_CLICK);
                if (clickListener_ == nullptr) {
                    HILOG_ERROR(HILOG_MODULE_ACE, "create click listener failed");
                    return;
                }
            }
        }
        if (clickListener_ != nullptr) {
            clickListener_->SetComponentListener(changeListener_);
            if (checkbox_ != nullptr) {
                checkbox_->SetOnClickListener(clickListener_);
            } else {
                radioButton_->SetOnClickListener(clickListener_);
            }
        }
        if (normalBackGroundImg_ != nullptr || pressedBackGroundImg_ != nullptr) {
            // make sure the normal and pressed image same in case user only set one of them
            char *normalImg = (normalBackGroundImg_ == nullptr) ? pressedBackGroundImg_ : normalBackGroundImg_;
            char *pressedImg = (pressedBackGroundImg_ == nullptr) ? normalBackGroundImg_ : pressedBackGroundImg_;
            if (checkbox_ != nullptr) {
                checkbox_->SetImages(pressedImg, normalImg);
            } else {
                radioButton_->SetImages(pressedImg, normalImg);
            }
        }
}

void InputComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    if (!updateResult || !KeyParser::IsKeyValid(attrKeyId)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "input component post update check args failed");
        return;
    }
    if (button_ != nullptr) {
        switch (attrKeyId) {
            case K_VALUE:
                if (textValue_ != nullptr) {
                    button_->SetText(textValue_);
                }
                break;
            case K_FONT_SIZE:
            case K_FONT_FAMILY:
                if (fontFamily_ != nullptr) {
                    button_->SetFont(fontFamily_, fontSize_);
                }
                break;
            default:
                break;
        }
    }
}
} // namespace ACELite
} // namespace OHOS
