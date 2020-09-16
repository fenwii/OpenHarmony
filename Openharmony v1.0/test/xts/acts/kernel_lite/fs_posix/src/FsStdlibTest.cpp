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

/**
 * @tc.number   SUB_KERNEL_FS_STDLIB_0100
 * @tc.name     basic function test : mkstemp create a temporary file
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT)
HWTEST_F(FileSystemTest, testMkstemp, TestSize.Level2)
{
    int fd = 0;
    char tmpFileName[]= "tmpFile_XXXXXX";
    fd = mkstemp(tmpFileName);
    EXPECT_NE(fd, -1) << "> mkstemp errno = " <<errno;
    WriteCloseTest(fd);
    fd = open(tmpFileName, O_RDWR);
    EXPECT_NE(fd, -1) << "> open errno = " << errno;
    ReadCloseTest(fd);
    EXPECT_NE(unlink(tmpFileName), -1) << "> unlink errno = " << errno;
}
#endif

/**
 * @tc.number   SUB_KERNEL_FS_STDLIB_0200
 * @tc.name     basic function test : mkstemps create a temporary file
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT)
HWTEST_F(FileSystemTest, testMkstemps, TestSize.Level2)
{
    int fd = 0;
    char tmpFileName[] = "tmpFile_XXXXXX";
    fd = mkstemps(tmpFileName, 0);
    EXPECT_NE(fd, -1) << "> mkstemp errno = " <<errno;
    WriteCloseTest(fd);
    fd = open(tmpFileName, O_RDWR);
    EXPECT_NE(fd, -1) << "> open errno = " << errno;
    ReadCloseTest(fd);
    EXPECT_NE(unlink(tmpFileName), -1) << "> unlink errno = " << errno;
}
#endif

/**
 * @tc.number   SUB_KERNEL_FS_STDLIB_0300
 * @tc.name     basic function test : mkostemp create a temporary file with read and write
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT)
HWTEST_F(FileSystemTest, testMkostemp, TestSize.Level2)
{
    int fd = 0;
    char tmpFileName[] = "tmpFile_XXXXXX";
    fd = mkostemp(tmpFileName, O_RDWR);
    EXPECT_NE(fd, -1) << "> mkstemp errno = " <<errno;
    WriteCloseTest(fd);
    fd = open(tmpFileName, O_RDWR);
    EXPECT_NE(fd, -1) << "> open errno = " << errno;
    ReadCloseTest(fd);
    EXPECT_NE(unlink(tmpFileName), -1) << "> unlink errno = " << errno;
}
#endif

/**
 * @tc.number   SUB_KERNEL_FS_STDLIB_0400
 * @tc.name     basic function test : mktemp create a temporary file name, mkdtemp create a directory
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT)
HWTEST_F(FileSystemTest, testMktempMkdtemp, TestSize.Level2)
{
    char tmpFileNamePre[] = "tmpFile_XXXXXX";
    char tmpFileName[] = "tmpFile_XXXXXX";
    EXPECT_NE(mktemp(tmpFileName), nullptr) << "> mktemp errno = " << errno;
    EXPECT_STRNE(tmpFileName, tmpFileNamePre) << "> tmpFileName no change";

    char tmpDirName[] = "tmpDir_XXXXXXX";
    EXPECT_NE(mkdtemp(tmpDirName), nullptr) << "> mktemp errno = " << errno;
    EXPECT_NE(remove(tmpDirName), -1) << "> remove errno = " << errno;
}
#endif

/**
 * @tc.number   SUB_KERNEL_FS_STDLIB_0500
 * @tc.name     basic function test : Use the realpath function to obtain the path.
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT) || defined(LITE_FS_NFS)
HWTEST_F(FileSystemTest, testRealpath, TestSize.Level3)
{
    int fd = 0;
    fd = creat(FILE0, 0777);
    EXPECT_NE(fd, -1) << "> creat faild errno = " << errno;
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;

    // get Absolute Path
    const char *realPathStandard = TOP_DIR "/" FILE0;
    char *realPath = (char*)malloc(256);
    EXPECT_NE(realpath(FILE0, realPath), nullptr) << "> realpath errno = " << errno;
    EXPECT_STREQ(realPath, realPathStandard);
    LOG("> realPath = %s", realPath);
    free(realPath);
}
#endif

/**
 * @tc.number   SUB_KERNEL_FS_STDLIB_0600
 * @tc.name     basic function test : Use the rename function to rename directories and files.
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT) || defined(LITE_FS_NFS)
HWTEST_F(FileSystemTest, testRename, TestSize.Level3)
{
    int fd = 0;
    const char *newFileName = "FILE_NEW";
    const char *newDirName = "DIR_NEW";
    fd = creat(FILE0, 0777);
    EXPECT_NE(fd, -1) << "> creat faild errno = " << errno;
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;
    EXPECT_NE(mkdir(DIR0, 0777), -1) << "> mkdir errno = " << errno;
    EXPECT_NE(rename(FILE0, newFileName), -1) << "> rename errno = " << errno;
    EXPECT_NE(rename(DIR0, newDirName), -1) << "> rename errno = " << errno;

    EXPECT_NE(unlink(newFileName), -1) << "> unlink errno = " << errno;
    EXPECT_NE(rmdir(newDirName), -1) << "> rmdir errno = " << errno;
}
#endif
