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

#include "picker_view_component.h"
#include "ace_log.h"
#include "ace_mem_base.h"
#include "key_parser.h"
#include "keys.h"
#include "ui_font.h"

namespace OHOS {
namespace ACELite {
#ifdef FEATURE_COMPONENT_DATE_PICKER
void DatePickerListener::OnDatePickerStoped(UIDatePicker &picker)
{
    if (!jerry_value_is_function(dateCallback_)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "DatePickerListener: callback type invalid!");
        return;
    }
    uint32_t year = (picker.GetSelectYear() == nullptr) ? 0 : strtol(picker.GetSelectYear(), nullptr, DEC);
    uint32_t month = (picker.GetSelectMonth() == nullptr) ? 0 : strtol(picker.GetSelectMonth(), nullptr, DEC);
    uint32_t day = (picker.GetSelectDay() == nullptr) ? 0 : strtol(picker.GetSelectDay(), nullptr, DEC);

    jerry_value_t arg = jerry_create_object();
    JerrySetNumberProperty(arg, DATE_PICKER_YEAR, year);
    JerrySetNumberProperty(arg, DATE_PICKER_MONTH, month);
    JerrySetNumberProperty(arg, DATE_PICKER_DAY, day);
    CallJSFunctionAutoRelease(dateCallback_, UNDEFINED, &arg, 1);
    jerry_release_value(arg);
}
#endif // FEATURE_COMPONENT_DATE_PICKER

void TextPickerListener::OnPickerStoped(UIPicker& picker)
{
    if (!jerry_value_is_function(textCallback_)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "TextPickerListener: callback type invalid!");
        return;
    }
    uint16_t index = picker.GetSelected();
    jerry_value_t arg = jerry_create_object();
    JerrySetStringProperty(arg, TEXT_PICKER_NEW_VALUE, pTextArray_[index]);
    JerrySetNumberProperty(arg, TEXT_PICKER_NEW_SELECTED, index);
    CallJSFunctionAutoRelease(textCallback_, UNDEFINED, &arg, 1);
    jerry_release_value(arg);
}

void TimePickerListener::OnTimePickerStoped(UITimePicker &picker)
{
    if (!jerry_value_is_function(timeCallback_)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "TimePickerListener: callback type invalid!");
        return;
    }
    uint32_t hour = (picker.GetSelectHour() == nullptr) ? 0 : strtol(picker.GetSelectHour(), nullptr, DEC);
    uint32_t minute = (picker.GetSelectMinute() == nullptr) ? 0 : strtol(picker.GetSelectMinute(), nullptr, DEC);

    jerry_value_t arg = jerry_create_object();
    JerrySetNumberProperty(arg, TIME_PICKER_HOUR, hour);
    JerrySetNumberProperty(arg, TIME_PICKER_MINUTE, minute);
    CallJSFunctionAutoRelease(timeCallback_, UNDEFINED, &arg, 1);
    jerry_release_value(arg);
}

PickerViewComponent::PickerViewComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager),
      options_(options),
      pickerType_(PickerType::TEXT),
      pickerView_(nullptr),
      color_(Color::Gray()),
      fontSize_(DEFAULT_FONT_SIZE),
      fontFamily_(nullptr),
      selectedColor_(Color::White()),
      selectedFontSize_(PICKER_SELECTED_FONT_SIZE),
      selectedFontFamily_(nullptr),
      textSelected_(0),
      pTextArray_(nullptr),
      textArraySize_(0),
      textPickerListener_(nullptr),
#ifdef FEATURE_COMPONENT_DATE_PICKER
      dateSelected_(nullptr),
      dateStart_(nullptr),
      dateEnd_(nullptr),
      datePickerListener_(nullptr),
#endif // FEATURE_COMPONENT_DATE_PICKER
      timePickerListener_(nullptr),
      timeSelected_(nullptr)
{
    SetComponentName(K_PICKER_VIEW);
}

bool PickerViewComponent::CreateNativeViews()
{
    bool result = false;
    pickerType_ = GetPickerType();
    switch (pickerType_) {
        case PickerType::TEXT: {
            result = CreateTextPicker();
            break;
        }
        case PickerType::TIME: {
            result = CreateTimePicker();
            break;
        }
#ifdef FEATURE_COMPONENT_DATE_PICKER
        case PickerType::DATE: {
            result = CreateDatePicker();
            break;
        }
#endif // FEATURE_COMPONENT_DATE_PICKER
        case PickerType::UNKNOWN: {
            HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: picker view type invalid!");
            break;
        }
        default:
            break;
    }

    if (pickerView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: create native view failed!");
        result = false;
    }
    if (result) {
        result = (CopyFontFamily(fontFamily_, DEFAULT_FONT_FAMILY)) &&
            (CopyFontFamily(selectedFontFamily_, DEFAULT_FONT_FAMILY));
    }
    return result;
}

bool PickerViewComponent::CreateTextPicker()
{
    UIPicker *uiPicker = new UIPicker();
    if (uiPicker == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: create text picker failed!");
        return false;
    }
    textPickerListener_ = new TextPickerListener();
    if (textPickerListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: create text picker listener failed!");
        delete uiPicker;
        uiPicker = nullptr;
        return false;
    }
    uiPicker->SetItemHeight(PICKER_ITEM_HEIGHT);
    pickerView_ = static_cast<UIView *>(uiPicker);
    return true;
}

bool PickerViewComponent::CreateTimePicker()
{
    UITimePicker *uiTimePicker = new UITimePicker();
    if (uiTimePicker == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: create time picker failed");
        return false;
    }
    timePickerListener_ = new TimePickerListener();
    if (timePickerListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: create time picker listener failed");
        delete uiTimePicker;
        uiTimePicker = nullptr;
        return false;
    }
    uiTimePicker->SetItemHeight(PICKER_ITEM_HEIGHT);
    pickerView_ = static_cast<UIView *>(uiTimePicker);
    return true;
}

#ifdef FEATURE_COMPONENT_DATE_PICKER
bool PickerViewComponent::CreateDatePicker()
{
    UIDatePicker *uiDatePicker = new UIDatePicker();
    if (uiDatePicker == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: create date picker failed");
        return false;
    }
    datePickerListener_ = new DatePickerListener();
    if (datePickerListener_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: create date picker failed");
        delete uiDatePicker;
        uiDatePicker = nullptr;
        return false;
    }
    uiDatePicker->SetItemHeight(PICKER_ITEM_HEIGHT);
    pickerView_ = static_cast<UIView *>(uiDatePicker);
    return true;
}
#endif // FEATURE_COMPONENT_DATE_PICKER

void PickerViewComponent::ReleaseTextRange()
{
    // free text picker resources
    if ((textArraySize_ > 0) && pTextArray_) {
        for (uint16_t index = 0; index < textArraySize_; index++) {
            if (pTextArray_[index]) {
                ace_free(pTextArray_[index]);
                pTextArray_[index] = nullptr;
            }
        }
        delete[] pTextArray_;
        pTextArray_ = nullptr;
    }
}
void PickerViewComponent::ReleaseNativeViews()
{
    if (pickerView_ != nullptr) {
        delete pickerView_;
        pickerView_ = nullptr;
    }

    ReleaseTextRange();

    if (textPickerListener_ != nullptr) {
        delete textPickerListener_;
        textPickerListener_ = nullptr;
    }

    // free time picker resources
    if (timePickerListener_ != nullptr) {
        delete timePickerListener_;
        timePickerListener_ = nullptr;
    }
    ACE_FREE(timeSelected_);
    ACE_FREE(fontFamily_);
    ACE_FREE(selectedFontFamily_);

#ifdef FEATURE_COMPONENT_DATE_PICKER
    // free date picker resources
    if (datePickerListener_ != nullptr) {
        delete datePickerListener_;
        datePickerListener_ = nullptr;
    }
    ACE_FREE(dateSelected_);
    ACE_FREE(dateStart_);
    ACE_FREE(dateEnd_);
#endif // FEATURE_COMPONENT_DATE_PICKER
}

inline UIView *PickerViewComponent::GetComponentRootView() const
{
    return pickerView_;
}

void PickerViewComponent::PostRender()
{
    if (pickerView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: no native view for post render!");
        return;
    }

    UpdatePickerStyles();
    UpdatePickerAttrs();
}

void PickerViewComponent::PostUpdate(uint16_t attrKeyId, bool updateResult)
{
    if ((pickerView_ == nullptr) || !updateResult) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: post update failed!");
        return;
    }

    switch (attrKeyId) {
        case K_SELECTED:
#ifdef FEATURE_COMPONENT_DATE_PICKER
        case K_START:
        case K_END:
#endif // FEATURE_COMPONENT_DATE_PICKER
            UpdatePickerAttrs();
            break;
        case K_COLOR:
        case K_FONT_SIZE:
        case K_FONT_FAMILY:
        case K_SELECTED_COLOR:
        case K_SELECTED_FONT_SIZE:
        case K_SELECTED_FONT_FAMILY:
            UpdatePickerStyles();
            break;
        default:
            break;
    }
}

void PickerViewComponent::UpdatePickerStyles() const
{
    if (pickerView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: update picker styles failed!");
        return;
    }
    if ((fontFamily_ == nullptr) || (fontSize_ == 0) ||
        (selectedFontFamily_ == nullptr) || (selectedFontSize_ == 0)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: font family or size invalid!");
        return;
    }
    UIFont* font = UIFont::GetInstance();
    if (font == nullptr) {
        return;
    }

    switch (pickerType_) {
        case PickerType::TEXT: {
            UIPicker *textPicker = reinterpret_cast<UIPicker *>(pickerView_);
            textPicker->SetBackgroundFont(fontFamily_, fontSize_);
            textPicker->SetHighlightFont(selectedFontFamily_, selectedFontSize_);
            textPicker->SetTextColor(color_, selectedColor_);
            break;
        }
        case PickerType::TIME: {
            UITimePicker *timePicker = reinterpret_cast<UITimePicker *>(pickerView_);
            timePicker->SetBackgroundFont(fontFamily_, fontSize_);
            timePicker->SetHighlightFont(selectedFontFamily_, selectedFontSize_);
            timePicker->SetTextColor(color_, selectedColor_);
            break;
        }
#ifdef FEATURE_COMPONENT_DATE_PICKER
        case PickerType::DATE: {
            uint8_t fontId = font->GetFontId(fontFamily_, fontSize_);
            uint8_t selectedFontId = font->GetFontId(selectedFontFamily_, selectedFontSize_);
            UIDatePicker *datePicker = reinterpret_cast<UIDatePicker *>(pickerView_);
            datePicker->SetTextStyle(fontId, selectedFontId, color_, selectedColor_);
            break;
        }
#endif // FEATURE_COMPONENT_DATE_PICKER
        default:
            break;
    }
}

void PickerViewComponent::UpdatePickerAttrs() const
{
    if (pickerView_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: update picker attributes failed!");
        return;
    }
    switch (pickerType_) {
        case PickerType::TEXT: {
            UIPicker *textPicker = reinterpret_cast<UIPicker *>(pickerView_);
            textPicker->SetSelected(textSelected_);
            break;
        }
        case PickerType::TIME: {
            UITimePicker *timePicker = reinterpret_cast<UITimePicker *>(pickerView_);
            if (timeSelected_ != nullptr) {
                timePicker->SetSelected(timeSelected_);
            }
            break;
        }
#ifdef FEATURE_COMPONENT_DATE_PICKER
        case PickerType::DATE: {
            UIDatePicker *datePicker = reinterpret_cast<UIDatePicker *>(pickerView_);
            if (dateStart_ != nullptr) {
                datePicker->SetStart(dateStart_);
            }
            if (dateEnd_ != nullptr) {
                datePicker->SetEnd(dateEnd_);
            }
            if (dateSelected_ != nullptr) {
                datePicker->SetSelected(dateSelected_);
            }
            break;
        }
#endif // FEATURE_COMPONENT_DATE_PICKER
        default:
            break;
    }
}

bool PickerViewComponent::SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue)
{
    bool result = true;
    switch (attrKeyId) {
        case K_SELECTED: {
            result = SetPickerSelected(attrValue);
            break;
        }
        case K_RANGE: {
            if (pickerType_ == PickerType::TEXT) {
                result = SetTextPickerRange(attrValue);
            }
            break;
        }
#ifdef FEATURE_COMPONENT_DATE_PICKER
        case K_START: {
            if (pickerType_ == PickerType::DATE) {
                ACE_FREE(dateStart_);
                dateStart_ = MallocStringOf(attrValue);
            }
            break;
        }
        case K_END: {
            if (pickerType_ == PickerType::DATE) {
                ACE_FREE(dateEnd_);
                dateEnd_ = MallocStringOf(attrValue);
            }
            break;
        }
#endif // FEATURE_COMPONENT_DATE_PICKER
        default:
            result = false;
            break;
    }
    return result;
}

bool PickerViewComponent::ApplyPrivateStyle(const AppStyleItem *styleItem)
{
    uint16_t styleNameId = GetStylePropNameId(styleItem);
    if (!KeyParser::IsKeyValid(styleNameId)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: apply private style failed!");
        return false;
    }
    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    switch (styleNameId) {
        case K_COLOR:
            if (!GetStyleColorValue(styleItem, color, alpha)) {
                return false;
            }
            color_ = GetRGBColor(color);
            break;
        case K_FONT_SIZE:
            fontSize_ = GetStylePixelValue(styleItem);
            break;
        case K_FONT_FAMILY:
            CopyFontFamily(fontFamily_, GetStyleStrValue(styleItem));
            break;
        case K_SELECTED_COLOR:
            if (!GetStyleColorValue(styleItem, color, alpha)) {
                return false;
            }
            selectedColor_ = GetRGBColor(color);
            break;
        case K_SELECTED_FONT_SIZE:
            selectedFontSize_ = GetStylePixelValue(styleItem);
            break;
        case K_SELECTED_FONT_FAMILY:
            CopyFontFamily(selectedFontFamily_, GetStyleStrValue(styleItem));
            break;
        default:
            return false;
    }
    return true;
}

bool PickerViewComponent::RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue)
{
    bool result = false;
    switch (eventTypeId) {
        case K_CHANGE: {
            SetPickerListener(funcValue);
            result = true;
            break;
        }
        default:
            break;
    }
    return result;
}

char *PickerViewComponent::GetStringAttrByName(const char * const name, uint16_t &length) const
{
    if (jerry_value_is_undefined(options_)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: options undefined!");
        return nullptr;
    }

    char *strValue = nullptr;
    jerry_value_t attrsPropValue = jerryx_get_property_str(options_, ATTR_ATTRS);
    if (!jerry_value_is_undefined(attrsPropValue)) {
        strValue = JerryMallocStringProperty(attrsPropValue, name, length);
    }
    jerry_release_value(attrsPropValue);
    return strValue;
}

PickerViewComponent::PickerType PickerViewComponent::GetPickerType() const
{
    uint16_t length = 0;
    char *typeStr = GetStringAttrByName(ATTR_TYPE, length);
    if (typeStr == nullptr) {
        return PickerType::TEXT;
    }

    PickerType type = PickerType::UNKNOWN;
    uint16_t typeId = KeyParser::ParseKeyId(typeStr, length);
    switch (typeId) {
        case K_TEXT:
            type = PickerType::TEXT;
            break;
        case K_TIME:
            type = PickerType::TIME;
            break;
#ifdef FEATURE_COMPONENT_DATE_PICKER
        case K_DATE:
            type = PickerType::DATE;
            break;
#endif // FEATURE_COMPONENT_DATE_PICKER
        default:
            type = PickerType::UNKNOWN;
            break;
    }
    ace_free(typeStr);
    typeStr = nullptr;
    return type;
}

bool PickerViewComponent::SetPickerSelected(jerry_value_t selectedValue)
{
    switch (pickerType_) {
        case PickerType::TEXT: {
            textSelected_ = IntegerOf(selectedValue);
            break;
        }
        case PickerType::TIME: {
            ACE_FREE(timeSelected_);
            timeSelected_ = MallocStringOf(selectedValue);
            break;
        }
#ifdef FEATURE_COMPONENT_DATE_PICKER
        case PickerType::DATE: {
            ACE_FREE(dateSelected_);
            dateSelected_ = MallocStringOf(selectedValue);
            break;
        }
#endif // FEATURE_COMPONENT_DATE_PICKER
        default:
            break;
    }
    return true;
}

void PickerViewComponent::SetPickerListener(jerry_value_t funcValue) const
{
    switch (pickerType_) {
        case PickerType::TEXT: {
            if (textPickerListener_ != nullptr) {
                UIPicker *textPicker = reinterpret_cast<UIPicker *>(pickerView_);
                textPickerListener_->SetTextCallback(funcValue);
                textPicker->RegisterSelectedListener(textPickerListener_);
            }
            break;
        }
        case PickerType::TIME: {
            if (timePickerListener_ != nullptr) {
                UITimePicker *timePicker = reinterpret_cast<UITimePicker *>(pickerView_);
                timePickerListener_->SetTimeCallback(funcValue);
                timePicker->RegisterSelectedListener(timePickerListener_);
            }
            break;
        }
#ifdef FEATURE_COMPONENT_DATE_PICKER
        case PickerType::DATE: {
            if (datePickerListener_ != nullptr) {
                UIDatePicker *datePicker = reinterpret_cast<UIDatePicker *>(pickerView_);
                datePickerListener_->SetDateCallback(funcValue);
                datePicker->RegisterSelectedListener(datePickerListener_);
            }
            break;
        }
#endif // FEATURE_COMPONENT_DATE_PICKER
        default:
            break;
    }
}

bool PickerViewComponent::SetTextPickerRange(jerry_value_t rangeValue)
{
    textArraySize_ = jerry_get_array_length(rangeValue);
    if (textArraySize_ == 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: text picker range invalid!");
        return false;
    }

    ReleaseTextRange();

    pTextArray_ = new char *[textArraySize_];
    if (pTextArray_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: allocate memory for dynamic array failed!");
        return false;
    }

    for (uint16_t index = 0; index < textArraySize_; index++) {
        jerry_value_t element = jerry_get_property_by_index(rangeValue, index);
        char *elementStr = MallocStringOf(element);
        jerry_release_value(element);
        if (elementStr == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "PickerViewComponent: text picker range contents invalid!");
            textArraySize_ = index;
            return false;
        }
        pTextArray_[index] = elementStr;
    }
    UIPicker *textPicker = reinterpret_cast<UIPicker *>(pickerView_);
    if (textPickerListener_ != nullptr) {
        textPickerListener_->SetTextRange(pTextArray_); // call SetTextRange before SetValues!
    }
    textPicker->SetValues(const_cast<const char **>(pTextArray_), textArraySize_);
    return true;
}
} // namespace ACELite
} // namespace OHOS
