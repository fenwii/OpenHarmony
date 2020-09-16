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

#ifndef OHOS_GLOBAL_UTILS_H
#define OHOS_GLOBAL_UTILS_H

#include <stdint.h>

#include "global.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus

#define LOCALE_ELEMENT_NUM 3
typedef struct GlobalUtilsImpl {
    uint32_t (*GetOffsetByLocale)(const char *path, char *locale, uint32_t length);
    uint32_t (*GetDefaultOffsetValue)(int32_t file);
    uint32_t (*GetKeyValue)(int32_t file);
    int32_t (*GetIdItem)(int32_t file, uint32_t offset, IdItem *idItem);
    uint32_t (*GetIdHeaderOffsetByLocale)(char *locale, Key *keys, uint32_t configNum);
    int32_t (*GetIdHeaderByOffset)(int32_t file, uint32_t offset, IdHeader *idHeader);
    int32_t (*SplitLocale)(char *src, char **dest, int32_t *num);
    int32_t (*CheckFilePath)(const char *path, char *realResourcePath, int32_t length);
} GlobalUtilsImpl;

typedef struct LocaleItem {
    uint32_t language;
    uint32_t script;
    uint32_t region;
} LocaleItem;

GlobalUtilsImpl *GetGlobalUtilsImpl(void);

inline static uint8_t ToLowerCase(uint8_t c)
{
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

#define MC_FAILURE -1
#define MC_SUCCESS 0

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // OHOS_GLOBAL_UTILS_H
