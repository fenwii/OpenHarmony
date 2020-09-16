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
#define _GNU_SOURCE
#include "appspawn_process.h"
#include <errno.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "appspawn_adapter.h"
#include "log.h"
#include "securec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define DEFAULT_UMASK 022
#define CAP_NUM 2
#define ABILITY_EXE_FILE_FULL_PATH "/bin/abilityMain"
#define ABILITY_EXE_FILE_NAME "abilityMain"
#define ENV_TITLE "LD_LIBRARY_PATH="
#define UPPER_BOUND_GID   999
#define LOWER_BOUND_GID   100
#define GRP_NUM 2
#define DEVMGR_GRP 99

static const unsigned int MAX_IDENTITY_ID_LENGTH = 25;
static const unsigned int MAX_PROCESS_NAME_LENGTH = 130;

static int SetPerms(uid_t uID, gid_t gID)
{
    gid_t groups[GRP_NUM];

    if (KeepCapability() != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] KeepCapability failed, uID %{public}u, err: %{public}d.",\
            uID, errno);
        return -1;
    }

    if (setuid(uID) != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] setuid failed, uID %{public}u, err: %{public}d.",\
            uID, errno);
        return -1;
    }

    if (setgid(gID) != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] setgid failed, gID %{public}u, err: %{public}d.",\
            gID, errno);
        return -1;
    }

    // add device groups for system app
    if (gID >= LOWER_BOUND_GID && gID <= UPPER_BOUND_GID) {
        groups[0] = gID;
        groups[1] = DEVMGR_GRP;
        if (setgroups(GRP_NUM, groups)) {
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] setgroups failed, uID %{public}u, err: %{public}d.",\
                uID, errno);
            return -1;
        }
    }

    // umask call always succeeds and return the previous mask value which is not needed here
    (void)umask(DEFAULT_UMASK);

    struct __user_cap_header_struct capHeader;
    capHeader.version = _LINUX_CAPABILITY_VERSION_3;
    capHeader.pid = 0;

    // common user, clear all caps
    struct __user_cap_data_struct capData[CAP_NUM] = {0};

    if (capset(&capHeader, capData) != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] capset failed, err: %{public}d.", errno);
        return -1;
    }
    return 0;
}

static char* GetEnvStrs(const MessageSt* msgSt)
{
    size_t totalLen = strlen(ENV_TITLE) + strlen(msgSt->sharedLibPaths);
    char* envStr = (char*)malloc(totalLen + 1);
    if (envStr == NULL) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] malloc for env failed! len %{public}u.", totalLen);
        return NULL;
    }

    if (memset_s(envStr, totalLen + 1, '\0', totalLen + 1) != EOK) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] memset_s for env failed.");
        free(envStr);
        return NULL;
    }

    if (sprintf_s(envStr, totalLen + 1, "%s%s", ENV_TITLE, msgSt->sharedLibPaths) <= 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] sprintf_s for env failed. libPath %{public}s",\
            msgSt->sharedLibPaths);
        free(envStr);
        return NULL;
    }
    return envStr;
}

pid_t CreateProcess(const MessageSt* msgSt)
{
    char identityIDStr[MAX_IDENTITY_ID_LENGTH];
    char processNameStr[MAX_PROCESS_NAME_LENGTH];
    if (memset_s(identityIDStr, MAX_IDENTITY_ID_LENGTH, '\0', MAX_IDENTITY_ID_LENGTH) != EOK ||
        memset_s(processNameStr, MAX_PROCESS_NAME_LENGTH, '\0', MAX_PROCESS_NAME_LENGTH) != EOK) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] create service, memset_s failed.");
        return -1;
    }

    if (sprintf_s(identityIDStr, MAX_IDENTITY_ID_LENGTH, "%llu", msgSt->identityID) <= 0 ||
        sprintf_s(processNameStr, MAX_PROCESS_NAME_LENGTH, "%s", msgSt->bundleName) <= 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] sprintf_s failed. id %{public}llu, name %{public}s.",\
            msgSt->identityID, msgSt->bundleName);
        return -1;
    }

    char* envStr = GetEnvStrs(msgSt);
    if (envStr == NULL) {
        return -1;
    }

    // check if the exe file exists
    struct stat pathStat = {0};
    if (stat(ABILITY_EXE_FILE_FULL_PATH, &pathStat) != 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] stat %{public}s failed, err %{public}d.",\
            ABILITY_EXE_FILE_FULL_PATH, errno);
        free(envStr);
        return -1;
    }

    pid_t newPID = fork();
    if (newPID < 0) {
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] create process, fork failed! err %{public}d.", errno);
        free(envStr);
        return -1;
    }

    // in child process
    if (newPID == 0) {
        // set permissions
        if (SetPerms(msgSt->uID, msgSt->gID) != 0) {
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] process %{public}s exit!", processNameStr);
            _exit(0x7f); // 0x7f: user specified
        }

        char* argv[] = {ABILITY_EXE_FILE_NAME, identityIDStr, processNameStr, NULL};
        char* env[] = {envStr, NULL};
        if (execve(ABILITY_EXE_FILE_FULL_PATH, argv, env) != 0) {
            HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] execve %{public}s failed! err %{public}d.",\
                ABILITY_EXE_FILE_FULL_PATH, errno);
        }
        HILOG_ERROR(HILOG_MODULE_HIVIEW, "[appspawn] sub-process exit, pid %{public}d.", getpid());
        _exit(0x7f); // 0x7f: user specified
    }

    free(envStr);
    return newPID;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
