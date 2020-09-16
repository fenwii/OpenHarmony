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
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file event_injector.h
 *
 * @brief Declares the function for simulating input events.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef GRAPHIC_LITE_EVENT_INJECTOR_H
#define GRAPHIC_LITE_EVENT_INJECTOR_H

#include "graphic_config.h"
#if ENABLE_DEBUG
#include "dock/input_device.h"
namespace OHOS {
/**
 * @ Enumerates the event types.
 */
enum class EventDataType {
    /** Point event */
    POINT_TYPE,
    /** Other events */
    OTHERS
};

class PointEventInjector;

/**
 * @brief Manages all types of simulated input events, registers and unregisters event injectors, and simulates
 * input events.
 *
 * @since 1.0
 * @version 1.0
 */
class EventInjector : public HeapBase {
public:
    /**
     * @brief Obtains an instance in singleton pattern.
     *
     * @return Returns the event injector instance.
     * @since 1.0
     * @version 1.0
     */
    static EventInjector* GetInstance()
    {
        static EventInjector instance;
        return &instance;
    }

    /**
     * @brief Registers an event injector of a specified type.
     *
     * @param type Indicates the event type. For details, see {@link EventDataType}.
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool RegisterEventInjector(EventDataType type);

    /**
     * @brief Unregisters an event injector of a specified type.
     *
     * @param type Indicates the event type. For details, see {@link EventDataType}.
     * @since 1.0
     * @version 1.0
     */
    void UnregisterEventInjector(EventDataType type);

    /**
     * @brief Checks whether the event injector of a specified type is registered.
     *
     * @param type Indicates the event type. For details, see {@link EventDataType}.
     * @return Returns <b>true</b> if the device is registered; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool IsEventInjectorRegistered(EventDataType type) const;

    /**
     * @brief Uses a data array of a specified length to simulate an input event of a specified type.
     *
     * @param dataArray Indicates the pointer to the data array used for simulating the event.
     * @param arrayLength Indicates the length of the data array.
     * @param type Indicates the event type. For details, see {@link EventDataType}.
     * @return Returns <b>true</b> if the operation is successful; returns <b>false</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    bool SetInjectEvent(const DeviceData* dataArray, uint16_t arrayLength, EventDataType type);

private:
    PointEventInjector* pointEventInjector_;

    EventInjector() : pointEventInjector_(nullptr) {}
    virtual ~EventInjector();

    EventInjector(const EventInjector&) = delete;
    EventInjector& operator=(const EventInjector&) = delete;
    EventInjector(EventInjector&&) = delete;
    EventInjector& operator=(EventInjector&&) = delete;
};
}
#endif // ENABLE_DEBUG
#endif // GRAPHIC_LITE_EVENT_INJECTOR_H
