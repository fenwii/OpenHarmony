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

#ifndef _LITEIPC_H
#define _LITEIPC_H

#include <stdint.h>
#include "sys/ioctl.h"
#include "serializer.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define LITEIPC_DRIVER "/dev/lite_ipc"

typedef enum { MT_REQUEST, MT_REPLY, MT_FAILED_REPLY, MT_DEATH_NOTIFY } MsgType;

#define IPC_IOC_MAGIC       'i'
#define IPC_SET_CMS         _IO(IPC_IOC_MAGIC, 1)
#define IPC_CMS_CMD         _IOWR(IPC_IOC_MAGIC, 2, CmsCmdContent)
#define IPC_SET_IPC_THREAD  _IO(IPC_IOC_MAGIC, 3)
#define IPC_SEND_RECV_MSG   _IOWR(IPC_IOC_MAGIC, 4, IpcContent)

typedef enum { CMS_GEN_HANDLE, CMS_REMOVE_HANDLE, CMS_ADD_ACCESS } CmsCmd;

typedef struct {
    CmsCmd cmd;
    uint32_t taskID;
    uint32_t serviceHandle;
} CmsCmdContent;

typedef struct {
    MsgType type;       /**< cmd type, decide the data structure below */
    SvcIdentity target; /**< serviceHandle or targetTaskId, depending on type */
    uint32_t code;
    uint32_t flag;
    uint64_t timestamp;
    uint32_t dataSz;    /**< size of data */
    void* data;
    uint32_t spObjNum;
    void* offsets;
    uint32_t processID; /**< filled by kernel, processId of sender/reciever */
    uint32_t taskID;    /**< filled by kernel, taskId of sender/reciever */
    uint32_t userID;
    uint32_t gid;
} IpcMsg;

#define SEND (1 << 0)
#define RECV (1 << 1)
#define BUFF_FREE (1 << 2)

typedef struct {
    uint32_t flag;
    IpcMsg* outMsg; /**< data to send to target */
    IpcMsg* inMsg;  /**< data reply by target */
    void* buffToFree;
} IpcContent;

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
