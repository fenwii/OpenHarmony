/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __KEY_AGREEMENT_VERSION_H__
#define __KEY_AGREEMENT_VERSION_H__

#include <stdbool.h>
#include "jsonutil.h"
#include "key_agreement.h"

#if (defined(_SUPPORT_SEC_CLONE_) || defined(_SUPPORT_SEC_CLONE_SERVER_))
#define RET_STR_LENGTH 8192
#else
#define RET_STR_LENGTH 0x800
#endif

bool parse_version(json_pobject obj_ver, struct key_agreement_version *min_ver, struct key_agreement_version *cur_ver);
uint8_t *raw_byte_to_hex_string(const uint8_t *hex, int32_t length);
#endif /* __KEY_AGREEMENT_VERSION_H__ */
