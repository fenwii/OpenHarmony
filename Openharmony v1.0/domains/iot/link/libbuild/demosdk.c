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
#include "demosdk.h"

#include <stdio.h>

#include "demosdk_adapter.h"

#define TASK_STACK_SIZE 1000
#define TASK_PRIO 20
#define SECOND_CNT 1000

void *DemoSdkBiz(const char *arg)
{
    (void)arg;
    while (1) {
        printf("it is demo biz: hello world.\n");
        DemoSdkSleepMs(SECOND_CNT);
    }
    return NULL;
}

int DemoSdkEntry(void)
{
    printf("it is demosdk entry.\n");
    struct TaskPara para = {0};
    para.name = "demotask";
    para.func = (void *)DemoSdkBiz;
    para.prio = TASK_PRIO;
    para.size = TASK_STACK_SIZE;
    unsigned int handle;
    int ret = DemoSdkCreateTask(&handle, &para);
    if (ret != 0) {
        printf("create task fail.\n");
        return -1;
    }
    return 0;
}
