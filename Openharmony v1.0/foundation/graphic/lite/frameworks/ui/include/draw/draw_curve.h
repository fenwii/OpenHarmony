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

#ifndef GRAPHIC_LITE_DRAW_CURVE_H
#define GRAPHIC_LITE_DRAW_CURVE_H

#include "color.h"
#include "geometry2d.h"

namespace OHOS {
class DrawCurve : public HeapBase {
public:
    static void DrawCubicBezier(const Point& start, const Point& control1, const Point& control2, const Point& end,
        const Rect& mask, int16_t width, const ColorType& color, OpacityType opacity);
private:
    static constexpr uint16_t INTERPOLATION_RANGE = 1024;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_DRAW_CURVE_H