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

#include "tc_ns_client.h"
#include "tee_client_type.h"
#include "tee_client_inner.h"

#ifndef LIBTEEC_TEE_CLIENT_APP_LOAD_H
#define LIBTEEC_TEE_CLIENT_APP_LOAD_H

#define MAX_FILE_PATH_LEN 20
#define MAX_FILE_NAME_LEN 40
#define MAX_FILE_EXT_LEN  6

#define MAX_IMAGE_LEN          0x800000 /* max image len */

#define TA_HEAD_MAGIC1         0xA5A55A5A
#define TA_HEAD_MAGIC2         0x55AA
#define NUM_OF_RESERVED_BITMAP 16

enum TA_VERSION {
    TA_SIGN_VERSION        = 1, /* first version */
    TA_RSA2048_VERSION     = 2, /* use rsa 2048, and use right crypt mode */
    CIPHER_LAYER_VERSION   = 3,
    CONFIG_SEGMENT_VERSION = 4,
    TA_SIGN_VERSION_MAX
};

typedef struct {
    uint32_t context_len;         /* manifest_crypto_len + cipher_bin_len */
    uint32_t manifest_crypto_len; /* manifest crypto len */
    uint32_t manifest_plain_len;  /* manfiest str + manifest binary */
    uint32_t manifest_str_len;    /* manifest str len */
    uint32_t cipher_bin_len;      /* cipher elf len */
    uint32_t sign_len;            /* sign file len, now rsa 2048 this len is 256 */
} TEEC_image_head;

typedef struct {
    uint32_t magic_num1;
    uint16_t magic_num2;
    uint16_t version_num;
} TEEC_image_identity;

typedef struct {
    TEEC_image_identity img_identity;
    uint32_t context_len;
    uint32_t ta_key_version;
} ta_image_hdr_v3_t;

typedef struct {
    TEEC_image_head img_hd;
    TEEC_image_identity img_identity;
    uint8_t reserved[NUM_OF_RESERVED_BITMAP];
} TEEC_TA_HEAD;

int32_t TEEC_GetApp(const TaFileInfo *taFile, const TEEC_UUID *srvUuid, TC_NS_ClientContext *cliContext);
int32_t TEEC_LoadSecfile(const char *filePath, int tzFd, FILE *fp);

#endif
