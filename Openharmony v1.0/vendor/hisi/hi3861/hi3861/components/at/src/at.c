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
#include <at_cmd.h>
#include <at_parse.h>
#include "hi_config.h"

#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "stdarg.h"
#include "securec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define AT_SSID_MAX_LEN 32

at_cmd_ctrl g_at_ctrl = {
    .at_state = AT_IDLE,
    .send_len = 0,
    .trans_len = 0,
    .is_first_recv_data = HI_TRUE,
    .is_first_over_data = HI_TRUE,
    .is_recv_end_char_flag = 0,
};

hi_u32 at_cmd_excute(const at_cmd_func *cmd_func, at_cmd_attr *cmd_parsed)
{
    hi_u32 ret;

    if (cmd_func == HI_NULL || cmd_parsed == HI_NULL) {
        return HI_ERR_FAILURE;
    }

    if (cmd_parsed->at_cmd_type == AT_CMD_TYPE_TEST) {
        if (cmd_func->at_test_cmd) {
            ret = cmd_func->at_test_cmd((hi_s32)cmd_parsed->at_param_cnt,
                (const hi_char **)&cmd_parsed->param_array[0]);
        } else {
            at_printf("COMMAND TYPE NOT SUPPORT!\r\n");
            ret = HI_ERR_FAILURE;
            at_printf("err at %s line: %d\n", __FUNCTION__, __LINE__);
        }
    } else if (cmd_parsed->at_cmd_type == AT_CMD_TYPE_QUERY) {
        if (cmd_func->at_query_cmd) {
            ret = cmd_func->at_query_cmd((hi_s32)cmd_parsed->at_param_cnt,
                (const hi_char **)&cmd_parsed->param_array[0]);
        } else {
            at_printf("COMMAND TYPE NOT SUPPORT!\r\n");
            ret = HI_ERR_FAILURE;
            at_printf("err at %s line: %d\n", __FUNCTION__, __LINE__);
        }
    } else if (cmd_parsed->at_cmd_type == AT_CMD_TYPE_SETUP) {
        if (cmd_func->at_setup_cmd) {
            ret = cmd_func->at_setup_cmd((hi_s32)cmd_parsed->at_param_cnt,
                (const hi_char **)&cmd_parsed->param_array[0]);
        } else {
            at_printf("COMMAND TYPE NOT SUPPORT!\r\n");
            ret = HI_ERR_FAILURE;
            at_printf("err at %s line: %d\n", __FUNCTION__, __LINE__);
        }
    } else if (cmd_parsed->at_cmd_type == AT_CMD_TYPE_EXE) {
        if (cmd_func->at_exe_cmd) {
            ret = cmd_func->at_exe_cmd((hi_s32)cmd_parsed->at_param_cnt,
                (const hi_char **)&cmd_parsed->param_array[0]);
        } else {
            at_printf("COMMAND TYPE NOT SUPPORT!\r\n");
            ret = HI_ERR_FAILURE;
            at_printf("err at %s line: %d\n", __FUNCTION__, __LINE__);
        }
    } else {
        at_printf("COMMAND TYPE NOT SUPPORT!\r\n");
        ret = HI_ERR_FAILURE;
        at_printf("err at %s line: %d\n", __FUNCTION__, __LINE__);
    }

    return ret;
}

static hi_void at_get_cmd_name(hi_char *cmd_line, at_cmd_attr *cmd_parsed)
{
    hi_s8 n = 0;

    for (hi_u8 i = AT_CMD_MAX_LEN; i > 0; i--) {
        if ((*cmd_line == '\0') || (*cmd_line == '=') || (*cmd_line == '?')) {
            cmd_parsed->at_cmd_len = n;
            return;
        } else {
            cmd_parsed->cmd_name[n] = *cmd_line;
            cmd_line++;
            n++;
        }
    }

    cmd_parsed->at_cmd_len = -1;
    memset_s(cmd_parsed->cmd_name, AT_CMD_MAX_LEN, 0, AT_CMD_MAX_LEN);
}

hi_u32 at_func_process(hi_char *out_cmd_line, at_cmd_attr *cmd_parsed)
{
    hi_u32 ret;
    at_cmd_func *cmd_func = HI_NULL;
    at_get_cmd_name(out_cmd_line, cmd_parsed);
    if (cmd_parsed->at_cmd_len != (-1)) {
        cmd_func = at_find_proc_func(cmd_parsed);
    }

    if (cmd_func != HI_NULL) {
        ret = at_cmd_parse(out_cmd_line, cmd_parsed);
        if (ret != HI_ERR_SUCCESS) {
            at_printf("%s line: %d PARSE CMD FAIL!\r\n", __FUNCTION__, __LINE__);
            return ret;
        }

        ret = at_cmd_excute(cmd_func, cmd_parsed);
    } else {
        ret = HI_ERR_FAILURE;
        at_printf("%s line: %d COMMAND NOT SUPPORT!\r\n", __FUNCTION__, __LINE__);
    }

    return ret;
}

hi_u32 at_cmd_process(const hi_char *at_cmd_line)
{
    hi_u32 at_cmd_line_len;
    hi_char *out_cmd_line = HI_NULL;
    at_cmd_attr cmd_parsed = {0};
    hi_u32 ret;

    AT_ENTER;
    if (at_cmd_line == HI_NULL) {
        at_printf("INVALID NULL CMD!\r\n");
        AT_RESPONSE_ERROR;
        return HI_ERR_FAILURE;
    }

    at_cmd_line_len = (hi_u32)strlen(at_cmd_line) + 1;
    out_cmd_line = (hi_char *)hi_malloc(HI_MOD_ID_SAL_DFX, at_cmd_line_len);
    if (out_cmd_line == HI_NULL) {
        at_printf("%s line%d NO ENOUGH MEMORY!\r\n", __FUNCTION__, __LINE__);
        AT_RESPONSE_ERROR;
        return HI_ERR_FAILURE;
    }
    memset_s(out_cmd_line, at_cmd_line_len, 0, at_cmd_line_len);

    ret = (hi_u32)strncpy_s(out_cmd_line, at_cmd_line_len, at_cmd_line, at_cmd_line_len - 1);
    if (ret != EOK) {
        at_printf("%s,%d strncpy_s failed, err:%d!\n", __FUNCTION__, __LINE__, ret);
        AT_RESPONSE_ERROR;
        hi_free(HI_MOD_ID_SAL_DFX, out_cmd_line);
        return HI_ERR_FAILURE;
    }
    out_cmd_line[at_cmd_line_len - 1] = '\0';

    ret = at_func_process(out_cmd_line, &cmd_parsed);
    if (ret != HI_ERR_SUCCESS && ret != HI_ERR_RECVING) {
        at_printf("err at %s line: %d\n", __FUNCTION__, __LINE__);
        AT_RESPONSE_ERROR;
    } else if (ret == HI_ERR_RECVING) {
        g_at_ctrl.at_state = AT_DATA_RECVING;
    } else {
        g_at_ctrl.at_state = AT_IDLE;
    }

    hi_free(HI_MOD_ID_SAL_DFX, out_cmd_line);
    out_cmd_line = HI_NULL;

    return ret;
}

hi_u32 at_param_null_check(hi_s32 argc, const hi_char **argv)
{
    for (hi_s32 i = 0; i < argc; i++) {
        if (argv[i] == HI_NULL) {
            return HI_ERR_FAILURE;
        }
    }
    return HI_ERR_SUCCESS;
}

hi_u32 integer_check(const hi_char *val)
{
    hi_u32 len;
    hi_u32 i;
    hi_char *buf = (hi_char *)val;
    if (buf == HI_NULL) {
        return HI_ERR_FAILURE;
    }
    len = strlen(buf);
    if ((*buf == '0') && (len != 1)) {
        return HI_ERR_FAILURE;
    }
    for (i = 0; i < len; i++) {
        if ((*buf < '0') || (*buf > '9')) {
            return HI_ERR_FAILURE;
        }
        buf++;
    }
    return HI_ERR_SUCCESS;
}

static hi_u32 at_check_mac_elem(const hi_char elem)
{
    if (elem >= '0' && elem <= '9') {
        return HI_ERR_SUCCESS;
    } else if (elem >= 'A' && elem <= 'F') {
        return HI_ERR_SUCCESS;
    } else if (elem >= 'a' && elem <= 'f') {
        return HI_ERR_SUCCESS;
    } else if (elem == ':') {
        return HI_ERR_SUCCESS;
    }

    return HI_ERR_FAILURE;
}

hi_u32 cmd_strtoaddr(const hi_char *param, hi_uchar *mac_addr, hi_u32 addr_len)
{
    hi_u32 cnt;
    hi_char *tmp1 = (hi_char *)param;
    hi_char *tmp2 = NULL;
    hi_char *tmp3 = NULL;

    for (cnt = 0; cnt < 17; cnt++) {    /* 17 */
        if (at_check_mac_elem(param[cnt]) != HI_ERR_SUCCESS) {
            return HI_ERR_FAILURE;
        }
    }

    for (cnt = 0; cnt < (addr_len - 1); cnt++) {
        tmp2 = (char*)strsep(&tmp1, ":");
        if (tmp2 == NULL) {
            return HI_ERR_APP_INVALID_PARAMETER;
        }
        mac_addr[cnt] = (hi_uchar)strtoul(tmp2, &tmp3, 16); /* 16 */
    }

    if (tmp1 == NULL) {
        return HI_ERR_APP_INVALID_PARAMETER;
    }
    mac_addr[cnt] = (hi_uchar)strtoul(tmp1, &tmp3, 16); /* 16 */
    return HI_ERR_SUCCESS;
}

char *at_strrchr(const char *src, int c)
{
    return strrchr(src, c);
}

void *at_malloc(size_t size)
{
    if (size > 4096) {  /* max alloc mem 4096 */
        return NULL;
    }
    void *ptr = malloc(size);
    return ptr;
}

void at_free(char *ptr)
{
    if (ptr) {
        free(ptr);
    }
}

size_t at_strlen(const char *src)
{
    return strlen(src);
}

int at_pading(char *str, size_t size, const char *format, ...)
{
    va_list ap = NULL;
    int ret;

    va_start(ap, format);
    ret = vsnprintf_s(str, AT_SSID_MAX_LEN * 4 + 1, size, format, ap); /* 4 length */
    va_end(ap);
    if (size > 0) {
        str[size - 1] = '\0';
    }
    return ret;
}

char* at_dup_binstr(const char *src, size_t len)
{
    char *res = NULL;
    int ret;

    if (src == NULL) {
        return NULL;
    }
    res = at_malloc(len + 1);
    if (res == NULL) {
        return NULL;
    }
    ret = memcpy_s(res, len, src, len);
    if (ret != EOK) {
        at_free(res);
        res = NULL;
        return NULL;
    }
    res[len] = '\0';

    return res;
}

static int at_hex2num(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;    /* add 10 */
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;    /* add 10 */
    }
    return -1;
}

int at_hex2byte(const char *hex)
{
    int a, b;
    a = at_hex2num(*hex++);
    if (a < 0) {
        return -1;
    }
    b = at_hex2num(*hex++);
    if (b < 0) {
        return -1;
    }
    return ((hi_u32)a << 4) | (hi_u32)b;    /* 4 */
}

/**
 * at_hexstr2bin - Convert ASCII hex string into binary data
 * @hex: ASCII hex string (e.g., "01ab")
 * @buf: Buffer for the binary data
 * @len: Length of the text to convert in bytes (of buf); hex will be double
 * this size
 * Returns: 0 on success, -1 on failure (invalid hex string)
 */
int at_hexstr2bin(const char *hex, hi_u8 *buf, size_t len)
{
    size_t i;
    const char *ipos = hex;
    hi_u8 *opos = buf;

    for (i = 0; i < len; i++) {
        int a = at_hex2byte(ipos);
        if (a < 0) {
            return -1;
        }
        *opos++ = a;
        ipos += 2;  /* add 2 */
    }
    return 0;
}

void at_printf_encode(char *txt, size_t maxlen, const hi_u8 *data, size_t len)
{
    char *end = txt + maxlen;
    size_t i;

    for (i = 0; i < len; i++) {
        if (txt + 4 >= end) {   /* add 4 */
            break;
        }

        switch (data[i]) {
            case '\"':
                *txt++ = '\\';
                *txt++ = '\"';
                break;
            case '\\':
                *txt++ = '\\';
                *txt++ = '\\';
                break;
            case '\033':
                *txt++ = '\\';
                *txt++ = 'e';
                break;
            case '\n':
                *txt++ = '\\';
                *txt++ = 'n';
                break;
            case '\r':
                *txt++ = '\\';
                *txt++ = 'r';
                break;
            case '\t':
                *txt++ = '\\';
                *txt++ = 't';
                break;
            default:
                if (data[i] >= 32 && data[i] <= 126) {  /* range [32,126] */
                    *txt++ = data[i];
                } else {
                    txt += at_pading(txt, end - txt, "\\x%02x", data[i]);
                }
                break;
        }
    }

    *txt = '\0';
}

hi_void at_printf_decode_slash(hi_u8 *buf, const char **str_pos, size_t *str_len)
{
    const char *pos = *str_pos;
    size_t len = *str_len;
    int val;

    pos++;
    switch (*pos) {
        case '\\':
            buf[len++] = '\\';
            pos++;
            break;
        case '"':
            buf[len++] = '"';
            pos++;
            break;
        case 'n':
            buf[len++] = '\n';
            pos++;
            break;
        case 'r':
            buf[len++] = '\r';
            pos++;
            break;
        case 't':
            buf[len++] = '\t';
            pos++;
            break;
        case 'e':
            buf[len++] = '\033';
            pos++;
            break;
        case 'x':
            pos++;
            val = at_hex2byte(pos);
            if (val < 0) {
                val = at_hex2num(*pos);
                if (val < 0) {
                    break;
                }
                buf[len++] = val;
                pos++;
            } else {
                buf[len++] = val;
                pos += 2;   /* add 2 */
            }
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
            val = *pos++ - '0';
            if (*pos >= '0' && *pos <= '7') {
                val = val * 8 + (*pos++ - '0'); /* 8 */
            }
            if (*pos >= '0' && *pos <= '7') {
                val = val * 8 + (*pos++ - '0'); /* 8 */
            }
            buf[len++] = val;
            break;
        default:
            break;
    }

    *str_pos = pos;
    *str_len = len;
}

size_t at_printf_decode(hi_u8 *buf, size_t maxlen, const char *str)
{
    const char *pos = str;
    size_t len = 0;

    while (*pos) {
        if (len + 1 >= maxlen) {
            break;
        }
        switch (*pos) {
            case '\\':
                at_printf_decode_slash(buf, &pos, &len);
                break;
            default:
                buf[len++] = *pos++;
                break;
        }
    }
    if (maxlen > len) {
        buf[len] = '\0';
    }

    return len;
}

char* at_parse_string_normal(const char *value, size_t *len)
{
    const char *pos = NULL;
    char *str = NULL;

    value++;
    pos = at_strrchr(value, '"');
    if (pos == NULL || pos[1] != '\0') {
        return NULL;
    }
    *len = pos - value;
    str = at_dup_binstr(value, *len);
    if (str == NULL) {
        return NULL;
    }
    return str;
}

char* at_parse_string_with_p(const char *value, size_t *len)
{
    const char *pos = NULL;
    char *tstr = NULL;
    char *str = NULL;
    size_t tlen;

    value += 2;     /* add 2 */
    pos = at_strrchr(value, '"');
    if (pos == NULL || pos[1] != '\0') {
        return NULL;
    }
    tlen = pos - value;
    tstr = at_dup_binstr(value, tlen);
    if (tstr == NULL) {
        return NULL;
    }

    str = at_malloc(tlen + 1);
    if (str == NULL) {
        at_free(tstr);
        return NULL;
    }

    *len = at_printf_decode((hi_u8 *) str, tlen + 1, tstr);
    at_free(tstr);

    return str;
}

char* at_parse_string_other(const char *value, size_t *len)
{
    hi_u8 *str = NULL;
    size_t tlen;
    size_t hlen = at_strlen(value);
    if (hlen & 1) {
        return NULL;
    }
    tlen = hlen / 2;    /* 2 */
    str = at_malloc(tlen + 1);
    if (str == NULL) {
        return NULL;
    }
    if (at_hexstr2bin(value, str, tlen)) {
        at_free((char*)str);
        return NULL;
    }
    str[tlen] = '\0';
    *len = tlen;
    return (char *) str;
}


char* at_parse_string(const char *value, size_t *len)
{
    if (len == HI_NULL) {
        return HI_NULL;
    }
    if (*value == '"') {
        return at_parse_string_normal(value, len);
    } else if (*value == 'P' && value[1] == '"') {
        return at_parse_string_with_p(value, len);
    } else {
        return at_parse_string_other(value, len);
    }
}

/**
 * at_ssid_txt - Convert SSID to a printable string
 * @ssid: SSID (32-octet string)
 * @ssid_len: Length of ssid in octets
 * Returns: Pointer to a printable string
 *
 * This function can be used to convert SSIDs into printable form. In most
 * cases, SSIDs do not use unprintable characters, but IEEE 802.11 standard
 * does not limit the used character set, so anything could be used in an SSID.
 *
 * This function uses a static buffer, so only one call can be used at the
 * time, i.e., this is not re-entrant and the returned buffer must be used
 * before calling this again.
 */
const char* at_ssid_txt(const hi_u8 *ssid, size_t ssid_len)
{
    static char ssid_txt[AT_SSID_MAX_LEN * 4 + 1]; /* 4 */

    if (ssid == NULL) {
        ssid_txt[0] = '\0';
        return ssid_txt;
    }

    at_printf_encode(ssid_txt, sizeof(ssid_txt), ssid, ssid_len);
    return ssid_txt;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif
