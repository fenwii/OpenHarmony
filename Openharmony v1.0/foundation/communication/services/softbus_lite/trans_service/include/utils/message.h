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
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "cJSON.h"

#define CODE_VERIFY_IP              1
#define CODE_VERIFY_DEVID           2
#define CODE_VERIFY_P2P             3
#define CODE_OPEN_AUTH_MSG_CHANNEL  4
#define CODE_OPEN_CHANNEL           1

int GetJsonInt(const cJSON *root, const char *name, int *result);
char* GetJsonString(const cJSON *root, const char *name);


#endif