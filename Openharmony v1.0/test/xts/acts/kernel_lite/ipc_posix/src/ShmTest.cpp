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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <gtest/gtest.h>
#include "utils.h"
#include "log.h"

using namespace testing::ext;

class ShmTest : public::testing::Test {
public:
    static const char SHM_TEST_STR[];
    static const int SHM_TEST_STR_LEN;
};

const char ShmTest::SHM_TEST_STR[] = "hello shmem";
const int ShmTest::SHM_TEST_STR_LEN = sizeof(SHM_TEST_STR);

/**
 * @tc.number   SUB_KERNEL_IPC_SHM_ALL_0100
 * @tc.name     basic function test : hello world
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(ShmTest, testShmBasic, TestSize.Level0)
{
    const int memSize = 1024;
    int shmid;
    char *shared = nullptr;

    shmid = shmget(static_cast<key_t> IPC_PRIVATE, memSize, 0666 | IPC_CREAT);
    ASSERT_NE(shmid, -1) << "> parent: shmid errno = " << errno;

    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "> parent: fork errno = " << errno;
    if (pid == 0) {
        int exitCode = 0;
        Msleep(40);
        shared = static_cast<char*>(shmat(shmid, nullptr, 0));
        if (shared == reinterpret_cast<char*>(-1)) {
            LOG("> child: shmat errno = %d", errno);
            exit(1);
        }
        if (strncmp(shared, SHM_TEST_STR, SHM_TEST_STR_LEN) != 0) {
            LOG("> child: error strncmp() shared = %s", shared);
            exitCode = 1;
        }
        if ((shmdt(shared)) == -1) {
            LOG("> child: shmdt errno = %d", errno);
            exit(1);
        }
        if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
            LOG("> child: shmctl errno = %d", errno);
            exit(1);
        }
        exit(exitCode);
    }
    // parent
    shared = static_cast<char*>(shmat(shmid, nullptr, 0));
    ASSERT_NE(shared, (void*)-1) << "> parent : error: shmat";
    strncpy(shared, SHM_TEST_STR, SHM_TEST_STR_LEN);
    ASSERT_NE(shmdt(shared), -1) << "> parent: error : shmdt";

    Msleep(100);
    AssertProcExitedOK(pid);
}

/**
 * @tc.number   SUB_KERNEL_IPC_SHM_ALL_0300
 * @tc.name     Single-process test
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(ShmTest, testShmSingleProcess, TestSize.Level1)
{
    const int memSize = 1024;
    char *shared = nullptr;

    int shmid = shmget(static_cast<key_t> IPC_PRIVATE, memSize, 0666 | IPC_CREAT);
    ASSERT_NE(shmid, -1) << "> shmget errno = " << errno;

    shared = static_cast<char*>(shmat(shmid, nullptr, 0));
    ASSERT_NE(shared, (void*)-1) << "> shmat errno = " << errno;
    strncpy(shared, SHM_TEST_STR, SHM_TEST_STR_LEN);

    int re = shmdt(shared);
    ASSERT_NE(re, -1) << "> shmdt errno = " << errno;

    re = shmctl(shmid, IPC_RMID, nullptr);
    ASSERT_NE(re, -1) << "> shmctl errno = " << errno;
}

/**
 * @tc.number   SUB_KERNEL_IPC_SHM_SHMGET_0100
 * @tc.name     shmat basic function test
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(ShmTest, testShmget, TestSize.Level0)
{
    const int memSize = 1024;
    int tmp;
    int shmid;
    int shmidTmp;
    int tmpKey = GetRandom(2147483647);
    LOG("> tmpKey = %d", tmpKey);

    shmid = shmget(IPC_PRIVATE, memSize, 0666 | IPC_CREAT);
    ASSERT_NE(shmid, -1) << "> shmget : errno = " << errno;
    tmp = shmctl(shmid, IPC_RMID, nullptr);
    ASSERT_NE(tmp, -1) << "shmctl : error : IPC_RMID ";

    // make sure tmpKey free
    shmid = shmget(key_t(tmpKey), memSize, 0666 | IPC_CREAT);
    ASSERT_NE(shmid, -1) << "> shmget : errno = " << errno;
    tmp = shmctl(shmid, IPC_RMID, nullptr);
    ASSERT_NE(tmp, -1) << "shmctl : error : IPC_RMID ";

    shmid = shmget(key_t(tmpKey), memSize, IPC_EXCL | IPC_CREAT);
    ASSERT_NE(shmid, -1) << "> shmget : errno = " << errno;

    shmidTmp = shmid;
    shmidTmp = shmget(key_t(tmpKey), memSize, IPC_EXCL | IPC_CREAT);
    ASSERT_EQ(shmidTmp, -1) << "> shmget : errno = " << errno;

    tmp = shmctl(shmid, IPC_RMID, nullptr);
    ASSERT_NE(tmp, -1) << "> shmctl : error : IPC_RMID ";

    shmid = shmget(key_t(tmpKey), memSize, 0);
    ASSERT_EQ(shmid, -1) << "> shmget : errno = " << errno;

    shmid = shmget(IPC_PRIVATE, 0, 0666 | IPC_CREAT);
    ASSERT_EQ(shmid, -1) << "> shmget : errno = " << errno;

    shmid = shmget(IPC_PRIVATE, memSize, 0666 | IPC_CREAT);
    ASSERT_NE(shmid, -1) << "> shmget : errno = " << errno;

    tmp = shmctl(shmid, IPC_RMID, nullptr);
    ASSERT_NE(tmp, -1) << "> shmctl : error : IPC_RMID";
}

/**
 * @tc.number   SUB_KERNEL_IPC_SHM_SHMAT_0100
 * @tc.name     shmat: SHM_REMAP function test
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(ShmTest, testShmatSHM_REMAP, TestSize.Level1)
{
    const int memSize = 1024;
    int shmid;
    char *shared = nullptr;

    shmid = shmget(static_cast<key_t> IPC_PRIVATE, memSize, 0666 | IPC_CREAT);
    ASSERT_NE(shmid, -1) << "> parent: error : shmget";

    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "> parent: error : fork";
    if (pid == 0) {
        Msleep(10);
        int exitCode = 0;
        shared = static_cast<char*>(shmat(shmid, nullptr, 0));
        if (shared == reinterpret_cast<char*>(-1)) {
            LOG("> child: shmat 1 : errno = %d", errno);
            exit(1);
        }
        if (shmdt(shared) == -1) {
            LOG("> child: shmdt: errno = %d", errno);
            exit(1);
        }
        shared = static_cast<char*>(shmat(shmid, shared, SHM_REMAP));
        if (shared == reinterpret_cast<char*>(-1)) {
            LOG("> child: shmat 2 : errno = %d", errno);
            exit(1);
        }
        if (strncmp(shared, SHM_TEST_STR, SHM_TEST_STR_LEN) != 0) {
            LOG("> child: error strncmp() shared = %s", shared);
            exitCode = 1;
        }
        if ((shmdt(shared)) == -1) {
            LOG("> child: shmdt : errno = %d", errno);
            exit(1);
        }
        exit(exitCode);
    }
    // parent
    shared = static_cast<char*>(shmat(shmid, nullptr, 0));
    ASSERT_NE(shared, (void*)-1) << "> shmat 1 : errno = " << errno;
    ASSERT_NE(shmdt(shared), -1) << "> shmdt 1 : errno = " << errno;
    shared = static_cast<char*>(shmat(shmid, shared, SHM_REMAP));
    ASSERT_NE(shared, (void*)-1) << "> parent: shmat 2 : errno = " << errno;
    strncpy(shared, SHM_TEST_STR, SHM_TEST_STR_LEN);
    ASSERT_NE(shmdt(shared), -1) << "> parent: shmdt 2 : errno = " << errno;
    Msleep(20);
    ASSERT_NE(shmctl(shmid, IPC_RMID, nullptr), -1) << "> parent: shmctl : errno = " << errno;

    Msleep(50);
    AssertProcExitedOK(pid);
}

/**
 * @tc.number   SUB_KERNEL_IPC_SHM_SHMAT_0300
 * @tc.name     shmat: SHM_RND function test
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(ShmTest, testShmatSHM_RND, TestSize.Level0)
{
    const int memSize = 1024;
    int tmp;
    int shmid;
    void *shared = nullptr;

    Msleep(10);
    shmid = shmget(IPC_PRIVATE, memSize, 0666 | IPC_CREAT);
    EXPECT_NE(shmid, -1) << "shmget : errno = " << errno;

    shared = shmat(shmid, nullptr, 0);
    EXPECT_NE(shared, (void*)-1) << "> shmat : errno = " << errno;
    int re = shmdt(shared);
    EXPECT_NE(re, -1) << "> shmdt : errno = " << errno;

    void *sharedTmp = shared;
    sharedTmp = shmat(shmid, sharedTmp, SHM_RND);
    EXPECT_NE(sharedTmp, (void*)-1) << "> shmat : error : sharedTmp = " << sharedTmp << "shared = " << shared;
    strncpy(static_cast<char*>(sharedTmp), SHM_TEST_STR, SHM_TEST_STR_LEN);
    re = shmdt(sharedTmp);
    EXPECT_NE(re, -1) << "> shmdt : errno = " << errno;

    tmp = shmctl(shmid, IPC_RMID, nullptr);
    EXPECT_NE(tmp, -1) << "> shmctl : IPC_RMID errno = " << errno;
}

/**
 * @tc.number   SUB_KERNEL_IPC_SHM_SHMCTL_0100
 * @tc.name     shmctl: IPC_STAT and IPC_SET function test
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(ShmTest, testShmctl, TestSize.Level1)
{
    const int memSize = 4096;
    struct shmid_ds shmPerm;
    int tmp;
    int shmid;

    LOG("> getuid = %d", getuid());
    LOG("> getgid = %d", getgid());
    LOG("> getpid = %d", getpid());

    Msleep(10);
    shmid = shmget(IPC_PRIVATE, memSize, 0666 | IPC_CREAT);
    ASSERT_NE(shmid, -1) << "> shmget : errno = " << errno;

    tmp = shmctl(shmid, IPC_STAT, &shmPerm);
    EXPECT_NE(tmp, -1) << "> shmctl : IPC_STAT1 ：erron = " << errno;
    EXPECT_EQ(shmPerm.shm_lpid, 0);                         // PID of last shmat/shmdt
    EXPECT_EQ(shmPerm.shm_nattch, 0);                       // No. of current attaches

    char *shared = static_cast<char*>(shmat(shmid, nullptr, 0));
    EXPECT_NE(shared, (void*)-1) << "> shmat : errno = " << errno;

    tmp = shmctl(shmid, IPC_STAT, &shmPerm);
    ASSERT_NE(tmp, -1) << "> shmctl : IPC_STAT2 ：erron = " << errno;
    EXPECT_EQ(shmPerm.shm_perm.__key, 0);                   // Key supplied to shmget
    EXPECT_EQ(shmPerm.shm_perm.cuid, geteuid());            // Effective UID of creator
    EXPECT_EQ(shmPerm.shm_perm.uid, geteuid());             // Effective UID of owne
    EXPECT_EQ(shmPerm.shm_perm.cgid, getegid());            // Effective GID of creator
    EXPECT_EQ(shmPerm.shm_perm.gid, getegid());             // Effective GID of owner
    EXPECT_EQ(shmPerm.shm_perm.mode, 0666);                 // Permissions + SHM_DEST and SHM_LOCKED flags
    LOG("> last shmat() time %lld", shmPerm.shm_atime);     // Last attach time
    LOG("> last shmdt() time %lld", shmPerm.shm_dtime);     //  Last detach time
    EXPECT_EQ(shmPerm.shm_segsz, memSize);                  // Size of segment (bytes)
    EXPECT_EQ(shmPerm.shm_cpid, getpid());                  // PID of creator
    EXPECT_EQ(shmPerm.shm_lpid, getpid());                  // PID of last shmat/shmdt
    EXPECT_EQ(shmPerm.shm_nattch, 1);                       // No. of current attaches

    tmp = shmctl(shmid, IPC_SET, &shmPerm);
    EXPECT_NE(shared, (void*)-1) << "> shmat : errno = " << errno;

    tmp = shmdt(shared);
    ASSERT_NE(tmp, -1) << "> shmdt : errno = " << errno;

    tmp = shmctl(shmid, IPC_RMID, nullptr);
    ASSERT_NE(tmp, -1) << "> shmctl : IPC_RMID : errno = " << errno;
}

/**
 * @tc.number   SUB_KERNEL_IPC_SHM_SHMCTL_0200
 * @tc.name     shmctl: IPC_INFO and SHM_INFO function test
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(ShmTest, testShmctlINFO, TestSize.Level0)
{
    int tmp;
    struct shminfo buf;
    tmp = shmctl(0, IPC_INFO, (struct shmid_ds *) &buf);
    EXPECT_NE(tmp, -1) << "shmctl : IPC_INFO errno = " << errno;
    LOG("> shminfo.shmmax = %lu", buf.shmmax);  // Maximum segment size 42428800
    EXPECT_EQ(buf.shmmin, 1) << "> shminfo.shmmin = " << buf.shmmin;    // Minimum segment size 1
    LOG("> shminfo.shmmni = %lu", buf.shmmni);  // Maximum number of segments 192
    LOG("> shminfo.shmseg = %lu", buf.shmseg);  // Maximum number of segments that a process can attach 128
    LOG("> shminfo.shmall = %lu", buf.shmall);  // Maximum number of pages of shared memory, system-wide 12800

    // Describes the system resource information for Shared memory
    struct shm_info info;
    tmp = shmctl(0, SHM_INFO, (struct shmid_ds *) &info);
    EXPECT_NE(tmp, -1) << "shmctl : SHM_INFO errno = " << errno;
    LOG("> shm_info.used_ids         = %d", info.used_ids);             // Currently existing segments
    LOG("> shm_info.shm_tot          = %lu", info.shm_tot);             // Total number of shared memory pages
    LOG("> shm_info.shm_rss          = %lu", info.shm_rss);             // Resident shared memory pages
    LOG("> shm_info.shm_swp          = %lu", info.shm_swp);             // Swapped shared memory pages
    LOG("> shm_info.__swap_attempts  = %ld", info.__swap_attempts);     // Number of exchange attempts
    LOG("> shm_info.__swap_successes = %ld", info.__swap_successes);    // Number of successful exchanges
}
