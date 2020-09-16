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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "utils.h"
#include <gtest/gtest.h>
#include "log.h"

// init rand seed at startup
__attribute__((constructor)) static void Initialize(void)
{
    LOGD("srand(time(0)) is called.");
    srand(time(0));
}

int CheckValueClose(double target, double actual, double accuracy)
{
    double diff = actual - target;
    if (diff < 0) {
        diff = -diff;
    }
    double pct = diff / actual;
    LOGD("diff=%f, pct=%f\n", diff, pct);
    return (pct <= accuracy);
}

const int SYS_US_PER_MS = 1000;
void Msleep(int msec)
{
    usleep(msec * SYS_US_PER_MS);
}

int KeepRun(int msec)
{
    struct timespec time1 = {0, 0};
	struct timespec time2 = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &time1);
    LOGD("KeepRun start : tv_sec=%ld, tv_nsec=%ld\n", time1.tv_sec, time1.tv_nsec);
    int loop = 0;
    int runned = 0;
    while (runned < msec) {
        ++loop;
        clock_gettime(CLOCK_MONOTONIC, &time2);
        runned = (time2.tv_sec - time1.tv_sec) * 1000 + (time2.tv_nsec - time1.tv_nsec) / 1000000;
    }
    LOGD("KeepRun end : tv_sec=%ld, tv_nsec=%ld\n", time2.tv_sec, time2.tv_nsec);
    return loop;
}

// check process state use 'waitpid'
int CheckProcStatus(pid_t pid, int* code, int flag)
{
    int status;
    int rt = waitpid(pid, &status, flag);
    errno = 0;
    if (rt == -1) {
        LOGE("waitpid return -1, errno=%d:%s\n", errno, strerror(errno));
        return -1;
    } else if (rt == 0) {
        return 0;
    } else if (rt != pid) { // waitpid return error
        if (errno) {
            LOGE("waitpid return error, rt=%d, errno=%d:%s\n", rt, errno, strerror(errno));
        } else {
            LOGE("waitpid return error, errno is not set(no more info)\n");
        }
        return -2;
    }

    if (WIFEXITED(status)) {
		*code = WEXITSTATUS(status);
        return 1;
    } else if (WIFSIGNALED(status)) {
		*code = WTERMSIG(status);
        return 2;
    } else if (WIFSTOPPED(status)) {
        *code = WSTOPSIG(status);
        return 3;
    }
    return 4;
}

// start a elf, only check if execve success or not
static int StartElf(const char* fname, char* const argv[], char* const envp[])
{
    int pid = fork();
    if (pid == -1) {
        LOGE("ERROR: Fork Error, errno=%d, err=%s\n", errno, strerror(errno));
        return -1;
    } else if (pid == 0) { // child
        errno = 0;
        int rt = execve(fname, argv, envp);
        if (rt == -1) {
            LOGE("ERROR: execve return -1, errno=%d, err=%s\n", errno, strerror(errno));
            exit(EXECVE_RETURN_ERROR);
        }
        LOGE("ERROR: execve should never return on success. rt=%d, errno=%d, err=%s\n", rt, errno, strerror(errno));
        exit(EXECVE_RETURN_OK);
    }
    return pid;
}

int RunElf(const char* fname, char* const argv[], char* const envp[], int timeoutSec)
{
    int isTimeout = 0;
    int status;
    int exitCode;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);

    int pid = StartElf(fname, argv, envp);
    if (pid == -1) { // fork error
        return -1;
    }

    if (timeoutSec > 0) {
        struct timespec time1 = {timeoutSec, 0};
        if (sigtimedwait(&set, 0, &time1) == -1) {
            if (errno == EAGAIN) {
                isTimeout = 1;
            } else {
                LOGE("ERROR: sigtimedwait FAIL: %s\n", strerror(errno));
                return -1;
            }
            if (kill(pid, SIGKILL) == -1) {
                LOGE("ERROR: kill child FAIL: %s\n", strerror(errno));
                return -1;
            }
        }
        // else: sigtimedwait return ok, child has exited already, nothing else to do
    }
    int rt = CheckProcStatus(pid, &exitCode, 0);
    if ((rt <= 0) || (exitCode == EXECVE_RETURN_OK) || (exitCode == EXECVE_RETURN_ERROR)) {
        return -1;
    }
    if (isTimeout) {
        LOGE("ERROR: child execute timed out!\n");
        return -2;
    }
    return exitCode;
}

int StartExecveError(const char* fname, char* const argv[], char* const envp[])
{
    pid_t pid = fork();
    if (pid == -1) {
        LOGE("ERROR: Fork Error, errno=%d, err=%s\n", errno, strerror(errno));
        return -1;
    } else if (pid == 0) { // child
        int rt = execve(fname, argv, envp);
        if (rt == -1) {
            LOG("ERROR: execve return -1, errno=%d, err=%s\n", errno, strerror(errno));
            exit(errno);
        }
        LOGE("ERROR: execve should never return on success. rt=%d, errno=%d, err=%s\n", rt, errno, strerror(errno));
        exit(EXECVE_RETURN_OK);
    }
    // parent
    Msleep(30);
    int exitCode;
    int procStat = CheckProcStatus(pid, &exitCode);
    LOG("procStat=%d, exitCode=%d\n", procStat, exitCode);
    if (procStat != 1) {
        return -3;
    } else if (exitCode == EXECVE_RETURN_OK) {
        return -2;
    } else {
        return exitCode;
    }
}

// Get a pid number that currently not exist
// by creat a child process and exit.
pid_t GetNonExistPid()
{
    pid_t pid = fork();
    if (pid < 0) {
        LOG("fork error, wait 5 seconds than try angain...");
        sleep(5);
        pid = fork();
        if (pid < 0) {
            LOG("still fork error!");
            return -1;
        }
    }
    if (pid > 0) { // parent
        Msleep(20);
        if (waitpid(pid, NULL, 0) != pid) {
            LOG("waitpid failed, errno = %d", errno);
            return -1;
        }
    } else { // child
        exit(0);
    }
    return pid;
}

// return n: 0 < n <= max
uint32_t GetRandom(uint32_t max)
{
    if (max == 0 || max == 1) {
        return 1;
    }
    return (rand() % max) + 1;
}
