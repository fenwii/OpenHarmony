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


#include "font/ui_font.h"
#include <memory>

#include "common/text.h"
#include "file.h"
#include "font/ui_base_font.h"
#include "font/ui_dynamic_font.h"
#include "font/ui_font_cache.h"
#include "font/ui_font_vector.h"
#include "font/ui_text_manager.h"
#include "graphic_config.h"
#if ENABLE_VECTOR_FONT
#include "font/ui_font_vector.h"
#endif

namespace OHOS {
UIFont::UIFont() : pInstance_(nullptr) {}

UIFont::~UIFont() {}

UIFont* UIFont::GetInstance()
{
    static UIFont instance;
    if (instance.pInstance_ == nullptr) {
        instance.pInstance_ = new UIFontVector();
    }

    return &instance;
}

bool UIFont::IsVectorFont() const
{
    return pInstance_->IsVectorFont();
}

uint8_t UIFont::GetFontWeight(uint8_t fontId) const
{
    return pInstance_->GetFontWeight(fontId);
}

int8_t UIFont::SetPsramMemory(uintptr_t ramAddr, uint32_t ramLen)
{
    return pInstance_->SetPsramMemory(ramAddr, ramLen);
}

int8_t UIFont::SetFontPath(const char* dPath)
{
    return pInstance_->SetFontPath(dPath);
}

int8_t UIFont::SetCurrentFontId(uint8_t fontId, uint8_t size)
{
    return pInstance_->SetCurrentFontId(fontId, size);
}

uint8_t UIFont::GetFontId(const char* name, uint8_t size)
{
    return pInstance_->GetFontId(name, size);
}

uint8_t UIFont::GetCurrentFontId() const
{
    return pInstance_->GetCurrentFontId();
}

uint16_t UIFont::GetHeight()
{
    return pInstance_->GetHeight();
}

uint16_t UIFont::GetWidth(uint32_t unicode, uint8_t shapingId)
{
    return pInstance_->GetWidth(unicode, shapingId);
}

int8_t UIFont::GetCurrentFontHeader(FontHeader& fontHeader)
{
    return pInstance_->GetCurrentFontHeader(fontHeader);
}

int8_t UIFont::GetGlyphNode(uint32_t unicode, GlyphNode& glyphNode, bool isGlyph)
{
    return pInstance_->GetGlyphNode(unicode, glyphNode, isGlyph);
}

uint8_t* UIFont::GetBitmap(uint32_t unicode, GlyphNode& glyphNode, uint8_t shapingFont)
{
    return pInstance_->GetBitmap(unicode, glyphNode, shapingFont);
}

uint8_t UIFont::RegisterFontInfo(const char* ttfName)
{
    return pInstance_->RegisterFontInfo(ttfName);
}
uint8_t UIFont::UnregisterFontInfo(const char* ttfName)
{
    return pInstance_->UnregisterFontInfo(ttfName);
}
} // namespace OHOS
