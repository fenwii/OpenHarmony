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

#ifndef __DRV_OSAL_CHIP_H__
#define __DRV_OSAL_CHIP_H__

/* otp attr */
#define OTP_ATTR_BURN_KEY           0x00000001
#define OTP_ATTR_VERIFY_KEY         0x00000002
#define OTP_ATTR_LOAD_KEY           0x00000004
#define OTP_ATTR_ENABLE_FLAG        0x00000008
#define OTP_ATTR_RESERVED_DATA      0x00000010

#if defined(CHIP_TYPE_hi3521dv200)
#include "otp_data_hi3521dv200.h"

#elif defined(CHIP_TYPE_hi3531dv200)
#include "otp_data_hi3531dv200.h"

#else
#error You need to define a configuration file for chip !
#endif

#endif /* __DRV_OSAL_CHIP_H__ */

