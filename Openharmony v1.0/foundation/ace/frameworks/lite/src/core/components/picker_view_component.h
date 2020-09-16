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

#ifndef OHOS_ACELITE_PICKER_VIEW_COMPONENT_H
#define OHOS_ACELITE_PICKER_VIEW_COMPONENT_H

#include "acelite_config.h"
#include "component.h"
#include "non_copyable.h"
#ifdef FEATURE_COMPONENT_DATE_PICKER
#include "ui_date_picker.h"
#endif // FEATURE_COMPONENT_DATE_PICKER
#include "ui_time_picker.h"

namespace OHOS {
namespace ACELite {
static constexpr char TEXT_PICKER_NEW_VALUE[] = "newValue";
static constexpr char TEXT_PICKER_NEW_SELECTED[] = "newSelected";
static constexpr char TIME_PICKER_HOUR[] = "hour";
static constexpr char TIME_PICKER_MINUTE[] = "minute";
#ifdef FEATURE_COMPONENT_DATE_PICKER
static constexpr char DATE_PICKER_YEAR[] = "year";
static constexpr char DATE_PICKER_MONTH[] = "month";
static constexpr char DATE_PICKER_DAY[] = "day";
#endif // FEATURE_COMPONENT_DATE_PICKER
static constexpr int16_t PICKER_ITEM_HEIGHT = 50; // default picker item height
static constexpr uint8_t PICKER_SELECTED_FONT_SIZE = 38; // F_HYQIHEI_65S_38_4

/**
 * @brief listener class for text picker onchange event.
 */
class TextPickerListener final : public OHOS::UIPicker::SelectedListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TextPickerListener);
    TextPickerListener() : pTextArray_(nullptr), textCallback_(UNDEFINED) {}
    ~TextPickerListener()
    {
        jerry_release_value(textCallback_);
    }

    void OnPickerStoped(UIPicker& picker) override;

    void SetTextCallback(jerry_value_t callback)
    {
        jerry_release_value(textCallback_);
        textCallback_ = jerry_acquire_value(callback);
    }

    void SetTextRange(char** range)
    {
        pTextArray_ = range;
    }

private:
    char** pTextArray_;
    jerry_value_t textCallback_;
};

/**
 * @brief listener class for time picker onchange event.
 */
class TimePickerListener final : public OHOS::UITimePicker::SelectedListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(TimePickerListener);
    TimePickerListener() : timeCallback_(UNDEFINED) {}
    ~TimePickerListener()
    {
        jerry_release_value(timeCallback_);
    }

    void OnTimePickerStoped(UITimePicker& picker) override;

    void SetTimeCallback(jerry_value_t callback)
    {
        jerry_release_value(timeCallback_);
        timeCallback_ = jerry_acquire_value(callback);
    }

private:
    jerry_value_t timeCallback_;
};

#ifdef FEATURE_COMPONENT_DATE_PICKER
/**
 * @brief listener class for date picker onchange event.
 */
class DatePickerListener final : public UIDatePicker::SelectedListener {
public:
    ACE_DISALLOW_COPY_AND_MOVE(DatePickerListener);
    DatePickerListener() : dateCallback_(UNDEFINED) {}
    ~DatePickerListener()
    {
        jerry_release_value(dateCallback_);
    }

    void OnDatePickerStoped(UIDatePicker& picker) override;

    void SetDateCallback(jerry_value_t callback)
    {
        jerry_release_value(dateCallback_);
        dateCallback_ = jerry_acquire_value(callback);
    }

private:
    jerry_value_t dateCallback_;
};
#endif // FEATURE_COMPONENT_DATE_PICKER

/**
 * @brief class for picker-view component adaptation.
 */
class PickerViewComponent final : public Component {
public:
    ACE_DISALLOW_COPY_AND_MOVE(PickerViewComponent);
    PickerViewComponent() = delete;
    PickerViewComponent(jerry_value_t options, jerry_value_t children, AppStyleManager* styleManager);
    ~PickerViewComponent() override {}

protected:
    bool CreateNativeViews() override;
    void ReleaseNativeViews() override;
    UIView *GetComponentRootView() const override;
    bool SetPrivateAttribute(uint16_t attrKeyId, jerry_value_t attrValue) override;
    bool ApplyPrivateStyle(const AppStyleItem* styleItem) override;
    bool RegisterPrivateEventListener(uint16_t eventTypeId, jerry_value_t funcValue) override;
    void PostRender() override;
    void PostUpdate(uint16_t attrKeyId, bool updateResult) override;

    /**
     * @enum    PickerType
     *
     * @brief   Values that represent different types of picker-view
     */
    enum class PickerType {
        UNKNOWN,
        TEXT,
        TIME,
#ifdef FEATURE_COMPONENT_DATE_PICKER
        DATE,
#endif // FEATURE_COMPONENT_DATE_PICKER
        TYPE_MAX
    };

private:
    char* GetStringAttrByName(const char * const name, uint16_t& length) const;
    PickerType GetPickerType() const;
    bool CreateTextPicker();
    bool CreateTimePicker();
#ifdef FEATURE_COMPONENT_DATE_PICKER
    bool CreateDatePicker();
#endif // FEATURE_COMPONENT_DATE_PICKER
    bool SetPickerSelected(jerry_value_t selectedValue);
    void SetPickerListener(jerry_value_t funcValue) const;
    bool SetTextPickerRange(jerry_value_t rangeValue);
    void ReleaseTextRange();
    void UpdatePickerAttrs() const;
    void UpdatePickerStyles() const;

    jerry_value_t options_;
    PickerType pickerType_;
    UIView* pickerView_;
    ColorType color_;
    uint8_t fontSize_;
    char* fontFamily_;
    ColorType selectedColor_;
    uint8_t selectedFontSize_;
    char* selectedFontFamily_;

    // text picker-view attributes
    uint16_t textSelected_;
    char** pTextArray_;
    uint16_t textArraySize_;
    TextPickerListener* textPickerListener_;

#ifdef FEATURE_COMPONENT_DATE_PICKER
    // date picker-view attributes
    char* dateSelected_;
    char* dateStart_;
    char* dateEnd_;
    DatePickerListener* datePickerListener_;
#endif // FEATURE_COMPONENT_DATE_PICKER

    // time picker-view listener
    TimePickerListener* timePickerListener_;
    char* timeSelected_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_PICKER_VIEW_COMPONENT_H
