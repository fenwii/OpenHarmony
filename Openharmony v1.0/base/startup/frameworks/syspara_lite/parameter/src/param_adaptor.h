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

#ifndef IOT_SYSPARA_API_H
#define IOT_SYSPARA_API_H

#include "ohos_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define MAX_GET_VALUE_LEN  0x7FFFFFFF
#define MAX_KEY_LEN 32
#define MAX_VALUE_LEN 128

int GetSysParam(const char* key, char* value, unsigned int len);
int SetSysParam(const char* key, const char* value);
boolean CheckPermission(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // IOT_SYSPARA_API_H
