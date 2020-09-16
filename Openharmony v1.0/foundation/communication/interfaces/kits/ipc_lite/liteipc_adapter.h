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

#ifndef _LITEIPC_ADAPTER_H
#define _LITEIPC_ADAPTER_H

#include "pthread.h"
#include "stdint.h"
#include "stdbool.h"
#include "unistd.h"
#include "serializer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define MMAP_DEFAULT_SIZE 65536UL /* 64KB */
#define MMAP_MAX_SIZE 262144UL    /* 256KB */
#define MAX_DEATHCB_PER_SVC 5
#define IPC_WAIT_FOREVER 0XFFFFFFFF
#define IPC_TIMEOUT_MIN 10        /* unit:ms */
#define IPC_INVAILD_TIMER_ID (timer_t)-1
#define IPC_IO_DATA_MAX 200

typedef enum {
    LITEIPC_FLAG_DEFAULT = 0, // send and reply
    LITEIPC_FLAG_ONEWAY,      // send message only
} IpcFlag;

typedef enum {
    ONCE = 0,          // Callback will be removed when timeout
    RESET_AFTER_USE,   // The interval will be refresh when the callback is called
} IpcCbMode;

enum IpcErr {
    LITEIPC_EINVAL = -10,  /* Invalid argument */
    LITEIPC_EBADF,         /* Bad file descriptor */
    LITEIPC_ENOMEM,        /* No memory */
    LITEIPC_ENOENT,        /* Service is not avaliable; For example, Transact on a timeout ipc callback */
    LITEIPC_EINTNL,        /* Internal error, check strerrno in log */
    LITEIPC_OK = 0,
};

enum { DEATH_CODE = 0 };

typedef struct {
    int fd;
    size_t mmapSize;
    void* mmapAddr;
} IpcContext;

typedef int32_t (*IpcMsgHandler)(const IpcContext* context, void* ipcMsg, IpcIo* data, void* arg);

#define LITEIPC_DEFAULT_MAP_SIZE 0X10000

IpcContext* OpenLiteIpc(size_t mmapSize);
void CloseLiteIpc(IpcContext* context);

/* thread-unsafe, cannot be repeatedly invoked */
int32_t SetSaManager(const IpcContext* context, size_t maxMsgSize);
int32_t AddServiceAccess(SvcIdentity sid, pid_t pid);
int32_t GenServiceHandle(SvcIdentity* sid, pid_t tid);

int32_t StartLoop(const IpcContext* context, IpcMsgHandler func, void* arg);
int32_t GetToken(const void* ipcMsg, uint32_t* token);
int32_t GetCode(const void* ipcMsg, uint32_t* code);
int32_t GetFlag(const void* ipcMsg, uint32_t* flag);
pid_t GetCallingTid(const void* ipcMsg);
pid_t GetCallingPid(const void* ipcMsg);
pid_t GetCallingUid(const void* ipcMsg);
pid_t GetCallingGid(const void* ipcMsg);

int32_t Transact(const IpcContext* context,
                 SvcIdentity sid,
                 uint32_t code,
                 IpcIo* data,
                 IpcIo* reply,
                 IpcFlag flag,
                 uintptr_t* buffer);
int32_t SendReply(const IpcContext* context, void* ipcMsg, IpcIo* reply);
int32_t FreeBuffer(const IpcContext* context, void* ptr);
int32_t RegisteIpcCallback(IpcMsgHandler func,
                           uint32_t mode,
                           uint32_t timeoutMs,
                           SvcIdentity* sid,
                           void* arg);
int32_t UnRegisteIpcCallback(SvcIdentity sid);
int32_t RegisteDeathCallback(const IpcContext* context, SvcIdentity sid, IpcMsgHandler func, void* arg, uint32_t* cbId);
int32_t UnRegisteDeathCallback(SvcIdentity sid, uint32_t cbId);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
