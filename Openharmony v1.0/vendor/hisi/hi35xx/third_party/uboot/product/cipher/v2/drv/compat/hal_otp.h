/*
 * hal_otp.h
 *
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
 * Description   : The OTP Driver
 */

#ifndef __HAL_OTP_H__
#define __HAL_OTP_H__

#include "hi_types.h"

#define OTP_USER_IF_BASE            g_efuse_otp_reg_base
#define OTP_USER_WORK_MODE          (OTP_USER_IF_BASE + 0x0000)
#define OTP_USER_OP_START           (OTP_USER_IF_BASE + 0x0004)
#define OTP_USER_KEY_INDEX          (OTP_USER_IF_BASE + 0x0008)
#define OTP_USER_KEY_DATA0          (OTP_USER_IF_BASE + 0x000c)
#define OTP_USER_KEY_DATA1          (OTP_USER_IF_BASE + 0x0010)
#define OTP_USER_KEY_DATA2          (OTP_USER_IF_BASE + 0x0014)
#define OTP_USER_KEY_DATA3          (OTP_USER_IF_BASE + 0x0018)
#define OTP_USER_KEY_DATA4          (OTP_USER_IF_BASE + 0x001c)
#define OTP_USER_KEY_DATA5          (OTP_USER_IF_BASE + 0x0020)
#define OTP_USER_KEY_DATA6          (OTP_USER_IF_BASE + 0x0024)
#define OTP_USER_KEY_DATA7          (OTP_USER_IF_BASE + 0x0028)
#define OTP_USER_KEY_DATA8          (OTP_USER_IF_BASE + 0x002c)
#define OTP_USER_FLAG_VALUE         (OTP_USER_IF_BASE + 0x0030)
#define OTP_USER_FLAG_INDEX         (OTP_USER_IF_BASE + 0x0034)
#define OTP_USER_REV_ADDR           (OTP_USER_IF_BASE + 0x0038)
#define OTP_USER_REV_WDATA          (OTP_USER_IF_BASE + 0x003c)
#define OTP_USER_REV_RDATA          (OTP_USER_IF_BASE + 0x0040)
#define OTP_USER_LOCK_STA0          (OTP_USER_IF_BASE + 0x0044)
#define OTP_USER_LOCK_STA1          (OTP_USER_IF_BASE + 0x0048)
#define OTP_USER_CTRL_STA           (OTP_USER_IF_BASE + 0x004c)

#if (defined(CONFIG_TARGET_HI3519AV100) || defined(CONFIG_TARGET_HI3556AV100))
#define REG_SYS_OTP_CLK_ADDR_PHY    0x04510194
#define OTP_CRG_CLOCK_BIT           (0x01 << 7)
#elif defined(CONFIG_TARGET_HI3559AV100) || defined(CONFIG_TARGET_HI3569V100)
#define REG_SYS_OTP_CLK_ADDR_PHY    0x12010194
#define OTP_CRG_CLOCK_BIT           (0x01 << 7)
#define OTP_CRG_RESET_BIT           (0x01 << 6)
#define OTP_CRG_RESET_SUPPORT
#elif (defined(CONFIG_TARGET_HI3516DV300) || defined(CONFIG_TARGET_HI3516AV300) || \
	defined(CONFIG_TARGET_HI3516CV500) || defined(CONFIG_TARGET_HI3556V200)  || \
	defined(CONFIG_TARGET_HI3559V200))
#define REG_SYS_OTP_CLK_ADDR_PHY    0x120101BC
#define OTP_CRG_CLOCK_BIT           (0x01 << 1)
#elif (defined(CONFIG_TARGET_HI3516EV200) || defined(CONFIG_TARGET_HI3516EV300) || \
	defined(CONFIG_TARGET_HI3518EV300) || defined(CONFIG_TARGET_HI3516DV200))
#define REG_SYS_OTP_CLK_ADDR_PHY    0x120101BC
#define OTP_CRG_CLOCK_BIT           (0x01 << 1)
#elif (defined(CONFIG_TARGET_HI3531DV200) || defined(CONFIG_TARGET_HI3535AV100) || \
	defined(CONFIG_TARGET_HI3521DV200) || defined(CONFIG_TARGET_HI3520DV500))
#define REG_SYS_OTP_CLK_ADDR_PHY    0x11013240
#define OTP_CRG_CLOCK_BIT           (0x01 << 4)
#endif

hi_s32 hal_efuse_otp_init(hi_void);
hi_s32 hal_efuse_otp_load_cipher_key(hi_u32 chn_id, hi_u32 opt_id);

#endif
