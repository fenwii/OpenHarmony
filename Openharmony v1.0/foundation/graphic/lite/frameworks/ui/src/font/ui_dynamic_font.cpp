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

#include "font/ui_dynamic_font.h"
#include <cstring>
#include <string>
#include "file.h"

namespace OHOS {
DynamicFont::DynamicFont()
    : fontNum_(0),
      start_(0),
      fontHeaderSectionStart_(0),
      fontIndexSectionStart_(0),
      curFontIndexSectionStart_(0),
      glyphNodeSectionStart_(0),
      curGlyphNodeSectionStart_(0),
      bitMapSectionStart_(0),
      curBitMapSectionStart_(0),
      ramAddr_(nullptr),
      ramUsedLen_(0),
      fp_(-1)
{
    binHeader_ = {{0}};

    fontHeaderCache_ = nullptr;
    indexCache_ = nullptr;
    curIndexCache_ = nullptr;
    nodeCache_ = nullptr;
    cacheStatus_ = nullptr;
    curFontHeader_ = nullptr;
    curGlyphNode_ = nullptr;

    fontId_ = GetTotalFontId();
    fontIdx_ = 0;

    isRamSet_ = false;
    isFileSet_ = false;
    isFontIdSet_ = false;
}
DynamicFont::~DynamicFont() {}

int8_t DynamicFont::GlyphNodeCacheInit()
{
    int32_t ret;
    uint32_t size = 0;
    for (int i = 0; i < fontNum_; i++) {
        size += fontHeaderCache_[i].indexLen;
    }

    indexCache_ = ramAddr_ + ramUsedLen_;
    ramUsedLen_ += size;
    /* align up to 4 byte, power of 2 */
    ramUsedLen_ = AlignUp(ramUsedLen_, 2);

    ret = FileRead(fp_, indexCache_, size);
    if (ret != size) {
        return INVALID_RET_VALUE;
    }

    cacheStatus_ = reinterpret_cast<CacheState*>(ramAddr_ + ramUsedLen_);
    ramUsedLen_ += sizeof(CacheState);
    /* align up to 4 byte, power of 2 */
    ramUsedLen_ = AlignUp(ramUsedLen_, 2);
    for (int font = 0; font < FONT_HASH_NR; font++) {
        for (int uc = 0; uc < UNICODE_HASH_NR; uc++) {
            (*cacheStatus_)[font][uc] = 0;
        }
    }

    nodeCache_ = reinterpret_cast<CacheType*>(ramAddr_ + ramUsedLen_);
    ramUsedLen_ += sizeof(CacheType);
    /* align up to 4 byte, power of 2 */
    ramUsedLen_ = AlignUp(ramUsedLen_, 2);
    for (int font = 0; font < FONT_HASH_NR; font++) {
        for (int uc = 0; uc < UNICODE_HASH_NR; uc++) {
            for (int node = 0; node < NODE_HASH_NR; node++) {
                (*nodeCache_)[font][uc][node].unicode = 0;
            }
        }
    }

    return RET_VALUE_OK;
}

struct GlyphNode* DynamicFont::GetNodeFromCache(uint32_t unicode)
{
    struct GlyphNode* node = nullptr;

    uint8_t font = fontId_ & FONT_HASH_MASK;
    uint8_t uc = unicode & UNICODE_HASH_MASK;
    for (uint8_t i = 0; i < NODE_HASH_NR; i++) {
        struct GlyphNode* p = &((*nodeCache_)[font][uc][i]);
        if (p->unicode == unicode && p->reserve == fontId_) {
            node = p;
            break;
        }
    }
    return node;
}

struct GlyphNode* DynamicFont::GetNodeCacheSpace(uint32_t unicode)
{
    uint8_t font, uc, i;
    struct GlyphNode* node = nullptr;

    font = fontId_ & FONT_HASH_MASK;
    uc = unicode & UNICODE_HASH_MASK;
    i = (*cacheStatus_)[font][uc];
    node = &((*nodeCache_)[font][uc][i]);

    i++;
    if (i >= NODE_HASH_NR) {
        i = 0;
    }
    (*cacheStatus_)[font][uc] = i;

    return node;
}

struct GlyphNode* DynamicFont::GetNodeFromFile(uint32_t unicode)
{
    uint16_t idx = 0;
    uint8_t key;
    uint32_t offset;

    for (int i = RADIX_SHIFT_START; i >= 0; i -= RADIX_TREE_BITS) {
        offset = idx * sizeof(struct IndexNode);
        key = static_cast<uint8_t>((unicode >> static_cast<uint8_t>(i)) & RADIX_TREE_MASK);
        offset += key * sizeof(uint16_t);
        idx = *(reinterpret_cast<uint16_t*>(curIndexCache_ + offset));
        if (idx == 0) {
            return nullptr;
        }
    }

    int ret;
    offset = curGlyphNodeSectionStart_ + (idx - 1) * sizeof(struct GlyphNode);
    ret = FileSeek(fp_, offset, SEEK_SET);
    if (ret < 0) {
        return nullptr;
    }
    struct GlyphNode* node = GetNodeCacheSpace(unicode);
    ret = FileRead(fp_, node, sizeof(struct GlyphNode));
    if (ret < 0) {
        return nullptr;
    }

    return node;
}

int8_t DynamicFont::SetRamBuffer(uintptr_t ramAddr)
{
    ramAddr_ = reinterpret_cast<uint8_t*>(ramAddr);
    isRamSet_ = true;

    return 0;
}

int8_t DynamicFont::SetFile(int32_t fp, uint32_t start)
{
    int ret;

    if (!isRamSet_) {
        return INVALID_RET_VALUE;
    }

    fp_ = fp;
    start_ = start;
    ret = FileSeek(fp_, start_, SEEK_SET);
    if (ret != start) {
        return INVALID_RET_VALUE;
    }
    ret = FileRead(fp_, &binHeader_, sizeof(binHeader_));
    if (ret != sizeof(binHeader_)) {
        return INVALID_RET_VALUE;
    }
    if (strncmp(binHeader_.fontMagic, FONT_MAGIC_NUMBER, FONT_MAGIC_NUM_LEN) != 0) {
        return INVALID_RET_VALUE;
    }
    if (binHeader_.fontNum > GetTotalFontId()) {
        return INVALID_RET_VALUE;
    }

    fontNum_ = binHeader_.fontNum;
    fontHeaderSectionStart_ = start_ + sizeof(binHeader_);
    int size = sizeof(struct FontHeader) * fontNum_;
    fontIndexSectionStart_ = fontHeaderSectionStart_ + size;

    fontHeaderCache_ = reinterpret_cast<FontHeader*>(ramAddr_);
    /* align up to 4 byte, power of 2 */
    ramUsedLen_ = AlignUp(size, 2);

    ret = FileRead(fp_, fontHeaderCache_, size);
    if (ret != size) {
        return INVALID_RET_VALUE;
    }

    struct FontHeader* last = fontHeaderCache_ + fontNum_ - 1;
    size = last->indexOffset + last->indexLen;
    glyphNodeSectionStart_ = fontIndexSectionStart_ + size;

    size = 0;
    for (uint32_t i = 0; i < fontNum_; i++) {
        size += fontHeaderCache_[i].glyphNum * sizeof(struct GlyphNode);
    }
    bitMapSectionStart_ = glyphNodeSectionStart_ + size;
    ret = GlyphNodeCacheInit();
    if (ret == RET_VALUE_OK) {
        isFileSet_ = true;
    }

    fontId_ = GetTotalFontId();
    return ret;
}

int8_t DynamicFont::SetCurrentFontId(uint8_t fontId)
{
    if (!isFileSet_) {
        return INVALID_RET_VALUE;
    }
    if (fontId > GetTotalFontId()) {
        return INVALID_RET_VALUE;
    }
    if (fontId_ == fontId) {
        return RET_VALUE_OK;
    }

    int low = 0;
    int high = binHeader_.fontNum - 1;
    bool found = false;

    while (low <= high) {
        int mid = (low + high) / 2; // 2 means half
        if (fontHeaderCache_[mid].fontId == fontId) {
            fontIdx_ = mid;
            found = true;
            break;
        } else if (fontHeaderCache_[mid].fontId > fontId) {
            high = mid - 1;
        } else if (fontHeaderCache_[mid].fontId < fontId) {
            low = mid + 1;
        }
    }
    if (found == false) {
        isFontIdSet_ = false;
        curFontHeader_ = nullptr;
        fontId_ = GetTotalFontId();
        return INVALID_RET_VALUE;
    }

    uint32_t size = 0;
    fontId_ = fontId;
    curFontHeader_ = fontHeaderCache_ + fontIdx_;
    curGlyphNode_ = nullptr;
    curFontIndexSectionStart_ = fontIndexSectionStart_ + curFontHeader_->indexOffset;
    for (uint32_t i = 0; i < fontIdx_; i++) {
        size += fontHeaderCache_[i].glyphNum * sizeof(struct GlyphNode);
    }
    curGlyphNodeSectionStart_ = glyphNodeSectionStart_ + size;
    curBitMapSectionStart_ = bitMapSectionStart_ + curFontHeader_->glyphOffset;
    curIndexCache_ = indexCache_ + curFontHeader_->indexOffset;
    isFontIdSet_ = true;

    return RET_VALUE_OK;
}

int32_t DynamicFont::GetRamUsedLen() const
{
    if (!isFileSet_) {
        return INVALID_RET_VALUE;
    }
    return ramUsedLen_;
}

int8_t DynamicFont::GetFontVersion(char* version, uint8_t len) const
{
    if (!isFileSet_ || version == nullptr || len > FONT_VERSION_LEN ||
        len < (strlen(binHeader_.fontVersion) + 1)) {
        return INVALID_RET_VALUE;
    }

    char* v = version;
    const char* s = binHeader_.fontVersion;
    while (*s != '\0') {
        *v = *s;
        v++;
        s++;
    }
    *v = '\0';
    return RET_VALUE_OK;
}

const struct FontHeader* DynamicFont::GetCurrentFontHeader() const
{
    if (!isFontIdSet_) {
        return nullptr;
    }

    if (curFontHeader_ == nullptr) {
        return nullptr;
    }

    return curFontHeader_;
}

const struct GlyphNode* DynamicFont::GetGlyphNode(uint32_t unicode)
{
    struct GlyphNode* node = nullptr;

    if (isFontIdSet_ == false) {
        return nullptr;
    }

    if (curGlyphNode_ != nullptr) {
        if (curGlyphNode_->unicode == unicode && curGlyphNode_->reserve == fontId_) {
            return curGlyphNode_;
        }
    }
    node = GetNodeFromCache(unicode);
    if (node == nullptr) {
        node = GetNodeFromFile(unicode);
        if (node != nullptr) {
            node->reserve = fontId_;
        }
    }

    curGlyphNode_ = node;
    return node;
}

int16_t DynamicFont::GetFontHeight() const
{
    if (isFontIdSet_ == false) {
        return INVALID_RET_VALUE;
    }

    if (curFontHeader_ == nullptr) {
        return INVALID_RET_VALUE;
    }

    return curFontHeader_->fontHeight;
}

int16_t DynamicFont::GetFontWidth(uint32_t unicode)
{
    const struct GlyphNode* node = nullptr;

    if (isFontIdSet_ == false) {
        return INVALID_RET_VALUE;
    }
    node = GetGlyphNode(unicode);
    if (node == nullptr) {
        return INVALID_RET_VALUE;
    }
    return node->advance;
}

int8_t DynamicFont::GetBitmap(uint32_t unicode, uint8_t* bitmap)
{
    int ret;
    const struct GlyphNode* node = nullptr;

    if (bitmap == nullptr) {
        return INVALID_RET_VALUE;
    }
    if (isFontIdSet_ == false) {
        return INVALID_RET_VALUE;
    }

    node = GetGlyphNode(unicode);
    if (node == nullptr) {
        return INVALID_RET_VALUE;
    }

    uint32_t offset = curBitMapSectionStart_ + node->dataOff;
    uint32_t size = node->kernOff - node->dataOff;
    ret = FileSeek(fp_, offset, SEEK_SET);
    if (ret != offset) {
        return INVALID_RET_VALUE;
    }
    ret = FileRead(fp_, bitmap, size);
    if (ret != size) {
        return INVALID_RET_VALUE;
    }

    return RET_VALUE_OK;
}
} // namespace OHOS
