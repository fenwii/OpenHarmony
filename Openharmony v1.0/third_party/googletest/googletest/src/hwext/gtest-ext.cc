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

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string>
#include "gtest/hwext/gtest-ext.h"


namespace testing {
  namespace ext {
    #define GTEST_EXT_DEBUG 0

    TestDefManager* TestDefManager::instance() {
        static TestDefManager* instance_ = NULL;
        if (instance_ == NULL) {
            instance_ = new TestDefManager();
        }
        return instance_;
    }

    const TestDefManager* TestDefManager::cinstance() {
        return instance();
    }

    // c'tor, all members immutable
    TestDefInfo::TestDefInfo(const char* tcn, const char* n, int fs, TestDefType tdf) :\
        test_case_name(tcn), name(n), flags(fs), def_type(tdf) {};

    bool TestDefManager::regist(const char* test_case_name, const char* test_name, int test_flags, TestDefType tdf) {
        TestDefManager::testDefInfos.push_back(new TestDefInfo(test_case_name, test_name, test_flags, tdf));
        return true;
    }

    int TestDefManager::queryFlagsFor(const TestInfo* test, int def_value) const {
        const TestDefInfo* def = findDefFor(test);
        return def == NULL ? def_value : def->flags;
    }

    const TestDefInfo* TestDefManager::findDefFor(const TestInfo* test) const {
        // search by matching test definition information
        NamingMatchType case_name_mt = AEqualsB;
        NamingMatchType test_name_mt = AEqualsB;

        for (unsigned int i = 0; i < testDefInfos.size(); i++)
        {
            const TestDefInfo* info = testDefInfos.at(i);
            switch (info->def_type) {
            case Plain:
            case Fixtured:
                case_name_mt = AEqualsB;
                test_name_mt = AEqualsB;
                break;
            case Typed:
                case_name_mt = AStartsWithB;
                test_name_mt = AEqualsB;
                break;
            case PatternTyped:
                case_name_mt = AContainsB;
                test_name_mt = AEqualsB;
                break;
            case Parameterized:
                case_name_mt = AEndsWithB;
                test_name_mt = AStartsWithB;
                break;
            }

            const bool matched = matchNaming(test->test_case_name(), info->test_case_name, case_name_mt) && matchNaming(test->name(), info->name, test_name_mt);
            if (matched) {
                return info;
            }
        }

        #if GTEST_EXT_DEBUG
        printf("cannot find test definition for: %s.%s\n", test->test_case_name(), test->name());
        #endif
        return NULL;
    }

    bool TestDefManager::matchNaming(const char* const a, const char* const b, NamingMatchType mt) const {
        const char sep = TestDefInfo::kNamingSepchar;
        const int len_a = strlen(a);
        const int len_b = strlen(b);
        int i;
        switch (mt) {
        case AEqualsB:
            // a=b
            return strcmp(a, b) == 0;
        case AStartsWithB:
            // a=b/xxx
            return strstr(a, b) == a && a[len_b] == sep;
        case AContainsB:
            // a=xxx/b/yyy
            for (i = 1; i < len_a - len_b; i++) {
                if (a[i - 1] == sep&&a[i + len_b] == sep&&strstr(a + i, b) == a + i) {
                    return true;
                }
            }
            return false;
        case AEndsWithB:
            // a=xxx/b
            return len_a > len_b&&a[len_a - len_b - 1] == sep&&strcmp(a + len_a - len_b, b) == 0;
        default:
            fprintf(stderr, "Illegal NamingMatchType: %d", mt);
            return false;
        }
    }

    int TestDefManager::getLevel(const std::string testcasename, const std::string testname) const {
      NamingMatchType case_name_mt = AEqualsB;
      NamingMatchType test_name_mt = AEqualsB;

      for (unsigned int i = 0; i < testDefInfos.size(); i++)
      {
          const TestDefInfo* info = testDefInfos.at(i);
          switch (info->def_type) {
          case Plain:
          case Fixtured:
              case_name_mt = AEqualsB;
              test_name_mt = AEqualsB;
              break;
          case Typed:
              case_name_mt = AStartsWithB;
              test_name_mt = AEqualsB;
              break;
          case PatternTyped:
              case_name_mt = AContainsB;
              test_name_mt = AEqualsB;
              break;
          case Parameterized:
              case_name_mt = AEndsWithB;
              test_name_mt = AStartsWithB;
              break;
          }

          const bool matched = matchNaming(testcasename.c_str(), info->test_case_name, case_name_mt) && matchNaming(testname.c_str(), info->name, test_name_mt);
          if (matched) {
              int level = (info->flags >> 24);
              if (level == 1) return 0;
              if (level == 2) return 1;
              if (level == 4) return 2;
              if (level == 8) return 3;
              if (level == 16) return 4;
          }
      }
      return -1;
  }

  } //namespace ext
} //namespace testing
