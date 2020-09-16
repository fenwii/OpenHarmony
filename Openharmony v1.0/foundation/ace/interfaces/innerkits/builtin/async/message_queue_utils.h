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
#ifndef OHOS_ACELITE_MESSAGE_QUEUE_UTILS_H
#define OHOS_ACELITE_MESSAGE_QUEUE_UTILS_H

#include <cstdint>

#include "memory_heap.h"

namespace OHOS {
namespace ACELite {
/**
 * Message queue handler which identify one queue entity
 */
typedef void* QueueHandler;

/**
 * Successful message queue operation
 */
#ifndef MSGQ_OK
#define MSGQ_OK 0
#endif

/**
 * Failed message queue operation
 */
#ifndef MSGQ_FAIL
#define MSGQ_FAIL -1
#endif

/**
 * Wait forever timeout value
 */
#ifndef WAIT_FOREVER
#ifdef osWaitForever
#define WAIT_FOREVER osWaitForever
#else
#define WAIT_FOREVER 0xFFFFFFFFU
#endif // osWaitForever
#endif // WAIT_FOREVER

/**
 * No wait timeout value
 */
#ifndef NO_WAIT
#ifdef osNoWait
#define NO_WAIT osNoWait
#else
#define NO_WAIT 0x0U
#endif // osNoWait
#endif // NO_WAIT

/**
 * @enum AbilityMsgId
 *
 * @brief Values that represent ability message states
 */
enum AbilityMsgId {
    UNKNOWN,
    START_ABILITY,
    ACTIVE,
    NEW_DATA,
    BACKGROUND,
    DESTORY,
    BACKPRESSED,
    ASYNCWORK,
    TE_EVENT,
    MSG_ID_MAX,
};

struct AbilityInnerMsg {
    AbilityMsgId msgId;
    uint16_t token;
    const char *bundleName;
    const char *path;
    void *data;
    uint16_t dataLength;
    AbilityInnerMsg() : msgId(UNKNOWN), token(0), bundleName(nullptr), path(nullptr), data(nullptr), dataLength(0) {}
};

/**
 * @class MessageQueueUtils
 *
 * @brief A queue utility to handle messages
 *
 * @see MemoryHeap
 */
class MessageQueueUtils : public MemoryHeap {
public:
    MessageQueueUtils(const MessageQueueUtils &) = delete;
    MessageQueueUtils &operator=(const MessageQueueUtils &) = delete;
    MessageQueueUtils(MessageQueueUtils &&) = delete;
    MessageQueueUtils &operator=(MessageQueueUtils &&) = delete;
    ~MessageQueueUtils() {}

    /**
     * @brief Create a Message Queue entity
     *
     * @param [in] capacity: maximum number of messages in queue
     * @param [in] msgSize: message size in bytes
     * @return handler of the queue created
     */
    static QueueHandler CreateMessageQueue(uint32_t capacity, uint32_t msgSize);

    /**
     * @brief Delete a Message Queue entity
     *
     * @param [in] handler: the handler of the target queue
     * @return MSGQ_OK: success
     *         MSGQ_FAIL: fail
     */
    static int8_t DeleteMessageQueue(QueueHandler handler);

    /**
     * @brief Put a message into the given queue or timeout if the queue is full
     *
     * @param [in] handler: the handler of the target queue
     * @param [in] msgPtr: pointer to buffer for message to put into the queue
     * @param [in] timeOut: the time to wait when the queue is full
     * @return MSGQ_OK: success
     *         MSGQ_FAIL: fail
     */
    static int8_t PutMessage(QueueHandler handler, const void *msgPtr, uint32_t timeOut);

    /**
     * @brief Get a message from the given queue or timeout if the queue is empty
     *
     * @param [in] handler: the handler of the target queue
     * @param [in] msgPtr: pointer to buffer for message to get from the queue
     * @param [in] timeOut: the time to wait when the queue is empty
     * @return MSGQ_OK: success
     *         MSGQ_FAIL: fail
     */
    static int8_t GetMessage(QueueHandler handler, void *msgPtr, uint32_t timeOut);
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_MESSAGE_QUEUE_UTILS_H
