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

#include "hiview_util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "los_hwi.h"
#include "cmsis_os.h"
#include "utils_file.h"

extern void HAL_NVIC_SystemReset(void);
extern void __disable_irq(void);
extern void __enable_irq(void);

#define HIVIEW_WAIT_FOREVER           0xFFFFFFFF
#define HIVIEW_MS_PER_SECOND          1000

void *HIVIEW_MemAlloc(uint8 modId, uint32 size)
{
    (void)modId;
    return malloc(size);
}

void HIVIEW_MemFree(uint8 modId, void *pMem)
{
    (void)modId;
    free(pMem);
}

uint64 HIVIEW_GetCurrentTime()
{
    return osKernelGetTickCount();
}

int32 HIVIEW_RtcGetCurrentTime(uint64 *val, HIVIEW_RtcTime *time)
{
    (void)val;
    (void)time;
    return HOS_SUCCESS;
}

HiviewMutexId_t HIVIEW_MutexInit()
{
    return (HiviewMutexId_t)osMutexNew(NULL);
}

void HIVIEW_MutexLock(HiviewMutexId_t mutex)
{
    if (OS_INT_ACTIVE) {
        __disable_irq();
        return;
    }

    if (mutex == NULL) {
        return;
    }
    osMutexAcquire((osMutexId_t)mutex, HIVIEW_WAIT_FOREVER);
}

void HIVIEW_MutexUnlock(HiviewMutexId_t mutex)
{
    if (OS_INT_ACTIVE) {
        __enable_irq();
        return;
    }

    if (mutex == NULL) {
        return;
    }
    osMutexRelease((osMutexId_t)mutex);
}

uint32 HIVIEW_GetTaskId()
{
    return (uint32)osThreadGetId();
}

void HIVIEW_UartPrint(const char *str)
{
    printf("%s", str);
}

void HIVIEW_Sleep(uint32 ms)
{
    osDelay(ms / HIVIEW_MS_PER_SECOND);
}

/* Create the directory */
int32 HIVIEW_FileMakeDir(const char *dir)
{
    return UtilsFileOpen(dir, O_CREAT_FS, O_RDWR_FS);
}

int32 HIVIEW_FileOpen(const char *path)
{
    return UtilsFileOpen(path, O_RDWR_FS | O_CREAT_FS, O_RDWR_FS);
}

int32 HIVIEW_FileClose(int32 handle)
{
    return UtilsFileClose(handle);
}

int32 HIVIEW_FileRead(int32 handle, uint8 *buf, uint32 len)
{
    return UtilsFileRead(handle, (char *)buf, len);
}

int32 HIVIEW_FileWrite(int32 handle, const uint8 *buf, uint32 len)
{
    return UtilsFileWrite(handle, (const char *)buf, len);
}

int32 HIVIEW_FileSeek(int32 handle, int32 offset, int32 whence)
{
    return UtilsFileSeek(handle, offset, whence);
}

int32 HIVIEW_FileUnlink(const char *path)
{
    return UtilsFileDelete(path);
}

void HIVIEW_WatchDogSystemReset()
{
    /* reset MCU Core */
    HAL_NVIC_SystemReset();
}

uint8 HIVIEW_WdgResetFlag()
{
    /* Depend:HAL_WdgGetResetFlag */
    return 1;
}
