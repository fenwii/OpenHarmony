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

#include <ctype.h>
#include <math.h>
#include <stropts.h>

#include "gtest/gtest.h"
#include "log.h"
#include "utils.h"

using namespace testing::ext;

class ActsUtilCheckApiTest : public testing::Test {
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
    }
    // Testcase teardown
    virtual void TearDown()
    {
    }
};

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALNUM_0100
* @tc.name       test isalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalnum0100, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = '2';
    returnVal = isalnum(paraVal);
    LOGD("    isalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALNUM_0200
* @tc.name       test isalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalnum0200, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'z';
    returnVal = isalnum(paraVal);
    LOGD("    isalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALNUM_0300
* @tc.name       test isalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalnum0300, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'Z';
    returnVal = isalnum(paraVal);
    LOGD("    isalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALNUM_0400
* @tc.name       test isalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalnum0400, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = isalnum(paraVal);
    LOGD("    isalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALNUM_0500
* @tc.name       test isalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalnum0500, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = '\n';
    returnVal = isalnum(paraVal);
    LOGD("    isalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALPHA_1100
* @tc.name       test isalpha api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalpha1100, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'z';
    returnVal = isalpha(paraVal);
    LOGD("    isalpha returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isalpha returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALPHA_1200
* @tc.name       test isalpha api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalpha1200, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'Z';
    returnVal = isalpha(paraVal);
    LOGD("    isalpha returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isalpha returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALPHA_1300
* @tc.name       test isalpha api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalpha1300, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = isalpha(paraVal);
    LOGD("    isalpha returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isalpha returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISALPHA_1400
* @tc.name       test isalpha api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsalpha1400, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = '\n';
    returnVal = isalpha(paraVal);
    LOGD("    isalpha returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isalpha returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISASCII_1900
* @tc.name       test isascii api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsascii1900, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'z';
    returnVal = isascii(paraVal);
    LOGD("    isascii returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isascii returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISASCII_2000
* @tc.name       test isascii api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsascii2000, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'Z';
    returnVal = isascii(paraVal);
    LOGD("    isascii returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isascii returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISASCII_2100
* @tc.name       test isascii api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsascii2100, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = '~';
    returnVal = isascii(paraVal);
    LOGD("    isascii returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isascii returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISASCII_2200
* @tc.name       test isascii api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsascii2200, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 128;
    returnVal = isascii(paraVal);
    LOGD("    isascii returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isascii returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISASTREAM_2300
* @tc.name       test isastream api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsastream2300, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 128;
    returnVal = isastream(paraVal);
    LOGD("    isastream returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(-1 == returnVal) << "ErrInfo: isastream returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISATTY_2400
* @tc.name       test isatty api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsatty2400, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 128;
    returnVal = isatty(paraVal);
    LOGD("    isatty returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isatty returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISBLANK_2500
* @tc.name       test isblank api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsblank2500, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = isblank(paraVal);
    LOGD("    isblank returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isblank returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISBLANK_2600
* @tc.name       test isblank api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsblank2600, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'A';
    returnVal = isblank(paraVal);
    LOGD("    isblank returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isblank returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISCNTRL_2900
* @tc.name       test iscntrl api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIscntrl2900, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = '\n';
    returnVal = iscntrl(paraVal);
    LOGD("    iscntrl returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iscntrl returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISCNTRL_3000
* @tc.name       test iscntrl api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIscntrl3000, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'A';
    returnVal = iscntrl(paraVal);
    LOGD("    iscntrl returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iscntrl returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISDIGIT_3300
* @tc.name       test isdigit api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsdigit3300, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = '3';
    returnVal = isdigit(paraVal);
    LOGD("    isdigit returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isdigit returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISDIGIT_3400
* @tc.name       test isdigit api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsdigitl3400, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = 'a';
    returnVal = isdigit(paraVal);
    LOGD("    isdigit returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isdigit returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISDIGIT_3500
* @tc.name       test isdigit api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsdigitl3500, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = '\n';
    returnVal = isdigit(paraVal);
    LOGD("    isdigit returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isdigit returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISDIGIT_3600
* @tc.name       test isdigit api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsdigit3600, TestSize.Level1) {
    int paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = isdigit(paraVal);
    LOGD("    isdigit returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isdigit returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISFINITE_4100
* @tc.name       test isfinite api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsfinite4100, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = isfinite(paraVal);
    LOGD("    isfinite returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isfinite returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISFINITE_4200
* @tc.name       test isfinite api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsfinite4200, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = 3.1415926;
    returnVal = isfinite(paraVal);
    LOGD("    isfinite returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isfinite returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISFINITE_4300
* @tc.name       test isfinite api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsfinite4300, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = 1.26e3;
    returnVal = isfinite(paraVal);
    LOGD("    isfinite returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isfinite returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGRAPH_4400
* @tc.name       test isgraph api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgraph4400, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = 'A';
    returnVal = isgraph(paraVal);
    LOGD("    isgraph returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isgraph returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGRAPH_4500
* @tc.name       test isgraph api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgraph4500, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = 'z';
    returnVal = isgraph(paraVal);
    LOGD("    isgraph returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isgraph returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGRAPH_4600
* @tc.name       test isgraph api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgraph4600, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = '\n';
    returnVal = isgraph(paraVal);
    LOGD("    isgraph returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isgraph returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGRAPH_4700
* @tc.name       test isgraph api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgraph4700, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = isgraph(paraVal);
    LOGD("    isgraph returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isgraph returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGREATER_5200
* @tc.name       test isgreater api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgreater5200, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 1.1;
    paraVal2 = 2.1;
    returnVal = isgreater(paraVal1, paraVal2);
    LOGD("    isgreater returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isgreater returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGREATER_5300
* @tc.name       test isgreater api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgreater5300, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 2.1;
    paraVal2 = 1.1;
    returnVal = isgreater(paraVal1, paraVal2);
    LOGD("    isgreater returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isgreater returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGREATER_5400
* @tc.name       test isgreater api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgreater5400, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 2.1;
    paraVal2 = 2.1;
    returnVal = isgreater(paraVal1, paraVal2);
    LOGD("    isgreater returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isgreater returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGREATEREQUAL_5500
* @tc.name       test isgreaterequal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgreaterequal5500, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 1.1;
    paraVal2 = 2.1;
    returnVal = isgreaterequal(paraVal1, paraVal2);
    LOGD("    isgreaterequal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isgreaterequal returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGREATEREQUAL_5600
* @tc.name       test isgreaterequal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgreaterequal5600, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 2.1;
    paraVal2 = 1.1;
    returnVal = isgreaterequal(paraVal1, paraVal2);
    LOGD("    isgreaterequal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isgreaterequal returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISGREATEREQUAL_5700
* @tc.name       test isgreaterequal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsgreaterequal5700, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 2.1;
    paraVal2 = 2.1;
    returnVal = isgreaterequal(paraVal1, paraVal2);
    LOGD("    isgreaterequal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isgreaterequal returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISINF_5800
* @tc.name       test isinf api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsinf5800, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = INFINITY;
    returnVal = isinf(paraVal);
    LOGD("    isinf returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(1 == returnVal) << "ErrInfo: isinf  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLESSEQUAL_5900
* @tc.name       test islessequal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslessequal5900, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 1.1;
    paraVal2 = 2.1;
    returnVal = islessequal(paraVal1, paraVal2);
    LOGD("    islessequal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 != returnVal) << "ErrInfo: islessequal returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLESSEQUAL_6000
* @tc.name       test islessequal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslessequal6000, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 2.1;
    paraVal2 = 1.1;
    returnVal = islessequal(paraVal1, paraVal2);
    LOGD("    islessequal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: islessequal returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLESSEQUAL_6100
* @tc.name       test islessequal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslessequal6100, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 2.1;
    paraVal2 = 2.1;
    returnVal = islessequal(paraVal1, paraVal2);
    LOGD("    islessequal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: islessequal returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLESSGREATER_6200
* @tc.name       test islessgreater api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslessgreater6200, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 2.1;
    paraVal2 = 2.1;
    returnVal = islessgreater(paraVal1, paraVal2);
    LOGD("    islessgreater returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: islessgreater returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLESSGREATER_6300
* @tc.name       test islessgreater api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslessgreater6300, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 1.1;
    paraVal2 = 2.1;
    returnVal = islessgreater(paraVal1, paraVal2);
    LOGD("    islessgreater returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: islessgreater returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLESSGREATER_6400
* @tc.name       test islessgreater api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslessgreater6400, TestSize.Level1) {
    double paraVal1;
    double paraVal2;
    int returnVal;

    paraVal1 = 3.1;
    paraVal2 = 2.1;
    returnVal = islessgreater(paraVal1, paraVal2);
    LOGD("    islessgreater returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: islessgreater returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLOWER_6500
* @tc.name       test islower api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslower6500, TestSize.Level1) {
    char paraChar;
    int returnVal;

    paraChar = 'A';
    returnVal = islower(paraChar);
    LOGD("    islower c:='%c',   returnVal:='%c'\n", paraChar, returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: islower c:='" << paraChar << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLOWER_6600
* @tc.name       test islower api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslower6600, TestSize.Level1) {
    char paraChar;
    int returnVal;

    paraChar = 'a';
    returnVal = islower(paraChar);
    LOGD("    islower c:='%c',   returnVal:='%c'\n", paraChar, returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: islower c:='" << paraChar << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLOWER_6700
* @tc.name       test islower api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslower6700, TestSize.Level1) {
    char paraChar;
    int returnVal;

    paraChar = '5';
    returnVal = islower(paraChar);
    LOGD("    islower c:='%c',   returnVal:='%c'\n", paraChar, returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: islower c:='" << paraChar << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISLOWER_6800
* @tc.name       test islower api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIslower6800, TestSize.Level1) {
    char paraChar;
    int returnVal;

    paraChar = ' ';
    returnVal = islower(paraChar);
    LOGD("    islower c:='%c',   returnVal:='%c'\n", paraChar, returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: islower c:='" << paraChar << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISNAN_7300
* @tc.name       test isnan api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsnan7300, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = NAN;
    returnVal = isnan(paraVal);
    LOGD("    isnan returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isnan  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISNORMAL_7400
* @tc.name       test isnormal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsnormal7400, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = FP_NORMAL;
    returnVal = isnormal(paraVal);
    LOGD("    isnormal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isnormal  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISNORMAL_7500
* @tc.name       test isnormal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsnormal7500, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = NAN;
    returnVal = isnormal(paraVal);
    LOGD("    isnormal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isnormal  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISNORMAL_7600
* @tc.name       test isnormal api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsnormal7600, TestSize.Level1) {
    double paraVal;
    int returnVal;

    paraVal = 2.1;
    returnVal = isnormal(paraVal);
    LOGD("    isnormal returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isnormal  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISPRINT_7700
* @tc.name       test isprint api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsprint7700, TestSize.Level1) {
    char paraVal;
    int returnVal;

    paraVal = 'a';
    returnVal = isprint(paraVal);
    LOGD("    isprint returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isprint  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISPRINT_7800
* @tc.name       test isprint api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsprint7800, TestSize.Level1) {
    char paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = isprint(paraVal);
    LOGD("    isprint returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: isprint  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_CHECK_ISPRINT_7900
* @tc.name       test isprint api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilCheckApiTest, testIsprint7900, TestSize.Level1) {
    char paraVal;
    int returnVal;

    paraVal = '\n';
    returnVal = isprint(paraVal);
    LOGD("    isprint returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: isprint  returnVal:='" << returnVal << "'";
}
