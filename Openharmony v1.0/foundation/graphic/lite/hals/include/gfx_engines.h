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

#ifndef GRAPHIC_LITE_GFX_ENGINES_H
#define GRAPHIC_LITE_GFX_ENGINES_H

#include "color.h"
#include "common/lite_wm_type.h"
#include "display_gfx.h"
#include "display_type.h"
#include "geometry2d.h"

namespace OHOS {
class GfxEngines {
public:
    static GfxEngines* GetInstance()
    {
        static GfxEngines instance;
        return &instance;
    }

    bool InitDriver();
    void CloseDriver();

    bool GfxFillArea(const LiteSurfaceData& dstSurfaceData,
                     const Rect& fillArea,
                     const ColorType& color,
                     const OpacityType& opa);

    bool GfxBlit(const LiteSurfaceData& srcSurfaceData,
                 const Rect& srcRect,
                 const LiteSurfaceData& dstSurfaceData,
                 int16_t x,
                 int16_t y);
private:
    GfxEngines() : gfxFuncs_(nullptr) {}
    virtual ~GfxEngines() {}
    GfxFuncs* gfxFuncs_;
};
} // namespace OHOS
#endif
