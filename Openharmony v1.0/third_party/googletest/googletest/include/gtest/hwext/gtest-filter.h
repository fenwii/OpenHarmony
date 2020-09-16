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

#ifndef GTEST_INCLUDE_GTEST_GTEST_FILTER_H_
#define GTEST_INCLUDE_GTEST_GTEST_FILTER_H_

#include <string>
#include <map>
#include <vector>

namespace testing {
  namespace ext {

    using ::std::string;
    using ::std::map;
    using ::std::vector;

    class TestFilter {
    public:
        map<const char*, string*>& getAllFilterFlagsKv();
        void printHelp() const;
        bool postParsingArguments();
        bool accept(int flags) const;
        void reset();
        static TestFilter* instance();

    private:
        TestFilter() {};
        static const char* const kStrictFilter;
        int requiredFlags;
        // strcit filter requires the entirely same test flags and require no
        bool strictMode;
        bool flag_kvs_inited; // teels iff the filter kvs has been parsed
        bool ready; // teels iff the filter are ready to be used
        map<const char*, string*> filterFlagsKv;
        vector<int> vecTestLevel;
    };

  } // namespace ext
} // namespace testing

#endif  // GTEST_INCLUDE_GTEST_GTEST_FILTER_H_

