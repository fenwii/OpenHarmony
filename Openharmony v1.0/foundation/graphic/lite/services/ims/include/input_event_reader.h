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

#ifndef GRAPHIC_LITE_INPUT_EVENT_READER_H
#define GRAPHIC_LITE_INPUT_EVENT_READER_H

#include "input_event_hub.h"

namespace OHOS {
/** @brief Reader og input event */
class InputEventReader : public InputEventHub::InputDevStatusListener {
typedef void(*RegCallback)(RawEvent*);
public:
    /** @brief Default constructor */
    InputEventReader();
    /** @brief Default destructor */
    ~InputEventReader();

    /**
     * @brief Registration read callback.
     *
     */
    int32_t RegisterReadCallback(RegCallback callback)
    {
        if (callback == nullptr) {
            return 1;
        }
        readCallback_ = callback;
        return 0;
    }

    /**
     * @brief start up hub.
     *
     */
    void StartUpHub()
    {
        hub_->SetUp();
    }

    /**
     * @brief Listener of input device.
     */
    class InputEventListener {
    public:
        InputEventListener() : data_{0} {}
        virtual ~InputEventListener() {}

        /**
         * @brief Callback when hub updata.
         *
         * @param [in] event event of hub send data.
         *
         */
        virtual RawEvent DisposeData(RawEvent event)
        {
            return data_;
        }

        /**
         * @brief Callback when get listener type.
         *
         */
        InputDevType GetDevType()
        {
            return data_.type;
        }

    protected:
        RawEvent data_;
    };

    /**
     * @brief Bind device index and device listener.
     *
     * @param [in] device device of device listener.
     * @param [in] devIndex devIndex of bind device index.
     *
     * @return [out] if return -1,bind fail;
     *
     */
    void RegisterInputEventListener(InputEventListener* device);

protected:
    void OnDeviceMounted(uint32_t devIndex) override;

    void OnDeviceUnmounted(uint32_t devIndex) override;

    void OnSend(RawEvent event) override;

    bool OnFindDeviceMounted(uint32_t devIndex) override;
private:
    RegCallback readCallback_;
    InputEventHub* hub_;
    std::map<uint32_t, InputEventListener*> deviceListenerMap_;
};

/** @brief input device of mouse listener */
class MouseInputEventListener : public InputEventReader::InputEventListener {
public:
    MouseInputEventListener()
    {
        data_.x = 0;
        data_.y = 0;
        data_.type = InputDevType::INDEV_TYPE_MOUSE;
    }
    ~MouseInputEventListener() {}

    RawEvent DisposeData(RawEvent event) override
    {
        data_.x += event.x;
        data_.y += event.y;
        if ((event.state & 0x01) == 1) {
            data_.state = 1;
        } else if ((event.state & 0x07) == 0) {
            data_.state = 0;
        }
        data_.timestamp = event.timestamp;
        return data_;
    }
};

/** @brief input device of touch listener */
class TouchInputEventListener : public InputEventReader::InputEventListener {
public:
    TouchInputEventListener()
    {
        data_.type = InputDevType::INDEV_TYPE_TOUCH;
    }
    ~TouchInputEventListener() {}

    RawEvent DisposeData(RawEvent event) override
    {
        data_.x = event.x;
        data_.y = event.y;
        if (event.state == 0 || event.state == 2) { // 2:hold on touch pick down state
            data_.state = 1;
        } else if (event.state == 1) {
            data_.state = 0;
        }
        data_.timestamp = event.timestamp;
        return data_;
    }
};
} // namespace OHOS
#endif // GRAPHIC_LITE_INPUT_EVENT_READER_H
