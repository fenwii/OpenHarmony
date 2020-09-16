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
 * @addtogroup Surface
 * @{
 *
 * @brief Provides the capabilities of applying for and releasing shared memory in multimedia and graphics scenarios.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ibuffer_consumer_listener.h
 *
 * @brief Declares the consumer listener used to notify consumers when the surface status is updated.
 *
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_IBUFFER_CONSUMER_LISTENER_H
#define GRAPHIC_LITE_IBUFFER_CONSUMER_LISTENER_H

namespace OHOS {
/**
 * @brief Defines the consumer listener used to notify consumers when the surface status is updated.
 *
 * @since 1.0
 * @version 1.0
 */
class IBufferConsumerListener {
public:
    /**
     * @brief Called to notify a consumer that a buffer is available for consumption.
     *
     * @since 1.0
     * @version 1.0
     */
    virtual void OnBufferAvailable() = 0;
};
} // end namespace
#endif
