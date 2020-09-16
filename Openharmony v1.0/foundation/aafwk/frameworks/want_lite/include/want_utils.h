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

#ifndef OHOS_WANT_UTILS_H
#define OHOS_WANT_UTILS_H

#include "want.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus

#ifdef OHOS_APPEXECFWK_BMS_BUNDLEMANAGER
#include <serializer.h>

bool SerializeWant(IpcIo *io, const Want *want);
bool DeserializeWant(Want *want, IpcIo *io);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // OHOS_WANT_UTILS_H
