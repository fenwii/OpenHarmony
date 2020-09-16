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

#include "tc_client_sub_driver.h"
#include "agent.h"
#include "gp_ops.h"
#include "mailbox_mempool.h"
#ifdef SECURITY_AUTH_ENHANCE
#include "security_auth_enhance.h"
#endif
#include "smc.h"
#include "tc_client_driver.h"
#include "tc_ns_log.h"
#include "tzdriver_compat.h"

static DEFINE_MUTEX(g_loadAppLock);

#ifdef SECURITY_AUTH_ENHANCE

typedef struct {
    TcNsDevFile *devFile;
    TcNsClientContext *context;
    TcNsSession *session;
} GetSecureInfoParams;

static int CheckRandomData(const uint8_t *data, uint32_t size)
{
    uint32_t i;

    for (i = 0; i < size; i++) {
        if (data[i] != 0) {
            break;
        }
    }
    if (i >= size) {
        return -1;
    }
    return 0;
}

int GenerateRandomData(uint8_t *data, uint32_t size)
{
    if (data == NULL || size == 0) {
        tloge("Bad parameters!\n");
        return -EFAULT;
    }
    if (memset_s((void *)data, size, 0, size)) {
        tloge("Clean the data buffer failed!\n");
        return -EFAULT;
    }
    GetRandomBytesArch((void *)data, size);
    if (CheckRandomData(data, size) != 0) {
        return -EFAULT;
    }
    return 0;
}

bool IsValidEncryptionHead(const struct EncryptionHead *head,
    const uint8_t *data, uint32_t len)
{
    if (head == NULL || data == NULL || len == 0) {
        tloge("In parameters check failed.\n");
        return false;
    }

    if (strncmp((const char *)head->magic, MAGIC_STRING, sizeof(MAGIC_STRING))) {
        tloge("Magic string is invalid.\n");
        return false;
    }

    if (head->payloadLen != len) {
        tloge("Payload length is invalid.\n");
        return false;
    }
    return true;
}

int GenerateChallengeWord(uint8_t *challengeWord, uint32_t size)
{
    if (challengeWord == NULL) {
        tloge("Parameter is null pointer!\n");
        return -EINVAL;
    }
    return GenerateRandomData(challengeWord, size);
}

int SetEncryptionHead(struct EncryptionHead *head,
    uint32_t len)
{
    if (head == NULL || len == 0) {
        tloge("In parameters check failed.\n");
        return -EINVAL;
    }
    if (strncpy_s((char *)head->magic, sizeof(head->magic),
        MAGIC_STRING, strlen(MAGIC_STRING) + 1)) {
        tloge("Copy magic string failed.\n");
        return -EFAULT;
    }
    head->payloadLen = len;
    return 0;
}

static TcNsDevFile *TcFindDevFile(unsigned int devFileId)
{
    TcNsDevFile *devFile = NULL;

    list_for_each_entry(devFile, &GetTcNsDevList()->devFileList, head) {
        if (devFile->devFileId == devFileId) {
            return devFile;
        }
    }
    return NULL;
}

TcNsSession *TcFindSession2(unsigned int devFileId,
    const TcNsSmcCmd *cmd)
{
    TcNsDevFile *devFile = NULL;
    TcNsService *service = NULL;
    TcNsSession *session = NULL;

    if (cmd == NULL) {
        tloge("Parameter is null pointer!\n");
        return NULL;
    }
    mutex_lock(&GetTcNsDevList()->devLock);
    devFile = TcFindDevFile(devFileId);
    mutex_unlock(&GetTcNsDevList()->devLock);
    if (devFile == NULL) {
        tloge("Can't find dev file! devFileId %d\n", devFileId);
        return NULL;
    }
    mutex_lock(&devFile->serviceLock);
    service = TcFindServiceInDev(devFile, cmd->uuid, UUID_LEN);
    GetServiceStruct(service);
    mutex_unlock(&devFile->serviceLock);
    if (service == NULL) {
        tloge(" Can't find service!\n");
        return NULL;
    }
    mutex_lock(&service->SessionLock);
    session = TcFindSessionWithOwner(&service->sessionList,
        cmd->contextId, devFile);
    GetSessionStruct(session);
    mutex_unlock(&service->SessionLock);
    PutServiceStruct(service);
    if (session == NULL) {
        tloge("can't find session[0x%x]!\n", cmd->contextId);
        return NULL;
    }
    return session;
}

static inline uint32_t AlginUp(uint32_t x, uint32_t align)
{
    return (x + align - 1) & ~(align - 1);
}

void CleanSessionSecureInformation(TcNsSession *session)
{
    if (session != NULL) {
        if (memset_s((void *)&session->secureInfo,
            sizeof(session->secureInfo), 0, sizeof(session->secureInfo)))
            tloge("Clean this session secure information failed!\n");
    }
}

static int AllocSecureParams(uint32_t secureParamsAlignedSize,
    uint32_t paramsSize, struct SessionSecureParams **reeSecureParams,
    struct SessionSecureParams **teeSecureParams)
{
    if (secureParamsAlignedSize == 0) {
        tloge("secureParamsAlignedSize is invalid.\n");
        return -ENOMEM;
    }
    *reeSecureParams = MailboxAlloc(paramsSize, 0);
    if (*reeSecureParams == NULL) {
        tloge("Malloc REE session secure parameters buffer failed.\n");
        return -ENOMEM;
    }
    *teeSecureParams = calloc(1, secureParamsAlignedSize);
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)(*teeSecureParams))) {
        tloge("Malloc TEE session secure parameters buffer failed.\n");
        MailboxFree(*reeSecureParams);
        *reeSecureParams = NULL;
        return -ENOMEM;
    }
    return 0;
}

static int InitForAllocSecureParams(GetSecureInfoParams *paramsIn,
    uint32_t *secureParamsAlignedSize, uint32_t *paramsSize)
{
    int ret;

    ret = GenerateChallengeWord(
        (uint8_t *)&paramsIn->session->secureInfo.challengeWord,
        sizeof(paramsIn->session->secureInfo.challengeWord));
    if (ret) {
        tloge("Generate challenge word failed, ret = %d\n", ret);
        return ret;
    }
    *secureParamsAlignedSize =
        AlginUp(sizeof(struct SessionSecureParams), CIPHER_BLOCK_BYTESIZE);
    *paramsSize = *secureParamsAlignedSize + IV_BYTESIZE;
    return 0;
}

static int SendSmcCmdForSecureParams(const GetSecureInfoParams *paramsIn,
    struct SessionSecureParams *reeSecureParams)
{
    int ret;
    TcNsSmcCmd smcCmd = { {0}, 0 };
    uint32_t uid;

    uid = GetTaskUid(OsCurrTaskGet());
    /* Transfer chanllenge word to secure world */
    reeSecureParams->payload.ree2tee.challengeWord =
        paramsIn->session->secureInfo.challengeWord;
    smcCmd.globalCmd = true;
    if (memcpy_s(smcCmd.uuid, sizeof(smcCmd.uuid),
        paramsIn->context->uuid, UUID_LEN)) {
        tloge("memcpy_s uuid error.\n");
        return -EFAULT;
    }
    smcCmd.cmdId = GLOBAL_CMD_ID_GET_SESSION_SECURE_PARAMS;
    smcCmd.devFileId = paramsIn->devFile->devFileId;
    smcCmd.contextId = paramsIn->context->sessionId;
    smcCmd.operationPhys = 0;
    smcCmd.operationHphys = 0;
    smcCmd.loginDataPhy = 0;
    smcCmd.loginDataHaddr = 0;
    smcCmd.loginDataLen = 0;
    smcCmd.errOrigin = 0;
    smcCmd.uid = uid;
    smcCmd.started = paramsIn->context->started;
    smcCmd.paramsPhys = LOS_PaddrQuery((void *)reeSecureParams);
    smcCmd.paramsHphys = 0;
    ret = TcNsSmc(&smcCmd);
    if (ret) {
        reeSecureParams->payload.ree2tee.challengeWord = 0;
        tloge("TC_NS_SMC returns error, ret = %d\n", ret);
        return ret;
    }
    return 0;
}

static int UpdateSecureParamsFromTee(GetSecureInfoParams *paramsIn,
    struct SessionSecureParams *reeSecureParams,
    struct SessionSecureParams *teeSecureParams,
    uint32_t secureParamsAlignedSize,
    uint32_t paramsSize)
{
    int ret;
    uint8_t *encSecureParams = NULL;
    /* Get encrypted session secure parameters from secure world */
    encSecureParams = (uint8_t *)reeSecureParams;
    struct SessionCryptoInfo *rootKey = GetSessionRootKeyInstance();
    if (rootKey == NULL) {
        return -EINVAL;
    }
    ret = CryptoSessionAescbcKey256(encSecureParams, paramsSize,
        (uint8_t *)teeSecureParams, secureParamsAlignedSize,
        rootKey->key, NULL, DECRYPT);
    if (ret) {
        tloge("Decrypted session secure parameters failed, ret = %d.\n", ret);
        return ret;
    }
    /* Analyze encryption head */

    if (!IsValidEncryptionHead(&teeSecureParams->head,
        (uint8_t *)&teeSecureParams->payload,
        sizeof(teeSecureParams->payload)))
        return -EFAULT;

    /* Store session secure parameters */
    ret = memcpy_s((void *)paramsIn->session->secureInfo.scrambling,
        sizeof(paramsIn->session->secureInfo.scrambling),
        (void *)&teeSecureParams->payload.tee2ree.scrambling,
        sizeof(teeSecureParams->payload.tee2ree.scrambling));
    if (ret) {
        tloge("Memcpy scrambling data failed, ret = %d.\n", ret);
        return ret;
    }
    ret = memcpy_s((void *)&paramsIn->session->secureInfo.cryptoInfo,
        sizeof(paramsIn->session->secureInfo.cryptoInfo),
        (void *)&teeSecureParams->payload.tee2ree.cryptoInfo,
        sizeof(teeSecureParams->payload.tee2ree.cryptoInfo));
    if (ret) {
        tloge("Memcpy session crypto information failed, ret = %d.\n", ret);
        return ret;
    }
    return 0;
}

int GetSessionSecureParams(TcNsDevFile *devFile,
    TcNsClientContext *context, TcNsSession *session)
{
    int ret;
    uint32_t paramsSize;
    uint32_t secureParamsAlignedSize;
    struct SessionSecureParams *reeSecureParams = NULL;
    struct SessionSecureParams *teeSecureParams = NULL;
    bool checkValue = false;
    GetSecureInfoParams paramsIn = { devFile, context, session };

    checkValue = (devFile == NULL || context == NULL || session == NULL);
    if (checkValue == true) {
        tloge("Parameter is null pointer!\n");
        return -EINVAL;
    }
    ret = InitForAllocSecureParams(&paramsIn,
        &secureParamsAlignedSize, &paramsSize);
    if (ret != 0) {
        return ret;
    }
    ret = AllocSecureParams(secureParamsAlignedSize,
        paramsSize, &reeSecureParams, &teeSecureParams);
    if (ret != 0) {
        return ret;
    }
    ret = SendSmcCmdForSecureParams(&paramsIn, reeSecureParams);
    if (ret != 0) {
        goto free;
    }

    ret = UpdateSecureParamsFromTee(&paramsIn, reeSecureParams,
        teeSecureParams, secureParamsAlignedSize, paramsSize);
    if (memset_s((void *)teeSecureParams, secureParamsAlignedSize,
        0, secureParamsAlignedSize)) {
        tloge("Clean the secure parameters buffer failed!\n");
    }
free:
    MailboxFree(reeSecureParams);
    reeSecureParams = NULL;
    free(teeSecureParams);
    teeSecureParams = NULL;
    if (ret) {
        CleanSessionSecureInformation(session);
    }
    return ret;
}

int GenerateEncryptedSessionSecureParams(
    const struct SessionSecureInfo *secureInfo,
    uint8_t *encSecureParams, size_t encParamsSize)
{
    int ret;
    struct SessionSecureParams *reeSecureParams = NULL;
    uint32_t secureParamsAlignedSize =
        AlginUp(sizeof(*reeSecureParams), CIPHER_BLOCK_BYTESIZE);
    uint32_t paramsSize = secureParamsAlignedSize + IV_BYTESIZE;

    if (secureInfo == NULL || encSecureParams == NULL ||
        encParamsSize < paramsSize) {
        tloge("invalid enc params\n");
        return -EINVAL;
    }
    reeSecureParams = calloc(1, secureParamsAlignedSize);
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)reeSecureParams)) {
        tloge("Malloc REE session secure parameters buffer failed.\n");
        return -ENOMEM;
    }
    /* Transfer chanllenge word to secure world */
    reeSecureParams->payload.ree2tee.challengeWord = secureInfo->challengeWord;
    /* Setting encryption head */
    ret = SetEncryptionHead(&reeSecureParams->head,
        sizeof(reeSecureParams->payload));
    if (ret) {
        tloge("Set encryption head failed, ret = %d.\n", ret);
        reeSecureParams->payload.ree2tee.challengeWord = 0;
        free(reeSecureParams);
        return -EINVAL;
    }
    /* Setting padding data */
    ret = CryptoAescbcCmsPadding((uint8_t *)reeSecureParams,
        secureParamsAlignedSize,
        sizeof(struct SessionSecureParams));
    if (ret) {
        tloge("Set encryption padding data failed, ret = %d.\n", ret);
        reeSecureParams->payload.ree2tee.challengeWord = 0;
        free(reeSecureParams);
        return -EINVAL;
    }
    /* Encrypt buffer with current session key */
    ret = CryptoSessionAescbcKey256((uint8_t *)reeSecureParams,
        secureParamsAlignedSize,
        encSecureParams, paramsSize, secureInfo->cryptoInfo.key,
        NULL, ENCRYPT);
    if (ret) {
        tloge("Encrypted session secure parameters failed, ret = %d.\n",
              ret);
        reeSecureParams->payload.ree2tee.challengeWord = 0;
        free(reeSecureParams);
        return -EINVAL;
    }
    reeSecureParams->payload.ree2tee.challengeWord = 0;
    free(reeSecureParams);
    return 0;
}

static int CheckParamsForCryptoSession(const uint8_t *in, const uint8_t *out,
    const uint8_t *key, uint32_t inLen, uint32_t outLen)
{
    if (in == NULL || out == NULL || key == NULL) {
        tloge("AES-CBC crypto parameters have null pointer.\n");
        return -EINVAL;
    }
    if (inLen < IV_BYTESIZE || outLen < IV_BYTESIZE) {
        tloge("AES-CBC crypto data length is invalid.\n");
        return -EINVAL;
    }
    return 0;
}

int CryptoSessionAescbcKey256(uint8_t *in, uint32_t inLen, uint8_t *out,
    uint32_t outLen, const uint8_t *key, uint8_t *iv, uint32_t mode)
{
    int ret;
    uint32_t srcLen;
    uint32_t destLen;
    uint8_t *aescbcIv = NULL;
    bool checkValue = false;

    ret = CheckParamsForCryptoSession(in, out, key, inLen, outLen);
    if (ret) {
        return ret;
    }
    /* For iv variable is null, iv is the first 16 bytes
     * in cryptotext buffer.
     */
    switch (mode) {
        case ENCRYPT:
            srcLen = inLen;
            destLen = outLen - IV_BYTESIZE;
            aescbcIv = out + destLen;
            break;
        case DECRYPT:
            srcLen = inLen - IV_BYTESIZE;
            destLen = outLen;
            aescbcIv = in + srcLen;
            break;
        default:
            tloge("AES-CBC crypto use error mode = %u.\n", mode);
            return -EINVAL;
    }

    /* IV is configured by user */
    if (iv != NULL) {
        srcLen = inLen;
        destLen = outLen;
        aescbcIv = iv;
    }
    checkValue = (srcLen != destLen) || (srcLen == 0) ||
        (srcLen % CIPHER_BLOCK_BYTESIZE);
    if (checkValue == true) {
        tloge("AES-CBC, plaintext-len must be equal to cryptotext's. srcLen=%u, destLen=%u.\n",
            srcLen, destLen);
        return -EINVAL;
    }
    /* IV is configured in here */
    checkValue = (iv == NULL) && (mode == ENCRYPT);
    if (checkValue == true) {
        ret = GenerateRandomData(aescbcIv, IV_BYTESIZE);
        if (ret) {
            tloge("Generate AES-CBC iv failed, ret = %d.\n", ret);
            return ret;
        }
    }
    struct AesParam param = {
        aescbcIv, key, srcLen, mode
    };
    return CryptoAescbcKey256(out, in, &param);
}

int CryptoAescbcCmsPadding(uint8_t *plaintext, uint32_t plaintextLen,
    uint32_t payloadLen)
{
    uint32_t paddingLen;
    uint8_t padding;
    bool checkValue = false;

    if (plaintext == NULL) {
        tloge("Plaintext is NULL.\n");
        return -EINVAL;
    }
    checkValue = (!plaintextLen) ||
        (plaintextLen % CIPHER_BLOCK_BYTESIZE) ||
        (plaintextLen < payloadLen);
    if (checkValue == true) {
        tloge("Plaintext length is invalid.\n");
        return -EINVAL;
    }
    paddingLen = plaintextLen - payloadLen;
    if (paddingLen >= CIPHER_BLOCK_BYTESIZE) {
        tloge("Padding length is error.\n");
        return -EINVAL;
    }
    if (paddingLen == 0) {
        /* No need padding */
        return 0;
    }
    padding = (uint8_t)paddingLen;
    if (memset_s((void *)(plaintext + payloadLen),
        paddingLen, padding, paddingLen)) {
        tloge("CMS-Padding is failed.\n");
        return -EFAULT;
    }
    return 0;
}
#endif

char *GetProcessPath(LosTaskCB *task, char *tpath, int pathLen)
{
    if (task == NULL || tpath == NULL || pathLen < 0 || pathLen > MAX_PATH_SIZE) {
        return NULL;
    }

    struct file *fp = OS_PCB_FROM_PID(task->processID)->execFile;
    if (fp == NULL) {
        return NULL;
    }
    int ret = memset_s(tpath, pathLen, '\0', pathLen);
    if (ret != EOK) {
        tloge("memset error ret is %d\n", ret);
        return NULL;
    }

    ret = memcpy_s(tpath, pathLen - 1, fp->f_path, strlen(fp->f_path));
    if (ret != EOK) {
        tloge("memcpy error ret is %d\n", ret);
        return NULL;
    }
    return tpath;
}

int CalcProcessPathHash(const unsigned char *data,
    unsigned long dataLen, unsigned char *digest, unsigned int digLen)
{
    bool checkValue = false;
    TeeSha256Context ctx;

    checkValue = (data == NULL || digest == NULL ||
        dataLen == 0 || digLen != SHA256_DIGEST_LENTH);
    if (checkValue == true) {
        tloge("Bad parameters!\n");
        return -EFAULT;
    }

    TeeSha256Init(&ctx);
    TeeSha256Update(&ctx, data, dataLen);
    TeeSha256Final(&ctx, digest);
    return 0;
}

int PackCaCert(char *caCert, const char *path,
    LosTaskCB *caTask, int uid)
{
    int messageSize;

    if (caCert == NULL || path == NULL || caTask == NULL) {
        return 0;
    }

    messageSize = snprintf_s(caCert, BUF_MAX_SIZE - 1,
        BUF_MAX_SIZE - 1, "%s%u", path,
        uid);

    return messageSize;
}

#define MAX_REF_COUNT 255
TcNsService *TcRefServiceInDev(TcNsDevFile *dev, const unsigned char *uuid,
    int uuidSize, bool *isFull)
{
    uint32_t i;

    if (dev == NULL || uuid == NULL || uuidSize != UUID_LEN ||
        isFull == NULL) {
        return NULL;
    }
    for (i = 0; i < SERVICES_MAX_COUNT; i++) {
        if (dev->services[i] != NULL &&
            memcmp(dev->services[i]->uuid, uuid, UUID_LEN) == 0) {
            if (dev->serviceRef[i] == MAX_REF_COUNT) {
                *isFull = true;
                return NULL;
            }
            dev->serviceRef[i]++;
            return dev->services[i];
        }
    }
    return NULL;
}

TcNsService *TcFindServiceInDev(TcNsDevFile *dev,
    const unsigned char *uuid, int uuidSize)
{
    uint32_t i;

    if (dev == NULL || uuid == NULL || uuidSize != UUID_LEN) {
        return NULL;
    }
    for (i = 0; i < SERVICES_MAX_COUNT; i++) {
        if (dev->services[i] != NULL &&
            memcmp(dev->services[i]->uuid, uuid, UUID_LEN) == 0) {
            return dev->services[i];
        }
    }
    return NULL;
}

TcNsService *TcFindServiceFromAll(const unsigned char *uuid, uint32_t uuidLen)
{
    TcNsService *service = NULL;

    if (uuid == NULL || uuidLen != UUID_LEN) {
        return NULL;
    }
    list_for_each_entry(service, GetServiceList(), head) {
        if (memcmp(service->uuid, uuid, sizeof(service->uuid)) == 0) {
            return service;
        }
    }
    return NULL;
}

int AddServiceToDev(TcNsDevFile *dev, TcNsService *service)
{
    uint32_t i;

    if (dev == NULL || service == NULL) {
        return -1;
    }
    for (i = 0; i < SERVICES_MAX_COUNT; i++) {
        if (dev->services[i] == NULL) {
            tlogd("add service %u to %u\n", i, dev->devFileId);
            dev->services[i] = service;
            dev->serviceRef[i] = 1;
            return 0;
        }
    }
    return -1;
}

void DelServiceFromDev(TcNsDevFile *dev, TcNsService *service)
{
    uint32_t i;

    if (dev == NULL || service == NULL) {
        return;
    }
    for (i = 0; i < SERVICES_MAX_COUNT; i++) {
        if (dev->services[i] == service) {
            tlogd("dev->serviceRef[%u] = %u\n", i, dev->serviceRef[i]);
            if (dev->serviceRef[i] == 0) {
                tloge("Caution! No service to be deleted!\n");
                break;
            }
            dev->serviceRef[i]--;
            if (!dev->serviceRef[i]) {
                tlogd("del service %u from %u\n", i, dev->devFileId);
                dev->services[i] = NULL;
                PutServiceStruct(service);
            }
            break;
        }
    }
}

TcNsSession *TcFindSessionWithOwner(struct list_head *sessionList,
    unsigned int sessionId, TcNsDevFile *devFile)
{
    TcNsSession *session = NULL;
    bool checkValue = false;

    checkValue = (sessionList == NULL || devFile == NULL);
    if (checkValue == true) {
        tloge("sessionList or devFile is Null.\n");
        return NULL;
    }
    list_for_each_entry(session, sessionList, head) {
        checkValue = (session->sessionId == sessionId &&
            session->owner == devFile);
        if (checkValue == true) {
            return session;
        }
    }
    return NULL;
}

void DumpServicesStatus(const char *param)
{
    TcNsService *service = NULL;

    (void)param;
    mutex_lock(GetServiceListLock());
    tlogi("show service list:\n");
    list_for_each_entry(service, GetServiceList(), head) {
        tlogi("uuid-%x, usage=%d\n", *(uint32_t *)service->uuid,
            atomic_read(&service->usage));
    }
    mutex_unlock(GetServiceListLock());
}

errno_t InitContext(TcNsClientContext *context, const unsigned char *uuid,
    const unsigned int uuidLen)
{
    errno_t sret;

    if (context == NULL || uuid == NULL || uuidLen != UUID_LEN) {
        return -1;
    }
    sret = memset_s(context, sizeof(*context), 0, sizeof(*context));
    if (sret != EOK) {
        return -1;
    }

    sret = memcpy_s(context->uuid, sizeof(context->uuid), uuid, uuidLen);
    if (sret != EOK) {
        return -1;
    }
    return 0;
}

int CloseSession(TcNsDevFile *dev, TcNsSession *session,
    const unsigned char *uuid, unsigned int uuidLen, unsigned int sessionId)
{
    TcNsClientContext context;
    int ret;
    errno_t sret;
    bool checkValue = false;

    checkValue = (dev == NULL || session == NULL ||
        uuid == NULL || uuidLen != UUID_LEN);
    if (checkValue == true) {
        return TEEC_ERROR_GENERIC;
    }
    sret = InitContext(&context, uuid, uuidLen);
    if (sret != 0) {
        return TEEC_ERROR_GENERIC;
    }
    context.sessionId = sessionId;
    context.cmdId = GLOBAL_CMD_ID_CLOSE_SESSION;
    ret = TcClientCall(&context, dev, session,
        TC_CALL_GLOBAL | TC_CALL_SYNC);
    if (ret) {
        tloge("close session failed, ret=0x%x\n", ret);
    }
    return ret;
}

void KillSession(TcNsDevFile *dev, const unsigned char *uuid,
    unsigned int uuidLen, unsigned int sessionId)
{
    TcNsClientContext context;
    int ret;
    errno_t sret;

    if (dev == NULL || uuid == NULL || uuidLen != UUID_LEN) {
        return;
    }
    sret = InitContext(&context, uuid, uuidLen);
    if (sret != 0) {
        return;
    }
    context.sessionId = sessionId;
    context.cmdId = GLOBAL_CMD_ID_KILL_TASK;
    tlogd("devFileId=%u\n", dev->devFileId);
    /* do clear work in agent */
    TeeAgentClearWork(&context, dev->devFileId);
    ret = TcClientCall(&context, dev, NULL,
        TC_CALL_GLOBAL | TC_CALL_SYNC);
    if (ret) {
        tloge("close session failed, ret=0x%x\n", ret);
    }
    return;
}

int TcNsServiceInit(const unsigned char *uuid, uint32_t uuidLen,
    TcNsService **newService)
{
    int ret = 0;
    TcNsService *service = NULL;
    errno_t sret;
    bool checkValue = false;

    checkValue = (uuid == NULL || newService == NULL ||
        uuidLen != UUID_LEN);
    if (checkValue == true) {
        return -ENOMEM;
    }
    service = calloc(1, sizeof(*service));
    if (ZERO_OR_NULL_PTR((unsigned long)(uintptr_t)service)) {
        tloge("calloc failed\n");
        ret = -ENOMEM;
        return ret;
    }
    sret = memcpy_s(service->uuid, sizeof(service->uuid), uuid, uuidLen);
    if (sret != EOK) {
        free(service);
        return -ENOMEM;
    }
    INIT_LIST_HEAD(&service->sessionList);
    mutex_init(&service->SessionLock);
    list_add_tail(&service->head, GetServiceList());
    tlogd("add service [0x%x] to service list\n", *(uint32_t *)uuid);
    atomic_set(&service->usage, 1);
    mutex_init(&service->operationLock);
    *newService = service;
    return ret;
}

uint32_t TcNsGetUid(void)
{
    return GetTaskUid(OsCurrTaskGet());
}

int GetPackNameLen(TcNsDevFile *devFile, const uint8_t *certBuffer,
    unsigned int certBufferSize)
{
    errno_t sret;

    if (devFile == NULL || certBuffer == NULL || certBufferSize == 0) {
        return -ENOMEM;
    }
    sret = memcpy_s(&devFile->pkgNameLen, sizeof(devFile->pkgNameLen),
        certBuffer, sizeof(devFile->pkgNameLen));
    if (sret != EOK) {
        return -ENOMEM;
    }
    tlogd("package_name_len is %u\n", devFile->pkgNameLen);
    if (devFile->pkgNameLen == 0 ||
        devFile->pkgNameLen >= MAX_PACKAGE_NAME_LEN) {
        tloge("Invalid size of package name len login info!\n");
        return -EINVAL;
    }
    return 0;
}

int GetPublicKeyLen(TcNsDevFile *devFile, const uint8_t *certBuffer,
    unsigned int certBufferSize)
{
    errno_t sret;

    if (devFile == NULL || certBuffer == NULL || certBufferSize == 0) {
        return -ENOMEM;
    }
    sret = memcpy_s(&devFile->pubKeyLen, sizeof(devFile->pubKeyLen),
        certBuffer, sizeof(devFile->pubKeyLen));
    if (sret != EOK) {
        return -ENOMEM;
    }
    tlogd("publick_key_len is %u\n", devFile->pubKeyLen);
    if (devFile->pubKeyLen > MAX_PUBKEY_LEN) {
        tloge("Invalid public key length in login info!\n");
        return -EINVAL;
    }
    return 0;
}

bool IsValidTaSize(const char *fileBuffer, unsigned int fileSize)
{
    if (fileBuffer == NULL || fileSize == 0) {
        tloge("invalid load ta size\n");
        return false;
    }
    if (fileSize > SZ_8M) {
        tloge("larger than 8M TA is not supportedi, size=%d\n", fileSize);
        return false;
    }
    return true;
}

int TcNsNeedLoadImage(unsigned int fileId, const unsigned char *uuid,
    unsigned int uuidLen)
{
    int ret = 0;
    int smcRet;
    TcNsSmcCmd smcCmd = { {0}, 0 };
    struct MbCmdPack *mbPack = NULL;
    char *mbParam = NULL;

    if (uuid == NULL || uuidLen != UUID_LEN) {
        tloge("invalid uuid\n");
        return -ENOMEM;
    }
    mbPack = MailboxAllocCmdPack();
    if (mbPack == NULL) {
        tloge("alloc mb pack failed\n");
        return -ENOMEM;
    }

    mbParam = MailboxCopyAlloc((void *)uuid, uuidLen);
    if (mbParam == NULL) {
        tloge("alloc mb param failed\n");
        ret = -ENOMEM;
        goto clean;
    }

    mbPack->operation.paramTypes = TEEC_MEMREF_TEMP_INOUT;
    mbPack->operation.params[0].memref.buffer = LOS_PaddrQuery((void *)mbParam);
    mbPack->operation.bufferHaddr[0] = 0;
    mbPack->operation.params[0].memref.size = SZ_4K;
    smcCmd.cmdId = GLOBAL_CMD_ID_NEED_LOAD_APP;
    smcCmd.globalCmd = true;
    smcCmd.devFileId = fileId;
    smcCmd.contextId = 0;
    smcCmd.operationPhys = LOS_PaddrQuery(&mbPack->operation);
    smcCmd.operationHphys = 0;
    tlogd("secure app load smc command\n");
    smcRet = TcNsSmc(&smcCmd);
    if (smcRet != 0) {
        tloge("smc_call returns error ret 0x%x\n", smcRet);
        ret = -1;
        goto clean;
    } else {
        ret = *(int *)mbParam;
    }

clean:
    if (mbParam != NULL) {
        MailboxFree(mbParam);
    }
    MailboxFree(mbPack);

    return ret;
}

int TcNsLoadSecfile(TcNsDevFile *devFile,
    const void *argp)
{
    int ret;
    struct LoadSecfileIoctlStruct ioctlArg = { 0, {0}, 0, { NULL } };

    if (devFile == NULL || argp == NULL) {
        tloge("Invalid params !\n");
        return -EINVAL;
    }
    if (copy_from_user(&ioctlArg, argp, sizeof(ioctlArg))) {
        tloge("copy from user failed\n");
        ret = -ENOMEM;
        return ret;
    }
    mutex_lock(&g_loadAppLock);
    if (ioctlArg.secfileType == LOAD_TA) {
        ret = TcNsNeedLoadImage(devFile->devFileId,
            ioctlArg.uuid, (unsigned int)UUID_LEN);
        if (ret == 1) { // 1 means we need to load image
            ret = TcNsLoadImage(devFile, ioctlArg.fileBuffer,
                ioctlArg.fileSize);
        }
    } else if (ioctlArg.secfileType == LOAD_LIB) {
        ret = TcNsLoadImage(devFile,
            ioctlArg.fileBuffer, ioctlArg.fileSize);
    } else {
        tloge("invalid secfile type: %d!", ioctlArg.secfileType);
        ret = -EINVAL;
    }

    if (ret) {
        tloge("load TA secfile: %d failed, ret = %x", ioctlArg.secfileType, ret);
    }
    mutex_unlock(&g_loadAppLock);
    return ret;
}

int LoadTaImage(TcNsDevFile *devFile, TcNsClientContext *context)
{
    int ret;

    if (devFile == NULL || context == NULL) {
        return -1;
    }
    mutex_lock(&g_loadAppLock);
    ret = TcNsNeedLoadImage(devFile->devFileId, context->uuid,
        (unsigned int)UUID_LEN);
    if (ret == 1) {
        if (context->fileBuffer == NULL) {
            tloge("context's fileBuffer is NULL");
            mutex_unlock(&g_loadAppLock);
            return -1;
        }
        ret = TcNsLoadImage(devFile, context->fileBuffer,
            context->fileSize);
        if (ret) {
            tloge("load image failed, ret=%x", ret);
            mutex_unlock(&g_loadAppLock);
            return ret;
        }
    }
    mutex_unlock(&g_loadAppLock);
    return ret;
}

void ReleaseFreeSession(TcNsDevFile *devFile,
    TcNsClientContext *context, TcNsSession *session)
{
    bool needKillSession = false;
#ifdef SECURITY_AUTH_ENHANCE
    bool needFree = false;
#endif

    if (devFile == NULL || context == NULL || session == NULL) {
        return;
    }
    needKillSession = context->sessionId != 0;
    if (needKillSession) {
        KillSession(devFile, context->uuid, (unsigned int)UUID_LEN, context->sessionId);
    }
#ifdef SECURITY_AUTH_ENHANCE
    needFree = (session != NULL &&
        session->TcNsToken.tokenBuffer != NULL);
    if (needFree) {
        if (memset_s((void *)session->TcNsToken.tokenBuffer,
            session->TcNsToken.tokenLen,
            0, session->TcNsToken.tokenLen) != EOK) {
            tloge("Caution, memset failed!\n");
        }
        free(session->TcNsToken.tokenBuffer);
        session->TcNsToken.tokenBuffer = NULL;
    }
#endif
}

void CloseSessionInServiceList(TcNsDevFile *dev, TcNsService *service,
    uint32_t index)
{
    TcNsSession *tmpSession = NULL;
    TcNsSession *session = NULL;
    errno_t retErr;
    int ret;

    if (dev == NULL || service == NULL || index >= SERVICES_MAX_COUNT) {
        return;
    }
    list_for_each_entry_safe(session, tmpSession,
        &dev->services[index]->sessionList, head) {
        if (session->owner != dev) {
            continue;
        }
        ret = CloseSession(dev, session, service->uuid,
            (unsigned int)UUID_LEN, session->sessionId);
        if (ret != TEEC_SUCCESS) {
            tloge("close session smc(when close fd) failed!\n");
        }
#ifdef SECURITY_AUTH_ENHANCE
        /* Clean session secure information */
        retErr = memset_s((void *)&session->secureInfo,
            sizeof(session->secureInfo),
            0,
            sizeof(session->secureInfo));
        if (retErr != EOK) {
            tloge("TcNsClientClose memset error=%d\n", retErr);
        }
#endif
        mutex_lock(&service->SessionLock);
        list_del(&session->head);
        mutex_unlock(&service->SessionLock);
        PutSessionStruct(session); /* pair with open session */
    }
}

void CloseUnclosedSession(TcNsDevFile *dev, uint32_t index)
{
    TcNsService *service = NULL;

    if (dev == NULL || index >= SERVICES_MAX_COUNT) {
        return;
    }
    if (dev->services[index] != NULL &&
        !list_empty(&dev->services[index]->sessionList)) {
        service = dev->services[index];

        mutex_lock(&service->operationLock);
        CloseSessionInServiceList(dev, service, index);
        mutex_unlock(&service->operationLock);
        PutServiceStruct(service); /* pair with open session */
    }
}

void DelDevNode(TcNsDevFile *dev)
{
    if (dev == NULL) {
        return;
    }
    mutex_lock(&GetTcNsDevList()->devLock);
    /* del dev from the list */
    list_del(&dev->head);
    mutex_unlock(&GetTcNsDevList()->devLock);
}

int NsClientCloseTeecdNotAgent(TcNsDevFile *dev)
{
    if (dev == NULL) {
        tloge("invalid dev(null)\n");
        return TEEC_ERROR_GENERIC;
    }
    DelDevNode(dev);
    free(dev);
    return TEEC_SUCCESS;
}
