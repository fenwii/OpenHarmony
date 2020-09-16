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

#ifndef KERNEL_LITE_FILESYSTEMTEST
#define KERNEL_LITE_FILESYSTEMTEST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <gtest/gtest.h>
#include "utils.h"
#include "log.h"
#include "KernelConstants.h"
#include "libfs.h"

class FileSystemTest : public::testing::Test {
protected:
    char *mCurPath;
    void SetUp();
    void TearDown();
};

// Creating Folders and Files for the Test
#define FILE0           "FILE0"                 // FILE0
#define DIR0            "DIR0"                  // DIR0/
#define DIR0_FILE0      "DIR0_FILE0"            // ├── DIR0_FILE0
#define DIR0_DIR0       "DIR0_DIR0"             // ├── DIR0_DIR0/
#define DIR0_DIR1       "DIR0_DIR1"             // └── DIR0_DIR1/
#define DIR0_DIR1_FILE0 "DIR0_DIR1_FILE0"       //     ├── DIR0_DIR1_FILE0
#define DIR0_DIR1_DIR0  "DIR0_DIR1_DIR0"        //     └── DIR0_DIR1_DIR0/

// Creating Folders and Files for the Test
#define CreateTestFolder()  do {                                                                                    \
    int thisFd;                                                                                                     \
    ASSERT_NE(mkdir(DIR0, 0777), -1) << "> mkdir errno = " << errno;                                                \
    ASSERT_NE((thisFd = creat((DIR0 "/" DIR0_FILE0), 0777)), -1) << "> creat errno = " << errno;                    \
    ASSERT_NE(close(thisFd), -1) << "> close errno = " << errno;                                                    \
    ASSERT_NE(mkdir((DIR0 "/" DIR0_DIR0), 0777), -1) << "> mkdir errno = " << errno;                                \
    ASSERT_NE(mkdir((DIR0 "/" DIR0_DIR1), 0777), -1) << "> mkdir errno = " << errno;                                \
    ASSERT_NE((thisFd = creat((DIR0 "/" DIR0_DIR1"/" DIR0_DIR1_FILE0), 0777)), -1) << "> creat errno = " << errno;  \
    ASSERT_NE(close(thisFd), -1) << "> close errno = " << errno;                                                    \
    ASSERT_NE(mkdir((DIR0 "/" DIR0_DIR1"/" DIR0_DIR1_DIR0), 0777), -1) << "> mkdir errno = " << errno;              \
    } while (0)

// write and close
#define WriteCloseTest(fd)  do {                                                             \
    char writeBuf[] = "this is a file";                                                      \
    EXPECT_NE(write(fd, writeBuf, sizeof(writeBuf)), -1) << "> write errno = " << errno;     \
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;                                 \
    } while (0)                                                                              \

// read and close
#define ReadCloseTest(fd)  do {                                                              \
    char writeBuf[] = "this is a file";                                                      \
    char readBuf[100];                                                                       \
    EXPECT_NE(read(fd, readBuf, 20), -1) << "> read errno = " << errno;                      \
    EXPECT_STREQ(writeBuf, readBuf) << "> writeBuf = " << writeBuf                           \
                                    << "\n> readBuf = " << readBuf;                          \
    EXPECT_NE(close(fd), -1) << "> close errno = " << errno;                                 \
    } while (0)                                                                              \

#endif
