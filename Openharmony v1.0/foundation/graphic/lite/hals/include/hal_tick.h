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

#ifndef GRAPHIC_LITE_HAL_TICK_H
#define GRAPHIC_LITE_HAL_TICK_H

#include <cstdint>

#include "heap_base.h"

namespace OHOS {
/** @brief Class for calculate the time. */
class HALTick : public HeapBase {
public:
    /**
     * Gets the instance
     *
     * @returns The instance.
     */
    static HALTick& GetInstance()
    {
        static HALTick instance;
        return instance;
    }

    /**
     * Gets the milliseconds since start up
     *
     * @returns The elapsed time.
     */
    uint32_t GetTime();

    /**
     * Gets elapse milliseconds since the startTime
     *
     * @param startTime The start time.
     *
     * @returns The elapse time.
     */
    uint32_t GetElapseTime(uint32_t startTime);

private:
    /** Default constructor */
    HALTick() {}
    /** Destructor */
    ~HALTick() {}
    static constexpr uint32_t MILLISEC_TO_NANOSEC = 1000000;
    static constexpr uint16_t SEC_TO_MILLISEC = 1000;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_HAL_TICK_H