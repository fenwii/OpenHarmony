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
 * @file text_adapter.h
 *
 * @brief Defines a text adapter that is used to construct UILabel instances.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_TEXT_ADAPTER_H
#define GRAPHIC_LITE_TEXT_ADAPTER_H

#include "components/abstract_adapter.h"
#include "components/ui_label.h"

namespace OHOS {
/**
 * @brief Defines a text formatter. You can inherit this class and implement the <b>Format()</b> function.
 *
 * @since 1.0
 * @version 1.0
 */
class TextFormatter : public HeapBase {
public:
    /**
     * @brief Converts the input integer into a character string for output.
     *
     * @param value Indicates the input integer.
     * @param outText Indicates the pointer to the converted string.
     * @param textLen Indicates the length of the string.
     * @since 1.0
     * @version 1.0
     */
    virtual bool Format(int16_t value, char* outText, uint16_t textLen);
};

/**
 * @brief Defines a text adapter, which implements UILabel instance construction and supports text data and continuous
 *        integer data.
 *
 * @since 1.0
 * @version 1.0
 */
class TextAdapter : public AbstractAdapter {
public:
    /**
     * @brief A constructor used to create a <b>UILabel</b> instance.
     * @since 1.0
     * @version 1.0
     */
    TextAdapter();

    /**
     * @brief A destructor used to delete the <b>UILabel</b> instance.
     * @since 1.0
     * @version 1.0
     */
    virtual ~TextAdapter();

    /**
     * @brief Obtains a <b>UILabel</b> instance to convert adapter data into another <b>UILabel</b> instance.
     *
     * @param inView Indicates the pointer to the reusable instance. If this parameter is not <b>NULL</b>, a reusable
     *        <b>UILabel</b> instance is available. In this case, this function does not need to create a new
     *        <b>UILabel</b> instance, just resusing the instance specified by <b>inView</b> to update the <b>inView</b>
     *        data. If this parameter is <b>NULL</b>, there is no resuable <b>UIView</b> instance. In this case, this
     *        function needs to create a new <b>UILabel</b> instance.
     *
     * @param index Indicates the adapter data index.
     *
     * @return Returns the address of the <b>UILabel</b> instance constructed by the adapter.
     * @since 1.0
     * @version 1.0
     */
    UIView* GetView(UIView* inView, int16_t index) override;

    /**
     * @brief Sets the UILabel adapter data, which is a string linked list.
     *
     * @param data Indicates the string linked list data.
     * @since 1.0
     * @version 1.0
     */
    void SetData(List<const char*>* data);

    /**
     * @brief Sets continuously increasing data. For example, if you need to set data <b>0</b>, <b>1</b>, <b>2</b>,
     *        <b>3</b>, <b>4</b>, use this function to set <b>start</b> to 0 and <b>end</b> to 4.
     *
     * @param start Indicates the start value of the integer data.
     * @param end Indicates the end value of the integer data.
     * @since 1.0
     * @version 1.0
     */
    void SetData(int16_t start, int16_t end);

    /**
     * @brief Sets font ID.
     *
     * @param fontId Indicates the font ID. For details, see {@link UITextLanguageFontId}.
     * @since 1.0
     * @version 1.0
     */
    void SetFontId(uint8_t fontId)
    {
        fontId_ = fontId;
        if (fontName_ != nullptr) {
            UIFree(fontName_);
            fontName_ = nullptr;
        }
    }

    /**
     * @brief Obtains font ID.
     *
     * @return Returns the font ID. For details, see {@link UITextLanguageFontId}.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetFontId() const
    {
        return fontId_;
    }

    /**
     * @brief Sets the font.
     *
     * @param name Indicates the pointer to the font name.
     * @param size Indicates the font size to set.
     * @since 1.0
     * @version 1.0
     */
    void SetFont(const char* name, uint8_t size);

    /**
     * @brief Obtains the UILabel adapter style.
     *
     * @return Returns the UILabel adapter style.
     * @since 1.0
     * @version 1.0
     */
    Style& GetStyle()
    {
        return style_;
    }

    /**
     * @brief Obtains the <b>data</b> size of the UILabel adapter.
     *
     * @return Returns the <b>data</b> size of the UILabel adapter.
     * @since 1.0
     * @version 1.0
     */
    virtual uint16_t GetCount() override;

    /**
     * @brief Sets the width of UILabel constructed by the adapter.
     *
     * @return Returns the width of UILabel.
     * @since 1.0
     * @version 1.0
     */
    void SetWidth(int16_t width)
    {
        width_ = width;
    }

    /**
     * @brief Sets the direction of the UILabel constructed by the adapter.
     *
     * @param direct Indicates the direction of the UILabel constructed by the adapter.
     * @since 1.0
     * @version 1.0
     */
    void SetDirect(UITextLanguageDirect direct)
    {
        direct_ = direct;
    }

    /**
     * @brief Sets the height of the UILabel constructed by the adapter.
     *
     * @return Returns the height of the UILabel constructed by the adapter.
     * @since 1.0
     * @version 1.0
     */
    void SetHeight(int16_t height)
    {
        height_ = height;
    }

    /**
     * @brief Sets the <b>LineBreakMode</b> attribute of UILabel constructed by the adapter. For details about the
     *        values of <b>LineBreakMode</b>, see {@link LINE_BREAK_ADAPT}, {@link LINE_BREAK_WRAP},
     *        {@link LINE_BREAK_ELLIPSIS}, and {@link LINE_BREAK_MARQUEE}.
     *
     * @param lineBreakMode Indicates the <b>LineBreakMode</b> of UILabel.
     * @since 1.0
     * @version 1.0
     */
    void SetLineBreakMode(const uint8_t lineBreakMode)
    {
        lineBreakMode_ = lineBreakMode;
    }

    /**
     * @brief Sets the callback function to be invoked upon a click event.
     *
     * @param clickListener Indicates the pointer to the callback function.
     * @since 1.0
     * @version 1.0
     */
    void SetOnClickListener(UIView::OnClickListener* clickListener)
    {
        clickListener_ = clickListener;
    }

    /**
     * @brief Sets the text formatter.
     *
     * @param formatter Indicates the pointer to the text formatter. For details, see {@link TextFormatter}.
     *
     * @since 1.0
     * @version 1.0
     */
    void SetTextFormatter(TextFormatter* formatter)
    {
        formatter_ = formatter;
    }

private:
    static constexpr uint8_t DYNAMIC_TEXT_MODE = 0;
    static constexpr uint8_t CONTINUOUS_INTEGER_MODE = 3;
    static constexpr uint8_t BUF_LEN = 7;
    UILabel* GetDynamicText(UIView* inView, int16_t index);
    UILabel* GetIntegerText(UIView* inView, int16_t index);
    void ClearDynamicText();
    uint8_t fontId_;
    char* fontName_;
    uint8_t fontSize_;
    int16_t width_;
    int16_t height_;
    UITextLanguageDirect direct_;
    uint8_t lineBreakMode_;
    uint8_t dataMode_;
    int16_t integerTextStart_;
    int16_t integerTextEnd_;
    Style style_;
    List<const char*> dynamicText_;
    UIView::OnClickListener* clickListener_;
    TextFormatter* formatter_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_TEXT_ADAPTER_H
