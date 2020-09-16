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

#include <string.h>
#include <string>
#include "gtest/hwext/gtest-utils.h"

namespace testing {

    /*
     * Function:     compareStringsByIgnoreCase
     * Description:  Ignore case to compare two strings
     * Input:        one: first string
     *               two: second string
     * Output:       N/A
     * Return:       true(equal),flase(not equal)
     * Others:       N/A
     */
    bool compareStringsByIgnoreCase(const char* one, const char* two) {
        if (one == NULL && two == NULL) {
            return true;
        }

        if (one == NULL || two == NULL) {
            return false;
        }

        if (strcmp(one, two) == 0) {
            return true;
        }

        const int len_one = strlen(one);
        const int len_two = strlen(two);

        if (len_one != len_two) {
            return false;
        }

        if (len_one == 0 && len_two == 0) {
            return true;
        }

        for (int i = 0; i < len_one; i++) {
            if (tolower(one[i]) != tolower(two[i])) {
                return false;
            }
        }

        return true;
    }

    bool IsElementInVector(vector<int> vec, int element){
        vector<int>::iterator it = find(vec.begin(), vec.end(), element);
        if (it != vec.end()) {
            return true;
        }
        return false;
    }

    vector<string> SplitString(const string& str, const string& delim) {
        vector<string> result;
        if (str != "") {
            int len = str.length();
            char *src = new char[len + 1];
            memset(src, 0, len + 1);
            strcpy(src, str.c_str());
            src[len] = '\0';

            char *tokenptr = strtok(src, delim.c_str());
            while (tokenptr != NULL)
            {
                string tk = tokenptr;
                result.emplace_back(tk);
                tokenptr = strtok(NULL, delim.c_str());
            }
            delete[] src;
        }

        return result;
    }

} // namespace testing
