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

#include "file.h"

#if defined(_LITEOS) && defined(_WIN32)
#error platform define err, check _LITEOS and _WIN32
#endif // _LITEOS && _WIN32

#if defined(_LITEOS) && defined(__linux__)
#error platform define err, check _LITEOS and __linux__
#endif // _LITEOS && __linux__


#if defined(_LITEOS)
#include "mc_file.h"
#elif defined _WIN32
#include "win_file.h"
#elif defined __linux__ || defined __LITEOS__
#include "linux_file.h"
#endif

FileOperations* g_fileOp = NULL;

void FileInit()
{
#ifdef _LITEOS
    MCFileInit();
#elif defined _WIN32
    WinFileInit();
#elif defined __linux__ || defined __LITEOS__
    LinuxFileInit();
#else
#error must define one at least
#endif
}
