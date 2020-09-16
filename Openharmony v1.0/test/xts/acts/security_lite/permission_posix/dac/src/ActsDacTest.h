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
#ifndef XTS_ACTS_SECURITY_LITE_PERMISSSION_POSIX_DAC_SRC_ACTSDACTEST_H
#define XTS_ACTS_SECURITY_LITE_PERMISSSION_POSIX_DAC_SRC_ACTSDACTEST_H

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

constexpr int WRONGNUM = -1;
constexpr int NUM3 = 3;
constexpr int NUM500 = 500;
constexpr int NUM1000 = 1000;
constexpr int NUM3000 = 3000;

constexpr int ABNORMALINT = -100;
constexpr int SINGLESIZE = 1;
constexpr int CAP_NUM = 2;
constexpr int SLEEP_NUM = 500000;
constexpr unsigned int MAX_INT = 2147483647;

constexpr size_t SIZE1 = 1;
constexpr size_t SIZE2 = 2;
constexpr size_t SIZE3 = 3;
constexpr size_t SIZE253 = 253;
constexpr size_t SIZE254 = 254;
constexpr size_t SIZE255 = 255;
constexpr size_t SIZE512 = 512;
constexpr size_t MAX_SIZE = 65536;
constexpr size_t INVAILD_SIZE = 65537;

constexpr uid_t UID0 = 0;
constexpr uid_t UID555 = 555;
constexpr uid_t UID1000 = 1000;
constexpr uid_t UID10000 = 10000;
constexpr gid_t GID0 = 0;
constexpr gid_t GID555 = 555;
constexpr gid_t GID1000 = 1000;
constexpr gid_t GID10000 = 10000;

constexpr mode_t ZEROUMASK = 0000;
constexpr mode_t NORWX = 0001;
constexpr mode_t RWX = 0777;
constexpr mode_t CHMOD000 = 00000;
constexpr mode_t CHMOD111 = 00111;
constexpr mode_t CHMOD700 = 00700;
constexpr mode_t CHMOD777 = 00777;

extern "C" {
#define LOG(format, ...) fprintf(stdout, format "\n", ##__VA_ARGS__)
}

static int RemoveDir(const char* dirname)
{
    char curDir[] = ".";
    char upDir[] = "..";
    char updirname[SIZE512];
    DIR* dir = nullptr;
    struct dirent* dp = nullptr;
    struct stat upDirStat;
    struct __user_cap_header_struct capheader;
    struct __user_cap_data_struct capdata[CAP_NUM];
    memset_s(&capheader, sizeof(struct __user_cap_header_struct), 0, sizeof(struct __user_cap_header_struct));
    memset_s(capdata, CAP_NUM * sizeof(struct __user_cap_data_struct), 0,
        CAP_NUM * sizeof(struct __user_cap_data_struct));
    capdata[0].permitted = 0xffffffff;
    capdata[1].permitted = 0xffffffff;
    capdata[0].effective = 0xffffffff;
    capdata[1].effective = 0xffffffff;
    capheader.version = _LINUX_CAPABILITY_VERSION_3;
    capset(&capheader, &capdata[0]);
    // 参数传递进来的目录不存在，直接返回
    if (access(dirname, F_OK != 0)) {
        return 0;
    }
    dir = opendir(dirname);
    while ((dp = readdir(dir)) != nullptr) {
        if ((strcmp(curDir, dp->d_name) == 0) || (strcmp(upDir, dp->d_name) == 0)) {
            continue;
        }
        int spr = sprintf_s(updirname, SIZE512, "%s/%s", dirname, dp->d_name);
        if (spr == -1) {
            closedir(dir);
            return -1;
        }
        stat(updirname, &upDirStat);
        if (upDirStat.st_mode & S_IFDIR) { // 目录文件，递归删除目录中内容
            RemoveDir(updirname);          // 递归调用
        } else {                           // 普通文件直接删除
            unlink(updirname);
        }
    }
    closedir(dir);
    int ret = rmdir(dirname); // 删除空目录
    if (ret != 0) {
        return -1;
    }
    capdata[CAP_TO_INDEX(CAP_DAC_OVERRIDE)].effective &= ~CAP_TO_MASK(CAP_DAC_OVERRIDE);
    capdata[CAP_TO_INDEX(CAP_DAC_READ_SEARCH)].effective &= ~CAP_TO_MASK(CAP_DAC_READ_SEARCH);
    capset(&capheader, &capdata[0]);
    return 0;
}

static void SetUid0Gid0()
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
    ret = capset(&capheader, &capdata[0]);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
    ret = setuid(UID0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set uid failed,now uid=" << getuid();
    ret = setgid(GID0);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set gid failed,now gid=" << getgid();
}

static void SetUid555Gid555()
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
    ret = capset(&capheader, &capdata[0]);
    EXPECT_EQ(ret, 0) << "ErrInfo: Failed in setting privileges";
    ret = setuid(UID555);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set uid failed,now uid=" << getuid();
    ret = setgid(GID555);
    EXPECT_EQ(ret, 0) << "ErrInfo: Set gid failed,now gid=" << getgid();
}

#endif