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

#define QUERY_TIMES    50
#define FILE_SEEK_OFFSET_10 10
#define FILE_SEEK_OFFSET_20 20
#define FILE_SEEK_OFFSET_50 50
#define FILE_SEEK_OFFSET_MINUS_10 (-10)
#define FILE_SEEK_OFFSET_MINUS_20 (-20)
#define FILE_SEEK_OFFSET_MINUS_50 (-50)
#define LENGTH_OF_READ_BUF 36

static const char* g_def = "utils_file_operation implement.";

/**
 * @tc.desc      : register a test suite, this suite is used to test basic flow and interface dependency
 * @param        : subsystem name is utils
 * @param        : module name is utilsFile
 * @param        : test suit name is UtilsFileFuncTestSuite
 */
LITE_TEST_SUIT(utils, utilsFile, UtilsFileFuncTestSuite);

/**
 * @tc.setup     : setup for all testcases
 * @return       : setup result, TRUE is success, FALSE is fail
 */
static BOOL UtilsFileFuncTestSuiteSetUp(void)
{
    return TRUE;
}

/**
 * @tc.teardown  : teardown for all testcases
 * @return       : teardown result, TRUE is success, FALSE is fail
 */
static BOOL UtilsFileFuncTestSuiteTearDown(void)
{
    printf("+-------------------------------------------+\n");
    return TRUE;
}

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file creat/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCreatAndClose001, LEVEL1)
{
    char* fileName = "testfile101";
    int fd = UtilsFileOpen(fileName, O_RDONLY_FS | O_CREAT_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file creat/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCreatAndClose002, LEVEL1)
{
    char* fileName = "testfile102";
    int fd = UtilsFileOpen(fileName, O_WRONLY_FS | O_CREAT_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file creat/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCreatAndClose003, LEVEL1)
{
    char* fileName = "testfile103";
    int fd = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file open/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileOpenAndClose001, LEVEL1)
{
    char* fileName = "testfile104";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDONLY_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file open/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileOpenAndClose002, LEVEL1)
{
    char* fileName = "testfile105";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_WRONLY_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file open/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileOpenAndClose003, LEVEL1)
{
    char* fileName = "testfile106";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file open/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileOpenAndClose004, LEVEL1)
{
    char* fileName = "testfile107";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS | O_TRUNC_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file open/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileOpenAndClose005, LEVEL1)
{
    char* fileName = "testfile108";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS | O_APPEND_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200
 * @tc.name      : File operation for file creat/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCreatAndClose004, LEVEL1)
{
    char* fileName = "testfile109";
    int fd = UtilsFileOpen(fileName, O_RDONLY_FS | O_CREAT_FS | O_EXCL_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd1 = UtilsFileOpen(fileName, O_RDONLY_FS | O_CREAT_FS | O_EXCL_FS, 0);
    TEST_ASSERT_EQUAL_INT(-1, fd1);
    int ret1 = UtilsFileClose(fd1);
    TEST_ASSERT_EQUAL_INT(-1, ret1);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200 
 * @tc.name      : File operation for file creat/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCreatAndClose005, LEVEL1)
{
    char* fileName = "testfile110";
    int fd = UtilsFileOpen(fileName, O_WRONLY_FS | O_CREAT_FS | O_EXCL_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd1 = UtilsFileOpen(fileName, O_WRONLY_FS | O_CREAT_FS | O_EXCL_FS, 0);
    TEST_ASSERT_EQUAL_INT(-1, fd1);
    int ret1 = UtilsFileClose(fd1);
    TEST_ASSERT_EQUAL_INT(-1, ret1);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200 
 * @tc.name      : File operation for file creat/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCreatAndClose006, LEVEL1)
{
    char* fileName = "testfile111";
    int fd = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS | O_EXCL_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd1 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS | O_EXCL_FS, 0);
    TEST_ASSERT_EQUAL_INT(-1, fd1);
    int ret1 = UtilsFileClose(fd1);
    TEST_ASSERT_EQUAL_INT(-1, ret1);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200 
 * @tc.name      : File operation for file creat/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCreatAndClose007, LEVEL1)
{
    char* fileName = "testfile112";
    int fd = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS | O_EXCL_FS | O_TRUNC_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd1 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS | O_EXCL_FS | O_TRUNC_FS, 0);
    TEST_ASSERT_EQUAL_INT(-1, fd1);
    int ret1 = UtilsFileClose(fd1);
    TEST_ASSERT_EQUAL_INT(-1, ret1);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200 
 * @tc.name      : File operation for file creat/close
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCreatAndClose008, LEVEL1)
{
    char* fileName = "testfile113";
    int fd = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS | O_EXCL_FS | O_APPEND_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(0, ret);
    int fd1 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS | O_EXCL_FS | O_APPEND_FS, 0);
    TEST_ASSERT_EQUAL_INT(-1, fd1);
    int ret1 = UtilsFileClose(fd1);
    TEST_ASSERT_EQUAL_INT(-1, ret1);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100 
 * @tc.name      : File operation for file write
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileWrite001, LEVEL1)
{
    char* fileName = "testfile114";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileWrite(fd, g_def, strlen(g_def));
    TEST_ASSERT_GREATER_THAN_INT(0, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : File operation for file write
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileWrite002, LEVEL1)
{
    char* fileName = "testfile115";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS | O_APPEND_FS, 0);
    int ret = UtilsFileWrite(fd, g_def, strlen(g_def));
    TEST_ASSERT_GREATER_THAN_INT(0, ret);
    UtilsFileClose(fd);
    int fd1 = UtilsFileOpen(fileName, O_RDWR_FS | O_TRUNC_FS, 0);
    int ret1 = UtilsFileWrite(fd1, g_def, strlen(g_def));
    TEST_ASSERT_GREATER_THAN_INT(0, ret1);
    UtilsFileClose(fd1);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : Creat file with long file name
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testCreatLongNameFile, LEVEL1)
{
    char* fileName = "testLongFileName116-Ab123456789";
    int fd = UtilsFileOpen(fileName, O_RDONLY_FS | O_CREAT_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_100
 * @tc.name      : Creat file with special characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testCreatFileWithSpecChar, LEVEL1)
{
    char* fileName = "case117-~!@#$%^&*()+_/:?<;>|\\";
    int fd = UtilsFileOpen(fileName, O_RDONLY_FS | O_CREAT_FS, 0);
    TEST_ASSERT_GREATER_THAN_INT(0, fd);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200 
 * @tc.name      : Open none exist file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testOpenNotExistFile, LEVEL1)
{
    char* fileName = "fileNotExist118";
    int fd = UtilsFileOpen(fileName, O_RDONLY_FS, 0);
    TEST_ASSERT_EQUAL_INT(-1, fd);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200 
 * @tc.name      : Write none exist file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testWriteNotExistFile, LEVEL1)
{
    int fd = 1073;
    int ret = UtilsFileWrite(fd, g_def, strlen(g_def));
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200 
 * @tc.name      : Close none exist file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testCloseNotExistFile, LEVEL1)
{
    int fd = 1073;
    int ret = UtilsFileClose(fd);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_200 
 * @tc.name      : Creat file with invalid long file name
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testCreatInvalidlongNameFile, LEVEL1)
{
    char* fileName = "copyLongFileName403-Abcdefg123456789Abcdefg123456789Abcdefg123456789\
                    Abcdefg123456789Abcdefg123456789";
    int fd = UtilsFileOpen(fileName, O_RDONLY_FS | O_CREAT_FS, 0);
    TEST_ASSERT_EQUAL_INT(-1, fd);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_300 
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek001, LEVEL1)
{
    char* fileName = "testfile201";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_300 
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek002, LEVEL1)
{
    char* fileName = "testfile202";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_20, SEEK_CUR_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_300 
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek003, LEVEL1)
{
    char* fileName = "testfile203";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_MINUS_20, SEEK_END_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_400
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek004, LEVEL1)
{
    char* fileName = "testfile204";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_50, SEEK_SET_FS);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_400
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek005, LEVEL1)
{
    char* fileName = "testfile205";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_50, SEEK_CUR_FS);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_400
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek006, LEVEL1)
{
    char* fileName = "testfile206";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_MINUS_50, SEEK_END_FS);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_300
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek007, LEVEL1)
{
    char* fileName = "testfile207";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_10, SEEK_CUR_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_300
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek008, LEVEL1)
{
    char* fileName = "testfile208";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_MINUS_10, SEEK_CUR_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_400
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek009, LEVEL1)
{
    char* fileName = "testfile209";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_50, SEEK_CUR_FS);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_400
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek010, LEVEL1)
{
    char* fileName = "testfile210";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_MINUS_50, SEEK_CUR_FS);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_300
 * @tc.name      : File operation for fileseek
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeek011, LEVEL1)
{
    char* fileName = "testfile211";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_MINUS_50, SEEK_CUR_FS);
    ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_MINUS_10, SEEK_CUR_FS);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_400
 * @tc.name      : File seek for none exist file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileSeekForNotExistFile, LEVEL1)
{
    int fd = 1073;
    int ret = UtilsFileSeek(fd, FILE_SEEK_OFFSET_20, SEEK_SET_FS);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_500
 * @tc.name      : Obtaining file size
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testObtainFileSize, LEVEL1)
{
    char* fileName = "testfile301";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    unsigned int fileLen = 0;
    int ret = UtilsFileStat(fileName, &fileLen);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_600
 * @tc.name      : Obtaining size for none exist file 
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testObtainSizeForNotExistFile, LEVEL1)
{
    char* fileName = "fileNotExist302";
    unsigned int fileLen = 0;
    int ret = UtilsFileStat(fileName, &fileLen);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_500
 * @tc.name      : File operation for file read
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileRead, LEVEL1)
{
    char* fileName = "testfile303";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    char buf[LENGTH_OF_READ_BUF] = {0};
    int fd = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    int ret = UtilsFileRead(fd, buf, LENGTH_OF_READ_BUF);
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, ret);
    UtilsFileClose(fd);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_600
 * @tc.name      : Read none exist file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testReadNotExistFile, LEVEL1)
{
    char buf[LENGTH_OF_READ_BUF] = {0};
    int fd = 1073;
    int ret = UtilsFileRead(fd, buf, LENGTH_OF_READ_BUF);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_500
 * @tc.name      : Obtaining size for file with long file name
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testObtainLongNameFileSize, LEVEL1)
{
    char* fileName = "testLongFileName305-Ab123456789";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    unsigned int fileLen = 0;
    int ret = UtilsFileStat(fileName, &fileLen);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_500
 * @tc.name      : Obtaining size for file with special characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testObtainSizeForFileWithSpecChar, LEVEL1)
{
    char* fileName = "case307-~!@#$%^&*()+_/:?<;>|\\";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    unsigned int fileLen = 0;
    int ret = UtilsFileStat(fileName, &fileLen);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_700
 * @tc.name      : File operation for file copy
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileCopy, LEVEL1)
{
    char* fileName = "testfile401";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    char* fileNameCopy = "copyFile401";
    int ret = UtilsFileCopy(fileName, fileNameCopy);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
    UtilsFileDelete(fileNameCopy);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_800
 * @tc.name      : Copy none exist file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testCopyNotExistFile, LEVEL1)
{
    char* fileName = "fileNotExist402";
    char* fileNameCopy = "copyFile402";
    int ret = UtilsFileCopy(fileName, fileNameCopy);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_700
 * @tc.name      : Copy file with long file name
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testCopyLongNameFile, LEVEL1)
{
    char* fileName = "testLongFileName403-Ab123456789";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    char* fileNameCopy = "copyLongFileName403-Ab123456789";
    int ret = UtilsFileCopy(fileName, fileNameCopy);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
    UtilsFileDelete(fileNameCopy);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_700
 * @tc.name      : Copy file with special characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testCopyFileWithSpecChar, LEVEL1)
{
    char* fileName = "case404-~!@#$%^&*()+_/:?<;>|\\";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    char* fileNameCopy = "copy404-~!@#$%^&*()+_/:?<;>|\\";
    int ret = UtilsFileCopy(fileName, fileNameCopy);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileName);
    UtilsFileDelete(fileNameCopy);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_900
 * @tc.name      : File operation for file move
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileMove, LEVEL1)
{
    char* fileName = "testfile501";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    char* fileNameMove = "moveFile501";
    int ret = UtilsFileMove(fileName, fileNameMove);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileNameMove);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1000 
 * @tc.name      : Move none exist file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testMoveNotExistFile, LEVEL1)
{
    char* fileName = "fileNotExist502";
    char* fileNameMove = "moveFile502";
    int ret = UtilsFileMove(fileName, fileNameMove);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_900
 * @tc.name      : Move file with long file name
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testMoveLongNameFile, LEVEL1)
{
    char* fileName = "testLongFileName503-Ab123456789";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    char* fileNameMove = "moveLongFileName503-Ab123456789";
    int ret = UtilsFileMove(fileName, fileNameMove);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileNameMove);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_900
 * @tc.name      : Move file with special characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testMoveFileWithSpecChar, LEVEL1)
{
    char* fileName = "case504-~!@#$%^&*()+_/:?<;>|\\";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    char* fileNameMove = "move504-~!@#$%^&*()+_/:?<;>|\\";
    int ret = UtilsFileMove(fileName, fileNameMove);
    TEST_ASSERT_EQUAL_INT(0, ret);
    UtilsFileDelete(fileNameMove);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1100
 * @tc.name      : File operation for file delete
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testFileDelete, LEVEL1)
{
    char* fileName = "deleteFile601";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int ret = UtilsFileDelete(fileName);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1200
 * @tc.name      : Delete none exist file
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testDeleteNotExistFile, LEVEL1)
{
    char* fileName = "fileNotExist602";
    int ret = UtilsFileDelete(fileName);
    TEST_ASSERT_EQUAL_INT(-1, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1100
 * @tc.name      : Delete file with long file name
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testDeleteLongNameFile, LEVEL1)
{
    char* fileName = "deleteLongFileName603-Ab1234567";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int ret = UtilsFileDelete(fileName);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

/**
 * @tc.number    : SUB_UTILS_FILE_OPERATION_1100
 * @tc.name      : Delete file with special characters
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 1
 */
LITE_TEST_CASE(UtilsFileFuncTestSuite, testDeleteFileWithSpecChar, LEVEL1)
{
    char* fileName = "delete604-~!@#$%^&*()+_/:?<;>|\\";
    int fd0 = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS, 0);
    UtilsFileWrite(fd0, g_def, strlen(g_def));
    UtilsFileClose(fd0);
    int ret = UtilsFileDelete(fileName);
    TEST_ASSERT_EQUAL_INT(0, ret);
};

RUN_TEST_SUITE(UtilsFileFuncTestSuite);
