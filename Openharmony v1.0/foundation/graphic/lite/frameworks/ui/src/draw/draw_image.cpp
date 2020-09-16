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

#include "draw/draw_image.h"

#include "color.h"
#include "graphic_log.h"
#include "imgdecode/cache_manager.h"

namespace OHOS {
void DrawImage::DrawCommon(const Rect& coords, const Rect& mask,
    const ImageInfo* img, const Style& style, uint8_t opaScale)
{
    if (img == nullptr) {
        return;
    }
    OpacityType opa = (opaScale == OPA_OPAQUE) ? style.imageOpa_ :
        ((static_cast<uint16_t>(style.imageOpa_) * opaScale) >> SHIFT_8);

    /* 3 : when single pixel change bit to byte, the buffer should divide by 8, equal to shift right 3 bits. */
    uint8_t pxByteSize = DrawUtils::GetPxSizeByImageInfo(*img) >> 3;
    DrawUtils::GetInstance()->DrawImage(coords, mask, img->data, opa, pxByteSize);
}

void DrawImage::DrawCommon(const Rect& coords, const Rect& mask,
    const char* path, const Style& style, uint8_t opaScale)
{
    if (path == nullptr) {
        return;
    }
    OpacityType opa = (opaScale == OPA_OPAQUE) ? style.imageOpa_ :
        ((static_cast<uint16_t>(style.imageOpa_) * opaScale) >> SHIFT_8);

    CacheEntry entry;
    if (CacheManager::GetInstance().Open(path, style, entry) != RetCode::OK) {
        return;
    }

    /* 3 : when single pixel change bit to byte, the buffer should divide by 8, equal to shift right 3 bits. */
    uint8_t pxByteSize = DrawUtils::GetPxSizeByImageInfo(entry.GetImageInfo()) >> 3;
    if (entry.InCache()) {
        DrawUtils::GetInstance()->DrawImage(coords, mask, entry.GetImgData(), opa, pxByteSize);
    } else {
        Rect valid = coords;
        if (!valid.Intersect(valid, mask)) {
            return;
        }

        int16_t width = valid.GetWidth();
        if (width <= 0) {
            return;
        }
        uint8_t* buf = static_cast<uint8_t*>(UIMalloc(static_cast<uint32_t>(width) * ((COLOR_DEPTH >> SHIFT_3) + 1)));
        if (buf == nullptr) {
            return;
        }

        Rect line = valid;
        line.SetHeight(1);
        Point start;
        start.x = valid.GetLeft() - coords.GetLeft();
        start.y = valid.GetTop() - coords.GetTop();
        int16_t row;
        for (row = valid.GetTop(); row <= valid.GetBottom(); row++) {
            if (entry.ReadLine(start, width, buf) != RetCode::OK) {
                CacheManager::GetInstance().Close(path);
                UIFree(buf);
                return;
            }
            DrawUtils::GetInstance()->DrawImage(line, mask, buf, opa, pxByteSize);
            line.SetTop(line.GetTop() + 1);
            line.SetBottom(line.GetBottom() + 1);
            start.y++;
        }
        UIFree(buf);
    }
}
} // namespace OHOS
