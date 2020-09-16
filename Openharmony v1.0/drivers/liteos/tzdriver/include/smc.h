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

#ifndef _SMC_H_
#define _SMC_H_

#include "teek_client_constants.h"
#include "teek_ns_client.h"

enum TcNsCmdType {
    TC_NS_CMD_TYPE_INVALID = 0,
    TC_NS_CMD_TYPE_NS_TO_SECURE,
    TC_NS_CMD_TYPE_SECURE_TO_NS,
    TC_NS_CMD_TYPE_SECURE_TO_SECURE,
    TC_NS_CMD_TYPE_SECURE_CONFIG = 0xf,
    TC_NS_CMD_TYPE_MAX
};

#ifdef CONFIG_TEE_SMP
struct PendingEntry {
    atomic_t users;
    pid_t pid;
    wait_queue_head_t wq;
    atomic_t run;
    struct list_head list;
};
#endif

#define RESLEEP_TIMEOUT 15

struct SessionCryptoInfo *GetSessionRootKeyInstance(void);
int SigkillPending(LosTaskCB *tsk);
int SmcInitData(void);
void SmcFreeData(void);
int TcNsSmc(TcNsSmcCmd *cmd);
int TcNsSmcWithNoNr(TcNsSmcCmd *cmd);
void SetCmdSendState(void);
int InitSmcSvcThread(void);
int SmcWakeupCa(pid_t ca);
int SmcWakeupBroadcast(void);
int SmcShadowExit(pid_t ca);
int SmcQueueShadowWorker(uint64_t target);
void FiqShadowWorkFunc(uint64_t target);
struct PendingEntry *FindPendingEntry(pid_t pid);
void ForeachPendingEntry(void (*func)(struct PendingEntry *));
void PutPendingEntry(struct PendingEntry *pe);
void ShowCmdBitmap(void);
void ShowCmdBitmapWithLock(void);
void WakeupTcSiq(void);

#endif
