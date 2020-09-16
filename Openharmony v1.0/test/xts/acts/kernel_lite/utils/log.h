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

#ifndef KERNEL_LITE_LOG
#define KERNEL_LITE_LOG

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


const int SYS_NS_PER_US = 1000;
// get current time, for logging only
static char* GetCurTime(void)
{
    static char buff[20];
    struct timespec time1 = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &time1);
    snprintf(buff, sizeof(buff), "%ld:%06ld", time1.tv_sec, time1.tv_nsec / SYS_NS_PER_US);
    return buff;
}

#ifdef DEBUG
#define LOGD(format, ...) fprintf(stdout, "[%s] " format "\n", GetCurTime(), ##__VA_ARGS__)
#define LOG(format, ...)  fprintf(stdout, "[%s] " format "\n", GetCurTime(), ##__VA_ARGS__)
#else
#define LOGD(...)
#define LOG(format, ...)  fprintf(stdout, format "\n", ##__VA_ARGS__)
#endif

#define T_LOC2(l) __FILE__ ":" #l
#define T_LOC1(l) T_LOC2(l)
#define LOGE(format, ...)  fprintf(stdout,  "\n" T_LOC1(__LINE__) ": " format "\n", ##__VA_ARGS__)

#define PANIC(format, ...)   do {     \
        LOGE(format, ##__VA_ARGS__);  \
        exit(1);                      \
    } while (0)


#ifdef __cplusplus
}
#endif

#endif
