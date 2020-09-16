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

#include "draw/draw_label.h"
#include <cstdio>
#include "common/typed_text.h"
#include "draw/draw_utils.h"
#include "font/ui_font.h"
#include "font/ui_font_header.h"
#include "graphic_log.h"
#include "securec.h"

namespace OHOS {
void DrawLabel::DrawTextOneLine(const LabelLineInfo& labelLine)
{
    UIFont* pFont = UIFont::GetInstance();
    if (labelLine.direct == TEXT_DIRECT_RTL) {
        labelLine.pos.x -= labelLine.offset.x;
    } else {
        labelLine.pos.x += labelLine.offset.x;
    }

    uint32_t i = 0;
    uint32_t tmp;
    while (i < labelLine.lineLength) {
        tmp = i;
        uint32_t letter = TypedText::GetUTF8Next(labelLine.text, tmp, i);

        LabelLetterInfo letterInfo {
            labelLine.pos, labelLine.mask, labelLine.rotate, labelLine.style.textColor_,
            labelLine.opaScale, letter, labelLine.direct, labelLine.fontId, 0
        };
        DrawUtils::GetInstance()->DrawLetter(letterInfo);
        uint16_t letterWidth = pFont->GetWidth(letter, 0);
        if (labelLine.direct == TEXT_DIRECT_RTL) {
            labelLine.pos.x -= (letterWidth + labelLine.style.letterSpace_);
        } else {
            labelLine.pos.x += (letterWidth + labelLine.style.letterSpace_);
        }
    }
}

void DrawLabel::DrawArcText(const Rect& mask, const char* text, const Point& arcCenter, uint8_t fontId,
    const UIArcLabel::ArcTextInfo arcTextInfo, UIArcLabel::TextOrientation orientation, const Style& style,
    uint8_t opaScale)
{
    if (text == nullptr || arcTextInfo.lineStart == arcTextInfo.lineEnd) {
        GRAPHIC_LOGE("DrawLabel::DrawArcText invalid parameter\n");
        return;
    }

    uint16_t letterWidth;
    uint32_t i = arcTextInfo.lineStart;
    uint32_t tmp;
    uint32_t letter;
    int16_t angle = arcTextInfo.startAngle;
    Point pos;
    int16_t rotateAngle;

    while (i < arcTextInfo.lineEnd) {
        tmp = i;
        letter = TypedText::GetUTF8Next(text, tmp, i);
        if (letter == '\r' || letter == '\n') {
            break;
        }
        letterWidth = UIFont::GetInstance()->GetWidth(letter, 0);
        rotateAngle = ((orientation == UIArcLabel::TextOrientation::INSIDE) ? angle : (angle - SEMICIRCLE_IN_DEGREE));

        int16_t tmpRadius = static_cast<int16_t>(arcTextInfo.radius);
        pos.x = arcCenter.x + static_cast<int16_t>(tmpRadius * Sin(angle));
        pos.y = arcCenter.y - static_cast<int16_t>(tmpRadius * Sin(angle + QUARTER_IN_DEGREE));

        DrawLetterWithRotate(mask, fontId, letter, pos, rotateAngle, style.textColor_, opaScale);

        uint32_t arcLen = letterWidth + style.letterSpace_;
        if (arcTextInfo.direct == TEXT_DIRECT_LTR) {
            angle += (SEMICIRCLE_IN_DEGREE * arcLen) / (UI_PI * tmpRadius);
        } else {
            angle += CIRCLE_IN_DEGREE - (SEMICIRCLE_IN_DEGREE * arcLen) / (UI_PI * tmpRadius);
        }
        angle = angle % CIRCLE_IN_DEGREE;
    }
}

void DrawLabel::DrawLetterWithRotate(const Rect& mask, uint8_t fontId, uint32_t letter, const Point& pos,
    int16_t rotateAngle, const ColorType& color, uint8_t opa)
{
    if (opa == OPA_TRANSPARENT) {
        return;
    }
    UIFont* pFont = UIFont::GetInstance();
    FontHeader head;
    GlyphNode node;
    if (pFont->GetCurrentFontHeader(head) != 0) {
        return;
    }

    const uint8_t* fontMap = pFont->GetBitmap(letter, node, 0);
    if (fontMap == nullptr) {
        return;
    }
    UITextLanguageFontParam* fontParam = GetTextLangFontsTable(fontId);
    if (fontParam == nullptr) {
        return;
    }
    uint8_t fontWeight = pFont->GetFontWeight(fontId);
    ColorMode colorMode;
    switch (fontWeight) {
        case FONT_WEIGHT_1:
            colorMode = A1;
            break;
        case FONT_WEIGHT_2:
            colorMode = A2;
            break;
        case FONT_WEIGHT_4:
            colorMode = A4;
            break;
        case FONT_WEIGHT_8:
            colorMode = A8;
            break;
        default:
            return;
    }
    Rect rectLetter;
    rectLetter.SetPosition(pos.x + node.left, pos.y + head.ascender - node.top);
    rectLetter.Resize(node.cols, node.rows);
    TransformMap transMap(rectLetter);
    transMap.Rotate(rotateAngle, Vector2<int16_t>(-node.left, node.top - head.ascender));
    TransformDataInfo letterTranDataInfo = {
        ImageHeader{ colorMode, 0, node.cols, node.rows }, fontMap, fontWeight, BlurLevel::LEVEL0
    };
    DrawUtils::GetInstance()->DrawTransform(mask, Point{ 0, 0 }, color, transMap, letterTranDataInfo);
}
} // namespace OHOS
