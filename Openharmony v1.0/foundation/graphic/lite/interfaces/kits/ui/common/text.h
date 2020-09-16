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
 * @file text.h
 *
 * @brief Declares the <b>Text</b> class that provides functions to set basic text attributes, such as the text
 *        direction and alignment mode.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_TEXT_H
#define GRAPHIC_LITE_TEXT_H

#include "graphic_types.h"
#include "geometry2d.h"
#include "style.h"

namespace OHOS {
/**
 * @brief Enumerates text alignment modes.
 */
enum UITextLanguageAlignment : uint8_t {
    /** Left-aligned */
    TEXT_ALIGNMENT_LEFT = 0,
    /** Right-aligned */
    TEXT_ALIGNMENT_RIGHT,
    /** Centered */
    TEXT_ALIGNMENT_CENTER,
    /** Top-aligned */
    TEXT_ALIGNMENT_TOP,
    /** Bottom-aligned */
    TEXT_ALIGNMENT_BOTTOM,
};

/**
 * @brief Enumerates text directions.
 */
enum UITextLanguageDirect : uint8_t {
    /** Left-to-right */
    TEXT_DIRECT_LTR = 0,
    /** Right-to-left */
    TEXT_DIRECT_RTL,
};

struct LabelRotation {
    const Rect& realMask;
    const Rect& coords;
    Point pivot;
    uint16_t degree;
};

/**
 * @brief Represents the base class of <b>Text</b>, providing the text attribute setting and text drawing
 *        capabilities for components that require font display.
 *
 * @since 1.0
 * @version 1.0
 */
class Text : HeapBase {
public:
    /** Invalid value for the ellipsis position */
    static constexpr uint16_t TEXT_ELLIPSIS_END_INV = 0xFFFF;

    /**
     * @brief A constructor used to create a <b>Text</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    Text();

    /**
     * @brief A destructor used to delete the <b>Text</b> instance.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual ~Text();

    /**
     * @brief Sets the content for this text.
     *
     * @param text Indicates the pointer to the text content.
     * @since 1.0
     * @version 1.0
     */
    void SetText(const char* text);

    /**
     * @brief Obtains the content of this text.
     *
     * @return Returns the text content.
     * @since 1.0
     * @version 1.0
     */
    const char* GetText() const
    {
        return text_;
    }

    /**
     * @brief Sets the font name and size.
     *
     * @param name Indicates the pointer to the font name.
     * @param size Indicates the font size to set.
     * @since 1.0
     * @version 1.0
     */
    void SetFont(const char* name, uint8_t size);

    static void SetFont(const char* name, uint8_t size, char*& destName, uint8_t& destSize);

    /**
     * @brief Sets the font ID.
     *
     * @param fontId Indicates the font ID to set.
     * @since 1.0
     * @version 1.0
     */
    void SetFontId(uint8_t fontId);

    /**
     * @brief Obtains the font ID.
     *
     * @return Returns the front ID.
     * @since 1.0
     * @version 1.0
     */
    uint8_t GetFontId() const
    {
        return fontId_;
    }

    /**
     * @brief Sets the direction for this text.
     *
     * @param direct Indicates the text direction, as defined in {@link UITextLanguageDirect}.
     * @since 1.0
     * @version 1.0
     */
    void SetDirect(UITextLanguageDirect direct)
    {
        direct_ = direct;
    }

    /**
     * @brief Obtains the direction of this text.
     *
     * @return Returns the text direction, as defined in {@link UITextLanguageDirect}.
     * @since 1.0
     * @version 1.0
     */
    UITextLanguageDirect GetDirect() const
    {
        return static_cast<UITextLanguageDirect>(direct_);
    }

    /**
     * @brief Sets the alignment mode for this text.
     *
     * @param horizontalAlign Indicates the horizontal alignment mode to set,
     *                        which can be {@link TEXT_ALIGNMENT_LEFT},
     *                        {@link TEXT_ALIGNMENT_CENTER}, or {@link TEXT_ALIGNMENT_RIGHT}.
     * @param verticalAlign Indicates the vertical alignment mode to set, which can be
     *                      {@link TEXT_ALIGNMENT_TOP} (default mode), {@link TEXT_ALIGNMENT_CENTER},
     *                      or {@link TEXT_ALIGNMENT_BOTTOM}.
     * @since 1.0
     * @version 1.0
     */
    void SetAlign(UITextLanguageAlignment horizontalAlign,
        UITextLanguageAlignment verticalAlign = TEXT_ALIGNMENT_TOP)
    {
        if ((horizontalAlign_ != horizontalAlign) || (verticalAlign_ != verticalAlign)) {
            needRefresh_ = true;
            horizontalAlign_ = horizontalAlign;
            verticalAlign_ = verticalAlign;
        }
    }

    /**
     * @brief Obtains the horizontal alignment mode.
     *
     * @return Returns the horizontal alignment mode.
     * @since 1.0
     * @version 1.0
     */
    UITextLanguageAlignment GetHorAlign() const
    {
        return static_cast<UITextLanguageAlignment>(horizontalAlign_);
    }

    /**
     * @brief Obtains the vertical alignment mode.
     *
     * @return Returns the vertical alignment mode.
     * @since 1.0
     * @version 1.0
     */
    UITextLanguageAlignment GetVerAlign() const
    {
        return static_cast<UITextLanguageAlignment>(verticalAlign_);
    }

    /**
     * @brief Sets the clockwise rotation angle for this text.
     *
     * @param angle Indicates the rotation angle to set. The value can be <b>DEGREE_0</b>,
     *              <b>DEGREE_90</b>, <b>DEGREE_180</b>, or <b>DEGREE_270</b>, as defined in {@link LabelRotateDegree}.
     * @since 1.0
     * @version 1.0
     */
    void SetTextRotation(LabelRotateDegree angle)
    {
        rotateAngle_ = angle;
    }

    /**
     * @brief Obtains the clockwise rotation degree of this text.
     *
     * @return Returns the rotation degree, as defined in {@link LabelRotateDegree}.
     * @since 1.0
     * @version 1.0
     */
    LabelRotateDegree GetTextRotation() const
    {
        return static_cast<LabelRotateDegree>(rotateAngle_);
    }

    /**
     * @brief Obtains the number of text rotation degrees.
     *
     * @return Returns the number of text rotation degrees.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetTextRotateDegree() const
    {
        return rotateAngle_ * QUARTER_IN_DEGREE;
    }

    /**
     * @brief Obtains the size of this text.
     *
     * @return Returns the text size.
     * @since 1.0
     * @version 1.0
     */
    Point GetTextSize() const
    {
        return textSize_;
    }

    void ReMeasureTextSize(const Rect& textRect, const Style& style);

    void OnDraw(const Rect& invalidatedArea, const Rect& viewOrigRect, const Rect& textRect, int16_t offsetX,
        const Style& style, uint16_t ellipsisIndex);

    /**
     * @brief Sets whether to adapt the component width to this text.
     *
     * @param expand Specifies whether to adapt the component width to this text. The value <b>true</b> indicates
     *               that the component width will adapt to this text, and <b>false</b> indicates not.
     * @since 1.0
     * @version 1.0
     */
    void SetExpandWidth(bool expand)
    {
        expandWidth_ = expand;
    }

    /**
     * @brief Checks whether the component width adapts to this text.
     *
     * @return Returns <b>true</b> if the component width adapts to this text; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsExpandWidth() const
    {
        return expandWidth_;
    }

    /**
     * @brief Sets whether to adapt the component height to this text.
     *
     * @param expand Specifies whether to adapt the component height to this text. The value <b>true</b> indicates
     *               that the component height will adapt to this text, and <b>false</b> indicates not.
     * @since 1.0
     * @version 1.0
     */
    void SetExpandHeight(bool expand)
    {
        expandHeight_ = expand;
    }

    /**
     * @brief Checks whether the component height adapts to this text.
     *
     * @return Returns <b>true</b> if the component height adapts to this text; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsExpandHeight() const
    {
        return expandHeight_;
    }

    bool IsNeedRefresh() const
    {
        return needRefresh_;
    }

    /**
     * @brief Obtains the index of the character from where text will be replaced by ellipses based on
     *        the text rectangle and style.
     *
     * @param textRect Indicates the text rectangle.
     * @param style Indicates the text style.
     * @since 1.0
     * @version 1.0
     */
    uint16_t GetEllipsisIndex(const Rect& textRect, const Style& style);

private:
    static constexpr int16_t TEXT_ELLIPSIS_DOT_NUM = 3;
    struct TextLine {
        uint16_t lineBytes;
        uint16_t lineBegin;
    };

    /** Maximum number of lines */
    static constexpr uint16_t MAX_LINE_COUNT = 50;
    static TextLine textLine_[MAX_LINE_COUNT];

    void Draw(const Rect& mask, const LabelRotation& rotate, const Style& style, int16_t offsetX,
        uint16_t ellipsisIndex);
    int16_t TextPositionY(const Rect& textRect);
    int16_t LineStartPos(const Rect& textRect, uint16_t lineWidth);
    uint16_t GetLine(const char* text, int16_t width, uint8_t letterSpace);
    char* GetEllipsisText(char* text, uint16_t ellipsisIndex);
    uint16_t GetLetterIndexByPosition(const Rect& textRect, const Style& style, const Point& pos);

    char* text_;
    uint8_t fontId_;
    uint8_t fontSize_; // Only the vector font library has a valid value.
    Point textSize_;
    bool needRefresh_ : 1;
    bool expandWidth_ : 1;
    bool expandHeight_ : 1;
    uint8_t direct_ : 1; // UITextLanguageDirect
    uint8_t rotateAngle_ : 4; // LabelRotateDegree
    uint8_t horizontalAlign_ : 4; // UITextLanguageAlignment
    uint8_t verticalAlign_ : 4; // UITextLanguageAlignment
};
} // namespace OHOS
#endif // GRAPHIC_LITE_TEXT_H