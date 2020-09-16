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

#include "drv_ioctl_otp.h"
#include "drv_osal_lib.h"

hi_void hi_otp_print_arr_u8(const hi_char *name, const hi_u8 *msg, hi_u32 msg_len)
{
#if HI_OTP_TEST
    hi_u32 i;

    if (name != HI_NULL) {
        HI_PRINT("%s: \n", name);
    }

    for (i = 0; i < msg_len; i++) {
        if (i != 0 && align_16_bytes(i)) {
            HI_PRINT("\n");
        }
        HI_PRINT("%02X ", msg[i]);
    }
    HI_PRINT("\n");
#endif
}

hi_void hi_otp_print_arr_u32(const hi_char *name, const hi_u32 *msg, hi_u32 msg_len)
{
#if HI_OTP_TEST
    hi_u32 i;

    if (name != HI_NULL) {
        HI_PRINT("%s: \n", name);
    }

    for (i = 0; i < msg_len; i++) {
        if (i != 0 && align_16_bytes(i)) {
            HI_PRINT("\n");
        }
        HI_PRINT("%08X ", msg[i]);
    }
    HI_PRINT("\n");
#endif
}

hi_s32 hi_otp_word_big_endian(const hi_u32 word_val, hi_u8 *byte_buf, hi_u32 len)
{
    hi_otp_check_formula_fail(len != WORD_BYTE_WIDTH, HI_ERR_OTP_INVALID_PARAM);

    byte_buf[WORD_IDX_0] = (word_val >> OFFSET_3_BYTE) & 0xff;
    byte_buf[WORD_IDX_1] = (word_val >> OFFSET_2_BYTE) & 0xff;
    byte_buf[WORD_IDX_2] = (word_val >> OFFSET_1_BYTE) & 0xff;
    byte_buf[WORD_IDX_3] = (word_val >> OFFSET_0_BYTE) & 0xff;

    return HI_SUCCESS;
}

hi_u16 hi_otp_crc16_modbus(const hi_u8 *msg, hi_u32 msg_len)
{
    hi_u32 i;
    hi_u16 crc_in = 0xFFFF;
    hi_u16 crc_poly = 0x8005;
    hi_u8 crc_char = 0;

    while (msg_len--) {
        crc_char = *(msg++);
        crc_in ^= (crc_char << OFFSET_1_BYTE);
        for (i = 0; i < BYTE_BIT_WIDTH; i++) {
            if (crc_in & 0x8000) {
                crc_in = (crc_in << 1) ^ crc_poly;
            } else {
                crc_in = crc_in << 1;
            }
        }
    }

    return (crc_in) ;
}

hi_s32 otp_memset(void *src, hi_u32 len1, int num, hi_u32 len2)
{
    if (len1 < len2) {
        hi_otp_err("len1 < len2!!!\n");
        return HI_ERR_OTP_INVALID_PARAM;
    }
    memset(src, num, len2);
    return EOK;
}

hi_s32 otp_memcpy(void *dst, hi_u32 len1, const void *src, hi_u32 len2)
{
    if (len1 < len2) {
        hi_otp_err("len1 < len2!!!\n");
        return HI_ERR_OTP_INVALID_PARAM;
    }
    memcpy(dst, src, len2);
    return EOK;
}



