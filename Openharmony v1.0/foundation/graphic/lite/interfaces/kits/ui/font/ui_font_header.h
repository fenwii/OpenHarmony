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

#ifndef GRAPHIC_LITE_UI_FONT_HEADER_H
#define GRAPHIC_LITE_UI_FONT_HEADER_H

#include <string>

namespace OHOS {
#pragma pack(1)

enum UITextWildcardStaticType : uint8_t { TEXT_STATIC_STR1 = 0, TEXT_STATIC_STR2, TEXT_STATIC_STR3 };

struct UITextLanguageTextParam {
    uint16_t textId;
    uint8_t fontId;
    uint8_t align : 2;  // UITextLanguageAlignment
    uint8_t direct : 1; // UITextLanguageDirect
    uint8_t shaping : 1;
    uint8_t wildCard1 : 1;
    uint8_t wildCard2 : 1;
    uint8_t reserve : 2;
    uint32_t strOff1;
    uint16_t strLen1;
    uint16_t strLen2;
    uint16_t strLen3;
    uint32_t codePointsOff;
    uint16_t codePointsLen;
}; // UITextLanguageTextParam

// bin header
constexpr uint8_t FONT_VERSION_OFFSET = 0;
constexpr uint8_t FONT_VERSION_LEN = 10;
constexpr uint8_t FONT_MAGIC_NUM_OFFSET = FONT_VERSION_OFFSET + FONT_VERSION_LEN;
constexpr uint8_t FONT_MAGIC_NUM_LEN = 5;
constexpr uint8_t FONT_NUMBER_OFFSET = FONT_MAGIC_NUM_OFFSET + FONT_MAGIC_NUM_LEN;
constexpr uint8_t FONT_NUMBER_LEN = 2;
constexpr uint8_t BIN_HEAD_RES_OFFSET = FONT_NUMBER_OFFSET + FONT_NUMBER_LEN;
constexpr uint8_t BIN_HEAD_RES_LEN = 2;
constexpr uint8_t FONT_DATA_OFFSET = BIN_HEAD_RES_OFFSET + BIN_HEAD_RES_LEN;
constexpr uint8_t BIN_HEAD_TOTAL_LEN = FONT_VERSION_LEN + FONT_MAGIC_NUM_LEN + FONT_NUMBER_LEN + BIN_HEAD_RES_LEN;

// font header
constexpr uint8_t FONT_ID_OFFSET = 0;
constexpr uint8_t FONT_ID_LEN = 1;
constexpr uint8_t GLYPH_NUM_OFFSET = FONT_ID_OFFSET + FONT_ID_LEN;
constexpr uint8_t GLYPH_NUM_LEN = 2;
constexpr uint8_t FONT_HEIGHT_OFFSET = GLYPH_NUM_OFFSET + GLYPH_NUM_LEN;
constexpr uint8_t FONT_HEIGHT_LEN = 2;
constexpr uint8_t FONT_ASCEND_OFFSET = FONT_HEIGHT_OFFSET + FONT_HEIGHT_LEN;
constexpr uint8_t FONT_ASCEND_LEN = 2;
constexpr uint8_t FONT_DESCEND_OFFSET = FONT_ASCEND_OFFSET + FONT_ASCEND_LEN;
constexpr uint8_t FONT_DESCEND_LEN = 2;
constexpr uint8_t FONT_INDEX_OFF_OFFSET = FONT_DESCEND_OFFSET + FONT_DESCEND_LEN;
constexpr uint8_t FONT_INDEX_OFF_LEN = 4;
constexpr uint8_t FONT_INDEX_LEN_OFFSET = FONT_INDEX_OFF_OFFSET + FONT_INDEX_OFF_LEN;
constexpr uint8_t FONT_INDEX_LEN_LEN = 4;
constexpr uint8_t GLYPH_OFF_OFFSET = FONT_INDEX_LEN_OFFSET + FONT_INDEX_LEN_LEN;
constexpr uint8_t GLYPH_OFF_LEN = 4;
constexpr uint8_t GLYPH_LEN_OFFSET = GLYPH_OFF_OFFSET + GLYPH_OFF_LEN;
constexpr uint8_t GLYPH_LEN_LEN = 4;
constexpr uint8_t FONT_HEAD_RES_OFFSET = GLYPH_LEN_OFFSET + GLYPH_LEN_LEN;
constexpr uint8_t FONT_HEAD_RES_LEN = 2;
constexpr uint8_t FONT_HEAD_TOTAL_LEN = FONT_ID_LEN + GLYPH_NUM_LEN + FONT_HEIGHT_LEN + FONT_ASCEND_LEN +
                                        FONT_DESCEND_LEN + GLYPH_OFF_LEN + GLYPH_LEN_LEN + FONT_HEAD_RES_LEN;

// glyph header, internal using, not write to bin file
constexpr uint8_t FONT_G_HEIGHT_OFFSET = 0;
constexpr uint8_t FONT_G_HEIGHT_LEN = 2;
constexpr uint8_t GLYPH_G_NUM_OFFSET = FONT_G_HEIGHT_OFFSET + FONT_G_HEIGHT_LEN;
constexpr uint8_t GLYPH_G_NUM_LEN = 2;
constexpr uint8_t GLYPH_G_ASCEND_OFFSET = GLYPH_G_NUM_OFFSET + GLYPH_G_NUM_LEN;
constexpr uint8_t GLYPH_G_ASCEND_LEN = 2;
constexpr uint8_t GLYPH_G_DESCEND_OFFSET = GLYPH_G_ASCEND_OFFSET + GLYPH_G_ASCEND_LEN;
constexpr uint8_t GLYPH_G_DESCEND_LEN = 2;
constexpr uint8_t GLYPH_G_INDEX_OFF_OFFSET = GLYPH_G_DESCEND_OFFSET + GLYPH_G_DESCEND_LEN;
constexpr uint8_t GLYPH_G_INDEX_OFF_LEN = 4;
constexpr uint8_t GLYPH_G_INDEX_LEN_OFFSET = GLYPH_G_INDEX_OFF_OFFSET + GLYPH_G_INDEX_OFF_LEN;
constexpr uint8_t GLYPH_G_INDEX_LEN_LEN = 4;
constexpr uint8_t GLYPH_G_OFF_OFFSET = GLYPH_G_INDEX_LEN_OFFSET + GLYPH_G_INDEX_LEN_LEN;
constexpr uint8_t GLYPH_G_OFF_LEN = 4;
constexpr uint8_t GLYPH_G_LEN_OFFSET = GLYPH_G_OFF_OFFSET + GLYPH_G_OFF_LEN;
constexpr uint8_t GLYPH_G_LEN_LEN = 4;
constexpr uint8_t FONT_G_HEAD_TOTAL_LEN =
    FONT_G_HEIGHT_LEN + GLYPH_G_NUM_LEN + GLYPH_G_ASCEND_LEN + GLYPH_G_DESCEND_LEN + GLYPH_G_OFF_LEN + GLYPH_G_LEN_LEN;

// glyph node
constexpr uint8_t GLYPH_UNICODE_OFFSET = GLYPH_G_NUM_OFFSET + GLYPH_G_NUM_LEN;
constexpr uint8_t GLYPH_UNICODE_LEN = 4;
constexpr uint8_t GLYPH_LEFT_OFFSET = GLYPH_UNICODE_OFFSET + GLYPH_UNICODE_LEN;
constexpr uint8_t GLYPH_LEFT_LEN = 2;
constexpr uint8_t GLYPH_TOP_OFFSET = GLYPH_LEFT_OFFSET + GLYPH_LEFT_LEN;
constexpr uint8_t GLYPH_TOP_LEN = 2;
constexpr uint8_t GLYPH_ADVANCE_OFFSET = GLYPH_TOP_OFFSET + GLYPH_TOP_LEN;
constexpr uint8_t GLYPH_ADVANCE_LEN = 2;
constexpr uint8_t GLYPH_COLS_OFFSET = GLYPH_ADVANCE_OFFSET + GLYPH_ADVANCE_LEN;
constexpr uint8_t GLYPH_COLS_LEN = 2;
constexpr uint8_t GLYPH_ROWS_OFFSET = GLYPH_COLS_OFFSET + GLYPH_COLS_LEN;
constexpr uint8_t GLYPH_ROWS_LEN = 2;
constexpr uint8_t GLYPH_DATA_OFF_OFFSET = GLYPH_ROWS_OFFSET + GLYPH_ROWS_LEN;
constexpr uint8_t GLYPH_DATA_OFF_LEN = 4;
constexpr uint8_t GLYPH_KERN_OFF_OFFSET = GLYPH_DATA_OFF_OFFSET + GLYPH_DATA_OFF_LEN;
constexpr uint8_t GLYPH_KERN_OFF_LEN = 4;
constexpr uint8_t GLYPH_KERN_SIZE_OFFSET = GLYPH_KERN_OFF_OFFSET + GLYPH_KERN_OFF_LEN;
constexpr uint8_t GLYPH_KERN_SIZE_LEN = 2;
constexpr uint8_t GLYPH_HEAD_RES_OFFSET = GLYPH_KERN_SIZE_OFFSET + GLYPH_KERN_SIZE_LEN;
constexpr uint8_t GLYPH_HEAD_RES_LEN = 2;
constexpr uint8_t GLYPH_HEAD_TOTAL_LEN = GLYPH_UNICODE_LEN + GLYPH_LEFT_LEN + GLYPH_TOP_LEN + GLYPH_ADVANCE_LEN +
                                         GLYPH_COLS_LEN + GLYPH_ROWS_LEN + GLYPH_DATA_OFF_LEN + GLYPH_KERN_OFF_LEN +
                                         GLYPH_KERN_SIZE_LEN + GLYPH_HEAD_RES_LEN;

// language texts table header
constexpr uint8_t LANG_TEXTS_PARAM_OFF = 0;
constexpr uint8_t LANG_TEXTS_PARAM_LEN = 4;
constexpr uint8_t LANG_TEXTS_UTF8P_OFF = LANG_TEXTS_PARAM_OFF + LANG_TEXTS_PARAM_LEN;
constexpr uint8_t LANG_TEXTS_UTF8P_LEN = 4;
constexpr uint8_t LANG_TEXTS_UTF8_OFF = LANG_TEXTS_UTF8P_OFF + LANG_TEXTS_UTF8P_LEN;
constexpr uint8_t LANG_TEXTS_UTF8_LEN = 4;
constexpr uint8_t LANG_TEXTS_TOTAL_LEN = LANG_TEXTS_PARAM_LEN + LANG_TEXTS_UTF8P_LEN + LANG_TEXTS_UTF8_LEN;

// language texts utf-8 param header
constexpr uint8_t LANG_UTF8_PARAM_TOTAL_LEN = 8; // 4B offset + 4B len

// language bin header
constexpr uint8_t LANG_OFFSET_OFF = 0;
constexpr uint8_t LANG_OFFSET_LEN = 4;
constexpr uint8_t LANG_SIZE_OFF = LANG_OFFSET_OFF + LANG_OFFSET_LEN;
constexpr uint8_t LANG_SIZE_LEN = 4;
constexpr uint8_t LANG_HEAD_TOTAL_LEN = LANG_OFFSET_LEN + LANG_SIZE_LEN;

// dynamic font
constexpr uint32_t GLYPH_HEADER_LENGTH = 0xD7C00;                  // 860 K, almost 33870 glyph header
constexpr uint32_t FONT_HEADER_LENGTH = FONT_HEAD_TOTAL_LEN * 150; // 150 font, almost 3K
constexpr uint32_t DYNAMIC_FONT_HEADER_TOTAL_LENGTH = GLYPH_HEADER_LENGTH + FONT_HEADER_LENGTH;

// static font psram
constexpr uint32_t UTF8_PARAM_LENGTH = LANG_UTF8_PARAM_TOTAL_LEN * 100;          // 100 lang, almost 1K
constexpr uint32_t STATIC_PARAM_LENGTH = sizeof(UITextLanguageTextParam) * 3218; // 3218 texts, 44K
constexpr uint32_t STATIC_UTF8_LENGTH = 0xC800;                                  // 50 * 1024 = 50K
constexpr uint32_t STATIC_FONT_HEADER_LENGTH = FONT_HEAD_TOTAL_LEN * 150;        // 150 font, almost 3K
constexpr uint32_t STATIC_GLYPH_HEADER_LENGTH = 0x15C00;                         // 87K, almost 26 * 3426 glyph header
constexpr uint32_t STATIC_FONT_HEADER_TOTAL_LENGTH = UTF8_PARAM_LENGTH + STATIC_PARAM_LENGTH + STATIC_UTF8_LENGTH +
                                                     STATIC_FONT_HEADER_LENGTH + STATIC_GLYPH_HEADER_LENGTH;

constexpr uint8_t MAX_CACHE_CHAR_NUMBER = 50;        // cache 50 letters
constexpr uint32_t DYNAMIC_ONE_CHAR_LENGTH = 0x5000; // 20 K means w200:h200:bpp4, 200 x 200 / 2

// 50 * 20K = 1000K
constexpr uint32_t DYNAMIC_TEXT_CACHE_LENGTH = MAX_CACHE_CHAR_NUMBER * DYNAMIC_ONE_CHAR_LENGTH;
constexpr uint32_t MIN_FONT_PSRAM_LENGTH = 0x300000;

// text shaping psram
constexpr uint32_t SHAPING_TTF_TABLE_LENGTH = 0x96000; // 600K
constexpr uint32_t SHAPING_WORD_DICT_LENGTH = 0x7D000; // 500K
constexpr uint32_t SHAPING_CACHE_LENGTH = 0x64000;     // 400K
constexpr uint32_t MIN_SHAPING_PSRAM_LENGTH =
    SHAPING_TTF_TABLE_LENGTH + SHAPING_WORD_DICT_LENGTH + SHAPING_CACHE_LENGTH;

// other definition
constexpr uint8_t FONT_DPI = 100;
constexpr uint8_t FONT_PIXEL_IN_POINT = 64;
constexpr uint8_t BPP_BIT_1 = 1;
constexpr uint8_t BPP_MASK_1 = 7;
constexpr uint8_t BPP_SHIFT_1 = 3;
constexpr uint8_t BPP_MASK_NUM_1 = 0x80;
constexpr uint8_t BPP_BIT_2 = 2;
constexpr uint8_t BPP_MASK_2 = 3;
constexpr uint8_t BPP_SHIFT_2 = 2;
constexpr uint8_t BPP_MASK_NUM_2 = 0xC0;
constexpr uint8_t BPP_BIT_4 = 4;
constexpr uint8_t BPP_MASK_4 = 1;
constexpr uint8_t BPP_SHIFT_4 = 1;
constexpr uint8_t BPP_MASK_NUM_4 = 0xF0;
constexpr uint8_t BPP_BIT_8 = 8;
constexpr uint32_t DEFAULT_FONT_SIZE = 10;
constexpr uint32_t MAX_CHAR_MB_LEN = 16;
constexpr uint32_t MAX_CHAR_NUM = 512;
constexpr uint8_t BITS_PER_BYTE = 8;
constexpr uint8_t BITS_MASK_IN_BYTE = 7;
constexpr uint32_t MAX_MONO_ADVANCE = 128;
constexpr uint8_t BIT0 = 0;
constexpr uint8_t BIT1 = 1;
constexpr uint8_t BIT2 = 2;
constexpr uint8_t BIT3 = 3;
constexpr uint8_t BIT4 = 4;
constexpr uint8_t BIT5 = 5;
constexpr uint8_t BIT6 = 6;
constexpr uint8_t BIT7 = 7;
constexpr uint8_t BIT8 = 8;
constexpr uint8_t BIT12 = 12;
constexpr uint8_t BIT18 = 18;
constexpr uint8_t GLYPH_KERN_ITEM_LEN = 2;
constexpr uint8_t UTF_TO_UNICODE_MASK1 = 0x80;
constexpr uint8_t UTF_TO_UNICODE_MASK2 = 0xC0;
constexpr uint8_t UTF_TO_UNICODE_MASK3 = 0xE0;
constexpr uint8_t UTF_TO_UNICODE_MASK4 = 0xF0;
constexpr uint8_t UTF_TO_UNICODE_MASK5 = 0xF8;
constexpr uint8_t UTF_TO_UNICODE_MASK6 = 0x3F;
constexpr uint8_t UTF_TO_UNICODE_MASK7 = 0x1F;
constexpr uint8_t UTF_TO_UNICODE_MASK8 = 0x07;
constexpr uint8_t UTF_TO_UNICODE_MASK9 = 0x0F;
constexpr uint8_t MAX_FILE_NAME_LEN = 255;
constexpr uint8_t GPU_FONT_ALIGN_BIT = 16;
constexpr uint8_t INVALID_UCHAR_ID = 0xFF;
constexpr uint16_t INVALID_USHORT_ID = 0xFFFF;
constexpr uint32_t INVALID_UINT_ID = 0xFFFFFFFF;
constexpr int8_t INVALID_RET_VALUE = -1;
constexpr int8_t RET_VALUE_OK = 0;
constexpr const char* FONT_MAGIC_NUMBER = "OHOS";

/**
 * @brief struct BinHeader for font
 * refer to ui_font.h
 */
struct BinHeader {
    char fontVersion[FONT_VERSION_LEN]; // FONT_VERSION_OFFSET
    char fontMagic[FONT_MAGIC_NUM_LEN]; // FONT_MAGIC_NUM_OFFSET
    uint16_t fontNum;                   // FONT_NUMBER_OFFSET
    uint16_t reserve;                   // BIN_HEAD_RES_OFFSET
};

/**
 * @brief struct FontHeader
 * refer to ui_font.h
 */
struct FontHeader {
    uint8_t fontId;      // FONT_ID_OFFSET
    uint16_t glyphNum;   // GLYPH_NUM_OFFSET
    uint16_t fontHeight; // FONT_HEIGHT_OFFSET
    int16_t ascender;    // FONT_ASCEND_LEN
    int16_t descender;   // FONT_DESCEND_LEN
    uint32_t indexOffset;
    uint32_t indexLen;
    uint32_t glyphOffset; // GLYPH_G_OFF_OFFSET
    uint32_t glyphLen;    // GLYPH_OFF_OFFSET
    uint16_t reserve;     // GLYPH_LEN_OFFSET
};

/**
 * @brief struct GlyphHeader for font, font tool using, not for bin file
 * refer to ui_font.h
 */
struct GlyphHeader {
    uint16_t fontHeight; // FONT_G_HEIGHT_OFFSET
    uint16_t glyphNum;   // GLYPH_G_NUM_OFFSET
    int16_t ascender;    // GLYPH_G_ASCEND_LEN
    int16_t descender;   // GLYPH_G_DESCEND_LEN
    uint32_t indexOffset;
    uint32_t indexLen;
    uint32_t glyphOffset; // GLYPH_G_OFF_OFFSET
    uint32_t glyphLen;    // GLYPH_G_LEN_OFFSET
};

/**
 * @brief struct GlyphNode for font
 * refer to ui_font.h
 */
struct GlyphNode {
    uint32_t unicode;  // GLYPH_UNICODE_OFFSET
    int16_t left;      // GLYPH_LEFT_OFFSET
    int16_t top;       // GLYPH_TOP_OFFSET
    uint16_t advance;  // GLYPH_ADVANCE_OFFSET
    uint16_t cols;     // GLYPH_COLS_OFFSET
    uint16_t rows;     // GLYPH_ROWS_OFFSET
    uint32_t dataOff;  // GLYPH_DATA_OFF_OFFSET
    uint32_t kernOff;  // GLYPH_KERN_OFF_OFFSET
    uint16_t kernSize; // GLYPH_KERN_SIZE_OFFSET
    uint16_t reserve;  // GLYPH_HEAD_RES_OFFSET
};

/**
 * @brief struct LangBinHeader for font
 * refer to ui_font.h
 */
struct LangBinHeader {
    char fontVersion[FONT_VERSION_LEN]; // FONT_VERSION_OFFSET
    char fontMagic[FONT_MAGIC_NUM_LEN]; // FONT_MAGIC_NUM_OFFSET
};

/**
 * @brief struct LangFontBinHeader for font
 * refer to ui_font.h
 */
struct LangFontBinHeader {
    uint32_t offset; // LANG_OFFSET_LEN
    uint32_t size;   // LANG_SIZE_LEN
};

/**
 * @brief struct LangTexsTableHeader for font
 * refer to ui_font.h
 */
struct LangTexsTableHeader {
    uint32_t textParamStart;
    uint32_t textParamLen; // LANG_TEXTS_PARAM_LEN
    uint32_t textUtf8ParamStart;
    uint32_t textUtf8ParamLen; // LANG_TEXTS_UTF8P_LEN
    uint32_t textUtf8Start;
    uint32_t textUtf8Len; // LANG_TEXTS_UTF8_LEN
    uint32_t textCodepointsStart;
    uint32_t textCodepointsLen;
};

/**
 * @brief struct LangTexsUtf8Param for font
 * refer to ui_font.h
 */
struct LangTexsUtf8Param {
    uint32_t offset;
    uint32_t len;
};

/**
 * @brief struct KernNode for kerning of font
 * refer to ui_font.h
 */
struct KernNode {
    uint32_t unicode;  // GLYPH_UNICODE_LEN
    int16_t kernValue; // GLYPH_KERN_SIZE_LEN
    uint8_t found;     // found the kerning or not
};

/**
 * @brief struct TtfHeader for header of ttftab.bin
 * refer to ui_font.h
 */
struct TtfHeader {
    uint8_t ttfId;
    uint32_t offset;
    uint32_t len;
};

struct UITextLanguageFontParam {
    uint8_t size;
    uint8_t fontWeight;
    uint8_t shaping;
    uint8_t ttfId;
    const char* ttfName;
}; // UITextLanguageFontParam

struct TextIsoHeader {
    uint16_t paramLen;
    uint16_t strLen;
};

struct TextIsoParam {
    uint16_t offset;
    uint16_t len;
};

struct LangTextParam {
    uint8_t fontDirect; // refer to UITextLanguageDirect
    uint8_t fontSize;
    const char* familyName; // such as "Roboto-Medium"
    const char* langName;   // such as "ar", "zh"
};

struct FileCommonHeader {
    const char magicWord[5]; // 5:file identifier's length is 5
    uint32_t fileLength;
};
#pragma pack()

/**
 * @brief Get the Text Lang Fonts Table
 * @param uint8_t langFontId [in] the font id
 * @return UITextLanguageFontParam* the font table, definition is in font tool
 */
UITextLanguageFontParam* GetTextLangFontsTable(uint8_t langFontId);

/**
 * @brief Get the Total Lang Id
 * @return uint8_t the total Lang id, definition is in font tool
 */
uint8_t GetTotalLangId();

/**
 * @brief Get the Total Font Id
 * @return uint8_t the total font id, definition is in font tool
 */
uint8_t GetTotalFontId();

/**
 * @brief Get the Total Text Id
 * @return uint8_t the total text id, definition is in font tool
 */
uint16_t GetTotalTextId();

/**
 * @brief Get the Lang Text default param table
 * @return LangTextParam* the param table, definition is in font tool
 */
LangTextParam* GetLangTextDefaultParamTable();
} // namespace OHOS
#endif /* UI_FONT_HEADER_H */