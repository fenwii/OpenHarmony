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

#ifndef __USER_OSAL_LIB_H__
#define __USER_OSAL_LIB_H__

#include <common.h>
#include <asm/string.h>
#include "hal_otp.h"

extern hi_s32 g_otp_dev_fd;
#define otp_open(a, b, c)           hal_otp_init()
#define otp_close(x)                (hal_otp_deinit(), 0)
#define otp_ioctl(cmd, argp)        drv_ioctl_otp(cmd, argp)

#define OTP_MUTEX_T                 // pthread_mutex_t
#define otp_mutex_init(x)           // (hi_void)pthread_mutex_init(x, NULL)
#define otp_mutex_lock(x)           // (hi_void)pthread_mutex_lock(x)
#define otp_mutex_unlock(x)         // (hi_void)pthread_mutex_unlock(x)
#define otp_mutex_destroy(x)        // pthread_mutex_destroy(x)

#define HI_PRINT                    printf
#define hi_otp_log(fmt, ...)        // HI_PRINT("[LOG-%s-%d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define hi_otp_info(fmt, ...)       // HI_PRINT("[INFO-%s-%d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define hi_otp_err(fmt, ...)        HI_PRINT("[ERR-%s-%d] "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define hi_otp_func_fail_return(_func, _formula, _errno) \
    do { \
        if (_formula) { \
            hi_otp_err("call %s failed, ret = 0x%08X\n", #_func, _errno); \
            return _errno; \
        } \
    } while (0)

#define hi_otp_check_formula_fail(_formula, _errno) \
    do { \
        if (_formula) { \
            hi_otp_err("%s is invalid, ret = 0x%08X\n", #_formula, _errno); \
            return _errno; \
        } \
    } while (0)

#endif /* __USER_OSAL_LIB_H__ */