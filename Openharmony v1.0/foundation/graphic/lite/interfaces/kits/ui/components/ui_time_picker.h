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

/**
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ui_time_picker.h
 *
 * @brief Defines the attributes and functions of the <b>UITimePicker</b> class.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_UI_TIME_PICKER_H
#define GRAPHIC_LITE_UI_TIME_PICKER_H

#include "components/ui_picker.h"

namespace OHOS {
/**
 * @brief Defines the time picker. The time is in the format of "hour:minute" or "hour:minute:second".
 *        The selected time is highlighted.
 *
 * @since 1.0
 * @version 1.0
 */
class UITimePicker : public UIViewGroup {
public:
    /**
     * @brief A constructor used to create a <b>UITimePicker</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UITimePicker();

    /**
     * @brief A destructor used to delete the <b>UITimePicker</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UITimePicker();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type. For details, see {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_TIME_PICKER;
    }

    /**
     * @brief Sets the time currently selected in the time picker.
     *
     * @param value Indicates the pointer to the selected time, which is in the format of "hour:minute:second",
     *              for example, 10:12:50. The second is optional and depends on the setting of {@link EnableSecond}.
     *              The time must be a valid value. For example, the hour value must range from 0 to 23.
     * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool SetSelected(const char* value);

    /**
     * @brief Obtains the time currently selected in the time picker.
     *
     * @return Returns a string representing the selected time. The time is in the format of "hour:minute:second",
     *         for example, 10:12:50. The second is optional and depends on the setting of {@link EnableSecond}.
     * @since 1.0
     * @version 1.0
     */
    const char* GetSelectValue()
    {
        return selectedValue_;
    }

    /**
     * @brief Obtains the hour currently selected in the time picker.
     *
     * @return Returns a string representing the selected hour, for example, 10.
     * @since 1.0
     * @version 1.0
     */
    const char* GetSelectHour() const
    {
        return selectedHour_;
    }

    /**
     * @brief Obtains the minute currently selected in the time picker.
     *
     * @return Returns a string representing the selected minute, for example, 12.
     * @since 1.0
     * @version 1.0
     */
    const char* GetSelectMinute() const
    {
        return selectedMinute_;
    }

    /**
     * @brief Obtains the second currently selected in the time picker.
     *
     * @return Returns a string representing the selected second, for example, 50.
     * @since 1.0
     * @version 1.0
     */
    const char* GetSelectSecond() const
    {
        return selectedSecond_;
    }

    /**
     * @brief Sets the height of each item in the time picker.
     *
     * @param height Indicates the height of each item.
     * @since 1.0
     * @version 1.0
     */
    void SetItemHeight(int16_t height);

    /**
     * @brief Sets whether to enable seconds in the time picker.
     *
     * @param state Specifies whether to enable seconds in the time picker. Value <b>true</b> means to enable seconds,
     *              and value <b>false</b> means to disable seconds. The default value is <b>false</b>.
     * @since 1.0
     * @version 1.0
     */
    void EnableSecond(bool state);

    /**
     * @brief Sets the text format in the time picker, including the font ID and color.
     *
     * @param backgroundFontId Indicates the font ID of the background text.
     * @param highlightFontId  Indicates the font ID of the highlighted text.
     * @param backgroundColor  Indicates the color of the background text.
     * @param highlightColor   Indicates the color of the highlighted text.
     * @since 1.0
     * @version 1.0
     */
    void SetTextStyle(uint8_t backgroundFontId, uint8_t highlightFontId,
                      ColorType backgroundColor, ColorType highlightColor);

    void SetTextColor(ColorType backgroundColor, ColorType highlightColor);

    void SetBackgroundFont(const char* name, uint8_t size);

    void SetHighlightFont(const char* name, uint8_t size);

    /**
     * @brief Sets the width for the time picker.
     *
     * @param width Indicates the width to set.
     * @since 1.0
     * @version 1.0
     */
    void SetWidth(int16_t width) override;

    /**
     * @brief Sets the height for the time picker.
     *
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    void SetHeight(int16_t height) override;

    /**
     * @brief Defines the listener used by the time picker. This listener is triggered when an item is selected
     *        after sliding stops.
     *
     * @since 1.0
     * @version 1.0
     */
    class SelectedListener : public HeapBase {
    public:
        /**
         * @brief A constructor used to create a <b>SelectedListener</b> instance.
         *
         * @since 1.0
         * @version 1.0
         */
        SelectedListener() {}

        /**
         * @brief A destructor used to delete the <b>SelectedListener</b> instance.
         *
         * @since 1.0
         * @version 1.0
         */
        ~SelectedListener() {}

        /**
         * @brief Called when an item is selected after sliding stops. This function is implemented by applications.
         *
         * @param picker Indicates the time picker instance.
         * @since 1.0
         * @version 1.0
         */
        virtual void OnTimePickerStoped(UITimePicker& picker) {}
    };

    /**
     * @brief Registers a listener for a selected event.
     *
     * @param timePickerListener Indicates the listener to register. For details, see {@link SelectedListener}.
     *
     * @since 1.0
     * @version 1.0
     */
    void RegisterSelectedListener(SelectedListener* timePickerListener)
    {
        timePickerListener_ = timePickerListener;
    }

private:
    class UIPickerListener : public UIPicker::SelectedListener {
    public:
        UIPickerListener(UITimePicker* timePicker)
        {
            timePicker_ = timePicker;
        }

        ~UIPickerListener() {}

        virtual void OnPickerStoped(UIPicker& picker) override
        {
            if (timePicker_ != nullptr) {
                timePicker_->TimeSelectedCallback();
            }
        }

    private:
        UITimePicker* timePicker_;
    };
    static constexpr uint8_t TIME_START = 0;
    static constexpr uint8_t HOUR_END = 23;
    static constexpr uint8_t MIN_END = 59;
    static constexpr uint8_t SEC_END = 59;
    static constexpr uint8_t BUF_SIZE = 3;
    static constexpr uint8_t SELECTED_VALUE_SIZE = 9;
    static constexpr uint8_t SEC_VISIBLE_COUNT = 3;
    static constexpr uint8_t SEC_INVISIBLE_COUNT = 2;
    void TimeSelectedCallback();
    void InitTimePicker();
    void DeInitTimePicker();
    void RefreshTimePicker();
    bool RefreshSelected(const char* value);
    void InitPicker(UIPicker*& picker, int16_t start, int16_t end);
    void DeInitPicker(UIPicker*& picker);
    void GetValueByIndex(char* value, uint8_t len, uint16_t index, int16_t start, int16_t end);
    UIPicker* hourPicker_;
    UIPicker* minutePicker_;
    UIPicker* secondPicker_;
    char selectedValue_[SELECTED_VALUE_SIZE];
    char selectedHour_[BUF_SIZE];
    char selectedMinute_[BUF_SIZE];
    char selectedSecond_[BUF_SIZE];
    bool secVisible_;
    const char* setSelectedTime_;
    uint16_t pickerWidth_;
    uint16_t itemsHeight_;
    int16_t xPos_;
    uint8_t highlightFontId_;
    uint8_t backgroundFontId_;
    uint8_t backgroundFontSize_;
    uint8_t highlightFontSize_;
    char* backgroundFontName_;
    char* highlightFontName_;
    ColorType highlightColor_;
    ColorType backgroundColor_;
    UIPickerListener pickerListener_;
    SelectedListener* timePickerListener_;
};
}
#endif // GRAPHIC_LITE_UI_TIME_PICKER_H
