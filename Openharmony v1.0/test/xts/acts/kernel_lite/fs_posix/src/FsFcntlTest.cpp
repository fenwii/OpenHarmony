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
 * @tc.number   SUB_KERNEL_FS_FCNTL_0100
 * @tc.name     basic function test : {fcntl} Test of three basic functions
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FileSystemTest, testFcntl, TestSize.Level3)
{
    int fd = 0;
    EXPECT_NE((fd = open(FILE0, O_CREAT | O_RDWR, 0777)), -1) << "> open faild errno = " << errno;
    WriteCloseTest(fd);

#if defined(LITE_FS_NFS)
    // F_DUPFD
    int fdNew = 0;
    EXPECT_NE((fd = open(FILE0, O_RDONLY, 0777)), -1) << "> open faild errno = " << errno;
    EXPECT_NE((fdNew = fcntl(fd, F_DUPFD)), -1) << "> fcntl errno = " << errno;
    ReadCloseTest(fdNew);
#endif
    int flagReadWrite = GetRandom(3) - 1;       // 0 is O_RDONLY, 1 is O_WRONLY, 2 is O_RDWR
    EXPECT_NE((fd = open(FILE0, flagReadWrite, 0777)), -1) << "> open faild errno = " << errno;

    // F_GETFL
    int flagGet = 0;
    EXPECT_NE((flagGet = fcntl(fd, F_GETFL)), -1) << "> fcntl errno = " << errno;
    EXPECT_EQ(flagReadWrite, (flagGet & O_ACCMODE)) << "> flagReadWrite != (flagGet & O_ACCMODE)";

    // F_SETFL
    int flagSet = flagGet | O_APPEND | O_NONBLOCK;
    EXPECT_NE(fcntl(fd, F_SETFL, flagSet), -1) << "> fcntl errno = " << errno;

    // F_GETFL
    EXPECT_NE((flagGet = fcntl(fd, F_GETFL)), -1) << "> fcntl errno = " << errno;
    EXPECT_EQ(flagGet & O_APPEND, O_APPEND) << "> O_APPEND faild";
    EXPECT_EQ(flagGet & O_NONBLOCK, O_NONBLOCK) << "> O_NONBLOCK faild";

    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;
}
#endif

#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT) || defined(LITE_FS_NFS)
/**
 * @tc.number   SUB_KERNEL_FS_FCNTL_0200
 * @tc.name     basic function test : Setting the read and write positions by running the {lseek} function
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
HWTEST_F(FileSystemTest, testLseek, TestSize.Level3)
{
    int reLseek;
    int fd = 0;
    char writeBuf[100];
    memset(writeBuf, '1', 100);
    char readBuf[100];
    memset(writeBuf, '0', 100);

    // reLseek 0 -> 20
    fd = open(FILE0, O_CREAT | O_RDWR, 0777);
    EXPECT_NE(fd, -1) << "> open faild errno = " << errno;
    EXPECT_NE(write(fd, writeBuf, 20), -1) << "> write errno = " << errno;
    reLseek = lseek(fd, 0, SEEK_CUR);
    EXPECT_NE(reLseek, -1) << "> lseek errno = " << errno;
    EXPECT_EQ(reLseek, 20) << "> reLseek = " << reLseek;

    // reLseek 20 -> 10
    reLseek = lseek(fd, 10, SEEK_SET);
    EXPECT_NE(reLseek, -1) << "> lseek errno = " << errno;
    EXPECT_EQ(reLseek, 10) << "> reLseek = " << reLseek;

    // reLseek 10 -> 20
    EXPECT_NE(write(fd, writeBuf, 10), -1) << "> write errno = " << errno;
    EXPECT_NE((reLseek = lseek(fd, 0, SEEK_CUR)), -1) << "> lseek errno = " << errno;
    EXPECT_EQ(reLseek, 20) << "> reLseek = " << reLseek;

    // reLseek 20 -> 10
    reLseek = lseek(fd, -10, SEEK_END);
    EXPECT_NE(reLseek, -1) << "> lseek errno = " << errno;
    EXPECT_EQ(reLseek, 10) << "> reLseek = " << reLseek;

    // reLseek 10 -> 30
    EXPECT_NE(write(fd, writeBuf, 20), -1) << "> write errno = " << errno;
    reLseek = lseek(fd, 0, SEEK_CUR);
    EXPECT_NE(reLseek, -1) << "> lseek errno = " << errno;
    EXPECT_EQ(reLseek, 30) << "> reLseek = " << reLseek;

    // reLseek 30 -> 0
    reLseek = lseek(fd, 0, SEEK_SET);
    EXPECT_NE(reLseek, -1) << "> lseek errno = " << errno;
    EXPECT_EQ(reLseek, 0) << "> reLseek = " << reLseek;

    // reLseek 0 -> 30
    EXPECT_EQ(read(fd, readBuf, 50), 30) << "> read errno = " << errno;
    EXPECT_EQ(strncmp(readBuf, writeBuf, 30), 0) << "readBuf = " << readBuf;
    reLseek = lseek(fd, 0, SEEK_CUR);
    EXPECT_NE(reLseek, -1) << "> lseek errno = " << errno;
    EXPECT_EQ(reLseek, 30) << "> reLseek = " << reLseek;

    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;
}
#endif
