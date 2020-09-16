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

#ifndef UI_MUTI_FONT_MANAGER_H
#define UI_MUTI_FONT_MANAGER_H

#include "graphic_config.h"

#if ENABLE_MUTI_FONT
namespace OHOS {
class UIMutiFontManager {
public:
    UIMutiFontManager(const UIMutiFontManager&) = delete;
    UIMutiFontManager& operator=(const UIMutiFontManager&) = delete;
    UIMutiFontManager(UIMutiFontManager&&) noexcept = delete;
    UIMutiFontManager& operator=(UIMutiFontManager&&) noexcept = delete;

    /**
     * @brief Get the Instance object
     *
     * @return UIMutiFontManager*
     */
    static UIMutiFontManager* GetInstance()
    {
        static UIMutiFontManager instance;
        return &instance;
    }

    void ClearSearchFontList();
    int8_t SetSearchFontList(uint8_t fontListId, uint8_t* fontIds, uint8_t size);
    int8_t GetSearchFontList(uint8_t fontListId, uint8_t** fontIds);
    bool IsNeedShaping(char* text, uint8_t& ttfId);
    uint8_t GetShapingFontId(char* text, uint8_t fontId, uint8_t& ttfId);

private:
    /**
     * @brief Construct a new UIMutiFontManager object
     *
     */
    UIMutiFontManager();

    /**
     * @brief Destroy the UIMutiFontManager object
     *
     */
    ~UIMutiFontManager();
    int8_t AddNewFont(uint8_t fontListId, uint8_t* fontIds, int8_t size, uint8_t fontId);
    int8_t UpdateFont(uint8_t fontListId, uint8_t* fontIds, uint8_t size);
    int8_t IsShapingLetter(uint32_t unicode, uint8_t& ttfId)
    {
        // arbic
        if (unicode <= 0x06FF && unicode >= 0x0600) {
            ttfId = arbicTtfId_;
            return true;
        }
        // thai
        if (unicode <= 0x0E7F && unicode >= 0x0E00) {
            ttfId = thaiTtfId_;
            return true;
        }
        // Devanagari
        if (unicode <= 0x097F && unicode >= 0x0900) {
            ttfId = devanagariTtfId_;
            return true;
        }
        // Hebrew
        if (unicode <= 0x05FF && unicode >= 0x0590) {
            ttfId = hebrewTtfId_;
            return true;
        }
        // Myanmar
        if (unicode <= 0x109F && unicode >= 0x1000) {
            ttfId = myanmarTtfId_;
            return true;
        }
        return false;
    }

    struct FontIdNode {
        uint8_t* fontIds = nullptr;
        int8_t size = 0;
    };
    static constexpr uint8_t MAX_LIST_NUM = 20;
    static constexpr uint8_t DEFAULT_SHAPING_ID = 1;
    static constexpr const char* ARABIC_LANG = "Arabic";
    static constexpr const char* THAI_LANG = "Thai";
    static constexpr const char* MYAN_LANG = "Myanmar";
    static constexpr const char* DVCARI_LANG = "Devanagari";
    static constexpr const char* HBREW_LANG = "Hebrew";
    uint8_t arbicTtfId_;
    uint8_t thaiTtfId_;
    uint8_t myanmarTtfId_;
    uint8_t devanagariTtfId_;
    uint8_t hebrewTtfId_;
    uint8_t topIndex_;
    uint8_t* fontIdIndex_;
    FontIdNode fontNodes_[MAX_LIST_NUM];
};
} // namespace OHOS
#endif
#endif