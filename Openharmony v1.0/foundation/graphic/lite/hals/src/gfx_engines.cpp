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

#include "gfx_engines.h"

#include "graphic_log.h"

namespace OHOS {
struct {
    ImagePixelFormat srcColorFmt;
    PixelFormat dstColorFmt;
} g_fmtMapTable[] = {
    {IMAGE_PIXEL_FORMAT_RGB565, PIXEL_FMT_RGB_565},
    {IMAGE_PIXEL_FORMAT_ARGB1555, PIXEL_FMT_RGBA_5551},
    {IMAGE_PIXEL_FORMAT_RGB888, PIXEL_FMT_RGB_888},
    {IMAGE_PIXEL_FORMAT_ARGB8888, PIXEL_FMT_RGBA_8888},
};

static bool ConvertFormat(const ImagePixelFormat& srcColorFmt, PixelFormat& dstColorFmt)
{
    int32_t i;
    int32_t len = sizeof(g_fmtMapTable) / sizeof(g_fmtMapTable[0]);
    for (i = 0; i < len; i++) {
        if (g_fmtMapTable[i].srcColorFmt == srcColorFmt) {
            dstColorFmt = g_fmtMapTable[i].dstColorFmt;
            return true;
        }
    }
    return false;
}

static bool Convert2ISurface(const LiteSurfaceData& liteSurfaceData, ISurface& iSurface)
{
    if (ConvertFormat(liteSurfaceData.pixelFormat, iSurface.enColorFmt) == false) {
        GRAPHIC_LOGE("unsupport color format!");
        return false;
    }

    uintptr_t phyAddr = reinterpret_cast<uintptr_t>(liteSurfaceData.phyAddr);
    iSurface.phyAddr = phyAddr;
    iSurface.height = liteSurfaceData.height;
    iSurface.width = liteSurfaceData.width;
    iSurface.stride = liteSurfaceData.stride;
    iSurface.clutPhyAddr = 0;
    iSurface.bYCbCrClut = false;
    iSurface.bAlphaMax255 = true;
    iSurface.bAlphaExt1555 = false;
    iSurface.alpha0 = 0;
    iSurface.alpha1 = OPA_OPAQUE;
    return true;
}

static void Convert2IRect(const Rect& rect, IRect& iRect)
{
    iRect.x = rect.GetLeft();
    iRect.y = rect.GetTop();
    iRect.w = rect.GetWidth();
    iRect.h = rect.GetHeight();
}

bool GfxEngines::InitDriver()
{
    if (GfxInitialize(&gfxFuncs_) == DISPLAY_SUCCESS) {
        if (gfxFuncs_ == nullptr) {
            GRAPHIC_LOGE("gfxFuncs_ is null!");
            return false;
        }
        if (gfxFuncs_->InitGfx == nullptr) {
            GRAPHIC_LOGE("InitGfx is null!");
            return false;
        }
        if (gfxFuncs_->InitGfx() != DISPLAY_SUCCESS) {
            GRAPHIC_LOGE("InitGfx failed!");
            return false;
        }
        return true;
    }
    return false;
}

void GfxEngines::CloseDriver()
{
    if (gfxFuncs_ == nullptr) {
        GRAPHIC_LOGE("gfxFuncs_ is null!");
        return;
    }
    if (gfxFuncs_->DeinitGfx != nullptr) {
        if (gfxFuncs_->DeinitGfx() != DISPLAY_SUCCESS) {
            GRAPHIC_LOGE("DeinitGfx failed!");
        }
    }
    GfxUninitialize(gfxFuncs_);
    gfxFuncs_ = nullptr;
}

bool GfxEngines::GfxFillArea(const LiteSurfaceData& dstSurfaceData,
                             const Rect& fillArea,
                             const ColorType& color,
                             const OpacityType& opa)
{
    if (gfxFuncs_ == nullptr || dstSurfaceData.phyAddr == nullptr) {
        return false;
    }
    ISurface surface = {};
    if (Convert2ISurface(dstSurfaceData, surface) == false) {
        return false;
    }
    IRect rect = {};
    Convert2IRect(fillArea, rect);
    GfxOpt opt = {};
    opt.enAlpha = true;
    opt.globalAlpha = opa;
    if (gfxFuncs_->FillRect(&surface, &rect, color.full, &opt) == DISPLAY_FAILURE) {
        GRAPHIC_LOGE("fill rect failed!");
        return false;
    }
    return true;
}

bool GfxEngines::GfxBlit(const LiteSurfaceData& srcSurfaceData,
                         const Rect& srcRect,
                         const LiteSurfaceData& dstSurfaceData,
                         int16_t x,
                         int16_t y)
{
    if (gfxFuncs_ == nullptr || srcSurfaceData.phyAddr == nullptr || dstSurfaceData.phyAddr == nullptr) {
        return false;
    }
    ISurface srcSurface = {};
    ISurface dstSurface = {};
    if (Convert2ISurface(srcSurfaceData, srcSurface) == false) {
        return false;
    }
    if (Convert2ISurface(dstSurfaceData, dstSurface) == false) {
        return false;
    }
    IRect srcIRect = {};
    Convert2IRect(srcRect, srcIRect);
    IRect dstIRect = {x, y, srcRect.GetWidth(), srcRect.GetHeight()};
    if (gfxFuncs_->Blit(&srcSurface, &srcIRect, &dstSurface, &dstIRect) == DISPLAY_FAILURE) {
        GRAPHIC_LOGE("blit failed!");
        return false;
    }
    return true;
}
} // namespace OHOS
