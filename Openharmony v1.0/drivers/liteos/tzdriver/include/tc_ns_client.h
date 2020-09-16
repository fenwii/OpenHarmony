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

#ifndef _TC_NS_CLIENT_H_
#define _TC_NS_CLIENT_H_

#include <linux/fs.h>
#include "teek_client_type.h"

#ifdef SECURITY_AUTH_ENHANCE
#define SCRAMBLING_KEY_LEN      4
#define TOKEN_BUFFER_LEN        42   /* token(32byte) + timestamp(8byte) + kernal_api(1byte) + sync(1byte) */
#define TIMESTAMP_BUFFER_INDEX  32
#define KERNAL_API_INDEX        40
#define SYNC_INDEX              41
#define UUID_LEN                16
#define PARAM_NUM               4
#define ADDR_TRANS_NUM          32
#define TEE_PARAM_ONE           0
#define TEE_PARAM_TWO           1
#define TEE_PARAM_THREE         2
#define TEE_PARAM_FOUR          3

#define TIMESTAMP_LEN_DEFAULT \
    ((KERNAL_API_INDEX) - (TIMESTAMP_BUFFER_INDEX))
#define KERNAL_API_LEN \
    ((TOKEN_BUFFER_LEN) - (KERNAL_API_INDEX))
#define TIMESTAMP_SAVE_INDEX    16
#endif

#ifndef ZERO_SIZE_PTR
#define ZERO_SIZE_PTR ((void *)16)
#define ZERO_OR_NULL_PTR(x) ((unsigned long)(x) <= (unsigned long)ZERO_SIZE_PTR)
#endif

typedef struct {
    unsigned int method;
    unsigned int mdata;
} TcNsClientLogin;

typedef union {
    struct {
        unsigned int buffer;
        unsigned int bufferH;
        unsigned int offset;
        unsigned int offsetH;
        unsigned int sizeAddr;
        unsigned int sizeAddrH;
    } memref;
    struct {
        unsigned int aAddr;
        unsigned int aHaddr;
        unsigned int bAddr;
        unsigned int bHaddr;
    } value;
} TcNsClientParam;

typedef struct {
    int code;
    unsigned int origin;
} TcNsClientReturn;

typedef struct {
    unsigned char uuid[UUID_LEN];
    unsigned int sessionId;
    unsigned int cmdId;
    TcNsClientReturn returns;
    TcNsClientLogin login;
    TcNsClientParam params[PARAM_NUM];
    unsigned int paramTypes;
    unsigned char started;
#ifdef SECURITY_AUTH_ENHANCE
    void* teecToken;
    unsigned int tokenLen;
#endif
    unsigned int callingPid;
    unsigned int fileSize;
    union {
        char *fileBuffer;
        unsigned long long fileAddr;
    };
} TcNsClientContext;

typedef struct {
    unsigned int seconds;
    unsigned int millis;
} TcNsClientTime;

enum SecfileTypeT {
    LOAD_TA = 0,
    LOAD_SERVICE,
    LOAD_LIB,
};

struct LoadSecfileIoctlStruct {
    enum SecfileTypeT secfileType;
    unsigned char uuid[UUID_LEN];
    unsigned int fileSize;
    union {
        char *fileBuffer;
        unsigned long long file_addr;
    };
};

struct AgentIoctlArgs {
    unsigned int id;
    unsigned int bufferSize;
    union {
        void *buffer;
        unsigned long long addr;
    };
};

#define TST_CMD_01 1
#define TST_CMD_02 2
#define TST_CMD_03 3
#define TST_CMD_04 4
#define TST_CMD_05 5

#define MAX_SHA_256_SZ 32

#define TC_NS_CLIENT_IOCTL_SES_OPEN_REQ \
    _IOW(TC_NS_CLIENT_IOC_MAGIC, 1, TcNsClientContext)
#define TC_NS_CLIENT_IOCTL_SES_CLOSE_REQ \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 2, TcNsClientContext)
#define TC_NS_CLIENT_IOCTL_SEND_CMD_REQ \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 3, TcNsClientContext)
#define TC_NS_CLIENT_IOCTL_SHRD_MEM_RELEASE \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 4, unsigned int)
#define TC_NS_CLIENT_IOCTL_WAIT_EVENT \
    _IO(TC_NS_CLIENT_IOC_MAGIC, 5)
#define TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE \
    _IO(TC_NS_CLIENT_IOC_MAGIC, 6)
#define TC_NS_CLIENT_IOCTL_REGISTER_AGENT \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 7, struct AgentIoctlArgs)
#define TC_NS_CLIENT_IOCTL_UNREGISTER_AGENT \
    _IO(TC_NS_CLIENT_IOC_MAGIC, 8)
#define TC_NS_CLIENT_IOCTL_LOAD_APP_REQ \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 9, struct LoadSecfileIoctlStruct)
#define TC_NS_CLIENT_IOCTL_NEED_LOAD_APP \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 10, TcNsClientContext)
#define TC_NS_CLIENT_IOCTL_ALLOC_EXCEPTING_MEM \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 12, unsigned int)
#define TC_NS_CLIENT_IOCTL_CANCEL_CMD_REQ \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 13, TcNsClientContext)
#define TC_NS_CLIENT_IOCTL_LOGIN \
    _IO(TC_NS_CLIENT_IOC_MAGIC, 14)
#define TC_NS_CLIENT_IOCTL_TST_CMD_REQ \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 15, int)
#define TC_NS_CLIENT_IOCTL_TUI_EVENT \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 16, int)
#define TC_NS_CLIENT_IOCTL_SYC_SYS_TIME \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 17, TcNsClientTime)
#define TC_NS_CLIENT_IOCTL_SET_NATIVECA_IDENTITY \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 18, int)
#define TC_NS_CLIENT_IOCTL_LOAD_TTF_FILE_AND_NOTCH_HEIGHT \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 19, unsigned int)
#define TC_NS_CLIENT_IOCTL_LATEINIT \
    _IO(TC_NS_CLIENT_IOC_MAGIC, 20)
#define TC_NS_CLIENT_IOCTL_GET_TEE_VERSION \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 21, unsigned int)
#define TC_NS_CLIENT_IOCTL_UNMAP_SHARED_MEM \
    _IOWR(TC_NS_CLIENT_IOC_MAGIC, 22, unsigned int)

#endif
