/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SECURITY_APP_FILE_H
#define SECURITY_APP_FILE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define FILE_OPEN_FAIL_ERROR_NUM (-1)

enum ReadFileErrorCode {
    DEST_BUFFER_IS_NULL = -1,
    FILE_IS_CLOSE = -2,
    MMAP_COPY_FAILED = -3,
    READ_OFFSET_OUT_OF_RANGE = -4,
    MMAP_FAILED = -5,
    MMAP_PARAM_INVALID = -6,
};

typedef struct {
    int mmapPosition;
    int readMoreLen;
    int mmapSize;
    char* mapAddr;
} MmapInfo;

typedef struct {
    int fp;
    int offset;
    int len;
} FileRead;

int InitVerify(FileRead *file, const char *filePath, int *handle);
int HapMMap(int bufCapacity, int offset, MmapInfo *mmapInfo, const FileRead *file);
void HapMUnMap(char *mapAddr, int mmapSize);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
