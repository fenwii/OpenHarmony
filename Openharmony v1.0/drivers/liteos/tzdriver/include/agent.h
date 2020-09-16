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

#ifndef AGENT_H
#define AGENT_H
#include "teek_ns_client.h"

#define AGENT_FS_ID           0x46536673 /* FSfs */
#define AGENT_MISC_ID         0x4d495343 /* MISC */
#define TEE_RPMB_AGENT_ID     0x4abe6198 /* RPMB */
#define AGENT_SOCKET_ID       0x69e85664 /* socket */
#define SECFILE_LOAD_AGENT_ID 0x4c4f4144 /* SECFILE-LOAD-AGENT */
#define TEE_SECE_AGENT_ID     0x53656345 /* test */

typedef enum {
    AGENT_FALSE = -1,
    AGENT_SUCCESS = 0,
} AgentErrCode;

typedef enum {
    AGENT_ALIVE = 1,
    AGENT_DEAD = 0,
} AgentStatusCode;

enum AgentStateType {
    AGENT_CRASHED = 0,
    AGENT_REGISTERED,
    AGENT_READY,
};

struct SmcEventData *FindEventControl(unsigned int agentId);

/* for secure agent */
struct SmcEventData {
    unsigned int agentId;
    atomic_t agentReady;
    wait_queue_head_t waitEventWq;
    int retFlag; /* indicate whether agent is returned from TEE */
    wait_queue_head_t sendResponseWq;
    struct list_head head;
    TcNsSmcCmd cmd;
    TcNsDevFile *owner;
    void *agentBuffKernel;
    void *agentBuffUser; /* used for unmap */
    unsigned int agentBuffSize;
    atomic_t usage;
#ifdef CONFIG_TEE_SMP
    wait_queue_head_t caPendingWq;
    atomic_t caRun; /* indicate whether agent is allowed to return to TEE */
#endif
};

struct TeeAgentKernelOps {
    const char *agentName;  /* MUST NOT be NULL */
    unsigned int agentId;   /* MUST NOT be zero */
    int (*teeAgentInit)(struct TeeAgentKernelOps *agentInstance);
    int (*teeAgentRun)(struct TeeAgentKernelOps *agentInstance);
    /* MUST NOT be NULL */
    int (*teeAgentWork)(struct TeeAgentKernelOps *agentInstance);
    int (*teeAgentStop)(struct TeeAgentKernelOps *agentInstance);
    int (*teeAgentExit)(struct TeeAgentKernelOps *agentInstance);
    int (*teeAgentCrashWork)(
        struct TeeAgentKernelOps *agentInstance,
        TcNsClientContext *context,
        unsigned int devFileId);
    LosTaskCB *agentThread;
    void *agentData;
    void *agentBuff;
    unsigned int agentBuffSize;
    struct list_head list;
};

static inline void GetAgentEvent(struct SmcEventData *eventData)
{
    if (eventData != NULL) {
        atomic_inc(&eventData->usage);
    }
}

static inline void PutAgentEvent(struct SmcEventData *eventData)
{
    if (eventData != NULL) {
        if (atomic_dec_and_test(&eventData->usage)) {
            free(eventData);
        }
    }
}

void AgentInit(void);
int AgentExit(void);
void SendEventResponse(unsigned int agentId);
int AgentProcessWork(const TcNsSmcCmd *smcCmd, unsigned int agentId);
int IsAgentAlive(unsigned int agentId);
int TcNsSetNativeHash(unsigned long arg, unsigned int cmdId);
int TcNsLateInit(unsigned long arg);
int TcNsRegisterAgent(TcNsDevFile *devFile, unsigned int agentId,
    unsigned int bufferSize, void **buffer, bool userAgent);
int TcNsUnregisterAgent(unsigned int agentId);
void SendCrashedEventResponseAll(const TcNsDevFile *devFile);
int TcNsWaitEvent(unsigned int agentId);
int TcNsSendEventResponse(unsigned int agentId);
void SendEventResponseSingle(const TcNsDevFile *devFile);
int TcNsSyncSysTime(const TcNsClientTime *tcNsTime);
int TeeAgentClearWork(TcNsClientContext *context,
    unsigned int devFileId);
int TeeAgentKernelRegister(struct TeeAgentKernelOps *newAgent);
bool IsSystemAgent(const TcNsDevFile *devFile);
void TeeAgentClearDevOwner(const TcNsDevFile *devFile);
extern int checkExtAgentAccess(LosTaskCB *caTask);

#endif /* AGENT_H */
