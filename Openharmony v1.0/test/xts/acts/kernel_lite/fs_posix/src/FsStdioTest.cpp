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
 * @tc.number   SUB_KERNEL_FS_STDIO_0100
 * @tc.name     basic function test : SUB_KERNEL_FS_1100  read and write with stream
 * @tc.desc     [C- SOFTWARE -0200]
 * @tc.size     SMALL
 * @tc.type     FUNC
 */
#if defined(LITE_FS_JFFS2) || defined(LITE_FS_VFAT)
HWTEST_F(FileSystemTest, testFILE, TestSize.Level2)
{
    FILE *fp;
    int fd = 0;
    char writeBuf[] = "this is a file";
    char readBuf[20];
    memset(readBuf, 0, sizeof(readBuf));

    // write
    fd = creat(FILE0, 0777);
    EXPECT_NE(fd, -1) << "> creat faild errno = " << errno;
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;
    fp = fopen(FILE0, "w+");
    EXPECT_NE(fp, nullptr) << "> fopen errno = " << errno;
    fwrite(writeBuf, sizeof(writeBuf), 1, fp);
    EXPECT_NE(fclose(fp), -1) << "> fclose errno =" <<errno;

    // read
    fp = fopen(FILE0, "r+");
    EXPECT_NE(fp, nullptr) << "> fopen errno = " << errno;
    EXPECT_NE(fread(readBuf, sizeof(writeBuf), 1, fp), 0) << "> fread errno = " <<errno;
    EXPECT_STREQ(writeBuf, readBuf) << "> writeBuf = " << writeBuf\
                                    << "\n> readBuf = " << readBuf;
    EXPECT_NE(fclose(fp), -1) << "> fclose errno =" <<errno;
}
#endif
