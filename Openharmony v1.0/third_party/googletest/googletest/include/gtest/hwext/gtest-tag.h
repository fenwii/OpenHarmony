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

#ifndef GTEST_INCLUDE_GTEST_GTEST_TAG_H_
#define GTEST_INCLUDE_GTEST_GTEST_TAG_H_

#include <string.h>
#include <map>
#include <vector>

namespace testing {
  namespace ext {

    using ::std::string;
    using ::std::map;
    using ::std::pair;
    using ::std::vector;

    // base class of tag flag::bitwise integers
    class TestFlag {
    public:
        static const int None = 0;
    private:
        const char* const name;
        const char* const desc;
        const int mask;
        map<int, const char*> elementMap;
        int eleCount;
    protected:
        TestFlag(const char*  n, const char* d, int m);
        void element(const char* desc, int hex);
    public:
        bool verify(const int hex, char* err) const;
        const char* naming() const { return name; }
        const char* description() const { return desc; }
        bool eleForName(const char* name, int& result) const;
        void printHelp(const char** indents) const;
    };

    // test size scope
    class  TestSizeSet : public TestFlag {
    public:
        TestSizeSet();
        static const int Level0 = 1  << 24;
        static const int Level1 = 2  << 24;
        static const int Level2 = 4  << 24;
        static const int Level3 = 8  << 24;
        static const int Level4 = 16 << 24;
    };

    extern const TestSizeSet TestSize;

    // get each instance of all the TestFlag implementions
    const vector<const TestFlag*>& allHextTagSets();
    // verify the test flagset, returns false if the flagset is illegal
    bool checkFlagsLegality(int flags);
    // convert name string to test flag value
    bool flagForName(const char* set_name, const char* ele_name, int& result);

  } // namespace ext
} // namespace testing

#endif  // GTEST_INCLUDE_GTEST_GTEST_TAG_H_
