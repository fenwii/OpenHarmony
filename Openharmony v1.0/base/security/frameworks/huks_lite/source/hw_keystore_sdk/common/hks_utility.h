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

#ifndef HKS_UTILITY_H
#define HKS_UTILITY_H

#include "hks_log_utils.h"
#include "hks_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* time */
struct hks_time {
    uint16_t year;
    uint8_t mon;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
};

/* the length of end character */
#define HKS_END_CHAR_LEN 1

/* the string length of uint8 variable */
#define HKS_U8_VAR_STR_LEN 2

/* the base value of year */
#define HKS_TM_YEAR_BASE 1900
/* the base value of month */
#define HKS_TM_MON_BASE 1

/* little endian */
#define HKS_LITTLE_ENDIAN 0
    /* big endian */
#define HKS_BIG_ENDIAN 1
/* the number of endian */
#define HKS_ENDIAN_NUM 2

/* the uint16 value for endian test */
#define HKS_ENDIAN_TEST_U16_VAL 0x1234
/* the uint8 value for endian test */
#define HKS_ENDIAN_TEST_U8_VAL 0x12

/* the max length of uint8 buffer */
#define HKS_U8_BUF_LEN_MAX 20480

/* the byte number of uint16 */
#define HKS_U16_BYTE_NUM 2
/* the byte number of uint32 */
#define HKS_U32_BYTE_NUM 4
/* the byte number of uint64 */
#define HKS_U64_BYTE_NUM 8
/* the word number of uint32 */
#define HKS_U32_WORD_NUM 2
/* the word number of uint64 */
#define HKS_U64_WORD_NUM 4
/* the dword number of uint64 */
#define HKS_U64_DWORD_NUM 2

union hks_u8_u64 {
    uint64_t u64_var;                     /* 1 uint64 */
    uint32_t u32_var[HKS_U64_DWORD_NUM];  /* 1 uint64 = 2 uint32 */
    uint16_t u16_var[HKS_U64_WORD_NUM];   /* 1 uint64 = 4 uint16 */
    uint8_t u8_var[HKS_U64_BYTE_NUM];     /* 1 uint64 = 8 uint8 */
};

union hks_u8_u32 {
    uint32_t u32_var;                   /* 1 uint32 */
    uint16_t u16_var[HKS_U32_WORD_NUM]; /* 1 uint32 = 2 uint16 */
    uint8_t u8_var[HKS_U32_BYTE_NUM];   /* 1 uint32 = 4 uint8 */
};

union hks_u8_u16 {
    uint16_t u16_var;                   /* 1 uint16 */
    uint8_t u8_var[HKS_U16_BYTE_NUM];   /* 1 uint16 = 2 uint8 */
};


/*
 * clone string
 * parameter:
 *     src_str      - [in]  - source string.
 *     str_len_max  - [in]  - the max length of string.
 * return value:
 *     destination string, the buffer will be allcated in function,
 *     and it should be freed by caller.
 */
char *hks_clone_str(const char *src_str, uint32_t str_len_max);

/*
 * get endian.
 * parameter: none
 * return value:
 *     HKS_LITTLE_ENDIAN or HKS_LITTLE_ENDIAN
 */
uint8_t hks_get_endian(void);

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
    uint32_t *u8_buf_offset);

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
    uint32_t *u8_buf_offset, uint16_t *u16_var);

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
    uint32_t *u8_buf_offset);

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
    uint32_t *u8_buf_offset, uint32_t *u32_var);

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
    uint32_t *u8_buf_offset);

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
    uint32_t *u8_buf_offset, uint64_t *u64_var);

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
    uint32_t *u8_buf_offset);

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
    uint32_t *u8_buf_offset, uint8_t *u8_var);

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
    uint8_t *u8_buf, uint32_t u8_buf_len, uint32_t *u8_buf_offset);

/*
 * convert uint8 buffer data to uint8 array.
 * parameter:
 *     u8_buf        - [in]      - uint8 buffer.
 *     u8_buf_len    - [in]      - uint8 buffer length.
 *     u8_buf_offset - [in/out]  - uint8 buffer offset.
 *     u8_array      - [in]      - uint8 array.
 *     u8_array_size - [in]      - uint8 array size.
 * return value:
 *     success or error code.
 */
int32_t hks_u8_buf_2_u8_array(const uint8_t *u8_buf, uint32_t u8_buf_len,
    uint32_t *u8_buf_offset, uint8_t *u8_array, uint32_t u8_array_size);

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
    uint32_t u8_buf_len, uint32_t *u8_buf_offset);

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
    uint32_t *u8_buf_offset, struct hks_time *time_var);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HKS_UTILITY_H */
