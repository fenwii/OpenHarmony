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

#ifndef __SYS_OTP_H__
#define __SYS_OTP_H__

#include "hi_type.h"
#include "hi_common_otp.h"

hi_s32 sys_otp_set_user_data(const hi_char *field_name,
    hi_u32 offset, const hi_u8 *value, hi_u32 value_len);

hi_s32 sys_otp_get_user_data(const hi_char *field_name,
    hi_u32 offset, hi_u8 *value, hi_u32 value_len);

hi_s32 sys_otp_set_user_data_lock(const hi_char *field_name,
    hi_u32 offset, hi_u32 value_len, hi_bool lock);

hi_s32 sys_otp_get_user_data_lock(const hi_char *field_name,
    hi_u32 offset, hi_u32 value_len, hi_otp_lock_status *lock_sta);

hi_s32 sys_otp_burn_product_pv(const hi_otp_burn_pv_item *pv, hi_u32 num);

hi_s32 sys_otp_read_product_pv(hi_otp_burn_pv_item *pv, hi_u32 num);

hi_s32 sys_otp_get_key_verify_status(const hi_char *key_name, hi_bool *status);

#endif /* __SYS_OTP_H__ */