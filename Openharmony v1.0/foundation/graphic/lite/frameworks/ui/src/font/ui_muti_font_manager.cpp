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

#include "font/ui_muti_font_manager.h"
#include "core/typed_text.h"
#include "font/ui_font_header.h"
#include "mem_api.h"
#include "securec.h"

#if ENABLE_MUTI_FONT
namespace OHOS {
UIMutiFontManager::UIMutiFontManager() : arbicTtfId_(0), thaiTtfId_(0), topIndex_(0)
{
    UITextLanguageFontParam* fontParam = nullptr;
    uint8_t totalFontId = GetTotalFontId();
    for (uint8_t i = 0; i < totalFontId; i++) {
        fontParam = GetTextLangFontsTable(i);
        if (fontParam == nullptr) {
            continue;
        }
        if (!fontParam->shaping) {
            continue;
        }
        if (strstr(fontParam->ttfName, ARABIC_LANG) != nullptr) {
            arbicTtfId_ = fontParam->ttfId;
        } else if (strstr(fontParam->ttfName, THAI_LANG) != nullptr) {
            thaiTtfId_ = fontParam->ttfId;
        } else if (strstr(fontParam->ttfName, MYAN_LANG) != nullptr) {
            myanmarTtfId_ = fontParam->ttfId;
        } else if (strstr(fontParam->ttfName, DVCARI_LANG) != nullptr) {
            devanagariTtfId_ = fontParam->ttfId;
        } else if (strstr(fontParam->ttfName, HBREW_LANG) != nullptr) {
            hebrewTtfId_ = fontParam->ttfId;
        }
    }
    fontIdIndex_ = static_cast<uint8_t*>(UIMalloc(totalFontId));
    if (fontIdIndex_ == nullptr) {
        return;
    }
    for (int8_t index = 0; index < totalFontId; index++) {
        fontIdIndex_[index] = MAX_LIST_NUM;
    }
}

UIMutiFontManager::~UIMutiFontManager()
{
    UIFree(fontIdIndex_);
    fontIdIndex_ = nullptr;
}

int8_t UIMutiFontManager::AddNewFont(uint8_t fontListId, uint8_t* fontIds, int8_t size, uint8_t fontId)
{
    fontNodes_[fontId].fontIds = static_cast<uint8_t*>(UIMalloc(size));
    if (fontNodes_[fontId].fontIds == nullptr) {
        return fontId;
    }
    fontIdIndex_[fontListId] = fontId;
    (void)memcpy_s(fontNodes_[fontId].fontIds, size, fontIds, size);
    fontNodes_[fontId].size = size;
    return fontId + 1;
}

int8_t UIMutiFontManager::UpdateFont(uint8_t fontListId, uint8_t* fontIds, uint8_t size)
{
    uint8_t index = fontIdIndex_[fontListId];
    if (index < topIndex_) {
        UIFree(fontNodes_[index].fontIds);
        fontNodes_[index].fontIds = nullptr;
    } else {
        index = topIndex_;
    }

    uint8_t nextIndex = AddNewFont(fontListId, fontIds, size, index);
    if (topIndex_ < nextIndex) {
        topIndex_ = nextIndex;
    }
    return (fontNodes_[index].fontIds == nullptr) ? INVALID_RET_VALUE : RET_VALUE_OK;
}

void UIMutiFontManager::ClearSearchFontList()
{
    uint8_t totalFontId = GetTotalFontId();
    for (int8_t index = 0; index < totalFontId; index++) {
        fontIdIndex_[index] = MAX_LIST_NUM;
    }

    for (auto& node : fontNodes_) {
        UIFree(node.fontIds);
        node.fontIds = nullptr;
        node.size = 0;
    }
    topIndex_ = 0;
}

int8_t UIMutiFontManager::SetSearchFontList(uint8_t fontListId, uint8_t* fontIds, uint8_t size)
{
    if (fontListId >= GetTotalFontId() || fontIds == nullptr || size == 0 || fontIdIndex_ == nullptr ||
        topIndex_ >= MAX_LIST_NUM) {
        return INVALID_RET_VALUE;
    }

    // update
    return UpdateFont(fontListId, fontIds, size);
}

int8_t UIMutiFontManager::GetSearchFontList(uint8_t fontListId, uint8_t** fontIds)
{
    if (fontListId >= GetTotalFontId() || fontIds == nullptr || fontIdIndex_ == nullptr ||
        fontIdIndex_[fontListId] >= MAX_LIST_NUM) {
        return INVALID_RET_VALUE;
    }
    *fontIds = fontNodes_[fontIdIndex_[fontListId]].fontIds;
    return fontNodes_[fontIdIndex_[fontListId]].size;
}

bool UIMutiFontManager::IsNeedShaping(char* text, uint8_t& ttfId)
{
    if (text == nullptr) {
        return false;
    }

    uint32_t i = 0;
    while (text[i] != '\0') {
        uint32_t unicode = TypedText::GetUTF8Next(text, i, &i);
        if (IsShapingLetter(unicode, ttfId)) {
            return true;
        }
    }
    return false;
}

uint8_t UIMutiFontManager::GetShapingFontId(char* text, uint8_t fontId, uint8_t& ttfId)
{
    // the shaping font is in search list, then shapingFontId_ store the real shaping fontid
    if (!IsNeedShaping(text, ttfId)) {
        return 0;
    }

    UITextLanguageFontParam* fontParam1 = GetTextLangFontsTable(fontId);
    if (fontParam1 == nullptr) {
        return DEFAULT_SHAPING_ID;
    }
    if (!fontParam1->shaping) {
        uint8_t* searchLists = nullptr;
        int8_t length = GetSearchFontList(fontId, &searchLists);
        UITextLanguageFontParam* fontParam2 = nullptr;
        for (uint8_t i = 0; i < length; i++) {
            fontParam2 = GetTextLangFontsTable(searchLists[i]);
            if (fontParam2 == nullptr) {
                continue;
            }
            if (fontParam2->ttfId == ttfId) {
                return searchLists[i];
            }
        }
    }
    return DEFAULT_SHAPING_ID;
}
} // namespace OHOS
#endif