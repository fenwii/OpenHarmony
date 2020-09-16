/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup Softbus
 * @{
 *
 * @brief Provides high-speed, secure communication between devices.
 *
 * This module implements unified distributed communication capability management between
 * nearby devices, and provides link-independent device discovery and transmission interfaces
 * to support service publishing and data transmission.
 *
 * @since 1.0
 * @version 1.0
*/

/**
 * @file session.h
 *
 * @brief Declares unified data transmission interfaces.
 *
 * This file provides data transmission capabilities, including creating and removing a session server,
 * opening and closing sessions, receiving data, and querying basic session information. \n
 * After multiple nearby devices are discovered and networked, these interfaces can be used to
 * transmit data across devices. \n
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef SESSION_H
#define SESSION_H
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Defines session callbacks.
 *
 * When a session is opened or closed, or there is data to process, the related callback is invoked.
 *
 * @since 1.0
 * @version 1.0
 */
struct ISessionListener {
    /**
     * @brief Called when a session is opened.
     *
     * This function can be used to verify the session or initialize resources related to the session.
     *
     * @param sessionId Indicates the session ID.
     * @return Returns <b>0</b> if the session connection is accepted; returns a non-zero value
     * otherwise (you do not need to call {@link CloseSession} to close the session).
     * @since 1.0
     * @version 1.0
     */
    int (*onSessionOpened)(int sessionId);
    /**
     * @brief Called when a session is closed.
     *
     * This function can be used to release resources related to the session.
     * You do not need to call {@link CloseSession}.
     *
     * @param sessionId Indicates the session ID.
     * @since 1.0
     * @version 1.0
     */
    void (*onSessionClosed)(int sessionId);
    /**
     * @brief Called when data is received.
     *
     * This function is used to notify that data is received.
     *
     * @param sessionId Indicates the session ID.
     * @param data Indicates the pointer to the data received.
     * @param dataLen Indicates the length of the data received.
     * @since 1.0
     * @version 1.0
     */
    void (*onBytesReceived)(int sessionId, const void *data, unsigned int dataLen);
};

/**
 * @brief Creates a session server based on a module name and session name.
 *
 * A maximum of 18 session servers can be created.
 *
 * @param moduleName Indicates the pointer to the module name, which can be used to check whether the
 * session server is in this module. The value cannot be empty and can contain a maximum of 64 characters.
 * @param sessionName Indicates the pointer to the session name, which is the unique ID of the session server.
 * The value cannot be empty and can contain a maximum of 64 characters.
 * @param listener Indicates the pointer to the session callback structure, which cannot be empty.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @see RemoveSessionServer
 * @since 1.0
 * @version 1.0
 */
int CreateSessionServer(const char *mouduleName, const char *sessionName, struct ISessionListener *listener);

/**
 * @brief Removes a session server based on a module name and session name.
 *
 * @param moduleName Indicates the pointer to the name of the registered module, which can be used to check
 * whether the session server is in this module. The value cannot be empty and can contain a maximum of 64 characters.
 * @param sessionName Indicates the pointer to the session name. The value cannot be empty and can contain
 * a maximum of 64 characters.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @see CreateSessionServer
 * @since 1.0
 * @version 1.0
 */
int RemoveSessionServer(const char *mouduleName, const char *sessionName);

/**
 * @brief Sends data based on a session ID.
 *
 * @param sessionId Indicates the session ID.
 * @param data Indicates the pointer to the data to send, which cannot be <b>NULL</b>.
 * @param len Indicates the length of the data to send. The maximum length cannot exceed 984 characters.
 * @return Returns <b>0</b> if the function is called successfully; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int SendBytes(int sessionId, const void *data, unsigned int len);

/**
 * @brief Obtains the session name registered by the local device based on the session ID.
 *
 * @param sessionId Indicates the session ID.
 * @param sessionName Indicates the pointer to the buffer for storing the session name.
 * @param len Indicates the length of the buffer.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetMySessionName(int sessionId, char *sessionName, unsigned int len);

/**
 * @brief Obtains the session name registered by the peer device based on the session ID.
 *
 * @param sessionId Indicates the session ID.
 * @param sessionName Indicates the pointer to the buffer for storing the session name.
 * @param len Indicates the length of the buffer.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetPeerSessionName(int sessionId, char *sessionName, unsigned int len);

/**
 * @brief Obtains the peer device ID based on a session ID.
 *
 * @param sessionId Indicates the session ID.
 * @param devId Indicates the pointer to the buffer for storing the device ID.
 * @param len Indicates the length of the buffer.
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetPeerDeviceId(int sessionId, char *devId, unsigned int len);

/**
 * @brief Closes a connected session based on a session ID.
 *
 * @param sessionId Indicates the session ID.
 * @since 1.0
 * @version 1.0
 */
void CloseSession(int sessionId);
#ifdef __cplusplus
}
#endif
#endif  // SESSION_H
