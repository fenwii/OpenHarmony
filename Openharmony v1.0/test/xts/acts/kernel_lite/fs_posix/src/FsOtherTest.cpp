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
#include "FileSystemTest.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/statvfs.h>
#include <sys/statfs.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <ftw.h>
#include <libgen.h>

#include <gtest/gtest.h>

#include "utils.h"
#include "log.h"
#include "KernelConstants.h"
#include "libfs.h"

using namespace testing::ext;

/**
 * @tc.number   SUB_KERNEL_FS_OTHER_0100
 * @tc.name     basic function test : get dirname, get current dir name, and get basename
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT)
HWTEST_F(FileSystemTest, testPath, TestSize.Level1)
{
    int fd = 0;
    fd = creat(FILE0, 0777);
    EXPECT_NE(fd, -1) << "> creat faild errno = " << errno;
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;

    // get dir
    char *workDir = dirname((char*)FILE0);
    EXPECT_NE(workDir, nullptr) << "> dirname errno = " << errno;
    EXPECT_STREQ(".", workDir);
    LOG("> workDir = %s", workDir);

    // get current dir name
    const char *currentDirStandard = TOP_DIR;
    char *currentDir = get_current_dir_name();
    EXPECT_NE(currentDir, nullptr);
    EXPECT_STREQ(currentDir, currentDirStandard);
    LOG("> currentDir = %s", currentDir);

    // get file name
    char *desName = basename((char*)FILE0);
    EXPECT_NE(desName, nullptr) << "> basename errno = " << errno;
    EXPECT_STREQ(desName, FILE0);
    LOG("> desName = %s", desName);
}
#endif

// check file or directory for ftw
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT) || defined(LITE_FS_NFS)
int ftwCheckDirTree(const char *path, const struct stat *sb, int flag)
{
    const char file0[] = DIR0 "/" DIR0_FILE0;
    const char file1[] = DIR0 "/" DIR0_DIR1 "/" DIR0_DIR1_FILE0;
    const char dir0[] = DIR0;
    const char dir1[] = DIR0 "/" DIR0_DIR0;
    const char dir2[] = DIR0 "/" DIR0_DIR1;
    const char dir3[] = DIR0 "/" DIR0_DIR1"/" DIR0_DIR1_DIR0;
    if (flag == FTW_F) {
        if (strncmp(path, file0, sizeof(file0)) == 0) {
            LOG("> File %s", file0);
        } else if (strncmp(path, file1, sizeof(file1)) == 0) {
            LOG("> File %s", file1);
        } else {
            LOG("> File error %s", path);
            return -1;
        }
    } else if (flag == FTW_D) {
        if (strncmp(path, dir0, sizeof(dir0)) == 0) {
            LOG("> Dir  %s", DIR0);
        } else if (strncmp(path, dir1, sizeof(dir1)) == 0) {
            LOG("> Dir  %s", dir1);
        } else if (strncmp(path, dir2, sizeof(dir2)) == 0) {
            LOG("> Dir  %s", dir2);
        } else if (strncmp(path, dir3, sizeof(dir3)) == 0) {
            LOG("> Dir  %s", dir3);
        } else {
            LOG("> File error  %s", path);
            return -1;
        }
    }
    return 0;
}

// check file or directory for nftw
int nftwCheckDirTree(const char *path, const struct stat *sb, int flag, struct FTW *s)
{
    const char file0[] = DIR0 "/" DIR0_FILE0;
    const char file1[] = DIR0 "/" DIR0_DIR1 "/" DIR0_DIR1_FILE0;
    const char dir0[] = DIR0;
    const char dir1[] = DIR0 "/" DIR0_DIR0;
    const char dir2[] = DIR0 "/" DIR0_DIR1;
    const char dir3[] = DIR0 "/" DIR0_DIR1"/" DIR0_DIR1_DIR0;
    if (flag == FTW_F) {
        if (strncmp(path, file0, sizeof(file0)) == 0) {
            LOG("> File %s", file0);
        } else if (strncmp(path, file1, sizeof(file1)) == 0) {
            LOG("> File %s", file1);
        } else {
            LOG("> File %s", path);
            return -1;
        }
    } else if (flag == FTW_D) {
        if (strncmp(path, dir0, sizeof(dir0)) == 0) {
            LOG("> Dir  %s", DIR0);
        } else if (strncmp(path, dir1, sizeof(dir1)) == 0) {
            LOG("> Dir  %s", dir1);
        } else if (strncmp(path, dir2, sizeof(dir2)) == 0) {
            LOG("> Dir  %s", dir2);
        } else if (strncmp(path, dir3, sizeof(dir3)) == 0) {
            LOG("> Dir  %s", dir3);
        } else {
            LOG("> File %s", path);
            return -1;
        }
    }
    return 0;
}

/**
 * @tc.number   SUB_KERNEL_FS_OTHER_0200
 * @tc.name     basic function test : use ftw and nftw check file tree
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FileSystemTest, testFtw, TestSize.Level3)
{
    CreateTestFolder();

    LOG("> to check ftw");
    EXPECT_EQ(ftw(DIR0, ftwCheckDirTree, 100), 0) << "> ftw error";

    LOG("> to check nftw");
    EXPECT_EQ(nftw(DIR0, nftwCheckDirTree, 100, 0), 0) << "> ftw error";
}
#endif

#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT) || defined(LITE_FS_NFS)
/**
 * @tc.number   SUB_KERNEL_FS_OTHER_0300
 * @tc.name     basic function test : use statvfs and statfs check file system information.
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FileSystemTest, test, TestSize.Level2)
{
    struct statvfs vfsBuf;
    struct statfs fsBuf;

    statvfs(".", &vfsBuf);
    LOG("vfsBuf.f_bsise = %lu", vfsBuf.f_bsize);        // File system block size.
    LOG("vfsBuf.f_frsize = %lu", vfsBuf.f_frsize);      // Fundamental file system block size.
    LOG("vfsBuf.f_blocks = %lu", vfsBuf.f_blocks);      // Total number of blocks on file system in units of f_frsize.
    LOG("vfsBuf.f_bfree = %lu", vfsBuf.f_bfree);        // Total number of free blocks.
    LOG("vfsBuf.f_bavail = %lu", vfsBuf.f_bavail);      // Number of free blocks available to non-privileged process.
    LOG("vfsBuf.f_files = %lu", vfsBuf.f_files);        // Total number of file serial numbers.
    LOG("vfsBuf.f_ffree = %lu", vfsBuf.f_ffree);        // Total number of free file serial numbers.
    LOG("vfsBuf.f_favail = %lu", vfsBuf.f_favail);      // Number of i-nodes available to unprivileged process.
    LOG("vfsBuf.f_fsid = %lu", vfsBuf.f_fsid);          // File system ID.
    LOG("vfsBuf.f_flag = %lu", vfsBuf.f_flag);          // Bit mask of f_flag values.
    LOG("vfsBuf.f_namemax = %lu", vfsBuf.f_namemax);    // Maximum filename length.

    statfs(".", &fsBuf);
    LOG("fsBuf.f_type = %lu", fsBuf.f_type);            // Type of filesystem.
    LOG("fsBuf.f_bsize = %lu", fsBuf.f_bsize);          // Optimal transfer block size.
    LOG("fsBuf.f_blocks = %lu", fsBuf.f_blocks);        // Total data blocks in filesystem.
    LOG("fsBuf.f_bfree = %lu", fsBuf.f_bfree);          // Total data blocks in filesystem.
    LOG("fsBuf.f_bavail = %lu", fsBuf.f_bavail);        // Free blocks available to unprivileged user.
    LOG("fsBuf.f_files = %lu", fsBuf.f_files);          // Total file nodes in filesystem.
    LOG("fsBuf.f_ffree = %lu", fsBuf.f_ffree);          // Free file nodes in filesystem.
    LOG("fsBuf.f_fsid.__val[0] = %d", fsBuf.f_fsid.__val[0]);   // Filesystem ID.
    LOG("fsBuf.f_fsid.__val[1] = %d", fsBuf.f_fsid.__val[1]);   // Filesystem ID.
    LOG("fsBuf.f_namelen = %ld", fsBuf.f_namelen);      // Maximum length of filenames.

    EXPECT_EQ(vfsBuf.f_bsize, fsBuf.f_bsize);
    EXPECT_EQ(vfsBuf.f_blocks, fsBuf.f_blocks);
    EXPECT_EQ(vfsBuf.f_bfree, fsBuf.f_bfree);
    EXPECT_EQ(vfsBuf.f_bavail, fsBuf.f_bavail);
    EXPECT_EQ(vfsBuf.f_files, fsBuf.f_files);
    EXPECT_EQ(vfsBuf.f_ffree, fsBuf.f_ffree);
    EXPECT_EQ(vfsBuf.f_namemax, fsBuf.f_namelen);
}
#endif
