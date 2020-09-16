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

#include "key_agreement_version.h"
#include <securec.h>
#include "log.h"
#include "mem_stat.h"
#include "jsonutil.h"
#include "commonutil.h"
#include "base.h"
#include "parsedata.h"

static void split_ver(char *tmp_ver, const char *sub_ver, struct key_agreement_version *cur_ver, char *next)
{
    sub_ver = strtok_s(tmp_ver, ".", &next);
    if (sub_ver != NULL) {
        cur_ver->first = strtoul(sub_ver, NULL, HC_VERSION_DEC); /* first */
    }
    sub_ver = strtok_s(NULL, ".", &next);
    if (sub_ver != NULL) {
        cur_ver->second = strtoul(sub_ver, NULL, HC_VERSION_DEC); /* second */
    }
    sub_ver = strtok_s(NULL, ".", &next);
    if (sub_ver != NULL) {
        cur_ver->third = strtoul(sub_ver, NULL, HC_VERSION_DEC); /* third */
    }
}

bool parse_version(json_pobject obj_ver, struct key_agreement_version *min_ver, struct key_agreement_version *cur_ver)
{
    const char *str_cur_ver = get_json_string(obj_ver, FIELD_CURRENT_VERSION); /* version---cur */
    if (str_cur_ver == NULL) {
        return false;
    }
    char *sub_cur_ver = NULL;
    char *next = NULL;
    int32_t len_cur_ver = strlen(str_cur_ver);
    char *tmp_cur_ver = (char *)MALLOC(len_cur_ver + 1);
    if (tmp_cur_ver == NULL) {
        return false;
    }
    (void)memset_s(tmp_cur_ver, len_cur_ver + 1, 0, len_cur_ver + 1);
    if (strcpy_s(tmp_cur_ver, len_cur_ver + 1, str_cur_ver) != EOK) {
        FREE(tmp_cur_ver);
        tmp_cur_ver = NULL;
        return false;
    }
    split_ver(tmp_cur_ver, sub_cur_ver, min_ver, next);
    FREE(tmp_cur_ver);
    tmp_cur_ver = NULL;

    const char *str_min_ver = get_json_string(obj_ver, FIELD_MIN_VERSION); /* version---min */
    if (str_min_ver == NULL) {
        return false;
    }
    char *sub_min_ver = NULL;
    int32_t len_min_ver = strlen(str_min_ver);
    char *tmp_min_ver = (char *)MALLOC(len_min_ver + 1);
    if (tmp_min_ver == NULL) {
        return false;
    }
    (void)memset_s(tmp_min_ver, len_min_ver + 1, 0, len_min_ver + 1);
    if (strcpy_s(tmp_min_ver, len_min_ver + 1, str_min_ver) != EOK) {
        FREE(tmp_min_ver);
        tmp_min_ver = NULL;
        return false;
    }
    split_ver(tmp_min_ver, sub_min_ver, cur_ver, next);
    FREE(tmp_min_ver);
    tmp_min_ver = NULL;
    return true;
}

uint8_t *raw_byte_to_hex_string(const uint8_t *hex, int32_t length)
{
    int32_t tmp_hex_len = length * BYTE_TO_HEX_OPER_LENGTH + sizeof("");
    uint8_t *tmp_cha_data_hex = (uint8_t *)MALLOC(tmp_hex_len);
    if (tmp_cha_data_hex == NULL) {
        return NULL;
    }
    (void)memset_s(tmp_cha_data_hex, tmp_hex_len, 0, tmp_hex_len);
    byte_to_hex_string(hex, length, tmp_cha_data_hex, length * BYTE_TO_HEX_OPER_LENGTH);
    return tmp_cha_data_hex;
}
