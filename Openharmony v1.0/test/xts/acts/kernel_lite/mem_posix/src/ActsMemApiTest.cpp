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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <malloc.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "gtest/gtest.h"
#include "XtsActsUtil.h"
#include "XtsActsMemApiExpect.h"

using namespace testing::ext;

class ActsMemApiTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
    }
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void)
    {
    }
    // Testcase setup
    virtual void SetUp()
    {
        errno = 0;
    }
    // Testcase teardown
    virtual void TearDown()
    {
    }
};

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_BCMP_0100
* @tc.name       test bcmp api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemBcmp_0100, TestSize.Level1) {
    char str1[] = "this is string1";
    char str2[] = "this is string2";
    int returnVal;

    returnVal = bcmp(str1, str2, 7);
    LogPrint("    bcmp *s1:='%s' *s2:='%s' size:='7',   --> returnVal:='%d'\n", str1, str2, returnVal);
    EXPECT_EQ(0, returnVal)
        << "ErrInfo: bcmp *s1:='" << str1 << "' *s2:='" << str2
        << "' size:='7',   --> returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_BCMP_1000
* @tc.name       test bcmp api NE
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemBcmp_1000, TestSize.Level1) {
    char str1[] = "this is string1";
    char str2[] = "this is string2";
    int returnVal;
    
    returnVal = bcmp(str1, str2, 15);
    LogPrint("    bcmp *s1:='%s' *s2:='%s' size:='15',   --> returnVal:='%d'\n", str1, str2, returnVal);
    EXPECT_NE(0, returnVal)
        << "ErrInfo: bcmp *s1:='" << str1 << "' *s2:='" << str2
        << "' size:='15',   --> returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_BCOPY_0100
* @tc.name       test bcopy api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemBcopy_0100, TestSize.Level1) {
    char srcStr[] = "this";
    char destStr[] = "00000000";
    int iRtn = 1;

    LogPrint("    bcopy *src:='%s' *dest:='%s', size:='4', \n", srcStr, destStr);
    bcopy(srcStr, destStr, 4);
    LogPrint("    --> *dest:='%s'\n", destStr);
	
    for (int iLoop = 0; iLoop < 4; iLoop++)
    {
        if (srcStr[iLoop] != destStr[iLoop]) {
            iRtn = 0;
            break;
        }
    }

    EXPECT_EQ(1, iRtn)
        << "ErrInfo: bcopy *src:='" << srcStr << "' *dest:='"
        << "' size:='4',   --> *dest:='" << destStr << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_BZERO_0100
* @tc.name       test bzero api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemBzero_0100, TestSize.Level1) {
    char srcStr[] = "this is string1";
    char destStr[] = "this is string1";
    int iFlag = 1;
	
    LogPrint("    bzero *s:='%s' size:='4',   ", srcStr);
    bzero(destStr, 4);
    LogPrint("--> afterrun s:='%s', ", destStr);
	
    for(int iLoop = 0; iLoop < 4; iLoop++)
    {
        if (destStr[iLoop] != '\0') {
            iFlag = 0;
            break;
        } else {
            destStr[iLoop] = '0';
        }
    }
    LogPrint("  for_print s:='%s'\n", destStr);

    EXPECT_EQ(1, iFlag)
        << "ErrInfo: bzero *:='" << srcStr << "' size:='4',   --> afterrun s:='" << destStr << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MALLOC_USABLE_SIZE_0100
* @tc.name       test malloc_usable_size api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMallocUsableSize_0100, TestSize.Level1) {
    char *pt = nullptr;
    size_t size;
	
    pt = (char *)malloc(128);
    if (pt) {
        LogPrint("    Mem allocated at: %x\n", pt);
    } else {
        LogPrint("    No enough Mem!\n");
    }
	
    size = malloc_usable_size(pt);
    LogPrint("    malloc_usable_size *ptr:='%x',   --> return size:='%d'\n", pt, size);

    EXPECT_GT(size, 1)
        << "ErrInfo: malloc_usable_size *ptr:='" << pt << "',   --> return size:='" << size << "'";
    free(pt);
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MALLOC_USABLE_SIZE_1000
* @tc.name       test malloc_usable_size api exception null
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMallocUsableSize_1000, TestSize.Level1) {
    char *pt = nullptr;
    size_t size;
	
    size = malloc_usable_size(NULL);
    LogPrint("    malloc_usable_size *ptr:='NULL',   --> return size:='%d'\n", size);

    EXPECT_EQ(size, 0)
        << "ErrInfo: malloc_usable_size *ptr:='NULL',   --> return size:='" << size << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MEMCCPY_0100
* @tc.name       test memccpy api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemCcpy_0100, TestSize.Level1) {
    char srcStr[] = "this is str1:stop here";
    char destStr[] = "000000000000000000000000";
    char *pt = nullptr;

    LogPrint("    bcopy *dest:='%s' *src:='%s' c:=':' size:='18', \n", destStr, srcStr);
    pt = (char *)memccpy(destStr, srcStr, ':', 18);
    LogPrint("    --> return pt:='%x', dest:='%s'\n", pt, destStr);
    ASSERT_TRUE(pt)
        << "ErrInfo: bcopy *dest:='destStr' *src:='"
        << srcStr << "' c:=':' size:='18',   --> afterrun dest:='" << destStr << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MEMCCPY_0200
* @tc.name       test memccpy api not find c
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemCcpy_0200, TestSize.Level1) {
    char srcStr[] = "this is str1:stop here";
    char destStr[] = "000000000000000000000000";
    char *pt = nullptr;

    LogPrint("    bcopy *dest:='%s' *src:='%s' c:=';' size:='18', \n", destStr, srcStr);
    pt = (char *)memccpy(destStr, srcStr, ';', 18);
    LogPrint("    --> return pt:='%x', *dest:='%s'\n", pt, destStr);
    ASSERT_FALSE(pt)
        << "ErrInfo: bcopy *dest:='destStr' *src:='"
        << srcStr << "' c:=':' size:='18',   --> return pt:='" << pt << "', dest:='" << destStr << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MEMPCPY_0100
* @tc.name       test mempcpy api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMempcpy_0100, TestSize.Level1) {
    char srcStr[] = "this is str1";
    char destStr[] = "00000000000000000000";
    size_t size;
    char *pt = nullptr;

    LogPrint("    mempcpy *dest:='%s' *src:='%s' size:='16',", destStr, srcStr);
    pt = (char *)mempcpy(destStr, srcStr, 16);
    LogPrint("    --> return pt:='%x', *dest:='%s'\n", pt, destStr);
    ASSERT_TRUE(pt)
        << "ErrInfo: mempcpy *dest:='destStr' *src:='"
        << srcStr << "' size:='16',   --> return pt:='" << pt << "', dest:='" << destStr << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MEMCHR_0100
* @tc.name       test memchr api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemchr_0100, TestSize.Level1) {
    char srcStr[] = "this is str a;";
    char *pos = nullptr;

    LogPrint("    memchr *s:='%s' c:='a' size:='14',", srcStr);
    pos = (char *)memchr(srcStr, 'a', 14);
    LogPrint("    --> return pos:='%x'\n", pos);
	
    ASSERT_TRUE(pos)
        << "ErrInfo: memchr *s:='" << srcStr << "' c:='a' size:='14',"
        << "   --> return pos:='" << pos << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MEMCHR_1000
* @tc.name       test memchr api para len not enough
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemchr_1000, TestSize.Level1) {
    char srcStr[] = "this is str a;";
    char *pos = nullptr;

    LogPrint("    memchr *s:='%s' c:='a' size:='4',", srcStr);
    pos = (char *)memchr(srcStr, 'a', 4);
    LogPrint("    --> return pos:='%x'\n", pos);
    ASSERT_FALSE(pos)
        << "ErrInfo: memchr *s:='" << srcStr << "' c:='a' size:='4',"
        << "   --> return pos:='" << pos << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MEMCHR_1100
* @tc.name       test memchr api para c not found
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemchr_1100, TestSize.Level1) {
    char srcStr[] = "this is str a;";
    char *pos = nullptr;

    LogPrint("    memchr *s:='%s' c:='b' size:='14',", srcStr);
    pos = (char *)memchr(srcStr, 'b', 14);
    LogPrint("    --> return pos:='%x'\n", pos);
    ASSERT_FALSE(pos)
        << "ErrInfo: memchr *s:='" << srcStr << "' c:='b' size:='14',"
        << "   --> return pos:='" << pos << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MEMMEM_0100
* @tc.name       test memmem api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemmem_0100, TestSize.Level1) {
    char srcStr[] = "this is str a;";
    char srcSubStr[] = "str";
    char *pos = nullptr;

    LogPrint("    memmem *haystack:='%s' size_haystack:='%d' ", srcStr, strlen(srcStr));
    LogPrint("*needle:='%s' size_needle:='%d',\n", srcSubStr, strlen(srcSubStr));
    pos = (char *)memmem(srcStr, strlen(srcStr), srcSubStr, strlen(srcSubStr));
    LogPrint("    --> return pos:='%x'\n", pos);
	
    ASSERT_TRUE(pos)
        << "ErrInfo: memmem *haystack:='" << srcStr << " size_haystack:='"
        << strlen(srcStr) << "' *needle:='" << srcSubStr << "' size_needle:='" << strlen(srcSubStr)
        << "   --> return pos:='" << pos << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_MEMMEM_1000
* @tc.name       test memmem api para not found
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemmem_1000, TestSize.Level1) {
    char srcStr[] = "this is str a;";
    char srcSubStr[] = "strb";
    char *pos = nullptr;

    pos = (char *)memmem(srcStr, strlen(srcStr), srcSubStr, strlen(srcSubStr));
    LogPrint("    memmem *haystack:='%s' size_haystack:='%d' ", srcStr, strlen(srcStr));
    LogPrint("*needle:='%s' size_needle:='%d',\n", srcSubStr, strlen(srcSubStr));
    LogPrint("    --> return pos:='%x'\n", pos);
	
    ASSERT_FALSE(pos)
        << "ErrInfo: memmem *haystack:='" << srcStr << " size_haystack:='"
        << strlen(srcStr) << "' *needle:='" << srcSubStr << "' size_needle:='" << strlen(srcSubStr)
        << "   --> return pos:='" << pos << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_OPEN_MEMSTREAM_0100
* @tc.name       test open_memstream api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testOpenMemStream_0100, TestSize.Level1) {
    FILE *memStream;
    char *ptr = nullptr;
    size_t sizeLoc;
	
    memStream = open_memstream(&ptr, &sizeLoc);
    LogPrint("    open_memstream **ptr:='*ptr' *sizeloc:='*sizeLoc', ");
    LogPrint("    --> return memStream:='%x'\n", memStream);
    LogPrint("    ptr:='%x', sizeLoc:='%d'\n", ptr, sizeLoc);
	
    ASSERT_TRUE(memStream)
        << "ErrInfo: open_memstream **ptr:='*ptr' *sizeloc:='*sizeLoc', "
        << "   --> return memStream:='" << memStream << "'";

    LogPrint("    fprintf(memStream, 'Hello!');\n");
    fprintf(memStream, "Hello!");
    fflush(memStream);
    LogPrint("    ptr:='%s', sizeloc:='%zu'\n", ptr, sizeLoc);

    LogPrint("    fclose(memStream);\n");
    fclose(memStream);
    LogPrint("    ptr:='%s', sizeloc:='%zu'\n", ptr, sizeLoc);
    free(ptr);
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_MEM_GETPAGESIZE_0100
* @tc.name       test getpagesize api
* @tc.desc       [C- SOFTWARE -0200]
*/
HWTEST_F(ActsMemApiTest, testMemGetpagesize_0100, TestSize.Level1) {
    int returnVal;

    returnVal = getpagesize();
    LogPrint("    getpagesize,   --> returnVal:='%d'\n", returnVal);
    EXPECT_GE(returnVal, 0);
    EXPECT_EQ(returnVal, XTS_ACTS_MEM_API_EXPECT_PAGESIZE)
        << "ErrInfo: getpagesize,   --> returnVal:='" << returnVal << "'";
}
