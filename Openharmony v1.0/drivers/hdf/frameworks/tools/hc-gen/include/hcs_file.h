/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
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

#ifndef HCS_COMPILER_FILE_H
#define HCS_COMPILER_FILE_H

#include <stdio.h>
#include "hcs_types.h"

#define HCS_SOURCE_FILE_SUFFIX ".hcs"
#define HCS_OUTPUT_FILE_SUFFIX ".hcb"
#define HCS_DECOMPILE_OUTPUT_FILE_SUFFIX ".d.hcs"

struct HcsFile {
    const char *name;
    const char *fullPath;
    FILE *file;
    uint64_t pos;
    struct HcsFile *next;
};

struct HcsFileQueue {
    struct HcsFile *head;
    uint32_t count;
};

struct HcsSourceName {
    const char *name;
    struct HcsSourceName *next;
};

const char *HcsGetInputFileName();

void HcsSetInputFileName(const char *name);

int32_t HcsOpenSourceFile(const char *path, struct HcsFile **file, const char *flag);

void HcsCloseFile(struct HcsFile *file);

int32_t HcsSetOutPutName(const char *name);

int32_t HcsSetOutPutNameWithCurrentWorkPath(const char *name);

const char *HcsGetOutPutFileName();

const char *HcsGetStripedOutputFileName();

struct HcsFile *HcsOpenOutputFile(const char *suffix);

void HcsCloseOutput(struct HcsFile *output);

int32_t HcsOutputWrite(const void *buffer, uint32_t length);

int32_t HcsOutputWriteAlign(const void *buffer, uint32_t length);

void HcsMockOutPut(bool dummyOutput);

uint32_t HcsGetOutputCurrentCount(void);

void HcsResetOutputCurrentCount(void);

void HcsSourceQueuePush(struct HcsFile *sourceFile);

void HcsSourceQueuePop();

struct HcsFile *HcsSourceQueueTop();

uint32_t HcsSourceQueueSize();

const char *HcsGetCurrentSourceName();

int32_t HcsSourceNameSetPush(const char *name);

void HcsSourceNameSetClean(void);

bool HcsFileCopyDir(char *dst, uint32_t dstBufferSize, const char *fullPath);

uint64_t HcsSourceFileGetSize(struct HcsFile *file);

int32_t HcsSourceFileRead(struct HcsFile *file, uint8_t *out, uint32_t readSize);

uint32_t HcsGetSourceFilePos(struct HcsFile *file);

#endif // HCS_COMPILER_FILE_H
