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

#ifndef _TEEK_NS_CLIENT_H_
#define _TEEK_NS_CLIENT_H_

#include <linux/list.h>
#include <linux/slab.h>
#include <securec.h>
#include "tc_ns_client.h"
#include "tc_ns_log.h"
#include "tzdriver_compat.h"

#define TC_NS_CLIENT_IOC_MAGIC  't'
#define TC_NS_CLIENT_DEV        "tc_ns_client"
#define TC_NS_CLIENT_DEV_NAME   "/dev/tc_ns_client"

#ifdef CONFIG_SECURE_EXTENSION
#define TC_ASYNC_NOTIFY_SUPPORT
#endif

#define EXCEPTION_MEM_SIZE (8*1024) /* mem for exception handling */
#define TSP_REQUEST        0xB2000008
#define TSP_RESPONSE       0xB2000009
#define TSP_REE_SIQ        0xB200000A
#define TSP_CRASH          0xB200000B
#define TSP_PREEMPTED      0xB2000005
#define TC_CALL_GLOBAL     0x01
#define TC_CALL_SYNC       0x02
#define TC_CALL_LOGIN            0x04
#define TEE_REQ_FROM_USER_MODE   0x0
#define TEE_REQ_FROM_KERNEL_MODE 0x1

/* Max sizes for login info buffer comming from teecd */
#define MAX_PACKAGE_NAME_LEN 255
/* The apk certificate format is as follows:
  * modulus_size(4 bytes) + modulus buffer(512 bytes)
  * + exponent size(4 bytes) + exponent buffer(1 bytes)
  */
#define MAX_PUBKEY_LEN 1024

struct TagTcNsSharedMem;
struct TagTcNsService;

struct TcNsDevList {
    mutex_t devLock; /* for devFileList */
    struct list_head devFileList;
};

#define SERVICES_MAX_COUNT 32 /* service limit can opened on 1 fd */
typedef struct TagTcNsDevFile {
    unsigned int devFileId;
    mutex_t serviceLock; /* for serviceRef[], services[] */
    uint8_t serviceRef[SERVICES_MAX_COUNT]; /* a judge if set services[i]=NULL */
    struct TagTcNsService *services[SERVICES_MAX_COUNT];
    mutex_t sharedMemLock; /* for sharedMemList */
    struct list_head sharedMemList;
    struct list_head head;
    /* Device is linked to call from kernel */
    uint8_t kernelApi;
    /* client login info provided by teecd, can be either package name and public
     * key or uid(for non services/daemons)
     * login information can only be set once, dont' allow subsequent calls
     */
    bool loginSetup;
    mutex_t LoginSetupLock; /* for loginSetup */
    uint32_t pkgNameLen;
    uint8_t PkgName[MAX_PACKAGE_NAME_LEN];
    uint32_t pubKeyLen;
    uint8_t pubKey[MAX_PUBKEY_LEN];
    int loadAppFlag;
} TcNsDevFile;

typedef union {
    struct {
        unsigned int buffer;
        unsigned int size;
    } memref;
    struct {
        unsigned int a;
        unsigned int b;
    } value;
} TcNsParameter;

typedef struct TagTcNsLogin {
    unsigned int method;
    unsigned int mdata;
} tc_ns_login;

typedef struct TagTcNsOperation {
    unsigned int paramTypes;
    TcNsParameter params[TEE_PARAM_NUM];
    unsigned int    bufferHaddr[TEE_PARAM_NUM];
    struct TagTcNsSharedMem *sharemem[TEE_PARAM_NUM];
    void *mbBuffer[TEE_PARAM_NUM];
} TcNsOperation;

typedef struct TagTcNsTempBuf {
    void *tempBuffer;
    unsigned int size;
} TcNsTempBuf;

typedef struct  TagTcNsSmcCmd {
    uint8_t      uuid[sizeof(TeecUuid)];
    bool         globalCmd; /* mark it's a gtask cmd */
    unsigned int cmdId;
    unsigned int devFileId;
    unsigned int contextId;
    unsigned int agentId;
    unsigned int operationPhys;
    unsigned int operationHphys;
    unsigned int loginMethod;
    unsigned int loginDataPhy;
    unsigned int loginDataHaddr;
    unsigned int loginDataLen;
    unsigned int errOrigin;
    int          retVal;
    unsigned int eventNr;
    unsigned int uid;
#ifdef CONFIG_TEE_SMP
    unsigned int caPid;
#endif
#ifdef SECURITY_AUTH_ENHANCE
    unsigned int tokenPhys;
    unsigned int tokenHphys;
    unsigned int pid;
    unsigned int paramsPhys;
    unsigned int paramsHphys;
    unsigned int eventindex;     // tee audit event index for upload
#endif
    bool started;
}__attribute__((__packed__))TcNsSmcCmd;

typedef struct TagTcNsSharedMem {
    void *kernelAddr;
    void *userAddr;
    void *userAddrCa; /* for ca alloc share mem */
    unsigned int len;
    struct list_head head;
    atomic_t usage;
    atomic_t offset;
} TcNsSharedMem;

typedef struct TagTcNsService {
    unsigned char uuid[UUID_LEN];
    mutex_t SessionLock; /* for sessionList */
    struct list_head sessionList;
    struct list_head head;
    mutex_t operationLock; /* for session's open/close */
    atomic_t usage;
} TcNsService;

/*
 * @brief
 */
struct TcWaitData {
    wait_queue_head_t sendCmdWq;
    int sendWaitFlag;
};

#ifdef SECURITY_AUTH_ENHANCE
/* Using AES-CBC algorithm to encrypt communication between secure world and
 * normal world.
 */
#define CIPHER_KEY_BYTESIZE 32   /* AES-256 key size */
#define IV_BYTESIZE   16  /* AES-CBC encryption initialization vector size */
#define CIPHER_BLOCK_BYTESIZE 16 /* AES-CBC cipher block size */
#define SCRAMBLING_NUMBER 3
#define CHKSUM_LENGTH  (sizeof(TcNsSmcCmd) - sizeof(uint32_t))

#define HASH_PLAINTEXT_SIZE (MAX_SHA_256_SZ + sizeof(struct EncryptionHead))
#define HASH_PLAINTEXT_ALIGNED_SIZE \
    ALIGN_TZ(HASH_PLAINTEXT_SIZE, CIPHER_BLOCK_BYTESIZE)

enum SCRAMBLING_ID {
    SCRAMBLING_TOKEN = 0,
    SCRAMBLING_OPERATION = 1,
    SCRAMBLING_MAX = SCRAMBLING_NUMBER
};

struct SessionCryptoInfo {
    uint8_t key[CIPHER_KEY_BYTESIZE]; /* AES-256 key */
    uint8_t iv[IV_BYTESIZE]; /* AES-CBC encryption initialization vector */
};

struct SessionSecureInfo {
    uint32_t challengeWord;
    uint32_t scrambling[SCRAMBLING_NUMBER];
    struct SessionCryptoInfo cryptoInfo;
};

#define MAGIC_SIZE 16
#define MAGIC_STRING "Trusted-magic"

/* One encrypted block, which is aligned with CIPHER_BLOCK_BYTESIZE bytes
 * Head + Payload + Padding
 */
struct EncryptionHead {
    int8_t magic[MAGIC_SIZE];
    uint32_t payloadLen;
};

struct SessionSecureParams {
    struct EncryptionHead head;
    union {
        struct {
            uint32_t challengeWord;
        } ree2tee;
        struct {
            uint32_t scrambling[SCRAMBLING_NUMBER];
            struct SessionCryptoInfo cryptoInfo;
        } tee2ree;
    } payload;
};
#endif

#ifdef SECURITY_AUTH_ENHANCE
typedef struct TagTcNsToken {
    /* 42byte, token_32byte + timestamp_8byte + kernal_api_1byte + sync_1byte */
    uint8_t *tokenBuffer;
    uint32_t tokenLen;
} TcNsToken;
#endif

#define NUM_OF_SO 1
#define KIND_OF_SO 2
typedef struct TagTcNsSession {
    unsigned int sessionId;
    struct list_head head;
    struct TcWaitData waitData;
    mutex_t taSessionLock; /* for open/close/invoke on 1 session */
    TcNsDevFile *owner;
#ifdef SECURITY_AUTH_ENHANCE
    /* Session secure enhanced information */
    struct SessionSecureInfo secureInfo;
    TcNsToken TcNsToken;
    /* when SECURITY_AUTH_ENHANCE enabled, hash of the same CA and
     * SO library will be encrypted by different session key,
     * so put authHashBuf in TcNsSession.
     * the first MAX_SHA_256_SZ size stores SO hash,
     * the next HASH_PLAINTEXT_ALIGNED_SIZE stores CA hash and cryptohead,
     * the last IV_BYTESIZE size stores aes iv
     */
    uint8_t authHashBuf[MAX_SHA_256_SZ * NUM_OF_SO + HASH_PLAINTEXT_ALIGNED_SIZE + IV_BYTESIZE];
#else
    uint8_t authHashBuf[MAX_SHA_256_SZ * NUM_OF_SO + MAX_SHA_256_SZ];
#endif
    atomic_t usage;
} TcNsSession;

void GetServiceStruct(struct TagTcNsService *service);
void PutServiceStruct(struct TagTcNsService *service);

static inline void GetSessionStruct(struct TagTcNsSession *session)
{
    if (session != NULL) {
        atomic_inc(&session->usage);
    }
}

void PutSessionStruct(struct TagTcNsSession *session);

TcNsSession *TcFindSessionWithOwner(struct list_head *sessionList,
    unsigned int sessionId, TcNsDevFile *dev);

#ifdef SECURITY_AUTH_ENHANCE
int GenerateEncryptedSessionSecureParams(
    const struct SessionSecureInfo *secureInfo,
    uint8_t *encSecureParams, size_t encParamsSize);
#define ENCRYPT 1
#define DECRYPT 0

int CryptoSessionAescbcKey256(uint8_t *in, uint32_t inLen,
    uint8_t *out, uint32_t out_len,
    const uint8_t *key, uint8_t *iv,
    uint32_t mode);
int CryptoAescbcCmsPadding(uint8_t *plaintext, uint32_t plaintextLen,
    uint32_t payloadLen);
#endif

int TcNsClientOpen(TcNsDevFile **devFile, uint8_t kernelApi);
int TcNsClientClose(TcNsDevFile *dev);
int IsAgentAlive(unsigned int agentId);
int TcNsOpenSession(TcNsDevFile *devFile, TcNsClientContext *context);
int TcNsCloseSession(TcNsDevFile *devFile, TcNsClientContext *context);
int TcNsSendCmd(TcNsDevFile *devFile, TcNsClientContext *context);
uint32_t TcNsGetUid(void);

#endif
