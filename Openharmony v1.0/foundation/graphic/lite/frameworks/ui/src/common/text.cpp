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

#include "common/text.h"
#include "common/typed_text.h"
#include "draw/draw_label.h"
#include "font/ui_font.h"
#include "graphic_log.h"
#include "securec.h"

namespace OHOS {
Text::TextLine Text::textLine_[MAX_LINE_COUNT] = { {0} };

Text::Text()
    : text_(nullptr),
      fontId_(0),
      fontSize_(0),
      textSize_({ 0, 0 }),
      needRefresh_(false),
      expandWidth_(false),
      expandHeight_(false),
      direct_(TEXT_DIRECT_LTR),
      rotateAngle_(LabelRotateDegree::DEGREE_0),
      horizontalAlign_(TEXT_ALIGNMENT_LEFT),
      verticalAlign_(TEXT_ALIGNMENT_TOP) {}

Text::~Text()
{
    if (text_ != nullptr) {
        UIFree(text_);
        text_ = nullptr;
    }
}

void Text::SetText(const char* text)
{
    if (text == nullptr) {
        return;
    }
    if (text_ != nullptr) {
        if (strcmp(text, text_) == 0) {
            return;
        }
        UIFree(text_);
        text_ = nullptr;
    }
    uint32_t textLen = static_cast<uint32_t>(strlen(text));
    if (textLen > MAX_TEXT_LENGTH) {
        return;
    }
    if (textLen != 0) {
        text_ = static_cast<char*>(UIMalloc(++textLen));
        if (text_ == nullptr) {
            return;
        }
        if (memcpy_s(text_, textLen, text, textLen) != EOK) {
            UIFree(text_);
            text_ = nullptr;
            return;
        }
    }
    needRefresh_ = true;
}

void Text::SetFont(const char* name, uint8_t size)
{
    if (name == nullptr) {
        return;
    }
    if (UIFont::GetInstance()->IsVectorFont()) {
        fontId_ = UIFont::GetInstance()->GetFontId(name);
        fontSize_ = size;
    } else {
        uint8_t fontId = UIFont::GetInstance()->GetFontId(name, size);
        SetFontId(fontId);
    }
}

void Text::SetFont(const char* name, uint8_t size, char*& destName, uint8_t& destSize)
{
    if (name == nullptr) {
        return;
    }
    if (destName != nullptr) {
        if (strcmp(destName, name) == 0) {
            destSize = size;
            return;
        }
        UIFree(destName);
        destName = nullptr;
    }
    uint32_t nameLen = static_cast<uint32_t>(strlen(name));
    if (nameLen > MAX_TEXT_LENGTH) {
        return;
    }
    if (nameLen != 0) {
        /* one more to store '\0' */
        destName = static_cast<char*>(UIMalloc(++nameLen));
        if (destName == nullptr) {
            return;
        }
        if (memcpy_s(destName, nameLen, name, nameLen) != EOK) {
            UIFree(destName);
            destName = nullptr;
            return;
        }
        destSize = size;
    }
}

void Text::SetFontId(uint8_t fontId)
{
    if (fontId >= GetTotalFontId() || fontId_ == fontId) {
        GRAPHIC_LOGE("Text::SetFontId invalid fontId(%d)", fontId);
        return;
    }
    if (!UIFont::GetInstance()->IsVectorFont()) {
        fontId_ = fontId;
        needRefresh_ = true;
    }
}

void Text::ReMeasureTextSize(const Rect& textRect, const Style& style)
{
    UIFont::GetInstance()->SetCurrentFontId(fontId_, fontSize_);
    int16_t maxWidth = (expandWidth_ ? COORD_MAX : textRect.GetWidth());
    textSize_ = TypedText::GetTextSize(text_, style.letterSpace_, style.lineSpace_, maxWidth);
}

void Text::OnDraw(const Rect& invalidatedArea, const Rect& viewOrigRect, const Rect& textRect, int16_t offsetX,
    const Style& style, uint16_t ellipsisIndex)
{
    if (text_ == nullptr) {
        return;
    }
    UIFont::GetInstance()->SetCurrentFontId(fontId_, fontSize_);
    Rect mask;
    Rect coords;
    uint16_t angle = 0;
    if (rotateAngle_ != LabelRotateDegree::DEGREE_0) {
        coords = viewOrigRect;
        TransformMap reverseMap(invalidatedArea);
        int16_t pivotX = coords.GetLeft() - invalidatedArea.GetLeft();
        int16_t pivotY = coords.GetTop() - invalidatedArea.GetTop();
        angle = GetTextRotateDegree();
        reverseMap.Rotate(-angle, { pivotX, pivotY });
        mask = reverseMap.GetBoxRect();
    } else {
        mask = invalidatedArea;
        coords = textRect;
    }

    if (mask.Intersect(mask, coords)) {
        LabelRotation rotation {
            invalidatedArea, coords, { coords.GetLeft(), coords.GetTop() }, angle
        };
        Draw(mask, rotation, style, offsetX, ellipsisIndex);
    }
}

void Text::Draw(const Rect& mask, const LabelRotation& rotate, const Style& style, int16_t offsetX,
    uint16_t ellipsisIndex)
{
    Point offset = { offsetX, 0 };
    int16_t lineMaxWidth = expandWidth_ ? textSize_.x : rotate.coords.GetWidth();
    int16_t lineHeight = UIFont::GetInstance()->GetHeight() + style.lineSpace_;
    Point pos;
    pos.y = TextPositionY(rotate.coords);
    char* realText = GetEllipsisText(text_, ellipsisIndex);
    if (realText == nullptr) {
        return;
    }
    uint16_t lineCount = GetLine(realText, lineMaxWidth, style.letterSpace_);
    for (int i = 0; i < lineCount; i++) {
        if (pos.y > mask.GetBottom()) {
            if (ellipsisIndex != TEXT_ELLIPSIS_END_INV) {
                UIFree(realText);
            }
            return;
        }
        uint16_t lineBegin = textLine_[i].lineBegin;
        uint16_t lineWidth;
        int16_t nextLine = pos.y + lineHeight;
        if (nextLine >= mask.GetTop()) {
            int16_t letterSpace = style.letterSpace_;
            lineWidth = TypedText::GetTextWidth(&realText[lineBegin], textLine_[i].lineBytes, letterSpace);
            pos.x = LineStartPos(rotate.coords, lineWidth);
            LabelLineInfo labelLine{ pos, offset, mask, rotate, lineHeight, textLine_[i].lineBytes, 0,
                style.textOpa_, style, &realText[lineBegin], textLine_[i].lineBytes, lineBegin,
                fontId_, static_cast<UITextLanguageDirect>(direct_), nullptr };
            DrawLabel::DrawTextOneLine(labelLine);
        }
        pos.y = nextLine;
    }
    if (ellipsisIndex != TEXT_ELLIPSIS_END_INV) {
        UIFree(realText);
    }
}

int16_t Text::TextPositionY(const Rect& textRect)
{
    int16_t yOffset = 0;
    if (!expandHeight_ && (verticalAlign_ != TEXT_ALIGNMENT_TOP) && (textRect.GetHeight() > textSize_.y)) {
        if (verticalAlign_ == TEXT_ALIGNMENT_CENTER) {
            yOffset = (textRect.GetHeight() - textSize_.y) >> 1;
        }
        if (verticalAlign_ == TEXT_ALIGNMENT_BOTTOM) {
            yOffset = textRect.GetHeight() - textSize_.y;
        }
    }
    return textRect.GetY() + yOffset;
}

int16_t Text::LineStartPos(const Rect& textRect, uint16_t lineWidth)
{
    int16_t xOffset = 0;
    int16_t rectWidth = textRect.GetWidth();
    if (horizontalAlign_ == TEXT_ALIGNMENT_CENTER) {
        xOffset = (direct_ == TEXT_DIRECT_RTL) ?
            ((rectWidth + lineWidth + 1) >> 1) :
            ((rectWidth - lineWidth) >> 1);
    } else if (horizontalAlign_ == TEXT_ALIGNMENT_RIGHT) {
        xOffset = (direct_ == TEXT_DIRECT_RTL) ? rectWidth : (rectWidth - lineWidth);
    } else {
        xOffset = (direct_ == TEXT_DIRECT_RTL) ? lineWidth : 0;
    }
    return textRect.GetX() + xOffset;
}

uint16_t Text::GetLine(const char* text, int16_t width, uint8_t letterSpace)
{
    if (text == nullptr) {
        return 0;
    }
    uint16_t lineNum = 0;
    uint32_t textLen = strlen(text);
    uint16_t begin = 0;
    uint16_t nextBegin = 0;
    while ((begin <= textLen) && (text[begin] != '\0') && (lineNum < MAX_LINE_COUNT)) {
        nextBegin += TypedText::GetNextLine(&text[begin], letterSpace, width);
        textLine_[lineNum].lineBegin = begin;
        textLine_[lineNum].lineBytes = nextBegin - begin;
        begin = nextBegin;
        lineNum++;
    }
    return lineNum;
}

char* Text::GetEllipsisText(char* text, uint16_t ellipsisIndex)
{
    if (ellipsisIndex == TEXT_ELLIPSIS_END_INV) {
        return text;
    }
    uint32_t byteIdx = TypedText::GetByteIndexFromUTF8Id(text, ellipsisIndex);
    uint32_t ellipsisTextSize = byteIdx + TEXT_ELLIPSIS_DOT_NUM + 1;
    char* ellipsisText = reinterpret_cast<char*>(UIMalloc(ellipsisTextSize));
    if (ellipsisText == nullptr) {
        return nullptr;
    }
    if (memcpy_s(ellipsisText, ellipsisTextSize, text, byteIdx) != EOK) {
        UIFree(ellipsisText);
        return nullptr;
    }
    if (memset_s(ellipsisText + byteIdx, TEXT_ELLIPSIS_DOT_NUM + 1, '.', TEXT_ELLIPSIS_DOT_NUM) != EOK) {
        UIFree(ellipsisText);
        return nullptr;
    }
    ellipsisText[ellipsisTextSize - 1] = '\0';

    return ellipsisText;
}

uint16_t Text::GetEllipsisIndex(const Rect& textRect, const Style& style)
{
    if (textSize_.y <= textRect.GetHeight() || TypedText::GetUTF8CharacterSize(text_) <= TEXT_ELLIPSIS_DOT_NUM) {
        return TEXT_ELLIPSIS_END_INV;
    }
    UIFont* pFont = UIFont::GetInstance();
    pFont->SetCurrentFontId(fontId_);
    int16_t letterWidth = pFont->GetWidth('.', 0) + style.letterSpace_;
    Point p;
    p.x = textRect.GetWidth() - letterWidth * TEXT_ELLIPSIS_DOT_NUM;
    p.y = textRect.GetHeight();
    int16_t height = pFont->GetHeight() + style.lineSpace_;
    if (height) {
        p.y -= p.y % height;
    }

    p.y -= style.lineSpace_;
    return GetLetterIndexByPosition(textRect, style, p);
}

uint16_t Text::GetLetterIndexByPosition(const Rect& textRect, const Style& style, const Point& pos)
{
    if (text_ == nullptr) {
        return 0;
    }
    uint32_t lineStart = 0;
    uint32_t nextLineStart = 0;

    uint16_t lineHeight = UIFont::GetInstance()->GetHeight();
    int16_t y = 0;
    uint32_t textLen = static_cast<uint32_t>(strlen(text_));
    while (lineStart < textLen && text_[lineStart] != '\0') {
        nextLineStart += TypedText::GetNextLine(&text_[lineStart], style.letterSpace_, textRect.GetWidth());
        if (pos.y <= y + lineHeight) {
            break;
        }
        y += lineHeight + style.lineSpace_;
        lineStart = nextLineStart;
    }
    /* Calculate the x coordinate */
    int16_t x = 0;
    uint32_t i = lineStart;
    uint32_t pre = i;
    while (i < nextLineStart - 1) {
        uint32_t tmp = i;
        uint32_t letter = TypedText::GetUTF8Next(text_, tmp, i);
        x += UIFont::GetInstance()->GetWidth(letter, 0);
        if (pos.x < x) {
            i = pre;
            break;
        }
        x += style.letterSpace_;
        pre = i;
    }
    return TypedText::GetUTF8CharacterSize(text_, i);
}
} // namespace OHOS