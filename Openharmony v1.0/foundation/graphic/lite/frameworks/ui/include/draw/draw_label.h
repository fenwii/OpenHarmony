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

#ifndef GRAPHIC_LITE_DRAW_LABEL_H
#define GRAPHIC_LITE_DRAW_LABEL_H

#include "common/typed_text.h"
#include "draw/draw_utils.h"
#include "geometry2d.h"
#include "heap_base.h"
#include "style.h"

namespace OHOS {
class DrawLabel : public HeapBase {
public:
    static void DrawTextOneLine(const LabelLineInfo& labelLine);

    static void DrawArcText(const Rect& mask, const char* text, const Point& arcCenter, uint8_t fontId,
        const UIArcLabel::ArcTextInfo arcTextInfo, UIArcLabel::TextOrientation orientation, const Style& style,
        uint8_t opaScale);

    static void DrawLetterWithRotate(const Rect& mask, uint8_t fontId, uint32_t letter, const Point& pos,
        int16_t rotateAngle, const ColorType& color, uint8_t opa);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_DRAW_LABEL_H
