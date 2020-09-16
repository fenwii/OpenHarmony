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

#include "hks_utility.h"

#include "securec.h"

#include "hks_errno.h"
#include "hks_mem.h"

/*
 * get the length of clone string
 * parameter:
 *     src_str      - [in]  - source string.
 *     str_len_max  - [in]  - the max length of string.
 * return value:
 *     the length of source string.
 * note:
 *     if src_str is null or real length is invalid,
 *     the returned value of length will be 0.
 */
static size_t hks_get_clone_str_len(const char *src_str, uint32_t str_len_max)
{
    if (src_str == NULL) {
        log_error("invalid src_str");
        return 0;
    }

    size_t str_len = strlen(src_str);

    if ((str_len == 0) || (str_len > str_len_max)) {
        log_error("invalid src_str len=%u, max_len=%u", str_len,
            str_len_max);
        return 0;
    }

    return str_len;
}

/*
 * clone string
 * parameter:
 *     src_str      - [in]  - source string.
 *     str_len_max  - [in]  - the max length of string.
 * return value:
 *     destination string, the buffer will be allcated in function,
 *     and it should be freed by caller.
 */
char *hks_clone_str(const char *src_str, uint32_t str_len_max)
{
    /* if src_str is null or real length is invalid,
     * the returned value of length will be 0.
     */
    size_t str_len = hks_get_clone_str_len(src_str, str_len_max);

    if (str_len == 0)
        return NULL;

    char *new_buf = (char *)HKS_MALLOC(str_len + HKS_END_CHAR_LEN);

    if (new_buf == NULL) {
        log_error("malloc new buffer fail");
        return NULL;
    }

    errno_t rc = memcpy_s(new_buf, str_len + HKS_END_CHAR_LEN, src_str, str_len);

    /* It's impossible to fail, only for CodeMars scan. */
    if (rc != EOK) {
        hks_free_ptr(new_buf);
        return NULL;
    }
    new_buf[str_len] = '\0';

    return new_buf;
}

/*
 * get endian.
 * parameter: none
 * return value:
 *     HKS_LITTLE_ENDIAN or HKS_BIG_ENDIAN
 */
uint8_t hks_get_endian(void)
{
    uint16_t u16_val = HKS_ENDIAN_TEST_U16_VAL;
    uint8_t u8_val = *((uint8_t *)&u16_val);

    if (u8_val == HKS_ENDIAN_TEST_U8_VAL)
        return HKS_BIG_ENDIAN;

    return HKS_LITTLE_ENDIAN;
}

/* the byte offset of uint16 */
const uint8_t g_hks_u16_byte_offset[HKS_ENDIAN_NUM][HKS_U16_BYTE_NUM] = {
    { 0, 1 }, /* big endian */
    { 1, 0 }, /* little endian */
};

/* the byte offset of uint32 */
const uint8_t g_hks_u32_byte_offset[HKS_ENDIAN_NUM][HKS_U32_BYTE_NUM] = {
    { 0, 1, 2, 3 }, /* big endian */
    { 3, 2, 1, 0 }, /* little endian */
};

/* the byte offset of uint64 */
const uint8_t g_hks_u64_byte_offset[HKS_ENDIAN_NUM][HKS_U64_BYTE_NUM] = {
    { 0, 1, 2, 3, 4, 5, 6, 7 }, /* big endian */
    { 7, 6, 5, 4, 3, 2, 1, 0 }, /* little endian */
};

/*
 *  check the parameter of uint8 buffer data.
 * parameter:
 *     var_size      - [in]      - variable size.
 *     u8_buf        - [in]      - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in]      - uint8 buffer offset.
 * return value:
 *     success or error code.
 */
static int32_t hks_chk_u8_buf_para(uint32_t var_size, const uint8_t *u8_buf,
    uint32_t u8_buf_len, const uint32_t *u8_buf_offset)
{
    if (u8_buf == NULL) {
        log_error("invalid u8 buf");
        return HKS_ERROR_NULL_POINTER;
    }
    if (u8_buf_offset == NULL) {
        log_error("invalid u8 buf offset");
        return HKS_ERROR_NULL_POINTER;
    }

    if ((*u8_buf_offset >= u8_buf_len) ||
        (*u8_buf_offset >= HKS_U8_BUF_LEN_MAX) ||
        (u8_buf_len > HKS_U8_BUF_LEN_MAX) ||
        ((*u8_buf_offset + var_size) > u8_buf_len)) {
        log_error("invalid para,buf_offset=%u,buf_len=%u",
            *u8_buf_offset, u8_buf_len);
        return HKS_ERROR_INVALID_ARGUMENT;
    }

    return HKS_STATUS_OK;
}

/*
 * convert uint16 variable to uint8 buffer data.
 * parameter:
 *     u16_var       - [in]      - uint16 variable.
 *     u8_buf        - [out]     - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 * return value:
 *     success or error code.
 */
int32_t hks_u16_2_u8_buf(uint16_t u16_var, uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset)
{
    int32_t rc = hks_chk_u8_buf_para(HKS_U16_BYTE_NUM, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    uint8_t endian = hks_get_endian();

    union hks_u8_u16 tmp;

    tmp.u16_var = u16_var;

    uint32_t i = 0;

    for (; i < HKS_U16_BYTE_NUM; i++) {
        uint32_t offset = *u8_buf_offset +
            g_hks_u16_byte_offset[endian][i];

        if (offset >= u8_buf_len) {
            log_error("impossible error,offset=%u,buf_offset=%u, \
            buf_len=%u", offset, *u8_buf_offset, u8_buf_len);
            return HKS_ERROR_INTERNAL_UNKOWN;
        }
        u8_buf[offset] = tmp.u8_var[i];
    }

    *u8_buf_offset += HKS_U16_BYTE_NUM;

    return HKS_STATUS_OK;
}

/*
 * convert uint8 buffer data to uint16 variable.
 * parameter:
 *     u8_buf        - [in]     - uint8 buffer.
 *     u8_buf_len    - [in]     - uint8 buffer length.
 *     u8_buf_offset - [in/out] - uint8 buffer offset.
 *     u16_var       - [out]    - uint16 variable.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_buf_2_u16(const uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset, uint16_t *u16_var)
{
    if (u16_var == NULL) {
        log_error("invalid u16 var");
        return HKS_ERROR_NULL_POINTER;
    }

    int32_t rc = hks_chk_u8_buf_para(HKS_U16_BYTE_NUM, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    uint8_t endian = hks_get_endian();

    union hks_u8_u16 tmp;
    uint32_t i = 0;

    for (; i < HKS_U16_BYTE_NUM; i++) {
        uint32_t offset = *u8_buf_offset +
            g_hks_u16_byte_offset[endian][i];

        if (offset >= u8_buf_len) {
            log_error("impossible error,offset=%u,buf_offset=%u, \
            buf_len=%u", offset, *u8_buf_offset, u8_buf_len);
            return HKS_ERROR_INTERNAL_UNKOWN;
        }
        tmp.u8_var[i] = u8_buf[offset];
    }

    *u16_var = tmp.u16_var;
    *u8_buf_offset += HKS_U16_BYTE_NUM;

    return HKS_STATUS_OK;
}

/*
 * convert uint32 variable to uint8 buffer data.
 * parameter:
 *     u32_var       - [in]      - uint32 variable.
 *     u8_buf        - [out]     - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 * return value:
 *     success or error code.
 */
int32_t hks_u32_2_u8_buf(uint32_t u32_var, uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset)
{
    int32_t rc = hks_chk_u8_buf_para(HKS_U32_BYTE_NUM, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    uint8_t endian = hks_get_endian();

    union hks_u8_u32 tmp;

    tmp.u32_var = u32_var;

    uint32_t i = 0;

    for (; i < HKS_U32_BYTE_NUM; i++) {
        uint32_t offset = *u8_buf_offset +
            g_hks_u32_byte_offset[endian][i];

        if (offset >= u8_buf_len) {
            log_error("impossible error,offset=%u,buf_offset=%u, \
            buf_len=%u", offset, *u8_buf_offset, u8_buf_len);
            return HKS_ERROR_INTERNAL_UNKOWN;
        }
        u8_buf[offset] = tmp.u8_var[i];
    }
    *u8_buf_offset += HKS_U32_BYTE_NUM;

    return HKS_STATUS_OK;
}

/*
 * convert uint8 buffer data to uint32 variable.
 * parameter:
 *     u8_buf        - [in]      - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 *     u32_var       - [out]     - uint32 variable.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_buf_2_u32(const uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset, uint32_t *u32_var)
{
    if (u32_var == NULL) {
        log_error("invalid u32 var");
        return HKS_ERROR_NULL_POINTER;
    }

    int32_t rc = hks_chk_u8_buf_para(HKS_U32_BYTE_NUM, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    uint8_t endian = hks_get_endian();

    union hks_u8_u32 tmp;

    uint32_t i = 0;

    for (; i < HKS_U32_BYTE_NUM; i++) {
        uint32_t offset = *u8_buf_offset +
            g_hks_u32_byte_offset[endian][i];

        if (offset >= u8_buf_len) {
            log_error("impossible error,offset=%u,buf_offset=%u, \
            buf_len=%u", offset, *u8_buf_offset, u8_buf_len);
            return HKS_ERROR_INTERNAL_UNKOWN;
        }
        tmp.u8_var[i] = u8_buf[offset];
    }
    *u32_var = tmp.u32_var;
    *u8_buf_offset += HKS_U32_BYTE_NUM;

    return HKS_STATUS_OK;
}

/*
 * convert uint64 variable to uint8 buffer data.
 * parameter:
 *     u64_var       - [in]      - uint64 variable.
 *     u8_buf        - [out]     - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 * return value:
 *     success or error code.
 */
int32_t hks_u64_2_u8_buf(uint64_t u64_var, uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset)
{
    int32_t rc = hks_chk_u8_buf_para(HKS_U64_BYTE_NUM, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    uint8_t endian = hks_get_endian();

    union hks_u8_u64 tmp;

    tmp.u64_var = u64_var;

    uint32_t i = 0;

    for (; i < HKS_U64_BYTE_NUM; i++) {
        uint32_t offset = *u8_buf_offset +
            g_hks_u64_byte_offset[endian][i];

        if (offset >= u8_buf_len) {
            log_error("impossible error,offset=%u,buf_offset=%u, \
            buf_len=%u", offset, *u8_buf_offset, u8_buf_len);
            return HKS_ERROR_INTERNAL_UNKOWN;
        }
        u8_buf[offset] = tmp.u8_var[i];
    }
    *u8_buf_offset += HKS_U64_BYTE_NUM;

    return HKS_STATUS_OK;
}

/*
 * convert uint8 buffer data to uint64 variable.
 * parameter:
 *     u8_buf        - [in]      - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 *     u64_var       - [out]     - uint64 variable.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_buf_2_u64(const uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset, uint64_t *u64_var)
{
    if (u64_var == NULL) {
        log_error("invalid u64 var");
        return HKS_ERROR_NULL_POINTER;
    }

    int32_t rc = hks_chk_u8_buf_para(HKS_U64_BYTE_NUM, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    uint8_t endian = hks_get_endian();

    union hks_u8_u64 tmp;
    uint32_t i = 0;

    for (; i < HKS_U64_BYTE_NUM; i++) {
        uint32_t offset = *u8_buf_offset +
            g_hks_u64_byte_offset[endian][i];

        if (offset >= u8_buf_len) {
            log_error("impossible error,offset=%u,buf_offset=%u, \
            buf_len=%u", offset, *u8_buf_offset, u8_buf_len);
            return HKS_ERROR_INTERNAL_UNKOWN;
        }
        tmp.u8_var[i] = u8_buf[offset];
    }
    *u64_var = tmp.u64_var;
    *u8_buf_offset += HKS_U64_BYTE_NUM;

    return HKS_STATUS_OK;
}

/*
 * convert uint8 variable to uint8 buffer data.
 * parameter:
 *     u8_var        - [in]      - uint8 variable.
 *     u8_buf        - [out]     - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_2_u8_buf(uint8_t u8_var, uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset)
{
    int32_t rc = hks_chk_u8_buf_para(sizeof(uint8_t), u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    *(u8_buf + *u8_buf_offset) = u8_var;
    *u8_buf_offset += sizeof(uint8_t);

    return HKS_STATUS_OK;
}

/*
 * convert uint8 buffer data to uint8 array.
 * parameter:
 *     u8_buf        - [in]      - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 *     u8_var        - [out]     - uint8 variable.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_buf_2_u8(const uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset, uint8_t *u8_var)
{
    if (u8_var == NULL) {
        log_error("invalid u8 var");
        return HKS_ERROR_NULL_POINTER;
    }

    int32_t rc = hks_chk_u8_buf_para(sizeof(uint8_t), u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    *u8_var = *(u8_buf + *u8_buf_offset);
    *u8_buf_offset += sizeof(uint8_t);

    return HKS_STATUS_OK;
}

/*
 * convert uint8 array to uint8 buffer data.
 * parameter:
 *     u8_array      - [in]      - uint8 array.
 *     u8_array_size - [in]      - uint8 array size.
 *     u8_buf        - [out]     - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_array_2_u8_buf(const uint8_t *u8_array, uint32_t u8_array_size,
    uint8_t *u8_buf, uint32_t u8_buf_len, uint32_t *u8_buf_offset)
{
    if (u8_array == NULL) {
        log_error("invalid u8 array");
        return HKS_ERROR_NULL_POINTER;
    }

    int32_t rc = hks_chk_u8_buf_para(u8_array_size, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    errno_t err = memcpy_s(u8_buf + *u8_buf_offset, u8_buf_len - *u8_buf_offset,
                  u8_array, u8_array_size);

    if (err != EOK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    *u8_buf_offset += u8_array_size;

    return HKS_STATUS_OK;
}

/*
 * convert uint8 buffer data to uint8 array.
 * parameter:
 *     u8_buf        - [in]      - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 *     u8_array      - [out]     - uint8 array.
 *     u8_array_size - [in]      - uint8 array size.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_buf_2_u8_array(const uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset, uint8_t *u8_array, uint32_t u8_array_size)
{
    if (u8_array == NULL) {
        log_error("invalid u8 array");
        return HKS_ERROR_NULL_POINTER;
    }

    int32_t rc = hks_chk_u8_buf_para(u8_array_size, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    errno_t err = memcpy_s(u8_array, u8_array_size, u8_buf + *u8_buf_offset,
        u8_array_size);

    if (err != EOK)
        return HKS_ERROR_INTERNAL_UNKOWN;

    *u8_buf_offset += u8_array_size;

    return HKS_STATUS_OK;
}

/*
 * convert time variable to uint8 buffer data.
 * parameter:
 *     time_var      - [in]      - time variable.
 *     u8_buf        - [out]     - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 * return value:
 *     success or error code.
 */
int32_t hks_time_2_u8_buf(const struct hks_time *time_var, uint8_t *u8_buf,
    uint32_t u8_buf_len, uint32_t *u8_buf_offset)
{
    if (time_var == NULL) {
        log_error("invalid time var");
        return HKS_ERROR_NULL_POINTER;
    }

    /* Fill year */
    int32_t rc = hks_u16_2_u8_buf(time_var->year, u8_buf, u8_buf_len,
        u8_buf_offset);

    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill month */
    rc = hks_u8_2_u8_buf(time_var->mon, u8_buf, u8_buf_len, u8_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill day */
    rc = hks_u8_2_u8_buf(time_var->day, u8_buf, u8_buf_len, u8_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill hour */
    rc = hks_u8_2_u8_buf(time_var->hour, u8_buf, u8_buf_len, u8_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill minuter */
    rc = hks_u8_2_u8_buf(time_var->min, u8_buf, u8_buf_len, u8_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Fill second */
    rc = hks_u8_2_u8_buf(time_var->sec, u8_buf, u8_buf_len, u8_buf_offset);
    if (rc != HKS_STATUS_OK)
        return rc;

    return HKS_STATUS_OK;
}

/*
 * convert uint8 buffer data to time variable.
 * parameter:
 *     u8_buf        - [in]     - uint8 buffer.
 *     u8_buf_len    - [in]     - uint8 buffer length.
 *     u8_buf_offset - [in/out] - uint8 buffer offset.
 *     time_var      - [out]    - time variable.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_buf_2_time(const uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset, struct hks_time *time_var)
{
    if (time_var == NULL) {
        log_error("invalid time var");
        return HKS_ERROR_NULL_POINTER;
    }

    /* Extract year */
    int32_t rc = hks_u8_buf_2_u16(u8_buf, u8_buf_len, u8_buf_offset,
        &(time_var->year));

    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract month */
    rc = hks_u8_buf_2_u8(u8_buf, u8_buf_len, u8_buf_offset,
        &(time_var->mon));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract day */
    rc = hks_u8_buf_2_u8(u8_buf, u8_buf_len, u8_buf_offset,
        &(time_var->day));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract hour */
    rc = hks_u8_buf_2_u8(u8_buf, u8_buf_len, u8_buf_offset,
        &(time_var->hour));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract minuter */
    rc = hks_u8_buf_2_u8(u8_buf, u8_buf_len, u8_buf_offset,
        &(time_var->min));
    if (rc != HKS_STATUS_OK)
        return rc;

    /* Extract second */
    rc = hks_u8_buf_2_u8(u8_buf, u8_buf_len, u8_buf_offset,
        &(time_var->sec));
    if (rc != HKS_STATUS_OK)
        return rc;

    return HKS_STATUS_OK;
}
