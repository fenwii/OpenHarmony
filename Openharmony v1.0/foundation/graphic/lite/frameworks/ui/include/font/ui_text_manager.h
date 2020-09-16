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

#ifndef UI_TEXT_MANAGER_H
#define UI_TEXT_MANAGER_H

#include "font/ui_font_header.h"
constexpr uint32_t TEXT_UTF8_DATA_MAX = 153600;
namespace OHOS {
class TextManager {
public:
    TextManager();
    TextManager(const TextManager&) = delete;
    TextManager& operator=(const TextManager&) = delete;

    ~TextManager();

    uint32_t GetRamUsedLen() const;

    uint32_t GetBinarySize() const;

    int8_t GetTextVersion(char* version, uint8_t len) const;

    struct UITextLanguageTextParam* GetTextParam(uint16_t textId) const;

    int8_t GetTextUtf8(uint16_t textId, uint8_t** utf8Addr, uint16_t& utf8Len) const;

    int8_t
        GetWildCardStaticStr(uint16_t textId, UITextWildcardStaticType type, uint8_t** strAddr, uint16_t& strLen) const;

    int8_t SetFile(int32_t fp, uint32_t start);

    int8_t SetRamBuffer(uintptr_t addr);

    int8_t SetCurrentLangId(uint8_t langId);

    int8_t GetLocaleByLangId(uint8_t langId, char** isoStr, uint8_t& len) const;

    int8_t GetCodePoints(uint16_t textId, uint32_t** codePoints, uint16_t& codePointsNum) const;

private:
    void CacheInit(void);
    uint32_t getFileLen(int32_t fp, uint32_t offset);
    uint32_t AlignUp(uint32_t addr, uint32_t align)
    {
        return (((addr + (1 << align)) >> align) << align);
    }

    int32_t fp_;
    uint8_t langId_;

    struct LangBinHeader langBinHeader_;
    struct LangTexsTableHeader langTextHeader_;
    struct TextIsoHeader textIsoHeader_;

    uint32_t start_;
    uint32_t end_;
    uint32_t ttfBinStart_;
    uint32_t lineBrkStart_;
    uint32_t lineBrkEnd_;
    uint32_t textParamStart_;
    uint32_t textUtf8ParamStart_;
    uint32_t textUtf8Start_;
    uint32_t textCodepointsStart_;

    uint8_t* ramAddr_;
    uint32_t ramUsedLen_;

    struct UITextLanguageTextParam* textParamCache_;
    struct LangTexsUtf8Param* textUtf8ParamCache_;
    struct TextIsoParam* textIsoParmCache_;
    uint8_t* textUtf8Cache_;
    uint32_t* textCodepointsCache_;
    char* textIsoUtf8Cache_;

    bool isRamSet_;
    bool isFileSet_;
    bool isLangSet_;

    bool SetIsoCache();
};
} // namespace OHOS
#endif
