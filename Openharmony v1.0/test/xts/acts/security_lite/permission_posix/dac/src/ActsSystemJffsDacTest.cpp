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

class SystemJffsDacTestSuite : public testing::Test {
protected:
    // SetUpTestCase：测试套预置动作,在第一个TestCase之前执行
    static void SetUpTestCase(void)
    {
        setuid(UID0);
        setgid(GID0);
        RemoveDir("/storage/SystemJffsDacTestSuite");
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
        RemoveDir("/storage/SystemJffsDacTestSuite");
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

static void CreateDir()
{
    int ret;
    // uid=gid=0
    setuid(UID0);
    setgid(GID0);
    umask(ZEROUMASK);
    ret = mkdir("/storage/SystemJffsDacTestSuite", CHMOD777);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
    ret = mkdir("/storage/SystemJffsDacTestSuite/mkdir", CHMOD777);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
}

static void CreateTxt()
{
    int ret;
    int fd = 0;
    char cap[] = "SystemJffsDacTestSuite!\n";
    // uid=gid=0
    setuid(UID0);
    setgid(GID0);
    umask(ZEROUMASK);
    ret = mkdir("/storage/SystemJffsDacTestSuite", CHMOD777);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
    fd = open("/storage/SystemJffsDacTestSuite/Dac.txt", O_WRONLY | O_CREAT | O_TRUNC, CHMOD777);
    if (fd >= 0) {
        write(fd, cap, sizeof(cap));
        close(fd);
    } else {
        EXPECT_GE(fd, 0) << "Creat txt error";
    }
}

/* *
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0820
 * @tc.name       : securityDACTest0820
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0820, TestSize.Level2)
{
    int ret;
    struct stat buf = { 0 };
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0000);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 000,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncOverrideCap();
        setuid(UID0);
        setgid(GID0);
        ret = stat("/storage/SystemJffsDacTestSuite/Dac.txt", &buf);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0840
 * @tc.name       : securityDACTest0840
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0840, TestSize.Level2)
{
    int ret;
    struct stat buf = { 0 };
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0334);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 334,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID555);
        ret = stat("/storage/SystemJffsDacTestSuite/Dac.txt", &buf);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0850
 * @tc.name       : securityDACTest0850
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0850, TestSize.Level2)
{
    int ret;
    struct stat buf = { 0 };
    gid_t list[SINGLESIZE] = {0};
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0334);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 334,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = stat("/storage/SystemJffsDacTestSuite/Dac.txt", &buf);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0860
 * @tc.name       : securityDACTest0860
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0860, TestSize.Level2)
{
    int ret;
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0614);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 614,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID0);
        setgid(GID555);
        ret = rename("/storage/SystemJffsDacTestSuite/Dac.txt", "/storage/SystemJffsDacTestSuite/Dac_bak.txt");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0890
 * @tc.name       : securityDACTest0890
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0890, TestSize.Level2)
{
    int ret;
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0765);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 765,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID0);
        setgid(GID0);
        ret = rename("/storage/SystemJffsDacTestSuite/Dac.txt", "/storage/SystemJffsDacTestSuite/Dac_bak.txt");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0920
 * @tc.name       : securityDACTest0920
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0920, TestSize.Level2)
{
    int ret;
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0256);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 256,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncBothCap();
        setuid(UID555);
        setgid(GID0);
        ret = chdir("/storage/SystemJffsDacTestSuite/mkdir");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0930
 * @tc.name       : securityDACTest0930
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0930, TestSize.Level2)
{
    int ret;
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0235);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 235,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID0);
        setgid(GID0);
        ret = chdir("/storage/SystemJffsDacTestSuite/mkdir");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0940
 * @tc.name       : securityDACTest0940
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0940, TestSize.Level2)
{
    int ret;
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0670);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 672,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID555);
        setgid(GID555);
        ret = chdir("/storage/SystemJffsDacTestSuite/mkdir");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0950
 * @tc.name       : securityDACTest0950
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0950, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0116);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 116,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = chdir("/storage/SystemJffsDacTestSuite/mkdir");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0960
 * @tc.name       : securityDACTest0960
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0960, TestSize.Level2)
{
    int ret;
    char *argv[] = {nullptr, nullptr};
    char *envp[] = {nullptr};
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0045);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 045,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID0);
        setgid(GID555);
        ret = execve("/storage/SystemJffsDacTestSuite/Dac.txt", argv, envp);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0970
 * @tc.name       : securityDACTest0970
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0970, TestSize.Level2)
{
    int ret;
    char *argv[] = {nullptr, nullptr};
    char *envp[] = {nullptr};
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0124);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 124,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID555);
        setgid(GID0);
        ret = execve("/storage/SystemJffsDacTestSuite/Dac.txt", argv, envp);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0980
 * @tc.name       : securityDACTest0980
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0980, TestSize.Level2)
{
    int ret;
    char *argv[] = {nullptr, nullptr};
    char *envp[] = {nullptr};
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0536);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 536,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID0);
        setgid(GID0);
        ret = execve("/storage/SystemJffsDacTestSuite/Dac.txt", argv, envp);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0990
 * @tc.name       : securityDACTest0990
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest0990, TestSize.Level2)
{
    int ret;
    char *argv[] = {nullptr, nullptr};
    char *envp[] = {nullptr};
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0657);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 657,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID555);
        ret = execve("/storage/SystemJffsDacTestSuite/Dac.txt", argv, envp);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1000
 * @tc.name       : securityDACTest1000
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1000, TestSize.Level2)
{
    int ret;
    char *argv[] = {nullptr, nullptr};
    char *envp[] = {nullptr};
    gid_t list[SINGLESIZE] = {0};
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0310);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 310,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = execve("/storage/SystemJffsDacTestSuite/Dac.txt", argv, envp);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1010
 * @tc.name       : securityDACTest1010
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1010, TestSize.Level2)
{
    int ret;
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0354);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 354,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID0);
        setgid(GID555);
        ret = access("/storage/SystemJffsDacTestSuite/Dac.txt", F_OK);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1030
 * @tc.name       : securityDACTest1030
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1030, TestSize.Level2)
{
    int ret;
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0717);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 717,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID555);
        ret = access("/storage/SystemJffsDacTestSuite/Dac.txt", F_OK);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1050
 * @tc.name       : securityDACTest1050
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1050, TestSize.Level2)
{
    int ret;
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite/mkdir", 0325);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 325,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID0);
        setgid(GID0);
        ret = mkdir("/storage/SystemJffsDacTestSuite/mkdir/Dac", NORWX);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1080
 * @tc.name       : securityDACTest1080
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1080, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite/mkdir", 0731);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 731,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = mkdir("/storage/SystemJffsDacTestSuite/mkdir/Dac", NORWX);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1090
 * @tc.name       : securityDACTest1090
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1090, TestSize.Level2)
{
    int ret;
    gid_t list[SINGLESIZE] = {0};
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite/mkdir", 0074);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 074,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        ret = mkdir("/storage/SystemJffsDacTestSuite/mkdir/Dac", NORWX);
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1100
 * @tc.name       : securityDACTest1100
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1100, TestSize.Level2)
{
    int ret;
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0175);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 175,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID0);
        ret = unlink("/storage/SystemJffsDacTestSuite/Dac.txt");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1150
 * @tc.name       : securityDACTest1150
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1150, TestSize.Level2)
{
    int ret;
    int fd = 0;
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0120);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 120,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID0);
        setgid(GID555);
        fd = open("/storage/SystemJffsDacTestSuite/Dac.txt", F_OK);
        if (fd >= 0) {
            close(fd);
        } else {
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1160
 * @tc.name       : securityDACTest1160
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1160, TestSize.Level2)
{
    int ret;
    int fd = 0;
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0564);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 564,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID0);
        setgid(GID555);
        fd = open("/storage/SystemJffsDacTestSuite/Dac.txt", F_OK);
        if (fd >= 0) {
            close(fd);
        } else {
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1200
 * @tc.name       : securityDACTest1200
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1200, TestSize.Level2)
{
    int ret;
    int fd = 0;
    gid_t list[SINGLESIZE] = {0};
    CreateTxt();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0637);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 637,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        fd = open("/storage/SystemJffsDacTestSuite/Dac.txt", F_OK);
        if (fd >= 0) {
            close(fd);
        } else {
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1210
 * @tc.name       : securityDACTest1210
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1210, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0031);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 031,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID555);
        setgid(GID0);
        dir = opendir("/storage/SystemJffsDacTestSuite/mkdir");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1220
 * @tc.name       : securityDACTest1220
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1220, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0712);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 312,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncNoCap();
        setuid(UID0);
        setgid(GID0);
        dir = opendir("/storage/SystemJffsDacTestSuite/mkdir");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1230
 * @tc.name       : securityDACTest1230
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1230, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0274);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 274,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID555);
        dir = opendir("/storage/SystemJffsDacTestSuite/mkdir");
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_1240
 * @tc.name       : securityDACTest1240
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(SystemJffsDacTestSuite, securityDACTest1240, TestSize.Level2)
{
    int ret;
    DIR* dir = nullptr;
    gid_t list[SINGLESIZE] = {0};
    CreateDir();
    ret = chmod("/storage/SystemJffsDacTestSuite", 0665);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in chmod 665,now uid=" << getuid();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        ChildFuncReadsearchCap();
        setuid(UID555);
        setgid(GID555);
        setgroups(SINGLESIZE, list);
        dir = opendir("/storage/SystemJffsDacTestSuite/mkdir");
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