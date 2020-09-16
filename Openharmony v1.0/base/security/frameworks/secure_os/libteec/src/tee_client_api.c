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

#include "tee_client_api.h"
#include <errno.h>     /* for errno */
#include <fcntl.h>
#include <securec.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h> /* for ioctl */
#include <sys/mman.h>  /* for mmap */
#include <sys/types.h> /* for open close */
#include <unistd.h>

#include "tc_ns_client.h"
#include "tee_auth_common.h"
#include "tee_ca_daemon.h"
#include "tee_client_app_load.h"
#include "tee_client_id.h"
#include "tee_client_inner.h"
#include "tee_list.h"
#include "tee_log.h"
#include "teec_compat.h"

#define TEE_ERROR_CA_AUTH_FAIL 0xFFFFCFE5

#define AGENT_BUFF_SIZE           0x1000
#define CA_AUTH_RETRY_TIMES       30
#define H_OFFSET                  32

#define SHIFT    3
#define MASK     0x7
#define BYTE_BIT 8

static void SetBit(uint32_t i, uint32_t byteMax, uint8_t *bitMap)
{
    if ((i >> SHIFT) >= byteMax) {
        return;
    }
    bitMap[i >> SHIFT] |= (1U << (i & MASK));
}

static void ClearBit(uint32_t i, uint32_t byteMax, uint8_t *bitMap)
{
    if ((i >> SHIFT) >= byteMax) {
        return;
    }
    bitMap[i >> SHIFT] &= ~(1U << (i & MASK));
}

static int32_t GetAndSetBit(uint8_t *bitMap, uint32_t byteMax)
{
    uint32_t i;
    uint32_t j;
    int32_t validBit = -1;

    for (i = 0; i < byteMax; i++) {
        if (bitMap[i] == 0xFF) {
            continue;
        }
        for (j = 0; j < BYTE_BIT; j++) {
            if (!(bitMap[i] & (0x1U << j))) {
                validBit = (int32_t)i * BYTE_BIT + (int32_t)j;
                break;
            }
        }

        if (validBit != -1) {
            break;
        }
    }

    if (validBit == -1) {
        return validBit;
    }

    SetBit(validBit, byteMax, bitMap);
    return validBit;
}

static pthread_mutex_t g_mutexAtom = PTHREAD_MUTEX_INITIALIZER;
static void AtomInc(volatile uint32_t *cnt)
{
    /*
     * The use of g_mutexAtom has been rigorously checked
     * and there is no risk of failure, we do not care the return value
     * of pthread_mutex_lock here
     */
    (void)pthread_mutex_lock(&g_mutexAtom);
    (*cnt)++;
    (void)pthread_mutex_unlock(&g_mutexAtom);
}

static bool AtomDecAndCompareWithZero(volatile uint32_t *cnt)
{
    bool result = false;

    /*
     * The use of g_mutexAtom has been rigorously checked
     * and there is no risk of failure, we do not care the return value
     * of pthread_mutex_lock here
     */
    (void)pthread_mutex_lock(&g_mutexAtom);
    (*cnt)--;
    if ((*cnt) == 0) {
        result = true;
    }
    (void)pthread_mutex_unlock(&g_mutexAtom);
    return result;
}

#ifdef SECURITY_AUTH_ENHANCE
typedef struct {
    uint8_t uuid[UUID_LEN];
    uint32_t sessionId;
    uint8_t teecToken[TOKEN_SAVE_LEN];
    int fd;
    tee_list_t tokenNode;
    uint32_t opsCnt;
} TC_NS_Token;

static tee_list_t g_teecTokenList = { &g_teecTokenList, &g_teecTokenList };
static pthread_mutex_t g_mutexTeecToken = PTHREAD_MUTEX_INITIALIZER;

static int32_t MutexLockToken(void)
{
    int lockRet = pthread_mutex_lock(&g_mutexTeecToken);
    tlogd("MutexLockToken: pthread_mutex_lock ret = %d.\n", lockRet);
    return lockRet;
}

static void MutexUnlockToken(int lockRet)
{
    if (lockRet) {
        tloge("MutexUnlockToken: not exe, mutex not in lock state.lockRet = %d.\n", lockRet);
        return;
    }

    (void)pthread_mutex_unlock(&g_mutexTeecToken);
}

static TC_NS_Token *FindToken(const TEEC_UUID *serviceId, uint32_t sessionId, int fd)
{
    TC_NS_Token *ret = NULL;
    TC_NS_Token *token = NULL;
    tee_list_t *ptr = NULL;

    bool condition = (serviceId == NULL) || (sessionId == 0x0) || (fd < 0x0);
    if (condition) {
        tlogd("FindToken: invalid params.\n");
        return NULL;
    }

    /* Paramters right, start execution */
    if (!TeeListEmpty(&g_teecTokenList)) {
        TEE_LIST_FOR_EACH(ptr, &g_teecTokenList) {
            token = TEE_LIST_ENTRY(ptr, TC_NS_Token, tokenNode);
            condition = (token == NULL) || (sessionId != token->sessionId) || (fd != token->fd) ||
                (memcmp(token->uuid, serviceId, sizeof(token->uuid)) != EOK);
            if (condition) {
                continue;
            }
            ret = token;
            break;
        }
    }
    return ret;
}

static TC_NS_Token *GetToken(const TEEC_UUID *serviceId, uint32_t sessionId, int fd)
{
    TC_NS_Token *token = NULL;

    int retMutexLock = MutexLockToken();
    if (retMutexLock != 0) {
        tloge("get token lock failed.\n");
        return NULL;
    }
    token = FindToken(serviceId, sessionId, fd);
    if (token != NULL) {
        AtomInc(&token->opsCnt);
    }
    MutexUnlockToken(retMutexLock);
    return token;
}

static void PutToken(TC_NS_Token *token)
{
    if (token == NULL) {
        tloge("put token: token is null.\n");
        return;
    }

    if (AtomDecAndCompareWithZero(&token->opsCnt)) {
        errno_t rc = memset_s(token, sizeof(TC_NS_Token), 0, sizeof(TC_NS_Token));
        if (rc != EOK) {
            tloge("memset token failed.\n");
        }
        free(token);
    }
    return;
}

static int32_t SaveToken(TC_NS_Token *sessionToken, const TC_NS_ClientContext *cliContext, int fd)
{
    int retMutexLock;

    if ((cliContext->session_id == 0x0) || (fd < 0x0)) {
        tloge("SaveToken: invalid  params.\n");
        return -EINVAL;
    }

    if (memcpy_s((void *)sessionToken->uuid, sizeof(sessionToken->uuid), cliContext->uuid, sizeof(cliContext->uuid)) !=
        EOK) {
        return -EINVAL;
    }
    sessionToken->sessionId = cliContext->session_id;
    sessionToken->fd = fd;
    TeeListInit(&(sessionToken->tokenNode));
    retMutexLock = MutexLockToken();
    if (retMutexLock != 0) {
        tloge("get token lock failed.\n");
        return -EPERM;
    }

    /* if token is in list, remove it */
    TC_NS_Token *token = FindToken((TEEC_UUID *)sessionToken->uuid, sessionToken->sessionId, fd);
    if (token != NULL) {
        TeeListDelete(&(token->tokenNode));
        PutToken(token);
    }

    TeeListTailInsert(&g_teecTokenList, &(sessionToken->tokenNode));
    MutexUnlockToken(retMutexLock);
    return EOK;
}

static void DelToken(const TEEC_UUID *serviceId, uint32_t sessionId, int fd)
{
    TC_NS_Token *token = NULL;

    int retMutexLock = MutexLockToken();
    if (retMutexLock != 0) {
        tloge("get token lock failed.\n");
        return;
    }
    token = FindToken(serviceId, sessionId, fd);
    if (token != NULL) {
        TeeListDelete(&(token->tokenNode));
    }
    MutexUnlockToken(retMutexLock);

    PutToken(token);
    return;
}
#endif

static tee_list_t g_teecContextList = { &g_teecContextList, &g_teecContextList };
static pthread_mutex_t g_mutexTeecContext = PTHREAD_MUTEX_INITIALIZER;
void TEEC_CloseSessionHal(TEEC_Session *session, const TEEC_ContextHal *context);
void TEEC_FinalizeContextHal(TEEC_ContextHal *context);

static int32_t MutexLockContext(void)
{
    int lockRet = pthread_mutex_lock(&g_mutexTeecContext);
    return lockRet;
}

static void MutexUnlockContext(int lockRet)
{
    if (lockRet) {
        tloge("%s: not exe, mutex not in lock state. lockRet = %d\n", __func__, lockRet);
        return;
    }
    (void)pthread_mutex_unlock(&g_mutexTeecContext);
}

static TEEC_Result AddSessionList(uint32_t sessionId, const TEEC_UUID *destination, TEEC_ContextHal *context,
    TEEC_Session *session)
{
    tee_list_t *node = NULL;
    tee_list_t *n = NULL;
    TEEC_Session *sessionEntry = NULL;

    session->session_id = sessionId;
    session->service_id = *destination;
    session->ops_cnt = 1;

    int lockRet = pthread_mutex_lock(&context->sessionLock);
    if (lockRet != 0) {
        tloge("get session lock failed.\n");
        return TEEC_ERROR_GENERIC;
    }
    /* if session is still in list, remove it */
    TEE_LIST_FOR_EACH_SAFE(node, n, &context->session_list) {
        sessionEntry = TEE_LIST_ENTRY(node, TEEC_Session, head);
        if (sessionEntry == session) {
            TeeListDelete(node);
        }
    }
    TeeListInit(&session->head);
    TeeListTailInsert(&context->session_list, &session->head);
    AtomInc(&session->ops_cnt);
    (void)pthread_mutex_unlock(&context->sessionLock);
    return TEEC_SUCCESS;
}

static TEEC_ContextHal *FindBnContext(const TEEC_Context *context)
{
    TEEC_ContextHal *sContext = NULL;

    if (context == NULL) {
        tloge("%s: context is NULL!\n", __func__);
        return NULL;
    }

    tee_list_t *ptr = NULL;
    if (!TeeListEmpty(&g_teecContextList)) {
        TEE_LIST_FOR_EACH(ptr, &g_teecContextList)
        {
            TEEC_ContextHal *tmp = TEE_LIST_ENTRY(ptr, TEEC_ContextHal, c_node);
            if (tmp->fd == context->fd) {
                sContext = tmp;
                break;
            }
        }
    }
    return sContext;
}

TEEC_ContextHal *GetBnContext(const TEEC_Context *context)
{
    TEEC_ContextHal *sContext = NULL;
    if (context == NULL) {
        return NULL;
    }

    int retMutexLock = MutexLockContext();
    if (retMutexLock != 0) {
        tloge("get context lock failed.\n");
        return NULL;
    }
    sContext = FindBnContext(context);
    if (sContext != NULL) {
        AtomInc(&sContext->ops_cnt);
    }
    MutexUnlockContext(retMutexLock);
    return sContext;
}

void PutBnContext(TEEC_ContextHal *context)
{
    if (context == NULL) {
        tloge("put context: context is NULL!\n");
        return;
    }

    if (AtomDecAndCompareWithZero(&context->ops_cnt)) {
        TEEC_FinalizeContextHal(context);
    }
    return;
}

TEEC_ContextHal *FindAndRemoveBnContext(const TEEC_Context *context)
{
    TEEC_ContextHal *sContext = NULL;
    if (context == NULL) {
        return NULL;
    }

    int retMutexLock = MutexLockContext();
    if (retMutexLock != 0) {
        tloge("get context lock failed.\n");
        return NULL;
    }
    sContext = FindBnContext(context);
    if (sContext != NULL) {
        TeeListDelete(&sContext->c_node);
    }
    MutexUnlockContext(retMutexLock);
    return sContext;
}

static TEEC_Session *FindBnSession(const TEEC_Session *session, TEEC_ContextHal *context)
{
    TEEC_Session *sSession = NULL;

    tee_list_t *ptr = NULL;
    if (!TeeListEmpty(&context->session_list)) {
        TEE_LIST_FOR_EACH(ptr, &context->session_list)
        {
            TEEC_Session *tmp = TEE_LIST_ENTRY(ptr, TEEC_Session, head);
            if (tmp->session_id == session->session_id) {
                sSession = tmp;
                break;
            }
        }
    }
    return sSession;
}

TEEC_Session *GetBnSession(const TEEC_Session *session, TEEC_ContextHal *context)
{
    TEEC_Session *sSession = NULL;

    if (session == NULL || context == NULL) {
        tloge("get session: context or session is NULL!\n");
        return NULL;
    }

    int lockRet = pthread_mutex_lock(&context->sessionLock);
    if (lockRet != 0) {
        tloge("get session lock failed.\n");
        return NULL;
    }
    sSession = FindBnSession(session, context);
    if (sSession != NULL) {
        AtomInc(&sSession->ops_cnt);
    }
    (void)pthread_mutex_unlock(&context->sessionLock);
    return sSession;
}

void PutBnSession(TEEC_Session *session)
{
    if (session == NULL) {
        tloge("put session: session is NULL!\n");
        return;
    }

    if (AtomDecAndCompareWithZero(&session->ops_cnt)) {
        free(session);
    }
    return;
}

TEEC_Session *FindAndRemoveSession(const TEEC_Session *session, TEEC_ContextHal *context)
{
    TEEC_Session *sSession = NULL;

    if (session == NULL || context == NULL) {
        tloge("find and remove session: context or session is NULL!\n");
        return NULL;
    }

    int lockRet = pthread_mutex_lock(&context->sessionLock);
    if (lockRet != 0) {
        tloge("get session lock failed.\n");
        return NULL;
    }
    sSession = FindBnSession(session, context);
    if (sSession != NULL) {
        TeeListDelete(&sSession->head);
    }
    (void)pthread_mutex_unlock(&context->sessionLock);
    return sSession;
}

static void ReleaseSharedMemory(TEEC_SharedMemoryHal *sharedMem)
{
    bool condition = (sharedMem->is_allocated) && (sharedMem->buffer != NULL) && (sharedMem->buffer != ZERO_SIZE_PTR) &&
                     (sharedMem->context != NULL) && (sharedMem->size != 0);
    if (condition) {
        int32_t ret = ioctl(sharedMem->context->fd, (int)TC_NS_CLIENT_IOCTL_UNMAP_SHARED_MEM, sharedMem->buffer);
        if (ret) {
            tloge("Release SharedMemory failed, ioctl error\n");
        }
        ret = munmap(sharedMem->buffer, sharedMem->size);
        if (ret) {
            tloge("Release SharedMemory failed, munmap error\n");
        }

        int lockRet = pthread_mutex_lock(&sharedMem->context->shrMemBitMapLock);
        if (lockRet != 0) {
            /* lock fail, but do not return here */
            tloge("get share mem lock failed.\n");
        } else {
            ClearBit(sharedMem->offset, sizeof(sharedMem->context->shm_bitmap), sharedMem->context->shm_bitmap);
            (void)pthread_mutex_unlock(&sharedMem->context->shrMemBitMapLock);
        }
    }

    sharedMem->buffer  = NULL;
    sharedMem->size    = 0;
    sharedMem->flags   = 0;
    sharedMem->ops_cnt = 0;
    sharedMem->context = NULL;
    free(sharedMem);
}

void PutBnShrMem(TEEC_SharedMemoryHal *shrMem)
{
    if (shrMem == NULL) {
        return;
    }

    if (AtomDecAndCompareWithZero(&shrMem->ops_cnt)) {
        ReleaseSharedMemory(shrMem);
    }
    return;
}

TEEC_SharedMemoryHal *GetBnShmByOffset(uint32_t shmOffset, TEEC_ContextHal *context)
{
    TEEC_SharedMemoryHal *tempShardMem = NULL;

    if (context == NULL) {
        tloge("%s: context is NULL!\n", __func__);
        return NULL;
    }

    int lockRet = pthread_mutex_lock(&context->shrMemLock);
    if (lockRet != 0) {
        tloge("get shrmem lock failed.\n");
        return NULL;
    }

    /* found server shardmem */
    tee_list_t *ptr = NULL;
    if (!TeeListEmpty(&context->shrd_mem_list)) {
        TEE_LIST_FOR_EACH(ptr, &context->shrd_mem_list) {
            tempShardMem = TEE_LIST_ENTRY(ptr, TEEC_SharedMemoryHal, head);
            if (tempShardMem->offset == shmOffset) {
                AtomInc(&tempShardMem->ops_cnt);
                (void)pthread_mutex_unlock(&context->shrMemLock);
                return tempShardMem;
            }
        }
    }
    (void)pthread_mutex_unlock(&context->shrMemLock);
    return NULL;
}

static TEEC_Result MallocShrMemHal(TEEC_SharedMemoryHal **shareMemHal)
{
    errno_t nRet;

    TEEC_SharedMemoryHal *shmHal = (TEEC_SharedMemoryHal *)malloc(sizeof(*shmHal));
    if (shmHal == NULL) {
        tloge("%s: shmHal malloc failed\n", __func__);
        return TEEC_FAIL;
    }
    nRet = memset_s(shmHal, sizeof(*shmHal), 0x00, sizeof(*shmHal));
    if (nRet != EOK) {
        tloge("%s: shmHal memset failed : %d\n", __func__, (int)nRet);
        free(shmHal);
        return TEEC_FAIL;
    }
    *shareMemHal = shmHal;
    return TEEC_SUCCESS;
}

static TEEC_Result TranslateRetValue(int32_t ret)
{
    TEEC_Result teeRet;

    switch (ret) {
        case -EFAULT:
            teeRet = TEEC_ERROR_ACCESS_DENIED;
            break;
        case -ENOMEM:
            teeRet = TEEC_ERROR_OUT_OF_MEMORY;
            break;
        case -EINVAL:
            teeRet = TEEC_ERROR_BAD_PARAMETERS;
            break;
        default:
            teeRet = TEEC_ERROR_GENERIC;
            break;
    }
    return teeRet;
}

static uint32_t TranslateParamType(uint32_t flag)
{
    uint32_t paramType;

    switch (flag) {
        case TEEC_MEM_INPUT:
            paramType = TEEC_MEMREF_PARTIAL_INPUT;
            break;
        case TEEC_MEM_OUTPUT:
            paramType = TEEC_MEMREF_PARTIAL_OUTPUT;
            break;
        case TEEC_MEM_INOUT:
            paramType = TEEC_MEMREF_PARTIAL_INOUT;
            break;
        default:
            paramType = TEEC_MEMREF_PARTIAL_INOUT;
            break;
    }

    return paramType;
}

static void TEEC_EncodeTempParam(const TEEC_TempMemoryReference *tempRef, TC_NS_ClientParam *param)
{
    param->memref.buffer        = (unsigned int)(uintptr_t)tempRef->buffer;
    param->memref.buffer_h_addr = ((unsigned long long)(uintptr_t)tempRef->buffer) >> H_OFFSET;
    param->memref.size_addr     = (unsigned int)(uintptr_t)&tempRef->size;
    param->memref.size_h_addr   = ((unsigned long long)(uintptr_t)&tempRef->size) >> H_OFFSET;
}

static void TEEC_EncodePartialParam(uint32_t paramType, const TEEC_RegisteredMemoryReference *memRef,
                                    TC_NS_ClientParam *param)
{
    /* buffer offset len */
    if (paramType == TEEC_MEMREF_WHOLE) {
        param->memref.offset      = 0;
        param->memref.size_addr   = (unsigned int)(uintptr_t)&memRef->parent->size;
        param->memref.size_h_addr = ((unsigned long long)(uintptr_t)&memRef->parent->size) >> H_OFFSET;
    } else {
        param->memref.offset      = memRef->offset;
        param->memref.size_addr   = (unsigned int)(uintptr_t)&memRef->size;
        param->memref.size_h_addr = ((unsigned long long)(uintptr_t)&memRef->size) >> H_OFFSET;
    }

    if (memRef->parent->is_allocated) {
        param->memref.buffer        = (unsigned int)(uintptr_t)memRef->parent->buffer;
        param->memref.buffer_h_addr = ((unsigned long long)(uintptr_t)memRef->parent->buffer) >> H_OFFSET;
    } else {
        param->memref.buffer = (unsigned int)(uintptr_t)((unsigned char *)memRef->parent->buffer + memRef->offset);
        param->memref.buffer_h_addr =
            (unsigned long long)(uintptr_t)((unsigned char *)memRef->parent->buffer + memRef->offset) >> H_OFFSET;
        param->memref.offset = 0;
    }
}

static void TEEC_EncodeValueParam(const TEEC_Value *val, TC_NS_ClientParam *param)
{
    param->value.a_addr   = (unsigned int)(uintptr_t)&val->a;
    param->value.a_h_addr = ((unsigned long long)(uintptr_t)&val->a) >> H_OFFSET;
    param->value.b_addr   = (unsigned int)(uintptr_t)&val->b;
    param->value.b_h_addr = ((unsigned long long)(uintptr_t)&val->b) >> H_OFFSET;
}

static void TEEC_EncodeIonParam(const TEEC_IonReference *ionRef, TC_NS_ClientParam *param)
{
    param->value.a_addr   = (unsigned int)(uintptr_t)&ionRef->ion_share_fd;
    param->value.a_h_addr = ((unsigned long long)(uintptr_t)&ionRef->ion_share_fd) >> H_OFFSET;
    param->value.b_addr   = (unsigned int)(uintptr_t)&ionRef->ion_size;
    param->value.b_h_addr = ((unsigned long long)(uintptr_t)&ionRef->ion_size) >> H_OFFSET;
}

static void TEEC_EncodeParam(TC_NS_ClientContext *cliContext, const TEEC_Operation *operation)
{
    uint32_t paramType[TEEC_PARAM_NUM];
    uint32_t paramCnt;
    uint32_t diff;

    diff = (uint32_t)TEEC_MEMREF_PARTIAL_INPUT - (uint32_t)TEEC_MEMREF_TEMP_INPUT;

    for (paramCnt = 0; paramCnt < TEEC_PARAM_NUM; paramCnt++) {
        paramType[paramCnt] = TEEC_PARAM_TYPE_GET(operation->paramTypes, paramCnt);
        bool checkValue     = (paramType[paramCnt] == TEEC_ION_INPUT || paramType[paramCnt] == TEEC_ION_SGLIST_INPUT);
        if (IS_TEMP_MEM(paramType[paramCnt])) {
            TEEC_EncodeTempParam(&operation->params[paramCnt].tmpref, &cliContext->params[paramCnt]);
        } else if (IS_PARTIAL_MEM(paramType[paramCnt])) {
            const TEEC_RegisteredMemoryReference *memref = &operation->params[paramCnt].memref;

            TEEC_EncodePartialParam(paramType[paramCnt], memref, &cliContext->params[paramCnt]);

            /* translate the paramType to know the driver */
            if (paramType[paramCnt] == TEEC_MEMREF_WHOLE) {
                paramType[paramCnt] = TranslateParamType(memref->parent->flags);
            }

            /* if is not allocated,
             * translate TEEC_MEMREF_PARTIAL_XXX to TEEC_MEMREF_TEMP_XXX */
            if (!memref->parent->is_allocated) {
                paramType[paramCnt] = paramType[paramCnt] - diff;
            }
        } else if (IS_VALUE_MEM(paramType[paramCnt])) {
            TEEC_EncodeValueParam(&operation->params[paramCnt].value, &cliContext->params[paramCnt]);
        } else if (checkValue == true) {
            TEEC_EncodeIonParam(&operation->params[paramCnt].ionref, &cliContext->params[paramCnt]);
        } else {
            /* if type is none, ignore it */
        }
    }

    cliContext->paramTypes = TEEC_PARAM_TYPES(paramType[TEEC_PARAM_ONE], paramType[TEEC_PARAM_TWO],
        paramType[TEEC_PARAM_THREE], paramType[TEEC_PARAM_FOUR]);
    tlogd("cli param type %x\n", cliContext->paramTypes);
    return;
}

static TEEC_Result TEEC_Encode(TC_NS_ClientContext *cliContext, const TEEC_UUID *serviceId, uint32_t sessionId,
    uint32_t cmdId, const TC_NS_ClientLogin *cliLogin, const TEEC_Operation *operation)
{
    errno_t rc;

    rc = memset_s(cliContext, sizeof(TC_NS_ClientContext), 0x00, sizeof(TC_NS_ClientContext));
    if (rc != EOK) {
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    rc = memcpy_s(cliContext->uuid, sizeof(cliContext->uuid), (uint8_t *)serviceId, sizeof(TEEC_UUID));
    if (rc != EOK) {
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    cliContext->session_id   = sessionId;
    cliContext->cmd_id       = cmdId;
    cliContext->returns.code = 0;

    cliContext->login.method = cliLogin->method;
    cliContext->login.mdata  = cliLogin->mdata;

    if ((operation == NULL) || (!operation->paramTypes)) {
        return TEEC_SUCCESS;
    }
    cliContext->started = operation->cancel_flag;

    TEEC_EncodeParam(cliContext, operation);

    return TEEC_SUCCESS;
}

TEEC_Result TEEC_InitializeContextWithType(const char *name, TEEC_ContextHal *context, const int32_t type,
    bool fromHal, const CaAuthInfo *caInfo)
{
    int32_t ret;
    errno_t nRet;

    (void)name; /* supress warning */

    if (context == NULL) {
        tloge("%s: context is NULL\n", __func__);
        return TEEC_ERROR_BAD_PARAMETERS;
    }

    context->fd = open(TC_NS_CLIENT_DEV_NAME, O_RDWR);
    if (context->fd <= 0) {
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }
    context->ops_cnt      = 1;
    context->callFromHal = fromHal;

    ret = ioctl(context->fd, TC_NS_CLIENT_IOCTL_LOGIN, 0);
    if (ret) {
        tloge("Failed set login info for client err=%d!\n", ret);
        close((int)context->fd);
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }

    TeeListInit(&context->session_list);
    TeeListInit(&context->shrd_mem_list);

    nRet = memset_s(context->shm_bitmap, sizeof(context->shm_bitmap), 0x00, sizeof(context->shm_bitmap));
    if (nRet != EOK) {
        tloge("%s: context->shm_bitmap memset failed : %d\n", __func__, (int)nRet);
        close((int)context->fd);
        return TEEC_FAIL;
    }

    int retMutexLock = MutexLockContext();
    if (retMutexLock != 0) {
        tloge("get context lock failed.\n");
        close((int)context->fd);
        return TEEC_FAIL;
    }
    (void)pthread_mutex_init(&context->sessionLock, NULL);
    (void)pthread_mutex_init(&context->shrMemLock, NULL);
    TeeListTailInsert(&g_teecContextList, &context->c_node);
    AtomInc(&context->ops_cnt);
    MutexUnlockContext(retMutexLock);

    return TEEC_SUCCESS;
}

/*
 * Function:      TEEC_InitializeContext
 * Description:   This function initializes a new TEE Context, forming a connection between
 *                this Client Application and the TEE identified by the string identifier name.
 * Parameters:   name: a zero-terminated string that describes the TEE to connect to.
 *                If this parameter is set to NULL, the Implementation MUST select a default TEE.
 *                context: a TEEC_Context structure that be initialized by the Implementation.
 * Return:        TEEC_SUCCESS: the initialization was successful.
 *                     other: initialization was not successful.
 */
TEEC_Result TEEC_InitializeContext(const char *name, TEEC_Context *context)
{
    TEEC_Result ret;
    errno_t nRet;

    (void)name; /* supress warning */

    if (context == NULL) {
        tloge("%s: context is NULL\n", __func__);
        return TEEC_ERROR_BAD_PARAMETERS;
    }

    TEEC_ContextHal *contextHal = (TEEC_ContextHal *)malloc(sizeof(*contextHal));
    if (contextHal == NULL) {
        tloge("%s: Failed to malloc teec contextHal\n", __func__);
        return TEEC_ERROR_GENERIC;
    }
    nRet = memset_s(contextHal, sizeof(*contextHal), 0x00, sizeof(*contextHal));
    if (nRet != EOK) {
        tloge("%s: contextHal memset failed : %d\n", __func__, (int)nRet);
        free(contextHal);
        return TEEC_FAIL;
    }

    ret = TEEC_InitializeContextWithType(name, contextHal, TEECD_CONNECT, false, NULL);
    if (ret == TEEC_SUCCESS) {
        context->fd      = contextHal->fd;
        context->ta_path = NULL;

        TeeListInit(&context->session_list);
        TeeListInit(&context->shrd_mem_list);
        PutBnContext(contextHal); /* pair with ops_cnt++ when add to list */
        return TEEC_SUCCESS;
    }

    free(contextHal);
    return ret;
}

void FreeContextSessionList(TEEC_ContextHal *context)
{
    tee_list_t *ptr           = NULL;
    tee_list_t *n             = NULL;
    TEEC_Session *session          = NULL;

    int lockRet = pthread_mutex_lock(&context->sessionLock);
    if (lockRet != 0) {
        tloge("get session lock failed.\n");
        return;
    }
    if (!TeeListEmpty(&context->session_list)) {
        tlogd("context still has sessions opened, close it\n");

        TEE_LIST_FOR_EACH_SAFE(ptr, n, &context->session_list) {
            session = TEE_LIST_ENTRY(ptr, TEEC_Session, head);
            TeeListDelete(&session->head);
            TEEC_CloseSessionHal(session, context);
            if (context->callFromHal) {
                PutBnSession(session); /* pair with open session */
                session = NULL;
            }
        }
    }
    (void)pthread_mutex_unlock(&context->sessionLock);
}

void FreeContextShrdMemList(TEEC_ContextHal *context)
{
    tee_list_t *ptr           = NULL;
    tee_list_t *n             = NULL;
    TEEC_SharedMemoryHal *shrdMem = NULL;

    int lockRet = pthread_mutex_lock(&context->shrMemLock);
    if (lockRet != 0) {
        tloge("get shrmem lock failed.\n");
        return;
    }

    if (!TeeListEmpty(&context->shrd_mem_list)) {
        tlogd("context contains unreleased Shared Memory blocks, release it\n");

        TEE_LIST_FOR_EACH_SAFE(ptr, n, &context->shrd_mem_list) {
            shrdMem = TEE_LIST_ENTRY(ptr, TEEC_SharedMemoryHal, head);
            TeeListDelete(&shrdMem->head);
            PutBnShrMem(shrdMem); /* pair with Initial value 1 */
        }
    }
    (void)pthread_mutex_unlock(&context->shrMemLock);
}

/*
 * Function:       TEEC_FinalizeContext
 * Description:   This function finalizes an initialized TEE Context.
 * Parameters:   context: an initialized TEEC_Context structure which is to be finalized.
 * Return:         NULL
 */
void TEEC_FinalizeContextHal(TEEC_ContextHal *context)
{
    /* First, check parameters is valid or not */
    if (context == NULL) {
        tloge("%s: context is NULL\n", __func__);
        return;
    }

    FreeContextSessionList(context);
    FreeContextShrdMemList(context);

    close((int)context->fd);
    context->fd = -1;
    (void)pthread_mutex_destroy(&context->sessionLock);
    (void)pthread_mutex_destroy(&context->shrMemLock);
    free(context);
}

void TEEC_FinalizeContext(TEEC_Context *context)
{
    if (context == NULL) {
        tloge("%s: context is NULL\n", __func__);
        return;
    }

    TEEC_ContextHal *contextHal = FindAndRemoveBnContext(context);
    PutBnContext(contextHal); /* pair with initialize context */
    context->fd = -1;
}

#ifdef SECURITY_AUTH_ENHANCE
static TEEC_Result AllocAndInitToken(TC_NS_ClientContext *context, TC_NS_Token **token)
{
    TC_NS_Token *newToken = (TC_NS_Token *)malloc(sizeof(TC_NS_Token));
    if (newToken == NULL) {
        tloge("malloc for cliContext.teecToken failed.\n");
        return TEEC_ERROR_OUT_OF_MEMORY;
    }
    *token = newToken;
    errno_t rc = memset_s(*token, sizeof(TC_NS_Token), 0x00, sizeof(TC_NS_Token));
    if (rc != EOK) {
        tloge("memset_s for token failed.\n");
    }
    (*token)->opsCnt = 1;
    context->token.teec_token = (*token)->teecToken;
    context->token_len        = TOKEN_SAVE_LEN;
    return TEEC_SUCCESS;
}
#endif

static TEEC_Result TEEC_DoOpenSession(int fd, TC_NS_ClientContext *cliContext, const TEEC_UUID *destination,
                                      TEEC_ContextHal *context, TEEC_Session *session)
{
    int32_t ret;
    TEEC_Result teecRet;
#ifdef SECURITY_AUTH_ENHANCE
    TC_NS_Token *token = NULL;

    ret = AllocAndInitToken(cliContext, &token);
    if (ret < 0) {
        return TEEC_ERROR_OUT_OF_MEMORY;
    }
#endif

    int i = CA_AUTH_RETRY_TIMES;
    do {
        cliContext->returns.code   = 0;
        cliContext->returns.origin = TEEC_ORIGIN_API;
        ret                        = ioctl(fd, (int)TC_NS_CLIENT_IOCTL_SES_OPEN_REQ, cliContext);
    } while (((TEEC_Result)cliContext->returns.code == TEE_ERROR_CA_AUTH_FAIL) && i--);

    if (ret < 0) {
        tloge("open session failed, ioctl errno = %d\n", ret);
        teecRet                    = TranslateRetValue(ret);
        cliContext->returns.origin = TEEC_ORIGIN_COMMS;
        goto ERROR;
    } else if (ret > 0) {
        tloge("open session failed(%d), code=0x%x, origin=%u\n", ret, cliContext->returns.code,
            cliContext->returns.origin);
        if (cliContext->returns.code) {
            teecRet = (TEEC_Result)cliContext->returns.code;
        } else {
            teecRet = (TEEC_Result)TEEC_ERROR_GENERIC;
        }
        goto ERROR;
    }

#ifdef SECURITY_AUTH_ENHANCE
    int32_t tokenRet = SaveToken(token, cliContext, fd);
    if (tokenRet != EOK) {
        teecRet                    = TEEC_FAIL;
        cliContext->returns.origin = TEEC_ORIGIN_API;
        goto ERROR;
    }
#endif
    return AddSessionList(cliContext->session_id, destination, context, session);

ERROR:
#ifdef SECURITY_AUTH_ENHANCE
    PutToken(token);
    cliContext->token.teec_token = NULL;
    cliContext->token_len        = 0;
#endif
    return teecRet;
}

/*
 * Function:       TEEC_OpenSession
 * Description:   This function opens a new Session
 * Parameters:   context: a pointer to an initialized TEE Context.
 *                     session: a pointer to a Session structure to open.
 *                     destination: a pointer to a UUID structure.
 *                     connectionMethod: the method of connection to use.
 *                     connectionData: any necessary data required to support the connection method chosen.
 *                     operation: a pointer to an Operation containing a set of Parameters.
 *                     returnOrigin: a pointer to a variable which will contain the return origin.
 * Return:         TEEC_SUCCESS: success
 *                     other: failure
 */
TEEC_Result TEEC_OpenSessionHal(int callingPid, const TaFileInfo *taFile, TEEC_ContextHal *context,
                                TEEC_Session *session, const TEEC_UUID *destination, uint32_t connectionMethod,
                                const void *connectionData, TEEC_Operation *operation, uint32_t *returnOrigin)
{
    TEEC_Result teecRet = (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    TC_NS_ClientContext cliContext;
    TC_NS_ClientLogin cliLogin = { 0, 0 };

    /* prefirst, we set origin be zero */
    cliContext.returns.origin = TEEC_ORIGIN_API;
    cliContext.file_buffer    = NULL;

    bool condition = (context == NULL) || (taFile == NULL) || (session == NULL) || (destination == NULL);
    if (condition) {
        tloge("context or session or destination is NULL\n");
        goto ERROR;
    }
    /* now only support TEEC_LOGIN_IDENTIFY */
    condition = (connectionMethod != TEEC_LOGIN_IDENTIFY) || (connectionData != NULL);
    if (condition) {
        tloge("Login method is not supported or connection data is not null\n");
        goto ERROR;
    }

    cliLogin.method = connectionMethod;

    if (operation != NULL) {
        /* Params 2 and 3 are used for ident by teecd hence ->TEEC_NONE */
        operation->paramTypes = TEEC_PARAM_TYPES(TEEC_PARAM_TYPE_GET(operation->paramTypes, 0),
                                                 TEEC_PARAM_TYPE_GET(operation->paramTypes, 1), TEEC_NONE, TEEC_NONE);
    }
    teecRet = TEEC_CheckOperation(operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("operation is invalid\n");
        goto ERROR;
    }

    /* Paramters right, start execution */
    /*
     * note:before open session success, we should send session=0 as initial state.
     */
    teecRet = TEEC_Encode(&cliContext, destination, 0, GLOBAL_CMD_ID_OPEN_SESSION, &cliLogin, operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("OpenSession: teec encode failed(0x%x)!\n", teecRet);
        goto ERROR;
    }

    cliContext.callingPid = (unsigned int)callingPid;

    int32_t ret = TEEC_GetApp(taFile, destination, &cliContext);
    if (ret < 0) {
        tloge("get app error\n");
        teecRet = (TEEC_Result)TEEC_ERROR_TRUSTED_APP_LOAD_ERROR;
        goto ERROR;
    }

    teecRet = TEEC_DoOpenSession(context->fd, &cliContext, destination, context, session);

ERROR:
    /* ONLY when ioctl returnCode!=0 and returnOrigin not NULL,
     * set *returnOrigin
     */
    if (returnOrigin != NULL) {
        *returnOrigin = cliContext.returns.origin;
    }

    if (cliContext.file_buffer != NULL) {
        free(cliContext.file_buffer);
    }
    return teecRet;
}

TEEC_Result TEEC_OpenSession(TEEC_Context *context, TEEC_Session *session, const TEEC_UUID *destination,
    uint32_t connectionMethod, const void *connectionData, TEEC_Operation *operation, uint32_t *returnOrigin)
{
    TEEC_Result ret    = TEEC_ERROR_BAD_PARAMETERS;
    uint32_t retOrigin = TEEC_ORIGIN_API;

    if ((context == NULL) || (session == NULL) || (destination == NULL)) {
        tloge("param is null!\n");
        goto END;
    }

    /*
     * ca may call closesession even if opensession failed,
     * we set session->context here to avoid receive a illegal ptr
     */
    session->context = context;

    TaFileInfo taFile = {
        .taPath = NULL,
        .taFp = NULL
    };
    taFile.taPath     = context->ta_path;

    TEEC_ContextHal *contextHal = GetBnContext(context);
    if (contextHal == NULL) {
        tloge("no context found in service!\n");
        goto END;
    }

    ret = TEEC_OpenSessionHal(0, &taFile, contextHal, session, destination, connectionMethod, connectionData,
        operation, &retOrigin);
    PutBnContext(contextHal);

END:
    if (returnOrigin != NULL) {
        *returnOrigin = retOrigin;
    }
    return ret;
}

/*
 * Function:       TEEC_CloseSession
 * Description:   This function closes an opened Session.
 * Parameters:   session: the session to close.
 * Return:         NULL
 */
void TEEC_CloseSessionHal(TEEC_Session *session, const TEEC_ContextHal *context)
{
    int32_t ret;
    TC_NS_ClientContext cliContext;
    TC_NS_ClientLogin cliLogin = { 0, 0 };
    TEEC_Result teecRet;

    /* First, check parameters is valid or not */
    if ((session == NULL) || (context == NULL)) {
        tloge("%s: session or context is NULL\n", __func__);
        return;
    }

    teecRet = TEEC_Encode(&cliContext, &session->service_id, session->session_id, GLOBAL_CMD_ID_CLOSE_SESSION,
        &cliLogin, NULL);
    if (teecRet != TEEC_SUCCESS) {
        tloge("CloseSession: teec encode failed(0x%x)!\n", teecRet);
        return;
    }

#ifdef SECURITY_AUTH_ENHANCE
    /* close session donot check token, so del it here */
    DelToken(&session->service_id, session->session_id, (int)context->fd);
#endif
    ret = ioctl((int)context->fd, (int)TC_NS_CLIENT_IOCTL_SES_CLOSE_REQ, &cliContext);
    if (ret != 0) {
        tloge("close session failed, ret=0x%x\n", ret);
    }
    session->session_id = 0;
    session->context    = NULL;
    errno_t rc =
        memset_s((uint8_t *)&session->service_id, sizeof(session->service_id), 0x00, sizeof(session->service_id));
    if (rc != EOK) {
        tloge("memset service id fail\n");
    }
    return;
}

void TEEC_CloseSession(TEEC_Session *session)
{
    if ((session == NULL) || (session->context == NULL)) {
        tloge("%s: session or session->context is NULL\n", __func__);
        return;
    }

    TEEC_ContextHal *contextHal = GetBnContext(session->context);
    if (contextHal == NULL) {
        tloge("context is NULL\n");
        return;
    }
    TEEC_Session *sessionInList = FindAndRemoveSession(session, contextHal);
    if (sessionInList == NULL) {
        tloge("session is not in the context list\n");
        PutBnContext(contextHal);
        return;
    }

    TEEC_CloseSessionHal(session, contextHal);
    PutBnContext(contextHal);
}

static TEEC_Result SendIoctlCmdReq(const TEEC_ContextHal *context, TC_NS_ClientContext *cliContext)
{
    TEEC_Result teecRet;
    int32_t ret = ioctl((int)context->fd, (int)TC_NS_CLIENT_IOCTL_SEND_CMD_REQ, cliContext);
    if (ret == 0) {
        tlogd("invoke cmd success\n");
        teecRet = TEEC_SUCCESS;
    } else if (ret < 0) {
        tloge("invoke cmd failed, ioctl errno = %d\n", errno);
        teecRet = TranslateRetValue(-errno);
        cliContext->returns.origin = TEEC_ORIGIN_COMMS;
    } else {
        tloge("invoke cmd failed(%d), code=0x%x, origin=%u\n",
            ret, cliContext->returns.code, cliContext->returns.origin);
        if (cliContext->returns.code) {
            teecRet = (TEEC_Result)cliContext->returns.code;
        } else {
            teecRet = (TEEC_Result)TEEC_ERROR_GENERIC;
        }
    }
    return teecRet;
}

/*
 * Function:       TEEC_InvokeCommand
 * Description:   This function invokes a Command within the specified Session.
 * Parameters:   session: the open Session in which the command will be invoked.
 *                     commandID: the identifier of the Command.
 *                     operation: a pointer to an Operation containing a set of Parameters.
 *                     returnOrigin: a pointer to a variable which will contain the return origin.
 * Return:         TEEC_SUCCESS: success
 *                     other: failure
 */
TEEC_Result TEEC_InvokeCommandHal(const TEEC_ContextHal *context, const TEEC_Session *session, uint32_t commandID,
    const TEEC_Operation *operation, uint32_t *returnOrigin)
{
    TEEC_Result teecRet = (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    TC_NS_ClientContext cliContext;
    TC_NS_ClientLogin cliLogin = { 0, 0 };
    /* prefirst, we set origin be zero */
    cliContext.returns.origin = TEEC_ORIGIN_API;
    /* First, check parameters is valid or not */
    if ((session == NULL) || (context == NULL)) {
        goto ERROR;
    }
    teecRet = TEEC_CheckOperation(operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("operation is invalid\n");
        goto ERROR;
    }

    /* Paramters all right, start execution */
    teecRet = TEEC_Encode(&cliContext, &session->service_id, session->session_id, commandID, &cliLogin, operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("InvokeCommand: teec encode failed(0x%x)!\n", teecRet);
        goto ERROR;
    }

#ifdef SECURITY_AUTH_ENHANCE
    TC_NS_Token *token = GetToken(&session->service_id, session->session_id, context->fd);
    if (token == NULL) {
        tloge("invoke command: find token failed!\n");
        teecRet = TEEC_ERROR_ACCESS_DENIED;
        goto ERROR;
    }
    cliContext.token.teec_token = token->teecToken;
    cliContext.token_len        = TOKEN_SAVE_LEN;
#endif

    teecRet = SendIoctlCmdReq(context, &cliContext);
#ifdef SECURITY_AUTH_ENHANCE
    PutToken(token);
#endif

ERROR:
    /* ONLY when ioctl returnCode!=0 and returnOrigin not NULL,
     * set *returnOrigin
     */
    if (returnOrigin != NULL) {
        *returnOrigin = cliContext.returns.origin;
    }
    return teecRet;
}

TEEC_Result TEEC_InvokeCommand(TEEC_Session *session, uint32_t commandID, TEEC_Operation *operation,
                               uint32_t *returnOrigin)
{
    TEEC_Result ret = TEEC_ERROR_BAD_PARAMETERS;
    uint32_t retOrigin = TEEC_ORIGIN_API;

    if ((session == NULL) || (session->context == NULL)) {
        goto END;
    }
    TEEC_Context *contextTemp     = session->context;
    TEEC_ContextHal *contextHal = GetBnContext(session->context);

    ret = TEEC_InvokeCommandHal(contextHal, session, commandID, operation, &retOrigin);
    if (ret == TEEC_SUCCESS) {
        session->context = contextTemp;
    }
    PutBnContext(contextHal);

END:
    if (returnOrigin != NULL) {
        *returnOrigin = retOrigin;
    }
    return ret;
}

/*
 * Function:       TEEC_RegisterSharedMemory
 * Description:   This function registers a block of existing Client Application memory
 *                     as a block of Shared Memory within the scope of the specified TEE Context.
 * Parameters:   context: a pointer to an initialized TEE Context.
 *                     sharedMem: a pointer to a Shared Memory structure to register.
 * Return:         TEEC_SUCCESS: success
 *                     other: failure
 */
TEEC_Result TEEC_RegisterSharedMemoryHal(TEEC_ContextHal *context, TEEC_SharedMemoryHal *sharedMem)
{
    /* First, check parameters is valid or not */
    if ((context == NULL) || (sharedMem == NULL)) {
        tloge("%s: context or sharedMem is NULL\n", __func__);
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    bool condition =
        (sharedMem->buffer == NULL) || ((sharedMem->flags != TEEC_MEM_INPUT) && (sharedMem->flags != TEEC_MEM_OUTPUT) &&
                                        (sharedMem->flags != TEEC_MEM_INOUT));
    if (condition) {
        tloge("%s: sharedMem->flags wrong\n", __func__);
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    /* Paramters all right, start execution */
    sharedMem->ops_cnt      = 1;
    sharedMem->is_allocated = false;
    sharedMem->offset       = (uint32_t)(-1);
    sharedMem->context      = context;
    TeeListInit(&sharedMem->head);
    int lockRet = pthread_mutex_lock(&context->shrMemLock);
    if (lockRet != 0) {
        tloge("get share mem lock failed.\n");
        return TEEC_ERROR_GENERIC;
    }
    TeeListTailInsert(&context->shrd_mem_list, &sharedMem->head);
    AtomInc(&sharedMem->ops_cnt);
    (void)pthread_mutex_unlock(&context->shrMemLock);

    return TEEC_SUCCESS;
}

TEEC_Result TEEC_RegisterSharedMemory(TEEC_Context *context, TEEC_SharedMemory *sharedMem)
{
    TEEC_Result ret;
    TEEC_ContextHal *contextHal  = NULL;
    TEEC_SharedMemoryHal *shmHal = NULL;

    bool condition = (context == NULL) || (sharedMem == NULL);
    if (condition) {
        tloge("%s: context or sharedMem is NULL\n", __func__);
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    /*
     * ca may call ReleaseShareMemory even if RegisterShareMem failed,
     * we set sharedMem->context here to avoid receive a illegal ptr
     */
    sharedMem->context = context;

    ret = MallocShrMemHal(&shmHal);
    if (ret != TEEC_SUCCESS) {
        return ret;
    }
    shmHal->buffer = sharedMem->buffer;
    shmHal->size   = sharedMem->size;
    shmHal->flags  = sharedMem->flags;

    contextHal = GetBnContext(context);
    ret         = TEEC_RegisterSharedMemoryHal(contextHal, shmHal);
    if (ret == TEEC_SUCCESS) {
        sharedMem->ops_cnt      = shmHal->ops_cnt;
        sharedMem->is_allocated = shmHal->is_allocated;
        TeeListInit(&sharedMem->head);
        PutBnShrMem(shmHal); /* pair with ops_cnt++ when add to list */
        PutBnContext(contextHal);
        return ret;
    }
    tloge("%s: failed:0x%x\n", __func__, ret);
    PutBnContext(contextHal);
    free(shmHal);
    return ret;
}

static int HandleMmapFail(TEEC_ContextHal *context, TEEC_SharedMemoryHal *sharedMem)
{
    tloge("mmap failed\n");
    sharedMem->buffer = NULL;
    sharedMem->offset = 0;
    int lockRet = pthread_mutex_lock(&context->shrMemBitMapLock);
    if (lockRet != 0) {
        tloge("get share mem lock failed.\n");
        return TEEC_ERROR_GENERIC;
    }
    ClearBit(sharedMem->offset, sizeof(context->shm_bitmap), context->shm_bitmap);
    (void)pthread_mutex_unlock(&context->shrMemBitMapLock);
    return (TEEC_Result)TEEC_ERROR_OUT_OF_MEMORY;
}

/*
 * Function:       TEEC_AllocateSharedMemory
 * Description:   This function allocates a new block of memory as a block of
 *                     Shared Memory within the scope of the specified TEE Context.
 * Parameters:   context: a pointer to an initialized TEE Context.
 *                     sharedMem: a pointer to a Shared Memory structure to allocate.
 * Return:         TEEC_SUCCESS: success
 *                     other: failure
 */
TEEC_Result TEEC_AllocateSharedMemoryHal(TEEC_ContextHal *context, TEEC_SharedMemoryHal *sharedMem)
{
    /* First, check parameters is valid or not */
    if ((context == NULL) || (sharedMem == NULL)) {
        tloge("%s: context or sharedMem is NULL\n", __func__);
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    bool condition = (sharedMem->flags != TEEC_MEM_INPUT) && (sharedMem->flags != TEEC_MEM_OUTPUT) &&
        (sharedMem->flags != TEEC_MEM_INOUT);
    if (condition) {
        tloge("%s: sharedMem->flags wrong\n", __func__);
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    /* Paramters all right, start execution */
    sharedMem->buffer = NULL;

    int lockRet = pthread_mutex_lock(&context->shrMemBitMapLock);
    if (lockRet != 0) {
        tloge("get share mem lock failed.\n");
        return TEEC_ERROR_GENERIC;
    }
    int32_t validBit = (int32_t)GetAndSetBit(context->shm_bitmap, sizeof(context->shm_bitmap));
    (void)pthread_mutex_unlock(&context->shrMemBitMapLock);
    if (validBit < 0) {
        tloge("There is no valid bit for shm\n");
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }
    sharedMem->offset = (uint32_t)validBit;
    if (sharedMem->size != 0) {
        sharedMem->buffer = mmap(0, (unsigned long)sharedMem->size, (PROT_READ | PROT_WRITE), MAP_SHARED,
                                 (int)context->fd, (long)(sharedMem->offset * PAGE_SIZE));
    } else {
        sharedMem->buffer = ZERO_SIZE_PTR;
    }

    if (sharedMem->buffer == MAP_FAILED) {
        return HandleMmapFail(context, sharedMem);
    }
    sharedMem->ops_cnt      = 1;
    sharedMem->is_allocated = true;
    sharedMem->context      = context;
    TeeListInit(&sharedMem->head);
    lockRet = pthread_mutex_lock(&context->shrMemLock);
    if (lockRet != 0) {
        tloge("get share mem lock failed.\n");
        return TEEC_ERROR_GENERIC;
    }
    TeeListTailInsert(&context->shrd_mem_list, &sharedMem->head);
    AtomInc(&sharedMem->ops_cnt);
    (void)pthread_mutex_unlock(&context->shrMemLock);
    return TEEC_SUCCESS;
}

TEEC_Result TEEC_AllocateSharedMemory(TEEC_Context *context, TEEC_SharedMemory *sharedMem)
{
    TEEC_Result ret;
    TEEC_ContextHal *contextHal  = NULL;
    TEEC_SharedMemoryHal *shmHal = NULL;

    bool condition = (context == NULL) || (sharedMem == NULL);
    if (condition) {
        tloge("%s: context or sharedMem is NULL\n", __func__);
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    /*
     * ca may call ReleaseShareMemory even if AllocateSharedMemory failed,
     * we set sharedMem->context here to avoid receive a illegal ptr
     */
    sharedMem->context = context;

    ret = MallocShrMemHal(&shmHal);
    if (ret != TEEC_SUCCESS) {
        return ret;
    }
    shmHal->size  = sharedMem->size;
    shmHal->flags = sharedMem->flags;

    contextHal = GetBnContext(context);
    ret         = TEEC_AllocateSharedMemoryHal(contextHal, shmHal);
    if (ret == TEEC_SUCCESS) {
        sharedMem->buffer       = shmHal->buffer;
        sharedMem->ops_cnt      = shmHal->ops_cnt;
        sharedMem->is_allocated = shmHal->is_allocated;
        TeeListInit(&sharedMem->head);
        PutBnShrMem(shmHal); /* pair with ops_cnt++ when add to list */
        PutBnContext(contextHal);
        return TEEC_SUCCESS;
    }

    tloge("%s: failed:0x%x\n", __func__, ret);
    PutBnContext(contextHal);
    free(shmHal);
    return ret;
}

static bool TEEC_FindAndRemoveShrMemHal(TEEC_SharedMemoryHal **sharedMem, TEEC_ContextHal *contextHal)
{
    bool found                           = false;
    tee_list_t *ptr                 = NULL;
    TEEC_SharedMemoryHal *tempSharedMem = NULL;
    TEEC_SharedMemoryHal *shm           = *sharedMem;

    int lockRet = pthread_mutex_lock(&contextHal->shrMemLock);
    if (lockRet != 0) {
        tloge("get share mem lock failed.\n");
        return false;
    }

    TEE_LIST_FOR_EACH(ptr, &contextHal->shrd_mem_list) {
        tempSharedMem = TEE_LIST_ENTRY(ptr, TEEC_SharedMemoryHal, head);
        if (contextHal->callFromHal && shm->is_allocated) {
            if (tempSharedMem->offset == shm->offset && tempSharedMem->context == shm->context) {
                found = true;
                TeeListDelete(&tempSharedMem->head);
                *sharedMem = tempSharedMem;
                break;
            }
        } else {
            if (tempSharedMem->buffer == shm->buffer && tempSharedMem->context == shm->context) {
                found = true;
                TeeListDelete(&tempSharedMem->head);
                *sharedMem = tempSharedMem;
                break;
            }
        }
    }

    (void)pthread_mutex_unlock(&contextHal->shrMemLock);
    return found;
}

/*
 * Function:       TEEC_ReleaseSharedMemory
 * Description:   This function deregisters or deallocates a previously initialized
 *                      block of Shared Memory..
 * Parameters:   sharedMem: a pointer to a valid Shared Memory structure.
 * Return:         NULL
 */
void TEEC_ReleaseSharedMemoryHal(TEEC_SharedMemoryHal *sharedMem)
{
    TEEC_SharedMemoryHal *shm = sharedMem;

    /* First, check parameters is valid or not */
    if ((shm == NULL) || (shm->context == NULL)) {
        tloge("Shared Memory is NULL\n");
        return;
    }

    bool found = TEEC_FindAndRemoveShrMemHal(&shm, shm->context);
    if (!found) {
        tloge("Shared Memory is not in the list\n");
        return;
    }

    PutBnShrMem(shm); /* pair with Initial value 1 */
}

void TEEC_ReleaseSharedMemory(TEEC_SharedMemory *sharedMem)
{
    if ((sharedMem == NULL) || (sharedMem->context == NULL)) {
        tloge("%s: sharedMem or sharedMem->context is NULL\n", __func__);
        return;
    }

    TEEC_SharedMemoryHal shmHal = { 0 };
    shmHal.buffer                = sharedMem->buffer;
    shmHal.size                  = sharedMem->size;
    shmHal.flags                 = sharedMem->flags;
    shmHal.ops_cnt               = sharedMem->ops_cnt;
    shmHal.is_allocated          = sharedMem->is_allocated;

    TEEC_ContextHal *contextHal = GetBnContext(sharedMem->context);
    shmHal.context              = contextHal;

    TEEC_ReleaseSharedMemoryHal(&shmHal);
    PutBnContext(contextHal);
    sharedMem->buffer  = NULL;
    sharedMem->size    = 0;
    sharedMem->flags   = 0;
    sharedMem->ops_cnt = 0;
    sharedMem->context = NULL;
}

static TEEC_Result TEEC_CheckTmpRef(TEEC_TempMemoryReference tmpref)
{
    if ((tmpref.buffer == NULL) || (tmpref.size == 0)) {
        tloge("tmpref buffer is null, or size is zero\n");
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }
    return (TEEC_Result)TEEC_SUCCESS;
}

static TEEC_Result TEEC_CheckMemRef(TEEC_RegisteredMemoryReference memref, uint32_t paramType)
{
    bool condition = (memref.parent == NULL) || (memref.parent->buffer == NULL);
    if (condition) {
        tloge("parent of memref is null, or the buffer is zero\n");
        return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
    }

    if (paramType == TEEC_MEMREF_PARTIAL_INPUT) {
        if (!(memref.parent->flags & TEEC_MEM_INPUT)) {
            goto PARAM_ERROR;
        }
    } else if (paramType == TEEC_MEMREF_PARTIAL_OUTPUT) {
        if (!(memref.parent->flags & TEEC_MEM_OUTPUT)) {
            goto PARAM_ERROR;
        }
    } else if (paramType == TEEC_MEMREF_PARTIAL_INOUT) {
        if (!(memref.parent->flags & TEEC_MEM_INPUT)) {
            goto PARAM_ERROR;
        }
        if (!(memref.parent->flags & TEEC_MEM_OUTPUT)) {
            goto PARAM_ERROR;
        }
    } else {
        /*  if type is TEEC_MEMREF_WHOLE, ignore it */
    }

    condition = (paramType == TEEC_MEMREF_PARTIAL_INPUT) || (paramType == TEEC_MEMREF_PARTIAL_OUTPUT) ||
                (paramType == TEEC_MEMREF_PARTIAL_INOUT);
    if (condition) {
        if ((memref.offset + memref.size) > memref.parent->size) {
            tloge("offset + size exceed the parent size\n");
            return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
        }
    }

    return (TEEC_Result)TEEC_SUCCESS;
PARAM_ERROR:
    tloge("type of memref not belong to the parent flags\n");
    return (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
}

/*
 * Function:       TEEC_CheckOperation
 * Description:   This function checks a operation is valid or not.
 * Parameters:   operation: a pointer to an Operation to be checked.
 * Return:         TEEC_SUCCESS: success
 *                     other: failure
 */
TEEC_Result TEEC_CheckOperation(const TEEC_Operation *operation)
{
    uint32_t paramType[TEEC_PARAM_NUM];
    uint32_t paramCnt;
    TEEC_Result ret = TEEC_SUCCESS;
    /* GP Support operation is NULL
     * operation: a pointer to a Client Application initialized TEEC_Operation structure,
     * or NULL if there is no payload to send or if the Command does not need to support
     * cancellation.
     */
    if (operation == NULL) {
        return ret;
    }
    if (!operation->started) {
        tloge("sorry, cancellation not support\n");
        return (TEEC_Result)TEEC_ERROR_NOT_IMPLEMENTED;
    }

    for (paramCnt = 0; paramCnt < TEEC_PARAM_NUM; paramCnt++) {
        paramType[paramCnt] = TEEC_PARAM_TYPE_GET(operation->paramTypes, paramCnt);
        bool checkValue     = (paramType[paramCnt] == TEEC_ION_INPUT || paramType[paramCnt] == TEEC_ION_SGLIST_INPUT);
        if (IS_TEMP_MEM(paramType[paramCnt])) {
            ret = TEEC_CheckTmpRef(operation->params[paramCnt].tmpref);
        } else if (IS_PARTIAL_MEM(paramType[paramCnt])) {
            ret = TEEC_CheckMemRef(operation->params[paramCnt].memref, paramType[paramCnt]);
        } else if (IS_VALUE_MEM(paramType[paramCnt])) {
            /*  if type is value, ignore it */
        } else if (checkValue == true) {
            if (operation->params[paramCnt].ionref.ion_share_fd < 0 ||
                operation->params[paramCnt].ionref.ion_size == 0) {
                tloge("check failed: ion_share_fd and ion_size\n");
                ret = (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
                break;
            }
        } else if (paramType[paramCnt] == TEEC_NONE) {
            /*  if type is none, ignore it */
        } else {
            tloge("paramType is not support\n");
            ret = (TEEC_Result)TEEC_ERROR_BAD_PARAMETERS;
            break;
        }

        if (ret != TEEC_SUCCESS) {
            tloge("paramCnt is %u\n", paramCnt);
            break;
        }
    }
    return ret;
}

/*
 * Function:       TEEC_RequestCancellation
 * Description:   This function requests the cancellation of a pending open Session operation or
            a Command invocation operation.
 * Parameters:   operation:a pointer to a Client Application instantiated Operation structure
 * Return:         void
 */
void TEEC_RequestCancellation(const TEEC_Operation *operation)
{
    int32_t ret;
    TEEC_Result teecRet;
    TC_NS_ClientContext cliContext;
    TC_NS_ClientLogin cliLogin = { 0, 0 };

    /* First, check parameters is valid or not */
    if (operation == NULL) {
        return;
    }

    TEEC_Session *session = operation->session;
    if ((session == NULL) || (session->context == NULL)) {
        tloge("session is invalid\n");
        return;
    }
    teecRet = TEEC_CheckOperation(operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("operation is invalid\n");
        return;
    }

    /* Paramters all right, start execution */
    teecRet = TEEC_Encode(&cliContext, &session->service_id, session->session_id, TC_NS_CLIENT_IOCTL_CANCEL_CMD_REQ,
                          &cliLogin, operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("RequestCancellation: teec encode failed(0x%x)!\n", teecRet);
        return;
    }

    ret = ioctl((int)session->context->fd, (int)TC_NS_CLIENT_IOCTL_CANCEL_CMD_REQ, &cliContext);
    if (ret == 0) {
        tlogd("invoke cmd success\n");
    } else if (ret < 0) {
        tloge("invoke cmd failed, ioctl errno = %d\n", ret);
    } else {
        tloge("invoke cmd failed, code=0x%x, origin=%u\n", cliContext.returns.code, cliContext.returns.origin);
    }

    return;
}

TEEC_Result TEEC_EXT_RegisterAgent(uint32_t agentId, int *devFd, void **buffer)
{
    int ret;
    struct AgentIoctlArgs args = { 0 };

    if ((devFd == NULL) || (buffer == NULL)) {
        tloge("Failed to open tee client dev!\n");
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }

    int fd = open(TC_NS_CLIENT_DEV_NAME, O_RDWR);
    if (fd < 0) {
        tloge("Failed to open tee client dev!\n");
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }

    args.id         = agentId;
    args.bufferSize = AGENT_BUFF_SIZE;
    ret             = ioctl(fd, (int)TC_NS_CLIENT_IOCTL_REGISTER_AGENT, &args);
    if (ret) {
        (void)close(fd);
        tloge("ioctl failed, failed to register agent!\n");
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }

    *devFd  = fd;
    *buffer = args.buffer;
    return TEEC_SUCCESS;
}

TEEC_Result TEEC_EXT_WaitEvent(uint32_t agentId, int devFd)
{
    int ret;

    ret = ioctl(devFd, (int)TC_NS_CLIENT_IOCTL_WAIT_EVENT, agentId);
    if (ret == -1) {
        tloge("Agent 0x%x wait failed, errno=%d\n", agentId, errno);
        return TEEC_ERROR_GENERIC;
    }

    return TEEC_SUCCESS;
}

TEEC_Result TEEC_EXT_SendEventResponse(uint32_t agentId, int devFd)
{
    int ret;
    ret = ioctl(devFd, (int)TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, agentId);
    if (ret) {
        tloge("Agent %u failed to send response, ret is %d!\n", agentId, ret);
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }

    return TEEC_SUCCESS;
}

TEEC_Result TEEC_EXT_UnregisterAgent(uint32_t agentId, int devFd, void **buffer)
{
    int ret;
    TEEC_Result result = TEEC_SUCCESS;

    if (buffer == NULL || *buffer == NULL) {
        tloge("buffer is invalid!\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    if (devFd < 0) {
        tloge("fd is invalid!\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    ret = ioctl(devFd, (int)TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT, agentId);
    if (ret != 0) {
        tloge("Failed to unregister agent %u, ret is %d\n", agentId, ret);
        result = TEEC_ERROR_GENERIC;
    }

    (void)close(devFd);
    *buffer = NULL;
    return result;
}

TEEC_Result TEEC_EXT_TST(const TEEC_Session *session, const TEEC_Operation *operation)
{
    TC_NS_ClientContext cliContext;
    TC_NS_ClientLogin cliLogin = { 0, 0 };
    int32_t ret;
    TEEC_Result result;

    if ((session == NULL) || (session->context == NULL)) {
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }

    result = TEEC_Encode(&cliContext, &session->service_id, 0, GLOBAL_CMD_ID_OPEN_SESSION, &cliLogin, operation);
    if (result != TEEC_SUCCESS) {
        tloge("TEEC_EXT_TST: teec encode failed(0x%x)!\n", result);
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }

    ret = ioctl((int)session->context->fd, (int)TC_NS_CLIENT_IOCTL_TST_CMD_REQ, &cliContext);
    if (ret) {
        return (TEEC_Result)TEEC_ERROR_GENERIC;
    }
    return TEEC_SUCCESS;
}

uint32_t TEEC_GetTEEVersionHal(void)
{
    unsigned int version = 0;
    int ret;

    int fd = open(TC_NS_CLIENT_DEV_NAME, O_RDWR);
    if (fd < 0) {
        return 0;
    }

    ret = ioctl(fd, TC_NS_CLIENT_IOCTL_GET_TEE_VERSION, &version);
    if (ret < 0) {
        tloge("get tee version failed\n");
        close(fd);
        return 0;
    }

    close(fd);
    return version;
}

/*
 * Function:       TEEC_EXT_Send_Secfile
 * Description:   This function sends a secfile to TEE and saves it for use.
 * Parameters:   session: the session to close.
 * Return:         NULL
 */
TEEC_Result TEEC_SendSecfileHal(const char *path, int tzFd, FILE *fp)
{
    int32_t ret;
    TEEC_Result teecRet = (TEEC_Result)TEEC_SUCCESS;

    if (path == NULL) {
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    ret = TEEC_LoadSecfile(path, tzFd, fp);
    if (ret < 0) {
        tloge("Send secfile error\n");
        teecRet = (TEEC_Result)TEEC_ERROR_TRUSTED_APP_LOAD_ERROR;
    }
    return teecRet;
}

TEEC_Result TEEC_SendSecfile(const char *path, TEEC_Session *session)
{
    TEEC_Result ret;
    TEEC_ContextHal *contextHal = NULL;

    if (path == NULL || session == NULL || session->context == NULL) {
        tloge("params error!\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    contextHal = GetBnContext(session->context);
    if (contextHal == NULL) {
        tloge("find context hal failed!\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    ret = TEEC_SendSecfileHal(path, contextHal->fd, NULL);
    PutBnContext(contextHal);
    return ret;
}
