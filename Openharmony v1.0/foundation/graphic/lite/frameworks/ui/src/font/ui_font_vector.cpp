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

#include "graphic_config.h"
#if ENABLE_VECTOR_FONT
#include <cstring>
#include <string>
#include "file.h"
#include "font/ui_font_vector.h"
#include "securec.h"

namespace OHOS {
struct Metric {
    int left;
    int top;
    int cols;
    int rows;
    int advance;
    uint8_t buf[0];
};
UIFontVector::UIFontVector()
{
#ifdef _WIN32
    ttfDir_ = _pgmptr;
    size_t len = ttfDir_.size();
    size_t pos = ttfDir_.find_last_of('\\');
    if (pos != std::string::npos) {
        ttfDir_.replace((pos + 1), (len - pos), VECTOR_FONT_DIR);
    }
#else
    ttfDir_ = VECTOR_FONT_DIR;
#endif // _WIN32
    ftLibrary_ = nullptr;
    freeTypeInited_ = ((FT_Init_FreeType(&ftLibrary_) == 0) ? true : false);
    fontId_ = FONT_ID_MAX;
    bitmapCache_ = nullptr;
}

UIFontVector::~UIFontVector()
{
    if (freeTypeInited_) {
        FT_Done_FreeType(ftLibrary_);
        freeTypeInited_ = false;
        UnregisterFontInfo(DEFAULT_VECTOR_FONT_FILENAME);
    }
    delete bitmapCache_;
}

uint8_t UIFontVector::RegisterFontInfo(const char* ttfName)
{
    if (ttfName != nullptr && freeTypeInited_) {
        int32_t i = 0;
        while (i < FONT_ID_MAX) {
            if (fontInfo_[i] != nullptr && strncmp(fontInfo_[i], ttfName, TTF_NAME_LEN_MAX) == 0) {
                return FONT_ID_MAX;
            }
            i++;
        }
        i = 0;
        while (i < FONT_ID_MAX) {
            if (fontInfo_[i] == nullptr) {
                std::string ttfPath = ttfDir_;
                ttfPath.append(ttfName);
                int32_t error = FT_New_Face(ftLibrary_, ttfPath.c_str(), 0, &ftFaces_[i]);
                if (error != 0) {
                    return FONT_ID_MAX;
                }
                fontInfo_[i] = ttfName;
                return static_cast<uint8_t>(i);
            }
            i++;
        }
    }

    return FONT_ID_MAX;
}

uint8_t UIFontVector::UnregisterFontInfo(const char* ttfName)
{
    if (ttfName != nullptr) {
        int32_t i = 0;
        while (i < FONT_ID_MAX) {
            if (fontInfo_[i] != nullptr && strncmp(fontInfo_[i], ttfName, TTF_NAME_LEN_MAX) == 0) {
                fontInfo_[i] = nullptr;
                FT_Done_Face(ftFaces_[i]);
                ftFaces_[i] = nullptr;
                return static_cast<uint8_t>(i);
            }
            i++;
        }
    }
    return FONT_ID_MAX;
}

const char* UIFontVector::GetFontTtfName(uint8_t fontId) const
{
    if (fontId < FONT_ID_MAX) {
        return fontInfo_[fontId];
    }

    return nullptr;
}

bool UIFontVector::IsVectorFont() const
{
    return true;
}

uint8_t UIFontVector::GetFontWeight(uint8_t fontId) const
{
    return FONT_BPP_8;
}

int8_t UIFontVector::SetPsramMemory(uintptr_t ramAddr, uint32_t ramLen)
{
    ramAddr_ = ramAddr;
    ramLen_ = ramLen;
    return 0;
}

int8_t UIFontVector::SetFontPath(const char* dPath)
{
    if (dPath == nullptr)
        return INVALID_RET_VALUE;
    if (ttfDir_ == dPath)
        return RET_VALUE_OK;
    ttfDir_ = dPath;
    return RET_VALUE_OK;
}

int8_t UIFontVector::SetCurrentFontId(uint8_t fontId, uint8_t size)
{
    if (fontId >= FONT_ID_MAX || size == 0) {
        return INVALID_RET_VALUE;
    }
    const char* ttfName = GetFontTtfName(fontId);
    if (ttfName == nullptr) {
        return INVALID_RET_VALUE;
    }
    int key = GetKey(fontId, size);
    if (key_ == key) {
        return RET_VALUE_OK;
    }

    if (!freeTypeInited_) {
        return INVALID_RET_VALUE;
    }

    // Set the size
    int error = FT_Set_Char_Size(ftFaces_[fontId], size * FONT_PIXEL_IN_POINT, 0, 0, 0);
    if (error != 0) {
        return INVALID_RET_VALUE;
    }
    key_ = key;
    fontId_ = fontId;
    if (bitmapCache_ == nullptr) {
        bitmapCache_ = new(std::nothrow) UIFontCache(reinterpret_cast<uint8_t*>(ramAddr_), ramLen_);
        if (bitmapCache_ == nullptr) {
            return INVALID_RET_VALUE;
        }
    }
    return RET_VALUE_OK;
}

uint16_t UIFontVector::GetHeight()
{
    if (!freeTypeInited_ || ftFaces_[fontId_] == nullptr || bitmapCache_ == nullptr) {
        return 0;
    }
    return static_cast<uint16_t>(ftFaces_[fontId_]->size->metrics.height / FONT_PIXEL_IN_POINT);
}

uint8_t UIFontVector::GetFontId(const char* ttfName, uint8_t size) const
{
    if (ttfName != nullptr) {
        int32_t i = 0;
        while (i < FONT_ID_MAX) {
            if (fontInfo_[i] != nullptr && strstr(fontInfo_[i], ttfName) != nullptr) {
                return static_cast<uint8_t>(i);
            }
            i++;
        }
    }

    return FONT_ID_MAX;
}

uint16_t UIFontVector::GetWidth(uint32_t unicode, uint8_t shapingId)
{
    if (!freeTypeInited_ || ftFaces_[fontId_] == nullptr || bitmapCache_ == nullptr) {
        return 0;
    }

    uint8_t *bitmap = bitmapCache_->GetBitmap(key_, unicode);
    if (bitmap != nullptr) {
        return reinterpret_cast<struct Metric *>(bitmap)->advance;
    }

    int32_t error;
    if (shapingId != 0) {
        error = FT_Load_Glyph(ftFaces_[fontId_], unicode, FT_LOAD_RENDER);
    } else {
        error = FT_Load_Char(ftFaces_[fontId_], unicode, FT_LOAD_RENDER);
    }
    if (error != 0 || ftFaces_[fontId_]->glyph == nullptr) {
        return 0;
    }
    SetFace(ftFaces_[fontId_], unicode);
    return static_cast<uint16_t>(ftFaces_[fontId_]->glyph->advance.x / FONT_PIXEL_IN_POINT);
}

int8_t UIFontVector::GetCurrentFontHeader(FontHeader& fontHeader)
{
    if (!freeTypeInited_ || ftFaces_[fontId_] == nullptr || bitmapCache_ == nullptr) {
        return INVALID_RET_VALUE;
    }

    fontHeader.ascender = static_cast<int16_t>(ftFaces_[fontId_]->size->metrics.ascender / FONT_PIXEL_IN_POINT);
    fontHeader.descender = static_cast<int16_t>(ftFaces_[fontId_]->size->metrics.descender / FONT_PIXEL_IN_POINT);
    fontHeader.fontHeight = static_cast<uint16_t>(ftFaces_[fontId_]->size->metrics.height / FONT_PIXEL_IN_POINT);
    return RET_VALUE_OK;
}

int8_t UIFontVector::GetGlyphNode(uint32_t unicode, GlyphNode& glyphNode, bool isGlyph)
{
    if (!freeTypeInited_ || ftFaces_[fontId_] == nullptr || bitmapCache_ == nullptr) {
        return INVALID_RET_VALUE;
    }
    uint8_t *bitmap = bitmapCache_->GetBitmap(key_, unicode);
    if (bitmap != nullptr) {
        struct Metric *f = reinterpret_cast<struct Metric *>(bitmap);
        glyphNode.left = f->left;
        glyphNode.top = f->top;
        glyphNode.cols = f->cols;
        glyphNode.rows = f->rows;
        glyphNode.advance = f->advance;
        return RET_VALUE_OK;
    }

    int32_t error;
    if (isGlyph == true) {
        error = FT_Load_Glyph(ftFaces_[fontId_], unicode, FT_LOAD_RENDER);
    } else {
        error = FT_Load_Char(ftFaces_[fontId_], unicode, FT_LOAD_RENDER);
    }
    if (error != 0) {
        return INVALID_RET_VALUE;
    }

    glyphNode.left = ftFaces_[fontId_]->glyph->bitmap_left;
    glyphNode.top = ftFaces_[fontId_]->glyph->bitmap_top;
    glyphNode.cols = ftFaces_[fontId_]->glyph->bitmap.width;
    glyphNode.rows = ftFaces_[fontId_]->glyph->bitmap.rows;
    glyphNode.advance = static_cast<uint16_t>(ftFaces_[fontId_]->glyph->advance.x / FONT_PIXEL_IN_POINT);
    SetFace(ftFaces_[fontId_], unicode);
    return RET_VALUE_OK;
}

uint8_t* UIFontVector::GetBitmap(uint32_t unicode, GlyphNode& glyphNode, uint8_t shapingFont)
{
    if (GetGlyphNode(unicode, glyphNode, shapingFont) != RET_VALUE_OK) {
        return nullptr;
    }

    uint8_t *bitmap = bitmapCache_->GetBitmap(key_, unicode);
    if (bitmap != nullptr) {
        return bitmap + sizeof(struct Metric);
    }
    int32_t error;
    if (shapingFont != 0) {
        error = FT_Load_Glyph(ftFaces_[fontId_], unicode, FT_LOAD_RENDER);
    } else {
        error = FT_Load_Char(ftFaces_[fontId_], unicode, FT_LOAD_RENDER);
    }
    if (error != 0) {
        return nullptr;
    }
    SetFace(ftFaces_[fontId_], unicode);
    return static_cast<uint8_t *>(ftFaces_[fontId_]->glyph->bitmap.buffer);
}

const void UIFontVector::SetFace(FT_Face ftFace, uint32_t unicode) const
{
    struct Metric f;
    f.advance = static_cast<uint16_t>(ftFace->glyph->advance.x / FONT_PIXEL_IN_POINT);
    f.left = ftFace->glyph->bitmap_left;
    f.top = ftFace->glyph->bitmap_top;
    f.cols = ftFace->glyph->bitmap.width;
    f.rows = ftFace->glyph->bitmap.rows;

    uint32_t bitmapSize = ftFace->glyph->bitmap.width * ftFace->glyph->bitmap.rows;
    uint8_t *bitmap = bitmapCache_->GetSpace(key_, unicode, bitmapSize + sizeof(struct Metric));
    if (bitmap != nullptr) {
        if (memcpy_s(bitmap, sizeof(struct Metric), &f, sizeof(struct Metric)) != EOK) {
            return;
        }
        if (memcpy_s(bitmap + sizeof(struct Metric), bitmapSize, ftFace->glyph->bitmap.buffer, bitmapSize) != EOK) {
            return;
        }
    }
}

inline uint32_t UIFontVector::GetKey(uint8_t fontId, uint32_t size)
{
    return (fontId << 5) + size; // fontId store at the 5th bit
}
} // namespace OHOS
#endif // ENABLE_VECTOR_FONT
