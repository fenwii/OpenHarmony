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

#include <mqueue.h>
#include <pthread.h>
#include <unistd.h>

int SemCreate(unsigned short count, unsigned long *semHandle)
{
    if (semHandle == NULL) {
        return -1;
    }

    (void)count;
    int ret = sem_init((sem_t *)semHandle, 1, 0);
    if (ret == 0) {
        return sem_post((sem_t *)semHandle);
    }
    return ret;
}

int SemDelete(const unsigned long *semHandle)
{
    if (semHandle == NULL) {
        return -1;
    }
    return sem_destroy((sem_t *)semHandle);
}

int SemWait(const unsigned long *semHandle)
{
    if (semHandle == NULL) {
        return -1;
    }
    return sem_wait((sem_t *)semHandle);
}

int SemPost(const unsigned long *semHandle)
{
    if (semHandle == NULL) {
        return -1;
    }
    return sem_post((sem_t *)semHandle);
}

void CloseSocket(int *fd)
{
    if (fd == NULL) {
        return;
    }
    if (*fd >= 0) {
        close(*fd);
        *fd = -1;
    }
}

int CreateMsgQue(const char *queueName,
    unsigned short len, unsigned int *queueID,
    unsigned int flags, unsigned short maxMsgSize)
{
    if (queueName == NULL || queueID == NULL) {
        return -1;
    }

    struct mq_attr newAttr = {0};
    newAttr.mq_flags = flags;
    newAttr.mq_maxmsg = len;
    newAttr.mq_msgsize = maxMsgSize;
    int mqd = mq_open(queueName, O_RDWR | O_CREAT, &newAttr);
    if (mqd < 0) {
        return -1;
    }

    *queueID = mqd;
    return 0;
}

int WriteMsgQue(unsigned int queueID,
    const void *bufferAddr, unsigned int bufferSize)
{
    if (bufferAddr == NULL) {
        return -1;
    }
    return mq_send(queueID, bufferAddr, bufferSize, 0);
}

int DeleteMsgQue(unsigned int queueID)
{
    return mq_close(queueID);
}

int ReadMsgQue(unsigned int queueID,
    void *bufferAddr, unsigned int *bufferSize)
{
    if (bufferAddr == NULL || bufferSize == NULL) {
        return -1;
    }
    unsigned int readSize = *bufferSize;
    unsigned int receiveSize = mq_receive(queueID, bufferAddr, readSize, 0);
    if (receiveSize != readSize) {
        return -1;
    }

    *bufferSize = receiveSize;
    return 0;
}

int SoftBusCheckPermission(const char* permissionName)
{
    if (permissionName == NULL) {
        return -1;
    }

    if (CheckPermission(0, permissionName) != GRANTED) {
        SOFTBUS_PRINT("[SOFTBUS] CheckPermission fail\n");
        return -1;
    }
    return 0;
}
