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

#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT) || defined(LITE_FS_NFS)
/**
 * @tc.number   SUB_KERNEL_FS_UNISTD_0100
 * @tc.name     basic function test : access check whether the file exists.
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FileSystemTest, testAccess, TestSize.Level0)
{
    int fd = 0;
    fd = creat(FILE0, 0777);
    EXPECT_NE(fd, -1) << "> creat faild errno = " << errno;
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;
    EXPECT_EQ(access(FILE0, F_OK), 0) << "> access F_OK errno = " << errno;
    EXPECT_EQ(unlink(FILE0), 0) << "> remove errno = " << errno;
    EXPECT_NE(access(FILE0, F_OK), 0) << "> access F_OK expect faild but success";
}
#endif

#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT)
/** 
 * @tc.number   SUB_KERNEL_FS_UNISTD_0200
 * @tc.name     basic function test : switch to the current working directory.
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FileSystemTest, testChdir, TestSize.Level1)
{
    char testDir[MAX_PATH_SIZE];
    const char *expectDirStandard = TOP_DIR "/" DIR0;
    EXPECT_NE(mkdir(DIR0, 0777), -1) << "> mkdir errno = " << errno;
    EXPECT_NE(chdir(DIR0), -1) << "> chdir errno = " << errno;
    EXPECT_NE(getcwd(testDir, sizeof(testDir)), nullptr) << "> getcwd errno = " << errno;
    EXPECT_NE(chdir(TOP_DIR), -1) << "> chdir errno = " << errno;

    EXPECT_STREQ(testDir, expectDirStandard);
    LOG("> expectDirStandard  = %s", expectDirStandard);
    LOG("> testDir   = %s", testDir);
}
#endif

/**
 * @tc.number   SUB_KERNEL_FS_UNISTD_0300
 * @tc.name     basic function test : dup copy file description, then write and read
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_NFS)
HWTEST_F(FileSystemTest, testDup, TestSize.Level3)
{
    int fd = 0;
    int fdNew = 0;
    fd = open(FILE0, O_CREAT | O_RDWR, 0777);
    EXPECT_NE(fd, -1) << "> open faild errno = " << errno;
    WriteCloseTest(fd);
    fd = open(FILE0, O_RDONLY, 0777);
    EXPECT_NE(fd, -1) << "> open faild errno = " << errno;
    fdNew = dup(fd);
    EXPECT_NE(fdNew, -1) << "> dup errno = " << errno;
    ReadCloseTest(fdNew);
}
#endif

#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT) || defined(LITE_FS_NFS)
/**
 * @tc.number   SUB_KERNEL_FS_UNISTD_0400
 * @tc.name     basic function test : dup2 copy file description, then write and read
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FileSystemTest, testDup2, TestSize.Level3)
{
    int fd = 0;
    int fdNew = 0;
    fd = open(FILE0, O_CREAT | O_RDWR, 0777);
    EXPECT_NE(fd, -1) << "> open faild errno = " << errno;
    WriteCloseTest(fd);
    fd = open(FILE0, O_RDONLY, 0777);
    EXPECT_NE(fd, -1) << "> open faild errno = " << errno;
    EXPECT_NE(dup2(fd, fdNew), -1) << "> dup2 errno = " << errno;
    ReadCloseTest(fdNew);
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;
}
#endif

#if defined(LITE_FS_VFAT)
/**
 * @tc.number   SUB_KERNEL_FS_UNISTD_0500
 * @tc.name     basic function test : using ftruncate and truncate functions to change the file size
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FileSystemTest, testFtruncate, TestSize.Level1)
{
    struct stat statbuf;
    char writeBuf[] = "this is a file";
    int fd = 0;

    fd = open(FILE0, O_CREAT | O_RDWR, 0777);
    EXPECT_NE(fd, -1) << "> open faild errno = " << errno;
    EXPECT_NE(write(fd, "writeBuf", sizeof(writeBuf)), -1) << "> write errno = " << errno;

    EXPECT_NE(ftruncate(fd, 1000), -1) << "truncate errno = " << errno;
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;

    stat(FILE0, &statbuf);
    EXPECT_EQ(statbuf.st_size, 1000);

    EXPECT_NE(truncate(FILE0, 100), -1) << "truncate errno = " << errno;
    stat(FILE0, &statbuf);
    EXPECT_EQ(statbuf.st_size, 100);
}
#endif
