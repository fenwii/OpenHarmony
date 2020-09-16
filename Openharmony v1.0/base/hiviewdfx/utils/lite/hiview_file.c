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

#include "securec.h"
#include "hos_types.h"
#include "hiview_def.h"
#include "hiview_util.h"
#include "hiview_file.h"

/* Refresh the file header information after every 10 file operations. */
#define FILE_HEADER_UPDATE_CTL   10

static uint16 GetReadCursor(HiviewFile *fp);

boolean InitHiviewFile(HiviewFile *fp, HiviewFileType type, uint32 size)
{
    if (fp == NULL || fp->path == NULL) {
        return FALSE;
    }

    fp->fhandle = HIVIEW_FileOpen(fp->path);
    if (fp->fhandle < 0) {
        return FALSE;
    }
    fp->type = (uint8)type;
    fp->headerUpdateCtl = 0;
    HiviewFileHeader *pHeader = &(fp->header);
    FileHeaderCommon *pCommon = &(pHeader->common);
    pHeader->size = size + sizeof(HiviewFileHeader);
    // Create file for the first time
    if (ReadFileHeader(fp) == FALSE) {
        switch (fp->type) {
            case HIVIEW_LOG_TEXT_FILE:
                pCommon->prefix = HIVIEW_FILE_HEADER_PREFIX_TEXT;
                break;
            case HIVIEW_LOG_BIN_FILE:
                pCommon->prefix = HIVIEW_FILE_HEADER_PREFIX_LOG;
                break;
            case HIVIEW_FAULT_EVENT_FILE:
            case HIVIEW_UE_EVENT_FILE:
            case HIVIEW_STAT_EVENT_FILE:
                pCommon->prefix = HIVIEW_FILE_HEADER_PREFIX_EVENT;
                break;
            default:
                break;
        }
        pCommon->codeMainVersion = HIVIEW_FILE_HEADER_MAIN_VERSION;
        pCommon->codeSubVersion = HIVIEW_FILE_HEADER_SUB_VERSION;
        pCommon->defineFileVersion = HIVIEW_FILE_HEADER_DEFINE_FILE_VER;
        pHeader->createTime = (uint32)(HIVIEW_GetCurrentTime() / MS_PER_SECOND);
        pHeader->usedSize = sizeof(HiviewFileHeader);
        pHeader->wCursor = sizeof(HiviewFileHeader);
        if (WriteFileHeader(fp) == FALSE) {
            return FALSE;
        }
    } else {
        // Version number may change after system upgrade
        pCommon->codeMainVersion = HIVIEW_FILE_HEADER_MAIN_VERSION;
        pCommon->codeSubVersion = HIVIEW_FILE_HEADER_SUB_VERSION;
        pCommon->defineFileVersion = HIVIEW_FILE_HEADER_DEFINE_FILE_VER;
    }

    return TRUE;
}

boolean WriteFileHeader(HiviewFile *fp)
{
    if (fp == NULL || fp->fhandle < 0) {
        return FALSE;
    }

    int32 ret;
    if (HIVIEW_FileSeek(fp->fhandle, 0, HIVIEW_SEEK_SET) >= 0) {
        ret = HIVIEW_FileWrite(fp->fhandle, (uint8 *)&(fp->header), sizeof(HiviewFileHeader));
        if (ret == sizeof(HiviewFileHeader)) {
            return TRUE;
        }
    }

    return FALSE;
}

boolean ReadFileHeader(HiviewFile *fp)
{
    HiviewFileHeader h = { 0 };

    if (fp == NULL || fp->fhandle < 0) {
        return FALSE;
    }

    int32 ret;
    uint32 t = (uint32)(HIVIEW_GetCurrentTime() / MS_PER_SECOND);
    if (HIVIEW_FileSeek(fp->fhandle, 0, HIVIEW_SEEK_SET) < 0) {
        return FALSE;
    }
    ret = HIVIEW_FileRead(fp->fhandle, (uint8 *)&h, sizeof(HiviewFileHeader));
    if ((ret == sizeof(HiviewFileHeader)) && (h.createTime < t) &&
        ((h.common.prefix & 0xFFFFFF00) == HIVIEW_FILE_HEADER_PREFIX_MASK)) {
        memcpy_s(&(fp->header), sizeof(HiviewFileHeader), (void *)&h, sizeof(HiviewFileHeader));
        return TRUE;
    } else {
        return FALSE;
    }
}

int32 WriteToFile(HiviewFile *fp, const uint8 *data, uint32 len)
{
    if (fp == NULL || fp->fhandle < 0 || len == 0 || GetFileFreeSize(fp) < len) {
        return 0;
    }
    int32 wLen = 0;
    int32 firstLen, secondLen;
    HiviewFileHeader *h = &(fp->header);
    // overflow
    if (h->wCursor + len > h->size) {
        firstLen = h->size - h->wCursor;
        if (firstLen > 0) {
            if ((HIVIEW_FileSeek(fp->fhandle, h->wCursor, HIVIEW_SEEK_SET) < 0) ||
                firstLen != HIVIEW_FileWrite(fp->fhandle, data, firstLen)) {
                return 0;
            }
            h->wCursor += firstLen;
            h->usedSize += firstLen;
            wLen += firstLen;
        }
        // jump file header
        h->wCursor = sizeof(HiviewFileHeader);
        secondLen = len - firstLen;
        if ((HIVIEW_FileSeek(fp->fhandle, h->wCursor, HIVIEW_SEEK_SET) > 0) && (secondLen > 0) &&
            (secondLen == HIVIEW_FileWrite(fp->fhandle, data + firstLen, secondLen))) {
            h->wCursor += secondLen;
            h->usedSize += secondLen;
            wLen += secondLen;
        }
    } else {
        if (HIVIEW_FileSeek(fp->fhandle, h->wCursor, HIVIEW_SEEK_SET) < 0) {
            return 0;
        }
        if ((int32)len == HIVIEW_FileWrite(fp->fhandle, data, len)) {
            h->wCursor += len;
            h->usedSize += len;
            wLen += len;
        }
    }
    if (fp->headerUpdateCtl >= FILE_HEADER_UPDATE_CTL) {
        fp->headerUpdateCtl = 0;
        if (WriteFileHeader(fp) == FALSE) {
            return 0;
        }
    } else {
        fp->headerUpdateCtl++;
    }
    return wLen;
}

int32 ReadFromFile(HiviewFile *fp, uint8 *data, uint32 readLen)
{
    if (fp == NULL || data == NULL || fp->fhandle < 0 || readLen == 0) {
        return 0;
    }

    uint32 usedSize = GetFileUsedSize(fp);
    if (usedSize < readLen) {
        return 0;
    }
    int32 rLen = 0;
    int32 firstLen, secondLen;
    HiviewFileHeader *h = &(fp->header);
    uint32 rCursor = GetReadCursor(fp);
    // overflow
    if (rCursor + readLen > h->size) {
        firstLen = h->size - rCursor;
        if (firstLen > 0) {
            if ((HIVIEW_FileSeek(fp->fhandle, rCursor, HIVIEW_SEEK_SET) < 0) ||
                (firstLen != HIVIEW_FileRead(fp->fhandle, data, firstLen))) {
                return 0;
            }
            h->usedSize -= firstLen;
            rLen += firstLen;
        }
        secondLen = readLen - firstLen;
        // jump file header
        if ((HIVIEW_FileSeek(fp->fhandle, sizeof(HiviewFileHeader), HIVIEW_SEEK_SET) > 0) &&
            (secondLen > 0) && (secondLen == HIVIEW_FileRead(fp->fhandle, data + firstLen, secondLen))) {
            h->usedSize -= secondLen;
            rLen += secondLen;
        }
    } else {
        if (HIVIEW_FileSeek(fp->fhandle, rCursor, HIVIEW_SEEK_SET) < 0) {
            return 0;
        }
        if ((int32)readLen == HIVIEW_FileRead(fp->fhandle, data, readLen)) {
            h->usedSize -= readLen;
            rLen += readLen;
        }
    }
    if (fp->headerUpdateCtl >= FILE_HEADER_UPDATE_CTL) {
        fp->headerUpdateCtl = 0;
        if (WriteFileHeader(fp) == FALSE) {
            return 0;
        }
    } else {
        fp->headerUpdateCtl++;
    }
    return rLen;
}

uint32 GetFileUsedSize(HiviewFile *fp)
{
    if (fp == NULL || fp->fhandle < 0) {
        return 0;
    }

    HiviewFileHeader *h = &(fp->header);
    if (h->usedSize > sizeof(HiviewFileHeader)) {
        return h->usedSize - sizeof(HiviewFileHeader);
    } else {
        return 0;
    }
}

uint32 GetFileFreeSize(HiviewFile *fp)
{
    if (fp == NULL || fp->fhandle < 0) {
        return 0;
    }

    return (fp->header.size - fp->header.usedSize);
}

int32 CloseHiviewFile(HiviewFile *fp)
{
    if (fp != NULL && fp->fhandle > 0) {
        if (WriteFileHeader(fp) == FALSE) {
            return -1;
        }
        return HIVIEW_FileClose(fp->fhandle);
    }

    return -1;
}

static uint16 GetReadCursor(HiviewFile *fp)
{
    if (fp == NULL || fp->fhandle < 0) {
        return 0;
    }

    HiviewFileHeader *h = &(fp->header);
    if (h->wCursor >= h->usedSize) {
        return sizeof(HiviewFileHeader) + (h->wCursor - h->usedSize);
    } else {
        return (h->size - (h->usedSize - h->wCursor));
    }
}
