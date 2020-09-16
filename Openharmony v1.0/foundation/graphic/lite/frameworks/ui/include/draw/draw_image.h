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

#ifndef GRAPHIC_LITE_DRAW_IMAGE_H
#define GRAPHIC_LITE_DRAW_IMAGE_H

#include <cstdint>
#include <stdio.h>
#include "components/ui_view.h"
#include "draw_utils.h"
#include "geometry2d.h"

namespace OHOS {
class CacheEntry;

class DrawImage : public HeapBase {
public:
    DrawImage() {}
    ~DrawImage() {}

    static void DrawCommon(const Rect& coords, const Rect& mask,
        const ImageInfo* img, const Style& style, uint8_t opaScale);

    static void DrawCommon(const Rect& coords, const Rect& mask,
        const char* path, const Style& style, uint8_t opaScale);
};
} // namespace OHOS

#endif // GRAPHIC_LITE_DRAW_IMAGE_H
