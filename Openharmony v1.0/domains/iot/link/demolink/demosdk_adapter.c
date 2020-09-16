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

#include "demosdk_adapter.h"
#include <stdio.h>

#include "kal.h"

#include "cmsis_os2.h"

#define MS_CNT 1000

int DemoSdkCreateTask(unsigned int *handle, const struct TaskPara *para)
{
    osThreadAttr_t attr = {0};
    osThreadId_t threadId;
    if (handle == 0 || para == 0) {
        return DEMOSDK_ERR;
    }

    if (para->func == 0) {
        return DEMOSDK_ERR;
    }

    if (para->name == 0) {
        return DEMOSDK_ERR;
    }

    attr.name = para->name;
    attr.priority = para->prio;
    attr.stack_size = para->size;
    threadId = osThreadNew((osThreadFunc_t)para->func, para->arg, &attr);
    if (threadId == 0) {
        printf("osThreadNew fail\n");
        return DEMOSDK_ERR;
    }

    *(unsigned int *)handle = (unsigned int)threadId;
    return DEMOSDK_OK;
}

void DemoSdkSleepMs(int ms)
{
    KalDelayUs(MS_CNT * ms);
}

