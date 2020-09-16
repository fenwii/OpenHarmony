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

#ifndef OHOS_ACELITE_VERSION_MODULE_H
#define OHOS_ACELITE_VERSION_MODULE_H

#include "acelite_config.h"
#include "js_config.h"
#include "non_copyable.h"
#if ENABLED(ACE_LITE_VERSION_JS_API)
#include "presets/preset_module.h"
namespace OHOS {
namespace ACELite {
class VersionModule final : public PresetModule {
public:
    ACE_DISALLOW_COPY_AND_MOVE(VersionModule);
    /**
     * @fn VersionModule::VersionModule()
     *
     * @brief Constructor.
     */
    VersionModule() : PresetModule(nullptr) {}

    /**
     * @fn VersionModule::~VersionModule()
     *
     * @brief Constructor.
     */
    ~VersionModule() = default;

    void Init() override;

private:
    static jerry_value_t GetACEVersion(const jerry_value_t func,
                                       const jerry_value_t context,
                                       const jerry_value_t args[],
                                       const jerry_length_t argsNum);

    static jerry_value_t GetACECommit(const jerry_value_t func,
                                      const jerry_value_t context,
                                      const jerry_value_t args[],
                                      const jerry_length_t argsNum);

    static jerry_value_t GetACEBuildStamp(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum);
};
} // namespace ACELite
} // namespace OHOS
#endif // ENABLED(ACE_LITE_VERSION_JS_API)
namespace OHOS {
namespace ACELite {
class AceVersionModule final {
public:
    ACE_DISALLOW_COPY_AND_MOVE(AceVersionModule);
    AceVersionModule() = default;
    ~AceVersionModule() = default;
    static void Load()
    {
#if ENABLED(ACE_LITE_VERSION_JS_API)
        VersionModule versionModule;
        versionModule.Init();
#endif
    }
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_VERSION_MODULE_H
