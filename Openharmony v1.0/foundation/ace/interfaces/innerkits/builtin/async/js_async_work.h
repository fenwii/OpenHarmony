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

#ifndef OHOS_ACELITE_JS_ASYNC_WORK_H
#define OHOS_ACELITE_JS_ASYNC_WORK_H

#include "message_queue_utils.h"
#include "memory_heap.h"

namespace OHOS {
namespace ACELite {
/**
 * Function pointer type used for async work.
 * Note: this type is deprecated, use AsyncHandler alternatively
 */
typedef void (*AsyncWorkHandler)(void* data);

/**
 * Function pointer type used for async work.
 */
typedef void (*AsyncHandler)(void* data, int8_t statusCode);

struct AsyncWork : public MemoryHeap {
    AsyncWorkHandler workHandler;
    AsyncHandler handler;
    void* data;
    AsyncWork() : workHandler(nullptr), handler(nullptr), data(nullptr) {}
    AsyncWork(const AsyncWork &) = delete;
    AsyncWork &operator=(const AsyncWork &) = delete;
    AsyncWork(AsyncWork &&) = delete;
    AsyncWork &operator=(AsyncWork &&) = delete;
};

/**
 * @class JsASyncWork
 *
 * @brief JsAsyncWork is used to send asynchronous tasks to the system for execution
 *
 * @see MemoryHeap
 */
class JsAsyncWork final : public MemoryHeap {
public:
    JsAsyncWork(const JsAsyncWork &) = delete;
    JsAsyncWork &operator=(const JsAsyncWork &) = delete;
    JsAsyncWork(JsAsyncWork &&) = delete;
    JsAsyncWork &operator=(JsAsyncWork &&) = delete;
    ~JsAsyncWork() {}

    /**
     * @brief Set the queue handler of the app main queue
     *
     * @param [in] handler: QueueHandler object to set
     */
    static void SetAppQueueHandler(const QueueHandler handler);

    /**
     * @brief Create an async work from given parameters, and dispatch it to main app task handler
     *
     * @param [in] workHandler: the entry handler of the async work
     * @param [in] data: pointer to the data the async work needed
     * @return true: operation succeed
     *         false: operation failed
     * Note: this function is deprecated, use the other one alternatively
     */
    static bool DispatchAsyncWork(AsyncWorkHandler workHandler, void *data);

    /**
     * @brief Create an async work from given parameters, and dispatch it to main app task handler
     *
     * @param[in] handler: the entry handler of the async work
     * @param[in] data: pointer to the data the async work needed
     * @return true: operation succeed
     *         false: operation failed
     */
    static bool DispatchAsyncWork(AsyncHandler handler, void *data);

    /**
     * @brief Common new message dispatching method.
     *
     * @param [in] msgId: the new message ID
     * @param [in] data: pointer to the data
     * @return true: operation succeed
     *         false: operation failed
     */
    static bool DispatchToLoop(AbilityMsgId msgId, void *data);

    /**
     * @brief Execute the given async work
     *
     * @param [in] asyncWork: reference to the async work to be executed
     */
    static void ExecuteAsyncWork(AsyncWork *&asyncWork, int8_t statusCode = ERR_OK);

    // Error code used for async work processing
    static const int8_t ERR_OK = 0;
    static const int8_t ERR_FAIL = -1;

private:
    static bool DispatchAsyncWorkInner(AsyncWorkHandler workHandler, AsyncHandler handler, void *data);
    static QueueHandler appQueuehandler_;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_JS_ASYNC_WORK_H
