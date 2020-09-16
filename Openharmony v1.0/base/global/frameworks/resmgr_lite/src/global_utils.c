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

#include "global_utils.h"

#include <fcntl.h>
#include <limits.h>
#include <securec.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_ID_ITEM_NUM    0x7F
#define MAX_RES_CONFIG_NUM 0x10
#define MAX_ITEM_LENGTH    0xFF

enum LocaleIndex {
    LANGUAGE_INDEX = 0,
    SCRIPT_INDEX =   1,
    REGION_INDEX =   2
};

static int32_t Split(char *src, const char *separator, char **dest, int32_t *num);
static int32_t SplitLocale(char *src, char **dest, int32_t *num);
static uint32_t ConvertUint8ArrayToUint32(const uint8_t *array, int32_t count);
static uint32_t GetValueFromLocale(const char *locale);
static void SetLocaleItemViaKeys(KeyParam keyParam, LocaleItem *localeItem);
static uint32_t FindOffsetByLanguage(const char *language, Key *keys, uint32_t configNum);
static uint32_t FindOffsetByTwoParam(char **resConfig, Key *keys, uint32_t configNum);
static uint32_t FindOffsetByAllParam(char **resConfig, Key *keys, uint32_t configNum);
static uint32_t GetIdHeaderOffsetByCount(char **resConfig, Key *keys, uint32_t configNum, int32_t count);
static uint32_t GetOffsetByLocale(const char *path, char *locale, uint32_t length);
static uint32_t GetDefaultOffsetValue(int32_t file);
static uint32_t GetKeyValue(int32_t file);
static int32_t GetIdItem(int32_t file, uint32_t offset, IdItem *idItem);
static void FreeKeyParams(Key *keys, int32_t count);
static int32_t GetKeyParams(int32_t file, Key *keys, uint32_t resConfigNum);
static uint32_t GetIdHeaderOffsetByLocale(char *locale, Key *keys, uint32_t configNum);
static int32_t GetIdHeaderByOffset(int32_t file, uint32_t offset, IdHeader *idHeader);
static int32_t CheckFilePath(const char *path, char *realResourcePath, int32_t length);

static GlobalUtilsImpl g_globalUtilsImpl = {
    .GetOffsetByLocale = GetOffsetByLocale,
    .GetDefaultOffsetValue = GetDefaultOffsetValue,
    .GetKeyValue = GetKeyValue,
    .GetIdItem = GetIdItem,
    .GetIdHeaderOffsetByLocale = GetIdHeaderOffsetByLocale,
    .GetIdHeaderByOffset = GetIdHeaderByOffset,
    .SplitLocale = SplitLocale,
    .CheckFilePath = CheckFilePath,
};

static uint32_t g_defaultIdHeaderOffset = INVALID_OFFSET;

static int32_t Split(char *src, const char *separator, char **dest, int32_t *num)
{
    char *pNext = NULL;
    int32_t count = 0;
    if (src == NULL || strlen(src) == 0 || separator == NULL || strlen(separator) == 0) {
        return MC_FAILURE;
    }
    pNext = strtok(src, separator);
    while (pNext != NULL) {
        if (count >= LOCALE_ELEMENT_NUM) {
            return MC_FAILURE;
        }
        *dest++ = pNext;
        ++count;
        pNext = strtok(NULL, separator);
    }
    *num = count;
    return MC_SUCCESS;
}

static int32_t SplitLocale(char *src, char **dest, int32_t *num)
{
    if (src == NULL || strlen(src) == 0 || dest == NULL || num == NULL) {
        return MC_FAILURE;
    }
    if (strchr(src, '-') != NULL) {
        (void)Split(src, "-", dest, num);
    } else if (strchr(src, '_') != NULL) {
        (void)Split(src, "_", dest, num);
    } else {
        dest[0] = src;
    }
    return MC_SUCCESS;
}

static uint32_t ConvertUint8ArrayToUint32(const uint8_t *array, int32_t count)
{
    if (array == NULL) {
        return 0;
    }
    uint32_t value = 0;
    uint8_t offset = 0;
    // caculate big endian array, e.g. "ne\0\0" = 'n' + 'e' << 8 + 0 << 16 + 0 << 24
    for (int32_t i = 0; i < count; i++) {
        value += (array[i] << offset);
        offset += OFFSET_VALUE_STEP;
    }
    return value;
}

static uint32_t GetValueFromLocale(const char *locale)
{
    if (locale == NULL) {
        return 0;
    }
    uint32_t value = 0;
    uint32_t offset = 0;
    // caculate little endian array, e.g. "en" = 'n' + 'e' << 8
    for (int32_t i = strlen(locale) - 1; i >= 0; i--) {
        // locale needs to be case insensitive
        value += (ToLowerCase((uint8_t)locale[i]) << offset);
        offset += OFFSET_VALUE_STEP;
    }
    return value;
}

static uint32_t FindOffsetByLanguage(const char *language, Key *keys, uint32_t configNum)
{
    if (language == NULL || keys == NULL) {
        return INVALID_OFFSET;
    }
    uint32_t value = GetValueFromLocale(language);
    for (uint32_t i = 0; i < configNum; i++) {
        for (uint32_t j = 0; j < keys[i].keysCount; j++) {
            if (keys[i].keyParams[j].type == LANGUAGES && keys[i].keyParams[j].value == value) {
                return keys[i].offset;
            }
        }
    }
    return INVALID_OFFSET;
}

static void SetLocaleItemViaKeys(KeyParam keyParam, LocaleItem *localeItem)
{
    if (localeItem == NULL) {
        return;
    }
    switch (keyParam.type) {
        case LANGUAGES:
            localeItem->language = keyParam.value;
            break;
        case SCRIPT:
            localeItem->language = keyParam.value;
            break;
        case REGION:
            localeItem->region = keyParam.value;
            break;
        default:
            // unspport type
            break;
    }
}

static uint32_t FindOffsetByTwoParam(char **resConfig, Key *keys, uint32_t configNum)
{
    if (resConfig == NULL || keys == NULL) {
        return INVALID_OFFSET;
    }
    uint32_t offset = INVALID_OFFSET;
    uint32_t languageValue = GetValueFromLocale(resConfig[LANGUAGE_INDEX]);
    uint32_t secondValue = GetValueFromLocale(resConfig[1]); // secondValue may be script or region
    uint32_t len = strlen(resConfig[1]);
    for (uint32_t i = 0; i < configNum; i++) {
        LocaleItem locale = {0, 0, 0};
        for (uint32_t j = 0; j < keys[i].keysCount; j++) {
            SetLocaleItemViaKeys(keys[i].keyParams[j], &locale);
        }
        if (len == SCRIPT_LENGTH) { // script length is fixed at 4
            // if all matched, just return the offset
            if (languageValue == locale.language && secondValue == locale.script) {
                offset = keys[i].offset;
                break;
            }
            // if only language matched, use 1st found language
            if (offset == INVALID_OFFSET && languageValue == locale.language) {
                offset = keys[i].offset;
            }
        } else {
            // if all matched, just return the offset
            if (languageValue == locale.language && secondValue == locale.region) {
                offset = keys[i].offset;
                break;
            }
            // if only language matched, use 1st found language
            if (offset == INVALID_OFFSET && languageValue == locale.language) {
                offset = keys[i].offset;
            }
        }
    }
    return offset;
}

static uint32_t FindOffsetByAllParam(char **resConfig, Key *keys, uint32_t configNum)
{
    if (resConfig == NULL || keys == NULL) {
        return INVALID_OFFSET;
    }
    uint32_t offset = INVALID_OFFSET;
    uint32_t languageValue = GetValueFromLocale(resConfig[LANGUAGE_INDEX]);
    uint32_t scriptValue = GetValueFromLocale(resConfig[SCRIPT_INDEX]);
    uint32_t regionValue = GetValueFromLocale(resConfig[REGION_INDEX]);
    uint32_t retOffsets[ALL_PARAM_LENGTH] = {0};
    for (uint32_t i = 0; i < configNum; i++) {
        LocaleItem locale = {0, 0, 0};
        for (uint32_t j = 0; j < keys[i].keysCount; j++) {
            SetLocaleItemViaKeys(keys[i].keyParams[j], &locale);
        }
        // if all matched, save offset to retOffsets[0], the highest priority, and stop searching
        if (retOffsets[0] == INVALID_OFFSET &&
            languageValue == locale.language && scriptValue == locale.script && regionValue == locale.region) {
            retOffsets[0] = keys[i].offset; // retOffsets[0] has the highest priority
            break;
        }
        // if language and region matched, save 1st found offset to retOffsets[1]
        if (retOffsets[1] == INVALID_OFFSET && languageValue == locale.language && regionValue == locale.region) {
            retOffsets[1] = keys[i].offset; // retOffsets[1] has the second highest priority
            continue;
        }
        // if language and script matched, save 1st found offset to retOffsets[2]
        if (retOffsets[2] == INVALID_OFFSET && languageValue == locale.language && scriptValue == locale.script) {
            retOffsets[2] = keys[i].offset; // retOffsets[2] has the third highest priority
            continue;
        }
        // if only language matched, save 1st found offset to retOffsets[3], the lowest priority
        if (retOffsets[3] == INVALID_OFFSET && languageValue == locale.language) {
            retOffsets[3] = keys[i].offset; // retOffsets[3] has the lowest priority
            continue;
        }
    }
    // search the existed highest priority retOffsets[i]
    for (uint32_t i = 0; i < ALL_PARAM_LENGTH; i++) {
        if (retOffsets[i] != INVALID_OFFSET) {
            offset = retOffsets[i];
            break;
        }
    }
    return offset;
}

static uint32_t GetIdHeaderOffsetByCount(char **resConfig, Key *keys, uint32_t configNum, int32_t count)
{
    if (resConfig == NULL || keys == NULL) {
        return INVALID_OFFSET;
    }
    uint32_t offset = INVALID_OFFSET;
    switch (count) {
        case 1: // locale has only 1 element which is language
            offset = FindOffsetByLanguage(resConfig[0], keys, configNum);
            break;
        case 2: // locale has 2 element: language & script, or language & region
            offset = FindOffsetByTwoParam(resConfig, keys, configNum);
            break;
        case 3: // locale has all 3 element: language script, and region
            offset = FindOffsetByAllParam(resConfig, keys, configNum);
            break;
        default:
            break;
    }
    return offset;
}

static void FreeKeyParams(Key *keys, int32_t count)
{
    if (keys == NULL) {
        return;
    }
    for (int32_t i = 0; i < count; i++) {
        if (keys[i].keysCount != 0) {
            free(keys[i].keyParams);
            keys[i].keyParams = NULL;
            keys[i].keysCount = 0;
        }
    }
}

static int32_t GetKeyParams(int32_t file, Key *keys, uint32_t resConfigNum)
{
    if (file < 0 || keys == NULL) {
        return MC_FAILURE;
    }
    g_defaultIdHeaderOffset = INVALID_OFFSET;
    for (int32_t i = 0; i < resConfigNum; ++i) {
        (void)lseek(file, INDEX_DEFAULT_OFFSET, SEEK_CUR); // skip the "KEYS" header
        keys[i].offset = GetDefaultOffsetValue(file);
        keys[i].keysCount = GetDefaultOffsetValue(file);
        if (keys[i].keysCount == 0) {
            g_defaultIdHeaderOffset = keys[i].offset;
            continue;
        }
        if (keys[i].keysCount > KEY_TYPE_MAX) {
            FreeKeyParams(keys, i);
            return MC_FAILURE;
        }
        keys[i].keyParams = (KeyParam *)malloc(sizeof(KeyParam) * keys[i].keysCount);
        if (keys[i].keyParams == NULL) {
            FreeKeyParams(keys, i);
            return MC_FAILURE;
        }
        for (int32_t j = 0; j < keys[i].keysCount; j++) {
            keys[i].keyParams[j].type = (KeyType)GetDefaultOffsetValue(file);
            keys[i].keyParams[j].value = GetKeyValue(file);
        }
    }
    return MC_SUCCESS;
}

static int32_t CheckFilePath(const char *path, char *realResourcePath, int32_t length)
{
    if (length > PATH_MAX || length < 0) {
        return MC_FAILURE;
    }
#if (defined(_WIN32) || defined(_WIN64))
    if (!PathCanonicalizeA(path, realResourcePath)) {
        return MC_FAILURE;
    }
#else
    if (realpath(path, realResourcePath) == NULL) {
        return MC_FAILURE;
    }
#endif
    return MC_SUCCESS;
}

static uint32_t GetOffsetByLocale(const char *path, char *locale, uint32_t length)
{
    if (path == NULL || strlen(path) == 0 || locale == NULL || length == 0) {
        return INVALID_OFFSET;
    }
    char realResourcePath[PATH_MAX] = {0};
    if (CheckFilePath(path, realResourcePath, PATH_MAX) == MC_FAILURE) {
        return INVALID_OFFSET;
    }
    int32_t file = open(realResourcePath, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
    if (file < 0) {
        return INVALID_OFFSET;
    }
    (void)lseek(file, RES_CONFIG_NUM_OFFSET, SEEK_SET); // goto resConfigNum index, now is fixed at 132
    uint32_t resConfigNum = GetDefaultOffsetValue(file);
    if (resConfigNum > MAX_RES_CONFIG_NUM) {
        close(file);
        return INVALID_OFFSET;
    }
    Key *keys = (Key *)malloc(sizeof(Key) * resConfigNum);
    if (keys == NULL) {
        close(file);
        return INVALID_OFFSET;
    }
    int32_t ret = GetKeyParams(file, keys, resConfigNum);
    if (ret != MC_SUCCESS) {
        close(file);
        free(keys);
        return INVALID_OFFSET;
    }
    close(file);
    uint32_t offset = GetIdHeaderOffsetByLocale(locale, keys, resConfigNum);
    if (offset == INVALID_OFFSET) {
        offset = g_defaultIdHeaderOffset;
    }
    FreeKeyParams(keys, resConfigNum);
    free(keys);
    return offset;
}

static uint32_t GetDefaultOffsetValue(int32_t file)
{
    uint8_t cache[INDEX_DEFAULT_OFFSET] = {0};
    int32_t ret = read(file, cache, INDEX_DEFAULT_OFFSET);
    if (ret != INDEX_DEFAULT_OFFSET) {
        return 0;
    }
    return ConvertUint8ArrayToUint32(cache, INDEX_DEFAULT_OFFSET);
}

static uint32_t GetKeyValue(int32_t file)
{
    uint32_t value;
    uint8_t cache[INDEX_DEFAULT_OFFSET] = {0};
    int32_t ret = read(file, cache, INDEX_DEFAULT_OFFSET);
    if (ret != INDEX_DEFAULT_OFFSET) {
        return 0;
    }
    for (int32_t i = 0; i < INDEX_DEFAULT_OFFSET; i++) {
        cache[i] = ToLowerCase(cache[i]); // Key value is case insensitive
    }
    value = ConvertUint8ArrayToUint32(cache, INDEX_DEFAULT_OFFSET);
    return value;
}

static int32_t GetIdItem(int32_t file, uint32_t offset, IdItem *idItem)
{
    if (offset == INVALID_OFFSET || file == -1 || idItem == NULL) {
        return MC_FAILURE;
    }
    uint8_t defaultCache[INDEX_DEFAULT_OFFSET] = {0};
    uint8_t lengthCache[VALUE_LENGTH_OFFSET] = {0};
    (void)lseek(file, offset, SEEK_SET);

    (void)read(file, defaultCache, INDEX_DEFAULT_OFFSET);
    idItem->size = ConvertUint8ArrayToUint32(defaultCache, INDEX_DEFAULT_OFFSET);

    (void)read(file, defaultCache, INDEX_DEFAULT_OFFSET);
    idItem->resType = (ResType)ConvertUint8ArrayToUint32(defaultCache, INDEX_DEFAULT_OFFSET);

    (void)read(file, defaultCache, INDEX_DEFAULT_OFFSET);
    idItem->id = ConvertUint8ArrayToUint32(defaultCache, INDEX_DEFAULT_OFFSET);

    (void)read(file, lengthCache, VALUE_LENGTH_OFFSET);
    idItem->valueLen = ConvertUint8ArrayToUint32(lengthCache, VALUE_LENGTH_OFFSET);
    if (idItem->valueLen == 0 || idItem->valueLen > MAX_ITEM_LENGTH) {
        return MC_FAILURE;
    }

    idItem->value = (char *)malloc(idItem->valueLen);
    if (idItem->value == NULL) {
        return MC_FAILURE;
    }
    (void)memset_s(idItem->value, idItem->valueLen, 0, idItem->valueLen);
    (void)read(file, idItem->value, idItem->valueLen);

    (void)read(file, lengthCache, VALUE_LENGTH_OFFSET);
    idItem->nameLen = ConvertUint8ArrayToUint32(lengthCache, VALUE_LENGTH_OFFSET);
    if (idItem->nameLen == 0 || idItem->nameLen > MAX_ITEM_LENGTH) {
        free(idItem->value);
        idItem->value = NULL;
        return MC_FAILURE;
    }

    idItem->name = (char *)malloc(idItem->nameLen);
    if (idItem->name == NULL) {
        free(idItem->value);
        idItem->value = NULL;
        return MC_FAILURE;
    }
    (void)memset_s(idItem->name, idItem->nameLen, 0, idItem->nameLen);
    (void)read(file, idItem->name, idItem->nameLen);

    return MC_SUCCESS;
}

static uint32_t GetIdHeaderOffsetByLocale(char *locale, Key *keys, uint32_t configNum)
{
    if (locale == NULL || keys == NULL) {
        return INVALID_OFFSET;
    }
    char *resConfig[LOCALE_ELEMENT_NUM] = {0};
    int32_t count = 0;
    if (strchr(locale, '-') != NULL) {
        (void)Split(locale, "-", resConfig, &count);
    } else if (strchr(locale, '_') != NULL) {
        (void)Split(locale, "_", resConfig, &count);
    } else {
        resConfig[0] = locale;
    }
    return GetIdHeaderOffsetByCount(resConfig, keys, configNum, count);
}

static int32_t GetIdHeaderByOffset(int32_t file, uint32_t offset, IdHeader *idHeader)
{
    if (file == -1 || offset == INVALID_OFFSET || idHeader == NULL) {
        return MC_FAILURE;
    }

    (void)lseek(file, (int32_t)offset + INDEX_DEFAULT_OFFSET, SEEK_SET); // skip the "IDSS" header
    idHeader->count = GetDefaultOffsetValue(file);
    if (idHeader->count > MAX_ID_ITEM_NUM) {
        return MC_FAILURE;
    }
    idHeader->idParams = (IdParam *)malloc(sizeof(IdParam) * idHeader->count);
    if (idHeader->idParams == NULL) {
        return MC_FAILURE;
    }
    for (uint32_t i = 0; i < idHeader->count; i++) {
        idHeader->idParams[i].id = GetDefaultOffsetValue(file);
        idHeader->idParams[i].offset = GetDefaultOffsetValue(file);
    }
    return MC_SUCCESS;
}

GlobalUtilsImpl *GetGlobalUtilsImpl(void)
{
    return &g_globalUtilsImpl;
}
