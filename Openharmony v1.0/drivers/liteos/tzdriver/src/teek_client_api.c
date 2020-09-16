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

#include "teek_client_api.h"
#include <securec.h>
#include "tc_ns_log.h"
#include "tzdriver_compat.h"

static void EncdeForPartMem(TcNsClientContext *cliContext,
    const TeecOperation *operation, uint32_t paramCnt, uint32_t *paramType)
{
    uint32_t diff = (uint32_t)TEEC_MEMREF_PARTIAL_INPUT -
        (uint32_t)TEEC_MEMREF_TEMP_INPUT;

    if (paramCnt < TEE_PARAM_NUM) {
        /* buffer offset len */
        if (paramType[paramCnt] == TEEC_MEMREF_WHOLE) {
            cliContext->params[paramCnt].memref.offset = 0;
            cliContext->params[paramCnt].memref.sizeAddr =
                (uint64_t)(uintptr_t)&operation->params[paramCnt].memref.parent->size;
        } else {
            cliContext->params[paramCnt].memref.offset =
                operation->params[paramCnt].memref.offset;
            cliContext->params[paramCnt].memref.sizeAddr =
                (uint64_t)(uintptr_t)&operation->params[paramCnt].memref.size;
        }
        if (operation->params[paramCnt].memref.parent->isAllocated) {
            cliContext->params[paramCnt].memref.buffer =
                (uint64_t)(uintptr_t)
                operation->params[paramCnt].memref.parent->buffer;
        } else {
            cliContext->params[paramCnt].memref.buffer =
                (uint64_t)(uintptr_t)
                operation->params[paramCnt].memref.parent->buffer +
                operation->params[paramCnt].memref.offset;
            cliContext->params[paramCnt].memref.offset = 0;
        }
        /* translate the paramType to know the driver */
        if (paramType[paramCnt] == TEEC_MEMREF_WHOLE) {
            switch (operation->params[paramCnt].memref.parent->flags) {
                case TEEC_MEM_INPUT:
                    paramType[paramCnt] = TEEC_MEMREF_PARTIAL_INPUT;
                    break;
                case TEEC_MEM_OUTPUT:
                    paramType[paramCnt] = TEEC_MEMREF_PARTIAL_OUTPUT;
                    break;
                case TEEC_MEM_INOUT:
                    paramType[paramCnt] = TEEC_MEMREF_PARTIAL_INOUT;
                    break;
                default:
                    paramType[paramCnt] = TEEC_MEMREF_PARTIAL_INOUT;
                    break;
            }
        }
        /* if is not allocated, translate TEEC_MEMREF_PARTIAL_XXX to TEEC_MEMREF_TEMP_XXX */
        if (!operation->params[paramCnt].memref.parent->isAllocated) {
            paramType[paramCnt] = paramType[paramCnt] - diff;
        }
    }
    return;
}

static TeecResult ProcTeekEncode(TcNsClientContext *cliContext,
    const TeecOperation *operation)
{
    bool checkValue = false;
    bool checkTempMem = false;
    bool checkPartMem = false;
    uint32_t paramType[TEE_PARAM_NUM];
    uint32_t paramCnt;

    paramType[TEE_PARAM_ONE] =
        TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_ONE);
    paramType[TEE_PARAM_TWO] =
        TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_TWO);
    paramType[TEE_PARAM_THREE] =
        TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_THREE);
    paramType[TEE_PARAM_FOUR] =
        TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_FOUR);
    for (paramCnt = 0; paramCnt < TEE_PARAM_NUM; paramCnt++) {
        checkTempMem = paramType[paramCnt] == TEEC_MEMREF_TEMP_INPUT ||
            paramType[paramCnt] == TEEC_MEMREF_TEMP_OUTPUT ||
            paramType[paramCnt] == TEEC_MEMREF_TEMP_INOUT;
        checkPartMem = paramType[paramCnt] == TEEC_MEMREF_WHOLE ||
            paramType[paramCnt] == TEEC_MEMREF_PARTIAL_INPUT ||
            paramType[paramCnt] == TEEC_MEMREF_PARTIAL_OUTPUT ||
            paramType[paramCnt] == TEEC_MEMREF_PARTIAL_INOUT;
        checkValue = paramType[paramCnt] == TEEC_VALUE_INPUT ||
            paramType[paramCnt] == TEEC_VALUE_OUTPUT ||
            paramType[paramCnt] == TEEC_VALUE_INOUT;
        if (checkTempMem == true) {
            cliContext->params[paramCnt].memref.buffer =
                (uint64_t)(uintptr_t)(operation->params[paramCnt].tmpref.buffer);
            cliContext->params[paramCnt].memref.sizeAddr =
                (uint64_t)(uintptr_t)(&operation->params[paramCnt].tmpref.size);
        } else if (checkPartMem == true) {
            EncdeForPartMem(cliContext, operation,
                paramCnt, paramType);
        } else if (checkValue == true) {
            cliContext->params[paramCnt].value.aAddr =
                (uint64_t)(uintptr_t)(&operation->params[paramCnt].value.a);
            cliContext->params[paramCnt].value.bAddr =
                (uint64_t)(uintptr_t)(&operation->params[paramCnt].value.b);
        } else if (paramType[paramCnt] == TEEC_NONE) {
            /* do nothing */
        } else {
            tloge("paramType[%u]=%u not correct\n", paramCnt,
                paramType[paramCnt]);
            return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
        }
    }
    cliContext->paramTypes = TEEC_PARAM_TYPES(paramType[TEE_PARAM_ONE],
        paramType[TEE_PARAM_TWO], paramType[TEE_PARAM_THREE],
        paramType[TEE_PARAM_FOUR]);
    return TEEC_SUCCESS;
}

struct TeekEncodeMeg {
    TeecUuid serviceId;
    uint32_t sessionId;
    uint32_t cmdId;
};

static TeecResult TeekEncode(TcNsClientContext *cliContext,
    struct TeekEncodeMeg *msg,
    const TcNsClientLogin *cliLogin, const TeecOperation *operation)
{
    TeecResult ret;
    errno_t sret;

    if (cliContext == NULL || cliLogin == NULL) {
        tloge("cliContext or cliLogin is null.\n");
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    }
    sret = memset_s(cliContext, sizeof(*cliContext),
        0x00, sizeof(*cliContext));
    if (sret != EOK) {
        tloge("memset error sret is %d.\n", sret);
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    }
    sret = memcpy_s(cliContext->uuid, sizeof(cliContext->uuid),
        (uint8_t *)&msg->serviceId, sizeof(msg->serviceId));
    if (sret != EOK) {
        tloge("memcpy error sret is %d.\n", sret);
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    }
    cliContext->sessionId = msg->sessionId;
    cliContext->cmdId = msg->cmdId;
    cliContext->returns.code = 0;
    cliContext->returns.origin = 0;
    cliContext->login.method = cliLogin->method;
    cliContext->login.mdata = cliLogin->mdata;
    /* support when operation is null */
    if (operation == NULL) {
        return TEEC_SUCCESS;
    }
    cliContext->started = operation->cancelFlag;
    ret = ProcTeekEncode(cliContext, operation);
    tlogv("cli param type %u\n", cliContext->paramTypes);
    return ret;
}

static TeecResult TeekCheckTmpRef(TeecTempmemoryReference tmpref)
{
    TeecResult ret;
    bool checkValue = (tmpref.buffer == NULL) || (tmpref.size == 0);

    if (checkValue == true) {
        tloge("tmpref buffer is null, or size is zero\n");
        ret = (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
    } else {
        ret = (TeecResult) TEEC_SUCCESS;
    }
    return ret;
}

static TeecResult TeekCheckMemRef(TeecRegisteredmemoryReference memref,
    uint32_t paramType)
{
    bool checkValue = (memref.parent == NULL) || (memref.parent->buffer == NULL);
    bool checkOffset = false;

    if (checkValue == true) {
        tloge("parent of memref is null, or the buffer is zero\n");
        return (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
    }
    if (paramType == TEEC_MEMREF_PARTIAL_INPUT) {
        if (!(memref.parent->flags & TEEC_MEM_INPUT)) {
            return (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
        }
    } else if (paramType == TEEC_MEMREF_PARTIAL_OUTPUT) {
        if (!(memref.parent->flags & TEEC_MEM_OUTPUT)) {
            return (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
        }
    } else if (paramType == TEEC_MEMREF_PARTIAL_INOUT) {
        if (!(memref.parent->flags & TEEC_MEM_INPUT)) {
            return (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
        }
        if (!(memref.parent->flags & TEEC_MEM_OUTPUT)) {
            return (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
        }
    } else if (paramType == TEEC_MEMREF_WHOLE) {
        /* if type is TEEC_MEMREF_WHOLE, ignore it */
    } else {
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    }

    checkValue = (paramType == TEEC_MEMREF_PARTIAL_INPUT) ||
        (paramType == TEEC_MEMREF_PARTIAL_OUTPUT) ||
        (paramType == TEEC_MEMREF_PARTIAL_INOUT);
    if (checkValue == true) {
        checkOffset = (memref.offset + memref.size) > memref.parent->size ||
            (memref.offset + memref.size) < memref.offset ||
            (memref.offset + memref.size) < memref.size;
        if (checkOffset == true) {
            tloge("offset + size exceed the parent size\n");
            return (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
        }
    }
    return (TeecResult) TEEC_SUCCESS;
}

/*
 * This function checks a operation is valid or not.
 */
TeecResult TeekCheckOperation(const TeecOperation *operation)
{
    uint32_t paramType[TEE_PARAM_NUM] = {0};
    uint32_t paramCnt;
    TeecResult ret = TEEC_SUCCESS;
    bool checkValue = false;
    bool checkTempMem = false;
    bool checkPartMem = false;

    /* GP Support operation is NULL
     * operation: a pointer to a Client Application initialized TeecOperation structure,
     * or NULL if there is no payload to send or if the Command does not need to support
     * cancellation.
     */
    if (operation == NULL) {
        return (TeecResult)TEEC_SUCCESS;
    }
    if (!operation->started) {
        tloge("sorry, cancellation not support\n");
        return (TeecResult) TEEC_ERROR_NOT_IMPLEMENTED;
    }
    paramType[TEE_PARAM_ONE] = TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_ONE);
    paramType[TEE_PARAM_TWO] = TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_TWO);
    paramType[TEE_PARAM_THREE] = TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_THREE);
    paramType[TEE_PARAM_FOUR] = TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_FOUR);
    for (paramCnt = 0; paramCnt < TEE_PARAM_NUM; paramCnt++) {
        checkTempMem = paramType[paramCnt] == TEEC_MEMREF_TEMP_INPUT ||
            paramType[paramCnt] == TEEC_MEMREF_TEMP_OUTPUT || paramType[paramCnt] == TEEC_MEMREF_TEMP_INOUT;
        checkPartMem = paramType[paramCnt] == TEEC_MEMREF_WHOLE ||
            paramType[paramCnt] == TEEC_MEMREF_PARTIAL_INPUT ||
            paramType[paramCnt] == TEEC_MEMREF_PARTIAL_OUTPUT ||
            paramType[paramCnt] == TEEC_MEMREF_PARTIAL_INOUT;
        checkValue = paramType[paramCnt] == TEEC_VALUE_INPUT ||
            paramType[paramCnt] == TEEC_VALUE_OUTPUT || paramType[paramCnt] == TEEC_VALUE_INOUT;
        if (checkTempMem == true) {
            ret = TeekCheckTmpRef(operation->params[paramCnt].tmpref);
            if (ret != TEEC_SUCCESS) {
                break;
            }
        } else if (checkPartMem == true) {
            ret = TeekCheckMemRef(operation->params[paramCnt].memref, paramType[paramCnt]);
            if (ret != TEEC_SUCCESS) {
                break;
            }
        } else if (checkValue == true) {
            /* if type is value, ignore it */
        } else if (paramType[paramCnt] == TEEC_NONE) {
            /* if type is none, ignore it */
        } else {
            tloge("paramType[%u]=%x is not support\n", paramCnt, paramType[paramCnt]);
            ret = (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
            break;
        }
    }
    return ret;
}

/*
 * This function check if the special agent is launched.Used For HDCP key.
 * e.g. If sfs agent is not alive, you can not do HDCP key write to SRAM.
 */
int TeekIsAgentAlive(unsigned int agentId)
{
    return IsAgentAlive(agentId);
}

/*
 * This function initializes a new TEE Context, forming a connection between this Client Application
 * and the TEE identified by the string identifier name.
 */
TeecResult TeekInitializeContext(const char *name, TeecContext *context)
{
    int32_t ret;

    /* name current not used */
    (void)(name);
    tlogd("TeekInitializeContext Started:\n");
    /* First, check parameters is valid or not */
    if (context == NULL) {
        tloge("context is null, not correct\n");
        return (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
    }
    context->dev = NULL;
    /* Paramters right, start execution */
    ret = TcNsClientOpen((TcNsDevFile **)&context->dev,
        TEE_REQ_FROM_KERNEL_MODE);
    if (ret != TEEC_SUCCESS) {
        tloge("open device failed\n");
        return (TeecResult) TEEC_ERROR_GENERIC;
    }
    tlogd("open device success\n");
    TEEK_INIT_LIST_HEAD(&context->sessionList);
    TEEK_INIT_LIST_HEAD(&context->shrdMemList);
    return TEEC_SUCCESS;
}

/*
 * This function finalizes an initialized TEE Context.
 */
void TeekFinalizeContext(TeecContext *context)
{
    struct ListNode *ptr = NULL;
    TeecSession *session = NULL;
    /* TeecSharedMemory* shrdmem */
    tlogd("TeekFinalizeContext started\n");
    /* First, check parameters is valid or not */
    if (context == NULL || context->dev == NULL) {
        tloge("context or dev is null, not correct\n");
        return;
    }
    /* Paramters right, start execution */
    if (!LIST_EMPTY(&context->sessionList)) {
        tlogi("context still has sessions opened, close it\n");
        LIST_FOR_EACH(ptr, &context->sessionList) {
            session = list_entry(ptr, TeecSession, head);
            TeekCloseSession(session);
        }
    }
    tlogd("close device\n");
    TcNsClientClose(context->dev);
    context->dev = NULL;
}

static TeecResult CheckParamsForOpenSession(TeecContext *context,
    const TeecOperation *operation, TcNsClientLogin *cliLogin)
{
    bool checkValue = false;
    TcNsDevFile *devFile = NULL;
    TeecResult teecRet;
    errno_t sret;
    uint32_t paramType[TEE_PARAM_NUM] = {0};

    paramType[TEE_PARAM_FOUR] = TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_FOUR);
    paramType[TEE_PARAM_THREE] = TEEC_PARAM_TYPE_GET(operation->paramTypes, TEE_PARAM_THREE);
    checkValue = paramType[TEE_PARAM_FOUR] != TEEC_MEMREF_TEMP_INPUT ||
        paramType[TEE_PARAM_THREE] != TEEC_MEMREF_TEMP_INPUT;
    if (checkValue == true) {
        tloge("invalid param type 0x%x\n", operation->paramTypes);
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    }
    checkValue = operation->params[TEE_PARAM_FOUR].tmpref.buffer == NULL ||
        operation->params[TEE_PARAM_THREE].tmpref.buffer == NULL ||
        operation->params[TEE_PARAM_FOUR].tmpref.size == 0 || operation->params[TEE_PARAM_THREE].tmpref.size == 0;
    if (checkValue == true) {
        tloge("invalid operation params(NULL)\n");
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    }
    cliLogin->method = TEEC_LOGIN_IDENTIFY;
    devFile = (TcNsDevFile *)(context->dev);
    if (devFile == NULL) {
        tloge("invalid context->dev (NULL)\n");
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    }
    devFile->pkgNameLen = operation->params[TEE_PARAM_FOUR].tmpref.size;
    if (operation->params[TEE_PARAM_FOUR].tmpref.size > (MAX_PACKAGE_NAME_LEN - 1)) {
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    } else {
        sret = memset_s(devFile->PkgName, sizeof(devFile->PkgName), 0, MAX_PACKAGE_NAME_LEN);
        if (sret != EOK) {
            tloge("memset error sret is %d.\n", sret);
            return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
        }
        sret = memcpy_s(devFile->PkgName, sizeof(devFile->PkgName), operation->params[TEE_PARAM_FOUR].tmpref.buffer,
            operation->params[TEE_PARAM_FOUR].tmpref.size);
        if (sret != EOK) {
            tloge("memcpy error sret is %d.\n", sret);
            return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
        }
    }
    devFile->pubKeyLen = 0;
    devFile->loginSetup = 1;
    teecRet = TeekCheckOperation(operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("operation is invalid\n");
        return (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
    }
    return teecRet;
}

static TeecResult OpenSessionAndSwitchRet(TeecSession *session,
    TeecContext *context, const TeecUuid *destination,
    TcNsClientContext *cliContext, uint32_t *origin)
{
    int32_t ret;
    TeecResult teecRet;

    ret = TcNsOpenSession(context->dev, cliContext);
    if (ret == 0) {
        tlogd("open session success\n");
        session->sessionId = cliContext->sessionId;
        session->serviceId = *destination;
        session->opsCnt = 0;
        TEEK_INIT_LIST_HEAD(&session->head);
        ListInsertTail(&context->sessionList, &session->head);
        session->context = context;
        return TEEC_SUCCESS;
    } else if (ret < 0) {
        tloge("open session failed, ioctl errno = %u\n", ret);
        if (ret == -EFAULT) {
            teecRet = (TeecResult) TEEC_ERROR_ACCESS_DENIED;
        } else if (ret == -ENOMEM) {
            teecRet = (TeecResult) TEEC_ERROR_OUT_OF_MEMORY;
        } else if (ret == -EINVAL) {
            teecRet = (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
        } else if (ret == -ERESTARTSYS) {
            teecRet = (TeecResult) TEEC_CLIENT_INTR;
        } else {
            teecRet = (TeecResult) TEEC_ERROR_GENERIC;
        }
        *origin = TEEC_ORIGIN_COMMS;
        return teecRet;
    } else {
        tloge("open session failed, code=0x%x, origin=%u\n", cliContext->returns.code,
              cliContext->returns.origin);
        teecRet = (TeecResult)cliContext->returns.code;
        *origin = cliContext->returns.origin;
    }
    return teecRet;
}

/*
 * Function:       TEEC_OpenSession
 * Description:   This function opens a new Session
 * Parameters:   context: a pointer to an initialized TEE Context.
 * session: a pointer to a Session structure to open.
 * destination: a pointer to a UUID structure.
 * connectionMethod: the method of connection to use.
 * connectionData: any necessary data required to support the connection method chosen.
 * operation: a pointer to an Operation containing a set of Parameters.
 * returnOrigin: a pointer to a variable which will contain the return origin.
 * Return: TEEC_SUCCESS: success other: failure
 */
static TeecResult ProcTeekOpenSession(TeecContext *context,
    TeecSession *session, const TeecUuid *destination,
    uint32_t connectionMethod, const void *connectionData,
    const TeecOperation *operation, uint32_t *returnOrigin)
{
    TeecResult teecRet;
    uint32_t origin = TEEC_ORIGIN_API;
    TcNsClientContext cliContext;
    TcNsClientLogin cliLogin = { 0, 0 };
    bool checkValue = false;

    tlogd("TeekOpenSession Started:\n");
    /* connectionData current not used */
    (void)(connectionData);
    /* returnOrigin maybe null, so only when it is valid, we set
     * origin(error come from which module)
     */
    if (returnOrigin != NULL) {
        *returnOrigin = origin;
    }
    /* First, check parameters is valid or not */
    checkValue = (context == NULL || operation == NULL ||
        connectionMethod != TEEC_LOGIN_IDENTIFY);
    if (checkValue == true || destination == NULL || session == NULL) {
        tloge("invalid input params\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    teecRet = CheckParamsForOpenSession(context, operation, &cliLogin);
    if (teecRet != TEEC_SUCCESS) {
        goto RET_FAIL;
    }
    /* Paramters right, start execution
     * note:before open session success,
     * we should send session=0 as initial state.
     */
    struct TeekEncodeMeg msg = {
        *destination, 0, GLOBAL_CMD_ID_OPEN_SESSION
    };
    teecRet = TeekEncode(&cliContext, &msg, &cliLogin, operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("encode failed\n");
        goto RET_FAIL;
    }
#ifdef SECURITY_AUTH_ENHANCE
    cliContext.teecToken = session->teecToken;
    cliContext.tokenLen = sizeof(session->teecToken);
#endif
    teecRet = OpenSessionAndSwitchRet(session, context,
        destination, &cliContext, &origin);
    /* ONLY when ioctl returnCode!=0 and returnOrigin not NULL, set returnOrigin */
    if (teecRet != TEEC_SUCCESS && returnOrigin != NULL) {
        *returnOrigin = origin;
    }
RET_FAIL:
    return teecRet;
}

#define RETRY_TIMES 5
TeecResult TeekOpenSession(TeecContext *context,
    TeecSession *session, const TeecUuid *destination,
    uint32_t connectionMethod, const void *connectionData,
    const TeecOperation *operation, uint32_t *returnOrigin)
{
    int i;
    TeecResult ret;

    for (i = 0; i < RETRY_TIMES; i++) {
        ret = ProcTeekOpenSession(context, session,
            destination, connectionMethod, connectionData,
            operation, returnOrigin);
        if (ret != (TeecResult)TEEC_CLIENT_INTR) {
            return ret;
        }
    }
    return ret;
}

static int CheckCloseSessionParam(TeecSession *session)
{
    bool checkValue = false;
    bool found = false;
    TeecSession *tempSess = NULL;
    struct ListNode *ptr = NULL;

    /* First, check parameters is valid or not */
    checkValue = session == NULL || session->context == NULL;
    if (checkValue || session->context->dev == NULL) {
        tloge("input invalid session or session->context is null\n");
        return -1;
    }
    LIST_FOR_EACH(ptr, &session->context->sessionList) {
        tempSess = list_entry(ptr, TeecSession, head);
        if (tempSess == session) {
            found = true;
            break;
        }
    }
    if (!found) {
        tloge("session is not in the context list\n");
        return -1;
    }
    return 0;
}

/*
 * This function closes an opened Session.
 */
void TeekCloseSession(TeecSession *session)
{
    int32_t ret;
    TcNsClientContext cliContext;
    TcNsClientLogin cliLogin = { 0, 0 };
    errno_t sret;

    tlogd("TeekCloseSession started\n");
    ret = CheckCloseSessionParam(session);
    if (ret) {
        return;
    }
    /* Paramters all right, start execution */
    if (session->opsCnt) {
        tloge("session still has commands running\n");
    }
    struct TeekEncodeMeg msg = {
        session->serviceId, session->sessionId, GLOBAL_CMD_ID_CLOSE_SESSION
    };
    if (TeekEncode(&cliContext, &msg, &cliLogin, NULL) != TEEC_SUCCESS) {
        tloge("encode failed, just return\n");
        return;
    }
#ifdef SECURITY_AUTH_ENHANCE
    cliContext.teecToken = session->teecToken;
    cliContext.tokenLen = sizeof(session->teecToken);
#endif
    ret = TcNsCloseSession(session->context->dev, &cliContext);
    if (ret == 0) {
        tlogd("close session success\n");
        session->sessionId = 0;
        sret = memset_s((uint8_t *)(&session->serviceId), sizeof(session->serviceId), 0x00, UUID_LEN);
        /* TeekCloseSession is void so go on execute */
        if (sret != EOK) {
            tloge("memset error sret is %d.\n", sret);
        }
#ifdef SECURITY_AUTH_ENHANCE
        sret = memset_s(session->teecToken, TOKEN_SAVE_LEN, 0x00, TOKEN_SAVE_LEN);
        if (sret != EOK) {
            tloge("memset session's member error ret value is %d.\n", sret);
        }
#endif
        session->opsCnt = 0;
        ListRemove(&session->head);
        session->context = NULL;
    } else {
        tloge("close session failed\n");
    }
}

static TeecResult InvokeCmdAndSwitchRet(TeecSession *session,
    TcNsClientContext *cliContext, uint32_t *origin)
{
    int32_t ret;
    TeecResult teecRet;

    ret = TcNsSendCmd(session->context->dev, cliContext);
    if (ret == 0) {
        tlogd("invoke cmd success\n");
        teecRet = TEEC_SUCCESS;
    } else if (ret < 0) {
        tloge("invoke cmd failed, ioctl errno = %d\n", ret);
        if (ret == -EFAULT) {
            teecRet = (TeecResult)TEEC_ERROR_ACCESS_DENIED;
        } else if (ret == -ENOMEM) {
            teecRet = (TeecResult)TEEC_ERROR_OUT_OF_MEMORY;
        } else if (ret == -EINVAL) {
            teecRet = (TeecResult)TEEC_ERROR_BAD_PARAMETERS;
        } else {
            teecRet = (TeecResult)TEEC_ERROR_GENERIC;
        }
        *origin = TEEC_ORIGIN_COMMS;
    } else {
        tloge("invoke cmd failed, code=0x%x, origin=%d\n",
            cliContext->returns.code, cliContext->returns.origin);
        teecRet = (TeecResult)cliContext->returns.code;
        *origin = cliContext->returns.origin;
    }
    return teecRet;
}

/* This function invokes a Command within the specified Session. */
TeecResult TeekInvokeCommand(TeecSession *session, uint32_t commandID,
    TeecOperation *operation, uint32_t *returnOrigin)
{
    TeecResult teecRet = (TeecResult) TEEC_ERROR_BAD_PARAMETERS;
    uint32_t origin = TEEC_ORIGIN_API;
    TcNsClientContext cliContext;
    TcNsClientLogin cliLogin = { 0, 0 };

    tlogd("TeekInvokeCommand Started:\n");
    /* First, check parameters is valid or not */
    if (session == NULL || session->context == NULL) {
        tloge("input invalid session or session->context is null\n");
        if (returnOrigin != NULL) {
            *returnOrigin = origin;
        }
        return teecRet;
    }
    teecRet = TeekCheckOperation(operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("operation is invalid\n");
        if (returnOrigin != NULL) {
            *returnOrigin = origin;
        }
        return teecRet;
    }
    /* Paramters all right, start execution */
    session->opsCnt++;
    struct TeekEncodeMeg msg = {
        session->serviceId, session->sessionId, commandID
    };
    teecRet = TeekEncode(&cliContext, &msg, &cliLogin, operation);
    if (teecRet != TEEC_SUCCESS) {
        tloge("encode failed\n");
        session->opsCnt--;
        if (returnOrigin != NULL) {
            *returnOrigin = origin;
        }
        return teecRet;
    }
#ifdef SECURITY_AUTH_ENHANCE
    cliContext.teecToken = session->teecToken;
    cliContext.tokenLen = sizeof(session->teecToken);
#endif
    teecRet = InvokeCmdAndSwitchRet(session, &cliContext, &origin);
    session->opsCnt--;
    /* ONLY when ioctl returnCode!=0 and returnOrigin not NULL, set *returnOrigin */
    if ((teecRet != TEEC_SUCCESS) && (returnOrigin != NULL)) {
        *returnOrigin = origin;
    }
    return teecRet;
}

/*
 * This function registers a block of existing Client Application memory
 * as a block of Shared Memory within the scope of the specified TEE Context.
 */
TeecResult TeekRegisterSharedMemory(TeecContext *context,
    TeecSharedMemory *sharedMem)
{
    tloge("TeekRegisterSharedMemory not supported\n");
    return (TeecResult)TEEC_ERROR_NOT_SUPPORTED;
}

/*
 * This function allocates a new block of memory as a block of
 *  Shared Memory within the scope of the specified TEE Context.
 */
TeecResult TeekAllocateSharedMemory(TeecContext *context,
    TeecSharedMemory *sharedMem)
{
    tloge("TeekAllocateSharedMemory not supported\n");
    return (TeecResult)TEEC_ERROR_NOT_SUPPORTED;
}

/*
 * This function deregisters or deallocates
 * a previously initialized block of Shared Memory..
 */
void TeekReleaseSharedMemory(TeecSharedMemory *sharedMem)
{
    tloge("TeekReleaseSharedMemory not supported\n");
}

/*
 * This function requests the cancellation of a pending open Session operation or
 * a Command invocation operation.
 */
void TeekRequestCancellation(TeecOperation *operation)
{
    tloge("TeekRequestCancellation not supported\n");
}
