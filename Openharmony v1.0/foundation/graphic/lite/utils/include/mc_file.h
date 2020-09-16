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

#ifndef GRAPHIC_LITE_MC_FILE_H
#define GRAPHIC_LITE_MC_FILE_H

#ifdef _LITEOS

#include <stdlib.h>
#include "mc_fs.h"  // set the right mc_fs.h path when porting to watch
#include "file.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void MCFileInit();

int32_t MCOpen(const char* path, int32_t oflag);

int32_t MCClose(int32_t handle);

int32_t MCWrite(int32_t handle, const void* buf, uint32_t nbyte);

int32_t MCRead(int32_t handle, void* buf, uint32_t nbyte);

off_t MCSeek(int32_t handle, off_t offset, int32_t whence);

int32_t MCUnlink(const char* path);

int32_t MCStatFD(int32_t handle, FileStatInfo* buf);

int32_t MCStat(const char* path, FileStatInfo* buf);

int32_t MCSync(int32_t handle);

int32_t MCDataSync(int32_t handle);

int32_t MCMakeDir(const char* path);

void* MCOpenDir(const char* path);

int32_t MCReadDir(void* dirp, FileDirentInfo* dirInfo);

int32_t MCCloseDir(void* dirp);

int32_t MCRemoveDir(const char* path);

int32_t MCRename(const char* oldName, const char* newName);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LITEOS
#endif // GRAPHIC_LITE_MC_FILE_H
