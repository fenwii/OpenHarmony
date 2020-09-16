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

#include "sys_otp.h"
#include "drv_ioctl_otp.h"
#include "user_osal_lib.h"

hi_s32 sys_otp_set_user_data(const hi_char *field_name,
    hi_u32 offset, const hi_u8 *value, hi_u32 value_len)
{
    hi_s32 ret;
    otp_user_data user_data;
    (hi_void)otp_memset(&user_data, sizeof(otp_user_data), 0, sizeof(otp_user_data));

    ret = otp_memcpy(user_data.field_name, sizeof(user_data.field_name), field_name, strlen(field_name));
    hi_otp_func_fail_return(otp_memcpy, ret != EOK, HI_ERR_OTP_FAILED_SEC_FUNC);

    addr_via_const(user_data.value) = value;
    user_data.offset = offset;
    user_data.value_len = value_len;

    ret = otp_ioctl(CMD_OTP_SET_USER_DATA, &user_data);
    hi_otp_func_fail_return(otp_ioctl, ret != HI_SUCCESS, ret);

    return HI_SUCCESS;
}

hi_s32 sys_otp_get_user_data(const hi_char *field_name,
    hi_u32 offset, hi_u8 *value, hi_u32 value_len)
{
    hi_s32 ret;
    otp_user_data user_data;
    (hi_void)otp_memset(&user_data, sizeof(otp_user_data), 0, sizeof(otp_user_data));

    ret = otp_memcpy(user_data.field_name, sizeof(user_data.field_name), field_name, strlen(field_name));
    hi_otp_func_fail_return(otp_memcpy, ret != EOK, HI_ERR_OTP_FAILED_SEC_FUNC);

    addr_via(user_data.value) = value;
    user_data.offset = offset;
    user_data.value_len = value_len;

    ret = otp_ioctl(CMD_OTP_GET_USER_DATA, &user_data);
    hi_otp_func_fail_return(otp_ioctl, ret != HI_SUCCESS, ret);

    return ret;
}

hi_s32 sys_otp_burn_product_pv(const hi_otp_burn_pv_item *pv, hi_u32 num)
{
    hi_s32 ret;
    otp_product_pv product_pv;

    (hi_void)otp_memset(&product_pv, sizeof(otp_product_pv), 0, sizeof(otp_product_pv));

    addr_via_const(product_pv.pv) = pv;
    product_pv.num = num;

    ret = otp_ioctl(CMD_OTP_BURN_PRODUCT_PV, &product_pv);
    hi_otp_func_fail_return(otp_ioctl, ret != HI_SUCCESS, ret);

    return ret;
}

hi_s32 sys_otp_read_product_pv(hi_otp_burn_pv_item *pv, hi_u32 num)
{
    hi_s32 ret;
    otp_product_pv product_pv;

    (hi_void)otp_memset(&product_pv, sizeof(otp_product_pv), 0, sizeof(otp_product_pv));

    addr_via(product_pv.pv) = pv;
    product_pv.num = num;

    ret = otp_ioctl(CMD_OTP_READ_PRODUCT_PV, &product_pv);
    hi_otp_func_fail_return(otp_ioctl, ret != HI_SUCCESS, ret);

    return ret;
}

hi_s32 sys_otp_get_key_verify_status(const hi_char *key_name, hi_bool *status)
{
    hi_s32 ret;
    otp_key_verify_status key_sta;

    (hi_void)otp_memset(&key_sta, sizeof(otp_key_verify_status), 0, sizeof(otp_key_verify_status));

    ret = otp_memcpy(key_sta.field_name, HI_OTP_FIELD_NAME_MAX_LEN, key_name, strlen(key_name));
    hi_otp_func_fail_return(otp_memcpy, ret != EOK, HI_ERR_OTP_FAILED_SEC_FUNC);

    ret = otp_ioctl(CMD_OTP_KEY_VERIFY_STATUS, &key_sta);
    hi_otp_func_fail_return(otp_ioctl, ret != HI_SUCCESS, ret);

    *status = key_sta.status;

    return ret;
}

