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

#include "ability_env_impl.h"

namespace OHOS {
constexpr static char PATH_SEPARATOR[] = "/";

void AbilityEnvImpl::SetAppInfo(const AppInfo& appInfo)
{
    bundleName_ = appInfo.bundleName;
    dataPath_ = appInfo.dataPath;
    srcPath_ = appInfo.srcPath;
    if (!appInfo.isNativeApp && !appInfo.moduleNames.empty()) {
        srcPath_ += PATH_SEPARATOR + appInfo.moduleNames.front();
    }
}

const std::string& AbilityEnvImpl::GetBundleName() const
{
    return bundleName_;
}

const std::string& AbilityEnvImpl::GetSrcPath() const
{
    return srcPath_;
}

const std::string& AbilityEnvImpl::GetDataPath() const
{
    return dataPath_;
}
}  // namespace OHOS
