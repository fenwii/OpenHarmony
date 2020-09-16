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

#ifndef OHOS_ACELITE_OHOS_MODULE_CONFIG_H
#define OHOS_ACELITE_OHOS_MODULE_CONFIG_H

#include "acelite_config.h"
#include "jsi_types.h"

namespace OHOS {
namespace ACELite {
#ifdef ENABLE_MODULE_REQUIRE_TEST
extern void InitSampleModule(JSIValue exports);
#endif
extern void InitRouterModule(JSIValue exports);
extern void InitAppModule(JSIValue exports);
#ifdef FEATURE_MODULE_AUDIO
extern void InitAudioModule(JSIValue exports);
#endif // FEATURE_MODULE_AUDIO
extern void InitDfxModule(JSIValue exports);
#ifdef ENABLE_MODULE_CIPHER
extern void InitCipherModule(JSIValue exports);
#endif

#ifdef FEATURE_MODULE_STORAGE
extern void InitNativeApiFs(JSIValue exports);
extern void InitNativeApiKv(JSIValue exports);
#endif

#ifdef FEATURE_MODULE_DEVICE
extern void InitDeviceModule(JSIValue exports);
#endif

// Config information for built-in JS modules of OHOS platform
const Module OHOS_MODULES[] = {
#ifdef ENABLE_MODULE_REQUIRE_TEST
    {"sample", InitSampleModule},
#endif
    {"app", InitAppModule},
#ifdef FEATURE_MODULE_AUDIO
    {"audio", InitAudioModule},
#endif // FEATURE_MODULE_AUDIO
    {"dfx", InitDfxModule},
    {"router", InitRouterModule},
#ifdef ENABLE_MODULE_CIPHER
    {"cipher", InitCipherModule},
#endif

#ifdef FEATURE_MODULE_STORAGE
    {"file", InitNativeApiFs},
    {"storage", InitNativeApiKv},
#endif
#ifdef FEATURE_MODULE_DEVICE
    {"device", InitDeviceModule},
#endif
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_OHOS_MODULE_CONFIG_H
