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

#ifndef UI_FONT_VECTOR_H
#define UI_FONT_VECTOR_H

#include "graphic_config.h"
#if ENABLE_VECTOR_FONT
#include "ft2build.h"
#include "freetype/freetype.h"
#include "font/ui_base_font.h"
#include "font/ui_font_cache.h"
#include "font/ui_text_manager.h"
#include <memory>

namespace OHOS {
class UIFontVector : public UIBaseFont {
public:
    UIFontVector();

    ~UIFontVector();
    UIFontVector(const UIFontVector&) = delete;
    UIFontVector& operator=(const UIFontVector&) noexcept = delete;

    bool IsVectorFont() const;
    int8_t SetPsramMemory(uintptr_t psramAddr, uint32_t psramLen);
    int8_t SetFontPath(const char* dpath);
    int8_t SetCurrentFontId(uint8_t fontId, uint8_t size = 0);
    uint16_t GetHeight();
    uint8_t GetFontId(const char* ttfName, uint8_t size = 0) const;
    uint16_t GetWidth(uint32_t unicode, uint8_t shapingId);
    uint8_t* GetBitmap(uint32_t unicode, GlyphNode& glyphNode, uint8_t shapingFont);
    int8_t GetCurrentFontHeader(FontHeader& fontHeader);
    int8_t GetGlyphNode(uint32_t unicode, GlyphNode& glyphNode, bool isGlyph = false);
    uint8_t GetFontWeight(uint8_t fontId) const;
private:
    const void SetFace(FT_Face ftface, uint32_t unicode) const;
    uint32_t GetKey(uint8_t fontId, uint32_t size);
    static constexpr uint8_t FONT_BPP_8 = 8;
    const char* fontInfo_[FONT_ID_MAX + 1] = {0};
    std::string ttfDir_;
    FT_Library ftLibrary_;
    FT_Face ftFaces_[FONT_ID_MAX + 1] = {0};
    bool freeTypeInited_;
    uint32_t key_ = 0;

    uint8_t RegisterFontInfo(const char* ttfName);
    uint8_t UnregisterFontInfo(const char* ttfName);
    const char* GetFontTtfName(uint8_t fontId) const;
    UIFontCache* bitmapCache_;
};
} // namespace OHOS
#endif /* ENABLE_VECTOR_FONT */
#endif /* UI_FONT_VECTOR_H */
