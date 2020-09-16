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

#ifndef UI_DYNAMIC_FONT_H
#define UI_DYNAMIC_FONT_H

#include "font/ui_font_header.h"

namespace OHOS {
constexpr uint8_t RADIX_TREE_BITS = 4;
constexpr uint8_t RADIX_SHIFT_START = 32 - RADIX_TREE_BITS;
constexpr uint32_t RADIX_TREE_SLOT_NUM = 1 << RADIX_TREE_BITS;
constexpr uint32_t RADIX_TREE_MASK = RADIX_TREE_SLOT_NUM - 1;

constexpr uint8_t FONT_HASH_SHIFT = 3;
constexpr uint8_t FONT_HASH_NR = 1 << FONT_HASH_SHIFT;
constexpr uint32_t FONT_HASH_MASK = FONT_HASH_NR - 1;
constexpr uint8_t UNICODE_HASH_SHIFT = 6;
constexpr uint8_t UNICODE_HASH_NR = 1 << UNICODE_HASH_SHIFT;
constexpr uint32_t UNICODE_HASH_MASK = UNICODE_HASH_NR - 1;
constexpr uint8_t NODE_HASH_SHIFT = 4;
constexpr uint8_t NODE_HASH_NR = 1 << NODE_HASH_SHIFT;

class DynamicFont {
public:
    using CacheType = GlyphNode[FONT_HASH_NR][UNICODE_HASH_NR][NODE_HASH_NR];
    using CacheState = uint8_t[FONT_HASH_NR][UNICODE_HASH_NR];

    struct IndexNode {
        uint16_t stubs[RADIX_TREE_SLOT_NUM];
    };

    DynamicFont();

    DynamicFont(const DynamicFont&) = delete;

    DynamicFont& operator=(const DynamicFont&) = delete;

    ~DynamicFont();

    int32_t GetRamUsedLen() const;

    int8_t GetFontVersion(char* version, uint8_t len) const;

    int16_t GetFontHeight() const;

    int16_t GetFontWidth(uint32_t unicode);

    const struct FontHeader* GetCurrentFontHeader() const;

    const struct GlyphNode* GetGlyphNode(uint32_t unicode);

    int8_t GetBitmap(uint32_t unicode, uint8_t* bitmap);

    int8_t SetRamBuffer(uintptr_t ramAddr);

    int8_t SetFile(int32_t fp, uint32_t start);

    int8_t SetCurrentFontId(uint8_t fontId);

private:
    int8_t GlyphNodeCacheInit();
    struct GlyphNode* GetNodeFromCache(uint32_t unicode);
    struct GlyphNode* GetNodeCacheSpace(uint32_t unicode);
    struct GlyphNode* GetNodeFromFile(uint32_t unicode);
    uint32_t AlignUp(uint32_t addr, uint32_t align)
    {
        return (((addr + (1 << align)) >> align) << align);
    }

    struct BinHeader binHeader_;
    uint8_t fontNum_;
    uint32_t start_;
    uint32_t fontHeaderSectionStart_;
    uint32_t fontIndexSectionStart_;
    uint32_t curFontIndexSectionStart_;
    uint32_t glyphNodeSectionStart_;
    uint32_t curGlyphNodeSectionStart_;
    uint32_t bitMapSectionStart_;
    uint32_t curBitMapSectionStart_;

    uint8_t* ramAddr_;
    uint32_t ramUsedLen_;
    struct FontHeader* fontHeaderCache_;
    uint8_t* indexCache_;
    uint8_t* curIndexCache_;

    CacheType* nodeCache_;
    CacheState* cacheStatus_;

    int32_t fp_;
    uint8_t fontId_;
    struct FontHeader* curFontHeader_;
    struct GlyphNode* curGlyphNode_;
    uint16_t fontIdx_;

    bool isRamSet_;
    bool isFileSet_;
    bool isFontIdSet_;
};
} // namespace OHOS
#endif /* UI_DYNAMIC_FONT_H */
