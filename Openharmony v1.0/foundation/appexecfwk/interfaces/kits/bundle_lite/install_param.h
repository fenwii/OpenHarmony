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

#ifndef OHOS_INSTALL_PARAM_H
#define OHOS_INSTALL_PARAM_H

#include "stdint.h"

#include <stdbool.h>

// when installLocation set 1, it means install dir is storage/app
const static int32_t INSTALL_LOCATION_INTERNAL_ONLY = 1;
// when installLocation set 2, it means install dir is sdcard/app
const static int32_t INSTALL_LOCATION_PREFER_EXTERNAL = 2;

typedef struct {
    int32_t installLocation;
    bool keepData;
} InstallParam;

#endif // OHOS_INSTALL_PARAM_H