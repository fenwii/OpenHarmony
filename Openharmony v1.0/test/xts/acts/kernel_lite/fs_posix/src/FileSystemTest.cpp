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
#include "FileSystemTest.h"
#include <unistd.h>
#include "utils.h"

using namespace testing::ext;

// before testCase
void FileSystemTest::SetUp()
{
    LOG("------- case start");
    mCurPath = GetCurrentPath();
    int rt = chdir(TOP_DIR);
    if (rt == -1) {
        LOG("== chdir to %s failed! rt=%d, errno=%d", TOP_DIR, rt, errno);
    } else {
        LOG("== chdir to %s OK!", TOP_DIR);
    }
}

// after testCase
void FileSystemTest::TearDown()
{
    RemoveDir(TOP_DIR "/" DIR0);
    remove(TOP_DIR "/" FILE0);
    int rt = chdir(mCurPath);
    if (rt == -1) {
        LOG("== chdir to %s failed! rt=%d, errno=%d", mCurPath, rt, errno);
    } else {
        LOG("== chdir to %s OK!", mCurPath);
    }
    LOG("------- case end\n");
}

int main(int argc, char *argv[])
{
    testing::GTEST_FLAG(output) = "xml:";
    testing::InitGoogleTest(&argc, argv);
    if (access(TOP_DIR, F_OK) == 0) {
        RemoveDir(TOP_DIR "/" DIR0);
        remove(TOP_DIR "/" FILE0);
        return RUN_ALL_TESTS();
    } else {
        LOG("======= %s dose not exist. Test Stop.", TOP_DIR);
        return 0;
    }
}