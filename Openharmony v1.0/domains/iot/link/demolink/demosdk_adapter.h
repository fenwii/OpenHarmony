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

#ifndef DEMOSDK_ADAPTER_H
#define DEMOSDK_ADAPTER_H

#define DEMOSDK_ERR (-1)
#define DEMOSDK_OK 0

struct TaskPara {
    char *name;
    void *(*func)(char* arg);
    void *arg;
    unsigned char prio;
    unsigned int size;
};

int DemoSdkCreateTask(unsigned int *handle, const struct TaskPara *para);
void DemoSdkSleepMs(int ms);

#endif
