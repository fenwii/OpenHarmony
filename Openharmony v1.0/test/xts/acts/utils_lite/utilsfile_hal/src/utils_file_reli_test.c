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

#include "hos_types.h"
#include <securec.h>
#include "hctest.h"
#include "utils_file.h"

#define FILE_SEEK_OFFSET_0 0
#define FILE_SEEK_OFFSET_20 20
#define FILE_SEEK_OFFSET_MINUS_20 (-20)
#define MAX_NUM_OF_OPENED_FILES 32
#define LENGTH_OF_READ_BUF 36
#define FILE_INDEX_31 31
#define LENGTH_OF_FILE_NAME_BUF 32

static const char* g_def = "utils_file_operation implement.";

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is UtilsFileReliTestSuite
 */
LITE_TEST_SUIT(utils, utilsFile, UtilsFileReliTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL UtilsFileReliTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL UtilsFileReliTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1300
 * @tc.name      : Creat file after max files opened
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : RELI
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileReliTestSuite, testCreatFileAfterMaxFilesOpened, LEVEL1)
{
    // Open 32 files
    int fd32[MAX_NUM_OF_OPENED_FILES] = {0};
    for (int i = 0; i < MAX_NUM_OF_OPENED_FILES; i++)
    { 
        int j = i + 1;
        char fileName32[LENGTH_OF_FILE_NAME_BUF] = {0};
        int size = sprintf_s(fileName32, sizeof(fileName32), "%s%d", "testReli101-", j);
        if (size < 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        }
        fd32[i] = UtilsFileOpen(fileName32, O_RDWR_FS | O_CREAT_FS, 0);
        TEST_ASSERT_GREATER_THAN_INT(0, fd32[i]);
    } 
    // Open the 33th file  
    char* fileName33 = "testReli101-33";
    int fd33 = UtilsFileOpen(fileName33, O_RDWR_FS | O_CREAT_FS, 0);
    TEST_ASSERT_EQUAL_INT(-1, fd33);
    // Close file
    UtilsFileClose(fd32[0]);
    fd33 = UtilsFileOpen(fileName33, O_RDWR_FS | O_CREAT_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd33);
    UtilsFileClose(fd33);
    // Delete all files
    for (int i = 0; i < MAX_NUM_OF_OPENED_FILES; i++)
    { 
        int j = i + 1;
        char fileName32[LENGTH_OF_FILE_NAME_BUF] = {0};
        int size = sprintf_s(fileName32, sizeof(fileName32), "%s%d", "testReli101-", j);
        if (size < 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        }
        UtilsFileDelete(fileName32);
    } 
    UtilsFileDelete(fileName33);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1300
 * @tc.name      : Delete file after max files opened
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : RELI
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileReliTestSuite, testDeleteFileAfterMaxFilesOpened, LEVEL1)
{
    // Open 32 files
    int fd32[MAX_NUM_OF_OPENED_FILES] = {0};
    for (int i = 0; i < MAX_NUM_OF_OPENED_FILES; i++)
    { 
        int j = i + 1;
        char fileName32[LENGTH_OF_FILE_NAME_BUF] = {0};
        int size = sprintf_s(fileName32, sizeof(fileName32), "%s%d", "testReli101-", j);
        if (size < 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        }
        fd32[i] = UtilsFileOpen(fileName32, O_RDWR_FS | O_CREAT_FS, 0);
        UtilsFileWrite(fd32[i], g_def, strlen(g_def));
    } 
    // Delete file
    char* fileName1 = "testReli101-1";
    int ret = UtilsFileDelete(fileName1);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    // Close file
    UtilsFileClose(fd32[FILE_INDEX_31]);
    ret = UtilsFileDelete(fileName1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Delete all files
    for (int i = 0; i < MAX_NUM_OF_OPENED_FILES; i++)
    { 
        int j = i + 1;
        char fileName32[LENGTH_OF_FILE_NAME_BUF] = {0};
        int size = sprintf_s(fileName32, sizeof(fileName32), "%s%d", "testReli101-", j);
        if (size < 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        }
        UtilsFileDelete(fileName32);
    } 
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1300
 * @tc.name      : Copy file after max files opened
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : RELI
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileReliTestSuite, testCopyFileAfterMaxFilesOpened, LEVEL1)
{
    // Open 32 files
    int fd32[MAX_NUM_OF_OPENED_FILES] = {0};
    for (int i = 0; i < MAX_NUM_OF_OPENED_FILES; i++)
    { 
        int j = i + 1;
        char fileName32[LENGTH_OF_FILE_NAME_BUF] = {0};
        int size = sprintf_s(fileName32, sizeof(fileName32), "%s%d", "testReli101-", j);
        if (size < 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        }
        fd32[i] = UtilsFileOpen(fileName32, O_RDWR_FS | O_CREAT_FS, 0);
        UtilsFileWrite(fd32[i], g_def, strlen(g_def));
    } 
    // Copy file
    char* fileName1 = "testReli101-1";
    char* fileNameCopy = "testReliCopy";
    int ret = UtilsFileCopy(fileName1, fileNameCopy);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    // Close first file
    UtilsFileClose(fd32[0]);
    ret = UtilsFileCopy(fileName1, fileNameCopy);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    // Close second file
    UtilsFileClose(fd32[1]);
    ret = UtilsFileCopy(fileName1, fileNameCopy);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Delete all files
    for (int i = 0; i < MAX_NUM_OF_OPENED_FILES; i++)
    { 
        int j = i + 1;
        char fileName32[LENGTH_OF_FILE_NAME_BUF] = {0};
        int size = sprintf_s(fileName32, sizeof(fileName32), "%s%d", "testReli101-", j);
        if (size < 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        }
        UtilsFileDelete(fileName32);
    } 
    UtilsFileDelete(fileNameCopy);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1300
 * @tc.name      : Move file after max files opened
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : RELI
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileReliTestSuite, testMoveFileAfterMaxFilesOpened, LEVEL1)
{
    // Open 32 files
    int fd32[MAX_NUM_OF_OPENED_FILES] = {0};
    for (int i = 0; i < MAX_NUM_OF_OPENED_FILES; i++)
    { 
        int j = i + 1;
        char fileName32[LENGTH_OF_FILE_NAME_BUF] = {0};
        int size = sprintf_s(fileName32, sizeof(fileName32), "%s%d", "testReli101-", j);
        if (size < 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        }
        fd32[i] = UtilsFileOpen(fileName32, O_RDWR_FS | O_CREAT_FS, 0);
        UtilsFileWrite(fd32[i], g_def, strlen(g_def));
    }
    // Move file  
    char* fileName1 = "testReli101-1";
    char* fileNameMove = "testReliMove";
    int ret = UtilsFileMove(fileName1, fileNameMove);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    // Close first file
    UtilsFileClose(fd32[0]);
    ret = UtilsFileMove(fileName1, fileNameMove);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    // Close second file
    UtilsFileClose(fd32[1]);
    ret = UtilsFileMove(fileName1, fileNameMove);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Delete all files
    for (int i = 0; i < MAX_NUM_OF_OPENED_FILES; i++)
    { 
        int j = i + 1;
        char fileName32[LENGTH_OF_FILE_NAME_BUF] = {0};
        int size = sprintf_s(fileName32, sizeof(fileName32), "%s%d", "testReli101-", j);
        if (size < 0) {
        TEST_ASSERT_EQUAL_INT(0, 1);
        }
        UtilsFileDelete(fileName32);
    } 
    UtilsFileDelete(fileNameMove);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1400 
 * @tc.name      : File operation flow
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : RELI
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileReliTestSuite, testFileOperFlow001, LEVEL1)
{
    char* fileName1 = "testReli102a";
    char* fileName2 = "testReli102b";
    // Creat file
    int fd1 = UtilsFileOpen(fileName1, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd1, g_def, strlen(g_def));
    UtilsFileClose(fd1);
    // Copy file
    UtilsFileCopy(fileName1, fileName2);
    // File operation for copied file
    unsigned int fileLen = 0;
    int ret = UtilsFileStat(fileName2, &fileLen); 
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd2 = UtilsFileOpen(fileName2, O_RDWR_FS | O_APPEND_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd2);
    ret = UtilsFileWrite(fd2, g_def, strlen(g_def));
    TEST_ASSERT_GREATER_THAN_INT(0, ret);
    ret = UtilsFileSeek(fd2, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    char buf[LENGTH_OF_READ_BUF] = {0};
    ret = UtilsFileRead(fd2, buf, LENGTH_OF_READ_BUF);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    ret = UtilsFileClose(fd2);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Delete all files
    ret = UtilsFileDelete(fileName1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = UtilsFileDelete(fileName2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1400 
 * @tc.name      : File operation flow
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : RELI
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileReliTestSuite, testFileOperFlow002, LEVEL1)
{
    char* fileName1 = "testReli102a";
    char* fileName2 = "testReli102b";
    char* fileName3 = "testReli102c";
    // Creat file
    int fd1 = UtilsFileOpen(fileName1, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd1, g_def, strlen(g_def));
    UtilsFileClose(fd1);
    // Copy file
    UtilsFileCopy(fileName1, fileName2);
    // Move the copied file
    int ret = UtilsFileMove(fileName2, fileName3);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // File operation for moved file
    unsigned int fileLen = 0;
    ret = UtilsFileStat(fileName3, &fileLen); 
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd2 = UtilsFileOpen(fileName3, O_RDWR_FS | O_APPEND_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd2);
    ret = UtilsFileWrite(fd2, g_def, strlen(g_def));
    TEST_ASSERT_GREATER_THAN_INT(0, ret);
    ret = UtilsFileSeek(fd2, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    char buf[LENGTH_OF_READ_BUF] = {0};
    ret = UtilsFileRead(fd2, buf, LENGTH_OF_READ_BUF);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    ret = UtilsFileClose(fd2);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Delete all files
    ret = UtilsFileDelete(fileName1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = UtilsFileDelete(fileName2);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    ret = UtilsFileDelete(fileName3);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1500
 * @tc.name      : File operation flow for empty file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : RELI
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileReliTestSuite, testEmptyFileOperFlow001, LEVEL1)
{
    char* fileName1 = "testReli103a";
    char* fileName2 = "testReli103b";
    // Creat an empty file
    int fd1 = UtilsFileOpen(fileName1, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileClose(fd1);
    // Copy file
    int ret = UtilsFileCopy(fileName1, fileName2);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // File operation for copied file
    unsigned int fileLen = 0;
    ret = UtilsFileStat(fileName2, &fileLen); 
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd2 = UtilsFileOpen(fileName2, O_RDWR_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd2);
    ret = UtilsFileSeek(fd2, FILE_SEEK_OFFSET_0, SEEK_SET_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    char buf[LENGTH_OF_READ_BUF] = {0};
    ret = UtilsFileRead(fd2, buf, LENGTH_OF_READ_BUF);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    ret = UtilsFileClose(fd2);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Delete all files
    ret = UtilsFileDelete(fileName1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = UtilsFileDelete(fileName2);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1500
 * @tc.name      : File operation flow for empty file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : RELI
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileReliTestSuite, testEmptyFileOperFlow002, LEVEL1)
{
    char* fileName1 = "testReli103a";
    char* fileName2 = "testReli103b";
    char* fileName3 = "testReli103c";
    // Creat an empty file
    int fd1 = UtilsFileOpen(fileName1, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileClose(fd1);
    // Copy file
    UtilsFileCopy(fileName1, fileName2);
    // Move the copied file
    int ret = UtilsFileMove(fileName2, fileName3);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // File operation for moved file
    unsigned int fileLen = 0;
    ret = UtilsFileStat(fileName3, &fileLen); 
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd2 = UtilsFileOpen(fileName3, O_RDWR_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd2);
    ret = UtilsFileSeek(fd2, FILE_SEEK_OFFSET_0, SEEK_SET_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    char buf[LENGTH_OF_READ_BUF] = {0};
    ret = UtilsFileRead(fd2, buf, LENGTH_OF_READ_BUF);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    ret = UtilsFileClose(fd2);
    TEST_ASSERT_EQUAL_INT(0, ret);
    // Delete all files
    ret = UtilsFileDelete(fileName1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = UtilsFileDelete(fileName2);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    ret = UtilsFileDelete(fileName3);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

RUN_TEST_SUITE(UtilsFileReliTestSuite);
