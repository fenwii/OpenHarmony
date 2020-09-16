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

#ifndef GRAPHIC_LITE_WIN_FILE_H
#define GRAPHIC_LITE_WIN_FILE_H

#ifdef _WIN32

#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>
#include <direct.h>
#include "file.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void WinFileInit();

int32_t WinOpen(const char* path, int32_t oflag);

int32_t WinClose(int32_t handle);

int32_t WinWrite(int32_t handle, const void* buf, uint32_t nbyte);

int32_t WinRead(int32_t handle, void* buf, uint32_t nbyte);

off_t WinSeek(int32_t handle, off_t offset, int32_t whence);

int32_t WinUnlink(const char* path);

int32_t WinStatFD(int32_t handle, FileStatInfo* buf);

int32_t WinStat(const char* path, FileStatInfo* buf);

int32_t WinSync(int32_t handle);

int32_t WinDataSync(int32_t handle);

int32_t WinMakeDir(const char* path);

int32_t WinRemoveDir(const char* path);

int32_t WinRename(const char* oldName, const char* newName);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _WIN32
#endif // GRAPHIC_LITE_WIN_FILE_H
