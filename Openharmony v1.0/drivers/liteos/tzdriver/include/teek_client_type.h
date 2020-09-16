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

#ifndef _TEE_CLIENT_TYPE_H_
#define _TEE_CLIENT_TYPE_H_
#define SECURITY_AUTH_ENHANCE
#include "teek_client_constants.h"
#include "teek_client_list.h"
#define TOKEN_SAVE_LEN    24
#define CLOCK_NODE_LEN    8
#define TEE_PARAM_NUM   4

/*
 * @ingroup teec_common_data
 * define NULL
 */
#ifndef NULL
#define NULL 0
#endif

/*
 * @ingroup teec_common_data
 * Function return value type
 */
typedef uint32_t TeecResult;

/*
 * @ingroup teec_common_data
 * uuid type def
 *
 * uuid type follow rfc4122 [2]，is used to identify the security service.
 */
typedef struct {
    /* Lower 4 bytes of the timestamp */
    uint32_t timeLow;
    /* Middle 2 bytes of the timestamp */
    uint16_t timeMid;
    /* Combination of higher 2 bytes of the timestamp and version */
    uint16_t timeHiAndVersion;
    /* Combination of clock sequence and node identifier */
    uint8_t clockseqAndNode[CLOCK_NODE_LEN];
} TeecUuid;

/*
 * @ingroup teec_common_data
 * teec_context struct definition
 *
 * Describes the connect context between client applications and the secure world.
 */
typedef struct {
    void *dev;
    uint8_t *ta_path;
    /* session list */
    struct ListNode sessionList;
    /* shared memory list */
    struct ListNode shrdMemList;
} TeecContext;

/*
 * @ingroup teec_common_data
 * teec_session
 *
 * Describes the sessions established between CAs and the TEE.
 */
typedef struct {
    /* Session ID, which is returned by the TEE. */
    uint32_t sessionId;
    /* Indicates the UUID of a security service. Each TA has a unique UUID. */
    TeecUuid serviceId;
    /* Number of operations in a session. */
    uint32_t opsCnt;
    /* Session linked list header */
    struct ListNode head;
    /* Point to the Tee context to which the session belongs */
    TeecContext *context;
#ifdef SECURITY_AUTH_ENHANCE
    /* token_save_len  24byte = token  16byte + timestamp  8byte */
    uint8_t teecToken[TOKEN_SAVE_LEN];
#endif
} TeecSession;

/*
 * @ingroup teec_common_data
 * teec_sharedmemory
 *
 * Describes a piece of shared memory that can be registered or allocated.
 */
typedef struct {
    /* Memory pointer */
    void *buffer;
    /* Memory Size */
    size_t size;
    /* Memory flags which is used to distinguish between input and output, range is as follows:#teec_sharedmemctl */
    uint32_t flags;
    /* Number of memory operations */
    uint32_t opsCnt;
    /* Memory allocation identifier, which is used to identify whether the memory is registered or allocated. */
    bool isAllocated;
    /* Linked list header of the shared memory */
    struct ListNode head;
    /* The Tee context to which the object belongs. */
    TeecContext *context;
} TeecSharedMemory;

/*
 * @ingroup teec_common_data
 * teec_tempmemory_reference
 *
 * A temporary buffer is used for #teec_parameter, corresponding to which can be
 * #teec_memref_temp_input, #teec_memref_temp_output，or #teec_memref_temp_inout
 */
typedef struct {
    /* temporary buffer pointer */
    void *buffer;
    /* temporary buffer size */
    size_t size;
} TeecTempmemoryReference;

/*
 * @ingroup teec_common_data
 * teec_registeredmemory_reference
 *
 * Indicates the pointer of the shared memory, which points to the registered or allocated shared memory.
 * The type that can be used for #teec_parameter, corresponding to which can be
 * #teec_memref_whole， #teec_memref_partial_input，
 * #teec_memref_partial_output，or #teec_memref_partial_inout
 */
typedef struct {
    /* shared memory pointer */
    TeecSharedMemory *parent;
    /* shared memory size */
    size_t size;
    /* shared memory offset */
    size_t offset;
} TeecRegisteredmemoryReference;

/*
 * @ingroup teec_common_data
 * teec_value
 *
 * Describe a small amount of data
 * The type that can be used for #teec_parameter, corresponding to which can be
 * #teec_value_input, #teec_value_output, or #teec_value_inout
 */
typedef struct {
    uint32_t a;
    uint32_t b;
} TeecValue;

/*
 * @ingroup teec_common_data
 * teec_parameter
 *
 * Parameter type corresponding to #teec_operation.
 */
typedef union {
    TeecTempmemoryReference tmpref;
    TeecRegisteredmemoryReference memref;
    TeecValue value;
} TeecParameter;

/*
 * @ingroup teec_common_data
 * teec_operation
 *
 * Parameters used for opening a session or sending a command,
 * can also be used to cancel an operation
 */
typedef struct {
    /* Indicates whether the operation is canceled. 0 indicates canceled. */
    uint32_t started;
    uint32_t paramTypes;
    TeecParameter params[TEE_PARAM_NUM];
    TeecSession *session;
    bool cancelFlag;
} TeecOperation;

#endif
