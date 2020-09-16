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

#include "common/ui_text_language.h"
#include "font/ui_font_header.h"

namespace OHOS {
static UITextLanguageFontParam g_uiTextLangFontsTable[LANGUAGE_FONT_ID_MAX] = {
    {14, 4, 0, 0, "RobotoCondensed-Regular"},
    {18, 4, 0, 0, "RobotoCondensed-Regular"},
    {20, 4, 0, 0, "RobotoCondensed-Regular"},
    {23, 4, 0, 0, "RobotoCondensed-Regular"},
    {23, 4, 0, 0, "RobotoCondensed-Regular"},
    {26, 4, 0, 0, "RobotoCondensed-Regular"},
    {28, 4, 0, 0, "RobotoCondensed-Regular"},
    {30, 4, 0, 0, "RobotoCondensed-Regular"},
    {38, 4, 0, 0, "RobotoCondensed-Regular"},
    {48, 4, 0, 0, "RobotoCondensed-Regular"},
    {14, 4, 0, 1, "HYQiHei-65S"},
    {18, 4, 0, 1, "HYQiHei-65S"},
    {16, 4, 0, 1, "HYQiHei-65S"},
    {22, 4, 0, 1, "HYQiHei-65S"},
    {24, 4, 0, 1, "HYQiHei-65S"},
    {26, 4, 0, 1, "HYQiHei-65S"},
    {30, 4, 0, 1, "HYQiHei-65S"},
    {34, 4, 0, 1, "HYQiHei-65S"},
    {38, 4, 0, 1, "HYQiHei-65S"},
    {48, 4, 0, 1, "HYQiHei-65S"},
    {14, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {18, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {24, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {30, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {38, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {20, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {23, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {26, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {28, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {48, 4, 1, 2, "NotoNaskhArabic-Regular"},
    {14, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {18, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {24, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {20, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {23, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {26, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {28, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {30, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {38, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {48, 4, 0, 3, "NotoSansCJKjp-Regular"},
    {14, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {18, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {24, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {20, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {23, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {26, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {28, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {30, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {38, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {48, 4, 0, 4, "NotoSansCJKkr-Regular"},
    {14, 4, 1, 5, "NotoSansThai-Regular"},
    {18, 4, 1, 5, "NotoSansThai-Regular"},
    {24, 4, 1, 5, "NotoSansThai-Regular"},
    {30, 4, 1, 5, "NotoSansThai-Regular"},
    {38, 4, 1, 5, "NotoSansThai-Regular"},
    {14, 4, 0, 6, "NotoSansHebrew-Regular"},
    {18, 4, 0, 6, "NotoSansHebrew-Regular"},
    {24, 4, 0, 6, "NotoSansHebrew-Regular"},
    {30, 4, 0, 6, "NotoSansHebrew-Regular"},
    {38, 4, 0, 6, "NotoSansHebrew-Regular"},
    {20, 4, 0, 6, "NotoSansHebrew-Regular"},
    {23, 4, 0, 6, "NotoSansHebrew-Regular"},
    {26, 4, 0, 6, "NotoSansHebrew-Regular"},
    {28, 4, 0, 6, "NotoSansHebrew-Regular"},
    {48, 4, 0, 6, "NotoSansHebrew-Regular"},
    {20, 4, 1, 5, "NotoSansThai-Regular"},
    {23, 4, 1, 5, "NotoSansThai-Regular"},
    {26, 4, 1, 5, "NotoSansThai-Regular"},
    {28, 4, 1, 5, "NotoSansThai-Regular"},
    {48, 4, 1, 5, "NotoSansThai-Regular"},
    {14, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {18, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {24, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {20, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {23, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {26, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {28, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {30, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {38, 4, 0, 7, "NotoSansDevanagari-Regular"},
    {48, 4, 0, 7, "NotoSansDevanagari-Regular"},
}; // g_uiTextLangFontsTable

static LangTextParam g_langTextDefaultParamTable[LANGUAGE_MAX] = {
    {0, 30, "HYQiHei-65S", "zh"},
    {0, 30, "RobotoCondensed-Regular", "en"},
    {0, 30, "RobotoCondensed-Regular", "fr"},
    {0, 30, "RobotoCondensed-Regular", "de"},
    {0, 30, "RobotoCondensed-Regular", "pt"},
    {0, 30, "RobotoCondensed-Regular", "ru"},
    {0, 30, "RobotoCondensed-Regular", "es"},
    {0, 30, "RobotoCondensed-Regular", "it"},
    {0, 30, "RobotoCondensed-Regular", "pl"},
    {0, 30, "RobotoCondensed-Regular", "en"},
    {0, 30, "RobotoCondensed-Regular", "tr"},
    {0, 30, "RobotoCondensed-Regular", "da"},
    {0, 30, "RobotoCondensed-Regular", "sv"},
    {0, 30, "RobotoCondensed-Regular", "no"},
    {0, 30, "RobotoCondensed-Regular", "fi"},
    {0, 30, "HYQiHei-65S", "zh"},
    {0, 30, "HYQiHei-65S", "zh"},
    {0, 30, "NotoSansCJKjp-Regular", "jv"},
    {0, 30, "NotoSansCJKkr-Regular", "ko"},
    {1, 30, "NotoNaskhArabic-Regular", "ar"},
    {0, 30, "RobotoCondensed-Regular", "pt"},
    {0, 30, "RobotoCondensed-Regular", "es"},
    {0, 30, "NotoSansThai-Regular", "th"},
    {0, 30, "RobotoCondensed-Regular", "vi"},
    {1, 30, "NotoSansHebrew-Regular", "he"},
    {0, 30, "RobotoCondensed-Regular", "cs"},
    {0, 30, "RobotoCondensed-Regular", "sk"},
    {0, 30, "RobotoCondensed-Regular", "nl"},
    {0, 30, "RobotoCondensed-Regular", "el"},
    {0, 30, "RobotoCondensed-Regular", "hu"},
    {0, 30, "RobotoCondensed-Regular", "ms"},
    {0, 30, "RobotoCondensed-Regular", "ro"},
    {0, 30, "RobotoCondensed-Regular", "sr"},
    {0, 30, "NotoSansDevanagari-Regular", "hi"},
    {0, 30, "RobotoCondensed-Regular", "uk"},
    {0, 30, "RobotoCondensed-Regular", "my"},
    {0, 30, "RobotoCondensed-Regular", "id"},
    {0, 30, "RobotoCondensed-Regular", "bg"},
    {0, 30, "RobotoCondensed-Regular", "hr"},
    {0, 30, "RobotoCondensed-Regular", "sl"},
    {0, 30, "RobotoCondensed-Regular", "lt"},
    {0, 30, "RobotoCondensed-Regular", "lv"},
    {0, 30, "RobotoCondensed-Regular", "et"},
}; // g_langTextDefaultParamTable

UITextLanguageFontParam* GetTextLangFontsTable(uint8_t langFontId)
{
    if (langFontId >= LANGUAGE_FONT_ID_MAX) {
        return nullptr;
    }
    return &(g_uiTextLangFontsTable[langFontId]);
}

uint8_t GetTotalLangId()
{
    return LANGUAGE_MAX;
}

uint8_t GetTotalFontId()
{
    return LANGUAGE_FONT_ID_MAX;
}

uint16_t GetTotalTextId()
{
    return LANGUAGE_TEXT_ID_MAX;
}

LangTextParam* GetLangTextDefaultParamTable()
{
    return g_langTextDefaultParamTable;
}
} // namespace OHOS
