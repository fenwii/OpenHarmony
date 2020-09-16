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

#ifndef UI_FONT_H
#define UI_FONT_H

#include <cstring>
#include <string>
#include "font/ui_font_header.h"

namespace OHOS {
class UIBaseFont;

class UIFont {
public:
    UIFont(const UIFont &) = delete;
    UIFont& operator=(const UIFont &) = delete;

    /**
     * @brief Get the Instance object
     *
     * @return UIFont*
     */
    static UIFont *GetInstance();

    /**
     * @brief Indicates whether the current font library is a vector font library.
     * @return uint8_t: 0 BitmapFont  1 VectorFont
     */
    bool IsVectorFont() const;

    /**
     * @brief Get the ttfId Property
     * @param fontId
     * @return uint8_t: fontWeight
     */
    uint8_t GetFontWeight(uint8_t fontId) const;

    /**
     * @brief Set the cache start address
     *
     * @param psramAddr
     * @param psramLen
     * @return int8_t
     */
    int8_t SetPsramMemory(uintptr_t psramAddr, uint32_t psramLen);

    /**
     * @brief Set the Font Path
     *
     * @param dpath
     * @param spath
     * @return int8_t
     */
    int8_t SetFontPath(const char *dPath);

    /**
     * @brief Set font id
     *
     * @param fontId
     * @param size
     * @return int8_t
     */
    int8_t SetCurrentFontId(uint8_t fontId, uint8_t size = 0);

    /**
     * @brief Get height for specific font
     *
     * @return uint16_t
     */
    uint16_t GetHeight();

    /**
     * @brief Get current font id
     *
     * @return uint8_t
     */
    uint8_t GetCurrentFontId() const;

    /**
     * @brief Get font id
     *
     * @param name
     * @param size
     * @return uint8_t
     */
    uint8_t GetFontId(const char *name, uint8_t size = 0);

    /**
     * @brief Get width of the letter
     *
     * @param unicode: [in] unicode or glyph index according to isGlyph param
     * @param shapingId: [in]
     * @return uint16_t: the letter width
     */
    uint16_t GetWidth(uint32_t unicode, uint8_t shapingId);

    /**
     * @brief Get bitmap for specific unicode
     *
     * @param unicode
     * @return uint8_t*
     */
    uint8_t *GetBitmap(uint32_t unicode, GlyphNode& glyphNode, uint8_t shapingFont);

    /**
     * @brief Get font header
     *
     * @param fontHeader
     * @return int8_t
     */
    int8_t GetCurrentFontHeader(FontHeader &fontHeader);

    /**
     * @brief Get the glyph node
     *
     * @param unicode
     * @param glyphNode
     * @return int8_t
     */
    int8_t GetGlyphNode(uint32_t unicode, GlyphNode &glyphNode, bool isGlyph = false);

    uint8_t RegisterFontInfo(const char* ttfName);

    uint8_t UnregisterFontInfo(const char* ttfName);

private:
    UIBaseFont *pInstance_;
    /**
     * @brief Construct a new UIFont object
     *
     */
    UIFont();

    /**
     * @brief Destroy the UIFont object
     *
     */
    ~UIFont();
};
}
#endif  /* UI_FONT_H */