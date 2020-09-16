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
 * @file iproxy_server.h
 *
 * @brief Provides the server proxy.
 *
 * This feature is required for providing cross-process system capabilities. \n
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef LITE_IPROXY_SERVER_H
#define LITE_IPROXY_SERVER_H

#include "iunknown.h"
#include "message.h"
#include "serializer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Defines the default version number of the server proxy.
 *
 * The cross-process system capabilities are registered when Samgr uses <b>SERVER_PROXY_VER</b>
 * to query the registered server proxy. \n
 *
 */
#define SERVER_PROXY_VER 0x80
#define SERVER_IMPL_PROXY_VER ((uint16)SERVER_PROXY_VER | (uint16)DEFAULT_VERSION)

/**
 * @brief Inherits the server proxy function.
 *
 * When the server provides cross-process system capabilities, it uses <b>INHERIT_SERVER_IPROXY</b>
 * to define the server proxy function. \n
 *
 */
#define INHERIT_SERVER_IPROXY \
        INHERIT_IUNKNOWN; \
        int32 (*Invoke)(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)

typedef struct IServerProxy IServerProxy;

/**
 * @brief Defines the base class of the server proxy object.
 *
 * When the server provides cross-process system capabilities, it uses <b>INHERIT_SERVER_IPROXY</b>
 * to define the server proxy. \n
 */
struct IServerProxy {
    /** This class inherits from <b>IUnknown</b>. */
    INHERIT_IUNKNOWN;
    /**
     * @brief Unmarshals the IPC message received by the server.
     *
     * This function is implemented by developers and called by the system. \n
     * This function runs in the message processing thread of the service. Do not block the message
     * processing thread; otherwise, the function may fail to be executed. \n
     *
     * @param Proxy Indicates the pointer to the server proxy object.
     * @param funcId Indicates the ID of the server function to be invoked by the client.
     * @param origin Indicates the original IPC message, from which the header information can be
     * obtained.
     * @param req ipc Indicates the message body, from which data can be obtained.
     * @param reply Indicates the output parameter, which is used to respond to the message.
     * The value can contain a maximum of five objects and 200 bytes.
     * @return Returns <b>EC_SUCCESS</b> if the unmarshalling is successful; returns other error
     * codes if the unmarshalling fails.
     * @since 1.0
     * @version 1.0
     */
    int32 (*Invoke)(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply);
};

/**
 * @brief Inherits the server proxy class.
 *
 * When the server provides cross-process system capabilities, it uses <b>INHERIT_IPROXY_ENTRY</b>
 * to define the server proxy class. \n
 *
 */
#define INHERIT_IPROXY_ENTRY(T) INHERIT_IUNKNOWNENTRY(T)

/**
 * @brief Defines the beginning of the default initialization for the server proxy class.
 *
 * This macro is used for developing the server proxy class. You can inherit this macro to
 * reduce the code amount and prevent class definition inconsistency. \n
 *
 */
#define SERVER_IPROXY_BEGIN  IUNKNOWN_ENTRY_BEGIN(SERVER_PROXY_VER)

#define SERVER_IPROXY_IMPL_BEGIN  IUNKNOWN_ENTRY_BEGIN(SERVER_IMPL_PROXY_VER)

/**
 * @brief Defines the end of the default initialization for the server proxy class.
 *
 * This macro is used for developing the server proxy class. You can inherit this macro to
 * reduce the code amount and prevent class definition inconsistency. \n
 *
 */
#define IPROXY_END IUNKNOWN_ENTRY_END

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // LITE_IPROXY_SERVER_H
/** @} */
