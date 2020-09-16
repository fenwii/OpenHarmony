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

#include "commonutil.h"
#include <securec.h>
#include "base.h"
#include "log.h"
#include "mem_stat.h"
#include "hichain.h"

char hex_to_char(uint8_t hex)
{
    return (hex > 9) ? hex + 0x37 : hex + 0x30; /* Convert to the corresponding character */
}

void byte_to_hex_string(const uint8_t *hex, int32_t hex_len, uint8_t *buf, int32_t buf_len)
{
    if (buf_len < hex_len * BYTE_TO_HEX_OPER_LENGTH) {
        return;
    }
    for (int32_t i = 0; i < hex_len; i++) {
        buf[i * BYTE_TO_HEX_OPER_LENGTH] = hex_to_char((hex[i] & 0xF0) >> 4); /* shift right for filling */
        buf[i * BYTE_TO_HEX_OPER_LENGTH + 1] = hex_to_char(hex[i] & 0x0F); /* get low four bits */
    }
}

int32_t hex_string_to_byte(const char *str, int32_t len, uint8_t *hex)
{
    if (len % BYTE_TO_HEX_OPER_LENGTH) { /* even number or not */
        LOGE("Length is not even number");
        return HC_INPUT_ERROR;
    }

    int32_t hex_len = len / BYTE_TO_HEX_OPER_LENGTH; /* Halve the length */
    uint8_t nibble[BYTE_TO_HEX_OPER_LENGTH]; /* create array */

    for (int32_t i = 0; i < hex_len; i++) {
        nibble[0] = str[i * BYTE_TO_HEX_OPER_LENGTH]; /* hex conversion */
        nibble[1] = str[i * BYTE_TO_HEX_OPER_LENGTH + 1]; /* hex conversion */
        for (int32_t j = 0; j < BYTE_TO_HEX_OPER_LENGTH; j++) { /* iterate through array */
            if ((nibble[j] <= 'F') && (nibble[j] >= 'A')) {
                nibble[j] = nibble[j] - 'A' + 10; /* decimal conversion */
            } else if ((nibble[j] <= 'f') && (nibble[j] >= 'a')) {
                nibble[j] = nibble[j] - 'a' + 10; /* decimal conversion */
            } else if ((nibble[j] >= '0') && (nibble[j] <= '9')) {
                nibble[j] = nibble[j] - '0';
            } else {
                LOGE("Message is invalid");
                return HC_INPUT_ERROR;
            }
        }
        hex[i] = nibble[0] << 4; /* Set the high nibble */
        hex[i] |= nibble[1]; /* Set the low nibble */
    }
    return HC_OK;
}

void print_bytes(uint8_t *buf, int32_t buf_len)
{
    int32_t tmp_data_hex_len = buf_len * BYTE_TO_HEX_OPER_LENGTH + sizeof("");
    uint8_t *tmp_data_hex = (uint8_t *)MALLOC(tmp_data_hex_len);
    if (tmp_data_hex == NULL) {
        LOGE("Malloc failed");
        return;
    }
    (void)memset_s(tmp_data_hex, tmp_data_hex_len, 0, tmp_data_hex_len);
    byte_to_hex_string(buf, buf_len, tmp_data_hex, buf_len * BYTE_TO_HEX_OPER_LENGTH);
    DBG_OUT("PrintBytes:%s", (char *)tmp_data_hex);
    FREE(tmp_data_hex);
}

int32_t byte_convert(json_pobject obj, const char *field, uint8_t *hex, uint32_t *length, uint32_t max_len)
{
    const char *str_json = get_json_string(obj, field);
    if (str_json == NULL) {
        return HC_INPUT_ERROR;
    }

    uint32_t len = strlen(str_json);
    if ((len / BYTE_TO_HEX_OPER_LENGTH) > max_len) {
        return HC_INPUT_ERROR;
    }
    if (hex_string_to_byte(str_json, len, hex) != HC_OK) {
        return HC_INPUT_ERROR;
    }
    *length = len / BYTE_TO_HEX_OPER_LENGTH;
    return HC_OK;
}

int32_t string_convert(json_pobject obj, const char *field, uint8_t *str, uint32_t *length, uint32_t max_len)
{
    const char *str_json = get_json_string(obj, field);
    if (str_json == NULL) {
        return HC_INPUT_ERROR;
    }

    uint32_t len = strlen(str_json);
    if (len > max_len) {
        return HC_INPUT_ERROR;
    }
    if (memcpy_s(str, max_len, str_json, len) != EOK) {
        return memory_copy_error(__func__, __LINE__);
    }
    *length = len;
    return HC_OK;
}

void hex_string_convert(uint32_t length, const uint8_t *hex, const char *field, json_pobject parent)
{
    int32_t org_cha_len = length;
    int32_t tmp_cha_data_hex_len = org_cha_len * BYTE_TO_HEX_OPER_LENGTH + 1;
    uint8_t *tmp_cha_data_hex = (uint8_t *)MALLOC(tmp_cha_data_hex_len);

    if (tmp_cha_data_hex == NULL) {
        return;
    }
    (void)memset_s(tmp_cha_data_hex, tmp_cha_data_hex_len, 0, tmp_cha_data_hex_len);
    byte_to_hex_string(hex, org_cha_len, tmp_cha_data_hex, org_cha_len * BYTE_TO_HEX_OPER_LENGTH);
    add_string_to_object(parent, field, (char *)tmp_cha_data_hex);
    FREE(tmp_cha_data_hex);
    tmp_cha_data_hex = NULL;
}

int32_t memory_copy_error(const char *fun, unsigned int line)
{
    (void)fun;
    (void)line;
    LOGE("memory copy error in fun:%s line:%u", fun, line);
    return HC_MEMCPY_ERROR;
}

