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

#include "common/typed_text.h"

#include "font/ui_font.h"
#include "graphic_log.h"
#include "mem_api.h"
#include "transform.h"

namespace OHOS {
Point TypedText::GetTextSize(const char* text, int16_t letterSpace, int16_t lineSpace, int16_t maxWidth)
{
    Point size{0, 0};
    if (text == nullptr) {
        GRAPHIC_LOGE("TypedText::GetTextSize text invalid parameter\n");
        return size;
    }

    uint32_t lineBegin = 0;
    uint32_t nextLineBegin = 0;
    uint16_t lineHeight = UIFont::GetInstance()->GetHeight();
    while (text[lineBegin] != '\0') {
        nextLineBegin += GetNextLine(&text[lineBegin], letterSpace, maxWidth);
        size.y += lineHeight;
        size.y += lineSpace;
        size.x = MATH_MAX(GetTextWidth(&text[lineBegin], nextLineBegin - lineBegin, letterSpace), size.x);
        lineBegin = nextLineBegin;
    }

    if (size.y == 0) {
        size.y = lineHeight;
    } else {
        size.y -= lineSpace;
    }
    return size;
}

void TypedText::GetArcTextRect(Rect& rect,
                               const char* text,
                               const Point& arcCenter,
                               int16_t letterSpace,
                               UIArcLabel::TextOrientation orientation,
                               const UIArcLabel::ArcTextInfo arcTextInfo)
{
    if (text == nullptr || arcTextInfo.lineStart == arcTextInfo.lineEnd || arcTextInfo.radius == 0 ||
        arcTextInfo.lineEnd > strlen(text)) {
        GRAPHIC_LOGE("TypedText::GetArcTextRect invalid parameter\n");
        return;
    }

    uint16_t letterHeight = UIFont::GetInstance()->GetHeight();
    uint16_t letterWidth;

    int16_t posX = arcCenter.x + static_cast<int16_t>(arcTextInfo.radius * Sin(arcTextInfo.startAngle));
    int16_t posY =
        arcCenter.y - static_cast<int16_t>(arcTextInfo.radius * Sin(arcTextInfo.startAngle + QUARTER_IN_DEGREE));
    rect.SetPosition(posX, posY);

    uint32_t i = arcTextInfo.lineStart;
    uint32_t tmp;
    uint32_t letter;
    uint16_t angle = arcTextInfo.startAngle;
    Rect rectLetter;
    TransformMap transform;
    while (i < arcTextInfo.lineEnd) {
        tmp = i;
        letter = GetUTF8Next(text, tmp, i);
        if (letter == '\r' || letter == '\n') {
            break;
        }
        letterWidth = UIFont::GetInstance()->GetWidth(letter, 0);

        rectLetter.SetPosition(posX, posY);
        rectLetter.Resize(letterWidth, letterHeight);
        transform.SetPolygon(Polygon(rectLetter));
        int16_t rotateAngle =
            ((orientation == UIArcLabel::TextOrientation::INSIDE) ? angle : (angle - SEMICIRCLE_IN_DEGREE));
        transform.Rotate(rotateAngle, Vector2<int16_t>(posX, posY));
        rect.Join(rect, transform.GetBoxRect());
        uint32_t arcLen = letterWidth + letterSpace;
        if (arcTextInfo.direct == TEXT_DIRECT_LTR) {
            angle += (SEMICIRCLE_IN_DEGREE * arcLen) / (UI_PI * arcTextInfo.radius);
        } else {
            angle += CIRCLE_IN_DEGREE - (SEMICIRCLE_IN_DEGREE * arcLen) / (UI_PI * arcTextInfo.radius);
        }
        angle = angle % CIRCLE_IN_DEGREE;
        posX = arcCenter.x + static_cast<int16_t>(arcTextInfo.radius * Sin(angle));
        posY = arcCenter.y - static_cast<int16_t>(arcTextInfo.radius * Sin(angle + QUARTER_IN_DEGREE));
    }
}

uint32_t TypedText::GetNextLine(const char* text, int16_t letterSpace, int16_t maxWidth)
{
    int16_t lastBreakPos = 0;
    int16_t curW = 0;
    uint32_t index = 0;
    uint32_t tmp = 0;
    if (GetWrapPoint(text, index)) {
        return index;
    }

    while (true) {
        curW = TypedText::GetTextWidth(text, index, letterSpace);
        if (curW > maxWidth) {
            index = lastBreakPos;
            if (lastBreakPos == 0) {
                curW = 0;
                uint32_t i = 0;
                uint32_t letter = 0;
                int16_t letterWidth = 0;
                while (text[i] != '\0') {
                    tmp = i;
                    letter = TypedText::GetUTF8Next(text, tmp, i);
                    letterWidth = UIFont::GetInstance()->GetWidth(letter, 0);
                    curW += letterWidth;
                    if (letterWidth > 0) {
                        curW += letterSpace;
                    }
                    if (curW > maxWidth) {
                        index = lastBreakPos;
                        return index;
                    } else {
                        lastBreakPos = i;
                    }
                }
            }
            break;
        }
        if (index > 0 && index < strlen(text) && (text[index - 1] == '\r' || text[index - 1] == '\n')) {
            break;
        }
        lastBreakPos = index;
        if (text[index] == '\0') {
            break;
        }
        if (GetWrapPoint(text + index, tmp)) {
            return index + tmp;
        }
        index += tmp;
        if (lastBreakPos == index) {
            break;
        }
    }
    return index;
}

bool TypedText::GetWrapPoint(const char* text, uint32_t& breakPoint)
{
    breakPoint = 0;
    uint32_t j = 0;
    uint32_t letter = 0;
    if (text == nullptr) {
        return true;
    }

    while (text[breakPoint] != '\0') {
        letter = GetUTF8Next(text, breakPoint, j);
        breakPoint = j;
        if (letter == ' ' || letter == '.' || letter == ',' || letter == '!' || letter == '=' || letter == '?') {
            return false;
        }
        if (letter == '\n') {
            return true;
        }
        if (letter == '\r' && GetUTF8Next(text, breakPoint, j) == '\n') {
            breakPoint = j;
            return true;
        }
    }
    return false;
}

uint16_t TypedText::GetTextWidth(const char* text, uint32_t length, int16_t letterSpace)
{
    if (text == nullptr || length == 0 || length > strlen(text)) {
        GRAPHIC_LOGE("TypedText::GetTextWidth invalid parameter\n");
        return 0;
    }

    uint32_t i = 0;
    uint32_t tmp;
    uint16_t width = 0;
    uint32_t letter;

    while (i < length) {
        tmp = i;
        letter = GetUTF8Next(text, tmp, i);
        if (letter == '\n' || letter == '\r') {
            continue;
        }
        uint16_t charWidth = UIFont::GetInstance()->GetWidth(letter, 0);
        width += charWidth;
        width += letterSpace;
    }

    if (width > 0) {
        width -= letterSpace;
    }
    return width;
}

uint8_t TypedText::GetUTF8OneCharacterSize(const char* str)
{
    unsigned char c = str[0];
    if (c <= 0x7F) {
        return 1;
    } else if (c >= 0xC0 && c <= 0xDF) {
        return 2; // 2: 2 bytes
    } else if (c >= 0xE0 && c <= 0xEF) {
        return 3; // 3: 3 bytes
    } else if (c >= 0xF0 && c <= 0xF7) {
        return 4; // 4: 4 bytes
    } else {
        return 0;
    }
}

uint32_t TypedText::GetUTF8Next(const char* text, uint32_t i, uint32_t& j)
{
    uint32_t unicoode = 0;
    if (text == nullptr) {
        GRAPHIC_LOGE("text invalid parameter");
        return 0;
    }

    j = i;
    uint8_t lettetSize = GetUTF8OneCharacterSize(text + i);
    switch (lettetSize) {
        case 1:
            unicoode = text[j];
            break;
        case 2: // 2: letter size
            unicoode = static_cast<uint32_t>(text[j] & 0x1F) << UTF8_TO_UNICODE_SHIFT1;
            break;
        case 3: // 3: letter size
            unicoode = static_cast<uint32_t>(text[j] & 0x0F) << UTF8_TO_UNICODE_SHIFT2;
            unicoode += static_cast<uint32_t>(text[++j] & 0x3F) << UTF8_TO_UNICODE_SHIFT1;
            unicoode += (text[++j] & 0x3F);
            break;
        case 4: // 4: letter size
            unicoode = static_cast<uint32_t>(text[j] & 0x07) << UTF8_TO_UNICODE_SHIFT3;
            unicoode += static_cast<uint32_t>(text[++j] & 0x3F) << UTF8_TO_UNICODE_SHIFT2;
            unicoode += static_cast<uint32_t>(text[++j] & 0x3F) << UTF8_TO_UNICODE_SHIFT1;
            unicoode += text[++j] & 0x3F;
            break;
        default:
            break;
    }
    j++;
    return unicoode;
}

uint32_t TypedText::GetByteIndexFromUTF8Id(const char* text, uint32_t utf8Id)
{
    if (text == nullptr) {
        GRAPHIC_LOGE("TypedText::GetByteIndexFromUTF8Id text invalid parameter\n");
        return 0;
    }
    uint32_t byteIndex = 0;
    for (uint32_t i = 0; i < utf8Id; i++) {
        byteIndex += GetUTF8OneCharacterSize(&text[byteIndex]);
    }

    return byteIndex;
}

uint32_t TypedText::GetUTF8CharacterSize(const char* text, uint32_t byteIndex)
{
    uint32_t i = 0;
    uint32_t size = 0;
    uint32_t tmp;

    if (text == nullptr) {
        GRAPHIC_LOGE("TypedText::GetUTF8CharacterSize text invalid parameter\n");
        return 0;
    }
    while (text[i] != '\0' && i < byteIndex) {
        tmp = i;
        GetUTF8Next(text, tmp, i);
        size++;
    }

    return size;
}
} // namespace OHOS