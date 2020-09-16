/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define _GNU_SOURCE    // syscall function need this macro definition
#include "init_adapter.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#ifdef __LINUX__
#include <sys/reboot.h>
#else
#include <sys/syscall.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

void RebootSystem()
{
#ifdef __LINUX__
    int ret = reboot(RB_DISABLE_CAD);
#else
    int ret = syscall(__NR_shellexec, "reset", "reset");
#endif
    if (ret != 0) {
        printf("[Init] reboot failed! syscall ret %d, err %d.\n", ret, errno);
    }
}

int KeepCapability()
{
#ifdef __LINUX__
    if (prctl(PR_SET_KEEPCAPS, 1)) {
        printf("[Init] prctl failed\n");
        return -1;
    }
#endif
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
