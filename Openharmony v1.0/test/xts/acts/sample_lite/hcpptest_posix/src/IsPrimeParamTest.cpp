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

// --------------------<测试 参数化>-----------------------------------
#include "gtest/gtest.h"
#include <cmath>
#include "demo.h"
using namespace ::testing;

struct ParamList {
    bool    out;
    int     in;
};

class IsPrimeParamTest : public ::testing::TestWithParam<struct ParamList> {
};

// if n is prime num return true else return false
static bool IsPrimeNum(int n)
{
    if (n < NUM2) {
        return false;
    }
    int i;
    for (i = NUM2; i <= sqrt(n); i++) {
        if ((n % i) == 0) {
            return false;
        }
    }
    return true;
}

TEST_P(IsPrimeParamTest, IsPrime)
{
    bool out = GetParam().out;
    int in = GetParam().in;
    EXPECT_EQ(out, IsPrimeNum(in));
}

INSTANTIATE_TEST_CASE_P(IsPrimeParamTest,
    IsPrimeParamTest,
    Values(ParamList{false, NUM10}, ParamList{true, NUM3}, ParamList{false, NUM0}, ParamList{false, NG_NUM1}));
