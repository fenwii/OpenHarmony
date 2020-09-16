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

#include <linux/types.h>

#ifndef _TEEK_CLIENT_CONSTANTS_H_
#define _TEEK_CLIENT_CONSTANTS_H_

enum GlobalServiceCmdId {
    GLOBAL_CMD_ID_INVALID = 0x0,
    GLOBAL_CMD_ID_BOOT_ACK = 0x1,
    GLOBAL_CMD_ID_OPEN_SESSION = 0x2,
    GLOBAL_CMD_ID_CLOSE_SESSION = 0x3,
    /* Global Task dynamically load secure applications */
    GLOBAL_CMD_ID_LOAD_SECURE_APP = 0x4,
    /* Global Task determine whether to load a secure application */
    GLOBAL_CMD_ID_NEED_LOAD_APP = 0x5,
    GLOBAL_CMD_ID_REGISTER_AGENT = 0x6,
    GLOBAL_CMD_ID_UNREGISTER_AGENT = 0x7,
    GLOBAL_CMD_ID_REGISTER_NOTIFY_MEMORY = 0x8,
    GLOBAL_CMD_ID_UNREGISTER_NOTIFY_MEMORY = 0x9,
    GLOBAL_CMD_ID_INIT_CONTENT_PATH = 0xa, /* Global Task init content path */
    /* Global Task free content path */
    GLOBAL_CMD_ID_TERMINATE_CONTENT_PATH = 0xb,
    GLOBAL_CMD_ID_ALLOC_EXCEPTION_MEM = 0xc,
    GLOBAL_CMD_ID_TEE_TIME = 0xd,
    GLOBAL_CMD_ID_TEE_INFO = 0xe,
    GLOBAL_CMD_ID_REGISTER_RDR_MEM = 0xf,
    GLOBAL_CMD_ID_KILL_TASK = 0x10,         /* Global Task Kill session */
    GLOBAL_CMD_ID_ADJUST_TIME = 0x12,        /* TIME adjust */
    GLOBAL_CMD_ID_SET_CA_HASH = 0x13,        /* set ca hash info */
    GLOBAL_CMD_ID_SET_BUILD_VERSION = 0x14,  /* set the build version */
    /* get session key for encrypting dialog */
    GLOBAL_CMD_ID_GET_SESSION_SECURE_PARAMS = 0x16,
    GLOBAL_CMD_ID_REGISTER_MAILBOX = 0x17,
    GLOBAL_CMD_ID_DUMP_MEMINFO = 0x1a,

    /* this cmd will be used to service no ca handle cmd */
    GLOBAL_CMD_ID_SET_SERVE_CMD = 0x1b,
    GLOBAL_CMD_ID_ADD_DYNAMIC_ION = 0x1c,
    GLOBAL_CMD_ID_DEL_DYNAMIC_ION = 0x1d,
    GLOBAL_CMD_ID_LOAD_SECURE_APP_ION = 0x1e,
    GLOBAL_CMD_ID_LATE_INIT = 0x20,
    GLOBAL_CMD_ID_GET_TEE_VERSION = 0x22,
    GLOBAL_CMD_ID_UNKNOWN = 0x7FFFFFFE,
    GLOBAL_CMD_ID_MAX = 0x7FFFFFFF
};

// Return Codes
enum TeecResult {
    TEEC_SUCCESS = 0x0,
    TEEC_ERROR_INVALID_CMD = 0x1,
    TEEC_ERROR_SERVICE_NOT_EXIST = 0x2,
    TEEC_ERROR_SESSION_NOT_EXIST = 0x3,
    TEEC_ERROR_SESSION_MAXIMUM,          /* security service session is full */
    TEEC_ERROR_REGISTER_EXIST_SERVICE,   /* register exist service */
    TEEC_ERROR_TAGET_DEAD_FATAL,         /* security service Global error，(Global is the basic of all services) */
    TEEC_ERROR_READ_DATA,                /* read file fail  */
    TEEC_ERROR_WRITE_DATA,               /* write file fail  */
    TEEC_ERROR_TRUNCATE_OBJECT,          /* trancate file fail  */
    TEEC_ERROR_SEEK_DATA,                /* seek file fail */
    TEEC_ERROR_RENAME_OBJECT,            /* renme file fail */
    TEEC_ERROR_TRUSTED_APP_LOAD_ERROR,   /* load security app fail */
    TEEC_ERROR_GENERIC = 0xFFFF0000,
    TEEC_ERROR_ACCESS_DENIED = 0xFFFF0001,
    TEEC_ERROR_CANCEL = 0xFFFF0002,
    TEEC_ERROR_ACCESS_CONFLICT = 0xFFFF0003,
    TEEC_ERROR_EXCESS_DATA = 0xFFFF0004,
    TEEC_ERROR_BAD_FORMAT = 0xFFFF0005,
    TEEC_ERROR_BAD_PARAMETERS = 0xFFFF0006,
    TEEC_ERROR_BAD_STATE = 0xFFFF0007,
    TEEC_ERROR_ITEM_NOT_FOUND = 0xFFFF0008,
    TEEC_ERROR_NOT_IMPLEMENTED = 0xFFFF0009,
    TEEC_ERROR_NOT_SUPPORTED = 0xFFFF000A,
    TEEC_ERROR_NO_DATA = 0xFFFF000B,
    TEEC_ERROR_OUT_OF_MEMORY = 0xFFFF000C,
    TEEC_ERROR_BUSY = 0xFFFF000D,
    TEEC_ERROR_COMMUNICATION = 0xFFFF000E,
    TEEC_ERROR_SECURITY = 0xFFFF000F,
    TEEC_ERROR_SHORT_BUFFER = 0xFFFF0010,
    TEEC_PENDING = 0xFFFF2000,
    TEEC_PENDING2 = 0xFFFF2001,
    TEE_ERROR_TAGET_DEAD = 0xFFFF3024,
    TEE_ERROR_GT_DEAD = 0xFFFF3124,
    TEEC_ERROR_MAC_INVALID = 0xFFFF3071,
    TEEC_CLIENT_INTR = 0xFFFF4000,
    TEEC_ERROR_CA_AUTH_FAIL = 0xFFFFCFE5,
    TEE_ERROR_AUDIT_FAIL = 0xFFFF9112,
};

// Return Code Origins
enum TEEC_ReturnCodeOrigin {
    TEEC_ORIGIN_API = 0x1,
    TEEC_ORIGIN_COMMS = 0x2,
    TEEC_ORIGIN_TEE = 0x3,
    TEEC_ORIGIN_TRUSTED_APP = 0x4,
    TEEC_ORIGIN_TRUSTED_APP_TUI = 0x5,
};

// Shared Memory Control
enum TEEC_SharedMemCtl {
    TEEC_MEM_INPUT = 0x1,
    TEEC_MEM_OUTPUT = 0x2,
    TEEC_MEM_INOUT = 0x3,
};

// API Parameter Types
enum TEEC_ParamType {
    TEEC_NONE = 0x0,
    TEEC_VALUE_INPUT = 0x01,
    TEEC_VALUE_OUTPUT = 0x02,
    TEEC_VALUE_INOUT = 0x03,
    TEEC_MEMREF_TEMP_INPUT = 0x05,
    TEEC_MEMREF_TEMP_OUTPUT = 0x06,
    TEEC_MEMREF_TEMP_INOUT = 0x07,
    TEEC_ION_INPUT = 0x08,
    TEEC_ION_SGLIST_INPUT = 0x09,
    TEEC_MEMREF_WHOLE = 0xc,
    TEEC_MEMREF_PARTIAL_INPUT = 0xd,
    TEEC_MEMREF_PARTIAL_OUTPUT = 0xe,
    TEEC_MEMREF_PARTIAL_INOUT = 0xf
};

enum TEE_ParamType {
    TEE_PARAM_TYPE_NONE = 0x0,
    TEE_PARAM_TYPE_VALUE_INPUT = 0x1,
    TEE_PARAM_TYPE_VALUE_OUTPUT = 0x2,
    TEE_PARAM_TYPE_VALUE_INOUT = 0x3,
    TEE_PARAM_TYPE_MEMREF_INPUT = 0x5,
    TEE_PARAM_TYPE_MEMREF_OUTPUT = 0x6,
    TEE_PARAM_TYPE_MEMREF_INOUT = 0x7,
    TEE_PARAM_TYPE_ION_INPUT = 0x8,
    TEE_PARAM_TYPE_ION_SGLIST_INPUT = 0x9,
};

// Session Login Methods
enum TEEC_LoginMethod {
    TEEC_LOGIN_PUBLIC = 0x0,
    TEEC_LOGIN_USER,
    TEEC_LOGIN_GROUP,
    TEEC_LOGIN_APPLICATION = 0x4,
    TEEC_LOGIN_USER_APPLICATION = 0x5,
    TEEC_LOGIN_GROUP_APPLICATION = 0x6,
    TEEC_LOGIN_IDENTIFY = 0x7,
};

#endif
