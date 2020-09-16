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
 * @file interpolation.h
 *
 * @brief Defines the functions for calculating the interpolation in computer graphics.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_INTERPOLATION_H
#define GRAPHIC_LITE_INTERPOLATION_H

#include "heap_base.h"

namespace OHOS {
/**
 * @brief Calculates the Bezier interpolation.
 *
 * @since 1.0
 * @version 1.0
 */
class Interpolation : public HeapBase {
public:
    /**
     * @brief Obtains the value calculated by the cubic Bezier equation.
     *
     * Use [0, 1024] instead of [0, 1] in the standard Bezier equation. The cubic Bezier equation
     * is <b>B(t) = P0*(1-t)^3 + 3*P1*t*(1-t)^2 + 3*P2*t^2*(1-t) + P3*t^3</b>.
     *
     * @param t  Indicates the current change rate of the cubic Bezier curve, within [0, 1024].
     * @param u0 Indicates the coordinates for the start point of the cubic Bezier curve, within [0, 1024].
     * @param u1 Indicates the coordinates for the first control point of the cubic Bezier curve, within [0, 1024].
     * @param u2 Indicates the coordinates for the second control point of the cubic Bezier curve, within [0, 1024].
     * @param u3 Indicates the coordinates for the end point of the cubic Bezier curve, within [0, 1024].
     *
     * @return Returns the coordinates for the current change rate.
     * @since 1.0
     * @version 1.0
     */
    static int16_t GetBezierInterpolation(int16_t t, int16_t u0, int16_t u1, int16_t u2, int16_t u3);

private:
    constexpr static uint16_t BESSEL_COEFFICIENT = 3;
    constexpr static uint16_t INTERPOLATION_RANGE = 1024;
    constexpr static uint16_t CUBIC_BEZIER_CALCULATE_OFFSET = 30;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_INTERPOLATION_H
