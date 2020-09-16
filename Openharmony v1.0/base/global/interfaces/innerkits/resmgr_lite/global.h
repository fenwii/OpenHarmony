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

#ifndef OHOS_GLOBAL_H
#define OHOS_GLOBAL_H

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus

#define RES_CONFIG_NUM_OFFSET 132
#define INDEX_DEFAULT_OFFSET  4
#define VALUE_LENGTH_OFFSET   2
#define OFFSET_VALUE_STEP     8
#define SCRIPT_LENGTH         4
#define ALL_PARAM_LENGTH      4
#define INVALID_OFFSET        0
#define MAX_LANGUAGE_LENGTH   4
#define MAX_REGION_LENGTH     4

typedef enum KeyType {
    LANGUAGES   = 0,
    REGION      = 1,
    RESOLUTION  = 2,
    ORIENTATION = 3,
    DEVICETYPE  = 4,
    SCRIPT      = 5,
    KEY_TYPE_MAX,
} KeyType;

typedef enum ResType {
    VALUES    = 0,
    ANIMATION = 1,
    DRAWABLE  = 2,
    LAYOUT    = 3,
    MENU      = 4,
    MIPMAP    = 5,
    RAW       = 6,
    XML       = 7,

    INTEGER          = 8,
    STRING           = 9,
    STRINGARRAY      = 10,
    INTARRAY         = 11,
    BOOLEAN_         = 12,
    DIMEN            = 13,
    COLOR            = 14,
    ID               = 15,
    THEME            = 16,
    PLURALS          = 17,
    MY_FLOAT         = 18,
    MEDIA            = 19,
    PROF             = 20,
    SVG              = 21,
    INVALID_RES_TYPE = -1,
} ResType;

typedef struct KeyParam {
    KeyType type;
    uint32_t value;
} KeyParam;

typedef struct Key {
    uint32_t offset;
    uint32_t keysCount;
    KeyParam *keyParams;
} Key;

typedef struct IdParam {
    uint32_t id;
    uint32_t offset;
} IdParam;

typedef struct IdHeader {
    uint32_t count;
    IdParam *idParams;
} IdHeader;

typedef struct IdItem {
    uint32_t size;
    ResType resType;
    uint32_t id;
    uint16_t valueLen;
    char *value;
    uint16_t nameLen;
    char *name;
} IdItem;

int32_t GLOBAL_GetValueById(uint32_t id, const char *path, char **value);
int32_t GLOBAL_GetValueByName(const char *name, const char *path, char **value);
void GLOBAL_ConfigLanguage(const char *appLanguage);
int32_t GLOBAL_GetLanguage(char *language, uint8_t len);
int32_t GLOBAL_GetRegion(char *region, uint8_t len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // OHOS_GLOBAL_H
