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

#ifndef __AT_H__
#define __AT_H__

#include <hi_at.h>
#include <hi_early_debug.h>
#include <hi_mem.h>
#include <hi_stdlib.h>
#include <hi_types_base.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define AT_CMD_MAX_PARAS 64
#define AT_CMD_MAX_LEN   128
#define AT_CMD_LIST_NUM  20

#define AT_RESPONSE_OK              do {                      \
                                        hi_at_printf("OK\r\n");     \
                                    } while (0)

#define AT_RESPONSE_ERROR           do {                      \
                                        hi_at_printf("ERROR\r\n");  \
                                    } while (0)

#define AT_ENTER                    do {                      \
                                        hi_at_printf("\r\n");       \
                                    } while (0)

#ifdef AT_CMD_DEBUG
#define at_printf(fmt...)  printf(fmt)
#else
#define at_printf(fmt...)
#endif

#define AT_MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#define at_mac2str(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]


typedef enum {
    AT_CMD_TYPE_TEST   = 1,
    AT_CMD_TYPE_QUERY  = 2,
    AT_CMD_TYPE_SETUP  = 3,
    AT_CMD_TYPE_EXE = 4,
} at_cmd_type;

typedef struct {
    hi_s8 at_cmd_len;
    hi_char cmd_name[AT_CMD_MAX_LEN];
    at_cmd_type at_cmd_type;
    hi_s32 at_param_cnt;                  /* command actual para num  */
    hi_u32 param_array[AT_CMD_MAX_PARAS];
} at_cmd_attr;

typedef struct {
    HI_CONST at_cmd_func *at_cmd_list[AT_CMD_LIST_NUM];     /* user input at cmd list */
    hi_u16 at_cmd_num[AT_CMD_LIST_NUM];                     /* command number */
} at_cmd_func_list;

extern at_cmd_ctrl g_at_ctrl;

hi_u32 at_cmd_process(const hi_char *at_cmd_line);
hi_u32 at_param_null_check(hi_s32 argc, const hi_char **argv);
hi_u32 integer_check(const hi_char *val);
hi_u32 cmd_strtoaddr(const hi_char *param, hi_uchar *mac_addr, hi_u32 addr_len);
char* at_parse_string(const char *value, size_t *len);
const char* at_ssid_txt(const hi_u8 *ssid, size_t ssid_len);
void* at_malloc(size_t size);
void at_free(char *ptr);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif
