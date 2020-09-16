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

#ifndef LIBTEEC_TEE_CA_DAEMON_H
#define LIBTEEC_TEE_CA_DAEMON_H
#include <sys/stat.h>

#define SFS_PARTITION_USER_SYMLINK "sec_storage_data_users/"
#ifdef SEC_STORAGE_DATA_NEW_PATH
#define SEC_STORAGE_DATA_USERS  "/data/vendor/sec_storage_data_users/"
#define SEC_STORAGE_DATA_USER_0 "/data/vendor/sec_storage_data_users/0"
#else
#define SEC_STORAGE_DATA_USERS  "/data/sec_storage_data_users/"
#define SEC_STORAGE_DATA_USER_0 "/data/sec_storage_data_users/0"
#endif

#define TRANS_BUFF_SIZE (4 * 1024) /* agent transfer share buffer size */
/* when reset to factory mode, keep the data in this patition */
#define SEC_STORAGE_ROOT_DIR "/storage/sec_storage/"

/* when reset to factory mode, clear the data in this patition */
#ifdef SEC_STORAGE_DATA_NEW_PATH
#define SEC_STORAGE_DATA_DIR "/storage/data/vendor/sec_storage_data/"
#define USER_DATA_DIR        "/storage/data/vendor/"
#else
#define SEC_STORAGE_DATA_DIR "/storage/data/sec_storage_data/"
#define USER_DATA_DIR        "/storage/data/"
#endif
#define ROOT_DIR "/"
/* 0600 only root can read and write sec_storage folder */
#define ROOT_DIR_PERM                   (S_IRUSR | S_IWUSR)
#define SFS_PARTITION_PERSISTENT        "sec_storage/"
#define SFS_PARTITION_TRANSIENT         "sec_storage_data/"
#define SFS_PARTITION_TRANSIENT_PRIVATE "sec_storage_data/_private"
#define SFS_PARTITION_TRANSIENT_PERSO   "sec_storage_data/_perso"

#define FILE_NAME_INVALID_STR "../" // file name path must not contain ../

#endif
