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

#ifndef __DRV_OTP_H__
#define __DRV_OTP_H__

#include "hi_type.h"
#include "hi_common_otp.h"
#include "drv_ioctl_otp.h"

#define OTP_USER_WORK_MODE          0x0000
#define OTP_USER_OP_START           0x0004
#define OTP_USER_KEY_INDEX          0x0008
#define OTP_USER_KEY_DATA0          0x000c
#define OTP_USER_KEY_DATA1          0x0010
#define OTP_USER_KEY_DATA2          0x0014
#define OTP_USER_KEY_DATA3          0x0018
#define OTP_USER_KEY_DATA4          0x001c
#define OTP_USER_KEY_DATA5          0x0020
#define OTP_USER_KEY_DATA6          0x0024
#define OTP_USER_KEY_DATA7          0x0028
#define OTP_USER_KEY_DATA8          0x002c
#define OTP_USER_FLAG_VALUE         0x0030
#define OTP_USER_FLAG_INDEX         0x0034
#define OTP_USER_REV_ADDR           0x0038
#define OTP_USER_REV_WDATA          0x003c
#define OTP_USER_REV_RDATA          0x0040
#define OTP_USER_LOCK_STA0          0x0044
#define OTP_USER_LOCK_STA1          0x0048
#define OTP_USER_CTRL_STA           0x004c
#define OTP_WAIT_TIME_OUT           10000
#define OTP_OP_START_VAL            0x1acce551
#define OTP_USER_INDEX_ROOM_MAX     0x37F

#define OTP_USER_KEY_MAX_BYTES      32
#define OTP_USER_KEY_MAX_WORDS      (OTP_USER_KEY_MAX_BYTES / 4)

typedef union {
    struct {
        hi_u32 secure_boot_en: 1;           /* 0 */
        hi_u32 ddr_ca_en: 1;                /* 1 */
        hi_u32 jtag_ca_en: 1;               /* 2 */
        hi_u32 reserved: 1;                 /* 3 */
        hi_u32 jtag_prt_mode: 2;            /* [4:5] */
        hi_u32 jtag_prt_mode_lock_en: 1;    /* 6 */
        hi_u32 secure_iso_en: 1;            /* 7 */
        hi_u32 uboot_redundance: 1;         /* 8 */
        hi_u32 reserved_flag1: 1;           /* 9 */
        hi_u32 reserved_flag2: 21;          /* [10:30] */
        hi_u32 reserved_flag2_lock_en: 1;   /* 31 */
    } bits;
    hi_u32 u32;
} otp_user_flag_value;

typedef union {
    struct {
        hi_u32 secure_boot_en_lock: 1;      /* 0 */
        hi_u32 ddr_ca_en_lock: 1;           /* 1 */
        hi_u32 jtag_pw_id_lock: 1;          /* 2 */
        hi_u32 jtag_pw_lock: 1;             /* 3 */
        hi_u32 root_key_lock: 1;            /* 4 */
        hi_u32 key0_lock: 1;                /* 5 */
        hi_u32 key1_lock: 1;                /* 6 */
        hi_u32 key2_lock: 1;                /* 7 */
        hi_u32 key3_lock: 1;                /* 8 */
        hi_u32 jtag_ca_en_lock: 1;          /* 9 */
        hi_u32 jtag_prt_mode_lock: 1;       /* 10 */
        hi_u32 reserved2: 1;                /* 11 */
        hi_u32 uboot_redundance_lock: 1;    /* 12 */
        hi_u32 reserved_flag1_lock: 1;      /* 13 */
        hi_u32 reserved_flag2_lock: 1;      /* 14 */
        hi_u32 hmac_key_lock: 1;            /* 15 */
        hi_u32 reserved3: 16;               /* [16:31] */
    } bits;
    hi_u32 u32;
} otp_user_lock_sta0;

typedef enum {
    OTP_CTRL_STA_OP_BUSY = 0,
    OTP_CTRL_STA_USER_CMD_FINISH,
    OTP_CTRL_STA_USER_LOCK_ERR,
    OTP_CTRL_STA_KEY_RD_BACK_CHECK_ERR,
    OTP_CTRL_STA_KEY_CRC_CHECK_OK_FLAG,
    OTP_CTRL_STA_USER_REV_RD_FINISH,
    OTP_CTRL_STA_USER_REV_PGM_FINISH,
    OTP_CTRL_STA_FLAG_PGM_FINISH,
    OTP_CTRL_STA_KEY_CRC_CHECK_FINISH,
    OTP_CTRL_STA_KEY_PGM_FINISH,
    OTP_CTRL_STA_KEY_LOAD_FINISH,
    OTP_CTRL_STA_RD_LOCK_STA_FINISH,
    OTP_CTRL_STA_KEY0_INDEX_FINISH,
    OTP_CTRL_STA_KEY1_INDEX_FINISH,
    OTP_CTRL_STA_KEY2_INDEX_FINISH,
    OTP_CTRL_STA_KEY3_INDEX_FINISH,
    OTP_CTRL_STA_USER_REV_ADDR0_FINISH,
    OTP_CTRL_STA_USER_REV_ADDR1_FINISH,
    OTP_CTRL_STA_USER_REV_ADDR2_FINISH,
    OTP_CTRL_STA_USER_REV_ADDR3_FINISH,
    OTP_CTRL_STA_USER_REV_ADDR4_FINISH,
    OTP_CTRL_STA_USER_REV_ADDR5_FINISH,
    OTP_CTRL_STA_USER_REV_ADDR6_FINISH,
    OTP_CTRL_STA_USER_REV_ADDR7_FINISH,
    OTP_CTRL_STA_FLAG_INDEX_FINISH,
    OTP_CTRL_STA_BUTT,
    OTP_CTRL_STA_INVALID,
} otp_user_ctrl_sta;

typedef enum {
    OTP_WORK_MODE_READ_LOCK_STA = 0,
    OTP_WORK_MODE_LOAD_CIPHER_KEY,
    OTP_WORK_MODE_BURN_KEY,
    OTP_WORK_MODE_VERIFY_KEY_CRC,
    OTP_WORK_MODE_ENABLE_FLAG_CFG,
    OTP_WORK_MODE_WRITE_USER_ROOM,
    OTP_WORK_MODE_READ_USER_ROOM,
    OTP_WORK_MODE_BUTT,
} otp_user_work_mode;

typedef enum {
    OTP_USER_KEY0 = 0,
    OTP_USER_KEY1,
    OTP_USER_KEY2,
    OTP_USER_KEY3,
    OTP_USER_KEY_JTAG_PW_ID,
    OTP_USER_KEY_JTAG_PW,
    OTP_USER_KEY_ROOTKEY,
    OTP_USER_KEY_HMACKEY,
    OTP_USER_KEY_BUTT,
} otp_user_key_index;

typedef enum {
    OTP_USER_FLAG_SECURE_BOOT_EN = 0,
    OTP_USER_FLAG_DDR_CA_EN,
    OTP_USER_FLAG_JTAG_CA_EN,
    OTP_USER_FLAG_JTAG_PRT_MODE,
    OTP_USER_FLAG_SECURE_ISO_EN,
    OTP_USER_FLAG_UBOOT_REDUNDANCE,
    OTP_USER_FLAG_RESERVED,
    OTP_USER_FLAG_BUTT,
} otp_user_flag_index;

hi_s32 drv_otp_set_user_data(const hi_char *field_name,
    hi_u32 offset, const hi_u8 *value, hi_u32 value_len);

hi_s32 drv_otp_get_user_data(const hi_char *field_name,
    hi_u32 offset, hi_u8 *value, hi_u32 value_len);

hi_s32 drv_otp_burn_product_pv(const hi_otp_burn_pv_item *pv, hi_u32 num);

hi_s32 drv_otp_read_product_pv(hi_otp_burn_pv_item *pv, hi_u32 num);

hi_s32 drv_otp_get_key_verify_status(const hi_char *key_name, hi_bool *status);

hi_s32 drv_otp_load_key_to_klad(const hi_char *key_name);

#endif /* __DRV_OTP_H__ */