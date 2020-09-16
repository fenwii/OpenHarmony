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

#include "SignalTest.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "log.h"
#include "utils.h"

using namespace testing::ext;

/**
 * @tc.number SUB_KERNEL_IPC_SIGNAL_0100
 * @tc.name   test SIGKILL and SIGSTOP's action can not changed by signal
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSignalFailSig, TestSize.Level2)
{
    int rt, status;
    SignalFailTest(SIGKILL, SignalHandler);
    SignalFailTest(SIGKILL, SIG_IGN);
    SignalFailTest(SIGSTOP, SignalHandler);
    SignalFailTest(SIGSTOP, SIG_IGN);
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGTIMEDWAIT_0100
 * @tc.name   sigtimedwait still work even blocked by sigprocmask
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigtimedwaitBlock, TestSize.Level1)
{
    int rt, status;
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        signal(SIGSEGV, SignalHandler);
        struct timespec time1 = {0, 100*1000000};
        sigset_t sigmask, timeset;
        sigemptyset(&sigmask);
        sigaddset(&sigmask, SIGINT);
        sigaddset(&sigmask, SIGSEGV);
        sigemptyset(&timeset);
        sigaddset(&timeset, SIGSEGV);

        sigprocmask(SIG_BLOCK, &sigmask, 0);
        Msleep(80);

        rt = sigtimedwait(&timeset, 0, &time1);
        if (rt != SIGSEGV) {
            LOG("sigtimedwait return fail, expected:%d, actual:%d", SIGSEGV, rt);
            exitCode = 1;
        }

        // check the sigprocmask set not changed
        sigemptyset(&sigmask);
        sigprocmask(SIG_UNBLOCK, NULL, &sigmask);
        if (sigismember(&sigmask, SIGINT) != 1) {
            LOG("SIGINT should still in block set!");
            exitCode = 1;
        }
        if (sigismember(&sigmask, SIGSEGV) != 1) {
            LOG("SIGSEGV should still in block set!");
            exitCode = 1;
        }
        exit(exitCode);
    } else { // parent
        Msleep(40);
        kill(pid, SIGSEGV);
        Msleep(200);
        AssertProcExitedOK(pid);
    }
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    if (sigisemptyset(&pending)) {
        LOG("pending set empty");
        return;
    }
    LOG("========pending set not empty=========");
    if (sigismember(&pending, SIGCHLD)) {
        LOG("pending set is SIGCHLD");
        return;
    } else {
        LOG("pending set is not SIGCHLD!");
    }
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGTIMEDWAIT_0200
 * @tc.name   sigtimedwait error test: timeout or interupted.
 *            by now, liteos sigtimedwait cannot interupted
 *            so the interupte-check-code will run only when 'POSIX_TEST' is set
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigtimedwaitTimeout, TestSize.Level2)
{
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int rt;
        int exitCode = 0;
        sigset_t set;
        siginfo_t si;
        struct timespec ts = {0, 500*1000000};
        sigemptyset(&set);
        sigaddset(&set, SIGUSR1);

        struct timespec time1 = {0, 0};
        struct timespec time2 = {0, 0};
        errno = 0;
        clock_gettime(CLOCK_MONOTONIC, &time1);
        rt = sigtimedwait(&set, &si, &ts);
        clock_gettime(CLOCK_MONOTONIC, &time2);
        LOG("sigtimedwait returned: %d", rt);
        if (rt != -1 || errno != EAGAIN) {
            LOG("sigtimedwait error check fail, expected errno=%d(EAGAIN), actual=%d", EAGAIN, errno);
            exitCode = 1;
        }
        double duration = (time2.tv_sec - time1.tv_sec)*1000.0 + (time2.tv_nsec - time1.tv_nsec)/1000000.0;
        LOG("clock_gettime1 : tv_sec=%ld, tv_nsec=%ld", time1.tv_sec, time1.tv_nsec);
        LOG("clock_gettime2 : tv_sec=%ld, tv_nsec=%ld", time2.tv_sec, time2.tv_nsec);
        LOG("duration : %f ms", duration);
        if (CheckValueClose(1000, duration)) {
            LOG("Timeout value accuracy check fail, expected=1000, actual=%f", duration);
            exitCode = 1;
        }

        LOG("child exited with code=%d", exitCode);
        exit(exitCode);
    } else { // parent
        sleep(1);
        AssertProcExitedOK(pid);
    }
}


/**
 * @tc.number SUB_KERNEL_IPC_SIGTIMEDWAIT_0300
 * @tc.name   sigtimedwait siginfo_t test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigtimedwaitSiginfo, TestSize.Level2)
{
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        signal(SIGINT, SignalHandler);
        struct timespec time1 = {0, 100*1000000};
        sigset_t set;
        siginfo_t si;
        sigemptyset(&set);
        sigaddset(&set, SIGINT);
        int rt = sigtimedwait(&set, &si, &time1);
        if (rt != SIGINT) {
            LOG("sigtimedwait should return the signal, expected:%d, actual:%d", SIGINT, rt);
            exitCode = 1;
        }
        LOGD("si: %d,%d,%d,%p", si.si_signo, si.si_code, si.si_value.slval_int, si.si_value.slval_int);
        if (si.si_signo != SIGINT) {
            LOG("sigtimedwait set siginfo_t fail, si_signo=%d", si.si_signo);
            exitCode = 1;
        }
        // other area of siginfo_t is not supported yet, test code deleted
        LOG("child exited with code=%d", exitCode);
        exit(exitCode);
    } else { // parent
        Msleep(20);
        kill(pid, SIGINT);
        Msleep(100);
        AssertProcExitedOK(pid);
    }
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGWAITINFO_0100
 * @tc.name   test sigwaitinfo basic test: a pending signal should cause sigwaitinfo return immediately
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigwaitinfoBasic, TestSize.Level1)
{
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        sigset_t set, pending;
        sigemptyset(&pending);
        sigemptyset(&set);
        sigaddset(&set, SIGALRM);
        signal(SIGALRM, SignalHandler);
        if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
            LOG("sigprocmask failed");
            exit(1);
        }
        LOG("raise SIGALRM");
        raise(SIGALRM);

        sigpending(&pending);
        if (!sigismember(&pending, SIGALRM)) {
            LOG("SIGALRM is not in pending set");
            exit(1);
        }

        LOGD("before sigwaitinfo");
        struct timespec time1 = {0, 0};
        struct timespec time2 = {0, 0};
        clock_gettime(CLOCK_MONOTONIC, &time1);
        int rt = sigwaitinfo(&set, NULL);
        clock_gettime(CLOCK_MONOTONIC, &time2);

        LOGD("after sigwaitinfo");
        double duration = (time2.tv_sec - time1.tv_sec)*1000.0 + (time2.tv_nsec - time1.tv_nsec)/1000000.0;
        LOG("duration: %f ms", duration);
        if (CheckValueClose(0.1, duration)) {
            LOG("sigwaitinfo should return immediately, but %f ms used", duration);
            exitCode = 1;
        }
        if (rt != SIGALRM) {
            LOG("sigwaitinfo should return the signal, expected:%d, actual:%d", SIGALRM, rt);
            exitCode = 1;
        }
        LOG("child exited with code=%d", exitCode);
        exit(exitCode);
    } else { // parent
        sleep(1);
        AssertProcExitedOK(pid);
    }
}

/**
 * @tc.number SUB_KERNEL_IPC_SIG_PAUSE_0100
 * @tc.name   pause basic function test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testPauseBasic, TestSize.Level1)
{
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        struct timespec time1, time2;
        int exitCode = 0;
        signal(SIGQUIT, SignalHandler);
        Msleep(100);

        clock_gettime(CLOCK_MONOTONIC, &time1);
        int rt = pause();
        clock_gettime(CLOCK_MONOTONIC, &time2);
        if (rt != -1) {
            LOG("pause should return -1, but rt=%d", rt);
            exitCode = 1;
        }
        if (errno != EINTR) {
            LOG("pause should set errno to 4(EINTR),but get %d", errno);
            exitCode = 1;
        }

        long duration = (time2.tv_sec - time1.tv_sec)*1000 + (time2.tv_nsec - time1.tv_nsec)/1000000;
        LOG("paused time: %ld ms", duration);
        if (! CheckValueClose(100, duration, 0.2)) {
            LOG("paused time check error.");
            exitCode = 1;
        }
        if (mReceivedSignal != SIGQUIT) {
            LOG("Received signal check fail, expected signal=%d", SIGQUIT);
            exitCode = 1;
        }
        exit(exitCode);
    } else { // parent
        Msleep(200);
        kill(pid, SIGQUIT);
        Msleep(20);
        AssertProcExitedOK(pid);
    }
}
/**
 * @tc.number SUB_KERNEL_IPC_SIG_PAUSE_0200
 * @tc.name   pause basic function test
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testPauseAndMask, TestSize.Level1)
{
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        signal(SIGINT, SignalHandler);
        signal(SIGTRAP, SignalHandler);

        sigset_t sigmask;
        sigemptyset(&sigmask);
        sigaddset(&sigmask, SIGINT);
        int rt = sigprocmask(SIG_BLOCK, &sigmask, NULL);
        if (rt != 0) {
            LOG("sigprocmask fail, rt=%d, errno=%d", rt, errno);
            exit(1);
        }
        LOG("before pause");
        rt = pause();
        if (rt != -1) {
            LOG("pause should return -1, but rt=%d", rt);
            exitCode = 1;
        }
        if (errno != EINTR) {
            LOG("pause should set errno to 4(EINTR),but get %d", errno);
            exitCode = 1;
        }
        LOG("after pause");
        if (mReceivedSignal != SIGTRAP) {
            LOG("Received signal check fail, expected %d,but get %d", SIGINT, mReceivedSignal);
            exitCode = 1;
        }
        exit(exitCode);
    } else { // parent
        Msleep(20);
        kill(pid, SIGINT);
        Msleep(20);
        AssertProcAlive(pid);
        kill(pid, SIGTRAP);
        Msleep(20);
        AssertProcExitedOK(pid);
    }
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    if (sigisemptyset(&pending)) {
        LOG("pending set empty");
    } else {
        LOG("========pending set not empty=========");
    }
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGPENDING_0100
 * @tc.name   sigpending basic function test, also test pending-signal-set should not inherited after fork,
              but signal mask set should inherited, and the change of child's pending set should not effect parent's.
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigpendingBasic, TestSize.Level1)
{
    int status, rt;
    sigset_t sigmask, oldmask;
    sigset_t pending;
    sigemptyset(&sigmask);
    sigemptyset(&oldmask);
    sigemptyset(&pending);
    sigpending(&pending);
    EXPECT_EQ(1, sigisemptyset(&pending)) << "initial pending set should empty";

    signal(SIGALRM, SignalHandler);

    sigaddset(&sigmask, SIGALRM);
    sigaddset(&sigmask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigmask, &oldmask);
    EXPECT_EQ(1, sigisemptyset(&oldmask)) << "initial sig mask set should empty";
    rt = sigpending(&pending);
    EXPECT_EQ(rt, 0);
    EXPECT_EQ(1, sigisemptyset(&pending)) << "SIG_BLOCK set should not effect on pending set";

    LOGD("raise SIGALRM");
    raise(SIGALRM);
    sigpending(&pending);
    EXPECT_EQ(1, sigismember(&pending, SIGALRM));

    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        sigemptyset(&pending);
        sigpending(&pending);
        if (sigisemptyset(&pending) != 1) {
            LOG("pending signal set should not reserved via fork");
            exitCode = 1;
        }

        sigemptyset(&oldmask);
        sigprocmask(SIG_BLOCK, NULL, &oldmask); // read mask
        if ((sigismember(&oldmask, SIGALRM) != 1) || (sigismember(&oldmask, SIGUSR1) != 1)) {
            LOG("signal mask set should reserved via fork");
            exitCode = 1;
        }

        LOG("unblock SIGALRM.");
        rt = sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
        sigemptyset(&pending);
        sigpending(&pending);
        if (sigisemptyset(&pending) != 1) {
            LOG("pending signal set is not empty after unblock");
            exitCode = 1;
        }

        LOG("child exit(%d).", exitCode);
        exit(exitCode);
    } else { // parent
        Msleep(50);
        AssertProcExitedOK(pid);
        // check child's pending set should not effect parent's
        sigemptyset(&pending);
        sigpending(&pending);
        EXPECT_EQ(1, sigismember(&pending, SIGALRM)) << "parent's pending set is changed!";
    }
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGPROCMASK_0100
 * @tc.name   sigprocmask function test: use raise and kill to send signal
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigprocmaskBasic, TestSize.Level1)
{
    int status, rt;
    sigset_t sigmask, oldmask;
    sigset_t pending;
    sigemptyset(&sigmask);
    sigemptyset(&oldmask);
    sigemptyset(&pending);
    sigaddset(&sigmask, SIGINT);
    sigaddset(&sigmask, SIGUSR1);
    rt = sigprocmask(SIG_BLOCK, &sigmask, &oldmask);
    EXPECT_EQ(rt, 0);

    signal(SIGINT, SignalHandler);
    signal(SIGUSR1, SignalHandler);
    ASSERT_EQ(mReceivedSignal, 0);

    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        raise(SIGINT);
        if (mReceivedSignal != 0) {
            LOG("SignalHandler check fail, expected=%d, actual=%d", 0, mReceivedSignal);
            LOG("SIGINT(%d) should has blocked!", SIGINT);
            exit(1);
        }

        LOG("unblock SIGINT");
        sigemptyset(&sigmask);
        sigaddset(&sigmask, SIGINT);
        rt = sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
        EXPECT_EQ(rt, 0);

        // check the new block set
        sigemptyset(&oldmask);
        sigprocmask(SIG_UNBLOCK, NULL, &oldmask);
        if (sigismember(&oldmask, SIGINT) == 1) {
            LOG("SIGINT should has deleted from block set!");
            exitCode = 1;
        }
        if (sigismember(&oldmask, SIGUSR1) != 1) {
            LOG("SIGUSR1 should still in block set!");
            exitCode = 1;
        }
        if (mReceivedSignal != SIGINT) {
            LOG("SignalHandler check fail, expected=%d, actual=%d", SIGINT, mReceivedSignal);
            LOG("SIGALRM should deliver after unblock!");
            exitCode = 1;
        }

        // test kill
        mReceivedSignal = 0;
        Msleep(80);
        sigpending(&pending);
        if (!sigismember(&pending, SIGUSR1)) {
            LOG("SIGUSR1 is not in pending set!");
            exitCode = 1;
        } else {
            LOG("SIGUSR1 is in pending set.");
        }

        if (mReceivedSignal != 0) {
            LOG("SignalHandler check fail, expected=%d, actual=%d", 0, mReceivedSignal);
            LOG("SIGUSR1(%d) should has blocked!", SIGUSR1);
            exit(1);
        }

        LOG("unblock SIGUSR1");
        sigemptyset(&sigmask);
        sigaddset(&sigmask, SIGUSR1);
        sigprocmask(SIG_UNBLOCK, &sigmask, NULL);

        if (mReceivedSignal != SIGUSR1) {
            LOG("SignalHandler check fail, expected=%d, actual=%d", SIGUSR1, mReceivedSignal);
            LOG("SIGUSR1 should deliver after unblock!");
            exitCode = 1;
        }

        LOG("child exit(%d).", exitCode);
        exit(exitCode);
    } else { // parent
        Msleep(50);
        kill(pid, SIGUSR1);
        Msleep(50);
        ExpectProcExitedOK(pid);
    }
    // restore default config
    signal(SIGINT, SIG_DFL);
    signal(SIGUSR1, SIG_DFL);
    rt = sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
    EXPECT_EQ(rt, 0);
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGPROCMASK_0200
 * @tc.name   sigprocmask function test: use alarm to send the signal
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigprocmaskAlarm, TestSize.Level2)
{
    int status, rt;
    sigset_t sigmask, oldmask;
    sigset_t pending;
    sigemptyset(&sigmask);
    sigemptyset(&oldmask);
    sigemptyset(&pending);
    sigaddset(&sigmask, SIGALRM);
    rt = sigprocmask(SIG_BLOCK, &sigmask, &oldmask);
    ASSERT_EQ(rt, 0);

    signal(SIGALRM, SignalHandler);
    ASSERT_EQ(mReceivedSignal, 0);
    alarm(1);
    Msleep(1100);

    sigpending(&pending);
    EXPECT_EQ(1, sigismember(&pending, SIGALRM));
    EXPECT_EQ(mReceivedSignal, 0);

    LOG("unblock SIGALRM.");
    rt = sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
    EXPECT_EQ(rt, 0);
    ASSERT_EQ(mReceivedSignal, SIGALRM);

    signal(SIGALRM, SIG_DFL);
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGPROCMASK_0300
 * @tc.name   sigprocmask function test: mask operation
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigprocmaskSetMask, TestSize.Level2)
{
    int rt;
    sigset_t sigmask, oldmask, pending;
    sigemptyset(&sigmask);
    sigemptyset(&oldmask);
    sigemptyset(&pending);
    sigaddset(&sigmask, SIGALRM);
    rt = sigprocmask(SIG_BLOCK, &sigmask, NULL);
    ASSERT_EQ(rt, 0);
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGINT);
    rt = sigprocmask(SIG_BLOCK, &sigmask, NULL);
    ASSERT_EQ(rt, 0);

    LOG("add a new sig to block set");
    rt = sigprocmask(SIG_BLOCK, NULL, &oldmask); // check
    ASSERT_EQ(rt, 0);
    EXPECT_EQ(1, sigismember(&oldmask, SIGALRM));
    EXPECT_EQ(1, sigismember(&oldmask, SIGINT));

    LOG("unblock a not-in-set sig");
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGTRAP);
    rt = sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
    ASSERT_EQ(rt, 0);
    rt = sigprocmask(SIG_UNBLOCK, NULL, &oldmask); // check
    EXPECT_EQ(1, sigismember(&oldmask, SIGALRM));
    EXPECT_EQ(1, sigismember(&oldmask, SIGINT));
    EXPECT_EQ(0, sigismember(&oldmask, SIGTRAP));

    LOG("set new block set, clear old one");
    rt = sigprocmask(SIG_SETMASK, &sigmask, NULL);
    ASSERT_EQ(rt, 0);
    rt = sigprocmask(10, NULL, &oldmask); // check
    ASSERT_EQ(rt, 0);
    EXPECT_EQ(0, sigismember(&oldmask, SIGALRM));
    EXPECT_EQ(0, sigismember(&oldmask, SIGINT));
    EXPECT_EQ(1, sigismember(&oldmask, SIGTRAP));

    LOG("unblock git, clear the block set");
    rt = sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
    ASSERT_EQ(rt, 0);
    rt = sigprocmask(100, NULL, &oldmask); // check
    ASSERT_EQ(rt, 0);
    EXPECT_EQ(1, sigisemptyset(&oldmask));
}
/**
 * @tc.number SUB_KERNEL_IPC_SIGPROCMASK_0400
 * @tc.name   sigprocmask function test: don't block signal that not in block-set
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigprocmaskNotinSet, TestSize.Level2)
{
    LOG("Test1: not-in-set signal could be caught.");
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        sigset_t sigmask;
        sigemptyset(&sigmask);
        sigaddset(&sigmask, SIGTRAP);
        int rt = sigprocmask(SIG_BLOCK, &sigmask, NULL);
        if (rt != 0) {
            LOG("sigprocmask fail, rt=%d, errno=%d", rt, errno);
            exit(1);
        }
        signal(SIGINT, SignalHandler);
        signal(SIGTRAP, SignalHandler);

        Msleep(80);
        if (mReceivedSignal != SIGINT) {
            LOG("SignalHandler check fail, expected=SIGINT, actual=%d", mReceivedSignal);
            exit(1);
        }
        exit(0);
    } else { // parent
        Msleep(30);
        kill(pid, SIGINT);
        Msleep(100);
        AssertProcExitedOK(pid);
    }

    LOG("Test2: not-in-set signal could terminate the process.");
    pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        sigset_t sigmask;
        sigemptyset(&sigmask);
        sigaddset(&sigmask, SIGTRAP);
        int rt = sigprocmask(SIG_BLOCK, &sigmask, NULL);
        if (rt != 0) {
            LOG("sigprocmask fail, rt=%d, errno=%d", rt, errno);
            exit(1);
        }
        Msleep(60);
        exit(0);
    } else { // parent
        Msleep(30);
        kill(pid, SIGINT);
        Msleep(80);
        AssertProcKilled(pid, SIGINT);
    }
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGSUSPEND_0100
 * @tc.name   sigsuspend basic function test1: the sigsuspend-signal terminates the process
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigsuspendTerminate, TestSize.Level1)
{
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        signal(SIGTRAP, SignalHandler);
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGHUP);
        int rt = sigsuspend(&set);
        // should not get here:
        LOG("sigsuspend rt = %d, errno=%d", rt, errno);
        exit(1);
    } else { // parent
        Msleep(20);

        kill(pid, SIGHUP); // this should blocked by sigsuspend
        Msleep(20);
        AssertProcAlive(pid);

        kill(pid, SIGTRAP); // this should interupt sigsuspend
        Msleep(20);
        AssertProcKilled(pid, SIGHUP);
    }
}
/**
 * @tc.number SUB_KERNEL_IPC_SIGSUSPEND_0200
 * @tc.name   sigsuspend basic function test2: the sigsuspend-signal caught, and process continue run
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigsuspendContinue, TestSize.Level2)
{
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        signal(SIGTRAP, SignalHandler);
        signal(SIGHUP, SignalHandler);
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGHUP);
        int rt = sigsuspend(&set);
        if (rt != -1) {
            LOG("sigsuspend should return -1, but rt=%d", rt);
            exitCode = 1;
        }
        if (errno != EINTR) {
            LOG("sigsuspend should set errno to 4(EINTR),but get %d", errno);
            exitCode = 1;
        }
        if (mReceivedSignal != SIGHUP) {
            LOG("Received signal check fail, expected signal=%d", SIGHUP);
            exitCode = 1;
        }
        exit(exitCode);
    } else { // parent
        Msleep(20);

        kill(pid, SIGHUP);
        Msleep(20);
        AssertProcAlive(pid);

        kill(pid, SIGTRAP);
        Msleep(20);
        AssertProcExitedOK(pid);
    }
}

/**
 * @tc.number SUB_KERNEL_IPC_SIGSUSPEND_0300
 * @tc.name   sigsuspend test with sigprocmask
 * @tc.desc   [C- SOFTWARE -0200]
 * @tc.size   SMALL
 * @tc.type   FUNC
 */
HWTEST_F(IpcSignalTest, testSigsuspendAndMask, TestSize.Level1)
{
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    if (pid == 0) { // child
        int exitCode = 0;
        sigset_t procMask, suspendMask, pending;
        sigemptyset(&suspendMask);
        sigemptyset(&procMask);
        sigaddset(&suspendMask, SIGQUIT);
        sigaddset(&procMask, SIGINT);

        signal(SIGINT, SignalHandler);
        signal(SIGQUIT, SignalHandler);

        LOG("Block SIGINT...");
        int rt = sigprocmask(SIG_SETMASK, &procMask, NULL);
        if (rt != 0) {
            LOG("sigprocmask fail, rt=%d, errno=%d", rt, errno);
            exit(1);
        }
        LOG("Suspend SIGQUIT...");
        rt = sigsuspend(&suspendMask);
        if (rt != -1) {
            LOG("sigsuspend should return -1, but rt=%d", rt);
            exitCode = 1;
        }
        // signal in procmask should received 1st
        // need change to check SIGQUIT only if multi-signal issue fixed
        if ((mReceivedSignal != SIGQUIT) && (mReceivedSignal != SIGINT)) {
            LOG("Received signal check fail, get %d", mReceivedSignal);
            exitCode = 1;
        }

        LOG("Check current mask...");
        sigemptyset(&procMask);
        sigprocmask(10, NULL, &procMask);
        if (!sigismember(&procMask, SIGINT)) {
            LOG("SIGINT should in block set!");
            exitCode = 1;
        }
        if (sigismember(&procMask, SIGQUIT)) {
            LOG("SIGQUIT should not in block set!");
            exitCode = 1;
        }
        exit(exitCode);
    } else { // parent
        Msleep(20);
        kill(pid, SIGQUIT);
        Msleep(20);
        AssertProcAlive(pid);

        kill(pid, SIGINT); // this should interupt sigsuspend
        Msleep(20);
        AssertProcExitedOK(pid);
    }
}
