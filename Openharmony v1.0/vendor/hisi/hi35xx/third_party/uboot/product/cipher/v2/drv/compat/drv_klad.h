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
 * Description   : head files for drv klad.
 */

#ifndef DRV_KLAD_H
#define DRV_KLAD_H

#include "hi_types.h"
#include "common.h"
#include "drv_cipher_ioctl.h"

extern hi_void *g_efuse_otp_reg_base;

hi_s32 drv_klad_init(hi_void);
hi_void drv_klad_deinit(hi_void);

hi_s32 drv_cipher_klad_load_key(hi_u32 chn_id,
                                hi_cipher_ca_type root_key,
                                hi_cipher_klad_target klad_target,
                                hi_u8 *data_input,
                                hi_u32 key_len);

hi_s32 drv_cipher_klad_encrypt_key(hi_cipher_ca_type root_key,
                                   hi_cipher_klad_target klad_target,
                                   hi_u32 *clean_key,
                                   hi_u32 *encrypt_key);

#endif