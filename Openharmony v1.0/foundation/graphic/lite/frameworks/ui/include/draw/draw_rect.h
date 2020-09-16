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

#ifndef GRAPHIC_LITE_DRAW_RECT_H
#define GRAPHIC_LITE_DRAW_RECT_H

#include "components/ui_view.h"

namespace OHOS {
/** @brief Class for drawing rectangle. */
class DrawRect : public HeapBase {
public:
    DrawRect() {};
    ~DrawRect() {};

    static void Draw(const Rect& rect, const Rect& dirtyRect, const Style& style);

private:
    static void DrawRectRadiusWithoutBorder(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectBorderWithoutRadius(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusEqualBorder(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusSmallThanBorder(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusBiggerThanBorder(const Rect& rect, const Rect& dirtyRect, const Style& style);

    static void DrawRectRadiusWithoutBorderCon1(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusWithoutBorderCon2(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusWithoutBorderCon3(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusWithoutBorderCon4(const Rect& rect, const Rect& dirtyRect, const Style& style);

    static void DrawRectRadiusBiggerThanBorderCon1(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusBiggerThanBorderCon2(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusBiggerThanBorderCon3(const Rect& rect, const Rect& dirtyRect, const Style& style);
    static void DrawRectRadiusBiggerThanBorderCon4(const Rect& rect, const Rect& dirtyRect, const Style& style);
};
} // namespace OHOS
#endif // GRAPHIC_LITE_DRAW_RECT_H
