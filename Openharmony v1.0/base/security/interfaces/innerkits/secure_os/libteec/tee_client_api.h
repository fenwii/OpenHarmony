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

#ifndef _TEE_CLIENT_API_H_
#define _TEE_CLIENT_API_H_

#include <string.h>
#include "tee_client_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define S_VAR_NOT_USED(variable)  do { (void)(variable); } while (0)

/**
 * @ingroup TEEC_BASIC_FUNC
 * Calculate the values of the transfer parameters between REE and TEE
 */
#define TEEC_PARAM_TYPES(param0Type, param1Type, param2Type, param3Type) \
    ((param3Type) << 12 | (param2Type) << 8 | (param1Type) << 4 | (param0Type))

/**
 * @ingroup TEEC_BASIC_FUNC
 * Get the index value in parmaTypes
 */
#define TEEC_PARAM_TYPE_GET(paramTypes, index) \
    (((paramTypes) >> (4 * (index))) & 0x0F)

/**
 * @ingroup TEEC_BASIC_FUNC
 * When the parameter type is #teec_value, if the member variable a or b is not assigned,
 * you need to assign this value to it, indicates that this member variable is not used.
 */
#define TEEC_VALUE_UNDEF 0xFFFFFFFF

/**
 * @ingroup TEEC_VERSION
 * TEEC version number 1.0 : TrustedCore1.xx version
 */
#define TEEC_VERSION (100)


/**
 * @ingroup TEEC_BASIC_FUNC
 * Debug interface, it is valid when the macro TEEC_DEBUG is defined
 */
#ifdef TEEC_DEBUG
#define TEEC_Debug(fmt, args...) printf("%s: " fmt, __func__, ## args);
#else
#define TEEC_Debug(fmt, args...)
#endif

/**
 * @ingroup TEEC_BASIC_FUNC
 * Debug interface，API print error message
 */
#define TEEC_Error(fmt, args...) printf("%s: " fmt, __func__, ## args);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Initialize the TEE context
 *
 * @par Description
 * Initialize the TEE context whose path is 'name'. The 'name' parameter can be left empty,
 * TEE initialization is the basis for opening a session and sending a command,
 * after the initialization is successful, a connection is set up between the CA and the TEE.
 *
 * @param name [IN] Tee context path
 * @param context [IN/OUT] Context pointer，secure world environment handle
 *
 * @retval #TEEC_SUCCESS TEE context is successfully initialized
 * @retval #TEEC_ERROR_BAD_PARAMETERS Parameter is incorrect, name is incorrect or context is empty
 * @retval #TEEC_ERROR_GENERIC System resources are insufficient
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 * @see TEEC_FinalizeContext
 */
TEEC_Result TEEC_InitializeContext(
    const char *name,
    TEEC_Context *context);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Close tee context
 *
 * @par Description
 * Close the TEE context to which the 'context' points, and disconnect the client application from the TEE environment.
 *
 * @param context [IN/OUT] The TEE context that has been successfully initialized
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 * @see TEEC_InitializeContext
 */
void TEEC_FinalizeContext(
    TEEC_Context *context);

/*
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Open session
 *
 * @par Description
 * Create a session which is from CA to the 'destination' UUID TA,
 * the connection method is 'connectionMethod', and the connection data is 'connectionData',
 * The transferred data is contained in the 'opetation'.
 * After a session is opened successfully, the output parameter 'session' is a description of the connection.
 * If the session fails to be opened, 'returnOrigin' is the error source.
 *
 * @param context [IN/OUT] The TEE context that has been successfully initialized
 * @param session [OUT] Point to the session, the value cannot be empty.
 * @param destination [IN] UUID of a security service, a security service has a unique UUID.
 * @param connectionMethod [IN] Connection mode. The value range is #TEEC_LoginMethod.
 * @param connectionData [IN] Connection data corresponding to the link mode
 * If connection mode is #TEEC_LOGIN_PUBLIC, #TEEC_LOGIN_USE,
 * #TEEC_LOGIN_USER_APPLICATION, #TEEC_LOGIN_GROUP_APPLICATION, connection data must be empty.
 * If connection mode is #TEEC_LOGIN_GROUP、#TEEC_LOGIN_GROUP_APPLICATION，
 * the connection data must point to data of type uint32_t,
 * which represents the user group that the client application expects to connect to.
 * @param operation [IN/OUT] Data transferred between CAs and TAs
 * @param returnOrigin [IN/OUT] Error source. The value range is #TEEC_ReturnCodeOrigin.
 *
 * @retval #TEEC_SUCCESS  Open successfully.
 * @retval #TEEC_ERROR_BAD_PARAMETERS The parameter is incorrect.
 * @retval #TEEC_ERROR_ACCESS_DENIED Failed to access the system call permission.
 * @retval #TEEC_ERROR_OUT_OF_MEMORY Insufficient system resources.
 * @retval #TEEC_ERROR_TRUSTED_APP_LOAD_ERROR Failed to load the security service.
 * @retval Other return values, see. #TEEC_ReturnCode

 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 * @see TEEC_CloseSession
 */
TEEC_Result TEEC_OpenSession(
    TEEC_Context *context,
    TEEC_Session *session,
    const TEEC_UUID *destination,
    uint32_t connectionMethod,
    const void *connectionData,
    TEEC_Operation *operation,
    uint32_t *returnOrigin);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Close session
 *
 * @par Description
 * Close the session to which the session points, and disconnect the client application from the security service.
 *
 * @param session [IN/OUT] Point to a session that has been opened successfully

 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 * @see TEEC_OpenSession
 */
void TEEC_CloseSession(
    TEEC_Session *session);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Send a command.
 *
 * @par Description
 * In a specified 'session', the CA sends the 'commandID' command to the TA.
 * The sent data is 'operation'.
 * If the command fails to be sent, the 'returnOrigin' indicate the error source.
 *
 * @param session [IN/OUT] Point to a session that has been successfully opened
 * @param commandID [IN] Command ID supported by the security service, which is defined by the security service.
 * @param operation [IN/OUT] Contain the data sent from the CA to the TA.
 * @param returnOrigin [IN/OUT] Error source. The value range is #TEEC_ReturnCodeOrigin.
 *
 * @retval #TEEC_SUCCESS Command sent successfully.
 * @retval #TEEC_ERROR_BAD_PARAMETERS The parameter is incorrect,
 *         the session parameter is empty or the operation parameter is in an incorrect format.
 * @retval #TEEC_ERROR_ACCESS_DENIED Failed to access the system call permission.
 * @retval #TEEC_ERROR_OUT_OF_MEMORY Insufficient system resources.
 * @retval other return values, see. #TEEC_ReturnCode
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 */
TEEC_Result TEEC_InvokeCommand(
    TEEC_Session     *session,
    uint32_t          commandID,
    TEEC_Operation   *operation,
    uint32_t         *returnOrigin);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Register the Shared Memory
 *
 * @par Description
 * Registers the shared memory 'sharedMem' in the specified TEE 'context'，
 * the operating system needs to support zero copy to obtain the shared memory through registration,
 * in the current implementation, zero copy cannot be implemented in this mode.
 *
 * @attention If the size field of the input parameter 'sharedMem' is set to 0,
 *        the function returns a success message, but this Shared memory field cannot be used,
 *        because this memory has no size
 * @param context [IN/OUT] TEE context that has been successfully initialized
 * @param sharedMem [IN/OUT] Pointer to the shared memory, the memory cannot be null or 0.
 *
 * @retval #TEEC_SUCCESS Command sent successfully.
 * @retval #TEEC_ERROR_BAD_PARAMETERS The parameter is incorrect. The context or sharedMem parameter is empty，
 * or the memory to which the shared memory points is empty.
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 * @see TEEC_AllocateSharedMemory
 */
TEEC_Result TEEC_RegisterSharedMemory(
    TEEC_Context *context,
    TEEC_SharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Apply for Shared Memory
 *
 * @par Description
 * Apply for the shared memory 'sharedMem' in the specified TEE 'context',
 * the shared memory can implement zero copy when data is transferred
 * between the non-secure world and the secure world.
 *
 * @attention If the size field of the input parameter 'sharedMem' is set to 0,
 * the function returns a success message, but this shared memory cannot be used,
 * because this memory has neither address nor size.
 * @param context [IN/OUT] TEE environment that has been successfully initialized
 * @param sharedMem [IN/OUT] Point to the shared memory. The size of the shared memory cannot be 0.
 *
 * @retval #TEEC_SUCCESS Command sent successfully.
 * @retval #TEEC_ERROR_BAD_PARAMETERS The parameter is incorrect. The context or sharedMem parameter is empty.
 * @retval #TEEC_ERROR_OUT_OF_MEMORY Allocation failed due to insufficient system resources.
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 * @see TEEC_RegisterSharedMemory
 */
TEEC_Result TEEC_AllocateSharedMemory(
    TEEC_Context *context,
    TEEC_SharedMemory *sharedMem);

 /**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Release the shared memory.
 *
 * @par Description
 * Releases the shared memory that has been registered or applied for.
 *
 * @attention If the shared memory is obtained in #TEEK_AllocateSharedMemory mode, When the memory is released,
 * the memory is reclaimed. If the #TEEK_RegisterSharedMemory method is used:Obtained shared memory.
 * The local memory to which the shared memory points is not reclaimed when the shared memory is released.
 * @param sharedMem [IN/OUT] Pointing to the shared memory that has been registered or applied for successfully
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 * @see TEEC_RegisterSharedMemory | TEEC_AllocateSharedMemory
 */
void TEEC_ReleaseSharedMemory(
    TEEC_SharedMemory *sharedMem);


/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief cancel API
 *
 * @par Description
 * Cancel a running open session or an invoke command.
 * Send a cancel signal and return immediately.
 *
 * @attention This operation only sends a cancel message,
 *            whether to perform the cancel operation is determined by the TEE or TA.
 * @param operation [IN/OUT] Contains the data sent from the CA to the TA.
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 */
void TEEC_RequestCancellation(const TEEC_Operation *operation);

/**
 * @ingroup  TEEC_EXT_FUNC
 * @brief register agent API
 *
 * @par Description
 * Register the agent (listener) with the REE
 *
 * @attention This operation first maps and registers the shared memory (only 4 KB shared memory is supported),
 * then register the agent.
 * @param agent_id [IN] Agent_id is the unique identifier for communicating with the TA,
 * so TA use this agent_id to send a message to the CA
 * @param dev_fd [OUT] The descriptor for accessing the TEE driver device.
 * @param buffer [OUT] User-Mode Address Pointing to the Shared Memory
 * @retval #TEEC_SUCCESS agent regiter success
 * @retval #TEEC_ERROR_GENERIC generic error
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 */
TEEC_Result TEEC_EXT_RegisterAgent(uint32_t agentId, int *devFd, void **buffer);

/**
 * @ingroup  TEEC_EXT_FUNC
 * @brief wait for event from TA
 *
 * @par Description
 * REE agent wait for TEE TA evnet
 *
 * @attention This API will be blocked, invoking this API in the newly thread is suggested.
 * @param agent_id [IN] Agent_id is the unique identifier for communicating with the TA,
 * so TA use this agent_id to send a message to the CA
 * @param dev_fd [IN] The descriptor for accessing the TEE driver device.
 * @retval #TEEC_SUCCESS agent wait for TA message success
 * @retval #TEEC_ERROR_GENERIC generic error
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header file
 */
TEEC_Result TEEC_EXT_WaitEvent(uint32_t agentId, int devFd);

/**
 * @ingroup  TEEC_EXT_FUNC
 * @brief send response to TA
 *
 * @par Description
 * Agent response TA event
 *
 * @attention This API will wake up main thread
 * @param agent_id [IN]  Agent_id is the unique identifier for communicating with the TA,
 * so TA use this agent_id to send a message to the CA
 * @param dev_fd [IN] The descriptor for accessing the TEE driver device.
 * @retval #TEEC_SUCCESS Agent response send success
 * @retval #TEEC_ERROR_GENERIC Generic error
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header
 */
TEEC_Result TEEC_EXT_SendEventResponse(uint32_t agentId, int devFd);

/**
 * @ingroup  TEEC_EXT_FUNC
 * @brief unregister agent API
 *
 * @par Description
 * Agent（listener）unregister
 *
 * @attention The API instructs the kernel to deregister the agent and release the shared memory.
 * Therefore, the user-mode pointer cannot be used any more.
 * @param agent_id [IN] Agent_id is the unique identifier for communicating with the TA,
 * so TA use this agent_id to send a message to the CA
 * @param dev_fd [IN] The descriptor for accessing the TEE driver device.
 * @param buffer [IN] The user-state address that shares memory, and the function returns with a pointer null
 * @retval #TEEC_SUCCESS Agent unregister success
 * @retval #TEEC_ERROR_GENERIC Generic error
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header
 */
TEEC_Result TEEC_EXT_UnregisterAgent(uint32_t agentId, int devFd, void **buffer);

/**
 * @ingroup  TEEC_GetTEEVersion
 * @brief send response to TA
 *
 * @par Description
 * Ree get tee version
 *
 * @par Dependency
 * @li libteec: library
 * @li tee_client_api.h: header
 */
uint32_t TEEC_GetTEEVersion(void);

/**
 * Function:       TEEC_Send_Secfile
 * Description:   This function sends a secfile to TEE and saves it for use.
 * Parameters:   session: the session to close.
 * Return:         NULL
 */
TEEC_Result TEEC_SendSecfile(const char *path, TEEC_Session *session);

#ifdef __cplusplus
}
#endif

#endif
