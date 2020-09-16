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

#include "security_auth_enhance.h"
#include <securec.h>
#include "securectype.h"
#include "tc_client_sub_driver.h"
#include "tc_ns_client.h"
#include "tc_ns_log.h"
#include "teek_client_constants.h"
#include "teek_client_type.h"
#include "tzdriver_compat.h"

#if !defined(UINT64_MAX)
    #define UINT64_MAX ((uint64_t)0xFFFFFFFFFFFFFFFFULL)
#endif

#ifdef SECURITY_AUTH_ENHANCE
#define GLOBAL_CMD_ID_SSA               0x2DCB /* SSA cmdId 11723 */
#define GLOBAL_CMD_ID_MT                0x2DCC /* MT cmdId 11724 */
#define GLOBAL_CMD_ID_MT_UPDATE         0x2DCD /* MT_IPDATE cmdId 11725 */
#define TEEC_PENDING2_AGENT             0xFFFF2001

static bool IsTokenEmpty(const uint8_t *token, uint32_t tokenLen)
{
    uint32_t i;

    if (token == NULL) {
        tloge("bad parameters, token is null\n");
        return true;
    }
    for (i = 0; i < tokenLen; i++) {
        if (*(token + i)) {
            return false;
        }
    }
    return true;
}

static TeecResult ScramblingTimestamp(const void *in, void *out,
    uint32_t dataLen, const void *key, uint32_t keyLen)
{
    uint32_t i;
    bool checkValue = false;

    if (in == NULL || out == NULL || key == NULL) {
        tloge("bad parameters, input_data is null\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    checkValue = (dataLen == 0 || dataLen > SECUREC_MEM_MAX_LEN ||
            keyLen > SECUREC_MEM_MAX_LEN || keyLen == 0);
    if (checkValue) {
        tloge("bad parameters, dataLen is %u, scrambling_len is %u\n",
              dataLen, keyLen);
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    for (i = 0; i < dataLen; i++) {
        *((uint8_t *)out + i) =
            *((uint8_t *)in + i) ^ *((uint8_t *)key + i % keyLen);
    }

    return TEEC_SUCCESS;
}

static int32_t ChangeTimeStamp(uint8_t flag, uint64_t *timeStamp)
{
    if (flag == INC) {
        if (*timeStamp < UINT64_MAX) {
            (*timeStamp)++;
        } else {
            tloge("val overflow\n");
            return -EFAULT;
        }
    } else if (flag == DEC) {
        if (*timeStamp > 0) {
            (*timeStamp)--;
        } else {
            tloge("val down overflow\n");
            return -EFAULT;
        }
    } else {
        tloge("flag error , 0x%x\n", flag);
        return -EFAULT;
    }
    return EOK;
}

static int32_t DescramblingTimestamp(uint8_t *inTokenBuf,
    const struct SessionSecureInfo *secureInfo, uint8_t flag)
{
    uint64_t timeStamp = 0;
    int32_t ret;

    if (inTokenBuf == NULL || secureInfo == NULL) {
        tloge("invalid params!\n");
        return -EINVAL;
    }
    if (ScramblingTimestamp(&inTokenBuf[TIMESTAMP_BUFFER_INDEX],
        &timeStamp, TIMESTAMP_LEN_DEFAULT, secureInfo->scrambling, SCRAMBLING_KEY_LEN)) {
        tloge("DescramblingTimestamp failed\n");
        return -EFAULT;
    }
    ret = ChangeTimeStamp(flag, &timeStamp);
    if (ret != EOK) {
        return ret;
    }

    tlogd("timestamp is %llu\n", timeStamp);
    if (ScramblingTimestamp(&timeStamp, &inTokenBuf[TIMESTAMP_BUFFER_INDEX],
        TIMESTAMP_LEN_DEFAULT, secureInfo->scrambling, SCRAMBLING_KEY_LEN)) {
        tloge("DescramblingTimestamp failed\n");
        return -EFAULT;
    }
    return EOK;
}

TeecResult UpdateTimestamp(const TcNsSmcCmd *cmd)
{
    TcNsSession *session = NULL;
    struct SessionSecureInfo *secureInfo = NULL;
    uint8_t *tokenBuffer = NULL;
    bool filterFlag = false;
    bool needCheckFlag = false;

    if (cmd == NULL) {
        tloge("cmd is NULL, error!");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    /* if cmd is agent, not check uuid. and sometime uuid canot access it */
    filterFlag = (cmd->agentId != 0) ||
            (cmd->retVal == TEEC_PENDING2_AGENT);
    if (filterFlag) {
        return TEEC_SUCCESS;
    }

    needCheckFlag = (cmd->globalCmd == false) && (cmd->agentId == 0) &&
        (cmd->retVal != TEEC_PENDING2_AGENT);
    if (needCheckFlag) {
        tokenBuffer = (void *)LOS_PaddrToKVaddr((paddr_t)(cmd->tokenPhys));
        if (tokenBuffer == NULL ||
            IsTokenEmpty(tokenBuffer, TOKEN_BUFFER_LEN)) {
            tloge("token is NULL or token is empyt, error!\n");
            return TEEC_ERROR_GENERIC;
        }

        session = TcFindSession2(cmd->devFileId, cmd);
        if (session == NULL) {
            tlogd("tc_find_session_key find session FAILURE\n");
            return TEEC_ERROR_GENERIC;
        }
        secureInfo = &session->secureInfo;
        if (DescramblingTimestamp(tokenBuffer, secureInfo, INC) != EOK) {
            PutSessionStruct(session);
            tloge("update tokenBuffer error\n");
            return TEEC_ERROR_GENERIC;
        }
        PutSessionStruct(session);
        tokenBuffer[SYNC_INDEX] = UN_SYNCED;
    } else {
        tlogd("global cmd or agent, do not update timestamp\n");
    }
    return TEEC_SUCCESS;
}

TeecResult SyncTimestamp(const TcNsSmcCmd *cmd, uint8_t *token,
    uint32_t tokenLen, bool global)
{
    TcNsSession *session = NULL;
    bool checkVal = false;

    checkVal = (cmd == NULL || token == NULL || tokenLen <= SYNC_INDEX);
    if (checkVal) {
        tloge("parameters is NULL, error!\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    if (cmd->cmdId == GLOBAL_CMD_ID_OPEN_SESSION && global) {
        tlogd("OpenSession would not need sync timestamp\n");
        return TEEC_SUCCESS;
    }

    if (token[SYNC_INDEX] == UN_SYNCED) {
        tlogd("flag is UN_SYNC, to sync timestamp!\n");

        session = TcFindSession2(cmd->devFileId, cmd);
        if (session == NULL) {
            tloge("SyncTimestamp find session FAILURE\n");
            return TEEC_ERROR_GENERIC;
        }
        if (DescramblingTimestamp(token, &session->secureInfo, DEC) != EOK) {
            PutSessionStruct(session);
            tloge("sync tokenBuffer error\n");
            return TEEC_ERROR_GENERIC;
        }
        PutSessionStruct(session);
        return TEEC_SUCCESS;
    } else if (token[SYNC_INDEX] == IS_SYNCED) {
        return TEEC_SUCCESS;
    } else {
        tloge("sync flag error! 0x%x\n", token[SYNC_INDEX]);
    }
    return TEEC_ERROR_GENERIC;
}

/* scrambling operation and pid */
static void ScramblingOperation(TcNsSmcCmd *cmd, uint32_t scrambler)
{
    if (cmd == NULL) {
        return;
    }
    if (cmd->operationPhys != 0 || cmd->operationHphys != 0) {
        cmd->operationPhys = cmd->operationPhys ^ scrambler;
        cmd->operationHphys = cmd->operationHphys ^ scrambler;
    }
    cmd->pid = cmd->pid ^ scrambler;
}

static bool AgentMsg(uint32_t cmdId)
{
    bool agent = cmdId == GLOBAL_CMD_ID_SSA ||
        cmdId == GLOBAL_CMD_ID_MT ||
        cmdId == GLOBAL_CMD_ID_MT_UPDATE;

    return agent;
}

/* calculate cmd checksum and scrambling operation */
TeecResult UpdateChksum(TcNsSmcCmd *cmd)
{
    TcNsSession *session = NULL;
    struct SessionSecureInfo *secureInfo = NULL;
    uint32_t ScramblerOper;
    bool checkValue = false;

    if (cmd == NULL) {
        tloge("cmd is NULL, error\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    /*
     * if cmd is agent, do not check uuid.
     * and sometimes uuid cannot access it
     */
    checkValue = (cmd->agentId != 0 || cmd->retVal == TEEC_PENDING2_AGENT);
    if (checkValue == true) {
        return TEEC_SUCCESS;
    }

    if (AgentMsg(cmd->cmdId)) {
        tlogd("SSA cmd, no need to UpdateChksum\n");
        return TEEC_SUCCESS;
    }
    /* cmd is invoke command */
    checkValue = (cmd->globalCmd == false) && (cmd->agentId == 0) &&
        (cmd->retVal != TEEC_PENDING2_AGENT);

    if (checkValue) {
        session = TcFindSession2(cmd->devFileId, cmd);
        if (session != NULL) {
            secureInfo = &session->secureInfo;
            ScramblerOper =
                secureInfo->scrambling[SCRAMBLING_OPERATION];
            ScramblingOperation(cmd, ScramblerOper);
            PutSessionStruct(session);
        }
    }
    return TEEC_SUCCESS;
}

TeecResult VerifyChksum(const TcNsSmcCmd *cmd)
{
    TcNsSession *session = NULL;
    bool checkFlag = false;

    if (cmd == NULL) {
        tloge("cmd is NULL, error\n");
        return TEEC_ERROR_BAD_PARAMETERS;
    }
    if (AgentMsg(cmd->cmdId)) {
        tlogd("SSA cmd, no need to UpdateChksum\n");
        return TEEC_SUCCESS;
    }

    /* cmd is invoke command */
    checkFlag = cmd->globalCmd == false &&
            cmd->cmdId != GLOBAL_CMD_ID_CLOSE_SESSION &&
            cmd->cmdId != GLOBAL_CMD_ID_KILL_TASK &&
            cmd->agentId == 0;
    if (checkFlag) {
        session = TcFindSession2(cmd->devFileId, cmd);
        if (session) {
            PutSessionStruct(session);
        }
    }
    return TEEC_SUCCESS;
}
#endif
