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

#ifndef JS_NATIVE_API_CONFIG_H
#define JS_NATIVE_API_CONFIG_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define FILE_NAME_MAX_LEN 300
#define URI_NAME_MAX_LEN 128
#define TEXT_MAX_READ_LEN 4096
#define DIR_LEVEL 5
#define ERROR_CODE "code"
#define TEXT "text"
#define FILE_URI "uri"
#define FILE_SOURCE_URI "srcUri"
#define FILE_DESTINATION_URI "dstUri"
#define FILE_LENGTH "length"
#define FILE_LAST_MODIFIED_TIME "lastModifiedTime"
#define FILE_TYPE "type"
#define FILE_POSITION "position"
#define FILE_APPEND "append"
#define FILE_BUFFER "buffer"
#define KV_KEY "key"
#define KV_VALUE "value"
#define DEFAULT "default"
#define FILE_PREFIX "internal://app"
#define DEFAULT_FOLDER_PATH "kvstore"
#define TYPE_FILE "file"
#define TYPE_DIR "dir"
#define FILE_LIST "fileList"
#define RECURSIVE "recursive"
#define SUB_FILES "subFiles"
#define ERR_NO_FILE "File or directory not exist"
#define ERR_IO_EXCEPTION "I/O error"
#define ERR_ILLEGAL_PARAM "Invalid parameter"
#define ERR_GENERAL "System error"
#define ERR_READ_TOO_LONG "The content of the file to be read exceeds 4KB"

#define NATIVE_FEATURE_ON 1
#define NATIVE_FEATURE_OFF 0

enum ErrorCode {
    NATIVE_SUCCESS = 0,
    ERROR_FR_NO_FILE = -2,
    ERROR_DIR_NOT_EMPTY = -39,
    ERROR_CODE_GENERAL = -200,
    ERROR_CODE_PARAM = -202,
    ERROR_CODE_IO = -300,
    ERROR_CODE_NO_FILE = -301,
    ERROR_CODE_READ_TOO_LONG = -302
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* JS_NATIVE_API_COMMON_H */