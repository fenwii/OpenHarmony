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

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "log.h"
#include "utils.h"
#include "SignalTest.h"

using namespace testing::ext;

// static membor must init before use.
int IpcSignalTest::mReceivedSignal = 0;
siginfo_t IpcSignalTest::mSiginfo;
const char* IpcSignalTest::mAbortPipeName = "/dev/AbortPipe001";

// special signal hander for function 'abort'
void IpcSignalTest::SigAbortHandler(int signum)
{
    LOG("hander: recv a signal: %d", signum);
    int fd = open(mAbortPipeName, O_WRONLY);
    // use mAbortPipeName as message
    int rt = write(fd, mAbortPipeName, strlen(mAbortPipeName));
    LOG("hander: pipe write rt=%d, errno=%d", rt, errno);
    close(fd);
}

// special signal handler for function 'sigaction'
void IpcSignalTest::SigactionHandler(int signum, siginfo_t* si, void* ucontext)
{
    LOG("hander recv a signal: %s(%d)", ALL_SIGNALS[signum].signame, signum);
    mReceivedSignal = signum;
    // siginfo_t para is not supported yet
}

// general signal hander
void IpcSignalTest::SignalHandler(int signum)
{
    LOG("hander recv a signal: %s(%d)", ALL_SIGNALS[signum].signame, signum);
    mReceivedSignal = signum;
}

SignalNameAction const ALL_SIGNALS[MAX_SIGNAL + 1] = {
    {"NA", TERMINATE},
    {"SIGHUP", 	  TERMINATE}, // 1
    {"SIGINT",	  TERMINATE},
    {"SIGQUIT",	  COREDUMP},
    {"SIGILL",	  COREDUMP},
    {"SIGTRAP",	  COREDUMP},
    {"SIGABRT",	  COREDUMP},  // alias: SIGIOT
    {"SIGBUS",	  COREDUMP},
    {"SIGFPE",	  COREDUMP},
    {"SIGKILL",	  TERMINATE},
    {"SIGUSR1",	  TERMINATE},
    {"SIGSEGV",	  COREDUMP},
    {"SIGUSR2",	  TERMINATE},
    {"SIGPIPE",	  TERMINATE},
    {"SIGALRM",	  TERMINATE},
    {"SIGTERM",	  TERMINATE},
    {"SIGSTKFLT", TERMINATE},
    {"SIGCHLD",	  IGNORE},    // alias: SIGCLD
    {"SIGCONT",	  CONTINUE},
    {"SIGSTOP",	  STOP},
    {"SIGTSTP",	  STOP},
    {"SIGTTIN",	  STOP},
    {"SIGTTOU",	  STOP},
    {"SIGURG",	  IGNORE},
    {"SIGXCPU",	  COREDUMP},
    {"SIGXFSZ",	  COREDUMP},
    {"SIGVTALRM", TERMINATE},
    {"SIGPROF",	  TERMINATE},
    {"SIGWINCH",  IGNORE},
    {"SIGIO",	  TERMINATE}, // alias: SIGPOLL
    {"SIGPWR",	  TERMINATE}  // alias: SIGINFO, 30
};

void IpcSignalTest::DefaultActionTest(int signum, bool expectStop, bool coredump)
{
    int status, rt;
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid > 0) { // parent
        Msleep(20);
        kill(pid, signum);
        if (!expectStop) {
            Msleep(20);
            AssertProcAlive(pid);
            Msleep(100);
            AssertProcExitedOK(pid);
        } else {
            Msleep(20);
            AssertProcKilled(pid, signum);
            if (coredump) {
                // todo: check codedump, liteos not support yet
            }
        }
    } else { // child
        KeepRun(100);
        if (expectStop) {
            LOG("Child should has been Terminated, but still alive.");
            exit(1);
        }
        exit(0);
    }
}

void IpcSignalTest::SendAndRecvTest(int signum)
{
    pid_t pid1, pid2;
    int status, rt;
    bool useBrother = GetRandom(100) % 2; // if use brother to send the signal
    pid1 = fork();
    ASSERT_TRUE(pid1 >= 0) << "======== Fork1 Error! =========";
    if (pid1 > 0) { // parent
        LOGD("in parent...");
        if (useBrother) {
            pid2 = fork();
            ASSERT_TRUE(pid2 >= 0) << "======== Fork2 Error! =========";
            if (pid2 == 0) { // child 2
                Msleep(50);
                kill(pid1, signum);
                exit(0);
            }
            // parent
            Msleep(100);
            LOG("check if child2 exited OK");
            AssertProcExitedOK(pid2);
        } else {
            Msleep(100);
            kill(pid1, signum);
        }
        AssertProcAlive(pid1);

        Msleep(200); // child should exited now
        LOG("check if child exited OK");
        AssertProcExitedOK(pid1);
    } else { // child 1, the receiver
        LOGD("in child, pid=%d", getpid());
        signal(signum, SignalHandler);
        Msleep(150);
        if (mReceivedSignal != signum) {
            LOG("SignalHandler check fail, expected=%d, received=%d", signum, mReceivedSignal);
            exit(1);
        }
        LOGD("child sleeping....");
        Msleep(20);
        LOGD("child exit 0....");
        exit(0);
    }
}

void IpcSignalTest::SignalFailTest(int signum, handler_type h, int expectErrno)
{
    errno = 0;
    handler_type rt = signal(signum, h);
    ASSERT_EQ(rt, SIG_ERR);
    ASSERT_EQ(errno, expectErrno);
}
void IpcSignalTest::SigpendingFailTest(sigset_t* pset)
{
    errno = 0;
    int rt = sigpending(pset);
    ASSERT_EQ(rt, -1);
    ASSERT_EQ(errno, EFAULT);
}
void IpcSignalTest::SigtimedwaitFailTest(const sigset_t *set, siginfo_t* info, const timespec* timeout, int expectErrno)
{
    errno = 0;
    int rt = sigtimedwait(set, info, timeout);
    ASSERT_EQ(rt, -1);
    ASSERT_EQ(errno, expectErrno);
}
