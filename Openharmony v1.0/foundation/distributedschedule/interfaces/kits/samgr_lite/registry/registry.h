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
 * @addtogroup Registry
 * @{
 *
 * @brief Provides APIs for registering and discovering inter-process communication (IPC)
 * capabilities.
 *
 * Based on the Samgr development framework, this module helps you to develop system capabilities
 * and implement cross-process calls. \n
 * This module is used when system capabilities need to be provided across processes. \n
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file registry.h
 *
 * @brief Provides basic APIs for remote service registration and discovery.
 *
 * APIs provided by this file include the factory registration function of the client code. \n
 * This file is used when there are customized client objects. \n
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef LITE_REGISTRY_H
#define LITE_REGISTRY_H

#include <ohos_types.h>
#include <iunknown.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Indicates the creator of the customized client proxy.
 *
 * This macro creates a local client proxy for remote service APIs.
 * If you want to call the remote APIs in the way that local APIs are called, implement this macro
 * to encapsulate serialized data into the proxy. \n
 * The system automatically calls this macro when creating a proxy object. \n
 *
 * @param service Indicates the pointer to the name of the service to which the function belongs.
 * @param feature Indicates the pointer to the name of the feature to which the function belongs.
 * @param size Indicates the size of the head to be added when a client proxy is created. The
 * required memory capacity is the head size plus the object size.
 * @return void * Returns the applied memory capacity and initialize the memory for the client
 * proxy.
 */
typedef void *(*Creator)(const char *service, const char *feature, uint32 size);

/**
 * @brief Indicates the destroyer of the customized client proxy.
 *
 * This macro destroys local client proxy for remote service APIs.
 * If you want to call the remote APIs in the way that local APIs are called, implement this macro
 * to encapsulate serialized data into the proxy. \n
 * The system automatically calls this macro when destroying a proxy object. \n
 *
 * @param service Indicates the pointer to the name of the service to which the function belongs.
 * @param feature Indicates the pointer to the name of the feature to which the function belongs.
 * @param iproxy Indicates the pointer to the start address of the memory that is applied by
 * <b>Creator</b>.
 */
typedef void (*Destroyer)(const char *service, const char *feature, void *iproxy);

/**
 * @brief Registers the factory method of the client proxy object with the Samgr.
 *
 *
 * If you want to call the remote APIs in the way that local APIs are called, implement this
 * function to encapsulate serialized data into the proxy. \n
 * During system initialization, the module that uses the remote proxy calls the function as
 * required. \n
 *
 * @param service Indicates the pointer to the service name of the client proxy.
 * @param feature Indicates the pointer to the feature name of the client proxy.
 * @param creator Indicates the <b>Creator</b> function of the client proxy.
 * @param destroyer Indicates the <b>Destroyer</b> function of the client proxy.
 * @return Returns <b>EC_SUCCESS</b> if the registration is successful; returns other error codes
 * if the registration fails.
 * @since 1.0
 * @version 1.0
 */
int SAMGR_RegisterFactory(const char *service, const char *feature, Creator creator, Destroyer destroyer);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_REGISTRY_H
/** @} */
