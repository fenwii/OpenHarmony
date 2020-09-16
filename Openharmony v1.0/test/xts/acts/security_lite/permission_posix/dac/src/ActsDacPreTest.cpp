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

#include "ActsDacTest.h"
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <dirent.h>
#include <fcntl.h>
#include <sched.h>
#include <securec.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "gtest/gtest.h"

#ifdef __LINUX__
#include <grp.h>
#include <sys/cdefs.h>
#include <linux/capability.h>
#else
#include <sys/capability.h>
#endif

#ifdef __LINUX__
__BEGIN_DECLS
extern int capget(cap_user_header_t hdrp, cap_user_data_t datap);
extern int capset(cap_user_header_t hdrp, const cap_user_data_t datap);
__END_DECLS
#endif

using namespace std;
using namespace testing::ext;

class DacPreTestSuite : public testing::Test {
protected:
    // SetUpTestCase：测试套预置动作,在第一个TestCase之前执行
    static void SetUpTestCase(void) {}
    // TearDownTestCase：测试套清理动作,在最后一个TestCase之后执行
    static void TearDownTestCase(void) {}
    // 用例的预置动作
    virtual void SetUp()
    {
        // uid=gid=0
        struct __user_cap_header_struct capheader;
        struct __user_cap_data_struct capdata[CAP_NUM];
        int ret;
        memset_s(&capheader, sizeof(struct __user_cap_header_struct), 0, sizeof(struct __user_cap_header_struct));
        memset_s(capdata, CAP_NUM * sizeof(struct __user_cap_data_struct), 0,
            CAP_NUM * sizeof(struct __user_cap_data_struct));
        capdata[0].permitted = 0xffffffff;
        capdata[1].permitted = 0xffffffff;
        capheader.version = _LINUX_CAPABILITY_VERSION_3;
        capdata[CAP_TO_INDEX(CAP_SETPCAP)].effective |= CAP_TO_MASK(CAP_SETPCAP);
        capdata[CAP_TO_INDEX(CAP_SETUID)].effective |= CAP_TO_MASK(CAP_SETUID);
        capdata[CAP_TO_INDEX(CAP_SETGID)].effective |= CAP_TO_MASK(CAP_SETGID);
        ret = capset(&capheader, &capdata[0]);
        EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
        ret = setuid(UID0);
        EXPECT_EQ(ret, 0) << "ErrInfo: Set uid failed,now uid=" << getuid();
        ret = setgid(GID0);
        EXPECT_EQ(ret, 0) << "ErrInfo: Set gid failed,now gid=" << getgid();
    }
    // 用例的清理动作
    virtual void TearDown() {}
};

static int TestSetUid()
{
    int ret;
    int exitCode = 0;
    uid_t ruid1, euid1, suid1;
    // setuid
    ret = setuid(0);
    if (ret != 0) {
        LOG("Failed in setting uid=0,now uid=%d", getuid());
        exitCode = 1;
    }
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == 0) && (euid1 == 0) && (suid1 == 0)) << "Failed in setting uid:ruid=" << ruid1 << ",euid=" <<
        euid1 << ",suid=" << suid1;
    ret = setuid(UID1000);
    if (ret != 0) {
        LOG("Failed in setting uid=1000,now uid=%d", getuid());
        exitCode = 1;
    }
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == UID1000) && (euid1 == UID1000) && (suid1 == UID1000)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
    ret = setuid(UID10000);
    if (ret != 0) {
        LOG("Failed in setting uid=10000,now uid=%d", getuid());
        exitCode = 1;
    }
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == UID10000) && (euid1 == UID10000) && (suid1 == UID10000)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
    ret = setuid(MAX_INT);
    if (ret != 0) {
        LOG("Failed in setting uid=MAX_INT,now uid=%d", getuid());
        exitCode = 1;
    }
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == MAX_INT) && (euid1 == MAX_INT) && (suid1 == MAX_INT)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
    return exitCode;
}

static void TestSetREUid()
{
    int ret;
    uid_t ruid1, euid1, suid1;
    // setreuid
    ret = setreuid(0, 0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting reuid,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == 0) && (euid1 == 0) && (suid1 == 0)) << "Failed in setting uid:ruid=" << ruid1 << ",euid=" <<
        euid1 << ",suid=" << suid1;
    ret = setreuid(UID1000, UID1000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting reuid,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == UID1000) && (euid1 == UID1000) && (suid1 == UID1000)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
    ret = setreuid(UID10000, UID10000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting reuid,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == UID10000) && (euid1 == UID10000) && (suid1 == UID10000)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
    ret = setreuid(MAX_INT, MAX_INT);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set uid = MAX_INT,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == MAX_INT) && (euid1 == MAX_INT) && (suid1 == MAX_INT)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
}

static void TestSetRESUid()
{
    int ret;
    uid_t ruid1, euid1, suid1;
    // setresuid
    ret = setresuid(0, 0, 0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting resuid,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == 0) && (euid1 == 0) && (suid1 == 0)) << "Failed in setting uid:ruid=" << ruid1 << ",euid=" <<
        euid1 << ",suid=" << suid1;
    ret = setresuid(UID1000, UID1000, UID1000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting resuid,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == UID1000) && (euid1 == UID1000) && (suid1 == UID1000)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
    ret = setresuid(UID10000, UID10000, UID10000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting resuid,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == UID10000) && (euid1 == UID10000) && (suid1 == UID10000)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
    ret = setresuid(MAX_INT, MAX_INT, MAX_INT);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set uid = MAX_INT,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == MAX_INT) && (euid1 == MAX_INT) && (suid1 == MAX_INT)) << "Failed in setting uid:ruid=" <<
        ruid1 << ",euid=" << euid1 << ",suid=" << suid1;
}

static void TestSetUidAbnormal()
{
    int ret;
    uid_t ruid1, euid1, suid1, ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    // setuid = -1
    ret = setuid(ABNORMALINT);
    EXPECT_EQ(ret, -1) << "ErrInfo: Set uid=-1,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == ruid) && (euid1 == euid) && (suid1 == suid)) << "Failed in setting uid:ruid=" << ruid1 <<
        ",euid=" << euid1 << ",suid=" << suid1;
    // setreuid = -1
    ret = setreuid(ABNORMALINT, ABNORMALINT);
    EXPECT_EQ(ret, -1) << "ErrInfo: Set uid=-1,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == ruid) && (euid1 == euid) && (suid1 == suid)) << "Failed in setting uid:ruid=" << ruid1 <<
        ",euid=" << euid1 << ",suid=" << suid1;
    // setresuid = -1
    ret = setresuid(ABNORMALINT, ABNORMALINT, ABNORMALINT);
    EXPECT_EQ(ret, -1) << "ErrInfo: Set uid=-1,now uid=" << getuid();
    getresuid(&ruid1, &euid1, &suid1);
    EXPECT_TRUE((ruid1 == ruid) && (euid1 == euid) && (suid1 == suid)) << "Failed in setting uid:ruid=" << ruid1 <<
        ",euid=" << euid1 << ",suid=" << suid1;
}

static int TestSetGid()
{
    int ret;
    int exitCode = 0;
    gid_t rgid1, egid1, sgid1;
    // setgid
    ret = setgid(0);
    if (ret != 0) {
        LOG("Failed in setting gid=0,now gid=%d", getgid());
        exitCode = 1;
    }
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == 0) && (egid1 == 0) && (sgid1 == 0)) << "Failed in setting gid:rgid=" << rgid1 << ",egid=" <<
        egid1 << ",sgid=" << sgid1;
    ret = setgid(GID1000);
    if (ret != 0) {
        LOG("Failed in setting gid=1000,now gid=%d", getgid());
        exitCode = 1;
    }
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == GID1000) && (egid1 == GID1000) && (sgid1 == GID1000)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
    ret = setgid(GID10000);
    if (ret != 0) {
        LOG("Failed in setting gid=10000,now gid=%d", getgid());
        exitCode = 1;
    }
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == GID10000) && (egid1 == GID10000) && (sgid1 == GID10000)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
    ret = setgid(MAX_INT);
    if (ret != 0) {
        LOG("Failed in setting gid=MAX_INT,now gid=%d", getgid());
        exitCode = 1;
    }
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == MAX_INT) && (egid1 == MAX_INT) && (sgid1 == MAX_INT)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
    return exitCode;
}

static void TestSetREGid()
{
    int ret;
    gid_t rgid1, egid1, sgid1;
    // setregid
    ret = setregid(0, 0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting regid,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == 0) && (egid1 == 0) && (sgid1 == 0)) << "Failed in setting gid:rgid=" << rgid1 << ",egid=" <<
        egid1 << ",sgid=" << sgid1;
    ret = setregid(GID1000, GID1000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting regid,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == GID1000) && (egid1 == GID1000) && (sgid1 == GID1000)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
    ret = setregid(GID10000, GID10000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting regid,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == GID10000) && (egid1 == GID10000) && (sgid1 == GID10000)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
    ret = setregid(MAX_INT, MAX_INT);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set gid = MAX_INT,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == MAX_INT) && (egid1 == MAX_INT) && (sgid1 == MAX_INT)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
}

static void TestSetRESGid()
{
    int ret;
    gid_t rgid1, egid1, sgid1;
    // setresgid
    ret = setresgid(0, 0, 0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting resgid,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == 0) && (egid1 == 0) && (sgid1 == 0)) << "Failed in setting gid:rgid=" << rgid1 << ",egid=" <<
        egid1 << ",sgid=" << sgid1;
    ret = setresgid(GID1000, GID1000, GID1000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting resgid,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == GID1000) && (egid1 == GID1000) && (sgid1 == GID1000)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
    ret = setresgid(GID10000, GID10000, GID10000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting resgid,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == GID10000) && (egid1 == GID10000) && (sgid1 == GID10000)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
    ret = setresgid(MAX_INT, MAX_INT, MAX_INT);
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set gid = MAX_INT,now uid=" << getuid();
    EXPECT_TRUE((rgid1 == MAX_INT) && (egid1 == MAX_INT) && (sgid1 == MAX_INT)) << "Failed in setting gid:rgid=" <<
        rgid1 << ",egid=" << egid1 << ",sgid=" << sgid1;
}

static void TestSetGidAbnormal()
{
    int ret;
    gid_t rgid1, egid1, sgid1, rgid, egid, sgid;
    getresgid(&rgid, &egid, &sgid);
    // setgid = -1
    ret = setgid(ABNORMALINT);
    EXPECT_EQ(ret, -1) << "ErrInfo: Set gid=-1,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == rgid) && (egid1 == egid) && (sgid1 == sgid)) << "Failed in setting gid:rgid=" << rgid1 <<
        ",egid=" << egid1 << ",sgid=" << sgid1;
    // setregid = -1
    ret = setregid(ABNORMALINT, ABNORMALINT);
    EXPECT_EQ(ret, -1) << "ErrInfo: Set gid=-1,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == rgid) && (egid1 == egid) && (sgid1 == sgid)) << "Failed in setting gid:rgid=" << rgid1 <<
        ",egid=" << egid1 << ",sgid=" << sgid1;
    // setresgid = -1
    ret = setresgid(ABNORMALINT, ABNORMALINT, ABNORMALINT);
    EXPECT_EQ(ret, -1) << "ErrInfo: Set gid=-1,now uid=" << getuid();
    getresgid(&rgid1, &egid1, &sgid1);
    EXPECT_TRUE((rgid1 == rgid) && (egid1 == egid) && (sgid1 == sgid)) << "Failed in setting gid:rgid=" << rgid1 <<
        ",egid=" << egid1 << ",sgid=" << sgid1;
}

static int TestSetGroups()
{
    int ret;
    int exitCode = 0;
    gid_t list[SIZE255];
    for (size_t num = 0; num < SIZE253; num++) {
        list[num] = num;
    }
    list[SIZE254] = MAX_INT;
    ret = setgroups(SIZE255, list);
    if (ret != 0) {
        LOG("Failed in setting groups");
        exitCode = 1;
    }
    return exitCode;
}

static void TsetFork(uid_t uid, gid_t gid, size_t size, const gid_t list[])
{
    int ret;
    int status = 0;
    ret = setuid(uid);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting uid,now uid=" << getuid();
    ret = setgid(gid);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting gid,now uid=" << getuid();
    setgroups(0, nullptr);
    ret = setgroups(size, list);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // fork
    gid_t reallist[SIZE255];
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        uid_t retuid = getuid();
        if (retuid != uid) {
            LOG("ErrInfo: Failed in getting uid,uid=%d,pid=%d,ppid=%d", ret, getpid(), getppid());
            exitCode = 1;
        }
        gid_t retgid = getgid();
        if (retgid != gid) {
            LOG("ErrInfo: Failed in getting gid,gid=%d,pid=%d,ppid=%d", ret, getpid(), getppid());
            exitCode = 1;
        }
        int retgroups = getgroups(0, reallist);
        if (retgroups == -1) {
            LOG("ErrInfo: Failed in getting groups,getroups=%d,pid=%d,ppid=%d", ret, getpid(), getppid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        waitpid(pid, &status, 0);
        usleep(SLEEP_NUM);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0010
 * @tc.name       : securityDACTest0010
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacPreTestSuite, securityDACTest0010, TestSize.Level1)
{
    int ret;
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    TestSetUid();
    TestSetREUid();
    TestSetRESUid();
    TestSetUidAbnormal();
    // Restore the test environment
    ret = setresuid(ruid, euid, suid);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting resuid,now uid=" << getuid();
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0020
 * @tc.name       : securityDACTest0020
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacPreTestSuite, securityDACTest0020, TestSize.Level1)
{
    int ret;
    gid_t rgid, egid, sgid;
    getresgid(&rgid, &egid, &sgid);
    TestSetGid();
    TestSetREGid();
    TestSetRESGid();
    TestSetGidAbnormal();
    // Restore the test environment
    ret = setresgid(rgid, egid, sgid);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting resgid,now uid=" << getuid();
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0030
 * @tc.name       : securityDACTest0030
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacPreTestSuite, securityDACTest0030, TestSize.Level1)
{
    int ret;
    gid_t grouplist[SIZE255];
    int groupsize = getgroups(0, grouplist);
    if (groupsize >= 0) {
        getgroups(groupsize, grouplist);
    } else {
        EXPECT_GE(groupsize, 0) << "ErrInfo: Failed in getgroups";
    }
    gid_t list1[SIZE1] = {1};
    gid_t list2[SIZE1] = {MAX_INT};
    gid_t list3[SIZE1] = {};
    // setgroups equal 1
    ret = setgroups(SIZE1, list1);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // setgroups equal MAX_INT
    ret = setgroups(SIZE1, list2);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // setgroups equal NULL
    ret = setgroups(SIZE1, list3);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // Restore the test environment
    ret = setgroups(groupsize, grouplist);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0040
 * @tc.name       : securityDACTest0040
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacPreTestSuite, securityDACTest0040, TestSize.Level2)
{
    int ret;
    gid_t grouplist[SIZE255];
    gid_t list1[SIZE2]={0, 0};
    gid_t list2[SIZE2]={1, 1};
    gid_t list3[SIZE2]={MAX_INT, MAX_INT};
    int groupsize = getgroups(0, grouplist);
    if (groupsize >= 0) {
        getgroups(groupsize, grouplist);
    } else {
        EXPECT_GE(groupsize, 0) << "ErrInfo: Failed in getgroups";
    }
    // setgroups = 0,0
    ret = setgroups(SIZE2, list1);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // setgroups = 1,1
    ret = setgroups(SIZE2, list2);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // setgroups = MAX_INT,MAX_INT
    ret = setgroups(SIZE2, list3);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // Restore the test environment
    setgroups(0, nullptr);
    ret = setgroups(groupsize, grouplist);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0050
 * @tc.name       : securityDACTest0050
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacPreTestSuite, securityDACTest0050, TestSize.Level3)
{
    int ret;
    gid_t grouplist[SIZE255];
    gid_t list1[SIZE3]={GID0, GID0, MAX_INT};
    gid_t list2[SIZE3]={GID10000, GID10000, MAX_INT};
    gid_t list3[SIZE3]={GID0, MAX_INT, MAX_INT};
    int groupsize = getgroups(0, grouplist);
    if (groupsize >= 0) {
        getgroups(groupsize, grouplist);
    } else {
        EXPECT_GE(groupsize, 0) << "ErrInfo: Failed in getgroups";
    }
    // setgroups = 0, 0, MAX_INT
    ret = setgroups(SIZE3, list1);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // setgroups = 10000, 10000, MAX_INT
    ret = setgroups(SIZE3, list2);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
    // setgroups = 0, MAX_INT, MAX_INT
    ret = setgroups(SIZE3, list3);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();

    // Restore the test environment
    setgroups(0, nullptr);
    ret = setgroups(groupsize, grouplist);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0060
 * @tc.name       : securityDACTest0060
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacPreTestSuite, securityDACTest0060, TestSize.Level3)
{
    int ret;
    gid_t grouplist[SIZE255];
    int groupsize = getgroups(0, grouplist);
    if (groupsize >= 0) {
        getgroups(groupsize, grouplist);
    } else {
        EXPECT_GE(groupsize, 0) << "ErrInfo: Failed in getgroups";
    }
    gid_t list0[SIZE255];
    for (size_t num0 = 0; num0 < SIZE254; num0++) {
        list0[num0] = num0;
    }
    list0[SIZE254] = MAX_INT;
    ret = setgroups(SIZE255, list0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();

    // Restore the test environment
    setgroups(0, nullptr);
    ret = setgroups(groupsize, grouplist);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();

    gid_t list1[INVAILD_SIZE];
    for (size_t num1 = 0; num1 < MAX_SIZE; num1++) {
        list1[num1] = num1;
    }
    list1[MAX_SIZE] = MAX_INT;
    ret = setgroups(INVAILD_SIZE, list1);
    EXPECT_EQ(ret, -1) << "ErrInfo: Set groups size over 255,size=" << SIZE2;

    // Restore the test environment
    setgroups(0, nullptr);
    ret = setgroups(groupsize, grouplist);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting groups,now uid=" << getuid();
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0070
 * @tc.name       : securityDACTest0070
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacPreTestSuite, securityDACTest0070, TestSize.Level2)
{
    int ret;
    int status = 0;
    pid_t pid;
    for (int num = 0; num < NUM3; num++) {
        pid = fork();
        ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
        usleep(SLEEP_NUM);
        if (pid == 0) {
            break;
        }
    }
    if (pid == 0) {
        int exitCode = 0;
        for (int number = 0; number < NUM3000; number++) {
            ret = TestSetUid();
            if (ret != 0) {
                LOG("Failed in TestSetUid when the %d time", number);
                exitCode = 1;
                break;
            }
            ret = TestSetGid();
            if (ret != 0) {
                LOG("Failed in TestSetGid when the %d time", number);
                exitCode = 1;
                break;
            }
            ret = TestSetGroups();
            if (ret != 0) {
                LOG("Failed in TestSetGroups when the %d time", number);
                exitCode = 1;
                break;
            }
            // Restore the test environment
            setuid(0);
            setgid(0);
            setgroups(0, nullptr);
        }
        exit(exitCode);
    } else {
        while (wait(&status) > 0) {
            usleep(SLEEP_NUM);
            EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
            EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo:Pid = " << wait(&status) <<
                ",the WEXITSTATUS return code is " << WEXITSTATUS(status);
            usleep(SLEEP_NUM);
        }
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0080
 * @tc.name       : securityDACTest0080
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacPreTestSuite, securityDACTest0080, TestSize.Level2)
{
    gid_t grouplist[SIZE255];
    int groupsize = getgroups(0, grouplist);
    if (groupsize >= 0) {
        getgroups(groupsize, grouplist);
    } else {
        EXPECT_GE(groupsize, 0) << "ErrInfo: Failed in getgroups";
    }
    gid_t list1[SIZE1] = {GID10000};
    gid_t list2[SIZE1] = {};
    gid_t list3[SIZE255];
    for (size_t num = 0; num < SIZE254; num++) {
        list3[num] = num;
    }
    list3[SIZE254] = MAX_INT;

    TsetFork(UID0, GID10000, SIZE1, list1);
    TsetFork(UID10000, GID10000, SIZE1, list1);
    TsetFork(MAX_INT, GID10000, SIZE1, list1);
    TsetFork(UID10000, GID0, SIZE1, list1);
    TsetFork(UID10000, MAX_INT, SIZE1, list1);
    TsetFork(UID10000, GID10000, SIZE1, list2);
    TsetFork(UID10000, GID10000, SIZE255, list3);

    usleep(SLEEP_NUM);
}