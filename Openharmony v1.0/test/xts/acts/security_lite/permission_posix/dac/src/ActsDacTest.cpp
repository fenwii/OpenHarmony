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

class DacTestSuite : public testing::Test {
protected:
    // SetUpTestCase：测试套预置动作,在第一个TestCase之前执行
    static void SetUpTestCase(void)
    {
        // uid=gid=555
        SetUid555Gid555();
        RemoveDir("/storage/DacTestSuite");
        RemoveDir("/storage/DacTestSuite1");
        // uid=gid=0
        SetUid0Gid0();
        RemoveDir("/storage/DacTestSuite");
        RemoveDir("/storage/DacTestSuite1");
    }
    // TearDownTestCase：测试套清理动作,在最后一个TestCase之后执行
    static void TearDownTestCase(void) {}
    // 用例的预置动作
    virtual void SetUp()
    {
        // uid=gid=0
        SetUid0Gid0();
    }
    // 用例的清理动作
    virtual void TearDown()
    {
        RemoveDir("/storage/DacTestSuite");
        RemoveDir("/storage/DacTestSuite1");
    }
};

static void NoChownCapFunc()
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

static void ChownCapFunc()
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
    capdata[CAP_TO_INDEX(CAP_CHOWN)].effective |= CAP_TO_MASK(CAP_CHOWN);
    capdata[CAP_TO_INDEX(CAP_FOWNER)].effective &= ~CAP_TO_MASK(CAP_FOWNER);
    capdata[CAP_TO_INDEX(CAP_DAC_OVERRIDE)].effective &= ~CAP_TO_MASK(CAP_DAC_OVERRIDE);
    capdata[CAP_TO_INDEX(CAP_DAC_READ_SEARCH)].effective &= ~CAP_TO_MASK(CAP_DAC_READ_SEARCH);
    ret = capset(&capheader, &capdata[0]);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
}

static void CreateTxt()
{
    int ret;
    int fd = 0;
    char cap[] = "DacTestSuite!\n";
    // uid=gid=0
    SetUid0Gid0();
    umask(ZEROUMASK);
    ret = mkdir("/storage/DacTestSuite", CHMOD700);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
    ret = mkdir("/storage/DacTestSuite/Dac", RWX);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
    fd = open("/storage/DacTestSuite/Dac.txt", O_WRONLY | O_CREAT | O_TRUNC, CHMOD700);
    if (fd >= 0) {
        write(fd, cap, sizeof(cap));
        close(fd);
    } else {
        EXPECT_GE(fd, 0) << "Creat txt error";
    }
}

static void CreateTxt1()
{
    int ret;
    int fd = 0;
    char cap[] = "DacTestSuite!\n";
    // uid=gid=0 & chown cap
    struct __user_cap_header_struct capheader;
    struct __user_cap_data_struct capdata[CAP_NUM];
    memset_s(&capheader, sizeof(struct __user_cap_header_struct), 0, sizeof(struct __user_cap_header_struct));
    memset_s(capdata, CAP_NUM * sizeof(struct __user_cap_data_struct), 0,
        CAP_NUM * sizeof(struct __user_cap_data_struct));
    capdata[0].permitted = 0xffffffff;
    capdata[1].permitted = 0xffffffff;
    capheader.version = _LINUX_CAPABILITY_VERSION_3;
    capdata[CAP_TO_INDEX(CAP_SETPCAP)].effective |= CAP_TO_MASK(CAP_SETPCAP);
    capdata[CAP_TO_INDEX(CAP_SETUID)].effective |= CAP_TO_MASK(CAP_SETUID);
    capdata[CAP_TO_INDEX(CAP_SETGID)].effective |= CAP_TO_MASK(CAP_SETGID);
    capdata[CAP_TO_INDEX(CAP_CHOWN)].effective |= CAP_TO_MASK(CAP_CHOWN);
    ret = capset(&capheader, &capdata[0]);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
    ret = setuid(UID0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set uid failed,now uid=" << getuid();
    ret = setgid(GID0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set gid failed,now gid=" << getgid();
    umask(ZEROUMASK);
    ret = mkdir("/storage/DacTestSuite1", CHMOD700);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
    ret = mkdir("/storage/DacTestSuite1/Dac1", RWX);
    EXPECT_EQ(ret, 0) << "ErrInfo: Now uid=" << getuid();
    fd = open("/storage/DacTestSuite1/Dac.txt", O_WRONLY | O_CREAT | O_TRUNC, CHMOD700);
    if (fd >= 0) {
        write(fd, cap, sizeof(cap));
        close(fd);
    } else {
        EXPECT_GE(fd, 0) << "Creat txt error";
    }
    ret = chown("/storage/DacTestSuite1/Dac.txt", UID555, GID555);
    EXPECT_EQ(ret, 0) << "ErrInfo: chown error,now uid=" << getuid();
    ret = chown("/storage/DacTestSuite1", UID555, GID555);
    EXPECT_EQ(ret, 0) << "ErrInfo: chown error,now uid=" << getuid();
}

static void ThreeProcessReadOneTxt()
{
    int status = 0;
    int fd = 0;
    pid_t pid;
    CreateTxt();
    for (int num = 0; num < NUM3; num++) {
        pid = fork();
        ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
        usleep(SLEEP_NUM);
        if (pid == 0) {
            break;
        }
    } // get one parent & Three children
    usleep(SLEEP_NUM);
    if (pid == 0) {
        SetUid0Gid0();
        int exitCode = 0;
        for (int number = 0; number < NUM1000; number++) {
            fd = open("/storage/DacTestSuite/Dac.txt", O_WRONLY);
            if (fd >= 0) {
                close(fd);
            } else {
                LOG("open txt error when the %d time", number);
                exitCode = 1;
                break;
            }
        }
        exit(exitCode);
    } else {
        SetUid555Gid555();
        for (int number2 = 0; number2 < NUM500; number2++) {
            fd = open("/storage/DacTestSuite/Dac.txt", O_WRONLY);
            if (fd >= 0) {
                EXPECT_EQ(fd, WRONGNUM) << "ErrInfo: Open txt without DAC,now uid=" << getuid() << ",No." << number2;
                close(fd);
                break;
            }
        }
        while (wait(&status) > 0) {
            usleep(SLEEP_NUM);
            EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
            EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo:Pid = " << wait(&status) <<
                ",the WEXITSTATUS return code is " << WEXITSTATUS(status);
        }
    }
}

static void TwoProcessReadTwoTxt()
{
    int status = 0;
    int fd = 0;
    CreateTxt();
    CreateTxt1();
    pid_t pid = fork();
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        SetUid0Gid0(); // uid=gid=0
        for (int number = 0; number < NUM1000; number++) {
            fd = open("/storage/DacTestSuite/Dac.txt", O_WRONLY); // uid=gid=0
            if (fd >= 0) {
                close(fd);
            } else {
                LOG("open txt error when the %d time", number);
                exitCode = 1;
                break;
            }
            fd = open("/storage/DacTestSuite1/Dac.txt", O_WRONLY); // uid=gid=555
            if (fd >= 0) {
                LOG("open txt with wrong uid&gid when the %d time", number);
                close(fd);
                exitCode = 1;
                break;
            }
        }
        exit(exitCode);
    } else {
        SetUid555Gid555(); // uid=gid=555
        for (int number2 = 0; number2 < NUM500; number2++) {
            fd = open("/storage/DacTestSuite/Dac.txt", O_WRONLY); // uid=gid=0
            if (fd >= 0) {
                EXPECT_EQ(fd, WRONGNUM) << "ErrInfo: Open txt,now uid=" << getuid() << ",No." << number2;
                close(fd);
                break;
            }
            fd = open("/storage/DacTestSuite1/Dac.txt", O_WRONLY); // uid=gid=1
            if (fd >= 0) {
                close(fd);
            } else {
                EXPECT_EQ(fd, 0) << "ErrInfo: Failed in open txt,now uid=" << getuid() << ",No." << number2;
                break;
            }
        }
        waitpid(pid, &status, 0);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}

static void TenProcessReadSameTxt()
{
    int ret;
    int status = 0;
    int fd = 0;
    CreateTxt();
    pid_t pid;
    for (int num = 0; num < NUM3; num++) {
        pid = fork();
        ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
        usleep(SLEEP_NUM);
        if (pid == 0) {
            ret = setuid(num);
            EXPECT_EQ(ret, 0) << "ErrInfo: Set uid failed,now uid=" << getuid();
            break;
        }
    } // get one parent & three children
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        for (int number = 0; number < NUM1000; number++) {
            fd = open("/storage/DacTestSuite/Dac.txt", O_WRONLY);
            if (getuid() == 0) {
                if (fd >= 0) {
                    close(fd);
                } else {
                    LOG("open txt error when the %d time", number);
                    exitCode = 1;
                    break;
                }
            } else {
                if (fd >= 0) {
                    LOG("open txt with wrong uid&gid when the %d time", number);
                    close(fd);
                    exitCode = 1;
                    break;
                }
            }
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
 * @tc.number     : SUB_SEC_AppSEC_PermissionMgmt_DAC_0140
 * @tc.name       : securityDACTest0140
 * @tc.desc       : [C- SECURITY -0200]
 * @tc.size       : MEDIUM
 * @tc.type       : FUNC
 */
HWTEST_F(DacTestSuite, securityDACTest0140, TestSize.Level2)
{
    int ret;
    int status = 0;
    CreateTxt();
    pid_t pid = fork();
    ASSERT_TRUE(pid >= 0) << "======== Fork Error! =========";
    usleep(SLEEP_NUM);
    if (pid == 0) {
        int exitCode = 0;
        NoChownCapFunc();
        // uid=gid=0
        setuid(UID0);
        setgid(GID0);
        ret = chmod("/storage/DacTestSuite/Dac.txt", CHMOD700);
        if (ret != 0) {
            LOG("Failed in chmod 700");
            exitCode = 1;
        }
        ret = chmod("/storage/DacTestSuite/Dac.txt", CHMOD111);
        if (ret != 0) {
            LOG("Failed in chmod 111");
            exitCode = 1;
        }
        ret = chmod("/storage/DacTestSuite/Dac.txt", -1);
        if (ret != 0) {
            LOG("Failed in chmod -1");
            exitCode = 1;
        }
        ret = chmod("/storage/DacTestSuite/Dac.txt", -777);
        if (ret != 0) {
            LOG("Failed in chmod -777");
            exitCode = 1;
        }
        // uid=gid=10000
        setuid(UID10000);
        setgid(GID10000);
        EXPECT_EQ(ret, 0) << "ErrInfo: Set gid failed,now gid=" << getgid();
        ret = chmod("/storage/DacTestSuite/Dac.txt", CHMOD777);
        EXPECT_EQ(ret, -1) << "ErrInfo: Chmod 777 with wrong uid,now uid=" << getuid();
        // restore
        setuid(UID0);
        setgid(GID0);
        chmod("/storage/DacTestSuite/Dac.txt", CHMOD777);
        exit(exitCode);
    } else {
        waitpid(pid, &status, 0);
        usleep(SLEEP_NUM);
        EXPECT_TRUE(WIFEXITED(status) > 0) << "ErrInfo: Exit error";
        EXPECT_EQ(WEXITSTATUS(status), 0) << "ErrInfo: WEXITSTATUS is " << WEXITSTATUS(status);
    }
}
