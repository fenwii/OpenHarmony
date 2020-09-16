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
 * @file ui_picker.h
 *
 * @brief Defines the attributes and functions of the <b>UIPicker</b> class.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef UI_PICKER_H
#define UI_PICKER_H

#include "components/text_adapter.h"
#include "components/ui_list.h"

namespace OHOS {
/**
 * @brief Defines a picker. Multiple texts or numbers can be put into a sliding list for selection.
 *        The selected text or numbers are highlighted.
 *
 * @since 1.0
 * @version 1.0
 */
class UIPicker : public UIViewGroup {
public:
    /**
     * @brief A constructor used to create a <b>UIPicker</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    UIPicker();

    /**
     * @brief A destructor used to delete the <b>UIPicker</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~UIPicker();

    /**
     * @brief Obtains the view type.
     *
     * @return Returns the view type. For details, see {@link UIViewType}.
     * @since 1.0
     * @version 1.0
     */
    UIViewType GetViewType() const override
    {
        return UI_PICKER;
    }

    bool OnPreDraw(const Rect& invalidatedArea) override
    {
        return false;
    }

    /**
     * @brief Sets dynamic text data in the picker by using a string array.
     *
     * @param value[] Indicates the array of text data.
     * @param count   Indicates the array size.
     * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool SetValues(const char* value[], uint16_t count);

    /**
     * @brief Sets the numeric data in the picker by using a given numeric range.
     *
     * All integers in the range are automatically generated based on the start value and end value and placed in
     * the picker in sequence. The start value must be smaller or equal to the end value.
     *
     * @param start Indicates the start integer.
     * @param end   Indicates the end integer.
     * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool SetValues(int16_t start, int16_t end);

    /**
     * @brief Clears all values in the picker.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void ClearValues();

    /**
     * @brief Sets the font IDs of dynamic text, which is the string array set through {@link SetValues}.
     *
     * @param backgroundFontId Indicates the font ID of the background text.
     * @param highlightFontId  Indicates the font ID of the highlighted text.
     * @since 1.0
     * @version 1.0
     */
    void SetFontId(uint8_t backgroundFontId, uint8_t highlightFontId);

    void SetBackgroundFont(const char* name, uint8_t size);

    void SetHighlightFont(const char* name, uint8_t size);

    /**
     * @brief Obtains the font ID of the background text.
     *
     * @return Returns the font ID.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetBackgroundFontId() const
    {
        return backgroundFontId_;
    }

    /**
     * @brief Obtains the font ID of the highlighted text.
     *
     * @return Returns the font ID.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetHighlightFontId() const
    {
        return highlightFontId_;
    }

    /**
     * @brief Sets the text color.
     *
     * @param backgroundColor Indicates the color of the background text.
     * @param highlightColor  Indicates the color of the highlighted text.
     * @since 1.0
     * @version 1.0
     */
    void SetTextColor(ColorType backgroundColor, ColorType highlightColor);

    /**
     * @brief Obtains the color of the background text.
     *
     * @return Returns the color.
     * @since 1.0
     * @version 1.0
     */
    ColorType GetBackgroundTextColor() const
    {
        return backgroundColor_;
    }

    /**
     * @brief Obtains the color of the highlighted text.
     *
     * @return Returns the color of the highlighted text.
     * @since 1.0
     * @version 1.0
     */
    ColorType GetHighlightTextColor() const
    {
        return highlightColor_;
    }

    /**
     * @brief Sets the index of the item currently selected in the picker.
     *
     * @param index Indicates the index to set.
     * @return Returns <b>true</b> if the setting is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool SetSelected(uint16_t index);

    /**
     * @brief Obtains the index of the item currently selected in the picker.
     *
     * @return Returns the index.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetSelected() const;

    /**
     * @brief Sets the height of each item in the picker.
     *
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    void SetItemHeight(int16_t height);

    /**
     * @brief Sets the width for this component.
     *
     * @param width Indicates the width to set.
     * @since 1.0
     * @version 1.0
     */
    void SetWidth(int16_t width) override;

    /**
     * @brief Sets the height for this component.
     *
     * @param height Indicates the height to set.
     * @since 1.0
     * @version 1.0
     */
    void SetHeight(int16_t height) override;

    /**
     * @brief Sets whether a picker can slide cyclically.
     *
     * @param state Specifies whether the picker can slide cyclically. Value <b>true</b> indicates that the picker
     *              can slide cyclically, and value <b>false</b> indicates that the picker cannot
     *              slide cyclically. The default value is <b>false</b>.
     * @since 1.0
     * @version 1.0
     */
    void SetLoopState(bool state);

    /**
     * @brief Defines the listener used by a picker. This listener is triggered when an item
     *        is selected after sliding stops.
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
        virtual ~SelectedListener() {}

        /**
         * @brief Called when an item is selected after sliding stops. This function is implemented by applications.
         *
         * @param picker Indicates the picker instance.
         * @since 1.0
         * @version 1.0
         */
        virtual void OnPickerStoped(UIPicker& picker) {}
    };

    /**
     * @brief Registers a listener for a selected event.
     *
     * @param pickerListener Indicates the listener for a selected event in the picker. For details,
     *                       see {@link SelectedListener}.
     *
     * @since 1.0
     * @version 1.0
     */
    void RegisterSelectedListener(SelectedListener* pickerListener)
    {
        pickerListener_ = pickerListener;
    }

    /**
     * @brief Sets the text direction.
     *
     * @param direct Indicates the text direction to set. For details, see {@link UITextLanguageDirect}.
     *
     * @since 1.0
     * @version 1.0
     */
    void SetDirect(UITextLanguageDirect direct);

    /**
     * @brief Sets the text formatter.
     *
     * @param formatter Indicates the pointer to the text formatter. For details, see {@link TextFormatter}.
     *
     * @since 1.0
     * @version 1.0
     */
    void SetTextFormatter(TextFormatter* formatter);

protected:
    bool RefreshSelected(uint16_t index);
    void RefreshList();
    virtual void ClearList();
    virtual void Refresh();

    bool isWidthSet_ : 1;
    bool isHeightSet_ : 1;
    TextAdapter textAdapter_;
    uint16_t maxCount_;
    uint16_t backgroundFontId_;
    uint16_t highlightFontId_;
    uint16_t setSelectedIndex_;
    uint8_t backgroundFontSize_;
    uint8_t highlightFontSize_;
    char* backgroundFontName_;
    char* highlightFontName_;

private:
    friend class PickerListScrollListener;
    bool RefreshValues(const char* value[], uint16_t count);
    bool RefreshValues(int16_t start, int16_t end);
    uint16_t itemsWidth_;
    uint16_t itemsHeight_;
    const char** rangeValue_;
    uint16_t rangeValueCount_;
    int16_t startValue_;
    int16_t endValue_;
    ColorType backgroundColor_;
    ColorType highlightColor_;
    List<const char*> dataList_;
    bool isSetAdaptered_ : 1;
    UIList list_;
    void* listListener_;
    SelectedListener* pickerListener_;
    UITextLanguageDirect direct_;
};
}
#endif
