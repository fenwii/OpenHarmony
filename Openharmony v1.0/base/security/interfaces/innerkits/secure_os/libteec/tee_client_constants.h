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

#ifndef _TEE_CLIENT_CONSTANTS_H_
#define _TEE_CLIENT_CONSTANTS_H_

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Error code
 */
enum TEEC_ReturnCode {
    TEEC_SUCCESS = 0x0,                   /* Return success */
    TEEC_ERROR_INVALID_CMD,               /* Invalid cmds，unsupported */
    TEEC_ERROR_SERVICE_NOT_EXIST,         /* TA not exist */
    TEEC_ERROR_SESSION_NOT_EXIST,         /* Session not exit */
    TEEC_ERROR_SESSION_MAXIMUM,           /* The number of security service sessions reaches the maximum. */
    TEEC_ERROR_REGISTER_EXIST_SERVICE,    /* Register an Existing Security Service */
    TEEC_ERROR_TAGET_DEAD_FATAL,          /* Global task error，(global is the basic of all services) */
    TEEC_ERROR_READ_DATA,                 /* Read file error */
    TEEC_ERROR_WRITE_DATA,                /* Write file error */
    TEEC_ERROR_TRUNCATE_OBJECT,           /* Truncate file error */
    TEEC_ERROR_SEEK_DATA,                 /* Seek file error */
    TEEC_ERROR_FSYNC_DATA,                /* Fsync file error */
    TEEC_ERROR_RENAME_OBJECT,             /* Rename file error */
    TEEC_ERROR_TRUSTED_APP_LOAD_ERROR,    /* Load TA error during opening session */
    TEEC_ERROR_GENERIC = 0xFFFF0000,      /* Generic error */

    /* Permission verification failed，during init context, open session, and invoke cmd */
    TEEC_ERROR_ACCESS_DENIED = 0xFFFF0001,

    /* Operation cancel，if paramer cancel flag is set, Operation with this paramer will thow this error. */
    TEEC_ERROR_CANCEL = 0xFFFF0002,

    /* Concurrent access leads to permission conflict,
        Concurrent access to files in secstorage service can cause such errors */
    TEEC_ERROR_ACCESS_CONFLICT = 0xFFFF0003,

    /* The operation contains too much data for the security service to parse */
    TEEC_ERROR_EXCESS_DATA = 0xFFFF0004,

    /* Incorrect data format,The parameter format does not meet the communication protocol between CA and TA,
        TA cannot parse it */
    TEEC_ERROR_BAD_FORMAT = 0xFFFF0005,

    /* Invalid parameter, null or illegal input parameter */
    TEEC_ERROR_BAD_PARAMETERS = 0xFFFF0006,

    /* The operation in the current state is invalid, when secstore service operation is requested,
        this error is returned if the secure store service is not initialized */
    TEEC_ERROR_BAD_STATE = 0xFFFF0007,

    /* The requested data was not found */
    TEEC_ERROR_ITEM_NOT_FOUND = 0xFFFF0008,

    /* The requested operation exists but is not yet implemented,
        This error is returned when the operation is requested to be cancelled */
    TEEC_ERROR_NOT_IMPLEMENTED = 0xFFFF0009,

    /* The requested operation is valid but not supported,
        Some algorithms such as DSA for secure encryption and decryption services return such errors  */
    TEEC_ERROR_NOT_SUPPORTED = 0xFFFF000A,

    /* Data error. The requested operation cannot find the corresponding data */
    TEEC_ERROR_NO_DATA = 0xFFFF000B,

    /* Insufficient system resources, Memory request failure will return this error */
    TEEC_ERROR_OUT_OF_MEMORY = 0xFFFF000C,

    /* system busy. The system may be monopolizing some resources */
    TEEC_ERROR_BUSY = 0xFFFF000D,

    /* An error occurred while CA was communicating with the SA */
    TEEC_ERROR_COMMUNICATION = 0xFFFF000E,

    /* Security error detected, security world error */
    TEEC_ERROR_SECURITY = 0xFFFF000F,

    /* Memory input length is less than output length，#TEEC_MEMREF_TEMP_OUTPUT may get such error */
    TEEC_ERROR_SHORT_BUFFER = 0xFFFF0010,

    TEEC_ERROR_MAC_INVALID = 0xFFFF3071,     /* Mac check error */
    TEEC_ERROR_TARGET_DEAD = 0xFFFF3024,     /* Trusted Application dead */
    TEEC_FAIL              = 0xFFFF5002
};

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * error code source
 */
enum TEEC_ReturnCodeOrigin {
    TEEC_ORIGIN_API = 0x1,         /* error code from client api */
    TEEC_ORIGIN_COMMS = 0x2,       /* error code from Communication between REE and TEE */
    TEEC_ORIGIN_TEE = 0x3,         /* error code from TEE */
    TEEC_ORIGIN_TRUSTED_APP = 0x4, /* error code from TEE service */
};

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * shared memory flag
 */
enum TEEC_SharedMemCtl {
    TEEC_MEM_INPUT = 0x1,  /* data is from CA to TA */
    TEEC_MEM_OUTPUT = 0x2, /* data is from TA to CA */
    TEEC_MEM_INOUT = 0x3,  /* data is Communication between TA ands CA */
};

/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Paramer type
 */
enum TEEC_ParamType {
    TEEC_NONE = 0x0,  /* not use */

    /* Corresponding to #TEEC_Value, only for input, data is from CA to TA */
    TEEC_VALUE_INPUT = 0x01,

    /* Corresponding to #TEEC_Value, only for output, data is from TA to CA */
    TEEC_VALUE_OUTPUT = 0x02,

    /* Corresponding to #TEEC_Value, it can be both input or output */
    TEEC_VALUE_INOUT = 0x03,

    /* Corresponding to #TEEC_TempMemoryReference, only for input, data is from CA to TA */
    TEEC_MEMREF_TEMP_INPUT = 0x05,

    /* Corresponding to #TEEC_TempMemoryReference, only for output, data is from TA to CA */
    TEEC_MEMREF_TEMP_OUTPUT = 0x06,

    /* Corresponding to #TEEC_TempMemoryReference, it can be both input or output */
    TEEC_MEMREF_TEMP_INOUT = 0x07,

    /* Corresponding to #TEEC_IonReference, only for input, data is from CA to TA */
    TEEC_ION_INPUT = 0x08,

    /* Corresponding to #TEEC_IonSglistReference, only for input, data is from CA to TA */
    TEEC_ION_SGLIST_INPUT = 0x09,

    /* Corresponding to #TEEC_RegisteredMemoryReference, Reference whole memory,
        Data flow is consistent with TEEC_Sharedmemctl */
    TEEC_MEMREF_WHOLE = 0xc,

    /* Corresponding to #TEEC_RegisteredMemoryReference, only for input, data is from CA to TA */
    TEEC_MEMREF_PARTIAL_INPUT = 0xd,

    /* Corresponding to #TEEC_RegisteredMemoryReference, only for output, data is from TA to CA */
    TEEC_MEMREF_PARTIAL_OUTPUT = 0xe,

    /* Corresponding to #TEEC_RegisteredMemoryReference, it can be both input or output */
    TEEC_MEMREF_PARTIAL_INOUT = 0xf
};

/****************************************************
 *      Session Login Methods
 ****************************************************/
/*
 * @ingroup  TEEC_COMMON_DATA
 *
 * Login mode
 */
enum TEEC_LoginMethod {
    TEEC_LOGIN_PUBLIC = 0x0,            /* No login data is required */
    TEEC_LOGIN_USER,                    /* Provide user login data to run client applications */
    TEEC_LOGIN_GROUP,                   /* Provide user group login data to run client applications */
    TEEC_LOGIN_APPLICATION = 0x4,       /* Provide application login data to run client applications */
    TEEC_LOGIN_USER_APPLICATION = 0x5,  /* Provide application login data and user login data */
    TEEC_LOGIN_GROUP_APPLICATION = 0x6, /* Provide application login data and user group login data */
    TEEC_LOGIN_IDENTIFY = 0x7,          /* Provide login data when using secstorage */
};
enum TST_CMD_ID {
    TST_CMD_ID_01 = 1,
    TST_CMD_ID_02,
    TST_CMD_ID_03,
    TST_CMD_ID_04,
    TST_CMD_ID_05
};
#define AGENT_FS_ID 0x46536673
#define AGENT_MISC_ID 0x4d495343

#define TEEC_PARAM_NUM 4    /* teec param max number */
#define TEEC_PARAM_ONE 0
#define TEEC_PARAM_TWO 1
#define TEEC_PARAM_THREE 2
#define TEEC_PARAM_FOUR 3
#endif
