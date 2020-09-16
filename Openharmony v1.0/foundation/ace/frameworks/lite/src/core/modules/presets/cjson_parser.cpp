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

#include "cjson_parser.h"
#ifdef FEATURE_LOCALIZATION_MODULE
#include "ace_log.h"
#include "global.h"
#include "js_fwk_common.h"
#if (defined(_WIN32) || defined(_WIN64))
#include <io.h>
#else
#include "file.h"
#endif
#if ENABLED(SECURE_C_FUNCTION)
#include "securec.h"
#endif
#include "ui_text_language.h"
#include <string.h>

namespace OHOS {
namespace ACELite {
CJSONParser::CJSONParser()
    : curFileIndex_(0),
      totalFiles_(0),
      countries_(nullptr),
      language_(nullptr),
      filePath_(nullptr),
      fileList_(nullptr)
{
    char left = '{';
    leftDelemeter_ = left;
    char right = '}';
    rightDelemeter_ = right;
}

bool CJSONParser::Init()
{
    const char * const filePath = JsAppContext::GetInstance()->GetCurrentAbilityPath();
    const char * const folderName = "i18n";
    filePath_ = RelocateResourceFilePath(filePath, folderName);
    return (filePath_ != nullptr);
}

bool CJSONParser::ChangeJsonFile(cJSON *&currentItem)
{
    if (currentItem != nullptr) { // if the currentItem is not null, it must be free
        cJSON_Delete(currentItem);
        currentItem = nullptr;
    }
    SetLanguage();     // get the new locale string
    if (totalFiles_ == 0) {
        return false;
    }
    char *name = nullptr;
    if (curFileIndex_ == totalFiles_) {
        return false;
    } else {
        // read the next json resource file
        name = GetNode(fileList_, curFileIndex_ + 1);
    }
    char *content = ReadJSFile(filePath_, name);
    if (content == nullptr) {
        currentItem = nullptr;
        curFileIndex_++;
        return true;
    }
    currentItem = cJSON_Parse(content);
    ace_free(content);
    content = nullptr;
    // point to next file
    curFileIndex_++;
    return true;
}

bool CJSONParser::GetFiles()
{
    ClearNode(fileList_);
    totalFiles_ = 0;
    if (language_ == nullptr) {
        return false;
    }
    ListNode *languageFile = nullptr; // save language-XXX.json
    ListNode *countryFile = nullptr;  // save language-country-XXX.json
#if (defined(_WIN32) || defined(_WIN64))
    if (!ReadWinFile(languageFile, countryFile)) {
        ClearNode(languageFile);
        ClearNode(countryFile);
        return false;
    }
#else
    if (!ReadFile(languageFile, countryFile)) {
        ClearNode(languageFile);
        ClearNode(countryFile);
        return false;
    }
#endif
    SortFileName(fileList_);
    SortFileName(languageFile);
    SortFileName(countryFile);
    const char *defaultFileName = "en-US.json"; // add the default file name
    ListNode *defaultFile = new ListNode();
    if (defaultFile == nullptr) {
        // release the list which stores atrget file name, the fileList_ release in destructor or next used time
        ClearNode(languageFile);
        ClearNode(countryFile);
        return false;
    }
    defaultFile->value = SubStr(defaultFileName, 0, strlen(defaultFileName));
    totalFiles_++;
    MergeList(countryFile, defaultFile);
    MergeList(languageFile, countryFile);
    MergeList(fileList_, languageFile);
    return true;
}

#if (!defined(_WIN32) && !defined(_WIN64))
bool CJSONParser::ReadFile(ListNode *&languageFile, ListNode *&countryFile)
{
    void *files = FileOpenDir(filePath_);
    FileDirentInfo info;
    if (files == nullptr) {
        return false;
    }
    bool result = true;
    while ((FileReadDir(files, &info) == 0) && (totalFiles_ < UINT8_MAX)) {
        if ((info.name == nullptr) || (strncmp(info.name, language_, strlen(language_)) != 0)) {
            continue;
        }
        size_t infoNameLen = strlen(info.name);
        if (infoNameLen >= NAME_LENGTH_MAX) {
            break;
        }
        char *value = static_cast<char *>(ace_malloc(infoNameLen + 1));
        if (value == nullptr) {
            break;
        }
        errno_t error = strcpy_s(value, infoNameLen + 1, info.name);
        if (error != 0) {
            ace_free(value);
            value = nullptr;
            break;
        }
        bool check = true;
        int8_t fileType = CompareFileName(info.name);
        if (fileType == COUNTRY) {
            check = AddNode(fileList_, value);
        } else if (fileType == LANG) {
            check = AddNode(languageFile, value);
        } else if (fileType == OTHERCOUNTRY) {
            check = AddNode(countryFile, value);
        } else {
            ace_free(value);
            value = nullptr;
            result = false; // the country and lang list would be release if return false
            break;
        }
        if (!check) {
            ace_free(value);
            value = nullptr;
        } else {
            totalFiles_++;
        }
    }
    FileCloseDir(files);
    return result;
}
#endif

#ifdef LOCALIZATION_PLURAL
char *CJSONParser::FillPlaceholder(char *format, jerry_value_t arg, jerry_length_t num, bool isPlural)
#else
char *CJSONParser::FillPlaceholder(char *format, jerry_value_t arg, jerry_length_t num)
#endif // LOCALIZATION_PLURAL
{
    if (format == nullptr) {
        return nullptr;
    }
#ifdef LOCALIZATION_PLURAL
    if (isPlural) {
        format = GetPluralValue(format, arg);
        if (format == nullptr) {
            return nullptr;
        }
    }
#endif
    ListNode *values = nullptr; // store the value after split.
#ifdef LOCALIZATION_PLURAL
    uint8_t length = FormatString(format, arg, values, isPlural, num);
    if (isPlural) {
        ACE_FREE(format);
    }
#else
    uint8_t length = FormatString(format, arg, values, num);
#endif // LOCALIZATION_PLURAL
    char *result = nullptr;
    if (values != nullptr) {
        result = ToString(values, length);
        ClearNode(values);
    }
    return result;
}

#ifdef LOCALIZATION_PLURAL
uint8_t CJSONParser::FormatString(char *format, jerry_value_t arg, ListNode *&values, bool isPlural, jerry_length_t num)
#else
uint8_t CJSONParser::FormatString(char *format, jerry_value_t arg, ListNode *&values, jerry_length_t num)
#endif
{
    uint8_t length = 0;
    int index = 0;
    int leftIndex = IndexOf(format, leftDelemeter_, index); // get the index of '{'
    while (leftIndex >= 0) {
        char* value = SubStr(format, index, leftIndex - index);
        if (AddNode(values, value)) {
            length++;
        } else {
            ACE_FREE(value);
        }
        leftIndex++;
        index = IndexOf(format, rightDelemeter_, leftIndex); // get the index of '}'
        if (index > 0 && num > 1) {
            char *content = nullptr;
            content = SubStr(format, leftIndex, index - leftIndex);
#ifdef LOCALIZATION_PLURAL
            char *contentValue = GetParamValue(content, arg, isPlural);
#else
            char *contentValue = GetParamValue(content, arg);
#endif // LOCALIZATION_PLURAL
            if (AddNode(values, contentValue)) {
                length++;
            } else {
                ACE_FREE(contentValue);
            }
        }
        if ((index > 0) && (index < strlen(format))) {
            index++; // move the index '}' to the next char
        } else {
            // add the remain character to node.eg.the value is {count}aa, add the last aa to the node
            char* currentVal = SubStr(format, index, strlen(format) - index);
            if (AddNode(values, currentVal)) {
                length++;
            } else {
                ACE_FREE(currentVal);
            }
        }
        leftIndex = IndexOf(format, leftDelemeter_, index);
    }
    if (leftIndex < 0 && (index < strlen(format))) {
        char* currentVal = SubStr(format, index, strlen(format) - index);
        if (AddNode(values, currentVal)) {
            length++;
        } else {
            ACE_FREE(currentVal);
        }
    }
    return length;
}

#ifdef LOCALIZATION_PLURAL
char *CJSONParser::GetPluralValue(char *value, jerry_value_t param)
{
    ListNode *plurals = nullptr;
    int defaultNum = jerry_value_is_number(param) ? IntegerOf(param) : 1;
    const char delemeter = '|'; // if the function is get plural, split the value in json by '|'
    int len = Split(value, delemeter, plurals);
    const int maxLen = 2;
    // get the index in plural array
    if (len <= maxLen) {
        value = (defaultNum != 1) ? GetNode(plurals, 1) : GetNode(plurals, len);
    } else {
        int index = (abs(defaultNum) < maxLen) ? abs(defaultNum) : maxLen; // get the index in plurals
        value = GetNode(plurals, len - index);
    }
    char *result = SubStr(value, 0, strlen(value));
    if (plurals) {
        ClearNode(plurals);
    }
    return result;
}
#endif // LOCALIZATION_PLURAL

void CJSONParser::ResetIndex()
{
    curFileIndex_ = 0;
}

bool CJSONParser::AddNode(ListNode *&head, char *current)
{
    if (current == nullptr || strlen(current) == 0) {
        return false;
    }
    ListNode *node = new ListNode();
    if (node == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create node failed");
        return false;
    }
    node->next = head;
    node->value = current;
    head = node;
    return true;
}

char *CJSONParser::GetNode(ListNode *node, int index)
{
    for (int i = 0; i < index - 1; i++) {
        if (node == nullptr) {
            break;
        }
        node = node->next;
    }
    return (node == nullptr) ? nullptr : node->value;
}

void CJSONParser::ClearNode(ListNode *&node)
{
    while (node != nullptr) {
        ListNode *current = node->next;
        ACE_FREE(node->value);
        delete node;
        node = current;
    }
}

char *CJSONParser::ToString(ListNode *node, uint8_t length)
{
    if (node == nullptr || (length == 0)) {
        return nullptr;
    }
    char **temp = static_cast<char **>(ace_malloc(length * sizeof(char*)));
    if (temp == nullptr) {
        return nullptr;
    }
    // reverse node value
    uint8_t index = 0;
    uint16_t strLength = 0; // the length of result
    while (node != nullptr) {
        if ((length - index - 1 >= 0) && (node->value != nullptr)) {
            if (strLength > (UINT16_MAX - (uint16_t)(strlen(node->value)))) {
                ACE_FREE(temp);
                return nullptr;
            }
            temp[length - 1 - index] = node->value;
            strLength += strlen(node->value);
        }
        node = node->next;
        index++;
    }
    if (strLength == UINT16_MAX) {
        HILOG_ERROR(HILOG_MODULE_ACE, "the str length is too long");
        ACE_FREE(temp);
        return nullptr;
    }
    strLength++;
    char *result = static_cast<char *>(ace_malloc(strLength));
    if (result == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc localization result failed");
        ACE_FREE(temp);
        return nullptr;
    }
    // convert the value in node to string
    if (strcpy_s(result, strLength, temp[0]) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "merge string failed");
        ACE_FREE(result);
        ACE_FREE(temp);
        return nullptr;
    }
    for (int i = 1; i < length; i++) {
        if (strcat_s(result, strLength, temp[i]) != 0) {
            HILOG_INFO(HILOG_MODULE_ACE, "merge string failed");
            ACE_FREE(result);
            ACE_FREE(temp);
            return nullptr;
        }
    }
    ACE_FREE(temp);
    return result;
}

char *CJSONParser::SubStr(const char *src, size_t start, size_t length)
{
    if (src == nullptr || start >= strlen(src)) {
        return nullptr;
    }
    if (length >= UINT8_MAX) {
        HILOG_ERROR(HILOG_MODULE_ACE, "the length is too long");
        return nullptr;
    }
    size_t len = length + 1;
    char *result = static_cast<char *>(ace_malloc(len));
    if (result == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc failed");
        return nullptr;
    }
    errno_t error = strncpy_s(result, len, src + start, length);
    if (error != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "copy string failed");
        ACE_FREE(result);
        return nullptr;
    }
    result[length] = '\0';
    return result;
}

int8_t CJSONParser::CompareFileName(const char *name)
{
    if ((name == nullptr) || (language_ == nullptr)) {
        return ERRORCODE;
    }
    size_t languageLen = strlen(language_);
    if (languageLen >= UINT8_MAX) {
        return ERRORCODE;
    }
    const char delemeter = '-';
    const int countryLen = 2;
    size_t minLen = languageLen + 1 + countryLen; // the length of .json
    if ((strlen(name) <= minLen) || (name[languageLen] != delemeter)) {
        return 1;
    } else {
        int result = COUNTRY;
        if (countries_ == nullptr) {
            return ERRORCODE;
        }
        char *countryName = static_cast<char *>(ace_malloc(countryLen + 1));
        if (countryName == nullptr) {
            return ERRORCODE;
        }
        for (int i = 0; i < countryLen; i++) {
            countryName[i] = name[languageLen + 1 + i];
        }
        countryName[countryLen] = '\0';
        if (strstr(countries_, countryName) == nullptr) {
            const char startIndex = 'A';
            int index = countryName[0] - startIndex;
            const char * const countries = GetCountries(index);
            if ((countries != nullptr) && (IndexOf(const_cast<char *>(countries), countryName[1], 0) > 0)) {
                result = OTHERCOUNTRY;
            } else {
                result = LANG;
            }
        }
        ace_free(countryName);
        countryName = nullptr;
        return result;
    }
}

void CJSONParser::SetLanguage()
{
    char* currentLanguage = static_cast<char*>(ace_malloc(MAX_LANGUAGE_LENGTH));
    if (currentLanguage == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "malloc language failed\n");
        return;
    }
    if (GLOBAL_GetLanguage(currentLanguage, MAX_LANGUAGE_LENGTH) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get language failed\n");
        ace_free(currentLanguage);
        currentLanguage = nullptr;
        return;
    }

    char* currentOrigion = static_cast<char*>(ace_malloc(MAX_REGION_LENGTH));
    if (currentOrigion == nullptr) {
        ace_free(currentLanguage);
        currentLanguage = nullptr;
        return;
    }
    if (GLOBAL_GetRegion(currentOrigion, MAX_REGION_LENGTH) != 0) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get origion failed");
        ace_free(currentOrigion);
        currentOrigion = nullptr;
        ace_free(currentLanguage);
        currentLanguage = nullptr;
        return;
    }
    if ((language_ != nullptr) && (strcmp(currentLanguage, language_) == 0)
        && (countries_ != nullptr) && (strcmp(currentOrigion, countries_) == 0)) {
        ace_free(currentLanguage);
        currentLanguage = nullptr;
        ace_free(currentOrigion);
        currentOrigion = nullptr;
        return;
    }
    ACE_FREE(language_);
    language_ = currentLanguage;
    ACE_FREE(countries_);
    countries_ = currentOrigion;
    if (!GetFiles()) { // get the files whose name begins with the local string
        return;
    }
    curFileIndex_ = 0;
}

#if (defined(_WIN32) || (defined(_WIN64)))
bool CJSONParser::ReadWinFile(ListNode *&languageFile, ListNode *&countryFile)
{
    _finddata_t file;
    intptr_t opendir;
    const char * const match = "*.*";
    char* fileDir = RelocateResourceFilePath(filePath_, match);
    if (fileDir == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get localization path failed");
        return false;
    }
    if ((opendir = _findfirst(fileDir, &file)) == -1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "file not defined");
        ACE_FREE(fileDir);
        return false;
    }
    bool result = true;
    // get the file start with the split locale string, for example, en-US_XXX.json
    while ((_findnext(opendir, &file) == 0) && (totalFiles_ < UINT8_MAX)) {
        // if the file name is not start with the language , go to the next file
        if (strncmp(file.name, language_, strlen(language_)) != 0) {
            continue;
        }
        char *value = SubStr(file.name, 0, strlen(file.name));
        bool check = true;
        int8_t fileType = CompareFileName(file.name);
        if (fileType == COUNTRY) {
            check = AddNode(fileList_, value);
        } else if (fileType == LANG) {
            check = AddNode(languageFile, value);
        } else if (fileType == OTHERCOUNTRY) {
            check = AddNode(countryFile, value);
        } else {
            ACE_FREE(value);
            result = false; // the country and lang list would be release if return false
            break;
        }
        if (!check) {
            ACE_FREE(value);
        } else {
            totalFiles_++;
        }
    }
    _findclose(opendir);
    ACE_FREE(fileDir);
    return result;
}
#endif

uint8_t CJSONParser::Split(const char *target, char delemeter, ListNode *&node)
{
    if (target == nullptr) {
        return 0;
    }
    uint8_t nodeCount = 0;
    char *current = nullptr;
    int startPos = 0;
    // get the position of delemeter
    int pos = IndexOf(target, delemeter, startPos);
    while (pos != -1) {
        // add the value between startPos and index to node
        current = SubStr(target, startPos, pos - startPos);
        if (AddNode(node, current)) {
            nodeCount++;
        } else {
            ACE_FREE(current);
        }
        startPos = pos + 1;
        pos = IndexOf(target, delemeter, startPos);
    }
    if ((startPos != -1) && (startPos < strlen(target))) {
        current = SubStr(target, startPos, strlen(target) - startPos);
        if (AddNode(node, current)) {
            nodeCount++;
        } else {
            ACE_FREE(current);
        }
    }
    // deal the key from lastIndex to strlen(target), the last find would return -1
    return nodeCount;
}

int CJSONParser::IndexOf(const char *string, char delemeter, int index)
{
    if (string == nullptr) {
        return -1;
    }
    if ((index >= strlen(string)) || (index < 0) || (strlen(string) >= INT8_MAX)) {
        return -1;
    }
    int length = strlen(string);
    int i = index;
    do {
        if (string[i] == delemeter) {
            return i;
        }
        i++;
    } while (i < length);
    // if the delemeter is not find return the length of string
    return -1;
}

#ifdef LOCALIZATION_PLURAL
char *CJSONParser::GetParamValue(char *attrName, jerry_value_t param, bool isPlural)
#else
char *CJSONParser::GetParamValue(char *attrName, jerry_value_t param)
{
    char *contentValue = nullptr; // store the value defined in param
    uint16_t contentLen = 0;
#ifdef LOCALIZATION_PLURAL
    if (jerry_value_is_number(param)) {
        contentValue = MallocStringOf(param, &contentLen);
    }
#else
    jerry_value_t propName = jerry_create_string(reinterpret_cast<jerry_char_t *>(attrName));
    if (JerryHasProperty(param, propName)) { // get the placehoder {...} value defined in param
        jerry_value_t paramValue = jerry_get_property(param, propName);
        // the contentValue would be released in clearNode values
        contentValue = MallocStringOf(paramValue, &contentLen);
        jerry_release_value(paramValue);
    }
    jerry_release_value(propName);
#endif
    // if the length of attrVal is 0, the node wouldn't add to the list
    if ((contentValue != nullptr) && contentLen != 0) {
        return contentValue;
    } else {
        ACE_FREE(contentValue); // if the contentValue is \0
        return nullptr;
    }
}
#endif

void CJSONParser::SortFileName(ListNode *node)
{
    if (node == nullptr || (node->next == nullptr)) {
        return;
    }
    ListNode *current = node;
    ListNode *compare = nullptr;
    const int suffixLen = 5;
    while (current != nullptr) {
        compare = current->next;
        int currentLen = strlen(current->value);
        while (compare != nullptr) {
            int min = (currentLen < strlen(compare->value)) ? currentLen : strlen(compare->value);
            int compareResult = strncmp(compare->value, current->value, min - suffixLen);
            // when the file name is zh-CN.json and zh-CN-1.json, the sort result is zh-CN.json,zh-CN-1.json
            if ((compareResult < 0) || ((compareResult == 0) && (min != currentLen))) {
                char *value = compare->value;
                compare->value = current->value;
                current->value = value;
            }
            compare = compare->next;
        }
        current = current->next;
    }
}

const char *CJSONParser::GetCountries(int8_t index)
{
    if ((index >= maxLen_) || (index < 0)) {
        return nullptr;
    }
    return allCountries_[index];
}

void CJSONParser::MergeList(ListNode *&destination, ListNode *source)
{
    // merge two list
    if (source == nullptr) {
        return;
    }
    if (destination == nullptr) {
        destination = source;
        return;
    }
    ListNode *current = destination;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = source;
}
} // namespace ACELite
} // namespace OHOS
#endif
