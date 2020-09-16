/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

#ifndef __TRANSFER_H__
#define __TRANSFER_H__

#include <ymodem.h>
#include <hi_boot_rom.h>
#include <efuse_opt.h>
#include <load.h>

#define MODEM_SOH                   0x01 /* Start character of data block */
#define MODEM_STX                   0x02 /* The start byte of 1024 bytes */
#define MODEM_EOT                   0x04 /* File transfer finish */
#define MODEM_ACK                   0x06 /* ACK message */
#define MODEM_NAK                   0x15 /* Error occurred */
#define MODEM_CAN                   0x18 /* Cancel transmission */
#define MODEM_EOF                   0x1A /* Data blank filler */
#define MODEM_C                     0x43 /* Capital letter C */

#define FLASH_ADDR_OFFSET           0x400000

#define UPLOAD_WAIT_START_C_TIME    10000000 /* 10s */
#define UPLOAD_WAIT_DEFAULT_TIME    2000000  /* 2s */

#define UPLOAD_DATA_SIZE            1024
#define UPLOAD_BUFF_LEN             1029

#define RETRY_COUNT                 0
#define CAN_COUNT                   3
#define MSG_START_LEN               3
#define SOH_MSG_LEN                 128
#define SOH_MSG_TOTAL_LEN           133
#define WAIT_ZERO_ACK_DELAY         100
#define UPLOAD_FILE_NAME            "upload.bin"
#define UPLOAD_FILE_NAME_LEN        11

enum {
    UPLOAD_NONE,
    UPLOAD_WAIT_START_C,
    UPLOAD_WAIT_INIT_ACK,
    UPLOAD_WAIT_TRANS_C,
    UPLOAD_WAIT_INTER_ACK,
    UPLOAD_WAIT_FINAL_ACK,
    UPLOAD_WAIT_EOT_C,
    UPLOAD_WAIT_ZERO_ACK,
};

typedef struct {
    uintptr_t file_addr;
    hi_u32 file_length;
    hi_char *file_name;
    hi_u32 offset;
    hi_u8 status;
    hi_u8 seq;
    hi_u8 retry : 4;
    hi_u8 can_cnt : 4;
    hi_u8 buffer[UPLOAD_BUFF_LEN];
} upload_context;

hi_u32 download_image(hi_u32 addr, hi_u32 erase_size, hi_u32 flash_size, hi_u8 burn_efuse);
hi_u32 download_factory_image(hi_u32 addr, hi_u32 erase_size, hi_u32 flash_size, hi_u8 burn_efuse);
hi_u32 loady_file(uintptr_t ram_addr);
hi_u32 loady_version_file(uintptr_t ram_addr);
hi_u32 upload_data(hi_u32 addr, hi_u32 length);

#endif
