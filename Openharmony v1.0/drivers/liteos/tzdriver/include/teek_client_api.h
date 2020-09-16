/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* @defgroup TEEC_API client(REE) interface
 * @defgroup TEEC_BASIC_FUNC common interface
 * @ingroup TEEC_API
 */

#ifndef _TEEK_CLIENT_API_H_
#define _TEEK_CLIENT_API_H_
#include "teek_client_type.h"
#include "teek_ns_client.h"

/*
  * @ingroup TEEC_BASIC_FUNC
  * Calculate the values of the transfer parameters between REE and TEE
  */
#define TEEC_PARAM_TYPES(param0_type, param1_type, param2_type, param3_type) \
        (((param3_type) << 12) | ((param2_type) << 8) | \
         ((param1_type) << 4) | (param0_type))

/*
 * @ingroup TEEC_BASIC_FUNC
 * Get the index value in parmaTypes
 */
#define TEEC_PARAM_TYPE_GET(paramTypes, index) \
        (((paramTypes) >> ((index) << 2)) & 0x0F)

/*
 * @ingroup TEEC_BASIC_FUNC
 * When the parameter type is #teec_value, if the member variable a or b is not assigned,
 * you need to assign this value to it, indicates that this member variable is not used.
 */
#define TEEC_VALUE_UNDEF 0xFFFFFFFF

/*
 * Function:      TeekIsAgentAlive
 * Description:   This function check if the special agent is launched.
 *                         Used For HDCP key.
 *                         e.g. If sfs agent is not alive,
 *                         you can not do HDCP key write to SRAM.
 * Parameters:    agentId.
 * Return:        1:agent is alive
 *                0:agent not exsit.
 */
int TeekIsAgentAlive(unsigned int agentId);

/*
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Initialize the TEE context
 *
 * @par Description
 * Initialize the TEE context whose path is 'name'. The 'name' can be left empty,
 * TEE initialization is the basis for opening a session and sending a command,
 * after the initialization is successful, a connection is set up between the CA and the TEE.
 *
 * @param name [IN] Tee context path
 * @param context [IN/OUT] context pointer，secure world environment handle
 *
 * @retval #TEEC_SUCCESS  TEE context is successfully initialized
 * @retval #TEEC_ERROR_BAD_PARAMETERS  Parameter is incorrect, 'name' is incorrect or context is empty
 * @retval #TEEC_ERROR_GENERIC  System resources are insufficient
 */
TeecResult TeekInitializeContext(const char *name, TeecContext *context);

/*
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Close the tee context
 *
 * @par Description
 * Close the TEE context to which the 'context' points, and disconnect the client application from the TEE environment.
 *
 * @param context [IN/OUT] The TEE context that has been successfully initialized
 *
 */
void TeekFinalizeContext(TeecContext *context);

/*
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Open session
 *
 * @par Description
 * Create a session which is from CA to the 'destination' UUID TA,
 * the connection method is 'connectionMethod', and the link data is 'connectionData',
 * The transferred data is contained in the 'opetation'.
 * After a session is opened successfully, the output parameter 'session' is a description of the link.
 * If the session fails to be opened, 'returnOrigin' is the error source.
 *
 * @param context [IN/OUT] The TEE context that has been successfully initialized
 * @param session [OUT] Pointed to the session, the value cannot be empty
 * @param destination [IN] UUID of a security service, a security service has a unique UUID.
 * @param connectionMethod [IN] Connection mode. The value range is #TEEC_LoginMethod.
 * @param connectionData [IN] Connection data corresponding to the connection mode
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
 */
TeecResult TeekOpenSession(TeecContext *context,
    TeecSession *session,
    const TeecUuid *destination,
    uint32_t connectionMethod,
    const void *connectionData,
    const TeecOperation *operation,
    uint32_t *returnOrigin);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Close session
 *
 * @par Description
 * Close the session to which the 'session' points, and disconnect the client application from the security service.
 *
 * @param session [IN/OUT] Point to a session that has been opened successfully
 */
void TeekCloseSession(TeecSession *session);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Send a command.
 *
 * @par Description
 * In a specified 'session', the CA sends the 'commandID' command to the TA.
 * The sent data is 'operation'.
 * If the command fails to be sent, the 'returnOrigin' indicate the error source.
 *
 * @param session [IN/OUT] Pointing to a session that has been successfully opened
 * @param commandID [IN] Command ID supported by the security service, which is defined by the security service.
 * @param operation [IN/OUT] Contains the data sent from the CA to the TA.
 * @param returnOrigin [IN/OUT] Error source. The value range is #TEEC_ReturnCodeOrigin.
 *
 * @retval #TEEC_SUCCESS Command sent successfully.
 * @retval #TEEC_ERROR_BAD_PARAMETERS The parameter is incorrect,
 *         the session parameter is empty or the operation parameter is in an incorrect format.
 * @retval #TEEC_ERROR_ACCESS_DENIED Failed to access the system call permission.
 * @retval #TEEC_ERROR_OUT_OF_MEMORY Insufficient system resources.
 * @retval other return values, see. #TEEC_ReturnCode
 */
TeecResult TeekInvokeCommand(TeecSession *session,
    uint32_t commandID,
    TeecOperation *operation,
    uint32_t *returnOrigin);

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
 *        the function returns a success message, but this field cannot be used.Shared memory,
 *        because this memory has no size
 * @param context [IN/OUT] TEE environment that has been successfully initialized
 * @param sharedMem [IN/OUT] Pointer to the shared memory, the memory cannot be null or 0.
 *
 * @retval #TEEC_SUCCESS Command sent successfully.
 * @retval #TEEC_ERROR_BAD_PARAMETERS The parameter is incorrect. The context or sharedMem parameter is empty，
 * or the memory to which the shared memory points is empty.
 */
TeecResult TeekRegisterSharedMemory(TeecContext *context,
    TeecSharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Apply for Shared Memory
 *
 * @par Description
 * Apply for the shared memory 'sharedMem' in the specified TEE 'context',
 * The shared memory can implement zero copy when data is transferred
 * between the non-secure world and the secure world.
 *
 * @attention If the size field of the input parameter 'sharedMem' is set to 0,
 * the function returns a success message, but this Shared memory field cannot be used,
 * because this memory has neither address nor size.
 * @param context [IN/OUT] TEE environment that has been successfully initialized
 * @param sharedMem [IN/OUT] Pointer to the shared memory. The size of the shared memory cannot be 0.
 *
 * @retval #TEEC_SUCCESS Command sent successfully.
 * @retval #TEEC_ERROR_BAD_PARAMETERS The parameter is incorrect. The context or sharedMem parameter is empty.
 * @retval #TEEC_ERROR_OUT_OF_MEMORY Allocation failed due to insufficient system resources.
 */
TeecResult TeekAllocateSharedMemory(TeecContext *context,
    TeecSharedMemory *sharedMem);

/**
 * @ingroup  TEEC_BASIC_FUNC
 * @brief Release the shared memory.
 *
 * @par Description
 * Releases the shared memory that has been registered or applied for.
 *
 * @attention If the shared memory is obtained in #TEEK_AllocateSharedMemory mode, When the memory is released,
 * the memory is reclaimed. If the #TEEK_RegisterSharedMemory method is used,
 * The local memory to which the shared memory points is not reclaimed when the shared memory is released.
 * @param sharedMem [IN/OUT] Point to the shared memory that has been registered or applied for successfully
 */
void TeekReleaseSharedMemory(TeecSharedMemory *sharedMem);

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
 */
void TeekRequestCancellation(TeecOperation *operation);

#endif
