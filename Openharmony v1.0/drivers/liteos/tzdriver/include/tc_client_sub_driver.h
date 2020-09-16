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

#ifndef _TC_NS_CLIENT_DRIVER_SUB_H_
#define _TC_NS_CLIENT_DRIVER_SUB_H_
#include <securec.h>
#include "tc_ns_client.h"
#include "teek_ns_client.h"

#define CHECK_PATH_HASH_FAIL   0xff01
#define CHECK_SECLABEL_FAIL    0xff02
#define CHECK_CODE_HASH_FAIL   0xff03
#define ENTER_BYPASS_CHANNEL   0xff04
#define BUF_MAX_SIZE           1024
#define MAX_PATH_SIZE          512
#define SHA256_DIGEST_LENTH    32

char *GetProcessPath(LosTaskCB *task, char *tpath, int pathLen);
int CalcProcessPathHash(const unsigned char *data,
    unsigned long dataLen, unsigned char *digest, unsigned int digLen);
int PackCaCert(char *caCert, const char *path,
    LosTaskCB *caTask, int uid);
TcNsService *TcFindServiceInDev(TcNsDevFile *dev,
    const unsigned char *uuid, int uuidSize);
TcNsService *TcRefServiceInDev(TcNsDevFile *dev, const unsigned char *uuid,
    int uuidSize, bool *isFull);
TcNsService *TcFindServiceFromAll(const unsigned char *uuid, uint32_t uuidLen);
int AddServiceToDev(TcNsDevFile *dev, TcNsService *service);
void DelServiceFromDev(TcNsDevFile *dev, TcNsService *service);
TcNsSession *TcFindSessionWithOwner(struct list_head *sessionList,
    unsigned int sessionId, TcNsDevFile *devFile);
void DumpServicesStatus(const char *param);
errno_t InitContext(TcNsClientContext *context,
    const unsigned char *uuid, const unsigned int uuidLen);
#ifdef SECURITY_AUTH_ENHANCE
int GenerateRandomData(uint8_t *data, uint32_t size);
bool IsValidEncryptionHead(const struct EncryptionHead *head, const uint8_t *data, uint32_t len);
int GenerateChallengeWord(uint8_t *challengeWord, uint32_t size);
int SetEncryptionHead(struct EncryptionHead *head, uint32_t len);
TcNsSession *TcFindSession2(unsigned int devFileId, const TcNsSmcCmd *cmd);
void CleanSessionSecureInformation(TcNsSession *session);
int GetSessionSecureParams(TcNsDevFile *devFile, TcNsClientContext *context, TcNsSession *session);
#endif
int CloseSession(TcNsDevFile *dev, TcNsSession *session, const unsigned char *uuid,
    unsigned int uuidLen, unsigned int sessionId);
void KillSession(TcNsDevFile *dev, const unsigned char *uuid,
    unsigned int uuidLen, unsigned int sessionId);
int TcNsServiceInit(const unsigned char *uuid, uint32_t uuidLen, TcNsService **newService);
uint32_t TcNsGetUid(void);
int GetPackNameLen(TcNsDevFile *devFile, const uint8_t *certBuffer,
    unsigned int certBufferSize);
int GetPublicKeyLen(TcNsDevFile *devFile, const uint8_t *certBuffer,
    unsigned int certBufferSize);
bool IsValidTaSize(const char *fileBuffer, unsigned int fileSize);
int TcNsNeedLoadImage(unsigned int fileId, const unsigned char *uuid,
    unsigned int uuidLen);
int LoadTaImage(TcNsDevFile *devFile, TcNsClientContext *context);
void ReleaseFreeSession(TcNsDevFile *devFile, TcNsClientContext *context, TcNsSession *session);
void CloseSessionInServiceList(TcNsDevFile *dev, TcNsService *service, uint32_t i);
void CloseUnclosedSession(TcNsDevFile *dev, uint32_t i);
void DelDevNode(TcNsDevFile *dev);
int NsClientCloseTeecdNotAgent(TcNsDevFile *dev);
int TcNsLoadSecfile(TcNsDevFile *devFile, const void __user *argp);
#endif
