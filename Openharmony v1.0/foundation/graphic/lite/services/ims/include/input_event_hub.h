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

#ifndef GRAPHIC_LITE_INPUT_EVENT_HUB_H
#define GRAPHIC_LITE_INPUT_EVENT_HUB_H

#include "input_event_info.h"
#include "input_manager.h"
#include "securec.h"
#include <map>

namespace OHOS {
/**
 * @brief Hub of input event.
 */
class InputEventHub {
public:
    static InputEventHub* GetInstance()
    {
        static InputEventHub instance;
        return &instance;
    }

    /**
     * @brief SetUp hub. This operation will open all input devices.
     *
     */
    void SetUp();

    /**
     * @brief TearDown hub. This operation will close all input devices.
     *
     */
    void TearDown();

    /**
     * @brief Get device index type.
     *
     * @param [in] devIndex input device index.
     */
    InputDevType GetDeviceType(uint32_t devIndex);

    /**
     * @brief Listener of device status.
     */
    class InputDevStatusListener {
    public:
        InputDevStatusListener() {}
        virtual ~InputDevStatusListener() {}

        /**
         * @brief Callback when device mounted.
         *
         * @param [in] devIndex devIndex of mounted device index.
         *
         */
        virtual void OnDeviceMounted(uint32_t devIndex) {}

        /**
         * @brief Callback when device unmounted.
         *
         * @param [in] devIndex devIndex of unmounted device.
         *
         */
        virtual void OnDeviceUnmounted(uint32_t devIndex) {}

        /**
         * @brief Callback when device unmounted.
         *
         * @param [in] devIndex devIndex of unmounted device.
         *
         */
        virtual bool OnFindDeviceMounted(uint32_t devIndex)
        {
            return false;
        }

        /**
         * @brief Callback when send device data.
         *
         * @param [in] devIndex devIndex of find device.
         *
         */
        virtual void OnSend(RawEvent event) {}
    };

    /**
     * @brief Add an input device status listener to hub.
     *
     * @param [in] listener input device status listener.
     *
     */
    void AddInputDevStatusListener(InputDevStatusListener* listener)
    {
        listener_ = listener;
    }

    /**
     * @brief Remove an input device status listener from hub.
     *
     * @param [in] listener input device status listener.
     *
     */
    void RemoveInputDevStatusListener()
    {
        listener_ = nullptr;
    }

private:
    static void EventCallback(const InputEventData* eventData, uint32_t count, uint32_t devIndex);
    uint8_t ScanInputDevice();
    InputEventHub() : mountDevIndex_{0} {}

    ~InputEventHub() {}

    InputEventHub(const InputEventHub&) = delete;
    InputEventHub& operator=(const InputEventHub&) = delete;
    InputEventHub(InputEventHub&&) = delete;
    InputEventHub& operator=(InputEventHub&&) = delete;

    static IInputInterface *inputInterface_;
    static InputReportEventCb callback_;
    static InputDevStatusListener* listener_;
    uint32_t mountDevIndex_[MAX_INPUT_DEVICE_NUM];
};
} // namespace OHOS
#endif
