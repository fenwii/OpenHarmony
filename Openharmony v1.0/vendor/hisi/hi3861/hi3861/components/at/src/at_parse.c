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

#include <hi_stdlib.h>
#include <at.h>
#include <at_parse.h>
#include "hi_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

hi_u32 at_param_shift(const hi_char *cmd_in, hi_char *cmd_out, hi_u32 size)
{
    hi_char *output = (hi_char *)NULL;
    hi_char *out_bak = (hi_char *)NULL;
    hi_u32 len = size;
    hi_s32 ret;

    if ((cmd_in == NULL) || (cmd_out == NULL)) {
        at_printf("cmd_in and cmd_out = NULL in %s[%d]", __FUNCTION__, __LINE__);
        return HI_ERR_FAILURE;
    }

    output = (hi_char *)hi_malloc(HI_MOD_ID_SAL_DFX, len);
    if (output == NULL) {
        at_printf("malloc failure in %s[%d]", __FUNCTION__, __LINE__);
        return HI_ERR_FAILURE;
    }
    /* Backup the 'output' start address */
    out_bak = output;
    /* Scan each charactor in 'cmd_in',and squeeze the overmuch space and ignore invaild charactor */
    for (; *cmd_in != '\0'; cmd_in++) {
        if ((*cmd_in == '\\') && ((*(cmd_in + 1) == '\"') || (*(cmd_in + 1) == ','))) {
            continue;
        }
        *output = *cmd_in;
        output++;
    }
    *output = '\0';
    /* Restore the 'pscOutput' start address */
    output = out_bak;
    len = strlen(output);

    /* Copy out the buffer which is been operated already */
    ret = strncpy_s(cmd_out, size, output, len);
    if (ret != EOK) {
        at_printf("%s,%d strncpy_s failed, err:%d!\n", __FUNCTION__, __LINE__, ret);
        hi_free(HI_MOD_ID_SAL_DFX, out_bak);
        return HI_ERR_FAILURE;
    }
    cmd_out[len] = '\0';

    hi_free(HI_MOD_ID_SAL_DFX, out_bak);

    return HI_ERR_SUCCESS;
}

hi_u32 cmd_parse_para_get(hi_u32 *value, hi_char *para_token_str)
{
    if ((para_token_str == NULL) || (value == NULL)) {
        return HI_ERR_FAILURE;
    }
    hi_u32 ret;
    hi_u32 value_in_len;
    hi_char *value_in = HI_NULL;

    value_in_len = strlen(para_token_str) + 1;
    value_in = (hi_char *)hi_malloc(HI_MOD_ID_SAL_DFX, value_in_len);
    if (value_in == HI_NULL) {
        at_printf("%s,%d hi_malloc failed!\n", __FUNCTION__, __LINE__);
        return HI_ERR_FAILURE;
    }

    memset_s(value_in, value_in_len, 0, value_in_len);

    ret = (hi_u32)strncpy_s(value_in, value_in_len, para_token_str, strlen(para_token_str));
    if (ret != EOK) {
        at_printf("%s,%d strncpy_s failed, err:%d!\n", __FUNCTION__, __LINE__, ret);
        hi_free(HI_MOD_ID_SAL_DFX, value_in);
        return HI_ERR_FAILURE;
    }

    ret = at_param_shift(value_in, para_token_str, value_in_len);
    if (ret != HI_ERR_SUCCESS) {
        at_printf("%s,%d at_param_shift failed, err:%d!\n", __FUNCTION__, __LINE__, ret);
        hi_free(HI_MOD_ID_SAL_DFX, value_in);
        return HI_ERR_FAILURE;
    }
    *value = (hi_u32)(uintptr_t)para_token_str;

    hi_free(HI_MOD_ID_SAL_DFX, value_in);
    return HI_ERR_SUCCESS;
}

hi_u32 cmd_parse_one_token(at_cmd_attr *cmd_parsed, hi_u32 index, hi_char *token)
{
    hi_u32 ret = HI_ERR_SUCCESS;

    if (cmd_parsed == NULL) {
        return HI_ERR_FAILURE;
    }

    if (index == 0) {
        if (cmd_parsed->at_cmd_type != AT_CMD_TYPE_SETUP) {
            return ret;
        }
    }

    if (index >= AT_CMD_MAX_PARAS) {
        return HI_ERR_FAILURE;
    }

    if (token[0] == '\0') {
        hi_u32 len = cmd_parsed->at_param_cnt;
        cmd_parsed->param_array[len] = NULL;
        cmd_parsed->at_param_cnt++;
        return ret;
    }

    if (cmd_parsed->at_param_cnt < AT_CMD_MAX_PARAS) {
        hi_u32 len = cmd_parsed->at_param_cnt;
        ret = cmd_parse_para_get(&(cmd_parsed->param_array[len]), token);
        if (ret != HI_ERR_SUCCESS) {
            return ret;
        }
        cmd_parsed->at_param_cnt++;
    }

    return ret;
}

hi_u32 at_cmd_token_split(hi_char *cmd, hi_char split, at_cmd_attr *cmd_parsed)
{
    enum {
        STAT_INIT,
        STAT_TOKEN_IN,
        STAT_TOKEN_OUT
    } state = STAT_INIT;

    hi_char *token = NULL;
    hi_char *p = NULL;
    hi_u32 count = 0;
    hi_u32 ret = HI_ERR_SUCCESS;

    if (cmd == NULL) {
        return HI_ERR_FAILURE;
    }

    token = cmd;

    for (p = cmd; (*p != '\0') && (ret == HI_ERR_SUCCESS); p++) {
        if (state == STAT_TOKEN_OUT) {
            token = p;
            state = STAT_TOKEN_IN;
        }

        if (state == STAT_INIT || state == STAT_TOKEN_IN) {
            if ((*p == split) && (*(p - 1) != '\\')) {
                *p = '\0';
                ret = cmd_parse_one_token(cmd_parsed, count++, token);
                state = STAT_TOKEN_OUT;
            }
        }
    }

    if (*(p - 1) == '\0') {
        token = p;
    }
    if ((ret == HI_ERR_SUCCESS) || (state == STAT_INIT)) {
        ret = cmd_parse_one_token(cmd_parsed, count, token);
    }

    return ret;
}

hi_u32 at_para_parse(hi_char *cmd_line, at_cmd_attr *cmd_parsed)
{
    if ((cmd_line == NULL) || (cmd_parsed == NULL) || (strlen(cmd_line) == 0)) {
        return HI_ERR_FAILURE;
    }

    return at_cmd_token_split(cmd_line, ',', cmd_parsed);
}

hi_u32 at_cmd_parse(hi_char *cmd_line, at_cmd_attr *cmd_parsed)
{
    hi_u32 ret;
    if (cmd_line == HI_NULL || cmd_parsed == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    cmd_line += cmd_parsed->at_cmd_len;
    at_printf("at_cmd_parse line %d: cmd_line = %s\n", __LINE__, cmd_line);
    if (*cmd_line == '\0') {
        cmd_parsed->at_cmd_type = AT_CMD_TYPE_EXE;
    } else if (*cmd_line == '?' && (cmd_line[1] == '\0')) {
        cmd_parsed->at_cmd_type = AT_CMD_TYPE_QUERY;
    } else if ((*cmd_line == '=') && (cmd_line[1] == '?') && (cmd_line[2] == '\0')) { /* 2: the third character */
        cmd_parsed->at_cmd_type = AT_CMD_TYPE_TEST;
    } else if ((*cmd_line == '=') && (cmd_line[1] != '?')) {
        cmd_parsed->at_cmd_type = AT_CMD_TYPE_SETUP;

        if (cmd_line[1] != '\0') {
            ret = at_para_parse(cmd_line + 1, cmd_parsed);
            if (ret != HI_ERR_SUCCESS) {
                return ret;
            }
        }
    }

    return HI_ERR_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif