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

#include "init_service.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "init_adapter.h"
#include "init_perms.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define CAP_NUM 2

// 240 seconds, 4 minutes
static const int CRASH_TIME_LIMIT  = 240;
// maximum number of crashes within time CRASH_TIME_LIMIT for one service
static const int CRASH_COUNT_LIMIT = 4;

static int SetPerms(const Service *service)
{
    if (KeepCapability() != 0) {
        return SERVICE_FAILURE;
    }

    if (setgid(service->servPerm.gID) != 0) {
        return SERVICE_FAILURE;
    }

    if (setuid(service->servPerm.uID) != 0) {
        return SERVICE_FAILURE;
    }

    // umask call always succeeds and return the previous mask value which is not needed here
    (void)umask(DEFAULT_UMASK_INIT);

    struct __user_cap_header_struct capHeader;
    capHeader.version = _LINUX_CAPABILITY_VERSION_3;
    capHeader.pid = 0;

    struct __user_cap_data_struct capData[CAP_NUM] = {0};
    for (unsigned int i = 0; i < service->servPerm.capsCnt; ++i) {
        if (service->servPerm.caps[i] == FULL_CAP) {
            for (int i = 0; i < CAP_NUM; ++i) {
                capData[i].effective = FULL_CAP;
                capData[i].permitted = FULL_CAP;
                capData[i].inheritable = FULL_CAP;
            }
            break;
        }
        capData[CAP_TO_INDEX(service->servPerm.caps[i])].effective |= CAP_TO_MASK(service->servPerm.caps[i]);
        capData[CAP_TO_INDEX(service->servPerm.caps[i])].permitted |= CAP_TO_MASK(service->servPerm.caps[i]);
        capData[CAP_TO_INDEX(service->servPerm.caps[i])].inheritable |= CAP_TO_MASK(service->servPerm.caps[i]);
    }

    if (capset(&capHeader, capData) != 0) {
        return SERVICE_FAILURE;
    }
    return SERVICE_SUCCESS;
}

int ServiceStart(Service *service)
{
    if (service->attribute & SERVICE_ATTR_INVALID) {
        printf("[Init] start service %s invalid.\n", service->name);
        return SERVICE_FAILURE;
    }

    struct stat pathStat = {0};
    service->attribute &= (~(SERVICE_ATTR_NEED_RESTART | SERVICE_ATTR_NEED_STOP));
    if (stat(service->path, &pathStat) != 0) {
        service->attribute |= SERVICE_ATTR_INVALID;
        printf("[Init] start service %s invalid, please check %s.\n", service->name, service->path);
        return SERVICE_FAILURE;
    }

    int pid = fork();
    if (pid == 0) {
        // permissions
        if (SetPerms(service) != SERVICE_SUCCESS) {
            printf("[Init] service %s exit! set perms failed! err %d.\n", service->name, errno);
            _exit(0x7f); // 0x7f: user specified
        }

        char* argv[] = {service->name, NULL};
        char* env[] = {NULL};
        if (execve(service->path, argv, env) != 0) {
            printf("[Init] service %s execve failed! err %d.\n", service->name, errno);
        }
        _exit(0x7f); // 0x7f: user specified
    } else if (pid < 0) {
        printf("[Init] start service %s fork failed!\n", service->name);
        return SERVICE_FAILURE;
    }

    service->pid = pid;
    printf("[Init] start service %s succeed, pid %d.\n", service->name, service->pid);
    return SERVICE_SUCCESS;
}

int ServiceStop(Service *service)
{
    service->attribute &= ~SERVICE_ATTR_NEED_RESTART;
    service->attribute |= SERVICE_ATTR_NEED_STOP;
    if (service->pid <= 0) {
        return SERVICE_SUCCESS;
    }

    if (kill(service->pid, SIGKILL) != 0) {
        printf("[Init] stop service %s pid %d failed! err %d.\n", service->name, service->pid, errno);
        return SERVICE_FAILURE;
    }

    printf("[Init] stop service %s, pid %d.\n", service->name, service->pid);
    return SERVICE_SUCCESS;
}

void ServiceReap(Service *service)
{
    service->pid = -1;

    // stopped by system-init itself, no need to restart even if it is not one-shot service
    if (service->attribute & SERVICE_ATTR_NEED_STOP) {
        service->attribute &= (~SERVICE_ATTR_NEED_STOP);
        service->crashCnt = 0;
        return;
    }

    // for one-shot service
    if (service->attribute & SERVICE_ATTR_ONCE) {
        // no need to restart
        if (!(service->attribute & SERVICE_ATTR_NEED_RESTART)) {
            service->attribute &= (~SERVICE_ATTR_NEED_STOP);
            return;
        }
        // the service could be restart even if it is one-shot service
    }

    // the service that does not need to be restarted restarts, indicating that it has crashed
    if (!(service->attribute & SERVICE_ATTR_NEED_RESTART)) {
        // crash time and count check
        time_t curTime = time(NULL);
        if (service->crashCnt == 0) {
            service->firstCrashTime = curTime;
            ++service->crashCnt;
        } else if (difftime(curTime, service->firstCrashTime) > CRASH_TIME_LIMIT) {
            service->firstCrashTime = curTime;
            service->crashCnt = 1;
        } else {
            ++service->crashCnt;
            if (service->crashCnt > CRASH_COUNT_LIMIT) {
                printf("[Init] reap service %s, crash too many times!\n", service->name);
                return;
            }
        }
    }

    int ret = ServiceStart(service);
    if (ret != SERVICE_SUCCESS) {
        printf("[Init] reap service %s start failed!\n", service->name);
    }

    service->attribute &= (~SERVICE_ATTR_NEED_RESTART);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
