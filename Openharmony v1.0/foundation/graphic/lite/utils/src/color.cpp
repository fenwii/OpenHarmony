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

#include "color.h"

namespace OHOS {
uint32_t Color::ColorTo32(ColorType color)
{
#if COLOR_DEPTH == 16
    Color32 ret;
    ret.red = color.red << 3;     /* (2^8 - 1)/(2^5 - 1) = 255/31 = 8 */
    ret.green = color.green << 2; /* (2^8 - 1)/(2^6 - 1) = 255/63 = 4 */
    ret.blue = color.blue << 3;   /* (2^8 - 1)/(2^5 - 1) = 255/31 = 8 */
    ret.alpha = 0xFF;
    return ret.full;
#elif COLOR_DEPTH == 32
    return color.full;
#endif
}

uint32_t Color::ColorTo32(Color16 color, uint8_t alpha)
{
    Color32 ret;
    /*
     * when 16-bitmap image is tansformed to 32-bitmap,
     * R should shift left 3 bits,
     * G should shift left 2 bits,
     * B should shift left 3 bits,
     */
    ret.red = color.red << 3;     /* (2^8 - 1)/(2^5 - 1) = 255/31 = 8 */
    ret.green = color.green << 2; /* (2^8 - 1)/(2^6 - 1) = 255/63 = 4 */
    ret.blue = color.blue << 3;   /* (2^8 - 1)/(2^5 - 1) = 255/31 = 8 */
    ret.alpha = alpha;
    return ret.full;
}

uint16_t Color::ColorTo16(Color32 color)
{
    /*
     * when 32-bitmap image is tansformed to 16-bitmap,
     * R should shift right 3 bits,
     * G should shift right 2 bits,
     * B should shift right 3 bits,
     */
    Color16 rColor;
    rColor.red = color.red >> 3;
    rColor.green = color.green >> 2;
    rColor.blue = color.blue >> 3;
    return rColor.full;
}
} // namespace OHOS