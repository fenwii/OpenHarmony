/*
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GTEST_INCLUDE_GTEST_GTEST_EXT_H_
#define GTEST_INCLUDE_GTEST_GTEST_EXT_H_

#include <vector>
#include "gtest/gtest.h"

namespace testing {
  namespace ext {

    // helper macro to create unique variable name
    #define GTEST_TEST_UNIQUE_ID_(test_case_name, test_name, file_line) \
    test_case_name##_##test_name##_##file_line

    // 1. define a extended TEST supporting test flags registing
    #if !GTEST_DONT_DEFINE_TEST
    # define HWTEST(test_case_name, test_name, test_flags) \
    bool GTEST_TEST_UNIQUE_ID_(test_case_name, test_name, __LINE__) = testing::ext::TestDefManager::instance()->regist(#test_case_name, #test_name, test_flags, testing::ext::Plain);\
    TEST(test_case_name, test_name)
    #endif

    // 2. define a extended TEST_F supporting test flags registing
    # define HWTEST_F(test_case_name, test_name, test_flags) \
    bool GTEST_TEST_UNIQUE_ID_(test_case_name, test_name, __LINE__) = testing::ext::TestDefManager::instance()->regist(#test_case_name, #test_name, test_flags, testing::ext::Fixtured);\
    TEST_F(test_case_name, test_name)

    // 3. define a extended TYPED_TEST supporting test flags registing
    # define HWTYPED_TEST(test_case_name, test_name, test_flags) \
    bool GTEST_TEST_UNIQUE_ID_(test_case_name, test_name, __LINE__) = testing::ext::TestDefManager::instance()->regist(#test_case_name, #test_name, test_flags, testing::ext::Typed);\
    TYPED_TEST(test_case_name, test_name)

    // 4. define a extended TYPED_TEST_P supporting test flags registing
    # define HWTYPED_TEST_P(test_case_name, test_name, test_flags) \
    bool GTEST_TEST_UNIQUE_ID_(test_case_name, test_name, __LINE__) = testing::ext::TestDefManager::instance()->regist(#test_case_name, #test_name, test_flags, testing::ext::PatternTyped);\
    TYPED_TEST_P(test_case_name, test_name)

    // 5. define a extended TEST_P supporting test flags registing
    # define HWTEST_P(test_case_name, test_name, test_flags) \
    bool GTEST_TEST_UNIQUE_ID_(test_case_name, test_name, __LINE__) = testing::ext::TestDefManager::instance()->regist(#test_case_name, #test_name, test_flags, testing::ext::Parameterized);\
    TEST_P(test_case_name, test_name)

    // test definition types
    enum TestDefType {
        Plain, Fixtured, Typed, PatternTyped, Parameterized
    };
    // case_name/test_name matchNaming pattern
    enum NamingMatchType {
        AEqualsB, AStartsWithB, AContainsB, AEndsWithB
    };

    // information of a test difinition
    class TestDefInfo {
    public:
        friend class TestDefManager;
    private:
        const static  char kNamingSepchar = '/';
        const char* const test_case_name;
        const char* const name;
        const int flags;
        const TestDefType def_type;
        TestDefInfo(const char* tcn, const char* n, int fs, TestDefType tdf);
    };

    class TestDefManager {
    private:
        TestDefManager() {};
        std::vector<const TestDefInfo*> testDefInfos;
        const TestDefInfo* findDefFor(const TestInfo* test) const;
        bool matchNaming(const char* const a, const char* const b, NamingMatchType mt) const;
    public:
        static TestDefManager* instance();
        static const TestDefManager* cinstance();
        bool regist(const char* test_case_name, const char* test_name, int test_flags, TestDefType tdf);
        int queryFlagsFor(const TestInfo* test, int def_value) const;
        int getLevel(const std::string testcasename, const std::string testname) const;
    };

  } // namespace ext
} // namespace testing

#endif  // GTEST_INCLUDE_GTEST_GTEST_EXT_H_