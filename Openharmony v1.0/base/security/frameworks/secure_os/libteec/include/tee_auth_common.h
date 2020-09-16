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

#ifndef TEE_COMMON_H
#define TEE_COMMON_H

#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUF_MAX_SIZE           4096
#define HASH_FILE_MAX_SIZE     (16 * 1024)

typedef enum {
    SYSTEM_CA = 1,
    VENDOR_CA,
    APP_CA,
    MAX_CA,
} CaType;

typedef struct {
    uint8_t certs[BUF_MAX_SIZE];
    CaType type;
    uid_t uid;
    pid_t pid;
    int fromHalSide;
} CaAuthInfo;

#ifdef __cplusplus
}
#endif

#endif
