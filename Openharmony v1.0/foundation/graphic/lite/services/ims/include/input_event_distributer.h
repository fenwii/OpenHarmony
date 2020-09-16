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

#ifndef GRAPHIC_LITE_INPUT_EVENT_DISTRIBUTER_H
#define GRAPHIC_LITE_INPUT_EVENT_DISTRIBUTER_H

#include "input_event_info.h"
#include <set>

namespace OHOS {
/**
 * @brief Distributer distribute all input events to specific window.
 */
class InputEventDistributer {
public:
    InputEventDistributer() {}
    ~InputEventDistributer() {}

    /**
     * @brief Distribute input events.
     *
     * @param [in] events events waiting for distribution.
     * @param [in] size totoal size of events.
     *
     */
    void Distribute(RawEvent* events, int32_t size);

    /**
     * @brief Listener of raw event.
    */
    class RawEventListener {
    public:
        virtual void OnRawEvent(const RawEvent& event) = 0;
    };

    /**
     * @brief Add a raw event listener.
     *
     * @param listener raw event listener.
     */
    void AddRawEventListener(RawEventListener* listener)
    {
        if (listener == nullptr) {
            return;
        }
        rawEventListeners_.insert(listener);
    }

    /**
     * @brief Remove a raw event listener.
     *
     * @param listener raw event listener.
     */
    void RemoveRawEventListener(RawEventListener* listener)
    {
        if (listener == nullptr) {
            return;
        }
        rawEventListeners_.erase(listener);
    }
private:
    std::set<RawEventListener*> rawEventListeners_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_INPUT_EVENT_DISTRIBUTER_H