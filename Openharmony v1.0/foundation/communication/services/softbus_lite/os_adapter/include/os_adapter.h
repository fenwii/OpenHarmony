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
#ifndef OS_ADAPTER_H
#define OS_ADAPTER_H
#include <stdint.h>
#include <stdio.h>
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#include "los_sem.h"
#else
#include "pms_interface.h"
#include "pms_types.h"
#include <semaphore.h>
#endif

#ifdef SOFTBUS_DEBUG
#define SOFTBUS_PRINT(format, ...) printf (format, ##__VA_ARGS__)
#else
#define SOFTBUS_PRINT(format, ...)
#endif
#ifdef __cplusplus
extern "C" {
#endif
int SemCreate(unsigned short count, unsigned long *semHandle);
int SemDelete(const unsigned long *semHandle);
int SemWait(const unsigned long *semHandle);
int SemPost(const unsigned long *semHandle);
void CloseSocket(int *fd);
int WriteMsgQue(unsigned int queueID,
    const void *bufferAddr,
    unsigned int bufferSize);
int CreateMsgQue(const char *queueName,
    unsigned short len,
    unsigned int *queueID,
    unsigned int flags,
    unsigned short maxMsgSize);
int DeleteMsgQue(unsigned int queueID);
int ReadMsgQue(unsigned int queueID,
    void *bufferAddr,
    unsigned int *bufferSize);
int SoftBusCheckPermission(const char* permissionName);
#ifdef __cplusplus
}
#endif
#endif
