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
 * @addtogroup Samgr
 * @{
 *
 * @brief Manages system capabilities.
 *
 * This module provides the development framework base of the service-oriented architecture (SOA).
 * You can develop your own abilities based on the Samgr development framework. \n
 * This module provides basic models of services, features, and functions, and registration and
 * discovery capabilities. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file message.h
 *
 * @brief Provides message communication APIs that help you to implement asynchronous functions
 * of {@link IUnknown}.
 *
 * This API is used to implement asynchronous functions of {@link IUnknown}. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef LITE_MESSAGE_H
#define LITE_MESSAGE_H

#include "common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
typedef struct Identity Identity;
typedef struct Request Request;
typedef struct Response Response;

/**
 * @brief Handles asynchronous responses.
 *
 * This function will be used when a service or feature uses {@link IUnknown} to send a request. \n
 * If the caller is a feature, this function is used to handle the response that is sent after the
 * feature processes a request. \n
 * If the caller is a service, <b>Handler</b> will run in the service thread. \n
 *
 */
typedef void (*Handler)(const Request *request, const Response *response);

// Will be used for message interaction, so use one-byte alignment
#pragma pack(1)
/**
 * @brief Identifies a service and feature.
 *
 * You can use this structure to identity a {@link IUnknown} feature to which messages will be
 * sent through the asynchronous function of {@link IUnknown}. \n
 *
 */
struct Identity {
    /** Service ID */
    int16 serviceId;
    /** Feature ID */
    int16 featureId;
    /** Message queue ID */
    MQueueId queueId;
};

/**
 * @brief Defines a request.
 *
 * You can use this structure to define the request that will be sent to a feature through the
 * asynchronous function of {@link IUnknown}. \n
 * Request, which is data that is packed to send to a feature. \n
 * If the data is not empty and the length is not 0, the system automatically releases the data. \n
 *
 */
struct Request {
    /** Message ID */
    int16 msgId;
    /** Data length */
    int16 len;
    /** Data content */
    void *data;
    /** Message value, which is defined by developers */
    uint32 msgValue;
};

/**
 * @brief Defines a response.
 *
 * This structure is used to send a response after the message processing function of a service
 * or feature processes a request. \n
 * If the data is not empty and the length is not 0, the system automatically releases the data. \n
 *
 */
struct Response {
    /** Data content */
    void *data;
    /** Data length */
    int16 len;
};
#pragma pack()

/**
 * @brief Sends a request to a service or feature of a specified identity.
 *
 * This function is called by a service to send messages to its own features through the
 * asynchronous function of {@link IUnknown}. \n
 *
 * @param identity Indicates the pointer to the ID of the feature or service that processes
 * the message.
 * @param request Indicates the pointer to the request.
 * @param handler Indicates the function handling the response. If the value is <b>NULL</b>,
 * no response is required.
 * @return Returns <b>EC_SUCCESS</b> if the request is sent successfully; returns other error codes
 * if the request fails to be sent. The caller needs to release the memory applied in the request.
 * @since 1.0
 * @version 1.0
 */
int32 SAMGR_SendRequest(const Identity *identity, const Request *request, Handler handler);

/**
 * @brief Sends a request to multiple services or features to save memory.
 *
 * This function is used to publish topics for the {@link Broadcast} service to broadcast messages. \n
 *
 * @param identity Indicates the pointer to the IDs of services or features, to which requests
 * are sent.
 * @param request Indicates the pointer to the request.
 * @param token Indicates the pointer to reference counting.
 * @param handler Indicates the function handling the response. If the value is <b>NULL</b>,
 * no response is required.
 * @retval Returns the token if the request is sent successfully; returns <b>NULL</b> if the
 * request fails to be sent.
 * @attention
 *  <ul><li>Ensure that the thread specified by <b>identity</b> processes the message after
 *  all messages are sent. Common practice: Add a lock before sending a request and add
 *  the same lock during processing. </li>
 *  <li>If <b>NULL</b> is returned, the caller needs to release the memory of the request. </li></ul>
 * @since 1.0
 * @version 1.0
 */
uint32 *SAMGR_SendSharedRequest(const Identity *identity, const Request *request, uint32 *token, Handler handler);

/**
 * @brief Sends a request and response of a caller to the feature thread. The handler is directly
 * called to process the request and response without using the message processing functions.
 * (Customized function for the broadcast service)
 *
 * This function is used to publish topics for the {@link Broadcast} service to broadcast messages. \n
 * The value of reference counting is incremented by one each time this function is called. \n
 *
 * @param id Indicates the pointer to the IDs of services or features, to which the request and
 * response are sent.
 * @param request Indicates the pointer to the request.
 * @param resp Indicates the pointer to the response.
 * @param ref Indicates the reference counting.
 * @param handler Indicates the function for handling the request and response. This parameter
 * cannot be <b>NULL</b>.
 * @return Returns <b>EC_SUCCESS</b> if the request and response are sent successfully; returns
 * other error codes if the request and response fail to be sent.
 * @attention
 *  <ul><li>Ensure that the thread specified by <b>identity</b> processes the message after all
 *  messages are sent. Common practice: Add a lock before sending a request and add the same lock
 *  during processing. </li>
 *  <li>If <b>NULL</b> is returned, the caller needs to release the memory of the request and
 *  response. </li>
 *  <li>If the response changes each time when a request is sent, ensure that the response
 *  will not be released. (Set <b>len</b> to <b>0</b>, the <b>data</b> of response will be
 *  the resident memory.) </li></ul>
 * @since 1.0
 * @version 1.0
 */
int32 SAMGR_SendSharedDirectRequest(const Identity *id, const Request *req, const Response *resp, uint32 **ref,
                                    Handler handler);

/**
 * @brief Sends a response after processing a request.
 *
 * This function is called to send a response after processing a request by {@link MessageHandle}
 * of a service or {@link OnMessage} of a feature. \n
 *
 * @param request Indicates the pointer to the original request.
 * @param response Indicates the pointer to the response content.
 * @return Returns <b>EC_SUCCESS</b> if the response is sent successfully; returns other error
 * codes if the response fails to be sent.
 * @attention
 *  <ul><li>This function can be called only in {@link MessageHandle} or {@link OnMessage}. </li>
 *  <li>The request must be the original one passed from {@link MessageHandle} or
 *  {@link OnMessage}. Otherwise, a memory exception occurs. </li>
 *  <li> When the caller sends a request, the <b>handler</b> callback function must be carried. </li>
 *  <li>The response is sent to the message queue of the service to which the requester belongs
 *  for processing. Therefore, the requester should wait for the response in non-blocking mode. </li></ul>
 * @since 1.0
 * @version 1.0
 */
int32 SAMGR_SendResponse(const Request *request, const Response *response);

/**
 * @brief Sends a response to a specified service or feature after processing the original request.
 * (Customized function for <b>bootstrap</b>)
 *
 * This function is called to send a response after processing a request by {@link MessageHandle}
 * of a service or {@link OnMessage} of a feature. \n
 * This function can be customized to implement phased startup of different types of services. \n
 *
 * @param id Indicates the pointer to the ID of a service or feature. The response is sent to the
 * thread of the service or feature for processing.
 * @param request Indicates the pointer to the original request.
 * @param response Indicates the pointer to the response content.
 * @return Returns <b>EC_SUCCESS</b> if the response is sent successfully; returns other error
 * codes if the response fails to be sent.
 * @attention
 *  <ul><li>This function can be called only in <b>MessageHandle</b> or <b>OnMessage</b>. </li>
 *  <li>The request must be the original one passed from <b>MessageHandle</b> or <b>OnMessage</b>.
 *  Otherwise, a memory exception occurs. </li>
 *  <li> When the caller sends a request, the <b>handler</b> callback function must be carried. </li>
 *  <li>The response is sent to the message queue of a specified ID for processing. Therefore,
 *  wait for the response in non-blocking mode. </li></ul>
 * @since 1.0
 * @version 1.0
 */
int32 SAMGR_SendResponseByIdentity(const Identity *id, const Request *request, const Response *response);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_MESSAGE_H
/** @} */
