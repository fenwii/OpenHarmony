/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UI_BASE_FONT_H
#define UI_BASE_FONT_H

#include "graphic_config.h"
#include "font/ui_dynamic_font.h"
#include "font/ui_font_cache.h"
#include "font/ui_text_manager.h"
#include <memory>

namespace OHOS {
class UIBaseFont {
public:
    UIBaseFont(const UIBaseFont&) = delete;
    UIBaseFont& operator=(const UIBaseFont&) = delete;
    UIBaseFont(UIBaseFont&&) noexcept = delete;
    UIBaseFont& operator=(UIBaseFont&&) noexcept = delete;

    virtual bool IsVectorFont() const = 0;

    virtual int8_t SetPsramMemory(uintptr_t psramAddr, uint32_t psramLen) = 0;

    /**
     * @brief Set the Font Path
     *
     * @param dpath
     * @param spath
     * @return int8_t
     */
    virtual int8_t SetFontPath(const char* dpath) = 0;

    virtual int8_t SetCurrentFontId(uint8_t fontId, uint8_t size) = 0;

    virtual uint16_t GetHeight() = 0;

    uint8_t GetCurrentFontId() const;

    virtual uint8_t GetFontId(const char* ttfName, uint8_t size) const = 0;

    virtual uint16_t GetWidth(uint32_t unicode, uint8_t shapingId) = 0;

    virtual uint8_t* GetBitmap(uint32_t unicode, GlyphNode& glyphNode, uint8_t shapingFont) = 0;

    virtual int8_t GetCurrentFontHeader(FontHeader& fontHeader) = 0;

    virtual int8_t GetGlyphNode(uint32_t unicode, GlyphNode& glyphNode, bool isGlyph) = 0;

    virtual uint8_t GetFontWeight(uint8_t fontId) const = 0;
    virtual uint8_t RegisterFontInfo(const char* ttfName) = 0;
    virtual uint8_t UnregisterFontInfo(const char* ttfName) = 0;

protected:
    static constexpr uint8_t FONT_INVAILD_TTF_ID = 0xFF;
    static constexpr uint8_t FONT_ID_MAX = 0xFF;
    static constexpr uint8_t TTF_NAME_LEN_MAX = 128;
    uint8_t fontId_;
    uintptr_t ramAddr_;
    uint32_t ramLen_;
    UIBaseFont() : fontId_(0), ramAddr_(0), ramLen_(0) {}
    virtual ~UIBaseFont() {}
};
} // namespace OHOS
#endif /* UI_BASE_FONT_H */