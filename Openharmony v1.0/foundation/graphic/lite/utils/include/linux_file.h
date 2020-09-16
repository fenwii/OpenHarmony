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

#ifndef GRAPHIC_LITE_LINUX_FILE_H
#define GRAPHIC_LITE_LINUX_FILE_H

#if defined __linux__ || defined __LITEOS__

#include <memory.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "file.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    void LinuxFileInit();

    int32_t LinuxOpen(const char* path, int32_t oflag);

    int32_t LinuxClose(int32_t handle);

    int32_t LinuxWrite(int32_t handle, const void* buf, uint32_t nbyte);

    int32_t LinuxRead(int32_t handle, void* buf, uint32_t nbyte);

    off_t LinuxSeek(int32_t handle, off_t offset, int32_t whence);

    int32_t LinuxUnlink(const char* path);

    int32_t LinuxStatFD(int32_t handle, FileStatInfo* buf);

    int32_t LinuxStat(const char* path, FileStatInfo* buf);

    int32_t LinuxSync(int32_t handle);

    int32_t LinuxDataSync(int32_t handle);

    int32_t LinuxMakeDir(const char* path);

    void* LinuxOpenDir(const char* path);

    int32_t LinuxReadDir(void* dirp, FileDirentInfo* dirInfo);

    int32_t LinuxCloseDir(void* dirp);

    int32_t LinuxRemoveDir(const char* path);

    int32_t LinuxRename(const char* oldName, const char* newName);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __linux__
#endif // GRAPHIC_LITE_LINUX_FILE_H
