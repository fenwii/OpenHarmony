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

#ifndef __OTP_DATA_HI3521DV200_H__
#define __OTP_DATA_HI3521DV200_H__

#include "hi_type.h"
#include "drv_osal_lib.h"

typedef struct {
    hi_char field_name[HI_OTP_FIELD_NAME_MAX_LEN]; /* OTP fuse name */
    hi_u8 index; /* OTP bit index */
    hi_u32 value_len; /* OTP max value length */
    hi_bool burn; /* OTP whether or not burn permition */
    hi_u32 attr; /* OTP fuse name attribution */
} otp_data_item;

otp_data_item g_otp_data_item[] = {
    {"aes_key0",            0, 32, HI_TRUE, OTP_ATTR_BURN_KEY | OTP_ATTR_VERIFY_KEY | OTP_ATTR_LOAD_KEY},
    {"aes_key1",            1, 32, HI_TRUE, OTP_ATTR_BURN_KEY | OTP_ATTR_VERIFY_KEY | OTP_ATTR_LOAD_KEY},
    {"aes_key2",            2, 32, HI_TRUE, OTP_ATTR_BURN_KEY | OTP_ATTR_VERIFY_KEY | OTP_ATTR_LOAD_KEY},
    {"aes_key3",            3, 32, HI_TRUE, OTP_ATTR_BURN_KEY | OTP_ATTR_VERIFY_KEY | OTP_ATTR_LOAD_KEY},
    {"jtag_pw_id",          4, 8,  HI_TRUE, OTP_ATTR_BURN_KEY | OTP_ATTR_VERIFY_KEY},
    {"jtag_pw",             5, 16, HI_TRUE, OTP_ATTR_BURN_KEY | OTP_ATTR_VERIFY_KEY},
    {"root_key_sha256",     6, 32, HI_TRUE, OTP_ATTR_BURN_KEY | OTP_ATTR_VERIFY_KEY},

    {"secure_boot_en",      0, 1, HI_TRUE, OTP_ATTR_ENABLE_FLAG},
    {"ddr_ca_en",           1, 1, HI_TRUE, OTP_ATTR_ENABLE_FLAG},
    {"jtag_ca_en",          2, 1, HI_TRUE, OTP_ATTR_ENABLE_FLAG},
    {"jtag_prt_mode",       3, 1, HI_TRUE, OTP_ATTR_ENABLE_FLAG},
    {"uboot_redundance",    5, 1, HI_TRUE, OTP_ATTR_ENABLE_FLAG},

    {"user_reserved_data",  0, 3584, HI_TRUE, OTP_ATTR_RESERVED_DATA},
};

#endif /* __OTP_DATA_HI3521DV200_H__ */
