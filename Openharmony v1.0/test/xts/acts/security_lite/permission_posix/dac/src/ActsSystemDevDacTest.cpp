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

class SystemDevDacTestSuite : public testing::Test {
protected:
    // SetUpTestCase：测试套预置动作,在第一个TestCase之前执行
    static void SetUpTestCase(void)
    {
        setuid(UID0);
        setgid(GID0);
        RemoveDir("/dev/SystemDevDacTestSuite");
    }
    // TearDownTestCase：测试套清理动作,在最后一个TestCase之后执行
    static void TearDownTestCase(void) {}
    // 用例的预置动作
    virtual void SetUp()
    {
        setuid(UID0);
        setgid(GID0);
    }
    // 用例的清理动作
    virtual void TearDown()
    {
        RemoveDir("/dev/SystemDevDacTestSuite");
    }
};

static void ChildFuncNoCap()
{
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
    capdata[CAP_TO_INDEX(CAP_CHOWN)].effective &= ~CAP_TO_MASK(CAP_CHOWN);
    capdata[CAP_TO_INDEX(CAP_FOWNER)].effective &= ~CAP_TO_MASK(CAP_FOWNER);
    capdata[CAP_TO_INDEX(CAP_DAC_OVERRIDE)].effective &= ~CAP_TO_MASK(CAP_DAC_OVERRIDE);
    capdata[CAP_TO_INDEX(CAP_DAC_READ_SEARCH)].effective &= ~CAP_TO_MASK(CAP_DAC_READ_SEARCH);
    ret = capset(&capheader, &capdata[0]);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
}

static void ChildFuncOverrideCap()
{
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
    capdata[CAP_TO_INDEX(CAP_CHOWN)].effective &= ~CAP_TO_MASK(CAP_CHOWN);
    capdata[CAP_TO_INDEX(CAP_FOWNER)].effective &= ~CAP_TO_MASK(CAP_FOWNER);
    capdata[CAP_TO_INDEX(CAP_DAC_OVERRIDE)].effective |= CAP_TO_MASK(CAP_DAC_OVERRIDE);
    capdata[CAP_TO_INDEX(CAP_DAC_READ_SEARCH)].effective &= ~CAP_TO_MASK(CAP_DAC_READ_SEARCH);
    ret = capset(&capheader, &capdata[0]);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
}

static void ChildFuncReadsearchCap()
{
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
    capdata[CAP_TO_INDEX(CAP_CHOWN)].effective &= ~CAP_TO_MASK(CAP_CHOWN);
    capdata[CAP_TO_INDEX(CAP_FOWNER)].effective &= ~CAP_TO_MASK(CAP_FOWNER);
    capdata[CAP_TO_INDEX(CAP_DAC_OVERRIDE)].effective &= ~CAP_TO_MASK(CAP_DAC_OVERRIDE);
    capdata[CAP_TO_INDEX(CAP_DAC_READ_SEARCH)].effective |= CAP_TO_MASK(CAP_DAC_READ_SEARCH);
    ret = capset(&capheader, &capdata[0]);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
}

static void ChildFuncBothCap()
{
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
    capdata[CAP_TO_INDEX(CAP_CHOWN)].effective &= ~CAP_TO_MASK(CAP_CHOWN);
    capdata[CAP_TO_INDEX(CAP_FOWNER)].effective &= ~CAP_TO_MASK(CAP_FOWNER);
    capdata[CAP_TO_INDEX(CAP_DAC_OVERRIDE)].effective |= CAP_TO_MASK(CAP_DAC_OVERRIDE);
    capdata[CAP_TO_INDEX(CAP_DAC_READ_SEARCH)].effective |= CAP_TO_MASK(CAP_DAC_READ_SEARCH);
    ret = capset(&capheader, &capdata[0]);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
}

static void CreateDevDir()
{
    int ret;
    setuid(UID0);
    setgid(GID0);
    umask(ZEROUMASK);
    ret = mkdir("/dev/SystemDevDacTestSuite", CHMOD777);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
    ret = mkdir("/dev/SystemDevDacTestSuite/mkdir", CHMOD777);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
}

static void CreateDevTxt()
{
    int ret;
    int fd = 0;
    setuid(UID0);
    setgid(GID0);
    umask(ZEROUMASK);
    ret = mkdir("/dev/SystemDevDacTestSuite", CHMOD777);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
    fd = open("/dev/SystemDevDacTestSuite/Dac.txt", O_WRONLY | O_CREAT | O_TRUNC, CHMOD777);
    // dev/ not allow creat folders
    if (fd >= 0) {
        EXPECT_EQ(fd, WRONGNUM) << "Creat txt /dev";
        close(fd);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0290
 * @tc.name       : securityDACTest0290
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0290, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0333);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 333,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID555);
        ret = rmdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0300
 * @tc.name       : securityDACTest0300
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0300, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0611);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 611,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID0);
        ret = rmdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0310
 * @tc.name       : securityDACTest0310
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0310, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0105);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 105,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        ret = rmdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0320
 * @tc.name       : securityDACTest0320
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0320, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0555);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 555,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        ret = rmdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0330
 * @tc.name       : securityDACTest0330
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0330, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0666);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 666,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = rmdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
        chmod("/dev/SystemDevDacTestSuite", 0777);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0340
 * @tc.name       : securityDACTest0340
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0340, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0777);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 777,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID0);
        setgid(GID555);
        ret = rmdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0350
 * @tc.name       : securityDACTest0350
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0350, TestSize.Level2)
{
    int ret;
    struct stat buf = { 0 };
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0166);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 166,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID0);
        ret = stat("/dev/SystemDevDacTestSuite/mkdir", &buf);
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0360
 * @tc.name       : securityDACTest0360
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0360, TestSize.Level2)
{
    int ret;
    struct stat buf = { 0 };
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0111);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 111,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID0);
        ret = stat("/dev/SystemDevDacTestSuite/mkdir", &buf);
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0370
 * @tc.name       : securityDACTest0370
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0370, TestSize.Level2)
{
    int ret;
    struct stat buf = { 0 };
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0210);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 210,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID0);
        ret = stat("/dev/SystemDevDacTestSuite/mkdir", &buf);
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0380
 * @tc.name       : securityDACTest0380
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0380, TestSize.Level2)
{
    int ret;
    struct stat buf = { 0 };
    gid_t list[SINGLESIZE] = {0};
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0655);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 655,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = stat("/dev/SystemDevDacTestSuite/mkdir", &buf);
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0390
 * @tc.name       : securityDACTest0390
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0390, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0570);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 570,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID0);
        ret = rename("/dev/SystemDevDacTestSuite/mkdir", "/dev/SystemDevDacTestSuite/mkdir_bak");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0400
 * @tc.name       : securityDACTest0400
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0400, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0306);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 306,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID0);
        ret = rename("/dev/SystemDevDacTestSuite/mkdir", "/dev/SystemDevDacTestSuite/mkdir_bak");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0410
 * @tc.name       : securityDACTest0410
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0410, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0027);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 027,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID555);
        ret = rename("/dev/SystemDevDacTestSuite/mkdir", "/dev/SystemDevDacTestSuite/mkdir_bak");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0420
 * @tc.name       : securityDACTest0420
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0420, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0401);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 401,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID0);
        setgid(GID555);
        ret = chdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0430
 * @tc.name       : securityDACTest0430
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0430, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0507);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 507,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID555);
        ret = chdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0440
 * @tc.name       : securityDACTest0440
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0440, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0347);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 347,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID0);
        ret = chdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0450
 * @tc.name       : securityDACTest0450
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0450, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0063);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 063,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        ret = chdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0460
 * @tc.name       : securityDACTest0460
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0460, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0230);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 230,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID555);
        ret = chdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0470
 * @tc.name       : securityDACTest0470
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0470, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite", 0724);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 724,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = chdir("/dev/SystemDevDacTestSuite/mkdir");
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
        chdir("/storage");
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0480
 * @tc.name       : securityDACTest0480
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0480, TestSize.Level2)
{
    int ret;
    char *argv[] = {nullptr, nullptr};
    char *envp[] = {nullptr};
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0702);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID0);
        ret = execve("/dev/SystemDevDacTestSuite/Dac.txt", argv, envp);
        // the file is not elf , can not exec
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0490
 * @tc.name       : securityDACTest0490
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0490, TestSize.Level2)
{
    int ret;
    char *argv[] = {nullptr, nullptr};
    char *envp[] = {nullptr};
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0473);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID0);
        ret = execve("/dev/SystemDevDacTestSuite/Dac.txt", argv, envp);
        // the file is not elf , can not exec
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0500
 * @tc.name       : securityDACTest0500
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0500, TestSize.Level2)
{
    int ret;
    char *argv[] = {nullptr, nullptr};
    char *envp[] = {nullptr};
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0261);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        ret = execve("/dev/SystemDevDacTestSuite/Dac.txt", argv, envp);
        // the file is not elf , can not exec
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0510
 * @tc.name       : securityDACTest0510
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0510, TestSize.Level2)
{
    int ret;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0460);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID555);
        ret = access("/dev/SystemDevDacTestSuite/Dac.txt", F_OK);
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0520
 * @tc.name       : securityDACTest0520
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0520, TestSize.Level2)
{
    int ret;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0562);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID555);
        ret = access("/dev/SystemDevDacTestSuite/Dac.txt", F_OK);
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}


/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0530
 * @tc.name       : securityDACTest0530
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0530, TestSize.Level2)
{
    int ret;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0076);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID0);
        ret = access("/dev/SystemDevDacTestSuite/Dac.txt", F_OK);
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0540
 * @tc.name       : securityDACTest0540
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0540, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0076);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = access("/dev/SystemDevDacTestSuite/Dac.txt", F_OK);
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0550
 * @tc.name       : securityDACTest0550
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0550, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0132);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = access("/dev/SystemDevDacTestSuite/Dac.txt", F_OK);
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0560
 * @tc.name       : securityDACTest0560
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0560, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0241);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = access("/dev/SystemDevDacTestSuite/Dac.txt", F_OK);
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0570
 * @tc.name       : securityDACTest0570
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0570, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0456);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 456,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID555);
        ret = mkdir("/dev/SystemDevDacTestSuite/mkdir/Dac", NORWX);
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0580
 * @tc.name       : securityDACTest0580
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0580, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0167);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 167,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID0);
        ret = mkdir("/dev/SystemDevDacTestSuite/mkdir/Dac", NORWX);
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0590
 * @tc.name       : securityDACTest0590
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0590, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0511);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 511,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID555);
        ret = mkdir("/dev/SystemDevDacTestSuite/mkdir/Dac", NORWX);
        if (ret != 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0600
 * @tc.name       : securityDACTest0600
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0600, TestSize.Level2)
{
    int ret;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0640);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 640,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID555);
        ret = mkdir("/dev/SystemDevDacTestSuite/mkdir/Dac", NORWX);
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0610
 * @tc.name       : securityDACTest0610
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0610, TestSize.Level2)
{
    int ret;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0362);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID555);
        ret = unlink("/dev/SystemDevDacTestSuite/Dac.txt");
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0620
 * @tc.name       : securityDACTest0620
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0620, TestSize.Level2)
{
    int ret;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0526);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID555);
        ret = unlink("/dev/SystemDevDacTestSuite/Dac.txt");
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0630
 * @tc.name       : securityDACTest0630
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0630, TestSize.Level2)
{
    int ret;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0604);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID0);
        ret = unlink("/dev/SystemDevDacTestSuite/Dac.txt");
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0640
 * @tc.name       : securityDACTest0640
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0640, TestSize.Level2)
{
    int ret;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0671);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID0);
        ret = unlink("/dev/SystemDevDacTestSuite/Dac.txt");
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0650
 * @tc.name       : securityDACTest0650
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0650, TestSize.Level2)
{
    int ret;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0743);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID0);
        ret = unlink("/dev/SystemDevDacTestSuite/Dac.txt");
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0660
 * @tc.name       : securityDACTest0660
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0660, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0235);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = unlink("/dev/SystemDevDacTestSuite/Dac.txt");
        if (ret == 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0670
 * @tc.name       : securityDACTest0670
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0670, TestSize.Level2)
{
    int ret;
    int fd = 0;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0371);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID0);
        fd = open("/dev/SystemDevDacTestSuite/Dac.txt", O_WRONLY);
        if (fd >= 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            close(fd);
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0680
 * @tc.name       : securityDACTest0680
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0680, TestSize.Level2)
{
    int ret;
    int fd = 0;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0702);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID0);
        fd = open("/dev/SystemDevDacTestSuite/Dac.txt", O_WRONLY);
        if (fd >= 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            close(fd);
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0690
 * @tc.name       : securityDACTest0690
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0690, TestSize.Level2)
{
    int ret;
    int fd = 0;
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0406);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        fd = open("/dev/SystemDevDacTestSuite/Dac.txt", O_WRONLY);
        if (fd >= 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            close(fd);
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0700
 * @tc.name       : securityDACTest0700
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0700, TestSize.Level2)
{
    int ret;
    int fd = 0;
    gid_t list[SINGLESIZE] = {0};
    CreateDevTxt();
    ret = chmod("/dev/SystemDevDacTestSuite", 0257);
    // dev/shm can not change chmod
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod ,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        fd = open("/dev/SystemDevDacTestSuite/Dac.txt", O_WRONLY);
        if (fd >= 0) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            close(fd);
            exitCode = 1;
        }
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0710
 * @tc.name       : securityDACTest0710
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0710, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0750);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 750,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID555);
        dir = opendir("/dev/SystemDevDacTestSuite/mkdir");
        if (dir == nullptr) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        closedir(dir);
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0720
 * @tc.name       : securityDACTest0720
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0720, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0143);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 143,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID0);
        dir = opendir("/dev/SystemDevDacTestSuite/mkdir");
        if (dir == nullptr) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        closedir(dir);
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0730
 * @tc.name       : securityDACTest0730
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0730, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0521);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 521,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        dir = opendir("/dev/SystemDevDacTestSuite/mkdir");
        if (dir == nullptr) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        closedir(dir);
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0740
 * @tc.name       : securityDACTest0740
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0740, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    gid_t list[SINGLESIZE] = {0};
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0016);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 016,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        dir = opendir("/dev/SystemDevDacTestSuite/mkdir");
        if (dir == nullptr) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        closedir(dir);
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0750
 * @tc.name       : securityDACTest0750
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemDevDacTestSuite, securityDACTest0750, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    gid_t list[SINGLESIZE] = {0};
    CreateDevDir();
    ret = chmod("/dev/SystemDevDacTestSuite/mkdir", 0407);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 407,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        dir = opendir("/dev/SystemDevDacTestSuite/mkdir");
        if (dir == nullptr) {
            LOG("VFS error with DAC or Capability, now the uid=%d", getuid());
            exitCode = 1;
        }
        closedir(dir);
        exit(exitCode);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}