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
 * @file easing_equation.h
 *
 * @brief Defines the attributes and functions of the animation easing module.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_EASING_EQUATION_H
#define GRAPHIC_LITE_EASING_EQUATION_H

#include <cstdint>
#include "heap_base.h"

namespace OHOS {
/**
 * @brief Calculates the value for the current time of an animation.
 *
 * @param startPos     Indicates the start value of this animation.
 * @param endPos       Indicates the end value of this animation.
 * @param curTime      Indicates the current time of this animation.
 * @param durationTime Indicates the total duration of this animation.
 *
 * @brief Returns the value for the current time.
 */
typedef int16_t(*EasingFunc)(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

/**
 * @brief Defines functions for specifying the velocity of an animation.
 *
 * @since 1.0
 * @version 1.0
 */
class EasingEquation : public HeapBase {
public:
    /**
     * @brief Sets the parameter <b>s</b> in the equation <b>(s+1)*t^3 - s*t^2</b> for a back easing.
     *
     * A larger <b>s</b> indicates a larger degree of overshoot. The default value is 1.7. You are advised to set
     * this parameter to a value ranging from 1 to 4. The setting takes effect for all the back-ease animations.
     *
     * @param overshoot Indicates the overshoot <b>s</b> in the equation to set.
     * @see BackEaseIn | BackEaseOut | BackEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static void SetBackOvershoot(double overshoot);

    /**
     * @brief Eases in with an overshoot.
     *
     * <b>(s+1)*t^3 - s*t^2</b> is the equation for a back easing.
     * The animation moves back slightly at the beginning and then accelerates towards the end.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see SetBackOvershoot | BackEaseOut | BackEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t BackEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases out with an overshoot.
     *
     * <b>(s+1)*t^3 - s*t^2</b> is the equation for a back easing.
     * The animation moves towards the end, slightly exceeds it and finally comes back.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see SetBackOvershoot | BackEaseIn | BackEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t BackEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in and then out with an overshoot.
     *
     * <b>(s+1)*t^3 - s*t^2</b> is the equation for a back easing. The animation slightly moves back at the beginning,
     * goes towards the end, slightly exceeds it and finally comes back.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see SetBackOvershoot | BackEaseIn | BackEaseOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t BackEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in shaping like a circular curve.
     *
     * <b>sqrt(1-t^2)</b> is the equation for a circular easing. The animation starts slowly from zero velocity and
     * accelerates fast towards the end. The acceleration change is similar to a circular curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see CircEaseOut | CircEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t CircEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases out shaping like a circular curve.
     *
     * <b>sqrt(1-t^2)</b> is the equation for a circular easing. The animation starts fast and decelerates slowly
     * towards the end. The acceleration change is similar to a circular curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see CircEaseIn | CircEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t CircEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in and then out shaping like a circular curve.
     *
     * <b>sqrt(1-t^2)</b> is the equation for a circular easing. The animation accelerates slowly until halfway and
     * decreases slowly towards the end. The acceleration change is similar to a circular curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see CircEaseIn | CircEaseOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t CircEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in shaping like a cubic curve.
     *
     * <b>t^3</b> is the equation for a cubic easing. The animation starts slowly from zero velocity and accelerates
     * fast towards the end. The acceleration change is similar to a cubic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see CubicEaseOut | CubicEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t CubicEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases out shaping like a cubic curve.
     *
     * <b>t^3</b> is the equation for a cubic easing. The animation starts fast and decelerates slowly
     * towards the end. The acceleration change is similar to a cubic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see CubicEaseIn | CubicEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t CubicEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in and then out shaping like a cubic curve.
     *
     * <b>t^3</b> is the equation for a cubic easing. The animation accelerates slowly until halfway
     * and decelerates slowly towards the end. The acceleration change is similar to a cubic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see CubicEaseIn | CubicEaseOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t CubicEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Displays no linear easing effects.
     *
     * <b>t</b> is the equation for a linear easing. The animation progresses at a constant velocity towards the end.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see LinearEaseIn | LinearEaseOut | LinearEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t LinearEaseNone(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in shaping like a quadratic curve.
     *
     * <b>t^2</b> is the equation for a quadratic easing. The animation starts slowly from zero velocity and
     * accelerates fast towards the end. The acceleration change is similar to a quadratic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see QuadEaseOut | QuadEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t QuadEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases out shaping like a quadratic curve.
     *
     * <b>t^2</b> is the equation for a quadratic easing. The animation starts fast and decelerates slowly
     * towards the end. The acceleration change is similar to a quadratic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see QuadEaseIn | QuadEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t QuadEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in and then out shaping like a quadratic curve.
     *
     * <b>t^2</b> is the equation for a quadratic easing. The animation accelerates slowly until halfway
     * and decelerates slowly towards the end. The acceleration change is similar to a quadratic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see QuadEaseIn | QuadEaseOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t QuadEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in shaping like a quintic curve.
     *
     * <b>t^5</b> is the equation for a quintic easing. The animation starts slowly from zero velocity and
     * accelerates fast towards the end. The acceleration change is similar to a quintic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see QuintEaseOut | QuintEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t QuintEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases out shaping like a quintic curve.
     *
     * <b>t^5</b> is the equation for a quintic easing. The animation starts fast and decelerates slowly
     * towards the end. The acceleration change is similar to a quintic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see QuintEaseIn | QuintEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t QuintEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in and then out shaping like a quintic curve.
     *
     * <b>t^5</b> is the equation for a quintic easing. The animation accelerates slowly until halfway and
     * decelerates slowly towards the end. The acceleration change is similar to a quintic curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see QuintEaseIn | QuintEaseOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t QuintEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in shaping like a sinusoidal curve.
     *
     * <b>sin(t)</b> is the equation for a sinusoidal easing. The animation starts slowly from zero velocity
     * and accelerates fast towards the end. The acceleration change is similar to a sinusoidal curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see SineEaseOut | SineEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t SineEaseIn(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases out shaping like a sinusoidal curve.
     *
     * <b>sin(t)</b> is the equation for a sinusoidal easing. The animation starts fast and decelerates
     * slowly towards the end. The acceleration change is similar to a sinusoidal curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see SineEaseIn | SineEaseInOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t SineEaseOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

    /**
     * @brief Eases in and then out shaping like a sinusoidal curve.
     *
     * <b>sin(t)</b> is the equation for a sinusoidal easing. The animation accelerates slowly until
     * halfway and decelerates slowly towards the end. The acceleration change is similar to a sinusoidal curve.
     *
     * @param startPos     Indicates the start value of this animation.
     * @param endPos       Indicates the end value of this animation.
     * @param curTime      Indicates the current time of this animation.
     * @param durationTime Indicates the total duration of this animation.
     *
     * @return Returns the value for the current time.
     * @see SineEaseIn | SineEaseOut
     * @since 1.0
     * @version 1.0
     */
    static int16_t SineEaseInOut(int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime);

private:
    static constexpr uint16_t INTERPOLATION_RANGE = 1024;
    static constexpr uint16_t INTERPOLATION_RANGE_OFFSET = 10;
    static constexpr uint32_t INTERPOLATION_RANGE_SQUARE = 1048576;
    static constexpr double OVERSHOOT_MAX = 4;
    static constexpr double OVERSHOOT_MIN = 1;
    static double overshoot_;
};
}
#endif
