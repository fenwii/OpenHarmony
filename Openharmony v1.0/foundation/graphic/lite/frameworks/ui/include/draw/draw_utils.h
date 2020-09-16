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

#ifndef GRAPHIC_LITE_DRAW_UTILS_H
#define GRAPHIC_LITE_DRAW_UTILS_H

#include "color.h"
#include "common/text.h"
#include "graphic_types.h"
#include "common/screen_device_proxy.h"
#include "geometry2d.h"
#include "style.h"
#include "transform.h"

namespace OHOS {
struct EdgeSides {
    int16_t left;
    int16_t right;
    int16_t top;
    int16_t bottom;
};

struct LabelLineInfo {
    Point& pos;
    Point& offset;
    const Rect& mask;
    const LabelRotation& rotate;
    int16_t lineHeight;
    uint16_t lineLength;
    uint8_t shapingId;
    uint8_t opaScale;
    const Style& style;

    const char* text;
    uint16_t length;
    uint16_t start;
    uint8_t fontId;
    UITextLanguageDirect direct;
    uint32_t* codePoints;
};

struct LabelLetterInfo {
    const Point& pos;
    Rect mask;
    const LabelRotation& rotate;

    const ColorType& color;
    OpacityType opa;

    const uint32_t& letter;
    UITextLanguageDirect direct;
    uint8_t fontId;
    uint8_t shapingId;
};

struct TransformInitState {
    float verticalU;
    float verticalV;
    float duHorizon;
    float dvHorizon;
    float duVertical;
    float dvVertical;
};

struct TriangleEdge {
    TriangleEdge() {}
    TriangleEdge(int16_t x1, int16_t y1, int16_t duInt, int16_t dvInt);
    ~TriangleEdge();
    float curX = 0.0f;
    float curY = 0.0f;
    float du = 0.0f;
    float dv = 0.0f;
};
struct TransformDataInfo {
    ImageHeader header;
    const uint8_t* data;
    uint8_t pxSize;
    BlurLevel blurLevel;
    TransformAlgorithm algorithm;
};

struct TriangleTransformDataInfo {
    const TransformDataInfo& info;
    Point p1;
    Point p2;
    Point p3;
};

struct TriangleScanInfo {
    int16_t yMin;
    int16_t yMax;
    TriangleEdge& edge1;
    TriangleEdge& edge2;
    ScreenBufferType* screenBuffer;
    Rect screenBufferRect;
    const ColorType& color;
    TransformInitState& init;
    uint16_t screenBufferWidth;
    uint8_t pixelSize;
    const int32_t srcLineWidth;
    const TransformDataInfo& info;
};

struct TrianglePartInfo {
    const Rect& mask;
    const TransformMap& transMap;
    const Point& position;
    TriangleEdge& edge1;
    TriangleEdge& edge2;
    int16_t yMin;
    int16_t yMax;
    const TransformDataInfo& info;
    const ColorType& color;
};

enum {
    IMG_SRC_VARIABLE,
    IMG_SRC_FILE,
    IMG_SRC_UNKNOWN,
};

enum PixelType {
    IMG_RGB565 = 2,
    IMG_RGB888 = 3,
    IMG_ARGB8888 = 4,
};

class DrawUtils : public HeapBase {
public:
    static DrawUtils* GetInstance()
    {
        static DrawUtils instance;
        return &instance;
    }

    void DrawColorArea(const Rect& area, const Rect& mask, const ColorType& color, OpacityType opa) const;

    void DrawColorAreaBySides(const Rect& mask, const ColorType& color, OpacityType opa, const EdgeSides& sides) const;

    void DrawPixel(int16_t x, int16_t y, const Rect& mask, const ColorType& color, OpacityType opa) const;

    void DrawLetter(const LabelLetterInfo& letterInfo) const;

    void DrawImage(const Rect& area, const Rect& mask, const uint8_t* image, OpacityType opa, uint8_t pxByteSize) const;

    static void GetTransformInitState(const TransformMap& transMap, const Point& position,
        const Rect& trans, TransformInitState& init);

    static void DrawTriangleTransform(const Rect& mask, const Point& position, const ColorType& color,
        const TransformMap& transMap, const TriangleTransformDataInfo& dataInfo);

    void DrawTransform(const Rect& mask, const Point& position, const ColorType& color, const TransformMap& transMap,
        const TransformDataInfo& dataInfo) const;

    void DrawTranspantArea(const Rect& rect, const Rect& mask);

    void DrawWithBuffer(const Rect& rect, const Rect& mask, const ColorType* colorBuf);

    static uint8_t GetPxSizeByColorMode(uint8_t colorMode);

    static uint8_t GetPxSizeByImageInfo(ImageInfo imageInfo);

private:
#if ENABLE_WINDOW && ENABLE_HARDWARE_ACCELERATION
    bool FillAreaWithHardware(const Rect& fillArea, const ColorType& color, const OpacityType& opa) const;
#endif
    void FillAreaWithSoftWare(const Rect& fillArea, ScreenBufferType* mem, int16_t bufWidth, const ColorType& color,
        const OpacityType& opa) const;
#if ENABLE_DMA2D
    bool FillAreaWithDMA2D(const Rect& fillArea, ScreenBufferType* mem, const ColorType& color,
        const OpacityType& opa, const DisplayDevice* disp) const;
    void BlendWithDMA2D(const Rect& fillArea, ScreenBufferType* dest, const Rect& srcArea, const ColorType* src,
        uint32_t srcColorMode, const OpacityType& opa, const DisplayDevice* disp,
        const ColorType& color = Color::White()) const;
#endif
    void BlendWithSoftWare(ScreenBufferType* dest, const uint8_t* src, uint32_t length,
        OpacityType opa, uint8_t pxByteSize) const;

    static void DrawRectTransformNearestTrueColor(const Rect& mask, const Point& position, const ColorType& color,
        const TransformMap& transMap, const TransformDataInfo& dataInfo);

    using DrawTriangleTransformFuc = void(*)(const TriangleScanInfo& triangle);

    static void DrawTriangleTrueColorNearest(const TriangleScanInfo& triangle);

    static void DrawTriangleAlphaBilinear(const TriangleScanInfo& triangle);

    static void DrawTriangleTrueColorBilinear565(const TriangleScanInfo& triangle);

    static void DrawTriangleTrueColorBilinear888(const TriangleScanInfo& triangle);

    static void DrawTriangleTrueColorBilinear8888(const TriangleScanInfo& triangle);

    inline static void StepToNextLine(TriangleEdge& edg1, TriangleEdge& edg2);

    static void DrawTriangleTransformPart(const TrianglePartInfo& part);

    static OpacityType GetPxAlphaForAlphaImg(const TransformDataInfo& dataInfo, const Point& point);

    void FillArea(const Rect& rect, const Rect& mask, bool isTransparent, const ColorType* colorBuf);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_DRAW_UTILS_H
