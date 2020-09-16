/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __DRV_LIB_OSAL_H__
#define __DRV_LIB_OSAL_H__

#include <common.h>
#include <asm/io.h>
#include <asm/string.h>
#include "hi_type.h"

/* otp cmd param buffer size for ioctl. */
#define OTP_CMD_PARAM_SIZE              256

/* otp user data max 16k bytes */
#define OTP_USER_DATA_MAX_SIZE          0x4000

#define align_word(offset)          (((offset) & 0x03) == 0)
#define align_16_bytes(offset)      (((offset) & 0x0f) == 0)
#define word_number(len)            (((len) % 4 == 0) ? ((len) / 4) : ((len) / 4 + 1))

#define array_size(x)               (sizeof(x) / sizeof(x[0]))

/* --------------- debug tools --------------- */
#define HI_OTP_TEST                 0
#define HI_PRINT                    printf
#define hi_otp_err(fmt, ...)        HI_PRINT("[ERR-%s-%04d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#if HI_OTP_TEST
#define hi_otp_log(fmt, ...)        HI_PRINT("[LOG-%s-%04d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define hi_otp_info(fmt, ...)       HI_PRINT("[INFO-%s-%04d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define hi_otp_enter()              HI_PRINT("%s-%04d enter --->\n", __FUNCTION__, __LINE__);
#define hi_otp_exit()               HI_PRINT("%s-%04d exit <---\n\n", __FUNCTION__, __LINE__);
#else
#define hi_otp_log(fmt, ...)
#define hi_otp_info(fmt, ...)
#define hi_otp_enter()
#define hi_otp_exit()
#endif

#define hi_otp_func_fail_return(_func, _formula, _errno) \
        do { \
            if (_formula) { \
                hi_otp_err("call %s failed, ret = 0x%08X\n", #_func, _errno); \
                return _errno; \
            } \
        } while (0)

#define hi_otp_func_fail_goto(_func, _formula, _errno) \
    do { \
        if (_formula) { \
            hi_otp_err("call %s failed, ret = 0x%08X\n", #_func, _errno); \
            goto otp_exit; \
        } \
    } while (0)


#define hi_otp_check_formula_fail(_formula, _errno) \
        do { \
            if (_formula) { \
                hi_otp_err("%s is invalid, ret = 0x%08X\n", #_formula, _errno); \
                return _errno; \
            } \
        } while (0)

hi_void hi_otp_print_arr_u8(const hi_char *name, const hi_u8 *msg, hi_u32 msg_len);

hi_void hi_otp_print_arr_u32(const hi_char *name, const hi_u32 *msg, hi_u32 msg_len);

hi_s32 hi_otp_word_big_endian(const hi_u32 word_val, hi_u8 *byte_buf, hi_u32 len);

hi_u16 hi_otp_crc16_modbus(const hi_u8 *msg, hi_u32 msg_len);

#endif /* __DRV_LIB_OSAL_H__ */
