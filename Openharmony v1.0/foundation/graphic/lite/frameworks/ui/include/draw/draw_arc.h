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

#ifndef GRAPHIC_LITE_DRAW_ARC_H
#define GRAPHIC_LITE_DRAW_ARC_H
#include "common/image.h"
#include "draw_image.h"
#include "draw_utils.h"
#include "graphic_math.h"
#include "heap_base.h"
#include "imgdecode/cache_manager.h"
#include "style.h"

namespace OHOS {
struct ArcInfo {
    Point center;
    Point imgPos;
    uint16_t radius;
    int16_t startAngle;
    int16_t endAngle;
    const Image* imgSrc;
};

class DrawArc : public HeapBase {
public:
    static DrawArc* GetInstance()
    {
        static DrawArc drawArc;
        return &drawArc;
    }

    void GetDrawRange(int16_t& start, int16_t& end);

    void Draw(ArcInfo& arcInfo, const Rect& mask, const Style& style, uint8_t opaScale, uint8_t cap);

private:
    static constexpr uint8_t DRAW_ARC_QUADRANT_NUM = 4;
    static constexpr uint8_t ARC_QUADRANT_ONE = 0;
    static constexpr uint8_t ARC_QUADRANT_TWO = 1;
    static constexpr uint8_t ARC_QUADRANT_THREE = 2;
    static constexpr uint8_t ARC_QUADRANT_FOUR = 3;
    static constexpr int16_t IN_DEGREE_RANG = 0;
    static constexpr int16_t OUT_DEGREE_RANG = 1;
    static constexpr int16_t INTERSECT = 2;
    static constexpr int16_t DOUBLE_INTERSECT = 3;

    int16_t lineStart_;
    int16_t lineEnd_;
    int16_t outAntiStart_;
    int16_t outAntiEnd_;
    int16_t inAntiStart_;
    int16_t inAntiEnd_;
    int16_t y_;
    int16_t outRadius_;
    int16_t inRadius_;
    uint32_t ySqr_;
    uint32_t outRadiusSqr_;
    uint32_t inRadiusSqr_;
    bool isCircle_;
    uint32_t antiOutRadiusSqr_;
    uint32_t antiInRadiusSqr_;

    DrawArc()
        : lineStart_(0),
          lineEnd_(0),
          outAntiStart_(0),
          outAntiEnd_(0),
          inAntiStart_(0),
          inAntiEnd_(0),
          y_(0),
          outRadius_(0),
          inRadius_(0),
          ySqr_(0),
          outRadiusSqr_(0),
          inRadiusSqr_(0),
          isCircle_(false),
          antiOutRadiusSqr_(0),
          antiInRadiusSqr_(0)
    {
    }
    ~DrawArc() {}
    void DrawVerLine(const Point& begin,
                     const Point& imgPos,
                     const Rect& mask,
                     int16_t len,
                     const Style& style,
                     uint8_t opaScale,
                     const Image* imgSrc);

    void DrawHorLine(const Point& begin,
                     const Point& imgPos,
                     const Rect& mask,
                     int16_t len,
                     const Style& style,
                     uint8_t opaScale,
                     const Image* imgSrc);

    void DrawImg(const Point& imgPos,
                 Rect& area,
                 const Rect& invalidatedArea,
                 const Style& style,
                 uint8_t opaScale,
                 const Image* imgSrc);

    int16_t GetDegreeRangeIntersectState(uint16_t degreeStart, uint16_t degreeEnd, uint16_t start, uint16_t end);
    uint16_t CalculateTanDegree(uint16_t x, uint16_t y);
    int16_t GetDrawAngle(int16_t angle);
    void DrawCircleNoEndpoint(ArcInfo& arcInfo, const Rect& mask, const Style& style, uint8_t opa, bool anti);
    void DrawAxisLine(ArcInfo& arcInfo, const Rect& mask, const Style& style, uint8_t opa);
    void DrawLineWithDegree(ArcInfo& arcInfo,
                            int16_t start,
                            int16_t end,
                            int16_t y,
                            const Rect& mask,
                            const Style& style,
                            uint8_t opaScale,
                            uint8_t quadrant);
    int16_t DrawLineWithDegreeInner(ArcInfo& arcInfo,
                                    int16_t start,
                                    int16_t end,
                                    int16_t y,
                                    const Rect& mask,
                                    const Style& style,
                                    uint8_t opaScale,
                                    uint8_t quadrant);
#if ENABLE_ANTIALIAS
    void DrawLineAnti(ArcInfo& arcInfo, const Rect& mask, const Style& style, uint8_t opa);
    void DrawPointAnti(ArcInfo& arcInfo, int16_t x, const Rect& mask, const Style& style, uint8_t antiOpa);
#endif
    uint16_t GetDegreeInQuadrant(uint16_t degree, uint8_t quadrant);
    void SetArcInfo(ArcInfo& arcInfo, const Style& style);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_DRAW_ARC_H
