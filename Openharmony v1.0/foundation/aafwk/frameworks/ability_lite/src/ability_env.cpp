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
#include "ability_env.h"

#include <string>

#include "ability_env_impl.h"

extern "C" {
const char *GetBundleName()
{
    const std::string &bundleName = OHOS::AbilityEnvImpl::GetInstance().GetBundleName();
    return bundleName.c_str();
}

const char *GetSrcPath()
{
    const std::string &srcPath = OHOS::AbilityEnvImpl::GetInstance().GetSrcPath();
    return srcPath.c_str();
}

const char *GetDataPath()
{
    const std::string &dataPath = OHOS::AbilityEnvImpl::GetInstance().GetDataPath();
    return dataPath.c_str();
}
}
