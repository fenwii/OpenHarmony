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

#include "drv_osal_lib.h"
#include "drv_ioctl_otp.h"
#include "drv_otp.h"

hi_s32 drv_ioctl_otp(hi_u32 cmd, hi_void *argp)
{
    hi_s32 ret;
    hi_u32 nr;

    nr = otp_ioc_nr(cmd);

    hi_otp_check_formula_fail(argp == HI_NULL, HI_ERR_OTP_NULL_PTR);
    hi_otp_check_formula_fail(nr >= CMD_OTP_COUNT, HI_ERR_OTP_INVALID_PARAM);

    switch (cmd) {
        case CMD_OTP_SET_USER_DATA: {
            otp_user_data *data = (otp_user_data *)argp;
            ret = drv_otp_set_user_data(data->field_name, data->offset,
                addr_via_const(data->value), data->value_len);
            hi_otp_func_fail_return(drv_otp_set_user_data, ret != HI_SUCCESS, ret);
            break;
        }
        case CMD_OTP_GET_USER_DATA: {
            otp_user_data *data = (otp_user_data *)argp;
            ret = drv_otp_get_user_data(data->field_name, data->offset,
                addr_via(data->value), data->value_len);
            hi_otp_func_fail_return(drv_otp_get_user_data, ret != HI_SUCCESS, ret);
            break;
        }
        case CMD_OTP_BURN_PRODUCT_PV: {
            otp_product_pv *product_pv = (otp_product_pv *)argp;
            ret = drv_otp_burn_product_pv(addr_via_const(product_pv->pv), product_pv->num);
            hi_otp_func_fail_return(drv_otp_burn_product_pv, ret != HI_SUCCESS, ret);
            break;
        }
        case CMD_OTP_READ_PRODUCT_PV: {
            otp_product_pv *product_pv = (otp_product_pv *)argp;
            ret = drv_otp_read_product_pv(addr_via(product_pv->pv), product_pv->num);
            hi_otp_func_fail_return(drv_otp_read_product_pv, ret != HI_SUCCESS, ret);
            break;
        }
        case CMD_OTP_KEY_VERIFY_STATUS: {
            otp_key_verify_status *status = (otp_key_verify_status *)argp;
            ret = drv_otp_get_key_verify_status(status->field_name, &status->status);
            hi_otp_func_fail_return(drv_otp_get_key_verify_status, ret != HI_SUCCESS, ret);
            break;
        }
        default: {
            hi_otp_err("invalid command\n");
            return HI_ERR_OTP_INVALID_PARAM;
        }
    }

    return ret;
}

