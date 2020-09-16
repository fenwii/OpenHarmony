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

#ifndef _TEE_CLIENT_INNER_H_
#define _TEE_CLIENT_INNER_H_

#include <pthread.h>
#include <semaphore.h>
#include "tee_client_constants.h"
#include "tee_list.h"

#define IS_TEMP_MEM(paramType)                                                              \
    (((paramType) == TEEC_MEMREF_TEMP_INPUT) || ((paramType) == TEEC_MEMREF_TEMP_OUTPUT) || \
     ((paramType) == TEEC_MEMREF_TEMP_INOUT))

#define IS_PARTIAL_MEM(paramType)                                                        \
    (((paramType) == TEEC_MEMREF_WHOLE) || ((paramType) == TEEC_MEMREF_PARTIAL_INPUT) || \
     ((paramType) == TEEC_MEMREF_PARTIAL_OUTPUT) || ((paramType) == TEEC_MEMREF_PARTIAL_INOUT))

#define IS_VALUE_MEM(paramType) \
    (((paramType) == TEEC_VALUE_INPUT) || ((paramType) == TEEC_VALUE_OUTPUT) || ((paramType) == TEEC_VALUE_INOUT))

#define NUM_OF_SHAREMEM_BITMAP 8

typedef struct {
    int32_t fd;                    /* file descriptor */
    tee_list_t session_list;  /* session list  */
    tee_list_t shrd_mem_list; /* share memory list */
    struct {
        void *buffer;
        sem_t buffer_barrier;
    } share_buffer; /* share_buffer only used in Qualcomm platform */
    uint8_t shm_bitmap[NUM_OF_SHAREMEM_BITMAP];
    tee_list_t c_node; /* context list node  */
    uint32_t ops_cnt;
    pthread_mutex_t sessionLock;
    pthread_mutex_t shrMemLock;
    pthread_mutex_t shrMemBitMapLock;
    bool callFromHal; /* true:from hal,false:from vendor */
} TEEC_ContextHal;

typedef struct {
    void *buffer;              /* memory pointer */
    uint32_t size;             /* memory size */
    uint32_t flags;            /* memory flag, distinguish between input and output, range in #TEEC_SharedMemCtl */
    uint32_t ops_cnt;          /* memoty operation cnt */
    bool is_allocated;         /* memory allocated flag, distinguish between registered or distributed */
    tee_list_t head;      /* head of shared memory list */
    TEEC_ContextHal *context; /* point to its own TEE environment */
    uint32_t offset;
} TEEC_SharedMemoryHal;

typedef struct {
    const uint8_t *taPath;
    FILE *taFp;
} TaFileInfo;

#endif
