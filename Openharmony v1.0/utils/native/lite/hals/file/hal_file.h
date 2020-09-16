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

#ifndef HAL_FILE_SYSTEM_API_H
#define HAL_FILE_SYSTEM_API_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

int HalFileOpen(const char* path, int oflag, int mode);

int HalFileClose(int fd);

int HalFileRead(int fd, char *buf, unsigned int len);

int HalFileWrite(int fd, const char *buf, unsigned int len);

int HalFileDelete(const char *path);

int HalFileStat(const char *path, unsigned int *fileSize);

int HalFileSeek(int fd, int offset, unsigned int whence);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // HAL_FILE_SYSTEM_API_H