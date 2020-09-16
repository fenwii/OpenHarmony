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

/**
 * @addtogroup pms_types
 * @{
 *
 * @brief Defines variables and data structures used by the permission management module.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file pms_types.h
 *
 * @brief Declares variables and data structures used by the permission management module.
 *
 * To use permission management APIs, you must obtain this file.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef PMS_TYPES_H
#define PMS_TYPES_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @brief Indicates the length of a permission name.
 *
 * The default length is 64 bytes, including the terminating null byte <b>'\0'</b>.
 */
#define PERM_NAME_LEN 64
/**
 * @brief Indicates the length of a permission description.
 *
 * The default length is 128 bytes, including the terminating null byte <b>'\0'</b>.
 */
#define PERM_DESC_LEN 128

/**
 * @brief Enumerates granting statuses of the permission.
 *
 */
enum IsGranted {
    NOT_GRANTED = 0,  /** Not granted */
    GRANTED = 1,      /** Granted */
};

/**
 * @brief Defines the permission, including the name, description, and whether the permission is granted.
 *
 */
typedef struct {
    char name[PERM_NAME_LEN];  /** Permission name. For details about its length, see {@link PERM_NAME_LEN}. */
    char desc[PERM_DESC_LEN];  /** Permission description. For details about its length, see {@link PERM_DESC_LEN}. */
    enum IsGranted granted;    /** Whether the permission is granted */
} PermissionSaved;

/**
 * @brief Enumerates error codes of the permission management module.
 *
 */
enum PmsErrorCode {
    PERM_ERRORCODE_SUCCESS = 0,           /** Success */
    PERM_ERRORCODE_INVALID_PARAMS = 10,   /** Invalid parameters */
    PERM_ERRORCODE_INVALID_PERMNAME,      /** Invalid permission name */
    PERM_ERRORCODE_MALLOC_FAIL,           /** Failed to allocate memory using the <b>malloc</b> function. */
    PERM_ERRORCODE_OPENFD_FAIL,           /** Failed to open the file descriptor. */
    PERM_ERRORCODE_READFD_FAIL,           /** Failed to read the file descriptor. */
    PERM_ERRORCODE_WRITEFD_FAIL,          /** Failed to write the file descriptor. */
    PERM_ERRORCODE_JSONPARSE_FAIL,        /** Failed to parse the JSON string. */
    PERM_ERRORCODE_COPY_ERROR,            /** Failed to copy the string. */
    PERM_ERRORCODE_FIELD_TOO_LONG,        /** The permission name or description is too long. */
    PERM_ERRORCODE_PERM_NOT_EXIST,        /** The permission does not exist. */
    PERM_ERRORCODE_UNLINK_ERROR,          /** Failed to delete the permission file. */
    PERM_ERRORCODE_FILE_NOT_EXIST,        /** The file does not exist. */
    PERM_ERRORCODE_MEMSET_FAIL,           /** Failed to set memory using the <b>memset</b> function. */
    PERM_ERRORCODE_STAT_FAIL,             /** Failed to obtain information about the named file using the <b>stat</b>
                                           * function.
                                           */
    PERM_ERRORCODE_PATH_INVALID,          /** Invalid path */
    PERM_ERRORCODE_TOO_MUCH_PERM,         /** Too many permissions */
    PERM_ERRORCODE_TASKID_NOT_EXIST,      /** The process ID does not exist. */
    PERM_ERRORCODE_PERM_NUM_ERROR,        /** Abnormal number of permissions */
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif // PMS_TYPES_H