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

#ifndef GRAPHIC_LITE_TYPE_TEXT_H
#define GRAPHIC_LITE_TYPE_TEXT_H

#include "color.h"
#include "components/ui_arc_label.h"
#include "font/ui_font_header.h"
#include "geometry2d.h"
#include "graphic_config.h"

namespace OHOS {
/**
 * @brief typed text, support UTF-8
 */
class TypedText : public HeapBase {
public:
    static Point GetTextSize(const char* text, int16_t letterSpace, int16_t lineSpace, int16_t maxWidth);

    static uint32_t GetNextLine(const char* text, int16_t letterSpace, int16_t maxWidth);

    static uint16_t GetTextWidth(const char* text, uint32_t length, int16_t letterSpace);

    static void GetArcTextRect(Rect& rect,
                               const char* text,
                               const Point& arcCenter,
                               int16_t letterSpace,
                               UIArcLabel::TextOrientation orientation,
                               const UIArcLabel::ArcTextInfo arcTextInfo);

    static uint32_t GetUTF8Next(const char* text, uint32_t i, uint32_t& j);

    static uint8_t GetUTF8OneCharacterSize(const char* str);

    static uint32_t GetByteIndexFromUTF8Id(const char* text, uint32_t utf8Id);

    static uint32_t GetUTF8CharacterSize(const char* text, uint32_t byteIndex = UINT32_MAX);

private:
    static constexpr uint8_t UTF8_TO_UNICODE_SHIFT1 = 6;
    static constexpr uint8_t UTF8_TO_UNICODE_SHIFT2 = 12;
    static constexpr uint8_t UTF8_TO_UNICODE_SHIFT3 = 18;
    static constexpr uint8_t DRAW_ARC_QUADRANT_NUM = 4;
    static bool GetWrapPoint(const char* text, uint32_t& breakPoint);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_TYPE_TEXT_H
