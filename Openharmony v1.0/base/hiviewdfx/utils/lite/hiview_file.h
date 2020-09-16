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

#ifndef HOS_LITE_HIVIEW_FILE_H
#define HOS_LITE_HIVIEW_FILE_H

#include "hos_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define HIVIEW_FILE_HEADER_PREFIX_LOG      0x48565701      /* HVW ASCii + 0x01 */
#define HIVIEW_FILE_HEADER_PREFIX_EVENT    0x48565702      /* HVW ASCii + 0x02 */
#define HIVIEW_FILE_HEADER_PREFIX_TEXT     0x48565703      /* HVW ASCii + 0x03 */
#define HIVIEW_FILE_HEADER_PREFIX_MASK     0x48565700      /* HVW ASCii + 0x00 */
#define HIVIEW_FILE_HEADER_MAIN_VERSION    1               /* Main version:1 */
#define HIVIEW_FILE_HEADER_SUB_VERSION     10              /* Sub version:10 (lite) */
#define HIVIEW_FILE_HEADER_DEFINE_FILE_VER 200602001       /* XML file version:200602001 */
#define HIVIEW_CONF_PRODUCT_VER_STR        "1.0.0"

typedef enum {
    HIVIEW_LOG_TEXT_FILE = 0,
    HIVIEW_LOG_BIN_FILE,
    HIVIEW_DUMP_FILE,
    HIVIEW_FAULT_EVENT_FILE,
    HIVIEW_UE_EVENT_FILE,
    HIVIEW_STAT_EVENT_FILE,
} HiviewFileType;

#pragma pack(1)
typedef struct {
    uint32 prefix;
    uint8 codeMainVersion;
    uint8 codeSubVersion;
    uint32 defineFileVersion;
} FileHeaderCommon;

typedef struct {
    FileHeaderCommon common;
    uint32 createTime;
    uint32 wCursor;
    uint32 usedSize;
    uint32 size;    /* Max size. Include the file header. */
} HiviewFileHeader;

typedef struct {
    HiviewFileHeader header;
    const char *path;
    int32 fhandle;  /* Circular file */
    uint8 type;     /* HiviewFileType */
    uint8 headerUpdateCtl;
} HiviewFile;
#pragma pack()

/**
 * Initialize the file object.
 * @param fp The address of hivew file object.
 * @param type file type.
 * @param size file size.
 * @return TRUE/FALSE.
 **/
boolean InitHiviewFile(HiviewFile *fp, HiviewFileType type, uint32 size);

/**
 * Write the file header to file.
 * @param fp The pointer of hivew file object.
 * @return TRUE/FALSE.
 **/
boolean WriteFileHeader(HiviewFile *fp);

/**
 * Read the file header from file.
 * @param fp The pointer of hivew file object.
 * @return TRUE/FALSE. TRUE: If the file contain the correct header info.
 **/
boolean ReadFileHeader(HiviewFile *fp);

/**
 * Write data to file.
 * @param fp The pointer of hivew file object.
 * @param data Data to be written to the file.
 * @param len The length of the data to be written. The length should be a multiple of a structure.
 * @return Length write.
 * @attention Reduce the file operation frequency. Otherwise, the watchdog may time out.
 **/
int32 WriteToFile(HiviewFile *fp, const uint8 *data, uint32 len);

/**
 * Read data form file.
 * @param fp The pointer of hivew file object.
 * @param data Buffer of reading data.
 * @param readLen The length of the data to be read. The length should be a multiple of a structure.
 * @return Length read.
 * @attention Reduce the file operation frequency. Otherwise, the watchdog may time out.
 **/
int32 ReadFromFile(HiviewFile *fp, uint8 *data, uint32 readLen);

/**
 * Get used size of file. Do not contain the size of file header.
 * @param fp The pointer of hivew file object.
 * @return used size. Not include the file header.
 **/
uint32 GetFileUsedSize(HiviewFile *fp);

/**
 * Get free size of file.
 * @param fp The pointer of hivew file object.
 * @return free size. Not include the file header.
 **/
uint32 GetFileFreeSize(HiviewFile *fp);

/**
 * Close the file.
 * @param fp The pointer of hivew file object.
 * @return 0:success -1:failure.
 **/
int32 CloseHiviewFile(HiviewFile *fp);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HOS_LITE_HIVIEW_FILE_H */
