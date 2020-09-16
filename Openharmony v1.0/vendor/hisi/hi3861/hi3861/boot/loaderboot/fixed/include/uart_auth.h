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

#ifndef __UART_AUTH_H__
#define __UART_AUTH_H__

#include <secure.h>
#include "hi_boot_rom.h"
#include <hi_types.h>

#define UART_PACKET_START_FLAG 0xDEADBEEF

#define UART_PACKET_PAYLOAD_MAX 1024

HI_EXTERN uart_param_stru g_uart_param;
HI_EXTERN hi_u32 g_uart_int_type;

enum {
    UART_TYPE_ROMBOOT_HANDSHAKE = 0xF0,
    UART_TYPE_ACK = 0xE1,
    UART_TYPE_FILE_START = 0xD2,
    UART_TYPE_FILE_END = 0xC3,
    UART_TYPE_CMD = 0xB4,
    UART_TYPE_DATA = 0xA5,
    UART_TYPE_FLASHBOOT_HANDSHAKE = 0x0F,
};

typedef struct {
    hi_u32 start_flag;  /* start flag: 0xDEADBEEF */
    hi_u16 packet_size; /* Packet length: actual length of data to be transmitted.
                           The length cannot exceed 1024 bytes.
                           CNcomment:报文长度：真实传输数据长度，要求不超过1024 */
    hi_u8 type;         /* Packet Type。CNcomment：报文类型 */
    hi_u8 pad;
} packet_data_head;

typedef struct {
    packet_data_head head;
    hi_u8 payload[UART_PACKET_PAYLOAD_MAX]; /**< Packet data */
    hi_u16 check_sum;   /* Checksum */
    hi_u8 rev[2];       /* 2: rev */
} packet_data_info;

/* UART AUTH context */
typedef struct {
    hi_u8 status;
    hi_u8 pad;
    hi_u16 received;
    packet_data_info packet;
} uart_ctx;

hi_u32 uart_process(hi_uart uart, hi_u32 interrupt_timeout_ms);

#endif /* __UART_AUTH_H__ */
