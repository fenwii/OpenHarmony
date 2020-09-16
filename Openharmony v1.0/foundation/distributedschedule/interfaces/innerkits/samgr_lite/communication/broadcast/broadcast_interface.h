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
 * @addtogroup Broadcast
 * @{
 *
 * @brief Provides data subscription and data push for services.
 *
 * With this module, the Service, Feature, or other modules can broadcast events or data. \n
 * All services that listen to these events or data can receive these broadcasts. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file broadcast_intertface.h
 *
 * @brief Provides the external interfaces and basic type definitions of the broadcast service.
 *
 * The interface and type are used for subscribing to and publishing events and data. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef LITE_BROADCAST_INTERFACE_H
#define LITE_BROADCAST_INTERFACE_H

#include <ohos_errno.h>
#include "feature.h"
#include "iunknown.h"
#include "message.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Indicates the name of the broadcast service.
 *
 * @since 1.0
 * @version 1.0 */
#define BROADCAST_SERVICE "Broadcast"

/**
 * @brief Indicates the name of the pub/sub feature.
 *
 * @since 1.0
 * @version 1.0
 */
#define PUB_SUB_FEATURE "Provider and subscriber"

/**
 * @brief Indicates the topic of an event or data, which is used to distinguish different types of
 * events or data.
 *
 * @since 1.0
 * @version 1.0
 */
typedef uint32 Topic;

/**
 * @brief Enumerates error codes unique to the Broadcast service.
 */
enum BroadcastErrCode {
    /** Error code showing that a topic has been subscribed to */
    EC_ALREADY_SUBSCRIBED = EC_SUCCESS + 1
};

typedef struct Consumer Consumer;

/**
 * @brief Defines the topic consumer used to receive events and push data. You need to implement
 * this struct for your application.
 */
struct Consumer {
    /** Consumer ID */
    const Identity *identity;

    /**
     * @brief Defines how the consumer will process the events or data of a released topic.
     *
     * You can implement this function for consumers to process topics associated with the them. \n
     * Note that the passed topic must have been subscribed by the consumer. Otherwise, the
     * function does nothing. \n
     *
     * @param consumer Indicates <b>this</b> pointer of the consumer.
     * @param topic Indicates the pointer to the topic to be processed.
     * @param origin Indicates the pointer to the data to be processed.
     * @since 1.0
     * @version 1.0
     */
    void (*Notify)(Consumer *consumer, const Topic *topic, const Request *origin);

    /**
     * @brief Checks whether two consumers are equal.
     *
     * You need to implement this function to prevent repeated topic subscription. \n
     *
     * @param current Indicates the pointer to the current consumer.
     * @param other Indicates the pointer to the target consumer to compare.
     * @return Returns <b>TRUE</b> if the two consumers are equal; returns <b>FALSE</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    BOOL (*Equal)(const Consumer *current, const Consumer *other);
};

typedef struct Provider Provider;

/**
 * @brief Defines the provider of events and data of a topic.
 */
struct Provider {
    /**
     * @brief Publishes events and data of a specified topic.
     *
     * The events or data is published by the publisher, sent to all consumers who have subscribed
     * to the topic, and processed by the consumers. \n
     *
     * @param iUnknown Indicates external interface of the pub/sub feature.
     * @param topic Indicates the pointer to the topic to publish.
     * @param data Indicates the pointer to the data to publish.
     * @param len Indicates the length of the data to be published. The length must be the same as
     * the <b>data</b> length. The caller must ensure the validity of this parameter.
     * @return Returns <b>TRUE</b> if the topic is successfully published; returns <b>FALSE</b>
     * otherwise.
     * @since 1.0
     * @version 1.0
     */
    BOOL (*Publish)(IUnknown *iUnknown, const Topic *topic, uint8 *data, int16 len);
};

typedef struct Subscriber Subscriber;

/**
 * @brief Defines the subscriber for external interfaces to subsribe to events and data of a topic.
 */
struct Subscriber {
    /**
     * @brief Adds a specified topic to the Broadcast service.
     *
     * The specified topic is added by the subscriber. \n
     * A topic can be subscribed to only after being added. \n
     *
     * @param iUnknown Indicates external interface of the pub/sub feature.
     * @param topic Indicates the topic to be subscribed to.
     * @return Returns <b>EC_SUCCESS</b> if the topic is successfully added; returns other error
     * codes if the topic fails to be added.
     * @since 1.0
     * @version 1.0
     */
    int (*AddTopic)(IUnknown *iUnknown, const Topic *topic);

    /**
     * @brief Subscribes to a specified topic for consumers.
     *
     * Call this function on the subscriber. The topic to be subscribed to must have been added to
     * the Broadcast service. \n
     *
     * @param iUnknown Indicates external interface of the pub/sub feature.
     * @param topic Indicates the topic to be subscribed to.
     * @param consumer Indicates the consumer who subscribes to the topic.
     * @return Returns <b>EC_SUCCESS</b> if the subscription is successful; returns other error
     * codes if the subscription fails.
     * @since 1.0
     * @version 1.0
     */
    int (*Subscribe)(IUnknown *iUnknown, const Topic *topic, Consumer *consumer);

    /**
     * @brief Modifies the consumer of a specified topic.
     *
     *
     *
     * @param iUnknown Indicates the pointer to the external interface of the pub/sub feature.
     * @param topic Indicates the pointer to the topic whose consumer will be modified.
     * @param old Indicates the pointer to the original consumer of the topic.
     * @param current Indicates the pointer to the new consumer of the topic.
     * @return Returns the pointer of the original consumer if the modification is successful;
     * returns <b>NULL</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    Consumer *(*ModifyConsumer)(IUnknown *iUnknown, const Topic *topic, Consumer *old, Consumer *current);

    /**
     * @brief Unsubscribes from a specified topic.
     *
     * This function cancels the subscription relationship between the specified topic and
     * consumer. \n
     *
     * @param iUnknown Indicates external interface of the pub/sub feature. This parameter is used
     * to obtain subscription relationships.
     * @param topic Indicates the pointer to the topic to unsubscribe from.
     * @param consumer Indicates the pointer to the consumer.
     * @return Returns the pointer of the consumer if the unsubscription is successful; returns
     * <b>NULL</b> otherwise.
     * @since 1.0
     * @version 1.0
     */
    Consumer *(*Unsubscribe)(IUnknown *iUnknown, const Topic *topic, const Consumer *consumer);
};

typedef struct PubSubInterface PubSubInterface;

struct PubSubInterface {
    INHERIT_IUNKNOWN;
    Subscriber subscriber;
    Provider provider;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_BROADCAST_INTERFACE_H
/** @} */
