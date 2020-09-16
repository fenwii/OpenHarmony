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

#ifndef __HAL_OTP_H__
#define __HAL_OTP_H__

#include "hi_type.h"
#include "hi_common_otp.h"

#define OTP_REG_BASE_ADDR_PHY           0x10200000
#define REG_SYS_OTP_CLK_ADDR_PHY        0x11013240
#define OTP_CRG_CLOCK_BIT               (0x01 << 4)

hi_s32 hal_otp_init(hi_void);

hi_void hal_otp_deinit(hi_void);

hi_s32 hal_otp_read_word(hi_u32 offset, hi_u32 *value);

hi_s32 hal_otp_write_word(hi_u32 offset, hi_u32 value);

#endif /* __HAL_OTP_H__ */
