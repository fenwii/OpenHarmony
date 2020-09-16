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
 * @file graphic_types.h
 *
 * @brief Defines the common data types for the graphics system.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_TYPES_H
#define GRAPHIC_LITE_TYPES_H

#include <cstdint>

namespace OHOS {
using TimeType = uint32_t;
using ImageSrcType = uint8_t;

enum BlurLevel : uint8_t {
    INVALID,
    LEVEL0, // no blur
    LEVEL1, // blur one line
    LEVEL2, // blur two line
};

enum TransformAlgorithm : uint8_t {
    NEAREST_NEIGHBOR,
    BILINEAR,
};

enum LabelRotateDegree : uint8_t {
    DEGREE_0,
    DEGREE_90,
    DEGREE_180,
    DEGREE_270,
};

/**
 * @brief colormode of image and font.
 */
enum ColorMode : uint8_t {
    /** ARGB8888 color mode */
    ARGB8888 = 0,
    /** RGB888 color mode */
    RGB888,
    /** RGB565 color mode */
    RGB565,
    /** ARGB1555 color mode */
    ARGB1555,
    /** ARGB4444 color mode */
    ARGB4444,
    /** AL44 color mode */
    AL44,
    /** AL88 color mode */
    AL88,
    /** L1 color mode */
    L1,
    /** L2 color mode */
    L2,
    /** L4 color mode */
    L4,
    /** L8 color mode */
    L8,
    /** A1 color mode */
    A1,
    /** A2 color mode */
    A2,
    /** A4 color mode */
    A4,
    /** A8 color mode */
    A8,
    /** unknow color mode */
    UNKNOW,
};

enum FontWeight : uint8_t {
    FONT_WEIGHT_1 = 1,
    FONT_WEIGHT_2 = 2,
    FONT_WEIGHT_4 = 4,
    FONT_WEIGHT_8 = 8,
};

static constexpr uint8_t SHIFT_2 = 2;
static constexpr uint8_t SHIFT_3 = 3;
static constexpr uint8_t SHIFT_4 = 4;
static constexpr uint8_t SHIFT_8 = 8;
static constexpr uint8_t SHIFT_15 = 15;

/**
 * @brief Defines a point.
 * @since 1.0
 * @version 1.0
 */
struct Point {
    /** X coordinate */
    int16_t x;
    /** Y coordinate */
    int16_t y;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_TYPES_H
