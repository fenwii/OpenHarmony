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

#ifndef _TEE_CLIENT_TYPE_H_
#define _TEE_CLIENT_TYPE_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <semaphore.h>
#include "tee_list.h"
#include "tee_client_constants.h"

/*
 * @ingroup TEEC_COMMON_DATA
 * bool type
 */
#ifndef __cplusplus
#ifndef bool
#define bool    uint8_t
#endif
#endif

/*
 * @ingroup TEEC_COMMON_DATA
 * define true
 */
#ifndef true
#define true    1
#endif

/*
 * @ingroup TEEC_COMMON_DATA
 * define false
 */
#ifndef false
#define false   0
#endif

/*
 * @ingroup TEEC_COMMON_DATA
 * define NULL
 */
#ifndef NULL
#define NULL 0
#endif

/*
 * @ingroup TEEC_COMMON_DATA
 * define function return
 *
 * indicate the result of a function
 */
typedef enum TEEC_ReturnCode TEEC_Result;

/*
 * @ingroup TEEC_COMMON_DATA
 * UUID type
 *
 * UUID type follow RFC4122 [2]，indicate SA
 */
typedef struct {
    uint32_t timeLow;           /* Lower 4 bytes of the timestamp */
    uint16_t timeMid;           /* Middle 2 bytes of the timestamp */
    uint16_t timeHiAndVersion;  /* Combination of higher 2 bytes of the timestamp and version */
    uint8_t clockSeqAndNode[8]; /* Combination of clock sequence and node identifier */
} TEEC_UUID;

/*
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Context struct definition
 *
 * Describes the connect context between client applications and the secure world.
 */
typedef struct {
    int32_t fd;  /* file descriptor */
    uint8_t *ta_path;
    tee_list_t session_list;  /* session list */
    tee_list_t shrd_mem_list; /* shared memory list */
    struct {
        void *buffer;
        sem_t buffer_barrier;
    } share_buffer;
} TEEC_Context;

/*
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Session struct definition
 *
 * Describes the sessions established between CAs and the TEE.
 */
typedef struct {
    uint32_t session_id;    /* Session ID, which is returned by the TEE */
    TEEC_UUID service_id;   /* Indicates the UUID of a security service. Each TA has a unique UUID */
    uint32_t ops_cnt;       /* Number of operations in a session */
    tee_list_t head;   /* Session linked list header  */
    TEEC_Context *context;  /* Pointing to the Tee context to which the session belongs */
} TEEC_Session;

/*
 * @ingroup TEEC_COMMON_DATA
 * TEEC_SharedMemory struct definition
 *
 * Describes a piece of shared memory that can be registered or allocated.
 */
typedef struct {
    void *buffer;           /* Memory pointer */
    uint32_t size;          /* Memory Size */

    /* Memory flags which is used to distinguish between input and output, range is as follows:#teec_sharedmemctl */
    uint32_t flags;
    uint32_t ops_cnt;       /* Number of memory operations */

    /* Memory allocation identifier, which is used to identify whether the memory is registered or allocated. */
    bool is_allocated;
    tee_list_t head;   /*  Linked list header of the shared memory */
    TEEC_Context *context;  /* The Tee context to which the object belongs */
} TEEC_SharedMemory;

/*
 * @ingroup TEEC_COMMON_DATA
 * TEEC_TempMemoryReference struct definition
 *
 * A temporary buffer is used for #TEEC_Parameter, corresponding to which can be
 * #TEEC_MEMREF_TEMP_INPUT, #TEEC_MEMREF_TEMP_OUTPUT, #TEEC_MEMREF_TEMP_INOUT
 */
typedef struct {
    void *buffer;   /* temporary buffer pointer */
    uint32_t size;  /* temporary buffer size */
} TEEC_TempMemoryReference;

/*
 * @ingroup TEEC_COMMON_DATA
 * TEEC_RegisteredMemoryReference struct definition
 *
 * Indicates the pointer of the shared memory, which points to the registered or allocated shared memory.
 * The type that can be used for #teec_parameter, corresponding to which can be
 * #TEEC_MEMREF_WHOLE，， #TEEC_MEMREF_PARTIAL_INPUT，
 * #TEEC_MEMREF_PARTIAL_OUTPUT，or #TEEC_MEMREF_PARTIAL_INOUT
 */
typedef struct {
    TEEC_SharedMemory *parent;  /* shared memory pointer */
    uint32_t size;              /* shared memory size */
    uint32_t offset;            /* shared memory offset */
} TEEC_RegisteredMemoryReference;

/*
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Value struct definition
 *
 * Describe a small amount of data
 * The type that can be used for #teec_parameter, corresponding to which can be
 * #TEEC_VALUE_INPUT, #TEEC_VALUE_OUTPUT, or #TEEC_VALUE_INOUT
 */
typedef struct {
    uint32_t a;
    uint32_t b;
} TEEC_Value;

typedef struct {
    int ion_share_fd;
    uint32_t ion_size;
} TEEC_IonReference;

/*
 * @ingroup TEEC_COMMON_DATA
 * TEEC_Parameter union definition
 *
 * Parameter type corresponding to #teec_operation.
 */
typedef union {
    TEEC_TempMemoryReference tmpref;
    TEEC_RegisteredMemoryReference memref;
    TEEC_Value value;
    TEEC_IonReference ionref;
} TEEC_Parameter;

/*
 * @ingroup TEEC_COMMON_DATA
  * TEEC_Operation struct definition
  *
 * Parameters used for opening a session or sending a command,
 * can also be used to cancel an operation
 */
typedef struct {
    uint32_t started;     /* Indicates whether the operation is canceled. 0 indicates canceled. */
    uint32_t paramTypes;  /* #TEEC_ParamType，need #TEEC_PARAM_TYPES combine paramer type */
    TEEC_Parameter params[TEEC_PARAM_NUM];
    TEEC_Session *session;
    bool cancel_flag;
} TEEC_Operation;

/*
 * @ingroup TEEC_COMMON_DATA
 * TEEC_EXT_TEEInfo struct definition
 *
 * Get TEE version number and other info
 */
typedef struct {
    uint32_t version;
    uint32_t reserve1;
    uint32_t reserve2;
    uint32_t reserve3;
} TEEC_EXT_TEEInfo;
#endif
