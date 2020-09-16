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

#include "graphic_math.h"

namespace OHOS {
static float g_sinValues[] = {
    0.000000, 0.017452, 0.034899, 0.052336, 0.069756, 0.087156, 0.104528, 0.121869, 0.139173, 0.156434, 0.173648,
    0.190809, 0.207912, 0.224951, 0.241922, 0.258819, 0.275637, 0.292372, 0.309017, 0.325568, 0.342020, 0.358368,
    0.374607, 0.390731, 0.406737, 0.422618, 0.438371, 0.453990, 0.469472, 0.484810, 0.500000, 0.515038, 0.529919,
    0.544639, 0.559193, 0.573576, 0.587785, 0.601815, 0.615661, 0.629320, 0.642788, 0.656059, 0.669131, 0.681998,
    0.694658, 0.707107, 0.719340, 0.731354, 0.743145, 0.754710, 0.766044, 0.777146, 0.788011, 0.798636, 0.809017,
    0.819152, 0.829038, 0.838671, 0.848048, 0.857167, 0.866025, 0.874620, 0.882948, 0.891007, 0.898794, 0.906308,
    0.913545, 0.920505, 0.927184, 0.933580, 0.939693, 0.945519, 0.951057, 0.956305, 0.961262, 0.965926, 0.970296,
    0.974370, 0.978148, 0.981627, 0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.998630,
    0.999391, 0.999848, 1.000000
};

float Sin(int16_t angle)
{
    angle = angle % CIRCLE_IN_DEGREE;
    if (angle < 0) {
        angle = CIRCLE_IN_DEGREE + angle;
    }

    if (angle <= QUARTER_IN_DEGREE) {
        return g_sinValues[angle];
    } else if (angle <= SEMICIRCLE_IN_DEGREE) {
        return g_sinValues[SEMICIRCLE_IN_DEGREE - angle];
    } else if (angle <= THREE_QUARTER_IN_DEGREE) {
        return -g_sinValues[angle - SEMICIRCLE_IN_DEGREE];
    } else {
        return -g_sinValues[CIRCLE_IN_DEGREE - angle];
    }
}

/* arctan(x) = x - p3 * x^3 + p5 * x^5 - p7 * x^7 */
uint16_t FastAtan2(int16_t x, int16_t y)
{
    if (x == 0 && y == 0) {
        return 0;
    }

    int16_t absX = MATH_ABS(x);
    int16_t absY = MATH_ABS(y);
    float t;
    float t2;
    uint16_t angle;
    if (absX <= absY) {
        t = static_cast<float>(absX) / absY;
        t2 = t * t;
        angle = static_cast<uint16_t>(t * (1 + t2 * (ATAN2_P3 + t2 * (ATAN2_P5 + t2 * ATAN2_P7))) * RADIAN_TO_ANGLE);
    } else {
        t = static_cast<float>(absY) / absX;
        t2 = t * t;
        angle = QUARTER_IN_DEGREE -
            static_cast<uint16_t>(t * (1 + t2 * (ATAN2_P3 + t2 * (ATAN2_P5 + t2 * ATAN2_P7))) * RADIAN_TO_ANGLE);
    }

    if (y < 0) {
        if (x < 0) {
            angle = SEMICIRCLE_IN_DEGREE + angle;
        } else {
            angle = SEMICIRCLE_IN_DEGREE - angle;
        }
    } else if (x < 0) {
        angle = CIRCLE_IN_DEGREE - angle;
    }

    return angle;
}

uint32_t Sqrt(uint32_t num)
{
    uint32_t root = 0;
    uint32_t bit = 1 << 30; // 30: The second bit is set.

    while (bit > num) {
        bit >>= 2; // 2: shift right 2 places at a time
    }

    while (bit != 0) {
        if (num >= root + bit) {
            num -= root + bit;
            root = (root >> 1) + bit; // 1: shift right 1 place at a time
        } else {
            root >>= 1; // 1: shift right 1 place at a time
        }
        bit >>= 2; // 2: shift right 2 places at a time
    }
    return root;
}
} // namespace OHOS