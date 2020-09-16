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

#ifndef _TEE_CLIENT_ID_H_
#define _TEE_CLIENT_ID_H_

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Security Global services UUID，Global service is the basic of all services
 */
#define TEE_SERVICE_GLOBAL \
{ \
    0x00000000, \
    0x0000, \
    0x0000, \
    { \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
    } \
}

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Security Echo services UUID
 */
#define TEE_SERVICE_ECHO \
{ \
    0x01010101, \
    0x0101, \
    0x0101, \
    { \
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 \
    } \
}

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Security secstorage services UUID
 */
#define TEE_SERVICE_STORAGE \
{ \
    0x02020202, \
    0x0202, \
    0x0202, \
    { \
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 \
    } \
}

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Security ut services UUID
 */
#define TEE_SERVICE_UT \
{ \
    0x03030303, \
    0x0303, \
    0x0303, \
    { \
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 \
    } \
}

/*
 * @ingroup  TEE_ID
 *
 * Security crypto services UUID
 */
#define TEE_SERVICE_CRYPTO \
{ \
    0x04040404, \
    0x0404, \
    0x0404, \
    { \
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 \
    } \
}

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Security Global service cmd id
 */
enum SVC_GLOBAL_CMD_ID {
    GLOBAL_CMD_ID_INVALID = 0x0,        /* Invalid cmd */
    GLOBAL_CMD_ID_BOOT_ACK,             /* Boot ack */
    GLOBAL_CMD_ID_OPEN_SESSION,         /* Open Session */
    GLOBAL_CMD_ID_CLOSE_SESSION,        /* Close Session */
    GLOBAL_CMD_ID_LOAD_SECURE_APP,      /* Dynamic load TA */
    GLOBAL_CMD_ID_NEED_LOAD_APP,        /* Determine whether TA needs to be loaded */
    GLOBAL_CMD_ID_REGISTER_AGENT,       /* Register agent */
    GLOBAL_CMD_ID_UNREGISTER_AGENT,     /* Unregister agent */
    GLOBAL_CMD_ID_REGISTER_NOTIFY_MEMORY,   /* Register notify memory buffer */
    GLOBAL_CMD_ID_UNREGISTER_NOTIFY_MEMORY, /* Unregister notify memory buffer */
    GLOBAL_CMD_ID_INIT_CONTENT_PATH,        /* Init content path */
    GLOBAL_CMD_ID_TERMINATE_CONTENT_PATH,   /* Release content path */
    GLOBAL_CMD_ID_ALLOC_EXCEPTION_MEM,      /* Alloc exception info memory */
    GLOBAL_CMD_ID_TEE_TIME,                 /* Get Tee time */
    GLOBAL_CMD_ID_TEE_INFO,
    GLOBAL_CMD_ID_INVOKE_COMMAND,          /* Invoke command */
    GLOBAL_CMD_ID_GET_TA_CALL_CMD,
    GLOBAL_CMD_ID_REGISTER_TA_CALL_CMD,
    GLOBAL_CMD_ID_UNREGISTER_TA_CALL_CMD,
    GLOBAL_CMD_ID_PUSH_TA_RESULT_CMD,
    GLOBAL_CMD_ID_TA_INVOKE_COMMAND,
    GLOBAL_CMD_ID_MAX,
};

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Security echo service cmd id
 */
enum SVC_ECHO_CMD_ID {
    ECHO_CMD_ID_INVALID = 0x0,
    ECHO_CMD_ID_SEND_CMD,
    ECHO_CMD_ID_EFUSE_READ,
    ECHO_CMD_ID_EFUSE_WRITE,
    ECHO_CMD_ID_MAX,
};

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Security secstorage service cmd ids
 */
enum SVC_STORAGE_CMD_ID {
    STORAGE_CMD_ID_INVALID = 0x10,        /* Invalid cmd */
    STORAGE_CMD_ID_OPEN,                  /* Open file */
    STORAGE_CMD_ID_CLOSE,                 /* Close file */
    STORAGE_CMD_ID_CLOSEALL,              /* Close all files */
    STORAGE_CMD_ID_READ,                  /* Read file */
    STORAGE_CMD_ID_WRITE,                 /* Write file */
    STORAGE_CMD_ID_SEEK,                  /* Seek file */
    STORAGE_CMD_ID_TELL,                  /* Obtains the current value of the file position */
    STORAGE_CMD_ID_TRUNCATE,              /* Truncate file */
    STORAGE_CMD_ID_REMOVE,                /* Remove file */
    STORAGE_CMD_ID_FINFO,                 /* Get file info */
    STORAGE_CMD_ID_FSYNC,                 /* Sync file to disk */
    STORAGE_CMD_ID_UNKNOWN = 0x7FFFFFFE,  /* Unknown id */
    STORAGE_CMD_ID_MAX = 0x7FFFFFFF,
};

#endif
