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

#include <wctype.h>

#include "gtest/gtest.h"
#include "log.h"
#include "utils.h"

using namespace testing::ext;

class ActsUtilWideCheckApiTest : public testing::Test {
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
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALNUM_0100
* @tc.name       test iswalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalnum0100, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = '2';
    returnVal = iswalnum(paraVal);
    LOGD("    iswalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALNUM_0200
* @tc.name       test iswalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalnum0200, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = 'Z';
    returnVal = iswalnum(paraVal);
    LOGD("    iswalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALNUM_0300
* @tc.name       test iswalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalnum0300, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = 'z';
    returnVal = iswalnum(paraVal);
    LOGD("    iswalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALNUM_0400
* @tc.name       test iswalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalnum0400, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = iswalnum(paraVal);
    LOGD("    iswalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALNUM_0500
* @tc.name       test iswalnum api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalnum0500, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = '\n';
    returnVal = iswalnum(paraVal);
    LOGD("    iswalnum returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswalnum returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALPHA_1100
* @tc.name       test iswalpha api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalpha1100, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = 'z';
    returnVal = iswalpha(paraVal);
    LOGD("    iswalpha returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswalpha returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALPHA_1200
* @tc.name       test iswalpha api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalpha1200, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = 'Z';
    returnVal = iswalpha(paraVal);
    LOGD("    iswalpha returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswalpha returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALPHA_1300
* @tc.name       test iswalpha api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalpha1300, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = iswalpha(paraVal);
    LOGD("    iswalpha returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswalpha returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWALPHA_1400
* @tc.name       test iswalpha api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswalpha1400, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = '\n';
    returnVal = iswalpha(paraVal);
    LOGD("    iswalpha returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswalpha returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWBLANK_1900
* @tc.name       test iswblank api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswblank1900, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = ' ';
    returnVal = iswblank(paraVal);
    LOGD("    iswblank returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswblank returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWBLANK_2000
* @tc.name       test iswblank api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswblank2000, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = 'A';
    returnVal = iswblank(paraVal);
    LOGD("    iswblank returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswblank returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWCNTRL_2400
* @tc.name       test iswcntrl api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswcntrl2400, TestSize.Level1) {
    wint_t paraVal;
    int returnVal;

    paraVal = 'A';
    returnVal = iswcntrl(paraVal);
    LOGD("    iswcntrl returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswcntrl returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWCTYPE_2700
* @tc.name       test iswctype api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswctype2700, TestSize.Level1) {
    wint_t wideChar;
    wctype_t paraDesc;
    int returnVal;

    wideChar = 'A';
    paraDesc = wctype("alnum");
    returnVal = iswctype(wideChar, paraDesc);
    LOGD("    iswctype returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswctype returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWCTYPE_2800
* @tc.name       test iswctype api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswctype2800, TestSize.Level1) {
    wint_t wideChar;
    wctype_t paraDesc;
    int returnVal;

    wideChar = '3';
    paraDesc = wctype("alnum");
    returnVal = iswctype(wideChar, paraDesc);
    LOGD("    iswctype returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswctype returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWDIGIT_3100
* @tc.name       test iswdigit api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswdigit3100, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = '3';
    returnVal = iswdigit(wideChar);
    LOGD("    iswdigit returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswdigit returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWDIGIT_3200
* @tc.name       test iswdigit api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswdigit3200, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = 'A';
    returnVal = iswdigit(wideChar);
    LOGD("    iswdigit returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswdigit returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWGRAPH_3500
* @tc.name       test iswgraph api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswgraph3500, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = 'A';
    returnVal = iswgraph(wideChar);
    LOGD("    iswgraph returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswgraph returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWGRAPH_3600
* @tc.name       test iswgraph api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswgraph3600, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = '\n';
    returnVal = iswgraph(wideChar);
    LOGD("    iswgraph returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswgraph returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWLOWER_3900
* @tc.name       test iswlower api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswlower3900, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = 'A';
    returnVal = iswlower(wideChar);
    LOGD("    iswlower c:='%c',   returnVal:='%c'\n", wideChar, returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswlower c:='" << wideChar << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWLOWER_4000
* @tc.name       test islower api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswlower4000, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = 'a';
    returnVal = iswlower(wideChar);
    LOGD("    iswlower c:='%c',   returnVal:='%c'\n", wideChar, returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswlower c:='" << wideChar << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWLOWER_4100
* @tc.name       test islower api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswlower4100, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = '5';
    returnVal = iswlower(wideChar);
    LOGD("    iswlower c:='%c',   returnVal:='%c'\n", wideChar, returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswlower c:='" << wideChar << "',   returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWPRINT_4500
* @tc.name       test iswprint api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswprint4500, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = 'a';
    returnVal = iswprint(wideChar);
    LOGD("    iswprint returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(returnVal != 0) << "ErrInfo: iswprint  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWPRINT_4600
* @tc.name       test iswprint api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswprint4600, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = '\n';
    returnVal = iswprint(wideChar);
    LOGD("    iswprint returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswprint  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWPUNCT_4900
* @tc.name       test iswpunct api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswpunct4900, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = ' ';
    returnVal = iswpunct(wideChar);
    LOGD("    iswpunct returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswpunct  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWPUNCT_5000
* @tc.name       test iswpunct api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswpunct5000, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = 'A';
    returnVal = iswpunct(wideChar);
    LOGD("    iswpunct returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswpunct  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWPUNCT_5100
* @tc.name       test iswpunct api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswpunct5100, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = '3';
    returnVal = iswpunct(wideChar);
    LOGD("    iswpunct returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswpunct  returnVal:='" << returnVal << "'";
}

/**
* @tc.number     SUB_KERNEL_UTIL_WIDECHECK_ISWPUNCT_5200
* @tc.name       test iswpunct api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsUtilWideCheckApiTest, testIswpunct5200, TestSize.Level1) {
    wint_t wideChar;
    int returnVal;

    wideChar = '\n';
    returnVal = iswpunct(wideChar);
    LOGD("    iswpunct returnVal:='%d'\n", returnVal);
    ASSERT_TRUE(0 == returnVal) << "ErrInfo: iswpunct  returnVal:='" << returnVal << "'";
}
