/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "os_adapter.h"

#include <los_queue.h>
#include <los_task.h>

#include "lwip/sockets.h"

int SemCreate(unsigned short count, unsigned long *semHandle)
{
    if (semHandle == NULL) {
        return -1;
    }
    int ret = LOS_SemCreate(count, (unsigned int*)semHandle);
    if (ret == 0) {
        return LOS_SemPost((unsigned int)*semHandle);
    }
    return ret;
}

int SemDelete(const unsigned long *semHandle)
{
    if (semHandle == NULL) {
        return -1;
    }
    return LOS_SemDelete((unsigned int)*semHandle);
}

int SemWait(const unsigned long *semHandle)
{
    if (semHandle == NULL) {
        return -1;
    }
    return LOS_SemPend((unsigned int)*semHandle, LOS_WAIT_FOREVER);
}

int SemPost(const unsigned long *semHandle)
{
    if (semHandle == NULL) {
        return -1;
    }
    return LOS_SemPost((unsigned int)*semHandle);
}

void CloseSocket(int *fd)
{
    if (fd == NULL) {
        return;
    }

    if (*fd >= 0) {
        closesocket(*fd);
        *fd = -1;
    }
}

int WriteMsgQue(unsigned int queueID, const void *bufferAddr, unsigned int bufferSize)
{
    if (bufferAddr == NULL) {
        return -1;
    }
    return LOS_QueueWriteCopy(queueID, (void*)bufferAddr, bufferSize, LOS_NO_WAIT);
}

int CreateMsgQue(const char *queueName,
    unsigned short len, unsigned int *queueID,
    unsigned int flags, unsigned short maxMsgSize)
{
    if (queueName == NULL || queueID == NULL) {
        return -1;
    }
    int ret = LOS_QueueCreate(queueName, len, queueID, flags, maxMsgSize);
    return ret;
}

int DeleteMsgQue(unsigned int queueID)
{
    return LOS_QueueDelete(queueID);
}

int ReadMsgQue(unsigned int queueID,
    void *bufferAddr, unsigned int *bufferSize)
{
    if (bufferAddr == NULL || bufferSize == NULL) {
        return -1;
    }
    return LOS_QueueReadCopy(queueID, bufferAddr, bufferSize, LOS_WAIT_FOREVER);
}

int SoftBusCheckPermission(const char* permissionName)
{
    if (permissionName == NULL) {
        return -1;
    }
    return 0;
}

