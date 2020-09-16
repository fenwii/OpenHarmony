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

#ifndef KERNEL_LITE_UTILS
#define KERNEL_LITE_UTILS

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>


// check if 'actual' is close to 'target', within 5% in default
int CheckValueClose(double target, double actual, double accuracy = 0.05);

// sleep n millisecond(1/1000 sec)
void Msleep(int n);

/**
 * desc:   check process state use 'waitpid'
 * input:  pid  -- target pid
 *         code -- store exit code or signal number
 *         flag -- flag for waitpid, default to WNOHANG
 * output: -1 -- waitpid return -1
 *         -2 -- waitpid return value error(not -1 and not pid)
 *          0 -- target process still alive
 *          1 -- target process existd, exist code is set in 'code'
 *          2 -- target process killed by a signal, signal number is set in 'code'
 *          3 -- target process is stopped,  signal number is set in 'code'
 *          4 -- get target process state error, due to waitpid error
 */
int CheckProcStatus(pid_t pid, int* code, int flag = WNOHANG);

// make sure process is still alive
#define AssertProcAlive(pid)  do {                                        \
        int exitCode;                                                     \
        int procStat = CheckProcStatus(pid, &exitCode);                   \
        ASSERT_EQ(procStat, 0) << "target process should still alive.\n"; \
    } while (0)
#define ExpectProcAlive(pid)  do {                                        \
        int exitCode;                                                     \
        int procStat = CheckProcStatus(pid, &exitCode);                   \
        EXPECT_EQ(procStat, 0) << "target process should still alive.\n"; \
    } while (0)

// make sure process exited with exitCode 0
#define AssertProcExitedOK(pid)  do {                                  \
        int exitCode;                                                  \
        int procStat = CheckProcStatus(pid, &exitCode);                \
        EXPECT_EQ(procStat, 1);                                        \
        ASSERT_EQ(exitCode, 0) << "target process should exited 0.\n"; \
    } while (0)
#define ExpectProcExitedOK(pid)  do {                                  \
        int exitCode;                                                  \
        int procStat = CheckProcStatus(pid, &exitCode);                \
        EXPECT_EQ(procStat, 1);                                        \
        EXPECT_EQ(exitCode, 0) << "target process should exited 0.\n"; \
    } while (0)

// make sure process killed by signal signum
#define AssertProcKilled(pid, signum)  do {                                          \
        int exitCode;                                                                \
        int procStat = CheckProcStatus(pid, &exitCode);                              \
        ASSERT_EQ(procStat, 2);                                                      \
        ASSERT_EQ(exitCode, signum) << "target process should killed by " << signum; \
    } while (0)
#define ExpectProcKilled(pid, signum)  do {                                          \
        int exitCode;                                                                \
        int procStat = CheckProcStatus(pid, &exitCode);                              \
        EXPECT_EQ(procStat, 2);                                                      \
        EXPECT_EQ(exitCode, signum) << "target process should killed by " << signum; \
    } while (0)


// keep current process run for a specific time, no sleep.
// msec is millisecond (1/1000 sec).
// return value is the loop count(generally you don't need to care about it)
int KeepRun(int msec);

/**
 * code to determain if execve is faild, may confic with actual sub program's exit code
 */
const int EXECVE_RETURN_ERROR = 190;  // execve return -1
const int EXECVE_RETURN_OK    = 191;  // execve return not -1: execve should never return on success

/**
 * desc:   start a elf, check if execve success, and return child process exit code within timeout_sec
 * input:  fname, argv, envp -- parameters for execve
 *         timeout_sec       -- timeout of the child executing, default: 5 seconds.
 *                              timeout_sec<=0 means no timeout, wait forever until child exit.
 * output: -1 -- something wrong for internal syscall, check log for detail
 *         -2 -- child does not finish in 'timeout_sec'
 *     n(>=0) -- child exit code
 */
int RunElf(const char* fname, char* const argv[], char* const envp[], int timeoutSec = 5);

/**
 * desc:   call execve with error parameters(e.g. a non-exist file)
 * input:  fname, argv, envp -- parameters for execve
 * output:  0 -- execve ok
 *         -1 -- unexpected fork error
 *         -2 -- unexpected execve error
 *         -3 -- unknow error
 *      n(>0) -- errno of execve
 */
int StartExecveError(const char* fname, char* const argv[], char* const envp[]);

// Get a pid number that currently not exist
pid_t GetNonExistPid();

/**
 * return random number n: 0 < n <= max
 * we found in most case '0' is not expected.
 */
uint32_t GetRandom(uint32_t max);

#endif