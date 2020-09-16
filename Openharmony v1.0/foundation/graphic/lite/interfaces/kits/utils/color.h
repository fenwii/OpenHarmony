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
 * @file color.h
 *
 * @brief Defines color attributes for the graphics system and implements common color functions.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_COLOR_H
#define GRAPHIC_LITE_COLOR_H

#include <cstdint>

#include "graphic_config.h"
#include "heap_base.h"

namespace OHOS {
/**
 * @brief Defines the color attribute when the color depth is <b>16</b>.
 */
typedef union {
    struct {
        /** Blue */
        uint16_t blue : 5;
        /** Green */
        uint16_t green : 6;
        /** Red */
        uint16_t red : 5;
    };
    /** Full RGB data */
    uint16_t full;
} Color16;

/**
 * @brief Defines the color attribute when the color depth is <b>24</b>.
 */
struct Color24 {
    /** Blue */
    uint8_t blue;
    /** Green */
    uint8_t green;
    /** Red */
    uint8_t red;
};

/**
 * @brief Defines the color attribute when the color depth is <b>32</b>.
 */
typedef union {
    struct {
        /** Blue */
        uint8_t blue;
        /** Green */
        uint8_t green;
        /** Red */
        uint8_t red;
        /** Alpha (how opaque each pixel is) */
        uint8_t alpha;
    };
    /** Full RGB data */
    uint32_t full;
} Color32;

#if COLOR_DEPTH == 16
typedef Color16 ColorType;
#elif COLOR_DEPTH == 32
typedef Color32 ColorType;
#else
#error "Invalid COLOR_DEPTH, Set it to 16 or 32!"
#endif

using OpacityType = uint8_t;

/**
 * @brief Enumerates opacity values.
 */
enum {
    /** The opacity is 0. */
    OPA_TRANSPARENT = 0,
    /** The opacity is 100%. */
    OPA_OPAQUE = 255,
};

/**
 * @brief Converts colors in different formats and defines common colors.
 *
 * @since 1.0
 * @version 1.0
 */
class Color : public HeapBase {
public:
    /**
     * @brief Mixes two colors (color 1 and color 2) based on a specified opacity.
     *
     * @param c1 Indicates color 1.
     * @param c2 Indicates color 2.
     * @param mix Indicates the alpha, that is, how opaque each pixel is.

     * @return Returns the color data after mixing.
     * @since 1.0
     * @version 1.0
     */
    static ColorType GetMixColor(ColorType c1, ColorType c2, uint8_t mix)
    {
        ColorType ret;
        /* COLOR_DEPTH is 16 or 32 */
        // 8: right move 8 bit. 255: 2^8-1
        ret.red = (static_cast<uint16_t>(c1.red) * mix + (static_cast<uint16_t>(c2.red) * (255 - mix))) >> 8;
        // 8: right move 8 bit. 255: 2^8-1
        ret.green = (static_cast<uint16_t>(c1.green) * mix + (static_cast<uint16_t>(c2.green) * (255 - mix))) >> 8;
        // 8: right move 8 bit. 255: 2^8-1
        ret.blue = (static_cast<uint16_t>(c1.blue) * mix + (static_cast<uint16_t>(c2.blue) * (255 - mix))) >> 8;
#if COLOR_DEPTH == 32
        ret.alpha = 0xFF;
#endif
        return ret;
    }

    /**
     * @brief Obtains the color based on the RGB color value.
     *
     * @param r8 Indicates the intensity of red.
     * @param g8 Indicates the intensity of green.
     * @param b8 Indicates the intensity of blue.
     *
     * @return Returns the color data generated.
     * @since 1.0
     * @version 1.0
     */
    static ColorType GetColorFromRGB(uint8_t r8, uint8_t g8, uint8_t b8)
    {
        return GetColorFromRGBA(r8, g8, b8, 0xFF);
    }

    /**
     * @brief Obtains the color based on the RGBA color value.
     *
     * @param r8 Indicates the intensity of red.
     * @param g8 Indicates the intensity of green.
     * @param b8 Indicates the intensity of blue.
     * @param alpha Indicates the alpha, that is, how opaque each pixel is.
     *
     * @return Returns the color data generated.
     * @since 1.0
     * @version 1.0
     */
    static ColorType GetColorFromRGBA(uint8_t r8, uint8_t g8, uint8_t b8, uint8_t alpha)
    {
        ColorType rColor;
#if COLOR_DEPTH == 16
        rColor.red = r8 >> 3;  // 3: shift right 3 places
        rColor.blue = b8 >> 3;  // 3: shift right 3 places
        rColor.green = g8 >> 2;  // 2: shift right 2 places
#elif COLOR_DEPTH == 32
        // 24, 16, 8: shift right places
        rColor.full = (alpha << 24) | (r8 << 16) | (g8 << 8) | (b8);
#endif
        return rColor;
    }

    /**
     * @brief Converts color data into the RGBA8888 format.
     *
     * The color data definition varies according to the color depth.
     *
     * @param color Indicates the color data, which is defined by {@link ColorType}.
     * @return Returns the RGBA8888 color data.
     * @since 1.0
     * @version 1.0
     */
    static uint32_t ColorTo32(ColorType color);

    /**
     * @brief Converts color data with the 16-bit color depth into the RGBA8888 format.
     *
     * @param color Indicates the color data with the 16-bit color depth, which is defined by {@link Color16}.
     * @param alpha Indicates the alpha, that is, how opaque each pixel is.
     * @return Returns the RGBA8888 color data.
     * @since 1.0
     * @version 1.0
     */
    static uint32_t ColorTo32(Color16 color, uint8_t alpha);

    /**
     * @brief Converts color data from the RGBA8888 format into the RGB565 format.
     *
     * @param color Indicates the color data with the 32-bit color depth, which is defined by {@link Color32}.
     * @return Returns the RGB565 color data.
     * @since 1.0
     * @version 1.0
     */
    static uint16_t ColorTo16(Color32 color);

    /**
     * @brief Obtains the color data of white.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType White()
    {
        return GetColorFromRGB(0xFF, 0xFF, 0xFF);
    }

    /**
     * @brief Obtains the color data of silver.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Silver()
    {
        return GetColorFromRGB(0xC0, 0xC0, 0xC0);
    }

    /**
     * @brief Obtains the color data of gray.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Gray()
    {
        return GetColorFromRGB(0x80, 0x80, 0x80);
    }

    /**
     * @brief Obtains the color data of black.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Black()
    {
        return GetColorFromRGB(0x00, 0x00, 0x00);
    }

    /**
     * @brief Obtains the color data of red.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Red()
    {
        return GetColorFromRGB(0xFF, 0x00, 0x00);
    }

    /**
     * @brief Obtains the color data of maroon.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Maroon()
    {
        return GetColorFromRGB(0x80, 0x00, 0x00);
    }

    /**
     * @brief Obtains the color data of yellow.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Yellow()
    {
        return GetColorFromRGB(0xFF, 0xFF, 0x00);
    }

    /**
     * @brief Obtains the color data of olive.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Olive()
    {
        return GetColorFromRGB(0x80, 0x80, 0x00);
    }

    /**
     * @brief Obtains the color data of lime.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Lime()
    {
        return GetColorFromRGB(0x00, 0xFF, 0x00);
    }

    /**
     * @brief Obtains the color data of green.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Green()
    {
        return GetColorFromRGB(0x00, 0xFF, 0x00);
    }

    /**
     * @brief Obtains the color data of cyan.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Cyan()
    {
        return GetColorFromRGB(0x00, 0xFF, 0xFF);
    }

    /**
     * @brief Obtains the color data of aqua.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Aqua()
    {
        return GetColorFromRGB(0x00, 0xFF, 0xFF);
    }

    /**
     * @brief Obtains the color data of teal.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Teal()
    {
        return GetColorFromRGB(0x00, 0x80, 0x80);
    }

    /**
     * @brief Obtains the color data of blue.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Blue()
    {
        return GetColorFromRGB(0x00, 0x00, 0xFF);
    }

    /**
     * @brief Obtains the color data of navy.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Navy()
    {
        return GetColorFromRGB(0x00, 0x00, 0x80);
    }

    /**
     * @brief Obtains the color data of magenta.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Magenta()
    {
        return GetColorFromRGB(0xFF, 0x00, 0xFF);
    }

    /**
     * @brief Obtains the color data of purple.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Purple()
    {
        return GetColorFromRGB(0x80, 0x00, 0x80);
    }

    /**
     * @brief Obtains the color data of orange.
     *
     * @return Returns the color data.
     * @since 1.0
     * @version 1.0
     */
    static ColorType Orange()
    {
        return GetColorFromRGB(0xFF, 0xA5, 0x00);
    }
};
} // namespace OHOS
#endif // GRAPHIC_LITE_COLOR_H
