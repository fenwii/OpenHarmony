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

#include "gp_ops.h"
#include <securec.h>
#include "agent.h"
#include "mailbox_mempool.h"
#include "mem.h"
#include "smc.h"
#include "tc_client_sub_driver.h"
#include "tc_ns_log.h"
#include "teek_client_constants.h"
#include "tzdriver_compat.h"

#ifdef SECURITY_AUTH_ENHANCE
#include "security_auth_enhance.h"
#define AES_LOGIN_MAXLEN   (((MAX_PUBKEY_LEN) > (MAX_PACKAGE_NAME_LEN)) ? \
    (MAX_PUBKEY_LEN) : (MAX_PACKAGE_NAME_LEN))
static int DoEncryption(uint8_t *buffer, uint32_t bufferSize,
    uint32_t payloadSize, const uint8_t *key);
static int EncryptLoginInfo(uint32_t loginInfoSize, uint8_t *buffer,
    const uint8_t *key);
#endif

typedef struct {
    TcNsDevFile *devFile;
    TcNsClientContext *clientContext;
    TcNsSession *session;
    TcNsTempBuf *localTempBuffer;
    unsigned int tmpBufSize;
} TcCallParams;

typedef struct {
    TcNsDevFile *devFile;
    TcNsClientContext *clientContext;
    TcNsSession *session;
    TcNsOperation *operation;
    TcNsTempBuf *localTempBuffer;
    unsigned int tmpBufSize;
    unsigned int *transParamTypeToTee;
    unsigned int TransParamTypeSize;
} AllocParams;

typedef struct {
    TcNsDevFile *devFile;
    TcNsClientContext *clientContext;
    TcNsOperation *operation;
    TcNsTempBuf *localTempBuffer;
    unsigned int tmpBufSize;
    bool isComplete;
} UpdateParams;

#define MAX_SHARED_SIZE 0x100000      /* 1 MiB */
#define TEEC_PARAM_TYPES(param0_type, param1_type, param2_type, param3_type) \
    (((param3_type) << 12) | ((param2_type) << 8) | \
     ((param1_type) << 4) | (param0_type))

#define TEEC_PARAM_TYPE_GET(paramTypes, index) \
    (((paramTypes) >> ((index) << 2)) & 0x0F)

#define ROUND_UP(N, S) (((N)+(S)-1)&(~((S)-1)))

static void FreeOperation(TcCallParams *params, TcNsOperation *operation);

#define INPUT_DIR 0
#define OUTPUT_DIR 1
#define BOTH_DIR 2
/* dir: 0-inclue input, 1-include output, 2-both */
static inline bool TeecValueType(unsigned int type, int dir)
{
    return (((dir == INPUT_DIR || dir == BOTH_DIR) && type == TEEC_VALUE_INPUT) ||
        ((dir == OUTPUT_DIR || dir == BOTH_DIR) && type == TEEC_VALUE_OUTPUT) ||
        type == TEEC_VALUE_INOUT) ? true : false;
}

static inline bool TeecTmpmemType(unsigned int type, int dir)
{
    return (((dir == INPUT_DIR || dir == BOTH_DIR) && type == TEEC_MEMREF_TEMP_INPUT) ||
        ((dir == OUTPUT_DIR || dir == BOTH_DIR) && type == TEEC_MEMREF_TEMP_OUTPUT) ||
        type == TEEC_MEMREF_TEMP_INOUT) ? true : false;
}

static inline bool TeecMemrefType(unsigned int type, int dir)
{
    return (((dir == INPUT_DIR || dir == BOTH_DIR) && type == TEEC_MEMREF_PARTIAL_INPUT) ||
        ((dir == OUTPUT_DIR || dir == BOTH_DIR) && type == TEEC_MEMREF_PARTIAL_OUTPUT) ||
        type == TEEC_MEMREF_PARTIAL_INOUT) ? true : false;
}

static int CheckUserParamValue(const TcNsClientContext *clientContext,
    unsigned int index)
{
    if (clientContext == NULL) {
        tloge("clientContext is null.\n");
        return -EINVAL;
    }
    if (index > TEE_PARAM_FOUR) {
        tloge("index is invalid, index:%x.\n", index);
        return -EINVAL;
    }
    return 0;
}

static int IsMemParam(unsigned int paramType)
{
    return (paramType == TEEC_MEMREF_TEMP_INPUT) ||
        (paramType == TEEC_MEMREF_TEMP_OUTPUT) ||
        (paramType == TEEC_MEMREF_TEMP_INOUT) ||
        (paramType == TEEC_MEMREF_PARTIAL_INPUT) ||
        (paramType == TEEC_MEMREF_PARTIAL_OUTPUT) ||
        (paramType == TEEC_MEMREF_PARTIAL_INOUT);
}

static int IsValueParam(unsigned int paramType)
{
    return (paramType == TEEC_VALUE_INPUT) ||
        (paramType == TEEC_VALUE_OUTPUT) ||
        (paramType == TEEC_VALUE_INOUT) ||
        (paramType == TEEC_ION_INPUT) ||
        (paramType == TEEC_ION_SGLIST_INPUT);
}

static int CheckMemParam(TcNsClientParam *clientParam)
{
    uint32_t size;
    /* Check the size and buffer addresses  have valid userspace addresses */
    if (!AccessOk(VERIFY_READ,
        (unsigned long)(uintptr_t)clientParam->memref.sizeAddr,
        sizeof(uint32_t))) {
        return -EFAULT;
    }
    GetUser(&size,
        (uint32_t *)(uintptr_t)clientParam->memref.sizeAddr);
    /* Check if the buffer address is valid user space address */
    if (!AccessOk(VERIFY_READ,
        (unsigned long)(uintptr_t)clientParam->memref.buffer,
        size)) {
        return -EFAULT;
    }
    return 0;
}

static int CheckValueParam(TcNsClientParam *clientParam)
{
    if (!AccessOk(VERIFY_READ,
        (unsigned long)(uintptr_t)clientParam->value.aAddr,
        sizeof(uint32_t))) {
        return -EFAULT;
    }
    if (!AccessOk(VERIFY_READ,
        (unsigned long)(uintptr_t)clientParam->value.bAddr,
        sizeof(uint32_t))) {
        return -EFAULT;
    }
    return 0;
}

int TcUserParamValid(TcNsClientContext *clientContext,
    unsigned int index)
{
    TcNsClientParam *clientParam = NULL;
    unsigned int paramType;
    int checkResult = CheckUserParamValue(clientContext, index);
    if (checkResult != 0) {
        return checkResult;
    }

    clientParam = &(clientContext->params[index]);
    paramType = TEEC_PARAM_TYPE_GET(clientContext->paramTypes, index);
    tlogd("Param %u type is %x\n", index, paramType);
    if (paramType == TEEC_NONE) {
        tlogd("paramType is TEEC_NONE.\n");
        return 0;
    }
    if (IsMemParam(paramType)) {
        return CheckMemParam(clientParam);
    } else if (IsValueParam(paramType)) {
        return CheckValueParam(clientParam);
    } else {
        tloge("paramTypes is not supported.\n");
        return -EFAULT;
    }
}

/*
 * These function handle read from client. Because client here can be
 * kernel client or user space client, we must use the proper function
 */
static int ReadFromClient(void *dest, size_t destSize,
    const void *src, size_t size, uint8_t kernelApi)
{
    int ret;
    bool checkValue = false;

    checkValue = (dest == NULL) || (src == NULL);
    if (checkValue == true) {
        tloge("src or dest is NULL input buffer\n");
        return -EINVAL;
    }
    /*  to be sure that size is <= dest's buffer size. */
    if (size > destSize) {
        tloge("size is larger than destSize or size is 0\n");
        return -EINVAL;
    }
    if (size == 0) {
        return 0;
    }

    if (kernelApi) {
        checkValue = (!LOS_IsUserAddress((uintptr_t)src) && LOS_PaddrQuery((void *)src));
        if (!checkValue) {
            tloge("invalid addr\n");
            return -EFAULT;
        }
        ret = memcpy_s(dest, destSize, src, size);
        if (ret != EOK) {
            tloge("memcpy fail. line=%d, s_ret=%d\n",
                __LINE__, ret);
            return ret;
        }
        return ret;
    }
    /* buffer is in user space(CA call TEE API) */
    if (copy_from_user(dest, src, size)) {
        tloge("copy from user failed\n");
        return -EFAULT;
    }

    return 0;
}

static int WriteToClient(void *dest, size_t destSize,
    const void *src, size_t size, uint8_t kernelApi)
{
    int ret;
    bool checkValue = false;

    checkValue = (dest == NULL) || (src == NULL);
    if (checkValue == true) {
        tloge("src or dest is NULL input buffer\n");
        return -EINVAL;
    }
    /*  to be sure that size is <= dest's buffer size. */
    if (size > destSize) {
        tloge("size is larger than destSize\n");
        return -EINVAL;
    }
    if (size == 0) {
        return 0;
    }

    if (kernelApi) {
        checkValue = (!LOS_IsUserAddress((uintptr_t)src) && LOS_PaddrQuery((void *)src));
        if (!checkValue) {
            tloge("invalid addr\n");
            return -EFAULT;
        }
        ret = memcpy_s(dest, destSize, src, size);
        if (ret != EOK) {
            tloge("write to client fail. line=%d, ret=%d\n",
                  __LINE__, ret);
            return ret;
        }
        return ret;
    }
    /* buffer is in user space(CA call TEE API) */
    if (copy_to_user(dest, src, size)) {
        tloge("copy to user failed\n");
        return -EFAULT;
    }
    return 0;
}

static int CheckParamsForAlloc(const TcCallParams *params,
    const TcNsOperation *operation)
{
    if (params->devFile == NULL) {
        tloge("devFile is null");
        return -EINVAL;
    }
    if (params->session == NULL) {
        tloge("session is null\n");
        return -EINVAL;
    }
    if (operation == NULL) {
        tloge("operation is null\n");
        return -EINVAL;
    }
    if (params->localTempBuffer == NULL) {
        tloge("localTempBuffer is null");
        return -EINVAL;
    }
    if (params->tmpBufSize != (unsigned int)TEE_PARAM_NUM) {
        tloge("tmpBufSize is wrong");
        return -EINVAL;
    }
    return 0;
}

static int CheckContextForAlloc(const TcNsClientContext *clientContext)
{
    if (clientContext == NULL) {
        tloge("clientContext is null");
        return -EINVAL;
    }
    if (clientContext->paramTypes == 0) {
        tloge("invalid param type\n");
        return -EINVAL;
    }
    return 0;
}

static void SetKernelParamsForOpenSession(uint8_t flags,
    int index, uint8_t *kernelParams)
{
    /*
     * Normally kernelParams = kernelApi
     * But when TC_CALL_LOGIN, params 2/3 will
     * be filled by kernel. so under this circumstance,
     * params 2/3 has to be set to kernel mode; and
     * param 0/1 will keep the same with kernelApi.
     */
    bool checkValue = (flags & TC_CALL_LOGIN) && (index >= TEE_PARAM_THREE);
    if (checkValue) {
        *kernelParams = TEE_REQ_FROM_KERNEL_MODE;
    }
    return;
}

#ifdef SECURITY_AUTH_ENHANCE
static bool IsOpenSessionByIndex(uint8_t flags, uint32_t cmdId,
    int index);
#endif

static int CheckSizeForAlloc(const AllocParams *paramsIn, unsigned int index)
{
    bool checkValue = false;

    checkValue = (paramsIn->TransParamTypeSize != TEE_PARAM_NUM ||
        paramsIn->tmpBufSize != TEE_PARAM_NUM ||
        index >= TEE_PARAM_NUM);
    if (checkValue == true) {
        tloge("buf size or params type or index is invalid.\n");
        return -EFAULT;
    }
    return 0;
}

static int CheckAllocTmpMem(AllocParams *paramsIn, unsigned int index, TcNsClientParam **clientParam,
    uint32_t *bufferSize, uint8_t kernelParams)
{
    TcNsClientContext *clientContext = paramsIn->clientContext;
    if (CheckSizeForAlloc(paramsIn, index) != 0) {
        return -EFAULT;
    }
    /* For interface compatibility sake we assume buffer size to be 32bits */
    *clientParam = &(clientContext->params[index]);
    if (ReadFromClient(bufferSize, sizeof(*bufferSize),
        (uint32_t __user *)(uintptr_t)(*clientParam)->memref.sizeAddr,
        sizeof(uint32_t), kernelParams)) {
        tloge("copy memref.sizeAddr failed\n");
        return -EFAULT;
    }
    /* Don't allow unbounded malloc requests */
    if (*bufferSize > MAX_SHARED_SIZE) {
        tloge("bufferSize %u from user is too large\n", *bufferSize);
        return -EFAULT;
    }
    return 0;
}

static int AllocForTmpMem(AllocParams *paramsIn,
    uint8_t kernelParams, unsigned int paramType, uint8_t flags,
    unsigned int index)
{
    TcNsClientContext *clientContext = paramsIn->clientContext;
    TcNsTempBuf *localTempBuffer = paramsIn->localTempBuffer;
    TcNsOperation *operation = paramsIn->operation;
    TcNsSession *session = paramsIn->session;
    unsigned int *transParamTypeToTee = paramsIn->transParamTypeToTee;
    TcNsClientParam *clientParam = NULL;
    void *tempBuf = NULL;
    uint32_t bufferSize = 0;
    bool checkValue = false;
    int ret;

    ret = CheckAllocTmpMem(paramsIn, index, &clientParam, &bufferSize, kernelParams);
    if (ret) {
        return ret;
    }
    tempBuf = MailboxAlloc(bufferSize, MB_FLAG_ZERO);
    /* If buffer size is zero or malloc failed */
    if (tempBuf == NULL) {
        tloge("tempBuf malloc failed, i = %u.\n", index);
        return -ENOMEM;
    }
    tlogd("tempBuf malloc ok, i = %u.\n", index);
    localTempBuffer[index].tempBuffer = tempBuf;
    localTempBuffer[index].size = bufferSize;
    checkValue = (paramType == TEEC_MEMREF_TEMP_INPUT) ||
        (paramType == TEEC_MEMREF_TEMP_INOUT);
    if (checkValue == true) {
        tlogv("clientParam->memref.buffer=0x%llx\n",
            clientParam->memref.buffer);
        /* Kernel side buffer */
        if (ReadFromClient(tempBuf, bufferSize,
            (void *)(uintptr_t)clientParam->memref.buffer,
            bufferSize, kernelParams)) {
            tloge("copy memref.buffer failed\n");
            return -EFAULT;
        }
    }
#ifdef SECURITY_AUTH_ENHANCE
    if (IsOpenSessionByIndex(flags, clientContext->cmdId, index) == true) {
        ret = EncryptLoginInfo(bufferSize,
            tempBuf, session->secureInfo.cryptoInfo.key);
        if (ret != 0) {
            tloge("SECURITY_AUTH_ENHANCE:encry failed\n");
            return ret;
        }
    }
#endif
    operation->params[index].memref.buffer = LOS_PaddrQuery((void *)tempBuf);
    operation->bufferHaddr[index] = 0;
    operation->params[index].memref.size = bufferSize;
    /* TEEC_MEMREF_TEMP_INPUT equal to TEE_PARAM_TYPE_MEMREF_INPUT */
    transParamTypeToTee[index] = paramType;
    return ret;
}

static int CheckBufferForRef(uint32_t *bufferSize,
    const TcNsClientParam *clientParam, uint8_t kernelParams)
{
    if (ReadFromClient(bufferSize, sizeof(*bufferSize),
        (uint32_t __user *)(uintptr_t)clientParam->memref.sizeAddr,
        sizeof(uint32_t), kernelParams)) {
        tloge("copy memref.sizeAddr failed\n");
        return -EFAULT;
    }
    if (*bufferSize == 0) {
        tloge("bufferSize from user is 0\n");
        return -ENOMEM;
    }
    return 0;
}

static int CheckRefSharedMem(TcNsSharedMem *sharedMem, TcNsClientParam *clientParam,
    uint32_t bufferSize, int index, TcNsOperation *operation)
{
    /* arbitrary CA can control offset by ioctl, so in here
    * offset must be checked, and avoid integer overflow.
    */
    int checkValue = ((sharedMem->len -
        clientParam->memref.offset) >= bufferSize) &&
        (sharedMem->len > clientParam->memref.offset);
    if (checkValue == true) {
        void *bufferAddr =
            (void *)(uintptr_t)((uintptr_t)sharedMem->kernelAddr + clientParam->memref.offset);
        bufferAddr = MailboxCopyAlloc(bufferAddr, bufferSize);
        if (bufferAddr == NULL) {
            tloge("alloc mailbox copy failed\n");
            return -ENOMEM;
        }
        operation->mbBuffer[index] = bufferAddr;
        operation->params[index].memref.buffer = LOS_PaddrQuery(bufferAddr);
        operation->bufferHaddr[index] = 0;
        /* save sharedMem in operation
         * so that we can use it while FreeOperation
         */
        operation->sharemem[index] = sharedMem;
        GetSharememStruct(sharedMem);
    } else {
        tloge("Unexpected size %u vs %u",
            sharedMem->len, bufferSize);
    }
    return 0;
}

static int AllocForRefMem(AllocParams *paramsIn,
    uint8_t kernelParams, unsigned int paramType, int index)
{
    TcNsClientContext *clientContext = paramsIn->clientContext;
    TcNsOperation *operation = paramsIn->operation;
    unsigned int *transParamTypeToTee = paramsIn->transParamTypeToTee;
    TcNsDevFile *devFile = paramsIn->devFile;
    TcNsClientParam *clientParam = NULL;
    TcNsSharedMem *sharedMem = NULL;
    uint32_t bufferSize = 0;
    bool checkValue = false;
    int ret;

    if (CheckSizeForAlloc(paramsIn, index) != 0) {
        return -EFAULT;
    }
    clientParam = &(clientContext->params[index]);
    ret = CheckBufferForRef(&bufferSize, clientParam, kernelParams);
    if (ret != 0) {
        return ret;
    }
    operation->params[index].memref.buffer = 0;
    /* find kernel addr refered to user addr */
    mutex_lock(&devFile->sharedMemLock);
    list_for_each_entry(sharedMem, &devFile->sharedMemList, head) {
        if (sharedMem->userAddr ==
            (void *)(uintptr_t)clientParam->memref.buffer) {
            ret = CheckRefSharedMem(sharedMem, clientParam, bufferSize, index, operation);
            break;
        }
    }
    mutex_unlock(&devFile->sharedMemLock);
    /* for 8G physical memory device, there is a chance that
     * operation->params[i].memref.buffer could be all 0,
     * bufferHaddr cannot be 0 in the same time.
     */
    checkValue = (!operation->params[index].memref.buffer) &&
        (!operation->bufferHaddr[index]);
    if (checkValue == true) {
        tloge("can not find shared buffer, exit\n");
        return -EINVAL;
    }
    operation->params[index].memref.size = bufferSize;
    /* Change TEEC_MEMREF_PARTIAL_XXXXX  to TEE_PARAM_TYPE_MEMREF_XXXXX */
    transParamTypeToTee[index] = paramType -
        (TEEC_MEMREF_PARTIAL_INPUT - TEE_PARAM_TYPE_MEMREF_INPUT);
    return ret;
}

static int CopyForValue(AllocParams *paramsIn, uint8_t kernelParams,
    unsigned int paramType, int index)
{
    TcNsOperation *operation = paramsIn->operation;
    unsigned int *transParamTypeToTee = paramsIn->transParamTypeToTee;
    TcNsClientContext *clientContext = paramsIn->clientContext;
    int ret = 0;
    TcNsClientParam *clientParam = NULL;

    if (CheckSizeForAlloc(paramsIn, index) != 0) {
        return -EFAULT;
    }

    clientParam = &(clientContext->params[index]);
    if (ReadFromClient(&operation->params[index].value.a,
        sizeof(operation->params[index].value.a),
        (void *)(uintptr_t)clientParam->value.aAddr,
        sizeof(operation->params[index].value.a),
        kernelParams)) {
        tloge("copy value.aAddr failed\n");
        return -EFAULT;
    }
    if (ReadFromClient(&operation->params[index].value.b,
        sizeof(operation->params[index].value.b),
        (void *)(uintptr_t)clientParam->value.bAddr,
        sizeof(operation->params[index].value.b),
        kernelParams)) {
        tloge("copy value.bAddr failed\n");
        return -EFAULT;
    }
    /* TEEC_VALUE_INPUT equal
     * to TEE_PARAM_TYPE_VALUE_INPUT
     */
    transParamTypeToTee[index] = paramType;
    return ret;
}

static int AllocOperationParam(TcCallParams *params, AllocParams *paramsIn,
    uint8_t flags, uint8_t kernelParams, int index)
{
    SetKernelParamsForOpenSession(flags, index, &kernelParams);
    unsigned int paramType = TEEC_PARAM_TYPE_GET(
        params->clientContext->paramTypes, index);
    tlogd("Param %u type is %x\n", index, paramType);
    if (TeecTmpmemType(paramType, TEE_PARAM_THREE)) {
        /* temp buffers we need to allocate/deallocate
            * for every operation
            */
        return AllocForTmpMem(paramsIn, kernelParams,
            paramType, flags, index);
    } else if (TeecMemrefType(paramType, TEE_PARAM_THREE)) {
        /* MEMREF_PARTIAL buffers are already allocated so we just
            * need to search for the sharedMem ref;
            * For interface compatibility we assume buffer size to be 32bits
            */
        return AllocForRefMem(paramsIn, kernelParams,
            paramType, index);
    } else if (TeecValueType(paramType, TEE_PARAM_THREE)) {
        return CopyForValue(paramsIn, kernelParams,
            paramType, index);
    } else {
        tlogd("paramType = TEEC_NONE\n");
    }
    return 0;
}

static int AllocOperation(TcCallParams *params,
    TcNsOperation *operation, uint8_t flags)
{
    int ret;
    unsigned int index;
    unsigned int transParamTypeToTee[TEE_PARAM_NUM] = { TEE_PARAM_TYPE_NONE };
    uint8_t kernelParams;
    AllocParams paramsIn = {
        params->devFile, params->clientContext, params->session,
        operation, params->localTempBuffer, TEE_PARAM_NUM,
        transParamTypeToTee, TEE_PARAM_NUM,
    };
    ret = CheckParamsForAlloc(params, operation);
    if (ret != 0) {
        return ret;
    }
    ret = CheckContextForAlloc(params->clientContext);
    if (ret != 0) {
        return ret;
    }
    kernelParams = params->devFile->kernelApi;
    tlogd("Allocating param types %08X\n",
        params->clientContext->paramTypes);
    /* Get the 4 params from the client context */
    for (index = 0; index < TEE_PARAM_NUM; index++) {
        /*
         * Normally kernelParams = kernelApi
         * But when TC_CALL_LOGIN(open session), params 2/3 will
         * be filled by kernel for authentication. so under this circumstance,
         * params 2/3 has to be set to kernel mode for  authentication; and
         * param 0/1 will keep the same with user_api.
         */
        ret = AllocOperationParam(params, &paramsIn, flags, kernelParams, index);
        if (ret != 0) {
            break;
        }
    }
    if (ret != 0) {
        FreeOperation(params, operation);
        return ret;
    }
    operation->paramTypes =
        TEEC_PARAM_TYPES(transParamTypeToTee[TEE_PARAM_ONE],
        transParamTypeToTee[TEE_PARAM_TWO],
        transParamTypeToTee[TEE_PARAM_THREE],
        transParamTypeToTee[TEE_PARAM_FOUR]);
    return ret;
}

static int CheckParamsForUpdate(const TcCallParams *inParams)
{
    if (inParams->devFile == NULL) {
        tloge("devFile is null");
        return -EINVAL;
    }
    if (inParams->clientContext == NULL) {
        tloge("clientContext is null");
        return -EINVAL;
    }
    if (inParams->localTempBuffer == NULL) {
        tloge("localTempBuffer is null");
        return -EINVAL;
    }
    if (inParams->tmpBufSize != TEE_PARAM_NUM) {
        tloge("tmpBufSize is invalid");
        return -EINVAL;
    }
    return 0;
}

static int UpdateForTmpMem(UpdateParams *paramsIn, int index)
{
    TcNsClientParam *clientParam = NULL;
    uint32_t bufferSize;
    TcNsDevFile *devFile = paramsIn->devFile;
    TcNsClientContext *clientContext = paramsIn->clientContext;
    TcNsOperation *operation = paramsIn->operation;
    TcNsTempBuf *localTempBuffer = paramsIn->localTempBuffer;
    bool isComplete = paramsIn->isComplete;
    bool checkValue = paramsIn->tmpBufSize != TEE_PARAM_NUM ||
        index >= TEE_PARAM_NUM;

    if (checkValue == true) {
        tloge("tmpBufSize or index is invalid\n");
        return -EFAULT;
    }
    /* temp buffer */
    bufferSize = operation->params[index].memref.size;
    clientParam = &(clientContext->params[index]);
    /* Size is updated all the time */
    if (WriteToClient((void *)(uintptr_t)clientParam->memref.sizeAddr,
        sizeof(bufferSize),
        &bufferSize, sizeof(bufferSize),
        devFile->kernelApi)) {
        tloge("copy tempbuf size failed\n");
        return -EFAULT;
    }
    if (bufferSize > localTempBuffer[index].size) {
        /* incomplete case, when the buffer size is invalid see next param */
        if (!isComplete)
            return 0;
        /* complete case, operation is allocated from mailbox
         *  and share with gtask, so it's possible to be changed
         */
        tloge("clientParam->memref.size has been changed larger than the initial\n");
        return -EFAULT;
    }
    /* Only update the buffer when the buffer size is valid in complete case */
    if (WriteToClient((void *)(uintptr_t)clientParam->memref.buffer,
        operation->params[index].memref.size,
        localTempBuffer[index].tempBuffer,
        operation->params[index].memref.size, devFile->kernelApi)) {
        tloge("copy tempbuf failed\n");
        return -ENOMEM;
    }
    return 0;
}

static int UpdateForRefMem(UpdateParams *paramsIn, unsigned int index)
{
    TcNsClientParam *clientParam = NULL;
    uint32_t bufferSize;
    bool checkValue = false;
    unsigned int origSize = 0;
    TcNsDevFile *devFile = paramsIn->devFile;
    TcNsClientContext *clientContext = paramsIn->clientContext;
    TcNsOperation *operation = paramsIn->operation;

    if (index >= TEE_PARAM_NUM) {
        tloge("index is invalid\n");
        return -EFAULT;
    }
    /* update size */
    bufferSize = operation->params[index].memref.size;
    clientParam = &(clientContext->params[index]);

    if (ReadFromClient(&origSize,
        sizeof(origSize),
        (uint32_t __user *)(uintptr_t)clientParam->memref.sizeAddr,
        sizeof(origSize), devFile->kernelApi)) {
        tloge("copy orig memref.sizeAddr failed\n");
        return -EFAULT;
    }
    if (WriteToClient((void *)(uintptr_t)clientParam->memref.sizeAddr,
        sizeof(bufferSize),
        &bufferSize, sizeof(bufferSize), devFile->kernelApi)) {
        tloge("copy buf size failed\n");
        return -EFAULT;
    }
    /* copy from mbBuffer to sharemem */
    checkValue = operation->mbBuffer[index] && origSize >= bufferSize;
    if (checkValue == true) {
        void *bufferAddr =
            (void *)(uintptr_t)((uintptr_t)
            operation->sharemem[index]->kernelAddr +
            clientParam->memref.offset);
        if (memcpy_s(bufferAddr,
            operation->sharemem[index]->len -
            clientParam->memref.offset,
            operation->mbBuffer[index], bufferSize)) {
            tloge("copy to sharemem failed\n");
            return -EFAULT;
        }
    }
    return 0;
}

static int UpdateForValue(UpdateParams *paramsIn, unsigned int index)
{
    TcNsClientParam *clientParam = NULL;
    TcNsDevFile *devFile = paramsIn->devFile;
    TcNsClientContext *clientContext = paramsIn->clientContext;
    TcNsOperation *operation = paramsIn->operation;

    if (index >= TEE_PARAM_NUM) {
        tloge("index is invalid\n");
        return -EFAULT;
    }
    clientParam = &(clientContext->params[index]);
    if (WriteToClient((void *)(uintptr_t)clientParam->value.aAddr,
        sizeof(operation->params[index].value.a),
        &operation->params[index].value.a,
        sizeof(operation->params[index].value.a),
        devFile->kernelApi)) {
        tloge("inc copy value.aAddr failed\n");
        return -EFAULT;
    }
    if (WriteToClient((void *)(uintptr_t)clientParam->value.bAddr,
        sizeof(operation->params[index].value.b),
        &operation->params[index].value.b,
        sizeof(operation->params[index].value.b),
        devFile->kernelApi)) {
        tloge("inc copy value.bAddr failed\n");
        return -EFAULT;
    }
    return 0;
}

static int UpdateClientOperation(TcCallParams *params,
    TcNsOperation *operation, bool isComplete)
{
    int ret;
    unsigned int paramType;
    unsigned int index;
    UpdateParams paramsIn = {
        params->devFile, params->clientContext,
        operation, params->localTempBuffer, TEE_PARAM_NUM,
        isComplete
    };
    ret = CheckParamsForUpdate(params);
    if (ret != 0) {
        return -EINVAL;
    }
    /* if paramTypes is NULL, no need to update */
    if (params->clientContext->paramTypes == 0) {
        return 0;
    }
    for (index = 0; index < TEE_PARAM_NUM; index++) {
        paramType = TEEC_PARAM_TYPE_GET(
            params->clientContext->paramTypes, index);
        if (TeecTmpmemType(paramType, OUTPUT_DIR)) {
            ret = UpdateForTmpMem(&paramsIn, index);
        } else if (TeecMemrefType(paramType, OUTPUT_DIR)) {
            ret = UpdateForRefMem(&paramsIn, index);
        } else if (isComplete &&
            TeecValueType(paramType, OUTPUT_DIR)) {
            ret = UpdateForValue(&paramsIn, index);
        } else {
            tlogd("paramType:%u don't need to update.\n",
                paramType);
        }
        if (ret != 0) {
            break;
        }
    }
    return ret;
}

static void FreeOperation(TcCallParams *params, TcNsOperation *operation)
{
    unsigned int paramType;
    unsigned int index;
    void *tempBuf = NULL;
    bool checkTempMem = false;
    bool checkPartMem = false;
    TcNsTempBuf *localTempBuffer = params->localTempBuffer;
    TcNsClientContext *clientContext = params->clientContext;

    if (params->tmpBufSize != TEE_PARAM_NUM) {
        tloge("tmpBufSize is invalid %x.\n", params->tmpBufSize);
    }
    for (index = 0; index < TEE_PARAM_NUM; index++) {
        paramType = TEEC_PARAM_TYPE_GET(
            clientContext->paramTypes, index);
        checkTempMem = paramType == TEEC_MEMREF_TEMP_INPUT ||
            paramType == TEEC_MEMREF_TEMP_OUTPUT ||
            paramType == TEEC_MEMREF_TEMP_INOUT;
        checkPartMem = paramType == TEEC_MEMREF_PARTIAL_INPUT ||
            paramType == TEEC_MEMREF_PARTIAL_OUTPUT ||
            paramType == TEEC_MEMREF_PARTIAL_INOUT;
        if (checkTempMem == true) {
            /* free temp buffer */
            tempBuf = localTempBuffer[index].tempBuffer;
            tlogd("Free temp buf, i = %u\n", index);
            if (LOS_PaddrQuery(tempBuf) &&
                !ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)tempBuf)) {
                MailboxFree(tempBuf);
                tempBuf = NULL;
            }
        } else if (checkPartMem == true) {
            PutSharememStruct(operation->sharemem[index]);
            if (operation->mbBuffer[index]) {
                MailboxFree(operation->mbBuffer[index]);
            }
        }
    }
}

#ifdef SECURITY_AUTH_ENHANCE
unsigned char g_authHashBuf[MAX_SHA_256_SZ * NUM_OF_SO + HASH_PLAINTEXT_ALIGNED_SIZE + IV_BYTESIZE];
#else
unsigned char g_authHashBuf[MAX_SHA_256_SZ * NUM_OF_SO + MAX_SHA_256_SZ];
#endif

#ifdef SECURITY_AUTH_ENHANCE
static int32_t SaveTokenInfo(void *dstTeec, uint32_t dstSize,
    uint8_t *srcBuf, uint32_t srcSize, uint8_t kernelApi)
{
    uint8_t tempTeecToken[TOKEN_SAVE_LEN] = {0};
    bool checkValue = (dstTeec == NULL || srcBuf == NULL ||
        dstSize != TOKEN_SAVE_LEN || srcSize == 0);

    if (checkValue == true) {
        tloge("dst data or src data is invalid.\n");
        return -EINVAL;
    }
    /* copy libteec_token && timestamp to libteec */
    if (memmove_s(tempTeecToken, sizeof(tempTeecToken),
        srcBuf, TIMESTAMP_SAVE_INDEX) != EOK) {
        tloge("copy teec token failed.\n");
        return -EFAULT;
    }
    if (memmove_s(&tempTeecToken[TIMESTAMP_SAVE_INDEX],
        TIMESTAMP_LEN_DEFAULT, &srcBuf[TIMESTAMP_BUFFER_INDEX],
        TIMESTAMP_LEN_DEFAULT) != EOK) {
        tloge("copy teec timestamp failed.\n");
        return -EFAULT;
    }
    /* copy libteec_token to libteec */
    if (WriteToClient(dstTeec, dstSize,
        tempTeecToken, TOKEN_SAVE_LEN,
        kernelApi) != EOK) {
        tloge("copy teec token & timestamp failed.\n");
        return -EFAULT;
    }
    /* clear libteec(16byte) */
    if (memset_s(srcBuf, TIMESTAMP_SAVE_INDEX, 0,
        TIMESTAMP_SAVE_INDEX) != EOK) {
        tloge("clear libteec failed.\n");
        return -EFAULT;
    }
    return EOK;
}

static int CheckParamsForFillToken(const TcNsSmcCmd *smcCmd,
    const TcNsToken *tcToken, const uint8_t *mbPackToken,
    uint32_t mbPackTokenSize, const TcNsClientContext *clientContext)
{
    if (smcCmd == NULL || tcToken == NULL || mbPackToken == NULL ||
        clientContext == NULL || mbPackTokenSize < TOKEN_BUFFER_LEN) {
        tloge("in parameter is ivalid.\n");
        return -EFAULT;
    }

    if (clientContext->teecToken == NULL ||
        tcToken->tokenBuffer == NULL) {
        tloge("teecToken or tokenBuffer is NULL, error!\n");
        return -EFAULT;
    }
    return 0;
}

int FillSessionToken(uint8_t *tempLibteecToken, int len, TcNsToken *tcToken,
    const TcNsClientContext *clientContext, const TcNsDevFile *devFile)
{
    errno_t retErr;
    if (len != TOKEN_SAVE_LEN) {
        return -EFAULT;
    }
    if (ReadFromClient(tempLibteecToken,
        TOKEN_SAVE_LEN,
        clientContext->teecToken, TOKEN_SAVE_LEN,
        devFile->kernelApi)) {
        tloge("copy libteec token failed!\n");
        return -EFAULT;
    }
    if (memcmp(&tempLibteecToken[TIMESTAMP_SAVE_INDEX],
        &tcToken->tokenBuffer[TIMESTAMP_BUFFER_INDEX],
        TIMESTAMP_LEN_DEFAULT)) {
        tloge("timestamp compare failed!\n");
        return -EFAULT;
    }
    /* combine tokenBuffer teecToken, 0-15byte */
    if (memmove_s(tcToken->tokenBuffer,
        TIMESTAMP_SAVE_INDEX, tempLibteecToken,
        TIMESTAMP_SAVE_INDEX) != EOK) {
        tloge("copy buffer failed!\n");
        retErr = memset_s(tcToken->tokenBuffer,
            tcToken->tokenLen, 0, TOKEN_BUFFER_LEN);
        if (retErr != EOK)
            tloge("memset buffer error=%d\n", retErr);
        return -EFAULT;
    }
    /* kernal_api, 40byte */
    if (memmove_s((tcToken->tokenBuffer + KERNAL_API_INDEX),
        KERNAL_API_LEN, &devFile->kernelApi,
        KERNAL_API_LEN) != EOK) {
        tloge("copy KERNAL_API_LEN failed!\n");
        retErr = memset_s(tcToken->tokenBuffer,
            tcToken->tokenLen, 0, TOKEN_BUFFER_LEN);
        if (retErr != EOK)
            tloge("fill info memset error=%d\n", retErr);
        return -EFAULT;
    }
    return 0;
}

static int FillTokenInfo(TcNsSmcCmd *smcCmd,
    const TcNsClientContext *clientContext, TcNsToken *tcToken,
    const TcNsDevFile *devFile, bool global, uint8_t *mbPackToken,
    uint32_t mbPackTokenSize)
{
    uint8_t tempLibteecToken[TOKEN_SAVE_LEN] = {0};
    int ret;
    bool checkValue = true;

    ret = CheckParamsForFillToken(smcCmd, tcToken, mbPackToken,
        mbPackTokenSize, clientContext);
    if (ret != 0) {
        return ret;
    }
    checkValue = (clientContext->cmdId == GLOBAL_CMD_ID_CLOSE_SESSION) ||
        (!global);
    if (checkValue == true) {
        ret = FillSessionToken(tempLibteecToken, TOKEN_SAVE_LEN, tcToken, clientContext, devFile);
        if (ret) {
            return ret;
        }
    } else { /* open_session, set tokenBuffer 0 */
        if (memset_s(tcToken->tokenBuffer, tcToken->tokenLen,
            0, TOKEN_BUFFER_LEN) != EOK) {
            tloge("alloc TcNsToken->tokenBuffer error.\n");
            return -EFAULT;
        }
    }
    if (memcpy_s(mbPackToken, mbPackTokenSize, tcToken->tokenBuffer,
        tcToken->tokenLen)) {
        tloge("copy token failed\n");
        return -EFAULT;
    }

    smcCmd->pid = OsCurrTaskGet()->processID;
    smcCmd->tokenPhys = LOS_PaddrQuery(mbPackToken);
    smcCmd->tokenHphys = 0;
    return EOK;
}

static int LoadSecurityEnhanceInfo(TcCallParams *params,
    TcNsSmcCmd *smcCmd, TcNsToken *tcToken,
    struct MbCmdPack *mbPack, bool global, bool IsTokenWork)
{
    int ret;
    bool IsOpenSessionCmd = false;
    TcNsDevFile *devFile = params->devFile;
    TcNsClientContext *clientContext = params->clientContext;
    TcNsSession *session = params->session;

    if (smcCmd == NULL || mbPack == NULL) {
        tloge("in parameter is invalid.\n");
        return -EFAULT;
    }
    if (IsTokenWork == true) {
        ret = FillTokenInfo(smcCmd, clientContext, tcToken,
            devFile, global, mbPack->token, sizeof(mbPack->token));
        if (ret != EOK) {
            tloge("fill info failed. global=%u, cmdId=%u, sessionId=%u\n",
                global, smcCmd->cmdId, smcCmd->contextId);
            return -EFAULT;
        }
    }
    IsOpenSessionCmd = global &&
        (smcCmd->cmdId == GLOBAL_CMD_ID_OPEN_SESSION);
    if (IsOpenSessionCmd) {
        if (session == NULL) {
            tloge("invalid session when load secure info\n");
            return -EFAULT;
        }
        if (GenerateEncryptedSessionSecureParams(
            &session->secureInfo, mbPack->secureParams,
            sizeof(mbPack->secureParams))) {
            tloge("Can't get encrypted session parameters buffer!");
            return -EFAULT;
        }
        smcCmd->paramsPhys =
            LOS_PaddrQuery((void *)mbPack->secureParams);
        smcCmd->paramsHphys = 0;
    }
    return EOK;
}

#ifdef TC_ASYNC_NOTIFY_SUPPORT
static int CheckParamsForAppendToken(
    const TcNsClientContext *clientContext,
    const TcNsToken *tcToken, const TcNsDevFile *devFile,
    uint32_t mbPackTokenSize)
{
    if (clientContext == NULL || devFile == NULL || tcToken == NULL) {
        tloge("in parameter is invalid.\n");
        return -EFAULT;
    }
    if (clientContext->teecToken == NULL ||
        tcToken->tokenBuffer == NULL) {
        tloge("teecToken or tokenBuffer is NULL, error!\n");
        return -EFAULT;
    }
    if (mbPackTokenSize < TOKEN_BUFFER_LEN) {
        tloge("mbPackTokenSize is invalid.\n");
        return -EFAULT;
    }
    return 0;
}

static int AppendTeecToken(const TcNsClientContext *clientContext,
    TcNsToken *tcToken, const TcNsDevFile *devFile, bool global,
    uint8_t *mbPackToken, uint32_t mbPackTokenSize)
{
    uint8_t tempLibteecToken[TOKEN_SAVE_LEN] = {0};
    int sret;
    int ret;

    ret = CheckParamsForAppendToken(clientContext, tcToken,
        devFile, mbPackTokenSize);
    if (ret) {
        return ret;
    }
    if (!global) {
        if (ReadFromClient(tempLibteecToken,
            TOKEN_SAVE_LEN,
            clientContext->teecToken, TOKEN_SAVE_LEN,
            devFile->kernelApi)) {
            tloge("copy libteec token failed!\n");
            return -EFAULT;
        }
        /* combine tokenBuffer ,teecToken, 0-15byte */
        if (memmove_s(tcToken->tokenBuffer, tcToken->tokenLen,
            tempLibteecToken, TIMESTAMP_SAVE_INDEX) != EOK) {
            tloge("copy tempLibteecToken failed!\n");
            sret = memset_s(tcToken->tokenBuffer,
                tcToken->tokenLen, 0, TOKEN_BUFFER_LEN);
            if (sret != 0) {
                tloge("memset failed!\n");
                return -EFAULT;
            }
            return -EFAULT;
        }
        if (memcpy_s(mbPackToken, mbPackTokenSize,
            tcToken->tokenBuffer, tcToken->tokenLen)) {
            tloge("copy token failed\n");
            return -EFAULT;
        }
    }
    return EOK;
}
#endif

static int PostProcessToken(const TcNsSmcCmd *smcCmd,
    TcNsClientContext *clientContext, TcNsToken *tcToken,
    uint8_t *mbPackToken, uint32_t mbPackTokenSize,
    uint8_t kernelApi, bool global)
{
    int ret;
    bool checkValue = false;

    checkValue = (mbPackToken == NULL || tcToken == NULL ||
        clientContext == NULL || clientContext->teecToken == NULL ||
        tcToken->tokenBuffer == NULL ||
        mbPackTokenSize < TOKEN_BUFFER_LEN);
    if (checkValue == true) {
        tloge("in parameter is invalid.\n");
        return -EINVAL;
    }
    if (memcpy_s(tcToken->tokenBuffer, tcToken->tokenLen, mbPackToken,
        mbPackTokenSize)) {
        tloge("copy token failed\n");
        return -EFAULT;
    }
    if (memset_s(mbPackToken, mbPackTokenSize, 0, mbPackTokenSize)) {
        tloge("memset mbPack token error.\n");
        return -EFAULT;
    }
    if (SyncTimestamp(smcCmd, tcToken->tokenBuffer, tcToken->tokenLen, global)
        != TEEC_SUCCESS) {
        tloge("sync time stamp error.\n");
        return -EFAULT;
    }

    ret = SaveTokenInfo(clientContext->teecToken, clientContext->tokenLen,
        tcToken->tokenBuffer, tcToken->tokenLen, kernelApi);
    if (ret != EOK) {
        tloge("save token info  failed.\n");
        return -EFAULT;
    }
    return EOK;
}

#define TEE_TZMP \
{ \
    0xf8028dca, \
    0xaba0, \
    0x11e6, \
    { \
        0x80, 0xf5, 0x76, 0x30, 0x4d, 0xec, 0x7e, 0xb7 \
    } \
}
#define INVALID_TZMP_UID   0xffffffff
static DEFINE_MUTEX(g_tzmpLock);
static unsigned int g_tzmpUid = INVALID_TZMP_UID;

int Tzmp2Uid(const TcNsClientContext *clientContext,
    TcNsSmcCmd *smcCmd, bool global)
{
    TeecUuid uuidTzmp = TEE_TZMP;
    bool checkValue = false;

    if (clientContext == NULL || smcCmd == NULL) {
        tloge("clientContext or smcCmd is null! ");
        return -EINVAL;
    }
    if (memcmp(clientContext->uuid, (unsigned char *)&uuidTzmp,
        sizeof(clientContext->uuid)) == 0) {
        checkValue = smcCmd->cmdId == GLOBAL_CMD_ID_OPEN_SESSION &&
            global;
        if (checkValue == true) {
            /* save tzmp_uid */
            mutex_lock(&g_tzmpLock);
            g_tzmpUid = 0; /* for multisesion, we use same uid */
            smcCmd->uid = 0;
            tlogv("openSession , tzmp_uid.uid is %u", g_tzmpUid);
            mutex_unlock(&g_tzmpLock);
            return EOK;
        }
        mutex_lock(&g_tzmpLock);
        if (g_tzmpUid == INVALID_TZMP_UID) {
            tloge("tzmp_uid.uid error!");
            mutex_unlock(&g_tzmpLock);
            return -EFAULT;
        }
        smcCmd->uid = g_tzmpUid;
        tlogv("invokeCommand or closeSession , tzmp_uid is %u, global is %d",
            g_tzmpUid, global);
        mutex_unlock(&g_tzmpLock);
        return EOK;
    }
    return EOK;
}
#endif

static int CheckParamsForClientCall(const TcNsDevFile *devFile,
    const TcNsClientContext *clientContext)
{
    if (devFile == NULL) {
        tloge("devFile is null");
        return -EINVAL;
    }
    if (clientContext == NULL) {
        tloge("clientContext is null");
        return -EINVAL;
    }
    return 0;
}

static int AllocForClientCall(TcNsSmcCmd **smcCmd,
    struct MbCmdPack **mbPack)
{
    *smcCmd = calloc(1, sizeof(**smcCmd));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)(*smcCmd))) {
        tloge("smcCmd malloc failed.\n");
        return -ENOMEM;
    }
    *mbPack = MailboxAllocCmdPack();
    if (*mbPack == NULL) {
        free(*smcCmd);
        *smcCmd = NULL;
        return -ENOMEM;
    }
    return 0;
}

static int InitSmcCmd(const TcNsDevFile *devFile,
    const TcNsClientContext *clientContext, TcNsSmcCmd *smcCmd,
    const struct MbCmdPack *mbPack, bool global)
{
    smcCmd->globalCmd = global;
    if (memcpy_s(smcCmd->uuid, sizeof(smcCmd->uuid),
        clientContext->uuid, UUID_LEN)) {
        tloge("memcpy_s uuid error.\n");
        return -EFAULT;
    }
    smcCmd->cmdId = clientContext->cmdId;
    smcCmd->devFileId = devFile->devFileId;
    smcCmd->contextId = clientContext->sessionId;
    smcCmd->errOrigin = clientContext->returns.origin;
    smcCmd->started = clientContext->started;
#ifdef SECURITY_AUTH_ENHANCE
    if (Tzmp2Uid(clientContext, smcCmd, global) != EOK) {
        tloge("caution! tzmp uid failed !\n\n");
    }
#endif
    tlogv("current uid is %u\n", smcCmd->uid);
    if (clientContext->paramTypes != 0) {
        smcCmd->operationPhys = LOS_PaddrQuery((void *)&mbPack->operation);
        smcCmd->operationHphys = 0;
    } else {
        smcCmd->operationPhys = 0;
        smcCmd->operationHphys = 0;
    }
    smcCmd->loginMethod = clientContext->login.method;
    return 0;
}

static int CheckLoginForEncrypt(TcNsClientContext *clientContext,
    TcNsSession *session, TcNsSmcCmd *smcCmd,
    struct MbCmdPack *mbPack, int needCheckLogin)
{
    int ret;

    if (needCheckLogin && session != NULL) {
#ifdef SECURITY_AUTH_ENHANCE
        ret = DoEncryption(session->authHashBuf,
            sizeof(session->authHashBuf),
            MAX_SHA_256_SZ * (NUM_OF_SO + 1),
            session->secureInfo.cryptoInfo.key);
        if (ret) {
            tloge("hash encryption failed ret=%d\n", ret);
            return ret;
        }
#endif
        if (memcpy_s(mbPack->loginData, sizeof(mbPack->loginData),
            session->authHashBuf,
            sizeof(session->authHashBuf))) {
            tloge("copy login data failed\n");
            return -EFAULT;
        }
        smcCmd->loginDataPhy = LOS_PaddrQuery(mbPack->loginData);
        smcCmd->loginDataHaddr = 0;
        smcCmd->loginDataLen = MAX_SHA_256_SZ * (NUM_OF_SO + 1);
    } else {
        smcCmd->loginDataPhy = 0;
        smcCmd->loginDataHaddr = 0;
        smcCmd->loginDataLen = 0;
    }
    return 0;
}

static void GetUidForCmd(uint32_t *uid)
{
    *uid = GetTaskUid(OsCurrTaskGet());
}

static int ProcCheckLoginForOpenSession(
    TcCallParams *params, struct MbCmdPack *mbPack,
    bool global, TcNsSmcCmd *smcCmd)
{
    int ret;
    int needCheckLogin;
    TcNsDevFile *devFile = params->devFile;
    TcNsClientContext *clientContext = params->clientContext;
    TcNsSession *session = params->session;

    ret = InitSmcCmd(devFile, clientContext,
        smcCmd, mbPack, global);
    if (ret != 0) {
        return ret;
    }
    needCheckLogin = devFile->pubKeyLen == sizeof(uint32_t) &&
        smcCmd->cmdId == GLOBAL_CMD_ID_OPEN_SESSION &&
        (!IsKernelThread(OsCurrTaskGet())) && global;
    ret = CheckLoginForEncrypt(clientContext, session,
        smcCmd, mbPack, needCheckLogin);
    if (ret != 0) {
        return ret;
    }
#ifdef CONFIG_TEE_SMP
    smcCmd->caPid = GetCurrentPid();
#endif
    return ret;
}

static void ResetSessionId(TcNsClientContext *clientContext,
    bool global, TcNsSmcCmd *smcCmd, int teeRet)
{
    int needReset;

    clientContext->sessionId = smcCmd->contextId;
    // if teeRet error except TEEC_PENDING,but contextId is seted,need to reset to 0.
    needReset = global &&
        clientContext->cmdId == GLOBAL_CMD_ID_OPEN_SESSION &&
        teeRet != 0 && TEEC_PENDING != teeRet;
    if (needReset) {
        clientContext->sessionId = 0;
    }
    return;
}

#ifdef TC_ASYNC_NOTIFY_SUPPORT
static void PendCaThread(TcNsSession *session, const TcNsSmcCmd *smcCmd)
{
    struct TcWaitData *wq = NULL;

    if (session != NULL) {
        wq = &session->waitData;
    }
    if (wq != NULL) {
        tlogv("before wait event\n");
        /* use wait_event instead of wait_event_interruptible so
         * that ap suspend will not wake up the TEE wait call
         */
        wait_event(wq->sendCmdWq, wq->sendWaitFlag);
        wq->sendWaitFlag = 0;
    }
    tlogv("operation start is :%d\n", smcCmd->started);
    return;
}
#endif

static void ProcErrorSituation(TcCallParams *params,
    struct MbCmdPack *mbPack, const TcNsSmcCmd *smcCmd,
    int teeRet, bool operationInit)
{
    /* free(NULL) is safe and this check is probably not required */
    params->clientContext->returns.code = teeRet;
    params->clientContext->returns.origin = smcCmd->errOrigin;
    /* when CA invoke command and crash,
     * Gtask happen to release service node ,tzdriver need to kill ion;
     * ta crash ,tzdriver also need to kill ion
     */
    if (teeRet == TEE_ERROR_TAGET_DEAD || teeRet == TEEC_ERROR_GENERIC) {
        tloge("ta_crash or ca is killed or some error happen\n");
    }
    if (operationInit && mbPack != NULL) {
        FreeOperation(params, &mbPack->operation);
    }
    free((void *)smcCmd);
    MailboxFree(mbPack);
    return;
}

static void ProcShortBufferSituation(TcCallParams *params,
    TcNsOperation *operation, TcNsSmcCmd *smcCmd,
    bool operationInit)
{
    int ret;
    /* update size */
    if (operationInit) {
        ret = UpdateClientOperation(params, operation, false);
        if (ret) {
            smcCmd->errOrigin = TEEC_ORIGIN_COMMS;
            return;
        }
    }
    return;
}

struct TcClientCallPreprocStruct {
    TcNsSmcCmd *smcCmd;
    bool global;
#ifdef SECURITY_AUTH_ENHANCE
    bool IsTokenWork;
    TcNsToken *tcToken;
#endif
    TcCallParams inParams;
    struct MbCmdPack *mbPack;
    bool operationInit;
};

static int TcClientCallPreprocess(TcNsClientContext *clientContext,
    TcNsDevFile *devFile, TcNsSession *session, uint8_t flags, struct TcClientCallPreprocStruct *preproc)
{
    int ret;
    TcNsTempBuf localTempBuffer[TEE_PARAM_NUM] = {
        { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }
    };
    preproc->global = flags & TC_CALL_GLOBAL;
    uint32_t uid = 0;
#ifdef SECURITY_AUTH_ENHANCE
    preproc->tcToken = (session != NULL) ? &session->TcNsToken : NULL;
#endif
    TcCallParams tmpCallParams = {
        devFile, clientContext, session, localTempBuffer, TEE_PARAM_NUM
    };
    if (memcpy_s(&preproc->inParams, sizeof(preproc->inParams), &tmpCallParams, sizeof(tmpCallParams)) != EOK) {
        return -EINVAL;
    }

    GetUidForCmd(&uid);
    ret = CheckParamsForClientCall(devFile, clientContext);
    if (ret != 0) {
        return ret;
    }
    ret = AllocForClientCall(&preproc->smcCmd, &preproc->mbPack);
    if (ret != 0) {
        return ret;
    }
    preproc->smcCmd->uid = uid;
    if (clientContext->paramTypes != 0) {
        ret = AllocOperation(&preproc->inParams, &preproc->mbPack->operation, flags);
        if (ret) {
            tloge("AllocOperation malloc failed");
            goto ERROR;
        }
        preproc->operationInit = true;
    }
    ret = ProcCheckLoginForOpenSession(&preproc->inParams, preproc->mbPack, preproc->global, preproc->smcCmd);
    if (ret != 0) {
        goto ERROR;
    }
#ifdef SECURITY_AUTH_ENHANCE
    /* invoke cmd(global is false) or open session */
    preproc->IsTokenWork = (!preproc->global) || (preproc->smcCmd->cmdId == GLOBAL_CMD_ID_OPEN_SESSION);
    ret = LoadSecurityEnhanceInfo(&preproc->inParams, preproc->smcCmd, preproc->tcToken,
        preproc->mbPack, preproc->global, preproc->IsTokenWork);
    if (ret != EOK) {
        tloge("LoadSecurityEnhanceInfo failed.\n");
        goto ERROR;
    }
#endif
    return ret;
ERROR:
    ProcErrorSituation(&preproc->inParams, preproc->mbPack, preproc->smcCmd, 0, preproc->operationInit);
    return ret;
}

static int TcClientCallFail(TcNsClientContext *clientContext, int teeRetFirst,
    TcNsDevFile *devFile, TcNsSession *session, struct TcClientCallPreprocStruct *preproc)
{
    int teeRet = teeRetFirst;
    int ret = 0;
#ifdef TC_ASYNC_NOTIFY_SUPPORT
    while (teeRet == TEEC_PENDING) {
        PendCaThread(session, preproc->smcCmd);
#ifdef SECURITY_AUTH_ENHANCE
        if (preproc->IsTokenWork) {
            ret = AppendTeecToken(clientContext, preproc->tcToken, devFile, preproc->global,
                preproc->mbPack->token, sizeof(preproc->mbPack->token));
            if (ret != EOK) {
                tloge("append teec's member failed. global=%d, cmdId=%u, sessionId=%u\n",
                      preproc->global, preproc->smcCmd->cmdId, preproc->smcCmd->contextId);
                goto ERROR;
            }
        }
#endif
        teeRet = TcNsSmcWithNoNr(preproc->smcCmd);
#ifdef SECURITY_AUTH_ENHANCE
        if (preproc->IsTokenWork) {
            ret = PostProcessToken(preproc->smcCmd, clientContext, preproc->tcToken, preproc->mbPack->token,
                sizeof(preproc->mbPack->token), devFile->kernelApi, preproc->global);
            if (ret != EOK) {
                tloge("NO NR, PostProcessToken failed.\n");
                goto ERROR;
            }
        }
#endif
    }
#endif
    /* Client was interrupted, return and let it handle it's own signals first then retry */
    if (teeRet == TEEC_CLIENT_INTR) {
        ret = -ERESTARTSYS;
        goto ERROR;
    } else if (teeRet) {
        tloge("smc_call returns error ret 0x%x\n", teeRet);
        tloge("smc_call smc cmd ret 0x%x\n", preproc->smcCmd->retVal);
        goto SHORT_BUFFER;
    }
    clientContext->sessionId = preproc->smcCmd->contextId;
    return ret;

SHORT_BUFFER:
    if (teeRet == TEEC_ERROR_SHORT_BUFFER) {
        ProcShortBufferSituation(&preproc->inParams, &preproc->mbPack->operation,
            preproc->smcCmd, preproc->operationInit);
    }
    ret = EFAULT;
ERROR:
    ProcErrorSituation(&preproc->inParams, preproc->mbPack, preproc->smcCmd, teeRet, preproc->operationInit);
    return ret;
}

int TcClientCall(TcNsClientContext *clientContext,
    TcNsDevFile *devFile, TcNsSession *session, uint8_t flags)
{
    struct TcClientCallPreprocStruct preproc;
    if (memset_s(&preproc, sizeof(preproc), 0, sizeof(preproc)) != EOK) {
        return -ENOMEM;
    }

    int ret = TcClientCallPreprocess(clientContext, devFile, session, flags, &preproc);
    if (ret) {
        return ret;
    }

    /* send smc to secure world */
    int teeRet = TcNsSmc(preproc.smcCmd);

    ResetSessionId(clientContext, preproc.global, preproc.smcCmd, teeRet);
#ifdef SECURITY_AUTH_ENHANCE
    if (preproc.IsTokenWork) {
        ret = PostProcessToken(preproc.smcCmd, clientContext, preproc.tcToken,
            preproc.mbPack->token, sizeof(preproc.mbPack->token), devFile->kernelApi, preproc.global);
        if (ret != EOK) {
            tloge("PostProcessToken failed.\n");
            preproc.smcCmd->errOrigin = TEEC_ORIGIN_COMMS;
            goto ERROR;
        }
    }
#endif

    if (teeRet != 0) {
        ret = TcClientCallFail(clientContext, teeRet, devFile, session, &preproc);
        if (ret != EOK) {
            return ret;
        }
    }
    /* wake_up tee log reader */
    if (preproc.operationInit) {
        ret = UpdateClientOperation(&preproc.inParams, &preproc.mbPack->operation, true);
        if (ret) {
            preproc.smcCmd->errOrigin = TEEC_ORIGIN_COMMS;
            goto ERROR;
        }
    }
    ret = 0;
ERROR:
    ProcErrorSituation(&preproc.inParams, preproc.mbPack, preproc.smcCmd, teeRet, preproc.operationInit);
    return ret;
}

#ifdef SECURITY_AUTH_ENHANCE
static bool IsOpenSessionByIndex(uint8_t flags, uint32_t cmdId,
    int index)
{
    /* params[2] for apk cert or native ca uid;
     * params[3] for pkg name; therefore we set i>= 2
     */
    bool global = flags & TC_CALL_GLOBAL;
    bool login_en = (global && (index >= TEE_PARAM_THREE) &&
        (cmdId == GLOBAL_CMD_ID_OPEN_SESSION));
    return login_en;
}

static bool IsValidSize(uint32_t bufferSize, uint32_t tempSize)
{
    bool overFlow = false;

    if (bufferSize > AES_LOGIN_MAXLEN) {
        tloge("SECURITY_AUTH_ENHANCE: bufferSize is not right\n");
        return false;
    }
    overFlow = (tempSize > ROUND_UP(bufferSize, SZ_4K)) ? true : false;
    if (overFlow) {
        tloge("SECURITY_AUTH_ENHANCE: input data exceeds limit\n");
        return false;
    }
    return true;
}
static int CheckParamForEncryption(uint8_t *buffer,
    uint32_t bufferSize, uint8_t **plaintext,
    uint32_t *plainTextBufferSize)
{
    if (buffer == NULL || bufferSize == 0) {
        tloge("bad params before encryption!\n");
        return -EINVAL;
    }
    *plainTextBufferSize = bufferSize;
    *plaintext = calloc(1, *plainTextBufferSize);
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)(*plaintext))) {
        tloge("malloc plaintext failed\n");
        return -ENOMEM;
    }
    if (memcpy_s(*plaintext, *plainTextBufferSize,
        buffer, bufferSize)) {
        tloge("memcpy failed\n");
        free(*plaintext);
        *plaintext = NULL;
        return -EINVAL;
    }
    return 0;
}

static int HandleEnd(uint8_t *plaintext, uint8_t *cryptotext, int ret)
{
    free(plaintext);
    if (cryptotext != NULL) {
        free((void *)cryptotext);
    }
    return ret;
}

static int GetTotalAndCheck(uint32_t *plaintextSize,
    uint32_t payloadSize, uint32_t bufferSize,
    uint32_t *plaintextAlignedSize, uint32_t *totalSize)
{
    int ret = 0;
    /* Payload + Head + Padding */
    *plaintextSize = payloadSize + sizeof(struct EncryptionHead);
    *plaintextAlignedSize =
        ROUND_UP(*plaintextSize, CIPHER_BLOCK_BYTESIZE);
    /* Need 16 bytes to store AES-CBC iv */
    *totalSize = *plaintextAlignedSize + IV_BYTESIZE;
    if (*totalSize > bufferSize) {
        tloge("Do encryption buffer is not enough!\n");
        ret = -ENOMEM;
    }
    return ret;
}

static int DoEncryption(uint8_t *buffer, uint32_t bufferSize,
    uint32_t payloadSize, const uint8_t *key)
{
    uint32_t plaintextSize;
    uint32_t plaintextAlignedSize;
    uint32_t totalSize;
    uint8_t *cryptotext = NULL;
    uint8_t *plaintext = NULL;
    uint32_t plainTextBufferSize;
    struct EncryptionHead head;
    int ret = CheckParamForEncryption(buffer, bufferSize, &plaintext, &plainTextBufferSize);
    if (ret != 0) {
        return ret;
    }

    ret = GetTotalAndCheck(&plaintextSize, payloadSize, bufferSize, &plaintextAlignedSize, &totalSize);
    if (ret != 0) {
        goto END;
    }
    cryptotext = calloc(1, totalSize);
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)cryptotext)) {
        tloge("Malloc failed when doing encryption!\n");
        ret = -ENOMEM;
        goto END;
    }
    /* Setting encryption head */
    ret = SetEncryptionHead(&head, payloadSize);
    if (ret) {
        tloge("Set encryption head failed, ret = %d.\n", ret);
        goto END;
    }
    ret = memcpy_s((void *)(plaintext + payloadSize), plainTextBufferSize - payloadSize, (void *)&head, sizeof(head));
    if (ret) {
        tloge("Copy encryption head failed, ret = %d.\n", ret);
        goto END;
    }
    /* Setting padding data */
    ret = CryptoAescbcCmsPadding(plaintext, plaintextAlignedSize, plaintextSize);
    if (ret) {
        tloge("Set encryption padding data failed, ret = %d.\n", ret);
        goto END;
    }
    ret = CryptoSessionAescbcKey256(plaintext, plaintextAlignedSize, cryptotext, totalSize, key, NULL, ENCRYPT);
    if (ret) {
        tloge("Encrypt failed, ret=%d.\n", ret);
        goto END;
    }
    ret = memcpy_s((void *)buffer, bufferSize, (void *)cryptotext, totalSize);
    if (ret) {
        tloge("Copy cryptotext failed, ret=%d.\n", ret);
    }
END:
    return HandleEnd(plaintext, cryptotext, ret);
}

static int EncryptLoginInfo(uint32_t loginInfoSize,
    uint8_t *buffer, const uint8_t *key)
{
    uint32_t payloadSize;
    uint32_t plaintextSize;
    uint32_t plaintextAlignedSize;
    uint32_t totalSize;

    if (buffer == NULL) {
        tloge("Login information buffer is null!\n");
        return -EINVAL;
    }
    /* Need adding the termination null byte ('\0') to the end. */
    payloadSize = loginInfoSize + sizeof(char);

    /* Payload + Head + Padding */
    plaintextSize = payloadSize + sizeof(struct EncryptionHead);
    plaintextAlignedSize = ROUND_UP(plaintextSize, CIPHER_BLOCK_BYTESIZE);
    /* Need 16 bytes to store AES-CBC iv */
    totalSize = plaintextAlignedSize + IV_BYTESIZE;
    if (!IsValidSize(loginInfoSize, totalSize)) {
        tloge("Login information encryption size is invalid!\n");
        return -EFAULT;
    }
    return DoEncryption(buffer, totalSize, payloadSize, key);
}
#endif
