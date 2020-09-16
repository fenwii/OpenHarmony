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

#ifndef _TEE_AGENT_H
#define _TEE_AGENT_H

#include <stdint.h>
#include <stdio.h>

#define AGENT_FS_ID 0x46536673
#define AGENT_MISC_ID 0x4d495343

#define FILE_NAME_MAX_BUF       256
#define USEC_PER_MSEC 1000
#define K_BYTES 1024
#define TIME_START_YEAR 1900

/* static func declare */
typedef enum {
    SEC_OPEN,
    SEC_CLOSE,
    SEC_READ,
    SEC_WRITE,
    SEC_SEEK,
    SEC_REMOVE,
    SEC_TRUNCATE,
    SEC_RENAME,
    SEC_CREATE,
    SEC_INFO,
    SEC_ACCESS,
    SEC_ACCESS2,
    SEC_FSYNC,
    SEC_CP,
    SEC_DISKUSAGE,
    SEC_DELETE_ALL,
    SEC_MAX
} FsCmdType;

typedef enum {
    SEC_GET_TIME,
    MISC_CMD_MAX
} MiscCmdType;

enum {
    SEC_WRITE_SLOG,
    SEC_WRITE_SSA,
};

struct SecStorageType {
    FsCmdType cmd; /* for s to n */
    int32_t ret;   /* fxxx call's return */
    int32_t ret2;  /* fread: end-of-file or error;fwrite:the sendor is SSA or SLOG */
    uint32_t userId;
    uint32_t magic;
    uint32_t error;
    union Args1 {
        struct {
            char mode[4];
            uint32_t nameLen;
            uint32_t name[1]; /* change name[0] --> name[1], for pc-lint */
        } Open;
        struct {
            int32_t fd;
        } Close;
        struct {
            int32_t fd;
            uint32_t count;
            uint32_t buffer[1]; /* the same as name[0] --> name[1] */
        } Read;
        struct {
            int32_t fd;
            uint32_t count;
            uint32_t buffer[1];
        } Write;
        struct {
            int32_t fd;
            int32_t offset;
            uint32_t whence;
        } Seek;
        struct {
            uint32_t nameLen;
            uint32_t name[1];
        } Remove;
        struct {
            uint32_t len;
            uint32_t nameLen;
            uint32_t name[1];
        } Truncate;
        struct {
            uint32_t oldNameLen;
            uint32_t newNameLen;
            uint32_t buffer[1]; /* old_name + new_name */
        } Rename;
        struct {
            uint32_t fromPathLen;
            uint32_t toPathLen;
            uint32_t buffer[1]; /* from_path+to_path */
        } Cp;
        struct {
            char mode[4];
            uint32_t nameLen;
            uint32_t name[1];
        } Create;
        struct {
            int32_t fd;
            uint32_t curPos;
            uint32_t fileLen;
        } Info;
        struct {
            int mode;
            uint32_t nameLen;
            uint32_t name[1];
        } Access;
        struct {
            int32_t fd;
        } Fsync;
        struct {
            uint32_t secStorage;
            uint32_t data;
        } DiskUsage;
        struct {
            uint32_t pathLen;
            uint32_t path[1];
        } DeleteAll;
    } Args;
};

struct MiscControlType {
    MiscCmdType cmd; /* for s to n */
    int32_t ret;
    int32_t magic;
    union Args2 {
        struct {
            uint32_t seconds;
            uint32_t millis;
            char timeStr[30];
        } GetTime;
    } Args;
};

struct OpenedFile {
    FILE *file;
    struct OpenedFile *next;
    struct OpenedFile *prev;
};
#endif
