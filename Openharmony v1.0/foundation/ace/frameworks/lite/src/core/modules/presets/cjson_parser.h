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
#ifndef OHOS_ACELITE_CJSON_PARSER_H
#define OHOS_ACELITE_CJSON_PARSER_H
#include "acelite_config.h"

#ifdef FEATURE_LOCALIZATION_MODULE
#include <cJSON.h>
#include <jerryscript.h>
#include "ace_mem_base.h"
#include "js_app_context.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class CJSONParser final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(CJSONParser);
    struct ListNode : public MemoryHeap {
        char *value;
        ListNode *next;
    };

    CJSONParser();

    ~CJSONParser()
    {
        if (fileList_ != nullptr) {
            ClearNode(fileList_);
        }
        ACE_FREE(countries_);
        ACE_FREE(language_);
        ACE_FREE(filePath_);
    }

    /**
     * @breif: read the next file which matches the language-country, and then transfer the file content
     * to json.
     *
     * @return if the fileList is nullptr or read the last one return false.if get the correct content return true.
     */
    bool ChangeJsonFile(cJSON *&currentItem);

    /**
     * @brief: replace the placeholder in result with the data defined by user
     * if plural is true, it will replace the number in placeholder,
     * replace the same name in js object.
     */
#ifdef LOCALIZATION_PLURAL
    char *FillPlaceholder(char *format, jerry_value_t arg, jerry_length_t num, bool isPlural);
#else
    char *FillPlaceholder(char *format, jerry_value_t arg, jerry_length_t num);
#endif // LOCALIZATION_PLURAL

    /**
     * @brief:set the readIndex_ = 0; the value of index is the index where the key is defined
     */
    void ResetIndex();

    /**
     * @brief: get the filePath name
     */
    bool Init();

    /**
     * @brief: merge string destination and resource, save the merge result in destination
     * if check is true, it will free destination string
     */
    char *SubStr(const char *src, size_t start, size_t length);

    /**
     * @brief: split the string by delemeter and save the split result in node
     *
     * @return the length of node
     */
    uint8_t Split(const char *target, char delemeter, ListNode *&node);

    static bool AddNode(ListNode *&head, char *current);
    static char *GetNode(ListNode *node, int index);
    static void ClearNode(ListNode *&node);
    static char *ToString(ListNode *node, uint8_t length);

private:
    constexpr static int maxLen_ = 26;
    const char * const allCountries_[maxLen_] = {
        "DEFGILMOQRSTUWXZ",
        "ABDEFGHIJLMNORSTVWYZ",
        "ACDFGHIKLMNORUVWXYZ",
        "EJKMOZ",
        "CEGHRST",
        "IJKMOR",
        "ABDEFGHILMNPQRSTUWY",
        "KMNRTU",
        "DELMNOQRST",
        "EMOP",
        "EGHIMNPRWYZ",
        "ABCIKRSTUVY",
        "ACDEFGHKLMNOPQRSTUVWXYZ",
        "ACEFGILOPRUZ",
        "M",
        "AEFGHKLMNRSTWY",
        "A",
        "EOSUW",
        "ABCDEGHIJKLMNORSTVXYZ",
        "CDFGHJKLMNORTVWZ",
        "AGMSYZ",
        "ACEGINU",
        "FS",
        "",
        "ET",
        "AMW",
    };
    enum FILETYPE { COUNTRY = 0, LANG = 1, OTHERCOUNTRY = -1, ERRORCODE = -2};
    const char *GetCountries(int8_t index);

    bool GetFiles();
    /**
     * @brief:compare the fileName with the string language-country
     *
     * @return 0:the file name is language-countryXXXX.json
     *         1:the file name is language -XXX.json
     *         2:the file name is language-otherCountryXXX.json
     */
    int8_t CompareFileName(const char *name);
    /**
     * @Brief get the locale string and split it by ','
     */
    void SetLanguage();

    /**
     * @Brief: get the positon of delemeter after index
     * @return if the index is upper than the length of string, return -1
     * else if the index is not defined in string, return the length, else return the position of it
     */
    int IndexOf(const char *string, char delemeter, int index);

    /**
     * @Brief: split the string defined in value by '|', and get value in the split string
     * For example: the string is car|cars, if the value of param is odd, assign value car,else cars
     */
#ifdef LOCALIZATION_PLURAL
    char *GetPluralValue(char *value, jerry_value_t param);
    uint8_t FormatString(char *format, jerry_value_t arg, ListNode *&node, bool isPlural, jerry_value_t num);
    /**
     * @brief: get the value defined in param
     * @param: attrName:the attrbute name in param, for example "name"
     *         param: the object defined attrName, for example {"name":"Jane"}
     * @return: the value in param
     */
    char *GetParamValue(char *attrName, jerry_value_t param, bool isPlural);
#else
    uint8_t FormatString(char *format, jerry_value_t arg, ListNode *&node, jerry_value_t num);
    char *GetParamValue(char *attrName, jerry_value_t param);
#endif

    /**
     * @Brief: sort the file name alphabetical order
     */
    void SortFileName(ListNode *node);

    void MergeList(ListNode *&destination, ListNode *source);

    uint8_t curFileIndex_;  // the file index current read
    uint8_t totalFiles_;
    char *countries_; // the current country and origion
    char *language_;  // the current system language
    char leftDelemeter_;
    char rightDelemeter_;
    char *filePath_;
    ListNode *fileList_;
#if (defined(_WIN32) || defined(_WIN64))
    bool ReadWinFile(ListNode *&languageFile, ListNode *&countryFile);
#else
    bool ReadFile(ListNode *&languageFile, ListNode *&countryFile);
#endif
};
} // namespace ACELite
} // namespace OHOS
#endif // LOCALIZATION_MODULE
#endif // OHOS_ACELITE_CJSON_PARSER_H
