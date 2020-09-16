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

/**
 * @addtogroup MultiMedia_CameraAbility
 * @{
 *
 * @brief Defines the camera capability set for applications to achieve and access the capabilities.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file camera_ability.h
 *
 * @brief Declares functions of the <b>CameraAbility</b> class.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_CAMERA_ABILITY_H
#define OHOS_CAMERA_ABILITY_H

#include "media_log.h"
#include "meta_data.h"
#include <cstdint>
#include <list>
#include <map>
#include <set>

namespace OHOS {
namespace Media {
/**
 * @brief Declares functions of the <b>CameraAbility</b> class.
 *
 *
 * @since 1.0
 * @version 1.0
 */
class CameraAbility {
public:
    /**
     * @brief A constructor used to create a <b>CameraAbility</b> instance.
     *
     */
    CameraAbility();

    /**
     * @brief A destructor used to delete the <b>CameraAbility</b> instance.
     *
     */
    virtual ~CameraAbility();

    /**
     * @brief Obtains the supported image sizes for a specified image format.
     *
     * @param format Indicates the image format, which can be YUV, H.265, or H.264.
     * @return Returns the image size list if obtained; returns <b>NULL</b> otherwise.
     */
    std::list<CameraPicSize> GetSupportedSizes(int format) const;

    /**
     * @brief Sets value ranges for a specified parameter.
     *
     * @param key Indicates the parameter key.
     * @param rangeList Indicates the list of parameter value ranges.
     * @return Returns <b>SUCCESS</b> if the setting is successful; returns <b>FAIL</b> otherwise.
     */
    template<typename T> int32_t SetParameterRange(uint32_t key, std::list<T> rangeList)
    {
        if (IsParameterSupport(key)) {
            SetSupportParameterRange(key, rangeList);
            return MEDIA_OK;
        }
        return MEDIA_ERR;
    }

    /**
     * @brief Obtains the parameter value range based on a specified parameter key.
     *
     * @param key Indicates the parameter key.
     * @return Returns the parameter value range if obtained; returns <b>NULL</b> otherwise.
     */
    template<typename T> std::list<T> GetParameterRange(uint32_t key) const
    {
        if (supportProperties_.find(key) != supportProperties_.end()) {
            return GetSupportParameterRange(key);
        }
    }

private:
    void SetSupportParameterRange(uint32_t key, std::list<CameraPicSize> &rangeList);
    std::list<CameraPicSize> GetSupportParameterRange(uint32_t key) const;
    bool IsParameterSupport(uint32_t key) const;

    std::map<uint32_t, std::list<CameraPicSize>> SizeMap_;
    std::set<uint32_t> supportProperties_;
};
} // namespace Media
} // namespace OHOS
#endif // OHOS_CAMERA_ABILITY_H
