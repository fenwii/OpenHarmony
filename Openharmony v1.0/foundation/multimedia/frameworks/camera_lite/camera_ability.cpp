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
#include "camera_ability.h"

#include "media_log.h"

using namespace std;
namespace OHOS {
namespace Media {
CameraAbility::CameraAbility() {}
CameraAbility::~CameraAbility() {}

list<CameraPicSize> CameraAbility::GetSupportedSizes(int format) const
{
    auto target = SizeMap_.find(PARAM_KEY_SIZE);
    return target->second;
}

list<CameraPicSize> CameraAbility::GetSupportParameterRange(uint32_t key) const
{
    switch (key) {
        case PARAM_KEY_SIZE: {
            auto target = SizeMap_.find(PARAM_KEY_SIZE);
            return target->second;
        }
        default: {
            list<CameraPicSize> emptyList;
            return emptyList;
        }
    }
}

void CameraAbility::SetSupportParameterRange(uint32_t key, list<CameraPicSize> &rangeList)
{
    switch (key) {
        case PARAM_KEY_SIZE:
            supportProperties_.emplace(key);
            SizeMap_[key] = rangeList;
            break;
        default:
            break;
    }
}

bool CameraAbility::IsParameterSupport(uint32_t key) const
{
    if (key != PARAM_KEY_SIZE) {
        return false;
    }
    return true;
}
} // namespace Media
} // namespace OHOS