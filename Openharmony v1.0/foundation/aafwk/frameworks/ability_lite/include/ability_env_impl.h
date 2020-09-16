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
#ifndef OHOS_ABILITY_ENV_IMPL_H
#define OHOS_ABILITY_ENV_IMPL_H

#include <app_info.h>
#include <string>

#include "nocopyable.h"

namespace OHOS {
class AbilityEnvImpl : public NoCopyable {
public:
    static AbilityEnvImpl &GetInstance()
    {
        static AbilityEnvImpl instance;
        return instance;
    }

    ~AbilityEnvImpl() override = default;

    void SetAppInfo(const AppInfo& appInfo);

    const std::string& GetBundleName() const;

    const std::string& GetSrcPath() const;

    const std::string& GetDataPath() const;

private:
    AbilityEnvImpl() = default;

    std::string bundleName_;
    std::string srcPath_;
    std::string dataPath_;
};
}  // namespace OHOS
#endif  // OHOS_ABILITY_ENV_IMPL_H
