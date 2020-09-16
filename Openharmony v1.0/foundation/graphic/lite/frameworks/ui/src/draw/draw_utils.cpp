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

#include "draw/draw_utils.h"
#include "color.h"
#include "draw/draw_triangle.h"
#include "font/ui_font.h"
#include "font/ui_font_header.h"
#include "graphic_log.h"
#include "securec.h"

#if ENABLE_WINDOW && ENABLE_HARDWARE_ACCELERATION
#include "gfx_engines.h"
#endif

namespace OHOS {
// Preprocess operation for draw
#define DRAW_UTILS_PREPROCESS(opa)                                                   \
    if ((opa) == OPA_TRANSPARENT) {                                                       \
        return;                                                                      \
    }                                                                                \
    ScreenBufferType* screenBuffer = ScreenDeviceProxy::GetInstance()->GetBuffer();  \
    if (screenBuffer == nullptr) {                                                   \
        return;                                                                      \
    }                                                                                \
    ScreenDevice* disp = ScreenDeviceProxy::GetInstance()->GetDevice();              \
    if (disp == nullptr) {                                                           \
        return;                                                                      \
    }                                                                                \
    uint16_t screenBufferWidth = ScreenDeviceProxy::GetInstance()->GetBufferWidth(); \
    Rect bufferRect = ScreenDeviceProxy::GetInstance()->GetBufferRect();

// Write color to screen buffer operation
#if COLOR_DEPTH == 32 && ENABLE_BUFFER_RGBA == 0
#define WRITE_BUFFER(c, v)                                                           \
    (c).blue = (v).blue;                                                             \
    (c).green = (v).green;                                                           \
    (c).red = (v).red;

#define WRITE_BUFFER_WITH_ALPHA(hal, color, opa)                                     \
    ColorType bgColor = Color::GetColorFromRGB((hal).red, (hal).green, (hal).blue);  \
    ColorType blendColor = Color::GetMixColor((color), bgColor, (opa));              \
    WRITE_BUFFER((hal), (blendColor))
#else
#define WRITE_BUFFER(c, v) (c).full = (v).full;
#define WRITE_BUFFER_WITH_ALPHA(hal, color, opa) (hal) = Color::GetMixColor((color), (hal), (opa));
#endif

#if ENABLE_DMA2D
constexpr uint8_t MIN_DMA2D_SIZE = 5;
#endif
#ifdef VERSION_STANDARD
const int16_t HARDWARE_ACC_SIZE_LIMIT = 50 * 50;
#endif

static constexpr uint8_t OPACITY_STEP_A1 = 255;
static constexpr uint8_t OPACITY_STEP_A2 = 85;
static constexpr uint8_t OPACITY_STEP_A4 = 17;

TriangleEdge::TriangleEdge(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    curX = static_cast<float>(x1);
    curY = static_cast<float>(y1);
    du = static_cast<float>(x2 - x1);
    dv = static_cast<float>(y2 - y1);
}

TriangleEdge::~TriangleEdge() {}

void DrawUtils::DrawColorAreaBySides(const Rect& mask, const ColorType& color, OpacityType opa,
    const EdgeSides& sides) const
{
    Rect area(sides.left, sides.top, sides.right, sides.bottom);
    DrawUtils::GetInstance()->DrawColorArea(area, mask, color, opa);
}

void DrawUtils::DrawColorArea(const Rect& area, const Rect& mask, const ColorType& color, OpacityType opa) const
{
    DRAW_UTILS_PREPROCESS(opa);
    Rect maskedArea;
    if (!maskedArea.Intersect(area, mask)) {
        return;
    }
#if !ENABLE_WINDOW
    maskedArea.SetRect(maskedArea.GetLeft() - bufferRect.GetLeft(),
        maskedArea.GetTop() - bufferRect.GetTop(),
        maskedArea.GetRight() - bufferRect.GetLeft(),
        maskedArea.GetBottom() - bufferRect.GetTop());
#endif
#if ENABLE_DMA2D
    if (!FillAreaWithDMA2D(maskedArea, screenBuffer, color, opa, disp)) {
        FillAreaWithSoftWare(maskedArea, screenBuffer, screenBufferWidth, color, opa);
    }
#elif ENABLE_WINDOW && ENABLE_HARDWARE_ACCELERATION
    if (!FillAreaWithHardware(maskedArea, color, opa)) {
        FillAreaWithSoftWare(maskedArea, screenBuffer, screenBufferWidth, color, opa);
    }
#else
    FillAreaWithSoftWare(maskedArea, screenBuffer, screenBufferWidth, color, opa);
#endif
}

uint8_t DrawUtils::GetPxSizeByColorMode(uint8_t colorMode)
{
    uint8_t pxSize = 0;

    switch (colorMode) {
        case ARGB8888:
            pxSize = 32; // 32: 32 bit
            break;
        case RGB888:
            pxSize = 24; // 24: 24 bit
            break;
        case RGB565:
        case ARGB1555:
        case ARGB4444:
            pxSize = 16; // 16: 16 bit
            break;
        case L1:
        case A1:
            pxSize = 1; // 1: 1 bit
            break;
        case L2:
        case A2:
            pxSize = 2; // 2: 2 bit
            break;
        case L4:
        case A4:
            pxSize = 4; // 4: 4 bit
            break;
        case L8:
        case A8:
            pxSize = 8; // 8: 8 bit
            break;
        default:
            pxSize = 0;
            break;
    }

    return pxSize;
}

uint8_t DrawUtils::GetPxSizeByImageInfo(ImageInfo imageInfo)
{
    if (imageInfo.header.width == 0 || imageInfo.header.height == 0) {
        return 0;
    }
    /* 3 : when change byte to single pixel, the buffer should multiply by 8, equal to shift left 3 bits. */
    uint8_t pxSize = (imageInfo.dataSize / (imageInfo.header.width * imageInfo.header.height)) << 3;
    return pxSize;
}

void DrawUtils::DrawPixel(int16_t x, int16_t y, const Rect& mask, const ColorType& color, OpacityType opa) const
{
    if (x < mask.GetLeft() || x > mask.GetRight() || y < mask.GetTop() || y > mask.GetBottom()) {
        return;
    }

    DRAW_UTILS_PREPROCESS(opa);

#if !ENABLE_WINDOW
    x -= bufferRect.GetLeft();
    y -= bufferRect.GetTop();
#endif

    screenBuffer += y * screenBufferWidth + x;
    if (opa == OPA_OPAQUE) {
        WRITE_BUFFER(*screenBuffer, color);
    } else {
        WRITE_BUFFER_WITH_ALPHA(*screenBuffer, color, opa);
    }
}

void DrawUtils::DrawLetter(const LabelLetterInfo& letterInfo) const
{
    OpacityType opa = letterInfo.opa;
    DRAW_UTILS_PREPROCESS(opa);
    UIFont* pFont = UIFont::GetInstance();
    FontHeader head;
    GlyphNode node;
    if (pFont->GetCurrentFontHeader(head) != 0) {
        return;
    }

    const uint8_t* fontMap = pFont->GetBitmap(letterInfo.letter, node, letterInfo.shapingId);
    if (fontMap == nullptr) {
        return;
    }
    uint16_t letterW = node.cols;
    uint16_t letterH = node.rows;
    uint8_t opacityMask;
    int16_t posX;
    int16_t posY = letterInfo.pos.y + head.ascender - node.top;
    uint8_t fontWeight = pFont->GetFontWeight(letterInfo.fontId);
    uint8_t colorMode = 0;
    uint8_t opacityStep = 1;
    switch (fontWeight) {
        case FONT_WEIGHT_1:
            opacityStep = OPACITY_STEP_A1;
            opacityMask = 0x01;
            colorMode = A1;
            break;
        case FONT_WEIGHT_2:
            opacityStep = OPACITY_STEP_A2;
            opacityMask = 0x03;
            colorMode = A2;
            break;
        case FONT_WEIGHT_4:
            opacityStep = OPACITY_STEP_A4;
            opacityMask = 0x0F;
            colorMode = A4;
            break;
        case FONT_WEIGHT_8:
            opacityMask = 0xFF;
            colorMode = A8;
            break;
        default:
            return;
    }

    if (letterInfo.direct == TEXT_DIRECT_RTL) {
        /* RTL */
        posX = letterInfo.pos.x - node.advance + node.left;
    } else {
        /* LTR */
        posX = letterInfo.pos.x + node.left;
    }

    if (posX + letterW < letterInfo.mask.GetLeft() || posX > letterInfo.mask.GetRight() ||
        posY + letterH < letterInfo.mask.GetTop() || posY > letterInfo.mask.GetBottom()) {
        return;
    }

    if (letterInfo.rotate.degree != 0) {
        Rect rectLetter;
        rectLetter.SetPosition(posX, posY);
        rectLetter.Resize(letterW, letterH);
        TransformMap transform(rectLetter);
        int16_t pivotRelativeX = letterInfo.rotate.pivot.x - posX;
        int16_t pivotRelativeY = letterInfo.rotate.pivot.y - posY;
        transform.Rotate(letterInfo.rotate.degree, { pivotRelativeX, pivotRelativeY });
        TransformDataInfo letterTranDataInfo = {
            ImageHeader{ colorMode, 0, node.cols, node.rows }, fontMap, fontWeight, BlurLevel::LEVEL0
        };
        DrawTransform(letterInfo.rotate.realMask, { 0, 0 }, letterInfo.color, transform, letterTranDataInfo);
        return;
    }

    uint16_t rowStart = (posY >= letterInfo.mask.GetTop()) ? 0 : (letterInfo.mask.GetTop() - posY);
    uint16_t rowEnd =
        (posY + letterH <= letterInfo.mask.GetBottom()) ? letterH : (letterInfo.mask.GetBottom() - posY + 1);
    uint16_t colStart = (posX >= letterInfo.mask.GetLeft()) ? 0 : (letterInfo.mask.GetLeft() - posX);
    uint16_t colEnd =
        (posX + letterW <= letterInfo.mask.GetRight()) ? letterW : (letterInfo.mask.GetRight() - posX + 1);

    uint8_t letterWidthInByte = (letterW * fontWeight) >> SHIFT_3;
    if ((letterW * fontWeight) & 0x7) {
        letterWidthInByte++;
    }

#if ENABLE_WINDOW
    screenBuffer += (posY * screenBufferWidth) + posX;
#else
    screenBuffer += ((posY - bufferRect.GetTop()) * screenBufferWidth) + posX - bufferRect.GetLeft();
#endif
    screenBuffer += (rowStart * screenBufferWidth) + colStart;
    fontMap += (rowStart * letterWidthInByte) + ((colStart * fontWeight) >> SHIFT_3);

#if ENABLE_DMA2D & ENABLE_DMA2D_TEXT
    bool isDMA2DSupport = true;
    if (colorMode != A4 && colorMode != A8) {
        isDMA2DSupport = false;
    }

    uint32_t fillAreaWidth = colEnd - colStart;
    uint32_t destOffset = screenBufferWidth - fillAreaWidth;
    uint32_t srcOffset = letterW - fillAreaWidth;
    if (colorMode == A4 && (srcOffset != 0)) {
        isDMA2DSupport = false;
    }
    if (disp->GetDMA2DBlendState() && isDMA2DSupport) {
        if (colorMode == A4 && (fillAreaWidth & 0x1) != 0) {
            fillAreaWidth++;
            destOffset--;
        }
        disp->DMA2DBlend(fontMap, destOffset, srcOffset, colorMode, BUFFER_COLOR_MODE, fillAreaWidth, rowEnd - rowStart,
            opa, Color::ColorTo32(letterInfo.color), reinterpret_cast<uint8_t*>(screenBuffer));
        return;
    }
#endif
    uint8_t offsetInFont = (colStart * fontWeight) % FONT_WEIGHT_8;
    int16_t temp = (colEnd - colStart) * fontWeight - FONT_WEIGHT_8 + offsetInFont;
    if (temp < 0) {
        temp = 0;
    }
    int16_t validWidthInByte = temp / FONT_WEIGHT_8 + 1;
    if (temp % FONT_WEIGHT_8 != 0) {
        validWidthInByte++;
    }
    for (int16_t i = rowStart; i < rowEnd; i++) {
        int16_t col = colStart;
        uint8_t tempOffset = offsetInFont;
        uint8_t tempFontByte = (*fontMap++) >> offsetInFont;
        while (col < colEnd) {
            while (tempOffset < FONT_WEIGHT_8 && col < colEnd) {
                uint8_t validOpacity = tempFontByte & opacityMask;
                if (validOpacity != 0) {
                    validOpacity *= opacityStep;
                    if (opa != OPA_OPAQUE) {
                        validOpacity =
                            static_cast<OpacityType>((static_cast<uint16_t>(validOpacity) * opa) >> FONT_WEIGHT_8);
                    }
                    WRITE_BUFFER_WITH_ALPHA(*screenBuffer, letterInfo.color, validOpacity);
                }
                screenBuffer++;
                tempFontByte = tempFontByte >> fontWeight;
                tempOffset += fontWeight;
                col++;
            }
            tempOffset = 0;
            tempFontByte = *(fontMap++);
        }
        fontMap += (letterWidthInByte) - validWidthInByte - 1;
        screenBuffer += screenBufferWidth - (colEnd - colStart);
    }
}

void DrawUtils::DrawImage(const Rect& area, const Rect& mask, const uint8_t* image, OpacityType opa,
    uint8_t pxByteSize) const
{
    if (image == nullptr) {
        return;
    }
    DRAW_UTILS_PREPROCESS(opa);
    Rect maskedArea;
    Rect originMaskedArea;
    if (!originMaskedArea.Intersect(area, mask)) {
        return;
    }
#if ENABLE_WINDOW
    maskedArea = originMaskedArea;
#else
    maskedArea.SetRect(originMaskedArea.GetLeft() - bufferRect.GetLeft(),
                       originMaskedArea.GetTop() - bufferRect.GetTop(),
                       originMaskedArea.GetRight() - bufferRect.GetLeft(),
                       originMaskedArea.GetBottom() - bufferRect.GetTop());
#endif

    screenBuffer += static_cast<uint32_t>(screenBufferWidth) * maskedArea.GetTop();
    screenBuffer += static_cast<uint32_t>(maskedArea.GetLeft());

    int16_t mapWidth = area.GetWidth();
    if (area.GetTop() < originMaskedArea.GetTop()) {
        image += static_cast<uint32_t>(mapWidth) * (originMaskedArea.GetTop() - area.GetTop()) * pxByteSize;
    }
    if (area.GetLeft() < originMaskedArea.GetLeft()) {
        image += static_cast<uint32_t>(originMaskedArea.GetLeft() - area.GetLeft()) * pxByteSize;
    }

#if ENABLE_DMA2D
    ColorMode srcMode;
    if (pxByteSize == static_cast<uint8_t>(PixelType::IMG_RGB888)) {
        srcMode = RGB888;
    } else if (pxByteSize == static_cast<uint8_t>(PixelType::IMG_RGB565)) {
        srcMode = RGB565;
    } else if (pxByteSize == static_cast<uint8_t>(PixelType::IMG_ARGB8888)) {
        srcMode = ARGB8888;
    } else {
        GRAPHIC_LOGE("DrawUtils::DrawImage image format err\n");
        return;
    }

    if (disp->GetDMA2DBlendState() && maskedArea.GetHeight() > MIN_DMA2D_SIZE &&
        maskedArea.GetWidth() > MIN_DMA2D_SIZE) {
        BlendWithDMA2D(maskedArea, screenBuffer, area, reinterpret_cast<const ColorType*>(image), srcMode, opa, disp);
        return;
    }
#endif
    /* RGB565 RGB888 color mode, image src don't have alpha */
    for (int16_t row = maskedArea.GetTop(); row <= maskedArea.GetBottom(); row++) {
        BlendWithSoftWare(screenBuffer, image, maskedArea.GetWidth(), opa, pxByteSize);
        image += mapWidth * pxByteSize;
        screenBuffer += screenBufferWidth;
    }
}

#if ENABLE_DMA2D
void DrawUtils::BlendWithDMA2D(const Rect& fillArea, ScreenBufferType* dest, const Rect& srcArea, const ColorType* src,
    uint32_t srcColorMode, const OpacityType& opa, const DisplayDevice* disp, const ColorType& color) const
{
    uint32_t destOffset = ScreenDeviceProxy::GetInstance()->GetBufferWidth() - fillArea.GetWidth();
    uint32_t srcOffset = srcArea.GetWidth() - fillArea.GetWidth();
    uint32_t color32 = Color::ColorTo32(color);
    disp->DMA2DBlend(reinterpret_cast<const uint8_t*>(src), destOffset, srcOffset, srcColorMode, BUFFER_COLOR_MODE,
        fillArea.GetWidth(), fillArea.GetHeight(), opa, color32, reinterpret_cast<uint8_t*>(dest));
}

bool DrawUtils::FillAreaWithDMA2D(const Rect& fillArea, ScreenBufferType* mem, const ColorType& color,
    const OpacityType& opa, const DisplayDevice* disp) const
{
    int16_t height = fillArea.GetHeight();
    int16_t width = fillArea.GetWidth();
    if (!disp->GetDMA2DFillState() || height <= MIN_DMA2D_SIZE || width <= MIN_DMA2D_SIZE) {
        return false;
    }
    uint32_t screenBufferWidth = ScreenDeviceProxy::GetInstance()->GetBufferWidth();
    ScreenBufferType* screenBuffer = mem + screenBufferWidth * fillArea.GetTop();
    uint32_t destOffset = screenBufferWidth - width;
    uint32_t color32 = Color::ColorTo32(color);
    screenBuffer += fillArea.GetLeft();
    disp->DMA2DFill(color32, destOffset, BUFFER_COLOR_MODE, width, height, opa,
        reinterpret_cast<uint8_t*>(screenBuffer));
    return true;
}
#endif

#if ENABLE_WINDOW && ENABLE_HARDWARE_ACCELERATION
bool DrawUtils::FillAreaWithHardware(const Rect& fillArea, const ColorType& color, const OpacityType& opa) const
{
    if (opa != OPA_OPAQUE && fillArea.GetSize() >= HARDWARE_ACC_SIZE_LIMIT) {
        AllocationInfo gfxAlloc = ScreenDeviceProxy::GetInstance()->GetAllocationInfo();
        LiteSurfaceData data;
        data.phyAddr = gfxAlloc.phyAddr;
        data.width = gfxAlloc.width;
        data.height = gfxAlloc.height;
        data.stride = gfxAlloc.stride;
        data.pixelFormat = gfxAlloc.pixelFormat;
        if (GfxEngines::GetInstance()->GfxFillArea(data, fillArea, color, opa)) {
            return true;
        }
    }
    return false;
}
#endif

void DrawUtils::FillAreaWithSoftWare(const Rect& fillArea, ScreenBufferType* mem, int16_t screenBufferWidth,
    const ColorType& color, const OpacityType& opa) const
{
    int32_t halBufferDeltaByteLen = static_cast<int32_t>(screenBufferWidth) * sizeof(ScreenBufferType);
    int16_t width = fillArea.GetWidth();
    int16_t height = fillArea.GetHeight();
    int32_t offset = static_cast<int32_t>(fillArea.GetTop()) * screenBufferWidth + fillArea.GetLeft();
    mem += offset;
    int32_t dstMaxSize = (ScreenDeviceProxy::GetInstance()->GetScreenArea() - offset) * sizeof(ScreenBufferType);

    if (opa == OPA_OPAQUE) {
        for (int16_t col = 0; col < width; col++) {
            WRITE_BUFFER(mem[col], color);
        }
        ScreenBufferType* memStart = mem;
        int32_t memSize = static_cast<int32_t>(width) * sizeof(ScreenBufferType);
        mem += screenBufferWidth;
        dstMaxSize -= halBufferDeltaByteLen;
        for (int16_t row = 1; row < height; row++) {
            if (memcpy_s(mem, dstMaxSize, memStart, memSize) != EOK) {
                GRAPHIC_LOGE("DrawUtils::FillAreaWithSoftWare memcpy failed!\n");
                return;
            }
            mem += screenBufferWidth;
            dstMaxSize -= halBufferDeltaByteLen;
        }
    } else {
        ColorType backgroundColor = Color::Black();
        ColorType mixColor = Color::GetMixColor(color, backgroundColor, opa);
        for (int16_t row = 0; row < height; row++) {
            for (int16_t col = 0; col < width; col++) {
#if COLOR_DEPTH == 32
                if (mem[col].blue != backgroundColor.blue || mem[col].green != backgroundColor.green ||
                    mem[col].red != backgroundColor.red) {
#else
                if (mem[col].full != backgroundColor.full) {
#endif
                    WRITE_BUFFER(backgroundColor, mem[col]);
                    mixColor = Color::GetMixColor(color, backgroundColor, opa);
                }
                WRITE_BUFFER(mem[col], mixColor);
            }
            mem += screenBufferWidth;
        }
    }
}

void DrawUtils::BlendWithSoftWare(ScreenBufferType* dest, const uint8_t* src, uint32_t length, OpacityType opa,
    uint8_t pxByteSize) const
{
    ColorType color;
#if COLOR_DEPTH == 32 /* halbuffer is RGB888 */
    if (pxByteSize == static_cast<uint8_t>(PixelType::IMG_RGB888)) {
        if (opa == OPA_OPAQUE) {
            /* hal buffer is RGB888, image buffer RGB888, just memcpy */
            if (memcpy_s(dest, length * sizeof(Color24), src, length * sizeof(Color24)) != EOK) {
                return;
            }
        } else {
            Color24* temp = reinterpret_cast<Color24*>(const_cast<uint8_t*>(src));
            for (uint32_t col = 0; col < length; col++, temp++) {
                color = Color::GetColorFromRGB(temp->red, temp->green, temp->blue);
                WRITE_BUFFER_WITH_ALPHA(dest[col], color, opa);
            }
        }
    } else if (pxByteSize == static_cast<uint8_t>(PixelType::IMG_RGB565)) {
        Color16* temp = reinterpret_cast<Color16*>(const_cast<uint8_t*>(src));
        for (uint32_t col = 0; col < length; col++, temp++) {
            color.full = Color::ColorTo32(*temp, 255);
            if (opa == OPA_OPAQUE) {
                WRITE_BUFFER(dest[col], color);
            } else {
                WRITE_BUFFER_WITH_ALPHA(dest[col], color, opa);
            }
        }
    }
#else /* halbuffer is RGB565 */
    if (pxByteSize == static_cast<uint8_t>(PixelType::IMG_RGB565)) {
        if (opa == OPA_OPAQUE) {
            /* hal buffer is RGB565, image buffer RGB565, just memcpy */
            if (memcpy_s(dest, length * sizeof(Color16), src, length * sizeof(Color16)) != EOK) {
                return;
            }
        } else {
            Color16* temp = reinterpret_cast<Color16*>(const_cast<uint8_t*>(src));
            for (uint32_t col = 0; col < length; col++, temp++) {
                WRITE_BUFFER_WITH_ALPHA(dest[col], *temp, opa);
            }
        }
    } else if (pxByteSize == static_cast<uint8_t>(PixelType::IMG_RGB888)) {
        Color24* temp = reinterpret_cast<Color24*>(const_cast<uint8_t*>(src));
        for (uint32_t col = 0; col < length; col++, temp++) {
            color = Color::GetColorFromRGB(temp->red, temp->green, temp->blue);
            if (opa == OPA_OPAQUE) {
                dest[col].blue = color.blue;
                dest[col].green = color.green;
                dest[col].red = color.red;
            } else {
                WRITE_BUFFER_WITH_ALPHA(dest[col], color, opa);
            }
        }
    }
#endif
    else if (pxByteSize == static_cast<uint8_t>(PixelType::IMG_ARGB8888)) {
        Color32* temp = reinterpret_cast<Color32*>(const_cast<uint8_t*>(src));
        for (uint32_t col = 0; col < length; col++, temp++) {
            if (temp->alpha == OPA_TRANSPARENT) {
                continue;
            }
            if (opa == OPA_OPAQUE && temp->alpha == OPA_OPAQUE) {
                WRITE_BUFFER(dest[col], *temp);
            } else {
                OpacityType opaResult = opa;
                color = Color::GetColorFromRGB(temp->red, temp->green, temp->blue);
                opaResult = static_cast<uint32_t>(static_cast<uint32_t>(temp->alpha) * opaResult) >> 8;
                WRITE_BUFFER_WITH_ALPHA(dest[col], color, opaResult);
            }
        }
    } else {
        GRAPHIC_LOGE("DrawUtils::BlendWithSoftWare image format err\n");
    }
}

void DrawUtils::GetTransformInitState(const TransformMap& transMap, const Point& position,
    const Rect& trans, TransformInitState& init)
{
    int16_t offsetX = -transMap.translate_.GetData()[6] + position.x; // 6: x shift
    int16_t offsetY = -transMap.translate_.GetData()[7] + position.y; // 7: y shift
    float cosma = transMap.rotate_.GetData()[0] * 1.0 / 32768; // 32768: 2^15, int to float
    float sinma = transMap.rotate_.GetData()[1] * 1.0 / 32768; // 32768: 2^15, int to float
    int16_t x = trans.GetLeft();
    int16_t y = trans.GetTop();
    float scaleX = 1.0 * transMap.scale_.GetData()[0] / (1 << SHIFT_8); // x scale ratio
    float scaleY = 1.0 * transMap.scale_.GetData()[4] / (1 << SHIFT_8); // y scale ratio
    Point pivot = transMap.GetPivot();

    init.verticalU = (cosma * (x - pivot.x - offsetX) - sinma * (y - pivot.y - offsetY)) * scaleX + pivot.x;
    init.verticalV = (sinma * (x - pivot.x - offsetX) + cosma * (y - pivot.y - offsetY)) * scaleY + pivot.y;
    init.duHorizon = cosma * scaleX;
    init.dvHorizon = sinma * scaleX;
    init.duVertical = -sinma * scaleY;
    init.dvVertical = cosma * scaleY;
}

void DrawUtils::DrawRectTransformNearestTrueColor(const Rect& mask, const Point& position, const ColorType& color,
    const TransformMap& transMap, const TransformDataInfo& dataInfo)
{
    TransformInitState init;
    Rect trans = transMap.GetBoxRect();
    trans.SetX(trans.GetX() + position.x);
    trans.SetY(trans.GetY() + position.y);
    trans.Intersect(mask, trans);
    GetTransformInitState(transMap, position, trans, init);

#if ENABLE_WINDOW
    const int32_t xMin = trans.GetLeft();
    const int32_t xMax = trans.GetRight();
    const int32_t yMin = trans.GetTop();
    const int32_t yMax = trans.GetBottom();
#else
    Rect bufferRect = ScreenDeviceProxy::GetInstance()->GetBufferRect();
    const int32_t xMin = trans.GetLeft() - bufferRect.GetLeft();
    const int32_t xMax = trans.GetRight() - bufferRect.GetLeft();
    const int32_t yMin = trans.GetTop() - bufferRect.GetTop();
    const int32_t yMax = trans.GetBottom() - bufferRect.GetTop();
#endif

    uint8_t* imgHead = const_cast<uint8_t*>(dataInfo.data);
    int32_t dstMaxSize = ScreenDeviceProxy::GetInstance()->GetScreenArea() * sizeof(ScreenBufferType);
    const uint8_t pixelSize = dataInfo.pxSize >> SHIFT_3;
    uint16_t screenBufferWidth = ScreenDeviceProxy::GetInstance()->GetBufferWidth();
    int32_t offset = yMin * screenBufferWidth + xMin;
    ScreenBufferType* screenBuffer = ScreenDeviceProxy::GetInstance()->GetBuffer() + offset;
    dstMaxSize -= offset * sizeof(ScreenBufferType);
    const int16_t deltaWidth = screenBufferWidth - (xMax - xMin + 1);

    int32_t blurLevel = dataInfo.blurLevel;
    if (dataInfo.blurLevel == BlurLevel::INVALID) {
        blurLevel = BlurLevel::LEVEL0;
    }
    init.duVertical *= blurLevel;
    init.dvVertical *= blurLevel;

    const int32_t dstLineWidth = sizeof(ScreenBufferType) * (xMax - xMin + 1);
    const int32_t srcLineWidth = dataInfo.header.width * pixelSize;
    const int32_t halBufferDeltaByteLen = screenBufferWidth * sizeof(ScreenBufferType);
    for (int16_t y = yMin; y <= yMax; y += blurLevel) {
        float u = init.verticalU;
        float v = init.verticalV;
        ScreenBufferType* preLine = screenBuffer;
        for (int16_t x = xMin; x <= xMax; x++) {
            const int32_t intU = static_cast<int32_t>(u);
            const int32_t intV = static_cast<int32_t>(v);
            if (intU >= 0 && intU < dataInfo.header.width && intV >= 0 && intV < dataInfo.header.height) {
#ifndef _LITEOS
                uint32_t px = intV * srcLineWidth + intU * pixelSize;
#else
                uint32_t val1 = __SMUAD(intV, srcLineWidth);
                uint32_t val2 = __SMUAD(intU, pixelSize);
                uint32_t px = val1 + val2;
#endif
                ColorType src = *(reinterpret_cast<ColorType*>(&imgHead[px]));
                if (dataInfo.header.colorMode == RGB888 || dataInfo.header.colorMode == RGB565) {
                    WRITE_BUFFER(*screenBuffer, src);
                } else if (src.alpha == OPA_OPAQUE) {
                    WRITE_BUFFER(*screenBuffer, src);
                } else if (src.alpha != OPA_TRANSPARENT) {
                    WRITE_BUFFER_WITH_ALPHA(*screenBuffer, src, src.alpha);
                }
            }
            u += init.duHorizon;
            v += init.dvHorizon;
            screenBuffer++;
        }
        screenBuffer += deltaWidth;
        dstMaxSize -= halBufferDeltaByteLen;

        // just copy to blur
        for (int32_t k = 0; k < blurLevel - 1; k++) {
            if (memcpy_s(screenBuffer, dstMaxSize, preLine, dstLineWidth) != EOK) {
                return;
            }
            screenBuffer += screenBufferWidth;
            dstMaxSize -= halBufferDeltaByteLen;
        }
        init.verticalU += init.duVertical;
        init.verticalV += init.dvVertical;
    }
}

inline void DrawUtils::StepToNextLine(TriangleEdge& edge1, TriangleEdge& edge2)
{
    edge1.curY++;
    edge2.curY++;
    edge1.curX += edge1.du / edge1.dv;
    edge2.curX += edge2.du / edge2.dv;
}

void DrawUtils::DrawTriangleAlphaBilinear(const TriangleScanInfo& in)
{
    for (int16_t y = in.yMin; y <= in.yMax; y++) {
        int16_t xMin = static_cast<int16_t>(in.edge1.curX);
        int16_t xMax = static_cast<int16_t>(in.edge2.curX);
#if ENABLE_WINDOW
        ScreenBufferType* screenBuffer = in.screenBuffer + y * in.screenBufferWidth + xMin;
#else
        ScreenBufferType* screenBuffer = in.screenBuffer + (y - in.screenBufferRect.GetTop()) * in.screenBufferWidth +
            (xMin - in.screenBufferRect.GetLeft());
#endif
        float u = in.init.verticalU;
        float v = in.init.verticalV;
        for (int16_t x = xMin; x <= xMax; x++) {
            const int16_t intU = static_cast<int16_t>(u);
            const int16_t intV = static_cast<int16_t>(v);
            if (u >= 0 && intU < in.info.header.width - 1 && v >= 0 && intV < in.info.header.height - 1) {
                const int16_t intUPlus1 = intU + 1;
                const int16_t intVPlus1 = intV + 1;
                OpacityType p1 = GetPxAlphaForAlphaImg(in.info, { intU, intV });
                OpacityType p2 = GetPxAlphaForAlphaImg(in.info, { intUPlus1, intV });
                OpacityType p3 = GetPxAlphaForAlphaImg(in.info, { intU, intVPlus1 });
                OpacityType p4 = GetPxAlphaForAlphaImg(in.info, { intUPlus1, intVPlus1 });

                float decU = u - intU;
                float decV = v - intV;
                float decUMinus1 = 1.0f - decU;
                float decVMinus1 = 1.0f - decV;

                const int32_t w1 = static_cast<int32_t>(decUMinus1 * decVMinus1 * 256.0f); // 256:shift 8 bit left
                const int32_t w2 = static_cast<int32_t>(decU * decVMinus1 * 256.0f); // 256:shift 8 bit left
                const int32_t w3 = static_cast<int32_t>(decUMinus1 * decV * 256.0f); // 256:shift 8 bit left
                const int32_t w4 = static_cast<int32_t>(decU * decV * 256.0f); // 256:shift 8 bit left

#ifndef _LITEOS
                const int32_t outA = p1 * w1 + p2 * w2 + p3 * w3 + p4 * w4;
#else
                const int32_t outA = __SMUAD(p1, w1) + __SMUAD(p2, w2) + __SMUAD(p3, w3) + __SMUAD(p4, w4);
#endif
                ColorType result = in.color;
                result.alpha = static_cast<uint8_t>(outA >> 8); // 8:shift 8 bit right
                WRITE_BUFFER_WITH_ALPHA(*screenBuffer, result, result.alpha);
            }
            u += in.init.duHorizon;
            v += in.init.dvHorizon;
            screenBuffer++;
        }
        StepToNextLine(in.edge1, in.edge2);
        in.init.verticalU += in.init.duVertical;
        in.init.verticalV += in.init.dvVertical;
        int16_t deltaX = static_cast<int16_t>(in.edge1.curX) - xMin;
        in.init.verticalU += in.init.duHorizon * deltaX;
        in.init.verticalV += in.init.dvHorizon * deltaX;
    }
}

void DrawUtils::DrawTriangleTrueColorBilinear565(const TriangleScanInfo& in)
{
    for (int16_t y = in.yMin; y <= in.yMax; y++) {
        int16_t xMin = static_cast<int16_t>(in.edge1.curX);
        int16_t xMax = static_cast<int16_t>(in.edge2.curX);
#if ENABLE_WINDOW
        ScreenBufferType* screenBuffer = in.screenBuffer + y * in.screenBufferWidth + xMin;
#else
        ScreenBufferType* screenBuffer = in.screenBuffer + (y - in.screenBufferRect.GetTop()) * in.screenBufferWidth +
            (xMin - in.screenBufferRect.GetLeft());
#endif
        float u = in.init.verticalU;
        float v = in.init.verticalV;
        for (int16_t x = xMin; x <= xMax; x++) {
            const int16_t intU = static_cast<int16_t>(u);
            const int16_t intV = static_cast<int16_t>(v);
            if (u >= 0 && intU < in.info.header.width - 1 && v >= 0 && intV < in.info.header.height - 1) {
#ifndef _LITEOS
                uint32_t px1 = intV * in.srcLineWidth + intU * in.pixelSize;
#else
                uint32_t val1 = __SMUAD(intV, in.srcLineWidth);
                uint32_t val2 = __SMUAD(intU, in.pixelSize);
                uint32_t px1 = val1 + val2;
#endif
                uint8_t* imgHead = const_cast<uint8_t *>(in.info.data);
                const Color16 p1 = *(reinterpret_cast<Color16*>(&imgHead[px1]));
                const Color16 p2 = *(reinterpret_cast<Color16*>(&imgHead[px1 + in.pixelSize]));
                const Color16 p3 = *(reinterpret_cast<Color16*>(&imgHead[px1 + in.srcLineWidth]));
                const Color16 p4 = *(reinterpret_cast<Color16*>(&imgHead[px1 + in.srcLineWidth + in.pixelSize]));

                float decU = u - intU;
                float decV = v - intV;
                float decUMinus1 = 1 - decU;
                float decVMinus1 = 1 - decV;

                const int32_t w1 = static_cast<int32_t>(decUMinus1 * decVMinus1 * 256.0f); // 256:shift 8 bit left
                const int32_t w2 = static_cast<int32_t>(decU * decVMinus1 * 256.0f); // 256:shift 8 bit left
                const int32_t w3 = static_cast<int32_t>(decUMinus1 * decV * 256.0f); // 256:shift 8 bit left
                const int32_t w4 = static_cast<int32_t>(decU * decV * 256.0f); // 256:shift 8 bit left
#ifndef _LITEOS
                const int32_t outR = p1.red * w1 + p2.red * w2 + p3.red * w3 + p4.red * w4;
                const int32_t outG = p1.green * w1 + p2.green * w2 + p3.green * w3 + p4.green * w4;
                const int32_t outB = p1.blue * w1 + p2.blue * w2 + p3.blue * w3 + p4.blue * w4;
#else
                const int32_t outR = __SMUAD(p1.red, w1) + __SMUAD(p2.red, w2) + __SMUAD(p3.red, w3) +
                    __SMUAD(p4.red, w4);
                const int32_t outG = __SMUAD(p1.green, w1) + __SMUAD(p2.green, w2) + __SMUAD(p3.green, w3) +
                    __SMUAD(p4.green, w4);
                const int32_t outB = __SMUAD(p1.blue, w1) + __SMUAD(p2.blue, w2) + __SMUAD(p3.blue, w3) +
                    __SMUAD(p4.blue, w4);
#endif

                ColorType result;
                result.red = static_cast<uint8_t>(outR >> 5); // 8:shift 8 bit right
                result.green = static_cast<uint8_t>(outG >> 6); // 8:shift 8 bit right
                result.blue = static_cast<uint8_t>(outB >> 5); // 8:shift 8 bit right
                WRITE_BUFFER(*screenBuffer, result);
            }
            u += in.init.duHorizon;
            v += in.init.dvHorizon;
            screenBuffer++;
        }
        StepToNextLine(in.edge1, in.edge2);
        in.init.verticalU += in.init.duVertical;
        in.init.verticalV += in.init.dvVertical;
        int16_t deltaX = static_cast<int16_t>(in.edge1.curX) - xMin;
        in.init.verticalU += in.init.duHorizon * deltaX;
        in.init.verticalV += in.init.dvHorizon * deltaX;
    }
}

void DrawUtils::DrawTriangleTrueColorBilinear888(const TriangleScanInfo& in)
{
    for (int16_t y = in.yMin; y <= in.yMax; y++) {
        int16_t xMin = static_cast<int16_t>(in.edge1.curX);
        int16_t xMax = static_cast<int16_t>(in.edge2.curX);
#if ENABLE_WINDOW
        ScreenBufferType* screenBuffer = in.screenBuffer + y * in.screenBufferWidth + xMin;
#else
        ScreenBufferType* screenBuffer = in.screenBuffer + (y - in.screenBufferRect.GetTop()) * in.screenBufferWidth +
            (xMin - in.screenBufferRect.GetLeft());
#endif
        float u = in.init.verticalU;
        float v = in.init.verticalV;
        for (int16_t x = xMin; x <= xMax; x++) {
            const int16_t intU = static_cast<int16_t>(u);
            const int16_t intV = static_cast<int16_t>(v);
            if (u >= 0 && intU < in.info.header.width - 1 && v >= 0 && intV < in.info.header.height - 1) {
#ifndef _LITEOS
                uint32_t px1 = intV * in.srcLineWidth + intU * in.pixelSize;
#else
                uint32_t val1 = __SMUAD(intV, in.srcLineWidth);
                uint32_t val2 = __SMUAD(intU, in.pixelSize);
                uint32_t px1 = val1 + val2;
#endif
                uint8_t* imgHead = const_cast<uint8_t*>(in.info.data);
                const Color24 p1 = *(reinterpret_cast<Color24*>(&imgHead[px1]));
                const Color24 p2 = *(reinterpret_cast<Color24*>(&imgHead[px1 + in.pixelSize]));
                const Color24 p3 = *(reinterpret_cast<Color24*>(&imgHead[px1 + in.srcLineWidth]));
                const Color24 p4 = *(reinterpret_cast<Color24*>(&imgHead[px1 + in.srcLineWidth + in.pixelSize]));

                float decU = u - intU;
                float decV = v - intV;
                float decUMinus1 = 1 - decU;
                float decVMinus1 = 1 - decV;

                const int32_t w1 = static_cast<int32_t>(decUMinus1 * decVMinus1 * 256.0f); // 256:shift 8 bit left
                const int32_t w2 = static_cast<int32_t>(decU * decVMinus1 * 256.0f); // 256:shift 8 bit left
                const int32_t w3 = static_cast<int32_t>(decUMinus1 * decV * 256.0f); // 256:shift 8 bit left
                const int32_t w4 = static_cast<int32_t>(decU * decV * 256.0f); // 256:shift 8 bit left
#ifndef _LITEOS
                const int32_t outR = p1.red * w1 + p2.red * w2 + p3.red * w3 + p4.red * w4;
                const int32_t outG = p1.green * w1 + p2.green * w2 + p3.green * w3 + p4.green * w4;
                const int32_t outB = p1.blue * w1 + p2.blue * w2 + p3.blue * w3 + p4.blue * w4;
#else
                const int32_t outR = __SMUAD(p1.red, w1) + __SMUAD(p2.red, w2) + __SMUAD(p3.red, w3) +
                    __SMUAD(p4.red, w4);
                const int32_t outG = __SMUAD(p1.green, w1) + __SMUAD(p2.green, w2) + __SMUAD(p3.green, w3) +
                    __SMUAD(p4.green, w4);
                const int32_t outB = __SMUAD(p1.blue, w1) + __SMUAD(p2.blue, w2) + __SMUAD(p3.blue, w3) +
                    __SMUAD(p4.blue, w4);
#endif

                ColorType result;
                result.red = static_cast<uint8_t>(outR >> 8); // 8:shift 8 bit right
                result.green = static_cast<uint8_t>(outG >> 8); // 8:shift 8 bit right
                result.blue = static_cast<uint8_t>(outB >> 8); // 8:shift 8 bit right
                WRITE_BUFFER(*screenBuffer, result);
            }
            u += in.init.duHorizon;
            v += in.init.dvHorizon;
            screenBuffer++;
        }
        StepToNextLine(in.edge1, in.edge2);
        in.init.verticalU += in.init.duVertical;
        in.init.verticalV += in.init.dvVertical;
        int16_t deltaX = static_cast<int16_t>(in.edge1.curX) - xMin;
        in.init.verticalU += in.init.duHorizon * deltaX;
        in.init.verticalV += in.init.dvHorizon * deltaX;
    }
}

void DrawUtils::DrawTriangleTrueColorBilinear8888(const TriangleScanInfo& in)
{
    for (int16_t y = in.yMin; y <= in.yMax; y++) {
        int16_t xMin = static_cast<int16_t>(in.edge1.curX);
        int16_t xMax = static_cast<int16_t>(in.edge2.curX);
#if ENABLE_WINDOW
        ScreenBufferType* screenBuffer = in.screenBuffer + y * in.screenBufferWidth + xMin;
#else
        ScreenBufferType* screenBuffer = in.screenBuffer + (y - in.screenBufferRect.GetTop()) * in.screenBufferWidth +
            (xMin - in.screenBufferRect.GetLeft());
#endif
        float u = in.init.verticalU;
        float v = in.init.verticalV;
        for (int16_t x = xMin; x <= xMax; x++) {
            const int16_t intU = static_cast<int16_t>(u);
            const int16_t intV = static_cast<int16_t>(v);
            if (u >= 0 && intU < in.info.header.width - 1 && v >= 0 && intV < in.info.header.height - 1) {
#ifndef _LITEOS
                uint32_t px1 = intV * in.srcLineWidth + intU * in.pixelSize;
#else
                uint32_t val1 = __SMUAD(intV, in.srcLineWidth);
                uint32_t val2 = __SMUAD(intU, in.pixelSize);
                uint32_t px1 = val1 + val2;
#endif
                uint8_t* imgHead = const_cast<uint8_t *>(in.info.data);
                const ColorType p1 = *(reinterpret_cast<ColorType*>(&imgHead[px1]));
                const ColorType p2 = *(reinterpret_cast<ColorType*>(&imgHead[px1 + in.pixelSize]));
                const ColorType p3 = *(reinterpret_cast<ColorType*>(&imgHead[px1 + in.srcLineWidth]));
                const ColorType p4 = *(reinterpret_cast<ColorType*>(&imgHead[px1 + in.srcLineWidth + in.pixelSize]));

                float decU = u - intU;
                float decV = v - intV;
                float decUMinus1 = 1 - decU;
                float decVMinus1 = 1 - decV;

                const int32_t w1 = static_cast<int32_t>(decUMinus1 * decVMinus1 * 256.0f); // 256:shift 8 bit left
                const int32_t w2 = static_cast<int32_t>(decU * decVMinus1 * 256.0f); // 256:shift 8 bit left
                const int32_t w3 = static_cast<int32_t>(decUMinus1 * decV * 256.0f); // 256:shift 8 bit left
                const int32_t w4 = static_cast<int32_t>(decU * decV * 256.0f); // 256:shift 8 bit left
#ifndef _LITEOS
                const int32_t outR = p1.red * w1 + p2.red * w2 + p3.red * w3 + p4.red * w4;
                const int32_t outG = p1.green * w1 + p2.green * w2 + p3.green * w3 + p4.green * w4;
                const int32_t outB = p1.blue * w1 + p2.blue * w2 + p3.blue * w3 + p4.blue * w4;
                const int32_t outA = p1.alpha * w1 + p2.alpha * w2 + p3.alpha* w3 + p4.alpha * w4;
#else
                const int32_t outR = __SMUAD(p1.red, w1) + __SMUAD(p2.red, w2) + __SMUAD(p3.red, w3) +
                    __SMUAD(p4.red, w4);
                const int32_t outG = __SMUAD(p1.green, w1) + __SMUAD(p2.green, w2) + __SMUAD(p3.green, w3) +
                    __SMUAD(p4.green, w4);
                const int32_t outB = __SMUAD(p1.blue, w1) + __SMUAD(p2.blue, w2) + __SMUAD(p3.blue, w3) +
                    __SMUAD(p4.blue, w4);
                const int32_t outA = __SMUAD(p1.alpha, w1) + __SMUAD(p2.alpha, w2) + __SMUAD(p3.alpha, w3) +
                    __SMUAD(p4.alpha, w4);
#endif

                ColorType result;
                result.red = static_cast<uint8_t>(outR >> 8); // 8:shift 8 bit right
                result.green = static_cast<uint8_t>(outG >> 8); // 8:shift 8 bit right
                result.blue = static_cast<uint8_t>(outB >> 8); // 8:shift 8 bit right
                result.alpha = static_cast<uint8_t>(outA >> 8); // 8:shift 8 bit right

                if (result.alpha == OPA_OPAQUE) {
                    WRITE_BUFFER(*screenBuffer, result);
                } else if (result.alpha > OPA_TRANSPARENT) {
                    WRITE_BUFFER_WITH_ALPHA(*screenBuffer, result, result.alpha);
                }
            }
            u += in.init.duHorizon;
            v += in.init.dvHorizon;
            screenBuffer++;
        }
        StepToNextLine(in.edge1, in.edge2);
        in.init.verticalU += in.init.duVertical;
        in.init.verticalV += in.init.dvVertical;
        int16_t deltaX = static_cast<int16_t>(in.edge1.curX) - xMin;
        in.init.verticalU += in.init.duHorizon * deltaX;
        in.init.verticalV += in.init.dvHorizon * deltaX;
    }
}

void DrawUtils::DrawTriangleTrueColorNearest(const TriangleScanInfo& in)
{
    for (int16_t y = in.yMin; y <= in.yMax; y++) {
        int16_t xMin = static_cast<int16_t>(in.edge1.curX);
        int16_t xMax = static_cast<int16_t>(in.edge2.curX);
#if ENABLE_WINDOW
        ScreenBufferType* screenBuffer = in.screenBuffer + y * in.screenBufferWidth + xMin;
#else
        ScreenBufferType* screenBuffer = in.screenBuffer + (y - in.screenBufferRect.GetTop()) * in.screenBufferWidth +
            (xMin - in.screenBufferRect.GetLeft());
#endif
        float u = in.init.verticalU;
        float v = in.init.verticalV;
        for (int16_t x = xMin; x <= xMax; x++) {
            const int16_t intU = static_cast<int16_t>(u);
            const int16_t intV = static_cast<int16_t>(v);
            if (u >= 0 && intU < in.info.header.width - 1 && v >= 0 && intV < in.info.header.height - 1) {
#ifndef _LITEOS
                uint32_t px1 = intV * in.srcLineWidth + intU * in.pixelSize;
#else
                uint32_t val1 = __SMUAD(intV, in.srcLineWidth);
                uint32_t val2 = __SMUAD(intU, in.pixelSize);
                uint32_t px1 = val1 + val2;
#endif
                uint8_t* imgHead = const_cast<uint8_t*>(in.info.data);
                ColorType p1 = *(reinterpret_cast<ColorType*>(&imgHead[px1]));
                if (in.info.header.colorMode == RGB888 || in.info.header.colorMode == RGB565) {
                    WRITE_BUFFER(*screenBuffer, p1);
                } else if (p1.alpha == OPA_OPAQUE) {
                    WRITE_BUFFER(*screenBuffer, p1);
                } else if (p1.alpha > OPA_TRANSPARENT) {
                    WRITE_BUFFER_WITH_ALPHA(*screenBuffer, p1, p1.alpha);
                }
            }
            u += in.init.duHorizon;
            v += in.init.dvHorizon;
            screenBuffer++;
        }
        StepToNextLine(in.edge1, in.edge2);
        in.init.verticalU += in.init.duVertical;
        in.init.verticalV += in.init.dvVertical;
        int16_t deltaX = static_cast<int16_t>(in.edge1.curX) - xMin;
        in.init.verticalU += in.init.duHorizon * deltaX;
        in.init.verticalV += in.init.dvHorizon * deltaX;
    }
}

void DrawUtils::DrawTriangleTransformPart(const TrianglePartInfo& part)
{
    part.edge1.curX += part.edge1.du * (part.yMin - part.edge1.curY) / part.edge1.dv;
    part.edge1.curY = part.yMin;
    part.edge2.curX += part.edge2.du * (part.yMin - part.edge2.curY) / part.edge2.dv;
    part.edge2.curY = part.yMin;

    Rect line;
    line.SetLeft(static_cast<int16_t>(part.edge1.curX));
    line.SetRight(static_cast<int16_t>(part.edge1.curX));
    line.SetTop(static_cast<int16_t>(part.edge1.curY));
    line.SetBottom(static_cast<int16_t>(part.edge1.curY));
    TransformInitState init;
    GetTransformInitState(part.transMap, part.position, line, init);

    uint16_t screenBufferWidth = ScreenDeviceProxy::GetInstance()->GetBufferWidth();
    ScreenBufferType* screenBuffer = ScreenDeviceProxy::GetInstance()->GetBuffer();
    if (screenBuffer == nullptr) {
        return;
    }
    Rect bufferRect = ScreenDeviceProxy::GetInstance()->GetBufferRect();
    uint8_t pixelSize;
    DrawTriangleTransformFuc fuc;
    bool isTrueColor = part.info.header.colorMode == ARGB8888 || part.info.header.colorMode == RGB888 ||
                       part.info.header.colorMode == RGB565;
    if (isTrueColor) {
        pixelSize = part.info.pxSize >> SHIFT_3;
        fuc = DrawTriangleTrueColorBilinear8888;
        if (part.info.algorithm == TransformAlgorithm::NEAREST_NEIGHBOR) {
            fuc = DrawTriangleTrueColorNearest;
        } else if (part.info.header.colorMode == ARGB8888) {
            fuc = DrawTriangleTrueColorBilinear8888;
        } else if (part.info.header.colorMode == RGB888) {
            fuc = DrawTriangleTrueColorBilinear888;
        } else {
            fuc = DrawTriangleTrueColorBilinear565;
        }
    } else {
        pixelSize = part.info.pxSize;
        fuc = DrawTriangleAlphaBilinear;
    }
    const int32_t srcLineWidth = part.info.header.width * pixelSize;
    TriangleScanInfo input {
        part.yMin, part.yMax, part.edge1, part.edge2, screenBuffer, bufferRect, part.color, init,
        screenBufferWidth, pixelSize, srcLineWidth, part.info
    };
    fuc(input);
}

void DrawUtils::DrawTriangleTransform(const Rect& mask, const Point& position,
    const ColorType& color, const TransformMap& transMap, const TriangleTransformDataInfo& triangleInfo)
{
    bool p3IsInRight = ((triangleInfo.p1.y - triangleInfo.p2.y) * triangleInfo.p3.x +
        (triangleInfo.p2.x - triangleInfo.p1.x) * triangleInfo.p3.y +
        triangleInfo.p1.x * triangleInfo.p2.y - triangleInfo.p2.x * triangleInfo.p1.y) < 0;
    int16_t yMin = 0;
    int16_t yMax = 0;
    TriangleEdge edge1;
    TriangleEdge edge2;
    TrianglePartInfo part {
        mask, transMap, position, edge1, edge2, yMin, yMax, triangleInfo.info, color
    };

    if (triangleInfo.p2.y == triangleInfo.p1.y) {
        goto BottomHalf;
    }
    if (p3IsInRight) {
        edge1 = TriangleEdge(triangleInfo.p1.x, triangleInfo.p1.y, triangleInfo.p2.x, triangleInfo.p2.y);
        edge2 = TriangleEdge(triangleInfo.p1.x, triangleInfo.p1.y, triangleInfo.p3.x, triangleInfo.p3.y);
    } else {
        edge2 = TriangleEdge(triangleInfo.p1.x, triangleInfo.p1.y, triangleInfo.p2.x, triangleInfo.p2.y);
        edge1 = TriangleEdge(triangleInfo.p1.x, triangleInfo.p1.y, triangleInfo.p3.x, triangleInfo.p3.y);
    }

    part.yMin = MATH_MAX(mask.GetTop(), triangleInfo.p1.y);
    part.yMax = MATH_MIN(mask.GetBottom(), triangleInfo.p2.y);
    part.edge1 = edge1;
    part.edge2 = edge2;
    DrawTriangleTransformPart(part);
BottomHalf:
    if (triangleInfo.p2.y == triangleInfo.p3.y) {
        return;
    }

    if (triangleInfo.p2.y == triangleInfo.p1.y) {
        if (triangleInfo.p1.x < triangleInfo.p2.x) {
            edge1 = TriangleEdge(triangleInfo.p1.x, triangleInfo.p1.y, triangleInfo.p3.x, triangleInfo.p3.y);
            edge2 = TriangleEdge(triangleInfo.p2.x, triangleInfo.p2.y, triangleInfo.p3.x, triangleInfo.p3.y);
        } else {
            edge2 = TriangleEdge(triangleInfo.p1.x, triangleInfo.p1.y, triangleInfo.p3.x, triangleInfo.p3.y);
            edge1 = TriangleEdge(triangleInfo.p2.x, triangleInfo.p2.y, triangleInfo.p3.x, triangleInfo.p3.y);
        }
    } else {
        if (p3IsInRight) {
            edge1 = TriangleEdge(triangleInfo.p2.x, triangleInfo.p2.y, triangleInfo.p3.x, triangleInfo.p3.y);
        } else {
            edge2 = TriangleEdge(triangleInfo.p2.x, triangleInfo.p2.y, triangleInfo.p3.x, triangleInfo.p3.y);
        }
    }

    part.yMin = MATH_MAX(mask.GetTop(), triangleInfo.p2.y);
    part.yMax = MATH_MIN(mask.GetBottom(), triangleInfo.p3.y);
    part.edge1 = edge1;
    part.edge2 = edge2;
    DrawTriangleTransformPart(part);
}

void DrawUtils::DrawTransform(const Rect& mask, const Point& position,
    const ColorType& color, const TransformMap& transMap, const TransformDataInfo& dataInfo) const
{
    Rect trans = transMap.GetBoxRect();
    trans.SetX(trans.GetX() + position.x);
    trans.SetY(trans.GetY() + position.y);
    if (!trans.Intersect(trans, mask)) {
        return;
    }

    if (dataInfo.header.colorMode == RGB888 || (dataInfo.header.colorMode == ARGB8888 &&
        dataInfo.blurLevel > BlurLevel::LEVEL0)) {
        return DrawRectTransformNearestTrueColor(mask, position, color, transMap, dataInfo);
    }

    TriangleTransformDataInfo triangleInfo { dataInfo, };
    Polygon polygon = transMap.GetPolygon();
    Point p1;
    p1.x = polygon[0].x_ + position.x; // 0:first point
    p1.y = polygon[0].y_ + position.y; // 0:first point
    Point p2;
    p2.x = polygon[1].x_ + position.x; // 1:second point
    p2.y = polygon[1].y_ + position.y; // 1:second point
    Point p3;
    p3.x = polygon[2].x_ + position.x; // 2:third point
    p3.y = polygon[2].y_ + position.y; // 2:third point
    DrawTriangle::SortVertexs(p1, p2, p3);
    triangleInfo.p1 = p1;
    triangleInfo.p2 = p2;
    triangleInfo.p3 = p3;
    if (triangleInfo.p1.y <= mask.GetBottom() && triangleInfo.p3.y >= mask.GetTop()) {
        DrawTriangleTransform(mask, position, color, transMap, triangleInfo);
    }

    p1.x = polygon[0].x_ + position.x; // 0:first point
    p1.y = polygon[0].y_ + position.y; // 0:first point
    p3.x = polygon[2].x_ + position.x; // 2:third point
    p3.y = polygon[2].y_ + position.y; // 2:third point
    Point p4;
    p4.x = polygon[3].x_ + position.x; // 3:fourth point
    p4.y = polygon[3].y_ + position.y; // 3:fourth point
    DrawTriangle::SortVertexs(p1, p3, p4);
    triangleInfo.p1 = p1;
    triangleInfo.p2 = p3;
    triangleInfo.p3 = p4;
    if (triangleInfo.p1.y <= mask.GetBottom() && triangleInfo.p3.y >= mask.GetTop()) {
        DrawTriangleTransform(mask, position, color, transMap, triangleInfo);
    }
}

OpacityType DrawUtils::GetPxAlphaForAlphaImg(const TransformDataInfo& dataInfo, const Point& point)
{
    Point tmpPoint = point;
    const uint8_t* bufU8 = const_cast<uint8_t*>(dataInfo.data);
#if ENABLE_SPEC_FONT
    if (dataInfo.header.colorMode == A1) {
        uint8_t bit = tmpPoint.x & 0x7;
        tmpPoint.x = tmpPoint.x >> 3;

        uint32_t px = (dataInfo.header.width >> 3) * tmpPoint.y + tmpPoint.x;
        uint8_t pxOpa = (bufU8[px] & (1 << (7 - bit))) >> (7 - bit);
        return pxOpa ? OPA_TRANSPARENT : OPA_OPAQUE;
    } else if (dataInfo.header.colorMode == A2) {
        uint8_t bit = (tmpPoint.x & 0x3) * 2;
        tmpPoint.x = tmpPoint.x >> SHIFT_2;

        uint32_t px = (dataInfo.header.width >> 2) * tmpPoint.y + tmpPoint.x;
        uint8_t pxOpa = (bufU8[px] & (3 << (SHIFT_6 - bit))) >> (SHIFT_6 - bit);
        return pxOpa * OPACITY_STEP_A2;
    } else if (dataInfo.header.colorMode == A8) {
        uint32_t px = dataInfo.header.width * tmpPoint.y + tmpPoint.x;
        return bufU8[px];
    }
#else
    uint8_t letterWidthInByte = (dataInfo.header.width * dataInfo.pxSize) >> SHIFT_3;
    if ((dataInfo.header.width * dataInfo.pxSize) & 0x7) {
        letterWidthInByte++;
    }
    uint8_t bit = (tmpPoint.x & 0x1) << SHIFT_2;
    bufU8 += (tmpPoint.y * letterWidthInByte) + ((tmpPoint.x * dataInfo.pxSize) >> SHIFT_3);
    uint8_t pxOpa = (*bufU8 & (0xF << bit)) >> (bit);
    return pxOpa * OPACITY_STEP_A4;
#endif // ENABLE_SPEC_FONT
}

void DrawUtils::DrawTranspantArea(const Rect& rect, const Rect& mask)
{
    FillArea(rect, mask, true, nullptr);
}

void DrawUtils::DrawWithBuffer(const Rect& rect, const Rect& mask, const ColorType* colorBuf)
{
    FillArea(rect, mask, false, colorBuf);
}

void DrawUtils::FillArea(const Rect& rect, const Rect& mask, bool isTransparent, const ColorType* colorBuf)
{
    Rect maskedArea;
    if (!maskedArea.Intersect(rect, mask)) {
        return;
    }

    int16_t left = maskedArea.GetLeft();
    int16_t right = maskedArea.GetRight();
    int16_t top = maskedArea.GetTop();
    int16_t bottom = maskedArea.GetBottom();

#if ENABLE_WINDOW != 1
    Rect bufferRect = ScreenDeviceProxy::GetInstance()->GetBufferRect();
    maskedArea.SetLeft(left - bufferRect.GetLeft());
    maskedArea.SetRight(right - bufferRect.GetLeft());
    maskedArea.SetTop(top - bufferRect.GetTop());
    maskedArea.SetBottom(bottom - bufferRect.GetTop());
#endif

    uint16_t screenBufferWidth = ScreenDeviceProxy::GetInstance()->GetBufferWidth();
    ScreenBufferType* mem = ScreenDeviceProxy::GetInstance()->GetBuffer();

    mem += top * screenBufferWidth;
    if (isTransparent) {
        ColorType transColor = Color::GetColorFromRGBA(0, 0, 0, 0);
        for (int16_t row = top; row <= bottom; row++) {
            for (int16_t col = left; col <= right; col++) {
                WRITE_BUFFER(mem[col], transColor);
            }
            mem += screenBufferWidth;
        }
    } else {
        if (colorBuf == nullptr) {
            return;
        }
        for (int16_t row = top; row <= bottom; row++) {
            for (int16_t col = left; col <= right; col++) {
                WRITE_BUFFER(mem[col], colorBuf[row * screenBufferWidth + col]);
            }
            mem += screenBufferWidth;
        }
    }
}
} // namespace OHOS